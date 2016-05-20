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
#include <stdint.h>
#include <stddef.h>
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include <common/bsp_types.h>
#include <captcore/vpscore_vip.h>
#include <common/trace.h>
#include <common/stw_config.h>
#include <common/bsp_utils.h>
#include <app_frameBufMgmt.h>
#include <app_videoLoopbackConfigure.h>
#include <dispcore/vpscore_dctrl.h>
#include <dispcore/vpscore_dss.h>
#include <hw/hw_ctrl_core.h>
#include <hw/hw_ctrl_core_pad.h>
#include <vps_dssDrv.h>
#include <vps_dctrlDrv.h>

#include "i2clib/lld_hsi2c.h"
#include "soc.h"
#include "interrupt.h"
#include "hw_types.h"
#include "vps_dssDrv.h"
#include "gpio_v2.h"
#include "boards/stw_board.h"
#include "devices/stw_device.h"
#include "stwutils_app.h"

#define TEST_CASE_DURATION (1000)

void videoLoopbackAppInit(void);
#if defined (TDA2XX_FAMILY_BUILD) && !(defined (TDA2EX_BUILD))
static void App_DssSetLCD1PixClkPOlarity(UInt32 polarity);
#endif
extern Int32 Platform_Tda2xxInit();
extern void sensor_config(void);
extern void LCDConfigMain(void);
extern Int32 Platform_Tda3xxInit();

UInt32                 gEnableInfiniteCaptLoop = 0;
volatile UInt32        gDqCount_portA          = 0;
volatile UInt32        gDqCount_portB          = 0;
volatile int           gNLinIntCount_sxportA   = 0;
volatile int           gNLinIntCount_sxportB   = 0;

extern volatile UInt32 gDqCount_vid;

VpsCore_Frame *App_queBufs(void *drvData, UInt32 streamId, UInt32 chId)
{
    return (VpsCore_Frame *) App_GetFrameBuf((UInt32) drvData);
}

Int32 App_deQueBufs(void *drvData, VpsCore_Frame *frmBufList)
{
    if (BUF_ARRAY_IDX_PORTA == (UInt32) drvData)
    {
        gDqCount_portA++;
    }
    else if (BUF_ARRAY_IDX_PORTB == (UInt32) drvData)
    {
        gDqCount_portB++;
    }

    App_ReleaseFrameBuf(frmBufList, (UInt32) drvData);
    return 0;
}

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

int32_t videoLoopbackModuleInit()
{
    int32_t retVal = STW_SOK;

    /* PinMux Configuration for VOUT1 */
    BOARDConfigModulePinMux(DEVICE_MODULE_ID_DCTRL,
                            DEVICE_MODULE_DSS_DISPC_OVLY_DPI1_INST_ID_0,
                            BOARD_MODE_DEFAULT);

#ifdef TDA2EX_BUILD
    /* Set the VIN mux at control module level */
    HW_WR_FIELD32(
        (SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
         CTRL_CORE_VIP_MUX_SELECT),
        CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_2A,
        CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_2A_GROUP2A);

    /* PinMux Configuration for VIN2A */
    BOARDConfigModulePinMux(DEVICE_MODULE_ID_VIP,
                            DEVICE_MODULE_VIP1_S1_PORTA_INST_ID_0,
                            BOARD_MODE_VIDEO_8BIT);

#else
    /* PinMux Configuration for VIN1A */
    BOARDConfigModulePinMux(DEVICE_MODULE_ID_VIP,
                            DEVICE_MODULE_VIP1_S0_PORTA_INST_ID_0,
                            BOARD_MODE_VIDEO_8BIT);
#endif
    return retVal;
}

int main()
{
    Int32 retVal = 0;
    VpsDrv_CaptInstObj  *captObj_portA = NULL;
    VpsDrv_CaptInstObj  *captObj_portB = NULL;
    VpsDrv_DispInstObj  *DispObj       = NULL;
    VpsDrv_DctrlInstObj *DctrlObj      = NULL;

    /*** START POINT ***/
    videoLoopbackAppInit();
    videoLoopbackModuleInit();
#if defined (TDA2XX_FAMILY_BUILD) && !(defined (TDA2EX_BUILD))
    App_DssSetLCD1PixClkPOlarity(1);
#endif

    /* Sensor configuation */
    sensor_config();

    Bsp_printf("***** START :: VPS Init\n");
    Vps_init(NULL);
    Bsp_printf("***** STOP  :: VPS Init\n");

    App_FrameBufInit();

    /* Initialize & Open the VIP Core */
    Bsp_printf("***** START :: VIP Core Initialization\n");
#ifdef TDA2EX_BUILD
    captObj_portA = App_coreOpen(VPSHAL_VIP1, VPSHAL_VIP_S1, VPSHAL_VIP_PORT_A);
#else
    captObj_portA = App_coreOpen(VPSHAL_VIP1, VPSHAL_VIP_S0, VPSHAL_VIP_PORT_A);
#endif

#ifdef TDA2EX_BUILD
    captObj_portB = App_coreOpen(VPSHAL_VIP1, VPSHAL_VIP_S1, VPSHAL_VIP_PORT_B);
#else
    captObj_portB = App_coreOpen(VPSHAL_VIP1, VPSHAL_VIP_S0, VPSHAL_VIP_PORT_B);
#endif
    if ((captObj_portA == NULL) || (captObj_portB == NULL))
    {
        Bsp_printf("***** FAILED :: VIP Core Open  ***** \n");
        return -1;
    }
    Bsp_printf("***** STOP  :: VIP Core Initialization\n");

    /* Configure VIP1 module */
    Bsp_printf("***** START :: Configure VIP\n");
#ifdef TDA2EX_BUILD
    retVal = App_configureVIP(captObj_portA, VPSHAL_VIP_S1, VPSHAL_VIP_PORT_A);
#else
    retVal = App_configureVIP(captObj_portA, VPSHAL_VIP_S0, VPSHAL_VIP_PORT_A);
#endif

#ifdef TDA2EX_BUILD
    retVal |= App_configureVIP(captObj_portB, VPSHAL_VIP_S1, VPSHAL_VIP_PORT_B);
#else
    retVal |= App_configureVIP(captObj_portB, VPSHAL_VIP_S0, VPSHAL_VIP_PORT_B);
#endif
    if (retVal != BSP_SOK)
    {
        Bsp_printf("***** FAIL  :: Configure VIP \n");
        return -1;
    }
    Bsp_printf("***** STOP  :: Configure VIP\n");

    /* Configure LCD */
    LCDConfigMain();

    /* Initialize & Open the VIP Core */
    Bsp_printf("***** START :: DSS Core Initialization\n");
    DctrlObj = App_dctrlcoreOpen();
    if (DctrlObj == NULL)
    {
        Bsp_printf("***** FAILED :: Dctrl Core Open  ***** \n");
        return -1;
    }

    /* Configure Dss and Dctrl module */
    Bsp_printf("***** START :: Configure Dctrl\n");
    retVal  = App_configureDctrl(DctrlObj);
    retVal |= App_configureDctrlPipe(DctrlObj);

    if (retVal != BSP_SOK)
    {
        Bsp_printf("***** FAIL  :: Configure Dctrl \n");
        return -1;
    }

    DispObj = App_dsscoreOpen(VPSDRV_DISP_INST_DSS_VID1);

    Bsp_printf("***** STOP  :: Dss Core Initialization\n");

    if (DispObj == NULL)
    {
        Bsp_printf("***** FAILED :: Dss Core Open  ***** \n");
        return -1;
    }

    retVal = App_dssconfigure(DispObj);

    if (retVal != BSP_SOK)
    {
        Bsp_printf("***** FAIL  :: Configure Dss\n");
        return -1;
    }
    Bsp_printf("***** STOP  :: Configure Dss\n");

    gNLinIntCount_sxportA = 0;
    gNLinIntCount_sxportB = 0;
    gDqCount_portA        = 0;
    gDqCount_portB        = 0;

    /* Start Capture */
    App_coreStart(captObj_portA);
    App_coreStart(captObj_portB);

    /* Start display */
    App_dsscoreStart(DispObj);

    while ((gDqCount_portA < TEST_CASE_DURATION) || gEnableInfiniteCaptLoop)
    {
        /*
         * Wait for TEST_CASE_DURATION number of frames to be captured on
         * PORT A
         */
    }

    App_coreStop(captObj_portA);
    App_coreStop(captObj_portB);

    Bsp_printf("Frames captured on PortA            : %d\n", gDqCount_portA);
    Bsp_printf("Frames captured on PortB            : %d\n", gDqCount_portB);
    Bsp_printf("Sub-frame interrupts recvd on PortA : %d\n",
               gNLinIntCount_sxportA);
    Bsp_printf("Sub-frame interrupts recvd on PortB : %d\n",
               gNLinIntCount_sxportB);

    App_dsscoreStop(DispObj);

    Bsp_printf("Frames Displayed            : %d\n", gDqCount_vid);

    gNLinIntCount_sxportA = 0;
    gNLinIntCount_sxportB = 0;
    gDqCount_portA        = 0;
    gDqCount_portB        = 0;

    /* De-Initialize & Close the VIP Core*/
    App_coreClose(captObj_portA);
    App_coreClose(captObj_portB);

    /* De-Initialize & Close the Dss and Dctrl Core*/
    App_dsscoreClose(DispObj);
    /* Add dctrl clear config */

    /* De-Initialize Frame buffer management and VPS library */
    App_FrameBufDeInit();
    Vps_deInit(NULL);

    return 0;
}

void videoLoopbackAppInit(void)
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
}

