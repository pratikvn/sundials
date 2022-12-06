/* -----------------------------------------------------------------
 * SUNDIALS Copyright Start
 * Copyright (c) 2002-2022, Lawrence Livermore National Security
 * and Southern Methodist University.
 * All rights reserved.
 *
 * See the top-level LICENSE and NOTICE files for details.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * SUNDIALS Copyright End
 * -----------------------------------------------------------------
 * Implementation header for N_Vector class.
 * -----------------------------------------------------------------*/

#define NVECTOR_DEFINE_ENABLE_FUSEDOP(fname, opname, suffix) \
  SUNErrCode N_VEnable ## fname ## suffix(N_Vector v, booleantype tf) \
  { \
    if (tf) \
      v->ops->nv ## opname = N_V ## fname ## _ ## suffix; \
    else \
      v->ops->nv ## opname = NULL; \
    \
    return SUN_SUCCESS; \
  }
