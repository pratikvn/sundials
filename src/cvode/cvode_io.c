/* -----------------------------------------------------------------
 * Programmer(s): Alan C. Hindmarsh and Radu Serban @ LLNL
 * -----------------------------------------------------------------
 * SUNDIALS Copyright Start
 * Copyright (c) 2002-2023, Lawrence Livermore National Security
 * and Southern Methodist University.
 * All rights reserved.
 *
 * See the top-level LICENSE and NOTICE files for details.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * SUNDIALS Copyright End
 * -----------------------------------------------------------------
 * This is the implementation file for the optional input and output
 * functions for the CVODE solver.
 * -----------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#include "cvode_impl.h"
#include "cvode_ls_impl.h"
#include "sundials/sundials_types.h"

#define ZERO   RCONST(0.0)
#define HALF   RCONST(0.5)
#define ONE    RCONST(1.0)
#define TWOPT5 RCONST(2.5)

/*
 * =================================================================
 * CVODE optional input functions
 * =================================================================
 */


/*
 * CVodeSetDeltaGammaMaxLSetup
 *
 * Specifies the gamma ratio threshold to signal for a linear solver setup
 */

int CVodeSetDeltaGammaMaxLSetup(void *cvode_mem, realtype dgmax_lsetup)
{
  CVodeMem cv_mem;

  if (cvode_mem == NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__,
                   MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  /* Set value or use default */
  if(dgmax_lsetup < ZERO)
    cv_mem->cv_dgmax_lsetup = DGMAX_LSETUP_DEFAULT;
  else
    cv_mem->cv_dgmax_lsetup = dgmax_lsetup;

  return(CV_SUCCESS);
}

/*
 * CVodeSetErrHandlerFn
 *
 * Specifies the error handler function
 */

int CVodeSetErrHandlerFn(void *cvode_mem, CVErrHandlerFn ehfun, void *eh_data)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  cv_mem->cv_ehfun = ehfun;
  cv_mem->cv_eh_data = eh_data;

  return(CV_SUCCESS);
}

/*
 * CVodeSetErrFile
 *
 * Specifies the FILE pointer for output (NULL means no messages)
 */

int CVodeSetErrFile(void *cvode_mem, FILE *errfp)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  cv_mem->cv_errfp = errfp;

  return(CV_SUCCESS);
}

/*
 * CVodeSetUserData
 *
 * Specifies the user data pointer for f
 */

int CVodeSetUserData(void *cvode_mem, void *user_data)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  cv_mem->cv_user_data = user_data;

  return(CV_SUCCESS);
}

/*
 * CVodeSetMonitorFn
 *
 * Specifies the user function to call for monitoring
 * the solution and/or integrator statistics.
 */

int CVodeSetMonitorFn(void *cvode_mem, CVMonitorFn fn)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

#ifdef SUNDIALS_BUILD_WITH_MONITORING
  cv_mem->cv_monitorfun = fn;
  return(CV_SUCCESS);
#else
  cvProcessError(cv_mem, CV_ILL_INPUT, __LINE__, __func__, __FILE__, "SUNDIALS was not built with monitoring enabled.");
  return(CV_ILL_INPUT);
#endif
}

/*
 * CVodeSetMonitorFrequency
 *
 * Specifies the frequency with which to call the user function.
 */

int CVodeSetMonitorFrequency(void *cvode_mem, long int nst)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  if (nst < 0) {
    cvProcessError(NULL, CV_ILL_INPUT, __LINE__, __func__, __FILE__, "step interval must be >= 0\n");
    return(CV_ILL_INPUT);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

#ifdef SUNDIALS_BUILD_WITH_MONITORING
  cv_mem->cv_monitor_interval = nst;
  return(CV_SUCCESS);
#else
  cvProcessError(cv_mem, CV_ILL_INPUT, __LINE__, __func__, __FILE__, "SUNDIALS was not built with monitoring enabled.");
  return(CV_ILL_INPUT);
#endif
}

/*
 * CVodeSetMaxOrd
 *
 * Specifies the maximum method order
 */

int CVodeSetMaxOrd(void *cvode_mem, int maxord)
{
  CVodeMem cv_mem;
  int qmax_alloc;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  if (maxord <= 0) {
    cvProcessError(cv_mem, CV_ILL_INPUT, __LINE__, __func__, __FILE__, MSGCV_NEG_MAXORD);
    return(CV_ILL_INPUT);
  }

  /* Cannot increase maximum order beyond the value that
     was used when allocating memory */
  qmax_alloc = cv_mem->cv_qmax_alloc;

  if (maxord > qmax_alloc) {
    cvProcessError(cv_mem, CV_ILL_INPUT, __LINE__, __func__, __FILE__, MSGCV_BAD_MAXORD);
    return(CV_ILL_INPUT);
  }

  cv_mem->cv_qmax = maxord;

  return(CV_SUCCESS);
}

/*
 * CVodeSetMaxNumSteps
 *
 * Specifies the maximum number of integration steps
 */

int CVodeSetMaxNumSteps(void *cvode_mem, long int mxsteps)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  /* Passing mxsteps=0 sets the default. Passing mxsteps<0 disables the test. */
  if (mxsteps == 0)
    cv_mem->cv_mxstep = MXSTEP_DEFAULT;
  else
    cv_mem->cv_mxstep = mxsteps;

  return(CV_SUCCESS);
}

/*
 * CVodeSetMaxHnilWarns
 *
 * Specifies the maximum number of warnings for small h
 */

