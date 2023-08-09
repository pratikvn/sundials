/* -----------------------------------------------------------------
 * Programmer(s): Jean M. Sexton @ SMU
 *                Slaven Peles @ LLNL
 * -----------------------------------------------------------------
 * Based on work by: Scott D. Cohen, Alan C. Hindmarsh, Radu Serban,
 *                   and Aaron Collier @ LLNL
 * -----------------------------------------------------------------
 * SUNDIALS Copyright Start
 * Copyright (c) 2002-2023, Lawrence Livermore National Security
 * and Southern Methodist University.
 * All rights reserved.
 *
 * See the top-level LICENSE and NOTICE files for details.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * SUNDIALS Copyright End
 * -----------------------------------------------------------------
 * This is the main header file for the ParHyp implementation
 * of the NVECTOR module.
 *
 * Notes:
 *
 *   - The definition of the generic N_Vector structure can be
 *     found in the header file sundials_nvector.h.
 *
 *   - The definition of the type realtype can be found in the
 *     header file sundials_types.h, and it may be changed (at the
 *     configuration stage) according to the user's needs.
 *     The sundials_types.h file also contains the definition
 *     for the type booleantype.
 *
 *   - N_Vector arguments to arithmetic vector operations need not
 *     be distinct. For example, the following call:
 *
 *        N_VLinearSum_ParHyp(a,x,b,y,y);
 *
 *     (which stores the result of the operation a*x+b*y in y)
 *     is legal.
 * -----------------------------------------------------------------*/

#ifndef _NVECTOR_PARHYP_H
#define _NVECTOR_PARHYP_H

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

/* --- SUNDIALS and hypre headers --- */

#include <sundials/sundials_math.h>
#include <sundials/sundials_config.h>
#include <sundials/sundials_nvector.h>
#include <sundials/sundials_mpi_types.h>

#include <_hypre_parcsr_mv.h>

/* --- Backend-specific headers --- */

#if defined(SUNDIALS_HYPRE_BACKENDS_SERIAL)
#pragma message "hypre backend SERIAL confirmed from nvector_parhyp.h"

#elif defined(SUNDIALS_HYPRE_BACKENDS_CUDA)
#pragma message "hypre backend CUDA confirmed from nvector_parhyp.h"
#include <cuda_runtime.h>
#include <sundials/sundials_cuda_policies.hpp>
#include <sunmemory/sunmemory_cuda.h>
#include "sundials_cuda.h"            /* located in src/nvector/sundials */

#elif defined(SUNDIALS_HYPRE_BACKENDS_HIP)
#pragma message "hypre backend HIP confirmed from nvector_parhyp.h"
#include <hip/hip_runtime.h>
#include <sundials/sundials_hip_policies.hpp>
#include <sunmemory/sunmemory_hip.h>
#include "sundials_hip.h"             /* located in src/nvector/sundials */
#endif

/* --- Backend-specific definitions --- */

#if defined(SUNDIALS_HYPRE_BACKENDS_SERIAL)
#define NV_BACKEND_STRING_PH "SERIAL"

#elif defined(SUNDIALS_HYPRE_BACKENDS_CUDA)
#define NV_BACKEND_STRING_PH "CUDA"
#define NV_GPU_LANG_TOKEN_PH cuda
#define NV_ADD_LANG_PREFIX_PH(token) cuda##token // token pasting; expands to ```cuda[token]```
#define NV_EXECPOLICY_TYPE_PH SUNCudaExecPolicy
#define NV_MEMHELP_STRUCT_PH SUNMemoryHelper_Cuda
#define NV_VERIFY_CALL_PH SUNDIALS_CUDA_VERIFY

#elif defined(SUNDIALS_HYPRE_BACKENDS_HIP)
#define NV_BACKEND_STRING_PH "HIP"
#define NV_GPU_LANG_TOKEN_PH hip
#define NV_ADD_LANG_PREFIX_PH(token) hip##token // token pasting; expands to ```hip[token]```
#define NV_EXECPOLICY_TYPE_PH SUNHipExecPolicy
#define NV_MEMHELP_STRUCT_PH SUNMemoryHelper_Hip
#define NV_VERIFY_CALL_PH SUNDIALS_HIP_VERIFY
#endif

#if defined(SUNDIALS_HYPRE_BACKENDS_CUDA) || defined(SUNDIALS_HYPRE_BACKENDS_HIP)
#define SUNDIALS_HYPRE_BACKENDS_CUDA_OR_HIP
#endif

