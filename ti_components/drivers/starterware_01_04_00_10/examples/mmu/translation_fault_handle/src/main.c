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
#include "mmu.h"
#include "soc.h"
#include "mailbox.h"
#include "soc_defines.h"
#include "platform.h"
#include "uartStdio.h"
#include "interrupt.h"
#include "hw_dsp1_prm.h"
#include <common/stw_types.h>
#include "hw_dsp1_cm_core_aon.h"
#include <common/stw_dataTypes.h>
#if defined (BUILD_M4)
#include "irq_xbar.h"
#endif

#if defined (BUILD_M4)
#define MMU_FAULT_INT_NUM       (33)
#elif defined (BUILD_A15)
#define MMU_FAULT_INT_NUM       (28)
#endif

/*DSP Entry Point*/
#define DSP_ENTRY_POINT (0x8B000000)

#define DSP1BOOTADDR            (SOC_CTRL_MODULE_CORE_BASE + 0x55C)
#define DSP1BOOTADDRVALUE       (SOC_DSP1_L2_SRAM_BASE - 0x40000000)

void dspMmuFaultIsr();
int32_t DSP1SystemReset();
void DSP1BringUp(uint32_t EntryPoint);

volatile uint8_t mmuFault      = 0;
volatile int8_t  waitForMmuInt = 1;

int main()
{
    volatile int8_t keepMainActive = 0;
    volatile int8_t done           = 1;

    PlatformUartConsoleSetPinMux();

#if defined (BUILD_M4)
    /*Unlock the Crossbar register */
    PlatformUnlockMMR();

    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1, 11,
                   DSP1_IRQ_MMU0);
#endif

    UARTStdioInit();
#if defined (BUILD_A15)
    UARTPuts("\n\nFrom A15", -1);
#elif defined (BUILD_M4)
    UARTPuts("\n\nFrom M4", -1);
#endif
    UARTPuts("\nDSP MMU fault test", -1);

    Intc_Init();
    Intc_IntEnable(0);

    Intc_IntRegister(MMU_FAULT_INT_NUM, (IntrFuncPtr) dspMmuFaultIsr, NULL);
    Intc_IntPrioritySet(MMU_FAULT_INT_NUM, 1, 0);
    Intc_SystemEnable(MMU_FAULT_INT_NUM);

    while (waitForMmuInt)
    {
        keepMainActive++;
    }

    while (done) ;

    return 0;
}

void dspMmuFaultIsr()
{
    uint32_t msgToDsp = (uint32_t) 'A';

    waitForMmuInt = 0;
#if defined (BUILD_A15)
    UARTPuts("\n\nFrom A15 ISR", -1);
#elif defined (BUILD_M4)
    UARTPuts("\n\nFrom M4 ISR", -1);
#endif
    UARTPuts("\nMMU fault occurred", -1);

    /*Reset DSP1 Core*/
    DSP1SystemReset();

    MMUIrqClearStatus(SOC_DSP1_MMU0CFG_BASE, MMU_INT_All);
#if defined (BUILD_A15)
    UARTPuts("\nDSP accessed fault address configured in DSP MMU from A15", -1);
#elif defined (BUILD_M4)
    UARTPuts("\nDSP accessed fault address configured in DSP MMU from M4", -1);
#endif
    MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_0, msgToDsp);

    /*Release DSP cores out of reset*/
    DSP1BringUp(DSP_ENTRY_POINT);
    UARTPuts("\nDSP is out of reset", -1);
}

int32_t DSP1SystemReset()
{
    uint32_t CPU_PRM_BASE;
    uint32_t RM_CPU_RSTCTRL;
    uint32_t RM_CPU_RSTST;
    uint32_t tmpRegVal;

    CPU_PRM_BASE   = SOC_DSP1_PRM_BASE;
    RM_CPU_RSTCTRL = RM_DSP1_RSTCTRL;
    RM_CPU_RSTST   = RM_DSP1_RSTST;

    /*Assert the DSP1*/
    HW_WR_REG32(CPU_PRM_BASE + RM_CPU_RSTCTRL, 0x3);

    /*Check the Reset status & clear*/
    if ((HW_RD_REG32(CPU_PRM_BASE + RM_CPU_RSTCTRL) & 0x3) == 0x3)
    {
        HW_WR_REG32(CPU_PRM_BASE + RM_CPU_RSTST, 0x3);
    }

    /*Clear reset for MMU, Cache & Slave interface OCP port*/
    tmpRegVal  = HW_RD_REG32(CPU_PRM_BASE + RM_CPU_RSTCTRL);
    tmpRegVal &= ~0x2;
    HW_WR_REG32(CPU_PRM_BASE + RM_CPU_RSTCTRL, tmpRegVal);

    while ((HW_RD_REG32(CPU_PRM_BASE + RM_CPU_RSTST) & 0x2) != 0x2) ;

    return 0;
}

/**
 * \brief   DSP1BringUp function assert reset(CPU & DSP SS) , set the entry
 *          point & release the CPU from reset.
 *
 *
 * \param[in]  EntryPoint - CPU entry location on reset
 *
 * \return      None.
 *
 **/
void DSP1BringUp(uint32_t EntryPoint)
{
    uint8_t i;

    /*Set the Entry point*/
    if (EntryPoint == 0)
    {
        HW_WR_REG32(DSP1BOOTADDR, (DSP1BOOTADDRVALUE >> 0xA));
        for (i = 0; i < 8; i++) {
            HW_WR_REG32(SOC_DSP1_L2_SRAM_BASE + 4 * i, 0x12); /*Write Self
                                                               * Branch
                                                               *Instruction*/
        }
    }
    else
    {
        HW_WR_REG32(DSP1BOOTADDR, (EntryPoint >> 0xA));
    }

    /*Bring-out of Reset*/
    HW_WR_REG32(SOC_DSP1_PRM_BASE + RM_DSP1_RSTCTRL, 0x0);
    while ((HW_RD_REG32(SOC_DSP1_PRM_BASE + RM_DSP1_RSTST) & 0x3) != 0x3)

        /*Check the Status of DSP1 Module mode*/
        while ((HW_RD_REG32(SOC_DSP1_CM_CORE_AON_BASE +
                            CM_DSP1_DSP1_CLKCTRL) & 0x30000) != 0x0) ;
}

