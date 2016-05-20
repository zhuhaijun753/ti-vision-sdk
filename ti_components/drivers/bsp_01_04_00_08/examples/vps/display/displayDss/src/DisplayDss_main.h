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
 *  \file displayDss_main.h
 *
 *  \brief DSS Display driver sample application private header file.
 *
 */

#ifndef DISPLAY_DSS_MAIN_H_
#define DISPLAY_DSS_MAIN_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xdc/std.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/utils/Load.h>
#include <ti/sysbios/knl/Semaphore.h>

#include <common/bsp_types.h>
#include <common/trace.h>
#include <common/bsp_config.h>
#include <common/bsp_utils.h>
#include <osal/bsp_osal.h>
#include <fvid2/fvid2.h>
#include <platforms/bsp_platform.h>
#include <vps/vps.h>
#ifdef VPS_DSS_BUILD
#include <vps/vps_display.h>
#include <vps/vps_displayCtrl.h>
#endif

#include <devices/bsp_device.h>
#include <devices/bsp_lcdController.h>
#include <devices/bsp_sii9022a.h>
#include <boards/bsp_board.h>
#include <utility/bsputils_prf.h>
#include <utility/bsputils_app.h>
#include <utility/bsputils_mem.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Test application stack size */
#define DISP_APP_TSK_STACK_MAIN         (10U * 1024U)

/* Test application task priority */
#define DISP_APP_TSK_PRI_MAIN           (10U)

#define APP_NAME                        "DISP_DSS_APP"

/* Worst case frames per handle */
#define DISP_APP_MAX_FRAMES_PER_HANDLE  (4U)

/* Padding required for allocating extra memory. */
#define DISP_APP_PADDING_LINES          (0U)

/* Default run count in seconds in case of EVM else this is in frame count. */
#define DISP_APP_RUN_COUNT              (10U)

/* Buffer width in pixels to allocate. */
#define DISP_APP_BUF_WIDTH              (1920U)
/* Buffer height in lines to allocate. */
#define DISP_APP_BUF_HEIGHT             (1080U)

/* Flag used to set in test params input width and height so that the detected
 * LCD width and height is used. This is kept same as LCD width/height so
 * that the same code works for Zebu as well */
#define DISP_APP_USE_LCD_WIDTH          (800U)
#define DISP_APP_USE_LCD_HEIGHT         (480U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Forward declaration for common object. */
typedef struct DispApp_Obj_t DispApp_Obj;

/**
 *  \brief Display application test parameters.
 *  The test case execution happens based on values of this structure
 */
typedef struct
{
    Char            *testDescStr;
    /**< Test description. */

    UInt32           numEnc;
    /**< Number of Video Encoders to run with. */
    UInt32           encDrvId[VPS_DISP_ENC_INST_MAX];
    /**< Video encoder driver ID to open for each handle. */
    UInt32           vencId[VPS_DISP_ENC_INST_MAX];
    /**< Venc ID for each handle. */
    Fvid2_Standard   standard[VPS_DISP_ENC_INST_MAX];
    /**< Video encoder video standard. */
    UInt32           isSdVenc;
    /**< True for SD VENC and false for others. Valid only for Tda3xx. */

    UInt32           numHandles;
    /**< Number of display handles to run with. */
    UInt32           instId[VPS_DISP_INST_MAX];
    /**< Instance ID to open for each handle. */

    Fvid2_DataFormat inDataFmt[VPS_DISP_INST_MAX];
    /**< YUV or RGB data format. */

    UInt32           inWidth[VPS_DISP_INST_MAX];
    /**< Input buffer resolution width in pixels. */
    UInt32           inHeight[VPS_DISP_INST_MAX];
    /**< Input buffer resolution height in lines. */
    UInt32           posx[VPS_DISP_INST_MAX];
    /**< Input buffer position x. */
    UInt32           posy[VPS_DISP_INST_MAX];
    /**< Input buffer position y. */
    UInt32           inScanFormat[VPS_DISP_INST_MAX];
    /**< In scan format. */
    UInt32           isFieldMerge[VPS_DISP_INST_MAX];
    /**< Field merge or field separated. */
    Int32            runCount;
    /**< Number of frames to display. */
    Bsp_BoardMode    boardMode;
    /**< Board mode param like 24-bit, 8-bit. */
    UInt32           boardId;
    /**< List of valid boards to run the test case. */
} DispApp_TestParams;

