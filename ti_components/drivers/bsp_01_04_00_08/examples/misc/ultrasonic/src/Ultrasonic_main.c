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
 *  \file Ultrasonic_main.c
 *
 *  \brief Main file invoking the ultrasonic test function.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <xdc/std.h>
#include <stdio.h>
#include <string.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/heaps/HeapMem.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>

#include <common/bsp_types.h>
#include <common/trace.h>
#include <common/bsp_config.h>
#include <common/bsp_utils.h>
#include <common/bsp_common.h>
#include <platforms/bsp_platform.h>
#include <fvid2/fvid2.h>
#include <vps/vps.h>
#include <i2c/bsp_i2c.h>
#include <devices/bsp_device.h>
#include <devices/bsp_pga450.h>
#include <boards/bsp_board.h>
#include <uart/bsp_uart.h>
#include <utility/bsputils_mem.h>
#include <utility/bsputils_prf.h>
#include <utility/bsputils_app.h>
#include <hw/hw_types.h>
#include <hw/hw_ctrl_wkup.h>
#include <hw/hw_ctrl_core_pad_io.h>
#include <hw/hw_wkupaon_cm.h>
#include <soc.h>
#include <soc_defines.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Test application stack size. */
#define APP_TSK_STACK_SIZE              (10U * 1024U)
#define PRCM_ENABLE                     ((UInt32) 2U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void App_mainTestTask(void);
static void App_testSensor(void);

static Int32 App_uartDefaultInit(UInt32 isI2cInitReq);
static Int32 App_uartDefaultDeInit(UInt32 isI2cDeInitReq);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Align stack memory to integer boundary. */
#pragma DATA_ALIGN(AppMainTskStack, 32)
/* Place the stack in stack section. */
#pragma DATA_SECTION(AppMainTskStack, ".bss:taskStackSection")
/* Test application stack. */
static UInt8 AppMainTskStack[APP_TSK_STACK_SIZE];

/**
 *  \brief I2C Device Init Params used for storing init Params handle,
 *  Semaphore handle, etc.
 */
static I2c_DevInitParams gI2cDevInitParams[BSP_DEVICE_I2C_INST_ID_MAX];

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
    Int32 retVal;

    /* System init */
    retVal = App_uartDefaultInit(TRUE);
    if (retVal != BSP_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR, "System Init Failed!!!\n");
        return;
    }

    /* Invoke sensor test */
    App_testSensor();

    /* System de-init */
    retVal = App_uartDefaultDeInit(TRUE);
    if (retVal != BSP_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR, "System De-Init Failed!!!\n");
        return;
    }

    GT_0trace(BspAppTrace, GT_INFO, "Test Application Complete!!\n");

    return;
}

static void App_testSensor(void)
{
    Int32  isDetected, distMeasured;
    UInt32 uartInstId;
    UInt8  deviceId;

    uartInstId = BSP_DEVICE_UART_INST_ID_9;

    /* Detect all devices connected to the UART */
    System_printf("\r\nProbing all sensors connected to UART\n");
    System_printf("-------------------------------------\n");
    for (deviceId = 1U; deviceId < BSP_PGA450_MAX_DEVICE; deviceId++)
    {
        isDetected = Bsp_pga450ProbeDevice(uartInstId, deviceId);
        if (TRUE == isDetected)
        {
            System_printf(
                "UART %d: Detected Sensor %d\r\n",
                uartInstId, deviceId);
        }
    }
    System_printf(" \r\n");

    /* Measure short distance to all the sensors detected */
    System_printf("\r\nMeasuring short distance\n");
    System_printf("------------------------\n");
    for (deviceId = 1U; deviceId < BSP_PGA450_MAX_DEVICE; deviceId++)
    {
        isDetected = Bsp_pga450ProbeDevice(uartInstId, deviceId);
        if (TRUE == isDetected)
        {
            distMeasured = Bsp_pga450GetMeasurement(
                uartInstId,
                deviceId,
                BSP_PGA450_DISTANCE_MODE_SHORT);
            if (distMeasured >= 0)
            {
                System_printf(
                    "Sensor %d Short Distance: %d cm\r\n",
                    deviceId, distMeasured);
            }
            else
            {
                System_printf(
                    "Sensor %d Short Distance Measuremenet Failed!!\r\n",
                    deviceId);
            }
        }
    }
    System_printf(" \r\n");

    /* Measure long distance to all the sensors detected */
    System_printf("\r\nMeasuring long distance\n");
    System_printf("-----------------------\n");
    for (deviceId = 1U; deviceId < BSP_PGA450_MAX_DEVICE; deviceId++)
    {
        isDetected = Bsp_pga450ProbeDevice(uartInstId, deviceId);
        if (TRUE == isDetected)
        {
            distMeasured = Bsp_pga450GetMeasurement(
                uartInstId,
                deviceId,
                BSP_PGA450_DISTANCE_MODE_LONG);
            if (distMeasured >= 0)
            {
                System_printf(
                    "Sensor %d Long Distance: %d cm\r\n",
                    deviceId, distMeasured);
            }
            else
            {
                System_printf(
                    "Sensor %d Long Distance Measuremenet Failed!!\r\n",
                    deviceId);
            }
        }
    }
    System_printf(" \r\n");

    return;
}

/**
 *  App_uartDefaultInit
 *  \brief Application utils function to call all the default init functions.
 */
static Int32 App_uartDefaultInit(UInt32 isI2cInitReq)
{
    Int32                   retVal = BSP_SOK;
    UInt32                  instCnt;
    Bsp_CommonInitParams    commonInitPrms;
    Bsp_BoardInitParams     boardInitPrms;
    Bsp_PlatformInitParams  platInitPrms;
    Bsp_DeviceInitParams    deviceInitPrms;
    lld_hsi2c_initParam_t   i2cInitParams[BSP_DEVICE_I2C_INST_ID_MAX];
    const Bsp_BoardI2cData *i2cData;
    Bsp_BoardI2cInstData   *i2cInstData;
    Error_Block             eb;
    Bsp_Pga450InitParams    pga450InitParams;

    Error_init(&eb);

    Uart_init();

    BspCommonInitParams_init(&commonInitPrms);
    retVal += Bsp_commonInit(&commonInitPrms);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: BSP Common Init failed!!\n");
    }

    BspBoardInitParams_init(&boardInitPrms);
    /* Override board detection if I2C is disabled */
    if (((Bool) TRUE) != ((Bool) isI2cInitReq))
    {
        boardInitPrms.boardId      = BSP_BOARD_UNKNOWN;
        boardInitPrms.baseBoardRev = BSP_BOARD_REV_UNKNOWN;
        boardInitPrms.dcBoardRev   = BSP_BOARD_REV_UNKNOWN;
    }
    retVal += Bsp_boardInit(&boardInitPrms);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: Board Init failed!!\n");
    }

    BspPlatformInitParams_init(&platInitPrms);
    retVal += Bsp_platformInit(&platInitPrms);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: Platform Init failed!!\n");
    }

    /* Set the pin Mux */
    Bsp_boardSetPinMux(BSP_DRV_ID_UART, BSP_DEVICE_UART_INST_ID_9,
                       BSP_BOARD_MODE_DEFAULT);

    /* Enable UART10 module */
    HW_WR_REG32(
        SOC_WKUPAON_CM_BASE + CM_WKUPAON_UART10_CLKCTRL, PRCM_ENABLE);
    while ((HW_RD_REG32(SOC_WKUPAON_CM_BASE +
                        CM_WKUPAON_UART10_CLKCTRL) & ((UInt32) (0x00030000)))
           != 0x0)
    {
        /* Do nothing - Busy wait */
    }

    retVal += Fvid2_init(NULL);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: FVID2 Init failed!!\n");
    }

    /* Override I2C init for non-EVM builds */
    if (BSP_PLATFORM_ID_EVM != Bsp_platformGetId())
    {
        isI2cInitReq = FALSE;
    }

    if (((Bool) TRUE) == ((Bool) isI2cInitReq))
    {
        i2cData = Bsp_boardGetI2cData();
        GT_assert(BspAppTrace, (NULL != i2cData));
        GT_assert(BspAppTrace,
                  (i2cData->numInst <= BSP_DEVICE_I2C_INST_ID_MAX));
        GT_assert(BspAppTrace, (NULL != i2cData->instData));

        for (instCnt = 0U; instCnt < i2cData->numInst; instCnt++)
        {
            i2cInstData = &i2cData->instData[instCnt];
            GT_assert(BspAppTrace,
                      (i2cInstData->instId < BSP_DEVICE_I2C_INST_ID_MAX));
            i2cInitParams[instCnt].opMode       = HSI2C_OPMODE_INTERRUPT;
            i2cInitParams[instCnt].isMasterMode = TRUE;
            i2cInitParams[instCnt].is10BitAddr  = FALSE;
            i2cInitParams[instCnt].i2cBusFreq   =
                (lld_i2c_busspeed) i2cInstData->busClkKHz;
            i2cInitParams[instCnt].i2cIntNum      = i2cInstData->intNum;
            i2cInitParams[instCnt].i2cOwnAddr     = 0xCC;
            gI2cDevInitParams[instCnt].initParams = &i2cInitParams[instCnt];
            gI2cDevInitParams[instCnt].hsi2c_sem  =
                BspOsal_semCreate((Int32) 1, (Bool) TRUE);
            gI2cDevInitParams[instCnt].instId = i2cInstData->instId;
        }

        if (i2cData->numInst > 0)
        {
            retVal = I2c_GlobalInit(i2cData->numInst, &gI2cDevInitParams[0U]);
            if (BSP_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR, "Error: I2C Init failed!!\n");
            }
        }

        BspDeviceInitParams_init(&deviceInitPrms);
        deviceInitPrms.isI2cProbingReq = FALSE;
        retVal += Bsp_deviceInit(&deviceInitPrms);
        if (BSP_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR, "Error: Device Init failed!!\n");
        }
    }

    retVal += BspUtils_memInit();
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: App MEM Utils Init failed!!\n");
    }

    retVal += BspUtils_prfInit();
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: App PRF Utils Init failed!!\n");
    }

    retVal += BspUtils_appInit();
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: App Utils Init failed!!\n");
    }

    BspPga450InitParams_init(&pga450InitParams);
    retVal += Bsp_pga450Init(&pga450InitParams);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: PGA450 Init failed!!\n");
    }

    /* Print BSP version string and platform info*/
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    GT_2trace(BspAppTrace, GT_INFO,
              " Build time            : [%s %s]\r\n", __TIME__, __DATE__);
    GT_1trace(BspAppTrace, GT_INFO,
              " BSP Version           : [%s]\r\n", Bsp_getVersionString());
    Bsp_platformPrintInfo();
    Bsp_boardPrintInfo();
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");

    return (retVal);
}

/**
 *  App_uartDefaultDeInit
 *  \brief Application utils function to call all the default de-init
 *  functions.
 */
static Int32 App_uartDefaultDeInit(UInt32 isI2cDeInitReq)
{
    Int32  retVal = BSP_SOK;
    const Bsp_BoardI2cData *i2cData;
    UInt32 instCnt;

    retVal += Bsp_pga450DeInit();
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: PGA450 De-Init failed!!\n");
    }

    retVal += BspUtils_appDeInit();
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: App Utils De-Init failed!!\n");
    }

    retVal += BspUtils_prfDeInit();
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  "Error: App PRF Utils De-Init failed!!\n");
    }

    retVal += BspUtils_memDeInit();
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  "Error: App MEM Utils De-Init failed!!\n");
    }

    /* Override I2C de-init for non-EVM builds */
    if (BSP_PLATFORM_ID_EVM != Bsp_platformGetId())
    {
        isI2cDeInitReq = FALSE;
    }

    if (((Bool) TRUE) == ((Bool) isI2cDeInitReq))
    {
        i2cData = Bsp_boardGetI2cData();
        GT_assert(BspAppTrace, (NULL != i2cData));
        GT_assert(BspAppTrace,
                  (i2cData->numInst <= BSP_DEVICE_I2C_INST_ID_MAX));

        retVal += Bsp_deviceDeInit(NULL);
        if (BSP_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR, "Error: Device De-Init failed!!\n");
        }
        if (i2cData->numInst > 0)
        {
            for (instCnt = 0U; instCnt < i2cData->numInst; instCnt++)
            {
                BspOsal_semDelete(&(gI2cDevInitParams[instCnt].hsi2c_sem));
            }
            retVal += I2c_GlobalDeInit(NULL);
            if (BSP_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR, "Error: I2C De-Init failed!!\n");
            }
        }
    }

    retVal += Fvid2_deInit(NULL);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: FVID2 De-Init failed!!\n");
    }

    retVal += Bsp_platformDeInit(NULL);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  "Error: BSP Platform De-Init failed!!\n");
    }

    retVal += Bsp_boardDeInit(NULL);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: BSP Board De-Init failed!!\n");
    }

    retVal += Bsp_commonDeInit(NULL);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: BSP Common De-Init failed!!\n");
    }

    return (retVal);
}

