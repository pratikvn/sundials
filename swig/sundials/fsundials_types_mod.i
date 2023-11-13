// ---------------------------------------------------------------
// Programmer: Seth R. Johnson @ ORNL
//             Cody J. Balos @ LLNL
// ---------------------------------------------------------------
// SUNDIALS Copyright Start
// Copyright (c) 2002-2023, Lawrence Livermore National Security
// and Southern Methodist University.
// All rights reserved.
//
// See the top-level LICENSE and NOTICE files for details.
//
// SPDX-License-Identifier: BSD-3-Clause
// SUNDIALS Copyright End
// ---------------------------------------------------------------
// Swig interface file
// ---------------------------------------------------------------

%module fsundials_types_mod

%include <stdint.i>

// Inform SWIG of the configure-provided types
#define SUNDIALS_INT64_T
#define SUNDIALS_INDEX_TYPE int64_t
#define SUNDIALS_DOUBLE_PRECISION
#define sunbooleantype int

// Handle MPI_Comm and SUNComm
%include <typemaps.i>

%apply int { MPI_Comm };

%typemap(ftype) MPI_Comm
   "integer"
%typemap(fin, noblock=1) MPI_Comm {
    $1 = int($input, C_INT)
}
%typemap(fout, noblock=1) MPI_Comm {
    $result = int($1)
}

%typemap(in, noblock=1) MPI_Comm {
%#if SUNDIALS_MPI_ENABLED
    int flag = 0;
    MPI_Initialized(&flag);
    if(flag) {
      $1 = MPI_Comm_f2c(%static_cast(*$input, MPI_Fint));
    } else {
      $1 = SUN_COMM_NULL;
    }
%#else
    $1 = *$input;
%#endif
}
%typemap(out, noblock=1) MPI_Comm {
%#if SUNDIALS_MPI_ENABLED
    if ($1 != SUN_COMM_NULL) {
      $result = %static_cast(MPI_Comm_c2f($1), int);
    }
%#else
    $result = $1;
%#endif
}

%apply MPI_Comm { SUNComm };


// Insert code into the C wrapper to check that the sizes match
%{
#include "sundials/sundials_types.h"

#ifndef SUNDIALS_DOUBLE_PRECISION
#error "The Fortran bindings are only targeted at double-precision"
#endif

#ifndef SUNDIALS_INT64_T
#error "The Fortran bindings are only targeted at 64-bit indices"
#endif
%}

// Process and wrap functions in the following files
%include "sundials/sundials_types.h"

