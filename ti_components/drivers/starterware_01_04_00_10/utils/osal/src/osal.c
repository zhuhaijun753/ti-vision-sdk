/* =================================================================
 *   Copyright (C) 2013 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and
 *    conditionsstipulated in the agreement under which this program
 *     has been supplied.
 * =================================================================*/
#include <stdint.h>
#include <stdio.h>  /* Required to handle variable argument list */
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>

#include <osal/bsp_osal.h>
#include <common/bsp_types.h>

#ifdef SYSBIOS
    #include <ti/sysbios/BIOS.h>
    #include <ti/sysbios/hal/Hwi.h>
    #include <ti/sysbios/knl/Task.h>
    #include <ti/sysbios/knl/Semaphore.h>
#else
    #include <interrupt.h>
#endif

/**
 *  \file osal.c
 *
 *  \brief Implement the OSAL layer required for starterware.
 *
 */

UInt32 BspOsal_disableInterrupt(void)
{
#ifdef SYSBIOS
    return Hwi_disable();
#else
    return (UInt32) Intc_IntDisable();
#endif
}

void BspOsal_restoreInterrupt(UInt32 cookie)
{
#ifdef SYSBIOS
    Hwi_restore(cookie);
#else
    Intc_IntEnable((UInt8) cookie);
#endif
}

void BspOsal_clearIntr(UInt32 intNum)
{
#ifdef SYSBIOS
    Hwi_clearInterrupt(intNum);
#endif
}

BspOsal_IntrHandle BspOsal_registerIntr(
    UInt32              intNum,
    BspOsal_IntrFuncPtr fxn,
    void               *arg0)
{
#ifdef SYSBIOS
    Hwi_Params hwiParams = {0};

    Hwi_Params_init(&hwiParams);
    hwiParams.arg = (UInt32) arg0;
    return (BspOsal_IntrHandle) Hwi_create(
               intNum,
               (Hwi_FuncPtr) fxn,
               &hwiParams,
               0U);
#else
    UInt32     retVal = intNum;

    Intc_IntRegister((UInt16) intNum, (IntrFuncPtr) fxn, (void *) arg0);

    Intc_SystemEnable((UInt16) intNum);
    return (BspOsal_IntrHandle) retVal;
#endif
}

void BspOsal_unRegisterIntr(const BspOsal_IntrHandle *pIntrHandle)
{
#ifdef SYSBIOS
    Hwi_delete((Hwi_Handle *) pIntrHandle);
#else
    UInt32 intNum = (UInt32) * pIntrHandle;
    Intc_SystemEnable((UInt16) intNum);
    Intc_IntUnregister((UInt16) intNum);
#endif
}

BspOsal_SemHandle BspOsal_semCreate(Int32 initValue, Bool isBinary)
{
#ifdef SYSBIOS
    Semaphore_Params semParams;

    Semaphore_Params_init(&semParams);
    semParams.mode = Semaphore_Mode_COUNTING;
    if (isBinary)
    {
        semParams.mode = Semaphore_Mode_BINARY;
    }
    return (BspOsal_SemHandle) Semaphore_create(initValue, &semParams, NULL);
#else
    /* Semaphores not supported in these mode */
    return (BspOsal_SemHandle) 1;
#endif
}

void BspOsal_semDelete(BspOsal_SemHandle *pSemHandle)
{
#ifdef SYSBIOS
    Semaphore_delete((Semaphore_Handle *) pSemHandle);
#else
    /* Semaphores not supported in these mode */
#endif
}

Bool BspOsal_semWait(BspOsal_SemHandle semHandle, UInt32 timeOut)
{
#ifdef SYSBIOS
    if (timeOut == BSP_OSAL_WAIT_FOREVER)
    {
        timeOut = BIOS_WAIT_FOREVER;
    }
    if (timeOut == BSP_OSAL_NO_WAIT)
    {
        timeOut = BIOS_NO_WAIT;
    }
    return Semaphore_pend((Semaphore_Handle) semHandle, timeOut);
#else
    /* Semaphores not supported in these mode */
    return TRUE;
#endif
}

void BspOsal_semPost(BspOsal_SemHandle semHandle)
{
#ifdef SYSBIOS
    Semaphore_post((Semaphore_Handle) semHandle);
#else
    /* Semaphores not supported in these mode */
#endif
}

void BspOsal_sleep(UInt32 delayMsec)
{
#ifdef SYSBIOS
    Task_sleep(delayMsec);
#else
    volatile UInt32 a = delayMsec * 100U;
    while (a--)
    {
        /* delay */
    }
#endif
}

UInt32 BspOsal_getClockTicks(void) {
    return 0U;
}

Int32 BspOsal_printf(const Char *format, ...)
{
#if (defined (BUILD_A15)) || (defined (BUILD_A8))
    Int32   retVal = BSP_SOK;
#else
    va_list vaArgPtr;
    Int32   retVal = BSP_SOK;
    Int32   val;
    /*UInt32  cookie;*/

    va_start(vaArgPtr, format);
    val = va_arg(vaArgPtr, Int32);
    va_end(vaArgPtr);

    printf(format, val);
#endif
    return (retVal);
}

UInt64 BspOsal_getTimestamp64(void)
{
    return (0U);
}

UInt64 BspOsal_getTimestampFreq(void)
{
    return (1U);
}

UInt32 BspOsal_getCurTimeInMsec(void)
{
    return (0U);
}

UInt64 BspOsal_getCurTimeInUsec(void)
{
    return (0U);
}

