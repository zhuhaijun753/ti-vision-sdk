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
#include <stdio.h>
#include "uartStdio.h"
#include "stdint.h"
#include <common/stw_types.h>
#include <common/stw_dataTypes.h>
#include "debug.h"
#include "nor.h"

/* Debug print function For A15 use UART For M4 use stdio */
uint32_t DEBUG_printString(const char *s)
{
    if (gNor_InitPrms.norFlashInitPrintFxnPtr != NULL)
    {
        gNor_InitPrms.norFlashInitPrintFxnPtr(s);
    }
    return SUCCESS;
}

void DEBUG_ConvertHexToString(uint32_t hexValue, char *stringValue,
                              int32_t maxLimitCount)
{
    uint32_t quotient = 0;
    uint32_t dividend = 0;
    /* Count starts from two because of '0x' */
    int32_t  count         = 0, tmpCount = 0;
    char     tmpString[10] = {0};

    dividend           = hexValue;
    stringValue[count] = (char) '0';
    count++;
    stringValue[count] = (char) 'x';
    count++;
    do
    {
        quotient = dividend / 16U;
        tmpString[tmpCount] = (char) (dividend % 16U);
        if (0U == quotient)
        {
            break;
        }
        tmpCount++;
        dividend = quotient;
    } while (tmpCount < maxLimitCount);

    /* If we exceed limit, reduce and print from actual digits */
    if (tmpCount == maxLimitCount)
    {
        tmpCount--;
    }
    while (tmpCount >= 0)
    {
        /* Checking for alphanumeric numbers. */
        if ((16 - tmpString[tmpCount]) <= 6)
        {
            /* Alphanumeric numbers. */
            stringValue[count] = tmpString[tmpCount] + 0x37U;
            tmpCount--;
            count++;
        }
        else
        {
            /* Numbers in the range 0 to 9. */
            stringValue[count] = tmpString[tmpCount] + 0x30U;
            tmpCount--;
            count++;
        }
    }
}

