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

module fsuncontrol_mripi_mod
 use, intrinsic :: ISO_C_BINDING
 use fsundials_control_mod
 use fsundials_types_mod
 use fsundials_context_mod
 implicit none
 private

 ! DECLARATION CONSTRUCTS
 public :: FSUNControlMRIPI
 public :: FSUNControlMRIPI_SetParams
 public :: FSUNControlGetID_MRIPI
 public :: FSUNControlEstimateMRISteps_MRIPI
 public :: FSUNControlReset_MRIPI
 public :: FSUNControlSetDefaults_MRIPI
 public :: FSUNControlWrite_MRIPI
 public :: FSUNControlSetErrorBias_MRIPI
 public :: FSUNControlUpdateMRIH_MRIPI
 public :: FSUNControlSpace_MRIPI

! WRAPPER DECLARATIONS
interface
function swigc_FSUNControlMRIPI(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNControlMRIPI") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT), intent(in) :: farg2
integer(C_INT), intent(in) :: farg3
type(C_PTR) :: fresult
end function

function swigc_FSUNControlMRIPI_SetParams(farg1, farg2, farg3, farg4, farg5) &
bind(C, name="_wrap_FSUNControlMRIPI_SetParams") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
real(C_DOUBLE), intent(in) :: farg2
real(C_DOUBLE), intent(in) :: farg3
real(C_DOUBLE), intent(in) :: farg4
real(C_DOUBLE), intent(in) :: farg5
integer(C_INT) :: fresult
end function

function swigc_FSUNControlGetID_MRIPI(farg1) &
bind(C, name="_wrap_FSUNControlGetID_MRIPI") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNControlEstimateMRISteps_MRIPI(farg1, farg2, farg3, farg4, farg5, farg6, farg7) &
bind(C, name="_wrap_FSUNControlEstimateMRISteps_MRIPI") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
real(C_DOUBLE), intent(in) :: farg2
real(C_DOUBLE), intent(in) :: farg3
real(C_DOUBLE), intent(in) :: farg4
real(C_DOUBLE), intent(in) :: farg5
type(C_PTR), value :: farg6
type(C_PTR), value :: farg7
integer(C_INT) :: fresult
end function

function swigc_FSUNControlReset_MRIPI(farg1) &
bind(C, name="_wrap_FSUNControlReset_MRIPI") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNControlSetDefaults_MRIPI(farg1) &
bind(C, name="_wrap_FSUNControlSetDefaults_MRIPI") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNControlWrite_MRIPI(farg1, farg2) &
bind(C, name="_wrap_FSUNControlWrite_MRIPI") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNControlSetErrorBias_MRIPI(farg1, farg2) &
bind(C, name="_wrap_FSUNControlSetErrorBias_MRIPI") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
real(C_DOUBLE), intent(in) :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNControlUpdateMRIH_MRIPI(farg1, farg2, farg3, farg4, farg5) &
bind(C, name="_wrap_FSUNControlUpdateMRIH_MRIPI") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
real(C_DOUBLE), intent(in) :: farg2
real(C_DOUBLE), intent(in) :: farg3
real(C_DOUBLE), intent(in) :: farg4
real(C_DOUBLE), intent(in) :: farg5
integer(C_INT) :: fresult
end function

function swigc_FSUNControlSpace_MRIPI(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNControlSpace_MRIPI") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
integer(C_INT) :: fresult
end function

end interface


contains
 ! MODULE SUBPROGRAMS
function FSUNControlMRIPI(sunctx, p, p2) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(SUNControl), pointer :: swig_result
type(C_PTR) :: sunctx
integer(C_INT), intent(in) :: p
integer(C_INT), intent(in) :: p2
type(C_PTR) :: fresult 
type(C_PTR) :: farg1 
integer(C_INT) :: farg2 
integer(C_INT) :: farg3 

farg1 = sunctx
farg2 = p
farg3 = p2
fresult = swigc_FSUNControlMRIPI(farg1, farg2, farg3)
call c_f_pointer(fresult, swig_result)
end function

function FSUNControlMRIPI_SetParams(c, k11, k12, k21, k22) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNControl), target, intent(inout) :: c
real(C_DOUBLE), intent(in) :: k11
real(C_DOUBLE), intent(in) :: k12
real(C_DOUBLE), intent(in) :: k21
real(C_DOUBLE), intent(in) :: k22
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
real(C_DOUBLE) :: farg2 
real(C_DOUBLE) :: farg3 
real(C_DOUBLE) :: farg4 
real(C_DOUBLE) :: farg5 

farg1 = c_loc(c)
farg2 = k11
farg3 = k12
farg4 = k21
farg5 = k22
fresult = swigc_FSUNControlMRIPI_SetParams(farg1, farg2, farg3, farg4, farg5)
swig_result = fresult
end function

function FSUNControlGetID_MRIPI(c) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(SUNControl_ID) :: swig_result
type(SUNControl), target, intent(inout) :: c
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(c)
fresult = swigc_FSUNControlGetID_MRIPI(farg1)
swig_result = fresult
end function

function FSUNControlEstimateMRISteps_MRIPI(c, h, h2, dsm, dsm4, hnew, hnew6) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNControl), target, intent(inout) :: c
real(C_DOUBLE), intent(in) :: h
real(C_DOUBLE), intent(in) :: h2
real(C_DOUBLE), intent(in) :: dsm
real(C_DOUBLE), intent(in) :: dsm4
real(C_DOUBLE), dimension(*), target, intent(inout) :: hnew
real(C_DOUBLE), dimension(*), target, intent(inout) :: hnew6
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
real(C_DOUBLE) :: farg2 
real(C_DOUBLE) :: farg3 
real(C_DOUBLE) :: farg4 
real(C_DOUBLE) :: farg5 
type(C_PTR) :: farg6 
type(C_PTR) :: farg7 

