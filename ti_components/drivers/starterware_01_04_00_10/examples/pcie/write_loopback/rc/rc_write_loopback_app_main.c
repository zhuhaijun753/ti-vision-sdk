/**
 *  \file     rc_write_loopback_app_main.c
 *
 *  \brief    This file contains PCIe write loopback test code for RC.
 *
 *  \details   RC transmits 1MB of data to EP, waits till EP sends back data
 *             and checks for data integrity.
 *
 *  \copyright Copyright (C) 2013 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "stdint.h"
#include <string.h>
#include <common/stw_types.h>
#include "hw_types.h"
#include "hw_counter_32k.h"
#include "interrupt.h"
#include "irq_xbar_interrupt_ids.h"
#include "irq_xbar.h"
#include "soc.h"
#include "edma.h"
#include "uartStdio.h"
#include "soc_defines.h"
#include "platform.h"

/* Application header files */
#include "pcie_app.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

#define OUTBOUND_PCIE_ADDRESS ((uint32_t) 0xA0000000U)
#define INBOUND_PCIE_ADDRESS  ((uint32_t) 0xB0000000U)

#define DATA_SIZE                         ((uint32_t) 0x1000000U)
#define DATA_SIZE_IN_WORD                 ((uint32_t) DATA_SIZE / 4U)

#define EDMA_TCC_NUM                      ((uint32_t) 0U)
#define EDMA_CH_NUM                       ((uint32_t) 0U)
#define EDMA_EQ_NUM                       ((uint32_t) 0U)
#define EDMA_CC_REGION_A15                ((uint32_t) 0U)
#define EDMA_A_COUNT                      ((uint32_t) 0x4000U)
#define EDMA_B_COUNT                      ((uint32_t) DATA_SIZE / EDMA_A_COUNT)
#define EDMA_C_COUNT                      ((uint32_t) 1U)

#define PCIE_MAIN_INT_A15                 ((uint32_t) 13U)
#define EDMA_XFER_COMPLETION_INT_A15      ((uint32_t) 12U)

#define RX_DATA_BUFFER_ADDR               ((uint32_t) 0x90000000U)

#define COUNTER_MAX_VALUE                 ((uint32_t) 0xFFFFFFFFU)
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static volatile uint32_t dataTxBuffer[DATA_SIZE_IN_WORD];

static volatile uint32_t transfer_complete = 0U;
static volatile uint32_t memSpaceEnable    = 0U;
static volatile uint32_t linkEnable        = 0U;
static volatile uint32_t timerStartVal, timerEndVal, timerDiffVal;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This API configures the PCIe outbound window.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void PcieAppConfigOutBoundWindow(void);

/**
 * \brief   This API configures the PCIe inbound window.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void PcieAppConfigInBoundWindow(void);

/**
 * \brief   This API configures the PCIe local traffic.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void PcieAppConfigTrafficLocal(void);

/**
 * \brief   This API configures the PCIe remote traffic.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void PcieAppConfigTrafficRemote(void);

/**
 * \brief   This API initializes the RX and Tx data buffer.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void PcieAppInitRxTxBuf(void);

/**
 * \brief   This API initializes the EDMA for data transfer.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void PcieAppEdmaInit(void);

/**
 * \brief   This API configures the INTC for PCIe and EDMA interrupts.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void PcieAppIntrInit(void);

/**
 * \brief   ISR which gets called on EDMA completion interrupt.
 *
 * \param   handle      Interrupt handle.
 *
 * \retval  none.
 */
static void PcieAppEdmaCompletionIsr(void *handle);

/**
 * \brief   ISR that gets called when main interrupt is raised.
 *
 * \param   handle      Interrupt handle.
 *
 * \retval  none.
 */
static void PcieAppMainIsr(void *handle);

/**
 * \brief   This API checks the data sent by EP for integrity.
 *
 * \param   none.
 *
 * \retval  PASS      Test case ran successfully and receive data matches
 *                    transmitted data.
 * \retval  FAIL      Test case ran successfully and receive data does not
 *                    match transmitted data.
 */
static uint32_t PcieAppCheckDataIntegrity(void);

/**
 * \brief   This API Reads current 32KHz counter value.
 *
 * \param   none.
 *
 * \retval  none.
 */
static uint32_t PcieRead32kCounter(void);

/**
 * \brief   This API Calculates the count difference between old and new timer.
 *          count value. Takes care when the counter value is wrapped back to 0.
 *
 * \param   none.
 *
 * \retval  none.
 */
static uint32_t PcieCounterDiff(uint32_t oldVal, uint32_t newVal);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int main()
{
    uint32_t timeInUSec, txSpeed;
    uint32_t linkSpeed, linkSpeedUsrInput;

    PCIEAppUartInit();
    UARTPuts("RC: PCIe write loopBack App\n\n", -1);
    UARTPuts("RC: Please enter link speed\n 1 - for Gen 1\n 2 - For Gen 2\n",
             -1);
    linkSpeedUsrInput = UARTGetNum();
    if (linkSpeedUsrInput == 1)
    {
        linkSpeed = PCIE_LINK_SPEED_GEN1;
        UARTPuts("RC: Configured for Gen1 Mode\n", -1);
    }
    else if (linkSpeedUsrInput == 2)
    {
        linkSpeed = PCIE_LINK_SPEED_GEN2;
        UARTPuts("RC: Configured for Gen2 Mode\n", -1);
    }
    else
    {
        linkSpeed = PCIE_LINK_SPEED_GEN1;
        UARTPuts("RC: Invalid Input. Using Gen1 by default\n", -1);
    }

    /*Configure INTC*/
    PcieAppIntrInit();
    /*Configure PCIe Pll, PRCM, PHY */
    PCIEAppPrcmConfig();

    /*Set device type*/
    PCIESetDeviceType(SOC_PCIE_SS1_CONF_BASE, PCIE_DEVICE_TYPE_RC);

    PCIEMainIntrEnable(
        SOC_PCIE_SS1_CONF_BASE,
        PCIE_MAIN_INTR_FLAG_CFG_MSG_SPACE_EN_EVT |
        PCIE_MAIN_INTR_FLAG_LINK_UP_EVT);

    /*Set max link width and speed*/
    PCIEConfigLink(
        SOC_PCIE_SS1_CONF_BASE,
        linkSpeed,
        PCIE_NUMBER_OF_LANES);

    /*Configure outbound cfg and mem space*/
    PcieAppConfigOutBoundWindow();
    /*Configure inbound mem space*/
    PcieAppConfigInBoundWindow();
    /*Init transmit and receive buffer*/
    PcieAppInitRxTxBuf();

    PcieAppConfigTrafficLocal();

    /*Enable link*/
    PCIELtssmEnable(SOC_PCIE_SS1_CONF_BASE, PCIE_CONFIG_ENABLE);
    UARTPuts("RC: Waiting for link to be UP\n", -1);

    /*Wait till link is up link*/
    while (linkEnable != 1U) ;
    UARTPuts("RC: Link is UP\n\n", -1);

    /*Configure PCIe traffic*/
    PcieAppConfigTrafficRemote();
    /*Wait till mem space is enabled*/
    while (memSpaceEnable != 1U) ;
    UARTPuts("RC: Mem space is enabled\n", -1);
    UARTPuts("RC: Sending data to EP\n", -1);

    /*Init EDMA and enable transfer*/
    PcieAppEdmaInit();

    /* Wait till EP receives the data. */
    while (HW_RD_REG32(PCIEGetOutboundAddr(SOC_PCIE_SS1_CONF_BASE) +
                       OUTBOUND_MEM_SPACE + DATA_SIZE - 4U) != 0x12344321U) ;

    timerEndVal  = PcieRead32kCounter();
    timerDiffVal = PcieCounterDiff(timerStartVal, timerEndVal);

    /* Time in Micro Sec = (Counter Difference * 1000 * 1000) / 32K) */
    timeInUSec = (timerDiffVal * 1000) / 32;
    /* Transfer Speed = Data transferred / Time taken for transfer */
    txSpeed = DATA_SIZE / timeInUSec;

    UARTPuts("RC: Data sent to EP\n", -1);
    UARTPuts("RC: Data size is : ", -1);
    UARTPutHexNum(DATA_SIZE);
    UARTPuts("\nRC: Time taken to transmit data is : ", -1);
    UARTPutNum(timeInUSec);
    UARTPuts(" micro Sec\n", -1);
    UARTPuts("RC: Transfer Speed is : ", -1);
    UARTPutNum(txSpeed);
    UARTPuts(" MBps\n", -1);

    /* Deinit EDMA*/
    EDMA3Deinit(SOC_EDMA_TPCC_BASE, EDMA_EQ_NUM);
    UARTPuts("RC: Waiting for EP to transmit data\n", -1);
    /*Wait till EP writes back data to RC*/
    while (HW_RD_REG32(RX_DATA_BUFFER_ADDR + DATA_SIZE - 4U) !=
           0x12344321U) ;
    UARTPuts("RC: Data received from EP\n", -1);

    if (SUCCESS == PcieAppCheckDataIntegrity())
    {
        UARTPuts("RC: Sent data matches received data\n", -1);
        UARTPuts("RC: PCIe write loopBack test passed\n", -1);
    }
    else
    {
        UARTPuts("RC: Sent data doesn't match received data\n", -1);
        UARTPuts("RC: PCIe write loopBack test failed\n", -1);
    }

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */
static uint32_t PcieRead32kCounter(void)
{
    uint32_t val;
    val = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
    return val;
}

static uint32_t PcieCounterDiff(uint32_t oldVal, uint32_t newVal)
{
    uint32_t diff;
    if (oldVal > newVal)
    {
        /* Counter has Wrapped back to 0 */
        diff  = COUNTER_MAX_VALUE - oldVal;
        diff += newVal;
    }
    else
    {
        diff = newVal - oldVal;
    }
    return diff;
}

static uint32_t PcieAppCheckDataIntegrity(void)
{
    uint32_t wordCount;
    uint32_t status = SUCCESS;

    for (wordCount = 0U; wordCount < DATA_SIZE_IN_WORD - 1U;
         wordCount++)
    {
        if (dataTxBuffer[wordCount] !=
            HW_RD_REG32(RX_DATA_BUFFER_ADDR + (wordCount * 4U)))
        {
            UARTPuts(
                "\nRC: Received data did not match transmitted data",
                -1);
            status = FAIL;
            break;
        }
        wordCount++;
    }

    return status;
}

static void PcieAppConfigOutBoundWindow(void)
{
    pcieLocationParams_t  locationParams;
    pcieAtuRegionParams_t regionParams;

    /*Configure OB region for remote configuration access space*/
    locationParams.location = PCIE_LOCATION_LOCAL;

    regionParams.regionDir    = PCIE_ATU_REGION_DIR_OUTBOUND;
    regionParams.tlpType      = PCIE_TLP_TYPE_CFG;
    regionParams.enableRegion = PCIE_CONFIG_ENABLE;

    regionParams.lowerBaseAddr    = OUTBOUND_CFG_OFFSET;
    regionParams.upperBaseAddr    = PCIE_UPPER_ADDRESS;
    regionParams.regionWindowSize = OUTBOUND_CFG_OFFSET_LIMIT;

    regionParams.lowerTargetAddr = 0U;
    regionParams.upperTargetAddr = 0U;

    PCIEAtuRegionConfig(
        SOC_PCIE_SS1_CONF_BASE,
        &locationParams,
        (uint32_t) 0U,
        &regionParams);

    /*Configure OB region for memory transfer*/
    locationParams.location = PCIE_LOCATION_LOCAL;

    regionParams.regionDir    = PCIE_ATU_REGION_DIR_OUTBOUND;
    regionParams.tlpType      = PCIE_TLP_TYPE_MEM;
    regionParams.enableRegion = PCIE_CONFIG_ENABLE;

    regionParams.lowerBaseAddr    = OUTBOUND_MEM_SPACE;
    regionParams.upperBaseAddr    = PCIE_UPPER_ADDRESS;
    regionParams.regionWindowSize = OUTBOUND_MEM_SPACE_LIMIT;

    regionParams.lowerTargetAddr = OUTBOUND_PCIE_ADDRESS;
    regionParams.upperTargetAddr = PCIE_UPPER_ADDRESS;

    PCIEAtuRegionConfig(
        SOC_PCIE_SS1_CONF_BASE,
        &locationParams,
        (uint32_t) 1U,
        &regionParams);
}

static void PcieAppConfigInBoundWindow(void)
{
    pcieLocationParams_t  locationParams;
    pcieAtuRegionParams_t regionParams;

    /*Configure IB region for memory transfer*/
    locationParams.location = PCIE_LOCATION_LOCAL;

    regionParams.regionDir    = PCIE_ATU_REGION_DIR_INBOUND;
    regionParams.tlpType      = PCIE_TLP_TYPE_MEM;
    regionParams.enableRegion = PCIE_CONFIG_ENABLE;
    regionParams.matchMode    = PCIE_ATU_REGION_MATCH_MODE_ADDR;

    regionParams.lowerBaseAddr    = INBOUND_PCIE_ADDRESS;
    regionParams.upperBaseAddr    = PCIE_UPPER_ADDRESS;
    regionParams.regionWindowSize = INBOUND_PCIE_LIMIT;

    regionParams.lowerTargetAddr = RX_DATA_BUFFER_ADDR;
    regionParams.upperTargetAddr = PCIE_UPPER_ADDRESS;

    PCIEAtuRegionConfig(
        SOC_PCIE_SS1_CONF_BASE,
        &locationParams,
        (uint32_t) 0U,
        &regionParams);
}

static void PcieAppConfigTrafficLocal(void)
{
    pcieLocationParams_t    locationParams;
    pcieTrafficCtrlParams_t trafficCtrlParams;

    /*Enable local traffic*/
    locationParams.location = PCIE_LOCATION_LOCAL;

    trafficCtrlParams.enableMemSpace   = PCIE_CONFIG_ENABLE;
    trafficCtrlParams.enableBusMaster  = PCIE_CONFIG_ENABLE;
    trafficCtrlParams.enableIntxAssert = PCIE_CONFIG_ENABLE;
    trafficCtrlParams.enableIoSpace    = PCIE_CONFIG_DISABLE;
    trafficCtrlParams.enableSerr       = PCIE_CONFIG_DISABLE;
    PCIETrafficCtrl(SOC_PCIE_SS1_CONF_BASE, &locationParams,
                    &trafficCtrlParams);
}

static void PcieAppConfigTrafficRemote(void)
{
    pcieLocationParams_t    locationParams;
    pcieTrafficCtrlParams_t trafficCtrlParams;

    /*Enable remote traffic*/
    locationParams.location          = PCIE_LOCATION_REMOTE;
    locationParams.outboundCfgOffset = OUTBOUND_CFG_OFFSET;

    trafficCtrlParams.enableMemSpace  = PCIE_CONFIG_ENABLE;
    trafficCtrlParams.enableBusMaster = PCIE_CONFIG_ENABLE;
    trafficCtrlParams.enableIntxAssert = PCIE_CONFIG_DISABLE;
    trafficCtrlParams.enableIoSpace    = PCIE_CONFIG_DISABLE;
    PCIETrafficCtrl(SOC_PCIE_SS1_CONF_BASE, &locationParams,
                    &trafficCtrlParams);
}

static void PcieAppInitRxTxBuf(void)
{
    uint32_t wordCount;

    for (wordCount = 0U; wordCount < DATA_SIZE_IN_WORD; wordCount++)
    {
        dataTxBuffer[wordCount] = wordCount;
    }
    dataTxBuffer[--wordCount] = 0xE0DU;

    memset((void *) RX_DATA_BUFFER_ADDR, 0U, DATA_SIZE);
}

static void PcieAppEdmaInit(void)
{
    EDMA3CCPaRAMEntry edmaParam;
    uint32_t          triggerCount;

    /*Configure the EDMA clock */
    PlatformEDMAWkupDepEnable();

    EDMAsetRegion(EDMA_CC_REGION_A15);

    /* Do EDMA init Done once in the beginning of application */
    EDMA3Init(SOC_EDMA_TPCC_BASE, 0U);

    EDMA3RequestChannel(
        SOC_EDMA_TPCC_BASE,
        EDMA3_CHANNEL_TYPE_DMA,
        EDMA_CH_NUM,
        EDMA_TCC_NUM,
        EDMA_EQ_NUM);

    edmaParam.opt      = 0U;
    edmaParam.srcAddr  = (uint32_t) dataTxBuffer;
    edmaParam.destAddr =
        (PCIEGetOutboundAddr(SOC_PCIE_SS1_CONF_BASE) +
         OUTBOUND_MEM_SPACE);
    edmaParam.aCnt     = EDMA_A_COUNT;
    edmaParam.bCnt     = EDMA_B_COUNT;
    edmaParam.cCnt     = EDMA_C_COUNT;
    edmaParam.srcBIdx  = EDMA_A_COUNT;
    edmaParam.destBIdx = EDMA_A_COUNT;
    edmaParam.srcCIdx  = EDMA_C_COUNT;
    edmaParam.destCIdx = EDMA_C_COUNT;
    edmaParam.linkAddr = 0xFFFFU;
    edmaParam.opt     |=
        (EDMA3_OPT_TCINTEN_MASK | EDMA3_OPT_ITCINTEN_MASK |
         ((EDMA_TCC_NUM <<
           EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK) |
         (EDMA3_SYNC_AB << 2U));

    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, EDMA_CH_NUM, &edmaParam);
    timerStartVal = PcieRead32kCounter();
    /*
     * Transfer is done in AB sync mode
     * Number of triggers required are C COUNT
     */
    for (triggerCount = 0U; triggerCount < (EDMA_C_COUNT);
         triggerCount++)
    {
        transfer_complete = 0U;
        EDMA3EnableTransfer(
            SOC_EDMA_TPCC_BASE,
            EDMA_CH_NUM,
            EDMA3_TRIG_MODE_MANUAL);
        while (transfer_complete != 1U) ;
    }
}

static void PcieAppEdmaCompletionIsr(void *handle)
{
    transfer_complete = 1;
    EDMA3ClrIntr(SOC_EDMA_TPCC_BASE, EDMA_TCC_NUM);
}

static void PcieAppMainIsr(void *handle)
{
    uint32_t status;

    status = PCIEMainIntrStatus(SOC_PCIE_SS1_CONF_BASE);
    if (status & PCIE_MAIN_INTR_FLAG_CFG_MSG_SPACE_EN_EVT)
    {
        memSpaceEnable = 1;
    }

    if (status & PCIE_MAIN_INTR_FLAG_LINK_UP_EVT)
    {
        linkEnable = 1;
    }

    PCIEMainIntrClear(SOC_PCIE_SS1_CONF_BASE, status);
}

static void PcieAppIntrInit(void)
{
    /*Unlock the Crossbar register */
    PlatformUnlockMMR();

    IRQXBARConnect(
        SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
        CPU_MPUSS,
        7,
        EDMA_TPCC_IRQ_REGION0);
    IRQXBARConnect(
        SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
        CPU_MPUSS,
        8,
        PCIe_SS1_IRQ_INT0);

    /* Enable The EDMA interrupt */
    Intc_Init();
    Intc_IntEnable(0);

    Intc_IntRegister(
        EDMA_XFER_COMPLETION_INT_A15,
        (IntrFuncPtr) PcieAppEdmaCompletionIsr,
        NULL);
    Intc_IntPrioritySet(EDMA_XFER_COMPLETION_INT_A15, 1, 0);

    Intc_IntRegister(
        PCIE_MAIN_INT_A15,
        (IntrFuncPtr) PcieAppMainIsr,
        NULL);
    Intc_IntPrioritySet(PCIE_MAIN_INT_A15, 1, 0);

    Intc_SystemEnable(EDMA_XFER_COMPLETION_INT_A15);
    Intc_SystemEnable(PCIE_MAIN_INT_A15);
}

