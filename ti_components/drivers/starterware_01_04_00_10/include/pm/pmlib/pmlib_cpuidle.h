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
 *  \file  pmlib_cpuidle.h
 *
 *  \brief  This file declares the interface for CPU Idle functionality. This is
 *          is a low latency power saving mode which allows fast wakeup
 *          depending on the power mode set.
 */

#ifndef PMLIB_CPUIDLE_H_
#define PMLIB_CPUIDLE_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "pm_types.h"
#include "pmhal_prcm.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Enter the CPU specified into the given low power state.
 *
 * NOTE:    To keep the ADAS power management simple, we only
 *          support one low-power mode per CPU. The power state is
 *          used in the API to enable supporting multiple low power
 *          states in future w/o breaking compatibility.
 *
 * \param   pwrst   Low power state to enter into. Refer enum
 *                  #pmhalPrcmPdState_t for details.
 *
 * \return  status  Returns the status of the API. This can be the following
 *                  values:
 *                  PM_SUCCESS  If the desired power state was met.
 *                  PM_FAIL     If the desired power state was not met.
 */
pmErrCode_t PMLIBCpuIdle(pmhalPrcmPdState_t pwrst);

/**
 * \brief   Enter CPU1 into FORCE_OFF mode.
 *
 *          This function can be used by the application to enter CPU1
 *          into FORCE_OFF mode when no binary is loaded for CPU1.
 *
 * \param   none
 *
 * \return  none
 */
void PMLIBCpu1ForcedOff(void);

/**
 * \brief   Configure the DSP Core Pac Off mode when the DSP CPU executes Idle.
 *          Applicable only to DSP.
 *
 * \param   enable  1 - to configure the DSP PWRCMD register to put the DSP Core
 *                  Pac to off state when the DSP executes Idle Instruction.
 *                  0 - to configure the DSP PWRCMD register to not put the DSP
 *                  CorePac to off state when the DSP executes Idle Instruction.
 *
 * \return  none
 */
void PMLIBSetCorepacPowerDown(uint32_t enable);

#ifdef __cplusplus
}
#endif

#endif

