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
 *  \file CaptureIss_main.c
 *
 *  \brief ISS Capture demo application - Receives via CSI2/Parallel and
 *          write to memory
 *         Most board / EVM specifics are handled in function
 *          appCaptcreateVidSensor () In addition to configuring the sensor
 *          for the given config and enable sensor to stream.
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "CaptureIss_main.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**< CSI2 PHY Clock OV10640
 *      For a 15X15 Package TDA3MAx(15x15), TDA3LAx(15x15), TDA3LRx(15x15). */
#define APP_CAPT_ISS_CAL_OV10640_PHY_CLK_MHz (400U)

/**< CSI2 PHY Clock IMX224 */
#define APP_CAPT_ISS_CAL_IMX224_PHY_CLK_MHz (150U)

/**< CSI2 PHY Clock for UB960 with 4 TIDA00262 modules */
#define APP_CAPT_ISS_CAL_UB960_PHY_CLK_MHz (800U)
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void appCaptCreateTask(void);
static void appCaptTask(UArg arg0, UArg arg1);
static void appCaptInit(appCaptObj_t *appObj);
static void appCaptDeInit(appCaptObj_t *appObj);
static void appCapture4GivenConfig(appCaptObj_t *appObj, appCaptCfg_t *pCfg);
static void appCaptDeriveCfg(appCaptObj_t *appObj, appCaptCfg_t *pCfg);
static Int32 appCaptCreateDrv(appCaptObj_t *appObj);
static Int32 appCaptDeleteDrv(appCaptObj_t *appObj);
static Int32 appCaptSetDrvCfg(appCaptObj_t *appObj, appCaptCfg_t *pCfg);
static Int32 appCaptAllocAndQFrames(appCaptObj_t *appObj);
static Int32 appCaptFreeFrames(appCaptObj_t *appObj);
static void appCaptCountQ(appCaptObj_t *appObj, Fvid2_FrameList *frmList,
                          UInt32 streamId);
static void appCaptCountDQ(appCaptObj_t *appObj, Fvid2_FrameList *frmList,
                           UInt32 streamId);
static void appCaptChkDQCounts(appCaptObj_t *appObj);
static Int32 appCaptGetTestId(appCaptObj_t *appObj);
static Int32 appCaptcreateVidSensor(appCaptObj_t *instObj, appCaptCfg_t *pCfg);
static void appCaptPrintStatistics(appCaptObj_t *appObj,
                                   UInt32        execTimeInMsecs);
static Int32 appCaptDeleteVidSensor(appCaptObj_t *instObj, appCaptCfg_t *pCfg);
static void appCaptErrCb(const UInt32 *event, UInt32 numEvents, Ptr arg);
static Int32 appCaptEnableErrorReporting(appCaptObj_t *appObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**< Align stack memory to integer boundary. */
#pragma DATA_ALIGN(gCaptAppTskStackMain, 32)
/**< Place the stack in stack section. */
#pragma DATA_SECTION(gCaptAppTskStackMain, ".bss:taskStackSection")
/**< Demo application stack */
static UInt8 gCaptAppTskStackMain[CAPT_APP_TSK_STACK_MAIN];

/**< demo application object */
appCaptObj_t gCaptAppObj;

/**< Different capture options supported by this demo */
appCaptCfg_t gTestCfg[] = {
    {"OV10640 CSI2 4Lanes capture on ISS",                        0U,
     TRUE,
     FVID2_VIFM_SCH_CSI2,
     FVID2_VIFW_4LANES, 1U, 0U, VPS_ISS_CAL_CSI2_RAW12, FVID2_BPP_BITS12,
     CAPT_APP_RUN_COUNT, 1280U, 720U, (1280U * 2U),
     FVID2_VID_SENSOR_OV10640_CSI2_DRV,
     FVID2_STD_720P_60, FVID2_DF_BAYER_BGGR, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_DEFAULT},

    {"IMX224 CSI2 4Lanes capture on ISS",                         0U,
     TRUE,
     FVID2_VIFM_SCH_CSI2,
     FVID2_VIFW_4LANES, 1U, 0U, VPS_ISS_CAL_CSI2_RAW12, FVID2_BPP_BITS12,
     CAPT_APP_RUN_COUNT, 1312U, 2164U, (1312U * 2U),
     FVID2_VID_SENSOR_SONY_IMX224_CSI2_DRV,
     FVID2_STD_720P_60, FVID2_DF_BAYER_BGGR, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_DEFAULT},

    {"APT AR0132 Sensor Parallel capture on ISS",                 1U,
     TRUE,
     FVID2_VIFM_SCH_CPI,
     FVID2_VIFW_12BIT, 1U, 0U, VPS_ISS_CAL_CSI2_ANY, FVID2_BPP_BITS12,
     CAPT_APP_RUN_COUNT, 1280U, 720U, (1280U * 2U),
     FVID2_VID_SENSOR_APT_AR0132_DRV,
     FVID2_STD_720P_60, FVID2_DF_BAYER_GRBG, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_VIDEO_16BIT},

    {"APT AR0140 1280x720 Sensor Parallel capture on ISS",        1U,
     TRUE,
     FVID2_VIFM_SCH_CPI,
     FVID2_VIFW_12BIT, 1U, 0U, VPS_ISS_CAL_CSI2_ANY, FVID2_BPP_BITS12,
     CAPT_APP_RUN_COUNT, 1280U, 720U, (1280U * 2U),
     FVID2_VID_SENSOR_APT_AR0140_DRV,
     FVID2_STD_720P_60, FVID2_DF_BAYER_GRBG, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_VIDEO_16BIT},

    {"APT AR0140 1280x800 Sensor Parallel capture on ISS",        1U,
     TRUE,
     FVID2_VIFM_SCH_CPI,
     FVID2_VIFW_12BIT, 1U, 0U, VPS_ISS_CAL_CSI2_ANY, FVID2_BPP_BITS12,
     CAPT_APP_RUN_COUNT, 1280U, 800U, (1280U * 2U),
     FVID2_VID_SENSOR_APT_AR0140_DRV,
     FVID2_STD_WXGA_30, FVID2_DF_BAYER_GRBG, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_VIDEO_16BIT},

    {"Omnivision OV10640 Sensor Parallel capture on ISS over LI", 1U,
     TRUE,
     FVID2_VIFM_SCH_CPI,
     FVID2_VIFW_12BIT, 1U, 0U, VPS_ISS_CAL_CSI2_ANY, FVID2_BPP_BITS12,
     CAPT_APP_RUN_COUNT, 1280U, 720U, (1280U * 2U),
     FVID2_VID_SENSOR_OV10640_CPI_DRV,
     FVID2_STD_720P_60, FVID2_DF_BAYER_BGGR, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_VIDEO_16BIT},

    {"UB960 & TIDA00262 CSI2 4 channel capture",                  0U,
     TRUE,
     FVID2_VIFM_SCH_CSI2,
     FVID2_VIFW_4LANES, 4U, 0U, VPS_ISS_CAL_CSI2_RAW12, FVID2_BPP_BITS12,
     CAPT_APP_RUN_COUNT, 1280U, 720U, (1280U * 2U),
     FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV,
     FVID2_STD_WXGA_30, FVID2_DF_BAYER_GRBG, FVID2_BPP_BITS12,
     BSP_BOARD_MODE_DEFAULT},
};

/**< Number of options supported */
#define APP_CAPT_NUM_OPTS              (sizeof (gTestCfg) / \
                                        sizeof (gTestCfg[0U]))

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
    appCaptCreateTask();

    /* Start BIOS */
    BIOS_start();

    return (0);
}

