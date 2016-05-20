/**
 *  \file     sbl_utils_tda3xx.h
 *
 *  \brief    This file contains the SBL Utility layer specific to TDA3xx
 *            platform. This also contains some related macros, structures and
 *            enums.
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

#ifndef SBL_UTILS_TDA3XX_H_
#define SBL_UTILS_TDA3XX_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "crc.h"

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
 * \brief   This function wakes up IPU1 Core1. Core1 is held in WFE by RBL.
 *          To wakeup core1 SEV instruction is sent from master core.
 *
 * \param   startAddr       Address at which Core1 starts executing.
 *
 * \return  None.
 */
void SBLUtilsWakeUpIPU1Core1(uint32_t startAddr);

/**
 * \brief   This function enables the IPU1's Uni-cache.
 *
 * \param   None.
 *
 * \return  None.
 */
void SBLUtilsEnableIPU1Unicache(void);

/**
 * \brief   This function computes the CRC of TESOC ROM used for IPU TESOC
 *          tests.
 *
 * \param   crcSignVal      CRC Signature value.
 *
 * \return  status          CRC signature calculation status.
 *                          STW_SOK   : Signature is calculated successfully
 *                          STW_EFAIL : Failed to calculate signature
 */
int32_t SBLUtilsComputeIPUTesocROMCRC(crcSignature_t *crcSignVal);

/**
 * \brief   This function computes the CRC of the given data.
 *
 * \param   crcSrcAddr   Source Address of data for which CRC is calculated.
 * \param   crcDataSize  CRC Data Size.
 * \param   crcSignVal   CRC Signature value.
 *
 * \return  status       CRC signature calculation status.
 *                       STW_SOK   : Signature is calculated successfully
 *                       STW_EFAIL : Failed to calculate signature
 *
 * \note    This API does not initialize and de-initialize the EDMA. This
 *          should be taken care by caller.
 */
int32_t SBLUtilsComputeCRC(const void     *crcSrcAddr,
                           uint32_t        crcDataSize,
                           crcSignature_t *crcSignVal);

/**
 * \brief   This function does the IPU1's default AMMU Configuration.
 *
 * \param   None.
 *
 * \return  None.
 */
void SBLUtilsConfigIPU1DefaultAMMU(void);

/**
 * \brief   This function evicts the IPU1's Uni-cache.
 *
 * \param   None.
 *
 * \return  None.
 */
void SBLUtilsEvictIPU1Unicache(void);

/**
 * \brief   This function disables the IPU1's Uni-cache.
 *
 * \param   None.
 *
 * \return  None.
 */
void SBLUtilsDisableIPU1Unicache(void);

/**
 * \brief   This function invalidates the IPU1's Uni-cache.
 *
 * \param   None.
 *
 * \return  None.
 */
void SBLUtilsInvalidateIPU1Unicache(void);

/**
 * \brief   This function disable the AMMU configuration for large pages that
 *          was done by SBL.
 *
 * \param   None.
 *
 * \return  None.
 */
void SBLUtilsDisableIPU1AMMU(void);

/**
 * \brief   This function configures and enables the EMIF ECC using parameters
 *          from SBL config file.
 *
 * \param   None.
 *
 * \return  status       ECC enable status.
 *                       STW_SOK   : ECC enabled successfully
 *                       STW_EFAIL : Failed to enable ECC
 */
int32_t SBLUtilsEmifECCConfigure(void);

/**
 * \brief   This function configures the source for DSP and EVE clocks
 *          based on the package type and opp.
 *
 * \param   oppId       Index giving the choice of Operating point.
 * \param   packageType Parameter indicates if this is a 15x15 or a 12x12
 *                      package.
 *
 * \return  status       Multiplexer configuration status.
 *                       STW_SOK   : Multiplexer configured successfully
 *                       STW_EFAIL : Failed to configure multiplexer
 *
 */
int32_t SBLUtilsConfigureDspEveMux(uint32_t oppId,
                                   uint32_t siliconPackageType);

#ifdef __cplusplus
}

#endif

#endif

