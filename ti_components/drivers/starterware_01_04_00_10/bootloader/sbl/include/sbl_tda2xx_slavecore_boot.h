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
 *                      module enable & booting up the slave cores
 */
#ifndef SBL_TDA2XX_SLAVECORE_BOOT_H_
#define SBL_TDA2XX_SLAVECORE_BOOT_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "stdint.h"
#include "hw_types.h"

#ifdef __cplusplus
extern "C"
{
#endif
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/**
 * \brief  Enum to select the SBL's Build Mode.
 */
typedef enum SblBuildMode
{
    SBL_BUILD_MODE_PROD,
    /**< SBL's build mode is production. In production build mode, the slave
     *   core is put in a low power state (normally PD_OFF) when the Multi-core
     *   Application does not have Image for that particular core.
     */
    SBL_BUILD_MODE_DEV
    /**< SBL's build mode is development. In development build mode, the slave
     *   core is brought out of reset even when the Multi-core Application does
     *   not have Image for that particular core.
     */
} SblBuildMode_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
int32_t CPU_SystemReset(cpu_core_id_t cpu);
void MPU_CPU1_BringUp(uint32_t EntryPoint, uint32_t sblBuildMode);
int32_t IPU1_Clk_Enable(void);
void IPU1_AMMU_Config(void);
void IPU1_SystemReset(void);
void IPU1_CPU0_BringUp(uint32_t EntryPoint, uint32_t sblBuildMode);
void IPU1_CPU1_BringUp(uint32_t EntryPoint, uint32_t sblBuildMode);
int32_t IPU2_Clk_Enable(void);
void IPU2_AMMU_Config(void);
void IPU2_CPU0_BringUp(uint32_t EntryPoint, uint32_t sblBuildMode);
void IPU2_CPU1_BringUp(uint32_t EntryPoint, uint32_t sblBuildMode);
int32_t DSP1_Clk_Enable(void);
void DSP1_BringUp(uint32_t EntryPoint, uint32_t sblBuildMode);
int32_t DSP2_Clk_Enable(void);
void DSP2_BringUp(uint32_t EntryPoint, uint32_t sblBuildMode);
int32_t EVE1_Clk_Enable(void);
void EVE_SYSMMU_Config(uint32_t eve_mmu_base_address, uint32_t eve_entryPoint);
void EVE1_BringUp(uint32_t EntryPoint, uint32_t sblBuildMode);
int32_t EVE2_Clk_Enable(void);
void EVE2_BringUp(uint32_t EntryPoint, uint32_t sblBuildMode);
int32_t EVE3_Clk_Enable(void);
void EVE3_BringUp(uint32_t EntryPoint, uint32_t sblBuildMode);
int32_t EVE4_Clk_Enable(void);
void EVE4_BringUp(uint32_t EntryPoint, uint32_t sblBuildMode);
void IVAHD_Clk_Enable(void);
void IVAHD_BringUp(uint32_t EntryPoint, uint32_t sblBuildMode);
void slavecore_prcm_enable(void);
void IPU2_SystemReset(void);
/** \brief  Function to bring up the dual core IPU subsystem.
 *
 *  \param  ipuId           ID of the IPU to be loaded. Valid values are:
 *                          0U - IPU1
 *                          1U - IPU2
 *  \param  entryPtCPU0     Entry Point of the CPU0 for the given IPU.
 *  \param  entryPtCPU1     Entry Point of the CPU1 for the given IPU.
 *
 *  \return None.
 */
void SBLIPUBringUp(uint32_t ipuId,
                   uint32_t entryPtCPU0,
                   uint32_t entryPtCPU1, uint32_t sblBuildMode);

#ifdef __cplusplus
}
#endif

#endif /*SBL_TDA2XX_SLAVECORE_BOOT_H_*/

