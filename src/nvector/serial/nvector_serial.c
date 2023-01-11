/* -----------------------------------------------------------------
 * Programmer(s): Scott D. Cohen, Alan C. Hindmarsh, Radu Serban,
 *                and Aaron Collier @ LLNL
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
 * This is the implementation file for a serial implementation
 * of the NVECTOR package.
 * -----------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#include <sundials/sundials.h>
#include <nvector/nvector_serial.h>
#include "sundials/sundials_errors.h"
#include "sundials_nvector_impl.h"

#define ZERO   RCONST(0.0)
#define HALF   RCONST(0.5)
#define ONE    RCONST(1.0)
#define ONEPT5 RCONST(1.5)

/* Private functions for special cases of vector operations */
static void VCopy_Serial(N_Vector x, N_Vector z);                              /* z=x       */
static void VSum_Serial(N_Vector x, N_Vector y, N_Vector z);                   /* z=x+y     */
static void VDiff_Serial(N_Vector x, N_Vector y, N_Vector z);                  /* z=x-y     */
static void VNeg_Serial(N_Vector x, N_Vector z);                               /* z=-x      */
static void VScaleSum_Serial(realtype c, N_Vector x, N_Vector y, N_Vector z);  /* z=c(x+y)  */
static void VScaleDiff_Serial(realtype c, N_Vector x, N_Vector y, N_Vector z); /* z=c(x-y)  */
static void VLin1_Serial(realtype a, N_Vector x, N_Vector y, N_Vector z);      /* z=ax+y    */
static void VLin2_Serial(realtype a, N_Vector x, N_Vector y, N_Vector z);      /* z=ax-y    */
static void Vaxpy_Serial(realtype a, N_Vector x, N_Vector y);                  /* y <- ax+y */
static void VScaleBy_Serial(realtype a, N_Vector x);                           /* x <- ax   */

/* Private functions for special cases of vector array operations */
static void VSumVectorArray_Serial(int nvec, N_Vector* X, N_Vector* Y, N_Vector* Z);                   /* Z=X+Y     */
static void VDiffVectorArray_Serial(int nvec, N_Vector* X, N_Vector* Y, N_Vector* Z);                  /* Z=X-Y     */
static void VScaleSumVectorArray_Serial(int nvec, realtype c, N_Vector* X, N_Vector* Y, N_Vector* Z);  /* Z=c(X+Y)  */
static void VScaleDiffVectorArray_Serial(int nvec, realtype c, N_Vector* X, N_Vector* Y, N_Vector* Z); /* Z=c(X-Y)  */
static void VLin1VectorArray_Serial(int nvec, realtype a, N_Vector* X, N_Vector* Y, N_Vector* Z);      /* Z=aX+Y    */
static void VLin2VectorArray_Serial(int nvec, realtype a, N_Vector* X, N_Vector* Y, N_Vector* Z);      /* Z=aX-Y    */
static void VaxpyVectorArray_Serial(int nvec, realtype a, N_Vector* X, N_Vector* Y);                   /* Y <- aX+Y */

/*
 * -----------------------------------------------------------------
 * exported functions
 * -----------------------------------------------------------------
 */

/* ----------------------------------------------------------------------------
 * Function to create a new empty serial vector
 */

N_Vector N_VNewEmpty_Serial(sunindextype length, SUNContext sunctx)
{
  SUNDeclareContext(sunctx);
  N_Vector v;
  N_VectorContent_Serial content;

  SUNAssertContext(SUNCTX);
  SUNAssert(length > 0, SUN_ERR_ARG_OUTOFRANGE, SUNCTX);

  /* Create an empty vector object */
  v = NULL;
  v = SUNCheckCallLastErrNull(N_VNewEmpty(sunctx), SUNCTX);

  /* Attach operations */

  /* constructors, destructors, and utility operations */
  v->ops->nvgetvectorid     = N_VGetVectorID_Serial;
  v->ops->nvclone           = N_VClone_Serial;
  v->ops->nvcloneempty      = N_VCloneEmpty_Serial;
  v->ops->nvdestroy         = N_VDestroy_Serial;
  v->ops->nvspace           = N_VSpace_Serial;
  v->ops->nvgetarraypointer = N_VGetArrayPointer_Serial;
  v->ops->nvsetarraypointer = N_VSetArrayPointer_Serial;
  v->ops->nvgetlength       = N_VGetLength_Serial;
  v->ops->nvgetlocallength  = N_VGetLength_Serial;

  /* standard vector operations */
  v->ops->nvlinearsum    = N_VLinearSum_Serial;
  v->ops->nvconst        = N_VConst_Serial;
  v->ops->nvprod         = N_VProd_Serial;
  v->ops->nvdiv          = N_VDiv_Serial;
  v->ops->nvscale        = N_VScale_Serial;
  v->ops->nvabs          = N_VAbs_Serial;
  v->ops->nvinv          = N_VInv_Serial;
  v->ops->nvaddconst     = N_VAddConst_Serial;
  v->ops->nvdotprod      = N_VDotProd_Serial;
  v->ops->nvmaxnorm      = N_VMaxNorm_Serial;
  v->ops->nvwrmsnormmask = N_VWrmsNormMask_Serial;
  v->ops->nvwrmsnorm     = N_VWrmsNorm_Serial;
  v->ops->nvmin          = N_VMin_Serial;
  v->ops->nvwl2norm      = N_VWL2Norm_Serial;
  v->ops->nvl1norm       = N_VL1Norm_Serial;
  v->ops->nvcompare      = N_VCompare_Serial;
  v->ops->nvinvtest      = N_VInvTest_Serial;
  v->ops->nvconstrmask   = N_VConstrMask_Serial;
  v->ops->nvminquotient  = N_VMinQuotient_Serial;

  /* fused and vector array operations are disabled (NULL) by default */

  /* local reduction operations */
  v->ops->nvdotprodlocal     = N_VDotProd_Serial;
  v->ops->nvmaxnormlocal     = N_VMaxNorm_Serial;
  v->ops->nvminlocal         = N_VMin_Serial;
  v->ops->nvl1normlocal      = N_VL1Norm_Serial;
  v->ops->nvinvtestlocal     = N_VInvTest_Serial;
  v->ops->nvconstrmasklocal  = N_VConstrMask_Serial;
  v->ops->nvminquotientlocal = N_VMinQuotient_Serial;
  v->ops->nvwsqrsumlocal     = N_VWSqrSumLocal_Serial;
  v->ops->nvwsqrsummasklocal = N_VWSqrSumMaskLocal_Serial;

  /* single buffer reduction operations */
  v->ops->nvdotprodmultilocal = N_VDotProdMulti_Serial;

  /* XBraid interface operations */
  v->ops->nvbufsize   = N_VBufSize_Serial;
  v->ops->nvbufpack   = N_VBufPack_Serial;
  v->ops->nvbufunpack = N_VBufUnpack_Serial;

  /* debugging functions */
  v->ops->nvprint     = N_VPrint_Serial;
  v->ops->nvprintfile = N_VPrintFile_Serial;

  /* Create content */
  content = NULL;
  content = (N_VectorContent_Serial) malloc(sizeof *content);
  SUNAssert(content, SUN_ERR_MALLOC_FAIL, sunctx);

  /* Attach content */
  v->content = content;

  /* Initialize content */
  content->length   = length;
  content->own_data = SUNFALSE;
  content->data     = NULL;

  return(v);
}

/* ----------------------------------------------------------------------------
 * Function to create a new serial vector
 */

