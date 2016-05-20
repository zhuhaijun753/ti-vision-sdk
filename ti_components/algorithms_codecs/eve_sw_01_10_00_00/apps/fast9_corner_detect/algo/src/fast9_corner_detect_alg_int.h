/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       fast_corner_detect_alg_int.h
 *
 *  @brief      This file defines the functions for FAST9 applet
 *  @version 0.0 (Dec 2013) : Base version.
 */


#ifndef FAST9_CORNER_DETECT_ALG_INT_H
#define FAST9_CORNER_DETECT_ALG_INT_H

/*--------------------------------------------------------------------------*/
/* This header file inclusion is only for XDAIS module. It accepts specific */
/* data types defined externally                                            */
/*--------------------------------------------------------------------------*/
#include <xdais_types.h>

#include "ifast9_corner_detect_ti.h"
#include "fast9_corner_detect_graph_int.h"
#include "binary_image_to_list_graph_int.h"

/**
 *  @enum   eMemrecs
 *  @brief  Memory records for FAST9 Corner Detector application
*/
typedef enum
{
  /* Memory records for handle */
 /* Alg Handle should be first entry in this enum table
  as test app is expecting it to be first entry*/
  ALG_HANDLE_MEMREC,
  ALG_HANDLE_INT_MEMREC,
  /* Memory records for Fast9 graph */
  FAST9_GRAPH_OBJ_MEMREC,
  /* For all the external memory if same copy is expected to be present in
  DMEM than they should be kept consecutive in this enum. This is needed
  because alg activate and deactivate has this assumption*/
  FAST9_GRAPH_OBJ_INT_MEMREC,
  FAST9_GRAPH_SCRATCH_MEMREC,
  FAST9_GRAPH_CONTEXT_MEMREC,
  FAST9_GRAPH_ARGS_MEMREC,
  /* Memory records for Binary image to list graph */
  BIN2LIST_GRAPH_OBJ_MEMREC,
  BIN2LIST_GRAPH_OBJ_INT_MEMREC,
  BIN2LIST_GRAPH_SCRATCH_MEMREC,
  BIN2LIST_GRAPH_CONTEXT_MEMREC,
  BIN2LIST_GRAPH_ARGS_MEMREC,
  /* Applet specific scratch buffers */
  BIN_IMG_SCRATCH_MEMREC,
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
  @struct FAST9_CORNER_DETECT_TI_Obj
  @brief  This structure is the main handle of fast9 corner detect
          applet.

  @param  ivision    All public function pointers
  @param  algState   State of algorithm to indicate
  @param  numMemRecs Number of memory records
  @param  memRec     Array of memory records
  @param  graphMem   BAM specific memory for graph creation
  @param  numLevels  Number of levels for which this applet needs to run
  @param  activeImageWidth[]   active image width on which this applet will be working for all levels
  @param  activeImageHeight[]  active image height on which this applet will be working for all levels
  @param blockWidth[] blockWidth to be used for all levels
  @param blockHeight[] blockHeight to be used for all levels
  @param  dx[]  Horizontal Offset of the partial image on which corner detection is working to
              satisfy DMA and kernel constraints for all levels
  @param  dy[]  Vertical Offset of the partial image on which corner detection is working to
              satisfy DMA and kernel constraints for all levels
  @param  activeBinImgWidth[]   active image width on which this applet will be working for all levels for bin to img list graph
  @param  activeBinImgHeight[]  active image height on which this applet will be working for all levels for bin to img list graph
  @param blockWidthBinImgToList[] blockWidth to be used for all levels for bin to img list graph
  @param blockHeightBinImgToList[] blockHeight to be used for all levels for bin to img list graph
  @param  dx_binImg[]  Horizontal Offset of the partial image on which corner detection is working to
              satisfy DMA and kernel constraints for all levels
  @param  dy_binImg[]  Vertical Offset of the partial image on which corner detection is working to
              satisfy DMA and kernel constraints for all levels
*/
typedef struct
{
  IVISION_Fxns* ivision;
  uint8_t       algState;
  uint32_t      numMemRecs;
  IALG_MemRec   memRec[NUM_MEMRECS];
  BAM_GraphMem  fast9GraphMem;
  BAM_GraphMem  binToListGraphMem;
  uint8_t       numLevels;
  /* Fast9 corner detect parameters */
  uint16_t      activeImageWidth[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  uint16_t      activeImageHeight[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  uint16_t      blockWidth[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  uint16_t      blockHeight[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  uint16_t      dx[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  uint16_t      dy[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  /* Binary image to list parameters*/
  uint16_t      activeBinImgWidth[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  uint16_t      activeBinImgHeight[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  uint16_t      blockWidthBinImgToList[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  uint16_t      blockHeightBinImgToList[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  uint16_t      dx_binImg[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  uint16_t      dy_binImg[FAST9_CORNER_DETECT_TI_MAXLEVELS];
} FAST9_CORNER_DETECT_TI_Obj;

typedef FAST9_CORNER_DETECT_TI_Obj * FAST9_CORNER_DETECT_TI_Handle;


/*--------------------------------------------------------*/
/* IALG functions                                         */
/* Refer XDAIS ialg.h file for details on these functions */
/*--------------------------------------------------------*/
int32_t FAST9_CORNER_DETECT_TI_numAlloc(void);
int32_t FAST9_CORNER_DETECT_TI_alloc(const IALG_Params *params,
  IALG_Fxns **parentFxns, IALG_MemRec memRec[]);
int32_t FAST9_CORNER_DETECT_TI_init(IALG_Handle handle,
  const IALG_MemRec memRec[], IALG_Handle parent, const IALG_Params *params);
void  FAST9_CORNER_DETECT_TI_activate(IALG_Handle handle);
void  FAST9_CORNER_DETECT_TI_deactivate(IALG_Handle handle);
int32_t FAST9_CORNER_DETECT_TI_free(IALG_Handle handle, IALG_MemRec memRec[]);

int32_t FAST9_CORNER_DETECT_TI_control(IVISION_Handle handle, IALG_Cmd cmd,
    const IALG_Params *inParams, IALG_Params *outParams);

int32_t FAST9_CORNER_DETECT_TI_process(IVISION_Handle handle, IVISION_InBufs *inBufs,
    IVISION_OutBufs *outBufs, IVISION_InArgs *inArgs,
    IVISION_OutArgs *outArgs);

/*--------------------------------------------------------*/
/* IRES functions                                         */
/*--------------------------------------------------------*/
int32_t FAST9_CORNER_DETECT_TI_getResourceDescriptors(IALG_Handle handle, IRES_ResourceDescriptor *resDesc);

#endif /* FAST9_CORNER_DETECT_ALG_INT_H */

