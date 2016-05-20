/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       edge_detector_alg_int.h
 *
 *  @brief      This file defines the functions for Edge Detector applet
 *  @version 0.0 (Dec 2014) : Base version.
 */


#ifndef EDGE_DETECTOR_ALG_INT_H_
#define EDGE_DETECTOR_ALG_INT_H_

/*--------------------------------------------------------------------------*/
/* This header file inclusion is only for XDAIS module. It accepts specific */
/* data types defined externally                                            */
/*--------------------------------------------------------------------------*/
#include <xdais_types.h>

#include "iedge_detector_ti.h"
#include "edge_detector_sobel_graph_int.h"
#include "edge_detector_canny_graph_int.h"



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
  /* Memory records for Feature Plane computation for Luma component graph */
  EDGE_DETECTOR_GRAPH_OBJ_MEMREC,
  /* For all the external memory if same copy is expected to be present in
  DMEM than they should be kept consecutive in this enum. This is needed
  because alg activate and deactivate has this assumption*/
  EDGE_DETECTOR_GRAPH_OBJ_INT_MEMREC,
  EDGE_DETECTOR_GRAPH_SCRATCH_MEMREC,
  EDGE_DETECTOR_GRAPH_CONTEXT_MEMREC,
  EDGE_DETECTOR_GRAPH_ARGS_MEMREC,
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
  @struct EDGE_DETECTOR_TI_Obj
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
  BAM_GraphMem      edgeDetectGraphMem;
  uint8_t           filterCoeff[9];
  EDGE_DETECTOR_TI_CreateParams createParams;
} EDGE_DETECTOR_TI_Obj;

typedef EDGE_DETECTOR_TI_Obj * EDGE_DETECTOR_TI_Handle;


/*--------------------------------------------------------*/
/* IALG functions                                         */
/* Refer XDAIS ialg.h file for details on these functions */
/*--------------------------------------------------------*/
int32_t EDGE_DETECTOR_TI_numAlloc(void);
int32_t EDGE_DETECTOR_TI_alloc(const IALG_Params *params,
     IALG_Fxns **parentFxns, IALG_MemRec memRec[]);
int32_t EDGE_DETECTOR_TI_init(IALG_Handle handle,
  const IALG_MemRec *memRec, IALG_Handle parent, const IALG_Params *params);
void  EDGE_DETECTOR_TI_activate(IALG_Handle handle);
void  EDGE_DETECTOR_TI_deactivate(IALG_Handle handle);
int32_t EDGE_DETECTOR_TI_free(IALG_Handle handle, IALG_MemRec memRec[]);

int32_t EDGE_DETECTOR_TI_control(IVISION_Handle handle, IALG_Cmd cmd,
    const IALG_Params *inParams, IALG_Params *outParams);

int32_t EDGE_DETECTOR_TI_process(IVISION_Handle handle, IVISION_InBufs *inBufs,
    IVISION_OutBufs *outBufs, IVISION_InArgs *inArgs,
    IVISION_OutArgs *outArgs);

/*--------------------------------------------------------*/
/* IRES functions                                         */
/*--------------------------------------------------------*/
int32_t EDGE_DETECTOR_TI_getResourceDescriptors(IALG_Handle handle, IRES_ResourceDescriptor *resDesc);

#endif /* EDGE_DETECTOR_ALG_INT_H_ */

