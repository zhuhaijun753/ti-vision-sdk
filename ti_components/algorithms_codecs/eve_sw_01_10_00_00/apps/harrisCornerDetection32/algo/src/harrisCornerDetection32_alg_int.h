/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       harrisCornerDetection32_alg_int.h
 *
 *  @brief      This file defines the functions for harris corner detection
 *  @version 0.0 (Dec 2013) : Base version.
 */


#ifndef HARRIS_CORNER_DETECTION_32_ALG_INT_H
#define HARRIS_CORNER_DETECTION_32_ALG_INT_H

/*--------------------------------------------------------------------------*/
/* This header file inclusion is only for XDAIS module. It accepts specific */
/* data types defined externally                                            */
/*--------------------------------------------------------------------------*/
#pragma CHECK_MISRA ("none")
#include <xdais_types.h>
#pragma RESET_MISRA ("required")

#include "iHarrisCornerDetection32_ti.h"
#include "harrisCornerDetection32_graph_int.h"

/**
 *  @enum   eMemrecs
 *  @brief  Memory records for Harris Corner detection application
*/
typedef enum
{
  /* Memory records for handle */
  ALG_HANDLE_MEMREC,
  ALG_HANDLE_INT_MEMREC,
  /* Memory records for harris corner detection graph */
  GRAPH_OBJ_MEMREC,
  GRAPH_OBJ_INT_MEMREC,
  GRAPH_SCRATCH_MEMREC,
  GRAPH_CONTEXT_MEMREC,
  GRAPH_ARGS_MEMREC,
  NUM_MEMRECS
} eMemrecs;

/**
 *  @enum   eAlgState
 *  @brief  State of Harris corner detection application
*/
typedef enum
{
  ALG_NOT_ACTIVE,
  ALG_ACTIVE
} eAlgState;

/**
  @struct HARRIS_CORNER_DETECTION_32_TI_Obj
  @brief  This structure is the main handle of Harris corner detection
          applet.

  @param  ivision    All public function pointers
  @param  algState   State of algorithm to indicate
  @param  numMemRecs Number of memory records
  @param  memRec     Array of memory records
  @param  graphMem   BAM specific memory for graph creation
  @param  activeImageWidth   Width in bytes of the area that will be accessed by the EDMA when reading the frame.
                             For this function, it should always be equal to (createParams->imgFrameWidth + TOTAL_FILTER_SZ)
  @param  activeImgHeight  Height in number of rows of the area that will be accessed by the EDMA when reading the frame.
                           For this function, it should always be equal to (createParams->imgFrameHeight + TOTAL_FILTER_SZ)
  @param  outputBlockWidth  Output block width returned by BAM_createGraph(). That's useful information to understand performance.
  @param  outputBlockHeight Output block height picked by BAM_createGraph(). That's useful information to understand performance.
*/
typedef struct
{
  IVISION_Fxns* ivision;
  uint8_t       algState;
  uint32_t      numMemRecs;
  IALG_MemRec   memRec[NUM_MEMRECS];
  BAM_GraphMem  graphMem;
  uint16_t activeImgWidth;
  uint16_t activeImgHeight;
  uint16_t outputBlockWidth;
  uint16_t outputBlockHeight;
  uint8_t  totalBorderRequired;
  HARRIS_CORNER_DETECTION_32_TI_CreateParams createParams;


} HARRIS_CORNER_DETECTION_32_TI_Obj;

typedef HARRIS_CORNER_DETECTION_32_TI_Obj * HARRIS_CORNER_DETECTION_32_TI_Handle;


/*--------------------------------------------------------*/
/* IALG functions                                         */
/* Refer XDAIS ialg.h file for details on these functions */
/*--------------------------------------------------------*/
int32_t HARRIS_CORNER_DETECTION_32_TI_numAlloc(void);
int32_t HARRIS_CORNER_DETECTION_32_TI_alloc(const IALG_Params *params,
  IALG_Fxns **parentFxns, IALG_MemRec *memRec);
int32_t HARRIS_CORNER_DETECTION_32_TI_init(IALG_Handle handle,
  const IALG_MemRec memRec[], IALG_Handle parent, const IALG_Params *params);
XDAS_Void  HARRIS_CORNER_DETECTION_32_TI_activate(IALG_Handle handle);
XDAS_Void  HARRIS_CORNER_DETECTION_32_TI_deactivate(IALG_Handle handle);
int32_t HARRIS_CORNER_DETECTION_32_TI_free(IALG_Handle handle, IALG_MemRec memRec[]);

int32_t HARRIS_CORNER_DETECTION_32_TI_control(IVISION_Handle handle, IALG_Cmd cmd,
    const IALG_Params *inParams, IALG_Params *outParams);

int32_t HARRIS_CORNER_DETECTION_32_TI_process(IVISION_Handle Handle, IVISION_InBufs *inBufs,
    IVISION_OutBufs *outBufs, IVISION_InArgs *inArgs,
    IVISION_OutArgs *outArgs);

/*--------------------------------------------------------*/
/* IRES functions                                         */
/*--------------------------------------------------------*/
int32_t HARRIS_CORNER_DETECTION_32_TI_getResourceDescriptors(IALG_Handle handle, IRES_ResourceDescriptor *resDesc);

#endif /* HARRIS_CORNER_DETECTION_32_ALG_INT_H */

