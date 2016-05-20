/*==========================================================================*/
/*      Copyright (C) 2009-2015 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/** @file stereovision_tb.c
 *
 *  @brief  This file contains test code for stereovision postprocessing algorithm
 *
 *
 *  @date   March 2015
 *
 *  Description
 *    This file contains test code to validate the frame level algorithm TI ST
 *    
 */

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#include "stereovision_config.h"
#include "istereovision_ti.h"
#include "ti_mem_manager.h"
#if (!HOST_EMULATION)
#include "edma3_lld_helper.h"
#endif
#include "fileIO.h"
#include "profile.h"

#define ENABLE_TRACES 0
#define RANDOM_INPUT  0

#define DISABLE_FILE_IO 0

#if (!HOST_EMULATION)
#define _STATIC_INPUT
#endif

#if (HOST_EMULATION)
#define DISABLE_FILE_IO 0
/*#define ENABLE_TRACES 1*/
#endif

#ifdef _STATIC_INPUT

extern unsigned short inputFrame[640*480/2];
extern unsigned short inputDisparity[640*480/2];
extern unsigned short inputAuxDisparity[640*480/4];
extern unsigned short inputCost[3*640*480];
extern unsigned short outputDisparity0[640*480/2];
extern unsigned short outputDisparity3[640*480/2];
unsigned short *outputDisparity;
extern unsigned short gInput_width;
extern unsigned short gInput_height;
extern unsigned short gInput_bytesPerPixel;
extern unsigned short gInput_maxBitPerPixel;
extern unsigned short gInput_n_maxValue;

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
    L2CFG()  = 3;

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

#define DMEM_SIZE (24*1024)

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

void convertDisparityFalseColor(
        uint8_t *image_red, 
        uint8_t *image_grn, 
        uint8_t *image_blu, 
        uint8_t *dispOutput,
        uint16_t width,
        uint16_t height, 
        uint8_t numDisparities);

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
    TIMemHandle memHdl_DMEM = &memObj_DMEM;
    TIMemHandle memHdl_L2MEM = &memObj_L2MEM;

    for (i = 0; i < numMemRec; i++)
    {
        if(memRec[i].base == NULL)
        {
            return IALG_EFAIL;
        }
        else if(memRec[i].space == IALG_DARAM0) {
            TI_ResetMemoryHandle(memHdl_DMEM);
        }
        else if(memRec[i].space == IALG_DARAM1) {
            TI_ResetMemoryHandle(memHdl_L2MEM);
        }
        else {
            free(memRec[i].base);
        }
    }
    return IALG_EOK;
}

typedef struct IM_Fxns
{
    IVISION_Fxns * ivision;

} IM_Fxns;


int32_t stereovisionTest(sSTEREOVISION_Config * testcaseParams)
{
    int32_t numMemRec;
    uint32_t i;
    IALG_MemRec *memRec;
    int32_t status;
    uint32_t testcase;
    char *filename;
#ifndef _STATIC_INPUT
    FILE *fid;
    uint16_t bytesPerPixel;
    uint16_t maxBitPerPixel;
    uint8_t len;
    int32_t n_maxValue;
#else
    int32_t fail;
#endif
    long long  t0, t1;
    uint16_t n_rows_image, n_rows_disp, n_rows_aux_disp;
    uint16_t n_cols_image, n_cols_disp, n_cols_aux_disp;

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
    STEREOVISION_TI_CreateParams   createParams;
    STEREOVISION_TI_InArgs      inArgs;
    IVISION_InBufs    inBufs;

    /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
    IVISION_BufDesc   inBufDesc[STEREOVISION_TI_BUFDESC_IN_TOTAL];
    IVISION_BufDesc   *inBufDescList[STEREOVISION_TI_BUFDESC_IN_TOTAL];

    STEREOVISION_TI_OutArgs     outArgs;
    IVISION_OutBufs   outBufs;

    /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
    IVISION_BufDesc   outBufDesc[STEREOVISION_TI_BUFDESC_OUT_TOTAL];
    IVISION_BufDesc   *outBufDescList[STEREOVISION_TI_BUFDESC_OUT_TOTAL];

#if ENABLE_TRACES
    IVISION_BufDesc   outImBufDesc;
    IVISION_BufDesc   *outImBufDescList[1];
    IVISION_InBufs    outImBufs;
    uint8_t *laneOutIm;
    uint8_t  levelCnt=0;
#endif

    outArgs.iVisionOutArgs.size = sizeof(STEREOVISION_TI_OutArgs);
    inArgs.iVisionInArgs.size   = sizeof(STEREOVISION_TI_InArgs);

    uint32_t sizeDispOutput;
    uint8_t *dispOut;
    uint8_t *dispImage_red;
    uint8_t *dispImage_grn;
    uint8_t *dispImage_blu;
    uint16_t *prevCostIn;
    uint16_t *costIn;
    uint16_t *nextCostIn;
    uint16_t *confidenceOut;
    uint8_t *textureOut;

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

    filename = (char *)malloc(256);

    for ( testcase = 0 ; testcase < stereovision_numTestCases; testcase++ )
    {
        /*-----------------------------------------------------------------
      Set buffer descriptor pointers array base
      -----------------------------------------------------------------*/
        inBufs.bufDesc  = inBufDescList;
        outBufs.bufDesc = outBufDescList;

        inBufs.numBufs   = STEREOVISION_TI_BUFDESC_IN_TOTAL;
        outBufs.numBufs  = STEREOVISION_TI_BUFDESC_OUT_TOTAL;

        for(i = 0 ; i < STEREOVISION_TI_BUFDESC_IN_TOTAL ;i++)
        {
            inBufDescList[i]     = &inBufDesc[i];
            inBufDesc[i].numPlanes  = 1;
        }

        for(i = 0 ; i < STEREOVISION_TI_BUFDESC_OUT_TOTAL ;i++)
        {
            outBufDescList[i]     = &outBufDesc[i];
            outBufDesc[i].numPlanes  = 1;
        }

        /*-----------------------------------------------------------------
      Set algorithm parameters
      -----------------------------------------------------------------*/

#ifdef _STATIC_INPUT
        createParams.maxImageRoiWidth      = gInput_width;
        createParams.maxImageRoiHeight     = gInput_height;
        createParams.inputBitDepth         = 8;
        createParams.processingMode        = STEREOVISION_TI_POSTPROCESS_ONLY;
        createParams.disparityOptions.censusWinWidth        = 9;
        createParams.disparityOptions.censusWinHeight       = 9;
        createParams.disparityOptions.costSupportWinWidth     = 9;
        createParams.disparityOptions.costSupportWinHeight    = 9;
        createParams.disparityOptions.minDisparity        = 0;
        createParams.disparityOptions.maxDisparity        = 71;
        createParams.disparityOptions.disparityStep         = 1;
        createParams.disparityOptions.costMethod            = STEREOVISION_TI_HAM_DIST;
        createParams.disparityOptions.searchDir             = STEREOVISION_TI_LEFT_TO_RIGHT;
        inArgs.postProcOptions.disparityNumFracBits   = 0;
        inArgs.postProcOptions.disparityMinThreshold   = 0;
        inArgs.postProcOptions.disparityMaxThreshold   = 72;
        inArgs.postProcOptions.costMaxThreshold        = 60;
        inArgs.postProcOptions.minConfidenceThreshold  = 98;
        inArgs.postProcOptions.holeFillingStrength  = 5;
        inArgs.postProcOptions.textureLumaLoThresh= 0;
        inArgs.postProcOptions.textureLumaHiThresh= 100;
        inArgs.postProcOptions.textureThreshold= 100;
        inArgs.postProcOptions.maxDispDissimilarity= 4;
        inArgs.postProcOptions.lrMaxDiffThreshold= 3;
        inArgs.postProcOptions.minConfidentNSegment= 6;
        inArgs.postProcOptions.auxDisparityHorzDsFactor= 1;
        inArgs.postProcOptions.auxDisparityVertDsFactor= 2;

        /* If smoothingStrength== 0, set outputDisparity to &outputDisparity0[0]
         * if smoothingStrength== 3, set outputDisparity to &outputDisparity3[0]
         */
#if 1
        /* When smoothingStrength= 0, we only perform confidence/curvature calculation, thresholding to remove unreliable disparities and then we apply hole filling */
        inArgs.postProcOptions.smoothingStrength      = STEREOVISION_TI_SMOOTHING_STRENGTH_NONE;
        outputDisparity= &outputDisparity0[0];
#else
        /* When smoothingStrength= 1,2 or 3 in addition to above, we perform noise filtering */
        inArgs.postProcOptions.smoothingStrength      = STEREOVISION_TI_SMOOTHING_STRENGTH_HI;
        outputDisparity= &outputDisparity3[0];
#endif
        testcaseParams[testcase].startX= 8;
        testcaseParams[testcase].startY= 8;
#else
        createParams.maxImageRoiWidth      = testcaseParams[testcase].maxImageWidth;
        createParams.maxImageRoiHeight     = testcaseParams[testcase].maxImageHeight;
        createParams.inputBitDepth         = testcaseParams[testcase].inputBitDepth;
        createParams.processingMode        = STEREOVISION_TI_POSTPROCESS_ONLY;
        createParams.disparityOptions.censusWinWidth        = testcaseParams[testcase].censusWinWidth;
        createParams.disparityOptions.censusWinHeight       = testcaseParams[testcase].censusWinHeight;
        createParams.disparityOptions.costSupportWinWidth     = testcaseParams[testcase].costSupportWinWidth;
        createParams.disparityOptions.costSupportWinHeight    = testcaseParams[testcase].costSupportWinHeight;
        createParams.disparityOptions.minDisparity        = 0;
        createParams.disparityOptions.maxDisparity        = testcaseParams[testcase].numDisparities - 1;
        createParams.disparityOptions.disparityStep         = testcaseParams[testcase].disparityStep;
        createParams.disparityOptions.costMethod            = STEREOVISION_TI_HAM_DIST;
        createParams.disparityOptions.searchDir             = testcaseParams[testcase].searchDir;
        inArgs.postProcOptions.disparityNumFracBits   = testcaseParams[testcase].disparityNumFracBits;
        inArgs.postProcOptions.disparityMinThreshold   = testcaseParams[testcase].disparityMinThreshold;
        inArgs.postProcOptions.disparityMaxThreshold   = testcaseParams[testcase].disparityMaxThreshold;
        inArgs.postProcOptions.costMaxThreshold        = testcaseParams[testcase].costMaxThreshold;
        inArgs.postProcOptions.minConfidenceThreshold  = testcaseParams[testcase].minConfidenceThreshold;
        inArgs.postProcOptions.holeFillingStrength  = testcaseParams[testcase].holeFillingStrength;
        inArgs.postProcOptions.smoothingStrength      = (STEREOVISION_TI_SmoothingStrength) testcaseParams[testcase].smoothingStrength;
        inArgs.postProcOptions.textureLumaLoThresh= testcaseParams[testcase].textureLumaLoThresh;
        inArgs.postProcOptions.textureLumaHiThresh= testcaseParams[testcase].textureLumaHiThresh;
        inArgs.postProcOptions.textureThreshold= testcaseParams[testcase].textureThreshold;
        inArgs.postProcOptions.lrMaxDiffThreshold= testcaseParams[testcase].lrMaxDiffThreshold;
        inArgs.postProcOptions.maxDispDissimilarity= testcaseParams[testcase].maxDispDissimilarity;
        inArgs.postProcOptions.minConfidentNSegment= testcaseParams[testcase].minConfidentNSegment;
        inArgs.postProcOptions.auxDisparityHorzDsFactor= 1;
        inArgs.postProcOptions.auxDisparityVertDsFactor= 2;
#endif


#if (!HOST_EMULATION)
        createParams.edma3RmLldHandle   = edma3RmLldHandle;
#else
        createParams.edma3RmLldHandle   = NULL;
#endif

        /*-----------------------------------------------------------------
      Query alogorithm memory requirement using standard IALG interface
      -----------------------------------------------------------------*/
        numMemRec = STEREOVISION_TI_VISION_FXNS.ialg.algNumAlloc();
        memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

        status = STEREOVISION_TI_VISION_FXNS.ialg.algAlloc((IALG_Params *)(&createParams), NULL, memRec);

        if(status != IALG_EOK)
        {
            PRINT_ERRORE_MSG();
            goto EXIT_LOOP;
        }
#if ENABLE_TRACES
        printf("Stereovision algorithm Create Done\n");
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
        status = STEREOVISION_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
                memRec,NULL,(IALG_Params *)(&createParams));

        handle = (IM_Fxns *) memRec[0].base;

        if(status != IALG_EOK)
        {
            PRINT_ERRORE_MSG();
            goto EXIT_LOOP;
        }
#if ENABLE_TRACES
        printf("Stereovision algorithm Init Done\n");
#endif

        inArgs.iVisionInArgs.subFrameInfo = 0;
        inArgs.iVisionInArgs.size         = sizeof(STEREOVISION_TI_InArgs);

#if ENABLE_TRACES
        printf("Processing started for frame \n");
#endif

#ifdef _STATIC_INPUT
        n_cols_image= gInput_width;
        n_rows_image= gInput_height;
        n_cols_disp= gInput_width;
        n_rows_disp= gInput_height;
        n_cols_aux_disp= gInput_width;
        n_rows_aux_disp= gInput_height/2;
        /*bytesPerPixel= gInput_bytesPerPixel;
        maxBitPerPixel= gInput_maxBitPerPixel;
        n_maxValue= gInput_n_maxValue;*/

        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].buf= (void*)&inputFrame[0];
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->bufPlanes[0].buf= (void*)&inputDisparity[0];
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_AUX_DISPARITY]->bufPlanes[0].buf= (void*)&inputAuxDisparity[0];
        prevCostIn= (uint16_t*)&inputCost[0];
        costIn= (uint16_t*)&inputCost[n_cols_image*n_rows_image];
        nextCostIn= (uint16_t*)&inputCost[2*n_cols_image*n_rows_image];

#else
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].buf=  NULL;
        readFilePGM((const int8_t*)testcaseParams[testcase].inImageFileName,
                (uint8_t**)&inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].buf,
                &n_rows_image,
                &n_cols_image,
                &bytesPerPixel,
                &maxBitPerPixel,
                &n_maxValue);

        if (testcaseParams[testcase].maxImageWidth*testcaseParams[testcase].maxImageHeight < n_rows_image*n_cols_image) {
            PRINT_ERRORE_MSG();
            goto EXIT_LOOP;
        }

        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->bufPlanes[0].buf= NULL;
        readFilePGM((const int8_t*)testcaseParams[testcase].inDisparityFileName,
                (uint8_t**)&inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->bufPlanes[0].buf,
                &n_rows_disp,
                &n_cols_disp,
                &bytesPerPixel,
                &maxBitPerPixel,
                &n_maxValue);

        if (testcaseParams[testcase].maxImageWidth*testcaseParams[testcase].maxImageHeight < n_rows_disp*n_cols_disp) {
            PRINT_ERRORE_MSG();
            goto EXIT_LOOP;
        }
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_AUX_DISPARITY]->bufPlanes[0].buf= NULL;
        readFilePGM((const int8_t*)testcaseParams[testcase].inAuxDisparityFileName,
                (uint8_t**)&inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_AUX_DISPARITY]->bufPlanes[0].buf,
                &n_rows_aux_disp,
                &n_cols_aux_disp,
                &bytesPerPixel,
                &maxBitPerPixel,
                &n_maxValue);

        if (testcaseParams[testcase].maxImageWidth*testcaseParams[testcase].maxImageHeight < n_rows_aux_disp*n_cols_aux_disp) {
            PRINT_ERRORE_MSG();
            goto EXIT_LOOP;

        }

        /* Allocate buffers for costs */
        costIn= (uint16_t*)malloc(2*n_cols_disp*n_rows_disp);
        assert(costIn != NULL);
        prevCostIn= (uint16_t*)malloc(2*n_cols_disp*n_rows_disp);
        assert(prevCostIn != NULL);
        nextCostIn= (uint16_t*)malloc(2*n_cols_disp*n_rows_disp);
        assert(nextCostIn != NULL);

        fid= fopen((char*)testcaseParams[testcase].inCostFileName,"rb");
        assert(fid!=NULL);
        fread(prevCostIn, 2, n_cols_disp*n_rows_disp, fid);
        fread(costIn, 2, n_cols_disp*n_rows_disp, fid);
        fread(nextCostIn, 2, n_cols_disp*n_rows_disp, fid);

        fclose(fid);
