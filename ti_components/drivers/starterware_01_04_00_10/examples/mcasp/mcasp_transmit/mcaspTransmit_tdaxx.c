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
 * @file mcaspTransmit.c
 *
 * This file contains the McASP application, designed to meet specific
 * requirements -
 * 1. Showcase bit clock of 10MHz
 * 2. Data output on two data lines
 * 3. The McASP to output the data on the lines and observe the same on the CRO.
 *
 * @path  $(ds)\examples\mcasp\mcspiTransmit.c
 *
 * @rev  00.01
 */

/******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************/
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "hw_types.h"
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include "mcasp.h"
#include "edma.h"
#include "soc_defines.h"
#include "platform.h"
#include "interrupt.h"
#include "soc.h"
#include "hsi2c.h"
#include "hw_ctrl_core_pad_io.h"

#if (defined (BUILD_M4) || defined (BUILD_A15))
    #include "irq_xbar.h"
#endif
#ifndef SOC_EDMA_TPCC_BASE /* Temporary HACK for Vayu M4 */
#if defined (BUILD_M4)
/* EDMA region 0x43300000 mappped to 0xA0000000 */
#define SOC_EDMA_TPCC_BASE      (0x63300000U)
#endif
#endif

/******************************************************************************
**                      INTERNAL MACRO DEFINITIONS
******************************************************************************/
#ifdef TDA2XX_FAMILY_BUILD
#define SOC_MCASP_CFG_BASE SOC_MCASP3_CFG_BASE
#define SOC_MCASP_BASE SOC_MCASP3_BASE
#define SOC_MCASP_3_FIFO_REGS (SOC_MCASP_CFG_BASE + 0x1000)
#define MCASP_RX_DMA_XBAR_INST            (132U)
#define MCASP_TX_DMA_XBAR_INST            (133U)
#else
#define SOC_MCASP_CFG_BASE SOC_MCASP1_CFG_BASE
#define SOC_MCASP_BASE SOC_MCASP1_BASE
#define SOC_MCASP_1_FIFO_REGS (SOC_MCASP_CFG_BASE + 0x1000)
#define MCASP_RX_DMA_XBAR_INST            (128U)
#define MCASP_TX_DMA_XBAR_INST            (129U)
#endif

/*
** Values which are configurable
*/
/* Slot size to send/receive data */
#define SLOT_SIZE                         (32U)

/* Word size to send/receive data. Word size <= Slot size */
#define WORD_SIZE                         (32U)

/* Number of channels, L & R */
#define NUM_I2S_CHANNELS                  (2U)

/* Number of samples to be used per audio buffer */
#define NUM_SAMPLES_PER_AUDIO_BUF         (2000U)

/* Number of buffers used per tx/rx */
#define NUM_BUF                           (3U)

/* Number of linked parameter set used per tx/rx */
#define NUM_PAR                           (2U)

/* Specify where the parameter set starting is */
#define PAR_ID_START                      (72U)

/* Number of samples in loop buffer */
#define NUM_SAMPLES_LOOP_BUF              (10U)

/* McASP Serializer 0 for Transmit */
#define MCASP_XSER_TX_0                   (0U)

/* McASP Serializer 1 for Transmit */
#define MCASP_XSER_TX_1                   (1U)

/*
** Below Macros are calculated based on the above inputs
*/

#define I2S_SLOTS                         ((1 << NUM_I2S_CHANNELS) - 1)

#define BYTES_PER_SAMPLE                  ((WORD_SIZE >> 3) \
                                           * NUM_I2S_CHANNELS)

#define AUDIO_BUF_SIZE                    (NUM_SAMPLES_PER_AUDIO_BUF \
                                           * BYTES_PER_SAMPLE)

#define TX_DMA_INT_ENABLE                 (EDMA3CC_OPT_TCC_SET            \
                                               (EDMA3_CHA_MCASP_TX) | (1  \
                                                                       << \
                                                                       EDMA_TPCC_OPT_TCINTEN_SHIFT))

