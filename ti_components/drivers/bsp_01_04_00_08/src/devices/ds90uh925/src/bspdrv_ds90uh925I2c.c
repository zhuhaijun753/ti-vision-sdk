/******************************************************************************
 *                                                                            *
 * Copyright (c) 2015 Texas Instruments Incorporated - http://www.ti.com/     *
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
 *  \file bspdrv_ds90uh925I2c.c
 *
 *  \brief DS90UH925 24-bit FPD-III serializer FVID2 driver implementation file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ds90uh925/src/bspdrv_ds90uh925Priv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

#define DS90UH925_NUM_WR_BYTE           (2U)

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 Bsp_ds90uh925Reset(Bsp_Ds90uh925HandleObj *pObj);
static Int32 Bsp_ds90uh925ProgramDefault(Bsp_Ds90uh925HandleObj *pObj);

static Int32 Bsp_ds90uh925I2cRead8(const Bsp_Ds90uh925HandleObj *pObj,
                                   UInt32                        i2cInstId,
                                   UInt32                        i2cDevAddr,
                                   const UInt8                  *regAddr,
                                   UInt8                        *regVal,
                                   UInt32                        numRegs);
static Int32 Bsp_ds90uh925I2cWrite8(const Bsp_Ds90uh925HandleObj *pObj,
                                    UInt32                        i2cInstId,
                                    UInt32                        i2cDevAddr,
                                    const UInt8                  *regAddr,
                                    const UInt8                  *regVal,
                                    UInt32                        numRegs);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Default power-up sequence */
static UInt8       gDs90uh925DefaultConfig[][DS90UH925_NUM_WR_BYTE] =
{
    /* Register Offset, Value */
    {BSP_DS90UH925_REG_CONFIG0,         0xAAU},
    {BSP_DS90UH925_REG_CONFIG1,         0x8AU},
    {BSP_DS90UH925_REG_DATA_PATH_CTRL,  0x8AU}
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief Gets DS90UH925 Chip ID and revision ID.
 */
Int32 Bsp_ds90uh925GetChipId(Bsp_Ds90uh925HandleObj       *pObj,
                             const Bsp_VidEncChipIdParams *pPrm,
                             Bsp_VidEncChipIdStatus       *pStatus)
{
    Int32  retVal = FVID2_SOK;
    Bsp_VidEncCreateParams *pCreatePrms;
    UInt8  regAddr[4];
    UInt8  regVal[4];
    UInt32 numRegs;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if((NULL == pStatus) ||
       (NULL == pPrm))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        BspUtils_memset(pStatus, 0, sizeof(*pStatus));

        pCreatePrms = &pObj->createPrms;

        numRegs = 0;

        regAddr[numRegs] = BSP_DS90UH925_REG_REV_ID_GPIO0_CONFIG;
        regVal[numRegs]  = 0;
        numRegs++;

        retVal = Bsp_ds90uh925I2cRead8(
            pObj,
            pCreatePrms->deviceI2cInstId,
            pCreatePrms->deviceI2cAddr,
            regAddr,
            regVal,
            numRegs);
    }

    if(FVID2_SOK == retVal)
    {
        pStatus->chipId          = 0x00U;
        pStatus->chipRevision    = ((UInt32) regVal[0] >> 4U);
        pStatus->firmwareVersion = 0x00U;
    }

    return (retVal);
}

/**
 *  \brief Sets the required video standard and output formats depending
 *  on requested parameters.
 */
