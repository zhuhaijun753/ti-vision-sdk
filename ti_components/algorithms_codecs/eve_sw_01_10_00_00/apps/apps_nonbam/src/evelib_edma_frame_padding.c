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
#include "evelib_edma_frame_padding.h"

#define EN_CHAINING

void evelib_EDMAInitInt(DMA_resourceStruct * edmaResources);

void EVELIB_padVertEDMA(uint8_t     *padSourcePtr,
                       uint8_t      *padDestPtr,
                       uint32_t     padWidth,
                       uint32_t     padHeight,
                       int32_t      srcDataStride,
                       int32_t      dstDataStride,
                       int32_t      padPixelSize)
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
    volatile uint32_t   *tparam;

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
#ifdef EN_CHAINING
    itccEn     =  CSL_EDMACC_OPT_ITCCHEN_ENABLE;
    tccEn      =  CSL_EDMACC_OPT_TCCHEN_DISABLE;
    itcintEn   =  CSL_EDMACC_OPT_ITCINTEN_DISABLE;
#else
    itccEn     =  CSL_EDMACC_OPT_ITCCHEN_DISABLE;
    tccEn      =  CSL_EDMACC_OPT_TCCHEN_DISABLE;
    itcintEn   =  CSL_EDMACC_OPT_ITCINTEN_ENABLE;
#endif
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
                            padSourcePtr,
                            padDestPtr,
                            padWidth,
                            padPixelSize,
                            srcDataStride,
                            dstDataStride,
                            0,
                            padPixelSize*dstDataStride,
                            padHeight,
                            0);

#ifdef EN_CHAINING

        DMA_SUBMIT(edmaCc, submitWord);
        uint32_t waitWord   = 0x1 << edmaResources.tccVal[0];

        /* ------------------------------------------------------------- */
        /* Wait till C count becomes zero.                               */
        /* ------------------------------------------------------------- */
        tparam     =    edmaResources.baseParam[0];
        DMA_WAIT(edmaCc,waitWord);
#else
        int i;
        uint32_t            waitWord = 0;
        waitWord   = 0x1 << edmaResources.tccVal[0];
        waitWord = 0x1 << edmaResources.tccVal[0];
        for(i=0; i<padHeight; i++)
        {
            DMA_SUBMIT(edmaCc, submitWord);
            DMA_WAIT(edmaCc, waitWord);
        }
#endif
    DMA_resourceAllocator_deallocateResources(edmaCc,&edmaResources);

}


void EVELIB_padHorzEDMA(uint8_t     *padSourcePtr,
                       uint8_t      *padDestPtr,
                       uint32_t     padWidth,
                       uint32_t     padHeight,
                       int32_t      srcDataStride,
                       int32_t      dstDataStride,
                       int32_t      padPixelSize)
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
    uint32_t            tcc = 0;
    uint32_t            opt = 0;
    uint32_t            submitWord = 0;
    volatile uint32_t   *tparam;

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
#ifdef EN_CHAINING
    itccEn     =  CSL_EDMACC_OPT_ITCCHEN_ENABLE;
    tccEn      =  CSL_EDMACC_OPT_TCCHEN_DISABLE;
    itcintEn   =  CSL_EDMACC_OPT_ITCINTEN_DISABLE;
#else
    itccEn     =  CSL_EDMACC_OPT_ITCCHEN_DISABLE;
    tccEn      =  CSL_EDMACC_OPT_TCCHEN_DISABLE;
    itcintEn   =  CSL_EDMACC_OPT_ITCINTEN_ENABLE;
#endif
    tcintEn    =  CSL_EDMACC_OPT_TCINTEN_ENABLE;
    tccMode    =  CSL_EDMACC_OPT_TCCMODE_NORMAL;
    fwid       =  CSL_EDMACC_OPT_FWID_8;
    stat       =  CSL_EDMACC_OPT_STATIC_NORMAL;
    syncDim    =  CSL_EDMACC_OPT_SYNCDIM_ABSYNC;
    dam        =  CSL_EDMACC_OPT_DAM_INCR;
    sam        =  CSL_EDMACC_OPT_SAM_INCR;

    tcc = edmaResources.tccVal[0];

    /* ------------------------------------------------------------- */
    /* Options field calculation for the self chained EDMA transfer. */
    /* ------------------------------------------------------------- */
    opt =
        CSL_EDMA_OPT_MAKE
        (itccEn,tccEn,itcintEn,tcintEn,tcc,tccMode,fwid,stat,syncDim,dam,sam);

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
                            padSourcePtr,
                            padDestPtr,
                            padPixelSize,
                            padHeight,
                            srcDataStride,
                            dstDataStride,
                            0,
                            padPixelSize,
                            padWidth,
                            0);

#ifdef EN_CHAINING
        uint32_t waitWord = 0x1 << edmaResources.tccVal[0];
        DMA_SUBMIT(edmaCc, submitWord);

        /* ------------------------------------------------------------- */
        /* Wait till C count becomes zero.                               */
        /* ------------------------------------------------------------- */
        tparam     =    edmaResources.baseParam[0];
        while (tparam[7])
        {
        }
        DMA_WAIT(edmaCc,waitWord);

#else
        int i;
        uint32_t waitWord = 0x1 << edmaResources.tccVal[0];
        for(i=0; i<padWidth; i++)
        {
            DMA_SUBMIT(edmaCc, submitWord);
            DMA_WAIT(edmaCc, waitWord);
        }
#endif
    DMA_resourceAllocator_deallocateResources(edmaCc , &edmaResources);
}

void evelib_EDMAInitInt(DMA_resourceStruct * edmaResources)
{
    CSL_EdmaccRegsOvly       edmaCc;
    int                 status  = 0;

    edmaCc  =  (CSL_EdmaccRegsOvly) (CSL_EDMACC_0_REGS);



    memset(edmaResources, 0, sizeof(DMA_resourceStruct));

    /* ------------------------------------------------------------------ */
    edmaResources->numChannels  = 1;
    edmaResources->numParam[0]  = 1;
    edmaResources->dmaAttr[0]   = DMA_CHAN_ATTR_EDMA;
    edmaResources->queNo[0]     = 0;

    DMA_resourceAllocator_initResources();

    status = DMA_resourceAllocator_allocateResources(edmaCc,edmaResources);

    if (status == 0)
    {
        status = DMA_funcs_hardwareRegSetup(edmaCc,edmaResources);

    }

}
/*-----------------------------------------------------------------------*/
/*  End of file edma_frame_padding.c                                     */
/*=======================================================================*/
/*  Texas Instruments incorporated 2013.                                 */
/*-----------------------------------------------------------------------*/

