/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       imagePyramid_u8_alg_int.h
 *
 *  @brief      This file defines the functions for image pyramid
 *  @version 0.0 (Dec 2013) : Base version.
 */


#ifndef IMAGE_PYRAMID_U8_ALG_INT_H
#define IMAGE_PYRAMID_U8_ALG_INT_H

/*--------------------------------------------------------------------------*/
/* This header file inclusion is only for XDAIS module. It accepts specific */
/* data types defined externally                                            */
/*--------------------------------------------------------------------------*/
#pragma CHECK_MISRA ("none")
#include <xdais_types.h>
#pragma RESET_MISRA ("required")

#include "iImagePyramid_u8_ti.h"
#include "evealgframework.h"
#include "bam_common.h"

/**
 *  @enum   eMemrecs
 *  @brief  Memory records for image pyramid application
*/
typedef enum
{
  /* Memory records for handle */
  ALG_HANDLE_MEMREC,
  ALG_HANDLE_INT_MEMREC,
  /* Memory records for image pyramid graph */
  GRAPH_OBJ_MEMREC,
  GRAPH_OBJ_INT_MEMREC,
  GRAPH_SCRATCH_MEMREC,
  GRAPH_CONTEXT_MEMREC,
  GRAPH_ARGS_MEMREC,
  NUM_MEMRECS
} eMemrecs;

/**
 *  @enum   eAlgState
 *  @brief  State of image pyramid application
*/
typedef enum
{
  ALG_NOT_ACTIVE,
  ALG_ACTIVE
} eAlgState;

/**
  @struct IMAGE_PYRAMID_U8_TI_Obj
  @brief  This structure is the main handle of image pyramid
          applet.

  @param  ivision    All public function pointers
  @param  algState   State of algorithm to indicate
  @param  numMemRecs Number of memory records
  @param  memRec     Array of memory records
  @param  graphMem   BAM specific memory for graph creation
  @param  numLevels  Number of pyramid levels
  @param  filterType Filter type can be IMAGE_PYRAMID_U8_TI_2x2_AVERAGE or IMAGE_PYRAMID_U8_TI_5x5_GAUSSIAN
  @param  activeImageWidth   Width in bytes of the area that will be accessed by the EDMA when reading the frame.
                             For this function, it should always be equal to (createParams->imgFrameWidth)
  @param  activeImgHeight  Height in number of rows of the area that will be accessed by the EDMA when reading the frame.
                           For this function, it should always be equal to (createParams->imgFrameHeight)
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
  uint8_t       numLevels;
  uint8_t       filterType;
  uint16_t activeImgWidth;
  uint16_t activeImgHeight;
  uint16_t outputBlockWidth;
  uint16_t outputBlockHeight;


} IMAGE_PYRAMID_U8_TI_Obj;

typedef IMAGE_PYRAMID_U8_TI_Obj * IMAGE_PYRAMID_U8_TI_Handle;


/*--------------------------------------------------------*/
/* IALG functions                                         */
/* Refer XDAIS ialg.h file for details on these functions */
/*--------------------------------------------------------*/
int32_t IMAGE_PYRAMID_U8_TI_numAlloc(void);
int32_t IMAGE_PYRAMID_U8_TI_alloc(const IALG_Params *params,
  IALG_Fxns **parentFxns, IALG_MemRec *memRec);
int32_t IMAGE_PYRAMID_U8_TI_init(IALG_Handle handle,
  const IALG_MemRec *memRec, IALG_Handle parent, const IALG_Params *params);
XDAS_Void  IMAGE_PYRAMID_U8_TI_activate(IALG_Handle handle);
XDAS_Void  IMAGE_PYRAMID_U8_TI_deactivate(IALG_Handle handle);
int32_t IMAGE_PYRAMID_U8_TI_free(IALG_Handle handle, IALG_MemRec *memRec);

int32_t IMAGE_PYRAMID_U8_TI_control(IVISION_Handle Handle, IALG_Cmd cmd,
    const IALG_Params *inParams, IALG_Params *outParams);

int32_t IMAGE_PYRAMID_U8_TI_process(IVISION_Handle Handle, IVISION_InBufs *inBufs,
    IVISION_OutBufs *outBufs, IVISION_InArgs *inArgs,
    IVISION_OutArgs *outArgs);

/*--------------------------------------------------------*/
/* IRES functions                                         */
/*--------------------------------------------------------*/
int32_t IMAGE_PYRAMID_U8_TI_getResourceDescriptors(IALG_Handle handle, IRES_ResourceDescriptor *resDesc);

#endif /* IMAGE_PYRAMID_U8_ALG_INT_H */

