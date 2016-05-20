/*==========================================================================*/		
/*      Copyright (C) 2013 Texas Instruments Incorporated.             */		
/*                      All Rights Reserved                                 */		
/*==========================================================================*/		
/**		
*  @file       example_platform.h		
*		
*  @brief      Contains platform specific parameters		
*		
*		
*/		
#ifndef EXAMPLE_PLATFORM_H		
#define EXAMPLE_PLATFORM_H		
		
#ifdef VAYU_PLATFORM		
#define INTH_INT_ID_EVE11SYNC 90		
#endif		
		
#ifdef VME_PLATFORM		
#define INTH_INT_ID_EVE11SYNC 94		
#endif		
		
#endif /*EXAMPLE_PLATFORM_H*/