int CVodeSetMaxHnilWarns(void *cvode_mem, int mxhnil)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  cv_mem->cv_mxhnil = mxhnil;

  return(CV_SUCCESS);
}

/*
 *CVodeSetStabLimDet
 *
 * Turns on/off the stability limit detection algorithm
 */

int CVodeSetStabLimDet(void *cvode_mem, booleantype sldet)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  if( sldet && (cv_mem->cv_lmm != CV_BDF) ) {
    cvProcessError(cv_mem, CV_ILL_INPUT, __LINE__, __func__, __FILE__, MSGCV_SET_SLDET);
    return(CV_ILL_INPUT);
  }

  cv_mem->cv_sldeton = sldet;

  return(CV_SUCCESS);
}

/*
 * CVodeSetInitStep
 *
 * Specifies the initial step size
 */

int CVodeSetInitStep(void *cvode_mem, realtype hin)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  cv_mem->cv_hin = hin;

  return(CV_SUCCESS);
}

/*
 * CVodeSetMinStep
 *
 * Specifies the minimum step size
 */

int CVodeSetMinStep(void *cvode_mem, realtype hmin)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  if (hmin < ZERO) {
    cvProcessError(cv_mem, CV_ILL_INPUT, __LINE__, __func__, __FILE__, MSGCV_NEG_HMIN);
    return(CV_ILL_INPUT);
  }

  /* Passing 0 sets hmin = zero */
  if (hmin == ZERO) {
    cv_mem->cv_hmin = HMIN_DEFAULT;
    return(CV_SUCCESS);
  }

  if (hmin * cv_mem->cv_hmax_inv > ONE) {
    cvProcessError(cv_mem, CV_ILL_INPUT, __LINE__, __func__, __FILE__, MSGCV_BAD_HMIN_HMAX);
    return(CV_ILL_INPUT);
  }

  cv_mem->cv_hmin = hmin;

  return(CV_SUCCESS);
}

/*
 * CVodeSetMaxStep
 *
 * Specifies the maximum step size
 */

int CVodeSetMaxStep(void *cvode_mem, realtype hmax)
{
  realtype hmax_inv;
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return (CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  if (hmax < ZERO) {
    cvProcessError(cv_mem, CV_ILL_INPUT, __LINE__, __func__, __FILE__, MSGCV_NEG_HMAX);
    return(CV_ILL_INPUT);
  }

  /* Passing 0 sets hmax = infinity */
  if (hmax == ZERO) {
    cv_mem->cv_hmax_inv = HMAX_INV_DEFAULT;
    return(CV_SUCCESS);
  }

  hmax_inv = ONE/hmax;
  if (hmax_inv * cv_mem->cv_hmin > ONE) {
    cvProcessError(cv_mem, CV_ILL_INPUT, __LINE__, __func__, __FILE__, MSGCV_BAD_HMIN_HMAX);
    return(CV_ILL_INPUT);
  }

  cv_mem->cv_hmax_inv = hmax_inv;

  return(CV_SUCCESS);
}

/*
 * CVodeSetEtaFixedStepBounds
 *
 * Specifies the bounds for retaining the current step size
 */


int CVodeSetEtaFixedStepBounds(void* cvode_mem, realtype eta_min_fx,
                               realtype eta_max_fx)
{
  CVodeMem cv_mem;

  if (cvode_mem == NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__,
                   MSGCV_NO_MEM);
    return (CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  /* set allowed value or use default */
  if (eta_min_fx < ZERO || eta_min_fx >= ONE)
    cv_mem->cv_eta_min_fx = ETA_MIN_FX_DEFAULT;
  else
    cv_mem->cv_eta_min_fx = eta_min_fx;

  if (eta_max_fx <= ONE)
    cv_mem->cv_eta_max_fx = ETA_MAX_FX_DEFAULT;
  else
    cv_mem->cv_eta_max_fx = eta_max_fx;

  return(CV_SUCCESS);
}

/*
 * CVodeSetEtaMaxFirstStep
 *
 * Specifies the maximum step size change on the first step
 */

int CVodeSetEtaMaxFirstStep(void* cvode_mem, realtype eta_max_fs)
{
  CVodeMem cv_mem;

  if (cvode_mem == NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__,
                   MSGCV_NO_MEM);
    return (CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  /* set allowed value or use default */
  if (eta_max_fs <= ONE)
    cv_mem->cv_eta_max_fs = ETA_MAX_FS_DEFAULT;
  else
    cv_mem->cv_eta_max_fs = eta_max_fs;

  return(CV_SUCCESS);
}

/*
 * CVodeSetEtaMaxEarlyStep
 *
 * Specifies the maximum step size change on steps early in the integration
 * when nst <= small_nst
 */

int CVodeSetEtaMaxEarlyStep(void* cvode_mem, realtype eta_max_es)
{
  CVodeMem cv_mem;

  if (cvode_mem == NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__,
                   MSGCV_NO_MEM);
    return (CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  /* set allowed value or use default */
  if (eta_max_es <= ONE)
    cv_mem->cv_eta_max_es = ETA_MAX_ES_DEFAULT;
  else
    cv_mem->cv_eta_max_es = eta_max_es;

  return(CV_SUCCESS);
}

/*
 * CVodeSetNumStepsEtaMaxEarlyStep
 *
 * Specifies the maximum number of steps for using the early integration change
 * factor
 */

int CVodeSetNumStepsEtaMaxEarlyStep(void* cvode_mem, long int small_nst)
{
  CVodeMem cv_mem;

  if (cvode_mem == NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__,
                   MSGCV_NO_MEM);
    return (CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  /* set allowed value or use default */
  if (small_nst < 0)
    cv_mem->cv_small_nst = SMALL_NST_DEFAULT;
  else
    cv_mem->cv_small_nst = small_nst;

  return(CV_SUCCESS);
}

/*
 * CVodeSetEtaMax
 *
 * Specifies the maximum step size change on a general steps (nst > small_nst)
 */

int CVodeSetEtaMax(void* cvode_mem, realtype eta_max_gs)
{
  CVodeMem cv_mem;

  if (cvode_mem == NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__,
                   MSGCV_NO_MEM);
    return (CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  /* set allowed value or use default */
  if (eta_max_gs <= ONE)
    cv_mem->cv_eta_max_gs = ETA_MAX_GS_DEFAULT;
  else
    cv_mem->cv_eta_max_gs = eta_max_gs;

  return(CV_SUCCESS);
}

/*
 * CVodeSetEtaMin
 *
 * Specifies the minimum change on a general steps
 */

int CVodeSetEtaMin(void* cvode_mem, realtype eta_min)
{
  CVodeMem cv_mem;

  if (cvode_mem == NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__,
                   MSGCV_NO_MEM);
    return (CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  /* set allowed value or use default */
  if (eta_min <= ZERO || eta_min >= ONE)
    cv_mem->cv_eta_min = ETA_MIN_DEFAULT;
  else
    cv_mem->cv_eta_min = eta_min;

  return(CV_SUCCESS);
}

/*
 * CVodeSetEtaMinErrFail
 *
 * Specifies the minimum step size change after an error test failure
 */

int CVodeSetEtaMinErrFail(void* cvode_mem, realtype eta_min_ef)
{
  CVodeMem cv_mem;

  if (cvode_mem == NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__,
                   MSGCV_NO_MEM);
    return (CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  /* set allowed value or use default */
  if (eta_min_ef <= ZERO || eta_min_ef >= ONE)
    cv_mem->cv_eta_min_ef = ETA_MIN_EF_DEFAULT;
  else
    cv_mem->cv_eta_min_ef = eta_min_ef;

  return(CV_SUCCESS);
}

/*
 * CVodeSetEtaMaxErrFail
 *
 * Specifies the maximum step size change after multiple (>= small_nef) error
 * test failures
 */

int CVodeSetEtaMaxErrFail(void* cvode_mem, realtype eta_max_ef)
{
  CVodeMem cv_mem;

  if (cvode_mem == NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__,
                   MSGCV_NO_MEM);
    return (CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  /* set allowed value or use default */
  if (eta_max_ef <= ZERO || eta_max_ef >= ONE)
    cv_mem->cv_eta_max_ef = ETA_MAX_EF_DEFAULT;
  else
    cv_mem->cv_eta_max_ef = eta_max_ef;

  return(CV_SUCCESS);
}

/*
 * CVodeSetNumFailsEtaMaxErrFail
 *
 * Specifies the maximum number of error test failures necessary to enforce
 * eta_max_ef
 */

int CVodeSetNumFailsEtaMaxErrFail(void* cvode_mem, int small_nef)
{
  CVodeMem cv_mem;

  if (cvode_mem == NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__,
                   MSGCV_NO_MEM);
    return (CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  /* set allowed value or use default */
  if (small_nef < 0)
    cv_mem->cv_small_nef = SMALL_NEF_DEFAULT;
  else
    cv_mem->cv_small_nef = small_nef;

  return(CV_SUCCESS);
}

/*
 * CVodeSetEtaConvFail
 *
 * Specifies the step size change after a nonlinear solver failure
 */

int CVodeSetEtaConvFail(void* cvode_mem, realtype eta_cf)
{
  CVodeMem cv_mem;

  if (cvode_mem == NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__,
                   MSGCV_NO_MEM);
    return (CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  /* set allowed value or use default */
  if (eta_cf <= ZERO || eta_cf >= ONE)
    cv_mem->cv_eta_cf = ETA_CF_DEFAULT;
  else
    cv_mem->cv_eta_cf = eta_cf;

  return(CV_SUCCESS);
}

/*
 * CVodeSetStopTime
 *
 * Specifies the time beyond which the integration is not to proceed.
 */

int CVodeSetStopTime(void *cvode_mem, realtype tstop)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return (CV_MEM_NULL);
  }
  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  /* If CVode was called at least once, test if tstop is legal
   * (i.e. if it was not already passed).
   * If CVodeSetStopTime is called before the first call to CVode,
   * tstop will be checked in CVode. */
  if (cv_mem->cv_nst > 0) {

    if ( (tstop - cv_mem->cv_tn) * cv_mem->cv_h < ZERO ) {
      cvProcessError(cv_mem, CV_ILL_INPUT, __LINE__, __func__, __FILE__, MSGCV_BAD_TSTOP, tstop, cv_mem->cv_tn);
      return(CV_ILL_INPUT);
    }

  }

  cv_mem->cv_tstop = tstop;
  cv_mem->cv_tstopset = SUNTRUE;

  return(CV_SUCCESS);
}

/*
 * CVodeClearStopTime
 *
 * Disable the stop time.
 */

int CVodeClearStopTime(void *cvode_mem)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, "CVODE", "CVodeClearStopTime", MSGCV_NO_MEM);
    return (CV_MEM_NULL);
  }
  cv_mem = (CVodeMem) cvode_mem;

  cv_mem->cv_tstopset = SUNFALSE;

  return(CV_SUCCESS);
}

/*
 * CVodeSetMaxErrTestFails
 *
 * Specifies the maximum number of error test failures during one
 * step try.
 */

int CVodeSetMaxErrTestFails(void *cvode_mem, int maxnef)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return (CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  cv_mem->cv_maxnef = maxnef;

  return(CV_SUCCESS);
}

/*
 * CVodeSetMaxConvFails
 *
 * Specifies the maximum number of nonlinear convergence failures
 * during one step try.
 */

int CVodeSetMaxConvFails(void *cvode_mem, int maxncf)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return (CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  cv_mem->cv_maxncf = maxncf;

  return(CV_SUCCESS);
}

/*
 * CVodeSetMaxNonlinIters
 *
 * Specifies the maximum number of nonlinear iterations during
 * one solve.
 */

int CVodeSetMaxNonlinIters(void *cvode_mem, int maxcor)
{
  int retval;
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return (CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  if (cv_mem->NLS == NULL) {
    cvProcessError(NULL, CV_MEM_FAIL, __LINE__, __func__, __FILE__, MSGCV_MEM_FAIL);
    return (CV_MEM_FAIL);
  }

  retval = SUNNonlinSolSetMaxIters(cv_mem->NLS, maxcor);
  SUNCheckCallNoRet(retval);
  return(retval);
}

/*
 * CVodeSetNonlinConvCoef
 *
 * Specifies the coeficient in the nonlinear solver convergence
 * test
 */

int CVodeSetNonlinConvCoef(void *cvode_mem, realtype nlscoef)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  cv_mem->cv_nlscoef = nlscoef;

  return(CV_SUCCESS);
}

/*
 * CVodeSetLSetupFrequency
 *
 * Specifies the frequency for calling the linear solver setup function to
 * recompute the Jacobian matrix and/or preconditioner
 */

int CVodeSetLSetupFrequency(void *cvode_mem, long int msbp)
{
  CVodeMem cv_mem;

  if (cvode_mem == NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__,
                   MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  /* check for a valid input */
  if (msbp < 0) {
    cvProcessError(cv_mem, CV_ILL_INPUT, __LINE__, __func__, __FILE__,
                   "A negative setup frequency was provided");
    return(CV_ILL_INPUT);
  }

  /* use default or user provided value */
  cv_mem->cv_msbp = (msbp == 0) ? MSBP_DEFAULT : msbp;

  return(CV_SUCCESS);
}

/*
 * CVodeSetRootDirection
 *
 * Specifies the direction of zero-crossings to be monitored.
 * The default is to monitor both crossings.
 */

int CVodeSetRootDirection(void *cvode_mem, int *rootdir)
{
  CVodeMem cv_mem;
  int i, nrt;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  nrt = cv_mem->cv_nrtfn;
  if (nrt==0) {
    cvProcessError(NULL, CV_ILL_INPUT, __LINE__, __func__, __FILE__, MSGCV_NO_ROOT);
    return(CV_ILL_INPUT);
  }

  for(i=0; i<nrt; i++) cv_mem->cv_rootdir[i] = rootdir[i];

  return(CV_SUCCESS);
}

/*
 * CVodeSetNoInactiveRootWarn
 *
 * Disables issuing a warning if some root function appears
 * to be identically zero at the beginning of the integration
 */

int CVodeSetNoInactiveRootWarn(void *cvode_mem)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  cv_mem->cv_mxgnull = 0;

  return(CV_SUCCESS);
}

/*
 * CVodeSetConstraints
 *
 * Setup for constraint handling feature
 */

int CVodeSetConstraints(void *cvode_mem, N_Vector constraints)
{
  CVodeMem cv_mem;
  realtype temptest;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  /* If there are no constraints, destroy data structures */
  if (constraints == NULL) {
    if (cv_mem->cv_constraintsMallocDone) {
      SUNCheckCallLastErrNoRet(N_VDestroy(cv_mem->cv_constraints));      cv_mem->cv_lrw -= cv_mem->cv_lrw1;
      cv_mem->cv_liw -= cv_mem->cv_liw1;
    }
    cv_mem->cv_constraintsMallocDone = SUNFALSE;
    cv_mem->cv_constraintsSet = SUNFALSE;
    return(CV_SUCCESS);
  }

  /* Test if required vector ops. are defined */

  if (constraints->ops->nvdiv         == NULL ||
      constraints->ops->nvmaxnorm     == NULL ||
      constraints->ops->nvcompare     == NULL ||
      constraints->ops->nvconstrmask  == NULL ||
      constraints->ops->nvminquotient == NULL) {
    cvProcessError(cv_mem, CV_ILL_INPUT, __LINE__, __func__, __FILE__, MSGCV_BAD_NVECTOR);
    return(CV_ILL_INPUT);
  }

  /* Check the constraints vector */
  temptest = SUNCheckCallLastErrNoRet(N_VMaxNorm(constraints));  if ((temptest > TWOPT5) || (temptest < HALF)) {
    cvProcessError(cv_mem, CV_ILL_INPUT, __LINE__, __func__, __FILE__, MSGCV_BAD_CONSTR);
    return(CV_ILL_INPUT);
  }

  if ( !(cv_mem->cv_constraintsMallocDone) ) {
    cv_mem->cv_constraints = SUNCheckCallLastErrNoRet(N_VClone(constraints));    cv_mem->cv_lrw += cv_mem->cv_lrw1;
    cv_mem->cv_liw += cv_mem->cv_liw1;
    cv_mem->cv_constraintsMallocDone = SUNTRUE;
  }

  /* Load the constraints vector */
  SUNCheckCallLastErrNoRet(N_VScale(ONE, constraints, cv_mem->cv_constraints));
  cv_mem->cv_constraintsSet = SUNTRUE;

  return(CV_SUCCESS);
}

/*
 * CVodeSetUseIntegratorFusedKernels
 *
 * Enable or disable integrator specific fused kernels
 */

int CVodeSetUseIntegratorFusedKernels(void *cvode_mem, booleantype onoff)
{
  CVodeMem cv_mem;
#ifdef SUNDIALS_BUILD_PACKAGE_FUSED_KERNELS
  N_Vector_ID id;
#endif

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

#ifdef SUNDIALS_BUILD_PACKAGE_FUSED_KERNELS
  id = N_VGetVectorID(cv_mem->cv_ewt);
  if (!cv_mem->cv_MallocDone ||
      (id != SUNDIALS_NVEC_CUDA && id != SUNDIALS_NVEC_HIP)) {
    cvProcessError(cv_mem, CV_ILL_INPUT, __LINE__, __func__, __FILE__,
                   "Fused Kernels not supported for the provided vector");
    return(CV_MEM_NULL);
  }
  cv_mem->cv_usefused = onoff;
  return(CV_SUCCESS);
#else
  cvProcessError(cv_mem, CV_ILL_INPUT, __LINE__, __func__, __FILE__,
                 "CVODE was not built with fused integrator kernels enabled");
  return(CV_ILL_INPUT);
#endif
}

/*
 * =================================================================
 * CVODE optional output functions
 * =================================================================
 */

/*
 * CVodeGetNumSteps
 *
 * Returns the current number of integration steps
 */

int CVodeGetNumSteps(void *cvode_mem, long int *nsteps)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  *nsteps = cv_mem->cv_nst;

  return(CV_SUCCESS);
}

/*
 * CVodeGetNumRhsEvals
 *
 * Returns the current number of calls to f
 */

int CVodeGetNumRhsEvals(void *cvode_mem, long int *nfevals)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  *nfevals = cv_mem->cv_nfe;

  return(CV_SUCCESS);
}

/*
 * CVodeGetNumLinSolvSetups
 *
 * Returns the current number of calls to the linear solver setup routine
 */

int CVodeGetNumLinSolvSetups(void *cvode_mem, long int *nlinsetups)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  *nlinsetups = cv_mem->cv_nsetups;

  return(CV_SUCCESS);
}

/*
 * CVodeGetNumErrTestFails
 *
 * Returns the current number of error test failures
 */

int CVodeGetNumErrTestFails(void *cvode_mem, long int *netfails)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  *netfails = cv_mem->cv_netf;

  return(CV_SUCCESS);
}

/*
 * CVodeGetLastOrder
 *
 * Returns the order on the last succesful step
 */

int CVodeGetLastOrder(void *cvode_mem, int *qlast)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  *qlast = cv_mem->cv_qu;

  return(CV_SUCCESS);
}

/*
 * CVodeGetCurrentOrder
 *
 * Returns the order to be attempted on the next step
 */

int CVodeGetCurrentOrder(void *cvode_mem, int *qcur)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  *qcur = cv_mem->cv_next_q;

  return(CV_SUCCESS);
}

/*
 * CVodeGetCurrentGamma
 *
 * Returns the value of gamma for the current step.
 */

int CVodeGetCurrentGamma(void *cvode_mem, realtype *gamma)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  *gamma = cv_mem->cv_gamma;

  return(CV_SUCCESS);
}

/*
 * CVodeGetNumStabLimOrderReds
 *
 * Returns the number of order reductions triggered by the stability
 * limit detection algorithm
 */

int CVodeGetNumStabLimOrderReds(void *cvode_mem, long int *nslred)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  if (cv_mem->cv_sldeton==SUNFALSE)
    *nslred = 0;
  else
    *nslred = cv_mem->cv_nor;

  return(CV_SUCCESS);
}

/*
 * CVodeGetActualInitStep
 *
 * Returns the step size used on the first step
 */

int CVodeGetActualInitStep(void *cvode_mem, realtype *hinused)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  *hinused = cv_mem->cv_h0u;

  return(CV_SUCCESS);
}

/*
 * CVodeGetLastStep
 *
 * Returns the step size used on the last successful step
 */

int CVodeGetLastStep(void *cvode_mem, realtype *hlast)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  *hlast = cv_mem->cv_hu;

  return(CV_SUCCESS);
}

/*
 * CVodeGetCurrentStep
 *
 * Returns the step size to be attempted on the next step
 */

int CVodeGetCurrentStep(void *cvode_mem, realtype *hcur)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  *hcur = cv_mem->cv_next_h;

  return(CV_SUCCESS);
}

/*
 * CVodeGetCurrentState
 *
 * Returns the current state vector
 */

int CVodeGetCurrentState(void *cvode_mem, N_Vector *y)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  *y = cv_mem->cv_y;

  return(CV_SUCCESS);
}

/*
 * CVodeGetCurrentTime
 *
 * Returns the current value of the independent variable
 */

int CVodeGetCurrentTime(void *cvode_mem, realtype *tcur)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  *tcur = cv_mem->cv_tn;

  return(CV_SUCCESS);
}

/*
 * CVodeGetTolScaleFactor
 *
 * Returns a suggested factor for scaling tolerances
 */

int CVodeGetTolScaleFactor(void *cvode_mem, realtype *tolsfact)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  *tolsfact = cv_mem->cv_tolsf;

  return(CV_SUCCESS);
}

/*
 * CVodeGetErrWeights
 *
 * This routine returns the current weight vector.
 */

int CVodeGetErrWeights(void *cvode_mem, N_Vector eweight)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  SUNCheckCallLastErrNoRet(N_VScale(ONE, cv_mem->cv_ewt, eweight));
  return(CV_SUCCESS);
}

/*
 * CVodeGetEstLocalErrors
 *
 * Returns an estimate of the local error
 */

int CVodeGetEstLocalErrors(void *cvode_mem, N_Vector ele)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  SUNCheckCallLastErrNoRet(N_VScale(ONE, cv_mem->cv_acor, ele));
  return(CV_SUCCESS);
}

/*
 * CVodeGetWorkSpace
 *
 * Returns integrator work space requirements
 */

int CVodeGetWorkSpace(void *cvode_mem, long int *lenrw, long int *leniw)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  *leniw = cv_mem->cv_liw;
  *lenrw = cv_mem->cv_lrw;

  return(CV_SUCCESS);
}

/*
 * CVodeGetIntegratorStats
 *
 * Returns integrator statistics
 */

int CVodeGetIntegratorStats(void *cvode_mem, long int *nsteps, long int *nfevals,
                            long int *nlinsetups, long int *netfails, int *qlast,
                            int *qcur, realtype *hinused, realtype *hlast,
                            realtype *hcur, realtype *tcur)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  *nsteps     = cv_mem->cv_nst;
  *nfevals    = cv_mem->cv_nfe;
  *nlinsetups = cv_mem->cv_nsetups;
  *netfails   = cv_mem->cv_netf;
  *qlast      = cv_mem->cv_qu;
  *qcur       = cv_mem->cv_next_q;
  *hinused    = cv_mem->cv_h0u;
  *hlast      = cv_mem->cv_hu;
  *hcur       = cv_mem->cv_next_h;
  *tcur       = cv_mem->cv_tn;

  return(CV_SUCCESS);
}

/*
 * CVodeGetNumGEvals
 *
 * Returns the current number of calls to g (for rootfinding)
 */

int CVodeGetNumGEvals(void *cvode_mem, long int *ngevals)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  *ngevals = cv_mem->cv_nge;

  return(CV_SUCCESS);
}

/*
 * CVodeGetRootInfo
 *
 * Returns pointer to array rootsfound showing roots found
 */

int CVodeGetRootInfo(void *cvode_mem, int *rootsfound)
{
  CVodeMem cv_mem;
  int i, nrt;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  nrt = cv_mem->cv_nrtfn;

  for (i=0; i<nrt; i++) rootsfound[i] = cv_mem->cv_iroots[i];

  return(CV_SUCCESS);
}


/*
 * CVodeGetNumNonlinSolvIters
 *
 * Returns the current number of iterations in the nonlinear solver
 */

int CVodeGetNumNonlinSolvIters(void *cvode_mem, long int *nniters)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  *nniters = cv_mem->cv_nni;

  return(CV_SUCCESS);
}

/*
 * CVodeGetNumNonlinSolvConvFails
 *
 * Returns the current number of convergence failures in the
 * nonlinear solver
 */

int CVodeGetNumNonlinSolvConvFails(void *cvode_mem, long int *nnfails)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  *nnfails = cv_mem->cv_nnf;

  return(CV_SUCCESS);
}

/*
 * CVodeGetNonlinSolvStats
 *
 * Returns nonlinear solver statistics
 */

int CVodeGetNonlinSolvStats(void *cvode_mem, long int *nniters,
                            long int *nnfails)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  *nniters = cv_mem->cv_nni;
  *nnfails = cv_mem->cv_nnf;

  return(CV_SUCCESS);
}

/*
 * CVodeGetNumStepSolveFails
 *
 * Returns the current number of failed steps due to a nonlinear solver
 * convergence failure
 */

int CVodeGetNumStepSolveFails(void *cvode_mem, long int *nncfails)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__,
                   MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  *nncfails = cv_mem->cv_ncfn;

  return(CV_SUCCESS);
}

/*
 * CVodePrintAllStats
 *
 * Print all integrator statistics
 */

int CVodePrintAllStats(void *cvode_mem, FILE *outfile, SUNOutputFormat fmt)
{
  CVodeMem cv_mem;
  CVLsMem cvls_mem;
  CVodeProjMem cvproj_mem;

  if (cvode_mem == NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__,
                   MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  switch(fmt)
  {
  case SUN_OUTPUTFORMAT_TABLE:
    /* step and method stats */
    fprintf(outfile, "Current time                 = %"RSYM"\n", cv_mem->cv_tn);
    fprintf(outfile, "Steps                        = %ld\n", cv_mem->cv_nst);
    fprintf(outfile, "Error test fails             = %ld\n", cv_mem->cv_netf);
    fprintf(outfile, "NLS step fails               = %ld\n", cv_mem->cv_ncfn);
    fprintf(outfile, "Initial step size            = %"RSYM"\n", cv_mem->cv_h0u);
    fprintf(outfile, "Last step size               = %"RSYM"\n", cv_mem->cv_hu);
    fprintf(outfile, "Current step size            = %"RSYM"\n", cv_mem->cv_next_h);
    fprintf(outfile, "Last method order            = %d\n", cv_mem->cv_qu);
    fprintf(outfile, "Current method order         = %d\n", cv_mem->cv_next_q);
    fprintf(outfile, "Stab. lim. order reductions  = %ld\n", cv_mem->cv_nor);

    /* function evaluations */
    fprintf(outfile, "RHS fn evals                 = %ld\n", cv_mem->cv_nfe);

    /* nonlinear solver stats */
    fprintf(outfile, "NLS iters                    = %ld\n", cv_mem->cv_nni);
    fprintf(outfile, "NLS fails                    = %ld\n", cv_mem->cv_nnf);
    if (cv_mem->cv_nst > 0)
    {
      fprintf(outfile, "NLS iters per step           = %"RSYM"\n",
              (realtype) cv_mem->cv_nni / (realtype) cv_mem->cv_nst);
    }

    /* linear solver stats */
    fprintf(outfile, "LS setups                    = %ld\n", cv_mem->cv_nsetups);
    if (cv_mem->cv_lmem)
    {
      cvls_mem = (CVLsMem) (cv_mem->cv_lmem);
      fprintf(outfile, "Jac fn evals                 = %ld\n", cvls_mem->nje);
      fprintf(outfile, "LS RHS fn evals              = %ld\n", cvls_mem->nfeDQ);
      fprintf(outfile, "Prec setup evals             = %ld\n", cvls_mem->npe);
      fprintf(outfile, "Prec solves                  = %ld\n", cvls_mem->nps);
      fprintf(outfile, "LS iters                     = %ld\n", cvls_mem->nli);
      fprintf(outfile, "LS fails                     = %ld\n", cvls_mem->ncfl);
      fprintf(outfile, "Jac-times setups             = %ld\n", cvls_mem->njtsetup);
      fprintf(outfile, "Jac-times evals              = %ld\n", cvls_mem->njtimes);
      if (cv_mem->cv_nni > 0)
      {
        fprintf(outfile, "LS iters per NLS iter        = %"RSYM"\n",
                (realtype) cvls_mem->nli / (realtype) cv_mem->cv_nni);
        fprintf(outfile, "Jac evals per NLS iter       = %"RSYM"\n",
                (realtype) cvls_mem->nje / (realtype) cv_mem->cv_nni);
        fprintf(outfile, "Prec evals per NLS iter      = %"RSYM"\n",
                (realtype) cvls_mem->npe / (realtype) cv_mem->cv_nni);
      }
    }

    /* rootfinding stats */
    fprintf(outfile, "Root fn evals                = %ld\n", cv_mem->cv_nge);

    /* projection stats */
    if (cv_mem->proj_mem)
    {
      cvproj_mem = (CVodeProjMem) (cv_mem->proj_mem);
      fprintf(outfile, "Projection fn evals          = %ld\n", cvproj_mem->nproj);
      fprintf(outfile, "Projection fails             = %ld\n", cvproj_mem->npfails);
    }
    break;

  case SUN_OUTPUTFORMAT_CSV:
    /* step and method stats */
    fprintf(outfile, "Time,%"RSYM, cv_mem->cv_tn);
    fprintf(outfile, ",Steps,%ld", cv_mem->cv_nst);
    fprintf(outfile, ",Error test fails,%ld", cv_mem->cv_netf);
    fprintf(outfile, ",NLS step fails,%ld", cv_mem->cv_ncfn);
    fprintf(outfile, ",Initial step size,%"RSYM, cv_mem->cv_h0u);
    fprintf(outfile, ",Last step size,%"RSYM, cv_mem->cv_hu);
    fprintf(outfile, ",Current step size,%"RSYM, cv_mem->cv_next_h);
    fprintf(outfile, ",Last method order,%d", cv_mem->cv_qu);
    fprintf(outfile, ",Current method order,%d", cv_mem->cv_next_q);
    fprintf(outfile, ",Stab. lim. order reductions,%ld", cv_mem->cv_nor);

    /* function evaluations */
    fprintf(outfile, ",RHS fn evals,%ld", cv_mem->cv_nfe);

    /* nonlinear solver stats */
    fprintf(outfile, ",NLS iters,%ld", cv_mem->cv_nni);
    fprintf(outfile, ",NLS fails,%ld", cv_mem->cv_nnf);
    if (cv_mem->cv_nst > 0)
    {
      fprintf(outfile, ",NLS iters per step,%"RSYM,
              (realtype) cv_mem->cv_nni / (realtype) cv_mem->cv_nst);
    }
    else
    {
      fprintf(outfile, ",NLS iters per step,0");
    }

    /* linear solver stats */
    fprintf(outfile, ",LS setups,%ld", cv_mem->cv_nsetups);
    if (cv_mem->cv_lmem)
    {
      cvls_mem = (CVLsMem) (cv_mem->cv_lmem);
      fprintf(outfile, ",Jac fn evals,%ld", cvls_mem->nje);
      fprintf(outfile, ",LS RHS fn evals,%ld", cvls_mem->nfeDQ);
      fprintf(outfile, ",Prec setup evals,%ld", cvls_mem->npe);
      fprintf(outfile, ",Prec solves,%ld", cvls_mem->nps);
      fprintf(outfile, ",LS iters,%ld", cvls_mem->nli);
      fprintf(outfile, ",LS fails,%ld", cvls_mem->ncfl);
      fprintf(outfile, ",Jac-times setups,%ld", cvls_mem->njtsetup);
      fprintf(outfile, ",Jac-times evals,%ld", cvls_mem->njtimes);
      if (cv_mem->cv_nni > 0)
      {
        fprintf(outfile, ",LS iters per NLS iter,%"RSYM,
                (realtype) cvls_mem->nli / (realtype) cv_mem->cv_nni);
        fprintf(outfile, ",Jac evals per NLS iter,%"RSYM,
                (realtype) cvls_mem->nje / (realtype) cv_mem->cv_nni);
        fprintf(outfile, ",Prec evals per NLS iter,%"RSYM,
                (realtype) cvls_mem->npe / (realtype) cv_mem->cv_nni);
      }
      else
      {
        fprintf(outfile, ",LS iters per NLS iter,0");
        fprintf(outfile, ",Jac evals per NLS iter,0");
        fprintf(outfile, ",Prec evals per NLS iter,0");
      }
    }

    /* rootfinding stats */
    fprintf(outfile, ",Root fn evals,%ld", cv_mem->cv_nge);

    /* projection stats */
    if (cv_mem->proj_mem)
    {
      cvproj_mem = (CVodeProjMem) (cv_mem->proj_mem);
      fprintf(outfile, ",Projection fn evals,%ld", cvproj_mem->nproj);
      fprintf(outfile, ",Projection fails,%ld", cvproj_mem->npfails);
    }
    fprintf(outfile, "\n");
    break;

  default:
    cvProcessError(cv_mem, CV_ILL_INPUT, __LINE__, __func__, __FILE__,
                   "Invalid formatting option.");
    return(CV_ILL_INPUT);
  }

  return(CV_SUCCESS);
}

/*-----------------------------------------------------------------*/

int CVodeGetUserData(void *cvode_mem, void** user_data)
{
  CVodeMem cv_mem;

  if (cvode_mem==NULL) {
    cvProcessError(NULL, CV_MEM_NULL, __LINE__, __func__, __FILE__, MSGCV_NO_MEM);
    return(CV_MEM_NULL);
  }

  cv_mem = (CVodeMem) cvode_mem;

  SUNDeclareContext(CV_SUNCTX);

  *user_data = cv_mem->cv_user_data;

  return(CV_SUCCESS);
}

/*-----------------------------------------------------------------*/

char *CVodeGetReturnFlagName(long int flag)
{
  char *name;

  name = (char *)malloc(24*sizeof(char));

  switch(flag) {
  case CV_SUCCESS:
    sprintf(name,"CV_SUCCESS");
    break;
  case CV_TSTOP_RETURN:
    sprintf(name,"CV_TSTOP_RETURN");
    break;
  case CV_ROOT_RETURN:
    sprintf(name,"CV_ROOT_RETURN");
    break;
  case CV_TOO_MUCH_WORK:
    sprintf(name,"CV_TOO_MUCH_WORK");
    break;
  case CV_TOO_MUCH_ACC:
    sprintf(name,"CV_TOO_MUCH_ACC");
    break;
  case CV_ERR_FAILURE:
    sprintf(name,"CV_ERR_FAILURE");
    break;
  case CV_CONV_FAILURE:
    sprintf(name,"CV_CONV_FAILURE");
    break;
  case CV_LINIT_FAIL:
    sprintf(name,"CV_LINIT_FAIL");
    break;
  case CV_LSETUP_FAIL:
    sprintf(name,"CV_LSETUP_FAIL");
    break;
  case CV_LSOLVE_FAIL:
    sprintf(name,"CV_LSOLVE_FAIL");
    break;
  case CV_RHSFUNC_FAIL:
    sprintf(name,"CV_RHSFUNC_FAIL");
    break;
  case CV_FIRST_RHSFUNC_ERR:
    sprintf(name,"CV_FIRST_RHSFUNC_ERR");
    break;
  case CV_REPTD_RHSFUNC_ERR:
    sprintf(name,"CV_REPTD_RHSFUNC_ERR");
    break;
  case CV_UNREC_RHSFUNC_ERR:
    sprintf(name,"CV_UNREC_RHSFUNC_ERR");
    break;
  case CV_RTFUNC_FAIL:
    sprintf(name,"CV_RTFUNC_FAIL");
    break;
  case CV_MEM_FAIL:
    sprintf(name,"CV_MEM_FAIL");
    break;
  case CV_MEM_NULL:
    sprintf(name,"CV_MEM_NULL");
    break;
  case CV_ILL_INPUT:
    sprintf(name,"CV_ILL_INPUT");
    break;
  case CV_NO_MALLOC:
    sprintf(name,"CV_NO_MALLOC");
    break;
  case CV_BAD_K:
    sprintf(name,"CV_BAD_K");
    break;
  case CV_BAD_T:
    sprintf(name,"CV_BAD_T");
    break;
  case CV_BAD_DKY:
    sprintf(name,"CV_BAD_DKY");
    break;
  case CV_TOO_CLOSE:
    sprintf(name,"CV_TOO_CLOSE");
    break;
  case CV_NLS_INIT_FAIL:
    sprintf(name,"CV_NLS_INIT_FAIL");
    break;
  case CV_NLS_SETUP_FAIL:
    sprintf(name,"CV_NLS_SETUPT_FAIL");
    break;
  case CV_NLS_FAIL:
    sprintf(name,"CV_NLS_FAIL");
    break;
  case CV_PROJ_MEM_NULL:
    sprintf(name,"CV_PROJ_MEM_NULL");
    break;
  case CV_PROJFUNC_FAIL:
    sprintf(name,"CV_PROJFUNC_FAIL");
    break;
  case CV_REPTD_PROJFUNC_ERR:
    sprintf(name,"CV_REPTD_PROJFUNC_ERR");
    break;
  default:
    sprintf(name,"NONE");
  }

  return(name);
}
