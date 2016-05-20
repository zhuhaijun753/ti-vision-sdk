/**
 *  \file     sbl_mbx_ipu1_cpu0.c
 *
 *  \brief    This file contains SBL multicore mailbox binary for IPU1 CPU0.
 *
 *  \details   IPU1 CPU0 sends message to IPU1 CPU1, DSP1, DSP2 and EVE1. Each
 *             core sends an acknowledgement after receiving message.
 *
 *  \copyright Copyright (C) 2014 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

/* ======================================================================
 *   Copyright (C) 2014 Texas Instruments Incorporated
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
#include "stdio.h"
#include "stdint.h"
#include "hw_emif.h"
#include <common/stw_types.h>
#include "soc.h"
#include "soc_defines.h"
#include "pmhal_prcm.h"
#include "platform.h"
#include "mailbox.h"
#include "uartStdio.h"
#include "interrupt.h"
#include "irq_xbar.h"
#include "emif.h"
#include "pmhal_rm.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

#define IPU1_CPU0_MAILBOX_MSG                           ((uint32_t) 0xFF33BB00U)
#define IPU_ECC_EMIF_TEST_INTR_LINE_NUMBER              ((uint32_t) 35U)
#define ECC_EMIF_START_ADDRESS                          (0x80000000U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void EmifEccErrHandler(void);
static void EmifEccHFHandler(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int main()
{
    uint32_t         msg           = 0U;
    uint32_t         ipu1Cpu1Flag  = 0U;
    uint32_t         dsp1Flag      = 0U;
    uint32_t         dsp2Flag      = 0U;
    uint32_t         eve1Flag      = 0U;
    emifEccErrInfo_t eccDDRErrInfo = {0};
    uint32_t         index         = 0U;

    /* Configure UART1 */
    UARTStdioInit();

    UARTPuts("\n Multi-core Mailbox Application: IPU1 Core0 Master core \n ",
             -1);

    /* Check if any one bit errors occurred previously */
    EMIFConfigECCGetEccErrInfo(SOC_EMIF1_CONF_REGS_BASE,
                               EMIF_ERR_ECC_ONEBIT,
                               &eccDDRErrInfo);

    for (index = 0U; index < eccDDRErrInfo.numValidErrAddr; index++)
    {
        UARTPuts("\n 1 Bit ECC Error occurred before coming to application", -1);
        UARTPuts("\n 1 Bit Error occurred at address: ", -1);
        UARTPutHexNum(eccDDRErrInfo.errAddr[index] + ECC_EMIF_START_ADDRESS);
    }

    if (0U < eccDDRErrInfo.numValidErrAddr)
    {
        UARTPuts("\n 1 Bit Error mask value: ", -1);
        UARTPutHexNum(eccDDRErrInfo.errBitLoc);
        EMIFClearIntrStatus(
            SOC_EMIF1_CONF_REGS_BASE,
            EMIF_SYSTEM_OCP_INTERRUPT_STATUS_ONEBIT_ECC_ERR_SYS_MASK);
    }

    /* Check if any two bit errors occurred previously */
    EMIFConfigECCGetEccErrInfo(SOC_EMIF1_CONF_REGS_BASE,
                               EMIF_ERR_ECC_TWOBIT,
                               &eccDDRErrInfo);

    if (0U != eccDDRErrInfo.errAddr[0U])
    {
        UARTPuts("\n 2 Bit ECC Error occurred before coming to application", -1);
        UARTPuts("\n 2 Bit Error occurred at address: ", -1);
        UARTPutHexNum(eccDDRErrInfo.errAddr[0U] + ECC_EMIF_START_ADDRESS);
    }

    /* Configure interrupts for ECC Errors */
    PlatformUnlockMMR();
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                   CPU_IPU1,
                   XBAR_INST_IPU1_IRQ_35,
                   EMIF1_IRQ);

    Intc_Init();
    Intc_IntEnable(0);

    /* Enable The EMIF interrupt for 1Bit ECC Error */
    Intc_IntRegister(IPU_ECC_EMIF_TEST_INTR_LINE_NUMBER,
                     (IntrFuncPtr) EmifEccErrHandler,
                     NULL);
    Intc_IntPrioritySet(IPU_ECC_EMIF_TEST_INTR_LINE_NUMBER, 1, 0);
    Intc_SystemEnable(IPU_ECC_EMIF_TEST_INTR_LINE_NUMBER);

    /* Register Hard Fault Handler for 2Bit ECC Error */
    Intc_IntRegister(EXCEPTION_M4_HARD_FAULT_NUM_3,
                     (IntrFuncPtr) EmifEccHFHandler,
                     NULL);

    EMIFEnableIntr(SOC_EMIF1_CONF_REGS_BASE,
                   EMIF_SYSTEM_OCP_INTERRUPT_STATUS_WR_ECC_ERR_SYS_MASK |
                   EMIF_SYSTEM_OCP_INTERRUPT_STATUS_TWOBIT_ECC_ERR_SYS_MASK |
                   EMIF_SYSTEM_OCP_INTERRUPT_STATUS_ONEBIT_ECC_ERR_SYS_MASK);

    /* Send message to IPU1 CPU1(MBX2_Q0) */
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_0,
                              IPU1_CPU0_MAILBOX_MSG)) ;

    /* Send message to DSP1(MBX2_Q1) */
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_1,
                              IPU1_CPU0_MAILBOX_MSG)) ;

    /* Send message to DSP2(MBX2_Q2) */
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_2,
                              IPU1_CPU0_MAILBOX_MSG)) ;

    /* Send message to EVE1(MBX2_Q3) */
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_3,
                              IPU1_CPU0_MAILBOX_MSG)) ;

    while ((ipu1Cpu1Flag != 1U) ||
           (dsp1Flag != 1U) ||
           (dsp2Flag != 1U) ||
           (eve1Flag != 1U))
    {
        /* Read message from IPU1 CPU1 */
        if (MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_4, &msg))
        {
            UARTPuts(" \n IPU1 CPU1 booted-up successfully \n", -1);
            ipu1Cpu1Flag = 1U;
        }

        /* Read message from DSP1 */
        if (MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_5, &msg))
        {
            UARTPuts("\n DSP1 booted-up successfully \n", -1);
            dsp1Flag = 1U;
        }

        /* Read message from DSP2 */
        if (MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_6, &msg))
        {
            UARTPuts("\n DSP2 booted-up successfully \n", -1);
            dsp2Flag = 1U;
        }
        /* Read message from EVE1 */
        if (MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_7, &msg))
        {
            UARTPuts("\n EVE1 booted-up successfully \n", -1);
            eve1Flag = 1U;
        }
    }
    return 0;
}

