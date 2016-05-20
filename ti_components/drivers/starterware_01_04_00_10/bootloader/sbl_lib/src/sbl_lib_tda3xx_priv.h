/**
 *  \file     sbl_lib_tda3xx_priv.h
 *
 *  \brief    This file contains the platform specific private layer of
 *            Secondary Bootloader(SBL) Library for tda3xx.
 *            This also contains some related macros.
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

#ifndef SBL_LIB_TDA3XX_PRIV_H_
#define SBL_LIB_TDA3XX_PRIV_H_

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

/**
 * \brief  This macro contains the size of OCMC1 (512 KB).
 */
#define SBLLIB_SOC_OCMC_RAM1_SIZE                       ((uint32_t) 0x00080000U)

/**
 * \brief  This macro contains the L2 base address of DSP.
 */
#define SBLLIB_SOC_DSP_L2_BASE                          ((uint32_t) 0x00800000U)

/**
 * \brief  This macro contains the L1P base address of DSP.
 */
#define SBLLIB_SOC_DSP_L1P_BASE                         ((uint32_t) 0x00E00000U)

/**
 * \brief  This macro contains the L1D base address of DSP.
 */
#define SBLLIB_SOC_DSP_L1D_BASE                         ((uint32_t) 0x00F00000U)

/**
 * \brief  This macro contains the DMEM base address of EVE.
 */
#define SBLLIB_SOC_EVE_DMEM_BASE                        ((uint32_t) 0x40020000U)

/**
 * \brief  This macro contains the WBUF base address of EVE.
 */
#define SBLLIB_SOC_EVE_WBUF_BASE                        ((uint32_t) 0x40040000U)

/**
 * \brief  This macro contains the IBUF LA base address of EVE.
 */
#define SBLLIB_SOC_EVE_IBUF_LA_BASE                     ((uint32_t) 0x40050000U)

/**
 * \brief  This macro contains the IBUF HA base address of EVE.
 */
#define SBLLIB_SOC_EVE_IBUF_HA_BASE                     ((uint32_t) 0x40054000U)

/**
 * \brief  This macro contains the IBUF LB base address of EVE.
 */
#define SBLLIB_SOC_EVE_IBUF_LB_BASE                     ((uint32_t) 0x40070000U)

/**
 * \brief  This macro contains the IBUF HB base address of EVE.
 */
#define SBLLIB_SOC_EVE_IBUF_HB_BASE                     ((uint32_t) 0x40074000U)

/**
 * \brief  This macro contains the DMEM base address of EVE as accessed from
 *         IPU.
 */
#define SBLLIB_SOC_IPU_EVE_DMEM_BASE                    ((uint32_t) 0x42020000U)

/**
 * \brief  This macro contains the WBUF base address of EVE as accessed from
 *         IPU.
 */
#define SBLLIB_SOC_IPU_EVE_WBUF_BASE                    ((uint32_t) 0x42040000U)

/**
 * \brief  This macro contains the IBUF LA base address of EVE as accessed from
 *         IPU.
 */
#define SBLLIB_SOC_IPU_EVE_IBUF_LA_BASE                 ((uint32_t) 0x42050000U)

/**
 * \brief  This macro contains the IBUF HA base address of EVE as accessed from
 *         IPU.
 */
#define SBLLIB_SOC_IPU_EVE_IBUF_HA_BASE                 ((uint32_t) 0x42054000U)

/**
 * \brief  This macro contains the IBUF LB base address of EVE as accessed from
 *         IPU.
 */
#define SBLLIB_SOC_IPU_EVE_IBUF_LB_BASE                 ((uint32_t) 0x42070000U)

/**
 * \brief  This macro contains the IBUF HB base address of EVE as accessed from
 *         IPU.
 */
#define SBLLIB_SOC_IPU_EVE_IBUF_HB_BASE                 ((uint32_t) 0x42074000U)

/**
 * \brief  This macro contains the EVE's MMU base address as accessed from
 *         IPU.
 */
#define SBLLIB_SOC_IPU_EVE_MMU0_BASE                    ((uint32_t) 0x62081000U)

/**
 * \brief  This macro contains the IPU1's internal RAM base address as accessed
 *         from L3's(SOC) view.
 */
#define SBLLIB_SOC_IPU_RAM_BASE                         ((uint32_t) 0x58820000U)

/**
 * \brief  This macro contains the EDMA TPTC0 base address of EVE as accessed
 *         from IPU.
 */
#define SBLLIB_SOC_IPU_EVE_TPTC0_BASE                   ((uint32_t) 0x62086000U)

/**
 * \brief  This macro contains the EDMA TPTC1 base address of EVE as accessed
 *         from IPU.
 */
#define SBLLIB_SOC_IPU_EVE_TPTC1_BASE                   ((uint32_t) 0x62087000U)

/**
 * \brief  This macro contains the EVE core's boot address when there is no
 *         App Image for EVE.
 */
#define SBLLIB_EVE_BOOT_ADDRESS_NO_IMAGE                ((uint32_t) 0x80000000U)

/**
 * \brief  This macro contains the EVE core's reset vector address when there
 *         is no App Image for EVE.
 */
#define SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE       ( \
        SBLLIB_EVE_BOOT_ADDRESS_NO_IMAGE + 0x100U)

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

/* None */

#ifdef __cplusplus
}

#endif

#endif

