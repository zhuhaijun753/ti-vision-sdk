/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      vcop_vec_bin_image_morph_diff                                      */
/*                                                                          */
/*  Test file for testing Morph Diff kernel function              */
/*                                                                          */
/*                                                                          */
/*  USAGE                                                                   */
/*      This code contains a driver program for testing the 'vcop_vec_bin_  */
/*  _image_morph_diff" function by injecting it with the same data set as  */
/*  natural C testbench functions.                                          */
/*                                                                          */
/*  This testbench then compares the results with the expected output       */
/*  array by doing a standard "memcmp" function and printing a pass/fail    */
/*  message. If it failed it prints a byte by byte trace.                   */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>

#if (!VCOP_HOST_EMULATION)
#include "GlobalTypes.h"
#include "baseaddress.h"
#include "sctm.h"
#endif

#include "vcop.h"
#include "eve_profile.h"
#include "configparser.h"
#include "vcop_vec_bin_image_morph_diff_config.h"

#include "vcop_vec_bin_image_morph_diff_c.h"
#if (VCOP_HOST_EMULATION)
#include "..\src_kernelC\vcop_vec_bin_image_morph_diff_kernel.k"
#else
#include "vcop_vec_bin_image_morph_diff_kernel.h"
#endif


#define MAX_CONFIG_LINE_SIZE     (300U)
#define MAX_FILE_NAME_SIZE       (200U)
#define MAX_PARAM_STRING_SIZE    (30U)

#define SE_WIDTH                 (3U)
#define SE_HEIGHT                (3U)
#define PACKED_PIXEL_COUNT       (8U)

#if (VCOP_HOST_EMULATION)
#define Bin_Morphology_malloc(heap, size)   malloc(size)
#define Bin_Morphology_free(ptr)            free(ptr)
#else
#define Bin_Morphology_malloc(heap, size)   vcop_malloc(heap, size)
#define Bin_Morphology_free(ptr)            vcop_free(ptr)
#endif



char * moveToNextElement(char *in, char *LinePtr)
{
    LinePtr += strlen(in);
    while((LinePtr[0] == ' ')||(LinePtr[0] == '	')||(LinePtr[0] == ','))
    {
      LinePtr++;
    }
    return(LinePtr);
}

void fillDefaultConfig(sBin_Morphology_Morph_Diff_Config *params)
{
    strcpy((char *)params->testCaseName, "BinaryMorphology_Diff");
    strcpy((char *)params->inImageA, "");
    strcpy((char *)params->inImageB, "");
    strcpy((char *)params->outImage, "");
    strcpy((char *)params->desc, "");
    params->performanceTestcase = 1;

    params->blkWidth       = 32;
    params->blkStride      = 32;
    params->blkHeight      = 30;
    params->dataAbitShift  = 2;
    params->dataBbitShift  = 0;
}

void test_binary_morphology_morph_diff(sBin_Morphology_Morph_Diff_Config *testcaseParams)
{
    uint32_t *dataPtr_A, *dataPtr_C, *outputPtr_B, *refOutputPtr;
    uint8_t  *dataPtr_u8_A, *dataPtr_u8_C, fail;
    uint32_t  i, j;
    FILE     *fp;

    profiler_init();

    vcop_minit();
    /*-----------------------------------------------------------------
          Open Input File. If non existant, fill input with data.
          -----------------------------------------------------------------*/
    dataPtr_A = (uint32_t *)Bin_Morphology_malloc(VCOP_IBUFLA,
                                           testcaseParams->blkStride*testcaseParams->blkHeight);
    dataPtr_C = (uint32_t *)Bin_Morphology_malloc(VCOP_WMEM,
                                           testcaseParams->blkStride*testcaseParams->blkHeight);
    outputPtr_B = (uint32_t *)Bin_Morphology_malloc(VCOP_IBUFHA,
                                           testcaseParams->blkStride*testcaseParams->blkHeight);

    fp = fopen((char *)testcaseParams->inImageA, "rb");
    if(fp == NULL)
    {
        dataPtr_u8_A = (uint8_t *)dataPtr_A;
        srand(1);
        for(i = 0; i < (testcaseParams->blkStride * testcaseParams->blkHeight); i++)
        {
           dataPtr_u8_A[i] = rand() % 256;
        }
    } else
    {
        fread(dataPtr_A, 1, testcaseParams->blkStride*testcaseParams->blkHeight, fp);
        fclose(fp);
    }
    fp = fopen((char *)testcaseParams->inImageB, "rb");
    if(fp == NULL)
    {
        dataPtr_u8_C = (uint8_t *)dataPtr_C;
        srand(1);
        for(i = 0; i < (testcaseParams->blkStride * testcaseParams->blkHeight); i++)
        {
           dataPtr_u8_C[i] = rand() % 256;
        }
    } else
    {
        fread(dataPtr_C, 1, testcaseParams->blkStride*testcaseParams->blkHeight, fp);
        fclose(fp);
    }

    refOutputPtr  = (uint32_t *)malloc(testcaseParams->blkStride*testcaseParams->blkHeight);
    memset(refOutputPtr, 0, testcaseParams->blkStride*testcaseParams->blkHeight);

    /*---------------------------------------------------------------------*/
    /*  Function call to the VCOP-C API to be tested                       */
    /*---------------------------------------------------------------------*/

    for (i = 0; i < 2; i++)
    {
        memset(outputPtr_B, 0, testcaseParams->blkStride*testcaseParams->blkHeight);

        profiler_start();

        vcop_vec_bin_image_morph_diff(testcaseParams->blkWidth *PACKED_PIXEL_COUNT,
                                      testcaseParams->blkStride*PACKED_PIXEL_COUNT,
                                      testcaseParams->blkHeight,
                                      dataPtr_A,
                                      testcaseParams->dataAbitShift,
                                      dataPtr_C,
                                      testcaseParams->dataBbitShift,
                                      outputPtr_B);

        profiler_end_print(1);
        profiler_performanceParam(testcaseParams->blkWidth * testcaseParams->blkHeight);
    }

    vcop_vec_bin_image_morph_diff_cn(testcaseParams->blkWidth *PACKED_PIXEL_COUNT,
                                     testcaseParams->blkStride*PACKED_PIXEL_COUNT,
                                     testcaseParams->blkHeight,
                                     dataPtr_A,
                                     testcaseParams->dataAbitShift,
                                     dataPtr_C,
                                     testcaseParams->dataBbitShift,
                                     refOutputPtr);

    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*  If there is a mis-compare, print out a memory trace, else print    */
    /*  pass.                                                              */
    /*---------------------------------------------------------------------*/
    fail = 0;
    for (i = 0; i < (testcaseParams->blkHeight); i++)
    {
        for (j = 0; j < (testcaseParams->blkWidth/sizeof(*outputPtr_B)); j++)
        {
            if( outputPtr_B[i*testcaseParams->blkStride/sizeof(*outputPtr_B) + j] !=
               refOutputPtr[i*testcaseParams->blkStride/sizeof(*outputPtr_B) + j])
            {
                fail = 1;
                printf ("i:%d, j:%d, Out:%u, Ref_Out:%u \n", i, j,
                        outputPtr_B[i*testcaseParams->blkStride/sizeof(*outputPtr_B) + j],
                        refOutputPtr[i*testcaseParams->blkStride/sizeof(*outputPtr_B) + j]);
            }
        }
    }

    profiler_printStatus(fail);
    profiler_deinit();

    fp = fopen((char *)testcaseParams->outImage, "wb");
    if(fp != NULL)
    {
        fwrite(outputPtr_B, 1, testcaseParams->blkStride*testcaseParams->blkHeight, fp);
        fclose(fp);
    }

    Bin_Morphology_free(dataPtr_A);
    Bin_Morphology_free(dataPtr_C);
    Bin_Morphology_free(outputPtr_B);
    free(refOutputPtr);

}



int32_t main(int32_t argc, char *argv[])
{
    char    configFile[FILE_NAME_SIZE]={0};
    char    configLine[MAX_CONFIG_LINE_SIZE];
    char    configParam[MAX_PARAM_STRING_SIZE];
    int8_t *LinePtr;
    FILE   *fp;
    int32_t lineNum = -1, config_cmd, status = 0;

    if (argc > 1)
    {
        strcpy(configFile, argv[1]) ;
    } else
    {
        strcpy(configFile, "../testvecs/config/config_list.txt");
    }

    fp = fopen((const char *)configFile , "r");
    if(fp== NULL)
    {
        printf("Could not open config list file : %s \n", configFile);
        return(status);
    }
    CF_profile_init(2, "vcop_vec_bin_image_morph_diff");

    while(1)
    {
        memset(configLine, 0, MAX_CONFIG_LINE_SIZE);
        status  = (int)fgets(configLine,MAX_CONFIG_LINE_SIZE,fp);
        LinePtr = (int8_t *)configLine;
        if ((status == EOF) || (status == 0))
        {
            break;
        }

        status = 0;
        lineNum++;
        sscanf((const char *)LinePtr, "%d",&config_cmd);
        sscanf((const char *)LinePtr, "%s",configParam);

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
            LinePtr = (int8_t *)moveToNextElement(configParam,(char *)LinePtr);
            status  = sscanf((const char *)LinePtr, "%s",configFile);
            fillDefaultConfig(&gConfig_bin_morphology_morph_diff);

            printf("\nProcessing config file %s !\n", configFile);
            status = readparamfile(configFile, &gsTokenMap_bin_morphology_morph_diff[0]);

            if(status == -1)
            {
                printf("Parser Failed");
                return -1 ;
            }

            /* Validate the kernel */
            profiler_testCaseInfo((int8_t *)gConfig_bin_morphology_morph_diff.testCaseName,
                                  (int8_t *)gConfig_bin_morphology_morph_diff.desc,
                                            gConfig_bin_morphology_morph_diff.performanceTestcase);

            printparams(&gsTokenMap_bin_morphology_morph_diff[0],
                         (int32_t)MAX_ITEMS_TO_PARSE,
                         (uint32_t)(&gConfig_bin_morphology_morph_diff),
                             sizeof(gConfig_bin_morphology_morph_diff));

            test_binary_morphology_morph_diff(&gConfig_bin_morphology_morph_diff);

            CF_formula_add_test((gConfig_bin_morphology_morph_diff.blkWidth *
                                 gConfig_bin_morphology_morph_diff.blkHeight),
                                 NULL, NULL,  NULL, 0, NULL , 1);

        }
        else
        {
            printf("Unsupported config list command parameter at line num : %4d !\n", lineNum);
        }
    }

    CF_profile_setMode(2, 1);
    CF_profile_cycle_report(CF_PROFILE_FORMULA_RANGE, "N = num pixels");

    fclose(fp);

    return status;
}

/* ======================================================================== */
/*  End of file:  vcop_vec_bin_image_dilate_mask.c                          */
/*--------------------------------------------------------------------------*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

