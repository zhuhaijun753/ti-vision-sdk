/**
 *  \file     FWLIBL3.c
 *
 *  \brief    This file contains the implementation of the APIs present in the
 *            device abstraction layer file of L3FW.
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include "common/stw_types.h"
#include "common/stw_dataTypes.h"
#include "hw_types.h"
#include "soc.h"
#include "soc_defines.h"
#include "fwlibl3.h"

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
/**
 * \brief   This API will return index for given L3 firewall instance in global
 *          struct #gL3FwInst.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 *
 * \return  index           Index in gL3FWInst structure.
 */
uint32_t FWLIBL3GetInstSummary(uint32_t baseAddr);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
l3fwInstSummary_t gL3FWInst[L3FW_INST_NUM] = L3FW_INST_SUMMARY;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t FWLIBL3ConfigRegion(uint32_t                        baseAddr,
                            const l3fwRegionConfigParams_t *regionParams,
                            uint32_t                        numOfMasters,
                            const l3fwMasterList_t         *masterList)
{
    int32_t  status = STW_SOK;
    uint32_t instIndex;
    l3fwRegionConfigParams_t regionConfigParams;

    /* Get L3 Firewall instance details */
    instIndex = FWLIBL3GetInstSummary(baseAddr);
    if (L3FW_INST_NUM == instIndex)
    {
        status = STW_EFAIL;
    }
    /* Configure region */
    if (STW_SOK == status)
    {
        if ((gL3FWInst[instIndex].fwNumRegions > regionParams->regionId) &&
            (regionParams->regionEndAddr > regionParams->regionStartAddr))
        {
            regionConfigParams.regionId        = regionParams->regionId;
            regionConfigParams.targetBaseAddr  = regionParams->targetBaseAddr;
            regionConfigParams.regionStartAddr =
                regionParams->regionStartAddr;
            regionConfigParams.regionEndAddr    = regionParams->regionEndAddr;
            regionConfigParams.regionPermission =
                regionParams->regionPermission;
            L3FWSetRegionParams(baseAddr, &regionConfigParams);
        }
        else
        {
            status = STW_EFAIL;
        }
    }
    if (STW_SOK == status)
    {
        /* Remove permission for add masters */
        L3FWRemoveAllRegionMRMPermissions(baseAddr, regionParams->regionId);
        /* Configure region MRM permissions */
        status = FWLIBL3UpdateMRMPermissions(baseAddr,
                                             regionParams->regionId,
                                             numOfMasters,
                                             masterList);
    }
    return status;
}

int32_t FWLIBL3UpdateMRMPermissions(uint32_t                baseAddr,
                                    uint32_t                regionId,
                                    uint32_t                numOfMasters,
                                    const l3fwMasterList_t *masterList)
{
    int32_t  status = STW_SOK;
    uint32_t instIndex, loopCnt;

    /* Get L3 Firewall instance details */
    instIndex = FWLIBL3GetInstSummary(baseAddr);
    if (L3FW_INST_NUM == instIndex)
    {
        status = STW_EFAIL;
    }
    /* Configure region MRM permissions */
    if (STW_SOK == status)
    {
        if ((gL3FWInst[instIndex].fwNumRegions > regionId))
        {
            for (loopCnt = 0U; loopCnt < numOfMasters; loopCnt++)
            {
                L3FWSetRegionMRMPermission(
                    baseAddr,
                    regionId,
                    masterList[loopCnt].connId,
                    masterList[loopCnt].permission);
            }
        }
        else
        {
            status = STW_EFAIL;
        }
    }
    return status;
}

int32_t FWLIBL3RegionEnable(uint32_t baseAddr,
                            uint32_t regionId,
                            uint32_t portNum)
{
    int32_t  status = STW_SOK;
    uint32_t instIndex;

    /* Get L3 Firewall instance details */
    instIndex = FWLIBL3GetInstSummary(baseAddr);
    if (L3FW_INST_NUM == instIndex)
    {
        status = STW_EFAIL;
    }
    if (STW_SOK == status)
    {
        /* Enable region */
        if ((gL3FWInst[instIndex].fwNumPorts > portNum) &&
            (gL3FWInst[instIndex].fwNumRegions > regionId))
        {
            L3FWEnableRegion(baseAddr,
                             regionId,
                             portNum);
        }
        else
        {
            status = STW_EFAIL;
        }
    }
    return status;
}

int32_t FWLIBL3RegionDisable(uint32_t baseAddr,
                             uint32_t regionId,
                             uint32_t portNum)
{
    int32_t  status = STW_SOK;
    uint32_t instIndex;

    /* Get L3 Firewall instance details */
    instIndex = FWLIBL3GetInstSummary(baseAddr);
    if (L3FW_INST_NUM == instIndex)
    {
        status = STW_EFAIL;
    }
    if (STW_SOK == status)
    {
        /* Disable region */
        if ((gL3FWInst[instIndex].fwNumPorts > portNum) &&
            (gL3FWInst[instIndex].fwNumRegions > regionId))
        {
            L3FWDisableRegion(baseAddr,
                              regionId,
                              portNum);
        }
        else
        {
            status = STW_EFAIL;
        }
    }
    return status;
}

int32_t FWLIBL3GetErrorLog(uint32_t                 baseAddr,
                           uint32_t                 portNum,
                           l3fwRegionErrorStatus_t *errorInfo)
{
    int32_t  status = STW_SOK;
    uint32_t instIndex;

    /* Get L3 Firewall instance details */
    instIndex = FWLIBL3GetInstSummary(baseAddr);
    if (L3FW_INST_NUM == instIndex)
    {
        status = STW_EFAIL;
    }
    if (STW_SOK == status)
    {
        if ((gL3FWInst[instIndex].fwNumPorts > portNum))
        {
            /* Get Error Information */
            L3FWGetErrorInfo(baseAddr, portNum, errorInfo);
        }
        else
        {
            status = STW_EFAIL;
        }
    }
    return status;
}

int32_t FWLIBL3ClearErrorLog(uint32_t baseAddr, uint32_t portNum)
{
    int32_t  status = STW_SOK;
    uint32_t instIndex;

    /* Get L3 Firewall instance details */
    instIndex = FWLIBL3GetInstSummary(baseAddr);
    if (L3FW_INST_NUM == instIndex)
    {
        status = STW_EFAIL;
    }
    if (STW_SOK == status)
    {
        if ((gL3FWInst[instIndex].fwNumPorts > portNum))
        {
            /* Clear Error Information */
            L3FWClearErrorInfo(baseAddr, portNum);
        }
        else
        {
            status = STW_EFAIL;
        }
    }
    return status;
}

uint32_t FWLIBL3GetInstSummary(uint32_t baseAddr)
{
    uint32_t index, loopCnt;

    for (loopCnt = 0U; loopCnt < L3FW_INST_NUM; loopCnt++)
    {
        if (gL3FWInst[loopCnt].fwBaseAddr == baseAddr)
        {
            break;
        }
    }
    index = loopCnt;
    return index;
}

