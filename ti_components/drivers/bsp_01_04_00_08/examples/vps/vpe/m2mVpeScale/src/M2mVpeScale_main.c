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
 *  \file M2mVpeScale_main.c
 *
 *  \brief Main file invoking the test function.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "M2mVpeScale_utils.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Test application stack size. */
#define APP_TSK_STACK_SIZE              (10U * 1024U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void App_mainTestTask(void);
extern Task_Handle App_m2mVpeCreateTsk(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Align stack memory to integer boundary. */
#pragma DATA_ALIGN(AppMainTskStack, 32)
/* Place the stack in stack section. */
#pragma DATA_SECTION(AppMainTskStack, ".bss:taskStackSection")
/* Test application stack. */
static UInt8     AppMainTskStack[APP_TSK_STACK_SIZE];

/* Test complete semaphore used to sync between test task and main task. */
Semaphore_Handle AppTestCompleteSem;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  main
 *  Application main function.
 */
Int32 main(void)
{
    Task_Params tskPrms;
    static Char stdin_buf[BUFSIZ];

    /* Provide buffer so that STDIO library will use this memory instead of
     * allocating from system heap, which might lead to false system leak
     * warning */
    setvbuf(stdin, stdin_buf, _IOLBF, BUFSIZ);

    Task_Params_init(&tskPrms);
    tskPrms.stack     = AppMainTskStack;
    tskPrms.stackSize = APP_TSK_STACK_SIZE;
    Task_create((Task_FuncPtr) App_mainTestTask, &tskPrms, NULL);

    BIOS_start();

    return (0);
}

/**
 *  App_mainTestTask
 *  Application test task.
 */
static void App_mainTestTask(void)
{
    UInt32           userInput = 0U, scCnt;
    Int32            retVal = FVID2_SOK;
    UInt32           isI2cInitReq, isI2cDeInitReq;
    Semaphore_Params semPrms;
    Task_Handle      m2mVpeTaskHandle;

    /* Create semaphore */
    Semaphore_Params_init(&semPrms);
    AppTestCompleteSem = Semaphore_create(0, &semPrms, NULL);
    if (NULL == AppTestCompleteSem)
    {
        GT_2trace(BspAppTrace, GT_ERR,
                  "%s: Error @ line %d\n", __FUNCTION__, __LINE__);
        retVal = FVID2_EFAIL;
    }

    if (FVID2_SOK == retVal)
    {
        /* System init */
        isI2cInitReq = isI2cDeInitReq = FALSE;
        retVal       = BspUtils_appDefaultInit(isI2cInitReq);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME "System Init Failed!!!\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
#ifndef TDA2EX_BUILD
        BspUtils_tilerInit();
        BspUtils_tilerDebugLogEnable(FALSE);
#endif  /* #ifndef TDA2EX_BUILD */

        for (scCnt = 0U; scCnt < VPS_M2M_SCALER_ID_MAX; scCnt++)
        {
            BspUtils_appSetVpeLazyLoad(VPS_M2M_INST_VPE1, scCnt, TRUE);
        }

        while (1U)
        {
            /* Create test task */
            m2mVpeTaskHandle = App_m2mVpeCreateTsk();
            if (NULL == m2mVpeTaskHandle)
            {
                GT_2trace(BspAppTrace, GT_ERR,
                          "%s: Error @ line %d\n", __FUNCTION__, __LINE__);
                retVal = BSP_EFAIL;
            }
            if (FVID2_SOK == retVal)
            {
                /* Register the task to the load module for calculating the load
                **/
                BspUtils_prfLoadRegister(m2mVpeTaskHandle, APP_NAME ":");

                /* Wait for test to complete */
                Semaphore_pend(AppTestCompleteSem, BIOS_WAIT_FOREVER);

                /* UnRegister the task from the load module */
                BspUtils_prfLoadUnRegister(m2mVpeTaskHandle);

                /* Delete the task */
                Task_delete(&m2mVpeTaskHandle);

                GT_0trace(
                    BspAppTrace, GT_INFO,
                    "Enter 0 to exit or any other key to continue testing...\n");
                BspOsal_scanf("%d", &userInput);
            }
            if ((0 == userInput) || (retVal != FVID2_SOK))
            {
                break;
            }
        }
    }
    if (FVID2_SOK == retVal)
    {
        for (scCnt = 0U; scCnt < VPS_M2M_SCALER_ID_MAX; scCnt++)
        {
            BspUtils_appSetVpeLazyLoad(VPS_M2M_INST_VPE1, scCnt, FALSE);
        }

#ifndef TDA2EX_BUILD
        BspUtils_tilerDeInit();
#endif  /* #ifndef TDA2EX_BUILD */

        /* System de-init */
        retVal = BspUtils_appDefaultDeInit(isI2cDeInitReq);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME "System De-Init Failed!!!\n");
        }
    }
    if (FVID2_SOK == retVal)
    {
        Semaphore_delete(&AppTestCompleteSem);
        GT_1trace(
            BspAppTrace, GT_INFO,
            APP_NAME
            ": Max stack used for main task (init sequence): %d bytes\n",
            BspOsal_getTaskStackUsage(NULL));
        GT_1trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Max system stack used (ISR): %d bytes\n",
                  BspOsal_getSystemStackUsage());
        BspUtils_appPrintMemStatus();

        GT_0trace(BspAppTrace, GT_INFO, APP_NAME "Test Successfull!!\n");
    }
    return;
}