farg1 = c_loc(c)
farg2 = h
farg3 = h2
farg4 = dsm
farg5 = dsm4
farg6 = c_loc(hnew(1))
farg7 = c_loc(hnew6(1))
fresult = swigc_FSUNControlEstimateMRISteps_MRIPI(farg1, farg2, farg3, farg4, farg5, farg6, farg7)
swig_result = fresult
end function

function FSUNControlReset_MRIPI(c) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNControl), target, intent(inout) :: c
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(c)
fresult = swigc_FSUNControlReset_MRIPI(farg1)
swig_result = fresult
end function

function FSUNControlSetDefaults_MRIPI(c) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNControl), target, intent(inout) :: c
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(c)
fresult = swigc_FSUNControlSetDefaults_MRIPI(farg1)
swig_result = fresult
end function

function FSUNControlWrite_MRIPI(c, fptr) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNControl), target, intent(inout) :: c
type(C_PTR) :: fptr
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 

farg1 = c_loc(c)
farg2 = fptr
fresult = swigc_FSUNControlWrite_MRIPI(farg1, farg2)
swig_result = fresult
end function

function FSUNControlSetErrorBias_MRIPI(c, bias) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNControl), target, intent(inout) :: c
real(C_DOUBLE), intent(in) :: bias
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
real(C_DOUBLE) :: farg2 

farg1 = c_loc(c)
farg2 = bias
fresult = swigc_FSUNControlSetErrorBias_MRIPI(farg1, farg2)
swig_result = fresult
end function

function FSUNControlUpdateMRIH_MRIPI(c, h, h2, dsm, dsm4) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNControl), target, intent(inout) :: c
real(C_DOUBLE), intent(in) :: h
real(C_DOUBLE), intent(in) :: h2
real(C_DOUBLE), intent(in) :: dsm
real(C_DOUBLE), intent(in) :: dsm4
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
real(C_DOUBLE) :: farg2 
real(C_DOUBLE) :: farg3 
real(C_DOUBLE) :: farg4 
real(C_DOUBLE) :: farg5 

farg1 = c_loc(c)
farg2 = h
farg3 = h2
farg4 = dsm
farg5 = dsm4
fresult = swigc_FSUNControlUpdateMRIH_MRIPI(farg1, farg2, farg3, farg4, farg5)
swig_result = fresult
end function

function FSUNControlSpace_MRIPI(c, lenrw, leniw) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNControl), target, intent(inout) :: c
integer(C_LONG), dimension(*), target, intent(inout) :: lenrw
integer(C_LONG), dimension(*), target, intent(inout) :: leniw
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 
type(C_PTR) :: farg3 

farg1 = c_loc(c)
farg2 = c_loc(lenrw(1))
farg3 = c_loc(leniw(1))
fresult = swigc_FSUNControlSpace_MRIPI(farg1, farg2, farg3)
swig_result = fresult
end function


end module
