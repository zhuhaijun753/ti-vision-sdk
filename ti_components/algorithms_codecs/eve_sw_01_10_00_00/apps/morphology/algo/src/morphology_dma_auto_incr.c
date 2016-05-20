/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*-----------------------------------------------------------------------*/
/*  NAME : morphology_dma_auto_incr.c                                       */
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
#include <vcop.h>
#if (!VCOP_HOST_EMULATION)
#include <arp32.h>
#else
#include <vcop_host.h>
#endif

/*-----------------------------------------------------------------------*/
/*  These are the include files that are needed for edma/qdma.           */
/*-----------------------------------------------------------------------*/
#include "evestarterware.h"
#include "edma_utils_autoincrement.h"
#include "edma_utils_context_size.h"
#include "edma_utils.h"

#include "morphology_dma_auto_incr.h"

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */
#define ALIGN(x,y)         (((x) + (y) - 1U)/(y))*(y)
/* RESET_MISRA("19.7")  -> Reset rule 19.7     */


/* --------------------------------------------------------------------- */
/*  Start of the main test_harness code.                                 */
/* --------------------------------------------------------------------- */
int32_t morphology_DMAAutoIncrInit(
                              uint8_t       *autoIncrementContext,
                              uint8_t       *src,
                              uint32_t       srcImageWidth,
                              uint32_t       srcImageHeight,
                              int32_t        srcImagePitch,
                              uint8_t       *dst,
                              uint32_t       dstImageWidth,
                              uint32_t       dstImageHeight,
                              int32_t        dstImagePitch,
                              uint8_t       *srcBlk,
                              uint32_t       srcBlkWidth,
                              uint32_t       srcBlkHeight,
                              int32_t        srcBlkPitch,
                              uint8_t       *dstBlk,
                              uint32_t       dstBlkWidth,
                              uint32_t       dstBlkHeight,
                              int32_t        dstBlkPitch,
                              uint32_t       srcBlkPadX,
                              uint32_t       srcBlkPadY)
{

    EDMA_UTILS_autoIncrement_initParam initParam;
    int32_t status = 0;

    /* Reset the global State Structure */
    EDMA_UTILS_globalReset();

    VCOP_SET_MEM_VIEW ((uint32_t)ALIAS_128K_VIEW);
    VCOP_BUF_SWITCH_SET (WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    /*vcop_setview(VCOP_MEMALIASED);*/

    /* ------------------------------------------------------------------ */
    /* Configure channel for EDMA transfer. We will use two channels, one */
    /* for the input transfer and one for the output transfer.            */
    /* ------------------------------------------------------------------ */

    initParam.numInTransfers    = 1;
    initParam.numOutTransfers   = 1;
    initParam.transferType      = EDMA_UTILS_TRANSFER_INOUT;

    initParam.transferProp[0].roiWidth             = (ALIGN((srcImageWidth  - srcBlkPadX), srcBlkWidth))  + srcBlkPadX;
    initParam.transferProp[0].roiHeight            = (ALIGN((srcImageHeight - srcBlkPadY), srcBlkHeight)) + srcBlkPadY;
    initParam.transferProp[0].roiOffset            = 0;
    initParam.transferProp[0].blkWidth             = srcBlkWidth  + srcBlkPadX;
    initParam.transferProp[0].blkHeight            = srcBlkHeight + srcBlkPadY;
    initParam.transferProp[0].extBlkIncrementX     = srcBlkWidth;
    initParam.transferProp[0].extBlkIncrementY     = srcBlkHeight;
    initParam.transferProp[0].intBlkIncrementX     = 0;
    initParam.transferProp[0].intBlkIncrementY     = 0;
    initParam.transferProp[0].extMemPtrStride      = srcImagePitch;
    initParam.transferProp[0].interMemPtrStride    = srcBlkPitch;
    initParam.transferProp[0].extMemPtr            = src;
    initParam.transferProp[0].interMemPtr          = srcBlk;
    initParam.transferProp[0].dmaQueNo             = 0;

    initParam.transferProp[1].roiWidth             = ALIGN(dstImageWidth,  dstBlkWidth);
    initParam.transferProp[1].roiHeight            = ALIGN(dstImageHeight, dstBlkHeight);
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
    initParam.transferProp[1].dmaQueNo             = 1;

    EDMA_UTILS_autoIncrement_init(autoIncrementContext,&initParam);

    status = EDMA_UTILS_autoIncrement_configure(autoIncrementContext , EDMA_UTILS_TRANSFER_INOUT);

    return status;
}


void morphology_DMAAutoIncrDeInit(void)
{
    /* ------------------------------------------------------------- */
    /* Clear the event registers                                     */
    /* ------------------------------------------------------------- */
    EDMA_UTILS_globalReset();
}



void morphology_DMAAutoIncrExec(
                                    uint8_t                 *autoIncrementContext,
                                    EVELIB_KernelFuncType    execFunc[],
                                    EVELIB_KernelContextType context[],
                                    uint8_t                  numKernels)
{
    uint32_t flag, k;
    int32_t  sinkStatus = 0;

    /* ----------------------------------------------------------------- */
    /* Processing loop begins here                                       */
    /* ----------------------------------------------------------------- */
    flag = (uint32_t)BUF_PING;
    VCOP_BUF_SWITCH_SET (WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP, IBUFHA_SYST, IBUFLA_SYST);

#if (!VCOP_HOST_EMULATION)
    /* ------------------------------------------------------------- */
    /* Prologue:                                                     */
    /* Get First Block In                                           */
    /* ------------------------------------------------------------- */
    EDMA_UTILS_autoIncrement_triggerInChannel(autoIncrementContext);
    EDMA_UTILS_autoIncrement_waitInChannel(autoIncrementContext);
#endif

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
    VCOP_BUF_SWITCH_TOGGLE (flag);

    EDMA_UTILS_autoIncrement_triggerOutChannel(autoIncrementContext);
    EDMA_UTILS_autoIncrement_waitOutChannel(autoIncrementContext);

    /*---------------------------------------------------------------*/
    /*  Return all buffers to system before returning.               */
    /*---------------------------------------------------------------*/
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);
}

/*-----------------------------------------------------------------------*/
/*  End of file algo_dma_auto_incr.c                                     */
/*=======================================================================*/
