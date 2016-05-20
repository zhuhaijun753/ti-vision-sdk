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
 *  \file bspdrv_ar0132Priv.h
 *
 *  \brief ar0132 decoder internal header file.
 */

#ifndef BSPDRV_AR0132_PRIV_H_
#define BSPDRV_AR0132_PRIV_H_

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
#include <ar0132/bspdrv_ar0132.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Driver object state - NOT IN USE. */
#define BSP_AR0132_OBJ_STATE_UNUSED                    (0U)
/** \brief Driver object state - IN USE and IDLE. */
#define BSP_AR0132_OBJ_STATE_IDLE                      (1U)

#define BSP_VID_SENSOR_AR0132_PID_MSB                  (0x24U)
#define BSP_VID_SENSOR_AR0132_PID_LSB                  (0x00U)

/*
 * AR0132 Register Offsets.
 */

/** < Register to set the operating mode of sensor : Streaming or Still
 *    capture*/
#define BSP_AR0132_SOFTWARE_RESET_REG                  (0x301AU)

#define BSP_AR0132_SOFTWARE_RESET_REG_VAL              (0x10D8U)

#define BSP_AR0132_OPERATING_MODE_REG_VAL              (0x10D8U)

#define BSP_AR0132_CHIP_ID_UPPER_REG                   (0x3000U)
/** < Address of chip ID MSB register */
#define BSP_AR0132_CHIP_ID_LOWER_REG                   (0x3001U)
/** <  Address of chip ID LSB register */

#define BSP_AR0132_NUM_REGS                            (340U)

#define BSP_AR0132_DEFAULT_EXP_RATIO                    (256U)

#define BSP_AR0132_DLY_IN_MS_AFTER_RESET                (200)

/**
 *  \brief AR0132 driver handle object.
 */
typedef struct
{
    UInt32                    state;
    /**< Handle state - used or free. */
    UInt32                    handleId;
    /**< Handle ID, 0..BSP_DEVICE_MAX_HANDLES-1. */
    UInt32                    nDrvId;
    /**< Driver Id - AR0132 */
    BspOsal_SemHandle         lock;
    /**< Driver lock. */
    Bsp_VidSensorCreateParams createPrms;
    /**< Create time arguments. */
    Bsp_VidSensorConfigParams sensorConfig;
    Float                     lineIntgTimeInMs;
    Float                     pixIntgTimeInMs;

    UInt32                    isWdrEnabled;
    UInt32                    dataFormat;
} Bsp_ar0132HandleObj;

/**
 *  \brief AR0132 Global driver object.
 */
typedef struct
{
    BspOsal_SemHandle   lock;
    /* Global driver lock. */
    Bsp_ar0132HandleObj handlePool[BSP_DEVICE_MAX_HANDLES];
    /**< Handle objects. */
} Bsp_ar0132Obj;

Int32 Bsp_ar0132GetChipId(Bsp_ar0132HandleObj             *pObj,
                          const Bsp_VidSensorChipIdParams *pPrm,
                          Bsp_VidSensorChipIdStatus       *pStatus);

Int32 Bsp_ar0132SoftwareReset(const Bsp_ar0132HandleObj *pObj);

Int32 Bsp_ar0132SensorStartStop(const Bsp_ar0132HandleObj *pObj,
                                UInt32                     bStartSensor);

Int32 Bsp_ar0132SensorConfig(Bsp_ar0132HandleObj     *pObj,
                             Bsp_VidSensorConfigRegs *sensorConfig,
                             UInt32                   numSensorConfigEntries,
                             UInt32                   dataFormat);

Int32 Bsp_ar0132RegWrite(Bsp_ar0132HandleObj              *pObj,
                         const Bsp_VidSensorRegRdWrParams *pPrm);

Int32 Bsp_ar0132RegRead(Bsp_ar0132HandleObj        *pObj,
                        Bsp_VidSensorRegRdWrParams *pPrm);

Int32 Bsp_ar0132SensorGetExposureRatio(const Bsp_ar0132HandleObj   *pObj,
                             Bsp_VidSensorExpRatioParams *expRatioPrms);

Int32 Bsp_ar0132SensorSetWdrParams(Bsp_ar0132HandleObj   *pObj,
                                   const Bsp_VidSensorWdrParams *wdrPrms);
Int32 Bsp_ar0132SensorGetDccParams(
    const Bsp_ar0132HandleObj *pObj,
    Bsp_VidSensorDccParams    *dccPrms);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSPDRV_AR0132_PRIV_H_  */

