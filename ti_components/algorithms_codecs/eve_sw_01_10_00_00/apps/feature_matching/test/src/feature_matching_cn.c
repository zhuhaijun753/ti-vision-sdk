/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "vcop_hamming_distance_cn.h"

#define PIX_SORT(a,b) { if ((a)>(b)) PIX_SWAP((a),(b)); }
#define PIX_SWAP(a,b) { uint32_t temp=(a);(a)=(b);(b)=temp; }

int32_t feature_matching_cn(
    uint8_t  *pFeatureDescriptors_1,
    uint8_t  *pFeatureDescriptors_2,
    uint16_t *pCorrespondenceList,
    uint16_t  numDescriptors1,
    uint16_t  numDescriptors2,
    uint16_t  descriptorLength,
    uint16_t  minDistanceThres,
    uint16_t  matchConfidence)  // U1.15
{
  int32_t status = 0;
  uint32_t i, j;
  uint32_t currDist, minDist0, minDist1;
  uint16_t minHamDist0, minHamDist1;
  uint32_t *pHammingDistance;

  pHammingDistance = (uint32_t *)malloc(numDescriptors2*sizeof(uint32_t));

  for(i = 0; i < numDescriptors1; i++) {
    vcop_hamming_distance_cn(pFeatureDescriptors_2, pFeatureDescriptors_1 +
         i*descriptorLength, descriptorLength, numDescriptors2, 0,
         descriptorLength, pHammingDistance, 1, 0);

    minDist0 = 0xFFFFFFFF;
    minDist1 = 0xFFFFFFFF;

    for(j = 0; j < numDescriptors2; j++) {
      currDist = pHammingDistance[j];
      PIX_SORT(minDist0, currDist);
      PIX_SORT(minDist1, currDist);
    }

    pCorrespondenceList[i] = 0xFFFF;
    minHamDist0 = minDist0 >> 16;
    minHamDist1 = minDist1 >> 16;
    if((minHamDist0 <= minDistanceThres) && (minHamDist0 <= (((1<<15) -
        matchConfidence)*minHamDist1)>>15)) {
      pCorrespondenceList[i] = (uint16_t)(minDist0 & 0x0000FFFF);
    }
  }

  free(pHammingDistance);

  return (status);
}

