/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.0
 *
 * This file is not intended to be easily readable and contains a number of
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG
 * interface file instead.
 * ----------------------------------------------------------------------------- */
/* -----------------------------------------------------------------------------
 *  This section contains generic SWIG labels for method/variable
 *  declarations/attributes, and other compiler dependent labels.
 * ----------------------------------------------------------------------------- */

/* template workaround for compilers that cannot correctly implement the C++ standard */
#ifndef SWIGTEMPLATEDISAMBIGUATOR
# if defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x560)
#  define SWIGTEMPLATEDISAMBIGUATOR template
# elif defined(__HP_aCC)
/* Needed even with `aCC -AA' when `aCC -V' reports HP ANSI C++ B3910B A.03.55 */
/* If we find a maximum version that requires this, the test would be __HP_aCC <= 35500 for A.03.55 */
#  define SWIGTEMPLATEDISAMBIGUATOR template
# else
#  define SWIGTEMPLATEDISAMBIGUATOR
# endif
#endif

/* inline attribute */
#ifndef SWIGINLINE
# if defined(__cplusplus) || (defined(__GNUC__) && !defined(__STRICT_ANSI__))
#   define SWIGINLINE inline
# else
#   define SWIGINLINE
# endif
#endif

/* attribute recognised by some compilers to avoid 'unused' warnings */
#ifndef SWIGUNUSED
# if defined(__GNUC__)
#   if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#     define SWIGUNUSED __attribute__ ((__unused__))
#   else
#     define SWIGUNUSED
#   endif
# elif defined(__ICC)
#   define SWIGUNUSED __attribute__ ((__unused__))
# else
#   define SWIGUNUSED
# endif
#endif

#ifndef SWIG_MSC_UNSUPPRESS_4505
# if defined(_MSC_VER)
#   pragma warning(disable : 4505) /* unreferenced local function has been removed */
# endif
#endif

#ifndef SWIGUNUSEDPARM
# ifdef __cplusplus
#   define SWIGUNUSEDPARM(p)
# else
#   define SWIGUNUSEDPARM(p) p SWIGUNUSED
# endif
#endif

/* internal SWIG method */
#ifndef SWIGINTERN
# define SWIGINTERN static SWIGUNUSED
#endif

/* internal inline SWIG method */
#ifndef SWIGINTERNINLINE
# define SWIGINTERNINLINE SWIGINTERN SWIGINLINE
#endif

/* qualifier for exported *const* global data variables*/
#ifndef SWIGEXTERN
# ifdef __cplusplus
#   define SWIGEXTERN extern
# else
#   define SWIGEXTERN
# endif
#endif

/* exporting methods */
#if defined(__GNUC__)
#  if (__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#    ifndef GCC_HASCLASSVISIBILITY
#      define GCC_HASCLASSVISIBILITY
#    endif
#  endif
#endif

#ifndef SWIGEXPORT
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   if defined(STATIC_LINKED)
#     define SWIGEXPORT
#   else
#     define SWIGEXPORT __declspec(dllexport)
#   endif
# else
#   if defined(__GNUC__) && defined(GCC_HASCLASSVISIBILITY)
#     define SWIGEXPORT __attribute__ ((visibility("default")))
#   else
#     define SWIGEXPORT
#   endif
# endif
#endif

/* calling conventions for Windows */
#ifndef SWIGSTDCALL
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   define SWIGSTDCALL __stdcall
# else
#   define SWIGSTDCALL
# endif
#endif

/* Deal with Microsoft's attempt at deprecating C standard runtime functions */
#if !defined(SWIG_NO_CRT_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_CRT_SECURE_NO_DEPRECATE)
# define _CRT_SECURE_NO_DEPRECATE
#endif

/* Deal with Microsoft's attempt at deprecating methods in the standard C++ library */
#if !defined(SWIG_NO_SCL_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_SCL_SECURE_NO_DEPRECATE)
# define _SCL_SECURE_NO_DEPRECATE
#endif

