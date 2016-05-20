/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_multipoint_harrisScore_u16.h
 *
 *  @brief      This header defines interfaces for integrating multi-point
 *              16-bit Harris score kernel into BAM.
 */

#ifndef BAM_MULTIPOINT_HARRIS_SCORE_H_
#define BAM_MULTIPOINT_HARRIS_SCORE_H_

#define SPARSE_HARRIS_SCORE_TI_NUMPOINTSPERBLOCK (32)
#define SPARSE_HARRIS_SCORE_TI_BLKSTRIDE         (9)
#define SPARSE_HARRIS_SCORE_TI_BLKHEIGHT         (9)
#define SPARSE_HARRIS_SCORE_TI_INTERBLKOFFSET    ((SPARSE_HARRIS_SCORE_TI_BLKSTRIDE)*(SPARSE_HARRIS_SCORE_TI_BLKHEIGHT))

typedef struct
{
  uint8_t  level ;
  uint8_t  firstTimeFlag ;
  uint16_t numTotalPointsInThisLevel;
} BAM_Multipoint_Harris_Score_InArgs;

typedef struct bam_multipoint_harris_score_args
{
    uint16_t  numPoints;
    uint16_t  totalNumPoints;
    uint16_t  inputStride;
    uint16_t  interBlockOffset;
    uint16_t  sensitivityParam;
    int16_t   start_idx;
    uint32_t *pOutScoreBuffer;
} BAM_Multipoint_Harris_Score_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_multipointHarrisScoreHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_multipointHarrisScoreExecFunc;

extern BAM_KernelInfo gBAM_TI_multipointHarrisScoreKernel;

typedef enum
{
 BAM_MULTIPOINT_HARRIS_SCORE_INPUT_PORT_IMG   =    0,
 BAM_MULTIPOINT_HARRIS_SCORE_INPUT_PORT_INARGS ,
 BAM_MULTIPOINT_HARRIS_SCORE_NUM_INPUT_BLOCKS
} eBAM_MULTIPOINT_HARRIS_INPUT_PORTS ;

typedef enum
{
 BAM_MULTIPOINT_HARRIS_SCORE_OUTPUT_PORT   =    0,
 BAM_MULTIPOINT_HARRIS_SCORE_NUM_OUTPUT_BLOCKS
} eBAM_MULTIPOINT_HARRIS_OUTPUT_PORTS ;

#endif /* BAM_MULTIPOINT_HARRIS_SCORE_H_ */

