/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_prune_big_list.h
 *  @version 0.0 (Dec 2013) : Base version.
 *  @version 0.1 (May 2014) : Updated as per control node requirements
 *  @brief      This header defines interfaces for integrating  prune
 *              big list function into BAM.
 */

#ifndef BAM_PRUNE_BIG_LIST_H_
#define BAM_PRUNE_BIG_LIST_H_

#define BAM_PRUNE_BIG_LIST (2048U)

typedef struct bam_prune_big_list_cntrlArgs
{
    uint16_t    offset;
    uint16_t    bestNFeaturesOut;
}BAM_Prune_Big_List_ctrlArgs;

typedef struct bam_prune_big_list_args
{
    uint16_t    maxFeatures;
    uint16_t    offset;
    uint16_t    bestNFeaturesOut;
    uint16_t    threshold;
} BAM_Prune_Big_List_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_prune_big_listHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_prune_big_listExecFunc;

extern BAM_KernelInfo gBAM_TI_prune_big_listKernel;

#define BAM_PRUNE_BIG_LIST_INPUT_PORT_IN_LIST       (0)
#define BAM_PRUNE_BIG_LIST_INPUT_PORT_IDX_LIST      (1)
#define BAM_PRUNE_BIG_LIST_OUTPUT_PORT_OUT_LIST     (0)
#define BAM_PRUNE_BIG_LIST_OUTPUT_PORT_SIZE_OUT     (1)
#define BAM_PRUNE_BIG_LIST_TEMP_PARAM               (0)

#endif /* BAM_PRUNE_BIG_LIST_H_ */
