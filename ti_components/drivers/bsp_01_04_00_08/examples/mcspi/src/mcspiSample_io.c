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
 *  \brief  Sample application to demostrate the usage of McSPI driver.
 *
 *  (C) Copyright 2010, Texas Instruments, Inc
 *
 *  \author     PSG
 *
 *  \version    0.1    Created for DM814x/C6A811x platform.
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

#include "mcspi/bsp_mcspi.h"
#include <ti/sdo/edma3/drv/edma3_drv.h>

/* ========================================================================== */
/*                            EXTERNAL VARIABLES                              */
/* ========================================================================== */

/* ========================================================================== */
/*                          LOCAL FUNCTION PROTOTYPES                         */
/* ========================================================================== */

static Int spi_Test(void);
static void Spi_Flash_WriteEnable(Mcspi_DataParam *dataparam, Error_Block *eb);
static Bool Spi_Flash_IsBusy(Mcspi_DataParam *dataparam, Error_Block *eb);

EDMA3_DRV_Handle edma3init(UInt32 edma3Id, EDMA3_DRV_Result *);
/* ========================================================================== */
/*                            MACRO DEFINITONS                                */
/* ========================================================================== */

#define  SPI_TEST_STRING_LEN       0x100

/* chip select for the spi flash                          */
#define  SPI_CHIPSELECT_SPIFLASH   0x01

/* flash address where the data will be written and read  */
#define  SPI_FLASH_ADDR_MSB1       0x1F
#define  SPI_FLASH_ADDR_MSB0       0x00
#define  SPI_FLASH_ADDR_LSB        0x00

#define  SPI_MAX_CMD_LEN           0x04

/* SPI flash opcode */
/* Read flash manufacturer/Device ID*/
#define SPI_FLASH_READ_DEV_ID      0x9F
/* flash page write                                       */
#define  SPI_FLASH_PAGE_WRITE      0x02

/* flash data read                                        */
#define  SPI_FLASH_READ            0x03

/* read the status register                               */
#define  SPI_FLASH_READ_STATUS_REG 0x05

/* write enable opcode                                    */
#define  SPI_FLASH_WRITE_ENABLE    0x06

/* sectore erase command                                  */
#define SPI_FLASH_BLOCK_ERASE      0xD8

#define SPI_FLASH_SECTOR_ERASE     0x20

/* ========================================================================== */
/*                              GLOBAL VARIABLES                              */
/* ========================================================================== */

/* Buffer alignement is required when working in DMA Mode */
/* max command length is 4 (opcode + 3 bytes address) + max trnsfer size )    */
#pragma DATA_ALIGN(loopWrite, 128);
Uint8            loopWrite[SPI_TEST_STRING_LEN + SPI_MAX_CMD_LEN];

/* Buffer alignement is required when working in DMA Mode */
#pragma DATA_ALIGN(loopRead, 128);
Uint8            loopRead[SPI_TEST_STRING_LEN + SPI_MAX_CMD_LEN];

#pragma DATA_ALIGN(loopWrittenData, 128);
Uint8            loopWrittenData[SPI_TEST_STRING_LEN + SPI_MAX_CMD_LEN];

/* Handle to the EDMA driver instance                                         */
EDMA3_DRV_Handle gEdmaHandle;

/* McSPI handle for INOUT stream                                              */
GIO_Handle       spiHandle;

/* ========================================================================== */
/*                           FUNCTION DEFINITIONS                             */
/* ========================================================================== */

/**
 * \brief      Function to initialize the edma driver and get the handle to the
 *             edma driver;
 *
 * \param      arg1  [IN]   unused
 * \param      arg2  [IN]   unused
 *
 * \return     None
 */
static void spiEdmaInit(void)
{
    EDMA3_DRV_Result edmaResult = 0;

    gEdmaHandle = edma3init(0, &edmaResult);

    if (edmaResult != EDMA3_DRV_SOK)
    {
        /* Report EDMA Error */
        System_printf("EDMA driver initialization FAIL\n");
    }
    else
    {
        System_printf("EDMA driver initialization PASS.\n");
    }
}

/*
 *  \fn    void start_spi_sample(void)
 *
 *  \brief function which creates the inout and output channels for the SPI
 *         device.
 *
 *   This function opens two channels for the transaction. The channel handles
 *   returned are used to transact with the PSI device.
 *
 *  \param  eb    [OUT]  error block given by the upper layers
 *
 *  \return None
 */
void start_spi_sample(void)
{
    Int              devStatus;
    Mcspi_ChanParams chanParams;
    Error_Block      eb;
    GIO_Params       ioParams;

    Error_init(&eb);

    /*
     * Initialize channel attributes.
     */
    GIO_Params_init(&ioParams);
    /* initialise the edma library and get the EDMA handle                    */
    spiEdmaInit();

    /* update the edma Handle                                                 */
    chanParams.hEdma = gEdmaHandle;
    chanParams.chipSelTimeControl = MCSPI_CLK_CYCLE0;
    chanParams.fifoEnable         = (UInt32)TRUE;
    chanParams.spiChipSelectHold  = (UInt32)TRUE;
    chanParams.chanNum = 0;

    ioParams.chanParams = (Ptr) & chanParams;

    /* create the required channels(TX/RX) for the McSPI demo
     *                 */
    spiHandle = GIO_create("/mcspi0", GIO_INOUT, &ioParams, &eb);

    if (NULL != spiHandle)
    {
        devStatus = spi_Test();

        if (IOM_COMPLETED != devStatus)
        {
            System_printf("\r\nBIOS SPI:Error in SPI sample Test\n");
        }
        else
        {
            System_printf(
                "\r\nBIOS SPI:SPI sample transceive ended succesfully\n");
        }

        GIO_delete(&spiHandle);
    }
    else
    {
        System_printf("\r\nSPI Driver Handle creation Failed\n");
    }

    return;
}

/*
 *  \fn    static Int spi_Test(Error_block *eb)
 *
 *  \brief function That will test the SPI device by reading and writing from
 *  the SPI flash device.
 *
 *  \param  eb    [OUT]  error block given by the upper layers
 *
 *  \return
 *          DriverTypes_Completed - if sucessful
 *          Error code            - in case of error
 */
static Int spi_Test(void)
{
    Uint32          ui32Count = 0;
    Int             status    = IOM_COMPLETED;
    Mcspi_DataParam dataparam;
    SizeT           size = 0;
    Error_Block     eb;

    Error_init(&eb);

    /* clear the input and output buffers                                     */
    memset(loopWrite, 0x00, sizeof (loopWrite));
    memset(loopRead, 0x00, sizeof (loopRead));
    memset(loopWrittenData, 0x00, sizeof (loopWrittenData));
    /* clear the spi params data structure                                    */
    memset(&dataparam, 0x00, sizeof (Mcspi_DataParam));

    /* enable the write to SPI flash                                          */
    Spi_Flash_WriteEnable(&dataparam, &eb);

    /* Read manufacturer ID and the device ID                                 */
    loopWrite[0] = SPI_FLASH_READ_DEV_ID;
    loopWrite[1] = 0x00;
    loopWrite[2] = 0x00;
    loopWrite[3] = 0x00;

    dataparam.bufLen    = 4U;
    dataparam.inBuffer  = &loopRead[0];
    dataparam.outBuffer = &loopWrite[0];

    size = dataparam.bufLen;

    /* write command to FLASH                                                 */
    status = GIO_submit(spiHandle, IOM_WRITE, &dataparam, &size, NULL);

    if (IOM_COMPLETED != status)
    {
        /* Report Error                                                       */
        System_printf("\r\nGIO_submit failed\n");
    }

    System_printf("Manufacturer ID 0x%x Device ID 0x%x 0x%x\n",
                  loopRead[1 + 0],
                  loopRead[1 + 1],
                  loopRead[1 + 2]
                  );

    /* enable the write to SPI flash                                          */
    Spi_Flash_WriteEnable(&dataparam, &eb);

    /* erase a sector of the flash                                            */
    System_printf("Sector Erase command started\n");
    memset(loopWrite, 0x00, sizeof (loopWrite));
    loopWrite[0] = SPI_FLASH_SECTOR_ERASE;
    loopWrite[1] = SPI_FLASH_ADDR_MSB1;
    loopWrite[2] = SPI_FLASH_ADDR_MSB0;
    loopWrite[3] = SPI_FLASH_ADDR_LSB;

    dataparam.bufLen    = SPI_MAX_CMD_LEN;
    dataparam.inBuffer  = NULL;
    dataparam.outBuffer = &loopWrite[0];

    size = dataparam.bufLen;

    /* write command to FLASH                                                 */
    status = GIO_submit(spiHandle, IOM_WRITE, &dataparam, &size, NULL);

    if (IOM_COMPLETED != status)
    {
        /* Report Error                                                   */
        System_printf("GIO_submit failed\n");
    }

    System_printf("Sector Erase in progress...\n");
    /* wait till the flash has completed the erase                            */
    while (TRUE == Spi_Flash_IsBusy(&dataparam, &eb))
    {
        volatile UInt32 i, y = 1000;
        for (i = 0; i < 1000; i++)
        {
            y--;
        }
    }

    System_printf("Sector Erase completed\n");
    /* enable the write to SPI flash                                          */
    Spi_Flash_WriteEnable(&dataparam, &eb);

    /* initialise the data to write to the flash                              */
    for (ui32Count = 0; ui32Count < SPI_TEST_STRING_LEN; ui32Count++)
    {
        /* first 4 bytes will accomodate the command                          */
        loopWrite[SPI_MAX_CMD_LEN + ui32Count]       = ui32Count;
        loopWrittenData[SPI_MAX_CMD_LEN + ui32Count] = ui32Count;

        /* clear the input buffer                                             */
        loopRead[SPI_MAX_CMD_LEN + ui32Count] = 0x00;
    }

    /* write a page of data to the SPI flash                                  */
    loopWrite[0] = SPI_FLASH_PAGE_WRITE;
    loopWrite[1] = SPI_FLASH_ADDR_MSB1;
    loopWrite[2] = SPI_FLASH_ADDR_MSB0;
    loopWrite[3] = SPI_FLASH_ADDR_LSB;

    dataparam.bufLen    = SPI_TEST_STRING_LEN + SPI_MAX_CMD_LEN;
    dataparam.inBuffer  = NULL;
    dataparam.outBuffer = &loopWrite[0];

    size = dataparam.bufLen;

    /* write data to FLASH */
    System_printf("Sector write command started\n");
    status = GIO_submit(spiHandle, IOM_WRITE, &dataparam, &size, NULL);

    if (IOM_COMPLETED != status)
    {
        /* Report Error                                                       */
        System_printf("GIO_submit failed\n");
    }

    /* wait till the flash has completed the write                            */
    System_printf("Sector write in progress...\n");
    while (TRUE == Spi_Flash_IsBusy(&dataparam, &eb))
    {
        volatile UInt32 i, y = 1000;
        for (i = 0; i < 1000; i++)
        {
            y--;
        }
    }

    System_printf("Sector write in completed\n");
    /* The loopwrite needs to be made zero here, otherwise sometimes the data
     * written into the Tx (dummy write) may appear in Rx, which may lead to
     * successful execution of the app without actually transferring the data
     * (kind of loopback)
     */
    memset(loopWrite, 0x00, sizeof (loopWrite));
    /* read the data from the Flash                                           */
    loopWrite[0] = SPI_FLASH_READ;
    loopWrite[1] = SPI_FLASH_ADDR_MSB1;
    loopWrite[2] = SPI_FLASH_ADDR_MSB0;
    loopWrite[3] = SPI_FLASH_ADDR_LSB;

    /* ( Opcode (1byte) + address (3bytes) + (data to be read)                */
    dataparam.bufLen    = SPI_TEST_STRING_LEN + SPI_MAX_CMD_LEN;
    dataparam.outBuffer = &loopWrite[0];
    dataparam.inBuffer  = &loopRead[0];

    size = dataparam.bufLen;

    /* read from Flash                                                        */
    System_printf("Sector read command started\n");
    status = GIO_submit(spiHandle, IOM_WRITE, &dataparam, &size, NULL);

    if (IOM_COMPLETED != status)
    {
        /* Report Error                                                       */
        System_printf("GIO_submit failed\n");
    }

    System_printf("Sector read in completed\n");
    System_printf("Data Verification started\n");

    /* compare the data and check if the data read is OK                      */
    for (ui32Count = 0; ui32Count < SPI_TEST_STRING_LEN; ui32Count++)
    {
        if (loopRead[ui32Count + SPI_MAX_CMD_LEN] != ui32Count)
        {
            System_printf("Data compare Failed SENT %d RECV %d \n",
                          ui32Count, loopRead[ui32Count + SPI_MAX_CMD_LEN]);
            status = IOM_EBADIO;
            break;
        }
    }
    return status;
}

/**
 * \fn      static void Spi_Flash_WriteEnable(Spi_DataParam
 * dataparam,Error_Block *eb)
 *
 * \brief   function That will test the SPI device by reading and writing from
 * the SPI flash device.
 *
 * \param   dataparam  [IN]   pointer to the SPI data params structure
 * \param   eb         [OUT]  error block given by the upper layers
 *
 * \return
 *          DriverTypes_Completed - if sucessful
 *          Error code            - in case of error
 */
static void Spi_Flash_WriteEnable(Mcspi_DataParam *dataparam, Error_Block *eb)
{
    SizeT size   = 0;
    Int   status = IOM_COMPLETED;

    /* Enable the write for the SPI flash                                     */

    /* send the command for enabling the write to SPI flash                   */
    loopWrite[0]         = SPI_FLASH_WRITE_ENABLE;
    dataparam->inBuffer  = NULL;
    dataparam->outBuffer = (Uint8 *) &loopWrite[0];
    dataparam->bufLen    = 1U;

    size = dataparam->bufLen;

    /* SPI Data Write OPCODE Transfer                                         */
    status = GIO_submit(spiHandle, IOM_WRITE, dataparam, &size, NULL);

    if (IOM_COMPLETED != status)
    {
        /* Report Error                                                       */
        System_printf("GIO_submit failed\n");
    }

    /* now read the status register                                           */
    loopWrite[0]         = SPI_FLASH_READ_STATUS_REG;
    dataparam->inBuffer  = loopRead;
    dataparam->outBuffer = loopWrite;
    dataparam->bufLen    = 2U;

    size = dataparam->bufLen;

    /* read the register                                                      */
    status = GIO_submit(spiHandle, IOM_WRITE, dataparam, &size, NULL);

    if (IOM_COMPLETED != status)
    {
        /* Report Error                                                       */
        System_printf("GIO_submit failed\n");
    }

    /* now check if the write enable latch is set to 1 (write enabled)        */
    if (loopRead[1] & (UInt8)0x02)
    {
        System_printf("write is Enabled \n");
    }
    else
    {
        System_printf("Error unable to enable write \n");
    }
}

/**
 * \brief   This function tests whether the flash  is busy executing a command
 *          or is it free to receive the next command
 *
 * \param   dataparam  [IN]   pointer to the SPI data params structure
 * \param   eb         [OUT]  error block given by the upper layers
 *
 * \return  TRUE   - if flash is busy executing command
 *          FALSE  - if flash is free
 */
static Bool Spi_Flash_IsBusy(Mcspi_DataParam *dataparam, Error_Block *eb)
{
    SizeT size   = 0;
    Int   status = IOM_COMPLETED;
    /* now read the status register                                           */
    loopWrite[0]         = SPI_FLASH_READ_STATUS_REG;
    dataparam->inBuffer  = loopRead;
    dataparam->outBuffer = loopWrite;
    dataparam->bufLen    = 2U;

    size = dataparam->bufLen;

    /* read the register                                                      */
    status = GIO_submit(spiHandle, IOM_WRITE, dataparam, &size, NULL);

    if (IOM_COMPLETED != status)
    {
        /* Report Error                                                       */
        System_printf("GIO_submit failed\n");
    }

    /* now check if the write enable latch is set to 1 (write enabled)        *
     * The first byte will contain junk data hence check the second byte      */
    if (loopRead[1] & (UInt8)0x01)
    {
        /* flash is busy     */
        return TRUE;
    }
    else
    {
        /* flash is not busy */
        return FALSE;
    }
}

/* ========================================================================== */
/*                                END OF FILE                                 */
/* ========================================================================== */
