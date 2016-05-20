/* ======================================================================
 *   Copyright (C) 2013 Texas Instruments Incorporated
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

#include "stdint.h"
#include <stdio.h>
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include <common/stw_config.h>
#include <common/stw_utils.h>
#include "i2clib/lld_hsi2c.h"
#include "soc_defines.h"
#include "platform.h"
#include "uartStdio.h"
#include "interrupt.h"
#include "soc.h"
#include "stw_boardPriv.h"
#include "boards/stw_board.h"
#include "devices/stw_device.h"
#include "stwutils_app.h"

/***********************************************************************/
/*                    INTERNAL MACRO DEFINITION                        */
/***********************************************************************/

#define TEMP_SENSOR_INST_NUM                    (0U)

/***********************************************************************/
/*                   INTERNAL VARIABLE DEFINITION                      */
/***********************************************************************/
volatile uint32_t intStatus = 1;
uint8_t           data_tx[4];
uint8_t           data_rx[4];

/*******************************************************************************
**                   INTERNAL FUNCTION PROTOTYPE
*******************************************************************************/
void get_temp();

uint32_t readTemperature(uint32_t tempSensorI2cInstId,
                         uint32_t tempSensorI2cAddr);

void sampleDelay(uint32_t delay);

static int32_t tempSensorBoardInfoGet(uint32_t *tempSensorI2cInstId,
                                      uint32_t *tempSensorI2cAddr);

static int32_t tempSensorBoardInfoGet(uint32_t *tempSensorI2cInstId,
                                      uint32_t *tempSensorI2cAddr)
{
    int32_t  status = STW_EFAIL;
    uint32_t ctrlModId;
    uint32_t ctrlModInstNum;
    uint32_t ctrlModAddr;

    /* Get the I2C data for EEPROM from the board data */
    ctrlModId = BOARDGetDeviceCtrlModId(DEVICE_ID_TMP102, TEMP_SENSOR_INST_NUM);

    if (DEVICE_ID_INVALID == ctrlModId)
    {
        console_print_string("\nDevice is not available on this board ");
    }
    else if (DEVICE_ID_I2C == ctrlModId)
    {
        ctrlModInstNum = BOARDGetDeviceCtrlModInstNum(DEVICE_ID_TMP102,
                                                      TEMP_SENSOR_INST_NUM);
        ctrlModAddr = BOARDGetDeviceCtrlInfo(DEVICE_ID_TMP102,
                                             TEMP_SENSOR_INST_NUM);

        if ((INVALID_INST_NUM == ctrlModInstNum) ||
            (INVALID_INFO == ctrlModAddr))
        {
            console_print_string("\nInvalid I2C board data ");
        }
        else
        {
            *tempSensorI2cInstId = ctrlModInstNum;
            *tempSensorI2cAddr   = ctrlModAddr;
            status = STW_SOK;
        }
    }
    else
    {
        console_print_string("\nDevice is not connected to I2C ");
    }

    return status;
}

int main()
{
    uint32_t             tempSensorI2cInstId = 0U;
    uint32_t             tempSensorI2cAddr   = BOARD_TEMP_SENSOR_I2C_ADDR;
    stwAppInitParams_t   stwAppInitParams;
    stwAppDeInitParams_t stwAppDeInitParams;
    int32_t retVal;

    /* System init */
    stwAppInitParams.isI2cInitReq  = TRUE;
    stwAppInitParams.isUartInitReq = TRUE;
    retVal = StwUtils_appDefaultInit(stwAppInitParams);
    if (retVal != STW_SOK)
    {
        console_print_string("\nSystem Init Failed ");
    }

    retVal = tempSensorBoardInfoGet(&tempSensorI2cInstId, &tempSensorI2cAddr);
    if (retVal != STW_SOK)
    {
        console_print_string("\nTemp Sensor Board Get Info Failed ");
    }

    Intc_Init();
    Intc_IntEnable(0);

    retVal = DEVICEI2cProbeDevice(
        tempSensorI2cInstId,
        tempSensorI2cAddr);
    if (LLD_HSI2C_SUCCESS != retVal)
    {
        return retVal;
    }

    console_print_string("\nProbing Temperature sensor with slave address ");
    console_print_valHex(tempSensorI2cAddr);
    console_print_string(" successful ");

    readTemperature(tempSensorI2cInstId, tempSensorI2cAddr);
    get_temp();

    console_print_string("\nTemperature sensor test successful ");

    /* System De init */
    stwAppDeInitParams.isI2cDeInitReq = TRUE;
    retVal = StwUtils_appDefaultDeInit(stwAppDeInitParams);
    if (retVal != STW_SOK)
    {
        console_print_string("\nSystem Init Failed ");
    }

    return 0;
}

void sampleDelay(uint32_t delay)
{
    volatile uint32_t delay1 = delay;
    while (delay1--) ;
}

uint32_t readTemperature(uint32_t tempSensorI2cInstId,
                         uint32_t tempSensorI2cAddr)
{
    uint32_t retVal = LLD_HSI2C_SUCCESS;
    data_tx[0] = 0x00;

    retVal = DEVICEI2cRawWrite8(tempSensorI2cInstId,
                                tempSensorI2cAddr,
                                &data_tx[0],
                                1);
    sampleDelay(1000);

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        console_print_string("\nI2c write failed ");
    }
    else
    {
        /*console_print_string("\nI2c write successfull ");*/
    }

    retVal = DEVICEI2cRawRead8(tempSensorI2cInstId,
                               tempSensorI2cAddr,
                               &data_rx[0],
                               2);

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        console_print_string("\nI2c read failed ");
    }
    else
    {
        /*console_print_string("\nI2c read successfull ");*/
    }

    return retVal;
}

void get_temp()
{
    unsigned int temp, temp1;
    temp  = data_rx[0];
    temp  = temp << 4;
    temp1 = data_rx[1] >> 4;
    temp  = temp | temp1;

    temp1 = temp * 625; /*convert the hex number to tempurature degrees*/
    temp1 = temp1 / 10000;
    console_print_string("\n Temperature is: ");
    console_print_val(temp1);
    console_print_string(" degree C ");
}

