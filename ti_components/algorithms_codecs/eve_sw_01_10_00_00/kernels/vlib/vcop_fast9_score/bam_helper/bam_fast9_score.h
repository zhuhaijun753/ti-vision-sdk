/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_fast9_score.h
 *
 *  @brief      This header defines interfaces for integrating fast9 score
 *              into BAM.
 */

#ifndef BAM_FAST9_SCORE_H_
#define BAM_FAST9_SCORE_H_

typedef struct bam_fast9_score_args
{
    uint16_t     num_features;
    uint32_t       total_features;
    uint8_t        thr;
    uint8_t      score_method;
} BAM_Fast9_Score_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_fast9scoreHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_fast9scoreExecFunc;

extern BAM_KernelInfo gBAM_TI_fast9scoreKernel;

#define BAM_FAST9_SCORE_INPUT_PORT_IN     (0)

#define BAM_FAST9_SCORE_OUTPUT_PORT_SCORE (0)


#endif /* BAM_FAST9_SCORE_H_ */
