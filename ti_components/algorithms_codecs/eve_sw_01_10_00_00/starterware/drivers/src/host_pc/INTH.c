/* $Header: <fileName>.c    <lastVersionNumber>    	<lastEditionDate>
 * =============================================================================
 *
 *            TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION
 *
 *  Property of Texas Instruments
 *  For Unrestricted Internal Use Only
 *  Unauthorized reproduction and/or distribution is strictly
 *  prohibited.
 *  This product is protected under copyright law and trade secret law
 *  as an unpublished work.
 *  Created 2008, (C) Copyright 2008 Texas Instruments.  All rights
 *  reserved.
 */
/**
 *  @Component    INTH - Interrupt (IRQ) handler library component
 *
 *  @Filename     INTH.c
 *
 *  @Description  Interrupt handling utilities
 *
 *//*======================================================================== */

/* ============================================================================
* STANDARD INCLUDE FILES
* =============================================================================
*/

/* ============================================================================
* PROJECT SPECIFIC INCLUDE FILES
* =============================================================================
*/
#include "GlobalTypes.h"
#include "INTH.h"
/* ============================================================================
* FUNCTIONS
* =============================================================================
*/

ReturnCode_t EVE_INTH_InterruptSetup( const UWORD8               intVector,
                                  const UWORD32       intHandler,
                                  const INTH_InterruptKind_t intKind,
                                  const INTH_Priority_t      intPriority)
{
    ReturnCode_t returnCode = RET_OK;
	return returnCode;

} /* EVE_INTH_InterruptSetup() */


ReturnCode_t EVE_INTH_InterruptEnable( const UWORD8 intVector)
{
   ReturnCode_t returnCode = RET_OK;

   return returnCode;

} /* EVE_INTH_InterruptEnable() */

ReturnCode_t EVE_INTH_InterruptDisable( const UWORD8 intVector)
{

    ReturnCode_t returnCode = RET_OK;

    return returnCode;

} /* EVE_INTH_InterruptDisable() */


void EVE_INTH_LockEnable(void)
{
	return;
}