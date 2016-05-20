/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
*  @file       rBrief_alg.c
*
*  @brief       This file defines the XDAIS/iVISION functions for rBrief applet
*  @version     0.0 (Dec 2013) : Base version.
*/

/*#pragma CHECK_MISRA ("none")*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
/*#pragma RESET_MISRA ("required")*/

#include "rbrief_alg_int.h"
#include "edma_utils_memcpy.h"
/**
* IVISION interface of the algorithm
*/
const IVISION_Fxns RBRIEF_TI_VISION_FXNS =
{
  {
    (void *)&RBRIEF_TI_VISION_FXNS, /* module ID */
      &RBRIEF_TI_activate,    /* activate */
      &RBRIEF_TI_alloc,       /* algAlloc */
      NULL,                          /* control (not suported) */
      &RBRIEF_TI_deactivate,  /* deactivate */
      &RBRIEF_TI_free,        /* free */
      &RBRIEF_TI_init,        /* init */
      NULL,                          /* moved (not suported) */
      &RBRIEF_TI_numAlloc     /* algNumAlloc  */
  },
  &RBRIEF_TI_process,
  &RBRIEF_TI_control
};


/**
* IRES interface of the algorithm
*/
const IRES_Fxns RBRIEF_TI_IRES = {
  (void *)&RBRIEF_TI_IRES,
  NULL,                                     /*getResourceDescriptors, */
  NULL,                                     /*numResourceDescriptors */
  NULL,                                     /*initResources,  */
  NULL,                                     /*reinitResources, */
  NULL,                                     /*deinitResources, */
  NULL,                                     /*activateResource,*/
  NULL,                                     /*activateAllResources, */
  NULL,                                     /*deactivateResource,   */
  NULL                                      /*deactivateAllResources */
};

/**
* Other exposed functions
*/
int32_t RBRIEF_TI_numAlloc(void)
{
  return NUM_MEMRECS;
}

/*---------------------------------------------------------------*/
/* Function to supply memory requirement to user                 */
/* refer algAlloc function for details in XADIS (ialg.h file)    */
/*---------------------------------------------------------------*/
int32_t RBRIEF_TI_alloc(const IALG_Params *params,
                                                    IALG_Fxns **parentFxns,
                                                    IALG_MemRec memRec[])
{
  int32_t status = IALG_EOK;

  BAM_GraphMemReq graphMem;
  RBRIEF_TI_CreateParams * createParams =
    (RBRIEF_TI_CreateParams*)(void *)params;
  /*---------------------------------------------------------*/
  /* Request BAM public function about memories assosiated   */
  /* to graph creation                                       */
  /*---------------------------------------------------------*/
  RBRIEF_TI_getGraphMemReq(&graphMem);

  /*-----------------------------------------------------------------------------*/
  /*  For memory record ALG_HANDLE_INT_MEMREC and RBRIEF_GRAPH_OBJ_INT_MEMREC,          */
  /*  which are scratch buffers in BAM_MEMSPACE_DMEM, they must be preceded      */
  /*  by a persistent memory record in IALG_EXTERNAL of the same size.           */
  /*  This persistent record will be used to backup the following scratch        */
  /*  memory record during context saving when RBRIEF_TI_deactivate */
  /*  is called. Likewise when RBRIEF_TI_activate it called,        */
  /*  the content of the persistent memory record is copied back to the          */
  /*  scratch memory record in BAM_MEMSPACE_DMEM                                 */
  /*-----------------------------------------------------------------------------*/
  memRec[ALG_HANDLE_MEMREC].size          = sizeof(RBRIEF_TI_Obj);
  memRec[ALG_HANDLE_MEMREC].space         = (IALG_MemSpace)IALG_EXTERNAL;
  memRec[ALG_HANDLE_MEMREC].attrs         = IALG_PERSIST;
  memRec[ALG_HANDLE_MEMREC].alignment     = 4;

  memRec[ALG_HANDLE_INT_MEMREC].size      = sizeof(RBRIEF_TI_Obj);
  memRec[ALG_HANDLE_INT_MEMREC].space     = (IALG_MemSpace)IALG_DARAM0;
  memRec[ALG_HANDLE_INT_MEMREC].attrs     = IALG_SCRATCH;
  memRec[ALG_HANDLE_INT_MEMREC].alignment = 4;

    /*-------------------------------------------------------------------------*/
    /* Below 5 memory records are used to store data related to the BAM graph: */
    /* 1. RBRIEF_GRAPH_OBJ_MEMREC     - To hold graph object in external memory       */
    /* 2. RBRIEF_GRAPH_OBJ_INT_MEMREC - To hold the graph object in internal memory   */
    /* GRAPH OBJECT has 2 instances - internal and external memory - it is to  */
    /* speed up the processing - Main processing will work on internal memory  */
    /* instance and before any one else needing internal memory, deacitavte    */
    /* has to be performed by caller to make sure the data is backed up to ext */
    /* memory                                                                  */
    /*                                                                         */
    /* 3. RBRIEF_GRAPH_SCRATCH_MEMREC -                                               */
    /*  It is used as scratch memory during graph create time                  */
    /*  Scratch mem is currently placed in external memory.                    */
    /*  For faster graph creation time, you can place it in internal memory    */
    /*                                                                         */
    /* 4. RBRIEF_GRAPH_CONTEXT_MEMREC                                                 */
    /*  It is used to backup into external memory the graph's                  */
    /*  nodes internal memory records that are persistent.                     */
    /*                                                                         */
    /* 5. RBRIEF_GRAPH_ARGS_MEMREC  -                                                 */
    /*   It is used keep kernels arguments during graph create time            */
    /*-------------------------------------------------------------------------*/

  memRec[RBRIEF_GRAPH_OBJ_MEMREC].size           = graphMem.graphObjSize;
  memRec[RBRIEF_GRAPH_OBJ_MEMREC].space          = (IALG_MemSpace) IALG_EXTERNAL;
  memRec[RBRIEF_GRAPH_OBJ_MEMREC].attrs          = IALG_PERSIST;
  memRec[RBRIEF_GRAPH_OBJ_MEMREC].alignment      = 4;

  /*
    RBRIEF_GRAPH_OBJ_INT_MEMREC is allocated in DMEM and is used when the backup is
    restored from external memory to faster internal memory when activate is called.
  */
  memRec[RBRIEF_GRAPH_OBJ_INT_MEMREC].size       = graphMem.graphObjSize;
  memRec[RBRIEF_GRAPH_OBJ_INT_MEMREC].space      = (IALG_MemSpace) IALG_DARAM0;
  memRec[RBRIEF_GRAPH_OBJ_INT_MEMREC].attrs      = IALG_SCRATCH;
  memRec[RBRIEF_GRAPH_OBJ_INT_MEMREC].alignment  = 4;

  memRec[RBRIEF_GRAPH_SCRATCH_MEMREC].size       =  graphMem.graphScratchSize;
  memRec[RBRIEF_GRAPH_SCRATCH_MEMREC].space      =  (IALG_MemSpace) IALG_EXTERNAL;
  memRec[RBRIEF_GRAPH_SCRATCH_MEMREC].attrs      =  IALG_SCRATCH;
  memRec[RBRIEF_GRAPH_SCRATCH_MEMREC].alignment  = 4;

  memRec[RBRIEF_GRAPH_CONTEXT_MEMREC].size       =  graphMem.graphcontextSize;
  memRec[RBRIEF_GRAPH_CONTEXT_MEMREC].space      =  (IALG_MemSpace) IALG_EXTERNAL;
  memRec[RBRIEF_GRAPH_CONTEXT_MEMREC].attrs      =  IALG_SCRATCH;
  memRec[RBRIEF_GRAPH_CONTEXT_MEMREC].alignment  = 4;

  memRec[RBRIEF_GRAPH_ARGS_MEMREC].size          =  graphMem.graphArgsSize;
  memRec[RBRIEF_GRAPH_ARGS_MEMREC].space         =  (IALG_MemSpace) IALG_EXTERNAL;
  memRec[RBRIEF_GRAPH_ARGS_MEMREC].attrs         =  IALG_SCRATCH;
  memRec[RBRIEF_GRAPH_ARGS_MEMREC].alignment     = 4;

  /* Following are scratch buffers Needed to copy XY list and Level list in DMEM */
  memRec[RBRIEF_XY_LIST_MEMREC].size       = createParams->maxNumFeatures * sizeof(uint32_t);
  memRec[RBRIEF_XY_LIST_MEMREC].space      = (IALG_MemSpace) IALG_DARAM0;
  memRec[RBRIEF_XY_LIST_MEMREC].attrs      = (IALG_MemAttrs)IVISION_SCRATCH_NOCONTEXT;
  memRec[RBRIEF_XY_LIST_MEMREC].alignment  = 4;

  memRec[RBRIEF_LEVEL_LIST_MEMREC].size       = createParams->maxNumFeatures * sizeof(uint8_t);
  memRec[RBRIEF_LEVEL_LIST_MEMREC].space      = (IALG_MemSpace) IALG_DARAM0;
  memRec[RBRIEF_LEVEL_LIST_MEMREC].attrs      = (IALG_MemAttrs)IVISION_SCRATCH_NOCONTEXT;
  memRec[RBRIEF_LEVEL_LIST_MEMREC].alignment  = 4;

  return (status);
}

