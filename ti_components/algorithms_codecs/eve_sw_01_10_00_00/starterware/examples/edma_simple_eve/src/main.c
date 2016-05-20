/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*-----------------------------------------------------------------------*/
/*  NAME : main.c                                                        */
/*                                                                       */
/*  DESCRIPTION:                                                         */
/*                                                                       */
/*  This file is intended to show several simple examples of how to      */
/*  use the register level CSL for edma to setup single 1D -> 1D,        */
/*  1D -> 2D, 2D -> 1D, 2D -> 2D transfers. The aim is to show a         */
/*  basic template for simple memcpy, with the transfer being            */
/*  kicked off by CPU setting up an event. This file also shows a        */
/*  linking with self-chaining example, to demonstrate linked 1D ->      */
/*  1D and linked 1D -> 2D. It also has an example of auto-increment     */
/*  on 1D -> 1D transfers which posts both intermediate and final        */
/*  transfer completion codes.                                           */
/*                                                                       */
/*=======================================================================*/
/*  Texas Instruments Incorporated 2000-2006.                            */
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/*  Standard header includes for c environment.                          */
/*-----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <arp32.h>

/*-----------------------------------------------------------------------*/
/*  This defines the standard data types such as Bool.                   */
/*-----------------------------------------------------------------------*/


/*-----------------------------------------------------------------------*/
/*  These are the include files that are needed for edma/qdma.           */
/*-----------------------------------------------------------------------*/

#include "csl_edma.h"
#include "cslr_edmacc.h"
#include "edma_baseaddr.h"
#include "tistdtypes.h"
#include "dma_funcs.h"

#include "eve_dma_test_data.h"
#include "dma_resource_allocator.h"

#define NUM_TESTS       10

#define NUM_CHANNELS     1


/*-----------------------------------------------------------------------*/
/*  Zero out all destination buffers and do a cache clean on L2 to make  */
/*  these commit.                                                        */
/*-----------------------------------------------------------------------*/

void dst_buffers_setup()
{
    memset (dst_1, 0x0, sizeof(dst_1));
    memset (dst_2, 0x0, sizeof(dst_2));
    memset (dst_3, 0x0, sizeof(dst_3));
    memset (dst_4, 0x0, sizeof(dst_4));
    memset (dst_5, 0x0, sizeof(dst_5));
    memset (dst_6, 0x0, sizeof(dst_6));
    memset (dst_7, 0x0, sizeof(dst_7));
    memset (dst_8, 0x0, sizeof(dst_8));
}


/*-----------------------------------------------------------------------*/
/*  Start of the main test_harness code.                                 */
/*-----------------------------------------------------------------------*/

