/*---------------------------------------------------------------
 * Programmer(s): Daniel R. Reynolds @ SMU
 *---------------------------------------------------------------
 * LLNS/SMU Copyright Start
 * Copyright (c) 2017, Southern Methodist University and 
 * Lawrence Livermore National Security
 *
 * This work was performed under the auspices of the U.S. Department 
 * of Energy by Southern Methodist University and Lawrence Livermore 
 * National Laboratory under Contract DE-AC52-07NA27344.
 * Produced at Southern Methodist University and the Lawrence 
 * Livermore National Laboratory.
 *
 * All rights reserved.
 * For details, see the LICENSE file.
 * LLNS/SMU Copyright End
 *---------------------------------------------------------------
 * This is the implementation file for the main ARKODE integrator.
 * It is independent of the ARKODE linear solver in use.
 *--------------------------------------------------------------*/

/*===============================================================
  Import Header Files                                 
  ===============================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "arkode_impl.h"
#include <sundials/sundials_math.h>
#include <sundials/sundials_types.h>

#define NO_DEBUG_OUTPUT
/* #define DEBUG_OUTPUT */
#ifdef DEBUG_OUTPUT
#include <nvector/nvector_serial.h>
#endif

#if defined(SUNDIALS_EXTENDED_PRECISION)
#define RSYM ".32Lg"
#else
#define RSYM ".16g"
#endif


/*===============================================================
  EXPORTED FUNCTIONS
  ===============================================================*/

/*---------------------------------------------------------------
  ARKodeCreate:

  ARKodeCreate creates an internal memory block for a problem to 
  be solved by ARKODE.  If successful, ARKodeCreate returns a 
  pointer to the problem memory. This pointer should be passed to
  ARKodeInit. If an initialization error occurs, ARKodeCreate 
  prints an error message to standard err and returns NULL. 
  ---------------------------------------------------------------*/
void *ARKodeCreate()
{
  int iret;
  ARKodeMem ark_mem;

  ark_mem = NULL;
  ark_mem = (ARKodeMem) malloc(sizeof(struct ARKodeMemRec));
  if (ark_mem == NULL) {
    arkProcessError(NULL, 0, "ARKODE", "ARKodeCreate", 
                    MSGARK_ARKMEM_FAIL);
    return(NULL);
  }

  /* Zero out ark_mem */
  memset(ark_mem, 0, sizeof(struct ARKodeMemRec));

  /* Set uround */
  ark_mem->ark_uround = UNIT_ROUNDOFF;

  /* Set default values for integrator optional inputs */
  iret = ARKodeSetDefaults((void *)ark_mem);
  if (iret != ARK_SUCCESS) {
    arkProcessError(NULL, 0, "ARKODE", "ARKodeCreate", 
                    "Error setting default solver options");
    return(NULL);
  }

  /* Initialize time step module to NULL */
  ark_mem->ark_step_attachlinsol = NULL;
  ark_mem->ark_step_attachmasssol = NULL;
  ark_mem->ark_step_disablelsetup = NULL;
  ark_mem->ark_step_disablemsetup = NULL;
  ark_mem->ark_step_getlinmem = NULL;
  ark_mem->ark_step_getmassmem = NULL;
  ark_mem->ark_step_getimplicitrhs = NULL;
  ark_mem->ark_step_mmult = NULL;
  ark_mem->ark_step_getgammas = NULL;
  ark_mem->ark_step_init = NULL;
  ark_mem->ark_step_fullrhs = NULL;
  ark_mem->ark_step = NULL;
  ark_mem->ark_step_resize = NULL;
  ark_mem->ark_step_print = NULL;
  ark_mem->ark_step_free = NULL;
  ark_mem->ark_step_mem = NULL;

  /* Initialize root finding variables */
  ark_mem->root_mem = NULL;

  /* Initialize diagnostics reporting variables */
  ark_mem->ark_report  = SUNFALSE;
  ark_mem->ark_diagfp  = NULL;

  /* Initialize lrw and liw */
  ark_mem->ark_lrw = 18;
  ark_mem->ark_liw = 39;  /* fcn/data ptr, int, long int, sunindextype, booleantype */

  /* No mallocs have been done yet */
  ark_mem->ark_VabstolMallocDone  = SUNFALSE;
  ark_mem->ark_VRabstolMallocDone = SUNFALSE;
  ark_mem->ark_MallocDone         = SUNFALSE;

  /* No user-supplied step postprocessing function yet */
  ark_mem->ark_ProcessStep = NULL;

  /* Return pointer to ARKODE memory block */
  return((void *)ark_mem);
}


/*---------------------------------------------------------------
  ARKodeResize:

  ARKodeResize re-initializes ARKODE's memory for a problem with a
  changing vector size.  It is assumed that the problem dynamics 
  before and after the vector resize will be comparable, so that 
  all time-stepping heuristics prior to calling ARKodeResize 
  remain valid after the call.  If instead the dynamics should be 
  re-calibrated, the ARKode memory structure should be deleted 
  with a call to ARKodeFree, and re-created with calls to 
  ARKodeCreate and arkodeInit.

  To aid in the vector-resize operation, the user can supply a 
  vector resize function, that will take as input an N_Vector with
  the previous size, and return as output a corresponding vector 
  of the new size.  If this function (of type ARKVecResizeFn) is 
  not supplied (i.e. is set to NULL), then all existing N_Vectors 
  will be destroyed and re-cloned from the input vector.

  In the case that the dynamical time scale should be modified 
  slightly from the previous time scale, an input "hscale" is 
  allowed, that will re-scale the upcoming time step by the 
  specified factor.  If a value <= 0 is specified, the default of 
  1.0 will be used.

  Other arguments:
  arkode_mem       Existing ARKode memory data structure.
  y0               The newly-sized solution vector, holding 
                   the current dependent variable values.
  t0               The current value of the independent 
                   variable.
  resize_data      User-supplied data structure that will be 
                   passed to the supplied resize function.

  The return value is ARK_SUCCESS = 0 if no errors occurred, or
  a negative value otherwise.
  ---------------------------------------------------------------*/
int ARKodeResize(void *arkode_mem, N_Vector y0, 
                 realtype hscale, realtype t0, 
                 ARKVecResizeFn resize, void *resize_data)
{
  ARKodeMem ark_mem;
  sunindextype lrw1, liw1, lrw_diff, liw_diff;
  int ier;
 
  /* Check arkode_mem */
  if (arkode_mem==NULL) {
    arkProcessError(NULL, ARK_MEM_NULL, "ARKODE", 
                    "ARKodeResize", MSGARK_NO_MEM);
    return(ARK_MEM_NULL);
  }
  ark_mem = (ARKodeMem) arkode_mem;

  /* Check if arkode_mem was allocated */
  if (ark_mem->ark_MallocDone == SUNFALSE) {
    arkProcessError(ark_mem, ARK_NO_MALLOC, "ARKODE", 
                    "ARKodeResize", MSGARK_NO_MALLOC);
    return(ARK_NO_MALLOC);
  }

  /* Check for legal input parameters */
  if (y0 == NULL) {
    arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", 
                    "ARKodeResize", MSGARK_NULL_Y0);
    return(ARK_ILL_INPUT);
  }
  
  /* Copy the input parameters into ARKODE state */
  ark_mem->ark_tn = t0;
  ark_mem->ark_tnew = t0;

  /* Update time-stepping parameters */
  /*   adjust upcoming step size depending on hscale */
  if (hscale < 0.0)  hscale = 1.0;
  if (hscale != 1.0) {

    /* Encode hscale into ark_mem structure */
    ark_mem->ark_eta = hscale;
    ark_mem->ark_hprime *= hscale;

    /* If next step would overtake tstop, adjust stepsize */
    if ( ark_mem->ark_tstopset ) 
      if ( (ark_mem->ark_tn + ark_mem->ark_hprime - ark_mem->ark_tstop)*ark_mem->ark_hprime > ZERO ) {
        ark_mem->ark_hprime = (ark_mem->ark_tstop-ark_mem->ark_tn) *
          (ONE-FOUR*ark_mem->ark_uround);
        ark_mem->ark_eta = ark_mem->ark_hprime/ark_mem->ark_h;
      }

  }

  /* Determing change in vector sizes */
  lrw1 = liw1 = 0;
  if (y0->ops->nvspace != NULL) 
    N_VSpace(y0, &lrw1, &liw1);
  lrw_diff = lrw1 - ark_mem->ark_lrw1;
  liw_diff = liw1 - ark_mem->ark_liw1;
  ark_mem->ark_lrw1 = lrw1;
  ark_mem->ark_liw1 = liw1;

  /* Resize the ARKode vectors */
  /*     Vabstol */
  ier = arkResizeVec(ark_mem, resize, resize_data, lrw_diff,
                     liw_diff, y0, &ark_mem->ark_Vabstol);
  if (ier != ARK_SUCCESS)  return(ier);
  /*     VRabstol */
  ier = arkResizeVec(ark_mem, resize, resize_data, lrw_diff,
                     liw_diff, y0, &ark_mem->ark_VRabstol);
  if (ier != ARK_SUCCESS)  return(ier);
  /*     ewt */
  ier = arkResizeVec(ark_mem, resize, resize_data, lrw_diff,
                     liw_diff, y0, &ark_mem->ark_ewt);
  if (ier != ARK_SUCCESS)  return(ier);
  /*     rwt  */
  if (ark_mem->ark_rwt_is_ewt) {      /* update pointer to ewt */
    ark_mem->ark_rwt = ark_mem->ark_ewt;
  } else {                            /* resize if distinct from ewt */
    ier = arkResizeVec(ark_mem, resize, resize_data, lrw_diff,
                       liw_diff, y0, &ark_mem->ark_rwt);
    if (ier != ARK_SUCCESS)  return(ier);
  }
  /*     ycur */
  ier = arkResizeVec(ark_mem, resize, resize_data, lrw_diff,
                     liw_diff, y0, &ark_mem->ark_ycur);
  if (ier != ARK_SUCCESS)  return(ier);
  /*     tempv */
  ier = arkResizeVec(ark_mem, resize, resize_data, lrw_diff,
                     liw_diff, y0, &ark_mem->ark_tempv1);
  if (ier != ARK_SUCCESS)  return(ier);
  /*     tempv2 */
  ier = arkResizeVec(ark_mem, resize, resize_data, lrw_diff,
                     liw_diff, y0, &ark_mem->ark_tempv2);
  if (ier != ARK_SUCCESS)  return(ier);


  /* Resize interpolation structure memory */
  if (ark_mem->ark_interp) {
    ier = arkInterpResize(ark_mem, ark_mem->ark_interp, resize,
                          resize_data, lrw_diff, liw_diff, y0);
    if (ier != ARK_SUCCESS) {
      arkProcessError(ark_mem, ier, "ARKODE", "ARKodeResize",
                      "Interpolation module resize failure");
      return(ier);
    }
  }
  
  /* Resize time step module memory */
  if (ark_mem->ark_step_resize == NULL) {
    arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", "ARKodeResize", 
                    "Missing ark_step_resize routine");
    return(ARK_ILL_INPUT);
  }
  ier = ark_mem->ark_step_resize(ark_mem, resize, resize_data,
                                 lrw_diff, liw_diff, y0);
  if (ier != ARK_SUCCESS) {
    arkProcessError(ark_mem, ier, "ARKODE", "ARKodeResize",
                    "Time step module resize failure");
    return(ier);
  }

  /* Copy y0 into ark_ycur to set the current solution */
  N_VScale(ONE, y0, ark_mem->ark_ycur);

  /* Indicate that problem size is new */
  ark_mem->ark_resized = SUNTRUE;
  ark_mem->ark_firststage = SUNTRUE;
  
  /* Problem has been successfully re-sized */
  return(ARK_SUCCESS);
}


/*---------------------------------------------------------------
  ARKodeSStolerances:
  ARKodeSVtolerances:
  ARKodeWFtolerances:

  These functions specify the integration tolerances. One of them
  SHOULD be called before the first call to ARKode; otherwise 
  default values of reltol=1e-4 and abstol=1e-9 will be used, 
  which may be entirely incorrect for a specific problem.

  ARKodeSStolerances specifies scalar relative and absolute 
  tolerances.

  ARKodeSVtolerances specifies scalar relative tolerance and a 
  vector absolute tolerance (a potentially different absolute 
  tolerance for each vector component).

  ARKodeWFtolerances specifies a user-provides function (of type
  ARKEwtFn) which will be called to set the error weight vector.
  ---------------------------------------------------------------*/
int ARKodeSStolerances(void *arkode_mem, realtype reltol, 
                       realtype abstol)
{
  ARKodeMem ark_mem;

  if (arkode_mem==NULL) {
    arkProcessError(NULL, ARK_MEM_NULL, "ARKODE", 
                    "ARKodeSStolerances", MSGARK_NO_MEM);
    return(ARK_MEM_NULL);
  }
  ark_mem = (ARKodeMem) arkode_mem;

  if (ark_mem->ark_MallocDone == SUNFALSE) {
    arkProcessError(ark_mem, ARK_NO_MALLOC, "ARKODE", 
                    "ARKodeSStolerances", MSGARK_NO_MALLOC);
    return(ARK_NO_MALLOC);
  }

  /* Check inputs */
  if (reltol < ZERO) {
    arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", 
                    "ARKodeSStolerances", MSGARK_BAD_RELTOL);
    return(ARK_ILL_INPUT);
  }
  if (abstol < ZERO) {
    arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", 
                    "ARKodeSStolerances", MSGARK_BAD_ABSTOL);
    return(ARK_ILL_INPUT);
  }

  /* Copy tolerances into memory */
  ark_mem->ark_reltol  = reltol;
  ark_mem->ark_Sabstol = abstol;
  ark_mem->ark_itol    = ARK_SS;

  /* enforce use of arkEwtSet */
  ark_mem->ark_user_efun = SUNFALSE;
  ark_mem->ark_efun      = arkEwtSet;
  ark_mem->ark_e_data    = ark_mem;

  return(ARK_SUCCESS);
}


int ARKodeSVtolerances(void *arkode_mem, realtype reltol, 
                       N_Vector abstol)
{
  ARKodeMem ark_mem;

  if (arkode_mem==NULL) {
    arkProcessError(NULL, ARK_MEM_NULL, "ARKODE", 
                    "ARKodeSVtolerances", MSGARK_NO_MEM);
    return(ARK_MEM_NULL);
  }
  ark_mem = (ARKodeMem) arkode_mem;

  if (ark_mem->ark_MallocDone == SUNFALSE) {
    arkProcessError(ark_mem, ARK_NO_MALLOC, "ARKODE", 
                    "ARKodeSVtolerances", MSGARK_NO_MALLOC);
    return(ARK_NO_MALLOC);
  }

  /* Check inputs */
  if (reltol < ZERO) {
    arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", 
                    "ARKodeSVtolerances", MSGARK_BAD_RELTOL);
    return(ARK_ILL_INPUT);
  }
  if (N_VMin(abstol) < ZERO) {
    arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", 
                    "ARKodeSVtolerances", MSGARK_BAD_ABSTOL);
    return(ARK_ILL_INPUT);
  }

  /* Copy tolerances into memory */
  if ( !(ark_mem->ark_VabstolMallocDone) ) {
    ark_mem->ark_Vabstol = N_VClone(ark_mem->ark_ewt);
    ark_mem->ark_lrw += ark_mem->ark_lrw1;
    ark_mem->ark_liw += ark_mem->ark_liw1;
    ark_mem->ark_VabstolMallocDone = SUNTRUE;
  }
  N_VScale(ONE, abstol, ark_mem->ark_Vabstol);
  ark_mem->ark_reltol = reltol;
  ark_mem->ark_itol   = ARK_SV;

  /* enforce use of arkEwtSet */
  ark_mem->ark_user_efun = SUNFALSE;
  ark_mem->ark_efun      = arkEwtSet;
  ark_mem->ark_e_data    = ark_mem;

  return(ARK_SUCCESS);
}


int ARKodeWFtolerances(void *arkode_mem, ARKEwtFn efun)
{
  ARKodeMem ark_mem;

  if (arkode_mem==NULL) {
    arkProcessError(NULL, ARK_MEM_NULL, "ARKODE", 
                    "ARKodeWFtolerances", MSGARK_NO_MEM);
    return(ARK_MEM_NULL);
  }
  ark_mem = (ARKodeMem) arkode_mem;

  if (ark_mem->ark_MallocDone == SUNFALSE) {
    arkProcessError(ark_mem, ARK_NO_MALLOC, "ARKODE", 
                    "ARKodeWFtolerances", MSGARK_NO_MALLOC);
    return(ARK_NO_MALLOC);
  }

  /* Copy tolerance data into memory */
  ark_mem->ark_itol      = ARK_WF;
  ark_mem->ark_user_efun = SUNTRUE;
  ark_mem->ark_efun      = efun;
  ark_mem->ark_e_data    = NULL; /* set to user_data in InitialSetup */

  return(ARK_SUCCESS);
}


/*---------------------------------------------------------------
  ARKodeResStolerance:
  ARKodeResVtolerance:
  ARKodeResFtolerance:

  These functions specify the absolute residual tolerance. 
  Specification of the absolute residual tolerance is only 
  necessary for problems with non-identity mass matrices in which
  the units of the solution vector y dramatically differ from the 
  units of the ODE right-hand side f(t,y).  If this occurs, one 
  of these routines SHOULD be called before the first call to 
  ARKode; otherwise the default value of rabstol=1e-9 will be 
  used, which may be entirely incorrect for a specific problem.

  ARKodeResStolerances specifies a scalar residual tolerance.

  ARKodeResVtolerances specifies a vector residual tolerance 
  (a potentially different absolute residual tolerance for 
  each vector component).

  ARKodeResFtolerances specifies a user-provides function (of 
  type ARKRwtFn) which will be called to set the residual 
  weight vector.
  ---------------------------------------------------------------*/
int ARKodeResStolerance(void *arkode_mem, realtype rabstol)
{
  ARKodeMem ark_mem;

  if (arkode_mem==NULL) {
    arkProcessError(NULL, ARK_MEM_NULL, "ARKODE", 
                    "ARKodeResStolerances", MSGARK_NO_MEM);
    return(ARK_MEM_NULL);
  }
  ark_mem = (ARKodeMem) arkode_mem;

  if (ark_mem->ark_MallocDone == SUNFALSE) {
    arkProcessError(ark_mem, ARK_NO_MALLOC, "ARKODE", 
                    "ARKodeResStolerances", MSGARK_NO_MALLOC);
    return(ARK_NO_MALLOC);
  }

  /* Check inputs */
  if (rabstol < ZERO) {
    arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", 
                    "ARKodeResStolerances", MSGARK_BAD_RABSTOL);
    return(ARK_ILL_INPUT);
  }

  /* Allocate space for rwt if necessary */
  if (ark_mem->ark_rwt_is_ewt) {
    ark_mem->ark_rwt_is_ewt = SUNFALSE;
    ark_mem->ark_rwt = N_VClone(ark_mem->ark_ewt);
    ark_mem->ark_lrw += ark_mem->ark_lrw1;
    ark_mem->ark_liw += ark_mem->ark_liw1;
  }

  /* Copy tolerances into memory */
  ark_mem->ark_SRabstol = rabstol;
  ark_mem->ark_ritol    = ARK_SS;

  /* enforce use of arkRwtSet */
  ark_mem->ark_user_efun = SUNFALSE;
  ark_mem->ark_rfun      = arkRwtSet;
  ark_mem->ark_r_data    = ark_mem;

  return(ARK_SUCCESS);
}


int ARKodeResVtolerance(void *arkode_mem, N_Vector rabstol)
{
  ARKodeMem ark_mem;

  if (arkode_mem==NULL) {
    arkProcessError(NULL, ARK_MEM_NULL, "ARKODE", 
                    "ARKodeResVtolerances", MSGARK_NO_MEM);
    return(ARK_MEM_NULL);
  }
  ark_mem = (ARKodeMem) arkode_mem;

  if (ark_mem->ark_MallocDone == SUNFALSE) {
    arkProcessError(ark_mem, ARK_NO_MALLOC, "ARKODE", 
                    "ARKodeResVtolerances", MSGARK_NO_MALLOC);
    return(ARK_NO_MALLOC);
  }

  /* Check inputs */
  if (N_VMin(rabstol) < ZERO) {
    arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", 
                    "ARKodeResVtolerances", MSGARK_BAD_RABSTOL);
    return(ARK_ILL_INPUT);
  }

  /* Allocate space for rwt if necessary */
  if (ark_mem->ark_rwt_is_ewt) {
    ark_mem->ark_rwt_is_ewt = SUNFALSE;
    ark_mem->ark_rwt = N_VClone(ark_mem->ark_ewt);
    ark_mem->ark_lrw += ark_mem->ark_lrw1;
    ark_mem->ark_liw += ark_mem->ark_liw1;
  }

  /* Copy tolerances into memory */
  if ( !(ark_mem->ark_VRabstolMallocDone) ) {
    ark_mem->ark_VRabstol = N_VClone(ark_mem->ark_rwt);
    ark_mem->ark_lrw += ark_mem->ark_lrw1;
    ark_mem->ark_liw += ark_mem->ark_liw1;
    ark_mem->ark_VRabstolMallocDone = SUNTRUE;
  }
  N_VScale(ONE, rabstol, ark_mem->ark_VRabstol);
  ark_mem->ark_ritol = ARK_SV;


  /* enforce use of arkRwtSet */
  ark_mem->ark_user_efun = SUNFALSE;
  ark_mem->ark_rfun      = arkRwtSet;
  ark_mem->ark_r_data    = ark_mem;

  return(ARK_SUCCESS);
}


int ARKodeResFtolerance(void *arkode_mem, ARKRwtFn rfun)
{
  ARKodeMem ark_mem;

  if (arkode_mem==NULL) {
    arkProcessError(NULL, ARK_MEM_NULL, "ARKODE", 
                    "ARKodeResFtolerances", MSGARK_NO_MEM);
    return(ARK_MEM_NULL);
  }
  ark_mem = (ARKodeMem) arkode_mem;

  if (ark_mem->ark_MallocDone == SUNFALSE) {
    arkProcessError(ark_mem, ARK_NO_MALLOC, "ARKODE", 
                    "ARKodeResFtolerances", MSGARK_NO_MALLOC);
    return(ARK_NO_MALLOC);
  }

  /* Allocate space for rwt if necessary */
  if (ark_mem->ark_rwt_is_ewt) {
    ark_mem->ark_rwt_is_ewt = SUNFALSE;
    ark_mem->ark_rwt = N_VClone(ark_mem->ark_ewt);
    ark_mem->ark_lrw += ark_mem->ark_lrw1;
    ark_mem->ark_liw += ark_mem->ark_liw1;
  }

  /* Copy tolerance data into memory */
  ark_mem->ark_ritol     = ARK_WF;
  ark_mem->ark_user_rfun = SUNTRUE;
  ark_mem->ark_rfun      = rfun;
  ark_mem->ark_r_data    = NULL; /* set to user_data in InitialSetup */

  return(ARK_SUCCESS);
}


/*---------------------------------------------------------------
  ARKode:

  This routine is the main driver of the ARKODE package. 

  It integrates over a time interval defined by the user, by 
  calling ark_step to do internal time steps.

  The first time that ARKode is called for a successfully 
  initialized problem, it computes a tentative initial step size.

  ARKode supports two modes as specified by itask: ARK_NORMAL and
  ARK_ONE_STEP.  In the ARK_NORMAL mode, the solver steps until 
  it reaches or passes tout and then interpolates to obtain 
  y(tout).  In the ARK_ONE_STEP mode, it takes one internal step 
  and returns.  The behavior of both modes can be over-rided 
  through user-specification of ark_tstop (through the
  ARKodeSetStopTime function), in which case if a solver step 
  would pass tstop, the step is shortened so that it stops at
  exactly the specified stop time, and hence interpolation of 
  y(tout) is not required.
  ---------------------------------------------------------------*/
int ARKode(void *arkode_mem, realtype tout, N_Vector yout, 
           realtype *tret, int itask)
{
  ARKodeMem ark_mem;
  long int nstloc;
  int retval, kflag, istate, ir, ier;
  int ewtsetOK;
  realtype troundoff, nrm;
  booleantype inactive_roots;


  /* Check and process inputs */

  /* Check if arkode_mem exists */
  if (arkode_mem == NULL) {
    arkProcessError(NULL, ARK_MEM_NULL, "ARKODE", "ARKode", 
                    MSGARK_NO_MEM);
    return(ARK_MEM_NULL);
  }
  ark_mem = (ARKodeMem) arkode_mem;

  /* Check if arkode_mem was allocated */
  if (ark_mem->ark_MallocDone == SUNFALSE) {
    arkProcessError(ark_mem, ARK_NO_MALLOC, "ARKODE", "ARKode", 
                    MSGARK_NO_MALLOC);
    return(ARK_NO_MALLOC);
  }
  
  /* Check for yout != NULL */
  if ((ark_mem->ark_y = yout) == NULL) {
    arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", "ARKode", 
                    MSGARK_YOUT_NULL);
    return(ARK_ILL_INPUT);
  }

  /* Check for tret != NULL */
  if (tret == NULL) {
    arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", "ARKode", 
                    MSGARK_TRET_NULL);
    return(ARK_ILL_INPUT);
  }

  /* Check for valid itask */
  if ( (itask != ARK_NORMAL) && (itask != ARK_ONE_STEP) ) {
    arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", "ARKode", 
                    MSGARK_BAD_ITASK);
    return(ARK_ILL_INPUT);
  }

  /* store copy of itask if using root-finding */
  if (ark_mem->root_mem != NULL) {
    if (itask == ARK_NORMAL) ark_mem->root_mem->toutc = tout;
    ark_mem->root_mem->taskc = itask;
  }


  /* perform first-step-specific initializations:
     - initialize tret values to initialization time
     - perform initial integrator setup  */
  if (ark_mem->ark_nst == 0) {
    ark_mem->ark_tretlast = *tret = ark_mem->ark_tn;
    ier = arkInitialSetup(ark_mem, tout);
    if (ier!= ARK_SUCCESS) return(ier);
  }


  /* perform first-step-after-resize initializations */ 
  if (ark_mem->ark_nst > 0 && ark_mem->ark_resized) {
    ier = arkPostResizeSetup(ark_mem);
    if (ier!= ARK_SUCCESS) return(ier);
  }


  /* perform stopping tests */
  if (ark_mem->ark_nst > 0 && !ark_mem->ark_resized)
    if (arkStopTests(ark_mem, tout, yout, tret, itask, &ier))
      return(ier);


  /*--------------------------------------------------
    Looping point for internal steps
 
    - update the ewt vector for the next step
    - check for errors (too many steps, too much
      accuracy requested, step size too small)
    - take a new step (via ark_step); stop on error 
    - perform stop tests:
    - check for root in last step taken
    - check if tout was passed
    - check if close to tstop
    - check if in ONE_STEP mode (must return)
    --------------------------------------------------*/
  nstloc = 0;
  for(;;) {
   
    ark_mem->ark_next_h = ark_mem->ark_h;
    
    /* Reset and check ewt */
    if (ark_mem->ark_nst > 0 && !ark_mem->ark_resized) {
      ewtsetOK = ark_mem->ark_efun(ark_mem->ark_ycur,
                                   ark_mem->ark_ewt, 
                                   ark_mem->ark_e_data);
      if (ewtsetOK != 0) {
        if (ark_mem->ark_itol == ARK_WF) 
          arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", "ARKode", 
                          MSGARK_EWT_NOW_FAIL, ark_mem->ark_tn);
        else 
          arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", "ARKode", 
                          MSGARK_EWT_NOW_BAD, ark_mem->ark_tn);
        
        istate = ARK_ILL_INPUT;
        ark_mem->ark_tretlast = *tret = ark_mem->ark_tn;
        N_VScale(ONE, ark_mem->ark_ycur, yout);
        break;
      }
    }
    
    /* Reset and check rwt */
    if (!ark_mem->ark_rwt_is_ewt) {
      if (ark_mem->ark_nst > 0 && !ark_mem->ark_resized) {
        ewtsetOK = ark_mem->ark_rfun(ark_mem->ark_ycur,
                                     ark_mem->ark_rwt,
                                     ark_mem->ark_r_data);
        if (ewtsetOK != 0) {
          if (ark_mem->ark_itol == ARK_WF) 
            arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", "ARKode", 
                            MSGARK_RWT_NOW_FAIL, ark_mem->ark_tn);
          else 
            arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", "ARKode", 
                            MSGARK_RWT_NOW_BAD, ark_mem->ark_tn);
        
          istate = ARK_ILL_INPUT;
          ark_mem->ark_tretlast = *tret = ark_mem->ark_tn;
          N_VScale(ONE, ark_mem->ark_ycur, yout);
          break;
        }
      }
    }
    
    /* Check for too many steps */
    if ( (ark_mem->ark_mxstep>0) && (nstloc >= ark_mem->ark_mxstep) ) {
      arkProcessError(ark_mem, ARK_TOO_MUCH_WORK, "ARKODE", "ARKode", 
                      MSGARK_MAX_STEPS, ark_mem->ark_tn);
      istate = ARK_TOO_MUCH_WORK;
      ark_mem->ark_tretlast = *tret = ark_mem->ark_tn;
      N_VScale(ONE, ark_mem->ark_ycur, yout);
      break;
    }

    /* Check for too much accuracy requested */
    nrm = N_VWrmsNorm(ark_mem->ark_ycur, ark_mem->ark_ewt);
    ark_mem->ark_tolsf = ark_mem->ark_uround * nrm;
    if (ark_mem->ark_tolsf > ONE) {
      arkProcessError(ark_mem, ARK_TOO_MUCH_ACC, "ARKODE", "ARKode", 
                      MSGARK_TOO_MUCH_ACC, ark_mem->ark_tn);
      istate = ARK_TOO_MUCH_ACC;
      ark_mem->ark_tretlast = *tret = ark_mem->ark_tn;
      N_VScale(ONE, ark_mem->ark_ycur, yout);
      ark_mem->ark_tolsf *= TWO;
      break;
    } else {
      ark_mem->ark_tolsf = ONE;
    }

    /* Check for h below roundoff level in tn */
    if (ark_mem->ark_tn + ark_mem->ark_h == ark_mem->ark_tn) {
      ark_mem->ark_nhnil++;
      if (ark_mem->ark_nhnil <= ark_mem->ark_mxhnil) 
        arkProcessError(ark_mem, ARK_WARNING, "ARKODE", "ARKode", 
                        MSGARK_HNIL, ark_mem->ark_tn, ark_mem->ark_h);
      if (ark_mem->ark_nhnil == ark_mem->ark_mxhnil) 
        arkProcessError(ark_mem, ARK_WARNING, "ARKODE", "ARKode", 
                        MSGARK_HNIL_DONE);
    }

    /* Update parameter for upcoming step size */
    if ((ark_mem->ark_nst > 0) && (ark_mem->ark_hprime != ark_mem->ark_h)) {
      ark_mem->ark_h = ark_mem->ark_h * ark_mem->ark_eta;
      ark_mem->ark_next_h = ark_mem->ark_h;
    }
    if (ark_mem->ark_fixedstep) {
      ark_mem->ark_h = ark_mem->ark_hin;
      ark_mem->ark_next_h = ark_mem->ark_h;
    }

    /* Call arkStep to take a step */
    kflag = ark_mem->ark_step((void*) ark_mem);

    /* Process successful step, catch additional errors to send to arkHandleFailure */
    if (kflag == ARK_SUCCESS) 
      kflag = arkCompleteStep(ark_mem);
    
    /* Process failed step cases, and exit loop */
    if (kflag != ARK_SUCCESS) {
      istate = arkHandleFailure(ark_mem, kflag);
      ark_mem->ark_tretlast = *tret = ark_mem->ark_tn;
      N_VScale(ONE, ark_mem->ark_ycur, yout);
      break;
    }
    
    nstloc++;

    /* Check for root in last step taken. */
    if (ark_mem->root_mem != NULL)
      if (ark_mem->root_mem->nrtfn > 0) {

        retval = arkRootCheck3((void*) ark_mem);
        if (retval == RTFOUND) {  /* A new root was found */
          ark_mem->root_mem->irfnd = 1;
          istate = ARK_ROOT_RETURN;
          ark_mem->ark_tretlast = *tret = ark_mem->root_mem->tlo;
          break;
        } else if (retval == ARK_RTFUNC_FAIL) { /* g failed */
          arkProcessError(ark_mem, ARK_RTFUNC_FAIL, "ARKODE", "arkRootCheck3", 
                          MSGARK_RTFUNC_FAILED, ark_mem->root_mem->tlo);
          istate = ARK_RTFUNC_FAIL;
          break;
        }

        /* If we are at the end of the first step and we still have
           some event functions that are inactive, issue a warning
           as this may indicate a user error in the implementation
           of the root function. */
        if (ark_mem->ark_nst==1) {
          inactive_roots = SUNFALSE;
          for (ir=0; ir<ark_mem->root_mem->nrtfn; ir++) { 
            if (!ark_mem->root_mem->gactive[ir]) {
              inactive_roots = SUNTRUE;
              break;
            }
          }
          if ((ark_mem->root_mem->mxgnull > 0) && inactive_roots) {
            arkProcessError(ark_mem, ARK_WARNING, "ARKODES", "ARKode", 
                            MSGARK_INACTIVE_ROOTS);
          }
        }
      }
    
    /* In NORMAL mode, check if tout reached */
    if ( (itask == ARK_NORMAL) &&
         (ark_mem->ark_tn-tout)*ark_mem->ark_h >= ZERO ) {
      istate = ARK_SUCCESS;
      ark_mem->ark_tretlast = *tret = tout;
      (void) ARKodeGetDky(ark_mem, tout, 0, yout);
      ark_mem->ark_next_h = ark_mem->ark_hprime;
      break;
    }

    /* Check if tn is at tstop or near tstop */
    if ( ark_mem->ark_tstopset ) {
      troundoff = FUZZ_FACTOR*ark_mem->ark_uround * 
        (SUNRabs(ark_mem->ark_tn) + SUNRabs(ark_mem->ark_h));
      if ( SUNRabs(ark_mem->ark_tn - ark_mem->ark_tstop) <= troundoff) {
        (void) ARKodeGetDky(ark_mem, ark_mem->ark_tstop, 0, yout);
        ark_mem->ark_tretlast = *tret = ark_mem->ark_tstop;
        ark_mem->ark_tstopset = SUNFALSE;
        istate = ARK_TSTOP_RETURN;
        break;
      }
      if ( (ark_mem->ark_tn + ark_mem->ark_hprime - ark_mem->ark_tstop)*ark_mem->ark_h > ZERO ) {
        ark_mem->ark_hprime = (ark_mem->ark_tstop - ark_mem->ark_tn) *
          (ONE-FOUR*ark_mem->ark_uround);
        ark_mem->ark_eta = ark_mem->ark_hprime/ark_mem->ark_h;
      }
    }

    /* In ONE_STEP mode, copy y and exit loop */
    if (itask == ARK_ONE_STEP) {
      istate = ARK_SUCCESS;
      ark_mem->ark_tretlast = *tret = ark_mem->ark_tn;
      N_VScale(ONE, ark_mem->ark_ycur, yout);
      ark_mem->ark_next_h = ark_mem->ark_hprime;
      break;
    }

  } /* end looping for internal steps */

  return(istate);
}


/*---------------------------------------------------------------
  ARKodeGetDky:

  This routine computes the k-th derivative of the interpolating
  polynomial at the time t and stores the result in the vector 
  dky. This routine internally calls arkInterpEvaluate to perform the
  interpolation.  We have the restriction that 0 <= k <= 3.  This 
  routine uses an interpolating polynomial of degree 
  max(ark_dense_q, k), i.e. it will form a polynomial of the
  degree requested by the user through ark_dense_q, unless 
  higher-order derivatives are requested.

  This function is called by ARKode with k=0 and t=tout to perform
  interpolation of outputs, but may also be called directly by the
  user.  Note: in all cases it will be called after ark_tn has 
  been updated to correspond with the end time of the last 
  successful step.
  ---------------------------------------------------------------*/
int ARKodeGetDky(void *arkode_mem, realtype t, int k, N_Vector dky)
{
  realtype s, tfuzz, tp, tn1;
  int retval, degree;
  ARKodeMem ark_mem;
  
  /* Check all inputs for legality */
  if (arkode_mem == NULL) {
    arkProcessError(NULL, ARK_MEM_NULL, "ARKODE", "ARKodeGetDky", 
                    MSGARK_NO_MEM);
    return(ARK_MEM_NULL);
  }
  ark_mem = (ARKodeMem) arkode_mem;
  if (dky == NULL) {
    arkProcessError(ark_mem, ARK_BAD_DKY, "ARKODE", "ARKodeGetDky", 
                    MSGARK_NULL_DKY);
    return(ARK_BAD_DKY);
  }
  if ((k < 0) || (k > 3)) {
    arkProcessError(ark_mem, ARK_BAD_K, "ARKODE", "ARKodeGetDky", 
                    MSGARK_BAD_K);
    return(ARK_BAD_K);
  }
  if (ark_mem->ark_interp == NULL) {
    arkProcessError(ark_mem, ARK_MEM_NULL, "ARKODE", "ARKodeGetDky",
                    "Missing interpolation structure");
    return(ARK_MEM_NULL);
  }

  
  /* Allow for some slack */
  tfuzz = FUZZ_FACTOR * ark_mem->ark_uround * 
    (SUNRabs(ark_mem->ark_tn) + SUNRabs(ark_mem->ark_hold));
  if (ark_mem->ark_hold < ZERO) tfuzz = -tfuzz;
  tp = ark_mem->ark_tn - ark_mem->ark_hold - tfuzz;
  tn1 = ark_mem->ark_tn + tfuzz;
  if ((t-tp)*(t-tn1) > ZERO) {
    arkProcessError(ark_mem, ARK_BAD_T, "ARKODE", "ARKodeGetDky", 
                    MSGARK_BAD_T, t, ark_mem->ark_tn-ark_mem->ark_hold, 
                    ark_mem->ark_tn);
    return(ARK_BAD_T);
  }

  /* call arkInterpEvaluate to evaluate result */
  s = (t - ark_mem->ark_tn) / ark_mem->ark_h;
  degree = (k > ark_mem->ark_dense_q) ? k : ark_mem->ark_dense_q;
  retval = arkInterpEvaluate(ark_mem, ark_mem->ark_interp, s, k, degree, dky);
  if (retval != ARK_SUCCESS) { 
    arkProcessError(ark_mem, retval, "ARKODE", "ARKodeGetDky", 
                    "Error calling arkInterpEvaluate");
    return(retval);
  }
  return(ARK_SUCCESS);
}


/*---------------------------------------------------------------
  ARKodeFree:

  This routine frees the problem memory allocated by arkodeInit.
  Such memory includes all the vectors allocated by 
  arkAllocVectors, and the memory lmem for
  the linear solver (deallocated by a call to lfree).
  ---------------------------------------------------------------*/
void ARKodeFree(void **arkode_mem)
{
  ARKodeMem ark_mem;

  if (*arkode_mem == NULL) return;

  ark_mem = (ARKodeMem) (*arkode_mem);
  
  arkFreeVectors(ark_mem);
  if (ark_mem->ark_interp != NULL) 
    arkInterpFree(&(ark_mem->ark_interp));

  if (ark_mem->ark_step_free != NULL)
    (void) ark_mem->ark_step_free(*arkode_mem);
  
  if (ark_mem->root_mem != NULL)
    (void) arkRootFree(*arkode_mem);

  free(*arkode_mem);
  *arkode_mem = NULL;
}



/*===============================================================
  Internal functions that may be replaced by the user
  ===============================================================*/

/*---------------------------------------------------------------
  arkEwtSet

  This routine is responsible for setting the error weight vector ewt,
  according to tol_type, as follows:

  (1) ewt[i] = 1 / (reltol * SUNRabs(ycur[i]) + abstol), i=0,...,neq-1
      if tol_type = ARK_SS
  (2) ewt[i] = 1 / (reltol * SUNRabs(ycur[i]) + abstol[i]), i=0,...,neq-1
      if tol_type = ARK_SV

  arkEwtSet returns 0 if ewt is successfully set as above to a
  positive vector and -1 otherwise. In the latter case, ewt is
  considered undefined.

  All the real work is done in the routines arkEwtSetSS, arkEwtSetSV.
  ---------------------------------------------------------------*/
int arkEwtSet(N_Vector ycur, N_Vector weight, void *data)
{
  ARKodeMem ark_mem;
  int flag = 0;

  /* data points to ark_mem here */
  ark_mem = (ARKodeMem) data;

  switch(ark_mem->ark_itol) {
  case ARK_SS: 
    flag = arkEwtSetSS(ark_mem, ycur, weight);
    break;
  case ARK_SV: 
    flag = arkEwtSetSV(ark_mem, ycur, weight);
    break;
  }
  
  return(flag);
}


/*---------------------------------------------------------------
  arkRwtSet

  This routine is responsible for setting the residual weight 
  vector rwt, according to tol_type, as follows:

  (1) rwt[i] = 1 / (reltol * SUNRabs(M*ycur[i]) + rabstol), i=0,...,neq-1
      if tol_type = ARK_SS
  (2) rwt[i] = 1 / (reltol * SUNRabs(M*ycur[i]) + rabstol[i]), i=0,...,neq-1
      if tol_type = ARK_SV
  (3) unset if tol_type is any other value (occurs rwt=ewt)

  arkRwtSet returns 0 if rwt is successfully set as above to a
  positive vector and -1 otherwise. In the latter case, rwt is
  considered undefined.

  All the real work is done in the routines arkRwtSetSS, arkRwtSetSV.
  ---------------------------------------------------------------*/
int arkRwtSet(N_Vector y, N_Vector weight, void *data)
{
  ARKodeMem ark_mem;
  N_Vector My;
  int flag = 0;

  /* data points to ark_mem here */
  ark_mem = (ARKodeMem) data;

  /* return if rwt is just ewt */
  if (ark_mem->ark_rwt_is_ewt)  return(0);

  /* put M*y into ark_tempv1 */
  My = ark_mem->ark_tempv1;
  if (ark_mem->ark_step_mmult != NULL) {
    flag = ark_mem->ark_step_mmult((void *) ark_mem, y, My);
    if (flag != ARK_SUCCESS)  return (ARK_MASSMULT_FAIL);
  } else {  /* this condition should not apply, but just in case */
    N_VScale(ONE, y, My);
  }

  /* call appropriate routine to fill rwt */
  switch(ark_mem->ark_ritol) {
  case ARK_SS: 
    flag = arkRwtSetSS(ark_mem, My, weight);
    break;
  case ARK_SV: 
    flag = arkRwtSetSV(ark_mem, My, weight);
    break;
  }
  
  return(flag);
}


/*---------------------------------------------------------------
  arkErrHandler is the default error handling function.
  It sends the error message to the stream pointed to by ark_errfp 
  ---------------------------------------------------------------*/
void arkErrHandler(int error_code, const char *module,
                   const char *function, char *msg, void *data)
{
  ARKodeMem ark_mem;
  char err_type[10];

  /* data points to ark_mem here */
  ark_mem = (ARKodeMem) data;

  if (error_code == ARK_WARNING)
    sprintf(err_type,"WARNING");
  else
    sprintf(err_type,"ERROR");

#ifndef NO_FPRINTF_OUTPUT
  if (ark_mem->ark_errfp!=NULL) {
    fprintf(ark_mem->ark_errfp,"\n[%s %s]  %s\n",module,err_type,function);
    fprintf(ark_mem->ark_errfp,"  %s\n\n",msg);
  }
#endif

  return;
}



/*===============================================================
  Private Helper Functions
  ===============================================================*/

/*---------------------------------------------------------------
  arkodeInit:
 
  arkodeInit allocates and initializes memory for a problem. All 
  inputs are checked for errors. If any error occurs during 
  initialization, it is reported to the file whose file pointer 
  is errfp and an error flag is returned. Otherwise, it returns 
  ARK_SUCCESS.  This routine should be called by an ARKode 
  timestepper module (not by the user).  This routine must be 
  called prior to calling ARKode to evolve the problem.
  ---------------------------------------------------------------*/
int arkodeInit(ARKodeMem ark_mem, realtype t0, N_Vector y0)
{
  booleantype stepperOK, nvectorOK, allocOK;
  sunindextype lrw1, liw1;
  
  /* Check for legal input parameters */
  if (y0==NULL) {
    arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", 
                    "arkodeInit", MSGARK_NULL_Y0);
    return(ARK_ILL_INPUT);
  }

  /* Test if all required time stepper operations are implemented */
  stepperOK = arkCheckTimestepper(ark_mem);
  if (!stepperOK) {
    arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", "arkodeInit",
                    "Time stepper module is missing required functionality");
    return(ARK_ILL_INPUT);
  }

  /* Test if all required vector operations are implemented */
  nvectorOK = arkCheckNvector(y0);
  if (!nvectorOK) {
    arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", 
                    "arkodeInit", MSGARK_BAD_NVECTOR);
    return(ARK_ILL_INPUT);
  }

  /* Set space requirements for one N_Vector */
  if (y0->ops->nvspace != NULL) {
    N_VSpace(y0, &lrw1, &liw1);
  } else {
    lrw1 = 0;
    liw1 = 0;
  }
  ark_mem->ark_lrw1 = lrw1;
  ark_mem->ark_liw1 = liw1;


  /* Allocate the solver vectors (using y0 as a template) */
  allocOK = arkAllocVectors(ark_mem, y0);
  if (!allocOK) {
    arkProcessError(ark_mem, ARK_MEM_FAIL, "ARKODE", 
                    "arkodeInit", MSGARK_MEM_FAIL);
    return(ARK_MEM_FAIL);
  }

  /* Initialize the interpolation structure to NULL */
  ark_mem->ark_interp = NULL;

  /* All error checking is complete at this point */

  /* Copy the input parameters into ARKODE state */
  ark_mem->ark_tn   = t0;
  ark_mem->ark_tnew = t0;

  /* Set step parameters */
  ark_mem->ark_hold     = ZERO;
  ark_mem->ark_tolsf    = ONE;
  ark_mem->ark_hmin     = ZERO;       /* no minimum step size */
  ark_mem->ark_hmax_inv = ZERO;       /* no maximum step size */

  /* Initialize ycur */
  N_VScale(ONE, y0, ark_mem->ark_ycur);

  /* Initialize all the counters */
  ark_mem->ark_nst   = 0;
  ark_mem->ark_nhnil = 0;

  /* Initialize other integrator optional outputs */
  ark_mem->ark_h0u    = ZERO;
  ark_mem->ark_next_h = ZERO;

  /* Initially, rwt should point to ewt */
  ark_mem->ark_rwt_is_ewt = SUNTRUE;

  /* Indicate that problem size is new */
  ark_mem->ark_resized = SUNTRUE;
  ark_mem->ark_firststage = SUNTRUE;

  /* Problem has been successfully initialized */
  ark_mem->ark_MallocDone = SUNTRUE;

  return(ARK_SUCCESS);
}


/*---------------------------------------------------------------
  arkodeReInit:

  arkodeReInit re-initializes ARKODE's memory for a problem, 
  assuming it has already been allocated in a prior arkodeInit 
  call.  All problem specification inputs are checked for errors.
  If any error occurs during initialization, it is reported to 
  the file whose file pointer is errfp.  This routine should only
  be called after arkodeInit, and only when the problem dynamics 
  or desired solvers have changed dramatically, so that the
  problem integration should resume as if started from scratch.

  The return value is ARK_SUCCESS = 0 if no errors occurred, or
  a negative value otherwise.
  ---------------------------------------------------------------*/
int arkodeReInit(ARKodeMem ark_mem, realtype t0, N_Vector y0)
{
  /* Check if ark_mem was allocated */
  if (ark_mem->ark_MallocDone == SUNFALSE) {
    arkProcessError(ark_mem, ARK_NO_MALLOC, "ARKODE", 
                    "arkodeReInit", MSGARK_NO_MALLOC);
    return(ARK_NO_MALLOC);
  }

  /* Check for legal input parameters */
  if (y0 == NULL) {
    arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", 
                    "arkodeReInit", MSGARK_NULL_Y0);
    return(ARK_ILL_INPUT);
  }
  
  /* Copy the input parameters into ARKODE state */
  ark_mem->ark_tn   = t0;
  ark_mem->ark_tnew = t0;
  
  /* Set step parameters */
  ark_mem->ark_hold     = ZERO;
  ark_mem->ark_tolsf    = ONE;
  ark_mem->ark_hmin     = ZERO;       /* no minimum step size */
  ark_mem->ark_hmax_inv = ZERO;       /* no maximum step size */

  /* Do not reset the linear solver addresses to NULL.  This means 
     that if the user does not re-set these manually, we'll re-use 
     the linear solver routines that were set during arkodeInit. */

  /* Initialize ycur */
  N_VScale(ONE, y0, ark_mem->ark_ycur);

  /* Initialize all the counters */
  ark_mem->ark_nst   = 0;
  ark_mem->ark_nhnil = 0;

  /* Indicate that problem size is new */
  ark_mem->ark_resized    = SUNTRUE;
  ark_mem->ark_firststage = SUNTRUE;

  /* Initialize other integrator optional outputs */
  ark_mem->ark_h0u    = ZERO;
  ark_mem->ark_next_h = ZERO;

  /* Problem has been successfully re-initialized */
  return(ARK_SUCCESS);
}


/*---------------------------------------------------------------
  arkPrintMem:

  This routine outputs the ark_mem structure to a specified file 
  pointer.
  ---------------------------------------------------------------*/
void arkPrintMem(ARKodeMem ark_mem, FILE *outfile)
{
  /* output general values */
  fprintf(outfile, "ark_itol = %i\n", ark_mem->ark_itol);
  fprintf(outfile, "ark_ritol = %i\n", ark_mem->ark_ritol);
  fprintf(outfile, "ark_dense_q = %i\n", ark_mem->ark_dense_q);
  fprintf(outfile, "ark_mxhnil = %i\n", ark_mem->ark_mxhnil);
  fprintf(outfile, "ark_mxstep = %li\n", ark_mem->ark_mxstep);
  fprintf(outfile, "ark_lrw1 = %li\n", (long int) ark_mem->ark_lrw1);
  fprintf(outfile, "ark_liw1 = %li\n", (long int) ark_mem->ark_liw1);
  fprintf(outfile, "ark_lrw = %li\n", (long int) ark_mem->ark_lrw);
  fprintf(outfile, "ark_liw = %li\n", (long int) ark_mem->ark_liw);
  fprintf(outfile, "ark_user_efun = %i\n", ark_mem->ark_user_efun);
  fprintf(outfile, "ark_tstopset = %i\n", ark_mem->ark_tstopset);
  fprintf(outfile, "ark_tstop = %" RSYM"\n", ark_mem->ark_tstop);
  fprintf(outfile, "ark_report = %i\n", ark_mem->ark_report);
  fprintf(outfile, "ark_VabstolMallocDone = %i\n", ark_mem->ark_VabstolMallocDone);
  fprintf(outfile, "ark_MallocDone = %i\n", ark_mem->ark_MallocDone);
  fprintf(outfile, "ark_resized = %i\n", ark_mem->ark_resized);
  fprintf(outfile, "ark_firststage = %i\n", ark_mem->ark_firststage);
  fprintf(outfile, "ark_uround = %" RSYM"\n", ark_mem->ark_uround);
  fprintf(outfile, "ark_reltol = %" RSYM"\n", ark_mem->ark_reltol);
  fprintf(outfile, "ark_Sabstol = %" RSYM"\n", ark_mem->ark_Sabstol);
  fprintf(outfile, "ark_fixedstep = %i\n", ark_mem->ark_fixedstep);
  fprintf(outfile, "ark_tolsf = %" RSYM"\n", ark_mem->ark_tolsf);

  /* output counters */
  fprintf(outfile, "ark_nhnil = %i\n", ark_mem->ark_nhnil);
  fprintf(outfile, "ark_nst = %li\n", ark_mem->ark_nst);
  
  /* output time-stepping values */
  fprintf(outfile, "ark_hin = %" RSYM"\n", ark_mem->ark_hin);
  fprintf(outfile, "ark_h = %" RSYM"\n", ark_mem->ark_h);
  fprintf(outfile, "ark_hprime = %" RSYM"\n", ark_mem->ark_hprime);
  fprintf(outfile, "ark_next_h = %" RSYM"\n", ark_mem->ark_next_h);
  fprintf(outfile, "ark_eta = %" RSYM"\n", ark_mem->ark_eta);
  fprintf(outfile, "ark_tn = %" RSYM"\n", ark_mem->ark_tn);
  fprintf(outfile, "ark_tretlast = %" RSYM"\n", ark_mem->ark_tretlast);
  fprintf(outfile, "ark_hmin = %" RSYM"\n", ark_mem->ark_hmin);
  fprintf(outfile, "ark_hmax_inv = %" RSYM"\n", ark_mem->ark_hmax_inv);
  fprintf(outfile, "ark_h0u = %" RSYM"\n", ark_mem->ark_h0u);
  fprintf(outfile, "ark_tnew = %" RSYM"\n", ark_mem->ark_tnew);
  fprintf(outfile, "ark_hold = %" RSYM"\n", ark_mem->ark_hold);
  
  /* output root-finding quantities */
  if (ark_mem->root_mem != NULL)
    (void) arkPrintRootMem((void*) ark_mem, outfile);

  /* output interpolation quantities */
  if (ark_mem->ark_interp != NULL)
    arkPrintInterpMem(ark_mem->ark_interp, outfile);

  /* output time step module quantities */
  if (ark_mem->ark_step_print != NULL)
    ark_mem->ark_step_print((void*) ark_mem, outfile);

#ifdef DEBUG_OUTPUT
  /* output vector quantities */  
  if (ark_mem->ark_Vabstol != NULL) {
    fprintf(outfile, "ark_Vapbsol:\n");
    N_VPrint_Serial(ark_mem->ark_Vabstol);
  }
  if (ark_mem->ark_ewt != NULL) {
    fprintf(outfile, "ark_ewt:\n");
    N_VPrint_Serial(ark_mem->ark_ewt);
  }
  if (!ark_mem->ark_rwt_is_ewt && ark_mem->ark_rwt != NULL) {
    fprintf(outfile, "ark_rwt:\n");
    N_VPrint_Serial(ark_mem->ark_rwt);
  }
  if (ark_mem->ark_y != NULL) {
    fprintf(outfile, "ark_y:\n");
    N_VPrint_Serial(ark_mem->ark_y);
  }
  if (ark_mem->ark_ycur != NULL) {
    fprintf(outfile, "ark_ycur:\n");
    N_VPrint_Serial(ark_mem->ark_ycur);
  }
  if (ark_mem->ark_tempv1 != NULL) {
    fprintf(outfile, "ark_tempv1:\n");
    N_VPrint_Serial(ark_mem->ark_tempv1);
  }
  if (ark_mem->ark_tempv2 != NULL) {
    fprintf(outfile, "ark_tempv2:\n");
    N_VPrint_Serial(ark_mem->ark_tempv2);
  }
#endif

}


