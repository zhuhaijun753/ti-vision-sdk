/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      vcop_median3x3_tb                                                   */
/*                                                                          */
/*  Driver file for testing kernel for 3x3 median filtering of 8-bit        */
/*  gray-scale images.                                                      */
/*                                                                          */
/*  USAGE                                                                   */
/*      This code contains a driver program for testing the vcop_           */
/*  median3x3 kernel.                                                       */
/*                                                                          */
/*  This testbench then compares the results with the expected output       */
/*  array by doing a standard "memcmp" function and printing a pass/fail    */
/*  message. If it fails it prints a byte by byte trace.                    */
/*                                                                          */
/* ======================================================================== */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vcop.h"
#include "eve_profile.h"
#include "configparser.h"
#include "vcop_median3x3_config.h"

/* ------------------------------------------------------------------------ */
/*  Include prototype for the "C" reference of 3x3 Median filter function   */
/* ------------------------------------------------------------------------ */
#include "vcop_median3x3_cn.h"

#if VCOP_HOST_EMULATION
  #include "../src_kernelC/vcop_median3x3_kernel.k" // kernel source
#else
  #include "vcop_median3x3_kernel.h"
#endif

//#define __DEBUG

#define IMG_WIDTH  (64)
#define IMG_PITCH  (64)
#define IMG_HEIGHT (64)

#pragma DATA_SECTION(IN, "Adata");
uint8_t IN[IMG_HEIGHT*IMG_PITCH] = {0};

#pragma DATA_SECTION(SCRATCH1, "Bdata");
uint8_t SCRATCH1[3*IMG_HEIGHT*IMG_WIDTH] = {0};

#pragma DATA_SECTION(SCRATCH2, "Cdata");
uint8_t SCRATCH2[3*IMG_HEIGHT*IMG_WIDTH] = {0};

#pragma DATA_SECTION(OUT_MED, "Bdata");
uint8_t OUT_MED[IMG_HEIGHT*IMG_WIDTH] = {0};

#pragma DATA_SECTION(REF_MED, "Eoutdata");
uint8_t REF_MED[IMG_HEIGHT*IMG_WIDTH] = {0};

void createRndPattern(uint8_t *img, uint16_t height, uint32_t width,
                      uint32_t pitch, uint16_t max)
{
  int32_t i, j;

  for(i = 0; i < height; i++) {
    for(j = 0; j < width; j++) {
      img[i*pitch + j] = (uint8_t)rand()%(max + 1);
    }
  }
}

void fillDefaultConfig(sMedian3x3_Config * params)
{
  strcpy(params->inImg, "");
  strcpy(params->outImg, "");
  params->blockWidth  = 32;
  params->blockHeight = 32;
  params->dataType    = 0;

  params->randSeed    = 0;
  params->numIter     = 1;
}


void print_2d_buf_u8(uint8_t    *buf,
                     uint16_t    buf_height,
                     uint16_t    buf_width,
                     uint16_t    buf_pitch,
                     const char *str)
{
#ifdef __DEBUG
    int32_t i,j;

    printf("\n%s:\n", str);
    for(i = 0; i < buf_height; i++) {
        for(j = 0; j < buf_width; j++) {
            printf("%4d, ", buf[i*buf_pitch + j]);
        }
        printf("\n");
    }
#endif
}


int32_t main(int32_t argc, char *argv[])
{
  int32_t iter, fail = 0, status = 0;
  uint32_t i, j;
  uint32_t seed;
  FILE *fp_in = NULL, *fp_out = NULL;
  char configFile[FILE_NAME_SIZE];
  char fileName[FILE_NAME_SIZE];

  if (argc > 1)
  {
    strcpy(configFile, argv[1]) ;
  }
  else
  {
    strcpy(configFile,"../testvecs/config/median3x3.cfg");
  }

  fillDefaultConfig(&gConfig_median3x3);
  fail = readparamfile(configFile, &gsTokenMap_median3x3[0]) ;
  if(fail == -1)
  {
    printf("Parser Failed. Running default config.\n");
  }

  profiler_init();

  printf("Testing 3x3 median filtering:\n");

#if !(VCOP_HOST_EMULATION)
  VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                      IBUFHA_SYST, IBUFLA_SYST);

  if(gConfig_median3x3.dataType == 0) {
    vcop_median3x3_uchar_init(IN, OUT_MED, SCRATCH1, SCRATCH2,
        gConfig_median3x3.blockWidth, gConfig_median3x3.blockHeight,
        __pblock_vcop_median3x3_uchar);
  }
  else {
    vcop_median3x3_char_init((char*)IN, (char*)OUT_MED,
        (char*)SCRATCH1, (char*)SCRATCH2,
        gConfig_median3x3.blockWidth, gConfig_median3x3.blockHeight,
        __pblock_vcop_median3x3_char);
  }
