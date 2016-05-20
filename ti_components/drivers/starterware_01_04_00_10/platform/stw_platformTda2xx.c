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

/**
 *  \file stw_platformTda2xx.c
 *
 *  \brief Implements the Tda2xx platform specific functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "stdint.h"
#include <stddef.h>
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include <common/stw_config.h>
#include <common/stw_utils.h>
#include "platforms/stw_platform.h"
#include <stw_platformTda2xx.h>
#include <hw/hw_ctrl_wkup.h>
#include <hw/hw_ctrl_core_pad_io.h>
#include <hw/hw_ctrl_core_irq_dma.h>
#include "pmhal_prcm.h"
#include "pm/pmhal/pmhal_mm.h"
#include "pm/pm_types.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/** \brief Enables the MMR region lock  */
/**<  Note : Only if required Enable the macro to lock the MMR region
 *    In the code if unlock MMR and lock MMR is not taken care properly ,
 *    by enabling this macro will result in hang while configuring pinmux ,
 *    PRCM etc.,
 */
/* #define PLATFORM_MMR_REG_LOCK_ENABLE*/

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t PLATFORMTda2xxInit(const platformInitParams_t *initParams)
{
    int32_t      status = STW_SOK;
#ifdef TDA2EX_BUILD
    int32_t      retVal = PM_SUCCESS;
#endif
    platformId_t platfrmId;

    platfrmId = PLATFORMGetId();

    if ((TRUE == initParams->isPinMuxSettingReq)
        && ((PLATFORM_ID_EVM == platfrmId)
            || (PLATFORM_ID_ZEBU == platfrmId)))
    {
        status = PLATFORMTda2xxSetPinMux(initParams);
    }

    /* Cross bar setup */
    if (TRUE == initParams->isIrqXBarSettingReq)
    {
        status = PLATFORMTda2xxSetIrqXBar(initParams);
    }
#ifdef TDA2EX_BUILD
    /* Enable I2C5 module */
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_I2C5,
                                PMHAL_PRCM_MODULE_MODE_ENABLED,
                                PM_TIMEOUT_INFINITE);
    if (retVal != PM_SUCCESS)
    {
        status = STW_EFAIL;
    }
#endif
    return status;
}

int32_t PLATFORMTda2xxDeInit(void)
{
    int32_t status = STW_SOK;

    return (status);
}

platformCpuRev_t PLATFORMTda2xxGetCpuRev(void)
{
    uint32_t         prodId, cpuRev;
    platformCpuRev_t cpuRevEnum = PLATFORM_CPU_REV_1_0;

    prodId = HW_RD_REG32(SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE +
                         CTRL_WKUP_ID_CODE);
    cpuRev = (prodId & 0xF0000000U) >> 28U;
    switch (cpuRev)
    {
        case 0x0U:
            cpuRevEnum = PLATFORM_CPU_REV_1_0;
            break;

        case 0x1U:
            cpuRevEnum = PLATFORM_CPU_REV_1_1;
            break;

        default:
            /* Default to last known version */
            console_print_string(
                "\nPLATFORM: UNKNOWN CPU detected, defaulting to CPU REV 1.1");
            cpuRevEnum = PLATFORM_CPU_REV_1_1;
            break;
    }

    return (cpuRevEnum);
}

/**
 *  \brief  PLATFORMTda2xxGetFtRev function to Get FT Revision Number
 */
uint32_t PLATFORMTda2xxGetFtRev(void)
{
    uint32_t ftRev;

    ftRev = HW_RD_REG32(
        SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE +
        CTRL_WKUP_STD_FUSE_DIE_ID_2);

    /* FT revision is found in bits [15:8] */
    ftRev &= (uint32_t) 0x0000FF00;

    ftRev = (ftRev >> 0x8);

    return (ftRev);
}

/*
 * \brief PLATFORMTda2xxSetPinmuxRegs function to program the pin mux properties
 *
 *
 * \param[in]   baseAddrOffset - Base address offset of pin mux config register
 * \param[in]   ioPinCfg       - property of the pin mux to be configured.
 *
 */

int32_t PLATFORMTda2xxSetPinmuxRegs(uint32_t baseAddrOffset, uint32_t ioPinCfg)
{
    uint32_t tmpRegVal;
    int32_t  retVal = STW_SOK;

    /* Unlock MMR_5 for pin muxing*/
    PLATFORMUnLockRegion(PLATFORM_MMR_REG_5);

    tmpRegVal = HW_RD_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + baseAddrOffset);

    tmpRegVal &= ~(0xF000FU);
    tmpRegVal |= (ioPinCfg & 0xF000FU);

    HW_WR_REG32((SOC_CORE_PAD_IO_REGISTERS_BASE + baseAddrOffset), tmpRegVal);
    /* Lock MMR_5 for pin muxing*/
    PLATFORMLockRegion(PLATFORM_MMR_REG_5);
    return retVal;
}

int32_t PLATFORMTda2xxLockRegion(platformMmrRegion_t region)
{
    int32_t retVal = STW_SOK;

#ifdef PLATFORM_MMR_REG_LOCK_ENABLE
    switch (region)
    {
        case PLATFORM_MMR_REG_1:
            HW_WR_REG32(0x4A002540U, 0x1A1C8144U);
            break;
        case PLATFORM_MMR_REG_2:
            HW_WR_REG32(0x4A002544U, 0xFDF45530U);
            break;
        case PLATFORM_MMR_REG_3:
            HW_WR_REG32(0x4A002548U, 0x1AE6E320U);
            break;
        case PLATFORM_MMR_REG_4:
            HW_WR_REG32(0x4A00254CU, 0x2FFA927CU);
            break;
        case PLATFORM_MMR_REG_5:
            HW_WR_REG32(0x4A002550U, 0x143F832CU);
            break;
        default:
            break;
    }
#endif
    return (retVal);
}

int32_t PLATFORMTda2xxUnLockRegion(platformMmrRegion_t region)
{
    int32_t retVal = STW_SOK;

    switch (region)
    {
        case PLATFORM_MMR_REG_1:
            HW_WR_REG32(0x4A002540U, 0x2FF1AC2BU);
            break;
        case PLATFORM_MMR_REG_2:
            HW_WR_REG32(0x4A002544U, 0xF757FDC0U);
            break;
        case PLATFORM_MMR_REG_3:
            HW_WR_REG32(0x4A002548U, 0xE2BC3A6DU);
            break;
        case PLATFORM_MMR_REG_4:
            HW_WR_REG32(0x4A00254CU, 0x1EBF131DU);
            break;
        case PLATFORM_MMR_REG_5:
            HW_WR_REG32(0x4A002550U, 0x6F361E05U);
            break;
        default:
            break;
    }

    return (retVal);
}

