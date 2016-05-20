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
 *  \file bspdrv_mt9v022Priv.h
 *
 *  \brief mt9v022 decoder internal header file.
 */

#ifndef BSPDRV_MT9V022_PRIV_H_
#define BSPDRV_MT9V022_PRIV_H_

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
#include <devices/bsp_videoSensor.h>
#include <mt9v022/bspdrv_mt9v022.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Driver object state - NOT IN USE. */
#define BSP_MT9V022_OBJ_STATE_UNUSED    (0U)
/** \brief Driver object state - IN USE and IDLE. */
#define BSP_MT9V022_OBJ_STATE_IDLE      (1U)

/*
 * MT9V022 Register Offsets.
 */
/** \brief Reset register. */
#define BSP_MT9V022_RESET_REG           (0x0CU)
/** \brief CHIP ID register. */
#define BSP_MT9V022_CHIP_ID_REG         (0xFFU)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief MT9V022 driver handle object.
 */
typedef struct
{
    UInt32                    state;
    /**< Handle state - used or free. */
    UInt32                    handleId;
    /**< Handle ID, 0..BSP_DEVICE_MAX_HANDLES-1. */
    BspOsal_SemHandle         lock;
    /**< Driver lock. */
    Bsp_VidSensorCreateParams createPrms;
    /**< Create time arguments. */
} Bsp_Mt9v022HandleObj;

/**
 *  \brief MT9V022 Global driver object.
 */
typedef struct
{
    BspOsal_SemHandle    lock;
    /* Global driver lock. */
    Bsp_Mt9v022HandleObj handlePool[BSP_DEVICE_MAX_HANDLES];
    /**< Handle objects. */
} Bsp_Mt9v022Obj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

Int32 Bsp_mt9v022Reset(Bsp_Mt9v022HandleObj *pObj);

Int32 Bsp_mt9v022GetChipId(Bsp_Mt9v022HandleObj            *pObj,
                           const Bsp_VidSensorChipIdParams *pPrm,
                           Bsp_VidSensorChipIdStatus       *pStatus);

Int32 Bsp_mt9v022Start(Bsp_Mt9v022HandleObj *pObj);
Int32 Bsp_mt9v022Stop(Bsp_Mt9v022HandleObj *pObj);

Int32 Bsp_mt9v022RegWrite(Bsp_Mt9v022HandleObj             *pObj,
                          const Bsp_VidSensorRegRdWrParams *pPrm);
Int32 Bsp_mt9v022RegRead(Bsp_Mt9v022HandleObj       *pObj,
                         Bsp_VidSensorRegRdWrParams *pPrm);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSPDRV_MT9V022_PRIV_H_  */
