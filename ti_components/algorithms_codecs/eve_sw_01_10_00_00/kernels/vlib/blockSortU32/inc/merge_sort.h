#ifndef _MERGE_SORT_H

#define _MERGE_SORT_H

#include <stdint.h>

#define MAX_PARAMS        1150U
#define MAX_FUNC_CALLS    32U

typedef void (*FUNC_PTR)(uint16_t* pblock);

typedef struct {
    FUNC_PTR funcs_exec[MAX_FUNC_CALLS]; /**< List the vloops that EVELIB_algoDMAAutoIncrProcess() will need to call */
    uint16_t *ptr_params[MAX_FUNC_CALLS]; /**< List the pointers to the param registers passed as arguments to the vloops */
    int32_t  *my_out_offset_ptr;  /**< Internal usage */
    uint16_t *my_pblock_ptr; /**< Running pointer of the param blocks */
    int32_t  *backup_my_out_offset_ptr;  /**< Pointer to where the output offsets are backed up in external memory as we don't want to generate them directly in WMEM */
    uint16_t *backup_my_pblock_ptr; /**< Running pointer of where the param blocks are backed up in external memory as we don't want to generate them directly in WMEM */
    uint32_t num_funcs_exec; /**< Number of vloops functions registered in funcs_exec */
} SortContext;

/* All the functions below are used internally by the implementation of EVELIB_sort() */
int32_t mergeSort_init(void *bufa, void *bufb, void *output, uint32_t n, SortContext *c);

int32_t lmbd(int32_t x);

void vcop_sort8_simd8(int32_t niter, int32_t out_transpose, int32_t *in, int32_t *out, SortContext *c);

void swap_ptr(int32_t **x, int32_t **y);

int32_t  transp_idx(int32_t x, int32_t w1, int32_t w2);

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
);

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
       );

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
       SortContext *c);

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
       SortContext *c);

#endif
