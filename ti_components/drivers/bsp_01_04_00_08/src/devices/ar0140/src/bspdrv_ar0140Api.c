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
 *  \file bspdrv_ar0140Api.c
 *
 *  \brief AR0140 video sensor FVID2 driver API file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ar0140/src/bspdrv_ar0140Priv.h>
#include <ar0140/src/bspdrv_ar0140Reg.h>
#include <ar0140/src/bspdrv_ar0140_default_setup.h>
#include <ar0140/src/bspdrv_ar0140_1280x720_60fps_Linear.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static Bsp_VidSensorConfigRegs gBsp_AR0140SensorsDefault[
    BSP_AR0140_SENSORS_DEFAULT_NUM_ELEM] = BSP_AR0140SENSORS_DEFAULT;
static Bsp_VidSensorConfigRegs gBsp_AR0140SensorsLinear[
    BSP_AR0140_SENSORS_LINEAR_NUM_ELEM] = BSP_AR0140SENSORS_LINEAR;
static Bsp_VidSensorConfigRegs gBsp_AR0140SensorsCfg1280x720[
    BSP_AR0140_SENSORS_CFG_1280X720_NUM_ELEM] = BSP_AR0140SENSORS_CFG_1280x720;
static Bsp_VidSensorConfigRegs gBsp_AR0140SensorsCfg1280x800[
    BSP_AR0140_SENSORS_CFG_1280X800_NUM_ELEM] = BSP_AR0140SENSORS_CFG_1280x800;
static Bsp_VidSensorConfigRegs gBps_AR0140TIDA00262Linear720P30[] = \
    BSP_AR0140SENSORS_DEFAULT;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif
static Int32 Bsp_ar0140Control(Fdrv_Handle handle,
                               UInt32      cmd,
                               Ptr         cmdArgs,
                               Ptr         cmdStatusArgs);

static Fdrv_Handle Bsp_ar0140Create(UInt32                   nDrvId,
                                    UInt32                   instId,
                                    Ptr                      createPrms,
                                    Ptr                      createStatusArgs,
                                    const Fvid2_DrvCbParams *fdmCbPrms);

static Int32 Bsp_ar0140Delete(Fdrv_Handle handle, Ptr deleteArgs);
#ifdef __cplusplus
}
#endif
static Int32 Bsp_ar0140Unlock(void);
static Int32 Bsp_ar0140Lock(void);
static Int32 Bsp_ar0140LockObj(Bsp_ar0140HandleObj *pObj);
static Int32 Bsp_ar0140UnlockObj(Bsp_ar0140HandleObj *pObj);
static Int32 Bsp_ar0140FreeObj(Bsp_ar0140HandleObj *pObj);
static Bsp_ar0140HandleObj *Bsp_ar0140AllocObj(void);
static Int32 Bsp_ar0140SensorSetConfig(
    Bsp_ar0140HandleObj             *pObj,
    const Bsp_VidSensorConfigParams *cfgPrms);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief AR0140 driver function pointer. */
static const Fvid2_DrvOps          gBspAr0140DrvOps =
{
    FVID2_VID_SENSOR_APT_AR0140_DRV,       /* Driver ID */
    &Bsp_ar0140Create,                     /* Create */
    &Bsp_ar0140Delete,                     /* Delete */
    &Bsp_ar0140Control,                    /* Control */
    NULL,                                  /* Queue */
    NULL,                                  /* Dequeue */
    NULL,                                  /* ProcessFrames */
    NULL,                                  /* GetProcessedFrames */
    NULL,                                  /* ProcessRequest */
    NULL                                   /* GetProcessedRequest */
};

/** \brief TIDA00262 AR0140 driver function pointer. */
static const Fvid2_DrvOps          gBspTida00262Ar0140DrvOps =
{
    FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV,  /* Driver ID */
    &Bsp_ar0140Create,                          /* Create */
    &Bsp_ar0140Delete,                          /* Delete */
    &Bsp_ar0140Control,                         /* Control */
    NULL,                                       /* Queue */
    NULL,                                       /* Dequeue */
    NULL,                                       /* ProcessFrames */
    NULL,                                       /* GetProcessedFrames */
    NULL,                                       /* ProcessRequest */
    NULL                                        /* GetProcessedRequest */
};

/** \brief AR0140 driver function pointer For Single Pass WDR Flow. */
static const Fvid2_DrvOps          gBspAr0140DrvOnePassWdrOps =
{
    FVID2_VID_SENSOR_APT_AR0140_ONEPASSWDR_DRV, /* Driver ID */
    &Bsp_ar0140Create,                          /* Create */
    &Bsp_ar0140Delete,                          /* Delete */
    &Bsp_ar0140Control,                         /* Control */
    NULL,                                       /* Queue */
    NULL,                                       /* Dequeue */
    NULL,                                       /* ProcessFrames */
    NULL,                                       /* GetProcessedFrames */
    NULL,                                       /* ProcessRequest */
    NULL                                        /* GetProcessedRequest */
};

/**< \brief Global object containing AR0140 sensor driver features */
static const Bsp_VidSensorFeatures gBspAR0140SensorFeatures =
{
    BSP_VID_SENSOR_APT_AR0140,      /* SensorId */
    0x0,                            /* Chip Id, read from register */
    0x0,                            /* Revision Id, read from register */
    0x0,                            /* firmware version, read from register */
    FVID2_DF_BAYER_GRBG,            /* Bayer format */
    1280U,                          /* Active Width */
    720U,                           /* Active Height */
    FALSE,                          /* isEmbededDataSupported */
    TRUE,                           /* isManualExposureSupported */
    FALSE,                          /* isEepromDataSupported */
    FALSE,                          /* isSoftStandbySupported */
    TRUE,                           /* isFlipSupported */
    TRUE,                           /* isManualAnalogGainSupported */
    TRUE,                           /* isWdrModeSupported */
    TRUE,                           /* isSetCfgSupported */
    TRUE                            /* isDccCfgSupported */
};

/**
 *  \brief Global object storing all information related to all AR0140 driver
 *  handles.
 */
static Bsp_ar0140Obj gBspar0140Obj;

/**
 *  \brief System init for AR0140  driver
 *
 *  This API
 *      - create semaphore locks needed
 *      - registers driver to FVID2 sub-system
 *      - gets called as part of Bsp_deviceInit()
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_ar0140Init(void)
{
    Int32 status = FVID2_SOK;
    Int32 initValue;
    UInt32 idx, numEle;

    /* Memset global object */
    BspUtils_memset(&gBspar0140Obj, 0, sizeof (gBspar0140Obj));

    /* Create global AR0140 lock */
    initValue          = 1;
    gBspar0140Obj.lock = BspOsal_semCreate(initValue, (Bool) TRUE);
    if (NULL == gBspar0140Obj.lock)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Global semaphore create failed\n");
        status = FVID2_EALLOC;
    }

    if (FVID2_SOK == status)
    {
        /* Register AR0140 driver with FVID2 sub-system */
        status = Fvid2_registerDriver(&gBspAr0140DrvOps);
        if (FVID2_SOK != status)
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      "Registering AR0140 to FVID2 driver manager failed\n");
            /* Error - free acquired resources */
            BspOsal_semDelete(&gBspar0140Obj.lock);
        }
    }

    if (FVID2_SOK == status)
    {
        /* Register AR0140 driver with FVID2 sub-system */
        status = Fvid2_registerDriver(&gBspTida00262Ar0140DrvOps);
        if (FVID2_SOK != status)
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      "Registering TIDA00262 to FVID2 driver manager failed\n");
            Fvid2_unRegisterDriver(&gBspAr0140DrvOps);
            BspOsal_semDelete(&gBspar0140Obj.lock);
        }
    }

    if (FVID2_SOK == status)
    {
        /* Register AR0140 driver with FVID2 sub-system */
        status = Fvid2_registerDriver(&gBspAr0140DrvOnePassWdrOps);
        if (FVID2_SOK != status)
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      "Registering FVID2 driver manager "
                      "failed for SinglePassWDR\n");
            Fvid2_unRegisterDriver(&gBspTida00262Ar0140DrvOps);
            Fvid2_unRegisterDriver(&gBspAr0140DrvOps);
            BspOsal_semDelete(&gBspar0140Obj.lock);
        }
    }

    /* Over ride default for TIDA00262 AR0140 sensor config */
    numEle = sizeof (gBps_AR0140TIDA00262Linear720P30) /
                    sizeof (gBps_AR0140TIDA00262Linear720P30[0U]);
    for (idx = 0U; idx < numEle; idx++)
    {
        if (0x302A == gBps_AR0140TIDA00262Linear720P30[idx].regAddr)
        {
            gBps_AR0140TIDA00262Linear720P30[idx].regValue = 0x5;
        }
        if (0x3030 == gBps_AR0140TIDA00262Linear720P30[idx].regAddr)
        {
            gBps_AR0140TIDA00262Linear720P30[idx].regValue = 0x3C;
        }
        if (0x300A == gBps_AR0140TIDA00262Linear720P30[idx].regAddr)
        {
            gBps_AR0140TIDA00262Linear720P30[idx].regValue = 0x05AA;
        }
    }
    return (status);
}

/**
 *  \brief System de-init for AR0140 driver
 *
 *  This API
 *      - de-registers driver from FVID2 sub-system
 *      - delete's allocated semaphore locks
 *      - gets called as part of Bsp_deviceDeInit()
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_ar0140DeInit(void)
{
    /* Unregister FVID2 driver */
    Fvid2_unRegisterDriver(&gBspAr0140DrvOps);
    Fvid2_unRegisterDriver(&gBspTida00262Ar0140DrvOps);
    Fvid2_unRegisterDriver(&gBspAr0140DrvOnePassWdrOps);

    /* Delete semaphore's. */
    BspOsal_semDelete(&gBspar0140Obj.lock);

    return (FVID2_SOK);
}

/**
 *  \brief AR0140 create API that gets called when Fvid2_create is called.
 *
 *  This API does not configure the AR0140 is any way.
 *
 *  This API
 *      - validates parameters
 *      - allocates driver handle
 *      - stores create arguments in its internal data structure.
 *
 *  Later the create arguments will be used when doing I2C communcation with
 *  AR0140.
 *
 *  \param drvId            [IN] Driver ID, must be
 *                          either FVID2_VID_SENSOR_AR0140_DRV
 *  \param instId           [IN] Must be 0.
 *  \param createPrms       [IN] Create arguments - pointer to valid
 *                          Bsp_VidSensorCreateParams. This parameter should
 *                          be non-NULL.
 *  \param createStatusArgs [OUT] AR0140 driver return parameter -
 *                          pointer to Bsp_VidSensorCreateStatus.
 *                          This parameter could be NULL and the driver fills
 *                          the status information only if this is not NULL.
 *  \param fdmCbPrms        [IN] Not used. Set to NULL
 *
 *  \return                 Returns NULL in case of any error. Otherwise
 *                          returns a valid handle.
 */
static Fdrv_Handle Bsp_ar0140Create(UInt32                   nDrvId,
                                    UInt32                   instId,
                                    Ptr                      createPrms,
                                    Ptr                      createStatusArgs,
                                    const Fvid2_DrvCbParams *fdmCbPrms)
{
    Int32 status = FVID2_SOK;
    Bsp_ar0140HandleObj       *pObj = NULL;
    Bsp_VidSensorCreateParams *sensorCreatePrms;
    Bsp_VidSensorCreateStatus *sensorCreateStatus;

    /* Check parameters */
    if ((NULL == createPrms) ||
        ((FVID2_VID_SENSOR_APT_AR0140_DRV != nDrvId) &&
         (FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV != nDrvId) &&
         (FVID2_VID_SENSOR_APT_AR0140_ONEPASSWDR_DRV != nDrvId)))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        sensorCreatePrms = (Bsp_VidSensorCreateParams *) createPrms;
        if (sensorCreatePrms->deviceI2cInstId >= BSP_DEVICE_I2C_INST_ID_MAX)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Invalid I2C instance ID\n");
            status = FVID2_EINVALID_PARAMS;
        }
        if (sensorCreatePrms->numDevicesAtPort >=
            BSP_VID_SENSOR_DEV_PER_PORT_MAX)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Invalid device per port\n");
            status = FVID2_EINVALID_PARAMS;
        }
    }

    if (FVID2_SOK == status)
    {
        /* Allocate driver handle */
        pObj = Bsp_ar0140AllocObj();
        if (NULL == pObj)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Alloc object failed\n");
            status = FVID2_EALLOC;
        }
    }

    if (FVID2_SOK == status)
    {
        /* Store the Driver ID in pObj */
        pObj->nDrvId = nDrvId;

        /* Reset flip parameters */
        pObj->flipPrms.hFlip = FALSE;
        pObj->flipPrms.vFlip = FALSE;
    }

    if (FVID2_SOK == status)
    {
        /* Copy parameters to allocate driver handle */
        BspUtils_memcpy(
            &pObj->createPrms,
            sensorCreatePrms,
            sizeof (*sensorCreatePrms));
    }

    if (FVID2_SOK == status)
    {
        if (sensorCreatePrms->sensorCfg == NULL)
        {
            if (FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV == nDrvId)
            {
                status = Bsp_ar0140SensorConfig(pObj,
                            &gBps_AR0140TIDA00262Linear720P30[0U],
                            (sizeof (gBps_AR0140TIDA00262Linear720P30) /
                                sizeof (gBps_AR0140TIDA00262Linear720P30[0U])));

            }
            else
            {
                /* Configure sensor with default configuration :1280x720 */
                status = Bsp_ar0140SensorConfig(pObj, NULL, 0);
            }
        }
        else
        {
            status = Bsp_ar0140SensorConfig(pObj,
                                            sensorCreatePrms->sensorCfg,
                                            sensorCreatePrms->numSensorCfg);
        }

        pObj->sensorConfig.dataformat   = FVID2_DF_RAW12;
        pObj->sensorConfig.standard     = FVID2_STD_720P_60;
        pObj->sensorConfig.fps          = FVID2_FPS_60;
        pObj->sensorConfig.videoIfWidth = FVID2_VIFW_12BIT;
    }

    if ((FVID2_SOK != status) && (pObj != NULL))
    {
        Bsp_ar0140FreeObj(pObj);
        pObj = NULL;
    }

    /* Fill the status if possible */
    if (NULL != createStatusArgs)
    {
        sensorCreateStatus =
            (Bsp_VidSensorCreateStatus *) createStatusArgs;
        sensorCreateStatus->retVal = status;
    }

    return (pObj);
}

/**
 *  \brief Delete function that is called when Fvid2_delete is called.
 *
 *  This API
 *      - free's driver handle object
 *
 *  \param handle           [IN] Driver handle.
 *  \param deleteArgs       [IN] Not used currently. Meant for future purpose.
 *                          Set this to NULL.
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code. *
 */
static Int32 Bsp_ar0140Delete(Fdrv_Handle handle, Ptr deleteArgs)
{
    Int32 status = FVID2_SOK;
    Bsp_ar0140HandleObj *pObj;

    /* Check parameters */
    if (NULL == handle)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        /* Free driver handle object */
        pObj   = (Bsp_ar0140HandleObj *) handle;
        status = Bsp_ar0140FreeObj(pObj);
        if (FVID2_SOK != status)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Free object failed\n");
        }
    }

    return (status);
}

/**
 *  \brief Control API that gets called when Fvid2_control is called.
 *
 *  This API does handle level semaphore locking
 *
 *  \param handle           [IN] AR0140 driver handle returned by
 *                          create function.
 *  \param cmd              [IN] Supports the standard video decoder interface
 *                          commands.
 *  \param cmdArgs          [IN] Depending on the command this will vary.
 *  \param cmdStatusArgs    [OUT] Depending on the command this will vary.
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error codes for illegal parameters and
 *                          I2C command RX/TX error.
 */
static Int32 Bsp_ar0140Control(Fdrv_Handle handle,
                               UInt32      cmd,
                               Ptr         cmdArgs,
                               Ptr         cmdStatusArgs)
{
    Int32 status = FVID2_SOK;
    Bsp_ar0140HandleObj *pObj = NULL;
    /* Check parameters */
    if (NULL == handle)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        pObj = (Bsp_ar0140HandleObj *) handle;

        /* lock handle */
        Bsp_ar0140LockObj(pObj);

        switch (cmd)
        {
            case IOCTL_BSP_VID_SENSOR_RESET:
                status = Bsp_ar0140SoftwareReset(pObj);
                break;

            case IOCTL_BSP_VID_SENSOR_GET_CHIP_ID:
                status = Bsp_ar0140GetChipId(
                    pObj,
                    (Bsp_VidSensorChipIdParams *) cmdArgs,
                    (Bsp_VidSensorChipIdStatus *) cmdStatusArgs);
                break;

            case FVID2_START:
                status = FVID2_SOK;
                break;

            case FVID2_STOP:
                status = FVID2_SOK;
                break;

            case IOCTL_BSP_VID_SENSOR_REG_WRITE:
                status = Bsp_ar0140RegWrite(
                    pObj,
                    (Bsp_VidSensorRegRdWrParams *) cmdArgs);
                break;

            case IOCTL_BSP_VID_SENSOR_REG_READ:
                status = Bsp_ar0140RegRead(
                    pObj,
                    (Bsp_VidSensorRegRdWrParams *) cmdArgs);
                break;

            case IOCTL_BSP_VID_SENSOR_GET_FEATURES:
                BspUtils_memcpy((Bsp_VidSensorFeatures *) cmdArgs,
                                &gBspAR0140SensorFeatures,
                                sizeof (Bsp_VidSensorFeatures));
                break;

            case IOCTL_BSP_VID_SENSOR_SET_CONFIG:
                status = Bsp_ar0140SensorSetConfig(
                    pObj,
                    (Bsp_VidSensorConfigParams *) cmdArgs);
                break;

            case IOCTL_BSP_VID_SENSOR_GET_CONFIG:
                BspUtils_memcpy((Bsp_VidSensorConfigParams *) cmdArgs,
                                &pObj->sensorConfig,
                                sizeof (Bsp_VidSensorConfigParams));
                break;

            case IOCTL_BSP_VID_SENSOR_SET_EXP_PARAMS:
                if (NULL != cmdArgs)
                {
                    status = Bsp_ar0140SetExpParams(
                        pObj,
                        (Bsp_VidSensorExposureParams *) cmdArgs);
                }
                else
                {
                    status = FVID2_EBADARGS;
                }
                break;

            case IOCTL_BSP_VID_SENSOR_SET_GAIN_PARAMS:
                if (NULL != cmdArgs)
                {
                    status = Bsp_ar0140SetGainParams(
                        pObj,
                        (Bsp_VidSensorGainParams *) cmdArgs);
                }
                else
                {
                    status = FVID2_EBADARGS;
                }
                break;

            case IOCTL_BSP_VID_SENSOR_GET_EXP_RATIO_PARAMS:
                status = Bsp_ar0140SensorGetExposureRatio(
                    pObj,
                    (Bsp_VidSensorExpRatioParams *) cmdArgs);
                break;

            case IOCTL_BSP_VID_SENSOR_SET_WDR_PARAMS:
                status = Bsp_ar0140SensorSetWdrParams(
                    pObj,
                    (Bsp_VidSensorWdrParams *) cmdArgs);
                break;

            case IOCTL_BSP_VID_SENSOR_GET_DCC_PARAMS:
                status = Bsp_ar0140SensorGetDccParams(
                    pObj,
                    (Bsp_VidSensorDccParams *) cmdArgs);
                break;
            case IOCTL_BSP_VID_SENSOR_SET_FLIP_PARAMS:
            {
                Bsp_VidSensorFlipParams *flipPrms;

                flipPrms = (Bsp_VidSensorFlipParams *)cmdArgs;
                if (NULL != cmdArgs)
                {
                    BspUtils_memcpy(
                        &pObj->flipPrms,
                        flipPrms,
                        sizeof(Bsp_VidSensorFlipParams));
                }
                else
                {
                    status = FVID2_EBADARGS;
                }
                break;
            }
            default:
                GT_0trace(BspDeviceTrace, GT_ERR, "Unsupported command\n");
                status = FVID2_EUNSUPPORTED_CMD;
                break;
        }

        /* Unlock handle */
        Bsp_ar0140UnlockObj(pObj);
    }

    return (status);
}

/**
 *  \brief Allocates driver object.
 *
 *  Searches in list of driver handles and allocate's a 'NOT IN USE' handle
 *  Also create's handle level semaphore lock.
 *
 *  Returns NULL in case handle could not be allocated.
 */
static Bsp_ar0140HandleObj *Bsp_ar0140AllocObj(void)
{
    UInt32 handleId;
    Bsp_ar0140HandleObj *pObj = NULL;
    Int32  initValue;

    /* Take global lock to avoid race condition */
    Bsp_ar0140Lock();

    /* Find a unallocated object in pool */
    for (handleId = 0U; handleId < BSP_DEVICE_MAX_HANDLES; handleId++)
    {
        if (BSP_AR0140_OBJ_STATE_UNUSED ==
            gBspar0140Obj.handlePool[handleId].state)
        {
            /* Free object found */
            pObj = &gBspar0140Obj.handlePool[handleId];

            /* Init state and handle ID */
            BspUtils_memset(pObj, 0, sizeof (*pObj));
            pObj->state    = BSP_AR0140_OBJ_STATE_IDLE;
            pObj->handleId = handleId;

            /* Create driver object specific semaphore lock */
            initValue  = 1;
            pObj->lock = BspOsal_semCreate(initValue, (Bool) TRUE);
            if (NULL == pObj->lock)
            {
                GT_0trace(BspDeviceTrace, GT_ERR,
                          "Handle semaphore create failed\n");
                /* Error - release object */
                pObj->state = BSP_AR0140_OBJ_STATE_UNUSED;
                pObj        = NULL;
            }
            break;
        }
    }

    /* Release global lock */
    Bsp_ar0140Unlock();

    return (pObj);
}

/**
 *  \brief De-Allocate driver object.
 *
 *  Marks handle as 'NOT IN USE'.
 *  Also delete's handle level semaphore lock.
 */
static Int32 Bsp_ar0140FreeObj(Bsp_ar0140HandleObj *pObj)
{
    Int32 status = FVID2_EFAIL;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    /* Take global lock to avoid race condition */
    Bsp_ar0140Lock();

    if (pObj->state != BSP_AR0140_OBJ_STATE_UNUSED)
    {
        /* Mark state as unused */
        pObj->state = BSP_AR0140_OBJ_STATE_UNUSED;

        /* Delete object locking semaphore */
        BspOsal_semDelete(&pObj->lock);

        status = FVID2_SOK;
    }

    /* Release global lock */
    Bsp_ar0140Unlock();

    return (status);
}

/**
 *  \brief Handle level lock.
 */
static Int32 Bsp_ar0140LockObj(Bsp_ar0140HandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    BspOsal_semWait(pObj->lock, BSP_OSAL_WAIT_FOREVER);

    return (FVID2_SOK);
}

/**
 *  \brief Handle level unlock
 */
static Int32 Bsp_ar0140UnlockObj(Bsp_ar0140HandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    BspOsal_semPost(pObj->lock);

    return (FVID2_SOK);
}

/**
 *  \brief Global driver level lock.
 */
static Int32 Bsp_ar0140Lock(void)
{
    BspOsal_semWait(gBspar0140Obj.lock, BSP_OSAL_WAIT_FOREVER);

    return (FVID2_SOK);
}

/**
 *  \brief Global driver level unlock.
 */
static Int32 Bsp_ar0140Unlock(void)
{
    BspOsal_semPost(gBspar0140Obj.lock);

    return (FVID2_SOK);
}

/**
 *  \brief Set the Configuration
 */
static Int32 Bsp_ar0140SensorSetConfig(
    Bsp_ar0140HandleObj             *pObj,
    const Bsp_VidSensorConfigParams *cfgPrms)
{
    Int32  status = FVID2_SOK;
    UInt32 numRegs;
    Bsp_VidSensorConfigRegs *sensorRegs = NULL;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    GT_assert(BspDeviceTrace, (NULL != cfgPrms));

    if ((FVID2_VIFW_12BIT != cfgPrms->videoIfWidth) &&
        (FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV != pObj->nDrvId))
    {
        status = FVID2_EBADARGS;
    }
    else
    {
        pObj->sensorConfig.videoIfWidth = cfgPrms->videoIfWidth;
    }

    /* Only two resolutions are supported */
    if ((FVID2_STD_720P_60 != cfgPrms->standard) &&
        (FVID2_STD_WXGA_30 != cfgPrms->standard))
    {
        status = FVID2_EBADARGS;
    }

    if ((FVID2_VID_SENSOR_TIDA00262_APT_AR0140_DRV == pObj->nDrvId) &&
        (FVID2_SOK == status))
    {
        /* We have already set TIDA00262 default, set Linear mode now */
        sensorRegs = gBsp_AR0140SensorsLinear;
        numRegs    = (sizeof (gBsp_AR0140SensorsLinear) /
                      sizeof (gBsp_AR0140SensorsLinear[0]));

        status = Bsp_ar0140SensorConfig(pObj, sensorRegs, numRegs);

        sensorRegs = gBsp_AR0140SensorsCfg1280x800;
        numRegs    = (sizeof (gBsp_AR0140SensorsCfg1280x800) /
                      sizeof (gBsp_AR0140SensorsCfg1280x800[0]));

        status = Bsp_ar0140SensorConfig(pObj, sensorRegs, numRegs);

        if (FVID2_SOK == status)
        {
            pObj->sensorConfig.dataformat = FVID2_DF_BAYER_GRBG;

            pObj->sensorConfig.standard = FVID2_STD_WXGA_30;
            pObj->outputHeight          = 800U;
            pObj->sensorConfig.fps          = FVID2_FPS_30;
            pObj->sensorConfig.videoIfWidth = FVID2_VIFW_12BIT;
            pObj->sensorConfig.bpp          = FVID2_BPP_BITS12;

            /* By Default WDR Mode is disabled */
            pObj->isWdrOutputEnabled = FALSE;

            /* For Linear mode, coarse integration time is height - 52U */
            pObj->maxCoarseIntgTime = pObj->outputHeight - 52U;
        }
    }
    else if (FVID2_SOK == status)
    {
        /* Set the default Settings first */
        sensorRegs = gBsp_AR0140SensorsDefault;
        numRegs    = (sizeof (gBsp_AR0140SensorsDefault) /
                      sizeof (gBsp_AR0140SensorsDefault[0]));

        status = Bsp_ar0140SensorConfig(pObj, sensorRegs, numRegs);

        if (FVID2_SOK == status)
        {
            /* Set the Linear Mode By Default */
            sensorRegs = gBsp_AR0140SensorsLinear;
            numRegs    = (sizeof (gBsp_AR0140SensorsLinear) /
                          sizeof (gBsp_AR0140SensorsLinear[0]));

            status = Bsp_ar0140SensorConfig(pObj, sensorRegs, numRegs);
        }

        if (FVID2_SOK == status)
        {
            /* Set the Resolution */
            if (FVID2_STD_720P_60 == cfgPrms->standard)
            {
                sensorRegs = gBsp_AR0140SensorsCfg1280x720;
                numRegs    = (sizeof (gBsp_AR0140SensorsCfg1280x720) /
                              sizeof (gBsp_AR0140SensorsCfg1280x720[0]));
            }
            else
            {
                sensorRegs = gBsp_AR0140SensorsCfg1280x800;
                numRegs    = (sizeof (gBsp_AR0140SensorsCfg1280x800) /
                              sizeof (gBsp_AR0140SensorsCfg1280x800[0]));
            }

            status = Bsp_ar0140SensorConfig(pObj, sensorRegs, numRegs);
        }

        if (FVID2_SOK == status)
        {
            pObj->sensorConfig.dataformat = FVID2_DF_BAYER_GRBG;
            if (FVID2_STD_720P_60 == cfgPrms->standard)
            {
                pObj->sensorConfig.standard = FVID2_STD_720P_60;
                pObj->outputHeight          = 720U;
            }
            else
            {
                pObj->sensorConfig.standard = FVID2_STD_WXGA_30;
                pObj->outputHeight          = 800U;
            }
            pObj->sensorConfig.fps          = FVID2_FPS_30;
            pObj->sensorConfig.videoIfWidth = FVID2_VIFW_12BIT;
            pObj->sensorConfig.bpp          = FVID2_BPP_BITS12;

            /* By Default WDR Mode is disabled */
            pObj->isWdrOutputEnabled = FALSE;

            /* For Linear mode, coard integration time is height - 52U */
            pObj->maxCoarseIntgTime = pObj->outputHeight - 52U;
        }
    }
    else
    {
        /* Nothing to be done here */
    }
    return (status);
}

