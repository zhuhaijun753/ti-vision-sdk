/**
 *  \file     mmu_a15_data_validation_app_main.c
 *
 *  \brief    Source file containing the example application code for A15 MMU
 *            App. First MMU is enabled and data is written using virtual
 *            address. Afterwards MMU is disabled and data is read from physical
 *            address and data integrity is verified.
 *
 *  \copyright Copyright (C) 2015 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

/* ======================================================================
 *   Copyright (C) 2015 Texas Instruments Incorporated
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
#include "hw_types.h"
#include "soc.h"
#include "soc_defines.h"
#include "mmu_a15.h"
#include "cache_a15.h"
#include "uartStdio.h"
#include "platform.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

__attribute__((aligned(16384)))
mmuA15ModuleTable_t gMmuTable;

mmuA15DescriptorAttrs_t gAttrs;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main()
{
    uint32_t cacheEnabled = 0;
    uint32_t virtualAddr, tempVirtualAddr;
    uint32_t phyAddr, tempPhyAddr;
    uint32_t regVal = 0, err = 0;

    /* UART Init */
    PlatformUARTSetPinMux(UART1_INST);
    UARTStdioInit();

    UARTPuts("\nA15 MMU Data Validation App", -1);

    /* Check if cache is already enabled */
    cacheEnabled = CACHEA15GetEnabled();

    /* In case cache is disabled, invalidate and enable it */
    if (CACHE_A15_TYPE_ALL != cacheEnabled)
    {
        CACHEA15InvalidateL1DAll();

        CACHEA15InvalidateL1IAll();

        CACHEA15Enable(CACHE_A15_TYPE_ALL);
    }

    /* Initialize MMU module */
    MMUA15Init();

    /* Set MAIR to inner and outer cacheable */
    MMUA15SetMAIR(&gMmuTable, MMU_A15_ATTR_INDEX_2, 0xFF);

    /* Initialize descriptor attributes */
    MMUA15InitDescAttrs(&gAttrs);

    /* Set level one descriptor attributes */
    gAttrs.descriptorType = MMU_A15_DESCRIPTOR_TYPE_BLOCK;
    gAttrs.attrIndx       = MMU_A15_ATTR_INDEX_2;
    gAttrs.nonSecure      = MMU_A15_NON_SECURE_ENABLE;
    gAttrs.accPerm        = MMU_A15_ACC_PERM_RW_ANY_PL; /*Read Write at any PL */

    /* Set level one descriptor */
    virtualAddr = 0x0, phyAddr = 0x0;
    MMUA15SetFirstLevelDesc(&gMmuTable, virtualAddr, phyAddr, &gAttrs);
    virtualAddr = 0x40000000, phyAddr = 0x40000000;
    MMUA15SetFirstLevelDesc(&gMmuTable, virtualAddr, phyAddr, &gAttrs);
    virtualAddr = 0x80000000, phyAddr = 0x80000000;
    MMUA15SetFirstLevelDesc(&gMmuTable, virtualAddr, phyAddr, &gAttrs);
    virtualAddr = 0xc0000000, phyAddr = 0x80000000;
    MMUA15SetFirstLevelDesc(&gMmuTable, virtualAddr, phyAddr, &gAttrs);

    /* Enable MMU */
    MMUA15Enable(&gMmuTable);

    virtualAddr = 0xd0000000;

    for (tempVirtualAddr = virtualAddr;
         tempVirtualAddr < virtualAddr + 0x00200000;
         tempVirtualAddr = tempVirtualAddr + 4)
    {
        HW_WR_REG32(tempVirtualAddr, 0x12345678U);
    }

    /* Disable MMU */
    MMUA15Disable();

    phyAddr = 0x90000000;

    /* Check if data is written correctly at physical address */
    for (tempPhyAddr = phyAddr;
         tempPhyAddr < phyAddr + 0x00200000;
         tempPhyAddr = tempPhyAddr + 4)
    {
        regVal = HW_RD_REG32(tempPhyAddr);
        if (0x12345678 != regVal)
        {
            UARTPuts("\nData read error at address:", -1);
            UARTPutHexNum(tempPhyAddr);
            err = 1;
            break;
        }
    }

    if ((0U == err) && (tempPhyAddr == (phyAddr + 0x00200000)))
    {
        UARTPuts("\nData integrity verified", -1);
        UARTPuts("\nA15 MMU App Passed", -1);
    }

    /* Disable cache */
    CACHEA15Disable(CACHE_A15_TYPE_ALL);

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */