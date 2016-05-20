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
 * @file mcaspBurstTransmit_tda2xx.c
 *
 * This file contains the McASP application, designed to meet specific
 * requirements -
 * 1. Burst Mode Support on A15, M4 using EDMA Manual Trigger Mode.
 * 2. Demonstrate Burst Transfer of 128 bytes in Single Burst and no
 *    intermediate transfers
 * 3. Synchronization using Interrupt and Polled Mechanism between EDMA
 *    Transfers and Buffers
 * 4. HW Ping Pong Buffer Mechanism.
 * 5. Data Packets to be sent at different user configurable Delays,
 * 6. Update User Configurable Buffer Params
 * Output : To probe data on CRO as we do not have any slave on Board.
 *
 * @path  $(ds)\examples\mcasp\mcasp_bursttransmit\mcaspBurstTransmit_tda2xx.c
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

#ifndef SOC_EDMA_TPCC_BASE

#if (defined (BUILD_A15))

#define SOC_EDMA_TPCC_BASE      (0x43300000U)

#elif defined (BUILD_M4)

#define SOC_EDMA_TPCC_BASE      (0x63300000U)

#endif
#endif

/******************************************************************************
**                      INTERNAL MACRO DEFINITIONS
******************************************************************************/

/*
 * Enable Polled Mode by defining below Macro
 * #define CONFIG_POLLED_MODE
 */

/*
** Values which are configurable
*/
/* Slot size to send/receive data */
#define SLOT_SIZE                         (32U)

/* Word size to send/receive data. Word size <= Slot size */
#define WORD_SIZE                         (32U)

/* Number of channels, L & R */
#define NUM_I2S_CHANNELS                  (1U)

/* Number of samples to be used per audio buffer */
#define NUM_SAMPLES_PER_BURST         (2000U)

/* Number of buffers used per tx/rx */
#define NUM_BUF                           (3U)

/* Number of linked parameter set used per tx/rx */
#define NUM_PAR                           (2U)

/* Specify where the parameter set starting is */
#define PAR_ID_START                      (72U)

/* Number of samples in loop buffer */
#define NUM_SAMPLES_LOOP_BUF              (1U)

/* McASP Serializer 0 for Transmit */
#define MCASP_XSER_TX_0                   (0U)

/* McASP Serializer 1 for Transmit */
#define MCASP_XSER_TX_1                   (1U)

/* McASP Serializer 2 for Transmit */
#define MCASP_XSER_TX_2               (2U)

/* McASP Serializer 3 for Transmit */
#define MCASP_XSER_TX_3               (3U)

/* McASP Serializer 4 for Transmit */
#define MCASP_XSER_TX_4               (4U)

/* McASP Serializer 5 for Transmit */
#define MCASP_XSER_TX_5               (5U)

/* McASP Serializer 6 for Transmit */
#define MCASP_XSER_TX_6               (6U)

/* McASP Serializer 7 for Transmit */
#define MCASP_XSER_TX_7               (7U)

/* McASP Serializer 8 for Transmit */
#define MCASP_XSER_TX_8               (8U)

/* McASP Serializer 9 for Transmit */
#define MCASP_XSER_TX_9               (9U)

/*
** Below Macros are calculated based on the above inputs
*/

#define BURST_SLOTS                         1

#define WORDS_PER_SER (WORD_SIZE >> 3)

#define WORD_CFG_PING_PONG      (0x21)

#define NUM_SERZ      (1U)

#define MAX_NUM_SERZ      (10U)

#define BYTES_PER_SAMPLE                  ((WORD_SIZE >> 3) \
                                           * NUM_I2S_CHANNELS)

#define BURST_BUF_SIZE                    (NUM_SAMPLES_PER_BURST \
                                           * BYTES_PER_SAMPLE)

#define TX_DMA_INT_ENABLE                 (EDMA3CC_OPT_TCC_SET             \
                                               (EDMA3_CHA_MCASP3_TX) | (1  \
                                                                        << \
                                                                        EDMA_TPCC_OPT_TCINTEN_SHIFT))

#define TX_DMA_INT_INT_ENABLE                 (EDMA3CC_OPT_TCC_SET             \
                                                   (EDMA3_CHA_MCASP3_TX) | (1  \
                                                                            << \
                                                                            EDMA_TPCC_OPT_ITCINTEN_SHIFT))

#define PAR_TX_START                      (PAR_ID_START)

/*
** Definitions which are not configurable
*/
#define SIZE_PARAMSET                     (32U)
#define OPT_FIFO_WIDTH                    (0x02 << 8U)

/*
** Definitions which are configurable depending on the core to be used(ARM here)
*/
#define EDMA3_CHA_MCASP3_RX               (4)
#define EDMA3_CHA_MCASP3_TX               (5)

#define EDMA3_CC_REGION_A15                (0U)
#define EDMA3_CC_REGION_M4            (1U)

#define EDMA3_CC_QUEUE                    (0U)

#define EVENT_TRIGGER 0
#define MANUAL_TRIGGER 1

#define EDMA3_CC_XFER_COMPLETION_INT_A15                (12U)
#define EDMA3_CC_XFER_COMPLETION_INT_M4                 (34U)

#ifdef BUILD_A15
#define EDMA3_CC_XFER_COMPLETION_INT EDMA3_CC_XFER_COMPLETION_INT_A15
#define MCASP3_TX_IRQ_NUM   65

#elif defined (BUILD_M4)
#define EDMA3_CC_XFER_COMPLETION_INT EDMA3_CC_XFER_COMPLETION_INT_M4
#define MCASP3_TX_IRQ_NUM   51
#endif

#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_MASK (0x00FF0000U)
#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_SHIFT (0x00000010U)
#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_RESETVAL (0x00000000U)

#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_MASK (0x000000FFU)
#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_SHIFT (0x00000000U)
#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_RESETVAL (0x00000000U)

#define EDMA3_MAX_CROSS_BAR_EVENTS_TI814X (230U)

#define EDMA3_EVENT_MUX_REG_BASE_ADDR               (0x4a002c78)

#define MCASP3_RX_DMA_XBAR_INST            (132U)
#define MCASP3_TX_DMA_XBAR_INST            (133U)
/*
** Definitions which are configurable depending on the application requirement
*/
#define MCASP_ACLKX_CLKXDIV_VALUE         (0x4U)
#define MCASP_AHCLKX_HCLKXDIV_VALUE       (0x10U)

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
static void McASPBurstConfigure(void);
static void DataTxActivate(void);
static void McASPTxDMAComplHandler(void);
static void EDMA3CCComplIsr(void *dummy);
static void mcasp3_platform_init();
static void mcasp3_edma_init();
static void mcasp3_intsetup(void);
static void mcasp3_AxevtIsr(void *dummyPtr);

void sampleDelay(int32_t delay);

/******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
******************************************************************************/

/* Global counters to keep track of errors. Can be removed before releasing  */
uint32_t                       errInterruptCounter = 0x00;
uint32_t                       delayCounter        = (5000U);

uint8_t                        dataToSlave;
uint8_t                        dataFromSlave;

EDMA3CCPaRAMEntry              dummyPaRAMSet, dummyPaRAMSet2;

/*
** Transmit buffers. If any new buffer is to be added, define it here and
** update the NUM_BUF.
*/
static uint8_t                 txBuf0[BURST_BUF_SIZE];

/*
** The offset of the paRAM ID sent, from starting of the paRAM set.
*/
static volatile uint16_t       parOffSent = 0;

typedef struct  {
    volatile unsigned int TPCC_EVTMUX[32];
} CSL_IntmuxRegs;

typedef volatile CSL_IntmuxRegs *CSL_IntmuxRegsOvly;
/******************************************************************************
**                      INTERNAL CONSTATNT DEFINITIONS
******************************************************************************/

/*
** Default paRAM for Transmit section. This will be transmitting from
** a loop buffer.
*/
static EDMA3CCPaRAMEntry const txDefaultPar =
{
    (uint32_t) (OPT_FIFO_WIDTH),                  /* Opt field */
    (uint32_t) txBuf0,                            /* source address */
    (uint16_t) (BYTES_PER_SAMPLE * MAX_NUM_SERZ), /* aCnt */
    (uint16_t) (1),                               /* bCnt */
    (uint32_t) SOC_MCASP3_BASE,                   /* dest address */
    (uint16_t) (1),                               /* source bIdx */
    (uint16_t) (0),                               /* dest bIdx */
    (uint16_t) (0xFFFF),                          /* link address */
    (uint16_t) (1),                               /* bCnt reload value */
    (int16_t) 0,                                  /* source cIdx */
    (uint16_t) (0),                               /* dest cIdx */
    (uint16_t)   1                                /* cCnt */
};

/******************************************************************************
**                          FUNCTION DEFINITIONS
******************************************************************************/

void sampleDelay(int32_t delay)
{
    volatile int32_t i, j;

    for (i = 0; i < delay; i++)
    {
        for (j = 0; j < 100; j++) ;
    }
}

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
** Initializes the DMA parameters.
** The TX paRAM sets will be initialized to transmit .
** The transfer completion interrupt will be enabled for paRAM set;
** Manual Trigger Mode is used for the Burst Mode Configuration
** Transmission happens in burst transfers with aCount value
** until all the data is sent out.
** We give a delay once the transfer is completed and next paRAM set can be
** loaded in ISR Call
*/
static void BurstDMAParamInit(void)
{
    EDMA3CCPaRAMEntry paramSet;
    int i = 0;
    static uint8_t    data;
    data = 0x00;
    /* Initialize TX Buffers
     *
     * These patterns are seen/output on serializer0
     */
    for (i = 0; i < BURST_BUF_SIZE; i++)
    {
        txBuf0[i] = data++;
    }

    /* Initialize the paRAM set for transmit */
    memcpy(&paramSet, &txDefaultPar, SIZE_PARAMSET);

    paramSet.opt |= TX_DMA_INT_ENABLE;

    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, EDMA3_CHA_MCASP3_TX, &paramSet);
}

/*
** Configures the McASP Transmit Section in Burst mode.
*/
static void McASPBurstConfigure(void)
{
    McASPTxReset(SOC_MCASP3_CFG_BASE);

    /* Enable the FIFOs for DMA transfer */

    McASPWriteFifoEnable(SOC_MCASP3_CFG_BASE, NUM_SERZ, WORD_CFG_PING_PONG);

    /* Set Burst format in the transmitter/receiver format units */
    /* Reusing I2SSet API for Burst Mode as well */
    McASPTxFmtI2SSet(SOC_MCASP3_CFG_BASE, WORD_SIZE, SLOT_SIZE,
                     MCASP_TX_MODE_DMA);

    McASPTxFrameSyncCfg(SOC_MCASP3_CFG_BASE, 0, MCASP_TX_FS_WIDTH_BIT,
                        MCASP_TX_FS_EXT_BEGIN_ON_RIS_EDGE |
                        MCASP_TX_FS_INTERNAL);

    /* configure the clock for transmitter */
    McASPTxClkCfg(SOC_MCASP3_CFG_BASE, MCASP_TX_CLK_INTERNAL,
                  ((MCASP_ACLKX_CLKXDIV_VALUE &
                    MCASP_ACLKXCTL_CLKXDIV_MASK) >>
                   MCASP_ACLKXCTL_CLKXDIV_SHIFT),
                  ((MCASP_AHCLKX_HCLKXDIV_VALUE &
                    MCASP_AHCLKXCTL_HCLKXDIV_MASK) >>
                   MCASP_AHCLKXCTL_HCLKXDIV_SHIFT));

    McASPTxClkPolaritySet(SOC_MCASP3_CFG_BASE, MCASP_TX_CLK_POL_FALL_EDGE);

    McASPTxClkCheckConfig(SOC_MCASP3_CFG_BASE, MCASP_TX_CLKCHCK_DIV32,
                          0x00, 0xFF);

    /* Enable the transmitter/receiver slots. */
    McASPTxTimeSlotSet(SOC_MCASP3_CFG_BASE, BURST_SLOTS);

    /*
    ** Set the serializers
    */
    McASPSerializerTxSet(SOC_MCASP3_CFG_BASE, MCASP_XSER_TX_0);

    /*
    ** Configure the McASP pins
    ** Output - Frame Sync, Clock, Serializer Rx and Serializer Tx
    **          (Clocks generated internally)
    */
    McASPPinMcASPSet(SOC_MCASP3_CFG_BASE, (MCASP_PIN_AFSR |
                                           MCASP_PIN_ACLKR | MCASP_PIN_AFSX |
                                           MCASP_PIN_AHCLKX |
                                           MCASP_PIN_ACLKX |
                                           MCASP_PIN_AMUTE |
                                           MCASP_PIN_AXR(MCASP_XSER_TX_0)
                                           ));
    McASPPinDirOutputSet(SOC_MCASP3_CFG_BASE, MCASP_PIN_AFSR);
    McASPPinDirOutputSet(SOC_MCASP3_CFG_BASE, MCASP_PIN_ACLKR);

    McASPPinDirOutputSet(SOC_MCASP3_CFG_BASE, MCASP_PIN_AFSX);

    /* Configure high clock as Output */
    McASPPinDirOutputSet(SOC_MCASP3_CFG_BASE, MCASP_PIN_AHCLKX);

    McASPPinDirOutputSet(SOC_MCASP3_CFG_BASE, MCASP_PIN_ACLKX);

    /* Both Serializers used to output data out */
    McASPPinDirOutputSet(SOC_MCASP3_CFG_BASE, MCASP_PIN_AXR(MCASP_XSER_TX_0));
}

/*
** Sets up the interrupts for EDMA in AINTC
*/
static void EDMA3IntSetup(void)
{
#ifdef BUILD_A15

    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_MPUSS, 7,
                   EDMA_TPCC_IRQ_REGION0);

#elif defined (BUILD_M4)

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
static void DataTxActivate(void)
{
    /* Start the clocks */
    McASPTxClkStart(SOC_MCASP3_CFG_BASE, MCASP_TX_CLK_INTERNAL);

    /* Activate the  serializers */
    McASPTxSerActivate(SOC_MCASP3_CFG_BASE);

    while (!(McASPTxStatusGet(SOC_MCASP3_CFG_BASE) & MCASP_TX_STAT_DATAREADY)) ;

    /* Enable EDMA for the transfer */
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE, EDMA3_CHA_MCASP3_TX,
                        EDMA3_TRIG_MODE_MANUAL);

    /* Activate the state machines */
    McASPTxEnable(SOC_MCASP3_CFG_BASE);
}

void sampleConfigScr(unsigned int eventNum,
                     unsigned int chanNum)
{
    unsigned int       scrChanOffset = 0;
    unsigned int       scrRegOffset  = 0;
    unsigned int       xBarEvtNum    = 0;
    CSL_IntmuxRegsOvly scrEvtMux     =
        (CSL_IntmuxRegsOvly) (EDMA3_EVENT_MUX_REG_BASE_ADDR);

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
                    ~(CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_MASK);
                scrEvtMux->TPCC_EVTMUX[scrRegOffset] |=
                    (xBarEvtNum & CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_MASK);
                break;
            case 1:
                scrEvtMux->TPCC_EVTMUX[scrRegOffset] &=
                    ~(CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_MASK);
                scrEvtMux->TPCC_EVTMUX[scrRegOffset] |=
                    ((xBarEvtNum <<
                      CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_SHIFT) &
                     (CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_MASK));
                break;
            default:
                break;
        }
    }
}

void Configure_Edma_xbar()
{
    sampleConfigScr(MCASP3_RX_DMA_XBAR_INST, EDMA3_CHA_MCASP3_TX);
}

/*
** The main function. Application starts here.
*/
int main(void)
{
    uint32_t loopHere = 1;

    mcasp3_platform_init();

    mcasp3_edma_init();
#ifndef CONFIG_POLLED_MODE
    mcasp3_intsetup();
#endif
    /* Initialize the DMA parameters */
    BurstDMAParamInit();

    /* Configure the McASP for Burst Mode*/
    McASPBurstConfigure();

    /* Activate the transmission  */
    DataTxActivate();

/*
 *
 * Loop In Here for transfering data continuously
 *
 */

    while (loopHere)
    {
        /*
         * Pending Transfers from the Burst Frame are Triggered here.
         * Trigger a Manual EDMA Transfer
         */

#ifdef CONFIG_POLLED_MODE
        while (!(McASPTxStatusGet(SOC_MCASP3_CFG_BASE) &
                 MCASP_TX_STAT_DATAREADY)) ;
#endif
/*
 * We wait till FIFO is half empty, this is specific to support PING PONG
 * Mechanism
 */

        while (McASPTxFifoStatusGet(SOC_MCASP3_CFG_BASE) > 0x20) ;

        /* Enable EDMA for the transfer */
        EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE, EDMA3_CHA_MCASP3_TX,
                            EDMA3_TRIG_MODE_MANUAL);

        /*
         * Once the full Transfer is completed we can update the buffer.
         * New Buffer would be updated in the CallBack Function from EDMA
         * Transfer Completion ISR
         * Here we can program user required Delay to demonstrate Burst Transfer
         */

        sampleDelay(delayCounter);
        delayCounter = delayCounter + 1000;
        if (delayCounter > 10000)
            delayCounter = (1000U);
    }

    return 0;
}

/*
** This function will be called once transmit DMA is completed
*/
static void McASPTxDMAComplHandler(void)
{
    /* Buffers can be updated here, if required */

    BurstDMAParamInit();
}

/*
** EDMA transfer completion ISR
*/
static void EDMA3CCComplIsr(void *dummy)
{
    EDMA3CCPaRAMEntry dummyPaRAMSet;

    /* Check if transmit DMA completed */
    if (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE) & (1 << EDMA3_CHA_MCASP3_TX))
    {
        /* Clear the interrupt status for the first channel */
        EDMA3ClrIntr(SOC_EDMA_TPCC_BASE, EDMA3_CHA_MCASP3_TX);
    }

/*
 * Check if this is an Intermediate Transfer or Complete Transfer
 */
    EDMA3GetPaRAM(SOC_EDMA_TPCC_BASE, EDMA3_CHA_MCASP3_TX, &dummyPaRAMSet);

    if (dummyPaRAMSet.cCnt == 0)
    {
        McASPTxDMAComplHandler();
    }

    McASPTxIntEnable(SOC_MCASP3_CFG_BASE, MCASP_TXSTAT_XDATA_MASK);
}

static void mcasp3_platform_init()
{
    /*Unlock the Crossbar register */
    PlatformUnlockMMR();
    /* Pad mux configuration for McASP instance 3 */
    PlatformMCASP3SetPinMux();

    /* Power on McASP instance 3 */
    PlatformMCASP3PrcmEnable();

#ifdef TDA2EX_BUILD
    /* Pad mux configuration for I2C instance 2 */
    PlatformI2C5SetPinMux();
#else
    /* Pad mux configuration for I2C instance 2 */
    PlatformI2C2SetPinMux();
#endif

    SetupI2C(HSI2C_SLAVE_ADDR);
    /*Clear 6th bit i.e VIN6_SEL_S0 line*/
    SetupI2CTransmit();
}

static void mcasp3_edma_init()
{
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
                        EDMA3_CHA_MCASP3_TX,
                        EDMA3_CHA_MCASP3_TX,
                        EDMA3_CC_QUEUE);
}

/*
** Sets up the interrupts for EDMA in AINTC
*/
static void mcasp3_intsetup(void)
{
#ifdef BUILD_A15

    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_MPUSS, 60,
                   McASP3_IRQ_AXEVT);

#elif defined (BUILD_M4)

    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1, 29,
                   McASP3_IRQ_AXEVT);

#endif

    Intc_IntRegister(MCASP3_TX_IRQ_NUM, (IntrFuncPtr) mcasp3_AxevtIsr, NULL);

    Intc_IntPrioritySet(MCASP3_TX_IRQ_NUM, 1, 0);
    Intc_SystemEnable(MCASP3_TX_IRQ_NUM);
}

static void mcasp3_AxevtIsr(void *dummyPtr)
{
    if ((McASPTxStatusGet(SOC_MCASP3_CFG_BASE) & MCASP_TX_STAT_DATAREADY) ==
        MCASP_TX_STAT_DATAREADY)
    {
        McASPTxIntDisable(SOC_MCASP3_CFG_BASE, MCASP_TXSTAT_XDATA_MASK);
        McASPTxStatusSet(SOC_MCASP3_CFG_BASE, MCASP_TXSTAT_XDATA_MASK);
    }
}

/***************************** End Of File ***********************************/
