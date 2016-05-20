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
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include "mcasp.h"
#include "edma.h"
#include "soc_defines.h"
#include "platform.h"
#include "interrupt.h"
#include "soc.h"

/******************************************************************************
**                      INTERNAL MACRO DEFINITIONS
******************************************************************************/
#define SOC_MCASP_2_FIFO_REGS (SOC_MCASP2_CFG_BASE + 0x1000)

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

#ifdef TDA2xx

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

#endif

/*
** Below Macros are calculated based on the above inputs
*/

#define I2S_SLOTS                         ((1 << NUM_I2S_CHANNELS) - 1)

#define BYTES_PER_SAMPLE                  ((WORD_SIZE >> 3) \
                                           * NUM_I2S_CHANNELS)

#define AUDIO_BUF_SIZE                    (NUM_SAMPLES_PER_AUDIO_BUF \
                                           * BYTES_PER_SAMPLE)

#define TX_DMA_INT_ENABLE                 (EDMA3CC_OPT_TCC_SET             \
                                               (EDMA3_CHA_MCASP2_TX) | (1  \
                                                                        << \
                                                                        EDMA_TPCC_OPT_TCINTEN_SHIFT))

#define PAR_TX_START                      (PAR_ID_START)

/*
** Definitions which are not configurable
*/
#define SIZE_PARAMSET                     (32U)
#define OPT_FIFO_WIDTH                    (0x02 << 8U)

#define WR_MEM_32(addr, \
                  data)             *(uint32_t *) (addr) = (uint32_t) (data)
#define RD_MEM_32(addr)                   *(uint32_t *) (addr)

#define WR_MEM_32_VOLATILE(addr, data)    *(volatile uint32_t *) (addr) = \
    (uint32_t) (data)

#define RD_MEM_32_VOLATILE(addr)          *(volatile uint32_t *) (addr)

/*
** Definitions which are configurable depending on the core to be used(ARM here)
*/
#define EDMA3_CHA_MCASP2_RX               (13)
#define EDMA3_CHA_MCASP2_TX               (12)
#define EDMA3_CHA_MCASP5_RX               (88)
#define EDMA3_CHA_MCASP5_TX               (87)

#define EDMA3_CC_XFER_COMPLETION_INT_A8   (12U)
#define EDMA3_ERROR_INT_A8                (14U)
#define EDMA3_CC_REGION_A8                (0U)

#define EDMA3_CC_XFER_COMPLN_INT_M3VPSS   (63U)
#define EDMA3_ERROR_INT_M3VPSS            (46U)
#define EDMA3_CC_REGION_M3VPSS            (5U)

#define EDMA3_CC_XFER_COMPLN_INT_M3VIDEO  (62U)
#define EDMA3_ERROR_INT_M3VIDEO           (46U)
#define EDMA3_CC_REGION_M3VIDEO           (4U)

#define EDMA3_CC_QUEUE                    (0U)

/*
** Definitions which are configurable depending on the application requirement
*/
#define MCASP_ACLKX_CLKXDIV_VALUE         (0x2U)
#define MCASP_AHCLKX_HCLKXDIV_VALUE       (0x5U)

/******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
******************************************************************************/
static void EDMA3IntSetup(void);
static void I2SDMAParamInit(void);
static void McASPI2SConfigure(void);
static void I2SDataTxActivate(void);
static void McASPTxDMAComplHandler(void);
static void EDMA3CCComplIsr(void *dummy);
static void Edma3ErrorIsr(void *dummy);
static void ParamTxLoopJobSet(uint16_t parId);

/******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
******************************************************************************/

/* Global counters to keep track of errors. Can be removed before releasing  */
uint32_t                       complInterruptCounter = 0x00;
uint32_t                       errInterruptCounter   = 0x00;

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

/******************************************************************************
**                      INTERNAL CONSTATNT DEFINITIONS
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
    (uint32_t) SOC_MCASP2_BASE,                /* dest address */
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
                /* '0xF0' data pattern that yields freq of 1.38MHz */
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
                /* '0xCC' data pattern that yields freq of 2.77MHz */
                txBuf0[4 * i + index] = 0xCCU;
                txBuf1[4 * i + index] = 0xCCU;
                txBuf2[4 * i + index] = 0xCCU;
            }
        }
    }

    /* Initialize the 1st paRAM set for transmit */
    memcpy(&paramSet, &txDefaultPar, SIZE_PARAMSET - 2);

    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, EDMA3_CHA_MCASP2_TX, &paramSet);

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
    McASPTxReset(SOC_MCASP2_CFG_BASE);

    /* Enable the FIFOs for DMA transfer */
    McASPWriteFifoEnable(SOC_MCASP2_CFG_BASE, 2, 1);

    /* Set I2S format in the transmitter/receiver format units */
    McASPTxFmtI2SSet(SOC_MCASP2_CFG_BASE, WORD_SIZE, SLOT_SIZE,
                     MCASP_TX_MODE_DMA);

    McASPTxFrameSyncCfg(SOC_MCASP2_CFG_BASE, 2, MCASP_TX_FS_WIDTH_WORD,
                        MCASP_TX_FS_EXT_BEGIN_ON_FALL_EDGE |
                        MCASP_TX_FS_INTERNAL);

    /* configure the clock for transmitter */
    McASPTxClkCfg(SOC_MCASP2_CFG_BASE, MCASP_TX_CLK_INTERNAL,
                  ((MCASP_ACLKX_CLKXDIV_VALUE &
                    MCASP_ACLKXCTL_CLKXDIV_MASK) >>
                   MCASP_ACLKXCTL_CLKXDIV_SHIFT),
                  ((MCASP_AHCLKX_HCLKXDIV_VALUE &
                    MCASP_AHCLKXCTL_HCLKXDIV_MASK) >>
                   MCASP_AHCLKXCTL_HCLKXDIV_SHIFT));

    McASPTxClkPolaritySet(SOC_MCASP2_CFG_BASE, MCASP_TX_CLK_POL_FALL_EDGE);

    McASPTxClkCheckConfig(SOC_MCASP2_CFG_BASE, MCASP_TX_CLKCHCK_DIV32,
                          0x00, 0xFF);

    /* Enable the transmitter/receiver slots. I2S uses 2 slots */
    McASPTxTimeSlotSet(SOC_MCASP2_CFG_BASE, I2S_SLOTS);

    /*
    ** Set the serializers
    */
    McASPSerializerTxSet(SOC_MCASP2_CFG_BASE, MCASP_XSER_TX_0);
    McASPSerializerTxSet(SOC_MCASP2_CFG_BASE, MCASP_XSER_TX_1);

#ifdef TDA2xx
    McASPSerializerTxSet(SOC_MCASP2_CFG_BASE, MCASP_XSER_TX_2);
    McASPSerializerTxSet(SOC_MCASP2_CFG_BASE, MCASP_XSER_TX_3);
    McASPSerializerTxSet(SOC_MCASP2_CFG_BASE, MCASP_XSER_TX_4);
    McASPSerializerTxSet(SOC_MCASP2_CFG_BASE, MCASP_XSER_TX_5);
    McASPSerializerTxSet(SOC_MCASP2_CFG_BASE, MCASP_XSER_TX_6);
    McASPSerializerTxSet(SOC_MCASP2_CFG_BASE, MCASP_XSER_TX_7);
    McASPSerializerTxSet(SOC_MCASP2_CFG_BASE, MCASP_XSER_TX_8);
    McASPSerializerTxSet(SOC_MCASP2_CFG_BASE, MCASP_XSER_TX_9);
#endif

    /*
    ** Configure the McASP pins
    ** Output - Frame Sync, Clock, Serializer Rx and Serializer Tx
    **          (Clocks generated internally)
    */