/*---------------------------------------------------------------
  arkCheckTimestepper:

  This routine checks if all required time stepper function 
  pointers have been supplied.  If any of them is missing it 
  returns SUNFALSE.
  ---------------------------------------------------------------*/
booleantype arkCheckTimestepper(ARKodeMem ark_mem)
{
  if ( (ark_mem->ark_step_init == NULL) ||
       (ark_mem->ark_step      == NULL) ||
       (ark_mem->ark_step_free == NULL) ||
       (ark_mem->ark_step_mem  == NULL) )
    return(SUNFALSE);
  if ( (ark_mem->ark_interp != NULL) &&
       (ark_mem->ark_step_fullrhs == NULL) )
    return(SUNFALSE);
  return(SUNTRUE);
}


/*---------------------------------------------------------------
  arkCheckNvector:

  This routine checks if all required vector operations are 
  present.  If any of them is missing it returns SUNFALSE.
  ---------------------------------------------------------------*/
booleantype arkCheckNvector(N_Vector tmpl)  /* to be updated?? */
{
  if ((tmpl->ops->nvclone     == NULL) ||
      (tmpl->ops->nvdestroy   == NULL) ||
      (tmpl->ops->nvlinearsum == NULL) ||
      (tmpl->ops->nvconst     == NULL) ||
      (tmpl->ops->nvdiv       == NULL) ||
      (tmpl->ops->nvscale     == NULL) ||
      (tmpl->ops->nvabs       == NULL) ||
      (tmpl->ops->nvinv       == NULL) ||
      (tmpl->ops->nvaddconst  == NULL) ||
      (tmpl->ops->nvmaxnorm   == NULL) ||
      (tmpl->ops->nvwrmsnorm  == NULL) ||
      (tmpl->ops->nvmin       == NULL))
    return(SUNFALSE);
  else
    return(SUNTRUE);
}


/*---------------------------------------------------------------
  arkAllocVec:

  This routine allocates a single vector based on a template 
  vector.  If the target vector already exists it is left alone; 
  otherwise it is allocated by cloning the input vector. If the 
  allocation is successful (or if the target vector already 
  exists) then this returns SUNTRUE.  This routine also updates 
  the optional outputs lrw and liw, which are (respectively) the 
  lengths of the overall ARKode real and integer work spaces.
  ---------------------------------------------------------------*/
booleantype arkAllocVec(ARKodeMem ark_mem, 
                        N_Vector tmpl,
                        N_Vector *v)
{
  if (*v == NULL) {
    *v = N_VClone(tmpl);
    if (*v == NULL) {
      arkFreeVectors(ark_mem);
      return(SUNFALSE);
    } else {
      ark_mem->ark_lrw += ark_mem->ark_lrw1;
      ark_mem->ark_liw += ark_mem->ark_liw1;
    }
  }
  return (SUNTRUE);
}


/*---------------------------------------------------------------
  arkFreeVec:

  This routine frees a single vector.  If the target vector is
  already NULL it is left alone; otherwise it is freed and the
  optional outputs lrw and liw are updated accordingly.
  ---------------------------------------------------------------*/
void arkFreeVec(ARKodeMem ark_mem, N_Vector *v)
{
  if (*v != NULL) {
    N_VDestroy(*v);
    *v = NULL;
    ark_mem->ark_lrw -= ark_mem->ark_lrw1;
    ark_mem->ark_liw -= ark_mem->ark_liw1;
  }
}


/*---------------------------------------------------------------
  arkResizeVec:

  This routine resizes a single vector based on a template 
  vector.  If the ARKVecResizeFn function is non-NULL, then it 
  calls that routine to perform the single-vector resize; 
  otherwise it deallocates and reallocates the target vector based 
  on the template vector.  If the resize is successful then this 
  returns SUNTRUE.  This routine also updates the optional outputs 
  lrw and liw, which are (respectively) the lengths of the overall 
  ARKode real and integer work spaces.
  ---------------------------------------------------------------*/
int arkResizeVec(ARKodeMem ark_mem, ARKVecResizeFn resize,
                 void *resize_data, sunindextype lrw_diff,
                 sunindextype liw_diff, N_Vector tmpl, N_Vector *v)
{
  if (*v != NULL) {
    if (resize == NULL) {
      N_VDestroy(*v);
      *v = N_VClone(tmpl);
    } else {
      if (resize(*v, tmpl, resize_data)) {
        arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", 
                        "arkResizeVec", MSGARK_RESIZE_FAIL);
        return(ARK_ILL_INPUT);
      }
    }
    ark_mem->ark_lrw += lrw_diff;
    ark_mem->ark_liw += liw_diff;
  }
  return(ARK_SUCCESS);
}

/*---------------------------------------------------------------
  arkAllocVectors:

  This routine allocates the ARKODE vectors ewt, ycur, tempv1, 
  tempv2 and ftemp.  If any of 
  these vectors already exist, they are left alone.  Otherwise, it
  will allocate each vector by cloning the input vector. If all 
  memory allocations are successful, arkAllocVectors returns SUNTRUE. 
  Otherwise all vector memory is freed and arkAllocVectors 
  returns SUNFALSE. This routine also updates the optional outputs 
  lrw and liw, which are (respectively) the lengths of the real 
  and integer work spaces.
  ---------------------------------------------------------------*/
booleantype arkAllocVectors(ARKodeMem ark_mem, N_Vector tmpl)
{
  /* Allocate ewt if needed */
  if (!arkAllocVec(ark_mem, tmpl, &ark_mem->ark_ewt))
    return(SUNFALSE);

  /* Set rwt to point at ewt */
  if (ark_mem->ark_rwt_is_ewt) 
    ark_mem->ark_rwt = ark_mem->ark_ewt;

  /* Allocate ycur if needed */
  if (!arkAllocVec(ark_mem, tmpl, &ark_mem->ark_ycur))
    return(SUNFALSE);

  /* Allocate tempv1 if needed */
  if (!arkAllocVec(ark_mem, tmpl, &ark_mem->ark_tempv1))
    return(SUNFALSE);

  /* Allocate tempv2 if needed */
  if (!arkAllocVec(ark_mem, tmpl, &ark_mem->ark_tempv2))
    return(SUNFALSE);

  return(SUNTRUE);
}


/*---------------------------------------------------------------
  arkFreeVectors

  This routine frees the ARKODE vectors allocated in both
  arkAllocVectors and arkAllocRKVectors.
  ---------------------------------------------------------------*/
void arkFreeVectors(ARKodeMem ark_mem)
{
  arkFreeVec(ark_mem, &ark_mem->ark_ewt);
  if (!ark_mem->ark_rwt_is_ewt)
    arkFreeVec(ark_mem, &ark_mem->ark_rwt);
  arkFreeVec(ark_mem, &ark_mem->ark_tempv1);
  arkFreeVec(ark_mem, &ark_mem->ark_tempv2);
  arkFreeVec(ark_mem, &ark_mem->ark_ycur);
  arkFreeVec(ark_mem, &ark_mem->ark_Vabstol);
}


/*---------------------------------------------------------------
  arkAllocFPData

  This routine allocates all required memory for performing the
  accelerated fixed-point solver.
  ---------------------------------------------------------------*/
ARKodeFPMem arkAllocFPData(ARKodeMem ark_mem, long int maa)
{
  ARKodeFPMem fp_mem;

  /* ensure that DotProd function is defined */
  if (ark_mem->ark_ewt->ops->nvdotprod == NULL) {
    arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE",
                    "arkAllocFPData", MSGARK_BAD_NVECTOR);
    return(NULL);
  }

  /* Create FP solver structure */
  fp_mem = (ARKodeFPMem) malloc(sizeof(struct ARKodeFPMemRec));
  if (fp_mem == NULL) {
    arkProcessError(NULL, 0, "ARKODE", "arkAllocFPData",
                    MSGARK_ARKMEM_FAIL);
    return(NULL);
  }

  /* Zero out fp_mem */
  memset(fp_mem, 0, sizeof(struct ARKodeFPMemRec));

  /* set acceleration subspace size */
  fp_mem->m = maa;

  /* Allocate fval */
  if (!arkAllocVec(ark_mem, ark_mem->ark_ewt, &fp_mem->fval)) {
    arkFreeFPData(ark_mem, fp_mem);
    return(NULL);
  }

  /* Allocate fold */
  if (!arkAllocVec(ark_mem, ark_mem->ark_ewt, &fp_mem->fold)) {
    arkFreeFPData(ark_mem, fp_mem);
    return(NULL);
  }

  /* Allocate gold */
  if (!arkAllocVec(ark_mem, ark_mem->ark_ewt, &fp_mem->gold)) {
    arkFreeFPData(ark_mem, fp_mem);
    return(NULL);
  }
 
  /* Allocate df if needed */
  if (maa > 0) {
    fp_mem->df = N_VCloneVectorArray(maa, ark_mem->ark_ewt);
    if (fp_mem->df == NULL) {
      arkFreeFPData(ark_mem, fp_mem);
      return(NULL);
    }
    ark_mem->ark_lrw += maa*ark_mem->ark_lrw1;
    ark_mem->ark_liw += maa*ark_mem->ark_liw1;
  }

  /* Allocate dg if needed */
  if (maa > 0) {
    fp_mem->dg = N_VCloneVectorArray(maa, ark_mem->ark_ewt);
    if (fp_mem->dg == NULL) {
      arkFreeFPData(ark_mem, fp_mem);
      return(NULL);
    }
    ark_mem->ark_lrw += maa*ark_mem->ark_lrw1;
    ark_mem->ark_liw += maa*ark_mem->ark_liw1;
  }

  /* Allocate q if needed */
  if (maa > 0) {
    fp_mem->q = N_VCloneVectorArray(maa, ark_mem->ark_ewt);
    if (fp_mem->q == NULL) {
      arkFreeFPData(ark_mem, fp_mem);
      return(NULL);
    }
    ark_mem->ark_lrw += maa*ark_mem->ark_lrw1;
    ark_mem->ark_liw += maa*ark_mem->ark_liw1;
  }

  /* Allocate R if needed */
  if (maa > 0) {
    fp_mem->R = (realtype *) malloc((maa*maa) * sizeof(realtype));
    if (fp_mem->R == NULL) {
      arkFreeFPData(ark_mem, fp_mem);
      return(NULL);
    }
    ark_mem->ark_lrw += maa*maa;
  }

  /* Allocate gamma if needed */
  if (maa > 0) {
    fp_mem->gamma = (realtype *) malloc(maa * sizeof(realtype));
    if (fp_mem->gamma == NULL) {
      arkFreeFPData(ark_mem, fp_mem);
      return(NULL);
    }
    ark_mem->ark_lrw += maa;
  }

  /* Allocate imap if needed */
  if (maa > 0) {
    fp_mem->imap = (long int *) malloc(maa * sizeof(long int));
    if (fp_mem->imap == NULL) {
      arkFreeFPData(ark_mem, fp_mem);
      return(NULL);
    }
    ark_mem->ark_liw += maa;
  }

  return(fp_mem);
}

