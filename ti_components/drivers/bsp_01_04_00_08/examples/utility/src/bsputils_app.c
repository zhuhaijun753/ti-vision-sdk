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
 *  \file bsputils_app.c
 *
 *  \brief This file implements application level generic helper functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>

#include <xdc/std.h>
#include <stdint.h>
#include <hw_types.h>
#include <common/bsp_types.h>
#include <common/trace.h>
#include <common/bsp_config.h>
#include <common/bsp_utils.h>
#include <common/bsp_common.h>
#include <vps/vps_control.h>
#ifdef VPS_DSS_BUILD
#include <vps/vps_displayCtrlDataTypes.h>
#include <vps/vps_displayCtrl.h>
#endif /* #ifdef VPS_DSS_BUILD */
#include <boards/bsp_board.h>
#include <i2c/bsp_i2c.h>
#include <devices/bsp_device.h>
#include <bsputils_app.h>
#include <bsputils_mem.h>
#include <bsputils_prf.h>
#include <soc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  None
 */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Structure to store app objects.
 */
typedef struct BspUtils_AppObj_t
{
    Bool               initDone;
    /**< Initialization done flag. */
    BspOsal_SemHandle  lockSem;
    /**< Semaphore used to protect globals. */

    Bsp_PlatformId     platformId;
    /**< Platform identifier. */
    Bsp_PlatformCpuRev cpuRev;
    /**< CPU version identifier. */
} BspUtils_AppObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  None
 */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief BSP Utils app object used for storing semaphore handle, flags etc. */
static BspUtils_AppObj   gBspUtilsAppObj;

/**
 *  \brief I2C Device Init Params used for storing init Params handle,
 *  Semaphore handle, etc.
 */
static I2c_DevInitParams gI2cDevInitParams[BSP_DEVICE_I2C_INST_ID_MAX];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  BspUtils_appInit
 *  \brief BSP application utils init function.
 */
Int32 BspUtils_appInit(void)
{
    Int32 retVal = BSP_SOK;
    BspUtils_AppObj *appObj = &gBspUtilsAppObj;

    BspUtils_memset(appObj, 0U, sizeof (*appObj));

    /* Get platform type, board and CPU revisions */
    appObj->platformId = Bsp_platformGetId();
    if ((appObj->platformId == BSP_PLATFORM_ID_UNKNOWN) ||
        (appObj->platformId >= BSP_PLATFORM_ID_MAX))
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: Unrecognized platform!!\n");
        retVal = BSP_EFAIL;
    }
    appObj->cpuRev = Bsp_platformGetCpuRev();
    if (appObj->cpuRev >= BSP_PLATFORM_CPU_REV_MAX)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: Unrecognized CPU version!!\n");
        retVal = BSP_EFAIL;
    }

    if (BSP_SOK == retVal)
    {
        appObj->lockSem = BspOsal_semCreate((Int32) 1, FALSE);
        if (NULL == appObj->lockSem)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      "Error: Semaphore create failed!!\n");
            retVal = BSP_EALLOC;
        }
    }

    if (BSP_SOK == retVal)
    {
        appObj->initDone = (Bool) TRUE;
    }

    return (retVal);
}

/**
 *  BspUtils_appDeInit
 *  \brief BSP application utils deinit function.
 */
Int32 BspUtils_appDeInit(void)
{
    Int32 retVal = BSP_SOK;
    BspUtils_AppObj *appObj = &gBspUtilsAppObj;

    if (NULL != appObj->lockSem)
    {
        BspOsal_semDelete(&appObj->lockSem);
        appObj->lockSem = NULL;
    }

    appObj->initDone = (Bool) FALSE;

    return (retVal);
}

/**
 *  BspUtils_appDefaultInit
 *  \brief BSP application utils function to call all the default init
 *  functions.
 */
Int32 BspUtils_appDefaultInit(UInt32 isI2cInitReq)
{
    Int32                   retVal = BSP_SOK;
    UInt32                  instCnt;
    Vps_InitParams          vpsInitPrms;
    Bsp_CommonInitParams    commonInitPrms;
    Bsp_BoardInitParams     boardInitPrms;
    Bsp_PlatformInitParams  platInitPrms;
    Bsp_DeviceInitParams    deviceInitPrms;
    lld_hsi2c_initParam_t   i2cInitParams[BSP_DEVICE_I2C_INST_ID_MAX];
    const Bsp_BoardI2cData *i2cData;
    Bsp_BoardI2cInstData   *i2cInstData;

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

    retVal += Fvid2_init(NULL);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: FVID2 Init failed!!\n");
    }

    VpsInitParams_init(&vpsInitPrms);
    /* Need to use address translation becasue of limited memory of 512MB */
