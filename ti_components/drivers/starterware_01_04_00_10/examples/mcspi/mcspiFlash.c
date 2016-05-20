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
 * @file mcspiFlash.c
 *
 * This file contains the McSPI application which demonstrates master
 * mode of operation with default configuration settings. This example uses the
 * Spi bus to write an array of data to the Spi Flash memory and then, the Spi
 * bus is again is used to read the same data from the Spi Flash memory.
 *
 * @path  $(ds)\hal\examples\mcspiFlash.c
 *
 * @rev  00.01
 */

/******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************/
#include "stdint.h"
#include <stdio.h>
#include "mcspi.h"
#include "interrupt.h"
#include "edma.h"
#include "soc.h"
#include "soc_defines.h"
#include "platform.h"
#include "uartStdio.h"
#include <common/stw_dataTypes.h>

/* ****************************************************************************
 * Please comment the below line to have the application in polled mode. Once
 * after validation/bring up this code can be removed
 * ***************************************************************************/
#define EDMA_CONFIG 1

/******************************************************************************/
/* The macros which needs to be reviewed and included from appropriate header */
/* files                                                                      */
/******************************************************************************/

#if defined (TI814X_FAMILY_BUILD)
    #define MCSPI0_BASE_ADDRESS              (SOC_MCSPI0_REGS)
#endif

#if EDMA_CONFIG

    #define MCSPI_TX_EVENT                  (16U)
    #define MCSPI_RX_EVENT                  (17U)

    #define MCSPI_TX0_REG                   (MCSPI0_BASE_ADDRESS + (0x138U))
    #define MCSPI_RX0_REG                   (MCSPI0_BASE_ADDRESS + (0x13CU))

    #define MCSPI_CH_NUM                    (0U)
    #define EVT_QUEQUE_NUM                  (0U)
    #define DUMMY_CH_NUM                    (5U)

    #define EDMA_TI814X_U_BASE              (SOC_EDMA_TPCC_BASE)

    #define EDMA3CC_PaRAM_BASE            (0x4000)
    #define EDMA3CC_OPT(n)                (EDMA3CC_PaRAM_BASE + 0x0 + (0x20 * n))

    #define EDMA3_CC_XFER_COMPLETION_INT_A8                 (12U)
    #define EDMA3_CC_XFER_COMPLETION_INT_M3VPSS             (63U)
    #define EDMA3_CC_XFER_COMPLETION_INT_M3VIDEO            (62U)

    #define EDMA3_CC_REGION_A8                              (0U)
    #define EDMA3_CC_REGION_M3VPSS                          (5U)
    #define EDMA3_CC_REGION_M3VIDEO                         (4U)

    #define EDMA3_ERROR_INT_A8                              (14)
    #define EDMA3_ERROR_INT_M3VPSS                          (46)
    #define EDMA3_ERROR_INT_M3VIDEO                         (46)

#endif

/******************************************************************************
**                      INTERNAL MACRO DEFINITIONS
******************************************************************************/
#define FLASH_WRITE_IN_PROGRESS          (0x01U)
#define FLASH_SECTOR_ADD_HIGH            (0x1FU)
#define FLASH_SECTOR_ADD_LOW             (0x00U)
#define FLASH_SECTOR_ADD_MID             (0x00U)
#define FLASH_READ_STAT_REG1             (0x05U)
#define FLASH_WRITE_ENABLE               (0x06U)
#define FLASH_SECTOR_ERASE               (0x20U)
#define FLASH_PAGE_PROGRAM               (0x02U)
#define FLASH_DUMMY_BYTE                 (0xFFU)
#define FLASH_DATA_READ                  (0x03U)
#define MCSPI_OUT_FREQ                   (48000000U)
#define MCSPI_IN_CLK                     (48000000U)

/******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
******************************************************************************/
static void McSPISetUp(void);
static void McSPITransfer(uint16_t length);
static void McSPIConfigure(void);
static void McSPIVerifyData(void);
static void McSPIWriteEnable(void);
static void McSPISectorErase(void);
static void McSPIIsFlashBusy(void);
static void McSPIWriteToFlash(void);
static void McSPIReadFromFlash(void);
static void McSPIFlashStatusGet(void);
static uint32_t McSPIIsWriteSuccess(void);

#if EDMA_CONFIG
static void McSpiTxEdmaParamSet(uint32_t tccNum, uint32_t chNum,
                                volatile uint8_t *buffer,
                                uint16_t buffLength);
static void McSpiRxEdmaParamSet(uint32_t tccNum, uint32_t chNum,
                                volatile uint8_t *buffer,
                                uint16_t buffLength,
                                uint32_t destBidxFlag);
static void CallBack(uint32_t tccNum, uint32_t status);

static void TxDummyPaRAMConfEnable(void);

static void Edma3ErrorHandlerIsr(void *dummy);
static void Edma3ComplHandlerIsr(void *dummy);
static void RequestEDMA3Channels(void);
static void EDMA3IntConfigure(void);
static void EDMA3Initialize(void);
#else
static void McSPIPolledModeTransfer(uint16_t length);
#endif

/******************************************************************************
**                      GLOBAL VARIABLE DEFINITIONS
******************************************************************************/
uint8_t          rxBuffer[260];
uint8_t          txBuffer[260];
uint8_t          vrfyData[256];
uint32_t         gChNum = 0;
uint8_t         *p_rx;
uint8_t         *p_tx;

#if EDMA_CONFIG
static void(*cb_Fxn[EDMA3_NUM_TCC]) (uint32_t tcc,
                                     uint32_t status);
volatile uint8_t flagTx = 0;
volatile uint8_t flagRx = 0;
#endif

/******************************************************************************
**                      INTERNAL FUNCTION DEFINITIONS
******************************************************************************/
int main(void)
{
    volatile uint32_t count  = 0xFFFFFU;
    volatile uint32_t retVal = 1; // FALSE
    /* volatile uint8_t  choice = 0; */
    char choice = 0;
#ifdef TDA2XX_FAMILY_BUILD
    PlatformUART1SetPinMux();
#endif
    UARTStdioInit();

    /* Perform Pin-Muxing for CS0 of SPI0 Instance */
    McSPIConfigure();

#if EDMA_CONFIG

#if defined (BUILD_A8)
    EDMAsetRegion(EDMA3_CC_REGION_A8);
#elif defined (BUILD_M3VPSS)
    EDMAsetRegion(EDMA3_CC_REGION_M3VPSS);
#elif defined (BUILD_M3VIDEO)
    EDMAsetRegion(EDMA3_CC_REGION_M3VIDEO);
#endif

    EDMA3Init(EDMA_TI814X_U_BASE, 0);

    /* Request EDMA3CC for Tx and Rx channels for SPI0. */
    RequestEDMA3Channels();

    /* Initialize the EDMA3 instance.*/
    EDMA3Initialize();

#endif
    /* Do the necessary set up configurations for McSPI.*/
    McSPISetUp();

    /* Pass the write enable command to flash.*/
    McSPIWriteEnable();

    /* Wait until write enable command is successfully written to flash.*/
    while (1 == retVal)
    {
        retVal = McSPIIsWriteSuccess();
    }

    retVal = 1; // FALSE

    UARTPuts("\r\nDo you want to erase a sector of the flash before", -1);
    UARTPuts(" writing to it ?.\r\n", -1);
    UARTPuts("\r\nInput y(Y)/n(N) to proceed.\r\n", -1);

    UARTGets(&choice, 1);

    if (((uint8_t) 'Y' == choice) || ((uint8_t) 'y' == choice))
    {
        /* Erase a sector of flash.*/
        McSPISectorErase();

        UARTPuts("\r\nSector Erase Complete.\r\n", -1);
    }

    /* Pass the write enable command to flash.*/
    McSPIWriteEnable();

    /* Wait until write enable command is successfully written to flash.*/
    while (1 == retVal)
    {
        retVal = McSPIIsWriteSuccess();
    }

    /* Write data of 1 page size to flash.*/
    McSPIWriteToFlash();

    /* Channel Disable Enable Transition */
    while (count--) ;

    /* Read data of 1 page size from flash.*/
    McSPIReadFromFlash();

    /* Verify the data written to and read from flash are same or not.*/
    McSPIVerifyData();

    UARTPuts("\r\n End of McSPI Application\r\n", -1);

    return 0;
}

static void McSPIConfigure(void)
{
    /*Configure Pin mux*/
    PlatformMCSPI0SetPinMux();
    /* power on SPI */
    PlatformMCSPI0PrcmEnable();

    /* power on the EDMA */
    PlatformEDMAPrcmEnable();
}

/*
** This function will write data of 1 page size on to a page of a specific
** sector.
*/
static void McSPIWriteToFlash(void)
{
    uint32_t index = 0;
#if EDMA_CONFIG
    uint32_t dummy = 0;
#endif
    uint32_t length = 0;

    txBuffer[0] = FLASH_PAGE_PROGRAM;
    txBuffer[1] = FLASH_SECTOR_ADD_HIGH;
    txBuffer[2] = FLASH_SECTOR_ADD_MID;
    txBuffer[3] = FLASH_SECTOR_ADD_LOW;

    for (index = 0; index < 256; index++)
    {
        txBuffer[index + 4] = (uint8_t) index;
        vrfyData[index]     = (uint8_t) index;
    }

    length = 260;

#if EDMA_CONFIG
    /* Configure the Page-program parameters for Edma transmit.*/
    McSpiTxEdmaParamSet(MCSPI_TX_EVENT, MCSPI_TX_EVENT, txBuffer,
                        length);

    /* Configure the Page-program parameters for Edma receive.*/
    McSpiRxEdmaParamSet(MCSPI_RX_EVENT, MCSPI_RX_EVENT, (uint8_t *) dummy,
                        length, FALSE);

    /* Register the call-back function for McSPI Tx/Rx events.*/
    cb_Fxn[MCSPI_TX_EVENT] = &CallBack;
    cb_Fxn[MCSPI_RX_EVENT] = &CallBack;
#endif

    McSPITransfer(length);
}

/*
** This function will verify the data written to and read from flash and print
** the appropriate message.
*/
static void McSPIVerifyData(void)
{
    uint32_t index = 0;

    for (index = 4; index < 260; index++)
    {
        if (rxBuffer[index] != vrfyData[index - 4])
        {
#ifndef BUILD_GCC
            printf("\r\n VerifyData: Comparing the data written to and read");
            printf(" from Flash.\r\nThe two data blocks are unequal.");
            printf("\r\nData Mismatch found at index - %d\n", (int) index);
#else
            UARTPuts("\r\n VerifyData: Comparing the data written to and read", -1);
            UARTPuts(" from Flash.\r\nThe two data blocks are unequal.", -1);
            UARTPuts("\r\nData Mismatch found at index - %d\n", -1);
            UARTPutNum((int) index);
#endif
            break;
        }
    }

    if (260 == index)
    {
#ifndef BUILD_GCC
        printf("\nThe data in the Flash and the one written are Equal\r\n");
#else
        UARTPuts("\nThe data in the Flash and the one written are Equal\r\n", -1);
#endif
    }
}

/*
** This function will read data of 1 page size from a specific sector of flash.
*/
static void McSPIReadFromFlash(void)
{
    uint32_t index  = 0;
    uint32_t length = 0;

    txBuffer[0] = FLASH_DATA_READ;
    txBuffer[1] = FLASH_SECTOR_ADD_HIGH;
    txBuffer[2] = FLASH_SECTOR_ADD_MID;
    txBuffer[3] = FLASH_SECTOR_ADD_LOW;

    for (index = 4; index < 260; index++)
    {
        txBuffer[index] = 0;
    }

    length = 260;

#if EDMA_CONFIG
    /* Configure the read data parameters of McSPI for Edma transmit.*/
    McSpiTxEdmaParamSet(MCSPI_TX_EVENT, MCSPI_TX_EVENT, txBuffer,
                        length);

    /* Configure the read data parameters of McSPI for Edma receive.*/
    McSpiRxEdmaParamSet(MCSPI_RX_EVENT, MCSPI_RX_EVENT, rxBuffer,
                        length, TRUE);

    /* Register the call-back function for Tx/Rx edma events of McSPI.*/
    cb_Fxn[MCSPI_TX_EVENT] = &CallBack;
    cb_Fxn[MCSPI_RX_EVENT] = &CallBack;
#endif

    McSPITransfer(length);
}

/*
** This function will check whether the write enable command is successfully
** latched on to flash or not.
*/
static uint32_t McSPIIsWriteSuccess(void)
{
    uint32_t retVal = 1; // FALSE
    uint32_t length = 0;

    txBuffer[0] = FLASH_READ_STAT_REG1;
    txBuffer[1] = 0;

    length = 2;

#if EDMA_CONFIG
    /* Configure the read data parameters of McSPI for Edma transmit.*/
    McSpiTxEdmaParamSet(MCSPI_TX_EVENT, MCSPI_TX_EVENT, txBuffer,
                        length);

    /* Configure the read data parameters of McSPI for Edma receive.*/
    McSpiRxEdmaParamSet(MCSPI_RX_EVENT, MCSPI_RX_EVENT, rxBuffer,
                        length, TRUE);

    /* Register the call-back function for Tx/Rx edma events of McSPI.*/
    cb_Fxn[MCSPI_TX_EVENT] = &CallBack;
    cb_Fxn[MCSPI_RX_EVENT] = &CallBack;
#endif

    McSPITransfer(length);

    if (0x02 == rxBuffer[1])
    {
        retVal = 0; // TRUE
    }

    return retVal;
}

/*
** This function will send the write enable command to the flash device.
*/
static void McSPIWriteEnable(void)
{
    txBuffer[0] = FLASH_WRITE_ENABLE;
    uint32_t length = 0;

    length = 1;

#if EDMA_CONFIG
    /* Configure the read data parameters of McSPI for Edma transmit.*/
    McSpiTxEdmaParamSet(MCSPI_TX_EVENT, MCSPI_TX_EVENT, txBuffer,
                        length);

    /* Configure the read data parameters of McSPI for Edma receive.*/
    McSpiRxEdmaParamSet(MCSPI_RX_EVENT, MCSPI_RX_EVENT, rxBuffer,
                        length, TRUE);

    /* Register the call-back function for Tx/Rx edma events of McSPI.*/
    cb_Fxn[MCSPI_TX_EVENT] = &CallBack;
    cb_Fxn[MCSPI_RX_EVENT] = &CallBack;
#endif

    McSPITransfer(length);
}

/*
** This function will activate/deactivate CS line and also enable Tx and Rx
** interrupts of McSPI peripheral.
*/
#if EDMA_CONFIG
static void McSPITransfer(uint16_t length)
{
    /* Set the word count field with the data length to be transferred.*/
    McSPIWordCountSet(MCSPI0_BASE_ADDRESS, length);

    /* SPIEN line is forced to low state.*/
    McSPICSAssert(MCSPI0_BASE_ADDRESS, gChNum);

    /* Enable the Tx/Rx DMA events for McSPI. */
    McSPIDMAEnable(MCSPI0_BASE_ADDRESS,
                   (MCSPI_DMA_RX_EVENT | MCSPI_DMA_TX_EVENT),
                   MCSPI_CH_NUM);

    /* Enable the McSPI channel for communication.*/
    McSPIChannelEnable(MCSPI0_BASE_ADDRESS, gChNum);

    /* Wait for control to return from ISR.*/
    while ((0 == flagTx) || (flagRx == 0)) ;

    flagTx = 0;
    flagRx = 0;

    /* Force SPIEN line to the inactive state.*/
    McSPICSDeAssert(MCSPI0_BASE_ADDRESS, gChNum);

    /* Disable the McSPI channel.*/
    McSPIChannelDisable(MCSPI0_BASE_ADDRESS, gChNum);
}

#else
static void McSPITransfer(uint16_t length)
{
    p_tx = txBuffer;
    p_rx = rxBuffer;

    /* Enable the McSPI channel for communication.*/
    McSPIChannelEnable(MCSPI0_BASE_ADDRESS, gChNum);

    /* SPIEN line is forced to low state.*/
    McSPICSAssert(MCSPI0_BASE_ADDRESS, gChNum);

    McSPIPolledModeTransfer(length);

    /* Force SPIEN line to the inactive state.*/
    McSPICSDeAssert(MCSPI0_BASE_ADDRESS, gChNum);

    /* Disable the McSPI channel.*/
    McSPIChannelDisable(MCSPI0_BASE_ADDRESS, gChNum);
}

#endif
/*
** This function will erase a sector of flash.
*/
static void McSPISectorErase(void)
{
    uint32_t length = 0;

    txBuffer[0] = FLASH_SECTOR_ERASE;
    txBuffer[1] = FLASH_SECTOR_ADD_HIGH;
    txBuffer[2] = FLASH_SECTOR_ADD_MID;
    txBuffer[3] = FLASH_SECTOR_ADD_LOW;

    length = 4;

#if EDMA_CONFIG
    /* Configure the read data parameters of McSPI for Edma transmit.*/
    McSpiTxEdmaParamSet(MCSPI_TX_EVENT, MCSPI_TX_EVENT, txBuffer,
                        length);

    /* Configure the read data parameters of McSPI for Edma receive.*/
    McSpiRxEdmaParamSet(MCSPI_RX_EVENT, MCSPI_RX_EVENT, rxBuffer,
                        length, TRUE);

    /* Register the call-back function for Tx/Rx edma events of McSPI.*/
    cb_Fxn[MCSPI_TX_EVENT] = &CallBack;
    cb_Fxn[MCSPI_RX_EVENT] = &CallBack;
#endif

    McSPITransfer(length);

    McSPIIsFlashBusy();
}

/*
** This function will send the flash status register bits on to the receive
** buffer.
*/
static void McSPIFlashStatusGet(void)
{
    uint32_t length = 0;

    txBuffer[0] = FLASH_READ_STAT_REG1;
    txBuffer[1] = 0xFF;

    length = 2;

#if EDMA_CONFIG
    /* Configure the read data parameters of McSPI for Edma transmit.*/
    McSpiTxEdmaParamSet(MCSPI_TX_EVENT, MCSPI_TX_EVENT, txBuffer,
                        length);

    /* Configure the read data parameters of McSPI for Edma receive.*/
    McSpiRxEdmaParamSet(MCSPI_RX_EVENT, MCSPI_RX_EVENT, rxBuffer,
                        length, TRUE);

    /* Register the call-back function for Tx/Rx edma events of McSPI.*/
    cb_Fxn[MCSPI_TX_EVENT] = &CallBack;
    cb_Fxn[MCSPI_RX_EVENT] = &CallBack;
#endif

    McSPITransfer(length);
}

/*
** This function will check whether write enable command is still in progress
**  or not.
*/
static void McSPIIsFlashBusy(void)
{
    do {
        McSPIFlashStatusGet();
    } while (rxBuffer[1] & FLASH_WRITE_IN_PROGRESS);
}

/*
** This function will call the necessary McSPI APIs which will configure the
** McSPI controller.
*/
static void McSPISetUp(void)
{
    uint32_t status = 1U;

    /* Reset the McSPI instance.*/
    McSPIReset(MCSPI0_BASE_ADDRESS);

    /* CLOCKACTIVITY bit - OCP and Functional clocks are maintained           */
    /* SIDLEMODE     bit - Ignore the idle request and configure in normal mode
     */
    /* AUTOIDLE      bit - Disable (OCP clock is running free, no gating)     */
    MCSPISysConfigSetup(MCSPI0_BASE_ADDRESS, MCSPI_CLOCKS_OCP_ON_FUNC_ON,
                        MCSPI_SIDLEMODE_NO, MCSPI_WAKEUP_DISABLE,
                        MCSPI_AUTOIDLE_OFF);

    /* Enable chip select pin.*/
    McSPICSEnable(MCSPI0_BASE_ADDRESS);

    /* Enable master mode of operation.*/
    McSPIMasterModeEnable(MCSPI0_BASE_ADDRESS);

    /* Perform the necessary configuration for master mode.*/
    status = McSPIMasterModeConfig(MCSPI0_BASE_ADDRESS, MCSPI_SINGLE_CH,
                                   MCSPI_TX_RX_MODE,
                                   MCSPI_DATA_LINE_COMM_MODE_1,
                                   gChNum);

    if (0 == status)
    {
        printf("Communication not supported by SPIDAT[1:0]\r\n");
    }

    /* Configure the McSPI bus clock depending on clock mode. */
    McSPIClkConfig(MCSPI0_BASE_ADDRESS, MCSPI_IN_CLK, MCSPI_OUT_FREQ, gChNum,
                   MCSPI_CLK_MODE_0);

    /* Configure the word length.*/
    McSPIWordLengthSet(MCSPI0_BASE_ADDRESS, MCSPI_WORD_LENGTH(8), gChNum);

    /* Set polarity of SPIEN to low.*/
    McSPICSPolarityConfig(MCSPI0_BASE_ADDRESS,
                          (MCSPI_CH0CONF_EPOL_ACTIVELOW <<
                           MCSPI_CH0CONF_EPOL_SHIFT), gChNum);

    /* Enable the transmitter FIFO of McSPI peripheral.*/
    McSPITxFIFOConfig(MCSPI0_BASE_ADDRESS, MCSPI_TX_FIFO_ENABLE, gChNum);

    /* Enable the receiver FIFO of McSPI peripheral.*/
    McSPIRxFIFOConfig(MCSPI0_BASE_ADDRESS, MCSPI_RX_FIFO_ENABLE, gChNum);
}

