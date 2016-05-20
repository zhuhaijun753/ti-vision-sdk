/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_nonMaxSuppress_mxn_S16bitPack_int.h
 *
 *  @brief      This header defines internal structures  for integrating non max suppression
 */
#ifndef BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INT_H_
#define BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_nonMaxSuppress_mxn_S16bitPack.h"


#define NONMAXSUPPRESS_MXN_S16BITPACK_NUM_IN_BLOCKS (BAM_NONMAXSUPPRESS_MXN_S16BITPACK_NUM_INPUT_BLOCKS)
#define NONMAXSUPPRESS_MXN_S16BITPACK_NUM_OUT_BLOCKS (BAM_NONMAXSUPPRESS_MXN_S16BITPACK_NUM_OUTPUT_BLOCKS)
#define NONMAXSUPPRESS_MXN_S16BITPACK_NUM_INTERNAL_BLOCKS (BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_NUM_BLOCK)

typedef struct bam_nonMaxSuppress_mxn_s16bitpack_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NONMAXSUPPRESS_MXN_S16BITPACK_NUM_INTERNAL_BLOCKS];
    void *pInBlock[NONMAXSUPPRESS_MXN_S16BITPACK_NUM_IN_BLOCKS];
    void *pOutBlock[NONMAXSUPPRESS_MXN_S16BITPACK_NUM_OUT_BLOCKS];
    BAM_NonMaxSuppress_mxn_S16bitPack_CtlArgs ctrlArgs;
} BAM_NonMaxSuppress_mxn_S16bitPack_Context;

#endif /* BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INT_H_ */
