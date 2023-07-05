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

module fsuncontrol_i_mod
 use, intrinsic :: ISO_C_BINDING
 use fsundials_control_mod
 use fsundials_types_mod
 use fsundials_context_mod
 implicit none
 private

 ! DECLARATION CONSTRUCTS
 public :: FSUNControlI
 public :: FSUNControlI_SetParams
 public :: FSUNControlGetID_I
 public :: FSUNControlEstimateStep_I
 public :: FSUNControlSetDefaults_I
 public :: FSUNControlWrite_I
 public :: FSUNControlSetMethodOrder_I
 public :: FSUNControlSetEmbeddingOrder_I
 public :: FSUNControlSetErrorBias_I
 public :: FSUNControlSpace_I

! WRAPPER DECLARATIONS
interface
function swigc_FSUNControlI(farg1) &
bind(C, name="_wrap_FSUNControlI") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR) :: fresult
end function

function swigc_FSUNControlI_SetParams(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNControlI_SetParams") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT), intent(in) :: farg2
real(C_DOUBLE), intent(in) :: farg3
integer(C_INT) :: fresult
end function

function swigc_FSUNControlGetID_I(farg1) &
bind(C, name="_wrap_FSUNControlGetID_I") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNControlEstimateStep_I(farg1, farg2, farg3, farg4) &
bind(C, name="_wrap_FSUNControlEstimateStep_I") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
real(C_DOUBLE), intent(in) :: farg2
real(C_DOUBLE), intent(in) :: farg3
type(C_PTR), value :: farg4
integer(C_INT) :: fresult
end function

function swigc_FSUNControlSetDefaults_I(farg1) &
bind(C, name="_wrap_FSUNControlSetDefaults_I") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNControlWrite_I(farg1, farg2) &
bind(C, name="_wrap_FSUNControlWrite_I") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNControlSetMethodOrder_I(farg1, farg2) &
bind(C, name="_wrap_FSUNControlSetMethodOrder_I") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT), intent(in) :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNControlSetEmbeddingOrder_I(farg1, farg2) &
bind(C, name="_wrap_FSUNControlSetEmbeddingOrder_I") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT), intent(in) :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNControlSetErrorBias_I(farg1, farg2) &
bind(C, name="_wrap_FSUNControlSetErrorBias_I") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
real(C_DOUBLE), intent(in) :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNControlSpace_I(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNControlSpace_I") &
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
function FSUNControlI(sunctx) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(SUNControl), pointer :: swig_result
type(C_PTR) :: sunctx
type(C_PTR) :: fresult 
type(C_PTR) :: farg1 

farg1 = sunctx
fresult = swigc_FSUNControlI(farg1)
call c_f_pointer(fresult, swig_result)
end function

function FSUNControlI_SetParams(c, pq, k1) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNControl), target, intent(inout) :: c
integer(C_INT), intent(in) :: pq
real(C_DOUBLE), intent(in) :: k1
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
integer(C_INT) :: farg2 
real(C_DOUBLE) :: farg3 

farg1 = c_loc(c)
farg2 = pq
farg3 = k1
fresult = swigc_FSUNControlI_SetParams(farg1, farg2, farg3)
swig_result = fresult
end function

function FSUNControlGetID_I(c) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(SUNControl_ID) :: swig_result
type(SUNControl), target, intent(inout) :: c
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(c)
fresult = swigc_FSUNControlGetID_I(farg1)
swig_result = fresult
end function

function FSUNControlEstimateStep_I(c, h, dsm, hnew) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNControl), target, intent(inout) :: c
real(C_DOUBLE), intent(in) :: h
real(C_DOUBLE), intent(in) :: dsm
real(C_DOUBLE), dimension(*), target, intent(inout) :: hnew
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
real(C_DOUBLE) :: farg2 
real(C_DOUBLE) :: farg3 
type(C_PTR) :: farg4 

farg1 = c_loc(c)
farg2 = h
farg3 = dsm
farg4 = c_loc(hnew(1))
fresult = swigc_FSUNControlEstimateStep_I(farg1, farg2, farg3, farg4)
swig_result = fresult
end function

function FSUNControlSetDefaults_I(c) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNControl), target, intent(inout) :: c
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(c)
fresult = swigc_FSUNControlSetDefaults_I(farg1)
swig_result = fresult
end function

function FSUNControlWrite_I(c, fptr) &
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
fresult = swigc_FSUNControlWrite_I(farg1, farg2)
swig_result = fresult
end function

function FSUNControlSetMethodOrder_I(c, q) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNControl), target, intent(inout) :: c
integer(C_INT), intent(in) :: q
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
integer(C_INT) :: farg2 

farg1 = c_loc(c)
farg2 = q
fresult = swigc_FSUNControlSetMethodOrder_I(farg1, farg2)
swig_result = fresult
end function

function FSUNControlSetEmbeddingOrder_I(c, p) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNControl), target, intent(inout) :: c
integer(C_INT), intent(in) :: p
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
integer(C_INT) :: farg2 

farg1 = c_loc(c)
farg2 = p
fresult = swigc_FSUNControlSetEmbeddingOrder_I(farg1, farg2)
swig_result = fresult
end function

function FSUNControlSetErrorBias_I(c, bias) &
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
fresult = swigc_FSUNControlSetErrorBias_I(farg1, farg2)
swig_result = fresult
end function

function FSUNControlSpace_I(c, lenrw, leniw) &
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
fresult = swigc_FSUNControlSpace_I(farg1, farg2, farg3)
swig_result = fresult
end function


end module