#define PAR_TX_START                      (PAR_ID_START)

/*
** Definitions which are not configurable
*/
#define SIZE_PARAMSET                     (32U)
#define OPT_FIFO_WIDTH                    (0x02 << 8U)

/*
** Definitions which are configurable depending on the core to be used(ARM here)
*/
#define EDMA3_CHA_MCASP_RX               (4)
#define EDMA3_CHA_MCASP_TX               (5)

#define EDMA3_CC_REGION_A15               (0U)
#define EDMA3_CC_REGION_M4                (1U)

#define EDMA3_CC_QUEUE                    (0U)

#define EDMA3_CC_XFER_COMPLETION_INT_A15  (12U)
#define EDMA3_CC_XFER_COMPLETION_INT_M4   (34U)

#ifdef BUILD_A15
#define EDMA3_CC_XFER_COMPLETION_INT EDMA3_CC_XFER_COMPLETION_INT_A15
#elif defined (BUILD_M4)
#define EDMA3_CC_XFER_COMPLETION_INT EDMA3_CC_XFER_COMPLETION_INT_M4
#endif

#define INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_MASK (0x00FF0000U)
#define INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_SHIFT (0x00000010U)
#define INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_RESETVAL (0x00000000U)

#define INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_MASK (0x000000FFU)
#define INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_SHIFT (0x00000000U)
#define INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_RESETVAL (0x00000000U)

#define EDMA3_MAX_CROSS_BAR_EVENTS_TI814X (230U)

#define EDMA3_EVENT_MUX_REG_BASE_ADDR               (0x4a002c78)

/*
** Definitions which are configurable depending on the application requirement
*/
#define MCASP_ACLKX_CLKXDIV_VALUE         (0x2U)
#define MCASP_AHCLKX_HCLKXDIV_VALUE       (0x5U)

#define HSI2C_SLAVE_ADDR                  (0x26)

#ifdef TDA2EX_BUILD
#define SOC_I2Cx_BASE                  (SOC_I2C5_BASE)
#else
#define SOC_I2Cx_BASE                  (SOC_I2C2_BASE)
#endif

/******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
******************************************************************************/
static void EDMA3IntSetup(void);
static void I2SDMAParamInit(void);
static void McASPI2SConfigure(void);
static void I2SDataTxActivate(void);
static void McASPTxDMAComplHandler(void);
static void EDMA3CCComplIsr(void *dummy);
static void ParamTxLoopJobSet(uint16_t parId);

/******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
******************************************************************************/

/* Global counters to keep track of errors. Can be removed before releasing  */
uint32_t                       complInterruptCounter = 0x00;
uint32_t                       errInterruptCounter   = 0x00;

uint8_t                        dataToSlave;
uint8_t                        dataFromSlave;

/*
** Transmit buffers. If any new buffer is to be added, define it here and
** update the NUM_BUF.
*/
static uint8_t                 txBuf0[AUDIO_BUF_SIZE];
static uint8_t                 txBuf1[AUDIO_BUF_SIZE];
static uint8_t                 txBuf2[AUDIO_BUF_SIZE];

/*
** The offset of the paRAM ID sent, from starting of the paRAM set.
*/
static volatile uint16_t       parOffSent = 0;

typedef struct  {
    volatile unsigned int TPCC_EVTMUX[32];
} IntmuxRegs;

typedef volatile IntmuxRegs *IntmuxRegsOvly;

/******************************************************************************
**                      INTERNAL CONSTANT DEFINITIONS
******************************************************************************/
/* Array of transmit buffer pointers */
static uint32_t const          txBufPtr[NUM_BUF] =
{
    (uint32_t) txBuf0,
    (uint32_t) txBuf1,
    (uint32_t) txBuf2
};

