/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       hough_for_lines_alg_int.h
 *
 *  @brief      This file defines the functions for hough for lines applet
 *  @version 0.0 (July 2014) : Base version.
 */


#ifndef HOUGH_FOR_LINES_ALG_INT_H_
#define HOUGH_FOR_LINES_ALG_INT_H_

/*--------------------------------------------------------------------------*/
/* This header file inclusion is only for XDAIS module. It accepts specific */
/* data types defined externally                                            */
/*--------------------------------------------------------------------------*/
#include <xdais_types.h>

#include "ihough_for_lines_ti.h"
#include "hough_for_lines_graph_int.h"

/**
 *  @enum   eMemrecs
 *  @brief  Memory records for rBrief applet
*/
typedef enum
{
  /* Memory records for handle */
 /* Alg Handle should be first entry in this enum table
  as test app is expecting it to be first entry*/
  ALG_HANDLE_MEMREC,
  ALG_HANDLE_INT_MEMREC,
  /* Memory records for rBrief graph */
  HOUGH_FOR_LINES_GRAPH_OBJ_MEMREC,
  /* For all the external memory if same copy is expected to be present in
  DMEM than they should be kept consecutive in this enum. This is needed
  because alg activate and deactivate has this assumption*/
  HOUGH_FOR_LINES_GRAPH_OBJ_INT_MEMREC,
  HOUGH_FOR_LINES_GRAPH_SCRATCH_MEMREC,
  HOUGH_FOR_LINES_GRAPH_CONTEXT_MEMREC,
  HOUGH_FOR_LINES_GRAPH_ARGS_MEMREC,
  NUM_MEMRECS
} eMemrecs;

/**
 *  @enum   eAlgState
 *  @brief  State of Fast9 corner detect application
*/
typedef enum
{
  ALG_NOT_ACTIVE,
  ALG_ACTIVE
} eAlgState;

/**
  @struct HOUGH_FOR_LINES_TI_Obj
  @brief  This structure is the main handle of rBrief.
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
} HOUGH_FOR_LINES_TI_Obj;

typedef HOUGH_FOR_LINES_TI_Obj * HOUGH_FOR_LINES_TI_Handle;


/*--------------------------------------------------------*/
/* IALG functions                                         */
/* Refer XDAIS ialg.h file for details on these functions */
/*--------------------------------------------------------*/
int32_t HOUGH_FOR_LINES_TI_numAlloc(void);
int32_t HOUGH_FOR_LINES_TI_alloc(const IALG_Params *params,
  IALG_Fxns **parentFxns, IALG_MemRec memRec[]);
int32_t HOUGH_FOR_LINES_TI_init(IALG_Handle handle,
  const IALG_MemRec memRec[], IALG_Handle parent, const IALG_Params *params);
void  HOUGH_FOR_LINES_TI_activate(IALG_Handle handle);
void  HOUGH_FOR_LINES_TI_deactivate(IALG_Handle handle);
int32_t HOUGH_FOR_LINES_TI_free(IALG_Handle handle, IALG_MemRec memRec[]);

int32_t HOUGH_FOR_LINES_TI_control(IVISION_Handle handle, IALG_Cmd cmd,
    const IALG_Params *inParams, IALG_Params *outParams);

int32_t HOUGH_FOR_LINES_TI_process(IVISION_Handle handle, IVISION_InBufs *inBufs,
    IVISION_OutBufs *outBufs, IVISION_InArgs *inArgs,
    IVISION_OutArgs *outArgs);

/*--------------------------------------------------------*/
/* IRES functions                                         */
/*--------------------------------------------------------*/
int32_t HOUGH_FOR_LINES_TI_getResourceDescriptors(IALG_Handle handle, IRES_ResourceDescriptor *resDesc);

#endif /* HOUGH_FOR_LINES_ALG_INT_H_ */

