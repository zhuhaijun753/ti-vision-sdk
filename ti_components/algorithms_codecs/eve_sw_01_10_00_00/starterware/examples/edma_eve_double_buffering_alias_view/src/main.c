/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*-----------------------------------------------------------------------*/
/*  NAME : main.c                                                        */
/*                                                                       */
/*                                                                       */
/*  DESCRIPTION:                                                         */
/*                                                                       */
/*  This is a driver file for setting up double buffering via DMA. The   */
/*  input is a greyscale image, stored in DDR memory, which is divided   */
/*  into 2D blocks that are transfered via DMA for proccessing in EVE    */
/*  internal memory. The proccessing step is a simple copy of the        */
/*  block between two EVE internal memory regions. The processed data is */
/*  then transferred from internal to DDR memory via DMA.                */
/*                                                                       */
/*=======================================================================*/
/*  Texas Instruments Incorporated 2012.                                 */
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/*  Standard header includes for c environment.                          */
/*-----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <vcop\vcop.h>

/*-----------------------------------------------------------------------*/
/*  These are the include files that are needed for edma/qdma.           */
/*-----------------------------------------------------------------------*/

#include "edma_utils.h"
#include "edma_utils_autoincrement.h"
#include "edma_utils_context_size.h"
#include "edma_utils_memcpy.h"
#include "image_dims.h"
#include "arp32.h"

#include "vcop_copy_data_per_8.h"

extern unsigned short __pblock_vcop_copy_data_per_8[10];


/* --------------------------------------------------------------------- */
/* EVE internal memory ping/pong buffers for processing                  */
/* --------------------------------------------------------------------- */
#define BUF_PING   1    /**< Macro indicating set of PING buffers in double buffering mode */
#define BUF_PONG   0    /**< Macro indicating set of PONG buffers in double buffering mode */


#ifndef VCOP_CAMA

#pragma DATA_ALIGN   (src_proc_ping,  32);
#pragma DATA_ALIGN   (src_proc_pong,  32);
#pragma DATA_ALIGN   (dst_proc_ping,  32);
#pragma DATA_ALIGN   (dst_proc_pong,  32);
#pragma DATA_ALIGN   (autoIncrementContext,  32);


#pragma DATA_SECTION (src_proc_ping, "IBUFLA");
#pragma DATA_SECTION (src_proc_pong, "IBUFLB");
#pragma DATA_SECTION (dst_proc_ping, "IBUFHA");
#pragma DATA_SECTION (dst_proc_pong, "IBUFHB");
#pragma DATA_SECTION (autoIncrementContext, "WMEM");


unsigned char src_proc_ping[BLK_WIDTH*BLK_HEIGHT];
unsigned char src_proc_pong[BLK_WIDTH*BLK_HEIGHT];
unsigned char dst_proc_ping[BLK_WIDTH*BLK_HEIGHT];
unsigned char dst_proc_pong[BLK_WIDTH*BLK_HEIGHT];
unsigned char autoIncrementContext[EDMA_UTILS_AUTOINCREMENT_CONTEXT_SIZE];



#else
#define  ALIAS_128K (128 * 1024)
unsigned char *src_proc_ping;
unsigned char *dst_proc_ping;
unsigned char * autoIncrementContext;

#endif

unsigned int  profile[10];

/* --------------------------------------------------------------------- */
/* Output image                                                          */
/* --------------------------------------------------------------------- */

#pragma DATA_SECTION (output,        "DST_MEM");
unsigned char output[IMG_WIDTH*IMG_HEIGHT];


/* --------------------------------------------------------------------- */
/* Input image                                                           */
/* --------------------------------------------------------------------- */

extern unsigned char CurrentLuma0[IMG_WIDTH*IMG_HEIGHT];


/* --------------------------------------------------------------------- */
/* Function to zero out all destination and processing buffers           */
/* --------------------------------------------------------------------- */

void dst_buffers_setup()
{
   #ifndef VCOP_CAMA
   memset (src_proc_ping, 0x0, sizeof(src_proc_ping));
   memset (src_proc_pong, 0x0, sizeof(src_proc_pong));
   memset (dst_proc_ping, 0x0, sizeof(dst_proc_ping));
   memset (dst_proc_pong, 0x0, sizeof(dst_proc_pong));
   memset (output,        0x0, sizeof(output));
   #else
   memset (src_proc_ping,              0x0, sizeof(src_proc_ping));
   memset (src_proc_ping + ALIAS_128K, 0x0, sizeof(src_proc_ping));
   memset (dst_proc_ping,              0x0, sizeof(dst_proc_ping));
   memset (dst_proc_ping + ALIAS_128K, 0x0, sizeof(dst_proc_ping));
   memset (output,                     0x0, sizeof(output));
   #endif
}



/* --------------------------------------------------------------------- */
/*  Start of the main test_harness code.                                 */
/* --------------------------------------------------------------------- */

int main()
{
    /* ----------------------------------------------------------------- */
    /* Pointers to input/output buffers in external memory               */
    /* ----------------------------------------------------------------- */

    unsigned char           *src;
    unsigned char           *dst;

    unsigned int            fail_dma;
    unsigned int            t0;
    unsigned int            t1;
    unsigned int            num_wpreg_params;
    EDMA_UTILS_autoIncrement_initParam initParam;
    int32_t status = 0;
    volatile uint8_t flag = 0;
    uint32_t         contextSize;
    /* ----------------------------------------------------------------- */
    /* Check to see if block width is a multiple of 8 since VCOP will    */
    /* process 8 pixels in SIMD.                                         */
    /* ----------------------------------------------------------------- */

    assert((BLK_WIDTH % 8) == 0);


    /* ------------------------------------------------------------------ */
    /* Check to see if block width is a multiple of the image width and   */
    /* height.                                                            */
    /* ------------------------------------------------------------------ */

    assert((IMG_WIDTH % BLK_WIDTH) == 0);
    assert((IMG_HEIGHT % BLK_HEIGHT) == 0);

    /* Reset the global State Structure */

    EDMA_UTILS_globalReset();

    /* ------------------------------------------------------------------ */
    /* Set memory view to aliased view, and change all buffers to SYSTEM. */
    /* ------------------------------------------------------------------ */

    VCOP_SET_MEM_VIEW (ALIAS_128K_VIEW);

#ifdef VCOP_CAMA

    printf("Now allocating memory \n\n");
    vcop_setview(VCOP_MEMALIASED);

    src_proc_ping = (unsigned char *)vcop_malloc(VCOP_IBUFLA, BLK_WIDTH * BLK_HEIGHT);
    dst_proc_ping = (unsigned char *)vcop_malloc(VCOP_IBUFHA, BLK_WIDTH * BLK_HEIGHT);

    contextSize = EDMA_UTILS_autoIncrement_getContextSize();
    autoIncrementContext = (unsigned char *)vcop_malloc(VCOP_WBUF,contextSize);
    printf ("src_proc_ping:0x%.8x, dst_proc_ping:0x%.8x \n", src_proc_ping, dst_proc_ping);
#endif

    _tsc_start();


    /* ------------------------------------------------------------------ */
    /*  Clear destination and processing buffers                          */
    /* ------------------------------------------------------------------ */

    dst_buffers_setup();

    /* ------------------------------------------------------------- */
    /* Declare the pointers to the source and destination arrays in  */
    /* external memory.                                              */
    /* ------------------------------------------------------------- */

    src = CurrentLuma0;
    dst = output;

    initParam.numInTransfers    = 1;
    initParam.numOutTransfers   = 1;
    initParam.transferType      = EDMA_UTILS_TRANSFER_INOUT;

    initParam.transferProp[0].blkWidth             = BLK_WIDTH;
    initParam.transferProp[0].blkHeight            = BLK_HEIGHT;
    initParam.transferProp[0].extBlkIncrementX     = BLK_WIDTH;
    initParam.transferProp[0].extBlkIncrementY     = BLK_HEIGHT;
    initParam.transferProp[0].intBlkIncrementX     = 0;
    initParam.transferProp[0].intBlkIncrementY     = 0;
    initParam.transferProp[0].extMemPtrStride      = IMG_LINE_PITCH;
    initParam.transferProp[0].interMemPtrStride    = BLK_WIDTH;
    initParam.transferProp[0].roiWidth             = IMG_WIDTH;
    initParam.transferProp[0].roiHeight            = IMG_HEIGHT;
    initParam.transferProp[0].roiOffset            = 0;
    initParam.transferProp[0].extMemPtr            = src;
    initParam.transferProp[0].interMemPtr          = src_proc_ping;

    initParam.transferProp[1].blkWidth             = BLK_WIDTH;
    initParam.transferProp[1].blkHeight            = BLK_HEIGHT;
    initParam.transferProp[1].extBlkIncrementX     = BLK_WIDTH;
    initParam.transferProp[1].extBlkIncrementY     = BLK_HEIGHT;
    initParam.transferProp[1].intBlkIncrementX     = 0;
    initParam.transferProp[1].intBlkIncrementY     = 0;
    initParam.transferProp[1].extMemPtrStride      = IMG_LINE_PITCH;
    initParam.transferProp[1].interMemPtrStride    = BLK_WIDTH;
    initParam.transferProp[1].roiWidth             = IMG_WIDTH;
    initParam.transferProp[1].roiHeight            = IMG_HEIGHT;
    initParam.transferProp[1].roiOffset            = 0;

    initParam.transferProp[1].extMemPtr            = dst;
    initParam.transferProp[1].interMemPtr          = dst_proc_ping;

    /* Initialize EDMA autoincrement Utiliy*/
    EDMA_UTILS_autoIncrement_init(autoIncrementContext,&initParam);

    /* Configure EDMA register */
    EDMA_UTILS_autoIncrement_configure(autoIncrementContext , EDMA_UTILS_TRANSFER_INOUT);

    num_wpreg_params = vcop_copy_data_per_8_init(src_proc_ping, dst_proc_ping, BLK_WIDTH, BLK_HEIGHT, __pblock_vcop_copy_data_per_8);

    flag = BUF_PING;
    VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP, IBUFHA_SYST, IBUFLA_SYST);



    /* Get First Block In */
    EDMA_UTILS_autoIncrement_triggerInChannel(autoIncrementContext);
    EDMA_UTILS_autoIncrement_waitInChannel(autoIncrementContext);

    t0 = _tsc_gettime();
    while ( status == 0)
    {
        flag = VCOP_BUF_SWITCH_TOGGLE(flag);
        status = EDMA_UTILS_autoIncrement_triggerOutChannel(autoIncrementContext);
        EDMA_UTILS_autoIncrement_triggerInChannel(autoIncrementContext);

        vcop_copy_data_per_8_vloops(__pblock_vcop_copy_data_per_8);

        EDMA_UTILS_autoIncrement_waitOutChannel(autoIncrementContext);
        EDMA_UTILS_autoIncrement_waitInChannel(autoIncrementContext);

        _vcop_vloop_done();

    }
    flag = VCOP_BUF_SWITCH_TOGGLE(flag);

    status = EDMA_UTILS_autoIncrement_triggerOutChannel(autoIncrementContext);
    EDMA_UTILS_autoIncrement_waitOutChannel(autoIncrementContext);

    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);
    t1 = _tsc_gettime();
    profile[0] = t1 - t0;

    printf ("cycles:%d \n", (t1 - t0));

    /*--------------------------------------------------------------*/
    /* Free allocated memory.                                       */
    /*--------------------------------------------------------------*/

#ifdef VCOP_CAMA


    printf("Freeing allocated memory \n\n");
    vcop_free(src_proc_ping );
    vcop_free(dst_proc_ping );

#endif

    profile[1] = 0xDEADBEEF;

    /*---------------------------------------------------------------*/
    /*  Now compare destination with expected destination, and see   */
    /*  if they match                                                */
    /*---------------------------------------------------------------*/

    /* ------------------------------------------------------------- */
    /* Check to make sure there are no more pending transfers        */
    /* ------------------------------------------------------------- */

    fail_dma = memcmp (CurrentLuma0, output, sizeof(CurrentLuma0));


    if (!fail_dma) printf ("Pass \n");
    else           printf ("Fail \n");

    return (!fail_dma);
}

/*-----------------------------------------------------------------------*/
/*  End of file main.c                                                   */
/*=======================================================================*/
/*  Texas Instruments incorporated 2012.                                 */
/*-----------------------------------------------------------------------*/

