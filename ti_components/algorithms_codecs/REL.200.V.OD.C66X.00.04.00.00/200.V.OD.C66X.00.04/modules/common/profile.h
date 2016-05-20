/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#ifndef _PROFILE_H_
#define _PROFILE_H_

typedef enum 
{
  TI_DSP_PROFILE_MODULE0    = 0,
  TI_DSP_PROFILE_MODULE1    = 1,
  TI_DSP_PROFILE_MODULE2    = 2,
  TI_DSP_PROFILE_MODULE3    = 3,
  TI_DSP_PROFILE_MODULE4    = 4,
  TI_DSP_PROFILE_MODULE5    = 5,
  TI_DSP_PROFILE_MODULE6    = 6,
  TI_DSP_PROFILE_MODULE7    = 7,
  TI_DSP_PROFILE_MODULE8    = 8,
  TI_DSP_PROFILE_MODULE9    = 9,
  TI_DSP_PROFILE_MODULE10   = 10,
  TI_DSP_PROFILE_MODULE11   = 11,
  TI_DSP_PROFILE_MODULE12   = 12,
  TI_DSP_PROFILE_MODULE13   = 13,
  TI_DSP_PROFILE_MODULE14   = 14,
  TI_DSP_PROFILE_MODULE15   = 15,
  TI_DSP_PROFILE_MAX        = 16
} TI_DSP_ProfileModuleID;

typedef enum 
{
  TI_DSP_PROFILE_END      = 0,
  TI_DSP_PROFILE_START    = 1
} TI_DSP_ProfileFlag;

typedef enum 
{                 
  TI_DSP_PROFILE_INDIVIDUAL     = 0,
  TI_DSP_PROFILE_CUMULATIVE     = 1
  
} TI_DSP_ProfileMode;

typedef struct
{
  short      moduleId;
  short      count;
  unsigned int  totalTime;
  unsigned int  start;
  
} TI_DSP_PrfData;

typedef struct
{
  TI_DSP_PrfData* prfData;
  unsigned int        profileOverhead;
  unsigned int        profileDataIdx;
} TI_DSP_PrfInfo;

unsigned int TI_DSP_ProfileReset(TI_DSP_PrfInfo* prfInfo);
unsigned int TI_DSP_ProfileModule(TI_DSP_PrfInfo* prfInfo, unsigned int moduleId, unsigned int start, unsigned int acc);
unsigned int TI_DSP_getTime();

#endif

