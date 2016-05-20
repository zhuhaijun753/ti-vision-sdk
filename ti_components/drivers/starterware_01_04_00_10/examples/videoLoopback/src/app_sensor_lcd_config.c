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
#include "i2clib/lld_hsi2c.h"
#include "lld_hsi2c_edma.h"
#include "soc_defines.h"
#include "platform.h"
#include "ov_sensorconfig.h"
#include "edma.h"
#include "interrupt.h"
#include "soc.h"
#include <gpio_v2.h>
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include <common/stw_utils.h>
#include "boards/stw_board.h"
#include "devices/stw_device.h"
#include <common/trace.h>

/***********************************************************************/
/*                    INTERNAL MACRO DEFINITION                        */
/***********************************************************************/
/*None*/

/***********************************************************************/
/*                   INTERNAL VARIABLE DEFINITION                      */
/***********************************************************************/

/*******************************************************************************
**                   INTERNAL FUNCTION PROTOTYPE
*******************************************************************************/
uint32_t ovSensorConfig(uint32_t ovSensorI2cInstId, uint32_t ovSensorI2cAddr);
UInt32 LCDConfig(uint32_t lcdCtrlI2cInstId, uint32_t lcdCtrlI2cAddr);
void sensor_config(void);
void LCDConfigMain(void);
void sampleDelay(uint32_t delay);
static void videoLoopbackCaptInit(uint32_t ovSensorInstId);
static void videoLoopbackDSSInit(uint32_t lcdCtrlInstId);
static int32_t lcdBoardInfoGet(uint32_t *lcdCtrlInstId,
                               uint32_t *lcdCtrlI2cInstId,
                               uint32_t *lcdCtrlI2cAddr)
{
    int32_t status = STW_SOK;

    *lcdCtrlInstId = BOARDGetVideoDeviceInstId(
        DEVICE_ID_LCD,
        DEVICE_MODULE_ID_DCTRL,
        DEVICE_MODULE_DSS_DISPC_OVLY_DPI1_INST_ID_0);

    *lcdCtrlI2cInstId = BOARDGetVideoDeviceI2cInstId(
        DEVICE_ID_LCD,
        DEVICE_MODULE_ID_DCTRL,
        DEVICE_MODULE_DSS_DISPC_OVLY_DPI1_INST_ID_0);

    *lcdCtrlI2cAddr = BOARDGetVideoDeviceI2cAddr(
        DEVICE_ID_LCD,
        DEVICE_MODULE_ID_DCTRL,
        DEVICE_MODULE_DSS_DISPC_OVLY_DPI1_INST_ID_0);

    return status;
}

static int32_t ovSensorBoardInfoGet(uint32_t *ovSensorInstId,
                                    uint32_t *ovSensorI2cInstId,
                                    uint32_t *ovSensorI2cAddr)
{
    int32_t  status = STW_SOK;
    uint32_t vipModInstNum;

#ifdef TDA2EX_BUILD
    vipModInstNum = DEVICE_MODULE_VIP1_S1_PORTA_INST_ID_0;
#else
    vipModInstNum = DEVICE_MODULE_VIP1_S0_PORTA_INST_ID_0;
#endif

    *ovSensorInstId = BOARDGetVideoDeviceInstId(
        DEVICE_ID_OV1063X,
        DEVICE_MODULE_ID_VIP,
        vipModInstNum);

    *ovSensorI2cInstId = BOARDGetVideoDeviceI2cInstId(
        DEVICE_ID_OV1063X,
        DEVICE_MODULE_ID_VIP,
        vipModInstNum);

    *ovSensorI2cAddr = BOARDGetVideoDeviceI2cAddr(
        DEVICE_ID_OV1063X,
        DEVICE_MODULE_ID_VIP,
        vipModInstNum);

    return status;
}

void sensor_config(void)
{
    uint32_t ovSensorInstId, ovSensorI2cInstId, ovSensorI2cAddr;
    int32_t  retVal;

    retVal = ovSensorBoardInfoGet(&ovSensorInstId,
                                  &ovSensorI2cInstId, &ovSensorI2cAddr);
    if (retVal != STW_SOK)
    {
        console_print_string("\nOV Sensor Board Get Info Failed ");
    }

    videoLoopbackCaptInit(ovSensorInstId);

    ovSensorConfig(ovSensorI2cInstId, ovSensorI2cAddr);

    console_print_string("\nSensor config done ");
}

void sampleDelay(uint32_t delay)
{
    volatile uint32_t delay1 = delay;
    while (delay1--) ;
}

uint32_t ovSensorConfig(uint32_t ovSensorI2cInstId, uint32_t ovSensorI2cAddr)
{
    uint32_t          retVal = LLD_HSI2C_SUCCESS;
    volatile uint32_t count, k;
    uint32_t          sensorScriptSize;
    uint16_t          regAddr;
    uint8_t           data[4];

    data[0] = 0x30;
    data[1] = 0x03;
    data[2] = 0x20;

    retVal = DEVICEI2cRawWrite8(ovSensorI2cInstId,
                                ovSensorI2cAddr,
                                &data[0],
                                3);
    sampleDelay(1000);

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        console_print_string("\nI2c write failed ");
    }

    regAddr = 0x3003;
    data[0] = (uint8_t) (regAddr >> 8);
    data[1] = (uint8_t) (regAddr);

    retVal = DEVICEI2cRawWrite8(ovSensorI2cInstId,
                                ovSensorI2cAddr,
                                &data[0],
                                2);
    sampleDelay(1000);

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        console_print_string("\nI2c write failed ");
    }

    retVal = DEVICEI2cRawRead8(ovSensorI2cInstId,
                               ovSensorI2cAddr,
                               &data[0],
                               2);
    sampleDelay(1000);

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        console_print_string("\nI2c Read failed ");
    }

    sensorScriptSize = sizeof (SensorConfigScript_OV) / (3 * sizeof (uint32_t));

    for (count = 0; count < sensorScriptSize; count++)
    {
        data[0] = (SensorConfigScript_OV[count][0] & 0xffff) >> 8;  /* MSB */

        data[1] = (SensorConfigScript_OV[count][0] & 0xff);         /* LSB  */

        data[2] = (SensorConfigScript_OV[count][1] & 0xff);         /* value  */

        retVal = DEVICEI2cRawWrite8(ovSensorI2cInstId,
                                    ovSensorI2cAddr,
                                    &data[0],
                                    3);

        if (LLD_HSI2C_SUCCESS != retVal)
        {
            console_print_string("\nI2c write failed ");
        }
    }

    return retVal;
}

void LCDConfigMain(void)
{
    uint32_t lcdCtrlInstId, lcdCtrlI2cInstId, lcdCtrlI2cAddr;
    int32_t  retVal;

    printf("LCD Config\n");

    retVal = lcdBoardInfoGet(&lcdCtrlInstId,
                             &lcdCtrlI2cInstId, &lcdCtrlI2cAddr);
    if (retVal != STW_SOK)
    {
        console_print_string("\nLCD Board Get Info Failed ");
    }

    videoLoopbackDSSInit(lcdCtrlInstId);

    LCDConfig(lcdCtrlI2cInstId, lcdCtrlI2cAddr);

    printf("LCD config done\n");
}

UInt32 LCDConfig(uint32_t lcdCtrlI2cInstId, uint32_t lcdCtrlI2cAddr)
{
    UInt32 retVal = LLD_HSI2C_SUCCESS;
    UInt8  data[2];

/* For Tda3xx board its done in videoLoopbackAppinit API */
#ifdef TDA2XX_FAMILY_BUILD

    /* Configure board mux */
    data[0] = 0xDBU;
    data[1] = 0xDBU;
    retVal  = DEVICEI2cRawWrite8(lcdCtrlI2cInstId,
                                 lcdCtrlI2cAddr,
                                 &data[0],
                                 2);
    /* Delay is required to stabalize TLC after it is poered on */
    sampleDelay(1000);

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        console_print_string("I2c failed: Step 1\n");
    }
#endif
    data[0] = 0x00U;
    data[1] = 0x01U;
    retVal  = DEVICEI2cRawWrite8(lcdCtrlI2cInstId,
                                 lcdCtrlI2cAddr,
                                 &data[0],
                                 2);
    if (LLD_HSI2C_SUCCESS != retVal)
    {
        console_print_string("I2c failed: Step 2\n");
    }

    data[0] = 0x0CU;
    data[1] = 0x21U;
    retVal  = DEVICEI2cRawWrite8(lcdCtrlI2cInstId,
                                 lcdCtrlI2cAddr,
                                 &data[0],
                                 2);
    if (LLD_HSI2C_SUCCESS != retVal)
    {
        console_print_string("I2c failed: Step 3\n");
    }

    data[0] = 0x04U;
    data[1] = 0xFFU;
    retVal  = DEVICEI2cRawWrite8(lcdCtrlI2cInstId,
                                 lcdCtrlI2cAddr,
                                 &data[0],
                                 2);
    if (LLD_HSI2C_SUCCESS != retVal)
    {
        console_print_string("I2c failed: Step 4\n");
    }

    data[0] = 0x0DU;
#if defined (TDA3XX_FAMILY_BUILD) || defined (TDA2EX_BUILD)
    /* For LG LCD panel, the bit 8 of TLC specified the pixel polarity at
     * which data should be sampled - configuring it to rising edge as there
     * is a inverter in LCD.
     */
    data[1] = 0x51U;
#elif defined (TDA2XX_FAMILY_BUILD)
    data[1] = 0x01U;
#endif
    retVal = DEVICEI2cRawWrite8(lcdCtrlI2cInstId,
                                lcdCtrlI2cAddr,
                                &data[0],
                                2);
    if (LLD_HSI2C_SUCCESS != retVal)
    {
        console_print_string("I2c failed: Step 5\n");
    }
    return retVal;
}

static void videoLoopbackCaptInit(uint32_t ovSensorInstId)
{
    Int32 retVal;

    retVal = BOARDPowerOnDevice(DEVICE_ID_OV1063X, ovSensorInstId, TRUE);
    if (retVal != STW_SOK)
    {
        printf("\nBoard Power On OV Sensor Device Failed ");
    }

    BOARDSelectDevice(DEVICE_ID_OV1063X, ovSensorInstId);

    retVal = BOARDSelectMode(DEVICE_ID_OV1063X,
                             ovSensorInstId, BOARD_MODE_VIDEO_8BIT);
    if (retVal != STW_SOK)
    {
        printf("\n Board Select Mode Failed ");
    }
}

static void videoLoopbackDSSInit(uint32_t lcdCtrlInstId)
{
    Int32 retVal;

    retVal = BOARDPowerOnDevice(DEVICE_ID_LCD, lcdCtrlInstId, TRUE);
    if (retVal != STW_SOK)
    {
        printf("\nBoard Power On LCD Device Failed ");
    }

    BOARDSelectDevice(DEVICE_ID_LCD, lcdCtrlInstId);

    retVal = BOARDSelectMode(DEVICE_ID_LCD, lcdCtrlInstId,
                             BOARD_MODE_VIDEO_24BIT);
    if (retVal != STW_SOK)
    {
        printf("\n Board Select Mode Failed ");
    }
}

