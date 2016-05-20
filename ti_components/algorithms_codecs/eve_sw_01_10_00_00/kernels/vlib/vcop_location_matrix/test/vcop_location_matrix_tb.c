/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*     vcop_location_matrix_tb.c                                            */
/*                                                                          */
/*  Driver file for kernel that accepts one bins block and one mangnitude   */
/*  block and generates N bin planes each having ther magnitued for         */
/* each bins seperately                                                     */
/*                                                                          */
/*  This testbench compares the results with the expected output            */
/*  array by doing a standard "memcmp" and printing a pass/fail             */
/*  message. If it failed it prints a byte by byte trace.                   */
/*                                                                          */
/*  To build the "C" executable type:                                       */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2014 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vcop.h>
#include "eve_profile.h"
#include "configparser.h"
#include "vcop_location_matrix_cn.h"

#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define MAX_INPUT_LINE_SIZE      (300)
#define MAX_INPUT_VALUE_SIZE      (20)

#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

typedef struct
{
  char binFile[MAX_FILE_NAME_SIZE];
  char magFile[MAX_FILE_NAME_SIZE];
  char binPlanesFile[MAX_FILE_NAME_SIZE];
  int  numBins;
  int  width;
  int  height;
  int  inputDataSize;
  int  writeOutput;
  int  seedForRND;
  char inputSrc[MAX_PARAM_STRING_SIZE];
  char testCaseName[MAX_FILE_NAME_SIZE];
  char configLine[MAX_CONFIG_LINE_SIZE];
  char configParam[MAX_PARAM_STRING_SIZE];

} config_params;

config_params gParams ;

#pragma DATA_SECTION(refdataMem, "DDR_MEM");
unsigned char refdataMem[32*1024];

sTokenMapping gsTokenMap_sof[MAX_ITEMS_TO_PARSE] =
{
  {(char* )"inputSrc",                   &(gParams.inputSrc)                    , STRING, SINGLE},
  {(char* )"binFile",                    &(gParams.binFile)                     , STRING, SINGLE},
  {(char* )"magFile",                    &(gParams.magFile)                     , STRING, SINGLE},
  {(char* )"binPlanesFile",              &(gParams.binPlanesFile)               , STRING, SINGLE},
  {(char* )"numBins",                    &gParams.numBins                       , INT_32, SINGLE},
  {(char* )"width",                      &gParams.width                         , INT_32, SINGLE},
  {(char* )"height",                     &gParams.height                        , INT_32, SINGLE},
  {(char* )"inputDataSize",              &gParams.inputDataSize                 , INT_32, SINGLE},
  {(char* )"writeOutput",                &gParams.writeOutput                   , INT_32, SINGLE},
  {(char* )"seedForRND",                 &gParams.seedForRND                    , INT_32, SINGLE},
  {(char *)"testCaseName",               &gParams.testCaseName                  , STRING, SINGLE},
} ; 

#define COMPARE_REFERENCE

#if VCOP_HOST_EMULATION
#include "../src_kernelC/vcop_location_matrix_kernel.k"
#else
#include "vcop_location_matrix_kernel.h"
#endif

char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '	'))
  {
    LinePtr++;
  }
  return(LinePtr);
}
void fillDefaultConfig(config_params * params)
{
  strcpy(params->inputSrc, "RND_PTRN");
  params->writeOutput         = 0;
  params->numBins             = 6;
  params->width               = 32;
  params->height              = 32;
  params->inputDataSize       = 8;
  params->seedForRND          = 0xABDC1234;
  strcpy(params->testCaseName, " ");
}
static int writeOutputToTxtFile(unsigned short n, unsigned char numBins, unsigned char * ptr1,unsigned char * ptr2, char * fileName,unsigned char inputDataSize)
{
  int i, j;
  FILE * fp;
  unsigned char  * ptr8Bits  = (unsigned char  *)ptr1;
  unsigned short * ptr16Bits = (unsigned short *)ptr1;
  unsigned char firstHalf = (numBins+1)/2;
  fp = fopen(fileName, "w+");
  if(fp== NULL)
  {
    printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
    return (-1);
  }
  for(j = 0; j < firstHalf; j++)
  {
    for(i = 0; i < n; i++)
    {
      if(inputDataSize != 8)
      {
        fprintf(fp,"%d\n",ptr16Bits[j*n + i]);
      }
      else
      {
        fprintf(fp,"%d\n",ptr8Bits[j*n + i]);
      }
    }
  }
  ptr8Bits  = (unsigned char  *)ptr2;
  ptr16Bits = (unsigned short *)ptr2;

  for(j = 0; j < numBins/2; j++)
  {
    for(i = 0; i < n; i++)
    {
      if(inputDataSize != 8)
      {
        fprintf(fp,"%d\n",ptr16Bits[j*n + i]);
      }
      else
      {
        fprintf(fp,"%d\n",ptr8Bits[j*n + i]);
      }
    }
  }

  fclose(fp);
  return(0);
}

static int readInputFromTxtFile(unsigned char * ptr, unsigned short n, char * fileName, unsigned char inputDataSize)
{
  int k;
  FILE * fp;
  int status;
  int value;
  char inputLine[MAX_INPUT_LINE_SIZE];
  unsigned char * ptr8Bits  = ptr;
  unsigned short * ptr16Bits = (unsigned short *)ptr;

  fp = fopen(fileName, "r");
  if(fp== NULL)
  {
    printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
    return (-1);
  }
  for(k = 0; k < n; k++)
  {
    memset(inputLine, 0, MAX_INPUT_LINE_SIZE);
    status = (int)fgets(inputLine,MAX_CONFIG_LINE_SIZE,fp);
    if ((status == EOF) || (status == 0))
    {
      printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
      return(-1);
    }
    sscanf(inputLine, "%d",&value);
    if(inputDataSize != 8)
    {
      ptr16Bits[k] = value;
    }
    else
    {
      ptr8Bits[k] = value;
    }
  }
  fclose(fp);
  return(0);
}

static void CreateRandPatternU8(unsigned char *ptr, unsigned short n, unsigned char maxValue)
{
  int i;
  unsigned char val;
  for(i = 0; i < n; i++)
  {
    val = rand() & 0xFF;
    ptr[i] =  val % maxValue;
  }
}
static void CreateRandPatternU9(unsigned short *ptr, unsigned short n)
{
  int i;
  unsigned short val;
  for(i = 0; i < n; i++)
  {
    val = rand() & 0x1FF;
    ptr[i] =  val;
  }
}

int test_bench(config_params * params)
{
  unsigned char    * binBlk  ;
  unsigned char    * magBlk ;
  unsigned char    * outBlk1 ;
  unsigned char    * outBlk2 ;
  unsigned char    * ref;
  unsigned char    * binIdxArray  ;
  unsigned short numBytes;

  int fail,i;
  profiler_init();
  fail = 0;
  if(params->inputDataSize == 8)
  {
    numBytes = 1;
  }
  else
  {
    numBytes = 2;
  }

#if VCOP_HOST_EMULATION
    binBlk      = (unsigned char  *)malloc(params->width *params->height);
    magBlk      = (unsigned char  *)malloc(params->width *params->height*numBytes);
    outBlk1     = (unsigned char  *)malloc(params->width *params->height*((params->numBins+1)/2)*numBytes);
    outBlk2     = (unsigned char  *)malloc(params->width *params->height*((params->numBins+1)/2)*numBytes);
    binIdxArray = (unsigned char  *)malloc(((params->numBins+1)/2)*2);
#else
    binBlk      = (unsigned char  *)vcop_malloc(VCOP_WMEM,params->width *params->height);
    magBlk      = (unsigned char  *)vcop_malloc(VCOP_WMEM,params->width *params->height*numBytes);
    outBlk1     = (unsigned char  *)vcop_malloc(VCOP_IBUFLA,params->width *params->height*((params->numBins+1)/2)*numBytes);
    outBlk2     = (unsigned char  *)vcop_malloc(VCOP_IBUFLA,params->width *params->height*((params->numBins+1)/2)*numBytes);
    binIdxArray = (unsigned char  *)vcop_malloc(VCOP_WMEM,params->numBins);
#endif
    ref    = (unsigned char *)refdataMem;


  for(i = 0; i < (params->numBins+1)/2; i++)
  {
    binIdxArray[2*i] = i;
    binIdxArray[2*i+1] = (params->numBins+1)/2 + i;
  }
  if(strcmp(params->inputSrc, "RND_PTRN")==0)
  {
    printf("Pattern Generation Seed = %d\n", params->seedForRND);
    srand(params->seedForRND);

    CreateRandPatternU8(binBlk, params->width*params->height,params->numBins);
    if(params->inputDataSize == 8)
    {
      CreateRandPatternU8(magBlk, params->width*params->height,255);
    }
    else
    {
      CreateRandPatternU9((unsigned short *)magBlk, params->width*params->height);
    }

  }
  else if(strcmp(params->inputSrc, "TXT_FILE")==0)
  {
    readInputFromTxtFile(binBlk, params->width*params->height, params->binFile, 8);
    readInputFromTxtFile(magBlk, params->width*params->height, params->magFile, params->inputDataSize);
  }

#ifdef COMPARE_REFERENCE
  if(params->inputDataSize == 8)
  {
    vcop_vec_L_matrix_u8_Mag_cn(binBlk, magBlk, ref, params->width, params->height, params->numBins);
  }
  else
  {
    vcop_vec_L_matrix_u16_Mag_cn(binBlk, (unsigned short *)magBlk, (unsigned short *)ref, params->width, params->height, params->numBins);
  }
#endif
  profiler_start();

  if(params->inputDataSize == 8)
  {
    vcop_vec_L_matrix_u8_Mag(binBlk, magBlk, outBlk1, outBlk2, (unsigned int *)outBlk1, (unsigned int *)outBlk2, params->width, params->height, params->numBins,binIdxArray);
  }
  else
  {
    vcop_vec_L_matrix_u16_Mag(binBlk, (unsigned short *)magBlk, (unsigned short *)outBlk1, (unsigned short *)outBlk2, (unsigned int *)outBlk1, (unsigned int *)outBlk2, params->width, params->height, params->numBins,binIdxArray);
  }

  profiler_end_print(1);
  profiler_performanceParam(params->width * params->height);

#ifdef COMPARE_REFERENCE

  fail = memcmp(outBlk1,ref,(params->width *params->height*((params->numBins+1)/2)*numBytes));
  fail |= memcmp(outBlk2,(ref+params->width *params->height*((params->numBins+1)/2)*numBytes),(params->width *params->height*((params->numBins)/2)*numBytes));
  profiler_printStatus(fail);

  if(fail != 0)
  {
    for(i = 0; i < (params->width *params->height*((params->numBins+1)/2)*numBytes); i++)
    {
      printf("At %3d - outBlk1:ref = %9d:%9d ",i,outBlk1[i], ref[i]);
      if(outBlk1[i] != ref[i])
      {
        printf("*******\n");
      }
      else
      {
        printf("\n");
      }
    }
    for(i = 0; i < (params->width *params->height*((params->numBins)/2)*numBytes); i++)
    {
      printf("At %3d - outBlk1:ref = %9d:%9d ",i,outBlk2[i], ref[params->width *params->height*((params->numBins+1)/2)+i]);
      if(outBlk2[i] != ref[params->width *params->height*((params->numBins+1)/2)+i])
      {
        printf("*******\n");
      }
      else
      {
        printf("\n");
      }
    }
  }

#endif

  profiler_deinit();

  if(params->writeOutput)
  {
    writeOutputToTxtFile((params->height*params->width),params->numBins,outBlk1,outBlk2,params->binPlanesFile,params->inputDataSize);
  }

#if VCOP_HOST_EMULATION
  free(binBlk      );
  free(magBlk      );
  free(outBlk1     );
  free(outBlk2     );
  free(binIdxArray     );
#else
  vcop_free(binBlk       );
  vcop_free(magBlk       );
  vcop_free(outBlk1      );
  vcop_free(outBlk2      );
  vcop_free(binIdxArray  );
#endif
  return (0);
}

