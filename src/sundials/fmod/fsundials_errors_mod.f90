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

module fsundials_errors_mod
 use, intrinsic :: ISO_C_BINDING
 use fsundials_context_mod
 use fsundials_types_mod
 use fsundials_types_mod
 use fsundials_types_mod
 implicit none
 private

 ! DECLARATION CONSTRUCTS
 enum, bind(c)
  enumerator :: SUN_ERR_MINIMUM = -10000
  enumerator :: SUN_ERR_ARG_CORRUPT
  enumerator :: SUN_ERR_ARG_INCOMPATIBLE
  enumerator :: SUN_ERR_ARG_OUTOFRANGE
  enumerator :: SUN_ERR_ARG_WRONGTYPE
  enumerator :: SUN_ERR_ARG_DIMSMISMATCH
  enumerator :: SUN_ERR_CORRUPT
  enumerator :: SUN_ERR_FILE_OPEN
  enumerator :: SUN_ERR_MEM_FAIL
  enumerator :: SUN_ERR_MALLOC_FAIL
  enumerator :: SUN_ERR_DESTROY_FAIL
  enumerator :: SUN_ERR_NOT_IMPLEMENTED
  enumerator :: SUN_ERR_PROFILER_MAPFULL
  enumerator :: SUN_ERR_PROFILER_MAPGET
  enumerator :: SUN_ERR_PROFILER_MAPINSERT
  enumerator :: SUN_ERR_PROFILER_MAPKEYNOTFOUND
  enumerator :: SUN_ERR_PROFILER_MAPSORT
  enumerator :: SUN_ERR_SUNCTX_CORRUPT
  enumerator :: SUN_ERR_OP_FAIL
  enumerator :: SUN_ERR_MPI_FAIL
  enumerator :: SUN_ERR_UNREACHABLE
  enumerator :: SUN_ERR_UNKNOWN
  enumerator :: SUN_ERR_MAXIMUM = -1000
  enumerator :: SUN_SUCCESS = 0
 end enum
 public :: SUN_ERR_MINIMUM, SUN_ERR_ARG_CORRUPT, SUN_ERR_ARG_INCOMPATIBLE, SUN_ERR_ARG_OUTOFRANGE, SUN_ERR_ARG_WRONGTYPE, &
    SUN_ERR_ARG_DIMSMISMATCH, SUN_ERR_CORRUPT, SUN_ERR_FILE_OPEN, SUN_ERR_MEM_FAIL, SUN_ERR_MALLOC_FAIL, SUN_ERR_DESTROY_FAIL, &
    SUN_ERR_NOT_IMPLEMENTED, SUN_ERR_PROFILER_MAPFULL, SUN_ERR_PROFILER_MAPGET, SUN_ERR_PROFILER_MAPINSERT, &
    SUN_ERR_PROFILER_MAPKEYNOTFOUND, SUN_ERR_PROFILER_MAPSORT, SUN_ERR_SUNCTX_CORRUPT, SUN_ERR_OP_FAIL, SUN_ERR_MPI_FAIL, &
    SUN_ERR_UNREACHABLE, SUN_ERR_UNKNOWN, SUN_ERR_MAXIMUM, SUN_SUCCESS
 type, bind(C) :: SwigArrayWrapper
  type(C_PTR), public :: data = C_NULL_PTR
  integer(C_SIZE_T), public :: size = 0
 end type
 public :: FSUNLogErrHandlerFn
 public :: FSUNAbortErrHandlerFn
 public :: FSUNGetErrMsg

! WRAPPER DECLARATIONS
interface
subroutine swigc_FSUNLogErrHandlerFn(farg1, farg2, farg3, farg4, farg5, farg6, farg7) &
bind(C, name="_wrap_FSUNLogErrHandlerFn")
use, intrinsic :: ISO_C_BINDING
import :: swigarraywrapper
integer(C_INT), intent(in) :: farg1
type(SwigArrayWrapper) :: farg2
type(SwigArrayWrapper) :: farg3
type(SwigArrayWrapper) :: farg4
integer(C_INT), intent(in) :: farg5
type(C_PTR), value :: farg6
type(C_PTR), value :: farg7
end subroutine

subroutine swigc_FSUNAbortErrHandlerFn(farg1, farg2, farg3, farg4, farg5, farg6, farg7) &
bind(C, name="_wrap_FSUNAbortErrHandlerFn")
use, intrinsic :: ISO_C_BINDING
import :: swigarraywrapper
integer(C_INT), intent(in) :: farg1
type(SwigArrayWrapper) :: farg2
type(SwigArrayWrapper) :: farg3
type(SwigArrayWrapper) :: farg4
integer(C_INT), intent(in) :: farg5
type(C_PTR), value :: farg6
type(C_PTR), value :: farg7
end subroutine

 subroutine SWIG_free(cptr) &
  bind(C, name="free")
 use, intrinsic :: ISO_C_BINDING
 type(C_PTR), value :: cptr
end subroutine
function swigc_FSUNGetErrMsg(farg1) &
bind(C, name="_wrap_FSUNGetErrMsg") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigarraywrapper
integer(C_INT), intent(in) :: farg1
type(SwigArrayWrapper) :: fresult
end function

end interface


contains
 ! MODULE SUBPROGRAMS

subroutine SWIG_string_to_chararray(string, chars, wrap)
  use, intrinsic :: ISO_C_BINDING
  character(kind=C_CHAR, len=*), intent(IN) :: string
  character(kind=C_CHAR), dimension(:), target, allocatable, intent(OUT) :: chars
  type(SwigArrayWrapper), intent(OUT) :: wrap
  integer :: i

  allocate(character(kind=C_CHAR) :: chars(len(string) + 1))
  do i=1,len(string)
    chars(i) = string(i:i)
  end do
  i = len(string) + 1
  chars(i) = C_NULL_CHAR ! C string compatibility
  wrap%data = c_loc(chars)
  wrap%size = len(string)
end subroutine

subroutine FSUNLogErrHandlerFn(line, func, file, msg, err_code, err_user_data, sunctx)
use, intrinsic :: ISO_C_BINDING
integer(C_INT), intent(in) :: line
character(kind=C_CHAR, len=*), target :: func
character(kind=C_CHAR), dimension(:), allocatable, target :: farg2_chars
character(kind=C_CHAR, len=*), target :: file
character(kind=C_CHAR), dimension(:), allocatable, target :: farg3_chars
character(kind=C_CHAR, len=*), target :: msg
character(kind=C_CHAR), dimension(:), allocatable, target :: farg4_chars
integer(C_INT), intent(in) :: err_code
type(C_PTR) :: err_user_data
type(C_PTR) :: sunctx
integer(C_INT) :: farg1 
type(SwigArrayWrapper) :: farg2 
type(SwigArrayWrapper) :: farg3 
type(SwigArrayWrapper) :: farg4 
integer(C_INT) :: farg5 
type(C_PTR) :: farg6 
type(C_PTR) :: farg7 

farg1 = line
call SWIG_string_to_chararray(func, farg2_chars, farg2)
call SWIG_string_to_chararray(file, farg3_chars, farg3)
call SWIG_string_to_chararray(msg, farg4_chars, farg4)
farg5 = err_code
farg6 = err_user_data
farg7 = sunctx
call swigc_FSUNLogErrHandlerFn(farg1, farg2, farg3, farg4, farg5, farg6, farg7)
end subroutine

subroutine FSUNAbortErrHandlerFn(line, func, file, msg, err_code, err_user_data, sunctx)
use, intrinsic :: ISO_C_BINDING
integer(C_INT), intent(in) :: line
character(kind=C_CHAR, len=*), target :: func
character(kind=C_CHAR), dimension(:), allocatable, target :: farg2_chars
character(kind=C_CHAR, len=*), target :: file
character(kind=C_CHAR), dimension(:), allocatable, target :: farg3_chars
character(kind=C_CHAR, len=*), target :: msg
character(kind=C_CHAR), dimension(:), allocatable, target :: farg4_chars
integer(C_INT), intent(in) :: err_code
type(C_PTR) :: err_user_data
type(C_PTR) :: sunctx
integer(C_INT) :: farg1 
type(SwigArrayWrapper) :: farg2 
type(SwigArrayWrapper) :: farg3 
type(SwigArrayWrapper) :: farg4 
integer(C_INT) :: farg5 
type(C_PTR) :: farg6 
type(C_PTR) :: farg7 

farg1 = line
call SWIG_string_to_chararray(func, farg2_chars, farg2)
call SWIG_string_to_chararray(file, farg3_chars, farg3)
call SWIG_string_to_chararray(msg, farg4_chars, farg4)
farg5 = err_code
farg6 = err_user_data
farg7 = sunctx
call swigc_FSUNAbortErrHandlerFn(farg1, farg2, farg3, farg4, farg5, farg6, farg7)
end subroutine


subroutine SWIG_chararray_to_string(wrap, string)
  use, intrinsic :: ISO_C_BINDING
  type(SwigArrayWrapper), intent(IN) :: wrap
  character(kind=C_CHAR, len=:), allocatable, intent(OUT) :: string
  character(kind=C_CHAR), dimension(:), pointer :: chars
  integer(kind=C_SIZE_T) :: i
  call c_f_pointer(wrap%data, chars, [wrap%size])
  allocate(character(kind=C_CHAR, len=wrap%size) :: string)
  do i=1, wrap%size
    string(i:i) = chars(i)
  end do
end subroutine

function FSUNGetErrMsg(code) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
character(kind=C_CHAR, len=:), allocatable :: swig_result
integer(C_INT), intent(in) :: code
type(SwigArrayWrapper) :: fresult 
integer(C_INT) :: farg1 

farg1 = code
fresult = swigc_FSUNGetErrMsg(farg1)
call SWIG_chararray_to_string(fresult, swig_result)
if (.false.) call SWIG_free(fresult%data)
end function


end module
