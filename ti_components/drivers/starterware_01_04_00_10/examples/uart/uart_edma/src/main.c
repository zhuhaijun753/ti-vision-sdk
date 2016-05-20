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
#include "stdio.h"
#include "soc.h"
#include "hw_types.h"
#include "soc_defines.h"
#include "platform.h"
#include "uartConfig.h"
#include "interrupt.h"
#include "edma.h"
#include "dma_xbar.h"
#include "irq_xbar.h"
#include "hw_ctrl_core_pad_io.h"
#include "common/stw_dataTypes.h"
#include <common/stw_types.h>
#include "i2clib/lld_hsi2c.h"
#include "boards/stw_board.h"
#include "platforms/stw_platform.h"
#include "devices/stw_device.h"
#include "stw_boardPriv.h"
#include "pmhal_prcm.h"
#include "pm/pmhal/pmhal_mm.h"

/****************************************************************************/
/*                      INTERNAL MACROS                                     */
/****************************************************************************/
/* EDMA3 Event queue number. */
#define EVT_QUEUE_NUM                       (0U)

/* PaRAM Set number for Dummy Transfer. */
#define DUMMY_CH_NUM                        (5U)

/* Wrapper Definitions. */
#if defined (TDA2XX_FAMILY_BUILD)
#define EDMA3_UART_TX_CHA_NUM               EDMA3_UART1_TX_CHA_NUM
#define EDMA3_UART_RX_CHA_NUM               EDMA3_UART1_RX_CHA_NUM
#elif defined (TDA3XX_FAMILY_BUILD)
#define EDMA3_UART_TX_CHA_NUM               EDMA3_UART3_TX_CHA_NUM
#define EDMA3_UART_RX_CHA_NUM               EDMA3_UART3_RX_CHA_NUM
#endif
#if 0
#define EDMA3_UART1_TX_CHA_NUM               (48U)
#define EDMA3_UART1_RX_CHA_NUM               (49U)
#else
#define EDMA3_UART1_TX_CHA_NUM               (26U)
#define EDMA3_UART1_RX_CHA_NUM               (27U)
#endif

#if 0
#define EDMA3_UART3_TX_CHA_NUM               (52U)
#define EDMA3_UART3_RX_CHA_NUM               (53U)
#else // Todo Need To debug
#define EDMA3_UART3_TX_CHA_NUM               (26U)
#define EDMA3_UART3_RX_CHA_NUM               (27U)
#endif

#ifdef BUILD_A15

/* EDMA3 TPCC region. */
#define EDMA3_CC_REGION                     (0U)

/* EDMA3 interrupt number. */
#define EDMA3_CC_XFER_COMPLETION_INT        (12U)

/* EDMA3 error interrupt number. */
#define EDMA3_CC_XFER_ERROR_INT             (25U)

#elif defined (BUILD_M4)

/* EDMA3 TPCC region. */
#define EDMA3_CC_REGION                     (1U)

/* EDMA3 interrupt number. */
#define EDMA3_CC_XFER_COMPLETION_INT        (34U)

/* EDMA3 error interrupt number. */
#define EDMA3_CC_XFER_ERROR_INT             (35U)

#endif

/* EDMA region 0x43300000 mapped to 0x63300000 for M4. */
#ifndef SOC_EDMA_TPCC_BASE
#if defined (BUILD_M4)
#define SOC_EDMA_TPCC_BASE      (0x63300000U)
#endif
#endif

/******************* Transmit related definitions  **************************/
/*
** Transmit DMA Threshold Value. This is set in TX_DMA_THRESHOLD register.
*/
#define TX_DMA_THRESHOLD                    (5U)

/*
** Transmit Trigger Space value. Use this if TX Trigger Level granularity
** is selected to be 1.
*/
#define TX_TRIGGER_SPACE_GRAN_1             (8U)

/* Number of bytes transmitted by EDMA per TX event sent by UART. */
#define TX_BYTES_PER_EVENT                  (8U)

/******************* Receive related definitions  ***************************/
/* Receiver Buffer Size. */
#define RX_BUFFER_SIZE                      (50U)

/* Receive DMA Threshold Value. */
#define RX_DMA_THRESHOLD                    (8U)

/* Number of bytes to be received from the user. */
#define NUM_RX_BYTES              (8)

/******************* DMA XBAR related definitions  ***************************/
/* DMA XBAR Instance for UART1/UART3 Tx/RX. Refer TRM for DMA XBAR instance
 *numbers.*/
#if 0
#define DMA_XBAR_INST_49            (49U)  /*UART1 TX*/
#define DMA_XBAR_INST_50            (50U)  /*UART1 RX*/
#else
#define DMA_XBAR_INST_49            (27U)  /*UART1 TX*/
#define DMA_XBAR_INST_50            (28U)  /*UART1 RX*/
#endif

#if 0
#define DMA_XBAR_INST_53            (53U)  /*UART3 TX*/
#define DMA_XBAR_INST_54            (54U)  /*UART3 RX*/
#else // Todo Need To debug
#define DMA_XBAR_INST_53            (27U)  /*UART3 TX*/
#define DMA_XBAR_INST_54            (28U)  /*UART3 RX*/
#endif

/****************************************************************************/
/*                      LOCAL FUNCTION PROTOTYPES                           */
/****************************************************************************/
static void UARTTxEDMAPaRAMSetConfig(unsigned char *txBuffer,
                                     uint32_t       length,
                                     uint32_t       tccNum,
                                     uint32_t       linkAddr,
                                     uint32_t       chNum);
static void UARTRxEDMAPaRAMSetConfig(unsigned char *rxBuffer,
                                     uint32_t       length,
                                     uint32_t       tccNum,
                                     uint32_t       linkAddr,
                                     uint32_t       chNum);

static void Edma3INTCConfigure(void);
static void UartInitialize(void);
static void UartFIFOConfigure(void);
static void UartBaudRateSet(void);
static void callback(uint32_t tccNum);
static void Edma3CompletionIsr(void *handle);
static void TxDummyPaRAMConfEnable(void);
static void Edma3ErrorIsr(void *handle);
static void EdmaEvtConfigure(void);

/****************************************************************************/
/*                      GLOBAL VARIABLES                                    */
/****************************************************************************/
static void(*cb_Fxn[EDMA3_NUM_TCC]) (uint32_t tcc);
unsigned char     intent[] =
    "The application echoes the characters that you type on the console.\n";
unsigned char     welcome[]  = "StarterWare UART DMA application.\n";
unsigned char     enter[]    = "Please Enter 08 bytes from keyboard.\n";
volatile uint32_t clBackFlag = 0;

unsigned char     rxBuffer[RX_BUFFER_SIZE];
/*
** Transmit Trigger Space value. This is applicable only when UART FIFO mode
** is used. Refer to the comments of the API UARTFIFOConfig() to find the
** possible values of TX Trigger Space.
*/
uint32_t          txTrigSpace = TX_TRIGGER_SPACE_GRAN_1;

/*
** Number of bytes transmitted by EDMA per TX event sent by UART.
** In UART FIFO mode, this should be equal to the TX Trigger Space value.
*/
uint32_t          txBytesPerEvent = TX_BYTES_PER_EVENT;

/*
** Receive DMA Thresold Level. This applies to both UART FIFO and Non-FIFO
** modes of operation. For FIFO mode, refer to the comments of the API
** UARTFIFOConfig() to find the possible values of RX Trigger Level.
** For Non-FIFO mode, this value is 1.
*/
uint32_t          rxTrigLevel = RX_DMA_THRESHOLD;

/* Transmit DMA Threshold Level. This is set in TX_DMA_THRESHOLD register. */
uint32_t          txThreshLevel = TX_DMA_THRESHOLD;
uint32_t          uartBaseAddr;
/****************************************************************************/
/*                   LOCAL FUNCTION DEFINITIONS                             */
/****************************************************************************/

int main(void)
{
    uint32_t numByteChunks           = 0;
    unsigned char           *pBuffer = NULL;
    uint32_t remainBytes = 0;
    uint32_t uartInstId;
    pmhalPrcmModuleId_t pmModInstId;
    int32_t  retVal = STW_SOK;

    uartInstId   = 1;
    uartBaseAddr = SOC_UART1_BASE;
    pmModInstId  = PMHAL_PRCM_MOD_UART1;

#if defined (TDA3XX_FAMILY_BUILD)
    uartInstId   = 3;
    uartBaseAddr = SOC_UART3_BASE;
    pmModInstId  = PMHAL_PRCM_MOD_UART3;
#endif

    /*Enable the module - uart*/
    retVal = PMHALModuleModeSet(pmModInstId,
                                PMHAL_PRCM_MODULE_MODE_ENABLED,
                                PM_TIMEOUT_INFINITE);
    if (retVal != PM_SUCCESS)
    {
        return STW_EFAIL;
    }

    /* PinMux Configuration for UART*/
    BOARDConfigConsolePinMux(uartInstId);

    /*Configure the EDMA clock */
    PlatformEDMAWkupDepEnable();

    /* Do EDMA init Done once in the beginning of application */
    EDMAsetRegion(EDMA3_CC_REGION);
    EDMA3Init(SOC_EDMA_TPCC_BASE, EVT_QUEUE_NUM);

    /* Configuring the AINTC to receive EDMA3 interrupts. */
    Edma3INTCConfigure();

    /* Initializing the UART for use. */
    UartInitialize();

    /* Configure the DMA crossbar for UART TX and RX events. */
    EdmaEvtConfigure();

    /* Request DMA Channel and TCC for UART Transmit*/
    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE, EDMA3_CHANNEL_TYPE_DMA,
                        EDMA3_UART_TX_CHA_NUM, EDMA3_UART_TX_CHA_NUM,
                        EVT_QUEUE_NUM);

    /* Registering Callback Function for TX*/
    cb_Fxn[EDMA3_UART_TX_CHA_NUM] = &callback;

    /* Request DMA Channel and TCC for UART Receive */
    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE, EDMA3_CHANNEL_TYPE_DMA,
                        EDMA3_UART_RX_CHA_NUM, EDMA3_UART_RX_CHA_NUM,
                        EVT_QUEUE_NUM);

    /* Registering Callback Function for RX*/
    cb_Fxn[EDMA3_UART_RX_CHA_NUM] = &callback;

    /******************** Transmission of a string **************************/

    numByteChunks = (sizeof (welcome) - 1) / txBytesPerEvent;
    remainBytes   = (sizeof (welcome) - 1) % txBytesPerEvent;

    /* Configuring EDMA PaRAM sets to transmit 'welcome' message. */
    UARTTxEDMAPaRAMSetConfig(welcome,
                             numByteChunks * txBytesPerEvent,
                             EDMA3_UART_TX_CHA_NUM,
                             EDMA_TPCC_OPT(DUMMY_CH_NUM),
                             EDMA3_UART_TX_CHA_NUM);

    /* Configuring the PaRAM set for Dummy Transfer. */
    TxDummyPaRAMConfEnable();

    /* Enable EDMA Transfer */
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE, EDMA3_UART_TX_CHA_NUM,
                        EDMA3_TRIG_MODE_EVENT);

    /* Wait for return from callback */
    while (0 == clBackFlag) ;
    clBackFlag = 0;

    /* Remaining bytes are transferred through polling method. */
    if (0 != remainBytes)
    {
        pBuffer = welcome + (sizeof (welcome) - 1) - remainBytes;
        UARTConfigPuts(uartBaseAddr, (char *) pBuffer, remainBytes);
    }

    /******************** Transmission of a string **************************/

    numByteChunks = (sizeof (intent) - 1) / txBytesPerEvent;
    remainBytes   = (sizeof (intent) - 1) % txBytesPerEvent;

    /* Enabling DMA Mode 1. */
    UARTDMAEnable(uartBaseAddr, UART_DMA_MODE_1_ENABLE);

    /* Configuring EDMA PaRAM sets to transmit data. */
    UARTTxEDMAPaRAMSetConfig(intent,
                             numByteChunks * txBytesPerEvent,
                             EDMA3_UART_TX_CHA_NUM,
                             EDMA_TPCC_OPT(DUMMY_CH_NUM),
                             EDMA3_UART_TX_CHA_NUM);

    /* Configuring the PaRAM set for Dummy Transfer. */
    TxDummyPaRAMConfEnable();

    /* Enable EDMA Transfer */
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE, EDMA3_UART_TX_CHA_NUM,
                        EDMA3_TRIG_MODE_EVENT);

    /* Wait for return from callback */
    while (0 == clBackFlag) ;
    clBackFlag = 0;

    /* Remaining bytes are transferred through polling method. */
    if (0 != remainBytes)
    {
        pBuffer = intent + (sizeof (intent) - 1) - remainBytes;
        UARTConfigPuts(uartBaseAddr, (char *) pBuffer, remainBytes);
    }

    /******************** Transmission of a string **************************/

    numByteChunks = (sizeof (enter) - 1) / txBytesPerEvent;
    remainBytes   = (sizeof (enter) - 1) % txBytesPerEvent;

    /* Enabling DMA Mode 1. */
    UARTDMAEnable(uartBaseAddr, UART_DMA_MODE_1_ENABLE);

    /* Configuring EDMA PaRAM sets to transmit 'enter' message. */
    UARTTxEDMAPaRAMSetConfig(enter,
                             numByteChunks * txBytesPerEvent,
                             EDMA3_UART_TX_CHA_NUM,
                             EDMA_TPCC_OPT(DUMMY_CH_NUM),
                             EDMA3_UART_TX_CHA_NUM);

    /* Configuring the PaRAM set for Dummy Transfer. */
    TxDummyPaRAMConfEnable();

    /* Enable EDMA Transfer */
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE, EDMA3_UART_TX_CHA_NUM,
                        EDMA3_TRIG_MODE_EVENT);

    /* Wait for return from callback */
    while (0 == clBackFlag) ;
    clBackFlag = 0;

    /* Remaining bytes are transferred through polling method. */
    if (0 != remainBytes)
    {
        pBuffer = enter + (sizeof (enter) - 1) - remainBytes;
        UARTConfigPuts(uartBaseAddr, (char *) pBuffer, remainBytes);
    }

    /********************* Receiving Data from User *************************/

    /* Enabling DMA Mode 1. */
    UARTDMAEnable(uartBaseAddr, UART_DMA_MODE_1_ENABLE);

    /* Configuring the PaRAM set for reception. */
    UARTRxEDMAPaRAMSetConfig(rxBuffer,
                             NUM_RX_BYTES,
                             EDMA3_UART_RX_CHA_NUM,
                             0xFFFF,
                             EDMA3_UART_RX_CHA_NUM);

    /* Enable EDMA Transfer */
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE, EDMA3_UART_RX_CHA_NUM,
                        EDMA3_TRIG_MODE_EVENT);

    /* Wait for return from callback */
    while (0 == clBackFlag) ;
    clBackFlag = 0;

    /******************* Echoing received bytes *****************************/

    numByteChunks = (NUM_RX_BYTES) / txBytesPerEvent;
    remainBytes   = (NUM_RX_BYTES) % txBytesPerEvent;

    /* Enabling DMA Mode 1. */
    UARTDMAEnable(uartBaseAddr, UART_DMA_MODE_1_ENABLE);

    /* Configuring the PaRAM set to transmit the bytes that were received. */
    UARTTxEDMAPaRAMSetConfig(rxBuffer,
                             numByteChunks * txBytesPerEvent,
                             EDMA3_UART_TX_CHA_NUM,
                             EDMA_TPCC_OPT(DUMMY_CH_NUM),
                             EDMA3_UART_TX_CHA_NUM);

    /* Configuring the PaRAM set for Dummy Transfer. */
    TxDummyPaRAMConfEnable();

    /* Enable EDMA Transfer */
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE, EDMA3_UART_TX_CHA_NUM,
                        EDMA3_TRIG_MODE_EVENT);

    /* Wait for return from callback */
    while (0 == clBackFlag) ;
    clBackFlag = 0;

    /* Remaining bytes are transferred through polling method. */
    if (0 != remainBytes)
    {
        pBuffer = rxBuffer + NUM_RX_BYTES - remainBytes;
        UARTConfigPuts(uartBaseAddr, (char *) pBuffer, remainBytes);
    }

    /******************* Freeing of allocated channels **********************/

    /* Free EDMA3 Channels for TX and RX */
    EDMA3FreeChannel(SOC_EDMA_TPCC_BASE, EDMA3_CHANNEL_TYPE_DMA,
                     EDMA3_UART_TX_CHA_NUM, EDMA3_TRIG_MODE_EVENT,
                     EDMA3_UART_TX_CHA_NUM, EVT_QUEUE_NUM);

    EDMA3FreeChannel(SOC_EDMA_TPCC_BASE, EDMA3_CHANNEL_TYPE_DMA,
                     EDMA3_UART_RX_CHA_NUM, EDMA3_TRIG_MODE_EVENT,
                     EDMA3_UART_RX_CHA_NUM, EVT_QUEUE_NUM);

    return 0;
}

