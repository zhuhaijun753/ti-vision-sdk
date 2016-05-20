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
#include "hw_types.h"
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include "lld_hsi2c_edma.h"
#include "i2clib/lld_hsi2c.h"
#include "edma.h"
#include "interrupt.h"
#include "soc.h"

/******************************************************************************
 *                        MACRO DEFINITIONS
 ******************************************************************************/

/* Edma OPT Field specific defines */

#ifdef TI814X_FAMILY_BUILD
#define EDMA3CC_U_BASE (SOC_EDMA_TPCC_BASE)
#elif (defined (TDA2XX_FAMILY_BUILD)) || (defined (TDA3XX_FAMILY_BUILD))
    #ifdef BUILD_M4
#define EDMA3CC_U_BASE ((uint32_t) 0x63300000U)
    #elif defined (BUILD_A15)
#define EDMA3CC_U_BASE (SOC_EDMA_TPCC_BASE)
    #else
/* Edma Base Address for DSP Core on Vayu/ADASLO */
#define EDMA3CC_U_BASE ((uint32_t) 0x43300000U)
    #endif
#endif

#define EDMA3CC_IPR_OFFSET  ((uint32_t) EDMA_TPCC_IPR)
#define EDMA3CC_IPRH_OFFSET ((uint32_t) EDMA_TPCC_IPRH)

#define EDMA3CC_ICR_OFFSET  ((uint32_t) EDMA_TPCC_ICR)
#define EDMA3CC_ICRH_OFFSET ((uint32_t) EDMA_TPCC_ICRH)

#define LLD_I2C_EDMA_OPT_SYNCDIM_SHIFT      ((uint32_t) 0x00000002U)
#define LLD_I2C_EDMA_OPT_TCC_MASK           ((uint32_t) 0x0003F000U)
#define LLD_I2C_EDMA_OPT_TCC_SHIFT          ((uint32_t) 0x0000000CU)
#define LLD_I2C_EDMA_OPT_ITCINTEN_SHIFT     ((uint32_t) 0x00000015U)
#define LLD_I2C_EDMA_OPT_TCINTEN_SHIFT      ((uint32_t) 0x00000014U)

#ifdef TI814X_FAMILY_BUILD
#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_3_MASK ((uint32_t) 0x3F000000U)
#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_3_SHIFT ((uint32_t) 0x00000018U)
#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_3_RESETVAL ((uint32_t) 0x00000000U)

#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_2_MASK ((uint32_t) 0x003F0000U)
#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_2_SHIFT ((uint32_t) 0x00000010U)
#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_2_RESETVAL ((uint32_t) 0x00000000U)

#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_MASK ((uint32_t) 0x00003F00U)
#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_SHIFT ((uint32_t) 0x00000008U)
#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_RESETVAL ((uint32_t) 0x00000000U)

#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_MASK ((uint32_t) 0x0000003FU)
#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_SHIFT ((uint32_t) 0x00000000U)
#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_RESETVAL ((uint32_t) 0x00000000U)

#define EDMA3_MAX_CROSS_BAR_EVENTS_TI814X  ((uint32_t) 95U)

/*Cross Bar mapped*/
#define LLD_I2C_EDMA_CHA_I2CTXEVT2_XBAR    ((uint32_t) 3U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT2_XBAR    ((uint32_t) 4U)

#define LLD_I2C_EDMA_CHA_I2CTXEVT3_XBAR    ((uint32_t) 5U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT3_XBAR    ((uint32_t) 6U)

typedef struct  {
    volatile uint32_t DSP_INTMUX[21];
    volatile uint32_t DUCATI_INTMUX[15];
    volatile uint32_t TPCC_EVTMUX[16];
    volatile uint32_t TIMER_EVTCAPT;
    volatile uint32_t GPIO_MUX;
} CSL_IntmuxRegs;

typedef volatile CSL_IntmuxRegs *CSL_IntmuxRegsOvly;

#endif

#ifdef TDA2XX_FAMILY_BUILD
#define LLD_I2C_EDMA_CHA_I2CTXEVT3_XBAR    ((uint32_t) 3U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT3_XBAR    ((uint32_t) 4U)
#define LLD_I2C_EDMA_CHA_I2CTXEVT4_XBAR    ((uint32_t) 5U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT4_XBAR    ((uint32_t) 6U)
#if defined (TDA2EX_BUILD)
#define LLD_I2C_EDMA_CHA_I2CTXEVT5_XBAR    ((uint32_t) 7U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT5_XBAR    ((uint32_t) 8U)
#endif
#endif

static lldHsi2cEdmaCallback callbackFn;

/******************************************************************************
 *                        Local Function Declarations
 ******************************************************************************/
#ifdef TI814X_FAMILY_BUILD
static uint32_t sampleConfigScr(uint32_t eventNum, uint32_t chanNum);

/**
 * \brief   sampleConfigScr
 *
 * This function configures control config registers for the cross bar events
 * mapped to the EDMA channel.
 *
 * \return  EDMA3_DRV_SOK if success, else error code
 */
static uint32_t sampleConfigScr(uint32_t eventNum, uint32_t chanNum)
{
    uint32_t           retVal        = TRUE;
    uint32_t           scrChanOffset = 0;
    uint32_t           scrRegOffset  = 0;
    uint32_t           xBarEvtNum    = 0;
    CSL_IntmuxRegsOvly scrEvtMux     = (CSL_IntmuxRegsOvly) (0x48140F00U);

    if ((eventNum < EDMA3_MAX_CROSS_BAR_EVENTS_TI814X) &&
        (chanNum < EDMA3_NUM_TCC))
    {
        scrRegOffset  = chanNum / 4U;
        scrChanOffset = chanNum - (scrRegOffset * 4U);
        xBarEvtNum    = (eventNum - EDMA3_NUM_TCC) + 1U;

        switch (scrChanOffset)
        {
            case 0:
                scrEvtMux->TPCC_EVTMUX[scrRegOffset] |=
                    (xBarEvtNum & CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_MASK);
                break;
            case 1U:
                scrEvtMux->TPCC_EVTMUX[scrRegOffset] |=
                    ((xBarEvtNum <<
                      CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_SHIFT) &
                     (CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_MASK));
                break;
            case 2U:
                scrEvtMux->TPCC_EVTMUX[scrRegOffset] |=
                    ((xBarEvtNum <<
                      CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_2_SHIFT) &
                     (CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_2_MASK));
                break;
            case 3U:
                scrEvtMux->TPCC_EVTMUX[scrRegOffset] |=
                    ((xBarEvtNum <<
                      CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_3_SHIFT) &
                     (CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_3_MASK));
                break;
            default:
                retVal = (UInt32) FALSE;
                break;
        }
    }
    else
    {
        retVal = (UInt32) FALSE;
    }

    return retVal;
}

#endif

#ifndef OMAP5X_FAMILY_BUILD
void EDMA_callbackFn(void *arg)
{
    uint32_t regVal, tcc, i;
    LLD_hsi2cEdmaStatus i2cEdmaErrStatus = EDMA_TRANSFER_SUCCESS;

#ifdef TI814X_FAMILY_BUILD
    regVal = HW_RD_REG32(EDMA3CC_U_BASE + EDMA3CC_IPR_OFFSET);
    for (i = 0; i < 4U; i++)
    {
        if ((uint32_t) 0U !=
            (regVal & ((uint32_t) 1U << (LLD_I2C_EDMA_CHA_I2CTXEVT2_XBAR + i))))
        {
            tcc = LLD_I2C_EDMA_CHA_I2CTXEVT2_XBAR + i;

            tcc += 63U;

            /*I2C LLD EDMA call back function should be called here*/
            callbackFn(tcc, i2cEdmaErrStatus, arg);

            HW_WR_REG32(
                EDMA3CC_U_BASE + EDMA3CC_ICR_OFFSET,
                (uint32_t) 1U << (LLD_I2C_EDMA_CHA_I2CTXEVT2_XBAR + i));
        }
    }

    regVal = HW_RD_REG32(EDMA3CC_U_BASE + EDMA3CC_IPRH_OFFSET);
    for (i = 0; i < 4U; i++)
    {
        if ((uint32_t) 0U !=
            (regVal & ((uint32_t) 1U << ((LLD_I2C_EDMA_CHA_I2CTXEVT0 - 32U) + i))))
        {
            tcc = LLD_I2C_EDMA_CHA_I2CTXEVT0 + i;

            /*I2C LLD EDMA call back function should be called here*/
            callbackFn(tcc, i2cEdmaErrStatus, arg);

            HW_WR_REG32(
                EDMA3CC_U_BASE + EDMA3CC_ICRH_OFFSET,
                (uint32_t) 1U << ((LLD_I2C_EDMA_CHA_I2CTXEVT0 - 32U) + i));
        }
    }
#endif

#ifdef TDA2XX_FAMILY_BUILD
    regVal = HW_RD_REG32(EDMA3CC_U_BASE + EDMA3CC_IPR_OFFSET);
    for (i = 0; i < 6U; i++)
    {
        if ((uint32_t) 0U !=
            (regVal & ((uint32_t) 1U << (LLD_I2C_EDMA_CHA_I2CTXEVT2 + i))))
        {
            tcc = LLD_I2C_EDMA_CHA_I2CTXEVT2 + i;

            /*I2C LLD EDMA call back function should be called here*/
            callbackFn(tcc, i2cEdmaErrStatus, arg);

            HW_WR_REG32(
                EDMA3CC_U_BASE + EDMA3CC_ICR_OFFSET,
                (uint32_t) 1U << (LLD_I2C_EDMA_CHA_I2CTXEVT2 + i));
        }
    }
    regVal = HW_RD_REG32(EDMA3CC_U_BASE + EDMA3CC_IPR_OFFSET);
    for (i = 0; i < 4U; i++)
    {
        if ((uint32_t) 0U !=
            (regVal & ((uint32_t) 1U << (LLD_I2C_EDMA_CHA_I2CTXEVT3_XBAR + i))))
        {
            tcc = LLD_I2C_EDMA_CHA_I2CTXEVT3_XBAR + i;

            /*I2C LLD EDMA call back function should be called here*/
            callbackFn(tcc, i2cEdmaErrStatus, arg);

            HW_WR_REG32(
                EDMA3CC_U_BASE + EDMA3CC_ICR_OFFSET,
                (uint32_t) 1U << (LLD_I2C_EDMA_CHA_I2CTXEVT3_XBAR + i));
        }
    }

#endif
#ifdef TDA3XX_FAMILY_BUILD
    regVal = HW_RD_REG32(EDMA3CC_U_BASE + EDMA3CC_IPR_OFFSET);
    for (i = 0; i < 4U; i++)
    {
        if ((uint32_t) 0U !=
            (regVal & ((uint32_t) 1U << (LLD_I2C_EDMA_CHA_I2CTXEVT0 + i))))
        {
            tcc = LLD_I2C_EDMA_CHA_I2CTXEVT0 + i;

            /*I2C LLD EDMA call back function should be called here*/
            callbackFn(tcc, i2cEdmaErrStatus, arg);

            HW_WR_REG32(
                EDMA3CC_U_BASE + EDMA3CC_ICR_OFFSET,
                (uint32_t) 1U << (LLD_I2C_EDMA_CHA_I2CTXEVT0 + i));
        }
    }
#endif
}

#endif

LLD_hsi2cEdmaStatus EDMA_requestChannel(hsI2cHandle          handle,
                                        uint32_t            *i2cEventNo,
                                        lldHsi2cEdmaCallback i2cCallback,
                                        void                *edmaParam)
{
#if (defined (TI814X_FAMILY_BUILD)) || (defined (TDA2XX_FAMILY_BUILD))
    uint32_t chanNum = 0;
#elif (defined (TDA3XX_FAMILY_BUILD))
    uint32_t chanNum = *i2cEventNo;
#endif
    LLD_hsi2cEdmaParam *edmaParams    = (LLD_hsi2cEdmaParam *) edmaParam;
    LLD_hsi2cEdmaStatus i2cEdmaStatus = EDMA_TRANSFER_SUCCESS;

    callbackFn = i2cCallback;

#if (defined (TI814X_FAMILY_BUILD)) || (defined (TDA2XX_FAMILY_BUILD))
    if (*i2cEventNo >= EDMA3_NUM_TCC)
    {
        switch (*i2cEventNo)
        {
#ifdef TI814X_FAMILY_BUILD
            case LLD_I2C_EDMA_CHA_I2CTXEVT2:
                chanNum = LLD_I2C_EDMA_CHA_I2CTXEVT2_XBAR;
                break;
            case LLD_I2C_EDMA_CHA_I2CRXEVT2:
                chanNum = LLD_I2C_EDMA_CHA_I2CRXEVT2_XBAR;
                break;
#endif
            case LLD_I2C_EDMA_CHA_I2CTXEVT3:
                chanNum = LLD_I2C_EDMA_CHA_I2CTXEVT3_XBAR;
                break;
            case LLD_I2C_EDMA_CHA_I2CRXEVT3:
                chanNum = LLD_I2C_EDMA_CHA_I2CRXEVT3_XBAR;
                break;
#ifdef TDA2XX_FAMILY_BUILD
            case LLD_I2C_EDMA_CHA_I2CTXEVT4:
                chanNum = LLD_I2C_EDMA_CHA_I2CTXEVT4_XBAR;
                break;
            case LLD_I2C_EDMA_CHA_I2CRXEVT4:
                chanNum = LLD_I2C_EDMA_CHA_I2CRXEVT4_XBAR;
                break;
#if defined (TDA2EX_BUILD)
            case LLD_I2C_EDMA_CHA_I2CTXEVT5:
                chanNum = LLD_I2C_EDMA_CHA_I2CTXEVT5_XBAR;
                break;
            case LLD_I2C_EDMA_CHA_I2CRXEVT5:
                chanNum = LLD_I2C_EDMA_CHA_I2CRXEVT5_XBAR;
                break;
#endif
#endif
            default:
                break;
        }

#ifdef TI814X_FAMILY_BUILD
        if (TRUE == sampleConfigScr(*i2cEventNo, chanNum))
        {
            *i2cEventNo = chanNum;
        }
        else
        {
            i2cEdmaStatus = EDMA_TRANSFER_FAIL;
        }
#else
        *i2cEventNo = chanNum;
#endif
    }
#endif

#ifdef TDA3XX_FAMILY_BUILD
    *i2cEventNo = chanNum;
#endif

    if (TRUE !=
        EDMA3RequestChannel(edmaParams->baseAddr,
                            EDMA3_CHANNEL_TYPE_DMA,
                            *i2cEventNo,
                            *i2cEventNo,
                            edmaParams->eventQueue))
    {
        i2cEdmaStatus = EDMA_TRANSFER_FAIL;
    }

    return i2cEdmaStatus;
}

LLD_hsi2cEdmaStatus EDMA_freeChannel(uint32_t i2cEventNo, void *edmaParam)
{
    LLD_hsi2cEdmaStatus status     = EDMA_TRANSFER_SUCCESS;
    LLD_hsi2cEdmaParam *edmaParams = (LLD_hsi2cEdmaParam *) edmaParam;

    if (TRUE !=
        (EDMA3FreeChannel(edmaParams->baseAddr,
                          EDMA3_CHANNEL_TYPE_DMA,
                          i2cEventNo,
                          EDMA3_TRIG_MODE_EVENT,
                          i2cEventNo,
                          edmaParams->eventQueue)))
    {
        status = EDMA_TRANSFER_FAIL;
    }

    return status;
}

LLD_hsi2cEdmaStatus EDMA_disableLogicalChannel(uint32_t tcc, void *edmaParam)
{
    LLD_hsi2cEdmaStatus status     = EDMA_TRANSFER_SUCCESS;
    LLD_hsi2cEdmaParam *edmaParams = (LLD_hsi2cEdmaParam *) edmaParam;

    EDMA3DisableDmaEvt(edmaParams->baseAddr, tcc);

    return status;
}

