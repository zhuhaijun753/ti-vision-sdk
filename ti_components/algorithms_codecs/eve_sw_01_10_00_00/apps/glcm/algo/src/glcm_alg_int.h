/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       glcm_alg_int.h
 *
 *  @brief      This file defines the functions for Gray-level
 *              co-occurrence matrix applet
 *
 *  @version    0.1 (Jan 2014) : Base version.
 */


#ifndef GLCM_ALG_INT_H
#define GLCM_ALG_INT_H

/*--------------------------------------------------------------------------*/
/* This header file inclusion is only for XDAIS module. It accepts specific */
/* data types defined externally                                            */
/*--------------------------------------------------------------------------*/
#include <xdais_types.h>

#include "iglcm_ti.h"
#include "glcm_graph_int.h"

/**
* @brief Maximum memory reserved for gray-levels co-occurrence output
* in internal memory (WMEM). Currently the component assumes 24kB.
*/
#define GLCM_TI_MAXMEMORY        (24576U)


/**
 *  @enum   eMemrecs
 *  @brief  Memory records for Harris score based Best Feature to Front application
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
 *  @brief  State of Gray-level co-occurrence matrix application
*/
typedef enum
{
  ALG_NOT_ACTIVE,
  ALG_ACTIVE
} eAlgState;

/**
  @struct GLCM_TI_Obj
  @brief  This structure is the main handle of Gray-level co-occurrence
           matrix applet.

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
  uint16_t      outBufSize;
  uint16_t      scatterOffset;
  uint8_t       numLevels;
  uint8_t       numDirections;
  uint8_t       numChannels;
} GLCM_TI_Obj;

typedef GLCM_TI_Obj * GLCM_TI_Handle;


/*--------------------------------------------------------*/
/* IALG functions                                         */
/* Refer XDAIS ialg.h file for details on these functions */
/*--------------------------------------------------------*/
int32_t GLCM_TI_numAlloc(void);
int32_t GLCM_TI_alloc(const IALG_Params *params,
  IALG_Fxns **parentFxns, IALG_MemRec memRec[]);
int32_t GLCM_TI_init(IALG_Handle handle,
  const IALG_MemRec memRec[], IALG_Handle parent, const IALG_Params *params);
void  GLCM_TI_activate(IALG_Handle handle);
void  GLCM_TI_deactivate(IALG_Handle handle);
int32_t GLCM_TI_free(IALG_Handle handle, IALG_MemRec memRec[]);

int32_t GLCM_TI_control(IVISION_Handle handle, IALG_Cmd cmd,
    const IALG_Params *inParams, IALG_Params *outParams);

int32_t GLCM_TI_process(IVISION_Handle handle, IVISION_InBufs *inBufs,
    IVISION_OutBufs *outBufs, IVISION_InArgs *inArgs,
    IVISION_OutArgs *outArgs);

/*--------------------------------------------------------*/
/* IRES functions                                         */
/*--------------------------------------------------------*/
XDAS_Int32 GLCM_TI_getResourceDescriptors(IALG_Handle handle, IRES_ResourceDescriptor *resDesc);

#endif /* GLCM_ALG_INT_H */

