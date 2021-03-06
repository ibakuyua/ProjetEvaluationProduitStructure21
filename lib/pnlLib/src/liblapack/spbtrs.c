/* spbtrs.f -- translated by f2c (version 20061008).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "pnl/pnl_f2c.h"

/* Table of constant values */

static int c__1 = 1;

 int spbtrs_(char *uplo, int *n, int *kd, int *
	nrhs, float *ab, int *ldab, float *b, int *ldb, int *info)
{
    /* System generated locals */
    int ab_dim1, ab_offset, b_dim1, b_offset, i__1;

    /* Local variables */
    int j;
    extern int lsame_(char *, char *);
    int upper;
    extern  int stbsv_(char *, char *, char *, int *, 
	    int *, float *, int *, float *, int *), xerbla_(char *, int *);


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  SPBTRS solves a system of linear equations A*X = B with a symmetric */
/*  positive definite band matrix A using the Cholesky factorization */
/*  A = U**T*U or A = L*L**T computed by SPBTRF. */

/*  Arguments */
/*  ========= */

/*  UPLO    (input) CHARACTER*1 */
/*          = 'U':  Upper triangular factor stored in AB; */
/*          = 'L':  Lower triangular factor stored in AB. */

/*  N       (input) INTEGER */
/*          The order of the matrix A.  N >= 0. */

/*  KD      (input) INTEGER */
/*          The number of superdiagonals of the matrix A if UPLO = 'U', */
/*          or the number of subdiagonals if UPLO = 'L'.  KD >= 0. */

/*  NRHS    (input) INTEGER */
/*          The number of right hand sides, i.e., the number of columns */
/*          of the matrix B.  NRHS >= 0. */

/*  AB      (input) REAL array, dimension (LDAB,N) */
/*          The triangular factor U or L from the Cholesky factorization */
/*          A = U**T*U or A = L*L**T of the band matrix A, stored in the */
/*          first KD+1 rows of the array.  The j-th column of U or L is */
/*          stored in the j-th column of the array AB as follows: */
/*          if UPLO ='U', AB(kd+1+i-j,j) = U(i,j) for MAX(1,j-kd)<=i<=j; */
/*          if UPLO ='L', AB(1+i-j,j)    = L(i,j) for j<=i<=MIN(n,j+kd). */

/*  LDAB    (input) INTEGER */
/*          The leading dimension of the array AB.  LDAB >= KD+1. */

/*  B       (input/output) REAL array, dimension (LDB,NRHS) */
/*          On entry, the right hand side matrix B. */
/*          On exit, the solution matrix X. */

/*  LDB     (input) INTEGER */
/*          The leading dimension of the array B.  LDB >= MAX(1,N). */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value */

/*  ===================================================================== */

/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input parameters. */

    /* Parameter adjustments */
    ab_dim1 = *ldab;
    ab_offset = 1 + ab_dim1;
    ab -= ab_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;

    /* Function Body */
    *info = 0;
    upper = lsame_(uplo, "U");
    if (! upper && ! lsame_(uplo, "L")) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*kd < 0) {
	*info = -3;
    } else if (*nrhs < 0) {
	*info = -4;
    } else if (*ldab < *kd + 1) {
	*info = -6;
    } else if (*ldb < MAX(1,*n)) {
	*info = -8;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("SPBTRS", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*n == 0 || *nrhs == 0) {
	return 0;
    }

    if (upper) {

/*        Solve A*X = B where A = U'*U. */

	i__1 = *nrhs;
	for (j = 1; j <= i__1; ++j) {

/*           Solve U'*X = B, overwriting B with X. */

	    stbsv_("Upper", "Transpose", "Non-unit", n, kd, &ab[ab_offset], 
		    ldab, &b[j * b_dim1 + 1], &c__1);

/*           Solve U*X = B, overwriting B with X. */

	    stbsv_("Upper", "No transpose", "Non-unit", n, kd, &ab[ab_offset], 
		     ldab, &b[j * b_dim1 + 1], &c__1);
/* L10: */
	}
    } else {

/*        Solve A*X = B where A = L*L'. */

	i__1 = *nrhs;
	for (j = 1; j <= i__1; ++j) {

/*           Solve L*X = B, overwriting B with X. */

	    stbsv_("Lower", "No transpose", "Non-unit", n, kd, &ab[ab_offset], 
		     ldab, &b[j * b_dim1 + 1], &c__1);

/*           Solve L'*X = B, overwriting B with X. */

	    stbsv_("Lower", "Transpose", "Non-unit", n, kd, &ab[ab_offset], 
		    ldab, &b[j * b_dim1 + 1], &c__1);
/* L20: */
	}
    }

    return 0;

/*     End of SPBTRS */

} /* spbtrs_ */
