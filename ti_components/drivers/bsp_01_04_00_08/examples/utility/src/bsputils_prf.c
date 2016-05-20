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
 *  \file bsputils_prf.c
 *
 *  \brief Profiling API utility file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/Timestamp.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/utils/Load.h>

#include <common/bsp_types.h>
#include <common/trace.h>
#include <common/bsp_config.h>
#include <common/bsp_utils.h>
#include <osal/bsp_osal.h>
#include <bsputils_prf.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    Bool        isAlloc;
    Char        name[32];
    Task_Handle pTsk;
    UInt64      totalTskThreadTime;
} BspUtils_PrfLoadObj;

typedef struct
{
    BspUtils_PrfTsHndl  tsObj[BSPUTILS_PRF_MAX_HNDL];
    BspUtils_PrfLoadObj loadObj[BSPUTILS_PRF_MAX_HNDL];
} BspUtils_PrfObj;

typedef struct
{
    UInt64 totalSwiThreadTime;
    UInt64 totalHwiThreadTime;
    UInt64 totalTime;
    UInt64 totalIdlTskTime;
} BspUtils_AccPrfLoadObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static BspUtils_PrfObj        gBspUtils_prfObj;
static BspUtils_AccPrfLoadObj gBspUtils_accPrfLoadObj;
static UInt32 gBspUtils_startLoadCalc = 0;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 BspUtils_prfInit(void)
{
    BspUtils_memset(&gBspUtils_prfObj, 0, sizeof (gBspUtils_prfObj));
    BspUtils_memset(&gBspUtils_accPrfLoadObj, 0, sizeof (BspUtils_AccPrfLoadObj));

    return (0);
}

Int32 BspUtils_prfDeInit(void)
{
    return (0);
}

BspUtils_PrfTsHndl *BspUtils_prfTsCreate(const Char *name)
{
    UInt32 hndlId;
    UInt32 cookie;
    BspUtils_PrfTsHndl *pHndl = NULL;

    cookie = Hwi_disable();

    for (hndlId = 0; hndlId < BSPUTILS_PRF_MAX_HNDL; hndlId++)
    {
        pHndl = &gBspUtils_prfObj.tsObj[hndlId];

        if (FALSE == pHndl->isAlloc)
        {
            /* One less for NULL character */
            strncpy(pHndl->name, name, ((UInt32) sizeof (pHndl->name) - 1U));
            pHndl->name[sizeof (pHndl->name) - 1] = (UInt8) '\0';
            pHndl->isAlloc = (Bool) TRUE;
            BspUtils_prfTsReset(pHndl);
            break;
        }
    }

    Hwi_restore(cookie);

    return (pHndl);
}

Int32 BspUtils_prfTsDelete(BspUtils_PrfTsHndl *pHndl)
{
    pHndl->isAlloc = (Bool) FALSE;
    return (0);
}

UInt64 BspUtils_prfTsBegin(BspUtils_PrfTsHndl *pHndl)
{
    pHndl->startTs = BspUtils_prfTsGet64();

    return (pHndl->startTs);
}

UInt64 BspUtils_prfTsEnd(BspUtils_PrfTsHndl *pHndl, UInt32 numFrames)
{
    return (BspUtils_prfTsDelta(pHndl, pHndl->startTs, numFrames));
}

UInt64 BspUtils_prfTsDelta(BspUtils_PrfTsHndl *pHndl,
                           UInt64              startTime,
                           UInt32              numFrames)
{
    UInt64 endTs;
    UInt32 cookie;

    endTs = BspUtils_prfTsGet64();

    cookie = Hwi_disable();

    pHndl->totalTs += (endTs - pHndl->startTs);
    pHndl->count++;
    pHndl->numFrames += numFrames;

    Hwi_restore(cookie);

    return (endTs);
}

Int32 BspUtils_prfTsReset(BspUtils_PrfTsHndl *pHndl)
{
    UInt32 cookie;

    cookie = Hwi_disable();

    pHndl->totalTs   = 0;
    pHndl->count     = 0;
    pHndl->numFrames = 0;

    Hwi_restore(cookie);

    return (0);
}

UInt64 BspUtils_prfTsGet64(void)
{
    UInt64 curTs;
    Types_Timestamp64 ts64;

    Timestamp_get64(&ts64);

    curTs = ((UInt64) ts64.hi << 32) | ts64.lo;

    return (curTs);
}

Int32 BspUtils_prfTsPrint(BspUtils_PrfTsHndl *pHndl, Bool resetAfterPrint)
{
    UInt32       cpuKhz;
    UInt32       timeMs, fps, fpc;
    Types_FreqHz cpuHz;

    Timestamp_getFreq(&cpuHz);

    cpuKhz = cpuHz.lo / (UInt32) 1000U; /* convert to Khz */

    timeMs = pHndl->totalTs / cpuKhz;

    fps = (pHndl->numFrames * (UInt32) 1000U) / timeMs;
    fpc = pHndl->numFrames / pHndl->count;

    GT_7trace(
        BspAppTrace, GT_INFO,
        " %d: PRF : %s : t: %d ms, count: %d, frames: %d, fps: %d, fpc: %d \r\n",
        BspOsal_getCurTimeInMsec(),
        pHndl->name,
        timeMs,       /* in msecs    */
        pHndl->count,
        pHndl->numFrames,
        fps,       /* frames per second */
        fpc        /* frames per count */
        );

    if (resetAfterPrint)
    {
        BspUtils_prfTsReset(pHndl);
    }

    return (0);
}

Int32 BspUtils_prfTsPrintAll(Bool resetAfterPrint)
{
    UInt32 hndlId;
    BspUtils_PrfTsHndl *pHndl;

    GT_0trace(BspAppTrace, GT_INFO, "\r\n");

    for (hndlId = 0; hndlId < BSPUTILS_PRF_MAX_HNDL; hndlId++)
    {
        pHndl = &gBspUtils_prfObj.tsObj[hndlId];

        if (TRUE == pHndl->isAlloc)
        {
            BspUtils_prfTsPrint(pHndl, resetAfterPrint);
        }
    }

    GT_0trace(BspAppTrace, GT_INFO, "\r\n");

    return (0);
}

Int32 BspUtils_prfLoadRegister(Task_Handle pTsk, const Char *name)
{
    UInt32 hndlId;
    UInt32 cookie;
    Int32  status = BSP_EFAIL;
    BspUtils_PrfLoadObj *pHndl;

    cookie = Hwi_disable();

    for (hndlId = 0; hndlId < BSPUTILS_PRF_MAX_HNDL; hndlId++)
    {
        pHndl = &gBspUtils_prfObj.loadObj[hndlId];

        if (FALSE == pHndl->isAlloc)
        {
            pHndl->isAlloc = (Bool) TRUE;
            pHndl->pTsk    = pTsk;
            /* One less for NULL character */
            strncpy(pHndl->name, name, ((UInt32) sizeof (pHndl->name) - 1U));
            pHndl->name[sizeof (pHndl->name) - 1] = (UInt8) '\0';
            status = BSP_SOK;
            break;
        }
    }

    Hwi_restore(cookie);

    return (status);
}

Int32 BspUtils_prfLoadUnRegister(Task_Handle pTsk)
{
    UInt32 hndlId;
    UInt32 cookie;
    Int32  status = BSP_EFAIL;
    BspUtils_PrfLoadObj *pHndl;

    cookie = Hwi_disable();

    for (hndlId = 0; hndlId < BSPUTILS_PRF_MAX_HNDL; hndlId++)
    {
        pHndl = &gBspUtils_prfObj.loadObj[hndlId];

        if ((TRUE == pHndl->isAlloc) && (pHndl->pTsk == pTsk))
        {
            pHndl->isAlloc = (Bool) FALSE;
            status         = BSP_SOK;
            break;
        }
    }

    Hwi_restore(cookie);

    return (status);
}

Int32 BspUtils_prfLoadPrintAll(Bool printTskLoad)
{
    UInt32 hwiLoad, swiLoad, tskLoad, hndlId, cpuLoad;
    BspUtils_PrfLoadObj *pHndl;

    hwiLoad = (UInt32) ((gBspUtils_accPrfLoadObj.totalHwiThreadTime *
                         (UInt64) 100U) / gBspUtils_accPrfLoadObj.totalTime);
    swiLoad = (UInt32) ((gBspUtils_accPrfLoadObj.totalSwiThreadTime *
                         (UInt64) 100U) / gBspUtils_accPrfLoadObj.totalTime);
    cpuLoad = (UInt32) 100U -
              (UInt32) ((gBspUtils_accPrfLoadObj.totalIdlTskTime *
                         (UInt64) 100U) /
                        gBspUtils_accPrfLoadObj.totalTime);

    GT_0trace(BspAppTrace, GT_INFO, "\r\n");
    GT_4trace(BspAppTrace, GT_INFO,
              " %d: LOAD: CPU: %d%%, HWI: %d%%, SWI:%d%% \n",
              BspOsal_getCurTimeInMsec(),
              cpuLoad,
              hwiLoad,
              swiLoad);

    if (((Bool) TRUE) == printTskLoad)
    {
        for (hndlId = 0; hndlId < BSPUTILS_PRF_MAX_HNDL; hndlId++)
        {
            pHndl = &gBspUtils_prfObj.loadObj[hndlId];

            if (TRUE == pHndl->isAlloc)
            {
                tskLoad = (UInt32) ((pHndl->totalTskThreadTime *
                                     (UInt64) 100U) /
                                    gBspUtils_accPrfLoadObj.totalTime);

                GT_3trace(BspAppTrace, GT_INFO,
                          " %d: LOAD: TSK: %s: %d%% \r\n",
                          BspOsal_getCurTimeInMsec(),
                          pHndl->name,
                          tskLoad);
            }
        }
    }

    GT_0trace(BspAppTrace, GT_INFO, "\r\n");

    return (0);
}

void BspUtils_prfLoadCalcStart(void)
{
    UInt32 cookie;

    cookie = Hwi_disable();
    gBspUtils_startLoadCalc = (UInt32) TRUE;
    Hwi_restore(cookie);

    return;
}

void BspUtils_prfLoadCalcStop(void)
{
    UInt32 cookie;

    cookie = Hwi_disable();
    gBspUtils_startLoadCalc = FALSE;
    Hwi_restore(cookie);

    return;
}

void BspUtils_prfLoadCalcReset(void)
{
    UInt32 hndlId;
    BspUtils_PrfLoadObj *pHndl;

    gBspUtils_accPrfLoadObj.totalHwiThreadTime = 0;
    gBspUtils_accPrfLoadObj.totalSwiThreadTime = 0;
    gBspUtils_accPrfLoadObj.totalTime          = 0;
    gBspUtils_accPrfLoadObj.totalIdlTskTime    = 0;

    /* Reset the performace loads accumulator */
    for (hndlId = 0; hndlId < BSPUTILS_PRF_MAX_HNDL; hndlId++)
    {
        pHndl = &gBspUtils_prfObj.loadObj[hndlId];

        if (((Bool) TRUE == pHndl->isAlloc) &&
            (pHndl->pTsk != NULL))
        {
            pHndl->totalTskThreadTime = 0;
        }
    }

    return;
}

/* Function called by Loadupdate for each update cycle */
void BspUtils_prfLoadUpdate(void)
{
    UInt32               hndlId;
    Load_Stat            hwiLoadStat, swiLoadStat, tskLoadStat, idlTskLoadStat;
    Task_Handle          idlTskHndl = NULL;
    BspUtils_PrfLoadObj *pHndl;

    if (((Bool) TRUE) == (Bool) gBspUtils_startLoadCalc)
    {
        idlTskHndl = Task_getIdleTask();

        /* Get the all loads first */
        Load_getGlobalHwiLoad(&hwiLoadStat);
        Load_getGlobalSwiLoad(&swiLoadStat);
        Load_getTaskLoad(idlTskHndl, &idlTskLoadStat);

        gBspUtils_accPrfLoadObj.totalHwiThreadTime += hwiLoadStat.threadTime;
        gBspUtils_accPrfLoadObj.totalSwiThreadTime += swiLoadStat.threadTime;
        gBspUtils_accPrfLoadObj.totalTime          += hwiLoadStat.totalTime;
        gBspUtils_accPrfLoadObj.totalIdlTskTime    += idlTskLoadStat.threadTime;

        /* Call the load updated function of each registered task one by one
         * along with the swiLoad, hwiLoad, and Task's own load */
        for (hndlId = 0; hndlId < BSPUTILS_PRF_MAX_HNDL; hndlId++)
        {
            pHndl = &gBspUtils_prfObj.loadObj[hndlId];

            if (((Bool) TRUE == pHndl->isAlloc) &&
                (pHndl->pTsk != NULL))
            {
                Load_getTaskLoad(pHndl->pTsk, &tskLoadStat);
                pHndl->totalTskThreadTime += tskLoadStat.threadTime;
            }
        }
    }

    return;
}

