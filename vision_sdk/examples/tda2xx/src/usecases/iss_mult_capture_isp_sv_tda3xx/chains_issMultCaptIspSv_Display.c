/*
 *******************************************************************************
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "chains_issMultCaptIspSv_Display_priv.h"
#include <examples/tda2xx/include/chains_common.h>

#define SV_ISP_OUT_HEIGHT           (800)
#define SV_CARBOX_WIDTH             (160)
#define SV_CARBOX_HEIGHT            (240)

#define SV_NUM_VIEWS                (4)

#define SV_HOR_WIDTH                (1280)
#define SV_HOR_HEIGHT               (720)

#define SV_CAPT_SENSOR_AR140_WIDTH  (1280)
#define SV_CAPT_SENSOR_AR140_HEIGHT (800)

#define SV_ALGO_ALIGN_IGNORE_FIRST_N_FRAMES (50U)
#define SV_ALGO_ALIGN_DEFAULT_FOCAL_LENGTH  (407U)

#define ENABLE_WDR_MERGE_PARAMS_CFG
#define ISP_OUTPUT_NUM_BUFFERS (4U)

/**
 *******************************************************************************
 *
 *  \brief  chains_issMultCaptIspSv_DisplayAppObj
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_issMultCaptIspSv_DisplayObj ucObj;

    IssIspConfigurationParameters ispConfig;

    UInt32  captureOutWidth;
    UInt32  captureOutHeight;
    UInt32  displayWidth;
    UInt32  displayHeight;

    Chains_Ctrl *chainsCfg;

} chains_issMultCaptIspSv_DisplayAppObj;


char gChains_IssMultCaptIspSv_Display_runTimeMenu[] = {
"\r\n "
"\r\n ===================="
"\r\n Chains Run-time Menu"
"\r\n ===================="
"\r\n "
"\r\n 0: Stop Chain"
"\r\n 1: Camera Position Calibration"
"\r\n 2: Save a captured RAW frame from channel 0"
"\r\n "
"\r\n "
"\r\n p: Print Performance Statistics "
"\r\n "
"\r\n Enter Choice: "
"\r\n "
};

static Void chains_issMultCaptIspSv_Display_SetSyncPrm(
                    SyncLink_CreateParams *pPrm,
                    UInt32 numCh,
                    UInt32 syncPeriod)
{
    pPrm->syncDelta = 37U; /* round up 1 / 27.0 */
    pPrm->syncThreshold = pPrm->syncDelta * 2U;
}


static Void chains_issMultCaptIspSv_Display_SetSelectlinkPrms(
                                                SelectLink_CreateParams *pPrm)
{
    pPrm->numOutQue = 1U;

    pPrm->outQueChInfo[0].outQueId   = 0;
    pPrm->outQueChInfo[0].numOutCh   = 1;
    pPrm->outQueChInfo[0].inChNum[0] = 0;
}


static Void chains_issMultCaptIspSv_Display_Config_Aewb(
        IssAewbAlgOutParams *pAewbAlgOut,
        Void *appData)
{
    UInt32 chId;

    chains_issMultCaptIspSv_DisplayAppObj *pObj =
        (chains_issMultCaptIspSv_DisplayAppObj *)appData;

    UTILS_assert(NULL != pObj);
    UTILS_assert(NULL != pAewbAlgOut);

    for ( chId = 0U; chId < pObj->ucObj.IssCapturePrm.numCh; chId++)
    {
        pAewbAlgOut->channelId = chId;
        /* AEWB Output parameters are already converted and stored in
           ispCfg parameter of alg out, so set it in the ISP using ISP
           Link */
        System_linkControl(
            pObj->ucObj.IssM2mIspLinkID,
            ISSM2MISP_LINK_CMD_SET_AEWB_PARAMS,
            pAewbAlgOut,
            sizeof(IssAewbAlgOutParams),
            TRUE);

        ChainsCommon_UpdateAewbParams(pAewbAlgOut);
    }
}

static Void chains_issMultCaptIspSv_Display_Config_DCC_Params(
        IssIspConfigurationParameters *ispCfg,
        IssM2mSimcopLink_ConfigParams *simcopCfg,
        Void                          *appData)
{
    UInt32 chId;
    chains_issMultCaptIspSv_DisplayAppObj *pObj =
        (chains_issMultCaptIspSv_DisplayAppObj *)appData;

    UTILS_assert(NULL != pObj);
    UTILS_assert(NULL != ispCfg);
    UTILS_assert(NULL != simcopCfg);

    for ( chId = 0U; chId < pObj->ucObj.IssCapturePrm.numCh; chId++)
    {
        ispCfg->channelId = chId;

        System_linkControl(
            pObj->ucObj.IssM2mIspLinkID,
            ISSM2MISP_LINK_CMD_SET_ISPCONFIG,
            ispCfg,
            sizeof(IssIspConfigurationParameters),
            TRUE);
    }

}

static Void chains_issMultCaptIspSv_Display_SetIspConfig(
            chains_issMultCaptIspSv_DisplayAppObj *pObj)
{
    Int32 status;
    UInt32 numCh;
    static IssM2mSimcopLink_ConfigParams dummySimcopCfg;

    /* Assuming all channels will be using same isp operating mode */
    ChainsCommon_GetIssIspConfig(
        pObj->chainsCfg->captureSrc,
        pObj->ucObj.Alg_IssAewbLinkID,
        pObj->ucObj.IssM2mIspPrm.channelParams[0U].operatingMode,
        &pObj->ispConfig,
        &dummySimcopCfg);

    /* MUST be called after link create and before link start */
    /* Apply the same config to all channel,
        right now the sensor are the same so its fine. */
    for (numCh = 0U; numCh < pObj->ucObj.IssCapturePrm.numCh; numCh++)
    {
        pObj->ispConfig.channelId = numCh;
        status = System_linkControl(
                pObj->ucObj.IssM2mIspLinkID,
                ISSM2MISP_LINK_CMD_SET_ISPCONFIG,
                &pObj->ispConfig,
                sizeof(pObj->ispConfig),
                TRUE);
        UTILS_assert(0 == status);
    }

}

static Void chains_issMultCaptIspSv_Display_SetDccConfig(
            chains_issMultCaptIspSv_DisplayAppObj *pObj)
{
    Int32 status;
    VidSensor_DccInfo dccInfo;
    AlgorithmLink_IssAewbDccCameraInfo camInfo;

    memset((void*) &dccInfo, 0, sizeof(dccInfo));
    VidSensor_control(
        ChainsCommon_GetSensorCreateParams(),
        VID_SENSOR_CMD_GET_DCC_INFO,
        &dccInfo,
        NULL);
    if (TRUE == dccInfo.isDccCfgSupported)
    {
        camInfo.baseClassControl.controlCmd =
            ALGORITHM_AEWB_LINK_CMD_SET_CAMERA_INFO;
        camInfo.baseClassControl.size = sizeof(camInfo);

        camInfo.cameraId = dccInfo.cameraId;

        if (pObj->chainsCfg->captureSrc == CHAINS_CAPTURE_SRC_UB960_TIDA00262)
        {
            camInfo.width = SV_CAPT_SENSOR_AR140_WIDTH;
            camInfo.height = SV_CAPT_SENSOR_AR140_HEIGHT;
        }
        else
        {
            /* Un Recognized Capture source */
            UTILS_assert(FALSE);
        }

        status = System_linkControl(
                    pObj->ucObj.Alg_IssAewbLinkID,
                    ALGORITHM_LINK_CMD_CONFIG,
                    &camInfo,
                    sizeof(camInfo),
                    TRUE);
        UTILS_assert(0 == status);
    }
}


