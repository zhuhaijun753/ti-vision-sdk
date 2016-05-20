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
 *  \file stw_device_ioexp_tca64xx.c
 *
 *  \brief TCA64xx (16/24) I2C IO expander driver file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "stdint.h"
#include <stddef.h>
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include <common/stw_config.h>
#include "i2clib/lld_hsi2c.h"
#include "boards/stw_board.h"
#include <devices/stw_device.h>
#include <devices/stw_deviceIoexp.h>
#include "stw_deviceI2cPriv.h"
#include "stw_deviceIoexpPriv.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define DEVICE_IOEXP_TCA6424_CMD_AUTO_INC            (0x80U)

/* Input status register */
#define DEVICE_IOEXP_TCA6424_REG_INPUT0              (0x00U)
#define DEVICE_IOEXP_TCA6424_REG_INPUT1              (0x01U)
#define DEVICE_IOEXP_TCA6424_REG_INPUT2              (0x02U)
/* Output register to change state of output BIT set to 1, output set HIGH */
#define DEVICE_IOEXP_TCA6424_REG_OUTPUT0             (0x04U)
#define DEVICE_IOEXP_TCA6424_REG_OUTPUT1             (0x05U)
#define DEVICE_IOEXP_TCA6424_REG_OUTPUT2             (0x06U)
/* Polarity inversion register. BIT '1' inverts input polarity of input */
#define DEVICE_IOEXP_TCA6424_REG_POLARITY0           (0x08U)
#define DEVICE_IOEXP_TCA6424_REG_POLARITY1           (0x09U)
#define DEVICE_IOEXP_TCA6424_REG_POLARITY2           (0x0AU)
/* Configuration register. BIT = '1' sets port to input, BIT = '0' sets
 * port to output */
#define DEVICE_IOEXP_TCA6424_REG_CONFIG0             (0x0CU)
#define DEVICE_IOEXP_TCA6424_REG_CONFIG1             (0x0DU)
#define DEVICE_IOEXP_TCA6424_REG_CONFIG2             (0x0EU)

/* Input status register */
#define DEVICE_IOEXP_TCA6416_REG_INPUT0              (0x00U)
#define DEVICE_IOEXP_TCA6416_REG_INPUT1              (0x01U)
/* Output register to change state of output BIT set to 1, output set HIGH */
#define DEVICE_IOEXP_TCA6416_REG_OUTPUT0             (0x02U)
#define DEVICE_IOEXP_TCA6416_REG_OUTPUT1             (0x03U)
/* Polarity inversion register. BIT '1' inverts input polarity of input */
#define DEVICE_IOEXP_TCA6416_REG_POLARITY0           (0x04U)
#define DEVICE_IOEXP_TCA6416_REG_POLARITY1           (0x05U)
/* Configuration register. BIT = '1' sets port to input, BIT = '0' sets
 * port to output */
#define DEVICE_IOEXP_TCA6416_REG_CONFIG0             (0x06U)
#define DEVICE_IOEXP_TCA6416_REG_CONFIG1             (0x07U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief IO expander global driver object.
 */
typedef struct deviceIoexpObj
{
    int32_t initValue;
} deviceIoexpObj_t;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 *  \brief Global object storing all information related to all IO expanders
 */
static deviceIoexpObj_t gDeviceIoexpObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief System init for IO expander driver
 *
 *  This API
 *      - gets called as part of Stw_deviceInit()
 *
 *  \return                 Returns STW_SOK on success else returns
 *                          failure.
 */
int32_t DEVICEIoexpInit(void)
{
    int32_t retVal = STW_SOK;
    int32_t initValue;

    /* Memset global object */
    memset(&gDeviceIoexpObj, 0, sizeof (gDeviceIoexpObj));

    initValue = (int32_t) 1;
    gDeviceIoexpObj.initValue = initValue;

    return (retVal);
}

/**
 *  \brief System de-init for IO expander driver
 *
 *  This API
 *      - gets called as part of Stw_deviceDeInit()
 *
 *  \return                 Returns STW_SOK on success else returns
 *                          failure.
 */
int32_t DEVICEIoexpDeInit(void)
{
    return (STW_SOK);
}

int32_t DEVICEIoexpTca6424WriteConfig(uint32_t       i2cInstId,
                                      uint32_t       i2cDevAddr,
                                      const uint8_t *regValue,
                                      uint32_t       numRegs)
{
    int32_t  retVal = STW_SOK;
    uint32_t cnt;
    uint8_t  tempRegVal[DEVICE_IOEXP_TCA6424_NUM_PORTS + 1U];

    if ((NULL == regValue) || (0U == numRegs) ||
        (numRegs > DEVICE_IOEXP_TCA6424_NUM_PORTS))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        /* Set command and data */
        tempRegVal[0U] = (DEVICE_IOEXP_TCA6424_REG_CONFIG0 |
                          DEVICE_IOEXP_TCA6424_CMD_AUTO_INC);
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            tempRegVal[cnt + 1U] = regValue[cnt];
        }
        retVal = DEVICEI2cRawWrite8(
            i2cInstId,
            i2cDevAddr,
            tempRegVal,
            (numRegs + 1U));
    }
    return (retVal);
}

int32_t DEVICEIoexpTca6424WriteOutputPort(uint32_t       i2cInstId,
                                          uint32_t       i2cDevAddr,
                                          const uint8_t *regValue,
                                          uint32_t       numRegs)
{
    int32_t  retVal = STW_SOK;
    uint32_t cnt;
    uint8_t  tempRegVal[DEVICE_IOEXP_TCA6424_NUM_PORTS + 1U];

    if ((NULL == regValue) || (0U == numRegs) ||
        (numRegs > DEVICE_IOEXP_TCA6424_NUM_PORTS))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        /* Set command and data */
        tempRegVal[0U] = (DEVICE_IOEXP_TCA6424_REG_OUTPUT0 |
                          DEVICE_IOEXP_TCA6424_CMD_AUTO_INC);
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            tempRegVal[cnt + 1U] = regValue[cnt];
        }
        retVal = DEVICEI2cRawWrite8(
            i2cInstId,
            i2cDevAddr,
            tempRegVal,
            (numRegs + 1U));
    }

    return (retVal);
}

int32_t DEVICEIoexpTca6424ReadOutputPort(uint32_t i2cInstId,
                                         uint32_t i2cDevAddr,
                                         uint8_t *regValue,
                                         uint32_t numRegs)
{
    int32_t  retVal = STW_SOK;
    uint32_t cnt;
    uint8_t  tempRegVal[1U];

    if ((NULL == regValue) || (0U == numRegs) ||
        (numRegs > DEVICE_IOEXP_TCA6424_NUM_PORTS))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            /* Set command */
            tempRegVal[0U] = (DEVICE_IOEXP_TCA6424_REG_OUTPUT0 |
                              DEVICE_IOEXP_TCA6424_CMD_AUTO_INC) + cnt;
            retVal = DEVICEI2cRawWrite8(
                i2cInstId,
                i2cDevAddr,
                tempRegVal,
                (uint32_t) 1);
            if (STW_SOK == retVal)
            {
                retVal = DEVICEI2cRawRead8(
                    i2cInstId,
                    i2cDevAddr,
                    &regValue[cnt],
                    (uint32_t) 1);
            }

            if (STW_SOK != retVal)
            {
                break;
            }
        }
    }

    return (retVal);
}

int32_t DEVICEIoexpTca6424ReadInputPort(uint32_t i2cInstId,
                                        uint32_t i2cDevAddr,
                                        uint8_t *regValue,
                                        uint32_t numRegs)
{
    int32_t  retVal = STW_SOK;
    uint32_t cnt;
    uint8_t  tempRegVal[1U];

    if ((NULL == regValue) || (0U == numRegs) ||
        (numRegs > DEVICE_IOEXP_TCA6424_NUM_PORTS))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            /* Set command */
            tempRegVal[0U] = (DEVICE_IOEXP_TCA6424_REG_INPUT0 |
                              DEVICE_IOEXP_TCA6424_CMD_AUTO_INC) + cnt;
            retVal = DEVICEI2cRawWrite8(
                i2cInstId,
                i2cDevAddr,
                tempRegVal,
                (uint32_t) 1);
            if (STW_SOK == retVal)
            {
                retVal = DEVICEI2cRawRead8(
                    i2cInstId,
                    i2cDevAddr,
                    &regValue[cnt],
                    (uint32_t) 1);
            }

            if (STW_SOK != retVal)
            {
                break;
            }
        }
    }

    return (retVal);
}

int32_t DEVICEIoexpTca6424WritePolarity(uint32_t       i2cInstId,
                                        uint32_t       i2cDevAddr,
                                        const uint8_t *regValue,
                                        uint32_t       numRegs)
{
    int32_t  retVal = STW_SOK;
    uint32_t cnt;
    uint8_t  tempRegVal[DEVICE_IOEXP_TCA6424_NUM_PORTS + 1U];

    if ((NULL == regValue) || (0U == numRegs) ||
        (numRegs > DEVICE_IOEXP_TCA6424_NUM_PORTS))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        /* Set command and data */
        tempRegVal[0U] = (DEVICE_IOEXP_TCA6424_REG_POLARITY0 |
                          DEVICE_IOEXP_TCA6424_CMD_AUTO_INC);
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            tempRegVal[cnt + 1U] = regValue[cnt];
        }
        retVal = DEVICEI2cRawWrite8(
            i2cInstId,
            i2cDevAddr,
            tempRegVal,
            (numRegs + 1U));
    }

    return (retVal);
}

int32_t DEVICEIoexpTca6416WriteConfig(uint32_t       i2cInstId,
                                      uint32_t       i2cDevAddr,
                                      const uint8_t *regValue,
                                      uint32_t       numRegs)
{
    int32_t  retVal = STW_SOK;
    uint32_t cnt;
    uint8_t  tempRegVal[DEVICE_IOEXP_TCA6416_NUM_PORTS + 1U];

    if ((NULL == regValue) || (0U == numRegs) ||
        (numRegs > DEVICE_IOEXP_TCA6416_NUM_PORTS))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        /* Set command and data */
        tempRegVal[0U] = DEVICE_IOEXP_TCA6416_REG_CONFIG0;
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            tempRegVal[cnt + 1U] = regValue[cnt];
        }
        retVal = DEVICEI2cRawWrite8(
            i2cInstId,
            i2cDevAddr,
            tempRegVal,
            (numRegs + 1U));
    }

    return (retVal);
}

int32_t DEVICEIoexpTca6416WriteOutputPort(uint32_t       i2cInstId,
                                          uint32_t       i2cDevAddr,
                                          const uint8_t *regValue,
                                          uint32_t       numRegs)
{
    int32_t  retVal = STW_SOK;
    uint32_t cnt;
    uint8_t  tempRegVal[DEVICE_IOEXP_TCA6416_NUM_PORTS + 1U];

    if ((NULL == regValue) || (0U == numRegs) ||
        (numRegs > DEVICE_IOEXP_TCA6416_NUM_PORTS))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        /* Set command and data */
        tempRegVal[0U] = DEVICE_IOEXP_TCA6416_REG_OUTPUT0;
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            tempRegVal[cnt + 1U] = regValue[cnt];
        }
        retVal = DEVICEI2cRawWrite8(
            i2cInstId,
            i2cDevAddr,
            tempRegVal,
            (numRegs + 1U));
    }

    return (retVal);
}

int32_t DEVICEIoexpTca6416ReadOutputPort(uint32_t i2cInstId,
                                         uint32_t i2cDevAddr,
                                         uint8_t *regValue,
                                         uint32_t numRegs)
{
    int32_t  retVal = STW_SOK;
    uint32_t cnt;
    uint8_t  tempRegVal[1U];

    if ((NULL == regValue) || (0U == numRegs) ||
        (numRegs > DEVICE_IOEXP_TCA6416_NUM_PORTS))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            /* Set command */
            tempRegVal[0U] = DEVICE_IOEXP_TCA6416_REG_OUTPUT0 + cnt;
            retVal         = DEVICEI2cRawWrite8(
                i2cInstId,
                i2cDevAddr,
                tempRegVal,
                (uint32_t) 1);
            if (STW_SOK == retVal)
            {
                retVal = DEVICEI2cRawRead8(
                    i2cInstId,
                    i2cDevAddr,
                    &regValue[cnt],
                    (uint32_t) 1);
            }

            if (STW_SOK != retVal)
            {
                break;
            }
        }
    }

    return (retVal);
}

int32_t DEVICEIoexpTca6416ReadInputPort(uint32_t i2cInstId,
                                        uint32_t i2cDevAddr,
                                        uint8_t *regValue,
                                        uint32_t numRegs)
{
    int32_t  retVal = STW_SOK;
    uint32_t cnt;
    uint8_t  tempRegVal[1U];

    if ((NULL == regValue) || (0U == numRegs) ||
        (numRegs > DEVICE_IOEXP_TCA6416_NUM_PORTS))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            /* Set command */
            tempRegVal[0U] = DEVICE_IOEXP_TCA6416_REG_INPUT0 + cnt;
            retVal         = DEVICEI2cRawWrite8(
                i2cInstId,
                i2cDevAddr,
                tempRegVal,
                (uint32_t) 1);
            if (STW_SOK == retVal)
            {
                retVal = DEVICEI2cRawRead8(
                    i2cInstId,
                    i2cDevAddr,
                    &regValue[cnt],
                    (uint32_t) 1);
            }

            if (STW_SOK != retVal)
            {
                break;
            }
        }
    }

    return (retVal);
}

int32_t DEVICEIoexpTca6416WritePolarity(uint32_t       i2cInstId,
                                        uint32_t       i2cDevAddr,
                                        const uint8_t *regValue,
                                        uint32_t       numRegs)
{
    int32_t  retVal = STW_SOK;
    uint32_t cnt;
    uint8_t  tempRegVal[DEVICE_IOEXP_TCA6416_NUM_PORTS + 1U];

    if ((NULL == regValue) || (0U == numRegs) ||
        (numRegs > DEVICE_IOEXP_TCA6416_NUM_PORTS))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        /* Set command and data */
        tempRegVal[0U] = DEVICE_IOEXP_TCA6416_REG_POLARITY0;
        for (cnt = 0U; cnt < numRegs; cnt++)
        {
            tempRegVal[cnt + 1U] = regValue[cnt];
        }
        retVal = DEVICEI2cRawWrite8(
            i2cInstId,
            i2cDevAddr,
            tempRegVal,
            (numRegs + 1U));
    }

    return (retVal);
}

