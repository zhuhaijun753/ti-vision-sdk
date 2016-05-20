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
 *  \file bspdrv_tvp7002Priv.h
 *
 *  \brief TVP7002 decoder internal header file.
 */

#ifndef BSPDRV_TVP7002_PRIV_H_
#define BSPDRV_TVP7002_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <xdc/std.h>
#include <common/bsp_types.h>
#include <common/bsp_config.h>
#include <common/trace.h>
#include <osal/bsp_osal.h>
#include <common/bsp_utils.h>
#include <fvid2_drvMgr.h>
#include <platforms/bsp_platform.h>
#include <devices/bsp_videoDecoder.h>
#include <tvp7002/bspdrv_tvp7002.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Driver object state - NOT IN USE. */
#define BSP_TVP7002_OBJ_STATE_UNUSED    (0U)
/** \brief Driver object state - IN USE and IDLE. */
#define BSP_TVP7002_OBJ_STATE_IDLE      (1U)

/*
 * TVP7002 Register Offsets.
 */
#define BSP_TVP7002_REG_CHIP_REVISION               (UInt8) (0x00U)
#define BSP_TVP7002_REG_HPLL_DIVIDER_MSB            (UInt8) (0x01U)
#define BSP_TVP7002_REG_HPLL_DIVIDER_LSB            (UInt8) (0x02U)
#define BSP_TVP7002_REG_HPLL_CTRL                   (UInt8) (0x03U)
#define BSP_TVP7002_REG_HPLL_PHASE_SELECT           (UInt8) (0x04U)
#define BSP_TVP7002_REG_CLAMP_START                 (UInt8) (0x05U)
#define BSP_TVP7002_REG_CLAMP_WIDTH                 (UInt8) (0x06U)
#define BSP_TVP7002_REG_HSYNC_OUT_WIDTH             (UInt8) (0x07U)
#define BSP_TVP7002_REG_B_FINE_GAIN                 (UInt8) (0x08U)
#define BSP_TVP7002_REG_G_FINE_GAIN                 (UInt8) (0x09U)
#define BSP_TVP7002_REG_R_FINE_GAIN                 (UInt8) (0x0AU)
#define BSP_TVP7002_REG_B_FINE_OFFSET_MSB           (UInt8) (0x0BU)
#define BSP_TVP7002_REG_G_FINE_OFFSET_MSB           (UInt8) (0x0CU)
#define BSP_TVP7002_REG_R_FINE_OFFSET_MSB           (UInt8) (0x0DU)
#define BSP_TVP7002_REG_SYNC_CTRL1                  (UInt8) (0x0EU)
#define BSP_TVP7002_REG_HPLL_CLAMP_CTRL             (UInt8) (0x0FU)
#define BSP_TVP7002_REG_SOG_THRLD                   (UInt8) (0x10U)
#define BSP_TVP7002_REG_SYNC_SEPARATER_THRLD        (UInt8) (0x11U)
#define BSP_TVP7002_REG_HPLL_PRE_COAST              (UInt8) (0x12U)
#define BSP_TVP7002_REG_HPLL_POST_COAST             (UInt8) (0x13U)
#define BSP_TVP7002_REG_SYNC_DETECT_STATUS          (UInt8) (0x14U)
#define BSP_TVP7002_REG_OUT_FMT                     (UInt8) (0x15U)
#define BSP_TVP7002_REG_MISC_CTRL1                  (UInt8) (0x16U)
#define BSP_TVP7002_REG_MISC_CTRL2                  (UInt8) (0x17U)
#define BSP_TVP7002_REG_MISC_CTRL3                  (UInt8) (0x18U)
#define BSP_TVP7002_REG_IN_MUX_SELECT1              (UInt8) (0x19U)
#define BSP_TVP7002_REG_IN_MUX_SELECT2              (UInt8) (0x1AU)
#define BSP_TVP7002_REG_B_G_COARSE_GAIN             (UInt8) (0x1BU)
#define BSP_TVP7002_REG_R_COARSE_GAIN               (UInt8) (0x1CU)
#define BSP_TVP7002_REG_FINE_OFFSET_LSBS            (UInt8) (0x1DU)
#define BSP_TVP7002_REG_B_COARSE_OFFSET             (UInt8) (0x1EU)
#define BSP_TVP7002_REG_G_COARSE_OFFSET             (UInt8) (0x1FU)
#define BSP_TVP7002_REG_R_COARSE_OFFSET             (UInt8) (0x20U)
#define BSP_TVP7002_REG_HSOUT_OUT_START             (UInt8) (0x21U)
#define BSP_TVP7002_REG_MISC_CTRL4                  (UInt8) (0x22U)
#define BSP_TVP7002_REG_B_ALC_OUT_LSBS              (UInt8) (0x23U)
#define BSP_TVP7002_REG_G_ALC_OUT_LSBS              (UInt8) (0x24U)
#define BSP_TVP7002_REG_R_ALC_OUT_LSBS              (UInt8) (0x25U)
#define BSP_TVP7002_REG_ALC_ENABLE                  (UInt8) (0x26U)
#define BSP_TVP7002_REG_ALC_OUT_MSBS                (UInt8) (0x27U)
#define BSP_TVP7002_REG_ALC_FILTER                  (UInt8) (0x28U)
#define BSP_TVP7002_REG_RESERVED1                   (UInt8) (0x29U)
#define BSP_TVP7002_REG_FINE_CLAMP_CTRL             (UInt8) (0x2AU)
#define BSP_TVP7002_REG_POWER_CTRL                  (UInt8) (0x2BU)
#define BSP_TVP7002_REG_ADC_SETUP                   (UInt8) (0x2CU)
#define BSP_TVP7002_REG_COARSE_CLAMP_CTRL           (UInt8) (0x2DU)
#define BSP_TVP7002_REG_SOG_CLAMP                   (UInt8) (0x2EU)
#define BSP_TVP7002_REG_RGB_COARSE_CLAMP_CTRL       (UInt8) (0x2FU)
#define BSP_TVP7002_REG_SOG_COARSE_CLAMP_CTRL       (UInt8) (0x30U)
#define BSP_TVP7002_REG_ALC_PLACEMENT               (UInt8) (0x31U)
#define BSP_TVP7002_REG_RESERVED2                   (UInt8) (0x32U)
#define BSP_TVP7002_REG_RESERVED3                   (UInt8) (0x33U)
#define BSP_TVP7002_REG_MAC_STRIPPER_WIDTH          (UInt8) (0x34U)
#define BSP_TVP7002_REG_VSYNC_ALIGNMENT             (UInt8) (0x35U)
#define BSP_TVP7002_REG_SYNC_BYPASS                 (UInt8) (0x36U)
#define BSP_TVP7002_REG_LINES_PER_FRAME_STATUS_LSB  (UInt8) (0x37U)
#define BSP_TVP7002_REG_LINES_PER_FRAME_STATUS_MSB  (UInt8) (0x38U)
#define BSP_TVP7002_REG_CLOCK_PER_LINE_STATUS_LSB   (UInt8) (0x39U)
#define BSP_TVP7002_REG_CLOCK_PER_LINE_STATUS_MSB   (UInt8) (0x3AU)
#define BSP_TVP7002_REG_HSYNC_WIDTH                 (UInt8) (0x3BU)
#define BSP_TVP7002_REG_VSYNC_WIDTH                 (UInt8) (0x3CU)
#define BSP_TVP7002_REG_LINE_LENGTH_TOLERENCE       (UInt8) (0x3DU)
#define BSP_TVP7002_REG_RESERVED4                   (UInt8) (0x3EU)
#define BSP_TVP7002_REG_VIDEO_BANDWIDTH_CTRL        (UInt8) (0x3FU)
#define BSP_TVP7002_REG_AVID_START_PIXEL_LSB        (UInt8) (0x40U)
#define BSP_TVP7002_REG_AVID_START_PIXEL_MSB        (UInt8) (0x41U)
#define BSP_TVP7002_REG_AVID_STOP_PIXEL_LSB         (UInt8) (0x42U)
#define BSP_TVP7002_REG_AVID_STOP_PIXEL_MSB         (UInt8) (0x43U)
#define BSP_TVP7002_REG_VBLK_FLD0_START_OFFSET      (UInt8) (0x44U)
#define BSP_TVP7002_REG_VBLK_FLD1_START_OFFSET      (UInt8) (0x45U)
#define BSP_TVP7002_REG_VBLK_FLD0_DURATION          (UInt8) (0x46U)
#define BSP_TVP7002_REG_VBLK_FLD1_DURATION          (UInt8) (0x47U)
#define BSP_TVP7002_REG_FBIT_FLD0_START_OFFSET      (UInt8) (0x48U)
#define BSP_TVP7002_REG_FBIT_FLD1_START_OFFSET      (UInt8) (0x49U)
#define BSP_TVP7002_REG_CSC_COEFF0_LSB              (UInt8) (0x4AU)
/*
 * Shifts and masks for the fields.
 */
#define BSP_TVP7002_OUT_FMT_RANGE_SHIFT             (0x05U)
#define BSP_TVP7002_OUT_FMT_ORDER_SHIFT             (0x02U)
#define BSP_TVP7002_OUT_FMT_DECIMATION_SHIFT        (0x01U)
#define BSP_TVP7002_OUT_FMT_SYNC_ENABLE_SHIFT       (0x00U)

#define BSP_TVP7002_MISC_CTRL3_CSC_ENABLE_MASK      (0x10U)
#define BSP_TVP7002_MISC_CTRL3_CSC_ENABLE_SHIFT     (0x04U)

/** \brief RGB coding range (Y, Cb, and Cr range from 0 to 1023). */
#define BSP_TVP7002_RANGE_RGB           (0x00U)
/** \brief Extended coding range (Y, Cb, and Cr range from 4 to 1019). */
#define BSP_TVP7002_RANGE_EXTENDED      (0x01U)
/** \brief ITU-R BT.601 coding range (Y - 64 to 940, Cb/Cr - 64 to 960). */
#define BSP_TVP7002_RANGE_BT601         (0x02U)

/** \brief CbCr order. */
#define BSP_TVP7002_CBCR_ORDER          (0x00U)
/** \brief CrCb order. */
#define BSP_TVP7002_CRCB_ORDER          (0x01U)

/** \brief 30-bit 4:4:4 output format. */
#define BSP_TVP7002_OUT_FORMAT_30BIT    (0x00U)
/** \brief 30-bit 4:4:4 output format. */
#define BSP_TVP7002_OUT_FORMAT_20BIT    (0x01U)

/** \brief Number of CSC co-eff rgs in TVP7002 */
#define BSP_TVP7002_NUM_CSC_COEFF_REGS  (9U * 2U)

#define BSP_TVP7002_NUM_DEFAULT_SETTINGS (27U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief TVP7002 driver handle object.
 */
typedef struct
{
    UInt32                    state;
    /**< Handle state - used or free. */
    UInt32                    handleId;
    /**< Handle ID, 0..BSP_DEVICE_MAX_HANDLES-1. */
    BspOsal_SemHandle         lock;
    /**< Driver lock. */
    Bsp_VidDecCreateParams    createPrms;
    /**< Create time arguments. */
    Bsp_VidDecVideoModeParams modePrms;
    /**< Video decoder mode parameters. */
} Bsp_Tvp7002HandleObj;

/**
 *  \brief TVP7002 Global driver object.
 */
typedef struct
{
    BspOsal_SemHandle    lock;
    /* Global driver lock. */
    Bsp_Tvp7002HandleObj handlePool[BSP_DEVICE_MAX_HANDLES];
    /**< Handle objects. */
} Bsp_Tvp7002Obj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

Int32 Bsp_tvp7002Reset(const Bsp_Tvp7002HandleObj *pObj);
Int32 Bsp_tvp7002GetChipId(const Bsp_Tvp7002HandleObj   *pObj,
                           const Bsp_VidDecChipIdParams *pPrm,
                           Bsp_VidDecChipIdStatus       *pStatus);

Int32 Bsp_tvp7002SetVideoMode(Bsp_Tvp7002HandleObj            *pObj,
                              const Bsp_VidDecVideoModeParams *pPrm);
Int32 Bsp_tvp7002GetVideoStatus(const Bsp_Tvp7002HandleObj        *pObj,
                                const Bsp_VidDecVideoStatusParams *pPrm,
                                Bsp_VidDecVideoStatus             *pStatus);

Int32 Bsp_tvp7002Start(const Bsp_Tvp7002HandleObj *pObj);
Int32 Bsp_tvp7002Stop(const Bsp_Tvp7002HandleObj *pObj);

Int32 Bsp_tvp7002RegWrite(const Bsp_Tvp7002HandleObj    *pObj,
                          const Bsp_VidDecRegRdWrParams *pPrm);
Int32 Bsp_tvp7002RegRead(const Bsp_Tvp7002HandleObj *pObj,
                         Bsp_VidDecRegRdWrParams    *pPrm);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern const UInt8 gTvp7002DefAddrList[1];
extern UInt8       gTvp7002DefValueList[1];

extern const UInt8 gTvp7002ModeAddrList[BSP_TVP7002_NUM_DEFAULT_SETTINGS];
extern UInt8       gTvp7002Value1080p60EmbSync
[BSP_TVP7002_NUM_DEFAULT_SETTINGS];
extern UInt8       gTvp7002Value1080p60DiscSync
[BSP_TVP7002_NUM_DEFAULT_SETTINGS];
extern UInt8       gTvp7002Value1080i60EmbSync
[BSP_TVP7002_NUM_DEFAULT_SETTINGS];
extern UInt8       gTvp7002Value1080i60DiscSync
[BSP_TVP7002_NUM_DEFAULT_SETTINGS];
extern UInt8       gTvp7002Value720p60EmbSync[BSP_TVP7002_NUM_DEFAULT_SETTINGS];
extern UInt8       gTvp7002Value720p60DiscSync
[BSP_TVP7002_NUM_DEFAULT_SETTINGS];
extern UInt8       gTvp7002ValueSxga60[BSP_TVP7002_NUM_DEFAULT_SETTINGS];

extern UInt16      gTvp7002CscCoeffRgb2Yuv[9];
extern UInt16      gTvp7002CscCoeffYuv2Rgb[9];

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSPDRV_TVP7002_PRIV_H_ */
