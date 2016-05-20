/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#include "stereoVision_config.h"
#include "remap_common.h"

int32_t rectify(sstereoVision_Config *gConfig_stereoVision, uint8_t *leftSrc, uint8_t*rightSrc, uint8_t *leftDst, uint8_t *rightDst);

void rectify_getBlockMap(uint8_t **srcBlkMap, uint32_t *blockMap_LEN, sConvertMap *maps, uint8_t *convertedMap);
