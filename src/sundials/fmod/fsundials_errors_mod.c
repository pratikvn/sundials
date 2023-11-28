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


#include "sundials/sundials_errors.h"


#include <stdlib.h>
#ifdef _MSC_VER
# ifndef strtoull
#  define strtoull _strtoui64
# endif
# ifndef strtoll
#  define strtoll _strtoi64
# endif
#endif


typedef struct {
    void* data;
    size_t size;
} SwigArrayWrapper;


SWIGINTERN SwigArrayWrapper SwigArrayWrapper_uninitialized() {
  SwigArrayWrapper result;
  result.data = NULL;
  result.size = 0;
  return result;
}


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


#include <string.h>

SWIGEXPORT int _wrap_FSUNLogErrHandlerFn(int const *farg1, SwigArrayWrapper *farg2, SwigArrayWrapper *farg3, SwigArrayWrapper *farg4, int const *farg5, void *farg6, SwigClassWrapper const *farg7) {
  int fresult ;
  int arg1 ;
  char *arg2 = (char *) 0 ;
  char *arg3 = (char *) 0 ;
  char *arg4 = (char *) 0 ;
  SUNErrCode arg5 ;
  void *arg6 = (void *) 0 ;
  SUNContext arg7 = (SUNContext) 0 ;
  int result;
  
  arg1 = (int)(*farg1);
  arg2 = (char *)(farg2->data);
  arg3 = (char *)(farg3->data);
  arg4 = (char *)(farg4->data);
  arg5 = (SUNErrCode)(*farg5);
  arg6 = (void *)(farg6);
  SWIG_check_mutable(*farg7, "SUNContext", "SWIGTYPE_p_SUNContext_", "SUNLogErrHandlerFn(int,char const *,char const *,char const *,SUNErrCode,void *,SUNContext)", return 0);
  arg7 = (SUNContext)(farg7->cptr);
  result = (int)SUNLogErrHandlerFn(arg1,(char const *)arg2,(char const *)arg3,(char const *)arg4,arg5,arg6,arg7);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNAbortErrHandlerFn(int const *farg1, SwigArrayWrapper *farg2, SwigArrayWrapper *farg3, SwigArrayWrapper *farg4, int const *farg5, void *farg6, SwigClassWrapper const *farg7) {
  int fresult ;
  int arg1 ;
  char *arg2 = (char *) 0 ;
  char *arg3 = (char *) 0 ;
  char *arg4 = (char *) 0 ;
  SUNErrCode arg5 ;
  void *arg6 = (void *) 0 ;
  SUNContext arg7 = (SUNContext) 0 ;
  int result;
  
  arg1 = (int)(*farg1);
  arg2 = (char *)(farg2->data);
  arg3 = (char *)(farg3->data);
  arg4 = (char *)(farg4->data);
  arg5 = (SUNErrCode)(*farg5);
  arg6 = (void *)(farg6);
  SWIG_check_mutable(*farg7, "SUNContext", "SWIGTYPE_p_SUNContext_", "SUNAbortErrHandlerFn(int,char const *,char const *,char const *,SUNErrCode,void *,SUNContext)", return 0);
  arg7 = (SUNContext)(farg7->cptr);
  result = (int)SUNAbortErrHandlerFn(arg1,(char const *)arg2,(char const *)arg3,(char const *)arg4,arg5,arg6,arg7);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_FSUNAssertErrHandlerFn(int const *farg1, SwigArrayWrapper *farg2, SwigArrayWrapper *farg3, SwigArrayWrapper *farg4, int const *farg5, void *farg6, SwigClassWrapper const *farg7) {
  int fresult ;
  int arg1 ;
  char *arg2 = (char *) 0 ;
  char *arg3 = (char *) 0 ;
  char *arg4 = (char *) 0 ;
  SUNErrCode arg5 ;
  void *arg6 = (void *) 0 ;
  SUNContext arg7 = (SUNContext) 0 ;
  int result;
  
  arg1 = (int)(*farg1);
  arg2 = (char *)(farg2->data);
  arg3 = (char *)(farg3->data);
  arg4 = (char *)(farg4->data);
  arg5 = (SUNErrCode)(*farg5);
  arg6 = (void *)(farg6);
  SWIG_check_mutable(*farg7, "SUNContext", "SWIGTYPE_p_SUNContext_", "SUNAssertErrHandlerFn(int,char const *,char const *,char const *,SUNErrCode,void *,SUNContext)", return 0);
  arg7 = (SUNContext)(farg7->cptr);
  result = (int)SUNAssertErrHandlerFn(arg1,(char const *)arg2,(char const *)arg3,(char const *)arg4,arg5,arg6,arg7);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT SwigArrayWrapper _wrap_FSUNGetErrMsg(int const *farg1, SwigClassWrapper const *farg2) {
  SwigArrayWrapper fresult ;
  SUNErrCode arg1 ;
  SUNContext arg2 = (SUNContext) 0 ;
  char *result = 0 ;
  
  arg1 = (SUNErrCode)(*farg1);
  SWIG_check_mutable(*farg2, "SUNContext", "SWIGTYPE_p_SUNContext_", "SUNGetErrMsg(SUNErrCode,SUNContext)", return SwigArrayWrapper_uninitialized());
  arg2 = (SUNContext)(farg2->cptr);
  result = (char *)SUNGetErrMsg(arg1,arg2);
  fresult.size = strlen((const char*)(result));
  fresult.data = (char *)(result);
  return fresult;
}