#if defined(SUNDIALS_HYPRE_USING_UNIFIED_MEMORY) && defined(SUNDIALS_HYPRE_BACKENDS_CUDA)
#define SUNDIALS_HYPRE_UNIFIED_MEMORY_AND_CUDA
#endif

/* --- Wrapper to enable C++ usage --- */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * -----------------------------------------------------------------
 * ParHyp implementation of N_Vector
 * -----------------------------------------------------------------
 */

struct _N_VectorContent_ParHyp
{
  sunindextype    local_length;  /* local vector length               */
  sunindextype    global_length; /* global vector length              */
  booleantype     own_parvector; /* ownership of HYPRE vector         */
  MPI_Comm        comm;          /* pointer to MPI communicator       */
  HYPRE_ParVector x;             /* the actual HYPRE_ParVector object */
#if defined(SUNDIALS_HYPRE_BACKENDS_CUDA_OR_HIP)
  NV_EXECPOLICY_TYPE_PH* stream_exec_policy;
  NV_EXECPOLICY_TYPE_PH* reduce_exec_policy;
  SUNMemoryHelper        mem_helper;
  void*                  priv;   /* private buffers, counters, etc.   */
#endif
};

typedef struct _N_VectorContent_ParHyp *N_VectorContent_ParHyp;

/*
 * -----------------------------------------------------------------
 * Functions exported by nvector_parhyp
 * -----------------------------------------------------------------
 */

SUNDIALS_EXPORT N_Vector N_VNewEmpty_ParHyp(MPI_Comm comm,
                                            sunindextype local_length,
                                            sunindextype global_length,
                                            SUNContext sunctx);

SUNDIALS_EXPORT N_Vector N_VMake_ParHyp(HYPRE_ParVector x, SUNContext sunctx);

SUNDIALS_EXPORT HYPRE_ParVector N_VGetVector_ParHyp(N_Vector v);

SUNDIALS_EXPORT void N_VPrint_ParHyp(N_Vector v);

SUNDIALS_EXPORT void N_VPrintFile_ParHyp(N_Vector v, FILE *outfile);

SUNDIALS_EXPORT N_Vector_ID N_VGetVectorID_ParHyp(N_Vector v);
SUNDIALS_EXPORT N_Vector N_VCloneEmpty_ParHyp(N_Vector w);
SUNDIALS_EXPORT N_Vector N_VClone_ParHyp(N_Vector w);
SUNDIALS_EXPORT void N_VDestroy_ParHyp(N_Vector v);
SUNDIALS_EXPORT void N_VSpace_ParHyp(N_Vector v, sunindextype *lrw,
                                     sunindextype *liw);
SUNDIALS_EXPORT realtype *N_VGetArrayPointer_ParHyp(N_Vector v);
SUNDIALS_EXPORT void N_VSetArrayPointer_ParHyp(realtype *v_data, N_Vector v);
SUNDIALS_EXPORT void *N_VGetCommunicator_ParHyp(N_Vector v);
SUNDIALS_EXPORT sunindextype N_VGetLength_ParHyp(N_Vector v);

/* --- Backend-specific operations --- */

//TODO: add these in the .c file
// #if defined(SUNDIALS_HYPRE_BACKENDS_CUDA_OR_HIP)
// SUNDIALS_EXPORT booleantype N_VIsManagedMemory_ParHyp(N_Vector x);
// SUNDIALS_EXPORT void N_VCopyToDevice_ParHyp(N_Vector v);
// SUNDIALS_EXPORT void N_VCopyFromDevice_ParHyp(N_Vector v);
// #endif

// #if defined(SUNDIALS_HYPRE_BACKENDS_CUDA)
// SUNDIALS_EXPORT int N_VSetKernelExecPolicy_ParHyp(N_Vector x,
//                                                 SUNCudaExecPolicy* stream_exec_policy,
//                                                 SUNCudaExecPolicy* reduce_exec_policy);
// #elif defined(SUNDIALS_HYPRE_BACKENDS_HIP)
// SUNDIALS_EXPORT int N_VSetKernelExecPolicy_ParHyp(N_Vector x,
//                                                 SUNHipExecPolicy* stream_exec_policy,
//                                                 SUNHipExecPolicy* reduce_exec_policy);
// #endif

/* --- Standard vector operations --- */

SUNDIALS_EXPORT void N_VLinearSum_ParHyp(realtype a, N_Vector x, realtype b,
                                         N_Vector y, N_Vector z);
SUNDIALS_EXPORT void N_VConst_ParHyp(realtype c, N_Vector z);
SUNDIALS_EXPORT void N_VProd_ParHyp(N_Vector x, N_Vector y, N_Vector z);
SUNDIALS_EXPORT void N_VDiv_ParHyp(N_Vector x, N_Vector y, N_Vector z);
SUNDIALS_EXPORT void N_VScale_ParHyp(realtype c, N_Vector x, N_Vector z);
SUNDIALS_EXPORT void N_VAbs_ParHyp(N_Vector x, N_Vector z);
SUNDIALS_EXPORT void N_VInv_ParHyp(N_Vector x, N_Vector z);
SUNDIALS_EXPORT void N_VAddConst_ParHyp(N_Vector x, realtype b, N_Vector z);
SUNDIALS_EXPORT realtype N_VDotProd_ParHyp(N_Vector x, N_Vector y);
SUNDIALS_EXPORT realtype N_VMaxNorm_ParHyp(N_Vector x);
SUNDIALS_EXPORT realtype N_VWrmsNorm_ParHyp(N_Vector x, N_Vector w);
SUNDIALS_EXPORT realtype N_VWrmsNormMask_ParHyp(N_Vector x, N_Vector w,
                                                N_Vector id);
SUNDIALS_EXPORT realtype N_VMin_ParHyp(N_Vector x);
SUNDIALS_EXPORT realtype N_VWL2Norm_ParHyp(N_Vector x, N_Vector w);
SUNDIALS_EXPORT realtype N_VL1Norm_ParHyp(N_Vector x);
SUNDIALS_EXPORT void N_VCompare_ParHyp(realtype c, N_Vector x, N_Vector z);
SUNDIALS_EXPORT booleantype N_VInvTest_ParHyp(N_Vector x, N_Vector z);
SUNDIALS_EXPORT booleantype N_VConstrMask_ParHyp(N_Vector c, N_Vector x,
                                                 N_Vector m);
SUNDIALS_EXPORT realtype N_VMinQuotient_ParHyp(N_Vector num, N_Vector denom);

/* --- Fused vector operations --- */

SUNDIALS_EXPORT int N_VLinearCombination_ParHyp(int nvec, realtype* c,
                                                N_Vector* X, N_Vector z);
SUNDIALS_EXPORT int N_VScaleAddMulti_ParHyp(int nvec, realtype* a, N_Vector x,
                                            N_Vector* Y, N_Vector* Z);
SUNDIALS_EXPORT int N_VDotProdMulti_ParHyp(int nvec, N_Vector x, N_Vector* Y,
                                           realtype* dotprods);

/* --- Vector array operations --- */

SUNDIALS_EXPORT int N_VLinearSumVectorArray_ParHyp(int nvec,
                                                   realtype a, N_Vector* X,
                                                   realtype b, N_Vector* Y,
                                                   N_Vector* Z);
SUNDIALS_EXPORT int N_VScaleVectorArray_ParHyp(int nvec, realtype* c,
                                               N_Vector* X, N_Vector* Z);
SUNDIALS_EXPORT int N_VConstVectorArray_ParHyp(int nvecs, realtype c,
                                               N_Vector* Z);
SUNDIALS_EXPORT int N_VWrmsNormVectorArray_ParHyp(int nvecs, N_Vector* X,
                                                  N_Vector* W, realtype* nrm);
SUNDIALS_EXPORT int N_VWrmsNormMaskVectorArray_ParHyp(int nvec, N_Vector* X,
                                                      N_Vector* W, N_Vector id,
                                                      realtype* nrm);
SUNDIALS_EXPORT int N_VScaleAddMultiVectorArray_ParHyp(int nvec, int nsum,
                                                       realtype* a,
                                                       N_Vector* X,
                                                       N_Vector** Y,
                                                       N_Vector** Z);
SUNDIALS_EXPORT int N_VLinearCombinationVectorArray_ParHyp(int nvec, int nsum,
                                                           realtype* c,
                                                           N_Vector** X,
                                                           N_Vector* Z);

/* --- OPTIONAL local reduction kernels (no parallel communication) --- */

