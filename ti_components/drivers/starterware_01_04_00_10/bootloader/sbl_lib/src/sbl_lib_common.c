/**
 *  \file     sbl_lib_common.c
 *
 *  \brief    This file contains the SBL Library layer common across various
 *            platforms.
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
#include <stdint.h>
#include "hw_types.h"
#include "common/stw_types.h"
#include "hw_ctrl_core.h"
#include "soc.h"
#include "soc_defines.h"
#include "platform.h"
#include "mmu.h"
#include "sbl_lib/sbl_lib.h"
#include "pm/pmhal/pmhal_cm.h"
#include "pm/pmhal/pmhal_rm.h"
#include "pm/pmhal/pmhal_mm.h"
#include "pm/pmhal/pmhal_pdm.h"
#ifdef TDA3XX_FAMILY_BUILD
#include "sbl_lib_tda3xx_priv.h"
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Define DSP1's boot address value when entry point is zero */
#define SBL_LIB_DSP1_BOOT_ADDRESS_VAL      (SBLLIB_SOC_DSP_L2_BASE)

/* Define DSP2's boot address value when entry point is zero */
#define SBL_LIB_DSP2_BOOT_ADDRESS_VAL      (SBLLIB_SOC_DSP_L2_BASE)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This function configures the EVE MMU as per EVE's entry point.
 *          Contains entries to access entry location page, L4 peripheral
 *          space and internal memories. Remaining DDR entries should be
 *          taken care by application.
 *
 * \param   baseAddr       Base address of EVE MMU.
 * \param   entryPoint     Entry Point of EVE.
 *
 * \retval  None.
 */