/*-----------------------------------------------------------------------*/
/* Function to accept memory pointers from user and initialize algorithm */
/* Refer algInit function for details in XADIS (ialg.h file)             */
/*-----------------------------------------------------------------------*/
int32_t RBRIEF_TI_init(IALG_Handle handle,
                            const IALG_MemRec memRec[],
                            IALG_Handle parent,
                            const IALG_Params * params)
{
  int32_t status = IALG_EOK;
  int32_t bamStatus;

  RBRIEF_TI_CreateParams * createParams =
    (RBRIEF_TI_CreateParams*)(void *)params;

  RBRIEF_TI_graphCreateParams rBriefGraphCreateParams;

  RBRIEF_TI_Handle algHandle =
        (RBRIEF_TI_Handle)(void *)memRec[ALG_HANDLE_MEMREC].base;

  /*-----------------------------------------------------------------------*/
  /* Call BAM Graph creation function with passing all the memories        */
  /*-----------------------------------------------------------------------*/
  algHandle->graphMem.graphObj      = memRec[RBRIEF_GRAPH_OBJ_MEMREC].base;
  algHandle->graphMem.graphScratch  = memRec[RBRIEF_GRAPH_SCRATCH_MEMREC].base;
  algHandle->graphMem.graphcontext  = memRec[RBRIEF_GRAPH_CONTEXT_MEMREC].base;
  algHandle->graphMem.graphArgs     = memRec[RBRIEF_GRAPH_ARGS_MEMREC].base;

  if ( createParams->maxNumFeatures > RBRIEF_TI_MAXNUMFEATURES )
  {
    status = IALG_EFAIL;
    PRINTF("RBRIEF_TI_init() returned error : Max num feature exceeded the limit!!!");
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  rBriefGraphCreateParams.iRbriefCreateParams = createParams;
  algHandle->xyListInDmem     = createParams->xyListInDmem;
  algHandle->levelListInDmem  = createParams->levelListInDmem;
  algHandle->maxNumFeatures   = createParams->maxNumFeatures;
  algHandle->orbPattern       = createParams->orbPattern;

  bamStatus = RBRIEF_TI_graphCreate(&(algHandle->graphMem),&rBriefGraphCreateParams);

  if (bamStatus != BAM_S_SUCCESS)
  {
    status = IALG_EFAIL;
    PRINTF("RBRIEF_TI_graphCreate() returned error!!!");
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  algHandle->numMemRecs  = NUM_MEMRECS;
  memcpy(algHandle->memRec,memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);
  algHandle->ivision = (IVISION_Fxns *)&RBRIEF_TI_VISION_FXNS;

  /*-----------------------------------------------------------------------*/
  /* State to indicate that internal context of algorithm is not active    */
  /*-----------------------------------------------------------------------*/
  algHandle->algState = ALG_NOT_ACTIVE;

Exit:
  return (status);
}

/*-----------------------------------------------------------------------*/
/* Function to accept any run time updates with recreation of object     */
/* Refer algControl function for details in ivision.h file               */
/* Not implemented for this function                                     */
/*-----------------------------------------------------------------------*/
int32_t RBRIEF_TI_control(IVISION_Handle handle,
                                       IALG_Cmd cmd,
                                       const IALG_Params *inParams,
                                       IALG_Params *outParams)
{
  int32_t status = IALG_EOK;

  return (status);
}

/*--------------------------------------------------------------------------*/
/* This is the main processing function and should be called for each frame */
/* Refer process function for details in ivision.h file                     */
/*--------------------------------------------------------------------------*/
/* CHECK_MISRA("-16.7")  -> Disable rule 16.7  */
/* MISRA.PPARAM.NEEDS.CONST:   Pointer parameter is not used to modify the addressed object but is not declared as a pointer to const*/
/* Pointer parameter inBufs and outBufs are not used to modify the addressed object but is not declared as a pointer to const. Fixing this will
    involve changing ivision interface and as this interface is already widely in use we have decided to waive this issue for such incidences */
int32_t RBRIEF_TI_process(IVISION_Handle handle,
                                       IVISION_InBufs *inBufs,
                                       IVISION_OutBufs *outBufs,
                                       IVISION_InArgs *inArgs,
                                       IVISION_OutArgs *outArgs)
{
/* RESET_MISRA("16.7")  -> Reset rule 16.7     */

  RBRIEF_TI_Handle algHandle = (RBRIEF_TI_Handle)(void *)(handle);
  RBRIEF_TI_Handle intAlgHandle;
  int32_t status            = IALG_EOK;
  int32_t bamStatus;

  IBAMALG_InArgs          bamInArgs;
  IBAMALG_OutArgs         bamOutArgs;

  IVISION_BufDesc  xyListBufDesc;
  IVISION_BufDesc  levelListBufDesc;

  IVISION_BufDesc    *(*inBufDesc)[RBRIEF_TI_BUFDESC_IN_TOTAL];
  IVISION_BufDesc    *(*outBufDesc)[RBRIEF_TI_BUFDESC_OUT_TOTAL];


  inBufDesc  = (IVISION_BufDesc *(*)[RBRIEF_TI_BUFDESC_IN_TOTAL])(void *)inBufs->bufDesc;
  outBufDesc = (IVISION_BufDesc *(*)[RBRIEF_TI_BUFDESC_OUT_TOTAL])(void *)outBufs->bufDesc;

  if ( inBufs->numBufs != 3U )
  {
    status = IVISION_ERRORTYPE_NUM_INBUF_EXCEEDED;
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  /*-----------------------------------------------------------------------*/
  /* Activate the algorithm to make sure that now onwards internal memory  */
  /* handle can be utilized                                                */
  /*-----------------------------------------------------------------------*/

  RBRIEF_TI_activate((IALG_Handle)(void *)handle);

  intAlgHandle                      = (RBRIEF_TI_Handle)(void *)algHandle->memRec[ALG_HANDLE_INT_MEMREC].base;
  intAlgHandle->graphMem.graphObj   = intAlgHandle->memRec[RBRIEF_GRAPH_OBJ_INT_MEMREC].base;

  bamInArgs.size                  = sizeof(IBAMALG_InArgs);
  bamInArgs.sliceIndex            = 0;

  bamOutArgs.size                 = sizeof(IBAMALG_OutArgs);


  xyListBufDesc = *((*inBufDesc)[RBRIEF_TI_BUFDESC_IN_XY_LIST]);

  /* Check if the XY list is in DMEM, else DMA one shot into DMEM */
  if(intAlgHandle->xyListInDmem == 0)
  {
    EDMA_UTILS_memcpy2D(intAlgHandle->memRec[RBRIEF_XY_LIST_MEMREC].base,
             (*inBufDesc)[RBRIEF_TI_BUFDESC_IN_XY_LIST]->bufPlanes[0].buf,
             algHandle->maxNumFeatures * sizeof(uint32_t),
             1U,
             0,
             0);
    xyListBufDesc.bufPlanes[0].buf =
              intAlgHandle->memRec[RBRIEF_XY_LIST_MEMREC].base;
  }

  levelListBufDesc = *((*inBufDesc)[RBRIEF_TI_BUFDESC_IN_LEVEL_ID]);

   /* Check if the level id list is in DMEM, else DMA one shot into DMEM */
  if(intAlgHandle->levelListInDmem == 0)
  {
    EDMA_UTILS_memcpy2D(intAlgHandle->memRec[RBRIEF_LEVEL_LIST_MEMREC].base,
             (*inBufDesc)[RBRIEF_TI_BUFDESC_IN_LEVEL_ID]->bufPlanes[0].buf,
             algHandle->maxNumFeatures * sizeof(uint8_t),
             1U,
             0,
             0);
    levelListBufDesc.bufPlanes[0].buf =
                intAlgHandle->memRec[RBRIEF_LEVEL_LIST_MEMREC].base;
  }

   bamStatus = RBRIEF_TI_graphDmaControl(&(intAlgHandle->graphMem),
                                        (*inBufDesc)[RBRIEF_TI_BUFDESC_IN_IMAGEBUFFER],
                                        &xyListBufDesc,
                                        &levelListBufDesc,
                                        outBufs);

  /*-----------------------------------------------------------------------*/
  /* Call execute function                                                 */
  /*-----------------------------------------------------------------------*/
  if (bamStatus == BAM_S_SUCCESS)
  {
    bamStatus =  RBRIEF_TI_execute(&(intAlgHandle->graphMem), &bamInArgs, &bamOutArgs);
  }

  if (bamStatus != BAM_S_SUCCESS)
  {
    status = IALG_EFAIL;
    PRINTF("RBRIEF_TI_process() returned error!!!");
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

Exit:
  /*----------------------------------*/
  /* Free the input and output buffer */
  /*----------------------------------*/
  outArgs->inFreeBufIDs[RBRIEF_TI_BUFDESC_IN_IMAGEBUFFER] =
            (*inBufDesc)[RBRIEF_TI_BUFDESC_IN_IMAGEBUFFER]->bufferId ;

  outArgs->inFreeBufIDs[RBRIEF_TI_BUFDESC_IN_XY_LIST] =
            (*inBufDesc)[RBRIEF_TI_BUFDESC_IN_XY_LIST]->bufferId ;

  outArgs->inFreeBufIDs[RBRIEF_TI_BUFDESC_IN_LEVEL_ID] =
            (*inBufDesc)[RBRIEF_TI_BUFDESC_IN_LEVEL_ID]->bufferId ;

  outArgs->inFreeBufIDs[RBRIEF_TI_BUFDESC_IN_TOTAL]    = 0 ;
  outArgs->outFreeBufIDs[RBRIEF_TI_BUFDESC_OUT_RBRIEF_DESC]   =
            (*outBufDesc)[RBRIEF_TI_BUFDESC_OUT_RBRIEF_DESC]->bufferId ;
  outArgs->outFreeBufIDs[RBRIEF_TI_BUFDESC_OUT_TOTAL]   = 0 ;
  (*outBufDesc)[RBRIEF_TI_BUFDESC_OUT_RBRIEF_DESC]->bufPlanes[0].accessMask =
            IVISION_ACCESSMODE_HWA;

  return status;
}

/*--------------------------------------------------------------------------*/
/* This is the function to do activation of algorithm. All scratch memory   */
/* are restored in this                                                     */
/* Refer algActivate function for details in ialg.h file                    */
/*--------------------------------------------------------------------------*/
void  RBRIEF_TI_activate(IALG_Handle handle)
{
  RBRIEF_TI_Handle algHandle = (RBRIEF_TI_Handle)(void *)(handle);
  int32_t i;

  /*----------------------------------------------------------------*/
  /* Do Activation only if it is deactivated or just after creation */
  /*----------------------------------------------------------------*/
  if(algHandle->algState == ALG_NOT_ACTIVE)
  {
    for(i= 1; i < algHandle->numMemRecs; i++)
    {
      if((i == ALG_HANDLE_INT_MEMREC) ||(i == RBRIEF_GRAPH_OBJ_INT_MEMREC))
      {

        EDMA_UTILS_memcpy2D(algHandle->memRec[i].base,
                            algHandle->memRec[i-1].base,
                            algHandle->memRec[i].size,
                            1U,
                            0,
                            0);
      }

    }
    algHandle->algState = ALG_ACTIVE;
  }

  return;
}

/*--------------------------------------------------------------------------*/
/* This is the function to do de-activation of algorithm. All scratch memory*/
/* are stoed to external memory in this                                     */
/* Refer algDeActivate function for details in ialg.h file                  */
/*--------------------------------------------------------------------------*/
void  RBRIEF_TI_deactivate(IALG_Handle handle)
{
  RBRIEF_TI_Handle algHandle = (RBRIEF_TI_Handle)(void *)(handle);
  int32_t i;
  /*----------------------------------------------------------------*/
  /* Do Activation only if it is deactivated or just after creation */
  /*----------------------------------------------------------------*/
  if(algHandle->algState == ALG_ACTIVE)
  {
    for(i= 1; i < algHandle->numMemRecs; i++)
    {
      if((i == ALG_HANDLE_INT_MEMREC) ||(i == RBRIEF_GRAPH_OBJ_INT_MEMREC))
      {
          EDMA_UTILS_memcpy2D(algHandle->memRec[i-1].base,
                              algHandle->memRec[i].base,
                              algHandle->memRec[i].size,
                              1U,
                              0,
                              0);
      }

    }
    algHandle->algState = ALG_NOT_ACTIVE;
  }

  return;
}

/*--------------------------------------------------------------------------*/
/* This is the function which user can call to get back the memory given to */
/* algo                                                                     */
/* Refer algFree function for details in ialg.h file                        */
/*--------------------------------------------------------------------------*/
int32_t RBRIEF_TI_free(IALG_Handle handle, IALG_MemRec memRec[])
{
  int32_t status            = IALG_EOK;
  RBRIEF_TI_Handle algHandle = (RBRIEF_TI_Handle)(void *)(handle);

  memcpy(memRec, algHandle->memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);

  return status;
}
