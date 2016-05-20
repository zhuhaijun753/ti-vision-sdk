/**
 *  \file     emif.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            device abstraction layer file of EMIF.
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

#ifndef EMIF_H_
#define EMIF_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "hw_emif.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ==========================================================================
 * *//**
 * \brief  Macro defines mask for all the interrupts status for EMIF.
 */
#define EMIF_INTR_STATUS_ALL     (                                 \
        EMIF_SYSTEM_OCP_INTERRUPT_STATUS_WR_ECC_ERR_SYS_MASK |     \
        EMIF_SYSTEM_OCP_INTERRUPT_STATUS_TWOBIT_ECC_ERR_SYS_MASK | \
        EMIF_SYSTEM_OCP_INTERRUPT_STATUS_ONEBIT_ECC_ERR_SYS_MASK | \
        EMIF_SYSTEM_OCP_INTERRUPT_STATUS_ERR_SYS_MASK)

/**
 * \brief  Macro defines mask for all the interrupts to enable for EMIF.
 */
#define EMIF_INTR_ENABLE_ALL     (                                     \
        EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_EN_ERR_SYS_MASK |         \
        EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_WR_ECC_ERR_SYS_MASK |     \
        EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_TWOBIT_ECC_ERR_SYS_MASK | \
        EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_ONEBIT_ECC_ERR_SYS_MASK)

/**
 * \brief  Macro defines mask for all the interrupts to disable for EMIF.
 */
#define EMIF_INTR_DISABLE_ALL    (                                       \
        EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR_EN_ERR_SYS_MASK |         \
        EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR_WR_ECC_ERR_SYS_MASK |     \
        EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR_TWOBIT_ECC_ERR_SYS_MASK | \
        EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR_ONEBIT_ECC_ERR_SYS_MASK)

/**
 * \brief  Macro defines mask for all the interrupts for EMIF.
 */
#define EMIF_INTR_ALL             (EMIF_INTR_STATUS_ALL)

/** \brief Number of ECC Protected Adrress range in EMIF Module */
#define EMIF_ECC_PROTECTED_NUM_ADDR_RANGE     (0x2)

/** \brief Internal FIFO Buffer with depth of 4 which can store corrected error
 *         address or non correctable error address
 *         This fifo can store only first 4 error address.To store the 5th
 *         error address. Writing 0x1 will pop one element of the FIFO to error
 *         address register ,clearing 0th address in FIFO & then we can store
 *         next new error addresss in FIFO else will miss the error address log
 *         i.e., Overflow occurs when the num ECC Err is more than
 *         EMIF_ECC_FIFO_BUF_SIZE
 */
#define EMIF_ECC_FIFO_BUF_SIZE                (0x4U)

/** \brief Macro to Enable EMIF ECC */
#define EMIF_ECC_ENABLE                 (0x1U)
/** \brief Macro to DISABLE EMIF ECC */
#define EMIF_ECC_DISABLE                (0x0U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *  \brief    Enumerates the values used to represent ECC EMIF protected address
 *            ranges
 */
typedef enum emifEccAddrRangeNum
{
    EMIF_ECC_ADDR_RANGE_NUM_1,
    /**< First ECC EMIF protected address range */
    EMIF_ECC_ADDR_RANGE_NUM_2
    /**< Second ECC EMIF protected address range */
} emifEccAddrRangeNum_t;

/**
 *  \brief    Enumerates the values used to represent ECC EMIF ECC protected
 *            address ranges within/outside defined address range
 */
typedef enum emifEccAddrRangeType
{
    EMIF_ECC_ADDR_RANGE_OUTSIDE,
    /**<  ECC protected address range outside defined address range of EMIF*/
    EMIF_ECC_ADDR_RANGE_WITHIN
    /**<  ECC protected address range within defined address range of EMIF*/
} emifEccAddrRangeType_t;

/**
 * \brief  Enum for EMIF interrupts.
 */
typedef enum emifIntrSrc
{
    EMIF_INTR_SRC_CMD_ADDR_ERR = \
        EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_EN_ERR_SYS_MASK,
    /**< Command or Address Error interrupt */
#ifdef TDA3XX_BUILD
    EMIF_INTR_SRC_TEMP_ALERT_ERR = \
        EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_TA_SYS_MASK,
    /**< Temperature Alert Error interrupt */
#endif
    EMIF_INTR_SRC_WR_ECC_ERR = \
        EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_WR_ECC_ERR_SYS_MASK,
    /**< Non Quanta aligned Memory access ECC Error interrupt */
    EMIF_INTR_SRC_TWOBIT_ECC_ERR = \
        EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_TWOBIT_ECC_ERR_SYS_MASK,
    /**< Two Bit ECC Error interrupt */
    EMIF_INTR_SRC_ONEBIT_ECC_ERR = \
        EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_ONEBIT_ECC_ERR_SYS_MASK
        /**< One Bit ECC Error interrupt */
}emifIntrSrc_t;

/**
 *  \brief    Enumerates the values used to represent different types of ECC
 *            Errors in EMIF Module
 */
typedef enum emifEccErrType
{
    EMIF_ERR_ECC_ONEBIT = 0x1U,
    /**< EMIF 1 bit ECC Error */
    EMIF_ERR_ECC_TWOBIT = 0x2U,
    /**< EMIF 2 bit ECC Error */
    EMIF_ERR_ECC_NONQUANTA = 0x3U
                             /**< EMIF ECC Error for When a non-quanta
                              *memory/data access */
} emifEccErrType_t;

/** \brief Structure holding error information of EMIF
 */
typedef struct emifEccErrInfo
{
    uint32_t errBitLoc;
    /**<  Error Bit location of EMIF when 1 Bit Error occurs
     *    Valid only for 1 bit Error
     */
    uint32_t errCnt;
    /**<  As per hardware, it represent Error count for 1 Bit Errors. ErrCnt
     *    could be more than ECC_EMIF_FIFO_BUF_SIZE in case of overflow. And
     *    user can check overflow if this count is greater that numValidErrAddr
     */
    uint32_t numValidErrAddr;
    /**<  Number of Valid ECC Error Address */
    uint32_t errAddr[EMIF_ECC_FIFO_BUF_SIZE];
    /**<  Address offset of EMIF when 1 bit or 2 bit or non-quanta ECC error
     *    Occurs.
     */
} emifEccErrInfo_t;

/** \brief Structure holding ECC Protected Address range configuration
 *          parameters of EMIF
 */
typedef struct emifEccAddrRangeCfgPrm
{
    uint32_t startAddr;
    /**<  Start Adddress for ECC Protected Address which is of 16bit aligned
     *    such as 0x90000000 but not the MSB offset address as EMIF module
     *    expected for ECC protected address such as 0x1000 i.e.,
     *    ((0x90000000 >> 16) - (0x80000000 >> 16)) where 0x80000000 is
     *     EMIF Start address which is done in code
     */
    uint32_t endAddr;
    /**<  End Adddress for ECC Protected Address which is of 16bit aligned
     *    such as 0x9FFFFFFF but not the MSB offset address as EMIF module
     *    expected for ECC protected address such as 0x1FFF i.e.,
     *    ((0x9FFFFFFF >> 16) - (0x80000000 >> 16)) where 0x80000000 is
     *     EMIF Start address which is done in code
     */
    uint32_t addrRangeNum;
    /**<  ECC protected address range number. For valid values refer
     *    enum #emifEccAddrRangeNum_t
     */
    uint32_t addrRangeType;
    /**<  ECC Address range Type . For valid values refer
     *    enum #eccEmifAddrRangeType_t
     */
    uint32_t enableAddrRange;
    /**<  Enable/Disable ECC for the defined address range */
} emifEccAddrRangeCfgPrm_t;

/** \brief Structure holding ECC configuration parameters of EMIF
 */
