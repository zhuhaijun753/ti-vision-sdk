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
#include "stdint.h"
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include <common/stw_utils.h>
#include "gpmc.h"
#include "soc_defines.h"
#include "platform.h"
#include "edma.h"
#include "interrupt.h"
#include "soc.h"
#include "util.h"
#include "platform.h"
#include "uartStdio.h"
#include "i2clib/lld_hsi2c.h"
#include "boards/stw_board.h"
#include "devices/stw_device.h"
#include "stwutils_app.h"

#if (defined (BUILD_M4) || defined (BUILD_A15))
    #include "irq_xbar.h"
#endif

#define MAX_ACNT            (0x1C20)
#define MAX_BCNT            (0x01)
#define MAX_CCNT            (0x01)
#define MAX_BUFFER_SIZE     (MAX_ACNT * MAX_BCNT * MAX_CCNT)
#define EDMA_U_BASE         (SOC_EDMA_TPCC_BASE)

#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(dstBuff, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
unsigned char dstBuff[MAX_BUFFER_SIZE];

#ifdef BUILD_A15
#define printf UARTprintf
#endif

#ifndef SOC_EDMA_TPCC_BASE /* Temporary HACK for Vayu M4 */
#if defined (BUILD_M4)
/* EDMA region 0x43300000 mappped to 0x63300000 */
#define SOC_EDMA_TPCC_BASE      (0x63300000U)
#endif
#endif

#define EDMA3_CC_XFER_COMPLETION_INT_A8                 (12U)
#define EDMA3_CC_XFER_COMPLETION_INT_DSP                (20U)
#define EDMA3_CC_XFER_COMPLETION_INT_M3VPSS             (63U)
#define EDMA3_CC_XFER_COMPLETION_INT_M3VIDEO            (62U)
#define EDMA3_CC_XFER_COMPLETION_INT_A15                (12U)
#define EDMA3_CC_XFER_COMPLETION_INT_M4                 (34U)

#ifdef BUILD_A8
#define EDMA3_CC_XFER_COMPLETION_INT EDMA3_CC_XFER_COMPLETION_INT_A8
#elif defined (BUILD_DSP)
#define EDMA3_CC_XFER_COMPLETION_INT EDMA3_CC_XFER_COMPLETION_INT_DSP
#elif defined (BUILD_M3VPSS)
#define EDMA3_CC_XFER_COMPLETION_INT EDMA3_CC_XFER_COMPLETION_INT_M3VPSS
#elif defined (BUILD_M3VIDEO)
#define EDMA3_CC_XFER_COMPLETION_INT EDMA3_CC_XFER_COMPLETION_INT_M3VIDEO
#elif defined (BUILD_A15)
#define EDMA3_CC_XFER_COMPLETION_INT EDMA3_CC_XFER_COMPLETION_INT_A15
#elif defined (BUILD_M4)
#define EDMA3_CC_XFER_COMPLETION_INT EDMA3_CC_XFER_COMPLETION_INT_M4
#endif

#define EDMA3_CC_REGION_A8                              (0U)
#define EDMA3_CC_REGION_DSP                             (1U)
#define EDMA3_CC_REGION_M3VPSS                          (5U)
#define EDMA3_CC_REGION_M3VIDEO                         (4U)
#define EDMA3_CC_REGION_A15                             (0U)
#define EDMA3_CC_REGION_M4                              (1U)

#ifdef BUILD_A8
#define EDMA3_CC_REGION EDMA3_CC_REGION_A8
#elif defined (BUILD_DSP)
#define EDMA3_CC_REGION EDMA3_CC_REGION_DSP
#elif defined (BUILD_M3VPSS)
#define EDMA3_CC_REGION EDMA3_CC_REGION_M3VPSS
#elif defined (BUILD_M3VIDEO)
#define EDMA3_CC_REGION EDMA3_CC_REGION_M3VIDEO
#elif defined (BUILD_A15)
#define EDMA3_CC_REGION EDMA3_CC_REGION_A15
#elif defined (BUILD_M4)
#define EDMA3_CC_REGION EDMA3_CC_REGION_M4
#endif

uint32_t          region           = EDMA3_CC_REGION;
uint32_t          interrupt_num    = EDMA3_CC_XFER_COMPLETION_INT;
uint32_t          ch_num           = 1;
uint32_t          tcc_num          = 1;
uint32_t          evtq_num         = 0;
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
    EDMA3CCPaRAMEntry  edmaParam;
    uint32_t           i = 0;

    stwAppInitParams_t stwAppInitParams;
    int32_t retVal;

    /* System init */
    stwAppInitParams.isI2cInitReq  = TRUE;
    stwAppInitParams.isUartInitReq = TRUE;
    retVal = StwUtils_appDefaultInit(stwAppInitParams);
    if (retVal != STW_SOK)
    {
        UARTPuts("\nSystem Init Failed ", -1);
    }

    /*Enable GPIO clock */
    PlatformGPIOClockEnable();

    /*Enable GPMC clock */
    PlatformGPMCClockEnable();

    /*PlatformGPMCPinCtrl need to be in supervisor mode from A8*/
    /*Enable GPMC pin mux*/
    PlatformGPMCSetPinMux();

    BOARDSelectDevice(DEVICE_ID_NORFLASH, DEVICE_NORFLASH_INST_ID_0);

    /* Configure the GPMC */
    GPMC_Init();

    UARTPuts("GPMC Configuration complete\n", -1);
    UARTPuts("Now running EDMA\n", -1);
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

    /* Transfer is done in async mode */
    /* Number of triggers required are MAX_BCNT * MAX_CCNT i.e. bCnt*cCnt */
    for (i = 0; i < MAX_BCNT * MAX_CCNT; i++)
    {
        transfer_complete = 0;
        EDMA3EnableTransfer(base_address, ch_num, EDMA3_TRIG_MODE_MANUAL);
        while (transfer_complete != 1) ;
    }

    /* Disable the EDMA interrupt */
    Intc_SystemDisable(interrupt_num);
    Intc_IntUnregister(interrupt_num);

    UARTPuts("EDMA complete, application exiting normally!!", -1);
    return 0;
}

