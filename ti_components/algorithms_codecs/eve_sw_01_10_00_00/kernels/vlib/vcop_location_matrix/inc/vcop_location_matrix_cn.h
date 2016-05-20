/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_location_matrix_cn.h                                            */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*         This is the c-reference header for the                           */
/*         vcop_location_matrix  kernel                                     */
/*                                                                          */
/*                                                                          */
/*     @version 0.1 (May 2014) : Base version.                              */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_LOCATION_MATRIX_CN
#define _VCOP_LOCATION_MATRIX_CN  1

void vcop_vec_L_matrix_u8_Mag_cn
(
    unsigned char *    pBin,
    unsigned char *    pMag,
    unsigned char *    pOut,
    unsigned short  width,
    unsigned short  height,
    unsigned short  numBins
);

void vcop_vec_L_matrix_u16_Mag_cn
(
    unsigned char *    pBin,
    unsigned short *   pMag,
    unsigned short *   pOut,
    unsigned short  width,
    unsigned short  height,
    unsigned short  numBins
);
#endif /* _VCOP_LOCATION_MATRIX_CN */

