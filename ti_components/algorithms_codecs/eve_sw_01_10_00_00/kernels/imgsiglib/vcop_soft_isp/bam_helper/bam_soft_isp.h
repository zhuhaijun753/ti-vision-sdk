/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_soft_isp.h
 *
 *  @brief      This header defines interfaces for integrating software
 *              Image Signal Processor (ISP) into BAM.
 */

#ifndef BAM_SOFT_ISP_H_
#define BAM_SOFT_ISP_H_

#define SOFT_ISP_MAX_BLOCK_WIDTH  (68U)
#define SOFT_ISP_MAX_BLOCK_HEIGHT (68U)
#define SOFT_ISP_MAX_BLOCK_STRIDE (68U)

typedef struct
{
    uint16_t  blockWidth;
    uint16_t  blockHeight;
    uint16_t  blockStride;

    uint8_t   rPosition;
    uint8_t   sensorBitDepth;

    /* Decompanding parameters */
    uint8_t   enableDecompand;
    uint16_t  p1;
    uint16_t  pk;
    uint8_t   r1;
    uint16_t  r1r2;

    /* Black clamp and C balance */
    uint16_t *blackClamp;
    uint16_t *cBalanceGain;
    uint8_t   cBalanceShift;

    /* Extract R pixels */
    uint8_t   enableExtractR;

    /* GBCE parameter */
    uint8_t   gbceMethod;
    uint32_t *gbceToneCurveAddr;

    /* Stats Collection parameters */
    uint8_t   enableStats;
    uint16_t  saturationLimit;
} BAM_SoftIsp_Args;

typedef struct
{
    uint8_t   rPosition;
    uint8_t   sensorBitDepth;

    /* Decompanding parameters */
    uint8_t   enableDecompand;
    uint16_t  p1;
    uint16_t  pk;
    uint8_t   r1;
    uint16_t  r1r2;

    /* Black clamp and C balance */
    uint16_t *blackClamp;
    uint16_t *cBalanceGain;
    uint8_t   cBalanceShift;

    /* Extract R pixels */
    uint8_t   enableExtractR;

    /* GBCE parameter */
    uint8_t   gbceMethod;
    uint32_t *gbceToneCurveAddr;

    /* Stats Collection parameters */
    uint8_t   enableStats;
    uint16_t  saturationLimit;
} BAM_SoftIsp_CtlArgs;

extern BAM_KernelHelperFuncDef gBAM_TI_softIspHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_softIspExecFunc;

extern BAM_KernelInfo gBAM_TI_softIspKernel;

typedef enum
{
  BAM_SOFT_ISP_INPUT_RC_PORT   =   0,
  BAM_SOFT_ISP_INPUT_CC_PORT,
  BAM_SOFT_ISP_NUM_INPUT_BLOCKS
} eBAM_SOFT_ISP_INPUT_PORTS;

typedef enum
{
  BAM_SOFT_ISP_OUTPUT_RC_PORT    =  0,
  BAM_SOFT_ISP_OUTPUT_CC_PORT,
  BAM_SOFT_ISP_OUTPUT_R_PORT,
  BAM_SOFT_ISP_OUTPUT_STATS_PORT,
  BAM_SOFT_ISP_NUM_OUTPUT_BLOCKS
} eBAM_SOFT_ISP_OUTPUT_PORTS;

#endif /* BAM_SOFT_ISP_H_ */

