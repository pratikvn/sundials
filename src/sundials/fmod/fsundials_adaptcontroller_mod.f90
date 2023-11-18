! This file was automatically generated by SWIG (http://www.swig.org).
! Version 4.0.0
!
! Do not make changes to this file unless you know what you are doing--modify
! the SWIG interface file instead.
module fsundials_adaptcontroller_mod
 use, intrinsic :: ISO_C_BINDING
 use fsundials_types_mod
 use fsundials_context_mod
 use fsundials_types_mod
 use fsundials_types_mod
 implicit none
 private

 ! DECLARATION CONSTRUCTS
 ! typedef enum SUNAdaptController_Type
 enum, bind(c)
  enumerator :: SUN_ADAPTCONTROLLER_NONE
  enumerator :: SUN_ADAPTCONTROLLER_H
 end enum
 integer, parameter, public :: SUNAdaptController_Type = kind(SUN_ADAPTCONTROLLER_NONE)
 public :: SUN_ADAPTCONTROLLER_NONE, SUN_ADAPTCONTROLLER_H
 ! struct struct _generic_SUNAdaptController_Ops
 type, bind(C), public :: SUNAdaptController_Ops
  type(C_FUNPTR), public :: gettype
  type(C_FUNPTR), public :: estimatestep
  type(C_FUNPTR), public :: destroy
  type(C_FUNPTR), public :: reset
  type(C_FUNPTR), public :: setdefaults
  type(C_FUNPTR), public :: write
  type(C_FUNPTR), public :: seterrorbias
  type(C_FUNPTR), public :: updateh
  type(C_FUNPTR), public :: space
 end type SUNAdaptController_Ops
 ! struct struct _generic_SUNAdaptController
 type, bind(C), public :: SUNAdaptController
  type(C_PTR), public :: content
  type(C_PTR), public :: ops
  type(C_PTR), public :: sunctx
 end type SUNAdaptController
 public :: FSUNAdaptController_NewEmpty
 public :: FSUNAdaptController_GetType
 public :: FSUNAdaptController_Destroy
 public :: FSUNAdaptController_EstimateStep
 public :: FSUNAdaptController_Reset
 public :: FSUNAdaptController_SetDefaults
 public :: FSUNAdaptController_Write
 public :: FSUNAdaptController_SetErrorBias
 public :: FSUNAdaptController_UpdateH
 public :: FSUNAdaptController_Space
 integer(C_INT), parameter, public :: SUNADAPTCONTROLLER_SUCCESS = 0_C_INT
 integer(C_INT), parameter, public :: SUNADAPTCONTROLLER_ILL_INPUT = -1001_C_INT
 integer(C_INT), parameter, public :: SUNADAPTCONTROLLER_MEM_FAIL = -1002_C_INT
 integer(C_INT), parameter, public :: SUNADAPTCONTROLLER_USER_FCN_FAIL = -1003_C_INT
 integer(C_INT), parameter, public :: SUNADAPTCONTROLLER_OPERATION_FAIL = -1004_C_INT

! WRAPPER DECLARATIONS
interface
function swigc_FSUNAdaptController_NewEmpty(farg1) &
bind(C, name="_wrap_FSUNAdaptController_NewEmpty") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR) :: fresult
end function

function swigc_FSUNAdaptController_GetType(farg1) &
bind(C, name="_wrap_FSUNAdaptController_GetType") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_Destroy(farg1) &
bind(C, name="_wrap_FSUNAdaptController_Destroy") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_EstimateStep(farg1, farg2, farg3, farg4, farg5) &
bind(C, name="_wrap_FSUNAdaptController_EstimateStep") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
real(C_DOUBLE), intent(in) :: farg2
integer(C_INT), intent(in) :: farg3
real(C_DOUBLE), intent(in) :: farg4
type(C_PTR), value :: farg5
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_Reset(farg1) &
bind(C, name="_wrap_FSUNAdaptController_Reset") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_SetDefaults(farg1) &
bind(C, name="_wrap_FSUNAdaptController_SetDefaults") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_Write(farg1, farg2) &
bind(C, name="_wrap_FSUNAdaptController_Write") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_SetErrorBias(farg1, farg2) &
bind(C, name="_wrap_FSUNAdaptController_SetErrorBias") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
real(C_DOUBLE), intent(in) :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_UpdateH(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNAdaptController_UpdateH") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
real(C_DOUBLE), intent(in) :: farg2
real(C_DOUBLE), intent(in) :: farg3
integer(C_INT) :: fresult
end function

function swigc_FSUNAdaptController_Space(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNAdaptController_Space") &
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
function FSUNAdaptController_NewEmpty(sunctx) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(SUNAdaptController), pointer :: swig_result
type(C_PTR) :: sunctx
type(C_PTR) :: fresult 
type(C_PTR) :: farg1 

farg1 = sunctx
fresult = swigc_FSUNAdaptController_NewEmpty(farg1)
call c_f_pointer(fresult, swig_result)
end function

function FSUNAdaptController_GetType(c) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(SUNAdaptController_Type) :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(c)
fresult = swigc_FSUNAdaptController_GetType(farg1)
swig_result = fresult
end function

function FSUNAdaptController_Destroy(c) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(c)
fresult = swigc_FSUNAdaptController_Destroy(farg1)
swig_result = fresult
end function

function FSUNAdaptController_EstimateStep(c, h, p, dsm, hnew) &
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
fresult = swigc_FSUNAdaptController_EstimateStep(farg1, farg2, farg3, farg4, farg5)
swig_result = fresult
end function

function FSUNAdaptController_Reset(c) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(c)
fresult = swigc_FSUNAdaptController_Reset(farg1)
swig_result = fresult
end function

function FSUNAdaptController_SetDefaults(c) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNAdaptController), target, intent(inout) :: c
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(c)
fresult = swigc_FSUNAdaptController_SetDefaults(farg1)
swig_result = fresult
end function

function FSUNAdaptController_Write(c, fptr) &
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
fresult = swigc_FSUNAdaptController_Write(farg1, farg2)
swig_result = fresult
end function

function FSUNAdaptController_SetErrorBias(c, bias) &
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
fresult = swigc_FSUNAdaptController_SetErrorBias(farg1, farg2)
swig_result = fresult
end function

function FSUNAdaptController_UpdateH(c, h, dsm) &
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
fresult = swigc_FSUNAdaptController_UpdateH(farg1, farg2, farg3)
swig_result = fresult
end function

function FSUNAdaptController_Space(c, lenrw, leniw) &
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
fresult = swigc_FSUNAdaptController_Space(farg1, farg2, farg3)
swig_result = fresult
end function


end module