int32_t PLATFORMTda2xxSetPinMux(const platformInitParams_t *initParams)
{
    int32_t retVal = STW_SOK;

    /*I2C1 Mux*/
    PLATFORMSetPinmuxRegs(CTRL_CORE_PAD_I2C1_SDA, 0x60000U);
    PLATFORMSetPinmuxRegs(CTRL_CORE_PAD_I2C1_SCL, 0x60000U);
#ifdef TDA2EX_BUILD
    /*I2C5 Mux*/
    PLATFORMSetPinmuxRegs(CTRL_CORE_PAD_MCASP1_AXR0, 0x6000AU);
    PLATFORMSetPinmuxRegs(CTRL_CORE_PAD_MCASP1_AXR1, 0x6000AU);
#else
    /*I2C2 Mux*/
    PLATFORMSetPinmuxRegs(CTRL_CORE_PAD_I2C2_SDA, 0x60000U);
    PLATFORMSetPinmuxRegs(CTRL_CORE_PAD_I2C2_SCL, 0x60000U);
#endif
    /*UART1 Console Mux*/
    PLATFORMSetPinmuxRegs(CTRL_CORE_PAD_UART1_RXD, 0x40000U);
    PLATFORMSetPinmuxRegs(CTRL_CORE_PAD_UART1_TXD, (uint32_t) 0x0);

    /* GPIO mux ( for OV,LI,Aptina, Multi Deserialiser and SIL9127 Sensor) */
    if (PLATFORM_ID_ZEBU != PLATFORMGetId())
    {
        /* In EVM, needs to be configured as GPIO for mux programming
         * PAD=vin2a_d12, PIN=gpio4_13
         * PAD=vin2a_d13, PIN=gpio4_14
         * PAD=vin2a_d14, PIN=gpio4_15
         * PAD=vin2a_d15, PIN=gpio4_16 */
        PLATFORMSetPinmuxRegs(CTRL_CORE_PAD_VIN2A_D12, 0x1000EU);
        PLATFORMSetPinmuxRegs(CTRL_CORE_PAD_VIN2A_D13, 0x1000EU);
        PLATFORMSetPinmuxRegs(CTRL_CORE_PAD_VIN2A_D14, 0x1000EU);
        PLATFORMSetPinmuxRegs(CTRL_CORE_PAD_VIN2A_D15, 0x1000EU);
        PLATFORMSetPinmuxRegs(CTRL_CORE_PAD_VIN2A_D12, 0x1000EU);
        /* PAD=mcasp2_axr6, PIN=gpio2_29
         * PAD=mcasp2_axr4, PIN=gpio1_4
         * PAD=mcasp2_axr5, PIN=gpio6_7 */
        PLATFORMSetPinmuxRegs(CTRL_CORE_PAD_MCASP2_AXR6, 0x1000EU);
        PLATFORMSetPinmuxRegs(CTRL_CORE_PAD_MCASP2_AXR4, 0x1000EU);
        PLATFORMSetPinmuxRegs(CTRL_CORE_PAD_MCASP2_AXR5, 0x1000EU);
        PLATFORMSetPinmuxRegs(CTRL_CORE_PAD_VIN2A_D15, 0x1000EU);
        PLATFORMSetPinmuxRegs(CTRL_CORE_PAD_VIN2A_D12, 0x1000EU);
    }
    /* GPIO mux, OV_PWDN of vision board is connected to GPIO6_17
     * PAD=xref_clk0, PIN=gpio6_17 */
    PLATFORMSetPinmuxRegs(CTRL_CORE_PAD_XREF_CLK0, 0x4000EU);

    return (retVal);
}

int32_t PLATFORMTda2xxSetIrqXBar(const platformInitParams_t *initParams)
{
    int32_t retVal = STW_SOK;
    /* Unlock MMR_2 */
    PLATFORMUnLockRegion(PLATFORM_MMR_REG_2);
    /* XBAR VIP1_IRQ1 to IPU1_27
     * XBAR VIP2_IRQ1 to IPU1_28 */
    HW_WR_REG32(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE +
                CTRL_CORE_IPU1_IRQ_27_28, ((UInt32) 352 << 16) | (UInt32) 351);
    /* XBAR VIP3_IRQ1 to IPU1_29
     * XBAR VPE1_IRQ1 to IPU1_30 */
    HW_WR_REG32(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE +
                CTRL_CORE_IPU1_IRQ_29_30, ((UInt32) 354 << 16) | (UInt32) 353);
    /* XBAR DISPC_IRQ at IPU1_23 */
    HW_WR_REG32(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE +
                CTRL_CORE_IPU1_IRQ_23_24, (UInt32) 20);
    /* XBAR HDMI_IRQ at IPU1_26 */
    HW_WR_REG32(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE +
                CTRL_CORE_IPU1_IRQ_25_26, ((UInt32) 96 << 16));
#ifdef TDA2EX_BUILD
    /* XBAR I2C1_IRQ to IPU1_41
     * XBAR I2C5_IRQ to IPU1_42 */
    HW_WR_REG32(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE +
                CTRL_CORE_IPU1_IRQ_41_42, ((UInt32) 55 << 16) | (UInt32) 51);
#else
    /* XBAR I2C1_IRQ to IPU1_41
     * XBAR I2C2_IRQ to IPU1_42 */
    HW_WR_REG32(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE +
                CTRL_CORE_IPU1_IRQ_41_42, ((UInt32) 52 << 16) | (UInt32) 51);
#endif
    /* Lock MMR_2 */
    PLATFORMLockRegion(PLATFORM_MMR_REG_2);
    return (retVal);
}