LLD_hsi2cEdmaStatus EDMA_clearErrorBits(uint32_t tcc, void *edmaParam)
{
    LLD_hsi2cEdmaStatus status     = EDMA_TRANSFER_SUCCESS;
    LLD_hsi2cEdmaParam *edmaParams = (LLD_hsi2cEdmaParam *) edmaParam;

    EDMA3ClearErrorBits(edmaParams->baseAddr, tcc, edmaParams->eventQueue);

    return status;
}

LLD_hsi2cEdmaStatus EDMA_setPaRAM(const void *srcPtr, const void *dstPtr,
                                  uint32_t rdWrflag,
                                  uint32_t chan, uint32_t bufLen,
                                  void *edmaParam,
                                  uint8_t fifoThreshold)
{
    uint16_t            srcIndex   = 0U;
    uint16_t            dstIndex   = 1U;
    LLD_hsi2cEdmaStatus status     = EDMA_TRANSFER_SUCCESS;
    LLD_hsi2cEdmaParam *edmaParams = (LLD_hsi2cEdmaParam *) edmaParam;
    EDMA3CCPaRAMEntry   i2cEdmaParam;

    i2cEdmaParam.opt = 0U;
    if (LLD_HSI2C_WRITE == rdWrflag)
    {
        srcIndex = 1U;
        dstIndex = 0U;

        i2cEdmaParam.srcCIdx  = fifoThreshold;
        i2cEdmaParam.destCIdx = 0U;
    }
    else
    {
        i2cEdmaParam.srcCIdx  = 0U;
        i2cEdmaParam.destCIdx = fifoThreshold;
    }

    i2cEdmaParam.srcAddr  = (uint32_t) srcPtr;
    i2cEdmaParam.destAddr = (uint32_t) dstPtr;
    i2cEdmaParam.aCnt     = 0x1U;

    if (bufLen >= (uint32_t) fifoThreshold)
    {
        i2cEdmaParam.bCnt =
            ((uint16_t) ((uint32_t) 0xFFFFU & (uint32_t) fifoThreshold));
        i2cEdmaParam.cCnt =
            ((uint16_t) ((uint32_t) 0xFFFFU &
                         (bufLen / (uint32_t) fifoThreshold)));
    }
    else
    {
        i2cEdmaParam.bCnt = ((uint16_t) 0xFFFFU & bufLen);
        i2cEdmaParam.cCnt = 1U;
    }

    i2cEdmaParam.srcBIdx  = srcIndex;
    i2cEdmaParam.destBIdx = dstIndex;

    i2cEdmaParam.linkAddr   = 0xFFFFU;
    i2cEdmaParam.bCntReload = 0U;
    i2cEdmaParam.opt       &= (uint32_t) 0xFFFFFFFCU;

    /* FIFO width is 8 bit                                                */
    i2cEdmaParam.opt &= (uint32_t) 0xFFFFF8FFU;

    /* EDMA3_DRV_SYNC_AB                                                  */
    i2cEdmaParam.opt |= (uint32_t) 0x04U;

    /* EDMA3_DRV_OPT_FIELD_TCINTEN                                        */
    i2cEdmaParam.opt |= ((uint32_t) 1U << LLD_I2C_EDMA_OPT_TCINTEN_SHIFT);

    /* update the transfer completion code                                */
    i2cEdmaParam.opt &= (~LLD_I2C_EDMA_OPT_TCC_MASK);
    i2cEdmaParam.opt |= (chan << LLD_I2C_EDMA_OPT_TCC_SHIFT);

    EDMA3SetPaRAM(edmaParams->baseAddr, chan, &i2cEdmaParam);

    return status;
}

LLD_hsi2cEdmaStatus EDMA_enableTransfer(uint32_t chan, void *edmaParam)
{
    LLD_hsi2cEdmaStatus edmaStatus = EDMA_TRANSFER_SUCCESS;
    uint32_t status;
    LLD_hsi2cEdmaParam *edmaParams = (LLD_hsi2cEdmaParam *) edmaParam;

    status = EDMA3EnableTransfer(edmaParams->baseAddr, chan,
                                 EDMA3_TRIG_MODE_EVENT);
    if (FALSE == status)
    {
        edmaStatus = EDMA_TRANSFER_FAIL;
    }
    return edmaStatus;
}

