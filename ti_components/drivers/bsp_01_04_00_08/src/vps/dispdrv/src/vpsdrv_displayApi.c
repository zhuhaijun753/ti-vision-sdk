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
 *  \file vpsdrv_displayApi.c
 *
 *  \brief File containing the VPS display driver APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <xdc/std.h>
#include <dispdrv/src/vpsdrv_displayPriv.h>

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
/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Display API's
 */
static Fdrv_Handle VpsDrv_dispCreate(UInt32                   drvId,
                                     UInt32                   instId,
                                     Ptr                      createArgs,
                                     Ptr                      createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbPrms);
static Int32 VpsDrv_dispDelete(Fdrv_Handle handle, Ptr reserved);
static Int32 VpsDrv_dispQueue(Fdrv_Handle      handle,
                              Fvid2_FrameList *frmList,
                              UInt32           streamId);
static Int32 VpsDrv_dispDequeue(Fdrv_Handle      handle,
                                Fvid2_FrameList *frmList,
                                UInt32           streamId,
                                UInt32           timeout);
static Int32 VpsDrv_dispControl(Fdrv_Handle handle,
                                UInt32      cmd,
                                Ptr         cmdArgs,
                                Ptr         cmdStatusArgs);
#ifdef __cplusplus
}
#endif
/*
 * Display IOCTLs
 */
static Int32 vpsDrvDispStartIoctl(VpsDrv_DispInstObj *instObj);
static Int32 vpsDrvDispStopIoctl(VpsDrv_DispInstObj *instObj);
static Int32 vpsDrvDispGetStatusIoctl(VpsDrv_DispInstObj *instObj,
                                      Vps_DispStatus     *dispStat);
static Int32 vpsDrvDispRegisterBufPrgmCbIoctl(
    VpsDrv_DispInstObj               *instObj,
    const Vps_DispBufPrgmCbFxnParams *bufPrgmCbPrms);
static Int32 vpsDrvDispBypassLowLatencyCheckIoctl(
    VpsDrv_DispInstObj                        *instObj,
    const Vps_DispBypassLowLatencyCheckParams *bypassPrms);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  VpsDrv_dispInit
 *  \brief Display driver init function.
 *
 *  Initializes driver objects, allocates memory etc.
 *  This function should be called before calling any of display driver API.
 *  This should be called only once for all the instance together.
 *  This function could be called from task context only.
 *
 *  \param numInst          [IN] Number of instance objects to be initialized.
 *  \param initPrms         [IN] Pointer to the instance parameter containing
 *                          instance specific information. If the number of
 *                          instance is greater than 1, then this pointer
 *                          should point to an array of init parameter
 *                          structure of size numInst.
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 VpsDrv_dispInit(UInt32 numInst, const VpsDrv_DispInitParams *initPrms)
{
    Int32 retVal = FVID2_SOK;
    VpsDrv_DispCommonObj *pObj;

    retVal = vpsDrvDispPrivInit(numInst, initPrms);
    if (FVID2_SOK == retVal)
    {
        pObj = &gVpsDispCommonObj;
        GT_assert(VpsDrvDispTrace, (NULL != pObj));

        /* Initialize Driver operations */
        Fvid2DrvOps_init(&pObj->fvidDrvOps);

        pObj->fvidDrvOps.drvId      = FVID2_VPS_DISP_DRV;
        pObj->fvidDrvOps.createFxn  = &VpsDrv_dispCreate;
        pObj->fvidDrvOps.deleteFxn  = &VpsDrv_dispDelete;
        pObj->fvidDrvOps.controlFxn = &VpsDrv_dispControl;
        pObj->fvidDrvOps.queueFxn   = &VpsDrv_dispQueue;
        pObj->fvidDrvOps.dequeueFxn = &VpsDrv_dispDequeue;

        retVal = Fvid2_registerDriver(&pObj->fvidDrvOps);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsDrvDispTrace, GT_ERR,
                      "Registering to FVID2 driver manager failed\n");
            /* Uninitialize the internal objects if error occurs */
            vpsDrvDispPrivDeInit();
        }
        else
        {
            /* Init successful */
            pObj->isRegistered = (UInt32) TRUE;
            pObj->numInst      = numInst;
        }
    }

    return (retVal);
}

/**
 *  VpsDrv_dispDeInit
 *  \brief Display driver exit function.
 *
 *  Deallocates memory allocated by init function. This should be called only
 *  once for all the instance together. This function could be called from
 *  task context only.
 *
 *  \param arg              [IN] Not used currently. Meant for future purpose.
 *                          Set this to NULL.
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 VpsDrv_dispDeInit(void)
{
    Int32 retVal = FVID2_SOK;
    VpsDrv_DispCommonObj *pObj;

    pObj = &gVpsDispCommonObj;
    GT_assert(VpsDrvDispTrace, (NULL != pObj));

    if (TRUE == pObj->isRegistered)
    {
        /* Unregister from driver manager */
        retVal = Fvid2_unRegisterDriver(&pObj->fvidDrvOps);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsDrvDispTrace, GT_ERR,
                      "Unregistering from FVID2 driver manager failed\n");
        }
        pObj->isRegistered = (UInt32) FALSE;
    }

    retVal += vpsDrvDispPrivDeInit();

    return (retVal);
}

/**
 *  VpsDrv_dispCreate
 *  \brief Display driver create function. Returns the handle to the created
 *  driver instance.
 *
 *  This function could be called from task context only.
 *  And is reentrant - could be called from multiple tasks at the same time for
 *  creating different instances.
 *
 *  \param drvId            [IN] Driver ID - Should be FVID2_VPS_DISP_DRV.
 *  \param instId           [IN] Instance to open.
 *  \param createArgs       [IN] Display driver create parameter - pointer
 *                          to Vps_DispCreateParams. This parameter should be
 *                          non-NULL.
 *  \param createStatusArgs [OUT] Display driver return status parameter -
 *                          pointer to Vps_DispCreateStatus. This parameter
 *                          could be NULL and the driver fills the status
 *                          information only if this is not NULL.
 *  \param fdmCbParams      [IN] Call back function parameters. This parameter
 *                          should be non-NULL. But the callback function
 *                          pointer inside this structure could be NULL if the
 *                          application decides not to get display completion
 *                          callback. In this case application has to poll
 *                          the driver for knowing the status about display
 *                          completion.
 *
 *  \return                 Returns instance handle for the respective instance
 *                          ID else returns NULL on error. Appropriate error
 *                          code is returned via status argument.
 */
static Fdrv_Handle VpsDrv_dispCreate(UInt32                   drvId,
                                     UInt32                   instId,
                                     Ptr                      createArgs,
                                     Ptr                      createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbPrms)
{
    Int32                 retVal         = FVID2_SOK, tempRetVal;
    UInt32                instCreateFlag = FALSE, coreCreateFlag = FALSE;
    Fdrv_Handle           drvHandle      = NULL;
    VpsDrv_DispInstObj   *instObj        = NULL;
    Vps_DispCreateParams *createPrms;
    Vps_DispCreateStatus *createStatus;

    /* Check for NULL pointers and invalid arguments */
    if ((NULL == createArgs) ||
        (NULL == createStatusArgs) ||
        (NULL == fdmCbPrms) ||
        (FVID2_VPS_DISP_DRV != drvId))
    {
        GT_0trace(VpsDrvDispTrace, GT_ERR, "Invalid arguments\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        /* Get the instance object for this instance */
        instObj = vpsDrvDispGetInstObj(instId);
        if (NULL == instObj)
        {
            GT_0trace(VpsDrvDispTrace, GT_ERR, "Invalid instance ID\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
    }

    if (NULL != instObj)
    {
        /* Take the instance semaphore */
        BspOsal_semWait(instObj->lockSem, BSP_OSAL_WAIT_FOREVER);

        /* Check if the instance is already opened */
        if (TRUE == instObj->state.isOpened)
        {
            GT_0trace(VpsDrvDispTrace, GT_ERR,
                      "DEVICE_INUSE: Driver instance already created!!\n");
            retVal = FVID2_EDEVICE_INUSE;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Check for valid create parameters and copy them */
        createPrms = (Vps_DispCreateParams *) createArgs;
        retVal     = vpsDrvDispCheckParams(instObj, createPrms);
        if (FVID2_SOK == retVal)
        {
            BspUtils_memcpy(
                &instObj->createPrms,
                createPrms,
                sizeof (instObj->createPrms));
        }
    }

    if (FVID2_SOK == retVal)
    {
        retVal = vpsDrvDispCreateInstObj(instObj);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsDrvDispTrace, GT_ERR,
                      "Channel object create failed!!\n");
        }
        else
        {
            instCreateFlag = (UInt32) TRUE;
        }
    }

    if (FVID2_SOK == retVal)
    {
        retVal = vpsDrvDispOpenCore(instObj);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsDrvDispTrace, GT_ERR, "Core open failed!!\n");
        }
        else
        {
            coreCreateFlag = (UInt32) TRUE;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Initialize instance variables */
        BspUtils_memcpy(
            &instObj->fdmCbPrms,
            fdmCbPrms,
            sizeof (instObj->fdmCbPrms));

        instObj->state.isOpened = TRUE;
        instObj->isPrevBufRep   = FALSE;
        drvHandle = instObj;
    }

    /* Return the status if possible */
    if (NULL != createStatusArgs)
    {
        createStatus         = (Vps_DispCreateStatus *) createStatusArgs;
        createStatus->retVal = retVal;
        if (NULL != instObj)
        {
            createStatus->standard       = instObj->standard;
            createStatus->dispWidth      = instObj->dispWidth;
            createStatus->dispHeight     = instObj->dispHeight;
            createStatus->minNumPrimeBuf = VPS_DRV_DISP_MIN_PRIME_BUFFERS;
        }
    }

    if (NULL != instObj)
    {
        /* Deallocate if error occurs */
        if (FVID2_SOK != retVal)
        {
            if ((UInt32) TRUE == coreCreateFlag)
            {
                tempRetVal = vpsDrvDispCloseCore(instObj);
                GT_assert(VpsDrvDispTrace, (FVID2_SOK == tempRetVal));
            }

            if ((UInt32) TRUE == instCreateFlag)
            {
                tempRetVal = vpsDrvDispDeleteInstObj(instObj);
                GT_assert(VpsDrvDispTrace, (FVID2_SOK == tempRetVal));
            }
        }

        /* Post the instance semaphore */
        BspOsal_semPost(instObj->lockSem);
    }

    return (drvHandle);
}

/**
 *  VpsDrv_dispDelete
 *  \brief Display driver delete function. Relinquish the resources allocated
 *  by create function.
 *
 *  This function could be called from task context only.
 *  And is reentrant - could be called from multiple tasks at the same time for
 *  deleting different instances.
 *
 *  \param handle           [IN] Display driver instance handle returned by
 *                          create function.
 *  \param deleteArgs       [IN] Not used currently. Meant for future purpose.
 *                          Set this to NULL.
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
static Int32 VpsDrv_dispDelete(Fdrv_Handle handle, Ptr reserved)
{
    Int32 retVal = FVID2_SOK;
    VpsDrv_DispInstObj *instObj = NULL;

    /* Check for NULL pointers and invalid arguments */
    if (NULL == handle)
    {
        GT_0trace(VpsDrvDispTrace, GT_ERR, "Invalid arguments\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        instObj = (VpsDrv_DispInstObj *) handle;
    }

    if (NULL != instObj)
    {
        /* Take the instance semaphore */
        BspOsal_semWait(instObj->lockSem, BSP_OSAL_WAIT_FOREVER);

        /* Check if already opened. */
        if (TRUE != instObj->state.isOpened)
        {
            GT_0trace(VpsDrvDispTrace, GT_ERR, "ERROR: Driver not opened\n");
            retVal = FVID2_EFAIL;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* If already started, stop it. */
        if (TRUE == instObj->state.isStarted)
        {
            retVal = vpsDrvDispStopIoctl(instObj);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(VpsDrvDispTrace, GT_ERR, "Stop display failed\n");
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        retVal = vpsDrvDispCloseCore(instObj);
        GT_assert(VpsDrvDispTrace, (FVID2_SOK == retVal));

        retVal = vpsDrvDispDeleteInstObj(instObj);
        GT_assert(VpsDrvDispTrace, (FVID2_SOK == retVal));

        /* Reset other variables */
        instObj->state.isOpened      = FALSE;
        instObj->state.isStarted     = FALSE;
        instObj->stat.queueCount     = 0U;
        instObj->stat.dequeueCount   = 0U;
        instObj->stat.dispFrmCount   = 0U;
        instObj->stat.repeatFrmCount = 0U;

        instObj->fdmCbPrms.fdmCbFxn    = NULL;
        instObj->fdmCbPrms.fdmErrCbFxn = NULL;
        instObj->fdmCbPrms.handle      = NULL;
        instObj->fdmCbPrms.errList     = NULL;
        instObj->fdmCbPrms.fdmData     = NULL;
    }

    if (NULL != instObj)
    {
        /* Post the instance semaphore */
        BspOsal_semPost(instObj->lockSem);
    }

    return (retVal);
}

/**
 *  VpsDrv_dispQueue
 *  \brief Display driver queue buffer API. This submits the buffers
 *  to the driver for display.
 *
 *  This function could be called from ISR or task context.
 *  And is reentrant - could be called from multiple tasks/ISR at the same time
 *  to queue buffers for the same or different instances.
 *
 *  \param handle           [IN] Display driver instance handle returned by
 *                          create function.
 *  \param frameList        [IN] Pointer to frame list containing valid
 *                          frame pointers.
 *  \param streamId         [IN] Not used currently. Meant for future purpose.
 *                          Set this to 0.
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
static Int32 VpsDrv_dispQueue(Fdrv_Handle      handle,
                              Fvid2_FrameList *frmList,
                              UInt32           streamId)
{
    Int32  retVal = FVID2_SOK;
    UInt32 frmCnt;
    UInt32 cookie;
    UInt32 reqQCnt;
    UInt32 isBufAccepted;
    Fvid2_Frame        *frm, *newFrm;
    VpsDrv_DispInstObj *instObj;
    VpsDrv_DispQueObj  *qObj, *qObjTemp;

    /* Check for NULL pointers */
    if ((NULL == handle) || (NULL == frmList))
    {
        GT_0trace(VpsDrvDispTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        instObj = (VpsDrv_DispInstObj *) handle;

        /* Check framelist for error and NULL pointer check */
        retVal = Fvid2_checkFrameList(frmList, (UInt32) FVID2_MAX_FRAME_PTR);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsDrvDispTrace, GT_ERR, "Check frame list error\n");
        }

        if (FALSE == instObj->state.isOpened)
        {
            /* If driver handle is not open then skip this frame queue */
            GT_0trace(VpsDrvDispTrace, GT_ERR,
                      "Invalid state: Can't queue to an un-opened instance!!\n");
            retVal = FVID2_EFAIL;
        }

        /* Only one frame submit supportted per instance */
        if (frmList->numFrames > 1U)
        {
            GT_0trace(VpsDrvDispTrace, GT_ERR,
                      "Only one frame submit supported in current design\n");
            retVal = FVID2_EFAIL;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* for all frames that need to be queued */
        for (frmCnt = 0U; frmCnt < frmList->numFrames; frmCnt++)
        {
            /* Get FVID2 frame pointer - NULL check is already done in
             * check frame list function */
            frm = frmList->frames[frmCnt];
            GT_assert(VpsDrvDispTrace, (NULL != frm));

            cookie = BspOsal_disableInterrupt();

            /* Allocate a free queue object from the pool */
            qObj = (VpsDrv_DispQueObj *) BspUtils_dequeue(instObj->bmObj.freeQ);
            if (NULL == qObj)
            {
                BspOsal_restoreInterrupt(cookie);
                GT_0trace(VpsDrvDispTrace, GT_ERR,
                          "ALLOC: Q object allocation failed\n");
                retVal = FVID2_EALLOC;
                break;
            }

            /* Copy the frame to the driver's queue object */
            qObj->frm = frm;
            /* Initial credit count should be zero!! */
            GT_assert(VpsDrvDispTrace, (0U == qObj->creditCnt));
            /* Push mechanism */
            /* 1. Check if the previous frame was repeated
             * 2. Check if request queue is empty
             * 3. If request Queue is not empty then put it in the req queue and
             *    exit.
             * 4. If request queue is empty then push the buffer to core
             * 5. If core accepts then put the buffer in current queue and
             *    update the credit count
             * 6. If core accepts the buffer then make the prevRepBuf as false.
             *    a. This is required if two back to back buffers are queueud in
             *       same frame period.
             *       (The second buffer should not be pushed to core if first
             *        once is accepted)
             * 7. If core doesnt accept the buffer then put it in the request
             *    Queue.
             * 8. In Request Frame call back we set the prevBufRepeated flag
             *    appropriately.
             *    a. Set to true if no buffer is available in req queue
             *    b. Set to false if buffer is given to core
             * 9. Here we will overwrite the buffer present in the curQ with the
             *    new one.Basically what needs to done is to revert what is
             *    being done in reqFrame callback function when the buffer
             *    is repeated. so peak the current queue and decrement
             *    the credit count. It will automatically moved to doneQ in next
             *    frameDone Call back.
             */
            reqQCnt = BspUtils_getNumQElem(instObj->bmObj.reqQ);

            if ((0U == reqQCnt) && (TRUE == instObj->isPrevBufRep))
            {
                /* Call the user buffer program callback */
                if (NULL != instObj->bufPrgmCbFxn)
                {
                    newFrm = instObj->bufPrgmCbFxn(
                        instObj->fdmCbPrms.handle,
                        qObj->frm,
                        FALSE,
                        qObj->creditCnt);
                    if (NULL != newFrm)
                    {
                        /* Swap the current frame */
                        qObj->frm = newFrm;
                    }
                }

                qObj->coreFrm.addr[0][0] = qObj->frm->addr[0][0];
                qObj->coreFrm.addr[0][1] = qObj->frm->addr[0][1];
                qObj->coreFrm.addr[0][2] = qObj->frm->addr[0][2];

                qObj->coreFrm.addr[1][0] = qObj->frm->addr[1][0];
                qObj->coreFrm.addr[1][1] = qObj->frm->addr[1][1];
                qObj->coreFrm.addr[1][2] = qObj->frm->addr[1][2];

                isBufAccepted = instObj->coreOps->progBuffer(
                    instObj->coreHandle,
                    &qObj->coreFrm,
                    instObj->bmObj.bypassLowLatencyCheck);

                if ((UInt32) TRUE == isBufAccepted)
                {
                    /* Decrement the credit count of previously repeated buffer,
                     * This is not a repeat now as we are overwriting the
                     * buffer */
                    qObjTemp = (VpsDrv_DispQueObj *) BspUtils_peakTail(
                        instObj->bmObj.curQ);
                    /* This can't return NULL unless there is a bug in the
                     * buffer management */
                    GT_assert(VpsDrvDispTrace, (NULL != qObjTemp));
                    qObjTemp->creditCnt--;

                    BspUtils_queue(instObj->bmObj.curQ, &qObj->qElem, qObj);
                    qObj->creditCnt++;
                    instObj->isPrevBufRep = FALSE;
                    /* This is like a queue only, so increment the count*/
                    instObj->stat.queueCount++;
                }
                else
                {
                    /* Add the queue object in driver's request queue */
                    BspUtils_queue(instObj->bmObj.reqQ, &qObj->qElem, qObj);
                    instObj->stat.queueCount++;
                }
            }
            else
            {
                /* Add the queue object in driver's request queue */
                BspUtils_queue(instObj->bmObj.reqQ, &qObj->qElem, qObj);
                instObj->stat.queueCount++;
            }

            BspOsal_restoreInterrupt(cookie);

            /* Mark frame in frmList as NULL */
            frmList->frames[frmCnt] = NULL;
        }
    }

    return (retVal);
}

/**
 *  VpsDrv_dispDequeue
 *  \brief Display driver dequeue buffer API. This returns the displayed
 *  buffers from the driver.
 *
 *  The behaviour of this function depends on whether the display is in
 *  progress or not. When display is in progress, this will return the
 *  the displayed buffers from the driver's done queue. If done queue is
 *  empty, then it returns FVID2_EAGAIN, indicating the application to try
 *  again after sometime (used in polling mode).
 *  When display is stopped, this returns the displayed buffers, display in
 *  progress buffers, buffers in input request queue in that order. This
 *  is used by the application to flush out any driver owned buffers before
 *  deleting the display driver. When no more buffers are with the driver,
 *  then it returns FVID2_ENO_MORE_BUFFERS.
 *
 *  This function could be called from ISR or task context.
 *  And is reentrant - could be called from multiple tasks/ISR at the same time
 *  to queue buffers for the same or different instances.
 *
 *  \param handle           [IN] Display driver instance handle returned by
 *                          create function.
 *  \param frameList        [IN] Pointer to frame list containing valid
 *                          frame pointers.
 *  \param streamId         [IN] Not used currently. Meant for future purpose.
 *                          Set this to 0.
 *  \param timeout          [IN] Not used currently. Meant for future purpose.
 *                          Set this to FVID2_TIMEOUT_NONE.
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
static Int32 VpsDrv_dispDequeue(Fdrv_Handle      handle,
                                Fvid2_FrameList *frmList,
                                UInt32           streamId,
                                UInt32           timeout)
{
    Int32  retVal = FVID2_SOK;
    UInt32 cookie;
    VpsDrv_DispInstObj   *instObj;
    VpsDrv_DispQueObj    *qObj;
    VpsDrv_DispBufManObj *bmObj;

    /* Check for NULL pointers */
    if ((NULL == handle) || (NULL == frmList) || (streamId > 0U))
    {
        GT_0trace(VpsDrvDispTrace, GT_ERR, "Invalid argument!!\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        instObj = (VpsDrv_DispInstObj *) handle;
        bmObj   = &instObj->bmObj;

        if (FALSE == instObj->state.isOpened)
        {
            GT_0trace(
                VpsDrvDispTrace, GT_ERR,
                "Invalid state: Can't dequeue to an un-opened instance!!\n");
            retVal = FVID2_EFAIL;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* init frame list fields */
        frmList->numFrames  = 0U;
        frmList->perListCfg = NULL;

        cookie = BspOsal_disableInterrupt();

        /* Get a completed queue object from driver's done queue */
        qObj = (VpsDrv_DispQueObj *) BspUtils_dequeue(bmObj->doneQ);
        if (NULL == qObj)
        {
            /* When display is stopped, give back all the driver owned buffer
             * including the current programmed and the buffers in request
             * queue */
            if (TRUE != instObj->state.isStarted)
            {
                /* Give the buffers in current state */
                qObj = (VpsDrv_DispQueObj *) BspUtils_dequeue(bmObj->curQ);
                if (NULL == qObj)
                {
                    /* At last give back the buffers in request queue as well */
                    qObj = (VpsDrv_DispQueObj *) BspUtils_dequeue(bmObj->reqQ);
                }

                /* Check if all these operation has failed */
                if (NULL == qObj)
                {
                    GT_0trace(VpsDrvDispTrace, GT_DEBUG,
                              "NO_MORE_BUFFERS: No more buffers with driver\n");
                    retVal = FVID2_ENO_MORE_BUFFERS;
                }
            }
            else
            {
                GT_0trace(VpsDrvDispTrace, GT_DEBUG,
                          "AGAIN: Out queue Empty. Try again\n");
                retVal = FVID2_EAGAIN;
            }
        }

        BspOsal_restoreInterrupt(cookie);

        /* Copy the driver's frame list to application's frame list */
        if (NULL != qObj)
        {
            cookie = BspOsal_disableInterrupt();

            GT_assert(VpsDrvDispTrace, (NULL != qObj->frm));
            frmList->frames[frmList->numFrames] = qObj->frm;
            frmList->numFrames++;

            /* Give back the queue object back to the free pool */
            qObj->frm = NULL;
            /* At time of deqeue, credit should be zero!! */
            GT_assert(VpsDrvDispTrace, (0U == qObj->creditCnt));
            BspUtils_queue(bmObj->freeQ, &qObj->qElem, qObj);
            instObj->stat.dequeueCount++;

            BspOsal_restoreInterrupt(cookie);
        }
    }

    return (retVal);
}

/**
 *  VpsDrv_dispControl
 *  \brief Display driver control function. This function implements various
 *  IOCTLS.
 *
 *  All IOCTLS are blocking and could not be called from ISR context unless
 *  otherwise specified for a particular IOCTL.
 *
 *  cmd             : FVID2_START
 *  cmdArgs         : NULL
 *  cmdStatusArgs   : NULL
 *  Description     : Starts the display. At least minimum number of buffers
 *                    should be queued before calling start IOCTL.
 *
 *  cmd             : FVID2_STOP
 *  cmdArgs         : NULL
 *  cmdStatusArgs   : NULL
 *  Description     : Stops the display
 *
 *  cmd             : IOCTL_VPS_DISP_GET_STATUS
 *  cmdArgs         : Vps_DispStatus *
 *  cmdStatusArgs   : NULL
 *  Description     : Gets the current display status information.
 *
 *  \param handle           [IN] Display driver instance handle returned by
 *                          create function.
 *  \param cmd              [IN] Supports the above mentioned commands.
 *  \param cmdArgs          [IN] Depending on the command this will vary.
 *  \param cmdStatusArgs    [OUT] Depending on the command this will vary.
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
static Int32 VpsDrv_dispControl(Fdrv_Handle handle,
                                UInt32      cmd,
                                Ptr         cmdArgs,
                                Ptr         cmdStatusArgs)
{
    Int32 retVal = FVID2_SOK;
    VpsDrv_DispInstObj *instObj;

    /* Check for NULL pointers */
    if (NULL == handle)
    {
        GT_0trace(VpsDrvDispTrace, GT_ERR, "Invalid argument!!\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        instObj = (VpsDrv_DispInstObj *) handle;
        switch (cmd)
        {
            case FVID2_START:
                retVal = vpsDrvDispStartIoctl(instObj);
                break;

            case FVID2_STOP:
                retVal = vpsDrvDispStopIoctl(instObj);
                break;

            case IOCTL_VPS_DISP_GET_STATUS:
                retVal = vpsDrvDispGetStatusIoctl(
                    instObj,
                    (Vps_DispStatus *) cmdArgs);
                break;

            case IOCTL_VPS_DISP_REGISTER_BUF_PRGM_CB:
                retVal = vpsDrvDispRegisterBufPrgmCbIoctl(
                    instObj,
                    (const Vps_DispBufPrgmCbFxnParams *) cmdArgs);
                break;

            case IOCTL_VPS_DISP_BYPASS_LOW_LATENCY_CHECK:
                retVal = vpsDrvDispBypassLowLatencyCheckIoctl(
                    instObj,
                    (const Vps_DispBypassLowLatencyCheckParams *)
                    cmdArgs);
                break;

            case IOCTL_VPS_DISP_SET_DSS_PARAMS:
                if (NULL != cmdArgs)
                {
                    retVal = vpsDrvDispSetDssCoreParams(
                        instObj,
                        (Vps_DispDssParams *) cmdArgs);
                }
                else
                {
                    GT_0trace(VpsDrvDispTrace, GT_ERR, "NULL argument\n");
                    retVal = FVID2_EBADARGS;
                }
                break;

            case IOCTL_VPS_DISP_GET_DSS_PARAMS:
                if (NULL != cmdArgs)
                {
                    retVal = vpsDrvDispGetDssCoreParams(
                        instObj,
                        (Vps_DispDssParams *) cmdArgs);
                }
                else
                {
                    GT_0trace(VpsDrvDispTrace, GT_ERR, "NULL argument\n");
                    retVal = FVID2_EBADARGS;
                }
                break;

            case IOCTL_VPS_DISP_SET_CSC_COEFF:
                if (NULL != cmdArgs)
                {
                    retVal = vpsDrvDispSetDssCscCoeff(
                        instObj,
                        (Vps_DssCscCoeff *) cmdArgs);
                }
                else
                {
                    GT_0trace(VpsDrvDispTrace, GT_ERR, "NULL argument\n");
                    retVal = FVID2_EBADARGS;
                }
                break;

            default:
                GT_0trace(VpsDrvDispTrace, GT_ERR,
                          "UNSUPPORTED_CMD: IOCTL not supported\n");
                retVal = FVID2_EUNSUPPORTED_CMD;
                break;
        }
    }

    return (retVal);
}

/**
 *  vpsDrvDispStartIoctl
 *  \brief Implements the start display IOCTL.
 *
 *  Returns FVID2_SOK on success else returns appropriate error code.
 */
static Int32 vpsDrvDispStartIoctl(VpsDrv_DispInstObj *instObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 numElemInReqQ;
    VpsDrv_DispBufManObj *bmObj;

    /* Check for NULL pointers */
    GT_assert(VpsDrvDispTrace, (NULL != instObj));

    /* Take the instance semaphore */
    BspOsal_semWait(instObj->lockSem, BSP_OSAL_WAIT_FOREVER);

    bmObj = &instObj->bmObj;

    /* Initialize instance variables that needs to be reset in stop/start
     * sequence */
    instObj->stat.dispFrmCount   = 0U;
    instObj->stat.repeatFrmCount = 0U;
    bmObj->expectedFid           = 0U;
    bmObj->curFid = 0U;

    /* Check if the number of elements in the queue is sufficient to */
    numElemInReqQ = BspUtils_getNumQElem(instObj->bmObj.reqQ);
    /* Check if the primed buffers are sufficient */
    if (numElemInReqQ < VPS_DRV_DISP_MIN_PRIME_BUFFERS)
    {
        GT_0trace(VpsDrvDispTrace, GT_ERR, "Insufficient buffers queued\n");
        retVal = FVID2_EFAIL;
    }

    if (FVID2_SOK == retVal)
    {
        /* Start display */
        instObj->state.isStarted = TRUE;
        retVal = vpsDrvDispStartCore(instObj);
        if (FVID2_SOK != retVal)
        {
            instObj->state.isStarted = FALSE;
            GT_0trace(VpsDrvDispTrace, GT_ERR, "Core start failed!!\n");
        }
    }

    /* Post the instance semaphore */
    BspOsal_semPost(instObj->lockSem);

    return (retVal);
}

/**
 *  vpsDrvDispStopIoctl
 *  \brief Implements the stop display IOCTL.
 *
 *  When the display is stopped, this function queues back the on going frame
 *  back to the input request queue so that when the display starts again,
 *  it starts displaying from the current un-displayed frame.
 *
 *  Returns FVID2_SOK on success else returns appropriate error code.
 */
static Int32 vpsDrvDispStopIoctl(VpsDrv_DispInstObj *instObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 cookie;
    VpsDrv_DispQueObj *qObj;

    /* Check for NULL pointers */
    GT_assert(VpsDrvDispTrace, (NULL != instObj));

    /* Take the instance semaphore */
    BspOsal_semWait(instObj->lockSem, BSP_OSAL_WAIT_FOREVER);

    retVal = vpsDrvDispStopCore(instObj);
    if (FVID2_SOK == retVal)
    {
        cookie = BspOsal_disableInterrupt();

        instObj->state.isStarted = FALSE;

        /* Take the buffers in current state and push them in to the request
         * queue so that the next start will use those buffers */
        while (1U)
        {
            qObj = (VpsDrv_DispQueObj *) BspUtils_dequeue(instObj->bmObj.curQ);
            if (NULL == qObj)
            {
                break;
            }
            qObj->creditCnt = 0U;

            /* Push it to the request queue */
            BspUtils_queueBack(instObj->bmObj.reqQ, &qObj->qElem, qObj);
        }

        BspOsal_restoreInterrupt(cookie);
    }

    /* Post the instance semaphore */
    BspOsal_semPost(instObj->lockSem);

    return (retVal);
}

/**
 *  vpsDrvDispGetStatusIoctl
 *  \brief Gets the current display status information.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns FVID2_SOK on success else returns appropriate error code.
 */
static Int32 vpsDrvDispGetStatusIoctl(VpsDrv_DispInstObj *instObj,
                                      Vps_DispStatus     *dispStat)

{
    Int32 retVal = FVID2_SOK;
    VpsCore_DssVidErrorStatus errStatus;

    /* Check for NULL pointers */
    GT_assert(VpsDrvDispTrace, (NULL != instObj));

    /* Take the instance semaphore */
    BspOsal_semWait(instObj->lockSem, BSP_OSAL_WAIT_FOREVER);

    if (NULL == dispStat)
    {
        GT_0trace(VpsDrvDispTrace, GT_ERR, "Invalid argument!!\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        retVal = vpsDrvDispGetCoreErrStat(instObj, &errStatus);

        if (retVal == FVID2_SOK)
        {
            instObj->stat.underflowCount = errStatus.vidBufferUnderflow;

            BspUtils_memcpy(
                dispStat,
                &instObj->stat,
                sizeof (instObj->stat));
        }
    }

    /* Post the instance semaphore */
    BspOsal_semPost(instObj->lockSem);

    return (retVal);
}

/**
 *  vpsDrvDispRegisterBufPrgmCbIoctl
 *  \brief Register buffer program callback function IOCTL.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns FVID2_SOK on success else returns appropriate error code.
 */
static Int32 vpsDrvDispRegisterBufPrgmCbIoctl(
    VpsDrv_DispInstObj               *instObj,
    const Vps_DispBufPrgmCbFxnParams *bufPrgmCbPrms)
{
    Int32 retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(VpsDrvDispTrace, (NULL != instObj));

    /* Take the instance semaphore */
    BspOsal_semWait(instObj->lockSem, BSP_OSAL_WAIT_FOREVER);

    /* Check for NULL pointers */
    if (NULL == bufPrgmCbPrms)
    {
        GT_0trace(VpsDrvDispTrace, GT_ERR, "Invalid argument!!\n");
        retVal = FVID2_EBADARGS;
    }

    /* IOCTL supportted only when display is stopped */
    if (TRUE == instObj->state.isStarted)
    {
        GT_0trace(VpsDrvDispTrace, GT_ERR, "Display in progress!!\n");
        retVal = FVID2_EFAIL;
    }

    if (FVID2_SOK == retVal)
    {
        instObj->bufPrgmCbFxn = bufPrgmCbPrms->bufPrgmCbFxn;
    }

    /* Post the instance semaphore */
    BspOsal_semPost(instObj->lockSem);

    return (retVal);
}

static Int32 vpsDrvDispBypassLowLatencyCheckIoctl(
    VpsDrv_DispInstObj                        *instObj,
    const Vps_DispBypassLowLatencyCheckParams *bypassPrms)
{
    Int32 retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(VpsDrvDispTrace, (NULL != instObj));

    /* Take the instance semaphore */
    BspOsal_semWait(instObj->lockSem, BSP_OSAL_WAIT_FOREVER);

    /* Check for NULL pointers */
    if (NULL == bypassPrms)
    {
        GT_0trace(VpsDrvDispTrace, GT_ERR, "Invalid argument!!\n");
        retVal = FVID2_EBADARGS;
    }

    /* IOCTL supportted only when display is stopped */
    if (TRUE == instObj->state.isStarted)
    {
        GT_0trace(VpsDrvDispTrace, GT_ERR, "Display in progress!!\n");
        retVal = FVID2_EFAIL;
    }

    if (FVID2_SOK == retVal)
    {
        instObj->bmObj.bypassLowLatencyCheck =
            bypassPrms->bypassLowLatencyCheck;
    }

    /* Post the instance semaphore */
    BspOsal_semPost(instObj->lockSem);

    return (retVal);
}

