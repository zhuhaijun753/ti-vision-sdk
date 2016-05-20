/*
 * TI Booting and Flashing Utilities
 *
 * Header for the debug routines.
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

#ifndef DEBUG_H_
#define DEBUG_H_

#include "tistdtypes.h"

// Prevent C++ name mangling
#ifdef __cplusplus
extern far "c" {
#endif

/***********************************************************
* Global Macro Declarations                                *
***********************************************************/

/***********************************************************
* Global Typedef declarations                              *
***********************************************************/

/***********************************************************
* Global Function Declarations                             *
***********************************************************/

Uint32 DEBUG_printString(String s);
Uint32 DEBUG_printHexInt(Uint32 i);
Uint32 DEBUG_readString(String s);
Uint32 DEBUG_readChar(Char *c);
Uint32 DEBUG_readHexInt(Uint32 *i);


/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
}
#endif

#endif /* DEBUG_H_ */

/* --------------------------------------------------------------------------
    HISTORY
		v1.00  -  DJA  -  07-Nov-2007
 	        Initial release
 ----------------------------------------------------------------------------- */
