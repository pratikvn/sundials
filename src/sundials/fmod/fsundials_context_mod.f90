! This file was automatically generated by SWIG (http://www.swig.org).
! Version 4.0.0
!
! Do not make changes to this file unless you know what you are doing--modify
! the SWIG interface file instead.

! ---------------------------------------------------------------
! Programmer(s): Auto-generated by swig.
! ---------------------------------------------------------------
! SUNDIALS Copyright Start
! Copyright (c) 2002-2023, Lawrence Livermore National Security
! and Southern Methodist University.
! All rights reserved.
!
! See the top-level LICENSE and NOTICE files for details.
!
! SPDX-License-Identifier: BSD-3-Clause
! SUNDIALS Copyright End
! ---------------------------------------------------------------


#include "sundials/sundials_config.h"

module fsundials_context_mod
 use, intrinsic :: ISO_C_BINDING
 use fsundials_types_mod
 implicit none
 private

 ! DECLARATION CONSTRUCTS

 integer, parameter :: swig_cmem_own_bit = 0
 integer, parameter :: swig_cmem_rvalue_bit = 1
 integer, parameter :: swig_cmem_const_bit = 2
 type, bind(C) :: SwigClassWrapper
  type(C_PTR), public :: cptr = C_NULL_PTR
  integer(C_INT), public :: cmemflags = 0
 end type
 type, public :: SWIGTYPE_p_SUNErrHandler_
  type(SwigClassWrapper), public :: swigdata
 end type
 ! struct struct SUNContext_
 type, public :: SUNContext_
  type(SwigClassWrapper), public :: swigdata
 contains
  procedure :: set_profiler => swigf_SUNContext__profiler_set
  procedure :: get_profiler => swigf_SUNContext__profiler_get
  procedure :: set_own_profiler => swigf_SUNContext__own_profiler_set
  procedure :: get_own_profiler => swigf_SUNContext__own_profiler_get
  procedure :: set_logger => swigf_SUNContext__logger_set
  procedure :: get_logger => swigf_SUNContext__logger_get
  procedure :: set_own_logger => swigf_SUNContext__own_logger_set
  procedure :: get_own_logger => swigf_SUNContext__own_logger_get
  procedure :: set_last_err => swigf_SUNContext__last_err_set
  procedure :: get_last_err => swigf_SUNContext__last_err_get
  procedure :: set_err_handler => swigf_SUNContext__err_handler_set
  procedure :: get_err_handler => swigf_SUNContext__err_handler_get
  procedure :: set_comm => swigf_SUNContext__comm_set
  procedure :: get_comm => swigf_SUNContext__comm_get
  procedure :: release => swigf_release_SUNContext_
  procedure, private :: swigf_SUNContext__op_assign__
  generic :: assignment(=) => swigf_SUNContext__op_assign__
 end type SUNContext_
 interface SUNContext_
  module procedure swigf_create_SUNContext_
 end interface
 public :: FSUNContext_GetLastError
 public :: FSUNContext_PeekLastError
 public :: FSUNContext_PushErrHandler
 public :: FSUNContext_PopErrHandler
 public :: FSUNContext_ClearHandlers
 public :: FSUNContext_GetProfiler
 public :: FSUNContext_SetProfiler
 public :: FSUNContext_GetLogger
 public :: FSUNContext_SetLogger

public :: FSUNContext_Free
public :: FSUNContext_Create


! WRAPPER DECLARATIONS
interface
subroutine swigc_SUNContext__profiler_set(farg1, farg2) &
bind(C, name="_wrap_SUNContext__profiler_set")
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
type(C_PTR), value :: farg2
end subroutine

function swigc_SUNContext__profiler_get(farg1) &
bind(C, name="_wrap_SUNContext__profiler_get") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
type(C_PTR) :: fresult
end function

subroutine swigc_SUNContext__own_profiler_set(farg1, farg2) &
bind(C, name="_wrap_SUNContext__own_profiler_set")
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
integer(C_INT), intent(in) :: farg2
end subroutine

function swigc_SUNContext__own_profiler_get(farg1) &
bind(C, name="_wrap_SUNContext__own_profiler_get") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
integer(C_INT) :: fresult
end function

subroutine swigc_SUNContext__logger_set(farg1, farg2) &
bind(C, name="_wrap_SUNContext__logger_set")
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
type(C_PTR), value :: farg2
end subroutine

function swigc_SUNContext__logger_get(farg1) &
bind(C, name="_wrap_SUNContext__logger_get") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
type(C_PTR) :: fresult
end function

subroutine swigc_SUNContext__own_logger_set(farg1, farg2) &
bind(C, name="_wrap_SUNContext__own_logger_set")
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
integer(C_INT), intent(in) :: farg2
end subroutine

function swigc_SUNContext__own_logger_get(farg1) &
bind(C, name="_wrap_SUNContext__own_logger_get") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
integer(C_INT) :: fresult
end function

subroutine swigc_SUNContext__last_err_set(farg1, farg2) &
bind(C, name="_wrap_SUNContext__last_err_set")
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
integer(C_INT), intent(in) :: farg2
end subroutine

function swigc_SUNContext__last_err_get(farg1) &
bind(C, name="_wrap_SUNContext__last_err_get") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
integer(C_INT) :: fresult
end function

subroutine swigc_SUNContext__err_handler_set(farg1, farg2) &
bind(C, name="_wrap_SUNContext__err_handler_set")
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
type(SwigClassWrapper) :: farg2
end subroutine

function swigc_SUNContext__err_handler_get(farg1) &
bind(C, name="_wrap_SUNContext__err_handler_get") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
type(SwigClassWrapper) :: fresult
end function

subroutine swigc_SUNContext__comm_set(farg1, farg2) &
bind(C, name="_wrap_SUNContext__comm_set")
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
type(C_PTR), value :: farg2
end subroutine

function swigc_SUNContext__comm_get(farg1) &
bind(C, name="_wrap_SUNContext__comm_get") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: farg1
type(C_PTR) :: fresult
end function

function swigc_new_SUNContext_() &
bind(C, name="_wrap_new_SUNContext_") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper) :: fresult
end function

subroutine swigc_delete_SUNContext_(farg1) &
bind(C, name="_wrap_delete_SUNContext_")
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper), intent(inout) :: farg1
end subroutine

subroutine swigc_SUNContext__op_assign__(farg1, farg2) &
bind(C, name="_wrap_SUNContext__op_assign__")
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(SwigClassWrapper), intent(inout) :: farg1
type(SwigClassWrapper) :: farg2
end subroutine

function swigc_FSUNContext_GetLastError(farg1, farg2) &
bind(C, name="_wrap_FSUNContext_GetLastError") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNContext_PeekLastError(farg1, farg2) &
bind(C, name="_wrap_FSUNContext_PeekLastError") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNContext_PushErrHandler(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNContext_PushErrHandler") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigclasswrapper
type(C_PTR), value :: farg1
type(C_FUNPTR), value :: farg2
type(C_PTR), value :: farg3
type(SwigClassWrapper) :: fresult
end function

function swigc_FSUNContext_PopErrHandler(farg1) &
bind(C, name="_wrap_FSUNContext_PopErrHandler") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNContext_ClearHandlers(farg1) &
bind(C, name="_wrap_FSUNContext_ClearHandlers") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNContext_GetProfiler(farg1, farg2) &
bind(C, name="_wrap_FSUNContext_GetProfiler") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNContext_SetProfiler(farg1, farg2) &
bind(C, name="_wrap_FSUNContext_SetProfiler") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNContext_GetLogger(farg1, farg2) &
bind(C, name="_wrap_FSUNContext_GetLogger") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNContext_SetLogger(farg1, farg2) &
bind(C, name="_wrap_FSUNContext_SetLogger") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT) :: fresult
end function


function swigc_FSUNContext_Free(farg1) &
bind(C, name="_wrap_FSUNContext_Free") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNContext_Create(farg1, farg2) &
bind(C, name="_wrap_FSUNContext_Create") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT) :: fresult
end function


end interface


contains
 ! MODULE SUBPROGRAMS
subroutine swigf_SUNContext__profiler_set(self, profiler)
use, intrinsic :: ISO_C_BINDING
class(SUNContext_), intent(in) :: self
type(C_PTR) :: profiler
type(SwigClassWrapper) :: farg1 
type(C_PTR) :: farg2 

farg1 = self%swigdata
farg2 = profiler
call swigc_SUNContext__profiler_set(farg1, farg2)
end subroutine

function swigf_SUNContext__profiler_get(self) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(C_PTR) :: swig_result
class(SUNContext_), intent(in) :: self
type(C_PTR) :: fresult 
type(SwigClassWrapper) :: farg1 

farg1 = self%swigdata
fresult = swigc_SUNContext__profiler_get(farg1)
swig_result = fresult
end function

subroutine swigf_SUNContext__own_profiler_set(self, own_profiler)
use, intrinsic :: ISO_C_BINDING
class(SUNContext_), intent(in) :: self
integer(C_INT), intent(in) :: own_profiler
type(SwigClassWrapper) :: farg1 
integer(C_INT) :: farg2 

farg1 = self%swigdata
farg2 = own_profiler
call swigc_SUNContext__own_profiler_set(farg1, farg2)
end subroutine

function swigf_SUNContext__own_profiler_get(self) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
class(SUNContext_), intent(in) :: self
integer(C_INT) :: fresult 
type(SwigClassWrapper) :: farg1 

farg1 = self%swigdata
fresult = swigc_SUNContext__own_profiler_get(farg1)
swig_result = fresult
end function

subroutine swigf_SUNContext__logger_set(self, logger)
use, intrinsic :: ISO_C_BINDING
class(SUNContext_), intent(in) :: self
type(C_PTR) :: logger
type(SwigClassWrapper) :: farg1 
type(C_PTR) :: farg2 

farg1 = self%swigdata
farg2 = logger
call swigc_SUNContext__logger_set(farg1, farg2)
end subroutine

function swigf_SUNContext__logger_get(self) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(C_PTR) :: swig_result
class(SUNContext_), intent(in) :: self
type(C_PTR) :: fresult 
type(SwigClassWrapper) :: farg1 

farg1 = self%swigdata
fresult = swigc_SUNContext__logger_get(farg1)
swig_result = fresult
end function

subroutine swigf_SUNContext__own_logger_set(self, own_logger)
use, intrinsic :: ISO_C_BINDING
class(SUNContext_), intent(in) :: self
integer(C_INT), intent(in) :: own_logger
type(SwigClassWrapper) :: farg1 
integer(C_INT) :: farg2 

farg1 = self%swigdata
farg2 = own_logger
call swigc_SUNContext__own_logger_set(farg1, farg2)
end subroutine

function swigf_SUNContext__own_logger_get(self) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
class(SUNContext_), intent(in) :: self
integer(C_INT) :: fresult 
type(SwigClassWrapper) :: farg1 

farg1 = self%swigdata
fresult = swigc_SUNContext__own_logger_get(farg1)
swig_result = fresult
end function

subroutine swigf_SUNContext__last_err_set(self, last_err)
use, intrinsic :: ISO_C_BINDING
class(SUNContext_), intent(in) :: self
integer(C_INT), intent(in) :: last_err
type(SwigClassWrapper) :: farg1 
integer(C_INT) :: farg2 

farg1 = self%swigdata
farg2 = last_err
call swigc_SUNContext__last_err_set(farg1, farg2)
end subroutine

function swigf_SUNContext__last_err_get(self) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
class(SUNContext_), intent(in) :: self
integer(C_INT) :: fresult 
type(SwigClassWrapper) :: farg1 

farg1 = self%swigdata
fresult = swigc_SUNContext__last_err_get(farg1)
swig_result = fresult
end function

subroutine swigf_SUNContext__err_handler_set(self, err_handler)
use, intrinsic :: ISO_C_BINDING
class(SUNContext_), intent(in) :: self
class(SWIGTYPE_p_SUNErrHandler_), intent(in) :: err_handler
type(SwigClassWrapper) :: farg1 
type(SwigClassWrapper) :: farg2 

farg1 = self%swigdata
farg2 = err_handler%swigdata
call swigc_SUNContext__err_handler_set(farg1, farg2)
end subroutine

function swigf_SUNContext__err_handler_get(self) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(SWIGTYPE_p_SUNErrHandler_) :: swig_result
class(SUNContext_), intent(in) :: self
type(SwigClassWrapper) :: fresult 
type(SwigClassWrapper) :: farg1 

farg1 = self%swigdata
fresult = swigc_SUNContext__err_handler_get(farg1)
swig_result%swigdata = fresult
end function

subroutine swigf_SUNContext__comm_set(self, comm)
use, intrinsic :: ISO_C_BINDING
class(SUNContext_), intent(in) :: self
type(C_PTR) :: comm
type(SwigClassWrapper) :: farg1 
type(C_PTR) :: farg2 

farg1 = self%swigdata
farg2 = comm
call swigc_SUNContext__comm_set(farg1, farg2)
end subroutine

function swigf_SUNContext__comm_get(self) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(C_PTR) :: swig_result
class(SUNContext_), intent(in) :: self
type(C_PTR) :: fresult 
type(SwigClassWrapper) :: farg1 

farg1 = self%swigdata
fresult = swigc_SUNContext__comm_get(farg1)
swig_result = fresult
end function

function swigf_create_SUNContext_() &
result(self)
use, intrinsic :: ISO_C_BINDING
type(SUNContext_) :: self
type(SwigClassWrapper) :: fresult 

fresult = swigc_new_SUNContext_()
self%swigdata = fresult
end function

subroutine swigf_release_SUNContext_(self)
use, intrinsic :: ISO_C_BINDING
class(SUNContext_), intent(inout) :: self
type(SwigClassWrapper) :: farg1 

farg1 = self%swigdata
if (btest(farg1%cmemflags, swig_cmem_own_bit)) then
call swigc_delete_SUNContext_(farg1)
endif
farg1%cptr = C_NULL_PTR
farg1%cmemflags = 0
self%swigdata = farg1
end subroutine

subroutine swigf_SUNContext__op_assign__(self, other)
use, intrinsic :: ISO_C_BINDING
class(SUNContext_), intent(inout) :: self
type(SUNContext_), intent(in) :: other
type(SwigClassWrapper) :: farg1 
type(SwigClassWrapper) :: farg2 

farg1 = self%swigdata
farg2 = other%swigdata
call swigc_SUNContext__op_assign__(farg1, farg2)
self%swigdata = farg1
end subroutine

function FSUNContext_GetLastError(sunctx, last_err) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: sunctx
integer(C_INT), dimension(*), target, intent(inout) :: last_err
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 

farg1 = sunctx
farg2 = c_loc(last_err(1))
fresult = swigc_FSUNContext_GetLastError(farg1, farg2)
swig_result = fresult
end function

function FSUNContext_PeekLastError(sunctx, last_err) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: sunctx
integer(C_INT), dimension(*), target, intent(inout) :: last_err
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 

farg1 = sunctx
farg2 = c_loc(last_err(1))
fresult = swigc_FSUNContext_PeekLastError(farg1, farg2)
swig_result = fresult
end function

function FSUNContext_PushErrHandler(sunctx, err_fn, err_user_data) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(SWIGTYPE_p_SUNErrHandler_) :: swig_result
type(C_PTR) :: sunctx
type(C_FUNPTR), intent(in), value :: err_fn
type(C_PTR) :: err_user_data
type(SwigClassWrapper) :: fresult 
type(C_PTR) :: farg1 
type(C_FUNPTR) :: farg2 
type(C_PTR) :: farg3 

farg1 = sunctx
farg2 = err_fn
farg3 = err_user_data
fresult = swigc_FSUNContext_PushErrHandler(farg1, farg2, farg3)
swig_result%swigdata = fresult
end function

function FSUNContext_PopErrHandler(sunctx) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: sunctx
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = sunctx
fresult = swigc_FSUNContext_PopErrHandler(farg1)
swig_result = fresult
end function

function FSUNContext_ClearHandlers(sunctx) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: sunctx
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = sunctx
fresult = swigc_FSUNContext_ClearHandlers(farg1)
swig_result = fresult
end function

function FSUNContext_GetProfiler(sunctx, profiler) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: sunctx
type(C_PTR), target, intent(inout) :: profiler
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 

farg1 = sunctx
farg2 = c_loc(profiler)
fresult = swigc_FSUNContext_GetProfiler(farg1, farg2)
swig_result = fresult
end function

function FSUNContext_SetProfiler(sunctx, profiler) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: sunctx
type(C_PTR) :: profiler
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 

farg1 = sunctx
farg2 = profiler
fresult = swigc_FSUNContext_SetProfiler(farg1, farg2)
swig_result = fresult
end function

function FSUNContext_GetLogger(sunctx, logger) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: sunctx
type(C_PTR), target, intent(inout) :: logger
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 

farg1 = sunctx
farg2 = c_loc(logger)
fresult = swigc_FSUNContext_GetLogger(farg1, farg2)
swig_result = fresult
end function

function FSUNContext_SetLogger(sunctx, logger) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: sunctx
type(C_PTR) :: logger
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 

farg1 = sunctx
farg2 = logger
fresult = swigc_FSUNContext_SetLogger(farg1, farg2)
swig_result = fresult
end function


function FSUNContext_Free(ctx) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR), target, intent(inout) :: ctx
integer(C_INT) :: fresult
type(C_PTR) :: farg1

farg1 = c_loc(ctx)
fresult = swigc_FSUNContext_Free(farg1)
swig_result = fresult
end function

function FSUNContext_Create(comm, ctx) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
#ifdef SUNDIALS_BUILD_WITH_PROFILING
use fsundials_profiler_mod, only : FSUNProfiler_Create
#endif
integer(C_INT) :: swig_result
type(C_PTR) :: comm
type(C_PTR), target, intent(inout) :: ctx
integer(C_INT) :: fresult
type(C_PTR) :: farg1
type(C_PTR) :: farg2
#ifdef SUNDIALS_BUILD_WITH_PROFILING
type(C_PTR) :: profiler
#endif

farg1 = comm
farg2 = c_loc(ctx)
fresult = swigc_FSUNContext_Create(c_null_ptr, farg2)
#ifdef SUNDIALS_BUILD_WITH_PROFILING
fresult = FSUNProfiler_Create(farg1, "FSUNContext Default", profiler)
fresult = swigc_FSUNContext_SetProfiler(ctx, profiler)
#endif
swig_result = fresult
end function


end module
