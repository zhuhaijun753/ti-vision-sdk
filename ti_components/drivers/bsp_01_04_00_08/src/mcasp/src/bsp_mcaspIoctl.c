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
 *  \file   Mcasp_ioctl.c
 *
 *  \brief  This files contains the ioctl functions required for the Mcasp
 *          driver to execute the control commands.
 *
 *  \version   0.1 Created for DM814x/C6A811x platform.
 *
 */

/* ========================================================================== */
/*                             INCLUDE FILES                                  */
/* ========================================================================== */

#include <xdc/std.h>
#include <assert.h>
#include <ti/sysbios/io/IOM.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/sysbios/knl/Swi.h>

#include <mcasp/bsp_mcasp.h>
#include <bsp_mcaspPriv.h>

#ifdef Mcasp_LOOPJOB_ENABLED
extern Mcasp_TempBuffer Mcasp_loopDstBuf[CSL_MCASP_PER_CNT];
extern Mcasp_TempBuffer Mcasp_loopSrcBuf[CSL_MCASP_PER_CNT];
#endif  /* Mcasp_LOOPJOB_ENABLED */
/* ========================================================================== */
/*                          LOCAL FUNCTION PROTOTYPES                         */
/* ========================================================================== */

static Void mcaspConfigLoopBack(Mcasp_HwHandle hMcasp, Bool loopBack);

#ifdef Mcasp_LOOPJOB_ENABLED
static Void mcaspActivateRcvClkSer(Mcasp_HwHandle hMcasp);

static Void mcaspActivateXmtClkSer(Mcasp_HwHandle hMcasp);

static Void mcaspActivateClkRcvXmt(Mcasp_HwHandle hMcasp);
#endif

#if 0
static UInt8 mcaspGetSmFsRcv(Mcasp_HwHandle hMcasp);

static UInt8 mcaspGetSmFsXmt(Mcasp_HwHandle hMcasp);
#endif

static Int32 mcaspSetSamplingRate(Mcasp_ChannelHandle chanHandle,
                                  Ptr                 ioctlArg);
static Void mcaspDeviceInfoGet(Mcasp_ChannelHandle chanHandle,
                               Ptr                 arg);

static Int32 mcaspGetHwStatus(Mcasp_HwHandle      hMcasp,
                              Mcasp_HwStatusQuery myQuery,
                              Void               *response);

static Void mcaspReadXmtConfig(Mcasp_HwHandle             hMcasp,
                               Mcasp_HwSetupData   *const xmtData);

static Void mcaspReadRcvConfig(Mcasp_HwHandle             hMcasp,
                               Mcasp_HwSetupData   *const rcvData);

static Void mcaspGetSerMode(Mcasp_HwHandle      hMcasp,
                            Mcasp_SerMode      *serMode,
                            Mcasp_SerializerNum serNum);

static Void mcaspGetSerRcvReady(Mcasp_HwHandle      hMcasp,
                                Bool               *serRcvReady,
                                Mcasp_SerializerNum serNum);

static Void mcaspGetSerXmtReady(Mcasp_HwHandle      hMcasp,
                                Bool               *serXmtReady,
                                Mcasp_SerializerNum serNum);

/* ========================================================================== */
/*                           FUNCTION DEFINTIONS                              */
/* ========================================================================== */

/**
 *  \brief  This function executes the control commands passed by the IDriver,
 *          the application passes the control command required to the IDriver
 *          uisng the stream control function. The IDriver function then calls
 *          this function which then actually executes the control command.
 *
 *  \param  chanHandle  [IN]  Handle to channel
 *  \param  cmd         [IN]  Control command number
 *  \param  arg         [IN]  Arguments for control command
 *  \param  param       [IN]  user defined data structure
 *  \param  eb          [OUT] pointer to the error block
 *
 *  \return Appropriate error code in case of failure else IOM_COMPLETED
 *          is returned
 *
 * \entry   chanHandle  should be non NULL and valid pointer
 *          cmd         should be a valid value
 *          arg         arg can be NULL or any valid value
 *          param       should be a valid value
 *
 * \leave   Not implemented
 */
Int32 Mcasp_localSubmitIoctl(Mcasp_ChannelHandle chanHandle,
                             Uns                 cmd,
                             Ptr                 arg,
                             Ptr                 param)
{
    Mcasp_Object       *instHandle = NULL;
    Mcasp_ChannelHandle iohandlep  = NULL;
    Int16 serNum    = 0;
    UInt32 tempVal  = 0;
    UInt32 queryRes = 0;
    Int32 status    = IOM_COMPLETED;
    Bool dlbMode    = (Bool) FALSE;
    Bool falsewhile = (Bool) TRUE;
    Mcasp_HwSetupData  *chanSetup    = NULL;
    Mcasp_HwSetup      *mcaspHwSetup = NULL;
    UInt32 timeout = Mcasp_POLLED_RETRYCOUNT;
#ifdef Mcasp_LOOPJOB_ENABLED
    Mcasp_ChanParams   *params  = NULL;
    EDMA3_DRV_PaRAMRegs pramPtr = {0};
    EDMA3_DRV_SyncType  syncType;
    IOM_Packet         *ioPacket = NULL;
    Int16  linkCnt = 0;
    Bool   tempQueueStatus;
    Void  *tempCastPacket;
    Bool   breakLoop = (Bool) FALSE;
#endif
    UInt16 tempSerStatus;

    /* Validate the input parameters                                          */
    assert(NULL != chanHandle);
    assert(NULL != chanHandle->devHandle);

    instHandle = (Mcasp_Object *) chanHandle->devHandle;

    assert(NULL != instHandle);

    /* To remove the compiler warning                                         */
    param = param;

    /*--------------------MCASP IOCTL FOR HANDLING TIMEOUT--------------------*/

    if (((Uns)IOCTL_MCASP_CHAN_TIMEDOUT == cmd) ||
        ((Uns)IOCTL_MCASP_CHAN_RESET == cmd) ||
        ((Uns)IOM_CHAN_RESET == cmd) ||
        ((Uns) IOM_CHAN_TIMEDOUT == cmd))
    {
        /* To be called in case of channel timeoutand reset                   */
        status = Mcasp_localAbortReset((Mcasp_ChannelHandle) chanHandle);
    }
    /*---------------------------MCASP RESET CMD -----------------------------*/
    else if ((IOCTL_MCASP_DEVICE_RESET == cmd) ||
             ((Uns) IOM_DEVICE_RESET == cmd))
    {
        /* Abort all the request, give application callback and configure     *
         * EDMA in the LOOPJOB for both input and output channels             */
        Mcasp_localAbortRequests(&(instHandle->RcvObj), NULL);
        Mcasp_localAbortRequests(&(instHandle->XmtObj), NULL);
    }
    /*-------------------------MCASP DRIVER MODE------------------------------*/
    else if (IOCTL_MCASP_QUERY_LOOPJOB_MODE == cmd)
    {
        /* Query the working mode of the driver                               */
        assert(NULL != arg);

        *(Bool *) arg = instHandle->loopJobMode;
    }
    /*---------------------MCASP SET CHANNEL SETTINGS CMD --------------------*/
    else if (IOCTL_MCASP_CNTRL_SET_FORMAT_CHAN == cmd)
    {
        do
        {
            falsewhile = (Bool) FALSE;

            if (NULL == arg)
            {
                status = IOM_EBADARGS;
            }

            if (IOM_COMPLETED == status)
            {
                /* Reprogram xmt/rcv format unit registers. State m/c         *
                 * associated with channel should have been reset.            *
                 * a pointer to h/w setup data would have been passed through *
                 * the argument field.                                        */

                chanSetup = (Mcasp_HwSetupData *) arg;

                /* Stop the xmt/rcv state machine.                            */
                Mcasp_localSmReset((Mcasp_ChannelHandle) chanHandle);

                if (Mcasp_ChanMode_RCV == chanHandle->channelOpMode)
                {
                    /* Check if receive state machine and frame sync are reset*/
                    status = mcaspGetHwStatus(
                        &(instHandle->hwInfo),
                        Mcasp_HwStatusQuery_SM_FS_RCV,
                        &queryRes);
                }
                else
                {
                    /* Check if transmit state machine & frame sync are reset */
                    status = mcaspGetHwStatus(
                        &(instHandle->hwInfo),
                        Mcasp_HwStatusQuery_SM_FS_XMT,
                        &queryRes);
                }
                if (IOM_COMPLETED != status)
                {
                    status = IOM_EBADMODE;
                }
            }

            if ((Mcasp_SM_RESET != queryRes) && (IOM_COMPLETED == status))
            {
                /* The corresponding state m/c and frame sync have to be  *
                 * reset. And they are not. So return error.              */
                status = IOM_EBADARGS;
            }
            if (IOM_COMPLETED == status)
            {
                if ((Mcasp_ChanMode_XMT_DIT == chanHandle->channelOpMode)
                    || (Mcasp_ChanMode_XMT_TDM == chanHandle->channelOpMode))
                {
                    /* Configure transmit section
                     *                             */
                    status = Mcasp_localConfigXmtSection(
                        instHandle,
                        (Mcasp_HwSetupData *) chanSetup);
                }
                else
                {
                    /* Configure receive section                              */
                    status = Mcasp_localConfigRcvSection(
                        instHandle,
                        (Mcasp_HwSetupData *) chanSetup);
                }
                if (IOM_COMPLETED != status)
                {
                    /* Error configuring section.Mark channel state as INVALID*/
                    chanHandle->chanState = Mcasp_DriverState_CLOSED;
                }
                else
                {
                    /* Stop the xmt/rcv state machine.
                     *                           */
                    Mcasp_localSmSet((Mcasp_ChannelHandle) chanHandle);
                }
            }
        } while (falsewhile);
    }
    /*-----------------MCASP GET CHANNEL SETTINGS CMD --------------------*/
    else if (IOCTL_MCASP_CNTRL_GET_FORMAT_CHAN == cmd)
    {
        do
        {
            falsewhile = (Bool) FALSE;

            if (NULL == arg)
            {
                status = IOM_EBADARGS;
                break;
            }

            /* Read xmt/rcv format unit registers. A pointer to h/w setup *
             * data would have been passed through the argument field.    */
            chanSetup = (Mcasp_HwSetupData *) arg;

            if ((Mcasp_ChanMode_XMT_DIT == chanHandle->channelOpMode)
                || (Mcasp_ChanMode_XMT_TDM == chanHandle->channelOpMode))
            {
                /* Read transmit section infomration                      */
                mcaspReadXmtConfig(&(instHandle->hwInfo), chanSetup);
            }
            else
            {
                /* Read receive section information                       */
                mcaspReadRcvConfig(&(instHandle->hwInfo), chanSetup);
            }
        } while (falsewhile);
    }
    /*---------------------MCASP SET GBL REG CMD -------------------------*/
    else if (IOCTL_MCASP_CNTRL_SET_GBL_REGS == cmd)
    {
        do
        {
            falsewhile = (Bool) FALSE;

            if (NULL == arg)
            {
                status = IOM_EBADARGS;
                break;
            }

            /* This will program the global registers. Both channels will *
             * be reset and global registers programmed. A pointer to h/w *
             * setup would have been passed through the argument field.   */
            mcaspHwSetup = (Mcasp_HwSetup *) arg;

            if ((Mcasp_ChanMode_XMT_DIT == chanHandle->channelOpMode)
                || (Mcasp_ChanMode_XMT_TDM == chanHandle->channelOpMode))
            {
                McASPTxReset(instHandle->hwInfo.regs);
            }
            else
            {
                McASPRxReset(instHandle->hwInfo.regs);
            }

            Mcasp_localSetupHwInfo(&instHandle->hwInfo, mcaspHwSetup);
        } while (falsewhile);
    }
    /*-----------------------MCASP SET DIT CMD ---------------------------*/
    else if (IOCTL_MCASP_SET_DIT_MODE == cmd)
    {
        do
        {
            falsewhile = (Bool) FALSE;

            if (NULL == arg)
            {
                status = IOM_EBADARGS;
                break;
            }

            /* This will set the DIT mode                                 */
            tempVal = *(UInt32 *) arg;

            if ((Mcasp_ChanMode_XMT_DIT == instHandle->XmtObj.channelOpMode)
                || (Mcasp_ChanMode_XMT_TDM == instHandle->XmtObj.channelOpMode))
            {
                McASPDITModeCtlWrite(instHandle->hwInfo.regs, tempVal);
                chanHandle->channelOpMode = Mcasp_ChanMode_XMT_DIT;
            }
        } while (falsewhile);
    }
    /*-----------------------MCASP LOOPBACK CMD  -------------------------*/
    else if (IOCTL_MCASP_SET_DLB_MODE == cmd)
    {
        do
        {
            falsewhile = (Bool) FALSE;

            /* This will program the digital loopback mode.               */
            if (NULL == arg)
            {
                status = IOM_EBADARGS;
            }
            if (IOM_COMPLETED == status)
            {
                dlbMode   = *(Bool *) arg;
                iohandlep = &instHandle->RcvObj;
                if (NULL == iohandlep)
                {
                    /* May lead to unexpected results.Revert with error status*/
                    status = IOM_EBADMODE;
                }
            }
            if (IOM_COMPLETED == status)
            {
                /* May lead to unexpected results.Revert with error status*/
                if (NULL != iohandlep->dataPacket)
                {
                    status = IOM_EBADMODE;
                }
            }
            if (IOM_COMPLETED == status)
            {
                queryRes = (UInt32) iohandlep->noOfSerAllocated;

                iohandlep = &instHandle->XmtObj;
                if (NULL != iohandlep->dataPacket)
                {
                    /* May lead to unexpected results.Revert with error status*/
                    status = IOM_EBADMODE;
                }
                if (queryRes != iohandlep->noOfSerAllocated)
                {
                    /* Need equal number of serializers for DLB mode          */
                    status = IOM_EBADMODE;
                }
            }

            if (IOM_COMPLETED == status)
            {
                tempSerStatus = instHandle->hwInfo.numOfSerializers -
                                (UInt16) (1U);
                while (serNum < (Int16) tempSerStatus)
                {
                    if (Mcasp_SerializerStatus_FREE !=
                        instHandle->serStatus[serNum])
                    {
                        if (Mcasp_SerializerStatus_FREE !=
                            instHandle->serStatus[serNum + 1])
                        {
                            /* Increment serializers counter
                             *                  */
                            serNum += 2;
                        }
                        else
                        {
                            /* Serializers not in sequence                    */
                            status = IOM_EBADMODE;
                        }
                    }
                    else
                    {
                        if (Mcasp_SerializerStatus_FREE ==
                            instHandle->serStatus[serNum + 1])
                        {
                            /* Increment serializers counter
                             *                  */
                            serNum += 2;
                        }
                        else
                        {
                            /* Serializers not in sequence                    */
                            status = IOM_EBADMODE;
                        }
                    }
                    if (IOM_COMPLETED != status)
                    {
                        break;
                    }
                    tempSerStatus = instHandle->hwInfo.numOfSerializers -
                                    (UInt16) (1U);
                }
            }

            if (IOM_COMPLETED != status)
            {
                /* Error in setup!                                        */
                status = IOM_EBADIO;
            }
            if (IOM_COMPLETED == status)
            {
                mcaspConfigLoopBack(&(instHandle->hwInfo), dlbMode);

                Mcasp_localActivateSmFsForBoth(instHandle);
            }
        } while (falsewhile);
    }
    /*------------------------MCASP MUTE CMD  ----------------------------*/
    else if (IOCTL_MCASP_CNTRL_AMUTE == cmd)
    {
        do
        {
            falsewhile = (Bool) FALSE;

            if (NULL == arg)
            {
                status = IOM_EBADARGS;
                break;
            }

            tempVal = *(UInt32 *) arg;

            /* Enable or Disable AMUTE register                           */
        } while (falsewhile);
    }
    /*----------------------MCASP IOCTL QUERY  CMD -----------------------*/
    else if (IOCTL_MCASP_QUERY_MUTE == cmd)
    {
        do
        {
            falsewhile = (Bool) FALSE;
            status     = mcaspGetHwStatus(
                &(instHandle->hwInfo),
                Mcasp_HwStatusQuery_AMUTE,
                &queryRes);

            /*Sending back the value of the Amute Register                */
            *(UInt32 *) arg = queryRes;
        } while (falsewhile);
    }
#ifdef Mcasp_LOOPJOB_ENABLED
    /*-------------------MCASP LOOP JOB MODIFY CMD -----------------------*/
    /* Enable / disable loopjob. If the buffer pointer is, NULL then      *
     * disable loopjob not NULL then enable the loop job and asign buffer *
     * pointer to prdbuf                                                  */
    else if (IOCTL_MCASP_CTRL_MODIFY_LOOPJOB == cmd)
    {
        do
        {
            falsewhile = (Bool) FALSE;
            params     = (Mcasp_ChanParams *) arg;

            if (NULL == params)
            {
                status = IOM_EBADARGS;
            }

            if (((Bool) TRUE == chanHandle->isDmaDriven) &&
                (IOM_COMPLETED == status))
            {
                status = EDMA3_DRV_getPaRAM(
                    (EDMA3_DRV_Handle) chanHandle->edmaHandle,
                    chanHandle->pramTbl[ \
                        ((chanHandle->nextLinkParamSetToBeUpdated + 1) % 2)],
                    &pramPtr);

                if (IOM_COMPLETED == status)
                {
                    /* Here we need to change only the buffer pointer and the *
                     * length of the array which will go into bcnt            */
                    if (IOM_OUTPUT == (chanHandle->mode))
                    {
                        chanHandle->loopJobBuffer =
                            &Mcasp_loopSrcBuf[(instHandle->instNum)].
                            scratchBuffer;

                        chanHandle->loopJobLength =
                            (chanHandle->roundedWordWidth
                             * chanHandle->noOfSlots
                             * chanHandle->noOfSerAllocated);

                        if (NULL != params->userLoopJobBuffer)
                        {
                            /* user specified loop job is loaded
                             *                 */
                            chanHandle->userLoopJob = (Bool) TRUE;

                            chanHandle->loopJobBuffer =
                                params->userLoopJobBuffer;
                            chanHandle->userLoopJobLength =
                                params->userLoopJobLength;

                            status = Mcasp_localGetIndicesSyncType(
                                chanHandle,
                                &(pramPtr.srcBIdx),
                                &(pramPtr.srcCIdx),
                                &(pramPtr.aCnt),
                                &(pramPtr.bCnt),
                                &(pramPtr.cCnt),
                                &syncType,
                                (Bool) TRUE);
                            pramPtr.srcAddr =
                                (UInt32) params->userLoopJobBuffer;
                        }
                        else
                        {
                            status = IOM_EBADARGS;
                        }
                    }
                    else
                    {
                        chanHandle->loopJobBuffer =
                            &Mcasp_loopSrcBuf[(instHandle->instNum)].
                            scratchBuffer;

                        chanHandle->loopJobLength =
                            (chanHandle->roundedWordWidth
                             * chanHandle->noOfSlots
                             * chanHandle->noOfSerAllocated);

                        if (NULL != params->userLoopJobBuffer)
                        {
                            /* user specified loop job is loaded
                             *                 */
                            chanHandle->userLoopJob = (Bool) TRUE;

                            chanHandle->loopJobBuffer =
                                params->userLoopJobBuffer;
                            chanHandle->userLoopJobLength =
                                params->userLoopJobLength;

                            status = Mcasp_localGetIndicesSyncType(
                                chanHandle,
                                &(pramPtr.destBIdx),
                                &(pramPtr.destCIdx),
                                &(pramPtr.aCnt),
                                &(pramPtr.bCnt),
                                &(pramPtr.cCnt),
                                &syncType,
                                (Bool) TRUE);
                            pramPtr.destAddr =
                                (UInt32) params->userLoopJobBuffer;
                        }
                        else
                        {
                            status = IOM_EBADARGS;
                        }
                    }
                }
                if (IOM_COMPLETED == status)
                {
                    status = EDMA3_DRV_setPaRAM(
                        (EDMA3_DRV_Handle) chanHandle->edmaHandle,
                        chanHandle->pramTbl[ \
                            ((chanHandle->nextLinkParamSetToBeUpdated +
                              1) % 2)],
                        &pramPtr);
                }
            }
            else
            {
                status = IOM_ENOTIMPL;
            }
        } while (falsewhile);
    }
    /*----------------------- MCASP MUTE ON CMD --------------------------*/
    /* MUTE-ON command implementation Typical implementation for Mute is  *
     * writing zero data in buffer instead of writing real data.          */
    else if (IOCTL_MCASP_CTRL_MUTE_ON == cmd)
    {
        do
        {
            falsewhile = (Bool) FALSE;

            if (IOM_OUTPUT == chanHandle->mode)
            {
                if ((Bool) TRUE == chanHandle->bMuteON)
                {
                    status = IOM_EBADARGS;
                    break;
                }
                chanHandle->bMuteON = (Bool) TRUE;
            }
            else
            {
                status = IOM_ENOTIMPL;
            }
        } while (falsewhile);
    }
    /*----------------------- MCASP MUTE OFF CMD -------------------------*/
    /* Take out from the the Muted state                                  */
    else if (IOCTL_MCASP_CTRL_MUTE_OFF == cmd)
    {
        do
        {
            falsewhile = (Bool) FALSE;

            if (IOM_OUTPUT == chanHandle->mode)
            {
                /* Check if mute is not ON                                */
                if ((Bool) FALSE == chanHandle->bMuteON)
                {
                    status = IOM_EBADARGS;
                    break;
                }
                chanHandle->bMuteON = (Bool) FALSE;
            } /* if only dma driven transaction */
            else
            {
                status = IOM_ENOTIMPL;
            }
        } while (falsewhile);
    }
#endif /* Mcasp_LOOPJOB_ENABLED */
       /*--------------------------- MCASP ABORT CMD-------------------------*/
    else if (IOCTL_MCASP_ABORT == cmd)
    {
        status = Mcasp_localAbortRequests(chanHandle, NULL);
    }
    else if (IOCTL_MCASP_SET_SAMPLE_RATE == cmd)
    {
        status = mcaspSetSamplingRate(chanHandle, arg);
    }
    else if (IOCTL_MCASP_GET_DEVINFO == cmd)
    {
        mcaspDeviceInfoGet(chanHandle, arg);
    }
#ifdef Mcasp_LOOPJOB_ENABLED
    /*------------------------MCASP START CMD ----------------------------*/
    else if (IOCTL_MCASP_START_PORT == cmd)
    {
        if (IOM_INPUT == chanHandle->mode)
        {
            if ((Bool) TRUE == instHandle->stopSmFsRcv)
            {
                instHandle->stopSmFsRcv = (Bool) FALSE;
            }
            else
            {
                /* Start port is issued without issuing stop              */
                status = IOM_EBADARGS;
            }
        }
        else
        {
            if ((Bool) TRUE == instHandle->stopSmFsXmt)
            {
                instHandle->stopSmFsXmt = (Bool) FALSE;
            }
            else
            {
                /* Start port is issued without issuing stop              */
                status = IOM_EBADARGS;
            }
        }
        tempQueueStatus =
            Queue_empty(Queue_handle(&(chanHandle->queueFloatingList)));
        if (((Bool) TRUE == chanHandle->isDmaDriven)
            && ((Bool) TRUE == tempQueueStatus))
        {
            for (linkCnt = 0; linkCnt < (Int16) Mcasp_MAXLINKCNT; linkCnt++)
            {
                if ((Bool) FALSE ==
                    Queue_empty(Queue_handle(&(chanHandle->queueReqList))))
                {
                    ioPacket = (IOM_Packet *) Queue_get(
                        Queue_handle(&(chanHandle->queueReqList)));

                    if (NULL == ioPacket)
                    {
                        status = IOM_EBADARGS;
                    }
                    if (IOM_COMPLETED == status)
                    {
                        tempCastPacket = (Void *) ioPacket;
                        /* floating queue not full . Process this request.    */
                        Queue_put(Queue_handle(&(chanHandle->queueFloatingList)),
                                  (Queue_Elem *) tempCastPacket);

                        chanHandle->currentDataSize =
                            (UInt16) ioPacket->size;
                        chanHandle->userDataBufferSize =
                            (UInt32) ioPacket->size;

                        /* For DMA mode we will not use chanHandle->dataPacket*
                         * to hold current packet - we use floatingqueue      */
                        chanHandle->dataPacket = NULL;

                        if (((Int16) Mcasp_MAXLINKCNT - (Int16) 1U) == linkCnt)
                        {
                            /* Though we have to post to param set directly   *
                             * from here,there will be differene between first*
                             * such packet and second packet. As we have      *
                             * control here we are second packet and first    *
                             * packet has not yet returned (or corresponding  *
                             * edma callback has not been called.For second   *
                             * packet, we will be updating the second param   *
                             * set, which is currently hosting loopjob        *
                             * parameter. Hence increment the index to point  *
                             * second paramset and since we are moving out    *
                             * loopjob from both param sets,the loopjobUpdated*
                             * inParamset is reset                            */
                            chanHandle->loopjobUpdatedinParamset = (Bool) FALSE;

                            Mcasp_localGetNextIndex(
                                &chanHandle->nextLinkParamSetToBeUpdated);
                        }
                        status = Mcasp_localUpdtDtPktToLnkPrms(
                            chanHandle,
                            ioPacket);
                        if (IOM_COMPLETED != status)
                        {
                            status = IOM_EBADIO;
                        }
                    }

                    if ((0 == linkCnt) && (IOM_COMPLETED == status))
                    {
                        /* if at all this is the very first packet, then  *
                         * one param set has loop job loaded,self linked  *
                         * and active with the main xfer channel param.   *
                         * other param set is ready loaded (just now and  *
                         * has link paramater set as the one having loop  *
                         * job (this is to ensure that if at all we are   *
                         * not getting any more packets loopjob be will   *
                         * take over). Now we have to link the floating   *
                         * newly loaded param set to xfer channel.        */
                        status = EDMA3_DRV_linkChannel(
                            chanHandle->edmaHandle,
                            chanHandle->xferChan,
                            chanHandle->pramTbl[ \
                                chanHandle->nextLinkParamSetToBeUpdated]);

                        if (IOM_COMPLETED != status)
                        {
                            status = IOM_EBADIO;
                        }
                    }
                }
                if (IOM_COMPLETED != status)
                {
                    break;
                }
            }

            EDMA3_DRV_enableTransfer(
                chanHandle->edmaHandle,
                chanHandle->xferChan,
                EDMA3_DRV_TRIG_MODE_EVENT);

            dlbMode =
                (Bool) ((UInt32) MCASP_LBCTL_DLBEN_ENABLE ==
                        (McASPDlbRegRead(instHandle->hwInfo.regs) &
                         (UInt32) MCASP_LBCTL_DLBEN_MASK));

            if (dlbMode)
            {
                /* start both RCV and XMT state m/cs                      */
                /* Activate the transmit and receive clocks               */
                mcaspActivateClkRcvXmt(&(instHandle->hwInfo));

                Mcasp_localActivateSmFsForBoth(instHandle);
            }
            else
            {
                if (IOM_INPUT == chanHandle->mode)
                {
                    /* start Receive state m/c */
                    /* before touching McASP registers, place receive     *
                     * section in reset                                   */
                    mcaspActivateRcvClkSer(&(instHandle->hwInfo));

                    Mcasp_localActivateSmFsForRcv(instHandle);
                }
                else
                {
                    /* start Transmit state m/c*/
                    /* before touching McASP registers, place transmit    *
                     * section in reset                                   */
                    mcaspActivateXmtClkSer(&(instHandle->hwInfo));

                    Mcasp_localActivateSmFsForXmt(instHandle);
                }
            }
        } /* DMA driven is TRUE if loop */
    }
    /*------------------------MCASP STOP CMD  ----------------------------*/
    else if (IOCTL_MCASP_STOP_PORT == cmd)
    {
        do
        {
            falsewhile = (Bool) FALSE;
            if (IOM_INPUT == chanHandle->mode)
            {
                if ((Bool) FALSE == instHandle->stopSmFsRcv)
                {
                    instHandle->stopSmFsRcv = (Bool) TRUE;
                }
                else
                {
                    /* Already stop port command is issued. This is a     *
                     * redundant command.                                 */
                    status = IOM_EBADARGS;
                }
            }
            else
            {
                if ((Bool) FALSE == instHandle->stopSmFsXmt)
                {
                    instHandle->stopSmFsXmt = (Bool) TRUE;
                }
                else
                {
                    /* Already stop port command is issued. This is a    *
                     * redundant command.                                */
                    status = IOM_EBADARGS;
                }
            }
        } while (falsewhile);
    }
    /*------------------------MCASP PAUSE CMD ----------------------------*/
    else if (IOCTL_MCASP_PAUSE == cmd)
    {
        if ((Bool) FALSE == chanHandle->paused)
        {
            chanHandle->paused = (Bool) TRUE;
        }
        else
        {
            status = IOM_EBADARGS;
        }
    }
    /*------------------------MCASP RESUME CMD ---------------------------*/
    else if (IOCTL_MCASP_RESUME == cmd)
    {
        do
        {
            falsewhile = (Bool) FALSE;

            if ((Bool) FALSE == chanHandle->paused)
            {
                /* Pause is not issued so can not perform resume          */
                status = IOM_EBADARGS;
                break;
            }
            tempQueueStatus =
                Queue_empty(Queue_handle(&(chanHandle->queueFloatingList)));
            if (((Bool) TRUE == chanHandle->isDmaDriven)
                && ((Bool) TRUE == tempQueueStatus))
            {
                for (linkCnt = 0; linkCnt < (Int16) Mcasp_MAXLINKCNT; linkCnt++)
                {
                    if ((Bool) FALSE ==
                        Queue_empty(Queue_handle(&(chanHandle->queueReqList))))
                    {
                        ioPacket = (IOM_Packet *) Queue_get(
                            Queue_handle(&(chanHandle->queueReqList)));

                        if (NULL != ioPacket)
                        {
                            tempCastPacket = (Void *) ioPacket;
                            /* floating queue not full.Process this request   */
                            Queue_put(
                                Queue_handle(&(chanHandle->queueFloatingList)),
                                (Queue_Elem *) tempCastPacket);

                            chanHandle->currentDataSize =
                                (UInt16) ioPacket->size;
                            chanHandle->userDataBufferSize = ioPacket->size;

                            /* For DMA mode we will not use
                             * chanHandle->dataPacket
                             * to hold current packet - we use floatingqueue  */
                            chanHandle->dataPacket = NULL;

                            if (((Int16) Mcasp_MAXLINKCNT - (Int16) 1) ==
                                linkCnt)
                            {
                                /* Though we have to post to param set direct *
                                 * from here,there will be differene between  *
                                 * first such packet and second packet. As we *
                                 * have control here we are second packet and *
                                 * first packet has not yet returned (or      *
                                 * corresponding edma callback has not been   *
                                 * called.For second packet, we will be       *
                                 * updating the second param set, which is    *
                                 * currently hosting loopjob parameter. Hence *
                                 * increment the index to point second param  *
                                 * set and since we are moving out loopjob    *
                                 * from both param sets, the loopjobUpdated in*
                                 * Paramset is reset                          */
                                chanHandle->loopjobUpdatedinParamset =
                                    (Bool) FALSE;

                                Mcasp_localGetNextIndex(
                                    &chanHandle->nextLinkParamSetToBeUpdated);
                            }

                            if (IOM_COMPLETED !=
                                Mcasp_localUpdtDtPktToLnkPrms(
                                    chanHandle,
                                    ioPacket))
                            {
                                status = IOM_EBADIO;
                            }

                            if ((0 == linkCnt) && (IOM_COMPLETED == status))
                            {
                                /* if at all this is the very first packet,   *
                                 * then one param set has loop job loaded,    *
                                 * self linked and active with the main xfer  *
                                 * channel param. other param set is ready    *
                                 * loaded (just now and has link paramater set*
                                 * as the one having loopjob (this is to      *
                                 * ensure that if at all we are not getting   *
                                 * any more packets loopjob be will taken over*
                                 * ). Now we have to link the floating/newly  *
                                 * loaded param set to xfer channel.          */
                                status = EDMA3_DRV_linkChannel(
                                    chanHandle->edmaHandle,
                                    chanHandle->xferChan,
                                    chanHandle->pramTbl[ \
                                        chanHandle->nextLinkParamSetToBeUpdated
                                    ]);

                                if (IOM_COMPLETED != status)
                                {
                                    status = IOM_EBADIO;
                                }
                            }
                        }
                        else
                        {
                            breakLoop = (Bool) TRUE;
                        }
                        if (((Bool) TRUE == breakLoop) ||
                            (IOM_COMPLETED != status))
                        {
                            break;
                        }
                    }
                }
            }

            chanHandle->paused = (Bool) FALSE;
        } while (falsewhile);
    }
    /*****************command to modify the Timeout count value****************/
    else if (IOCTL_MCASP_SET_TIMEOUT == cmd)
    {
        assert(NULL != arg);

        /* modify the retry count value to be used                            */
        instHandle->retryCount = *(UInt32 *) arg;
    }
#endif
    else if (IOCTL_MCASP_FLUSH_RCV_FIFO == cmd)
    {
        if ((IOM_INPUT == chanHandle->mode) &&
            ((Bool) TRUE == chanHandle->enableHwFifo))
        {
            UInt32 tempValue = 0x00;
            tempValue = McASPRxFifoStatusGet(instHandle->hwInfo.regs);
            while (((UInt32) 0U != (tempValue &
                                    (UInt32) 0x000000FFU)) &&
                   ((UInt32) 0U != timeout))
            {
                /* empty the FIFO now                                         */
                timeout--;
                tempVal   = *((UInt32 *) instHandle->hwInfo.dataAddr);
                tempValue = McASPRxFifoStatusGet(instHandle->hwInfo.regs);
            }
        }
        else
        {
            status = IOM_EBADMODE;
        }
    }
    else
    {
        /* command not executed hence not set status as not implemented   */
        status = IOM_ENOTIMPL;
    }
    return (status);
}

/**
 * \brief   This function sets the digital loopback mode
 *
 * \param   hMcasp   [IN]  pointer to the Mcasp Hardware information structure
 * \param   loopBack [IN]     Value to be loaded into the bit filed
 *
 * \return
 *          IOM_COMPLETED   - Successful completion
 *          IOM_EBADARGS    - Invalid parameters or Invalid handle
 *
 * \entry   hMcasp      should be non NULL and valid pointer
 *          loopBack    should be a valid value
 *
 * \leave   Not implemented
 */

static Void mcaspConfigLoopBack(Mcasp_HwHandle hMcasp, Bool loopBack)
{
    Bool   loopBackEnable = 0;
    Bool   orderBit       = 0;
    Int16  serNum         = 0;
    UInt32 serMode        = 0;
    UInt32 tempVal        = 0;
    UInt32 dlbMode        = 0;

    assert(NULL != hMcasp);
    assert(NULL != (hMcasp->regs));

    /* Reset the RSRCLR and XSRCLR registers in GBLCTL                    */
    tempVal  = McASPGlobalCtlGet(hMcasp->regs);
    tempVal &= ~(MCASP_GBLCTLR_RSRCLR_MASK | MCASP_GBLCTLR_XSRCLR_MASK |
                 MCASP_GBLCTLR_RSMRST_MASK | MCASP_GBLCTLR_XSMRST_MASK |
                 MCASP_GBLCTLR_RFRST_MASK | MCASP_GBLCTLR_XFRST_MASK);

    McASPGlobalCtlSet(hMcasp->regs, tempVal);

    dlbMode  = McASPDlbRegRead(hMcasp->regs);
    dlbMode &= MCASP_LBCTL_DLBEN_MASK;
    dlbMode |= ((UInt32) loopBack << MCASP_LBCTL_DLBEN_SHIFT);
    McASPDlbRegWrite(hMcasp->regs, dlbMode);
    /* configure loop back mode                                           */
    loopBackEnable =
        (Bool) ((dlbMode & MCASP_LBCTL_DLBEN_MASK) == MCASP_LBCTL_DLBEN_MASK);
    if ((Bool) TRUE == loopBackEnable)
    {
        dlbMode &= MCASP_LBCTL_MODE_MASK;
        dlbMode |= MCASP_LBCTL_MODE_XMTCLK << MCASP_LBCTL_MODE_SHIFT;
        McASPDlbRegWrite(hMcasp->regs, dlbMode);
    }

    orderBit = (Bool) (((dlbMode & (UInt32) MCASP_LBCTL_ORD_MASK)
                        >> MCASP_LBCTL_ORD_SHIFT) == MCASP_LBCTL_ORD_EVEN);

    if (orderBit == (Bool) TRUE)
    {
        while (serNum < hMcasp->numOfSerializers)
        {
            serMode = McASPSerializerGet(hMcasp->regs, (UInt32) serNum);
            serMode = (serMode & (UInt32) MCASP_XRSRCTL0_SRMOD_MASK) >>
                      MCASP_XRSRCTL0_SRMOD_SHIFT;

            if (MCASP_XRSRCTL0_SRMOD_INACTIVE != serMode)
            {
                McASPSerializerRxSet(hMcasp->regs, (UInt32) serNum);

                McASPPinDirInputSet(hMcasp->regs, ((UInt32) 1U << serNum));
            }
            serNum++;
        }
    }
    else
    {
        while (serNum < hMcasp->numOfSerializers)
        {
            serMode = McASPSerializerGet(hMcasp->regs,
                                         (UInt32) serNum);
            serMode = (serMode & MCASP_XRSRCTL0_SRMOD_MASK) >>
                      MCASP_XRSRCTL0_SRMOD_SHIFT;

            if (MCASP_XRSRCTL0_SRMOD_INACTIVE != serMode)
            {
                McASPSerializerTxSet(hMcasp->regs, (UInt32) serNum);

                McASPPinDirOutputSet(hMcasp->regs, ((UInt32) 1U << serNum));
            }
            serNum++;
        }
    }
}

#ifdef Mcasp_LOOPJOB_ENABLED
/**
 * \brief   This function activates the receive and transmit clock.
 *
 * \param   hMcasp  [IN]  Handle to the Mcasp Hw info object
 * \param   eb      [OUT] Pointer to the error block
 *
 * \return  IOM_COMPLETED in case of sucess else An error code
 *
 * \entry   hMcasp      should be non NULL and valid pointer
 *
 * \leave   Not implemented
 */
static Void mcaspActivateClkRcvXmt(Mcasp_HwHandle hMcasp)
{
    UInt32 bitValue = 0U;
    UInt32 tempVal  = 0;

    assert(NULL != hMcasp);
    assert(NULL != (hMcasp->regs));

    /* Sequence of start: starting hclk first                             */
    /* start AHCLKR */
    tempVal = McASPGlobalCtlGet(hMcasp->regs);

    tempVal &= ~MCASP_GBLCTL_RHCLKRST_MASK;
    tempVal |= (MCASP_GBLCTL_RHCLKRST_ACTIVE <<
                MCASP_GBLCTL_RHCLKRST_SHIFT);
    McASPGlobalCtlSet(hMcasp->regs, tempVal);

    bitValue = 0U;

    while (MCASP_GBLCTL_RHCLKRST_ACTIVE != bitValue)
    {
        bitValue = McASPGlobalCtlGet(hMcasp->regs);
        bitValue = ((bitValue & MCASP_GBLCTL_RHCLKRST_MASK)
                    >> MCASP_GBLCTL_RHCLKRST_SHIFT);
    }

    tempVal = 0U;
    tempVal = McASPRxClkPolarityGet(hMcasp->regs);

    /* start ACLKR only if internal clock is used                         */
    if ((UInt32) MCASP_ACLKRCTL_CLKRM_INTERNAL ==
        ((tempVal & (UInt32) MCASP_ACLKRCTL_CLKRM_MASK)
         >> MCASP_ACLKRCTL_CLKRM_SHIFT))
    {
        bitValue = McASPGlobalCtlGet(hMcasp->regs);
        bitValue = (bitValue & ~(MCASP_GBLCTL_RCLKRST_MASK))
                   | (MCASP_GBLCTL_RCLKRST_ACTIVE
                      << MCASP_GBLCTL_RCLKRST_SHIFT);
        McASPGlobalCtlSet(hMcasp->regs, bitValue);

        bitValue = 0U;

        while (MCASP_GBLCTL_RCLKRST_ACTIVE != bitValue)
        {
            bitValue = McASPGlobalCtlGet(hMcasp->regs);
            bitValue = ((bitValue & MCASP_GBLCTL_RCLKRST_MASK)
                        >> MCASP_GBLCTL_RCLKRST_SHIFT);
        }
    }

    /* Sequence of start: starting hclk first                             */
    tempVal  = McASPTxGlobalCtlGet(hMcasp->regs);
    tempVal &= ~MCASP_GBLCTLX_XHCLKRST_MASK;
    tempVal |= (MCASP_GBLCTLX_XHCLKRST_ACTIVE <<
                MCASP_GBLCTLX_XHCLKRST_SHIFT);
    McASPTxGlobalCtlSet(hMcasp->regs, tempVal);

    bitValue = 0U;

    while (MCASP_GBLCTL_XHCLKRST_ACTIVE != bitValue)
    {
        bitValue = McASPGlobalCtlGet(hMcasp->regs);
        bitValue = (bitValue & MCASP_GBLCTL_XHCLKRST_MASK)
                   >> MCASP_GBLCTL_XHCLKRST_SHIFT;
    }
    tempVal = 0U;
    tempVal = McASPTxClkPolarityGet(hMcasp->regs);
    /* start ACLKX only if internal clock is used                         */
    if ((UInt32) MCASP_ACLKXCTL_CLKXM_INTERNAL ==
        ((tempVal & (UInt32) MCASP_ACLKXCTL_CLKXM_MASK)
         >> MCASP_ACLKXCTL_CLKXM_SHIFT))
    {
        tempVal = McASPTxGlobalCtlGet(hMcasp->regs);
        tempVal = (tempVal & ~(MCASP_GBLCTLX_XCLKRST_MASK))
                  | (MCASP_GBLCTLX_XCLKRST_ACTIVE
                     << MCASP_GBLCTLX_XCLKRST_SHIFT);
        McASPTxGlobalCtlSet(hMcasp->regs, tempVal);

        bitValue = 0U;

        while (MCASP_GBLCTL_XCLKRST_ACTIVE != bitValue)
        {
            bitValue = McASPGlobalCtlGet(hMcasp->regs);
            bitValue = (bitValue & MCASP_GBLCTL_XCLKRST_MASK)
                       >> MCASP_GBLCTL_XCLKRST_SHIFT;
        }
    }
}

/**
 * \brief   This function sets the bits related to receive in RGBLCTL.
 *
 * \param   hMcasp  [IN] Pointer to the Mcasp Hardware info structure
 *
 * \return
 *          IOM_COMPLETED   - Successful completion
 *          IOM_EBADARGS    - Invalid parameters or Invalid handle
 *
 * \entry   hMcasp      should be non NULL and valid pointer
 *
 * \leave   Not implemented
 */

static Void mcaspActivateRcvClkSer(Mcasp_HwHandle hMcasp)
{
    UInt32 bitValue = 0U;
    UInt32 tempVal  = 0;

    assert(NULL != hMcasp);
    assert(NULL != (hMcasp->regs));

    /* Sequence of start: starting hclk first                             */
    /* start AHCLKR */
    tempVal = McASPGlobalCtlGet(hMcasp->regs);
    tempVal = ((tempVal & ~MCASP_GBLCTL_RHCLKRST_MASK) |
               (MCASP_GBLCTL_RHCLKRST_ACTIVE <<
                MCASP_GBLCTL_RHCLKRST_SHIFT));
    McASPGlobalCtlSet(hMcasp->regs, tempVal);

    bitValue = 0U;

    while (MCASP_GBLCTL_RHCLKRST_ACTIVE != bitValue)
    {
        bitValue = McASPGlobalCtlGet(hMcasp->regs);
        bitValue = (bitValue & MCASP_GBLCTL_RHCLKRST_MASK)
                   >> MCASP_GBLCTL_RHCLKRST_SHIFT;
    }
#if 0
    /* start ACLKR only if internal clock is used                         */
    if (CSL_MCASP_ACLKRCTL_CLKRM_INTERNAL ==
        (((hMcasp->regs)->ACLKRCTL & CSL_MCASP_ACLKRCTL_CLKRM_MASK)
         >> CSL_MCASP_ACLKRCTL_CLKRM_SHIFT))
    {
        (hMcasp->regs)->GBLCTL =
            ((hMcasp->regs)->GBLCTL & ~(CSL_MCASP_GBLCTL_RCLKRST_MASK))
            | (CSL_MCASP_GBLCTL_RCLKRST_ACTIVE
               << CSL_MCASP_GBLCTL_RCLKRST_SHIFT);

        bitValue = 0U;

        while (CSL_MCASP_GBLCTL_RCLKRST_ACTIVE != bitValue)
        {
            bitValue = (((hMcasp->regs)->GBLCTL
                         & CSL_MCASP_GBLCTL_RCLKRST_MASK)
                        >> CSL_MCASP_GBLCTL_RCLKRST_SHIFT);
        }
    }
#else
    tempVal = 0U;
    tempVal = McASPRxClkPolarityGet(hMcasp->regs);

    /* start ACLKR only if internal clock is used                         */
    if ((UInt32) MCASP_ACLKRCTL_CLKRM_INTERNAL ==
        ((tempVal & (UInt32) MCASP_ACLKRCTL_CLKRM_MASK)
         >> MCASP_ACLKRCTL_CLKRM_SHIFT))
    {
        bitValue = McASPGlobalCtlGet(hMcasp->regs);
        bitValue = (bitValue & ~(MCASP_GBLCTL_RCLKRST_MASK))
                   | (MCASP_GBLCTL_RCLKRST_ACTIVE
                      << MCASP_GBLCTL_RCLKRST_SHIFT);
        McASPGlobalCtlSet(hMcasp->regs, bitValue);

        bitValue = 0U;

        while (MCASP_GBLCTL_RCLKRST_ACTIVE != bitValue)
        {
            bitValue = McASPGlobalCtlGet(hMcasp->regs);
            bitValue = ((bitValue & MCASP_GBLCTL_RCLKRST_MASK)
                        >> MCASP_GBLCTL_RCLKRST_SHIFT);
        }
    }
#endif

#if 0
    (hMcasp->regs)->RGBLCTL =
        ((hMcasp->regs)->RGBLCTL & ~(CSL_MCASP_RGBLCTL_RSRCLR_MASK))
        | (CSL_MCASP_RGBLCTL_RSRCLR_ACTIVE
           << CSL_MCASP_RGBLCTL_RSRCLR_SHIFT);

    bitValue = 0U;

    while (CSL_MCASP_GBLCTL_RSRCLR_ACTIVE != bitValue)
    {
        bitValue = (((hMcasp->regs)->GBLCTL & CSL_MCASP_GBLCTL_RSRCLR_MASK)
                    >> CSL_MCASP_GBLCTL_RSRCLR_SHIFT);
    }
#else
    tempVal = McASPRxGlobalCtlGet(hMcasp->regs);
    tempVal = (tempVal & ~(MCASP_GBLCTL_RSRCLR_MASK))
              | (MCASP_GBLCTL_RSRCLR_ACTIVE
                 << MCASP_GBLCTL_RSRCLR_SHIFT);
    McASPRxGlobalCtlSet(hMcasp->regs, tempVal);

    bitValue = 0U;

    while (MCASP_GBLCTL_RSRCLR_ACTIVE != bitValue)
    {
        bitValue = McASPGlobalCtlGet(hMcasp->regs);
        bitValue = (bitValue & MCASP_GBLCTL_RSRCLR_MASK)
                   >> MCASP_GBLCTL_RSRCLR_SHIFT;
    }
#endif
}

/**
 * \brief   This function sets the bits related to transmit in RGBLCTL.
 *
 * \param   hMcasp  [IN] Pointer to the Mcasp Hardware info structure
 *
 * \return
 *          IOM_COMPLETED   - Successful completion
 *          IOM_EBADARGS    - Invalid parameters or Invalid handle
 *
 * \entry   hMcasp      should be non NULL and valid pointer
 *
 * \leave   Not implemented
 */
static Void mcaspActivateXmtClkSer(Mcasp_HwHandle hMcasp)
{
    UInt32 bitValue = 0U;
    UInt32 tempVal  = 0;

    assert(NULL != hMcasp);
    assert(NULL != (hMcasp->regs));

    /* Sequence of start: starting hclk first*/

    tempVal  = McASPTxGlobalCtlGet(hMcasp->regs);
    tempVal &= ~MCASP_GBLCTLX_XHCLKRST_MASK;
    tempVal |= (MCASP_GBLCTLX_XHCLKRST_ACTIVE <<
                MCASP_GBLCTLX_XHCLKRST_SHIFT);
    McASPTxGlobalCtlSet(hMcasp->regs, tempVal);

    bitValue = 0U;

    while (MCASP_GBLCTL_XHCLKRST_ACTIVE != bitValue)
    {
        bitValue = McASPGlobalCtlGet(hMcasp->regs);
        bitValue = (bitValue & MCASP_GBLCTL_XHCLKRST_MASK)
                   >> MCASP_GBLCTL_XHCLKRST_SHIFT;
    }
    tempVal = 0U;
    tempVal = McASPTxClkPolarityGet(hMcasp->regs);

    /* start ACLKX only if internal clock is used*/
    if ((UInt32) MCASP_ACLKXCTL_CLKXM_INTERNAL ==
        ((tempVal & (UInt32) MCASP_ACLKXCTL_CLKXM_MASK)
         >> MCASP_ACLKXCTL_CLKXM_SHIFT))
    {
        tempVal = McASPTxGlobalCtlGet(hMcasp->regs);
        tempVal = (tempVal & ~(MCASP_GBLCTLX_XCLKRST_MASK))
                  | (MCASP_GBLCTLX_XCLKRST_ACTIVE
                     << MCASP_GBLCTLX_XCLKRST_SHIFT);
        McASPTxGlobalCtlSet(hMcasp->regs, tempVal);

        bitValue = 0U;

        while (MCASP_GBLCTL_XCLKRST_ACTIVE != bitValue)
        {
            bitValue = McASPGlobalCtlGet(hMcasp->regs);
            bitValue = (bitValue & MCASP_GBLCTL_XCLKRST_MASK)
                       >> MCASP_GBLCTL_XCLKRST_SHIFT;
        }
    }
    tempVal = 0U;

    tempVal  = McASPTxGlobalCtlGet(hMcasp->regs);
    tempVal &= ~MCASP_GBLCTLX_XSRCLR_MASK;
    tempVal |= (MCASP_GBLCTLX_XSRCLR_ACTIVE <<
                MCASP_GBLCTLX_XSRCLR_SHIFT);

    bitValue = 0U;

    while (MCASP_GBLCTL_XSRCLR_ACTIVE != bitValue)
    {
        bitValue = McASPGlobalCtlGet(hMcasp->regs);
        bitValue = (bitValue & MCASP_GBLCTL_XSRCLR_MASK)
                   >> MCASP_GBLCTL_XSRCLR_SHIFT;
    }
}

#endif

/**
 *  \brief  This function is used to get the value of various parameters of the
 *          McASP instance. The value returned depends on the query passed.
 *
 *  \param  hMcasp    [IN]    Handle to mcasp H/W information structure
 *  \param  myQuery   [IN]    Query requested by application
 *  \param  response  [IN]    Pointer to buffer to return the data requested by
 *                            the query passed
 *  \param  eb        [IN]    pointer to error block
 *
 *  \return
 *          IOM_COMPLETED  - Successful completion of the query
 *          IOM error code - in case of error.
 *
 * \entry   hMcasp      should be non NULL and valid pointer
 *          myQuery     should be a valid value
 *          response    shluld be non NULL and valid pointer
 *
 * \leave   Not implemented
 */
static Int32 mcaspGetHwStatus(Mcasp_HwHandle      hMcasp,
                              Mcasp_HwStatusQuery myQuery,
                              Void               *response)
{
    Int32  status = IOM_COMPLETED;
    Mcasp_SerQuery     *serQuery     = NULL;
    Mcasp_SerModeQuery *serModeQuery = NULL;
    UInt32 tempVal = 0U;

    assert(NULL != hMcasp);
    assert(NULL != response);

    switch (myQuery)
    {
        /* Return current transmit slot being transmitted                 */
        case Mcasp_HwStatusQuery_CURRENT_XSLOT:
            *((UInt16 *) response) =
                McASPCurrTransmitSlot(hMcasp->regs);
            break;

        /* Return current receive slot being received                     */
        case Mcasp_HwStatusQuery_CURRENT_RSLOT:
            *((UInt16 *) response) =
                McASPCurrReceiveSlot(hMcasp->regs);
            break;

        /* Return transmit error status bit                               */
        case Mcasp_HwStatusQuery_XSTAT_XERR:
            *(Bool *) response =
                (Bool) McASPTxErrStatus(hMcasp->regs, MCASP_TX_STAT_ERR);
            break;

        /* Return transmit clock failure flag status                      */
        case Mcasp_HwStatusQuery_XSTAT_XCLKFAIL:
            *(Bool *) response =
                (Bool) McASPTxErrStatus(hMcasp->regs, MCASP_TX_STAT_CLKFAIL);
            break;

        /* Return unexpected transmit frame sync flag status              */
        case Mcasp_HwStatusQuery_XSTAT_XSYNCERR:
            *(Bool *) response =
                (Bool) McASPTxErrStatus(hMcasp->regs, MCASP_TX_STAT_SYNCERR);
            break;

        /* Return transmit underrun flag status                           */
        case Mcasp_HwStatusQuery_XSTAT_XUNDRN:
            *((Bool *) response) =
                (Bool) McASPTxErrStatus(hMcasp->regs, MCASP_TX_STAT_UNDERRUN);
            break;

        /* Return transmit data ready flag status                         */
        case Mcasp_HwStatusQuery_XSTAT_XDATA:
            (*(Bool *) response) =
                (Bool) McASPTxErrStatus(hMcasp->regs, MCASP_TX_STAT_DATAREADY);
            break;

        /* Return receive error status bit                                */
        case Mcasp_HwStatusQuery_RSTAT_RERR:
            *((Bool *) response) =
                (Bool) McASPRxErrStatus(hMcasp->regs, MCASP_RX_STAT_ERR);
            break;

        /* Return receive clk failure flag status                         */
        case Mcasp_HwStatusQuery_RSTAT_RCLKFAIL:
            *((Bool *) response) =
                (Bool) McASPRxErrStatus(hMcasp->regs,
                                        (UInt32) MCASP_RXSTAT_RCKFAIL_MASK);
            break;

        /* Return unexpected receive frame sync flag status               */
        case Mcasp_HwStatusQuery_RSTAT_RSYNCERR:
            *((Bool *) response) =
                (Bool) McASPRxErrStatus(hMcasp->regs,
                                        (UInt32) MCASP_RXSTAT_RSYNCERR_MASK);
            break;

        /* Return receive overrun flag status                             */
        case Mcasp_HwStatusQuery_RSTAT_ROVRN:
            *((Bool *) response) =
                (Bool) McASPRxErrStatus(hMcasp->regs,
                                        (UInt32) MCASP_RXSTAT_ROVRN_MASK);
            break;
        /* Return receive data ready flag status                          */
        case Mcasp_HwStatusQuery_RSTAT_RDATA:
            *((Bool *) response) =
                (Bool) McASPRxErrStatus(hMcasp->regs,
                                        (UInt32) MCASP_RXSTAT_RDATA_MASK);
            break;

        /* Return status whether rrdy is set or not                       */
        case Mcasp_HwStatusQuery_SRCTL_RRDY:
        {
            serQuery = (Mcasp_SerQuery *) response;
            mcaspGetSerRcvReady(
                (Mcasp_HwHandle) hMcasp,
                (Bool *) &(serQuery->serStatus),
                serQuery->serNum);
        }
        break;

        /* Return status whether xrdy is set or not                       */
        case Mcasp_HwStatusQuery_SRCTL_XRDY:
        {
            serQuery = (Mcasp_SerQuery *) response;
            mcaspGetSerXmtReady(
                hMcasp,
                (Bool *) &(serQuery->serStatus),
                serQuery->serNum);
        }
        break;
        /* Return status whether serializer is configured as TX/RX/FREE    */
        case Mcasp_HwStatusQuery_SRCTL_SRMOD:
        {
            serModeQuery = (Mcasp_SerModeQuery *) response;
            mcaspGetSerMode(hMcasp,
                            &(serModeQuery->serMode),
                            serModeQuery->serNum);
            break;
        }

        /* Return the value of XSTAT register                             */
        case Mcasp_HwStatusQuery_XSTAT:
            *((UInt16 *) response) = (UInt16)
                                     McASPTxStatusGet(hMcasp->regs);
            break;

        /* Return the value of RSTAT register                             */
        case Mcasp_HwStatusQuery_RSTAT:
            *((UInt16 *) response) = (UInt16)
                                     McASPRxStatusGet(hMcasp->regs);
            break;

        /* Return the XSMRST and XFRST field values GBLCTL register       */
        case Mcasp_HwStatusQuery_SM_FS_XMT:
            *((UInt8 *) response) = McASPGetSmFsXmt(hMcasp->regs);
            break;

        /* Return the RSMRST and RFRST field values GBLCTL register       */
        case Mcasp_HwStatusQuery_SM_FS_RCV:
            *((UInt8 *) response) = McASPGetSmFsRcv(hMcasp->regs);
            break;

        /* Return status of DITEN bit in DITCTL register                  */
        case Mcasp_HwStatusQuery_DIT_MODE:
            tempVal = McASPDITModeCtlRead(hMcasp->regs);
            tempVal = (tempVal & MCASP_TXDITCTL_DITEN_MASK) >>
                      MCASP_TXDITCTL_DITEN_SHIFT;
            *((Bool *) response) = (Bool) tempVal;

            break;

        default:
            status = IOM_EBADARGS;
            break;
    }

    return status;
}

/**
 * \brief   This function checks whether transmit buffer ready bit of serializer
 *          control register is set or not
 *
 * \param   hMcasp      [IN] pointer to the Mcasp Hardware information structure
 * \param   serXmtReady [IN] Status of the serializer will be stored here
 * \param   serNum      [IN] serializer number to be checked
 *
 * \return
 *          IOM_COMPLETED   - Successful completion
 *          IOM_EBADARGS    - Invalid parameters or Invalid handle
 *
 * \entry   hMcasp      should be non NULL and valid pointer
 *          serCmtReady should be non NULL and valid pointer
 *          serNum      should be a valid value
 *
 * \leave   Not implemented
 */

static Void mcaspGetSerXmtReady(Mcasp_HwHandle      hMcasp,
                                Bool               *serXmtReady,
                                Mcasp_SerializerNum serNum)
{
    assert(NULL != serXmtReady);
    assert(NULL != hMcasp);

    assert(serNum < hMcasp->numOfSerializers);

    *(Bool *) serXmtReady =
        (Bool) McASPIsSerializerXmtReady(hMcasp->regs, serNum);
}

/**
 * \brief   This function checks whether receive buffer ready bit of serializer
 *          control register is set or not
 *
 * \param   hMcasp      [IN] pointer to the Mcasp Hardware information structure
 * \param   serRcvReady [IN] Serailizer status will be stored here
 * \param   serNum      [IN] Serailizer register to be checked
 *
 * \return
 *          IOM_COMPLETED   - Successful completion of read
 *          IOM_EBADARGS    - Invalid parameters or Invalid handle
 *
 * \entry   hMcasp      should be non NULL and valid pointer
 *          serRcvReady should be non NULL and valid pointer
 *          serNum      should be a valid value
 *
 * \leave   Not implemented
 *
 */

static Void mcaspGetSerRcvReady(Mcasp_HwHandle      hMcasp,
                                Bool               *serRcvReady,
                                Mcasp_SerializerNum serNum)
{
    assert(NULL != serRcvReady);
    assert(NULL != hMcasp);
    assert(serNum < hMcasp->numOfSerializers);

    (*(Bool *) serRcvReady) =
        (Bool) McASPIsSerializerRcvReady(hMcasp->regs, serNum);
}

/**
 * \brief   This function gets the current mode for the serializer requested
 *
 * \param   hMcasp    [IN]  pointer to the Mcasp Hardware information structure
 * \param   serMode   [IN]  Serializer mode will be stored here
 * \param   serNum    [IN]  Serailizer number to be checked
 *
 * \return
 *          IOM_COMPLETED   - Successful completion
 *          IOM_EBADARGS    - Invalid parameters or Invalid handle
 *
 * \entry   hMcasp      should be non NULL and valid pointer
 *          serMode     should be non NULL and valid pointer
 *          serNum      should be a valid value
 *
 * \leave   Not implemented
 */
static Void mcaspGetSerMode(Mcasp_HwHandle      hMcasp,
                            Mcasp_SerMode      *serMode,
                            Mcasp_SerializerNum serNum)
{
    UInt32 serializerVal = 0x0;

    assert(NULL != serMode);
    assert(NULL != hMcasp);
    assert(serNum < hMcasp->numOfSerializers);

    serializerVal = McASPSerializerGet(hMcasp->regs, serNum);
    *serMode      = (Mcasp_SerMode) ((serializerVal & MCASP_XRSRCTL0_SRMOD_MASK)
                                     >> MCASP_XRSRCTL0_SRMOD_SHIFT);
}

/**
 *  \brief    mcaspReadRcvConfig
 *
 *   Reads the configuration data of the receive section and updates the info
 *   to the pointer provided by the application.
 *
 *  \param    hMcasp         [IN]    Handle to mcasp hw information structure
 *  \param    rcvData        [OUT]   pointer to copy the data to
 *  \param    eb             [OUT]   pointer to error block
 *
 *  \return   Nothing
 *
 * \entry   hMcasp      should be non NULL and valid pointer
 *          rcvData     should be non NULL and valid pointer
 *
 * \leave   Not implemented
 */
static Void mcaspReadRcvConfig(Mcasp_HwHandle             hMcasp,
                               Mcasp_HwSetupData   *const rcvData)
{
    assert(NULL != hMcasp);
    assert(NULL != rcvData);

    /* Read RMASK register             */
    rcvData->mask = (UInt32) McASPRxFmtMaskGet(hMcasp->regs);

    /* Read RFMT register              */
    rcvData->fmt = (UInt32) McASPRxFmtGet(hMcasp->regs);

    /* Read AFSRCTL register           */
    rcvData->frSyncCtl = (UInt32) McASPTxRxFrameSyncRead(hMcasp->regs,
                                                         (UInt8) RX);

    /* Read ACLKRCTL register          */
    rcvData->clk.clkSetupClk = (UInt32)
                               McASPRxClkPolarityGet(hMcasp->regs);

    /* Read AHCLKRCTL register         */
    rcvData->clk.clkSetupHiClk = (UInt32)
                                 McASPRxHClkPolarityGet(hMcasp->regs);

    /* Read RTDM register              */
    rcvData->tdm = (UInt32)
                   McASPTxRxTimeSlotGet(hMcasp->regs, (UInt8) RX);

    /* Read RINTCTL register           */
    rcvData->intCtl = (UInt32) McASPRxIntrStatusGet(hMcasp->regs);

    /* Read RCLKCHK register           */
    rcvData->clk.clkChk = (UInt32)
                          McASPRxClkCheckRegRead(hMcasp->regs);

    /* Read RSTAT register             */
    rcvData->stat = (UInt32)
                    McASPRxStatusGet(hMcasp->regs);

    /* Read REVTCTL register           */
    rcvData->evtCtl = (UInt32)
                      McASPTxRxDMAEvtCntrlRead(hMcasp->regs, (UInt8) RX);
}

/**
 *  \brief    mcaspReadXmtConfig
 *
 *   Reads the configuration data of the transmit section and updates
 *   the info to the pointer provided by the application.
 *
 *  \param    hMcasp        [IN]    Handle to mcasp hw information structure
 *  \param    rcvData       [OUT]   pointer to copy the data to
 *  \param    eb            [OUT]   pointer to error block
 *
 *  \return   Nothing
 *
 * \entry   hMcasp      should be non NULL and valid pointer
 *          xmtData     should be non NULL and valid pointer
 *
 * \leave   Not implemented
 */
static Void mcaspReadXmtConfig(Mcasp_HwHandle             hMcasp,
                               Mcasp_HwSetupData   *const xmtData)
{
    assert(NULL != hMcasp);
    assert(NULL != xmtData);

    /* Read XMASK register              */
    xmtData->mask = (UInt32) McASPTxFmtMaskGet(hMcasp->regs);

    /* Read XFMT register               */
    xmtData->fmt = (UInt32) McASPTxFmtGet(hMcasp->regs);

    /* Read AFSXCTL register            */
    xmtData->frSyncCtl = (UInt32) McASPTxRxFrameSyncRead(hMcasp->regs,
                                                         (UInt8) TX);

    xmtData->clk.clkSetupClk = (UInt32)
                               McASPTxClkPolarityGet(hMcasp->regs);

    /* Read AHCLKXCTL register          */
    xmtData->clk.clkSetupHiClk = (UInt32)
                                 McASPTxHClkPolarityGet(hMcasp->regs);

    /* Read XTDM register               */
    xmtData->tdm = (UInt32)
                   McASPTxRxTimeSlotGet(hMcasp->regs, (UInt8) TX);

    /* Read XINTCTL register            */
    xmtData->intCtl = (UInt32) McASPTxIntrStatusGet(hMcasp->regs);

    /* Read XCLKCHK register            */
    xmtData->clk.clkChk = (UInt32)
                          McASPTxClkCheckRegRead(hMcasp->regs);

    /* Read XSTAT register              */
    xmtData->stat = (UInt32)
                    McASPTxStatusGet(hMcasp->regs);

    /* Read XEVTCTL register            */
    xmtData->evtCtl = (UInt32)
                      McASPTxRxDMAEvtCntrlRead(hMcasp->regs, (UInt8) TX);
}

/*
 *  \brief  Abort the operation of the requested Mcasp Channel. This function
 *          Aborts all current and pending Read and write requests
 *
 *  \param  handle   [IN]   Handle to the McASP channel
 *  \param  arg      [IN]   Unused argument(for future use)
 *  \param  eb       [OUT]  pointer to the error block
 *
 *  \return IOM_COMPLETED or Error code
 *
 * \entry   handle      should be non NULL and valid pointer
 *          arg         should be a valis value
 *
 * \leave   Not implemented
 */
