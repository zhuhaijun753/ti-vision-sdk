/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_harrisScore_7x7_cn                                              */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     int vcop_harrisScore_7x7_cn                                          */
/*     (                                                                    */
/*        const short *  gradX,                                             */
/*        const short *  gradY,                                             */
/*        int width,                                                        */
/*        int height,                                                       */
/*        short *  outm,                                                    */
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
/*            This routine accepts a gradient inputs and returns            */
/*     harris score for each pixel of the input image.                      */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef _vcop_harrisScore_7x7_CN
#define _vcop_harrisScore_7x7_CN  1

int vcop_harrisScore_7x7_cn
(
  const short *  gradX,
  const short *  gradY,
  int width,
  int height,
  short *  outm,
  unsigned short k
);

#endif

/* ======================================================================== */
/*            End of file:  vcop_harrisScore_7x7_c.h                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */



