/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/** @file yuv_scalar_tb.c
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
#include "iyuv_scalar_ti.h"
#include "yuv_scalar_config.h"
#include "ti_mem_manager.h"
#include "eve_profile.h"
#include "ti_file_io.h"
#include "vcop_yuv_scalar_cn.h"

#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define MAX_INPUT_LINE_SIZE      (300)
#define MAX_INPUT_VALUE_SIZE      (20)

#define ENABLE_FILE_IO (1)

#define CONFIG_LIST_FILE_NAME    ("..\\testvecs\\config\\config_list.txt")

#define Q_FORMATE_SCALE_RATIO                   (12)
#define Q_FORMATE_FRAC_WEIGHT                   (4)

#define ALIGN_SIZE(x,y) (((x + (y-1)) / y) * y)


#define PRINT_ERRORE_MSG()  TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#define DMEM_SIZE (19*1024)

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

char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '	'))
  {
    LinePtr++;
  }
  return(LinePtr);
}

int32_t TestApp_ReadInBufs(uint8_t * ptr,uint8_t * ptrC, int32_t currFrameNum, char * fileName)
{
#if ENABLE_FILE_IO
  int32_t lumaSize   = gParams.imWidth * gParams.imHeight ;
  int32_t ChromaSize = lumaSize/2;
  TI_FILE * fp;
  fp = FOPEN(fileName, "rb");
  FSEEK(fp, currFrameNum*(lumaSize+ChromaSize), SEEK_SET);
  FREAD(ptr, 1,lumaSize,fp);
  FREAD(ptrC,1,ChromaSize,fp);
  FCLOSE(fp);
#endif
  return (0);
}


int32_t TestApp_WrtiteOutBufs(uint8_t * ptr, uint8_t * ptrC, char * fileName)
{
#if ENABLE_FILE_IO
  TI_FILE * fp;
  static int firtsWrite = 1;
  int32_t size = gParams.outWidth * gParams.outHeight;
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

#endif
  return (0);
}


int test_yuv_scalar(void)
{
  int i=0,x,y,result = 0,failed=0;
  uint8_t *inLuma   ;
  uint8_t *inChroma ;
  uint8_t *refLuma  ;
  uint8_t *refChroma;
  uint8_t *eveLuma  ;
  uint8_t *eveChroma;

  uint16_t blockWidth  = 192;
  uint16_t blockHeight = 64;

  int32_t inLumaSize    = 2 * gParams.imWidth * gParams.imHeight ;
  int32_t inChromaSize  = inLumaSize/2;
  int32_t outLumaSize   = gParams.outWidth * gParams.outHeight ;
  int32_t outChromaSize = outLumaSize/2;

  uint16_t eveOutWidth    = ALIGN_SIZE(gParams.outWidth,blockWidth);
  uint16_t eveOutHeight   = ALIGN_SIZE(gParams.outHeight,blockHeight);
  uint16_t eveOutHeight1  = ALIGN_SIZE((gParams.outHeight/2),blockHeight);

  uint32_t eveLumaSize   = eveOutWidth*eveOutHeight;
  uint32_t eveChromaSize = eveOutWidth*eveOutHeight1;

  int32_t numMemRec;
  IALG_MemRec *memRec;
  int32_t status;

  /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
  IM_Fxns *     handle;

  /*-----------------------------------------------------------------
  Algorithm parameters memory in stack
  -----------------------------------------------------------------*/
  YUV_SCALAR_TI_CreateParams  createParams;

  YUV_SCALAR_TI_InArgs    inArgs;
  IVISION_InBufs    inBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inBufDesc;
  IVISION_BufDesc   outBufDesc;
  IVISION_BufDesc   *inBufDescList[1];

  YUV_SCALAR_TI_outArgs            outArgs;
  IVISION_OutBufs                  outBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   *outBufDescList[1];
  /*--------------------------------------------------------------------------*/
  /*Create memory handle for ARP32 DMEM.                                      */
  /*--------------------------------------------------------------------------*/
  uint8_t *pDmem;
  TIMemHandle memHdl_DMEM;

  pDmem = (uint8_t *)&DMEM_SCRATCH;
  memHdl_DMEM = &memObj_DMEM;
  TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);
  profiler_init();
  profiler_initStack(profiler_getSP());
  profiler_start();

  /*-----------------------------------------------------------------
  Set algorithm parameters
  -----------------------------------------------------------------*/
  createParams.visionParams.algParams.size   = sizeof(YUV_SCALAR_TI_CreateParams);
  createParams.visionParams.cacheWriteBack   = NULL;
  createParams.maxWidth                      = gParams.outWidth    ;
  createParams.maxHeight                     = gParams.outHeight   ;
  createParams.scaleRatioQ12                 = gParams.scaleRatioQ12 ;     
  createParams.scalingMethod                 = gParams.scalingMethod ;
  createParams.fracQFmt                      = gParams.fracQFmt;
  createParams.outStartX                     = 0;
  createParams.outStartY                     = 0;
 

  numMemRec = YUV_SCALAR_TI_VISION_FXNS.ialg.algNumAlloc();
  memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

  status = YUV_SCALAR_TI_VISION_FXNS.ialg.algAlloc(
    (IALG_Params *)(&createParams), NULL, memRec);

  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
    goto EXIT_LOOP;
  }

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
  status = YUV_SCALAR_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
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



  inLuma            = (uint8_t *)malloc(inLumaSize);
  inChroma          = (uint8_t *)malloc(inChromaSize);
  refLuma           = (uint8_t *)malloc(outLumaSize);
  refChroma         = (uint8_t *)malloc(outChromaSize);
  eveLuma           = (uint8_t *)malloc(eveLumaSize);
  eveChroma         = (uint8_t *)malloc(eveChromaSize);

  if((inLuma == NULL) || (inChroma == NULL) || (refLuma == NULL) || (refChroma == NULL) || (eveLuma == NULL) || (eveChroma == NULL))
  {
    PRINT_ERRORE_MSG();
    return -1;
  }

  inBufs.bufDesc  = inBufDescList;
  outBufs.bufDesc = outBufDescList;

  inBufs.numBufs   = 1;
  outBufs.numBufs  = 1;

  inBufDescList[0]     = &inBufDesc;
  outBufDescList[0]    = &outBufDesc;



  inBufDesc.numPlanes                          = 2;
  inBufDesc.bufPlanes[0].frameROI.topLeft.x    = 0;
  inBufDesc.bufPlanes[0].frameROI.topLeft.y    = 0;

  inBufDesc.bufPlanes[0].width                 = gParams.imWidth;
  inBufDesc.bufPlanes[0].height                = gParams.imHeight;
  inBufDesc.bufPlanes[0].frameROI.width        = gParams.imWidth;
  inBufDesc.bufPlanes[0].frameROI.height       = gParams.imHeight;

  inBufDesc.bufPlanes[0].buf = (uint8_t * )inLuma ;

  inBufDesc.bufPlanes[1].frameROI.topLeft.x    = 0;
  inBufDesc.bufPlanes[1].frameROI.topLeft.y    = 0;

  inBufDesc.bufPlanes[1].width                 = gParams.imWidth ;
  inBufDesc.bufPlanes[1].height                = gParams.imHeight/2;
  inBufDesc.bufPlanes[1].frameROI.width        = gParams.imWidth;
  inBufDesc.bufPlanes[1].frameROI.height       = gParams.imHeight/2;

  inBufDesc.bufPlanes[1].buf = (uint8_t * )inChroma ;


  outBufDesc.numPlanes                          = 2;
  outBufDesc.bufPlanes[0].frameROI.topLeft.x    = 0;
  outBufDesc.bufPlanes[0].frameROI.topLeft.y    = 0;

  outBufDesc.bufPlanes[0].width                 = eveOutWidth ;
  outBufDesc.bufPlanes[0].height                = eveOutHeight;
  outBufDesc.bufPlanes[0].frameROI.width        = gParams.outWidth ;
  outBufDesc.bufPlanes[0].frameROI.height       = gParams.outHeight;

  outBufDesc.bufPlanes[0].buf = (uint8_t * )eveLuma ;

  outBufDesc.bufPlanes[1].frameROI.topLeft.x    = 0;
  outBufDesc.bufPlanes[1].frameROI.topLeft.y    = 0;

  outBufDesc.bufPlanes[1].width                 = eveOutWidth ;
  outBufDesc.bufPlanes[1].height                = eveOutHeight1;
  outBufDesc.bufPlanes[1].frameROI.width        = gParams.outWidth ;
  outBufDesc.bufPlanes[1].frameROI.height       = gParams.outHeight/2;

  outBufDesc.bufPlanes[1].buf = (uint8_t * )eveChroma ;

  outArgs.iVisionOutArgs.size       = sizeof(YUV_SCALAR_TI_outArgs);
  inArgs.iVisionInArgs.size         = sizeof(YUV_SCALAR_TI_InArgs);
  inArgs.iVisionInArgs.subFrameInfo = 0;



  for(i = gParams.startFrame; i < gParams.numFrames; i++)
  {
    TestApp_ReadInBufs(inLuma, inChroma, i, (char *)gParams.inImage);

    vcop_resize_cn_y_s( inLuma,   refLuma, gParams.imWidth, gParams.imHeight, gParams.imWidth, gParams.outWidth, gParams.outHeight, gParams.outWidth, gParams.scaleRatioQ12, Q_FORMATE_SCALE_RATIO, Q_FORMATE_FRAC_WEIGHT);
    vcop_resize_cn_uv_s(inChroma, refChroma, gParams.imWidth, gParams.imHeight, gParams.imWidth, gParams.outWidth, gParams.outHeight, gParams.outWidth, gParams.scaleRatioQ12, Q_FORMATE_SCALE_RATIO, Q_FORMATE_FRAC_WEIGHT);
    
    profiler_start();
    status = handle->ivision->algProcess((IVISION_Handle)handle,
      &inBufs,&outBufs,(IVISION_InArgs *)&inArgs,(IVISION_OutArgs *)&outArgs);
    profiler_end_print(1);

    failed = 0;

    for(y = 0; y < gParams.outHeight; y++)
    {
      for(x = 0; x < gParams.outWidth; x++)
      {
        if(eveLuma[y*eveOutWidth+x] != refLuma[y*gParams.outWidth+x])
        {

          failed |= 1;
        }
      }
    } 
    if(failed != 0)
    {
      printf("EVE Luma re-size falied \n");
    }
    else
    {
      printf("EVE Luma re-size Passed \n");
    }

    for(y = 0; y < gParams.outHeight/2; y++)
    {
      for(x = 0; x < gParams.outWidth; x++)
      {
        if(eveChroma[y*eveOutWidth+x] != refChroma[y*gParams.outWidth+x])
        {

          failed |= 2;
        }
      }
    }    
    if((failed&2) != 0)
    {
      printf("EVE Chroma re-size falied \n");
    }
    else
    {
      printf("EVE Chroma re-size Passed \n");
    }


    TestApp_WrtiteOutBufs(refLuma,refChroma,(char *)gParams.outImage);
    if(failed)
    {
      break;
    }
  }

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


  /* Get the stack usage */
#if !(VCOP_HOST_EMULATION)
  profiler_getStackDepth();
#endif
EXIT_LOOP:
  free(inLuma            );
  free(inChroma          );
  free(refLuma           );
  free(refChroma         );
  free(eveLuma           );
  free(eveChroma         );

  return result;
}

int main(int argc, char *argv[])
{
  FILE * fp;
  char * LinePtr;
  int status;
  int lineNum = -1;
  yuv_scalar_config * params;
  int config_cmd;
  char configFileName[MAX_FILE_NAME_SIZE];

  params = (yuv_scalar_config *)(&gParams);
  report_printAppletInfo((int8_t *)"YUV_SCALAR_TI_VISION");

  fp = fopen(CONFIG_LIST_FILE_NAME, "r");
  if(fp== NULL)
  {
    printf("Could not open config list file : %s  \n",CONFIG_LIST_FILE_NAME);
    return(0);
  }

  while(1)
  {
    memset(params->configLine, 0, MAX_CONFIG_LINE_SIZE);
    status = (int)fgets((char *)params->configLine,MAX_CONFIG_LINE_SIZE,fp);
    LinePtr = (char *)params->configLine;
    if ((status == EOF) || (status == 0))
      break;
    lineNum++;
    sscanf(LinePtr, "%d",&config_cmd);
    sscanf(LinePtr, "%s",params->configParam);
    if(config_cmd == 0)
    {
      printf("End of config list found !\n");
      break;
    }
    else if(config_cmd == 2)
    {
      continue;
    }
    else if(config_cmd == 1)
    {
      LinePtr = moveToNextElement((char *)params->configParam,LinePtr);
      status  = sscanf(LinePtr, "%s",configFileName);
      printf("Processing config file %s !\n", configFileName);
      status = readparamfile(configFileName, &gsTokenMap_yuv_scalar[0]) ;
      if(status == -1)
      {
        printf("Parser Failed");
        return -1 ;
      }
      profiler_testCaseInfo((int8_t *)params->testCaseName,(int8_t *)params->testCaseDesc,params->performanceTestcase);
      printparams(&gsTokenMap_yuv_scalar[0],(int32_t)MAX_ITEMS_TO_PARSE,(uint32_t)(&gParams),sizeof(yuv_scalar_config)) ;

      /* Validate the applet */
      status = test_yuv_scalar();

    }
    else
    {
      printf(" Unsupported config list command parameter at line num : %4d !\n", lineNum);
    }
  }

  fclose(fp);
  return (0);
}