int main()
{


  FILE * fp;
  char * LinePtr;
  int status;
  int lineNum = -1;
  config_params * params;
  int config_cmd;
  char configFileName[MAX_FILE_NAME_SIZE];

  params = (config_params *)(&gParams);

  fp = fopen(CONFIG_LIST_FILE_NAME, "r");
  if(fp== NULL)
  {
    printf("Could not open config list file : %s , Runing in defult mode \n",CONFIG_LIST_FILE_NAME);
    fillDefaultConfig(params);
    test_bench(params);
    return(0);
  }

  CF_profile_init(4, "location_matrix");

  while(1)
  {
    memset(params->configLine, 0, MAX_CONFIG_LINE_SIZE);
    status = (int)fgets(params->configLine,MAX_CONFIG_LINE_SIZE,fp);
    LinePtr = params->configLine;
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
      LinePtr = moveToNextElement(params->configParam,LinePtr);
      status  = sscanf(LinePtr, "%s",configFileName);
      printf("Processing config file %s !\n", configFileName);
      fillDefaultConfig(params);
      status = readparamfile(configFileName, &gsTokenMap_sof[0]) ;
      if(status == -1)
      {
        printf("Parser Failed");
        return -1 ;
      }
      profiler_testCaseInfo((int8_t *)params->testCaseName,(int8_t *)" ",0);
      printparams(&gsTokenMap_sof[0],(int32_t)MAX_ITEMS_TO_PARSE,(uint32_t)(params),sizeof(config_params)) ;
      test_bench(params);
	    CF_formula_add_test((params->width * params->height), params->numBins, params->inputDataSize == 8 ? 1 : 2,  NULL, 0, NULL , 1);
    }
    else
    {
      printf(" Unsupported config list command parameter at line num : %4d !\n", lineNum);
    }
  }
  CF_profile_setMode(4, 1);
  CF_profile_cycle_report(CF_PROFILE_FORMULA_RANGE,"N = num pixels; M = numBins; L = Magnitude size in bytes");

  fclose(fp);
  return (0);

}
