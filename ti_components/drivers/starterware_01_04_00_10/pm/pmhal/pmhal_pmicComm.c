/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 * \file    pmhal_pmicComm.c
 *
 * \brief   This file contains the BUS communication utility functions to
 *          communicate with the PMIC.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include "pm_types.h"
#include "pm_utils.h"
#include "pmhal_pmicComm.h"
#include "hw_types.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None  */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/*
 * Pointer to the PMIC I2C functions. This should be populated with pointers to
 * the I2C driver being used.
 */
static const pmhalPmicCommI2cOperations_t *gPmhalPmicI2cFunc = NULL;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

pmErrCode_t PMHALPmicCommI2CRegister(
    const pmhalPmicCommI2cOperations_t *pmicI2cfunc)
{
    pmErrCode_t     status = PM_FAIL;
    static uint32_t i2cRegistrationDone = 0U;
    /*
     * The API checks if all the function pointers are properly populated.
     */
    if ((pmicI2cfunc != NULL) && (0U == i2cRegistrationDone))
    {
        if ((pmicI2cfunc->pmhalPmicI2cInit != NULL) &&
            (pmicI2cfunc->pmhalPmicI2cRead != NULL) &&
            (pmicI2cfunc->pmhalPmicI2cWrite != NULL))
        {
            gPmhalPmicI2cFunc = pmicI2cfunc;
            status = PM_SUCCESS;
            /* Once the registration is done do not re-do the registration */
            i2cRegistrationDone = 1U;
        }
    }
    return status;
}

pmErrCode_t PMHALPmicCommConfigure(uint8_t i2cNum)
{
    pmErrCode_t     status        = PM_SUCCESS;
    static uint32_t configureDone = 0U;
    int32_t         retval        = 0;
    /* Only one time configuration */
    if (0U == configureDone)
    {
        if (gPmhalPmicI2cFunc->pmhalPmicI2cInit != NULL)
        {
            /* This is the driver specific I2C initialization */
            retval = gPmhalPmicI2cFunc->pmhalPmicI2cInit();
            if (0 == retval)
            {
                status        = PM_SUCCESS;
                configureDone = 1U;
            }
            else
            {
                status = PM_FAIL;
            }
        }
    }
    return status;
}

pmErrCode_t PMHALPmicCommReadByte(uint8_t  i2cNum,
                                  uint8_t  slaveAddr,
                                  uint8_t  regAddr,
                                  uint8_t *value)
{
    pmErrCode_t status = PM_SUCCESS;
    int32_t     retval = 0;
    uint8_t     dataArr[1];

    /* Populate the data to an array */
    dataArr[0] = regAddr;
    /* This is the driver specific read implementation */
    if (gPmhalPmicI2cFunc->pmhalPmicI2cRead != NULL)
    {
        retval = gPmhalPmicI2cFunc->pmhalPmicI2cRead((uint32_t) i2cNum,
                                                     (uint32_t) slaveAddr,
                                                     (const uint8_t *) dataArr,
                                                     value, 1U);
        if (0 == retval)
        {
            status = PM_SUCCESS;
        }
        else
        {
            status = PM_FAIL;
        }
    }
    else
    {
        status = PM_FAIL;
    }
    return status;
}

pmErrCode_t PMHALPmicCommWriteByte(uint8_t i2cNum,
                                   uint8_t slaveAddr,
                                   uint8_t regAddr,
                                   uint8_t value)
{
    pmErrCode_t status = PM_SUCCESS;
    uint8_t     dataAddr[1], dataValue[1];
    int32_t     retval = 0;

    /* Populate the data to an array */
    dataAddr[0]  = regAddr;
    dataValue[0] = value;
    if (gPmhalPmicI2cFunc->pmhalPmicI2cWrite != NULL)
    {
        retval = gPmhalPmicI2cFunc->pmhalPmicI2cWrite(
            i2cNum, slaveAddr,
            (const uint8_t *)
            dataAddr, dataValue, 1U);
        if (0 == retval)
        {
            status = PM_SUCCESS;
        }
        else
        {
            status = PM_FAIL;
        }
    }
    else
    {
        status = PM_FAIL;
    }
    return status;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */
