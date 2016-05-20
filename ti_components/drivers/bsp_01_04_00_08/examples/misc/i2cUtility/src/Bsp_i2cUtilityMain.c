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
 *  \file   Bsp_i2cUtilityMain.c
 *
 *  \brief  This file contains the sample code to demonstrate the usage of the
 *          I2C driver implemented for SYS/BIOS.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xdc/std.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <xdc/runtime/System.h>

#include <common/bsp_types.h>
#include <common/trace.h>
#include <common/bsp_config.h>
#include <common/bsp_utils.h>
#include <osal/bsp_osal.h>
#include <platforms/bsp_platform.h>
#include <utility/bsputils_app.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Test application stack size */
#define I2C_APP_TSK_STACK_MAIN          (10U * 1024U)
/* Test application task priority */
#define I2C_APP_TSK_PRI_MAIN            (10U)

#define APP_NAME                        "I2C_UTILITY_APP"

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void I2cApp_createTsk(void);
static void I2cApp_tskMain(UArg arg0, UArg arg1);

extern void start_i2c_utility(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Align stack memory to integer boundary. */
#pragma DATA_ALIGN(gI2cAppTskStackMain, 32)
/* Place the stack in stack section. */
#pragma DATA_SECTION(gI2cAppTskStackMain, ".bss:taskStackSection")
/* Test application stack */
static UInt8 gI2cAppTskStackMain[I2C_APP_TSK_STACK_MAIN];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*
 * Application main
 */
Int32 main(void)
{
    static Char stdin_buf[BUFSIZ];

    /* Provide buffer so that STDIO library will use this memory instead of
     * allocating from system heap, which might lead to false system leak
     * warning */
    setvbuf(stdin, stdin_buf, _IOLBF, BUFSIZ);

    /* Create test task */
    I2cApp_createTsk();

    /* Start BIOS */
    BIOS_start();

    return (0);
}

/*
 * Create test task
 */
static void I2cApp_createTsk(void)
{
    Task_Params tskPrms;
    Task_Handle tskHandle;

    /* Create test task */
    Task_Params_init(&tskPrms);
    tskPrms.priority  = I2C_APP_TSK_PRI_MAIN;
    tskPrms.stack     = gI2cAppTskStackMain;
    tskPrms.stackSize = sizeof (gI2cAppTskStackMain);
    tskHandle         = Task_create(I2cApp_tskMain, &tskPrms, NULL);
    GT_assert(BspAppTrace, (tskHandle != NULL));

    return;
}

/*
 * Test task main
 */
static void I2cApp_tskMain(UArg arg0, UArg arg1)
{
    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": I2C Utility Application - STARTS !!!\n");

    BspUtils_appDefaultSerialInit(TRUE);

    /* Run I2C utility application */
    start_i2c_utility();

    BspUtils_appDefaultSerialDeInit(TRUE);

    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": I2C Utility Application - DONE !!!\n");
    return;
}

