/**
 *  \file     sbl_lib_config.h
 *
 *  \brief    This file contains compile time configurable parameters of
 *            TDA3xx SBL. This can be used to port SBL to custom use case.
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

#ifndef SBL_LIB_CONFIG_H_
#define SBL_LIB_CONFIG_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "sbl_lib/sbl_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

#if defined (SBL_CONFIG_DISABLE_SAFETY_FEATURES)

/* DDR Type */
#define SBL_LIB_CONFIG_DDR_TYPE                 (SBLLIB_DDR_TYPE_DDR3)
/* DDR Speed */
#define SBL_LIB_CONFIG_DDR_SPEED                (SBLLIB_DDR_SPEED_532MHZ)
/* DDR Type for 12x12 */
#define SBL_LIB_CONFIG_DDR_TYPE_12X12           (SBLLIB_DDR_TYPE_LPDDR2)
/* DDR Speed for LPDDR2 */
#define SBL_LIB_CONFIG_DDR_SPEED_12X12          (SBLLIB_DDR_SPEED_400MHZ)
/* UART instance to use for debug messages */
#define SBL_LIB_CONFIG_UART_INST                (UART3_INST)
/* Whether to disable AMMU before jumping to M4 App */
#define SBL_LIB_CONFIG_DISABLE_AMMU             (0)
/* Whether to disable cache before jumping to M4 App */
#define SBL_LIB_CONFIG_DISABLE_UNICACHE         (0)
/* Whether to enable TESOC Tests at SBL start */
#define SBL_LIB_CONFIG_ENABLE_IPU_TESOC_TESTS   (0)
/* Whether to run CRC on TESOC ROM before TESOC Tests */
#define SBL_LIB_CONFIG_ENABLE_IPU_TESOC_ROM_CRC (0)
/* Whether to enable TESOC Tests other than IPU i.e. DSP 1/2, EVE1,
 * DSS/ISS/VIP
 */
#define SBL_LIB_CONFIG_ENABLE_OTHER_TESOC_TESTS (0)
/* Whether to enable CRC Checks on App Image */
#define SBL_LIB_CONFIG_ENABLE_CRC               (0)
/* DDR location where app image is copied before doing CRC for 12X12 device */
#define SBL_LIB_APP_IMAGE_DDR_ADDRESS_12X12     (0x82000000U)
/* DDR location where app image is copied before doing CRC for 15X15 device */
#define SBL_LIB_APP_IMAGE_DDR_ADDRESS_15X15     (0x98000000U)
/* Whether to enable ECC for EMIF */
#define SBL_LIB_CONFIG_ENABLE_EMIF_ECC          (0)
/* EMIF start address */
#define SBL_LIB_CONFIG_EMIF_START_ADDR          (0x80000000U)
/* EMIF ECC start address for region 1 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR1_12X12 (0x0U)
/* EMIF ECC end address for region 1 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR1_12X12   (0x0U)
/* EMIF ECC start address for region 1 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR1_15X15 (0x0U)
/* EMIF ECC end address for region 1 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR1_15X15   (0x0U)
/* Define the range type of region 1 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_REG1_RANGE_TYPE_12X12 ( \
        EMIF_ECC_ADDR_RANGE_WITHIN)
/* Define the range type of region 1 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_REG1_RANGE_TYPE_15X15 ( \
        EMIF_ECC_ADDR_RANGE_WITHIN)
/* EMIF ECC start address for region 2 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR2_12X12 (0x0U)
/* EMIF ECC end address for region 2 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR2_12X12   (0x0U)
/* EMIF ECC start address for region 2 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR2_15X15 (0x0U)
/* EMIF ECC end address for region 2 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR2_15X15   (0x0U)
/* Define the range type of region 2 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_REG2_RANGE_TYPE_12X12 ( \
        EMIF_ECC_ADDR_RANGE_WITHIN)
/* Define the range type of region 2 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_REG2_RANGE_TYPE_15X15 ( \
        EMIF_ECC_ADDR_RANGE_WITHIN)
/* EMIF Size for 12X12 silicon: Half of total LPDDR2 size i.e. 32 MB */
#define SBL_LIB_CONFIG_EMIF_SIZE_12X12          (0x02000000U)
/* EMIF Size for 15X15 silicon i.e. 512 MB */
#define SBL_LIB_CONFIG_EMIF_SIZE_15X15          (0x20000000U)
/* OPP_HIGH DSP 750 MHz Enable Macro : Should be set to 1 to make sure
 * EVE VID DSP PLL is configured for DSP to be at 750 MHz. Please understand
 * in this mode the EVE VID DSP PLL can only be configured for 74.5 MHz and
 * 149 MHz VID_PIX clock.
 */