typedef struct emifEccCfgPrm
{
    uint32_t                  emifStartAddr;
    /**<  Start address of EMIF module*/
    emifEccAddrRangeCfgPrm_t *addrRangeCfgPrm;
    /**<  Configuration parameters for ECC Protected Address range
     */
    uint32_t                  thresholdVal;
    /**<  Threshold value to generate 1 bit error*/
} emifEccCfgPrm_t;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This function will intialize the ECC Protected Address range
 *          parameters and threshold for 1Bit Error of EMIF Module
 *
 * \param   baseAddr          Base address of EMIF module register
 *
 * \param   pCfgPrm           Pointer which holds ECC configuration parameters
 *                            of EMIF Module
 *
 * \return  STW_SOK on success else STW_EFAIL
 */
int32_t EMIFConfigECCInitECCParams(uint32_t               baseAddr,
                                   const emifEccCfgPrm_t *pCfgPrm);

/**
 * \brief   This function will enable ECC of EMIF Module
 *
 * \param   baseAddr            Base address of EMIF module register
 *
 * \return  None
 */
void EMIFConfigECCEnableEcc(uint32_t baseAddr);

/**
 * \brief   This function will disable ECC of EMIF Module
 *
 * \param   baseAddr            Base address of EMIF module register
 *
 * \return  None
 */
void EMIFConfigECCDisableEcc(uint32_t baseAddr);

/**
 * \brief   This API is used to enable interrupts.
 *
 * \param   baseAddr        Base Address of the EMIF module Registers.
 * \param   intrMask        Interrupts to enable.
 *                          Refer enum #emifIntrSrc_t.
 *
 * \return  None.
 */
void EMIFEnableIntr(uint32_t baseAddr, uint32_t intrMask);

/**
 * \brief   This API is used to disable interrupts.
 *
 * \param   baseAddr        Base Address of the EMIF module Registers.
 * \param   intrMask        Interrupts to disable.
 *                          Refer enum #emifIntrSrc_t.
 *
 * \return  None.
 */
void EMIFDisableIntr(uint32_t baseAddr, uint32_t intrMask);

/**
 * \brief   This API is used to get the pending interrupts.
 *
 * \param   baseAddr        Base Address of the EMIF module Registers.
 *
 * \return  status          Pending interrupt status/occurred.
 */
uint32_t EMIFGetIntrStatus(uint32_t baseAddr);

/**
 * \brief   This API is used to clear the interrupt status.
 *
 * \param   baseAddr        Base Address of the EMIF module Registers.
 * \param   intrMask        Interrupts to clear status.
 *                          Refer enum #emifIntrSrc_t.
 *
 * \return  None.
 */
void EMIFClearIntrStatus(uint32_t baseAddr, uint32_t intrMask);

/**
 * \brief   This API is used to get the raw interrupt status.
 *
 * \param   baseAddr        Base Address of the EMIF module Registers.
 *
 * \return  status          Pending interrupt status/occurred.
 */
uint32_t EMIFGetIntrRawStatus(uint32_t baseAddr);

/**
 * \brief   This function will return the EMIF ECC error information of the
 *          defined EMIF ECC Error
 *
 * \param   baseAddr      Base address of EMIF module register
 *
 * \param   errType       Value used to represent EMIF ECC Error
 *                        For valid values refer enum #emifEccErrType_t
 *
 * \param   pErrInfo      Pointer which hold Error information of the defined
 *                        EMIF ECC Error
 *                        For valid values refer enum #emifEccErrInfo_t
 *
 * \return  STW_SOK on success else STW_EFAIL
 */
int32_t EMIFConfigECCGetEccErrInfo(uint32_t          baseAddr,
                                   uint32_t          errType,
                                   emifEccErrInfo_t *pErrInfo);

/**
 * \brief   This function will clear all EMIF ECC error information
 *
 * \param   baseAddr       Base address of EMIF module register
 *
 * \return  None
 */
void EMIFConfigECCClrAllEccErrInfo(uint32_t baseAddr);

#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
