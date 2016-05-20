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
#include "soc_defines.h"
#include "platform.h"
#include "ov_sensorconfig.h"
#include "interrupt.h"
#include "soc.h"
#include "uartStdio.h"
#include "uartConsole.h"
#include <hw/hw_types.h>
#if (defined (TDA2XX_FAMILY_BUILD)) || (defined (TDA3XX_FAMILY_BUILD))
#include "irq_xbar.h"
#include <hw/hw_ctrl_core_pad_io.h>
#include "soc_defines.h"
#endif
#ifdef TI814X_FAMILY_BUILD
#include "soc_defines.h"
#endif
#include "soc.h"
#include <gpio_v2.h>
#include <common/stw_dataTypes.h>
#include <platform.h>
#include <common/stw_types.h>
#include "boards/stw_board.h"
#include "devices/stw_device.h"
#include "stwutils_app.h"

/***********************************************************************/
/*                    INTERNAL MACRO DEFINITION                        */
/***********************************************************************/

/* OV sensor decvice address*/
#define OV10630_ADDR                  (0x30)
#define BOARD_IO_EXP_I2C_ADDR_2       (0x26)

#ifdef BUILD_A8
#define I2C2_INT_NUM                  (30U)

#elif  (defined (BUILD_M3VPSS)) || (defined (BUILD_M4))
#define I2C2_INT_NUM                  (41U)

#elif defined (BUILD_DSP)
#define I2C2_INT_NUM                  (89U)

#elif defined (BUILD_A15)
#define I2C2_INT_NUM                  (57U)
#if defined (TDA2EX_BUILD)
#define I2C5_INT_NUM                  (60U)
#endif
#endif

#if (defined (BUILD_M4))
#define POLLED_MODE 1
#define INTERRUPT_MODE 0
#else
#define POLLED_MODE 0
#define INTERRUPT_MODE 1
#endif

#if INTERRUPT_MODE
#if defined (TDA2EX_BUILD)
#define MPU_XBAR_INSTANCE             (55U)
#else
#define MPU_XBAR_INSTANCE             (52U)
#endif
#endif

#if (defined (TDA2XX_BUILD)) || (defined (TDA3XX_FAMILY_BUILD))
#define HSI2C_INST HSI2C_INST_1
#elif (defined (TDA2EX_BUILD))
#define HSI2C_INST HSI2C_INST_4
#else
#define HSI2C_INST HSI2C_INST_2
#endif

#define XBAR_INT_LINE                 (4U)
#define XBAR_NUM                      (18U)

#define REG32(x)                        *((volatile unsigned int *) (x))
/*Todo : codecleanup to use starterware PAD MUX config instead of setPinmuxRegs
**/
#define PULLTYPESELECT_DOWN             (0x00U)
#define INPUTENABLE_OUT                 (0x00U)
#define DEFAULT                         (0xFF)

/* Video mux select for vision daughter card */
#define BOARD_GPIO_BASE_MUX_SEL             (SOC_GPIO4_BASE)
#define BOARD_GPIO_PIN_MUX1_SEL0            (13U)
#define BOARD_GPIO_PIN_MUX1_SEL1            (14U)
#define BOARD_GPIO_PIN_MUX2_SEL0            (15U)
#define BOARD_GPIO_PIN_MUX2_SEL1            (16U)
#define BOARD_GPIO_BASE_POWER_DWN           (SOC_GPIO6_BASE)
#define BOARD_GPIO_PIN_OV_PWDN              (17U)
#define BOARD_GPIO_BASE_DEMUX_FPD_A         ((UInt32) SOC_GPIO2_BASE)
#define BOARD_GPIO_BASE_DEMUX_FPD_B         ((UInt32) SOC_GPIO1_BASE)
#define BOARD_GPIO_BASE_DEMUX_FPD_C         ((UInt32) SOC_GPIO6_BASE)
#define BOARD_GPIO_PIN_DEMUX_FPD_A          ((UInt32) 29U)
#define BOARD_GPIO_PIN_DEMUX_FPD_B          ((UInt32) 4U)
#define BOARD_GPIO_PIN_DEMUX_FPD_C          ((UInt32) 7U)

#define BOARD_PCF8575_VIN2_S0               (0x04U)
#ifdef TDA2EX_BUILD
#define BOARD_PCF8575_VIN2_S2               (0x40U)
#else
#define BOARD_PCF8575_CAM_FPD_MUX_S0        (0x08U)
#endif

/**
 *  \name External Video Device ID.
 */

/** \brief OV10630 video sensor driver ID. */
#define VID_SENSOR_OV10630    0x0

/***********************************************************************/
/*                   INTERNAL VARIABLE DEFINITION                      */
/***********************************************************************/
LLD_hsi2cErrorCode_t txStatus;

volatile uint32_t    intStatus = 1;

/*******************************************************************************
**                   INTERNAL FUNCTION PROTOTYPE
*******************************************************************************/

uint32_t ovSensorConfig(hsI2cHandle i2cHandle);
Int32 Board_Tda2xxGPIOConfigure(hsI2cHandle i2cHandle, Int32 sensorDevID);
Int32 Board_Tda2xxInit(void);

void i2c_callback(hsI2cHandle i2cHandle, LLD_hsi2cErrorCode_t status,
                  void *appData);
Int32 Platform_Tda3xxInit();

#if (defined (TDA2XX_FAMILY_BUILD))
static Int32 setPinmuxRegs(UInt32 mode_index, UInt32 offset, UInt32 pupd_info)
{
    Int32 muxVal;

    if (offset != 0xffff)
    {
        muxVal =
            HW_RD_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + offset);
        muxVal &= ~(0x0FU);
        muxVal |= (mode_index & 0x0000000FU);

        if (pupd_info != DEFAULT)
        {
            muxVal &= ~(0x70000U);
            muxVal |= ((pupd_info & 0x07U) << 16U);
        }
        HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + offset, muxVal);
    }

    return 0;
}

#endif

#ifdef TDA3XX_FAMILY_BUILD
void sensorConfigAppInit(void)
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

void sensorConfigBoardMuxConfig(void)
{
    Int32 retVal;

    BOARDSelectDevice(DEVICE_ID_OV1063X, 0);

    retVal = BOARDSelectMode(DEVICE_ID_OV1063X, 0, BOARD_MODE_VIDEO_8BIT);
    if (retVal != STW_SOK)
    {
        printf("\n Board Select Mode Failed ");
    }
}

Int32 Platform_Tda3xxInit()
{
    Int32 retVal = STW_SOK;

    /* Unlock MMR_LOCK_2 For XBAR settings */
    *((volatile UInt32 *) 0x4A002544U) = (UInt32) 0xF757FDC0U;

    /* XBAR VIP1_IRQ1 to IPU1_27 */
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                   CPU_IPU1, XBAR_INST_IPU1_IRQ_27, VIP1_IRQ);

    /* XBAR DISPC_IRQ to IPU1_23 */
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                   CPU_IPU1, XBAR_INST_IPU1_IRQ_23, DISPC_IRQ);
    /* Lock MMR_LOCK_2 */
    *((volatile UInt32 *) 0x4A002544U) = (UInt32) 0xFDF45530U;

    return retVal;
}

#endif

#ifdef TDA2XX_FAMILY_BUILD
Int32 Platform_Tda2xxInit()
{
    int32_t retVal = 0;

    /* GPIO mux, OV_PWDN of vision board is connected to GPIO6_17
     * PAD=xref_clk0, PIN=gpio6_17 */
    setPinmuxRegs(14, CTRL_CORE_PAD_XREF_CLK0, DEFAULT);

    /* GPIO PIN MUX settings
     * PAD=vin2a_d12,PIN=gpio4_13
     * PAD=vin2a_d13,PIN=gpio4_14
     * PAD=vin2a_d14,PIN=gpio4_15
     * PAD=vin2a_d15,PIN=gpio4_16
     */
    setPinmuxRegs(
        14,
        CTRL_CORE_PAD_VIN2A_D12,
        (PULLUDENABLE_DISABLE | PULLTYPESELECT_DOWN | INPUTENABLE_OUT));
    setPinmuxRegs(
        14,
        CTRL_CORE_PAD_VIN2A_D13,
        (PULLUDENABLE_DISABLE | PULLTYPESELECT_DOWN | INPUTENABLE_OUT));
    setPinmuxRegs(
        14,
        CTRL_CORE_PAD_VIN2A_D14,
        (PULLUDENABLE_DISABLE | PULLTYPESELECT_DOWN | INPUTENABLE_OUT));
    setPinmuxRegs(
        14,
        CTRL_CORE_PAD_VIN2A_D15,
        (PULLUDENABLE_DISABLE | PULLTYPESELECT_DOWN | INPUTENABLE_OUT));

    /* PAD=mcasp2_axr6, PIN=gpio2_29
     * PAD=mcasp2_axr4, PIN=gpio1_4
     * PAD=mcasp2_axr5, PIN=gpio6_7 */
    setPinmuxRegs(
        14,
        (UInt32) CTRL_CORE_PAD_MCASP2_AXR6,
        (PULLUDENABLE_DISABLE | PULLTYPESELECT_DOWN | INPUTENABLE_OUT));
    setPinmuxRegs(
        14,
        (UInt32) CTRL_CORE_PAD_MCASP2_AXR4,
        (PULLUDENABLE_DISABLE | PULLTYPESELECT_DOWN | INPUTENABLE_OUT));
    setPinmuxRegs(
        14,
        (UInt32) CTRL_CORE_PAD_MCASP2_AXR5,
        (PULLUDENABLE_DISABLE | PULLTYPESELECT_DOWN | INPUTENABLE_OUT));

    /* I2C mux */
    setPinmuxRegs(0, CTRL_CORE_PAD_I2C1_SDA, DEFAULT);
    setPinmuxRegs(0, CTRL_CORE_PAD_I2C1_SCL, DEFAULT);
#ifdef TDA2EX_BUILD
    /* I2C5 mux */
    setPinmuxRegs(10, CTRL_CORE_PAD_MCASP1_AXR0, DEFAULT);
    setPinmuxRegs(10, CTRL_CORE_PAD_MCASP1_AXR1, DEFAULT);
#else
    setPinmuxRegs(0, CTRL_CORE_PAD_I2C2_SDA, DEFAULT);
    setPinmuxRegs(0, CTRL_CORE_PAD_I2C2_SCL, DEFAULT);
#endif

    /*
     * Cross bar setup
     */
    /* Unlock MMR_LOCK_2  */
    *((volatile UInt32 *) 0x4A002544U) = (UInt32) 0xF757FDC0;
    /* XBAR VIP1_IRQ1 to IPU1_27
     * XBAR VIP2_IRQ1 to IPU1_28 */
    *((volatile UInt32 *) 0x4A0027E8U) =
        ((UInt32) 352 << 16) | (UInt32) 351;
    /* XBAR VIP3_IRQ1 to IPU1_29
     * XBAR VPE1_IRQ1 to IPU1_30 */
    *((volatile UInt32 *) 0x4A0027ECU) =
        ((UInt32) 354 << 16) | (UInt32) 353;
    /* XBAR DISPC_IRQ at IPU1_23 */
    *((volatile UInt32 *) 0x4A0027E0U) = (UInt32) 20;
    /* XBAR HDMI_IRQ at IPU1_26 */
    *((volatile UInt32 *) 0x4A0027E4U) = ((UInt32) 96 << 16);
    /* XBAR I2C1_IRQ to IPU1_41
     * XBAR I2C2_IRQ to IPU1_42 */
    *((volatile UInt32 *) 0x4A002804U) =
        ((UInt32) 52 << 16) | (UInt32) 51;
    *((volatile UInt32 *) 0x4A002B94U) =
        ((UInt32) 132 << 16) | (UInt32) 133;

    return retVal;
}

#endif

int main()
{
    hsI2cHandle           i2cHandle;
    lld_hsi2c_initParam_t initPar;
    hsI2cObjHandle        i2cObjHandle;
    volatile uint8_t      done = 1U;

#if (INTERRUPT_MODE)

#ifdef BUILD_M3VPSS
    PlatformXBARIntMux(XBAR_INT_LINE, XBAR_NUM);
#endif

    Intc_Init();
    Intc_IntEnable(0);
#endif

#ifdef TDA2XX_FAMILY_BUILD
    Platform_Tda2xxInit();
    Board_Tda2xxInit();
    PlatformUART1SetPinMux();

#ifdef BUILD_A15

    PlatformUnlockMMR();

#if INTERRUPT_MODE
#ifdef TDA2EX_BUILD
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_MPUSS,
                   MPU_XBAR_INSTANCE,
                   I2C5_IRQ);
#else
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_MPUSS,
                   MPU_XBAR_INSTANCE,
                   I2C2_IRQ);
#endif
#endif
#endif
#endif

#if (defined (TDA2XX_FAMILY_BUILD)) || (defined (TI814X_FAMILY_BUILD))
    UART_Init(UART1_INST);
#endif

#ifdef TDA3XX_FAMILY_BUILD
    Platform_Tda3xxInit();
    sensorConfigAppInit();
#endif

    UARTprintf("\nSensor config start");

#ifdef TI814X_FAMILY_BUILD
    /*
     * Pad configuration has to be done in priviledge mode
     * or from gel file while running from a8
     */
    PlatformI2CSetPinMux();
    PlatformI2CClockEnable();
#endif
#ifdef BUILD_M4
    initPar.i2cIntNum = I2C2_INT_NUM;
#else
#ifdef TDA2EX_BUILD
    initPar.i2cIntNum = I2C5_INT_NUM;
#else
    initPar.i2cIntNum = I2C2_INT_NUM;
#endif
#endif
    initPar.i2cBusFreq = I2C_NORMAL;

#if INTERRUPT_MODE
    initPar.opMode = HSI2C_OPMODE_INTERRUPT;
#endif

#if POLLED_MODE
    initPar.opMode = HSI2C_OPMODE_POLLED;
#endif
    initPar.i2cOwnAddr   = 0;
    initPar.is10BitAddr  = 0;
    initPar.isMasterMode = 1;

    lld_i2c_init(&i2cObjHandle, HSI2C_INST, &initPar);

    i2cHandle = lld_i2c_open(HSI2C_INST, (lldHsi2cAppCallback) i2c_callback,
                             NULL);

    Intc_IntRegister(initPar.i2cIntNum, initPar.i2cIsr, i2cHandle);
    Intc_IntPrioritySet(initPar.i2cIntNum, 1, 0);
    Intc_SystemEnable(initPar.i2cIntNum);

    ovSensorConfig(i2cHandle);

    lld_i2c_close(&i2cHandle);

    lld_i2c_deinit(HSI2C_INST);

    UARTprintf("\nSensor config done");

    while (done) ;

    return 0;
}

void i2c_callback(hsI2cHandle i2cHandle, LLD_hsi2cErrorCode_t status,
                  void *appData)
{
    intStatus = 0;

    txStatus = status;

    if (LLD_HSI2C_SUCCESS == status)
    {
        /* printf("\n Error in sensor config");*/
    }
    else
    {
        /*printf("\nSensor config done");*/
    }
}

void sampleDelay(uint32_t delay)
{
    volatile uint32_t delay1 = delay;
    while (delay1--) ;
}

uint32_t ovSensorConfig(hsI2cHandle i2cHandle)
{
    uint32_t                   retVal = LLD_HSI2C_SUCCESS;
    volatile uint32_t          count;
    uint32_t                   sensorScriptSize;
    lld_hsi2c_datatfr_params_t i2cXferParams;
    uint16_t                   regAddr, regReadValHighBits, regReadValLowBits;
    uint8_t data[4];

#if (defined (TDA2XX_FAMILY_BUILD))
    Board_Tda2xxGPIOConfigure(i2cHandle, VID_SENSOR_OV10630);
#elif (defined (TDA3XX_FAMILY_BUILD))
    sensorConfigBoardMuxConfig();
#endif

    i2cXferParams.bufLen = 3;
    i2cXferParams.buffer = &data[0];
    i2cXferParams.flags  = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER |
                           LLD_HSI2C_START | LLD_HSI2C_STOP;
    i2cXferParams.slaveAddr = (uint8_t) OV10630_ADDR;
    i2cXferParams.timeout   = 4000;

    data[0] = 0x30;
    data[1] = 0x03;
    data[2] = 0x20;
    retVal  = lld_i2c_transfer(i2cHandle, &i2cXferParams);

#if (INTERRUPT_MODE)
    while (intStatus)
    {}
    intStatus = 1;

    if ((LLD_HSI2C_SUCCESS != retVal) || txStatus != LLD_HSI2C_SUCCESS)
    {
        UARTprintf("\nOV Reg writes failed");
    }
#else
    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTprintf("\nOV Reg writes failed");
    }
#endif

    regAddr = 0x3003;
    data[0] = (uint8_t) (regAddr >> 8);
    data[1] = (uint8_t) (regAddr);
    i2cXferParams.bufLen = 2;
    i2cXferParams.flags  = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER | LLD_HSI2C_START /*
                                                                                *|
                                                                                *LLD_HSI2C_STOP*/;
    retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

#if (INTERRUPT_MODE)
    while (intStatus)
    {}
    intStatus = 1;

    if ((LLD_HSI2C_SUCCESS != retVal) || txStatus != LLD_HSI2C_SUCCESS)
    {
        UARTprintf("\nOV Reg writes failed");
    }
#else
    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTprintf("\nOV Reg writes failed");
    }
#endif

    sampleDelay(1000);

    i2cXferParams.bufLen = 2;
    i2cXferParams.flags  = LLD_HSI2C_READ | LLD_HSI2C_MASTER |
                           LLD_HSI2C_START | LLD_HSI2C_STOP |
                           LLD_HSI2C_IGNORE_BUS_BUSY;
    retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

#if (INTERRUPT_MODE)
    while (intStatus)
    {}
    intStatus = 1;

    if ((LLD_HSI2C_SUCCESS != retVal) || txStatus != LLD_HSI2C_SUCCESS)
    {
        UARTprintf("\nOV Reg read failed\n");
    }
#else
    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTprintf("\nOV Reg read failed\n");
    }
#endif

    regReadValHighBits = data[0];
    regReadValLowBits  = data[1];
    UARTprintf("\nRegister %d value = %d", regAddr,
               (((regReadValHighBits <<
                  8) & 0xFF00) | (regReadValLowBits & 0xFF)));

    sensorScriptSize = sizeof (SensorConfigScript_OV) / (3 * sizeof (uint32_t));

    i2cXferParams.bufLen = 3;
    i2cXferParams.flags  = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER |
                           LLD_HSI2C_START | LLD_HSI2C_STOP;
    for (count = 0; count < sensorScriptSize; count++)
    {
        data[0] = (SensorConfigScript_OV[count][0] & 0xffff) >> 8;  /* MSB*/

        data[1] = (SensorConfigScript_OV[count][0] & 0xff);         /* LSB*/

        data[2] = (SensorConfigScript_OV[count][1] & 0xff);         /* value*/

        retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

        sampleDelay(1000);

#if (INTERRUPT_MODE)
        while (intStatus)
        {}
        intStatus = 1;

        if ((LLD_HSI2C_SUCCESS != retVal) || txStatus != LLD_HSI2C_SUCCESS)
        {
            UARTprintf("\nOV Reg writes failed");
        }
#else
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            UARTprintf("\nOV Reg writes failed");
        }
#endif
    }

    return retVal;
}

#ifdef TDA2XX_FAMILY_BUILD
Int32 Board_Tda2xxGPIOConfigure(hsI2cHandle i2cHandle, Int32 sensorDevID)
{
    lld_hsi2c_datatfr_params_t i2cXferParams;
    uint8_t data[4], retVal;

    if (sensorDevID == VID_SENSOR_OV10630)
    {
        /*
         * OV_PWDN is controlled by GP6[17]. 0 is ON, 1 is OFF
         */

        GPIOPinWrite(
            BOARD_GPIO_BASE_POWER_DWN,
            BOARD_GPIO_PIN_OV_PWDN,
            GPIO_PIN_LOW);

        i2cXferParams.bufLen = 2;
        i2cXferParams.buffer = &data[0];
        i2cXferParams.flags  = LLD_HSI2C_READ | LLD_HSI2C_MASTER |
                               LLD_HSI2C_START | LLD_HSI2C_STOP |
                               LLD_HSI2C_IGNORE_BUS_BUSY;
        i2cXferParams.slaveAddr = (uint8_t) BOARD_IO_EXP_I2C_ADDR_2;
        i2cXferParams.timeout   = 4000;
        retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

#if (INTERRUPT_MODE)
        while (intStatus)
        {}
        intStatus = 1;

        if ((LLD_HSI2C_SUCCESS != retVal) || txStatus != LLD_HSI2C_SUCCESS)
        {
            UARTprintf("\nReg Read failed");
        }
#else
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            UARTprintf("\nReg Read failed");
        }
#endif
        /* Configure board mux */
        i2cXferParams.bufLen = 2;
        i2cXferParams.buffer = &data[0];
        i2cXferParams.flags  = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER |
                               LLD_HSI2C_START | LLD_HSI2C_STOP;
        i2cXferParams.slaveAddr = (uint8_t) BOARD_IO_EXP_I2C_ADDR_2;
        i2cXferParams.timeout   = 4000;

#ifdef TDA2EX_BUILD
        data[0] |= (BOARD_PCF8575_VIN2_S2);
#else
        data[0] |= (BOARD_PCF8575_CAM_FPD_MUX_S0);
#endif
        data[0] &= ~((UInt8) (BOARD_PCF8575_VIN2_S0));;

        retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

#if (INTERRUPT_MODE)
        while (intStatus)
        {}
        intStatus = 1;

        if ((LLD_HSI2C_SUCCESS != retVal) || txStatus != LLD_HSI2C_SUCCESS)
        {
            UARTprintf("\nMux writes failed");
        }
#else
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            UARTprintf("\nMux writes failed");
        }
#endif
        /* By default set to 8-bit mode for all ports by setting
         * Demux_FPD_A,B,C to (1,0,1)  for OV*/
        GPIOPinWrite(
            BOARD_GPIO_BASE_DEMUX_FPD_A,
            BOARD_GPIO_PIN_DEMUX_FPD_A,
            GPIO_PIN_HIGH);
        GPIOPinWrite(
            BOARD_GPIO_BASE_DEMUX_FPD_B,
            BOARD_GPIO_PIN_DEMUX_FPD_B,
            GPIO_PIN_LOW);
        GPIOPinWrite(
            BOARD_GPIO_BASE_DEMUX_FPD_C,
            BOARD_GPIO_PIN_DEMUX_FPD_C,
            GPIO_PIN_HIGH);

        /*
         * Select CPLD mux to select between sensors/decoder in vision
         * daughter card
         *
         * MUX Signal mapping
         * ------------------
         * MUX1_SEL0 - GPIO4_13 (Mux mode 15, muxed with VIN2A_D12)
         * MUX1_SEL1 - GPIO4_14 (Mux mode 15, muxed with VIN2A_D13)
         * MUX2_SEL0 - GPIO4_15 (Mux mode 15, muxed with VIN2A_D14)
         * MUX2_SEL1 - GPIO4_16 (Mux mode 15, muxed with VIN2A_D15)
         *
         *                  MUX1_SEL0     MUX1_SEL1   MUX2_SEL0   MUX2_SEL1
         *                  -----------------------------------------------
         * OV Imager            1             0           1           0
         *
         */

        GPIOPinWrite(
            BOARD_GPIO_BASE_MUX_SEL,
            BOARD_GPIO_PIN_MUX1_SEL0,
            GPIO_PIN_HIGH);

        GPIOPinWrite(
            BOARD_GPIO_BASE_MUX_SEL,
            BOARD_GPIO_PIN_MUX1_SEL1,
            GPIO_PIN_LOW);

        GPIOPinWrite(
            BOARD_GPIO_BASE_MUX_SEL,
            BOARD_GPIO_PIN_MUX2_SEL0,
            GPIO_PIN_HIGH);

        GPIOPinWrite(
            BOARD_GPIO_BASE_MUX_SEL,
            BOARD_GPIO_PIN_MUX2_SEL1,
            GPIO_PIN_LOW);
    }

    return 0;
}

Int32 Board_Tda2xxInit(void)
{
    /* Enable GPIO required for video mux as output */
    GPIOModuleEnable(BOARD_GPIO_BASE_MUX_SEL);
    GPIOModuleEnable(BOARD_GPIO_BASE_POWER_DWN);
    GPIOModuleEnable(BOARD_GPIO_BASE_DEMUX_FPD_A);
    GPIOModuleEnable(BOARD_GPIO_BASE_DEMUX_FPD_B);
    GPIOModuleEnable(BOARD_GPIO_BASE_DEMUX_FPD_C);

    GPIODirModeSet(
        BOARD_GPIO_BASE_MUX_SEL,
        BOARD_GPIO_PIN_MUX1_SEL0,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_MUX_SEL,
        BOARD_GPIO_PIN_MUX1_SEL1,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_MUX_SEL,
        BOARD_GPIO_PIN_MUX2_SEL0,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_MUX_SEL,
        BOARD_GPIO_PIN_MUX2_SEL1,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_POWER_DWN,
        BOARD_GPIO_PIN_OV_PWDN,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_DEMUX_FPD_A,
        BOARD_GPIO_PIN_DEMUX_FPD_A,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_DEMUX_FPD_B,
        BOARD_GPIO_PIN_DEMUX_FPD_B,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_DEMUX_FPD_C,
        BOARD_GPIO_PIN_DEMUX_FPD_C,
        GPIO_DIR_OUTPUT);
    return 0;
}

#endif
