/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_remap_bilinear_interpolateUV_int.h
 *
 *  @brief      This header defines internal structures for integrating Remap Bilinear
 *              interpolate 8 bit kernel into BAM.
 */
#ifndef BAM_REMAP_BILINEAR_INTERPOLATEUV_INT_H_
#define BAM_REMAP_BILINEAR_INTERPOLATEUV_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_remap_bilinear_INTERPOLATEUV.h"

#define NUM_IN_BLOCKS       (2U)
#define NUM_OUT_BLOCKS      (1U)
#define NUM_INTERNAL_BLOCKS (4U)

#define REMAP_BILINEAR_INTERPOLATEUV_IN_DATA_IDX  (BAM_REMAP_BILINEAR_INTERPOLATEUV_INPUT_PORT)   /* 0 */
#define REMAP_BILINEAR_INTERPOLATEUV_IN_LUT_IDX   (BAM_REMAP_BILINEAR_INTERPOLATEUV_LUT_PORT)     /* 1 */


#define REMAP_BILINEAR_INTERPOLATEUV_OUT_DATA_IDX               (0U)   /* 0 */

#define REMAP_BILINEAR_INTERPOLATEUV_INTERTNAL_PARAMS_IDX       (0U) /* 0 */
#define REMAP_BILINEAR_INTERPOLATEUV_INTERTNAL_SCRATCH_IDX      (1U) /* 1 */
#define REMAP_BILINEAR_INTERPOLATEUV_INTERTNAL_SCRATCH_HBUF_IDX (3U) /* 2 */
#define REMAP_BILINEAR_INTERPOLATEUV_INTERTNAL_INDATA_LUT       (2U)

typedef struct bam_remapbilinearinterpolateUV_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_RemapBilinearinterpolateUV_Args kernelArgs;
    BAM_KernelCustom kernelCustom;
} BAM_RemapBilinearinterpolateUV_Context;

#endif /* BAM_REMAP_BILINEAR_INTERPOLATEUV_INT_H_*/

