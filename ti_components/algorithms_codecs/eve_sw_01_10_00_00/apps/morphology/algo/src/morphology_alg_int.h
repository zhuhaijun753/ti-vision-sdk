/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       morphology_alg_int.h
 *
 *  @brief      This file defines the functions for hough for lines applet
 *  @version 0.0 (July 2014) : Base version.
 */


#ifndef MORPHOLOGY_ALG_INT_H_
#define MORPHOLOGY_ALG_INT_H_

/*--------------------------------------------------------------------------*/
/* This header file inclusion is only for XDAIS module. It accepts specific */
/* data types defined externally                                            */
/*--------------------------------------------------------------------------*/
#include <xdais_types.h>

#include "imorphology_ti.h"
#include "grayscale_morphology.h"
#include "binary_morphology.h"


/**
 *  @enum   eMemrecs
 *  @brief  Memory records for rBrief applet
*/
typedef enum
{
  /* Memory records for handle */
  /* Alg Handle should be first entry in this enum table
         as test app is expecting it to be first entry.            */
  ALG_HANDLE_MEMREC,
  ALG_HANDLE_INT_MEMREC,
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
  @struct MORPHOLOGY_TI_Obj
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
  uint8_t       srcType;
  Grayscale_Morphology_Obj grayscaleMorphologyHandle;
  Binary_Morphology_Obj    binaryMorphologyHandle;
} MORPHOLOGY_TI_Obj;

typedef MORPHOLOGY_TI_Obj * MORPHOLOGY_TI_Handle;


/*--------------------------------------------------------*/
/* IALG functions                                         */
/* Refer XDAIS ialg.h file for details on these functions */
/*--------------------------------------------------------*/
int32_t MORPHOLOGY_TI_numAlloc(void);
int32_t MORPHOLOGY_TI_alloc(const IALG_Params *params,
  IALG_Fxns **parentFxns, IALG_MemRec memRec[]);
int32_t MORPHOLOGY_TI_init(IALG_Handle handle,
  const IALG_MemRec memRec[], IALG_Handle parent, const IALG_Params *params);
void  MORPHOLOGY_TI_activate(IALG_Handle handle);
void  MORPHOLOGY_TI_deactivate(IALG_Handle handle);
int32_t MORPHOLOGY_TI_free(IALG_Handle handle, IALG_MemRec memRec[]);

int32_t MORPHOLOGY_TI_control(IVISION_Handle handle, IALG_Cmd cmd,
    const IALG_Params *inParams, IALG_Params *outParams);

int32_t MORPHOLOGY_TI_process(IVISION_Handle handle, IVISION_InBufs *inBufs,
    IVISION_OutBufs *outBufs, IVISION_InArgs *inArgs, IVISION_OutArgs *outArgs);

/*--------------------------------------------------------*/
/* IRES functions                                         */
/*--------------------------------------------------------*/
XDAS_Int32 MORPHOLOGY_TI_getResourceDescriptors(IALG_Handle handle, IRES_ResourceDescriptor *resDesc);

#endif /* MORPHOLOGY_ALG_INT_H_ */

