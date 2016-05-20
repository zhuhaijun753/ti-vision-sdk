/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#include "remapConvertTable_config.h"
#include "remap_common.h"

int32_t remapConvertTable(sremapConvertTable_Config * gConfig_RemapConvertTablet);

void remapConvertTable_getBlockMap(uint8_t **srcBlkMap, uint32_t *blockMap_LEN, sConvertMap *maps, uint8_t *convertedMap);
