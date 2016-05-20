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
#include "edma.h"
#include "soc.h"
#include "soc_defines.h"
#include "platform.h"
#include "nor.h"
#include "util.h"
#include "device.h"
#include "uartStdio.h"
#include "cp15.h"
#include "debug.h"

#define NOR_BASE_ADDRESS 0x8000000
#define MAX_DELAY   0x900

uint32_t          ch_num           = 2;
uint32_t          tcc_num          = 2;
uint32_t          evtq_num         = 0;
uint32_t          region           = 0U;
uint32_t          interrupt_num    = 12U;
uint32_t          base_address     = SOC_EDMA_TPCC_BASE;
uint32_t          nor_base_address = 0x08000000;

volatile uint32_t transfer_complete = 0;

GPMC_Config_t     GPMC_ConfigNorDefault = {
    /* SysConfig - ROM Code defaults */
    0x0,           // 0x0008,
    /* IRQEnable - ROM Code defaults */
    0x0000,
    /* TimeOutControl - ROM Code defaults */
    0xf01f0000,
    /* Config - ROM Code defaults */
    0x000a0000,
    {
        0x41041010,
        0x001E1C01,
        0x00000000,
        0x0F071C03,
        0x041B1F1F,
        0x8F070000,
        0x00000f48,
    },
};

/************************************************************
 * Local Function Declarations                               *
 ************************************************************/
void GPMC_Write(Uint32 offset, Uint32 val)
{
    *(volatile Uint32 *) (GPMC_BASE + offset) = val;
}

void GPMC_CSWrite(Int8 cs, Uint32 offset, Uint32 val)
{
    *(volatile Uint32 *) (GPMC_CONFIG_CS0_BASE +
                          (GPMC_CS_CONFIG_SIZE * cs) + offset) = val;
}

Uint32 GPMC_Read(Uint32 offset)
{
    return (*(volatile Uint32 *) (GPMC_BASE + offset));
}

/* make sure compiler doesnt optimize this function */
Uint32 DEVICE_Delay(Uint32 delay)
{
    UTIL_waitLoop(delay * 0x100);
    return 0;
}

void CM_Write(Uint32 module, Uint32 reg, Uint32 val)
{
    *(volatile Uint32 *) (CM_BASE + module + reg) = val;
}

/*********************************************************************
 *
 * GPMC_Init - Initialize GPMC based on CS and config values
 *
 *********************************************************************/
void GPMC_Init(GPMC_Config_t *cfg, Int8 cs)
{
    Int32 i;

    /****** program global GPMC regs *****/
    GPMC_Write(GPMC_SYSCONFIG_OFF, cfg->SysConfig);
    GPMC_Write(GPMC_IRQENABLE_OFF, cfg->IrqEnable);
    GPMC_Write(GPMC_TIMEOUTCTRL_OFF, cfg->TimeOutControl);
    GPMC_Write(GPMC_CONFIG_OFF, cfg->Config);

    /****** program GPMC CS specific registers *****/
    /* disable cs */
    GPMC_CSWrite(cs, GPMC_CONFIG7_OFF, 0x00000000);
    DEVICE_Delay(MAX_DELAY);

    /* program new set of config values (1 to 7) */
    for (i = 0; i < GPMC_MAX_CS; i++) {
        GPMC_CSWrite(cs, (i * 4), cfg->ChipSelectConfig[i]);
    }

    /* enable cs */
    GPMC_CSWrite(cs, GPMC_CONFIG7_OFF, (cfg->ChipSelectConfig[6] | 0x40));
    DEVICE_Delay(MAX_DELAY);
}

void isrEdmaCompletion(void *handle)
{
    transfer_complete = 1;
    EDMA3ClrIntr(base_address, tcc_num);
}