Int32 Bsp_ds90uh925SetVideoMode(Bsp_Ds90uh925HandleObj       *pObj,
                                const Bsp_VidEncConfigParams *pPrm)
{
    Int32 retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if(NULL == pPrm)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        /* Reset device */
        retVal = Bsp_ds90uh925Reset(pObj);
        if(FVID2_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Device reset failed\n");
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Program recommended settings */
        retVal = Bsp_ds90uh925ProgramDefault(pObj);
        if(FVID2_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Default settings failed\n");
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Copy parameters to allocate driver handle */
        BspUtils_memcpy(&pObj->modePrms, pPrm, sizeof(pObj->modePrms));
    }

    return (retVal);
}

/**
 *  \brief Starts DS90UH925.
 */
Int32 Bsp_ds90uh925Start(const Bsp_Ds90uh925HandleObj *pObj)
{
    Int32 retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    return (retVal);
}

/**
 *  \brief Stops DS90UH925.
 */
Int32 Bsp_ds90uh925Stop(const Bsp_Ds90uh925HandleObj *pObj)
{
    Int32 retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    return (retVal);
}

/**
 *  \brief Resets the DS90UH925.
 *
 *  This API does the manual reset of DS90UH925
 */
static Int32 Bsp_ds90uh925Reset(Bsp_Ds90uh925HandleObj *pObj)
{
    Int32  retVal = FVID2_SOK;
    Bsp_VidEncCreateParams *pCreatePrms;
    UInt8  regAddr[4];
    UInt8  regVal[4];
    UInt32 numRegs;
    UInt32 devAddr;
    UInt32 delay;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    pCreatePrms = &pObj->createPrms;
    devAddr     = pCreatePrms->deviceI2cAddr;

    numRegs          = 0;
    regAddr[numRegs] = BSP_DS90UH925_REG_RESET;
    regVal[numRegs]  = 0x02U;   /* Self clearing */
    numRegs++;

    retVal += Bsp_ds90uh925I2cWrite8(
        pObj,
        pCreatePrms->deviceI2cInstId,
        devAddr,
        &regAddr[0],
        &regVal[0],
        numRegs);

    /* wait for reset to be effective */
    delay = 50U;
    BspOsal_sleep(delay);

    return (retVal);
}

static Int32 Bsp_ds90uh925ProgramDefault(Bsp_Ds90uh925HandleObj *pObj)
{
    Int32  retVal = FVID2_SOK;
    Bsp_VidEncCreateParams *pCreatePrms;
    UInt8  regAddr[4];
    UInt8  regVal[4];
    UInt32 devAddr, cnt;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    pCreatePrms = &pObj->createPrms;
    for(cnt = 0;
        cnt < (sizeof(gDs90uh925DefaultConfig) / DS90UH925_NUM_WR_BYTE);
        cnt++)
    {
        devAddr = pCreatePrms->deviceI2cAddr;
        regAddr[0] = gDs90uh925DefaultConfig[cnt][0];
        regVal[0]  = gDs90uh925DefaultConfig[cnt][1];
        retVal    += Bsp_ds90uh925I2cWrite8(
            pObj,
            pCreatePrms->deviceI2cInstId,
            devAddr,
            &regAddr[0],
            &regVal[0],
            (UInt32)1);
        if(retVal != FVID2_SOK)
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      "I2C write to IO Expander failed!!\n");
        }
    }

    return (retVal);
}

/**
 *  \brief I2C read wrapper function.
 */
static Int32 Bsp_ds90uh925I2cRead8(const Bsp_Ds90uh925HandleObj *pObj,
                                 UInt32                      i2cInstId,
                                 UInt32                      i2cDevAddr,
                                 const UInt8                *regAddr,
                                 UInt8                      *regVal,
                                 UInt32                      numRegs)
{
    Int32 retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    GT_assert(BspDeviceTrace, (NULL != regAddr));
    GT_assert(BspDeviceTrace, (NULL != regVal));

    retVal = Bsp_deviceRead8(i2cInstId, i2cDevAddr, regAddr, regVal, numRegs);
    if(FVID2_SOK != retVal)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "I2C read failed\n");
    }

    return (retVal);
}

/**
 *  \brief I2C write wrapper function.
 */
static Int32 Bsp_ds90uh925I2cWrite8(const Bsp_Ds90uh925HandleObj *pObj,
                                  UInt32                      i2cInstId,
                                  UInt32                      i2cDevAddr,
                                  const UInt8                *regAddr,
                                  const UInt8                *regVal,
                                  UInt32                      numRegs)
{
    Int32 retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    GT_assert(BspDeviceTrace, (NULL != regAddr));
    GT_assert(BspDeviceTrace, (NULL != regVal));

    retVal = Bsp_deviceWrite8(i2cInstId, i2cDevAddr, regAddr, regVal, numRegs);
    if(FVID2_SOK != retVal)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "I2C write failed\n");
    }

    return (retVal);
}
