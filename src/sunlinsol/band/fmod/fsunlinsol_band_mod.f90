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

module fsunlinsol_band_mod
 use, intrinsic :: ISO_C_BINDING
 use fsundials_types_mod
 use fsundials_linearsolver_mod
 use fsundials_context_mod
 use fsundials_types_mod
 use fsundials_nvector_mod
 use fsundials_context_mod
 use fsundials_types_mod
 use fsundials_matrix_mod
 use fsundials_nvector_mod
 use fsundials_context_mod
 use fsundials_types_mod
 implicit none
 private

 ! DECLARATION CONSTRUCTS
 public :: FSUNLinSol_Band
 public :: FSUNLinSolGetType_Band
 public :: FSUNLinSolGetID_Band
 public :: FSUNLinSolInitialize_Band
 public :: FSUNLinSolSetup_Band
 public :: FSUNLinSolSolve_Band
 public :: FSUNLinSolLastFlag_Band
 public :: FSUNLinSolSpace_Band
 public :: FSUNLinSolFree_Band

! WRAPPER DECLARATIONS
interface
function swigc_FSUNLinSol_Band(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNLinSol_Band") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
type(C_PTR) :: fresult
end function

function swigc_FSUNLinSolGetType_Band(farg1) &
bind(C, name="_wrap_FSUNLinSolGetType_Band") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolGetID_Band(farg1) &
bind(C, name="_wrap_FSUNLinSolGetID_Band") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolInitialize_Band(farg1) &
bind(C, name="_wrap_FSUNLinSolInitialize_Band") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolSetup_Band(farg1, farg2) &
bind(C, name="_wrap_FSUNLinSolSetup_Band") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolSolve_Band(farg1, farg2, farg3, farg4, farg5) &
bind(C, name="_wrap_FSUNLinSolSolve_Band") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
type(C_PTR), value :: farg4
real(C_DOUBLE), intent(in) :: farg5
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolLastFlag_Band(farg1) &
bind(C, name="_wrap_FSUNLinSolLastFlag_Band") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT64_T) :: fresult
end function

function swigc_FSUNLinSolSpace_Band(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNLinSolSpace_Band") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolFree_Band(farg1) &
bind(C, name="_wrap_FSUNLinSolFree_Band") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

end interface


contains
 ! MODULE SUBPROGRAMS
function FSUNLinSol_Band(y, a, sunctx) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(SUNLinearSolver), pointer :: swig_result
type(N_Vector), target, intent(inout) :: y
type(SUNMatrix), target, intent(inout) :: a
type(C_PTR) :: sunctx
type(C_PTR) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 
type(C_PTR) :: farg3 

farg1 = c_loc(y)
farg2 = c_loc(a)
farg3 = sunctx
fresult = swigc_FSUNLinSol_Band(farg1, farg2, farg3)
call c_f_pointer(fresult, swig_result)
end function

function FSUNLinSolGetType_Band(s) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(SUNLinearSolver_Type) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(s)
fresult = swigc_FSUNLinSolGetType_Band(farg1)
swig_result = fresult
end function

function FSUNLinSolGetID_Band(s) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(SUNLinearSolver_ID) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(s)
fresult = swigc_FSUNLinSolGetID_Band(farg1)
swig_result = fresult
end function

function FSUNLinSolInitialize_Band(s) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(s)
fresult = swigc_FSUNLinSolInitialize_Band(farg1)
swig_result = fresult
end function

function FSUNLinSolSetup_Band(s, a) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
type(SUNMatrix), target, intent(inout) :: a
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 

farg1 = c_loc(s)
farg2 = c_loc(a)
fresult = swigc_FSUNLinSolSetup_Band(farg1, farg2)
swig_result = fresult
end function

function FSUNLinSolSolve_Band(s, a, x, b, tol) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
type(SUNMatrix), target, intent(inout) :: a
type(N_Vector), target, intent(inout) :: x
type(N_Vector), target, intent(inout) :: b
real(C_DOUBLE), intent(in) :: tol
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 
type(C_PTR) :: farg3 
type(C_PTR) :: farg4 
real(C_DOUBLE) :: farg5 

farg1 = c_loc(s)
farg2 = c_loc(a)
farg3 = c_loc(x)
farg4 = c_loc(b)
farg5 = tol
fresult = swigc_FSUNLinSolSolve_Band(farg1, farg2, farg3, farg4, farg5)
swig_result = fresult
end function

function FSUNLinSolLastFlag_Band(s) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT64_T) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
integer(C_INT64_T) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(s)
fresult = swigc_FSUNLinSolLastFlag_Band(farg1)
swig_result = fresult
end function

function FSUNLinSolSpace_Band(s, lenrwls, leniwls) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
integer(C_LONG), dimension(*), target, intent(inout) :: lenrwls
integer(C_LONG), dimension(*), target, intent(inout) :: leniwls
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 
type(C_PTR) :: farg3 

farg1 = c_loc(s)
farg2 = c_loc(lenrwls(1))
farg3 = c_loc(leniwls(1))
fresult = swigc_FSUNLinSolSpace_Band(farg1, farg2, farg3)
swig_result = fresult
end function

function FSUNLinSolFree_Band(s) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(s)
fresult = swigc_FSUNLinSolFree_Band(farg1)
swig_result = fresult
end function


end module
