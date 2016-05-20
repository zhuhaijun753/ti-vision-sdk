#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <vcop.h>
#include "../inc/merge_sort.h"
#include "merge_sort_kernel.h"
#include "../inc/merge_sort_kernel_hard.h"

#if !(VCOP_HOST_EMULATION)

int32_t mergeSort_init(void *bufa, void *bufb, void *output, uint32_t n, SortContext *c) {

    int32_t merge_size, comp_dist, input_mode;
    int32_t *ptr_i, *ptr_o;
    int32_t nsteps;
    int32_t itransp;      // 0 = normal, 1 = transposed, 2 = stride-9
    int32_t otransp;      // same encoding as itransp
    uint32_t     diff;

    int32_t status=0;
    /*-----------------------------------------------------------------------*/
    /*                    SIMD block sort                                    */
    /*  Sort each 8x8-elem block, if we only have 1 block, ie 64 elements    */
    /*  set "otransp" or output transpose flag to be 1.                      */
    /*-----------------------------------------------------------------------*/

    otransp = (n==64) ? 1 : 0;
    vcop_sort8_simd8(n/64, otransp, (int32_t*)bufa, (int32_t*)bufb, c);

    /*-----------------------------------------------------------------------*/
    /*                     SIMD merge                                        */
    /* merge n/128x(8x8 + 8x8), n/64x(16x8 + 16x8), ..., 1x(n/16x8 + n/16x8) */
    /**** merge_size = 16x8, 32x8, ..., n/8 x 8                              */
    /**** for each merge_size, comp_dist = merge_size/2, merge_size/4 ... 8  */
    /**** very last step has output transposed                               */
    /*-----------------------------------------------------------------------*/

    ptr_i = (int32_t*)bufb;
    ptr_o = (int32_t*)bufa;
    merge_size = 16*8;
    itransp = otransp;

    while (merge_size <= n) /* n=64: nothing to do, n=128: 1 stage, etc  */
    {
        comp_dist = merge_size / 2;

        while (comp_dist >= 8)
        {
            input_mode = (comp_dist == merge_size/2);
            /* mirror rows 1st step of each merge_size */
            otransp = ((merge_size == n) && (comp_dist <= 32)) ? 1 : 0;
            /* only last call */
            nsteps = (comp_dist == 8)  ? 1 :              /* run 3 steps when we can */
                    ((comp_dist == 16) ? 2 : 3);

            status= bitonic_merge_multi_step(n, comp_dist, nsteps, input_mode,
                    itransp, otransp, ptr_i, ptr_o, c);

            if (status== -1)
                goto exit;

            swap_ptr(&ptr_i, &ptr_o);
            comp_dist = (nsteps == 1) ? comp_dist/2 :
                    ((nsteps == 2) ? comp_dist/4 : comp_dist/8);
        }

        merge_size *= 2;
    }

    /*-----------------------------------------------------------------------*/
    /*                Inter-SIMD-lane merge                                  */
    /**** merge 4x(n/8 + n/8), 2x(n/4 + n/4), 1x(n/2 + n/2)                  */
    /**** merge_size = n/4, n/2, n                                           */
    /**** for each merge_size, comp_dist = merge_size/2, merge_size/4 ...  1 */
    /**** array transposed when comp_dist = merge_size/2 ... 8               */
    /**** array stored with stride-9  when comp_dist = 4, 2, 1               */
    /*-----------------------------------------------------------------------*/

    merge_size = n/4;

    while (merge_size <= n) /* always 3 stages as long as n >= 64 */
    {
        comp_dist = merge_size / 2;

        while (comp_dist >= 8) /* operate up to comp_dist = 8, then transpose */
        {
            input_mode = (comp_dist == merge_size/2) ? 2 : 0;
            /* mirror points 1st step of each merge_size */
            itransp = otransp;
            nsteps = (comp_dist == 8)  ? 1 :
                    ((comp_dist == 16) ? 2 : 3);

            if (input_mode && (comp_dist / (1<<(nsteps-1)) != 8))
                nsteps = 1;  /* mirror points cannot combine unless final comp_dist = 8 */

            otransp = ((comp_dist >> nsteps) >= 8) ? 1 : 2;

            status= bitonic_merge_multi_step(n, comp_dist, nsteps, input_mode,
                    itransp, otransp, ptr_i, ptr_o, c);

            if (status== -1)
                goto exit;

            swap_ptr(&ptr_i, &ptr_o);
            comp_dist = (nsteps == 1) ? comp_dist/2 :
                    ((nsteps == 2) ? comp_dist/4 : comp_dist/8);
        }

        /* then do comp_dist = 4, 2, 1 in one step,
            but need to scale comp_dist by 8 to account for tranposition */

        nsteps = 3;
        itransp = otransp;
        otransp = 1;
        comp_dist = 4*8;
        input_mode = 0;

        status= bitonic_merge_multi_step(n, comp_dist, nsteps, input_mode,
                itransp, otransp, ptr_i, ptr_o, c);

        if (status== -1)
            goto exit;

        swap_ptr(&ptr_i, &ptr_o);
        merge_size *= 2;
    }

    /*---------------------------------------------------------------------*/
    /* Cleanup, get rid of extra column, introduced due to transpose.      */
    /*                                                                     */
    /* for (i=0; i<8; i++)                                                 */
    /*    for (j=0; j<n/8; j++)                                            */
    /*      x[i*n/8 + j] = ptr_i[i*(n/8 + 1) + j];                         */
    /*---------------------------------------------------------------------*/

    my_vcop_remove_ex_col_custom(ptr_i, output, n, c->backup_my_pblock_ptr);

    /*---------------------------------------------------------------------*/
    /* Capture this function for deferred execution, along with the        */
    /* associated parameter pointer.                                       */
    /*---------------------------------------------------------------------*/

    c->funcs_exec[c->num_funcs_exec]   =   &vcop_remove_ex_col_vloops;
    c->ptr_params[c->num_funcs_exec]   =   c->my_pblock_ptr;
    c->my_pblock_ptr               +=   vcop_remove_ex_col_param_count();
    c->backup_my_pblock_ptr        +=   vcop_remove_ex_col_param_count();
    c->num_funcs_exec++;

    /*---------------------------------------------------------------------*/
    /*  Check to make sure, we have not overflowed the allocated memory    */
    /*  for the parameter array.                                           */
    /*---------------------------------------------------------------------*/

    diff                         =  (c->my_pblock_ptr - c->ptr_params[0]);

    assert(diff <= MAX_PARAMS);

    assert(c->num_funcs_exec <= MAX_FUNC_CALLS);

    exit:
    return status;
}

/*------------------------------------------------------------------------*/
/* The "lmbd" is a helper function, that does the lmbd detect leading 1   */
/* bit position of positive number return -1 if zero or negative.         */
/*------------------------------------------------------------------------*/
int32_t lmbd(int32_t x)
{
#if VCOP_HOST_EMULATION
    int32_t i, k;

    if (x <= 0) return -1;

    for (i=0, k=1; k<=x; i++)
        k = 2*k;
#else

    return 31 - _norm(x);
#endif
}

void vcop_sort8_simd8(int32_t niter, int32_t out_transpose, int32_t *in, int32_t *out, SortContext *c)
{


    /*----------------------------------------------------------------------*/
    /* "niter" is the number of "8x8" bloxks, so the array's size is "niter */
    /* x 64". For each such 8x8 array, sort 8 columns each of 8 elements,   */
    /* and then advance to the next block. Do, this by first copying the    */
    /* "in" data into array "x". Sort in place in array "x" and either      */
    /* write back normally or transpose output based on "out_transpose"     */
    /* flag.                                                                */
    /*                                                                      */
    /*    int32_t i1, k, p;                                                     */
    /*    int32_t x[8][8];                                                      */
    /*    for (i1=0; i1 < niter; i1++)                                      */
    /*    {                                                                 */
    /*      for (k=0; k<8; k++)                                             */
    /*        for (p=0; p<8; p++)                                           */
    /*          x[k][p] = in[i1*64 + k*8 + p];                              */
    /*                                                                      */
    /*      sort2_simd8(&x[0][0], &x[1][0]);                                */
    /*      sort2_simd8(&x[2][0], &x[3][0]);                                */
    /*      sort2_simd8(&x[0][0], &x[2][0]);                                */
    /*      sort2_simd8(&x[1][0], &x[3][0]);                                */
    /*      sort2_simd8(&x[1][0], &x[2][0]);                                */
    /*      sort2_simd8(&x[4][0], &x[5][0]);                                */
    /*      sort2_simd8(&x[6][0], &x[7][0]);                                */
    /*      sort2_simd8(&x[4][0], &x[6][0]);                                */
    /*      sort2_simd8(&x[5][0], &x[7][0]);                                */
    /*      sort2_simd8(&x[5][0], &x[6][0]);                                */
    /*      sort2_simd8(&x[0][0], &x[4][0]);                                */
    /*      sort2_simd8(&x[2][0], &x[6][0]);                                */
    /*      sort2_simd8(&x[2][0], &x[4][0]);                                */
    /*      sort2_simd8(&x[1][0], &x[5][0]);                                */
    /*      sort2_simd8(&x[3][0], &x[7][0]);                                */
    /*      sort2_simd8(&x[3][0], &x[5][0]);                                */
    /*      sort2_simd8(&x[1][0], &x[2][0]);                                */
    /*      sort2_simd8(&x[3][0], &x[4][0]);                                */
    /*      sort2_simd8(&x[5][0], &x[6][0]);                                */
    /*                                                                      */
    /*      if (!out_transpose)                                             */
    /*        for (k=0; k<8; k++)                                           */
    /*          for (p=0; p<8; p++)                                         */
    /*            out[i1*64 + k*8 + p] = x[k][p];                           */
    /*      else                                                            */
    /*        for (k=0; k<8; k++)                                           */
    /*           for (p=0; p<8; p++)                                        */
    /*             out[i1*8 + k + p*(niter*8+1)] = x[k][p];                 */
    /*     }                                                                */
    /*  If "niter" is 1, call the function that works on one 8x8 block and  */
    /*  then performs a transpose right away, otherwise call the function   */
    /*  which works on multiple '8x8' blocks, by putting it into the        */
    /*  function pointer array, for dferred execution.                      */
    /*----------------------------------------------------------------------*/

    if (niter == 1)
    {
        my_vcop_sort8_simd8_64_custom (niter, out_transpose, in, out, c->backup_my_pblock_ptr);

        c->funcs_exec[c->num_funcs_exec]   =   &vcop_sort8_simd8_64_vloops;
        c->ptr_params[c->num_funcs_exec]   =   c->my_pblock_ptr;
        c->my_pblock_ptr               +=   vcop_sort8_simd8_64_param_count();
        c->backup_my_pblock_ptr        +=   vcop_sort8_simd8_64_param_count();
        c->num_funcs_exec++;
    }
    else
    {
        my_vcop_sort8_simd8_XX_custom (niter, out_transpose, in, out, c->backup_my_pblock_ptr);

        c->funcs_exec[c->num_funcs_exec]   =   &vcop_sort8_simd8_XX_vloops;
        c->ptr_params[c->num_funcs_exec]   =   c->my_pblock_ptr ;
        c->my_pblock_ptr                +=   vcop_sort8_simd8_XX_param_count();
        c->backup_my_pblock_ptr         +=   vcop_sort8_simd8_XX_param_count();
        c->num_funcs_exec++;;
    }
}


/*------------------------------------------------------------------------*/
/*  The function "bitonic_merge_multi_step" implements a multi-step       */
/*  merge, by calling out to individual helper functions to implement     */
/*  either 1 stage, 2 stage or 3 stages of merging. It accepts the        */
/*  following arguments:                                                  */
/*                                                                        */
/*  n :  Number of points to sort, limited to power of 2.                 */
/*                                                                        */
/*  comp_dstt : merge distance between two arrays. Enter 8, when          */
/*  merging two arrays each of 8 points.                                  */
/*                                                                        */
/*  nsteps : Number of merge stages, we try to combine up to 3 stages     */
/*  where possible, but have specific functions we call out to for        */
/*  1 stage, 2 stage and 3 stage merge.                                   */
/*                                                                        */
/*  input_mode:  The input array can come in three potentially            */
/*  different geometries over time, because of efficiencies in            */
/*  writing to banked memory, we have to maintain it in 3 different       */
/*  orientations, in order to ensure peak efficiency.                     */
/*                                                                        */
/*  Mode                 Description                                      */
/*------------------------------------------------------------------------*/
/*   0                   Normal, sort between x[i] and x[i + comp_dist]   */
/*                                                                        */
/*   1                   Mirror row, handle inter-vector sort of elems.   */
/*                       spaced 4, 2, 1 element apart. Sort between       */
/*                       x[i*8 + j], x[comp_dist + i*8 + j]               */
/*                                                                        */
/*   2                   Mirror point, bi-tonic merge requires reading    */
/*                       x[i*8 + j], x[2*comp_dist -1 - i]                */
/*                                                                        */
/*   itransp : Describes how input is organized, with the following       */
/*   semantics.                                                           */
/*                                                                        */
/*   0                  8 columns and n/8 rows tall.                      */
/*                                                                        */
/*   1                  N/8 + 1 and 8 rows tall, wide geometry.           */
/*                                                                        */
/*   2                  9 columns and  n/8 rows tall.                     */
/*                                                                        */
/*  otransp:            Is output transposed or not.                      */
/*                                                                        */
/*  input:              Pointer to input array.                           */
/*                                                                        */
/*  output:             Pointer to output array.                          */
/*                                                                        */
/*------------------------------------------------------------------------*/

int32_t bitonic_merge_multi_step
(
        int32_t     n,
        int32_t     comp_dist,
        int32_t     nsteps,
        int32_t     input_mode,
        int32_t     itransp,
        int32_t     otransp,
        int32_t     *input,
        int32_t     *output,
        SortContext *c
)
{
    int32_t  final_dist, two_to_nsteps;
    int32_t  niter1, niter2, niter3, in1_base, in2_base;
    int32_t  in1ptr_w1, in1ptr_w2, in1ptr_w3, in2ptr_w1, in2ptr_w2, in2ptr_w3;
    int32_t  out_base, outptr_ofst,  outptr_w1, outptr_w2, outptr_w3;
    int32_t  in1_base_step, out_base_step;
    int32_t  reverse_ptr, reverse_pts, in_pad, out_pad;
    int32_t status;

    two_to_nsteps = (nsteps == 1) ? 2 : ((nsteps == 2) ? 4 : 8);
    final_dist    = comp_dist*2/two_to_nsteps;
    niter1        = n / (2*comp_dist);
    niter2        = final_dist / 8;
    niter3        = 1;
    in1_base      = 0;
    in1_base_step = final_dist;
    in1ptr_w1     = 2*comp_dist;
    in1ptr_w2     = 8;
    in1ptr_w3     = 0;
    in2_base      = comp_dist;
    in2ptr_w1     = 2*comp_dist;
    in2ptr_w2     = 8;
    in2ptr_w3     = 0;
    out_base      = 0;
    outptr_w1     = 2*comp_dist;
    outptr_w2     = 8;
    outptr_w3     = 0;
    reverse_ptr   = (input_mode == 1) || (input_mode == 2);
    reverse_pts   = (input_mode == 2);
    in_pad        = (itransp == 0) ? 0 : ((itransp == 1) ? n/8 : 8);
    out_pad       = (otransp == 0) ? 0 : ((otransp == 1) ? n/8 : 8);
    outptr_ofst   = (itransp == otransp) ? 1 :
            ((otransp == 1) ? n/8+1 : 9);
    out_base_step = (itransp == otransp) ? final_dist :
            ((otransp == 1) ? transp_idx(final_dist, 8, n/8)
                    : transp_idx(final_dist, n/8, 8));
    outptr_w1     = (itransp == otransp) ? outptr_w1 :
            ((otransp == 1) ? transp_idx(outptr_w1, 8, n/8)
                    : transp_idx(outptr_w1, n/8, 8));

    status= 0;

    if (itransp == 0) /* SIMD merge */
    {
        if (input_mode == 1)
        {
            in2_base = 2*comp_dist - 8;
            in2ptr_w2 = -8;
        }

        if (input_mode == 2)
        {
            status= -1;
            goto exit;
        }
    }
    else if (input_mode == 2 && nsteps == 1) /* first step of inter-lane merge by itself */
    {
        /* only case 3 level looping is used */
        niter2 = comp_dist / (n/8);
        niter3 = (n/8)     / 8;
        in1ptr_w2   = n/8;
        in1ptr_w3   = 8;

        in2_base    = 2*comp_dist - 8;
        in2ptr_w2   = -n/8;
        in2ptr_w3   = -8;

        outptr_w2   = n/8;
        outptr_w3   = 8;
    }
    else if (input_mode == 2) /* first step of inter-lane merge, combined with other steps */
    {
        in2_base    = 2*comp_dist - 8;
        in2ptr_w2   = -8;

        if (final_dist != 8)
        {
            status= -1;
            goto exit;
        }
    }
    else if (itransp == 1) /* rest of first half of inter-lane merge */
    {
        if ((n/8) > (2*comp_dist))
        {
            /* for n==256 or larger, i1 loop of n/(2*comp_dist) iterations spans horz & vert
          in input & output(tranposed or not) so need to split into horz and vert loops */
            niter1        = 8;
            niter2        = (n/8) / (2*comp_dist);
            niter3        = final_dist / 8;
            in1ptr_w1     = n/8;
            in1ptr_w2     = 2*comp_dist;
            in1ptr_w3     = 8;
            in2_base      = comp_dist;
            in2ptr_w1     = n/8;
            in2ptr_w2     = 2*comp_dist;
            in2ptr_w3     = 8;
            out_base      = 0;
            outptr_w1     = n/8;
            outptr_w2     = 2*comp_dist;
            outptr_w3     = 8;
            outptr_w1     = (itransp == otransp) ? outptr_w1 :
                    ((otransp == 1) ? transp_idx(outptr_w1, 8, n/8)
                            : transp_idx(outptr_w1, n/8, 8));
            outptr_w2     = (itransp == otransp) ? outptr_w2 :
                    ((otransp == 1) ? transp_idx(outptr_w2, 8, n/8)
                            : transp_idx(outptr_w2, n/8, 8));

        }
    }
    else /* second half of inter-lane merge, always 3 steps together */
    {

    }
#if 0
    if (DEBUG_CALL)
    {
        printf("Dbg: calling vcop_psort2 nsteps=%d, niter1=%d, niter2=%d, niter3=%d\n",
                nsteps, niter1, niter2, niter3);
        printf("\t\t\t in1_base=%d, in2_base=%d, in_base_step=%d\n",
                in1_base, in2_base, in1_base_step);
        printf("\t\t\t in1ptr_w1=%d, in1ptr_w2=%d, in1ptr_w3=%d\n",
                in1ptr_w1, in1ptr_w2, in1ptr_w3);
        printf("\t\t\t in2ptr_w1=%d, in2ptr_w2=%d, in2ptr_w3=%d\n",
                in2ptr_w1, in2ptr_w2, in2ptr_w3);
        printf("\t\t\t out_base=%d, out_base_step=%d, outptr_w1=%d, outptr_w2=%d, outptr_w3=%d\n",
                out_base, out_base_step, outptr_w1, outptr_w2, outptr_w3);
        printf("\t\t\t outptr_ofst=%d, in_pad=%d, out_pad=%d, reverse_ptr=%d, reverse_pts=%d\n",
                outptr_ofst, in_pad, out_pad, reverse_ptr, reverse_pts);
    }

    if (DEBUG_PRECLR_OUTPUT) clear(n*9/8, output);
#endif
    if (nsteps == 1)
        vcop_psort2_1step(niter1, niter2, niter3, in1_base, in2_base,
                in1ptr_w1, in1ptr_w2, in1ptr_w3, in2ptr_w1, in2ptr_w2, in2ptr_w3,
                out_base, outptr_ofst,  out_base_step, outptr_w1, outptr_w2, outptr_w3,
                in_pad, out_pad, reverse_pts,
                input, output, c);
    else if (nsteps == 2)
        vcop_psort2_2steps(niter1, niter2, niter3,
                in1_base, in1_base_step, in1ptr_w1, in1ptr_w2, in1ptr_w3,
                in2_base, in2ptr_w1, in2ptr_w2, in2ptr_w3,
                out_base, outptr_ofst,  out_base_step, outptr_w1, outptr_w2, outptr_w3,
                in_pad, out_pad, reverse_ptr, reverse_pts,
                input, output, c);
    else
        vcop_psort2_3steps(niter1, niter2, niter3,
                in1_base, in1_base_step, in1ptr_w1, in1ptr_w2, in1ptr_w3,
                in2_base, in2ptr_w1, in2ptr_w2, in2ptr_w3,
                out_base, outptr_ofst,  out_base_step, outptr_w1, outptr_w2, outptr_w3,
                in_pad, out_pad, reverse_ptr, reverse_pts,
                input, output, c);

    exit:
    return status;
}

