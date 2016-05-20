/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/** @file pyramid_lk_sof_score_utility.c
*
*  @brief  This file contains coode to calculate score for SOF using ground truth file
*
*
*  @date   Dec 2013
*
*  Description
*     This file contains coode to calculate score for SOF using ground truth file
*/

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <vcop.h>

#if (VCOP_HOST_EMULATION)
#include "pyramid_lk_sof_config.h"
#include "pyramid_lk_sof_tb.h"
#include "configparser.h"

char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '	')||(LinePtr[0] == ','))
  {
    LinePtr++;
  }
  return(LinePtr);
}
void fillDefaultConfig(config_params * params)
{
  params->maxNumKeyPoints = 0;
  params->numLevels    = 4; 
  params->maxItersLK   = 10; 
  params->imWidth      = 640;
  params->imHeight     = 320;
  params->minErrValue  = 0;
}

int SOFDemo_ComputeStats(char *fileRef, char *fileCur, char *fileStats)
{
  FILE *fpCur, *fpStats;
  int ret ;
  int totalPts = 0;
  int rightPts = 0 ;
  
  sSOFFlow (*flowGT) [MAX_WIDTH];

  int x, y ;
  float u, v ;
  unsigned int error= 0;
  int totalPoints = 0 ;
  float accuracy;

#ifndef CREATE_FIXED_MOTION
  FILE *fpRef;
  fpRef = fopen(fileRef, "r");
  if(fpRef == NULL)
  {
    printf("Not able to open Ref flow vector file - %s\n",fileRef );
    return -1 ;
  }
#endif

  fpCur = fopen(fileCur, "r");
  if(fpCur == NULL)
  {
    printf("Not able to open Cur flow vector file - %s\n",fileCur );
    return -1 ;
  }

  fpStats = fopen(fileStats, "w");
  if(fpStats == NULL)
  {
    printf("Not able to open Out stats file - %s\n",fileStats );
    return -1 ;
  }

  /*---------------------------------------------------------------*/
  /* Main aim of this memory zeroing is to Set the valid flag = 0  */
  /*---------------------------------------------------------------*/
  flowGT   = (sSOFFlow (*)[MAX_WIDTH])malloc(MAX_HEIGHT*MAX_WIDTH* sizeof(sSOFFlow));
  memset(flowGT, 0, sizeof(sSOFFlow)*MAX_HEIGHT*MAX_WIDTH);

#ifndef CREATE_FIXED_MOTION
  while (!feof(fpRef))
  {
    ret = fscanf(fpRef,"%d,%d,%f,%f\n",&x,&y,&u,&v);
    if (ret != -1)
    {
      if(x <0 || x> (MAX_WIDTH-1) || y <0 || y> (MAX_HEIGHT-1))
      {
        printf("Ref flow vector file - %s is not Valid\n",fileRef );
        break;
      }
      flowGT[y][x].u = u ;
      flowGT[y][x].v = v ;
      flowGT[y][x].valid = 1 ;
    }
  }
#endif

  fprintf(fpStats, "XPos,YPos,u[calculated],v[calculated],u[GT],v[GT], Disatnce\n");
  while (!feof(fpCur))
  {
    ret = fscanf(fpCur,"%d,%d,%f,%f",&x,&y,&u,&v);
    if (ret != -1)
    {
      if(x <0 || x> (MAX_WIDTH-1) || y <0 || y> (MAX_HEIGHT-1))
      {
        printf("Flow vector file - %s is not Valid\n",fileCur );
        break;
      }
#ifdef CREATE_FIXED_MOTION
      flowGT[y][x].valid = 1 ;
      flowGT[y][x].u = MOTION_u ;
      flowGT[y][x].v = MOTION_v ;
#endif
      if(flowGT[y][x].valid == 1 )
      {
        double distance;
        distance = 
          sqrt((flowGT[y][x].u - u)*(flowGT[y][x].u - u) + (flowGT[y][x].v - v)*(flowGT[y][x].v - v));
        fprintf(fpStats, "%d,%d,%f,%f,%f,%f,%f\n",x,y,u,v,flowGT[y][x].u, flowGT[y][x].v,distance);
        if(distance <= MAX_PIXEL_DIFF)
        {
          rightPts++;
        }
        totalPts++;
      }
    }
  }
  if(totalPts !=0)
  {
    accuracy = (float)rightPts/totalPts;
    fprintf(fpStats,"****************** Distance Accurcay = %f %%  *************\n",accuracy*100);
    printf("****************** Distance Accurcay = %f %%  for %d points*************\n",accuracy*100,totalPts);
  }
  fclose(fpRef);
  fclose(fpCur);
  fclose(fpStats);
  free(flowGT );
  return 0 ;
}

int main(int argc, char *argv[])
{
  int32_t         status = 0;
  FILE           *fp;
  int8_t         *LinePtr;
  int32_t         lineNum = -1;
  config_params  *params;
  int32_t         config_cmd;
  int8_t          configFileName[MAX_FILE_NAME_SIZE];

  params = (config_params *)(&gParams);

  if (argc > 1)
  {
    strcpy((char *)configFileName, argv[1]) ;
  }
  else
  {
    strcpy((char *)configFileName,CONFIG_LIST_FILE_NAME);
  }

  fp = fopen((const char *)configFileName , "r");
  if(fp== NULL)
  {
    printf("Could not open config list file : %s , Exiting...\n",CONFIG_LIST_FILE_NAME);
    return(status);
  }

  while(1)
  {
    memset(params->configLine, 0, MAX_CONFIG_LINE_SIZE);
    status = (int)fgets(params->configLine,MAX_CONFIG_LINE_SIZE,fp);
    LinePtr = (int8_t *)params->configLine;
    if ((status == EOF) || (status == 0))
      break;
    lineNum++;
    sscanf((const char *)LinePtr, "%d",&config_cmd);
    sscanf((const char *)LinePtr, "%s",params->configParam);
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
      LinePtr = (int8_t *)moveToNextElement(params->configParam,(char *)LinePtr);
      status  = sscanf((const char *)LinePtr, "%s",configFileName);
      printf("Processing config file %s !\n", configFileName);
      fillDefaultConfig(params);
      status = readparamfile((char *)configFileName, gsTokenMap_sof) ;
      if(status == -1)
      {
        printf("Parser Failed");
        return -1 ;
      }     

      /* Validate the applet */
      SOFDemo_ComputeStats(params->gtFileName,params->outFileName,params->statsFileName);
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
  fclose(fp);

  return status;
}
#endif