#endif

        /* Allocate output buffers */
        sizeDispOutput= 2*n_cols_disp*n_rows_disp;

        dispOut= (uint8_t*)malloc(sizeDispOutput);
        assert(dispOut != NULL);

        confidenceOut= (uint16_t*)malloc(sizeDispOutput);
        assert(confidenceOut != NULL);

        textureOut= (uint8_t*)malloc(sizeDispOutput/2);
        assert(textureOut != NULL);

        dispImage_red= (uint8_t*)malloc(sizeDispOutput);
        assert(dispImage_red != NULL);

        dispImage_grn= (uint8_t*)malloc(sizeDispOutput);
        assert(dispImage_grn != NULL);

        dispImage_blu= (uint8_t*)malloc(sizeDispOutput);
        assert(dispImage_blu != NULL);

        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_IMAGE]->numPlanes                       = 1;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].frameROI.topLeft.x = testcaseParams[testcase].startX;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].frameROI.topLeft.y = testcaseParams[testcase].startY;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].width              = n_cols_image;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].height             = n_rows_image;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].frameROI.width     = n_cols_disp;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].frameROI.height    = n_rows_disp;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].planeType          = 0; // Luma Y

        /* Lines below not needed as readFilePGM() internally allocated and set inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].buf
        inBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].buf = TI_GetMemoryChunk(memHdl_EXTMEM, size, 4);

        if((inBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].buf == NULL))
        {
            PRINT_ERRORE_MSG();
        }
         */
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->numPlanes                       = 1;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->bufPlanes[0].frameROI.topLeft.x = 0;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->bufPlanes[0].frameROI.topLeft.y = 0;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->bufPlanes[0].width              = n_cols_disp;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->bufPlanes[0].height             = n_rows_disp;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->bufPlanes[0].frameROI.width     = n_cols_disp;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->bufPlanes[0].frameROI.height    = n_rows_disp;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->bufPlanes[0].planeType          = 0; // Luma Y

        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_AUX_DISPARITY]->numPlanes                       = 1;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_AUX_DISPARITY]->bufPlanes[0].frameROI.topLeft.x = 0;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_AUX_DISPARITY]->bufPlanes[0].frameROI.topLeft.y = 0;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_AUX_DISPARITY]->bufPlanes[0].width              = n_cols_aux_disp;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_AUX_DISPARITY]->bufPlanes[0].height             = n_rows_aux_disp;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_AUX_DISPARITY]->bufPlanes[0].frameROI.width     = n_cols_aux_disp;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_AUX_DISPARITY]->bufPlanes[0].frameROI.height    = n_rows_aux_disp;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_AUX_DISPARITY]->bufPlanes[0].planeType          = 0; // Luma Y

        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_PREV_COST]->numPlanes                       = 1;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_PREV_COST]->bufPlanes[0].frameROI.topLeft.x = 0;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_PREV_COST]->bufPlanes[0].frameROI.topLeft.y = 0;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_PREV_COST]->bufPlanes[0].width              = n_cols_disp;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_PREV_COST]->bufPlanes[0].height             = n_rows_disp;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_PREV_COST]->bufPlanes[0].frameROI.width     = n_cols_disp;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_PREV_COST]->bufPlanes[0].frameROI.height    = n_rows_disp;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_PREV_COST]->bufPlanes[0].planeType          = 0;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_PREV_COST]->bufPlanes[0].buf= prevCostIn;

        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_COST]->numPlanes                       = 1;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_COST]->bufPlanes[0].frameROI.topLeft.x = 0;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_COST]->bufPlanes[0].frameROI.topLeft.y = 0;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_COST]->bufPlanes[0].width              = n_cols_disp;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_COST]->bufPlanes[0].height             = n_rows_disp;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_COST]->bufPlanes[0].frameROI.width     = n_cols_disp;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_COST]->bufPlanes[0].frameROI.height    = n_rows_disp;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_COST]->bufPlanes[0].planeType          = 0;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_COST]->bufPlanes[0].buf= costIn;

        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_NEXT_COST]->numPlanes                       = 1;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_NEXT_COST]->bufPlanes[0].frameROI.topLeft.x = 0;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_NEXT_COST]->bufPlanes[0].frameROI.topLeft.y = 0;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_NEXT_COST]->bufPlanes[0].width              = n_cols_disp;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_NEXT_COST]->bufPlanes[0].height             = n_rows_disp;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_NEXT_COST]->bufPlanes[0].frameROI.width     = n_cols_disp;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_NEXT_COST]->bufPlanes[0].frameROI.height    = n_rows_disp;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_NEXT_COST]->bufPlanes[0].planeType          = 0;
        inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_NEXT_COST]->bufPlanes[0].buf= nextCostIn;

        /* Lines below not needed as readFilePGM() internally allocated and set inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->bufPlanes[0].buf
        size = (inBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->bufPlanes[0].width)*(inBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->bufPlanes[0].height);
        inBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->bufPlanes[0].buf = TI_GetMemoryChunk(memHdl_EXTMEM, size, 4);
        if((inBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->bufPlanes[0].buf == NULL))
        {
            PRINT_ERRORE_MSG();
        }
         */

        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_DISPARITY]->numPlanes                        = 1;
        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_DISPARITY]->bufPlanes[0].frameROI.topLeft.x  = 0;
        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_DISPARITY]->bufPlanes[0].frameROI.topLeft.y  = 0;
        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_DISPARITY]->bufPlanes[0].width               = n_cols_disp;
        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_DISPARITY]->bufPlanes[0].height              = n_rows_disp;
        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_DISPARITY]->bufPlanes[0].frameROI.width      = n_cols_disp;
        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_DISPARITY]->bufPlanes[0].frameROI.height     = n_rows_disp;
        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_DISPARITY]->bufPlanes[0].planeType           = 0;
        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_DISPARITY]->bufPlanes[0].buf = dispOut;

        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_CONFIDENCE]->numPlanes                        = 1;
        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_CONFIDENCE]->bufPlanes[0].frameROI.topLeft.x  = 0;
        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_CONFIDENCE]->bufPlanes[0].frameROI.topLeft.y  = 0;
        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_CONFIDENCE]->bufPlanes[0].width               = n_cols_disp;
        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_CONFIDENCE]->bufPlanes[0].height              = n_rows_disp;
        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_CONFIDENCE]->bufPlanes[0].frameROI.width      = n_cols_disp;
        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_CONFIDENCE]->bufPlanes[0].frameROI.height     = n_rows_disp;
        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_CONFIDENCE]->bufPlanes[0].planeType           = 0;
        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_CONFIDENCE]->bufPlanes[0].buf = confidenceOut;

        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_TEXTURE]->numPlanes                        = 1;
        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_TEXTURE]->bufPlanes[0].frameROI.topLeft.x  = 0;
        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_TEXTURE]->bufPlanes[0].frameROI.topLeft.y  = 0;
        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_TEXTURE]->bufPlanes[0].width               = n_cols_disp;
        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_TEXTURE]->bufPlanes[0].height              = n_rows_disp;
        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_TEXTURE]->bufPlanes[0].frameROI.width      = n_cols_disp;
        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_TEXTURE]->bufPlanes[0].frameROI.height     = n_rows_disp;
        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_TEXTURE]->bufPlanes[0].planeType           = 0;
        outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_TEXTURE]->bufPlanes[0].buf = textureOut;

        memset(outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_DISPARITY]->bufPlanes[0].buf , 100, 2*outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_DISPARITY]->bufPlanes[0].width * outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_DISPARITY]->bufPlanes[0].height);
        memset(outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_CONFIDENCE]->bufPlanes[0].buf ,0, 2*outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_CONFIDENCE]->bufPlanes[0].width * outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_CONFIDENCE]->bufPlanes[0].height);
        memset(outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_TEXTURE]->bufPlanes[0].buf ,0, outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_TEXTURE]->bufPlanes[0].width * outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_CONFIDENCE]->bufPlanes[0].height);

#if (!HOST_EMULATION)
        /* Write back Invalidate cache */
        CacheWbInv();
        t0 = _TSC_read();
#endif
        status = handle->ivision->algProcess((IVISION_Handle)handle,
                &inBufs,&outBufs,(IVISION_InArgs *)&inArgs,(IVISION_OutArgs *)&outArgs);
#if (!HOST_EMULATION)
        t1 = _TSC_read();
        printf(" MCycles per frame %d \n", (t1-t0)/1000000);      
        /* Write back Invalidate cache */
        CacheWbInv();

        {
            TI_DSP_PrfInfo*       prfInfo;
            int32_t md;
            prfInfo = (TI_DSP_PrfInfo*)(outArgs.rsvd1);

            printf("  Sub-Modules Profile Info\n");

            for(md = 0; md < TI_DSP_PROFILE_MAX; md ++){
                if((prfInfo->prfData[md].moduleId != -1))
                    printf("    MODULE%3d TotalCycle = %10d TotalCount = %10d avgCycle = %5d\n",\
                            prfInfo->prfData[md].moduleId,
                            prfInfo->prfData[md].totalTime,
                            prfInfo->prfData[md].count,
                            (prfInfo->prfData[md].totalTime/prfInfo->prfData[md].count));
            }
        }
#endif

        if(status != IALG_EOK)
        {
            PRINT_ERRORE_MSG();
            goto EXIT_LOOP;
        }
