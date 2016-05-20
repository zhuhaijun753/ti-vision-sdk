/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_yuv_scalar_cn.h.h                                               */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*         This is the c-reference header for the                           */
/*         YUV scalar  kernel                                               */
/*                                                                          */
/*                                                                          */
/*     @version 0.1 (Dec 2014) : Base version.                              */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_LOCATION_MATRIX_CN
#define _VCOP_LOCATION_MATRIX_CN  1

/* generic re-sizer for 8 bit Luma Image */
void vcop_resize_cn_y(uint8_t * inImage, uint8_t * outImage, uint16_t inWidth, uint16_t inHeight, uint16_t inPitch, uint16_t outWidth, uint16_t outHeight, uint16_t outPitch, uint16_t scaleRatioQ12,uint16_t srQShift,uint16_t fpQShift);
/* 8 bit Luma Image re-sizer. Vertical re-sizer followed by Horizontal Re-sizer*/
void vcop_resize_cn_y_s(uint8_t * inImage, uint8_t * outImage, uint16_t inWidth, uint16_t inHeight, uint16_t inPitch, uint16_t outWidth, uint16_t outHeight, uint16_t outPitch, uint16_t scaleRatioQ12,uint16_t srQShift,uint16_t fpQShift);
/* generic re-sizer for 8 bit Interleaved chroma Image */
void vcop_resize_cn_uv(uint8_t * inImage, uint8_t * outImage, uint16_t inWidth, uint16_t inHeight, uint16_t inPitch, uint16_t outWidth, uint16_t outHeight, uint16_t outPitch, uint16_t scaleRatioQ12,uint16_t srQShift,uint16_t fpQShift);
/* 8 bit  Interleaved chroma Image re-sizer. Vertical re-sizer followed by Horizontal Re-sizer*/
void vcop_resize_cn_uv_s(uint8_t * inImage, uint8_t * outImage, uint16_t inWidth, uint16_t inHeight, uint16_t inPitch, uint16_t outWidth, uint16_t outHeight, uint16_t outPitch, uint16_t scaleRatioQ12,uint16_t srQShift,uint16_t fpQShift);

/* Luma vertical resize : Natrual C-version of Kernel to utilizing look tables for resizing */
void vcop_scaler_luma_vertical_cn(uint8_t *inBlkPtr, uint8_t *interBlkPtr, uint16_t *yIndexPtr, uint8_t *yFracPtr, uint16_t inBlockWidth, uint16_t blockHeight,uint16_t LUT_DATA_SIZE,uint16_t fpQShift);
/* Luma Horizontal resize : Natrual C-version of Kernel to utilizing look tables for resizing */
void vcop_scaler_luma_Horizontal_cn(uint8_t *interBlkPtr, uint8_t *outBlkPtr, uint16_t *xIndexPtr, uint8_t *xFracPtr, uint16_t inBlockWidth, uint16_t blockWidth, uint16_t blockHeight,uint16_t LUT_DATA_SIZE,uint16_t fpQShift);
/* Chroma vertical resize : Natrual C-version of Kernel to utilizing look tables for resizing */
void vcop_scaler_chroma_vertical_cn(uint8_t *inBlkPtr, uint8_t *interBlkPtr, uint16_t *yIndexPtr, uint8_t *yFracPtr, uint16_t inBlockWidth, uint16_t blockHeight,uint16_t LUT_DATA_SIZE,uint16_t fpQShift);
/* Chroma Horizontal resize : Natrual C-version of Kernel to utilizing look tables for resizing */
void vcop_scaler_chroma_Horizontal_cn(uint8_t *interBlkPtr, uint8_t *outBlkPtr, uint16_t *xIndexPtr, uint8_t *xFracPtr, uint16_t inBlockWidth, uint16_t blockWidth, uint16_t blockHeight,uint16_t LUT_DATA_SIZE,uint16_t fpQShift);

#endif /* _VCOP_LOCATION_MATRIX_CN */

