/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#ifndef _FEATURE_MATCHING_REF_CN_H_
#define _FEATURE_MATCHING_REF_CN_H_

#include <stdint.h>

int32_t feature_matching_cn(
    uint8_t  *pFeatureDescriptors_1,
    uint8_t  *pFeatureDescriptors_2,
    uint16_t *pCorrespondenceList,
    uint16_t  numDescriptors1,
    uint16_t  numDescriptors2,
    uint16_t  descriptorLength,
    uint16_t  minDistanceThres,
    uint16_t  matchConfidence
);

#endif /*_FEATURE_MATCHING_REF_CN_H_*/

