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
 *  \file bspdrv_mt9v022I2c.c
 *
 *  \brief MT9V022 video encoder FVID2 driver implementation file.
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

static Int32 Bsp_mt9v022PowerDownReset(Bsp_Mt9v022HandleObj *pObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* Reset MT9V022 logic */
Int32 Bsp_mt9v022Reset(Bsp_Mt9v022HandleObj *pObj)
{
    Int32 retVal;

    /* PowerDown Reset */
    retVal = Bsp_mt9v022PowerDownReset(pObj);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(BspDeviceTrace, GT_ERR,
                  "Power Down Reset of MT9V022 failed\n");
    }

    return (retVal);
}

/*
 * Get MT9V022 chip ID and Manufacturer ID
 */
Int32 Bsp_mt9v022GetChipId(Bsp_Mt9v022HandleObj      *pObj,
                           const Bsp_VidSensorChipIdParams *pPrm,
                           Bsp_VidSensorChipIdStatus *pStatus)
{
    Int32  retVal = FVID2_SOK;
    UInt32 numRegs;
    UInt16 regAddr[8];
    UInt16 regValue[8];
    Bsp_VidSensorCreateParams *createPrms;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if ((NULL == pStatus) ||
        (NULL == pPrm) ||
        (pPrm->deviceNum >= pObj->createPrms.numDevicesAtPort))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        BspUtils_memset(pStatus, 0, sizeof (*pStatus));
        createPrms = &pObj->createPrms;

        numRegs           = 0;
        regAddr[numRegs]  = BSP_MT9V022_CHIP_ID_REG;
        regValue[numRegs] = 0;
        numRegs++;

        retVal = Bsp_deviceRead16_Custom(
            createPrms->deviceI2cInstId,
            createPrms->deviceI2cAddr[0],
            regAddr,
            regValue,
            numRegs);
    }

    if (FVID2_SOK == retVal)
    {
        pStatus->chipId          = 0;
        pStatus->chipRevision    = regValue[0];
        pStatus->firmwareVersion = 0;
    }

    return (retVal);
}

/* start/enable output */
Int32 Bsp_mt9v022Start(Bsp_Mt9v022HandleObj *pObj)
{
    Int32 retVal = FVID2_SOK;

    return (retVal);
}

/* stop/disable output */
Int32 Bsp_mt9v022Stop(Bsp_Mt9v022HandleObj *pObj)
{
    Int32 retVal = FVID2_SOK;

    return (retVal);
}

/**
 *  \brief Writes to device registers.
 */
Int32 Bsp_mt9v022RegWrite(Bsp_Mt9v022HandleObj       *pObj,
                          const Bsp_VidSensorRegRdWrParams *pPrm)
{
    Int32 retVal = FVID2_SOK;
    Bsp_VidSensorCreateParams *createPrms;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if ((NULL == pPrm) ||
        (NULL == pPrm->regAddr) ||
        (NULL == pPrm->regValue16) ||
        (0U == pPrm->numRegs) ||
        (pPrm->deviceNum >= pObj->createPrms.numDevicesAtPort))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid arguments\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        createPrms = &pObj->createPrms;
        retVal     = Bsp_deviceWrite16_Custom(
            createPrms->deviceI2cInstId,
            createPrms->deviceI2cAddr[0],
            pPrm->regAddr,
            pPrm->regValue16,
            pPrm->numRegs);
    }

    return (retVal);
}

/**
 *  \brief Read from device registers.
 */
Int32 Bsp_mt9v022RegRead(Bsp_Mt9v022HandleObj       *pObj,
                         Bsp_VidSensorRegRdWrParams *pPrm)
{
    Int32 retVal = FVID2_SOK;
    Bsp_VidSensorCreateParams *createPrms;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if ((NULL == pPrm) ||
        (NULL == pPrm->regAddr) ||
        (NULL == pPrm->regValue16) ||
        (0U == pPrm->numRegs) ||
        (pPrm->deviceNum >= pObj->createPrms.numDevicesAtPort))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid arguments\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        createPrms = &pObj->createPrms;
        retVal     = Bsp_deviceRead16_Custom(
            createPrms->deviceI2cInstId,
            createPrms->deviceI2cAddr[0],
            pPrm->regAddr,
            pPrm->regValue16,
            pPrm->numRegs);
    }

    return (retVal);
}

/* Reset MT9V022 logic */
static Int32 Bsp_mt9v022PowerDownReset(Bsp_Mt9v022HandleObj *pObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32  numRegs;
    UInt16 regAddr[8];
    UInt16 regValue[8];
    Bsp_VidSensorCreateParams *createPrms;

    createPrms        = &pObj->createPrms;
    numRegs           = 0;
    regAddr[numRegs]  = BSP_MT9V022_RESET_REG;
    regValue[numRegs] = 0x0000;
    numRegs++;

    retVal = Bsp_deviceWrite16_Custom(
        createPrms->deviceI2cInstId,
        createPrms->deviceI2cAddr[0],
        regAddr,
        regValue,
        numRegs);

    return (retVal);
}