/*------------------------------------------------------------------------*/
/* The function  "vcop_psort2_1step" performs either a reverse step or    */
/* normal sorting, 1-step at a time.                                      */
/*------------------------------------------------------------------------*/

void vcop_psort2_1step
(
        int32_t niter1,
        int32_t niter2,
        int32_t niter3,
        int32_t in1_base,
        int32_t in2_base,
        int32_t in1ptr_w1,
        int32_t in1ptr_w2,
        int32_t in1ptr_w3,
        int32_t in2ptr_w1,
        int32_t in2ptr_w2,
        int32_t in2ptr_w3,
        int32_t out_base,
        int32_t outptr_ofst, /* point spread in a vector */
        int32_t out_base_step,
        int32_t outptr_w1,
        int32_t outptr_w2,
        int32_t outptr_w3,
        int32_t in_pad,  /* 0: array not padded, N: stride = N+1 */
        int32_t out_pad,
        int32_t reverse_pts,
        int32_t *input,
        int32_t *output,
        SortContext *c
)
{
    int32_t ibase[2];
    int32_t obase[2];
    int32_t n;
    int32_t p;

    n = niter1 * niter2 * niter3 * 16;
    ibase[0] = in1_base;
    ibase[1] = in2_base;
    obase[0] = out_base;
    obase[1] = out_base + out_base_step;

    if (in_pad)
    {
        ibase[0]  += (in1_base / in_pad);
        ibase[1]  += (in2_base / in_pad);
        in1ptr_w1 += (in1ptr_w1 / in_pad);
        in1ptr_w2 += (in1ptr_w2 / in_pad);
        in1ptr_w3 += (in1ptr_w3 / in_pad);
        in2ptr_w1 += (in2ptr_w1 / in_pad);
        in2ptr_w2 += (in2ptr_w2 / in_pad);
        in2ptr_w3 += (in2ptr_w3 / in_pad);
    }

    if (out_pad)
    {
        obase[0]      =  (obase[0] % n) + (obase[0] / n);
        obase[1]      =  (obase[1] % n) + (obase[1] / n);
        obase[0]      += (obase[0] / out_pad);
        obase[1]      += (obase[1] / out_pad);
        outptr_w1     += (outptr_w1 / out_pad);
        outptr_w2     += (outptr_w2 / out_pad);
        outptr_w3     += (outptr_w3 / out_pad);
    }

    /*-----------------------------------------------------------------------*/
    /* The C code description for 1-step sorting is as :                     */
    /*                                                                       */
    /* for (i1=0; i1<niter1; i1++)                                           */
    /*  for (i2=0; i2<niter2; i2++)                                          */
    /*    for (i3=0; i3<niter3; i3++)                                        */
    /*    {                                                                  */
    /*     for (p=0; p<8; p++)                                               */
    /*       vec[0][p] =                                                     */
    /*       input[ibase[0] + i1*in1ptr_w1 + i2*in1ptr_w2 +                  */
    /*                                       i3*in1ptr_w3 + p];              */
    /*                                                                       */
    /*     if (!reverse_pts)                                                 */
    /*      for (p=0; p<8; p++)                                              */
    /*      vec[1][p] =                                                      */
    /*      input[ibase[1] + i1*in2ptr_w1 + i2*in2ptr_w2 +                   */
    /*                                      i3*in2ptr_w3 + p];               */
    /*      else                                                             */
    /*      for (p=0; p<8; p++)                                              */
    /*      vec[1][p] =                                                      */
    /*      input[ibase[1] + i1*in2ptr_w1 + i2*in2ptr_w2 +                   */
    /*                                      i3*in2ptr_w3 + 7-p];             */
    /*                                                                       */
    /*       sort2_simd8(&vec[0][0], &vec[1][0]);                            */
    /*                                                                       */
    /*      for (k=0; k<2; k++)                                              */
    /*        for (p=0; p<8; p++)                                            */
    /*          output[obase[k] + i1*outptr_w1 + i2*outptr_w2 +              */
    /*                                      i3*outptr_w3 + p*outptr_ofst]    */
    /*            = vec[k][p];                                               */
    /*     }                                                                 */
    /*                                                                       */
    /*-----------------------------------------------------------------------*/

    for (p = 0; p < 8; p++) c->backup_my_out_offset_ptr[p] = (p * outptr_ofst * sizeof(int32_t));

    if (reverse_pts)
    {
        my_vcop_psort2_1step_reverse_kernel_custom
        (
                niter1,
                niter2,
                niter3,
                ibase[0]   * sizeof(int32_t),
                ibase[1]   * sizeof(int32_t),
                in1ptr_w1  * sizeof(int32_t),
                in1ptr_w2  * sizeof(int32_t),
                in1ptr_w3  * sizeof(int32_t),
                in2ptr_w1  * sizeof(int32_t),
                in2ptr_w2  * sizeof(int32_t),
                in2ptr_w3  * sizeof(int32_t),
                obase[0]   * sizeof(int32_t),
                obase[1]   * sizeof(int32_t),
                outptr_w1  * sizeof(int32_t),
                outptr_w2  * sizeof(int32_t),
                outptr_w3  * sizeof(int32_t),
                input,
                output,
                c->my_out_offset_ptr,
                c->backup_my_pblock_ptr
        );

        c->funcs_exec[c->num_funcs_exec]   =   &vcop_psort2_1step_reverse_kernel_vloops;
        c->ptr_params[c->num_funcs_exec]   =   c->my_pblock_ptr;
        c->my_pblock_ptr               +=   vcop_psort2_1step_reverse_kernel_param_count();
        c->backup_my_pblock_ptr        +=   vcop_psort2_1step_reverse_kernel_param_count();
        c->my_out_offset_ptr           +=   8;
        c->backup_my_out_offset_ptr    +=   8;
        c->num_funcs_exec++;
    }
    else
    {
        my_vcop_psort2_1step_kernel_custom
        (
                niter1,
                niter2,
                niter3,
                ibase[0]   * sizeof(int32_t),
                ibase[1]   * sizeof(int32_t),
                in1ptr_w1  * sizeof(int32_t),
                in1ptr_w2  * sizeof(int32_t),
                in1ptr_w3  * sizeof(int32_t),
                in2ptr_w1  * sizeof(int32_t),
                in2ptr_w2  * sizeof(int32_t),
                in2ptr_w3  * sizeof(int32_t),
                obase[0]   * sizeof(int32_t),
                obase[1]   * sizeof(int32_t),
                outptr_w1  * sizeof(int32_t),
                outptr_w2  * sizeof(int32_t),
                outptr_w3  * sizeof(int32_t),
                input,
                output,
                c->my_out_offset_ptr,
                c->backup_my_pblock_ptr
        );

        c->funcs_exec[c->num_funcs_exec]   =   &vcop_psort2_1step_kernel_vloops;
        c->ptr_params[c->num_funcs_exec]   =   c->my_pblock_ptr;
        c->my_pblock_ptr               +=   vcop_psort2_1step_kernel_param_count();
        c->backup_my_pblock_ptr        +=   vcop_psort2_1step_kernel_param_count();
        c->my_out_offset_ptr           +=   8;
        c->backup_my_out_offset_ptr    +=   8;
        c->num_funcs_exec++;
    }

}

