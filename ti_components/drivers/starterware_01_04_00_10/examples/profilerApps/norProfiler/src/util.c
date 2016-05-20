/*
 * TI Booting and Flashing Utilities
 *
 * Utility functions for flashing applications.
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as 
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/* --------------------------------------------------------------------------
  AUTHOR      : Daniel Allred
 --------------------------------------------------------------------------- */

// General type include
#include "tistdtypes.h"

// This module's header file
#include "util.h"

// Device specific CSL
#include "device.h"

/************************************************************
* Explicit External Declarations                            *
************************************************************/




/************************************************************
* Local Macro Declarations                                  *
************************************************************/


/************************************************************
* Local Typedef Declarations                                *
************************************************************/


/************************************************************
* Local Function Declarations                               *
************************************************************/

/************************************************************
* Local Variable Definitions                                *
************************************************************/


/************************************************************
* Global Variable Definitions                               *
************************************************************/

// Global memory allocation pointer
static VUint32 currMemPtr;


/************************************************************
* Global Function Definitions                               *
************************************************************/

// DDR Memory allocation routines (for storing large data)
void *UTIL_getCurrMemPtr(void)
{
  return ((void *)currMemPtr);
}

// Setup for an adhoc heap
void UTIL_setCurrMemPtr(void *value)
{
  currMemPtr = (VUint32)value;
}

// Allocate memory from the ad-hoc heap
void *UTIL_allocMem(Uint32 size)
{
  void *cPtr;
  Uint32 size_temp;

  // Ensure word boundaries
  size_temp = ((size + 4) >> 2 ) << 2;
  
  if((currMemPtr + size_temp) > (DEVICE_DDR2_RAM_END))
  {
    return NULL;
  }

  cPtr = (void *) (DEVICE_DDR2_START_ADDR + currMemPtr);
  currMemPtr += size_temp;

  return cPtr;
}

// Allocate memory from the ad-hoc heap
void *UTIL_callocMem(Uint32 size)
{
  void *ptr;
  Uint8 *cPtr;
  Uint32 i;

  // Alloc the memory
  ptr = UTIL_allocMem(size);

  if(NULL != ptr)
  {
      // Clear the memory
      for (i=0,cPtr = ptr; i<size; i++)
      {
        cPtr[i] = 0x00;
      }
  }

  return ptr;
}

// Simple wait loop - comes in handy.
void UTIL_waitLoop(Uint32 loopcnt)
{
  Uint32 i;
  for (i = 0; i<loopcnt; i++)
  {
    asm("   NOP");
  }
}

// Accurate n = ((t us * f MHz) - 5) / 1.65 
void UTIL_waitLoopAccurate (Uint32 loopcnt)
{
#if defined(_TMS320C6X)
//  asm ("      SUB     B15, 8, B15     ");                 // Done by compiler 
//  asm ("      STW     A4, *+B15[1]    ");                 // Done by compiler 
  asm ("      STW     B0, *+B15[2]    ");
  asm ("      SUB     A4, 24, A4      ");          // Total cycles taken by this function, with n = 0, including clocks taken to jump to this function 
  asm ("      CMPGT   A4, 0, B0       ");
  asm ("loop:                         ");
  asm (" [B0] B       loop            ");
  asm (" [B0] SUB     A4, 6, A4       ");          // Cycles taken by loop 
  asm ("      CMPGT   A4, 0, B0       ");
  asm ("      NOP     3               ");
  asm ("      LDW     *+B15[2], B0    ");
//  asm ("      B       B3              ");                 // Done by compiler 
//  asm ("      ADD     B15, 8, B15     ");                 // Done by compiler 
//  asm ("      NOP     4     
#elif defined(_TMS320C5XX) || defined(__TMS320C55X__)
  UTIL_waitLoop(loopcnt);
#elif defined(_TMS320C28X)
  UTIL_waitLoop(loopcnt);
#elif (defined(__TMS470__) || defined(__GNUC__))
  UTIL_waitLoop(loopcnt);
#endif
}

/***********************************************************
* End file                                                 *
***********************************************************/

/* --------------------------------------------------------------------------
    HISTORY
        v1.00  -  DJA  -  16-Aug-2007
           Initial release 
 ----------------------------------------------------------------------------- */



