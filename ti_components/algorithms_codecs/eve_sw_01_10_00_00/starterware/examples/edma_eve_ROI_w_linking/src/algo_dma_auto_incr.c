/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*-----------------------------------------------------------------------*/
/*  NAME : algo_dma_auto_incr.c                                          */
/*                                                                       */
/*  DESCRIPTION:                                                         */
/*                                                                       */
/*  This file demonstrates double buffering of data from external ->     */
/*  internal memory, and internal -> external memory on an image frame   */
/*  for ROI processing. The input is a greyscale image stored in DDR.    */
/*  A set of square ROIs are defined by their <x,y> origins in           */
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
/*  external memory through a series of DMA autoincrementing transfers.  */
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
/*=======================================================================*/
/*  Texas Instruments incorporated 2012.                                 */
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

#include "dma_funcs.h"
#include "algo_dma_auto_incr.h"
#include "image_dims.h"
#include <vcop/vcop.h>
#include "vcop_copy_data_per_8.h"

extern unsigned short __pblock_vcop_copy_data_per_8[10];

void algo_dma_auto_incr
(
    CSL_EdmaccRegsOvly  edma_cc,
    DMA_resourceStruct *edmaResources,
    unsigned char       *src_proc,
    unsigned char       *dst_proc,
    unsigned int        chan_in,
    unsigned int        chan_out,
    Bool                *trf_pend
)
{
    unsigned int            j;

    unsigned int            tcc_in;
    unsigned int            tcc_out;

    /* ----------------------------------------------------- */
    /* ESR values for each event                             */
    /* ----------------------------------------------------- */

    unsigned int            evt_no_set_in;
    unsigned int            evt_no_set_out;

    /* ----------------------------------------------------- */
    /* Words used to set register values for DMA submission  */
    /* and completion. These will be passed as arguments to  */
    /* the DMA_SUBMIT() and DMA_WAIT macros to trigger       */
    /* transfers and wait for completion.                    */
    /* ----------------------------------------------------- */

    unsigned int            wait_word_in, wait_word_out, wait_word_in_out;
    unsigned int            submit_word_in, submit_word_out, submit_word_in_out;

    unsigned int            num_wpreg_params;
    unsigned int            flag;

    /* -------------------------------------------------------------------- */
    /* Precompute the transfer complete codes and event set register values */
    /* that will be passed into the DMA_WAIT and DMA_SUBMIT macros. These   */
    /* macros are used to start transfers and check for completion.         */
    /* -------------------------------------------------------------------- */

    tcc_in          =    0x1 << edmaResources->tccVal[chan_in];
    tcc_out         =    0x1 << edmaResources->tccVal[chan_out];

    evt_no_set_in   =    (CSL_EDMACC_ESR_E0_SET << edmaResources->logicalChannelNo[chan_in]);
    evt_no_set_out  =    (CSL_EDMACC_ESR_E0_SET << edmaResources->logicalChannelNo[chan_out]);

    wait_word_in       =    (tcc_in);
    wait_word_out      =    (tcc_out);
    wait_word_in_out   =    (tcc_in | tcc_out);

    submit_word_in_out =    (evt_no_set_in | evt_no_set_out);
    submit_word_in     =    evt_no_set_in;
    submit_word_out    =    evt_no_set_out;


    /* ------------------------------------------------------------- */
    /* Prologue                                                      */
    /* ------------------------------------------------------------- */

    num_wpreg_params = vcop_copy_data_per_8_init(src_proc, dst_proc, DMA_BLOCK_W, DMA_BLOCK_H, __pblock_vcop_copy_data_per_8);

    /*---------------------------------------------------------------*/
    /*  Set transfer pending status flag, to indicate that transfer  */
    /*  is in progress.                                              */
    /*---------------------------------------------------------------*/

    *trf_pend  =  TRUE;


    VCOP_BUF_SWITCH_SET (WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP, IBUFHA_SYST, IBUFLA_SYST);

    flag = BUF_PING;

    DMA_SUBMIT(edma_cc, submit_word_in);
    DMA_WAIT(edma_cc, wait_word_in);


    for(j = 0; j < (NUM_ROI*NUM_ITER); j++)
    {
        flag = VCOP_BUF_SWITCH_TOGGLE (flag);

        if(j == 0)                             {DMA_SUBMIT(edma_cc, submit_word_in);}
        else if(j == ((NUM_ROI*NUM_ITER) - 1)) {DMA_SUBMIT(edma_cc, submit_word_out);}
        else                                   {DMA_SUBMIT(edma_cc, submit_word_in_out);}

        /* ------------------------------------------------------------- */
        /* Use VCOP to copy data from IBUFL to IBUFH while DMA transfers */
        /* are occuring.                                                 */
        /* ------------------------------------------------------------- */

        vcop_copy_data_per_8_vloops(__pblock_vcop_copy_data_per_8);

        /* ------------------------ */
        /* Wait for VCOP to be done */
        /* ------------------------ */

        _vcop_vloop_done();

        if(j == 0)                             {DMA_WAIT(edma_cc, wait_word_in);}
        else if(j == ((NUM_ROI*NUM_ITER) - 1)) {DMA_WAIT(edma_cc, wait_word_out);}
        else                                   {DMA_WAIT(edma_cc, wait_word_in_out);}
    }

    /* ------------------------------------------------------------------ */
    /* Epilogue                                                           */
    /* ------------------------------------------------------------------ */

    flag = VCOP_BUF_SWITCH_TOGGLE (flag);

    DMA_SUBMIT(edma_cc, submit_word_out);
    DMA_WAIT(edma_cc, wait_word_out);


    /*---------------------------------------------------------------*/
    /*  Clear trf_pend status, as we have finished waiting on trans. */
    /*---------------------------------------------------------------*/

    *trf_pend   = FALSE;
}

