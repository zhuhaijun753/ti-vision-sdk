/**
 *  \file     sbl_tda3xx_priv.c
 *
 *  \brief    This file contains the private API layer specific to the SBL
 *            application.
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include "common/stw_types.h"
#include "soc_defines.h"
#include "sbl_tda3xx_priv.h"
#include "sbl_lib/sbl_lib.h"
#include "sbl_lib_config.h"
#include "sbl_utils/sbl_utils_common.h"
#include "platform.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** OPP Configuration*/
#define SBL_OPP_LOW                   (0)
#define SBL_OPP_NOM                   (1)
#define SBL_OPP_OD                    (2)
#define SBL_OPP_HIGH                  (3)

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

void SBLConfigTIEVMPad(void)
{
#if defined (BOOTMODE_QSPI)
    PlatformQSPISetPinMux();
#elif defined (BOOTMODE_NOR)
    PlatformGPMCSetPinMux();
#elif defined (BOOTMODE_QSPI_SD)
    PlatformMMCSDSetPinMux(MMC4_INST);
#endif
    /* MMC and RGMII require same pins to be configured. Thus RGMII pin mux
     * configuration is done after copying App Image in QSPI_SD boot-mode
     */
#if !defined (BOOTMODE_QSPI_SD)
    PlatformRGMIISetPinMux();
#endif
}

int32_t SBLLoadAppImage(sbllibAppImageParseParams_t *imageParams)
{
    int32_t retVal = STW_SOK;
    #if defined (BOOTMODE_QSPI)
    retVal = SBLUtilsQspiBootRprc(imageParams);
    #elif defined (BOOTMODE_NOR)
    retVal = SBLUtilsNorBootRprc(imageParams);
    #elif defined (BOOTMODE_QSPI_SD)
    retVal = SBLUtilsQspiSDBootRprc(imageParams);
    #else
    #error Unsupported Boot Mode!!
    #endif
    return retVal;
}

uint32_t SBLGetOppId(uint32_t packageType)
{
    /* Default value is OPP_NOM */
    uint32_t oppId = SBLLIB_PRCM_DPLL_OPP_NOM;
    if (packageType == PLATFORM_SILICON_PACKAGE_TYPE_15X15)
    {
#if (OPP_MODE == SBL_OPP_HIGH)
    #if (SBL_LIB_CONFIG_DSP_OPP_HIGH_750MHZ == 0U)
        SBLLibPrintf(
            SBLLIB_TRACE_LEVEL_IMP_INFO,
            "\n SBL_LIB_CONFIG_DSP_OPP_HIGH_750MHZ != 1: Falling back to OPP_OD \n");
        oppId = SBLLIB_PRCM_DPLL_OPP_OD;
    #else
        oppId = SBLLIB_PRCM_DPLL_OPP_HIGH;
    #endif
#elif (OPP_MODE == SBL_OPP_OD)
        oppId = SBLLIB_PRCM_DPLL_OPP_OD;
#else
        oppId = SBLLIB_PRCM_DPLL_OPP_NOM;
#endif
    }
    else
    {
        /* 12x12 TDA3xx packageType currently supports only OPP_NOM */
        oppId = SBLLIB_PRCM_DPLL_OPP_NOM;
    }
    return oppId;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */
