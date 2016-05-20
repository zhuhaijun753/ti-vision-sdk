/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 This function prepares an LUT which has 'numLevels' equi-sized
 bins ranging from [loPixelVal, hiPixelVal]. All pixels less than
 loPixelVal will be put into first bin (0) and all pixels greater
 than hiPixelVal will be binned to last bin (numLevels-1).
*/

#ifndef VCOP_INTENSITY_SCALING_H_
#define VCOP_INTENSITY_SCALING_H_

#define GLCM_ERROR_UNSUPPORTED_NUM_LUT_TABLES (-1)

int32_t prepare_lut(
    uint8_t loPixelVal,
    uint8_t hiPixelVal,
    uint8_t numLevels,
    uint8_t numTables,
    uint8_t scalingLUT[]);

#endif /* VCOP_INTENSITY_SCALING_H_ */

