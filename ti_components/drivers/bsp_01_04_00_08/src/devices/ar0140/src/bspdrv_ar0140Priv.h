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
 *  \file bspdrv_ar0140Priv.h
 *
 *  \brief ar0140 decoder internal header file.
 */

#ifndef BSPDRV_AR0140_PRIV_H_
#define BSPDRV_AR0140_PRIV_H_

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
#include <ar0140/bspdrv_ar0140.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Driver object state - NOT IN USE. */
#define BSP_AR0140_OBJ_STATE_UNUSED                    (0U)
/** \brief Driver object state - IN USE and IDLE. */
#define BSP_AR0140_OBJ_STATE_IDLE                      (1U)

#define BSP_VID_SENSOR_AR0140_PID_MSB                  (0x24U)
#define BSP_VID_SENSOR_AR0140_PID_LSB                  (0x00U)

#define BSP_AR0140_MIRROR_MODE_ENABLE_MASK             ((uint32_t) 0x1U << 14)
#define BSP_AR0140_FLIP_MODE_ENABLE_MASK               ((uint32_t) 0x1U << 15)

/*
 * AR0140 Register Offsets.
 */

/** < Register to set the operating mode of sensor : Streaming or Still
 *    capture*/
#define BSP_AR0140_SOFTWARE_RESET_REG                   (0x301AU)

#define BSP_AR0140_SOFTWARE_RESET_REG_VAL               (0x10D8U)

#define BSP_AR0140_OPERATING_MODE_REG_VAL               (0x10D8U)

/** < Address of chip ID MSB register */
#define BSP_AR0140_CHIP_ID_REG                          (0x3000U)

/** < Address of Analog Gain Register */
#define BSP_AR0140_ANALOG_GAIN_REG                      (0x3060U)

#define BSP_AR0140_NUM_REGS                             (320U)

#define BSP_AR0140_DEFAULT_EXP_RATIO                    (16U)

#define BSP_AR0140_EXP_RATIO_MULTIPLIER                 (51U)

#define BSP_AR0140_COARD_INTG_TIME_FRAME_SUBTRACT       (52U)

#define BSP_AR0140_DCC_CAMERA_ID                        (140U)

#define BSP_AR0140_SENSORS_DEFAULT_NUM_ELEM             (380U)
#define BSP_AR0140_SENSORS_LINEAR_NUM_ELEM              (11U)
#define BSP_AR0140_SENSORS_WDR_NUM_ELEM                 (404U)
#define BSP_AR0140_SENSORS_CFG_1280X720_NUM_ELEM        (13U)
#define BSP_AR0140_SENSORS_CFG_1280X800_NUM_ELEM        (13U)

#define BSP_AR0140_SENSOR_DLY_IN_MS_AFTER_RESET         (0xA)

/**
 *  \brief AR0140 driver handle object.
 */
typedef struct
{
    UInt32                    state;
    /**< Handle state - used or free. */
    UInt32                    handleId;
    /**< Handle ID, 0..BSP_DEVICE_MAX_HANDLES-1. */
    UInt32                    nDrvId;
    /**< Driver Id - AR0140 */
    BspOsal_SemHandle         lock;
    /**< Driver lock. */
    Bsp_VidSensorCreateParams createPrms;
    /**< Create time arguments. */
    Bsp_VidSensorConfigParams sensorConfig;
    /**< Sensor Configuration  */

    UInt32                    isWdrOutputEnabled;
    /**< Flag to indicate whether WDR Output is enabled or not */
    Bsp_VidSensorFlipParams   flipPrms;
    /**< Flipping parameters */
    UInt32                    maxCoarseIntgTime;
    /**< Max Coarse integration time supported by sensor */
    UInt32                    outputHeight;
    /**< Sensor Output Frame Height */

    Float                     lineIntgTimeInMs;
    Float                     pixIntgTimeInMs;
} Bsp_ar0140HandleObj;

/**
 *  \brief AR0140 Global driver object.
 */
typedef struct
{
    BspOsal_SemHandle   lock;
    /* Global driver lock. */
    Bsp_ar0140HandleObj handlePool[BSP_DEVICE_MAX_HANDLES];
    /**< Handle objects. */
} Bsp_ar0140Obj;

Int32 Bsp_ar0140GetChipId(Bsp_ar0140HandleObj             *pObj,
                          const Bsp_VidSensorChipIdParams *pPrm,
                          Bsp_VidSensorChipIdStatus       *pStatus);

Int32 Bsp_ar0140SoftwareReset(const Bsp_ar0140HandleObj *pObj);

Int32 Bsp_ar0140SensorStartStop(const Bsp_ar0140HandleObj *pObj,
                                UInt32                     bStartSensor);

Int32 Bsp_ar0140SensorConfig(Bsp_ar0140HandleObj     *pObj,
                             Bsp_VidSensorConfigRegs *sensorConfig,
                             UInt32                   numSensorConfigEntries);

Int32 Bsp_ar0140RegWrite(Bsp_ar0140HandleObj              *pObj,
                         const Bsp_VidSensorRegRdWrParams *pPrm);

Int32 Bsp_ar0140RegRead(const Bsp_ar0140HandleObj        *pObj,
                        const Bsp_VidSensorRegRdWrParams *pPrm);

Int32 Bsp_ar0140SetGainParams(const Bsp_ar0140HandleObj     *pObj,
                              const Bsp_VidSensorGainParams *gainPrms);

Int32 Bsp_ar0140SetExpParams(const Bsp_ar0140HandleObj         *pObj,
                             const Bsp_VidSensorExposureParams *expPrms);

Int32 Bsp_ar0140SensorGetExposureRatio(
    const Bsp_ar0140HandleObj   *pObj,
    Bsp_VidSensorExpRatioParams *expRatioPrms);

Int32 Bsp_ar0140SensorSetWdrParams(
    Bsp_ar0140HandleObj          *pObj,
    const Bsp_VidSensorWdrParams *wdrPrms);

Int32 Bsp_ar0140SensorGetDccParams(
    const Bsp_ar0140HandleObj *pObj,
    Bsp_VidSensorDccParams    *dccPrms);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSPDRV_AR0140_PRIV_H_  */

