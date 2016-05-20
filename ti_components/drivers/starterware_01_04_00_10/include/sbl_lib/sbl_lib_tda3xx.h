/**
 *  \file     sbl_lib_tda3xx.h
 *
 *  \brief    This file contains the interfaces present in the
 *            Secondary Bootloader(SBL) Library valid only for TDA3xx platform.
 *            This also contains some related macros, structures and enums.
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

#ifndef SBL_LIB_TDA3XX_H_
#define SBL_LIB_TDA3XX_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "tesoc.h"
#include "crc.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * \brief  This macro contains the maximum number of MPU cores where each
 *         dual core MPU subsystem is counted as two cores.
 */
#define SBLLIB_MAX_MPU_CORES                            ((uint32_t) 0U)

/**
 * \brief  This macro contains the maximum number of IPU cores where each
 *         dual core IPU subsystem is counted as two cores.
 */
#define SBLLIB_MAX_IPU_CORES                            ((uint32_t) 2U)

/**
 * \brief  This macro contains the maximum number of DSP cores.
 */
#define SBLLIB_MAX_DSP_CORES                            ((uint32_t) 2U)

/**
 * \brief  This macro contains the maximum number of EVE cores.
 */
#define SBLLIB_MAX_EVE_CORES                            ((uint32_t) 1U)

/**
 * \brief  This macro contains the IPU1 Core1's boot address when there is no
 *         App Image for IPU1 Core1.
 */
#define SBLLIB_IPU1_CORE1_BOOT_ADDRESS_NO_IMAGE        ((uint32_t) 0x80000201U)

/**
 * \brief  This macro contains the Address where IPU1 Core1 Entry Point is
 *         written and read.
 */
#define SBLLIB_IPU1_CORE_1_ENTRY_POINT_ADDRESS         ((uint32_t) 0x00300180U)

/**
 * \brief  This typedef contains the prototype of SBL function used for
 *         calculating CRC.
 *
 * \param   srcAddr      Source address of data for which CRC is calculated
 * \param   crcDataSize  Size of the CRC Data
 * \param   crcSignVal   Value of CRC Signature
 *
 * \return  status       Whether CRC is calculated successfully
 *                       STW_SOK   : Success
 *                       STW_EFAIL : Failure
 */
typedef int32_t (*SBLLibCalculateCRCFxn)(const void     *srcAddr,
                                         uint32_t        crcDataSize,
                                         crcSignature_t *crcSignVal);

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
 * \brief   This function runs the TESOC test for the selected test ID. It
 *          powers down the test module's clock domain and starts the TESOC
 *          test.
 *
 * \param   testId          Test ID for which TESOC test should be run.
 *                          Refer enum #tesocTestId_t for values.
 * \param   tesocTestConfig TESOC test configuration.
 *
 * \return  status          Whether TESOC test is configured and started
 *                          correctly.
 *                          STW_SOK         : Success
 *                          STW_EFAIL       : Failure
 *
 * \note    The application should configure TESOC's clock, dividers, etc.
 *          appropriately so that TESOC test runs correctly.
 */
int32_t SBLLibRunTesocTest(uint32_t              testId,
                           const tesocTestCfg_t *tesocTestConfig);

/**
 * \brief   This API checks the result of last run TESOC test. It reads TESOC
 *          registers to get the result value and there is only one set of
 *          registers in TESOC IP. Thus this API is dependent on last run TESOC
 *          test.
 *
 * \param   tesocTestConfig TESOC test configuration.
 *
 * \return  result          TESOC test result.
 *                          STW_SOK         : Test Passed.
 *                          STW_EFAIL       : Test Failed.
 *
 * \note    The test configuration should be exactly same as the one used for
 *          running TESOC test.
 */
int32_t SBLLibCheckTesocTestResult(const tesocTestCfg_t *tesocTestConfig);

/**
 * \brief   This function registers the CRC calculation callback function which
 *          is used for checking integrity of multi-core App image.
 *
 * \param   calculateCRCFxn Function for calculating CRC
 *
 * \return  status       Whether call back function is assigned correctly
 *                       STW_SOK   : Success
 *                       STW_EFAIL : Failure
 */
int32_t SBLLibRegisterCRCCallback(SBLLibCalculateCRCFxn calculateCRCFxn);

#ifdef __cplusplus
}

#endif

#endif

