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
/**
 * \file   uartConfig.c
 *
 * \brief  This file contains functions which interface interactively
 *         with the user through the serial console to perform some
 *         utility operations.
 */

#include "stdint.h"
#include "uartConfig.h"
#include <stdarg.h>
#include "soc.h"

/*****************************************************************************
**                    FUNCTION DEFINITIONS
*****************************************************************************/

/**
 * \brief   This function initializes the specified UART instance for use for
 *          console operations.
 *
 * \param   baseAddr    Base Address of UART instance.
 *
 * \return  None.
 *
 */

void UARTConfigInit(uint32_t baseAddr, uint32_t baudRate, uint32_t wordLength,
                    uint32_t stopBit, uint32_t parity, uint32_t mode)
{
    uint32_t divisorValue = 0, fifoConfig = 0;

    /* Performing a module reset. */
    UARTModuleReset(baseAddr);

    /* Performing FIFO configurations. */
    /*
    ** - Transmit Trigger Level Granularity is 4
    ** - Receiver Trigger Level Granularity is 1
    ** - Transmit FIFO Space Setting is 56. Hence TX Trigger level
    **   is 8 (64 - 56). The TX FIFO size is 64 bytes.
    ** - The Receiver Trigger Level is 1.
    ** - Clear the Transmit FIFO.
    ** - Clear the Receiver FIFO.
    ** - DMA Mode enabling shall happen through SCR register.
    ** - DMA Mode 0 is enabled. DMA Mode 0 corresponds to No
    **   DMA Mode. Effectively DMA Mode is disabled.
    */
    fifoConfig = UART_FIFO_CONFIG(UART_TRIG_LVL_GRANULARITY_4,
                                  UART_TRIG_LVL_GRANULARITY_1,
                                  UART_FCR_TX_TRIG_LVL_56,
                                  1,
                                  1,
                                  1,
                                  UART_DMA_EN_PATH_SCR,
                                  UART_DMA_MODE_0_ENABLE);

    /* Configuring the FIFO settings. */
    UARTFIFOConfig(baseAddr, fifoConfig);

    /* Performing Baud Rate settings. */
    /* Computing the Divisor Value. */
    divisorValue = UARTDivisorValCompute(UART_MODULE_INPUT_CLK,
                                         baudRate,
                                         mode,
                                         UART_MIR_OVERSAMPLING_RATE_42);
    /* Programming the Divisor Latches. */
    UARTDivisorLatchWrite(baseAddr, divisorValue);

    /* Switching to Configuration Mode B. */
    UARTRegConfigModeEnable(baseAddr, UART_REG_CONFIG_MODE_B);

    /* Programming the Line Characteristics. */
    UARTLineCharacConfig(baseAddr, (wordLength | stopBit), parity);

    /* Disabling write access to Divisor Latches. */
    UARTDivisorLatchDisable(baseAddr);

    /* Disabling Break Control. */
    UARTBreakCtl(baseAddr, UART_BREAK_COND_DISABLE);

    /* Uart enable */
    UARTOperatingModeSelect(baseAddr, mode);
}

/**
 * \brief   This function writes a byte on the serial console.
 *
 * \param   baseAddr    Base Address of UART instance.
 * \param   byteTx      The byte to be transmitted.
 *
 * \return  None.
 */

void UARTConfigPutc(uint32_t baseAddr, uint8_t byteTx)
{
    UARTCharPut(baseAddr, byteTx);
}

/**
 * \brief   This function reads a byte entered on the serial console.
 *
 * \param   baseAddr    Base Address of UART instance.
 *
 * \return  Returns the entered byte typecasted as an unsigned character.
 */

uint8_t UARTConfigGetc(uint32_t baseAddr)
{
    return UARTCharGet(baseAddr);
}

