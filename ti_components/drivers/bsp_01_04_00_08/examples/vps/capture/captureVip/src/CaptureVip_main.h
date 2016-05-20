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
 *  \file CaptureVip_main.h
 *
 *  \brief VIP capture driver sample application private header file.
 *
 */

#ifndef CAPTURE_VIP_MAIN_H_
#define CAPTURE_VIP_MAIN_H_

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

#include <common/bsp_types.h>
#include <common/trace.h>
#include <common/bsp_config.h>
#include <common/bsp_utils.h>
#include <osal/bsp_osal.h>
#include <fvid2/fvid2.h>
#include <platforms/bsp_platform.h>
#include <vps/vps.h>
#include <soc_defines.h>
#ifdef VPS_VIP_BUILD
#include <vps/vps_capture.h>
#endif
#include <devices/bsp_device.h>
#include <devices/bsp_videoDecoder.h>
#include <devices/bsp_videoSensor.h>
#include <boards/bsp_board.h>
#include <utility/bsputils_prf.h>
#include <utility/bsputils_app.h>
#include <utility/bsputils_mem.h>
#include <utility/bsputils_lvds.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Test application stack size */
#define CAPT_APP_TSK_STACK_MAIN         (10U * 1024U)

#define CAPT_APP_TSK_STACK_RESET        (10U * 1024)

/* Test application task priority */
#define CAPT_APP_TSK_PRI_MAIN           (10U)

#define APP_NAME                        "CAPT_VIP_APP"

/* Frames allocated per channel */
#define CAPT_APP_FRAMES_PER_CH          (4U)

/* Worst case frames per handle */
#define CAPT_APP_MAX_FRAMES_PER_HANDLE  (VPS_CAPT_STREAM_ID_MAX *   \
                                         VPS_CAPT_CH_PER_PORT_MAX * \
                                         CAPT_APP_FRAMES_PER_CH)

/* Padding required for allocating extra memory. */
#define CAPT_APP_PADDING_LINES          (0U)

/* Default run count in seconds in case of EVM else this is in frame count. */
#define CAPT_APP_RUN_COUNT              (5U)

/* SC enable/disable for different streams  */
#define CAPT_APP_SC_DISABLE_ALL         (0x00U)
#define CAPT_APP_SC_ENABLE_0            (0x01U)
#define CAPT_APP_SC_ENABLE_1            (0x02U)
#define CAPT_APP_SC_ENABLE_ALL          (CAPT_APP_SC_ENABLE_0 | \
                                         CAPT_APP_SC_ENABLE_1)

/**
 * There are 3 32-bit MAX_SIZE registers supported for TDA2XX platform family.
 * These registers provide two parameters width[31:16] and height[15:0].
 * The VPDMA transmits to external buffer the maximum out width number of
 * pixels and maximum out height number of pixel lines.
 * If the VIP receives data exceeding the maximum out width/height then it
 * continues to capture the data. VPDMA will not transfer it to the
 * external buffer.
 * This register (if used) should have valid range of values.
 * The valid range for maximum out width shall be [1, 4096]
 * The valid range for maximum out height shall be [1, 2048]
 * Example: For a YUV420SP capture,
 * For luma, the maximum out [width, height] can go up to [2048, 2048].
 * For chroma, the maximum out [width, height] can go up to [2048, 1024].
 * Example: For a YUV422I capture,
 * For luma, the maximum out [width, height] can go up to [4096, 2048].
 */
/* MAX SIZE Register Width and Height configurations */
#define CAPT_APP_MAXSIZE_1_WIDTH        (1920U)
#define CAPT_APP_MAXSIZE_2_WIDTH        (1920U)
#define CAPT_APP_MAXSIZE_3_WIDTH        (1280U)
#define CAPT_APP_MAXSIZE_1_HEIGHT       (1080U)
#define CAPT_APP_MAXSIZE_2_HEIGHT       (540U)
#define CAPT_APP_MAXSIZE_3_HEIGHT       (800U)

/* Capture frame skip pattern - No skip by default */
#define CAPT_APP_FRAME_SKIP_PATTERN     (0x00000000U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Forward declaration for common object. */
typedef struct CaptApp_Obj_t CaptApp_Obj;

/**
 *  \brief Capture application test parameters.
 *  The test case execution happens based on values of this structure
 */
typedef struct
{
    Char              *testDescStr;
    /**< Test description. */
    UInt32             numCh;
    /**< Number of channel in multi-ch case, must be 1 for single channel. */
    UInt32             numHandles;
    /**< Number of capture handles to run with. */
    UInt32             instId[VPS_CAPT_INST_MAX];
    /**< Instance ID to open for each handle. */

    UInt32             decDrvId[VPS_CAPT_INST_MAX];
    /**< Video decoder driver ID to open for each handle. */

    Fvid2_VideoIfMode  videoIfMode;
    /**< Capture mode, single channel, multi-channel etc */
    Fvid2_VideoIfWidth videoIfWidth;
    /**< 8/16/24-bit mode. */

    Fvid2_Standard     standard;
    /**< Video decoder video standard. */

    Fvid2_DataFormat   inDataFmt;
    /**< YUV or RGB data format. */
    UInt32             numStream;
    /**< Number of outputs. */
    Fvid2_DataFormat   outDataFmt[VPS_CAPT_STREAM_ID_MAX];
    /**< Output format of each output. */
    UInt32             scEnable;
    /**< Enable scaler in capture path.
     *   CAPT_APP_SC_DISABLE_ALL: SC Disabled,
     *   CAPT_APP_SC_ENABLE_0: SC enabled for stream 0
     *   CAPT_APP_SC_ENABLE_1: SC enable for stream 1
     *   CAPT_APP_SC_ENABLE_ALL: SC enabled for stream 0 and 1. */

    UInt32             inWidth;
    /**< Input resolution width in pixels - used in case scaler is used. */
    UInt32             inHeight;
    /**< Input resolution height in lines - used in case scaler is used. */
    UInt32             outWidth[VPS_CAPT_STREAM_ID_MAX];
    /**< Scaler output resolution width in pixels - used in case scaler is
     *   used. Otherwise this should be same as that of input width. */
    UInt32             outHeight[VPS_CAPT_STREAM_ID_MAX];
    /**< Scaler output resolution height in lines - used in case scaler is
     *   used. Otherwise this should be same as that of input height. */

    Int32              runCount;
    /**< Number of frames to capture. */
    Bsp_BoardMode      boardMode;
    /**< Capture board mode param like 24-bit, 8-bit. */
    UInt32             boardId;
    /**< List of valid boards to run the test case. */

    UInt32             testId;
    /**< Test ID for print purpose. This is initialized in the code */
} CaptApp_TestParams;

/**
 *  \brief Driver instance information.
 */
typedef struct
{
    UInt32               instId;
    /**< Instance ID. */
    UInt32               decDrvId;
    /**< Decoder driver ID. */

    Vps_CaptCreateParams createPrms;
    /**< Create time parameters. */
    Vps_CaptCreateStatus createStatus;
    /**< Create status returned by driver during Fvid2_create(). */
    Vps_CaptVipParams    vipPrms;
    /**< VIP hardware specific parameters. */
    Vps_VipPortConfig    vipPortCfg;
    /**< VIP port configuration. */
    Vps_CaptVipScParams  scPrms;
    /**< SC configuration. */

    UInt32               maxOutWidth[VPS_VPDMA_NUM_MAXSIZE_REG];
    /**<
     *   maxOutWidth:
     *   This the Maximum Width value that shall be used to set the
     *   MAX_SIZE registers.
     *   Maximum Width of the frame/field that shall be transmitted to the
     *   external buffer. If the captured width received exceeds this then
     *   only maxOutWidth number of pixels per line is transmitted to the
     *   external buffer. */
    UInt32               maxOutHeight[VPS_VPDMA_NUM_MAXSIZE_REG];
    /**<
     *   maxOutHeight:
     *   This the Maximum Height value that shall be used to set the
     *   MAX_SIZE registers.
     *   Maximum Height of the frame/field  that shall be transmitted to the
     *   external buffer. If the captured height received exceeds this then
     *   only maxOutHeight number of lines is transmitted to the external
     *   buffer.
     */

    Fvid2_Handle              drvHandle;
    /**< FVID2 capture driver handle. */
    Fvid2_CbParams            cbPrms;
    /**< Callback params. */

    Fvid2_Frame               frames[CAPT_APP_MAX_FRAMES_PER_HANDLE];
    /**< FVID2 Frames that will be used for capture. */
    Fvid2_Format              allocFmt[VPS_CAPT_STREAM_ID_MAX];
    /**< Format passed to utils frame alloc function. */

    Fvid2_Handle              decHandle;
    /**< FVID2 decoder/sensor driver handle. */
    Bsp_VidDecCreateParams    decCreatePrms;
    /**< Video decoder create params. */
    Bsp_VidDecVideoModeParams decVideoModePrms;
    /**< Video decoder mode params. */
    Bsp_VidSensorCreateParams sensorCreatePrms;
    /**< Video sensor create params. */

    CaptApp_Obj              *appObj;
    /**< Reference pointer to application common object. */
    UInt32                    overflowCount;
    /**< Store the count of the overflow. */
} CaptApp_InstObj;

/**
 *  \brief Test application data structure.
 */
struct CaptApp_Obj_t
{
    CaptApp_InstObj    instObj[VPS_CAPT_INST_MAX];
    /**< Driver instance objects. */
    CaptApp_TestParams testPrms;
    /**< Current test parameters. */

    Fvid2_Handle       fvidHandleAll;
    /**< Global capture handle. */
    Task_Handle        tskHandle;
    /**< Test task handle. */
    Task_Handle        resetTskHandle;
    /**< Reset task handle. */

    UInt32             maxWidth;
    /**< Max width in pixels - used for buffer allocation for all instance. */
    UInt32             maxHeight;
    /**< Max height in lines - used for buffer allocation for all instance. */

    UInt32             totalFldCount;
    /**< Count of all frames captured. */
    UInt32             totalCpuLoad;
    /**< Accumulated CPU load - added every frame. */
    UInt32             cpuLoadCount;
    /**< CPU load count used to get average CPU load - incremented every
     *   accumulation. */
    UInt32             callBackCount;
    /**< Callback count - used in case of sim/zebu to enable loop count in
     *   frames. */
    UInt32             enableAutoRun;
    /**< Auto-run enable flag. */

    UInt32             startTime;
    /**< Application start time in clock ticks. */
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

static CaptApp_TestParams gCaptAppTestPrms[] =
{
    {
#ifdef TDA2EX_BUILD
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out",
#endif
        1U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
#ifdef TDA2EX_BUILD
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        {
            FVID2_VID_SENSOR_OV1063X_DRV,
        },
        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
        FVID2_VIFW_8BIT,
        FVID2_STD_720P_60,
        FVID2_DF_YUV422P,
        1U,                                 /* numStream */
        {
            FVID2_DF_YUV422I_YUYV
        },
        CAPT_APP_SC_DISABLE_ALL,
        1280U,                              /* inWidth */
        720U,                               /* inHeight */
        {1280U },                           /* outWidth[] */
        {720U  },                           /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_VIDEO_8BIT,
        (BSP_BOARD_VISION | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX),
    },
    {
#ifdef TDA2EX_BUILD
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I 800x480 Scaled out",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I 800x480 Scaled out",
#endif
        1U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
#ifdef TDA2EX_BUILD
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        {
            FVID2_VID_SENSOR_OV1063X_DRV,
        },
        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
        FVID2_VIFW_8BIT,
        FVID2_STD_720P_60,
        FVID2_DF_YUV422P,
        1U,                                 /* numStream */
        {
            FVID2_DF_YUV422I_YUYV
        },
        CAPT_APP_SC_ENABLE_0,
        1280U,                              /* inWidth */
        720U,                               /* inHeight */
        {800U  },                           /* outWidth[] */
        {480U  },                           /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_VIDEO_8BIT,
        (BSP_BOARD_VISION | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX),
    },

    {
#ifdef TDA2EX_BUILD
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUV422SP_UV out",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUV422SP_UV out",
#endif
        1U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
#ifdef TDA2EX_BUILD
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        {
            FVID2_VID_SENSOR_OV1063X_DRV,
        },
        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
        FVID2_VIFW_8BIT,
        FVID2_STD_720P_60,
        FVID2_DF_YUV422P,
        1U,                                 /* numStream */
        {
            FVID2_DF_YUV422SP_UV
        },
        CAPT_APP_SC_DISABLE_ALL,
        1280U,                              /* inWidth */
        720U,                               /* inHeight */
        {1280U },                           /* outWidth[] */
        {720U  },                           /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_VIDEO_8BIT,
        (BSP_BOARD_VISION | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX),
    },

    {
#ifdef TDA2EX_BUILD
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUYV422I 800x480 Scaled out, YUYV422I",
#else
        "OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), Dual out - YUYV422I 800x480 Scaled out, YUYV422I",
#endif
        1U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
#ifdef TDA2EX_BUILD
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        {
            FVID2_VID_SENSOR_OV1063X_DRV,
        },
        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
        FVID2_VIFW_8BIT,
        FVID2_STD_720P_60,
        FVID2_DF_YUV422P,
        2U,                                 /* numStream */
        {
            FVID2_DF_YUV422I_YUYV,
            FVID2_DF_YUV422I_YUYV
        },
        CAPT_APP_SC_ENABLE_0,
        1280U,                              /* inWidth */
        720U,                               /* inHeight */
        {800U, 1280U},                      /* outWidth[] */
        {480U, 720U},                       /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_VIDEO_8BIT,
        (BSP_BOARD_VISION | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX),
    },
#if (defined TDA3XX_FAMILY_BUILD)
    {
        "OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out",
        1U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
        },
        {
            FVID2_VID_SENSOR_OV1063X_DRV,
        },
        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
        FVID2_VIFW_8BIT,
        FVID2_STD_720P_60,
        FVID2_DF_YUV422P,
        1U,                                 /* numStream */
        {
            FVID2_DF_YUV422I_YUYV
        },
        CAPT_APP_SC_DISABLE_ALL,
        1280U,                              /* inWidth */
        720U,                               /* inHeight */
        {1280U },                           /* outWidth[] */
        {720U  },                           /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_VIDEO_8BIT,
        (BSP_BOARD_BASE_TDA3XX | BSP_BOARD_MULTIDES),
    },
#endif  /* #if (defined TDA3XX_FAMILY_BUILD) */
    {
#ifdef TDA2EX_BUILD
        "OV1063x(MULDES_CAM2)->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out",
#else
        "OV1063x(MULDES_CAM1)->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out",
#endif  /* #if (defined TDA2EX_BUILD) */
        1U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
        },
        {
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
        },
        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
        FVID2_VIFW_8BIT,
        FVID2_STD_720P_60,
        FVID2_DF_YUV422P,
        1U,                                 /* numStream */
        {
            FVID2_DF_YUV422I_YUYV
        },
        CAPT_APP_SC_DISABLE_ALL,
        1280U,                              /* inWidth */
        720U,                               /* inHeight */
        {1280U },                           /* outWidth[] */
        {720U  },                           /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_VIDEO_8BIT,
        (BSP_BOARD_MULTIDES),
    },
    {
        "OV1063x(MULDES_CAM1,2,3,4)->VIP SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out",
        1U,                                 /* numCh */
        4U,                                 /* numHandles */
        {
#if (defined TDA3XX_FAMILY_BUILD) || (defined TDA2EX_BUILD)
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTB),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S0, VPS_VIP_PORTA),
#endif      /* #ifdef TDA3XX_FAMILY_BUILD */
        },
        {
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
        },
        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
        FVID2_VIFW_8BIT,
        FVID2_STD_720P_60,
        FVID2_DF_YUV422P,
        1U,                                 /* numStream */
        {
            FVID2_DF_YUV422I_YUYV
        },
        CAPT_APP_SC_DISABLE_ALL,
        1280U,                              /* inWidth */
        720U,                               /* inHeight */
        {1280U },                           /* outWidth[] */
        {720U  },                           /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_VIDEO_8BIT,
        (BSP_BOARD_MULTIDES),
    },
#if (defined TDA2XX_BUILD) || (defined DRA7XX_BUILD)
    {
        "OV1063x(MULDES_CAM1,2,3,4,5,6)->VIP SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out",
        1U,                                 /* numCh */
        6U,                                 /* numHandles */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1, VPS_VIP_PORTB),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S1, VPS_VIP_PORTA),
        },
        {
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
        },
        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
        FVID2_VIFW_8BIT,
        FVID2_STD_720P_60,
        FVID2_DF_YUV422P,
        1U,                                 /* numStream */
        {
            FVID2_DF_YUV422I_YUYV
        },
        CAPT_APP_SC_DISABLE_ALL,
        1280U,                              /* inWidth */
        720U,                               /* inHeight */
        {1280U },                           /* outWidth[] */
        {720U  },                           /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_VIDEO_8BIT,
        (BSP_BOARD_MULTIDES),
    },
#endif  /* #if (defined TDA2XX_BUILD) || (defined DRA7XX_BUILD) */
    {
#ifdef TDA2EX_BUILD
        "LI OV1063x->VIP1_S1_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out",
#else
        "LI OV1063x->VIP1_S0_PORTA SCH 8-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out",
#endif
        1U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
#ifdef TDA2EX_BUILD
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        {
            FVID2_VID_SENSOR_LI_OV1063X_DRV,
        },
        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
        FVID2_VIFW_8BIT,
        FVID2_STD_720P_60,
        FVID2_DF_YUV422P,
        1U,                                 /* numStream */
        {
            FVID2_DF_YUV422I_YUYV
        },
        CAPT_APP_SC_DISABLE_ALL,
        1280U,                              /* inWidth */
        720U,                               /* inHeight */
        {1280U },                           /* outWidth[] */
        {720U  },                           /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_VIDEO_8BIT,
        (BSP_BOARD_BASE_TDA2XX | BSP_BOARD_VISION | BSP_BOARD_JAMR3 |
         BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX | BSP_BOARD_BASE_TDA2EX),
    },
    {
#ifdef TDA2EX_BUILD
        "Aptina AR0132->VIP1_S1_PORTA SCH 12-bit Discrete Sync (HSYNC/VSYNC), Bayer (GR) out",
#else
        "Aptina AR0132->VIP1_S0_PORTA SCH 12-bit Discrete Sync (HSYNC/VSYNC), Bayer (GR) out",
#endif
        1U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
#ifdef TDA2EX_BUILD
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        {
            FVID2_VID_SENSOR_APT_AR0132_DRV,
        },
        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
        FVID2_VIFW_16BIT,
        FVID2_STD_720P_60,
        FVID2_DF_RAW16,
        1U,                                 /* numStream */
        {
            FVID2_DF_RAW16
        },
        CAPT_APP_SC_DISABLE_ALL,
        1280U,                              /* inWidth */
        720U,                               /* inHeight */
        {1280U },                           /* outWidth[] */
        {720U  },                           /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_VIDEO_12BIT,
        (BSP_BOARD_VISION | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX),
    },
    {
#ifdef TDA2EX_BUILD
        "ADV7611->VIP1_S1_PORTA SCH 16-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out",
#else
        "ADV7611->VIP1_S0_PORTA SCH 16-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out",
#endif
        1U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
#ifdef TDA2EX_BUILD
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        {
            FVID2_VID_DEC_ADV7611_DRV,
        },
        FVID2_VIFM_SCH_DS_AVID_VSYNC,
        FVID2_VIFW_16BIT,
        FVID2_STD_CUSTOM,
        FVID2_DF_YUV422P,
        1U,                                 /* numStream */
        {
            FVID2_DF_YUV422I_YUYV
        },
        CAPT_APP_SC_DISABLE_ALL,
        1920U,                              /* inWidth */
        1080U,                              /* inHeight */
        {1920U },                           /* outWidth[] */
        {1080U },                           /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_VIDEO_16BIT,
        /* Note: Can't run in muldes board because of I2C conflict */
        (BSP_BOARD_BASE_TDA3XX | BSP_BOARD_VISION),
    },
#if (defined TDA2XX_BUILD) || (defined DRA7XX_BUILD) || (defined TDA2EX_BUILD)
    {
#ifdef TDA2EX_BUILD
        "SII9127->VIP1_S1_PORTA SCH 16-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out",
#else
        "SII9127->VIP1_S0_PORTA SCH 16-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out",
#endif
        1U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
#ifdef TDA2EX_BUILD
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        {
            FVID2_VID_DEC_SII9127_DRV,
        },
        FVID2_VIFM_SCH_DS_AVID_VSYNC,
        FVID2_VIFW_16BIT,
        FVID2_STD_CUSTOM,
        FVID2_DF_YUV422P,
        1U,                                 /* numStream */
        {
            FVID2_DF_YUV422I_YUYV
        },
        CAPT_APP_SC_DISABLE_ALL,
        1920U,                              /* inWidth */
        1080U,                              /* inHeight */
        {1920U },                           /* outWidth[] */
        {1080U },                           /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_VIDEO_16BIT,
        /* Note: Can't run in muldes board because of I2C conflict */
        (BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX),
    },
    {
#ifdef TDA2EX_BUILD
        "TVP5158->VIP1_S1_PORTA SCH D1 8-bit Embedded Sync, YUYV422I out",
#else
        "TVP5158->VIP1_S0_PORTA SCH D1 8-bit Embedded Sync, YUYV422I out",
#endif
        1U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
#ifdef TDA2EX_BUILD
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        {
            FVID2_VID_DEC_TVP5158_DRV,
        },
        FVID2_VIFM_SCH_ES,
        FVID2_VIFW_8BIT,
        FVID2_STD_D1,
        FVID2_DF_YUV422P,
        1U,                                 /* numStream */
        {
            FVID2_DF_YUV422I_YUYV
        },
        CAPT_APP_SC_DISABLE_ALL,
        720U,                               /* inWidth */
        240U,                               /* inHeight */
        {720U  },                           /* outWidth[] */
        {240U  },                           /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_VIDEO_BT656,
        (BSP_BOARD_VS | BSP_BOARD_VISION_TI81XX | BSP_BOARD_JAMR3),
    },
    {
#ifdef TDA2EX_BUILD
        "TVP5158->VIP1_S1_PORTA 4-CH D1 8-bit Pixel Multiplexed Embedded Sync, YUYV422I out",
#else
        "TVP5158->VIP1_S0_PORTA 4-CH D1 8-bit Pixel Multiplexed Embedded Sync, YUYV422I out",
#endif
        4U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
#ifdef TDA2EX_BUILD
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        {
            FVID2_VID_DEC_TVP5158_DRV,
        },
        FVID2_VIFM_MCH_PIXEL_MUX_ES,
        FVID2_VIFW_8BIT,
        FVID2_STD_MUX_4CH_D1,
        FVID2_DF_YUV422P,
        1U,                                 /* numStream */
        {
            FVID2_DF_YUV422I_YUYV
        },
        CAPT_APP_SC_DISABLE_ALL,
        720U,                               /* inWidth */
        240U,                               /* inHeight */
        {720U  },                           /* outWidth[] */
        {240U  },                           /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_VIDEO_BT656,
        (BSP_BOARD_VS | BSP_BOARD_VISION_TI81XX | BSP_BOARD_JAMR3),
    },
    {
#ifdef TDA2EX_BUILD
        "TVP5158->VIP1_S1_PORTA 4-CH D1 8-bit Line Multiplexed Embedded Sync, YUYV422I out",
#else
        "TVP5158->VIP1_S0_PORTA 4-CH D1 8-bit Line Multiplexed Embedded Sync, YUYV422I out",
#endif
        4U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
#ifdef TDA2EX_BUILD
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        {
            FVID2_VID_DEC_TVP5158_DRV,
        },
        FVID2_VIFM_MCH_LINE_MUX_ES,
        FVID2_VIFW_8BIT,
        FVID2_STD_MUX_4CH_D1,
        FVID2_DF_YUV422P,
        1U,                                 /* numStream */
        {
            FVID2_DF_YUV422I_YUYV
        },
        CAPT_APP_SC_DISABLE_ALL,
        720U,                               /* inWidth */
        240U,                               /* inHeight */
        {720U  },                           /* outWidth[] */
        {240U  },                           /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_VIDEO_BT656,
        (BSP_BOARD_VS | BSP_BOARD_VISION_TI81XX | BSP_BOARD_JAMR3),
    },
#endif  /* #if (defined TDA2XX_BUILD) || (defined DRA7XX_BUILD) */
#ifdef TI814X_FAMILY_BUILD
    {
        "TVP7002->VIP1_S0_PORTA SCH 720p60 16-bit Embedded Sync, YUYV422I out",
        1U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
        },
        {
            FVID2_VID_DEC_TVP7002_DRV,
        },
        FVID2_VIFM_SCH_ES,
        FVID2_VIFW_16BIT,
        FVID2_STD_720P_60,
        FVID2_DF_YUV422P,
        1U,                                 /* numStream */
        {
            FVID2_DF_YUV422I_YUYV
        },
        CAPT_APP_SC_DISABLE_ALL,
        1280U,                              /* inWidth */
        720U,                               /* inHeight */
        {1280U },                           /* outWidth[] */
        {720U  },                           /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_VIDEO_BT1120,
        (BSP_BOARD_VC | BSP_BOARD_CATALOG),
    },
    {
        "TVP7002->VIP1_S0_PORTA SCH 720p60 16-bit Embedded Sync, 1/2 Scaled YUYV422I out",
        1U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
        },
        {
            FVID2_VID_DEC_TVP7002_DRV,
        },
        FVID2_VIFM_SCH_ES,
        FVID2_VIFW_16BIT,
        FVID2_STD_720P_60,
        FVID2_DF_YUV422P,
        1U,                                 /* numStream */
        {
            FVID2_DF_YUV422I_YUYV
        },
        CAPT_APP_SC_ENABLE_0,
        1280U,                              /* inWidth */
        720U,                               /* inHeight */
        {640U  },                           /* outWidth[] */
        {360U  },                           /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_VIDEO_BT1120,
        (BSP_BOARD_VC | BSP_BOARD_CATALOG),
    },
    {
        "TVP7002->VIP1_S0_PORTA SCH 720p60 16-bit Embedded Sync, RGB888 out",
        1U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
        },
        {
            FVID2_VID_DEC_TVP7002_DRV,
        },
        FVID2_VIFM_SCH_ES,
        FVID2_VIFW_16BIT,
        FVID2_STD_720P_60,
        FVID2_DF_YUV422P,
        1U,                                 /* numStream */
        {
            FVID2_DF_RGB24_888
        },
        CAPT_APP_SC_DISABLE_ALL,
        1280U,                              /* inWidth */
        720U,                               /* inHeight */
        {1280U },                           /* outWidth[] */
        {720U  },                           /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_VIDEO_BT1120,
        (BSP_BOARD_VC | BSP_BOARD_CATALOG),
    },
    {
        "TVP7002->VIP1_S0_PORTA SCH 720p60 16-bit Embedded Sync, YUV420SP_UV out",
        1U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
        },
        {
            FVID2_VID_DEC_TVP7002_DRV,
        },
        FVID2_VIFM_SCH_ES,
        FVID2_VIFW_16BIT,
        FVID2_STD_720P_60,
        FVID2_DF_YUV422P,
        1U,                                 /* numStream */
        {
            FVID2_DF_YUV420SP_UV
        },
        CAPT_APP_SC_DISABLE_ALL,
        1280U,                              /* inWidth */
        720U,                               /* inHeight */
        {1280U },                           /* outWidth[] */
        {720U  },                           /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_VIDEO_BT1120,
        (BSP_BOARD_VC | BSP_BOARD_CATALOG),
    },
    {
        "MT9V022->VIP1_S0_PORTA SCH 16-bit Discrete Sync (HSYNC/VSYNC), YUYV422I out",
        1U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
        },
        {
            FVID2_VID_SENSOR_MT9V022_DRV,
        },
        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,
        FVID2_VIFW_16BIT,
        FVID2_STD_CUSTOM,
        FVID2_DF_YUV422P,
        1U,                                 /* numStream */
        {
            FVID2_DF_YUV422I_YUYV
        },
        CAPT_APP_SC_DISABLE_ALL,
        720U,                               /* inWidth */
        480U,                               /* inHeight */
        {720U  },                           /* outWidth[] */
        {480U  },                           /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_VIDEO_16BIT,
        (BSP_BOARD_VISION_TI81XX),
    },
