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
 *  \file bspdrv_imx224I2c.c
 *
 *  \brief IMX224 sensor driver implementation file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <imx224/src/bspdrv_imx224Priv.h>
#include <imx224/src/bspdrv_imx224Dcc.h>
#include <imx224/src/bspdrv_imx224_gain_tbl.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define BSP_IMX224_GAIN_TBL_SIZE            (150U)
#define BSP_IMX224_GAIN_TBL_STEP_SIZE       (100U)
#define BSP_IMX224_GAIN_TBL_STARTOFFSET     (10U)

#define BSP_IMX224_EXPOSURE_RATIO            (64U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static const UInt8  gBspDrvImx224DccCfg[BSP_IMX224_DCC_CFG_NUM_ELEM] =
    BSP_DRV_IMX224DCC_CFG;

static const UInt16 gBspVidSensorIMX224GainsTable[BSP_IMX224_GAIN_TBL_SIZE] =
    BSP_DRV_IMX224_GAIN_TBL;

extern Bsp_VidSensorConfigRegs gBsp_IMX224_MIPI_DOL_1312x2164_4lanes[
    BSP_IMX224_NUM_REGS];
extern Bsp_VidSensorConfigRegs gBsp_IMX224_MIPI_720p_4lanes[
    BSP_IMX224_NUM_REGS];

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/*
 * Get IMX224 chip ID and Manufacturer ID
 */
Int32 Bsp_imx224GetChipId(Bsp_imx224HandleObj            *pObj,
                           const Bsp_VidSensorChipIdParams *pPrm,
                           Bsp_VidSensorChipIdStatus       *pStatus)
{
    return 0;
}

/**
 *  \brief Writes to device registers.
 */
Int32 Bsp_imx224RegWrite(Bsp_imx224HandleObj             *pObj,
                          const Bsp_VidSensorRegRdWrParams *pPrm)
{
    Int32 status = FVID2_SOK;
    UInt8 regVal;
    UInt32 numRegs;
    UInt16 regValTmp;
    Bsp_VidSensorCreateParams *pCreatePrms;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if((NULL == pPrm) ||
       (NULL == pPrm->regAddr) ||
       (NULL == pPrm->regValue16) ||
       (0U == pPrm->numRegs) ||
       (pPrm->deviceNum >= pObj->createPrms.numDevicesAtPort))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid arguments\n");
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        pCreatePrms = &pObj->createPrms;

        for(numRegs = 0; ((numRegs < pPrm->numRegs) &&
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
Int32 Bsp_imx224RegRead(const Bsp_imx224HandleObj       *pObj,
                         const Bsp_VidSensorRegRdWrParams *pPrm)
{
    UInt32 numRegs;
    UInt16 regValue, regValueTemp;
    Int32  status = FVID2_SOK;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if((NULL == pPrm) ||
       (NULL == pPrm->regAddr) ||
       (NULL == pPrm->regValue16) ||
       (0U == pPrm->numRegs) ||
       (pPrm->deviceNum >= pObj->createPrms.numDevicesAtPort))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid arguments\n");
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        for(numRegs = 0; ((numRegs < pPrm->numRegs) &&
                          (FVID2_SOK == status)); numRegs++)
        {
            status = Bsp_deviceRead16(
                pObj->createPrms.deviceI2cInstId,
                pObj->createPrms.deviceI2cAddr[0],
                &pPrm->regAddr[numRegs],
                (UInt16 *) &regValue,
                (UInt32)1U);

            regValueTemp = (regValue & (UInt16)0x00FF);
            pPrm->regValue16[numRegs] = regValueTemp;
        }
    }

    return (status);
}

Int32 Bsp_imx224SensorStartStop(const Bsp_imx224HandleObj *pObj,
                                 UInt32                      bStartSensor)
{
    Int32  status = FVID2_SOK;
    UInt8  nRegVal8;
    UInt16 nRegValue16;
    UInt16 nRegAddr16;
    UInt32 nI2cInstId;
    UInt32 nDeviceAddr;
    UInt32 numRegs;

    if(pObj == NULL)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\n");
        status = FVID2_EBADARGS;
    }

    if(status == FVID2_SOK)
    {
        nI2cInstId  = pObj->createPrms.deviceI2cInstId;
        nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];
        nRegAddr16  = BSP_IMX224_SOFTWARE_RESET_REG;
        numRegs     = 1U;

        status = Bsp_deviceRead16(
            nI2cInstId,
            nDeviceAddr,
            &nRegAddr16,
            &nRegValue16,
            numRegs);
        if((UInt32) TRUE == bStartSensor)
        {
            nRegValue16 = nRegValue16 | (UInt16) 0x1U;
        }
        else
        {
            nRegValue16 = nRegValue16 & (UInt16) 0xFEU;
        }
        numRegs = 1U;

        nRegVal8 = (UInt8)nRegValue16;

        status = Bsp_deviceWrite_Custom_16A8D(
            nI2cInstId,
            nDeviceAddr,
            &nRegAddr16,
            &nRegVal8,
            numRegs);
        if(status != FVID2_SOK)
        {
            status = FVID2_ETIMEOUT;
        }
    }
    return status;
}

