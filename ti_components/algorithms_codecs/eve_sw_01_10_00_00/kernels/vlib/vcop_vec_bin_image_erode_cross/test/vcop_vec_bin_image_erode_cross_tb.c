/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      vcop_vec_bin_image_erode_cross                                     */
/*                                                                          */
/*  Driver file for testing Dilation with cross kernel function             */
/*                                                                          */
/*                                                                          */
/*  USAGE                                                                   */
/*      This code contains a driver program for testing the 'vcop_vec_bin_  */
/*  image_erode_cross" function by injecting it with the same data set     */
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

#ifdef __ARP32__
#include "GlobalTypes.h"
#include "baseaddress.h"
#include "sctm.h"
#endif

#include "vcop.h"
#include "eve_profile.h"
#include "configparser.h"
#include "vcop_vec_bin_image_erode_cross_config.h"

#include "vcop_vec_bin_image_erode_cross_c.h"
#if (VCOP_HOST_EMULATION)
#include "../src_kernelC/vcop_vec_bin_image_erode_cross_kernel.k"
#else
#include "vcop_vec_bin_image_erode_cross_kernel.h"
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

void fillDefaultConfig(sBin_Morphology_Erode_Cross_Config *params)
{
    strcpy((char *)params->testCaseName, "BinaryMorphology_Dilation_Cross");
    strcpy((char *)params->inImage, "");
    strcpy((char *)params->outImage, "");
    strcpy((char *)params->desc, "");
    params->performanceTestcase = 1;

    params->blkWidth       = 32;
    params->blkStride      = 32;
    params->blkHeight      = 30;

}

void test_binary_morphology_erode_cross(sBin_Morphology_Erode_Cross_Config *testcaseParams)
{
    uint32_t *dataPtr_A, *outputPtr_B, *refOutputPtr;
    uint8_t  *dataPtr_u8_A, fail;
    uint32_t  i, j;
    FILE     *fp;

    profiler_init();

    vcop_minit();
    /*-----------------------------------------------------------------
          Open Input File. If non existant, fill input with data.
          -----------------------------------------------------------------*/
    dataPtr_A = (uint32_t *)Bin_Morphology_malloc((VCOP_IBUFLA), (testcaseParams->blkStride*testcaseParams->blkHeight));

    fp = fopen((char *)testcaseParams->inImage, "rb");
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
    outputPtr_B  = (uint32_t *)Bin_Morphology_malloc(VCOP_IBUFHA, testcaseParams->blkStride*testcaseParams->blkHeight);

    refOutputPtr  = (uint32_t *)malloc(testcaseParams->blkStride*testcaseParams->blkHeight);
    memset(refOutputPtr, 0, testcaseParams->blkStride*testcaseParams->blkHeight);


    /*---------------------------------------------------------------------*/
    /*  Function call to the VCOP-C API to be tested                       */
    /*---------------------------------------------------------------------*/

    for (i = 0; i < 2; i++)
    {
        memset(outputPtr_B, 0, testcaseParams->blkStride*testcaseParams->blkHeight);

        profiler_start();

        vcop_vec_bin_image_erode_cross (dataPtr_A, outputPtr_B ,
                                         testcaseParams->blkWidth *PACKED_PIXEL_COUNT,
                                         testcaseParams->blkStride*PACKED_PIXEL_COUNT,
                                         testcaseParams->blkHeight);

        profiler_end_print(1);
        profiler_performanceParam(testcaseParams->blkWidth * testcaseParams->blkHeight);
    }

    vcop_vec_bin_image_erode_cross_cn(dataPtr_A, refOutputPtr,
                                       testcaseParams->blkWidth *PACKED_PIXEL_COUNT,
                                       testcaseParams->blkStride*PACKED_PIXEL_COUNT,
                                       testcaseParams->blkHeight);

    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*  If there is a mis-compare, print out a memory trace, else print    */
    /*  pass.                                                              */
    /*---------------------------------------------------------------------*/
    fail = 0;
    for (i = 0; i < (testcaseParams->blkHeight - 2); i++)
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
    CF_profile_init(2, "vcop_vec_bin_image_erode_cross");

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
            fillDefaultConfig(&gConfig_bin_morphology_erode_cross);

            printf("\nProcessing config file %s !\n", configFile);
            status = readparamfile(configFile, &gsTokenMap_bin_morphology_erode_cross[0]);

            if(status == -1)
            {
                printf("Parser Failed");
                return -1 ;
            }

            /* Validate the kernel */
            profiler_testCaseInfo((int8_t *)gConfig_bin_morphology_erode_cross.testCaseName,
                                  (int8_t *)gConfig_bin_morphology_erode_cross.desc,
                                            gConfig_bin_morphology_erode_cross.performanceTestcase);

            printparams(&gsTokenMap_bin_morphology_erode_cross[0],
                         (int32_t)MAX_ITEMS_TO_PARSE,
                         (uint32_t)(&gConfig_bin_morphology_erode_cross),
                             sizeof(gConfig_bin_morphology_erode_cross));

            test_binary_morphology_erode_cross(&gConfig_bin_morphology_erode_cross);

            CF_formula_add_test((gConfig_bin_morphology_erode_cross.blkWidth *
                                 gConfig_bin_morphology_erode_cross.blkHeight),
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
/*  End of file:  vcop_vec_bin_image_erode_cross.c                         */
/*--------------------------------------------------------------------------*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

