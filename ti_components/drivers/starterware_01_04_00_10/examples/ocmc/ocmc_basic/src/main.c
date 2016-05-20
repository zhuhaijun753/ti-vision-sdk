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
#include "stdint.h"
#include <stdio.h>
#include "ocmc_ecc_l1.h"
#include "ocmc_ecc_l2.h"
#include "mailbox.h"
#include "uartStdio.h"

static void uart_val_print(uint32_t val, char *mess)
{
    UARTPuts(mess, -1);
    UARTPutHexNum(val);
}

int main(void)
{
    uint32_t  virtStartAddr;
    uint32_t  val = 0;
    uint32_t *read_addr;
    uint32_t  msgfromSender;

    UARTStdioInit();

    while (1)
    {
        /* Send virtual start address cmd*/
        val = 0x2233;

        MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_1, val);
        while (MESSAGE_INVALID ==
               (MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_0,
                                  &virtStartAddr))) ;

        /*Wait for message from M4 for 1st slice*/
        while (MESSAGE_INVALID ==
               (MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_0,
                                  &msgfromSender))) ;
#if defined (TDA2XX_FAMILY_BUILD)
        uart_val_print(virtStartAddr, "\nVirtual start addr A15 = ");
#elif defined (TDA3XX_FAMILY_BUILD)
        uart_val_print(virtStartAddr, "\nVirtual start addr C66x = ");
#endif
        read_addr = (uint32_t *) (virtStartAddr);
        UARTPuts("\n 1st slice = ", -1);
        val = *read_addr++;
        uart_val_print(val, " ");

        val = *read_addr++;
        uart_val_print(val, " ");

        val = *read_addr++;
        uart_val_print(val, " ");

        val = *read_addr++;
        uart_val_print(val, " ");

        /* Read 1st slice complete - send message */
        MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_1, val);

        /*Wait for message from M4 for 2nd slice*/
        while (MESSAGE_INVALID ==
               (MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_0,
                                  &msgfromSender))) ;
        UARTPuts("\n 2nd slice = ", -1);
        val = *read_addr++;
        uart_val_print(val, " ");

        val = *read_addr++;
        uart_val_print(val, " ");

        val = *read_addr++;
        uart_val_print(val, " ");

        val = *read_addr++;
        uart_val_print(val, " ");

        /* Read 2nd slice complete - send message */
        MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_1, val);

        /*Wait for message from M4 for 3rd slice*/
        while (MESSAGE_INVALID ==
               (MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_0,
                                  &msgfromSender))) ;
        UARTPuts("\n 3rd slice = ", -1);
        val = *read_addr++;
        uart_val_print(val, " ");

        val = *read_addr++;
        uart_val_print(val, " ");

        val = *read_addr++;
        uart_val_print(val, " ");

        val = *read_addr++;
        uart_val_print(val, " ");

        /* Read 3rd slice complete - send message */
        MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_1, val);
    }
}

