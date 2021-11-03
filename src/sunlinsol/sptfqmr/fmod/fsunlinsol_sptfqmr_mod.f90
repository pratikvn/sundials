! This file was automatically generated by SWIG (http://www.swig.org).
! Version 4.0.0
!
! Do not make changes to this file unless you know what you are doing--modify
! the SWIG interface file instead.

! ---------------------------------------------------------------
! Programmer(s): Auto-generated by swig.
! ---------------------------------------------------------------
! SUNDIALS Copyright Start
! Copyright (c) 2002-2021, Lawrence Livermore National Security
! and Southern Methodist University.
! All rights reserved.
!
! See the top-level LICENSE and NOTICE files for details.
!
! SPDX-License-Identifier: BSD-3-Clause
! SUNDIALS Copyright End
! ---------------------------------------------------------------

module fsunlinsol_sptfqmr_mod
 use, intrinsic :: ISO_C_BINDING
 use fsundials_linearsolver_mod
 use fsundials_types_mod
 use fsundials_nvector_mod
 use fsundials_types_mod
 use fsundials_matrix_mod
 use fsundials_nvector_mod
 use fsundials_types_mod
 implicit none
 private

 ! DECLARATION CONSTRUCTS
 integer(C_INT), parameter, public :: SUNSPTFQMR_MAXL_DEFAULT = 5_C_INT
 public :: FSUNLinSol_SPTFQMR
 public :: FSUNLinSol_SPTFQMRSetPrecType
 public :: FSUNLinSol_SPTFQMRSetMaxl
 public :: FSUNSPTFQMR
 public :: FSUNSPTFQMRSetPrecType
 public :: FSUNSPTFQMRSetMaxl
 public :: FSUNLinSolGetType_SPTFQMR
 public :: FSUNLinSolGetID_SPTFQMR
 public :: FSUNLinSolInitialize_SPTFQMR
 public :: FSUNLinSolSetATimes_SPTFQMR
 public :: FSUNLinSolSetPreconditioner_SPTFQMR
 public :: FSUNLinSolSetScalingVectors_SPTFQMR
 public :: FSUNLinSolSetZeroGuess_SPTFQMR
 public :: FSUNLinSolSetup_SPTFQMR
 public :: FSUNLinSolSolve_SPTFQMR
 public :: FSUNLinSolNumIters_SPTFQMR
 public :: FSUNLinSolResNorm_SPTFQMR
 public :: FSUNLinSolResid_SPTFQMR
 public :: FSUNLinSolLastFlag_SPTFQMR
 public :: FSUNLinSolSpace_SPTFQMR
 public :: FSUNLinSolFree_SPTFQMR
 public :: FSUNLinSolSetInfoFile_SPTFQMR
 public :: FSUNLinSolSetPrintLevel_SPTFQMR

! WRAPPER DECLARATIONS
interface
function swigc_FSUNLinSol_SPTFQMR(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNLinSol_SPTFQMR") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT), intent(in) :: farg2
integer(C_INT), intent(in) :: farg3
type(C_PTR) :: fresult
end function

function swigc_FSUNLinSol_SPTFQMRSetPrecType(farg1, farg2) &
bind(C, name="_wrap_FSUNLinSol_SPTFQMRSetPrecType") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT), intent(in) :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSol_SPTFQMRSetMaxl(farg1, farg2) &
bind(C, name="_wrap_FSUNLinSol_SPTFQMRSetMaxl") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT), intent(in) :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNSPTFQMR(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNSPTFQMR") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT), intent(in) :: farg2
integer(C_INT), intent(in) :: farg3
type(C_PTR) :: fresult
end function

function swigc_FSUNSPTFQMRSetPrecType(farg1, farg2) &
bind(C, name="_wrap_FSUNSPTFQMRSetPrecType") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT), intent(in) :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNSPTFQMRSetMaxl(farg1, farg2) &
bind(C, name="_wrap_FSUNSPTFQMRSetMaxl") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT), intent(in) :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolGetType_SPTFQMR(farg1) &
bind(C, name="_wrap_FSUNLinSolGetType_SPTFQMR") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolGetID_SPTFQMR(farg1) &
bind(C, name="_wrap_FSUNLinSolGetID_SPTFQMR") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolInitialize_SPTFQMR(farg1) &
bind(C, name="_wrap_FSUNLinSolInitialize_SPTFQMR") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolSetATimes_SPTFQMR(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNLinSolSetATimes_SPTFQMR") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_FUNPTR), value :: farg3
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolSetPreconditioner_SPTFQMR(farg1, farg2, farg3, farg4) &
bind(C, name="_wrap_FSUNLinSolSetPreconditioner_SPTFQMR") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_FUNPTR), value :: farg3
type(C_FUNPTR), value :: farg4
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolSetScalingVectors_SPTFQMR(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNLinSolSetScalingVectors_SPTFQMR") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolSetZeroGuess_SPTFQMR(farg1, farg2) &
bind(C, name="_wrap_FSUNLinSolSetZeroGuess_SPTFQMR") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT), intent(in) :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolSetup_SPTFQMR(farg1, farg2) &
bind(C, name="_wrap_FSUNLinSolSetup_SPTFQMR") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolSolve_SPTFQMR(farg1, farg2, farg3, farg4, farg5) &
bind(C, name="_wrap_FSUNLinSolSolve_SPTFQMR") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
type(C_PTR), value :: farg4
real(C_DOUBLE), intent(in) :: farg5
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolNumIters_SPTFQMR(farg1) &
bind(C, name="_wrap_FSUNLinSolNumIters_SPTFQMR") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolResNorm_SPTFQMR(farg1) &
bind(C, name="_wrap_FSUNLinSolResNorm_SPTFQMR") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
real(C_DOUBLE) :: fresult
end function

