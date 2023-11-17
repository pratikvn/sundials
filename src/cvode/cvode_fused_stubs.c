/*
 * -----------------------------------------------------------------
 * Programmer(s): Cody J. Balos @ LLNL
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
 * This file implements fused stub kernels for CVODE.
 * -----------------------------------------------------------------
 */

#include "cvode_diag_impl.h"
#include "cvode_impl.h"

#define ZERO   SUN_RCONST(0.0)
#define PT1    SUN_RCONST(0.1)
#define FRACT  SUN_RCONST(0.1)
#define ONEPT5 SUN_RCONST(1.50)
#define ONE    SUN_RCONST(1.0)

/*
 * -----------------------------------------------------------------
 * Compute the ewt vector when the tol type is CV_SS.
 * -----------------------------------------------------------------
 */

int cvEwtSetSS_fused(const sunbooleantype atolmin0, const sunrealtype reltol,
                     const sunrealtype Sabstol, const N_Vector ycur,
                     N_Vector tempv, N_Vector weight)
{
  SUNAssignSUNCTX(ycur->sunctx);
  SUNCheckCallLastErrNoRet(N_VAbs(ycur, tempv));
  SUNCheckCallLastErrNoRet(N_VScale(reltol, tempv, tempv));
  SUNCheckCallLastErrNoRet(N_VAddConst(tempv, Sabstol, tempv));
  if (atolmin0)
  {
    sunrealtype min = SUNCheckCallLastErrNoRet(N_VMin(tempv));
    if (min <= ZERO) { return (-1); }
  }
  SUNCheckCallLastErrNoRet(N_VInv(tempv, weight));
  return 0;
}

/*
 * -----------------------------------------------------------------
 * Compute the ewt vector when the tol type is CV_SV.
 * -----------------------------------------------------------------
 */

int cvEwtSetSV_fused(const sunbooleantype atolmin0, const sunrealtype reltol,
                     const N_Vector Vabstol, const N_Vector ycur,
                     N_Vector tempv, N_Vector weight)
{
  SUNAssignSUNCTX(Vabstol->sunctx);
  SUNCheckCallLastErrNoRet(N_VAbs(ycur, tempv));
  SUNCheckCallLastErrNoRet(N_VLinearSum(reltol, tempv, ONE, Vabstol, tempv));
  if (atolmin0)
  {
    sunrealtype min = SUNCheckCallLastErrNoRet(N_VMin(tempv));
    if (min <= ZERO) { return (-1); }
  }
  SUNCheckCallLastErrNoRet(N_VInv(tempv, weight));
  return 0;
}

/*
 * -----------------------------------------------------------------
 * Determine if the constraints of the problem are satisfied by
 * the proposed step.
 * -----------------------------------------------------------------
 */

int cvCheckConstraints_fused(const N_Vector c, const N_Vector ewt,
                             const N_Vector y, const N_Vector mm, N_Vector tmp)
{
  SUNAssignSUNCTX(c->sunctx);
  SUNCheckCallLastErrNoRet(N_VCompare(ONEPT5, c, tmp)); /* a[i]=1 when |c[i]|=2  */
  SUNCheckCallLastErrNoRet(N_VProd(tmp, c, tmp));  /* a * c                 */
  SUNCheckCallLastErrNoRet(N_VDiv(tmp, ewt, tmp)); /* a * c * wt            */
  SUNCheckCallLastErrNoRet(
    N_VLinearSum(ONE, y, -PT1, tmp, tmp));         /* y - 0.1 * a * c * wt  */
  SUNCheckCallLastErrNoRet(N_VProd(tmp, mm, tmp)); /* v = mm*(y-0.1*a*c*wt) */
  return 0;
}

/*
 * -----------------------------------------------------------------
 * Compute the nonlinear residual.
 * -----------------------------------------------------------------
 */

int cvNlsResid_fused(const sunrealtype rl1, const sunrealtype ngamma,
                     const N_Vector zn1, const N_Vector ycor,
                     const N_Vector ftemp, N_Vector res)
{
  SUNAssignSUNCTX(zn1->sunctx);
  SUNCheckCallLastErrNoRet(N_VLinearSum(rl1, zn1, ONE, ycor, res));
  SUNCheckCallLastErrNoRet(N_VLinearSum(ngamma, ftemp, ONE, res, res));
  return 0;
}

/*
 * -----------------------------------------------------------------
 * Form y with perturbation = FRACT*(func. iter. correction)
 * -----------------------------------------------------------------
 */

int cvDiagSetup_formY(const sunrealtype h, const sunrealtype r, const N_Vector fpred,
                      const N_Vector zn1, const N_Vector ypred, N_Vector ftemp,
                      N_Vector y)
{
  SUNAssignSUNCTX(fpred->sunctx);
  SUNCheckCallLastErrNoRet(N_VLinearSum(h, fpred, -ONE, zn1, ftemp));
  SUNCheckCallLastErrNoRet(N_VLinearSum(r, ftemp, ONE, ypred, y));
  return 0;
}

/*
 * -----------------------------------------------------------------
 * Construct M = I - gamma*J with J = diag(deltaf_i/deltay_i)
 * protecting against deltay_i being at roundoff level.
 * -----------------------------------------------------------------
 */

int cvDiagSetup_buildM(const sunrealtype fract, const sunrealtype uround,
                       const sunrealtype h, const N_Vector ftemp,
                       const N_Vector fpred, const N_Vector ewt, N_Vector bit,
                       N_Vector bitcomp, N_Vector y, N_Vector M)
{
  SUNAssignSUNCTX(ftemp->sunctx);
  SUNCheckCallLastErrNoRet(N_VLinearSum(ONE, M, -ONE, fpred, M));
  SUNCheckCallLastErrNoRet(N_VLinearSum(FRACT, ftemp, -h, M, M));
  SUNCheckCallLastErrNoRet(N_VProd(ftemp, ewt, y));
  /* Protect against deltay_i being at roundoff level */
  SUNCheckCallLastErrNoRet(N_VCompare(uround, y, bit));
  SUNCheckCallLastErrNoRet(N_VAddConst(bit, -ONE, bitcomp));
  SUNCheckCallLastErrNoRet(N_VProd(ftemp, bit, y));
  SUNCheckCallLastErrNoRet(N_VLinearSum(FRACT, y, -ONE, bitcomp, y));
  SUNCheckCallLastErrNoRet(N_VDiv(M, y, M));
  SUNCheckCallLastErrNoRet(N_VProd(M, bit, M));
  SUNCheckCallLastErrNoRet(N_VLinearSum(ONE, M, -ONE, bitcomp, M));
  return 0;
}

/*
 * -----------------------------------------------------------------
 *  Update M with changed gamma so that M = I - gamma*J.
 * -----------------------------------------------------------------
 */

int cvDiagSolve_updateM(const sunrealtype r, N_Vector M)
{
  SUNAssignSUNCTX(M->sunctx);
  SUNCheckCallLastErrNoRet(N_VInv(M, M));
  SUNCheckCallLastErrNoRet(N_VAddConst(M, -ONE, M));
  SUNCheckCallLastErrNoRet(N_VScale(r, M, M));
  SUNCheckCallLastErrNoRet(N_VAddConst(M, ONE, M));
  return 0;
}
