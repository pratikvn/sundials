/*---------------------------------------------------------------
 * Programmer(s): Daniel R. Reynolds @ SMU
 *---------------------------------------------------------------
 * SUNDIALS Copyright Start
 * Copyright (c) 2002-2023, Lawrence Livermore National Security
 * and Southern Methodist University.
 * All rights reserved.
 *
 * See the top-level LICENSE and NOTICE files for details.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * SUNDIALS Copyright End
 *---------------------------------------------------------------
 * Fortran/C interface routines for ARKODE/ARKLS, for the case
 * of a user-supplied Jacobian approximation routine.
 *--------------------------------------------------------------*/

#include <arkode/arkode_arkstep.h>
#include <stdio.h>
#include <stdlib.h>
#include <sunmatrix/sunmatrix_band.h>

#include "arkode_impl.h"
#include "farkode.h"

/*=============================================================*/

/* Prototype of the Fortran routine */

#ifdef __cplusplus /* wrapper to enable C++ usage */
extern "C" {
#endif

extern void FARK_BJAC(long int* N, long int* MU, long int* ML, long int* EBAND,
                      sunrealtype* T, sunrealtype* Y, sunrealtype* FY,
                      sunrealtype* BJAC, sunrealtype* H, long int* IPAR,
                      sunrealtype* RPAR, sunrealtype* V1, sunrealtype* V2,
                      sunrealtype* V3, int* IER);

#ifdef __cplusplus
}
#endif

/*=============================================================*/

/* Fortran interface routine to ARKStepSetJacFn; see farkode.h
   for further details */
void FARK_BANDSETJAC(int* flag, int* ier)
{
  if (*flag == 0) { *ier = ARKStepSetJacFn(ARK_arkodemem, NULL); }
  else { *ier = ARKStepSetJacFn(ARK_arkodemem, FARKBandJac); }
  return;
}

/*=============================================================*/

/* C interface to user-supplied Fortran subroutine FARKBJAC; see
   farkode.h for further details */
int FARKBandJac(sunrealtype t, N_Vector y, N_Vector fy, SUNMatrix J,
                void* user_data, N_Vector vtemp1, N_Vector vtemp2,
                N_Vector vtemp3)
{
  sunrealtype *ydata, *fydata, *jacdata, *v1data, *v2data, *v3data;
  sunrealtype h;
  long int N, mupper, mlower, smu, eband;
  FARKUserData ARK_userdata;
  int ier = 0;

  ARKStepGetLastStep(ARK_arkodemem, &h);
  ydata        = N_VGetArrayPointer(y);
  fydata       = N_VGetArrayPointer(fy);
  v1data       = N_VGetArrayPointer(vtemp1);
  v2data       = N_VGetArrayPointer(vtemp2);
  v3data       = N_VGetArrayPointer(vtemp3);
  N            = SUNBandMatrix_Columns(J);
  mupper       = SUNBandMatrix_UpperBandwidth(J);
  mlower       = SUNBandMatrix_LowerBandwidth(J);
  smu          = SUNBandMatrix_StoredUpperBandwidth(J);
  eband        = smu + mlower + 1;
  jacdata      = SUNBandMatrix_Column(J, 0) - mupper;
  ARK_userdata = (FARKUserData)user_data;

  FARK_BJAC(&N, &mupper, &mlower, &eband, &t, ydata, fydata, jacdata, &h,
            ARK_userdata->ipar, ARK_userdata->rpar, v1data, v2data, v3data, &ier);
  return (ier);
}

/*===============================================================
   EOF
===============================================================*/
