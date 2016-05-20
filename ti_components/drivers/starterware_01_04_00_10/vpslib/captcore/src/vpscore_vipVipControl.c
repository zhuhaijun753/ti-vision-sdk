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
 *  \file vpscore_vipVipControl.c
 *
 *  \brief Core functions for controlling VIP HW
 *  This file calls the HAL APIs of the VPDMA, VIP Port and VIP Top.
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

#include <captcore/vpscore_vip.h>
#include <captcore/src/vpscore_vipPriv.h>
#include <common/vps_graph.h>
#include <common/vps_common.h>
#include <captcore/src/vpscore_vipVipControl.h>

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

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 VpsCore_vipPostAbortList(VpsCore_VipPathObj *pathObj)
{
    Int32  retVal = BSP_SOK;
    UInt32 descAddr;
    UInt32 listSize = 0;
    UInt32 chId, strm, pl;

    for (chId = 0; chId < pathObj->numChannels; chId++)
    {
        UInt32 numPlanes;
        descAddr = (UInt32) pathObj->descMem[chId];
        for (strm = 0; strm < pathObj->numStreams; strm++)
        {
            numPlanes = pathObj->numPlanes[strm];
            for (pl = 0; pl < numPlanes; pl++)
            {
                VpsHal_vpdmaCreateAbortCtrlDesc(
                    (UInt8 *) (descAddr),
                    pathObj->strm2VpdmaChanMap[chId][(strm *
                                                      FVID2_MAX_PLANES) + pl]);
                descAddr += VPSHAL_VPDMA_CTRL_DESC_SIZE;
            }
        }
        listSize = (descAddr - (UInt32) pathObj->descMem[chId]);
        /* TODO: Alloc separate memory for abort descriptors */
        /* VPS_CAPT_ABORT_DESC_MEM_SIZE */
        /* GT_assert(VpsVipCoreTrace, listSize < VPS_CAPT_ABORT_DESC_MEM_SIZE);
        **/

        VpsHal_vpdmaPostList(pathObj->vpdmaHandle,        /* handle      */
                             pathObj->listId[chId],       /* listNum     */
                             VPSHAL_VPDMA_LT_NORMAL,      /* listType    */
                             &pathObj->descMem[chId][0U], /* memPtr      */
                             listSize,                    /* listSize    */
                             0);                          /* enableCheck */

        /* TODO: Fix 3000 */
        retVal = VpsHal_vpdmaListWaitComplete(pathObj->vpdmaHandle,
                                              (UInt8) pathObj->listId[chId],
                                              (UInt32) 3000U);
    }

    return retVal;
}

Int32 VpsCore_vipResetFIFO(VpsCore_VipPathObj *pathObj, UInt32 enable)
{
    Int32           retVal = BSP_SOK;
    /* TODO: Only one port for now. Might need to stop other PORT as well. */
    VpsHal_vipPortResetFIFO(pathObj->vipPortHandle, enable);

    VpsCore_VipObj *pVipInstObj = (VpsCore_VipObj *) (pathObj->parent);
    if (VPSHAL_VIP_S0 == pathObj->sliceId)
    {
        VpsHal_vipPortResetFIFO(pVipInstObj->s0PortAHandle, enable);
        VpsHal_vipPortResetFIFO(pVipInstObj->s0PortBHandle, enable);
    }
    else if (VPSHAL_VIP_S1 == pathObj->sliceId)
    {
        VpsHal_vipPortResetFIFO(pVipInstObj->s1PortAHandle, enable);
        VpsHal_vipPortResetFIFO(pVipInstObj->s1PortBHandle, enable);
    }
    else
    {
        retVal = BSP_EFAIL;
    }

    return retVal;
}

Int32 VpsCore_vipBlockReset(VpsCore_VipPathObj *pathObj)
{
    UInt32 delayMsec = 1U;
    Int32  retVal, chId;

    #ifdef VPS_CAPT_DEBUG_LOG_VIP_RESET
    GT_1trace(VpsVipCoreTrace, GT_DEBUG, " [VIP%d] VIP Reset Starting !!!\n",
              vipInstId);
    #endif

    BspOsal_sleep(delayMsec);

    #ifdef VPS_CAPT_DEBUG_LOG_VIP_RESET
    GT_1trace(VpsVipCoreTrace, GT_DEBUG, " [VIP%d] Disabling Parser !!!\n",
              vipInstId);
    #endif

    /* disable VIP Parser - TODO: Need to add disable for all PORTS */
    VpsHal_vipPortEnable(pathObj->vipPortHandle, (UInt32) FALSE, 0);

    #ifdef VPS_CAPT_DEBUG_LOG_VIP_RESET
    GT_1trace(VpsVipCoreTrace, GT_DEBUG, " [VIP%d] Asserting Reset !!!\n",
              vipInstId);
    #endif

    /* Reset the whole VIP block */
    if (VPSHAL_VIP_S0 == pathObj->sliceId)
    {
        VpsHal_vipTopResetModule(pathObj->vipTopHandle,
                                 VPSHAL_VIP_TOP_S0_DP, (UInt32) TRUE, 0);
    }
    else
    {
        VpsHal_vipTopResetModule(pathObj->vipTopHandle,
                                 VPSHAL_VIP_TOP_S1_DP, (UInt32) TRUE, 0);
    }

    #ifdef VPS_CAPT_DEBUG_LOG_VIP_RESET
    GT_1trace(VpsVipCoreTrace, GT_DEBUG, " [VIP%d] Asserting Clear FIFO !!!\n",
              vipInstId);
    #endif

    /* Assert clear async FIFO reset */
    VpsCore_vipResetFIFO(pathObj, (UInt32) TRUE);

    BspOsal_sleep(delayMsec);

    #ifdef VPS_CAPT_DEBUG_LOG_VIP_RESET
    GT_1trace(VpsVipCoreTrace, GT_DEBUG, " [VIP%d] Posting Abort List !!!\n",
              vipInstId);
    #endif

    /* clear VIP overflow FIQ : TODO: Implement in HAL*/
    /* VpsHal_vipInstPortClearFIQ((VpsHal_VipInst)vipInstId); */

    /* post abort desc on all VIP VPDMA CHs */
    /* Stop the capture list before posting abort descriptors */
    for (chId = 0; chId < pathObj->numChannels; chId++)
    {
        VpsHal_vpdmaStopList(pathObj->vpdmaHandle,
                             pathObj->listId[chId],
                             VPSHAL_VPDMA_LT_NORMAL);
    }

    /* Program Abort descriptors and wait for list to get completed */
    retVal = VpsCore_vipPostAbortList(pathObj);

    BspOsal_sleep(delayMsec);

    #ifdef VPS_CAPT_DEBUG_LOG_VIP_RESET
    GT_1trace(VpsVipCoreTrace, GT_DEBUG, " [VIP%d] De-asserting Reset !!!\n",
              vipInstId);
    #endif

    /* Release the VIP block reset TODO: Add conditional reset to other slice */
    if (VPSHAL_VIP_S0 == pathObj->sliceId)
    {
        VpsHal_vipTopResetModule(pathObj->vipTopHandle,
                                 VPSHAL_VIP_TOP_S0_DP, (UInt32) FALSE, 0);
    }
    else
    {
        VpsHal_vipTopResetModule(pathObj->vipTopHandle,
                                 VPSHAL_VIP_TOP_S1_DP, (UInt32) FALSE, 0);
    }

    #ifdef VPS_CAPT_DEBUG_LOG_VIP_RESET
    GT_1trace(VpsVipCoreTrace, GT_DEBUG,
              " [VIP%d] De-asserting Clear FIFO !!!\n",
              vipInstId);
    #endif

    /* TODO: Release clear async FIFO reset To remove this and put after start
    **/
    VpsCore_vipResetFIFO(pathObj, (UInt32) FALSE);

    BspOsal_sleep(delayMsec);

    #ifdef VPS_CAPT_DEBUG_LOG_VIP_RESET
    GT_1trace(VpsVipCoreTrace, GT_DEBUG, " [VIP%d] VIP Reset Done !!!\n",
              vipInstId);
    #endif

    return retVal;
}

void VpsCore_vipTopResetAllModules(VpsCore_VipPathObj *pathObj, UInt32 enable)
{
#ifndef TI814X_FAMILY_BUILD
    UInt32           i = 0;
    Vgraph_nodeInfo *curNode;
    while (i < pathObj->nodeList.numNodes)
    {
        curNode = &pathObj->nodeList.list[i];
        if (GRAPH_VIP_S0_CSC == curNode->nodeNum)
        {
            VpsHal_vipTopResetModule(pathObj->vipTopHandle,
                                     VPSHAL_VIP_TOP_S0_CSC, enable, 0);
        }
        if (GRAPH_VIP_S1_CSC == curNode->nodeNum)
        {
            VpsHal_vipTopResetModule(pathObj->vipTopHandle,
                                     VPSHAL_VIP_TOP_S1_CSC, enable, 0);
        }

        if (GRAPH_VIP_S0_SC == curNode->nodeNum)
        {
            VpsHal_vipTopResetModule(pathObj->vipTopHandle,
                                     VPSHAL_VIP_TOP_S0_SC, enable, 0);
        }
        if (GRAPH_VIP_S1_SC == curNode->nodeNum)
        {
            VpsHal_vipTopResetModule(pathObj->vipTopHandle,
                                     VPSHAL_VIP_TOP_S1_SC, enable, 0);
        }

        if (GRAPH_VIP_S0_CHRDS0 == curNode->nodeNum)
        {
            VpsHal_vipTopResetModule(pathObj->vipTopHandle,
                                     VPSHAL_VIP_TOP_S0_CHRDS0, enable, 0);
        }
        if (GRAPH_VIP_S0_CHRDS1 == curNode->nodeNum)
        {
            VpsHal_vipTopResetModule(pathObj->vipTopHandle,
                                     VPSHAL_VIP_TOP_S0_CHRDS1, enable, 0);
        }
        if (GRAPH_VIP_S1_CHRDS0 == curNode->nodeNum)
        {
            VpsHal_vipTopResetModule(pathObj->vipTopHandle,
                                     VPSHAL_VIP_TOP_S1_CHRDS0, enable, 0);
        }
        if (GRAPH_VIP_S1_CHRDS1 == curNode->nodeNum)
        {
            VpsHal_vipTopResetModule(pathObj->vipTopHandle,
                                     VPSHAL_VIP_TOP_S1_CHRDS1, enable, 0);
        }
        i++;
    }
#elif defined TI814X_FAMILY_BUILD   /* TODO: Confirm if individual reset
                                     * supported
                                     *in Vayu */
    VpsCore_vipBlockReset(pathObj); /* Do full reset */
#endif
}

VpsCore_Frame *VpsCore_vipGetCurrentCaptFrame(const VpsCore_VipPathObj *pathObj)
{
    VpsCore_Frame *curFrmptr;
    /* TODO: Add support for multi channel */
    if (pathObj->initialWait[0] != 0)
    {
        curFrmptr =
            pathObj->inputFrame[0][0][(pathObj->outFrmIdx[0]) % VIP_SW_Q_LEN];
    }
    else
    {
        curFrmptr =
            pathObj->inputFrame[0][0]
            [(pathObj->outFrmIdx[0] + 1U) % VIP_SW_Q_LEN];
    }
    return curFrmptr;
}

Int32 VpsCore_vipPortAndModulesReset(VpsCore_VipPathObj *pathObj)
{
    Int32  retVal    = 0;
    UInt32 delayMsec = 1U;
#ifndef TI814X_FAMILY_BUILD
    Int32  chId;
#endif

    /* Reset VIP Port */
    retVal = VpsHal_vipPortReset(pathObj->vipPortHandle, (UInt32) TRUE);

    /* Reset CSC, SC, core will ensure if CSC, SC is being used in the path,
     * it would reset otherwise skip resetting it */
    VpsCore_vipTopResetAllModules(pathObj, (UInt32) TRUE);

    BspOsal_sleep(delayMsec);

#ifndef TI814X_FAMILY_BUILD
    /* Stop the capture list before posting abort descriptors */
    for (chId = 0; chId < pathObj->numChannels; chId++)
    {
        VpsHal_vpdmaStopList(pathObj->vpdmaHandle,
                             pathObj->listId[chId],
                             VPSHAL_VPDMA_LT_NORMAL);
    }

    /* Program Abort descriptors and wait for list to get completed */
    retVal += VpsCore_vipPostAbortList(pathObj);

    /* TODO: clear VIP async FIFO -
     * need to take from latest release after Brijesh update - 06 AUG 2012
     */
    /* TODO: / * clear VIP overflow FIQ * / */
    /* TODO: VpsHal_vipInstPortClearFIQ((VpsHal_VipInst)vipInstId); */

    BspOsal_sleep(delayMsec);

    /* Un-reset all modules */
    VpsCore_vipTopResetAllModules(pathObj, (UInt32) FALSE);

    /* Resetting the Muxes involved in the path */
    VpsCore_vipPathResetMuxes(pathObj);

#endif
    /* Clear VIP port: TODO - check if this is applicable to 814x */
    retVal += VpsHal_vipPortReset(pathObj->vipPortHandle, (UInt32) FALSE);

    return BSP_SOK;
}