/**
 *  \brief Driver instance information.
 */
typedef struct
{
    UInt32                     instId;
    /**< Instance ID. */
    UInt32                     encDrvId;
    /**< Encoder driver ID. */

    Vps_DispCreateParams       createPrms;
    /**< Create time parameters. */
    Vps_DispCreateStatus       createStatus;
    /**< Create status returned by driver during Fvid2_create(). */

    Vps_DispDssParams          dssPrms;
    /**< DSS driver parameters. */
    Vps_DssDispcVidConfig      vidCfg;
    /**< DSS video configuration. */
    Vps_DssDispcGfxConfig      gfxCfg;
    /**< DSS graphics configuration. */

    Fvid2_Handle               drvHandle;
    /**< FVID2 display driver handle. */
    Fvid2_CbParams             cbPrms;
    /**< Callback params. */

    Vps_DssDispcOvlyPipeConfig ovlpipeconfig;
    /** <Pipe Config. */

    Fvid2_Frame                frames[DISP_APP_MAX_FRAMES_PER_HANDLE];
    /**< FVID2 Frames that will be used for display3. */
    Fvid2_Format               allocFmt;
    /**< Format passed to utils frame alloc function. */

    UInt32                     pitch[FVID2_MAX_PLANES];
    /**< Buffer pitch - used for buffer allocation for this instance. */

    UInt32                     isFieldMerge;
    /**< Field merge or field separated. */

    UInt32                     inWidth;
    /**< Input buffer resolution width in pixels. */

    UInt32                     inHeight;
    /**< Input buffer resolution height in lines. */

    Fvid2_DataFormat           inDataFmt;
    /**< YUV or RGB data format. */

    UInt32                     posx;
    /**< Input buffer position x. */

    UInt32                     posy;
    /**< Input buffer position y. */

    UInt32                     inScanFormat;
    /**< Scan Format. For valid values see #Fvid2_ScanFormat. */

    Fvid2_Handle               encHandle;
    /**< FVID2 encoder driver handle. */
    /* Bsp_VidEncCreateParams    encCreatePrms; */
    /**< Video encoder create params. */
    /* Bsp_VidEncVideoModeParams encVideoModePrms; */
    /**< Video encoder mode params. */

    DispApp_Obj               *appObj;
    /**< Reference pointer to application common object. */
} DispApp_InstObj;

/**
 *  \brief Test application data structure.
 */
struct DispApp_Obj_t
{
    DispApp_InstObj             instObj[VPS_DISP_INST_MAX];
    /**< Driver instance objects. */
    DispApp_TestParams          testPrms;
    /**< Current test parameters. */

    Fvid2_Handle                dctrlHandle;
    /**< DCTRL handle. */
    Fvid2_Handle                hdmiHandle;
    /**< Off-Chip HDMI handle. */
    Task_Handle                 tskHandle;
    /**< Test task handle. */

    Vps_DctrlConfig             dctrlCfg;
    /**< DCTRL path config. */

    Vps_DssDispcOvlyPanelConfig panelCfg;
    /** <Panel Config. */

    Bsp_LcdCtrlCreateParams     lcdCtrlCreatePrms;
    /** <LCD controller Create params. */

    Fvid2_Handle                lcdCtrlhdl;
    /**< LCD controller Driver handle. */
    Bsp_LcdCtrlPanelInfo        lcdPanelInfo;
    /**< LCD panel timing data. */

    UInt32                      maxWidth;
    /**< Max width in pixels - used for buffer allocation for all instance. */
    UInt32                      maxHeight;
    /**< Max height in lines - used for buffer allocation for all instance. */

    UInt32                      totalFldCount;
    /**< Count of all frames displayed. */
    UInt32                      totalCpuLoad;
    /**< Accumulated CPU load - added every frame. */
    UInt32                      cpuLoadCount;
    /**< CPU load count used to get average CPU load - incremented every
     *   accumulation. */
    UInt32                      callBackCount;
    /**< Callback count - used in case of sim/zebu to enable loop count in
     *   frames. */
    UInt32                      enableAutoRun;
    /**< Auto-run enable flag. */

    UInt32                      startTime;
    /**< Application start time in clock ticks. */
};

/**
 *  \brief Buffer configuration structure for buffer allocation.
 */
typedef struct
{
    UInt32 width;
    /**< Buffer width in pixels. */
    UInt32 height;
    /**< Buffer height. */
    UInt32 pitch;
    /**< Pitch in bytes. */
    UInt32 dataFmt;
    /**< Data format. */
    UInt32 scanFmt;
    /**< Scan format - interlaced or progressive. */
    Bool   fieldsMerged;
    /**< Fields are merged or separated for the interlaced scan format. */
    UInt32 numBuffers;
    /**< Number of buffers. */
} DispApp_LoadBufCfg;

/**
 *  \brief Buffer info structure.
 */
typedef struct
{
    UInt8             *bufAddr;
    /**< Buffer address. */
    UInt32             bufSize;
    /**< One buffer size in bytes. */
    UInt32             totalBufSize;
    /**< Total buffer size in bytes. */
    void              *yBufAddrEven[DISP_APP_MAX_FRAMES_PER_HANDLE];
    /**< Pointer to even luma for each buffer. */
    void              *yBufAddrOdd[DISP_APP_MAX_FRAMES_PER_HANDLE];
    /**< Pointer to odd luma for each buffer. */
    void              *cBufAddrEven[DISP_APP_MAX_FRAMES_PER_HANDLE];
    /**< Pointer to even chroma for each buffer. */
    void              *cBufAddrOdd[DISP_APP_MAX_FRAMES_PER_HANDLE];
    /**< Pointer to odd chroma for each buffer. */
    void              *bgrBufAddr[DISP_APP_MAX_FRAMES_PER_HANDLE];
    /**< Pointer to BGR data for each buffer. */
    DispApp_LoadBufCfg bufCfg;
    /**< Buffer configuration. */
} DispApp_BufInfo;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/** \brief Defines the various load buffer configuration. */
static const DispApp_LoadBufCfg gDispDssLoadBufCfg[] =
{
    /* width, height, pitch, dataFmt, scanFmt, fieldsMerged, numBuffers */
    {1920u, 1080u, 3840u, FVID2_DF_YUV422I_YUYV, FVID2_SF_PROGRESSIVE,
     FALSE,
     DISP_APP_MAX_FRAMES_PER_HANDLE},
    {1920u, 1080u, 5760u, FVID2_DF_BGR24_888,    FVID2_SF_PROGRESSIVE,
     FALSE,
     DISP_APP_MAX_FRAMES_PER_HANDLE},
};

/* None */
static const DispApp_TestParams gDispAppTestPrms[] =
{
    {       /* testDescStr */
        "DSS Video1     (YUY422I)                   -> DPI1 -> LCD",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard[] */
        {
            FVID2_STD_CUSTOM,
        },
        /* isSdVenc */
        FALSE,
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,
        },
        {
            /* inWidth */
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* inHeight */
            DISP_APP_USE_LCD_HEIGHT,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* Field Merge */
            FALSE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX),
    },
    {       /* testDescStr */
        "DSS                        GFX (BGR888)    -> DPI1 -> LCD",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard */
        {
            FVID2_STD_CUSTOM,
        },
        /* isSdVenc */
        FALSE,
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_GFX1,
        },
        {
            /* inDataFmt */
            FVID2_DF_BGR24_888,
        },
        {
            /* inWidth */
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* inHeight */
            DISP_APP_USE_LCD_HEIGHT,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* Field Merge */
            FALSE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX),
    },
    {       /* testDescStr */
        "DSS Video1     (YUV422I) + GFX (BGR888)    -> DPI1 -> LCD",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard */
        {
            FVID2_STD_CUSTOM,
        },
        /* isSdVenc */
        FALSE,
        /* numofHandles */
        2U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
            VPS_DISP_INST_DSS_GFX1,
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,
            FVID2_DF_BGR24_888,
        },
        {
            /* inWidth */
            DISP_APP_USE_LCD_WIDTH,
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* inHeight */
            DISP_APP_USE_LCD_HEIGHT,
            DISP_APP_USE_LCD_HEIGHT,
        },
        /* Posx*/
        {
            0U,
            0U,
        },
        /* Poxy*/
        {
            0U,
            0U,
        },
        /* Scan Format */
        {
            FVID2_SF_PROGRESSIVE,
            FVID2_SF_PROGRESSIVE,
        },
        /* Field Merge */
        {
            FALSE,
            FALSE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX),
    },
    {       /* testDescStr */
        "DSS Video1,2   (YUV422I) + GFX (BGR888)    -> DPI1 -> LCD",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard */
        {
            FVID2_STD_CUSTOM,
        },
        /* isSdVenc */
        FALSE,
        /* numofHandles */
        3U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
            VPS_DISP_INST_DSS_VID2,
            VPS_DISP_INST_DSS_GFX1
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,
            FVID2_DF_YUV422I_YUYV,
            FVID2_DF_BGR24_888,
        },
        {
            /* inWidth */
            360U,
            360U,
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* inHeight */
            DISP_APP_USE_LCD_HEIGHT,
            DISP_APP_USE_LCD_HEIGHT,
            DISP_APP_USE_LCD_HEIGHT,
        },
        /* Posx*/
        {
            0U,
            360U,
            0U,
        },
        /* Poxy*/
        {
            0U,
            0U,
            0U,
        },
        /* Scan Format */
        {
            FVID2_SF_PROGRESSIVE,
            FVID2_SF_PROGRESSIVE,
            FVID2_SF_PROGRESSIVE,
        },
        /* Field Merge */
        {
            FALSE,
            FALSE,
            FALSE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX),
    },
    {       /* testDescStr */
        "DSS Video1     (YUY422I)                   -> DPI1 -> SIL9022A-HDMI@1080P60",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            FVID2_VID_ENC_SII9022A_DRV,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard[] */
        {
            FVID2_STD_1080P_60,
        },
        /* isSdVenc */
        FALSE,
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,
        },
        {
            /* inWidth */
            1920U,
        },
        {
            /* inHeight */
            1080U,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* Field Merge */
            FALSE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_BASE_TDA3XX | BSP_BOARD_MULTIDES),
    },
    {       /* testDescStr */
        "DSS Video1     (YUY422I)                   -> DPI1 -> SIL9022A-HDMI@480P60(TDM)",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            FVID2_VID_ENC_SII9022A_DRV,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard[] */
        {
            FVID2_STD_480P,
        },
        /* isSdVenc */
        FALSE,
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,
        },
        {
            /* inWidth */
            720U,
        },
        {
            /* inHeight */
            480U,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* Field Merge */
            FALSE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_8BIT_TDM,
        /* boardId */
        (BSP_BOARD_BASE_TDA3XX | BSP_BOARD_MULTIDES),
    },
    {       /* testDescStr */
        "DSS Video1     (YUY422I)                   -> DPI1 -> SIL9022A-HDMI@720P60",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            FVID2_VID_ENC_SII9022A_DRV,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard[] */
        {
            FVID2_STD_720P_60,
        },
        /* isSdVenc */
        FALSE,
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,
        },
        {
            /* inWidth */
            1280U,
        },
        {
            /* inHeight */
            720U,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* Field Merge */
            FALSE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_BASE_TDA3XX | BSP_BOARD_MULTIDES),
    },
#if defined (TDA2XX_FAMILY_BUILD) || defined (OMAP5X_FAMILY_BUILD)
    {       /* testDescStr */
        "DSS Video1,2,3 (YUV422I) + GFX (BGR888)    -> DPI1 -> LCD",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard */
        {
            FVID2_STD_CUSTOM,
        },
        /* isSdVenc */
        FALSE,
        /* numofHandles */
        4U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
            VPS_DISP_INST_DSS_VID2,
            VPS_DISP_INST_DSS_VID3,
            VPS_DISP_INST_DSS_GFX1
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,
            FVID2_DF_YUV422I_YUYV,
            FVID2_DF_YUV422I_YUYV,
            FVID2_DF_BGR24_888,
        },
        {
            /* inWidth */
            DISP_APP_USE_LCD_WIDTH,
            100U,
            100U,
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* inHeight */
            DISP_APP_USE_LCD_HEIGHT,
            100U,
            100U,
            DISP_APP_USE_LCD_HEIGHT,
        },
        /* Posx*/
        {
            0U,
            150U,
            550U,
            0U,
        },
        /* Poxy*/
        {
            0U,
            300U,
            300U,
            0U,
        },
        /* Scan Format */
        {
            FVID2_SF_PROGRESSIVE,
            FVID2_SF_PROGRESSIVE,
            FVID2_SF_PROGRESSIVE,
            FVID2_SF_PROGRESSIVE,
        },
        /* Field Merge */
        {
            FALSE,
            FALSE,
            FALSE,
            FALSE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT * 2,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX),
    },

    {       /* testDescStr */
        "DSS Video2     (YUY422I)                   -> TV   -> HDMI@1080P60",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            0,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_HDMI,
        },
        /* standard[] */
        {
            FVID2_STD_1080P_60,
        },
        /* isSdVenc */
        FALSE,
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID2,
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,
        },
        {
            /* inWidth */
            1920U,
        },
        {
            /* inHeight */
            1080U,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* Field Merge */
            FALSE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_DEFAULT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA2EX),
    },
    {
        /* testDescStr */
        "DSS Video2     (YUY422I)                   -> TV   -> HDMI@1080I60",
        /* Num of encoders */
        1U,
        /* encDrvId[] */
        {
            0,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_HDMI,
        },
        /* standard[] */
        {
            FVID2_STD_CUSTOM,
        },
        /* isSdVenc */
        FALSE,
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID2,
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,
        },
        {
            /* inWidth */
            1920U,
        },
        {
            /* inHeight */
            1080U,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_INTERLACED,
        },
        {
            /* Field Merge */
            TRUE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_DEFAULT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA2EX),
    },
#endif
#ifdef TDA3XX_FAMILY_BUILD
    {       /* testDescStr */
        "DSS Video1     (YUY422I)                   -> DPI1 -> SD-VENC(NTSC)",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            0,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard[] */
        {
            FVID2_STD_NTSC,
        },
        /* isSdVenc */
        TRUE,
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,
        },
        {
            /* inWidth */
            720,
        },
        {
            /* inHeight */
            480,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_INTERLACED,
        },
        {
            /* Field Merge */
            TRUE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_DEFAULT,
        /* boardId */
        (BSP_BOARD_BASE_TDA3XX | BSP_BOARD_MULTIDES),
    },
    {       /* testDescStr */
        "DSS Video1     (YUY422I)                   -> DPI1 -> SD-VENC(PAL)",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            0,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard[] */
        {
            FVID2_STD_PAL,
        },
        /* isSdVenc */
        TRUE,
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        {
            /* inDataFmt */
            FVID2_DF_YUV422I_YUYV,
        },
        {
            /* inWidth */
            720,
        },
        {
            /* inHeight */
            576,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_INTERLACED,
        },
        {
            /* Field Merge */
            TRUE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_DEFAULT,
        /* boardId */
        (BSP_BOARD_BASE_TDA3XX | BSP_BOARD_MULTIDES),
    },
    {       /* testDescStr */
        "DSS Video1     (BGR888)                    -> DPI1 -> SD-VENC(NTSC)",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            0,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard[] */
        {
            FVID2_STD_NTSC,
        },
        /* isSdVenc */
        TRUE,
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        {
            /* inDataFmt */
            FVID2_DF_BGR24_888,
        },
        {
            /* inWidth */
            720,
        },
        {
            /* inHeight */
            480,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_INTERLACED,
        },
        {
            /* Field Merge */
            TRUE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_DEFAULT,
        /* boardId */
        (BSP_BOARD_BASE_TDA3XX | BSP_BOARD_MULTIDES),
    },
    {       /* testDescStr */
        "DSS Video1     (BGR888)                    -> DPI1 -> SD-VENC(PAL)",
        1U, /* num of encoders*/
        /* encDrvId[] */
        {
            0,
        },
        /* vencId[] */
        {
            VPS_DCTRL_DSS_VENC_LCD1,
        },
        /* standard[] */
        {
            FVID2_STD_PAL,
        },
        /* isSdVenc */
        TRUE,
        /* numofHandles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        {
            /* inDataFmt */
            FVID2_DF_BGR24_888,
        },
        {
            /* inWidth */
            720,
        },
        {
            /* inHeight */
            576,
        },
        /* Posx*/
        {
            0U,
        },
        /* Poxy*/
        {
            0U,
        },
        {
            /* Scan Format */
            FVID2_SF_INTERLACED,
        },
        {
            /* Field Merge */
            TRUE,
        },
        /* runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_DEFAULT,
        /* boardId */
        (BSP_BOARD_BASE_TDA3XX | BSP_BOARD_MULTIDES),
    },
#endif /* TDA3XX_FAMILY_BUILD */
};

#define DISP_APP_NUM_TESTS              (sizeof (gDispAppTestPrms) / \
                                         sizeof (gDispAppTestPrms[0U]))

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef DISPLAY_DSS_MAIN_H_ */