static void SblLibEVEMMUConfig(uint32_t baseAddr, uint32_t entryPoint);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void SBLLibDSP1BringUp(uint32_t entryPoint, uint32_t sblBuildMode)
{
    uint32_t index = 0U;
    pmhalPrcmModuleSIdleState_t sIdleState;
    int32_t  retVal = STW_SOK;

    /*Check if entry point is 1KB(0x400 byte) aligned */
    if (0U != entryPoint)
    {
        if ((uint32_t) 0U != (entryPoint & (0x000003FFU)))
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_ERROR,
                "\n DSP1 entry point address is not aligned - App boot-up fails \n");
            entryPoint = 0U;
        }
    }

    /* Set the entry point. Set appropriate instructions to put DSP1 in idle
     * mode so as to power down the DSP1 Power Domain in Production
     * Build Mode when there is no App Image.
     */
    if ((0U == entryPoint) && (SBLLIB_SBL_BUILD_MODE_PROD == sblBuildMode))
    {
        /* Op code for the following assembly code: This makes the DSP
         * branch to address 0x200 offset from L2 RAM.
         *  B.S2  0x800200
         *  NOP
         *  NOP
         *  NOP
         *  NOP
         *  NOP
         *  NOP
         *  NOP
         */
        uint32_t dspInstruction1[8U] =
        {0x00004012U, 0U, 0U, 0U, 0U, 0U, 0U, 0U};

        /* Op code for the following assembly code. This code sets the
         * PDCCMD DSP Sleep mode and then executes IDLE.
         *  MVK.L1   0,A3
         *  MVKH.S1  0x1810000,A3
         *  LDW.D1T1 *+A3[0],A3
         *  MVK.L2   0,B4
         *  MVKH.S2  0x1810000,B4
         *  NOP
         *  NOP
         *  SET.S1   A3,16,16,A3
         *  STW.D2T1 A3,*+B4[0]
         *  IDLE
         */
        uint32_t dspInstruction2[16U] =
        {0x0180A358U, 0x0180C0E8U, 0x018C0264U, 0x0200A35AU,
         0x0200C0EAU, 0x00000000U, 0x00000000U, 0x018E1088U,
         0x019002F4U, 0x00000000U, 0x00000000U, 0x00000000U,
         0x0001E000U, 0x0001E000U, 0x0001E000U, 0x00000000U};

        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
            CTRL_CORE_CONTROL_DSP1_RST_VECT,
            (SBL_LIB_DSP1_BOOT_ADDRESS_VAL) >> 0xAU);

        for (index = 0U; index < 8U; index++)
        {
            HW_WR_REG32(SOC_DSP1_L2_SRAM_BASE + (4U * index),
                        dspInstruction1[index]);
        }

        for (index = 0U; index < 16U; index++)
        {
            HW_WR_REG32(SOC_DSP1_L2_SRAM_BASE + (0x200U + (4U * index)),
                        dspInstruction2[index]);
        }
    }
    else if ((0U == entryPoint) && (SBLLIB_SBL_BUILD_MODE_DEV == sblBuildMode))
    {
        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
            CTRL_CORE_CONTROL_DSP1_RST_VECT,
            (SBL_LIB_DSP1_BOOT_ADDRESS_VAL) >> 0xAU);
        for (index = 0U; index < 8U; index++)
        {
            /* Write Self Branch Instruction */
            HW_WR_REG32(SOC_DSP1_L2_SRAM_BASE + (4U * index), 0x12U);
        }
    }
    else
    {
        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
            CTRL_CORE_CONTROL_DSP1_RST_VECT,
            entryPoint >> 0xAU);
    }

    /* Bring DSP1 out of reset */
    retVal = PMHALResetRelease(PMHAL_PRCM_RG_DSP1_RST, PM_TIMEOUT_INFINITE);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to release DSP1 reset \n");
    }

    if ((0U == entryPoint) && (SBLLIB_SBL_BUILD_MODE_PROD == sblBuildMode))
    {
        /* Power Down the DSP1 power domain */
        PMHALCMSetCdClockMode(PMHAL_PRCM_CD_DSP1,
                              PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                              PM_TIMEOUT_INFINITE);

        PMHALModuleModeSet(PMHAL_PRCM_MOD_DSP1,
                           PMHAL_PRCM_MODULE_MODE_DISABLED,
                           PM_TIMEOUT_INFINITE);

        PMHALPdmSetPDState(PMHAL_PRCM_PD_DSP1,
                           PMHAL_PRCM_PD_STATE_OFF,
                           PM_TIMEOUT_INFINITE);
    }
    else
    {
        /* Check the status of DSP1 Module Mode */
        do
        {
            PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_DSP1, &sIdleState);
        }
        while (sIdleState != PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL);
    }
}

void SBLLibDSP2BringUp(uint32_t entryPoint, uint32_t sblBuildMode)
{
    uint32_t index = 0U;
    pmhalPrcmModuleSIdleState_t sIdleState;
    int32_t  retVal = STW_SOK;

    /*Check if entry point is 1KB(0x400 byte) aligned */
    if (0U != entryPoint)
    {
        if ((uint32_t) 0U != (entryPoint & (0x000003FFU)))
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_ERROR,
                "\n DSP2 entry point address is not aligned - App boot-up fails \n");
            entryPoint = 0U;
        }
    }

    /* Set the entry point. Set appropriate instructions to put DSP2 in idle
     * mode so as to power down the DSP1 Power Domain in Production
     * Build Mode when there is no App Image.
     */
    if ((0U == entryPoint) && (SBLLIB_SBL_BUILD_MODE_PROD == sblBuildMode))
    {
        /* Op code for the following assembly code: This makes the DSP
         * branch to address 0x200 offset from L2 RAM.
         *  B.S2  0x800200
         *  NOP
         *  NOP
         *  NOP
         *  NOP
         *  NOP
         *  NOP
         *  NOP
         */
        uint32_t dspInstruction1[8U] =
        {0x00004012U, 0U, 0U, 0U, 0U, 0U, 0U, 0U};

        /* Op code for the following assembly code. This code sets the
         * PDCCMD DSP Sleep mode and then executes IDLE.
         *  MVK.L1   0,A3
         *  MVKH.S1  0x1810000,A3
         *  LDW.D1T1 *+A3[0],A3
         *  MVK.L2   0,B4
         *  MVKH.S2  0x1810000,B4
         *  NOP
         *  NOP
         *  SET.S1   A3,16,16,A3
         *  STW.D2T1 A3,*+B4[0]
         *  IDLE
         */
        uint32_t dspInstruction2[16U] =
        {0x0180A358U, 0x0180C0E8U, 0x018C0264U, 0x0200A35AU,
         0x0200C0EAU, 0x00000000U, 0x00000000U, 0x018E1088U,
         0x019002F4U, 0x00000000U, 0x00000000U, 0x00000000U,
         0x0001E000U, 0x0001E000U, 0x0001E000U, 0x00000000U};

        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
            CTRL_CORE_CONTROL_DSP2_RST_VECT,
            (SBL_LIB_DSP2_BOOT_ADDRESS_VAL) >> 0xAU);

        for (index = 0U; index < 8U; index++)
        {
            HW_WR_REG32(SOC_DSP2_L2_SRAM_BASE + (4U * index),
                        dspInstruction1[index]);
        }

        for (index = 0U; index < 16U; index++)
        {
            HW_WR_REG32(SOC_DSP2_L2_SRAM_BASE + (0x200U + (4U * index)),
                        dspInstruction2[index]);
        }
    }
    else if ((0U == entryPoint) && (SBLLIB_SBL_BUILD_MODE_DEV == sblBuildMode))
    {
        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
            CTRL_CORE_CONTROL_DSP2_RST_VECT,
            (SBL_LIB_DSP2_BOOT_ADDRESS_VAL) >> 0xAU);
        for (index = 0U; index < 8U; index++)
        {
            /* Write Self Branch Instruction */
            HW_WR_REG32(SOC_DSP2_L2_SRAM_BASE + (4U * index), 0x12U);
        }
    }
    else
    {
        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
            CTRL_CORE_CONTROL_DSP2_RST_VECT,
            entryPoint >> 0xAU);
    }

    /* Bring DSP2 out of reset */
    retVal = PMHALResetRelease(PMHAL_PRCM_RG_DSP2_RST, PM_TIMEOUT_INFINITE);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to release DSP2 reset \n");
    }

    if ((0U == entryPoint) && (SBLLIB_SBL_BUILD_MODE_PROD == sblBuildMode))
    {
        /* Power Down the DSP2 power domain */
        PMHALCMSetCdClockMode(PMHAL_PRCM_CD_DSP2,
                              PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                              PM_TIMEOUT_INFINITE);

        PMHALModuleModeSet(PMHAL_PRCM_MOD_DSP2,
                           PMHAL_PRCM_MODULE_MODE_DISABLED,
                           PM_TIMEOUT_INFINITE);

        PMHALPdmSetPDState(PMHAL_PRCM_PD_DSP2,
                           PMHAL_PRCM_PD_STATE_OFF,
                           PM_TIMEOUT_INFINITE);
    }
    else
    {
        /* Check the status of DSP2 Module Mode */
        do
        {
            PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_DSP2, &sIdleState);
        }
        while (sIdleState != PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL);
    }
}

void SBLLibEVE1BringUp(uint32_t entryPoint, uint32_t sblBuildMode)
{
    pmhalPrcmModuleSIdleState_t sIdleState;
    int32_t retVal = STW_SOK;

    if (0U != entryPoint)
    {
        /* Set the EVE MMU and entry point */
        SblLibEVEMMUConfig(SBLLIB_SOC_IPU_EVE_MMU0_BASE, entryPoint);
    }
    else
    {
        /* Assuming SBLLIB_EVE_BOOT_ADDRESS_NO_IMAGE i.e. 0x80000000U is
         * not in use. Reset vector points to
         * SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE i.e. 0x80000100U */
        HW_WR_REG32(SBLLIB_EVE_BOOT_ADDRESS_NO_IMAGE,
                    SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE);

        /* IDLE; Op Code for ARP32 */
        HW_WR_REG32(SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE, 0x0000037FU);
        /* IDLE; Op Code for ARP32 */
        HW_WR_REG32(SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE + 0x4U,
                    0x0000037FU);
        /* IDLE; Op Code for ARP32 */
        HW_WR_REG32(SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE + 0x8U,
                    0x0000037FU);
        /* IDLE; Op Code for ARP32 */
        HW_WR_REG32(SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE + 0xCU,
                    0x0000037FU);

        /* Set the EVE MMU and entry point */
        SblLibEVEMMUConfig(SBLLIB_SOC_IPU_EVE_MMU0_BASE,
                           SBLLIB_EVE_BOOT_ADDRESS_NO_IMAGE);
    }

    /* Bring EVE1 out of reset */
    retVal = PMHALResetRelease(PMHAL_PRCM_RG_EVE1_CPU_RST, PM_TIMEOUT_INFINITE);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to release EVE1 reset \n");
    }

    /* Power Down the EVE Power Domain in Production Build Mode
     * when there is no App Image */
    if ((0U == entryPoint) && (SBLLIB_SBL_BUILD_MODE_PROD == sblBuildMode))
    {
        /* Force Idle the EVE EDMA TPTC0 and TPTC1 */
        HW_WR_REG32(SBLLIB_SOC_IPU_EVE_TPTC0_BASE + 0x10U, 0U);
        HW_WR_REG32(SBLLIB_SOC_IPU_EVE_TPTC1_BASE + 0x10U, 0U);

        PMHALCMSetCdClockMode(PMHAL_PRCM_CD_EVE1,
                              PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                              PM_TIMEOUT_INFINITE);

        PMHALModuleModeSet(PMHAL_PRCM_MOD_EVE1,
                           PMHAL_PRCM_MODULE_MODE_DISABLED,
                           PM_TIMEOUT_INFINITE);

        PMHALPdmSetPDState(PMHAL_PRCM_PD_EVE1,
                           PMHAL_PRCM_PD_STATE_OFF,
                           PM_TIMEOUT_INFINITE);
    }
    else
    {
        /* Check the status of EVE1 Module Mode */
        do
        {
            PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_EVE1, &sIdleState);
        }
        while (sIdleState != PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL);
    }
}

void SBLLibConvertHexToString(uint32_t hexValue, char *stringValue)
{
    uint32_t remainder = 0, quotient = 0;
    uint32_t dividend  = 0;
    /* Count starts from two because of '0x' */
    int32_t  count = 2;

    dividend = hexValue;

    do
    {
        quotient           = dividend / 16U;
        remainder          = dividend % 16U;
        stringValue[count] = (char) (dividend / 16U);
        if (0U == quotient)
        {
            stringValue[count] = (char) (dividend % 16U);
            break;
        }
        count++;
        dividend = remainder;
    } while (count < 10);

    /* If we exceed limit, reduce and print from actual digits */
    if (count == 10)
    {
        count--;
    }
    while (count >= 2)
    {
        /* Checking for alphanumeric numbers. */
        if ((16 - stringValue[count]) <= 6)
        {
            /* Alphanumeric numbers. */
            stringValue[count] = stringValue[count] + 0x37U;
            count--;
        }
        else
        {
            /* Numbers in the range 0 to 9. */
            stringValue[count] = stringValue[count] + 0x30U;
            count--;
        }
    }
    stringValue[count] = (char) 'x';
    count--;
    stringValue[count] = (char) '0';
}