/*
** This function configures and sets the EDMA PaRAM set values for
** transferring data to UART TX FIFO.
*/
static void UARTTxEDMAPaRAMSetConfig(unsigned char *txBuffer,
                                     uint32_t       length,
                                     uint32_t       tccNum,
                                     uint32_t       linkAddr,
                                     uint32_t       chNum)
{
    EDMA3CCPaRAMEntry paramSet;

    /* Fill the PaRAM Set with transfer specific information */
    paramSet.srcAddr  = (uint32_t) txBuffer;
    paramSet.destAddr = (uint32_t) uartBaseAddr;

    paramSet.aCnt    = (uint32_t) 1;
    paramSet.bCnt    = (uint32_t) txBytesPerEvent;
    paramSet.cCnt    = (uint32_t) (length / txBytesPerEvent);
    paramSet.srcBIdx = (uint32_t) 1;
    paramSet.srcCIdx = (uint32_t) txBytesPerEvent;

    /* The destination indexes should not increment since it is a h/w register.
    **/
    paramSet.destBIdx = (uint32_t) 0;
    paramSet.destCIdx = (uint32_t) 0;

    paramSet.linkAddr   = (uint32_t) linkAddr;
    paramSet.bCntReload = (uint32_t) 0;

    /* OPT PaRAM entries. */
    paramSet.opt = (uint32_t) 0x0;

    /* Source and Destination addressing modes are Incremental. */

    /* AB Synchronized Transfer. */
    paramSet.opt |= (1 << EDMA_TPCC_OPT_SYNCDIM_SHIFT);

    /* Setting the Transfer Complete Code(TCC). */
    paramSet.opt |=
        ((tccNum << EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK);

    /* Enabling the Completion Interrupt. */
    paramSet.opt |= (1 << EDMA_TPCC_OPT_TCINTEN_SHIFT);

    /* Now write the PaRAM Set */
    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, chNum, &paramSet);
}

/*
** This function configures and sets the EDMA PaRAM set values for
** receiving data from UART RX FIFO.
*/
static void UARTRxEDMAPaRAMSetConfig(unsigned char *rxBuffer,
                                     uint32_t       length,
                                     uint32_t       tccNum,
                                     uint32_t       linkAddr,
                                     uint32_t       chNum)
{
    EDMA3CCPaRAMEntry paramSet;

    /* Fill the PaRAM Set with transfer specific information */
    paramSet.srcAddr  = (uint32_t) uartBaseAddr;
    paramSet.destAddr = (uint32_t) rxBuffer;

    paramSet.aCnt     = (uint32_t) 1;
    paramSet.bCnt     = (uint32_t) (rxTrigLevel);
    paramSet.cCnt     = (uint32_t) (length / rxTrigLevel);
    paramSet.destBIdx = (uint32_t) 1;
    paramSet.destCIdx = (uint32_t) rxTrigLevel;

    paramSet.srcBIdx = (uint32_t) 0;
    paramSet.srcCIdx = (uint32_t) 0;

    paramSet.linkAddr   = (uint32_t) linkAddr;
    paramSet.bCntReload = (uint32_t) 0;

    /* OPT PaRAM Entries. */
    paramSet.opt = (uint32_t) 0x0;

    /* Source and Destination addressing modes are Incremental. */

    /* Enable AB Synchronized Transfer. */
    paramSet.opt |= (1 << EDMA_TPCC_OPT_SYNCDIM_SHIFT);

    /* Setting the Transfer Complete Code(TCC). */
    paramSet.opt |=
        ((tccNum << EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK);

    /* Enabling the Completion Interrupt. */
    paramSet.opt |= (1 << EDMA_TPCC_OPT_TCINTEN_SHIFT);

    /* Now write the PaRAM Set */
    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, chNum, &paramSet);
}

