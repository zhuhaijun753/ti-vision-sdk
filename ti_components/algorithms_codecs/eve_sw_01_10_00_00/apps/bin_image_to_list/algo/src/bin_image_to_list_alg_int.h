/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bin_image_to_list_alg_int.h
 *
 *  @brief      This file defines the functions for BIN_IMAGE_TO_LIST_WITH_MASKING applet
 *  @version 0.0 (April 2015) : Base version.
 */


#ifndef BIN_IMAGE_TO_LIST_ALG_INT_H_
#define BIN_IMAGE_TO_LIST_ALG_INT_H_

/*--------------------------------------------------------------------------*/
/* This header file inclusion is only for XDAIS module. It accepts specific */
/* data types defined externally                                            */
/*--------------------------------------------------------------------------*/
#include <xdais_types.h>

#include "ibin_image_to_list_ti.h"
#include "bin_image_to_list_with_masking_graph_int.h"


/**
 *  @enum   eMemrecs
 *  @brief  Memory records for 2d filter applet
*/
typedef enum
{
  /* Memory records for handle */
 /* Alg Handle should be first entry in this enum table
  as test app is expecting it to be first entry*/
  ALG_HANDLE_MEMREC,
  ALG_HANDLE_INT_MEMREC,
  /* Memory records for bin img to list graph */
  BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_OBJ_MEMREC,
  /* For all the external memory if same copy is expected to be present in
  DMEM than they should be kept consecutive in this enum. This is needed
  because alg activate and deactivate has this assumption*/
  BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_OBJ_INT_MEMREC,
  BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_SCRATCH_MEMREC,
  BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_CONTEXT_MEMREC,
  BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_ARGS_MEMREC,
  /* Memory records for select list elements graph */
  BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_OBJ_MEMREC,
  /* For all the external memory if same copy is expected to be present in
  DMEM than they should be kept consecutive in this enum. This is needed
  because alg activate and deactivate has this assumption*/
  BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_OBJ_INT_MEMREC,
  BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_SCRATCH_MEMREC,
  BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_CONTEXT_MEMREC,
  BIN_IMAGE_TO_LIST_SEL_LIST_ELEM_ARGS_MEMREC,
  /* This memrec to be used to store intermediate outputs
  when listSuppression is enabled*/
  BIN_IMAGE_TO_LIST_INTERMEDIATE_BUF_MEMREC,
  NUM_MEMRECS
} eMemrecs;

/**
 *  @enum   eAlgState
 *  @brief  State of Feature Plane compuation applet
 */
typedef enum
{
  ALG_NOT_ACTIVE,
  ALG_ACTIVE
} eAlgState;

/**
  @struct BIN_IMAGE_TO_LIST_TI_Obj
  @brief  This structure is the main handle of 2D filter
          applet.

  @param  ivision    All public function pointers
  @param  algState   State of algorithm to indicate
  @param  numMemRecs Number of memory records
  @param  memRec     Array of memory records
  @param filter2DGraphMem  Graph memory pointers for 2D filter graph
*/
typedef struct
{
  IVISION_Fxns      *ivision;
  uint8_t           algState;
  uint32_t          numMemRecs;
  IALG_MemRec       memRec[NUM_MEMRECS];
  BAM_GraphMem      binImgToListWithMaskingGraphMem;
  BAM_GraphMem      binImgToListSelListElemGraphMem;
  BIN_IMAGE_TO_LIST_TI_CreateParams createParams;
  uint16_t          blockWidth;
  uint16_t          blockHeight;
} BIN_IMAGE_TO_LIST_TI_Obj;

typedef BIN_IMAGE_TO_LIST_TI_Obj * BIN_IMAGE_TO_LIST_TI_Handle;


/*--------------------------------------------------------*/
/* IALG functions                                         */
/* Refer XDAIS ialg.h file for details on these functions */
/*--------------------------------------------------------*/
int32_t BIN_IMAGE_TO_LIST_TI_numAlloc(void);
int32_t BIN_IMAGE_TO_LIST_TI_alloc(const IALG_Params *params,
   IALG_Fxns **parentFxns, IALG_MemRec *memRec);
int32_t BIN_IMAGE_TO_LIST_TI_init(IALG_Handle handle,
  const IALG_MemRec *memRec, IALG_Handle parent, const IALG_Params *params);
void  BIN_IMAGE_TO_LIST_TI_activate(IALG_Handle handle);
void  BIN_IMAGE_TO_LIST_TI_deactivate(IALG_Handle handle);
int32_t BIN_IMAGE_TO_LIST_TI_free(IALG_Handle handle, IALG_MemRec *memRec);

int32_t BIN_IMAGE_TO_LIST_TI_control(IVISION_Handle handle, IALG_Cmd cmd,
    const IALG_Params *inParams, IALG_Params *outParams);

int32_t BIN_IMAGE_TO_LIST_TI_process(IVISION_Handle handle, IVISION_InBufs *inBufs,
    IVISION_OutBufs *outBufs, IVISION_InArgs *inArgs,
    IVISION_OutArgs *outArgs);

/*--------------------------------------------------------*/
/* IRES functions                                         */
/*--------------------------------------------------------*/
int32_t BIN_IMAGE_TO_LIST_TI_getResourceDescriptors(IALG_Handle handle, IRES_ResourceDescriptor *resDesc);

#endif /* BIN_IMAGE_TO_LIST_ALG_INT_H_ */

