/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/** @file yuv_padding_tb.c
*
*  @brief  This file contains test code for YUV padding
*
*
*  @date   Mar 2014
*
*/
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <vcop.h>


#include "evestarterware.h"
#include "alg_osal.h"

#include "xdais_types.h"
#include "iyuv_padding_ti.h"
#include "yuv_padding_config.h"
#include "ti_mem_manager.h"
#include "eve_profile.h"
#include "ti_file_io.h"


#define ENABLE_TRACES 1
#define PRINT_ERRORE_MSG()  TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#define DMEM_SIZE (9*1024)

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
uint8_t DMEM_SCRATCH[DMEM_SIZE];

TIMemObject memObj_DMEM;
int32_t TestApp_AllocMemRecords(IALG_MemRec * memRec,int32_t numMemRec)
{
  int32_t i;
  TIMemHandle memHdl_DMEM = &memObj_DMEM;
  for (i = 0; i < numMemRec; i++)
  {
    if(memRec[i].space == IALG_DARAM0) {
      memRec[i].base = TI_GetMemoryChunk(memHdl_DMEM, memRec[i].size, memRec[i].alignment);
    }
    else {
      memRec[i].base = (Void *) malloc( memRec[i].size);
    }
    if(memRec[i].base == NULL)
    {
      return IALG_EFAIL;
    }
  }
  return IALG_EOK;
}

int32_t TestApp_FreeMemRecords(IALG_MemRec * memRec,int32_t numMemRec)
{
  int32_t i;
  TIMemHandle memHdl_DMEM = &memObj_DMEM;

  for (i = 0; i < numMemRec; i++)
  {
    if(memRec[i].base == NULL)
    {
      return IALG_EFAIL;
    }
    if(memRec[i].space == IALG_DARAM0) {
      TI_ResetMemoryHandle(memHdl_DMEM);
    }else {
      free(memRec[i].base);
    }
  }
  return IALG_EOK;
}

typedef struct IM_Fxns
{
  IVISION_Fxns * ivision;

} IM_Fxns;


int32_t TestApp_ReadInBufs(uint8_t * ptr,uint8_t * ptrC, int32_t currFrameNum, char * fileName,int32_t imPitch)
{
  TI_FILE * fp;
  int32_t i;
  int32_t lumaSize   = gParams.imWidth * gParams.imHeight ;
  int32_t ChromaSize = lumaSize/2;

  fp = FOPEN(fileName, "rb");
  FSEEK(fp, currFrameNum*(lumaSize+ChromaSize), SEEK_SET);
  for(i = 0; i < gParams.imHeight; i++)
  {
    FREAD((ptr + imPitch*i),1,gParams.imWidth,fp);
  }
  for(i = 0; i < gParams.imHeight/2; i++)
  {
    FREAD((ptrC + imPitch*i),1,gParams.imWidth,fp);
  }
  FCLOSE(fp);

  return (0);
}


int32_t TestApp_WrtiteOutBufs(uint8_t * ptr, uint8_t * ptrC, char * fileName)
{
  TI_FILE * fp;
  static int firtsWrite = 1;
  int32_t size = (gParams.imWidth + gParams.leftPadding + gParams.rightPadding )* (gParams.imHeight + gParams.topPadding  + gParams.BottomPadding);
  int32_t retVal;
  if(firtsWrite)
  {
    fp = FOPEN(fileName, "wb+");
    FCLOSE(fp);
    firtsWrite = 0;
  }
  fp = FOPEN(fileName, "ab+");
  retVal = FWRITE(ptr,1,size,fp);
  if(retVal != size)
  {
    printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
  }
  retVal = FWRITE(ptrC,1,size/2,fp);
  if(retVal != size/2)
  {
    printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
  }
  FCLOSE(fp);
  return (0);
}

int32_t TestApp_ComapreOutBufs(uint8_t * ptr, uint8_t * ptrC, char * fileName, int32_t currFrameNum )
{
  TI_FILE * fp;
  int32_t size = (gParams.imWidth + gParams.leftPadding + gParams.rightPadding )* (gParams.imHeight + gParams.topPadding  + gParams.BottomPadding);
  int32_t retVal;
  uint8_t * refdata;
  refdata = (uint8_t *)malloc(size);
  if(refdata == NULL)
  {
    printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
    return(-1);
  }

  fp = FOPEN(fileName, "rb");
  if(fp == NULL)
  {
    printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
    return(-1);
  }
  FSEEK(fp, currFrameNum*(size+size/2), SEEK_SET);

  retVal = FREAD(refdata,1,size,fp);
  if(retVal != size)
  {
    printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
    return(-1);
  }
  retVal = memcmp(refdata,ptr,size);
  if(retVal)
  {
    printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
    return(retVal);
  }

  retVal = FREAD(refdata,1,size/2,fp);
  if(retVal != size/2)
  {
    printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
    return(-1);
  }
  retVal = memcmp(refdata,ptrC,size/2);
  if(retVal)
  {
    printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
    return(retVal);
  }

  FCLOSE(fp);
  return (0);
}

int test_yuv_padding(void)
{
  int i=0,result = 0;

  uint8_t *input;
  uint8_t *inputChroma;

  int32_t numMemRec;
  IALG_MemRec *memRec;
  int32_t status;
  int32_t failed = 0;
  int32_t inBuffSize;

  /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
  IM_Fxns *     handle;

  /*-----------------------------------------------------------------
  Algorithm parameters memory in stack
  -----------------------------------------------------------------*/
  YUV_PADDING_TI_CreateParams  createParams;

  IVISION_InArgs    inArgs;
  IVISION_InBufs    inBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inBufDesc;
  IVISION_BufDesc   *inBufDescList[1];

  YUV_PADDING_TI_outArgs   outArgs;
  IVISION_OutBufs                  outBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   *outBufDescList[1];

  profiler_init();
  outArgs.iVisionOutArgs.size = sizeof(YUV_PADDING_TI_outArgs);

  /*--------------------------------------------------------------------------*/
  /*Create memory handle for ARP32 DMEM.                                      */
  /*--------------------------------------------------------------------------*/
  uint8_t *pDmem;
  TIMemHandle memHdl_DMEM;

  pDmem = (uint8_t *)&DMEM_SCRATCH;
  memHdl_DMEM = &memObj_DMEM;
  TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);

  /*-----------------------------------------------------------------
  Set algorithm parameters
  -----------------------------------------------------------------*/
  createParams.visionParams.algParams.size   = sizeof(YUV_PADDING_TI_CreateParams);
  createParams.visionParams.cacheWriteBack   = NULL;
  createParams.topPadding                  = gParams.topPadding    ;
  createParams.leftPadding                 = gParams.leftPadding   ;
  createParams.rightPadding                = gParams.rightPadding  ;
  createParams.BottomPadding               = gParams.BottomPadding ;
  createParams.maxImageWidth               = gParams.imWidth;

  /*---------------------------------------------------
  Query alogorithm memory requirement using standard IALG interface
  -----------------------------------------------------------------*/

#if ENABLE_TRACES
  TEST_PRINTF("Algorithm Init Start\n");
#endif
  profiler_initStack(profiler_getSP());
  profiler_start();

  numMemRec = YUV_PADDING_TI_VISION_FXNS.ialg.algNumAlloc();
  memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

  status = YUV_PADDING_TI_VISION_FXNS.ialg.algAlloc(
    (IALG_Params *)(&createParams), NULL, memRec);

  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
    goto EXIT_LOOP;
  }

  inBuffSize = (gParams.imWidth + gParams.leftPadding + gParams.rightPadding )* (gParams.imHeight + gParams.topPadding  + gParams.BottomPadding);

  /* Generate random input data */
  input           = (uint8_t*)malloc(inBuffSize);
  inputChroma     = (uint8_t*)malloc(inBuffSize/2);


  inBufs.bufDesc  = inBufDescList;
  outBufs.bufDesc = outBufDescList;

  inBufs.numBufs   = 1;
  outBufs.numBufs  = 1;

  inBufDescList[0]     = &inBufDesc;
  outBufDescList[0]    = &inBufDesc;


  /*-----------------------------------------------------------------
  Allocate memory for all the mem records
  Application has to implement the below function
  Refer the example implementation below in this file
  -----------------------------------------------------------------*/
  status = TestApp_AllocMemRecords(memRec,numMemRec);
  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
    goto EXIT_LOOP;
  }
  /*-----------------------------------------------------------------
  Intialize the algorithm instance with the allocated memory
  and user create parameters
  -----------------------------------------------------------------*/
  status = YUV_PADDING_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
    memRec,NULL,(IALG_Params *)(&createParams));

  handle = (IM_Fxns *) memRec[0].base;
  profiler_end_print(0);

  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
    goto EXIT_LOOP;
  }
#if ENABLE_TRACES
  TEST_PRINTF("Algorithm Init Done\n");
#endif


  inArgs.subFrameInfo = 0;
  inArgs.size                  = sizeof(IVISION_InArgs);

  inBufDesc.numPlanes                          = 2;
  inBufDesc.bufPlanes[0].frameROI.topLeft.x    = gParams.leftPadding;
  inBufDesc.bufPlanes[0].frameROI.topLeft.y    = gParams.topPadding ;

  inBufDesc.bufPlanes[0].width                 = gParams.imWidth +  gParams.leftPadding + gParams.rightPadding ;
  inBufDesc.bufPlanes[0].height                = gParams.imHeight +  gParams.topPadding  + gParams.BottomPadding;
  inBufDesc.bufPlanes[0].frameROI.width        = gParams.imWidth;
  inBufDesc.bufPlanes[0].frameROI.height       = gParams.imHeight;

  inBufDesc.bufPlanes[0].buf = (uint8_t * )input ;

  inBufDesc.bufPlanes[1].frameROI.topLeft.x    = gParams.leftPadding;
  inBufDesc.bufPlanes[1].frameROI.topLeft.y    = gParams.topPadding/2 ;

  inBufDesc.bufPlanes[1].width                 = inBufDesc.bufPlanes[0].width ;
  inBufDesc.bufPlanes[1].height                = inBufDesc.bufPlanes[0].height/2;
  inBufDesc.bufPlanes[1].frameROI.width        = gParams.imWidth;
  inBufDesc.bufPlanes[1].frameROI.height       = gParams.imHeight/2;

  inBufDesc.bufPlanes[1].buf = (uint8_t * )inputChroma ;


  /*------------------------------------------------------------*/
  /* This function actually sets Enable bit in the CT CNTL      */
  /* register of SCTM. Parameter CTM is defined in              */
  /* baseaddress.h, and is used by cred macros to compute       */
  /* baseaddress of CTM.                                        */
  /*------------------------------------------------------------*/
  EVE_SCTM_Enable(CTM);

  /*------------------------------------------------------------*/
  /* Configure Counter 0, to measure "vcop_busy" which is a     */
  /* duration signal, and enable the counter.                   */
  /*------------------------------------------------------------*/
  EVE_SCTM_CounterConfig(CTM, SCTM_Counter_0, VCOP_BUSY, SCTM_DURATION);
  EVE_SCTM_CounterTimerEnable(CTM, SCTM_Counter_0);


  if((inBufDesc.bufPlanes[0].buf == NULL) || (inBufDesc.bufPlanes[1].buf == NULL))
  {
    PRINT_ERRORE_MSG();
    goto EXIT_LOOP;
  }
  for(i = 0; i < gParams.numFrames; i++)
  {
#if 1
      TestApp_ReadInBufs(((uint8_t * )input) + inBufDesc.bufPlanes[0].width*gParams.topPadding + gParams.leftPadding,
                         ((uint8_t * )inputChroma) + inBufDesc.bufPlanes[0].width*gParams.topPadding/2 + gParams.leftPadding,
                         i,(char *)gParams.inImage,inBufDesc.bufPlanes[0].width);
#endif

#if ENABLE_TRACES
    TEST_PRINTF("Processing Started for frame num : %d\n",i);
#endif

    profiler_start();
   
    status = handle->ivision->algProcess((IVISION_Handle)handle,
      &inBufs,&outBufs,&inArgs,(IVISION_OutArgs *)&outArgs);

    profiler_end_print(1);

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }

    TestApp_WrtiteOutBufs(input,inputChroma,(char *)gParams.outImage);
    failed |= TestApp_ComapreOutBufs(input,inputChroma,(char *)gParams.refImage,i);

    if(failed != 0)
    {
      goto EXIT_LOOP;
    }

#if ENABLE_TRACES
    TEST_PRINTF("Processing End\n");
#endif
  }

EXIT_LOOP:
  profiler_printStatus(failed);
  status = handle->ivision->ialg.algFree((IALG_Handle)(handle), memRec);
  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
  }
  /* Here Free memory for all the mem records */
  status = TestApp_FreeMemRecords(memRec,numMemRec);
  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
  }

  if ( memRec != NULL )
  {
    free(memRec);
  }

  if (input != NULL)
  {
    free(input);
  }
  /* Get the stack usage */
#if !(VCOP_HOST_EMULATION)
  profiler_getStackDepth();
#endif
 return result;
}

int main(int argc, char *argv[])
{
  int status = 0;
  char configFile[FILE_NAME_SIZE]={0};

  report_printAppletInfo((int8_t *)"YUV_PADDING_TI_VISION");


  if (argc > 1)
  {
    strcpy(configFile, argv[1]) ;
  }
  else
  {
    strcpy(configFile,"../testvecs/config/yuv_padding.cfg");
  }

  status = readparamfile(configFile, &gsTokenMap_yuv_padding[0]) ;
  if(status == -1)
  {
    printf("Parser Failed");
    return -1 ;
  }

  profiler_testCaseInfo((int8_t *)gParams.testCaseName,(int8_t *)gParams.testCaseDesc,gParams.performanceTestcase);
  printparams(&gsTokenMap_yuv_padding[0],(int32_t)MAX_ITEMS_TO_PARSE,(uint32_t)(&gParams),sizeof(yuv_padding_config)) ;

  /* Validate the applet */
  status = test_yuv_padding();



  return status;
}

