/******************************************************************************
 *                                                                            *
 * Copyright (c) 2012 Texas Instruments Incorporated - http://www.ti.com/     *
 *                                                                            *
 * All rights reserved. Property of Texas Instruments Incorporated.           *
 * Restricted rights to use, duplicate or disclose this code are              *
 * granted through contract.                                                  *
 *                                                                            *
 * The program may not be used without the written permission                 *
 * of Texas Instruments Incorporated or against the terms and conditions      *
 * stipulated in the agreement under which this program has been              *
 * supplied.                                                                  *
 *                                                                            *
 *****************************************************************************/

/**
 *  \file vpscore_dctrl.c
 *
 *  \brief DSS display controller core implementation
 *  This file implements the Display controller core interface for DSS.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include <common/bsp_types.h>
#include <common/trace.h>
#include <common/stw_config.h>
#include <common/bsp_utils.h>

#include <common/vpscore.h>
#include <common/vps_common.h>
#include <dispcore/src/vpscore_dctrlPriv.h>
#include <vps/vps_displayCtrlDataTypes.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

Void VpsCore_DctrlGraphInit(const Vgraph_nodeInfoList *pathNodeList,
                            const Vgraph_edgeInfoList *edgeInfoList,
                            VpsCore_DctrlObj          *pDctrlInstObj);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Void VpsCore_DctrlGraphInit(const Vgraph_nodeInfoList *pathNodeList,
                            const Vgraph_edgeInfoList *edgeInfoList,
                            VpsCore_DctrlObj          *pDctrlInstObj)
{
    pDctrlInstObj->graphObj.nodeList = &pDctrlInstObj->graphObjNodeList;
    pDctrlInstObj->graphObj.edgeList = &pDctrlInstObj->graphObjEdgeList;
    pDctrlInstObj->graph = &pDctrlInstObj->graphObj;
    Vgraph_Init(pathNodeList, edgeInfoList,
                (Vgraph_Info *) pDctrlInstObj->graph);
}

VpsCore_Inst VpsCore_DctrlInit(VpsCore_DctrlObj *pNewObj)
{
    if (NULL != pNewObj)
    {
        /* Create default tree with all edges disabled
         * This tree will handle resource management
         */
        BspUtils_memcpy(pNewObj->allDctrlNodes,
                        dctrlNodeInfoDefaults,
                        sizeof (dctrlNodeInfoDefaults));
        pNewObj->dctrlNodeList.numNodes = GRAPH_DCTRL_DSS_NUM_NODES;
        pNewObj->dctrlNodeList.list     = pNewObj->allDctrlNodes;

        BspUtils_memcpy(pNewObj->allEdgeInfo,
                        dctrlEdgeInfoDefaults,
                        sizeof (dctrlEdgeInfoDefaults));
        pNewObj->dctrlEdgeList.numEdges = GRAPH_DCTRL_DSS_NUM_EDGES;
        pNewObj->dctrlEdgeList.list     = pNewObj->allEdgeInfo;

        VpsCore_DctrlGraphInit(&pNewObj->dctrlNodeList,
                               &pNewObj->dctrlEdgeList,
                               pNewObj);
    }
    else
    {
        GT_0trace(
            VpsDctrlCoreTrace, GT_ERR,
            "Allocation of DSS instance Handle failed in VpsCore_DctrlInit().\n");
    }

    return (VpsCore_Inst) pNewObj;
}

Int32 VpsCore_DctrlDeInit(VpsCore_Inst pDssHandle)
{
    VpsCore_DctrlObj *pDctrlObj = (VpsCore_DctrlObj *) pDssHandle;

    if (NULL != (void *) pDctrlObj)
    {
        Vgraph_DeInit((Vgraph_Info *) pDctrlObj->graph);
    }

    return BSP_SOK;
}

Int32 VpsCore_dctrlCreateEdgeList(VpsCore_DctrlObj *pathObj,
                                  Vps_DctrlConfig  *pathCfg)
{
    Vgraph_edgeInfoList tmpEdgeInfoList;
    VpsCore_DctrlObj   *pDctrlInstObj = (VpsCore_DctrlObj *) pathObj;
    Vgraph_Info        *DctrlGraph    = (Vgraph_Info *) (pDctrlInstObj->graph);
    Int32 retVal = BSP_SOK;

    tmpEdgeInfoList.numEdges = pathCfg->numEdges;
    tmpEdgeInfoList.list     = (Vgraph_edgeInfo *) &pathCfg->edgeInfo[0U];

    if (BSP_SOK == retVal)
    {
        /* Try to allocate nodes in the complete graph */
        if (BSP_SOK == Vgraph_allocNodes(DctrlGraph->nodeList,
                                         &tmpEdgeInfoList,
                                         VGRAPH_NODE_CHECK))
        {
            Vgraph_allocNodes(DctrlGraph->nodeList,
                              &tmpEdgeInfoList,
                              VGRAPH_NODE_ENABLE);

            pathObj->dctrlNodeList.list = pathObj->dctrlNodeObj;
            pathObj->dctrlEdgeList.list = pathObj->dctrlEdgeObj;
            Vgraph_getPath(DctrlGraph->nodeList,
                           &tmpEdgeInfoList,
                           &pathObj->dctrlNodeList,
                           &pathObj->dctrlEdgeList,
                           sizeof (pathObj->dctrlNodeObj) /
                           sizeof (Vgraph_nodeInfo),
                           sizeof (pathObj->dctrlEdgeObj) /
                           sizeof (Vgraph_edgeInfo));

            if (BSP_SOK != retVal)
            {
                /* TODO Free the resources */
            }
        }
        else
        {
            Vgraph_allocNodes(DctrlGraph->nodeList,
                              &tmpEdgeInfoList,
                              VGRAPH_NODE_DISABLE);
            retVal = BSP_EFAIL;
        }
    }

    return retVal;
}

Void VpsCore_dctrlFreeEdgeList(VpsCore_DctrlObj *pathObj)
{
    VpsCore_DctrlObj *pDctrlInstObj = (VpsCore_DctrlObj *) pathObj;
    Vgraph_Info      *DctrlGraph    = (Vgraph_Info *) (pDctrlInstObj->graph);

    Vgraph_allocNodes(DctrlGraph->nodeList,
                      &(pathObj->dctrlEdgeList),
                      VGRAPH_NODE_DISABLE);

    Vgraph_freePath(&pathObj->dctrlNodeList, &pathObj->dctrlEdgeList);
}

