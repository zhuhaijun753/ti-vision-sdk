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
 *   Component:         SBL
 *
 *   Filename:          sbl_tda2xx_slavecore_boot.c
 *
 *   Description:       This file contain functions to wake-up clock domain,
 *          module enable & booting up the slave cores
 */

/****************************************************************
 *  INCLUDE FILES
 ****************************************************************/

#include <stdint.h>
#include "hw_types.h"
#include "soc.h"
#include "cpu.h"
#include "pmhal_prcm.h"
#include "pm/pmhal/pmhal_mm.h"
#include "pm/pmhal/pmhal_rm.h"
#include "pm/pmhal/pmhal_pdm.h"
#include "hw_ipu_prm.h"
#include "hw_mpu_wugen.h"
#include "hw_ipu_cm_core_aon.h"
#include "hw_core_cm_core.h"
#include "hw_core_prm.h"
#include "hw_dsp1_prm.h"
#include "hw_dsp1_cm_core_aon.h"
#include "hw_dsp2_prm.h"
#include "hw_dsp2_cm_core_aon.h"
#include "hw_eve1_prm.h"
#include "hw_eve1_cm_core_aon.h"
#include "hw_eve2_prm.h"
#include "hw_eve2_cm_core_aon.h"
#include "hw_eve3_prm.h"
#include "hw_eve3_cm_core_aon.h"
#include "hw_eve4_prm.h"
#include "hw_eve4_cm_core_aon.h"
#include "hw_iva_prm.h"
#include "hw_iva_cm_core.h"
#include "hw_ctrl_core.h"
#include "soc.h"
#include "sbl_tda2xx_platform.h"
#include "mmu.h"
#include "soc_defines.h"
#include "uartConsole.h"
#include "sbl_tda2xx_slavecore_boot.h"
#include "pmhal_cm.h"
#include "pmhal_mpu_lprm.h"
#include "pmlib_cpuidle.h"
#include "mpu_wugen.h"
#include "cp15.h"

/* ============================================================================
 * GLOBAL VARIABLES DECLARATIONS
 * =============================================================================
 */

/* ============================================================================
 * LOCAL VARIABLES DECLARATIONS
 * =============================================================================
 */
#define DSP1BOOTADDR        (SOC_CTRL_MODULE_CORE_BASE + 0x55CU)
#define DSP1BOOTADDRVALUE       (0x00800000U)

#define DSP2BOOTADDR        (SOC_CTRL_MODULE_CORE_BASE + 0x560U)
#define DSP2BOOTADDRVALUE       (0x00800000U)

#define ICONT1_ITCM              (SOC_IVA_CONFIG_BASE + 0x08000U)
#define ICONT2_ITCM              (SOC_IVA_CONFIG_BASE + 0x18000U)

/* ============================================================================
 * LOCAL FUNCTIONS PROTOTYPES
 * =============================================================================
 */

/* ============================================================================
 * FUNCTIONS
 * =============================================================================
 */

/**
 * \brief               DSP_SystemReset
 *
 *
 *
 * \param[in]  EntryPoint - CPU entry location on reset
 *
 * \return      None.
 *
 **/
int32_t CPU_SystemReset(cpu_core_id_t cpu)
{
    pmhalPrcmResetGroupId_t SYSTEM_RESET = (pmhalPrcmResetGroupId_t) 0;
    pmhalPrcmResetGroupId_t LOCAL_RESET  = (pmhalPrcmResetGroupId_t) 0;
    int32_t  retVal  = 0;
    uint32_t retStat = 0U;

    SBL_PRINTF(TRACE_LOW, __func__);
    SBL_PRINTF(TRACE_LOW, "\nDSP1_SystemReset\n");

    switch (cpu)
    {
        case DSP1_ID:
            SYSTEM_RESET = PMHAL_PRCM_RG_DSP1_SYS_RST;
            LOCAL_RESET  = PMHAL_PRCM_RG_DSP1_RST;
            break;
#ifdef TDA2XX_BUILD
        case DSP2_ID:
            SYSTEM_RESET = PMHAL_PRCM_RG_DSP2_SYS_RST;
            LOCAL_RESET  = PMHAL_PRCM_RG_DSP2_RST;
            break;

        case EVE1_ID:
            SYSTEM_RESET = PMHAL_PRCM_RG_EVE1_RST;
            LOCAL_RESET  = PMHAL_PRCM_RG_EVE1_CPU_RST;
            break;

        case EVE2_ID:
            SYSTEM_RESET = PMHAL_PRCM_RG_EVE2_RST;
            LOCAL_RESET  = PMHAL_PRCM_RG_EVE2_CPU_RST;
            break;

        case EVE3_ID:
            SYSTEM_RESET = PMHAL_PRCM_RG_EVE3_RST;
            LOCAL_RESET  = PMHAL_PRCM_RG_EVE3_CPU_RST;
            break;

        case EVE4_ID:
            SYSTEM_RESET = PMHAL_PRCM_RG_EVE4_RST;
            LOCAL_RESET  = PMHAL_PRCM_RG_EVE4_CPU_RST;
            break;
#endif
        default:
            SYSTEM_RESET = PMHAL_PRCM_RG_LOWER_BOUND;
            LOCAL_RESET  = PMHAL_PRCM_RG_LOWER_BOUND;
            SBL_PRINTF(TRACE_HIGH, "\n CPU SystemReset - CPU ID error \n");
            retVal = -1;
            break;
    }
    if (retVal != -1)
    {
        /*Assert the Reset for given CPU ID*/
        retVal = PMHALResetAssert(SYSTEM_RESET);
        if (0 != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n SYSTEM_RESET Assert Failed \n");
        }
        retVal = PMHALResetAssert(LOCAL_RESET);
        if (0 != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n LOCAL_RESET Assert Failed \n");
        }

        /*Check the Reset status & clear*/
        retVal = PMHALResetGetStatus(LOCAL_RESET, &retStat);
        if (0 != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n LOCAL_RESET get status Failed \n");
        }
        if (0x1U == retStat)
        {
            retVal = PMHALResetClearStatus(LOCAL_RESET);
            if (0 != retVal)
            {
                SBL_PRINTF(TRACE_HIGH,
                           "\n LOCAL_RESET clear status Failed \n");
            }
            retStat = 0U;
        }
        retVal = PMHALResetGetStatus(SYSTEM_RESET, &retStat);
        if (0 != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n SYSTEM_RESET get status Failed \n");
        }
        if (0x1U == retStat)
        {
            retVal = PMHALResetClearStatus(SYSTEM_RESET);
            if (0 != retVal)
            {
                SBL_PRINTF(TRACE_HIGH,
                           "\n SYSTEM_RESET clear status Failed \n");
            }
            retStat = 0U;
        }

        /*Clear reset for MMU, Cache & Slave interface OCP port*/
        retVal = PMHALResetRelease(SYSTEM_RESET, PM_TIMEOUT_INFINITE);
        if (0 != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n SYSTEM_RESET Release Failed \n");
        }
    }
    return retVal;
}

/**
 * \brief               IPU1_Clk_Enable is PRCM function for IPU1. Configure the
 *          module to auto & force-wake-up the clock domain
 *
 *
 * \param           None.
 *
 * \return      error status.If error has occured it returns a non zero value.
 *      If no error has occured then return status will be zero.
 *
 **/
int32_t IPU1_Clk_Enable(void)
{
    int32_t retval = 0;

    SBL_PRINTF(TRACE_LOW, __func__);

    /* Select CORE_IPU_ISS_BOOST_CLK from CORE_DPLL for IPU1_GFCLK */
    retval = PMHALCMMuxParentSelect(PMHAL_PRCM_MUX_IPU1_GFCLK_MUX,
                                    PMHAL_PRCM_DPLL_CORE);
    if (retval != 0)
    {
        SBL_PRINTF(TRACE_HIGH, "\n ipu1 clock selection - Error \n");
    }
    else
    {
        retval = PMHALModuleModeSet(PMHAL_PRCM_MOD_IPU1,
                                    PMHAL_PRCM_MODULE_MODE_AUTO,
                                    PM_TIMEOUT_INFINITE);

        if (retval != 0)
        {
            SBL_PRINTF(TRACE_HIGH, "\nEnable IPU1 Module - Error \n");
        }
        else
        {
            /*Force Wake-up clock domain ipu1*/
            retval = PMHALCMSetCdClockMode(PMHAL_PRCM_CD_IPU1,
                                           PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                           PM_TIMEOUT_INFINITE);

            SBL_PRINTF(TRACE_LOW, "\nEnable IPU1 CLK Enable - completed \n");
        }
    }
    return retval;
}

/**
 * \brief     This function brings up the MPU Core1. Core0 will program the
 *            AUXBOOT registers and then it will send the SEV instruction.
 *
 * \param     EntryPoint       CPU entry point location
 *
 * \return    None.
 *
 **/
