/* ======================================================================
 *   Copyright (C) 2014 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

/**
 *  \file stw_device_i2c.c
 *
 *  \brief File containing the STW device I2C functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "stdint.h"
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include <common/stw_config.h>
#include <common/stw_utils.h>
#include "i2clib/lld_hsi2c.h"
#include "boards/stw_board.h"
#include <devices/stw_device.h>
#include <devices/stw_deviceIoexp.h>
#include "stw_deviceI2cPriv.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static deviceI2cObj_t gDevObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
LLD_hsi2cErrorCode_t DEVICEI2cInit(const deviceInitParams_t *pPrm)
{
    LLD_hsi2cErrorCode_t  retVal = LLD_HSI2C_SUCCESS;
    uint32_t instCnt;
    LLD_Hsi2cInstId_t     i2cInstId;
    const boardI2cData_t *i2cData;
    boardI2cInstData_t   *i2cInstData;
    lld_hsi2c_initParam_t initPar;
    hsI2cObjHandle        i2cObjHandle;

    initPar.opMode       = pPrm->i2cOpMode;
    initPar.is10BitAddr  = 0;
    initPar.isMasterMode = 1;

    i2cData = BOARDGetI2cData();
    if ((NULL != i2cData) &&
        (i2cData->numInst <= HSI2C_INST_MAX) &&
        (NULL != i2cData->pInstData))
    {
        DEVICEI2cDebugEnable(FALSE);

        for (instCnt = 0U; instCnt < HSI2C_INST_MAX; instCnt++)
        {
            gDevObj.i2cHndl[instCnt] = NULL;
        }

        for (instCnt = 0U; instCnt < i2cData->numInst; instCnt++)
        {
            i2cInstData        = &i2cData->pInstData[instCnt];
            i2cInstId          = i2cInstData->instId;
            initPar.i2cBusFreq = i2cInstData->busClkKHz;
            initPar.i2cIntNum  = i2cInstData->intNum;

            retVal = lld_i2c_init(&i2cObjHandle, i2cInstId, &initPar);

            gDevObj.i2cHndl[i2cInstId] = lld_i2c_open(i2cInstId, NULL, NULL);
        }
    }
    else
    {
        console_print_string("\nDevice Init: NULL i2cData pointer");
        retVal = LLD_HSI2C_FAIL;
    }
    return (retVal);
}

LLD_hsi2cErrorCode_t DEVICEI2cDeInit(void)
{
    LLD_hsi2cErrorCode_t retVal = LLD_HSI2C_SUCCESS;
    uint32_t instCnt;

    for (instCnt = 0U; instCnt < HSI2C_INST_MAX; instCnt++)
    {
        if (NULL != gDevObj.i2cHndl[instCnt])
        {
            lld_i2c_close(&gDevObj.i2cHndl[instCnt]);
            lld_i2c_deinit((LLD_Hsi2cInstId_t) instCnt);
        }
    }

    return (retVal);
}

LLD_hsi2cErrorCode_t DEVICEI2cProbeAll(uint32_t i2cInstId)
{
    LLD_hsi2cErrorCode_t retVal = LLD_HSI2C_SUCCESS;
    uint32_t slaveAddr, counter;

    /* Stw_i2cCreate should have been called for this instance
     * for its proper initialization. */
    if ((i2cInstId < HSI2C_INST_MAX) && (NULL != gDevObj.i2cHndl[i2cInstId]))
    {
        for (counter = 0U; counter < 128U; counter++)
        {
            slaveAddr = counter;
            /* Probing 0x18 STM LCD Controller address results in I2c hang */
            if ((DEVICE_I2C_INST_ID_0 == i2cInstId) &&
                ((uint32_t) 0x18 == slaveAddr))
            {
                /* Do Nothing */
            }
            else
            {
                if (lld_i2c_probe(gDevObj.i2cHndl[i2cInstId],
                                  (uint8_t) slaveAddr) == 0)
                {
                    console_print_string("\nI2C");
                    console_print_val((int32_t) i2cInstId);
                    console_print_string(" Passed for address ");
                    console_print_valHex(slaveAddr);
                    console_print_string("!!! \r\n");
                }
            }
        }
    }
    else
    {
        console_print_string("\n DEVICEI2cProbeAll: I2c handle is NULL for InstId ");
        console_print_val((int32_t) i2cInstId);
        retVal = LLD_HSI2C_FAIL;
    }
    return (retVal);
}

LLD_hsi2cErrorCode_t DEVICEI2cProbeDevice(uint32_t i2cInstId,
                                          uint8_t  slaveAddr)
{
    LLD_hsi2cErrorCode_t retVal = LLD_HSI2C_SUCCESS;

    if ((i2cInstId < HSI2C_INST_MAX) && (NULL != gDevObj.i2cHndl[i2cInstId]))
    {
        retVal = lld_i2c_probe(gDevObj.i2cHndl[i2cInstId], slaveAddr);
    }
    else
    {
        console_print_string("\n DEVICEI2cProbeDevice: I2c handle is NULL for InstId ");
        console_print_val((int32_t) i2cInstId);
        retVal = LLD_HSI2C_FAIL;
    }

    return (retVal);
}

LLD_hsi2cErrorCode_t DEVICEI2cRead8(uint32_t       i2cInstId,
                                    uint32_t       i2cDevAddr,
                                    const uint8_t *regAddr,
                                    uint8_t       *regValue,
                                    uint32_t       numRegs)
{
    LLD_hsi2cErrorCode_t       retVal = LLD_HSI2C_SUCCESS;
    uint32_t regId;
    uint8_t tempRegAddr;
    lld_hsi2c_datatfr_params_t i2cParams;

    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0)
        || (NULL == gDevObj.i2cHndl[i2cInstId]))
    {
        console_print_string("\nI2C");
        console_print_valHex(i2cInstId);
        console_print_string("DEV");
        console_print_valHex(i2cDevAddr);
        console_print_string("Illegal Params ... ERROR !!!\n");
        retVal = LLD_HSI2C_FAIL;
    }

    if (retVal == LLD_HSI2C_SUCCESS)
    {
        i2cParams.slaveAddr = i2cDevAddr;
        i2cParams.bufLen    = 1;
        i2cParams.timeout   = 0xFFFFFF;

        for (regId = 0; regId < numRegs; regId++)
        {
            tempRegAddr      = regAddr[regId];
            i2cParams.buffer = &tempRegAddr;
            i2cParams.flags
                = (LLD_HSI2C_WRITE | LLD_HSI2C_MASTER | LLD_HSI2C_START);

            retVal = lld_i2c_transfer(gDevObj.i2cHndl[i2cInstId], &i2cParams);

            if (retVal != LLD_HSI2C_SUCCESS)
            {
                console_print_string("\nI2C");
                console_print_valHex(i2cInstId);
                console_print_string("\nDEV");
                console_print_valHex(i2cDevAddr);
                console_print_string("RD");
                console_print_valHex(regAddr[regId]);
                console_print_string(" ERROR !!!");
            }

            if (retVal == LLD_HSI2C_SUCCESS)
            {
                i2cParams.buffer = &regValue[regId];
                i2cParams.flags
                    = (LLD_HSI2C_READ | LLD_HSI2C_MASTER |
                       LLD_HSI2C_START |
                       LLD_HSI2C_STOP |
                       LLD_HSI2C_IGNORE_BUS_BUSY);

                retVal = lld_i2c_transfer(gDevObj.i2cHndl[i2cInstId],
                                          &i2cParams);

                if (retVal != LLD_HSI2C_SUCCESS)
                {
                    console_print_string("\nI2C");
                    console_print_valHex(i2cInstId);
                    console_print_string("\nDEV");
                    console_print_valHex(i2cDevAddr);
                    console_print_string("RD");
                    console_print_valHex(regAddr[regId]);
                    console_print_string(" ERROR !!!");
                }
            }
            if ((gDevObj.i2cDebugEnable == (uint32_t) TRUE) &&
                (retVal == LLD_HSI2C_SUCCESS))
            {
                console_print_string("\nRead8 -");
                console_print_string(" I2C:");
                console_print_valHex(i2cInstId);
                console_print_string(" DEV:");
                console_print_valHex(i2cDevAddr);
                console_print_string(" RD");
                console_print_valHex(regAddr[regId]);
                console_print_string("=");
                console_print_valHex(regValue[regId]);
            }
            if (retVal != LLD_HSI2C_SUCCESS)
            {
                break;
            }
        }
    }

    return (retVal);
}

LLD_hsi2cErrorCode_t DEVICEI2cRawRead8(uint32_t i2cInstId,
                                       uint32_t i2cDevAddr,
                                       uint8_t *regValue,
                                       uint32_t numRegs)
{
    LLD_hsi2cErrorCode_t       retVal = LLD_HSI2C_SUCCESS;
    lld_hsi2c_datatfr_params_t i2cParams;
    uint32_t regId;

    if ((NULL == regValue) || (0U == numRegs) ||
        (NULL == gDevObj.i2cHndl[i2cInstId]))
    {
        console_print_string("\nI2C");
        console_print_valHex(i2cInstId);
        console_print_string("DEV");
        console_print_valHex(i2cDevAddr);
        console_print_string("Illegal Params ... ERROR !!!\n");

        retVal = LLD_HSI2C_FAIL;
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        i2cParams.slaveAddr = i2cDevAddr;
        i2cParams.bufLen    = numRegs;
        i2cParams.timeout   = 0xFFFFFF;
        i2cParams.buffer    = (uint8_t *) regValue;
        i2cParams.flags     = (LLD_HSI2C_DEFAULT_READ);

        retVal = lld_i2c_transfer(gDevObj.i2cHndl[i2cInstId], &i2cParams);
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            console_print_string("\nI2C");
            console_print_valHex(i2cInstId);
            console_print_string("DEV");
            console_print_valHex(i2cDevAddr);
            console_print_string("RD ERROR !!!\n");
        }

        if (gDevObj.i2cDebugEnable == TRUE)
        {
            if (LLD_HSI2C_SUCCESS == retVal)
            {
                for (regId = 0; regId < numRegs; regId++)
                {
                    console_print_string("\n RawRead8 -");
                    console_print_string(" I2C:");
                    console_print_valHex(i2cInstId);
                    console_print_string(" DEV:");
                    console_print_valHex(i2cDevAddr);
                    console_print_string(" RD");
                    console_print_valHex(0x8U + regId);
                    console_print_string("=");
                    console_print_valHex(regValue[regId]);
                }
            }
        }
    }

    return (retVal);
}