/*
 * Create test task
 */
static void appCaptCreateTask(void)
{
    Task_Params tskPrms;

    BspUtils_memset(&gCaptAppObj, 0x0, sizeof (appCaptObj_t));
    /* Create test task */
    Task_Params_init(&tskPrms);
    tskPrms.priority      = CAPT_APP_TSK_PRI_MAIN;
    tskPrms.stack         = gCaptAppTskStackMain;
    tskPrms.stackSize     = sizeof (gCaptAppTskStackMain);
    tskPrms.arg0          = (UArg) & gCaptAppObj;
    gCaptAppObj.tskHandle = Task_create(appCaptTask, &tskPrms, NULL);
    GT_assert(BspAppTrace, (gCaptAppObj.tskHandle != NULL));

    /* Register the task to the load module for calculating the load */
    BspUtils_prfLoadRegister(gCaptAppObj.tskHandle, APP_NAME);

    return;
}

/*
 * Test task main
 */
static void appCaptTask(UArg arg0, UArg arg1)
{
    BspUtils_MemHeapStatus startHeapStat1;
    appCaptObj_t          *appObj = (appCaptObj_t *) arg0;
    UInt32 testId;

    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": Sample Application - STARTS !!!\n");
    appCaptInit(appObj);

    while (1U)
    {
        /* Get the TestId */
        testId = appCaptGetTestId(appObj);
        if (testId < APP_CAPT_NUM_OPTS)
        {
            BspUtils_memGetHeapStat(&startHeapStat1);

            appCapture4GivenConfig(
                appObj,
                &gTestCfg[testId]);

            BspUtils_memCheckHeapStat(&startHeapStat1);
        }
        else
        {
            /* Exit */
            break;
        }
    }

    appCaptDeInit(appObj);

    GT_1trace(BspAppTrace, GT_INFO,
              APP_NAME ": Max BSS Memory used for test task: %d bytes\n",
              appObj->captIssAppMaxBSSMemHeapUS);
    GT_1trace(BspAppTrace, GT_INFO,
              APP_NAME ": Max stack used for test task: %d bytes\n",
              BspOsal_getTaskStackUsage(NULL));
    GT_1trace(BspAppTrace, GT_INFO,
              APP_NAME ": Max system stack used (ISR): %d bytes\n",
              BspOsal_getSystemStackUsage());
    BspUtils_appPrintMemStatus();

    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": Sample Application - DONE !!!\n");
    return;
}

static void appCaptInit(appCaptObj_t *appObj)
{
    Int32  retVal;
    UInt32 isI2cInitReq;

    appObj->captIssAppMaxBSSMemHeapUS = 0;

    /* System init */
    isI2cInitReq = TRUE;
    retVal       = BspUtils_appDefaultInit(isI2cInitReq);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": System Init Failed!!!\n");
    }

    if (FVID2_SOK == retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": VPS Initialized\n");
    }

    return;
}

static void appCaptDeInit(appCaptObj_t *appObj)
{
    Int32  retVal;
    UInt32 isI2cDeInitReq;

    appObj->captIssAppMaxBSSMemHeapUS = 0;

    /* System de-init */
    isI2cDeInitReq = TRUE;
    retVal         = BspUtils_appDefaultDeInit(isI2cDeInitReq);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": System De-Init Failed!!!\n");
    }

    if (retVal == FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": VPS De Initialized\n");
    }
    return;
}

/**
 *  appCapture4GivenConfig
 *  Capture test function.
 */
static void appCapture4GivenConfig(appCaptObj_t *appObj, appCaptCfg_t *pCfg)
{
    Int32           retVal = FVID2_SOK;
    UInt32          startTime, endTime;
    volatile UInt32 lastFrameNo = 0;

    /* Print test case information */
    GT_1trace(BspAppTrace, GT_INFO,
              APP_NAME ": Configured to capture %d frames \n",
              pCfg->numFrames);
    BspUtils_memcpy(&appObj->testPrms, pCfg, sizeof (appCaptCfg_t));

    appObj->instId = VPS_CAPT_INST_ISS_CAL_A;

    /* Make config required for open */
    appCaptDeriveCfg(appObj, pCfg);

    retVal = appCaptCreateDrv(appObj);
    if (FVID2_SOK != retVal)
    {
        return;
    }

    retVal = appCaptSetDrvCfg(appObj, pCfg);
    if (FVID2_SOK != retVal)
    {
        return;
    }

    retVal = appCaptEnableErrorReporting(appObj);
    if (FVID2_SOK != retVal)
    {
        return;
    }

    retVal = appCaptAllocAndQFrames(appObj);
    if (FVID2_SOK != retVal)
    {
        return;
    }

    retVal = appCaptcreateVidSensor(appObj, pCfg);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Failed to configure the sensor!!!\n");
        return;
    }

    appObj->rcvedFramesCount = 0x0;
    appObj->frameWithCrcErrorCnt = 0x0;
    appObj->frameWithWarning = 0x0;
    appObj->frameErrorCnt = 0x0;
    appObj->sofIntCount = 0x0;
    appObj->unExpectedIntCnt = 0x0;
    appObj->crcErrIntCnt = 0x0;
    lastFrameNo = 0x0U;

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": Starting Capture now...\n");

    startTime = BspOsal_getCurTimeInMsec();
    retVal    = Fvid2_start(appObj->drvHandle, NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Capture Start Failed!!!\n");
        return;
    }

    /* Wait for reception completion */
    while (appObj->rcvedFramesCount <
           (appObj->numFramesToCapture * pCfg->numStreams))
    {
        if ((0U == lastFrameNo) && (appObj->rcvedFramesCount))
        {
            lastFrameNo = appObj->rcvedFramesCount;
            GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": Stream Detected!!!\n");
        }
    }

    retVal = Fvid2_stop(appObj->drvHandle, NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Capture Stop Failed!!!\n");
        return;
    }
    endTime = BspOsal_getCurTimeInMsec();

    appCaptPrintStatistics(appObj, endTime - startTime);

    retVal = appCaptFreeFrames(appObj);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Capture Stop Failed!!!\n");
        return;
    }

    appCaptChkDQCounts(appObj);

    retVal = appCaptDeleteDrv(appObj);
    if (FVID2_SOK != retVal)
    {
        return;
    }

    retVal = appCaptDeleteVidSensor(appObj, pCfg);

    return;
}

/**
 *  appCaptCb
 *  \brief Driver callback function.
 */
static Int32 appCaptCb(Fvid2_Handle handle, Ptr appData, Ptr reserved)
{
    Int32  retVal = FVID2_SOK;
    UInt32 streamId, frmIdx;
    static Fvid2_FrameList frmList;
    Fvid2_Frame *pFrm;
    appCaptObj_t *appObj = (appCaptObj_t *) appData;
    GT_assert(BspAppTrace, appData != NULL);

    for (streamId = 0U; streamId < appObj->numStream; streamId++)
    {
        retVal = Fvid2_dequeue(
            appObj->drvHandle,
            &frmList,
            streamId,
            FVID2_TIMEOUT_NONE);
        if (FVID2_SOK == retVal)
        {
            for (frmIdx = 0; frmIdx < frmList.numFrames; frmIdx++)
            {
                pFrm = frmList.frames[frmIdx];
                if (FVID2_FRAME_STATUS_COMPLETED != pFrm->status)
                {
                    switch (pFrm->status)
                    {
                        case FVID2_FRAME_STATUS_CRC_ERROR:
                            appObj->frameWithCrcErrorCnt++;
                        break;

                        case FVID2_FRAME_STATUS_ECC_CORRECTED:
                            appObj->frameWithWarning++;
                        break;

                        case FVID2_FRAME_STATUS_OVERFLOW:
                        case FVID2_FRAME_STATUS_ECC_ERROR:
                            appObj->frameErrorCnt++;
                        break;
                        default:
                            appObj->frameErrorCnt++;
                        break;
                    }
                }
            }

            appCaptCountDQ(appObj, &frmList, streamId);
            appCaptCountQ(appObj, &frmList, streamId);

            retVal = Fvid2_queue(appObj->drvHandle, &frmList, streamId);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Capture Queue Failed!!!\n");
            }
        }
        appObj->rcvedFramesCount += frmList.numFrames;
        appObj->totalFrmCount    += frmList.numFrames;
    }
    return FVID2_SOK;
}

/**
 *  appCaptDeriveCfg
 *  Initialize the global variables and frame pointers.
 */
static void appCaptDeriveCfg(appCaptObj_t *appObj, appCaptCfg_t *pCfg)
{
    UInt32 streamId;
    Vps_CaptCreateParams  *createPrms;
    vpsissCalCmplxIoCfg_t *pCmplxIoCfg;

    appObj->maxWidth      = 1920U;
    appObj->maxHeight     = 1080U;
    appObj->totalFrmCount = 0U;
    appObj->totalCpuLoad  = 0U;
    appObj->cpuLoadCount  = 0U;

    appObj->instId    = VPS_CAPT_INST_ISS_CAL_A;
    appObj->drvHandle = NULL;
    Fvid2CbParams_init(&appObj->cbPrms);
    appObj->cbPrms.cbFxn   = &appCaptCb;
    appObj->cbPrms.appData = appObj;

    appObj->numStream = pCfg->numStreams;

    createPrms = &appObj->createPrms;
    VpsCaptCreateParams_init(&appObj->createPrms);
    createPrms->videoIfMode     = pCfg->interfaceType;
    createPrms->videoIfWidth    = pCfg->interfacewidth;
    createPrms->bufCaptMode     = VPS_CAPT_BCM_LAST_FRM_REPEAT;
    createPrms->numCh           = 1U;
    createPrms->numStream       = appObj->numStream;
    createPrms->pAdditionalArgs = &appObj->issOpenPrms;

    if (FVID2_VID_SENSOR_OV10640_CSI2_DRV == pCfg->sensorDrvId)
    {
        appObj->issOpenPrms.csi2PhyClock =
            APP_CAPT_ISS_CAL_OV10640_PHY_CLK_MHz;
    }
    else if (FVID2_VID_SENSOR_SONY_IMX224_CSI2_DRV == pCfg->sensorDrvId)
    {
        appObj->issOpenPrms.csi2PhyClock =
            APP_CAPT_ISS_CAL_IMX224_PHY_CLK_MHz;
    }
    else if (FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV == pCfg->sensorDrvId)
    {
        appObj->issOpenPrms.csi2PhyClock =
            APP_CAPT_ISS_CAL_UB960_PHY_CLK_MHz;
    }
    else
    {
        appObj->issOpenPrms.csi2PhyClock = APP_CAPT_ISS_CAL_OV10640_PHY_CLK_MHz;
    }

    if (FVID2_VIFM_SCH_CPI == pCfg->interfaceType)
    {
        appObj->issOpenPrms.subModules[0U] =
            (VPS_ISS_CAPT_CAL_SUB_CPORT_ID |
             VPS_ISS_CAPT_CAL_SUB_DMA_WR_ID |
             VPS_ISS_CAPT_CAL_SUB_DPCM_ENC_ID |
             VPS_ISS_CAPT_CAL_SUB_PIX_PACK_ID |
             VPS_ISS_CAPT_CAL_SUB_BYS_IN_ID);
    }
    else
    {
        appObj->issOpenPrms.subModules[0U] =
            (VPS_ISS_CAPT_CAL_SUB_PPI_ID |
             VPS_ISS_CAPT_CAL_SUB_CSI2_ID |
             VPS_ISS_CAPT_CAL_SUB_CPORT_ID |
             VPS_ISS_CAPT_CAL_SUB_DMA_WR_ID |
             VPS_ISS_CAPT_CAL_SUB_PIX_EXTRACT_ID |
             VPS_ISS_CAPT_CAL_SUB_DPCM_DEC_ID |
             VPS_ISS_CAPT_CAL_SUB_DPCM_ENC_ID |
             VPS_ISS_CAPT_CAL_SUB_PIX_PACK_ID);
    }

    if (FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV == pCfg->sensorDrvId)
    {
        appObj->issOpenPrms.subModules[1U] =
            (
                VPS_ISS_CAPT_CAL_SUB_CSI2_ID |
                VPS_ISS_CAPT_CAL_SUB_CPORT_ID |
                VPS_ISS_CAPT_CAL_SUB_DMA_WR_ID |
                VPS_ISS_CAPT_CAL_SUB_PIX_EXTRACT_ID |
                VPS_ISS_CAPT_CAL_SUB_DPCM_DEC_ID |
                VPS_ISS_CAPT_CAL_SUB_DPCM_ENC_ID |
                VPS_ISS_CAPT_CAL_SUB_PIX_PACK_ID);
        appObj->issOpenPrms.subModules[2U] =
            (
                VPS_ISS_CAPT_CAL_SUB_CSI2_ID |
                VPS_ISS_CAPT_CAL_SUB_CPORT_ID |
                VPS_ISS_CAPT_CAL_SUB_DMA_WR_ID |
                VPS_ISS_CAPT_CAL_SUB_PIX_EXTRACT_ID |
                VPS_ISS_CAPT_CAL_SUB_DPCM_DEC_ID |
                VPS_ISS_CAPT_CAL_SUB_DPCM_ENC_ID |
                VPS_ISS_CAPT_CAL_SUB_PIX_PACK_ID);
        appObj->issOpenPrms.subModules[3U] =
            (
                VPS_ISS_CAPT_CAL_SUB_CSI2_ID |
                VPS_ISS_CAPT_CAL_SUB_CPORT_ID |
                VPS_ISS_CAPT_CAL_SUB_DMA_WR_ID |
                VPS_ISS_CAPT_CAL_SUB_PIX_EXTRACT_ID |
                VPS_ISS_CAPT_CAL_SUB_DPCM_DEC_ID |
                VPS_ISS_CAPT_CAL_SUB_DPCM_ENC_ID |
                VPS_ISS_CAPT_CAL_SUB_PIX_PACK_ID);
    }

    appObj->issOpenPrms.isCmplxIoCfgValid = TRUE;
    pCmplxIoCfg                = &appObj->issOpenPrms.cmplxIoCfg[0U];
    pCmplxIoCfg->enable        = TRUE;
    pCmplxIoCfg->clockLane.pol = FALSE;

    pCmplxIoCfg->clockLane.pol      = FALSE;
    pCmplxIoCfg->clockLane.position = 2U;
    pCmplxIoCfg->data1Lane.pol      = FALSE;
    pCmplxIoCfg->data1Lane.position = 1U;
    pCmplxIoCfg->data2Lane.pol      = FALSE;
    pCmplxIoCfg->data2Lane.position = 3U;
    pCmplxIoCfg->data3Lane.pol      = FALSE;
    pCmplxIoCfg->data3Lane.position = 4U;
    pCmplxIoCfg->data4Lane.pol      = FALSE;
    pCmplxIoCfg->data4Lane.position = 5U;

    if (FVID2_VIFW_3LANES == pCfg->interfacewidth)
    {
        pCmplxIoCfg->data4Lane.position = 0U;
    }
    if (FVID2_VIFW_2LANES == pCfg->interfacewidth)
    {
        pCmplxIoCfg->data3Lane.position = 0U;
        pCmplxIoCfg->data4Lane.position = 0U;
    }
    if (FVID2_VIFW_1LANES == pCfg->interfacewidth)
    {
        pCmplxIoCfg->data2Lane.position = 0U;
        pCmplxIoCfg->data3Lane.position = 0U;
        pCmplxIoCfg->data4Lane.position = 0U;
    }
    if (FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV == pCfg->sensorDrvId)
    {
        pCmplxIoCfg->clockLane.pol      = FALSE;
        pCmplxIoCfg->clockLane.position = 1U;
        pCmplxIoCfg->data1Lane.pol      = FALSE;
        pCmplxIoCfg->data1Lane.position = 2U;
    }

    for (streamId = 0U; streamId < appObj->numStream; streamId++)
    {
        createPrms->chNumMap[streamId][0U] =
            Vps_captMakeChNum(appObj->instId, streamId, 0U);
    }

    return;
}