/*---------------------------------------------------------------
  arkResizeFPData

  This routine resizes all required memory for the accelerated
  fixed-point solver (called from ARKodeResize()).
  ---------------------------------------------------------------*/
int arkResizeFPData(ARKodeMem ark_mem, ARKodeFPMem fp_mem,
                    ARKVecResizeFn resize, void *resize_data, 
                    sunindextype lrw_diff, sunindextype liw_diff,
                    N_Vector tmpl)
{
  int ier, i;
  if (fp_mem == NULL) {
    arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", "arkResizeFPData", 
                    "Fixed point solver memory unallocated");
    return(ARK_ILL_INPUT);
  }
  
  /* Resize fval if needed */
  ier = arkResizeVec(ark_mem, resize, resize_data, lrw_diff,
                     liw_diff, tmpl, &fp_mem->fval);
  if (ier != ARK_SUCCESS)  return(ier);

  /* Resize fold if needed */
  ier = arkResizeVec(ark_mem, resize, resize_data, lrw_diff,
                     liw_diff, tmpl, &fp_mem->fold);
  if (ier != ARK_SUCCESS)  return(ier);

  /* Resize gold if needed */
  ier = arkResizeVec(ark_mem, resize, resize_data, lrw_diff,
                     liw_diff, tmpl, &fp_mem->gold);
  if (ier != ARK_SUCCESS)  return(ier);

  /* Resize df if needed */
  if ((fp_mem->df != NULL) && (fp_mem->m > 0)) {
    for (i=0; i<fp_mem->m; i++) {
      ier = arkResizeVec(ark_mem, resize, resize_data, lrw_diff,
                         liw_diff, tmpl, &fp_mem->df[i]);
      if (ier != ARK_SUCCESS)  return(ier);
    }
  }

  /* Resize dg if needed */
  if ((fp_mem->dg != NULL) && (fp_mem->m > 0)) {
    for (i=0; i<fp_mem->m; i++) {
      ier = arkResizeVec(ark_mem, resize, resize_data, lrw_diff,
                         liw_diff, tmpl, &fp_mem->dg[i]);
      if (ier != ARK_SUCCESS)  return(ier);
    }
  }

  /* Resize q if needed */
  if ((fp_mem->q != NULL) && (fp_mem->m > 0)) {
    for (i=0; i<fp_mem->m; i++) {
      ier = arkResizeVec(ark_mem, resize, resize_data, lrw_diff,
                         liw_diff, tmpl, &fp_mem->q[i]);
      if (ier != ARK_SUCCESS)  return(ier);
    }
  }

  return(ARK_SUCCESS);
}


/*---------------------------------------------------------------
  arkFreeFPData

  This routine frees all memory allocated by arkAllocFPData.
  ---------------------------------------------------------------*/
void arkFreeFPData(ARKodeMem ark_mem, ARKodeFPMem fp_mem)
{
  /* free fval if needed */
  arkFreeVec(ark_mem, &fp_mem->fval);

  /* free fold if needed */
  arkFreeVec(ark_mem, &fp_mem->fold);

  /* free gold if needed */
  arkFreeVec(ark_mem, &fp_mem->gold);

  /* free df if needed */
  if ((fp_mem->df != NULL) && (fp_mem->m>0)) {
    N_VDestroyVectorArray(fp_mem->df, fp_mem->m);
    fp_mem->df = NULL;
    ark_mem->ark_lrw -= fp_mem->m * ark_mem->ark_lrw1;
    ark_mem->ark_liw -= fp_mem->m * ark_mem->ark_liw1;
  }

  /* free dg if needed */
  if ((fp_mem->dg != NULL) && (fp_mem->m>0)) {
    N_VDestroyVectorArray(fp_mem->dg, fp_mem->m);
    fp_mem->dg = NULL;
    ark_mem->ark_lrw -= fp_mem->m * ark_mem->ark_lrw1;
    ark_mem->ark_liw -= fp_mem->m * ark_mem->ark_liw1;
  }

  /* free q if needed */
  if ((fp_mem->q != NULL) && (fp_mem->m>0)) {
    N_VDestroyVectorArray(fp_mem->q, fp_mem->m);
    fp_mem->q = NULL;
    ark_mem->ark_lrw -= fp_mem->m * ark_mem->ark_lrw1;
    ark_mem->ark_liw -= fp_mem->m * ark_mem->ark_liw1;
  }

  /* free R if needed */
  if (fp_mem->R != NULL) {
    free(fp_mem->R);
    fp_mem->R = NULL;
    ark_mem->ark_lrw -= fp_mem->m * fp_mem->m;
  }

  /* free gamma if needed */
  if (fp_mem->gamma != NULL) {
    free(fp_mem->gamma);
    fp_mem->gamma = NULL;
    ark_mem->ark_lrw -= fp_mem->m;
  }

  /* free imap if needed */
  if (fp_mem->imap != NULL) {
    free(fp_mem->imap);
    fp_mem->imap = NULL;
    ark_mem->ark_liw -= fp_mem->m;
  }

  /* free fp_mem structure */
  free(fp_mem);
}


/*---------------------------------------------------------------
  arkInitialSetup

  This routine performs all necessary items to prepare ARKode for 
  the first internal step, including:
  - checks for valid initial step input or estimates first step
  - input consistency checks 
  - checks the linear solver module (if applicable)
  - initializes linear solver (if applicable)
  ---------------------------------------------------------------*/
int arkInitialSetup(ARKodeMem ark_mem, realtype tout)
{
  int retval, hflag, istate, ier;
  realtype tout_hin, rh;

  /* Temporarily set ark_h */
  ark_mem->ark_h = SUNRabs(tout - ark_mem->ark_tn);
  if (ark_mem->ark_h == ZERO)  ark_mem->ark_h = ONE;

  /* Set up the time stepper module */
  if (ark_mem->ark_step_init == NULL) {
    arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE",
                    "arkInitialSetup", "Time stepper module is missing");
    return(ARK_ILL_INPUT);
  }
  retval = ark_mem->ark_step_init(ark_mem);
  if (retval != ARK_SUCCESS) {
    arkProcessError(ark_mem, retval, "ARKODE", "arkInitialSetup",
                    "Error in initialization of time stepper module");
    return(retval);
  }

  /* Check that user has supplied an initial step size if fixedstep mode is on */ 
  if ( (ark_mem->ark_fixedstep) && (ark_mem->ark_hin == ZERO) ) {
    arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", 
                    "arkInitialSetup",
                    "Fixed step mode enabled, but no step size set");
    return(ARK_ILL_INPUT);
  }

  /* Set data for efun (if left unspecified) */
  if (ark_mem->ark_user_efun) 
    ark_mem->ark_e_data = ark_mem->ark_user_data;
  else                        
    ark_mem->ark_e_data = ark_mem;

  /* Load initial error weights */
  ier = ark_mem->ark_efun(ark_mem->ark_ycur,
                          ark_mem->ark_ewt, 
                          ark_mem->ark_e_data);
  if (ier != 0) {
    if (ark_mem->ark_itol == ARK_WF) 
      arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", 
                      "arkInitialSetup", MSGARK_EWT_FAIL);
    else 
      arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", 
                      "arkInitialSetup", MSGARK_BAD_EWT);
    return(ARK_ILL_INPUT);
  }

  /* Set data for rfun (if left unspecified) */
  if (ark_mem->ark_user_rfun) 
    ark_mem->ark_r_data = ark_mem->ark_user_data;
  else                        
    ark_mem->ark_r_data = ark_mem;

  /* Load initial residual weights */
  if (ark_mem->ark_rwt_is_ewt) {      /* update pointer to ewt */
    ark_mem->ark_rwt = ark_mem->ark_ewt;
  } else { 
    ier = ark_mem->ark_rfun(ark_mem->ark_ycur,
                            ark_mem->ark_rwt, 
                            ark_mem->ark_r_data);
    if (ier != 0) {
      if (ark_mem->ark_itol == ARK_WF) 
        arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", 
                        "arkInitialSetup", MSGARK_RWT_FAIL);
      else 
        arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", 
                        "arkInitialSetup", MSGARK_BAD_RWT);
      return(ARK_ILL_INPUT);
    }
  }

  /* Allocate interpolation memory (if unallocated, and if needed) 
     UPDATE THIS BASED ON TSTOP MODE, ADD TEST TO CONDITIONALLY 
     ALLOCATE ON ANY ARKODE CALL WHERE TSTOP MODE IS NOT SET */
  if (ark_mem->ark_interp == NULL) {
    ark_mem->ark_interp = arkInterpCreate(ark_mem);
    if (ark_mem->ark_interp == NULL)
      return(ARK_MEM_FAIL);
  }
  
  /* Fill initial interpolation data (if needed) */
  if (ark_mem->ark_interp != NULL) {
    ier = arkInterpInit(ark_mem, ark_mem->ark_interp, ark_mem->ark_tn);
    if (ier != 0)  return(ier);
  }

  /* Test input tstop for legality. */
  if ( ark_mem->ark_tstopset ) {
    if ( (ark_mem->ark_tstop - ark_mem->ark_tn)*(tout - ark_mem->ark_tn) <= ZERO ) {
      arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", "arkInitialSetup", 
                      MSGARK_BAD_TSTOP, ark_mem->ark_tstop, ark_mem->ark_tn);
      return(ARK_ILL_INPUT);
    }
  }

  /* Check input h for validity */
  ark_mem->ark_h = ark_mem->ark_hin;
  if ( (ark_mem->ark_h != ZERO) && 
       ((tout-ark_mem->ark_tn)*ark_mem->ark_h < ZERO) ) {
    arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", "arkInitialSetup", 
                    MSGARK_BAD_H0);
    return(ARK_ILL_INPUT);
  }
  if ((ark_mem->ark_hin == ZERO) && (ark_mem->ark_fixedstep)) {
    arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", "arkInitialSetup", 
                    "nonzero step size must be supplied when using fixed-step mode");
    return(ARK_ILL_INPUT);
  }

  /* Estimate initial h if not set */
  if (ark_mem->ark_h == ZERO) {
    /* Again, temporarily set ark_h for estimating an optimal value */
    ark_mem->ark_h = SUNRabs(tout - ark_mem->ark_tn);
    if (ark_mem->ark_h == ZERO)  ark_mem->ark_h = ONE;
    /* Estimate the first step size */
    tout_hin = tout;
    if ( ark_mem->ark_tstopset && 
         (tout-ark_mem->ark_tn)*(tout-ark_mem->ark_tstop) > ZERO ) 
      tout_hin = ark_mem->ark_tstop; 
    hflag = arkHin(ark_mem, tout_hin);
    if (hflag != ARK_SUCCESS) {
      istate = arkHandleFailure(ark_mem, hflag);
      return(istate);
    }
  }

  /* Enforce step size bounds */
  rh = SUNRabs(ark_mem->ark_h)*ark_mem->ark_hmax_inv;
  if (rh > ONE) ark_mem->ark_h /= rh;
  if (SUNRabs(ark_mem->ark_h) < ark_mem->ark_hmin)
    ark_mem->ark_h *= ark_mem->ark_hmin/SUNRabs(ark_mem->ark_h);
  /* Check for approach to tstop */
  if (ark_mem->ark_tstopset) {
    if ( (ark_mem->ark_tn + ark_mem->ark_h - ark_mem->ark_tstop)*ark_mem->ark_h > ZERO ) {
      ark_mem->ark_h = (ark_mem->ark_tstop - ark_mem->ark_tn)*(ONE-FOUR*ark_mem->ark_uround);
    }
  }
  
  /* Set initial time step factors */
  ark_mem->ark_h0u    = ark_mem->ark_h;
  ark_mem->ark_hprime = ark_mem->ark_h;

  /* Check for zeros of root function g at and near t0. */
  if (ark_mem->root_mem != NULL) 
    if (ark_mem->root_mem->nrtfn > 0) {
      retval = arkRootCheck1((void*) ark_mem);
      
      if (retval == ARK_RTFUNC_FAIL) {
        arkProcessError(ark_mem, ARK_RTFUNC_FAIL, "ARKODE", "arkRootCheck1", 
                        MSGARK_RTFUNC_FAILED, ark_mem->ark_tn);
        return(ARK_RTFUNC_FAIL);
      }
    }
  
  return(ARK_SUCCESS);
}


/*---------------------------------------------------------------
  arkPostResizeSetup

  This routine performs all necessary items to prepare ARKode for 
  the first internal step after a resize() call, including:
  - re-initialize the linear solver
  - re-initialize the interpolation structure
  - check for approach to tstop
  - check for root near t0
  ---------------------------------------------------------------*/
int arkPostResizeSetup(ARKodeMem ark_mem)
{
  int retval, ier;

  /* Load updated error weights */
  ier = ark_mem->ark_efun(ark_mem->ark_ycur,
                          ark_mem->ark_ewt, 
                          ark_mem->ark_e_data);
  if (ier != 0) {
    if (ark_mem->ark_itol == ARK_WF) 
      arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", 
                      "arkPostResizeSetup", MSGARK_EWT_FAIL);
    else 
      arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", 
                      "arkPostResizeSetup", MSGARK_BAD_EWT);
    return(ARK_ILL_INPUT);
  }

  /* Load updated residual weights */
  if (!ark_mem->ark_rwt_is_ewt) {
    ier = ark_mem->ark_rfun(ark_mem->ark_ycur,
                            ark_mem->ark_rwt, 
                            ark_mem->ark_r_data);
    if (ier != 0) {
      if (ark_mem->ark_itol == ARK_WF) 
        arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", 
                        "arkPostResizeSetup", MSGARK_RWT_FAIL);
      else 
        arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", 
                        "arkPostResizeSetup", MSGARK_BAD_RWT);
      return(ARK_ILL_INPUT);
    }
  }

  /* Fill initial interpolation data (if needed) */
  if (ark_mem->ark_interp != NULL) {
    ier = arkInterpInit(ark_mem, ark_mem->ark_interp, ark_mem->ark_tn);
    if (ier != 0)  return(ier);
  }
  
  /* Check for legal tstop (correct direction of integration) */
  if (ark_mem->ark_tstopset) {
    if ( (ark_mem->ark_tstop - ark_mem->ark_tn)*ark_mem->ark_h < ZERO ) {
      arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", "arkPostResizeSetup", 
                      MSGARK_BAD_TSTOP, ark_mem->ark_tstop, ark_mem->ark_tn);
      return(ARK_ILL_INPUT);
    }
  }

  /* Check for zeros of root function g at and near t0. */
  if (ark_mem->root_mem != NULL) 
    if (ark_mem->root_mem->nrtfn > 0) {
      retval = arkRootCheck1((void*) ark_mem);
        
      if (retval == ARK_RTFUNC_FAIL) {
        arkProcessError(ark_mem, ARK_RTFUNC_FAIL, "ARKODE", "arkRootCheck1", 
                        MSGARK_RTFUNC_FAILED, ark_mem->ark_tn);
        return(ARK_RTFUNC_FAIL);
      }
    }

  return(ARK_SUCCESS);
}


/*---------------------------------------------------------------
  arkStopTests

  This routine performs relevant stopping tests:
  - check for root in last step
  - check if we passed tstop
  - check if we passed tout (NORMAL mode)
  - check if current tn was returned (ONE_STEP mode)
  - check if we are close to tstop
  (adjust step size if needed)
  ---------------------------------------------------------------*/
int arkStopTests(ARKodeMem ark_mem, realtype tout, N_Vector yout, 
                 realtype *tret, int itask, int *ier)
{
  int irfndp, retval;
  realtype troundoff;

  /* Estimate an infinitesimal time interval to be used as
     a roundoff for time quantities (based on current time 
     and step size) */
  troundoff = FUZZ_FACTOR*ark_mem->ark_uround *
    (SUNRabs(ark_mem->ark_tn) + SUNRabs(ark_mem->ark_h));

  /* First, check for a root in the last step taken, other than the
     last root found, if any.  If itask = ARK_ONE_STEP and y(tn) was not
     returned because of an intervening root, return y(tn) now.     */
  if (ark_mem->root_mem != NULL)
    if (ark_mem->root_mem->nrtfn > 0) {

      irfndp = ark_mem->root_mem->irfnd;
      
      retval = arkRootCheck2((void*) ark_mem);

      if (retval == CLOSERT) {
        arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", "arkRootCheck2", 
                        MSGARK_CLOSE_ROOTS, ark_mem->root_mem->tlo);
        *ier = ARK_ILL_INPUT;
        return(1);
      } else if (retval == ARK_RTFUNC_FAIL) {
        arkProcessError(ark_mem, ARK_RTFUNC_FAIL, "ARKODE", "arkRootCheck2", 
                        MSGARK_RTFUNC_FAILED, ark_mem->root_mem->tlo);
        *ier = ARK_RTFUNC_FAIL;
        return(1);
      } else if (retval == RTFOUND) {
        ark_mem->ark_tretlast = *tret = ark_mem->root_mem->tlo;
        *ier = ARK_ROOT_RETURN;
        return(1);
      }
        
      /* If tn is distinct from tretlast (within roundoff),
         check remaining interval for roots */
      if ( SUNRabs(ark_mem->ark_tn - ark_mem->ark_tretlast) > troundoff ) {
          
        retval = arkRootCheck3((void*) ark_mem);
          
        if (retval == ARK_SUCCESS) {     /* no root found */
          ark_mem->root_mem->irfnd = 0;
          if ((irfndp == 1) && (itask == ARK_ONE_STEP)) {
            ark_mem->ark_tretlast = *tret = ark_mem->ark_tn;
            N_VScale(ONE, ark_mem->ark_ycur, yout);
            *ier = ARK_SUCCESS;
            return(1);
          }
        } else if (retval == RTFOUND) {  /* a new root was found */
          ark_mem->root_mem->irfnd = 1;
          ark_mem->ark_tretlast = *tret = ark_mem->root_mem->tlo;
          *ier = ARK_ROOT_RETURN;
          return(1);
        } else if (retval == ARK_RTFUNC_FAIL) {  /* g failed */
          arkProcessError(ark_mem, ARK_RTFUNC_FAIL, "ARKODE", "arkRootCheck3", 
                          MSGARK_RTFUNC_FAILED, ark_mem->root_mem->tlo);
          *ier = ARK_RTFUNC_FAIL;
          return(1);
        }
      }
        
    } /* end of root stop check */
    
  /* In ARK_NORMAL mode, test if tout was reached */
  if ( (itask == ARK_NORMAL) && 
       ((ark_mem->ark_tn-tout)*ark_mem->ark_h >= ZERO) ) {
    ark_mem->ark_tretlast = *tret = tout;
    *ier = ARKodeGetDky(ark_mem, tout, 0, yout);
    if (*ier != ARK_SUCCESS) {
      arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", 
                      "ARKode", MSGARK_BAD_TOUT, tout);
      *ier = ARK_ILL_INPUT;
      return(1);
    }
    *ier = ARK_SUCCESS;
    return(1);
  }

  /* In ARK_ONE_STEP mode, test if tn was returned */
  if ( itask == ARK_ONE_STEP && 
       SUNRabs(ark_mem->ark_tn - ark_mem->ark_tretlast) > troundoff ) {
    ark_mem->ark_tretlast = *tret = ark_mem->ark_tn;
    N_VScale(ONE, ark_mem->ark_ycur, yout);
    *ier = ARK_SUCCESS;
    return(1);
  }

  /* Test for tn at tstop or near tstop */
  if ( ark_mem->ark_tstopset ) {

    if ( SUNRabs(ark_mem->ark_tn - ark_mem->ark_tstop) <= troundoff) {
      *ier = ARKodeGetDky(ark_mem, ark_mem->ark_tstop, 0, yout);
      if (*ier != ARK_SUCCESS) {
        arkProcessError(ark_mem, ARK_ILL_INPUT, "ARKODE", "ARKode", 
                        MSGARK_BAD_TSTOP, ark_mem->ark_tstop, ark_mem->ark_tn);
        *ier = ARK_ILL_INPUT;
        return(1);
      }
      ark_mem->ark_tretlast = *tret = ark_mem->ark_tstop;
      ark_mem->ark_tstopset = SUNFALSE;
      *ier = ARK_TSTOP_RETURN;
      return(1);
    }
      
    /* If next step would overtake tstop, adjust stepsize */
    if ( (ark_mem->ark_tn + ark_mem->ark_hprime - ark_mem->ark_tstop)*ark_mem->ark_h > ZERO ) {
      ark_mem->ark_hprime = (ark_mem->ark_tstop - ark_mem->ark_tn)*(ONE-FOUR*ark_mem->ark_uround);
      ark_mem->ark_eta = ark_mem->ark_hprime/ark_mem->ark_h;
    }
  }
   
  return(0);
}


/*---------------------------------------------------------------
  arkHin

  This routine computes a tentative initial step size h0. 
  If tout is too close to tn (= t0), then arkHin returns 
  ARK_TOO_CLOSE and h remains uninitialized. Note that here tout 
  is either the value passed to ARKode at the first call or the 
  value of tstop (if tstop is enabled and it is closer to t0=tn 
  than tout). If the RHS function fails unrecoverably, arkHin 
  returns ARK_RHSFUNC_FAIL. If the RHS function fails recoverably 
  too many times and recovery is not possible, arkHin returns 
  ARK_REPTD_RHSFUNC_ERR. Otherwise, arkHin sets h to the chosen 
  value h0 and returns ARK_SUCCESS.

  The algorithm used seeks to find h0 as a solution of
  (WRMS norm of (h0^2 ydd / 2)) = 1, 
  where ydd = estimated second derivative of y.  Although this 
  choice is based on an error expansion of the Backward Euler
  method, and hence results in an overly-conservative time step 
  for our higher-order ARK methods, it does find an order-of-
  magnitude estimate of the initial time scale of the solution.
  Since this method is only used on the first time step, the
  additional caution will not overly hinder solver efficiency.

  We start with an initial estimate equal to the geometric mean 
  of the lower and upper bounds on the step size.

  Loop up to H0_ITERS times to find h0.
  Stop if new and previous values differ by a factor < 2.
  Stop if hnew/hg > 2 after one iteration, as this probably 
  means that the ydd value is bad because of cancellation error.        
  
  For each new proposed hg, we allow H0_ITERS attempts to
  resolve a possible recoverable failure from f() by reducing
  the proposed stepsize by a factor of 0.2. If a legal stepsize
  still cannot be found, fall back on a previous value if 
  possible, or else return ARK_REPTD_RHSFUNC_ERR.

  Finally, we apply a bias (0.5) and verify that h0 is within 
  bounds.
  ---------------------------------------------------------------*/
int arkHin(ARKodeMem ark_mem, realtype tout)
{
  int retval, sign, count1, count2;
  realtype tdiff, tdist, tround, hlb, hub;
  realtype hg, hgs, hs, hnew, hrat, h0, yddnrm;
  booleantype hgOK, hnewOK;

  /* If tout is too close to tn, give up */
  if ((tdiff = tout-ark_mem->ark_tn) == ZERO) return(ARK_TOO_CLOSE);
  
  sign = (tdiff > ZERO) ? 1 : -1;
  tdist = SUNRabs(tdiff);
  tround = ark_mem->ark_uround * SUNMAX(SUNRabs(ark_mem->ark_tn), SUNRabs(tout));

  if (tdist < TWO*tround) return(ARK_TOO_CLOSE);
  
  /* Set lower and upper bounds on h0, and take geometric mean 
     as first trial value.
     Exit with this value if the bounds cross each other. */
  hlb = H0_LBFACTOR * tround;
  hub = arkUpperBoundH0(ark_mem, tdist);

  hg  = SUNRsqrt(hlb*hub);

  if (hub < hlb) {
    if (sign == -1) ark_mem->ark_h = -hg;
    else            ark_mem->ark_h =  hg;
    return(ARK_SUCCESS);
  }

  /* Outer loop */
  hnewOK = SUNFALSE;
  hs = hg;     /* safeguard against 'uninitialized variable' warning */
  for(count1 = 1; count1 <= H0_ITERS; count1++) {

    /* Attempts to estimate ydd */
    hgOK = SUNFALSE;

    for (count2 = 1; count2 <= H0_ITERS; count2++) {
      hgs = hg*sign;
      retval = arkYddNorm(ark_mem, hgs, &yddnrm);
      /* If f() failed unrecoverably, give up */
      if (retval < 0) return(ARK_RHSFUNC_FAIL);
      /* If successful, we can use ydd */
      if (retval == ARK_SUCCESS) {hgOK = SUNTRUE; break;}
      /* f() failed recoverably; cut step size and test it again */
      hg *= POINT2;
    }

    /* If f() failed recoverably H0_ITERS times */
    if (!hgOK) {
      /* Exit if this is the first or second pass. No recovery possible */
      if (count1 <= 2) return(ARK_REPTD_RHSFUNC_ERR);
      /* We have a fall-back option. The value hs is a previous hnew which
         passed through f(). Use it and break */
      hnew = hs;
      break;
    }

    /* The proposed step size is feasible. Save it. */
    hs = hg;

    /* If stopping criteria was met, or if this is the last pass, stop */
    if ( (hnewOK) || (count1 == H0_ITERS))  {hnew = hg; break;}

    /* Propose new step size */
    hnew = (yddnrm*hub*hub > TWO) ? SUNRsqrt(TWO/yddnrm) : SUNRsqrt(hg*hub);
    hrat = hnew/hg;
    
    /* Accept hnew if it does not differ from hg by more than a factor of 2 */
    if ((hrat > HALF) && (hrat < TWO))  hnewOK = SUNTRUE;

    /* After one pass, if ydd seems to be bad, use fall-back value. */
    if ((count1 > 1) && (hrat > TWO)) {
      hnew = hg;
      hnewOK = SUNTRUE;
    }

    /* Send this value back through f() */
    hg = hnew;
  }

  /* Apply bounds, bias factor, and attach sign */
  h0 = H0_BIAS*hnew;
  if (h0 < hlb) h0 = hlb;
  if (h0 > hub) h0 = hub;
  if (sign == -1) h0 = -h0;
  ark_mem->ark_h = h0;

  return(ARK_SUCCESS);
}


/*---------------------------------------------------------------
  arkUpperBoundH0

  This routine sets an upper bound on abs(h0) based on
  tdist = tn - t0 and the values of y[i]/y'[i].
  ---------------------------------------------------------------*/
realtype arkUpperBoundH0(ARKodeMem ark_mem, realtype tdist)
{
  realtype hub_inv, hub;
  N_Vector temp1, temp2;

  /* Bound based on |y0|/|y0'| -- allow at most an increase of
   * H0_UBFACTOR in y0 (based on a forward Euler step). The weight 
   * factor is used as a safeguard against zero components in y0. */
  temp1 = ark_mem->ark_tempv1;
  temp2 = ark_mem->ark_tempv2;

  N_VAbs(ark_mem->ark_ycur, temp2);
  ark_mem->ark_efun(ark_mem->ark_ycur, temp1, ark_mem->ark_e_data);
  N_VInv(temp1, temp1);
  N_VLinearSum(H0_UBFACTOR, temp2, ONE, temp1, temp1);

  N_VAbs(ark_mem->ark_interp->fnew, temp2);

  N_VDiv(temp2, temp1, temp1);
  hub_inv = N_VMaxNorm(temp1);

  /* bound based on tdist -- allow at most a step of magnitude
   * H0_UBFACTOR * tdist */
  hub = H0_UBFACTOR*tdist;

  /* Use the smaller of the two */
  if (hub*hub_inv > ONE) hub = ONE/hub_inv;

  return(hub);
}


/*---------------------------------------------------------------
  arkYddNorm

  This routine computes an estimate of the second derivative of y
  using a difference quotient, and returns its WRMS norm.
  ---------------------------------------------------------------*/
int arkYddNorm(ARKodeMem ark_mem, realtype hg, realtype *yddnrm)
{
  int retval;

  if (ark_mem->ark_interp == NULL) {
    arkProcessError(ark_mem, ARK_MEM_NULL, "ARKODE", "arkYddNorm",
                    "Missing interpolation structure");
    return(ARK_MEM_NULL);
  }
  
  /* increment y with a multiple of f */
  N_VLinearSum(hg, ark_mem->ark_interp->fnew, ONE, 
               ark_mem->ark_ycur, ark_mem->ark_y);

  /* compute y', via the ODE RHS routine */
  retval = ark_mem->ark_step_fullrhs(ark_mem, ark_mem->ark_tn+hg,
                                     ark_mem->ark_y,
                                     ark_mem->ark_tempv1, 2);
  if (retval != 0) return(ARK_RHSFUNC_FAIL);
  
  /* difference new f and original f to estimate y'' */
  N_VLinearSum(ONE, ark_mem->ark_tempv1, -ONE, 
               ark_mem->ark_interp->fnew, ark_mem->ark_tempv1);
  N_VScale(ONE/hg, ark_mem->ark_tempv1, ark_mem->ark_tempv1);

  /* compute norm of y'' */
  *yddnrm = N_VWrmsNorm(ark_mem->ark_tempv1, ark_mem->ark_ewt);

  return(ARK_SUCCESS);
}


/*---------------------------------------------------------------
  arkCompleteStep

  This routine performs various update operations when the step 
  solution is complete.  It is assumed that the timestepper 
  module has stored the time-evolved solution in ark_mem->ark_y, 
  and the step that gave rise to this solution in ark_mem->ark_h.
  We update the current time (tn), the current solution (ycur), 
  increment the overall step counter nst, record the values hold 
  and tnew, reset the resized flag, allow for user-provided 
  postprocessing, and update the interpolation structure.
  ---------------------------------------------------------------*/
int arkCompleteStep(ARKodeMem ark_mem)
{
  int retval;

  /* Set current time to the end of the step (in case the last 
     stage time does not coincide with the step solution time).  
     If tstop is enabled, it is possible for tn + h to be past 
     tstop by roundoff, and in that case, we reset tn (after 
     incrementing by h) to tstop. */
  ark_mem->ark_tn = ark_mem->ark_tnew + ark_mem->ark_h;
  if (ark_mem->ark_tstopset) {
    if ((ark_mem->ark_tn - ark_mem->ark_tstop)*ark_mem->ark_h > ZERO) 
      ark_mem->ark_tn = ark_mem->ark_tstop;
  }

  /* apply user-supplied step postprocessing function (if supplied) */ 
  if (ark_mem->ark_ProcessStep != NULL) {
    retval = ark_mem->ark_ProcessStep(ark_mem->ark_tn, 
                                      ark_mem->ark_y,
                                      ark_mem->ark_user_data);
    if (retval != 0) return(ARK_POSTPROCESS_FAIL);
  }

  /* update interpolation structure */
  if (ark_mem->ark_interp != NULL) {
    retval = arkInterpUpdate(ark_mem, ark_mem->ark_interp,
                             ark_mem->ark_tn,
                             (ark_mem->ark_ProcessStep != NULL));
    if (retval != ARK_SUCCESS)  return(retval);
  }
  
  /* update ycur to current solution */
  N_VScale(ONE, ark_mem->ark_y, ark_mem->ark_ycur);

  /* update scalar quantities */
  ark_mem->ark_nst++;
  ark_mem->ark_hold = ark_mem->ark_h;
  ark_mem->ark_tnew = ark_mem->ark_tn;

  /* turn off flag regarding resized problem */
  ark_mem->ark_resized = SUNFALSE;

  return(ARK_SUCCESS);
}


/*---------------------------------------------------------------
  arkHandleFailure

  This routine prints error messages for all cases of failure by
  arkHin and ark_step. It returns to ARKode the value that ARKode is 
  to return to the user.
  ---------------------------------------------------------------*/
int arkHandleFailure(ARKodeMem ark_mem, int flag)
{

  /* Depending on flag, print error message and return error flag */
  switch (flag) {
  case ARK_ERR_FAILURE: 
    arkProcessError(ark_mem, ARK_ERR_FAILURE, "ARKODE", "ARKode", 
                    MSGARK_ERR_FAILS, ark_mem->ark_tn, ark_mem->ark_h);
    break;
  case ARK_CONV_FAILURE:
    arkProcessError(ark_mem, ARK_CONV_FAILURE, "ARKODE", "ARKode", 
                    MSGARK_CONV_FAILS, ark_mem->ark_tn, ark_mem->ark_h);
    break;
  case ARK_LSETUP_FAIL:
    arkProcessError(ark_mem, ARK_LSETUP_FAIL, "ARKODE", "ARKode", 
                    MSGARK_SETUP_FAILED, ark_mem->ark_tn);
    break;
  case ARK_LSOLVE_FAIL:
    arkProcessError(ark_mem, ARK_LSOLVE_FAIL, "ARKODE", "ARKode", 
                    MSGARK_SOLVE_FAILED, ark_mem->ark_tn);
    break;
  case ARK_RHSFUNC_FAIL:
    arkProcessError(ark_mem, ARK_RHSFUNC_FAIL, "ARKODE", "ARKode", 
                    MSGARK_RHSFUNC_FAILED, ark_mem->ark_tn);
    break;
  case ARK_UNREC_RHSFUNC_ERR:
    arkProcessError(ark_mem, ARK_UNREC_RHSFUNC_ERR, "ARKODE", "ARKode", 
                    MSGARK_RHSFUNC_UNREC, ark_mem->ark_tn);
    break;
  case ARK_REPTD_RHSFUNC_ERR:
    arkProcessError(ark_mem, ARK_REPTD_RHSFUNC_ERR, "ARKODE", "ARKode", 
                    MSGARK_RHSFUNC_REPTD, ark_mem->ark_tn);
    break;
  case ARK_RTFUNC_FAIL:    
    arkProcessError(ark_mem, ARK_RTFUNC_FAIL, "ARKODE", "ARKode", 
                    MSGARK_RTFUNC_FAILED, ark_mem->ark_tn);
    break;
  case ARK_TOO_CLOSE:
    arkProcessError(ark_mem, ARK_TOO_CLOSE, "ARKODE", "ARKode", 
                    MSGARK_TOO_CLOSE);
    break;
  case ARK_MASSSOLVE_FAIL:
    arkProcessError(ark_mem, ARK_MASSSOLVE_FAIL, "ARKODE", "ARKode", 
                    MSGARK_MASSSOLVE_FAIL);
    break;
  default:
    return(ARK_SUCCESS);   
  }

  return(flag);
}


/*---------------------------------------------------------------
  arkEwtSetSS

  This routine sets ewt as decribed above in the case tol_type = ARK_SS.
  It tests for non-positive components before inverting. arkEwtSetSS
  returns 0 if ewt is successfully set to a positive vector
  and -1 otherwise. In the latter case, ewt is considered undefined.
  ---------------------------------------------------------------*/
int arkEwtSetSS(ARKodeMem ark_mem, N_Vector ycur, N_Vector weight)
{
  N_VAbs(ycur, ark_mem->ark_tempv1);
  N_VScale(ark_mem->ark_reltol, ark_mem->ark_tempv1, ark_mem->ark_tempv1);
  N_VAddConst(ark_mem->ark_tempv1, ark_mem->ark_Sabstol, ark_mem->ark_tempv1);
  if (N_VMin(ark_mem->ark_tempv1) <= ZERO) return(-1);
  N_VInv(ark_mem->ark_tempv1, weight);
  return(0);
}


/*---------------------------------------------------------------
  arkEwtSetSV

  This routine sets ewt as decribed above in the case tol_type = ARK_SV.
  It tests for non-positive components before inverting. arkEwtSetSV
  returns 0 if ewt is successfully set to a positive vector
  and -1 otherwise. In the latter case, ewt is considered undefined.
  ---------------------------------------------------------------*/
int arkEwtSetSV(ARKodeMem ark_mem, N_Vector ycur, N_Vector weight)
{
  N_VAbs(ycur, ark_mem->ark_tempv1);
  N_VLinearSum(ark_mem->ark_reltol, ark_mem->ark_tempv1, ONE, 
               ark_mem->ark_Vabstol, ark_mem->ark_tempv1);
  if (N_VMin(ark_mem->ark_tempv1) <= ZERO) return(-1);
  N_VInv(ark_mem->ark_tempv1, weight);
  return(0);
}


/*---------------------------------------------------------------
  arkRwtSetSS

  This routine sets rwt as decribed above in the case tol_type = ARK_SS.
  It tests for non-positive components before inverting. arkRwtSetSS
  returns 0 if rwt is successfully set to a positive vector
  and -1 otherwise. In the latter case, rwt is considered undefined.
  ---------------------------------------------------------------*/
int arkRwtSetSS(ARKodeMem ark_mem, N_Vector My, N_Vector weight)
{
  N_VAbs(My, ark_mem->ark_tempv1);
  N_VScale(ark_mem->ark_reltol, ark_mem->ark_tempv1, ark_mem->ark_tempv1);
  N_VAddConst(ark_mem->ark_tempv1, ark_mem->ark_SRabstol, ark_mem->ark_tempv1);
  if (N_VMin(ark_mem->ark_tempv1) <= ZERO) return(-1);
  N_VInv(ark_mem->ark_tempv1, weight);
  return(0);
}


/*---------------------------------------------------------------
  arkRwtSetSV

  This routine sets rwt as decribed above in the case tol_type = ARK_SV.
  It tests for non-positive components before inverting. arkRwtSetSV
  returns 0 if rwt is successfully set to a positive vector
  and -1 otherwise. In the latter case, rwt is considered undefined.
  ---------------------------------------------------------------*/
int arkRwtSetSV(ARKodeMem ark_mem, N_Vector My, N_Vector weight)
{
  N_VAbs(My, ark_mem->ark_tempv1);
  N_VLinearSum(ark_mem->ark_reltol, ark_mem->ark_tempv1, ONE, 
               ark_mem->ark_VRabstol, ark_mem->ark_tempv1);
  if (N_VMin(ark_mem->ark_tempv1) <= ZERO) return(-1);
  N_VInv(ark_mem->ark_tempv1, weight);
  return(0);
}


/*---------------------------------------------------------------
  arkExpStab is the default explicit stability estimation function
  ---------------------------------------------------------------*/
int arkExpStab(N_Vector y, realtype t, realtype *hstab, void *data)
{
  /* explicit stability not used by default, 
     set to zero to disable */
  *hstab = RCONST(0.0);

  return(ARK_SUCCESS);
}


/*---------------------------------------------------------------
  arkProcessError is a high level error handling function
  - if ark_mem==NULL it prints the error message to stderr
  - otherwise, it sets-up and calls the error handling function 
    pointed to by ark_ehfun 
  ---------------------------------------------------------------*/
void arkProcessError(ARKodeMem ark_mem, int error_code, 
                     const char *module, const char *fname, 
                     const char *msgfmt, ...)
{
  va_list ap;
  char msg[256];

  /* Initialize the argument pointer variable 
     (msgfmt is the last required argument to arkProcessError) */
  va_start(ap, msgfmt);

  /* Compose the message */
  vsprintf(msg, msgfmt, ap);

  if (ark_mem == NULL) {    /* We write to stderr */

#ifndef NO_FPRINTF_OUTPUT
    fprintf(stderr, "\n[%s ERROR]  %s\n  ", module, fname);
    fprintf(stderr, "%s\n\n", msg);
#endif

  } else {                 /* We can call ehfun */
    ark_mem->ark_ehfun(error_code, module, fname, msg, 
                       ark_mem->ark_eh_data);
  }

  /* Finalize argument processing */
  va_end(ap);

  return;
}


/*===============================================================
  EOF
  ===============================================================*/
