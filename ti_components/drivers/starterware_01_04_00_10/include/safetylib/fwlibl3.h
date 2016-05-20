/**
 *  \file     l3fwlib.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
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

#ifndef FWLIBL3_H_
#define FWLIBL3_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "hw_l3fw.h"
#include "l3fw.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/** \brief   Maximum number of masters for L3 Firewall. */
#define L3FW_NUM_MASTER_MAX                                 (16U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/**
 * \brief  Structure for L3 Firewall Instance summary.
 */
typedef struct l3fwInstSummary
{
    uint32_t fwBaseAddr;
    /**< L3 Firewall Instance Base Address */
    uint32_t fwNumRegions;
    /**< Number of regions for L3 Firewall Instance */
    uint32_t fwNumPorts;
    /**< Number of ports in Target */
}l3fwInstSummary_t;

/**
 * \brief  Structure for L3 Firewall Masters list along with with permission.
 */
typedef struct l3fwMasterList
{
    uint32_t connId;
    /**< ConnId of type #halL3fwL3ConnId which made the invalid access
     *  This ID should be 4bit connID
     *  (upper 4 bits of 6bit connID).
     */
    uint32_t permission;
    /**< Number of regions for L3 Firewall Instance
     *  Refer enum #l3fwMRMRWPermission_t
     */
}l3fwMasterList_t;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This API will configure region for L3FW Module.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 * \param   regionParams    Configuration parameters for region.
 *                          Refer enum #l3fwRegionInfoParams_t.
 * \param   numOfMasters    Number of masters for which MRM permission
 *                          is to set.
 * \param   masterList      List containing list of masters along with
 *                          permissions.
 *                          Refer enum #l3fwRegionInfoParams_t.
 *
 * \return  status          Configuration status.
 */
int32_t FWLIBL3ConfigRegion(uint32_t                        baseAddr,
                            const l3fwRegionConfigParams_t *regionParams,
                            uint32_t                        numOfMasters,
                            const l3fwMasterList_t         *masterList);

/**
 * \brief   This API will update MRM permissions for a region for L3FW Module.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 * \param   regionId        Region ID to configure.
 * \param   numOfMasters    Number of masters for which MRM permission
 *                          is to set.
 * \param   masterList      List containing list of masters along with
 *                          permissions.
 *                          Refer enum #l3fwRegionInfoParams_t.
 *
 * \return  status          Configuration status.
 */
int32_t FWLIBL3UpdateMRMPermissions(uint32_t                baseAddr,
                                    uint32_t                regionId,
                                    uint32_t                numOfMasters,
                                    const l3fwMasterList_t *masterList);

/**
 * \brief   This API will enable region for port for L3FW.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 * \param   regionId        Region ID to enable.
 * \param   portNum         Port number for which region is to enable.
 *
 * \return  status          Configuration status.
 */
int32_t FWLIBL3RegionEnable(uint32_t baseAddr,
                            uint32_t regionId,
                            uint32_t portNum);

/**
 * \brief   This API will disable region for port for L3FW.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 * \param   regionId        Region ID to disable.
 * \param   portNum         Port number for which region is to disable.
 *
 * \return  status          Configuration status.
 */
int32_t FWLIBL3RegionDisable(uint32_t baseAddr,
                             uint32_t regionId,
                             uint32_t portNum);

/**
 * \brief   This API will read and return error information for L3FW Module
 *          for given port number.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 * \param   portNum         Port number.
 * \param   errorInfo       Error information.
 *                          Refer enum #l3fwRegionErrorStatus_t.
 *
 * \return  status          Configuration status..
 */
int32_t FWLIBL3GetErrorLog(uint32_t                 baseAddr,
                           uint32_t                 portNum,
                           l3fwRegionErrorStatus_t *errorInfo);

/**
 * \brief   This API will clear error information for L3FW Module for
 *          given port number.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 * \param   portNum         Port number.
 *
 * \return  status          Configuration status..
 */
int32_t FWLIBL3ClearErrorLog(uint32_t baseAddr, uint32_t portNum);

#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