/*------------------------------------------------------------------------*/
/* The function  "vcop_psort2_2steps" performs either a reverse step or   */
/* normal sorting, 2-steps at a time.                                     */
/*------------------------------------------------------------------------*/

void vcop_psort2_2steps(
        int32_t niter1,
        int32_t niter2,
        int32_t niter3,
        int32_t in_base,
        int32_t in_base_step,
        int32_t in1ptr_w1,
        int32_t in1ptr_w2,
        int32_t in1ptr_w3,
        int32_t in2_base,
        int32_t in2ptr_w1,
        int32_t in2ptr_w2,
        int32_t in2ptr_w3,
        int32_t out_base,
        int32_t outptr_ofst,
        int32_t out_base_step,
        int32_t outptr_w1,
        int32_t outptr_w2,
        int32_t outptr_w3,
        int32_t in_pad,  /* 0: array not padded, N: stride = N+1 */
        int32_t out_pad,
        int32_t reverse_ptr,
        int32_t reverse_pts,
        int32_t *input,
        int32_t *output,
        SortContext *c)
{
    int32_t k, p;
    int32_t ibase[4];
    int32_t obase[4];
    int32_t n;

    n = niter1 * niter2 * niter3 * 32;

    for (k=0; k<4; k++)
    {
        ibase[k] = (!reverse_ptr || k<2) ? in_base + k*in_base_step
                : in2_base - (k-2)*in_base_step;
        obase[k] = out_base + k*out_base_step;

        if (in_pad)
            ibase[k] += (ibase[k] / in_pad);

        if (out_pad)
        {
            obase[k] = (obase[k] % n) + (obase[k] / n);
            obase[k] += (obase[k] / out_pad);
        }
    }

    if (in_pad)
    {
        in1ptr_w1 += (in1ptr_w1 / in_pad);
        in1ptr_w2 += (in1ptr_w2 / in_pad);
        in1ptr_w3 += (in1ptr_w3 / in_pad);
        in2ptr_w1 += (in2ptr_w1 / in_pad);
        in2ptr_w2 += (in2ptr_w2 / in_pad);
        in2ptr_w3 += (in2ptr_w3 / in_pad);
    }

    if (out_pad)
    {
        outptr_w1 += (outptr_w1 / out_pad);
        outptr_w2 += (outptr_w2 / out_pad);
        outptr_w3 += (outptr_w3 / out_pad);
    }

    /*---------------------------------------------------------------------*/
    /* The C code implemented on VCOP is as follows:                       */
    /*                                                                     */
    /* for (i1=0; i1<niter1; i1++)                                         */
    /*  for (i2=0; i2<niter2; i2++)                                        */
    /*  for (i3=0; i3<niter3; i3++)                                        */
    /*  {                                                                  */
    /*    for (k=0; k<2; k++)                                              */
    /*      for (p=0; p<8; p++)                                            */
    /*        x[k][p] = input[ibase[k] + i1*in1ptr_w1 + i2*in1ptr_w2 +     */
    /*                                   i3*in1ptr_w3 + p];                */
    /*                                                                     */
    /*      if (!reverse_pts)                                              */
    /*        for (k=2; k<4; k++)                                          */
    /*          for (p=0; p<8; p++)                                        */
    /*            x[k][p] = input[ibase[k] + i1*in2ptr_w1 + i2*in2ptr_w2 + */
    /*                                       i3*in2ptr_w3 + p];            */
    /*       else                                                          */
    /*         for (k=2; k<4; k++)                                         */
    /*           for (p=0; p<8; p++)                                       */
    /*             x[k][p] = input[ibase[k] + i1*in2ptr_w1 + i2*in2ptr_w2 +*/
    /*                                        i3*in2ptr_w3 + 7-p];         */
    /*                                                                     */
    /*       sort2_simd8(&x[0][0], &x[2][0]);                              */
    /*       sort2_simd8(&x[1][0], &x[3][0]);                              */
    /*       sort2_simd8(&x[0][0], &x[1][0]);                              */
    /*       sort2_simd8(&x[2][0], &x[3][0]);                              */
    /*                                                                     */
    /*       for (k=0; k<4; k++)                                           */
    /*         for (p=0; p<8; p++)                                         */
    /*           output[obase[k] + i1*outptr_w1 + i2*outptr_w2 +           */
    /*                             i3*outptr_w3 + p*outptr_ofst]           */
    /*             = x[k][p];                                              */
    /*     }                                                               */
    /*---------------------------------------------------------------------*/

    for (p = 0; p < 8; p++) c->backup_my_out_offset_ptr[p] = (p * outptr_ofst * sizeof(int32_t));

    if (reverse_pts)
    {
        my_vcop_psort2_2steps_reverse_kernel_custom
        (
                niter1,
                niter2,
                niter3,
                ibase[0]  *  sizeof(int32_t),
                ibase[1]  *  sizeof(int32_t),
                ibase[2]  *  sizeof(int32_t),
                ibase[3]  *  sizeof(int32_t),
                in1ptr_w1 *  sizeof(int32_t),
                in1ptr_w2 *  sizeof(int32_t),
                in1ptr_w3 *  sizeof(int32_t),
                in2ptr_w1 *  sizeof(int32_t),
                in2ptr_w2 *  sizeof(int32_t),
                in2ptr_w3 *  sizeof(int32_t),
                obase[0]  *  sizeof(int32_t),
                obase[1]  *  sizeof(int32_t),
                obase[2]  *  sizeof(int32_t),
                obase[3]  *  sizeof(int32_t),
                outptr_w1 *  sizeof(int32_t),
                outptr_w2 *  sizeof(int32_t),
                outptr_w3 *  sizeof(int32_t),
                input,
                output,
                c->my_out_offset_ptr,
                c->backup_my_pblock_ptr
        );

        c->funcs_exec[c->num_funcs_exec]   =   &vcop_psort2_2steps_reverse_kernel_vloops;
        c->ptr_params[c->num_funcs_exec]   =   c->my_pblock_ptr;
        c->my_pblock_ptr               +=   vcop_psort2_2steps_reverse_kernel_param_count();
        c->backup_my_pblock_ptr        +=   vcop_psort2_2steps_reverse_kernel_param_count();
        c->my_out_offset_ptr           +=   8;
        c->backup_my_out_offset_ptr    +=   8;
        c->num_funcs_exec++;
    }
    else
    {
        my_vcop_psort2_2steps_kernel_custom
        (
                niter1,
                niter2,
                niter3,
                ibase[0]  *  sizeof(int32_t),
                ibase[1]  *  sizeof(int32_t),
                ibase[2]  *  sizeof(int32_t),
                ibase[3]  *  sizeof(int32_t),
                in1ptr_w1 *  sizeof(int32_t),
                in1ptr_w2 *  sizeof(int32_t),
                in1ptr_w3 *  sizeof(int32_t),
                in2ptr_w1 *  sizeof(int32_t),
                in2ptr_w2 *  sizeof(int32_t),
                in2ptr_w3 *  sizeof(int32_t),
                obase[0]  *  sizeof(int32_t),
                obase[1]  *  sizeof(int32_t),
                obase[2]  *  sizeof(int32_t),
                obase[3]  *  sizeof(int32_t),
                outptr_w1 *  sizeof(int32_t),
                outptr_w2 *  sizeof(int32_t),
                outptr_w3 *  sizeof(int32_t),
                input,
                output,
                c->my_out_offset_ptr,
                c->backup_my_pblock_ptr
        );

        c->funcs_exec[c->num_funcs_exec]   =   &vcop_psort2_2steps_kernel_vloops;
        c->ptr_params[c->num_funcs_exec]   =   c->my_pblock_ptr;
        c->my_pblock_ptr               +=   vcop_psort2_2steps_kernel_param_count();
        c->backup_my_pblock_ptr        +=   vcop_psort2_2steps_kernel_param_count();
        c->my_out_offset_ptr           +=   8;
        c->backup_my_out_offset_ptr    +=   8;
        c->num_funcs_exec++;
    }
}

