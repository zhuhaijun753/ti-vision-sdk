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
 *  \file bspdrv_lcdCtrlPriv.h
 *
 *  \brief LCD Controller internal header file.
 */

#ifndef BSP_LCDCTRL_PRIV_H_
#define BSP_LCDCTRL_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <common/bsp_types.h>
#include <common/bsp_config.h>
#include <common/trace.h>
#include <osal/bsp_osal.h>
#include <common/bsp_utils.h>
#include <fvid2/fvid2_dataTypes.h>
#include <platforms/bsp_platform.h>
#include <devices/bsp_device.h>
#include <devices/bsp_lcdController.h>
#include <lcdCtrl/bspdrv_lcdCtrl.h>
#include <tlc59108/bsp_tlc59108.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define BSP_LCDCTRL_THREEFIVE_ENBKL       ((UInt32) BSP_TLC59108_PIN0)

#define BSP_LCDCTRL_THREEFIVE_AVDD_EN     ((UInt32) BSP_TLC59108_PIN1)

#define BSP_LCDCTRL_THREEFIVE_PWM         ((UInt32) BSP_TLC59108_PIN2)

#define BSP_LCDCTRL_THREEFIVE_STBYB       ((UInt32) BSP_TLC59108_PIN3)

#define BSP_LCDCTRL_THREEFIVE_UPDN        ((UInt32) BSP_TLC59108_PIN4)

#define BSP_LCDCTRL_THREEFIVE_DITH        ((UInt32) BSP_TLC59108_PIN5)

#define BSP_LCDCTRL_THREEFIVE_MODE3       ((UInt32) BSP_TLC59108_PIN6)

#define BSP_LCDCTRL_THREEFIVE_SHLR        ((UInt32) BSP_TLC59108_PIN7)

#define BSP_LCDCTRL_TLC59108_INST_0       (0x0)

#define BSP_LCDCTRL_TLC59108_INST_1       (0x1)

/** \brief Driver object state - NOT IN USE. */
#define BSP_LCDCTRL_OBJ_STATE_UNUSED    (0U)
/** \brief Driver object state - IN USE and IDLE. */
#define BSP_LCDCTRL_OBJ_STATE_IDLE      (1U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief TVP5158 driver handle object.
 */
typedef struct
{
    UInt32                  state;
    /**< Handle state - used or free. */
    UInt32                  handleId;
    /**< Handle ID, 0..BSP_DEVICE_MAX_HANDLES-1. */
    BspOsal_SemHandle       lock;
    /**< Driver lock. */
    Bsp_LcdCtrlCreateParams createPrms;
    /**< Create time arguments. */
} Bsp_LcdCtrlHandleObj;

/**
 *  \brief TVP5158 Global driver object.
 */
typedef struct
{
    BspOsal_SemHandle    lock;
    /* Global driver lock. */
    Bsp_LcdCtrlHandleObj handlePool[BSP_DEVICE_MAX_HANDLES];
    /**< Handle objects. */
} Bsp_LcdCtrlObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
void Tc358778_lcdBridgeInit(UInt32 deviceI2cInstId, UInt32 slaveAddr);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef BSP_LCDCTRL_PRIV_H_ */