#if EDMA_CONFIG

#else

static void McSPIPolledModeTransfer(uint16_t length)
{
    uint32_t channelStatus = 0;
    uint32_t timeout1      = 0xFFFU;
    uint32_t timeout2      = 0xFFFU;

    while (0 != length)
    {
        channelStatus = McSPIChannelStatusGet(MCSPI0_BASE_ADDRESS, gChNum);

        while (0 == (channelStatus & MCSPI_CH0STAT_TXS_MASK))
        {
            channelStatus = 0;
            channelStatus = McSPIChannelStatusGet(MCSPI0_BASE_ADDRESS, gChNum);
            --timeout1;
            if (0 == timeout1)
            {
                printf("TX Timed out!!\r\n");
            }
        }
        McSPITransmitData(MCSPI0_BASE_ADDRESS, (uint32_t) (*p_tx++), gChNum);

        while (0 == (channelStatus & MCSPI_CH0STAT_RXS_MASK))
        {
            channelStatus = 0;
            channelStatus = McSPIChannelStatusGet(MCSPI0_BASE_ADDRESS, gChNum);
            --timeout2;
            if (0 == timeout2)
            {
                printf("RX Timed out!!\r\n");
            }
        }
        *p_rx++ = (uint8_t)  McSPIReceiveData(MCSPI0_BASE_ADDRESS, gChNum);

        length--;
    }
}

#endif

#if EDMA_CONFIG
/*
** This function configures the power supply for EDMA3 Channel Controller 0
** and Transfer Controller 0, registers the EDMA interrupts in AINTC.
*/
static void EDMA3Initialize(void)
{
    /* Configuring the AINTC to receive EDMA3 Interrupts */
    EDMA3IntConfigure();
}

/*
** EDMA3 completion Interrupt Service Routine(ISR).
*/
static void Edma3ComplHandlerIsr(void *dummy)
{
    uint32_t          pendingIrqs;
    volatile uint32_t isIPR  = 0;
    volatile uint32_t isIPRH = 0;

    uint32_t          indexl;
    uint32_t          Cnt = 0;

    indexl = 1;

    isIPR  = EDMA3GetIntrStatus(EDMA_TI814X_U_BASE);
    isIPRH = EDMA3IntrStatusHighGet(EDMA_TI814X_U_BASE);

    if (isIPR)
    {
        while ((Cnt < EDMA3CC_COMPL_HANDLER_RETRY_COUNT) && (indexl != 0))
        {
            indexl = 0;

            pendingIrqs = EDMA3GetIntrStatus(EDMA_TI814X_U_BASE);

            while (pendingIrqs)
            {
                if ((pendingIrqs & 1) == TRUE)
                {
                    /**
                     * If the user has not given any callback function
                     * while requesting the TCC, its TCC specific bit
                     * in the IPR register will NOT be cleared.
                     */
                    /* Here write to ICR to clear the corresponding IPR bits. */
                    EDMA3ClrIntr(EDMA_TI814X_U_BASE, indexl);

                    (*cb_Fxn[indexl])(indexl, EDMA3_XFER_COMPLETE);
                }

                ++indexl;

                pendingIrqs >>= 1;
            }
            Cnt++;
        }
    }

    indexl = 32;

    if (isIPRH)
    {
        while ((Cnt < EDMA3CC_COMPL_HANDLER_RETRY_COUNT) && (indexl != 0))
        {
            indexl = 32;

            pendingIrqs = EDMA3IntrStatusHighGet(EDMA_TI814X_U_BASE);

            while (pendingIrqs)
            {
                if ((pendingIrqs & 1) == TRUE)
                {
                    /**
                     * If the user has not given any callback function
                     * while requesting the TCC, its TCC specific bit
                     * in the IPR register will NOT be cleared.
                     */
                    /* Here write to ICR to clear the corresponding IPR bits. */
                    EDMA3ClrIntr(EDMA_TI814X_U_BASE, indexl);

                    (*cb_Fxn[indexl])(indexl, EDMA3_XFER_COMPLETE);
                }

                ++indexl;

                pendingIrqs >>= 1;
            }
            Cnt++;
        }
    }
}

/* EDMA3 Error Handler */
static void Edma3ErrorHandlerIsr(void *dummy)
{
    volatile uint32_t pendingIrqs   = 0;
    volatile uint32_t pendingHIrqs  = 0;
    uint32_t          txEventHighNo = 0;
    uint32_t          rxEventHighNo = 0;

    pendingIrqs  = EDMA3GetErrIntrStatus(EDMA_TI814X_U_BASE);
    pendingHIrqs = EDMA3ErrIntrHighStatusGet(EDMA_TI814X_U_BASE);

    if (pendingIrqs)
    {
        txEventHighNo = MCSPI_TX_EVENT & 0x1F;
        rxEventHighNo = MCSPI_RX_EVENT & 0x1F;

        if ((pendingIrqs & (0x01 << txEventHighNo)))
        {
            /* clear the pending error interrupt */
            EDMA3ClrMissEvt(EDMA_TI814X_U_BASE, MCSPI_TX_EVENT);

            /* Disable McSPI Transmit event */
            McSPIDMADisable(MCSPI0_BASE_ADDRESS, MCSPI_CH0CONF_DMAW_MASK,
                            MCSPI_CH_NUM);

            /* Disable Edma Transfer */
            EDMA3DisableTransfer(EDMA_TI814X_U_BASE, MCSPI_TX_EVENT,
                                 EDMA3_TRIG_MODE_EVENT);

            flagTx = 1;
        }
        else if ((pendingIrqs & (0x01 << rxEventHighNo)))
        {
            /* clear the pending error interrupt */
            EDMA3ClrMissEvt(EDMA_TI814X_U_BASE, MCSPI_RX_EVENT);

            /* Disable McSPI Receive event */
            McSPIDMADisable(MCSPI0_BASE_ADDRESS, MCSPI_CH0CONF_DMAR_MASK,
                            MCSPI_CH_NUM);

            /* Disable Edma Transfer */
            EDMA3DisableTransfer(EDMA_TI814X_U_BASE, MCSPI_RX_EVENT,
                                 EDMA3_TRIG_MODE_EVENT);

            flagRx = 1;
        }
        else
        {
            /*
             * Do nothing;
             */
        }
    }
    else if (pendingHIrqs)
    {
        txEventHighNo = MCSPI_TX_EVENT - 32;
        rxEventHighNo = MCSPI_RX_EVENT - 32;

        if ((pendingHIrqs & (0x01 << txEventHighNo)))
        {
            /* clear the pending error interrupt */
            EDMA3ClrMissEvt(EDMA_TI814X_U_BASE, MCSPI_TX_EVENT);

            /* Disable McSPI Transmit event */
            McSPIDMADisable(MCSPI0_BASE_ADDRESS, MCSPI_CH0CONF_DMAW_MASK,
                            MCSPI_CH_NUM);

            /* Disable Edma Transfer */
            EDMA3DisableTransfer(EDMA_TI814X_U_BASE, MCSPI_TX_EVENT,
                                 EDMA3_TRIG_MODE_EVENT);

            flagTx = 1;
        }
        else if ((pendingIrqs & (0x01 << rxEventHighNo)))
        {
            /* clear the pending error interrupt */
            EDMA3ClrMissEvt(EDMA_TI814X_U_BASE, MCSPI_RX_EVENT);

            /* Disable McSPI Receive event */
            McSPIDMADisable(MCSPI0_BASE_ADDRESS, MCSPI_CH0CONF_DMAR_MASK,
                            MCSPI_CH_NUM);

            /* Disable Edma Transfer */
            EDMA3DisableTransfer(EDMA_TI814X_U_BASE, MCSPI_RX_EVENT,
                                 EDMA3_TRIG_MODE_EVENT);

            flagRx = 1;
        }
        else
        {
            /*
             * Do nothing;
             */
        }
    }
    else
    {
        /* Events has to be cross bar mapped */
    }
}

/*
** Call back function. Here we disable the Tx/Rx DMA events of McSPI
** peripheral.
*/
static void CallBack(uint32_t tccNum, uint32_t status)
{
    if (tccNum == MCSPI_TX_EVENT)
    {
        flagTx = 1;

        /* Disable McSPI Transmit event */
        McSPIDMADisable(MCSPI0_BASE_ADDRESS, MCSPI_CH0CONF_DMAW_MASK,
                        MCSPI_CH_NUM);
    }

    if (tccNum == MCSPI_RX_EVENT)
    {
        flagRx = 1;

        /* Disable McSPI Receive event */
        McSPIDMADisable(MCSPI0_BASE_ADDRESS, MCSPI_CH0CONF_DMAR_MASK,
                        MCSPI_CH_NUM);
    }
}

/*
** This function is used to set the PaRAM entries of EDMA3 for the Receive
** event of channel 0 of McSPI0 instance. The corresponding EDMA3 channel
** is also enabled for reception.
*/
static void McSpiRxEdmaParamSet(uint32_t tccNum, uint32_t chNum,
                                volatile uint8_t *buffer,
                                uint16_t buffLength,
                                uint32_t destBidxFlag)
{
    EDMA3CCPaRAMEntry paramSet;

    uint8_t          *p     = (uint8_t *) &paramSet;
    uint32_t          index = 0;

    /* Clean-up the contents of structure variable. */
    for (index = 0; index < sizeof (paramSet); index++)
    {
        p[index] = 0;
    }

    /* Fill the PaRAM Set with Receive specific information.*/

    /* srcAddr holds address of SPI Rx FIFO.*/
    paramSet.srcAddr = (uint32_t) (MCSPI_RX0_REG);

    /* destAddr is address of memory location named buffer.*/
    paramSet.destAddr = (uint32_t) buffer;

    /* aCnt holds the number of bytes in an array.*/
    paramSet.aCnt = 1;

    /* bCnt holds the number of such arrays to be transferred.*/
    paramSet.bCnt = buffLength;

    /* cCnt holds the number of frames of aCnt*bBcnt bytes to be transferred.*/
    paramSet.cCnt = 1;

    /* The srcBidx should not be incremented since it is a h/w register.*/
    paramSet.srcBIdx = 0;

    if (TRUE == destBidxFlag)
    {
        /* The destBidx should be incremented for every byte.*/
        paramSet.destBIdx = 1;
    }
    else
    {
        /* The destBidx should not be incremented.*/
        paramSet.destBIdx = 0;
    }

    /* A sync Transfer Mode. */
    /* srCIdx and destCIdx set to zero since ASYNC Mode is used.*/
    paramSet.srcCIdx  = 0;
    paramSet.destCIdx = 0;

    /* Linking transfers in EDMA3 are not used.*/
    paramSet.linkAddr = 0xFFFF;

    paramSet.bCntReload = 0;

    paramSet.opt = 0x00000000;

    /* Set TCC field in OPT with the tccNum.*/
    paramSet.opt |= ((tccNum << EDMA_TPCC_OPT_TCC_SHIFT) &
                     EDMA_TPCC_OPT_TCC_MASK);

    /* EDMA3 Interrupt is enabled and Intermediate Interrupt Disabled.*/
    paramSet.opt |= (1 << EDMA_TPCC_OPT_TCINTEN_SHIFT);

    /* Now write the PaRam Set to EDMA3.*/
    EDMA3SetPaRAM(EDMA_TI814X_U_BASE, chNum, &paramSet);

    /* EDMA3 Transfer is Enabled.*/
    EDMA3EnableTransfer(EDMA_TI814X_U_BASE, chNum, EDMA3_TRIG_MODE_EVENT);
}

/*
** This function is used to set the PaRAM entries of EDMA3 for the Transmit
** Channel 0 of SPI0 instance. The corresponding EDMA3 channel is also enabled
** for transmission.
*/
static void McSpiTxEdmaParamSet(uint32_t tccNum, uint32_t chNum,
                                volatile uint8_t *buffer,
                                uint16_t buffLength)
{
    EDMA3CCPaRAMEntry paramSet;

    uint8_t          *p     = (uint8_t *) &paramSet;
    uint32_t          index = 0;

    /* Clean-up the contents of structure variable. */
    for (index = 0; index < sizeof (paramSet); index++)
    {
        p[index] = 0;
    }

    /* Fill the PaRAM Set with transfer specific information. */

    /* srcAddr holds address of memory location buffer. */
    paramSet.srcAddr = (uint32_t) buffer;

    /* destAddr holds address of McSPI_TX register. */
    paramSet.destAddr = (uint32_t) (MCSPI_TX0_REG);

    /* aCnt holds the number of bytes in an array. */
    paramSet.aCnt = 1;

    /* bCnt holds the number of such arrays to be transferred. */
    paramSet.bCnt = buffLength;

    /* cCnt holds the number of frames of aCnt*bBcnt bytes to be transferred. */
    paramSet.cCnt = 1;

    /*
    ** The srcBidx should be incremented by aCnt number of bytes since the
    ** source used here is memory.
    */
    paramSet.srcBIdx  = 1;
    paramSet.destBIdx = 0;

    /* Async Transfer Mode is set in OPT.*/
    /* srCIdx and destCIdx set to zero since ASYNC Mode is used. */
    paramSet.srcCIdx  = 0;
    paramSet.destCIdx = 0;

    /* Linking transfers in EDMA3 are not used. */
    paramSet.linkAddr   = (EDMA3CC_OPT(DUMMY_CH_NUM));
    paramSet.bCntReload = 0;

    paramSet.opt = 0x00000000;

    /* SAM and DAM fields both are set to 0 */

    /* Set TCC field in OPT with the tccNum. */
    paramSet.opt |= ((tccNum << EDMA_TPCC_OPT_TCC_SHIFT) &
                     EDMA_TPCC_OPT_TCC_MASK);

    /* EDMA3 Interrupt is enabled and Intermediate Interrupt Disabled.*/
    paramSet.opt |= (1 << EDMA_TPCC_OPT_TCINTEN_SHIFT);

    /* Now write the PaRam Set to EDMA3.*/
    EDMA3SetPaRAM(EDMA_TI814X_U_BASE, chNum, &paramSet);

    /* Dummy param set is enabled */
    TxDummyPaRAMConfEnable();

    /* EDMA3 Transfer is Enabled. */
    EDMA3EnableTransfer(EDMA_TI814X_U_BASE, chNum, EDMA3_TRIG_MODE_EVENT);
}

