/* ======================================================================
 *   Copyright (C) 2013 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */
/**
 *   Component:         fatlib
 *
 *   Filename:               hsmmcsd_API.h.
 *
 *   Description:           This file contain API functions to init the MMCSD
 ****device & FAT filesystem
 */
#ifndef HSMMCSD_API_H_
#define HSMMCSD_API_H_

/****************************************************************
 *  INCLUDE FILES
 ****************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>
#include "fatfs/ff.h"
#include "soc_defines.h"

void HSMMCSDFsMount(uint32_t driveNum, void *ptr);
void HSMMCSDFsProcessCmdLine(void);
int32_t HSMMCSDInit(MMC_INST_t num);

#ifdef __cplusplus
}
#endif

#endif /* HSMMCSD_API_H_ */

