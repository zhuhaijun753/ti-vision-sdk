/* ======================================================================
 *   Copyright (C) 2013 Texas Instruments Incorporated
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
/*
 * main.c
 */
#include "stdint.h"
#include "soc.h"
#include "mailbox.h"
#include "uartStdio.h"

#define MPU_MBX_MAGIC_STR  0xFF33BB00

int main(void) {
    uint32_t msg = 0, msgStatus = MESSAGE_INVALID;
    uint32_t IPU1_CPU0_Flag = 0;
    uint32_t IPU1_CPU1_Flag = 0;
    uint32_t IPU2_CPU0_Flag = 0;
    uint32_t IPU2_CPU1_Flag = 0;
    uint32_t DSP1_Flag      = 0;
    uint32_t DSP2_Flag      = 0;
    uint32_t EVE1_Flag      = 0;
    uint32_t EVE2_Flag      = 0;
    uint32_t EVE3_Flag      = 0;
    uint32_t EVE4_Flag      = 0;

    UARTStdioInit();
    UARTPuts("\nMulticore Mailbox app - MPU-Core0 Master core \n ", -1);

    // Send message to IPU1_CPU0(MBX2_Q0)
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_0,
                              MPU_MBX_MAGIC_STR)) ;

    // Send message to IPU1_CPU1(MBX2_Q1)
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_1,
                              MPU_MBX_MAGIC_STR)) ;

    // Send message to IPU2_CPU0(MBX2_Q2)
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_2,
                              MPU_MBX_MAGIC_STR)) ;

    // Send message to IPU2_CPU1(MBX2_Q3)
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_3,
                              MPU_MBX_MAGIC_STR)) ;

    // Send message to DSP1(MBX2_Q4)
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_4,
                              MPU_MBX_MAGIC_STR)) ;

    // Send message to DSP2(MBX2_Q5)
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_5,
                              MPU_MBX_MAGIC_STR)) ;

    // Send message to EVE1(MBX2_Q6)
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_6,
                              MPU_MBX_MAGIC_STR)) ;

    // Send message to EVE2(MBX2_Q7)
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_7,
                              MPU_MBX_MAGIC_STR)) ;

    // Send message to EVE3(MBX2_Q8)
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_8,
                              MPU_MBX_MAGIC_STR)) ;

    // Send message to EVE4(MBX2_Q9)
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_9,
                              MPU_MBX_MAGIC_STR)) ;

    while (1)
    {
        // Read message from IPU1_CPU0
        if (!IPU1_CPU0_Flag && MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX3_BASE, MAILBOX_QUEUE_0, &msg))
        {
            UARTPuts("IPU1_CPU0 boot-up sucessfully", -1);
            IPU1_CPU0_Flag = 1;
        }

        // Read message from IPU1_CPU1
        if (!IPU1_CPU1_Flag && MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX4_BASE, MAILBOX_QUEUE_0, &msg))
        {
            UARTPuts("IPU1_CPU1 boot-up sucessfully", -1);
            IPU1_CPU1_Flag = 1;
        }

        // Read message from IPU2_CPU0

        if (!IPU2_CPU0_Flag && MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX5_BASE, MAILBOX_QUEUE_0, &msg))
        {
            UARTPuts("IPU2_CPU0 boot-up sucessfully", -1);
            IPU2_CPU0_Flag = 1;
        }

        // Read message from IPU2_CPU1
        if (!IPU2_CPU1_Flag && MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX6_BASE, MAILBOX_QUEUE_0, &msg))
        {
            UARTPuts("IPU2_CPU1 boot-up sucessfully", -1);
            IPU2_CPU1_Flag = 1;
        }

        // Read message from DSP1
        if (!DSP1_Flag && MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX7_BASE, MAILBOX_QUEUE_0, &msg))
        {
            UARTPuts("DSP1 boot-up sucessfully", -1);
            DSP1_Flag = 1;
        }

        // Read message from DSP2
        if (!DSP2_Flag && MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX8_BASE, MAILBOX_QUEUE_0, &msg))
        {
            UARTPuts("DSP2 boot-up sucessfully", -1);
            DSP2_Flag = 1;
        }

        // Read message from EVE1
        if (!EVE1_Flag && MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX9_BASE, MAILBOX_QUEUE_0, &msg))
        {
            UARTPuts("EVE1 boot-up sucessfully", -1);
            EVE1_Flag = 1;
        }

        // Read message from EVE2
        if (!EVE2_Flag && MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX10_BASE, MAILBOX_QUEUE_0, &msg))
        {
            UARTPuts("EVE2 boot-up sucessfully", -1);
            EVE2_Flag = 1;
        }

        // Read message from EVE3
        if (!EVE3_Flag && MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX11_BASE, MAILBOX_QUEUE_0, &msg))
        {
            UARTPuts("EVE3 boot-up sucessfully", -1);
            EVE3_Flag = 1;
        }

        // Read message from EVE4
        if (!EVE4_Flag && MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX12_BASE, MAILBOX_QUEUE_0, &msg))
        {
            UARTPuts("EVE4 boot-up sucessfully", -1);
            EVE4_Flag = 1;
        }
    }
    return 0;
}