/*
** This configures the PaRAM set for the Dummy Transfer.
*/

static void TxDummyPaRAMConfEnable(void)
{
    EDMA3CCPaRAMEntry dummyPaRAMSet;

    dummyPaRAMSet.aCnt       = 1;
    dummyPaRAMSet.bCnt       = 0;
    dummyPaRAMSet.cCnt       = 0;
    dummyPaRAMSet.srcAddr    = 0;
    dummyPaRAMSet.destAddr   = 0;
    dummyPaRAMSet.srcBIdx    = 0;
    dummyPaRAMSet.destBIdx   = 0;
    dummyPaRAMSet.srcCIdx    = 0;
    dummyPaRAMSet.destCIdx   = 0;
    dummyPaRAMSet.linkAddr   = 0xFFFF;
    dummyPaRAMSet.bCntReload = 0;
    dummyPaRAMSet.opt        = 0;

    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, DUMMY_CH_NUM, &dummyPaRAMSet);
}

/*
** EDMA Completion Interrupt Service Routine(ISR).
*/
static void Edma3CompletionIsr(void *handle)
{
    volatile uint32_t pendingIrqs;
    uint32_t          index = 1;
    uint32_t          count = 0;

    if (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE))
    {
        /*
        ** Wait for a finite time to monitor the EDMA Completion Interrupt
        ** status.
        */
        while ((count < EDMA3CC_COMPL_HANDLER_RETRY_COUNT) && (index != 0U))
        {
            index = 0;

            /* Get the Interrupt status. */
            pendingIrqs = EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE);
            while (pendingIrqs)
            {
                if ((pendingIrqs & 1U) == TRUE)
                {
                    /* Clear the interrupt status. */
                    EDMA3ClrIntr(SOC_EDMA_TPCC_BASE, index);

                    (*cb_Fxn[index])(index);
                }
                ++index;
                pendingIrqs >>= 1U;
            }
            count++;
        }
    }
}

/*
** This function is used as a callback from EDMA3 Completion Handler.
*/
static void callback(uint32_t tccNum)
{
    /* Disabling DMA Mode of operation in UART. */
    UARTDMADisable(uartBaseAddr);

    /* Disabling DMA transfer on the specified channel. */
    EDMA3DisableTransfer(SOC_EDMA_TPCC_BASE, tccNum, EDMA3_TRIG_MODE_EVENT);

    clBackFlag = 1;
}

/*
** EDMA Error Interrupt Service Routine(ISR).
*/

static void Edma3ErrorIsr(void *handle)
{
    volatile uint32_t pendingIrqs = 0;
    uint32_t          evtqueNum   = 0;
    uint32_t          index       = 1;
    uint32_t          Cnt         = 0;

    if ((0 != EDMA3GetErrIntrStatus(SOC_EDMA_TPCC_BASE)) ||
        (0 != (EDMA3GetCCErrStatus(SOC_EDMA_TPCC_BASE))))
    {
        /* Loop for EDMA3CC_ERR_HANDLER_RETRY_COUNT number of time, breaks
         * when no pending interrupt is found */
        while ((Cnt < EDMA3CC_ERR_HANDLER_RETRY_COUNT) && (index != 0U))
        {
            index       = 0U;
            pendingIrqs = EDMA3GetErrIntrStatus(SOC_EDMA_TPCC_BASE);

            while (pendingIrqs)
            {
                /*Process all the pending interrupts*/
                if ((pendingIrqs & 1U) == TRUE)
                {
                    /* Writing to EMCR to clear the corresponding EMR bits.
                     * Also clearing any Secondary events in SER. */
                    EDMA3ClrMissEvt(SOC_EDMA_TPCC_BASE, index);
                }
                ++index;
                pendingIrqs >>= 1U;
            }
            index = 0U;

            pendingIrqs = EDMA3GetCCErrStatus(SOC_EDMA_TPCC_BASE);
            if (pendingIrqs != 0U)
            {
                /* Process all the pending CC error interrupts. */
                /* Queue threshold error for different event queues. */
                for (evtqueNum = 0U; evtqueNum < EDMA3_0_NUM_EVTQUE;
                     evtqueNum++)
                {
                    if ((pendingIrqs & (1U << evtqueNum)) != 0U)
                    {
                        /* Clear the error interrupt. */
                        EDMA3ClrCCErr(SOC_EDMA_TPCC_BASE, (1U << evtqueNum));
                    }
                }

                /* Transfer completion code error. */
                if ((pendingIrqs & (1 << EDMA_TPCC_CCERR_TCERR_SHIFT)) != 0U)
                {
                    EDMA3ClrCCErr(SOC_EDMA_TPCC_BASE,
                                  (0x01U << EDMA_TPCC_CCERR_TCERR_SHIFT));
                }
                ++index;
            }

            Cnt++;
        }
    }
}

/*
** This function initializes the UART instance for use.
*/
static void UartInitialize(void)
{
    /* Performing a module reset. */
    UARTModuleReset(uartBaseAddr);

    /* Performing FIFO configurations. */
    UartFIFOConfigure();

    /* Selecting the method of setting the Transmit DMA Threshold value. */
    UARTTxDMAThresholdControl(uartBaseAddr, UART_TX_DMA_THRESHOLD_REG);

    /* Configuring the Transmit DMA Threshold value. */
    UARTTxDMAThresholdValConfig(uartBaseAddr, txThreshLevel);

    /* Performing Baud Rate settings. */
    UartBaudRateSet();

    /* Switching to Configuration Mode B. */
    UARTRegConfigModeEnable(uartBaseAddr, UART_REG_CONFIG_MODE_B);

    /* Programming the Line Characteristics. */
    UARTLineCharacConfig(uartBaseAddr,
                         (UART_FRAME_WORD_LENGTH_8 | UART_FRAME_NUM_STB_1),
                         UART_PARITY_NONE);

    /* Disabling write access to Divisor Latches. */
    UARTDivisorLatchDisable(uartBaseAddr);

    /* Disabling Break Control. */
    UARTBreakCtl(uartBaseAddr, UART_BREAK_COND_DISABLE);

    /* Switching to UART16x operating mode. */
    UARTOperatingModeSelect(uartBaseAddr, UART16x_OPER_MODE);
}

/*
** A wrapper function performing FIFO configurations.
*/
static void UartFIFOConfigure(void)
{
    uint32_t fifoConfig = 0;

    /*
    ** Transmitter Trigger Level Granularity is 1.
    ** Receiver Trigger Level Granularity is 1.
    ** Transmit Trigger Space set using 'txTrigSpace'.
    ** Receive Trigger level set using 'rxTrigLevel'.
    ** Clear the Trasnmit FIFO.
    ** Clear the Receive FIFO.
    ** DMA Mode enabling shall happen through SCR register.
    ** DMA Mode 1 is enabled.
    */
    fifoConfig = UART_FIFO_CONFIG(UART_TRIG_LVL_GRANULARITY_1,
                                  UART_TRIG_LVL_GRANULARITY_1,
                                  txTrigSpace,
                                  rxTrigLevel,
                                  1,
                                  1,
                                  UART_DMA_EN_PATH_SCR,
                                  UART_DMA_MODE_1_ENABLE);

    /* Configuring the FIFO settings. */
    UARTFIFOConfig(uartBaseAddr, fifoConfig);
}

