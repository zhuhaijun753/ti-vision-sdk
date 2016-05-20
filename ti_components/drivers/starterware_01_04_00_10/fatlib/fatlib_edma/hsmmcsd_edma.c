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
/**
 *   Component:     fatlib_edma
 *
 *   Filename:      hsmmcsd_edma.c
 *
 *   Description:   This file contain SD API to configure the edma channel using
 *                  starterware EDMA API
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <common/stw_dataTypes.h>
#include <soc.h>
#include <soc_defines.h>
#include <platform.h>
#include <edma.h>
#include <hsmmcsd_edma.h>
#ifdef TDA2XX_FAMILY_BUILD
#include <dma_xbar.h>
#endif
#if DEBUG
#include "uartStdio.h"
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static uint32_t hsmmcsdEdmaSetParam(uint32_t baseAddr,
                                    uint32_t srcBfr,
                                    uint32_t dstBfr,
                                    uint32_t chan,
                                    uint32_t bufLen,
                                    uint32_t blockSize,
                                    uint32_t rwflag);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

uint32_t HSMMCSDEdmaCopy(const hsmmcsdEdmaParam_t *pEdmaParam)
{
    EDMA3CCPaRAMEntry edmaParam;
    uint32_t          retVal = 0;
    uint32_t          intStatus = 0;

#ifdef TDA2XX_FAMILY_BUILD
    dma_xbar_ret_type_t status;
#endif

    /* Configure & enable the MMMCSD edma channel */

    /* Request the channel */
    retVal = EDMA3RequestChannel(pEdmaParam->baseAddr, EDMA3_CHANNEL_TYPE_DMA,
                                 pEdmaParam->chan, pEdmaParam->chan,
                                 0);
    if (retVal != TRUE)
    {
        return FALSE;
    }

#ifdef TDA2XX_FAMILY_BUILD
    /* DMA XBar instance number is (channel number +1) in this case.
     * This might be different in other cases. Please refer TRM.
     */
    status = DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                            EDMA, pEdmaParam->chan + 1,
                            (xbar_evt_t) (pEdmaParam->dreq + 1));
    if (status != dma_xbar_success)
    {
        return FALSE;
    }
#endif

    /* Configure the ParamSet */
    edmaParam.opt        = 0;
    edmaParam.srcAddr    = pEdmaParam->srcBfr;
    edmaParam.destAddr   = pEdmaParam->dstBfr;
    edmaParam.aCnt       = pEdmaParam->length;
    edmaParam.bCnt       = 1;
    edmaParam.cCnt       = 1;
    edmaParam.linkAddr   = 0xFFFF;
    edmaParam.opt       |=
        (EDMA_TPCC_OPT_TCINTEN_MASK |
         ((pEdmaParam->chan <<
           EDMA_TPCC_OPT_TCC_SHIFT) &
          EDMA_TPCC_OPT_TCC_MASK) | EDMA_TPCC_OPT_SYNCDIM_MASK);

    EDMA3SetPaRAM(pEdmaParam->baseAddr, pEdmaParam->chan, &edmaParam);

    /* Enable Edma Transfer*/
    retVal = EDMA3EnableTransfer(pEdmaParam->baseAddr, pEdmaParam->chan,
                                 EDMA3_TRIG_MODE_MANUAL);

    /* Wait for completion */
    do {
        if (pEdmaParam->chan < 32U)
        {
            intStatus = (EDMA3GetIntrStatus(pEdmaParam->baseAddr)
                            >> pEdmaParam->chan) & 1;
        }
        else
        {
            intStatus = (EDMA3IntrStatusHighGet(pEdmaParam->baseAddr)
                            >> (pEdmaParam->chan - 32U)) & 1;
        }
    } while(intStatus == 0);

    HSMMCSDEdmaClose(pEdmaParam);

    return retVal;
}

uint32_t HSMMCSDEdmaTransfer(const hsmmcsdEdmaParam_t *pEdmaParam)
{
    uint32_t retVal;
#ifdef TDA2XX_FAMILY_BUILD
    dma_xbar_ret_type_t status;
#endif

    /* Configure & enable the MMMCSD edma channel */

    /* Request the channel */
    retVal = EDMA3RequestChannel(pEdmaParam->baseAddr, EDMA3_CHANNEL_TYPE_DMA,
                                 pEdmaParam->chan, pEdmaParam->chan,
                                 0);
    if (retVal != TRUE)
    {
        return FALSE;
    }

#ifdef TDA2XX_FAMILY_BUILD
    /* DMA XBar instance number is (channel number +1) in this case.
     * This might be different in other cases. Please refer TRM.
     */
    status = DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                            EDMA, pEdmaParam->chan + 1,
                            (xbar_evt_t) (pEdmaParam->dreq + 1));
    if (status != dma_xbar_success)
    {
        return FALSE;
    }
#endif

    /* Configure the ParamSet */
    hsmmcsdEdmaSetParam(pEdmaParam->baseAddr, pEdmaParam->srcBfr,
                        pEdmaParam->dstBfr,
                        pEdmaParam->chan, pEdmaParam->length,
                        pEdmaParam->blockSize,
                        pEdmaParam->rwflag);

    /* Enable Edma Transfer*/

    retVal = EDMA3EnableTransfer(pEdmaParam->baseAddr, pEdmaParam->chan,
                                 EDMA3_TRIG_MODE_EVENT);

    return retVal;
}

uint32_t HSMMCSDEdmaClose(const hsmmcsdEdmaParam_t *pEdmaParam)
{
    /* Disable the MMCSD edma channel */
#ifdef TDA2XX_FAMILY_BUILD

    /* Disconnect the event source & channel map */
    DMAXBARDisconnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, EDMA,
                      pEdmaParam->chan + 1);
#endif

    /* Disable the EDMA event interrupt */
    EDMA3DisableEvtIntr(pEdmaParam->baseAddr, pEdmaParam->chan);

    /* Clear the interrupt status */
    EDMA3ClrIntr(pEdmaParam->baseAddr, pEdmaParam->chan);

    /* Free the edma channel */
    EDMA3FreeChannel(pEdmaParam->baseAddr, EDMA3_CHANNEL_TYPE_DMA,
                     pEdmaParam->chan,
                     EDMA3_TRIG_MODE_EVENT, pEdmaParam->chan, 0);

    /* Clear the status & error bits */
    EDMA3ClearErrorBits(pEdmaParam->baseAddr, pEdmaParam->chan,
                        pEdmaParam->chan);

    return 1;
}

void HSMMCSDEdmaWaitTransfer(uint32_t edmaChan)
{
    volatile uint32_t iprBit;

    /* wait for DMA complete */
    do
    {
        if (edmaChan < 31)
        {
            iprBit = EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE) & (1 << edmaChan);
        }
        else
        {
            iprBit = EDMA3IntrStatusHighGet(SOC_EDMA_TPCC_BASE) &
                        (1 << (edmaChan - 32));
        }
    } while (!iprBit);

    return;
}

void HSMMCSDUartPuts(const char *string)
{
#if DEBUG
    UARTPuts(string, -1);
#endif
}

void HSMMCSDUARTPutNum(int32_t value)
{
#if DEBUG
    UARTPutNum(value);
#endif
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/**
 * \brief   This function is derive the ParamSet values & configure edma
 *            PaRAM set registers
 *
 * \param   baseAddr  EDMA base addr
 * \param   srcBfr       mmcsd data buffer address
 * \param   dstBfr       application destination buffer address
 * \param   chan        edma logical channel event get triggerred
 * \param   bufLen      data buffer size to transfer
 * \param   blockSize   size of single block or frame
 * \param   rwflag      indicating if transfer is a card FLAG_READ or FLAG_WRITE
 *
 * \returns error status.If error has occured it returns a non zero value.
 *             If no error has occured then return status will be zero.
 */
static uint32_t hsmmcsdEdmaSetParam(uint32_t baseAddr,
                                    uint32_t srcBfr,
                                    uint32_t dstBfr,
                                    uint32_t chan,
                                    uint32_t bufLen,
                                    uint32_t blockSize,
                                    uint32_t rwflag)
{
    EDMA3CCPaRAMEntry edmaParam;
    uint32_t          aCntValue, bCntValue, cCntValue;
    uint32_t          retVal = 0;

    /*calculate the aCnt, bCnt & cCnt values for AB-SYNC mode*/
    if (bufLen < blockSize)
    {
        aCntValue = 4;
        bCntValue = bufLen / 4;
        cCntValue = 1;
    }
    else
    {
        aCntValue = 4;
        bCntValue = blockSize / 4;
        cCntValue = bufLen / blockSize;
    }

    /* Program the PaRam set*/
    edmaParam.opt        = 0;
    edmaParam.srcAddr    = srcBfr;
    edmaParam.destAddr   = dstBfr;
    edmaParam.aCnt       = aCntValue;
    edmaParam.bCnt       = bCntValue;
    edmaParam.cCnt       = cCntValue;
    if(rwflag == FLAG_READ)
    {
        edmaParam.srcBIdx    = 0;
        edmaParam.destBIdx   = 4;
        edmaParam.srcCIdx    = 0;
        edmaParam.destCIdx   = aCntValue * bCntValue;
    }
    else
    {
        edmaParam.srcBIdx    = 4;
        edmaParam.destBIdx   = 0;
        edmaParam.srcCIdx    = aCntValue * bCntValue;
        edmaParam.destCIdx   = 0;
    }
    edmaParam.bCntReload = bCntValue;
    edmaParam.linkAddr   = 0xFFFF;
    edmaParam.opt       |=
        (EDMA_TPCC_OPT_TCINTEN_MASK |
         ((chan <<
           EDMA_TPCC_OPT_TCC_SHIFT) &
          EDMA_TPCC_OPT_TCC_MASK) | EDMA_TPCC_OPT_SYNCDIM_MASK);

    EDMA3SetPaRAM(baseAddr, chan, &edmaParam);

    return retVal;
}
