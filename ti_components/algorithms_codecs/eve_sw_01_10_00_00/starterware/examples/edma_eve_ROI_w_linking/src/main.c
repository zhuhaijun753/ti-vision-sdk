/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*-----------------------------------------------------------------------*/
/*  NAME : main.c                                                        */
/*                                                                       */
/*  DESCRIPTION:                                                         */
/*                                                                       */
/*  This is a driver file for setting up double buffering of ROI blocks  */
/*  via DMA. The input is a greyscale image stored in DDR memory. A set  */
/*  of square ROIs are defined by their <x,y> origins in the arrays      */
/*  ROI_x[] and ROI_y[]. The origin is assumed to be at the top-left     */
/*  corner of the image. Each ROI is transferred from external memory    */
/*  to EVE IBUFL via linked DMA transfers. Prior to submission of the    */
/*  first transfer, the address and dimensions of each ROI block         */
/*  are written to an EDMA PARAM entry. The PARAM of subsequent          */
/*  transfers are referenced in the link address field of the prior ROI  */
/*  block's PARAM. In this example we have set up circularly linked      */
/*  transfers. For example, if we have defined six ROI blocks, A B C D E */
/*  and F, after block F has been transferred it will link back to block */
/*  A for the next transfer. Blocks are double buffered to IBUFL. For    */
/*  example, we can process block C in IBUFLA while transferring block D */
/*  to IBUFLB.                                                           */
/*                                                                       */
/*  The ROI block in IBUFL is copied to IBUFH by the vector core. In the */
/*  output direction, the processed ROI block in IBUFH is transferred to */
/*  external memory through a series of DMA autoincrememting transfers.  */
/*  These transfers place the processed ROIs contiguously in external    */
/*  memory, per the illustration below.                                  */
/*                                                                       */
/*  "Input image w 6 ROI in ext mem"            "6 ROI in ext mem"       */
/*                                              "transferred twice"      */
/*   ------------------------------                                      */
/*  | |E|                    |F|   |                 |A|                 */
/*  |     |A|                      |                 |B|                 */
/*  |                              |                 |C|                 */
/*  |               |D|            |      --->       |D|                 */
/*  |                              |                 |E|                 */
/*  | |C|                    |B|   |                 |F|                 */
/*  |                              |                 |A|                 */
/*   ------------------------------                  |B|                 */
/*                                                   |C|                 */
/*                                                   |D|                 */
/*                                                   |E|                 */
/*                                                   |F|                 */
/*                                                                       */
/*  In this example, we have setup 6 regions of interest, and have       */
/*  submitted 12 block transfers. The circular linking starts the        */
/*  transfer sequence at A again after F has been sent.                  */
/*                                                                       */
/*  ASSUMPTIONS:                                                         */
/*                                                                       */
/*  Since the vector core kernel processes data per 8 pixels in SIMD,    */
/*  the ROI block width must be a multiple of 8.                         */
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


/*-----------------------------------------------------------------------*/
/*  These are the include files that are needed for edma/qdma.           */
/*-----------------------------------------------------------------------*/

#include "csl_edma.h"
#include "cslr_edmacc.h"
#include "tistdtypes.h"
#include "image_dims.h"
#include <vcop/vcop.h>
#include "algo_dma_auto_incr.h"
#include "dma_funcs.h"
#include "dma_resource_allocator.h"
/*-----------------------------------------------------------------------*/
/*  Maintain array of sources, dests, num_bytes per line, num_lines,     */
/*  destination pitches for 6 2D -> 1D transfers.                        */
/*-----------------------------------------------------------------------*/

/* --------------------------------------------------------------------- */
/* Set ROI x,y coordinates here. Origin is assumed to be top-left corner */
/* --------------------------------------------------------------------- */

#define NUM_CHANNELS 2

unsigned int ROI_x[NUM_ROI] = {100, 405, 400, 150, 405, 250};
unsigned int ROI_y[NUM_ROI] = {100,  92, 300, 150, 134, 200};


/* --------------------------------------------------------------------- */
/* Set block dimensions for each ROI                                     */
/* --------------------------------------------------------------------- */

unsigned int ROI_w[NUM_ROI] = {DMA_BLOCK_W, DMA_BLOCK_W, DMA_BLOCK_W, DMA_BLOCK_W, DMA_BLOCK_W, DMA_BLOCK_W};
unsigned int ROI_h[NUM_ROI] = {DMA_BLOCK_H, DMA_BLOCK_H, DMA_BLOCK_H, DMA_BLOCK_H, DMA_BLOCK_H, DMA_BLOCK_H};


/* --------------------------------------------------------------------- */
/* Array of pointers to the src and destination arrays for the           */
/* transfers.                                                            */
/* --------------------------------------------------------------------- */

unsigned char *src_2d_1d[NUM_ROI];
unsigned char *dst_2d_1d[NUM_ROI];

int num_bytes_2d_1d[NUM_ROI];
int num_lines_2d_1d[NUM_ROI];

int pitch_2d_1d[NUM_ROI];


/* --------------------------------------------------------------------- */
/* Linear offset pointing to the origin of the regions of interest of    */
/* input image. The offsets are computed based on the values in the      */
/* arrays ROI_x[] and ROI_y[].                                           */
/* --------------------------------------------------------------------- */

unsigned int ROI_offset[NUM_ROI];


/* --------------------------------------------------------------------- */
/* EVE internal memory ping/pong buffers for processing                  */
/* --------------------------------------------------------------------- */

#pragma DATA_ALIGN   (src_proc_ping,  32);
#pragma DATA_ALIGN   (src_proc_pong,  32);
#pragma DATA_ALIGN   (dst_proc_ping,  32);
#pragma DATA_ALIGN   (dst_proc_pong,  32);

#pragma DATA_SECTION (src_proc_ping, "IBUFLA");
#pragma DATA_SECTION (src_proc_pong, "IBUFLB");
#pragma DATA_SECTION (dst_proc_ping, "IBUFHA");
#pragma DATA_SECTION (dst_proc_pong, "IBUFHB");

unsigned char src_proc_ping[DMA_BLOCK_W*2*DMA_BLOCK_H];
unsigned char src_proc_pong[DMA_BLOCK_W*2*DMA_BLOCK_H];
unsigned char dst_proc_ping[DMA_BLOCK_W*2*DMA_BLOCK_H];
unsigned char dst_proc_pong[DMA_BLOCK_W*2*DMA_BLOCK_H];

unsigned char *internal_mem_src;
unsigned char *internal_mem_dst;

#pragma DATA_SECTION (ROI_output, "EXT_MEM");
unsigned char ROI_output[DMA_BLOCK_W*DMA_BLOCK_H*NUM_ROI*NUM_ITER];

#pragma DATA_SECTION (ROI_ref_output, "EXT_MEM");
unsigned char ROI_ref_output[DMA_BLOCK_W*DMA_BLOCK_H*NUM_ROI*NUM_ITER];

extern unsigned char CurrentLuma0[IMG_WIDTH*IMG_HEIGHT];

/* --------------------------------------------------------------------- */
/* Natural C function prototype to copy ROI blocks. Used to verify DMA.  */
/* --------------------------------------------------------------------- */

void ROI_copy_cpu
(
    unsigned char *InputImg,
    unsigned char *ROI_output,
    unsigned int *ROI_offset,
    unsigned int num_roi,
    unsigned int num_iter,
    unsigned int blkw,
    unsigned int blkh,
    unsigned int img_pitch
);


/*-----------------------------------------------------------------------*/
/*  Zero out all buffers                                                 */
/*-----------------------------------------------------------------------*/

void dst_buffers_setup()
{
    memset (ROI_ref_output, 0x0, sizeof(ROI_ref_output));
    memset (ROI_output,     0x0, sizeof(ROI_output));
    memset (src_proc_ping,  0x0, sizeof(src_proc_ping));
    memset (dst_proc_ping,  0x0, sizeof(dst_proc_ping));
    memset (src_proc_pong,  0x0, sizeof(src_proc_pong));
    memset (dst_proc_pong,  0x0, sizeof(dst_proc_pong));
}


/*-----------------------------------------------------------------------*/
/*  Start of the main test_harness code.                                 */
/*-----------------------------------------------------------------------*/

