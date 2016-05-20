#ifndef _MERGE_SORT_KERNEL_HARD_H
#define _MERGE_SORT_KERNEL_HARD_H  1

#include <vcop.h>

void my_vcop_sort8_simd8_64_custom
(
   int             niter,
   int             out_tr,
   __vptr_int32    in,
   __vptr_int32    out,
   unsigned short  *pblock
);

void my_vcop_sort8_simd8_XX_custom
(
   int              niter,
   int              out_tr,
   __vptr_int32     in,
   __vptr_int32     out,
   unsigned short   *pblock
);

void my_vcop_psort2_1step_reverse_kernel_custom
(
   int              niter1,
   int              niter2,
   int              niter3,
   int              ibase_0,
   int              ibase_1,
   int              in1ptr_w1,
   int              in1ptr_w2,
   int              in1ptr_w3,
   int              in2ptr_w1,
   int              in2ptr_w2,
   int              in2ptr_w3,
   int              obase_0,
   int              obase_1,
   int              outptr_w1,
   int              outptr_w2,
   int              outptr_w3,
   __vptr_int32     input,
   __vptr_int32     output,
   __vptr_int32     out_ofst,
   unsigned short   *pblock
);

void my_vcop_psort2_1step_kernel_custom
(
   int              niter1,
   int              niter2,
   int              niter3,
   int              ibase_0,
   int              ibase_1,
   int              in1ptr_w1,
   int              in1ptr_w2,
   int              in1ptr_w3,
   int              in2ptr_w1,
   int              in2ptr_w2,
   int              in2ptr_w3,
   int              obase_0,
   int              obase_1,
   int              outptr_w1,
   int              outptr_w2,
   int              outptr_w3,
   __vptr_int32     input,
   __vptr_int32     output,
   __vptr_int32     out_ofst,
   unsigned short   *pblock
);

void my_vcop_psort2_2steps_reverse_kernel_custom
(
   int               niter1,
   int               niter2,
   int               niter3,
   int               ibase_0,
   int               ibase_1,
   int               ibase_2,
   int               ibase_3,
   int               in1ptr_w1,
   int               in1ptr_w2,
   int               in1ptr_w3,
   int               in2ptr_w1,
   int               in2ptr_w2,
   int               in2ptr_w3,
   int               obase_0,
   int               obase_1,
   int               obase_2,
   int               obase_3,
   int               outptr_w1,
   int               outptr_w2,
   int               outptr_w3,
   __vptr_int32      input,
   __vptr_int32      output,
   __vptr_int32      out_ofst,
   unsigned short    *pblock
);

void my_vcop_psort2_2steps_kernel_custom
(
   int               niter1,
   int               niter2,
   int               niter3,
   int               ibase_0,
   int               ibase_1,
   int               ibase_2,
   int               ibase_3,
   int               in1ptr_w1,
   int               in1ptr_w2,
   int               in1ptr_w3,
   int               in2ptr_w1,
   int               in2ptr_w2,
   int               in2ptr_w3,
   int               obase_0,
   int               obase_1,
   int               obase_2,
   int               obase_3,
   int               outptr_w1,
   int               outptr_w2,
   int               outptr_w3,
   __vptr_int32      input,
   __vptr_int32      output,
   __vptr_int32      out_ofst,
   unsigned short    *pblock
);


void my_vcop_psort2_3steps_reverse_kernel_custom
(
   int               niter1,
   int               niter2,
   int               niter3,
   int               ibase_0,
   int               ibase_1,
   int               ibase_2,
   int               ibase_3,
   int               ibase_4,
   int               ibase_5,
   int               ibase_6,
   int               ibase_7,
   int               in1ptr_w1,
   int               in1ptr_w2,
   int               in1ptr_w3,
   int               in2ptr_w1,
   int               in2ptr_w2,
   int               in2ptr_w3,
   int               obase_0,
   int               obase_1,
   int               obase_2,
   int               obase_3,
   int               obase_4,
   int               obase_5,
   int               obase_6,
   int               obase_7,
   int               outptr_w1,
   int               outptr_w2,
   int               outptr_w3,
   __vptr_int32      input,
   __vptr_int32      output,
   __vptr_int32      out_ofst,
   unsigned short    *pblock
);

void my_vcop_psort2_3steps_kernel_custom
(
   int                niter1,
   int                niter2,
   int                niter3,
   int                ibase_0,
   int                ibase_1,
   int                ibase_2,
   int                ibase_3,
   int                ibase_4,
   int                ibase_5,
   int                ibase_6,
   int                ibase_7,
   int                in1ptr_w1,
   int                in1ptr_w2,
   int                in1ptr_w3,
   int                in2ptr_w1,
   int                in2ptr_w2,
   int                in2ptr_w3,
   int                obase_0,
   int                obase_1,
   int                obase_2,
   int                obase_3,
   int                obase_4,
   int                obase_5,
   int                obase_6,
   int                obase_7,
   int                outptr_w1,
   int                outptr_w2,
   int                outptr_w3,
   __vptr_int32       input,
   __vptr_int32       output,
   __vptr_int32       out_ofst,
   unsigned short     *pblock
);

void my_vcop_remove_ex_col_custom
(
   __vptr_int32       input,
   __vptr_int32       output,
   int                nitems,
   unsigned short     *pblock
);
#endif










