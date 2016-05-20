/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "profile.h"

unsigned int TI_DSP_ProfileReset(TI_DSP_PrfInfo* prfInfo)
{
  volatile unsigned int temp;
  int i;
  
  if(prfInfo->prfData != NULL){
    for(i =0; i < TI_DSP_PROFILE_MAX; i++)
    {
      prfInfo->prfData[i].totalTime    = 0;
      prfInfo->prfData[i].count        = 0;
      prfInfo->prfData[i].moduleId     = -1;
      prfInfo->prfData[i].start        = 0;
    }
  }

  temp                     = TI_DSP_getTime();
  prfInfo->profileOverhead = TI_DSP_getTime() - temp; 
  prfInfo->profileDataIdx  = 0;

  return 0;
}
unsigned int TI_DSP_ProfileModule(TI_DSP_PrfInfo* prfInfo, unsigned int moduleId, unsigned int start, unsigned int acc)
{
  TI_DSP_PrfData * currPtr;
  int i;
  
  if(prfInfo->prfData == NULL)
    return 0;
  
  if(acc)
  { 
    for(i = 0; i < prfInfo->profileDataIdx; i++)
    {
      if(prfInfo->prfData[i].moduleId == moduleId)
      {
        break;
      }
    }
    currPtr = &(prfInfo->prfData[i]);
    if(i == prfInfo->profileDataIdx )
    {
     prfInfo->profileDataIdx++;
    }

  }
  else if(start) 
  {
    currPtr = &(prfInfo->prfData[prfInfo->profileDataIdx]);
    prfInfo->profileDataIdx++;
  }
  else  /* if end */
  {
    for(i = prfInfo->profileDataIdx-1; i >= 0; i--)
    {
      if(prfInfo->prfData[i].moduleId == moduleId)
      {
        currPtr = &(prfInfo->prfData[i]);
        break;
      }
    }
    if(i < 0)
    {
      return (-1);
    }

  }
  if(prfInfo->profileDataIdx >= TI_DSP_PROFILE_MAX)
  {
     return (-1);
  }
  
  currPtr->moduleId = moduleId;

  if(start)
  {
    currPtr->start        = TI_DSP_getTime();
  }
  else
  {
    currPtr->totalTime   += TI_DSP_getTime() - currPtr->start - prfInfo->profileOverhead;
    currPtr->count++;
  }
  return 1;
}
unsigned int TI_DSP_getTime()
{
#if (!HOST_EMULATION)
  return(_TSC_read());
#else
  return(0);
#endif  
}

#pragma RESET_MISRA ("required")
