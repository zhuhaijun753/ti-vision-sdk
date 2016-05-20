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
#include "stdint.h"
#include <stdio.h>
#include "soc.h"
#include "soc_defines.h"
#include "platform.h"
#include "interrupt.h"
#include "uartStdio.h"
#include "hw_ctrl_core.h"
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include "i2clib/lld_hsi2c.h"
#include "stw_boardPriv.h"
#include "devices/stw_device.h"
#include "pmhal_prcm.h"
#include "pm/pmhal/pmhal_mm.h"

#if (defined (TDA2XX_BUILD))
#define SD_BOOT     (0x8107)
#define QSPI_BOOT   (0x8136)
#define NOR_BOOT    (0xA135)
#elif (defined (TDA2EX_BUILD))
#define SD_BOOT     (0x8130)
#define QSPI_1_BOOT (0x8136)
#define QSPI_4_BOOT (0x8137)
#define NOR_BOOT    (0xA135)
#elif (defined (TDA3XX_FAMILY_BUILD))
#define QSPI_1_BOOT   (0x10)
#define QSPI_4_BOOT   (0x11)
#define NOR_XIP_BOOT  (0x12)
#endif
/*******************************************************************************
**                   INTERNAL FUNCTION PROTOTYPE
*******************************************************************************/
uint32_t readBootStrap(void);

int main()
{
    uint32_t reg;
#ifdef TDA3XX_FAMILY_BUILD
    int32_t  retVal = STW_SOK;
#endif

#ifdef TDA3XX_FAMILY_BUILD
    /*Enable the module - uart3*/
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_UART3,
                                PMHAL_PRCM_MODULE_MODE_ENABLED,
                                PM_TIMEOUT_INFINITE);
    if (retVal != PM_SUCCESS)
    {
        UARTPuts("\n Uart3 Module enable - error", -1);
        return 0;
    }
#endif

    PlatformUartConsoleSetPinMux();
    UARTStdioInit();
    UARTPuts("\n uart init  ", -1);

    /* read the boot configuration swich */
    reg = readBootStrap();

#if (defined (TDA2XX_FAMILY_BUILD))
#if (defined (TDA2XX_BUILD))
    if (reg == QSPI_BOOT)
    {
        UARTPuts("\n Test successfull ", -1);
        UARTPuts("\n Boot switch is set to QSPI Boot Mode ", -1);
        UARTPutHexNum(reg);
    }
#elif (defined (TDA2EX_BUILD))
    if (reg == QSPI_1_BOOT)
    {
        UARTPuts("\n Test successfull ", -1);
        UARTPuts("\n Boot switch is set to 1-bit QSPI Boot Mode ", -1);
        UARTPutHexNum(reg);
    }
    else if (reg == QSPI_4_BOOT)
    {
        UARTPuts("\n Test successfull ", -1);
        UARTPuts("\n Boot switch is set to 4-bit QSPI Boot Mode ", -1);
        UARTPutHexNum(reg);
    }
#endif
    else if (reg == SD_BOOT)
    {
        UARTPuts("\n Test successfull ", -1);
        UARTPuts("\n Boot switch is set to SD/MMC Boot Mode ", -1);
        UARTPutHexNum(reg);
    }
    else if (reg == NOR_BOOT)
    {
        UARTPuts("\n Test successfull ", -1);
        UARTPuts("\n Boot switch is set to NOR Boot Mode ", -1);
        UARTPutHexNum(reg);
    }
    else
    {
        UARTPuts("\n Boot switch is set to DDR Boot Mode ", -1);
        UARTPutHexNum(reg);
    }
#elif (defined (TDA3XX_FAMILY_BUILD))
    reg = reg & 0x1F;

    if (reg == QSPI_1_BOOT)
    {
        UARTPuts("\n Test successfull ", -1);
        UARTPuts("\n Boot switch is set to 1-bit SPI FLASH Boot Mode ", -1);
        UARTPutHexNum(reg);
    }
    else if (reg == QSPI_4_BOOT)
    {
        UARTPuts("\n Test successfull ", -1);
        UARTPuts("\n Boot switch is set to 4-bit QSPI FLASH Boot Mode ", -1);
        UARTPutHexNum(reg);
    }
    else if (reg == NOR_XIP_BOOT)
    {
        UARTPuts("\n Test successfull ", -1);
        UARTPuts(
            "\n Boot switch is set to NOR(CFI) FLASH/other \
                     Execute-in-place(XIP) device Boot Mode ",
            -1);
        UARTPutHexNum(reg);
    }
    else if (reg == 0x0)
    {
        UARTPuts("\n Invalid Option : Select proper boot mode ", -1);
        UARTPutHexNum(reg);
    }
    else
    {
        UARTPuts("\n Boot switch is set to other special Boot Modes ", -1);
        UARTPutHexNum(reg);
    }
#endif

    return 0;
}

uint32_t readBootStrap(void)
{
    uint32_t bootValue;
    bootValue = HW_RD_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_BOOTSTRAP);
    return bootValue;
}

