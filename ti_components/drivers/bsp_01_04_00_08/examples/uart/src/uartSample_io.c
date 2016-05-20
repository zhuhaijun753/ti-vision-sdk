/******************************************************************************
 *                                                                            *
 * Copyright (c) 2012 Texas Instruments Incorporated - http://www.ti.com/     *
 *                                                                            *
 * All rights reserved. Property of Texas Instruments Incorporated.           *
 * Restricted rights to use, duplicate or disclose this code are              *
 * granted through contract.                                                  *
 *                                                                            *
 * The program may not be used without the written permission                 *
 * of Texas Instruments Incorporated or against the terms and conditions      *
 * stipulated in the agreement under which this program has been              *
 * supplied.                                                                  *
 *                                                                            *
 *****************************************************************************/

/**
 * \file      uartSample_io.c
 *
 * \brief     This file contains the test / demo code to demonstrate the
 *            UART driver implemented for SYS/BIOS 6.
 *
 *            (C) Copyright 2010, Texas Instruments, Inc
 *
 * \author    PSG
 *
 * \version   0.1  Created for DM814x/C6A811x platform.
 *
 */

/* ========================================================================== */
/*                              INCLUDE FILES                                 */
/* ========================================================================== */
#include <xdc/std.h>
#include <string.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/io/GIO.h>
#include <uart/bsp_uart.h>

/* ========================================================================== */
/*                            EXTERNAL VARIABLES                              */
/* ========================================================================== */

/* UART handle for input stream                                               */
extern GIO_Handle uartRxHandle;

/* UART handle for output stream                                              */
extern GIO_Handle uartTxHandle;

/* ========================================================================== */
/*                             MACRO DEFINITIONS                              */
/* ========================================================================== */

#define SIZEOF_UART_START_STRING    (200U)

#ifdef PLATFORM_ZEBU
#define APP_UART_NUM_BYTES          (3U)
#else
#define APP_UART_NUM_BYTES          (1000U)
#endif

/* ========================================================================== */
/*                             GLOBAL VARIABLES                               */
/* ========================================================================== */

/**
 * \brief   Variable to hold the starting message printing string.
 *
 * \note    Buffer alignement is required only when working in DMA Mode.
 */
#pragma DATA_ALIGN(uartTestStringStart, 128);
static char       uartTestStringStart[SIZEOF_UART_START_STRING];

/**
 * \brief   Variable to hold the user supplied 1000 bytes
 *
 * \note    Buffer alignement is required only when working in DMA Mode.
 */
#pragma DATA_ALIGN(uartBuffer, 128);
static char       uartBuffer[1000];

/* ========================================================================== */
/*                           FUNCTION DEFINITIONS                             */
/* ========================================================================== */

/**
 * \brief    Function to demonstrate the UART functionality.This function
 *           requests the user to input 1000 bytes and reads the same and
 *           tranmits the same back to the user.
 *
 * \param    None
 *
 * \return   None
 *
 */
void UartApp_startUartSample(void)
{
    size_t len    = 0, totalLen = 0;
    char  *string = NULL;
    Int    status = IOM_COMPLETED;

    System_printf(
        "\r\nStart of UART sample application, "
        "check the serial Terminal to proceed \n");
#ifdef PLATFORM_ZEBU
    string = "Demo: Input 3 characters \n";
#else
    string = "** UART Demo Starts:  INPUT a file of size 1000 bytes **";
#endif
    /* Copy to start string to Cache aligned buffer */
    strncpy(uartTestStringStart, string, sizeof (uartTestStringStart));

    /* calculate the length of data */
    len = strlen(uartTestStringStart);

    /* Transmit the string */
    status = GIO_write(uartTxHandle, &uartTestStringStart, &len);
    if (IOM_COMPLETED != status)
    {
        /* Report Error */
        System_printf("\r\nGIO_write failed. returned : %d \n", status);
    }

    /* Now the user will input a string of APP_UART_NUM_BYTES bytes.
     * Hence submit a read request for APP_UART_NUM_BYTES bytes and loop
     * till we receive that many bytes */
    while (1U)
    {
        len    = APP_UART_NUM_BYTES - totalLen;
        status = GIO_read(uartRxHandle, &uartBuffer[totalLen], &len);
        if (IOM_COMPLETED != status)
        {
            /* Report Error */
            System_printf("\r\nGIO_read failed. returned : %d \n", status);
        }
        totalLen += len;
        if (totalLen >= APP_UART_NUM_BYTES)
        {
            break;
        }
    }

    /* Echo the input data to User for verification */
    len    = totalLen;
    status = GIO_write(uartTxHandle, &uartBuffer, &len);
    if (IOM_COMPLETED != status)
    {
        /* Report Error */
        System_printf("\r\nGIO_write failed. returned : %d \n", status);
    }

    return;
}

/* ========================================================================== */
/*                              END OF FILE                                   */
/* ========================================================================== */
