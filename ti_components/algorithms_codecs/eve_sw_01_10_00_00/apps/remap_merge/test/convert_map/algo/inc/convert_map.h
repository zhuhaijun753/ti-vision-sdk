/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef CONVERTMAP_H
#define CONVERTMAP_H

#ifdef __cplusplus
    extern "C" {
#endif

#include <stdint.h>
#include "remap_common.h"


/*!

  @struct convertMapBlockInfo

  @brief  This structure contains the parameters which assist Remap module to
          perform block level Pixel Remap. It is produced by convert map module
          and cosumed by Remap.


  @param collectStatFlag [In]
         0: do not collect statistics, 1: collect statistics
  @param maxWidthRatio  [out]
         maximum of all the ratios between input block's width output block's
         width is returned here
  @param minWidthRatio  [out]
         minimum of all the ratios between input block's width output block's
         width is returned here
  @param averWidthRatio [out]
         average of all the ratios between input block's
         width output block's width is returned here
  @param maxHeightRatio [out]
         maximum of all the ratios between input block's height
         output block's height is returned here
  @param minHeightRatio [out]
         minimum of all the ratios between input block's height
         output block's height is returned here
  @param averHeightRatio[out]
         average of all the ratios between input block's height
         output block's height is returned here

*/

typedef struct {
    uint8_t collectStatFlag;
    float maxWidthRatio;
    float minWidthRatio;
    float averWidthRatio;
    float maxHeightRatio;
    float minHeightRatio;
    float averHeightRatio;
} RemapStat;


/*!

  @func convertMap_tileApproach_getMemorysizeBlockMap

  @brief  This function retruns the memory size needed by Block Map

*/
int32_t convertMap_tileApproach_getMemorysizeBlockMap(sConvertMap *maps);


/*!

  @func convertMap_tileApproach

  @brief  This function perform the LUT table conversion from Frame format
          to block format
  @param  maps [In]
          It is pointer to memory are to hold block level LUT
          @sa sConvertMap
  @param  stat
          It is pointer to memory are to hold Statistics for Remap
          @sa RemapStat
@param  enableMerge
          It is a Boolean to input if Merge is enabled. It will be used for optimization.
          @sa uint8_t

*/
int32_t convertMap_tileApproach(sConvertMap *maps, RemapStat *stat, void *memLUT, uint8_t enableMerge);


/*!

  @func convertMap_tileApproach_getMemorysizeBlockMap

  @brief  This function retruns the memory size needed by Block Map

*/
int32_t convertMap_bbApproach_getMemorysizeBlockMap(sConvertMap *maps);


/*!

  @func convertMap_tileApproach

  @brief  This function perform the LUT table conversion from Frame format
          to block format
  @param  maps [In]
          It is pointer to memory are to hold block level LUT
          @sa sConvertMap
  @param  stat
          It is pointer to memory are to hold Statistics for Remap
          @sa RemapStat
@param  enableMerge
          It is a Boolean to input if Merge is enabled. Will be used to calculate memory availability.
          @sa uint8_t

*/
int32_t convertMap_bbApproach(sConvertMap *maps, RemapStat *stat, void *memLUT);


#ifdef __cplusplus
 }
#endif

#endif
