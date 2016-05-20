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
 *  \file bspdrv_ar0132I2c.c
 *
 *  \brief AR0132 sensor driver implementation file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ar0132/src/bspdrv_ar0132Priv.h>
#include <ar0132/src/bspdrv_Ar0132Dcc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern Bsp_VidSensorConfigRegs gBsp_AR0132SensorsDefault[BSP_AR0132_NUM_REGS];
static const UInt8 gBspDrvAr0132DccCfg[BSP_AR0132_DCC_CFG_NUM_ELEM] = BSP_DRV_AR0132DCC_CFG;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/*
 * Get AR0132 chip ID and Manufacturer ID
 */
Int32 Bsp_ar0132GetChipId(Bsp_ar0132HandleObj             *pObj,
                          const Bsp_VidSensorChipIdParams *pPrm,
                          Bsp_VidSensorChipIdStatus       *pStatus)
{
    Int32  status = FVID2_SOK;
    Bsp_VidSensorCreateParams *pCreateArgs;
    UInt16 regAddr[8];
    UInt16 regValue[8];
    UInt32 numRegs;
    UInt32 idx;

    if ((pStatus == NULL) || (pPrm == NULL))
    {
        status = FVID2_EBADARGS;
    }
    if (status == FVID2_SOK)
    {
        BspUtils_memset(pStatus, 0, sizeof (*pStatus));

        pCreateArgs = &pObj->createPrms;

        if (pPrm->deviceNum >= pCreateArgs->numDevicesAtPort)
        {
            status = FVID2_EBADARGS;
        }
    }
    if (status == FVID2_SOK)
    {
        numRegs = 0;

        regAddr[numRegs]  = BSP_AR0132_CHIP_ID_UPPER_REG;
        regValue[numRegs] = 0;
        numRegs++;

        regAddr[numRegs]  = BSP_AR0132_CHIP_ID_LOWER_REG;
        regValue[numRegs] = 0;
        numRegs++;

        status = Bsp_deviceRead16(pCreateArgs->deviceI2cInstId,
                                  pCreateArgs->deviceI2cAddr[0],
                                  regAddr,
                                  regValue,
                                  numRegs);

        if (status != FVID2_SOK)
        {
            status = FVID2_ETIMEOUT;
        }
    }
    if (status == FVID2_SOK)
    {
        for (idx = 0; idx < numRegs; idx++)
        {
            regValue[idx] = regValue[idx] & 0x00FFU;
        }
        pStatus->chipId = ((UInt32) regValue[0] << 8) | regValue[1];
    }
    return status;
}

/**
 *  \brief Writes to device registers.
 */
Int32 Bsp_ar0132RegWrite(Bsp_ar0132HandleObj              *pObj,
                         const Bsp_VidSensorRegRdWrParams *pPrm)
{
    Int32 status = FVID2_SOK;
    Bsp_VidSensorCreateParams *pCreatePrms;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if ((NULL == pPrm) ||
        (NULL == pPrm->regAddr) ||
        (NULL == pPrm->regValue16) ||
        (0U == pPrm->numRegs) ||
        (pPrm->deviceNum >= pObj->createPrms.numDevicesAtPort))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid arguments\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        pCreatePrms = &pObj->createPrms;
        status      = Bsp_deviceWrite16(pCreatePrms->deviceI2cInstId,
                                        pCreatePrms->deviceI2cAddr[0],
                                        pPrm->regAddr,
                                        pPrm->regValue16,
                                        pPrm->numRegs);
    }
    return (status);
}

/**
 *  \brief Read from device registers.
 */
Int32 Bsp_ar0132RegRead(Bsp_ar0132HandleObj        *pObj,
                        Bsp_VidSensorRegRdWrParams *pPrm)
{
    Int32 status = FVID2_SOK;
    Bsp_VidSensorCreateParams *pCreatePrms;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if ((NULL == pPrm) ||
        (NULL == pPrm->regAddr) ||
        (NULL == pPrm->regValue16) ||
        (0U == pPrm->numRegs) ||
        (pPrm->deviceNum >= pObj->createPrms.numDevicesAtPort))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid arguments\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        pCreatePrms = &pObj->createPrms;
        status      = Bsp_deviceRead16(pCreatePrms->deviceI2cInstId,
                                       pCreatePrms->deviceI2cAddr[0],
                                       pPrm->regAddr,
                                       pPrm->regValue16,
                                       pPrm->numRegs);
    }
    return (status);
}

Int32 Bsp_ar0132SensorStartStop(const Bsp_ar0132HandleObj *pObj,
                                UInt32                     bStartSensor)
{
    Int32  status = FVID2_SOK;
    UInt16 nRegAddr16, nRegValue16;
    UInt32 nI2cInstId;
    UInt32 nDeviceAddr;
    UInt32 numRegs;

    if (pObj == NULL)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\n");
        status = FVID2_EBADARGS;
    }
    if (status == FVID2_SOK)
    {
        nI2cInstId  = pObj->createPrms.deviceI2cInstId;
        nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];
        nRegAddr16  = BSP_AR0132_SOFTWARE_RESET_REG;
        numRegs     = 1U;

        status = Bsp_deviceRead16(nI2cInstId,
                                  nDeviceAddr,
                                  &nRegAddr16,
                                  &nRegValue16,
                                  numRegs);
        if ((UInt32) TRUE == bStartSensor)
        {
            nRegValue16 = nRegValue16 | (UInt16) 0x4U;
        }
        else
        {
            nRegValue16 = nRegValue16 & (UInt16) 0xFFFBU;
        }
        numRegs = 1U;

        status = Bsp_deviceWrite16(nI2cInstId,
                                   nDeviceAddr,
                                   &nRegAddr16,
                                   &nRegValue16,
                                   numRegs);
        if (status != FVID2_SOK)
        {
            status = FVID2_ETIMEOUT;
        }
    }
    return status;
}

/* AR0132 Sensor Software reset  */
Int32 Bsp_ar0132SoftwareReset(const Bsp_ar0132HandleObj *pObj)
{
    Int32  status = FVID2_SOK;
    UInt32 nI2cInstId;
    UInt32 nDeviceAddr;
    UInt16 nRegAddr16;
    UInt16 nRegValue16;
    UInt32 numRegs, delay;

    if (pObj == NULL)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\n");
        status = FVID2_EBADARGS;
    }

    if (status == FVID2_SOK)
    {
        nI2cInstId  = pObj->createPrms.deviceI2cInstId;
        nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];
        /* Reset Address 0x301A */
        nRegAddr16 = ((BSP_AR0132_SOFTWARE_RESET_REG) & 0xFFFFU);
        /* Reset value 0x10D8 */
        nRegValue16 = BSP_AR0132_SOFTWARE_RESET_REG_VAL;
        numRegs     = 1U;

        status = Bsp_deviceWrite16(nI2cInstId,
                                   nDeviceAddr,
                                   &nRegAddr16,
                                   &nRegValue16,
                                   numRegs);

        if (status == FVID2_SOK)
        {
            nRegAddr16 = BSP_AR0132_SOFTWARE_RESET_REG;
            do
            {
                numRegs = 1U;
                status  = Bsp_deviceRead16(nI2cInstId,
                                           nDeviceAddr,
                                           &nRegAddr16,
                                           &nRegValue16,
                                           numRegs);
                if (status != FVID2_SOK)
                {
                    status = FVID2_ETIMEOUT;
                    break;
                }
                delay = 1U;
                BspOsal_sleep(delay);
            } while (nRegValue16 != 0);
        }
        else
        {
            status = FVID2_ETIMEOUT;
        }
    }
    return status;
}

/* AR0132 Sensor Config  */
Int32 Bsp_ar0132SensorConfig
    (Bsp_ar0132HandleObj    *pObj,
    Bsp_VidSensorConfigRegs *sensorConfig,
    UInt32                   numSensorConfigEntries,
    UInt32                   dataFormat)
{
    Bsp_VidSensorConfigRegs *sensorConfiguration = NULL;
    UInt16 nAddr, nValue;
    UInt32 nIndex, nArraySize;
    Int32  status = FVID2_SOK;
    UInt32 nI2cInstId;
    UInt32 nDeviceAddr;
    UInt32 numRegs;

    /* Check for sensor configuration to be used */
    if (sensorConfig != NULL)
    {
        /* User provided configuration  */
        sensorConfiguration = (Bsp_VidSensorConfigRegs *) sensorConfig;
        nArraySize          = numSensorConfigEntries;
    }
    else
    {
        if (pObj->nDrvId == FVID2_VID_SENSOR_APT_AR0132_DRV)
        {
            /* Use the default configuration if user has passed NULL */
            sensorConfiguration =
                (Bsp_VidSensorConfigRegs *) gBsp_AR0132SensorsDefault;

            nArraySize =
                (sizeof (gBsp_AR0132SensorsDefault) /
                 sizeof (gBsp_AR0132SensorsDefault[0]));
        }
        else
        {
            status = FVID2_EBADARGS;
            GT_0trace(BspDeviceTrace, GT_ERR, "Invalid Driver ID!!\n");
        }
    }

    nI2cInstId  = pObj->createPrms.deviceI2cInstId;
    nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];

    if (FVID2_SOK == status)
    {
        for (nIndex = 0; ((FVID2_SOK == status) && (nIndex < nArraySize));
             nIndex++)
        {
            /* For AR0132 sensor the address is 16-bit long */
            nAddr = sensorConfiguration[nIndex].regAddr & (UInt16)0xFFFFU;

            /* For AR0132 sensor the value is 16-bit long */
            nValue = (sensorConfiguration[nIndex].regValue & (UInt16) 0xFFFFU);

            if (0x30b0U == nAddr)
            {
                if (FVID2_DF_BAYER_GRBG == dataFormat)
                {
                    nValue = nValue & (0xFF7FU);
                }
                if (FVID2_DF_RAW12 == dataFormat)
                {
                    nValue = nValue & (0x0080U);
                }
            }

            if (0x3082U == nAddr)
            {
                if (pObj->isWdrEnabled)
                {
                    nValue = (UInt16)0x28;
                }
                else
                {
                    nValue = (UInt16)0x29;
                }
            }
            if ((sensorConfiguration[nIndex].regMask ==
                    BSP_VID_SENSOR_DLY_REG_MASK) &&
                ((UInt16)BSP_VID_SENSOR_DLY_REG == nAddr))
            {
                BspOsal_sleep(nValue);
            }
            else
            {
                numRegs = 1U;

                status = Bsp_deviceWrite16(nI2cInstId,
                                           nDeviceAddr,
                                           &nAddr,
                                           &nValue,
                                           numRegs);
            }
        }

        /* Hard coding it as of now, need to read it from register,
         * Hard Coding since I2C read is not working properly */
        pObj->lineIntgTimeInMs = 0;
        pObj->pixIntgTimeInMs  = 0;
    }

    return (status);
}

Int32 Bsp_ar0132SensorGetExposureRatio(
    const Bsp_ar0132HandleObj   *pObj,
    Bsp_VidSensorExpRatioParams *expRatioPrms)
{
    Int32 status = FVID2_SOK;

    if ((pObj == NULL) || (NULL == expRatioPrms))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        /* TODO: Read exposure ratio from register */
        expRatioPrms->exposureRatio = BSP_AR0132_DEFAULT_EXP_RATIO;
    }

    return (status);
}

Int32 Bsp_ar0132SensorSetWdrParams(Bsp_ar0132HandleObj   *pObj,
                                   const Bsp_VidSensorWdrParams *wdrPrms)
{
    Int32 status = FVID2_SOK;

    if ((pObj == NULL) || (NULL == wdrPrms))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        pObj->isWdrEnabled = wdrPrms->wdrEnable;
        status = Bsp_ar0132SensorConfig(pObj, NULL, 0, pObj->dataFormat);
    }

    return (status);
}

Int32 Bsp_ar0132SensorGetDccParams(
    const Bsp_ar0132HandleObj *pObj,
    Bsp_VidSensorDccParams    *dccPrms)
{
    Int32 status = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    if (NULL == dccPrms)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        dccPrms->dccCameraId = 132;
        dccPrms->dccCfgSize  = sizeof (gBspDrvAr0132DccCfg);
        dccPrms->pDccCfg     = (Ptr) gBspDrvAr0132DccCfg;
    }

    return (status);
}


