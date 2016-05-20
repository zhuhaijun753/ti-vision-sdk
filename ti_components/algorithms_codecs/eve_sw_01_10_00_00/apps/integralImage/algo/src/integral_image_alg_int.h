/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       integral_image_alg_int.h
 *
 *  @brief      This file defines the functions for integral image algorithm
 *  @version 0.0 (Jul 2014) : Base version.
 */


#ifndef INTEGRAL_IMAGE_TI_ALG_INT_H
#define INTEGRAL_IMAGE_TI_ALG_INT_H

/*--------------------------------------------------------------------------*/
/* This header file inclusion is only for XDAIS module. It accepts specific */
/* data types defined externally                                            */
/*--------------------------------------------------------------------------*/
#include <xdais_types.h>

#include "iIntegral_image_ti.h"
#include "evealgframework.h"
#include "bam_common.h"

/**
 *  @enum   eMemrecs
 *  @brief  Memory records for Integral image application
*/
typedef enum
{
  ALG_HANDLE_MEMREC,
  ALG_HANDLE_INT_MEMREC,
  GRAPH_OBJ_MEMREC,
  GRAPH_OBJ_INT_MEMREC,
  GRAPH_SCRATCH_MEMREC,
  GRAPH_CONTEXT_MEMREC,
  GRAPH_ARGS_MEMREC,
  INTEGRAL_IMAGE_ACC_MEMREC,
  NUM_MEMRECS
} eMemrecs;

/**
 *  @enum   eAlgState
 *  @brief  State of Integral image application
*/
typedef enum
{
  ALG_NOT_ACTIVE,
  ALG_ACTIVE
} eAlgState;

/**
  @struct INTEGRAL_IMAGE_TI_Obj
  @brief  This structure is the main handle of integral image
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
  uint16_t      blockWidth;
  uint16_t      blockHeight;
} INTEGRAL_IMAGE_TI_Obj;

typedef INTEGRAL_IMAGE_TI_Obj *INTEGRAL_IMAGE_TI_Handle;


/*--------------------------------------------------------*/
/* IALG functions                                         */
/* Refer XDAIS ialg.h file for details on these functions */
/*--------------------------------------------------------*/
int32_t INTEGRAL_IMAGE_TI_numAlloc(void);
int32_t INTEGRAL_IMAGE_TI_alloc(const IALG_Params *params,
  IALG_Fxns **parentFxns, IALG_MemRec memRec[]);
int32_t INTEGRAL_IMAGE_TI_init(IALG_Handle handle,
  const IALG_MemRec memRec[], IALG_Handle parent, const IALG_Params *params);
XDAS_Void  INTEGRAL_IMAGE_TI_activate(IALG_Handle handle);
XDAS_Void  INTEGRAL_IMAGE_TI_deactivate(IALG_Handle handle);
int32_t INTEGRAL_IMAGE_TI_free(IALG_Handle handle, IALG_MemRec *memRec);

int32_t INTEGRAL_IMAGE_TI_control(IVISION_Handle Handle, IALG_Cmd cmd,
    const IALG_Params *inParams, IALG_Params *outParams);

int32_t INTEGRAL_IMAGE_TI_process(IVISION_Handle Handle, IVISION_InBufs *inBufs,
    IVISION_OutBufs *outBufs, IVISION_InArgs *inArgs,
    IVISION_OutArgs *outArgs);

/*--------------------------------------------------------*/
/* IRES functions                                         */
/*--------------------------------------------------------*/
int32_t INTEGRAL_IMAGE_TI_getResourceDescriptors(IALG_Handle handle, IRES_ResourceDescriptor *resDesc);

#endif

