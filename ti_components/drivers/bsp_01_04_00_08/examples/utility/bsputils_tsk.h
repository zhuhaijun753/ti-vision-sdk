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
 *  \ingroup BSPUTILS_API
 *  \defgroup BSPUTILS_TSK_API Task wrapper APIs
 *
 *  APIs in this file couple a BIOS Task with a mailbox in order to allow
 *  application to implement a state machine kind of logic, where in state
 *  change happens based on received message's
 *
 *  @{
 */

/**
 *  \file bsputils_tsk.h
 *  \brief Task wrapper API
 */

#ifndef BSPUTILS_TSK_H_
#define BSPUTILS_TSK_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <osal/bsp_osal.h>
#include "bsputils_mbx.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

struct BspUtils_TskHndl_t;

/**
 *  \brief Task main function
 *
 *  This function is called when a message is received by the
 *  task.
 *
 *  \param pHndl [OUT] Task handle
 *  \param pMsg  [OUT] Received message
 */
typedef void (*BspUtils_TskFuncMain)(struct BspUtils_TskHndl_t *pHndl,
                                     BspUtils_MsgHndl          *pMsg);

/**
 *  \brief Task handle.
 */
typedef struct BspUtils_TskHndl_t
{
    BspOsal_TaskHandle   tsk;
    /**< BIOS Task handle. */
    BspUtils_MbxHndl     mbx;
    /**< Mail box associated with this task. */

    UInt8               *stackAddr;
    /**< Task stack address. */
    UInt32               stackSize;
    /**< Task stack size. */

    UInt32               tskPri;
    /**< Task priority as defined by BIOS. */
    BspUtils_TskFuncMain funcMain;
    /**< Task main.
     *  Note, this is different from BIOS Task, since this function
     *  is entered ONLY when a message is received. */
    Ptr                  appData;
    /**< Application specific data. */
} BspUtils_TskHndl;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Create a task
 *
 *  \param pHndl        [OUT] Task handle
 *  \param funcMain     [IN]  Task main,
 *                            Note, this is different from BIOS Task, since
 *                            this function
 *                            is entered ONLY when a message is received.
 *  \param tskPri       [IN]  Task priority as defined by BIOS
 *  \param stackAddr    [IN]  Task stack address
 *  \param stackSize    [IN]  Task stack size
 *  \param appData      [IN]  Application specific data
 *  \param tskName      [IN]  Task name
 *
 *  \return FVID2_SOK on success else failure
 */
Int32 BspUtils_tskCreate(BspUtils_TskHndl    *pHndl,
                         BspUtils_TskFuncMain funcMain,
                         UInt32               tskPri,
                         UInt8               *stackAddr,
                         UInt32               stackSize,
                         Ptr                  appData,
                         const char          *tskName);

/**
 *  \brief Delete a task
 *
 *  \param pHndl        [OUT] Task handle
 *
 *  \return FVID2_SOK on success else failure
 */
Int32 BspUtils_tskDelete(BspUtils_TskHndl *pHndl);

/**
 *  \brief Send message from one task to another task
 *
 *  Refer to BspUtils_mbxSendMsg() for details
 */
static inline Int32 BspUtils_tskSendMsg(BspUtils_TskHndl *pFrom,
                                        BspUtils_TskHndl *pTo,
                                        UInt32            cmd,
                                        void             *pPrm,
                                        UInt32            msgFlags);

/**
 *  \brief Send 32-bit command to another task
 *
 *  Refer to BspUtils_mbxSendCmd() for details
 */
static inline Int32 BspUtils_tskSendCmd(BspUtils_TskHndl *pTo,
                                        UInt32            cmd);

/**
 *  \brief Wait for a message to arrive
 *
 *  Refer to BspUtils_mbxRecvMsg() for details
 */
static inline Int32 BspUtils_tskRecvMsg(BspUtils_TskHndl  *pHndl,
                                        BspUtils_MsgHndl **pMsg,
                                        UInt32             timeout);

/**
 *  \brief ACK or free received message
 *
 *  Refer to BspUtils_mbxAckOrFreeMsg() for details
 */
static inline Int32 BspUtils_tskAckOrFreeMsg(BspUtils_MsgHndl *pMsg,
                                             Int32             result);

/**
 *  \brief Wait until user specified command is received
 *
 *  Refer to BspUtils_mbxWaitCmd() for details
 */
static inline Int32 BspUtils_tskWaitCmd(BspUtils_TskHndl  *pHndl,
                                        BspUtils_MsgHndl **pMsg,
                                        UInt32             cmdToWait);

/* ========================================================================== */
/*                          Static Function Definition                        */
/* ========================================================================== */

static inline Int32 BspUtils_tskSendMsg(BspUtils_TskHndl *pFrom,
                                        BspUtils_TskHndl *pTo,
                                        UInt32            cmd,
                                        void             *pPrm,
                                        UInt32            msgFlags)
{
    return BspUtils_mbxSendMsg(&pFrom->mbx, &pTo->mbx, cmd, pPrm, msgFlags);
}

static inline Int32 BspUtils_tskSendCmd(BspUtils_TskHndl *pTo,
                                        UInt32            cmd)
{
    return BspUtils_mbxSendCmd(&pTo->mbx, cmd);
}

static inline Int32 BspUtils_tskRecvMsg(BspUtils_TskHndl  *pHndl,
                                        BspUtils_MsgHndl **pMsg,
                                        UInt32             timeout)
{
    return BspUtils_mbxRecvMsg(&pHndl->mbx, pMsg, timeout);
}

static inline Int32 BspUtils_tskAckOrFreeMsg(BspUtils_MsgHndl *pMsg,
                                             Int32             result)
{
    return BspUtils_mbxAckOrFreeMsg(pMsg, result);
}

static inline Int32 BspUtils_tskWaitCmd(BspUtils_TskHndl  *pHndl,
                                        BspUtils_MsgHndl **pMsg,
                                        UInt32             cmdToWait)
{
    return BspUtils_mbxWaitCmd(&pHndl->mbx, pMsg, cmdToWait);
}

#ifdef __cplusplus
}
#endif

#endif  /* #define BSPUTILS_TSK_H_ */

/* @} */
