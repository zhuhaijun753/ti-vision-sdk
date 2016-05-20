/**
 *  \file   ipu_ecc.c
 *
 *  \brief  IPU ECC related APIs.
 *
 *   This file contains the APIs for configuring IPU_ECC
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include "stdint.h"
#include "ipu_ecc.h"
#include <common/stw_types.h>
#include <common/stw_dataTypes.h>
#include "hw_types.h"
#include "hw_ipu_unicache_cfg.h"

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

void ECCIPUMemConfig(uint32_t                 baseAddr,
                     const eccIpuMemCfgPrm_t *pCfgPrm)
{
    if ((pCfgPrm->memType & ECC_IPU_MEM_TYPE_L1DATA) ==
        ECC_IPU_MEM_TYPE_L1DATA)
    {
        /* To Enable/Disable auto correction when 1 Bit error occurs in IPU
         * L1DATA Memory */
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L1DATA_SEC_AUTO_EN,
                      pCfgPrm->errAutoCorrectEnable);
        /* To Enable/Disable error respose to master when 2 Bit error occurs in
         * IPU L1DATA Memory*/
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L1DATA_SRESP_EN,
                      pCfgPrm->errIntrEnable);
        /*To Enable/Disable IPU L1DATA Memory data mask*/
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L1DATA_DATA_MASK,
                      pCfgPrm->dataMaskEnable);
        /*To Enable/Disable IPU L1DATA Memory ECC code mask */
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L1DATA_CODE_MASK,
                      pCfgPrm->eccCodeMaskEnable);
    }
    else if ((pCfgPrm->memType & ECC_IPU_MEM_TYPE_L1TAG) ==
             ECC_IPU_MEM_TYPE_L1TAG)
    {
        /*To Enable/Disable auto correction when 1 Bit error occurs in IPU
         * L1TAG Memory */
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L1TAG_SEC_AUTO_EN,
                      pCfgPrm->errAutoCorrectEnable);
        /*To Enable/Disable error respose to master when 2 Bit error occurs in
         * IPU L1TAG Memory*/
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L1TAG_SRESP_EN,
                      pCfgPrm->errIntrEnable);
        /*To Enable/Disable IPU L1TAG Memory data mask*/
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L1TAG_DATA_MASK,
                      pCfgPrm->dataMaskEnable);
        /*To Enable/Disable IPU L1TAG Memory ECC code mask */
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L1TAG_CODE_MASK,
                      pCfgPrm->eccCodeMaskEnable);
    }
    else
    {
        /* To Enable/Disable auto correction when 1 Bit error occurs in IPU
         * L2RAM Memory */
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L2RAM_SEC_AUTO_EN,
                      pCfgPrm->errAutoCorrectEnable);
        /* To Enable/Disable error respose to master when 2 Bit error occurs in
         * IPU L2RAM Memory*/
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L2RAM_SRESP_EN,
                      pCfgPrm->errIntrEnable);
        /*To Enable/Disable IPU L2RAM Memory data mask*/
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L2RAM_DATA_MASK,
                      pCfgPrm->dataMaskEnable);
        /*To Enable/Disable IPU L2RAM Memory ECC code mask */
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L2RAM_CODE_MASK,
                      pCfgPrm->eccCodeMaskEnable);
    }
}

void ECCIPUMemEnableEcc(uint32_t baseAddr,
                        uint32_t eccEnable,
                        uint32_t memType)
{
    if ((memType & ECC_IPU_MEM_TYPE_L1DATA) == ECC_IPU_MEM_TYPE_L1DATA)
    {
        /*To Enable/ Disable ECC in IPU L1DATA*/
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L1DATA_EN,
                      eccEnable);
    }
    else if ((memType & ECC_IPU_MEM_TYPE_L1TAG) == ECC_IPU_MEM_TYPE_L1TAG)
    {
        /*To Enable/ Disable ECC in IPU L1TAG*/
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L1TAG_EN,
                      eccEnable);
    }
    else
    {
        /*To Enable/ Disable ECC in IPU L2RAM*/
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L2RAM_EN,
                      eccEnable);
    }
}

uint32_t ECCIPUMemGetErrStatus(uint32_t baseAddr, uint32_t memType)
{
    uint32_t eccErrStatus = 0;

    if ((memType & ECC_IPU_MEM_TYPE_L1DATA) == ECC_IPU_MEM_TYPE_L1DATA)
    {
        eccErrStatus = HW_RD_REG32(baseAddr + IPU_UNICACHE_L1DATA_ERR_INFO);
    }
    else if ((memType & ECC_IPU_MEM_TYPE_L1TAG) == ECC_IPU_MEM_TYPE_L1TAG)
    {
        eccErrStatus = HW_RD_REG32(baseAddr + IPU_UNICACHE_L1TAG_ERR_INFO);
    }
    else
    {
        eccErrStatus = HW_RD_REG32(baseAddr + IPU_UNICACHE_L2RAM_ERR_INFO);
    }

    return eccErrStatus;
}

void ECCIPUMemClrErrStatus(uint32_t baseAddr,
                           uint32_t eccErrType,
                           uint32_t memType)
{
    if ((memType & ECC_IPU_MEM_TYPE_L1DATA) == ECC_IPU_MEM_TYPE_L1DATA)
    {
        if ((eccErrType & ECC_IPU_ERR_ONEBIT) == ECC_IPU_ERR_ONEBIT)
        {
            HW_WR_FIELD32(baseAddr + IPU_UNICACHE_L1DATA_ERR_INFO,
                          IPU_UNICACHE_L1DATA_ERR_INFO_SEC,
                          0x1);
        }
        else if ((eccErrType & ECC_IPU_ERR_TWOBIT) ==
                 ECC_IPU_ERR_TWOBIT)
        {
            HW_WR_FIELD32(baseAddr + IPU_UNICACHE_L1DATA_ERR_INFO,
                          IPU_UNICACHE_L1DATA_ERR_INFO_DED,
                          0x1);
        }
        else if ((eccErrType & ECC_IPU_ERR_CODE) == ECC_IPU_ERR_CODE)
        {
            HW_WR_FIELD32(baseAddr + IPU_UNICACHE_L1DATA_ERR_INFO,
                          IPU_UNICACHE_L1DATA_ERR_INFO_CODEERR,
                          0x1);
        }
        else
        {
            HW_WR_REG32((baseAddr + IPU_UNICACHE_L1DATA_ERR_INFO), 0xFFFFFFFFU);
        }
    }
    else if ((memType & ECC_IPU_MEM_TYPE_L1TAG) == ECC_IPU_MEM_TYPE_L1TAG)
    {
        if ((eccErrType & ECC_IPU_ERR_ONEBIT) == ECC_IPU_ERR_ONEBIT)
        {
            HW_WR_FIELD32(baseAddr + IPU_UNICACHE_L1TAG_ERR_INFO,
                          IPU_UNICACHE_L1TAG_ERR_INFO_SEC,
                          0x1);
        }
        else if ((eccErrType & ECC_IPU_ERR_TWOBIT) ==
                 ECC_IPU_ERR_TWOBIT)
        {
            HW_WR_FIELD32(baseAddr + IPU_UNICACHE_L1TAG_ERR_INFO,
                          IPU_UNICACHE_L1TAG_ERR_INFO_DED,
                          0x1);
        }
        else if ((eccErrType & ECC_IPU_ERR_CODE) == ECC_IPU_ERR_CODE)
        {
            HW_WR_FIELD32(baseAddr + IPU_UNICACHE_L1TAG_ERR_INFO,
                          IPU_UNICACHE_L1TAG_ERR_INFO_CODEERR,
                          0x1);
        }
        else
        {
            HW_WR_REG32((baseAddr + IPU_UNICACHE_L1TAG_ERR_INFO), 0xFFFFFFFFU);
        }
    }
    else
    {
        if ((eccErrType & ECC_IPU_ERR_ONEBIT) == ECC_IPU_ERR_ONEBIT)
        {
            HW_WR_FIELD32(baseAddr + IPU_UNICACHE_L2RAM_ERR_INFO,
                          IPU_UNICACHE_L2RAM_ERR_INFO_SEC,
                          0x1);
        }
        else if ((eccErrType & ECC_IPU_ERR_TWOBIT) ==
                 ECC_IPU_ERR_TWOBIT)
        {
            HW_WR_FIELD32(baseAddr + IPU_UNICACHE_L2RAM_ERR_INFO,
                          IPU_UNICACHE_L2RAM_ERR_INFO_DED,
                          0x1);
        }
        else if ((eccErrType & ECC_IPU_ERR_CODE) == ECC_IPU_ERR_CODE)
        {
            HW_WR_FIELD32(baseAddr + IPU_UNICACHE_L2RAM_ERR_INFO,
                          IPU_UNICACHE_L2RAM_ERR_INFO_CODEERR,
                          0x1);
        }
        else
        {
            HW_WR_REG32((baseAddr + IPU_UNICACHE_L2RAM_ERR_INFO), 0xFFFFFFFFU);
        }
    }
}

int32_t ECCIPUMemGetErrInfo(uint32_t            baseAddr,
                            eccIpuMemErrInfo_t *pErrInfo,
                            uint32_t            memType)
{
    int32_t retVal = STW_SOK;

    if (pErrInfo == NULL)
    {
        retVal = STW_EFAIL;
    }
    else
    {
        if ((memType & ECC_IPU_MEM_TYPE_L1DATA) ==
            ECC_IPU_MEM_TYPE_L1DATA)
        {
            pErrInfo->errAddr =
                HW_RD_REG32(baseAddr + IPU_UNICACHE_L1DATA_ERR_ADDR_LOC);

            pErrInfo->errBitLoc =
                HW_RD_REG32(baseAddr + IPU_UNICACHE_L1DATA_ERR_DATA_LOC);
        }
        else if ((memType & ECC_IPU_MEM_TYPE_L1TAG) ==
                 ECC_IPU_MEM_TYPE_L1TAG)
        {
            pErrInfo->errAddr =
                HW_RD_REG32(baseAddr + IPU_UNICACHE_L1TAG_ERR_ADDR_LOC);

            pErrInfo->errBitLoc =
                HW_RD_REG32(baseAddr + IPU_UNICACHE_L1TAG_ERR_DATA_LOC);
        }
        else
        {
            pErrInfo->errAddr =
                HW_RD_REG32(baseAddr + IPU_UNICACHE_L2RAM_ERR_ADDR_LOC);

            pErrInfo->errBitLoc =
                HW_RD_REG32(baseAddr + IPU_UNICACHE_L2RAM_ERR_DATA_LOC);
        }
    }

    return retVal;
}


/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */
