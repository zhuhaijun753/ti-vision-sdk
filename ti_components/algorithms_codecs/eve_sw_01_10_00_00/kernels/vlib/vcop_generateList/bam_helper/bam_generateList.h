/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_generateList.h
 *
 *  @brief      This header defines interfaces for integrating generate list kernel into BAM.
 */

#ifndef BAM_GENERATE_LIST_H_
#define BAM_GENERATE_LIST_H_

typedef struct
{
    uint16_t width;
    uint16_t height;
    uint16_t inStride; /* must be multiple of 8 */
    uint16_t numHorzBlock;   /* number of horizontal blocks in the frame */
    uint16_t numVertBlock;   /* number of vertical blocks in the frame */
    uint16_t maxNumElmts;
    uint16_t offsetX;
    uint16_t offsetY;
    uint8_t qShift;
} BAM_GenerateList_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_generateListHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_generateListExecFunc;

extern BAM_KernelInfo gBAM_TI_generateListKernel;

#define BAM_GENERATELIST_INPUT_PORT                 0
#define BAM_GENERATELIST_OUTPUT_XY_PORT             0
#define BAM_GENERATELIST_OUTPUT_NUM_ELMNTS_PORT     1

#endif /* BAM_GENERATE_LIST_H_ */
