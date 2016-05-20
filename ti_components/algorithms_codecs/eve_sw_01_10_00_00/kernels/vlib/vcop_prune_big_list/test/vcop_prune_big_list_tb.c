/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/* ======================================================================== */
/*                                                                          */
/*  NAME                                                                    */
/*      vcop_prune_big_list_tb                                              */
/*                                                                          */
/*  Driver file for testing pruning of a big list                           */
/*                                                                          */
/*  USAGE                                                                   */
/*      This code contains a driver program for testing the 'vcop_prune_    */
/*  big_list" function by injecting it with the a random data set and       */
/*  comparing the output against the natural C function output.             */
/*                                                                          */
/*  This testbench then compares the results with the expected output       */
/*  array by doing a standard "memcmp" function and printing a pass/fail    */
/*  message. If it failed it prints a byte by byte trace.                   */
/*                                                                          */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "vcop.h"
#include "eve_profile.h"
#include "configparser.h"
#include "vcop_prune_big_list_config.h"

#if VCOP_HOST_EMULATION
  #include "../src_kernelC/vcop_prune_big_list_kernel.k" // kernel source
#else
  #include "vcop_prune_big_list_kernel.h"
#endif

/* ------------------------------------------------------------------------ */
/*  Include prototype of "C" implementation of prune big list function.     */
/* ------------------------------------------------------------------------ */
#include "vcop_prune_big_list_cn.h"

//#define __DEBUG

#define MAX_LIST_LENGTH  (4032)
#define MAX_BEST_N       (2048)

#pragma DATA_SECTION(IN, "Adata");
uint32_t IN[MAX_LIST_LENGTH] = {0};

#pragma DATA_SECTION(IN_IDX, "Bdata");
uint32_t IN_IDX[MAX_LIST_LENGTH + 2*VCOP_SIMD_WIDTH] = {0};

#pragma DATA_SECTION(OUT, "Cdata");
uint32_t OUT[MAX_BEST_N] = {0};

#pragma DATA_SECTION(NONBESTNOUT_SIZE, "Cdata");
uint32_t NONBESTNOUT_SIZE[8] = {0};

#pragma DATA_SECTION(OUT_REF, "DDR_MEM");
uint32_t OUT_REF[MAX_BEST_N] = {0};

#pragma DATA_SECTION(NONBESTNOUT_SIZE_REF, "DDR_MEM");
uint32_t NONBESTNOUT_SIZE_REF[1] = {0};


void createRndPattern32(uint32_t *img, uint16_t length, uint32_t mask)
{
    int32_t i;

    for(i = 0; i < length; i++) {
        img[i] = rand()&mask;
    }
}


int32_t test_prune_big_list()
{
    int32_t i, iter, fail, status = 0;
    uint32_t seed;

    profiler_init();

    printf("Number of elements in pruned list = %d\n", gConfig_prune_big_list.bestN);

#if !(VCOP_HOST_EMULATION)
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                        IBUFHA_SYST, IBUFLA_SYST);

    vcop_prune_big_list_init(IN, (uint16_t *)IN_IDX, IN_IDX, OUT,NONBESTNOUT_SIZE, gConfig_prune_big_list.threshold,
                             gConfig_prune_big_list.bestN, __pblock_vcop_prune_big_list);
#endif


    for (iter = 0; iter < gConfig_prune_big_list.numIter; iter++)
    {
        printf("Iteration %d\n", iter);
        fail = 0;

        seed = (gConfig_prune_big_list.randSeed == 0) ? _tsc_gettime() : gConfig_prune_big_list.randSeed;
        srand(seed);
        printf("Pattern Generation Seed = %d\n", seed);
        createRndPattern32(IN, gConfig_prune_big_list.listLength, 0xFFFFFFFF);

        // IN_IDX list - upper 16-bits is payload data. Lower 16-bit is the index.
        createRndPattern32(IN_IDX, gConfig_prune_big_list.bestN,
                           (0xFFFF0000 + gConfig_prune_big_list.bestN - 1));
        /* Check the predication load by setting the payload non-zero*/
        for(i = 200; i < gConfig_prune_big_list.bestN; i++)
        {
          IN_IDX[i] = 0xFFFF0001;
        }        
#ifdef __DEBUG
        printf("\nInput List:\n");
        for(i = 0; i < gConfig_prune_big_list.listLength; i++) {
            printf("%3d ", IN[i]);
        }
        printf("\n");

        printf("\nInput Index List:\n");
        for(i = 0; i < gConfig_prune_big_list.listLength; i++) {
            printf("%3d ", IN_IDX[i]);
        }
        printf("\n");
#endif

        profiler_start();

#if VCOP_HOST_EMULATION
        vcop_prune_big_list(IN, (uint16_t *)IN_IDX, IN_IDX, OUT, NONBESTNOUT_SIZE, 
                                 gConfig_prune_big_list.threshold, gConfig_prune_big_list.bestN);
#else
        VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                        IBUFHA_VCOP, IBUFLA_VCOP);

        /*---------------------------------------------------------------------*/
        /*  Function call to the VCOP-C API to be tested                       */
        /*---------------------------------------------------------------------*/
        vcop_prune_big_list_vloops(__pblock_vcop_prune_big_list);
        _vcop_vloop_done();

        VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                            IBUFHA_SYST, IBUFLA_SYST);
#endif

        profiler_end();

        /*---------------------------------------------------------------------*/
        /*  Compare the results of output arrays with expected output arrays.  */
        /*---------------------------------------------------------------------*/
        vcop_prune_big_list_cn(IN, (uint16_t *)IN_IDX, IN_IDX, OUT_REF,
                               NONBESTNOUT_SIZE_REF, gConfig_prune_big_list.threshold, 
                               gConfig_prune_big_list.bestN);
        fail = memcmp(OUT, OUT_REF, gConfig_prune_big_list.bestN);

        if(fail != 0) {
            for(i = 0; i < gConfig_prune_big_list.bestN; i++) {
                if(OUT[i] != OUT_REF[i]) {
                    printf("\nOutput mismatch at %d, Output = %d, Expected = %d\n",
                           i, OUT[i], OUT_REF[i]);
                }
            }
        }
        
        fail = memcmp(NONBESTNOUT_SIZE, NONBESTNOUT_SIZE_REF, 1);
        if(fail != 0)
        {
          printf("\n Non bestN count mis match, Output = %d, Expected: %d\n", NONBESTNOUT_SIZE[0], NONBESTNOUT_SIZE_REF[0]);
        }

#ifdef __DEBUG
        printf("\nOutput List:\n");
        for(i = 0; i < gConfig_prune_big_list.bestN; i++) {
            printf("%3d ",OUT[i]);
        }
        printf("\n");

        printf("\nReference Output Frame:\n");
        for(i = 0; i < gConfig_prune_big_list.bestN; i++) {
            printf("%3d ",OUT_REF[i]);
        }
        printf("\n");
#endif

        printf(fail ? "FAIL\n":"PASS\n");
        status |= fail;
    }

    profiler_deinit();

    printf(status ? "test_prune_big_list: FAIL\n":"test_prune_big_list: PASS\n");

    return (status);
}


int32_t main(int32_t argc, char *argv[])
{
    int32_t status = 0;
    char configFile[FILE_NAME_SIZE];

    if (argc > 1)
    {
        strcpy(configFile, argv[1]) ;
    }
    else
    {
#if VCOP_HOST_EMULATION
        strcpy(configFile,"../testvecs/config/prune_big_list.cfg");
#else
        strcpy(configFile,"../testvecs/config/prune_big_list.cfg");
#endif
    }

    status = readparamfile(configFile, &gsTokenMap_prune_big_list[0]) ;
    if(status == -1)
    {
        printf("Parser Failed");
        return -1 ;
    }

    /* Validate the Kernel */
    printf ("\nPrune Big List Test Bench: Validating Kernel\n");
    status = test_prune_big_list();

    return status;
}
