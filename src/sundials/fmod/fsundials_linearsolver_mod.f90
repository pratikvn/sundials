! This file was automatically generated by SWIG (http://www.swig.org).
! Version 4.0.0
!
! Do not make changes to this file unless you know what you are doing--modify
! the SWIG interface file instead.
module fsundials_linearsolver_mod
 use, intrinsic :: ISO_C_BINDING
 use fsundials_types_mod
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
 enum, bind(c)
  enumerator :: SUN_PREC_NONE
  enumerator :: SUN_PREC_LEFT
  enumerator :: SUN_PREC_RIGHT
  enumerator :: SUN_PREC_BOTH
 end enum
 public :: SUN_PREC_NONE, SUN_PREC_LEFT, SUN_PREC_RIGHT, SUN_PREC_BOTH
 enum, bind(c)
  enumerator :: SUN_MODIFIED_GS = 1
  enumerator :: SUN_CLASSICAL_GS = 2
 end enum
 public :: SUN_MODIFIED_GS, SUN_CLASSICAL_GS
 public :: FSUNModifiedGS
 public :: FSUNClassicalGS
 public :: FSUNQRfact
 public :: FSUNQRsol
 public :: FSUNQRAdd_MGS
 public :: FSUNQRAdd_ICWY
 public :: FSUNQRAdd_ICWY_SB
 public :: FSUNQRAdd_CGS2
 public :: FSUNQRAdd_DCGS2
 public :: FSUNQRAdd_DCGS2_SB
 ! typedef enum SUNLinearSolver_Type
 enum, bind(c)
  enumerator :: SUNLINEARSOLVER_DIRECT
  enumerator :: SUNLINEARSOLVER_ITERATIVE
  enumerator :: SUNLINEARSOLVER_MATRIX_ITERATIVE
  enumerator :: SUNLINEARSOLVER_MATRIX_EMBEDDED
 end enum
 integer, parameter, public :: SUNLinearSolver_Type = kind(SUNLINEARSOLVER_DIRECT)
 public :: SUNLINEARSOLVER_DIRECT, SUNLINEARSOLVER_ITERATIVE, SUNLINEARSOLVER_MATRIX_ITERATIVE, &
    SUNLINEARSOLVER_MATRIX_EMBEDDED
 ! typedef enum SUNLinearSolver_ID
 enum, bind(c)
  enumerator :: SUNLINEARSOLVER_BAND
  enumerator :: SUNLINEARSOLVER_DENSE
  enumerator :: SUNLINEARSOLVER_KLU
  enumerator :: SUNLINEARSOLVER_LAPACKBAND
  enumerator :: SUNLINEARSOLVER_LAPACKDENSE
  enumerator :: SUNLINEARSOLVER_PCG
  enumerator :: SUNLINEARSOLVER_SPBCGS
  enumerator :: SUNLINEARSOLVER_SPFGMR
  enumerator :: SUNLINEARSOLVER_SPGMR
  enumerator :: SUNLINEARSOLVER_SPTFQMR
  enumerator :: SUNLINEARSOLVER_SUPERLUDIST
  enumerator :: SUNLINEARSOLVER_SUPERLUMT
  enumerator :: SUNLINEARSOLVER_CUSOLVERSP_BATCHQR
  enumerator :: SUNLINEARSOLVER_MAGMADENSE
  enumerator :: SUNLINEARSOLVER_ONEMKLDENSE
  enumerator :: SUNLINEARSOLVER_GINKGO
  enumerator :: SUNLINEARSOLVER_KOKKOSDENSE
  enumerator :: SUNLINEARSOLVER_CUSTOM
 end enum
 integer, parameter, public :: SUNLinearSolver_ID = kind(SUNLINEARSOLVER_BAND)
 public :: SUNLINEARSOLVER_BAND, SUNLINEARSOLVER_DENSE, SUNLINEARSOLVER_KLU, SUNLINEARSOLVER_LAPACKBAND, &
    SUNLINEARSOLVER_LAPACKDENSE, SUNLINEARSOLVER_PCG, SUNLINEARSOLVER_SPBCGS, SUNLINEARSOLVER_SPFGMR, SUNLINEARSOLVER_SPGMR, &
    SUNLINEARSOLVER_SPTFQMR, SUNLINEARSOLVER_SUPERLUDIST, SUNLINEARSOLVER_SUPERLUMT, SUNLINEARSOLVER_CUSOLVERSP_BATCHQR, &
    SUNLINEARSOLVER_MAGMADENSE, SUNLINEARSOLVER_ONEMKLDENSE, SUNLINEARSOLVER_GINKGO, SUNLINEARSOLVER_KOKKOSDENSE, &
    SUNLINEARSOLVER_CUSTOM
 ! struct struct _generic_SUNLinearSolver_Ops
 type, bind(C), public :: SUNLinearSolver_Ops
  type(C_FUNPTR), public :: gettype
  type(C_FUNPTR), public :: getid
  type(C_FUNPTR), public :: setatimes
  type(C_FUNPTR), public :: setpreconditioner
  type(C_FUNPTR), public :: setscalingvectors
  type(C_FUNPTR), public :: setzeroguess
  type(C_FUNPTR), public :: initialize
  type(C_FUNPTR), public :: setup
  type(C_FUNPTR), public :: solve
  type(C_FUNPTR), public :: numiters
  type(C_FUNPTR), public :: resnorm
  type(C_FUNPTR), public :: lastflag
  type(C_FUNPTR), public :: space
  type(C_FUNPTR), public :: resid
  type(C_FUNPTR), public :: free
 end type SUNLinearSolver_Ops
 ! struct struct _generic_SUNLinearSolver
 type, bind(C), public :: SUNLinearSolver
  type(C_PTR), public :: content
  type(C_PTR), public :: ops
  type(C_PTR), public :: sunctx
 end type SUNLinearSolver
 public :: FSUNLinSolNewEmpty
 public :: FSUNLinSolFreeEmpty
 public :: FSUNLinSolGetType
 public :: FSUNLinSolGetID
 public :: FSUNLinSolSetATimes
 public :: FSUNLinSolSetPreconditioner
 public :: FSUNLinSolSetScalingVectors
 public :: FSUNLinSolSetZeroGuess
 public :: FSUNLinSolInitialize
 public :: FSUNLinSolSetup
 public :: FSUNLinSolSolve
 public :: FSUNLinSolNumIters
 public :: FSUNLinSolResNorm
 public :: FSUNLinSolResid
 public :: FSUNLinSolLastFlag
 public :: FSUNLinSolSpace
 public :: FSUNLinSolFree
 integer(C_INT), parameter, public :: SUNLS_SUCCESS = 0_C_INT
 integer(C_INT), parameter, public :: SUNLS_UNRECOV_FAILURE = -800_C_INT
 integer(C_INT), parameter, public :: SUNLS_MEM_NULL = -801_C_INT
 integer(C_INT), parameter, public :: SUNLS_ILL_INPUT = -802_C_INT
 integer(C_INT), parameter, public :: SUNLS_MEM_FAIL = -803_C_INT
 integer(C_INT), parameter, public :: SUNLS_ATIMES_NULL = -804_C_INT
 integer(C_INT), parameter, public :: SUNLS_ATIMES_FAIL_UNREC = -805_C_INT
 integer(C_INT), parameter, public :: SUNLS_PSET_FAIL_UNREC = -806_C_INT
 integer(C_INT), parameter, public :: SUNLS_PSOLVE_NULL = -807_C_INT
 integer(C_INT), parameter, public :: SUNLS_PSOLVE_FAIL_UNREC = -808_C_INT
 integer(C_INT), parameter, public :: SUNLS_PACKAGE_FAIL_UNREC = -809_C_INT
 integer(C_INT), parameter, public :: SUNLS_GS_FAIL = -810_C_INT
 integer(C_INT), parameter, public :: SUNLS_QRSOL_FAIL = -811_C_INT
 integer(C_INT), parameter, public :: SUNLS_VECTOROP_ERR = -812_C_INT
 integer(C_INT), parameter, public :: SUNLS_RECOV_FAILURE = 800_C_INT
 integer(C_INT), parameter, public :: SUNLS_RES_REDUCED = 801_C_INT
 integer(C_INT), parameter, public :: SUNLS_CONV_FAIL = 802_C_INT
 integer(C_INT), parameter, public :: SUNLS_ATIMES_FAIL_REC = 803_C_INT
 integer(C_INT), parameter, public :: SUNLS_PSET_FAIL_REC = 804_C_INT
 integer(C_INT), parameter, public :: SUNLS_PSOLVE_FAIL_REC = 805_C_INT
 integer(C_INT), parameter, public :: SUNLS_PACKAGE_FAIL_REC = 806_C_INT
 integer(C_INT), parameter, public :: SUNLS_QRFACT_FAIL = 807_C_INT
 integer(C_INT), parameter, public :: SUNLS_LUFACT_FAIL = 808_C_INT

! WRAPPER DECLARATIONS
interface
function swigc_FSUNModifiedGS(farg1, farg2, farg3, farg4, farg5) &
bind(C, name="_wrap_FSUNModifiedGS") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT), intent(in) :: farg3
integer(C_INT), intent(in) :: farg4
type(C_PTR), value :: farg5
integer(C_INT) :: fresult
end function

function swigc_FSUNClassicalGS(farg1, farg2, farg3, farg4, farg5, farg6, farg7) &
bind(C, name="_wrap_FSUNClassicalGS") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT), intent(in) :: farg3
integer(C_INT), intent(in) :: farg4
type(C_PTR), value :: farg5
type(C_PTR), value :: farg6
type(C_PTR), value :: farg7
integer(C_INT) :: fresult
end function

function swigc_FSUNQRfact(farg1, farg2, farg3, farg4) &
bind(C, name="_wrap_FSUNQRfact") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
integer(C_INT), intent(in) :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
integer(C_INT), intent(in) :: farg4
integer(C_INT) :: fresult
end function

function swigc_FSUNQRsol(farg1, farg2, farg3, farg4) &
bind(C, name="_wrap_FSUNQRsol") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
integer(C_INT), intent(in) :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
type(C_PTR), value :: farg4
integer(C_INT) :: fresult
end function

function swigc_FSUNQRAdd_MGS(farg1, farg2, farg3, farg4, farg5, farg6) &
bind(C, name="_wrap_FSUNQRAdd_MGS") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
integer(C_INT), intent(in) :: farg4
integer(C_INT), intent(in) :: farg5
type(C_PTR), value :: farg6
integer(C_INT) :: fresult
end function

function swigc_FSUNQRAdd_ICWY(farg1, farg2, farg3, farg4, farg5, farg6) &
bind(C, name="_wrap_FSUNQRAdd_ICWY") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
integer(C_INT), intent(in) :: farg4
integer(C_INT), intent(in) :: farg5
type(C_PTR), value :: farg6
integer(C_INT) :: fresult
end function

function swigc_FSUNQRAdd_ICWY_SB(farg1, farg2, farg3, farg4, farg5, farg6) &
bind(C, name="_wrap_FSUNQRAdd_ICWY_SB") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
integer(C_INT), intent(in) :: farg4
integer(C_INT), intent(in) :: farg5
type(C_PTR), value :: farg6
integer(C_INT) :: fresult
end function

function swigc_FSUNQRAdd_CGS2(farg1, farg2, farg3, farg4, farg5, farg6) &
bind(C, name="_wrap_FSUNQRAdd_CGS2") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
integer(C_INT), intent(in) :: farg4
integer(C_INT), intent(in) :: farg5
type(C_PTR), value :: farg6
integer(C_INT) :: fresult
end function

function swigc_FSUNQRAdd_DCGS2(farg1, farg2, farg3, farg4, farg5, farg6) &
bind(C, name="_wrap_FSUNQRAdd_DCGS2") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
integer(C_INT), intent(in) :: farg4
integer(C_INT), intent(in) :: farg5
type(C_PTR), value :: farg6
integer(C_INT) :: fresult
end function

function swigc_FSUNQRAdd_DCGS2_SB(farg1, farg2, farg3, farg4, farg5, farg6) &
bind(C, name="_wrap_FSUNQRAdd_DCGS2_SB") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
integer(C_INT), intent(in) :: farg4
integer(C_INT), intent(in) :: farg5
type(C_PTR), value :: farg6
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolNewEmpty(farg1) &
bind(C, name="_wrap_FSUNLinSolNewEmpty") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR) :: fresult
end function

subroutine swigc_FSUNLinSolFreeEmpty(farg1) &
bind(C, name="_wrap_FSUNLinSolFreeEmpty")
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
end subroutine

