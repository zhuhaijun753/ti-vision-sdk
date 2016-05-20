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
 *  \file Loopback_main.c
 *
 *  \brief Capture->Display loopback sample application main file.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Loopback_priv.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void LpbkApp_createTsk(void);
static void LpbkApp_tskReset(UArg arg0, UArg arg1);
static void LpbkApp_tskMain(UArg arg0, UArg arg1);

static void LpbkApp_init(LpbkApp_Obj *appObj);
static void LpbkApp_deInit(LpbkApp_Obj *appObj);

static Int32 LpbkApp_getTestId(LpbkApp_Obj *appObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Align stack memory to integer boundary. */
#pragma DATA_ALIGN(gLpbkAppTskStackMain, 32)
/* Place the stack in stack section. */
#pragma DATA_SECTION(gLpbkAppTskStackMain, ".bss:taskStackSection")
/* Test application stack */
static UInt8              gLpbkAppTskStackMain[LPBK_APP_TSK_STACK_MAIN];

/* Align stack memory to integer boundary. */
#pragma DATA_ALIGN(gLpbkAppTskStackReset, 32)
/* Place the stack in stack section. */
#pragma DATA_SECTION(gLpbkAppTskStackReset, ".bss:taskStackSection")
/* Test application stack */
static UInt8              gLpbkAppTskStackReset[LPBK_APP_TSK_STACK_MAIN];

/* Test application object */
static LpbkApp_Obj        gLpbkAppObj;

/* Task struct Object for static allocation */
static Task_Struct        gResetTskStruct;
static Task_Struct        gTskStruct;

static volatile UInt32    gExitApp;

static LpbkApp_TestParams gLpbkAppTestPrms[] =
{
    {
#ifdef TDA2EX_BUILD
        "OV1063x            -> VIP1_S1_PORTA (1280x720@30FPS)  -> BGR888      -> DSS Video1 -> DPI1 LCD",
#else
        "OV1063x            -> VIP1_S0_PORTA (1280x720@30FPS)  -> BGR888      -> DSS Video1 -> DPI1 LCD",
#endif
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */
        /* captInstId[] */
        {
#ifdef TDA2EX_BUILD
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,           /* captVideoIfMode */
        FVID2_VIFW_8BIT,                         /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                    /* captScanFormat */
        FVID2_DF_YUV422P,                        /* captInDataFmt */
        FVID2_DF_BGR24_888,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                 /* captScEnable */
        1280U,                                   /* captInWidth */
        720U,                                    /* captInHeight */
        1280U,                                   /* captOutWidth */
        720U,                                    /* captOutHeight */

        1280U,                                   /* dispInWidth */
        720U,                                    /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                  /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                 /* Target Height */

        LPBK_APP_RUN_COUNT,                      /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,               /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,              /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX)
    },
    {
#ifdef TDA2EX_BUILD
        "OV1063x            -> VIP1_S1_PORTA (1280x720@30FPS)  -> ARGB32_8888 -> DSS Video1 -> DPI1 LCD",
#else
        "OV1063x            -> VIP1_S0_PORTA (1280x720@30FPS)  -> ARGB32_8888 -> DSS Video1 -> DPI1 LCD",
#endif
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */
        /* captInstId[] */
        {
#ifdef TDA2EX_BUILD
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,             /* captVideoIfMode */
        FVID2_VIFW_8BIT,                           /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                      /* captScanFormat */
        FVID2_DF_YUV422P,                          /* captInDataFmt */
        FVID2_DF_ARGB32_8888,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                   /* captScEnable */
        1280U,                                     /* captInWidth */
        720U,                                      /* captInHeight */
        1280U,                                     /* captOutWidth */
        720U,                                      /* captOutHeight */

        1280U,                                     /* dispInWidth */
        720U,                                      /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                    /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                   /* Target Height */

        LPBK_APP_RUN_COUNT,                        /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                 /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX)
    },
    {
#ifdef TDA2EX_BUILD
        "OV1063x            -> VIP1_S1_PORTA (1280x720@30FPS)  -> YUV420SP    -> DSS Video1 -> DPI1 LCD",
#else
        "OV1063x            -> VIP1_S0_PORTA (1280x720@30FPS)  -> YUV420SP    -> DSS Video1 -> DPI1 LCD",
#endif
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */
        /* captInstId[] */
        {
#ifdef TDA2EX_BUILD
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,             /* captVideoIfMode */
        FVID2_VIFW_8BIT,                           /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                      /* captScanFormat */
        FVID2_DF_YUV422P,                          /* captInDataFmt */
        FVID2_DF_YUV420SP_UV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                   /* captScEnable */
        1280U,                                     /* captInWidth */
        720U,                                      /* captInHeight */
        1280U,                                     /* captOutWidth */
        720U,                                      /* captOutHeight */

        1280U,                                     /* dispInWidth */
        720U,                                      /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                    /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                   /* Target Height */

        LPBK_APP_RUN_COUNT,                        /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                 /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_UNKNOWN | BSP_BOARD_BASE_TDA2XX | BSP_BOARD_VISION |
         BSP_BOARD_JAMR3 | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX |
         BSP_BOARD_BASE_TDA2EX)
    },
    {
#ifdef TDA2EX_BUILD
        "OV1063x            -> VIP1_S1_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
#else
        "OV1063x            -> VIP1_S0_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
#endif
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */
        /* captInstId[] */
        {
#ifdef TDA2EX_BUILD
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_VISION | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX)
    },
#ifdef TDA3XX_FAMILY_BUILD
    {
        "OV1063x            -> VIP1_S0_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI -> SDVENC (NTSC)",
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */
        /* captInstId[] */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            0,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        TRUE,                                       /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_NTSC,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        720U,                                       /* Target width */
        480U,                                       /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_DEFAULT,                     /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_BASE_TDA3XX | BSP_BOARD_MULTIDES)
    },
    {
        "OV1063x            -> VIP1_S0_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 ->SIL9022A HDMI @720P60",
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_VID_ENC_SII9022A_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_720P_60,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        1280U,                                      /* Target width */
        720U,                                       /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_BASE_TDA3XX | BSP_BOARD_MULTIDES)
    },
#endif  /* #ifdef TDA3XX_FAMILY_BUILD */
    {
#ifdef TDA2EX_BUILD
        "LI OV1063x         -> VIP1_S1_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
#else
        "LI OV1063x         -> VIP1_S0_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
#endif
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
#ifdef TDA2EX_BUILD
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_LI_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_BASE_TDA2XX | BSP_BOARD_VISION | BSP_BOARD_JAMR3 |
         BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX | BSP_BOARD_BASE_TDA2EX)
    },
#if (defined TDA2XX_BUILD) || (defined DRA7XX_BUILD) || (defined TDA2EX_BUILD)
    {
#ifdef TDA2EX_BUILD
        "SII9127            -> VIP1_S1_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
#else
        "SII9127            -> VIP1_S0_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
#endif
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
#ifdef TDA2EX_BUILD
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_DEC_SII9127_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_CUSTOM,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_AVID_VSYNC,               /* captVideoIfMode */
        FVID2_VIFW_16BIT,                           /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_16BIT,                 /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* Note: Can't run in muldes board because of I2C conflict */
        (BSP_BOARD_VISION)
    },
    {
#ifdef TDA2EX_BUILD
        "SII9127            -> VIP1_S1_PORTA (1920x1080@60FPS) -> DSS Video1 -> DPI1 LCD",
#else
        "SII9127            -> VIP1_S0_PORTA (1920x1080@60FPS) -> DSS Video1 -> DPI1 LCD",
#endif
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
#ifdef TDA2EX_BUILD
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_DEC_SII9127_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_CUSTOM,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_AVID_VSYNC,               /* captVideoIfMode */
        FVID2_VIFW_16BIT,                           /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1920U,                                      /* captInWidth */
        1080U,                                      /* captInHeight */
        1920U,                                      /* captOutWidth */
        1080U,                                      /* captOutHeight */

        1920,                                       /* dispInWidth */
        1080,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_16BIT,                 /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* Note: Can't run in muldes board because of I2C conflict */
        (BSP_BOARD_VISION)
    },
#endif  /* #if (defined TDA2XX_BUILD) || (defined DRA7XX_BUILD) || (defined
         *TDA2EX_BUILD) */
    {
#ifdef TDA2EX_BUILD
        "ADV7611            -> VIP1_S1_PORTA (1920x1080@60FPS) -> DSS Video1 -> DPI1 LCD",
#else
        "ADV7611            -> VIP1_S0_PORTA (1920x1080@60FPS) -> DSS Video1 -> DPI1 LCD",
#endif
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
#ifdef TDA2EX_BUILD
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_DEC_ADV7611_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_CUSTOM,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_AVID_VSYNC,               /* captVideoIfMode */
        FVID2_VIFW_16BIT,                           /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1920U,                                      /* captInWidth */
        1080U,                                      /* captInHeight */
        1920U,                                      /* captOutWidth */
        1080U,                                      /* captOutHeight */

        1920,                                       /* dispInWidth */
        1080,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_16BIT,                 /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* Note: Can't run in muldes board because of I2C conflict */
        (BSP_BOARD_VISION | BSP_BOARD_BASE_TDA3XX | BSP_BOARD_MULTIDES)
    },
    {
#ifdef TDA2EX_BUILD
        "MULDESCAM1_OV1063x -> VIP1_S1_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
#else
        "MULDESCAM1_OV1063x -> VIP1_S0_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
#endif  /* #ifdef TDA2EX_BUILD */
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
#ifdef TDA2EX_BUILD
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif      /* #ifdef TDA2EX_BUILD */
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_MULTIDES)
    },
    {
#ifdef TDA3XX_FAMILY_BUILD
        "MULDESCAM2_OV1063x -> VIP1_S0_PORTB (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
#elif (defined TDA2EX_BUILD)
        "MULDESCAM2_OV1063x -> VIP1_S0_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
#else
        "MULDESCAM2_OV1063x -> VIP1_S1_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
#endif
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
#ifdef TDA3XX_FAMILY_BUILD
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB),
#elif (defined TDA2EX_BUILD)
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#endif
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_MULTIDES)
    },
#ifdef TDA2XX_FAMILY_BUILD
    {
#ifdef TDA2EX_BUILD
        "MULDESCAM3_OV1063x -> VIP1_S1_PORTB (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
#else
        "MULDESCAM3_OV1063x -> VIP2_S0_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
#endif  /* #ifdef TDA2EX_BUILD */
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
#ifdef TDA2EX_BUILD
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTB),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTA),
#endif      /* #ifdef TDA2EX_BUILD */
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_MULTIDES)
    },
    {
#ifdef TDA2EX_BUILD
        "MULDESCAM4_OV1063x -> VIP1_S0_PORTB (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
#else
        "MULDESCAM4_OV1063x -> VIP3_S0_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
#endif  /* #ifdef TDA2EX_BUILD */
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
#ifdef TDA2EX_BUILD
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S0, VPS_VIP_PORTA),
#endif      /* #ifdef TDA2EX_BUILD */
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_MULTIDES)
    },
#endif
#if (defined TDA2XX_BUILD) || (defined DRA7XX_BUILD)
    {
        "MULDESCAM5_OV1063x -> VIP2_S1_PORTB (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1, VPS_VIP_PORTB),
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_MULTIDES)
    },
    {
        "MULDESCAM6_OV1063x -> VIP3_S1_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 LCD",
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S1, VPS_VIP_PORTA),
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_MULTIDES)
    },
#endif  /* #if (defined TDA2XX_BUILD) || (defined DRA7XX_BUILD) */
#ifdef TDA2XX_FAMILY_BUILD
    {
        "MULDESCAM1to4      -> VIP                             -> DSS Video1 -> DPI1 LCD",
        4U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
#ifdef TDA2EX_BUILD
            /*
             * CAM1->VIP1_S1_PORTA, CAM2->VIP1_S0_PORTA,
             * CAM3->VIP1_S1_PORTB, CAM4->VIP1_S0_PORTB
             */
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTB),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S0, VPS_VIP_PORTA),
#endif      /* #ifdef TDA2EX_BUILD */
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_MULTIDES)
    },
#endif  /* #ifdef TDA2XX_FAMILY_BUILD */
#if (defined TDA2XX_BUILD) || (defined DRA7XX_BUILD)
    {
        "MULDESCAM1to6      -> VIP                             -> DSS Video1 -> DPI1 LCD",
        6U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1, VPS_VIP_PORTB),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S1, VPS_VIP_PORTA),
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_MULTIDES)
    },
    {
        "MULDESCAM1to4      -> VIP                             -> DSS Video1 -> DPI1 HDMI 1920x1080@60FPS",
        4U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S0, VPS_VIP_PORTA),
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_HDMI
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_1080P_60,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        1920U,                                      /* Target width */
        1080U,                                      /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_DEFAULT,                     /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_MULTIDES)
    },
    {
        "MULDESCAM1to6      -> VIP                             -> DSS Video1 -> DPI1 HDMI 1920x1080@60FPS",
        6U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1, VPS_VIP_PORTB),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S1, VPS_VIP_PORTA),
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_HDMI
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_1080P_60,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        1920U,                                      /* Target width */
        1080U,                                      /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_DEFAULT,                     /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_MULTIDES)
    },
#endif  /* #if (defined TDA2XX_BUILD) || (defined DRA7XX_BUILD) */
#ifdef TDA2XX_FAMILY_BUILD
    {
#ifdef TDA2EX_BUILD
        "TVP5158            -> VIP1_S1_PORTA (PAL)             -> DSS Video1 -> DPI1 LCD",
#else
        "TVP5158            -> VIP1_S0_PORTA (PAL)             -> DSS Video1 -> DPI1 LCD",
#endif
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */
        {
#ifdef TDA2EX_BUILD
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        {
            VPS_DISP_INST_DSS_VID1
        },
        {
            FVID2_VID_DEC_TVP5158_DRV,
        },
        {
            FVID2_LCD_CTRL_DRV,
        },
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        FVID2_STD_D1,                               /* captStandard */
        {
            FVID2_STD_CUSTOM,                       /* dispStandard */
        },

        FVID2_VIFM_SCH_ES,                          /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_INTERLACED,                        /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        720U,                                       /* captInWidth */
        288U,                                       /* captInHeight */
        720U,                                       /* captOutWidth */
        288U,                                       /* captOutHeight */

        720U,                                       /* dispInWidth */
        576U,                                       /* dispInHeight */
        LPBK_APP_USE_LCD_WIDTH,                     /* Target width */
        LPBK_APP_USE_LCD_HEIGHT,                    /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_BT656,                 /* captBoardMode */
        BSP_BOARD_MODE_VIDEO_24BIT,                 /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_JAMR3)
    },
#endif  /* #ifdef TDA2XX_FAMILY_BUILD */
#ifdef TDA3XX_FAMILY_BUILD
    {
        "MULDESCAM1to4      -> VIP                             -> DSS Video1 -> DPI -> SDVENC (NTSC)",
        4U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTB),
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            0,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        TRUE,                                       /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_NTSC,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        720U,                                       /* Target width */
        480U,                                       /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_DEFAULT,                     /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_MULTIDES)
    },
#endif
#if defined (TDA2XX_FAMILY_BUILD) || defined (OMAP5X_FAMILY_BUILD)
    {
#ifdef TDA2EX_BUILD
        "OV1063x            -> VIP1_S1_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 HDMI 1920x1080@60FPS",
#else
        "OV1063x            -> VIP1_S0_PORTA (1280x720@30FPS)  -> DSS Video1 -> DPI1 HDMI 1920x1080@60FPS",
#endif
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
#ifdef TDA2EX_BUILD
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
#else
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
#endif
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            FVID2_VID_SENSOR_OV1063X_DRV,
        },
        /* encDrvId[] */
        {
            FVID2_LCD_CTRL_DRV,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_HDMI
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_720P_60,
        /* dispStandard */
        {
            FVID2_STD_1080P_60,
        },

        FVID2_VIFM_SCH_DS_HSYNC_VSYNC,              /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        1280U,                                      /* captInWidth */
        720U,                                       /* captInHeight */
        1280U,                                      /* captOutWidth */
        720U,                                       /* captOutHeight */

        1280U,                                      /* dispInWidth */
        720U,                                       /* dispInHeight */
        1920U,                                      /* Target width */
        1080U,                                      /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_VIDEO_8BIT,                  /* captBoardMode */
        BSP_BOARD_MODE_DEFAULT,                     /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_VISION | BSP_BOARD_MULTIDES | BSP_BOARD_BASE_TDA3XX)
    },
#endif  /* #if defined (TDA2XX_FAMILY_BUILD) || defined (OMAP5X_FAMILY_BUILD) */
#if (defined TDA2XX_BUILD) || (defined DRA7XX_BUILD)
    {
        "Virtio:               VIP1_S0_PORTA                   -> DSS Video1 -> DPI1 @ D1 (720x480), YUYV422I",
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },
        /* decDrvId[] */
        {
            0U,
        },
        /* encDrvId[] */
        {
            0U,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_D1,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_ES,                          /* captVideoIfMode */
        FVID2_VIFW_8BIT,                            /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422P,                           /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        720U,                                       /* captInWidth */
        480U,                                       /* captInHeight */
        720U,                                       /* captOutWidth */
        480U,                                       /* captOutHeight */

        720U,                                       /* dispInWidth */
        480U,                                       /* dispInHeight */
        720U,                                       /* Target width */
        480U,                                       /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_DEFAULT,                     /* captBoardMode */
        BSP_BOARD_MODE_DEFAULT,                     /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_UNKNOWN)
    },
#endif  /* #if (defined TDA2XX_BUILD) || (defined DRA7XX_BUILD) */
#ifdef PLATFORM_ZEBU
    {
        "Zebu:                 VIP1_S0_PORTA (16-bit DiscSync) -> DSS Video1 -> DPI1 @ D1 (720x480), YUYV422I",
        1U,                                         /* numCaptHandles */
        1U,                                         /* numDispHandles */

        /* captInstId[] */
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
        },
        /* dispInstId[] */
        {
            VPS_DISP_INST_DSS_VID1
        },

        /* decDrvId[] */
        {
            0U,
        },
        /* encDrvId[] */
        {
            0U,
        },
        /* vencId */
        {
            VPS_DCTRL_DSS_VENC_LCD1
        },
        FALSE,                                      /* isSdVenc */
        /* captStandard */
        FVID2_STD_D1,
        /* dispStandard */
        {
            FVID2_STD_CUSTOM,
        },

        FVID2_VIFM_SCH_DS_AVID_VSYNC,               /* captVideoIfMode */
        FVID2_VIFW_16BIT,                           /* captVideoIfWidth */
        FVID2_SF_PROGRESSIVE,                       /* captScanFormat */
        FVID2_DF_YUV422I_YUYV,                      /* captInDataFmt */
        FVID2_DF_YUV422I_YUYV,                      /* captOutDataFmt */

        LPBK_APP_SC_DISABLE_ALL,                    /* captScEnable */
        720U,                                       /* captInWidth */
        480U,                                       /* captInHeight */
        720U,                                       /* captOutWidth */
        480U,                                       /* captOutHeight */

        720U,                                       /* dispInWidth */
        480U,                                       /* dispInHeight */
        720U,                                       /* Target width */
        480U,                                       /* Target Height */

        LPBK_APP_RUN_COUNT,                         /* runCount */
        BSP_BOARD_MODE_DEFAULT,                     /* captBoardMode */
        BSP_BOARD_MODE_DEFAULT,                     /* dispBoardMode */
        /* boardId */
        (BSP_BOARD_UNKNOWN)
    }
#endif
};

#define LPBK_APP_NUM_TESTS              (sizeof (gLpbkAppTestPrms) / \
                                         sizeof (gLpbkAppTestPrms[0U]))

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
    LpbkApp_createTsk();

    /* Start BIOS */
    BIOS_start();

    return (0);
}

/*
 * Create test task
 */
static void LpbkApp_createTsk(void)
{
    Task_Params tskPrms;

    /* Create task to wait for overflow to occur.
     * When it occurs, this task will just reset VIP */
    gExitApp = FALSE;
    Task_Params_init(&tskPrms);
    tskPrms.priority  = LPBK_APP_TSK_PRI_MAIN;
    tskPrms.stack     = gLpbkAppTskStackReset;
    tskPrms.stackSize = sizeof (gLpbkAppTskStackReset);
    tskPrms.arg0      = (UArg) & gLpbkAppObj;
    Task_construct(&gResetTskStruct, LpbkApp_tskReset, &tskPrms, NULL);
    gLpbkAppObj.resetTskHandle = Task_handle(&gResetTskStruct);
    GT_assert(BspAppTrace, (gLpbkAppObj.resetTskHandle != NULL));

    /* Create test task */
    Task_Params_init(&tskPrms);
    tskPrms.priority  = LPBK_APP_TSK_PRI_MAIN;
    tskPrms.stack     = gLpbkAppTskStackMain;
    tskPrms.stackSize = sizeof (gLpbkAppTskStackMain);
    tskPrms.arg0      = (UArg) & gLpbkAppObj;
    Task_construct(&gTskStruct, LpbkApp_tskMain, &tskPrms, NULL);
    gLpbkAppObj.tskHandle = Task_handle(&gTskStruct);
    GT_assert(BspAppTrace, (gLpbkAppObj.tskHandle != NULL));

    /* Register the task to the load module for calculating the load */
    BspUtils_prfLoadRegister(gLpbkAppObj.tskHandle, APP_NAME);

    return;
}

/*
 *  Reset task
 * When overflow occurs, this task will run.
 * It will stop the driver, reset it and again start it.
 */

static void LpbkApp_tskReset(UArg arg0, UArg arg1)
{
    LpbkApp_Obj     *appObj = (LpbkApp_Obj *) arg0;
    LpbkApp_InstObj *instObj;
    UInt32           captInstCnt = 0;
    Int32 retVal;
    overflowSem = BspOsal_semCreate(0, FALSE);

    GT_assert(BspAppTrace, (NULL != appObj));
    GT_assert(BspAppTrace, (NULL != overflowSem));

    while (1U)
    {
        BspOsal_semWait(overflowSem, BSP_OSAL_WAIT_FOREVER);
        if ((UInt32) TRUE == gExitApp)
        {
            BspOsal_semDelete(&overflowSem);
            break;
        }
        for (captInstCnt = 0; captInstCnt < appObj->testPrms.numCaptHandles;
             captInstCnt++)
        {
            Vps_CaptOverflowCheckParams overflowCheckParams;
            instObj = &appObj->instObj[captInstCnt];
            instObj->overflowCount = 0;
            retVal = Fvid2_control(
                instObj->captDrvHandle,
                IOCTL_VPS_CAPT_CHECK_OVERFLOW,
                &overflowCheckParams,
                NULL);
            if (TRUE == overflowCheckParams.isOverflowOccured)
            {
                /*Stop the driver*/
                retVal = Fvid2_stop(instObj->captDrvHandle, NULL);
                if (retVal != FVID2_SOK)
                {
                    GT_0trace(BspAppTrace, GT_ERR,
                              APP_NAME ": Capture Stop Failed!!!\n");
                }

                if (FVID2_SOK == retVal)
                {
                    /* Reset the VIP */
                    retVal = Fvid2_control(
                        instObj->captDrvHandle,
                        IOCTL_VPS_CAPT_RESET_VIP,
                        NULL,
                        NULL);

                    if (retVal != FVID2_SOK)
                    {
                        GT_0trace(BspAppTrace, GT_ERR,
                                  APP_NAME ": VIP Port Reset Failed!!!\n");
                    }
                }

                if (FVID2_SOK == retVal)
                {
                    /* Restart the driver */
                    retVal = Fvid2_start(instObj->captDrvHandle, NULL);
                    if (retVal != FVID2_SOK)
                    {
                        GT_0trace(BspAppTrace, GT_ERR,
                                  APP_NAME ": Capture Start Failed!!!\n");
                    }
                }
                if (FVID2_SOK != retVal)
                {
                    break;
                }
            }
        }
    }

    return;
}

/*
 * Test task main
 */
static void LpbkApp_tskMain(UArg arg0, UArg arg1)
{
    Int32       testId;
    Bsp_BoardId boardId;
    LpbkApp_Obj           *appObj = (LpbkApp_Obj *) arg0;
    LpbkApp_TestParams    *testPrms;
    BspUtils_MemHeapStatus startHeapStat, startHeapStat1;

    GT_0trace(BspAppTrace, GT_INFO,
              APP_NAME ": Sample Application - STARTS !!!\n");
    BspUtils_memGetHeapStat(&startHeapStat);
    LpbkApp_init(appObj);

    appObj->enableAutoRun = (UInt32) FALSE;
    boardId = Bsp_boardGetId();
    while (1U)
    {
        /* Get the TestId */
        testId = LpbkApp_getTestId(appObj);
        if ((testId >= 0) && (testId < LPBK_APP_NUM_TESTS))
        {
            testPrms = &gLpbkAppTestPrms[testId];
            if (testPrms->boardId & boardId)
            {
                BspUtils_memGetHeapStat(&startHeapStat1);

                testPrms->testId = testId;
                LpbkApp_runTest(appObj, testPrms);

                BspUtils_memCheckHeapStat(&startHeapStat1);
            }
            else
            {
                GT_1trace(BspAppTrace, GT_INFO,
                          APP_NAME ": Skipping test case %d!!!\n", testId);
            }
        }
        else
        {
            /* Exit */
            break;
        }
    }

    LpbkApp_deInit(appObj);

    gExitApp = (UInt32) TRUE;
    BspOsal_semPost(overflowSem);
    BspOsal_sleep(500);         /* Wait for reset task to exit */

    BspUtils_memCheckHeapStat(&startHeapStat);
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

static void LpbkApp_init(LpbkApp_Obj *appObj)
{
    Int32  retVal;
    UInt32 isI2cInitReq;
    UInt32 defPixelClk;

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
        /* Create global capture handle, used for common driver configuration */
        appObj->fvidHandleAll = Fvid2_create(
            FVID2_VPS_CAPT_VID_DRV,
            VPS_CAPT_INST_ALL,
            NULL,                       /* NULL for VPS_LPBK_INST_ALL */
            NULL,                       /* NULL for VPS_LPBK_INST_ALL */
            NULL);                      /* NULL for VPS_LPBK_INST_ALL */
        if (NULL == appObj->fvidHandleAll)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Global Handle Create Failed!!!\n");
            retVal = FVID2_EBADARGS;
        }
    }
    if (FVID2_SOK == retVal)
    {
        /* Create DCTRL handle, used for common driver configuration */
        appObj->dctrlHandle = Fvid2_create(
            FVID2_VPS_DCTRL_DRV,
            VPS_DCTRL_INST_0,
            NULL,                       /* NULL for VPS_DCTRL_INST_0 */
            NULL,                       /* NULL for VPS_DCTRL_INST_0 */
            NULL);                      /* NULL for VPS_DCTRL_INST_0 */
        if (NULL == appObj->dctrlHandle)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": DCTRL Create Failed!!!\n");
            retVal = FVID2_EBADARGS;
        }
    }

    if ((BSP_PLATFORM_ID_EVM == Bsp_platformGetId()) && (FVID2_SOK == retVal))
    {
        /* Set default video PLL clock - This will be changed later based
         * on detected LCD */
        defPixelClk = 29232U * 4U;

        /* No Internal Dividers present in DSS in Tda3xx platform,
         * so default it to 29232 itself. */
        if (TRUE == Bsp_platformIsTda3xxFamilyBuild())
        {
            defPixelClk = 29232U;
        }

        retVal = LpbkApp_configureVideoPllAndClkSrc(defPixelClk);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Configuring PLL Failed!!!\n");
        }

        if (FVID2_SOK == retVal)
        {
            /* Needed onlt for TDA2xx platform. Other platform will do nothing
             * and return OK */
            retVal = Bsp_platformEnableHdmiPll(TRUE);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": Enabling HDMI PLL Failed!!!\n");
            }
        }

        if (FVID2_SOK == retVal)
        {
            if (BSP_BOARD_MULTIDES == Bsp_boardGetId())
            {
                retVal =
                    BspUtils_appInitSerDeSer(
                        FVID2_VID_SENSOR_MULDES_OV1063X_DRV);
                if (retVal != FVID2_SOK)
                {
                    GT_0trace(BspAppTrace, GT_ERR,
                              APP_NAME ": MultiDes Board Init failed!!!\n");
                }
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": LpbkApp_init() - DONE !!!\n");
    }

    return;
}

static void LpbkApp_deInit(LpbkApp_Obj *appObj)
{
    Int32  retVal;
    UInt32 isI2cDeInitReq;

    /* Delete DCTRL handle */
    retVal = Fvid2_delete(appObj->dctrlHandle, NULL);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  APP_NAME ": DCTRL handle delete failed!!!\n");
    }

    if (FVID2_SOK == retVal)
    {
        /* Delete global VIP capture handle */
        retVal = Fvid2_delete(appObj->fvidHandleAll, NULL);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Global handle delete failed!!!\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        if (BSP_BOARD_MULTIDES == Bsp_boardGetId())
        {
            retVal =
                BspUtils_appDeInitSerDeSer(
                    FVID2_VID_SENSOR_MULDES_OV1063X_DRV);
            if (retVal != FVID2_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          APP_NAME ": MultiDes Board DeInit failed!!!\n");
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* System de-init */
        isI2cDeInitReq = TRUE;
        retVal         = BspUtils_appDefaultDeInit(isI2cDeInitReq);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": System De-Init Failed!!!\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Needed onlt for TDA2xx platform. Other platform will do nothing
         * and return OK */
        retVal = Bsp_platformEnableHdmiPll(FALSE);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      APP_NAME ": Disabling HDMI PLL Failed!!!\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  APP_NAME ": LpbkApp_deInit() - DONE !!!\n");
    }

    return;
}

/**
 *  LpbkApp_getTestId
 *  Return the test ID to run.
 */
static Int32 LpbkApp_getTestId(LpbkApp_Obj *appObj)
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
    for (testCnt = 0; testCnt < LPBK_APP_NUM_TESTS; testCnt++)
    {
        GT_2trace(BspAppTrace, GT_INFO,
                  "%3d: %s\n", testCnt, gLpbkAppTestPrms[testCnt].testDescStr);
    }
    GT_2trace(BspAppTrace, GT_INFO,
              "%3d: %s\n", LPBK_APP_NUM_TESTS, "Auto Run\n");
    GT_1trace(BspAppTrace, GT_INFO, "%3d: EXIT\n", 100);
    GT_0trace(BspAppTrace, GT_INFO, " \n");
    GT_0trace(BspAppTrace, GT_INFO, "Enter Test to Run: \n");

    if (TRUE == appObj->enableAutoRun)
    {
        testId++;
        if (testId < LPBK_APP_NUM_TESTS)
        {
            GT_1trace(BspAppTrace, GT_INFO, "%d\n", testId);
        }
    }
    else
    {
        while (1U)
        {
            BspOsal_scanf("%d", &testId);
            if ((testId >= 0) && (testId < LPBK_APP_NUM_TESTS))
            {
                break;
            }
            else if (testId == LPBK_APP_NUM_TESTS)
            {
                appObj->enableAutoRun = (UInt32) TRUE;
                testId = 0;
                break;
            }
            else if (100 == testId)
            {
                break;
            }
            GT_0trace(BspAppTrace, GT_INFO, "Invalid Test ID. Enter Agian!!\n");
        }
    }

    return (testId);
}

