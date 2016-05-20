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
 *  \file bspdrv_imx224Api.c
 *
 *  \brief IMX224 video sensor FVID2 driver API file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <imx224/src/bspdrv_imx224Priv.h>

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

extern Bsp_VidSensorConfigRegs gBsp_IMX224_MIPI_DOL_1312x2164_4lanes[
    BSP_IMX224_NUM_REGS];
extern Bsp_VidSensorConfigRegs gBsp_IMX224_MIPI_720p_4lanes[
    BSP_IMX224_NUM_REGS];

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
static Int32 Bsp_imx224Control(Fdrv_Handle handle,
                                UInt32      cmd,
                                Ptr         cmdArgs,
                                Ptr         cmdStatusArgs);

static Fdrv_Handle Bsp_imx224Create(UInt32                   nDrvId,
                                     UInt32                   instId,
                                     Ptr                      createPrms,
                                     Ptr                      createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbPrms);

static Int32 Bsp_imx224Delete(Fdrv_Handle handle, Ptr deleteArgs);
#ifdef __cplusplus
}
#endif
static Int32 Bsp_imx224Unlock(void);
static Int32 Bsp_imx224Lock(void);
static Int32 Bsp_imx224LockObj(Bsp_imx224HandleObj *pObj);
static Int32 Bsp_imx224UnlockObj(Bsp_imx224HandleObj *pObj);
static Int32 Bsp_imx224FreeObj(Bsp_imx224HandleObj *pObj);
static Int32 Bsp_imx224SensorSetConfig(
    Bsp_imx224HandleObj            *pObj,
    const Bsp_VidSensorConfigParams *cfgPrms);
static Bsp_imx224HandleObj *Bsp_imx224AllocObj(void);

/** \brief IMX224 driver function pointer. */
static const Fvid2_DrvOps gBspimx224Csi2DrvOps =
{
    FVID2_VID_SENSOR_SONY_IMX224_CSI2_DRV,  /* Driver ID */
    &Bsp_imx224Create,                      /* Create */
    &Bsp_imx224Delete,                      /* Delete */
    &Bsp_imx224Control,                     /* Control */
    NULL,                                   /* Queue */
    NULL,                                   /* Dequeue */
    NULL,                                   /* ProcessFrames */
    NULL,                                   /* GetProcessedFrames */
    NULL,                                   /* ProcessRequest */
    NULL                                    /* GetProcessedRequest */
};

/**< \brief Global object containing IMX224 sensor driver features */
static const Bsp_VidSensorFeatures gBspIMX224SensorFeatures =
{
    BSP_VID_SENSOR_IMX224,          /* SensorId */
    0x0,                            /* Chip Id, read from register */
    0x0,                            /* Revision Id, read from register */
    0x0,                            /* firmware version, read from register */
    FVID2_DF_BAYER_RGGB,            /* Bayer format */
    1280U,                          /* Active Width */
    960U,                           /* Active Height */
    FALSE,                          /* isEmbededDataSupported */
    TRUE,                           /* isManualExposureSupported */
    FALSE,                          /* isEepromDataSupported */
    FALSE,                          /* isSoftStandbySupported */
    FALSE,                          /* isFlipSupported */
    TRUE,                           /* isManualAnalogGainSupported */
    TRUE,                           /* isWdrModeSupported */
    TRUE,                           /* isSetCfgSupported */
    TRUE                            /* isDCCSupported */
};


/**
 *  \brief Global object storing all information related to all IMX224 driver
 *  handles.
 */
static Bsp_imx224Obj     gBspimx224Obj;

