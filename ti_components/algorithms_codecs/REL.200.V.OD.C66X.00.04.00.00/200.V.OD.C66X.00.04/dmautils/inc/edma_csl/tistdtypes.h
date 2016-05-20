/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef TISTDTYPES_H_
#define TISTDTYPES_H_

#include <stdint.h>

#ifndef HOST_EMULATION
#include <stdbool.h>
#endif

typedef short           CSL_Status;
typedef unsigned int    CSL_InstNum;
typedef unsigned short  CSL_BitMask16;
typedef unsigned int    CSL_BitMask32;


#if (!(defined(xdc_target_name__) && defined(xdc_target_types__)))
/*
 * PATCH - AV BIOS SDK: Ensures that the Bool enum is defined only
 * in a non-XDC project. In an XDC project, xdc/std.h defined Bool.
 * This ensures that there is no multiple declaration compiler error.
 */
/* Changing the typedef to bool in stdbool.h so that vme and vayu eve starterwares match */

#ifndef HOST_EMULATION
    typedef bool Bool;
#else
    typedef  unsigned char BOOL;
#endif

#ifndef FALSE
#define FALSE false
#define TRUE  true
#endif

#endif /* (!(defined(xdc_target_name__) && defined(xdc_target_types__))) */


#endif /*TISTDTYPES_H_*/
