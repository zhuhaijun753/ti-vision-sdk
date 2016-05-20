/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_harrisScore_32_7x7_cn                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     int vcop_harrisScore_32_7x7_cn                                      */
/*     (                                                                    */
/*        const short *  gradX,                                             */
/*        const short *  gradY,                                             */
/*        int width,                                                        */
/*        int height,                                                       */
/*        int *  outm,                                             */
/*        short k                                                           */
/*     )                                                                    */
/*                                                                          */
/*     gradX    :  gradient value in X direction                            */
/*     gradY    :  gradient value in Y direction                            */
/*     width    :  width of the input image                                 */
/*     height   :  height of the input image                                */
/*     outm     :  harris score output                                      */
/*     k        :  harris score scaling factor                              */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*            This routine accepts a gradient inputs and returns a 32-bit   */
/*     harris score for each pixel of the input image.                      */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2013 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef _vcop_harrisScore_32_7x7_CN
#define _vcop_harrisScore_32_7x7_CN  1

int vcop_harrisScore_32_7x7_cn
(
    const short *  gradX,
    const short *  gradY,
    int width,
    int height,
    unsigned int srcPitch,
    unsigned int dstPitch,
    unsigned char windowSize,
    int *  outm,
    unsigned short k
);

/* ==================================================
 *  @function     vcop_harrisScore_32_methodB_cn
 *
 *  @desc     This function calculates the Harris Score defined as the trace of the matrix :
 *                 Score = gradX^2 + gradY^2
 *
 *  @inputs   This kernel takes following Inputs
 *                  gradX :
 *                          Pointer to the gradient in X direction. Size of this buffer should be inBlockWidth * inBlockHeight * sizeof(uint16_t)
 *                  gradY :
 *                          Pointer to the gradient in Y direction. Size of this buffer should be inBlockWidth * inBlockHeight * sizeof(uint16_t)
 *                  inBlockWidth :
 *                          Width of the input block
 *                  inBlockHeight :
 *                          Height of the input block
 *                  srcPitch :
 *                          Pitch of the input block
 *                  dstPitch :
 *                          Pitch for the output score
 *                  windowSize :
 *                          Size of the window. Should be an odd number
 *
 *  @outputs   This kernel produce following outputs
 *                  outm :
 *                          Pointer to the buffer which will store the score caluclated by this kernel. Size of this buffer
 *                          should be (inBlockWidth - (windowSize - 1) )* (inBlockWidth - (windowSize - 1) ) * sizeof(uint32_t))
 *
 *  @constraints Following constraints
 *
 *  @return    NONE
 *
 *  =======================================================
 */
int vcop_harrisScore_32_methodB_cn
(
    const int16_t *gradX,
    const int16_t *gradY,
    uint16_t      inBlockWidth,
    uint16_t      inBlockHeight,
    uint16_t      srcPitch,
    uint16_t      dstPitch,
    uint8_t       windowSize,
    uint32_t      *outm
);

#endif

/* ======================================================================== */
/*            End of file:  vcop_harrisScore_32_7x7_c.h                    */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
