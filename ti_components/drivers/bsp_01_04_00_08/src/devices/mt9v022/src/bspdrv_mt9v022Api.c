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
 *  \file bspdrv_mt9v022Api.c
 *
 *  \brief MT9V022 video sensor FVID2 driver API file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <mt9v022/src/bspdrv_mt9v022Priv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

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
static Fdrv_Handle Bsp_mt9v022Create(UInt32                   drvId,
                                     UInt32                   instId,
                                     Ptr                      createPrms,
                                     Ptr                      createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbPrms);
static Int32 Bsp_mt9v022Delete(Fdrv_Handle handle, Ptr deleteArgs);
static Int32 Bsp_mt9v022Control(Fdrv_Handle handle,
                                UInt32      cmd,
                                Ptr         cmdArgs,
                                Ptr         cmdStatusArgs);
#ifdef __cplusplus
}
#endif
static Int32 Bsp_mt9v022SensorConfig(const Bsp_Mt9v022HandleObj    *pObj,
                                     const Bsp_VidSensorConfigRegs *sensorCfg,
                                     UInt32                         numSensorCfg);

static Bsp_Mt9v022HandleObj *Bsp_mt9v022AllocObj(void);
static Int32 Bsp_mt9v022FreeObj(Bsp_Mt9v022HandleObj *pObj);

static Int32 Bsp_mt9v022LockObj(Bsp_Mt9v022HandleObj *pObj);
static Int32 Bsp_mt9v022UnlockObj(Bsp_Mt9v022HandleObj *pObj);
static Int32 Bsp_mt9v022Lock(void);
static Int32 Bsp_mt9v022Unlock(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief MT9V022 driver function pointer. */
static const Fvid2_DrvOps gBspMt9v022DrvOps =
{
    FVID2_VID_SENSOR_MT9V022_DRV,       /* Driver ID */
    &Bsp_mt9v022Create,                 /* Create */
    &Bsp_mt9v022Delete,                 /* Delete */
    &Bsp_mt9v022Control,                /* Control */
    NULL,                               /* Queue */
    NULL,                               /* Dequeue */
    NULL,                               /* ProcessFrames */
    NULL,                               /* GetProcessedFrames */
    NULL,                               /* ProcessRequest */
    NULL                                /* GetProcessedRequest */
};

/**
 *  \brief Global object storing all information related to all MT9V022 driver
 *  handles.
 */
static Bsp_Mt9v022Obj     gBspMt9v022Obj;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief System init for MT9V022 driver
 *
 *  This API
 *      - create semaphore locks needed
 *      - registers driver to FVID2 sub-system
 *      - gets called as part of Bsp_deviceInit()
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_mt9v022Init(void)
{
    Int32 retVal = FVID2_SOK;
    Int32 initValue;

    /* Memset global object */
    BspUtils_memset(&gBspMt9v022Obj, 0, sizeof (gBspMt9v022Obj));

    /* Create global MT9V022 lock */
    initValue = 1;
    gBspMt9v022Obj.lock = BspOsal_semCreate(initValue, (Bool)TRUE);
    if (NULL == gBspMt9v022Obj.lock)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Global semaphore create failed\n");
        retVal = FVID2_EALLOC;
    }

    if (FVID2_SOK == retVal)
    {
        /* Register MT9V022 driver with FVID2 sub-system */
        retVal = Fvid2_registerDriver(&gBspMt9v022DrvOps);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      "Registering to FVID2 driver manager failed\n");
            /* Error - free acquired resources */
            BspOsal_semDelete(&gBspMt9v022Obj.lock);
        }
    }

    return (retVal);
}

/**
 *  \brief System de-init for MT9V022 driver
 *
 *  This API
 *      - de-registers driver from FVID2 sub-system
 *      - delete's allocated semaphore locks
 *      - gets called as part of Bsp_deviceDeInit()
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_mt9v022DeInit(void)
{
    /* Unregister FVID2 driver */
    Fvid2_unRegisterDriver(&gBspMt9v022DrvOps);

    /* Delete semaphore's. */
    BspOsal_semDelete(&gBspMt9v022Obj.lock);

    return (FVID2_SOK);
}

/**
 *  \brief MT9V022 create API that gets called when Fvid2_create is called.
 *
 *  This API does not configure the MT9V022 is any way.
 *
 *  This API
 *      - validates parameters
 *      - allocates driver handle
 *      - stores create arguments in its internal data structure.
 *
 *  Later the create arguments will be used when doing I2C communcation with
 *  MT9V022.
 *
 *  \param drvId            [IN] Driver ID, must be
 *                          FVID2_VID_SENSOR_MT9V022_DRV.
 *  \param instId           [IN] Must be 0.
 *  \param createPrms       [IN] Create arguments - pointer to valid
 *                          Bsp_VidSensorCreateParams. This parameter should
 *                          be non-NULL.
 *  \param createStatusArgs [OUT] MT9V022 driver return parameter -
 *                          pointer to Bsp_VidSensorCreateStatus.
 *                          This parameter could be NULL and the driver fills
 *                          the retVal information only if this is not NULL.
 *  \param fdmCbPrms        [IN] Not used. Set to NULL
 *
 *  \return                 Returns NULL in case of any error. Otherwise
 *                          returns a valid handle.
 */
static Fdrv_Handle Bsp_mt9v022Create(UInt32                   drvId,
                                     UInt32                   instId,
                                     Ptr                      createPrms,
                                     Ptr                      createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbPrms)
{
    Int32 retVal = FVID2_SOK;
    Bsp_Mt9v022HandleObj      *pObj = NULL;
    Bsp_VidSensorCreateParams *sensorCreatePrms;
    Bsp_VidSensorCreateStatus *sensorCreateStatus;

    /* Check parameters */
    if ((NULL == createPrms) ||
        (drvId != FVID2_VID_SENSOR_MT9V022_DRV) ||
        (instId != 0U))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        sensorCreatePrms = (Bsp_VidSensorCreateParams *) createPrms;
        if (sensorCreatePrms->deviceI2cInstId >= BSP_DEVICE_I2C_INST_ID_MAX)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Invalid I2C instance ID\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
        if (sensorCreatePrms->numDevicesAtPort >=
            BSP_VID_SENSOR_DEV_PER_PORT_MAX)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Invalid device per port\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Allocate driver handle */
        pObj = Bsp_mt9v022AllocObj();
        if (NULL == pObj)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Alloc object failed\n");
            retVal = FVID2_EALLOC;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Copy parameters to allocate driver handle */
        BspUtils_memcpy(
            &pObj->createPrms,
            sensorCreatePrms,
            sizeof (*sensorCreatePrms));
    }

    if (FVID2_SOK == retVal)
    {
        /* Configure the sensor with user configuration  - default is no
         * configuration. */
        if (sensorCreatePrms->sensorCfg != NULL)
        {
            retVal = Bsp_mt9v022SensorConfig(
                pObj,
                sensorCreatePrms->sensorCfg,
                sensorCreatePrms->numSensorCfg);
        }
    }

    if ((FVID2_SOK != retVal) && (pObj != NULL))
    {
        Bsp_mt9v022FreeObj(pObj);
        pObj = NULL;
    }

    /* Fill the retVal if possible */
    if (NULL != createStatusArgs)
    {
        sensorCreateStatus =
            (Bsp_VidSensorCreateStatus *) createStatusArgs;
        sensorCreateStatus->retVal = retVal;
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
static Int32 Bsp_mt9v022Delete(Fdrv_Handle handle, Ptr deleteArgs)
{
    Int32 retVal = FVID2_SOK;
    Bsp_Mt9v022HandleObj *pObj;

    /* Check parameters */
    if (NULL == handle)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        /* Free driver handle object */
        pObj   = (Bsp_Mt9v022HandleObj *) handle;
        retVal = Bsp_mt9v022FreeObj(pObj);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Free object failed\n");
        }
    }

    return (retVal);
}

/**
 *  \brief Control API that gets called when Fvid2_control is called.
 *
 *  This API does handle level semaphore locking
 *
 *  \param handle           [IN] MT9V022 driver handle returned by
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
static Int32 Bsp_mt9v022Control(Fdrv_Handle handle,
                                UInt32      cmd,
                                Ptr         cmdArgs,
                                Ptr         cmdStatusArgs)
{
    Int32 retVal = FVID2_SOK;
    Bsp_Mt9v022HandleObj *pObj = NULL;

    /* Check parameters */
    if (NULL == handle)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        pObj = (Bsp_Mt9v022HandleObj *) handle;

        /* lock handle */
        Bsp_mt9v022LockObj(pObj);

        switch (cmd)
        {
            case IOCTL_BSP_VID_SENSOR_RESET:
                retVal = Bsp_mt9v022Reset(pObj);
                break;

            case IOCTL_BSP_VID_SENSOR_GET_CHIP_ID:
                retVal = Bsp_mt9v022GetChipId(
                    pObj,
                    (Bsp_VidSensorChipIdParams *) cmdArgs,
                    (Bsp_VidSensorChipIdStatus *) cmdStatusArgs);
                break;

            case FVID2_START:
                retVal = Bsp_mt9v022Start(pObj);
                break;

            case FVID2_STOP:
                retVal = Bsp_mt9v022Stop(pObj);
                break;

            case IOCTL_BSP_VID_SENSOR_REG_WRITE:
                retVal = Bsp_mt9v022RegWrite(
                    pObj,
                    (Bsp_VidSensorRegRdWrParams *) cmdArgs);
                break;

            case IOCTL_BSP_VID_SENSOR_REG_READ:
                retVal = Bsp_mt9v022RegRead(
                    pObj,
                    (Bsp_VidSensorRegRdWrParams *) cmdArgs);
                break;

            default:
                GT_0trace(BspDeviceTrace, GT_ERR, "Unsupported command\n");
                retVal = FVID2_EUNSUPPORTED_CMD;
                break;
        }

        /* Unlock handle */
        Bsp_mt9v022UnlockObj(pObj);
    }

    return (retVal);
}

/* MT9V022 Sensor Config  */
static Int32 Bsp_mt9v022SensorConfig(const Bsp_Mt9v022HandleObj    *pObj,
                                     const Bsp_VidSensorConfigRegs *sensorCfg,
                                     UInt32                         numSensorCfg)
{
    Int32  retVal = FVID2_SOK;
    UInt8  addr;
    UInt8  regValue[5];
    UInt32 index;
    UInt16 value, mask;
    UInt16 regAddr;
    UInt32 numRegs;

    for (index = 0U; index < numSensorCfg; index++)
    {
        /* For MT sensor the address is 8-bit long */
        regAddr = (UInt16)(sensorCfg[index].regAddr & 0x00FFU);
        addr = (UInt8)regAddr;

        /* For MT sensor the value is 16-bit long */
        value = sensorCfg[index].regValue & (UInt16)0xFFFFU;
        /* For MT sensor the mask is 16-bit long */
        mask = sensorCfg[index].regMask & (UInt16)0xFFFFU;

        if (mask != 0)
        {
            value = (value & 0xFFU) & mask;
        }
        else
        {
            value = (value & 0xFFU);
        }

        /* Address */
        regValue[0] = addr;

        /* Data */
        /* MSB of the data value */
        regValue[1] = (value & 0xFFFFU) >> 8U;
        /* LSB of the data value */
        regValue[2] = (value & 0x00FFU);
        numRegs = 3U;

        retVal = Bsp_deviceRawWrite8(
            pObj->createPrms.deviceI2cInstId,
            pObj->createPrms.deviceI2cAddr[0U],
            regValue,
            numRegs);
        if (retVal != FVID2_SOK)
        {
            break;
        }
    }

    return (retVal);
}

/**
 *  \brief Allocates driver object.
 *
 *  Searches in list of driver handles and allocate's a 'NOT IN USE' handle
 *  Also create's handle level semaphore lock.
 *
 *  Returns NULL in case handle could not be allocated.
 */
static Bsp_Mt9v022HandleObj *Bsp_mt9v022AllocObj(void)
{
    UInt32 handleId;
    Bsp_Mt9v022HandleObj *pObj = NULL;
    Int32  initValue;

    /* Take global lock to avoid race condition */
    Bsp_mt9v022Lock();

    /* Find a unallocated object in pool */
    for (handleId = 0U; handleId < BSP_DEVICE_MAX_HANDLES; handleId++)
    {
        if (BSP_MT9V022_OBJ_STATE_UNUSED ==
            gBspMt9v022Obj.handlePool[handleId].state)
        {
            /* Free object found */
            pObj = &gBspMt9v022Obj.handlePool[handleId];

            /* Init state and handle ID */
            BspUtils_memset(pObj, 0, sizeof (*pObj));
            pObj->state    = BSP_MT9V022_OBJ_STATE_IDLE;
            pObj->handleId = handleId;

            /* Create driver object specific semaphore lock */
            initValue = 1;
            pObj->lock = BspOsal_semCreate(initValue, (Bool)TRUE);
            if (NULL == pObj->lock)
            {
                GT_0trace(BspDeviceTrace, GT_ERR,
                          "Handle semaphore create failed\n");
                /* Error - release object */
                pObj->state = BSP_MT9V022_OBJ_STATE_UNUSED;
                pObj        = NULL;
            }
            break;
        }
    }

    /* Release global lock */
    Bsp_mt9v022Unlock();

    return (pObj);
}

/**
 *  \brief De-Allocate driver object.
 *
 *  Marks handle as 'NOT IN USE'.
 *  Also delete's handle level semaphore lock.
 */
static Int32 Bsp_mt9v022FreeObj(Bsp_Mt9v022HandleObj *pObj)
{
    Int32 retVal = FVID2_EFAIL;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    /* Take global lock to avoid race condition */
    Bsp_mt9v022Lock();

    if (pObj->state != BSP_MT9V022_OBJ_STATE_UNUSED)
    {
        /* Mark state as unused */
        pObj->state = BSP_MT9V022_OBJ_STATE_UNUSED;

        /* Delete object locking semaphore */
        BspOsal_semDelete(&pObj->lock);

        retVal = FVID2_SOK;
    }

    /* Release global lock */
    Bsp_mt9v022Unlock();

    return (retVal);
}

/**
 *  \brief Handle level lock.
 */
static Int32 Bsp_mt9v022LockObj(Bsp_Mt9v022HandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    BspOsal_semWait(pObj->lock, BSP_OSAL_WAIT_FOREVER);

    return (FVID2_SOK);
}

/**
 *  \brief Handle level unlock
 */
static Int32 Bsp_mt9v022UnlockObj(Bsp_Mt9v022HandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    BspOsal_semPost(pObj->lock);

    return (FVID2_SOK);
}

/**
 *  \brief Global driver level lock.
 */
static Int32 Bsp_mt9v022Lock(void)
{
    BspOsal_semWait(gBspMt9v022Obj.lock, BSP_OSAL_WAIT_FOREVER);

    return (FVID2_SOK);
}

/**
 *  \brief Global driver level unlock.
 */
static Int32 Bsp_mt9v022Unlock(void)
{
    BspOsal_semPost(gBspMt9v022Obj.lock);

    return (FVID2_SOK);
}

