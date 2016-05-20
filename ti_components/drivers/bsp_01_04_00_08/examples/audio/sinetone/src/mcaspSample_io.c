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

/** \file     audioSample_io.c
 *
 *  \brief    sample application for demostration of audio playing
 *
 *  This file contains the implementation of the sample appliation for the
 *  demonstration of audio playing through the audio interface layer.
 *
 *             (C) Copyright 2009, Texas Instruments, Inc
 */

/* ========================================================================== */
/*                            INCLUDE FILES                                   */
/* ========================================================================== */

#include <xdc/std.h>
#include <stdio.h>
#include <ti/sysbios/io/GIO.h>
#include <ti/sysbios/io/IOM.h>
#include <xdc/runtime/Memory.h>
#include <ti/sysbios/heaps/HeapMem.h>
#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Swi.h>

#include <mcasp/bsp_mcasp.h>
#include <audio/bsp_audio.h>
#include <ti/sdo/edma3/drv/edma3_drv.h>
#include "platforms/bsp_platform.h"
#include <osal/bsp_osal.h>
#include <i2c/bsp_i2c.h>
#include <i2clib/lld_hsi2c.h>

#include <audioCommon_cfg.h>

/* ========================================================================== */
/*                          IMPORTED VARIABLES                                */
/* ========================================================================== */

EDMA3_DRV_Handle edma3init(UInt32 edma3Id, EDMA3_DRV_Result *);
extern EDMA3_DRV_Handle          gEdmaHandle;
#ifdef TDA2XX_FAMILY_BUILD
extern EDMA3_DRV_GblConfigParams sampleEdma3GblCfgParams[3];
#endif
/* ========================================================================== */
/*                          MACRO DEFINITIONS                                 */
/* ========================================================================== */

/*
 * Buffers placed in external memory are aligned on a 128 bytes boundary.
 * In addition, the buffer should be of a size multiple of 128 bytes for
 * the cache work optimally on the C6x.
 */
#define NUM_OF_SAMPLES          (96)
/* number of samples in the frame */
#define BUFLEN                  (NUM_OF_SAMPLES * 5)

/* alignment of buffer for use of L2 cache */
#define BUFALIGN                (128)

/** Number of serializers configured for record */
#define RX_NUM_SERIALIZER       (1U)
#define TX_NUM_SERIALIZER       (1U)

#define BUFSIZE                 (BUFLEN * sizeof (Ptr))

#define NUM_BUFS                2                /* Num Bufs to be issued and
                                                  *reclaimed */

#ifdef TDA2XX_FAMILY_BUILD

#define I2C_SLAVE_ADDR            (0x26U)        /* i2c address of PCF8575PWR
                                                  *       */
#define I2C_EXP_PORT1_VIN6_SEL_MCASP     (0x00U) /* This will eNABLE McASP
                                                  *Multiplexing       */
#define I2C_TRANSFER_SIZE         (3U)

#endif

/* ========================================================================== */
/*                            GLOBAL VARIABLES                                */
/* ========================================================================== */

/* inStream and outStream are stream handles created in main */
static GIO_Handle   outStream;
#if defined (TDA2XX_FAMILY_BUILD) && !defined (USE_JAMR_AUDIO)
static GIO_Handle   i2cExpanderHandle;                  /* Handle to the I2C
                                                         * expander channel */

/* buffer aligned to cache line is required when working in DMA Mode          */
#pragma DATA_ALIGN(wBuffer, 128);
UInt8 wBuffer[I2C_TRANSFER_SIZE];
#pragma DATA_ALIGN(rBuffer, 128);
UInt8 rBuffer[I2C_TRANSFER_SIZE];
#endif

/* Function prototype */
extern void Configure_XBAR(void);

static void createStreams(void);
static void prime(void);
static void prepareDataForSineTone(Ptr tempPtr);
#if defined (TDA2XX_FAMILY_BUILD) && !defined (USE_JAMR_AUDIO)
static void i2cExpander_WritePort(const Uint8 *data, Error_Block *eb);
static void configureIOExpander(void);
#endif
Ptr buf[NUM_BUFS * 2];

/* Data that describes a Sine Tone */

Int16 _sineWavePattern[] =
{
    0x0000, 0x0000, 0x10b4, 0x10b4, 0x2120, 0x2120, 0x30fb, 0x30fb, 0x3fff,
    0x3fff, 0x4dea, 0x4dea, 0x5a81, 0x5a81, 0x658b, 0x658b,
    0x6ed8, 0x6ed8, 0x763f, 0x763f, 0x7ba1, 0x7ba1, 0x7ee5, 0x7ee5, 0x7ffd,
    0x7ffd, 0x7ee5, 0x7ee5, 0x7ba1, 0x7ba1, 0x76ef, 0x76ef,
    0x6ed8, 0x6ed8, 0x658b, 0x658b, 0x5a81, 0x5a81, 0x4dea, 0x4dea, 0x3fff,
    0x3fff, 0x30fb, 0x30fb, 0x2120, 0x2120, 0x10b4, 0x10b4,
    0x0000, 0x0000, 0xef4c, 0xef4c, 0xdee0, 0xdee0, 0xcf06, 0xcf06, 0xc002,
    0xc002, 0xb216, 0xb216, 0xa57f, 0xa57f, 0x9a75, 0x9a75,
    0x9128, 0x9128, 0x89c1, 0x89c1, 0x845f, 0x845f, 0x811b, 0x811b, 0x8002,
    0x8002, 0x811b, 0x811b, 0x845f, 0x845f, 0x89c1, 0x89c1,
    0x9128, 0x9128, 0x9a76, 0x9a76, 0xa57f, 0xa57f, 0xb216, 0xb216, 0xc002,
    0xc002, 0xcf06, 0xcf06, 0xdee0, 0xdee0, 0xef4c, 0xef4c
};

Mcasp_HwSetupData   mcaspRcvSetup = {
    /* .rmask    = */ 0xFFFFFFFF, /* All the data bits are to be used     */
    /* .rfmt     = */ 0x000180F0, /* 0 bit delay from framsync if DSP_MODE,
                                   * or 1 bit delay from framsync if I2S
                                   * MSB first
                                   * No extra bit padding
                                   * Padding bit (ignore)
                                   * slot Size is 32
                                   * Reads from DMA port
                                   * NO rotation
                                   */

#if defined (AIC_MASTER)
    /* .afsrctl  = */ 0x00000111, /* I2S mode,
                                   * Frame sync is one Word
                                   * externally generated frame sync
                                   * Falling edge is start of frame
                                   */

#else
    /* .afsrctl  = */ 0x00000113, /* I2S mode,
                                   * Frame sync is one Word
                                   * Interally generated frame sync
                                   * Falling edge is start of frame
                                   */

#endif
    /* .rtdm     = */ 0x00000003,     /* 2 slots are active (I2S)             */
    /* .rintctl  = */ 0x00000003,     /* sync error and overrun error         */
    /* .rstat    = */ 0x000001FF,     /* reset any existing status bits       */
    /* .revtctl  = */ 0x00000000,     /* DMA request is enabled or disabled   */
    {
#if defined (AIC_MASTER)
        /* .aclkrctl  = */ 0x00000080,
        /* .ahclkrctl = */ 0x00000000,
#else
        /* .aclkrctl  = */ 0x000000A6,
        /* .ahclkrctl = */ 0x00008009,
#endif
        /* .rclkchk   = */ 0x00000000
    }
};

Mcasp_HwSetupData   mcaspXmtSetup = {
    /* .xmask    = */ 0xFFFFFFFF, /* All the data bits are to be used     */
    /* .xfmt     = */ 0x000180F5, /* 0 bit delay from framsync if DSP_MODE,
                                   * or 1 bit delay from framsync if I2S
                                   * MSB first
                                   * No extra bit padding
                                   * Padding bit (ignore)
                                   * slot Size is 32
                                   * Reads from DMA port
                                   * NO rotation
                                   */
#if defined (AIC_MASTER)
    /* .afsxctl  = */ 0x00000111, /* I2S mode,
                                   * Frame sync is one word
                                   * externally generated frame sync
                                   * Falling edge is start of frame
                                   */

#else
    /* .afsxctl  = */ 0x00000113, /* I2S mode,
                                   * Frame sync is one word
                                   * internally generated frame sync
                                   * Falling edge is start of frame
                                   */

#endif
    /* .xtdm     = */ 0x00000003,     /* 2 slots are active (I2S)             */
    /* .xintctl  = */ 0x00000003,     /* sync error,overrun error             */
    /* .xstat    = */ 0x000001FF,     /* reset any existing status bits       */
    /* .xevtctl  = */ 0x00000000,     /* DMA request is enabled or disabled   */
    {
#if defined (AIC_MASTER)
        /* .aclkxctl  = */ 0x00000080,
        /* .ahclkxctl = */ 0x00000000,
#else
/*
 * In case of Tda2xx, AuxClock is to be 451.584 MHz,
 * We derive HCLK 22.5792MHz, BCLK 2.8224MHz
 * FS would be 44.1 kHz
 */
        /* .aclkxctl  = */ 0x000000A7,
        /* .ahclkxctl = */ 0x00008013,
#endif
        /* .xclkchk   = */ 0x00000000
    },
};

/* McBsp channel parameters                                  */
Mcasp_ChanParams    mcasp_chanparam[AUDIO_NUM_CHANS] =
{
    {
        0x0001,                    /* number of serialisers      */
        {MCASP_SERIALIZERNUM_1, }, /* serialiser index           */
        &mcaspRcvSetup,
        TRUE,
        MCASP_OPMODE_TDM,          /* Mode (TDM/DIT)             */
        MCASP_WORDLENGTH_32,
        NULL,
        0,
        NULL,
        NULL,
        2,                        /* number of TDM channels      */
        MCASP_BUFFERFORMAT_1SER_MULTISLOT_INTERLEAVED,
        TRUE,
        TRUE,
        9
    },
    {
        0x0001,                   /* number of serialisers       */
        {MCASP_SERIALIZERNUM_0, },
        &mcaspXmtSetup,
        TRUE,
        MCASP_OPMODE_TDM,
        MCASP_WORDLENGTH_32,      /* word width                  */
        NULL,
        0,
        NULL,
        NULL,
        2,                        /* number of TDM channels      */
        MCASP_BUFFERFORMAT_1SER_MULTISLOT_INTERLEAVED,
        TRUE,
        TRUE,
        9
    }
};

Audio_ChannelConfig audioChanParamsIN =
{
    /*  channel 0 (RX)                         */
    (Ptr) & mcasp_chanparam[0],
    {              /* codec [0]                           */
        {
            44100, /* sampling rate for codec */
            30,    /* gain (%) for codec      */
            0x00,
            0x00
        }
    }
};

Audio_ChannelConfig audioChanParamsOUT =
{
    /*  channel 1 (TX)                         */
    (Ptr) & mcasp_chanparam[1],
    {
        /* codec [1]                           */
        {
            44100, /* sampling rate           */
            70,    /* gain (%) for codec      */
            0x00,
            0x00
        }
    }
};

/*
 * ======== createStreams ========
 */
