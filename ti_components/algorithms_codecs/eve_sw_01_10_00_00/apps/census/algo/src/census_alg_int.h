/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       imagePyramid_u8_alg_int.h
 *
 *  @brief      This file defines the functions for harris corner detection
 *  @version 0.0 (Dec 2013) : Base version.
 */


#ifndef CENSUS_ALG_INT_H
#define CENSUS_ALG_INT_H

/*--------------------------------------------------------------------------*/
/* This header file inclusion is only for XDAIS module. It accepts specific */
/* data types defined externally                                            */
/*--------------------------------------------------------------------------*/
#pragma CHECK_MISRA ("none")
#include <xdais_types.h>
#pragma RESET_MISRA ("required")

#include "iCensus_ti.h"
#include "evealgframework.h"
#include "bam_common.h"

/**
 *  @enum   eMemrecs
 *  @brief  Memory records for image pyra,id application
*/
typedef enum
{
  /* Memory records for handle */
  ALG_HANDLE_MEMREC,
  ALG_HANDLE_INT_MEMREC,
  /* Memory records for image pyramid graph */
  GRAPH_OBJ_MEMREC,
  GRAPH_OBJ_INT_MEMREC,
  GRAPH_SCRATCH_MEMREC,
  GRAPH_CONTEXT_MEMREC,
  GRAPH_ARGS_MEMREC,
  NUM_MEMRECS
} eMemrecs;

/**
 *  @enum   eAlgState
 *  @brief  State of image pyramid application
*/
typedef enum
{
  ALG_NOT_ACTIVE,
  ALG_ACTIVE
} eAlgState;

/**
  @struct CENSUS_TI_Obj
  @brief  This structure is the main handle of image pyramid
          applet.

  @param  ivision    All public function pointers
  @param  algState   State of algorithm to indicate
  @param  numMemRecs Number of memory records
  @param  memRec     Array of memory records
  @param  graphMem   BAM specific memory for graph creation
  @param  activeImageWidth   Width in bytes of the area that will be accessed by the EDMA when reading the frame.
                             For this function, it should always be equal to (createParams->imgFrameWidth)
  @param  activeImgHeight  Height in number of rows of the area that will be accessed by the EDMA when reading the frame.
                           For this function, it should always be equal to (createParams->imgFrameHeight)
  @param  outputBlockWidth  Output block width returned by BAM_createGraph(). That's useful information to understand performance.
  @param  outputBlockHeight Output block height picked by BAM_createGraph(). That's useful information to understand performance.
  @param  codeWordLen  Census transform codeword's length in bytes
*/
typedef struct
{
  IVISION_Fxns* ivision;
  uint8_t       algState;
  uint32_t      numMemRecs;
  IALG_MemRec   memRec[NUM_MEMRECS];
  BAM_GraphMem  graphMem;
  uint8_t inputBitDepth;
  uint8_t winWidth;
  uint8_t winHeight;
  uint16_t activeImgWidth;
  uint16_t activeImgHeight;
  uint16_t outputBlockWidth;
  uint16_t outputBlockHeight;
  uint8_t numBytesPerCensus;

} CENSUS_TI_Obj;

typedef CENSUS_TI_Obj * CENSUS_TI_Handle;


/*--------------------------------------------------------*/
/* IALG functions                                         */
/* Refer XDAIS ialg.h file for details on these functions */
/*--------------------------------------------------------*/
int32_t CENSUS_TI_numAlloc(void);
int32_t CENSUS_TI_alloc(const IALG_Params *params,
  IALG_Fxns **parentFxns, IALG_MemRec *memRec);
int32_t CENSUS_TI_init(IALG_Handle handle,
  const IALG_MemRec *memRec, IALG_Handle parent, const IALG_Params *params);
XDAS_Void  CENSUS_TI_activate(IALG_Handle handle);
XDAS_Void  CENSUS_TI_deactivate(IALG_Handle handle);
int32_t CENSUS_TI_free(IALG_Handle handle, IALG_MemRec *memRec);

int32_t CENSUS_TI_control(IVISION_Handle handle, IALG_Cmd cmd,
    const IALG_Params *inParams, IALG_Params *outParams);

int32_t CENSUS_TI_process(IVISION_Handle Handle, IVISION_InBufs *inBufs,
    IVISION_OutBufs *outBufs, IVISION_InArgs *inArgs,
    IVISION_OutArgs *outArgs);

/*--------------------------------------------------------*/
/* IRES functions                                         */
/*--------------------------------------------------------*/
int32_t CENSUS_TI_getResourceDescriptors(IALG_Handle handle, IRES_ResourceDescriptor *resDesc);

#endif /* CENSUS_ALG_INT_H */

