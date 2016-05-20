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
 *  \file bspdrv_ov10640Api.c
 *
 *  \brief OV10640 video sensor FVID2 driver API file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ov10640/src/bspdrv_ov10640Priv.h>
#include <ov10640/src/bspdrv_ov10640Reg.h>

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

static const Bsp_VidSensorConfigRegs gBsp_OV10640_MIPI_720p_4lanes[
    BSP_OV10640_NUM_REGS] = BSP_OV10640_MIPI_720P_4LANES;

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
static Int32 Bsp_ov10640Control(Fdrv_Handle handle,
                                UInt32      cmd,
                                Ptr         cmdArgs,
                                Ptr         cmdStatusArgs);

static Fdrv_Handle Bsp_ov10640Create(UInt32                   nDrvId,
                                     UInt32                   instId,
                                     Ptr                      createPrms,
                                     Ptr                      createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbPrms);

static Int32 Bsp_ov10640Delete(Fdrv_Handle handle, Ptr deleteArgs);
#ifdef __cplusplus
}
#endif
static Int32 Bsp_ov10640Unlock(void);
static Int32 Bsp_ov10640Lock(void);
static Int32 Bsp_ov10640LockObj(Bsp_ov10640HandleObj *pObj);
static Int32 Bsp_ov10640UnlockObj(Bsp_ov10640HandleObj *pObj);
static Int32 Bsp_ov10640FreeObj(Bsp_ov10640HandleObj *pObj);
static Int32 Bsp_ov10640SensorSetConfig(
    Bsp_ov10640HandleObj            *pObj,
    const Bsp_VidSensorConfigParams *cfgPrms);
static Bsp_ov10640HandleObj *Bsp_ov10640AllocObj(void);

/** \brief OV10640 driver function pointer. */
static const Fvid2_DrvOps gBspov10640Csi2DrvOps =
{
    FVID2_VID_SENSOR_OV10640_CSI2_DRV,  /* Driver ID */
    &Bsp_ov10640Create,                 /* Create */
    &Bsp_ov10640Delete,                 /* Delete */
    &Bsp_ov10640Control,                /* Control */
    NULL,                               /* Queue */
    NULL,                               /* Dequeue */
    NULL,                               /* ProcessFrames */
    NULL,                               /* GetProcessedFrames */
    NULL,                               /* ProcessRequest */
    NULL                                /* GetProcessedRequest */
};

/** \brief OV10640 driver function pointer. */
static const Fvid2_DrvOps gBspov10640CpiDrvOps =
{
    FVID2_VID_SENSOR_OV10640_CPI_DRV,   /* Driver ID */
    &Bsp_ov10640Create,                 /* Create */
    &Bsp_ov10640Delete,                 /* Delete */
    &Bsp_ov10640Control,                /* Control */
    NULL,                               /* Queue */
    NULL,                               /* Dequeue */
    NULL,                               /* ProcessFrames */
    NULL,                               /* GetProcessedFrames */
    NULL,                               /* ProcessRequest */
    NULL                                /* GetProcessedRequest */
};

/**< \brief Global object containing OV10640 sensor driver features */
static const Bsp_VidSensorFeatures gBspOV10640SensorFeatures =
{
    BSP_VID_SENSOR_OV10640,         /* SensorId */
    0x0,                            /* Chip Id, read from register */
    0x0,                            /* Revision Id, read from register */
    0x0,                            /* firmware version, read from register */
    FVID2_DF_BAYER_BGGR,            /* Bayer format */
    1280U,                          /* Active Width */
    720U,                           /* Active Height */
    FALSE,                          /* isEmbededDataSupported */
    FALSE,                          /* isManualExposureSupported */
    FALSE,                          /* isEepromDataSupported */
    FALSE,                          /* isSoftStandbySupported */
    TRUE,                           /* isFlipSupported */
    FALSE,                          /* isManualAnalogGainSupported */
    TRUE,                           /* isWdrModeSupported */
    TRUE,                           /* isSetCfgSupported */
    TRUE                            /* isDccCfgSupported */
};


/**
 *  \brief Global object storing all information related to all OV10640 driver
 *  handles.
 */
static Bsp_ov10640Obj     gBspov10640Obj;

/**
 *  \brief System init for OV10640  driver
 *
 *  This API
 *      - create semaphore locks needed
 *      - registers driver to FVID2 sub-system
 *      - gets called as part of Bsp_deviceInit()
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_ov10640Init(void)
{
    Int32 status = FVID2_SOK;
    Int32 initValue;

    /* Memset global object */
    BspUtils_memset(&gBspov10640Obj, 0, sizeof(gBspov10640Obj));

    /* Create global OV10640 lock */
    initValue           = 1;
    gBspov10640Obj.lock = BspOsal_semCreate(initValue, (Bool) TRUE);
    if(NULL == gBspov10640Obj.lock)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Global semaphore create failed\n");
        status = FVID2_EALLOC;
    }

    if(FVID2_SOK == status)
    {
        /* Register OV10640 driver with FVID2 sub-system */
        status = Fvid2_registerDriver(&gBspov10640Csi2DrvOps);
        if(FVID2_SOK != status)
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      "Registering to FVID2 driver manager failed\n");
            /* Error - free acquired resources */
            BspOsal_semDelete(&gBspov10640Obj.lock);
        }
        else
        {
            /* Register OV10640 driver with FVID2 sub-system */
            status = Fvid2_registerDriver(&gBspov10640CpiDrvOps);
            if(FVID2_SOK != status)
            {
                GT_0trace(BspDeviceTrace, GT_ERR,
                          "Registering to FVID2 driver manager failed\n");

                Fvid2_unRegisterDriver(&gBspov10640Csi2DrvOps);
                /* Error - free acquired resources */
                BspOsal_semDelete(&gBspov10640Obj.lock);
            }
        }
    }

    return (status);
}

/**
 *  \brief System de-init for OV10640 driver
 *
 *  This API
 *      - de-registers driver from FVID2 sub-system
 *      - delete's allocated semaphore locks
 *      - gets called as part of Bsp_deviceDeInit()
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_ov10640DeInit(void)
{
    /* Unregister FVID2 driver */
    Fvid2_unRegisterDriver(&gBspov10640CpiDrvOps);

    Fvid2_unRegisterDriver(&gBspov10640Csi2DrvOps);

    /* Delete semaphore's. */
    BspOsal_semDelete(&gBspov10640Obj.lock);

    return (FVID2_SOK);
}

/**
 *  \brief OV10640 create API that gets called when Fvid2_create is called.
 *
 *  This API does not configure the OV10640 is any way.
 *
 *  This API
 *      - validates parameters
 *      - allocates driver handle
 *      - stores create arguments in its internal data structure.
 *
 *  Later the create arguments will be used when doing I2C communcation with
 *  OV10640.
 *
 *  \param drvId            [IN] Driver ID, must be
 *                          either FVID2_VID_SENSOR_OV10640_DRV
 *  \param instId           [IN] Must be 0.
 *  \param createPrms       [IN] Create arguments - pointer to valid
 *                          Bsp_VidSensorCreateParams. This parameter should
 *                          be non-NULL.
 *  \param createStatusArgs [OUT] OV10640 driver return parameter -
 *                          pointer to Bsp_VidSensorCreateStatus.
 *                          This parameter could be NULL and the driver fills
 *                          the status information only if this is not NULL.
 *  \param fdmCbPrms        [IN] Not used. Set to NULL
 *
 *  \return                 Returns NULL in case of any error. Otherwise
 *                          returns a valid handle.
 */
static Fdrv_Handle Bsp_ov10640Create(UInt32                   nDrvId,
                                     UInt32                   instId,
                                     Ptr                      createPrms,
                                     Ptr                      createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbPrms)
{
    Int32 status = FVID2_SOK;
    Bsp_ov10640HandleObj      *pObj = NULL;
    Bsp_VidSensorCreateParams *sensorCreatePrms;
    Bsp_VidSensorCreateStatus *sensorCreateStatus;

    /* Check parameters */
    if((NULL == createPrms) ||
       ((nDrvId != FVID2_VID_SENSOR_OV10640_CSI2_DRV) &&
        (nDrvId != FVID2_VID_SENSOR_OV10640_CPI_DRV)))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\n");
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        sensorCreatePrms = (Bsp_VidSensorCreateParams *) createPrms;
        if(sensorCreatePrms->deviceI2cInstId >= BSP_DEVICE_I2C_INST_ID_MAX)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Invalid I2C instance ID\n");
            status = FVID2_EINVALID_PARAMS;
        }
        if(sensorCreatePrms->numDevicesAtPort >=
           BSP_VID_SENSOR_DEV_PER_PORT_MAX)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Invalid device per port\n");
            status = FVID2_EINVALID_PARAMS;
        }
    }

    if(FVID2_SOK == status)
    {
        /* Allocate driver handle */
        pObj = Bsp_ov10640AllocObj();
        if(NULL == pObj)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Alloc object failed\n");
            status = FVID2_EALLOC;
        }
    }

    if(FVID2_SOK == status)
    {
        /* Store the Driver ID in pObj */
        pObj->nDrvId = nDrvId;
        pObj->instId = instId;

        /* Reset flip parameters */
        pObj->flipPrms.hFlip = FALSE;
        pObj->flipPrms.vFlip = FALSE;
    }

    if(FVID2_SOK == status)
    {
        /* Copy parameters to allocate driver handle */
        BspUtils_memcpy(
            &pObj->createPrms,
            sensorCreatePrms,
            sizeof(*sensorCreatePrms));
    }

    if((FVID2_SOK != status) && (pObj != NULL))
    {
        Bsp_ov10640FreeObj(pObj);
        pObj = NULL;
    }

    /* Fill the status if possible */
    if(NULL != createStatusArgs)
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
static Int32 Bsp_ov10640Delete(Fdrv_Handle handle, Ptr deleteArgs)
{
    Int32 status = FVID2_SOK;
    Bsp_ov10640HandleObj *pObj;

    /* Check parameters */
    if(NULL == handle)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        /* Free driver handle object */
        pObj   = (Bsp_ov10640HandleObj *) handle;
        status = Bsp_ov10640FreeObj(pObj);
        if(FVID2_SOK != status)
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
 *  \param handle           [IN] OV10640 driver handle returned by
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
static Int32 Bsp_ov10640Control(Fdrv_Handle handle,
                                UInt32      cmd,
                                Ptr         cmdArgs,
                                Ptr         cmdStatusArgs)
{
    Int32 status = FVID2_SOK;
    Bsp_ov10640HandleObj *pObj = NULL;
    /* Check parameters */
    if(NULL == handle)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        pObj = (Bsp_ov10640HandleObj *) handle;

        /* lock handle */
        Bsp_ov10640LockObj(pObj);

        switch(cmd)
        {
            case IOCTL_BSP_VID_SENSOR_RESET:
                status = Bsp_ov10640SoftwareReset(pObj);
                break;

            case IOCTL_BSP_VID_SENSOR_GET_CHIP_ID:
                status = Bsp_ov10640GetChipId(
                    pObj,
                    (Bsp_VidSensorChipIdParams *) cmdArgs,
                    (Bsp_VidSensorChipIdStatus *) cmdStatusArgs);
                break;

            case FVID2_START:
                /* status = Bsp_ov10640SensorStartStop(pObj, TRUE); */
                break;

            case FVID2_STOP:
                /* status = Bsp_ov10640SensorStartStop(pObj, FALSE); */
                break;

            case IOCTL_BSP_VID_SENSOR_REG_WRITE:
                status = Bsp_ov10640RegWrite(
                    pObj,
                    (Bsp_VidSensorRegRdWrParams *) cmdArgs);
                break;

            case IOCTL_BSP_VID_SENSOR_REG_READ:
                status = Bsp_ov10640RegRead(
                    pObj,
                    (Bsp_VidSensorRegRdWrParams *) cmdArgs);
                break;

            case IOCTL_BSP_VID_SENSOR_GET_FEATURES:
                BspUtils_memcpy((Bsp_VidSensorFeatures *) cmdArgs,
                                &gBspOV10640SensorFeatures,
                                sizeof(Bsp_VidSensorFeatures));
                break;

            case IOCTL_BSP_VID_SENSOR_SET_CONFIG:
                status = Bsp_ov10640SensorSetConfig(
                    pObj,
                    (Bsp_VidSensorConfigParams *) cmdArgs);
                break;

            case IOCTL_BSP_VID_SENSOR_GET_CONFIG:
                BspUtils_memcpy((Bsp_VidSensorConfigParams *) cmdArgs,
                                &pObj->sensorConfig,
                                sizeof(Bsp_VidSensorConfigParams));
                break;

            case IOCTL_BSP_VID_SENSOR_GET_EXP_RATIO_PARAMS:
                status = Bsp_ov10640SensorGetExposureRatio(
                            pObj,
                            (Bsp_VidSensorExpRatioParams*)cmdArgs);
                break;

            case IOCTL_BSP_VID_SENSOR_SET_WDR_PARAMS:
                status = Bsp_ov10640SensorSetWdrParams(
                            pObj,
                            (Bsp_VidSensorWdrParams*)cmdArgs);
                break;

            case IOCTL_BSP_VID_SENSOR_GET_DCC_PARAMS:
                status = Bsp_ov10640SensorGetDccParams(
                            pObj,
                            (Bsp_VidSensorDccParams*)cmdArgs);
                break;
            case IOCTL_BSP_VID_SENSOR_SET_FLIP_PARAMS:
            {
                Bsp_VidSensorFlipParams *flipPrms;

                flipPrms = (Bsp_VidSensorFlipParams *)cmdArgs;
                if (NULL != cmdArgs)
                {
                    BspUtils_memcpy(&pObj->flipPrms,
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
        Bsp_ov10640UnlockObj(pObj);
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
static Bsp_ov10640HandleObj *Bsp_ov10640AllocObj(void)
{
    UInt32 handleId;
    Bsp_ov10640HandleObj *pObj = NULL;
    Int32  initValue;

    /* Take global lock to avoid race condition */
    Bsp_ov10640Lock();

    /* Find a unallocated object in pool */
    for(handleId = 0U; handleId < BSP_DEVICE_MAX_HANDLES; handleId++)
    {
        if(BSP_OV10640_OBJ_STATE_UNUSED ==
           gBspov10640Obj.handlePool[handleId].state)
        {
            /* Free object found */
            pObj = &gBspov10640Obj.handlePool[handleId];

            /* Init state and handle ID */
            BspUtils_memset(pObj, 0, sizeof(*pObj));
            pObj->state    = BSP_OV10640_OBJ_STATE_IDLE;
            pObj->handleId = handleId;

            /* Create driver object specific semaphore lock */
            initValue  = 1;
            pObj->lock = BspOsal_semCreate(initValue, (Bool) TRUE);
            if(NULL == pObj->lock)
            {
                GT_0trace(BspDeviceTrace, GT_ERR,
                          "Handle semaphore create failed\n");
                /* Error - release object */
                pObj->state = BSP_OV10640_OBJ_STATE_UNUSED;
                pObj        = NULL;
            }
            break;
        }
    }

    /* Release global lock */
    Bsp_ov10640Unlock();

    return (pObj);
}

/**
 *  \brief De-Allocate driver object.
 *
 *  Marks handle as 'NOT IN USE'.
 *  Also delete's handle level semaphore lock.
 */
static Int32 Bsp_ov10640FreeObj(Bsp_ov10640HandleObj *pObj)
{
    Int32 status = FVID2_EFAIL;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    /* Take global lock to avoid race condition */
    Bsp_ov10640Lock();

    if(pObj->state != BSP_OV10640_OBJ_STATE_UNUSED)
    {
        /* Mark state as unused */
        pObj->state = BSP_OV10640_OBJ_STATE_UNUSED;

        /* Delete object locking semaphore */
        BspOsal_semDelete(&pObj->lock);

        status = FVID2_SOK;
    }

    /* Release global lock */
    Bsp_ov10640Unlock();

    return (status);
}

/**
 *  \brief Handle level lock.
 */
static Int32 Bsp_ov10640LockObj(Bsp_ov10640HandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    BspOsal_semWait(pObj->lock, BSP_OSAL_WAIT_FOREVER);

    return (FVID2_SOK);
}

/**
 *  \brief Handle level unlock
 */
static Int32 Bsp_ov10640UnlockObj(Bsp_ov10640HandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    BspOsal_semPost(pObj->lock);

    return (FVID2_SOK);
}

/**
 *  \brief Global driver level lock.
 */
static Int32 Bsp_ov10640Lock(void)
{
    BspOsal_semWait(gBspov10640Obj.lock, BSP_OSAL_WAIT_FOREVER);

    return (FVID2_SOK);
}

/**
 *  \brief Global driver level unlock.
 */
static Int32 Bsp_ov10640Unlock(void)
{
    BspOsal_semPost(gBspov10640Obj.lock);

    return (FVID2_SOK);
}

/**
 *  \brief Set the Configuration
 */
static Int32 Bsp_ov10640SensorSetConfig(
    Bsp_ov10640HandleObj            *pObj,
    const Bsp_VidSensorConfigParams *cfgPrms)
{
    Int32 status = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    GT_assert(BspDeviceTrace, (NULL != cfgPrms));

    if(FVID2_VID_SENSOR_OV10640_CSI2_DRV == pObj->nDrvId)
    {
        if(((FVID2_VIFW_4LANES != cfgPrms->videoIfWidth) &&
            (FVID2_VIFW_3LANES != cfgPrms->videoIfWidth)) &&
           ((FVID2_VIFW_2LANES != cfgPrms->videoIfWidth) &&
            ((FVID2_VIFW_1LANES != cfgPrms->videoIfWidth))))
        {
            status = FVID2_EBADARGS;
        }
        else
        {
            pObj->sensorConfig.videoIfWidth = cfgPrms->videoIfWidth;
        }
    }
    else
    {
        if(FVID2_VIFW_12BIT != cfgPrms->videoIfWidth)
        {
            status = FVID2_EBADARGS;
        }
        else
        {
            pObj->sensorConfig.videoIfWidth = cfgPrms->videoIfWidth;
        }
    }

    if(FVID2_SOK == status)
    {
        status = Bsp_ov10640SensorConfig(
            pObj,
            gBsp_OV10640_MIPI_720p_4lanes);

        pObj->sensorConfig.dataformat   = FVID2_DF_BAYER_BGGR;
        pObj->sensorConfig.standard     = FVID2_STD_720P_60;
        pObj->sensorConfig.fps          = FVID2_FPS_30;

        if(FVID2_VID_SENSOR_OV10640_CSI2_DRV == pObj->nDrvId)
        {
            pObj->sensorConfig.videoIfWidth = FVID2_VIFW_4LANES;
        }
        else
        {
            pObj->sensorConfig.videoIfWidth = FVID2_VIFW_12BIT;
        }
        pObj->sensorConfig.bpp          = FVID2_BPP_BITS12;
    }

    return (status);
}

