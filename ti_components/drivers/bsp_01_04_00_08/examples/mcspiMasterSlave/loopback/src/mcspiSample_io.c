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
 *  \file   mcspiSample_io.c
 *
 *  \brief  McSPI evm to evm communication sample application
 *
 *          This file demonstrates the use of Mcspi by using an
 *          EVM to EVM communication setup.This file configures one of the evm
 *          in master mode.
 *
 *  (C) Copyright 2010, Texas Instruments, Inc
 *
 *  \author     PSG
 *
 *
 */

/* ========================================================================== */
/*                          INCLUDE FILES                                     */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <xdc/std.h>
#include <ti/sysbios/io/GIO.h>
#include <ti/sysbios/BIOS.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/knl/Task.h>
#include <xdc/runtime/IHeap.h>
#include <ti/sysbios/heaps/HeapMem.h>
#include "mcspi/bsp_mcspi.h"
#include <xdc/runtime/Memory.h>
#include <ti/sdo/edma3/drv/edma3_drv.h>

/* ========================================================================== */
/*                          LOCAL FUNCTION PROTOTYPES                         */
/* ========================================================================== */
EDMA3_DRV_Handle edma3init(UInt32 edma3Id, EDMA3_DRV_Result *);
/* ========================================================================== */
/*                            MACRO DEFINITONS                                */
/* ========================================================================== */

/* ========================================================================== */
/*                              GLOBAL VARIABLES                              */
/* ========================================================================== */

EDMA3_DRV_Handle      gEdmaHandle;

extern HeapMem_Handle myHeap;

/*
 * Buffers placed in external memory are aligned on a 128 bytes boundary.
 * In addition, the buffer should be of a size multiple of 128 bytes for
 * the cache to work optimally.
 */

#define BUFLEN          (1024 * 4) /* Buffer size */
#define BUFALIGN        128        /* Alignment of buffer for use of L2 cache */
#define ITERATION_CNT   100        /* Number of Iterations */
#define NUM_BUFS        3          /* Num Bufs to be issued and reclaimed */

/* handle to the input and output streams   */
GIO_Handle mcspiHandle = NULL;

/* Global SPI init config data structure    */
Mcspi_Params          spiParams;

Mcspi_DataParam       issueDataparam[NUM_BUFS];

/* Buffer alignement is required when working in DMA Mode */
#pragma DATA_ALIGN(rxbuf, BUFALIGN);
Ptr  rxbuf[NUM_BUFS];

/* Buffer alignement is required when working in DMA Mode */
#pragma DATA_ALIGN(txbuf, BUFALIGN);
Ptr  txbuf[NUM_BUFS];

Bool failFlag = FALSE;

/* Function prototype */
static void createStream(void);
static void prime(void);
/* ========================================================================== */
/*                           FUNCTION DEFINITIONS                             */
/* ========================================================================== */

/*
 * ======== createStream ========
 */
static void createStream(void)
{
    GIO_Params       ioParams;
    Mcspi_ChanParams chanParams;
    Error_Block      eb;

    Error_init(&eb);

    /*
     * Initialize channel attributes.
     */
    GIO_Params_init(&ioParams);

    /* update the edma Handle                                                 */
    chanParams.hEdma = gEdmaHandle;
    chanParams.chipSelTimeControl = MCSPI_CLK_CYCLE0;
    chanParams.fifoEnable         = (UInt32) TRUE;
    chanParams.spiChipSelectHold  = (UInt32) TRUE;
    chanParams.chanNum = 0;

    /* If cross bar events are being used then make isCrossBarIntEn = TRUE and
     * choose appropriate interrupt number to be mapped (assign it to
     * intNumToBeMapped)
     */
    /* Cross bar evt disabled */
    chanParams.crossBarEvtParam.isCrossBarIntEn  = (UInt32) FALSE;
    chanParams.crossBarEvtParam.intNumToBeMapped = 0xFF;  /* Invalid number */

    ioParams.chanParams = (Ptr) & chanParams;
    ioParams.model      = GIO_Model_ISSUERECLAIM;
    ioParams.numPackets = NUM_BUFS + 1;

    mcspiHandle = GIO_create("/mcspi0", GIO_INOUT, &ioParams, &eb);
    if (mcspiHandle == NULL)
    {
        System_printf("\r\nCreate input stream FAILED.\n");
        BIOS_exit(0);
    }
}

/*
 * \brief   Function to submit request the driver.Depending on the macro
 *          "NUM_BUFS" either the driver can be buffered with multiple requests
 *          or only one buffer by using the NUM_BUFS as 1.
 *
 * \param   None
 *
 * \return  None
 */
static void prime(void)
{
    Error_Block  eb;
    Int32        count = 0;
    IHeap_Handle iheap;
    UInt32       tempCount = 0;
    UInt32       size      = 0;
    Int          status    = IOM_COMPLETED;

    iheap = HeapMem_Handle_to_xdc_runtime_IHeap(myHeap);
    Error_init(&eb);

    /* Allocate buffers for the GIO buffer exchanges                          */
    for (count = 0; count < (NUM_BUFS); count++)
    {
        rxbuf[count] = (Ptr) Memory_calloc(iheap, BUFLEN, BUFALIGN, &eb);
        if (NULL == rxbuf[count])
        {
            System_printf("\r\nMEM_calloc failed.\n");
        }

        txbuf[count] = (Ptr) Memory_calloc(iheap, BUFLEN, BUFALIGN, &eb);
        if (NULL == txbuf[count])
        {
            System_printf("\r\nMEM_calloc failed.\n");
        }
    }

    /* Fill the buffers with known data and transmit the same and check if the*
     * same pattern is received on the other EVM                              */
    for (count = 0; count < (NUM_BUFS); count++)
    {
        for (tempCount = 0; tempCount < BUFLEN; tempCount++)
        {
            ((Uint8 *) txbuf[count])[tempCount] = tempCount;
        }
    }
    for (count = 0; count < NUM_BUFS; count++)
    {
        issueDataparam[count].bufLen    = BUFLEN;
        issueDataparam[count].inBuffer  = rxbuf[count];
        issueDataparam[count].outBuffer = txbuf[count];

        size = issueDataparam[count].bufLen;

        /* Issue the first & second empty buffers to the input stream         */
        status = GIO_issue(mcspiHandle, &issueDataparam[count], size, NULL);

        if (status != IOM_PENDING && status != IOM_COMPLETED)
        {
            System_printf("\r\nFailed to issue empty buffer to stream\n");
        }
    }
}

/*
 * \brief   This function demostrates the use of Mcspi using an EVM to EVM
 *          communication setup.
 *
 * \param   None
 *
 * \return  None
 */
void start_spi_sample(void)
{
    volatile Int32   i32Count  = 0;
    Mcspi_DataParam *dataparam = {0};
    UInt32           tempCount = 0;
    UInt32           i, loopcount = 0;
    UInt32           dataMismatchError = 0;

    Int status = IOM_COMPLETED;

    EDMA3_DRV_Result edmaResult = 0;

    gEdmaHandle = edma3init(0, &edmaResult);

    if (edmaResult != EDMA3_DRV_SOK)
    {
        /* Report EDMA Error */
        System_printf("\nEDMA driver initialization FAIL\n");
    }
    else
    {
        System_printf("\nEDMA driver initialization PASS.\n");
    }

    /* Call createStream function to create I/O streams                       */
    createStream();

    /* Call prime function to do priming                                      */
    prime();

    for (i = 0; i < NUM_BUFS; i++)
    {
        dataparam = NULL;
        /* Reclaim full buffer from the stream                                */
        status = GIO_reclaim(mcspiHandle, (Ptr *) &dataparam, NULL, NULL);

        if (IOM_COMPLETED != status)
        {
            System_printf("Iteration %d\n", i32Count);

            System_printf(
                "Error reclaiming empty buffer from the streams %x"
                " error = 0x%d\n",
                ((Uint8) (dataparam->outBuffer[i32Count])),
                status);
            break;
        }

        for (tempCount = 0; tempCount < BUFLEN; tempCount++)
        {
            if (((Uint8 *) dataparam->outBuffer[tempCount]) !=
                ((Uint8 *) dataparam->inBuffer[tempCount]))
            {
                System_printf(
                    "Error matching data in Buffer no: %d at location %d\n", i,
                    tempCount);
                dataMismatchError = 1;
                break;
            }
        }
    }
    if (dataMismatchError == 0)
    {
        System_printf("Loop back test passed\n");
        System_printf(
            "\nRunning McSpi read in a loop to probe and verify the signals\n");
    }
    else
    {
        System_printf("Loop back test Failed\n");
        while (1) ;
    }
    /* Forever loop to continously recevie and transmit data            */
    for (loopcount = 0;; loopcount++)
    {
        status = GIO_issue(mcspiHandle, &issueDataparam[0], BUFLEN, NULL);
        if (status != IOM_PENDING && status != IOM_COMPLETED)
        {
            System_printf("\r\nFailed to issue empty buffer to stream\n");
        }
        status = GIO_reclaim(mcspiHandle, (Ptr *) &dataparam, NULL, NULL);
        if (IOM_COMPLETED != status)
        {
            System_printf("\r\nError In reclaim in continuous loop\n");
        }
        if (loopcount % 100 == 0)
        {
            System_printf(".\n");
        }
    }
}

/* ========================================================================== */
/*                                END OF FILE                                 */
/* ========================================================================== */
