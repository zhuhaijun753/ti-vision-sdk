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

#if (defined (TDA2XX_FAMILY_BUILD)) || (defined (TDA3XX_FAMILY_BUILD))
#include <hw/hw_ctrl_core_pad.h>
#endif

#include <common/bsp_types.h>
#include <captcore/vpscore_vip.h>

#include <app_frameBufMgmt.h>
#include <app_vipConfigure.h>
#include <common/trace.h>
#include <common/stw_config.h>
#include "soc.h"
#include "hw_types.h"
#include "i2clib/lld_hsi2c.h"
#include "boards/stw_board.h"
#include "devices/stw_device.h"
#include "stwutils_app.h"

#define TEST_CASE_DURATION (1000)

UInt32             gEnableInfiniteCaptLoop = 0;
volatile UInt32    gsubFrmCbCnt_s0portA    = 0;
volatile UInt32    gsubFrmCbCnt_s0portB    = 0;
volatile int       gNLinIntCount_s0portA   = 0;
volatile int       gNLinIntCount_s0portB   = 0;
volatile UInt32    gsubFrmAdd_s0portA;
volatile UInt32    gDqCount_portA = 0;
volatile UInt32    gDqCount_portB = 0;

Fvid2_SubFrameInfo gSubFrmInfo_s0portA;

extern UInt32      subFrmCallBackCount;
extern Int32 Platform_TI814xInit();
void vipCaptAppInit(void);
int32_t vipCaptModuleInit();

VpsCore_Frame *App_queBufs(void *drvData, UInt32 streamId, UInt32 chId)
{
    return (VpsCore_Frame *) App_GetFrameBuf((UInt32) drvData);
}

Int32 App_deQueBufs(void *drvData, VpsCore_Frame *frmBufList)
{
    if (BUF_ARRAY_IDX_PORTA == (UInt32) drvData)
    {
        gDqCount_portA++;
        /* Reset the subFrm call back count once frame is completely
         * captured */
        gsubFrmCbCnt_s0portA = 0;
    }
    else if (BUF_ARRAY_IDX_PORTB == (UInt32) drvData)
    {
        gDqCount_portB++;
        gsubFrmCbCnt_s0portB = 0;
    }

    App_ReleaseFrameBuf(frmBufList);
    return 0;
}

int main()
{
    Int32 retVal = 0;
    VpsDrv_CaptInstObj     *captObj_portA = NULL;
    VpsDrv_CaptInstObj     *captObj_portB = NULL;
    Vps_OverflowCheckParams isOverflowOccuredPortA;
    Vps_OverflowCheckParams isOverflowOccuredPortB;;

    /*** START POINT ***/
    Bsp_printf("Hello World\n");
#if (defined (TI814X_FAMILY_BUILD))
    Platform_TI814xInit();
#endif

#if (defined (TDA2XX_FAMILY_BUILD)) || (defined (TDA3XX_FAMILY_BUILD))
    vipCaptAppInit();
    vipCaptModuleInit();
#endif

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

    gNLinIntCount_s0portA = 0;
    gNLinIntCount_s0portB = 0;
    gDqCount_portA        = 0;
    gDqCount_portB        = 0;

#ifdef TI814X_FAMILY_BUILD
    /* Following two function calls are only for TI814X_FAMILY_BUILD.
     * These should be called for all PORTs before calling any App_coreStart()
     */
    App_portReset(captObj_portA);
    App_portReset(captObj_portB);
#endif

    /* Start Capture */
    App_coreStart(captObj_portA);
    App_coreStart(captObj_portB);

    while ((gDqCount_portA < TEST_CASE_DURATION) || gEnableInfiniteCaptLoop)
    {
        /*
         * Wait for TEST_CASE_DURATION number of frames to be captured on
         * PORT A
         */
        /*Keep checking for the overflow*/
        if ((captObj_portA->overflowCount > 0) ||
            (captObj_portB->overflowCount > 0))
        {
            retVal  = App_checkOverflow(captObj_portA, &isOverflowOccuredPortA);
            retVal += App_checkOverflow(captObj_portB, &isOverflowOccuredPortB);
            if (BSP_SOK == retVal)
            {
#ifdef TI814X_FAMILY_BUILD
                /*If overflow occured on port A or Port B, both ports get
                 * reset*/
                if (((UInt32) TRUE ==
                     isOverflowOccuredPortA.isOverflowOccured) ||
                    ((UInt32) TRUE == isOverflowOccuredPortB.isOverflowOccured))
                {
                    /*Stop the driver*/
                    App_coreStop(captObj_portA);
                    App_coreStop(captObj_portB);

                    /* Reset the VIP */
                    App_portReset(captObj_portA);
                    App_portReset(captObj_portB);
                    /* Restart the driver */
                    App_coreStart(captObj_portA);
                    App_coreStart(captObj_portB);
                    captObj_portA->overflowCount = 0;
                    captObj_portB->overflowCount = 0;
                }
#endif
#if (defined (TDA2XX_FAMILY_BUILD)) || (defined (TDA3XX_FAMILY_BUILD))
                /* In vayu, we have selective reset. We can reset one VIP port
                 * without affecting the
                 * working of other
                 */
                if ((UInt32) TRUE == isOverflowOccuredPortA.isOverflowOccured)
                {
                    /*Stop the driver*/
                    App_coreStop(captObj_portA);

                    /* Reset the VIP */
                    App_portReset(captObj_portA);
                    /* Restart the driver */
                    App_coreStart(captObj_portA);
                    captObj_portA->overflowCount = 0;
                }
                if ((UInt32) TRUE == isOverflowOccuredPortB.isOverflowOccured)
                {
                    /*Stop the driver*/
                    App_coreStop(captObj_portB);

                    /* Reset the VIP */
                    App_portReset(captObj_portB);
                    /* Restart the driver */
                    App_coreStart(captObj_portB);
                    captObj_portB->overflowCount = 0;
                }

#endif
            }
        }
    }

    App_coreStop(captObj_portA);
    App_coreStop(captObj_portB);

    Bsp_printf("Frames captured on PortA            : %d\n", gDqCount_portA);
    Bsp_printf("Frames captured on PortB            : %d\n", gDqCount_portB);
    Bsp_printf("Sub-frame interrupts recvd on PortA : %d\n",
               gNLinIntCount_s0portA);
    Bsp_printf("Sub-frame interrupts recvd on PortB : %d\n",
               gNLinIntCount_s0portB);

    gNLinIntCount_s0portA = 0;
    gNLinIntCount_s0portB = 0;
    gDqCount_portA        = 0;
    gDqCount_portB        = 0;

    /* De-Initialize & Close the VIP Core*/
    App_coreClose(captObj_portA);
    App_coreClose(captObj_portB);

    /* De-Initialize Frame buffer management and VPS library */
    App_FrameBufDeInit();
    Vps_deInit(NULL);

    return 0;
}

void vipCaptAppInit(void)
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

int32_t vipCaptModuleInit()
{
    int32_t retVal = STW_SOK;

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

