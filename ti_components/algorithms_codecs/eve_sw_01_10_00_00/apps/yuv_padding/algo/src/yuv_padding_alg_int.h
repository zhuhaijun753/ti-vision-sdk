/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       yuv_padding_alg_int.h
 *
 *  @brief      This file defines the functions for yuv padding
 *  @date   05 Mar 2014
 */


#ifndef YUV_PADDING_ALG_INT_H
#define YUV_PADDING_ALG_INT_H

/*--------------------------------------------------------------------------*/
/* This header file inclusion is only for XDAIS module. It accepts specific */
/* data types defined externally                                            */
/*--------------------------------------------------------------------------*/
/*#pragma CHECK_MISRA ("none")*/
#include <xdais_types.h>
/*#pragma RESET_MISRA ("required")*/

#include "iyuv_padding_ti.h"
#include "yuv_padding_graph_int.h"

/**
 *  @enum   eMemrecs
 *  @brief  Memory records for image pyra,id application
*/
typedef enum
{
  /* Memory records for handle */
  ALG_HANDLE_MEMREC,
  ALG_HANDLE_INT_MEMREC,
  /* Memory records for graph */
  GRAPH_OBJ_MEMREC,
  GRAPH_OBJ_INT_MEMREC,
  GRAPH_SCRATCH_MEMREC,
  GRAPH_CONTEXT_MEMREC,
  GRAPH_ARGS_MEMREC,
  GRAPH_YUV_LINE_INT_MEMREC,
  NUM_MEMRECS
} eMemrecs;

/**
 *  @enum   eAlgState
 *  @brief  State of application
*/
typedef enum
{
  ALG_NOT_ACTIVE,
  ALG_ACTIVE
} eAlgState;


/**
  @struct YUV_PADDING_TI_Obj
  @brief  This structure is the main handle of 
          applet.

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
  YUV_PADDING_TI_CreateParams createParams ;
} YUV_PADDING_TI_Obj;

typedef YUV_PADDING_TI_Obj * YUV_PADDING_TI_Handle;


/*--------------------------------------------------------*/
/* IALG functions                                         */
/* Refer XDAIS ialg.h file for details on these functions */
/*--------------------------------------------------------*/
XDAS_Int32 YUV_PADDING_TI_numAlloc(void);
XDAS_Int32 YUV_PADDING_TI_alloc(const IALG_Params *params,
  IALG_Fxns **parentFxns, IALG_MemRec *memRec);
XDAS_Int32 YUV_PADDING_TI_init(IALG_Handle handle,
  const IALG_MemRec *memRec, IALG_Handle parent, const IALG_Params *params);
XDAS_Void  YUV_PADDING_TI_activate(IALG_Handle handle);
XDAS_Void  YUV_PADDING_TI_deactivate(IALG_Handle handle);
XDAS_Int32 YUV_PADDING_TI_free(IALG_Handle handle, IALG_MemRec *memRec);

XDAS_Int32 YUV_PADDING_TI_control(IVISION_Handle Handle, IALG_Cmd cmd,
    const IALG_Params *inParams, IALG_Params *outParams);

XDAS_Int32 YUV_PADDING_TI_process(IVISION_Handle Handle, IVISION_InBufs *inBufs,
    IVISION_OutBufs *outBufs, IVISION_InArgs *inArgs,
    IVISION_OutArgs *outArgs);

/*--------------------------------------------------------*/
/* IRES functions                                         */
/*--------------------------------------------------------*/
XDAS_Int32 YUV_PADDING_TI_getResourceDescriptors(IALG_Handle handle, IRES_ResourceDescriptor *resDesc);

#endif /* YUV_PADDING_ALG_INT_H */

