/*==========================================================================*/
/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_lk_iterative_loop.h
 *
 *  @brief      This header defines interfaces for integrating kernel that computes
 *              relative location within the fetched input block along with updated
 *              source pointers using the new X, Y coordinates into BAM. It also
 *              incorporates the iterative LK loop to compute the flow vectors
 */

#ifndef BAM_LK_ITERATIVE_LOOP_H_
#define BAM_LK_ITERATIVE_LOOP_H_

#include "bam_pyramid_lk_tracker_dma_node.h"

typedef struct 
{
  uint16_t numKeyPointsPerCall;
  uint16_t keyPointsProcessedCnt;
  uint16_t *prevXYList;
  uint16_t *currXYList;
  uint16_t numKeyPoints;
  uint16_t  currBlkWidth;
  uint16_t  currBlkHeight;
  EDMA_UTILS_pyramidlktracker_dmaReadNode_ctrl_args * ctrlArgs;
} BAM_LK_Iterative_Loop_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_lkIterativeLoopHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_lkIterativeLoopExecFunc;

extern BAM_KernelInfo gBAM_TI_lkIterativeLoopKernel;

/*Input port comes from the DMA node outputdatablock which allocates memory for */
/*holding pointers of current frame, previous frame along with scratch memories */
/*required by the iterative LK loop in IBUFLA and IBUFHA buffers                */
#define BAM_LK_ITERATIVE_LOOP_INPUT_PORT_CURRIMG        (0) 
#define BAM_LK_ITERATIVE_LOOP_INPUT_PORT_PREVINTERP     (1) 
#define BAM_LK_ITERATIVE_LOOP_INPUT_PORT_GRADXINTERP    (2) 
#define BAM_LK_ITERATIVE_LOOP_INPUT_PORT_GRADYINTERP    (3) 
#define BAM_LK_ITERATIVE_LOOP_INPUT_PORT_INVMAT         (4) 
#define BAM_LK_ITERATIVE_LOOP_INPUT_PORT_LASCRATCH      (5) 
#define BAM_LK_ITERATIVE_LOOP_INPUT_PORT_HASCRATCH      (6) 
                                                          
#define BAM_LK_ITERATIVE_LOOP_OUTPUT_PORT_CURRXY        (0) 
#define BAM_LK_ITERATIVE_LOOP_OUTPUT_PORT_ERRMEASURE    (1) 

#define NUM_POINTS_IN_DMEM (96)
#define NUM_POINT_BUFFS_IN_DMEM (2)

#endif /* BAM_LK_ITERATIVE_LOOP_H_ */
