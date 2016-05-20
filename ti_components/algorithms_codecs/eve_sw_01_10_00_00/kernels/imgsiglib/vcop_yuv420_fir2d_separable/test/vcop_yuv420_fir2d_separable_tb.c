/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/* ======================================================================== */
/*                                                                          */
/*  NAME                                                                    */
/*      vcop_yuv420_fir2d_separable_tb.c                                  */
/*                                                                          */
/*  Driver file for testing YUV420 separable Filter 2D                        */
/*                                                                          */
/*  USAGE                                                                   */
/*      This code contains a driver program for testing the 'vcop_yuv420_fir2d_separable"*/
/*  function by injecting it with the a random data  */
/*  set and comparing the output against the natural C function output.     */
/*                                                                          */
/*  This testbench then compares the results with the expected output       */
/*  array by doing a standard "memcmp" function and printing a pass/fail    */
/*  message. If it failed it prints a byte by byte trace.                   */
/*                                                                          */
/* ======================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <vcop.h>
#include "eve_profile.h"
#include "configparser.h"
#include "vcop_yuv420_fir2d_separable_config.h"
#include <math.h>


/* ------------------------------------------------------------------------ */
/*  Include prototypes for "C" implementation of Gradient XY and magnitude kernel  */
/*  function.                                                               */
/* ------------------------------------------------------------------------ */
#include "vcop_yuv420_fir2d_separable_cn.h"


#if VCOP_HOST_EMULATION
#include "../src_kernelC/vcop_yuv420_fir2d_separable_kernel.k"
#else
#include "../inc/vcop_yuv420_fir2d_separable_kernel.h"
#endif

//#define __DEBUG
#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")
#define ALIGN_SIMD(a)   (((a) + VCOP_SIMD_WIDTH-1) & ~(VCOP_SIMD_WIDTH-1))
#define ALIGN_2SIMD(a)   (((a) + 2*VCOP_SIMD_WIDTH-1) & ~(2*VCOP_SIMD_WIDTH-1))

#define ALIGNED_WIDTH ALIGN_SIMD(MAX_WIDTH)

void fillDefaultConfig(sYUV420_fir2d_separable_Config * params)
{
  strcpy(params->inputData,"");
  params->width             = 34;
  params->height            = 34;
  params->pitch             = 34;
  params->numCoefficients   = 3;
  params->horzCoefficients[0] = 1;
  params->horzCoefficients[1] = 2;
  params->horzCoefficients[2] = 1;

  params->vertCoefficients[0] = 1;
  params->vertCoefficients[1] = 2;
  params->vertCoefficients[2] = 1;

  params->roundBits         = 4;
  params->randSeed          = 0;
  params->numIter           = 1;
}

//#define FIXEDPATTERN
///////////////////////////////////////
// Makes a 32x32 random
///////////////////////////////////////
static void CreatePattern(uint8_t * p, uint16_t imgWidth, uint16_t imgHeight, uint16_t imgPitch, uint8_t maxVal)
{
  int32_t i, j;

  for ( j = 0 ; j < imgWidth; j++)
  {
    for (i = 0; i < imgHeight; i++)
    {
#ifdef FIXEDPATTERN
      p[i + j * imgPitch] = (i * j)% maxVal;

#else
      p[i + j * imgPitch] = rand() % maxVal;
#endif
    }
  }


}


int32_t yuv420Fir2dSeparableTest(sYUV420_fir2d_separable_Config * testcaseParams)
{
  int32_t iter, status = 0;
  uint32_t seed;
  FILE *fp_in = NULL;

  uint8_t * inputDataY = NULL;
  int8_t * horzCoeffs = NULL;
  int8_t * vertCoeffs = NULL;
  int16_t * scratchBuffer = NULL;
  uint8_t * outPtrY =NULL;

  uint8_t * outPtrYRef =NULL;

  uint16_t computeWidth;
  uint16_t computeHeight;
  profiler_init();
  vcop_minit();

  computeWidth = (testcaseParams->width - (testcaseParams->numCoefficients - 1 ));
  computeHeight = (testcaseParams->height - (testcaseParams->numCoefficients - 1 ));


#if VCOP_HOST_EMULATION
  /* Multiplication by two because it stores x and y coordinate in packed format*/
  inputDataY = (uint8_t *) malloc(testcaseParams->width *
                                  testcaseParams->height);

  horzCoeffs   = (int8_t *) malloc( testcaseParams->numCoefficients);

  vertCoeffs   = (int8_t *) malloc( testcaseParams->numCoefficients);

  scratchBuffer = (int16_t *) malloc( testcaseParams->width * testcaseParams->height * sizeof(int16_t));

  outPtrY = (uint8_t *) malloc(computeWidth * computeHeight * sizeof(uint8_t));

#else
     /* vcop_malloc doesnt allow to allocate full 16k of image buffer LA. Hence using
     hard coded address for it edgeMap*/
  inputDataY = (uint8_t *) vcop_malloc(VCOP_IBUFLA, testcaseParams->width *
                                  testcaseParams->height);

  horzCoeffs     = (int8_t *) vcop_malloc(VCOP_WMEM, testcaseParams->numCoefficients);

  vertCoeffs   = (int8_t *) vcop_malloc(VCOP_WMEM, testcaseParams->numCoefficients);


  scratchBuffer = (int16_t *) vcop_malloc(VCOP_IBUFHA, testcaseParams->width * testcaseParams->height * sizeof(int16_t));

  outPtrY = (uint8_t *) vcop_malloc(VCOP_IBUFLA, computeWidth * computeHeight * sizeof(uint8_t));


#endif


  outPtrYRef= (uint8_t *) malloc(testcaseParams->width *
                                  testcaseParams->height);


  for (iter = 0; iter < testcaseParams->numIter; iter++)
  {
    printf("Iteration %d\n", iter);

    if(strcmp(testcaseParams->inputData, ""))
    {
      printf("File Test\n");
      fp_in = fopen((const char *)testcaseParams->inputData, "rb");

      if(fp_in == NULL)
      {
          printf("Failed to open input file: %s.\n", testcaseParams->inputData);
          return -1;
      }

      fread(inputDataY, testcaseParams->width * testcaseParams->height,
                        1, fp_in);


      fclose(fp_in);
    }
    else
    {
      /* Generate input data */
      seed = (testcaseParams->randSeed == 0) ? _tsc_gettime() : testcaseParams->randSeed;
      srand(seed);
      printf("Random pattern test: Seed = %d\n", seed);
      CreatePattern(inputDataY,
                    testcaseParams->width,
                    testcaseParams->height,
                    testcaseParams->pitch,
                    255);
    }


    memcpy( horzCoeffs, testcaseParams->horzCoefficients, testcaseParams->numCoefficients);
    memcpy( vertCoeffs, testcaseParams->vertCoefficients, testcaseParams->numCoefficients);

    profiler_start();
    vcop_yuv420_fir2d_separable_y(inputDataY,
                          scratchBuffer,
                          (char *)horzCoeffs,
                          (char *)vertCoeffs,
                          computeWidth,
                          testcaseParams->pitch,
                          computeHeight,
                          testcaseParams->numCoefficients,
                          outPtrY,
                          testcaseParams->roundBits);
    profiler_end_print(1);

    vcop_yuv420_fir2d_separable_y_cn(inputDataY,
                              horzCoeffs,
                              vertCoeffs,
                              computeWidth,
                              testcaseParams->pitch,
                              computeHeight,
                              testcaseParams->numCoefficients,
                              outPtrYRef,
                              testcaseParams->roundBits);


    status = memcmp(outPtrY, outPtrYRef, computeWidth * computeHeight);

    if ( status != 0 )
    {
      printf("NATC and Kernel C output not matching\n");
      break;
    }


  }
  profiler_printStatus(status);

  printf(status ? "yuv420Fir2dSeparableTest: FAIL\n" : "yuv420Fir2dSeparableTest: PASS\n");

#if VCOP_HOST_EMULATION
  if ( inputDataY)
  {
    free(inputDataY);
  }

  if ( scratchBuffer)
  {
    free(scratchBuffer);
  }
  if ( horzCoeffs)
  {
    free(horzCoeffs);
  }
  if ( vertCoeffs)
  {
    free(vertCoeffs);
  }
  if ( outPtrY)
  {
    free(outPtrY);
  }

#endif
  if( outPtrYRef )
  {
    free(outPtrYRef);
  }

  return (status);
}

char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '	')||(LinePtr[0] == ','))
  {
    LinePtr++;
  }
  return(LinePtr);
}

int32_t main(int32_t argc, char *argv[])
{
  int status = 0;
  char configFile[FILE_NAME_SIZE]={0};
  char configLine[MAX_CONFIG_LINE_SIZE];
  char configParam[MAX_PARAM_STRING_SIZE];
  int8_t         *LinePtr;
  FILE * fp;
  int32_t         lineNum = -1;
  int32_t         config_cmd;

  if (argc > 1)
  {
    strcpy(configFile, argv[1]) ;
  }
  else
  {
    strcpy(configFile,CONFIG_LIST_FILE_NAME);
  }

  fp = fopen((const char *)configFile , "r");
  if(fp== NULL)
  {
    printf("Could not open config list file : %s \n",CONFIG_LIST_FILE_NAME);
    return(status);
  }
  CF_profile_init(3, "vcop_yuv420_fir2d_separable_y");

  while ( 1 )
  {
    memset(configLine, 0, MAX_CONFIG_LINE_SIZE);
    status = (int)fgets(configLine,MAX_CONFIG_LINE_SIZE,fp);
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
      printf("\n Processing config file %s !\n", configFile);
      status = readparamfile(configFile, &gsTokenMap_yuv420_fir2d_separable[0]);
      if(status == -1)
      {
        printf("Parser Failed");
        return -1 ;
      }

      /* Validate the kernel  */
      profiler_testCaseInfo((int8_t *)gConfig_yuv420_fir2d_separable.testCaseName, (int8_t *)" ", 0);
      printparams(&gsTokenMap_yuv420_fir2d_separable[0], (int32_t)MAX_ITEMS_TO_PARSE,
                  (uint32_t)(&gConfig_yuv420_fir2d_separable),sizeof(gConfig_yuv420_fir2d_separable)) ;
      status = yuv420Fir2dSeparableTest(&gConfig_yuv420_fir2d_separable);

      if(status == -1)
      {
        return status;
      }
    }
    else
    {
      printf(" Unsupported config list command parameter at line num : %4d !\n", lineNum);
    }

  }
  CF_profile_setMode(3, 1);
  CF_profile_cycle_report(CF_PROFILE_FORMULA_RANGE,"N = num pixels; M = numFilterTaps");

  fclose(fp);

  return status;
}