/*
** A wrapper function performing Baud Rate settings.
*/
static void UartBaudRateSet(void)
{
    uint32_t divisorValue = 0;

    /* Computing the Divisor Value. */
    divisorValue = UARTDivisorValCompute(UART_MODULE_INPUT_CLK,
                                         BAUD_RATE_115200,
                                         UART16x_OPER_MODE,
                                         UART_MIR_OVERSAMPLING_RATE_42);

    /* Programming the Divisor Latches. */
    UARTDivisorLatchWrite(uartBaseAddr, divisorValue);
}

/*
** This function configures the AINTC to receive EDMA3 interrupts.
*/
static void Edma3INTCConfigure(void)
{
    /* Unlock Pad Config Registers */
    PLATFORMUnLockRegion(PLATFORM_MMR_REG_2);
#ifdef BUILD_A15

    /* Crossbar registers are already unlocked, so connect directly */
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_MPUSS, 7,
                   EDMA_TPCC_IRQ_REGION0);

    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_MPUSS, 20,
                   EDMA_TPCC_IRQ_ERR);

#elif defined (BUILD_M4)

    /* Crossbar registers are already unlocked, so connect directly */
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1, 12,
                   EDMA_TPCC_IRQ_REGION1);

    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1, 13,
                   EDMA_TPCC_IRQ_ERR);

#endif
    /* Lock Pad Config Registers */
    PLATFORMLockRegion(PLATFORM_MMR_REG_2);

    /* Initializing the ARM Interrupt Controller. */
    Intc_Init();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /* Registering EDMA3 Channel Controller 0 transfer completion interrupt.  */
    Intc_IntRegister(EDMA3_CC_XFER_COMPLETION_INT,
                     (IntrFuncPtr) Edma3CompletionIsr,
                     NULL);

    /* Setting the priority for EDMA3CC0 completion interrupt in AINTC. */
    Intc_IntPrioritySet(EDMA3_CC_XFER_COMPLETION_INT, 1, 0);

    /* Enabling the EDMA3CC0 completion interrupt in AINTC. */
    Intc_SystemEnable(EDMA3_CC_XFER_COMPLETION_INT);

    /* Registering EDMA3 Channel Controller 0 Error Interrupt. */
    Intc_IntRegister(EDMA3_CC_XFER_ERROR_INT, (IntrFuncPtr) Edma3ErrorIsr, NULL);

    /* Setting the priority for EDMA3CC0 Error interrupt in AINTC. */
    Intc_IntPrioritySet(EDMA3_CC_XFER_ERROR_INT, 1, 0);

    /* Enabling the EDMA3CC0 Error interrupt in AINTC. */
    Intc_SystemEnable(EDMA3_CC_XFER_ERROR_INT);
}

/*
** This function configures the DMA crossbar for UART TX and RX events.
*/
static void EdmaEvtConfigure(void)
{
    /* Unlock Pad Config Registers */
    PLATFORMUnLockRegion(PLATFORM_MMR_REG_2);

#if defined (TDA2XX_FAMILY_BUILD)
    /* Configure the UART TX event. */
    DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, EDMA,
                   DMA_XBAR_INST_49,
                   UART1_DREQ_TX);

    /* Configure the UART RX event. */
    DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, EDMA,
                   DMA_XBAR_INST_50,
                   UART1_DREQ_RX);
#elif defined (TDA3XX_FAMILY_BUILD)
    /* Configure the UART TX event. */
    DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, EDMA,
                   DMA_XBAR_INST_53,
                   UART3_DREQ_TX);

    /* Configure the UART RX event. */
    DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, EDMA,
                   DMA_XBAR_INST_54,
                   UART3_DREQ_RX);
#endif
    /* Lock Pad Config Registers */
    PLATFORMLockRegion(PLATFORM_MMR_REG_2);
}

/******************************** End of file *******************************/