/*
** This function allocates EDMA3 channels to McSPI0 for trasmisssion and
** reception purposes.
*/
static void RequestEDMA3Channels(void)
{
    /* Request DMA Channel and TCC for SPI Transmit*/
    EDMA3RequestChannel(EDMA_TI814X_U_BASE, EDMA3_CHANNEL_TYPE_DMA, \
                        MCSPI_TX_EVENT, MCSPI_TX_EVENT, EVT_QUEQUE_NUM);

    /* Request DMA Channel and TCC for SPI Receive*/
    EDMA3RequestChannel(EDMA_TI814X_U_BASE, EDMA3_CHANNEL_TYPE_DMA, \
                        MCSPI_RX_EVENT, MCSPI_RX_EVENT, EVT_QUEQUE_NUM);
}

/*
** This function configures the AINTC to receive EDMA3 interrupts.
*/
static void EDMA3IntConfigure(void)
{
#ifdef _TMS320C6X
    /* Initialize DSP interrupt controller and enable interrupts */
    IntDSPINTCInit();
    IntGlobalEnable();

    /* Map EDMA events to DSP interrupts */
    IntRegister(4, Edma3ComplHandlerIsr);
    IntEventMap(4, SYS_INT_EDMACOMPINT);
    IntEnable(4);

    IntRegister(5, Edma3ErrorHandlerIsr);
    IntEventMap(5, SYS_INT_EDMAERRINT);
    IntEnable(5);
#else

    Intc_Init();
    Intc_IntEnable(0);

#if defined (BUILD_A8)
    /* Cortex A8 interrupt configuration        */
    Intc_IntRegister(EDMA3_CC_XFER_COMPLETION_INT_A8,
                     (IntrFuncPtr) Edma3ComplHandlerIsr,
                     NULL);
    Intc_SystemEnable(EDMA3_CC_XFER_COMPLETION_INT_A8);

    Intc_IntRegister(EDMA3_ERROR_INT_A8, (IntrFuncPtr) Edma3ErrorHandlerIsr,
                     NULL);
    Intc_SystemEnable(EDMA3_ERROR_INT_A8);
#endif

#if defined (BUILD_M3VPSS)
    /* M3vpss interrupt configuration           */
    Intc_IntRegister(EDMA3_CC_XFER_COMPLETION_INT_M3VPSS,
                     (IntrFuncPtr) Edma3ComplHandlerIsr,
                     NULL);
    Intc_SystemEnable(EDMA3_CC_XFER_COMPLETION_INT_M3VPSS);

    Intc_IntRegister(EDMA3_ERROR_INT_M3VPSS, (IntrFuncPtr) Edma3ErrorHandlerIsr,
                     NULL);
    Intc_SystemEnable(EDMA3_ERROR_INT_M3VPSS);

#elif defined (BUILD_M3VIDEO)
    /* M3video interrupt configuration          */
    Intc_IntRegister(EDMA3_CC_XFER_COMPLETION_INT_M3VIDEO,
                     (IntrFuncPtr) Edma3ComplHandlerIsr,
                     NULL);
    Intc_SystemEnable(EDMA3_CC_XFER_COMPLETION_INT_M3VIDEO);

    Intc_IntRegister(EDMA3_ERROR_INT_M3VIDEO,
                     (IntrFuncPtr) Edma3ErrorHandlerIsr,
                     NULL);
    Intc_SystemEnable(EDMA3_ERROR_INT_M3VIDEO);
#endif

#endif
}

/*
** This configures the PaRAM set for the Dummy Transfer.
*/
static void TxDummyPaRAMConfEnable(void)
{
    EDMA3CCPaRAMEntry dummyPaRAMSet;

    EDMA3GetPaRAM(EDMA_TI814X_U_BASE, DUMMY_CH_NUM, &dummyPaRAMSet);

    dummyPaRAMSet.aCnt       = 1;
    dummyPaRAMSet.bCnt       = 0;
    dummyPaRAMSet.cCnt       = 0;
    dummyPaRAMSet.srcAddr    = 0;
    dummyPaRAMSet.destAddr   = 0;
    dummyPaRAMSet.srcBIdx    = 0;
    dummyPaRAMSet.destBIdx   = 0;
    dummyPaRAMSet.srcCIdx    = 0;
    dummyPaRAMSet.destCIdx   = 0;
    dummyPaRAMSet.linkAddr   = 0xFFFFU;
    dummyPaRAMSet.bCntReload = 0;
    dummyPaRAMSet.opt        = 0;

    EDMA3SetPaRAM(EDMA_TI814X_U_BASE, DUMMY_CH_NUM, &dummyPaRAMSet);
}

uint32_t EDMAVersionGet(void)
{
    return EDMA_REVID_AM335X;
}

#endif
/********************************* End Of File ******************************/
