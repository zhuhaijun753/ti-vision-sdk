/*
 *******************************************************************************
 *
 * EVE EDMA utility functions
 *
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *******************************************************************************
*/

/**
 *****************************************************************************
 * @file
 *  edma_utils_memcpy.c
 *
 * @brief    This file contains the data types and util function prototype for
 *              configuring EDMA memcpy usecase.
 *
 * @remarks
 *
 * @author: Anshu Jain (anshu_jain@ti.com)
 * @version 0.1 (Aug 2013) : First version of eve edma utils function
 *
 *****************************************************************************
 */


#include "edma_utils_memcpy.h"
#include "dma_resource_allocator.h"
#include "dma_funcs.h"
#include "globalTypes.h"
#include "edmacc_config.h"

extern CSL_EdmaccRegsOvly            gEdmaCc;                   /**< Pointer to the start of EDMA CC0 */


/* We are reserving dedicated resources for memcpy transfer just for memcpy operations */
#define EDMA_UTILS_MEMCPY_CHAN_NUMBER (NUM_QDMA_CHANNELS - 1U)
#define EDMA_UTILS_MEMCPY_TCC_NUMBER (EDMA_NUM_TCCS - 1U)
#define EDMA_UTILS_MEMCPY_PARAM_NUMBER (EDMA_NUM_PARAMS - 1U)


/* ==================================================
 *  @func     EDMA_UTILS_memcpy2D_init
 *
 *  @desc     This function configures hard ware with pre-reserved
 *            EDMA resources
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *             -1 : Failure
 *
 *  =======================================================
 */
static int32_t EDMA_UTILS_memcpy2D_init(void);


/* ==================================================
 *  @func     EDMA_UTILS_memcpy2D_init
 *
 *  @desc     This function configures hard ware with pre-reserved
 *            EDMA resources
 *
 *  @modif    This function modifies autoIncrementContext
 *
 *  @inputs   This function takes following Inputs
 *
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *             -1 : Failure
 *
 *  =======================================================
 */
static int32_t EDMA_UTILS_memcpy2D_init(void)
{
    int32_t             status = 0;
    DMA_resourceStruct  edmaResources;

    /* Resources for QDMA memcopy need not be allocated as we use preserved resources.
    So just populate edmaResources variable with reserved resouces*/
    edmaResources.numChannels   = 1U;
    edmaResources.dmaAttr[0]    = DMA_CHAN_ATTR_QDMA;
    edmaResources.numParam[0]   = 1U;
    edmaResources.queNo[0]      = 0U;
    edmaResources.logicalChannelNo[0]      = EDMA_UTILS_MEMCPY_CHAN_NUMBER;
    edmaResources.tccVal[0]                = EDMA_UTILS_MEMCPY_TCC_NUMBER;
    edmaResources.trigWordIndex[0]         = 7U;
    edmaResources.baseParam[0]             =
                (volatile uint32_t *)&gEdmaCc->PARAMENTRY[EDMA_UTILS_MEMCPY_PARAM_NUMBER];

    status = DMA_funcs_hardwareRegSetup(gEdmaCc, &edmaResources);

    return status;
}



/* ==================================================
 *  @func     EDMA_UTILS_memcpy2D
 *
 *  @desc     This function used EDMA module of eve subsytem to do a 2D memcpy
 *
 *  @modif
 *
 *  @inputs   This function takes following Inputs
 *                  dstPtr :
 *                          Pointer to destination
 *                  srcPtr :
 *                          Pointer to source
 *                  width :
 *                          width of 2D block to be transfered
 *                  height :
 *                          height of 2D block to be transfered
 *                  dstStride :
 *                          Stride/Pitch for dstPtr
 *                  srcStride :
 *                          Stride/Pitch for srcPtr
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
 /* This decleration violates MISRA-C Rule 16.7 : MISRA.PPARAM.NEEDS.CONST.
This cannot be avoided because dstPtr is actually modified by the EDMA hardware
but from the code compiler cannot detect this and hence returns a warning */
int32_t EDMA_UTILS_memcpy2D
(
    void        *dstPtr,
    const void  *srcPtr,
    uint16_t     width,
    uint16_t     height,
    int16_t      dstStride,
    int16_t      srcStride
)
{
#ifdef HOST_EMULATION
    uint32_t rowCnt;

    for (rowCnt = 0 ; rowCnt < height; rowCnt++)
    {
        memcpy ((uint8_t *)dstPtr + rowCnt * dstStride, (uint8_t *)srcPtr + rowCnt * srcStride, width);
    }

    return 0;
#else

    uint32_t            waitWord;

    uint32_t            itccEn;
    uint32_t            tccEn;
    uint32_t            itcintEn;
    uint32_t            tcintEn;
    uint32_t            tccMode;
    uint32_t            fwid;
    uint32_t            stat;
    uint32_t            syncDim;
    uint32_t            dam;
    uint32_t            sam;

    uint32_t            tcc;
    uint16_t            aCNT, bCNT, cCNT;
    /* ----------------------------------------------------------------- */
    /* Option words to hold configuration of dma transfers               */
    /* ----------------------------------------------------------------- */
    uint32_t            opt;
    volatile uint32_t * baseParam;
    int32_t             status = 0;
    /* ------------------------------------------------------------- */
    /* Check for invalid arguments                                   */
    /* ------------------------------------------------------------- */
    if((dstPtr == NULL) || (srcPtr == NULL))
    {
#ifdef DEBUG
        printf("NULL Pointers!!\n");
#endif
        status = -1;
    }

    if(status == 0)
    {
        status = EDMA_UTILS_memcpy2D_init();

        if ( status == 0 )
        {

            aCNT = width;
            bCNT = height;
            cCNT = 1U;

            /* ------------------------------------------------------------- */
            /* Set options field for transfers                               */
            /* ------------------------------------------------------------- */
            itccEn     =  CSL_EDMACC_OPT_ITCCHEN_DISABLE;
            tccEn      =  CSL_EDMACC_OPT_TCCHEN_DISABLE;
            itcintEn   =  CSL_EDMACC_OPT_ITCINTEN_DISABLE;
            tcintEn    =  CSL_EDMACC_OPT_TCINTEN_ENABLE;
            tccMode    =  CSL_EDMACC_OPT_TCCMODE_NORMAL;
            fwid       =  CSL_EDMACC_OPT_FWID_8;
            stat       =  CSL_EDMACC_OPT_STATIC_STATIC;
            syncDim    =  CSL_EDMACC_OPT_SYNCDIM_ABSYNC;
            dam        =  CSL_EDMACC_OPT_DAM_INCR;
            sam        =  CSL_EDMACC_OPT_SAM_INCR;

            tcc        = EDMA_UTILS_MEMCPY_TCC_NUMBER;
            waitWord   = (uint32_t)0x1U << tcc;

            /* ------------------------------------------------------------- */
            /* Options field calculation for the QDMA transfer.              */
            /* ------------------------------------------------------------- */
#pragma CHECK_MISRA ("none")
            opt =
                CSL_EDMA_OPT_MAKE
                (itccEn,tccEn,itcintEn,tcintEn,tcc,tccMode,fwid,stat,syncDim,dam,sam);
#pragma RESET_MISRA ("required")

            baseParam = (volatile uint32_t *)&gEdmaCc->PARAMENTRY[EDMA_UTILS_MEMCPY_PARAM_NUMBER];


            /* ------------------------------------------------------------- */
            /* Functions to write the DMA transfer attributes to PARAM       */
            /* src_proc_ping/dst_proc_ping are passed as parameters. The     */
            /* pong buffers are not passed as arguments since this example   */
            /* is in aliased memory view. VCOP/EDMA hardware knows which     */
            /* buffer (ping/pong) to access based on buffer ownership as     */
            /* defined by the macros VCOP_BUF_SWITCH_SET() and               */
            /* VCOP_BUF_SWITCH_TOGGLE().                                     */
            /* ------------------------------------------------------------- */
            DMA_funcs_writeTransferParams
            (
                baseParam,
                opt,
                (const uint8_t *)srcPtr,           /* SRC (internal mem) */
                (uint8_t *)dstPtr,           /* DST (external mem) */
                aCNT,              /* bytes per line in block */
                bCNT,              /* # of lines in block */
                srcStride,               /* line pitch of input image */
                dstStride,               /* line pitch of output image */
                0,                 /* offset to next block in input      */
                0,                 /* offset to next block in output      */
                cCNT,
                0 /* No linking*/
            );

            /* ------------------------------------------------------------- */
            /*  Check for completion of QDMA                                 */
            /* ------------------------------------------------------------- */
            QDMA_WAIT(gEdmaCc , waitWord);
        }

    }

    return status;
#endif
}