void NOR_ReadSectors_edma(void *dstAddr, void *srcOffsetAddr, uint32_t length,
                          uint32_t edma_ch_num)
{
    EDMA3CCPaRAMEntry edmaParam;
    int32_t           bCntValue = 1;
    int32_t           remBytes  = 0;
    int32_t           aCntValue = length;
    uint32_t          addr      = (uint32_t) (dstAddr);
    uint32_t          max_acnt  = 0x7FFFU;

    uint32_t          psrc = NOR_BASE_ADDRESS;

    if (length > max_acnt)
    {
        bCntValue = (length / max_acnt);
        remBytes  = (length % max_acnt);
        aCntValue = max_acnt;
    }

    /*Make the application images are word aligned*/
    psrc += *((uint32_t *) (srcOffsetAddr));

    /* Compute NOR address and size */
    edmaParam.opt      = 0;
    edmaParam.srcAddr  = psrc;
    edmaParam.destAddr = addr;
    edmaParam.aCnt     = aCntValue;
    edmaParam.bCnt     = bCntValue;
    edmaParam.cCnt     = 1;
    edmaParam.srcBIdx  = aCntValue;
    edmaParam.destBIdx = aCntValue;
    edmaParam.srcCIdx  = 0;
    edmaParam.destCIdx = 0;
    edmaParam.linkAddr = 0xFFFF;
    edmaParam.opt     |=
        (EDMA_TPCC_OPT_TCINTEN_MASK |
         ((edma_ch_num <<
           EDMA_TPCC_OPT_TCC_SHIFT) &
          EDMA_TPCC_OPT_TCC_MASK) | EDMA_TPCC_OPT_SYNCDIM_MASK);

    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, edma_ch_num, &edmaParam);
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE, edma_ch_num, EDMA3_TRIG_MODE_MANUAL);

    while (!(EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE) & (1 << edma_ch_num))) ;
    EDMA3ClrIntr(SOC_EDMA_TPCC_BASE, edma_ch_num);
    if (remBytes != 0)
    {
        /* Compute QSPI address and size */
        edmaParam.opt     = 0;
        edmaParam.srcAddr =
            (NOR_BASE_ADDRESS +
             (bCntValue * max_acnt) + *((uint32_t *) srcOffsetAddr));
        edmaParam.destAddr = (addr + (max_acnt * bCntValue));
        edmaParam.aCnt     = remBytes;
        edmaParam.bCnt     = 1;
        edmaParam.cCnt     = 1;
        edmaParam.srcBIdx  = remBytes;
        edmaParam.destBIdx = remBytes;
        edmaParam.srcCIdx  = 0;
        edmaParam.destCIdx = 0;
        edmaParam.linkAddr = 0xFFFF;
        edmaParam.opt     |=
            (EDMA_TPCC_OPT_TCINTEN_MASK |
             ((edma_ch_num << EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK));
        EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, edma_ch_num, &edmaParam);
        EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE, edma_ch_num,
                            EDMA3_TRIG_MODE_MANUAL);

        while (!(EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE) & (1 << edma_ch_num))) ;
        EDMA3ClrIntr(SOC_EDMA_TPCC_BASE, edma_ch_num);
    }
    *((uint32_t *) srcOffsetAddr) += length;
}

uint32_t NORReadLocal(void *dst1, uint32_t offset, uint32_t length)
{
    uint32_t  i;
    uint16_t *psrc = (uint16_t *) 0x08000000;
    uint16_t *pdst = (uint16_t *) dst1;

    /*Make the application images are word aligned*/
    psrc += (offset) >> 1;

    for (i = 0; i < length; )
    {
        *pdst++ = *psrc++;
        i       = i + 2;
    }

    return 0;
}

int main()
{
    uint32_t       dstaddr_edma   = 0x80600000;
    uint32_t       dstaddr_memcpy = 0x80700000;
    uint32_t      *srcaddr_ptr;
    uint32_t       srcaddr = 0x80000;
    NOR_InfoHandle hNorInfo;

    uint32_t       start_time, end_time;
    uint32_t       length = 0x100000;

    evtq_num = 0;
    region   = 0;

    /*NOR Flash profile code*/

    /*
     * 1) PIN Mux settings
     * 2) GPMC timing parameter configuration
     * 3) NOR Flash initialization
     * 4) CFI Querry
     * 5) Initialize the EDMA & request channel
     * 6) Do edma copy
     */

    UARTStdioInit();
    UARTPuts("\nNOR Flash profiler", -1);

    /*PMU Clock counter reset*/
    ARM_CCNT_Enable();

    GPMC_Init(&GPMC_ConfigNorDefault, 0);
    PlatformGPMCSetPinMux();

    /* Initialize NOR Flash*/
    hNorInfo = NOR_open(0, 2 /* 16 Bit */);
    if (hNorInfo == NULL)
    {
        DEBUG_printString("\tERROR: NOR Initialization failed.\r\n");
        return E_FAIL;
    }

    EDMAsetRegion(region);
    EDMA3Init(base_address, 0);

    EDMA3RequestChannel(base_address, EDMA3_CHANNEL_TYPE_DMA, ch_num, tcc_num,
                        evtq_num);

    srcaddr_ptr = &srcaddr;

    start_time = ARM_CCNT_Read();

    NORReadLocal((void *) dstaddr_memcpy, 0x80000, length);

    /*Read the CPU cycle */
    end_time = ARM_CCNT_Read();

    UARTprintf("\n Number of bytes read from NOR FLASH: %u", length);

    UARTprintf("\n NOR data copy with memcpy - cpu cycles - %u\n",
               end_time - start_time);

    start_time = ARM_CCNT_Read();

    NOR_ReadSectors_edma((void *) dstaddr_edma, (void *) srcaddr_ptr, length, 2);

    /*Read the CPU cycle */
    end_time = ARM_CCNT_Read();

    UARTprintf("\n NOR data copy in DMA MODE - cpu cycles - %u\n",
               end_time - start_time);

    UARTprintf(
        " \n PMCCNTR counts once every 64 clock cycles. To get actual CPU cycle multiple by 64\n");

    {volatile int spin = 1; while (spin) ; }
    return 0;
}

