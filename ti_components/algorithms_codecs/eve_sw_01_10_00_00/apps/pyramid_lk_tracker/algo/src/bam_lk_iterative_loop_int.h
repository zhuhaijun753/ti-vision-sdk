/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_lk_iterative_loop_int.h
 *
 *  @brief      This header defines internal structures for kernel that computes
 *              relative location within the fetched input block along with updated
 *              source pointers using the new X, Y coordinates into BAM. It also
 *              incorporates the iterative LK loop to compute the flow vectors
 */
#ifndef BAM_LK_ITERATIVE_LOOP_INT_H_
#define BAM_LK_ITERATIVE_LOOP_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_lk_iterative_loop.h"

#define NUM_IN_BLOCKS (7U)
#define NUM_OUT_BLOCKS (2U)
#define NUM_INTERNAL_BLOCKS (2U)

#define PARAMS_IDX   (0U)
#define SCRATCH_IDX1 (1U)

#define SCRATCH_IDX1_SIZE (5120U)

#define IN_IDX1 (BAM_LK_ITERATIVE_LOOP_INPUT_PORT_CURRIMG        )
#define IN_IDX2 (BAM_LK_ITERATIVE_LOOP_INPUT_PORT_PREVINTERP     )
#define IN_IDX3 (BAM_LK_ITERATIVE_LOOP_INPUT_PORT_GRADXINTERP    )
#define IN_IDX4 (BAM_LK_ITERATIVE_LOOP_INPUT_PORT_GRADYINTERP    )
#define IN_IDX5 (BAM_LK_ITERATIVE_LOOP_INPUT_PORT_INVMAT         )
#define IN_IDX6 (BAM_LK_ITERATIVE_LOOP_INPUT_PORT_LASCRATCH      )
#define IN_IDX7 (BAM_LK_ITERATIVE_LOOP_INPUT_PORT_HASCRATCH      )
                                                              
                                                              
#define OUT_IDX1 (BAM_LK_ITERATIVE_LOOP_OUTPUT_PORT_CURRXY     )
#define OUT_IDX2 (BAM_LK_ITERATIVE_LOOP_OUTPUT_PORT_ERRMEASURE )


#define VCOP_LK_Q_FORMATE_PEL_RESOLN (4)
#define VCOP_LK_PATCH_WIDTH          (7) /* 7x7*/

typedef struct 
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_LK_Iterative_Loop_Args kernelArgs;
    uint16_t           *pBlkWgtAddrUpdate;
    uint16_t           *pBlkCurrBiLin;
    uint16_t           *pBlkWgtAddrForErrMeas;
    uint16_t           *pBlkCurrBiLinForErrMeas;
    uint16_t           *pBlkCalcIxIt;
    uint16_t           *pBlkIterCalcNewXY;
    uint16_t           *pBlkCopyNewXY;
    uint16_t           *pBlkCalcSADErrMeasure;
    uint16_t  (*prevXYAdrs[2])[2*VCOP_LK_MAX_NUM_KEY_PER_CALL];
    uint16_t  (*currXYAdrs[2])[2*VCOP_LK_MAX_NUM_KEY_PER_CALL];
    uint16_t  (*localXYAdrs[2])[2*VCOP_LK_MAX_NUM_KEY_PER_CALL];
    uint16_t  (*localXAdrs[2])[VCOP_LK_MAX_NUM_KEY_PER_CALL];
    uint16_t  (*localYAdrs[2])[VCOP_LK_MAX_NUM_KEY_PER_CALL];
    uint8_t   (*currValidPointsAdrs[2])[VCOP_LK_MAX_NUM_KEY_PER_CALL];
    uint32_t  (*pValidInAddrListAdrs[2])[VCOP_LK_MAX_NUM_KEY_PER_CALL];
    uint32_t  (*pValidOutAddrListAdrs[2])[VCOP_LK_MAX_NUM_KEY_PER_CALL];
    volatile uint32_t   pBaseInAddrListLocal[VCOP_LK_MAX_NUM_KEY_PER_CALL];
    volatile uint32_t   pBaseOutAddrListLocal[VCOP_LK_MAX_NUM_KEY_PER_CALL];
    uint16_t            localXCb[2][VCOP_LK_MAX_NUM_KEY_PER_CALL];
    uint16_t            localYCb[2][VCOP_LK_MAX_NUM_KEY_PER_CALL];
    uint8_t             listInDMAContext[EDMA_UTILS_AUTOINCREMENT_1D_CONTEXT_SIZE];
    uint16_t          * numValidPoints;
    uint16_t            currIdx;
} BAM_LK_Iterative_Loop_Context;

#endif /* BAM_LK_ITERATIVE_LOOP_INT_H_ */