void main()
{

    unsigned int            numChannels;
    DMA_chanAttr            dmaAttr;

    unsigned int            itccEn;
    unsigned int            tccEn;
    unsigned int            itcintEn;
    unsigned int            tcintEn;
    unsigned int            tccIn;
    unsigned int            tccOut;
    unsigned int            tccMode;
    unsigned int            fwid;
    unsigned int            stat;
    unsigned int            syncDim;
    unsigned int            dam;
    unsigned int            sam;
    unsigned int            chanIn;
    unsigned int            chanOut;

    /* ----------------------------------------------------------------- */
    /* Arrays to store event numbers, transfer complete codes            */
    /* queue numbers, and register numbers for each channel              */
    /* ----------------------------------------------------------------- */

    unsigned int            opt_2d_1d_link_no_chaining, opt_1d_2d_auto_incr;

    unsigned int            linkAddr;
    unsigned int            paramChan;
    unsigned int            in, j;

    CSL_EdmaccRegsOvly       edmaCc;

    unsigned int fail_dma;
    DMA_resourceStruct edmaResources;
    int                     status = 0;

    unsigned int            numParam;
    unsigned int            queNum;
    volatile uint32_t    *tparam;

    DMA_resourceAllocator_initResources();

    for(j = 0; j < NUM_ROI; j++)
    {
        /* --------------------------------------------------------------------- */
        /* Check to see if block width is a multiple of 8 since vector core will */
        /* process 8 pixels in SIMD.                                             */
        /* --------------------------------------------------------------------- */

        assert((ROI_w[j] % 8) == 0);

        /* --------------------------------------------------------------------- */
        /* Check to see if ROI coordinates and block dimensions fit within the   */
        /* dimensions of the input image.                                        */
        /* --------------------------------------------------------------------- */

        assert(ROI_x[j] <= (IMG_WIDTH  - ROI_w[j]));
        assert(ROI_y[j] <= (IMG_HEIGHT - ROI_h[j]));
    }


    /* --------------------------------------------------------------------- */
    /* Set memory view to alias view, and change all buffers to SYSTEM.      */
    /* --------------------------------------------------------------------- */

    VCOP_SET_MEM_VIEW (ALIAS_128K_VIEW);
    VCOP_BUF_SWITCH_SET (WBUF_SYST, IBUFHB_SYST, IBUFHA_SYST, IBUFLB_SYST, IBUFLA_SYST);


    /*-----------------------------------------------------------------------*/
    /*  In this function we will zero all destinations and EVE IBUFs.        */
    /*-----------------------------------------------------------------------*/

    dst_buffers_setup();


    /*-----------------------------------------------------------------------*/
    /*  Anchor edmaCc to the start of the EDMA CC0, we only have one        */
    /*  CC so it is CC0.                                                     */
    /*-----------------------------------------------------------------------*/

    edmaCc  =  (CSL_EdmaccRegsOvly) (CSL_EDMACC_0_REGS);
    printf ("edmaCc:0x%.8x \n", edmaCc);
    assert ((unsigned int)edmaCc == 0x400a0000);


    /* --------------------------------------------------------------------- */
    /* Set pointers to EVE internal memories IBUFL and IBUFH that the vector */
    /* will get ROI blocks for EVE processing. Since we are in aliased view  */
    /* we set the pointers to IBUFLA and IBUFHA, and use the                 */
    /* VCOP_BUF_SWITCH_TOGGLE macro to switch between ping and pong buffers. */
    /* --------------------------------------------------------------------- */

    internal_mem_src = src_proc_ping;
    internal_mem_dst = dst_proc_ping;


    /* --------------------------------------------------------------------- */
    /* Write ROI block origins, widths, and heights to arrays.               */
    /* --------------------------------------------------------------------- */

    for(j = 0; j < NUM_ROI; j++)
    {
            ROI_offset[j]      = (ROI_y[j]*IMG_WIDTH) + ROI_x[j];

            src_2d_1d[j]       = (unsigned char *)(CurrentLuma0 +  ROI_offset[j]);
            dst_2d_1d[j]       = (unsigned char *)internal_mem_src;

            num_bytes_2d_1d[j] = ROI_w[j];
            num_lines_2d_1d[j] = ROI_h[j];

            pitch_2d_1d[j]     = IMG_WIDTH;
    }


    /* --------------------------------------------------------------------- */
    /* Configure channel for EDMA transfer. We will use two channels, one    */
    /* for the input transfer and one for the output transfer.               */
    /* --------------------------------------------------------------------- */

    dmaAttr       =       DMA_CHAN_ATTR_EDMA;
    numChannels   =       NUM_CHANNELS;

    /* Request EDMA resources for numChannels */
    edmaResources.numChannels   = numChannels;
    for ( j = 0 ; j < NUM_CHANNELS ; j++)
    {
        /*---------------------------------------------------------------*/
        /* Number of PaRAM entries for linked transfer                   */
        /*---------------------------------------------------------------*/
        edmaResources.numParam[j]       = NUM_ROI + 1;
        edmaResources.dmaAttr[j]        = dmaAttr;
        edmaResources.queNo[j]          = 0;
    }


    status = DMA_resourceAllocator_allocateResources(edmaCc,&edmaResources);


    if ( status == 0 )
    {
        DMA_funcs_hardwareRegSetup(edmaCc,&edmaResources);
    }


    /* ------------------------------------------------------------- */
    /* Set options field for input and output transfers              */
    /* ------------------------------------------------------------- */

    chanOut   =  edmaResources.logicalChannelNo[0];
    itccEn     =  CSL_EDMACC_OPT_ITCCHEN_DISABLE;
    tccEn      =  CSL_EDMACC_OPT_TCCHEN_DISABLE;
    itcintEn   =  CSL_EDMACC_OPT_ITCINTEN_ENABLE;
    tcintEn    =  CSL_EDMACC_OPT_TCINTEN_ENABLE;
    tccOut    =  edmaResources.tccVal[chanOut];
    tccMode    =  CSL_EDMACC_OPT_TCCMODE_NORMAL;
    fwid       =  CSL_EDMACC_OPT_FWID_8;
    stat       =  CSL_EDMACC_OPT_STATIC_NORMAL;
    syncDim    =  CSL_EDMACC_OPT_SYNCDIM_ABSYNC;
    dam        =  CSL_EDMACC_OPT_DAM_INCR;
    sam        =  CSL_EDMACC_OPT_SAM_INCR;

    opt_1d_2d_auto_incr  =
    CSL_EDMA_OPT_MAKE
    (itccEn,tccEn,itcintEn,tcintEn,tccOut,tccMode,fwid,stat,syncDim,dam,sam);

    /* ------------------------------------------------------------- */
    /* 1D to 2D, INT to EXT Transfers                                */
    /* ------------------------------------------------------------- */
    DMA_funcs_writeTransferParams(edmaResources.baseParam[chanOut],
                            opt_1d_2d_auto_incr,
                            internal_mem_dst,
                            ROI_output,
                            DMA_BLOCK_W,
                            DMA_BLOCK_H,
                            DMA_BLOCK_W,
                            DMA_BLOCK_W,
                            0,
                           (DMA_BLOCK_W*DMA_BLOCK_H),
                           NUM_AUTO_INCR,
                           0);


    chanIn    =  edmaResources.logicalChannelNo[1];
    itccEn     =  CSL_EDMACC_OPT_ITCCHEN_DISABLE;
    tccEn      =  CSL_EDMACC_OPT_TCCHEN_DISABLE;
    itcintEn   =  CSL_EDMACC_OPT_ITCINTEN_DISABLE;
    tcintEn    =  CSL_EDMACC_OPT_TCINTEN_ENABLE;
    tccIn     =  edmaResources.tccVal[chanIn];
    tccMode    =  CSL_EDMACC_OPT_TCCMODE_NORMAL;
    fwid       =  CSL_EDMACC_OPT_FWID_8;
    stat       =  CSL_EDMACC_OPT_STATIC_NORMAL;
    syncDim    =  CSL_EDMACC_OPT_SYNCDIM_ABSYNC;
    dam        =  CSL_EDMACC_OPT_DAM_INCR;
    sam        =  CSL_EDMACC_OPT_SAM_INCR;

    opt_2d_1d_link_no_chaining  =
    CSL_EDMA_OPT_MAKE
    (itccEn,tccEn,itcintEn,tcintEn,tccIn,tccMode,fwid,stat,syncDim,dam,sam);


    paramChan   = (unsigned int) edmaResources.baseParam[chanIn];
    linkAddr    =  paramChan + 32;
    tparam = edmaResources.baseParam[chanIn];

    /*---------------------------------------------------------------*/
    /*  We want to do 6 linked transfers. We setup a loop and keep   */
    /*  incrementing the link_address by 32 bytes.                   */
    /*---------------------------------------------------------------*/

    for (j = 0; j < NUM_ROI; j++)
    {
        linkAddr   &= 0xFFFF;

        DMA_funcs_writeTransferParams(tparam,
                            opt_2d_1d_link_no_chaining,
                            src_2d_1d[j],
                            dst_2d_1d[j],
                            num_bytes_2d_1d[j],
                            num_lines_2d_1d[j],
                            pitch_2d_1d[j],
                            num_bytes_2d_1d[j],
                            0,
                            0x0,
                            0x1,
                            linkAddr);

        tparam     = tparam + (8);
        linkAddr  += 32;
    }

    in          = 0;
    linkAddr   =  paramChan + 32;
    linkAddr   &= 0xFFFF;

    /* ------------------------------------------------------------- */
    /* To make the link circular, we create an additional PARAM      */
    /* entry that will link back to the first ROI here.              */
    /* ------------------------------------------------------------- */
    DMA_funcs_writeTransferParams(tparam,
                            opt_2d_1d_link_no_chaining,
                            src_2d_1d[in],
                            dst_2d_1d[in],
                            num_bytes_2d_1d[in],
                            num_lines_2d_1d[in],
                            pitch_2d_1d[in],
                            num_bytes_2d_1d[in],
                            0x0,
                            0x0,
                            0x1,
                            linkAddr);



    /* ------------------------------------------------------------- */
    /* Call algo_dma_auto_incr:                                      */
    /* This function implements dma double buffering with linking    */
    /* for ROI block transfers to internal memory and                */
    /* autoincrementing for output transfers. Within this subroutine */
    /* a vector core function (vcop_copy_data_per_8) is called       */
    /* that will copy the source block to the destination block      */
    /* before it is transferred to external memory.                  */
    /* ------------------------------------------------------------- */

    algo_dma_auto_incr
    (
        edmaCc,
        &edmaResources,
        internal_mem_src,
        internal_mem_dst,
        chanIn,
        chanOut,
        0
     );

    DMA_resourceAllocator_deallocateResources(edmaCc,&edmaResources);

    /*---------------------------------------------------------------*/
    /*  Assert that all previous interrupts have been cleared and    */
    /*  serviced.                                                    */
    /*---------------------------------------------------------------*/

    assert (edmaCc->IPR == 0);


    /* ------------------------------------------------------------- */
    /* C routine that uses the scalar core to copy the ROI blocks to */
    /* the reference array. The output of this routine is used       */
    /* to verify the EDMA transfers.                                 */
    /* ------------------------------------------------------------- */

    ROI_copy_cpu
    (
        CurrentLuma0,
        ROI_ref_output,
        ROI_offset,
        NUM_ROI,
        NUM_ITER,
        DMA_BLOCK_W,
        DMA_BLOCK_H,
        IMG_WIDTH
    );

    /*---------------------------------------------------------------*/
    /*  Now compare destination with expected destination, and see   */
    /*  if they match                                                */
    /*---------------------------------------------------------------*/

    fail_dma = (memcmp(ROI_output, ROI_ref_output, sizeof(ROI_output)));

    printf("\n------------------------EDMA_CHAN---------------------------------\n");

    if (fail_dma != 0)
    {
        printf ("ROI transfers failed!\n");
    }
    else
    {
        printf ("ROI transfers passed!\n");
    }

    printf("------------------------------------------------------------------\n\n\n");

}

/*-----------------------------------------------------------------------*/
/*  End of file main.c                                                   */
/*=======================================================================*/
/*  Texas Instruments incorporated 2002-2006.                            */
/*-----------------------------------------------------------------------*/

