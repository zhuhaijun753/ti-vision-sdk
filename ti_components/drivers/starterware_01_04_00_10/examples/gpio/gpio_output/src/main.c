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
#include "hsi2c.h"
#include "soc.h"
#include "hw_types.h"
#include "hw_ctrl_core_pad.h"
#include "hw_ctrl_core_pad_io.h"
#include "soc_defines.h"
#include "uartConsole.h"
#include "uartStdio.h"
#include "platform.h"

uint32_t gPinDirection = GPIO_DIR_OUTPUT;

#ifdef TDA2XX_FAMILY_BUILD
uint32_t gpio_base_address = SOC_GPIO1_BASE;
uint32_t gpio_pin          = 14;
#elif defined (TDA3XX_FAMILY_BUILD)
uint32_t gpio_base_address = SOC_GPIO4_BASE;
uint32_t gpio_pin          = 9;
#endif

void delay(void)
{
    volatile uint32_t i;
    for (i = 0; i < 200; i++) ;
}

int main(void)
{
    volatile uint32_t checkOutput = 1;

    PlatformUartConsoleSetPinMux();

    UARTStdioInit();
    UARTPuts("\nGPIO Output App", -1);
    UARTPuts("\nGenerating a square wave on GPIO pin", -1);
#ifdef TDA2XX_FAMILY_BUILD
    UARTPuts("\nProbe the GPIO1 pin 14 on JP2 connector - pin 1 on EVM", -1);
#elif defined (TDA3XX_FAMILY_BUILD)
    UARTPuts("\nProbe the GPIO4 pin 9 on J6108 connector - pin 1 on EVM", -1);
#endif

    /* Do GPIO pin mux */
    PlatformGPIOInputOutputSetPinMux();

    /*Enable GPIO clock */
    PlatformGPIOClockEnable();

    GPIOModuleReset(gpio_base_address);

    GPIOModuleEnable(gpio_base_address);

    GPIODirModeSet(gpio_base_address, gpio_pin, gPinDirection);

    while (checkOutput)
    {
        GPIOPinWrite(gpio_base_address, gpio_pin, GPIO_PIN_HIGH);
        delay();

        GPIOPinWrite(gpio_base_address, gpio_pin, GPIO_PIN_LOW);
        delay();
    }

    return 0;
}
