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
 *  \file bsp_osal.c
 *
 *  \brief Implement the OSAL layer for BIOS.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <xdc/std.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Timestamp.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/hal/Cache.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>

#include <common/bsp_types.h>
#include <osal/bsp_osal.h>
#include <osal/bsp_osalCfg.h>

#include <platforms/bsp_platform.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

#if (BSP_OSAL_CFG_USE_STATIC == TRUE)
typedef struct
{
    UInt32           isUsed;
    Semaphore_Struct semStruct;
} BspOsal_SemObj;

typedef struct
{
    UInt32      isUsed;
    Task_Struct taskStruct;
} BspOsal_TaskObj;

typedef struct
{
    UInt32       isUsed;
    Clock_Struct clockStruct;
} BspOsal_ClockObj;

typedef struct
{
    UInt32     isUsed;
    Hwi_Struct hwiStruct;
} BspOsal_HwiObj;
#endif

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

BspOsal_TaskHandle BspOsal_taskCreate(
    BspOsal_TaskFuncPtr fxn,
    Int32
    priority,
    void               *stack,
    UInt32
    stackSize,
    const void         *arg0);
void BspOsal_taskDelete(BspOsal_TaskHandle *pTskHandle);
BspOsal_SemHandle BspOsal_semCreate(Int32 initValue,
                                    Bool  isBinary);
void BspOsal_semDelete(BspOsal_SemHandle *pSemHandle);
Bool BspOsal_semWait(BspOsal_SemHandle semHandle, UInt32 timeOut);
void BspOsal_semPost(BspOsal_SemHandle semHandle);
BspOsal_ClockHandle BspOsal_clockCreate(
    BspOsal_ClockFuncPtr fxn,
    UInt32
    period,
    Bool
    startFlag,
    const void          *arg0);
void BspOsal_clockDelete(BspOsal_ClockHandle *pClkHandle);
void BspOsal_clockStart(BspOsal_ClockHandle clkHandle);
void BspOsal_clockStop(BspOsal_ClockHandle clkHandle);
UInt32 BspOsal_getClockTicks(void);
BspOsal_IntrHandle BspOsal_registerIntr(
    UInt32              intNum,
    BspOsal_IntrFuncPtr fxn,
    void               *arg0);
void BspOsal_unRegisterIntr(const BspOsal_IntrHandle *pIntrHandle);
void BspOsal_clearIntr(UInt32 intNum);
UInt32 BspOsal_disableInterrupt(void);
void BspOsal_restoreInterrupt(UInt32 cookie);
void BspOsal_sleep(UInt32 delayMsec);

static Cache_Type BspOsal_getBiosCacheType(UInt32 type);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#if (BSP_OSAL_CFG_USE_STATIC == TRUE)
static BspOsal_SemObj   gBspOsalSemObj[BSP_OSAL_CFG_MAX_SEM_OBJECTS] = {0};
static BspOsal_TaskObj  gBspOsalTaskObj[BSP_OSAL_CFG_MAX_TASK_OBJECTS] = {0};
static BspOsal_ClockObj gBspOsalClockObj[BSP_OSAL_CFG_MAX_CLOCK_OBJECTS] = {0};
static BspOsal_HwiObj   gBspOsalHwiObj[BSP_OSAL_CFG_MAX_HWI_OBJECTS] = {0};

static UInt32           gBspOsalSemAllocCnt   = 0U, gBspOsalSemPeak = 0U;
static UInt32           gBspOsalTaskAllocCnt  = 0U, gBspOsalTaskPeak = 0U;
static UInt32           gBspOsalClockAllocCnt = 0U, gBspOsalClockPeak = 0U;
static UInt32           gBspOsalHwiAllocCnt   = 0U, gBspOsalHwiPeak = 0U;
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 BspOsal_printf(const Char *format, ...)
{
    va_list vaArgPtr;
    Int32   retVal = BSP_SOK;
    Int32   val;
    UInt32  cookie;

    cookie = BspOsal_disableInterrupt();

    va_start(vaArgPtr, format);
    val = va_arg(vaArgPtr, Int32);
    va_end(vaArgPtr);

    BspOsal_restoreInterrupt(cookie);

    System_printf((CString) format, val);

    return (retVal);
}

Int32 BspOsal_scanf(const Char *format, ...)
{
    va_list vaArgPtr;
    Int32   retVal = BSP_SOK;
    Int32   val;
    UInt32  cookie;

    cookie = BspOsal_disableInterrupt();

    va_start(vaArgPtr, format);
    val = va_arg(vaArgPtr, Int32);
    va_end(vaArgPtr);

    BspOsal_restoreInterrupt(cookie);

    scanf((CString) format, val);

    return (retVal);
}

BspOsal_TaskHandle BspOsal_taskCreate(
    BspOsal_TaskFuncPtr fxn,
    Int32               priority,
    void               *stack,
    UInt32              stackSize,
    const void         *arg0)
{
    Task_Params tskPrms;
#if (BSP_OSAL_CFG_USE_STATIC == TRUE)
    UInt32      i;
    Task_Handle taskHandle = NULL;
    UInt32      cookie;
#endif

    Task_Params_init(&tskPrms);
    tskPrms.priority  = priority;
    tskPrms.stack     = stack;
    tskPrms.stackSize = stackSize;
    tskPrms.arg0      = (UInt32) arg0;
    tskPrms.arg1      = (UInt32) arg0;
#if (BSP_OSAL_CFG_USE_STATIC == TRUE)
    cookie = BspOsal_disableInterrupt();
    for (i = 0; i < BSP_OSAL_CFG_MAX_TASK_OBJECTS; i++)
    {
        if (gBspOsalTaskObj[i].isUsed == FALSE)
        {
            gBspOsalTaskObj[i].isUsed = TRUE;

            /* Update statistics */
            gBspOsalTaskAllocCnt++;
            if (gBspOsalTaskAllocCnt > gBspOsalTaskPeak)
            {
                gBspOsalTaskPeak = gBspOsalTaskAllocCnt;
            }
            break;
        }
    }
    BspOsal_restoreInterrupt(cookie);

    if (i < BSP_OSAL_CFG_MAX_TASK_OBJECTS)
    {
        /* We have found unused bsp osal task object */
        Task_construct(&(gBspOsalTaskObj[i].taskStruct), (Task_FuncPtr) fxn,
                       &tskPrms,
                       NULL);
        taskHandle = Task_handle(&(gBspOsalTaskObj[i].taskStruct));
    }
    else
    {
        BspOsal_printf("No free BspOsal_TaskObj found\n");
    }
    return taskHandle;
#else
    return (BspOsal_TaskHandle) Task_create((Task_FuncPtr) fxn, &tskPrms, NULL);
#endif
}

void BspOsal_taskDelete(BspOsal_TaskHandle *pTskHandle)
{
    UInt32       sleepTime = 16U;    /* in OS ticks */
#if (BSP_OSAL_CFG_USE_STATIC == TRUE)
    UInt32       i;
    Task_Struct *taskStruct;
    UInt32       cookie;
#endif

    /* confirm task termination */
    while (Task_Mode_TERMINATED != Task_getMode(*((Task_Handle *) pTskHandle)))
    {
        BspOsal_sleep(sleepTime);
        sleepTime >>= 1U;
        if (sleepTime == 0U)
        {
            /* Force delete after timeout */
            break;
        }
    }

    if (FALSE == ti_sysbios_knl_Task_deleteTerminatedTasks__C)
    {
#if (BSP_OSAL_CFG_USE_STATIC == TRUE)
        taskStruct = Task_struct(*((Task_Handle *) pTskHandle));
        cookie     = BspOsal_disableInterrupt();
        for (i = 0; i < BSP_OSAL_CFG_MAX_TASK_OBJECTS; i++)
        {
            if (gBspOsalTaskObj[i].isUsed != FALSE)
            {
                if ((&gBspOsalTaskObj[i].taskStruct) == taskStruct)
                {
                    /* Found the bsp osal task object to delete */
                    if (gBspOsalTaskAllocCnt > 0U)
                    {
                        gBspOsalTaskAllocCnt--;
                    }
                    break;
                }
            }
        }
        BspOsal_restoreInterrupt(cookie);

        if (i < BSP_OSAL_CFG_MAX_TASK_OBJECTS)
        {
            Task_destruct(taskStruct);
            memset(&gBspOsalTaskObj[i], 0, sizeof (BspOsal_TaskObj));
        }
        else
        {
            BspOsal_printf("BspOsal_TaskHandle passed is not in Used state\n");
        }
#else
        Task_delete((Task_Handle *) pTskHandle);
#endif
    }

    return;
}

UInt32 BspOsal_getTaskStackUsage(BspOsal_TaskHandle tskHandle)
{
    Task_Stat taskStat;

    if (NULL == tskHandle)
    {
        Task_stat(Task_self(), &taskStat);
    }
    else
    {
        Task_stat((Task_Handle) tskHandle, &taskStat);
    }

    return (taskStat.used);
}

UInt32 BspOsal_getSystemStackUsage(void)
{
    Hwi_StackInfo stkInfo;
    volatile Bool stackOverflow = FALSE;

    /* Request stack depth */
    stackOverflow = Hwi_getStackInfo(&stkInfo, (Bool) TRUE);
    if (stackOverflow)
    {
        /* isr Stack Overflow detected */
        BspOsal_printf("Stack overflow detected!!\n");
    }

    return (stkInfo.hwiStackPeak);
}

BspOsal_SemHandle BspOsal_semCreate(Int32 initValue,
                                    Bool  isBinary)
{
    Semaphore_Params semParams;
#if (BSP_OSAL_CFG_USE_STATIC == TRUE)
    UInt32           i;
    Semaphore_Handle semHandle = NULL;
    UInt32           cookie;
#endif

    Semaphore_Params_init(&semParams);
    semParams.mode = Semaphore_Mode_COUNTING;
    if (isBinary)
    {
        semParams.mode = Semaphore_Mode_BINARY;
    }
#if (BSP_OSAL_CFG_USE_STATIC == TRUE)
    cookie = BspOsal_disableInterrupt();
    for (i = 0; i < BSP_OSAL_CFG_MAX_SEM_OBJECTS; i++)
    {
        if (gBspOsalSemObj[i].isUsed == FALSE)
        {
            /* We have found unused bsp osal semaphore object */
            gBspOsalSemObj[i].isUsed = TRUE;

            /* Update statistics */
            gBspOsalSemAllocCnt++;
            if (gBspOsalSemAllocCnt > gBspOsalSemPeak)
            {
                gBspOsalSemPeak = gBspOsalSemAllocCnt;
            }
            break;
        }
    }
    BspOsal_restoreInterrupt(cookie);

    if (i < BSP_OSAL_CFG_MAX_SEM_OBJECTS)
    {
        Semaphore_construct(&(gBspOsalSemObj[i].semStruct), initValue,
                            &semParams);
        semHandle = Semaphore_handle(&(gBspOsalSemObj[i].semStruct));
    }
    else
    {
        BspOsal_printf("No free BspOsal_SemObj found\n");
    }
    return semHandle;
#else
    return (BspOsal_SemHandle) Semaphore_create(initValue, &semParams, NULL);
#endif
}

void BspOsal_semDelete(BspOsal_SemHandle *pSemHandle)
{
#if (BSP_OSAL_CFG_USE_STATIC == TRUE)
    UInt32 i;
    Semaphore_Struct *semStruct;
    UInt32 cookie;

    semStruct = Semaphore_struct(*((Semaphore_Handle *) pSemHandle));
    cookie    = BspOsal_disableInterrupt();
    for (i = 0; i < BSP_OSAL_CFG_MAX_SEM_OBJECTS; i++)
    {
        if (gBspOsalSemObj[i].isUsed != FALSE)
        {
            if ((&gBspOsalSemObj[i].semStruct) == semStruct)
            {
                /* Found the bsp osal semaphore object to delete */
                if (gBspOsalSemAllocCnt > 0U)
                {
                    gBspOsalSemAllocCnt--;
                }
                break;
            }
        }
    }
    BspOsal_restoreInterrupt(cookie);

    if (i < BSP_OSAL_CFG_MAX_SEM_OBJECTS)
    {
        Semaphore_destruct(semStruct);
        memset(&gBspOsalSemObj[i], 0, sizeof (BspOsal_SemObj));
    }
    else
    {
        BspOsal_printf("BspOsal_SemHandle passed is not in Used state\n");
    }

#else
    Semaphore_delete((Semaphore_Handle *) pSemHandle);
#endif
    return;
}

Bool BspOsal_semWait(BspOsal_SemHandle semHandle, UInt32 timeOut)
{
    if (timeOut == BSP_OSAL_WAIT_FOREVER)
    {
        timeOut = BIOS_WAIT_FOREVER;
    }
    if (timeOut == BSP_OSAL_NO_WAIT)
    {
        timeOut = BIOS_NO_WAIT;
    }
    return Semaphore_pend((Semaphore_Handle) semHandle, timeOut);
}

void BspOsal_semPost(BspOsal_SemHandle semHandle)
{
    Semaphore_post((Semaphore_Handle) semHandle);
    return;
}

/* Period is in OS ticks - assumed to be 1ms */
BspOsal_ClockHandle BspOsal_clockCreate(
    BspOsal_ClockFuncPtr fxn,
    UInt32
    period,
    Bool
    startFlag,
    const void          *arg0)
{
    Clock_Params clkPrms;
    Clock_Handle clkHandle = NULL;
#if (BSP_OSAL_CFG_USE_STATIC == TRUE)
    UInt32       i;
    UInt32       cookie;
#endif

    Clock_Params_init(&clkPrms);
    clkPrms.startFlag = startFlag;
    clkPrms.period    = period;
    clkPrms.arg       = (UInt32) arg0;
#if (BSP_OSAL_CFG_USE_STATIC == TRUE)
    cookie = BspOsal_disableInterrupt();
    for (i = 0; i < BSP_OSAL_CFG_MAX_CLOCK_OBJECTS; i++)
    {
        if (gBspOsalClockObj[i].isUsed == FALSE)
        {
            /* We have found unused bsp osal clock object */
            gBspOsalClockObj[i].isUsed = TRUE;

            /* Update statistics */
            gBspOsalClockAllocCnt++;
            if (gBspOsalClockAllocCnt > gBspOsalClockPeak)
            {
                gBspOsalClockPeak = gBspOsalClockAllocCnt;
            }
            break;
        }
    }
    BspOsal_restoreInterrupt(cookie);

    if (i < BSP_OSAL_CFG_MAX_CLOCK_OBJECTS)
    {
        Clock_construct(&(gBspOsalClockObj[i].clockStruct), (Clock_FuncPtr) fxn,
                        period,
                        &clkPrms);
        clkHandle = Clock_handle(&(gBspOsalClockObj[i].clockStruct));
    }
    else
    {
        BspOsal_printf("No free BspOsal_ClockObj found\n");
    }
#else
    clkHandle = Clock_create((Clock_FuncPtr) fxn, period, &clkPrms,
                             NULL);
#endif
    if (clkHandle != NULL)
    {
        /* Set timer expiry time in OS ticks */
        Clock_setTimeout((Clock_Handle) clkHandle, period);
        Clock_setPeriod((Clock_Handle) clkHandle, period);
    }

    return (BspOsal_ClockHandle) clkHandle;
}

void BspOsal_clockDelete(BspOsal_ClockHandle *pClkHandle)
{
#if (BSP_OSAL_CFG_USE_STATIC == TRUE)
    UInt32        i;
    Clock_Struct *clkStruct;
    UInt32        cookie;

    clkStruct = Clock_struct(*((Clock_Handle *) pClkHandle));
    cookie    = BspOsal_disableInterrupt();
    for (i = 0; i < BSP_OSAL_CFG_MAX_CLOCK_OBJECTS; i++)
    {
        if (gBspOsalClockObj[i].isUsed != FALSE)
        {
            if ((&gBspOsalClockObj[i].clockStruct) == clkStruct)
            {
                /* Found the bsp osal clock object to delete */
                if (gBspOsalClockAllocCnt > 0U)
                {
                    gBspOsalClockAllocCnt--;
                }
                break;
            }
        }
    }
    BspOsal_restoreInterrupt(cookie);

    if (i < BSP_OSAL_CFG_MAX_CLOCK_OBJECTS)
    {
        Clock_destruct(clkStruct);
        memset(&gBspOsalClockObj[i], 0, sizeof (BspOsal_ClockObj));
    }
    else
    {
        BspOsal_printf("BspOsal_ClockHandle passed is not in Used state\n");
    }
#else
    Clock_delete((Clock_Handle *) pClkHandle);
#endif

    return;
}

void BspOsal_clockStart(BspOsal_ClockHandle clkHandle)
{
    Clock_start((Clock_Handle) clkHandle);

    return;
}

void BspOsal_clockStop(BspOsal_ClockHandle clkHandle)
{
    Clock_stop((Clock_Handle) clkHandle);

    return;
}

UInt32 BspOsal_getClockTicks(void)
{
    return Clock_getTicks();
}

BspOsal_IntrHandle BspOsal_registerIntr(
    UInt32              intNum,
    BspOsal_IntrFuncPtr fxn,
    void               *arg0)
{
    Hwi_Params hwiParams = {0};
#if (BSP_OSAL_CFG_USE_STATIC == TRUE)
    UInt32     i;
    Hwi_Handle hwiHandle = NULL;
    UInt32     cookie;
#endif

    Hwi_Params_init(&hwiParams);
    hwiParams.arg = (UInt32) arg0;
#if (BSP_OSAL_CFG_USE_STATIC == TRUE)
    cookie = BspOsal_disableInterrupt();
    for (i = 0; i < BSP_OSAL_CFG_MAX_HWI_OBJECTS; i++)
    {
        if (gBspOsalHwiObj[i].isUsed == FALSE)
        {
            /* We have found unused bsp osal hwi object */
            gBspOsalHwiObj[i].isUsed = TRUE;

            /* Update statistics */
            gBspOsalHwiAllocCnt++;
            if (gBspOsalHwiAllocCnt > gBspOsalHwiPeak)
            {
                gBspOsalHwiPeak = gBspOsalHwiAllocCnt;
            }
            break;
        }
    }
    BspOsal_restoreInterrupt(cookie);

    if (i < BSP_OSAL_CFG_MAX_HWI_OBJECTS)
    {
        Hwi_construct(&(gBspOsalHwiObj[i].hwiStruct),
                      (Int32) intNum,
                      (Hwi_FuncPtr) fxn,
                      &hwiParams,
                      0U);

        hwiHandle = Hwi_handle(&(gBspOsalHwiObj[i].hwiStruct));
    }
    else
    {
        BspOsal_printf("No free BspOsal_HwiObj found\n");
    }
    return hwiHandle;
#else
    return (BspOsal_IntrHandle) Hwi_create(
               (Int32) intNum,
               (Hwi_FuncPtr) fxn,
               &hwiParams,
               0U);
#endif
}

void BspOsal_unRegisterIntr(const BspOsal_IntrHandle *pIntrHandle)
{
#if (BSP_OSAL_CFG_USE_STATIC == TRUE)
    UInt32      i;
    Hwi_Struct *hwiStruct;
    UInt32      cookie;

    hwiStruct = Hwi_struct(*((Hwi_Handle *) pIntrHandle));
    cookie    = BspOsal_disableInterrupt();
    for (i = 0; i < BSP_OSAL_CFG_MAX_HWI_OBJECTS; i++)
    {
        if (gBspOsalHwiObj[i].isUsed != FALSE)
        {
            if ((&gBspOsalHwiObj[i].hwiStruct) == hwiStruct)
            {
                /* Found the bsp osal hwi object to delete */
                if (gBspOsalHwiAllocCnt > 0U)
                {
                    gBspOsalHwiAllocCnt--;
                }
                break;
            }
        }
    }
    BspOsal_restoreInterrupt(cookie);

    if (i < BSP_OSAL_CFG_MAX_HWI_OBJECTS)
    {
        Hwi_destruct(hwiStruct);
        memset(&gBspOsalHwiObj[i], 0, sizeof (BspOsal_HwiObj));
    }
    else
    {
        BspOsal_printf("BspOsal_IntrHandle passed is not in Used state\n");
    }
#else
    Hwi_delete((Hwi_Handle *) pIntrHandle);
#endif
    return;
}

void BspOsal_clearIntr(UInt32 intNum)
{
    Hwi_clearInterrupt(intNum);
    return;
}

UInt32 BspOsal_disableInterrupt(void)
{
    return Hwi_disable();
}

void BspOsal_restoreInterrupt(UInt32 cookie)
{
    Hwi_restore(cookie);
    return;
}

void BspOsal_sleep(UInt32 delayMsec)
{
    #ifdef BUILD_ARP32
    /* ARP32 tick is 10ms */
    Task_sleep((delayMsec + 9U) / 10U);
    #else
    /* For all other cores, tick is 1ms */
    Task_sleep(delayMsec);
    #endif

    return;
}

UInt64 BspOsal_getTimestamp64(void)
{
    UInt64 timestamp;
    Types_Timestamp64 result;

    Timestamp_get64(&result);
    timestamp = (((UInt64) (result.hi) << 32U) | (UInt64) (result.lo));

    return (timestamp);
}

UInt64 BspOsal_getTimestampFreq(void)
{
    UInt64       freq;
    Types_FreqHz result;

    Timestamp_getFreq(&result);
    freq = (((UInt64) (result.hi) << 32U) | (UInt64) (result.lo));

    return (freq);
}

UInt32 BspOsal_getCurTimeInMsec(void)
{
    UInt64 curTimeMsec, curTimeUsec;

    curTimeUsec = BspOsal_getCurTimeInUsec();
    curTimeMsec = (curTimeUsec / 1000U);

    return ((UInt32) curTimeMsec);
}

UInt64 BspOsal_getCurTimeInUsec(void)
{
    static UInt64 cpuMhz = 500U;        /* default */
    static Bool   isInit = FALSE;
    UInt64        cpuHz;
    UInt64        curTs, curTimeUsec;

    if (FALSE == isInit)
    {
        /* do this only once */
        isInit = (Bool) TRUE;
        /* convert to Mhz */
        cpuHz  = BspOsal_getTimestampFreq();
        cpuMhz = (cpuHz / (1000U * 1000U));
    }

    curTs       = BspOsal_getTimestamp64();
    curTimeUsec = (curTs / cpuMhz);

    return (curTimeUsec);
}

Int32 BspOsal_getStaticMemStatus(BspOsal_StaticMemStatus *pMemStat)
{
    Int32  retVal = BSP_SOK;
#if (BSP_OSAL_CFG_USE_STATIC == TRUE)
    UInt32 cookie;

    if (NULL != pMemStat)
    {
        cookie = BspOsal_disableInterrupt();

        pMemStat->peakSemObjs    = gBspOsalSemPeak;
        pMemStat->numMaxSemObjs  = BSP_OSAL_CFG_MAX_SEM_OBJECTS;
        pMemStat->numFreeSemObjs =
            pMemStat->numMaxSemObjs - gBspOsalSemAllocCnt;

        pMemStat->peakTaskObjs    = gBspOsalTaskPeak;
        pMemStat->numMaxTaskObjs  = BSP_OSAL_CFG_MAX_TASK_OBJECTS;
        pMemStat->numFreeTaskObjs =
            pMemStat->numMaxTaskObjs - gBspOsalTaskAllocCnt;

        pMemStat->peakClockObjs    = gBspOsalClockPeak;
        pMemStat->numMaxClockObjs  = BSP_OSAL_CFG_MAX_CLOCK_OBJECTS;
        pMemStat->numFreeClockObjs =
            pMemStat->numMaxClockObjs - gBspOsalClockAllocCnt;

        pMemStat->peakHwiObjs    = gBspOsalHwiPeak;
        pMemStat->numMaxHwiObjs  = BSP_OSAL_CFG_MAX_HWI_OBJECTS;
        pMemStat->numFreeHwiObjs =
            pMemStat->numMaxHwiObjs - gBspOsalHwiAllocCnt;

        BspOsal_restoreInterrupt(cookie);
    }
    else
    {
        retVal = BSP_EFAIL;
    }
#else
    if (NULL != pMemStat)
    {
        memset(pMemStat, 0, sizeof (BspOsal_StaticMemStatus));
    }
    else
    {
        retVal = BSP_EFAIL;
    }
#endif

    return (retVal);
}

void BspOsal_cacheDisable(UInt32 type)
{
    Cache_Type biosCacheType = BspOsal_getBiosCacheType(type);

    Cache_disable(biosCacheType);

    return;
}

void BspOsal_cacheEnable(UInt32 type)
{
    Cache_Type biosCacheType = BspOsal_getBiosCacheType(type);

    Cache_enable(biosCacheType);

    return;
}

void BspOsal_cacheInv(void  *blockPtr,
                      UInt32 byteCnt,
                      UInt32 type,
                      UInt32 timeOut)
{
    Bool       wait          = (Bool) TRUE;
    Cache_Type biosCacheType = BspOsal_getBiosCacheType(type);

    if (BSP_OSAL_NO_WAIT == timeOut)
    {
        wait = (Bool) FALSE;
    }
    Cache_inv(blockPtr, byteCnt, biosCacheType, wait);

    return;
}

void BspOsal_cacheWb(void  *blockPtr,
                     UInt32 byteCnt,
                     UInt32 type,
                     UInt32 timeOut)
{
    Bool       wait          = (Bool) TRUE;
    Cache_Type biosCacheType = BspOsal_getBiosCacheType(type);

    if (BSP_OSAL_NO_WAIT == timeOut)
    {
        wait = (Bool) FALSE;
    }
    Cache_wb(blockPtr, byteCnt, biosCacheType, wait);

    return;
}

void BspOsal_cacheWbAll(void)
{
    Cache_wbAll();

    return;
}

void BspOsal_cacheWbInv(void  *blockPtr,
                        UInt32 byteCnt,
                        UInt32 type,
                        UInt32 timeOut)
{
    Bool       wait          = (Bool) TRUE;
    Cache_Type biosCacheType = BspOsal_getBiosCacheType(type);

    if (BSP_OSAL_NO_WAIT == timeOut)
    {
        wait = (Bool) FALSE;
    }
    Cache_wbInv(blockPtr, byteCnt, biosCacheType, wait);

    return;
}

void BspOsal_cacheWbInvAll(void)
{
    Cache_wbInvAll();

    return;
}

static Cache_Type BspOsal_getBiosCacheType(UInt32 type)
{
    Cache_Type biosCacheType;

    if (BSP_OSAL_CT_L1P == type)
    {
        biosCacheType = Cache_Type_L1P;
    }
    else if (BSP_OSAL_CT_L1D == type)
    {
        biosCacheType = Cache_Type_L1D;
    }
    else if (BSP_OSAL_CT_L1 == type)
    {
        biosCacheType = Cache_Type_L1;
    }
    else if (BSP_OSAL_CT_L2P == type)
    {
        biosCacheType = Cache_Type_L2P;
    }
    else if (BSP_OSAL_CT_L2D == type)
    {
        biosCacheType = Cache_Type_L2D;
    }
    else if (BSP_OSAL_CT_L2 == type)
    {
        biosCacheType = Cache_Type_L2;
    }
    else if (BSP_OSAL_CT_ALLP == type)
    {
        biosCacheType = Cache_Type_ALLP;
    }
    else if (BSP_OSAL_CT_ALLD == type)
    {
        biosCacheType = Cache_Type_ALLD;
    }
    else
    {
        biosCacheType = Cache_Type_ALL;
    }

    return (biosCacheType);
}

