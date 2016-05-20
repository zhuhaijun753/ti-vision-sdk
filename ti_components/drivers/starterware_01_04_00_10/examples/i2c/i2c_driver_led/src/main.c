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
#include "hsi2c.h"
#include "soc_defines.h"
#include "platform.h"
#include "soc.h"

/***********************************************************************/
/*                    INTERNAL MACRO DEFINITION                        */
/***********************************************************************/
#if defined (TDA3XX_FAMILY_BUILD)
/* I2C address of TCA6424 expander - 2. */
#define HSI2C_SLAVE_ADDR            ((uint8_t) 0x22U)
#else
/* I2C address of PCF8575 expander. */
#define HSI2C_SLAVE_ADDR            ((uint8_t) 0x20U)
#endif

/* Turn on the LEDs. */
#define HSI2C_EXP_PORT0_LED_ON      ((uint8_t) 0x00U)

/* Turn off the LEDs. */
#define HSI2C_EXP_PORT0_LED_OFF     ((uint8_t) 0xFU)

/* Number of times led toggles. */
#define HSI2C_LED_TOGGLE_NO         (10U)

/* Led toggle check value*/
#define HSI2C_LED_TOGGLE_END        (0U)

/* Transfer Size */
#define HSI2C_TRANSFER_SIZE         (5U)

#if defined (TDA3XX_FAMILY_BUILD)
#define TCA6424_CMD_AUTO_INC            ((uint8_t) 0x80U)

/* Output register to change state of output BIT set to 1, output set HIGH */
#define TCA6424_REG_OUTPUT0             ((uint8_t) 0x04U)
#define TCA6424_REG_OUTPUT1             ((uint8_t) 0x05U)
#define TCA6424_REG_OUTPUT2             ((uint8_t) 0x06U)

/* Configuration register. BIT = '1' sets port to input, BIT = '0' sets
 * port to output */
#define TCA6424_REG_CONFIG0             ((uint8_t) 0x0CU)
#define TCA6424_REG_CONFIG1             ((uint8_t) 0x0DU)
#define TCA6424_REG_CONFIG2             ((uint8_t) 0x0EU)

#endif

/***********************************************************************/
/*                   INTERNAL VARIABLE DEFINITION                      */
/***********************************************************************/
uint8_t dataToSlave[HSI2C_TRANSFER_SIZE];

/*******************************************************************************
**                   INTERNAL FUNCTION PROTOTYPE
*******************************************************************************/
void SetupI2C(void);
void sampleDelay(int32_t delay);
void SetupI2CTransmit(uint8_t *data, uint32_t numBytes);
static void ioexpDataWrite(uint8_t *data);
static void initialize_ioexp(void);

int main()
{
    volatile uint8_t done = 1;
    uint8_t          data;
    /*
    ** Configures I2C to Master mode to generate start codition
    ** on I2C bus and to transmit data at a bus speed of  100khz
    */

    uint32_t         num;

    SetupI2C();

    initialize_ioexp();

    for (num = HSI2C_LED_TOGGLE_NO; num != HSI2C_LED_TOGGLE_END; num--)
    {
        data = HSI2C_EXP_PORT0_LED_ON;
        /*
         * **Transmits command byte and data to I/0 expander
         * **through I2C bus
         */
        ioexpDataWrite(&data);
        sampleDelay(0xFFF);

        data = HSI2C_EXP_PORT0_LED_OFF; /*data to OFF LED*/
        ioexpDataWrite(&data);
        sampleDelay(0xFFF);
    }

    while (done) ;

    return 0;
}

static void initialize_ioexp(void)
{
#if defined (TDA3XX_FAMILY_BUILD)
    /* TCA6424 ioexpander pins should be configure as output
     * In config register write 1 for input, 0 for output */
    dataToSlave[0] = TCA6424_REG_CONFIG0 | TCA6424_CMD_AUTO_INC;
    dataToSlave[1] = 0x0U;
    SetupI2CTransmit(&dataToSlave[0], 2);
#endif
}

#if defined (TDA3XX_FAMILY_BUILD)
/* On tda3xx leds are connected on TCA6424 ioexpander - 2
 * LEDs are connected on port 0 first 4 bits, and ioexpander has 3 ports */
static void ioexpDataWrite(uint8_t *data)
{
    dataToSlave[0] = TCA6424_REG_OUTPUT0 | (uint32_t) TCA6424_CMD_AUTO_INC;
    dataToSlave[1] = ((*data) & 0x0FU);
    dataToSlave[2] = 0U;
    dataToSlave[3] = 0U;
    SetupI2CTransmit(&dataToSlave[0], 4);
}

#else
/* On tda2xx and ti814x leds are connected on PCF8575 ioexpander
 * LEDs are connected on port 0 last 4 bits, and ioexpander has 2 ports */
static void ioexpDataWrite(uint8_t *data)
{
    dataToSlave[0] = (((*data) << 4U) & 0xF0U);
    dataToSlave[1] = 0U;
    SetupI2CTransmit(&dataToSlave[0], 2);
}

#endif

void SetupI2C(void)
{
#ifdef TI814X_FAMILY_BUILD
    /*Pad Mux need to be configured in Supervisor mode*/
    PlatformI2CSetPinMux();
    PlatformI2CClockEnable();
#endif
    /* Do a software reset */
    I2CSoftReset(SOC_I2C1_BASE);

    /* Enable i2c module */
    I2CMasterEnable(SOC_I2C1_BASE);

    while (!I2CSystemStatusGet(SOC_I2C1_BASE)) ;

    /* Put i2c in reset/disabled state */
    I2CMasterDisable(SOC_I2C1_BASE);

    /* Configure i2c bus speed to 100khz */
    I2CMasterInitExpClk(SOC_I2C1_BASE, 24000000,
                        8000000, 100000);

    I2COwnAddressSet(SOC_I2C1_BASE, 0,
                     I2C_OWN_ADDR_0);

    I2CSyscInit(SOC_I2C1_BASE, 0x08);

    /*Set Rx and Tx FIFO threshold value and reset the fifo*/
    I2CFIFOThresholdConfig(SOC_I2C1_BASE, 0, I2C_TX_MODE);

    I2CFIFOThresholdConfig(SOC_I2C1_BASE, 0, I2C_RX_MODE);

    /* Set i2c slave address */
    I2CMasterSlaveAddrSet(SOC_I2C1_BASE, HSI2C_SLAVE_ADDR);

    /* Bring i2c out of reset */
    I2CMasterEnable(SOC_I2C1_BASE);

    /* Enable free run mode */
    I2CMasterEnableFreeRun(SOC_I2C1_BASE);
}

void SetupI2CTransmit(uint8_t *data, uint32_t numBytes)
{
    uint32_t i;

    /* Set data count */
    I2CSetDataCount(SOC_I2C1_BASE, numBytes);

    /*
    ** Configure i2c as master-transmitter and to generate stop condition
    */
    I2CMasterControl(SOC_I2C1_BASE,
                     I2C_CFG_MST_TX | I2C_CON_STP_STP | I2C_CFG_START);

    for (i = 0; i < numBytes; i++)
    {
        /*Wait for transmit interrupt to occur*/
        while (I2CMasterIntRawStatusEx(SOC_I2C1_BASE,
                                       I2C_INT_TRANSMIT_READY) != 0x10) ;

        /*Disable transmit ready and stop condition interrupt*/
        I2CMasterIntClearEx(SOC_I2C1_BASE,
                            I2C_INT_TRANSMIT_READY | I2C_INT_STOP_CONDITION);

        /* Send the data */
        I2CMasterDataPut(SOC_I2C1_BASE, data[i]);
    }

    sampleDelay(50);

    I2CFlushFifo(SOC_I2C1_BASE);

    /*Clear all interrupt status*/
    I2CMasterIntClearEx(SOC_I2C1_BASE, I2C_INT_ALL);

    /*Clear data buffer length*/
    I2CSetDataCount(SOC_I2C1_BASE, 0);
}

void sampleDelay(int32_t delay)
{
    volatile int32_t i, j;

    for (i = 0; i < delay; i++)
    {
        for (j = 0; j < 100; j++) ;
    }
}

