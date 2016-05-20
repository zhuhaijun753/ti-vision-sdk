/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       blockSort_u32_alg_int.h
 *
 *  @brief      This file defines the functions for block sort
 *  @version 0.0 (Dec 2013) : Base version.
 */


#ifndef BLOCK_SORT_U32_ALG_INT_H
#define BLOCK_SORT_U32_ALG_INT_H

/*--------------------------------------------------------------------------*/
/* This header file inclusion is only for XDAIS module. It accepts specific */
/* data types defined externally                                            */
/*--------------------------------------------------------------------------*/
#pragma CHECK_MISRA ("none")
#include <xdais_types.h>
#pragma RESET_MISRA ("required")

#include "iBlockSort_u32_ti.h"
#include "blockSort_u32_graph_int.h"

/**
 *  @enum   eMemrecs
 *  @brief  Memory records for block sort,id application
*/
typedef enum
{
  /* Memory records for handle */
  ALG_HANDLE_MEMREC,
  ALG_HANDLE_INT_MEMREC,
  /* Memory records for block sort graph */
  GRAPH_OBJ_MEMREC,
  GRAPH_OBJ_INT_MEMREC,
  GRAPH_SCRATCH_MEMREC,
  GRAPH_CONTEXT_MEMREC,
  GRAPH_ARGS_MEMREC,
  NUM_MEMRECS
} eMemrecs;

/**
 *  @enum   eAlgState
 *  @brief  State of block sortapplication
*/
typedef enum
{
  ALG_NOT_ACTIVE,
  ALG_ACTIVE
} eAlgState;

/**
  @struct BLOCK_SORT_U32_TI_Obj
  @brief  This structure is the main handle of block sort
          applet.

  @param  ivision    All public function pointers
  @param  algState   State of algorithm to indicate
  @param  numMemRecs Number of memory records
  @param  memRec     Array of memory records
  @param  graphMem   BAM specific memory for graph creation
  @param  activeImageWidth   Width in bytes of the area that will be accessed by the EDMA when reading the frame.
                             For this function, it should always be equal to (createParams->imgFrameWidth)
  @param  activeImgHeight  Height in number of rows of the area that will be accessed by the EDMA when reading the frame.
                           For this function, it should always be equal to (createParams->imgFrameHeight)
  @param  outputBlockWidth  Output block width returned by BAM_createGraph(). For this function, it will always be equal to blockWidth set at creation time.
  @param  outputBlockHeight Output block height picked by BAM_createGraph(). For this function, it will always be equal to blockWidth set at creation time.
  @param  srcImBuf This an output parameter filled by BLOCK_SORT_U32_TI_graphCreate(). It is used in one block mode, in case the function is called to process one block of elements, it can directly write the input data to the address returned in this member srcImBuf
  @param  dstImBuf This an output parameter filled by BLOCK_SORT_U32_TI_graphCreate(). It is used in one block mode, in case the function is called to process one block of elements, it can directly read the output data from the address returned in this member dstImBuf

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
  uint32_t     *srcImBuf;
  uint32_t     *dstImBuf;

} BLOCK_SORT_U32_TI_Obj;

typedef BLOCK_SORT_U32_TI_Obj * BLOCK_SORT_U32_TI_Handle;


/*--------------------------------------------------------*/
/* IALG functions                                         */
/* Refer XDAIS ialg.h file for details on these functions */
/*--------------------------------------------------------*/
int32_t BLOCK_SORT_U32_TI_numAlloc(void);
int32_t BLOCK_SORT_U32_TI_alloc(const IALG_Params *params,
  IALG_Fxns **parentFxns, IALG_MemRec memRec[]);
int32_t BLOCK_SORT_U32_TI_init(IALG_Handle handle,
  const IALG_MemRec memRec[], IALG_Handle parent, const IALG_Params *params);
XDAS_Void  BLOCK_SORT_U32_TI_activate(IALG_Handle handle);
XDAS_Void  BLOCK_SORT_U32_TI_deactivate(IALG_Handle handle);
int32_t BLOCK_SORT_U32_TI_free(IALG_Handle handle, IALG_MemRec *memRec);

int32_t BLOCK_SORT_U32_TI_control(IVISION_Handle Handle, IALG_Cmd cmd,
    const IALG_Params *inParams, IALG_Params *outParams);

int32_t BLOCK_SORT_U32_TI_process(IVISION_Handle Handle, IVISION_InBufs *inBufs,
    IVISION_OutBufs *outBufs, IVISION_InArgs *inArgs,
    IVISION_OutArgs *outArgs);

/*--------------------------------------------------------*/
/* IRES functions                                         */
/*--------------------------------------------------------*/
int32_t BLOCK_SORT_U32_TI_getResourceDescriptors(IALG_Handle handle, IRES_ResourceDescriptor *resDesc);

#endif /* BLOCK_SORT_U32_ALG_INT_H */

