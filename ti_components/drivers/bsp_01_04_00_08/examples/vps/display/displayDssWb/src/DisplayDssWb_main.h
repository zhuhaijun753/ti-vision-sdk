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

#ifndef DISPLAY_DSS_WB_MAIN_H_
#define DISPLAY_DSS_WB_MAIN_H_

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
#include <soc_defines.h>
#ifdef VPS_DSS_BUILD
#include <vps/vps_display.h>
#include <vps/vps_displayCtrl.h>
#endif
#include <vps/vps_captureDssWb.h>
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

/* Worst case frames per handle */
#define DISP_APP_WB_MAX_FRAMES_PER_HANDLE  (4U)

#define DISP_APP_WB_INST_MAX (1U)
/* Padding required for allocating extra memory. */
#define DISP_APP_PADDING_LINES          (0U)

/* Default run count in seconds in case of EVM else this is in frame count. */
#define DISP_APP_RUN_COUNT              (5U)

/* Buffer width in pixels to allocate. */
#define DISP_APP_BUF_WIDTH              (1920U)
/* Buffer height in lines to allocate. */
#define DISP_APP_BUF_HEIGHT             (1080U)

/* Flag used to set in test params input width and height so that the detected
 * LCD width and height is used. This is kept same as LCD width/height so
 * that the same code works for Zebu as well */
#define DISP_APP_USE_LCD_WIDTH          (5000U)
#define DISP_APP_USE_LCD_HEIGHT         (5001U)
#define DISP_APP_USE_LCD_WIDTH_BY2      (5002U)
#define DISP_APP_USE_LCD_HEIGHT_BY2     (5003U)
#define DISP_APP_USE_LCD_HEIGHT_MINUS10 (5004U)

/* Other hard coded parameters */
#define DISP_APP_NUM_CAPT_CH            (1U)
#define DISP_APP_NUM_CAPT_STREAM        (1U)

/* Maximum number of buffers to allocate. */
#define DISP_APP_MAX_BUFFERS            (10U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Forward declaration for common object. */
typedef struct DispWbApp_Obj_t DispWbApp_Obj;

/**
 *  \brief Display application test parameters.
 *  The test case execution happens based on values of this structure
 */
typedef struct
{
    UInt32             testId;
    /**< Test Id. */
    Char              *testDescStr;
    /**< Test description. */

    UInt32             numEnc;
    /**< Number of Video Encoders to run with. */
    UInt32             encDrvId[VPS_DISP_ENC_INST_MAX];
    /**< Video encoder driver ID to open for each handle. */
    UInt32             vencId[VPS_DISP_ENC_INST_MAX];
    /**< Venc ID for each handle. */
    Fvid2_Standard     standard[VPS_DISP_ENC_INST_MAX];
    /**< Video encoder video standard. */
    UInt32             isSdVenc;
    /**< True for SD VENC and false for others. Valid only for Tda3xx. */

    UInt32             numHandles;
    /**< Number of display handles to run with. */
    UInt32             numCaptHandles;
    /**< Number of display handles to run with(Used For WB). */
    UInt32             instId[VPS_DISP_INST_MAX];
    /**< Instance ID to open for each handle. */
    UInt32             captInstId[VPS_CAPT_INST_MAX];
    /**< Instance ID to open for each handle. */

    Fvid2_DataFormat   inDataFmt[VPS_DISP_INST_MAX];
    /**< YUV or RGB data format. */

    UInt32             inWidth[VPS_DISP_INST_MAX];
    /**< Input buffer resolution width in pixels. */
    UInt32             inHeight[VPS_DISP_INST_MAX];
    /**< Input buffer resolution height in lines. */
    UInt32             posx[VPS_DISP_INST_MAX];
    /**< Input buffer position x. */
    UInt32             posy[VPS_DISP_INST_MAX];
    /**< Input buffer position y. */
    UInt32             inScanFormat[VPS_DISP_INST_MAX];
    /**< In scan format. */
    UInt32             isFieldMerge[VPS_DISP_INST_MAX];
    /**< Field merge or field separated. */
    Int32              runCount;
    /**< Number of frames to display. */

    UInt32             wbInSourceWidth[VPS_DISP_INST_MAX];
    /**< Input width of overlay feeding Writeback pipeline. */
    UInt32             wbInSourceHeight[VPS_DISP_INST_MAX];
    /**< Input height of overlay feeding Writeback pipeline. */
    UInt32             wbInWidth[VPS_DISP_INST_MAX];
    /**< Input width for Writeback pipeline. */
    UInt32             wbInHeight[VPS_DISP_INST_MAX];
    /**< Input height for Writeback pipeline. */
    Fvid2_DataFormat   wbDataFmt[VPS_DISP_INST_MAX];
    /**< YUV or RGB data format. */
    UInt32             wbWidth[VPS_DISP_INST_MAX];
    /**< Output width in pixels for WB Pipeline. */
    UInt32             wbHeight[VPS_DISP_INST_MAX];
    /**< Output height in pixels for WB Pipeline. */
    UInt32             wbposx[VPS_DISP_INST_MAX];
    /**< Input position x for WB pipeline. */
    UInt32             wbposy[VPS_DISP_INST_MAX];
    /**< Input position y  for WB pipeline. */
    UInt32             wbScanFormat[VPS_DISP_INST_MAX];
    /**< Output scan format. */
    UInt32             wbFieldMerge[VPS_DISP_INST_MAX];
    /**< Field merge or field separated. */

    Fvid2_VideoIfMode  captVideoIfMode;
    /**< Capture mode, single channel, multi-channel etc */
    Fvid2_VideoIfWidth captVideoIfWidth;
    /**< 8/16/24-bit mode. */

    Int32              wbrunCount;
    /**< Number of frames to display. */
    Bsp_BoardMode      boardMode;
    /**< Board mode param like 24-bit, 8-bit. */
    UInt32             boardId;
    /**< List of valid boards to run the test case. */
} DispWbApp_TestParams;

/**
 *  \brief Driver instance information.
 */
typedef struct
{
    UInt32                     instId;
    /**< Instance ID. */
    UInt32                     captInstId;
    /**< Instance ID. */
    UInt32                     encDrvId;
    /**< Encoder driver ID. */

    Vps_DispCreateParams       createPrms;
    /**< Create time parameters. */
    Vps_DispCreateStatus       createStatus;
    /**< Create status returned by driver during Fvid2_create(). */
    Vps_CaptCreateParams       captCreatePrms;
    /**< Capture create time parameters. */
    Vps_CaptCreateStatus       captCreateStatus;
    /**< Capture create status returned by driver during Fvid2_create(). */

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
    Fvid2_Frame                wbFrames[DISP_APP_WB_MAX_FRAMES_PER_HANDLE];
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

    UInt32                     wbFieldMerge;
    /**< Field merge or field separated. */

    UInt32                     wbInSourceWidth;
    /**< Width of Overlay which feeds wb pipeline. */
    UInt32                     wbInSourceHeight;
    /**< height of Overlay which feeds wb pipeline. */
    Fvid2_DataFormat           wbInSourceDataFmt;
    /**< output data format of Overlay which feeds wb pipeline. */

    UInt32                     wbInWidth;
    /**< input width for wb pipeline. Same as wbInSourceWidth if crop not
     *required */
    UInt32                     wbInHeight;
    /**< input height for wb pipeline. Same as wbInSourceHeight if crop not
     *required */

    UInt32                     wbWidth;
    /**< Output buffer resolution width in pixels. */

    UInt32                     wbHeight;
    /**< Output buffer resolution height in lines. */

    Fvid2_DataFormat           wbDataFmt;
    /**< YUV or RGB data format of wb pipeline output. */

    UInt32                     wbPosx;
    /**< Input buffer position x. */

    UInt32                     wbPosy;
    /**< Input buffer position y. */

    UInt32                     wbScanFormat;
    /**< Scan Format. For valid values see #Fvid2_ScanFormat. */

    UInt32                     wbFramesSize;

    Fvid2_Handle               encHandle;
    /**< FVID2 encoder driver handle. */

    DispWbApp_Obj             *appObj;
    /**< Reference pointer to application common object. */
} DispWbApp_InstObj;

/**
 *  \brief Test application data structure.
 */
struct DispWbApp_Obj_t
{
    DispWbApp_InstObj           instObj[VPS_DISP_INST_MAX +
                                        DISP_APP_WB_INST_MAX];
    /**< Driver instance objects. */
    DispWbApp_TestParams        testPrms;
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
    UInt32                      callBackCountWb;
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
} DispWbApp_LoadBufCfg;

/**
 *  \brief Buffer info structure.
 */
typedef struct
{
    UInt8               *bufAddr;
    /**< Buffer address. */
    UInt32               bufSize;
    /**< One buffer size in bytes. */
    UInt32               totalBufSize;
    /**< Total buffer size in bytes. */
    void                *yBufAddrEven[DISP_APP_MAX_BUFFERS];
    /**< Pointer to even luma for each buffer. */
    void                *yBufAddrOdd[DISP_APP_MAX_BUFFERS];
    /**< Pointer to odd luma for each buffer. */
    void                *cBufAddrEven[DISP_APP_MAX_BUFFERS];
    /**< Pointer to even chroma for each buffer. */
    void                *cBufAddrOdd[DISP_APP_MAX_BUFFERS];
    /**< Pointer to odd chroma for each buffer. */
    void                *bgrBufAddr[DISP_APP_MAX_BUFFERS];
    /**< Pointer to BGR data for each buffer. */
    DispWbApp_LoadBufCfg bufCfg;
    /**< Buffer configuration. */
} DispWbApp_BufInfo;

/**
 *  \brief used for updating variables based on detected LCD parameters.
 */
typedef enum
{
    DISPWBAPP_FIELD_LCD_HEIGHT = 0,
    /**< Update Height parameter. */
    DISPWBAPP_FIELD_LCD_WIDTH,
    /**< Update Width parameter. */
    DISPWBAPP_FIELD_MAX
    /**< Max Value. */
} DispWbApp_LcdFieldType;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/** \brief Defines the various load buffer configuration. */
static const DispWbApp_LoadBufCfg gDispDssLoadBufCfg[] =
{
    /* width, height, pitch, dataFmt, scanFmt, fieldsMerged, numBuffers */
    {DISP_APP_BUF_WIDTH, DISP_APP_BUF_HEIGHT,
     (DISP_APP_BUF_WIDTH * 2), FVID2_DF_YUV422I_YUYV,
     FVID2_SF_PROGRESSIVE,
     FALSE,
     4u},
    {DISP_APP_BUF_WIDTH, DISP_APP_BUF_HEIGHT,
     (DISP_APP_BUF_WIDTH * 3), FVID2_DF_BGR24_888,
     FVID2_SF_PROGRESSIVE,
     FALSE,
     4u},
};

/* None */
static const DispWbApp_TestParams gDispWbAppTestPrms[] =
{
    {
        /* test Id */
        0,
        /* testDescStr */
        "DSS Video1 (YUYV422I input)-> DPI1 (LCD) -> WB (LCD_WIDTH X LCD_HEIGHT YUYV422I) ",
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
        FALSE,                                      /* isSdVenc */
        /* numofHandles */
        1U,
        /* num of Capture Handles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        /* Capt instId[] */
        {
            VPS_CAPT_INST_DSS_WB1,
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

        {
            /* wb in source width */
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* wb in source height */
            DISP_APP_USE_LCD_HEIGHT,
        },
        {
            /* wb in width */
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* wb in height */
            DISP_APP_USE_LCD_HEIGHT,
        },
        {
            /* wbDataFmt */
            FVID2_DF_YUV422I_YUYV,
        },
        {
            /* wbWidth */
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* wbHeight */
            DISP_APP_USE_LCD_HEIGHT,
        },
        /* wb Posx*/
        {
            0U,
        },
        /* wb Poxy*/
        {
            0U,
        },
        {
            /* wb Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* wb Field Merge */
            FALSE,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        /* wb runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX),
    },
    {
        /* test Id */
        1,
        /* testDescStr */
        "DSS Video1 (YUYV422I input)-> DPI1 (LCD) -> WB (LCD_WIDTH X LCD_HEIGHT BGR24)",
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
        FALSE,                                      /* isSdVenc */
        /* numofHandles */
        1U,
        /* num of Capture Handles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        /* Capt instId[] */
        {
            VPS_CAPT_INST_DSS_WB1,
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

        {
            /* wb in source width */
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* wb in source height */
            DISP_APP_USE_LCD_HEIGHT,
        },
        {
            /* wb in width */
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* wb in height */
            DISP_APP_USE_LCD_HEIGHT,
        },
        {
            /* wbDataFmt */
            FVID2_DF_BGR24_888,
        },
        {
            /* wbWidth */
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* wbHeight */
            DISP_APP_USE_LCD_HEIGHT,
        },
        /* wb Posx*/
        {
            0U,
        },
        /* wb Poxy*/
        {
            0U,
        },
        {
            /* wb Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* wb Field Merge */
            FALSE,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        /* wb runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX),
    },
    {
        /* test Id */
        2,
        /* testDescStr */
        "DSS Video1 (YUYV422I input)-> DPI1 (LCD) -> WB (Scaled output: (LCD_WIDTH/2) X (LCD_HEIGHT/2) YUYV422I)",
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
        FALSE,                                      /* isSdVenc */
        /* numofHandles */
        1U,
        /* num of Capture Handles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        /* Capt instId[] */
        {
            VPS_CAPT_INST_DSS_WB1,
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

        {
            /* wb in source width */
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* wb in source height */
            DISP_APP_USE_LCD_HEIGHT,
        },
        {
            /* wb in width */
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* wb in height */
            DISP_APP_USE_LCD_HEIGHT,
        },
        {
            /* wbDataFmt */
            FVID2_DF_YUV422I_YUYV,
        },
        {
            /* wbWidth */
            DISP_APP_USE_LCD_WIDTH_BY2,
        },
        {
            /* wbHeight */
            DISP_APP_USE_LCD_HEIGHT_BY2,
        },
        /* wb Posx*/
        {
            0U,
        },
        /* wb Poxy*/
        {
            0U,
        },
        {
            /* wb Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* wb Field Merge */
            FALSE,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        /* wb runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX),
    },
    {
        /* test Id */
        3,
        /* testDescStr */
        "DSS Video1 (YUYV422I input)-> DPI1 (LCD) -> WB (Scaled output: (LCD_WIDTH/2) X (LCD_HEIGHT/2) BGR24)",
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
        FALSE,                                      /* isSdVenc */
        /* numofHandles */
        1U,
        /* num of Capture Handles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        /* Capt instId[] */
        {
            VPS_CAPT_INST_DSS_WB1,
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

        {
            /* wb in source width */
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* wb in source height */
            DISP_APP_USE_LCD_HEIGHT,
        },
        {
            /* wb in width */
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* wb in height */
            DISP_APP_USE_LCD_HEIGHT,
        },
        {
            /* wbDataFmt */
            FVID2_DF_BGR24_888,
        },
        {
            /* wbWidth */
            DISP_APP_USE_LCD_WIDTH_BY2,
        },
        {
            /* wbHeight */
            DISP_APP_USE_LCD_HEIGHT_BY2,
        },
        /* wb Posx*/
        {
            0U,
        },
        /* wb Poxy*/
        {
            0U,
        },
        {
            /* wb Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* wb Field Merge */
            FALSE,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        /* wb runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX),
    },
    {
        /* test Id */
        4,
        /* testDescStr */
        "DSS Video1 (BGR24 888 input)-> DPI1 (LCD) -> WB (LCD_WIDTH X LCD_HEIGHT BGR24 888 output)",
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
        FALSE,                                      /* isSdVenc */
        /* numofHandles */
        1U,
        /* num of Capture Handles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        /* Capt instId[] */
        {
            VPS_CAPT_INST_DSS_WB1,
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

        {
            /* wb in source width */
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* wb in source height */
            DISP_APP_USE_LCD_HEIGHT,
        },
        {
            /* wb in width */
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* wb in height */
            DISP_APP_USE_LCD_HEIGHT,
        },
        {
            /* wbDataFmt */
            FVID2_DF_BGR24_888,
        },
        {
            /* wbWidth */
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* wbHeight */
            DISP_APP_USE_LCD_HEIGHT,
        },
        /* wb Posx*/
        {
            0U,
        },
        /* wb Poxy*/
        {
            0U,
        },
        {
            /* wb Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* wb Field Merge */
            FALSE,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        /* wb runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX),
    },
#ifdef TDA3XX_FAMILY_BUILD
    {
        /* test Id */
        5,
        /* testDescStr */
        "DSS Video1 (YUYV422I input)-> DPI1 SIL9022A-HDMI@1080P60 -> WB (1280X800 YUV422) ",
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
        /* num of Capture Handles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        /* Capt instId[] */
        {
            VPS_CAPT_INST_DSS_WB1,
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

        {
            /* wb in source width */
            1920U,
        },
        {
            /* wb in source height */
            1080
        },
        {
            /* wb in width */
            1920,
        },
        {
            /* wb in height */
            1080,
        },
        {
            /* wbDataFmt */
            FVID2_DF_YUV422I_YUYV,
        },
        {
            /* wbWidth */
            1280,
        },
        {
            /* wbHeight */
            800,
        },
        /* wb Posx*/
        {
            0U,
        },
        /* wb Poxy*/
        {
            0U,
        },
        {
            /* wb Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* wb Field Merge */
            FALSE,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        /* wb runCount */
        15,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX),
    },
    {
        /* test Id */
        6,
        /* testDescStr */
        "DSS Video1 (YUYV422I input)-> DPI1 SIL9022A-HDMI@1080P60 -> WB (800X480 BGR888) ",
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
        /* num of Capture Handles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        /* Capt instId[] */
        {
            VPS_CAPT_INST_DSS_WB1,
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

        {
            /* wb in source width */
            1920U,
        },
        {
            /* wb in source height */
            1080
        },
        {
            /* wb in width */
            1920,
        },
        {
            /* wb in height */
            1080,
        },
        {
            /* wbDataFmt */
            FVID2_DF_BGR24_888,
        },
        {
            /* wbWidth */
            800,
        },
        {
            /* wbHeight */
            480,
        },
        /* wb Posx*/
        {
            0U,
        },
        /* wb Poxy*/
        {
            0U,
        },
        {
            /* wb Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* wb Field Merge */
            FALSE,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        /* wb runCount */
        15,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX),
    },
    {
        /* test Id */
        7,
        /* testDescStr */
        "DSS Video1 (YUYV422I input)-> DPI1 SD - Venc (NTSC)-> WB (YUYV422I)",
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
        /* num of Capture Handles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        /* Capt instId[] */
        {
            VPS_CAPT_INST_DSS_WB1,
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

        {
            /* wb in source width */
            720,
        },
        {
            /* wb in source height */
            480,
        },
        {
            /* wb in width */
            720,
        },
        {
            /* wb in height */
            480,
        },
        {
            /* wbDataFmt */
            FVID2_DF_YUV422I_YUYV,
        },
        {
            /* wbWidth */
            720,
        },
        {
            /* wbHeight */
            480,
        },
        /* wb Posx*/
        {
            0U,
        },
        /* wb Poxy*/
        {
            0U,
        },
        {
            /* wb Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* wb Field Merge */
            FALSE,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        /* wb runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX),
    },
    {
        /* test Id */
        8,
        /* testDescStr */
        "DSS Video1 (YUYV422I input)-> DPI1 SD - Venc (PAL) -> WB (YUYV422I)",
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
        /* num of Capture Handles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        /* Capt instId[] */
        {
            VPS_CAPT_INST_DSS_WB1,
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

        {
            /* wb in source width */
            720,
        },
        {
            /* wb in source height */
            576,
        },
        {
            /* wb in width */
            720,
        },
        {
            /* wb in height */
            576,
        },
        {
            /* wbDataFmt */
            FVID2_DF_YUV422I_YUYV,
        },
        {
            /* wbWidth */
            720,
        },
        {
            /* wbHeight */
            576,
        },
        /* wb Posx*/
        {
            0U,
        },
        /* wb Poxy*/
        {
            0U,
        },
        {
            /* wb Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* wb Field Merge */
            FALSE,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        /* wb runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX),
    },
    {
        /* test Id */
        9,
        /* testDescStr */
        "DSS Video1 (YUYV422I input)-> DPI1 (LCD) -> WB SC BGR24(Region Based first quadrant)",
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
        FALSE,                                      /* isSdVenc */
        /* numofHandles */
        1U,
        /* num of Capture Handles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        /* Capt instId[] */
        {
            VPS_CAPT_INST_DSS_WB1,
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

        {
            /* wb in source width */
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* wb in source height */
            DISP_APP_USE_LCD_HEIGHT,
        },
        {
            /* wb in width */
            DISP_APP_USE_LCD_WIDTH_BY2,
        },
        {
            /* wb in height */
            DISP_APP_USE_LCD_HEIGHT_BY2,
        },
        {
            /* wbDataFmt */
            FVID2_DF_BGR24_888,
        },
        {
            /* wbWidth */
            DISP_APP_USE_LCD_WIDTH_BY2,
        },
        {
            /* wbHeight */
            DISP_APP_USE_LCD_HEIGHT_BY2,
        },
        /* wb Posx*/
        {
            0U,
        },
        /* wb Poxy*/
        {
            0U,
        },
        {
            /* wb Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* wb Field Merge */
            FALSE,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        /* wb runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX),
    },
    {
        /* test Id */
        10,
        /* testDescStr */
        "DSS Video1 (YUYV422I input)-> DPI1 (LCD) -> BGR24(Region Based last quadrant)",
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
        FALSE,                                      /* isSdVenc */
        /* numofHandles */
        1U,
        /* num of Capture Handles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        /* Capt instId[] */
        {
            VPS_CAPT_INST_DSS_WB1,
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

        {
            /* wb in source width */
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* wb in source height */
            DISP_APP_USE_LCD_HEIGHT,
        },
        {
            /* wb in width */
            DISP_APP_USE_LCD_WIDTH_BY2,
        },
        {
            /* wb in height */
            DISP_APP_USE_LCD_HEIGHT_BY2,
        },
        {
            /* wbDataFmt */
            FVID2_DF_BGR24_888,
        },
        {
            /* wbWidth */
            DISP_APP_USE_LCD_WIDTH_BY2,
        },
        {
            /* wbHeight */
            DISP_APP_USE_LCD_HEIGHT_BY2,
        },
        /* wb Posx*/
        {
            DISP_APP_USE_LCD_WIDTH_BY2,
        },
        /* wb Poxy*/
        {
            DISP_APP_USE_LCD_HEIGHT_BY2,
        },
        {
            /* wb Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* wb Field Merge */
            FALSE,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        /* wb runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX),
    },
    {
        /* test Id */
        11,
        /* testDescStr */
        "DSS Video1 (YUYV422I input)-> DPI1 (LCD) -> WB (Region based First ten half line window)",
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
        FALSE,                                      /* isSdVenc */
        /* numofHandles */
        1U,
        /* num of Capture Handles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        /* Capt instId[] */
        {
            VPS_CAPT_INST_DSS_WB1,
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

        {
            /* wb in source width */
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* wb in source height */
            DISP_APP_USE_LCD_HEIGHT,
        },
        {
            /* wb in width */
            DISP_APP_USE_LCD_WIDTH_BY2,
        },
        {
            /* wb in height */
            10,
        },
        {
            /* wbDataFmt */
            FVID2_DF_BGR24_888,
        },
        {
            /* wbWidth */
            DISP_APP_USE_LCD_WIDTH_BY2,
        },
        {
            /* wbHeight */
            10,
        },
        /* wb Posx*/
        {
            0U,
        },
        /* wb Poxy*/
        {
            0U,
        },
        {
            /* wb Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* wb Field Merge */
            FALSE,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        /* wb runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX),
    },
    {
        /* test Id */
        12,
        /* testDescStr */
        "DSS Video1 (YUYV422I input)-> DPI1 (LCD) -> WB (Region based last ten half line window)",
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
        FALSE,                                      /* isSdVenc */
        /* numofHandles */
        1U,
        /* num of Capture Handles */
        1U,
        /* instId[] */
        {
            VPS_DISP_INST_DSS_VID1,
        },
        /* Capt instId[] */
        {
            VPS_CAPT_INST_DSS_WB1,
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

        {
            /* wb in source width */
            DISP_APP_USE_LCD_WIDTH,
        },
        {
            /* wb in source height */
            DISP_APP_USE_LCD_HEIGHT,
        },
        {
            /* wb in width */
            DISP_APP_USE_LCD_WIDTH_BY2,
        },
        {
            /* wb in height */
            10,
        },
        {
            /* wbDataFmt */
            FVID2_DF_BGR24_888,
        },
        {
            /* wbWidth */
            DISP_APP_USE_LCD_WIDTH_BY2,
        },
        {
            /* wbHeight */
            10,
        },
        /* wb Posx*/
        {
            DISP_APP_USE_LCD_WIDTH_BY2,
        },
        /* wb Poxy*/
        {
            (DISP_APP_USE_LCD_HEIGHT_MINUS10),
        },
        {
            /* wb Scan Format */
            FVID2_SF_PROGRESSIVE,
        },
        {
            /* wb Field Merge */
            FALSE,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        /* wb runCount */
        DISP_APP_RUN_COUNT,
        /* boardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX),
    },
#endif
};

#define DISP_WB_APP_NUM_TESTS              (sizeof (gDispWbAppTestPrms) / \
                                            sizeof (gDispWbAppTestPrms[0U]))

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef DISPLAY_DSS_MAIN_H_ */
