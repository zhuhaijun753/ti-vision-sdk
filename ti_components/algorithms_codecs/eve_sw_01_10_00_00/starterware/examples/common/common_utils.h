/*==========================================================================*/
/*      Copyright (C) 2003 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/**
*  @file       common_functions.h
*
*  @brief      Contains common macros used by examples. These macros are 
*				temporarily added to provided some of the functionality 
*				which is currently not present in eve starterware. These will
*				be removed later.
*
*/
#ifndef __COMMON_UTILS_H
#define __COMMON_UTILS_H

#include "GlobalTypes.h"

/*-------------------------------------------------------------------------*//**
 * @DEFINITION WR_MEM_32_VOLATILE
 *
 * @BRIEF      Write memory volatile - 32bit; accessing the memory address
 *             This is ok for ARM cores and C64, not ok for C55
 *//*------------------------------------------------------------------------ */
#ifndef WR_MEM_32_VOLATILE
  #define WR_MEM_32_VOLATILE(addr, data) ( *((REG_UWORD32 *)(addr)) = (UWORD32)(data) )
#endif

/*-------------------------------------------------------------------------*//**
 * @DEFINITION RD_MEM_32_VOLATILE
 *
 * @BRIEF      Read memory volatile - 32bit; accessing the memory address
 *             This is ok for ARM cores and C64, not ok for C55
 *//*------------------------------------------------------------------------ */
#ifndef RD_MEM_32_VOLATILE
  #define RD_MEM_32_VOLATILE(addr)     ( (UWORD32)( *((REG_UWORD32 *)(addr)) ) )
#endif

/*-------------------------------------------------------------------------*//**
 * @DEFINITION MASKWR_REG_32 
 *
 * @BRIEF      Write masked value to register; takes component address, 
 *             register offset, the mask and value to write as parameters.
 *             The macro reads value first and sets only bits matching the mask,
 *             leaving the rest intact.
 *//*------------------------------------------------------------------------ */
#ifndef MASKWR_REG_32
#define MASKWR_REG_32(REG_ADDR, MASK, VAL) \
  WR_MEM_32_VOLATILE(REG_ADDR, \
    ( RD_MEM_32_VOLATILE(REG_ADDR) & (~(MASK))) | ( (UWORD32)(VAL)&(UWORD32)(MASK) ) )
#endif	

#endif /*__COMMON_FUNCTIONS_H*/