N_Vector N_VNew_Serial(sunindextype length, SUNContext sunctx)
{
  SUNDeclareContext(sunctx);
  N_Vector v;
  realtype *data;

  SUNAssertContext(SUNCTX);
  SUNAssert(length > 0, SUN_ERR_ARG_OUTOFRANGE, SUNCTX);

  v = NULL;
  v = SUNCheckCallLastErrNull(N_VNewEmpty_Serial(length, sunctx), SUNCTX);

  /* Create data */
  data = NULL;
  data = (realtype *) malloc(length * sizeof(realtype));
  SUNAssert(data, SUN_ERR_MALLOC_FAIL, SUNCTX);

  /* Attach data */
  NV_OWN_DATA_S(v) = SUNTRUE;
  NV_DATA_S(v)     = data;

  return(v);
}

/* ----------------------------------------------------------------------------
 * Function to create a serial N_Vector with user data component
 */

N_Vector N_VMake_Serial(sunindextype length, realtype *v_data, SUNContext sunctx)
{
  SUNDeclareContext(sunctx);
  N_Vector v;

  SUNAssertContext(SUNCTX);
  SUNAssert(length > 0, SUN_ERR_ARG_OUTOFRANGE, SUNCTX);

  v = NULL;
  v = SUNCheckCallLastErrNull(N_VNewEmpty_Serial(length, sunctx), SUNCTX);

  /* Attach data */
  NV_OWN_DATA_S(v) = SUNFALSE;
  NV_DATA_S(v)     = v_data;

  return(v);
}

/* ----------------------------------------------------------------------------
 * Function to create an array of new serial vectors.
 */

N_Vector* N_VCloneVectorArray_Serial(int count, N_Vector w)
{
  SUNDeclareContext(w->sunctx);
  N_Vector* result = SUNCheckCallLastErrNull(N_VCloneVectorArray(count, w), SUNCTX);
  return result;
}

/* ----------------------------------------------------------------------------
 * Function to create an array of new serial vectors with NULL data array.
 */

N_Vector* N_VCloneVectorArrayEmpty_Serial(int count, N_Vector w)
{
  SUNDeclareContext(w->sunctx);
  N_Vector* result = SUNCheckCallLastErrNull(N_VCloneEmptyVectorArray(count, w), SUNCTX);
  return result;
}

/* ----------------------------------------------------------------------------
 * Function to free an array created with N_VCloneVectorArray_Serial
 */

void N_VDestroyVectorArray_Serial(N_Vector* vs, int count)
{
  SUNDeclareContext(vs[0]->sunctx);
  SUNCheckCallLastErrNoRet(N_VDestroyVectorArray(vs, count), SUNCTX);
  return;
}

/* ----------------------------------------------------------------
 * Returns vector type ID. Used to identify vector implementation
 * from abstract N_Vector interface.
 */
N_Vector_ID N_VGetVectorID_Serial(N_Vector v)
{
  return SUNDIALS_NVEC_SERIAL;
}

/* ----------------------------------------------------------------------------
 * Function to return number of vector elements
 */
sunindextype N_VGetLength_Serial(N_Vector v)
{
  return NV_LENGTH_S(v);
}

/* ----------------------------------------------------------------------------
 * Function to print the a serial vector to stdout
 */

void N_VPrint_Serial(N_Vector x)
{
  SUNDeclareContext(x->sunctx);
  SUNCheckCallLastErrNoRet(N_VPrintFile_Serial(x, stdout), SUNCTX);
}

/* ----------------------------------------------------------------------------
 * Function to print the a serial vector to outfile
 */

void N_VPrintFile_Serial(N_Vector x, FILE* outfile)
{
  sunindextype i, N;
  realtype *xd;

  xd = NULL;

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);

  for (i = 0; i < N; i++) {
#if defined(SUNDIALS_EXTENDED_PRECISION)
    fprintf(outfile, "%35.32Le\n", xd[i]);
#elif defined(SUNDIALS_DOUBLE_PRECISION)
    fprintf(outfile, "%19.16e\n", xd[i]);
#else
    fprintf(outfile, "%11.8e\n", xd[i]);
#endif
  }
  fprintf(outfile, "\n");

  return;
}

/*
 * -----------------------------------------------------------------
 * implementation of vector operations
 * -----------------------------------------------------------------
 */

N_Vector N_VCloneEmpty_Serial(N_Vector w)
{
  SUNDeclareContext(w->sunctx);
  N_Vector v;
  N_VectorContent_Serial content;

  /* Create vector */
  v = NULL;
  v = SUNCheckCallLastErrNull(N_VNewEmpty(w->sunctx), SUNCTX);

  /* Attach operations */
  SUNCheckCallNull(N_VCopyOps(w, v), SUNCTX);

  /* Create content */
  content = NULL;
  content = (N_VectorContent_Serial) malloc(sizeof *content);
  SUNAssert(content, SUN_ERR_MALLOC_FAIL, SUNCTX);

  /* Attach content */
  v->content = content;

  /* Initialize content */
  content->length   = NV_LENGTH_S(w);
  content->own_data = SUNFALSE;
  content->data     = NULL;

  return(v);
}

N_Vector N_VClone_Serial(N_Vector w)
{
  SUNDeclareContext(w->sunctx);
  N_Vector v;
  realtype *data;
  sunindextype length;

  v = NULL;
  v = SUNCheckCallLastErrNull(N_VCloneEmpty_Serial(w), w->sunctx);

  length = NV_LENGTH_S(w);

  /* Create data */
  data = NULL;
  data = (realtype *) malloc(length * sizeof(realtype));
  SUNAssert(data, SUN_ERR_MALLOC_FAIL, SUNCTX);

  /* Attach data */
  NV_OWN_DATA_S(v) = SUNTRUE;
  NV_DATA_S(v)     = data;

  return(v);
}

void N_VDestroy_Serial(N_Vector v)
{
  if (v == NULL) return;

  /* free content */
  if (v->content != NULL) {
    /* free data array if it's owned by the vector */
    if (NV_OWN_DATA_S(v) && NV_DATA_S(v) != NULL) {
      free(NV_DATA_S(v));
      NV_DATA_S(v) = NULL;
    }
    free(v->content);
    v->content = NULL;
  }

  /* free ops and vector */
  if (v->ops != NULL) { free(v->ops); v->ops = NULL; }
  free(v); v = NULL;

  return;
}

void N_VSpace_Serial(N_Vector v, sunindextype *lrw, sunindextype *liw)
{
  *lrw = NV_LENGTH_S(v);
  *liw = 1;

  return;
}

realtype *N_VGetArrayPointer_Serial(N_Vector v)
{
  return((realtype *) NV_DATA_S(v));
}

void N_VSetArrayPointer_Serial(realtype *v_data, N_Vector v)
{
  if (NV_LENGTH_S(v) > 0) NV_DATA_S(v) = v_data;

  return;
}

void N_VLinearSum_Serial(realtype a, N_Vector x, realtype b, N_Vector y, N_Vector z)
{
  sunindextype i, N;
  realtype c, *xd, *yd, *zd;
  N_Vector v1, v2;
  booleantype test;

  xd = yd = zd = NULL;

  if ((b == ONE) && (z == y)) {    /* BLAS usage: axpy y <- ax+y */
    Vaxpy_Serial(a,x,y);
    return;
  }

  if ((a == ONE) && (z == x)) {    /* BLAS usage: axpy x <- by+x */
    Vaxpy_Serial(b,y,x);
    return;
  }

  /* Case: a == b == 1.0 */

  if ((a == ONE) && (b == ONE)) {
    VSum_Serial(x, y, z);
    return;
  }

  /* Cases: (1) a == 1.0, b = -1.0, (2) a == -1.0, b == 1.0 */

  if ((test = ((a == ONE) && (b == -ONE))) || ((a == -ONE) && (b == ONE))) {
    v1 = test ? y : x;
    v2 = test ? x : y;
    VDiff_Serial(v2, v1, z);
    return;
  }

  /* Cases: (1) a == 1.0, b == other or 0.0, (2) a == other or 0.0, b == 1.0 */
  /* if a or b is 0.0, then user should have called N_VScale */

  if ((test = (a == ONE)) || (b == ONE)) {
    c  = test ? b : a;
    v1 = test ? y : x;
    v2 = test ? x : y;
    VLin1_Serial(c, v1, v2, z);
    return;
  }

  /* Cases: (1) a == -1.0, b != 1.0, (2) a != 1.0, b == -1.0 */

  if ((test = (a == -ONE)) || (b == -ONE)) {
    c = test ? b : a;
    v1 = test ? y : x;
    v2 = test ? x : y;
    VLin2_Serial(c, v1, v2, z);
    return;
  }

  /* Case: a == b */
  /* catches case both a and b are 0.0 - user should have called N_VConst */

  if (a == b) {
    VScaleSum_Serial(a, x, y, z);
    return;
  }

  /* Case: a == -b */

  if (a == -b) {
    VScaleDiff_Serial(a, x, y, z);
    return;
  }

  /* Do all cases not handled above:
     (1) a == other, b == 0.0 - user should have called N_VScale
     (2) a == 0.0, b == other - user should have called N_VScale
     (3) a,b == other, a !=b, a != -b */

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);
  yd = NV_DATA_S(y);
  zd = NV_DATA_S(z);

  for (i = 0; i < N; i++)
    zd[i] = (a*xd[i])+(b*yd[i]);

  return;
}

void N_VConst_Serial(realtype c, N_Vector z)
{
  sunindextype i, N;
  realtype *zd;

  zd = NULL;

  N  = NV_LENGTH_S(z);
  zd = NV_DATA_S(z);

  for (i = 0; i < N; i++) zd[i] = c;

  return;
}

void N_VProd_Serial(N_Vector x, N_Vector y, N_Vector z)
{
  sunindextype i, N;
  realtype *xd, *yd, *zd;

  xd = yd = zd = NULL;

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);
  yd = NV_DATA_S(y);
  zd = NV_DATA_S(z);

  for (i = 0; i < N; i++)
    zd[i] = xd[i]*yd[i];

  return;
}

void N_VDiv_Serial(N_Vector x, N_Vector y, N_Vector z)
{
  sunindextype i, N;
  realtype *xd, *yd, *zd;

  xd = yd = zd = NULL;

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);
  yd = NV_DATA_S(y);
  zd = NV_DATA_S(z);

  for (i = 0; i < N; i++)
    zd[i] = xd[i]/yd[i];

  return;
}

void N_VScale_Serial(realtype c, N_Vector x, N_Vector z)
{
  sunindextype i, N;
  realtype *xd, *zd;

  xd = zd = NULL;

  if (z == x) {  /* BLAS usage: scale x <- cx */
    VScaleBy_Serial(c, x);
    return;
  }

  if (c == ONE) {
    VCopy_Serial(x, z);
  } else if (c == -ONE) {
    VNeg_Serial(x, z);
  } else {
    N  = NV_LENGTH_S(x);
    xd = NV_DATA_S(x);
    zd = NV_DATA_S(z);
    for (i = 0; i < N; i++)
      zd[i] = c*xd[i];
  }

  return;
}

void N_VAbs_Serial(N_Vector x, N_Vector z)
{
  sunindextype i, N;
  realtype *xd, *zd;

  xd = zd = NULL;

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);
  zd = NV_DATA_S(z);

  for (i = 0; i < N; i++)
    zd[i] = SUNRabs(xd[i]);

  return;
}

void N_VInv_Serial(N_Vector x, N_Vector z)
{
  sunindextype i, N;
  realtype *xd, *zd;

  xd = zd = NULL;

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);
  zd = NV_DATA_S(z);

  for (i = 0; i < N; i++)
    zd[i] = ONE/xd[i];

  return;
}

void N_VAddConst_Serial(N_Vector x, realtype b, N_Vector z)
{
  sunindextype i, N;
  realtype *xd, *zd;

  xd = zd = NULL;

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);
  zd = NV_DATA_S(z);

  for (i = 0; i < N; i++)
    zd[i] = xd[i]+b;

  return;
}

realtype N_VDotProd_Serial(N_Vector x, N_Vector y)
{
  sunindextype i, N;
  realtype sum, *xd, *yd;

  sum = ZERO;
  xd = yd = NULL;

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);
  yd = NV_DATA_S(y);

  for (i = 0; i < N; i++)
    sum += xd[i]*yd[i];

  return(sum);
}

realtype N_VMaxNorm_Serial(N_Vector x)
{
  sunindextype i, N;
  realtype max, *xd;

  max = ZERO;
  xd = NULL;

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);

  for (i = 0; i < N; i++) {
    if (SUNRabs(xd[i]) > max) max = SUNRabs(xd[i]);
  }

  return(max);
}

realtype N_VWrmsNorm_Serial(N_Vector x, N_Vector w)
{
  SUNDeclareContext(x->sunctx);
  sunrealtype norm = SUNCheckCallLastErrNoRet(N_VWSqrSumLocal_Serial(x, w), SUNCTX);
  norm = SUNRsqrt(norm/NV_LENGTH_S(x));
  return norm;
}

realtype N_VWSqrSumLocal_Serial(N_Vector x, N_Vector w)
{
  sunindextype i, N;
  realtype sum, prodi, *xd, *wd;

  sum = ZERO;
  xd = wd = NULL;

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);
  wd = NV_DATA_S(w);

  for (i = 0; i < N; i++) {
    prodi = xd[i]*wd[i];
    sum += SUNSQR(prodi);
  }

  return(sum);
}

realtype N_VWrmsNormMask_Serial(N_Vector x, N_Vector w, N_Vector id)
{
  SUNDeclareContext(x->sunctx);
  sunrealtype norm = SUNCheckCallLastErrNoRet(N_VWSqrSumMaskLocal_Serial(x, w, id), SUNCTX);
  norm = SUNRsqrt(norm/NV_LENGTH_S(x));
  return norm;
}

realtype N_VWSqrSumMaskLocal_Serial(N_Vector x, N_Vector w, N_Vector id)
{
  sunindextype i, N;
  realtype sum, prodi, *xd, *wd, *idd;

  sum = ZERO;
  xd = wd = idd = NULL;

  N  = NV_LENGTH_S(x);
  xd  = NV_DATA_S(x);
  wd  = NV_DATA_S(w);
  idd = NV_DATA_S(id);

  for (i = 0; i < N; i++) {
    if (idd[i] > ZERO) {
      prodi = xd[i]*wd[i];
      sum += SUNSQR(prodi);
    }
  }

  return(sum);
}

realtype N_VMin_Serial(N_Vector x)
{
  sunindextype i, N;
  realtype min, *xd;

  xd = NULL;

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);

  min = xd[0];

  for (i = 1; i < N; i++) {
    if (xd[i] < min) min = xd[i];
  }

  return(min);
}

realtype N_VWL2Norm_Serial(N_Vector x, N_Vector w)
{
  sunindextype i, N;
  realtype sum, prodi, *xd, *wd;

  sum = ZERO;
  xd = wd = NULL;

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);
  wd = NV_DATA_S(w);

  for (i = 0; i < N; i++) {
    prodi = xd[i]*wd[i];
    sum += SUNSQR(prodi);
  }

  return(SUNRsqrt(sum));
}

realtype N_VL1Norm_Serial(N_Vector x)
{
  sunindextype i, N;
  realtype sum, *xd;

  sum = ZERO;
  xd = NULL;

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);

  for (i = 0; i<N; i++)
    sum += SUNRabs(xd[i]);

  return(sum);
}

void N_VCompare_Serial(realtype c, N_Vector x, N_Vector z)
{
  sunindextype i, N;
  realtype *xd, *zd;

  xd = zd = NULL;

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);
  zd = NV_DATA_S(z);

  for (i = 0; i < N; i++) {
    zd[i] = (SUNRabs(xd[i]) >= c) ? ONE : ZERO;
  }

  return;
}

booleantype N_VInvTest_Serial(N_Vector x, N_Vector z)
{
  sunindextype i, N;
  realtype *xd, *zd;
  booleantype no_zero_found;

  xd = zd = NULL;

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);
  zd = NV_DATA_S(z);

  no_zero_found = SUNTRUE;
  for (i = 0; i < N; i++) {
    if (xd[i] == ZERO)
      no_zero_found = SUNFALSE;
    else
      zd[i] = ONE/xd[i];
  }

  return no_zero_found;
}

booleantype N_VConstrMask_Serial(N_Vector c, N_Vector x, N_Vector m)
{
  sunindextype i, N;
  realtype temp;
  realtype *cd, *xd, *md;
  booleantype test;

  cd = xd = md = NULL;

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);
  cd = NV_DATA_S(c);
  md = NV_DATA_S(m);

  temp = ZERO;

  for (i = 0; i < N; i++) {
    md[i] = ZERO;

    /* Continue if no constraints were set for the variable */
    if (cd[i] == ZERO)
      continue;

    /* Check if a set constraint has been violated */
    test = (SUNRabs(cd[i]) > ONEPT5 && xd[i]*cd[i] <= ZERO) ||
           (SUNRabs(cd[i]) > HALF   && xd[i]*cd[i] <  ZERO);
    if (test) {
      temp = md[i] = ONE;
    }
  }

  /* Return false if any constraint was violated */
  return (temp == ONE) ? SUNFALSE : SUNTRUE;
}

realtype N_VMinQuotient_Serial(N_Vector num, N_Vector denom)
{
  booleantype notEvenOnce;
  sunindextype i, N;
  realtype *nd, *dd, min;

  nd = dd = NULL;

  N  = NV_LENGTH_S(num);
  nd = NV_DATA_S(num);
  dd = NV_DATA_S(denom);

  notEvenOnce = SUNTRUE;
  min = BIG_REAL;

  for (i = 0; i < N; i++) {
    if (dd[i] == ZERO) continue;
    else {
      if (!notEvenOnce) min = SUNMIN(min, nd[i]/dd[i]);
      else {
	min = nd[i]/dd[i];
        notEvenOnce = SUNFALSE;
      }
    }
  }

  return(min);
}


/*
 * -----------------------------------------------------------------
 * fused vector operations
 * -----------------------------------------------------------------
 */

SUNErrCode N_VLinearCombination_Serial(int nvec, realtype* c, N_Vector* X, N_Vector z)
{
  SUNDeclareContext(X[0]->sunctx);
  int          i;
  sunindextype j, N;
  realtype*    zd=NULL;
  realtype*    xd=NULL;

  /* invalid number of vectors */
  SUNAssert(nvec >= 1, SUN_ERR_ARG_OUTOFRANGE, SUNCTX);

  /* should have called N_VScale */
  if (nvec == 1) {
    SUNCheckCallLastErr(N_VScale_Serial(c[0], X[0], z), SUNCTX);
    return SUN_SUCCESS;
  }

  /* should have called N_VLinearSum */
  if (nvec == 2) {
    SUNCheckCallLastErr(N_VLinearSum_Serial(c[0], X[0], c[1], X[1], z), SUNCTX);
    return SUN_SUCCESS;
  }

  /* get vector length and data array */
  N  = NV_LENGTH_S(z);
  zd = NV_DATA_S(z);

  /*
   * X[0] += c[i]*X[i], i = 1,...,nvec-1
   */
  if ((X[0] == z) && (c[0] == ONE)) {
    for (i=1; i<nvec; i++) {
      xd = NV_DATA_S(X[i]);
      for (j=0; j<N; j++) {
        zd[j] += c[i] * xd[j];
      }
    }
    return SUN_SUCCESS;
  }

  /*
   * X[0] = c[0] * X[0] + sum{ c[i] * X[i] }, i = 1,...,nvec-1
   */
  if (X[0] == z) {
    for (j=0; j<N; j++) {
      zd[j] *= c[0];
    }
    for (i=1; i<nvec; i++) {
      xd = NV_DATA_S(X[i]);
      for (j=0; j<N; j++) {
        zd[j] += c[i] * xd[j];
      }
    }
    return SUN_SUCCESS;
  }

  /*
   * z = sum{ c[i] * X[i] }, i = 0,...,nvec-1
   */
  xd = NV_DATA_S(X[0]);
  for (j=0; j<N; j++) {
    zd[j] = c[0] * xd[j];
  }
  for (i=1; i<nvec; i++) {
    xd = NV_DATA_S(X[i]);
    for (j=0; j<N; j++) {
      zd[j] += c[i] * xd[j];
    }
  }
  return SUN_SUCCESS;
}


SUNErrCode N_VScaleAddMulti_Serial(int nvec, realtype* a, N_Vector x, N_Vector* Y, N_Vector* Z)
{
  SUNDeclareContext(x->sunctx);
  int          i;
  sunindextype j, N;
  realtype*    xd=NULL;
  realtype*    yd=NULL;
  realtype*    zd=NULL;

  /* invalid number of vectors */
  SUNAssert(nvec >= 1, SUN_ERR_ARG_OUTOFRANGE, SUNCTX);

  /* should have called N_VLinearSum */
  if (nvec == 1) {
    SUNCheckCallLastErr(N_VLinearSum_Serial(a[0], x, ONE, Y[0], Z[0]), SUNCTX);
    return SUN_SUCCESS;
  }

  /* get vector length and data array */
  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);

  /*
   * Y[i][j] += a[i] * x[j]
   */
  if (Y == Z) {
    for (i=0; i<nvec; i++) {
      yd = NV_DATA_S(Y[i]);
      for (j=0; j<N; j++) {
        yd[j] += a[i] * xd[j];
      }
    }
    return SUN_SUCCESS;
  }

  /*
   * Z[i][j] = Y[i][j] + a[i] * x[j]
   */
  for (i=0; i<nvec; i++) {
    yd = NV_DATA_S(Y[i]);
    zd = NV_DATA_S(Z[i]);
    for (j=0; j<N; j++) {
      zd[j] = a[i] * xd[j] + yd[j];
    }
  }
  return SUN_SUCCESS;
}


SUNErrCode N_VDotProdMulti_Serial(int nvec, N_Vector x, N_Vector* Y, realtype* dotprods)
{
  SUNDeclareContext(x->sunctx);
  int          i;
  sunindextype j, N;
  realtype*    xd=NULL;
  realtype*    yd=NULL;

  /* invalid number of vectors */
  SUNAssert(nvec >= 1, SUN_ERR_ARG_OUTOFRANGE, SUNCTX);

  /* should have called N_VDotProd */
  if (nvec == 1) {
    dotprods[0] = SUNCheckCallLastErr(N_VDotProd_Serial(x, Y[0]), SUNCTX);
    return SUN_SUCCESS;
  }

  /* get vector length and data array */
  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);

  /* compute multiple dot products */
  for (i=0; i<nvec; i++) {
    yd = NV_DATA_S(Y[i]);
    dotprods[i] = ZERO;
    for (j=0; j<N; j++) {
      dotprods[i] += xd[j] * yd[j];
    }
  }

  return SUN_SUCCESS;
}


/*
 * -----------------------------------------------------------------
 * vector array operations
 * -----------------------------------------------------------------
 */

SUNErrCode N_VLinearSumVectorArray_Serial(int nvec,
                                          realtype a, N_Vector* X,
                                          realtype b, N_Vector* Y,
                                          N_Vector* Z)
{
  SUNDeclareContext(X[0]->sunctx);

  int          i;
  sunindextype j, N;
  realtype*    xd=NULL;
  realtype*    yd=NULL;
  realtype*    zd=NULL;
  realtype     c;
  N_Vector*   V1;
  N_Vector*   V2;
  booleantype  test;

  /* invalid number of vectors */
  SUNAssert(nvec >= 1, SUN_ERR_ARG_OUTOFRANGE, SUNCTX);

  /* should have called N_VLinearSum */
  if (nvec == 1) {
    SUNCheckCallLastErr(N_VLinearSum_Serial(a, X[0], b, Y[0], Z[0]), SUNCTX);
    return SUN_SUCCESS;
  }

  /* BLAS usage: axpy y <- ax+y */
  if ((b == ONE) && (Z == Y)) {
    VaxpyVectorArray_Serial(nvec, a, X, Y);
    return SUN_SUCCESS;
  }

  /* BLAS usage: axpy x <- by+x */
  if ((a == ONE) && (Z == X)) {
    VaxpyVectorArray_Serial(nvec, b, Y, X);
    return SUN_SUCCESS;
  }

  /* Case: a == b == 1.0 */
  if ((a == ONE) && (b == ONE)) {
    VSumVectorArray_Serial(nvec, X, Y, Z);
    return SUN_SUCCESS;
  }

  /* Cases:                    */
  /*   (1) a == 1.0, b = -1.0, */
  /*   (2) a == -1.0, b == 1.0 */
  if ((test = ((a == ONE) && (b == -ONE))) || ((a == -ONE) && (b == ONE))) {
    V1 = test ? Y : X;
    V2 = test ? X : Y;
    VDiffVectorArray_Serial(nvec, V2, V1, Z);
    return SUN_SUCCESS;
  }

  /* Cases:                                                  */
  /*   (1) a == 1.0, b == other or 0.0,                      */
  /*   (2) a == other or 0.0, b == 1.0                       */
  /* if a or b is 0.0, then user should have called N_VScale */
  if ((test = (a == ONE)) || (b == ONE)) {
    c  = test ? b : a;
    V1 = test ? Y : X;
    V2 = test ? X : Y;
    VLin1VectorArray_Serial(nvec, c, V1, V2, Z);
    return SUN_SUCCESS;
  }

  /* Cases:                     */
  /*   (1) a == -1.0, b != 1.0, */
  /*   (2) a != 1.0, b == -1.0  */
  if ((test = (a == -ONE)) || (b == -ONE)) {
    c = test ? b : a;
    V1 = test ? Y : X;
    V2 = test ? X : Y;
    VLin2VectorArray_Serial(nvec, c, V1, V2, Z);
    return SUN_SUCCESS;
  }

  /* Case: a == b                                                         */
  /* catches case both a and b are 0.0 - user should have called N_VConst */
  if (a == b) {
    VScaleSumVectorArray_Serial(nvec, a, X, Y, Z);
    return SUN_SUCCESS;
  }

  /* Case: a == -b */
  if (a == -b) {
    VScaleDiffVectorArray_Serial(nvec, a, X, Y, Z);
    return SUN_SUCCESS;
  }

  /* Do all cases not handled above:                               */
  /*   (1) a == other, b == 0.0 - user should have called N_VScale */
  /*   (2) a == 0.0, b == other - user should have called N_VScale */
  /*   (3) a,b == other, a !=b, a != -b                            */

  /* get vector length */
  N = NV_LENGTH_S(Z[0]);

  /* compute linear sum for each vector pair in vector arrays */
  for (i=0; i<nvec; i++) {
    xd = NV_DATA_S(X[i]);
    yd = NV_DATA_S(Y[i]);
    zd = NV_DATA_S(Z[i]);
    for (j=0; j<N; j++) {
      zd[j] = a * xd[j] + b * yd[j];
    }
  }

  return SUN_SUCCESS;
}


SUNErrCode N_VScaleVectorArray_Serial(int nvec, realtype* c, N_Vector* X, N_Vector* Z)
{
  SUNDeclareContext(X[0]->sunctx);
  int          i;
  sunindextype j, N;
  realtype*    xd=NULL;
  realtype*    zd=NULL;

  /* invalid number of vectors */
  SUNAssert(nvec >= 1, SUN_ERR_ARG_OUTOFRANGE, SUNCTX);

  /* should have called N_VScale */
  if (nvec == 1) {
    SUNCheckCallLastErr(N_VScale_Serial(c[0], X[0], Z[0]), SUNCTX);
    return SUN_SUCCESS;
  }

  /* get vector length */
  N = NV_LENGTH_S(Z[0]);

  /*
   * X[i] *= c[i]
   */
  if (X == Z) {
    for (i=0; i<nvec; i++) {
      xd = NV_DATA_S(X[i]);
      for (j=0; j<N; j++) {
        xd[j] *= c[i];
      }
    }
    return SUN_SUCCESS;
  }

  /*
   * Z[i] = c[i] * X[i]
   */
  for (i=0; i<nvec; i++) {
    xd = NV_DATA_S(X[i]);
    zd = NV_DATA_S(Z[i]);
    for (j=0; j<N; j++) {
      zd[j] = c[i] * xd[j];
    }
  }
  return SUN_SUCCESS;
}


SUNErrCode N_VConstVectorArray_Serial(int nvec, realtype c, N_Vector* Z)
{
  SUNDeclareContext(Z[0]->sunctx);
  int          i;
  sunindextype j, N;
  realtype*    zd=NULL;

  /* invalid number of vectors */
  SUNAssert(nvec >= 1, SUN_ERR_ARG_OUTOFRANGE, SUNCTX);

  /* should have called N_VConst */
  if (nvec == 1) {
    SUNCheckCallLastErr(N_VConst_Serial(c, Z[0]), SUNCTX);
    return SUN_SUCCESS;
  }

  /* get vector length */
  N = NV_LENGTH_S(Z[0]);

  /* set each vector in the vector array to a constant */
  for (i=0; i<nvec; i++) {
    zd = NV_DATA_S(Z[i]);
    for (j=0; j<N; j++) {
      zd[j] = c;
    }
  }

  return SUN_SUCCESS;
}


SUNErrCode N_VWrmsNormVectorArray_Serial(int nvec, N_Vector* X, N_Vector* W,
                                         realtype* nrm)
{
  SUNDeclareContext(X[0]->sunctx);
  int          i;
  sunindextype j, N;
  realtype*    wd=NULL;
  realtype*    xd=NULL;

  /* invalid number of vectors */
  SUNAssert(nvec >= 1, SUN_ERR_ARG_OUTOFRANGE, X[0]->sunctx);

  /* should have called N_VWrmsNorm */
  if (nvec == 1) {
    nrm[0] = SUNCheckCallLastErr(N_VWrmsNorm_Serial(X[0], W[0]), SUNCTX);
    return SUN_SUCCESS;
  }

  /* get vector length */
  N = NV_LENGTH_S(X[0]);

  /* compute the WRMS norm for each vector in the vector array */
  for (i=0; i<nvec; i++) {
    xd = NV_DATA_S(X[i]);
    wd = NV_DATA_S(W[i]);
    nrm[i] = ZERO;
    for (j=0; j<N; j++) {
      nrm[i] += SUNSQR(xd[j] * wd[j]);
    }
    nrm[i] = SUNRsqrt(nrm[i]/N);
  }

  return SUN_SUCCESS;
}


SUNErrCode N_VWrmsNormMaskVectorArray_Serial(int nvec, N_Vector* X, N_Vector* W,
                                      N_Vector id, realtype* nrm)
{
  SUNDeclareContext(X[0]->sunctx);
  int          i;
  sunindextype j, N;
  realtype*    wd=NULL;
  realtype*    xd=NULL;
  realtype*    idd=NULL;

  /* invalid number of vectors */
  SUNAssert(nvec >= 1, SUN_ERR_ARG_OUTOFRANGE, X[0]->sunctx);

  /* should have called N_VWrmsNorm */
  if (nvec == 1) {
    nrm[0] = SUNCheckCallLastErr(N_VWrmsNormMask_Serial(X[0], W[0], id), SUNCTX);
    return SUN_SUCCESS;
  }

  /* get vector length and mask data array */
  N   = NV_LENGTH_S(X[0]);
  idd = NV_DATA_S(id);

  /* compute the WRMS norm for each vector in the vector array */
  for (i=0; i<nvec; i++) {
    xd = NV_DATA_S(X[i]);
    wd = NV_DATA_S(W[i]);
    nrm[i] = ZERO;
    for (j=0; j<N; j++) {
      if (idd[j] > ZERO)
        nrm[i] += SUNSQR(xd[j] * wd[j]);
    }
    nrm[i] = SUNRsqrt(nrm[i]/N);
  }

  return SUN_SUCCESS;
}


SUNErrCode N_VScaleAddMultiVectorArray_Serial(int nvec, int nsum, realtype* a,
                                              N_Vector* X, N_Vector** Y, N_Vector** Z)
{
  SUNDeclareContext(X[0]->sunctx);
  int          i, j;
  sunindextype k, N;
  realtype*    xd=NULL;
  realtype*    yd=NULL;
  realtype*    zd=NULL;
  N_Vector*   YY;
  N_Vector*   ZZ;

  /* invalid number of vectors */
  SUNAssert(nvec >= 1 && nsum >= 1, SUN_ERR_ARG_OUTOFRANGE, SUNCTX);

  /* ---------------------------
   * Special cases for nvec == 1
   * --------------------------- */

  if (nvec == 1) {

    /* should have called N_VLinearSum */
    if (nsum == 1) {
      SUNCheckCallLastErr(N_VLinearSum_Serial(a[0], X[0], ONE, Y[0][0], Z[0][0]), SUNCTX);
      return SUN_SUCCESS;
    }

    /* should have called N_VScaleAddMulti */
    YY = (N_Vector*) malloc(nsum * sizeof(N_Vector));
    ZZ = (N_Vector*) malloc(nsum * sizeof(N_Vector));

    for (j=0; j<nsum; j++) {
      YY[j] = Y[j][0];
      ZZ[j] = Z[j][0];
    }

    SUNCheckCall(N_VScaleAddMulti_Serial(nsum, a, X[0], YY, ZZ), SUNCTX);
    
    free(YY);
    free(ZZ);

    return SUN_SUCCESS;
  }

  /* --------------------------
   * Special cases for nvec > 1
   * -------------------------- */

  /* should have called N_VLinearSumVectorArray */
  if (nsum == 1) {
    SUNCheckCall(N_VLinearSumVectorArray_Serial(nvec, a[0], X, ONE, Y[0], Z[0]), SUNCTX);
    return SUN_SUCCESS;
  }

  /* ----------------------------
   * Compute multiple linear sums
   * ---------------------------- */

  /* get vector length */
  N = NV_LENGTH_S(X[0]);

  /*
   * Y[i][j] += a[i] * x[j]
   */
  if (Y == Z) {
    for (i=0; i<nvec; i++) {
      xd = NV_DATA_S(X[i]);
      for (j=0; j<nsum; j++){
        yd = NV_DATA_S(Y[j][i]);
        for (k=0; k<N; k++) {
          yd[k] += a[j] * xd[k];
        }
      }
    }
    return SUN_SUCCESS;
  }

  /*
   * Z[i][j] = Y[i][j] + a[i] * x[j]
   */
  for (i=0; i<nvec; i++) {
    xd = NV_DATA_S(X[i]);
    for (j=0; j<nsum; j++){
      yd = NV_DATA_S(Y[j][i]);
      zd = NV_DATA_S(Z[j][i]);
      for (k=0; k<N; k++) {
        zd[k] = a[j] * xd[k] + yd[k];
      }
    }
  }
  return SUN_SUCCESS;
}


SUNErrCode N_VLinearCombinationVectorArray_Serial(int nvec, int nsum, realtype* c,
                                                  N_Vector** X, N_Vector* Z)
{
  SUNDeclareContext(X[0][0]->sunctx);
  int          i; /* vector arrays index in summation [0,nsum) */
  int          j; /* vector index in vector array     [0,nvec) */
  sunindextype k; /* element index in vector          [0,N)    */
  sunindextype N;
  realtype*    zd=NULL;
  realtype*    xd=NULL;
  realtype*    ctmp;
  N_Vector*   Y;

  /* invalid number of vectors */
  SUNAssert(nvec >= 1 && nsum >= 1, SUN_ERR_ARG_OUTOFRANGE, SUNCTX);

  /* ---------------------------
   * Special cases for nvec == 1
   * --------------------------- */

  if (nvec == 1) {

    /* should have called N_VScale */
    if (nsum == 1) {
      SUNCheckCallLastErr(N_VScale_Serial(c[0], X[0][0], Z[0]), SUNCTX);
      return SUN_SUCCESS;
    }

    /* should have called N_VLinearSum */
    if (nsum == 2) {
      SUNCheckCallLastErr(N_VLinearSum_Serial(c[0], X[0][0], c[1], X[1][0], Z[0]), SUNCTX);
      return SUN_SUCCESS;
    }

    /* should have called N_VLinearCombination */
    Y = (N_Vector*) malloc(nsum * sizeof(N_Vector));

    for (i=0; i<nsum; i++) {
      Y[i] = X[i][0];
    }

    SUNCheckCall(N_VLinearCombination_Serial(nsum, c, Y, Z[0]), SUNCTX);

    free(Y);

    return SUN_SUCCESS;
  }

  /* --------------------------
   * Special cases for nvec > 1
   * -------------------------- */

  /* should have called N_VScaleVectorArray */
  if (nsum == 1) {

    ctmp = (realtype*) malloc(nvec * sizeof(realtype));

    for (j=0; j<nvec; j++) {
      ctmp[j] = c[0];
    }

    SUNCheckCall(N_VScaleVectorArray_Serial(nvec, ctmp, X[0], Z), SUNCTX);

    free(ctmp);
    return SUN_SUCCESS;
  }

  /* should have called N_VLinearSumVectorArray */
  if (nsum == 2) {
    SUNCheckCall(N_VLinearSumVectorArray_Serial(nvec, c[0], X[0], c[1], X[1], Z), SUNCTX);
    return SUN_SUCCESS;
  }

  /* --------------------------
   * Compute linear combination
   * -------------------------- */

  /* get vector length */
  N = NV_LENGTH_S(Z[0]);

  /*
   * X[0][j] += c[i]*X[i][j], i = 1,...,nvec-1
   */
  if ((X[0] == Z) && (c[0] == ONE)) {
    for (j=0; j<nvec; j++) {
      zd = NV_DATA_S(Z[j]);
      for (i=1; i<nsum; i++) {
        xd = NV_DATA_S(X[i][j]);
        for (k=0; k<N; k++) {
          zd[k] += c[i] * xd[k];
        }
      }
    }
    return SUN_SUCCESS;
  }

  /*
   * X[0][j] = c[0] * X[0][j] + sum{ c[i] * X[i][j] }, i = 1,...,nvec-1
   */
  if (X[0] == Z) {
    for (j=0; j<nvec; j++) {
      zd = NV_DATA_S(Z[j]);
      for (k=0; k<N; k++) {
        zd[k] *= c[0];
      }
      for (i=1; i<nsum; i++) {
        xd = NV_DATA_S(X[i][j]);
        for (k=0; k<N; k++) {
          zd[k] += c[i] * xd[k];
        }
      }
    }
    return SUN_SUCCESS;
  }

  /*
   * Z[j] = sum{ c[i] * X[i][j] }, i = 0,...,nvec-1
   */
  for (j=0; j<nvec; j++) {
    xd = NV_DATA_S(X[0][j]);
    zd = NV_DATA_S(Z[j]);
    for (k=0; k<N; k++) {
      zd[k] = c[0] * xd[k];
    }
    for (i=1; i<nsum; i++) {
      xd = NV_DATA_S(X[i][j]);
      for (k=0; k<N; k++) {
        zd[k] += c[i] * xd[k];
      }
    }
  }
  return SUN_SUCCESS;
}


/*
 * -----------------------------------------------------------------
 * OPTIONAL XBraid interface operations
 * -----------------------------------------------------------------
 */


SUNErrCode N_VBufSize_Serial(N_Vector x, sunindextype *size)
{
  *size = NV_LENGTH_S(x) * ((sunindextype)sizeof(realtype));
  return SUN_SUCCESS;
}


SUNErrCode N_VBufPack_Serial(N_Vector x, void *buf)
{
  sunindextype i, N;
  realtype     *xd = NULL;
  realtype     *bd = NULL;

  SUNAssert(buf, SUN_ERR_ARG_CORRUPT, x->sunctx);

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);
  bd = (realtype*) buf;

  for (i = 0; i < N; i++)
    bd[i] = xd[i];

  return SUN_SUCCESS;
}


SUNErrCode N_VBufUnpack_Serial(N_Vector x, void *buf)
{
  sunindextype i, N;
  realtype     *xd = NULL;
  realtype     *bd = NULL;

  SUNAssert(buf, SUN_ERR_ARG_CORRUPT, x->sunctx);

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);
  bd = (realtype*) buf;

  for (i = 0; i < N; i++)
    xd[i] = bd[i];

  return SUN_SUCCESS;
}


/*
 * -----------------------------------------------------------------
 * private functions for special cases of vector operations
 * -----------------------------------------------------------------
 */

static void VCopy_Serial(N_Vector x, N_Vector z)
{
  sunindextype i, N;
  realtype *xd, *zd;

  xd = zd = NULL;

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);
  zd = NV_DATA_S(z);

  for (i = 0; i < N; i++)
    zd[i] = xd[i];

  return;
}

static void VSum_Serial(N_Vector x, N_Vector y, N_Vector z)
{
  sunindextype i, N;
  realtype *xd, *yd, *zd;

  xd = yd = zd = NULL;

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);
  yd = NV_DATA_S(y);
  zd = NV_DATA_S(z);

  for (i = 0; i < N; i++)
    zd[i] = xd[i]+yd[i];

  return;
}

static void VDiff_Serial(N_Vector x, N_Vector y, N_Vector z)
{
  sunindextype i, N;
  realtype *xd, *yd, *zd;

  xd = yd = zd = NULL;

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);
  yd = NV_DATA_S(y);
  zd = NV_DATA_S(z);

  for (i = 0; i < N; i++)
    zd[i] = xd[i]-yd[i];

  return;
}

static void VNeg_Serial(N_Vector x, N_Vector z)
{
  sunindextype i, N;
  realtype *xd, *zd;

  xd = zd = NULL;

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);
  zd = NV_DATA_S(z);

  for (i = 0; i < N; i++)
    zd[i] = -xd[i];

  return;
}

static void VScaleSum_Serial(realtype c, N_Vector x, N_Vector y, N_Vector z)
{
  sunindextype i, N;
  realtype *xd, *yd, *zd;

  xd = yd = zd = NULL;

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);
  yd = NV_DATA_S(y);
  zd = NV_DATA_S(z);

  for (i = 0; i < N; i++)
    zd[i] = c*(xd[i]+yd[i]);

  return;
}

static void VScaleDiff_Serial(realtype c, N_Vector x, N_Vector y, N_Vector z)
{
  sunindextype i, N;
  realtype *xd, *yd, *zd;

  xd = yd = zd = NULL;

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);
  yd = NV_DATA_S(y);
  zd = NV_DATA_S(z);

  for (i = 0; i < N; i++)
    zd[i] = c*(xd[i]-yd[i]);

  return;
}

static void VLin1_Serial(realtype a, N_Vector x, N_Vector y, N_Vector z)
{
  sunindextype i, N;
  realtype *xd, *yd, *zd;

  xd = yd = zd = NULL;

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);
  yd = NV_DATA_S(y);
  zd = NV_DATA_S(z);

  for (i = 0; i < N; i++)
    zd[i] = (a*xd[i])+yd[i];

  return;
}

static void VLin2_Serial(realtype a, N_Vector x, N_Vector y, N_Vector z)
{
  sunindextype i, N;
  realtype *xd, *yd, *zd;

  xd = yd = zd = NULL;

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);
  yd = NV_DATA_S(y);
  zd = NV_DATA_S(z);

  for (i = 0; i < N; i++)
    zd[i] = (a*xd[i])-yd[i];

  return;
}

static void Vaxpy_Serial(realtype a, N_Vector x, N_Vector y)
{
  sunindextype i, N;
  realtype *xd, *yd;

  xd = yd = NULL;

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);
  yd = NV_DATA_S(y);

  if (a == ONE) {
    for (i = 0; i < N; i++)
      yd[i] += xd[i];
    return;
  }

  if (a == -ONE) {
    for (i = 0; i < N; i++)
      yd[i] -= xd[i];
    return;
  }

  for (i = 0; i < N; i++)
    yd[i] += a*xd[i];

  return;
}

static void VScaleBy_Serial(realtype a, N_Vector x)
{
  sunindextype i, N;
  realtype *xd;

  xd = NULL;

  N  = NV_LENGTH_S(x);
  xd = NV_DATA_S(x);

  for (i = 0; i < N; i++)
    xd[i] *= a;

  return;
}


/*
 * -----------------------------------------------------------------
 * private functions for special cases of vector array operations
 * -----------------------------------------------------------------
 */

static void VSumVectorArray_Serial(int nvec, N_Vector* X, N_Vector* Y, N_Vector* Z)
{
  int          i;
  sunindextype j, N;
  realtype*    xd=NULL;
  realtype*    yd=NULL;
  realtype*    zd=NULL;

  N = NV_LENGTH_S(X[0]);

  for (i=0; i<nvec; i++) {
    xd = NV_DATA_S(X[i]);
    yd = NV_DATA_S(Y[i]);
    zd = NV_DATA_S(Z[i]);
    for (j=0; j<N; j++)
      zd[j] = xd[j] + yd[j];
  }
}