SUNDIALS_EXPORT realtype N_VDotProdLocal_ParHyp(N_Vector x, N_Vector y);
SUNDIALS_EXPORT realtype N_VMaxNormLocal_ParHyp(N_Vector x);
SUNDIALS_EXPORT realtype N_VMinLocal_ParHyp(N_Vector x);
SUNDIALS_EXPORT realtype N_VL1NormLocal_ParHyp(N_Vector x);
SUNDIALS_EXPORT realtype N_VWSqrSumLocal_ParHyp(N_Vector x, N_Vector w);
SUNDIALS_EXPORT realtype N_VWSqrSumMaskLocal_ParHyp(N_Vector x, N_Vector w,
                                                    N_Vector id);
SUNDIALS_EXPORT booleantype N_VInvTestLocal_ParHyp(N_Vector x, N_Vector z);
SUNDIALS_EXPORT booleantype N_VConstrMaskLocal_ParHyp(N_Vector c, N_Vector x,
                                                      N_Vector m);
SUNDIALS_EXPORT realtype N_VMinQuotientLocal_ParHyp(N_Vector num,
                                                    N_Vector denom);

/* --- OPTIONAL single buffer reduction operations --- */

SUNDIALS_EXPORT int N_VDotProdMultiLocal_ParHyp(int nvec, N_Vector x,
                                                N_Vector* Y,
                                                realtype* dotprods);
SUNDIALS_EXPORT int N_VDotProdMultiAllReduce_ParHyp(int nvec, N_Vector x,
                                                    realtype* sum);

/* --- OPTIONAL XBraid interface operations --- */

SUNDIALS_EXPORT int N_VBufSize_ParHyp(N_Vector x, sunindextype *size);
SUNDIALS_EXPORT int N_VBufPack_ParHyp(N_Vector x, void *buf);
SUNDIALS_EXPORT int N_VBufUnpack_ParHyp(N_Vector x, void *buf);

/*
 * -----------------------------------------------------------------
 * Enable / disable fused vector operations
 * -----------------------------------------------------------------
 */

SUNDIALS_EXPORT int N_VEnableFusedOps_ParHyp(N_Vector v, booleantype tf);

SUNDIALS_EXPORT int N_VEnableLinearCombination_ParHyp(N_Vector v,
                                                      booleantype tf);
SUNDIALS_EXPORT int N_VEnableScaleAddMulti_ParHyp(N_Vector v, booleantype tf);
SUNDIALS_EXPORT int N_VEnableDotProdMulti_ParHyp(N_Vector v, booleantype tf);

SUNDIALS_EXPORT int N_VEnableLinearSumVectorArray_ParHyp(N_Vector v,
                                                         booleantype tf);
SUNDIALS_EXPORT int N_VEnableScaleVectorArray_ParHyp(N_Vector v,
                                                     booleantype tf);
SUNDIALS_EXPORT int N_VEnableConstVectorArray_ParHyp(N_Vector v,
                                                     booleantype tf);
SUNDIALS_EXPORT int N_VEnableWrmsNormVectorArray_ParHyp(N_Vector v,
                                                        booleantype tf);
SUNDIALS_EXPORT int N_VEnableWrmsNormMaskVectorArray_ParHyp(N_Vector v,
                                                            booleantype tf);
SUNDIALS_EXPORT int N_VEnableScaleAddMultiVectorArray_ParHyp(N_Vector v,
                                                             booleantype tf);
SUNDIALS_EXPORT int N_VEnableLinearCombinationVectorArray_ParHyp(N_Vector v,
                                                                 booleantype tf);

/*
 * -----------------------------------------------------------------
 * Deprecated functions
 * -----------------------------------------------------------------
 */

/* use N_VCloneVectorArray */
SUNDIALS_DEPRECATED_EXPORT N_Vector *N_VCloneVectorArray_ParHyp(int count,
                                                                N_Vector w);

/* use N_VCloneVectorArrayEmpty */
SUNDIALS_DEPRECATED_EXPORT N_Vector *N_VCloneVectorArrayEmpty_ParHyp(int count,
                                                                     N_Vector w);

/* use N_VDestroyVectorArray */
SUNDIALS_DEPRECATED_EXPORT void N_VDestroyVectorArray_ParHyp(N_Vector *vs,
                                                             int count);

SUNDIALS_EXPORT int N_VEnableDotProdMultiLocal_ParHyp(N_Vector v, booleantype tf);

#ifdef __cplusplus
}
#endif

#endif
