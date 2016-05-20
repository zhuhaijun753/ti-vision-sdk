/*==========================================================================*/
/*      Copyright (C) 2009-2015 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/** @file ld_tb.c
*
*  @brief  This file contains test code for lane detection algorithm
*
*
*  @date   June 2014
*
*  Description
*    This file contains test code to validate the frame level algorithm TI LD
*    
*/

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "xdais_types.h"

#include "ld_config.h"
#include "ild_ti.h"
#include "ti_mem_manager.h"
#if (!HOST_EMULATION)
#include "edma3_lld_helper.h"
#endif

#define ENABLE_TRACES 0
#define RANDOM_INPUT  0

#define DISABLE_FILE_IO 0

#if (HOST_EMULATION)
#define DISABLE_FILE_IO 0
#define ENABLE_TRACES 1
#endif


#if (!HOST_EMULATION)
void _TSC_enable();
long long _TSC_read();

#define L2CFG()  (*(volatile uint32_t *)0x01840000)
#define L1PCFG() (*(volatile uint32_t *)0x01840020)
#define L1DCFG() (*(volatile uint32_t *)0x01840040)

static void SetMAR()
{

  uint32_t i ;

  uint32_t* MAR = (uint32_t*)0x01848200 ; //MAR_128

  /* DDR from 0x80000000 to 9F000000 made cacheable */
  /* From 9F000000 to A0000000 is non-cacheable region. */
  /*  This non-cacheable region is used to hold input and output buffers */
  for(i = 128 ;i <= 158 ; i++)
  {
    *MAR = 0x1;
     MAR++ ;
  }
  return ;
}

static void CacheWbInv()
{
  uint32_t* L1DWBINV = (uint32_t *)0x01845044;
  uint32_t* L2WBINV = (uint32_t *)0x01845004;
  
  /* Write back invalidate cache */
  *L1DWBINV = 1;
  *L2WBINV = 1; 
}

static void InitCache()
{
  /*-------------------------------------------------------------------------*/
  /* 4-> full 256 KB as cache, 3-> 128KB, 2 -> 64KB, 1-> 32KB                */
  /* IMPORTANT :: Currently 0 KB of L2 is assumed to be SRAM, hence in final */
  /* application any amount L2 can be configured as SRAM, but DMVAL will not */
  /* use that. Only thing here important is that if in application full L2 is*/
  /* configured as cache then standalone and final application performance   */
  /* numbers will match. otherwise no functionality issue.                    */
  /*-------------------------------------------------------------------------*/
  L2CFG()  = 4;

  /*-------------------------------------------------------------------------*/
  /* Full L1P is configured as 32KB of cache                                 */
  /* Nothing in L1P is assumed as SRAM, so no dependency from final applicati*/
  /* -on configuration. Only thing if full L1P is configured as cache then   */
  /* standalone and application performance numbers will match.              */
  /*-------------------------------------------------------------------------*/
  L1PCFG() = 4;

 /*-------------------------------------------------------------------------*/
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

#endif

#define ALIGN_T0_32(x) (((x+31)/32)*32)


#define PRINT_ERRORE_MSG()  printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#define DMEM_SIZE (23*1024)

#define L2SRAMMEM_SIZE (128*1024)

#define DDRNONCACHE_SIZE (16384*1024)

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
/* This will be used for allocation of memory in DMEM*/
uint8_t DMEM_SCRATCH[DMEM_SIZE];
TIMemObject memObj_DMEM;


#pragma DATA_SECTION (L2MEM_SCRATCH, ".l2memSect");
uint8_t L2MEM_SCRATCH[L2SRAMMEM_SIZE];
TIMemObject memObj_L2MEM;

#pragma DATA_SECTION (DDRMEM_NONCACHE, ".ddrnoncacheSect");
uint8_t DDRMEM_NONCACHE[DDRNONCACHE_SIZE];
TIMemObject memObj_DDRMEMNC;

int32_t TestApp_AllocMemRecords(IALG_MemRec * memRec,int32_t numMemRec)
{
  int32_t i;
  TIMemHandle memHdl_DMEM = &memObj_DMEM;
  TIMemHandle memHdl_L2MEM = &memObj_L2MEM;

  for (i = 0; i < numMemRec; i++)
  {
    if(memRec[i].space == IALG_DARAM0) {
      memRec[i].base = TI_GetMemoryChunk(memHdl_DMEM, memRec[i].size, memRec[i].alignment);
    }
    else if(memRec[i].space == IALG_DARAM1) {
      memRec[i].base = TI_GetMemoryChunk(memHdl_L2MEM, memRec[i].size, memRec[i].alignment);
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
    if(memRec[i].space == IALG_EXTERNAL){
      free(memRec[i].base);
    }
  }
  return IALG_EOK;
}

typedef struct IM_Fxns
{
  IVISION_Fxns * ivision;

} IM_Fxns;

int32_t TestApp_AllocIOBuffers(IVISION_InBufs * inBufs,IVISION_OutBufs * outBufs, sLD_Config * params)
{
  TIMemHandle memHdl_EXTMEM = &memObj_DDRMEMNC; 
  uint32_t size;
  
  inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->numPlanes                       = 1;
  inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.topLeft.x = params[0].startX;
  inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.topLeft.y = params[0].startY;
  inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].width              = params[0].actualImgWidth;
  inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].height             = params[0].actualImgHeight;
  inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.width     = params[0].roiWidth;
  inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.height    = params[0].roiHeight;
  inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].planeType          = 0; // Luma Y
  size = (inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].width)*(inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].height);
  /* Allocate the buffer in DDR which is non-cacheable */
  inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].buf = TI_GetMemoryChunk(memHdl_EXTMEM, size, 4);
  if((inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].buf == NULL))
  {
    PRINT_ERRORE_MSG();
  }

  outBufs->bufDesc[LD_BUFDESC_OUT_XY_LIST]->numPlanes                        = 1;
  outBufs->bufDesc[LD_BUFDESC_OUT_XY_LIST]->bufPlanes[0].frameROI.topLeft.x  = 0;
  outBufs->bufDesc[LD_BUFDESC_OUT_XY_LIST]->bufPlanes[0].frameROI.topLeft.y  = 0;
  outBufs->bufDesc[LD_BUFDESC_OUT_XY_LIST]->bufPlanes[0].width               = LD_TI_MAXLANEPOINTS * sizeof(uint32_t);
  outBufs->bufDesc[LD_BUFDESC_OUT_XY_LIST]->bufPlanes[0].height              = 1;
  outBufs->bufDesc[LD_BUFDESC_OUT_XY_LIST]->bufPlanes[0].frameROI.width      = LD_TI_MAXLANEPOINTS * sizeof(uint32_t);
  outBufs->bufDesc[LD_BUFDESC_OUT_XY_LIST]->bufPlanes[0].frameROI.height     = 1;
  outBufs->bufDesc[LD_BUFDESC_OUT_XY_LIST]->bufPlanes[0].planeType           = 0;
  size = (outBufs->bufDesc[LD_BUFDESC_OUT_XY_LIST]->bufPlanes[0].width)*(outBufs->bufDesc[LD_BUFDESC_OUT_XY_LIST]->bufPlanes[0].height);
  /* Allocate the buffer in DDR which is non-cacheable */
  outBufs->bufDesc[LD_BUFDESC_OUT_XY_LIST]->bufPlanes[0].buf = TI_GetMemoryChunk(memHdl_EXTMEM, size, 4);
  if((outBufs->bufDesc[LD_BUFDESC_OUT_XY_LIST]->bufPlanes[0].buf == NULL))
  {
    PRINT_ERRORE_MSG();
  }
  memset(outBufs->bufDesc[0]->bufPlanes[0].buf ,0,outBufs->bufDesc[0]->bufPlanes[0].width * outBufs->bufDesc[0]->bufPlanes[0].height);

  return IALG_EOK;
}

int32_t TestApp_ReadInBufs(IVISION_InBufs * inBufs,int32_t currFrameNum, char * fileName)
{
  int32_t size = inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].width * inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].height;
#if (!RANDOM_INPUT)
  FILE * fp;
  fp = fopen(fileName, "rb");

  if(fp == NULL)
  {
    goto Exit;
  }

  fseek(fp, currFrameNum*size, SEEK_SET);
#if (!DISABLE_FILE_IO)
  fread(inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].buf,1,size,fp);
#endif
  fclose(fp);
#else

  int32_t i;
  uint8_t * ptr = (uint8_t *)(inBufs->bufDesc[LD_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].buf);
  for(i = 0; i < size; i++)
  {
    ptr[i] = (i & 0xFF);
  }
#endif

  Exit:
    return (0);
}

int32_t TestApp_WriteOutBufs(IVISION_OutBufs * outBufs, uint16_t width, uint16_t height, char * fileName)
{
  FILE * fp;
  static int firtsWrite = 1;
  int32_t size;
  int32_t retVal;
  if(firtsWrite)
  {
    fp = fopen(fileName, "wb");
    fclose(fp);
    firtsWrite = 0;
  }
  fp = fopen(fileName, "ab");
  if(fp == NULL)
  {
    goto Exit;
  }
  size= width * height;

  retVal = fwrite(outBufs->bufDesc[LD_BUFDESC_OUT_XY_LIST]->bufPlanes[0].buf,1,size,fp);

  if(retVal != size)
  {
    printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
  }
  fclose(fp);
  Exit:
    return (0);
}

int32_t ldTest(sLD_Config * testcaseParams)
{
  int32_t numMemRec;
  uint32_t j;
  IALG_MemRec *memRec;
  int32_t status;
  uint32_t testcase;
  FILE *fpOut ;
  char *outFile;
  char *inFile;
  char *name;
  char *file;
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
  LD_TI_CreateParams   createParams;
  LD_TI_InArgs      inArgs;
  IVISION_InBufs    inBufs;
  
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inBufDesc;
  IVISION_BufDesc   *inBufDescList[LD_BUFDESC_IN_TOTAL];

  LD_TI_OutArgs     outArgs;
  IVISION_OutBufs   outBufs;
  
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   outBufDesc;
  IVISION_BufDesc   *outBufDescList[LD_BUFDESC_OUT_TOTAL];

#if ENABLE_TRACES
  IVISION_BufDesc   outImBufDesc;
  IVISION_BufDesc   *outImBufDescList[1];
  IVISION_InBufs    outImBufs;
  uint8_t *laneOutIm;
  uint8_t  levelCnt=0;
#endif

  outArgs.iVisionOutArgs.size = sizeof(LD_TI_OutArgs);
  inArgs.iVisionInArgs.size   = sizeof(LD_TI_InArgs);
  
  /*--------------------------------------------------------------------------*/
  /*Create memory handle for L1DMEM.                                      */
  /*--------------------------------------------------------------------------*/
  uint8_t *pDmem;
  TIMemHandle memHdl_DMEM;

  /*--------------------------------------------------------------------------*/
  /*Create memory handle for L2MEM.                                      */
  /*--------------------------------------------------------------------------*/
  uint8_t *pL2mem;
  TIMemHandle memHdl_L2MEM;

  /*--------------------------------------------------------------------------*/
  /*Create memory handle for DDR NON CACHE MEM                     */
  /*--------------------------------------------------------------------------*/
  uint8_t *pExtmem;
  TIMemHandle memHdl_EXTMEM;

  LD_TI_output *outputLanes;
  uint32_t     *outNumLanePoints;
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

  pL2mem = (uint8_t *)&L2MEM_SCRATCH;
  memHdl_L2MEM = &memObj_L2MEM;
  TI_CreateMemoryHandle(memHdl_L2MEM, pL2mem, L2SRAMMEM_SIZE);

  pExtmem = (uint8_t *)&DDRMEM_NONCACHE;
  memHdl_EXTMEM = &memObj_DDRMEMNC;
  TI_CreateMemoryHandle(memHdl_EXTMEM, pExtmem, DDRNONCACHE_SIZE);

  for ( testcase = 0 ; testcase < ld_numTestCases; testcase++ )
  {
    /*-----------------------------------------------------------------
      Set buffer descriptor pointers array base
      -----------------------------------------------------------------*/
    inBufs.bufDesc  = inBufDescList;
    outBufs.bufDesc = outBufDescList;

    inBufs.numBufs   = LD_BUFDESC_IN_TOTAL;
    outBufs.numBufs  = LD_BUFDESC_OUT_TOTAL;

    inBufDescList[LD_BUFDESC_IN_IMAGEBUFFER] = &inBufDesc;
    outBufDescList[LD_BUFDESC_OUT_XY_LIST]   = &outBufDesc;

#if ENABLE_TRACES
    outImBufs.bufDesc = outImBufDescList;
    outImBufs.numBufs = 1;
    outImBufDescList[0] = &outImBufDesc;
#endif

    /*-----------------------------------------------------------------
      Set algorithm parameters
      -----------------------------------------------------------------*/
    createParams.maxImageWidth      = testcaseParams[testcase].maxImageWidth;
    createParams.maxImageHeight     = testcaseParams[testcase].maxImageHeight;
    createParams.maxRho             = testcaseParams[testcase].maxRho;
    createParams.maxTheta           = LD_TI_MAXNUMTHETA;
#if (!HOST_EMULATION)
    createParams.edma3RmLldHandle   = edma3RmLldHandle;
#else
    createParams.edma3RmLldHandle   = NULL;
#endif

    /*-----------------------------------------------------------------
      Query alogorithm memory requirement using standard IALG interface
      -----------------------------------------------------------------*/
    numMemRec = LD_TI_VISION_FXNS.ialg.algNumAlloc();
    memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

    status = LD_TI_VISION_FXNS.ialg.algAlloc((IALG_Params *)(&createParams), NULL, memRec);

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }
#if ENABLE_TRACES
    printf("Lane Detection algorithm Create Done\n");
#endif
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
      Intialize the algorithm instance with the alocated memory
      and user create parameters
      -----------------------------------------------------------------*/
    status = LD_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
            memRec,NULL,(IALG_Params *)(&createParams));

    handle = (IM_Fxns *) memRec[0].base;

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }
#if ENABLE_TRACES
    printf("Lane detection algorithm Init Done\n");
#endif

    inArgs.iVisionInArgs.subFrameInfo = 0;
    inArgs.iVisionInArgs.size         = sizeof(LD_TI_InArgs);
    inArgs.cannyHighThresh            = testcaseParams[testcase].cannyHiThresh ;
    inArgs.cannyLowThresh             = testcaseParams[testcase].cannyLoThresh ;
    inArgs.houghNmsThresh             = testcaseParams[testcase].houghNmsThresh ;
    inArgs.startThetaLeft             = testcaseParams[testcase].startThetaLeft ;
    inArgs.endThetaLeft               = testcaseParams[testcase].endThetaLeft ;
    inArgs.startThetaRight            = testcaseParams[testcase].startThetaRight ;
    inArgs.endThetaRight              = testcaseParams[testcase].endThetaRight ;
    inArgs.thetaStepSize              = testcaseParams[testcase].thetaStepSize ;
    if(testcaseParams[testcase].trackMethod == 1)
    {
      inArgs.trackingMethod             = LD_TI_TRACK_KF;
    }
    else
    {
      inArgs.trackingMethod             = LD_TI_TRACK_DISABLE;
    }
    inArgs.numHoughMaximasDet         = testcaseParams[testcase].numHoughMaximasDet;
    inArgs.numHoughMaximasTrack       = testcaseParams[testcase].numHoughMaximasTrack;
    if(testcaseParams[testcase].enableWarning == 1)
    {
      inArgs.warningMethod              = LD_TI_WARNING_ENABLE;
    }
    else
    {
      inArgs.warningMethod              = LD_TI_WARNING_DISABLE;
    }
    inArgs.departThetaLeftMin         = testcaseParams[testcase].departThetaLeftMin;
    inArgs.departThetaLeftMax         = testcaseParams[testcase].departThetaLeftMax;
    inArgs.departRhoLeftMin           = testcaseParams[testcase].departRhoLeftMin;
    inArgs.departRhoLeftMax           = testcaseParams[testcase].departRhoLeftMax;
    inArgs.departThetaRightMin        = testcaseParams[testcase].departThetaRightMin;
    inArgs.departThetaRightMax        = testcaseParams[testcase].departThetaRightMax;
    inArgs.departRhoRightMin          = testcaseParams[testcase].departRhoRightMin;
    inArgs.departRhoRightMax          = testcaseParams[testcase].departRhoRightMax;
    inBufDesc.numPlanes               = 1;
    outBufDesc.numPlanes              = 1;

    TestApp_AllocIOBuffers(&inBufs,&outBufs,&testcaseParams[testcase]);

