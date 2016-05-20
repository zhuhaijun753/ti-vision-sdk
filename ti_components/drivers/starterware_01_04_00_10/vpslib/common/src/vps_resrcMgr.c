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
 * \file vps_resrcMgr.c
 *
 * \brief VPS Resource Manager Source file
 * This file exposes the APIs of the VPS Resource Manager.
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
#include <osal/bsp_osal.h>
#include <common/trace.h>
#include <common/stw_config.h>
#include <common/bsp_utils.h>
#include <common/vps_common.h>
#include <common/vps_resrcMgr.h>
#if defined (VPS_VIP_BUILD) || defined (VPS_VPE_BUILD)
#include <hal/vpshal_vpdma.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    UInt32            instId;
    UInt32            resource[VRM_RESOURCE_MAX];
#if defined (VPS_VIP_BUILD) || defined (VPS_VPE_BUILD)
    UInt32            vpdmaList[VPSHAL_VPDMA_MAX_LIST];
    UInt32            vpdmaFreeLmFidFlag[VPSHAL_VPDMA_MAX_LM_FID];
    UInt32            vpdmaFreeSiFlag[VPSHAL_VPDMA_MAX_SI_SOURCE];
    UInt32            cntFreeSi;
    UInt32            cntFreeChannels;
#endif
    BspOsal_SemHandle lockSem;
} Vrm_InstObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Vrm_InstObj *vrmGetInstObj(Vrm_InstId instId);

/* ========================================================================== */
/*                        Global Variables                                    */
/* ========================================================================== */

static Vrm_InstObj gVrmInstObj[VRM_MAX_INST];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  Vrm_init
 *  \brief Function to initialize Resource manager.
 */
Int32 Vrm_init(UInt32 numInst, const Vrm_InstParams *instPrms)
{
    Int32        retVal = BSP_SOK;
    UInt32       cnt, instCnt;
    Vrm_InstObj *instObj;

    /* Check for errors */
    GT_assert(VpsVrmTrace, (numInst <= VRM_MAX_INST));
    GT_assert(VpsVrmTrace, (NULL != instPrms));

    /* Init objects and mark flags as free */
    BspUtils_memset(gVrmInstObj, 0, sizeof (gVrmInstObj));
    for (instCnt = 0U; instCnt < VRM_MAX_INST; instCnt++)
    {
        gVrmInstObj[instCnt].instId = VRM_INST_ID_MAX;
    }

    for (instCnt = 0U; instCnt < numInst; instCnt++)
    {
        /* Initialize instance object members */
        instObj         = &gVrmInstObj[instCnt];
        instObj->instId = instPrms[instCnt].instId;

        /* Initialize all the resource to be Free */
        for (cnt = 0U; cnt < VRM_RESOURCE_MAX; cnt++)
        {
            instObj->resource[cnt] = (UInt32) FALSE;
        }

#if defined (VPS_VIP_BUILD) || defined (VPS_VPE_BUILD)
        /* Initialize All the VPDMA Lists to be free */
        for (cnt = 0U; cnt < VPSHAL_VPDMA_MAX_LIST; cnt++)
        {
            instObj->vpdmaList[cnt] = (UInt32) FALSE;
        }

        /* Initialize All the VPDMA LM FID to be free */
        for (cnt = 0U; cnt < VPSHAL_VPDMA_MAX_LM_FID; cnt++)
        {
            instObj->vpdmaFreeLmFidFlag[cnt] = (UInt32) FALSE;
        }

        /* Initialize All the VPDMA free channels to be free */
        for (cnt = 0U; cnt < VPSHAL_VPDMA_MAX_SI_SOURCE; cnt++)
        {
            instObj->vpdmaFreeSiFlag[cnt] = (UInt32) FALSE;
        }
        instObj->cntFreeSi = VPSHAL_VPDMA_MAX_SI_SOURCE;
#endif

        /* Get the semaphore handle */
        instObj->lockSem = BspOsal_semCreate((Int32) 1, TRUE);
        if (NULL == instObj->lockSem)
        {
            retVal = BSP_EALLOC;
            break;
        }
    }

    return (retVal);
}

/**
 *  Vrm_deInit
 *  \brief Function to de-initialize the resource manager.
 */
Int32 Vrm_deInit(void)
{
    UInt32       cnt, instCnt;
    Vrm_InstObj *instObj;

    for (instCnt = 0U; instCnt < VRM_MAX_INST; instCnt++)
    {
        instObj = &gVrmInstObj[instCnt];

        /* check to see no-resourece is allocated */
        for (cnt = 0; cnt < VRM_RESOURCE_MAX; cnt++)
        {
            if (TRUE == instObj->resource[cnt])
            {
                GT_1trace(
                    VpsVrmTrace, GT_ERR,
                    " WARNING: VPS: VRM DEINIT: %d resource is in use!!\n",
                    cnt);
            }
        }

        if (instObj->lockSem != NULL)
        {
            BspOsal_semDelete(&(instObj->lockSem));
        }
    }

    return (BSP_SOK);
}

/**
 *  Vrm_allocResource
 *  \brief  Function to get and allocate the give resource. It takes resource
 *  in the enum and returns the handle to the resource if resource is
 *  available.
 */
Int32 Vrm_allocResource(Vrm_InstId instId, Vrm_Resource resource)
{
    Int32        retVal = BSP_EALLOC;
    Vrm_InstObj *instObj;

    instObj = vrmGetInstObj(instId);
    GT_assert(VpsVrmTrace, (NULL != instObj));

    /* Get the semaphore */
    BspOsal_semWait(instObj->lockSem, BSP_OSAL_WAIT_FOREVER);

    if ((resource > VRM_RESOURCE_INVALID) && (resource < VRM_RESOURCE_MAX))
    {
        /* If resource is free, return handle */
        if (instObj->resource[(UInt32) resource] == FALSE)
        {
            /* Mark resource as allocated */
            instObj->resource[(UInt32) resource] = (UInt32) TRUE;
            retVal = BSP_SOK;
        }
    }

    /* Release Semaphore */
    BspOsal_semPost(instObj->lockSem);

    return (retVal);
}

/**
 *  Vrm_releaseResource
 *  \brief  Function to free the already allocated resource. It takes handle
 *  to the resource and frees the resource. This handle is returned
 *  from the Vrm_GetResource function.
 */
Int32 Vrm_releaseResource(Vrm_InstId instId, Vrm_Resource resource)
{
    Int32        retVal = BSP_EFAIL;
    Vrm_InstObj *instObj;

    instObj = vrmGetInstObj(instId);
    GT_assert(VpsVrmTrace, (NULL != instObj));

    /* Get the semaphore */
    BspOsal_semWait(instObj->lockSem, BSP_OSAL_WAIT_FOREVER);

    if ((resource > VRM_RESOURCE_INVALID) && (resource < VRM_RESOURCE_MAX))
    {
        if (TRUE == instObj->resource[(UInt32) resource])
        {
            instObj->resource[(UInt32) resource] = (UInt32) FALSE;
            retVal = BSP_SOK;
        }
    }

    /* Release Semaphore */
    BspOsal_semPost(instObj->lockSem);

    return (retVal);
}

/**
 *  Vrm_allocList
 *  \brief  Function to get the free VPDMA Lists. This function returns
 *  the free list from the 8 lists supported by the VPDMA. If any
 *  one of them is free, it returns number of that list and marks it
 *  as allocated. If the lists are not available, it returns error.
 */
Int32 Vrm_allocList(Vrm_InstId instId, UInt32 *listNum, Vrm_ListType listType)
{
    Int32        retVal = BSP_EALLOC;
#if defined (VPS_VIP_BUILD) || defined (VPS_VPE_BUILD)
    UInt32       listCnt, startListNum, allocListNum;
    Vrm_InstObj *instObj;

    instObj = vrmGetInstObj(instId);
    GT_assert(VpsVrmTrace, (NULL != instObj));

    /* The start list number shall be 0 for Tda2xx (VAYU) Family
     * of platforms. */
    startListNum = 0;

    if (VpsLib_platformIsTI814xFamilyBuild())
    {
        /* The below piece of code allows developer to give a preference
         * for list allocation based on the requesting driver type.
         * This preference is valid only for TI814x Family of platforms.
         * To make all list allocation equal, i.e no preference,
         * remove the below code. */
        if (VRM_LIST_TYPE_CAPTURE == listType)
        {
            startListNum = 0;
        }
        else if (VRM_LIST_TYPE_DISPLAY == listType)
        {
            startListNum = 1U;
        }
        else if (VRM_LIST_TYPE_M2M == listType)
        {
            startListNum = 4U;
        }
        else
        {
            GT_0trace(VpsVrmTrace, GT_ERR, "Wrong list type\n");
        }
    }

    if (NULL != listNum)
    {
        /* If resource is free, return handle */
        for (listCnt = 0; listCnt < VPSHAL_VPDMA_MAX_LIST; listCnt++)
        {
            allocListNum = (startListNum + listCnt) % VPSHAL_VPDMA_MAX_LIST;
            if (FALSE == instObj->vpdmaList[allocListNum])
            {
                break;
            }
        }

        if (listCnt < VPSHAL_VPDMA_MAX_LIST)
        {
            /* return allocated list number */
            *listNum = allocListNum;
            /* Mark the list as allocated */
            instObj->vpdmaList[allocListNum] = (UInt32) TRUE;
            retVal = BSP_SOK;
        }
    }
#endif

    return (retVal);
}

/**
 *  Vrm_releaseeList
 *  \brief  Function to free already allocated VDPMA list
 */
Int32 Vrm_releaseList(Vrm_InstId instId, UInt32 listNum)
{
    Int32        retVal = BSP_EALLOC;
#if defined (VPS_VIP_BUILD) || defined (VPS_VPE_BUILD)
    Vrm_InstObj *instObj;

    instObj = vrmGetInstObj(instId);
    GT_assert(VpsVrmTrace, (NULL != instObj));

    if (listNum < VPSHAL_VPDMA_MAX_LIST)
    {
        if (TRUE == instObj->vpdmaList[listNum])
        {
            /* Mark the list as free */
            instObj->vpdmaList[listNum] = (UInt32) FALSE;
            retVal = BSP_SOK;
        }
    }
#endif

    return (retVal);
}

/**
 *  Vrm_allocLmFid
 *  \brief Function to get the free LM FID. It returns success if it
 *  is able to find free LM FID and marks it as allocated.
 */
Int32 Vrm_allocSendIntr(Vrm_InstId instId, UInt32 *si, UInt32 numSi)
{
    Int32        retVal = BSP_EALLOC;
#if defined (VPS_VIP_BUILD) || defined (VPS_VPE_BUILD)
    UInt32       siCnt, cnt;
    Vrm_InstObj *instObj;

    instObj = vrmGetInstObj(instId);
    GT_assert(VpsVrmTrace, (NULL != instObj));

    if (NULL != si)
    {
        /* Get the semaphore */
        BspOsal_semWait(instObj->lockSem, BSP_OSAL_WAIT_FOREVER);

        /* Check to see if requested number of free send interrupt sources
         * are available */
        if (numSi <= instObj->cntFreeSi)
        {
            for (cnt = 0U; cnt < numSi; cnt++)
            {
                /* If resource is free, return handle */
                for (siCnt = 0U; siCnt < VPSHAL_VPDMA_MAX_SI_SOURCE; siCnt++)
                {
                    if (FALSE == instObj->vpdmaFreeSiFlag[siCnt])
                    {
                        break;
                    }
                }

                if (siCnt < VPSHAL_VPDMA_MAX_SI_SOURCE)
                {
                    /* return allocated list number */
                    si[cnt] = siCnt;
                    /* Mark the list as allocated */
                    instObj->vpdmaFreeSiFlag[siCnt] = (UInt32) TRUE;
                    /* Decrement Free send interrupt count */
                    instObj->cntFreeSi--;
                }
            }
            retVal = BSP_SOK;
        }

        /* Release Semaphore */
        BspOsal_semPost(instObj->lockSem);
    }
#endif

    return (retVal);
}

/**
 *  Vrm_releaseLmFid
 *  \brief Function to release VPDMA LM FID and mark it as free.
 */
Int32 Vrm_releaseSendIntr(Vrm_InstId instId, const UInt32 *si, UInt32 numSi)
{
    Int32        retVal = BSP_EALLOC;
#if defined (VPS_VIP_BUILD) || defined (VPS_VPE_BUILD)
    UInt32       siSrc, cnt;
    Vrm_InstObj *instObj;

    instObj = vrmGetInstObj(instId);
    GT_assert(VpsVrmTrace, (NULL != instObj));

    if (NULL != si)
    {
        /* Get the semaphore */
        BspOsal_semWait(instObj->lockSem, BSP_OSAL_WAIT_FOREVER);

        retVal = BSP_SOK;
        for (cnt = 0U; (cnt < numSi) && (0 == retVal); cnt++)
        {
            siSrc = si[cnt];

            /* Send interrupt source number should be correct */
            if (siSrc >= VPSHAL_VPDMA_MAX_SI_SOURCE)
            {
                retVal = BSP_EFAIL;
                break;
            }

            if (TRUE == instObj->vpdmaFreeSiFlag[siSrc])
            {
                /* Mark the list as free */
                instObj->vpdmaFreeSiFlag[siSrc] = (UInt32) FALSE;
                /* Increment count of free send interrupt source */
                instObj->cntFreeSi++;
                retVal = BSP_SOK;
            }
            else /* Trying to free send interrupt which is already free */
            {
                retVal = BSP_EFAIL;
            }
        }

        /* Release Semaphore */
        BspOsal_semPost(instObj->lockSem);
    }
#endif

    return (retVal);
}

/**
 *  vrmGetInstObj
 *  \brief Returns the instance object pointer.
 */
static Vrm_InstObj *vrmGetInstObj(Vrm_InstId instId)
{
    UInt32       instCnt;
    Vrm_InstObj *instObj = NULL;

    for (instCnt = 0U; instCnt < VRM_MAX_INST; instCnt++)
    {
        if (gVrmInstObj[instCnt].instId == instId)
        {
            instObj = &gVrmInstObj[instCnt];
            break;
        }
    }

    return (instObj);
}