#define SBL_LIB_CONFIG_DSP_OPP_HIGH_750MHZ      (0U)

#elif defined (SBL_CONFIG_CUSTOM1)

/* DDR Type */
#define SBL_LIB_CONFIG_DDR_TYPE                (SBLLIB_DDR_TYPE_DDR2)
/* DDR Speed */
#define SBL_LIB_CONFIG_DDR_SPEED               (SBLLIB_DDR_SPEED_333MHZ)
/* DDR Type for 12x12 */
#define SBL_LIB_CONFIG_DDR_TYPE_12X12          (SBLLIB_DDR_TYPE_INVALID)
/* DDR Speed for LPDDR2 */
#define SBL_LIB_CONFIG_DDR_SPEED_12X12         (SBLLIB_DDR_SPEED_INVALID)
/* UART instance to use for debug messages */
#define SBL_LIB_CONFIG_UART_INST               (UART1_INST)
/* Whether to disable AMMU before jumping to M4 App */
#define SBL_LIB_CONFIG_DISABLE_AMMU             (0)
/* Whether to disable cache before jumping to M4 App */
#define SBL_LIB_CONFIG_DISABLE_UNICACHE         (0)
/* Whether to enable TESOC Tests at SBL start */
#define SBL_LIB_CONFIG_ENABLE_IPU_TESOC_TESTS   (0)
/* Whether to run CRC on TESOC ROM before TESOC Tests */
#define SBL_LIB_CONFIG_ENABLE_IPU_TESOC_ROM_CRC (0)
/* Whether to enable TESOC Tests other than IPU i.e. DSP 1/2, EVE1,
 * DSS/ISS/VIP
 */
#define SBL_LIB_CONFIG_ENABLE_OTHER_TESOC_TESTS (0)
/* Whether to enable CRC Checks on App Image */
#define SBL_LIB_CONFIG_ENABLE_CRC               (0)
/* DDR location where app image is copied before doing CRC for 12X12 device */
#define SBL_LIB_APP_IMAGE_DDR_ADDRESS_12X12     (0x82000000U)
/* DDR location where app image is copied before doing CRC for 15X15 device */
#define SBL_LIB_APP_IMAGE_DDR_ADDRESS_15X15     (0x98000000U)
/* Whether to enable ECC for EMIF */
#define SBL_LIB_CONFIG_ENABLE_EMIF_ECC          (0)
/* EMIF start address */
#define SBL_LIB_CONFIG_EMIF_START_ADDR          (0x80000000U)
/* EMIF ECC start address for region 1 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR1_12X12 (0x0U)
/* EMIF ECC end address for region 1 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR1_12X12   (0x0U)
/* EMIF ECC start address for region 1 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR1_15X15 (0x0U)
/* EMIF ECC end address for region 1 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR1_15X15   (0x0U)
/* Define the range type of region 1 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_REG1_RANGE_TYPE_12X12 ( \
        EMIF_ECC_ADDR_RANGE_WITHIN)
/* Define the range type of region 1 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_REG1_RANGE_TYPE_15X15 ( \
        EMIF_ECC_ADDR_RANGE_WITHIN)
/* EMIF ECC start address for region 2 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR2_12X12 (0x0U)
/* EMIF ECC end address for region 2 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR2_12X12   (0x0U)
/* EMIF ECC start address for region 2 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR2_15X15 (0x0U)
/* EMIF ECC end address for region 2 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR2_15X15   (0x0U)
/* Define the range type of region 2 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_REG2_RANGE_TYPE_12X12 ( \
        EMIF_ECC_ADDR_RANGE_WITHIN)
/* Define the range type of region 2 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_REG2_RANGE_TYPE_15X15 ( \
        EMIF_ECC_ADDR_RANGE_WITHIN)
/* EMIF Size for 12X12 silicon: Half of total LPDDR2 size i.e. 32 MB */
#define SBL_LIB_CONFIG_EMIF_SIZE_12X12          (0x02000000U)
/* EMIF Size for 15X15 silicon i.e. 512 MB */
#define SBL_LIB_CONFIG_EMIF_SIZE_15X15          (0x20000000U)
/* OPP_HIGH DSP 750 MHz Enable Macro : Should be set to 1 to make sure
 * EVE VID DSP PLL is configured for DSP to be at 750 MHz. Please understand
 * in this mode the EVE VID DSP PLL can only be configured for 74.5 MHz and
 * 149 MHz VID_PIX clock.
 */
#define SBL_LIB_CONFIG_DSP_OPP_HIGH_750MHZ      (0U)

#else   /* Default configuration */

