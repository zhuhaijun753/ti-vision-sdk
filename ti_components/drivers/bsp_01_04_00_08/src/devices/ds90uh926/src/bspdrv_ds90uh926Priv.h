/******************************************************************************
 *                                                                            *
 * Copyright (c) 2015 Texas Instruments Incorporated - http://www.ti.com/     *
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
 *  \file bspdrv_ds90uh926Priv.h
 *
 *  \brief DS90UH926 24-bit FPD-III de-serializer internal header file.
 */

#ifndef BSPDRV_DS90UH926_PRIV_H_
#define BSPDRV_DS90UH926_PRIV_H_

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
#include <ds90uh926/bspdrv_ds90uh926.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Driver object state - NOT IN USE. */
#define BSP_DS90UH926_OBJ_STATE_UNUSED              ((UInt32) (0U))
/** \brief Driver object state - IN USE and IDLE. */
#define BSP_DS90UH926_OBJ_STATE_IDLE                ((UInt32) (1U))

/* DS90UH926 registers */
#define BSP_DS90UH926_REG_I2C_DEVICE_ID             ((UInt32) 0x00U)
#define BSP_DS90UH926_REG_RESET                     ((UInt32) 0x01U)
#define BSP_DS90UH926_REG_CONFIG0                   ((UInt32) 0x02U)
#define BSP_DS90UH926_REG_CONFIG1                   ((UInt32) 0x03U)
#define BSP_DS90UH926_REG_BCC_WATCHDOG_CTRL         ((UInt32) 0x04U)
#define BSP_DS90UH926_REG_I2C_CTRL1                 ((UInt32) 0x05U)
#define BSP_DS90UH926_REG_I2C_CTRL2                 ((UInt32) 0x06U)
#define BSP_DS90UH926_REG_REMOTE_DEV_ID             ((UInt32) 0x07U)
#define BSP_DS90UH926_REG_SLAVE_ID0                 ((UInt32) 0x08U)
#define BSP_DS90UH926_REG_SLAVE_ID1                 ((UInt32) 0x09U)
#define BSP_DS90UH926_REG_SLAVE_ID2                 ((UInt32) 0x0AU)
#define BSP_DS90UH926_REG_SLAVE_ID3                 ((UInt32) 0x0BU)
#define BSP_DS90UH926_REG_SLAVE_ID4                 ((UInt32) 0x0CU)
#define BSP_DS90UH926_REG_SLAVE_ID5                 ((UInt32) 0x0DU)
#define BSP_DS90UH926_REG_SLAVE_ID6                 ((UInt32) 0x0EU)
#define BSP_DS90UH926_REG_SLAVE_ID7                 ((UInt32) 0x0FU)
#define BSP_DS90UH926_REG_SLAVE_ALIAS0              ((UInt32) 0x10U)
#define BSP_DS90UH926_REG_SLAVE_ALIAS1              ((UInt32) 0x11U)
#define BSP_DS90UH926_REG_SLAVE_ALIAS2              ((UInt32) 0x12U)
#define BSP_DS90UH926_REG_SLAVE_ALIAS3              ((UInt32) 0x13U)
#define BSP_DS90UH926_REG_SLAVE_ALIAS4              ((UInt32) 0x14U)
#define BSP_DS90UH926_REG_SLAVE_ALIAS5              ((UInt32) 0x15U)
#define BSP_DS90UH926_REG_SLAVE_ALIAS6              ((UInt32) 0x16U)
#define BSP_DS90UH926_REG_SLAVE_ALIAS7              ((UInt32) 0x17U)
#define BSP_DS90UH926_REG_GENRAL_STATUS             ((UInt32) 0x1CU)
#define BSP_DS90UH926_REG_REV_ID_GPIO0_CONFIG       ((UInt32) 0x1DU)
#define BSP_DS90UH926_REG_GPIO12_CONFIG             ((UInt32) 0x1EU)
#define BSP_DS90UH926_REG_GPIO34_CONFIG             ((UInt32) 0x1FU)
#define BSP_DS90UH926_REG_GPIO56_CONFIG             ((UInt32) 0x20U)
#define BSP_DS90UH926_REG_GPIO78_CONFIG             ((UInt32) 0x21U)
#define BSP_DS90UH926_REG_DATA_PATH_CTRL            ((UInt32) 0x22U)
#define BSP_DS90UH926_REG_GENERAL_PURPOSE_CTRL      ((UInt32) 0x23U)
#define BSP_DS90UH926_REG_BIST_CTRL                 ((UInt32) 0x24U)
#define BSP_DS90UH926_REG_BIST_ERR                  ((UInt32) 0x25U)
#define BSP_DS90UH926_REG_SCL_HIGH_TIME             ((UInt32) 0x26U)
#define BSP_DS90UH926_REG_SCL_LOW_TIME              ((UInt32) 0x27U)
#define BSP_DS90UH926_REG_FCR_CTRL                  ((UInt32) 0x29U)
#define BSP_DS90UH926_REG_WHITE_BALANCE_CTRL        ((UInt32) 0x2AU)
#define BSP_DS90UH926_REG_I2S_CTRL                  ((UInt32) 0x2BU)
#define BSP_DS90UH926_REG_SSCG_CTRL                 ((UInt32) 0x2CU)
#define BSP_DS90UH926_REG_I2S_MCLK_OUTPUT           ((UInt32) 0x3AU)
#define BSP_DS90UH926_REG_LINK_ERR_CNT              ((UInt32) 0x41U)
#define BSP_DS90UH926_REG_EQUALIZATION              ((UInt32) 0x44U)
#define BSP_DS90UH926_REG_CML_OUTPUT                ((UInt32) 0x56U)
#define BSP_DS90UH926_REG_PATTERN_GEN_CTRL          ((UInt32) 0x64U)
#define BSP_DS90UH926_REG_PATTERN_GEN_CONFIG        ((UInt32) 0x65U)
#define BSP_DS90UH926_REG_PATTERN_GEN_INDIRECT_ADDR ((UInt32) 0x66U)
#define BSP_DS90UH926_REG_PATTERN_GEN_INDIRECT_DATA ((UInt32) 0x67U)
#define BSP_DS90UH926_REG_RX_BKSV0                  ((UInt32) 0x80U)
#define BSP_DS90UH926_REG_RX_BKSV1                  ((UInt32) 0x81U)
#define BSP_DS90UH926_REG_RX_BKSV2                  ((UInt32) 0x82U)
#define BSP_DS90UH926_REG_RX_BKSV3                  ((UInt32) 0x83U)
#define BSP_DS90UH926_REG_RX_BKSV4                  ((UInt32) 0x84U)
#define BSP_DS90UH926_REG_TX_KSV0                   ((UInt32) 0x90U)
#define BSP_DS90UH926_REG_TX_KSV1                   ((UInt32) 0x91U)
#define BSP_DS90UH926_REG_TX_KSV2                   ((UInt32) 0x92U)
#define BSP_DS90UH926_REG_TX_KSV3                   ((UInt32) 0x93U)
#define BSP_DS90UH926_REG_TX_KSV4                   ((UInt32) 0x94U)
#define BSP_DS90UH926_REG_HDCP_DBG1                 ((UInt32) 0xC0U)
#define BSP_DS90UH926_REG_HDCP_DBG2                 ((UInt32) 0xC1U)
#define BSP_DS90UH926_REG_HDCP_STATUS               ((UInt32) 0xC4U)
#define BSP_DS90UH926_REG_RPTR_TX0                  ((UInt32) 0xE0U)
#define BSP_DS90UH926_REG_RPTR_TX1                  ((UInt32) 0xE1U)
#define BSP_DS90UH926_REG_RPTR_TX2                  ((UInt32) 0xE2U)
#define BSP_DS90UH926_REG_RPTR_TX3                  ((UInt32) 0xE3U)
#define BSP_DS90UH926_REG_HDCP_RX_ID0               ((UInt32) 0xF0U)
#define BSP_DS90UH926_REG_HDCP_RX_ID1               ((UInt32) 0xF1U)
#define BSP_DS90UH926_REG_HDCP_RX_ID2               ((UInt32) 0xF2U)
#define BSP_DS90UH926_REG_HDCP_RX_ID3               ((UInt32) 0xF3U)
#define BSP_DS90UH926_REG_HDCP_RX_ID4               ((UInt32) 0xF4U)
#define BSP_DS90UH926_REG_HDCP_RX_ID5               ((UInt32) 0xF5U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief DS90UH926 driver handle object.
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
} Bsp_Ds90uh926HandleObj;

/**
 *  \brief DS90UH926 Global driver object.
 */
typedef struct
{
    BspOsal_SemHandle      lock;
    /**< Global driver lock. */
    Bsp_Ds90uh926HandleObj handlePool[BSP_DEVICE_MAX_HANDLES];
    /**< Handle objects. */
} Bsp_Ds90uh926Obj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

Int32 Bsp_ds90uh926Reset(Bsp_Ds90uh926HandleObj *pObj);
Int32 Bsp_ds90uh926GetChipId(Bsp_Ds90uh926HandleObj       *pObj,
                             const Bsp_VidDecChipIdParams *pPrm,
                             Bsp_VidDecChipIdStatus       *pStatus);

Int32 Bsp_ds90uh926SetVideoMode(Bsp_Ds90uh926HandleObj          *pObj,
                                const Bsp_VidDecVideoModeParams *pPrm);
Int32 Bsp_ds90uh926GetVideoStatus(Bsp_Ds90uh926HandleObj            *pObj,
                                  const Bsp_VidDecVideoStatusParams *pPrm,
                                  Bsp_VidDecVideoStatus             *pStatus);

Int32 Bsp_ds90uh926Start(const Bsp_Ds90uh926HandleObj *pObj);
Int32 Bsp_ds90uh926Stop(const Bsp_Ds90uh926HandleObj *pObj);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef BSPDRV_DS90UH926_PRIV_H_ */
