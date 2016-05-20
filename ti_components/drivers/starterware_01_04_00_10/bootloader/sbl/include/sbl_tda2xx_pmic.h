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
 *  Component:          SBL
 *
 *  Filename:           sbl_tda2xx_SR0.c
 *
 *  Description:        This file contain AVS Class-0 implementation
 *
 *  Author:             vinoth
 *  Reference:          vayu uboot AVS Class-0 (Nishanth Menon)
 */
#ifndef SBL_TDA2XX_PMIC_H
#define SBL_TDA2XX_PMIC_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include "pm/pm_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* IODelay register offsets for TDA2xx platform */
#define CONFIG_REG_0                                (uint32_t) (0x0000000CU)
#define CONFIG_REG_1                                (uint32_t) (0x00000010U)
#define CONFIG_REG_2                                (uint32_t) (0x00000014U)
#define CONFIG_REG_3                                (uint32_t) (0x00000018U)
#define CONFIG_REG_4                                (uint32_t) (0x0000001CU)
#define CONFIG_REG_8                                (uint32_t) (0x0000002CU)

/* Fields for CONFIG_REG_0 */
#define CONFIG_REG_0_CALIBRATION_START_MASK         (0x00000001U)
#define CONFIG_REG_0_CALIBRATION_START_SHIFT        (0U)

#define CONFIG_REG_0_ROM_READ_MASK                  (0x00000002U)
#define CONFIG_REG_0_ROM_READ_SHIFT                 (1U)

/* Fields for CONFIG_REG_2 */
#define CONFIG_REG_2_REFCLK_PERIOD_MASK             (0x0000FFFFU)
#define CONFIG_REG_2_REFCLK_PERIOD_SHIFT            (0U)

/* Fields for CONFIG_REG_3 */
#define CONFIG_REG_3_COARSE_REF_COUNT_MASK          (0x0000FFFFU)
#define CONFIG_REG_3_COARSE_REF_COUNT_SHIFT         (0U)

#define CONFIG_REG_3_COARSE_DELAY_COUNT_MASK        (0xFFFF0000U)
#define CONFIG_REG_3_COARSE_DELAY_COUNT_SHIFT       (16U)

/* Fields for CONFIG_REG_4 */
#define CONFIG_REG_4_FINE_REF_COUNT_MASK            (0x0000FFFFU)
#define CONFIG_REG_4_FINE_REF_COUNT_SHIFT           (0U)

#define CONFIG_REG_4_FINE_DELAY_COUNT_MASK          (0xFFFF0000U)
#define CONFIG_REG_4_FINE_DELAY_COUNT_SHIFT         (16U)

/* ISOIN Field for CTRL_CORE_SMA_SW_0 */
#define CTRL_CORE_SMA_SW_0_ISOIN_MASK               (0x00000004U)
#define CTRL_CORE_SMA_SW_0_ISOIN_SHIFT              (2U)

/* Lock and Unlock values for Global lock : CONFIG_REG_8 */
#define CONFIG_REG_8_LOCK_GLOBAL_LOCK               (0x0000AAABU)
#define CONFIG_REG_8_UNLOCK_GLOBAL_LOCK             (0x0000AAAAU)

/* Lock and Unlock values for MMR_LOCK1 */
#define LOCK_MMR_LOCK1                              (0x1A1C8144U)
#define UNLOCK_MMR_LOCK1                            (0x2FF1AC2BU)

/* Lock and Unlock values for MMR_LOCK5 */
#define LOCK_MMR_LOCK5                              (0x143F832CU)
#define UNLOCK_MMR_LOCK5                            (0x6F361E05U)

/* Reference clock period for sysclk1 of 20 MHz */
#define REFCLK_PERIOD_SYSCLK1_20MHZ                 (0x00002710U)

/* Reference clock period for L4 ICLK of 66.5 MHz */
#define REFCLK_PERIOD_L4ICLK_66_5_MHZ               (0x000005DEU)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif
