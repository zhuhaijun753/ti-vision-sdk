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
 *  \file bspdrv_ov10640Priv.h
 *
 *  \brief ov10640 decoder internal header file.
 */

#ifndef BSPDRV_OV10640_PRIV_H_
#define BSPDRV_OV10640_PRIV_H_

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
#include <ov10640/bspdrv_ov10640.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Driver object state - NOT IN USE. */
#define BSP_OV10640_OBJ_STATE_UNUSED                    (0U)
/** \brief Driver object state - IN USE and IDLE. */
#define BSP_OV10640_OBJ_STATE_IDLE                      (1U)

#define BSP_VID_SENSOR_OV10640_PID_MSB                  (0x24U)
#define BSP_VID_SENSOR_OV10640_PID_LSB                  (0x00U)

/*
 * OV10640 Register Offsets.
 */

/** < Register to set the operating mode of sensor : Streaming or Still
 *    capture*/
#define BSP_OV10640_SOFTWARE_RESET_REG                  (0x301AU)

#define BSP_OV10640_SOFTWARE_RESET_REG_VAL              (0x10D8U)

#define BSP_OV10640_OPERATING_MODE_REG_VAL              (0x10D8U)

#define BSP_OV10640_CHIP_ID_UPPER_REG                   (0x300AU)
/** < Address of chip ID MSB register */
#define BSP_OV10640_CHIP_ID_LOWER_REG                   (0x300BU)
/** <  Address of chip ID LSB register */
#define BSP_OV10640_CHIP_ID_REV_ID                      (0x300DU)
/** <  Address of chip ID LSB register */

#define BSP_OV10640_NUM_REGS                            (1285U)

#define BSP_OV10640_OUTPUT_DATA_FMT_MASK                (0x07U)
#define BSP_OV10640_OUTPUT_DATA_FMT_LONG_CH             (0x05U)
#define BSP_OV10640_OUTPUT_DATA_FMT_12BIT_COMP          (0x04U)

#define BSP_OV10640_DCC_CAMERA_ID                       (10640U)

#define BSP_OV10640_MIRROR_OFFSET_ENABLE_MASK           (0x2U)
#define BSP_OV10640_FLIP_OFFSET_ENABLE_MASK             (0x4U)

#define BSP_OV10640_MIRROR_MODE_ENABLE_MASK             (0x4U)
#define BSP_OV10640_FLIP_MODE_ENABLE_MASK               (0x8U)

#define BSP_OV10640_DLY_IN_MS                           (0xA)

/**
 *  \brief OV10640 driver handle object.
 */
typedef struct
{
    UInt32                    state;
    /**< Handle state - used or free. */
    UInt32                    handleId;
    /**< Handle ID, 0..BSP_DEVICE_MAX_HANDLES-1. */
    UInt32                    nDrvId;
    /**< Driver Id - OV10640 */
    UInt32                    instId;
    /*< Driver instance id */
    BspOsal_SemHandle         lock;
    /**< Driver lock. */
    Bsp_VidSensorCreateParams createPrms;
    /**< Create time arguments. */
    Bsp_VidSensorConfigParams sensorConfig;
    /**< Sensor Configuration */
    UInt32                    isWdrOutputEnabled;
    /**< Flag to indicate whether WDR output is enabled or not. */
    Bsp_VidSensorFlipParams   flipPrms;
    /**< Flipping parameters */
} Bsp_ov10640HandleObj;

/**
 *  \brief OV10640 Global driver object.
 */
typedef struct
{
    BspOsal_SemHandle    lock;
    /* Global driver lock. */
    Bsp_ov10640HandleObj handlePool[BSP_DEVICE_MAX_HANDLES];
    /**< Handle objects. */
} Bsp_ov10640Obj;

Int32 Bsp_ov10640GetChipId(Bsp_ov10640HandleObj            *pObj,
                           const Bsp_VidSensorChipIdParams *pPrm,
                           Bsp_VidSensorChipIdStatus       *pStatus);

Int32 Bsp_ov10640SoftwareReset(const Bsp_ov10640HandleObj *pObj);

Int32 Bsp_ov10640SensorStartStop(const Bsp_ov10640HandleObj *pObj,
                                 UInt32                      bStartSensor);

Int32 Bsp_ov10640SensorConfig(
    Bsp_ov10640HandleObj          *pObj,
    const Bsp_VidSensorConfigRegs *sensorConfig);

Int32 Bsp_ov10640RegWrite(Bsp_ov10640HandleObj             *pObj,
                          const Bsp_VidSensorRegRdWrParams *pPrm);

Int32 Bsp_ov10640RegRead(const Bsp_ov10640HandleObj       *pObj,
                         const Bsp_VidSensorRegRdWrParams *pPrm);

Int32 Bsp_ov10640SensorGetExposureRatio(
    const Bsp_ov10640HandleObj  *pObj,
    Bsp_VidSensorExpRatioParams *expRatioPrms);

Int32 Bsp_ov10640SensorSetWdrParams(
    Bsp_ov10640HandleObj         *pObj,
    const Bsp_VidSensorWdrParams *wdrPrms);

Int32 Bsp_ov10640SensorGetDccParams(
    const Bsp_ov10640HandleObj *pObj,
    Bsp_VidSensorDccParams     *dccPrms);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSPDRV_OV10640_PRIV_H_  */