#endif  /* #ifdef TI814X_FAMILY_BUILD */
#ifdef PLATFORM_SIM
    {
        "Simulator: VIP1_S0_PORTA SCH D1 8-bit Embedded Sync, YUYV422I out",
        1U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
        },
        {
            0U,
        },
        FVID2_VIFM_SCH_ES,
        FVID2_VIFW_8BIT,
        FVID2_STD_D1,
        FVID2_DF_YUV422P,
        1U,                                 /* numStream */
        {
            FVID2_DF_YUV422I_YUYV
        },
        CAPT_APP_SC_DISABLE_ALL,
        720U,                               /* inWidth */
        240U,                               /* inHeight */
        {720U  },                           /* outWidth[] */
        {240U  },                           /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_DEFAULT,
        (BSP_BOARD_UNKNOWN),
    },
    {
        "Simulator: VIP1_S0_PORTA/B 2xSCH D1 8-bit Embedded Sync, YUYV422I out",
        1U,                                 /* numCh */
        2U,                                 /* numHandles */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB),
        },
        {
            0U,
            0U,
        },
        FVID2_VIFM_SCH_ES,
        FVID2_VIFW_8BIT,
        FVID2_STD_D1,
        FVID2_DF_YUV422P,
        1U,                                 /* numStream */
        {
            FVID2_DF_YUV422I_YUYV
        },
        CAPT_APP_SC_DISABLE_ALL,
        720U,                               /* inWidth */
        240U,                               /* inHeight */
        {720U  },                           /* outWidth[] */
        {240U  },                           /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_DEFAULT,
        (BSP_BOARD_UNKNOWN),
    },
#endif  /* #ifdef PLATFORM_SIM */
#ifdef PLATFORM_ZEBU
    {
        "Zebu: VIP1_S0_PORTA SCH D1 16-bit Discrete Sync, YUYV422I out",
        1U,                                 /* numCh */
        1U,                                 /* numHandles */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
        },
        {
            0U,
        },
        FVID2_VIFM_SCH_DS_AVID_VSYNC,
        FVID2_VIFW_16BIT,
        FVID2_STD_D1,
        FVID2_DF_RAW16,
        1U,                                 /* numStream */
        {
            FVID2_DF_RAW16
        },
        CAPT_APP_SC_DISABLE_ALL,
        720U,                               /* inWidth */
        240U,                               /* inHeight */
        {720U  },                           /* outWidth[] */
        {240U  },                           /* outHeight[] */
        CAPT_APP_RUN_COUNT,
        BSP_BOARD_MODE_DEFAULT,
        (BSP_BOARD_UNKNOWN),
    },
#endif
};

#define CAPT_APP_NUM_TESTS              (sizeof (gCaptAppTestPrms) / \
                                         sizeof (gCaptAppTestPrms[0U]))

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef CAPTURE_VIP_MAIN_H_ */
