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

module fsunadaptcontroller_soderlind_mod
 use, intrinsic :: ISO_C_BINDING
 use fsundials_adaptcontroller_mod
 use fsundials_types_mod
 use fsundials_context_mod
 use fsundials_types_mod
 implicit none
 private

 ! DECLARATION CONSTRUCTS
 public :: FSUNAdaptController_Soderlind
 public :: FSUNAdaptController_SetParams_Soderlind
 public :: FSUNAdaptController_GetType_Soderlind
 public :: FSUNAdaptController_EstimateStep_Soderlind
 public :: FSUNAdaptController_Reset_Soderlind
 public :: FSUNAdaptController_SetDefaults_Soderlind
 public :: FSUNAdaptController_Write_Soderlind
 public :: FSUNAdaptController_SetErrorBias_Soderlind
 public :: FSUNAdaptController_UpdateH_Soderlind
 public :: FSUNAdaptController_Space_Soderlind
 public :: FSUNAdaptController_PID
 public :: FSUNAdaptController_SetParams_PID
 public :: FSUNAdaptController_PI
 public :: FSUNAdaptController_SetParams_PI
 public :: FSUNAdaptController_I
 public :: FSUNAdaptController_SetParams_I
 public :: FSUNAdaptController_ExpGus
 public :: FSUNAdaptController_SetParams_ExpGus
 public :: FSUNAdaptController_ImpGus
 public :: FSUNAdaptController_SetParams_ImpGus

! WRAPPER DECLARATIONS
interface
function swigc_FSUNAdaptController_Soderlind(farg1) &
bind(C, name="_wrap_FSUNAdaptController_Soderlind") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR) :: fresult
end function

function swigc_FSUNAdaptController_SetParams_Soderlind(farg1, farg2, farg3, farg4, farg5, farg6) &
bind(C, name="_wrap_FSUNAdaptController_SetParams_Soderlind") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
real(C_DOUBLE), intent(in) :: farg2
real(C_DOUBLE), intent(in) :: farg3
real(C_DOUBLE), intent(in) :: farg4
real(C_DOUBLE), intent(in) :: farg5
real(C_DOUBLE), intent(in) :: farg6
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_GetType_Soderlind(farg1) &
bind(C, name="_wrap_FSUNAdaptController_GetType_Soderlind") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_EstimateStep_Soderlind(farg1, farg2, farg3, farg4, farg5) &
bind(C, name="_wrap_FSUNAdaptController_EstimateStep_Soderlind") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
real(C_DOUBLE), intent(in) :: farg2
integer(C_INT), intent(in) :: farg3
real(C_DOUBLE), intent(in) :: farg4
type(C_PTR), value :: farg5
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_Reset_Soderlind(farg1) &
bind(C, name="_wrap_FSUNAdaptController_Reset_Soderlind") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_SetDefaults_Soderlind(farg1) &
bind(C, name="_wrap_FSUNAdaptController_SetDefaults_Soderlind") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_Write_Soderlind(farg1, farg2) &
bind(C, name="_wrap_FSUNAdaptController_Write_Soderlind") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_SetErrorBias_Soderlind(farg1, farg2) &
bind(C, name="_wrap_FSUNAdaptController_SetErrorBias_Soderlind") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
real(C_DOUBLE), intent(in) :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_UpdateH_Soderlind(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNAdaptController_UpdateH_Soderlind") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
real(C_DOUBLE), intent(in) :: farg2
real(C_DOUBLE), intent(in) :: farg3
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_Space_Soderlind(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNAdaptController_Space_Soderlind") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_PID(farg1) &
bind(C, name="_wrap_FSUNAdaptController_PID") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR) :: fresult
end function

function swigc_FSUNAdaptController_SetParams_PID(farg1, farg2, farg3, farg4) &
bind(C, name="_wrap_FSUNAdaptController_SetParams_PID") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
real(C_DOUBLE), intent(in) :: farg2
real(C_DOUBLE), intent(in) :: farg3
real(C_DOUBLE), intent(in) :: farg4
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_PI(farg1) &
bind(C, name="_wrap_FSUNAdaptController_PI") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR) :: fresult
end function

function swigc_FSUNAdaptController_SetParams_PI(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNAdaptController_SetParams_PI") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
real(C_DOUBLE), intent(in) :: farg2
real(C_DOUBLE), intent(in) :: farg3
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_I(farg1) &
bind(C, name="_wrap_FSUNAdaptController_I") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR) :: fresult
end function

function swigc_FSUNAdaptController_SetParams_I(farg1, farg2) &
bind(C, name="_wrap_FSUNAdaptController_SetParams_I") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
real(C_DOUBLE), intent(in) :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_ExpGus(farg1) &
bind(C, name="_wrap_FSUNAdaptController_ExpGus") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR) :: fresult
end function