static void EmifEccErrHandler(void)
{
    uint32_t         eccDDRErrStatus;
    emifEccErrInfo_t eccDDRErrInfo = {0};
    uint32_t         index         = 0U;
    int32_t          retVal        = STW_SOK;
    EMIFConfigECCGetEccErrInfo(SOC_EMIF1_CONF_REGS_BASE,
                               EMIF_ERR_ECC_ONEBIT,
                               &eccDDRErrInfo);

    for (index = 0U; index < eccDDRErrInfo.numValidErrAddr; index++)
    {
        UARTPuts("\n 1 Bit ECC Error is found!!", -1);
        UARTPuts("\n 1 Bit Error occurred at address: ", -1);
        UARTPutHexNum(eccDDRErrInfo.errAddr[index] + ECC_EMIF_START_ADDRESS);
    }

    UARTPuts("\n 1 Bit Error mask value: ", -1);
    UARTPutHexNum(eccDDRErrInfo.errBitLoc);

    EMIFClearIntrStatus(
        SOC_EMIF1_CONF_REGS_BASE,
        EMIF_SYSTEM_OCP_INTERRUPT_STATUS_ONEBIT_ECC_ERR_SYS_MASK);

    eccDDRErrStatus = EMIFGetIntrStatus(SOC_EMIF1_CONF_REGS_BASE);

    if (0x0U !=
        (eccDDRErrStatus &
         EMIF_SYSTEM_OCP_INTERRUPT_STATUS_TWOBIT_ECC_ERR_SYS_MASK))
    {
        EMIFConfigECCGetEccErrInfo(SOC_EMIF1_CONF_REGS_BASE,
                                   EMIF_ERR_ECC_TWOBIT,
                                   &eccDDRErrInfo);

        UARTPuts("\n 2 Bit ECC Error is found!!", -1);
        UARTPuts("\n 2 Bit Error occurred at address: ", -1);
        UARTPutHexNum(eccDDRErrInfo.errAddr[0] + ECC_EMIF_START_ADDRESS);
        UARTPuts("\n Doing a cold reset due to 2 Bit Error Interrupt \n", -1);
        retVal = PMHALResetAssertGlobal(PMHAL_PRCM_GLB_RG_GLOBAL_COLD_RST);
        if (STW_SOK != retVal)
        {
            UARTPuts("\nFailed to do cold reset\n", -1);
            while (1) ;
        }
    }
    else if (0x0U !=
             (eccDDRErrStatus &
              EMIF_SYSTEM_OCP_INTERRUPT_STATUS_WR_ECC_ERR_SYS_MASK))
    {
        UARTPuts("\n ECC Non-quanta Access Error is found!! \n", -1);
        UARTPuts("\n Doing a cold reset due to 2 Bit Error Interrupt \n", -1);
        retVal = PMHALResetAssertGlobal(PMHAL_PRCM_GLB_RG_GLOBAL_COLD_RST);
        if (STW_SOK != retVal)
        {
            UARTPuts("\nFailed to do cold reset\n", -1);
            while (1) ;
        }
    }
    else
    {
        UARTPuts("\n Unidentified interrupt found!! \n", -1);
        UARTPuts("\n Doing a cold reset due to Unidentified Interrupt \n", -1);
        retVal = PMHALResetAssertGlobal(PMHAL_PRCM_GLB_RG_GLOBAL_COLD_RST);
        if (STW_SOK != retVal)
        {
            UARTPuts("\nFailed to do cold reset\n", -1);
            while (1) ;
        }
    }
}

static void EmifEccHFHandler(void)
{
    uint32_t         eccDDRErrStatus;
    emifEccErrInfo_t eccDDRErrInfo = {0};
    int32_t          retVal        = STW_SOK;

    eccDDRErrStatus = EMIFGetIntrStatus(SOC_EMIF1_CONF_REGS_BASE);

    if (0x0U !=
        (eccDDRErrStatus &
         EMIF_SYSTEM_OCP_INTERRUPT_STATUS_TWOBIT_ECC_ERR_SYS_MASK))
    {
        EMIFConfigECCGetEccErrInfo(SOC_EMIF1_CONF_REGS_BASE,
                                   EMIF_ERR_ECC_TWOBIT,
                                   &eccDDRErrInfo);

        UARTPuts("\n 2 Bit ECC Error is found!!", -1);
        UARTPuts("\n 2 Bit Error occurred at address: ", -1);
        UARTPutHexNum(eccDDRErrInfo.errAddr[0] + ECC_EMIF_START_ADDRESS);
    }
    else if (0x0U !=
             (eccDDRErrStatus &
              EMIF_SYSTEM_OCP_INTERRUPT_STATUS_WR_ECC_ERR_SYS_MASK))
    {
        UARTPuts("\n ECC Non-quanta Access Error is found!! \n", -1);
    }
    else
    {
        UARTprintf("\n Hard Fault Interrupt occurred!! \n");
    }

    UARTPuts("\n Doing a cold reset due to HF Error \n", -1);
    retVal = PMHALResetAssertGlobal(PMHAL_PRCM_GLB_RG_GLOBAL_COLD_RST);
    if (STW_SOK != retVal)
    {
        UARTPuts("\nFailed to do cold reset\n", -1);
        while (1) ;
    }
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */
