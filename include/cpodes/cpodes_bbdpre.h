/*
 * -----------------------------------------------------------------
 * $Revision$
 * $Date$
 * ----------------------------------------------------------------- 
 * Programmer: Radu Serban @ LLNL
 * -----------------------------------------------------------------
 * LLNS Copyright Start
 * Copyright (c) 2014, Lawrence Livermore National Security
 * This work was performed under the auspices of the U.S. Department 
 * of Energy by Lawrence Livermore National Laboratory in part under 
 * Contract W-7405-Eng-48 and in part under Contract DE-AC52-07NA27344.
 * Produced at the Lawrence Livermore National Laboratory.
 * All rights reserved.
 * For details, see the LICENSE file.
 * LLNS Copyright End
 * -----------------------------------------------------------------
 * This is the header file for the CPBBDPRE module, for a
 * band-block-diagonal preconditioner, i.e. a block-diagonal
 * matrix with banded blocks, for use with one of the CPSPILS
 * linear solvers and the parallel implementation of the NVECTOR 
 * module.
 *
 * Summary:
 *
 * These routines provide a preconditioner matrix that is
 * block-diagonal with banded blocks. The blocking corresponds to the
 * distribution of the dependent variable vector y among the processors. 
 * Each preconditioner block is generated from the Jacobian of the local 
 * part (on the current processor) of a given function g(t,y) approximating 
 * f(t,y) (for explicit-form ODEs) or G(t,y,y') approximating F(t,y,y') 
 * (for implicit-form ODEs). The blocks are generated by a difference 
 * quotient scheme on each processor independently. This scheme utilizes 
 * an assumed banded structure with given half-bandwidths, mudq and mldq.
 * However, the banded Jacobian block kept by the scheme has half-bandwiths 
 * mukeep and mlkeep, which may be smaller.
 *
 * The user's calling program should have the following form:
 *
 *   #include <nvector_parallel.h>
 *   #include <cpodes/cpodes_bbdpre.h>
 *   ...
 *   void *cpode_mem;
 *   void *bbd_data;
 *   ...
 *   Set y0
 *   ...
 *   cpode_mem = CPodeCreate(...);
 *   ier = CPodeMalloc(...);
 *   ...
 *   flag = CPSpgmr(cpode_mem, pretype, maxl);
 *      -or-
 *   flag = CPSpbcg(cpode_mem, pretype, maxl);
 *      -or-
 *   flag = CPSptfqmr(cpode_mem, pretype, maxl);
 *   ...
 *   flag = CPBBDPrecInit(cpode_mem, Nlocal, mudq ,mldq,
 *                        mukeep, mlkeep, dqrely, gloc, cfn);
 *   ...                                                           
 *   CPodeFree(...);
 * 
 *   Free y0
 *
 * The user-supplied routines required are:
 *
 *   f or F - function defining the ODE right-hand side f(t,y)
 *            or the ODE residual F(t,y,y')
 *
 *   gloc or Gloc - function defining the approximation g(t,y)
 *                  or G(t,y,y')
 *
 *   cfn  - function to perform communication need for gloc.
 *
 * Notes:
 *
 * 1) This header file is included by the user for the definition
 *    of the CPBBDData type and for needed function prototypes.
 *
 * 2) The CPBBDPrecAlloc call includes half-bandwiths mudq and mldq
 *    to be used in the difference quotient calculation of the
 *    approximate Jacobian. They need not be the true
 *    half-bandwidths of the Jacobian of the local block of g,
 *    when smaller values may provide a greater efficiency.
 *    Also, the half-bandwidths mukeep and mlkeep of the retained
 *    banded approximate Jacobian block may be even smaller,
 *    to reduce storage and computation costs further.
 *    For all four half-bandwidths, the values need not be the
 *    same on every processor.
 *
 * 3) The actual name of the user's f (or F) function is passed to
 *    CPodeInitExpl or CPodeInitImpl, respectively, and the names 
 *    of the user's gloc (or Gloc) and cfn functions are passed to
 *    CPBBDPrecInit.
 *
 * 4) The pointer to the user-defined data block f_data, which is
 *    set through CPodeSetFdata is also available to the user in
 *    gloc/Gloc and cfn.
 *
 * 5) Optional outputs specific to this module are available by
 *    way of routines listed below. These include work space sizes
 *    and the cumulative number of gloc calls. The costs
 *    associated with this module also include nsetups banded LU
 *    factorizations, nlinsetups cfn calls, and npsolves banded
 *    backsolve calls, where nlinsetups and npsolves are
 *    integrator/CPSPGMR/CPSPBCG/CPSPTFQMR optional outputs.
 * -----------------------------------------------------------------
 */

