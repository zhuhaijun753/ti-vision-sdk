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
/**
 *  \defgroup ECC_STARTERWARE_API ECC Starterware DAL API
 *
 *  @{
 */

/*
 *  \file   stw_platformEcc.h
 *
 *  \brief  ECC API declarations for DSP Internal memory (L1P and L2) ECC
 *
 *   This file contains the API prototypes for DSP Internal memory (L1P and L2)
 *   ECC.
 */

#ifndef STW_PLATFORM_ECC_H_
#define STW_PLATFORM_ECC_H_

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
**                       MACRO DEFINITIONS
****************************************************************************/

/** \brief Macro to Enable ECC */
#define ECC_ENABLE                 (0x1U)
/** \brief Macro to DISABLE ECC */
#define ECC_DISABLE                (0x0U)

#if defined (BUILD_DSP)
/**
 *  \brief    Enumerates the values used to represent DSP ECC Memory types
 */
typedef enum eccDspMemType
{
    ECC_DSP_MEM_TYPE_L2 = 0x1U,
    /**<  DSP L2 RAM/Cache ECC Memory Type*/
    ECC_DSP_MEM_TYPE_L1P = 0x2U
                           /**<  DSP L1P RAM/Cache ECC Memory Type*/
} eccDspMemType_t;
#endif

/*****************************************************************************
**                     STRUCTURE DEFINITIONS
*****************************************************************************/

#if defined (BUILD_DSP)
/** \brief Structure holding ECC configuration parameters of DSP L2 EDC
 */
typedef struct eccDspL2CfgPrm
{
    uint32_t l1DCacheReadEccEn;
    /**< 1: Enables EDC on L1D memory controller reads from an external
     *      address (Hits L2 cache) if L2EDCMD.EN = 1.
     *   0: Disables EDC on L1D memory controller reads from an external
     *      address (Hits L2 cache)
     */
    uint32_t l1PCacheReadEccEn;
    /**< 0: Disables EDC on L1P memory controller reads from an external
     *      address (Hits L2 cache)
     *   1: Enables EDC on L1P memory controller reads from an external
     *      address (Hits L2 cache) if L2EDCMD.EN = 1
     */
    uint32_t l1DRamReadEccEn;
    /**< 0: Disables EDC on L1D memory controller read from L2 RAM
     *   1: Enables EDC on L1D memory controller read from L2 RAM
     *      (if L2EDCMD.EN = 1)
     */
    uint32_t l1PRamReadEccEn;
    /**< 0: Disables EDC on L1P memory controller read from L2 RAM
     *   1: Enables EDC on L1P memory controller read from L2 RAM (
     *      if L2EDCMD.EN = 1)
     */
    uint32_t sdmaReadEccEn;
    /**< 0: Disables EDC on SDMA read from L2 RAM
     *   1: Enables EDC on SDMA read from L2 RAM (if L2EDCMD.EN = 1).
     *   This includes RAM under cache.
     */
} eccDspL2CfgPrm_t;

/** \brief Structure holding DSP ECC Error status.
 */
typedef struct eccDspErrStatus
{
    uint32_t l1PProgramFetchErr;
    /**< L1P Mem: A program fetch resulted in a parity check error */
    uint32_t l1PDmaAccessErr;
    /**< L1P Mem: A DMA/IDMA access to L1P memory resulted in a parity
     *            check error.
     */
    uint32_t l2L1DAccessErr;
    /**< L2 Mem: Parity error occurred during L1D data access */
    uint32_t l2L1PAccessErr;
    /**< L2 Mem: Parity error occurred during L1P access */
    uint32_t l2DmaAccessErr;
    /**< L2 Mem: Parity error occurred during DMA access */
    uint32_t l2VictimsErr;
    /**< L2 Mem: Parity error occurred on L2 victims */
} eccDspErrStatus_t;

/** \brief Structure holding the DSP ECC Error Information.
 */
typedef struct eccDspErrInfo
{
    uint32_t errAddress;
    /**< L1P and L2: Contains the upper 27 bit of error location. */
    uint32_t errRamOrCache;
    /**< L1P and L2: 0: Error detected in L1P/L2 cache
     *               1: Error detected in L1P/L2 RAM
     */
    uint32_t errL2BitPosition;
    /**< L2 only:   0: Bit Position = 0
     *              1: Bit Position = 1
     *              ...
     *              255: Bit Position = 255
     *   L1P : Value returned is always 0
     */
    uint32_t errL2Type;
    /**< L2 Only :   0: Single Bit Error
     *               1: Double Bit Error
     *               3: Error in parity value, data is correct
     *               2: Reserved
     *   L1P : Value returned is always 0
     */
    uint32_t errL2way;
    /**< L2 Only :
     *               00: Error detected in Way 0 of L2 cache
     *               01: Error detected in Way 1 of L2 cache
     *               10: Error detected in Way 2 of L2 cache
     *               11: Error detected in Way 3 of L2 cache
     *               (Note: L2WAY = 00 when RAM = 1)
     *   L1P : Value returned is always 0
     */
    uint32_t errL2CorrectableCount;
    /**< Correctable Parity Error Count */
    uint32_t errL2NonCorrectableCount;
    /**< Non-Correctable Parity Error count */
} eccDspErrInfo_t;
#endif

/*****************************************************************************
**                     API FUNCTION PROTOTYPES
*****************************************************************************/

#if defined (BUILD_DSP)
/**
 * \brief   This function initializes the software structure to configure the
 *          DSP L2 ECC L2EDCEN register.
 *
 * \param   eccDspL2Param   Pointer to the structure to hold the L2 EDC/ECC
 *                          configuration. Refer #eccDspL2CfgPrm_t for details
 *                          on the structure fields.
 *
 * \return  STW_SOK on success else STW_EFAIL
 */
int32_t ECCDspL2CfgPrm_init(eccDspL2CfgPrm_t *eccDspL2Param);

/**
 * \brief   This function configures the DSP L2 ECC L2EDCEN register. The
 *          function to initialize the structure is #ECCDspL2CfgPrm_init.
 *
 * \param   eccDspL2Param   Pointer to the structure to hold the L2 ECC/EDC
 *                          configuration. Refer #eccDspL2CfgPrm_t for details
 *                          on the structure.
 *
 * \return  STW_SOK on success else STW_EFAIL
 */
int32_t ECCDspL2Configure(const eccDspL2CfgPrm_t *eccDspL2Param);

/**
 * \brief   This function enables or disables EDC/ECC for L1P or L2 DSP
 *          memories.
 *
 * \param   memType         DSP ECC memory type. This parameter can take any of
 *                          following values:
 *                          ECC_DSP_MEM_TYPE_L2  - DSP L2 ECC/EDC
 *                          ECC_DSP_MEM_TYPE_L1P - DSP L1P ECC/EDC
 * \param   eccEnable       Flag to indicate whether to enable or disable
 *                          EDC/ECC. It can take any of the two values:
 *                          ECC_ENABLE - To enable EDC/ECC
 *                          ECC_DISABLE - To disable EDC/ECC
 * \param   timeout         Time to wait for the ECC/EDC to get ENABLED/DISABLED
 *
 * \return  STW_SOK on success else STW_EFAIL
 */
int32_t ECCDspEnable(uint32_t memType, uint32_t eccEnable, uint32_t timeout);
/**
 * \brief   This function suspends the EDC/ECC for L1P or L2 DSP
 *          memories.
 *
 * \param   memType         DSP ECC memory type. This parameter can take any of
 *                          following values:
 *                          ECC_DSP_MEM_TYPE_L2  - DSP L2 ECC/EDC
 *                          ECC_DSP_MEM_TYPE_L1P - DSP L1P ECC/EDC
 * \param   timeout         Time to wait for the ECC/EDC to get SUSPENDED
 *
 * \return  STW_SOK on success else STW_EFAIL
 */
int32_t ECCDspSuspend(uint32_t memType, uint32_t timeout);

/**
 * \brief   This function reads the error status of both L1P and L2 EDC/ECC.
 *
 * \param   errStatus       Holds the values of which error got set. Refer
 *                          #eccDspErrStatus_t for more details. If the value
 *                          of any field is read as 1 the corresponding ECC
 *                          error has occurred.
 *
 * \return  STW_SOK on success else STW_EFAIL
 */
int32_t ECCDspIntrGetErrStatus(eccDspErrStatus_t *errStatus);

/**
 * \brief   This function clears the error status of both L1P and L2 EDC/ECC.
 *
 * \param   errClr          Holds the values of which error need to be cleared.
 *                          Refer #eccDspErrStatus_t for more details.
 *                          A value of 1 is written to fields that need to be
 *                          cleared and 0 for those that need not be cleared.
 *
 * \return  STW_SOK on success else STW_EFAIL
 */
int32_t ECCDspIntrClrErrStatus(const eccDspErrStatus_t *errClr);

/**
 * \brief   This function reads the details of the ECC errors for a particular
 *          DSP memory.
 *
 * \param   memType         DSP ECC memory type. This parameter can take any of
 *                          following values:
 *                          ECC_DSP_MEM_TYPE_L2  - DSP L2 ECC/EDC
 *                          ECC_DSP_MEM_TYPE_L1P - DSP L1P ECC/EDC
 * \param   eccDspInfo      Structure to hold the details of the ECC/EDC error
 *                          generated at L1P or L2. Refer #eccDspErrInfo_t for
 *                          which fields apply to L1P and which to L2 and their
 *                          meaning.
 *
 * \return  STW_SOK on success else STW_EFAIL
 */
int32_t ECCDspGetErrInfo(uint32_t memType, eccDspErrInfo_t *eccDspInfo);
#endif

#ifdef __cplusplus
}
#endif
#endif /* #ifndef STW_PLATFORM_ECC_H_ */

/* @} */