void MPU_CPU1_BringUp(uint32_t EntryPoint, uint32_t sblBuildMode)
{
    pmhalMpuLprmHgRampParams_t hgRampParam = {1, 0};

    SBL_PRINTF(TRACE_LOW, __func__);
    SBL_PRINTF(TRACE_LOW, "\nMPU CPU1 Set Entry Point\n");

    if (0U != EntryPoint)
    {
        /* Write the entry-point into AUXBOOT1 */
        HW_WR_REG32(SOC_MPU_WUGEN_BASE + MPU_AUX_CORE_BOOT_1, EntryPoint);

        /* Write the enable indicator into AUXBOOT0 */
        HW_WR_REG32(SOC_MPU_WUGEN_BASE + MPU_AUX_CORE_BOOT_0, 0x10U);

        /* Send event to wake-up CPU1 */
        CPUSendEvent();
    }
    else
    {
        if (SBL_BUILD_MODE_DEV != sblBuildMode)
        {
            /* Enable Hg/FastRamp-up in Retention */
            PMHALMpuLprmSetHgRampParams(&hgRampParam);
            PMHALMpuLprmSetMercuryRetention();
            MPU_WUGEN_1_DisableAll();
            /* Flushing the DCache is required to ensure CPU0 does not get
             * pipeline stalled when the cache is enabled later and the
             * cache invalidate is performed. */
            SBL_PRINTF(TRACE_HIGH, "Flush DCache...\r\n\n");
            CP15DCacheCleanFlush();
            SBL_PRINTF(TRACE_HIGH, "Putting CPU1 in OFF...\r\n\n");
            PMLIBCpu1ForcedOff();
        }
    }
}

/**
 * \brief          IPU1_SystemReset function assert reset(CPU0 & IPU1 SS) ,
 *                 configure AMMU, set the entry point & release the CPU0
 *                 from reset.
 *
 *
 * \param[in]  EntryPoint - CPU entry location on reset
 *
 * \return      None.
 *
 **/
void IPU1_SystemReset(void)
{
    SBL_PRINTF(TRACE_LOW, __func__);
    SBL_PRINTF(TRACE_LOW, "\nIPU SystemReset\n");
    int32_t  retVal  = 0;
    uint32_t retStat = 0U;

    /*Assert the Reset*/
    retVal = PMHALResetAssert(PMHAL_PRCM_RG_IPU1_CPU1_RST);
    if (0 != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n IPU1_CPU1_RST Assert Failed \n");
    }
    retVal = PMHALResetAssert(PMHAL_PRCM_RG_IPU1_CPU0_RST);
    if (0 != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n IPU1_CPU0_RST Assert Failed \n");
    }
    retVal = PMHALResetAssert(PMHAL_PRCM_RG_IPU1_RST);
    if (0 != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n IPU1_RST Assert Failed \n");
    }

    /*Check the Reset status & clear*/
    retVal = PMHALResetGetStatus(PMHAL_PRCM_RG_IPU1_CPU1_RST, &retStat);
    if (0 != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n IPU1_CPU0_RST get status Failed \n");
    }
    if (0x1U == retStat)
    {
        retVal = PMHALResetClearStatus(PMHAL_PRCM_RG_IPU1_CPU1_RST);
        if (0 != retVal)
        {
            SBL_PRINTF(TRACE_HIGH,
                       "\n IPU1_CPU1_RST clear status Failed \n");
        }
        retStat = 0U;
    }
    retVal = PMHALResetGetStatus(PMHAL_PRCM_RG_IPU1_CPU0_RST, &retStat);
    if (0 != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n IPU1_CPU0_RST get status Failed \n");
    }
    if (0x1U == retStat)
    {
        retVal = PMHALResetClearStatus(PMHAL_PRCM_RG_IPU1_CPU0_RST);
        if (0 != retVal)
        {
            SBL_PRINTF(TRACE_HIGH,
                       "\n IPU1_CPU0_RST clear status Failed \n");
        }
        retStat = 0U;
    }
    retVal = PMHALResetGetStatus(PMHAL_PRCM_RG_IPU1_RST, &retStat);
    if (0 != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n IPU1_RST get status Failed \n");
    }
    if (0x1U == retStat)
    {
        retVal = PMHALResetClearStatus(PMHAL_PRCM_RG_IPU1_RST);
        if (0 != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n IPU1_RST clear status Failed \n");
        }
        retStat = 0U;
    }

    /*Configure the boot translation page of IPU1 to 0x55020000 - IPU_RAM*/
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_CORTEX_M4_MMUADDRLOGICTR, 0x00000);
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_CORTEX_M4_MMUADDRTRANSLTR, 0x55020);

    /*Bring the MMU & cache out of reset*/

    retVal = PMHALResetRelease(PMHAL_PRCM_RG_IPU1_RST, PM_TIMEOUT_INFINITE);
    if (0 != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n IPU1_RST Release Failed \n");
    }
}

/**
 * \brief         IPU1_AMMU_Config function configure the IPU1 AMMU. Add
 *    entires to access DDR, L4Per1,L4Per2 & L4Per3,
 *    L3 RAM & IRAM
 *
 * \param           None.
 *
 * \return      None.
 *
 *
 **/
void IPU1_AMMU_Config(void)
{
    /*Large Page Translations */
    /* Logical Address */
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE, 0x40000000);
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x04U, 0x80000000U);
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x08U, 0xa0000000U);
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x0CU, 0x60000000);

    /* Physical Address */
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x20U, 0x40000000);
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x24U, 0x80000000U);
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x28U, 0xa0000000U);
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x2CU, 0x40000000);

    /* Policy Register */
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x40U, 0x00000007);
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x44U, 0x000B0007);
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x48U, 0x00020007);
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x4CU, 0x00000007);

    /*Medium Page*/
    /* Logical Address */
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x60U, 0x00300000);
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x64U, 0x20100000);

    /* Physical Address */
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0xA0U, 0x40300000);
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0xA4U, 0x43300000);

    /* Policy Register */
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0xE0U, 0x00000007);
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0xE4U, 0x00020007);

    /*Small Page*/
    /* Logical Address */
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x120U, 0x00000000);
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x124U, 0x20000000);
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x128U, 0x00004000);
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x12CU, 0x00008000);
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x130U, 0x0000C000);

    /* Physical Address */
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x1A0U, 0x55020000);
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x1A4U, 0x55020000);
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x1A8U, 0x55024000);
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x1ACU, 0x55028000);
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x1B0U, 0x5502C000);

    /* Policy Register */
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x220U, 0x0001000B);
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x224U, 0x0000000B);
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x228U, 0x00010007);
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x22CU, 0x00000007);
    HW_WR_REG32(SOC_IPU1_TARGET_UNICACHE_MMU_BASE + 0x230U, 0x00000007);
}

/**
 * \brief         IPU1_CPU0_BringUp function assert reset(CPU0 & IPU1 SS)
 *    configure AMMU, set the entry point & release the CPU0
 *    from reset.
 *
 *
 * \param[in]  EntryPoint - CPU entry location on reset
 *
 * \return      None.
 *
 **/
void IPU1_CPU0_BringUp(uint32_t EntryPoint, uint32_t sblBuildMode)
{
    int32_t retVal = 0;
    pmhalPrcmModuleSIdleState_t sIdleState;

    SBL_PRINTF(TRACE_LOW, __func__);
    SBL_PRINTF(TRACE_LOW, "\nSet Entry Point\n");

    /*Set the Entry point*/
    if (EntryPoint == 0)
    {
        HW_WR_REG32(MPU_IPU1_RAM, 0x10000);
        HW_WR_REG32(MPU_IPU1_RAM + 0x4U, 0x9);
        HW_WR_REG32(MPU_IPU1_RAM + 0x8U, 0xE7FEE7FEU);
    }
    else
    {
        HW_WR_REG32(MPU_IPU1_RAM, 0x10000);
        HW_WR_REG32(MPU_IPU1_RAM + 0x4U, EntryPoint);
    }

    if ((sblBuildMode == SBL_BUILD_MODE_DEV) || (EntryPoint != 0))
    {
        SBL_PRINTF(TRACE_LOW, "\n Bringout of reset \n");

        /* Bring-out of Reset - CPU0*/
        retVal = PMHALResetRelease(PMHAL_PRCM_RG_IPU1_CPU0_RST,
                                   PM_TIMEOUT_INFINITE);
        if (0 != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n IPU1_CPU0_RST Release Failed \n");
        }

        /*Check the Status of IPU1 Module mode*/
        do
        {
            PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_IPU1, &sIdleState);
        }
        while (sIdleState != PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL);
    }
}

/**
 * \brief          IPU1_CPU1_BringUp function assert reset(CPU1), set the
 *     entry point & release the CPU1
 *     from reset.
 *
 *
 * \param[in]  EntryPoint - CPU entry location on reset
 *
 * \return      None.
 *
 **/
void IPU1_CPU1_BringUp(uint32_t EntryPoint, uint32_t sblBuildMode)
{
    int32_t  retVal  = 0;
    uint32_t retStat = 0U;
    pmhalPrcmModuleSIdleState_t sIdleState;

    SBL_PRINTF(TRACE_LOW, __func__);
    SBL_PRINTF(TRACE_LOW, "\nSet Entry Point\n");

    /*Assert the CPU1 Reset*/
    retVal = PMHALResetAssert(PMHAL_PRCM_RG_IPU1_CPU1_RST);
    if (0 != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n IPU1_CPU1_RST Assert Failed \n");
    }

    /*Check the reset status & clear*/
    retVal = PMHALResetGetStatus(PMHAL_PRCM_RG_IPU1_CPU1_RST, &retStat);
    if (0 != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n IPU1_CPU0_RST get status Failed \n");
    }
    if (retStat == 0x1U)
    {
        retVal = PMHALResetClearStatus(PMHAL_PRCM_RG_IPU1_CPU1_RST);
        if (0 != retVal)
        {
            SBL_PRINTF(TRACE_HIGH,
                       "\n IPU1_CPU1_RST clear status Failed \n");
        }
    }

    /*Set the Entry point*/
    if (EntryPoint == 0)
    {
        HW_WR_REG32(MPU_IPU1_RAM, 0x10000);
        HW_WR_REG32(MPU_IPU1_RAM + 0x4U, 0x9);
        HW_WR_REG32(MPU_IPU1_RAM + 0x8U, 0xE7FEE7FEU);
    }
    else
    {
        HW_WR_REG32(MPU_IPU1_RAM, 0x10000);
        HW_WR_REG32(MPU_IPU1_RAM + 0x4U, EntryPoint);
    }

    if ((sblBuildMode == SBL_BUILD_MODE_DEV) || (EntryPoint != 0))
    {
        SBL_PRINTF(TRACE_MEDIUM, "\n Bringout of reset \n");

        /*Bring-out of Reset - CPU1*/
        retVal = PMHALResetRelease(PMHAL_PRCM_RG_IPU1_CPU1_RST,
                                   PM_TIMEOUT_INFINITE);
        if (0 != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n IPU1_CPU1_RST Release Failed \n");
        }

        /*Check the Status of IPU1 Module mode*/
        do
        {
            PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_IPU1, &sIdleState);
        }
        while (sIdleState != PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL);
    }
}

#if defined (TDA2XX_BUILD)
/**
 * \brief           IPU2_Clk_Enable is PRCM function for IPU2. Configure the
 *      module to auto & force-wake-up the clock domain
 *
 *
 * \param           None.
 *
 * \return      error status.If error has occured it returns a non zero value.
 *      If no error has occured then return status will be zero.
 *
 **/
int32_t IPU2_Clk_Enable(void)
{
    int32_t retval = 0;

    SBL_PRINTF(TRACE_LOW, __func__);

    /*Enable the module - ipu2*/
    retval = PMHALModuleModeSet(PMHAL_PRCM_MOD_IPU2,
                                PMHAL_PRCM_MODULE_MODE_AUTO,
                                PM_TIMEOUT_INFINITE);

    if (retval != 0)
    {
        SBL_PRINTF(TRACE_HIGH, "\nEnable IPU2 Module - Error \n");
    }
    else
    {
        /*Force Wake-up clock domain*/
        retval = PMHALCMSetCdClockMode(PMHAL_PRCM_CD_IPU2,
                                       PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                       PM_TIMEOUT_INFINITE);
        if (retval != 0)
        {
            SBL_PRINTF(TRACE_LOW, "\nEnable IPU2 CLK Enable - Error \n");
        }
    }
    return retval;
}

/**
 * \brief             IPU2_SystemReset function assert reset(CPU0 & IPU2 SS) ,
 *        configure AMMU, set the entry point & release the CPU0
 *        from reset.
 *
 *
 * \param[in]  EntryPoint - CPU entry location on reset
 *
 * \return      None.
 *
 **/
void IPU2_SystemReset(void)
{
    int32_t  retVal  = 0;
    uint32_t retStat = 0U;
    SBL_PRINTF(TRACE_LOW, __func__);
    SBL_PRINTF(TRACE_LOW, "\n IPU2 SystemReset\n");

    /*Assert the IPU2 - CPU0,CPU1 & MMU,cache*/
    retVal = PMHALResetAssert(PMHAL_PRCM_RG_IPU2_CPU1_RST);
    if (0 != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n IPU2_CPU1_RST Assert Failed \n");
    }
    retVal = PMHALResetAssert(PMHAL_PRCM_RG_IPU2_CPU0_RST);
    if (0 != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n IPU2_CPU0_RST Assert Failed \n");
    }
    retVal = PMHALResetAssert(PMHAL_PRCM_RG_IPU2_RST);
    if (0 != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n IPU2_RST Assert Failed \n");
    }

    /*Check the Reset status & clear*/
    retVal = PMHALResetGetStatus(PMHAL_PRCM_RG_IPU2_CPU1_RST, &retStat);
    if (0 != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n IPU2_CPU1_RST get status Failed \n");
    }
    if (retStat == 0x1U)
    {
        retVal = PMHALResetClearStatus(PMHAL_PRCM_RG_IPU2_CPU1_RST);
        if (0 != retVal)
        {
            SBL_PRINTF(TRACE_HIGH,
                       "\n IPU2_CPU1_RST clear status Failed \n");
        }
        retStat = 0U;
    }
    retVal = PMHALResetGetStatus(PMHAL_PRCM_RG_IPU2_CPU0_RST, &retStat);
    if (0 != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n IPU2_CPU0_RST get status Failed \n");
    }
    if (retStat == 0x1U)
    {
        retVal = PMHALResetClearStatus(PMHAL_PRCM_RG_IPU2_CPU0_RST);
        if (0 != retVal)
        {
            SBL_PRINTF(TRACE_HIGH,
                       "\n IPU2_CPU0_RST clear status Failed \n");
        }
        retStat = 0U;
    }
    retVal = PMHALResetGetStatus(PMHAL_PRCM_RG_IPU2_RST, &retStat);
    if (0 != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n IPU2_RST get status Failed \n");
    }
    if (retStat == 0x1U)
    {
        retVal = PMHALResetClearStatus(PMHAL_PRCM_RG_IPU2_RST);
        if (0 != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n IPU2_RST clear status Failed \n");
        }
        retStat = 0U;
    }

    /*Configure the boot translation page of IPU2 to 0x55020000 -
     *IPU_RAM*/

    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_CORTEX_M4_MMUADDRLOGICTR, 0x00000);
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_CORTEX_M4_MMUADDRTRANSLTR, 0x55020);

    /*Bring the MMU & cache out of reset*/
    retVal = PMHALResetRelease(PMHAL_PRCM_RG_IPU2_RST,
                               PM_TIMEOUT_INFINITE);
    if (0 != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n IPU2_RST Release Failed \n");
    }
}

/**
 * \brief      IPU2_AMMU_Config function configure the IPU2 AMMU. Add
 *             entires to access DDR, L4Per1,L4Per2 & L4Per3,
 *             L3 RAM & IRAM
 *
 * \param      None.
 *
 * \return      None.
 *
 *
 **/
void IPU2_AMMU_Config(void)
{
    /*Large Page Translations */
    /* Logical Address */
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE, 0x40000000);
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x04U, 0x80000000U);
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x08U, 0xa0000000U);
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x0CU, 0x60000000);

    /* Physical Address */
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x20U, 0x40000000);
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x24U, 0x80000000U);
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x28U, 0xa0000000U);
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x2CU, 0x60000000);

    /* Policy Register */
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x40U, 0x00000007);
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x44U, 0x000B0007);
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x48U, 0x00020007);
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x4CU, 0x00020007);

    /*Medium Page*/
    /* Logical Address */
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x60U, 0x00300000);
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x64U, 0x00400000);

    /* Physical Address */
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0xA0U, 0x40300000);
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0xA4U, 0x40400000);

    /* Policy Register */
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0xE0U, 0x00000007);
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0xE4U, 0x00020007);

    /*Small Page*/
    /* Logical Address */
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x120U, 0x00000000);
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x124U, 0x20000000);
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x128U, 0x00004000);
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x12CU, 0x00008000);
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x130U, 0x0000C000);

    /* Physical Address */
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x1A0U, 0x55020000);
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x1A4U, 0x55020000);
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x1A8U, 0x55024000);
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x1ACU, 0x55028000);
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x1B0U, 0x5502C000);

    /* Policy Register */
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x220U, 0x0001000B);
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x224U, 0x0000000B);
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x228U, 0x00010007);
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x22CU, 0x00000007);
    HW_WR_REG32(SOC_IPU2_TARGET_UNICACHE_MMU_BASE + 0x230U, 0x00000007);
}

/**
 * \brief      IPU2_CPU0_BringUp function assert reset(CPU0 & IPU2 SS)
 *             configure AMMU, set the entry point & release the CPU0
 *             from reset.
 *
 *
 * \param[in]  EntryPoint - CPU entry location on reset
 *
 * \return      None.
 *
 **/
void IPU2_CPU0_BringUp(uint32_t EntryPoint, uint32_t sblBuildMode)
{
    int32_t retVal = 0;
    pmhalPrcmModuleSIdleState_t sIdleState;

    SBL_PRINTF(TRACE_LOW, __func__);
    SBL_PRINTF(TRACE_LOW, "\nSet Entry Point\n");

    /*Set the Entry point*/
    if (EntryPoint == 0)
    {
        HW_WR_REG32(MPU_IPU2_RAM, 0x10000);
        HW_WR_REG32(MPU_IPU2_RAM + 0x4U, 0x9);
        HW_WR_REG32(MPU_IPU2_RAM + 0x8U, 0xE7FEE7FEU);
    }
    else
    {
        HW_WR_REG32(MPU_IPU2_RAM, 0x10000);
        HW_WR_REG32(MPU_IPU2_RAM + 0x4U, EntryPoint);
    }

    if ((sblBuildMode == SBL_BUILD_MODE_DEV) || (EntryPoint != 0))
    {
        SBL_PRINTF(TRACE_MEDIUM, "\nBringout of reset \n");

        /*Bring-out of Reset - CPU0*/
        retVal = PMHALResetRelease(PMHAL_PRCM_RG_IPU2_CPU0_RST,
                                   PM_TIMEOUT_INFINITE);
        if (0 != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n IPU2_CPU0_RST Release Failed \n");
        }

        /*Check the Status of IPU1 Module mode*/
        do
        {
            PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_IPU2, &sIdleState);
        }
        while (sIdleState != PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL);
    }
}

/**
 * \brief      IPU2_CPU1_BringUp function assert reset(CPU1), set the
 *             entry point & release the CPU1
 *             from reset.
 *
 *
 * \param[in]  EntryPoint - CPU entry location on reset
 *
 * \return      None.
 *
 **/
void IPU2_CPU1_BringUp(uint32_t EntryPoint, uint32_t sblBuildMode)
{
    int32_t  retVal  = 0;
    uint32_t retStat = 0U;

    pmhalPrcmModuleSIdleState_t sIdleState;

    SBL_PRINTF(TRACE_LOW, __func__);
    SBL_PRINTF(TRACE_LOW, "\nSet Entry Point\n");

    /*Assert the CPU2 Reset*/
    retVal = PMHALResetAssert(PMHAL_PRCM_RG_IPU2_CPU1_RST);
    if (0 != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n IPU2_CPU1_RST Assert Failed \n");
    }

    /*Check the reset status & clear*/
    retVal = PMHALResetGetStatus(PMHAL_PRCM_RG_IPU2_CPU1_RST,
                                 &retStat);
    if (0 != retVal)
    {
        SBL_PRINTF(TRACE_HIGH,
                   "\n IPU2_CPU0_RST get status Failed \n");
    }
    if (retStat == 0x1U)
    {
        retVal = PMHALResetClearStatus(PMHAL_PRCM_RG_IPU2_CPU1_RST);
        if (0 != retVal)
        {
            SBL_PRINTF(TRACE_HIGH,
                       "\n IPU2_CPU1_RST clear status Failed \n");
        }
    }

    /*Set the Entry point*/
    if (EntryPoint == 0)
    {
        HW_WR_REG32(MPU_IPU2_RAM, 0x10000);
        HW_WR_REG32(MPU_IPU2_RAM + 0x4U, 0x9);
        HW_WR_REG32(MPU_IPU2_RAM + 0x8U, 0xE7FEE7FEU);
    }
    else
    {
        HW_WR_REG32(MPU_IPU2_RAM, 0x10000);
        HW_WR_REG32(MPU_IPU2_RAM + 0x4U, EntryPoint);
    }

    if ((sblBuildMode == SBL_BUILD_MODE_DEV) || (EntryPoint != 0))
    {
        SBL_PRINTF(TRACE_MEDIUM, "\n Bringout of reset \n");

        /*Bring-out of Reset - CPU1 */
        retVal = PMHALResetRelease(PMHAL_PRCM_RG_IPU2_CPU1_RST,
                                   PM_TIMEOUT_INFINITE);
        if (0 != retVal)
        {
            SBL_PRINTF(TRACE_HIGH,
                       "\n IPU2_CPU1_RST Release Failed \n");
        }

        /*Check the Status of IPU2 Module mode*/
        do
        {
            PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_IPU2, &sIdleState);
        }
        while (sIdleState != PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL);
    }
}

#endif

/**
 * \brief      DSP1_Clk_Enable is PRCM function for DSP1. Configure the
 *             module to auto & force-wake-up the clock domain
 *
 *
 * \param      None.
 *
 * \return     error status.If error has occured it returns a non zero value.
 *             If no error has occured then return status will be zero.
 *
 **/
int32_t DSP1_Clk_Enable(void)
{
    int32_t retval = 0;

    SBL_PRINTF(TRACE_LOW, __func__);

    /*Enable the module - dsp1*/
    retval = PMHALModuleModeSet(PMHAL_PRCM_MOD_DSP1,
                                PMHAL_PRCM_MODULE_MODE_AUTO,
                                PM_TIMEOUT_INFINITE);

    if (retval != 0)
    {
        SBL_PRINTF(TRACE_HIGH,
                   "\nEnable DSP1 Module - Error \n");
    }
    else
    {
        /* Force Wake-up clock domain dsp1 */
        retval = PMHALCMSetCdClockMode(PMHAL_PRCM_CD_DSP1,
                                       PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                       PM_TIMEOUT_INFINITE);

        SBL_PRINTF(TRACE_LOW,
                   "\nEnable DSP1 CLK Enable - completed \n");
    }
    return retval;
}

/**
 * \brief      DSP1_BringUp function assert reset(CPU & DSP SS) , set
 *             the entry point & release the CPU
 *             from reset.
 *
 * \param[in]  EntryPoint - CPU entry location on reset
 *
 * \return      None.
 *
 **/
void DSP1_BringUp(uint32_t EntryPoint, uint32_t sblBuildMode)
{
    uint32_t idx;
    int32_t  retVal = 0;
    pmhalPrcmModuleSIdleState_t sIdleState;

    SBL_PRINTF(TRACE_LOW, __func__);
    SBL_PRINTF(TRACE_LOW, "\nSet Entry Point\n");

    /*Check the entry point 0x400 byte aligned*/
    if (EntryPoint != 0)
    {
        if ((EntryPoint & (~0xFFFFFC00U)) != 0)
        {
            SBL_PRINTF(
                TRACE_HIGH,
                "DSP1 entry point address is not aligned - application boot-up fails \n ");
            EntryPoint = 0;
        }
    }

    /*DSP L2RAM*/
    /* Set the Entry point */
    if ((EntryPoint == 0) && (SBL_BUILD_MODE_PROD == sblBuildMode))
    {
        /* Op code for the following assembly code: (This makes the DSP
         * branch
         * to address 0x200 offset from L2 RAM.)
         *   B.S2  0x800200
         *   NOP
         *   NOP
         *   NOP
         *   NOP
         *   NOP
         *   NOP
         *   NOP
         */
        uint32_t dspInstruction1[8] =
        {0x00004012, 0, 0, 0, 0, 0, 0, 0};

        /* Op code for the following assembly code. This code sets the
         * PDCCMD
         * DSP Sleep mode and then executes IDLE.
         *   MVK.L1        0,A3
         *   MVKH.S1       0x1810000,A3
         *   LDW.D1T1      *+A3[0],A3
         *   MVK.L2        0,B4
         *   MVKH.S2       0x1810000,B4
         *   NOP
         *   NOP
         *   SET.S1        A3,16,16,A3
         *   STW.D2T1      A3,*+B4[0]
         *   IDLE
         */
        uint32_t dspInstruction2[16] =
        {0x0180A358, 0x0180C0E8,
         0x018C0264,
         0x0200A35A, 0x0200C0EA,
         0x00000000,
         0x00000000, 0x018E1088,
         0x019002F4,
         0x00000000, 0x00000000,
         0x00000000,
         0x0001E000, 0x0001E000,
         0x0001E000, 0x00000000};
        HW_WR_REG32(DSP1BOOTADDR, (DSP1BOOTADDRVALUE >> 0xAU));

        for (idx = 0; idx < 8U; idx++)
        {
            HW_WR_REG32(SOC_DSP1_L2_SRAM_BASE + (4U * idx),
                        dspInstruction1[idx]);
        }

        for (idx = 0; idx < 16U; idx++)
        {
            HW_WR_REG32(SOC_DSP1_L2_SRAM_BASE + 0x200U + (4U *
                                                          idx),
                        dspInstruction2[idx]);
        }
    }
    else if ((EntryPoint == 0) && (sblBuildMode == SBL_BUILD_MODE_DEV))
    {
        HW_WR_REG32(DSP1BOOTADDR, (DSP1BOOTADDRVALUE >> 0xAU));
        for (idx = 0; idx < 8U; idx++) {
            HW_WR_REG32(SOC_DSP1_L2_SRAM_BASE + (4U * idx), 0x12); /*Write Self
                                                                    * Branch
                                                                    *Instruction*/
        }
    }
    else
    {
        HW_WR_REG32(DSP1BOOTADDR, (EntryPoint >> 0xAU));
    }

    SBL_PRINTF(TRACE_MEDIUM, "\nBringout of reset \n");

    /* Bring-out of Reset */
    retVal = PMHALResetRelease(PMHAL_PRCM_RG_DSP1_RST,
                               PM_TIMEOUT_INFINITE);
    if (0 != retVal)
    {
        SBL_PRINTF(
            TRACE_HIGH,
            "\n PMHAL_PRCM_RG_DSP1_RST Release Failed \n");
    }

    if ((EntryPoint == 0) && (SBL_BUILD_MODE_PROD == sblBuildMode))
    {
        /* The DSP at this point would have set the PWRCMD register for DSP to
         * to go to power down and executed/going to execute the IDLE
         * instruction as per the assembly instructions above. Under these
         * conditions the DSP Mstandby gets asserted. Once this is asserted the
         * hardware controlled power down sequence can be initiated by setting
         * the clock domain to HW_AUTO and the power domain request to PD_OFF.
         * Once the power domain is OFF the module can be disabled using the
         * sequence below.
         */
        PMHALModuleModeSet(PMHAL_PRCM_MOD_DSP1,
                           PMHAL_PRCM_MODULE_MODE_DISABLED,
                           PM_TIMEOUT_INFINITE);

        PMHALCMSetCdClockMode(PMHAL_PRCM_CD_DSP1,
                              PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                              PM_TIMEOUT_INFINITE);

        PMHALPdmSetPDState(PMHAL_PRCM_PD_DSP1,
                           PMHAL_PRCM_PD_STATE_OFF,
                           PM_TIMEOUT_INFINITE);
    }
    else
    {
        /* Check the Status of DSP1 Module mode */
        do
        {
            PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_DSP1, &sIdleState);
        }
        while (sIdleState != PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL);
    }
}

#ifdef TDA2XX_BUILD
/**
 * \brief       DSP2_Clk_Enable is PRCM function for DSP2. Configure the
 *              module to auto & force-wake-up the clock domain
 *
 *
 * \param       None.
 *
 * \return      error status.If error has occured it returns a non zero value.
 *              If no error has occured then return status will be zero.
 *
 **/

int32_t DSP2_Clk_Enable(void)
{
    int32_t retval = 0;

    SBL_PRINTF(TRACE_LOW, __func__);

    /* Enable the module - dsp2 */
    retval = PMHALModuleModeSet(PMHAL_PRCM_MOD_DSP2,
                                PMHAL_PRCM_MODULE_MODE_AUTO,
                                PM_TIMEOUT_INFINITE);

    if (retval != 0)
    {
        SBL_PRINTF(TRACE_HIGH,
                   "\nEnable DSP2 Module - Error \n");
    }
    else
    {
        /* Force Wake-up clock domain dsp1 */
        retval = PMHALCMSetCdClockMode(PMHAL_PRCM_CD_DSP2,
                                       PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                       PM_TIMEOUT_INFINITE);

        SBL_PRINTF(TRACE_LOW,
                   "\nEnable DSP2 CLK Enable - completed \n");
    }
    return retval;
}

/**
 * \brief   DSP2_BringUp function assert reset(CPU & DSP SS) , set
 *          the entry point & release the CPU
 *          from reset.
 *
 * \param[in]  EntryPoint - CPU entry location on reset
 *
 * \return      None.
 *
 **/
void DSP2_BringUp(uint32_t EntryPoint, uint32_t sblBuildMode)
{
    uint32_t idx;

    int32_t  retVal = 0;

    pmhalPrcmModuleSIdleState_t sIdleState;

    SBL_PRINTF(TRACE_LOW, __func__);
    SBL_PRINTF(TRACE_LOW, "\nSet Entry Point\n");

    /*Check the entry point 0x400 byte aligned*/
    if (EntryPoint != 0)
    {
        if ((EntryPoint & (~0xFFFFFC00U)) != 0)
        {
            SBL_PRINTF(
                TRACE_HIGH,
                "DSP2 entry point address is not aligned - application boot-up fails \n ");
            EntryPoint = 0;
        }
    }

    /*DSP L2RAM*/
    /*Set the Entry point*/
    if ((EntryPoint == 0) && (SBL_BUILD_MODE_PROD == sblBuildMode))
    {
        /* Op code for the following assembly code: (This makes the DSP
         * branch
         * to address 0x200 offset from L2 RAM.)
         *   B.S2  0x800200
         *   NOP
         *   NOP
         *   NOP
         *   NOP
         *   NOP
         *   NOP
         *   NOP
         */
        uint32_t dspInstruction1[8] =
        {0x00004012, 0, 0, 0, 0, 0, 0, 0};

        /* Op code for the following assembly code. This code sets the
         * PDCCMD
         * DSP Sleep mode and then executes IDLE.
         *   MVK.L1        0,A3
         *   MVKH.S1       0x1810000,A3
         *   LDW.D1T1      *+A3[0],A3
         *   MVK.L2        0,B4
         *   MVKH.S2       0x1810000,B4
         *   NOP
         *   NOP
         *   SET.S1        A3,16,16,A3
         *   STW.D2T1      A3,*+B4[0]
         *   IDLE
         */
        uint32_t dspInstruction2[16] =
        {0x0180A358, 0x0180C0E8,
         0x018C0264,
         0x0200A35A, 0x0200C0EA,
         0x00000000,
         0x00000000, 0x018E1088,
         0x019002F4,
         0x00000000, 0x00000000,
         0x00000000,
         0x0001E000, 0x0001E000,
         0x0001E000, 0x00000000};
        HW_WR_REG32(DSP2BOOTADDR, (DSP2BOOTADDRVALUE >> 0xAU));

        for (idx = 0; idx < 8U; idx++)
        {
            HW_WR_REG32(SOC_DSP2_L2_SRAM_BASE + (4U *
                                                 idx), dspInstruction1[idx]);
        }

        for (idx = 0; idx < 16U; idx++)
        {
            HW_WR_REG32(SOC_DSP2_L2_SRAM_BASE + 0x200U + (4U *
                                                          idx),
                        dspInstruction2[idx]);
        }
    }
    else if ((EntryPoint == 0) && (sblBuildMode == SBL_BUILD_MODE_DEV))
    {
        HW_WR_REG32(DSP2BOOTADDR, (DSP2BOOTADDRVALUE >> 0xAU));
        for (idx = 0; idx < 8U; idx++) {
            HW_WR_REG32(SOC_DSP2_L2_SRAM_BASE + (4U * idx), 0x12); /*Write Self
                                                                    * Branch
                                                                    *Instruction*/
        }
    }
    else
    {
        HW_WR_REG32(DSP2BOOTADDR, (EntryPoint >> 0xAU));
    }

    SBL_PRINTF(TRACE_MEDIUM, "\nBringout of reset \n");

    /*Bring-out of Reset - CPU , MMU & Cache*/
    retVal = PMHALResetRelease(PMHAL_PRCM_RG_DSP2_RST,
                               PM_TIMEOUT_INFINITE);
    if (0 != retVal)
    {
        SBL_PRINTF(
            TRACE_HIGH,
            "\n PMHAL_PRCM_RG_DSP2_RST Release Failed \n");
    }

    if ((EntryPoint == 0) && (SBL_BUILD_MODE_PROD == sblBuildMode))
    {
        /* The DSP at this point would have set the PWRCMD register for DSP to
         * to go to power down and executed/going to execute the IDLE
         * instruction as per the assembly instructions above. Under these
         * conditions the DSP Mstandby gets asserted. Once this is asserted the
         * hardware controlled power down sequence can be initiated by setting
         * the clock domain to HW_AUTO and the power domain request to PD_OFF.
         * Once the power domain is OFF the module can be disabled using the
         * sequence below.
         */
        PMHALModuleModeSet(PMHAL_PRCM_MOD_DSP2,
                           PMHAL_PRCM_MODULE_MODE_DISABLED,
                           PM_TIMEOUT_INFINITE);
        PMHALCMSetCdClockMode(PMHAL_PRCM_CD_DSP2,
                              PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                              PM_TIMEOUT_INFINITE);
        PMHALPdmSetPDState(PMHAL_PRCM_PD_DSP2,
                           PMHAL_PRCM_PD_STATE_OFF,
                           PM_TIMEOUT_INFINITE);
    }
    else
    {
        /*Check the Status of module mode*/
        do
        {
            PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_DSP2, &sIdleState);
        }
        while (sIdleState != PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL);
    }
}

/**
 * \brief    EVE1_Clk_Enable is PRCM function for EVE1. Configure the
 *            module to auto & force-wake-up the clock domain
 *
 *
 * \param     None.
 *
 * \return   error status.If error has occured it returns a non zero value.
 *                      If no error has occured then return status will be zero.
 *
 **/
int32_t EVE1_Clk_Enable(void)
{
    int32_t retval = 0;

    SBL_PRINTF(TRACE_LOW, __func__);

    /* Enable the module - eve1 */
    retval = PMHALModuleModeSet(PMHAL_PRCM_MOD_EVE1,
                                PMHAL_PRCM_MODULE_MODE_AUTO,
                                PM_TIMEOUT_INFINITE);

    if (retval != 0)
    {
        SBL_PRINTF(TRACE_HIGH,
                   "\nEnable EVE1 Module - Error \n");
    }
    else
    {
        /* Force Wake-up clock domain dsp1 */
        retval = PMHALCMSetCdClockMode(PMHAL_PRCM_CD_EVE1,
                                       PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                       PM_TIMEOUT_INFINITE);

        SBL_PRINTF(TRACE_LOW,
                   "\nEnable EVE1 CLK Enable - completed \n");
    }
    return retval;
}

/**
 * \brief        EVE_SYSMMU_Config function configure the EVE MMU0. Add
 *               entires to access entry location page, L4Per1,L4Per2 & L4Per3,
 *               & Internal memory buffers. Remaining DDR location should
 *               be taken care in the application layer.
 *
 * \param[in]           eve_mmu_base_address - Base address of EVEx MMU0.
 * \param[in]           eve_entryPoint - EVE start-up entry location
 *
 *
 * \return      None.
 **/

void EVE_SYSMMU_Config(uint32_t eve_mmu_base_address,
                       uint32_t eve_entryPoint)
{
    MMU_TlbEntry_t mmu_entry;
    uint32_t       entrypoint_page;

    SBL_PRINTF(TRACE_LOW, __func__);

    /* Derive Entry point page for the given entry point*/
    entrypoint_page = eve_entryPoint & (0xFF000000U);

    /* Configure MMU Tlb Entry for Vector table as 1MB section*/
    /* EVE starts executing from virtual address 0x0 when brought out of reset.
     * When SBL maps the 0x0 to entrypoint_page, it assumes that the vector
     * table is present at entrypoint_page.
     * E.g. If entry point is 0x81F62648, entrypoint_page is calculated as
     * 0x81000000 and application image should be built in a way that vector
     * table is present at this address.
     */
    mmu_entry.phyAddr        = entrypoint_page;
    mmu_entry.virtAddr       = 0x00000000;
    mmu_entry.valid          = TRUE;
    mmu_entry.pageSize       = MMU_Section_Size;
    mmu_entry.endianness     = MMU_Little_Endian;
    mmu_entry.elementSize    = MMU_NoTranslation_ElementSize;
    mmu_entry.tlbElementSize = MMU_CPU_ElementSize;
    mmu_entry.preserve       = TRUE;
    MMUTlbEntrySet(eve_mmu_base_address, (uint32_t) 1, &mmu_entry);

    /* Configure MMU Tlb Entry for code & data section  as 16MB
     *supersection*/
    mmu_entry.phyAddr        = entrypoint_page;
    mmu_entry.virtAddr       = entrypoint_page;
    mmu_entry.valid          = TRUE;
    mmu_entry.pageSize       = MMU_SuperSection_Size;
    mmu_entry.endianness     = MMU_Little_Endian;
    mmu_entry.elementSize    = MMU_NoTranslation_ElementSize;
    mmu_entry.tlbElementSize = MMU_CPU_ElementSize;
    mmu_entry.preserve       = TRUE;
    MMUTlbEntrySet(eve_mmu_base_address, (uint32_t) 2, &mmu_entry);

    /* Configure MMU Tlb Entry for EVE internal memory  as 16MB
     *supersection*/
    mmu_entry.phyAddr        = SOC_EVE_DMEM_BASE;
    mmu_entry.virtAddr       = SOC_EVE_DMEM_BASE;
    mmu_entry.valid          = TRUE;
    mmu_entry.pageSize       = MMU_SuperSection_Size;
    mmu_entry.endianness     = MMU_Little_Endian;
    mmu_entry.elementSize    = MMU_NoTranslation_ElementSize;
    mmu_entry.tlbElementSize = MMU_CPU_ElementSize;
    mmu_entry.preserve       = TRUE;
    MMUTlbEntrySet(eve_mmu_base_address, (uint32_t) 3, &mmu_entry);

    /* Configure MMU Tlb Entry for L4_Per1,L4_Per2,L4_Per3  as 16MB
     *supersection*/
    mmu_entry.phyAddr        = SOC_L4_PER_AP_BASE;
    mmu_entry.virtAddr       = SOC_L4_PER_AP_BASE;
    mmu_entry.valid          = TRUE;
    mmu_entry.pageSize       = MMU_SuperSection_Size;
    mmu_entry.endianness     = MMU_Little_Endian;
    mmu_entry.elementSize    = MMU_NoTranslation_ElementSize;
    mmu_entry.tlbElementSize = MMU_CPU_ElementSize;
    mmu_entry.preserve       = TRUE;
    MMUTlbEntrySet(eve_mmu_base_address, (uint32_t) 4, &mmu_entry);

    /* Enable MMU */
    MMUEnable(eve_mmu_base_address);

    SBL_PRINTF(TRACE_LOW,
               "\n EVE MMU configuration completed \n");
}

/**
 * \brief      EVE1_BringUp function assert reset(CPU & EVE SS), set
 *             the entry point & release the CPU
 *             from reset.
 *
 *
 * \param[in]  EntryPoint - CPU entry location on reset
 *
 * \return      None.
 *
 **/
void EVE1_BringUp(uint32_t EntryPoint, uint32_t sblBuildMode)
{
    int32_t retVal = 0;
    pmhalPrcmModuleSIdleState_t sIdleState;

    SBL_PRINTF(TRACE_LOW, __func__);
    SBL_PRINTF(TRACE_LOW, "\nSet Entry Point\n");

    if (EntryPoint != 0)
    {
        /*EVE_MMU0 config & set the entry point*/
        EVE_SYSMMU_Config(SOC_EVE1_MMU0_BASE, EntryPoint);
    }
    else
    {
        /*Assuming 0x80000000 not in use*/
        HW_WR_REG32(0x80000000U, 0x80000100U); /* Reset vector points to
                                                *0x8000_0100*/
        HW_WR_REG32(0x80000100U, 0x0000037F);  /* IDLE; opcode for ARP32 */
        HW_WR_REG32(0x80000104U, 0x0000037F);  /* IDLE; opcode for ARP32 */
        HW_WR_REG32(0x80000108U, 0x0000037F);  /* IDLE; opcode for ARP32 */
        HW_WR_REG32(0x8000010CU, 0x0000037F);  /* IDLE; opcode for ARP32 */
        /*EVE_MMU0 config & set the entry point*/
        EVE_SYSMMU_Config(SOC_EVE1_MMU0_BASE, 0x80000000U);
    }

    SBL_PRINTF(TRACE_MEDIUM, "\nBringout of reset \n");

    /* Bring-out of Reset*/
    retVal = PMHALResetRelease(PMHAL_PRCM_RG_EVE1_CPU_RST,
                               PM_TIMEOUT_INFINITE);
    if (0 != retVal)
    {
        SBL_PRINTF(
            TRACE_HIGH,
            "\n PMHAL_PRCM_RG_EVE1_CPU_RST Release Failed \n");
    }

    if ((EntryPoint == 0) && (SBL_BUILD_MODE_PROD == sblBuildMode))
    {
        /* Power Down the EVE power domain */

        /* Force Idle the EVE EDMA TPTC0 and TPTC1 */
        HW_WR_REG32(SOC_EVE1_TPTC0_BASE + 0x10U, 0);
        HW_WR_REG32(SOC_EVE1_TPTC1_BASE + 0x10U, 0);

        PMHALModuleModeSet(PMHAL_PRCM_MOD_EVE1,
                           PMHAL_PRCM_MODULE_MODE_DISABLED,
                           PM_TIMEOUT_INFINITE);

        PMHALCMSetCdClockMode(PMHAL_PRCM_CD_EVE1,
                              PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                              PM_TIMEOUT_INFINITE);

        PMHALPdmSetPDState(PMHAL_PRCM_PD_EVE1,
                           PMHAL_PRCM_PD_STATE_OFF,
                           PM_TIMEOUT_INFINITE);
    }
    else
    {
        /*Check the Status of EVE Module mode*/
        do
        {
            PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_EVE1, &sIdleState);
        }
        while (sIdleState != PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL);
    }
}

/**
 * \brief         EVE2_Clk_Enable is PRCM function for EVE1. Configure the
 *                module to auto & force-wake-up the clock domain
 *
 *
 * \param         None.
 *
 * \return        error status.If error has occured it returns a non zero value.
 *                If no error has occured then return status will be zero.
 *
 **/
int32_t EVE2_Clk_Enable(void)
{
    int32_t retval = 0;

    SBL_PRINTF(TRACE_LOW, __func__);

    /*Enable the module - EVE2*/
    retval = PMHALModuleModeSet(PMHAL_PRCM_MOD_EVE2,
                                PMHAL_PRCM_MODULE_MODE_AUTO,
                                PM_TIMEOUT_INFINITE);

    if (retval != 0)
    {
        SBL_PRINTF(TRACE_HIGH,
                   "\nEnable EVE2 Module - Error \n");
    }
    else
    {
        /*Force Wake-up clock domain dsp1*/
        retval = PMHALCMSetCdClockMode(PMHAL_PRCM_CD_EVE2,
                                       PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                       PM_TIMEOUT_INFINITE);

        SBL_PRINTF(TRACE_LOW,
                   "\nEnable EVE2 CLK Enable - completed \n");
    }
    return retval;
}

/**
 * \brief       EVE2_BringUp function assert reset(CPU & EVE SS), set
 *              the entry point & release the CPU
 *              from reset.
 *
 *
 * \param[in]   EntryPoint - CPU entry location on reset
 *
 * \return      None.
 *
 **/
void EVE2_BringUp(uint32_t EntryPoint, uint32_t sblBuildMode)
{
    int32_t retVal = 0;
    pmhalPrcmModuleSIdleState_t sIdleState;

    SBL_PRINTF(TRACE_LOW, __func__);
    SBL_PRINTF(TRACE_LOW, "\nSet Entry Point\n");

    if (EntryPoint != 0)
    {
        /*EVE_MMU0 config & set the entry point*/
        EVE_SYSMMU_Config(SOC_EVE2_MMU0_BASE, EntryPoint);
    }
    else
    {
        /*Assuming 0x80000000 not in use*/
        HW_WR_REG32(0x80000000U, 0x80000100U); /* Reset vector points to
                                                *0x8000_0100*/
        HW_WR_REG32(0x80000100U, 0x0000037F);  /* IDLE; opcode for ARP32 */
        HW_WR_REG32(0x80000104U, 0x0000037F);  /* IDLE; opcode for ARP32 */
        HW_WR_REG32(0x80000108U, 0x0000037F);  /* IDLE; opcode for ARP32 */
        HW_WR_REG32(0x8000010CU, 0x0000037F);  /* IDLE; opcode for ARP32 */
        /*EVE_MMU0 config & set the entry point*/
        EVE_SYSMMU_Config(SOC_EVE2_MMU0_BASE, 0x80000000U);
    }

    SBL_PRINTF(TRACE_MEDIUM, "\nBringout of reset \n");

    /* Bring-out of Reset*/
    retVal = PMHALResetRelease(PMHAL_PRCM_RG_EVE2_CPU_RST,
                               PM_TIMEOUT_INFINITE);
    if (0 != retVal)
    {
        SBL_PRINTF(
            TRACE_HIGH,
            "\n PMHAL_PRCM_RG_EVE2_CPU_RST Release Failed \n");
    }

    if ((EntryPoint == 0) && (SBL_BUILD_MODE_PROD == sblBuildMode))
    {
        /* Power Down the EVE power domain */

        /* Force Idle the EVE EDMA TPTC0 and TPTC1 */
        HW_WR_REG32(SOC_EVE2_TPTC0_BASE + 0x10U, 0);
        HW_WR_REG32(SOC_EVE2_TPTC1_BASE + 0x10U, 0);

        PMHALModuleModeSet(PMHAL_PRCM_MOD_EVE2,
                           PMHAL_PRCM_MODULE_MODE_DISABLED,
                           PM_TIMEOUT_INFINITE);

        PMHALCMSetCdClockMode(PMHAL_PRCM_CD_EVE2,
                              PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                              PM_TIMEOUT_INFINITE);

        PMHALPdmSetPDState(PMHAL_PRCM_PD_EVE2,
                           PMHAL_PRCM_PD_STATE_OFF,
                           PM_TIMEOUT_INFINITE);
    }
    else
    {
        /* Check the Status of EVE Module mode*/
        do
        {
            PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_EVE2, &sIdleState);
        }
        while (sIdleState != PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL);
    }
}

/**
 * \brief    EVE3_Clk_Enable is PRCM function for EVE1. Configure the
 *           module to auto & force-wake-up the clock domain
 *
 *
 * \param    None.
 *
 * \return   error status.If error has occured it returns a non zero value.
 *           If no error has occured then return status will be zero.
 *
 **/
int32_t EVE3_Clk_Enable(void)
{
    int32_t retval = 0;

    SBL_PRINTF(TRACE_LOW, __func__);

    /*Enable the module - EVE3*/
    retval = PMHALModuleModeSet(PMHAL_PRCM_MOD_EVE3,
                                PMHAL_PRCM_MODULE_MODE_AUTO,
                                PM_TIMEOUT_INFINITE);

    if (retval != 0)
    {
        SBL_PRINTF(TRACE_HIGH,
                   "\nEnable EVE3 Module - Error \n");
    }
    else
    {
        /* Force Wake-up clock domain EVE3 */
        retval = PMHALCMSetCdClockMode(PMHAL_PRCM_CD_EVE3,
                                       PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                       PM_TIMEOUT_INFINITE);

        SBL_PRINTF(TRACE_LOW,
                   "\nEnable EVE3 CLK Enable - completed \n");
    }
    return retval;
}

/**
 * \brief         EVE3_BringUp function assert reset(CPU & EVE SS), set
 *    the entry point & release the CPU
 *    from reset.
 *
 *
 * \param[in]  EntryPoint - CPU entry location on reset
 *
 * \return      None.
 *
 **/
void EVE3_BringUp(uint32_t EntryPoint, uint32_t sblBuildMode)
{
    int32_t retVal = 0;
    pmhalPrcmModuleSIdleState_t sIdleState;

    SBL_PRINTF(TRACE_LOW, __func__);
    SBL_PRINTF(TRACE_LOW, "\nSet Entry Point\n");

    if (EntryPoint != 0)
    {
        /*EVE_MMU0 config & set the entry point*/
        EVE_SYSMMU_Config(SOC_EVE3_MMU0_BASE, EntryPoint);
    }
    else
    {
        /*Assuming 0x80000000 not in use*/
        HW_WR_REG32(0x80000000U, 0x80000100U); /* Reset vector points to
                                                *0x8000_0100*/
        HW_WR_REG32(0x80000100U, 0x0000037F);  /* IDLE; opcode for ARP32 */
        HW_WR_REG32(0x80000104U, 0x0000037F);  /* IDLE; opcode for ARP32 */
        HW_WR_REG32(0x80000108U, 0x0000037F);  /* IDLE; opcode for ARP32 */
        HW_WR_REG32(0x8000010CU, 0x0000037F);  /* IDLE; opcode for ARP32 */
        /*EVE_MMU0 config & set the entry point*/
        EVE_SYSMMU_Config(SOC_EVE3_MMU0_BASE, 0x80000000U);
    }

    SBL_PRINTF(TRACE_MEDIUM, "\nBringout of reset \n");

    /*Bring-out of Reset*/
    retVal = PMHALResetRelease(PMHAL_PRCM_RG_EVE3_CPU_RST,
                               PM_TIMEOUT_INFINITE);
    if (0 != retVal)
    {
        SBL_PRINTF(
            TRACE_HIGH,
            "\n PMHAL_PRCM_RG_EVE3_CPU_RST Release Failed \n");
    }

    if ((EntryPoint == 0) && (SBL_BUILD_MODE_PROD == sblBuildMode))
    {
        /* Power Down the EVE power domain */

        /* Force Idle the EVE EDMA TPTC0 and TPTC1 */
        HW_WR_REG32(SOC_EVE3_TPTC0_BASE + 0x10U, 0);
        HW_WR_REG32(SOC_EVE3_TPTC1_BASE + 0x10U, 0);

        PMHALModuleModeSet(PMHAL_PRCM_MOD_EVE3,
                           PMHAL_PRCM_MODULE_MODE_DISABLED,
                           PM_TIMEOUT_INFINITE);

        PMHALCMSetCdClockMode(PMHAL_PRCM_CD_EVE3,
                              PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                              PM_TIMEOUT_INFINITE);

        PMHALPdmSetPDState(PMHAL_PRCM_PD_EVE3,
                           PMHAL_PRCM_PD_STATE_OFF,
                           PM_TIMEOUT_INFINITE);
    }
    else
    {
        /*Check the Status of EVE Module mode*/
        do
        {
            PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_EVE3, &sIdleState);
        }
        while (sIdleState != PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL);
    }
}

/**
 * \brief    EVE4_Clk_Enable is PRCM function for EVE4. Configure the
 *           module to auto & force-wake-up the clock domain
 *
 * \param    None.
 *
 * \return   error status.If error has occured it returns a non zero value.
 *           If no error has occured then return status will be zero.
 *
 **/
int32_t EVE4_Clk_Enable(void)
{
    int32_t retval = 0;

    SBL_PRINTF(TRACE_LOW, __func__);

    /* Enable the module - eve4 */
    retval = PMHALModuleModeSet(PMHAL_PRCM_MOD_EVE4,
                                PMHAL_PRCM_MODULE_MODE_AUTO,
                                PM_TIMEOUT_INFINITE);

    if (retval != 0)
    {
        SBL_PRINTF(TRACE_HIGH,
                   "\nEnable EVE4 Module - Error \n");
    }
    else
    {
        /* Force Wake-up clock domain dsp1 */
        retval = PMHALCMSetCdClockMode(PMHAL_PRCM_CD_EVE4,
                                       PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                       PM_TIMEOUT_INFINITE);

        SBL_PRINTF(TRACE_LOW,
                   "\nEnable EVE4 CLK Enable - completed \n");
    }
    return retval;
}

/**
 * \brief   EVE4_BringUp function assert reset(CPU & EVE SS), set
 *          the entry point & release the CPU
 *          from reset.
 *
 *
 * \param[in]  EntryPoint - CPU entry location on reset
 *
 * \return      None.
 *
 **/
void EVE4_BringUp(uint32_t EntryPoint, uint32_t sblBuildMode)
{
    int32_t retVal = 0;
    pmhalPrcmModuleSIdleState_t sIdleState;

    SBL_PRINTF(TRACE_LOW, __func__);
    SBL_PRINTF(TRACE_LOW, "\nSet Entry Point\n");

    if (EntryPoint != 0)
    {
        /*EVE_MMU0 config & set the entry point*/
        EVE_SYSMMU_Config(SOC_EVE4_MMU0_BASE, EntryPoint);
    }
    else
    {
        /*Assuming 0x80000000 not in use*/
        HW_WR_REG32(0x80000000U, 0x80000100U); /* Reset vector points to
                                                *0x8000_0100*/
        HW_WR_REG32(0x80000100U, 0x0000037F);  /* IDLE; opcode for ARP32 */
        HW_WR_REG32(0x80000104U, 0x0000037F);  /* IDLE; opcode for ARP32 */
        HW_WR_REG32(0x80000108U, 0x0000037F);  /* IDLE; opcode for ARP32 */
        HW_WR_REG32(0x8000010CU, 0x0000037F);  /* IDLE; opcode for ARP32 */
        /*EVE_MMU0 config & set the entry point*/
        EVE_SYSMMU_Config(SOC_EVE4_MMU0_BASE, 0x80000000U);
    }

    SBL_PRINTF(TRACE_MEDIUM, "\nBringout of reset \n");

    /* Bring-out of Reset*/
    retVal = PMHALResetRelease(PMHAL_PRCM_RG_EVE4_CPU_RST,
                               PM_TIMEOUT_INFINITE);
    if (0 != retVal)
    {
        SBL_PRINTF(
            TRACE_HIGH,
            "\n PMHAL_PRCM_RG_EVE4_CPU_RST Release Failed \n");
    }

    if ((EntryPoint == 0) && (SBL_BUILD_MODE_PROD == sblBuildMode))
    {
        /* Power Down the EVE power domain */

        /* Force Idle the EVE EDMA TPTC0 and TPTC1 */
        HW_WR_REG32(SOC_EVE4_TPTC0_BASE + 0x10U, 0);
        HW_WR_REG32(SOC_EVE4_TPTC1_BASE + 0x10U, 0);

        PMHALModuleModeSet(PMHAL_PRCM_MOD_EVE4,
                           PMHAL_PRCM_MODULE_MODE_DISABLED,
                           PM_TIMEOUT_INFINITE);

        PMHALCMSetCdClockMode(PMHAL_PRCM_CD_EVE4,
                              PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                              PM_TIMEOUT_INFINITE);

        PMHALPdmSetPDState(PMHAL_PRCM_PD_EVE4,
                           PMHAL_PRCM_PD_STATE_OFF,
                           PM_TIMEOUT_INFINITE);
    }
    else
    {
        /*Check the Status of EVE Module mode*/
        do
        {
            PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_EVE4, &sIdleState);
        }
        while (sIdleState != PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL);
    }
}

#endif
/**
 * \brief   IVAHD_Clk_Enable is PRCM function for IVA. Configure the
 *          module to enable & force-wake-up the clock domain
 *
 *
 * \param   None.
 *
 * \return  error status.If error has occured it returns a non zero value.
 *          If no error has occured then return status will be zero.
 *
 **/
void IVAHD_Clk_Enable(void)
{
    PMHALPdmSetPDState(PMHAL_PRCM_PD_IVA,
                       PMHAL_PRCM_PD_STATE_ON_ACTIVE,
                       PM_TIMEOUT_NOWAIT);

    /* Assert the IVA Reset*/
    PMHALResetAssert(PMHAL_PRCM_RG_IVA_RST);
    PMHALResetAssert(PMHAL_PRCM_RG_IVA_SEQ1_RST);
    PMHALResetAssert(PMHAL_PRCM_RG_IVA_SEQ2_RST);

    /* Force Wake-up clock domain iva */
    PMHALCMSetCdClockMode(PMHAL_PRCM_CD_IVA,
                          PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                          PM_TIMEOUT_INFINITE);

    /* Enable the module - iva */
    PMHALModuleModeSet(PMHAL_PRCM_MOD_IVA,
                       PMHAL_PRCM_MODULE_MODE_AUTO,
                       PM_TIMEOUT_INFINITE);

    PMHALModuleModeSet(PMHAL_PRCM_MOD_SL2,
                       PMHAL_PRCM_MODULE_MODE_AUTO,
                       PM_TIMEOUT_INFINITE);
}

/**
 * \brief   IVAHD_BringUp function assert reset & release the CPU
 *          from reset.
 *
 *
 * \param[in]  EntryPoint -Dummy parameter
 *
 * \return      None.
 *
 **/
void IVAHD_BringUp(uint32_t EntryPoint, uint32_t sblBuildMode)
{
    if (EntryPoint == 0)
    {
        /* Assert the IVA */
        PMHALResetAssert(PMHAL_PRCM_RG_IVA_RST);
        PMHALResetAssert(PMHAL_PRCM_RG_IVA_SEQ1_RST);
        PMHALResetAssert(PMHAL_PRCM_RG_IVA_SEQ2_RST);

        /* Warm reset asserted for CPU1, CPU2 */
        PMHALResetRelease(PMHAL_PRCM_RG_IVA_RST, PM_TIMEOUT_INFINITE);

        /* Self branch instruction */
        HW_WR_REG32(ICONT1_ITCM, 0xEAFFFFFEU);
        HW_WR_REG32(ICONT2_ITCM, 0xEAFFFFFEU);

        /* Warm reset released for CPU1, CPU2 */
        PMHALResetRelease(PMHAL_PRCM_RG_IVA_SEQ1_RST,
                          PM_TIMEOUT_INFINITE);
        PMHALResetRelease(PMHAL_PRCM_RG_IVA_SEQ2_RST,
                          PM_TIMEOUT_INFINITE);

        if (SBL_BUILD_MODE_PROD == sblBuildMode)
        {
            PMHALModuleModeSet(PMHAL_PRCM_MOD_IVA,
                               PMHAL_PRCM_MODULE_MODE_DISABLED,
                               PM_TIMEOUT_INFINITE);

            PMHALModuleModeSet(PMHAL_PRCM_MOD_SL2,
                               PMHAL_PRCM_MODULE_MODE_DISABLED,
                               PM_TIMEOUT_INFINITE);

            PMHALCMSetCdClockMode(PMHAL_PRCM_CD_IPU2,
                                  PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                                  PM_TIMEOUT_INFINITE);

            /* Assert the IVA Reset*/
            PMHALResetAssert(PMHAL_PRCM_RG_IVA_RST);
            PMHALResetAssert(PMHAL_PRCM_RG_IVA_SEQ1_RST);
            PMHALResetAssert(PMHAL_PRCM_RG_IVA_SEQ2_RST);

            PMHALPdmSetPDState(PMHAL_PRCM_PD_IVA,
                               PMHAL_PRCM_PD_STATE_OFF,
                               PM_TIMEOUT_INFINITE);

            /* Do not keep IVA in reset to avoid higher leakage current
             * - No
             * wait as power down sequence has been initiated here.
             */
            PMHALResetRelease(PMHAL_PRCM_RG_IVA_SEQ1_RST,
                              PM_TIMEOUT_NOWAIT);
            PMHALResetRelease(PMHAL_PRCM_RG_IVA_SEQ2_RST,
                              PM_TIMEOUT_NOWAIT);
            PMHALResetRelease(PMHAL_PRCM_RG_IVA_RST,
                              PM_TIMEOUT_NOWAIT);
        }
    }
}

/**
 * \brief   slavecore_enable() - This function do the slave cores
 *          PRCM module enable & clockdomain
 *          force wake-up. Brings the slave cores system out of
 *          reset.
 *
 * \param[in]  EntryPoint -Dummy parameter
 *
 * \return      None.
 *
 **/
void slavecore_prcm_enable(void)
{
    /* Slave core wake-up*/

    /*Clock Enable CPUs*/
    IPU1_Clk_Enable();
    IPU1_SystemReset();
#ifdef TDA2XX_BUILD
    IPU2_Clk_Enable();
    IPU2_SystemReset();
#endif
    DSP1_Clk_Enable();
    CPU_SystemReset(DSP1_ID);

#ifdef TDA2XX_BUILD
    DSP2_Clk_Enable();
    CPU_SystemReset(DSP2_ID);
    EVE1_Clk_Enable();
    CPU_SystemReset(EVE1_ID);
    EVE2_Clk_Enable();
    CPU_SystemReset(EVE2_ID);
    EVE3_Clk_Enable();
    CPU_SystemReset(EVE3_ID);
    EVE4_Clk_Enable();
    CPU_SystemReset(EVE4_ID);
#endif

#ifdef ZEBU
    IVAHD_Clk_Enable();
#endif
}

void SBLIPUBringUp(uint32_t ipuId,
                   uint32_t entryPtCPU0,
                   uint32_t entryPtCPU1, uint32_t sblBuildMode)
{
    if (0U == ipuId)
    {
        /*Release the slave cores out of reset*/
        IPU1_CPU0_BringUp(entryPtCPU0, sblBuildMode);
        IPU1_CPU1_BringUp(entryPtCPU1, sblBuildMode);

        /* Cut clocks for IPU if entry point is of both cores is 0 */
        if ((0U == entryPtCPU0) && (0U == entryPtCPU1) &&
            (SBL_BUILD_MODE_PROD == sblBuildMode))
        {
            PMHALModuleModeSet(PMHAL_PRCM_MOD_IPU1,
                               PMHAL_PRCM_MODULE_MODE_DISABLED,
                               PM_TIMEOUT_INFINITE);

            PMHALCMSetCdClockMode(PMHAL_PRCM_CD_IPU1,
                                  PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                                  PM_TIMEOUT_INFINITE);

            PMHALResetRelease(PMHAL_PRCM_RG_IPU1_CPU0_RST,
                              PM_TIMEOUT_NOWAIT);
            PMHALResetRelease(PMHAL_PRCM_RG_IPU1_CPU1_RST,
                              PM_TIMEOUT_NOWAIT);
        }
    }
    else
    {
        #if defined (TDA2XX_BUILD)
        IPU2_CPU0_BringUp(entryPtCPU0, sblBuildMode);
        IPU2_CPU1_BringUp(entryPtCPU1, sblBuildMode);

        /* Cut clocks for IPU if entry point is of both cores is 0 */
        if ((0U == entryPtCPU0) && (0U == entryPtCPU1) &&
            (SBL_BUILD_MODE_PROD == sblBuildMode))
        {
            PMHALModuleModeSet(PMHAL_PRCM_MOD_IPU2,
                               PMHAL_PRCM_MODULE_MODE_DISABLED,
                               PM_TIMEOUT_INFINITE);

            PMHALCMSetCdClockMode(PMHAL_PRCM_CD_IPU2,
                                  PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                                  PM_TIMEOUT_INFINITE);

            PMHALResetRelease(PMHAL_PRCM_RG_IPU2_CPU0_RST,
                              PM_TIMEOUT_NOWAIT);
            PMHALResetRelease(PMHAL_PRCM_RG_IPU2_CPU1_RST,
                              PM_TIMEOUT_NOWAIT);
        }
        #elif defined (TDA2EX_BUILD)
        SBL_PRINTF(TRACE_HIGH, "\n Tried to configure wrong IPU \n");
        #endif
    }
}

