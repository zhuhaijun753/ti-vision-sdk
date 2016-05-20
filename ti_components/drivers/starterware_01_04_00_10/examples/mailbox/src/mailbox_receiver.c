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
 * mailbox_receiver.c
 */
#include <stdint.h>
#include "mailbox.h"
#include "soc_defines.h"
#include "uartStdio.h"
#include "stdint.h"
#include "stdio.h"
#include "interrupt.h"
#include "platform.h"
#include "soc.h"
#ifndef TI814X_FAMILY_BUILD
#include "irq_xbar.h"
#endif
#include "mailbox_app.h"

#define INTERRUPT_MODE  (0)
#define POLLED_MODE     (1)

volatile uint32_t gMsg  = 0, msgStatus = MESSAGE_INVALID;
volatile uint32_t done = 1;
uint32_t          opMode;

void mailboxisr(void *handle);
void PlatformUnlockMMR(void);

#ifdef TI814X_FAMILY_BUILD
/* Receiver will run on A8 */
#define MAILBOX_IRQ_NO          (77U)
#define IRQ_XABR_CFG_REQUIRED   (0U)
#define MAILBOX_BASE_ADDRESS    SOC_SYSTEM_MAILBOX

#elif defined (TDA2XX_FAMILY_BUILD)
/* Receiver Will run on A15 */
#define MAILBOX_IRQ_NO          (26U)
#define IRQ_XABR_CFG_REQUIRED   (1U)
#define IRQ_XBAR_CPU_ID         CPU_MPUSS
#define IRQ_XBAR_INST_NO        XBAR_INST_MPU_IRQ_26
#define IRQ_XBAR_INDEX          MAILBOX2_IRQ_USER0
#define MAILBOX_BASE_ADDRESS    SOC_MAILBOX2_BASE

#elif defined (TDA3XX_FAMILY_BUILD)
/* Receiver will run on M4 */
#define MAILBOX_IRQ_NO          (50U)
#define IRQ_XABR_CFG_REQUIRED   (1U)
#define IRQ_XBAR_CPU_ID         CPU_IPU1
#define IRQ_XBAR_INST_NO        XBAR_INST_IPU1_IRQ_50
#define IRQ_XBAR_INDEX          MAILBOX2_IRQ_USER0
#define MAILBOX_BASE_ADDRESS    SOC_MAILBOX2_BASE
#endif
#define MAILBOX_USER            (0U)

int main(void)
{
#if IRQ_XABR_CFG_REQUIRED
    irq_xbar_ret_type_t status = invalid_mpu_id;
#endif

    PlatformUartConsoleSetPinMux();
    UARTStdioInit();
    UARTPuts("\nReceiver: Mailbox Application", -1);
    UARTPuts(
        "\nReceiver: Enter Operating mode\n0 - For Interrupt Mode\
         \n1 - For polled Mode\n$> ", -1);
    opMode = UARTGetNum();

    if ((opMode != POLLED_MODE) && (opMode != INTERRUPT_MODE))
    {
        UARTPuts("\nReceiver: Invalid Input. Defaulting to Interrupt Mode", -1);
        opMode = INTERRUPT_MODE;
    }

    if (opMode == POLLED_MODE)
    {
        UARTPuts("\nReceiver:  Polled Mode", -1);
    }
    else
    {
        UARTPuts("\nReceiver: Interrupt Mode", -1);

#if IRQ_XABR_CFG_REQUIRED
        /*Unlock the Crossbar register */
        PlatformUnlockMMR();

        status =
            IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                           IRQ_XBAR_CPU_ID,
                           IRQ_XBAR_INST_NO,
                           IRQ_XBAR_INDEX);
        if (status == irq_xbar_success)
        {
            UARTPuts("\nReceiver: XBar is sucessfully connected", -1);
        }
        else
        {
            UARTPuts("\nReceiver: XBar not able to connect", -1);
        }
#endif

        /* Register Mailbox interrupt for A15 */
        Intc_Init();
        Intc_IntEnable(0);
        Intc_IntRegister(MAILBOX_IRQ_NO, (IntrFuncPtr) mailboxisr, NULL);
        Intc_IntPrioritySet(MAILBOX_IRQ_NO, 1, 0);
        Intc_SystemEnable(MAILBOX_IRQ_NO);

        MailboxEnableNewMsgInt(MAILBOX_BASE_ADDRESS, MAILBOX_USER,
                               MAILBOX_QUEUE_0);
    }

    while (done)
    {
        if (opMode == POLLED_MODE)
        {
            while (msgStatus == MESSAGE_INVALID)
            {
                msgStatus =
                    MailboxGetMessage(MAILBOX_BASE_ADDRESS, MAILBOX_QUEUE_0,
                                      (uint32_t *) &gMsg);
            }
        }
        if (msgStatus == MESSAGE_VALID)
        {
            if (gMsg == MAILBOX_APP_A8_MSG)
            {
                UARTPuts("\nReceiver: A8 Core is up", -1);
            }
            if (gMsg == MAILBOX_APP_A15_MSG)
            {
                UARTPuts("\nReceiver: A15 Core is up", -1);
            }
            if (gMsg == MAILBOX_APP_DSP_MSG)
            {
                UARTPuts("\nReceiver: DSP Core is up", -1);
            }
            if (gMsg == MAILBOX_APP_M3_MSG)
            {
                UARTPuts("\nReceiver: M3 Core is up", -1);
            }
            if (gMsg == MAILBOX_APP_M4_MSG)
            {
                UARTPuts("\nReceiver: M4 Core is up", -1);
            }
            gMsg       = 0;
            msgStatus = MESSAGE_INVALID;
        }
    }
    return 0;
}

void mailboxisr(void *handle)
{
    msgStatus = MailboxGetMessage(MAILBOX_BASE_ADDRESS, MAILBOX_QUEUE_0,
                                  (uint32_t *) &gMsg);

    /* clear mlb intr */
    MailboxClrNewMsgStatus(MAILBOX_BASE_ADDRESS, MAILBOX_USER, MAILBOX_QUEUE_0);
}