/*------------------------------------------------------------------------*/
/* The function  "vcop_psort2_3steps" performs either a reverse step or   */
/* normal sorting, 3-steps at a time.                                     */
/*------------------------------------------------------------------------*/

void vcop_psort2_3steps(
        int32_t niter1,
        int32_t niter2,
        int32_t niter3,
        int32_t in_base,
        int32_t in_base_step,
        int32_t in1ptr_w1,
        int32_t in1ptr_w2,
        int32_t in1ptr_w3,
        int32_t in2_base,
        int32_t in2ptr_w1,
        int32_t in2ptr_w2,
        int32_t in2ptr_w3,
        int32_t out_base,
        int32_t outptr_ofst,
        int32_t out_base_step,
        int32_t outptr_w1,
        int32_t outptr_w2,
        int32_t outptr_w3,
        int32_t in_pad,  /* 0: array not padded, N: stride = N+1 */
        int32_t out_pad,
        int32_t reverse_ptr,
        int32_t reverse_pts,
        int32_t *input,
        int32_t *output,
        SortContext *c)
{
    int32_t  k, p;
    int32_t ibase[8];
    int32_t obase[8];
    int32_t n;

    n = niter1 * niter2 * niter3 * 64;

    for (k=0; k<8; k++)
    {
        ibase[k] = (!reverse_ptr || k<4) ? in_base + k*in_base_step
                : in2_base - (k-4)*in_base_step;

        obase[k] = out_base + k*out_base_step;

        if (in_pad)
            ibase[k] += (ibase[k] / in_pad);

        if (out_pad)
        {
            obase[k] = (obase[k] % n) + (obase[k] / n);
            obase[k] += (obase[k] / out_pad);
        }
    }

    if (in_pad)
    {
        in1ptr_w1 += (in1ptr_w1 / in_pad);
        in1ptr_w2 += (in1ptr_w2 / in_pad);
        in1ptr_w3 += (in1ptr_w3 / in_pad);
        in2ptr_w1 += (in2ptr_w1 / in_pad);
        in2ptr_w2 += (in2ptr_w2 / in_pad);
        in2ptr_w3 += (in2ptr_w3 / in_pad);
    }

    if (out_pad)
    {
        outptr_w1 += (outptr_w1 / out_pad);
        outptr_w2 += (outptr_w2 / out_pad);
        outptr_w3 += (outptr_w3 / out_pad);
    }

    /*---------------------------------------------------------------------*/
    /* The C code implemented on VCOP is as follows:                       */
    /*                                                                     */
    /*  for (i1=0; i1<niter1; i1++)                                        */
    /*  for (i2=0; i2<niter2; i2++)                                        */
    /*  for (i3=0; i3<niter3; i3++)                                        */
    /*  {                                                                  */
    /*    for (k=0; k<4; k++)                                              */
    /*      for (p=0; p<8; p++)                                            */
    /*        x[k][p] = input[ibase[k] + i1*in1ptr_w1 + i2*in1ptr_w2 +     */
    /*                                   i3*in1ptr_w3 + p];                */
    /*                                                                     */
    /*    if (!reverse_pts)                                                */
    /*      for (k=4; k<8; k++)                                            */
    /*        for (p=0; p<8; p++)                                          */
    /*          x[k][p] = input[ibase[k] + i1*in2ptr_w1 + i2*in2ptr_w2 +   */
    /*                                     i3*in2ptr_w3 + p];              */
    /*    else                                                             */
    /*      for (k=4; k<8; k++)                                            */
    /*        for (p=0; p<8; p++)                                          */
    /*          x[k][p] = input[ibase[k] + i1*in2ptr_w1 + i2*in2ptr_w2 +   */
    /*                                     i3*in2ptr_w3 + 7-p];            */
    /*                                                                     */
    /*    sort2_simd8(&x[0][0], &x[4][0]);                                 */
    /*    sort2_simd8(&x[1][0], &x[5][0]);                                 */
    /*    sort2_simd8(&x[2][0], &x[6][0]);                                 */
    /*    sort2_simd8(&x[3][0], &x[7][0]);                                 */
    /*    sort2_simd8(&x[0][0], &x[2][0]);                                 */
    /*    sort2_simd8(&x[1][0], &x[3][0]);                                 */
    /*    sort2_simd8(&x[4][0], &x[6][0]);                                 */
    /*    sort2_simd8(&x[5][0], &x[7][0]);                                 */
    /*    sort2_simd8(&x[0][0], &x[1][0]);                                 */
    /*    sort2_simd8(&x[2][0], &x[3][0]);                                 */
    /*    sort2_simd8(&x[4][0], &x[5][0]);                                 */
    /*    sort2_simd8(&x[6][0], &x[7][0]);                                 */
    /*                                                                     */
    /*    for (k=0; k<8; k++)                                              */
    /*      for (p=0; p<8; p++)                                            */
    /*        output[obase[k] + i1*outptr_w1 + i2*outptr_w2 +              */
    /*                          i3*outptr_w3 + p*outptr_ofst]              */
    /*          = x[k][p];                                                 */
    /*  }                                                                  */
    /*---------------------------------------------------------------------*/

    for (p = 0; p < 8; p++) c->backup_my_out_offset_ptr[p] = (p * outptr_ofst * sizeof(int32_t));

    if (reverse_pts)
    {
        my_vcop_psort2_3steps_reverse_kernel_custom
        (
                niter1,
                niter2,
                niter3,
                ibase[0]  *  sizeof(int32_t),
                ibase[1]  *  sizeof(int32_t),
                ibase[2]  *  sizeof(int32_t),
                ibase[3]  *  sizeof(int32_t),
                ibase[4]  *  sizeof(int32_t),
                ibase[5]  *  sizeof(int32_t),
                ibase[6]  *  sizeof(int32_t),
                ibase[7]  *  sizeof(int32_t),
                in1ptr_w1 *  sizeof(int32_t),
                in1ptr_w2 *  sizeof(int32_t),
                in1ptr_w3 *  sizeof(int32_t),
                in2ptr_w1 *  sizeof(int32_t),
                in2ptr_w2 *  sizeof(int32_t),
                in2ptr_w3 *  sizeof(int32_t),
                obase[0]  *  sizeof(int32_t),
                obase[1]  *  sizeof(int32_t),
                obase[2]  *  sizeof(int32_t),
                obase[3]  *  sizeof(int32_t),
                obase[4]  *  sizeof(int32_t),
                obase[5]  *  sizeof(int32_t),
                obase[6]  *  sizeof(int32_t),
                obase[7]  *  sizeof(int32_t),
                outptr_w1 *  sizeof(int32_t),
                outptr_w2 *  sizeof(int32_t),
                outptr_w3 *  sizeof(int32_t),
                input,
                output,
                c->my_out_offset_ptr,
                c->backup_my_pblock_ptr
        );

        c->funcs_exec[c->num_funcs_exec]   =   &vcop_psort2_3steps_reverse_kernel_vloops;
        c->ptr_params[c->num_funcs_exec]   =   c->my_pblock_ptr;
        c->my_pblock_ptr               +=   vcop_psort2_3steps_reverse_kernel_param_count();
        c->backup_my_pblock_ptr        +=   vcop_psort2_3steps_reverse_kernel_param_count();
        c->my_out_offset_ptr           +=   8;
        c->backup_my_out_offset_ptr    +=   8;
        c->num_funcs_exec++;

    }
    else
    {
        my_vcop_psort2_3steps_kernel_custom
        (
                niter1,
                niter2,
                niter3,
                ibase[0]  *  sizeof(int32_t),
                ibase[1]  *  sizeof(int32_t),
                ibase[2]  *  sizeof(int32_t),
                ibase[3]  *  sizeof(int32_t),
                ibase[4]  *  sizeof(int32_t),
                ibase[5]  *  sizeof(int32_t),
                ibase[6]  *  sizeof(int32_t),
                ibase[7]  *  sizeof(int32_t),
                in1ptr_w1 *  sizeof(int32_t),
                in1ptr_w2 *  sizeof(int32_t),
                in1ptr_w3 *  sizeof(int32_t),
                in2ptr_w1 *  sizeof(int32_t),
                in2ptr_w2 *  sizeof(int32_t),
                in2ptr_w3 *  sizeof(int32_t),
                obase[0]  *  sizeof(int32_t),
                obase[1]  *  sizeof(int32_t),
                obase[2]  *  sizeof(int32_t),
                obase[3]  *  sizeof(int32_t),
                obase[4]  *  sizeof(int32_t),
                obase[5]  *  sizeof(int32_t),
                obase[6]  *  sizeof(int32_t),
                obase[7]  *  sizeof(int32_t),
                outptr_w1 *  sizeof(int32_t),
                outptr_w2 *  sizeof(int32_t),
                outptr_w3 *  sizeof(int32_t),
                input,
                output,
                c->my_out_offset_ptr,
                c->backup_my_pblock_ptr
        );

        c->funcs_exec[c->num_funcs_exec]   =   &vcop_psort2_3steps_kernel_vloops;
        c->ptr_params[c->num_funcs_exec]   =   c->my_pblock_ptr;
        c->my_pblock_ptr               +=   vcop_psort2_3steps_kernel_param_count();
        c->backup_my_pblock_ptr        +=   vcop_psort2_3steps_kernel_param_count();
        c->my_out_offset_ptr           +=   8;
        c->backup_my_out_offset_ptr    +=   8;
        c->num_funcs_exec++;
    }
}

/*------------------------------------------------------------------------*/
/* Helper function to swap 2 pointers, is called swap_ptr.                */
/*------------------------------------------------------------------------*/

void swap_ptr(int32_t **x, int32_t **y)
{
    int32_t *t;

    t = *x;
    *x = *y;
    *y = t;
}

/*--------------------------------------------------------------------------*/
/* The function "transp_idx" returns the row number, by taking in a         */
/* absolute offset and calculating the new global coordinate in a           */
/* geometry of width "w2" when the width in the first geometry is "w1".     */
/*--------------------------------------------------------------------------*/

int32_t  transp_idx(int32_t x, int32_t w1, int32_t w2)
{
    int32_t hidx, vidx, y;

    hidx = x % w1;
    vidx = x / w1;
    y    = hidx * w2 + vidx;

    return y;
}

#endif
