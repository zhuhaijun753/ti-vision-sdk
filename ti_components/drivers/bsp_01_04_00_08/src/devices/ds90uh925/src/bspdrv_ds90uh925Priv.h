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
 *  \file bspdrv_ds90uh925Priv.h
 *
 *  \brief DS90UH925 24-bit FPD-III serializer internal header file.
 */

#ifndef BSPDRV_DS90UH925_PRIV_H_
#define BSPDRV_DS90UH925_PRIV_H_

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
#include <devices/bsp_videoEncoder.h>
#include <ds90uh925/bspdrv_ds90uh925.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Driver object state - NOT IN USE. */
#define BSP_DS90UH925_OBJ_STATE_UNUSED              ((UInt32) (0U))
/** \brief Driver object state - IN USE and IDLE. */
#define BSP_DS90UH925_OBJ_STATE_IDLE                ((UInt32) (1U))

/* DS90UH925 registers */
#define BSP_DS90UH925_REG_I2C_DEVICE_ID             ((UInt32) 0x00U)
#define BSP_DS90UH925_REG_RESET                     ((UInt32) 0x01U)
#define BSP_DS90UH925_REG_CONFIG0                   ((UInt32) 0x03U)
#define BSP_DS90UH925_REG_CONFIG1                   ((UInt32) 0x04U)
#define BSP_DS90UH925_REG_I2C_CTRL                  ((UInt32) 0x05U)
#define BSP_DS90UH925_REG_DES_ID                    ((UInt32) 0x06U)
#define BSP_DS90UH925_REG_SLAVE_ID                  ((UInt32) 0x07U)
#define BSP_DS90UH925_REG_SLAVE_ALIAS               ((UInt32) 0x08U)
#define BSP_DS90UH925_REG_CRC_ERR_LSB               ((UInt32) 0x0AU)
#define BSP_DS90UH925_REG_CRC_ERR_MSB               ((UInt32) 0x0BU)
#define BSP_DS90UH925_REG_GENRAL_STATUS             ((UInt32) 0x0CU)
#define BSP_DS90UH925_REG_REV_ID_GPIO0_CONFIG       ((UInt32) 0x0DU)
#define BSP_DS90UH925_REG_GPIO12_CONFIG             ((UInt32) 0x0EU)
#define BSP_DS90UH925_REG_GPIO34_CONFIG             ((UInt32) 0x0FU)
#define BSP_DS90UH925_REG_GPIO56_CONFIG             ((UInt32) 0x10U)
#define BSP_DS90UH925_REG_GPIO78_CONFIG             ((UInt32) 0x11U)
#define BSP_DS90UH925_REG_DATA_PATH_CTRL            ((UInt32) 0x12U)
#define BSP_DS90UH925_REG_MODE_STATUS               ((UInt32) 0x13U)
#define BSP_DS90UH925_REG_OSC_CLK_SRC_BIST_STATUS   ((UInt32) 0x14U)
#define BSP_DS90UH925_REG_BCC_WATCHDOG_CTRL         ((UInt32) 0x16U)
#define BSP_DS90UH925_REG_I2C_CTRL1                 ((UInt32) 0x17U)
#define BSP_DS90UH925_REG_SCL_HIGH_TIME             ((UInt32) 0x18U)
#define BSP_DS90UH925_REG_SCL_LOW_TIME              ((UInt32) 0x19U)
#define BSP_DS90UH925_REG_BIST_BC_ERR               ((UInt32) 0x1BU)
#define BSP_DS90UH925_REG_PATTERN_GEN_CTRL          ((UInt32) 0x64U)
#define BSP_DS90UH925_REG_PATTERN_GEN_CONFIG        ((UInt32) 0x65U)
#define BSP_DS90UH925_REG_PATTERN_GEN_INDIRECT_ADDR ((UInt32) 0x66U)
#define BSP_DS90UH925_REG_PATTERN_GEN_INDIRECT_DATA ((UInt32) 0x67U)
#define BSP_DS90UH925_REG_ICR                       ((UInt32) 0xC6U)
#define BSP_DS90UH925_REG_ISR                       ((UInt32) 0xC7U)
#define BSP_DS90UH925_REG_TX_ID0                    ((UInt32) 0xF0U)
#define BSP_DS90UH925_REG_TX_ID1                    ((UInt32) 0xF1U)
#define BSP_DS90UH925_REG_TX_ID2                    ((UInt32) 0xF2U)
#define BSP_DS90UH925_REG_TX_ID3                    ((UInt32) 0xF3U)
#define BSP_DS90UH925_REG_TX_ID4                    ((UInt32) 0xF4U)
#define BSP_DS90UH925_REG_TX_ID5                    ((UInt32) 0xF5U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief DS90UH925 driver handle object.
 */
typedef struct
{
    UInt32                 state;
    /**< Handle state - used or free. */
    UInt32                 handleId;
    /**< Handle ID, 0..BSP_DEVICE_MAX_HANDLES-1. */
    BspOsal_SemHandle      lock;
    /**< Driver lock. */
    Bsp_VidEncCreateParams createPrms;
    /**< Create time arguments. */
    Bsp_VidEncConfigParams modePrms;
    /**< Video encoder mode parameters. */
} Bsp_Ds90uh925HandleObj;

/**
 *  \brief DS90UH925 Global driver object.
 */
typedef struct
{
    BspOsal_SemHandle      lock;
    /**< Global driver lock. */
    Bsp_Ds90uh925HandleObj handlePool[BSP_DEVICE_MAX_HANDLES];
    /**< Handle objects. */
} Bsp_Ds90uh925Obj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

Int32 Bsp_ds90uh925GetChipId(Bsp_Ds90uh925HandleObj       *pObj,
                             const Bsp_VidEncChipIdParams *pPrm,
                             Bsp_VidEncChipIdStatus       *pStatus);
Int32 Bsp_ds90uh925SetVideoMode(Bsp_Ds90uh925HandleObj       *pObj,
                                const Bsp_VidEncConfigParams *pPrm);
Int32 Bsp_ds90uh925Start(const Bsp_Ds90uh925HandleObj *pObj);
Int32 Bsp_ds90uh925Stop(const Bsp_Ds90uh925HandleObj *pObj);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef BSPDRV_DS90UH925_PRIV_H_ */