/**
 * \brief  This function writes data from a specified buffer onto the
 *         transmitter FIFO of UART.
 *
 * \param  baseAddr         Base Address of UART instance.
 * \param  pTxBuffer        Pointer to a buffer in the transmitter.
 * \param  numBytesToWrite  Number of bytes to be transmitted to the
 *                          transmitter FIFO. The user has the freedom to not
 *                          specify any valid value for this if he wants to
 *                          print until the occurence of a NULL character.
 *                          In this case, he has to pass a negative value as
 *                          this parameter.
 *
 * \return  Number of bytes written to the transmitter FIFO.
 *
 * \note   1> Whenever a null character(\0) is encountered in the
 *            data to be transmitted, the transmission is stopped. \n
 *         2> Whenever the transmitter data has a new line character(\n),
 *            it is interpreted as a new line(\n) + carraige return(\r)
 *            characters. This is because the serial console interprets a
 *            new line character as it is and does not introduce a carraige
 *            return. \n
 *
 *         Some example function calls of this function are: \n
 *
 *         UARTPuts(txArray, -2): This shall print the contents of txArray[]
 *         until the occurence of a NULL character. \n
 *
 *         UARTPuts("Hello World", 8): This shall print the first 8 characters
 *         of the string shown. \n
 *
 *         UARTPuts("Hello World", 20): This shall print the string shown until
 *         the occurence of the NULL character. Here, the NULL character is
 *         encountered earlier than the length of 20 bytes.\n
 *
 */
uint32_t UARTConfigPuts(uint32_t baseAddr, char *pTxBuffer,
                        int32_t numBytesToWrite)
{
    uint32_t count = 0;
    uint32_t flag  = 0;

    if (numBytesToWrite < 0)
    {
        flag = 1;
    }

    while ('\0' != *pTxBuffer)
    {
        /* Checks if data is a newline character. */
        if ('\n' == *pTxBuffer)
        {
            /* Ensuring applicability to serial console.*/
            UARTConfigPutc(baseAddr, '\r');
            UARTConfigPutc(baseAddr, '\n');
        }
        else
        {
            UARTConfigPutc(baseAddr, (uint8_t) *pTxBuffer);
        }
        pTxBuffer++;
        count++;
        if ((0 == flag) && (count == numBytesToWrite))
        {
            break;
        }
    }
    /* Returns the number of bytes written onto the transmitter FIFO. */
    return count;
}

/**
 * \brief  This function reads data from the receiver FIFO to a buffer
 *         in the receiver.
 *
 * \param  baseAddr         Base Address of UART instance.
 * \param  pRxBuffer        Pointer to a buffer in the receiver.
 * \param  numBytesToRead   The number of bytes the receiver buffer can hold.
 *                          However, if the user wishes not to specify this
 *                          parameter, he has freedom to do so. In that case,
 *                          the user has to pass a negative value for this
 *                          parameter.
 *
 * \return  Number of bytes read from the receiver FIFO.
 *
 * \note   The two exit points for this function are:
 *         1> To enter an ESC character or a carraige return character('Enter'
 *            key on the Keyboard).\n
 *         2> Specify a limit to the number of bytes to be read. \n
 *
 *         Some example function calls of this function are:
 *
 *         UARTGets(rxBuffer, -2): This reads characters from
 *         the receiver FIFO of UART until the occurence of a carriage return
 *         ('Enter' key on the keyboard pressed) or an ESC character.
 *
 *         UARTGets(rxBuffer, 12): This reads characters until
 *         12 characters have been read or until an occurence of a carriage
 *         return or an ESC character, whichever occurs first.
 */

uint32_t UARTConfigGets(uint32_t baseAddr, char *pRxBuffer,
                        int32_t numBytesToRead)
{
    int32_t  count = 0;
    uint32_t flag  = 0;

    if (numBytesToRead < 0)
    {
        flag = 1;
    }
    do
    {
        *pRxBuffer = (char) UARTConfigGetc(baseAddr);

        /*
        ** 0xD - ASCII value of Carriage Return.
        ** 0x1B - ASCII value of ESC character.
        */
        if (0xD == *pRxBuffer || 0x1B == *pRxBuffer)
        {
            *pRxBuffer = '\0';
            break;
        }

        /* Echoing the typed character back to the serial console. */
        UARTConfigPutc(baseAddr, (uint8_t) *pRxBuffer);
        pRxBuffer++;
        count++;
        if (0 == flag && (count == numBytesToRead))
        {
            break;
        }
    } while (1);

    return count;
}

/**
 *  \brief   This function prints the specified numbers(positive or negative)
 *           on the serial console.
 *
 *  \param   baseAddr   Base Address of UART instance.
 *  \param   value      The number to be printed on the serial console.
 *
 *  \return  None.
 *
 *  \note    The numbers that this function can print should lie in the
 *           following range:
 *           [-2^(31)] to [2^(31) - 1] i.e.
 *           0x80000000 to  0x7FFFFFFF
 *
 */

