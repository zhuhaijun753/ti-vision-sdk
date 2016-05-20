/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_horizontal_non_max_suppression.h
 *  @version 0.0 (Dec 2013) : Base version.
 *  @version 0.1 (May 2014) : Updated as per control node requirements
 *
 *  @brief      This header defines interfaces for integrating horizontal nms
 *              into BAM.
 */

#ifndef BAM_HORIZONTAL_NON_MAX_SUPPRESSION_H_
#define BAM_HORIZONTAL_NON_MAX_SUPPRESSION_H_

typedef struct bam_horizontal_non_max_suppression_cntrlArgs
{
    uint16_t     num_corners_in;
}BAM_Horizontal_Non_Max_Suppression_ctrlArgs;

typedef struct bam_horizontal_non_max_suppression_args
{
    uint16_t     max_corners;
    uint16_t     num_corners_in;
} BAM_Horizontal_Non_Max_Suppression_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_horizontalnonmaxsuppressionHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_horizontalnonmaxsuppressionExecFunc;

extern BAM_KernelInfo gBAM_TI_horizontalnonmaxsuppressionKernel;

#define BAM_HORIZONTAL_NON_MAX_SUPPRESSION_INPUT_PORT_XY     (0)
#define BAM_HORIZONTAL_NON_MAX_SUPPRESSION_INPUT_PORT_SCORE  (1)

#define BAM_HORIZONTAL_NON_MAX_SUPPRESSION_OUTPUT_PORT_XY    (0)
#define BAM_HORIZONTAL_NON_MAX_SUPPRESSION_OUTPUT_PORT_SCORE (1)

#endif /* BAM_HORIZONTAL_NON_MAX_SUPPRESSION_H_ */
