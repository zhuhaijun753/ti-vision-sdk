/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*==========================================================================*/
/**
 *  @file:      block_statistics_alg_int.h
 *
 *  @brief:     This file defines the functions for block statistics
 *
 *  @version:   0.2 (Aug 2014) : Base version.
 */
/*==========================================================================*/

#ifndef BLK_STATS_ALG_INT_H
#define BLK_STATS_ALG_INT_H

/*--------------------------------------------------------------------------*/
/* This header file inclusion is only for XDAIS module. It accepts specific */
/* data types defined externally                                            */
/*--------------------------------------------------------------------------*/
#include <xdais_types.h>

#include "iblock_statistics_ti.h"
#include "block_statistics_graph_int.h"

/**
 *  @enum   eMemrecs
 *  @brief  Memory records for Block Statistics application
*/
typedef enum
{
  /* Memory records for handle */
  ALG_HANDLE_MEMREC,
  ALG_HANDLE_INT_MEMREC,
  /* Memory records for sparse Harris score graph */
  GRAPH_OBJ_MEMREC,
  GRAPH_OBJ_INT_MEMREC,
  GRAPH_SCRATCH_MEMREC,
  GRAPH_CONTEXT_MEMREC,
  GRAPH_ARGS_MEMREC,
  NUM_MEMRECS
} eMemrecs;


/**
 *  @enum   eAlgState
 *  @brief  State of Block Statistics application
*/
typedef enum
{
  ALG_NOT_ACTIVE,
  ALG_ACTIVE
} eAlgState;


/**
  @struct BLOCK_STATS_TI_Obj
  @brief  This structure is the main handle of block statistics applet.

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
} BLOCK_STATS_TI_Obj;

typedef BLOCK_STATS_TI_Obj * BLOCK_STATS_TI_Handle;

/*--------------------------------------------------------*/
/* IALG functions                                         */
/* Refer XDAIS ialg.h file for details on these functions */
/*--------------------------------------------------------*/
int32_t BLOCK_STATS_TI_numAlloc(void);
int32_t BLOCK_STATS_TI_alloc(const IALG_Params *params,
  IALG_Fxns **parentFxns, IALG_MemRec memRec[]);
int32_t BLOCK_STATS_TI_init(IALG_Handle handle,
  const IALG_MemRec memRec[], IALG_Handle parent, const IALG_Params *params);
void  BLOCK_STATS_TI_activate(IALG_Handle handle);
void  BLOCK_STATS_TI_deactivate(IALG_Handle handle);
int32_t BLOCK_STATS_TI_free(IALG_Handle handle, IALG_MemRec memRec[]);

int32_t BLOCK_STATS_TI_control(IVISION_Handle handle, IALG_Cmd cmd,
    const IALG_Params *inParams, IALG_Params *outParams);

int32_t BLOCK_STATS_TI_process(IVISION_Handle handle, IVISION_InBufs *inBufs,
    IVISION_OutBufs *outBufs, IVISION_InArgs *inArgs,
    IVISION_OutArgs *outArgs);

/*--------------------------------------------------------*/
/* IRES functions                                         */
/*--------------------------------------------------------*/
XDAS_Int32 BLOCK_STATS_TI_getResourceDescriptors(IALG_Handle handle, IRES_ResourceDescriptor *resDesc);

#endif