void UARTConfigPutNum(uint32_t baseAddr, int32_t value)
{
    char     num[10]  = {0};
    uint32_t quotient = 0;
    uint32_t dividend = 0;
    int32_t  count    = 0;

    if (value < 0)
    {
        UARTConfigPutc(baseAddr, '-');
        /*
        ** Making the negative number as positive.
        ** This is done to simplify further processing and printing.
        */
        value = -value;
    }

    dividend = value;
    do
    {
        quotient   = dividend / 10;
        num[count] = (uint8_t) (dividend % 10);
        if (0 == quotient)
        {
            break;
        }
        count++;
        dividend = quotient;
    } while (count < 10);

    if(0 < count)
    {
        count--;
    }
    /* Printing the digits. */
    do
    {
        /* We add 0x30 to a digit to obtain its respective ASCII value.*/
        UARTConfigPutc(baseAddr, num[count--] + 0x30);
    } while (count >= 0);
}

/**
 * \brief   This function reads the numbers typed on the serial console.
 *
 * \param   baseAddr    Base Address of UART instance.
 * \return  The value entered on the serial console.
 *
 * \note   The numbers that this function can recieve should lie in the
 *          following range:
 *          [-2^(31)] to [2^(31) - 1] i.e.
 *          0x80000000 to  0x7FFFFFFF
 *
 */

int32_t UARTConfigGetNum(uint32_t baseAddr)
{
    char    rxByte;
    int32_t sign  = 1;
    int32_t value = 0;

    rxByte = (char) UARTConfigGetc(baseAddr);

    /* Accounting for negative numbers.*/
    if ('-' == rxByte)
    {
        UARTConfigPutc(baseAddr, '-');
        sign = -1;
    }
    else
    {
        UARTConfigPutc(baseAddr, (uint8_t) rxByte);
        value = value * 10 + (rxByte - 0x30);
    }

    do
    {
        rxByte = (char) UARTConfigGetc(baseAddr);

        /* Echoing the typed characters to the serial console.*/
        UARTConfigPutc(baseAddr, (uint8_t) rxByte);
        /*
        ** Checking if the entered character is a carriage return.
        ** Pressing the 'Enter' key on the keyboard executes a
        ** carriage return on the serial console.
        */
        if ('\r' == rxByte)
        {
            break;
        }
        /*
        ** Subtracting 0x30 to convert the representation of the digit
        ** from ASCII to hexadecimal.
        */
        value = value * 10 + (rxByte - 0x30);
    } while (1);

    /* Accounting for the sign of the number.*/
    value = value * sign;

    return value;
}

/**
 * \brief  This function is used to print hexadecimal numbers on the serial
 *         console.
 *
 * \param  baseAddr   Base Address of UART instance.
 * \param  hexValue   The Hexadecimal number to be printed.
 *
 * \return None
 */

void UARTConfigPutHexNum(uint32_t baseAddr, uint32_t hexValue)
{
    uint8_t  num[8]   = {0};
    uint32_t quotient = 0;
    uint32_t dividend = 0;
    int32_t  count    = 0;

    dividend = hexValue;

    do
    {
        quotient   = dividend / 16;
        num[count] = (uint8_t) (dividend % 16);
        if (0 == quotient)
        {
            break;
        }
        count++;
        dividend = quotient;
    } while (count < 8);

    count--;
    UARTConfigPutc(baseAddr, '0');
    UARTConfigPutc(baseAddr, 'x');

    while (count >= 0)
    {
        /* Checking for alphanumeric numbers. */
        if ((16 - num[count]) <= 6)
        {
            /* Printing alphanumeric numbers. */
            UARTConfigPutc(baseAddr, num[count--] + 0x37);
        }
        else
        {
            /* Printing numbers in the range 0 to 9. */
            UARTConfigPutc(baseAddr, num[count--] + 0x30);
        }
    }
}

/**
 * \brief   This function receives hexadecimal numbers entered on the serial
 *          console of the host machine.
 *
 * \param   None
 *
 * \return  The hexadecimal number entered on the serial console of the host
 *          machine.
 *
 * \note    1> The points below explain the ways of entering hexadecimal
 *             numbers:\n
 *             - 0xABCDEF12 - Hexadecimal number preceded by a '0x'.\n
 *             - 0XABCDEF12 - Hexadecimal number preceded by a '0X'.\n
 *             - 0xabcdef12 - Lower-case alphanumeric numbers are allowed.\n
 *             - 0xaBcDeF12 - Intermixing of lower-case and upper-case
 *                            alphanumeric numbers is allowed.\n
 *             - abcdef12   - A preceding '0x' or '0X' is not requried.
 *                            The entered number shall be treated as a
 *                            hexadecimal number.\n
 *             - 12345678   - Interpreted as 0x12345678 and not decimal
 *                            12345678.\n
 *             - xABCDEF12  - A preceding '0' is not required.\n
 *          2> This function does not take into consideration any character
 *             other than a hexadecimal character after reception.\n
 *             Example: Characters in the range G,H,I,...Z or g,h,...,z
 *             are not taken into consideration.\n
 *          3> The maximum value that can be returned by this function
 *             is 0xFFFFFFFF. The reception exits after eight characters have
 *             been received.\n
 *          4> To input a  number lesser that eight characters (Ex: 0x1AB),
 *             press the 'Enter' key after entering the number.\n
 */

uint32_t UARTConfigGetHexNum(uint32_t baseAddr)
{
    char     rxByte;
    uint32_t value = 0;
    uint32_t loopIndex;
    uint32_t byteCount = 0;

    for (loopIndex = 0; loopIndex < 2; loopIndex++)
    {
        /* Receiving bytes from the host machine through serial console. */
        rxByte = (char) UARTConfigGetc(baseAddr);

        /*
        ** Checking if the entered character is a carriage return.
        ** Pressing the 'Enter' key on the keyboard executes a
        ** carriage return on the serial console.
        */
        if ('\r' == rxByte)
        {
            break;
        }

        /*
        ** Checking if the character entered is one among the alphanumeric
        ** character set A,B,C...F
        */
        if (('A' <= rxByte) && (rxByte <= 'F'))
        {
            /* Echoing the typed characters to the serial console.*/
            UARTConfigPutc(baseAddr, (uint8_t) rxByte);
            value = value * 16 + (rxByte - 0x37);
            byteCount++;
        }
        /*
        ** Checking if the character entered is one among the alphanumeric
        ** character set a,b,c...f
        */
        else if (('a' <= rxByte) && (rxByte <= 'f'))
        {
            UARTConfigPutc(baseAddr, (uint8_t) rxByte);
            value = value * 16 + (rxByte - 0x57);
            byteCount++;
        }
        /*
        ** Checking if the character entered is one among the decimal
        ** number set 0,1,2,3,....9
        */
        else if (('0' <= rxByte) && (rxByte <= '9'))
        {
            UARTConfigPutc(baseAddr, (uint8_t) rxByte);
            value = value * 16 + (rxByte - 0x30);
            byteCount++;
        }
        /*
        ** Checking if the character is either a 'x'(lower-case) or an 'X'
        ** (upper-case).
        */
        else if (('x' == rxByte) || ('X' == rxByte))
        {
            UARTConfigPutc(baseAddr, (uint8_t) rxByte);
            value = 0;
            break;
        }
    }

    if (0 == value)
    {
        byteCount = 0;
    }

    do
    {
        rxByte = (char) UARTConfigGetc(baseAddr);

        if ('\r' == rxByte)
        {
            break;
        }

        /*
        ** Checking if the character entered is one among the alphanumeric
        ** character set A,B,C...F
        */
        if (('A' <= rxByte) && (rxByte <= 'F'))
        {
            UARTConfigPutc(baseAddr, (uint8_t) rxByte);
            value = value * 16 + (rxByte - 0x37);
            byteCount++;
        }
        /*
        ** Checking if the character entered is one among the alphanumeric
        ** character set a,b,c...f
        */
        else if (('a' <= rxByte) && (rxByte <= 'f'))
        {
            UARTConfigPutc(baseAddr, (uint8_t) rxByte);
            value = value * 16 + (rxByte - 0x57);
            byteCount++;
        }
        /*
        ** Checking if the character entered is one among the decimal
        ** number set 0,1,2,3,....9
        */
        else if (('0' <= rxByte) && (rxByte <= '9'))
        {
            UARTConfigPutc(baseAddr, (uint8_t) rxByte);
            value = value * 16 + (rxByte - 0x30);
            byteCount++;
        }
        /*
        ** Not receiving any other character other than the one belonging
        ** to the above three categories.
        */
        else
        {
            /* Intentionally left empty. */
        }
    } while (byteCount < 8);

    return value;
}

/******************************* End of file *********************************/
