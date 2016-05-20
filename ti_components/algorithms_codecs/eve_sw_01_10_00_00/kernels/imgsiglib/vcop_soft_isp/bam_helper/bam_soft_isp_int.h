/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_soft_isp_int.h
 *
 *  @brief      This header defines internal structures for software
 *              Image Signal Processor (ISP) into BAM.
 */

 #ifndef BAM_SOFT_ISP_INT_H_
#define BAM_SOFT_ISP_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_soft_isp.h"

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */

#define MAX(A, B) (((A) > (B)) ? (A) : (B))
#define EXTRA_PIXELS(BLK_WIDTH, BLK_STRIDE, VECTOR_SZ) (MAX( ((((BLK_WIDTH) + (VECTOR_SZ) - 1U)/(VECTOR_SZ))*(VECTOR_SZ) - (BLK_STRIDE)), (0) ))

#define SOFT_ISP_MAX_OUT_WIDTH  (SOFT_ISP_MAX_BLOCK_WIDTH  - 4U)
#define SOFT_ISP_MAX_OUT_HEIGHT (SOFT_ISP_MAX_BLOCK_HEIGHT - 4U)
#define SOFT_ISP_MAX_OUT_STRIDE (16U*((SOFT_ISP_MAX_BLOCK_WIDTH + 15U)/16U))
#define SOFT_ISP_MAX_INBUF_SIZE (SOFT_ISP_MAX_BLOCK_WIDTH*SOFT_ISP_MAX_BLOCK_HEIGHT)
#define SOFT_ISP_MAX_BUF_SIZE   ((SOFT_ISP_MAX_OUT_WIDTH/2U)*(SOFT_ISP_MAX_OUT_HEIGHT/2U) + EXTRA_PIXELS((SOFT_ISP_MAX_OUT_WIDTH/2U), (SOFT_ISP_MAX_OUT_HEIGHT/2U), 8U))

/* Internal Buffer Maximum Sizes */
#define SOFT_ISP_MAX_PARAMS_SIZE     (800U)
#define SOFT_ISP_MAX_GBCE_TC_SIZE    (16384U)
#define SOFT_ISP_MAX_TEMP_RC_SIZE    (2U*SOFT_ISP_MAX_OUT_STRIDE*(SOFT_ISP_MAX_BLOCK_WIDTH/2U))
#define SOFT_ISP_MAX_TEMP_CC_SIZE    (2U*SOFT_ISP_MAX_OUT_STRIDE*(SOFT_ISP_MAX_BLOCK_WIDTH/2U))
#define SOFT_ISP_MAX_SCRATCH_A_SIZE  (3U*SOFT_ISP_MAX_BUF_SIZE)
#define SOFT_ISP_MAX_SCRATCH_B_SIZE  (4U*SOFT_ISP_MAX_BUF_SIZE)
#define SOFT_ISP_MAX_SCRATCH_C_SIZE  (13U*SOFT_ISP_MAX_BUF_SIZE)

/* RESET_MISRA("19.7")  -> Reset rule 19.7     */

typedef void (*FUNC_PTR)(uint16_t* pblock);

#define MAX_FUNC_CALLS    (6U)

#define NUM_IN_BLOCKS (BAM_SOFT_ISP_NUM_INPUT_BLOCKS)
#define NUM_OUT_BLOCKS (BAM_SOFT_ISP_NUM_OUTPUT_BLOCKS)

#define IN_RC_IDX     (BAM_SOFT_ISP_INPUT_RC_PORT)   /* 0 */
#define IN_CC_IDX     (BAM_SOFT_ISP_INPUT_CC_PORT)   /* 1 */

#define OUT_RC_IDX    (BAM_SOFT_ISP_OUTPUT_RC_PORT)     /* 0 */
#define OUT_CC_IDX    (BAM_SOFT_ISP_OUTPUT_CC_PORT)     /* 1 */
#define OUT_R_IDX     (BAM_SOFT_ISP_OUTPUT_R_PORT)      /* 2 */
#define OUT_STATS_IDX (BAM_SOFT_ISP_OUTPUT_STATS_PORT)  /* 3 */

typedef enum
{
  PARAMS_IDX   =    0,
  GBCE_TC_IDX,
  TEMP_RC_IDX,
  TEMP_CC_IDX,
  SCRATCH_A,
  SCRATCH_B,
  SCRATCH_C,
  NUM_INTERNAL_BLOCKS
} eBAM_SOFT_ISP_TEMP_PORTS;

typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_SoftIsp_Args kernelArgs;
    FUNC_PTR funcs_exec[MAX_FUNC_CALLS]; /**< List the vloops that EVELIB_algoDMAAutoIncrProcess() will need to call */
    uint16_t *ptr_params[MAX_FUNC_CALLS]; /**< List the pointers to the param registers passed as arguments to the vloops */
    uint32_t num_funcs_exec; /**< Number of vloops functions registered in funcs_exec */
} BAM_SoftIsp_Context;

#endif /* BAM_SOFT_ISP_INT_H_ */