#ifdef TDA2xx
    McASPPinMcASPSet(SOC_MCASP2_CFG_BASE, (MCASP_PIN_AFSR |
                                           MCASP_PIN_ACLKR | MCASP_PIN_AFSX |
                                           MCASP_PIN_AHCLKX |
                                           MCASP_PIN_ACLKX |
                                           MCASP_PIN_AMUTE |
                                           MCASP_PIN_AXR(MCASP_XSER_TX_0) |
                                           MCASP_PIN_AXR(MCASP_XSER_TX_1) |
                                           MCASP_PIN_AXR(MCASP_XSER_TX_2) |
                                           MCASP_PIN_AXR(MCASP_XSER_TX_3) |
                                           MCASP_PIN_AXR(MCASP_XSER_TX_4) |
                                           MCASP_PIN_AXR(MCASP_XSER_TX_5) |
                                           MCASP_PIN_AXR(MCASP_XSER_TX_6) |
                                           MCASP_PIN_AXR(MCASP_XSER_TX_7) |
                                           MCASP_PIN_AXR(MCASP_XSER_TX_8) |
                                           MCASP_PIN_AXR(MCASP_XSER_TX_9)));
#else
    McASPPinMcASPSet(SOC_MCASP2_CFG_BASE, (MCASP_PIN_AFSR |
                                           MCASP_PIN_ACLKR | MCASP_PIN_AFSX |
                                           MCASP_PIN_AHCLKX |
                                           MCASP_PIN_ACLKX |
                                           MCASP_PIN_AMUTE |
                                           MCASP_PIN_AXR(MCASP_XSER_TX_0) |
                                           MCASP_PIN_AXR(MCASP_XSER_TX_1)));
#endif
    McASPPinDirOutputSet(SOC_MCASP2_CFG_BASE, MCASP_PIN_AFSR);
    McASPPinDirOutputSet(SOC_MCASP2_CFG_BASE, MCASP_PIN_ACLKR);

    McASPPinDirOutputSet(SOC_MCASP2_CFG_BASE, MCASP_PIN_AFSX);
    McASPPinDirOutputSet(SOC_MCASP2_CFG_BASE, MCASP_PIN_ACLKX);

    /* Both Serializers used to output data out */
    McASPPinDirOutputSet(SOC_MCASP2_CFG_BASE, MCASP_PIN_AXR(MCASP_XSER_TX_0));
    McASPPinDirOutputSet(SOC_MCASP2_CFG_BASE, MCASP_PIN_AXR(MCASP_XSER_TX_1));

#ifdef TDA2xx
    McASPPinDirOutputSet(SOC_MCASP2_CFG_BASE, MCASP_PIN_AXR(MCASP_XSER_TX_2));
    McASPPinDirOutputSet(SOC_MCASP2_CFG_BASE, MCASP_PIN_AXR(MCASP_XSER_TX_3));
    McASPPinDirOutputSet(SOC_MCASP2_CFG_BASE, MCASP_PIN_AXR(MCASP_XSER_TX_4));
    McASPPinDirOutputSet(SOC_MCASP2_CFG_BASE, MCASP_PIN_AXR(MCASP_XSER_TX_5));
    McASPPinDirOutputSet(SOC_MCASP2_CFG_BASE, MCASP_PIN_AXR(MCASP_XSER_TX_6));
    McASPPinDirOutputSet(SOC_MCASP2_CFG_BASE, MCASP_PIN_AXR(MCASP_XSER_TX_7));
    McASPPinDirOutputSet(SOC_MCASP2_CFG_BASE, MCASP_PIN_AXR(MCASP_XSER_TX_8));
    McASPPinDirOutputSet(SOC_MCASP2_CFG_BASE, MCASP_PIN_AXR(MCASP_XSER_TX_9));
#endif
}

/*
** Sets up the interrupts for EDMA in AINTC
*/
static void EDMA3IntSetup(void)
{
#ifdef _TMS320C6X
    /* Initialize DSP interrupt controller and enable interrupts */
    IntDSPINTCInit();
    IntGlobalEnable();

    /* Map EDMA events to DSP interrupts        */
    IntRegister(4, EDMA3CCComplIsr);
    IntEventMap(4, SYS_INT_EDMACOMPINT);
    IntEnable(4);

    IntRegister(5, Edma3ErrorIsr);
    IntEventMap(5, SYS_INT_EDMAERRINT);
    IntEnable(5);
#else
    Intc_Init();
    Intc_IntEnable(0);

#if defined (BUILD_A8)
    /* Cortex A8 interrupt configuration        */
    Intc_IntRegister(EDMA3_CC_XFER_COMPLETION_INT_A8,
                     (IntrFuncPtr) EDMA3CCComplIsr,
                     NULL);
    Intc_SystemEnable(EDMA3_CC_XFER_COMPLETION_INT_A8);

    Intc_IntRegister(EDMA3_ERROR_INT_A8, (IntrFuncPtr) Edma3ErrorIsr, NULL);
    Intc_SystemEnable(EDMA3_ERROR_INT_A8);

#elif defined (BUILD_M3VPSS)
    /* M3vpss interrupt configuration           */
    Intc_IntRegister(EDMA3_CC_XFER_COMPLN_INT_M3VPSS,
                     (IntrFuncPtr) EDMA3CCComplIsr,
                     NULL);
    Intc_SystemEnable(EDMA3_CC_XFER_COMPLN_INT_M3VPSS);

    Intc_IntRegister(EDMA3_ERROR_INT_M3VPSS, (IntrFuncPtr) Edma3ErrorIsr, NULL);
    Intc_SystemEnable(EDMA3_ERROR_INT_M3VPSS);

#elif defined (BUILD_M3VIDEO)
    /* M3video interrupt configuration          */
    Intc_IntRegister(EDMA3_CC_XFER_COMPLN_INT_M3VIDEO,
                     (IntrFuncPtr) EDMA3CCComplIsr,
                     NULL);
    Intc_SystemEnable(EDMA3_CC_XFER_COMPLN_INT_M3VIDEO);

    Intc_IntRegister(EDMA3_ERROR_INT_M3VIDEO, (IntrFuncPtr) Edma3ErrorIsr, NULL);
    Intc_SystemEnable(EDMA3_ERROR_INT_M3VIDEO);
#endif
#endif
}

/*
** Activates the data transmission/reception
** The DMA parameters shall be ready before calling this function.
*/
static void I2SDataTxActivate(void)
{
    /* Start the clocks */
    McASPTxClkStart(SOC_MCASP2_CFG_BASE, MCASP_TX_CLK_INTERNAL);

    /* Enable EDMA for the transfer */
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE, EDMA3_CHA_MCASP2_TX,
                        EDMA3_TRIG_MODE_EVENT);

    /* Activate the  serializers */
    McASPTxSerActivate(SOC_MCASP2_CFG_BASE);

    /* make sure that the XDATA bit is cleared to zero */
    while (McASPTxStatusGet(SOC_MCASP2_CFG_BASE) & MCASP_TX_STAT_DATAREADY) ;

    /* Activate the state machines */
    McASPTxEnable(SOC_MCASP2_CFG_BASE);
}

/*
** The main function. Application starts here.
*/
int main(void)
{
    uint32_t loopHere = 1;

    /* Pad mux configuration for McASP instance 2 */
    PlatformMCASP2SetPinMux();

    /* Power on McASP instance 2*/
    PlatformMCASP2PrcmEnable();

#if defined (BUILD_A8)
    EDMAsetRegion(EDMA3_CC_REGION_A8);
#elif defined (M3VPSS)
    EDMAsetRegion(EDMA3_CC_REGION_M3VPSS);
#elif defined (BUILD_M3VIDEO)
    EDMAsetRegion(EDMA3_CC_REGION_M3VIDEO);
#endif

    EDMA3Init(SOC_EDMA_TPCC_BASE, EDMA3_CC_QUEUE);

    EDMA3IntSetup();

    /* Request EDMA channels */
    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE,
                        EDMA3_CHANNEL_TYPE_DMA,
                        EDMA3_CHA_MCASP2_TX,
                        EDMA3_CHA_MCASP2_TX,
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
    if (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE) & (1 << EDMA3_CHA_MCASP2_TX))
    {
        /* Clear the interrupt status for the first channel */
        EDMA3ClrIntr(SOC_EDMA_TPCC_BASE, EDMA3_CHA_MCASP2_TX);
        McASPTxDMAComplHandler();
    }
    ++complInterruptCounter;
}

/*
** EDMA transfer completion ISR
*/
static void Edma3ErrorIsr(void *dummy)
{
    /* Perform any error handling here.*/
    ++errInterruptCounter;
}

/***************************** End Of File ***********************************/
