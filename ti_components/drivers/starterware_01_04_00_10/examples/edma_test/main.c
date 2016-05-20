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

#ifndef TI814X_FAMILY_BUILD
    #include "irq_xbar.h"
#endif
    #include "hw_types.h"

#ifndef SOC_EDMA_TPCC_BASE /* Temporary HACK for M4
                            * as 0x43300000 is bit band region*/
#if defined (BUILD_M4)
/* EDMA region 0x43300000 mappped to 0x63300000 */
#define SOC_EDMA_TPCC_BASE      (0x63300000U)
#endif
#endif

#ifndef TI814X_FAMILY_BUILD
#if defined (BUILD_A15)
#define IRQ_XBAR_INST_NO XBAR_INST_MPU_IRQ_12
#elif defined (BUILD_M4)
#define IRQ_XBAR_INST_NO XBAR_INST_IPU1_IRQ_34
#elif defined (BUILD_DSP)
#define IRQ_XBAR_INST_NO XBAR_INST_DSP1_IRQ_38
#endif
#endif

uint32_t          edma_ch_num   = 1;
uint32_t          edma_tcc_num  = 1;
uint32_t          edma_evtq_num = 0;

uint32_t          qdma_ch_num1 = 1;
uint32_t          qdma_ch_num2 = 2;

uint32_t          edma_ch_num2  = 2;
uint32_t          edma_tcc_num2 = 2;

uint32_t          edma_paRAMId2 = 70;
uint32_t          edma_paRAMId3 = 80;

uint32_t          qdma_paramid1;
uint32_t          qdma_paramid2;
uint32_t          qdma_paramid3;

volatile uint32_t transfer_complete = 0;
uint32_t          region        = EDMA3_CC_REGION;
uint32_t          interrupt_num = EDMA3_CC_XFER_COMPLETION_INT;

#ifdef TI814X_FAMILY_BUILD
#define EDMA_U_BASE SOC_EDMA_TPCC_BASE
#elif (defined (TDA2XX_FAMILY_BUILD) || defined (TDA3XX_FAMILY_BUILD))
#if defined (BUILD_DSP)
#define EDMA_U_BASE SOC_EDMA_CC_BASE
#else
#define EDMA_U_BASE SOC_EDMA_TPCC_BASE
#endif
#endif

#if !defined (BUILD_A15) && !defined (BUILD_GCC)

#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_srcBuff1, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
signed char       _srcBuff1[MAX_BUFFER_SIZE];

#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_dstBuff1, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
signed char       _dstBuff1[MAX_BUFFER_SIZE];

#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_srcBuff2, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
signed char       _srcBuff2[MAX_BUFFER_SIZE];

#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_dstBuff2, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
signed char       _dstBuff2[MAX_BUFFER_SIZE];

#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_srcBuff3, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
signed char       _srcBuff3[MAX_BUFFER_SIZE];

#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_dstBuff3, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
signed char       _dstBuff3[MAX_BUFFER_SIZE];

#else
signed char __attribute__((section(".my_sect_ddr"))) _srcBuff1[MAX_BUFFER_SIZE];
signed char __attribute__((section(".my_sect_ddr"))) _dstBuff1[MAX_BUFFER_SIZE];
signed char __attribute__((section(".my_sect_ddr"))) _srcBuff2[MAX_BUFFER_SIZE];
signed char __attribute__((section(".my_sect_ddr"))) _dstBuff2[MAX_BUFFER_SIZE];
signed char __attribute__((section(".my_sect_ddr"))) _srcBuff3[MAX_BUFFER_SIZE];
signed char __attribute__((section(".my_sect_ddr"))) _dstBuff3[MAX_BUFFER_SIZE];
#endif

signed char      *srcBuff1;
signed char      *dstBuff1;
signed char      *srcBuff2;
signed char      *dstBuff2;
signed char      *srcBuff3;
signed char      *dstBuff3;

uint32_t          base_address = EDMA_U_BASE;

void isrEdmaCompletion(void *handle);

int main(void)
{
    qdma_paramid1 = (edma_ch_num + SOC_EDMA3_NUM_DMACH);
    qdma_paramid2 = (edma_ch_num + SOC_EDMA3_NUM_DMACH + 1);
    qdma_paramid3 = (edma_ch_num + SOC_EDMA3_NUM_DMACH + 2);
    PlatformUartConsoleSetPinMux();

    UARTStdioInit();
    UARTPuts("\nEDMA App", -1);

#ifndef TI814X_FAMILY_BUILD
    /*Configure the EDMA clock */
    PlatformEDMAWkupDepEnable();
#endif

    EDMAsetRegion(region);

    /* Do EDMA init Done once in the beginning of application */
    EDMA3Init(base_address, 0);

#ifndef TI814X_FAMILY_BUILD
    /*Unlock the Crossbar register */
    PlatformUnlockMMR();
#endif

#ifndef TI814X_FAMILY_BUILD
#ifdef BUILD_A15
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_MPUSS,
                   IRQ_XBAR_INST_NO,
                   EDMA_TPCC_IRQ_REGION0);
#elif defined (BUILD_M4)
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1,
                   IRQ_XBAR_INST_NO,
                   EDMA_TPCC_IRQ_REGION1);
#elif defined (BUILD_DSP)
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_DSP1,
                   IRQ_XBAR_INST_NO,
                   EDMA_TPCC_IRQ_REGION2);
#endif
#endif

    /* Enable The EDMA interrupt */
    Intc_Init();
    Intc_IntEnable(0);

    Intc_IntRegister(interrupt_num, (IntrFuncPtr) isrEdmaCompletion, NULL);

    Intc_IntPrioritySet(interrupt_num, 1, 0);
    Intc_SystemEnable(interrupt_num);

    if (dma_test(edma_ch_num, edma_tcc_num, edma_evtq_num, MAX_ACOUNT,
                 MAX_BCOUNT, MAX_CCOUNT) == SUCCESS)
    {
        UARTPuts("\nEDMA test First time transfer is complete", -1);
    }

    /* Do a EDMA DeInit and try the same transfer again */
    EDMA3Deinit(base_address, 0);
    EDMA3Init(base_address, 0);

    if (dma_test(edma_ch_num, edma_tcc_num, edma_evtq_num, MAX_ACOUNT,
                 MAX_BCOUNT, MAX_CCOUNT) == SUCCESS)
    {
        UARTPuts("\nEDMA test Second time transfer is complete", -1);
    }

    if (dma_chain_test(edma_ch_num, edma_tcc_num, edma_evtq_num, edma_ch_num2,
                       edma_tcc_num2, edma_evtq_num, MAX_ACOUNT, MAX_BCOUNT,
                       MAX_CCOUNT) == SUCCESS)
    {
        UARTPuts("\nEDMA chain test transfer is complete", -1);
    }

    if (dma_ping_pong_test(edma_ch_num, edma_tcc_num, edma_evtq_num,
                           edma_paRAMId2, edma_paRAMId3) == SUCCESS)
    {
        UARTPuts("\nDMA ping pong buffer test is complete", -1);
    }

    if (dma_link_test(edma_ch_num, edma_tcc_num, edma_evtq_num, edma_paRAMId2,
                      edma_paRAMId3, MAX_ACOUNT, MAX_BCOUNT,
                      MAX_CCOUNT) == SUCCESS)
    {
        UARTPuts("\nEDMA link test transfer is complete", -1);
    }
    if (qdma_test(qdma_ch_num1, edma_tcc_num, edma_evtq_num, qdma_paramid1,
                  MAX_ACOUNT,
                  MAX_BCOUNT, MAX_CCOUNT) == SUCCESS)
    {
        UARTPuts("\nQDMA test transfer is complete", -1);
    }

    /* Disable the EDMA interrupt */
    Intc_SystemDisable(interrupt_num);
    Intc_IntUnregister(interrupt_num);

    if (dma_polled(edma_ch_num, edma_tcc_num, edma_evtq_num, MAX_ACOUNT,
                   MAX_BCOUNT, MAX_CCOUNT) == SUCCESS)
    {
        UARTPuts("\nEDMA polled test transfer is complete", -1);
    }
    if (qdma_link_test(qdma_ch_num2, edma_tcc_num, edma_evtq_num, qdma_paramid2,
                       qdma_paramid3, MAX_ACOUNT,
                       MAX_BCOUNT, MAX_CCOUNT) == SUCCESS)
    {
        UARTPuts("\nQDMA link test transfer is complete", -1);
    }
    EDMA3Deinit(base_address, 0);

    return 0;
}

void isrEdmaCompletion(void *handle)
{
    transfer_complete = 1;
    EDMA3ClrIntr(base_address, edma_tcc_num);
    EDMA3ClrIntr(base_address, edma_tcc_num2);
}

