/**
 *  \file     sbl_utils_tda3xx_ddr_config.h
 *
 *  \brief    This file contains the SBL Utility layer specific to TDA3xx DDR
 *            configuration. This is taken from gel and follows the Gel coding
 *            guidelines which are different from starterware coding guidelines.
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

#ifndef SBL_UTILS_TDA3XX_DDR_CONFIG_H_
#define SBL_UTILS_TDA3XX_DDR_CONFIG_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Macros for DDR type */
#define CFG_MODE_DDR3                                           (0x1000U)
#define CFG_MODE_DDR2                                           (0x1001U)
#define CFG_MODE_LPDDR2                                         (0x1002U)

/* DMM Registers */
#define SOC_MA_MPU_CONF_REGS_BASE                               (0x482af000U)
#define LISA_MAP_0                                              (0x40)
#define LISA_MAP_1                                              (0x44)
#define LISA_MAP_2                                              (0x48)
#define LISA_MAP_3                                              (0x4C)

/* EMIF Registers */
#define EMIF_PHY_STATUS_7                                       (0x15CU)
#define EMIF_PHY_STATUS_8                                       (0x160U)
#define EMIF_PHY_STATUS_9                                       (0x164U)
#define EMIF_PHY_STATUS_10                                      (0x168U)
#define EMIF_PHY_STATUS_11                                      (0x16CU)
#define EMIF_PHY_STATUS_12                                      (0x170U)
#define EMIF_PHY_STATUS_13                                      (0x174U)
#define EMIF_PHY_STATUS_14                                      (0x178U)
#define EMIF_PHY_STATUS_15                                      (0x17CU)
#define EMIF_PHY_STATUS_16                                      (0x180U)
#define EMIF_PHY_STATUS_17                                      (0x184U)
#define EMIF_PHY_STATUS_18                                      (0x188U)
#define EMIF_PHY_STATUS_19                                      (0x18CU)
#define EMIF_PHY_STATUS_20                                      (0x190U)
#define EMIF_PHY_STATUS_21                                      (0x194U)
#define EMIF_PHY_STATUS_22                                      (0x198U)
#define EMIF_PHY_STATUS_23                                      (0x19CU)
#define EMIF_PHY_STATUS_24                                      (0x1A0U)
#define EMIF_PHY_STATUS_25                                      (0x1A4U)
#define EMIF_PHY_STATUS_26                                      (0x1A8U)
#define EMIF_LPDDR2_MODE_REG_DATA                               (0x40U)
#define EMIF_LPDDR2_MODE_REG_CONFIG                             (0x50U)

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
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This function does the DDR3 Configuration.
 *
 * \param   ddrSpeed         DDR Speed
 *                           SBLLIB_DDR_SPEED_532MHZ : For 532 MHz
 *                           SBLLIB_DDR_SPEED_400MHZ : For 400 MHz
 *                           SBLLIB_DDR_SPEED_333MHZ : For 333 MHz
 *
 * \return  None.
 */
void SBLUtilsDDR3Config(uint32_t ddrSpeed);

/**
 * \brief   This function does the DDR2 Configuration.
 *
 * \param   ddrSpeed         DDR Speed
 *                           SBLLIB_DDR_SPEED_532MHZ : For 532 MHz
 *                           SBLLIB_DDR_SPEED_400MHZ : For 400 MHz
 *                           SBLLIB_DDR_SPEED_333MHZ : For 333 MHz
 *
 * \return  None.
 */
void SBLUtilsDDR2Config(uint32_t ddrSpeed);

/**
 * \brief   This function does the LPDDR2 Configuration.
 *
 * \param   lpddr2Speed      LPDDR2 Speed
 *                           SBLLIB_DDR_SPEED_400MHZ : For 400 MHz
 *                           SBLLIB_DDR_SPEED_333MHZ : For 333 MHz
 *
 * \return  None.
 */
void SBLUtilsLPDDR2Config(uint32_t lpddr2Speed);

#ifdef __cplusplus
}

#endif

#endif