#if ENABLE_TRACES
        printf("Processing Completed\n");
#endif

#ifdef _STATIC_INPUT
#ifndef _TEST_EDMA
        /* If static input then we programmatically validate the output */
        fail= 0;
        for (i=0;i<(n_cols_image*(n_rows_image-29))/4;i++) { /* -29 because the last 29 rows are incorrect due to median filterlenght of up to 29 */
            if (*((uint32_t*)outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_DISPARITY]->bufPlanes[0].buf + i ) != *((uint32_t*)outputDisparity + i)) {
                printf("Mismatch at x= %d, y= %d\n", (i*4)%n_cols_image, (i*4)/n_cols_image);
                fail= 1;
            }
        }
#else
        /* If static input and we just want to test EDMA then the processing was just a copy of input to output */
        fail= 0;
        for (i=0;i<(n_cols_image*n_rows_image)/4;i++) { 
            if (*((uint32_t*)outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_DISPARITY]->bufPlanes[0].buf + i ) != *((uint32_t*)inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->bufPlanes[0].buf + i ) ) {
                printf("Mismatch at x= %d, y= %d\n", (i*4)%n_cols_image, (i*4)/n_cols_image);
                fail= 1;
            }
        }
#endif
        if (fail==0) {
            printf("Verification successful !!!!\n");
        }
#else
        writeFile_PGM((const int8_t *)testcaseParams[testcase].outFileName, 
                (const uint8_t *)outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_DISPARITY]->bufPlanes[0].buf,
                n_rows_disp,
                n_cols_disp,
                NULL,
                255);

        convertDisparityFalseColor(
                dispImage_red, 
                dispImage_grn, 
                dispImage_blu, 
                (uint8_t *)outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_DISPARITY]->bufPlanes[0].buf,
                n_cols_disp, 
                n_rows_disp, 
                createParams.disparityOptions.maxDisparity - createParams.disparityOptions.minDisparity + 1);

        // changes the .pgm extension to .ppm
        len = strlen((const char*)testcaseParams[testcase].outFileName);
        testcaseParams[testcase].outFileName[len-2] = 112; //"p";

        /* Write output ppmfile */
        writeFile_PPM((const int8_t *)testcaseParams[testcase].outFileName, 
                dispImage_red,
                dispImage_grn,
                dispImage_blu,
                n_rows_disp,
                n_cols_disp,
                NULL,
                255);

        len = strlen((const char*)testcaseParams[testcase].outFileName);
        testcaseParams[testcase].outFileName[len-2] = 112; //"p";

        /* Write confidence map into output bin file*/
        sprintf(filename, "%s.bin", testcaseParams[testcase].outFileName);

        // Replace '.pgm' with 'Cost' in the filename
        i = strlen(filename);
        filename[i-8] = 'C'; 
        filename[i-7] = 'o'; 
        filename[i-6] = 'n'; 
        filename[i-5] = 'f'; 


        fid= fopen(filename,"wb");
        assert(fid!=NULL);
        fwrite(confidenceOut, 1, 2*n_cols_disp*n_rows_disp, fid);
        fclose(fid);

        /* Write texture map into output pgm file*/
        sprintf(filename, "%s.pgm", testcaseParams[testcase].outFileName);

        // Replace '.pgm' with 'Text' in the filename
        i = strlen(filename);
        filename[i-8] = 'T'; 
        filename[i-7] = 'e'; 
        filename[i-6] = 'x'; 
        filename[i-5] = 't'; 


        writeFile_PGM((const int8_t *)filename, 
                (const uint8_t *)outBufs.bufDesc[STEREOVISION_TI_BUFDESC_OUT_TEXTURE]->bufPlanes[0].buf,
                n_rows_disp,
                n_cols_disp,
                NULL,
                255);

#endif         
        EXIT_LOOP:

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

        if (dispOut != NULL)
        {
            free(dispOut);
        }

        if (confidenceOut != NULL)
        {
            free(confidenceOut);
        }

        if (textureOut != NULL)
        {
            free(textureOut);
        }

        if (dispImage_red != NULL)
        {
            free(dispImage_red);
        }

        if (dispImage_grn != NULL)
        {
            free(dispImage_grn);
        }

        if (dispImage_blu != NULL)
        {
            free(dispImage_blu);
        }
#ifndef _STATIC_INPUT

        if (inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].buf != NULL) {
            free(inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].buf);
        }

        if (inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->bufPlanes[0].buf != NULL) {
            free(inBufs.bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->bufPlanes[0].buf);
        }

        if (prevCostIn != NULL)
        {
            free(prevCostIn);
        }

        if (costIn != NULL)
        {
            free(costIn);
        }

        if (nextCostIn != NULL)
        {
            free(nextCostIn);
        }
#endif
#if (!HOST_EMULATION)
        /* Delete resouce manager Handle */
        EDMA3_LLD_HELPER_deinit(0, edma3RmLldHandle);
#endif

    }

    free(filename);

    return status;
}

int32_t main(int32_t argc, char *argv[])
{
    int32_t status = 0;
    char configFile[STEREOVISION_FILE_NAME_SIZE]={0};
#if (!HOST_EMULATION)
    InitCache();
#endif
    if (argc > 1)
    {
        strcpy(configFile, argv[1]) ;
    }
    else
    {
        strcpy(configFile,"../testvecs/config/stereovision.cfg");
    }

    status = readparamfile(configFile, &gsTokenMap_STEREOVISION[0]) ;
    if(status == -1)
    {
        printf("Parser Failed");
        return -1 ;
    }

    /* Validate the algorithm */
    status = stereovisionTest(gConfig_STEREOVISION);

    return status;
}


/* The below table is used by convertDisparityFalseColor for producing a disparity colormap */
const uint8_t falseColorLUT_RGB[3][257] = {
        {0,33,28,24,21,18,14,10,6,3,1,2,2,2,3,2,3,2,2,2,2,3,3,3,2,2,2,3,3,2,3,1,3,3,2,2,3,2,3,3,2,2,3,2,2,3,3,3,3,2,2,4,2,3,3,2,3,3,2,2,3,3,3,2,2,3,2,2,3,1,3,2,3,2,3,3,3,2,2,2,2,3,2,3,2,3,3,3,3,2,2,2,3,2,3,2,4,2,1,3,2,2,2,3,3,3,2,2,2,1,8,13,20,26,31,38,44,50,56,63,67,74,81,86,93,99,104,110,117,123,129,136,140,147,155,159,166,172,177,183,191,196,202,209,214,219,225,231,238,244,249,255,254,255,255,255,255,255,255,255,255,254,255,255,254,255,255,255,255,255,255,255,255,254,255,255,255,255,255,255,255,255,255,255,255,255,255,254,255,255,255,255,255,255,255,255,255,255,255,254,255,255,254,255,255,255,255,255,255,255,254,254,255,254,255,255,255,254,255,255,255,255,255,255,255,255,255,255,255,255,255,255,254,255,255,255,254,255,255,255,254,255,254,255,255,255,255,255,254,255,255,255,255,255,255,254,255},
        {0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,6,12,19,25,32,37,43,51,57,63,70,76,82,89,95,101,109,115,120,127,133,140,146,152,158,165,172,178,184,190,196,204,209,216,222,229,236,241,247,254,254,254,255,254,254,255,254,254,255,254,255,254,254,254,254,253,254,253,254,254,253,255,253,253,254,254,254,254,254,254,254,253,254,253,254,254,253,254,254,254,254,253,254,253,254,254,253,254,254,254,253,254,254,254,254,253,254,253,254,255,254,254,254,254,254,254,255,254,255,254,254,255,254,254,254,255,254,255,255,255,255,255,252,249,247,244,241,239,237,234,231,230,227,225,222,219,217,215,211,209,207,205,201,200,198,195,192,189,187,184,181,179,177,174,171,169,168,164,162,160,157,154,152,150,147,144,142,139,138,135,132,130,126,124,122,120,116,114,112,109,107,105,100,97,94,90,87,83,81,76,73,70,67,63,59,57,52,49,45,43,39,35,31,29,25,21,18,15,11,7,4,1,0,0,1,0,1,0,1,1,0,1,1,1,1,1,1},
        {0,96,101,104,108,113,116,120,125,129,135,142,148,153,160,166,174,179,185,192,198,205,211,217,224,230,235,242,248,255,255,255,255,255,254,255,255,255,255,255,254,253,255,255,255,254,255,255,255,255,255,255,255,254,254,255,255,255,255,254,254,255,255,255,255,255,255,255,255,255,249,242,236,231,224,217,210,205,199,192,186,179,173,169,162,155,149,144,138,130,123,117,112,105,99,91,87,80,73,67,60,54,48,41,35,28,23,17,9,2,5,4,4,3,3,4,3,3,2,3,4,4,4,4,4,3,3,2,3,3,2,5,4,4,4,3,4,3,3,2,3,3,4,4,4,4,3,3,4,3,3,2,2,3,4,5,2,3,4,5,2,3,4,3,3,4,4,3,3,4,3,3,3,4,3,4,3,4,3,3,4,2,3,3,4,3,4,3,2,3,4,3,2,3,4,4,3,3,4,2,3,4,3,2,3,4,2,2,3,4,2,3,2,2,3,3,2,2,3,2,2,3,3,2,2,3,3,2,2,3,3,2,2,3,2,2,2,3,2,2,2,3,9,16,23,27,34,40,48,53,59,66,73,77,85,89,96}
};

void convertDisparityFalseColor(
        uint8_t *image_red, 
        uint8_t *image_grn, 
        uint8_t *image_blu, 
        uint8_t *dispOutput,
        uint16_t width,
        uint16_t height, 
        uint8_t numDisparities) {

    int32_t x, y, value, idx=0;

    idx= 0;
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            value = (dispOutput[idx] * (int32_t)255)/numDisparities;
            image_red[idx] = (uint8_t) (falseColorLUT_RGB[0][value]); 
            image_grn[idx] = (uint8_t) (falseColorLUT_RGB[1][value]); 
            image_blu[idx] = (uint8_t) (falseColorLUT_RGB[2][value]); 
            idx++;
        }
    }
}

