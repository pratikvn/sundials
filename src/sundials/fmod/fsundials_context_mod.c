/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.0
 *
 * This file is not intended to be easily readable and contains a number of
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG
 * interface file instead.
 * ----------------------------------------------------------------------------- */

/* ---------------------------------------------------------------
 * Programmer(s): Auto-generated by swig.
 * ---------------------------------------------------------------
 * SUNDIALS Copyright Start
 * Copyright (c) 2002-2023, Lawrence Livermore National Security
 * and Southern Methodist University.
 * All rights reserved.
 *
 * See the top-level LICENSE and NOTICE files for details.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * SUNDIALS Copyright End
 * -------------------------------------------------------------*/

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


enum {
    SWIG_MEM_OWN = 0x01,
    SWIG_MEM_RVALUE = 0x02,
    SWIG_MEM_CONST = 0x04
};


#define SWIG_check_mutable(SWIG_CLASS_WRAPPER, TYPENAME, FNAME, FUNCNAME, RETURNNULL) \
    if ((SWIG_CLASS_WRAPPER).cmemflags & SWIG_MEM_CONST) { \
        SWIG_exception_impl(FUNCNAME, SWIG_TypeError, \
            "Cannot pass const " TYPENAME " (class " FNAME ") " \
            "as a mutable reference", \
            RETURNNULL); \
    }


#define SWIG_check_nonnull(SWIG_CLASS_WRAPPER, TYPENAME, FNAME, FUNCNAME, RETURNNULL) \
  if (!(SWIG_CLASS_WRAPPER).cptr) { \
    SWIG_exception_impl(FUNCNAME, SWIG_TypeError, \
                        "Cannot pass null " TYPENAME " (class " FNAME ") " \
                        "as a reference", RETURNNULL); \
  }


#define SWIG_check_mutable_nonnull(SWIG_CLASS_WRAPPER, TYPENAME, FNAME, FUNCNAME, RETURNNULL) \
    SWIG_check_nonnull(SWIG_CLASS_WRAPPER, TYPENAME, FNAME, FUNCNAME, RETURNNULL); \
    SWIG_check_mutable(SWIG_CLASS_WRAPPER, TYPENAME, FNAME, FUNCNAME, RETURNNULL);


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


#include "sundials/sundials_context.h"


typedef struct {
    void* cptr;
    int cmemflags;
} SwigClassWrapper;


SWIGINTERN SwigClassWrapper SwigClassWrapper_uninitialized() {
    SwigClassWrapper result;
    result.cptr = NULL;
    result.cmemflags = 0;
    return result;
}


#include <stdlib.h>
#ifdef _MSC_VER
# ifndef strtoull
#  define strtoull _strtoui64
# endif
# ifndef strtoll
#  define strtoll _strtoi64
# endif
#endif


#include <string.h>


SWIGINTERN void SWIG_assign(SwigClassWrapper* self, SwigClassWrapper other) {
  if (self->cptr == NULL) {
    /* LHS is unassigned */
    if (other.cmemflags & SWIG_MEM_RVALUE) {
      /* Capture pointer from RHS, clear 'moving' flag */
      self->cptr = other.cptr;
      self->cmemflags = other.cmemflags & (~SWIG_MEM_RVALUE);
    } else {
      /* Become a reference to the other object */
      self->cptr = other.cptr;
      self->cmemflags = other.cmemflags & (~SWIG_MEM_OWN);
    }
  } else if (other.cptr == NULL) {
    /* Replace LHS with a null pointer */
    free(self->cptr);
    *self = SwigClassWrapper_uninitialized();
  } else {
    if (self->cmemflags & SWIG_MEM_OWN) {
      free(self->cptr);
    }
    self->cptr = other.cptr;
    if (other.cmemflags & SWIG_MEM_RVALUE) {
      /* Capture RHS */
      self->cmemflags = other.cmemflags & ~SWIG_MEM_RVALUE;
    } else {
      /* Point to RHS */
      self->cmemflags = other.cmemflags & ~SWIG_MEM_OWN;
    }
  }
}

SWIGEXPORT void _wrap_SUNContext__profiler_set(SwigClassWrapper const *farg1, void *farg2) {
  struct SUNContext_ *arg1 = (struct SUNContext_ *) 0 ;
  SUNProfiler arg2 ;
  
  SWIG_check_mutable_nonnull(*farg1, "struct SUNContext_ *", "SUNContext_", "SUNContext_::profiler", return );
  arg1 = (struct SUNContext_ *)(farg1->cptr);
  arg2 = (SUNProfiler)(farg2);
  if (arg1) (arg1)->profiler = arg2;
}


SWIGEXPORT void * _wrap_SUNContext__profiler_get(SwigClassWrapper const *farg1) {
  void * fresult ;
  struct SUNContext_ *arg1 = (struct SUNContext_ *) 0 ;
  SUNProfiler result;
  
  SWIG_check_mutable_nonnull(*farg1, "struct SUNContext_ *", "SUNContext_", "SUNContext_::profiler", return 0);
  arg1 = (struct SUNContext_ *)(farg1->cptr);
  result =  ((arg1)->profiler);
  fresult = result;
  return fresult;
}


SWIGEXPORT void _wrap_SUNContext__own_profiler_set(SwigClassWrapper const *farg1, int const *farg2) {
  struct SUNContext_ *arg1 = (struct SUNContext_ *) 0 ;
  int arg2 ;
  
  SWIG_check_mutable_nonnull(*farg1, "struct SUNContext_ *", "SUNContext_", "SUNContext_::own_profiler", return );
  arg1 = (struct SUNContext_ *)(farg1->cptr);
  arg2 = (int)(*farg2);
  if (arg1) (arg1)->own_profiler = arg2;
}


SWIGEXPORT int _wrap_SUNContext__own_profiler_get(SwigClassWrapper const *farg1) {
  int fresult ;
  struct SUNContext_ *arg1 = (struct SUNContext_ *) 0 ;
  int result;
  
  SWIG_check_mutable_nonnull(*farg1, "struct SUNContext_ *", "SUNContext_", "SUNContext_::own_profiler", return 0);
  arg1 = (struct SUNContext_ *)(farg1->cptr);
  result = (int) ((arg1)->own_profiler);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT void _wrap_SUNContext__logger_set(SwigClassWrapper const *farg1, void *farg2) {
  struct SUNContext_ *arg1 = (struct SUNContext_ *) 0 ;
  SUNLogger arg2 ;
  
  SWIG_check_mutable_nonnull(*farg1, "struct SUNContext_ *", "SUNContext_", "SUNContext_::logger", return );
  arg1 = (struct SUNContext_ *)(farg1->cptr);
  arg2 = (SUNLogger)(farg2);
  if (arg1) (arg1)->logger = arg2;
}


SWIGEXPORT void * _wrap_SUNContext__logger_get(SwigClassWrapper const *farg1) {
  void * fresult ;
  struct SUNContext_ *arg1 = (struct SUNContext_ *) 0 ;
  SUNLogger result;
  
  SWIG_check_mutable_nonnull(*farg1, "struct SUNContext_ *", "SUNContext_", "SUNContext_::logger", return 0);
  arg1 = (struct SUNContext_ *)(farg1->cptr);
  result =  ((arg1)->logger);
  fresult = result;
  return fresult;
}


SWIGEXPORT void _wrap_SUNContext__own_logger_set(SwigClassWrapper const *farg1, int const *farg2) {
  struct SUNContext_ *arg1 = (struct SUNContext_ *) 0 ;
  int arg2 ;
  
  SWIG_check_mutable_nonnull(*farg1, "struct SUNContext_ *", "SUNContext_", "SUNContext_::own_logger", return );
  arg1 = (struct SUNContext_ *)(farg1->cptr);
  arg2 = (int)(*farg2);
  if (arg1) (arg1)->own_logger = arg2;
}


SWIGEXPORT int _wrap_SUNContext__own_logger_get(SwigClassWrapper const *farg1) {
  int fresult ;
  struct SUNContext_ *arg1 = (struct SUNContext_ *) 0 ;
  int result;
  
  SWIG_check_mutable_nonnull(*farg1, "struct SUNContext_ *", "SUNContext_", "SUNContext_::own_logger", return 0);
  arg1 = (struct SUNContext_ *)(farg1->cptr);
  result = (int) ((arg1)->own_logger);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT void _wrap_SUNContext__last_err_set(SwigClassWrapper const *farg1, int const *farg2) {
  struct SUNContext_ *arg1 = (struct SUNContext_ *) 0 ;
  SUNErrCode arg2 ;
  
  SWIG_check_mutable_nonnull(*farg1, "struct SUNContext_ *", "SUNContext_", "SUNContext_::last_err", return );
  arg1 = (struct SUNContext_ *)(farg1->cptr);
  arg2 = (SUNErrCode)(*farg2);
  if (arg1) (arg1)->last_err = arg2;
}


SWIGEXPORT int _wrap_SUNContext__last_err_get(SwigClassWrapper const *farg1) {
  int fresult ;
  struct SUNContext_ *arg1 = (struct SUNContext_ *) 0 ;
  SUNErrCode result;
  
  SWIG_check_mutable_nonnull(*farg1, "struct SUNContext_ *", "SUNContext_", "SUNContext_::last_err", return 0);
  arg1 = (struct SUNContext_ *)(farg1->cptr);
  result = (SUNErrCode) ((arg1)->last_err);
  fresult = (SUNErrCode)(result);
  return fresult;
}


SWIGEXPORT void _wrap_SUNContext__err_handler_set(SwigClassWrapper const *farg1, SwigClassWrapper const *farg2) {
  struct SUNContext_ *arg1 = (struct SUNContext_ *) 0 ;
  struct SUNErrHandler_ *arg2 = (struct SUNErrHandler_ *) 0 ;
  
  SWIG_check_mutable_nonnull(*farg1, "struct SUNContext_ *", "SUNContext_", "SUNContext_::err_handler", return );
  arg1 = (struct SUNContext_ *)(farg1->cptr);
  SWIG_check_mutable(*farg2, "struct SUNErrHandler_ *", "SWIGTYPE_p_SUNErrHandler_", "SUNContext_::err_handler", return );
  arg2 = (struct SUNErrHandler_ *)(farg2->cptr);
  if (arg1) (arg1)->err_handler = arg2;
}


SWIGEXPORT SwigClassWrapper _wrap_SUNContext__err_handler_get(SwigClassWrapper const *farg1) {
  SwigClassWrapper fresult ;
  struct SUNContext_ *arg1 = (struct SUNContext_ *) 0 ;
  struct SUNErrHandler_ *result = 0 ;
  
  SWIG_check_mutable_nonnull(*farg1, "struct SUNContext_ *", "SUNContext_", "SUNContext_::err_handler", return SwigClassWrapper_uninitialized());
  arg1 = (struct SUNContext_ *)(farg1->cptr);
  result = (struct SUNErrHandler_ *) ((arg1)->err_handler);
  fresult.cptr = result;
  fresult.cmemflags = SWIG_MEM_RVALUE | (0 ? SWIG_MEM_OWN : 0);
  return fresult;
}


SWIGEXPORT void _wrap_SUNContext__comm_set(SwigClassWrapper const *farg1, void *farg2) {
  struct SUNContext_ *arg1 = (struct SUNContext_ *) 0 ;
  void *arg2 = (void *) 0 ;
  
  SWIG_check_mutable_nonnull(*farg1, "struct SUNContext_ *", "SUNContext_", "SUNContext_::comm", return );
  arg1 = (struct SUNContext_ *)(farg1->cptr);
  arg2 = (void *)(farg2);
  if (arg1) (arg1)->comm = arg2;
}


SWIGEXPORT void * _wrap_SUNContext__comm_get(SwigClassWrapper const *farg1) {
  void * fresult ;
  struct SUNContext_ *arg1 = (struct SUNContext_ *) 0 ;
  void *result = 0 ;
  
  SWIG_check_mutable_nonnull(*farg1, "struct SUNContext_ *", "SUNContext_", "SUNContext_::comm", return 0);
  arg1 = (struct SUNContext_ *)(farg1->cptr);
  result = (void *) ((arg1)->comm);
  fresult = result;
  return fresult;
}


SWIGEXPORT SwigClassWrapper _wrap_new_SUNContext_() {
  SwigClassWrapper fresult ;
  struct SUNContext_ *result = 0 ;
  
  result = (struct SUNContext_ *)calloc(1, sizeof(struct SUNContext_));
  fresult.cptr = result;
  fresult.cmemflags = SWIG_MEM_RVALUE | (1 ? SWIG_MEM_OWN : 0);
  return fresult;
}


SWIGEXPORT void _wrap_delete_SUNContext_(SwigClassWrapper *farg1) {
  struct SUNContext_ *arg1 = (struct SUNContext_ *) 0 ;
  
  SWIG_check_mutable(*farg1, "struct SUNContext_ *", "SUNContext_", "SUNContext_::~SUNContext_()", return );
  arg1 = (struct SUNContext_ *)(farg1->cptr);
  free((char *) arg1);
}


SWIGEXPORT void _wrap_SUNContext__op_assign__(SwigClassWrapper *farg1, SwigClassWrapper const *farg2) {
  struct SUNContext_ *arg1 = (struct SUNContext_ *) 0 ;
  struct SUNContext_ *arg2 = 0 ;
  
  (void)sizeof(arg1);
  (void)sizeof(arg2);
  SWIG_assign(farg1, *farg2);
  
}


SWIGEXPORT int _wrap_FSUNContext_GetLastError(void *farg1, int *farg2) {
  int fresult ;
  SUNContext arg1 = (SUNContext) 0 ;
  SUNErrCode *arg2 = (SUNErrCode *) 0 ;
  SUNErrCode result;
  
  arg1 = (SUNContext)(farg1);
  arg2 = (SUNErrCode *)(farg2);
  result = (SUNErrCode)SUNContext_GetLastError(arg1,arg2);
  fresult = (SUNErrCode)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNContext_ClearLastError(void *farg1) {
  int fresult ;
  SUNContext arg1 = (SUNContext) 0 ;
  SUNErrCode result;
  
  arg1 = (SUNContext)(farg1);
  result = (SUNErrCode)SUNContext_ClearLastError(arg1);
  fresult = (SUNErrCode)(result);
  return fresult;
}


SWIGEXPORT SwigClassWrapper _wrap_FSUNContext_PushErrHandler(void *farg1, int (*farg2)(int,char const *,char const *,char const *,SUNErrCode,void *,struct SUNContext_ *), void *farg3) {
  SwigClassWrapper fresult ;
  SUNContext arg1 = (SUNContext) 0 ;
  int (*arg2)(int,char const *,char const *,char const *,SUNErrCode,void *,struct SUNContext_ *) = (int (*)(int,char const *,char const *,char const *,SUNErrCode,void *,struct SUNContext_ *)) 0 ;
  void *arg3 = (void *) 0 ;
  struct SUNErrHandler_ *result = 0 ;
  
  arg1 = (SUNContext)(farg1);
  arg2 = (int (*)(int,char const *,char const *,char const *,SUNErrCode,void *,struct SUNContext_ *))(farg2);
  arg3 = (void *)(farg3);
  result = (struct SUNErrHandler_ *)SUNContext_PushErrHandler(arg1,arg2,arg3);
  fresult.cptr = result;
  fresult.cmemflags = SWIG_MEM_RVALUE | (0 ? SWIG_MEM_OWN : 0);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNContext_PopErrHandler(void *farg1) {
  int fresult ;
  SUNContext arg1 = (SUNContext) 0 ;
  SUNErrCode result;
  
  arg1 = (SUNContext)(farg1);
  result = (SUNErrCode)SUNContext_PopErrHandler(arg1);
  fresult = (SUNErrCode)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNContext_ClearHandlers(void *farg1) {
  int fresult ;
  SUNContext arg1 = (SUNContext) 0 ;
  SUNErrCode result;
  
  arg1 = (SUNContext)(farg1);
  result = (SUNErrCode)SUNContext_ClearHandlers(arg1);
  fresult = (SUNErrCode)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNContext_GetProfiler(void *farg1, void *farg2) {
  int fresult ;
  SUNContext arg1 = (SUNContext) 0 ;
  SUNProfiler *arg2 = (SUNProfiler *) 0 ;
  SUNErrCode result;
  
  arg1 = (SUNContext)(farg1);
  arg2 = (SUNProfiler *)(farg2);
  result = (SUNErrCode)SUNContext_GetProfiler(arg1,arg2);
  fresult = (SUNErrCode)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNContext_SetProfiler(void *farg1, void *farg2) {
  int fresult ;
  SUNContext arg1 = (SUNContext) 0 ;
  SUNProfiler arg2 ;
  SUNErrCode result;
  
  arg1 = (SUNContext)(farg1);
  arg2 = (SUNProfiler)(farg2);
  result = (SUNErrCode)SUNContext_SetProfiler(arg1,arg2);
  fresult = (SUNErrCode)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNContext_GetLogger(void *farg1, void *farg2) {
  int fresult ;
  SUNContext arg1 = (SUNContext) 0 ;
  SUNLogger *arg2 = (SUNLogger *) 0 ;
  SUNErrCode result;
  
  arg1 = (SUNContext)(farg1);
  arg2 = (SUNLogger *)(farg2);
  result = (SUNErrCode)SUNContext_GetLogger(arg1,arg2);
  fresult = (SUNErrCode)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNContext_SetLogger(void *farg1, void *farg2) {
  int fresult ;
  SUNContext arg1 = (SUNContext) 0 ;
  SUNLogger arg2 ;
  SUNErrCode result;
  
  arg1 = (SUNContext)(farg1);
  arg2 = (SUNLogger)(farg2);
  result = (SUNErrCode)SUNContext_SetLogger(arg1,arg2);
  fresult = (SUNErrCode)(result);
  return fresult;
}



SWIGEXPORT int _wrap_FSUNContext_Free(void *farg1) {
  int fresult ;
  SUNContext *arg1 = (SUNContext *) 0 ;
  int result;
#ifdef SUNDIALS_BUILD_WITH_PROFILING
  SUNProfiler profiler;
#endif

  arg1 = (SUNContext *)(farg1);
#ifdef SUNDIALS_BUILD_WITH_PROFILING
  result = (int)SUNContext_GetProfiler(*arg1,&profiler);
  result = (int)SUNContext_Free(arg1);
  result = (int)SUNProfiler_Free(&profiler);
#else
  result = (int)SUNContext_Free(arg1);
#endif
  fresult = (int)(result);
  return fresult;
}

SWIGEXPORT int _wrap_FSUNContext_Create(void *farg1, void *farg2) {
  int fresult ;
  void *arg1 = (void *) 0 ;
  SUNContext *arg2 = (SUNContext *) 0 ;
  int result;

  arg1 = (void *)(farg1);
  arg2 = (SUNContext *)(farg2);
  result = (int)SUNContext_Create(arg1,arg2);
  fresult = (int)(result);
  return fresult;
}


