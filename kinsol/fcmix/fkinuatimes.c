/******************************************************************
 *                                                                *
 * File          : fkinuatimes.c                                  *
 * Programmers   : Allan G Taylor, Alan C. Hindmarsh, and         *
 *                 Radu Serban @ LLNL                             *
 * Version of    : 29 July 2002                                   *
 *----------------------------------------------------------------*
 * Routine used to interface between KINSOL and a Fortran         *
 * user-supplied routine FATIMES (Jacobian A times vector v).     *
 ******************************************************************/

#include "kinsol.h"  /* prototypes of interfaces, global variables  */
#include "fkinsol.h" /* prototypes of interfaces, global variables  */

/* Prototype of the user-supplied Fortran routine */
void F_ATIMES(realtype*, realtype*, int*, realtype*, int*);

/**************************************************************************
 *  C function KINUAtimes is to interface between KINSpgmr/KINSpgmrATimes *
 *  and FATIMES, the user-supplied Fortran ATimes routine FATIMES.        *
 **************************************************************************/

int KINUAtimes(void *f_data, N_Vector v, N_Vector z,
               booleantype *new_uu,  N_Vector uu)
{
 int retcode;
 realtype *vdata, *zdata, *uudata;
 
 vdata      = N_VGetData(v);
 zdata      = N_VGetData(z);
 uudata     = N_VGetData(uu);
 
 F_ATIMES(vdata, zdata, (int *)new_uu, uudata, &retcode);

 N_VSetData(zdata, z);

 return(retcode);
}