static void VDiffVectorArray_Serial(int nvec, N_Vector* X, N_Vector* Y, N_Vector* Z)
{
  int          i;
  sunindextype j, N;
  realtype*    xd=NULL;
  realtype*    yd=NULL;
  realtype*    zd=NULL;

  N = NV_LENGTH_S(X[0]);

  for (i=0; i<nvec; i++) {
    xd = NV_DATA_S(X[i]);
    yd = NV_DATA_S(Y[i]);
    zd = NV_DATA_S(Z[i]);
    for (j=0; j<N; j++)
      zd[j] = xd[j] - yd[j];
  }
}

static void VScaleSumVectorArray_Serial(int nvec, realtype c, N_Vector* X, N_Vector* Y, N_Vector* Z)
{
  int          i;
  sunindextype j, N;
  realtype*    xd=NULL;
  realtype*    yd=NULL;
  realtype*    zd=NULL;

  N = NV_LENGTH_S(X[0]);

  for (i=0; i<nvec; i++) {
    xd = NV_DATA_S(X[i]);
    yd = NV_DATA_S(Y[i]);
    zd = NV_DATA_S(Z[i]);
    for (j=0; j<N; j++)
      zd[j] = c * (xd[j] + yd[j]);
  }
}

static void VScaleDiffVectorArray_Serial(int nvec, realtype c, N_Vector* X, N_Vector* Y, N_Vector* Z)
{
  int          i;
  sunindextype j, N;
  realtype*    xd=NULL;
  realtype*    yd=NULL;
  realtype*    zd=NULL;

  N = NV_LENGTH_S(X[0]);

  for (i=0; i<nvec; i++) {
    xd = NV_DATA_S(X[i]);
    yd = NV_DATA_S(Y[i]);
    zd = NV_DATA_S(Z[i]);
    for (j=0; j<N; j++)
      zd[j] = c * (xd[j] - yd[j]);
  }
}

static void VLin1VectorArray_Serial(int nvec, realtype a, N_Vector* X, N_Vector* Y, N_Vector* Z)
{
  int          i;
  sunindextype j, N;
  realtype*    xd=NULL;
  realtype*    yd=NULL;
  realtype*    zd=NULL;

  N = NV_LENGTH_S(X[0]);

  for (i=0; i<nvec; i++) {
    xd = NV_DATA_S(X[i]);
    yd = NV_DATA_S(Y[i]);
    zd = NV_DATA_S(Z[i]);
    for (j=0; j<N; j++)
      zd[j] = (a * xd[j]) + yd[j];
  }
}

static void VLin2VectorArray_Serial(int nvec, realtype a, N_Vector* X, N_Vector* Y, N_Vector* Z)
{
  int          i;
  sunindextype j, N;
  realtype*    xd=NULL;
  realtype*    yd=NULL;
  realtype*    zd=NULL;

  N = NV_LENGTH_S(X[0]);

  for (i=0; i<nvec; i++) {
    xd = NV_DATA_S(X[i]);
    yd = NV_DATA_S(Y[i]);
    zd = NV_DATA_S(Z[i]);
    for (j=0; j<N; j++)
      zd[j] = (a * xd[j]) - yd[j];
  }
}

static void VaxpyVectorArray_Serial(int nvec, realtype a, N_Vector* X, N_Vector* Y)
{
  int          i;
  sunindextype j, N;
  realtype*    xd=NULL;
  realtype*    yd=NULL;

  N = NV_LENGTH_S(X[0]);

  if (a == ONE) {
    for (i=0; i<nvec; i++) {
      xd = NV_DATA_S(X[i]);
      yd = NV_DATA_S(Y[i]);
      for (j=0; j<N; j++)
        yd[j] += xd[j];
    }
    return;
  }

  if (a == -ONE) {
    for (i=0; i<nvec; i++) {
      xd = NV_DATA_S(X[i]);
      yd = NV_DATA_S(Y[i]);
      for (j=0; j<N; j++)
        yd[j] -= xd[j];
    }
    return;
  }

  for (i=0; i<nvec; i++) {
    xd = NV_DATA_S(X[i]);
    yd = NV_DATA_S(Y[i]);
    for (j=0; j<N; j++)
      yd[j] += a * xd[j];
  }
}


/*
 * -----------------------------------------------------------------
 * Enable / Disable fused and vector array operations
 * -----------------------------------------------------------------
 */

SUNErrCode N_VEnableFusedOps_Serial(N_Vector v, booleantype tf)
{
  if (tf) {
    /* enable all fused vector operations */
    v->ops->nvlinearcombination = N_VLinearCombination_Serial;
    v->ops->nvscaleaddmulti     = N_VScaleAddMulti_Serial;
    v->ops->nvdotprodmulti      = N_VDotProdMulti_Serial;
    /* enable all vector array operations */
    v->ops->nvlinearsumvectorarray         = N_VLinearSumVectorArray_Serial;
    v->ops->nvscalevectorarray             = N_VScaleVectorArray_Serial;
    v->ops->nvconstvectorarray             = N_VConstVectorArray_Serial;
    v->ops->nvwrmsnormvectorarray          = N_VWrmsNormVectorArray_Serial;
    v->ops->nvwrmsnormmaskvectorarray      = N_VWrmsNormMaskVectorArray_Serial;
    v->ops->nvscaleaddmultivectorarray     = N_VScaleAddMultiVectorArray_Serial;
    v->ops->nvlinearcombinationvectorarray = N_VLinearCombinationVectorArray_Serial;
    /* enable single buffer reduction operations */
    v->ops->nvdotprodmultilocal = N_VDotProdMulti_Serial;
  } else {
    /* disable all fused vector operations */
    v->ops->nvlinearcombination = NULL;
    v->ops->nvscaleaddmulti     = NULL;
    v->ops->nvdotprodmulti      = NULL;
    /* disable all vector array operations */
    v->ops->nvlinearsumvectorarray         = NULL;
    v->ops->nvscalevectorarray             = NULL;
    v->ops->nvconstvectorarray             = NULL;
    v->ops->nvwrmsnormvectorarray          = NULL;
    v->ops->nvwrmsnormmaskvectorarray      = NULL;
    v->ops->nvscaleaddmultivectorarray     = NULL;
    v->ops->nvlinearcombinationvectorarray = NULL;
    /* disable single buffer reduction operations */
    v->ops->nvdotprodmultilocal = NULL;
  }

  /* return success */
  return SUN_SUCCESS;
}

NVECTOR_DEFINE_ENABLE_FUSEDOP(LinearCombination, linearcombination, Serial)
NVECTOR_DEFINE_ENABLE_FUSEDOP(ScaleAddMulti, scaleaddmulti, Serial)
NVECTOR_DEFINE_ENABLE_FUSEDOP(DotProdMulti, dotprodmulti, Serial)
NVECTOR_DEFINE_ENABLE_FUSEDOP(LinearSumVectorArray, linearsumvectorarray, Serial)
NVECTOR_DEFINE_ENABLE_FUSEDOP(ScaleVectorArray, scalevectorarray, Serial)
NVECTOR_DEFINE_ENABLE_FUSEDOP(ConstVectorArray, constvectorarray, Serial)
NVECTOR_DEFINE_ENABLE_FUSEDOP(WrmsNormVectorArray, wrmsnormvectorarray, Serial)
NVECTOR_DEFINE_ENABLE_FUSEDOP(WrmsNormMaskVectorArray, wrmsnormmaskvectorarray, Serial)
NVECTOR_DEFINE_ENABLE_FUSEDOP(ScaleAddMultiVectorArray, scaleaddmultivectorarray, Serial)
NVECTOR_DEFINE_ENABLE_FUSEDOP(LinearCombinationVectorArray, linearcombinationvectorarray, Serial)
