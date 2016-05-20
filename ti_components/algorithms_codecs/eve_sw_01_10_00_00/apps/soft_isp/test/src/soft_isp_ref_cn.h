/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#ifndef _SOFT_ISP_REF_CN_H_
#define _SOFT_ISP_REF_CN_H_

#include <stdint.h>

int32_t soft_isp_ref_cn(
    uint16_t *pInput,
    uint8_t  *pOutput,
    uint8_t  *pOutputR,
    uint8_t  *pStatsBuf,
    uint16_t  imageWidth,
    uint16_t  imageHeight,
    uint16_t  imagePitch,
    uint8_t   rPosition,
    uint8_t   sensorBitDepth,
    uint8_t   enableDecompand,
    uint16_t  pout1,
    uint16_t  pout2,
    uint8_t   slope1,
    uint16_t  slope2,
    uint16_t *blackClamp,
    uint16_t *cBalanceGain,
    uint8_t   cBalanceShift,
    uint8_t   enableExtractR,
    uint8_t   enableStats,
    uint16_t  statBlkWidth,
    uint16_t  statBlkHeight,
    uint16_t  saturationLimit,
    uint8_t   gbceMethod,
    uint8_t  *pGbceToneCurve
);

#endif /*_SOFT_ISP_REF_CN_H_*/

