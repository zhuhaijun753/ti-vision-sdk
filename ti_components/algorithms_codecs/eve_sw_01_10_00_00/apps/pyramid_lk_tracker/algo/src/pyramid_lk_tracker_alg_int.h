/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       pyramid_lk_tracker_alg_int.h
 *
 *  @brief      This file defines the functions for pyramid_lk_tracker applet
 *  @version 0.0 (Dec 2013) : Base version.
 */

#ifndef PYRAMID_LK_TRACKER_ALG_INT_H
#define PYRAMID_LK_TRACKER_ALG_INT_H

/*--------------------------------------------------------------------------*/
/* This header file inclusion is only for XDAIS module. It accepts specific */
/* data types defined externally                                            */
/*--------------------------------------------------------------------------*/
#include <xdais_types.h>

#include "ipyramid_lk_tracker_ti.h"
#include "pyramid_lk_tracker_graph_int.h"

#define VCOP_LK_MIN_IM_SIZE                   ((7U)+2U)

/**
 *  @enum   eMemrecs
 *  @brief  Memory records for Pyramid LK Tracker application
*/
typedef enum
{
  /* Memory records for handle */
 /* Alg Handle should be first entry in this enum table
  as test app is expecting it to be first entry*/
  ALG_HANDLE_MEMREC,
  ALG_HANDLE_INT_MEMREC,
  /* Memory records for Pyramid LK Tracker graph */
  LK_TRACKER_GRAPH_OBJ_MEMREC,
  /* For all the external memory if same copy is expected to be present in
  DMEM than they should be kept consecutive in this enum. This is needed
  because alg activate and deactivate has this assumption*/
  LK_TRACKER_GRAPH_OBJ_INT_MEMREC,
  LK_TRACKER_GRAPH_SCRATCH_MEMREC,
  LK_TRACKER_GRAPH_CONTEXT_MEMREC,
  LK_TRACKER_GRAPH_ARGS_MEMREC,
  /* Applet specific scratch buffers */
  LK_TRACKER_PREVXYLIST_MEMREC,
  LK_TRACKER_CURRXYLIST_MEMREC,
  LK_TRACKER_DMACTRL_MEMREC,
  LK_TRACKER_DMACTRL_INT_MEMREC,
  LK_TRACKER_KERNELSCTRL_MEMREC,
  NUM_MEMRECS
} eMemrecs;

/**
 *  @enum   eAlgState
 *  @brief  State of Pyramid LK Tracker application
*/
typedef enum
{
  ALG_NOT_ACTIVE,
  ALG_ACTIVE
} eAlgState;

/**
  @struct PYRAMID_LK_TRACKER_TI_Obj
  @brief  This structure is the main handle of pyramid_lk_tracker
          applet.

  @param  ivision             All public function pointers
  @param  algState            State of algorithm to indicate
  @param  numMemRecs          Number of memory records
  @param  memRec              Array of memory records
  @param  lkTrackerGraphMem   BAM specific memory for graph creation
  @param  imWidth             Width in bytes for the input image
  @param  imHeight            Height in bytes for the input image
  @param  numLevels           Number of levels for the pyramid
  @param  numKeyPoints        Number of key points to be tracked
  @param  maxItersLK          Maximum number of iteration
  @param  searchRange         Search range in pixel for each level
  @param  minErrValue         Minimum flow vector difference value that needs to be
                              considered as no motion and exit the iteration
*/
typedef struct
{
  IVISION_Fxns* ivision;
  uint8_t       algState;
  uint32_t      numMemRecs;
  IALG_MemRec   memRec[NUM_MEMRECS];
  uint16_t      imWidth  ;
  uint16_t      imHeight ;
  uint16_t      numLevels;
  uint16_t      numKeyPoints;
  uint16_t      maxItersLK[PYRAMID_LK_TRACKER_TI_MAXLEVELS];
  uint16_t      minErrValue[PYRAMID_LK_TRACKER_TI_MAXLEVELS];
  uint8_t       searchRange[PYRAMID_LK_TRACKER_TI_MAXLEVELS];
  BAM_GraphMem  lkTrackerGraphMem;
} PYRAMID_LK_TRACKER_TI_Obj;

typedef PYRAMID_LK_TRACKER_TI_Obj * PYRAMID_LK_TRACKER_TI_Handle;

/*--------------------------------------------------------*/
/* IALG functions                                         */
/* Refer XDAIS ialg.h file for details on these functions */
/*--------------------------------------------------------*/
XDAS_Int32 PYRAMID_LK_TRACKER_TI_numAlloc(void);
XDAS_Int32 PYRAMID_LK_TRACKER_TI_alloc(const IALG_Params *params,
  IALG_Fxns **parentFxns, IALG_MemRec *memRec);
XDAS_Int32 PYRAMID_LK_TRACKER_TI_init(IALG_Handle handle,
  const IALG_MemRec *memRec, IALG_Handle parent, const IALG_Params *params);
XDAS_Void  PYRAMID_LK_TRACKER_TI_activate(IALG_Handle handle);
XDAS_Void  PYRAMID_LK_TRACKER_TI_deactivate(IALG_Handle handle);
XDAS_Int32 PYRAMID_LK_TRACKER_TI_free(IALG_Handle handle, IALG_MemRec *memRec);
XDAS_Int32 PYRAMID_LK_TRACKER_TI_control(IVISION_Handle handle, IALG_Cmd cmd,
    const IALG_Params *inParams, IALG_Params *outParams);
XDAS_Int32 PYRAMID_LK_TRACKER_TI_process(IVISION_Handle handle, IVISION_InBufs *inBufs,
    IVISION_OutBufs *outBufs, IVISION_InArgs *inArgs,
    IVISION_OutArgs *outArgs);

/*--------------------------------------------------------*/
/* IRES functions                                         */
/*--------------------------------------------------------*/
XDAS_Int32 PYRAMID_LK_TRACKER_TI_getResourceDescriptors(IALG_Handle handle, IRES_ResourceDescriptor *resDesc);
#endif /* PYRAMID_LK_TRACKER_ALG_INT_H */
