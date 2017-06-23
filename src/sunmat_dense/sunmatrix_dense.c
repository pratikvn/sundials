/*
 * -----------------------------------------------------------------
 * Programmer(s): Daniel Reynolds @ SMU
 *                David Gardner, Carol Woodward, Slaven Peles @ LLNL
 * -----------------------------------------------------------------
 * LLNS/SMU Copyright Start
 * Copyright (c) 2017, Southern Methodist University and 
 * Lawrence Livermore National Security
 *
 * This work was performed under the auspices of the U.S. Department 
 * of Energy by Southern Methodist University and Lawrence Livermore 
 * National Laboratory under Contract DE-AC52-07NA27344.
 * Produced at Southern Methodist University and the Lawrence 
 * Livermore National Laboratory.
 *
 * All rights reserved.
 * For details, see the LICENSE file.
 * LLNS/SMU Copyright End
 * -----------------------------------------------------------------
 * This is the implementation file for the dense implementation of 
 * the SUNMATRIX package.
 * -----------------------------------------------------------------
 */ 

#include <stdio.h>
#include <stdlib.h>

#include <sunmatrix/sunmatrix_dense.h>
#include <sundials/sundials_math.h>

#define ZERO RCONST(0.0)
#define ONE  RCONST(1.0)


/* Private function prototypes */
static booleantype SMCompatible_Dense(SUNMatrix A, SUNMatrix B);
static booleantype SMCompatible2_Dense(SUNMatrix A, N_Vector x, N_Vector y);


/*
 * -----------------------------------------------------------------
 * exported functions
 * -----------------------------------------------------------------
 */

/* ----------------------------------------------------------------------------
 * Function to create a new dense matrix
 */

SUNMatrix SUNDenseMatrix(long int M, long int N)
{
  SUNMatrix A;
  SUNMatrix_Ops ops;
  SUNMatrixContent_Dense content;
  long int j;

  /* return with NULL matrix on illegal dimension input */
  if ( (M <= 0) || (N <= 0) ) return(NULL);

  /* Create matrix */
  A = NULL;
  A = (SUNMatrix) malloc(sizeof *A);
  if (A == NULL) return(NULL);
  
  /* Create matrix operation structure */
  ops = NULL;
  ops = (SUNMatrix_Ops) malloc(sizeof(struct _generic_SUNMatrix_Ops));
  if (ops == NULL) { free(A); return(NULL); }

  /* Attach operations */
  ops->getid       = SUNMatGetID_Dense;
  ops->clone       = SUNMatClone_Dense;
  ops->destroy     = SUNMatDestroy_Dense;
  ops->zero        = SUNMatZero_Dense;
  ops->scale       = SUNMatScale_Dense;
  ops->copy        = SUNMatCopy_Dense;
  ops->addidentity = SUNMatAddIdentity_Dense;
  ops->add         = SUNMatAdd_Dense;
  ops->matvec      = SUNMatMatvec_Dense;

  /* Create content */
  content = NULL;
  content = (SUNMatrixContent_Dense) malloc(sizeof(struct _SUNMatrixContent_Dense));
  if (content == NULL) { free(ops); free(A); return(NULL); }

  /* Fill content */
  content->M = M;
  content->N = N;
  content->ldata = M*N;
  content->data = NULL;
  content->data = (realtype *) malloc(M * N * sizeof(realtype));
  if (content->data == NULL) {
    free(content); free(ops); free(A); return(NULL);
  }
  content->cols = NULL;
  content->cols = (realtype **) malloc(N * sizeof(realtype *));
  if (content->cols == NULL) {
    free(content->data); free(content); free(ops); free(A); return(NULL);
  }
  for (j=0; j<N; j++) content->cols[j] = content->data + j * M;
  
  /* Attach content and ops */
  A->content = content;
  A->ops     = ops;

  return(A);
}


/* ----------------------------------------------------------------------------
 * Function to print the dense matrix 
 */
 
