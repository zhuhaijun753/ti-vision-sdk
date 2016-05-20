/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       integral_image_test.h
 *
 *  @brief      Example file that shows the usage of integral image applet
 */
#ifndef INTEGRAL_IMAGE_TI_TEST_H
#define INTEGRAL_IMAGE_TI_TEST_H
     
#pragma CHECK_MISRA ("none")
#include <stdint.h>
#include <stdio.h> 
#pragma RESET_MISRA ("required")
#include <xdais_types.h>


#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define MAX_INPUT_LINE_SIZE      (300)
#define MAX_INPUT_VALUE_SIZE     (20)

#define CONFIG_LIST_FILE_NAME    ("..\\testvecs\\config\\config_list.txt")

typedef struct 
{
  char inFile      [MAX_FILE_NAME_SIZE];
  char outFile     [MAX_FILE_NAME_SIZE];
  int  imWidth       ;
  int  imHeight      ;
  char configLine[MAX_CONFIG_LINE_SIZE];
  char configParam[MAX_PARAM_STRING_SIZE];
  uint8_t testCaseName[MAX_FILE_NAME_SIZE];
  uint8_t testCaseDesc[MAX_FILE_NAME_SIZE];
  uint8_t performanceTestcase ;

} config_params;

#define PRINT_ERRORE_MSG()  printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)
  
#endif
