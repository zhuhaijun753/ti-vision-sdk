/**
 *  \file  ipu_ecc.h
 *
 *  \brief This file contains the API prototypes for configuring ECC for
 *         ARM Cortex-M4
 *
 *  \copyright Copyright (C) 2015 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

/* =============================================================================
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
 * ===========================================================================*/

#ifndef IPU_ECC_H
#define IPU_ECC_H

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

/** \brief Macros that can be used to clear different types of Errors in IPU
 *         L2RAM / L1Data / L1Tag Error Info
 */

/** \brief IPU L2RAM / L1Data / L1Tag Memory 1 bit ECC Error  */
#define ECC_IPU_ERR_ONEBIT    (0x1U)
/** \brief IPU L2RAM / L1Data / L1Tag Memory 2 bit ECC Error  */
#define ECC_IPU_ERR_TWOBIT    (0x4U)
/** \brief IPU L2RAM / L1Data / L1Tag Memory ECC Error in Code Area  */
#define ECC_IPU_ERR_CODE      (0x2U)
/** \brief IPU L2RAM / L1Data / L1Tag Memory
 *         All ECC Error : 1bit, 2bit and code ecc error  */
#define ECC_IPU_ERR_ALL       (0x8U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *  \brief    Enumerates the values used to represent IPU ECC Memory types
 */
typedef enum eccIpuMemType
{
    ECC_IPU_MEM_TYPE_L2RAM = 0x1U,
    /**<  IPU L2RAM ECC Memory Type*/
    ECC_IPU_MEM_TYPE_L1DATA = 0x2U,
    /**<  IPU L1DATA ECC Memory Type*/
    ECC_IPU_MEM_TYPE_L1TAG = 0x4U
                             /**<  IPU L1TAG ECC Memory Type*/
} eccIpuMemType_t;

/** \brief Structure holding error information of IPU L2 RAM / L1 Data
 */
typedef struct eccIpuMemErrInfo
{
    uint32_t errBitLoc;
    /**<  Error Bit location of IPU L2 RAM / L1 Data / L1 Tag when 1 Bit Error
     *    occurs
     *    Valid only for 1 bit Error
     */
    uint32_t errAddr;
    /**<  Address of IPU L2 RAM / L1 Data / L1 Tag when 1bit or 2 bit ECC error
     *    occurs
     */
} eccIpuMemErrInfo_t;

/** \brief Structure holding ECC configuration parameters of
 *         IPU L2RAM /L1Data / L1TAG Memory
 */
typedef struct eccIpuMemCfgPrm
{
    uint32_t errAutoCorrectEnable;
    /**<  To Enable/Disable auto correction when 1 Bit error occurs in
     *    IPU L2RAM /L1DATA / L1TAG Memory. Valid values: TRUE or FALSE */
    uint32_t errIntrEnable;
    /**<  To Enable/Disable error interrupt when 2 Bit error occurs in
     *    IPU L2RAM /L1DATA/L1TAG Memory. Valid values: TRUE or FALSE */
    uint32_t dataMaskEnable;
    /**<  To Enable/Disable data Mask in IPU L2RAM /L1DATA / L1TAG Memory
     *     Valid values: TRUE or FALSE */
    uint32_t eccCodeMaskEnable;
    /**<  To Enable/Disable ECC code Mask in IPU L2RAM / L1DATA / L1TAG Memory
     *    Valid values: TRUE or FALSE */
    uint32_t memType;
    /**<  ECC IPU Memory Type. For valid values refer enum #eccIpuMemType_t */
} eccIpuMemCfgPrm_t;


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This function configures ECC configuration parameters for
 *          IPU L2RAM /L1Data / L1TAG Memory
 *
 * \param   baseAddr          Base address for IPU_UNICACHE_CFG register
 *
 * \param   pCfgPrm           Pointer which holds ECC configuration parameters
 *                            for IPU L2RAM /L1Data / L1TAG Memory. Refer
 *                            #eccIpuMemCfgPrm_t for details on the structure.
 *
 * \return  None
 */
void ECCIPUMemConfig(uint32_t                 baseAddr,
                     const eccIpuMemCfgPrm_t *pCfgPrm);

/**
 * \brief   This function will enable/disable ECC in IPU L2RAM / L1DATA / L1TAG
 *          Memory for the defined ECC IPU Memory type
 *
 * \param   baseAddr            Base address for IPU_UNICACHE_CFG register
 *
 * \param   eccEnable           To Enable/Disable ECC in IPU L2RAM / L1DATA /
 *                              L1TAG Memory
 *                              Valid values: TRUE or FALSE
 * \param   memType             ECC IPU Memory Type
 *                              For valid values refer enum #eccIpuMemType_t
 *
 * \return  None
 */
void ECCIPUMemEnableEcc(uint32_t baseAddr,
                        uint32_t eccEnable,
                        uint32_t memType);

/**
 * \brief   This function will return IPU L2RAM / L1DATA / L1TAG Memory
 *          Error status when 1 Bit or 2 Bit Error occurs for the defined
 *          ECC IPU Memory type
 *
 * \param   baseAddr         Base address for IPU_UNICACHE_CFG register
 *
 * \param   memType          ECC IPU Memory Type
 *                           For valid values refer enum #eccIpuMemType_t
 *
 * \return  Returns the IPU L2RAM / L1DATA / L1TAG Memory Error status when
 *          1 Bit or 2 Bit Error occurs
 */
uint32_t ECCIPUMemGetErrStatus(uint32_t baseAddr, uint32_t memType);

/**
 * \brief   This function will clear error status of the defined
 *          ECC Error for the defined ECC IPU Memory type
 *
 * \param   baseAddr         Base address for IPU_UNICACHE_CFG register
 *
 * \param   eccErrType       IPU L2RAM / L1DATA / L1TAG Memory Ecc Error Type
 *
 * \param   memType          ECC IPU Memory Type
 *                           For valid values refer enum #eccIpuMemType_t
 *
 * \return  None
 */
void ECCIPUMemClrErrStatus(uint32_t baseAddr,
                           uint32_t eccErrType,
                           uint32_t memType);

/**
 * \brief   This function will return the IPU L2RAM / L1DATA / L1TAG Memory
 *          error information when 1 Bit or 2 Bit Error occurs for the defined
 *          ECC IPU Memory type
 *
 * \param   baseAddr       Base address for IPU_UNICACHE_CFG register
 *
 * \param   pErrInfo       Pointer which hold Error information when 1 Bit or
 *                         2 Bit Error occurs
 *
 * \param   memType        ECC IPU Memory Type
 *                         For valid values refer enum #eccIpuMemType_t
 *
 * \return  STW_SOK on success else STW_EFAIL
 */
int32_t ECCIPUMemGetErrInfo(uint32_t            baseAddr,
                            eccIpuMemErrInfo_t *pErrInfo,
                            uint32_t            memType);

#ifdef __cplusplus
}
#endif
#endif
