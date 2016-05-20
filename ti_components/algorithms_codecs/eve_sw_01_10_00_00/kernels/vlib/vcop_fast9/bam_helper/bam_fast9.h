/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_fast9.h
 *
 *  @brief      This header defines interfaces for integrating FAST9 kernel
 *              into BAM.
 */

#ifndef BAM_FAST9_H_
#define BAM_FAST9_H_

/*--------------------------------------------------------------------*/
/* These are macros which are algorithm specfic and indicative to BAM */
/* to help decide the optimal block dimensions                        */
/*--------------------------------------------------------------------*/
#define FAST9_TI_BORDER_X (3U)
#define FAST9_TI_BORDER_Y (3U)
/*-------------------------------------------------------------------------*/
/* Keep the compute Block width multiple of 8 and don't aloow go below 64  */
/* Keep the compute Block height multiple of 8 and don't aloow go below 32 */
/*-------------------------------------------------------------------------*/

#define FAST9_TI_BLK_WIDTH_MAX  (96U + 2U * FAST9_TI_BORDER_X)
#define FAST9_TI_BLK_HEIGHT_MAX (32U + 2U * FAST9_TI_BORDER_Y)
#define FAST9_TI_BLK_WIDTH_MIN  (64U + 2U * FAST9_TI_BORDER_X)
#define FAST9_TI_BLK_HEIGHT_MIN (16U + 2U * FAST9_TI_BORDER_Y)


typedef struct bam_fast9_ctrlArgs
{
    uint16_t in_h;
    uint16_t in_w; /* Must be multiple fo 16 */
    uint16_t pitch;
    uint8_t threshold;
} BAM_Fast9_ctrlArgs;


typedef struct bam_fast9_args
{
  uint16_t in_h;
  uint16_t in_w; /* Must be multiple fo 16 */
  uint16_t pitch;
  uint8_t threshold;
} BAM_Fast9_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_fast9HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_fast9ExecFunc;

extern BAM_KernelInfo gBAM_TI_fast9Kernel;

#define BAM_FAST9_INPUT_PORT     (0)

#define BAM_FAST9_OUTPUT_PORT    (0)


#endif /* BAM_FAST9_H_ */

