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
 *  \file bspdrv_ov10640I2c.c
 *
 *  \brief OV10640 sensor driver implementation file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ov10640/src/bspdrv_ov10640Priv.h>
#include <ov10640/src/bspdrv_ov10640Dcc.h>
#include <ov10640/src/bspdrv_ov10640Dcc_1pass.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
void debug_sensor_driver(Int32 exp_ratio);

static const char gBspDrvOv10640DccCfg[BSP_OV10640_DCC_CFG_NUM_ELEM] = BSP_DRV_OV10640DCC_CFG;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/*
 * Get OV10640 chip ID and Manufacturer ID
 */
Int32 Bsp_ov10640GetChipId(Bsp_ov10640HandleObj            *pObj,
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

        regAddr[numRegs]  = BSP_OV10640_CHIP_ID_UPPER_REG;
        regValue[numRegs] = 0;
        numRegs++;

        regAddr[numRegs]  = BSP_OV10640_CHIP_ID_LOWER_REG;
        regValue[numRegs] = 0;
        numRegs++;

        regAddr[numRegs]  = BSP_OV10640_CHIP_ID_REV_ID;
        regValue[numRegs] = 0;
        numRegs++;

        status = Bsp_deviceRead16(
            pCreateArgs->deviceI2cInstId,
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
        pStatus->chipRevision = regValue[2U];
    }
    return status;
}

/**
 *  \brief Writes to device registers.
 */
Int32 Bsp_ov10640RegWrite(Bsp_ov10640HandleObj             *pObj,
                          const Bsp_VidSensorRegRdWrParams *pPrm)
{
    Int32 status = FVID2_SOK;
    UInt8 regVal;
    UInt32 numRegs;
    UInt16 regValTmp;
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
        for (numRegs = 0; ((numRegs < pPrm->numRegs) &&
                           (FVID2_SOK == status)); numRegs++)
        {
            regValTmp = pPrm->regValue16[numRegs] & (UInt16)0xFFU;
            regVal = (UInt8)regValTmp;

            status = Bsp_deviceWrite_Custom_16A8D(
                pCreatePrms->deviceI2cInstId,
                pCreatePrms->deviceI2cAddr[0],
                pPrm->regAddr,
                &regVal,
                1U);
        }
    }
    return (status);
}

/**
 *  \brief Read from device registers.
 */
Int32 Bsp_ov10640RegRead(const Bsp_ov10640HandleObj       *pObj,
                         const Bsp_VidSensorRegRdWrParams *pPrm)
{
    UInt32 numRegs;
    UInt16 regValue, regValueTemp;
    Int32  status = FVID2_SOK;

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
        for (numRegs = 0; ((numRegs < pPrm->numRegs) &&
                           (FVID2_SOK == status)); numRegs++)
        {
            status = Bsp_deviceRead16(
                pObj->createPrms.deviceI2cInstId,
                pObj->createPrms.deviceI2cAddr[0],
                &pPrm->regAddr[numRegs],
                (UInt16 *) &regValue,
                (UInt32) 1U);

            regValueTemp = (regValue & (UInt16) 0x00FF);
            pPrm->regValue16[numRegs] = regValueTemp;
        }
    }

    return (status);
}

Int32 Bsp_ov10640SensorStartStop(const Bsp_ov10640HandleObj *pObj,
                                 UInt32                      bStartSensor)
{
    Int32  status = FVID2_SOK;
    UInt8  nRegVal8;
    UInt16 nRegValue16;
    UInt16 nRegAddr16;
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
        nRegAddr16  = BSP_OV10640_SOFTWARE_RESET_REG;
        numRegs     = 1U;

        status = Bsp_deviceRead16(
            nI2cInstId,
            nDeviceAddr,
            &nRegAddr16,
            &nRegValue16,
            numRegs);
        if ((UInt32) TRUE == bStartSensor)
        {
            nRegValue16 = nRegValue16 | (UInt16) 0x1U;
        }
        else
        {
            nRegValue16 = nRegValue16 & (UInt16) 0xFEU;
        }
        numRegs = 1U;

        nRegVal8 = (UInt8) nRegValue16;

        status = Bsp_deviceWrite_Custom_16A8D(
            nI2cInstId,
            nDeviceAddr,
            &nRegAddr16,
            &nRegVal8,
            numRegs);
        if (status != FVID2_SOK)
        {
            status = FVID2_ETIMEOUT;
        }
    }
    return status;
}

/* OV10640 Sensor Software reset  */
Int32 Bsp_ov10640SoftwareReset(const Bsp_ov10640HandleObj *pObj)
{
    Int32 status = FVID2_SOK;

    if (pObj == NULL)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\n");
        status = FVID2_EBADARGS;
    }

    return status;
}

/* OV10640 Sensor Config  */
Int32 Bsp_ov10640SensorConfig(
    Bsp_ov10640HandleObj          *pObj,
    const Bsp_VidSensorConfigRegs *sensorConfig)
{
    UInt8           nValue;
    UInt16          nAddr;
    UInt32          nIndex;
    Int32           status = FVID2_SOK;
    UInt32          nI2cInstId;
    UInt32          nDeviceAddr   = 0U;
    UInt32          loopBreakFlag = 0U;
    volatile UInt32 wait;
    UInt32          nValueTemp;

    if (pObj == NULL)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\n");
        status = FVID2_EBADARGS;
    }
    else
    {
        nI2cInstId  = pObj->createPrms.deviceI2cInstId;
        nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];
    }

    if (FVID2_SOK == status)
    {
        nIndex = 0U;
        while (TRUE)
        {
            /* For OV10640 sensor the address is 16-bit long */
            nAddr = sensorConfig[nIndex].regAddr & (UInt16)0xFFFFU;

            /* For OV10640 sensor the value is 8-bit long */
            nValueTemp =
                ((UInt32) sensorConfig[nIndex].regValue & (UInt32) 0xFFU);
            nValue = (UInt8) nValueTemp;

            /* Set the output format to DPI in 0x3119 register */
            if ((FVID2_VID_SENSOR_OV10640_CSI2_DRV != pObj->nDrvId) &&
                ((UInt16) 0x3119 == nAddr))
            {
                nValueTemp = (UInt32) nValue & ((UInt32) ~((UInt32) 0x30));
                nValue     = (UInt8) nValueTemp;
            }

            /* Number of lanes in CSI2 format */
            if (nAddr == 0x3444U)
            {
                nValueTemp = ((UInt32) nValue & ((UInt32) ~((UInt32) 0x70)));
                nValue     = (UInt8) nValueTemp;
                if (FVID2_VIFW_4LANES == pObj->sensorConfig.videoIfWidth)
                {
                    nValueTemp = (UInt32) nValue | (UInt32) 0x40;
                    nValue     = (UInt8) nValueTemp;
                }
                else if (FVID2_VIFW_3LANES == pObj->sensorConfig.videoIfWidth)
                {
                    nValueTemp = (UInt32) nValue | (UInt32) 0x30;
                    nValue     = (UInt8) nValueTemp;
                }
                else if (FVID2_VIFW_2LANES == pObj->sensorConfig.videoIfWidth)
                {
                    nValueTemp = (UInt32) nValue | (UInt32) 0x20;
                    nValue     = (UInt8) nValueTemp;
                }
                else
                {
                    nValueTemp = (UInt32) nValue | (UInt32) 0x10;
                    nValue     = (UInt8) nValueTemp;
                }
            }

            if (0x3090U == nAddr)
            {
                nValue &= ~(BSP_OV10640_MIRROR_MODE_ENABLE_MASK |
                            BSP_OV10640_FLIP_MODE_ENABLE_MASK);
                if (TRUE == pObj->flipPrms.hFlip)
                {
                    nValue |= BSP_OV10640_MIRROR_MODE_ENABLE_MASK;
                }
                if (TRUE == pObj->flipPrms.vFlip)
                {
                    nValue |= BSP_OV10640_FLIP_MODE_ENABLE_MASK;
                }
            }

            if (0x3291U == nAddr)
            {
                nValue &= ~(BSP_OV10640_MIRROR_OFFSET_ENABLE_MASK |
                            BSP_OV10640_FLIP_OFFSET_ENABLE_MASK);
                if (TRUE == pObj->flipPrms.hFlip)
                {
                    nValue |= BSP_OV10640_MIRROR_OFFSET_ENABLE_MASK;
                }
                if (TRUE == pObj->flipPrms.vFlip)
                {
                    nValue |= BSP_OV10640_FLIP_OFFSET_ENABLE_MASK;
                }
            }

            if (nAddr == 0xFFFFU)
            {
                loopBreakFlag = 1U;
            }
            else if ((sensorConfig[nIndex].regMask ==
                        BSP_VID_SENSOR_DLY_REG_MASK) &&
                ((UInt16)BSP_VID_SENSOR_DLY_REG == nAddr))
            {
                BspOsal_sleep(nValue);
                nIndex ++;
            }
            else
            {
                status = Bsp_deviceWrite_Custom_16A8D(
                    nI2cInstId,
                    nDeviceAddr,
                    &(nAddr),
                    (const UInt8 *) &(nValue),
                    (UInt32) 0x1U);

                if (FVID2_SOK != status)
                {
                    GT_4trace(
                        BspDeviceTrace, GT_ERR, ": Could not write to "
                        "Reg at addr 0x%x, Value 0x%x, Slave Addr 0x%x, I2c 0x%x\n"
                        , nAddr, nValue,
                        nDeviceAddr,
                        nI2cInstId);
                    loopBreakFlag = 1U;
                }
                if (loopBreakFlag != 1U)
                {
                    nIndex++;
                }
            }
            if (loopBreakFlag == 1U)
            {
                break;
            }
        }
    }
    else
    {
        GT_1trace(
            BspDeviceTrace, GT_ERR,
            ": No I2C Ack from sensor OV 10640 At address %d"
            " Aborting this test\n",
            nDeviceAddr);
    }

    if (FVID2_SOK == status)
    {
        /* By Default WDR Merge output is enabled */
        pObj->isWdrOutputEnabled = TRUE;
    }

    return (status);
}

