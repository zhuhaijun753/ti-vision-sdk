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
 *  \file bsputils_mbx.c
 *
 *  \brief This file implements application level mailbox functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <xdc/std.h>
#include <common/bsp_types.h>
#include <common/trace.h>
#include <common/bsp_config.h>
#include <common/bsp_utils.h>
#include <osal/bsp_osal.h>
#include <common/bsp_utilsQue.h>
#include <bsputils_mbx.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define BSPUTILS_MBX_MSG_POOL_MAX   ((UInt32) 10240U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static BspUtils_MsgHndl *BspUtils_mbxAllocMsg(UInt32 timeout);
static Int32 BspUtils_mbxFreeMsg(BspUtils_MsgHndl *pMsg, UInt32 timeout);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static BspUtils_QueHandle gBspUtils_mbxMsgPoolFreeQue;
static Ptr gBspUtils_mbxMsgPoolFreeQueMem[BSPUTILS_MBX_MSG_POOL_MAX];
static BspUtils_MsgHndl   gBspUtils_mbxMsgPool[BSPUTILS_MBX_MSG_POOL_MAX];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

UInt32 BspUtils_mbxGetFreeMsgCount(void)
{
    UInt32 cookie;
    UInt32 freeMsg;

    cookie = BspOsal_disableInterrupt();

    freeMsg = gBspUtils_mbxMsgPoolFreeQue.count;

    BspOsal_restoreInterrupt(cookie);

    return (freeMsg);
}

static BspUtils_MsgHndl *BspUtils_mbxAllocMsg(UInt32 timeout)
{
    BspUtils_MsgHndl *pMsg = NULL;

    BspUtils_queGet(&gBspUtils_mbxMsgPoolFreeQue,
                    (Ptr *) &pMsg,
                    (UInt32) 1U,
                    timeout);

    return (pMsg);
}

static Int32 BspUtils_mbxFreeMsg(BspUtils_MsgHndl *pMsg, UInt32 timeout)
{
    Int32 status;

    status = BspUtils_quePut(&gBspUtils_mbxMsgPoolFreeQue, pMsg, timeout);

    return (status);
}

Int32 BspUtils_mbxInit(void)
{
    Int32  status = BSP_SOK;
    UInt32 msgId;

    status = BspUtils_queCreate(&gBspUtils_mbxMsgPoolFreeQue,
                                BSPUTILS_MBX_MSG_POOL_MAX,
                                gBspUtils_mbxMsgPoolFreeQueMem,
                                BSPUTILS_QUE_FLAG_BLOCK_QUE);

    if (status == BSP_SOK)
    {
        for (msgId = 0U; msgId < BSPUTILS_MBX_MSG_POOL_MAX; msgId++)
        {
            status = BspUtils_mbxFreeMsg(
                &gBspUtils_mbxMsgPool[msgId],
                BSP_OSAL_NO_WAIT);
            if (status != BSP_SOK)
            {
                BspUtils_mbxDeInit();
                break;
            }
        }
    }

    return (status);
}

Int32 BspUtils_mbxDeInit(void)
{
    Int32 status;

    status = BspUtils_queDelete(&gBspUtils_mbxMsgPoolFreeQue);

    return (status);
}

Int32 BspUtils_mbxCreate(BspUtils_MbxHndl *pMbx)
{
    Int32 status = BSP_SOK;

    /* create queues  */
    status = BspUtils_queCreate(&pMbx->recvQue,
                                BSPUTILS_MBX_RECV_QUE_LEN_MAX,
                                (Ptr) pMbx->memRecvQue,
                                BSPUTILS_QUE_FLAG_BLOCK_QUE);

    if (BSP_SOK == status)
    {
        status = BspUtils_queCreate(&pMbx->ackQue,
                                    BSPUTILS_MBX_ACK_QUE_LEN_MAX,
                                    (Ptr) pMbx->memAckQue,
                                    BSPUTILS_QUE_FLAG_BLOCK_QUE);
        if (status != BSP_SOK)
        {
            BspUtils_queDelete(&pMbx->recvQue);
        }
    }
    return (status);
}

Int32 BspUtils_mbxDelete(BspUtils_MbxHndl *pMbx)
{
    Int32 status = 0;

    /* delete queues  */
    status += BspUtils_queDelete(&pMbx->recvQue);
    status += BspUtils_queDelete(&pMbx->ackQue);

    return (status);
}

Int32 BspUtils_mbxSendCmd(BspUtils_MbxHndl *pTo, UInt32 cmd)
{
    BspUtils_MsgHndl *pSentMsg;
    Int32 retVal = BSP_SOK;

    if (pTo == NULL)
    {
        retVal = BSP_EFAIL;
    }

    /* alloc message  */
    if (BSP_SOK == retVal)
    {
        pSentMsg = BspUtils_mbxAllocMsg(BSP_OSAL_NO_WAIT);
        if (pSentMsg == NULL)
        {
            retVal = BSP_EFAIL;
        }
    }

    /* set message fields */
    if (BSP_SOK == retVal)
    {
        pSentMsg->pFrom  = NULL;
        pSentMsg->flags  = 0;
        pSentMsg->cmd    = cmd;
        pSentMsg->result = 0;
        pSentMsg->pPrm   = NULL;

        /* send message */
        retVal = BspUtils_quePut(&pTo->recvQue, pSentMsg, BSP_OSAL_NO_WAIT);

        if (retVal != BSP_SOK)
        {
            retVal += BspUtils_mbxFreeMsg(pSentMsg, BSP_OSAL_NO_WAIT);
        }
    }
    return (retVal);
}

Int32 BspUtils_mbxSendMsg(BspUtils_MbxHndl *pFrom,
                          BspUtils_MbxHndl *pTo,
                          UInt32            cmd,
                          void             *pPrm,
                          UInt32            msgFlags)
{
    BspUtils_MsgHndl   *pSentMsg, *pRcvMsg;
    Bool waitAck;
    Int32 retVal = BSP_SOK;
    BspUtils_QueHandle *ackQue;

    if (pTo == NULL)
    {
        retVal = BSP_EFAIL;
    }
    if (BSP_SOK == retVal)
    {
        /* set ACK que  */
        if (pFrom == NULL)
        {
            /* sender mailbox not specified by user */
            if (msgFlags & BSPUTILS_MBX_FLAG_WAIT_ACK)
            {
                /* ERROR: if sender mail box is NULL, then cannot wait for ACK
                **/
                retVal = BSP_EFAIL;
            }
            ackQue = NULL;
        }
        else
        {
            /* sender mail box  */
            ackQue = &pFrom->ackQue;
        }
    }
    if (BSP_SOK == retVal)
    {
        /* alloc message  */
        pSentMsg = BspUtils_mbxAllocMsg(BSP_OSAL_WAIT_FOREVER);
        if (pSentMsg == NULL)
        {
            retVal = BSP_EFAIL;
        }
    }
    if (BSP_SOK == retVal)
    {
        /* set message fields */
        pSentMsg->pFrom  = pFrom;
        pSentMsg->flags  = msgFlags;
        pSentMsg->cmd    = cmd;
        pSentMsg->result = 0;
        pSentMsg->pPrm   = pPrm;

        /* send message */
        retVal = BspUtils_quePut(&pTo->recvQue, pSentMsg, BSP_OSAL_WAIT_FOREVER);
    }

    if (BSP_SOK == retVal)
    {
        if (((msgFlags & BSPUTILS_MBX_FLAG_WAIT_ACK) > 0U) && (ackQue != NULL))
        {
            /* need to wait for ACK */
            waitAck = (Bool) TRUE;

            do
            {
                /* wait for ACK */
                retVal = BspUtils_queGet(&pFrom->ackQue,
                                         (Ptr *) &pRcvMsg,
                                         (UInt32) 1U,
                                         (UInt32) BSP_OSAL_WAIT_FOREVER);
                if (retVal != BSP_SOK)
                {
                    break;
                }

                if (pRcvMsg == pSentMsg)
                {
                    /* ACK received for sent MSG  */
                    waitAck = (Bool) FALSE;

                    /* copy ACK status to return value  */
                    retVal = pRcvMsg->result;
                } /* else ACK received for some other message */

                /* free message */
                retVal += BspUtils_mbxFreeMsg(pRcvMsg, BSP_OSAL_WAIT_FOREVER);
            } while (waitAck);
        }
    }
    return (retVal);
}

Int32 BspUtils_mbxRecvMsg(BspUtils_MbxHndl  *pMbxHndl,
                          BspUtils_MsgHndl **pMsg,
                          UInt32             timeout)
{
    Int32 retVal;

    /* wait for message to arrive */
    retVal = BspUtils_queGet(&pMbxHndl->recvQue, (Ptr *) pMsg, (UInt32) 1U,
                             timeout);

    return (retVal);
}

Int32 BspUtils_mbxAckOrFreeMsg(BspUtils_MsgHndl *pMsg, Int32 ackRetVal)
{
    Int32 retVal = BSP_EFAIL;

    if (pMsg != NULL)
    {
        /* check ACK flag */
        if (pMsg->flags & BSPUTILS_MBX_FLAG_WAIT_ACK)
        {
            /* ACK flag is set */

            /* Set ACK status */
            pMsg->result = ackRetVal;

            /* Send ACK to sender */
            if (pMsg->pFrom == NULL)
            {
                retVal  = BSP_EFAIL;
                retVal += BspUtils_mbxFreeMsg(pMsg, BSP_OSAL_WAIT_FOREVER);
            }
            else
            {
                retVal = BspUtils_quePut(
                    &pMsg->pFrom->ackQue,
                    pMsg,
                    BSP_OSAL_WAIT_FOREVER);
            }
        }
        else
        {
            /* ACK flag is not set  */

            /* free message */
            retVal = BspUtils_mbxFreeMsg(pMsg, BSP_OSAL_WAIT_FOREVER);
        }
    }

    return (retVal);
}

Int32 BspUtils_mbxWaitCmd(BspUtils_MbxHndl  *pMbxHndl,
                          BspUtils_MsgHndl **pMsg,
                          UInt32             waitCmd)
{
    Int32 status = BSP_SOK;
    BspUtils_MsgHndl *pRcvMsg;

    while (BSP_SOK == status)
    {
        /* wait for message */
        status = BspUtils_mbxRecvMsg(pMbxHndl, &pRcvMsg, BSP_OSAL_WAIT_FOREVER);
        if (BSP_SOK == status)
        {
            /* is message command ID same as expected command ID  */
            if (BspUtils_msgGetCmd(pRcvMsg) == waitCmd)
            {
                break;  /* yes, exit loop  */
            }

            /* no, ACK or free received message  */
            status = BspUtils_mbxAckOrFreeMsg(pRcvMsg, 0);
        }
    }

    if (BSP_SOK == status)
    {
        if (pMsg == NULL)
        {
            /* user does not want to examine the message, so free it here */
            status = BspUtils_mbxAckOrFreeMsg(pRcvMsg, 0);
        }
        else
        {
            /* user wants to examine the message to return it to user */
            *pMsg = pRcvMsg;
        }
    }

    return (status);
}