function swigc_FSUNAdaptController_SetParams_ExpGus(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNAdaptController_SetParams_ExpGus") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
real(C_DOUBLE), intent(in) :: farg2
real(C_DOUBLE), intent(in) :: farg3
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_ImpGus(farg1) &
bind(C, name="_wrap_FSUNAdaptController_ImpGus") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR) :: fresult
end function

function swigc_FSUNAdaptController_SetParams_ImpGus(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNAdaptController_SetParams_ImpGus") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
real(C_DOUBLE), intent(in) :: farg2
real(C_DOUBLE), intent(in) :: farg3
integer(C_INT) :: fresult
end function

end interface


contains
 ! MODULE SUBPROGRAMS
function FSUNAdaptController_Soderlind(sunctx) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(SUNAdaptController), pointer :: swig_result
type(C_PTR) :: sunctx
type(C_PTR) :: fresult 
type(C_PTR) :: farg1 

farg1 = sunctx
fresult = swigc_FSUNAdaptController_Soderlind(farg1)
call c_f_pointer(fresult, swig_result)
end function

function FSUNAdaptController_SetParams_Soderlind(c, k1, k2, k3, k4, k5) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
real(C_DOUBLE), intent(in) :: k1
real(C_DOUBLE), intent(in) :: k2
real(C_DOUBLE), intent(in) :: k3
real(C_DOUBLE), intent(in) :: k4
real(C_DOUBLE), intent(in) :: k5
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
real(C_DOUBLE) :: farg2 
real(C_DOUBLE) :: farg3 
real(C_DOUBLE) :: farg4 
real(C_DOUBLE) :: farg5 
real(C_DOUBLE) :: farg6 

farg1 = c_loc(c)
farg2 = k1
farg3 = k2
farg4 = k3
farg5 = k4
farg6 = k5
fresult = swigc_FSUNAdaptController_SetParams_Soderlind(farg1, farg2, farg3, farg4, farg5, farg6)
swig_result = fresult
end function

function FSUNAdaptController_GetType_Soderlind(c) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(SUNAdaptController_Type) :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(c)
fresult = swigc_FSUNAdaptController_GetType_Soderlind(farg1)
swig_result = fresult
end function

function FSUNAdaptController_EstimateStep_Soderlind(c, h, p, dsm, hnew) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
real(C_DOUBLE), intent(in) :: h
integer(C_INT), intent(in) :: p
real(C_DOUBLE), intent(in) :: dsm
real(C_DOUBLE), dimension(*), target, intent(inout) :: hnew
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
real(C_DOUBLE) :: farg2 
integer(C_INT) :: farg3 
real(C_DOUBLE) :: farg4 
type(C_PTR) :: farg5 

farg1 = c_loc(c)
farg2 = h
farg3 = p
farg4 = dsm
farg5 = c_loc(hnew(1))
fresult = swigc_FSUNAdaptController_EstimateStep_Soderlind(farg1, farg2, farg3, farg4, farg5)
swig_result = fresult
end function

function FSUNAdaptController_Reset_Soderlind(c) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(c)
fresult = swigc_FSUNAdaptController_Reset_Soderlind(farg1)
swig_result = fresult
end function

function FSUNAdaptController_SetDefaults_Soderlind(c) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(c)
fresult = swigc_FSUNAdaptController_SetDefaults_Soderlind(farg1)
swig_result = fresult
end function

function FSUNAdaptController_Write_Soderlind(c, fptr) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
type(C_PTR) :: fptr
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 

farg1 = c_loc(c)
farg2 = fptr
fresult = swigc_FSUNAdaptController_Write_Soderlind(farg1, farg2)
swig_result = fresult
end function

function FSUNAdaptController_SetErrorBias_Soderlind(c, bias) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
real(C_DOUBLE), intent(in) :: bias
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
real(C_DOUBLE) :: farg2 

farg1 = c_loc(c)
farg2 = bias
fresult = swigc_FSUNAdaptController_SetErrorBias_Soderlind(farg1, farg2)
swig_result = fresult
end function

function FSUNAdaptController_UpdateH_Soderlind(c, h, dsm) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
real(C_DOUBLE), intent(in) :: h
real(C_DOUBLE), intent(in) :: dsm
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
real(C_DOUBLE) :: farg2 
real(C_DOUBLE) :: farg3 

farg1 = c_loc(c)
farg2 = h
farg3 = dsm
fresult = swigc_FSUNAdaptController_UpdateH_Soderlind(farg1, farg2, farg3)
swig_result = fresult
end function

function FSUNAdaptController_Space_Soderlind(c, lenrw, leniw) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
integer(C_LONG), dimension(*), target, intent(inout) :: lenrw
integer(C_LONG), dimension(*), target, intent(inout) :: leniw
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 
type(C_PTR) :: farg3 

farg1 = c_loc(c)
farg2 = c_loc(lenrw(1))
farg3 = c_loc(leniw(1))
fresult = swigc_FSUNAdaptController_Space_Soderlind(farg1, farg2, farg3)
swig_result = fresult
end function

function FSUNAdaptController_PID(sunctx) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(SUNAdaptController), pointer :: swig_result
type(C_PTR) :: sunctx
type(C_PTR) :: fresult 
type(C_PTR) :: farg1 

farg1 = sunctx
fresult = swigc_FSUNAdaptController_PID(farg1)
call c_f_pointer(fresult, swig_result)
end function

function FSUNAdaptController_SetParams_PID(c, k1, k2, k3) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
real(C_DOUBLE), intent(in) :: k1
real(C_DOUBLE), intent(in) :: k2
real(C_DOUBLE), intent(in) :: k3
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
real(C_DOUBLE) :: farg2 
real(C_DOUBLE) :: farg3 
real(C_DOUBLE) :: farg4 

farg1 = c_loc(c)
farg2 = k1
farg3 = k2
farg4 = k3
fresult = swigc_FSUNAdaptController_SetParams_PID(farg1, farg2, farg3, farg4)
swig_result = fresult
end function

function FSUNAdaptController_PI(sunctx) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(SUNAdaptController), pointer :: swig_result
type(C_PTR) :: sunctx
type(C_PTR) :: fresult 
type(C_PTR) :: farg1 

farg1 = sunctx
fresult = swigc_FSUNAdaptController_PI(farg1)
call c_f_pointer(fresult, swig_result)
end function

function FSUNAdaptController_SetParams_PI(c, k1, k2) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
real(C_DOUBLE), intent(in) :: k1
real(C_DOUBLE), intent(in) :: k2
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
real(C_DOUBLE) :: farg2 
real(C_DOUBLE) :: farg3 

farg1 = c_loc(c)
farg2 = k1
farg3 = k2
fresult = swigc_FSUNAdaptController_SetParams_PI(farg1, farg2, farg3)
swig_result = fresult
end function

function FSUNAdaptController_I(sunctx) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(SUNAdaptController), pointer :: swig_result
type(C_PTR) :: sunctx
type(C_PTR) :: fresult 
type(C_PTR) :: farg1 

farg1 = sunctx
fresult = swigc_FSUNAdaptController_I(farg1)
call c_f_pointer(fresult, swig_result)
end function

function FSUNAdaptController_SetParams_I(c, k1) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
real(C_DOUBLE), intent(in) :: k1
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
real(C_DOUBLE) :: farg2 

farg1 = c_loc(c)
farg2 = k1
fresult = swigc_FSUNAdaptController_SetParams_I(farg1, farg2)
swig_result = fresult
end function

function FSUNAdaptController_ExpGus(sunctx) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(SUNAdaptController), pointer :: swig_result
type(C_PTR) :: sunctx
type(C_PTR) :: fresult 
type(C_PTR) :: farg1 

farg1 = sunctx
fresult = swigc_FSUNAdaptController_ExpGus(farg1)
call c_f_pointer(fresult, swig_result)
end function

function FSUNAdaptController_SetParams_ExpGus(c, k1, k2) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
real(C_DOUBLE), intent(in) :: k1
real(C_DOUBLE), intent(in) :: k2
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
real(C_DOUBLE) :: farg2 
real(C_DOUBLE) :: farg3 

farg1 = c_loc(c)
farg2 = k1
farg3 = k2
fresult = swigc_FSUNAdaptController_SetParams_ExpGus(farg1, farg2, farg3)
swig_result = fresult
end function

function FSUNAdaptController_ImpGus(sunctx) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(SUNAdaptController), pointer :: swig_result
type(C_PTR) :: sunctx
type(C_PTR) :: fresult 
type(C_PTR) :: farg1 

farg1 = sunctx
fresult = swigc_FSUNAdaptController_ImpGus(farg1)
call c_f_pointer(fresult, swig_result)
end function

function FSUNAdaptController_SetParams_ImpGus(c, k1, k2) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
real(C_DOUBLE), intent(in) :: k1
real(C_DOUBLE), intent(in) :: k2
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
real(C_DOUBLE) :: farg2 
real(C_DOUBLE) :: farg3 

farg1 = c_loc(c)
farg2 = k1
farg3 = k2
fresult = swigc_FSUNAdaptController_SetParams_ImpGus(farg1, farg2, farg3)
swig_result = fresult
end function


end module
