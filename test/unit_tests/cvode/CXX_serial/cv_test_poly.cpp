/* -----------------------------------------------------------------------------
 * Programmer(s): David J. Gardner @ LLNL
 * -----------------------------------------------------------------------------
 * SUNDIALS Copyright Start
 * Copyright (c) 2002-2023, Lawrence Livermore National Security
 * and Southern Methodist University.
 * All rights reserved.
 *
 * See the top-level LICENSE and NOTICE files for details.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * SUNDIALS Copyright End
 * -----------------------------------------------------------------------------
 * Polynomial resizing test problem
 * ---------------------------------------------------------------------------*/

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

#include <cvode/cvode.h>
#include <nvector/nvector_serial.h>
#include <sunnonlinsol/sunnonlinsol_fixedpoint.h>

#include <cvode/cvode_impl.h>

#include "test_utilities.hpp"

#define ZERO SUN_RCONST(0.0)
#define ONE  SUN_RCONST(1.0)

#define NVAR 4
#define CPLX 2


struct UserData
{
  int power = 3;
  int steps = 0;
  int resize = 0;
};

// ODE RHS function
int ode_rhs(sunrealtype t, N_Vector y, N_Vector ydot, void* user_data)
{
  int p = (static_cast<UserData*>(user_data))->power;
  sunrealtype* data = N_VGetArrayPointer(ydot);
  for (int i = 0; i < N_VGetLocalLength(ydot); i++)
  {
    data[i] = p * std::pow(t, p - 1);
  }

  return 0;
}

// True solution
int y_true(sunrealtype t, N_Vector y, int power)
{
  sunrealtype* data = N_VGetArrayPointer(y);
  for (int i = 0; i < N_VGetLocalLength(y); i++)
  {
    data[i] = std::pow(t, power);
  }

  return 0;
}

// Update saved time and state history
int save_history(sunrealtype t_n, N_Vector y_n, sunrealtype* t_hist,
                 N_Vector* y_hist, int hist_size, int step)
{
  // Shuffle over old values
  int i_start = hist_size - 2;
  if (step < hist_size) { i_start = step - 1; }

  for (int i = i_start; i >= 0; i--)
  {
    t_hist[i + 1] = t_hist[i];
  }
  t_hist[0] = t_n;

  for (int i = i_start; i >= 0; i--)
  {
    N_VScale(ONE, y_hist[i], y_hist[i + 1]);
  }
  N_VScale(ONE, y_n, y_hist[0]);

  return 0;
}

// Resize saved state history
int resize_history(N_Vector* y_hist, int hist_size, SUNContext sunctx)
{
  // Resize and fill all history vectors
  int new_size = N_VGetLength(y_hist[0]) + 2 * NVAR * CPLX;

  for (int i = 0; i < hist_size; i++)
  {
    sunrealtype* old_data = N_VGetArrayPointer(y_hist[i]);

    N_Vector new_vec = N_VNew_Serial(new_size, sunctx);
    sunrealtype* new_data = N_VGetArrayPointer(new_vec);
    for (int j = 0; j < new_size; j++)
    {
      new_data[j] = old_data[0];
    }
    N_VDestroy(y_hist[i]);
    y_hist[i] = new_vec;
  }

  return 0;
}

int resize_vec(N_Vector v_in, N_Vector v_out, void* user_data)
{
  sunrealtype* v_in_data  = N_VGetArrayPointer(v_in);
  sunrealtype* v_out_data = N_VGetArrayPointer(v_out);

  int resize = (static_cast<UserData*>(user_data))->resize;

  // Copy value
  if (resize == 1 || resize == 2)
  {
    for (int i = 0; i < N_VGetLength(v_out); i++)
    {
      v_out_data[i] = v_in_data[0];
    }
  }
  else if (resize == 3)
  {
    int steps = (static_cast<UserData*>(user_data))->steps;
    int old_idx = 0;
    int new_idx = 0;

    // Copy above diagonal values
    for (int i = 0; i < steps * NVAR * CPLX; i++, new_idx++, old_idx++)
    {
      v_out_data[new_idx] = v_in_data[old_idx];
    }

    // Insert new value above diagonal
    for (int i = 0; i < NVAR * CPLX; i++, new_idx++)
    {
      v_out_data[new_idx] = ZERO;
    }

    // Copy diagonal
    for (int i = 0; i < NVAR * CPLX; i++, new_idx++, old_idx++)
    {
      v_out_data[new_idx] = v_in_data[old_idx];
    }

    // Insert new value below diagonal
    for (int i = 0; i < NVAR * CPLX; i++, new_idx++)
    {
      v_out_data[new_idx] = ZERO;
    }

    // Copy below diagonal values
    for (int i = 0; i < steps * NVAR * CPLX; i++, new_idx++, old_idx++)
    {
      v_out_data[new_idx] = v_in_data[old_idx];
    }
  }

  return 0;
}

// Print CVODE Nordsieck History Array
int PrintNordsieck(CVodeMem cv_mem)
{
  const sunindextype N = N_VGetLength(cv_mem->cv_zn[0]);
  sunrealtype* vdata   = nullptr;

  std::cout << std::setw(4) << "idx" << std::setw(25) << "zn" << std::endl;
  for (int i = 0; i <= cv_mem->cv_qmax; i++)
  {
    vdata = N_VGetArrayPointer(cv_mem->cv_zn[i]);
    for (sunindextype j = 0; j < N; j++)
    {
      std::cout << std::setw(4) << i << std::setw(25) << vdata[j] << std::endl;
    }
  }
  std::cout << std::endl;

  return 0;
}


// Test main
int main(int argc, char* argv[])
{
  // SUNDIALS context object for this simulation
  sundials::Context sunctx;
  UserData udata;

  // resize = 0 -- do not resize
  // resize = 1 -- call resize but with the same problem size
  // resize = 2 -- grow the problem each time step, copy vec resize
  // resize = 3 -- grow the problem each time step, zero vec resize
  int resize = 0;
  if (argc > 1)
  {
    resize = atoi(argv[1]);
    udata.resize = resize;
  }

  // power to use in polynomial
  if (argc > 2)
  {
    udata.power = atoi(argv[2]);
  }

  // 0 is only valid with resize 0 or 1
  // reuse_fn = 0 -- evaluate RHS
  // reuse_fn = 1 -- copy old z[1]
  int reuse_fn = 0;
  if (argc > 3)
  {
    if (resize > 1)
    {
      std::cerr << "reuse_fn not compatible with resize" << std::endl;
    }
    reuse_fn = atoi(argv[3]);
  }

  // Switch between BDF and ADAMS
  int method = CV_BDF;
  if (argc > 4)
  {
    if (atoi(argv[4]) == 1) { method = CV_ADAMS; }
    else if (atoi(argv[4]) == 2) { method = CV_BDF; }
    else
    {
      std::cerr << "Invalid method option" << std::endl;
      return 1;
    }
  }

  // Number of steps to take
  int max_steps = 20;
  if (argc > 5)
  {
    max_steps = atoi(argv[5]);
  }

  if (resize == 0)
  {
    std::cout << "CVODE -- NO RESIZE" << std::endl;
  }
  else
  {
    std::cout << "CVODE -- RESIZE" << std::endl;
  }

  int problem_size = 1;
  if (resize > 1) { problem_size = 3 * NVAR * CPLX; }

  // Create initial condition
  N_Vector y = N_VNew_Serial(problem_size, sunctx);
  if (check_ptr(y, "N_VNew_Serial")) { return 1; }

  int flag = y_true(ZERO, y, udata.power);
  if (check_flag(flag, "y_true")) { return 1; }

  // Create CVODE memory structure
  void* cvode_mem = CVodeCreate(CV_BDF, sunctx);
  if (check_ptr(cvode_mem, "CVodeCreate")) { return 1; }

  flag = CVodeInit(cvode_mem, ode_rhs, ZERO, y);
  if (check_flag(flag, "CVodeInit")) { return 1; }

  // Relative and absolute tolerances
  const sunrealtype rtol = SUN_RCONST(1.0e-5);
  const sunrealtype atol = SUN_RCONST(1.0e-5);

  flag = CVodeSStolerances(cvode_mem, rtol, atol);
  if (check_flag(flag, "CVodeSStolerances")) { return 1; }

  // Use fixed-point nonlinear solver
  SUNNonlinearSolver NLS = SUNNonlinSol_FixedPoint(y, 2, sunctx);
  if (check_ptr(NLS, "SUNNonlinSol_FixedPoint")) { return 1; }

  flag = CVodeSetNonlinearSolver(cvode_mem, NLS);
  if (check_flag(flag, "CVodeSetNonlinearSolver")) { return 1; }

  flag = CVodeSetMaxNonlinIters(cvode_mem, 10);
  if (check_flag(flag, "CVodeSetMaxNonlinIters")) { return 1; }

  // Attach user data
  flag = CVodeSetUserData(cvode_mem, &udata);
  if (check_flag(flag, "CVodeSetUserData")) { return 1; }

  // Limit max order
  // flag = CVodeSetMaxOrd(cvode_mem, 2);
  // if (check_flag(flag, "CVodeSetMaxOrd")) { return 1; }

  // Initial time and final times
  sunrealtype tf = SUN_RCONST(10.0);

  // History of solution times
  sunrealtype t_ret;

  // Set output formatting
  std::cout << std::scientific;
  std::cout << std::setprecision(16);
  // std::cout << std::setprecision(std::numeric_limits<sunrealtype>::digits10);
  std::cout << std::endl;

  // Access private CVODE memory to output Nordsieck array
  CVodeMem cv_mem = (CVodeMem) cvode_mem;

  int hist_size = 0;
  if (method == CV_BDF) { hist_size = 5; }
  else { hist_size = 13; }

  N_Vector* y_hist = N_VCloneVectorArray(hist_size, y);
  if (check_ptr(y_hist, "N_VCloneVectorArray") != 0) { return 1; }

  sunrealtype* t_hist = new sunrealtype[hist_size];
  for (int i = 0; i < hist_size; i++) { t_hist[i] = ZERO; }

  // Initialize saved history
  t_hist[0] = ZERO;
  N_VScale(ONE, y, y_hist[0]);

  std::string file_name = "debug_resize_" + std::to_string(resize) + ".txt";
  FILE* debug_file = std::fopen(file_name.c_str(), "w");
  // FILE* debug_file = stdout;
  // FILE* debug_file = nullptr;

  std::cout << "t:      " << ZERO << std::endl;
  std::cout << "y:      " << N_VGetArrayPointer(y)[0] << std::endl;
  std::cout << "y_true: " << N_VGetArrayPointer(y)[0] << std::endl;
  std::cout << "Error:  " << ZERO << std::endl;

  // Advance in time
  for (int i = 1; i <= max_steps; i++)
  {
    N_Vector tmp = N_VClone(y);

    std::cout << std::flush;
    std::cerr << std::flush;
    std::cout << "\n========== Start Step " << i << " ==========\n\n";

    // Print Nordsieck array (length q_max + 1)
    // PrintNordsieck(cv_mem);
    // if (check_flag(flag, "PrintNordsieck")) { return 1; }

    flag = CVode(cvode_mem, tf, y, &(t_ret), CV_ONE_STEP);
    if (check_flag(flag, "CVode")) { return 1; }

    // Update number of completed steps
    udata.steps++;

    std::cout << " Step Number: " << std::setw(3) << i
              << " | Time: " << std::setw(21) << t_ret
              << " | Step Size: " << std::setw(21) << cv_mem->cv_h
              << " | Order: " << cv_mem->cv_q << std::endl;

    // Print Nordsieck array (length q_max + 1)
    // PrintNordsieck(cv_mem);
    // if (check_flag(flag, "PrintNordsieck")) { return 1; }

    std::cout << "t:      " << t_ret << std::endl;
    std::cout << "y:      " << N_VGetArrayPointer(y)[0] << std::endl;

    flag = y_true(t_ret, tmp, udata.power);
    if (check_flag(flag, "y_true")) { return 1; }
    std::cout << "y_true: " << N_VGetArrayPointer(tmp)[0] << std::endl;

    N_VLinearSum(ONE, y, -ONE, tmp, tmp);
    std::cout << "Error:  " << N_VMaxNorm(tmp) << std::endl;

    std::cout << "========== End Step " << i << " ==========\n";

    if (resize == 1)
    {
      // Save history but do not update problem size
      flag = save_history(t_ret, y, t_hist, y_hist, hist_size, i);

      int n_hist = (i < hist_size) ? i + 1 : hist_size;

      if (reuse_fn)
      {
        N_VScale(ONE / cv_mem->cv_hscale, cv_mem->cv_zn[1], tmp);
        flag = CVodeResizeHistory(cvode_mem, t_hist, y_hist, &tmp, n_hist,
                                  resize_vec, debug_file);
      }
      else
      {
        flag = CVodeResizeHistory(cvode_mem, t_hist, y_hist, nullptr, n_hist,
                                  resize_vec, debug_file);
      }
      if (check_flag(flag, "CVodeResizeHistory")) { return 1; }
    }
    else if (resize == 2 || resize == 3)
    {
      // Save history and update problem size
      flag = save_history(t_ret, y, t_hist, y_hist, hist_size, i);

      flag = resize_history(y_hist, hist_size, sunctx);

      int n_hist = (i < hist_size) ? i + 1 : hist_size;
      flag = CVodeResizeHistory(cvode_mem, t_hist, y_hist, nullptr, n_hist,
                                resize_vec, debug_file);
      if (check_flag(flag, "CVodeResizeHistory")) { return 1; }

      // "Resize" vectors and nonlinear solver
      N_VDestroy(y);
      y = N_VClone(y_hist[0]);

      SUNNonlinSolFree(NLS);
      NLS = SUNNonlinSol_FixedPoint(y, 2, sunctx);
      if (check_ptr(NLS, "SUNNonlinSol_FixedPoint")) { return 1; }

      flag = CVodeSetNonlinearSolver(cvode_mem, NLS);
      if (check_flag(flag, "CVodeSetNonlinearSolver")) { return 1; }

      flag = CVodeSetMaxNonlinIters(cvode_mem, 10);
      if (check_flag(flag, "CVodeSetMaxNonlinIters")) { return 1; }
    }

    N_VDestroy(tmp);
  }
  std::cout << std::endl;

  if (debug_file) { std::fclose(debug_file); }

  // Print some final statistics
  flag = CVodePrintAllStats(cvode_mem, stdout, SUN_OUTPUTFORMAT_TABLE);
  if (check_flag(flag, "CVodePrintAllStats")) { return 1; }

  // Clean up and return with successful completion
  N_VDestroy(y);
  N_VDestroyVectorArray(y_hist, hist_size);
  SUNNonlinSolFree(NLS);
  CVodeFree(&cvode_mem);
  delete [] t_hist;

  return 0;
}

/*---- end of file ----*/