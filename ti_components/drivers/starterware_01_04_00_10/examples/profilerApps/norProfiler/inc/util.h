/*
 * TI Booting and Flashing Utilities
 *
 * Header for UTIL module.
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

#ifndef UTIL_H_
#define UTIL_H_

#include "tistdtypes.h"

// Prevent C++ name mangling
#ifdef __cplusplus
extern far "c" {
#endif

/***********************************************************
* Global Macro Declarations                                *
***********************************************************/

#define ENDIAN_SWAP(a) (((a&0xFF)<<24)|((a&0xFF0000)>>8)|((a&0xFF00)<<8)|((a&0xFF000000)>>24))


/***********************************************************
* Global Typedef declarations                              *
***********************************************************/


/***********************************************************
* Global Function Declarations                             *
***********************************************************/

void *UTIL_allocMem (Uint32 size);
void *UTIL_callocMem(Uint32 size);
void *UTIL_getCurrMemPtr(void);
void UTIL_setCurrMemPtr(void *value);
void UTIL_waitLoop(Uint32 loopcnt);
void UTIL_waitLoopAccurate (Uint32 loopcnt);
Uint32 UTIL_calcCRC32(Uint32* lutCRC, Uint8 *data, Uint32 size, Uint32 currCRC);
void UTIL_buildCRC32Table(Uint32* lutCRC, Uint32 poly);
Uint16 UTIL_calcCRC16(Uint16* lutCRC, Uint8 *data, Uint32 size, Uint16 currCRC);
void UTIL_buildCRC16Table(Uint16* lutCRC, Uint16 poly);




/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
}
#endif

#endif /* UTIL_H_ */

/* --------------------------------------------------------------------------
  HISTORY
	  v1.00  -  DJA  -  07-Nov-2007
      Initial release
 ----------------------------------------------------------------------------- */

