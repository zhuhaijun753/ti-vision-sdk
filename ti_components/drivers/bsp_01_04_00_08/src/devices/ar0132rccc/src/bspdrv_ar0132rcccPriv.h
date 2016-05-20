/******************************************************************************
 *                                                                            *
 * Copyright (c) 2014 Texas Instruments Incorporated - http://www.ti.com/     *
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
 *  \file bspdrv_ar0132rcccPriv.h
 *
 *  \brief ar0132rccc decoder internal header file.
 */

#ifndef BSPDRV_AR0132RCCC_PRIV_H_
#define BSPDRV_AR0132RCCC_PRIV_H_

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
#include <ar0132rccc/bspdrv_ar0132rccc.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Driver object state - NOT IN USE. */
#define BSP_AR0132RCCC_OBJ_STATE_UNUSED                    (0U)
/** \brief Driver object state - IN USE and IDLE. */
#define BSP_AR0132RCCC_OBJ_STATE_IDLE                      (1U)

#define BSP_VID_SENSOR_AR0132RCCC_PID_MSB                  (0x24U)
#define BSP_VID_SENSOR_AR0132RCCC_PID_LSB                  (0x00U)

/*
 * AR0132RCCC Register Offsets.
 */

/** < Register to set the operating mode of sensor : Streaming or Still
 *    capture*/
#define BSP_AR0132RCCC_SOFTWARE_RESET_REG                  (0x301AU)

#define BSP_AR0132RCCC_SOFTWARE_RESET_REG_VAL              (0x10D8U)

#define BSP_AR0132RCCC_OPERATING_MODE_REG_VAL              (0x10D8U)

#define BSP_AR0132RCCC_CHIP_ID_UPPER_REG                   (0x3000U)
/** < Address of chip ID MSB register */
#define BSP_AR0132RCCC_CHIP_ID_LOWER_REG                   (0x3001U)
/** <  Address of chip ID LSB register */

#define BSP_AR0132RCCC_NUM_REGS                            (322U)

/**
 *  \brief AR0132RCCC driver handle object.
 */
typedef struct
{
    UInt32                    state;
    /**< Handle state - used or free. */
    UInt32                    handleId;
    /**< Handle ID, 0..BSP_DEVICE_MAX_HANDLES-1. */
    UInt32                    nDrvId;
    /**< Driver Id - AR0132RCCC */
    BspOsal_SemHandle         lock;
    /**< Driver lock. */
    Bsp_VidSensorCreateParams createPrms;
    /**< Create time arguments. */
    Bsp_VidSensorConfigParams sensorConfig;
} Bsp_ar0132rcccHandleObj;

/**
 *  \brief AR0132RCCC Global driver object.
 */
typedef struct
{
    BspOsal_SemHandle       lock;
    /* Global driver lock. */
    Bsp_ar0132rcccHandleObj handlePool[BSP_DEVICE_MAX_HANDLES];
    /**< Handle objects. */
} Bsp_ar0132rcccObj;

Int32 Bsp_ar0132rcccGetChipId(Bsp_ar0132rcccHandleObj         *pObj,
                              const Bsp_VidSensorChipIdParams *pPrm,
                              Bsp_VidSensorChipIdStatus       *pStatus);

Int32 Bsp_ar0132rcccSoftwareReset(const Bsp_ar0132rcccHandleObj *pObj);

Int32 Bsp_ar0132rcccSensorStartStop(const Bsp_ar0132rcccHandleObj *pObj,
                                    UInt32                         bStartSensor);

Int32 Bsp_ar0132rcccSensorConfig(
    const Bsp_ar0132rcccHandleObj *pObj,
    Bsp_VidSensorConfigRegs       *sensorConfig,
    UInt32
    numSensorConfigEntries);

Int32 Bsp_ar0132rcccRegWrite(Bsp_ar0132rcccHandleObj          *pObj,
                             const Bsp_VidSensorRegRdWrParams *pPrm);

Int32 Bsp_ar0132rcccRegRead(Bsp_ar0132rcccHandleObj    *pObj,
                            Bsp_VidSensorRegRdWrParams *pPrm);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSPDRV_AR0132RCCC_PRIV_H_  */

