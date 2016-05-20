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
#include <ti/sysbios/knl/Swi.h>

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
#define BUFLEN                  1024 /* number of samples in the frame */

#define BUFALIGN                128  /* alignment of buffer for use of L2
                                      *cache*/

/** Number of serializers configured for record */
#define RX_NUM_SERIALIZER       (1U)
#define TX_NUM_SERIALIZER       (1U)

#define BUFSIZE                 (BUFLEN * sizeof (Ptr))

#define NUM_BUFS                (2)   /* Num Bufs to be issued and reclaimed */

#define LOOPJOB_BUF_LEN         (8)

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
static GIO_Handle   inStream;

#if defined (TDA2XX_FAMILY_BUILD) && !defined (USE_JAMR_AUDIO)

static GIO_Handle   i2cExpanderHandle;                  /* Handle to the I2C
                                                         * expander channel */

/* buffer aligned to cache line is required when working in DMA Mode          */
#pragma DATA_ALIGN(wBuffer, 128);
UInt8 wBuffer[I2C_TRANSFER_SIZE];
#pragma DATA_ALIGN(rBuffer, 128);
UInt8 rBuffer[I2C_TRANSFER_SIZE];
#endif

/* ========================================================================== */
/*                           FUNCTION PROTOTYPE                          */
/* ========================================================================== */

extern void Configure_XBAR(void);

static void createStreams(void);
static void prime(void);
#if defined (TDA2XX_FAMILY_BUILD) && !defined (USE_JAMR_AUDIO)
static void i2cExpander_WritePort(const Uint8 *data, Error_Block *eb);
static void configureIOExpander(void);
#endif

Uint8 rxLoopjobBuffer[LOOPJOB_BUF_LEN] = {0x00, 0x00, 0x00, 0x00,
                                          0x00, 0x00, 0x00, 0x00};

Uint8 txLoopjobBuffer[LOOPJOB_BUF_LEN] = {0x00, 0x00, 0x00, 0x00,
                                          0x00, 0x00, 0x00, 0x00};

Ptr buf[NUM_BUFS * 2];

Mcasp_HwSetupData   mcaspRcvSetup = {
    /* .rmask    = */ 0xFFFFFFFF,           /* All the data bits are to be used
                                             *    */
#if defined (DSP_MODE)
    /* .xfmt     = */ 0x000080F0
#else /* I2S MODE*/
      /* .xfmt     = */ 0x000180F0,
#endif
    /* 0 bit delay from framsync if DSP_MODE,
     * or 1 bit delay from framsync if I2S
     * MSB first
     * No extra bit padding
     * Padding bit (ignore)
     * slot Size is 32
     * Reads from DMA port
     * NO rotation
     */
#if defined (AIC_MASTER)
    #if defined (DSP_MODE)
    /* .afsrctl  = */ 0x00000010,           /* burst mode,
                                             * Frame sync is one bit
                                             * externally generated frame sync
                                             * Rising edge is start of frame
                                             */

    #else /* I2S MODE*/
          /* .afsrctl  = */ 0x00000111,
    /* I2S mode,
     * Frame sync is one word
     * externally generated frame sync
     * Falling edge is start of frame
     */
    #endif
#else /* McASP MASTER*/
    #if defined (DSP_MODE)
    /* .afsrctl  = */ 0x00000002,           /* burst mode,
                                             * Frame sync is one bit
                                             * internally generated frame sync
                                             * Rising edge is start of frame
                                             */

    #else /* I2S MODE*/
          /* .afsrctl  = */ 0x00000113,     /* I2S mode,
                                             * Frame sync is one word
                                             * Internally generated frame sync
                                             * Falling edge is start of frame
                                             */
    #endif
#endif
    #if defined (DSP_MODE)
    /* .rtdm     = */ 0x00000001,           /* slot 1 is active (DSP)
                                             *              */

    #else /* I2S MODE*/
          /* .rtdm     = */ 0x00000003,     /* 2 slots are active (I2S)
                                             *            */
    #endif
    /* .rintctl  = */ 0x00000003,           /* sync error and overrun error
                                             *        */
    /* .rstat    = */ 0x000001FF,           /* reset any existing status bits
                                             *      */
    /* .revtctl  = */ 0x00000000,           /* DMA request is enabled or
                                             * disabled
                                             *  */
    {
#if defined (AIC_MASTER)
        #if defined (DSP_MODE)
        /* .aclkrctl  = */ 0x00000000,
        #else /* I2S MODE */
              /* .aclkrctl  = */ 0x00000080,
        #endif
        /* .ahclkrctl = */ 0x00000000,
#else   /* McASP MASTER*/
        #if defined (DSP_MODE)
        /* .aclkrctl  = */ 0x0000002C,
        /* .ahclkrctl = */ 0x00008013,
        #else /* I2S MODE*/
        /* .aclkrctl  = */ 0x000000A7,
        /* .ahclkrctl = */ 0x00008013,
        #endif
#endif
        /* .rclkchk   = */ 0x00000000
    }
};

Mcasp_HwSetupData   mcaspXmtSetup = {
    /* .xmask    = */ 0xFFFFFFFF,       /* All the data bits are to be used
                                         *    */
#if defined (DSP_MODE)
    /* .xfmt     = */ 0x000080F0
#else /* I2S MODE*/
      /* .xfmt     = */ 0x000180F0,
#endif
    /* 0 bit delay from framsync if DSP_MODE,
     * or 1 bit delay from framsync if I2S
     * MSB first
     * No extra bit padding
     * Padding bit (ignore)
     * slot Size is 32
     * Reads from DMA port
     * NO rotation
     */
#if defined (AIC_MASTER)
    #if defined (DSP_MODE)
    /* .afsxctl  = */ 0x00000000,       /* burst mode,
                                         * Frame sync is one bit
                                         * externally generated frame sync
                                         * Rising edge is start of frame
                                         */

    #else /* I2S MODE*/
          /* .afsxctl  = */ 0x00000111,
    /* I2S mode,
     * Frame sync is one word
     * externally generated frame sync
     * Falling edge is start of frame
     */
    #endif
#else /* McASP MASTER*/
    #if defined (DSP_MODE)
    /* .afsxctl  = */ 0x00000002,       /* burst mode,
                                         * Frame sync is one bit
                                         * Internally generated frame sync
                                         * Rising edge is start of frame
                                         * externally generated frame sync
                                         */
    #else /*I2S MODE*/
          /* .afsxctl  = */ 0x00000113, /* I2S mode,
                                         * Frame sync is one word
                                         * internally generated frame sync
                                         * Falling edge is start of frame
                                         */
    #endif
#endif
    #if defined (DSP_MODE)
    /* .xtdm     = */ 0x00000001,       /* slot 1 is active (DSP)
                                         *              */
    #else /* I2S MODE*/
          /* .xtdm     = */ 0x00000003, /* 2 slots are active (I2S)
                                         *            */
    #endif
    /* .xintctl  = */ 0x00000003,       /* sync error,overrun error
                                         *            */
    /* .xstat    = */ 0x000001FF,       /* reset any existing status bits
                                         *      */
    /* .xevtctl  = */ 0x00000000,       /* DMA request is enabled or disabled
                                         *  */
    {
#if defined (AIC_MASTER)
    #if defined (DSP_MODE)
        /* .aclkxctl  = */ 0x00000000,
    #else /* I2S MODE */
          /* .aclkxctl  = */ 0x00000080,
    #endif
        /* .ahclkxctl = */ 0x00000000,
#else   /* McASP MASTER*/
    #if defined (DSP_MODE)
        /* .aclkxctl  = */ 0x0000002C,
        /* .ahclkxctl = */ 0x00008009,

    #else /* I2S MODE*/
          /* .aclkxctl  = */ 0x000000A7,
        /* .ahclkxctl = */ 0x00008013,
    #endif
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
        rxLoopjobBuffer,
        LOOPJOB_BUF_LEN,
        NULL,
        NULL,
#if defined (DSP_MODE)
        1,
        MCASP_BUFFERFORMAT_1SER_1SLOT,
#else      /* I2S MODE*/
        2, /* number of TDM channels      */
        MCASP_BUFFERFORMAT_1SER_MULTISLOT_INTERLEAVED,
#endif
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
        txLoopjobBuffer,
        LOOPJOB_BUF_LEN,
        NULL,
        NULL,
#if defined (DSP_MODE)
        1,
        MCASP_BUFFERFORMAT_1SER_1SLOT,
#else      /* I2S MODE*/
        2, /* number of TDM channels      */
        MCASP_BUFFERFORMAT_1SER_MULTISLOT_INTERLEAVED,
#endif
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
            48000, /* sampling rate for codec */
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
            48000,   /* sampling rate           */
            70,      /* gain (%) for codec      */
            0x00,
            0x00
        }
    }
};

/* ========================================================================== */
/*                           FUNCTION DEFINITIONS                             */
/* ========================================================================== */

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

    /* Create channel for audio input stream
     */
    GIO_Params_init(&ioParams);

    ioParams.chanParams = &audioChanParamsIN;
    ioParams.model      = GIO_Model_ISSUERECLAIM;

    inStream = GIO_create("/audio0",GIO_INPUT, &ioParams, &eb);
    if (inStream == NULL)
    {
        System_printf("\r\nCreate input stream FAILED.\n");
        BIOS_exit(0);
    }

    /* Create channel for audio input stream
     */
    GIO_Params_init(&ioParams);

    ioParams.chanParams = &audioChanParamsOUT;
    ioParams.model      = GIO_Model_ISSUERECLAIM;

    outStream = GIO_create("/audio0", GIO_OUTPUT, &ioParams, &eb);
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

    /* Allocate buffers for the GIO buffer exchanges
     */
    for (count = 0; count < (NUM_BUFS); count++)
    {
        buf[count] = Memory_calloc(iheap, BUFSIZE * TX_NUM_SERIALIZER,
                                   BUFALIGN, &eb);
        if (NULL == buf[count])
        {
            System_printf("\r\nMEM_calloc failed.\n");
        }
    }

    /* Allocate buffers for the GIO buffer exchanges
     */
    for (count = NUM_BUFS; count < (NUM_BUFS * 2); count++)
    {
        buf[count] = Memory_calloc(iheap, BUFSIZE * RX_NUM_SERIALIZER,
                                   BUFALIGN, &eb);
        if (NULL == buf[count])
        {
            System_printf("\r\nMEM_calloc failed.\n");
        }
    }

    /* Prime the buffers for receive channel
     */
    for (count = NUM_BUFS; count < (NUM_BUFS * 2); count++)
    {
        GIO_issue(inStream, buf[count], BUFSIZE * RX_NUM_SERIALIZER, NULL);
    }

    /* Prime the buffers for transmit channel
     */
    for (count = 0; count < (NUM_BUFS); count++)
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
    Ptr rcv    = NULL;
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
        /* Report EDMA Error
         */
        System_printf("\nEDMA driver initialization FAIL\n");
    }
    else
    {
        System_printf("\nEDMA driver initialization PASS.\n");
    }

    /* enable the pinmux for the mcasp device
     */
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

    /* Call prime function to do priming
     */
    prime();

    /* Forever loop to continously receviec and transmit audio data           */
    for (i32Count = 0; i32Count >= 0; i32Count++)
    {
        /* Reclaim full buffer from the input stream
         */
        status = GIO_reclaim(inStream, (Ptr *) &rcv, NULL, NULL);
        if (status != IOM_COMPLETED)
        {
            System_printf("\r\n Error reclaiming full buffer from the input"
                          "stream\n");
        }

        /* Reclaim empty buffer from the output stream to be reused
         */
        status = GIO_reclaim(outStream, (Ptr *) &xmt, NULL, NULL);
        if (status != IOM_COMPLETED)
        {
            System_printf("\r\nError reclaiming empty buffer from the output"
                          "stream\n");
        }

        /* copy the receive information to the transmit buffer
         */
        memcpy(xmt, rcv, BUFSIZE * RX_NUM_SERIALIZER);

        /* Issue full buffer to the output stream
         */
        status = GIO_issue(outStream, xmt, BUFSIZE * TX_NUM_SERIALIZER, NULL);
        if (status != IOM_PENDING)
        {
            System_printf("\r\nFailed to issue full buffer to output stream\n");
        }

        /* Issue empty buffer to the input stream
         */
        status = GIO_issue(inStream, rcv, BUFSIZE * RX_NUM_SERIALIZER, NULL);
        if (status != IOM_PENDING)
        {
            System_printf("\r\nFailed to issue empty buffer to input stream\n");
        }
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

    System_printf("\r\nI2C  :Configuring Expander\n");

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
