/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 * \file    pmlib_cpuidle_arp32.c
 *
 * \brief   This file declares the interface for EVE CPU Idle functionality.
 *          This is a low latency power saving mode which allows fast wakeup
 *          depending on the power mode set.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include "hw_types.h"
#include "soc.h"
#include "hw_eve_control.h"
#include "pm_types.h"
#include "pmhal_prcm.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Execute IDLE instruction.
 *          This function is called by CPU Idle API to execute IDLE.
 *
 * \param   none
 *
 * \return  none
 **/
static void PmlibEveIdle(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

pmErrCode_t PMLIBCpuIdle(pmhalPrcmPdState_t pwrst)
{
    pmErrCode_t status = PM_SUCCESS;

    if (pwrst < PMHAL_PRCM_PD_STATUS_COUNT)
    {
        uint32_t regVal = 0U;
        pmhalPrcmModuleMStbyMode_t lastStandbyState =
            PMHAL_PRCM_MODULE_MSTANDBYMODE_FORCE_STANDBY;
        pmhalPrcmModuleSIdleMode_t lastIdleState =
            PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE;

        /* Read the EVE SYSCONFIG register contents and store to a
         * local variable.
         */
        regVal = HW_RD_REG32(SOC_EVE_SYSTEM_BASE + EVE_SYSCONFIG);

        /* Put the EVE to SMART_STANDBY_WITH_WAKEUP and SMART_IDLE_WITH_WAKEUP
         */
        HW_WR_FIELD32(SOC_EVE_SYSTEM_BASE + EVE_SYSCONFIG,
                      EVE_SYSCONFIG_STANDBYMODE, 0x3);
        HW_WR_FIELD32(SOC_EVE_SYSTEM_BASE + EVE_SYSCONFIG,
                      EVE_SYSCONFIG_IDLEMODE, 0x3);

        /* Let ARP32 execute Idle Instruction to make the EVE start its power
         * down sequence.
         */
        PmlibEveIdle();

        /* After coming out of idle find the origin standby and idle states
         * and reprogram to the EVE SYSCONFIG register.
         */
        lastStandbyState = (pmhalPrcmModuleMStbyMode_t) HW_GET_FIELD(
            regVal, EVE_SYSCONFIG_STANDBYMODE);
        HW_WR_FIELD32(SOC_EVE_SYSTEM_BASE + EVE_SYSCONFIG,
                      EVE_SYSCONFIG_STANDBYMODE,
                      lastStandbyState);

        lastIdleState = (pmhalPrcmModuleSIdleMode_t) HW_GET_FIELD(
            regVal, EVE_SYSCONFIG_IDLEMODE);
        HW_WR_FIELD32(SOC_EVE_SYSTEM_BASE + EVE_SYSCONFIG,
                      EVE_SYSCONFIG_IDLEMODE,
                      lastIdleState);
    }
    else
    {
        status = PM_BADARGS;
    }

    return status;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static void PmlibEveIdle(void)
{
    asm ("IDLE:  IDLE");
}

