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

/*
 * main.c
 */

#include <stdint.h>
#include <stddef.h>
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include <common/stw_utils.h>
#include <common/bsp_types.h>
#include <common/trace.h>
#include <common/stw_config.h>
#include <common/bsp_utils.h>
#include <hw/hw_ctrl_core.h>

#include "i2clib/lld_hsi2c.h"
#include "soc.h"
#include "interrupt.h"
#include "hw_types.h"
#include "boards/stw_board.h"
#include "devices/stw_device.h"
#include "stwutils_app.h"

#include "AlignPattern_720_480.h"
#include "BitPattern_720_480.h"
#include "ColorPattern_720_480.h"
#include "ImagePattern_720_480.h"

#define BUF_DSS_STRIDE          (720 * 2) /* Should be multiple of 16 */
#define BUF_DSS_HEIGHT          (480)

#define MAX_NUM_BUFS_PER_PIPE   (4)
#define MAX_NUM_VID_PIPE        (4)

#define MAX_DSS_BUF_SIZE        (BUF_DSS_STRIDE * BUF_DSS_HEIGHT)

#define HSI2C_INST              (HSI2C_INST_0)

extern UInt32   AlignImg[];
extern UInt32   BitImg[];
extern UInt32   ColorImg[];
extern UInt32   Image[];

UInt32          FrameBufArrayDss[MAX_NUM_VID_PIPE][MAX_NUM_BUFS_PER_PIPE];
UInt32          dataToSlave = 0;
volatile UInt32 intStatus   = 1;

extern int App_DssRun();

#if defined (TDA2XX_FAMILY_BUILD) && !(defined (TDA2EX_BUILD))
static void App_DssSetLCD1PixClkPOlarity(UInt32 polarity);
#endif

void DssAppInit(void);

#ifdef PLATFORM_EVM_SI
UInt32 LCDConfig(uint32_t lcdCtrlI2cInstId, uint32_t lcdCtrlI2cAddr);
void LCDConfigMain(void);

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

void sampleDelay(UInt32 delay)
{
    volatile UInt32 delay1 = delay;
    while (delay1--) ;
}

void LCDConfigMain(void)
{
    uint32_t lcdCtrlInstId, lcdCtrlI2cInstId, lcdCtrlI2cAddr;
    int32_t  retVal = STW_SOK;

    printf("LCD Config\n");

    retVal = lcdBoardInfoGet(&lcdCtrlInstId,
                             &lcdCtrlI2cInstId, &lcdCtrlI2cAddr);
    if (retVal != STW_SOK)
    {
        console_print_string("\nLCD Board Get Info Failed ");
    }

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
    /* Delay is required to stabalize TLC after it is powered on */
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

#endif

#if defined (TDA2XX_FAMILY_BUILD) && !(defined (TDA2EX_BUILD))
/*
 * Due to HW bug, polarity cannot be set by vencInfo.pixelClkPolarity
 * So need to change the register SMA_SW_1 which mirrors some fields of
 * the control register.setting 1 will make LCD1 Pixel clock to be negative
 * polarity. This is required as there is an inverter in the LCD panel which
 * will effectively cause the source to sample data at rising edge of the
 * clock instead of falling edge. So changing the polarity to negative.
 */
static void App_DssSetLCD1PixClkPOlarity(UInt32 polarity)
{
    UInt32 regVal;

    regVal = HW_RD_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_SMA_SW_1);

    HW_SET_FIELD32(regVal, CTRL_CORE_SMA_SW_1_DSS_CH1_RF, polarity);

    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_SMA_SW_1,
        regVal);
}

#endif

void DssAppInit(void)
{
    Int32 retVal;
    stwAppInitParams_t stwAppInitParams;

    /* System init */
    stwAppInitParams.isI2cInitReq  = TRUE;
    stwAppInitParams.isUartInitReq = TRUE;
    retVal = StwUtils_appDefaultInit(stwAppInitParams);
    if (retVal != STW_SOK)
    {
        printf("\nSystem Init Failed ");
    }

    /* PinMux Configuration for VOUT1 */
    BOARDConfigModulePinMux(DEVICE_MODULE_ID_DCTRL,
                            DEVICE_MODULE_DSS_DISPC_OVLY_DPI1_INST_ID_0,
                            BOARD_MODE_DEFAULT);
}

int main()
{
    UInt32 vidPipeIdx = 0, numBuff = 0;

    DssAppInit();

#if PLATFORM_EVM_SI
    LCDConfigMain();
#endif

#if defined (TDA2XX_FAMILY_BUILD) && !(defined (TDA2EX_BUILD))
    App_DssSetLCD1PixClkPOlarity(1);
#endif

    FrameBufArrayDss[vidPipeIdx][numBuff]     = (UInt32) AlignImg;
    FrameBufArrayDss[vidPipeIdx][numBuff + 1] = (UInt32) BitImg;
    FrameBufArrayDss[vidPipeIdx][numBuff + 2] = (UInt32) ColorImg;
    FrameBufArrayDss[vidPipeIdx][numBuff + 3] = (UInt32) Image;

    App_DssRun();

    return 0;
}

