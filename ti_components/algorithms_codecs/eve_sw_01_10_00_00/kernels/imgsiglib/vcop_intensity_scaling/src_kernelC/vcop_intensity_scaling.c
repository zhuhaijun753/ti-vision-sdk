/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include <stdint.h>
#include <stdio.h>

#include "vcop_intensity_scaling.h"

int32_t prepare_lut
(
    uint8_t loPixelVal,
    uint8_t hiPixelVal,
    uint8_t numLevels,
    uint8_t numTables,
    uint8_t scalingLUT[]
)
{
  int32_t status = 0;
  uint32_t i, j, k, idx, lut_idx;
  uint16_t curBin;
  uint8_t pixRange;

  if((numTables != 1U) && (numTables != 8U)) {
#ifdef __DEBUG
    printf("Unsupported number of tables.\n");
#endif
    status = GLCM_ERROR_UNSUPPORTED_NUM_LUT_TABLES;

    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto EXIT;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

  pixRange = (hiPixelVal - loPixelVal);

  /* Prepare the LUT for intensity scaling */
  for(i = 0; i < 256U/(32U/numTables); i++) {
    for(k = 0; k < numTables; k++) {
      for(j = 0; j < (32U/numTables); j++) {
        idx = i*(32U/numTables) + j;
        lut_idx = i*32U + k*4U + j;
        if(idx <= loPixelVal) {
          /* Pixels less than loPixelVal maps to first bin*/
          scalingLUT[lut_idx] = 0;
        }
        else if(idx >= hiPixelVal){
          /* Pixels greater than hiPixelVal maps to last bin*/
          scalingLUT[lut_idx] = numLevels - 1U;
        }
        else {
          /* Equi-sized bins within pixRange with loPixelVal mapping to 0 and
             hiPixelVal mapping to (numLevels-1) */
          curBin = (uint16_t)((idx - loPixelVal)*numLevels)/pixRange;
          if( curBin  > ((uint16_t)numLevels - (uint16_t)1)) {
            curBin = ((uint16_t)numLevels - (uint16_t)1);
          }
          scalingLUT[lut_idx] = curBin;
        }
      }
    }
  }

EXIT:
  return status;
}
