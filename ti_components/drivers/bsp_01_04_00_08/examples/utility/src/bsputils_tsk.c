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
 *  \file bsputils_buf.c
 *
 *  \brief This file implements application level buffer handling functions.
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
#include <fvid2/fvid2.h>
#include <bsputils_tsk.h>
#include <bsputils_prf.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define BSPUTILS_TSK_CMD_EXIT   (0xFFFFFFFFU)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void BspUtils_tskMain(UArg arg0, UArg arg1);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static void BspUtils_tskMain(UArg arg0, UArg arg1)
{
    BspUtils_TskHndl *pHndl = (BspUtils_TskHndl *) arg0;
    BspUtils_MsgHndl *pMsg;
    Int32 status = FVID2_SOK;
    UInt32 cmd;

    GT_assert(GT_DEFAULT_MASK, pHndl != NULL);

    while (FVID2_SOK == status)
    {
        status = BspUtils_mbxRecvMsg(&pHndl->mbx, &pMsg, BSP_OSAL_WAIT_FOREVER);
        if (FVID2_SOK == status)
        {
            cmd = BspUtils_msgGetCmd(pMsg);
            if (cmd == BSPUTILS_TSK_CMD_EXIT)
            {
                BspUtils_tskAckOrFreeMsg(pMsg, FVID2_SOK);
                break;
            }

            if (pHndl->funcMain)
            {
                pHndl->funcMain(pHndl, pMsg);
            }
        }
    }

    return;
}

Int32 BspUtils_tskCreate(BspUtils_TskHndl    *pHndl,
                         BspUtils_TskFuncMain funcMain,
                         UInt32               tskPri,
                         UInt8               *stackAddr,
                         UInt32               stackSize,
                         Ptr                  appData,
                         const char          *tskName)
{
    Int32 status;

    GT_assert(GT_DEFAULT_MASK, pHndl != NULL);
    GT_assert(GT_DEFAULT_MASK, funcMain != NULL);

    pHndl->funcMain  = funcMain;
    pHndl->stackSize = stackSize;
    pHndl->stackAddr = stackAddr;
    pHndl->tskPri    = tskPri;
    pHndl->appData   = appData;

    status = BspUtils_mbxCreate(&pHndl->mbx);
    GT_assert(GT_DEFAULT_MASK, FVID2_SOK == status);

    pHndl->tsk = BspOsal_taskCreate(
        (BspOsal_TaskFuncPtr) & BspUtils_tskMain,
        (Int32) tskPri,
        stackAddr,
        stackSize,
        pHndl);
    GT_assert(GT_DEFAULT_MASK, pHndl->tsk != NULL);

    BspUtils_prfLoadRegister((Task_Handle) pHndl->tsk, tskName);

    return (status);
}

Int32 BspUtils_tskDelete(BspUtils_TskHndl *pHndl)
{
    BspUtils_prfLoadUnRegister((Task_Handle) pHndl->tsk);

    BspUtils_tskSendCmd(pHndl, BSPUTILS_TSK_CMD_EXIT);
    /* wait for command to be received
     * and task to be exited - BspOsal_taskDelete() internally waits for task
     * to exit */
    BspOsal_sleep((UInt32) 1U);
    BspOsal_taskDelete(&pHndl->tsk);
    BspUtils_mbxDelete(&pHndl->mbx);

    return (FVID2_SOK);
}