Void chains_issMultCaptIspSv_Display_SetAppPrms(
                    chains_issMultCaptIspSv_DisplayObj *pUcObj, Void *appObj)
{
    chains_issMultCaptIspSv_DisplayAppObj *pObj
        = (chains_issMultCaptIspSv_DisplayAppObj*)appObj;
    IssM2mIspLink_OperatingMode ispOpMode;
    Int16 carBoxWidth;
    Int16 carBoxHeight;
    UInt32 numCh;

    pObj->captureOutWidth  = SV_CAPT_SENSOR_AR140_WIDTH;
    pObj->captureOutHeight = SV_CAPT_SENSOR_AR140_HEIGHT;

    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &pObj->displayWidth,
        &pObj->displayHeight
        );

    ispOpMode = ISSM2MISP_LINK_OPMODE_12BIT_LINEAR;

    if (CHAINS_ISS_WDR_MODE_SINGLE_PASS == pObj->chainsCfg->issWdrMode)
    {
        ispOpMode = ISSM2MISP_LINK_OPMODE_1PASS_WDR;
    }

    ChainsCommon_SetIssCreatePrms(
        &pUcObj->IssCapturePrm,
        &pUcObj->IssM2mIspPrm,
        NULL,
        &pUcObj->Alg_IssAewbPrm,
        pObj->chainsCfg->captureSrc,
        pObj->captureOutWidth,
        SV_ISP_OUT_HEIGHT,
        0U, /* RSZ B */
        0U, /* RSZ B */
        ISSM2MSIMCOP_LINK_OPMODE_MAXNUM,
        ispOpMode,
        NULL);

    /* Override for multiple channel capture */
    ChainsCommon_MultipleCam_UpdateIssCapturePrms (
        &pUcObj->IssCapturePrm,
        pObj->chainsCfg->captureSrc,
        ispOpMode, pObj->captureOutWidth, pObj->captureOutHeight);

    /* Since we are operating in Linear mode, disable back-light compensation */
    if ((ispOpMode == ISSM2MISP_LINK_OPMODE_12BIT_LINEAR) ||
        (ispOpMode == ISSM2MISP_LINK_OPMODE_1PASS_WDR))
    {
        pUcObj->Alg_IssAewbPrm.aeDynParams.enableBlc = FALSE;
    }

    pUcObj->Alg_IssAewbPrm.appData = pObj;
    pUcObj->Alg_IssAewbPrm.cfgCbFxn =
                                chains_issMultCaptIspSv_Display_Config_Aewb;

    pUcObj->Alg_IssAewbPrm.mergeCbFxn = NULL;

    pUcObj->Alg_IssAewbPrm.dccIspCfgFxn =
        chains_issMultCaptIspSv_Display_Config_DCC_Params;

    pUcObj->IssCapturePrm.allocBufferForRawDump = TRUE;

    chains_issMultCaptIspSv_Display_SetSelectlinkPrms(&pUcObj->SelectPrm);


    ChainsCommon_SurroundView_SetParams(
        NULL, // Capture Params
        NULL,
        NULL,
        NULL, //&pUcObj->SelectPrm,
        NULL, //&pUcObj->VPE_sv_orgPrm1,
        NULL, //&pUcObj->VPE_sv_orgPrm2,
        &pUcObj->Sync_svPrm,
        NULL, //&pUcObj->Sync_sv_orgPrm1,
        NULL, //&pUcObj->Sync_sv_orgPrm2,
        &pUcObj->Alg_SynthesisPrm,
        &pUcObj->Alg_GeoAlignPrm,
        &pUcObj->Alg_PhotoAlignPrm,
        NULL,
        NULL,
        NULL,
        NULL, //&pUcObj->Alg_DmaSwMs_sv_orgPrm1,
        NULL, //&pUcObj->Alg_DmaSwMs_sv_orgPrm2,
        &pUcObj->GrpxSrcPrm,
        &pUcObj->Display_VideoPrm,
        NULL, //&pUcObj->Display_sv_orgPrm1,
        NULL, //&pUcObj->Display_sv_orgPrm12,
        &pUcObj->Display_GrpxPrm,
        pObj->chainsCfg->displayType,
        pUcObj->IssCapturePrm.numCh,
        ALGORITHM_LINK_SRV_OUTPUT_2D, //pObj->chainsCfg->svOutputMode,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        TRUE /* Enable CAR overlay */
        );

        carBoxWidth = SV_CARBOX_HEIGHT;
        carBoxHeight = SV_CARBOX_WIDTH;

    chains_issMultCaptIspSv_Display_SetSyncPrm(
                    &pUcObj->Sync_svPrm,
                    pUcObj->IssCapturePrm.numCh, 0x0); /* Sync period not used
                                                            in this func now */

    ChainsCommon_SurroundView_SetSynthParams(&pUcObj->Alg_SynthesisPrm,
                                            SV_CAPT_SENSOR_AR140_WIDTH,
                                            SV_ISP_OUT_HEIGHT,
                                            SV_HOR_WIDTH,
                                            SV_HOR_HEIGHT,
                                            SV_NUM_VIEWS,
                                            carBoxWidth,
                                            carBoxHeight,
                                            ALGORITHM_LINK_SRV_OUTPUT_2D,
                                            TRUE); /* Enable CAR overlay */

    ChainsCommon_SurroundView_SetGAlignParams(&pUcObj->Alg_GeoAlignPrm,
                                            SV_CAPT_SENSOR_AR140_WIDTH,
                                            SV_ISP_OUT_HEIGHT,
                                            SV_HOR_WIDTH,
                                            SV_HOR_HEIGHT,
                                            SV_NUM_VIEWS,
                                            carBoxWidth,
                                            carBoxHeight,
                                            ALGORITHM_LINK_SRV_OUTPUT_2D);

    /* Override parameters specific to this use case */
    pUcObj->Alg_GeoAlignPrm.ignoreFirstNFrames =
                                    SV_ALGO_ALIGN_IGNORE_FIRST_N_FRAMES;
    pUcObj->Alg_GeoAlignPrm.defaultFocalLength =
                                    SV_ALGO_ALIGN_DEFAULT_FOCAL_LENGTH;

    ChainsCommon_SurroundView_SetPAlignParams(&pUcObj->Alg_PhotoAlignPrm,
                                            SV_CAPT_SENSOR_AR140_WIDTH,
                                            SV_ISP_OUT_HEIGHT,
                                            SV_HOR_WIDTH,
                                            SV_HOR_HEIGHT,
                                            SV_NUM_VIEWS,
                                            carBoxWidth,
                                            carBoxHeight,
                                            ALGORITHM_LINK_SRV_OUTPUT_2D);

    for (numCh = 0U; numCh < pUcObj->IssCapturePrm.numCh; numCh ++)
    {
        pUcObj->IssM2mIspPrm.channelParams[numCh].numBuffersPerCh =
            ISP_OUTPUT_NUM_BUFFERS;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Start the capture display Links
 *
 *          Function sends a control command to capture and display link to
 *          to Start all the required links . Links are started in reverce
 *          order as information of next link is required to connect.
 *          System_linkStart is called with LinkId to start the links.
 *
 * \param   pObj  [IN] chains_issMultCaptIspSv_DisplayAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Void chains_issMultCaptIspSv_Display_StartApp(
                                chains_issMultCaptIspSv_DisplayAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    ChainsCommon_SetWdrMode(pObj->chainsCfg->issWdrMode);

    /* Video sensor layer is used to get the dcc bin file and other information,
       to set the ISP configuration, so Video sensor is created first */
    ChainsCommon_StartCaptureDevice(
        pObj->chainsCfg->captureSrc,
        pObj->captureOutWidth,
        pObj->captureOutHeight);

    chains_issMultCaptIspSv_Display_SetDccConfig(pObj);

    /* Sets the Simcop Config also */
    chains_issMultCaptIspSv_Display_SetIspConfig(pObj);

    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    chains_issMultCaptIspSv_Display_Start(&pObj->ucObj);

    Chains_prfLoadCalcEnable(TRUE, FALSE, FALSE);
}

/**
 *******************************************************************************
 *
 * \brief   Delete the capture display Links
 *
 *          Function sends a control command to capture and display link to
 *          to delete all the prior created links
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   chains_issMultCaptIspSv_DisplayAppObj
 *
 *******************************************************************************
*/
static Void chains_issMultCaptIspSv_Display_StopAndDeleteApp(
                                chains_issMultCaptIspSv_DisplayAppObj *pObj)
{
    chains_issMultCaptIspSv_Display_Stop(&pObj->ucObj);
    chains_issMultCaptIspSv_Display_Delete(&pObj->ucObj);

    ChainsCommon_StopDisplayCtrl();

    ChainsCommon_StopCaptureDevice(pObj->chainsCfg->captureSrc);

    ChainsCommon_StopDisplayDevice(pObj->chainsCfg->displayType);

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    Chains_prfLoadCalcEnable(FALSE, TRUE, TRUE);
}

/**
 *******************************************************************************
 *
 * \brief   4 Channel surround view usecase entry function
 *
 *          This function configure, creates, link various links to establish
 *          usecase.
 *
 *          Further in a while loop displays run time menu and waits
 *          for user inputs to print the statistics or to end the demo.
 *
 *          Once the user inputs end of demo stop and delete
 *          functions are executed.
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_issMultCaptIspSv_Display(Chains_Ctrl *chainsCfg)
{
    char ch, chPrev, tempCh;
    UInt32 done = FALSE;
    Bool startWithCalibration;
    chains_issMultCaptIspSv_DisplayAppObj chainsObj;
    Chains_CaptureSrc oldCaptSrc;

    if ((CHAINS_ISS_WDR_MODE_SINGLE_PASS != chainsCfg->issWdrMode) &&
        (CHAINS_ISS_WDR_MODE_DISABLED != chainsCfg->issWdrMode))
    {
        Vps_printf(" CHAINS: WDR should either be disabled or "
                    "in One Pass mode!!!\n");
        return;
    }

    oldCaptSrc = chainsCfg->captureSrc;
    chainsCfg->displayType = CHAINS_DISPLAY_TYPE_HDMI_720P;
    chainsCfg->captureSrc = CHAINS_CAPTURE_SRC_UB960_TIDA00262;
    chainsObj.chainsCfg = chainsCfg;

    do
    {
        done = FALSE;
        /* Set startWithCalibration = TRUE to start the demo with calibration.
           Else it will use the previously calibrated LUTs */
        startWithCalibration = TRUE;
        ChainsCommon_SurroundView_CalibInit(startWithCalibration);
        /* Initialize Video Sensor, so that Algorithm can use Params
           from Vid Sensor layer */
        ChainsCommon_InitCaptureDevice(chainsCfg->captureSrc);
        chains_issMultCaptIspSv_Display_Create(&chainsObj.ucObj, &chainsObj);
        chains_issMultCaptIspSv_Display_StartApp(&chainsObj);

        do
        {
            Vps_printf(gChains_IssMultCaptIspSv_Display_runTimeMenu);

            ch = Chains_readChar();

            switch(ch)
            {
                case '0':
                    done = TRUE;
                    chPrev = '3';
                    break;
                case '1':
                    chPrev = ChainsCommon_SurroundView_MenuCalibration();
                    done = TRUE;
                    break;
                case '2':
                    System_linkControl(
                            chainsObj.ucObj.IssCaptureLinkID,
                            ISSCAPTURE_LINK_CMD_SAVE_FRAME,
                            NULL,
                            0,
                            TRUE);
                    break;
                case 'p':
                case 'P':
                    ChainsCommon_PrintStatistics();
                    chains_issMultCaptIspSv_Display_printStatistics(
                                    &chainsObj.ucObj);
                    break;
                default:
                    Vps_printf("\nUnsupported option '%c'. Please try again\n",
                                ch);
                    break;
            }
        } while ((chPrev!='3') && (FALSE == done));

        chains_issMultCaptIspSv_Display_StopAndDeleteApp(&chainsObj);
        ChainsCommon_SurroundView_CalibDeInit();
        Task_sleep(100);
        Vps_printf("\n Power Cycle UB960 and enter a number\n");
        Task_sleep(100);
        tempCh = Chains_readChar();
        Vps_printf("\n Restarting %d \n", tempCh);

    } while (chPrev!='3');
    chainsCfg->captureSrc = oldCaptSrc;
}

