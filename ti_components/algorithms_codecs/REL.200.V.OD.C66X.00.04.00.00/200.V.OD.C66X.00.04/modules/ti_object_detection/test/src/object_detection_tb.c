/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/** @file object_detection_tb.c
*
*  @brief  This is a test bench file for object detection module.
*          This test interface is common for PD and TSR.
*
*  @date   July 2014
*
*/

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "xdais_types.h"
#include "object_detection_config.h"
#include "iobjdet_ti.h"

#include "ti_mem_manager.h"
#include "ti_file_io.h"

#define DISABLE_FILE_IO 0

#define DISPLAY_HEADER 0

#if (!HOST_EMULATION)
#include "edma3_lld_helper.h"
#endif

#if (HOST_EMULATION)
#define DISABLE_FILE_IO 0
#endif

#if (!HOST_EMULATION)

void _TSC_enable();
long long _TSC_read();

#define L1D_SRAM_ADDR (0x00F00000)

#define L2CFG()  (*(volatile uint32_t *)0x01840000)
#define L1PCFG() (*(volatile uint32_t *)0x01840020)
#define L1DCFG() (*(volatile uint32_t *)0x01840040)
#define MAR148() (*(volatile uint32_t *)0x01848250)
#define MAR149() (*(volatile uint32_t *)0x01848254)
void SetMAR()
{

  uint32_t i ;

  uint32_t* MAR = (uint32_t*)0x01848200 ; //MAR_128

  for(i = 128 ;i <= 133 ; i++) // 0x80000000 - 0x85FFFFFF only cached! prev value 160
  {
    *MAR = 0x1;
     MAR++ ;
  }

  return ;
}

void InitCache()
{
  /*-------------------------------------------------------------------------*/
  /* 4-> full 256 KB as cache, 3-> 128KB, 2 -> 64KB, 1-> 32KB                */
  /* IMPORTANT :: Currently 0 KB of L2 is assumed to be SRAM, hence in final */
  /* application any amount L2 can be configured as SRAM, but DMVAL will not */
  /* use that. Only thing here important is that if in application full L2 is*/
  /* configured as cache then standalone and final application performance   */
  /* numbers will match. otherwise no functionality issue.                    */
  /*-------------------------------------------------------------------------*/
  L2CFG()  = 2;

  /*-------------------------------------------------------------------------*/
  /* Full L1P is configured as 32KB of cache                                 */
  /* Nothing in L1P is assumed as SRAM, so no dependency from final applicati*/
  /* -on configuration. Only thing if full L1P is configured as cache then   */
  /* standalone and application performance numbers will match.              */
  /*-------------------------------------------------------------------------*/
  L1PCFG() = 4;

 /*--------------------------------------------------------------------------*/
  /* 1 -> 4 KB, 2-> 8KB, 3 ->16 KB, 4 -> 32KB as cache                       */
  /* Currently 4KB as cache has been allocated for L1D, Rest 28 KB is configu*/
  /* red as SRAM. Any change in cache configuration should be done in conjuca*/
  /* of linker command file modification in test applciation                 */
  /* IMPORTANT :: Here 28 KB of L1 D is assumed as SRAM hence there is depend*/
  /* -dency from final applcaition configuration of L1D. If atleast 28 KB of */
  /* L1D is not configured as SRAM in final application then that will be a  */
  /* functional issue.                                                       */
  /*-------------------------------------------------------------------------*/
  L1DCFG() = 2;

  SetMAR() ;
}

#endif //!HOST_EMULATION

const char  *tsrClassString[TI_OD_NUM_TSR_TEMPLATES + 1] = {
    /*0*/ "speed limit 20",
    /*1*/ "speed limit 30",
    /*2*/ "speed limit 50",
    /*3*/ "speed limit 60",
    /*4*/ "speed limit 70",
    /*5*/ "speed limit 80",
    /*6*/ "restriction ends 80",
    /*7*/ "speed limit 100",
    /*8*/ "speed limit 120",
    /*9*/ "no overtaking",
    /*10*/ "no overtaking (trucks)",
    /*11*/ "priority at next intersection",
    /*12*/ "priority road",
    /*13*/ "give way",
    /*14*/ "stop",
    /*15*/ "no vehicles",
    /*16*/ "no trucks",
    /*17*/ "no entry",
    /*18*/ "danger ahead",
    /*19*/ "bend to left",
    /*20*/ "bend to right",
    /*21*/ "double bend (first to left)",
    /*22*/ "uneven road",
    /*23*/ "slippery road",
    /*24*/ "road narrows",
    /*25*/ "construction",
    /*26*/ "traffic signal",
    /*27*/ "pedestrian crossing",
    /*28*/ "school crossing",
    /*29*/ "cycles crossing",
    /*30*/ "snow",
    /*31*/ "animals",
    /*32*/ "restriction ends",
    /*33*/ "go right",
    /*34*/ "go left",
    /*35*/ "go straight",
    /*36*/ "go right or straight",
    /*37*/ "go left or straight",
    /*38*/ "keep right",
    /*39*/ "keep left",
    /*40*/ "roundabout",
    /*41*/ "restriction ends (overtaking)",
    /*42*/ "restriction ends (overtaking (trucks))",
    /*43*/ "NOT A TRAFFIC SIGN"
};

#define PRINT_ERROR_MSG()  printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#define MAX_FEATURE_PLANE_SIZE (8 * 1024 * 1024)

#define DMEM_SIZE (208 * 1024)

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
/* This will be used for allocation of memory in DMEM*/
uint8_t DMEM_SCRATCH[DMEM_SIZE];

TIMemObject memObj_DMEM;
int32_t TestApp_AllocMemRecords(IALG_MemRec * memRec,int32_t numMemRec)
{
  int32_t i;
  TIMemHandle memHdl_DMEM = &memObj_DMEM;
  for (i = 0; i < numMemRec; i++)
  {
    if(memRec[i].space == IALG_DARAM1) {
      memRec[i].base = TI_GetMemoryChunk(memHdl_DMEM, memRec[i].size, memRec[i].alignment);
    }
    else if(memRec[i].space == IALG_DARAM0) {
       //L1D SRAM space, curretly alg requires 24kb SRAM and 8kb cache.
#if (!HOST_EMULATION)
      memRec[i].base = (void *)L1D_SRAM_ADDR;
#else
      memRec[i].base = (void *)malloc( memRec[i].size);
#endif
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
  for (i = 0; i < numMemRec; i++)
  {
    if(memRec[i].base == NULL)
    {
      return IALG_EFAIL;
    }
    if(memRec[i].space == IALG_EXTERNAL) {
      free(memRec[i].base);
    }
  }
  return IALG_EOK;
}

typedef struct IM_Fxns
{
  IVISION_Fxns * ivision;

} IM_Fxns;



#pragma DATA_SECTION(featData,".featDat");
char featData[MAX_FEATURE_PLANE_SIZE];

int32_t TestApp_AllocIOBuffers(IVISION_InBufs * inBufs,IVISION_OutBufs * outBufs)
{
  int32_t size;

  inBufs->bufDesc[0]->numPlanes                          = 1;
  inBufs->bufDesc[0]->bufPlanes[0].frameROI.topLeft.x    = 0;
  inBufs->bufDesc[0]->bufPlanes[0].frameROI.topLeft.y    = 0;
  inBufs->bufDesc[0]->bufPlanes[0].width                 = MAX_FEATURE_PLANE_SIZE;
  inBufs->bufDesc[0]->bufPlanes[0].height                = 1;
  inBufs->bufDesc[0]->bufPlanes[0].frameROI.width        = inBufs->bufDesc[0]->bufPlanes[0].width;
  inBufs->bufDesc[0]->bufPlanes[0].frameROI.height       = inBufs->bufDesc[0]->bufPlanes[0].frameROI.height;
  inBufs->bufDesc[0]->bufPlanes[0].planeType             = 0;

  size = sizeof(TI_OBJECT_FEATURES_outputMetaData) + (inBufs->bufDesc[0]->bufPlanes[0].width * inBufs->bufDesc[0]->bufPlanes[0].height);
  inBufs->bufDesc[0]->bufPlanes[0].buf = &featData[0];//malloc(size);

  if((inBufs->bufDesc[0]->bufPlanes[0].buf == NULL))
  {
    PRINT_ERROR_MSG();
  }

  outBufs->bufDesc[0]->numPlanes                          = 1;
  outBufs->bufDesc[0]->bufPlanes[0].frameROI.topLeft.x    = 0;
  outBufs->bufDesc[0]->bufPlanes[0].frameROI.topLeft.y    = 0;
  outBufs->bufDesc[0]->bufPlanes[0].width                 = TI_OD_OUT_BUFDESC_LIST_SIZE + 16;
  outBufs->bufDesc[0]->bufPlanes[0].height                = 1;
  outBufs->bufDesc[0]->bufPlanes[0].frameROI.width        = TI_OD_OUT_BUFDESC_LIST_SIZE + 16;
  outBufs->bufDesc[0]->bufPlanes[0].frameROI.height       = 1;
  outBufs->bufDesc[0]->bufPlanes[0].planeType             = 0;


  outBufs->bufDesc[0]->bufPlanes[0].buf = malloc(outBufs->bufDesc[0]->bufPlanes[0].width * outBufs->bufDesc[0]->bufPlanes[0].height);
  if((outBufs->bufDesc[0]->bufPlanes[0].buf == NULL))
  {
    PRINT_ERROR_MSG();
  }
  memset(outBufs->bufDesc[0]->bufPlanes[0].buf ,0,outBufs->bufDesc[0]->bufPlanes[0].width * outBufs->bufDesc[0]->bufPlanes[0].height);

  return IALG_EOK;
}

int32_t TestApp_ReadInBufs(IVISION_InBufs * inBufs,int32_t currFrameNum, char * fileName)
{
  TI_OBJECT_FEATURES_outputMetaData *metaData;
  int32_t metaDataSize;
  int32_t size;

#ifdef USE_HOST_FILE_IO
  HOSTFILE * fp;
#else
  FILE * fp;
#endif

  fp = FOPEN(fileName, "rb");

  metaDataSize = sizeof(TI_OBJECT_FEATURES_outputMetaData);
  FREAD(inBufs->bufDesc[0]->bufPlanes[0].buf, 1, metaDataSize, fp);
  metaData = (TI_OBJECT_FEATURES_outputMetaData *)inBufs->bufDesc[0]->bufPlanes[0].buf;
  size = metaData->featBufSize;

  FSEEK(fp, (currFrameNum * size), SEEK_SET);

#if (!DISABLE_FILE_IO)

#ifdef USE_HOST_FILE_IO
{
    int32_t nChunks, reminder, ctr;
    int32_t ONE_MEGA_BYTE = 0x100000;

    nChunks  = size / ONE_MEGA_BYTE;
    reminder = size % ONE_MEGA_BYTE;

    for(ctr = 0; ctr < nChunks; ctr++)
       FREAD((void *)((uint32_t)inBufs->bufDesc[0]->bufPlanes[0].buf + (ctr * ONE_MEGA_BYTE)),1,ONE_MEGA_BYTE,fp);

    if(reminder)
       FREAD((void *)((uint32_t)inBufs->bufDesc[0]->bufPlanes[0].buf + (ctr * ONE_MEGA_BYTE)),1,reminder,fp);
}
#else

  FREAD((void *)((uint32_t)inBufs->bufDesc[0]->bufPlanes[0].buf),1,size,fp);

#endif
  metaData = (TI_OBJECT_FEATURES_outputMetaData *)inBufs->bufDesc[0]->bufPlanes[0].buf;
#if DISPLAY_HEADER
  printf("size        : %d \n", metaData->size);
  printf("featBufSize : %d \n", metaData->featBufSize);
  printf("numScales   : %d \n", metaData->numScales);
  printf("numPlanes   : %d \n", metaData->numPlanes);
  printf("featFormat  : %d \n", metaData->featFormat);
#endif

#endif

  FCLOSE(fp);

  return (0);
}

int32_t objectDetectionTest(sObjectDetection_Config * testcaseParams)
{
  int32_t numMemRec;
  int32_t j,k;
  IALG_MemRec *memRec;
  int32_t status;
  uint32_t testcase;
  uint8_t  levelCnt=0;
  FILE *fpOut ;
  long long  t0, t1;
#if (!HOST_EMULATION)
  _TSC_enable();
#endif
  /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
  IM_Fxns *     handle;

  /*-----------------------------------------------------------------
  Algorithm parameters memory in stack
  -----------------------------------------------------------------*/
  TI_OD_CreateParams   createParams;

  TI_OD_InArgs      inArgs;
  IVISION_InBufs    inBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inBufDesc;
  IVISION_BufDesc   *inBufDescList[TI_OD_IN_BUFDESC_TOTAL];

  TI_OD_OutArgs     outArgs;
  IVISION_OutBufs   outBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   outBufDesc;
  IVISION_BufDesc   *outBufDescList[TI_OD_OUT_BUFDESC_TOTAL];

  outArgs.iVisionOutArgs.size = sizeof(TI_OD_OutArgs);
  inArgs.iVisionInArgs.size   = sizeof(TI_OD_InArgs);
  /*--------------------------------------------------------------------------*/
  /*Create memory handle for ARP32 DMEM.                                      */
  /*--------------------------------------------------------------------------*/
  uint8_t *pDmem;
  TIMemHandle memHdl_DMEM;
  TI_OD_objectDescriptor *objDesc;
  TI_OD_output *outputPds;
  uint32_t frameIdx;

#if (!HOST_EMULATION)
  EDMA3_RM_Result edma3Error;
  EDMA3_RM_Handle edma3RmLldHandle;
  /* Create a resource manager Handle */
  edma3RmLldHandle = EDMA3_LLD_HELPER_init(0, NULL, NULL, &edma3Error);
#endif

  pDmem = (uint8_t *)&DMEM_SCRATCH;
  memHdl_DMEM = &memObj_DMEM;
  TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);

  objectDetection_numTestCases  = 1;

  for (testcase = 0 ; testcase < objectDetection_numTestCases; testcase++)
  {

    /*-----------------------------------------------------------------
    Set buffer descriptor pointers array base
    -----------------------------------------------------------------*/
    inBufs.bufDesc  = inBufDescList;
    outBufs.bufDesc = outBufDescList;

    inBufs.numBufs   = TI_OD_IN_BUFDESC_TOTAL;
    outBufs.numBufs  = TI_OD_OUT_BUFDESC_TOTAL;

    inBufDescList[TI_OD_IN_BUFDESC_FEATURE_PLANES] = &inBufDesc;
    outBufDescList[TI_OD_OUT_BUFDESC_LIST]         = &outBufDesc;

    createParams.maxImageWidth  = testcaseParams[testcase].maxImageWidth;
    createParams.maxImageHeight = testcaseParams[testcase].maxImageHeight;
    createParams.maxScales      = testcaseParams[testcase].maxScales;
    /*-----------------------------------------------------------------
    Set algorithm parameters
    -----------------------------------------------------------------*/
#if (!HOST_EMULATION)
    createParams.edma3RmLldHandle   = edma3RmLldHandle;
#else
    createParams.edma3RmLldHandle   = NULL;
#endif

    createParams.edma3RmLldHandle   = NULL; //TBD. To be removed when issue is resolved in Vision SDK.

    /*-----------------------------------------------------------------
    Query alogorithm memory requirement using standard IALG interface
    -----------------------------------------------------------------*/
    numMemRec = TI_OD_VISION_FXNS.ialg.algNumAlloc();
    memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

    status = TI_OD_VISION_FXNS.ialg.algAlloc(
      (IALG_Params *)(&createParams), NULL, memRec);

    if(status != IALG_EOK)
    {
      PRINT_ERROR_MSG();
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
      PRINT_ERROR_MSG();
      goto EXIT_LOOP;
    }

    /*-----------------------------------------------------------------
    Intialize the algorithm instance with the alocated memory
    and user create parameters
    -----------------------------------------------------------------*/
    status = TI_OD_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
      memRec,NULL,(IALG_Params *)(&createParams));


    handle = (IM_Fxns *) memRec[0].base;

    if(status != IALG_EOK)
    {
      PRINT_ERROR_MSG();
      goto EXIT_LOOP;
    }

    inArgs.iVisionInArgs.subFrameInfo       = 0;
    inArgs.iVisionInArgs.size               = sizeof(TI_OD_InArgs);

    inBufDesc.numPlanes                     = 1;
    outBufDesc.numPlanes                    = 1;

    TestApp_AllocIOBuffers(&inBufs,&outBufs);

    fpOut = fopen((char *)testcaseParams[testcase].outFileName,"w");
    if(fpOut == NULL)
    {
      printf("Unable to open output file\n");
      goto EXIT_LOOP;
    }

    for(frameIdx = 0; frameIdx < testcaseParams[testcase].maxFrames;frameIdx++)
    {

      printf("Frame %d : ",frameIdx);

      inArgs.detectionMode                    = testcaseParams[testcase].detectionMode;
      inArgs.roiPreset                        = testcaseParams[testcase].roiPreset;
      inArgs.refreshInterval                  = testcaseParams[testcase].refreshInterval;

      inArgs.pdConfig.enablePD                = testcaseParams[testcase].pdConfig.enablePD;
      inArgs.pdConfig.classifierTypePD        = testcaseParams[testcase].pdConfig.classifierTypePD;
      inArgs.pdConfig.trackingMethodPD        = testcaseParams[testcase].pdConfig.trackingMethodPD;
      inArgs.pdConfig.softCascadeThPD         = testcaseParams[testcase].pdConfig.softCascadeThPD;
      inArgs.pdConfig.strongCascadeThPD       = testcaseParams[testcase].pdConfig.strongCascadeThPD;

      inArgs.tsrConfig.enableTSR              = testcaseParams[testcase].tsrConfig.enableTSR;
      inArgs.tsrConfig.classifierTypeTSR      = testcaseParams[testcase].tsrConfig.classifierTypeTSR;
      inArgs.tsrConfig.trackingMethodTSR      = testcaseParams[testcase].tsrConfig.trackingMethodTSR;
      inArgs.tsrConfig.recognitionMethodTSR   = testcaseParams[testcase].tsrConfig.recognitionMethodTSR;
      inArgs.tsrConfig.softCascadeThTSR       = testcaseParams[testcase].tsrConfig.softCascadeThTSR;
      inArgs.tsrConfig.strongCascadeThTSR     = testcaseParams[testcase].tsrConfig.strongCascadeThTSR;

      //Set reserved params to 0 for normal operation
      inArgs.reserved0  = 0;
      inArgs.reserved1  = 0;
      inArgs.reserved2  = 0;
      inArgs.reserved3  = 0;

      TestApp_ReadInBufs(&inBufs,frameIdx, (char *)testcaseParams[testcase].inFileName);

#if (!HOST_EMULATION)
      t0 = _TSC_read();
#endif

      status = handle->ivision->algProcess((IVISION_Handle)handle,
                                            &inBufs,
                                            &outBufs,
                                           (IVISION_InArgs  *)&inArgs,
                                           (IVISION_OutArgs *)&outArgs);
#if (!HOST_EMULATION)
      t1 = _TSC_read();
      printf("Cycles per frame: %8lld ", t1-t0);
#endif

      if(inArgs.pdConfig.enablePD)
      {
          /*
          printf(" PD: Adaboost Cycles = %d, Trees processed =  %d \n"
                        ,outArgs.pdStats.numCyclesPD,outArgs.pdStats.numTreesPD);
          */
      }

      if(inArgs.tsrConfig.enableTSR)
      {
          /*
          printf(" TSR: Adaboost Cycles = %d, Trees processed =  %d \n"
                        ,outArgs.tsrStats.numCyclesTSR,outArgs.tsrStats.numTreesTSR);
          */
      }
      printf("\n");

      if(status != IALG_EOK)
      {
        PRINT_ERROR_MSG();
        goto EXIT_LOOP;
      }

      status = TI_OD_Report_Error(outArgs.errorCode);

      if(status != IALG_EOK)
      {
        PRINT_ERROR_MSG();
        goto EXIT_LOOP;
      }

      outputPds  = (TI_OD_output *)outBufs.bufDesc[0]->bufPlanes[0].buf;
      objDesc    = &outputPds->objDesc[0];

      fprintf(fpOut,"Frame %d detections \n", frameIdx);
      for(j = 0; j < outputPds->numObjects; j++)
      {
        if(objDesc->objType == TI_OD_PEDESTRIAN)
            fprintf(fpOut,"PD at %4d,%4d,%4d,%4d with ",objDesc->xPos, objDesc->yPos, objDesc->objWidth, objDesc->objHeight);

        if(objDesc->objType == TI_OD_TRAFFIC_SIGN)
        {
            fprintf(fpOut,"TSR at %4d,%4d,%4d,%4d with ",objDesc->xPos, objDesc->yPos, objDesc->objWidth, objDesc->objHeight);
            fprintf(fpOut, "%s ",(int8_t*)(&(tsrClassString[objDesc->objTag][0])));
            //printf("(ID %3d) - %s \n", objDesc->objTag, (int8_t*)(&(tsrClassString[objDesc->objTag][0])));
        }

        for(k = 0; k < objDesc->numMsg; k++)
        {
          fprintf(fpOut,"%s ",(int8_t*)(&(objDesc->objMsg[k][0])));
        }


        fprintf(fpOut,"\n");
        objDesc++;
      }

    }
    fprintf(fpOut,"\n");

EXIT_LOOP:
    if(fpOut)
    {
        fflush(fpOut);
        fclose(fpOut);
    }

    status = handle->ivision->ialg.algFree((IALG_Handle)(handle), memRec);
    if(status != IALG_EOK)
    {
      PRINT_ERROR_MSG();
    }

#if (!HOST_EMULATION)
  /* Delete resouce manager Handle */
  EDMA3_LLD_HELPER_deinit(0, edma3RmLldHandle);
#endif

    /* Here Free memory for all the mem records */
    status = TestApp_FreeMemRecords(memRec,numMemRec);
    if(status != IALG_EOK)
    {
      PRINT_ERROR_MSG();
    }

    if ( memRec != NULL )
    {
      free(memRec);
    }

    for ( levelCnt = 0 ; levelCnt < inBufDesc.numPlanes ; levelCnt++)
    {
      if ( inBufDesc.bufPlanes[levelCnt].buf != NULL )
      {
        //free(inBufDesc.bufPlanes[levelCnt].buf);
      }
    }

    for ( levelCnt = 0 ; levelCnt < outBufDesc.numPlanes ; levelCnt++)
    {
      if ( outBufDesc.bufPlanes[levelCnt].buf != NULL )
      {
        free(outBufDesc.bufPlanes[levelCnt].buf);
      }
    }

  }
  return status;
}

int32_t main(int32_t argc, char *argv[])
{
  int32_t status = 0;
  char configFile[FILE_NAME_SIZE]={0};

#if (!HOST_EMULATION)
  InitCache();
#endif

#if (!HOST_EMULATION)
  _TSC_enable();
#endif

  if (argc > 1)
  {
    strcpy(configFile, argv[1]) ;
  }
  else
  {
    strcpy(configFile,"../testvecs/config/object_detection.cfg");
  }

  status = readparamfile(configFile, &gsTokenMap_objectDetection[0]) ;
  if(status == -1)
  {
    printf("Parser Failed");
    return -1 ;
  }

  /* Validate the applet */
  status = objectDetectionTest(gConfig_objectDetection);

  return status;
}



