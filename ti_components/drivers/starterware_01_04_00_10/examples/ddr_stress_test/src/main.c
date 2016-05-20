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
#include "stdlib.h"
#include <common/stw_types.h>
#include "soc_defines.h"
#include "uartStdio.h"
#include "edma.h"
#include "sample.h"
#include "interrupt.h"
#include "soc.h"
#include "platform.h"
#include "hw_core_prm.h"
#include "hw_types.h"

#if (defined (BUILD_M4) || defined (BUILD_A15))
    #include "irq_xbar.h"
#endif

#if defined (TDA3XX_FAMILY_BUILD)
#define DDR_BASE_ADDRESS  0x80000000
#else
#define EMIF_1

#ifdef EMIF_1
#define DDR_BASE_ADDRESS  0x80000000
#else
#define DDR_BASE_ADDRESS  0xA0000000 /*DDR BANK 2*/
#endif
#endif

#ifndef SOC_EDMA_TPCC_BASE /* Temporary HACK for Vayu M4 */
#if defined (BUILD_M4)
#define SOC_EDMA_TPCC_BASE      (0x63300000U)
#endif
#endif

uint32_t          edma_ch_num  = 1;
uint32_t          edma_tcc_num = 1;

uint32_t          edma_evtq_num = 0;

volatile uint32_t transfer_complete = 0;
uint32_t          region        = EDMA3_CC_REGION;
uint32_t          interrupt_num = EDMA3_CC_XFER_COMPLETION_INT;
#define EDMA_U_BASE SOC_EDMA_TPCC_BASE

#if !defined (BUILD_A15) && !defined (BUILD_GCC)
#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_srcBuffm, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
signed char       _srcBuffm[BUFFER_SIZE];
#else
signed char __attribute__((section(".my_sect_ddr"))) _srcBuffm[MAX_BUFFER_SIZE];
#endif

uint32_t          base_address = EDMA_U_BASE;
uint32_t          ddr_base_address;
unsigned char     ddr_val;

void isrEdmaCompletion(void *handle);

int main(void)
{
    PlatformUartConsoleSetPinMux();

    UARTStdioInit();
    UARTPuts("\nDDR Stress Test App", -1);

#ifndef TI814X_FAMILY_BUILD
    /*Configure the EDMA clock */
    PlatformEDMAWkupDepEnable();
#endif

    /* Do EDMA init Done once in the beginning of application */
    EDMAsetRegion(region);
    EDMA3Init(base_address, 0);

#ifdef BUILD_A15

    /*Unlock the Crossbar register */
    PlatformUnlockMMR();

    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_MPUSS, 7,
                   EDMA_TPCC_IRQ_REGION0);

#elif defined (BUILD_M4)

    /*Unlock the Crossbar register */
    PlatformUnlockMMR();

    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1, 12,
                   EDMA_TPCC_IRQ_REGION1);

#endif

    /* Enable The EDMA interrupt */
    Intc_Init();
    Intc_IntEnable(0);

    Intc_IntRegister(interrupt_num, (IntrFuncPtr) isrEdmaCompletion, NULL);

    Intc_IntPrioritySet(interrupt_num, 1, 0);
    Intc_SystemEnable(interrupt_num);

    while (1)
    {
#if (defined (TDA3XX_FAMILY_BUILD)) || (defined (TDA2EX_BUILD))
        ddr_base_address = 0x80000000; /* DDR BANK */
        break;
#else
        UARTPuts("\nEnter the EMIF number to test:", -1);
        UARTPuts("\nEnter 1 for EMIF1 and 2 for EMIF2:", -1);
        ddr_val = UARTGetNum();
        if (ddr_val == 1)
        {
            ddr_base_address = 0x80000000; /* DDR BANK 1 */
            break;
        }
        else if (ddr_val == 2)
        {
            ddr_base_address = 0xA0000000;  /*DDR  BANK 2 */
            break;
        }
        else
        {
            UARTPuts("\nEnter valid EMIF number for DDR test \n", -1);
        }
#endif
    }

    if (edma_mem_test1(ddr_base_address, edma_ch_num, edma_tcc_num,
                       edma_evtq_num, MAX_ACOUNT,
                       MAX_BCOUNT, MAX_CCOUNT) == SUCCESS)
    {
        UARTPuts(" \nDDR-- Full memory read/write test is complete \n", -1);
    }
    if (edma_mem_test2(edma_ch_num, edma_tcc_num, edma_evtq_num, MAX_ACOUNT,
                       MAX_BCOUNT, MAX_CCOUNT) == SUCCESS)
    {
        UARTPuts(" \nDDR-- Random memory read/write test is complete \n", -1);
    }
    if (edma_mem_test3(edma_ch_num, edma_tcc_num, edma_evtq_num, MAX_ACOUNT,
                       MAX_BCOUNT, MAX_CCOUNT) == SUCCESS)
    {
        UARTPuts("\nDDR-- Sequential memory read/write test is complete \n", -1);
        UARTPuts(
            "==============================================================\n",
            -1);
    }
    if (edma_mem_test4(edma_ch_num, edma_tcc_num, edma_evtq_num, MAX_ACOUNT,
                       MAX_BCOUNT, MAX_CCOUNT) == SUCCESS)
    {
        UARTPuts("\nDDR-- Sequential increment pattern test is complete \n", -1);
        UARTPuts(
            "==============================================================\n",
            -1);
    }
    /* Disable the EDMA interrupt */
    Intc_SystemDisable(interrupt_num);
    Intc_IntUnregister(interrupt_num);

    return 0;
}

void isrEdmaCompletion(void *handle)
{
    transfer_complete = 1;
    EDMA3ClrIntr(base_address, edma_tcc_num);
}

