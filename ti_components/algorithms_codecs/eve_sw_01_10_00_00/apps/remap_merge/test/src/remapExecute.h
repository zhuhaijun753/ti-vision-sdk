/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2015 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#include "remapExecute_config.h"
#include "remap_common.h"

int32_t remapExecute(sremapExecute_Config * gConfig_remapExecute, uint8_t *src, uint8_t *dst);

void remapExecute_getBlockMap(uint8_t **srcBlkMap, uint32_t *blockMap_LEN, sConvertMap *maps, uint8_t *convertedMap);
