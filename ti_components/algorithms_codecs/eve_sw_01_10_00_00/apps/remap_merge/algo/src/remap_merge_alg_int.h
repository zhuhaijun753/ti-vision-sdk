/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file        remap_merge_alg_int.h
 *
 *  @brief      This file defines the functions for the Remap Merge Applet
 *  @version  0.0 (January, 2014) : Base version.
 */


#ifndef REMAP_MERGE_ALG_INT_H
#define REMAP_MERGE_ALG_INT_H

/*--------------------------------------------------------------------------*/
/* This header file inclusion is only for XDAIS module. It accepts specific */
/* data types defined externally                                            */
/*--------------------------------------------------------------------------*/
#include <xdais_types.h>

#include "iremap_merge_ti.h"
#include "remap_merge_graph_int.h"

/**
 *  @enum   eMemrecs
 *  @brief     Memory records for Remap Merge Applet
*/
typedef enum
{
    /* Memory records for handle */
    /* Alg Handle should be first entry in this enum table
            as test app is expecting it to be first entry*/
    ALG_HANDLE_MEMREC,
    ALG_HANDLE_INT_MEMREC,
    /* Memory records for Fast9 graph */
    REMAP_MERGE_GRAPH_OBJ_MEMREC,
    /* For all the external memory if same copy is expected to be present in
            DMEM than they should be kept consecutive in this enum. This is needed
            because alg activate and deactivate has this assumption*/
    REMAP_MERGE_GRAPH_OBJ_INT_MEMREC,
    REMAP_MERGE_GRAPH_SCRATCH_MEMREC,
    REMAP_MERGE_GRAPH_ARGS_MEMREC,
    NUM_REMAP_MERGE_MEMRECS
} eMemrecs;

/**
 *  @enum   eAlgState
 *  @brief     State of Fast9 corner detect application
*/
typedef enum
{
  ALG_NOT_ACTIVE,
  ALG_ACTIVE
} eAlgState;

/** ========================================================
 *  @name   REMAP_MERGE_TI_Obj
 *
 *  @desc   This structure is the main handle of Remap and Merge applet
 *
 *  @field ivision
 *          All public function pointers
 *
 *  @field algState
 *          State of algorithm to indicate
 *
 *  @field numMemRecs
 *          Number of memory records
 *
 *  @field memRec
 *          Array of memory records
 *
 *  @field remapMergeGraphMem
 *          BAM specific memory for graph creation
 *
 *  @field srcFormat
 *          Format of Source Image
 *
 *  @field dstFormat
 *          Format of output
 *
 *  @field enableMerge
 *          enable or disable Alpha blending kernel
 *
 *  ===============================================================
*/

typedef struct
{
    IVISION_Fxns *ivision;
    uint8_t       algState;
    uint32_t      numMemRecs;
    IALG_MemRec   memRec[NUM_REMAP_MERGE_MEMRECS];
    BAM_GraphMem  remapMergeGraphMem;
    Format        srcFormat;
    Format        dstFormat;
    uint8_t       enableMerge;
    uint8_t       enableTileApproach;
} REMAP_MERGE_TI_Obj;

typedef REMAP_MERGE_TI_Obj * REMAP_MERGE_TI_Handle;


/*--------------------------------------------------------*/
/* IALG functions                                         */
/* Refer XDAIS ialg.h file for details on these functions */
/*--------------------------------------------------------*/
int32_t REMAP_MERGE_TI_numAlloc(void);
int32_t REMAP_MERGE_TI_alloc(const IALG_Params *params,
  IALG_Fxns **parentFxns, IALG_MemRec memRec[]);
int32_t REMAP_MERGE_TI_init(IALG_Handle handle,
  const IALG_MemRec memRec[], IALG_Handle parent, const IALG_Params *params);
void  REMAP_MERGE_TI_activate(IALG_Handle handle);
void  REMAP_MERGE_TI_deactivate(IALG_Handle handle);
int32_t REMAP_MERGE_TI_free(IALG_Handle handle, IALG_MemRec memRec[]);

int32_t REMAP_MERGE_TI_control(IVISION_Handle handle, IALG_Cmd cmd,
    const IALG_Params *inParams, IALG_Params *outParams);

int32_t REMAP_MERGE_TI_process(IVISION_Handle handle, IVISION_InBufs *inBufs,
    IVISION_OutBufs *outBufs, IVISION_InArgs *inArgs,
    IVISION_OutArgs *outArgs);

/*--------------------------------------------------------*/
/* IRES functions                                         */
/*--------------------------------------------------------*/
XDAS_Int32 REMAP_MERGE_TI_getResourceDescriptors(IALG_Handle handle, IRES_ResourceDescriptor *resDesc);

#endif /* REMAP_MERGE_ALG_INT_H */

