/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_dma_one_shot_node_int.h
 *
 *  @brief      This header defines internal structures  for integrating block average 2x2 into BAM, used for image pyamid applet.
 */

#ifndef BAM_DMA_ONESHOT_NODE_INT_H_
#define BAM_DMA_ONESHOT_NODE_INT_H_


#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_dma_one_shot_node.h"

/* CHECK_MISRA("-20.2")  -> Disable rule 20.2 */
/* Usage of a reserved name for naming a language entity */
/* Deviation allowed because _bam_dma_oneShot_context is not reserved */
typedef struct _bam_dma_oneShot_context
{

    BAM_DMA_OneShot_Args kernelArgs;
    int32_t triggerTimer;
    uint8_t oneShotDone;
    int32_t blockCount;
} BAM_DMA_OneShot_Context;
/*RESET_MISRA("20.2")  -> Reset rule 20.2 */

#endif