LLD_hsi2cErrorCode_t DEVICEI2cWrite8(uint32_t       i2cInstId,
                                     uint32_t       i2cDevAddr,
                                     const uint8_t *regAddr,
                                     const uint8_t *regValue,
                                     uint32_t       numRegs)
{
    LLD_hsi2cErrorCode_t       retVal = LLD_HSI2C_SUCCESS;
    uint32_t regId;
    lld_hsi2c_datatfr_params_t i2cParams;
    uint8_t buffer[2];

    if ((regAddr == NULL) || (regValue == NULL) || (numRegs == 0)
        || (NULL == gDevObj.i2cHndl[i2cInstId]))
    {
        console_print_string("\nI2C");
        console_print_valHex(i2cInstId);
        console_print_string("DEV");
        console_print_valHex(i2cDevAddr);
        console_print_string("Illegal Params ... ERROR !!!\n");
        retVal = LLD_HSI2C_FAIL;
    }

    if (retVal == LLD_HSI2C_SUCCESS)
    {
        i2cParams.slaveAddr = i2cDevAddr;
        i2cParams.buffer    = buffer;
        i2cParams.bufLen    = 2;
        i2cParams.flags     = LLD_HSI2C_DEFAULT_WRITE;
        i2cParams.timeout   = 0xFFFFFF;

        for (regId = 0; regId < numRegs; regId++)
        {
            buffer[0] = regAddr[regId];
            buffer[1] = regValue[regId];

            retVal = lld_i2c_transfer(gDevObj.i2cHndl[i2cInstId],
                                      &i2cParams);
            if (retVal != LLD_HSI2C_SUCCESS)
            {
                console_print_string("\nI2C");
                console_print_valHex(i2cInstId);
                console_print_string("DEV");
                console_print_valHex(i2cDevAddr);
                console_print_string("WR");
                console_print_valHex(regAddr[regId]);
                console_print_string("=");
                console_print_valHex(regValue[regId]);
                console_print_string(" ERROR !!!\n");
                break;
            }

            if (gDevObj.i2cDebugEnable == TRUE)
            {
                console_print_string("\n Write8 -");
                console_print_string(" I2C:");
                console_print_valHex(i2cInstId);
                console_print_string(" DEV:");
                console_print_valHex(i2cDevAddr);
                console_print_string(" WR");
                console_print_valHex(regAddr[regId]);
                console_print_string("=");
                console_print_valHex(regValue[regId]);
            }
        }
    }

    return (retVal);
}

LLD_hsi2cErrorCode_t DEVICEI2cRawWrite8(uint32_t i2cInstId,
                                        uint32_t i2cDevAddr,
                                        uint8_t *regValue,
                                        uint32_t numRegs)
{
    LLD_hsi2cErrorCode_t       retVal = LLD_HSI2C_SUCCESS;
    lld_hsi2c_datatfr_params_t i2cParams;
    uint32_t regId;

    if ((NULL == regValue) || (0U == numRegs) ||
        (NULL == gDevObj.i2cHndl[i2cInstId]))
    {
        console_print_string("\nI2C");
        console_print_valHex(i2cInstId);
        console_print_string("DEV");
        console_print_valHex(i2cDevAddr);
        console_print_string("Illegal Params ... ERROR !!!\n");
        retVal = LLD_HSI2C_FAIL;
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        i2cParams.slaveAddr = i2cDevAddr;
        i2cParams.buffer    = regValue;
        i2cParams.bufLen    = numRegs;
        i2cParams.flags     = LLD_HSI2C_DEFAULT_WRITE;
        i2cParams.timeout   = 0xFFFFFF;

        retVal = lld_i2c_transfer(gDevObj.i2cHndl[i2cInstId], &i2cParams);
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            console_print_string("\nI2C");
            console_print_valHex(i2cInstId);
            console_print_string("DEV");
            console_print_valHex(i2cDevAddr);
            console_print_string("Illegal Params ... ERROR !!!\n");
        }
        if (gDevObj.i2cDebugEnable == TRUE)
        {
            console_print_string("\n RawWrite8 -");
            console_print_string(" I2C:");
            console_print_valHex(i2cInstId);
            console_print_string(" DEV:");
            console_print_valHex(i2cDevAddr);
            for (regId = 0; regId < numRegs; regId++)
            {
                console_print_string("-");
                console_print_valHex(regValue[regId]);
            }
        }
    }
    return (retVal);
}

int32_t DEVICEI2cDebugEnable(uint32_t enable)
{
    gDevObj.i2cDebugEnable = enable;

    return (STW_SOK);
}

