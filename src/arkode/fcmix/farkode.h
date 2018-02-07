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
 * This is the header file for FARKODE, the Fortran interface to
 * the ARKODE package.
 *--------------------------------------------------------------*/

/*===============================================================
  FARKODE Interface Package

  The FARKODE Interface Package is a package of C functions which
  support the use of the ARKODE solver in a mixed Fortran/C 
  setting.  While ARKODE is written in C, it is assumed here that 
  the user's calling program and user-supplied problem-defining 
  routines are written in Fortran.  This package provides the 
  necessary interface to ARKODE for any acceptable NVECTOR 
  implementation.
  
  While previous versions of this file included relatively 
  exhaustive documentation of the FARKODE interface, such 
  information is also included in the main ARKode documentation
  (PDF and HTML formats), so to ease the maintenance burden the 
  FARKODE documentation has been removed from this file.
  ===============================================================*/

#ifndef _FARKODE_H
#define _FARKODE_H

/* header files  */
#include <arkode/arkode.h>
#include <sundials/sundials_linearsolver.h>  /* definition of type SUNLinearSolver */
#include <sundials/sundials_matrix.h>        /* definition of type SUNMatrix */
#include <sundials/sundials_nvector.h>       /* definition of type N_Vector */
#include <sundials/sundials_types.h>         /* definition of type realtype */

/*=============================================================*/

#ifdef __cplusplus  /* wrapper to enable C++ usage */
extern "C" {
#endif

/* Definitions of interface function names */
#if defined(SUNDIALS_F77_FUNC)

#define FARK_IMP_FUN             SUNDIALS_F77_FUNC(farkifun,                FARKIFUN)
#define FARK_EXP_FUN             SUNDIALS_F77_FUNC(farkefun,                FARKEFUN)
#define FARK_MALLOC              SUNDIALS_F77_FUNC(farkmalloc,              FARKMALLOC)
#define FARK_REINIT              SUNDIALS_F77_FUNC(farkreinit,              FARKREINIT)
#define FARK_RESIZE              SUNDIALS_F77_FUNC(farkresize,              FARKRESIZE)
#define FARK_SETDEFAULTS         SUNDIALS_F77_FUNC(farksetdefaults,         FARKSETDEFAULTS)
#define FARK_SETIIN              SUNDIALS_F77_FUNC(farksetiin,              FARKSETIIN)
#define FARK_SETRIN              SUNDIALS_F77_FUNC(farksetrin,              FARKSETRIN)
#define FARK_SETADAPTMETHOD      SUNDIALS_F77_FUNC(farksetadaptivitymethod, FARKSETADAPTIVITYMETHOD)
#define FARK_SETERKTABLE         SUNDIALS_F77_FUNC(farkseterktable,         FARKSETERKTABLE)
#define FARK_SETIRKTABLE         SUNDIALS_F77_FUNC(farksetirktable,         FARKSETIRKTABLE)
#define FARK_SETARKTABLES        SUNDIALS_F77_FUNC(farksetarktables,        FARKSETARKTABLES)
#define FARK_SETRESTOLERANCE     SUNDIALS_F77_FUNC(farksetrestolerance,     FARKSETRESTOLERANCE)
#define FARK_SETDIAGNOSTICS      SUNDIALS_F77_FUNC(farksetdiagnostics,      FARKSETDIAGNOSTICS)
#define FARK_STOPDIAGNOSTICS     SUNDIALS_F77_FUNC(farkstopdiagnostics,     FARKSTOPDIAGNOSTICS)
#define FARK_DLSINIT             SUNDIALS_F77_FUNC(farkdlsinit,             FARKDLSINIT)
#define FARK_DLSMASSINIT         SUNDIALS_F77_FUNC(farkdlsmassinit,         FARKDLSMASSINIT)
#define FARK_SPILSINIT           SUNDIALS_F77_FUNC(farkspilsinit,           FARKSPILSINIT)
#define FARK_SPILSSETEPSLIN      SUNDIALS_F77_FUNC(farkspilssetepslin,      FARKSPILSSETEPSLIN)
#define FARK_SPILSMASSINIT       SUNDIALS_F77_FUNC(farkspilsmassinit,       FARKSPILSMASSINIT)
#define FARK_SPILSSETMASSEPSLIN  SUNDIALS_F77_FUNC(farkspilssetmassepslin,  FARKSPILSSETMASSEPSLIN)
#define FARK_ARKODE              SUNDIALS_F77_FUNC(farkode,                 FARKODE)
#define FARK_DKY                 SUNDIALS_F77_FUNC(farkdky,                 FARKDKY)
#define FARK_GETERRWEIGHTS       SUNDIALS_F77_FUNC(farkgeterrweights,       FARKGETERRWEIGHTS)
#define FARK_GETRESWEIGHTS       SUNDIALS_F77_FUNC(farkgetresweights,       FARKGETRESWEIGHTS)
#define FARK_GETESTLOCALERR      SUNDIALS_F77_FUNC(farkgetestlocalerr,      FARKGETESTLOCALERR)
#define FARK_FREE                SUNDIALS_F77_FUNC(farkfree,                FARKFREE)
#define FARK_WRITEPARAMETERS     SUNDIALS_F77_FUNC(farkwriteparameters,     FARKWRITEPARAMETERS)

#define FARK_DENSESETJAC         SUNDIALS_F77_FUNC(farkdensesetjac,         FARKDENSESETJAC)
#define FARK_DJAC                SUNDIALS_F77_FUNC(farkdjac,                FARKDJAC)

#define FARK_BANDSETJAC          SUNDIALS_F77_FUNC(farkbandsetjac,          FARKBANDSETJAC)
#define FARK_BJAC                SUNDIALS_F77_FUNC(farkbjac,                FARKBJAC)

#define FARK_SPARSESETJAC        SUNDIALS_F77_FUNC(farksparsesetjac,        FARKSPARSESETJAC)
#define FARK_SPJAC               SUNDIALS_F77_FUNC(farkspjac,               FARKSPJAC)

#define FARK_DENSESETMASS        SUNDIALS_F77_FUNC(farkdensesetmass,        FARKDENSESETMASS)
#define FARK_DMASS               SUNDIALS_F77_FUNC(farkdmass,               FARKDMASS)

#define FARK_BANDSETMASS         SUNDIALS_F77_FUNC(farkbandsetmass,         FARKBANDSETMASS)
#define FARK_BMASS               SUNDIALS_F77_FUNC(farkbmass,               FARKBMASS)

#define FARK_SPARSESETMASS       SUNDIALS_F77_FUNC(farksparsesetmass,       FARKSPARSESETMASS)
#define FARK_SPMASS              SUNDIALS_F77_FUNC(farkspmass,              FARKSPMASS)

#define FARK_SPILSSETJAC         SUNDIALS_F77_FUNC(farkspilssetjac,         FARKSPILSSETJAC)
#define FARK_JTSETUP             SUNDIALS_F77_FUNC(farkjtsetup,             FARKJTSETUP)
#define FARK_JTIMES              SUNDIALS_F77_FUNC(farkjtimes,              FARKJTIMES)

#define FARK_SPILSSETPREC        SUNDIALS_F77_FUNC(farkspilssetprec,        FARKSPILSSETPREC)
#define FARK_PSOL                SUNDIALS_F77_FUNC(farkpsol,                FARKPSOL)
#define FARK_PSET                SUNDIALS_F77_FUNC(farkpset,                FARKPSET)

#define FARK_SPILSSETMASS        SUNDIALS_F77_FUNC(farkspilssetmass,        FARKSPILSSETMASS)
#define FARK_MTSETUP             SUNDIALS_F77_FUNC(farkmtsetup,             FARKMTSETUP)
#define FARK_MTIMES              SUNDIALS_F77_FUNC(farkmtimes,              FARKMTIMES)

#define FARK_SPILSSETMASSPREC    SUNDIALS_F77_FUNC(farkspilssetmassprec,    FARKSPILSSETMASSPREC)
#define FARK_MASSPSOL            SUNDIALS_F77_FUNC(farkmasspsol,            FARKMASSPSOL)
#define FARK_MASSPSET            SUNDIALS_F77_FUNC(farkmasspset,            FARKMASSPSET)

#define FARK_EWTSET              SUNDIALS_F77_FUNC(farkewtset,              FARKEWTSET)
#define FARK_EWT                 SUNDIALS_F77_FUNC(farkewt,                 FARKEWT)

#define FARK_ADAPTSET            SUNDIALS_F77_FUNC(farkadaptset,            FARKADAPTSET)
#define FARK_ADAPT               SUNDIALS_F77_FUNC(farkadapt,               FARKADAPT)

#define FARK_EXPSTABSET          SUNDIALS_F77_FUNC(farkexpstabset,          FARKEXPSTABSET)
#define FARK_EXPSTAB             SUNDIALS_F77_FUNC(farkexpstab,             FARKEXPSTAB)

#else

#define FARK_IMP_FUN             farkifun_
#define FARK_EXP_FUN             farkefun_
#define FARK_MALLOC              farkmalloc_
#define FARK_REINIT              farkreinit_
#define FARK_RESIZE              farkresize_
#define FARK_SETDEFAULTS         farksetdefaults_
#define FARK_SETIIN              farksetiin_
#define FARK_SETRIN              farksetrin_
#define FARK_SETADAPTMETHOD      farksetadaptivitymethod_
#define FARK_SETERKTABLE         farkseterktable_
#define FARK_SETIRKTABLE         farksetirktable_
#define FARK_SETARKTABLES        farksetarktables_
#define FARK_SETRESTOLERANCE     farksetrestolerance_
#define FARK_SETDIAGNOSTICS      farksetdiagnostics_
#define FARK_STOPDIAGNOSTICS     farkstopdiagnostics_
#define FARK_DLSINIT             farkdlsinit_
#define FARK_DLSMASSINIT         farkdlsmassinit_
#define FARK_SPILSINIT           farkspilsinit_
#define FARK_SPILSSETEPSLIN      farkspilssetepslin_
#define FARK_SPILSMASSINIT       farkspilsmassinit_
#define FARK_SPILSSETMASSEPSLIN  farkspilssetmassepslin_
#define FARK_ARKODE              farkode_
#define FARK_DKY                 farkdky_
#define FARK_GETERRWEIGHTS       farkgeterrweights_
#define FARK_GETRESWEIGHTS       farkgetresweights_
#define FARK_GETESTLOCALERR      farkgetestlocalerr_
#define FARK_FREE                farkfree_
#define FARK_WRITEPARAMETERS     farkwriteparameters_

#define FARK_DENSESETJAC         farkdensesetjac_
#define FARK_DJAC                farkdjac_

#define FARK_BANDSETJAC          farkbandsetjac_
#define FARK_BJAC                farkbjac_

#define FARK_SPARSESETJAC        farksparsesetjac_
#define FARK_SPJAC               farkspjac_

#define FARK_DENSESETMASS        farkdensesetmass_
#define FARK_DMASS               farkdmass_

#define FARK_BANDSETMASS         farkbandsetmass_
#define FARK_BMASS               farkbmass_

#define FARK_SPARSESETMASS       farksparsesetmass_
#define FARK_SPMASS              farkspmass_


#define FARK_SPILSSETJAC         farkspilssetjac_
#define FARK_JTSETUP             farkjtsetup_
#define FARK_JTIMES              farkjtimes_

#define FARK_SPILSSETPREC        farkspilssetprec_
#define FARK_PSOL                farkpsol_
#define FARK_PSET                farkpset_

#define FARK_SPILSSETMASS        farkspilssetmass_
#define FARK_MTSETUP             farkmtsetup_
#define FARK_MTIMES              farkmtimes_

#define FARK_SPILSSETMASSPREC    farkspilssetmassprec_
#define FARK_MASSPSOL            farkmasspsol_
#define FARK_MASSPSET            farkmasspset_

#define FARK_EWTSET              farkewtset_
#define FARK_EWT                 farkewt_

#define FARK_ADAPTSET            farkadaptset_
#define FARK_ADAPT               farkadapt_

#define FARK_EXPSTABSET          farkexpstabset_
#define FARK_EXPSTAB             farkexpstab_

#endif

  /* Type for user data */
  typedef struct {
    realtype *rpar;
    long int *ipar;
  } *FARKUserData;

  /* Prototypes of exported functions */
  void FARK_MALLOC(realtype *t0, realtype *y0, int *imex, 
                   int *iatol, realtype *rtol, realtype *atol, 
                   long int *iout, realtype *rout, 
                   long int *ipar, realtype *rpar, int *ier);

  void FARK_REINIT(realtype *t0, realtype *y0, int *imex,
                   int *iatol, realtype *rtol, realtype *atol,
                   int *ier);

  void FARK_RESIZE(realtype *t0, realtype *y0, realtype *hscale,
                   int *itol, realtype *rtol, realtype *atol, int *ier);

  void FARK_SETDEFAULTS(int *ier);
  void FARK_SETIIN(char key_name[], long int *ival, int *ier);
  void FARK_SETRIN(char key_name[], realtype *rval, int *ier);

  void FARK_SETADAPTMETHOD(int *imethod, int *idefault, int *ipq, 
                           realtype *params, int *ier);

  void FARK_SETERKTABLE(int *s, int *q, int *p, realtype *c, realtype *A, 
                        realtype *b, realtype *b2, int *ier);
  void FARK_SETIRKTABLE(int *s, int *q, int *p, realtype *c,
                        realtype *A, realtype *b, realtype *b2, int *ier);
  void FARK_SETARKTABLES(int *s, int *q, int *p, realtype *ci, 
                         realtype *ce, realtype *Ai, realtype *Ae, 
                         realtype *bi, realtype *be, realtype *b2i, 
                         realtype *b2e, int *ier);

  void FARK_SETRESTOLERANCE(int *itol, realtype *atol, int *ier);
  void FARK_SETDIAGNOSTICS(char fname[], int *flen, int *ier);
  void FARK_STOPDIAGNOSTICS(int *ier);

  void FARK_DLSINIT(int *ier);
  void FARK_DLSMASSINIT(int *time_dep, int *ier);

  void FARK_SPILSINIT(int *ier);
  void FARK_SPILSSETEPSLIN(realtype *eplifac, int *ier);

  void FARK_SPILSMASSINIT(int *time_dep, int *ier);
  void FARK_SPILSSETMASSEPSLIN(realtype *eplifac, int *ier);

  void FARK_ARKODE(realtype *tout, realtype *t, realtype *y, 
                   int *itask, int *ier);
  void FARK_DKY(realtype *t, int *k, realtype *dky, int *ier);

  void FARK_GETERRWEIGHTS(realtype *eweight, int *ier);
  void FARK_GETRESWEIGHTS(realtype *rweight, int *ier);
  void FARK_GETESTLOCALERR(realtype *ele, int *ier);

  void FARK_FREE(void);

  void FARK_WRITEPARAMETERS(int *ier);

  void FARK_DENSESETJAC(int *flag, int *ier);
  void FARK_BANDSETJAC(int *flag, int *ier);
  void FARK_SPARSESETJAC(int *ier);

  void FARK_DENSESETMASS(int *ier);
  void FARK_BANDSETMASS(int *ier);
  void FARK_SPARSESETMASS(int *ier);


  void FARK_SPILSSETJAC(int *flag, int *ier);
  void FARK_SPILSSETPREC(int *flag, int *ier);
  void FARK_SPILSSETMASS(int *ier);
  void FARK_SPILSSETMASSPREC(int *flag, int *ier);

  void FARK_EWTSET(int *flag, int *ier);
  void FARK_ADAPTSET(int *flag, int *ier);
  void FARK_EXPSTABSET(int *flag, int *ier);


  /* Prototypes: Functions Called by the ARKODE Solver */
  int FARKfe(realtype t, N_Vector y, N_Vector ydot, void *user_data);
  int FARKfi(realtype t, N_Vector y, N_Vector ydot, void *user_data);
  
  int FARKDenseJac(realtype t, N_Vector y, N_Vector fy, 
                   SUNMatrix J, void *user_data,
                   N_Vector vtemp1, N_Vector vtemp2, N_Vector vtemp3);
  
  int FARKBandJac(realtype t, N_Vector y, N_Vector fy,
                  SUNMatrix J, void *user_data,
                  N_Vector vtemp1, N_Vector vtemp2, N_Vector vtemp3);
  
  int FARKSparseJac(realtype t, N_Vector y, N_Vector fy, 
                    SUNMatrix J, void *user_data, N_Vector vtemp1, 
                    N_Vector vtemp2, N_Vector vtemp3);

  
  int FARKDenseMass(realtype t, SUNMatrix M, void *user_data, 
                    N_Vector vtemp1, N_Vector vtemp2, N_Vector vtemp3);
  
  int FARKBandMass(realtype t, SUNMatrix M, void *user_data, 
                    N_Vector vtemp1, N_Vector vtemp2, N_Vector vtemp3);
  
  int FARKSparseMass(realtype t, SUNMatrix M, void *user_data, 
                    N_Vector vtemp1, N_Vector vtemp2, N_Vector vtemp3);
  

  int FARKPSet(realtype tn, N_Vector y, N_Vector fy, booleantype jok,
               booleantype *jcurPtr, realtype gamma, void *user_data);
  
  int FARKMassPSet(realtype tn, void *user_data);
  
  int FARKPSol(realtype tn, N_Vector y, N_Vector fy, N_Vector r, 
               N_Vector z, realtype gamma, realtype delta, int lr, 
               void *user_data);
  
  int FARKMassPSol(realtype tn, N_Vector r, N_Vector z, realtype delta, 
                   int lr, void *user_data);
  
  int FARKJTSetup(realtype t, N_Vector y, N_Vector fy, void *user_data);
  
  int FARKJtimes(N_Vector v, N_Vector Jv, realtype t, N_Vector y, 
                 N_Vector fy, void *user_data, N_Vector work);
  
  int FARKMTSetup(realtype t, void *user_data);
  
  int FARKMtimes(N_Vector v, N_Vector Mv, realtype t, void *user_data);

  int FARKEwt(N_Vector y, N_Vector ewt, void *user_data);

  int FARKAdapt(N_Vector y, realtype t, realtype h1, realtype h2,
                realtype h3, realtype e1, realtype e2, realtype e3,
                int q, realtype *hnew, void *user_data);

  int FARKExpStab(N_Vector y, realtype t, realtype *hstab, void *user_data);

  void FARKNullMatrix();
  void FARKNullLinsol();
  
  /* Declarations for global variables shared amongst various routines */
  extern N_Vector F2C_ARKODE_vec;             /* defined in FNVECTOR module */
  extern SUNMatrix F2C_ARKODE_matrix;         /* defined in FSUNMATRIX module */
  extern SUNMatrix F2C_ARKODE_mass_matrix;  
  extern SUNLinearSolver F2C_ARKODE_linsol;   /* defined in FSUNLINSOL module */
  extern SUNLinearSolver F2C_ARKODE_mass_sol; 

  extern void *ARK_arkodemem;     /* defined in farkode.c */
  extern long int *ARK_iout;      /* defined in farkode.c */
  extern realtype *ARK_rout;      /* defined in farkode.c */
  extern int ARK_nrtfn;           /* defined in farkode.c */
  extern int ARK_ls;              /* defined in farkode.c */
  extern int ARK_mass_ls;         /* defined in farkode.c */

  /* Linear solver IDs */
  enum { ARK_LS_ITERATIVE = 0, 
         ARK_LS_DIRECT    = 1, 
         ARK_LS_CUSTOM    = 2 };

#ifdef __cplusplus
}
#endif

#endif

/*===============================================================
  EOF
  ===============================================================*/