int main()
{

    /*-------------------------------------------------------------------*/
    /*  We declare temporary variables here, which we assume have been   */
    /*  allocated through DMAN3, IDMA3.                                  */
    /*-------------------------------------------------------------------*/

    unsigned int            i;
    unsigned int            num_tests;

    unsigned int            evt_no;
    unsigned int            tcc_no;

    unsigned int            numParam;
    unsigned int            numChannels;
    DMA_chanAttr            dmaAttr;
    Bool                   *trf_pend;
    Bool                    trf_status;

    unsigned int            itccEn;
    unsigned int            tccEn;
    unsigned int            itcintEn;
    unsigned int            tcintEn;
    unsigned int            tcc;
    unsigned int            tccMode;
    unsigned int            fwid;
    unsigned int            stat;
    unsigned int            syncDim;
    unsigned int            dam;
    unsigned int            sam;
    unsigned int            chan;
    unsigned int            restore_value;

    unsigned int            opt_1d_1d;
    unsigned int            opt_1d_2d;
    unsigned int            opt_2d_1d;
    unsigned int            opt_2d_2d;

    unsigned int            opt_1d_1d_link_chain;
    unsigned int            opt_1d_1d_link;
    unsigned int            opt_1d_2d_link_chain;
    unsigned int            opt_1d_2d_link;
    unsigned int            opt_1d_1d_norm;

    unsigned int            fail_1d_1d;
    unsigned int            fail_1d_2d;
    unsigned int            fail_2d_1d;
    unsigned int            fail_2d_2d;
    unsigned int            fail_2d_2d_sep;
    unsigned int            fail_1d_1d_inc;

    unsigned int            fail_1d_1d_lnk;
    unsigned int            fail_1d_2d_lnk;

    unsigned int            num_bytes;
    unsigned int            num_lines;
    unsigned int            pitch;
    unsigned int            src_pitch;
    unsigned int            dst_pitch;
    unsigned int            link_addr;
    unsigned int            param_chan;
    unsigned int            in;
    unsigned int            j;

    volatile unsigned int   *trigParam;
    CSL_EdmaccRegsOvly       edma_cc;

    DMA_resourceStruct edmaResources;
    int                     status = 0;

    /*-------------------------------------------------------------------*/
    /*  Anchor edma_cc to the start of the EDMA CC0, we only have one    */
    /*  CC so it is CC0.                                                 */
    /*-------------------------------------------------------------------*/

    edma_cc  =  (CSL_EdmaccRegsOvly) (CSL_EDMACC_0_REGS);
    printf ("edma_cc:0x%.8x \n", edma_cc);
    assert ((unsigned int)edma_cc == 0x400A0000);


    /*-------------------------------------------------------------------*/
    /*  The following loop runs for the number of tests requested by     */
    /*  the user, obtains a random event, random tcc, random PARAM       */
    /*  and performa a simple EDMA 1D to 1D transfer for purposes of     */
    /*  illustration.                                                    */
    /*-------------------------------------------------------------------*/

    num_tests = NUM_TESTS;
    numChannels = NUM_CHANNELS;
    /*-------------------------------------------------------------------*/
    /*  Allocate trf_status to trf_pend pointer.                         */
    /*-------------------------------------------------------------------*/

    trf_pend = &trf_status;

    /*--------------------------------------------------------------------*/
    /*  Seed the random number generator.                                 */
    /*--------------------------------------------------------------------*/

    srand (0xFADEBABE);
    DMA_resourceAllocator_initResources();

    for (i = 0; i < num_tests; i++)
    {
        /*---------------------------------------------------------------*/
        /*  In this function we will zero all destinations, so as to     */
        /*  reset executions.                                            */
        /*---------------------------------------------------------------*/

         dst_buffers_setup();
        dmaAttr = DMA_CHAN_ATTR_EDMA;
        numParam = 6;

        edmaResources.numChannels   = numChannels;
        edmaResources.numParam[0]   = numParam;
        edmaResources.dmaAttr[0]    = dmaAttr;
        status = DMA_resourceAllocator_allocateResources(edma_cc, &edmaResources);


        if ( status == 0)
        {
            DMA_funcs_hardwareRegSetup(edma_cc, &edmaResources);
        }

        /*---------------------------------------------------------------*/
        /*   The Options parameter explains the different                */
        /*   features of the transfer that are being excercised.         */
        /*   In this case the following values are used for              */
        /*   each of the individual bits of the "OPT" field.             */
        /*   We now start setting up the options for 1D -> 1D.           */
        /*                                                               */
        /*   BITS   CC      TYPE       DESCRIPTION AND VALUE             */
        /*   31     PRIV     R         Privelege level, not              */
        /*                             writeable by wdata.               */
        /*                                                               */
        /*   30..28 RSV      R         Reserved                          */
        /*                                                               */
        /*   27..24 PRIVID   R         Indicates privelege id            */
        /*                             not writeable by wdata.           */
        /*                                                               */
        /*   23     ITCCCHEN W         Intermediate tranfer              */
        /*                             completion chaining dis.          */
        /*                                                               */
        /*   22     TCCHEN   W         Transfer complete code            */
        /*                             for chaining disabled.            */
        /*                                                               */
        /*   21     ITCINTEN W         Intermediate transfer             */
        /*                             completion interrupt dis.         */
        /*                                                               */
        /*   20     TCINTEN  W         Transfer completion               */
        /*                             interrupt enabled.                */
        /*                                                               */
        /*   19     WIMODE   W         0: Normal operation               */
        /*                                                               */
        /*   18     RSV                RESERVED                          */
        /*                                                               */
        /*   17-12  TCC      W         Transfer completion code          */
        /*                             that will be posted IPR.          */
        /*                                                               */
        /*   11     TCCM     W         Mode 0:Normal completion          */
        /*                                                               */
        /*   10-8   FWID     W         000 FIFO with NA                  */
        /*                                                               */
        /*   7-4    RSVD     W         0000                              */
        /*                                                               */
        /*   3      STATIC   W         1:Static PARAM update.            */
        /*                                                               */
        /*   2      SYNCDIM  W         0-AB_sync 1D -> 1D                */
        /*                                                               */
        /*   1      DAM      W         0-Incrementing.                   */
        /*                                                               */
        /*   0      SAM      W         0-Incrementing.                   */
        /*---------------------------------------------------------------*/

        chan       =  edmaResources.logicalChannelNo[0];
        itccEn     =  CSL_EDMACC_OPT_ITCCHEN_DISABLE;
        tccEn      =  CSL_EDMACC_OPT_TCCHEN_DISABLE;
        itcintEn   =  CSL_EDMACC_OPT_ITCINTEN_DISABLE;
        tcintEn    =  CSL_EDMACC_OPT_TCINTEN_ENABLE;
        tcc        =  edmaResources.tccVal[chan];
        tccMode    =  CSL_EDMACC_OPT_TCCMODE_NORMAL;
        fwid       =  CSL_EDMACC_OPT_FWID_8;
        stat       =  CSL_EDMACC_OPT_STATIC_STATIC;
        syncDim    =  CSL_EDMACC_OPT_SYNCDIM_ASYNC;
        dam        =  CSL_EDMACC_OPT_DAM_INCR;
        sam        =  CSL_EDMACC_OPT_SAM_INCR;

        opt_1d_1d  =
        CSL_EDMA_OPT_MAKE
        (itccEn,tccEn,itcintEn,tcintEn,tcc,tccMode,fwid,stat,syncDim,dam,sam);

        /*---------------------------------------------------------------*/
        /*  Now setup a 1D -> 1D transfer from src to dst to transfer    */
        /*  256 bytes. Instead of calling a dedicated function we        */
        /*  will code it up using EDMA CSL register level. First we      */
        /*  will write in internal memory 8 words as follows:            */
        /*                                                               */
        /*  Program in 8 words that represent 1 TR request.              */
        /*                                                               */
        /*  WORD0:  OPTIONS field.                                       */
        /*  WORD1:  Sorce address (SRC).                                 */
        /*  WORD2:  BCNT | ACNT. BCNT needs to be 1 as we are transf.    */
        /*  1 row of 256 bytes, and ACNT is the number of 1D bytes to    */
        /*  be transferred.                                              */
        /*  WORD3:  Destination address (DST).                           */
        /*  WORD4:  DSTBIDX | SRBIDX.                                    */
        /*  WORD5:  BCNTRLD | LINK. This is the same as BCNT.            */
        /*  No linking is needed and hence the link field is             */
        /*  set to 0xFFFF.                                               */
        /*  WORD6:  DSTCIDX | SRCCIDX. This is not used and              */
        /*  hence both these are set to be 0x0.                          */
        /*  WORD7:  CCNT is 1.                                           */
        /*---------------------------------------------------------------*/

        num_bytes  =    256;

        /*---------------------------------------------------------------*/
        /*  Disable interrupts during the entire period of IDMA          */
        /*  registers programmation and transfer for correct operation.  */
        /*  The IDMA is a shared resource and other threads should wait  */
        /*  for the completion. Note we can disable this disable of      */
        /*  interrupts later, as we will be in an ISR, and therefore     */
        /*  interrupts cannot happen anyway.                             */
        /*---------------------------------------------------------------*/

        restore_value   = _disable_interrupts();

        /*---------------------------------------------------------------*/
        /*  Set transfer pending status flag, to indicate that transfer  */
        /*  is in progress.                                              */
        /*---------------------------------------------------------------*/

        *trf_pend  =  TRUE;

        /*---------------------------------------------------------------*/
        /*  Set up attributes of the 1D -> 1D transfer in intern mem.    */
        /*---------------------------------------------------------------*/

        trigParam       =    edmaResources.baseParam[chan];

        trigParam[0]    =   (unsigned int) opt_1d_1d;
        trigParam[1]    =   ((unsigned int) (src)   - CGEM_MEM_OFFSET);
        trigParam[2]    =   pack2(0x1, num_bytes);
        trigParam[3]    =   ((unsigned int) (dst_1) - CGEM_MEM_OFFSET);
        trigParam[4]    =   (0x0 << 16) | (0x0);
        trigParam[5]    =   pack2(0x1, 0xFFFF);
        trigParam[6]    =   (0x0 << 16) | (0x0);
        trigParam[7]    =    0x1;

        /*---------------------------------------------------------------*/
        /*  If channel is EDMA channel then set the associated event in  */
        /*  either ESR or ESRH.                                          */
        /*---------------------------------------------------------------*/

        if (edmaResources.dmaAttr[chan] == DMA_CHAN_ATTR_EDMA)
        {
            evt_no = edmaResources.logicalChannelNo[chan];
            DMA_SUBMIT(edma_cc, 0x1u<<evt_no);
        }

        /*---------------------------------------------------------------*/
        /* Restore the previous state. This finishes submission phase    */
        /* of EDMA.                                                      */
        /*---------------------------------------------------------------*/

        _restore_interrupts(restore_value);

        /*---------------------------------------------------------------*/
        /*  Here is where we start checking for the completion of the    */
        /*  transfer, so we have to disable interrupts.                  */
        /*---------------------------------------------------------------*/

        restore_value   = _disable_interrupts();

        /*---------------------------------------------------------------*/
        /*  Check completion by reading either IPR or IPRH based on      */
        /*  the TCC bit that has been selected.                          */
        /*---------------------------------------------------------------*/

        tcc       =  edmaResources.tccVal[chan];

        /*---------------------------------------------------------------*/
        /*  Irrespective of edma or qdma clear either IPR/IPRH.          */
        /*                                                               */
        /*  while  (!(edma_cc->IPR & (0x1 << tcc)));                     */
        /*  edma_cc->ICR  = (0x1 << tcc);                                */
        /*---------------------------------------------------------------*/

        DMA_WAIT(edma_cc, 0x1u<<tcc);

        /*---------------------------------------------------------------*/
        /*  Clear trf_pend status, as we have finished waiting on trans. */
        /*---------------------------------------------------------------*/

        *trf_pend   = FALSE;

        /*---------------------------------------------------------------*/
        /* Restore the previous state. This finishes submission phase    */
        /* of EDMA.                                                      */
        /*---------------------------------------------------------------*/

        _restore_interrupts(restore_value);

        /*---------------------------------------------------------------*/
        /* Perform a 1D-2D transfer, using AB sync and TCC enabled.      */
        /*---------------------------------------------------------------*/

        chan       =  0x0;
        itccEn     =  CSL_EDMACC_OPT_ITCCHEN_DISABLE;
        tccEn      =  CSL_EDMACC_OPT_TCCHEN_DISABLE;
        itcintEn   =  CSL_EDMACC_OPT_ITCINTEN_DISABLE;
        tcintEn    =  CSL_EDMACC_OPT_TCINTEN_ENABLE;
        tcc        =  edmaResources.tccVal[chan];
        tccMode    =  CSL_EDMACC_OPT_TCCMODE_NORMAL;
        fwid       =  CSL_EDMACC_OPT_FWID_8;
        stat       =  CSL_EDMACC_OPT_STATIC_STATIC;
        syncDim    =  CSL_EDMACC_OPT_SYNCDIM_ABSYNC;
        dam        =  CSL_EDMACC_OPT_DAM_INCR;
        sam        =  CSL_EDMACC_OPT_SAM_INCR;

        /*---------------------------------------------------------------*/
        /* Options field calculation for 1D src to 2D dst.               */
        /*---------------------------------------------------------------*/

        opt_1d_2d  =
        CSL_EDMA_OPT_MAKE
        (itccEn,tccEn,itcintEn,tcintEn,tcc,tccMode,fwid,stat,syncDim,dam,sam);

        /*---------------------------------------------------------------*/
        /*  Program in 8 words that represent 1 TR request.              */
        /*                                                               */
        /*  WORD0:  OPTIONS field.                                       */
        /*  WORD1:  Sorce address (SRC).                                 */
        /*  WORD2:  BCNT | ACNT. BCNT needs to be num_lines,             */
        /*  ACNT is the number of 1D bytes to be transferred.            */
        /*  WORD3:  Destination address (DST).                           */
        /*  WORD4:  DSTBIDX | SRBIDX.                                    */
        /*  DSTBIDX: pitch to increment destination and                  */
        /*  SRCBIDX: num_bytes to increment "SRC".                       */
        /*  WORD5:  BCNTRLD | LINK. This is the same as BCNT.            */
        /*  No linking is needed and hence the link field is             */
        /*  set to 0xFFFF.                                               */
        /*  WORD6:  DSTCIDX | SRCCIDX. This is not used and              */
        /*  hence both these are set to be 0x0.                          */
        /*  WORD7:  CCNT is 1.                                           */
        /*                                                               */
        /*  We are transferring 4 lines each of 64 bytes incrementing    */
        /*  destination by 80 bytes as dst is 2D, src by 64 bytes as     */
        /*  src is 1D.                                                   */
        /*---------------------------------------------------------------*/

        num_lines             =      4;
        num_bytes             =     64;
        pitch                 =     80;

        /*---------------------------------------------------------------*/
        /*  Disable interrupts during the entire period of IDMA          */
        /*  registers programmation and transfer for correct operation.  */
        /*  The IDMA is a shared resource and other threads should wait  */
        /*  for the completion. Note we can disable this disable of      */
        /*  interrupts later, as we will be in an ISR, and therefore     */
        /*  interrupts cannot happen anyway.                             */
        /*---------------------------------------------------------------*/

        restore_value   = _disable_interrupts();

        /*---------------------------------------------------------------*/
        /*  Set transfer pending status flag, to indicate that transfer  */
        /*  is in progress.                                              */
        /*---------------------------------------------------------------*/

        *trf_pend  =  TRUE;

        /*---------------------------------------------------------------*/
        /*  Write up the values of the PARAM in internal memory. Use     */
        /*  IDMA Channel 0 to perform transfer. Mask is 0xFFFFFF00,      */
        /*  as only 8 out of 32 words needs to be written.               */
        /*---------------------------------------------------------------*/

        trigParam       =    edmaResources.baseParam[chan];
        trigParam[0]    =    (unsigned int) opt_1d_2d;
        trigParam[1]    =    ((unsigned int) src - CGEM_MEM_OFFSET);
        trigParam[2]    =    pack2(num_lines, num_bytes);
        trigParam[3]    =    ((unsigned int) dst_2 - CGEM_MEM_OFFSET);
        trigParam[4]    =    pack2(pitch, num_bytes);
        trigParam[5]    =    pack2(num_lines, 0xFFFF);
        trigParam[6]    =    (0x0 << 16) | (0x0);
        trigParam[7]    =     0x1;

        /*---------------------------------------------------------------*/
        /*  If channel is EDMA channel then set the associated event in  */
        /*  either ESR or ESRH.                                          */
        /*                                                               */
        /*  edma_cc->ESR  = (CSL_EDMACC_ESR_E0_SET << evt_no);           */
        /*---------------------------------------------------------------*/

        if (edmaResources.dmaAttr[chan] == DMA_CHAN_ATTR_EDMA)
        {
            evt_no = edmaResources.logicalChannelNo[chan];
            DMA_SUBMIT(edma_cc , 0x1<<evt_no);
        }

        /*---------------------------------------------------------------*/
        /* Restore the previous state. This finishes submission phase    */
        /* of EDMA.                                                      */
        /*---------------------------------------------------------------*/

        _restore_interrupts(restore_value);

        /*---------------------------------------------------------------*/
        /*  Here is where we start checking for the completion of the    */
        /*  transfer, so we have to disable interrupts.                  */
        /*---------------------------------------------------------------*/

        restore_value   = _disable_interrupts();

        /*---------------------------------------------------------------*/
        /*  Check completion by reading either IPR or IPRH based on      */
        /*  the TCC bit that has been selected.                          */
        /*---------------------------------------------------------------*/

        tcc       =  edmaResources.tccVal[chan];

        /*---------------------------------------------------------------*/
        /*  Irrespective of edma or qdma clear either IPR/IPRH.          */
        /*                                                               */
        /*  while  (!(edma_cc->IPR & (0x1 << tcc)));                     */
        /*  edma_cc->ICR  = (0x1 << tcc);                                */
        /*---------------------------------------------------------------*/

        DMA_WAIT ( edma_cc ,0x1<<tcc);

        /*---------------------------------------------------------------*/
        /*  Clear trf_pend status, as we have finished waiting on trans. */
        /*---------------------------------------------------------------*/

        *trf_pend   = FALSE;

        /*---------------------------------------------------------------*/
        /* Restore the previous state. This finishes submission phase    */
        /* of EDMA.                                                      */
        /*---------------------------------------------------------------*/

        _restore_interrupts(restore_value);

        /*---------------------------------------------------------------*/
        /* Options field calculation for 2D src to 1D dst.               */
        /*---------------------------------------------------------------*/

        chan       =  0x0;
        itccEn     =  CSL_EDMACC_OPT_ITCCHEN_DISABLE;
        tccEn      =  CSL_EDMACC_OPT_TCCHEN_DISABLE;
        itcintEn   =  CSL_EDMACC_OPT_ITCINTEN_DISABLE;
        tcintEn    =  CSL_EDMACC_OPT_TCINTEN_ENABLE;
        tcc        =  edmaResources.tccVal[chan];
        tccMode    =  CSL_EDMACC_OPT_TCCMODE_NORMAL;
        fwid       =  CSL_EDMACC_OPT_FWID_8;
        stat       =  CSL_EDMACC_OPT_STATIC_STATIC;
        syncDim    =  CSL_EDMACC_OPT_SYNCDIM_ABSYNC;
        dam        =  CSL_EDMACC_OPT_DAM_INCR;
        sam        =  CSL_EDMACC_OPT_SAM_INCR;

        opt_2d_1d  =
        CSL_EDMA_OPT_MAKE
        (itccEn,tccEn,itcintEn,tcintEn,tcc,tccMode,fwid,stat,syncDim,dam,sam);

         /*---------------------------------------------------------------*/
         /*  Program in 8 words that represent 1 TR request.              */
         /*                                                               */
         /*  WORD0:  OPTIONS field.                                       */
         /*  WORD1:  Sorce address (SRC).                                 */
         /*  WORD2:  BCNT | ACNT. BCNT needs to be num_lines              */
         /*  ACNT is the number of 1D bytes to be transferred.            */
         /*  WORD3:  Destination address (DST).                           */
         /*  WORD4:  DSTBIDX | SRBIDX.                                    */
         /*  DSTBIDX: num_bytes and SRCBIDX:pitch                         */
         /*  WORD5:  BCNTRLD | LINK. This is the same as BCNT.            */
         /*  No linking is needed and hence the link field is             */
         /*  set to 0xFFFF.                                               */
         /*  WORD6:  DSTCIDX | SRCCIDX. This is not used and              */
         /*  hence both these are set to be 0x0.                          */
         /*  WORD7:  CCNT is 1.                                           */
         /*                                                               */
         /*  Here we are trying to transfer 4 lines each of 64 bytes,     */
         /*  treating "src" as 2D, incrementing src by 48 bytes, and      */
         /*  "dst" as 1D and incrementing dst by 64 bytes.                */
         /*---------------------------------------------------------------*/

         num_lines     =      4;
         num_bytes     =     64;
         pitch         =     48;

        /*---------------------------------------------------------------*/
        /*  Disable interrupts during the entire period of IDMA          */
        /*  registers programmation and transfer for correct operation.  */
        /*  The IDMA is a shared resource and other threads should wait  */
        /*  for the completion. Note we can disable this disable of      */
        /*  interrupts later, as we will be in an ISR, and therefore     */
        /*  interrupts cannot happen anyway.                             */
        /*---------------------------------------------------------------*/

        restore_value   = _disable_interrupts();

        /*---------------------------------------------------------------*/
        /*  Set transfer pending status flag, to indicate that transfer  */
        /*  is in progress.                                              */
        /*---------------------------------------------------------------*/

        *trf_pend  =  TRUE;

        /*---------------------------------------------------------------*/
        /*  Write up the values of the PARAM in internal memory. Use     */
        /*---------------------------------------------------------------*/

        trigParam     =    edmaResources.baseParam[chan];
        trigParam[0]  =    (unsigned int) opt_2d_1d;
        trigParam[1]  =    ((unsigned int) src - CGEM_MEM_OFFSET);
        trigParam[2]  =    pack2(num_lines, num_bytes);
        trigParam[3]  =    ((unsigned int) dst_3 - CGEM_MEM_OFFSET);
        trigParam[4]  =    pack2(num_bytes, pitch);
        trigParam[5]  =    pack2(num_lines, 0xFFFF);
        trigParam[6]  =    (0x0 << 16) | (0x0);
        trigParam[7]  =     0x1;

        /*---------------------------------------------------------------*/
        /*  If channel is EDMA channel then set the associated event in  */
        /*  either ESR or ESRH.                                          */
        /*---------------------------------------------------------------*/

        if (edmaResources.dmaAttr[chan] == DMA_CHAN_ATTR_EDMA)
        {
            evt_no = edmaResources.logicalChannelNo[chan];
            DMA_SUBMIT (edma_cc, 0x1<<evt_no);
        }

        /*---------------------------------------------------------------*/
        /* Restore the previous state. This finishes submission phase    */
        /* of EDMA.                                                      */
        /*---------------------------------------------------------------*/

        _restore_interrupts(restore_value);

        /*---------------------------------------------------------------*/
        /*  Here is where we start checking for the completion of the    */
        /*  transfer, so we have to disable interrupts.                  */
        /*---------------------------------------------------------------*/

        restore_value   = _disable_interrupts();

        /*---------------------------------------------------------------*/
        /*  Check completion by reading either IPR or IPRH based on      */
        /*  the TCC bit that has been selected.                          */
        /*---------------------------------------------------------------*/

        tcc       =  edmaResources.tccVal[chan];

        /*---------------------------------------------------------------*/
        /*  Irrespective of edma or qdma clear IPR.                      */
        /*---------------------------------------------------------------*/

        DMA_WAIT ( edma_cc ,0x1<<tcc);

        /*---------------------------------------------------------------*/
        /*  Clear trf_pend status, as we have finished waiting on trans. */
        /*---------------------------------------------------------------*/

        *trf_pend   = FALSE;

        /*---------------------------------------------------------------*/
        /* Restore the previous state. This finishes submission phase    */
        /* of EDMA.                                                      */
        /*---------------------------------------------------------------*/

        _restore_interrupts(restore_value);

        chan       =  0x0;
        itccEn     =  CSL_EDMACC_OPT_ITCCHEN_DISABLE;
        tccEn      =  CSL_EDMACC_OPT_TCCHEN_DISABLE;
        itcintEn   =  CSL_EDMACC_OPT_ITCINTEN_DISABLE;
        tcintEn    =  CSL_EDMACC_OPT_TCINTEN_ENABLE;
        tcc        =  edmaResources.tccVal[chan];
        tccMode    =  CSL_EDMACC_OPT_TCCMODE_NORMAL;
        fwid       =  CSL_EDMACC_OPT_FWID_8;
        stat       =  CSL_EDMACC_OPT_STATIC_STATIC;
        syncDim    =  CSL_EDMACC_OPT_SYNCDIM_ABSYNC;
        dam        =  CSL_EDMACC_OPT_DAM_INCR;
        sam        =  CSL_EDMACC_OPT_SAM_INCR;

        opt_2d_2d  =
        CSL_EDMA_OPT_MAKE
        (itccEn,tccEn,itcintEn,tcintEn,tcc,tccMode,fwid,stat,syncDim,dam,sam);

        num_lines     =      4;
        num_bytes     =     64;
        pitch         =     64;

        /*---------------------------------------------------------------*/
        /*  Disable interrupts during the entire period of IDMA          */
        /*  registers programmation and transfer for correct operation.  */
        /*  The IDMA is a shared resource and other threads should wait  */
        /*  for the completion. Note we can disable this disable of      */
        /*  interrupts later, as we will be in an ISR, and therefore     */
        /*  interrupts cannot happen anyway.                             */
        /*---------------------------------------------------------------*/

        restore_value   = _disable_interrupts();

        /*---------------------------------------------------------------*/
        /*  Set transfer pending status flag, to indicate that transfer  */
        /*  is in progress.                                              */
        /*---------------------------------------------------------------*/

        *trf_pend  =  TRUE;

        /*---------------------------------------------------------------*/
        /*  Write up the values of the PARAM in internal memory. Use     */
        /*  IDMA Channel 0 to perform transfer. Mask is 0xFFFFFF00,      */
        /*  as only 8 out of 32 words needs to be written.               */
        /*---------------------------------------------------------------*/

        trigParam     =    edmaResources.baseParam[chan];
        trigParam[0]  =    (unsigned int) opt_2d_2d;
        trigParam[1]  =    ((unsigned int) src   - CGEM_MEM_OFFSET);
        trigParam[2]  =    pack2(num_lines, num_bytes);
        trigParam[3]  =    ((unsigned int) dst_4 - CGEM_MEM_OFFSET);
        trigParam[4]  =    pack2(pitch, pitch);
        trigParam[5]  =    pack2(num_lines, 0xFFFF);
        trigParam[6]  =    (0x0 << 16) | (0x0);
        trigParam[7]  =     0x1;


        /*---------------------------------------------------------------*/
        /*  If channel is EDMA channel then set the associated event in  */
        /*  either ESR or ESRH.                                          */
        /*---------------------------------------------------------------*/

        if (edmaResources.dmaAttr[chan] == DMA_CHAN_ATTR_EDMA)
        {
            evt_no = edmaResources.logicalChannelNo[chan];
            DMA_SUBMIT(edma_cc , 0x1<<evt_no);
        }

        /*---------------------------------------------------------------*/
        /* Restore the previous state. This finishes submission phase    */
        /* of EDMA.                                                      */
        /*---------------------------------------------------------------*/

        _restore_interrupts(restore_value);

        /*---------------------------------------------------------------*/
        /*  Here is where we start checking for the completion of the    */
        /*  transfer, so we have to disable interrupts.                  */
        /*---------------------------------------------------------------*/

        restore_value   = _disable_interrupts();

        /*---------------------------------------------------------------*/
        /*  Check completion by reading either IPR or IPRH based on      */
        /*  the TCC bit that has been selected.                          */
        /*---------------------------------------------------------------*/

        tcc       =  edmaResources.tccVal[chan];

        /*---------------------------------------------------------------*/
        /*  Irrespective of edma or qdma clear either IPR/IPRH.          */
        /*---------------------------------------------------------------*/

        DMA_WAIT(edma_cc, 0x1<<tcc);

        /*---------------------------------------------------------------*/
        /*  Clear trf_pend status, as we have finished waiting on trans. */
        /*---------------------------------------------------------------*/

        *trf_pend   = FALSE;

        /*---------------------------------------------------------------*/
        /* Restore the previous state. This finishes submission phase    */
        /* of EDMA.                                                      */
        /*---------------------------------------------------------------*/

        _restore_interrupts(restore_value);

         /*---------------------------------------------------------------*/
         /*  Program in 8 words that represent 1 TR request.              */
         /*                                                               */
         /*  WORD0:  OPTIONS field.                                       */
         /*  WORD1:  Sorce address (SRC).                                 */
         /*  WORD2:  BCNT | ACNT. BCNT needs to be num_lines              */
         /*  ACNT is the number of 1D bytes to be transferred.            */
         /*  WORD3:  Destination address (DST).                           */
         /*  WORD4:  DSTBIDX | SRBIDX.                                    */
         /*  DSTBIDX: dst_pitch and SRCBIDX: src_pitch                    */
         /*  WORD5:  BCNTRLD | LINK. This is the same as BCNT.            */
         /*  No linking is needed and hence the link field is             */
         /*  set to 0xFFFF.                                               */
         /*  WORD6:  DSTCIDX | SRCCIDX. This is not used and              */
         /*  hence both these are set to be 0x0.                          */
         /*  WORD7:  CCNT is 1.                                           */
         /*                                                               */
         /*  Here we do a 2D -> 2D transfer with "src" and "dst" pitches  */
         /*  being different, src_pitch is 48 bytes and dst_pitch is 64   */
         /*  bytes.                                                       */
         /*---------------------------------------------------------------*/

         num_lines     =      4;
         num_bytes     =     64;
         src_pitch     =     48;
         dst_pitch     =     64;

        /*---------------------------------------------------------------*/
        /*  Disable interrupts during the entire period of IDMA          */
        /*  registers programmation and transfer for correct operation.  */
        /*  The IDMA is a shared resource and other threads should wait  */
        /*  for the completion. Note we can disable this disable of      */
        /*  interrupts later, as we will be in an ISR, and therefore     */
        /*  interrupts cannot happen anyway.                             */
        /*---------------------------------------------------------------*/

        restore_value   = _disable_interrupts();

        /*---------------------------------------------------------------*/
        /*  Set transfer pending status flag, to indicate that transfer  */
        /*  is in progress.                                              */
        /*---------------------------------------------------------------*/

        *trf_pend  =  TRUE;

        /*---------------------------------------------------------------*/
        /*  Write up the values of the PARAM in internal memory. Use     */
        /*  IDMA Channel 0 to perform transfer. Mask is 0xFFFFFF00,      */
        /*  as only 8 out of 32 words needs to be written. Here we       */
        /*  have seperate source and destination pitches.                */
        /*---------------------------------------------------------------*/

        trigParam       =    edmaResources.baseParam[chan];
        trigParam[0]    =   (unsigned int) opt_2d_2d;
        trigParam[1]    =   ((unsigned int) src   - CGEM_MEM_OFFSET);
        trigParam[2]    =   pack2(num_lines, num_bytes);
        trigParam[3]    =   ((unsigned int) dst_5 - CGEM_MEM_OFFSET);
        trigParam[4]    =   pack2(dst_pitch, src_pitch);
        trigParam[5]    =   pack2(num_lines, 0xFFFF);
        trigParam[6]    =   (0x0 << 16) | (0x0);
        trigParam[7]    =    0x1;

        /*---------------------------------------------------------------*/
        /*  If channel is EDMA channel then set the associated event in  */
        /*  either ESR or ESRH.                                          */
        /*---------------------------------------------------------------*/

        if (edmaResources.dmaAttr[chan] == DMA_CHAN_ATTR_EDMA)
        {
            evt_no = edmaResources.logicalChannelNo[chan];
            DMA_SUBMIT(edma_cc , 0x1<<evt_no);
        }

        /*---------------------------------------------------------------*/
        /* Restore the previous state. This finishes submission phase    */
        /* of EDMA.                                                      */
        /*---------------------------------------------------------------*/

        _restore_interrupts(restore_value);

        /*---------------------------------------------------------------*/
        /*  Here is where we start checking for the completion of the    */
        /*  transfer, so we have to disable interrupts.                  */
        /*---------------------------------------------------------------*/

        restore_value   = _disable_interrupts();

        /*---------------------------------------------------------------*/
        /*  Check completion by reading either IPR or IPRH based on      */
        /*  the TCC bit that has been selected.                          */
        /*---------------------------------------------------------------*/

        tcc       =  edmaResources.tccVal[chan];

        /*---------------------------------------------------------------*/
        /*  Irrespective of edma or qdma clear either IPR/IPRH.          */
        /*---------------------------------------------------------------*/

        DMA_WAIT(edma_cc, 0x1<<tcc);

        /*---------------------------------------------------------------*/
        /*  Clear trf_pend status, as we have finished waiting on trans. */
        /*---------------------------------------------------------------*/

        *trf_pend   = FALSE;

        /*---------------------------------------------------------------*/
        /* Restore the previous state. This finishes submission phase    */
        /* of EDMA.                                                      */
        /*---------------------------------------------------------------*/

        _restore_interrupts(restore_value);

        /*---------------------------------------------------------------*/
        /*  Disable interrupts during the entire period of IDMA          */
        /*  registers programmation and transfer for correct operation.  */
        /*  The IDMA is a shared resource and other threads should wait  */
        /*  for the completion. Note we can disable this disable of      */
        /*  interrupts later, as we will be in an ISR, and therefore     */
        /*  interrupts cannot happen anyway.                             */
        /*---------------------------------------------------------------*/

        restore_value   = _disable_interrupts();

        /*---------------------------------------------------------------*/
        /*  Set transfer pending status flag, to indicate that transfer  */
        /*  is in progress.                                              */
        /*---------------------------------------------------------------*/

        *trf_pend  =  TRUE;

        /*---------------------------------------------------------------*/
        /*  Write up the values of the PARAM in internal memory. We      */
        /*  have to prepare the options field once, upfront, to use      */
        /*  ASYNC, transfer complete chaining enable, transfer compl.    */
        /*  interrupt disable, evt_no for chaining in CER, early         */
        /*  completion, entry is updated as normal. SRC and DST are      */
        /*  set in increment mode. Read the param no, for this chan.     */
        /*  and figure out link address by adding 32 bytes or 1 PARAM.   */
        /*---------------------------------------------------------------*/

        param_chan  = (unsigned int) edmaResources.baseParam[chan];
        link_addr   =  param_chan + 32;

        chan       =  0x0;
        itccEn     =  CSL_EDMACC_OPT_ITCCHEN_DISABLE;
        tccEn      =  CSL_EDMACC_OPT_TCCHEN_ENABLE;
        itcintEn   =  CSL_EDMACC_OPT_ITCINTEN_DISABLE;
        tcintEn    =  CSL_EDMACC_OPT_TCINTEN_DISABLE;
        evt_no     =  edmaResources.logicalChannelNo[chan];
        tccMode    =  CSL_EDMACC_OPT_TCCMODE_EARLY;
        fwid       =  CSL_EDMACC_OPT_FWID_8;
        stat       =  CSL_EDMACC_OPT_STATIC_NORMAL;
        syncDim    =  CSL_EDMACC_OPT_SYNCDIM_ASYNC;
        dam        =  CSL_EDMACC_OPT_DAM_INCR;
        sam        =  CSL_EDMACC_OPT_SAM_INCR;

        /*---------------------------------------------------------------*/
        /*  Now prepare options for 1D -> 1D with linking and chaining.  */
        /*---------------------------------------------------------------*/

        opt_1d_1d_link_chain  =
        CSL_EDMA_OPT_MAKE
        (itccEn,tccEn,itcintEn,tcintEn,evt_no,tccMode,fwid,stat,syncDim,dam,sam);

        tccEn      =  CSL_EDMACC_OPT_TCCHEN_DISABLE;
        tcc_no     =  edmaResources.tccVal[chan];

        opt_1d_1d_link  =   0; // QDMA

        /*---------------------------------------------------------------*/
        /*  We want to do 6 linked transfers, we setup a loop. Keep      */
        /*  incrementing the link_address by 32 bytes. Pack src and      */
        /*  dst addresses along with num_bytes.                          */
        /*---------------------------------------------------------------*/

        trigParam       =    edmaResources.baseParam[chan];

        for (j = 0; j < 48; j+= 8)
        {
            in         = (j >> 3);
            link_addr &= 0xFFFF;

            if (dmaAttr == DMA_CHAN_ATTR_EDMA)  trigParam[j + 0]  = (unsigned int) (opt_1d_1d_link_chain);
            else                        trigParam[j + 0]  = (unsigned int) (opt_1d_1d_link);

            trigParam[j + 1]  = ((unsigned int) src_1d_1d[in] - CGEM_MEM_OFFSET);
            trigParam[j + 2]  = pack2(0x1, num_bytes_1d_1d[in]);
            trigParam[j + 3]  = ((unsigned int) dst_1d_1d[in] - CGEM_MEM_OFFSET);
            trigParam[j + 4]  = pack2(0x0, 0x0);
            trigParam[j + 5]  = pack2(0x1, link_addr);
            trigParam[j + 6]  = (0x0 << 16) | (0x0);
            if  (j) trigParam[j + 7]  =  0x1;

            link_addr  += 32;
        }

        /*---------------------------------------------------------------*/
        /*  Back up loop counter by 8. This will be used for fixing      */
        /*  last param.                                                  */
        /*---------------------------------------------------------------*/

        j -= 8;

        /*---------------------------------------------------------------*/
        /*  Set the link address for the last transfer to terminate.     */
        /*  Always set the last link to post completion. It is assumed   */
        /*  that the last link will always use the TCC allocated for     */
        /*  the channel as a whole irrespective of what the user         */
        /*  passes. Fix up options field.                                */
        /*---------------------------------------------------------------*/

        trigParam[j + 0] = opt_1d_1d;
        trigParam[j + 5] = pack2(0x1, 0xFFFF);

        /*---------------------------------------------------------------*/
        /* Ok, to write trigger word here after setting up everything.   */
        /* For EDMA this is always safe, for QDMA kicks off transfer.    */
        /*---------------------------------------------------------------*/

        trigParam[7]     =  1;

        /*---------------------------------------------------------------*/
        /*  If channel is EDMA channel then set the associated event in  */
        /*  either ESR or ESRH.                                          */
        /*---------------------------------------------------------------*/

        if (dmaAttr == DMA_CHAN_ATTR_EDMA)
        {
            evt_no = edmaResources.logicalChannelNo[chan];
            DMA_SUBMIT (edma_cc, 0x1<<evt_no);
        }

        /*---------------------------------------------------------------*/
        /* Restore the previous state. This finishes submission phase    */
        /* of EDMA.                                                      */
        /*---------------------------------------------------------------*/

        _restore_interrupts(restore_value);

        /*---------------------------------------------------------------*/
        /*  Here is where we start checking for the completion of the    */
        /*  transfer, so we have to disable interrupts.                  */
        /*---------------------------------------------------------------*/

        restore_value   = _disable_interrupts();

        /*---------------------------------------------------------------*/
        /*  Check completion by reading either IPR or IPRH based on      */
        /*  the TCC bit that has been selected.                          */
        /*---------------------------------------------------------------*/

        tcc       =  edmaResources.tccVal[chan];

        /*---------------------------------------------------------------*/
        /*  Irrespective of edma or qdma clear either IPR/IPRH.          */
        /*---------------------------------------------------------------*/

        DMA_WAIT(edma_cc, 0x1<<tcc);

        /*---------------------------------------------------------------*/
        /*  Clear trf_pend status, as we have finished waiting on trans. */
        /*---------------------------------------------------------------*/

        *trf_pend   = FALSE;

        /*---------------------------------------------------------------*/
        /* Restore the previous state. This finishes submission phase    */
        /* of EDMA.                                                      */
        /*---------------------------------------------------------------*/

        _restore_interrupts(restore_value);

        /*---------------------------------------------------------------*/
        /*  Disable interrupts during the entire period of IDMA          */
        /*  registers programmation and transfer for correct operation.  */
        /*  The IDMA is a shared resource and other threads should wait  */
        /*  for the completion. Note we can disable this disable of      */
        /*  interrupts later, as we will be in an ISR, and therefore     */
        /*  interrupts cannot happen anyway.                             */
        /*---------------------------------------------------------------*/

        restore_value   = _disable_interrupts();

        /*---------------------------------------------------------------*/
        /*  Set transfer pending status flag, to indicate that transfer  */
        /*  is in progress.                                              */
        /*---------------------------------------------------------------*/

        *trf_pend  =  TRUE;

        /*---------------------------------------------------------------*/
        /*  Write up the values of the PARAM in internal memory. We      */
        /*  have to prepare the options field once, upfront, to use      */
        /*  ABSYNC, transfer complete chaining enable, transfer compl.   */
        /*  interrupt disable, evt_no for chaining in CER, early         */
        /*  completion, entry is updated as normal. SRC and DST are      */
        /*  set in increment mode. Read the param no, for this chan.     */
        /*  and figure out link address by adding 32 bytes or 1 PARAM.   */
        /*  This is for linked 1D -> 2d example.                         */
        /*---------------------------------------------------------------*/

        param_chan  = (unsigned int) edmaResources.baseParam[chan];
        link_addr   =  param_chan + 32;

        chan       =  0x0;
        itccEn     =  CSL_EDMACC_OPT_ITCCHEN_DISABLE;
        tccEn      =  CSL_EDMACC_OPT_TCCHEN_ENABLE;
        itcintEn   =  CSL_EDMACC_OPT_ITCINTEN_DISABLE;
        tcintEn    =  CSL_EDMACC_OPT_TCINTEN_DISABLE;
        evt_no     =  edmaResources.logicalChannelNo[chan];
        tccMode    =  CSL_EDMACC_OPT_TCCMODE_EARLY;
        fwid       =  CSL_EDMACC_OPT_FWID_8;
        stat       =  CSL_EDMACC_OPT_STATIC_NORMAL;
        syncDim    =  CSL_EDMACC_OPT_SYNCDIM_ABSYNC;
        dam        =  CSL_EDMACC_OPT_DAM_INCR;
        sam        =  CSL_EDMACC_OPT_SAM_INCR;

        /*---------------------------------------------------------------*/
        /*  Now prepare options for 1D -> 2D with linking and chaining.  */
        /*---------------------------------------------------------------*/

        opt_1d_2d_link_chain  =
        CSL_EDMA_OPT_MAKE
        (itccEn,tccEn,itcintEn,tcintEn,evt_no,tccMode,fwid,stat,syncDim,dam,sam);

        tccEn      =  CSL_EDMACC_OPT_TCCHEN_DISABLE;


        opt_1d_2d_link   =
        CSL_EDMA_OPT_MAKE
        (0, 0, 0, 0, 0, 0, 0, 0, CSL_EDMACC_OPT_SYNCDIM_ABSYNC, 0, 0);

        /*---------------------------------------------------------------*/
        /*  We want to do 6 linked transfers, we setup a loop. Keep      */
        /*  incrementing the link_address by 32 bytes. Pack src and      */
        /*  dst addresses along with num_bytes.                          */
        /*---------------------------------------------------------------*/

        trigParam       =    edmaResources.baseParam[chan];

        for (j = 0; j < 48; j+= 8)
        {
            in         = (j >> 3);
            link_addr &= 0xFFFF;

            if (dmaAttr == DMA_CHAN_ATTR_EDMA) trigParam[j + 0]  = (unsigned int) (opt_1d_2d_link_chain);
            else                       trigParam[j + 0]  = (unsigned int) (opt_1d_2d_link);

            trigParam[j + 1]  = ((unsigned int) src_1d_2d[in] - CGEM_MEM_OFFSET);
            trigParam[j + 2]  = pack2(num_lines_1d_2d[in], num_bytes_1d_2d[in]);
            trigParam[j + 3]  = ((unsigned int) dst_1d_2d[in] - CGEM_MEM_OFFSET);
            trigParam[j + 4]  = pack2(pitch_1d_2d[in], num_bytes_1d_2d[in]);
            trigParam[j + 5]  = pack2(num_lines_1d_2d[in], link_addr);
            trigParam[j + 6]  = (0x0 << 16) | (0x0);

            if (j)
            trigParam[j + 7]  =  0x1;

            link_addr  += 32;
        }

        /*---------------------------------------------------------------*/
        /*  Back up loop counter by 8. This will be used for fixing      */
        /*  last param.                                                  */
        /*---------------------------------------------------------------*/

        j -= 8;

        /*---------------------------------------------------------------*/
        /*  Set the link address for the last transfer to terminate.     */
        /*  Always set the last link to post completion. It is assumed   */
        /*  that the last link will always use the TCC allocated for     */
        /*  the channel as a whole irrespective of what the user         */
        /*  passes. Fix up options field.                                */
        /*---------------------------------------------------------------*/

        trigParam[j + 0] = opt_1d_2d;
        trigParam[j + 5] = pack2(num_lines_1d_2d[j >> 3], 0xFFFF);

        /*---------------------------------------------------------------*/
        /* Ok, to write trigger word here after setting up everything.   */
        /* For EDMA this is always safe, for QDMA kicks off transfer.    */
        /*---------------------------------------------------------------*/

        trigParam[7]     =  1;

        /*---------------------------------------------------------------*/
        /*  If channel is EDMA channel then set the associated event in  */
        /*  either ESR or ESRH.                                          */
        /*---------------------------------------------------------------*/

        /*---------------------------------------------------------------*/
        /*  If channel is EDMA channel then set the associated event in  */
        /*  either ESR or ESRH.                                          */
        /*---------------------------------------------------------------*/

        if (dmaAttr == DMA_CHAN_ATTR_EDMA)
        {
            evt_no = edmaResources.logicalChannelNo[chan];
            DMA_SUBMIT (edma_cc, 0x1<<evt_no);
        }

        /*---------------------------------------------------------------*/
        /* Restore the previous state. This finishes submission phase    */
        /* of EDMA.                                                      */
        /*---------------------------------------------------------------*/

        _restore_interrupts(restore_value);

        /*---------------------------------------------------------------*/
        /*  Here is where we start checking for the completion of the    */
        /*  transfer, so we have to disable interrupts.                  */
        /*---------------------------------------------------------------*/

        restore_value   = _disable_interrupts();

        /*---------------------------------------------------------------*/
        /*  Check completion by reading either IPR or IPRH based on      */
        /*  the TCC bit that has been selected.                          */
        /*---------------------------------------------------------------*/

        tcc       =  edmaResources.tccVal[chan];

        /*---------------------------------------------------------------*/
        /*  Irrespective of edma or qdma clear either IPR/IPRH.          */
        /*---------------------------------------------------------------*/

        DMA_WAIT ( edma_cc ,0x1<<tcc);

        /*---------------------------------------------------------------*/
        /*  Clear trf_pend status, as we have finished waiting on trans. */
        /*---------------------------------------------------------------*/

        *trf_pend   = FALSE;

        if (dmaAttr == DMA_CHAN_ATTR_QDMA) goto test_results;

        /*---------------------------------------------------------------*/
        /* Restore the previous state. This finishes submission phase    */
        /* of EDMA.                                                      */
        /*---------------------------------------------------------------*/

        _restore_interrupts(restore_value);

        chan       =  0x0;
        itccEn     =  CSL_EDMACC_OPT_ITCCHEN_DISABLE;
        tccEn      =  CSL_EDMACC_OPT_TCCHEN_DISABLE;
        itcintEn   =  CSL_EDMACC_OPT_ITCINTEN_ENABLE;
        tcintEn    =  CSL_EDMACC_OPT_TCINTEN_ENABLE;
        tcc        =  edmaResources.tccVal[chan];
        tccMode    =  CSL_EDMACC_OPT_TCCMODE_NORMAL;
        fwid       =  CSL_EDMACC_OPT_FWID_8;
        stat       =  CSL_EDMACC_OPT_STATIC_NORMAL;
        syncDim    =  CSL_EDMACC_OPT_SYNCDIM_ASYNC;
        dam        =  CSL_EDMACC_OPT_DAM_INCR;
        sam        =  CSL_EDMACC_OPT_SAM_INCR;

        opt_1d_1d_norm  =
        CSL_EDMA_OPT_MAKE
        (itccEn,tccEn,itcintEn,tcintEn,tcc,tccMode,fwid,stat,syncDim,dam,sam);

        /*---------------------------------------------------------------*/
        /*  Now setup a 1D -> 1D transfer from src to dst to transfer    */
        /*  256 bytes as 4 sets of 64 bytes. Instead of calling a        */
        /*  dedicated function we  will code it up using EDMA CSL        */
        /*  register level. We will enable event 4 times with auto-incr. */
        /*                                                               */
        /*  Program in 8 words that represent 1 TR request.              */
        /*                                                               */
        /*  WORD0:  OPTIONS field.                                       */
        /*  WORD1:  Sorce address (SRC).                                 */
        /*  WORD2:  BCNT | ACNT. BCNT needs to be 4, and                 */
        /*  ACNT is the number of 1D bytes to be transferred.            */
        /*  WORD3:  Destination address (DST).                           */
        /*  WORD4:  DSTBIDX | SRBIDX.                                    */
        /*  WORD5:  BCNTRLD | LINK. This is the same as BCNT.            */
        /*  No linking is needed and hence the link field is             */
        /*  set to 0xFFFF.                                               */
        /*  WORD6:  DSTCIDX | SRCCIDX. This is not used and              */
        /*  hence both these are set to be 0x0.                          */
        /*  WORD7:  CCNT is 1.                                           */
        /*---------------------------------------------------------------*/

        /*---------------------------------------------------------------*/
        /*  Write up the values of the PARAM in internal memory. Use     */
        /*  IDMA Channel 0 to perform transfer from int_mem to ext_CFG.  */
        /*  We want to transfer 4 sets of 64 bytes, so num_bytes is 64.  */
        /*---------------------------------------------------------------*/

        num_bytes  =    64;

        /*---------------------------------------------------------------*/
        /*  Set up attributes of the 1D -> 1D transfer in intern mem.    */
        /*---------------------------------------------------------------*/

        trigParam       =   edmaResources.baseParam[chan];
        trigParam[0]    =   (unsigned int) opt_1d_1d_norm;
        trigParam[1]    =   ((unsigned int) src - CGEM_MEM_OFFSET);
        trigParam[2]    =   pack2(0x4, num_bytes);
        trigParam[3]    =   ((unsigned int) dst_8 - CGEM_MEM_OFFSET);
        trigParam[4]    =   pack2(num_bytes, num_bytes);
        trigParam[5]    =   pack2(0x4, 0xFFFF);
        trigParam[6]    =   (0x0 << 16) | (0x0);
        trigParam[7]    =    0x1;
        /*--------------------------------------------------------------*/
        /*  Now iterate in a loop for 4 times, enabling event and       */
        /*  verifying completion.                                       */
        /*---------------------------------------------------------------*/

        for (j = 0; j < 4; j++)
        {
            /*-----------------------------------------------------------*/
            /*  This is the submission phase.                            */
            /*-----------------------------------------------------------*/

             restore_value   = _disable_interrupts();
             *trf_pend       =  TRUE;
             evt_no = edmaResources.logicalChannelNo[chan];
             DMA_SUBMIT(edma_cc , 0x1<<evt_no);
             _restore_interrupts(restore_value);

             /*-----------------------------------------------------------*/
             /*  This is the verification of the completion phase.        */
             /*-----------------------------------------------------------*/

             restore_value   = _disable_interrupts();

             tcc             =  edmaResources.tccVal[chan];
             DMA_WAIT(edma_cc, 0x1<<tcc);
             *trf_pend   = FALSE;
             _restore_interrupts(restore_value);
        }

test_results:

        DMA_resourceAllocator_deallocateResources(edma_cc,&edmaResources);


        printf("i:%2d, evt:%2d, que:%2d, tcc:%2d, trigParam:%2x \n",
                i,
                edmaResources.logicalChannelNo[chan],
                edmaResources.queNo[chan],
                tcc_no,
                edmaResources.baseParam[chan]
              );




        /*---------------------------------------------------------------*/
        /*  Now compare destination with expected destination, and see   */
        /*  if they match, printing out pass/fail status for 1D -> 1D.   */
        /*---------------------------------------------------------------*/

        fail_1d_1d = (memcmp(e_dst_1, dst_1, sizeof(e_dst_1)));

        if (fail_1d_1d)
        {
            printf ("Fail in 1D -> 1D transfer \n");
            exit (-1);
        }

        /*---------------------------------------------------------------*/
        /*  Now compare destination with expected destination, and see   */
        /*  if they match, printing out pass/fail status for 1D -> 2D.   */
        /*---------------------------------------------------------------*/

        fail_1d_2d = (memcmp(e_dst_2, dst_2, sizeof(e_dst_2)));

        if (fail_1d_2d)
        {
            printf ("Fail in 1D -> 2D transfer \n");
            exit (-1);
        }

        /*---------------------------------------------------------------*/
        /*  Now compare destination with expected destination, and see   */
        /*  if they match, printing out pass/fail status for 2D -> 1D.   */
        /*---------------------------------------------------------------*/

        fail_2d_1d = (memcmp(e_dst_3, dst_3, sizeof(e_dst_3)));

        if (fail_2d_1d)
        {
            printf ("Fail in 2D -> 1D transfer \n");
            exit (-1);
        }

        /*---------------------------------------------------------------*/
        /*  Now compare destination with expected destination, and see   */
        /*  if they match, printing out pass/fail status for 2D -> 1D.   */
        /*---------------------------------------------------------------*/

        fail_2d_2d = (memcmp(e_dst_4, dst_4, sizeof(e_dst_4)));

        if (fail_2d_2d)
        {
            printf ("Fail in 2D -> 2D transfer \n");
            exit (-1);
        }

        /*---------------------------------------------------------------*/
        /*  Now compare destination with expected destination, and see   */
        /*  if they match, printing out pass/fail status for 2D -> 2D.   */
        /*---------------------------------------------------------------*/

        fail_2d_2d_sep = (memcmp(e_dst_5, dst_5, sizeof(e_dst_5)));

        if (fail_2d_2d_sep)
        {
            printf ("Fail in 2D -> 2D sep. transfer \n");
            exit (-1);
        }

        /*---------------------------------------------------------------*/
        /*  Assert that all previous interrupts have been cleared and    */
        /*  serviced. Assert that there are no TC errors in EDMA3 CC     */
        /*  error register.                                              */
        /*---------------------------------------------------------------*/

        assert (edma_cc->IPR    == 0);
        assert (edma_cc->CCERR == 0);

        /*---------------------------------------------------------------*/
        /* Do further tests only if this is an EDMA channel.             */
        /*---------------------------------------------------------------*/

        /*---------------------------------------------------------------*/
        /*  Now compare destination with expected destination, and see   */
        /*  if they match, printing out pass/fail status for 1D -> 1D.   */
        /*  link and chain.                                              */
        /*---------------------------------------------------------------*/

        fail_1d_1d_lnk = (memcmp(e_dst_6, dst_6, sizeof(e_dst_6)));

        if (fail_1d_1d_lnk)
        {
            printf ("Fail in 1D -> 1D link and chain\n");
            exit (-1);
        }

        /*---------------------------------------------------------------*/
        /*  Now compare destination with expected destination, and see   */
        /*  if they match, printing out pass/fail status for 1D -> 2D.   */
        /*  link and chain.                                              */
        /*---------------------------------------------------------------*/

        fail_1d_2d_lnk = (memcmp(e_dst_7, dst_7, sizeof(e_dst_7)));

        if (fail_1d_2d_lnk)
        {
            printf ("Fail in 1D -> 2D link and chain\n");
            exit (-1);
        }

        /*---------------------------------------------------------------*/
        /*  Now compare destination with expected destination, and see   */
        /*  if they match, printing out pass/fail status for 1D -> 1D.   */
        /*  auto incr.                                                   */
        /*---------------------------------------------------------------*/

        if (dmaAttr == DMA_CHAN_ATTR_EDMA)
        fail_1d_1d_inc = (memcmp(e_dst_8, dst_8, sizeof(e_dst_8)));
        else
        fail_1d_1d_inc = 0;

        if (fail_1d_1d_inc)
        {
            printf ("Fail in 1D -> 1D auot.inc\n");
            exit (-1);
        }

   }

   if (dmaAttr == DMA_CHAN_ATTR_EDMA)
   printf("------------------------EDMA_CHAN---------------------------------\n");
   else
   printf("------------------------QDMA_CHAN---------------------------------\n");
   if (!fail_1d_1d)     printf("Pass in 1d -> 1d             %d transfers \n", i);
   if (!fail_1d_2d)     printf("Pass in 1d -> 2d             %d transfers \n", i);
   if (!fail_2d_1d)     printf("Pass in 2d -> 1d             %d transfers \n", i);
   if (!fail_2d_2d)     printf("Pass in 2d -> 2d             %d transfers \n", i);
   if (!fail_2d_2d_sep) printf("Pass in 2d -> 2d sep.        %d transfers \n", i);
   if (!fail_1d_1d_lnk) printf("Pass in 1d -> 1d lnk & chain %d transfers \n", i);
   if (!fail_1d_2d_lnk) printf("Pass in 1d -> 2d lnk & chain %d transfers \n", i);
   if (!fail_1d_1d_inc) printf("Pass in 1d -> 1d auto incr.  %d transfers \n", i);

   printf("------------------------------------------------------------\n");
}

/*-----------------------------------------------------------------------*/
/*  End of file main.c                                                   */
/*=======================================================================*/
/*  Texas Instruments incorporated 2002-2006.                            */
/*-----------------------------------------------------------------------*/

