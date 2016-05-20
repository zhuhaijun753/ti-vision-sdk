/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_median3x3_int.h
 *
 *  @brief      This header defines internal structures for 3x3 median filter
 *              in BAM.
 */

 #ifndef BAM_MEDIAN_3x3_INT_H_
#define BAM_MEDIAN_3x3_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_median3x3.h"

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7 */
/* Function-like macro definition */
/* Deviation allowed here because MAX is a very simple operation better implemented in form of a macro */
#define MAX(A, B) (((A) > (B)) ? (A) : (B))
/* RESET_MISRA("19.7")  -> Reset rule 19.7*/

#define NUM_IN_BLOCKS  (1)
#define NUM_OUT_BLOCKS (1)

#define IN_IDX     (0)     /* 0 */
#define OUT_IDX    (0)     /* 0 */

typedef enum
{
  PARAMS_IDX  =  0,
  SCRATCH_VERT_IDX,
  SCRATCH_HORZ_IDX,
  NUM_INTERNAL_BLOCKS
} eBAM_MEDIAN_3x3_TEMP_PORTS;

typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Median3x3_Args kernelArgs;
} BAM_Median3x3_Context;

#endif /* BAM_MEDIAN_3x3_INT_H_ */

