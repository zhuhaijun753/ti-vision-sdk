/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_yuv_scalar_int.h
 *
 *  @brief      This header defines internal structures  YUV Scalar kernel
 *              into BAM.
 */

#ifndef BAM_YUV_SCALAR_INT_H_
#define BAM_YUV_SCALAR_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_yuv_scalar.h"

#define NUM_IN_BLOCKS         3
#define NUM_OUT_BLOCKS        1
#define NUM_INTERNAL_BLOCKS   7

#define YUV_SCALAR_IN_IDX                          (BAM_YUV_SCALAR_INPUT_DATA_PORT       )                     
#define YUV_SCALAR_INDEX_IDX                       (BAM_YUV_SCALAR_INPUT_INDEX_PORT      )                     
#define YUV_SCALAR_FRAC_IDX                        (BAM_YUV_SCALAR_INPUT_FRAC_COEFF_PORT )                     
#define YUV_SCALAR_OUT_IDX                         (BAM_YUV_SCALAR_OUTPUT_DATA_PORT      )                    
#define YUV_SCALAR_INTERNAL_PARAMS_IDX_0           (0)        
#define YUV_SCALAR_INTERNAL_PARAMS_IDX_1           (1)        
#define YUV_SCALAR_INTERNAL_PARAMS_IDX_2           (2)        
#define YUV_SCALAR_INTERNAL_LUT_OUT_IDX            (3)     
#define YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_0_IDX    (4)     
#define YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_1_IDX    (5)     
#define YUV_SCALAR_INTERNAL_OFFSETS_IDX            (6)     


typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_yuv_scalar_Args kernelArgs;
    uint16_t transposeBlkWidth;
    BAM_KernelCustom scalarCopyKenel;
    BAM_yuv_scalar_Ctrl_Args ctrlArgs;
} BAM_YUV_Scalar_Context;

#endif /* BAM_YUV_SCALAR_INT_H_*/

