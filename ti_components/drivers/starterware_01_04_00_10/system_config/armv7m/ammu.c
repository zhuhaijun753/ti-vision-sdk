/**
 *  \file     ammu.c
 *
 *  \brief    This file contains the AMMU HAL APIs.
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
#include "hw_types.h"
#include "common/stw_types.h"
#include "hw_ipu_unicache_mmu.h"
#include "ammu.h"

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
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t AMMUConfigPage(uint32_t baseAddr, const ammuPageConfig_t *ammuPageCfg)
{
    int32_t  retVal = STW_SOK;
    uint32_t ammuPolicyRegOffset      = 0U;
    uint32_t ammuPhyAddrRegOffset     = 0U;
    uint32_t ammuLogicalAddrRegOffset = 0U;

    switch (ammuPageCfg->ammuPageType)
    {
        case AMMU_PAGE_TYPE_SMALL:
            if (ammuPageCfg->ammuPageNum >= AMMU_NUM_SMALL_PAGES)
            {
                retVal = STW_EFAIL;
            }
            else
            {
                ammuPolicyRegOffset =
                    IPU_SMALL_POLICY(ammuPageCfg->ammuPageNum);
                ammuPhyAddrRegOffset =
                    IPU_SMALL_XLTE(ammuPageCfg->ammuPageNum);
                ammuLogicalAddrRegOffset =
                    IPU_SMALL_ADDR(ammuPageCfg->ammuPageNum);
            }
            break;
        case AMMU_PAGE_TYPE_MEDIUM:
            if (ammuPageCfg->ammuPageNum >= AMMU_NUM_MEDIUM_PAGES)
            {
                retVal = STW_EFAIL;
            }
            else
            {
                ammuPolicyRegOffset =
                    IPU_MED_POLICY(ammuPageCfg->ammuPageNum);
                ammuPhyAddrRegOffset =
                    IPU_MED_XLTE(ammuPageCfg->ammuPageNum);
                ammuLogicalAddrRegOffset =
                    IPU_MED_ADDR(ammuPageCfg->ammuPageNum);
            }
            break;
        case AMMU_PAGE_TYPE_LARGE:
            if (ammuPageCfg->ammuPageNum >= AMMU_NUM_LARGE_PAGES)
            {
                retVal = STW_EFAIL;
            }
            else
            {
                ammuPolicyRegOffset =
                    IPU_LARGE_POLICY(ammuPageCfg->ammuPageNum);
                ammuPhyAddrRegOffset =
                    IPU_LARGE_XLTE(ammuPageCfg->ammuPageNum);
                ammuLogicalAddrRegOffset =
                    IPU_LARGE_ADDR(ammuPageCfg->ammuPageNum);
            }
            break;
        case AMMU_PAGE_TYPE_INVALID:
            retVal = STW_EFAIL;
            break;
        default:
            retVal = STW_EFAIL;
            break;
    }

    if (STW_SOK == retVal)
    {
        /* First clear any previous configuration */
        /* Policy Register */
        HW_WR_REG32(baseAddr + ammuPolicyRegOffset, 0x00000000U);
        /* Logical Address */
        HW_WR_REG32(baseAddr + ammuLogicalAddrRegOffset, 0x00000000U);
        /* Physical Address */
        HW_WR_REG32(baseAddr + ammuPhyAddrRegOffset, 0x00000000U);

        /* Map the new configuration */
        if (0U != ammuPageCfg->policyRegVal)
        {
            /* Logical Address */
            HW_WR_REG32(baseAddr + ammuLogicalAddrRegOffset,
                        ammuPageCfg->logicalAddress);
            /* Physical Address */
            HW_WR_REG32(baseAddr + ammuPhyAddrRegOffset,
                        ammuPageCfg->physicalAddress);
            /* Policy Register */
            HW_WR_REG32(baseAddr + ammuPolicyRegOffset,
                        ammuPageCfg->policyRegVal);
        }
    }

    return retVal;
}

uint32_t AMMUMakePolicyReg(const ammuPolicyRegParams_t *policyParams)
{
    uint32_t policyRegVal = 0U;

    HW_SET_FIELD32(policyRegVal,
                   IPU_LARGE_POLICY_ENABLE,
                   policyParams->pageEnable);
    HW_SET_FIELD32(policyRegVal,
                   IPU_LARGE_POLICY_SIZE,
                   policyParams->pageSize);
    HW_SET_FIELD32(policyRegVal,
                   IPU_LARGE_POLICY_VOLATILE,
                   policyParams->volatileEnable);
    HW_SET_FIELD32(policyRegVal,
                   IPU_LARGE_POLICY_PRELOAD,
                   policyParams->preloadEnable);
    HW_SET_FIELD32(policyRegVal,
                   IPU_LARGE_POLICY_EXCLUSION,
                   policyParams->cacheExclusionEnable);
    HW_SET_FIELD32(policyRegVal,
                   IPU_LARGE_POLICY_L1_CACHEABLE,
                   policyParams->l1CacheEnable);
    HW_SET_FIELD32(policyRegVal,
                   IPU_LARGE_POLICY_L1_POSTED,
                   policyParams->l1PostedWrite);
    HW_SET_FIELD32(policyRegVal,
                   IPU_LARGE_POLICY_L1_ALLOCATE,
                   policyParams->l1AllocateWrite);
    HW_SET_FIELD32(policyRegVal,
                   IPU_LARGE_POLICY_L1_WR_POLICY,
                   policyParams->l1WritePolicy);
    HW_SET_FIELD32(policyRegVal,
                   IPU_LARGE_POLICY_L2_CACHEABLE,
                   policyParams->l2CacheEnable);
    HW_SET_FIELD32(policyRegVal,
                   IPU_LARGE_POLICY_L2_POSTED,
                   policyParams->l2PostedWrite);
    HW_SET_FIELD32(policyRegVal,
                   IPU_LARGE_POLICY_L2_ALLOCATE,
                   policyParams->l2AllocateWrite);
    HW_SET_FIELD32(policyRegVal,
                   IPU_LARGE_POLICY_L2_WR_POLICY,
                   policyParams->l2WritePolicy);

    return policyRegVal;
}

void AMMUInitPolicyParams(ammuPolicyRegParams_t *policyParams)
{
    policyParams->pageEnable           = AMMU_PAGE_DISABLED;
    policyParams->pageSize             = AMMU_PAGE_SIZE_INVALID;
    policyParams->volatileEnable       = AMMU_VOLATILE_DISABLED;
    policyParams->preloadEnable        = AMMU_PRELOAD_DISABLED;
    policyParams->cacheExclusionEnable = AMMU_CACHE_EXCLUSION_DISABLED;
    policyParams->l1CacheEnable        = AMMU_L1_CACHE_DISABLED;
    policyParams->l1PostedWrite        = AMMU_L1_POSTED_WRITE_DISABLED;
    policyParams->l1AllocateWrite      = AMMU_L1_ALLOCATE_WRITE_DISABLED;
    policyParams->l1WritePolicy        = AMMU_L1_WRITE_POLICY_WRITETHROUGH;
    policyParams->l2CacheEnable        = AMMU_L2_CACHE_DISABLED;
    policyParams->l2PostedWrite        = AMMU_L2_POSTED_WRITE_DISABLED;
    policyParams->l2AllocateWrite      = AMMU_L2_ALLOCATE_WRITE_DISABLED;
    policyParams->l2WritePolicy        = AMMU_L2_WRITE_POLICY_WRITETHROUGH;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */
