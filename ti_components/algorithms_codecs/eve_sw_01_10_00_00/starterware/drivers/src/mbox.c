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
 *  @Component    MBOX - Mailbox library component
 *  @Filename    mbox.c
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
#include "cram.h"

#pragma CHECK_MISRA ("none")
#include "baseaddress.h"
#include "mlb_cred.h"
#pragma RESET_MISRA ("required")

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
#define MBOX_ID_WIDTH           2U
#define MBOX_ID_MASK            0x3U

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

    /* Read 32-bit message in mail box */
    message = RD_BUNDLE_ARRAY_32(component, MLB__MAILBOX_MESSAGE_REGSET_0_15, MLB__MAILBOX_MESSAGE, mailBoxId, MLB__MAILBOX_MESSAGE_REGSET_0_15__ELSIZE, MLB__MAILBOX_MESSAGE__OFFSET);

    return message;
}

/* ======================== Function Separator ============================= */
void EVE_MBOX_Write( CRED_index_t  component,
                 MBOX_Id_t     mailBoxId,
                 UWORD32       writeValue )
{
    /* Write 32-bit value to mailbox */
    WR_BUNDLE_ARRAY_32(component, MLB__MAILBOX_MESSAGE_REGSET_0_15, MLB__MAILBOX_MESSAGE, mailBoxId, writeValue, MLB__MAILBOX_MESSAGE_REGSET_0_15__ELSIZE, MLB__MAILBOX_MESSAGE__OFFSET);

    return;
}

/* ======================== Function Separator ============================= */
ReturnCode_t EVE_MBOX_Reset( CRED_index_t  component )
{
    UWORD32      timeoutCounter = 0xFFFU;
    ReturnCode_t returnCode = RET_OK;

    /* set soft reset bit in Mailbox */
    WR_FIELD_32(component, MLB__MAILBOX_SYSCONFIG, MLB__MAILBOX_SYSCONFIG__SOFTRESET, (UWORD32)MLB__MAILBOX_SYSCONFIG__SOFTRESET__B1, MLB__MAILBOX_SYSCONFIG__SOFTRESET__POS);


    /* wait until reset complete and avoid infinite loop */
    while((RD_FIELD_32(component, MLB__MAILBOX_SYSCONFIG, MLB__MAILBOX_SYSCONFIG__SOFTRESET, MLB__MAILBOX_SYSCONFIG__SOFTRESET__POS)!= MLB__MAILBOX_SYSCONFIG__SOFTRESET__B0) &&
          ((timeoutCounter) != 0)                                                   )
    {
        --timeoutCounter;
    }

    /* if timeout occurred */
    if (timeoutCounter == 0)
    {
        returnCode = RET_TIMEOUT;
    }

    return returnCode;
}

/* ======================== Function Separator ============================= */

BOOL EVE_MBOX_IsFull( CRED_index_t  component,
                  MBOX_Id_t     mailBoxId )
{
    UWORD32 fullStatus;
    BOOL returnValue;

    fullStatus = RD_BUNDLE_ARRAY_32(component, MLB__MAILBOX_FIFOSTATUS_REGSET_0_15, MLB__MAILBOX_FIFOSTATUS, mailBoxId, MLB__MAILBOX_FIFOSTATUS_REGSET_0_15__ELSIZE, MLB__MAILBOX_FIFOSTATUS__OFFSET);

    /* fill in return parameter */
    if(fullStatus == 0)
    {
        returnValue = (BOOL)false;
    }
    else /* (fullStatus != 0) */
    {
        returnValue = (BOOL)true;
    }

    return returnValue;
}

/* ======================== Function Separator ============================= */
UWORD32 EVE_MBOX_GetNumMsg(
                       CRED_index_t  component,
                     MBOX_Id_t     mailBoxId
                      )
{
    UWORD32       NumMsg = 0;

    /* Get number of messages available for MailBox */
    NumMsg = RD_BUNDLE_ARRAY_32(component, MLB__MAILBOX_MSGSTATUS_REGSET_0_15, MLB__MAILBOX_MSGSTATUS, mailBoxId, MLB__MAILBOX_MSGSTATUS_REGSET_0_15__ELSIZE, MLB__MAILBOX_MSGSTATUS__OFFSET);

    return NumMsg;
} /* MBOX_GetNumMsg() */

/* ======================== Function Separator ============================= */
void EVE_MBOX_IrqEnable( CRED_index_t    component,
                   MBOX_Id_t       mailBoxId,
                     MBOX_UserId_t   userId,
                     MBOX_Int_t      enableIrq )
{
    UWORD32     irqEnableReg;
    UWORD32     irqStatusReg = 0;

    /* Get current enable status */
    irqEnableReg = RD_BUNDLE_ARRAY_32((UWORD32)component, MLB__MAILBOX_IRQ_REGSET_0_3, MLB__MAILBOX_IRQENABLE_SET, (UWORD32)userId, MLB__MAILBOX_IRQ_REGSET_0_3__ELSIZE, MLB__MAILBOX_IRQENABLE_SET__OFFSET);

    /* remove previous value for that field*/
    irqEnableReg &= ~(((UWORD32)(MBOX_ID_MASK)) << (((UWORD32)(mailBoxId))*MBOX_ID_WIDTH));

    /* if enabling the not full status bit */
    if(enableIrq != MBOX_INT_NONE)
    {
        /* calculate new enable value to write */
        UWORD32 temp = ((UWORD32)(enableIrq)) << (((UWORD32)(mailBoxId))*MBOX_ID_WIDTH); /*misra fix 12.1*/
        irqEnableReg |=  temp;

        /* Read Irq Status for specified userId */
        irqStatusReg = RD_BUNDLE_ARRAY_32(component, MLB__MAILBOX_IRQ_REGSET_0_3, MLB__MAILBOX_IRQSTATUS_RAW, userId, MLB__MAILBOX_IRQ_REGSET_0_3__ELSIZE, MLB__MAILBOX_IRQSTATUS_RAW__OFFSET) & (((UWORD32)(MBOX_ID_MASK)) << (((UWORD32)(mailBoxId))*MBOX_ID_WIDTH));

        /* Clear status interrupt */
        EVE_MBOX_IrqClearStatus(component, userId, irqStatusReg);
    }

    /* write new enable status */
    WR_BUNDLE_ARRAY_32(component, MLB__MAILBOX_IRQ_REGSET_0_3, MLB__MAILBOX_IRQENABLE_SET, userId, irqEnableReg, MLB__MAILBOX_IRQ_REGSET_0_3__ELSIZE, MLB__MAILBOX_IRQENABLE_SET__OFFSET);

    return;
}

/* ======================== Function Separator ============================= */
void EVE_MBOX_IrqDisable( CRED_index_t    component,
                      MBOX_Id_t       mailBoxId,
                      MBOX_UserId_t   userId,
                      MBOX_Int_t      disableIrq )
{
    UWORD32      irqDisableReg;

    /* calculate irq bitfields to disable */
    irqDisableReg = (UWORD32)disableIrq << ((UWORD32)mailBoxId * MBOX_ID_WIDTH);

    /* write new enable status */
    WR_BUNDLE_ARRAY_32(component, MLB__MAILBOX_IRQ_REGSET_0_3, MLB__MAILBOX_IRQENABLE_CLR, userId, irqDisableReg, MLB__MAILBOX_IRQ_REGSET_0_3__ELSIZE, MLB__MAILBOX_IRQENABLE_CLR__OFFSET);

    return;
}

/* ======================== Function Separator ============================= */
UWORD32 EVE_MBOX_IrqGetStatus( CRED_index_t    component,
         MBOX_Id_t       mailBoxId,
                           MBOX_UserId_t   userId )
{
    UWORD32      irqStatusReg;

    /* Get Irq Status for specified mailbox/User Id */
    irqStatusReg = RD_BUNDLE_ARRAY_32(component, MLB__MAILBOX_IRQ_REGSET_0_3, MLB__MAILBOX_IRQSTATUS_RAW, (UWORD32)userId, MLB__MAILBOX_IRQ_REGSET_0_3__ELSIZE, MLB__MAILBOX_IRQSTATUS_RAW__OFFSET) & (((UWORD32)(MBOX_ID_MASK)) << (((UWORD32)(mailBoxId))*MBOX_ID_WIDTH));

    return irqStatusReg;
}

/* ======================== Function Separator ============================= */
UWORD32 EVE_MBOX_IrqGetStatusMboxId( MBOX_Id_t       mailBoxId,
                                 UWORD32         irqStatus )
{
    UWORD32 mbox_irqStatus = 0;

    /* Get Irq Status for specified mailbox */
    mbox_irqStatus = ((irqStatus >> (((UWORD32)(mailBoxId))*MBOX_ID_WIDTH)) & ((UWORD32)(MBOX_ID_MASK)));

    return mbox_irqStatus;
}

/* ======================== Function Separator ============================= */
void EVE_MBOX_IrqClearStatus( CRED_index_t     component,
                          MBOX_UserId_t    userId,
                          UWORD32          irqStatus )
{
    /* clear Irq Status for specified userId */
    WR_BUNDLE_ARRAY_32(component, MLB__MAILBOX_IRQ_REGSET_0_3, MLB__MAILBOX_IRQSTATUS_CLR, userId, irqStatus, MLB__MAILBOX_IRQ_REGSET_0_3__ELSIZE, MLB__MAILBOX_IRQSTATUS_CLR__OFFSET);

    /* clear EOI register for specified userId */
    WR_REG_32(component, MLB__MAILBOX_IRQ_EOI, userId);

    return;
}
