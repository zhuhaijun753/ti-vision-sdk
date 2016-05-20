/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef VCOP_YUV420_FIR2D_SEPARABLE_CN_H_
#define VCOP_YUV420_FIR2D_SEPARABLE_CN_H_  1

#include <stdint.h>

void vcop_yuv420_fir2d_separable_y_cn
(
    uint8_t *        inputPtr,     // input data pointer
    int8_t *        horzCoeffPtr,    // horizontal coef data pointer
    int8_t *        vertCoeffPtr,    // vertical  coef data pointer
    uint16_t   blkw,         // width of input block, in elements
    uint16_t  lofst,        // offset between input lines, in elems
    uint16_t  blkh,         // height of input block
    uint16_t  numCoef,     // width of coef block, in elements
    uint8_t * outputPtr,   // output data pointer
    uint16_t rndBits      // bit position for rounding
);

#endif /* VCOP_YUV420_FIR2D_SEPARABLE_CN_H_*/

/* ======================================================================== */
/*  End of file:  vcop_yuv420_fir2d_separable_cn.h                   */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */



