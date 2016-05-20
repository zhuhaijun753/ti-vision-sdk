/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_glcm_int.h
 *
 *  @brief      This header defines internal structures for gray-level
 *              co-occurrence matrix computation into BAM.
 */

#ifndef BAM_GLCM_INT_H_
#define BAM_GLCM_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_glcm.h"

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */

#define MAX(A, B) (((A) > (B)) ? (A) : (B))
#define MIN(A, B) (((A) < (B)) ? (A) : (B))

/* RESET_MISRA("19.7")  -> Reset rule 19.7     */


#define NUM_IN_BLOCKS (BAM_GLCM_NUM_INPUT_BLOCKS)
#define NUM_OUT_BLOCKS (BAM_GLCM_NUM_OUTPUT_BLOCKS)

#define IN_IDX (BAM_GLCM_INPUT_PORT)         /* 0 */

#define OUT_IDX (BAM_GLCM_OUTPUT_PORT)       /* 0 */

typedef enum
{
  PARAMS_IDX   =    0,
  SCRATCH_IDX,
  WEIGHT_IDX,
  GLCM_BUFF_IDX,
  NUM_INTERNAL_BLOCKS
} eBAM_GLCM_TEMP_PORTS;

typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Glcm_Args kernelArgs;
} BAM_Glcm_Context;

#endif /* BAM_GLCM_INT_H_ */