function swigc_FSUNLinSolGetType(farg1) &
bind(C, name="_wrap_FSUNLinSolGetType") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolGetID(farg1) &
bind(C, name="_wrap_FSUNLinSolGetID") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolSetATimes(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNLinSolSetATimes") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_FUNPTR), value :: farg3
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolSetPreconditioner(farg1, farg2, farg3, farg4) &
bind(C, name="_wrap_FSUNLinSolSetPreconditioner") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_FUNPTR), value :: farg3
type(C_FUNPTR), value :: farg4
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolSetScalingVectors(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNLinSolSetScalingVectors") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolSetZeroGuess(farg1, farg2) &
bind(C, name="_wrap_FSUNLinSolSetZeroGuess") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT), intent(in) :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolInitialize(farg1) &
bind(C, name="_wrap_FSUNLinSolInitialize") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolSetup(farg1, farg2) &
bind(C, name="_wrap_FSUNLinSolSetup") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolSolve(farg1, farg2, farg3, farg4, farg5) &
bind(C, name="_wrap_FSUNLinSolSolve") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
type(C_PTR), value :: farg4
real(C_DOUBLE), intent(in) :: farg5
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolNumIters(farg1) &
bind(C, name="_wrap_FSUNLinSolNumIters") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolResNorm(farg1) &
bind(C, name="_wrap_FSUNLinSolResNorm") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
real(C_DOUBLE) :: fresult
end function

function swigc_FSUNLinSolResid(farg1) &
bind(C, name="_wrap_FSUNLinSolResid") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR) :: fresult
end function

function swigc_FSUNLinSolLastFlag(farg1) &
bind(C, name="_wrap_FSUNLinSolLastFlag") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT64_T) :: fresult
end function

function swigc_FSUNLinSolSpace(farg1, farg2, farg3) &
bind(C, name="_wrap_FSUNLinSolSpace") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
type(C_PTR), value :: farg2
type(C_PTR), value :: farg3
integer(C_INT) :: fresult
end function

function swigc_FSUNLinSolFree(farg1) &
bind(C, name="_wrap_FSUNLinSolFree") &
result(fresult)
use, intrinsic :: ISO_C_BINDING
type(C_PTR), value :: farg1
integer(C_INT) :: fresult
end function

end interface


contains
 ! MODULE SUBPROGRAMS
function FSUNModifiedGS(v, h, k, p, new_vk_norm) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: v
type(C_PTR), target, intent(inout) :: h
integer(C_INT), intent(in) :: k
integer(C_INT), intent(in) :: p
real(C_DOUBLE), dimension(*), target, intent(inout) :: new_vk_norm
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 
integer(C_INT) :: farg3 
integer(C_INT) :: farg4 
type(C_PTR) :: farg5 

farg1 = v
farg2 = c_loc(h)
farg3 = k
farg4 = p
farg5 = c_loc(new_vk_norm(1))
fresult = swigc_FSUNModifiedGS(farg1, farg2, farg3, farg4, farg5)
swig_result = fresult
end function

function FSUNClassicalGS(v, h, k, p, new_vk_norm, stemp, vtemp) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: v
type(C_PTR), target, intent(inout) :: h
integer(C_INT), intent(in) :: k
integer(C_INT), intent(in) :: p
real(C_DOUBLE), dimension(*), target, intent(inout) :: new_vk_norm
real(C_DOUBLE), dimension(*), target, intent(inout) :: stemp
type(C_PTR) :: vtemp
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 
integer(C_INT) :: farg3 
integer(C_INT) :: farg4 
type(C_PTR) :: farg5 
type(C_PTR) :: farg6 
type(C_PTR) :: farg7 

farg1 = v
farg2 = c_loc(h)
farg3 = k
farg4 = p
farg5 = c_loc(new_vk_norm(1))
farg6 = c_loc(stemp(1))
farg7 = vtemp
fresult = swigc_FSUNClassicalGS(farg1, farg2, farg3, farg4, farg5, farg6, farg7)
swig_result = fresult
end function

function FSUNQRfact(n, h, q, job) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
integer(C_INT), intent(in) :: n
type(C_PTR), target, intent(inout) :: h
real(C_DOUBLE), dimension(*), target, intent(inout) :: q
integer(C_INT), intent(in) :: job
integer(C_INT) :: fresult 
integer(C_INT) :: farg1 
type(C_PTR) :: farg2 
type(C_PTR) :: farg3 
integer(C_INT) :: farg4 

farg1 = n
farg2 = c_loc(h)
farg3 = c_loc(q(1))
farg4 = job
fresult = swigc_FSUNQRfact(farg1, farg2, farg3, farg4)
swig_result = fresult
end function

function FSUNQRsol(n, h, q, b) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
integer(C_INT), intent(in) :: n
type(C_PTR), target, intent(inout) :: h
real(C_DOUBLE), dimension(*), target, intent(inout) :: q
real(C_DOUBLE), dimension(*), target, intent(inout) :: b
integer(C_INT) :: fresult 
integer(C_INT) :: farg1 
type(C_PTR) :: farg2 
type(C_PTR) :: farg3 
type(C_PTR) :: farg4 

farg1 = n
farg2 = c_loc(h)
farg3 = c_loc(q(1))
farg4 = c_loc(b(1))
fresult = swigc_FSUNQRsol(farg1, farg2, farg3, farg4)
swig_result = fresult
end function

function FSUNQRAdd_MGS(q, r, df, m, mmax, qrdata) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: q
real(C_DOUBLE), dimension(*), target, intent(inout) :: r
type(N_Vector), target, intent(inout) :: df
integer(C_INT), intent(in) :: m
integer(C_INT), intent(in) :: mmax
type(C_PTR) :: qrdata
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 
type(C_PTR) :: farg3 
integer(C_INT) :: farg4 
integer(C_INT) :: farg5 
type(C_PTR) :: farg6 

farg1 = q
farg2 = c_loc(r(1))
farg3 = c_loc(df)
farg4 = m
farg5 = mmax
farg6 = qrdata
fresult = swigc_FSUNQRAdd_MGS(farg1, farg2, farg3, farg4, farg5, farg6)
swig_result = fresult
end function

function FSUNQRAdd_ICWY(q, r, df, m, mmax, qrdata) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: q
real(C_DOUBLE), dimension(*), target, intent(inout) :: r
type(N_Vector), target, intent(inout) :: df
integer(C_INT), intent(in) :: m
integer(C_INT), intent(in) :: mmax
type(C_PTR) :: qrdata
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 
type(C_PTR) :: farg3 
integer(C_INT) :: farg4 
integer(C_INT) :: farg5 
type(C_PTR) :: farg6 

farg1 = q
farg2 = c_loc(r(1))
farg3 = c_loc(df)
farg4 = m
farg5 = mmax
farg6 = qrdata
fresult = swigc_FSUNQRAdd_ICWY(farg1, farg2, farg3, farg4, farg5, farg6)
swig_result = fresult
end function

function FSUNQRAdd_ICWY_SB(q, r, df, m, mmax, qrdata) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: q
real(C_DOUBLE), dimension(*), target, intent(inout) :: r
type(N_Vector), target, intent(inout) :: df
integer(C_INT), intent(in) :: m
integer(C_INT), intent(in) :: mmax
type(C_PTR) :: qrdata
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 
type(C_PTR) :: farg3 
integer(C_INT) :: farg4 
integer(C_INT) :: farg5 
type(C_PTR) :: farg6 

farg1 = q
farg2 = c_loc(r(1))
farg3 = c_loc(df)
farg4 = m
farg5 = mmax
farg6 = qrdata
fresult = swigc_FSUNQRAdd_ICWY_SB(farg1, farg2, farg3, farg4, farg5, farg6)
swig_result = fresult
end function

function FSUNQRAdd_CGS2(q, r, df, m, mmax, qrdata) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: q
real(C_DOUBLE), dimension(*), target, intent(inout) :: r
type(N_Vector), target, intent(inout) :: df
integer(C_INT), intent(in) :: m
integer(C_INT), intent(in) :: mmax
type(C_PTR) :: qrdata
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 
type(C_PTR) :: farg3 
integer(C_INT) :: farg4 
integer(C_INT) :: farg5 
type(C_PTR) :: farg6 

farg1 = q
farg2 = c_loc(r(1))
farg3 = c_loc(df)
farg4 = m
farg5 = mmax
farg6 = qrdata
fresult = swigc_FSUNQRAdd_CGS2(farg1, farg2, farg3, farg4, farg5, farg6)
swig_result = fresult
end function

function FSUNQRAdd_DCGS2(q, r, df, m, mmax, qrdata) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: q
real(C_DOUBLE), dimension(*), target, intent(inout) :: r
type(N_Vector), target, intent(inout) :: df
integer(C_INT), intent(in) :: m
integer(C_INT), intent(in) :: mmax
type(C_PTR) :: qrdata
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 
type(C_PTR) :: farg3 
integer(C_INT) :: farg4 
integer(C_INT) :: farg5 
type(C_PTR) :: farg6 

farg1 = q
farg2 = c_loc(r(1))
farg3 = c_loc(df)
farg4 = m
farg5 = mmax
farg6 = qrdata
fresult = swigc_FSUNQRAdd_DCGS2(farg1, farg2, farg3, farg4, farg5, farg6)
swig_result = fresult
end function

function FSUNQRAdd_DCGS2_SB(q, r, df, m, mmax, qrdata) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(C_PTR) :: q
real(C_DOUBLE), dimension(*), target, intent(inout) :: r
type(N_Vector), target, intent(inout) :: df
integer(C_INT), intent(in) :: m
integer(C_INT), intent(in) :: mmax
type(C_PTR) :: qrdata
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 
type(C_PTR) :: farg2 
type(C_PTR) :: farg3 
integer(C_INT) :: farg4 
integer(C_INT) :: farg5 
type(C_PTR) :: farg6 

farg1 = q
farg2 = c_loc(r(1))
farg3 = c_loc(df)
farg4 = m
farg5 = mmax
farg6 = qrdata
fresult = swigc_FSUNQRAdd_DCGS2_SB(farg1, farg2, farg3, farg4, farg5, farg6)
swig_result = fresult
end function

function FSUNLinSolNewEmpty(sunctx) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(SUNLinearSolver), pointer :: swig_result
type(C_PTR) :: sunctx
type(C_PTR) :: fresult 
type(C_PTR) :: farg1 

farg1 = sunctx
fresult = swigc_FSUNLinSolNewEmpty(farg1)
call c_f_pointer(fresult, swig_result)
end function

subroutine FSUNLinSolFreeEmpty(s)
use, intrinsic :: ISO_C_BINDING
type(SUNLinearSolver), target, intent(inout) :: s
type(C_PTR) :: farg1 

farg1 = c_loc(s)
call swigc_FSUNLinSolFreeEmpty(farg1)
end subroutine

function FSUNLinSolGetType(s) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(SUNLinearSolver_Type) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(s)
fresult = swigc_FSUNLinSolGetType(farg1)
swig_result = fresult
end function

function FSUNLinSolGetID(s) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(SUNLinearSolver_ID) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(s)
fresult = swigc_FSUNLinSolGetID(farg1)
swig_result = fresult
end function

function FSUNLinSolSetATimes(s, a_data, atimes) &
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
fresult = swigc_FSUNLinSolSetATimes(farg1, farg2, farg3)
swig_result = fresult
end function

function FSUNLinSolSetPreconditioner(s, p_data, pset, psol) &
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
fresult = swigc_FSUNLinSolSetPreconditioner(farg1, farg2, farg3, farg4)
swig_result = fresult
end function

function FSUNLinSolSetScalingVectors(s, s1, s2) &
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
fresult = swigc_FSUNLinSolSetScalingVectors(farg1, farg2, farg3)
swig_result = fresult
end function

function FSUNLinSolSetZeroGuess(s, onoff) &
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
fresult = swigc_FSUNLinSolSetZeroGuess(farg1, farg2)
swig_result = fresult
end function

function FSUNLinSolInitialize(s) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(s)
fresult = swigc_FSUNLinSolInitialize(farg1)
swig_result = fresult
end function

function FSUNLinSolSetup(s, a) &
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
fresult = swigc_FSUNLinSolSetup(farg1, farg2)
swig_result = fresult
end function

function FSUNLinSolSolve(s, a, x, b, tol) &
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
fresult = swigc_FSUNLinSolSolve(farg1, farg2, farg3, farg4, farg5)
swig_result = fresult
end function

function FSUNLinSolNumIters(s) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(s)
fresult = swigc_FSUNLinSolNumIters(farg1)
swig_result = fresult
end function

function FSUNLinSolResNorm(s) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
real(C_DOUBLE) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
real(C_DOUBLE) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(s)
fresult = swigc_FSUNLinSolResNorm(farg1)
swig_result = fresult
end function

function FSUNLinSolResid(s) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
type(N_Vector), pointer :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
type(C_PTR) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(s)
fresult = swigc_FSUNLinSolResid(farg1)
call c_f_pointer(fresult, swig_result)
end function

function FSUNLinSolLastFlag(s) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT64_T) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
integer(C_INT64_T) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(s)
fresult = swigc_FSUNLinSolLastFlag(farg1)
swig_result = fresult
end function

function FSUNLinSolSpace(s, lenrwls, leniwls) &
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
fresult = swigc_FSUNLinSolSpace(farg1, farg2, farg3)
swig_result = fresult
end function

function FSUNLinSolFree(s) &
result(swig_result)
use, intrinsic :: ISO_C_BINDING
integer(C_INT) :: swig_result
type(SUNLinearSolver), target, intent(inout) :: s
integer(C_INT) :: fresult 
type(C_PTR) :: farg1 

farg1 = c_loc(s)
fresult = swigc_FSUNLinSolFree(farg1)
swig_result = fresult
end function


end module