/*
** Default paRAM for Transmit section. This will be transmitting from
** a loop buffer.
*/
static EDMA3CCPaRAMEntry const txDefaultPar =
{
    (uint32_t) (OPT_FIFO_WIDTH),               /* Opt field */
    (uint32_t) txBuf0,                         /* source address */
    (uint16_t) (BYTES_PER_SAMPLE),             /* aCnt */
    (uint16_t) (NUM_SAMPLES_LOOP_BUF),         /* bCnt */
    (uint32_t) (SOC_MCASP_BASE),               /* dest address */
    (uint16_t) (BYTES_PER_SAMPLE),             /* source bIdx */
    (uint16_t) (0),                            /* dest bIdx */
    (uint16_t) (PAR_TX_START * SIZE_PARAMSET), /* link address */
    (uint16_t) (0),                            /* bCnt reload value */
    (uint16_t) (0),                            /* source cIdx */
    (uint16_t) (0),                            /* dest cIdx */
    (uint16_t) 1                               /* cCnt */
};

/******************************************************************************
**                          FUNCTION DEFINITIONS
******************************************************************************/

void SetupI2C(uint8_t addr)
{
    /* Put i2c in reset/disabled state */
    I2CMasterDisable(SOC_I2Cx_BASE);

    /* Configure i2c bus speed to 100khz */
    I2CMasterInitExpClk(SOC_I2Cx_BASE, 24000000,
                        8000000, 100000);

    I2CMasterEnableFreeRun(SOC_I2Cx_BASE);

    /* Set i2c slave address */
    I2CMasterSlaveAddrSet(SOC_I2Cx_BASE, addr);

    /* Bring i2c out of reset */
    I2CMasterEnable(SOC_I2Cx_BASE);
}

void SetupI2CTransmit(void)
{
    /* Set data count */
    I2CSetDataCount(SOC_I2Cx_BASE, 2);

    /*
    ** Configure i2c as master-transmitter and to generate stop condition
    */
    I2CMasterControl(SOC_I2Cx_BASE, I2C_CFG_MST_TX);

    /*Enable transmit ready and stop condition interrupt*/
    I2CMasterIntEnableEx(SOC_I2Cx_BASE,
                         I2C_INT_TRANSMIT_READY | I2C_INT_STOP_CONDITION);

    /*Generate start conndition*/
    I2CMasterStart(SOC_I2Cx_BASE);

    /*Wait for transmit interrupt to occur*/
    while (I2CMasterIntStatusEx(SOC_I2Cx_BASE, I2C_INT_TRANSMIT_READY) != 0x10) ;

    /*Disable transmit ready and stop condition interrupt*/
    I2CMasterIntDisableEx(SOC_I2Cx_BASE, I2C_INT_TRANSMIT_READY);

    I2CMasterIntDisableEx(SOC_I2Cx_BASE, I2C_INT_STOP_CONDITION);

    /* Send first command word and then the data */
    I2CMasterDataPut(SOC_I2Cx_BASE, 0x00);
    I2CMasterDataPut(SOC_I2Cx_BASE, 0x00);
}

/*
** Assigns loop job for a parameter set
*/
static void ParamTxLoopJobSet(uint16_t parId)
{
    EDMA3CCPaRAMEntry paramSet;

    memcpy(&paramSet, &txDefaultPar, SIZE_PARAMSET - 2);

    /* link the paRAM to itself */
    paramSet.linkAddr = parId * SIZE_PARAMSET;
    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, parId, &paramSet);
}

/*
** Initializes the DMA parameters.
** The TX basic paRAM set (channel) is 12.
**
** The TX paRAM sets will be initialized to transmit from the loop buffer.
** The size of the loop buffer can be configured.
** The transfer completion interrupt will not be enabled for paRAM set 1;
** paRAM set 1 will be linked to linked paRAM set starting (PAR_TX_START) of TX.
** All other paRAM sets will be linked to itself.
** and further transmission only happens via linked paRAM set.
** For example, if the PAR_TX_START value is 72, and the number of paRAMS is 2,
** So transmission paRAM set linking will be initialized as 1-->72-->73, 73->73.
*/
static void I2SDMAParamInit(void)
{
    EDMA3CCPaRAMEntry paramSet;
    int i = 0;

    /* Initialize TX Buffers
     *
     * These patterns are seen/output on serializer0 and serializer1
     */
    for (i = 0; i < (AUDIO_BUF_SIZE / 4); i++)
    {
        if (0 == (i % 2))
        {
            int index;
            for (index = 0; index < 4; index++)
            {
                /* '0xF0' data pattern that yields freq of 1/8 of bit clock */
                txBuf0[4 * i + index] = 0xF0U;
                txBuf1[4 * i + index] = 0xF0U;
                txBuf2[4 * i + index] = 0xF0U;
            }
        }
        else
        {
            int index;
            for (index = 0; index < 4; index++)
            {
                /* '0xCC' data pattern that yields freq of 1/4 of bit clock */
                txBuf0[4 * i + index] = 0xCCU;
                txBuf1[4 * i + index] = 0xCCU;
                txBuf2[4 * i + index] = 0xCCU;
            }
        }
    }

    /* Initialize the 1st paRAM set for transmit */
    memcpy(&paramSet, &txDefaultPar, SIZE_PARAMSET - 2);

    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, EDMA3_CHA_MCASP_TX, &paramSet);

    memcpy(&paramSet, &txDefaultPar, SIZE_PARAMSET - 2);
    /* Enable Intr for Link Channel */
    paramSet.opt     |= TX_DMA_INT_ENABLE;
    paramSet.srcAddr  = txBufPtr[1];
    paramSet.linkAddr = (PAR_TX_START * SIZE_PARAMSET);
    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, (PAR_TX_START), &paramSet);

    memcpy(&paramSet, &txDefaultPar, SIZE_PARAMSET - 2);
    paramSet.srcAddr = txBufPtr[2];
    /* Self Link here */
    paramSet.linkAddr = ((PAR_TX_START + 1) * SIZE_PARAMSET);

    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, (PAR_TX_START + 1), &paramSet);
}

/*
** Configures the McASP Transmit Section in I2S mode.
*/
static void McASPI2SConfigure(void)
{
    McASPTxReset(SOC_MCASP_CFG_BASE);

    /* Enable the FIFOs for DMA transfer */
    McASPWriteFifoEnable(SOC_MCASP_CFG_BASE, 2, 1);

    /* Set I2S format in the transmitter/receiver format units */
    McASPTxFmtI2SSet(SOC_MCASP_CFG_BASE, WORD_SIZE, SLOT_SIZE,
                     MCASP_TX_MODE_DMA);

    McASPTxFrameSyncCfg(SOC_MCASP_CFG_BASE, 2, MCASP_TX_FS_WIDTH_WORD,
                        MCASP_TX_FS_EXT_BEGIN_ON_FALL_EDGE |
                        MCASP_TX_FS_INTERNAL);

    /* configure the clock for transmitter */
    McASPTxClkCfg(SOC_MCASP_CFG_BASE, MCASP_TX_CLK_INTERNAL,
                  ((MCASP_ACLKX_CLKXDIV_VALUE &
                    MCASP_ACLKXCTL_CLKXDIV_MASK) >>
                   MCASP_ACLKXCTL_CLKXDIV_SHIFT),
                  ((MCASP_AHCLKX_HCLKXDIV_VALUE &
                    MCASP_AHCLKXCTL_HCLKXDIV_MASK) >>
                   MCASP_AHCLKXCTL_HCLKXDIV_SHIFT));

    McASPTxClkPolaritySet(SOC_MCASP_CFG_BASE, MCASP_TX_CLK_POL_FALL_EDGE);

    McASPTxClkCheckConfig(SOC_MCASP_CFG_BASE, MCASP_TX_CLKCHCK_DIV32,
                          0x00, 0xFF);

    /* Enable the transmitter/receiver slots. I2S uses 2 slots */
    McASPTxTimeSlotSet(SOC_MCASP_CFG_BASE, I2S_SLOTS);

    /*
    ** Set the serializers
    */
    McASPSerializerTxSet(SOC_MCASP_CFG_BASE, MCASP_XSER_TX_0);
    McASPSerializerTxSet(SOC_MCASP_CFG_BASE, MCASP_XSER_TX_1);

    /*
    ** Configure the McASP pins
    ** Output - Frame Sync, Clock, Serializer Rx and Serializer Tx
    **          (Clocks generated internally)
    */
    McASPPinMcASPSet(SOC_MCASP_CFG_BASE, (MCASP_PIN_AFSR |
                                          MCASP_PIN_ACLKR | MCASP_PIN_AFSX |
                                          MCASP_PIN_AHCLKX |
                                          MCASP_PIN_ACLKX |
                                          MCASP_PIN_AMUTE |
                                          MCASP_PIN_AXR(MCASP_XSER_TX_0) |
                                          MCASP_PIN_AXR(MCASP_XSER_TX_1)));

    McASPPinDirOutputSet(SOC_MCASP_CFG_BASE, MCASP_PIN_AFSR);
    McASPPinDirOutputSet(SOC_MCASP_CFG_BASE, MCASP_PIN_ACLKR);

    McASPPinDirOutputSet(SOC_MCASP_CFG_BASE, MCASP_PIN_AFSX);

    /* Configure high clock as Output */
    McASPPinDirOutputSet(SOC_MCASP_CFG_BASE, MCASP_PIN_AHCLKX);

    McASPPinDirOutputSet(SOC_MCASP_CFG_BASE, MCASP_PIN_ACLKX);

    /* Both Serializers used to output data out */
    McASPPinDirOutputSet(SOC_MCASP_CFG_BASE, MCASP_PIN_AXR(MCASP_XSER_TX_0));
    McASPPinDirOutputSet(SOC_MCASP_CFG_BASE, MCASP_PIN_AXR(MCASP_XSER_TX_1));
}

/*
** Sets up the interrupts for EDMA in AINTC
*/
static void EDMA3IntSetup(void)
{
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

    Intc_IntRegister(EDMA3_CC_XFER_COMPLETION_INT,
                     (IntrFuncPtr) EDMA3CCComplIsr,
                     NULL);

    Intc_IntPrioritySet(EDMA3_CC_XFER_COMPLETION_INT, 1, 0);
    Intc_SystemEnable(EDMA3_CC_XFER_COMPLETION_INT);
}

/*
** Activates the data transmission/reception
** The DMA parameters shall be ready before calling this function.
*/
static void I2SDataTxActivate(void)
{
    /* Start the clocks */
    McASPTxClkStart(SOC_MCASP_CFG_BASE, MCASP_TX_CLK_INTERNAL);

    /* Enable EDMA for the transfer */
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE, EDMA3_CHA_MCASP_TX,
                        EDMA3_TRIG_MODE_EVENT);

    /* Activate the  serializers */
    McASPTxSerActivate(SOC_MCASP_CFG_BASE);

    /* make sure that the XDATA bit is cleared to zero */
    while (McASPTxStatusGet(SOC_MCASP_CFG_BASE) & MCASP_TX_STAT_DATAREADY) ;

    /* Activate the state machines */
    McASPTxEnable(SOC_MCASP_CFG_BASE);
}

void sampleConfigScr(unsigned int eventNum,
                     unsigned int chanNum)
{
    unsigned int   scrChanOffset = 0;
    unsigned int   scrRegOffset  = 0;
    unsigned int   xBarEvtNum    = 0;
    IntmuxRegsOvly scrEvtMux     =
        (IntmuxRegsOvly) (EDMA3_EVENT_MUX_REG_BASE_ADDR);

    if ((eventNum < EDMA3_MAX_CROSS_BAR_EVENTS_TI814X) &&
        (chanNum < EDMA3_NUM_TCC))
    {
        scrRegOffset  = chanNum / 2;
        scrChanOffset = chanNum - (scrRegOffset * 2);
        xBarEvtNum    = (eventNum + 1);

        switch (scrChanOffset)
        {
            case 0:
                scrEvtMux->TPCC_EVTMUX[scrRegOffset] &=
                    ~(INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_MASK);
                scrEvtMux->TPCC_EVTMUX[scrRegOffset] |=
                    (xBarEvtNum & INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_MASK);
                break;
            case 1:
                scrEvtMux->TPCC_EVTMUX[scrRegOffset] &=
                    ~(INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_MASK);
                scrEvtMux->TPCC_EVTMUX[scrRegOffset] |=
                    ((xBarEvtNum <<
                      INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_SHIFT) &
                     (INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_MASK));
                break;
            default:
                break;
        }
    }
}

void Configure_Edma_xbar()
{
    sampleConfigScr(MCASP_RX_DMA_XBAR_INST, EDMA3_CHA_MCASP_TX);
}

/*
** The main function. Application starts here.
*/
int main(void)
{
    uint32_t loopHere = 1;

    /*Unlock the Control registers */
    PlatformUnlockMMR();

#ifdef TDA2XX_FAMILY_BUILD
    /* Pad mux configuration for McASP instance 3 */
    PlatformMCASP3SetPinMux();
    /* Power on McASP instance 3 */
    PlatformMCASP3PrcmEnable();
#else
    /* Pad mux configuration for McASP instance 1 */
    PlatformMCASP1SetPinMux();
    /* Power on McASP instance 1 */
    PlatformMCASP1PrcmEnable();
#endif

#ifdef TDA2EX_BUILD
    /* Pad mux configuration for I2C instance 5 */
    PlatformI2C5SetPinMux();
#else
    /* Pad mux configuration for I2C instance 2 */
    PlatformI2C2SetPinMux();
#endif

    SetupI2C(HSI2C_SLAVE_ADDR);

    /*Clear 6th bit i.e VIN6_SEL_S0 line*/
    SetupI2CTransmit();

#if defined (BUILD_A15)
    EDMAsetRegion(EDMA3_CC_REGION_A15);
#elif defined (BUILD_M4)
    EDMAsetRegion(EDMA3_CC_REGION_M4);
#endif

    EDMA3Init(SOC_EDMA_TPCC_BASE, EDMA3_CC_QUEUE);

    EDMA3IntSetup();

    Configure_Edma_xbar();

    /* Request EDMA channels */
    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE,
                        EDMA3_CHANNEL_TYPE_DMA,
                        EDMA3_CHA_MCASP_TX,
                        EDMA3_CHA_MCASP_TX,
                        EDMA3_CC_QUEUE);

    /* Initialize the DMA parameters */
    I2SDMAParamInit();

    /* Configure the McASP for I2S */
    McASPI2SConfigure();

    /* Activate the audio transmission and reception */
    I2SDataTxActivate();

    /*
    ** Loop forever.
    */
    while (loopHere) ;

    return 0;
}

/*
** This function will be called once transmit DMA is completed
*/
static void McASPTxDMAComplHandler(void)
{
    /* Buffers can be updated here, if required */
    ParamTxLoopJobSet((uint16_t) (PAR_TX_START + parOffSent));

    parOffSent = (parOffSent + 1) % NUM_PAR;
}

/*
** EDMA transfer completion ISR
*/
static void EDMA3CCComplIsr(void *dummy)
{
    /* Check if transmit DMA completed */
    if (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE) & (1 << EDMA3_CHA_MCASP_TX))
    {
        /* Clear the interrupt status for the first channel */
        EDMA3ClrIntr(SOC_EDMA_TPCC_BASE, EDMA3_CHA_MCASP_TX);
        McASPTxDMAComplHandler();
    }
    ++complInterruptCounter;
}

/***************************** End Of File ***********************************/