static void createStreams(void)
{
    Error_Block eb;
    GIO_Params  ioParams;

    mcasp_chanparam[0].edmaHandle = gEdmaHandle;
    mcasp_chanparam[1].edmaHandle = gEdmaHandle;

    Error_init(&eb);
    GIO_Params_init(&ioParams);

    ioParams.chanParams = &audioChanParamsIN;
    ioParams.model      = GIO_Model_ISSUERECLAIM;

    GIO_Params_init(&ioParams);

    ioParams.chanParams = &audioChanParamsOUT;
    ioParams.model      = GIO_Model_ISSUERECLAIM;

    outStream = GIO_create("/audio0",GIO_OUTPUT, &ioParams, &eb);
    if (outStream == NULL)
    {
        System_printf("\r\nCreate output stream FAILED.\n");
        BIOS_exit(0);
    }
}

/*
 * ======== prime ========
 */
static void prime(void)
{
    Error_Block  eb;
    Int32        count = 0;
    IHeap_Handle iheap;

    iheap = HeapMem_Handle_to_xdc_runtime_IHeap(myHeap);
    Error_init(&eb);

    /* Allocate buffers for the SIO buffer exchanges                          */
    for (count = 0; count < (NUM_BUFS); count++)
    {
        buf[count] = Memory_calloc(iheap, BUFSIZE * RX_NUM_SERIALIZER,
                                   BUFALIGN, &eb);
        if (NULL == buf[count])
        {
            System_printf("\r\nMEM_calloc failed.\n");
        }
    }

    /* Allocate buffers for the SIO buffer exchanges                          */
    for (count = NUM_BUFS; count < (NUM_BUFS * 2); count++)
    {
        buf[count] = Memory_calloc(iheap, BUFSIZE * TX_NUM_SERIALIZER,
                                   BUFALIGN, &eb);
        if (NULL == buf[count])
        {
            System_printf("\r\nMEM_calloc failed.\n");
        }

        prepareDataForSineTone(buf[count]);
    }

    for (count = NUM_BUFS; count < (NUM_BUFS * 2); count++)
    {
        GIO_issue(outStream, buf[count], BUFSIZE * TX_NUM_SERIALIZER, NULL);
    }
}

/*
 * ======== echo ========
 * This function copies from the input SIO to the output SIO. You could
 * easily replace the copy function with a signal processing algorithm.
 */
void Audio_echo_Task(void)
{
#ifdef TI814X_BUILD
    Bsp_PlatformInitParams platInitPrms;
#endif
    volatile Int32         i32Count;
    Ptr xmt    = NULL;
    Int status = IOM_COMPLETED;

    EDMA3_DRV_Result       edmaResult = 0;

#ifdef TDA2XX_FAMILY_BUILD
    /* Configure INT/DMA XBAR for McASP instances */
    Configure_XBAR();

    /* Enable all McASP events */
    sampleEdma3GblCfgParams[0].dmaChannelHwEvtMap[0] |= 0xFFFFu;
#endif

#if defined (TDA2XX_FAMILY_BUILD) && defined (BUILD_DSP)
    gEdmaHandle = edma3init(1, &edmaResult);
#else
    gEdmaHandle = edma3init(0, &edmaResult);
#endif

    if (edmaResult != EDMA3_DRV_SOK)
    {
        /* Report EDMA Error */
        System_printf("\nEDMA driver initialization FAIL\n");
    }
    else
    {
        System_printf("\nEDMA driver initialization PASS.\n");
    }

    /* enable the pinmux for the mcasp device    */
#ifdef TI814X_BUILD
    /* isPinMuxSettingReq parameter will be initialised to TRUE */

    BspPlatformInitParams_init(&platInitPrms);

    /* Call the EVM specific initialization function                          */
    Bsp_platformInit(&platInitPrms);
#endif

#if defined (TDA2XX_FAMILY_BUILD) && !defined (USE_JAMR_AUDIO)
    configureIOExpander();
#endif

    /* Call createStream function to create I/O streams                       */
    createStreams();

    /* Call prime function to do priming                                      */
    prime();

    System_printf(
        "\r\nBeginning Audio Sine tone Transfer ********* from DMA \n");

    /* Forever loop to continously receviec and transmit audio data           */
    for (i32Count = 0; i32Count >= 0; i32Count++)
    {
        /* Reclaim empty buffer from the output stream to be reused */
        status = GIO_reclaim(outStream, (Ptr *) &xmt, NULL, NULL);
        if (status != IOM_COMPLETED)
        {
            System_printf(
                "\r\nError reclaiming empty buffer from the output stream\n");
        }

        /* Issue full buffer to the output stream                             */
        status = GIO_issue(outStream, xmt, BUFSIZE * TX_NUM_SERIALIZER, NULL);

        if (status != IOM_PENDING)
        {
            System_printf("\r\nFailed to issue empty buffer to stream\n");
        }
    }
}

/**
 * \brief prepareDataForSineTone
 *        This function prepares IO request packets, fills them with data for
 *         sine tone.
 *
 * \return  PAL_SOK
 *
 */
static void prepareDataForSineTone(Ptr tempPtr)
{
    Int16 *sineToneDataPtr    = NULL;
    Uint32 sineToneCount      = 5U;
    Uint32 noOfSamplePerCycle = 96;
    Int32 *tempPtrI           = (Int32 *) tempPtr;

    /* For all serilizers */
    /* Store 9 cycles of sine wave */
    while (sineToneCount)
    {
        /* Initialize sineToneDataPtr to start */
        sineToneDataPtr = _sineWavePattern;
        while (noOfSamplePerCycle)
        {
            /* Store the data */
            *tempPtrI = (Uint32) ((*sineToneDataPtr));

            noOfSamplePerCycle--;
            tempPtrI++;
            sineToneDataPtr++;
        }
        sineToneCount--;
        /* Let the sine tone loop start again */
        noOfSamplePerCycle = 96;
    }
}

#if defined (TDA2XX_FAMILY_BUILD) && !defined (USE_JAMR_AUDIO)
static void i2cExpander_WritePort(const Uint8 *data, Error_Block *eb)
{
    lld_hsi2c_datatfr_params_t i2cXferParams;

    /* Assign data into output buffer                                         */
    /* First command word and then the data                                   */
    wBuffer[0] = *data;
    wBuffer[1] = rBuffer[0];

    /* Prepare the data to be written to the port                             */
    i2cXferParams.slaveAddr = I2C_SLAVE_ADDR;
    i2cXferParams.buffer    = &wBuffer[0];
    i2cXferParams.bufLen    = 2U;
    i2cXferParams.flags     = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER |
                              LLD_HSI2C_START | LLD_HSI2C_STOP;
    i2cXferParams.timeout = 4000;

    /* Write the data to I2c expander                                         */
    GIO_submit(i2cExpanderHandle,
               IOM_WRITE,
               &i2cXferParams,
               &i2cXferParams.bufLen,
               NULL);
}

static void configureIOExpander(void)
{
    Error_Block eb;
    Uint8       value;
    lld_hsi2c_datatfr_params_t i2cXferParams;
    GIO_Params  ioParams;

    Error_init(&eb);
    /*
     * Initialize channel attributes.
     */
    GIO_Params_init(&ioParams);

    ioParams.chanParams = (void *) &i2cXferParams;

    System_printf("\r\nI2C  :Configuring IO Expander\n");

    /* Create the I2C Channels for the TX and RX communication                */
    i2cExpanderHandle = GIO_create(EXPANDER_CTRL_BUS, GIO_OUTPUT, &ioParams,
                                   &eb);

    if ((NULL == i2cExpanderHandle))
    {
        System_printf("\r\nI2C : I2C Expander Handle Create Failed.......! \n");
    }
    else
    {
        value = I2C_EXP_PORT1_VIN6_SEL_MCASP;
        /* Call function for the I2c read write test                          */
        i2cExpander_WritePort(&value, &eb);
    }
}

#endif

/*============================================================================*/
/*                          END OF FILE                                       */
/*============================================================================*/
