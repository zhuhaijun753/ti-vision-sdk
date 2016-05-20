/**
 *  \file     crc_app_semicpu.c
 *
 *  \brief    This file contains CRC test code for Semi-CPU mode.
 *
 *  \details  CRC operational mode is set to Semi-CPU for channel number 1.
 *            CRC signature is calculated on frame(1280*720*2) stored in DDR RAM
 *            and compared against pre-calculated good CRC signature value.
 *            Program uses SYNTIMER32k for performance calculation.
 *
 *  \copyright Copyright (C) 2014 Texas Instruments Incorporated =
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
#include <stdint.h>
#include <stdio.h>
#include "common/stw_dataTypes.h"
#include "soc.h"
#include "hw_types.h"
#include "edma.h"
#include "timer.h"
#include "hw_crc.h"
#include "interrupt.h"
#include "soc_defines.h"
#include "platform.h"
#include "uartStdio.h"
#include "hw_core_cm_core.h"
#include "hw_counter_32k.h"
#include "irq_xbar.h"
#include "crc.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
/* Pre-calculated crc signature value for gievn data pattern */
#define APP_CRC_REFERENCE_SIGN_VAL_L      (0xD5D7103DU)
#define APP_CRC_REFERENCE_SIGN_VAL_H      (0x6370D34EU)

/* Timer frequency */
#define TIMER_FREQUENCY                 (32000U)

/* Frame deatils - used as refeneance data */
#define APP_FRAME_HEIGHT                     ((uint32_t) 1280U)
#define APP_FRAME_WIDTH                      ((uint32_t) 720U)
#define APP_FRAME_PIXEL_SIZE                  ((uint32_t) 2U)

/* CRC configuration parameters */
#define APP_CRC_CHANNEL                      (CRC_CHANNEL_1)
#define APP_CRC_PATTERN_SIZE                  ((uint32_t) 8U)
#define APP_CRC_PATTERN_CNT                                        \
    ((APP_FRAME_HEIGHT * APP_FRAME_WIDTH * APP_FRAME_PIXEL_SIZE) / \
     APP_CRC_PATTERN_SIZE)
#define APP_CRC_SECT_CNT                  ((uint32_t) 1U)
#define APP_CRC_WATCHDOG_PRELOAD_VAL              ((uint32_t) 0U)
#define APP_CRC_BLOCK_PRELOAD_VAL                 ((uint32_t) 0U)
#define APP_CRC_CH_CCITENR_MASK              (CRC_INTR_CH1_CCITENR_MASK)

/* Interation count for checking data integrity */
#define APP_ITERATION_CNT                  (20U)

/* Parameters for registering EDMA interrupt */
#define EDMA3_CC_XFER_COMPLETION_INT_M4                 (34U)
#define EDMA3_CC_XFER_COMPLETION_INT_DSP                (32U)
#define EDMA3_CC_REGION_M4                              (1U)
#define EDMA3_CC_REGION_DSP                             (1U)
#ifdef BUILD_M4
    #define EDMA3_CC_XFER_COMPLETION_INT    (EDMA3_CC_XFER_COMPLETION_INT_M4)
    #define EDMA3_CC_REGION                 (EDMA3_CC_REGION_M4)
    #define XBAR_CPU                        (CPU_IPU1)
    #define XBAR_INST                       (XBAR_INST_IPU1_IRQ_34)
    #define XBAR_INTR_SOURCE                (EDMA_TPCC_IRQ_REGION1)
#elif defined (BUILD_DSP)
    #define SOC_EDMA_TPCC_BASE              (0x43300000U)
    #define EDMA3_CC_XFER_COMPLETION_INT    (EDMA3_CC_XFER_COMPLETION_INT_DSP)
    #define EDMA3_CC_REGION                 (EDMA3_CC_REGION_DSP)
    #define SOC_EMIF1_BASE                  (0x80000000U)
    #define XBAR_CPU                        (CPU_DSP1)
    #define XBAR_INST                       (XBAR_INST_DSP1_IRQ_32)
    #define XBAR_INTR_SOURCE                (EDMA_TPCC_IRQ_REGION1)
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
volatile uint32_t edmaTransferComplete;
uint32_t          edmaEvtqNumber, edmaTCCNumber, edmaChannelNumber,
                  edmaInterruptNumber;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This API to enable the clock for CRC module.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void CRCAppClockEnable(void);
/**
 * \brief   This Interrupt Service Routine for EDMA completion interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void CRCAppEdmaCompletionISR(void *handle);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int main(void)
{
    /* Declaration of variables */
    uint32_t              loopCnt, srcBuffer, edmaRegion,
                          errorFlag;
    uint32_t              transferLoopCnt, frameSize, edmaCCnt;
    uint32_t             *srcMemory;
    uint32_t              timeStampBeforeDMAConfig,
                          timeStampAfterCompleteCompression;
    Float32               completionTime;
    EDMA3CCPaRAMEntry     edmaParam;
    uint32_t              patternCnt, sectCnt, baseAddr;
    uint32_t              watchdogPreloadVal, blockPreloadVal, patternSize;
    crcChannel_t          chNumber;
    crcOperationMode_t    mode;
    crcSignature_t        sectSignVal;
    crcSignatureRegAddr_t psaSignRegAddr;
    Float32               semiCPUPerformance;

    /* Configure UARTStdioInit */
    PlatformUartConsoleSetPinMux();
    UARTStdioInit();
    /* Initialize variables */
    errorFlag        = 0U;
    srcMemory        = (uint32_t *) SOC_EMIF1_BASE;
    srcBuffer        = SOC_EMIF1_BASE;
    sectSignVal.regL = 0U;
    sectSignVal.regH = 0U;

    /* Configure CRC parameters */
    baseAddr           = SOC_CRC_BASE;
    patternSize        = APP_CRC_PATTERN_SIZE;
    patternCnt         = APP_CRC_PATTERN_CNT;
    sectCnt            = APP_CRC_SECT_CNT;
    watchdogPreloadVal = APP_CRC_WATCHDOG_PRELOAD_VAL;
    blockPreloadVal    = APP_CRC_BLOCK_PRELOAD_VAL;
    chNumber           = APP_CRC_CHANNEL;
    mode = CRC_OPERATION_MODE_SEMICPU;
    /* Enable CRC clock */
    CRCAppClockEnable();
    /* Get CRC PSA signature register address */
    CRCGetPSASigRegAddr(baseAddr,
                        chNumber,
                        &psaSignRegAddr);

    frameSize = (APP_FRAME_WIDTH * APP_FRAME_HEIGHT * APP_FRAME_PIXEL_SIZE);

    edmaRegion = EDMA3_CC_REGION;
    EDMAsetRegion(edmaRegion);
    /* Do EDMA init Done once in the beginning of application */
    EDMA3Init(SOC_EDMA_TPCC_BASE, 0);
    /* Enable EDAM completion interrupt */
    edmaInterruptNumber = EDMA3_CC_XFER_COMPLETION_INT;

    /* Unlock the Crossbar register */
    PlatformUnlockMMR();
    if (irq_xbar_success ==
        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                       XBAR_CPU, XBAR_INST,
                       XBAR_INTR_SOURCE))
    {
        /* Successfully configured CrossBar */
    }
    else
    {
        UARTPuts("Error in configuring CrossBar.\n", -1);
    }

    Intc_Init();
    Intc_IntEnable(edmaInterruptNumber);
    Intc_IntRegister(edmaInterruptNumber, (IntrFuncPtr) CRCAppEdmaCompletionISR,
                     NULL);
    Intc_IntPrioritySet(edmaInterruptNumber, 1, 0);
    Intc_SystemEnable(edmaInterruptNumber);

    /* Calculate EDMA cCnt */
    edmaCCnt = 1;
    while (((frameSize / patternSize) / edmaCCnt) > 0xFFFF)
    {
        edmaCCnt = edmaCCnt * 2;
    }
    /* Configure EDMA parameters */
    edmaChannelNumber  = 0x1U;
    edmaEvtqNumber     = 0x0U;
    edmaTCCNumber      = 0x1U;
    edmaParam.opt      = 0U;
    edmaParam.srcAddr  = (uint32_t) srcBuffer;
    edmaParam.destAddr = psaSignRegAddr.regL;
    edmaParam.aCnt     = patternSize;
    edmaParam.bCnt     = patternCnt / edmaCCnt;
    edmaParam.cCnt     = edmaCCnt;
    edmaParam.srcBIdx  = patternSize;
    edmaParam.destBIdx = 0U;
    edmaParam.srcCIdx  = (patternSize * patternCnt / edmaCCnt);
    edmaParam.destCIdx = 0U;
    edmaParam.linkAddr = 0xFFFFU;
    edmaParam.opt     |=
        (EDMA_TPCC_OPT_SYNCDIM_MASK | EDMA3_OPT_TCINTEN_MASK |
         EDMA3_OPT_ITCINTEN_MASK |
         ((edmaTCCNumber << EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));
    /* Initialize source memory with reference data */
    for (loopCnt = 0;
         loopCnt < (frameSize / 4);
         loopCnt++)
    {
        srcMemory[loopCnt] = loopCnt;
    }
    UARTPuts("Copied reference data into DDR memory.\n", -1);
    UARTPuts("Configuring EDMA and CRC for transfer.\n", -1);
    /* Configure CRC channel */
    CRCInitialize(baseAddr,
                  chNumber,
                  watchdogPreloadVal,
                  blockPreloadVal);
    /* Configure EDMA */
    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE,
                        EDMA3_CHANNEL_TYPE_DMA,
                        edmaChannelNumber,
                        edmaTCCNumber,
                        edmaEvtqNumber);
    /* Get time-stamp */
    timeStampBeforeDMAConfig = HW_RD_REG32(SOC_COUNTER_32K_BASE +
                                           COUNTER_32K_CR);
    for (loopCnt = 0U; loopCnt < APP_ITERATION_CNT; loopCnt++)
    {
        /* CRC channel RESET before initialization/configuration */
        CRCChannelReset(baseAddr, chNumber);
        /* Initialize CRC channel */
        CRCConfigure(baseAddr, chNumber, patternCnt, sectCnt, mode);
        EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, edmaChannelNumber, &edmaParam);
        for (transferLoopCnt = 0;
             transferLoopCnt < edmaParam.cCnt;
             transferLoopCnt++)
        {
            edmaTransferComplete = 0;
            EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE,
                                edmaChannelNumber,
                                EDMA3_TRIG_MODE_MANUAL);
            /* Wait for transfer to complete */
            while (edmaTransferComplete != 1)
            {}
            /* Check interrupt status at channel level */
        }

        while ((CRCGetIntrStatus(baseAddr, chNumber) & APP_CRC_CH_CCITENR_MASK)
               != 0x1U)
        {
            /* Wait here till CRC compression complete is set. */
        }

        /* Fetch CRC signature value */
        CRCGetPSASectorSig(baseAddr, chNumber, &sectSignVal);
        /* Compare CRC signature value against reference CRC signature */
        if ((sectSignVal.regH ==
             APP_CRC_REFERENCE_SIGN_VAL_H)
            && (sectSignVal.regL ==
                APP_CRC_REFERENCE_SIGN_VAL_L))
        {
            /* Sector signature matches */
        }
        else
        {
            errorFlag = 1U;
            UARTPuts(
                "Sector signature does not match with pre-calculated value.\n",
                -1);
            break;
        }
        CRCClearIntr(baseAddr,
                     chNumber,
                     CRC_CHANNEL_IRQSTATUS_RAW_MAIN_ALL);
    }

    if (errorFlag == 0U)
    {
        /* Get the time-stamp */
        timeStampAfterCompleteCompression = HW_RD_REG32(
            SOC_COUNTER_32K_BASE +
            COUNTER_32K_CR);
        UARTPuts("CRC signature verification done successfully.\n", -1);
        completionTime = ((Float32)
                          (timeStampAfterCompleteCompression -
                           timeStampBeforeDMAConfig))
                         / (Float32) TIMER_FREQUENCY;
        semiCPUPerformance =
            (Float32) (((Float32) frameSize) / completionTime);
        semiCPUPerformance = ((Float32) semiCPUPerformance) *
                             ((Float32) APP_ITERATION_CNT);
        semiCPUPerformance = (Float32) semiCPUPerformance /
                             (1024U * 1024U);
        UARTprintf("Processed %d frames of size(%d * %d * %d).\n"
                   , APP_ITERATION_CNT, APP_FRAME_HEIGHT,
                   APP_FRAME_WIDTH, APP_FRAME_PIXEL_SIZE);
        UARTprintf("CRC performance: %dMB/s.\n", (uint32_t) semiCPUPerformance);
    }
    else
    {
        UARTPuts("CRC signature verification failed.\n", -1);
    }
    /* Disable the EDMA interrupt */
    Intc_SystemDisable(edmaInterruptNumber);
    Intc_IntUnregister(edmaInterruptNumber);
    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static void CRCAppClockEnable(void)
{
    HW_WR_FIELD32(SOC_CORE_CM_CORE_BASE + CM_CRC_CLKSTCTRL,
                  CM_CRC_CLKSTCTRL_CLKTRCTRL,
                  CM_CRC_CLKSTCTRL_CLKTRCTRL_SW_WKUP);
    HW_WR_FIELD32(SOC_CORE_CM_CORE_BASE + CM_CRC_CRC_CLKCTRL,
                  CM_CRC_CRC_CLKCTRL_MODULEMODE,
                  CM_CRC_CRC_CLKCTRL_MODULEMODE_ENABLE);
}

static void CRCAppEdmaCompletionISR(void *handle)
{
    edmaTransferComplete = 1U;
    EDMA3ClrIntr(SOC_EDMA_TPCC_BASE, edmaTCCNumber);
}