Int32 Bsp_ov10640SensorGetExposureRatio(
    const Bsp_ov10640HandleObj  *pObj,
    Bsp_VidSensorExpRatioParams *expRatioPrms)
{
    Int32 status = FVID2_SOK;

    if ((pObj == NULL) || (NULL == expRatioPrms))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\n");
        status = FVID2_EBADARGS;
    }

    /* Not supported if wdr mode is disabled */
    if ((FVID2_SOK == status) && (FALSE == pObj->isWdrOutputEnabled))
    {
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        /* TODO: Read exposure ratio from register */
        expRatioPrms->exposureRatio = 32;
    }

    return (status);
}

Int32 Bsp_ov10640SensorSetWdrParams(
    Bsp_ov10640HandleObj         *pObj,
    const Bsp_VidSensorWdrParams *wdrPrms)
{
    Int32  status = FVID2_SOK;
    UInt16  regVal;
    UInt16 regAddr;
    Bsp_VidSensorRegRdWrParams rdWrPrms;

    if ((pObj == NULL) || (NULL == wdrPrms))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        regAddr = (UInt16) 0x3119;

        rdWrPrms.regAddr   = &regAddr;
        rdWrPrms.regValue16 = &regVal;
        rdWrPrms.numRegs   = 1U;
        rdWrPrms.deviceNum = 0U;

        status = Bsp_ov10640RegRead(pObj, &rdWrPrms);

        if (FVID2_SOK == status)
        {
            regVal &= ~BSP_OV10640_OUTPUT_DATA_FMT_MASK;
            if (TRUE == wdrPrms->wdrEnable)
            {
                regVal |= BSP_OV10640_OUTPUT_DATA_FMT_12BIT_COMP;
            }
            else /* For Non-WDR mode, enable Long channel output */
            {
                regVal |= BSP_OV10640_OUTPUT_DATA_FMT_LONG_CH;
            }

            status = Bsp_ov10640RegWrite(pObj, &rdWrPrms);
        }
    }

    if (FVID2_SOK == status)
    {
        pObj->isWdrOutputEnabled = wdrPrms->wdrEnable;
    }

    return (status);
}

Int32 Bsp_ov10640SensorGetDccParams(
    const Bsp_ov10640HandleObj *pObj,
    Bsp_VidSensorDccParams     *dccPrms)
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
        dccPrms->dccCameraId = BSP_OV10640_DCC_CAMERA_ID;
        dccPrms->dccCfgSize  = sizeof (gBspDrvOv10640DccCfg);
        dccPrms->pDccCfg     = (Ptr) gBspDrvOv10640DccCfg;
    }

    return (status);
}

