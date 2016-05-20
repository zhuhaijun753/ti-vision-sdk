/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       filter_2d_alg_int.h
 *
 *  @brief      This file defines the functions for 2d filter applet
 *  @version 0.0 (Dec 2013) : Base version.
 */


#ifndef FILTER_2D_ALG_INT_H
#define FILTER_2D_ALG_INT_H

/*--------------------------------------------------------------------------*/
/* This header file inclusion is only for XDAIS module. It accepts specific */
/* data types defined externally                                            */
/*--------------------------------------------------------------------------*/
#include <xdais_types.h>

#include "ifilter_2d_ti.h"
#include "filter_2d_graph_int.h"

/*--------------------------------------------------------------------*/
/* These are macros which are algorithm specfic and indicative to BAM */
/* to help decide the optimal block dimensions                        */
/*--------------------------------------------------------------------*/
#define FILTER_2D_TI_BLOCK_WIDTH  (80U)
#define FILTER_2D_TI_BLOCK_HEIGHT (30U)


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
  FILTER_2D_GRAPH_OBJ_MEMREC,
  /* For all the external memory if same copy is expected to be present in
  DMEM than they should be kept consecutive in this enum. This is needed
  because alg activate and deactivate has this assumption*/
  FILTER_2D_GRAPH_OBJ_INT_MEMREC,
  FILTER_2D_GRAPH_SCRATCH_MEMREC,
  FILTER_2D_GRAPH_CONTEXT_MEMREC,
  FILTER_2D_GRAPH_ARGS_MEMREC,
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
  @struct FILTER_2D_TI_Obj
  @brief  This structure is the main handle of 2D filter
          applet.

  @param  ivision    All public function pointers
  @param  algState   State of algorithm to indicate
  @param  numMemRecs Number of memory records
  @param  memRec     Array of memory records
  @param filter2DGraphMem  Graph memory pointers for 2D filter graph
  @param byPassFilterCoeff   This is the memory for filter coefficients. Reason for havin
                                           separate memory is that we overwrite the filter coefficient values
                                           when user only wants to run contrast enhancement
*/
typedef struct
{
  IVISION_Fxns      *ivision;
  uint8_t           algState;
  uint32_t          numMemRecs;
  IALG_MemRec       memRec[NUM_MEMRECS];
  uint8_t           byPassFilterCoeff[2];
  BAM_GraphMem      filter2DGraphMem;
  FILTER_2D_CreateParams createParams;
} FILTER_2D_TI_Obj;

typedef FILTER_2D_TI_Obj * FILTER_2D_TI_Handle;


/*--------------------------------------------------------*/
/* IALG functions                                         */
/* Refer XDAIS ialg.h file for details on these functions */
/*--------------------------------------------------------*/
int32_t FILTER_2D_TI_numAlloc(void);
int32_t FILTER_2D_TI_alloc(const IALG_Params *params,
  IALG_Fxns **parentFxns, IALG_MemRec memRec[]);
int32_t FILTER_2D_TI_init(IALG_Handle handle,
  const IALG_MemRec memRec[], IALG_Handle parent, const IALG_Params *params);
void   FILTER_2D_TI_activate(IALG_Handle handle);
void   FILTER_2D_TI_deactivate(IALG_Handle handle);
int32_t FILTER_2D_TI_free(IALG_Handle handle, IALG_MemRec memRec[]);

int32_t FILTER_2D_TI_control(IVISION_Handle handle, IALG_Cmd cmd,
    const IALG_Params *inParams, IALG_Params *outParams);

int32_t FILTER_2D_TI_process(IVISION_Handle handle, IVISION_InBufs *inBufs,
    IVISION_OutBufs *outBufs, IVISION_InArgs *inArgs,
    IVISION_OutArgs *outArgs);

/*--------------------------------------------------------*/
/* IRES functions                                         */
/*--------------------------------------------------------*/
int32_t FILTER_2D_TI_getResourceDescriptors(IALG_Handle handle, IRES_ResourceDescriptor *resDesc);

#endif /* FILTER_2D_ALG_INT_H */

