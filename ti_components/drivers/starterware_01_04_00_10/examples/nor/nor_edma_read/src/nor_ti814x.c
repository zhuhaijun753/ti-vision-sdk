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

#include <stdio.h>
#include <stdint.h>
#include "gpmc.h"
#include "soc_defines.h"
#include "platform.h"
#include "edma.h"
#include "interrupt.h"
#include "soc.h"
#include "util.h"
#include "uartStdio.h"
#include "timeProfile.h"

#define MAX_ACNT            (0x1C20)
#define MAX_BCNT            (0x01)
#define MAX_CCNT            (0x01)
#define MAX_BUFFER_SIZE     (MAX_ACNT * MAX_BCNT * MAX_CCNT)
#define EDMA_U_BASE         (SOC_EDMA_TPCC_BASE)

#if !defined (BUILD_GCC)
#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(dstBuff, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
unsigned char     dstBuff[MAX_BUFFER_SIZE];
#else
signed char __attribute__((section(".my_sect_ddr"))) dstBuff[MAX_BUFFER_SIZE];
#endif

uint32_t          ch_num           = 1;
uint32_t          tcc_num          = 1;
uint32_t          evtq_num         = 0;
uint32_t          region           = 0U;
uint32_t          interrupt_num    = 12U;
uint32_t          base_address     = EDMA_U_BASE;
uint32_t          nor_base_address = 0x08000000;

volatile uint32_t transfer_complete = 0;

void isrEdmaCompletion(void *handle)
{
    transfer_complete = 1;
    EDMA3ClrIntr(base_address, tcc_num);
}

int main()
{
    EDMA3CCPaRAMEntry edmaParam;
    uint32_t          i = 0;

#if !defined BUILD_GCC
    uint32_t          initTick = 0, finalTick = 0, totalTicks = 0;
#endif

    UARTStdioInit();
    UARTPuts("In Main\n", -1);

#if !defined BUILD_GCC
    enableticks;
#endif

    /*Enable GPIO clock */
    PlatformGPIOClockEnable();

    /*Enable GPMC clock */
    PlatformGPMCClockEnable();

    /*PlatformGPMCPinCtrl need to be in supervisor mode from A8*/
    /*Enable GPMC pin mux*/
    PlatformGPMCPinCtrl();

    /* Configure the GPMC */
    GPMC_Init();

    UARTPuts("GPMC Configuration complete\n", -1);
    UARTPuts("Now running EDMA\n", -1);

    EDMAsetRegion(region);
    EDMA3Init(base_address, 0);

    /* Enable The EDMA interrupt */
    Intc_Init();
    Intc_IntEnable(0);

    Intc_IntRegister(interrupt_num, (IntrFuncPtr) isrEdmaCompletion, NULL);
    Intc_IntPrioritySet(interrupt_num, 1, 0);
    Intc_SystemEnable(interrupt_num);

    EDMA3RequestChannel(base_address, EDMA3_CHANNEL_TYPE_DMA, ch_num, tcc_num,
                        evtq_num);

    edmaParam.opt      = 0;
    edmaParam.srcAddr  = (uint32_t) (nor_base_address);
    edmaParam.destAddr = (uint32_t) dstBuff;
    edmaParam.aCnt     = MAX_BUFFER_SIZE;
    edmaParam.bCnt     = MAX_BCNT;
    edmaParam.cCnt     = MAX_CCNT;
    edmaParam.srcBIdx  = 0;
    edmaParam.destBIdx = 0;
    edmaParam.srcCIdx  = 0;
    edmaParam.destCIdx = 0;
    edmaParam.linkAddr = 0xFFFFU;
    edmaParam.opt     |=
        (EDMA_TPCC_OPT_TCINTEN_MASK |
         ((tcc_num << EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK));

    EDMA3SetPaRAM(base_address, ch_num, &edmaParam);

    /* Get the number of ticks before EDMA transfer */
#if !defined BUILD_GCC
    initTick = getticks;
#endif

    /* Transfer is done in async mode */
    /* Number of triggers required are MAX_BCNT * MAX_CCNT i.e. bCnt*cCnt */
    for (i = 0; i < MAX_BCNT * MAX_CCNT; i++)
    {
        transfer_complete = 0;
        EDMA3EnableTransfer(base_address, ch_num, EDMA3_TRIG_MODE_MANUAL);
        while (transfer_complete != 1) ;
    }

    /* Get the number of ticks after EDMA is complete */
#if !defined BUILD_GCC
    finalTick  = getticks;
    totalTicks = ticks(initTick, finalTick);
    printticks(totalTicks, "time");
#endif

    /* Disable the EDMA interrupt */
    Intc_SystemDisable(interrupt_num);
    Intc_IntUnregister(interrupt_num);

    UARTPuts("EDMA complete, application exiting normally!!", -1);
    return (0);
}

