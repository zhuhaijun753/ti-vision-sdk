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
 *  \file bspdrv_tvp7002Settings.c
 *
 *  \brief TVP7002 decoder internal file for defining the register
 *  settings for various modes.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <tvp7002/src/bspdrv_tvp7002Priv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief List of address offset used for common default settings.
 *  Caution: The address offset order should match with the value list order.
 */
const UInt8 gTvp7002DefAddrList[1] =
{
    BSP_TVP7002_REG_MISC_CTRL2
};

/**
 *  \brief List of values used for common default settings.
 *  Caution: The value list order should match with the address list order.
 */
UInt8       gTvp7002DefValueList[1] =
{
    0x13U               /* MISC_CTRL2               */
};

/**
 *  \brief List of address offset used for different standard settings.
 *  Caution: The address offset order should match with the value list order.
 */
const UInt8 gTvp7002ModeAddrList[BSP_TVP7002_NUM_DEFAULT_SETTINGS] =
{
    BSP_TVP7002_REG_HPLL_DIVIDER_MSB,
    BSP_TVP7002_REG_HPLL_DIVIDER_LSB,
    BSP_TVP7002_REG_HPLL_CTRL,
    BSP_TVP7002_REG_HPLL_PHASE_SELECT,
    BSP_TVP7002_REG_CLAMP_START,
    BSP_TVP7002_REG_CLAMP_WIDTH,
    BSP_TVP7002_REG_HSYNC_OUT_WIDTH,
    BSP_TVP7002_REG_SYNC_CTRL1,
    BSP_TVP7002_REG_HPLL_PRE_COAST,
    BSP_TVP7002_REG_HPLL_POST_COAST,
    BSP_TVP7002_REG_MISC_CTRL3,
    BSP_TVP7002_REG_IN_MUX_SELECT1,
    BSP_TVP7002_REG_IN_MUX_SELECT2,
    BSP_TVP7002_REG_HSOUT_OUT_START,
    BSP_TVP7002_REG_MISC_CTRL4,
    BSP_TVP7002_REG_ADC_SETUP,
    BSP_TVP7002_REG_ALC_PLACEMENT,
    BSP_TVP7002_REG_AVID_START_PIXEL_LSB,
    BSP_TVP7002_REG_AVID_START_PIXEL_MSB,
    BSP_TVP7002_REG_AVID_STOP_PIXEL_LSB,
    BSP_TVP7002_REG_AVID_STOP_PIXEL_MSB,
    BSP_TVP7002_REG_VBLK_FLD0_START_OFFSET,
    BSP_TVP7002_REG_VBLK_FLD1_START_OFFSET,
    BSP_TVP7002_REG_VBLK_FLD0_DURATION,
    BSP_TVP7002_REG_VBLK_FLD1_DURATION,
    BSP_TVP7002_REG_FBIT_FLD0_START_OFFSET,
    BSP_TVP7002_REG_FBIT_FLD1_START_OFFSET
};

/**
 *  \brief List of values used for 1080p60 settings in embedded sync mode.
 *  Caution: The value list order should match with the address list order.
 */
UInt8       gTvp7002Value1080p60EmbSync[BSP_TVP7002_NUM_DEFAULT_SETTINGS] =
{
    0x89U,              /* HPLL_DIVIDER_MSB         */
    0x80U,              /* HPLL_DIVIDER_LSB         */
    0xE0U,              /* HPLL_CTRL                */
    0xA0U,              /* HPLL_PHASE_SELECT        */
    0x32U,              /* CLAMP_START              */
    0x20U,              /* CLAMP_WIDTH              */
    0x20U,              /* HSYNC_OUT_WIDTH          */
    0x5BU,              /* SYNC_CTRL1               */
    0x01U,              /* HPLL_PRE_COAST           */
    0x00U,              /* HPLL_POST_COAST          */
    0x00U,              /* MISC_CTRL3               */
    0x00U,              /* IN_MUX_SELECT1           */
    0x6AU,              /* IN_MUX_SELECT2           */
    0x08U,              /* HSOUT_OUT_START          */
    0x00U,              /* MISC_CTRL4               */
    0x80U,              /* ADC_SETUP                */
    0x5AU,              /* ALC_PLACEMENT            */
    0x00U,              /* AVID_START_PIXEL_LSB     */
    0x01U,              /* AVID_START_PIXEL_MSB     */
    0x84U,              /* AVID_STOP_PIXEL_LSB      */
    0x08U,              /* AVID_STOP_PIXEL_MSB      */
    0x05U,              /* VBLK_FLD0_START_OFFSET   */
    0x00U,              /* VBLK_FLD1_START_OFFSET   */
    0x2DU,              /* VBLK_FLD0_DURATION       */
    0x00U,              /* VBLK_FLD1_DURATION       */
    0x00U,              /* FBIT_FLD0_START_OFFSET   */
    0x00U               /* FBIT_FLD1_START_OFFSET   */
};

/**
 *  \brief List of values used for 1080p60 settings in discrete sync mode.
 *  Caution: The value list order should match with the address list order.
 */
UInt8       gTvp7002Value1080p60DiscSync[BSP_TVP7002_NUM_DEFAULT_SETTINGS] =
{
    0x89U,              /* HPLL_DIVIDER_MSB         */
    0x80U,              /* HPLL_DIVIDER_LSB         */
    0xE0U,              /* HPLL_CTRL                */
    0xA0U,              /* HPLL_PHASE_SELECT        */
    0x32U,              /* CLAMP_START              */
    0x20U,              /* CLAMP_WIDTH              */
    0x20U,              /* HSYNC_OUT_WIDTH          */
    0x5BU,              /* SYNC_CTRL1               */
    0x01U,              /* HPLL_PRE_COAST           */
    0x00U,              /* HPLL_POST_COAST          */
    0x00U,              /* MISC_CTRL3               */
    0x00U,              /* IN_MUX_SELECT1           */
    0x6AU,              /* IN_MUX_SELECT2           */
    0x08U,              /* HSOUT_OUT_START          */
    0x00U,              /* MISC_CTRL4               */
    0x80U,              /* ADC_SETUP                */
    0x5AU,              /* ALC_PLACEMENT            */
    0xF4U,              /* AVID_START_PIXEL_LSB     */
    0x00U,              /* AVID_START_PIXEL_MSB     */
    0x74U,              /* AVID_STOP_PIXEL_LSB      */
    0x08U,              /* AVID_STOP_PIXEL_MSB      */
    0x05U,              /* VBLK_FLD0_START_OFFSET   */
    0x00U,              /* VBLK_FLD1_START_OFFSET   */
    0x2DU,              /* VBLK_FLD0_DURATION       */
    0x00U,              /* VBLK_FLD1_DURATION       */
    0x00U,              /* FBIT_FLD0_START_OFFSET   */
    0x00U               /* FBIT_FLD1_START_OFFSET   */
};

/**
 *  \brief List of values used for 1080i60 settings in embedded sync mode.
 *  Caution: The value list order should match with the address list order.
 */
UInt8       gTvp7002Value1080i60EmbSync[BSP_TVP7002_NUM_DEFAULT_SETTINGS] =
{
    0x89U,              /* HPLL_DIVIDER_MSB         */
    0x80U,              /* HPLL_DIVIDER_LSB         */
    0x98U,              /* HPLL_CTRL                */
    0xA0U,              /* HPLL_PHASE_SELECT        */
    0x32U,              /* CLAMP_START              */
    0x20U,              /* CLAMP_WIDTH              */
    0x20U,              /* HSYNC_OUT_WIDTH          */
    0x5BU,              /* SYNC_CTRL1               */
    0x01U,              /* HPLL_PRE_COAST           */
    0x00U,              /* HPLL_POST_COAST          */
    0x00U,              /* MISC_CTRL3               */
    0x00U,              /* IN_MUX_SELECT1           */
    0x6AU,              /* IN_MUX_SELECT2           */
    0x0DU,              /* HSOUT_OUT_START          */
    0x00U,              /* MISC_CTRL4               */
    0x50U,              /* ADC_SETUP                */
    0x5AU,              /* ALC_PLACEMENT            */
    0xF1U,              /* AVID_START_PIXEL_LSB     */
    0x00U,              /* AVID_START_PIXEL_MSB     */
    0x75U,              /* AVID_STOP_PIXEL_LSB      */
    0x08U,              /* AVID_STOP_PIXEL_MSB      */
    0x02U,              /* VBLK_FLD0_START_OFFSET   */
    0x02U,              /* VBLK_FLD1_START_OFFSET   */
    0x16U,              /* VBLK_FLD0_DURATION       */
    0x17U,              /* VBLK_FLD1_DURATION       */
    0x00U,              /* FBIT_FLD0_START_OFFSET   */
    0x00U               /* FBIT_FLD1_START_OFFSET   */
};

/**
 *  \brief List of values used for 1080i60 settings in discrete sync mode.
 *  Caution: The value list order should match with the address list order.
 */
UInt8       gTvp7002Value1080i60DiscSync[BSP_TVP7002_NUM_DEFAULT_SETTINGS] =
{
    0x89U,              /* HPLL_DIVIDER_MSB         */
    0x80U,              /* HPLL_DIVIDER_LSB         */
    0x98U,              /* HPLL_CTRL                */
    0xA0U,              /* HPLL_PHASE_SELECT        */
    0x32U,              /* CLAMP_START              */
    0x20U,              /* CLAMP_WIDTH              */
    0x20U,              /* HSYNC_OUT_WIDTH          */
    0x5BU,              /* SYNC_CTRL1               */
    0x01U,              /* HPLL_PRE_COAST           */
    0x00U,              /* HPLL_POST_COAST          */
    0x00U,              /* MISC_CTRL3               */
    0x00U,              /* IN_MUX_SELECT1           */
    0x6AU,              /* IN_MUX_SELECT2           */
    0x0DU,              /* HSOUT_OUT_START          */
    0x00U,              /* MISC_CTRL4               */
    0x50U,              /* ADC_SETUP                */
    0x5AU,              /* ALC_PLACEMENT            */
    0xF4U,              /* AVID_START_PIXEL_LSB     */
    0x00U,              /* AVID_START_PIXEL_MSB     */
    0x74U,              /* AVID_STOP_PIXEL_LSB      */
    0x08U,              /* AVID_STOP_PIXEL_MSB      */
    0x02U,              /* VBLK_FLD0_START_OFFSET   */
    0x02U,              /* VBLK_FLD1_START_OFFSET   */
    0x16U,              /* VBLK_FLD0_DURATION       */
    0x17U,              /* VBLK_FLD1_DURATION       */
    0x00U,              /* FBIT_FLD0_START_OFFSET   */
    0x00U               /* FBIT_FLD1_START_OFFSET   */
};

/**
 *  \brief List of values used for 720p60 settings in embedded sync mode.
 *  Caution: The value list order should match with the address list order.
 */
UInt8       gTvp7002Value720p60EmbSync[BSP_TVP7002_NUM_DEFAULT_SETTINGS] =
{
    0x67U,              /* HPLL_DIVIDER_MSB         */
    0x20U,              /* HPLL_DIVIDER_LSB         */
    0xA0U,              /* HPLL_CTRL                */
    0xB0U,              /* HPLL_PHASE_SELECT        */
    0x32U,              /* CLAMP_START              */
    0x20U,              /* CLAMP_WIDTH              */
    0x20U,              /* HSYNC_OUT_WIDTH          */
    0x5BU,              /* SYNC_CTRL1               */
    0x01U,              /* HPLL_PRE_COAST           */
    0x00U,              /* HPLL_POST_COAST          */
    0x00U,              /* MISC_CTRL3               */
    0x00U,              /* IN_MUX_SELECT1           */
    0x6AU,              /* IN_MUX_SELECT2           */
    0x08U,              /* HSOUT_OUT_START          */
    0x00U,              /* MISC_CTRL4               */
    0x50U,              /* ADC_SETUP                */
    0x5AU,              /* ALC_PLACEMENT            */
    0x47U,              /* AVID_START_PIXEL_LSB     */
    0x01U,              /* AVID_START_PIXEL_MSB     */
    0x4BU,              /* AVID_STOP_PIXEL_LSB      */
    0x06U,              /* AVID_STOP_PIXEL_MSB      */
    0x05U,              /* VBLK_FLD0_START_OFFSET   */
    0x00U,              /* VBLK_FLD1_START_OFFSET   */
    0x1EU,              /* VBLK_FLD0_DURATION       */
    0x00U,              /* VBLK_FLD1_DURATION       */
    0x00U,              /* FBIT_FLD0_START_OFFSET   */
    0x00U               /* FBIT_FLD1_START_OFFSET   */
};

/**
 *  \brief List of values used for 720p60 settings in discrete sync mode.
 *  Caution: The value list order should match with the address list order.
 */
UInt8       gTvp7002Value720p60DiscSync[BSP_TVP7002_NUM_DEFAULT_SETTINGS] =
{
    0x67U,              /* HPLL_DIVIDER_MSB         */
    0x20U,              /* HPLL_DIVIDER_LSB         */
    0xA0U,              /* HPLL_CTRL                */
    0xB0U,              /* HPLL_PHASE_SELECT        */
    0x32U,              /* CLAMP_START              */
    0x20U,              /* CLAMP_WIDTH              */
    0x20U,              /* HSYNC_OUT_WIDTH          */
    0x5BU,              /* SYNC_CTRL1               */
    0x01U,              /* HPLL_PRE_COAST           */
    0x00U,              /* HPLL_POST_COAST          */
    0x00U,              /* MISC_CTRL3               */
    0x00U,              /* IN_MUX_SELECT1           */
    0x6AU,              /* IN_MUX_SELECT2           */
    0x08U,              /* HSOUT_OUT_START          */
    0x00U,              /* MISC_CTRL4               */
    0x50U,              /* ADC_SETUP                */
    0x5AU,              /* ALC_PLACEMENT            */
    0x35U,              /* AVID_START_PIXEL_LSB     */
    0x01U,              /* AVID_START_PIXEL_MSB     */
    0x35U,              /* AVID_STOP_PIXEL_LSB      */
    0x06U,              /* AVID_STOP_PIXEL_MSB      */
    0x05U,              /* VBLK_FLD0_START_OFFSET   */
    0x00U,              /* VBLK_FLD1_START_OFFSET   */
    0x1EU,              /* VBLK_FLD0_DURATION       */
    0x00U,              /* VBLK_FLD1_DURATION       */
    0x00U,              /* FBIT_FLD0_START_OFFSET   */
    0x00U               /* FBIT_FLD1_START_OFFSET   */
};

/**
 *  \brief List of values used for SXGA@60 settings.
 *  Caution: The value list order should match with the address list order.
 */
UInt8       gTvp7002ValueSxga60[BSP_TVP7002_NUM_DEFAULT_SETTINGS] =
{
    0x69U,              /* HPLL_DIVIDER_MSB         */
    0x80U,              /* HPLL_DIVIDER_LSB         */
    0xA0U,              /* HPLL_CTRL                */
    0x80U,              /* HPLL_PHASE_SELECT        */
    0x06U,              /* CLAMP_START              */
    0x10U,              /* CLAMP_WIDTH              */
    0x20U,              /* HSYNC_OUT_WIDTH          */
    0x52U,              /* SYNC_CTRL1               */
    0x01U,              /* HPLL_PRE_COAST           */
    0x00U,              /* HPLL_POST_COAST          */
    0x00U,              /* MISC_CTRL3               */
    0xAAU,              /* IN_MUX_SELECT1           */
    0x6AU,              /* IN_MUX_SELECT2           */
    0x08U,              /* HSOUT_OUT_START          */
    0x00U,              /* MISC_CTRL4               */
    0x50U,              /* ADC_SETUP                */
    0x18U,              /* ALC_PLACEMENT            */
    0x80U,              /* AVID_START_PIXEL_LSB     */
    0x01U,              /* AVID_START_PIXEL_MSB     */
    0x86U,              /* AVID_STOP_PIXEL_LSB      */
    0x06U,              /* AVID_STOP_PIXEL_MSB      */
    0x04U,              /* VBLK_FLD0_START_OFFSET   */
    0x00U,              /* VBLK_FLD1_START_OFFSET   */
    0x2AU,              /* VBLK_FLD0_DURATION       */
    0x00U,              /* VBLK_FLD1_DURATION       */
    0x00U,              /* FBIT_FLD0_START_OFFSET   */
    0x00U               /* FBIT_FLD1_START_OFFSET   */
};

UInt16      gTvp7002CscCoeffRgb2Yuv[9] =
{
    0x16E3, 0x024F, 0x06CE,
    0xF3AB, 0x1000, 0xFC55,
    0xF178, 0xFE88, 0x1000,
};

UInt16      gTvp7002CscCoeffYuv2Rgb[9] =
{
    0x2000, 0xF538, 0xE9A8,
    0x2000, 0x0000, 0x2BE8,
    0x2000, 0x3778, 0x0000,
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

