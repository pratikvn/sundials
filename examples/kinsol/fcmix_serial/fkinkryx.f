      program fkinkryx
c     ----------------------------------------------------------------
c     $Revision: 1.1 $
c     $Date: 2006-07-05 15:50:10 $
c     ----------------------------------------------------------------
c     Programmer(s): Allan Taylor, Alan Hindmarsh and
c                    Radu Serban @ LLNL  
c     ----------------------------------------------------------------
c     Simple diagonal test with Fortran interface, using user-supplied
c     preconditioner setup and solve routines (supplied in Fortran).
c
c     This example does a basic test of the solver by solving the
c     system:
c               f(u) = 0  for
c               f(u) = u(i)^2 - i^2
c
c     No scaling is done.
c     An approximate diagonal preconditioner is used.
c
c     Execution command: fkinkryx
c     ----------------------------------------------------------------
c
      implicit none

      integer ier, globalstrat, maxl, maxlrst
      integer*4 PROBSIZE
      parameter(PROBSIZE=128)
      integer*4 neq, i, msbpre
      integer*4 iout(15)
      double precision pp, fnormtol, scsteptol
      double precision rout(2), uu(PROBSIZE), scale(PROBSIZE)
      double precision constr(PROBSIZE)

      common /pcom/ pp(PROBSIZE)
      common /psize/ neq

      neq = PROBSIZE
      globalstrat = 0
      fnormtol = 1.0d-5
      scsteptol = 1.0d-4
      maxl = 10
      maxlrst = 2
      msbpre  = 5

c * * * * * * * * * * * * * * * * * * * * * *

      call fnvinits(3, neq, ier)
      if (ier .ne. 0) then
         write(6,1220) ier
 1220    format('SUNDIALS_ERROR: FNVINITS returned IER = ', i2)
         stop
      endif

      do 20 i = 1, neq
         uu(i) = 2.0d0 * i
         scale(i) = 1.0d0
         constr(i) = 0.0d0
  20  continue

      call fkinmalloc(iout, rout, ier)
      if (ier .ne. 0) then
         write(6,1230) ier
 1230    format('SUNDIALS_ERROR: FKINMALLOC returned IER = ', i2)
         stop
      endif

      call fkinsetiin('MAX_SETUPS', msbpre, ier)
      call fkinsetrin('FNORM_TOL', fnormtol, ier)
      call fkinsetrin('SSTEP_TOL', scsteptol, ier)
      call fkinsetvin('CONSTR_VEC', constr, ier)

      call fkinspgmr(maxl, maxlrst, ier)
      if (ier .ne. 0) then
         write(6,1235) ier
 1235    format('SUNDIALS_ERROR: FKINSPGMR returned IER = ', i2)
         call fkinfree
         stop
      endif

      call fkinspilssetprec(1, ier)

      write(6,1240)
 1240 format('Example program fkinkryx:'//' This fkinsol example code',
     1       ' solves a 128 eqn diagonal algebraic system.'/
     2       ' Its purpose is to demonstrate the use of the Fortran',
     3       ' interface'/' in a serial environment.'///
     4       ' globalstrategy = KIN_NONE')

      call fkinsol(uu, globalstrat, scale, scale, ier)
      if (ier .lt. 0) then
         write(6,1242) ier, iout(9)
 1242    format('SUNDIALS_ERROR: FKINSOL returned IER = ', i2, /,
     1          '                Linear Solver returned IER = ', i2)
         call fkinfree
         stop
      endif

      write(6,1245) ier
 1245 format(/' FKINSOL return code is ', i3)

      write(6,1246)
 1246 format(//' The resultant values of uu are:'/)

      do 30 i = 1, neq, 4
         write(6,1256) i, uu(i), uu(i+1), uu(i+2), uu(i+3)
 1256    format(i4, 4(1x, f10.6))
 30   continue

      write(6,1267) iout(3), iout(14), iout(4), iout(12), iout(13),
     1              iout(15)
 1267 format(//'Final statistics:'//
     1     '  nni = ', i3, ',  nli  = ', i3, /,
     2     '  nfe = ', i3, ',  npe  = ', i3, /,
     3     '  nps = ', i3, ',  ncfl = ', i3)

      call fkinfree

      stop
      end
      
c * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
c     The function defining the system f(u) = 0 must be defined by a Fortran
c     function of the following form.
      
      subroutine fkfun(uu, fval, ier)

      implicit none

      integer ier
      integer*4 neq, i
      double precision fval(*), uu(*)

      common /psize/ neq

      do 10 i = 1, neq
         fval(i) = uu(i) * uu(i) - i * i
 10   continue

      ier = 0

      return
      end
      
      
c * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
c     The routine kpreco is the preconditioner setup routine. It must have
c     that specific name be used in order that the c code can find and link
c     to it.  The argument list must also be as illustrated below:
      
      subroutine fkpset(udata, uscale, fdata, fscale, 
     1                  vtemp1, vtemp2, ier)

      implicit none

      integer ier
      integer*4 neq, i
      double precision pp
      double precision udata(*), uscale(*), fdata(*), fscale(*)
      double precision vtemp1(*), vtemp2(*)

      common /pcom/ pp(128)
      common /psize/ neq

      do 10 i = 1, neq
         pp(i) = 0.5d0 / (udata(i) + 5.0d0)
 10   continue
      ier = 0
      
      return
      end
      
      
c * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
c     The routine kpsol is the preconditioner solve routine. It must have
c     that specific name be used in order that the c code can find and link
c     to it.  The argument list must also be as illustrated below:
      
      subroutine fkpsol(udata, uscale, fdata, fscale, 
     1                  vv, ftem, ier)

      implicit none

      integer ier
      integer*4 neq, i
      double precision pp
      double precision udata(*), uscale(*), fdata(*), fscale(*)
      double precision vv(*), ftem(*)

      common /pcom/ pp(128)
      common /psize/ neq

      do 10 i = 1, neq
         vv(i) = vv(i) * pp(i)
 10   continue
      ier = 0
      
      return
      end
