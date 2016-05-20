/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*-----------------------------------------------------------------------*/
/*  NAME : eve_algo_dma_auto_incr.c                                       */
/*                                                                       */
/*  DESCRIPTION:                                                         */
/*                                                                       */
/*  This file demonstrates double buffering of data from external ->     */
/*  internal memory, and internal -> external memory on an image frame.  */
/*  Data from the image frame is transferred to internal memory on a     */
/*  block by block basis.                                                */
/*                                                                       */
/*  2D -> 1D transfers are used for incoming data and 1D -> 2D transfers */
/*  are used for outgoing data. Two parameter registers are used, 1 for  */
/*  the incoming ping/pong buffers and 1 for the outgoing ping/pong      */
/*  buffers.                                                             */
/*                                                                       */
/*  Autoincrementing at each DMA block transfer completion is used to    */
/*  to reduce the number of times entries in the parameter ram need to   */
/*  be updated. At the end of each block-row, the src and dst pointers   */
/*  are updated in the parameter ram to reflect the starting addresses   */
/*  of the next row of blocks.                                           */
/*-----------------------------------------------------------------------*/



/*-----------------------------------------------------------------------*/
/*  Standard header includes for c environment.                          */
/*-----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <vcop/vcop.h>
#include <arp32.h>

/*-----------------------------------------------------------------------*/
/*  These are the include files that are needed for edma/qdma.           */
/*-----------------------------------------------------------------------*/
#include "evestarterware.h"
#include "edma_utils_autoincrement.h"
#include "edma_utils_context_size.h"
#include "edma_utils.h"

#include "eve_algo_dma_auto_incr.h"

#define AETCTL_OFFSET (0x0700)


#pragma DATA_SECTION (autoIncrementContext, ".edmaUtilsMem");
unsigned char autoIncrementContext[EDMA_UTILS_AUTOINCREMENT_CONTEXT_SIZE];


/**
* @brief Get the best block dimensions
* @remarks Assumes that either the buffer dimensions or the image dimensions (in bytes) must be a multiple of 16x8.
  For best performance, either the buffer dimensions or the image dimensions (in bytes) must be a multiple
* of 64x32 or 32x16
*/
uint32_t EVELIB_getBestBlockDimensions(uint32_t imageWidthBypes, uint32_t imageHeight, uint32_t bufferPitch, uint32_t bufferHeight,
    uint32_t *procWidth, uint32_t *procHeight, uint32_t *blockWidth, uint32_t *blockHeight)
{
    uint32_t perfVal = 0;

    *blockWidth = ((imageWidthBypes%64)==0 || (bufferPitch%64)==0)? 64 : \
        (((imageWidthBypes%32)==0 || (bufferPitch%32)==0)? 32 : 16);

    *blockHeight = ((imageHeight%32==0) || (bufferHeight%32)==0)? 32 :  \
        (((imageHeight%16==0) || (bufferHeight%16)==0)? 16 : 8);

     *procWidth = (imageWidthBypes%(*blockWidth))? imageWidthBypes : bufferPitch;
     *procHeight = (imageHeight%(*blockHeight))? imageHeight : bufferHeight;

     perfVal = (((*blockWidth)%64) && ((*blockHeight)%32));

     return perfVal;
}



