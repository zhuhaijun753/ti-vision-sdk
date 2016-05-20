/* $Header: <fileName>.c    <lastVersionNumber>        <lastEditionDate>
 * =============================================================================
 *
 *            TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION
 *
 *  Property of Texas Instruments
 *  For Unrestricted Internal Use Only
 *  Unauthorized reproduction and/or distribution is strictly prohibited.
 *  This product is protected under copyright law and trade secret law
 *  as an unpublished work.
 *  Created 2007, (C) Copyright 2007 Texas Instruments.  All rights reserved.
 */
/**
 *  @Component		MBOX - Mailbox library component
 *  @Filename		mbox.c
 *  @Description    The mailbox library component offers basic mailbox
 *                  functionality that can be used to transmit 32-bit messages
 *                  between CPUs using the OMAP4.0 Mailbox
 *
 *//*======================================================================== */

/* =============================================================================
 * STANDARD INCLUDE FILES
 * =============================================================================
 */

/* =============================================================================
 * PROJECT SPECIFIC INCLUDE FILES
 * =============================================================================
 */
#include "GlobalTypes.h"
#include "baseaddress.h"
#include "mbox.h"

/* =============================================================================
 * GLOBAL VARIABLES DECLARATIONS
 * =============================================================================
 */

/* =============================================================================
 * LOCAL TYPES AND DEFINITIONS
 * =============================================================================
 */
/* width/mask in bits of MBOX Id */
#define MBOX_ID_WIDTH           2
#define MBOX_ID_MASK            0x3

/****************************************************************/

/* =============================================================================
 * LOCAL VARIABLES DECLARATIONS
 * =============================================================================
 */

/* =============================================================================
 * LOCAL FUNCTIONS PROTOTYPES
 * =============================================================================
 */

/* =============================================================================
 * FUNCTIONS
 * =============================================================================
 */

UWORD32 EVE_MBOX_Read( CRED_index_t  component,
	               MBOX_Id_t     mailBoxId)
{
    UWORD32 message = 0;
    return message;
}

/* ======================== Function Separator ============================= */
void EVE_MBOX_Write( CRED_index_t  component,
                 MBOX_Id_t     mailBoxId,
                 UWORD32       writeValue )
{
    return;
}

/* ======================== Function Separator ============================= */
ReturnCode_t EVE_MBOX_Reset( CRED_index_t  component )
{    
    ReturnCode_t returnCode = RET_OK;

    return returnCode;
}

/* ======================== Function Separator ============================= */

BOOL EVE_MBOX_IsFull( CRED_index_t  component,
                  MBOX_Id_t     mailBoxId )
{
    BOOL returnValue = true;

    return returnValue;
}

/* ======================== Function Separator ============================= */
UWORD32 EVE_MBOX_GetNumMsg(
                       CRED_index_t  component,
    	               MBOX_Id_t     mailBoxId
                      )
{
    UWORD32       NumMsg = 0;
    return NumMsg;
} /* MBOX_GetNumMsg() */

/* ======================== Function Separator ============================= */
void EVE_MBOX_IrqEnable( CRED_index_t    component,
	                 MBOX_Id_t       mailBoxId,
                     MBOX_UserId_t   userId,
                     MBOX_Int_t      enableIrq )
{

    return;
}

/* ======================== Function Separator ============================= */
void EVE_MBOX_IrqDisable( CRED_index_t    component,
                      MBOX_Id_t       mailBoxId,
                      MBOX_UserId_t   userId,
                      MBOX_Int_t      disableIrq )
{

    return;
}

/* ======================== Function Separator ============================= */
UWORD32 EVE_MBOX_IrqGetStatus( CRED_index_t    component,
			   MBOX_Id_t       mailBoxId,
                           MBOX_UserId_t   userId )
{
    UWORD32      irqStatusReg = 0;

    return irqStatusReg;
}

/* ======================== Function Separator ============================= */
UWORD32 EVE_MBOX_IrqGetStatusMboxId( MBOX_Id_t       mailBoxId,
                                 UWORD32         irqStatus )
{
    UWORD32 mbox_irqStatus = 0;

    return mbox_irqStatus;
}

/* ======================== Function Separator ============================= */
void EVE_MBOX_IrqClearStatus( CRED_index_t     component,
                          MBOX_UserId_t    userId,
                          UWORD32          irqStatus )
{
    return;
}
