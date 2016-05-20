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
 * \file    pmlib_cpuidle_m4.c
 *
 * \brief   This file declares the interface for IPU CPU Idle functionality.
 *          This is a low latency power saving mode which allows fast wakeup
 *          depending on the power mode set.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include "hw_types.h"
#include "soc.h"
#include "hw_ipu_mmu.h"
#include "hw_ipu_m4_nvic.h"
#include "pmhal_prcm.h"
#include "hw/hw_ipu_wugen_local_prcm.h"
#include "pmlib/pmlib_cpuidle.h"
#include "pmlib_cpuidle_utils_m4.h"
#include "hw_ctrl_core_sec.h"
#include "hw_ctrl_core.h"

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

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

pmErrCode_t PMLIBCpuIdle(pmhalPrcmPdState_t pwrst)
{
    pmErrCode_t retVal = PM_SUCCESS;

    if (pwrst < PMHAL_PRCM_PD_STATUS_COUNT)
    {
#if defined (TDA3XX_BUILD)
        HW_WR_FIELD32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                      CTRL_CORE_MMR_LOCK_1, CTRL_CORE_MMR_LOCK_1,
                      CTRL_CORE_MMR_LOCK_1_TOUNLOCK);

        /*
         * PRCM Override should be removed to allow the IPU to go to low power
         * state.
         */
        HW_WR_FIELD32(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_IPU_WAKEUP,
                      CTRL_CORE_SEC_IPU_WAKEUP_WKUP_EN,
                      0x00);
#endif

        /* Set IPU in deep sleep to set CM standby */
        HW_WR_FIELD32(SOC_IPU1_C0_INTC_BASE + IPU_M4_NVIC_SYSTEM_CONTROL,
                      IPU_M4_NVIC_SYSTEM_CONTROL_SLEEPDEEP,
                      0x01);

        HW_WR_FIELD32(SOC_IPU1_MMU_BASE + IPU_MMU_SYSCONFIG,
                      IPU_MMU_SYSCONFIG_IDLEMODE,
                      IPU_MMU_SYSCONFIG_IDLEMODE_SSIDLE);

        /* setStandBy_Core_sysconfig  */
        HW_WR_FIELD32(SOC_IPU1_WUGEN_BASE + IPU_STANDBY_CORE_SYSCONFIG,
                      IPU_STANDBY_CORE_SYSCONFIG_STANDBYMODE,
                      0x3);

        /* setIdle_Core_sysconfig */
        HW_WR_FIELD32(SOC_IPU1_WUGEN_BASE + IPU_IDLE_CORE_SYSCONFIG,
                      IPU_IDLE_CORE_SYSCONFIG_IDLEMODE,
                      0x3);

        PmlibDoWFI();
    }
    else
    {
        retVal = PM_BADARGS;
    }

    return retVal;
}

/* None */

