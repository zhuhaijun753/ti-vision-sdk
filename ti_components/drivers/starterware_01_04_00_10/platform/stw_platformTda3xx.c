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
 *  \file stw_platformTda3xx.c
 *
 *  \brief Implements the Tda3xx platform specific functions.
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
#include "platforms/stw_platform.h"
#include <stw_platformTda3xx.h>
#include <soc.h>
#include <hw_types.h>
#include <hw/hw_ctrl_core_irq_dma.h>
#include "irq_xbar.h"
#include "soc_defines.h"
#include "i2clib/lld_hsi2c.h"
#include "boards/stw_board.h"
#include "devices/stw_device.h"
#include <hw/hw_ctrl_core_pad_io.h>
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

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t PLATFORMTda3xxInit(const platformInitParams_t *initParams)
{
    int32_t      status = STW_SOK;
    int32_t      retVal = PM_SUCCESS;
    platformId_t platfrmId;

    platfrmId = PLATFORMGetId();

    /*Enable the module - uart3*/
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_UART3,
                                PMHAL_PRCM_MODULE_MODE_ENABLED,
                                PM_TIMEOUT_INFINITE);
    if (retVal != PM_SUCCESS)
    {
        status = STW_EFAIL;
    }
    else
    {
        if ((TRUE == initParams->isPinMuxSettingReq)
            && ((PLATFORM_ID_EVM == platfrmId)
                || (PLATFORM_ID_ZEBU == platfrmId)))
        {
            status = PLATFORMTda3xxSetPinMux(initParams);
        }

        /* Cross bar setup */
        if (TRUE == initParams->isIrqXBarSettingReq)
        {
            status = PLATFORMTda3xxSetIrqXBar(initParams);
        }
    }
    return status;
}

int32_t PLATFORMTda3xxDeInit(void)
{
    int32_t status = STW_SOK;

    return (status);
}

platformCpuRev_t PLATFORMTda3xxGetCpuRev(void)
{
    /* Todo - Read from Chip ID register */
    return (PLATFORM_CPU_REV_1_0);
}

/*
 * \brief PLATFORMTda3xxSetPinmuxRegs function to program the pin mux properties
 *
 *
 * \param[in]   baseAddrOffset - Base address offset of pin mux config register
 * \param[in]   ioPinCfg       - property of the pin mux to be configured.
 *
 */

int32_t PLATFORMTda3xxSetPinmuxRegs(uint32_t baseAddrOffset, uint32_t ioPinCfg)
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

int32_t PLATFORMTda3xxLockRegion(platformMmrRegion_t region)
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

int32_t PLATFORMTda3xxUnLockRegion(platformMmrRegion_t region)
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

int32_t PLATFORMTda3xxSetPinMux(const platformInitParams_t *initParams)
{
    int32_t retVal = STW_SOK;
    /*UART3 Console Mux*/
    PLATFORMSetPinmuxRegs(CTRL_CORE_PAD_IO_SPI1_SCLK, 0x40001U);
    PLATFORMSetPinmuxRegs(CTRL_CORE_PAD_IO_SPI1_CS0, (uint32_t) 0x1);
    return (retVal);
}

int32_t PLATFORMTda3xxSetIrqXBar(const platformInitParams_t *initParams)
{
    int32_t retVal = STW_SOK;
    /* Unlock MMR_2 */
    PLATFORMUnLockRegion(PLATFORM_MMR_REG_2);
    /* XBAR VIP1_IRQ1 to IPU1_27 */
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                   CPU_IPU1, XBAR_INST_IPU1_IRQ_27, VIP1_IRQ);

    /* XBAR DISPC_IRQ to IPU1_23 */
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                   CPU_IPU1, XBAR_INST_IPU1_IRQ_23, DISPC_IRQ);
    /* Lock MMR_2 */
    PLATFORMLockRegion(PLATFORM_MMR_REG_2);
    return (retVal);
}

