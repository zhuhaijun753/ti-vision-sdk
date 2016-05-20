/******************************************************************************
 *                                                                            *
 * Copyright (c) 2014 Texas Instruments Incorporated - http://www.ti.com/     *
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
 *  \file vpsdrv_m2mIssCore.c
 *
 *  \brief ISS core driver.
 *  This file implements ISS core APIs for the FVID2 APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <xdc/std.h>
#include "vpsdrv_m2mIntfPriv.h"
#include "vpsdrv_m2mIsscore.h"
#include <vps/iss/vps_isscommon.h>
#include <vps/iss/vps_m2mIss.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                               Functions                                    */
/* ========================================================================== */

#ifdef VPS_ISS_BUILD
/**
 *  vpsMdrvIssControl
 *  \brief Processes ISS specific control commands
 */
Int32 vpsMdrvIssControl(
    VpsMDrv_IntfHandleObj *hObj,
    UInt32                 cmd,
    Ptr                    cmdArgs,
    Ptr                    cmdStatArgs)
{
    Int32 status = FVID2_SOK;
    VpsMDrv_IntfInstObj *instObj = NULL;

    /* Null pointer check */
    if (NULL == hObj)
    {
        status = FVID2_EBADARGS;
    }
    else
    {
        instObj = hObj->instObj;
        if (NULL == instObj)
        {
            status = FVID2_EBADARGS;
        }
    }
    if (status == FVID2_SOK)
    {
        if (((UInt32)FALSE == BspUtils_isQEmpty(instObj->inQueue)) ||
            (NULL != instObj->activeQObj))
        {
            GT_0trace(
                VpsMDrvTrace, GT_ERR,
                "No ioctls are supported when a request is active or \
                  input queue is not empty!\n");
            status = FVID2_EAGAIN;
        }

        if (FVID2_SOK == status)
        {
            /* Core Ops is constant pointer, so can not be null,
             * ISP M2M is single core so assuming core Handle from the 0th Index
             * */

            GT_assert(VpsMDrvTrace, (NULL != hObj->coreHandle[0U]));

            switch (cmd)
            {
                case IOCTL_VPS_ISS_M2M_SET_ISP_PARAMS:
                    /* SetParams function pointer must not be null*/
                    GT_assert(VpsMDrvTrace,
                              (NULL != instObj->coreOps[0U]->setParams));

                    status = instObj->coreOps[0U]->setParams(
                        hObj->coreHandle[0U],
                        cmdArgs,
                        NULL);
                    break;
                case IOCTL_VPS_ISS_M2M_GET_ISP_PARAMS:
                    /* SetParams function pointer must not be null*/
                    GT_assert(VpsMDrvTrace,
                              (NULL != instObj->coreOps[0U]->getParams));

                    status = instObj->coreOps[0U]->getParams(
                        hObj->coreHandle[0U],
                        cmdArgs);
                    break;
                default:
                    /* SetParams function pointer must not be null*/
                    GT_assert(VpsMDrvTrace,
                              (NULL != instObj->coreOps[0U]->control));

                    status = instObj->coreOps[0U]->control(
                        hObj->coreHandle[0U],
                        cmd,
                        cmdArgs,
                        cmdStatArgs);
                    break;
            }
        }
    }
    return (status);
}

/**
 *  vpsMdrvIssSubmitReq
 *  \brief Submits a processing request to the ISS core.
 */
Int32 vpsMdrvIssSubmitReq(
    VpsMDrv_IntfHandleObj *hObj,
    VpsMDrv_IntfQueueObj  *qObj)
{
    Int32 status = FVID2_SOK;
    VpsMDrv_IntfInstObj *instObj = NULL;

    /* Null pointer check */
    if ((NULL == hObj) || (NULL == qObj))
    {
        status = FVID2_EBADARGS;
    }
    else
    {
        instObj = hObj->instObj;
        if (NULL == instObj)
        {
            status = FVID2_EBADARGS;
        }
    }

    if (FVID2_SOK == status)
    {
        /* Copy frames from input and output frames list to VpsCore_Frame */
        /* Copy input frames */
        VpsCore_copyFvid2ToVpsFrame(
            &qObj->frm[VPS_ISS_STREAM_CAL_RD_INPUT_0],
            qObj->inFrmList.frames[VPS_ISS_STREAM_CAL_RD_INPUT_0]);
        VpsCore_copyFvid2ToVpsFrame(
            &qObj->frm[VPS_ISS_STREAM_ID_INPUT_N1],
            qObj->inFrmList.frames[VPS_ISS_STREAM_ID_INPUT_N1]);

        /* Copy Output Frames */
        VpsCore_copyFvid2ToVpsFrame(
            &qObj->frm[VPS_ISS_STREAM_ID_RSZ_A],
            qObj->outFrmList.frames[VPS_ISS_STREAM_ID_RSZ_A]);
        VpsCore_copyFvid2ToVpsFrame(
            &qObj->frm[VPS_ISS_STREAM_ID_RSZ_B],
            qObj->outFrmList.frames[VPS_ISS_STREAM_ID_RSZ_B]);
        VpsCore_copyFvid2ToVpsFrame(
            &qObj->frm[VPS_ISS_STREAM_ID_BSC],
            qObj->outFrmList.frames[VPS_ISS_STREAM_ID_BSC]);
        VpsCore_copyFvid2ToVpsFrame(
            &qObj->frm[VPS_ISS_STREAM_ID_BOXCAR],
            qObj->outFrmList.frames[VPS_ISS_STREAM_ID_BOXCAR]);
        VpsCore_copyFvid2ToVpsFrame(
            &qObj->frm[VPS_ISS_STREAM_ID_HIST],
            qObj->outFrmList.frames[VPS_ISS_STREAM_ID_HIST]);
        VpsCore_copyFvid2ToVpsFrame(
            &qObj->frm[VPS_ISS_STREAM_ID_AF],
            qObj->outFrmList.frames[VPS_ISS_STREAM_ID_AF]);
        VpsCore_copyFvid2ToVpsFrame(
            &qObj->frm[VPS_ISS_STREAM_ID_AEWB],
            qObj->outFrmList.frames[VPS_ISS_STREAM_ID_AEWB]);

        /* Core Ops is constant pointer, so can not be null,
         * ISP M2M is single core so assuming core Handle from the 0th Index */
        GT_assert(VpsMDrvTrace, (NULL != instObj->coreOps[0U]->putFrames));
        GT_assert(VpsMDrvTrace, (NULL != hObj->coreHandle[0U]));

        status = instObj->coreOps[0U]->putFrames(
            hObj->coreHandle[0U],
            qObj->pFrm);
    }

    return (status);
}

#endif /* VPS_ISS_BUILD */

#ifdef VPS_SIMCOP_BUILD
/**
 *  vpsMdrvSimcopSubmitReq
 *  \brief Submits a processing request to the ISS core.
 */
Int32 vpsMdrvSimcopSubmitReq(
    VpsMDrv_IntfHandleObj *hObj,
    VpsMDrv_IntfQueueObj  *qObj)
{
    Int32 status = FVID2_SOK;
    VpsMDrv_IntfInstObj *instObj = NULL;

    /* Null pointer check */
    if ((NULL == hObj) || (NULL == qObj))
    {
        status = FVID2_EBADARGS;
    }
    else
    {
        instObj = hObj->instObj;
        if (NULL == instObj)
        {
            status = FVID2_EBADARGS;
        }
    }

    if (FVID2_SOK == status)
    {
        /* Copy frames from input and output frames list to VpsCore_Frame */
        /* Copy input frames */
        VpsCore_copyFvid2ToVpsFrame(
            &qObj->frm[VPS_SIMCOP_STREAM_ID_CUR_FRAME],
            qObj->inFrmList.frames[VPS_SIMCOP_STREAM_ID_CUR_FRAME]);
        VpsCore_copyFvid2ToVpsFrame(
            &qObj->frm[VPS_SIMCOP_STREAM_ID_PREV_FRAME],
            qObj->inFrmList.frames[VPS_SIMCOP_STREAM_ID_PREV_FRAME]);
        VpsCore_copyFvid2ToVpsFrame(
            &qObj->frm[VPS_SIMCOP_STREAM_ID_MESH_TABLE],
            qObj->inFrmList.frames[VPS_SIMCOP_STREAM_ID_MESH_TABLE]);

        /* Copy Output Frames */
        VpsCore_copyFvid2ToVpsFrame(
            &qObj->frm[VPS_SIMCOP_STREAM_ID_OUT_FRAME],
            qObj->outFrmList.frames[VPS_SIMCOP_STREAM_ID_OUT_FRAME]);

        /* Core Ops is constant pointer, so can not be null,
         * ISP M2M is single core so assuming core Handle from the 0th Index */
        GT_assert(VpsMDrvTrace, (NULL != instObj->coreOps[0U]->putFrames));
        GT_assert(VpsMDrvTrace, (NULL != hObj->coreHandle[0U]));

        status = instObj->coreOps[0U]->putFrames(
            hObj->coreHandle[0U],
            qObj->pFrm);
    }

    return (status);
}

/**
 *  vpsMdrvIssControl
 *  \brief Processes ISS specific control commands
 */
Int32 vpsMdrvSimcopControl(
    VpsMDrv_IntfHandleObj *hObj,
    UInt32                 cmd,
    Ptr                    cmdArgs,
    Ptr                    cmdStatArgs)
{
    Int32 status = FVID2_SOK;
    VpsMDrv_IntfInstObj *instObj = NULL;

    /* Null pointer check */
    if (NULL == hObj)
    {
        status = FVID2_EBADARGS;
    }
    else
    {
        instObj = hObj->instObj;
        if (NULL == instObj)
        {
            status = FVID2_EBADARGS;
        }
    }
    if (status == FVID2_SOK)
    {
        if (((UInt32)FALSE == BspUtils_isQEmpty(instObj->inQueue)) ||
            (NULL != instObj->activeQObj))
        {
            GT_0trace(
                VpsMDrvTrace, GT_ERR,
                "No ioctls are supported when a request is active or \
                  input queue is not empty!\n");
            status = FVID2_EAGAIN;
        }

        if (FVID2_SOK == status)
        {
            /* Core Ops is constant pointer, so can not be null,
             * ISP M2M is single core so assuming core Handle from the 0th Index
             * */

            GT_assert(VpsMDrvTrace, (NULL != hObj->coreHandle[0U]));

            switch (cmd)
            {
                case IOCTL_VPS_SIMCOP_M2M_SET_PARAMS:
                    /* SetParams function pointer must not be null*/
                    GT_assert(VpsMDrvTrace,
                              (NULL != instObj->coreOps[0U]->setParams));

                    status = instObj->coreOps[0U]->setParams(
                        hObj->coreHandle[0U],
                        cmdArgs,
                        NULL);
                    break;
                default:
                    /* Default goes to CONTROL function pointer which must
                     * not be null */
                    GT_assert(VpsMDrvTrace,
                              (NULL != instObj->coreOps[0U]->control));

                    status = instObj->coreOps[0U]->control(
                        hObj->coreHandle[0U],
                        cmd,
                        cmdArgs,
                        cmdStatArgs);
                    break;
            }
        }
    }
    return (status);
}

#endif
/* ========================================================================== */
/*                          Internal Functions                                */
/* ========================================================================== */

