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

module fsundials_logger_mod
 use, intrinsic :: ISO_C_BINDING
<<<<<<< HEAD
 use fsundials_context_mod
 use fsundials_types_mod
=======
>>>>>>> feature/sunmpicomm-formatted
 use fsundials_types_mod
 implicit none
 private

 ! DECLARATION CONSTRUCTS
 ! typedef enum SUNLogLevel
 enum, bind(c)
  enumerator :: SUN_LOGLEVEL_ALL = -1
  enumerator :: SUN_LOGLEVEL_NONE = 0
  enumerator :: SUN_LOGLEVEL_ERROR = 1
  enumerator :: SUN_LOGLEVEL_WARNING = 2
  enumerator :: SUN_LOGLEVEL_INFO = 3
  enumerator :: SUN_LOGLEVEL_DEBUG = 4
 end enum
 integer, parameter, public :: SUNLogLevel = kind(SUN_LOGLEVEL_ALL)
 public :: SUN_LOGLEVEL_ALL, SUN_LOGLEVEL_NONE, SUN_LOGLEVEL_ERROR, SUN_LOGLEVEL_WARNING, SUN_LOGLEVEL_INFO, &
    SUN_LOGLEVEL_DEBUG
 public :: FSUNLogger_Create
 public :: FSUNLogger_CreateFromEnv
 type, bind(C) :: SwigArrayWrapper
  type(C_PTR), public :: data = C_NULL_PTR
  integer(C_SIZE_T), public :: size = 0
 end type
 public :: FSUNLogger_SetErrorFilename
 public :: FSUNLogger_SetWarningFilename
 public :: FSUNLogger_SetDebugFilename
 public :: FSUNLogger_SetInfoFilename
 public :: FSUNLogger_QueueMsg
 public :: FSUNLogger_Flush
 public :: FSUNLogger_GetOutputRank
 public :: FSUNLogger_Destroy

! WRAPPER DECLARATIONS
interface
function swigc_FSUNLogger_Create(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNLogger_Create") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
integer(C_INT), intent(in) :: farg1
integer(C_INT), intent(in) :: farg2
type(C_PTR), value :: farg3
integer(C_INT) :: fresult
end function

function swigc_FSUNLogger_CreateFromEnv(farg1, farg2) &
bind(C, name="_wrap_FSUNLogger_CreateFromEnv") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
integer(C_INT), intent(in) :: farg1
type(C_PTR), value :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNLogger_SetErrorFilename(farg1, farg2) &
bind(C, name="_wrap_FSUNLogger_SetErrorFilename") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigarraywrapper
type(C_PTR), value :: farg1
type(SwigArrayWrapper) :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNLogger_SetWarningFilename(farg1, farg2) &
bind(C, name="_wrap_FSUNLogger_SetWarningFilename") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigarraywrapper
type(C_PTR), value :: farg1
type(SwigArrayWrapper) :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNLogger_SetDebugFilename(farg1, farg2) &
bind(C, name="_wrap_FSUNLogger_SetDebugFilename") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigarraywrapper
type(C_PTR), value :: farg1
type(SwigArrayWrapper) :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNLogger_SetInfoFilename(farg1, farg2) &
bind(C, name="_wrap_FSUNLogger_SetInfoFilename") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigarraywrapper
type(C_PTR), value :: farg1
type(SwigArrayWrapper) :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNLogger_QueueMsg(farg1, farg2, farg3, farg4, farg5) &
bind(C, name="_wrap_FSUNLogger_QueueMsg") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
import :: swigarraywrapper
type(C_PTR), value :: farg1
integer(C_INT), intent(in) :: farg2
type(SwigArrayWrapper) :: farg3
type(SwigArrayWrapper) :: farg4
type(SwigArrayWrapper) :: farg5
integer(C_INT) :: fresult
end function

function swigc_FSUNLogger_Flush(farg1, farg2) &
bind(C, name="_wrap_FSUNLogger_Flush") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT), intent(in) :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNLogger_GetOutputRank(farg1, farg2) &
bind(C, name="_wrap_FSUNLogger_GetOutputRank") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNLogger_Destroy(farg1) &
bind(C, name="_wrap_FSUNLogger_Destroy") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

end interface


contains
 ! MODULE SUBPROGRAMS
function FSUNLogger_Create(comm, output_rank, logger) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
integer :: comm
integer(C_INT), intent(in) :: output_rank
type(C_PTR), target, intent(inout) :: logger
integer(C_INT) :: fresult 
integer(C_INT) :: farg1 
integer(C_INT) :: farg2 
type(C_PTR) :: farg3 

farg1 = int(comm, C_INT)
farg2 = output_rank
farg3 = c_loc(logger)
fresult = swigc_FSUNLogger_Create(farg1, farg2, farg3)
swig_result = fresult
end function

function FSUNLogger_CreateFromEnv(comm, logger) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
integer :: comm
type(C_PTR), target, intent(inout) :: logger
integer(C_INT) :: fresult 
integer(C_INT) :: farg1 
type(C_PTR) :: farg2 

farg1 = int(comm, C_INT)
farg2 = c_loc(logger)
fresult = swigc_FSUNLogger_CreateFromEnv(farg1, farg2)
swig_result = fresult
end function


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

function FSUNLogger_SetErrorFilename(logger, error_filename) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: logger
character(kind=C_CHAR, len=*), target :: error_filename
character(kind=C_CHAR), dimension(:), allocatable, target :: farg2_chars
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(SwigArrayWrapper) :: farg2 

farg1 = logger
call SWIG_string_to_chararray(error_filename, farg2_chars, farg2)
fresult = swigc_FSUNLogger_SetErrorFilename(farg1, farg2)
swig_result = fresult
end function

function FSUNLogger_SetWarningFilename(logger, warning_filename) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: logger
character(kind=C_CHAR, len=*), target :: warning_filename
character(kind=C_CHAR), dimension(:), allocatable, target :: farg2_chars
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(SwigArrayWrapper) :: farg2 

farg1 = logger
call SWIG_string_to_chararray(warning_filename, farg2_chars, farg2)
fresult = swigc_FSUNLogger_SetWarningFilename(farg1, farg2)
swig_result = fresult
end function

function FSUNLogger_SetDebugFilename(logger, debug_filename) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: logger
character(kind=C_CHAR, len=*), target :: debug_filename
character(kind=C_CHAR), dimension(:), allocatable, target :: farg2_chars
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(SwigArrayWrapper) :: farg2 

farg1 = logger
call SWIG_string_to_chararray(debug_filename, farg2_chars, farg2)
fresult = swigc_FSUNLogger_SetDebugFilename(farg1, farg2)
swig_result = fresult
end function

function FSUNLogger_SetInfoFilename(logger, info_filename) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: logger
character(kind=C_CHAR, len=*), target :: info_filename
character(kind=C_CHAR), dimension(:), allocatable, target :: farg2_chars
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(SwigArrayWrapper) :: farg2 

farg1 = logger
call SWIG_string_to_chararray(info_filename, farg2_chars, farg2)
fresult = swigc_FSUNLogger_SetInfoFilename(farg1, farg2)
swig_result = fresult
end function

function FSUNLogger_QueueMsg(logger, lvl, scope, label, msg_txt) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: logger
integer(SUNLogLevel), intent(in) :: lvl
character(kind=C_CHAR, len=*), target :: scope
character(kind=C_CHAR), dimension(:), allocatable, target :: farg3_chars
character(kind=C_CHAR, len=*), target :: label
character(kind=C_CHAR), dimension(:), allocatable, target :: farg4_chars
character(kind=C_CHAR, len=*), target :: msg_txt
character(kind=C_CHAR), dimension(:), allocatable, target :: farg5_chars
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
integer(C_INT) :: farg2 
type(SwigArrayWrapper) :: farg3 
type(SwigArrayWrapper) :: farg4 
type(SwigArrayWrapper) :: farg5 

farg1 = logger
farg2 = lvl
call SWIG_string_to_chararray(scope, farg3_chars, farg3)
call SWIG_string_to_chararray(label, farg4_chars, farg4)
call SWIG_string_to_chararray(msg_txt, farg5_chars, farg5)
fresult = swigc_FSUNLogger_QueueMsg(farg1, farg2, farg3, farg4, farg5)
swig_result = fresult
end function

function FSUNLogger_Flush(logger, lvl) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: logger
integer(SUNLogLevel), intent(in) :: lvl
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
integer(C_INT) :: farg2 

farg1 = logger
farg2 = lvl
fresult = swigc_FSUNLogger_Flush(farg1, farg2)
swig_result = fresult
end function

function FSUNLogger_GetOutputRank(logger, output_rank) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: logger
integer(C_INT), dimension(*), target, intent(inout) :: output_rank
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 

farg1 = logger
farg2 = c_loc(output_rank(1))
fresult = swigc_FSUNLogger_GetOutputRank(farg1, farg2)
swig_result = fresult
end function

function FSUNLogger_Destroy(logger) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR), target, intent(inout) :: logger
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(logger)
fresult = swigc_FSUNLogger_Destroy(farg1)
swig_result = fresult
end function


end module
