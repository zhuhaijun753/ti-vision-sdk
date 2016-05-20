/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*==========================================================================*/
/**
 *  @file:      median_filter_alg_int.h
 *
 *  @brief:     This file defines the functions for median filtering
 *
 *  @version:   0.2 (July 2014) : Base version.
 */
/*==========================================================================*/

#ifndef MEDIAN_FILTER_ALG_INT_H
#define MEDIAN_FILTER_ALG_INT_H

/*--------------------------------------------------------------------------*/
/* This header file inclusion is only for XDAIS module. It accepts specific */
/* data types defined externally                                            */
/*--------------------------------------------------------------------------*/
#include <xdais_types.h>

#include "imedian_filter_ti.h"
#include "median_filter_graph_int.h"

/**
 *  @enum   eMemrecs
 *  @brief  Memory records for Median Filtering application
*/
typedef enum
{
  /* Memory records for handle */
  ALG_HANDLE_MEMREC,
  ALG_HANDLE_INT_MEMREC,
  /* Memory records for median filtering graph */
  GRAPH_OBJ_MEMREC,
  GRAPH_OBJ_INT_MEMREC,
  GRAPH_SCRATCH_MEMREC,
  GRAPH_CONTEXT_MEMREC,
  GRAPH_ARGS_MEMREC,
  NUM_MEMRECS
} eMemrecs;


/**
 *  @enum   eAlgState
 *  @brief  State of Median Filtering application
*/
typedef enum
{
  ALG_NOT_ACTIVE,
  ALG_ACTIVE
} eAlgState;


/**
  @struct MEDIAN_FILTER_TI_Obj
  @brief  This structure is the main handle of Median Filtering
          applet.

  @param  ivision       All public function pointers
  @param  algState      State of algorithm to indicate
  @param  numMemRecs    Number of memory records
  @param  memRec        Array of memory records
  @param  graphMem      BAM specific memory for graph creation
  @param  imageWidth    Width in pixels of the input image
  @param  imageHeight   Height of the input image
  @param  blockWidth    Width of the block over which median has
                        to be computed
  @param  blockHeight   Height of the block over which median has
                        to be computed
  @param  stepSizeHorz  Number of pixels by which the block has
                        to be advanced horizontally
  @param  stepSizeVert  Number of lines by which the block has
                        to be advanced vertically
*/
typedef struct
{
  IVISION_Fxns* ivision;
  uint8_t       algState;
  uint32_t      numMemRecs;
  IALG_MemRec   memRec[NUM_MEMRECS];
  BAM_GraphMem  graphMem;
  uint16_t      imageWidth;
  uint16_t      imageHeight;
  uint8_t       blockWidth;
  uint8_t       blockHeight;
  uint16_t      stepSizeHorz;
  uint16_t      stepSizeVert;
} MEDIAN_FILTER_TI_Obj;

typedef MEDIAN_FILTER_TI_Obj * MEDIAN_FILTER_TI_Handle;

/*--------------------------------------------------------*/
/* IALG functions                                         */
/* Refer XDAIS ialg.h file for details on these functions */
/*--------------------------------------------------------*/
int32_t MEDIAN_FILTER_TI_numAlloc(void);
int32_t MEDIAN_FILTER_TI_alloc(const IALG_Params *params,
  IALG_Fxns **parentFxns, IALG_MemRec memRec[]);
int32_t MEDIAN_FILTER_TI_init(IALG_Handle handle,
  const IALG_MemRec memRec[], IALG_Handle parent, const IALG_Params *params);
void  MEDIAN_FILTER_TI_activate(IALG_Handle handle);
void  MEDIAN_FILTER_TI_deactivate(IALG_Handle handle);
int32_t MEDIAN_FILTER_TI_free(IALG_Handle handle, IALG_MemRec memRec[]);

int32_t MEDIAN_FILTER_TI_control(IVISION_Handle handle, IALG_Cmd cmd,
    const IALG_Params *inParams, IALG_Params *outParams);

int32_t MEDIAN_FILTER_TI_process(IVISION_Handle handle, IVISION_InBufs *inBufs,
    IVISION_OutBufs *outBufs, IVISION_InArgs *inArgs,
    IVISION_OutArgs *outArgs);

/*--------------------------------------------------------*/
/* IRES functions                                         */
/*--------------------------------------------------------*/
XDAS_Int32 MEDIAN_FILTER_TI_getResourceDescriptors(IALG_Handle handle, IRES_ResourceDescriptor *resDesc);

#endif

