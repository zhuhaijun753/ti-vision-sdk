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
#include "hw_baseaddress_ipu.h"
#include "mailbox.h"

int main(void) {
    uint32_t msg = 'D';
    uint32_t msg_eve, msgStatus = MESSAGE_INVALID;

    // Wait for message from MPU
    while (MESSAGE_INVALID ==
           MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_0, &msg)) ;

    // Send ack message to MPU
    MailboxSendMessage(SOC_MAILBOX3_BASE, MAILBOX_QUEUE_0, 0xAA55FF00);
    return 0;
}

