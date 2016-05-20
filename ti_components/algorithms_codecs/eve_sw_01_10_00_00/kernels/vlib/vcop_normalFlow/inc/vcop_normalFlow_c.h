/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_normalFlow_cn                                                   */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_normalFlow_c(                                              */
/*                              short imDiff[],       // SQ15.0             */  
/*                              short Emag[],         // SQ15.0             */  
/*                              short Ex[],           // SQ15.0             */
/*                              short Ey[],           // SQ15.0             */  
/*                              short LUT[],          // QS0.15             */  
/*                              short T,              // SQ15.0             */  
/*                              char  numEls,           // SQ31.0           */  
/*                              short normalFlowU[],  // SQ8.7              */  
/*                              short normalFlowV[])  // SQ8.7              */  
/*     );                                                                   */
/*                                                                          */
/*     imdiff       :  image difference values (SQ15.0)                     */
/*     Emag         :  gradient magnitude values (SQ15.0)                   */
/*     Ex           :  x-direction gradient  (SQ15.0)                       */    
/*     Ey           :  y-direction gradient  (SQ15.0)                       */
/*     LUT          :  Look-Up-Table containing values for integer          */
/*                                      division (SQ0.15)                   */  
/*     T              :  Threshold on gradient magnitude                    */
/*     numEls       :  Number of pixels to process                          */
/*     normalFlowU    :  Normal flow vector output in x-direction           */
/*     normalFlowV    :  Normal flow vector output in y-direction           */
/*                                                                          */
/*     Returns        :  None or void.                                      */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine ocmputes for every pixel in the image, motion   */
/*     vectors parallel to the gradient direction at each pixel.            */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*     (1) The LUT array should hold values such that LUT[n] = X, where X   */
/*   is 1/n represented in SQ0.15 format.                                   */
/*   (2) The threshold, T, on gradient magnitude ensures that only those    */
/*   pixels with gradient madnitude greater than T will be processed.       */
/*   Normal flow values for pixels that do not pass the threshold is 0.     */
/*   (3) Minimum number of pixels allowed is 20 (numEls >=20)               */
/*   (4) Number of pixels to be processed should be a multiple of 4.        */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2011 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef _vcop_normalFlow_CN
#define _vcop_normalFlow_CN  1

void VCOP_normalFlow_cn
(
      short imDiff[],       // SQ15.0
      short Emag[],         // SQ15.0
      short Ex[],           // SQ15.0
      short Ey[],           // SQ15.0
      short LUT[],          // QS0.15
      short T,              // SQ15.0
      char  numEls,         // SQ31.0
      short normalFlowU[],  // SQ8.7
      short normalFlowV[]   // SQ8.7
);
#endif

/* ======================================================================== */
/*  End of file:  vcop_normalFlow_c.h                                       */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