/* DDR Type */
#define SBL_LIB_CONFIG_DDR_TYPE                 (SBLLIB_DDR_TYPE_DDR3)
/* DDR Speed */
#define SBL_LIB_CONFIG_DDR_SPEED                (SBLLIB_DDR_SPEED_532MHZ)
/* DDR Type for 12x12 */
#define SBL_LIB_CONFIG_DDR_TYPE_12X12           (SBLLIB_DDR_TYPE_LPDDR2)
/* DDR Speed for LPDDR2 */
#define SBL_LIB_CONFIG_DDR_SPEED_12X12          (SBLLIB_DDR_SPEED_400MHZ)
/* UART instance to use for debug messages */
#define SBL_LIB_CONFIG_UART_INST                (UART3_INST)
/* Whether to disable AMMU before jumping to M4 App */
#define SBL_LIB_CONFIG_DISABLE_AMMU             (0)
/* Whether to disable cache before jumping to M4 App */
#define SBL_LIB_CONFIG_DISABLE_UNICACHE         (0)
/* Whether to enable TESOC Tests at SBL start
 * NOTE: Enable is not supported and not validated
 **/
#define SBL_LIB_CONFIG_ENABLE_IPU_TESOC_TESTS   (0)
/* Whether to run CRC on TESOC ROM before TESOC Tests
 * NOTE: Enable is not supported and not validated
 **/
#define SBL_LIB_CONFIG_ENABLE_IPU_TESOC_ROM_CRC (0)
/* Whether to enable TESOC Tests other than IPU i.e. DSP 1/2, EVE1,
 * DSS/ISS/VIP
 */
#define SBL_LIB_CONFIG_ENABLE_OTHER_TESOC_TESTS (1)
/* Whether to enable CRC Checks on App Image */
#define SBL_LIB_CONFIG_ENABLE_CRC               (1)
/* DDR location where app image is copied before doing CRC for 12X12 device */
#define SBL_LIB_APP_IMAGE_DDR_ADDRESS_12X12     (0x82000000U)
/* DDR location where app image is copied before doing CRC for 15X15 device */
#define SBL_LIB_APP_IMAGE_DDR_ADDRESS_15X15     (0x98000000U)
/* Whether to enable ECC for EMIF */
#define SBL_LIB_CONFIG_ENABLE_EMIF_ECC          (0)
/* EMIF start address */
#define SBL_LIB_CONFIG_EMIF_START_ADDR          (0x80000000U)
/* EMIF ECC start address for region 1 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR1_12X12 (0x0U)
/* EMIF ECC end address for region 1 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR1_12X12   (0x0U)
/* EMIF ECC start address for region 1 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR1_15X15 (0x8C800000U)
/* EMIF ECC end address for region 1 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR1_15X15   (0x8CCFFFFFU)
/* Define the range type of region 1 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_REG1_RANGE_TYPE_12X12 ( \
        EMIF_ECC_ADDR_RANGE_WITHIN)
/* Define the range type of region 1 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_REG1_RANGE_TYPE_15X15 ( \
        EMIF_ECC_ADDR_RANGE_WITHIN)
/* EMIF ECC start address for region 2 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR2_12X12 (0x0U)
/* EMIF ECC end address for region 2 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR2_12X12   (0x0U)
/* EMIF ECC start address for region 2 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_START_ADDR2_15X15 (0x90000000U)
/* EMIF ECC end address for region 2 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_END_ADDR2_15X15   (0x904FFFFFU)
/* Define the range type of region 2 for 12X12 device */
#define SBL_LIB_CONFIG_EMIF_ECC_REG2_RANGE_TYPE_12X12 ( \
        EMIF_ECC_ADDR_RANGE_WITHIN)
/* Define the range type of region 2 for 15X15 device */
#define SBL_LIB_CONFIG_EMIF_ECC_REG2_RANGE_TYPE_15X15 ( \
        EMIF_ECC_ADDR_RANGE_WITHIN)
/* EMIF Size for 12X12 silicon: Half of total LPDDR2 size i.e. 32 MB */
#define SBL_LIB_CONFIG_EMIF_SIZE_12X12          (0x02000000U)
/* EMIF Size for 15X15 silicon i.e. 512 MB */
#define SBL_LIB_CONFIG_EMIF_SIZE_15X15          (0x20000000U)
/* OPP_HIGH DSP 750 MHz Enable Macro : Should be set to 1 to make sure
 * EVE VID DSP PLL is configured for DSP to be at 750 MHz. Please understand
 * in this mode the EVE VID DSP PLL can only be configured for 74.5 MHz and
 * 149 MHz VID_PIX clock.
 */
#define SBL_LIB_CONFIG_DSP_OPP_HIGH_750MHZ      (0U)
#endif

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