/* Deal with Apple's deprecated 'AssertMacros.h' from Carbon-framework */
#if defined(__APPLE__) && !defined(__ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES)
# define __ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES 0
#endif

/* Intel's compiler complains if a variable which was never initialised is
 * cast to void, which is a common idiom which we use to indicate that we
 * are aware a variable isn't used.  So we just silence that warning.
 * See: https://github.com/swig/swig/issues/192 for more discussion.
 */
#ifdef __INTEL_COMPILER
# pragma warning disable 592
#endif

/*  Errors in SWIG */
#define  SWIG_UnknownError    	   -1
#define  SWIG_IOError        	   -2
#define  SWIG_RuntimeError   	   -3
#define  SWIG_IndexError     	   -4
#define  SWIG_TypeError      	   -5
#define  SWIG_DivisionByZero 	   -6
#define  SWIG_OverflowError  	   -7
#define  SWIG_SyntaxError    	   -8
#define  SWIG_ValueError     	   -9
#define  SWIG_SystemError    	   -10
#define  SWIG_AttributeError 	   -11
#define  SWIG_MemoryError    	   -12
#define  SWIG_NullReferenceError   -13




#include <assert.h>
#define SWIG_exception_impl(DECL, CODE, MSG, RETURNNULL) \
 { printf("In " DECL ": " MSG); assert(0); RETURNNULL; }


#include <stdio.h>
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(_WATCOM)
# ifndef snprintf
#  define snprintf _snprintf
# endif
#endif


/* Support for the `contract` feature.
 *
 * Note that RETURNNULL is first because it's inserted via a 'Replaceall' in
 * the fortran.cxx file.
 */
#define SWIG_contract_assert(RETURNNULL, EXPR, MSG) \
 if (!(EXPR)) { SWIG_exception_impl("$decl", SWIG_ValueError, MSG, RETURNNULL); } 


#define SWIGVERSION 0x040000 
#define SWIG_VERSION SWIGVERSION


#define SWIG_as_voidptr(a) (void *)((const void *)(a)) 
#define SWIG_as_voidptrptr(a) ((void)SWIG_as_voidptr(*a),(void**)(a)) 


#include "sundials/sundials_iterative.h"
#include "sundials/sundials_linearsolver.h"

SWIGEXPORT int _wrap_FSUNModifiedGS(void *farg1, void *farg2, int const *farg3, int const *farg4, double *farg5) {
  int fresult ;
  N_Vector *arg1 = (N_Vector *) 0 ;
  sunrealtype **arg2 = (sunrealtype **) 0 ;
  int arg3 ;
  int arg4 ;
  sunrealtype *arg5 = (sunrealtype *) 0 ;
<<<<<<< HEAD
  SUNErrCode result;
=======
  int result;
>>>>>>> feature/sunmpicomm-formatted
  
  arg1 = (N_Vector *)(farg1);
  arg2 = (sunrealtype **)(farg2);
  arg3 = (int)(*farg3);
  arg4 = (int)(*farg4);
  arg5 = (sunrealtype *)(farg5);
<<<<<<< HEAD
  result = (SUNErrCode)SUNModifiedGS(arg1,arg2,arg3,arg4,arg5);
  fresult = (SUNErrCode)(result);
=======
  result = (int)SUNModifiedGS(arg1,arg2,arg3,arg4,arg5);
  fresult = (int)(result);
>>>>>>> feature/sunmpicomm-formatted
  return fresult;
}


SWIGEXPORT int _wrap_FSUNClassicalGS(void *farg1, void *farg2, int const *farg3, int const *farg4, double *farg5, double *farg6, void *farg7) {
  int fresult ;
  N_Vector *arg1 = (N_Vector *) 0 ;
  sunrealtype **arg2 = (sunrealtype **) 0 ;
  int arg3 ;
  int arg4 ;
  sunrealtype *arg5 = (sunrealtype *) 0 ;
  sunrealtype *arg6 = (sunrealtype *) 0 ;
  N_Vector *arg7 = (N_Vector *) 0 ;
  SUNErrCode result;
  
  arg1 = (N_Vector *)(farg1);
  arg2 = (sunrealtype **)(farg2);
  arg3 = (int)(*farg3);
  arg4 = (int)(*farg4);
  arg5 = (sunrealtype *)(farg5);
  arg6 = (sunrealtype *)(farg6);
  arg7 = (N_Vector *)(farg7);
  result = (SUNErrCode)SUNClassicalGS(arg1,arg2,arg3,arg4,arg5,arg6,arg7);
  fresult = (SUNErrCode)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNQRfact(int const *farg1, void *farg2, double *farg3, int const *farg4) {
  int fresult ;
  int arg1 ;
  sunrealtype **arg2 = (sunrealtype **) 0 ;
  sunrealtype *arg3 = (sunrealtype *) 0 ;
  int arg4 ;
  int result;
  
  arg1 = (int)(*farg1);
  arg2 = (sunrealtype **)(farg2);
  arg3 = (sunrealtype *)(farg3);
  arg4 = (int)(*farg4);
  result = (int)SUNQRfact(arg1,arg2,arg3,arg4);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNQRsol(int const *farg1, void *farg2, double *farg3, double *farg4) {
  int fresult ;
  int arg1 ;
  sunrealtype **arg2 = (sunrealtype **) 0 ;
  sunrealtype *arg3 = (sunrealtype *) 0 ;
  sunrealtype *arg4 = (sunrealtype *) 0 ;
  int result;
  
  arg1 = (int)(*farg1);
  arg2 = (sunrealtype **)(farg2);
  arg3 = (sunrealtype *)(farg3);
  arg4 = (sunrealtype *)(farg4);
  result = (int)SUNQRsol(arg1,arg2,arg3,arg4);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNQRAdd_MGS(void *farg1, double *farg2, N_Vector farg3, int const *farg4, int const *farg5, void *farg6) {
  int fresult ;
  N_Vector *arg1 = (N_Vector *) 0 ;
  sunrealtype *arg2 = (sunrealtype *) 0 ;
  N_Vector arg3 = (N_Vector) 0 ;
  int arg4 ;
  int arg5 ;
  void *arg6 = (void *) 0 ;
  SUNErrCode result;
  
  arg1 = (N_Vector *)(farg1);
  arg2 = (sunrealtype *)(farg2);
  arg3 = (N_Vector)(farg3);
  arg4 = (int)(*farg4);
  arg5 = (int)(*farg5);
  arg6 = (void *)(farg6);
  result = (SUNErrCode)SUNQRAdd_MGS(arg1,arg2,arg3,arg4,arg5,arg6);
  fresult = (SUNErrCode)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNQRAdd_ICWY(void *farg1, double *farg2, N_Vector farg3, int const *farg4, int const *farg5, void *farg6) {
  int fresult ;
  N_Vector *arg1 = (N_Vector *) 0 ;
  sunrealtype *arg2 = (sunrealtype *) 0 ;
  N_Vector arg3 = (N_Vector) 0 ;
  int arg4 ;
  int arg5 ;
  void *arg6 = (void *) 0 ;
  SUNErrCode result;
  
  arg1 = (N_Vector *)(farg1);
  arg2 = (sunrealtype *)(farg2);
  arg3 = (N_Vector)(farg3);
  arg4 = (int)(*farg4);
  arg5 = (int)(*farg5);
  arg6 = (void *)(farg6);
  result = (SUNErrCode)SUNQRAdd_ICWY(arg1,arg2,arg3,arg4,arg5,arg6);
  fresult = (SUNErrCode)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNQRAdd_ICWY_SB(void *farg1, double *farg2, N_Vector farg3, int const *farg4, int const *farg5, void *farg6) {
  int fresult ;
  N_Vector *arg1 = (N_Vector *) 0 ;
  sunrealtype *arg2 = (sunrealtype *) 0 ;
  N_Vector arg3 = (N_Vector) 0 ;
  int arg4 ;
  int arg5 ;
  void *arg6 = (void *) 0 ;
  SUNErrCode result;
  
  arg1 = (N_Vector *)(farg1);
  arg2 = (sunrealtype *)(farg2);
  arg3 = (N_Vector)(farg3);
  arg4 = (int)(*farg4);
  arg5 = (int)(*farg5);
  arg6 = (void *)(farg6);
  result = (SUNErrCode)SUNQRAdd_ICWY_SB(arg1,arg2,arg3,arg4,arg5,arg6);
  fresult = (SUNErrCode)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNQRAdd_CGS2(void *farg1, double *farg2, N_Vector farg3, int const *farg4, int const *farg5, void *farg6) {
  int fresult ;
  N_Vector *arg1 = (N_Vector *) 0 ;
  sunrealtype *arg2 = (sunrealtype *) 0 ;
  N_Vector arg3 = (N_Vector) 0 ;
  int arg4 ;
  int arg5 ;
  void *arg6 = (void *) 0 ;
  SUNErrCode result;
  
  arg1 = (N_Vector *)(farg1);
  arg2 = (sunrealtype *)(farg2);
  arg3 = (N_Vector)(farg3);
  arg4 = (int)(*farg4);
  arg5 = (int)(*farg5);
  arg6 = (void *)(farg6);
  result = (SUNErrCode)SUNQRAdd_CGS2(arg1,arg2,arg3,arg4,arg5,arg6);
  fresult = (SUNErrCode)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNQRAdd_DCGS2(void *farg1, double *farg2, N_Vector farg3, int const *farg4, int const *farg5, void *farg6) {
  int fresult ;
  N_Vector *arg1 = (N_Vector *) 0 ;
  sunrealtype *arg2 = (sunrealtype *) 0 ;
  N_Vector arg3 = (N_Vector) 0 ;
  int arg4 ;
  int arg5 ;
  void *arg6 = (void *) 0 ;
  SUNErrCode result;
  
  arg1 = (N_Vector *)(farg1);
  arg2 = (sunrealtype *)(farg2);
  arg3 = (N_Vector)(farg3);
  arg4 = (int)(*farg4);
  arg5 = (int)(*farg5);
  arg6 = (void *)(farg6);
  result = (SUNErrCode)SUNQRAdd_DCGS2(arg1,arg2,arg3,arg4,arg5,arg6);
  fresult = (SUNErrCode)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNQRAdd_DCGS2_SB(void *farg1, double *farg2, N_Vector farg3, int const *farg4, int const *farg5, void *farg6) {
  int fresult ;
  N_Vector *arg1 = (N_Vector *) 0 ;
  sunrealtype *arg2 = (sunrealtype *) 0 ;
  N_Vector arg3 = (N_Vector) 0 ;
  int arg4 ;
  int arg5 ;
  void *arg6 = (void *) 0 ;
  SUNErrCode result;
  
  arg1 = (N_Vector *)(farg1);
  arg2 = (sunrealtype *)(farg2);
  arg3 = (N_Vector)(farg3);
  arg4 = (int)(*farg4);
  arg5 = (int)(*farg5);
  arg6 = (void *)(farg6);
  result = (SUNErrCode)SUNQRAdd_DCGS2_SB(arg1,arg2,arg3,arg4,arg5,arg6);
  fresult = (SUNErrCode)(result);
  return fresult;
}


SWIGEXPORT SUNLinearSolver _wrap_FSUNLinSolNewEmpty(void *farg1) {
  SUNLinearSolver fresult ;
  SUNContext arg1 = (SUNContext) 0 ;
  SUNLinearSolver result;
  
  arg1 = (SUNContext)(farg1);
  result = (SUNLinearSolver)SUNLinSolNewEmpty(arg1);
  fresult = result;
  return fresult;
}


SWIGEXPORT void _wrap_FSUNLinSolFreeEmpty(SUNLinearSolver farg1) {
  SUNLinearSolver arg1 = (SUNLinearSolver) 0 ;
  
  arg1 = (SUNLinearSolver)(farg1);
  SUNLinSolFreeEmpty(arg1);
}


SWIGEXPORT int _wrap_FSUNLinSolGetType(SUNLinearSolver farg1) {
  int fresult ;
  SUNLinearSolver arg1 = (SUNLinearSolver) 0 ;
  SUNLinearSolver_Type result;
  
  arg1 = (SUNLinearSolver)(farg1);
  result = (SUNLinearSolver_Type)SUNLinSolGetType(arg1);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNLinSolGetID(SUNLinearSolver farg1) {
  int fresult ;
  SUNLinearSolver arg1 = (SUNLinearSolver) 0 ;
  SUNLinearSolver_ID result;
  
  arg1 = (SUNLinearSolver)(farg1);
  result = (SUNLinearSolver_ID)SUNLinSolGetID(arg1);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNLinSolSetATimes(SUNLinearSolver farg1, void *farg2, SUNATimesFn farg3) {
  int fresult ;
  SUNLinearSolver arg1 = (SUNLinearSolver) 0 ;
  void *arg2 = (void *) 0 ;
  SUNATimesFn arg3 = (SUNATimesFn) 0 ;
  SUNErrCode result;
  
  arg1 = (SUNLinearSolver)(farg1);
  arg2 = (void *)(farg2);
  arg3 = (SUNATimesFn)(farg3);
  result = (SUNErrCode)SUNLinSolSetATimes(arg1,arg2,arg3);
  fresult = (SUNErrCode)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNLinSolSetPreconditioner(SUNLinearSolver farg1, void *farg2, SUNPSetupFn farg3, SUNPSolveFn farg4) {
  int fresult ;
  SUNLinearSolver arg1 = (SUNLinearSolver) 0 ;
  void *arg2 = (void *) 0 ;
  SUNPSetupFn arg3 = (SUNPSetupFn) 0 ;
  SUNPSolveFn arg4 = (SUNPSolveFn) 0 ;
  SUNErrCode result;
  
  arg1 = (SUNLinearSolver)(farg1);
  arg2 = (void *)(farg2);
  arg3 = (SUNPSetupFn)(farg3);
  arg4 = (SUNPSolveFn)(farg4);
  result = (SUNErrCode)SUNLinSolSetPreconditioner(arg1,arg2,arg3,arg4);
  fresult = (SUNErrCode)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNLinSolSetScalingVectors(SUNLinearSolver farg1, N_Vector farg2, N_Vector farg3) {
  int fresult ;
  SUNLinearSolver arg1 = (SUNLinearSolver) 0 ;
  N_Vector arg2 = (N_Vector) 0 ;
  N_Vector arg3 = (N_Vector) 0 ;
  SUNErrCode result;
  
  arg1 = (SUNLinearSolver)(farg1);
  arg2 = (N_Vector)(farg2);
  arg3 = (N_Vector)(farg3);
  result = (SUNErrCode)SUNLinSolSetScalingVectors(arg1,arg2,arg3);
  fresult = (SUNErrCode)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNLinSolSetZeroGuess(SUNLinearSolver farg1, int const *farg2) {
  int fresult ;
  SUNLinearSolver arg1 = (SUNLinearSolver) 0 ;
  int arg2 ;
  SUNErrCode result;
  
  arg1 = (SUNLinearSolver)(farg1);
  arg2 = (int)(*farg2);
  result = (SUNErrCode)SUNLinSolSetZeroGuess(arg1,arg2);
  fresult = (SUNErrCode)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNLinSolInitialize(SUNLinearSolver farg1) {
  int fresult ;
  SUNLinearSolver arg1 = (SUNLinearSolver) 0 ;
  SUNErrCode result;
  
  arg1 = (SUNLinearSolver)(farg1);
  result = (SUNErrCode)SUNLinSolInitialize(arg1);
  fresult = (SUNErrCode)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNLinSolSetup(SUNLinearSolver farg1, SUNMatrix farg2) {
  int fresult ;
  SUNLinearSolver arg1 = (SUNLinearSolver) 0 ;
  SUNMatrix arg2 = (SUNMatrix) 0 ;
  int result;
  
  arg1 = (SUNLinearSolver)(farg1);
  arg2 = (SUNMatrix)(farg2);
  result = (int)SUNLinSolSetup(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNLinSolSolve(SUNLinearSolver farg1, SUNMatrix farg2, N_Vector farg3, N_Vector farg4, double const *farg5) {
  int fresult ;
  SUNLinearSolver arg1 = (SUNLinearSolver) 0 ;
  SUNMatrix arg2 = (SUNMatrix) 0 ;
  N_Vector arg3 = (N_Vector) 0 ;
  N_Vector arg4 = (N_Vector) 0 ;
  sunrealtype arg5 ;
  int result;
  
  arg1 = (SUNLinearSolver)(farg1);
  arg2 = (SUNMatrix)(farg2);
  arg3 = (N_Vector)(farg3);
  arg4 = (N_Vector)(farg4);
  arg5 = (sunrealtype)(*farg5);
  result = (int)SUNLinSolSolve(arg1,arg2,arg3,arg4,arg5);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNLinSolNumIters(SUNLinearSolver farg1) {
  int fresult ;
  SUNLinearSolver arg1 = (SUNLinearSolver) 0 ;
  int result;
  
  arg1 = (SUNLinearSolver)(farg1);
  result = (int)SUNLinSolNumIters(arg1);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT double _wrap_FSUNLinSolResNorm(SUNLinearSolver farg1) {
  double fresult ;
  SUNLinearSolver arg1 = (SUNLinearSolver) 0 ;
  sunrealtype result;
  
  arg1 = (SUNLinearSolver)(farg1);
  result = (sunrealtype)SUNLinSolResNorm(arg1);
  fresult = (sunrealtype)(result);
  return fresult;
}


SWIGEXPORT N_Vector _wrap_FSUNLinSolResid(SUNLinearSolver farg1) {
  N_Vector fresult ;
  SUNLinearSolver arg1 = (SUNLinearSolver) 0 ;
  N_Vector result;
  
  arg1 = (SUNLinearSolver)(farg1);
  result = (N_Vector)SUNLinSolResid(arg1);
  fresult = result;
  return fresult;
}


SWIGEXPORT int64_t _wrap_FSUNLinSolLastFlag(SUNLinearSolver farg1) {
  int64_t fresult ;
  SUNLinearSolver arg1 = (SUNLinearSolver) 0 ;
  sunindextype result;
  
  arg1 = (SUNLinearSolver)(farg1);
  result = SUNLinSolLastFlag(arg1);
  fresult = (sunindextype)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNLinSolSpace(SUNLinearSolver farg1, long *farg2, long *farg3) {
  int fresult ;
  SUNLinearSolver arg1 = (SUNLinearSolver) 0 ;
  long *arg2 = (long *) 0 ;
  long *arg3 = (long *) 0 ;
  SUNErrCode result;
  
  arg1 = (SUNLinearSolver)(farg1);
  arg2 = (long *)(farg2);
  arg3 = (long *)(farg3);
  result = (SUNErrCode)SUNLinSolSpace(arg1,arg2,arg3);
  fresult = (SUNErrCode)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNLinSolFree(SUNLinearSolver farg1) {
  int fresult ;
  SUNLinearSolver arg1 = (SUNLinearSolver) 0 ;
  SUNErrCode result;
  
  arg1 = (SUNLinearSolver)(farg1);
  result = (SUNErrCode)SUNLinSolFree(arg1);
  fresult = (SUNErrCode)(result);
  return fresult;
}



