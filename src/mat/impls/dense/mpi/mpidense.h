/* $Id: mpidense.h,v 1.14 1999/03/25 21:33:16 balay Exp bsmith $ */

#include "src/mat/impls/dense/seq/dense.h"

  /*  Data stuctures for basic parallel dense matrix  */

/* Structure to hold the information for factorization of a dense matrix */
/* Most of this info is used in the pipe send/recv routines */
typedef struct {
  int    nlnr;        /* number of local rows downstream */
  int    nrend;       /* rend for downstream processor */
  int    nbr, pnbr;   /* Down and upstream neighbors */
  int    *tag;        /* message tags */
  int    currow;      /* current row number */
  int    phase;       /* phase (used to indicate tag) */
  int    up;          /* Are we moving up or down in row number? */
  int    use_bcast;   /* Are we broadcasting max length? */
  int    nsend;       /* number of sends */
  int    nrecv;       /* number of receives */

  /* data initially in matrix context */
  int    k;           /* Blocking factor (unused as yet) */
  int    k2;          /* Blocking factor for solves */
  Scalar *temp;
  int    nlptr;
  int    *lrows;
  int    *nlrows;
  int    *pivots;
} FactorCtx;

#define PIPEPHASE (ctx->phase == 0)

typedef struct {
  int           *rowners, *cowners;     /* ranges owned by each processor */
  int           m, n;                   /* local rows and columns */
  int           M, N;                   /* global rows and columns */
                                        /* note n == N */
  int           nvec;                   /* this is the n size for the vector one multiplies with */
  int           rstart, rend;           /* starting and ending owned rows */
  Mat           A;                      /* local submatrix */
  int           size;                   /* size of communicator */
  int           rank;                   /* rank of proc in communicator */ 
  /* The following variables are used for matrix assembly */
  int           donotstash;             /* Flag indicationg if values should be stashed */
  MPI_Request   *send_waits;            /* array of send requests */
  MPI_Request   *recv_waits;            /* array of receive requests */
  int           nsends, nrecvs;         /* numbers of sends and receives */
  Scalar        *svalues, *rvalues;     /* sending and receiving data */
  int           rmax;                   /* maximum message length */

  /* The following variables are used for matrix-vector products */

  Vec           lvec;                   /* local vector */
  VecScatter    Mvctx;                  /* scatter context for vector */

  int           roworiented;            /* if true, row oriented input (default) */
  FactorCtx     *factor;                /* factorization context */
} Mat_MPIDense;