/* --------------------------------------------------------------------- */
/*  Start of the main test_harness code.                                 */
/* --------------------------------------------------------------------- */
int EVELIB_algoDMAAutoIncrInit(
    unsigned char       *src,
    unsigned int        srcImageWidth,
    unsigned int        srcImageHeight,
    int                 srcImagePitch,
    unsigned char       *dst,
    unsigned int        dstImageWidth,
    unsigned int        dstImageHeight,
    int                 dstImagePitch,
    unsigned char       *srcBlk,
    unsigned int        srcBlkWidth,
    unsigned int        srcBlkHeight,
    int                 srcBlkPitch,
    unsigned char       *dstBlk,
    unsigned int        dstBlkWidth,
    unsigned int        dstBlkHeight,
    int                 dstBlkPitch,
    unsigned int        srcBlkPadX,
    unsigned int        srcBlkPadY)
{

    EDMA_UTILS_autoIncrement_initParam initParam;
    int32_t status = 0;

    /* Reset the global State Structure */
    EDMA_UTILS_globalReset();

    VCOP_SET_MEM_VIEW (ALIAS_128K_VIEW);
    VCOP_BUF_SWITCH_SET (WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    /*vcop_setview(VCOP_MEMALIASED);*/

    /* ------------------------------------------------------------------ */
    /* Configure channel for EDMA transfer. We will use two channels, one */
    /* for the input transfer and one for the output transfer.            */
    /* ------------------------------------------------------------------ */

    initParam.numInTransfers    = 1;
    initParam.numOutTransfers   = 1;
    initParam.transferType      = EDMA_UTILS_TRANSFER_INOUT;

    initParam.transferProp[0].roiWidth             = srcImageWidth+srcBlkPadX;
    initParam.transferProp[0].roiHeight            = srcImageHeight+srcBlkPadY;
    initParam.transferProp[0].roiOffset            = 0;
    initParam.transferProp[0].blkWidth             = srcBlkWidth+srcBlkPadX;
    initParam.transferProp[0].blkHeight            = srcBlkHeight+srcBlkPadY;
    initParam.transferProp[0].extBlkIncrementX     = srcBlkWidth;
    initParam.transferProp[0].extBlkIncrementY     = srcBlkHeight;
    initParam.transferProp[0].intBlkIncrementX     = 0;
    initParam.transferProp[0].intBlkIncrementY     = 0;
    initParam.transferProp[0].extMemPtrStride      = srcImagePitch;
    initParam.transferProp[0].interMemPtrStride    = srcBlkPitch;
    initParam.transferProp[0].extMemPtr            = src;
    initParam.transferProp[0].interMemPtr          = srcBlk;
    initParam.transferProp[0].dmaQueNo             = 0;


    initParam.transferProp[1].roiWidth             = dstImageWidth;
    initParam.transferProp[1].roiHeight            = dstImageHeight;
    initParam.transferProp[1].roiOffset            = 0;
    initParam.transferProp[1].blkWidth             = dstBlkWidth;
    initParam.transferProp[1].blkHeight            = dstBlkHeight;
    initParam.transferProp[1].extBlkIncrementX     = dstBlkWidth;
    initParam.transferProp[1].extBlkIncrementY     = dstBlkHeight;
    initParam.transferProp[1].intBlkIncrementX     = 0;
    initParam.transferProp[1].intBlkIncrementY     = 0;
    initParam.transferProp[1].extMemPtrStride      = dstImagePitch;
    initParam.transferProp[1].interMemPtrStride    = dstBlkPitch;
    initParam.transferProp[1].extMemPtr            = dst;
    initParam.transferProp[1].interMemPtr          = dstBlk;
    initParam.transferProp[1].dmaQueNo             = 0;

    status = EDMA_UTILS_autoIncrement_init(autoIncrementContext,&initParam);

    if ( status == 0 )
    {
        status = EDMA_UTILS_autoIncrement_configure(autoIncrementContext , EDMA_UTILS_TRANSFER_INOUT);
    }

#if 0
    /* ------------------------------------------------------------- */
    /* Options field calculation for 1D src to 2D dst.               */
    /* Channel assignment to output ping/pong buffers.               */
    /* These will be written to PARAM.                               */
    /* ------------------------------------------------------------- */
    chan_out   =  0x1;
    tcc_out    =  dma_state_struct->tcc_val[chan_out];

    evt_no_set_in   =    (CSL_EDMACC_ESR_E0_SET << dma_state_struct->physical_chan[chan_in]);
    evt_no_set_out  =    (CSL_EDMACC_ESR_E0_SET << dma_state_struct->physical_chan[chan_out]);

    if (evt_no_set_out > evt_no_set_in)
    AETCTL[0]       =    0x80000000 + evt_no_set_in  + (dma_state_struct->tcc_val[chan_out] << 8);
    else
    AETCTL[0]       =    0x80000000 + evt_no_set_out + (dma_state_struct->tcc_val[chan_in] << 8);

#endif

    return status;
}


void EVELIB_algoDMAAutoIncrDeInit()
{
    /* ------------------------------------------------------------- */
    /* Clear the event registers                                     */
    /* ------------------------------------------------------------- */
    //dma_global_regs_teardown (edma_cc, dma_state_struct);
    EDMA_UTILS_globalReset();
}



void EVELIB_algoDMAAutoIncrConcurrent
(
    unsigned char       *src,
    unsigned int        srcImageWidth,
    unsigned int        srcImageHeight,
    int                 srcImagePitch,
    unsigned char       *dst,
    unsigned int        dstImageWidth,
    unsigned int        dstImageHeight,
    int                 dstImagePitch,
    unsigned char       *srcBlk,
    unsigned int        srcBlkWidth,
    unsigned int        srcBlkHeight,
    int                 srcBlkPitch,
    unsigned char       *dstBlk,
    unsigned int        dstBlkWidth,
    unsigned int        dstBlkHeight,
    int                 dstBlkPitch,
    unsigned int        srcBlkPadX,
    unsigned int        srcBlkPadY,
    EVELIB_KernelFuncType execFunc[],
    EVELIB_KernelContextType context[],
    unsigned int        numKernels
)
{
    unsigned int        flag;
    int                 sinkStatus = 0;
    int                  k;


    VCOP_BUF_SWITCH_SET (WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    /* ----------------------------------------------------------------- */
    /* Processing loop begins here                                       */
    /* ----------------------------------------------------------------- */
    flag = BUF_PING;
    VCOP_BUF_SWITCH_SET (WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP, IBUFHA_SYST, IBUFLA_SYST);


    /* ------------------------------------------------------------- */
    /* Prologue:                                                     */
    /* Get First Block In                                           */
    /* ------------------------------------------------------------- */
    EDMA_UTILS_autoIncrement_triggerInChannel(autoIncrementContext);
    EDMA_UTILS_autoIncrement_waitInChannel(autoIncrementContext);

    while (sinkStatus != 1)
    {

        flag = VCOP_BUF_SWITCH_TOGGLE (flag);

        sinkStatus = EDMA_UTILS_autoIncrement_triggerOutChannel(autoIncrementContext);
        EDMA_UTILS_autoIncrement_triggerInChannel(autoIncrementContext);

        /* ------------------------------------- */
        /* Submit the remaining kernels to VCOP  */
        /* ------------------------------------- */
        for(k=0; k<numKernels; k++)
        {
            (execFunc[k])(context[k]);
        }

        /* ------------------------------------------------------------- */
        /*  Check for completion of first horizontal block before        */
        /*  before entering inner loop.                                  */
        /* ------------------------------------------------------------- */
        EDMA_UTILS_autoIncrement_waitOutChannel(autoIncrementContext);
        EDMA_UTILS_autoIncrement_waitInChannel(autoIncrementContext);

        /* ------------------------ */
        /* Wait for VCOP to be done */
        /* ------------------------ */
        _vcop_vloop_done();

    }

    /*-------------------------------------------------------------------*/
    /*  Epilogue:                                                        */
    /*  Transfer the last processed block in the row                     */
    /* ----------------------------------------------------------------- */
    flag = VCOP_BUF_SWITCH_TOGGLE (flag);

    sinkStatus = EDMA_UTILS_autoIncrement_triggerOutChannel(autoIncrementContext);
    EDMA_UTILS_autoIncrement_waitOutChannel(autoIncrementContext);

    /*---------------------------------------------------------------*/
    /*  Return all buffers to system before returning.               */
    /*---------------------------------------------------------------*/
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);


}



void EVELIB_algoDMAAutoIncrSequential
(
    unsigned char       *src,
    unsigned int        srcImageWidth,
    unsigned int        srcImageHeight,
    int                 srcImagePitch,
    unsigned char       *dst,
    unsigned int        dstImageWidth,
    unsigned int        dstImageHeight,
    int                 dstImagePitch,
    unsigned char       *srcBlk,
    unsigned int        srcBlkWidth,
    unsigned int        srcBlkHeight,
    int                 srcBlkPitch,
    unsigned char       *dstBlk,
    unsigned int        dstBlkWidth,
    unsigned int        dstBlkHeight,
    int                 dstBlkPitch,
    unsigned int        srcBlkPadX,
    unsigned int        srcBlkPadY,
    EVELIB_KernelFuncType execFunc[],
    EVELIB_KernelContextType context[],
    unsigned int        numKernels
)
{
    int                 sinkStatus = 0;
    int                 k;


    VCOP_BUF_SWITCH_SET (WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);


    /* Get First Block In */
    /*First Dummy Transfer */
    sinkStatus = EDMA_UTILS_autoIncrement_triggerOutChannel(autoIncrementContext);
    EDMA_UTILS_autoIncrement_waitOutChannel(autoIncrementContext);

    while (sinkStatus != 1)
    {

        EDMA_UTILS_autoIncrement_triggerInChannel(autoIncrementContext);
        EDMA_UTILS_autoIncrement_waitInChannel(autoIncrementContext);

        VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP, IBUFHA_VCOP, IBUFLA_VCOP);
        /* ------------------------------------- */
        /* Submit the remaining kernels to VCOP  */
        /* ------------------------------------- */
        for(k=0; k<numKernels; k++)
        {
            (execFunc[k])(context[k]);
        }
        /* ------------------------ */
        /* Wait for VCOP to be done */
        /* ------------------------ */
        _vcop_vloop_done();
        VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

        sinkStatus = EDMA_UTILS_autoIncrement_triggerOutChannel(autoIncrementContext);
        EDMA_UTILS_autoIncrement_waitOutChannel(autoIncrementContext);


    }

    sinkStatus = EDMA_UTILS_autoIncrement_triggerOutChannel(autoIncrementContext);
    EDMA_UTILS_autoIncrement_waitOutChannel(autoIncrementContext);

    /*---------------------------------------------------------------*/
    /*  Return all buffers to system before returning.               */
    /*---------------------------------------------------------------*/
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

}