/* IMX224 Sensor Software reset  */
Int32 Bsp_imx224SoftwareReset(const Bsp_imx224HandleObj *pObj)
{
    Int32 status = FVID2_SOK;

    if(pObj == NULL)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\n");
        status = FVID2_EBADARGS;
    }

    return status;
}

/* IMX224 Sensor Config  */
Int32 Bsp_imx224SensorConfig(
    Bsp_imx224HandleObj          *pObj,
    const Bsp_VidSensorConfigRegs *sensorConfig)
{
    UInt8           nValue;
    UInt16          nAddr;
    Int32           status = FVID2_SOK;
    UInt32          nI2cInstId, cnt;
    UInt32          nDeviceAddr   = 0U;
    volatile UInt32 wait;
    UInt32          nValueTemp;
    UInt32          numReg;

    if(pObj == NULL)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\n");
        status = FVID2_EBADARGS;
    }
    else
    {
        nI2cInstId  = pObj->createPrms.deviceI2cInstId;
        nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];
    }

    if(FVID2_SOK == status)
    {
        numReg = BSP_IMX224_NUM_REGS;

        for (cnt = 0U; cnt < numReg; cnt ++)
        {
            /* For IMX224 sensor the address is 16-bit long */
            nAddr = sensorConfig[cnt].regAddr & (UInt16)0xFFFFU;

            /* For IMX224 sensor the value is 8-bit long */
            nValueTemp =
                ((UInt32)sensorConfig[cnt].regValue & (UInt32) 0xFFU);
            nValue = (UInt8)nValueTemp;

            if (sensorConfig[cnt].regMask != 0U)
            {
                wait = (UInt32)10000U * (UInt32)nValue;
                while(wait--)
                {
                    ;
                }
            }

                status = Bsp_deviceWrite_Custom_16A8D(
                    nI2cInstId,
                    nDeviceAddr,
                    &(nAddr),
                    (const UInt8 *) &(nValue),
                    (UInt32)0x1U);

                if(FVID2_SOK != status)
                {
                    GT_4trace(
                        BspDeviceTrace, GT_ERR, ": Could not write to "
                        "Reg at addr 0x%x, Value 0x%x, Slave Addr 0x%x, I2c 0x%x\n"
                        , nAddr, nValue,
                        nDeviceAddr,
                        nI2cInstId);
                }

            if (sensorConfig[cnt].regMask != 0U)
                {
                wait = (UInt32)10000U * (UInt32)nValue;
                while(wait--)
                {
                    ;
                }
            }

            #if 0
            {
                UInt16 val;
                Bsp_deviceRead16(
                    nI2cInstId,
                    nDeviceAddr,
                    &(nAddr),
                    &(val),
                    (UInt32)0x1U);

                GT_3trace(
                    BspDeviceTrace, GT_ERR, ": Value for register "
                    "%d Write Value 0x%x Read Value 0x%x\n"
                    , nAddr, nValue, val & 0xFF);
            }
            #endif
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

    if(pObj != NULL)
    {
        pObj->lineIntgTimeInMs = 15.0f;
        pObj->pixIntgTimeInMs = 0.0234f;
        pObj->maxCoarseIntgTime = BSP_IMX224_MAX_INTG_LINES;
    }


    return (status);
}

Int32 Bsp_imx224SensorGetExposureRatio(
    const Bsp_imx224HandleObj    *pObj,
    Bsp_VidSensorExpRatioParams   *expRatioPrms)
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

    if(FVID2_SOK == status)
    {
        /* TODO: Read exposure ratio from register */
        expRatioPrms->exposureRatio = BSP_IMX224_EXPOSURE_RATIO;
    }

    return (status);
}

Int32 Bsp_imx224SensorSetWdrParams(
    Bsp_imx224HandleObj          *pObj,
    const Bsp_VidSensorWdrParams        *wdrPrms)
{
    Int32 status = FVID2_SOK;

    if ((pObj == NULL) || (NULL == wdrPrms))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\n");
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        if (TRUE == wdrPrms->wdrEnable)
        {
            status = Bsp_imx224SensorConfig(
                pObj,
                gBsp_IMX224_MIPI_DOL_1312x2164_4lanes);
        }
        else /* For Non-WDR mode, enable Long channel output */
        {
            status = Bsp_imx224SensorConfig(
                pObj,
                gBsp_IMX224_MIPI_720p_4lanes);
        }
    }

    if (FVID2_SOK == status)
    {
        pObj->isWdrOutputEnabled = wdrPrms->wdrEnable;
    }

    return (status);
}

Int32 Bsp_imx224SetExpParams(const Bsp_imx224HandleObj           *pObj,
                             const Bsp_VidSensorExposureParams   *expPrms)
{
    Int32 status = FVID2_SOK;
    UInt16 nAddr;
    UInt8 nValue_low;
    UInt8 nValue_high;
    UInt16 shs_short;
    UInt16 shs_long;
    UInt32 nI2cInstId;
    UInt32 nDeviceAddr;
    Float lineIntgTime;
    UInt32 lineIntgTimeU32;
    UInt32 frameSetCount;
    UInt16 shs_longTmp;
    UInt16 shs_shortTmp;

    GT_assert(BspDeviceTrace, (NULL != pObj));

    if (NULL == expPrms)
    {
        status = FVID2_EBADARGS;
    }

    if ((FVID2_SOK == status) && (0 != expPrms->exposureTime))
    {
        nI2cInstId  = pObj->createPrms.deviceI2cInstId;
        nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];

        lineIntgTime = expPrms->exposureTime / pObj->lineIntgTimeInMs;

        if (lineIntgTime > pObj->maxCoarseIntgTime)
        {
            lineIntgTime = pObj->maxCoarseIntgTime;
        }

        lineIntgTimeU32 = (UInt32)lineIntgTime;
        if(pObj->isWdrOutputEnabled)
        {
                frameSetCount = 2U * BSP_IMX224_VMAX;
        }
        else
        {
                frameSetCount = BSP_IMX224_VMAX;
        }

        shs_long = (UInt16)(frameSetCount - lineIntgTimeU32);

        nAddr = (UInt16)BSP_IMX224_AE_CONTROL_LONG_REG_ADDR_LOW;

        shs_longTmp = (shs_long & 0xFFU);
        nValue_low = (UInt8)shs_longTmp;

        status = Bsp_deviceWrite_Custom_16A8D(nI2cInstId,
                                   nDeviceAddr,
                                   &nAddr,
                                   &nValue_low,
                                   1U);

        nAddr = (UInt16)BSP_IMX224_AE_CONTROL_LONG_REG_ADDR_HIGH;
        nValue_high = (UInt8)(shs_long >> 8U);
        status = Bsp_deviceWrite_Custom_16A8D(nI2cInstId,
                                   nDeviceAddr,
                                   &nAddr,
                                   &nValue_high,
                                   1U);

        shs_short = (UInt16)(BSP_IMX224_RHS -
                        (lineIntgTimeU32/BSP_IMX224_EXPOSURE_RATIO));

        nAddr = (UInt16)BSP_IMX224_AE_CONTROL_SHORT_REG_ADDR_LOW;

        shs_shortTmp = (shs_short & 0xFFU);
        nValue_low = (UInt8)shs_shortTmp;

        status = Bsp_deviceWrite_Custom_16A8D(nI2cInstId,
                                   nDeviceAddr,
                                   &nAddr,
                                   &nValue_low,
                                   1U);

        nAddr = (UInt16)BSP_IMX224_AE_CONTROL_SHORT_REG_ADDR_HIGH;
        nValue_high = (UInt8)(shs_short >> 8U);
        status = Bsp_deviceWrite_Custom_16A8D(nI2cInstId,
                                   nDeviceAddr,
                                   &nAddr,
                                   &nValue_high,
                                   1U);


    }

    return (status);
}

Int32 Bsp_imx224SetGainParams(const Bsp_imx224HandleObj     *pObj,
                              const Bsp_VidSensorGainParams       *gainPrms)
{
    Int32 status = FVID2_SOK;
    UInt32 cnt;
    UInt16 nAddr;
    UInt8 nValue;
    UInt32 nI2cInstId;
    UInt32 nDeviceAddr, gain;

    GT_assert(BspDeviceTrace, (NULL != pObj));

    if (NULL == gainPrms)
    {
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        nI2cInstId  = pObj->createPrms.deviceI2cInstId;
        nDeviceAddr = pObj->createPrms.deviceI2cAddr[0];

        gain = gainPrms->analogGain;
        cnt = (gain/BSP_IMX224_GAIN_TBL_STEP_SIZE)-BSP_IMX224_GAIN_TBL_STARTOFFSET;

        if( cnt >= BSP_IMX224_GAIN_TBL_SIZE)
        {
            cnt = BSP_IMX224_GAIN_TBL_SIZE-1U;
        }

        nAddr = BSP_IMX224_ANALOG_GAIN_CONTROL_REG_ADDR_LOW;
        nValue = gBspVidSensorIMX224GainsTable[cnt];

        status = Bsp_deviceWrite_Custom_16A8D(nI2cInstId,
                                   nDeviceAddr,
                                   &nAddr,
                                   &nValue,
                                   1u);

    }

    return (status);
}

Int32 Bsp_imx224SensorGetDccParams(
    const Bsp_imx224HandleObj *pObj,
    Bsp_VidSensorDccParams *dccPrms)
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
        dccPrms->dccCameraId = BSP_IMX224_DCC_CAMERA_ID;
        dccPrms->dccCfgSize  = sizeof (gBspDrvImx224DccCfg);
        dccPrms->pDccCfg     = (Ptr) gBspDrvImx224DccCfg;
    }

    return (status);
}