function swigc_FSUNLinSolResid_SPTFQMR(farg1) &
bind(C, name="_wrap_FSUNLinSolResid_SPTFQMR") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR) :: fresult
end function

function swigc_FSUNLinSolLastFlag_SPTFQMR(farg1) &
bind(C, name="_wrap_FSUNLinSolLastFlag_SPTFQMR") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT64_T) :: fresult
end function

function swigc_FSUNLinSolSpace_SPTFQMR(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNLinSolSpace_SPTFQMR") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolFree_SPTFQMR(farg1) &
bind(C, name="_wrap_FSUNLinSolFree_SPTFQMR") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolSetInfoFile_SPTFQMR(farg1, farg2) &
bind(C, name="_wrap_FSUNLinSolSetInfoFile_SPTFQMR") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolSetPrintLevel_SPTFQMR(farg1, farg2) &
bind(C, name="_wrap_FSUNLinSolSetPrintLevel_SPTFQMR") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT), intent(in) :: farg2
integer(C_INT) :: fresult
end function

end interface


contains
 ! MODULE SUBPROGRAMS
function FSUNLinSol_SPTFQMR(y, pretype, maxl) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(SUNLinearSolver), pointer :: swig_result
type(N_Vector), target, intent(inout) :: y
integer(C_INT), intent(in) :: pretype
integer(C_INT), intent(in) :: maxl
type(C_PTR) :: fresult 
type(C_PTR) :: farg1 
integer(C_INT) :: farg2 
integer(C_INT) :: farg3 

farg1 = c_loc(y)
farg2 = pretype
farg3 = maxl
fresult = swigc_FSUNLinSol_SPTFQMR(farg1, farg2, farg3)
call c_f_pointer(fresult, swig_result)
end function

function FSUNLinSol_SPTFQMRSetPrecType(s, pretype) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
integer(C_INT), intent(in) :: pretype
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
integer(C_INT) :: farg2 

farg1 = c_loc(s)
farg2 = pretype
fresult = swigc_FSUNLinSol_SPTFQMRSetPrecType(farg1, farg2)
swig_result = fresult
end function

function FSUNLinSol_SPTFQMRSetMaxl(s, maxl) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
integer(C_INT), intent(in) :: maxl
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
integer(C_INT) :: farg2 

farg1 = c_loc(s)
farg2 = maxl
fresult = swigc_FSUNLinSol_SPTFQMRSetMaxl(farg1, farg2)
swig_result = fresult
end function

function FSUNSPTFQMR(y, pretype, maxl) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(SUNLinearSolver), pointer :: swig_result
type(N_Vector), target, intent(inout) :: y
integer(C_INT), intent(in) :: pretype
integer(C_INT), intent(in) :: maxl
type(C_PTR) :: fresult 
type(C_PTR) :: farg1 
integer(C_INT) :: farg2 
integer(C_INT) :: farg3 

farg1 = c_loc(y)
farg2 = pretype
farg3 = maxl
fresult = swigc_FSUNSPTFQMR(farg1, farg2, farg3)
call c_f_pointer(fresult, swig_result)
end function

function FSUNSPTFQMRSetPrecType(s, pretype) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
integer(C_INT), intent(in) :: pretype
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
integer(C_INT) :: farg2 

farg1 = c_loc(s)
farg2 = pretype
fresult = swigc_FSUNSPTFQMRSetPrecType(farg1, farg2)
swig_result = fresult
end function

function FSUNSPTFQMRSetMaxl(s, maxl) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
integer(C_INT), intent(in) :: maxl
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
integer(C_INT) :: farg2 

farg1 = c_loc(s)
farg2 = maxl
fresult = swigc_FSUNSPTFQMRSetMaxl(farg1, farg2)
swig_result = fresult
end function

function FSUNLinSolGetType_SPTFQMR(s) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(SUNLinearSolver_Type) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(s)
fresult = swigc_FSUNLinSolGetType_SPTFQMR(farg1)
swig_result = fresult
end function

function FSUNLinSolGetID_SPTFQMR(s) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(SUNLinearSolver_ID) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(s)
fresult = swigc_FSUNLinSolGetID_SPTFQMR(farg1)
swig_result = fresult
end function

function FSUNLinSolInitialize_SPTFQMR(s) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(s)
fresult = swigc_FSUNLinSolInitialize_SPTFQMR(farg1)
swig_result = fresult
end function

function FSUNLinSolSetATimes_SPTFQMR(s, a_data, atimes) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
type(C_PTR) :: a_data
type(C_FUNPTR), intent(in), value :: atimes
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 
type(C_FUNPTR) :: farg3 

farg1 = c_loc(s)
farg2 = a_data
farg3 = atimes
fresult = swigc_FSUNLinSolSetATimes_SPTFQMR(farg1, farg2, farg3)
swig_result = fresult
end function

function FSUNLinSolSetPreconditioner_SPTFQMR(s, p_data, pset, psol) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
type(C_PTR) :: p_data
type(C_FUNPTR), intent(in), value :: pset
type(C_FUNPTR), intent(in), value :: psol
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 
type(C_FUNPTR) :: farg3 
type(C_FUNPTR) :: farg4 

farg1 = c_loc(s)
farg2 = p_data
farg3 = pset
farg4 = psol
fresult = swigc_FSUNLinSolSetPreconditioner_SPTFQMR(farg1, farg2, farg3, farg4)
swig_result = fresult
end function

function FSUNLinSolSetScalingVectors_SPTFQMR(s, s1, s2) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
type(N_Vector), target, intent(inout) :: s1
type(N_Vector), target, intent(inout) :: s2
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 
type(C_PTR) :: farg3 

farg1 = c_loc(s)
farg2 = c_loc(s1)
farg3 = c_loc(s2)
fresult = swigc_FSUNLinSolSetScalingVectors_SPTFQMR(farg1, farg2, farg3)
swig_result = fresult
end function

function FSUNLinSolSetZeroGuess_SPTFQMR(s, onoff) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
integer(C_INT), intent(in) :: onoff
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
integer(C_INT) :: farg2 

farg1 = c_loc(s)
farg2 = onoff
fresult = swigc_FSUNLinSolSetZeroGuess_SPTFQMR(farg1, farg2)
swig_result = fresult
end function

function FSUNLinSolSetup_SPTFQMR(s, a) &
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
fresult = swigc_FSUNLinSolSetup_SPTFQMR(farg1, farg2)
swig_result = fresult
end function

function FSUNLinSolSolve_SPTFQMR(s, a, x, b, tol) &
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
fresult = swigc_FSUNLinSolSolve_SPTFQMR(farg1, farg2, farg3, farg4, farg5)
swig_result = fresult
end function

function FSUNLinSolNumIters_SPTFQMR(s) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(s)
fresult = swigc_FSUNLinSolNumIters_SPTFQMR(farg1)
swig_result = fresult
end function

function FSUNLinSolResNorm_SPTFQMR(s) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
real(C_DOUBLE) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
real(C_DOUBLE) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(s)
fresult = swigc_FSUNLinSolResNorm_SPTFQMR(farg1)
swig_result = fresult
end function

function FSUNLinSolResid_SPTFQMR(s) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(N_Vector), pointer :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
type(C_PTR) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(s)
fresult = swigc_FSUNLinSolResid_SPTFQMR(farg1)
call c_f_pointer(fresult, swig_result)
end function

function FSUNLinSolLastFlag_SPTFQMR(s) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT64_T) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
integer(C_INT64_T) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(s)
fresult = swigc_FSUNLinSolLastFlag_SPTFQMR(farg1)
swig_result = fresult
end function

function FSUNLinSolSpace_SPTFQMR(s, lenrwls, leniwls) &
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
fresult = swigc_FSUNLinSolSpace_SPTFQMR(farg1, farg2, farg3)
swig_result = fresult
end function

function FSUNLinSolFree_SPTFQMR(s) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(s)
fresult = swigc_FSUNLinSolFree_SPTFQMR(farg1)
swig_result = fresult
end function

function FSUNLinSolSetInfoFile_SPTFQMR(ls, info_file) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: ls
type(C_PTR) :: info_file
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 

farg1 = c_loc(ls)
farg2 = info_file
fresult = swigc_FSUNLinSolSetInfoFile_SPTFQMR(farg1, farg2)
swig_result = fresult
end function

function FSUNLinSolSetPrintLevel_SPTFQMR(ls, print_level) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: ls
integer(C_INT), intent(in) :: print_level
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
integer(C_INT) :: farg2 

farg1 = c_loc(ls)
farg2 = print_level
fresult = swigc_FSUNLinSolSetPrintLevel_SPTFQMR(farg1, farg2)
swig_result = fresult
end function


end module