void EVELIB_algoDMAAutoIncrProcess
(
     unsigned char       *src,
    unsigned int        srcImageWidth,
    unsigned int        srcImageHeight,
    int                 srcImagePitch,
    unsigned char       *dst,
    unsigned int        dstImageWidth,
    unsigned int        dstImageHeight,
    int                 dstImagePitch,
    unsigned char       *srcBlk,
    unsigned int        srcBlkWidth,
    unsigned int        srcBlkHeight,
    int                 srcBlkPitch,
    unsigned char       *dstBlk,
    unsigned int        dstBlkWidth,
    unsigned int        dstBlkHeight,
    int                 dstBlkPitch,
    unsigned int        srcBlkPadX,
    unsigned int        srcBlkPadY,
    EVELIB_KernelFuncType execFunc[],
    EVELIB_KernelContextType context[],
    unsigned int        numKernels,
    int32_t             sequential
)
{
    if(sequential)
    {
        EVELIB_algoDMAAutoIncrSequential
        (
             src,
            srcImageWidth,
            srcImageHeight,
            srcImagePitch,
            dst,
            dstImageWidth,
            dstImageHeight,
            dstImagePitch,
            srcBlk,
            srcBlkWidth,
            srcBlkHeight,
            srcBlkPitch,
            dstBlk,
            dstBlkWidth,
            dstBlkHeight,
            dstBlkPitch,
            srcBlkPadX,
            srcBlkPadY,
            execFunc,
            context,
            numKernels
        );
    }
    else
    {
        EVELIB_algoDMAAutoIncrConcurrent
        (
             src,
            srcImageWidth,
            srcImageHeight,
            srcImagePitch,
            dst,
            dstImageWidth,
            dstImageHeight,
            dstImagePitch,
            srcBlk,
            srcBlkWidth,
            srcBlkHeight,
            srcBlkPitch,
            dstBlk,
            dstBlkWidth,
            dstBlkHeight,
            dstBlkPitch,
            srcBlkPadX,
            srcBlkPadY,
            execFunc,
            context,
            numKernels
        );
    }
}



/*-----------------------------------------------------------------------*/
/*  End of file algo_dma_auto_incr.c                                     */
/*=======================================================================*/
