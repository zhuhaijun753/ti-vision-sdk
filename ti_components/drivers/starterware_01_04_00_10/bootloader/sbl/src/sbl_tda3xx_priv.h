/**
 *  \file     sbl_tda3xx_priv.h
 *
 *  \brief    This file contains the platform specific private layer of
 *            Secondary Bootloader(SBL) for tda3xx.
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

#ifndef SBL_TDA3XX_PRIV_H_
#define SBL_TDA3XX_PRIV_H_

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

/**
 * \brief  This macro contains the IPU MBIST data address depending on the boot
 *         mode.
 */
#if defined (BOOTMODE_NOR)
#define SBL_IPU_MBIST_DATA_ADDRESS                      ((uint32_t) 0x08060000U)
#else
#define SBL_IPU_MBIST_DATA_ADDRESS                      ((uint32_t) 0x5C060000U)
#endif

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
 * \brief   This function does the PAD configuration for TI EVM.
 *
 * \param   None.
 *
 * \return  None.
 */
void SBLConfigTIEVMPad(void);

/**
 * \brief   This function copies the App Image from corresponding source
 *          depending on Boot Mode.
 *
 * \param   imageParams  Multi-core Application Image Parse Parameters.
 *                       Refer struct #sbllibAppImageParseParams_t for
 *                       details.
 *
 * \return  status       Whether Image is copied correctly
 *                       SUCCESS : Success
 *                       FAIL : Failure
 */
int32_t SBLLoadAppImage(sbllibAppImageParseParams_t *imageParams);

/**
 * \brief   This function returns the OPP ID for which the SBL has been
 *          compiled for a given package type.
 *
 * \param   packageType Parameter indicates if this is a 15x15 or a 12x12
 *                      package.
 *
 * \return  oppId       The OPP ID for which the SBL has been compiled is
 *                      returned.
 *
 * \note    12x12 package supports only OPP_NOM currently.
 */
uint32_t SBLGetOppId(uint32_t packageType);

#ifdef __cplusplus
}

#endif

#endif

