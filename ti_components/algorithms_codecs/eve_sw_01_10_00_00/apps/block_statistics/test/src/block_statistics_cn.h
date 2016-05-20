/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/* ===========================================================================*/
/*   @file   : block_statistics_cn.h                                          */
/*                                                                            */
/*   @brief  : This file contains all functions calls for block statistics    */
/*             reference                                                      */
/*                                                                            */
/*   @version 0.2 (Aug 2014) : Base version.                                  */
/*                                                                            */
/*============================================================================*/

#ifndef _BLOCK_STAT_CN_H
#define _BLOCK_STAT_CN_H

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <vcop.h>
#pragma RESET_MISRA ("required")

#include <xdais_types.h>
#include "iblock_statistics_ti.h"

void blockStat_cn(
    BLOCK_STATISTICS_TI_CreateParams *createParams,
    uint16_t imageStride,
    uint8_t  *inbuff,
    uint8_t  *refMinOutbuff,
    uint8_t  *refMaxOutbuff,
    uint16_t *refMeanOutbuff,
    uint32_t *refVarOutbuff);

#endif /* _BLOCK_STAT_CN_H */
