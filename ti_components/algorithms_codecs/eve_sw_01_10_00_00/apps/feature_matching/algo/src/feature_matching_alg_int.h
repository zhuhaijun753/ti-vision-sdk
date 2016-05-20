/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       feature_matching_alg_int.h
 *
 *  @brief      This file defines the functions for Feature matching applet
 *
 *  @version    0.1 (Aug 2014) : Base version.
 */


#ifndef FEATURE_MATCHING_ALG_INT_H
#define FEATURE_MATCHING_ALG_INT_H

/*--------------------------------------------------------------------------*/
/* This header file inclusion is only for XDAIS module. It accepts specific */
/* data types defined externally                                            */
/*--------------------------------------------------------------------------*/
#include <xdais_types.h>

#include "ifeature_matching_ti.h"
#include "feature_matching_graph_int.h"


/**
 *  @enum   eMemrecs
 *  @brief  Memory records for feature matching application
*/
typedef enum
{
  /* Memory records for handle */
  ALG_HANDLE_MEMREC,
  ALG_HANDLE_INT_MEMREC,
  /* Memory records for feature matching graph */
  GRAPH_OBJ_MEMREC,
  GRAPH_OBJ_INT_MEMREC,
  GRAPH_SCRATCH_MEMREC,
  GRAPH_CONTEXT_MEMREC,
  GRAPH_ARGS_MEMREC,
  NUM_MEMRECS
} eMemrecs;


/**
 *  @enum   eAlgState
 *  @brief  State of feature matching application
*/
typedef enum
{
  ALG_NOT_ACTIVE,
  ALG_ACTIVE
} eAlgState;

/**
  @struct FEATURE_MATCHING_TI_Obj
  @brief  This structure is the main handle of feature matching applet.

  @param  ivision    All public function pointers
  @param  algState   State of algorithm to indicate
  @param  numMemRecs Number of memory records
  @param  memRec     Array of memory records
  @param  graphMem   BAM specific memory for graph creation
*/
typedef struct
{
  IVISION_Fxns* ivision;
  uint8_t       algState;
  uint32_t      numMemRecs;
  IALG_MemRec   memRec[NUM_MEMRECS];
  BAM_GraphMem  graphMem;
  uint16_t      descriptorLength;
} FEATURE_MATCHING_TI_Obj;

typedef FEATURE_MATCHING_TI_Obj * FEATURE_MATCHING_TI_Handle;


/*--------------------------------------------------------*/
/* IALG functions                                         */
/* Refer XDAIS ialg.h file for details on these functions */
/*--------------------------------------------------------*/
int32_t FEATURE_MATCHING_TI_numAlloc(void);
int32_t FEATURE_MATCHING_TI_alloc(const IALG_Params *params,
  IALG_Fxns **parentFxns, IALG_MemRec memRec[]);
int32_t FEATURE_MATCHING_TI_init(IALG_Handle handle,
  const IALG_MemRec memRec[], IALG_Handle parent,
  const IALG_Params *params);
void  FEATURE_MATCHING_TI_activate(IALG_Handle handle);
void  FEATURE_MATCHING_TI_deactivate(IALG_Handle handle);
int32_t FEATURE_MATCHING_TI_free(IALG_Handle handle,
  IALG_MemRec memRec[]);

int32_t FEATURE_MATCHING_TI_control(IVISION_Handle handle,
    IALG_Cmd cmd, const IALG_Params *inParams,
    IALG_Params *outParams);

int32_t FEATURE_MATCHING_TI_process(IVISION_Handle handle,
    IVISION_InBufs *inBufs, IVISION_OutBufs *outBufs,
    IVISION_InArgs *inArgs, IVISION_OutArgs *outArgs);

/*--------------------------------------------------------*/
/* IRES functions                                         */
/*--------------------------------------------------------*/
XDAS_Int32 FEATURE_MATCHING_TI_getResourceDescriptors(
    IALG_Handle handle, IRES_ResourceDescriptor *resDesc);

#endif /* FEATURE_MATCHING_ALG_INT_H */

