/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_block_statistics.h
 *
 *  @brief      This header defines interfaces for integrating block statistics
 *              into BAM.
 */

#ifndef BAM_BLOCK_STATISTICS_H_
#define BAM_BLOCK_STATISTICS_H_

typedef struct bam_block_statistics_args
{
    uint16_t     blockStride;
    uint16_t     blockWidth;
    uint16_t     blockHeight;
    uint16_t     statBlockWidth;
    uint16_t     statBlockHeight;
} BAM_Block_Statistics_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_blockStatisticsHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_blockStatisticsExecFunc;

extern BAM_KernelInfo gBAM_TI_blockStatisticsKernel;

#define BAM_BLOCK_STATISTICS_INPUT_PORT     (0U)

#define BAM_BLOCK_STATISTICS_OUTPUT_PORT_MIN    (0U)
#define BAM_BLOCK_STATISTICS_OUTPUT_PORT_MAX    (1U)
#define BAM_BLOCK_STATISTICS_OUTPUT_PORT_MEAN   (2U)
#define BAM_BLOCK_STATISTICS_OUTPUT_PORT_VAR    (3U)

#define BAM_BLOCK_STATISTICS_TEMP_PARAM     (0U)
#define BAM_BLOCK_STATISTICS_TEMP_MIN_MAX   (1U)
#define BAM_BLOCK_STATISTICS_TEMP_SUM       (2U)
#define BAM_BLOCK_STATISTICS_TEMP_SUM_SQ_B  (3U)

#endif /* BAM_BLOCK_STATISTICS_H_ */