Int32 Mcasp_localAbortRequests(Ptr handle, Ptr arg)
{
    Mcasp_ChannelHandle chanHandle = NULL;
    Mcasp_Object       *instHandle = NULL;
    Int32 status = IOM_COMPLETED;

    assert(NULL != handle);

    chanHandle = (Mcasp_ChannelHandle) handle;

    assert(NULL != chanHandle->devHandle);

    instHandle = (Mcasp_Object *) chanHandle->devHandle;

    assert(NULL != instHandle);

    /* To remove compiler warning                                             */
    arg = arg;

    if (Mcasp_DriverState_OPENED == chanHandle->chanState)
    {
        /* Abort the requested channels                                       */
        if (IOM_INPUT == chanHandle->mode)
        {
            status = Mcasp_localAbortReset(
                (Mcasp_ChannelHandle) & instHandle->RcvObj);
        }
        else
        {
            status = Mcasp_localAbortReset(
                (Mcasp_ChannelHandle) & instHandle->XmtObj);
        }
    }

    return (status);
}

#if 0
/**
 * \brief   This function returns the RSMRST and RFRST field values of RGBLCTL
 *          register.
 *
 * \param   hMcasp [IN] Handle to the McASP hardware info structure
 *
 * \return
 *          0x00        - Both receive frame generator sync and receive state
 *                        machine are reset.
 *          0x1         - Only receive state machine is active.
 *          0x10        - Only receive frame sync generator is active.
 *          0x11        - Both receive frame generator sync and receive state
 *                        machine are active.
 *
 * \entry   hMcasp      should be non NULL and valid pointer
 *
 * \leave   Not implemented
 */
static UInt8 mcaspGetSmFsRcv(Mcasp_HwHandle hMcasp)
{
    UInt8  smFsRcv = 0;
    UInt32 tempVal = 0U;

    assert(NULL != hMcasp);

    tempVal = McASPRxGlobalCtlGet(CRED_index_t component);

    smFsRcv = (UInt8) ((tempVal & MCASP_GBLCTLR_RFRST_MASK)
                       >> MCASP_GBLCTLR_RFRST_MASK_SHIFT);

    smFsRcv = (UInt8) (smFsRcv << 4);

    smFsRcv |= (UInt8) (((hMcasp->regs)->RGBLCTL
                         & CSL_MCASP_RGBLCTL_RSMRST_MASK)
                        >> CSL_MCASP_RGBLCTL_RSMRST_SHIFT);

    return (smFsRcv);
}

/**
 * \brief   This function returns the XSMRST and XFRST field values of XGBLCTL
 *          register.
 *
 * \param   hMcasp [IN] Handle to the McASP hardware info structure
 *
 * \return
 *          0x00        - Both transmit frame generator sync and transmit state
 *                        machine are reset.
 *          0x1         - Only transmit state machine is active.
 *          0x10        - Only transmit frame sync generator is active.
 *          0x11        - Both transmit frame generator sync and transmit state
 *                        machine are active.
 * \entry   hMcasp      should be non NULL and valid pointer
 *
 * \leave   Not implemented
 */
static UInt8 mcaspGetSmFsXmt(Mcasp_HwHandle hMcasp)
{
    UInt8 smFsXmt = 0;

    assert(NULL != hMcasp);

    smFsXmt = (UInt8) (((hMcasp->regs)->XGBLCTL
                        & CSL_MCASP_XGBLCTL_XFRST_MASK)
                       >> CSL_MCASP_XGBLCTL_XFRST_SHIFT);

    smFsXmt = (UInt8) (smFsXmt << 4);

    smFsXmt |= (UInt8) (((hMcasp->regs)->XGBLCTL
                         & CSL_MCASP_XGBLCTL_XSMRST_MASK)
                        >> CSL_MCASP_XGBLCTL_XSMRST_SHIFT);

    return (smFsXmt);
}

#endif

/**
 *
 * \brief   This function configures the sample rate for the Mcasp.
 *
 * \param   chanHandle  [IN]  handle to the channel
 * \param   sampleRate  [IN]  sample rate to be configured.
 * \param   eb          [OUT] pointer to the application supplied error block
 *
 * \return  IOM_COMPLETED if success or else IOM_EBADARGS
 *
 * \entry   chanHandle  is a valid non NULL pointer
 *          sampleRate  is a valid supported sample rate
 *          eb          can be any value,in case the value is non null then the
 *                      application will receive updated error information block
 *                      in case of an error, if eb is NULL the program will
 *                      terminate the execution at the place where Error has
 *                      occured and an appropriate error message is logged.
 *
 * \leave   Not implemented
 */
static Int32 mcaspSetSamplingRate(Mcasp_ChannelHandle chanHandle,
                                  Ptr                 ioctlArg)
{
    Mcasp_Object  *instHandle = NULL;
    Mcasp_HwSetup *hwSetUp    = NULL;
    Int32          status     = IOM_COMPLETED;

    assert(NULL != chanHandle);
    assert(NULL != ioctlArg);

    instHandle = (Mcasp_Object *) chanHandle->devHandle;

    assert(NULL != instHandle);

    hwSetUp = (Mcasp_HwSetup *) ioctlArg;

    /* These values will not be changed hence we will take a copy of these    *
     * and reset the same values in the configuring of the TX ans RX sections */

    hwSetUp->tx.mask      = McASPTxFmtMaskGet(instHandle->hwInfo.regs);
    hwSetUp->tx.fmt       = McASPTxFmtGet(instHandle->hwInfo.regs);
    hwSetUp->tx.frSyncCtl = (UInt32) McASPTxRxFrameSyncRead(
        instHandle->hwInfo.regs,
        (UInt8) TX);

    hwSetUp->tx.tdm = McASPTxRxTimeSlotGet(instHandle->hwInfo.regs,
                                           (UInt8) TX);
    hwSetUp->tx.intCtl = McASPTxIntrStatusGet(instHandle->hwInfo.regs);
    hwSetUp->tx.evtCtl =
        McASPTxRxDMAEvtCntrlRead(instHandle->hwInfo.regs, (UInt8) TX);

    status = Mcasp_localConfigXmtSection(instHandle, &hwSetUp->tx);

    if (IOM_COMPLETED == status)
    {
        hwSetUp->rx.mask = McASPRxFmtMaskGet(instHandle->hwInfo.regs);
        hwSetUp->rx.fmt  = McASPRxFmtGet(instHandle->hwInfo.regs);

        hwSetUp->tx.frSyncCtl = (UInt32) McASPTxRxFrameSyncRead(
            instHandle->hwInfo.regs, (UInt8) RX);

        hwSetUp->rx.tdm =
            McASPTxRxTimeSlotGet(instHandle->hwInfo.regs, (UInt8) RX);
        hwSetUp->rx.intCtl = McASPRxIntrStatusGet(instHandle->hwInfo.regs);
        hwSetUp->rx.evtCtl = McASPTxRxDMAEvtCntrlRead(instHandle->hwInfo.regs,
                                                      (UInt8) RX);

        status = Mcasp_localConfigRcvSection(instHandle, &hwSetUp->rx);
    }
    return status;
}

/**
 *
 * \brief   This function gets the device related information of the mcasp.
 *
 * \param   chanHandle  [IN]  handle to the channel
 * \param   arg         [IN]  pointer to the Mcasp_AudioDevData structure
 *                            supplied by the application.
 *
 * \return  None
 *
 * \entry   chanHandle  is a valid non NULL pointer
 *          arg         is a valid non NULL pointer
 *
 * \leave   Not implemented
 */
static Void mcaspDeviceInfoGet(Mcasp_ChannelHandle chanHandle,
                               Ptr                 arg)
{
    Mcasp_Object       *instHandle = NULL;
    Mcasp_AudioDevData *devData    = NULL;
    Bool   isMaster = FALSE;
    UInt32 tempVal1 = 0x0;
    UInt32 tempVal2 = 0x0;

    assert(chanHandle != NULL);
    assert(NULL != arg);

    devData = (Mcasp_AudioDevData *) arg;

    instHandle = (Mcasp_Object *) chanHandle->devHandle;

    assert(NULL != instHandle);

    tempVal1 = McASPTxClkPolarityGet(instHandle->hwInfo.regs);
    tempVal2 = McASPRxClkPolarityGet(instHandle->hwInfo.regs);

    /* check if the bit clock of the TX section is generated internally       */
    if ((UInt32) MCASP_ACLKXCTL_CLKXM_INTERNAL ==
        ((tempVal1 & (UInt32) MCASP_ACLKXCTL_CLKXM_MASK)
         >> MCASP_ACLKXCTL_CLKXM_SHIFT))
    {
        /* check if both the sections are in sync                             */
        if ((UInt32) MCASP_ACLKXCTL_ASYNC_SYNC ==
            ((tempVal1 & (UInt32) MCASP_ACLKXCTL_ASYNC_MASK)
             >> MCASP_ACLKXCTL_ASYNC_SHIFT))
        {
            /* check if the TX and RX sections are in sync                    */
            isMaster = (Bool) TRUE;
        }
        else
        {
            /* check if the transmit bit clock is generated internally        */
            if ((UInt32) MCASP_ACLKRCTL_CLKRM_INTERNAL ==
                ((tempVal2 & (UInt32) MCASP_ACLKRCTL_CLKRM_MASK)
                 >> MCASP_ACLKRCTL_CLKRM_SHIFT))
            {
                isMaster = (Bool) TRUE;
            }
        }
    }
    /* update the information to the data structure                           */
    devData->isMaster = isMaster;
}

/* ========================================================================== */
/*                             END OF FILE                                    */
/* ========================================================================== */