void SBLLibAbortBoot(void)
{
    /*
     * Boot unsuccessful, Abort
     * Added dummy variable to avoid MISRA C error
     */

    volatile uint32_t dummyVal = 0U;

    while (1)
    {
        if (1U == dummyVal)
        {
            break;
        }
    }
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static void SblLibEVEMMUConfig(uint32_t baseAddr, uint32_t entryPoint)
{
    MMU_TlbEntry_t mmuEntry       = {0U};
    uint32_t       entryPointPage = 0U;

    /* Derive entry point page for given entry point */
    entryPointPage = entryPoint & (0xFF000000U);

    /* Configure MMU TLB entry for Vector table  as 1MB section */
    /* EVE starts executing from virtual address 0x0 when brought out of reset.
     * When SBL maps the 0x0 to entryPointPage, it assumes that the vector
     * table is present at entryPointPage.
     * E.g. If entry point is 0x81F62648, entryPointPage is calculated as
     * 0x81000000 and application image should be built in a way that vector
     * table is present at this address.
     */
    mmuEntry.phyAddr        = entryPointPage;
    mmuEntry.virtAddr       = 0x00000000U;
    mmuEntry.valid          = (uint32_t) TRUE;
    mmuEntry.pageSize       = MMU_Section_Size;
    mmuEntry.endianness     = MMU_Little_Endian;
    mmuEntry.elementSize    = MMU_NoTranslation_ElementSize;
    mmuEntry.tlbElementSize = MMU_CPU_ElementSize;
    mmuEntry.preserve       = (uint32_t) TRUE;
    MMUTlbEntrySet(baseAddr, (uint32_t) 1U, &mmuEntry);

    /*
     * Configure MMU TLB entry for code & data section  as 16MB super
     * section
     */
    mmuEntry.phyAddr        = entryPointPage;
    mmuEntry.virtAddr       = entryPointPage;
    mmuEntry.valid          = (uint32_t) TRUE;
    mmuEntry.pageSize       = MMU_SuperSection_Size;
    mmuEntry.endianness     = MMU_Little_Endian;
    mmuEntry.elementSize    = MMU_NoTranslation_ElementSize;
    mmuEntry.tlbElementSize = MMU_CPU_ElementSize;
    mmuEntry.preserve       = (uint32_t) TRUE;
    MMUTlbEntrySet(baseAddr, (uint32_t) 2U, &mmuEntry);

    /*
     * Configure MMU TLB entry for EVE's internal memory  as 16MB super
     * section
     */
    mmuEntry.phyAddr        = SBLLIB_SOC_EVE_DMEM_BASE;
    mmuEntry.virtAddr       = SBLLIB_SOC_EVE_DMEM_BASE;
    mmuEntry.valid          = (uint32_t) TRUE;
    mmuEntry.pageSize       = MMU_SuperSection_Size;
    mmuEntry.endianness     = MMU_Little_Endian;
    mmuEntry.elementSize    = MMU_NoTranslation_ElementSize;
    mmuEntry.tlbElementSize = MMU_CPU_ElementSize;
    mmuEntry.preserve       = (uint32_t) TRUE;
    MMUTlbEntrySet(baseAddr, (uint32_t) 3U, &mmuEntry);

    /*
     * Configure MMU TLB entry for L4PER1, L4PER2 and L4PER3 as 16MB super
     * section
     */
    mmuEntry.phyAddr        = SOC_L4_PER_AP_BASE;
    mmuEntry.virtAddr       = SOC_L4_PER_AP_BASE;
    mmuEntry.valid          = (uint32_t) TRUE;
    mmuEntry.pageSize       = MMU_SuperSection_Size;
    mmuEntry.endianness     = MMU_Little_Endian;
    mmuEntry.elementSize    = MMU_NoTranslation_ElementSize;
    mmuEntry.tlbElementSize = MMU_CPU_ElementSize;
    mmuEntry.preserve       = (uint32_t) TRUE;
    MMUTlbEntrySet(baseAddr, (uint32_t) 4U, &mmuEntry);

    /* Enable MMU */
    MMUEnable(baseAddr);

    SBLLibPrintf(
        SBLLIB_TRACE_LEVEL_INFO1,
        "\n EVE MMU configuration completed \n");
}

