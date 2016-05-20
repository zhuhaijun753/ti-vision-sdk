/**
 *  \file     ep_write_loopback_app_main.c
 *
 *  \brief    This file contains PCIe write loopback test code for EP.
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

#define OUTBOUND_PCIE_ADDRESS ((uint32_t) 0xB0000000U)
#define INBOUND_PCIE_ADDRESS  ((uint32_t) 0xA0000000U)

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

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static volatile uint32_t transfer_complete = 0U;
static volatile uint32_t memSpaceEnable    = 0U;
static volatile uint32_t linkEnable        = 0U;

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
 * \brief   This API configures the PCIe traffic.
 *
 * \param   none.
 *
 * \retval  none.
 */
 #if 0
static void PcieAppConfigTraffic(void);
#endif
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
 * \brief   This API configues the BAR for BAR matching.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void PcieAppBarConfig(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int main()
{
    uint32_t linkSpeed, linkSpeedUsrInput;

    PCIEAppUartInit();
    UARTPuts("EP: PCIe write loopBack App\n\n", -1);
    UARTPuts("EP: Please Enter Link Speed\n1 - For Gen 1\n2 - For Gen 2\n", -1);
    linkSpeedUsrInput = UARTGetNum();
    if (linkSpeedUsrInput == 1)
    {
        linkSpeed = PCIE_LINK_SPEED_GEN1;
        UARTPuts("EP: Configured for Gen1 Mode\n", -1);
    }
    else if (linkSpeedUsrInput == 2)
    {
        linkSpeed = PCIE_LINK_SPEED_GEN2;
        UARTPuts("EP: Configured for Gen2 Mode\n", -1);
    }
    else
    {
        linkSpeed = PCIE_LINK_SPEED_GEN1;
        UARTPuts("EP: Invalid Input. Using Gen1 by default\n", -1);
    }

    UARTPuts("EP: PCIe write loopBack App\n\n", -1);

    /*Configure INTC*/
    PcieAppIntrInit();
    /*Configure PCIe Pll, PRCM, PHY */
    PCIEAppPrcmConfig();

    /*Set device type*/
    PCIESetDeviceType(SOC_PCIE_SS1_CONF_BASE, PCIE_DEVICE_TYPE_EP);

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

    /*Configure BAR*/
    PcieAppBarConfig();

    /*Init transmit and receive buffer*/
    PcieAppInitRxTxBuf();

    /*Enable link*/
    PCIELtssmEnable(SOC_PCIE_SS1_CONF_BASE, PCIE_CONFIG_ENABLE);
    UARTPuts("EP: Waiting for link to be UP\n", -1);

    /*Wait till link is up link*/
    while (linkEnable != 1U) ;
    UARTPuts("EP: Link is UP\n\n", -1);

    /*Wait till RC enables EP's mem space*/
    while (memSpaceEnable != 1) ;
    UARTPuts("EP: Mem space is enabled by RC\n", -1);

    UARTPuts("EP: Waiting for RC to transfer data\n", -1);
    /*Wait for data to receive from RC*/
    while (HW_RD_REG32(RX_DATA_BUFFER_ADDR + DATA_SIZE - 4) != 0xE0DU) ;

    /* Indicate to RC that the Data is received */
    HW_WR_REG32((RX_DATA_BUFFER_ADDR + DATA_SIZE - 4), 0x12344321);
    UARTPuts("EP: Data received from RC\n", -1);

    /*Init EDMA and enable transfer*/
    PcieAppEdmaInit();

    /* Deinit EDMA*/
    EDMA3Deinit(SOC_EDMA_TPCC_BASE, EDMA_EQ_NUM);

    UARTPuts("EP: Data looped back to RC\n", -1);

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static void PcieAppBarConfig(void)
{
    pcieLocationParams_t locationParam;
    pcieBarParams_t      barParams;

    locationParam.location          = PCIE_LOCATION_LOCAL;
    locationParam.outboundCfgOffset = OUTBOUND_CFG_OFFSET;

    barParams.barAddrSize    = PCIE_BAR_ADDR_SIZE_32BIT;
    barParams.barType        = PCIE_BAR_TYPE_MEMORY;
    barParams.enableBar      = PCIE_CONFIG_ENABLE;
    barParams.enablePrefetch = PCIE_CONFIG_ENABLE;
    barParams.lowerBarMask   = INBOUND_PCIE_LIMIT;
    barParams.lowerBaseAddr  = INBOUND_PCIE_ADDRESS;
    barParams.upperBarMask   = PCIE_UPPER_ADDRESS;
    barParams.upperBaseAddr  = PCIE_UPPER_ADDRESS;

    PCIEBarConfig(SOC_PCIE_SS1_CONF_BASE, &locationParam, 0U, &barParams);
}

static void PcieAppConfigOutBoundWindow(void)
{
    pcieLocationParams_t  locationParams;
    pcieAtuRegionParams_t regionParams;

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
        (uint32_t) 0U,
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
    regionParams.matchMode    = PCIE_ATU_REGION_MATCH_MODE_BAR;
    regionParams.barNumber    = 0;

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

#if 0
static void PcieAppConfigTraffic(void)
{
    pcieLocationParams_t    locationParams;
    pcieTrafficCtrlParams_t trafficCtrlParams;

    /*Enable local traffic*/
    locationParams.location = PCIE_LOCATION_LOCAL;

    trafficCtrlParams.enableMemSpace  = PCIE_CONFIG_ENABLE;
    trafficCtrlParams.enableBusMaster = PCIE_CONFIG_ENABLE;
    PCIETrafficCtrl(SOC_PCIE_SS1_CONF_BASE, &locationParams, &trafficCtrlParams);

    /*Enable remote traffic*/
    locationParams.location          = PCIE_LOCATION_REMOTE;
    locationParams.outboundCfgOffset = OUTBOUND_CFG_OFFSET;

    trafficCtrlParams.enableMemSpace  = PCIE_CONFIG_ENABLE;
    trafficCtrlParams.enableBusMaster = PCIE_CONFIG_ENABLE;
    PCIETrafficCtrl(SOC_PCIE_SS1_CONF_BASE, &locationParams, &trafficCtrlParams);
}

#endif
static void PcieAppInitRxTxBuf(void)
{
    memset((void *) RX_DATA_BUFFER_ADDR, 0, DATA_SIZE);
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
    edmaParam.srcAddr  = (uint32_t) RX_DATA_BUFFER_ADDR;
    edmaParam.destAddr =
        (PCIEGetOutboundAddr(SOC_PCIE_SS1_CONF_BASE) + OUTBOUND_MEM_SPACE);
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
         ((EDMA_TCC_NUM << EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK) |
         (EDMA3_SYNC_AB << 2U));

    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, EDMA_CH_NUM, &edmaParam);

    /*
     * Transfer is done in AB sync mode
     * Number of triggers required are C COUNT
     */
    for (triggerCount = 0U; triggerCount < (EDMA_C_COUNT); triggerCount++)
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