void SUNDenseMatrix_Print(SUNMatrix A, FILE* outfile)
{
  long int i, j;
  
  /* should not be called unless A is a dense matrix; 
     otherwise return immediately */
  if (SUNMatGetID(A) != SUNMATRIX_DENSE)
    return;

  /* perform operation */
  fprintf(outfile,"\n");
  for (i=0; i<SM_ROWS_D(A); i++) {
    for (j=0; j<SM_COLUMNS_D(A); j++) {
#if defined(SUNDIALS_EXTENDED_PRECISION)
      fprintf(outfile,"%12Lg  ", SM_ELEMENT_D(A,i,j));
#elif defined(SUNDIALS_DOUBLE_PRECISION)
      fprintf(outfile,"%12g  ", SM_ELEMENT_D(A,i,j));
#else
      fprintf(outfile,"%12g  ", SM_ELEMENT_D(A,i,j));
#endif
    }
    fprintf(outfile,"\n");
  }
  fprintf(outfile,"\n");
  return;
}


/* ----------------------------------------------------------------------------
 * Functions to access the contents of the dense matrix structure
 */

long int SUNDenseMatrix_Rows(SUNMatrix A)
{
  if (SUNMatGetID(A) == SUNMATRIX_DENSE)
    return SM_ROWS_D(A);
  else
    return -1;
}

long int SUNDenseMatrix_Columns(SUNMatrix A)
{
  if (SUNMatGetID(A) == SUNMATRIX_DENSE)
    return SM_COLUMNS_D(A);
  else
    return -1;
}

long int SUNDenseMatrix_LData(SUNMatrix A)
{
  if (SUNMatGetID(A) == SUNMATRIX_DENSE)
    return SM_LDATA_D(A);
  else
    return -1;
}

realtype* SUNDenseMatrix_Data(SUNMatrix A)
{
  if (SUNMatGetID(A) == SUNMATRIX_DENSE)
    return SM_DATA_D(A);
  else
    return NULL;
}

realtype* SUNDenseMatrix_Column(SUNMatrix A, long int j)
{
  if (SUNMatGetID(A) == SUNMATRIX_DENSE)
    return SM_COLUMN_D(A,j);
  else
    return NULL;
}


/*
 * -----------------------------------------------------------------
 * implementation of matrix operations
 * -----------------------------------------------------------------
 */

SUNMatrix_ID SUNMatGetID_Dense(SUNMatrix A)
{
  return SUNMATRIX_DENSE;
}

SUNMatrix SUNMatClone_Dense(SUNMatrix A)
{
  SUNMatrix B = SUNDenseMatrix(SM_ROWS_D(A), SM_COLUMNS_D(A));
  return(B);
}

void SUNMatDestroy_Dense(SUNMatrix A)
{
  /* perform operation */
  free(SM_DATA_D(A));  SM_DATA_D(A) = NULL;
  free(SM_CONTENT_D(A)->cols);  SM_CONTENT_D(A)->cols = NULL;
  free(A->content);  A->content = NULL;
  free(A->ops);  A->ops = NULL;
  free(A); A = NULL;
  return;
}

int SUNMatZero_Dense(SUNMatrix A)
{
  long int i;
  realtype *Adata;

  /* Perform operation */
  Adata = SM_DATA_D(A);
  for (i=0; i<SM_LDATA_D(A); i++)
    Adata[i] = ZERO;
  return 0;
}

int SUNMatScale_Dense(realtype c, SUNMatrix A)
{
  long int i;
  realtype *Adata;

  /* Perform operation */
  Adata = SM_DATA_D(A);
  for (i=0; i<SM_LDATA_D(A); i++)
    Adata[i] *= c;
  return 0;
}

int SUNMatCopy_Dense(SUNMatrix A, SUNMatrix B)
{
  long int i, j;

  /* Verify that A and B are compatible */
  if (!SMCompatible_Dense(A, B))
    return 1;

  /* Perform operation */
  for (j=0; j<SM_COLUMNS_D(A); j++)
    for (i=0; i<SM_ROWS_D(A); i++)
      SM_ELEMENT_D(A,i,j) = SM_ELEMENT_D(B,i,j);
  return 0;
}

int SUNMatAddIdentity_Dense(SUNMatrix A)
{
  long int i;

  /* Perform operation */
  for (i=0; i<SM_COLUMNS_D(A); i++)
    SM_ELEMENT_D(A,i,i) += ONE;
  return 0;
}

int SUNMatAdd_Dense(SUNMatrix A, SUNMatrix B)
{
  long int i, j;

  /* Verify that A and B are compatible */
  if (!SMCompatible_Dense(A, B))
    return 1;

  /* Perform operation */
  for (j=0; j<SM_COLUMNS_D(A); j++)
    for (i=0; i<SM_ROWS_D(A); i++)
      SM_ELEMENT_D(A,i,j) += SM_ELEMENT_D(B,i,j);
  return 0;
}

int SUNMatMatvec_Dense(SUNMatrix A, N_Vector x, N_Vector y)
{
  long int i, j;
  realtype *col_j, *xd, *yd;
  
  /* Verify that A, x and y are compatible */
  if (!SMCompatible2_Dense(A, x, y))
    return 1;

  /* access vector data (return if failure) */
  xd = N_VGetArrayPointer(x);
  yd = N_VGetArrayPointer(y);
  if ((xd == NULL) || (yd == NULL))
    return 1;

  /* Perform operation */
  for (i=0; i<SM_ROWS_D(A); i++)
    yd[i] = ZERO;
  for(j=0; j<SM_COLUMNS_D(A); j++) {
    col_j = SM_COLUMN_D(A,j);
    for (i=0; i<SM_ROWS_D(A); i++)
      yd[i] += col_j[i]*xd[j];
  }
  return 0;
}


/*
 * -----------------------------------------------------------------
 * private functions
 * -----------------------------------------------------------------
 */

static booleantype SMCompatible_Dense(SUNMatrix A, SUNMatrix B)
{
  /* both matrices must be SUNMATRIX_DENSE */
  if (SUNMatGetID(A) != SUNMATRIX_DENSE)
    return FALSE;
  if (SUNMatGetID(B) != SUNMATRIX_DENSE)
    return FALSE;

  /* both matrices must have the same shape */
  if (SM_ROWS_D(A) != SM_ROWS_D(B))
    return FALSE;
  if (SM_COLUMNS_D(A) != SM_COLUMNS_D(B))
    return FALSE;

  return TRUE;
}


static booleantype SMCompatible2_Dense(SUNMatrix A, N_Vector x, N_Vector y)
{
  /* vectors must be one of {SERIAL, OPENMP, PTHREADS}, and 
     have compatible dimensions */ 
  if (N_VGetVectorID(x) == SUNDIALS_NVEC_SERIAL) {
    if (N_VGetLength_Serial(x) != SUNDenseMatrix_Columns(A))
      return FALSE;
  } else if (N_VGetVectorID(x) == SUNDIALS_NVEC_OPENMP) {
    if (N_VGetLength_OpenMP(x) != SUNDenseMatrix_Columns(A))
      return FALSE;
  } else if (N_VGetVectorID(x) == SUNDIALS_NVEC_PTHREADS) {
    if (N_VGetLength_Pthreads(x) != SUNDenseMatrix_Columns(A))
      return FALSE;
  } else {   /* incompatible type */
    return FALSE;
  }
  if (N_VGetVectorID(y) == SUNDIALS_NVEC_SERIAL) {
    if (N_VGetLength_Serial(y) != SUNDenseMatrix_Rows(A))
      return FALSE;
  } else if (N_VGetVectorID(y) == SUNDIALS_NVEC_OPENMP) {
    if (N_VGetLength_OpenMP(y) != SUNDenseMatrix_Rows(A))
      return FALSE;
  } else if (N_VGetVectorID(y) == SUNDIALS_NVEC_PTHREADS) {
    if (N_VGetLength_Pthreads(y) != SUNDenseMatrix_Rows(A))
      return FALSE;
  } else {   /* incompatible type */
    return FALSE;
  }

  return TRUE;
}