#ifndef _CPBBDPRE_H
#define _CPBBDPRE_H

#include <sundials/sundials_nvector.h>

#ifdef __cplusplus  /* wrapper to enable C++ usage */
extern "C" {
#endif

/*
 * -----------------------------------------------------------------
 * Types: CPBBDLocalRhsFn and CPBBDLocalResFn
 * -----------------------------------------------------------------
 *
 * For ODEs in explicit form, i.e., y' = f(t,y), the user must 
 * supply a function g(t,y) which approximates the right-hand side 
 * function f for the system y'=f(t,y), and which is computed locally 
 * (without interprocess communication). The case where g is 
 * mathematically identical to f is allowed. The implementation of 
 * this function must have type CPBBDLocalRhsFn.
 *
 * This function takes as input the local vector size Nlocal, the
 * independent variable value t, the local real dependent variable
 * vector y, and a pointer to the user-defined data block f_data. 
 * It is to compute the local part of g(t,y) and store this in the 
 * vector gout. Allocation of memory for y and g is handled within
 * the preconditioner module. The f_data parameter is the same as
 * that specified by the user through the CPodeSetFdata routine.
 *
 * A CPBBDLocalRhsFn should return 0 if successful, a positive value
 * if a recoverable error occurred, and a negative value if an 
 * unrecoverable error occurred.
 *
 * -----------------------------------------------------------------
 *
 * For ODEs in implicit form, the user must supply a function 
 * G(t,y,y') which approximates the function F for the system 
 * F(t,y,y') = 0, and which is computed locally (without interprocess 
 * communication. The case where G is mathematically identical to F 
 * is allowed. The implementation of this function must have type 
 * CPBBDLocalResFn.
 *
 * This function takes as input the independent variable value t,
 * the current solution vector y, the current solution derivative 
 * vector yp, and a pointer to the user-defined data block f_data. 
 * It is to compute the local part of G(t,y,y') and store it in the 
 * vector gout. Providing memory for y, yp, and gout is handled within 
 * this preconditioner module. It is expected that this routine will 
 * save communicated data in work space defined by the user and made 
 * available to the preconditioner function for the problem. The f_data
 * parameter is the same as that passed by the user to the CPodeSetFdata
 * routine.
 *
 * A CPBBDLocalResFn Gres is to return an int, defined in the same
 * way as for the residual function: 0 (success), +1 or -1 (fail).
 * -----------------------------------------------------------------
 */

typedef int (*CPBBDLocalRhsFn)(int Nlocal, realtype t, 
			       N_Vector y,
			       N_Vector gout, void *user_data);

typedef int (*CPBBDLocalResFn)(int Nlocal, realtype t, 
			       N_Vector y, N_Vector yp, 
			       N_Vector gout, void *user_data);

/*
 * -----------------------------------------------------------------
 * Type: CPBBDCommFn
 * -----------------------------------------------------------------
 * The user may supply a function of type CPBBDCommFn which performs
 * all interprocess communication necessary to evaluate the
 * approximate right-hand side function described above.
 *
 * This function takes as input the local vector size Nlocal,
 * the independent variable value t, the dependent variable
 * vector y, and a pointer to the user-defined data block user_data.
 * The user_data parameter is the same as that specified by the user
 * through the CPodeSetUserData routine. A CPBBDCommFn cfn is
 * expected to save communicated data in space defined within the
 * structure user_data. A CPBBDCommFn cfn does not have a return value.
 *
 * Each call to the CPBBDCommFn cfn is preceded by a call to the
 * CPRhsFn f (or CPResFn F) with the same (t, y, y') arguments 
 * (where y'=NULL for explicit-form ODEs). Thus cfn can omit any 
 * communications done by f (or F) if relevant to the evaluation of 
 * the local approximation. If all necessary communication was done 
 * by f (respectively F), the user can pass NULL for cfn in 
 * CPBBDPrecAlloc (see below).
 *
 * A CPBBDCommFn should return 0 if successful, a positive value if 
 * a recoverable error occurred, and a negative value if an 
 * unrecoverable error occurred.
 * -----------------------------------------------------------------
 */

typedef int (*CPBBDCommFn)(int Nlocal, realtype t, 
			   N_Vector y, N_Vector yp, void *user_data);


/*
 * -----------------------------------------------------------------
 * Function : CPBBDPrecInit
 * -----------------------------------------------------------------
 * CPBBDPrecInit allocates and initializes the BBD preconditioner.
 *
 * The parameters of CPBBDPrecInit are as follows:
 *
 * cpode_mem is the pointer to the integrator memory.
 *
 * Nlocal is the length of the local block of the vectors y etc.
 *        on the current processor.
 *
 * mudq, mldq are the upper and lower half-bandwidths to be used
 *            in the difference quotient computation of the local
 *            Jacobian block.
 *
 * mukeep, mlkeep are the upper and lower half-bandwidths of the
 *                retained banded approximation to the local Jacobian
 *                block.
 *
 * dqrely is an optional input. It is the relative increment
 *        in components of y used in the difference quotient
 *        approximations. To specify the default, pass 0.
 *        The default is dqrely = sqrt(unit roundoff).
 *
 * gloc is the name of the user-supplied function g(t,y) that
 *      approximates f and whose local Jacobian blocks are
 *      to form the preconditioner.
 *
 * cfn is the name of the user-defined function that performs
 *     necessary interprocess communication for the
 *     execution of gloc.
 *
 * The return value of CPBBDPrecInit is one of:
 *   CPSPILS_SUCCESS if no errors occurred
 *   CPSPILS_MEM_NULL if the integrator memory is NULL
 *   CPSPILS_LMEM_NULL if the linear solver memory is NULL
 *   CPSPILS_ILL_INPUT if an input has an illegal value
 *   CPSPILS_MEM_FAIL if a memory allocation request failed
 * -----------------------------------------------------------------
 */

SUNDIALS_EXPORT int CPBBDPrecInit(void *cpode_mem, int Nlocal, 
                                  int mudq, int mldq, 
                                  int mukeep, int mlkeep, 
                                  realtype dqrely,
                                  void *gloc, CPBBDCommFn cfn);

/*
 * -----------------------------------------------------------------
 * Function : CPBBDPrecReInit
 * -----------------------------------------------------------------
 * CPBBDPrecReInit re-initializes the BBDPRE module when solving a
 * sequence of problems of the same size with CPSPGMR/CPBBDPRE or
 * CPSPBCG/CPBBDPRE or CPSPTFQMR/CPBBDPRE provided there is no change 
 * in Nlocal, mukeep, or mlkeep. After solving one problem, and after 
 * calling CPodeReInit to re-initialize the integrator for a subsequent 
 * problem, call CPBBDPrecReInit.
 *
 * All arguments have the same names and meanings as those
 * of CPBBDPrecInit.
 *
 * The return value of CPBBDPrecReInit is one of:
 *   CPSPILS_SUCCESS if no errors occurred
 *   CPSPILS_MEM_NULL if the integrator memory is NULL
 *   CPSPILS_LMEM_NULL if the linear solver memory is NULL
 *   CPSPILS_PMEM_NULL if the preconditioner memory is NULL
 * -----------------------------------------------------------------
 */

SUNDIALS_EXPORT int CPBBDPrecReInit(void *cpode_mem, int mudq, int mldq,
				    realtype dqrely);

/*
 * -----------------------------------------------------------------
 * BBDPRE optional output extraction routines
 * -----------------------------------------------------------------
 * CPBBDPrecGetWorkSpace returns the BBDPRE real and integer work space
 *                       sizes.
 * CPBBDPrecGetNumGfnEvals returns the number of calls to gfn.
 *
 * The return value of CPBBDPrecGet* is one of:
 *   CPSPILS_SUCCESS if no errors occurred
 *   CPSPILS_MEM_NULL if the integrator memory is NULL
 *   CPSPILS_LMEM_NULL if the linear solver memory is NULL
 *   CPSPILS_PMEM_NULL if the preconditioner memory is NULL
 * -----------------------------------------------------------------
 */

SUNDIALS_EXPORT int CPBBDPrecGetWorkSpace(void *cpode_mem, indextype *lenrwLS, indextype *leniwLS);
SUNDIALS_EXPORT int CPBBDPrecGetNumGfnEvals(void *cpode_mem, indextype *ngevalsBBDP);


#ifdef __cplusplus
}
#endif

#endif
