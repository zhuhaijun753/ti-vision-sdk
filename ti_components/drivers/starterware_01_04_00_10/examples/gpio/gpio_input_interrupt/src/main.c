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
#include "stdint.h"
#include "gpio_v2.h"
#include "string.h"
#include "hsi2c.h"
#include "soc.h"
#include "hw_ctrl_core_pad_io.h"
#include "soc_defines.h"
#include "uartConsole.h"
#include "uartStdio.h"
#include "platform.h"
#include "interrupt.h"
#include "hw_types.h"
#include "irq_xbar.h"

char     uartOutput[100];

#ifdef TDA2XX_FAMILY_BUILD
uint32_t gpio_base_address = SOC_GPIO1_BASE;
uint32_t gpio_pin          = 14;
uint32_t interrupt_num     = 29;
uint32_t xbar_cfg_required = 0;
#elif defined (TDA3XX_FAMILY_BUILD)
uint32_t gpio_base_address = SOC_GPIO4_BASE;
uint32_t gpio_pin          = 10;
uint32_t interrupt_num     = 51;
#define IRQ_XBAR_CFG_REQUIRED 1
#define IRQ_XBAR_CPU_ID CPU_IPU1
#define IRQ_XBAR_INST_NO XBAR_INST_IPU1_IRQ_51
#define IRQ_XBAR_INDEX GPIO4_IRQ_1
#endif

void gpioIsr(void *arg)
{
    volatile uint32_t gpio_pin_value = 0;

    /*Disable interrupt*/
    GPIOPinIntDisable(gpio_base_address, GPIO_INT_LINE_1, gpio_pin);

    /*Read pin*/
    gpio_pin_value = GPIOPinRead(gpio_base_address, gpio_pin);

    UARTPuts(uartOutput, -1);
    UARTPutHexNum((gpio_pin_value & (0x1U << gpio_pin)) >> gpio_pin);

    GPIOPinIntClear(gpio_base_address, GPIO_INT_LINE_1, gpio_pin);

    /*Enable interrupt interrupt*/
    GPIOPinIntEnable(gpio_base_address, GPIO_INT_LINE_1, gpio_pin);
}

void configurGpioInterrupt()
{
#if IRQ_XBAR_CFG_REQUIRED
    PlatformUnlockMMR();
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, IRQ_XBAR_CPU_ID,
                   IRQ_XBAR_INST_NO, IRQ_XBAR_INDEX);
#endif
    Intc_Init();
    Intc_IntEnable(0);

    Intc_IntRegister(interrupt_num, (IntrFuncPtr) gpioIsr, (void *) 0);
    Intc_IntPrioritySet(interrupt_num, 1, 0);
    Intc_SystemEnable(interrupt_num);
}

int main(void)
{
    volatile uint32_t waitForGpioInput = 1;
    char testType = 0;

    PlatformUartConsoleSetPinMux();

    UARTStdioInit();
    UARTPuts("\nGPIO Input interrupt App", -1);
    UARTPuts("\nGenerate interrupt based on input value on GPIO pin", -1);
#ifdef TDA2XX_FAMILY_BUILD
    UARTPuts("\nUse GPIO1 pin 14 on JP2 connector - pin 1 on EVM.", -1);
#elif defined (TDA3XX_FAMILY_BUILD)
    UARTPuts("\nUse GPIO4 pin 10 on J6108 connector - pin 2 on EVM", -1);
#endif
    UARTPuts("\nTo Drive the value on pin to LOW connect to ground", -1);
    UARTPuts("\nDefault value on the pin is High", -1);

    /* User Interface*/
    UARTPuts("\nEnter type of test", -1);
    UARTPuts("\n1. GPIO_INT_TYPE_LEVEL_LOW", -1);
    UARTPuts("\n2. GPIO_INT_TYPE_LEVEL_HIGH ", -1);
    UARTPuts("\n3. GPIO_INT_TYPE_FALL_EDGE", -1);
    UARTPuts("\n4. GPIO_INT_TYPE_RISE_EDGE ", -1);
    UARTPuts("\nEnter value(1, 2, 3 or 4) : ", -1);
    UARTGets(&testType, 1);

    /* Do GPIO pin mux */
    PlatformGPIOInputOutputSetPinMux();

    /*Configure interrupt controller*/
    configurGpioInterrupt();

    /*Enable GPIO clock */
    PlatformGPIOClockEnable();

    /*Reset GPIO*/
    GPIOModuleReset(gpio_base_address);

    /*Enable GPIO*/
    GPIOModuleEnable(gpio_base_address);

    /*Configure and enable debouncing feature*/
    GPIODebounceTimeConfig(gpio_base_address, 0xFF);

    GPIODebounceFuncControl(gpio_base_address, gpio_pin,
                            GPIO_DEBOUNCE_FUNC_ENABLE);

    if ('1' == testType)
    {
        GPIOIntTypeSet(gpio_base_address, gpio_pin,
                       GPIO_INT_TYPE_LEVEL_LOW);
        strcpy(uartOutput, "\nGPIO: Low  Level detected. Pin value = ");
    }
    else if ('2' == testType)
    {
        GPIOIntTypeSet(gpio_base_address, gpio_pin,
                       GPIO_INT_TYPE_LEVEL_HIGH);
        strcpy(uartOutput, "\nGPIO: Default High Level detected. Pin value = ");
    }
    else if ('3' == testType)
    {
        GPIOIntTypeSet(gpio_base_address, gpio_pin,
                       GPIO_INT_TYPE_FALL_EDGE);
        strcpy(uartOutput, "\nGPIO: Falling edge detected. Pin value = ");
    }
    else
    {
        GPIOIntTypeSet(gpio_base_address, gpio_pin,
                       GPIO_INT_TYPE_RISE_EDGE);
        strcpy(uartOutput, "\nGPIO: Rising edge detected. Pin value = ");
    }

    /* Set pin direction as input*/
    GPIODirModeSet(gpio_base_address, gpio_pin, GPIO_DIR_INPUT);

    /*Clear interrupt*/
    GPIOPinIntDisable(gpio_base_address, GPIO_INT_LINE_1, gpio_pin);
    GPIOPinIntClear(gpio_base_address, GPIO_INT_LINE_1, gpio_pin);

    /*Enable interrupt*/
    GPIOPinIntEnable(gpio_base_address, GPIO_INT_LINE_1, gpio_pin);

    while (waitForGpioInput)
    {
        /*Keep while busy*/
        waitForGpioInput++;
        waitForGpioInput--;
    }
    return 0;
}