#if defined (TDA3XX_FAMILY_BUILD) || defined (TDA3XX_INTERPOSER_BUILD) || \
    defined (TDA2EX_BUILD)
    vpsInitPrms.isAddrTransReq = TRUE;
    vpsInitPrms.virtBaseAddr   = 0xA0000000U;
    vpsInitPrms.physBaseAddr   = 0x80000000U;
#endif
    retVal += Vps_init(&vpsInitPrms);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: VPS Init failed!!\n");
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
#if defined (TDA3XX_FAMILY_BUILD) || defined (TDA2EX_BUILD)
        deviceInitPrms.isI2cProbingReq = TRUE;
#else
        deviceInitPrms.isI2cProbingReq = FALSE;
#endif
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

    /* Print FVID2 and BSP version string and platform info*/
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    GT_2trace(BspAppTrace, GT_INFO,
              " Build time            : [%s %s]\r\n", __TIME__, __DATE__);
    GT_1trace(BspAppTrace, GT_INFO,
              " FVID2 Version         : [%s]\r\n", Fvid2_getVersionString());
    GT_1trace(BspAppTrace, GT_INFO,
              " BSP Version           : [%s]\r\n", Bsp_getVersionString());
    Bsp_platformPrintInfo();
    Bsp_boardPrintInfo();
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");

    return (retVal);
}

/**
 *  BspUtils_appDefaultDeInit
 *  \brief BSP application utils function to call all the default de-init
 *  functions.
 */
Int32 BspUtils_appDefaultDeInit(UInt32 isI2cDeInitReq)
{
    Int32  retVal = BSP_SOK;
    const Bsp_BoardI2cData *i2cData;
    UInt32 instCnt;

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

    retVal += Vps_deInit(NULL);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: VPS De-Init failed!!\n");
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

/**
 *  BspUtils_appDefaultSerialInit
 *  \brief BSP application utils function to call all the default init
 *  functions related to serial drivers.
 */
Int32 BspUtils_appDefaultSerialInit(UInt32 isI2cInitReq)
{
    Int32  retVal = BSP_SOK;
    UInt32 instCnt;
    Bsp_CommonInitParams    commonInitPrms;
    Bsp_BoardInitParams     boardInitPrms;
    Bsp_PlatformInitParams  platInitPrms;
    Bsp_DeviceInitParams    deviceInitPrms;
    lld_hsi2c_initParam_t   i2cInitParams[BSP_DEVICE_I2C_INST_ID_MAX];
    const Bsp_BoardI2cData *i2cData;
    Bsp_BoardI2cInstData   *i2cInstData;

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
#if defined (TDA3XX_FAMILY_BUILD) || defined (TDA2EX_BUILD)
        deviceInitPrms.isI2cProbingReq = TRUE;
#else
        deviceInitPrms.isI2cProbingReq = FALSE;
#endif
        retVal += Bsp_deviceInit(&deviceInitPrms);
        if (BSP_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR, "Error: Device Init failed!!\n");
        }
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

    /* Print FVID2 and BSP version string and platform info*/
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    GT_2trace(BspAppTrace, GT_INFO,
              " Build time            : [%s %s]\r\n", __TIME__, __DATE__);
    GT_1trace(BspAppTrace, GT_INFO,
              " FVID2 Version         : [%s]\r\n", Fvid2_getVersionString());
    GT_1trace(BspAppTrace, GT_INFO,
              " BSP Version           : [%s]\r\n", Bsp_getVersionString());
    Bsp_platformPrintInfo();
    Bsp_boardPrintInfo();
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");

    return (retVal);
}

/**
 *  BspUtils_appDefaultSerialDeInit
 *  \brief BSP application utils function to call all the default de-init
 *  functions related to serial drivers.
 */
Int32 BspUtils_appDefaultSerialDeInit(UInt32 isI2cDeInitReq)
{
    Int32  retVal = BSP_SOK;
    const Bsp_BoardI2cData *i2cData;
    UInt32 instCnt;

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

void BspUtils_appPrintMemStatus(void)
{
    BspOsal_StaticMemStatus memStat;

    BspOsal_getStaticMemStatus(&memStat);

    GT_0trace(BspAppTrace, GT_INFO, " \n");
    GT_0trace(BspAppTrace, GT_INFO, "BSP OSAL Memory Usage\n");
    GT_0trace(BspAppTrace, GT_INFO, "---------------------\n");

    GT_1trace(BspAppTrace, GT_INFO,
        "Peak OSAL Semaphore Objects : %d\n", memStat.peakSemObjs);
    GT_1trace(BspAppTrace, GT_INFO,
        "Max  OSAL Semaphore Objects : %d\n", memStat.numMaxSemObjs);
    GT_1trace(BspAppTrace, GT_INFO,
        "Free OSAL Semaphore Objects : %d\n", memStat.numFreeSemObjs);

    GT_1trace(BspAppTrace, GT_INFO,
        "Peak OSAL Task      Objects : %d\n", memStat.peakTaskObjs);
    GT_1trace(BspAppTrace, GT_INFO,
        "Max  OSAL Task      Objects : %d\n", memStat.numMaxTaskObjs);
    GT_1trace(BspAppTrace, GT_INFO,
        "Free OSAL Task      Objects : %d\n", memStat.numFreeTaskObjs);

    GT_1trace(BspAppTrace, GT_INFO,
        "Peak OSAL Clock     Objects : %d\n", memStat.peakClockObjs);
    GT_1trace(BspAppTrace, GT_INFO,
        "Max  OSAL Clock     Objects : %d\n", memStat.numMaxClockObjs);
    GT_1trace(BspAppTrace, GT_INFO,
        "Free OSAL Clock     Objects : %d\n", memStat.numFreeClockObjs);

    GT_1trace(BspAppTrace, GT_INFO,
        "Peak OSAL HWI       Objects : %d\n", memStat.peakHwiObjs);
    GT_1trace(BspAppTrace, GT_INFO,
        "Max  OSAL HWI       Objects : %d\n", memStat.numMaxHwiObjs);
    GT_1trace(BspAppTrace, GT_INFO,
        "Free OSAL HWI       Objects : %d\n", memStat.numFreeHwiObjs);

    /* Check for memory leaks */
    if (memStat.numFreeSemObjs != memStat.numMaxSemObjs)
    {
        GT_0trace(BspAppTrace, GT_INFO,
            "Warning: Not all SEM Objects are freed!!\n");
    }
    if (memStat.numFreeTaskObjs != memStat.numMaxTaskObjs)
    {
        GT_0trace(BspAppTrace, GT_INFO,
            "Warning: Not all TSK Objects are freed!!\n");
    }
    if (memStat.numFreeClockObjs != memStat.numMaxClockObjs)
    {
        GT_0trace(BspAppTrace, GT_INFO,
            "Warning: Not all CLK Objects are freed!!\n");
    }
    if (memStat.numFreeHwiObjs != memStat.numMaxHwiObjs)
    {
        GT_0trace(BspAppTrace, GT_INFO,
            "Warning: Not all HWI Objects are freed!!\n");
    }

    GT_0trace(BspAppTrace, GT_INFO, " \n");

    return;
}

/*
 *  \brief Function to print the loadRaw command used to load buffers from file
 *  through CCS scripting console.
 *
 *  \param fileStr          [IN]    File name string.
 *  \param bufAddr          [IN]    Buffer address.
 *  \param dataFormat       [IN]    FVID2 Data format.
 *  \param width            [IN]    Width of buffer in pixels.
 *  \param height           [IN]    Height of buffer in lines.
 */
void BspUtils_appPrintLoadRawCmd(const Char *fileStr,
                                 const void *bufAddr,
                                 UInt32      dataFormat,
                                 UInt32      width,
                                 UInt32      height)
{
    Char *fmtName;

    if (FVID2_DF_YUV422I_YUYV == dataFormat)
    {
        fmtName = "yuyv422";
    }
    else if (FVID2_DF_YUV422I_YVYU == dataFormat)
    {
        fmtName = "yvyu422";
    }
    else if (FVID2_DF_YUV422I_UYVY == dataFormat)
    {
        fmtName = "uyvy422";
    }
    else if (FVID2_DF_YUV422I_VYUY == dataFormat)
    {
        fmtName = "vyuy422";
    }
    else if (FVID2_DF_YUV420SP_UV == dataFormat)
    {
        fmtName = "nv12";
    }
    else if (FVID2_DF_YUV420SP_VU == dataFormat)
    {
        fmtName = "nv21";
    }
    else if (FVID2_DF_YUV422SP_UV == dataFormat)
    {
        fmtName = "nv16";
    }
    else if (FVID2_DF_YUV422SP_VU == dataFormat)
    {
        fmtName = "yuv422spvu";
    }
    else if (FVID2_DF_YUV444I == dataFormat)
    {
        fmtName = "yuv444";
    }
    else if (FVID2_DF_RGB24_888 == dataFormat)
    {
        fmtName = "rgb888";
    }
    else if (FVID2_DF_BGR24_888 == dataFormat)
    {
        fmtName = "bgr888";
    }
    else if (FVID2_DF_RAW16 == dataFormat)
    {
        fmtName = "raw16";
    }
    else if (FVID2_DF_RAW08 == dataFormat)
    {
        fmtName = "raw8";
    }
    else if (FVID2_DF_ARGB32_8888 == dataFormat)
    {
        fmtName = "argb8888";
    }
    else
    {
        fmtName = "unknownformat";
    }

    GT_5trace(
        BspAppTrace, GT_INFO,
        "loadRaw(0x%.8x, 0, \"C:\\\\%s_%s_prog_packed_%d_%d.tigf\", "
        "32, false);\n",
        bufAddr, fileStr, fmtName, width, height);

    return;
}

/**
 *  \brief Function to print the saveRaw command used to save buffers to file
 *  through CCS scripting console.
 */
void BspUtils_appPrintSaveRawCmd(const Char *fileStr,
                                 const void *bufAddr,
                                 UInt32      dataFormat,
                                 UInt32      width,
                                 UInt32      height,
                                 UInt32      bufSize)
{
    Char *fmtName;

    if (FVID2_DF_YUV422I_YUYV == dataFormat)
    {
        fmtName = "yuyv422";
    }
    else if (FVID2_DF_YUV422I_YVYU == dataFormat)
    {
        fmtName = "yvyu422";
    }
    else if (FVID2_DF_YUV422I_UYVY == dataFormat)
    {
        fmtName = "uyvy422";
    }
    else if (FVID2_DF_YUV422I_VYUY == dataFormat)
    {
        fmtName = "vyuy422";
    }
    else if (FVID2_DF_YUV420SP_UV == dataFormat)
    {
        fmtName = "nv12";
    }
    else if (FVID2_DF_YUV420SP_VU == dataFormat)
    {
        fmtName = "nv21";
    }
    else if (FVID2_DF_YUV422SP_UV == dataFormat)
    {
        fmtName = "nv16";
    }
    else if (FVID2_DF_YUV422SP_VU == dataFormat)
    {
        fmtName = "yuv422spvu";
    }
    else if (FVID2_DF_YUV444I == dataFormat)
    {
        fmtName = "yuv444";
    }
    else if (FVID2_DF_RGB24_888 == dataFormat)
    {
        fmtName = "rgb888";
    }
    else if (FVID2_DF_BGR24_888 == dataFormat)
    {
        fmtName = "bgr888";
    }
    else if (FVID2_DF_RAW16 == dataFormat)
    {
        fmtName = "raw16";
    }
    else if (FVID2_DF_RAW08 == dataFormat)
    {
        fmtName = "raw8";
    }
    else if (FVID2_DF_ARGB32_8888 == dataFormat)
    {
        fmtName = "argb8888";
    }
    else
    {
        fmtName = "unknownformat";
    }

    GT_6trace(
        BspAppTrace, GT_INFO,
        "saveRaw(0, 0x%.8x, \"D:\\\\%s_%s_prog_packed_%d_%d.tigf\", %d, "
        "32, false);\n",
        bufAddr, fileStr, fmtName, width, height, (bufSize / 4U));

    return;
}

#if (defined (VPS_VIP_BUILD) || defined (VPS_ISS_BUILD))

/**
 *  \brief Prints the capture instance status information by calling the
 *  driver get status IOCTL.
 */
void BspUtils_appPrintCaptStatus(Fvid2_Handle fvidHandle,
                                 UInt32       instId,
                                 UInt32       numStream,
                                 UInt32       numCh,
                                 UInt32       execTime)
{
    Int32                retVal;
    UInt32               streamId, chId;
    Vps_CaptStatus       captStat;
    Vps_CaptChStatusArgs chStatArgs;
    Vps_CaptChStatus     chStat;
    static Char          buf[300];

    retVal = Fvid2_control(
        fvidHandle,
        IOCTL_VPS_CAPT_GET_STATUS,
        &captStat,
        NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  "Capture Inst Status: Error: Get capture status failed!!\n");
    }
    else
    {
        GT_1trace(BspAppTrace, GT_INFO,
                  " Capture Instance %d Statistics\r\n", instId);
        GT_0trace(BspAppTrace, GT_INFO,
                  " ==============================\r\n");
        GT_2trace(BspAppTrace, GT_INFO,
                  " Capture Inst %d Status: Number of request queued  : %d\n",
                  instId,
                  captStat.queueCount);
        GT_2trace(BspAppTrace, GT_INFO,
                  " Capture Inst %d Status: Number of request dequeued: %d\n",
                  instId,
                  captStat.dequeueCount);
        GT_2trace(BspAppTrace, GT_INFO,
                  " Capture Inst %d Status: Overflow Count            : %d\r\n",
                  instId,
                  captStat.overflowCount);
        GT_0trace(BspAppTrace, GT_INFO, " \r\n");

        GT_0trace(
            BspAppTrace, GT_INFO,
            "    CH    |     Q      DQ     Total   Top     Bot    Total  Top    "
            "Bot   Min/Max     Min/Max   Dropped  Repeat   Fid   Desc \r\n");
        GT_0trace(
            BspAppTrace, GT_INFO,
            " (I/S/CH) |   Count   Count  Fields  Fields  Fields   FPS   FPS    "
            "FPS    Width       Height   Frames   Frames  Repeat Error\r\n");
        GT_0trace(
            BspAppTrace, GT_INFO,
            " ------------------------------------------------------------------"
            "---------------------------------------------------------\r\n");

        VpsCaptChStatusArgs_init(&chStatArgs);
        for (streamId = 0U; streamId < numStream; streamId++)
        {
            for (chId = 0U; chId < numCh; chId++)
            {
                chStatArgs.chNum =
                    Vps_captMakeChNum(instId, streamId, chId);
                chStatArgs.frameInterval = 33;

                retVal = Fvid2_control(
                    fvidHandle,
                    IOCTL_VPS_CAPT_GET_CH_STATUS,
                    &chStatArgs,
                    &chStat);
                if (FVID2_SOK != retVal)
                {
                    GT_0trace(BspAppTrace, GT_ERR,
                              "Get channel status failed!!\n");
                    break;
                }
                else
                {
                    snprintf(buf, sizeof (buf),
                             " %0.2d.%d.%0.2d | %7d %7d %7d %7d %7d %6d %5d "
                             "%5d %5d/%-5d %5d/%-5d %7d %7d %7d %5d\r\n",
                             instId,
                             streamId,
                             chId,
                             chStat.queueCount,
                             chStat.dequeueCount,
                             chStat.captFrmCount,
                             chStat.fldCount[FVID2_FID_TOP],
                             chStat.fldCount[FVID2_FID_BOTTOM],
                             chStat.captFrmCount / (execTime / 1000U),
                             chStat.fldCount[FVID2_FID_TOP] / (execTime / 1000U),
                             chStat.fldCount[FVID2_FID_BOTTOM] /
                             (execTime / 1000U),
                             chStat.minRecvFrmWidth,
                             chStat.maxRecvFrmWidth,
                             chStat.minRecvFrmHeight,
                             chStat.maxRecvFrmHeight,
                             chStat.droppedFrmCount,
                             chStat.repeatFrmCount,
                             chStat.fidRepeatCount,
                             chStat.descErrCount);

                    GT_1trace(BspAppTrace, GT_INFO, " %s\r\n", buf);
                }
            }
            if (FVID2_SOK != retVal)
            {
                break;
            }
        }
    }
}

#endif  /* #ifdef VPS_VIP_BUILD */

#ifdef VPS_VPE_BUILD
/**
 *  BspUtils_appAllocDeiCtxBuffer
 *  \brief Allocate context buffer according to the VPE driver need and
 *  provide it to the driver.
 */
Int32 BspUtils_appAllocDeiCtxBuffer(Fvid2_Handle fvidHandle, UInt32 numCh)
{
    Int32          retVal = FVID2_SOK;
    Vps_DeiCtxInfo deiCtxInfo;
    Vps_DeiCtxBuf  deiCtxBuf;
    UInt32         chCnt, bCnt;

    for (chCnt = 0U; chCnt < numCh; chCnt++)
    {
        /* Get the number of buffers to allocate */
        deiCtxInfo.chNum = chCnt;
        retVal           = Fvid2_control(
            fvidHandle,
            IOCTL_VPS_GET_DEI_CTX_INFO,
            &deiCtxInfo,
            NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      "Error: Get DEI Context Info IOCTL failed!!\n");
        }
        /* Allocate the buffers as requested by the driver */
        if (FVID2_SOK == retVal)
        {
            for (bCnt = 0U; bCnt < deiCtxInfo.numFld; bCnt++)
            {
                deiCtxBuf.fldBuf[bCnt] = (void *) BspUtils_memAlloc(
                    deiCtxInfo.fldBufSize,
                    (UInt32) VPS_BUFFER_ALIGNMENT_RECOMMENDED);
                if (NULL == deiCtxBuf.fldBuf[bCnt])
                {
                    GT_0trace(BspAppTrace, GT_ERR,
                              "Error: Mem alloc failed!!\n");
                    retVal = FVID2_EALLOC;
                }
            }
        }
        if (FVID2_SOK == retVal)
        {
            for (bCnt = 0U; bCnt < deiCtxInfo.numMv; bCnt++)
            {
                deiCtxBuf.mvBuf[bCnt] = (void *) BspUtils_memAlloc(
                    deiCtxInfo.mvBufSize,
                    (UInt32) VPS_BUFFER_ALIGNMENT_RECOMMENDED);
                if (NULL == deiCtxBuf.mvBuf[bCnt])
                {
                    GT_0trace(BspAppTrace, GT_ERR,
                              "Error: Mem alloc failed!!\n");
                    retVal = FVID2_EALLOC;
                }
            }
        }
        if (FVID2_SOK == retVal)
        {
            for (bCnt = 0U; bCnt < deiCtxInfo.numMvstm; bCnt++)
            {
                deiCtxBuf.mvstmBuf[bCnt] = (void *) BspUtils_memAlloc(
                    deiCtxInfo.mvstmBufSize,
                    (UInt32) VPS_BUFFER_ALIGNMENT_RECOMMENDED);
                if (NULL == deiCtxBuf.mvstmBuf[bCnt])
                {
                    GT_0trace(BspAppTrace, GT_ERR,
                              "Error: Mem alloc failed!!\n");
                    retVal = FVID2_EALLOC;
                }
            }
        }
        if (FVID2_SOK == retVal)
        {
            /* Provided the allocated buffer to driver */
            deiCtxBuf.chNum = chCnt;
            retVal          = Fvid2_control(
                fvidHandle,
                IOCTL_VPS_SET_DEI_CTX_BUF,
                &deiCtxBuf,
                NULL);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          "Error: Set DEI Context Buffer IOCTL failed!!\n");
            }
        }
        if (FVID2_SOK != retVal)
        {
            break;
        }
    }

    return (retVal);
}

/**
 *  BspUtils_appFreeDeiCtxBuffer
 *  \brief Get the context buffers back from the VPE driver and free them.
 */
Int32 BspUtils_appFreeDeiCtxBuffer(Fvid2_Handle fvidHandle, UInt32 numCh)
{
    Int32          retVal = FVID2_SOK;
    Vps_DeiCtxInfo deiCtxInfo;
    Vps_DeiCtxBuf  deiCtxBuf;
    UInt32         chCnt, bCnt;

    for (chCnt = 0U; chCnt < numCh; chCnt++)
    {
        /* Get the number of buffers to allocate */
        deiCtxInfo.chNum = chCnt;
        retVal           = Fvid2_control(
            fvidHandle,
            IOCTL_VPS_GET_DEI_CTX_INFO,
            &deiCtxInfo,
            NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      "Error: Get DEI Context Info IOCTL failed!!\n");
        }
        else
        {
            /* Get the allocated buffer back from the driver */
            deiCtxBuf.chNum = chCnt;
            retVal          = Fvid2_control(
                fvidHandle,
                IOCTL_VPS_GET_DEI_CTX_BUF,
                &deiCtxBuf,
                NULL);

            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          "Error: Get DEI Context Buffer IOCTL failed!!\n");
            }
            else
            {
                /* Free the buffers */
                for (bCnt = 0U; bCnt < deiCtxInfo.numFld; bCnt++)
                {
                    BspUtils_memFree(deiCtxBuf.fldBuf[bCnt],
                                     deiCtxInfo.fldBufSize);
                }
                for (bCnt = 0U; bCnt < deiCtxInfo.numMv; bCnt++)
                {
                    BspUtils_memFree(deiCtxBuf.mvBuf[bCnt],
                                     deiCtxInfo.mvBufSize);
                }
                for (bCnt = 0U; bCnt < deiCtxInfo.numMvstm; bCnt++)
                {
                    BspUtils_memFree(deiCtxBuf.mvstmBuf[bCnt],
                                     deiCtxInfo.mvstmBufSize);
                }
            }
        }
        if (FVID2_SOK != retVal)
        {
            break;
        }
    }

    return (retVal);
}

/**
 *  BspUtils_appPrintM2mVpeCreateStatus
 *  \brief Prints the M2M VPE driver create status information.
 */
void BspUtils_appPrintM2mVpeCreateStatus(
    const Vps_M2mCreateStatus *createStatus)
{
    GT_1trace(BspAppTrace, GT_INFO,
              "M2M VPE Create Status: Maximum Handles                  : %d\n",
              createStatus->maxHandles);
    GT_1trace(BspAppTrace, GT_INFO,
              "M2M VPE Create Status: Maximum Channels per Handle      : %d\n",
              createStatus->maxChPerHandle);
    GT_1trace(BspAppTrace, GT_INFO,
              "M2M VPE Create Status: Maximum same Channels per Request: %d\n",
              createStatus->maxSameChPerRequest);

    return;
}

/**
 *  BspUtils_appSetVpeLazyLoad
 *  \brief Sets the VPE lazy loading parameters through the VPS control driver.
 */
Int32 BspUtils_appSetVpeLazyLoad(UInt32 vpeInstId,
                                 UInt32 scalerId,
                                 Bool   lazyLoadingEnable)
{
    Int32        retVal     = FVID2_SOK;
    Fvid2_Handle fvidHandle = NULL;
    Vps_ScLazyLoadingParams lazyPrms;

    fvidHandle = Fvid2_create(
        (UInt32) FVID2_VPS_CTRL_DRV,
        VPS_CTRL_INST_0,
        NULL,
        NULL,
        NULL);
    if (NULL == fvidHandle)
    {
        GT_2trace(BspAppTrace, GT_ERR,
                  "%s: Error @ line %d\n", __FUNCTION__, __LINE__);
        retVal = FVID2_EFAIL;
    }

    if (FVID2_SOK == retVal)
    {
        VpsScLazyLoadingParams_init(&lazyPrms);
        lazyPrms.vpeInstId         = vpeInstId;
        lazyPrms.scalerId          = scalerId;
        lazyPrms.lazyLoadingEnable = (UInt32) lazyLoadingEnable;

        /* Set the lazy load params */
        retVal = Fvid2_control(
            fvidHandle,
            IOCTL_VPS_CTRL_SET_VPE_LAZY_LOADING,
            &lazyPrms,
            NULL);
        if (FVID2_SOK != retVal)
        {
            GT_2trace(BspAppTrace, GT_ERR,
                      "%s: Error @ line %d\n", __FUNCTION__, __LINE__);
        }
    }

    if (NULL != fvidHandle)
    {
        retVal = Fvid2_delete(fvidHandle, NULL);
        if (FVID2_SOK != retVal)
        {
            GT_2trace(BspAppTrace, GT_ERR,
                      "%s: Error @ line %d\n", __FUNCTION__, __LINE__);
        }
    }

    return (retVal);
}

#endif  /* #ifdef VPS_VPE_BUILD */

#ifdef VPS_DSS_BUILD

/**
 *  \brief Prints the display instance status information by calling the
 *  driver get status IOCTL.
 *
 *  \param fvidHandle   [IN] Valid display driver handle.
 *  \param instId       [IN] Instance ID used for print.
 *  \param execTime     [IN] Execution time from display start to display
 *                           stop in msec.
 *
 */
void BspUtils_appPrintDispStatus(Fvid2_Handle fvidHandle,
                                 UInt32       instId,
                                 UInt32       execTime)
{
    Int32          retVal;
    Vps_DispStatus dispStat;

    retVal = Fvid2_control(
        fvidHandle,
        IOCTL_VPS_DISP_GET_STATUS,
        &dispStat,
        NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  "Display Inst Status: Error: Get display status failed!!\n");
    }
    else
    {
        GT_1trace(BspAppTrace, GT_INFO,
                  " Display Instance %d Statistics\r\n", instId);
        GT_0trace(BspAppTrace, GT_INFO,
                  " ==============================\r\n");
        GT_2trace(BspAppTrace, GT_INFO,
                  " Display Inst %d Status: Number of request queued  : %d\n",
                  instId,
                  dispStat.queueCount);
        GT_2trace(BspAppTrace, GT_INFO,
                  " Display Inst %d Status: Number of request dequeued: %d\n",
                  instId,
                  dispStat.dequeueCount);
        GT_2trace(BspAppTrace, GT_INFO,
                  " Display Inst %d Status: Displayed frame count     : %d\r\n",
                  instId,
                  dispStat.dispFrmCount);
        GT_2trace(BspAppTrace, GT_INFO,
                  " Display Inst %d Status: Frame repeat count        : %d\r\n",
                  instId,
                  dispStat.repeatFrmCount);
        GT_2trace(BspAppTrace, GT_INFO,
                  " Display Inst %d Status: Underflow count           : %d\r\n",
                  instId,
                  dispStat.underflowCount);
        GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    }
    return;
}

void BspUtils_appPrintDctrlStatus(Fvid2_Handle fvidHandle)
{
    Int32 retVal;
    Vps_DctrlErrorSyncLostStats dctrlStat;

    retVal = Fvid2_control(
        fvidHandle,
        IOCTL_VPS_DCTRL_GET_ERROR_STATS,
        &dctrlStat,
        NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(
            BspAppTrace, GT_ERR,
            "Display Ctrl Error Status: Error: Get display control status failed!!\n");
    }
    else
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  " Dispaly Controller Error Status \r\n");
        GT_0trace(BspAppTrace, GT_INFO,
                  " ==============================\r\n");
        GT_1trace(BspAppTrace, GT_INFO,
                  " LCD1 SyncLost count          : %d\r\n",
                  dctrlStat.syncLost1);
#ifdef TDA2XX_FAMILY_BUILD
        GT_1trace(BspAppTrace, GT_INFO,
                  " LCD2 SyncLost2 count         : %d\r\n",
                  dctrlStat.syncLost2);
        GT_1trace(BspAppTrace, GT_INFO,
                  " LCD3 SyncLost3 count         : %d\r\n",
                  dctrlStat.syncLost3);
        GT_1trace(BspAppTrace, GT_INFO,
                  " TV SyncLost count            : %d\r\n",
                  dctrlStat.syncLostTV);
#endif
        GT_1trace(BspAppTrace, GT_INFO,
                  " OCP Error count              : %d\r\n",
                  dctrlStat.ocpError);
        GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    }
}

/**
 *  \brief Prints the display driver create status information.
 *
 *  \param createStatus [IN] Pointer to display driver create status.
 */
void BspUtils_appPrintDispCreateStatus(const Vps_DispCreateStatus *createStatus)
{
    GT_3trace(
        BspAppTrace, GT_INFO,
        "Display Create Status: VENC Standard: %s, Width: %d, Height: %d\n",
        Fvid2_getStandardString(createStatus->standard),
        createStatus->dispWidth, createStatus->dispHeight);
    GT_1trace(BspAppTrace, GT_INFO,
              "Display Create Status: Minimum Number of Buffers to Prime: %d\n",
              createStatus->minNumPrimeBuf);

    return;
}

#endif  /* #ifdef VPS_DSS_BUILD */
