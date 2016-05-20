/*
 *******************************************************************************
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \file utils_idle_arp32.c
 *
 * \brief  APIs from this file are used to interface the CPU Idle functions
 *
 *         The APIs allow a user to enable CPU idle on a given processor.
 *
 * \version 0.0 (Jan 2015) : [CM] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <stdint.h>
#include <hw/hw_types.h>
#include <arp32_wugen.h>
#include "soc_defines.h"
#include "platform.h"
#include <src/utils_common/include/utils.h>
#include <src/utils_common/include/utils_idle.h>
#include <src/utils_common/include/utils_prf.h>
#include <src/links_eve/system/system_priv_eve.h>
#include <include/link_api/system_trace.h>
#include <pmhal_prcm.h>
#include <pm/pmlib/pmlib_cpuidle.h>
#include <pm/pmhal/pmhal_pdm.h>
#include <pm/pmhal/pmhal_cm.h>
#include <ti/sysbios/knl/Swi.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Idle function to be plugged into Idle task.
 *        This function executes idle instruction and puts CPU into low power
 *        state. The targeted low power state is Retention.
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_idleFxn(Void)
{
#ifdef CPU_IDLE_ENABLED
    System_EveObj *pObj;
    pObj = &gSystem_objEve;
    Uint32 key;
    key = Hwi_disable();
    ARP32_WUGEN_IRQ_Interrupt_Lookup();
    Hwi_restore(key);

    if (0U != pObj->eveIdleInitDone)
    {
        PMLIBCpuIdle(PMHAL_PRCM_PD_STATE_RETENTION);
    }
#endif
}

/**
 *******************************************************************************
 *
 * \brief Prepare the system configuration for CPU idle in IDLE Task.
 *        In case of A15, this function enables SR3-APG (HG / Fast Ramp-up).
 *        It also forces A15_1 to OFF.
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_idlePrepare(Void)
{
#ifdef CPU_IDLE_ENABLED
    System_EveObj *pObj;
    UInt32 regVal;
    pObj = &gSystem_objEve;
    Int32 status = (Int32) PM_SUCCESS;
    if (SYSTEM_PROC_EVE1 == System_getSelfProcId())
    {
        status = PMHALPdmSetPDState(PMHAL_PRCM_PD_EVE1,
                           PMHAL_PRCM_PD_STATE_ON_ACTIVE,
                           PM_TIMEOUT_NOWAIT);
        UTILS_assert(status == (Int32)PM_SUCCESS);

        status =  PMHALCMSetCdClockMode(PMHAL_PRCM_CD_EVE1,
                           PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                           PM_TIMEOUT_NOWAIT);
        UTILS_assert(status == (Int32)PM_SUCCESS);

        pObj->eveIdleInitDone = 1U;
    }
#if defined (TDA2XX_FAMILY_BUILD)
    if (SYSTEM_PROC_EVE2 == System_getSelfProcId())
    {

        status = PMHALPdmSetPDState(PMHAL_PRCM_PD_EVE2,
                           PMHAL_PRCM_PD_STATE_ON_ACTIVE,
                           PM_TIMEOUT_NOWAIT);
        UTILS_assert(status == (Int32)PM_SUCCESS);


        status =  PMHALCMSetCdClockMode(PMHAL_PRCM_CD_EVE2,
                           PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                           PM_TIMEOUT_NOWAIT);
        UTILS_assert(status == (Int32)PM_SUCCESS);

        pObj->eveIdleInitDone = 1U;
    }
    if (SYSTEM_PROC_EVE3 == System_getSelfProcId())
    {
        status = PMHALPdmSetPDState(PMHAL_PRCM_PD_EVE3,
                           PMHAL_PRCM_PD_STATE_ON_ACTIVE,
                           PM_TIMEOUT_NOWAIT);
        UTILS_assert(status == (Int32)PM_SUCCESS);


        status =  PMHALCMSetCdClockMode(PMHAL_PRCM_CD_EVE3,
                           PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                           PM_TIMEOUT_NOWAIT);
        UTILS_assert(status == (Int32)PM_SUCCESS);

        pObj->eveIdleInitDone = 1U;
    }
    if (SYSTEM_PROC_EVE4 == System_getSelfProcId())
    {
        status = PMHALPdmSetPDState(PMHAL_PRCM_PD_EVE4,
                           PMHAL_PRCM_PD_STATE_ON_ACTIVE,
                           PM_TIMEOUT_NOWAIT);
        UTILS_assert(status == (Int32)PM_SUCCESS);


        status =  PMHALCMSetCdClockMode(PMHAL_PRCM_CD_EVE4,
                           PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                           PM_TIMEOUT_NOWAIT);
        UTILS_assert(status == (Int32)PM_SUCCESS);

        pObj->eveIdleInitDone = 1U;
    }
#endif
    /* If the DMA is freed then disable the DMA by setting
     * Force standby and Force Idle.
     */
    regVal  = HW_RD_REG32(0x400A5640);
    if (0U == regVal)
    {
        HW_WR_REG32(0x40086000 + 0x10, 0);
        HW_WR_REG32(0x40087000 + 0x10, 0);
    }
    /* Configure the SCTM counters to idle when the
     * ARP32 is IDLE.
     */
    regVal  = HW_RD_REG32(0x40085000U);
    regVal &= (UInt32)0xFFFFFFF9U;
    regVal |= (UInt32)0x04U;
    HW_WR_REG32(0x40085000U, regVal);
    regVal  = HW_RD_REG32(0x40085100U);
    regVal &= ~(UInt32)0x20U;
    HW_WR_REG32(0x40085100U, regVal);
    ARP32_WUGEN_IRQ_Init();
#endif
}

/**
 *******************************************************************************
 *
 * \brief This Function Enables the TPTC by setting it to smart IDLE and smart
 *        standby. The EDMA is operational after this setting.
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_idleEnableEveDMA(void)
{
#ifdef CPU_IDLE_ENABLED
    /* Enable DMA before ALG Process. Put the TPTC to
     * Smart Standby and Smart Idle
     */
    HW_WR_REG32(0x40086000 + 0x10, 0x28);
    HW_WR_REG32(0x40087000 + 0x10, 0x28);
#endif
}

/**
 *******************************************************************************
 *
 * \brief This Function Disables the TPTC by setting it to force IDLE and force
 *        standby. The EDMA is in low power mode after this setting.
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_idleDisableEveDMA(void)
{
#ifdef CPU_IDLE_ENABLED
    /* If the DMA is freed then disable the DMA by setting
    * Force standby and Force Idle.
    */
    UInt32 regVal  = HW_RD_REG32(0x400A5640);
    if (0U == regVal)
    {
        HW_WR_REG32(0x40086000 + 0x10, 0);
        HW_WR_REG32(0x40087000 + 0x10, 0);
    }
#endif
}

/* Nothing beyond this point */
