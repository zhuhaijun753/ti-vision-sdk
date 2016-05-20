/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#ifndef _GLCM_REF_CN_H_
#define _GLCM_REF_CN_H_

#include <stdint.h>

int32_t glcm_ref_cn(
    uint8_t  *pInput,
    uint16_t *pCoMatrix,
    uint16_t  imageWidth,
    uint16_t  imageHeight,
    uint16_t  imagePitch,
    uint8_t   loPixelVal,
    uint8_t   hiPixelVal,
    uint8_t   numLevels,
    uint8_t   numDirections,
    int8_t   *rowOffset,
    int8_t   *colOffset
);

#endif /*_GLCM_REF_CN_H_*/

