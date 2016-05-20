/**
 *  \file     sbl_mbx_mpu_cpu0.c
 *
 *  \brief    This file contains SBL multi-core mailbox binary for MPU CPU0.
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
#include "uartStdio.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

#define MPU_CPU0_MAILBOX_MSG                           ((uint32_t) 0xFF33BB00U)

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
    uint32_t msg          = 0U;
    uint32_t ipu1Cpu0Flag = 0U;
    uint32_t ipu1Cpu1Flag = 0U;
    uint32_t dsp1Flag     = 0U;

    /* Configure UART1 */
    UARTStdioInit();

    UARTPuts("\n Multi-core Mailbox Application: MPU Core0 Master core \n ",
             -1);

    /* Send message to IPU1 CPU0(MBX2_Q0) */
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_0,
                              MPU_CPU0_MAILBOX_MSG)) ;

    /* Send message to IPU1 CPU1(MBX2_Q1) */
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_1,
                              MPU_CPU0_MAILBOX_MSG)) ;

    /* Send message to DSP1(MBX2_Q2) */
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_2,
                              MPU_CPU0_MAILBOX_MSG)) ;

    while ((ipu1Cpu0Flag != 1U) ||
           (ipu1Cpu1Flag != 1U) ||
           (dsp1Flag != 1U))
    {
        /* Read message from IPU1 CPU0 */
        if (MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_3, &msg))
        {
            UARTPuts(" \n IPU1 CPU0 booted-up successfully \n", -1);
            ipu1Cpu0Flag = 1U;
        }

        /* Read message from IPU1 CPU1 */
        if (MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_4, &msg))
        {
            UARTPuts("\n IPU1 CPU1 booted-up successfully \n", -1);
            ipu1Cpu1Flag = 1U;
        }

        /* Read message from DSP1 */
        if (MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_5, &msg))
        {
            UARTPuts("\n DSP1 booted-up successfully \n", -1);
            dsp1Flag = 1U;
        }
    }
    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */
