/**
 *  \file     sbl_mbx_dsp1.c
 *
 *  \brief    This file contains SBL multicore mailbox binary for DSP1.
 *
 *  \details   MPU CPU0 sends message to IPU1 CPU0, IPU1 CPU1 and DSP1. Each
 *             core sends an acknowledgement after receiving message.
 *
 *  \copyright Copyright (C) 2015 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

/* ======================================================================
 *   Copyright (C) 2015 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "stdint.h"
#include "soc.h"
#include "mailbox.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int main()
{
    uint32_t msg = 0U;

    /* Wait for message from MPU CPU0 */
    while (MESSAGE_INVALID ==
           MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_2, &msg)) ;

    /* Send acknowledgement message to MPU CPU0 */
    MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_5, 0xAA55FF00);

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */
