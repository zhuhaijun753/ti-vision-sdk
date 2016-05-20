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
 *  \file bspdrv_imx224Priv.h
 *
 *  \brief imx224 decoder internal header file.
 */

#ifndef BSPDRV_IMX224_PRIV_H_
#define BSPDRV_IMX224_PRIV_H_

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
#include <imx224/bspdrv_imx224.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Driver object state - NOT IN USE. */
#define BSP_IMX224_OBJ_STATE_UNUSED                    (0U)
/** \brief Driver object state - IN USE and IDLE. */
#define BSP_IMX224_OBJ_STATE_IDLE                      (1U)

#define BSP_VID_SENSOR_IMX224_PID_MSB                  (0x24U)
#define BSP_VID_SENSOR_IMX224_PID_LSB                  (0x00U)

/*
 * IMX224 Register Offsets.
 */

/** < Register to set the operating mode of sensor : Streaming or Still
 *    capture*/
#define BSP_IMX224_SOFTWARE_RESET_REG                  (0x301AU)

#define BSP_IMX224_SOFTWARE_RESET_REG_VAL              (0x10D8U)

#define BSP_IMX224_OPERATING_MODE_REG_VAL              (0x10D8U)

#define BSP_IMX224_CHIP_ID_UPPER_REG                   (0x300AU)
/** < Address of chip ID MSB register */
#define BSP_IMX224_CHIP_ID_LOWER_REG                   (0x300BU)
/** <  Address of chip ID LSB register */

#define BSP_IMX224_NUM_REGS                            (255U * 4U + 1U)

#define BSP_IMX224_OUTPUT_DATA_FMT_MASK                (0x07U)
#define BSP_IMX224_OUTPUT_DATA_FMT_LONG_CH             (0x05U)
#define BSP_IMX224_OUTPUT_DATA_FMT_12BIT_COMP          (0x04U)

#define BSP_IMX224_MAX_INTG_LINES               (2050U)

#define BSP_IMX224_AE_CONTROL_SHORT_REG_ADDR_LOW   (0x3020)
#define BSP_IMX224_AE_CONTROL_SHORT_REG_ADDR_HIGH   ( \
        BSP_IMX224_AE_CONTROL_SHORT_REG_ADDR_LOW + 1)

#define BSP_IMX224_AE_CONTROL_LONG_REG_ADDR_LOW   (0x3023)
#define BSP_IMX224_AE_CONTROL_LONG_REG_ADDR_HIGH   ( \
        BSP_IMX224_AE_CONTROL_LONG_REG_ADDR_LOW + 1)

#define BSP_IMX224_VMAX                         (0x44cU)
#define BSP_IMX224_RHS                          (0x85U)

#define BSP_IMX224_MAX_ANALOG_GAIN      (16000)

#define BSP_IMX224_ANALOG_GAIN_CONTROL_REG_ADDR_LOW   (UInt16) (0x3014)
#define BSP_IMX224_ANALOG_GAIN_CONTROL_REG_ADDR_HIGH   ( \
        BSP_IMX224_ANALOG_GAIN_CONTROL_REG_ADDR_LOW + 1U)

#define BSP_IMX224_HCG_GAIN_CONTROL_REG_ADDR   (0x3009)

/*
 *  \brief DCC Camera ID for IMX224 Sensor
 */
#define BSP_IMX224_DCC_CAMERA_ID                    (224U)

/**
 *  \brief IMX224 driver handle object.
 */
typedef struct
{
    UInt32                    state;
    /**< Handle state - used or free. */
    UInt32                    handleId;
    /**< Handle ID, 0..BSP_DEVICE_MAX_HANDLES-1. */
    UInt32                    nDrvId;
    /**< Driver Id - IMX224 */
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
    UInt32                    maxCoarseIntgTime;
    /**< Max Coarse integration time supported by sensor */
    UInt32                    outputHeight;
    /**< Sensor Output Frame Height */
    Float                     lineIntgTimeInMs;
    /**< Line Integration time */
    Float                     pixIntgTimeInMs;
    /**< Pixel Integration time */
} Bsp_imx224HandleObj;

/**
 *  \brief IMX224 Global driver object.
 */
typedef struct
{
    BspOsal_SemHandle   lock;
    /* Global driver lock. */
    Bsp_imx224HandleObj handlePool[BSP_DEVICE_MAX_HANDLES];
    /**< Handle objects. */
} Bsp_imx224Obj;

Int32 Bsp_imx224GetChipId(Bsp_imx224HandleObj             *pObj,
                          const Bsp_VidSensorChipIdParams *pPrm,
                          Bsp_VidSensorChipIdStatus       *pStatus);

Int32 Bsp_imx224SoftwareReset(const Bsp_imx224HandleObj *pObj);

Int32 Bsp_imx224SensorStartStop(const Bsp_imx224HandleObj *pObj,
                                UInt32                     bStartSensor);

Int32 Bsp_imx224SensorConfig(
    Bsp_imx224HandleObj           *pObj,
    const Bsp_VidSensorConfigRegs *sensorConfig);

Int32 Bsp_imx224RegWrite(Bsp_imx224HandleObj              *pObj,
                         const Bsp_VidSensorRegRdWrParams *pPrm);

Int32 Bsp_imx224RegRead(const Bsp_imx224HandleObj        *pObj,
                        const Bsp_VidSensorRegRdWrParams *pPrm);

Int32 Bsp_imx224SensorGetExposureRatio(
    const Bsp_imx224HandleObj   *pObj,
    Bsp_VidSensorExpRatioParams *expRatioPrms);

Int32 Bsp_imx224SensorSetWdrParams(
    Bsp_imx224HandleObj          *pObj,
    const Bsp_VidSensorWdrParams *wdrPrms);

Int32 Bsp_imx224SetExpParams(const Bsp_imx224HandleObj *pObj,
                             const Bsp_VidSensorExposureParams *expPrms);

Int32 Bsp_imx224SetGainParams(const Bsp_imx224HandleObj     *pObj,
                              const Bsp_VidSensorGainParams *gainPrms);

Int32 Bsp_imx224SensorGetDccParams(
    const Bsp_imx224HandleObj *pObj,
    Bsp_VidSensorDccParams    *dccPrms);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSPDRV_IMX224_PRIV_H_  */