#if ENABLE_TRACES
    outImBufDesc.bufPlanes[0].frameROI.topLeft.x = testcaseParams[testcase].startX;
    outImBufDesc.bufPlanes[0].frameROI.topLeft.y = testcaseParams[testcase].startY;
    outImBufDesc.bufPlanes[0].width              = testcaseParams[testcase].actualImgWidth;
    outImBufDesc.bufPlanes[0].height             = testcaseParams[testcase].actualImgHeight;
    outImBufDesc.bufPlanes[0].frameROI.width     = testcaseParams[testcase].roiWidth;
    outImBufDesc.bufPlanes[0].frameROI.height    = testcaseParams[testcase].roiHeight;
    outImBufDesc.bufPlanes[0].planeType          = 0; // Luma Y

    outImBufDesc.bufPlanes[0].buf = 
      malloc(outImBufDesc.bufPlanes[0].width * outImBufDesc.bufPlanes[0].height);
    if((outImBufDesc.bufPlanes[0].buf == NULL))
    {
      PRINT_ERRORE_MSG();
    }
    laneOutIm = (uint8_t *)outImBufDesc.bufPlanes[0].buf;
#endif
    name = (char *)malloc(256);
    file = (char *)malloc(256);

    for(frameIdx = 0; frameIdx < testcaseParams[testcase].maxFrames;frameIdx++)
    {
      sprintf(name, "%d.csv", frameIdx);
      strcpy(file, (char *)testcaseParams[testcase].outFileName);
      outFile = strcat((char *)file, name);      
      fpOut = fopen((char *)outFile,"w");
      if(fpOut == NULL)
      {
        printf("Unable to open output file\n");
        goto EXIT_LOOP;
      }
#if ENABLE_TRACES
      printf("Processing started for frame %d \n",frameIdx);
#endif
      sprintf(name, "%d.y", frameIdx);
      strcpy(file, (char *)testcaseParams[testcase].inFileName);
      inFile = strcat((char *)file, name);
      TestApp_ReadInBufs(&inBufs,0,inFile);

#if ENABLE_TRACES
      TestApp_ReadInBufs(&outImBufs,0,inFile);
#endif
#if (!HOST_EMULATION)
      /* Write back Invalidate cache */
      CacheWbInv();
      t0 = _TSC_read();
#endif
      status = handle->ivision->algProcess((IVISION_Handle)handle,
        &inBufs,&outBufs,(IVISION_InArgs *)&inArgs,(IVISION_OutArgs *)&outArgs);
#if (!HOST_EMULATION)
      t1 = _TSC_read();
      printf(" Cycles per frame %ld \n", t1-t0);
      /* Write back Invalidate cache */
      CacheWbInv();
#endif
      printf(" Number of Left lane points detected = %d\n", outArgs.numLeftLanePoints);
      printf(" Number of Right lane points detected = %d\n", outArgs.numRightLanePoints);

      if(status != IALG_EOK)
      {
        PRINT_ERRORE_MSG();
        goto EXIT_LOOP;
      }
#if ENABLE_TRACES
      printf("Processing Completed for frame %d \n",frameIdx);
#endif
      outNumLanePoints = ( uint32_t * )outBufs.bufDesc[0]->bufPlanes[0].buf;
      outputLanes = ( LD_TI_output * )(outNumLanePoints);

      for(j = 0; j < (outArgs.numLeftLanePoints + outArgs.numRightLanePoints); j++)
      {
        fprintf(fpOut,"%4d,%4d \n",outputLanes[j].x,outputLanes[j].y);
#if ENABLE_TRACES
        if((outArgs.infoFlag == LD_TI_RIGHT_LANE_CROSS) || (outArgs.infoFlag == LD_TI_LEFT_LANE_CROSS))
        {
          laneOutIm[(outputLanes[j].y * testcaseParams[testcase].actualImgWidth) + outputLanes[j].x] = 255;
          laneOutIm[(outputLanes[j].y * testcaseParams[testcase].actualImgWidth) + outputLanes[j].x - 1] = 255;
          laneOutIm[(outputLanes[j].y * testcaseParams[testcase].actualImgWidth) + outputLanes[j].x - 2] = 255;
          laneOutIm[(outputLanes[j].y * testcaseParams[testcase].actualImgWidth) + outputLanes[j].x + 1] = 255;
          laneOutIm[(outputLanes[j].y * testcaseParams[testcase].actualImgWidth) + outputLanes[j].x + 2] = 255;
        }
        else
        {
          laneOutIm[(outputLanes[j].y * testcaseParams[testcase].actualImgWidth) + outputLanes[j].x] = 0;
          laneOutIm[(outputLanes[j].y * testcaseParams[testcase].actualImgWidth) + outputLanes[j].x - 1] = 0;
          laneOutIm[(outputLanes[j].y * testcaseParams[testcase].actualImgWidth) + outputLanes[j].x - 2] = 0;
          laneOutIm[(outputLanes[j].y * testcaseParams[testcase].actualImgWidth) + outputLanes[j].x + 1] = 0;
          laneOutIm[(outputLanes[j].y * testcaseParams[testcase].actualImgWidth) + outputLanes[j].x + 2] = 0;
        }
#endif
      }
      if(fpOut)
      {
        fclose(fpOut);
      }
#if ENABLE_TRACES
      sprintf(name, "../testvecs/output/ImgOut%d.y", frameIdx);
      TestApp_WriteOutBufs(&outImBufs, testcaseParams[testcase].actualImgWidth, 
                            testcaseParams[testcase].actualImgHeight, name);
#endif 

    }

EXIT_LOOP:
    if(name != NULL)
    {
      free(name);
    }
    if(file != NULL)
    {
      free(file);
    }    
    if(fpOut)
    {
      fclose(fpOut);
    }
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

#if ENABLE_TRACES
    for ( levelCnt = 0 ; levelCnt < outImBufDesc.numPlanes ; levelCnt++)
    {
      if ( outImBufDesc.bufPlanes[levelCnt].buf != NULL )
      {
        free(outImBufDesc.bufPlanes[levelCnt].buf);
      }
    }
#endif

  }
#if (!HOST_EMULATION)
  /* Delete resouce manager Handle */
  EDMA3_LLD_HELPER_deinit(0, edma3RmLldHandle);
#endif

  return status;
}

int32_t main(int32_t argc, char *argv[])
{
  int32_t status = 0;
  char configFile[LD_FILE_NAME_SIZE]={0};
#if (!HOST_EMULATION)
  InitCache();
#endif
  if (argc > 1)
  {
    strcpy(configFile, argv[1]) ;
  }
  else
  {
    strcpy(configFile,"../testvecs/config/ld.cfg");
  }

  status = readparamfile(configFile, &gsTokenMap_LD[0]) ;
  if(status == -1)
  {
    printf("Parser Failed");
    return -1 ;
  }

  /* Validate the algorithm */
  status = ldTest(gConfig_LD);

  return status;
}