#endif

  for (iter = 0; iter < gConfig_median3x3.numIter; iter++)
  {
    printf("Iteration %d \nBlock Size = %dx%d\n", iter, gConfig_median3x3.blockWidth,
           gConfig_median3x3.blockHeight);
    fail = 0;

    if(strcmp(gConfig_median3x3.inImg, "")) {
      sprintf(fileName, "../testvecs/input/%s", gConfig_median3x3.inImg);
      fp_in = fopen((const char *)fileName, "r");
      if(fp_in == NULL) {
        printf("Failed to open input file: %s.\n", gConfig_median3x3.inImg);
        return -1;
      }

      fread(IN, gConfig_median3x3.blockWidth*gConfig_median3x3.blockHeight, 1, fp_in);
      fclose(fp_in);
    }
    else {
      seed = (gConfig_median3x3.randSeed == 0) ? _tsc_gettime() : gConfig_median3x3.randSeed;
      srand(seed);
      printf("Pattern Generation Seed = %d\n", seed);
      createRndPattern(IN, gConfig_median3x3.blockHeight,
                       gConfig_median3x3.blockWidth,
                       gConfig_median3x3.blockWidth, 0xFF);
    }

    print_2d_buf_u8(IN, gConfig_median3x3.blockHeight,
        gConfig_median3x3.blockWidth,
        gConfig_median3x3.blockWidth, "Input image");

    profiler_start();

  #if VCOP_HOST_EMULATION
    if(gConfig_median3x3.dataType == 0) {
      vcop_median3x3_uchar(IN, OUT_MED, SCRATCH1, SCRATCH2,
        gConfig_median3x3.blockWidth, gConfig_median3x3.blockHeight);
    }
    else {
      vcop_median3x3_char(IN, OUT_MED, SCRATCH1, SCRATCH2,
        gConfig_median3x3.blockWidth, gConfig_median3x3.blockHeight);
    }
  #else
    VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                    IBUFHA_VCOP, IBUFLA_VCOP);

    /*---------------------------------------------------------------------*/
    /*  Function call to the VCOP-C API to be tested                       */
    /*---------------------------------------------------------------------*/
    if(gConfig_median3x3.dataType == 0) {
      vcop_median3x3_uchar_vloops(__pblock_vcop_median3x3_uchar);
    }
    else {
      vcop_median3x3_char_vloops(__pblock_vcop_median3x3_char);
    }
    _vcop_vloop_done();

    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                        IBUFHA_SYST, IBUFLA_SYST);
  #endif

    profiler_end();

    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*---------------------------------------------------------------------*/
    if(gConfig_median3x3.dataType == 0) {
        vcop_median3x3_uchar_cn(IN, REF_MED, SCRATCH1, SCRATCH2,
          gConfig_median3x3.blockWidth,
          gConfig_median3x3.blockWidth,
          gConfig_median3x3.blockWidth,
          gConfig_median3x3.blockHeight);
      }
      else {
        vcop_median3x3_char_cn((signed char *)IN, (signed char *)REF_MED,
          (signed char*)SCRATCH1, (signed char*)SCRATCH2,
          gConfig_median3x3.blockWidth,
          gConfig_median3x3.blockWidth,
          gConfig_median3x3.blockWidth,
          gConfig_median3x3.blockHeight);
      }

    print_2d_buf_u8(OUT_MED, gConfig_median3x3.blockHeight - 2,
        gConfig_median3x3.blockWidth - 2,
        gConfig_median3x3.blockWidth - 2, "Median Filter output");

    /* Compare against reference */
    fail = 0;
    for(i = 0; i < gConfig_median3x3.blockHeight - 2; i++) {
      for(j = 0; j < gConfig_median3x3.blockWidth - 2; j++) {
        if(OUT_MED[i*(gConfig_median3x3.blockWidth - 2) + j] != REF_MED[i*gConfig_median3x3.blockWidth + j]) {
          printf("\nOutput mismatch at (%d, %d), Output = %d, Expected = %d\n",
                 i, j, OUT_MED[i*(gConfig_median3x3.blockWidth - 2) + j],
                 REF_MED[i*gConfig_median3x3.blockWidth + j]);
          fail = 1;
        }
      }
    }

    sprintf(fileName, "../testvecs/output/%s", gConfig_median3x3.outImg);
    fp_out = fopen((const char*)fileName, "w");
    if(fp_out != NULL) {
      for(i = 0; i < gConfig_median3x3.blockHeight - 2; i++) {
        fwrite(OUT_MED + i*(gConfig_median3x3.blockWidth - 2), gConfig_median3x3.blockWidth - 2, 1, fp_out);
      }
      fclose(fp_out);
    }

    printf(fail ? "FAIL\n":"PASS\n");
    status |= fail;
  }

  profiler_deinit();

  printf(status ? "Median 3x3: FAIL\n":"Median 3x3: PASS\n");

  return (status);
}