static Int32 appCaptCreateDrv(appCaptObj_t *appObj)
{
    Int32 retVal = FVID2_SOK;

    appObj->drvHandle = Fvid2_create(
        FVID2_VPS_CAPT_VID_DRV,
        appObj->instId,
        &appObj->createPrms,
        &appObj->createStatus,
        &appObj->cbPrms);
    if ((NULL == appObj->drvHandle) ||
        (appObj->createStatus.retVal != FVID2_SOK))
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Capture Create Failed!!!\n");
        retVal = appObj->createStatus.retVal;
    }

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": ISS Capture created\n");

    return (retVal);
}

static Int32 appCaptDeleteDrv(appCaptObj_t *appObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 streamId;
    static Fvid2_FrameList frmList;

    for (streamId = 0U;
         streamId < appObj->createPrms.numStream;
         streamId++)
    {
        /* Dequeue all the request from the driver */
        while (1U)
        {
            retVal = Fvid2_dequeue(
                appObj->drvHandle,
                &frmList,
                streamId,
                FVID2_TIMEOUT_NONE);
            if (FVID2_SOK != retVal)
            {
                break;
            }
            else
            {
                appCaptCountDQ(appObj, &frmList, streamId);
            }
        }
    }
    retVal = Fvid2_delete(appObj->drvHandle, NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Capture Delete Failed!!!\n");
    }
    else
    {
        appObj->drvHandle = NULL;
    }

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": Capture Driver deleted\n");

    return (retVal);
}

static Int32 appCaptSetDrvCfg(appCaptObj_t *appObj, appCaptCfg_t *pCfg)
{
    UInt32 i;
    Int32  retVal = FVID2_SOK;
    appObj->numFramesToCapture = pCfg->numFrames;
    appObj->cfg.numStream      = pCfg->numStreams;
    for (i = 0; i < pCfg->numStreams; i++)
    {
        appObj->cfg.streamId[i] = i;

        appObj->cfg.inFmt[i].width  = pCfg->width;
        appObj->cfg.inFmt[i].height = pCfg->height;

        appObj->cfg.inFmt[i].pitch[0]   = pCfg->pitch;
        appObj->cfg.inFmt[i].bpp        = pCfg->inBpp;
        appObj->cfg.inFmt[i].dataFormat = 0x0U;
        appObj->cfg.csi2DataFormat[i]   = pCfg->inCsi2DataFormat;
        if (0 == i)
        {
            appObj->cfg.csi2VirtualChanNo[i] = pCfg->virtualChannel;
        }
        else if (1 == i)
        {
            appObj->cfg.csi2VirtualChanNo[i] = 1U;
        }
        else if (2 == i)
        {
            appObj->cfg.csi2VirtualChanNo[i] = 2U;
        }
        else
        {
            appObj->cfg.csi2VirtualChanNo[i] = 3U;
        }
        appObj->cfg.streamType[i] = VPS_ISS_CAL_TAG_PIX_DATA;

        appObj->cfg.isPixProcCfgValid[i] = FALSE;
        appObj->cfg.isBysOutCfgValid[i]  = FALSE;

        if (FVID2_VIFM_SCH_CPI == pCfg->interfaceType)
        {
            appObj->cfg.bysInEnable[0] = TRUE;
        }
        else
        {
            appObj->cfg.bysInEnable[i] = FALSE;
        }
        appObj->cfg.isVportCfgValid[i] = FALSE;

        appObj->cfg.writeToMem[i] = TRUE;

        /* Some how, simulator requiers an 16 bit writes */
        if (((VPS_ISS_CAL_CSI2_RAW12 == pCfg->inCsi2DataFormat) ||
             (VPS_ISS_CAL_CSI2_RAW14 == pCfg->inCsi2DataFormat)) ||
            (VPS_ISS_CAL_CSI2_RAW10 == pCfg->inCsi2DataFormat))
        {
            appObj->cfg.pixProcCfg[i].extract = VPS_ISS_CAL_PIX_EXRCT_B14_MIPI;
            if (VPS_ISS_CAL_CSI2_RAW12 == pCfg->inCsi2DataFormat)
            {
                appObj->cfg.pixProcCfg[i].extract =
                    VPS_ISS_CAL_PIX_EXRCT_B12_MIPI;
            }
            if (VPS_ISS_CAL_CSI2_RAW10 == pCfg->inCsi2DataFormat)
            {
                appObj->cfg.pixProcCfg[i].extract =
                    VPS_ISS_CAL_PIX_EXRCT_B10_MIPI;
            }
            appObj->cfg.isPixProcCfgValid[i]   = TRUE;
            appObj->cfg.pixProcCfg[i].decCodec = VPS_ISS_CAL_DPCM_DEC_BYPASS;
            appObj->cfg.pixProcCfg[i].enableDpcmInitContext = FALSE;
            appObj->cfg.pixProcCfg[i].encCodec = VPS_ISS_CAL_DPCM_ENC_BYPASS;
            appObj->cfg.pixProcCfg[i].pack     = VPS_ISS_CAL_PIX_PACK_B16;
            /* Write in 16 bit container */
            appObj->cfg.inFmt[i].pitch[0] = appObj->cfg.inFmt[i].width * 2;
            appObj->cfg.inFmt[i].bpp      = FVID2_BPP_BITS16;
        }
    }

    retVal = Fvid2_control(appObj->drvHandle, IOCTL_VPS_CAPT_SET_ISS_PARAMS,
                           &appObj->cfg, NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Capture Set ISS Params Failed!!!\n");
    }

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": ISS Capture Configured\n");

    return (retVal);
}

/**
 *  \brief Allocate and queue frames to driver
 */
static Int32 appCaptAllocAndQFrames(appCaptObj_t *appObj)
{
    Int32                  retVal = FVID2_SOK;
    UInt32                 streamId, idx;
    UInt32                 bufSize;
    Fvid2_Format           fmt;
    Fvid2_Frame           *pFrm;
    static Fvid2_FrameList frmList;
    static Char            fileStr[50U];

    /* for every stream and channel in a capture handle */
    Fvid2FrameList_init(&frmList);
    for (streamId = 0U; streamId < appObj->createPrms.numStream; streamId++)
    {
        Fvid2Format_init(&fmt);
        fmt.width      = appObj->maxWidth;
        fmt.height     = appObj->maxHeight;
        fmt.pitch[0]   = fmt.width * 2;
        fmt.bpp        = FVID2_BPP_BITS16;
        fmt.dataFormat = FVID2_DF_YUV422I_UYVY;

        idx = streamId * VPS_ISS_CAL_MAX_STREAMS;

        if (idx >= (CAPT_APP_FRAMES_PER_STREAM * VPS_ISS_CAL_MAX_STREAMS))
        {
            GT_assert(BspAppTrace, FALSE);
        }

        pFrm = (Fvid2_Frame *) &appObj->frames[idx];

        /* fill format with channel specific values  */
        fmt.chNum = Vps_captMakeChNum(appObj->instId, streamId, 0U);

        if (BSP_PLATFORM_ID_EVM == Bsp_platformGetId())
        {
            BspUtils_memClearOnAlloc(TRUE);
        }

        /*
         * alloc memory based on 'format'
         * Allocated frame info is put in frames[]
         * CAPT_APP_FRAMES_PER_STREAM is the number of buffers per channel to
         * allocate
         */
        retVal = BspUtils_memFrameAlloc(&fmt, pFrm,
                                        CAPT_APP_FRAMES_PER_STREAM);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Capture Frame Alloc Failed!!!\n");
            break;
        }

        snprintf(fileStr, sizeof (fileStr),
                 "captureOptionInst%dCh%dStr%d",
                 appObj->instId, 0, streamId);
        BspUtils_memFrameGetSize(&fmt, &bufSize, NULL);
        BspUtils_appPrintSaveRawCmd(
            fileStr,
            pFrm[0].addr[0][0],
            fmt.dataFormat,
            fmt.width,
            fmt.height,
            (CAPT_APP_FRAMES_PER_STREAM * bufSize));

        /* Set number of frame in frame list */
        for (idx = 0; idx < CAPT_APP_FRAMES_PER_STREAM; idx++)
        {
            frmList.frames[idx] = &pFrm[idx];
            GT_2trace(BspAppTrace, GT_INFO, APP_NAME ": Captured Frames [%d]"
                      " Available at 0x%x\n", idx, pFrm[idx].addr[0][0]);
        }

        frmList.numFrames = CAPT_APP_FRAMES_PER_STREAM;

        if (0x0 == streamId)
        {
            UInt32 idx;
            for (idx = 0; idx < CAPT_APP_FRAMES_PER_STREAM; idx++)
            {
                appObj->qCount[idx][0]   = (Uint32) frmList.frames[idx];
                appObj->dQCount[idx][0]  = (Uint32) frmList.frames[idx];
                appObj->qCount[idx][1U]  = 0U;
                appObj->dQCount[idx][1U] = 0U;
            }
            appCaptCountQ(appObj, &frmList, 0);
        }
        if (0x1 == streamId)
        {
            UInt32 idx;
            for (idx = 0; idx < CAPT_APP_FRAMES_PER_STREAM; idx++)
            {
                appObj->qCount[idx][2U]  = (Uint32) frmList.frames[idx];
                appObj->dQCount[idx][2U] = (Uint32) frmList.frames[idx];
                appObj->qCount[idx][3U]  = 0U;
                appObj->dQCount[idx][3U] = 0U;
            }
            appCaptCountQ(appObj, &frmList, 1);
        }
        if (0x2 == streamId)
        {
            UInt32 idx;
            for (idx = 0; idx < CAPT_APP_FRAMES_PER_STREAM; idx++)
            {
                appObj->qCount[idx][4U]  = (Uint32) frmList.frames[idx];
                appObj->dQCount[idx][4U] = (Uint32) frmList.frames[idx];
                appObj->qCount[idx][5U]  = 0U;
                appObj->dQCount[idx][5U] = 0U;
            }
            appCaptCountQ(appObj, &frmList, 2);
        }
        if (0x3 == streamId)
        {
            UInt32 idx;
            for (idx = 0; idx < CAPT_APP_FRAMES_PER_STREAM; idx++)
            {
                appObj->qCount[idx][6U]  = (Uint32) frmList.frames[idx];
                appObj->dQCount[idx][6U] = (Uint32) frmList.frames[idx];
                appObj->qCount[idx][7U]  = 0U;
                appObj->dQCount[idx][7U] = 0U;
            }
            appCaptCountQ(appObj, &frmList, 3);
        }
        /*
         * queue the frames in frmList
         * All allocated frames are queued here as an example.
         * In general atleast 2 frames per stream/channel need to queued
         * before capture can be started.
         * Failing which, frame could be dropped.
         */
        retVal = Fvid2_queue(appObj->drvHandle, &frmList, streamId);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Capture Queue Failed!!!\n");
            break;
        }
    }

    return (retVal);
}

static Int32 appCaptFreeFrames(appCaptObj_t *appObj)
{
    Int32                  retVal = FVID2_SOK;
    UInt32                 streamId, idx;
    Fvid2_Format           fmt;
    Fvid2_Frame           *pFrm;
    static Fvid2_FrameList frmList;

    /* for every stream and channel in a capture handle */
    Fvid2FrameList_init(&frmList);
    for (streamId = 0U; streamId < appObj->createPrms.numStream; streamId++)
    {
        Fvid2Format_init(&fmt);
        fmt.width      = appObj->maxWidth;
        fmt.height     = appObj->maxHeight;
        fmt.pitch[0]   = fmt.width * 2;
        fmt.bpp        = FVID2_BPP_BITS16;
        fmt.dataFormat = FVID2_DF_YUV422I_UYVY;

        while (1U)
        {
            retVal = Fvid2_dequeue(
                appObj->drvHandle,
                &frmList,
                streamId,
                FVID2_TIMEOUT_NONE);
            if (FVID2_SOK != retVal)
            {
                break;
            }
            else
            {
                appCaptCountDQ(appObj, &frmList, streamId);
            }
        }

        idx  = streamId * VPS_ISS_CAL_MAX_STREAMS;
        pFrm = (Fvid2_Frame *) &appObj->frames[idx];

        retVal = BspUtils_memFrameFree(&fmt, pFrm, CAPT_APP_FRAMES_PER_STREAM);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Capture Frame Free Failed!!!\n");
        }

        if (FVID2_SOK != retVal)
        {
            break;
        }
    }

    return (retVal);
}

static void appCaptCountQ(appCaptObj_t *appObj, Fvid2_FrameList *frmList,
                          UInt32 streamId)
{
    UInt32 frmIdx, frmAddr, cntIdx;
    for (frmIdx = 0U; frmIdx < frmList->numFrames; frmIdx++)
    {
        frmAddr = (Uint32) frmList->frames[frmIdx];
        for (cntIdx = 0U; cntIdx < CAPT_APP_FRAMES_PER_STREAM; cntIdx++)
        {
            if (0 == streamId)
            {
                if (appObj->qCount[cntIdx][0U] == frmAddr)
                {
                    appObj->qCount[cntIdx][1U]++;
                }
            }
            else if (1 == streamId)
            {
                if (appObj->qCount[cntIdx][2U] == frmAddr)
                {
                    appObj->qCount[cntIdx][3U]++;
                }
            }
            else if (2 == streamId)
            {
                if (appObj->qCount[cntIdx][4U] == frmAddr)
                {
                    appObj->qCount[cntIdx][5U]++;
                }
            }
            else
            {
                if (appObj->qCount[cntIdx][6U] == frmAddr)
                {
                    appObj->qCount[cntIdx][7U]++;
                }
            }
        }
    }
}

static void appCaptCountDQ(appCaptObj_t *appObj, Fvid2_FrameList *frmList,
                           UInt32 streamId)
{
    UInt32 frmIdx, frmAddr, cntIdx;
    for (frmIdx = 0U; frmIdx < frmList->numFrames; frmIdx++)
    {
        frmAddr = (Uint32) frmList->frames[frmIdx];
        for (cntIdx = 0U; cntIdx < CAPT_APP_FRAMES_PER_STREAM; cntIdx++)
        {
            if (0 == streamId)
            {
                if (appObj->dQCount[cntIdx][0U] == frmAddr)
                {
                    appObj->dQCount[cntIdx][1U]++;
                }
            }
            else if (1 == streamId)
            {
                if (appObj->dQCount[cntIdx][2U] == frmAddr)
                {
                    appObj->dQCount[cntIdx][3U]++;
                }
            }
            else if (2 == streamId)
            {
                if (appObj->dQCount[cntIdx][4U] == frmAddr)
                {
                    appObj->dQCount[cntIdx][5U]++;
                }
            }
            else
            {
                if (appObj->dQCount[cntIdx][6U] == frmAddr)
                {
                    appObj->dQCount[cntIdx][7U]++;
                }
            }
        }
    }
}

static void appCaptChkDQCounts(appCaptObj_t *appObj)
{
    UInt32 cntIdx, isError;
    isError = FALSE;
    for (cntIdx = 0U; cntIdx < CAPT_APP_FRAMES_PER_STREAM; cntIdx++)
    {
        if (appObj->dQCount[cntIdx][0U] != appObj->qCount[cntIdx][0U])
        {
            isError = TRUE;
            GT_1trace(
                BspAppTrace, GT_INFO, APP_NAME
                ": ERROR Q / DQ address are not in order [%d]!!!\n",
                cntIdx);
        }
        if (appObj->dQCount[cntIdx][1U] != appObj->qCount[cntIdx][1U])
        {
            isError = TRUE;
            GT_1trace(BspAppTrace, GT_INFO, APP_NAME
                      ": ERROR Q / DQ counts do not match up [%d]!!!\n", cntIdx);
        }
        if (appObj->dQCount[cntIdx][2U] != appObj->qCount[cntIdx][2U])
        {
            isError = TRUE;
            GT_1trace(
                BspAppTrace, GT_INFO, APP_NAME
                ": ERROR Q / DQ address are not in order [%d] - Stream 1!!!\n",
                cntIdx);
        }
        if (appObj->dQCount[cntIdx][3U] != appObj->qCount[cntIdx][3U])
        {
            isError = TRUE;
            GT_1trace(
                BspAppTrace, GT_INFO, APP_NAME
                ": ERROR Q / DQ counts do not match up [%d] - Stream 1!!!\n",
                cntIdx);
        }
    }
    if (FALSE == isError)
    {
        GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": Q/Dq Counts match up\n");
        GT_0trace(BspAppTrace, GT_INFO, APP_NAME ": Q/Dq Order match\n");
    }
}

/**
 *  appCaptGetTestId
 *  Return the test ID to run.
 */
static Int32 appCaptGetTestId(appCaptObj_t *appObj)
{
    UInt32       testCnt;
    static Int32 testId = 0;

    GT_0trace(BspAppTrace, GT_INFO, " \n");
    GT_0trace(BspAppTrace, GT_INFO,
              "--------------------------------------\n");
    GT_0trace(BspAppTrace, GT_INFO,
              "Select test to run as per below table:\n");
    GT_0trace(BspAppTrace, GT_INFO,
              "--------------------------------------\n");
    GT_0trace(BspAppTrace, GT_INFO, " \n");
    for (testCnt = 0; testCnt < APP_CAPT_NUM_OPTS; testCnt++)
    {
        GT_2trace(BspAppTrace, GT_INFO,
                  "%3d: %s\n", testCnt, gTestCfg[testCnt].testDescStr);
    }
    GT_2trace(BspAppTrace, GT_INFO,
              "%3d: %s\n", APP_CAPT_NUM_OPTS, "Auto Run\n");
    GT_1trace(BspAppTrace, GT_INFO, "%3d: EXIT\n", 100);
    GT_0trace(BspAppTrace, GT_INFO, " \n");
    GT_0trace(BspAppTrace, GT_INFO, "Enter Test to Run: \n");

    while (1U)
    {
        BspOsal_scanf("%d", &testId);
        Bsp_printf("%d\n", testId);
        if ((testId >= 0) && (testId < APP_CAPT_NUM_OPTS))
        {
            break;
        }
        else if (100 == testId)
        {
            break;
        }
        GT_0trace(BspAppTrace, GT_INFO, "Invalid Test ID. Enter Agian!!\n");
    }

    return (testId);
}

/**
 *  \brief Sets up the EVM / Board specifics, configures the sensor for a given
 *          config and enables sensor to stream.
 */
static Int32 appCaptcreateVidSensor(appCaptObj_t *instObj, appCaptCfg_t *pCfg)
{
    Int32  retVal;
    UInt32 sensorInstId, sensorI2cInstId, sensorI2cAddr, idx;
    Bsp_VidSensorChipIdParams   sensorChipIdPrms;
    Bsp_VidSensorChipIdStatus   sensorChipIdStatus;
    Bsp_VidSensorCreateStatus   sensorCreateStatus;
    Bsp_VidSensorConfigParams   configParams;
    BspUtils_Ub960Status        ub960Status;
    BspUtils_Ub960SourceI2cAddr ub960I2cAddr;

    sensorInstId = Bsp_boardGetVideoDeviceInstId(
        instObj->testPrms.sensorDrvId,
        FVID2_VPS_CAPT_VID_DRV,
        instObj->instId);
    sensorI2cInstId = Bsp_boardGetVideoDeviceI2cInstId(
        instObj->testPrms.sensorDrvId,
        FVID2_VPS_CAPT_VID_DRV,
        instObj->instId);
    sensorI2cAddr = Bsp_boardGetVideoDeviceI2cAddr(
        instObj->testPrms.sensorDrvId,
        FVID2_VPS_CAPT_VID_DRV,
        instObj->instId);

    if (FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV == pCfg->sensorDrvId)
    {
        ub960I2cAddr.slaveAddr       = UB960_SLAVE_ADDR;
        ub960I2cAddr.numSource       = pCfg->numStreams;
        ub960I2cAddr.rSlave1Addr[0U] = BspUtils_getSerAddrTida00262(0);
        ub960I2cAddr.rSlave2Addr[0U] = sensorI2cAddr;
        for (idx = 1U; idx < pCfg->numStreams; idx++)
        {
            sensorI2cAddr = Bsp_boardGetVideoDeviceI2cAddr(
                instObj->testPrms.sensorDrvId,
                FVID2_VPS_CAPT_VID_DRV,
                instObj->instId + idx);
            ub960I2cAddr.rSlave1Addr[idx] = BspUtils_getSerAddrTida00262(idx);
            ub960I2cAddr.rSlave2Addr[idx] = sensorI2cAddr;
        }

        sensorI2cAddr = ub960I2cAddr.rSlave2Addr[0U];
        retVal        = BspUtils_appInitUb960(0U, &ub960I2cAddr, &ub960Status);
        if (FVID2_SOK == retVal)
        {
            GT_1trace(BspAppTrace, GT_INFO,
                      "Detected 0x%x TIDA00262 modules\n",
                      ub960Status.numDetected);
        }
        else
        {
            GT_0trace(BspAppTrace, GT_ERR, "Failed to initialize UB960 !!!\n");
        }
    }

    GT_3trace(BspAppTrace, GT_INFO,
              "Sensor Inst ID-%d-Sensor I2C Inst ID %d,sensorI2cAddr: 0x%x\n",
              sensorInstId,
              sensorI2cInstId, sensorI2cAddr);

    if (FVID2_VIFM_SCH_CPI == instObj->createPrms.videoIfMode)
    {
        Bsp_boardSetPinMux(
            FVID2_VPS_CAPT_VID_DRV,
            VPS_CAPT_INST_ISS_CAL_A_CPI,
            instObj->testPrms.boardMode);
    }

    /* Power on video sensor at board level mux */
    retVal = Bsp_boardPowerOnDevice(instObj->testPrms.sensorDrvId, sensorInstId,
                                    TRUE);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Device power-on failed\n");
    }

    if (FVID2_VIFM_SCH_CPI == instObj->createPrms.videoIfMode)
    {
        if (FVID2_SOK == retVal)
        {
            /* select video sensor at board level mux */
            retVal = Bsp_boardSelectDevice(instObj->testPrms.sensorDrvId,
                                           sensorInstId);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR, "Device select failed\n");
            }
        }

        if (FVID2_SOK == retVal)
        {
            /* Select specific mode */
            retVal = Bsp_boardSelectMode(
                instObj->testPrms.sensorDrvId,
                sensorInstId,
                instObj->testPrms.boardMode);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR, "Device select mode failed\n");
            }
        }
    }

    for (idx = 0U; ((idx < pCfg->numStreams) && (FVID2_SOK == retVal)); idx++)
    {
        if (FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV == pCfg->sensorDrvId)
        {
            sensorI2cAddr = ub960I2cAddr.rSlave2Addr[idx];
            if (BSPUTILS_UB960EVM_NO_SOURCE_DETECTED !=
                ub960Status.portNum[idx])
            {
                /* Initialize TIDA00262 module */
                retVal = BspUtils_appInitTida00262(idx);
                if (FVID2_SOK != retVal)
                {
                    GT_1trace(BspAppTrace, GT_ERR, "Failed to initialize "
                              "TIDA00262 at port 0x%x!!!\n", idx);
                }
            }
            else
            {
                instObj->sensorHandle[idx] = NULL;
                continue;
            }
        }

        instObj->sensorCreatePrms.deviceI2cInstId    = sensorI2cInstId;
        instObj->sensorCreatePrms.numDevicesAtPort   = 1U;
        instObj->sensorCreatePrms.deviceI2cAddr[0]   = sensorI2cAddr;
        instObj->sensorCreatePrms.deviceResetGpio[0] = BSP_VID_SENSOR_GPIO_NONE;
        instObj->sensorCreatePrms.sensorCfg          = NULL;
        instObj->sensorCreatePrms.numSensorCfg       = 0U;

        instObj->sensorHandle[idx] = Fvid2_create(
            instObj->testPrms.sensorDrvId,
            sensorInstId,
            &instObj->sensorCreatePrms,
            &sensorCreateStatus,
            NULL);
        GT_assert(BspAppTrace, instObj->sensorHandle[idx] != NULL);

        sensorChipIdPrms.deviceNum = 0;
        retVal = Fvid2_control(
            instObj->sensorHandle[idx],
            IOCTL_BSP_VID_SENSOR_GET_CHIP_ID,
            &sensorChipIdPrms,
            &sensorChipIdStatus);
        GT_assert(BspAppTrace, (retVal == FVID2_SOK));

        GT_6trace(
            BspAppTrace, GT_INFO,
            APP_NAME
            ": ISS DrvInstId %d: VID SENSOR %04x (0x%02x): %04x:%04x:%04x\n",
            instObj->instId,
            instObj->testPrms.sensorDrvId,
            instObj->sensorCreatePrms.deviceI2cAddr[0],
            sensorChipIdStatus.chipId,
            sensorChipIdStatus.chipRevision,
            sensorChipIdStatus.firmwareVersion);

        configParams.videoIfWidth = instObj->testPrms.interfacewidth;
        configParams.dataformat   = instObj->testPrms.dataFormat;
        configParams.standard     = instObj->testPrms.standard;
        configParams.fps          = FVID2_FPS_30;
        configParams.bpp          = instObj->testPrms.bpp;
        retVal =
            Fvid2_control(instObj->sensorHandle[idx],
                          IOCTL_BSP_VID_SENSOR_SET_CONFIG,
                          &configParams,
                          NULL);
        GT_assert(BspAppTrace, (retVal == FVID2_SOK));

        /* start sensor, right now only OV sensor driver is implemented */
        retVal = Fvid2_control(instObj->sensorHandle[idx], FVID2_START, NULL,
                               NULL);
        GT_assert(BspAppTrace, (retVal == FVID2_SOK));
    }
    /* If interface is CSI2, print the number of lanes configured in sensor */
    if ((FVID2_SOK == retVal) &&
        (FVID2_VID_SENSOR_OV10640_CSI2_DRV == pCfg->sensorDrvId))
    {
        Bsp_VidSensorRegRdWrParams rdParams;
        /* MIPI_CTRL04 */
        UInt16 regAddr = 0x3444;
        UInt16 regValue = 0x0;

        rdParams.deviceNum = 0U;
        rdParams.numRegs   = 1U;
        rdParams.regAddr   = &regAddr;
        rdParams.regValue16 = &regValue;
        rdParams.regValue8  = NULL;

        retVal = Fvid2_control(instObj->sensorHandle[0],
                               IOCTL_BSP_VID_SENSOR_REG_READ,
                               &rdParams,
                               NULL);
        if (FVID2_SOK == retVal)
        {
            GT_1trace(BspAppTrace, GT_INFO, APP_NAME
                      ": CSI2 streaming on %d lanes !!!\n", regValue >> 4U);
        }
    }
    return (retVal);
}

static Int32 appCaptDeleteVidSensor(appCaptObj_t *appObj, appCaptCfg_t *pCfg)
{
    Int32  retVal = FVID2_SOK;
    UInt32 idx;

    for (idx = 0U; idx < appObj->createPrms.numStream; idx++)
    {
        if (NULL != appObj->sensorHandle[idx])
        {
            retVal = Fvid2_delete(appObj->sensorHandle[idx], NULL);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Sensor Delete Failed!!!\n");
            }
            else
            {
                appObj->sensorHandle[idx] = NULL;
            }
        }
    }
    if (FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV == pCfg->sensorDrvId)
    {
#ifdef NOT_YET
        for (idx = 0U; idx < appObj->createPrms.numStream; idx++)
        {
            retVal = BspUtils_appDeInitTida00262(idx);
            if (FVID2_SOK != retVal)
            {
                GT_1trace(BspAppTrace, GT_ERR, "Failed to Reset "
                          "TIDA00262 at port 0x%x!!!\n", idx);
            }
        }
        retVal = BspUtils_appDeInitUb960(0U);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR, "Failed to De Initialize "
                      "UB960 !!!\n");
        }
#endif  /* NOT_YET */
    }

    return (retVal);
}

static void appCaptPrintStatistics(appCaptObj_t *appObj,
                                   UInt32        execTimeInMsecs)
{
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    GT_0trace(BspAppTrace, GT_INFO, " Execution Statistics \r\n");
    GT_0trace(BspAppTrace, GT_INFO, " ==================== \r\n");
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    GT_2trace(BspAppTrace, GT_INFO,
              " Execution time    : %d.%d s \r\n",
              (execTimeInMsecs / 1000), (execTimeInMsecs % 1000));
    GT_2trace(BspAppTrace, GT_INFO,
              " Total Frame Count : %d (%d fields/sec) \r\n",
              appObj->totalFrmCount,
              (appObj->totalFrmCount * 1000) / execTimeInMsecs);
    GT_1trace(BspAppTrace, GT_INFO,
              " Avg CPU Load      : %d %% \r\n",
              appObj->totalCpuLoad / appObj->cpuLoadCount);
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");

    /* Print the driver status */
    BspUtils_appPrintCaptStatus(
        appObj->drvHandle,
        appObj->instId,
        appObj->createPrms.numStream,
        appObj->createPrms.numCh,
        execTimeInMsecs);

    GT_2trace(BspAppTrace, GT_INFO,
              " Capture Inst %d Status: Number of Frames with CRC Errors  : "
              "%d\n",
              appObj->instId,
              appObj->frameWithCrcErrorCnt);
    GT_2trace(BspAppTrace, GT_INFO,
              " Capture Inst %d Status: Number of Frames with ECC warning  : "
              "%d\n",
              appObj->instId,
              appObj->frameWithWarning);
    GT_2trace(BspAppTrace, GT_INFO,
              " Capture Inst %d Status: Number of Frames with un-handled error"
              ": %d\n",
              appObj->instId,
              appObj->frameErrorCnt);
        GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    return;
}

static void appCaptErrCb(const UInt32 *event, UInt32 numEvents, Ptr arg)
{
    uint32_t idx;
    appCaptObj_t *pAppObj = (appCaptObj_t *)arg;
    for (idx = 0U; idx < numEvents; idx++)
    {
        if (VPS_CAL_CSI2_PPI_VC_SOF1 == event[idx])
        {
            pAppObj->sofIntCount++;
        }
        else if (VPS_CAL_CSI2_PPI_VC_CRC_MISMATCH_VC1 == event[idx])
        {
            pAppObj->crcErrIntCnt++;
        }
        else
        {
            pAppObj->unExpectedIntCnt++;
        }
    }
}

static Int32 appCaptEnableErrorReporting(appCaptObj_t *appObj)
{
    Int32 retVal;
    vpsissCalErrorCfg_t errCfg;

    errCfg.numErrorsToMonitor = 2U;
    errCfg.errSrc[0U] = VPS_CAL_CSI2_PPI_VC_SOF1;
    errCfg.errSrc[1U] = VPS_CAL_CSI2_PPI_VC_CRC_MISMATCH_VC1;
    errCfg.appCb = &appCaptErrCb;
    errCfg.pAppCbArgs = (Ptr)appObj;

    retVal = Fvid2_control(appObj->drvHandle, IOCTL_VPS_CAPT_SET_ISS_ERR_PRMS,
                           &errCfg, NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": Capture Set ISS Params Failed!!!\n");
    }
    return retVal;
}
