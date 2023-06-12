/* -----------------------------------------------------------------
 * Programmer(s): Daniel Reynolds @ SMU
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
 * This is the header file for the SUNControl_PI module.
 * -----------------------------------------------------------------*/

#ifndef _SUNCONTROL_PI_H
#define _SUNCONTROL_PI_H

#include <stdio.h>
#include <sundials/sundials_control.h>

#ifdef __cplusplus  /* wrapper to enable C++ usage */
extern "C" {
#endif

/* -------------------------------
 * PI implementation of SUNControl
 * ------------------------------- */

struct _SUNControlContent_PI {
  realtype k1;     /* internal controller parameters */
  realtype k2;
  realtype bias;   /* error bias factor */
  realtype safety; /* step safety factor */
  realtype ep;     /* error from previous step */
  int p;           /* order of accuracy to use for controller */
};

typedef struct _SUNControlContent_PI *SUNControlContent_PI;

/* ------------------
 * Exported Functions
 * ------------------ */

SUNDIALS_EXPORT
SUNControl SUNControlPI(SUNContext sunctx);
SUNDIALS_EXPORT
SUNControl SUNControlPI_SetParams(SUNControl C, int p, realtype k1,
                                   realtype k2, realtype k3);
SUNDIALS_EXPORT
SUNControl_ID SUNControlGetID_PI(SUNControl C);
SUNDIALS_EXPORT
void SUNControlDestroy_PI(SUNControl C);
SUNDIALS_EXPORT
int SUNControlEstimateStep_PI(SUNControl C, realtype h,
                                 realtype dsm, realtype* hnew);
SUNDIALS_EXPORT
int SUNControlReset_PI(SUNControl C);
SUNDIALS_EXPORT
int SUNControlSetDefaults_PI(SUNControl C);
SUNDIALS_EXPORT
int SUNControlWrite_PI(SUNControl C, FILE* fptr);
SUNDIALS_EXPORT
int SUNControlSetMethodOrder_PI(SUNControl C, int p);
SUNDIALS_EXPORT
int SUNControlSetSafetyFactor_PI(SUNControl C, realtype safety);
SUNDIALS_EXPORT
int SUNControlSetErrorBias_PI(SUNControl C, realtype bias);
SUNDIALS_EXPORT
int SUNControlUpdate_PI(SUNControl C, realtype h, realtype dsm);
SUNDIALS_EXPORT
int SUNControlSpace_PI(SUNControl C, long int *lenrw,
                          long int *leniw);

#ifdef __cplusplus
}
#endif

#endif  /* _SUNCONTROL_PI_H */