/**
 *  \brief System init for IMX224  driver
 *
 *  This API
 *      - create semaphore locks needed
 *      - registers driver to FVID2 sub-system
 *      - gets called as part of Bsp_deviceInit()
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_imx224Init(void)
{
    Int32 status = FVID2_SOK;
    Int32 initValue;

    /* Memset global object */
    BspUtils_memset(&gBspimx224Obj, 0, sizeof(gBspimx224Obj));

    /* Create global IMX224 lock */
    initValue           = 1;
    gBspimx224Obj.lock = BspOsal_semCreate(initValue, (Bool) TRUE);
    if(NULL == gBspimx224Obj.lock)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Global semaphore create failed\n");
        status = FVID2_EALLOC;
    }

    if(FVID2_SOK == status)
    {
        /* Register IMX224 driver with FVID2 sub-system */
        status = Fvid2_registerDriver(&gBspimx224Csi2DrvOps);
        if(FVID2_SOK != status)
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      "Registering to FVID2 driver manager failed\n");
            /* Error - free acquired resources */
            BspOsal_semDelete(&gBspimx224Obj.lock);
        }
    }

    return (status);
}

/**
 *  \brief System de-init for IMX224 driver
 *
 *  This API
 *      - de-registers driver from FVID2 sub-system
 *      - delete's allocated semaphore locks
 *      - gets called as part of Bsp_deviceDeInit()
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_imx224DeInit(void)
{
    /* Unregister FVID2 driver */
    Fvid2_unRegisterDriver(&gBspimx224Csi2DrvOps);

    /* Delete semaphore's. */
    BspOsal_semDelete(&gBspimx224Obj.lock);

    return (FVID2_SOK);
}

/**
 *  \brief IMX224 create API that gets called when Fvid2_create is called.
 *
 *  This API does not configure the IMX224 is any way.
 *
 *  This API
 *      - validates parameters
 *      - allocates driver handle
 *      - stores create arguments in its internal data structure.
 *
 *  Later the create arguments will be used when doing I2C communcation with
 *  IMX224.
 *
 *  \param drvId            [IN] Driver ID, must be
 *                          either FVID2_VID_SENSOR_IMX224_DRV
 *  \param instId           [IN] Must be 0.
 *  \param createPrms       [IN] Create arguments - pointer to valid
 *                          Bsp_VidSensorCreateParams. This parameter should
 *                          be non-NULL.
 *  \param createStatusArgs [OUT] IMX224 driver return parameter -
 *                          pointer to Bsp_VidSensorCreateStatus.
 *                          This parameter could be NULL and the driver fills
 *                          the status information only if this is not NULL.
 *  \param fdmCbPrms        [IN] Not used. Set to NULL
 *
 *  \return                 Returns NULL in case of any error. Otherwise
 *                          returns a valid handle.
 */
static Fdrv_Handle Bsp_imx224Create(UInt32                   nDrvId,
                                     UInt32                   instId,
                                     Ptr                      createPrms,
                                     Ptr                      createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbPrms)
{
    Int32 status = FVID2_SOK;
    Bsp_imx224HandleObj      *pObj = NULL;
    Bsp_VidSensorCreateParams *sensorCreatePrms;
    Bsp_VidSensorCreateStatus *sensorCreateStatus;

    /* Check parameters */
    if((NULL == createPrms) ||
       (nDrvId != FVID2_VID_SENSOR_SONY_IMX224_CSI2_DRV))
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
        pObj = Bsp_imx224AllocObj();
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
        Bsp_imx224FreeObj(pObj);
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
static Int32 Bsp_imx224Delete(Fdrv_Handle handle, Ptr deleteArgs)
{
    Int32 status = FVID2_SOK;
    Bsp_imx224HandleObj *pObj;

    /* Check parameters */
    if(NULL == handle)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        /* Free driver handle object */
        pObj   = (Bsp_imx224HandleObj *) handle;
        status = Bsp_imx224FreeObj(pObj);
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
 *  \param handle           [IN] IMX224 driver handle returned by
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
static Int32 Bsp_imx224Control(Fdrv_Handle handle,
                                UInt32      cmd,
                                Ptr         cmdArgs,
                                Ptr         cmdStatusArgs)
{
    Int32 status = FVID2_SOK;
    Bsp_imx224HandleObj *pObj = NULL;
    /* Check parameters */
    if(NULL == handle)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        pObj = (Bsp_imx224HandleObj *) handle;

        /* lock handle */
        Bsp_imx224LockObj(pObj);

        switch(cmd)
        {
            case IOCTL_BSP_VID_SENSOR_RESET:
                status = Bsp_imx224SoftwareReset(pObj);
                break;

            case IOCTL_BSP_VID_SENSOR_GET_CHIP_ID:
                status = Bsp_imx224GetChipId(
                    pObj,
                    (Bsp_VidSensorChipIdParams *) cmdArgs,
                    (Bsp_VidSensorChipIdStatus *) cmdStatusArgs);
                break;

            case FVID2_START:
                /* status = Bsp_imx224SensorStartStop(pObj, TRUE); */
                break;

            case FVID2_STOP:
                /* status = Bsp_imx224SensorStartStop(pObj, FALSE); */
                break;

            case IOCTL_BSP_VID_SENSOR_REG_WRITE:
                status = Bsp_imx224RegWrite(
                    pObj,
                    (Bsp_VidSensorRegRdWrParams *) cmdArgs);
                break;

            case IOCTL_BSP_VID_SENSOR_REG_READ:
                status = Bsp_imx224RegRead(
                    pObj,
                    (Bsp_VidSensorRegRdWrParams *) cmdArgs);
                break;

            case IOCTL_BSP_VID_SENSOR_GET_FEATURES:
                BspUtils_memcpy((Bsp_VidSensorFeatures *) cmdArgs,
                                &gBspIMX224SensorFeatures,
                                sizeof(Bsp_VidSensorFeatures));
                break;

            case IOCTL_BSP_VID_SENSOR_SET_CONFIG:
                status = Bsp_imx224SensorSetConfig(
                    pObj,
                    (Bsp_VidSensorConfigParams *) cmdArgs);
                break;

            case IOCTL_BSP_VID_SENSOR_GET_CONFIG:
                BspUtils_memcpy((Bsp_VidSensorConfigParams *) cmdArgs,
                                &pObj->sensorConfig,
                                sizeof(Bsp_VidSensorConfigParams));
                break;

            case IOCTL_BSP_VID_SENSOR_SET_EXP_PARAMS:
                if (NULL != cmdArgs)
                {
                    status = Bsp_imx224SetExpParams(
                        pObj,
                        (Bsp_VidSensorExposureParams *)cmdArgs);
                }
                else
                {
                    status = FVID2_EBADARGS;
                }
                break;

            case IOCTL_BSP_VID_SENSOR_SET_GAIN_PARAMS:
                if (NULL != cmdArgs)
                {
                    status = Bsp_imx224SetGainParams(
                        pObj,
                        (Bsp_VidSensorGainParams *)cmdArgs);
                }
                else
                {
                    status = FVID2_EBADARGS;
                }
                break;

            case IOCTL_BSP_VID_SENSOR_GET_EXP_RATIO_PARAMS:
                status = Bsp_imx224SensorGetExposureRatio(
                            pObj,
                            (Bsp_VidSensorExpRatioParams*)cmdArgs);
                break;

            case IOCTL_BSP_VID_SENSOR_SET_WDR_PARAMS:
                status = Bsp_imx224SensorSetWdrParams(
                            pObj,
                            (Bsp_VidSensorWdrParams*)cmdArgs);
                break;
            case IOCTL_BSP_VID_SENSOR_GET_DCC_PARAMS:
                status = Bsp_imx224SensorGetDccParams(
                    pObj,
                    (Bsp_VidSensorDccParams *) cmdArgs);
                break;
            default:
                GT_0trace(BspDeviceTrace, GT_ERR, "Unsupported command\n");
                status = FVID2_EUNSUPPORTED_CMD;
                break;
        }

        /* Unlock handle */
        Bsp_imx224UnlockObj(pObj);
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
static Bsp_imx224HandleObj *Bsp_imx224AllocObj(void)
{
    UInt32 handleId;
    Bsp_imx224HandleObj *pObj = NULL;
    Int32  initValue;

    /* Take global lock to avoid race condition */
    Bsp_imx224Lock();

    /* Find a unallocated object in pool */
    for(handleId = 0U; handleId < BSP_DEVICE_MAX_HANDLES; handleId++)
    {
        if(BSP_IMX224_OBJ_STATE_UNUSED ==
           gBspimx224Obj.handlePool[handleId].state)
        {
            /* Free object found */
            pObj = &gBspimx224Obj.handlePool[handleId];

            /* Init state and handle ID */
            BspUtils_memset(pObj, 0, sizeof(*pObj));
            pObj->state    = BSP_IMX224_OBJ_STATE_IDLE;
            pObj->handleId = handleId;

            /* Create driver object specific semaphore lock */
            initValue  = 1;
            pObj->lock = BspOsal_semCreate(initValue, (Bool) TRUE);
            if(NULL == pObj->lock)
            {
                GT_0trace(BspDeviceTrace, GT_ERR,
                          "Handle semaphore create failed\n");
                /* Error - release object */
                pObj->state = BSP_IMX224_OBJ_STATE_UNUSED;
                pObj        = NULL;
            }
            break;
        }
    }

    /* Release global lock */
    Bsp_imx224Unlock();

    return (pObj);
}

/**
 *  \brief De-Allocate driver object.
 *
 *  Marks handle as 'NOT IN USE'.
 *  Also delete's handle level semaphore lock.
 */
static Int32 Bsp_imx224FreeObj(Bsp_imx224HandleObj *pObj)
{
    Int32 status = FVID2_EFAIL;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    /* Take global lock to avoid race condition */
    Bsp_imx224Lock();

    if(pObj->state != BSP_IMX224_OBJ_STATE_UNUSED)
    {
        /* Mark state as unused */
        pObj->state = BSP_IMX224_OBJ_STATE_UNUSED;

        /* Delete object locking semaphore */
        BspOsal_semDelete(&pObj->lock);

        status = FVID2_SOK;
    }

    /* Release global lock */
    Bsp_imx224Unlock();

    return (status);
}

/**
 *  \brief Handle level lock.
 */
static Int32 Bsp_imx224LockObj(Bsp_imx224HandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    BspOsal_semWait(pObj->lock, BSP_OSAL_WAIT_FOREVER);

    return (FVID2_SOK);
}

/**
 *  \brief Handle level unlock
 */
static Int32 Bsp_imx224UnlockObj(Bsp_imx224HandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    BspOsal_semPost(pObj->lock);

    return (FVID2_SOK);
}

/**
 *  \brief Global driver level lock.
 */
static Int32 Bsp_imx224Lock(void)
{
    BspOsal_semWait(gBspimx224Obj.lock, BSP_OSAL_WAIT_FOREVER);

    return (FVID2_SOK);
}

/**
 *  \brief Global driver level unlock.
 */
static Int32 Bsp_imx224Unlock(void)
{
    BspOsal_semPost(gBspimx224Obj.lock);

    return (FVID2_SOK);
}

/**
 *  \brief Set the Configuration
 */
static Int32 Bsp_imx224SensorSetConfig(
    Bsp_imx224HandleObj            *pObj,
    const Bsp_VidSensorConfigParams *cfgPrms)
{
    Int32 status = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    GT_assert(BspDeviceTrace, (NULL != cfgPrms));

    /*if(FVID2_VIFW_4LANES != cfgPrms->videoIfWidth)
    {
        status = FVID2_EBADARGS;
    }
    else*/
    {
        pObj->sensorConfig.videoIfWidth = cfgPrms->videoIfWidth;
    }

    if(FVID2_SOK == status)
    {
        status = Bsp_imx224SensorConfig(
            pObj,
            gBsp_IMX224_MIPI_720p_4lanes);

        pObj->sensorConfig.dataformat   = FVID2_DF_BAYER_RGGB;
        pObj->sensorConfig.standard     = FVID2_STD_720P_60;
        pObj->sensorConfig.fps          = FVID2_FPS_30;

        pObj->sensorConfig.videoIfWidth = FVID2_VIFW_4LANES;
        pObj->sensorConfig.bpp          = FVID2_BPP_BITS12;
    }

    return (status);
}

