/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#pragma CHECK_MISRA ("none")
#include <stdint.h>
#include <string.h>
#pragma RESET_MISRA ("required")

#include "dma_funcs.h"
#include "dma_resource_allocator.h"

#include "evelib_memcopy_dma_2d.h"

static void evelib_EDMAInitInt(DMA_resourceStruct * edmaResources);

void EVELIB_memcopyDMA2D(uint8_t     *sourcePtr,
                   uint8_t      *destPtr,
                   uint32_t     widthBytes,
                   uint32_t     height,
                   int32_t      srcStride,
                   int32_t      dstStride)
{
    DMA_resourceStruct   edmaResources;
    CSL_EdmaccRegsOvly    edmaCc;
    uint32_t            itccEn = 0;
    uint32_t            tccEn = 0;
    uint32_t            itcintEn = 0;
    uint32_t            tcintEn = 0;
    uint32_t            tccMode = 0;
    uint32_t            fwid = 0;
    uint32_t            stat = 0;
    uint32_t            syncDim = 0;
    uint32_t            dam = 0;
    uint32_t            sam = 0;
    uint32_t            evtNo = 0;
    uint32_t            opt = 0;
    uint32_t            submitWord = 0;
    volatile unsigned int * tparam;
    uint32_t            waitWord = 0;
    /* perform edma module init */
    evelib_EDMAInitInt(&edmaResources);
    edmaCc  =  (CSL_EdmaccRegsOvly) (CSL_EDMACC_0_REGS);

    /* -------------------------------------------------------------------- */
    /* Precompute the transfer complete codes and event set register values */
    /* that will be passed into the DMA_WAIT and DMA_SUBMIT macros. These   */
    /* macros are used to start transfers and check for completion.         */
    /* -------------------------------------------------------------------- */
    submitWord = ((uint32_t)CSL_EDMACC_ESR_E0_SET << edmaResources.logicalChannelNo[0]);

    /* ------------------------------------------------------------- */
    /* Set options field for transfers                               */
    /* ------------------------------------------------------------- */

    itccEn     =  CSL_EDMACC_OPT_ITCCHEN_DISABLE;
    tccEn      =  CSL_EDMACC_OPT_TCCHEN_DISABLE;
    itcintEn   =  CSL_EDMACC_OPT_ITCINTEN_ENABLE;
    tcintEn    =  CSL_EDMACC_OPT_TCINTEN_ENABLE;
    tccMode    =  CSL_EDMACC_OPT_TCCMODE_NORMAL;
    fwid       =  CSL_EDMACC_OPT_FWID_8;
    stat       =  CSL_EDMACC_OPT_STATIC_NORMAL;
    syncDim    =  CSL_EDMACC_OPT_SYNCDIM_ABSYNC;
    dam        =  CSL_EDMACC_OPT_DAM_INCR;
    sam        =  CSL_EDMACC_OPT_SAM_INCR;

    evtNo = edmaResources.logicalChannelNo[0];

    /* ------------------------------------------------------------- */
    /* Options field calculation for the EDMA transfer.              */
    /* ------------------------------------------------------------- */
    opt =
        CSL_EDMA_OPT_MAKE
        (itccEn,tccEn,itcintEn,tcintEn,evtNo,tccMode,fwid,stat,syncDim,dam,sam);

    /* ------------------------------------------------------------- */
    /* Functions to write the DMA transfer attributes to PARAM       */
    /* src_proc_ping/dst_proc_ping are passed as parameters. The     */
    /* pong buffers are not passed as arguments since this example   */
    /* is in aliased memory view. VCOP/EDMA hardware knows which     */
    /* buffer (ping/pong) to access based on buffer ownership as     */
    /* defined by the macros VCOP_BUF_SWITCH_SET() and               */
    /* VCOP_BUF_SWITCH_TOGGLE().                                     */
    /* ------------------------------------------------------------- */
    tparam = edmaResources.baseParam[0];
    DMA_funcs_writeTransferParams(tparam,
                            opt,
                            sourcePtr,
                            destPtr,
                            widthBytes,
                            height,
                            srcStride,
                            dstStride,
                            0,
                            0,
                            1,
                            0);



    waitWord   = 0x1 << edmaResources.tccVal[0];
    DMA_SUBMIT(edmaCc, submitWord);
    DMA_WAIT(edmaCc, waitWord);


    DMA_resourceAllocator_deallocateResources(edmaCc, &edmaResources);
}

static void evelib_EDMAInitInt(DMA_resourceStruct * edmaResources)
{
    CSL_EdmaccRegsOvly       edmaCc;
    int                 status = 0;

    edmaCc  =  (CSL_EdmaccRegsOvly) (CSL_EDMACC_0_REGS);

    memset(edmaResources, 0 , sizeof(DMA_resourceStruct));



    edmaResources->numChannels  = 1;
    edmaResources->numParam[0]  = 1;
    edmaResources->dmaAttr[0]   = DMA_CHAN_ATTR_EDMA;
    edmaResources->queNo[0]     = 0;
    /* ------------------------------------------------------------------ */
    /* Assign unique events, queues and transfer complete codes to each   */
    /* channel.                                                           */
    /* ------------------------------------------------------------------ */
    DMA_resourceAllocator_initResources();

    status = DMA_resourceAllocator_allocateResources(edmaCc, edmaResources);

    if (status == 0)
    {
        DMA_funcs_hardwareRegSetup(edmaCc,edmaResources);
    }
}
/*-----------------------------------------------------------------------*/
/*  End of file edma_frame_padding.c                                     */
/*=======================================================================*/
/*  Texas Instruments incorporated 2013.                                 */
/*-----------------------------------------------------------------------*/

