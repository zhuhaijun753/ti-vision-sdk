/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*-----------------------------------------------------------------------*/
/*  NAME : main.c                                                        */
/*                                                                       */
/*  REVISION HISTORY:                                                    */
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
#include "tistdtypes.h"
#include "dma_resource_allocator.h"
#include "eve_dma_test_data.h"
#include "dma_funcs.h"

#define NUM_TESTS       1


/*-----------------------------------------------------------------------*/
/*  Zero out all destination buffers and do a cache clean on L2 to make  */
/*  these commit.                                                        */
/*-----------------------------------------------------------------------*/

void dst_buffers_setup()
{
    memset (dst_1, 0x0, sizeof(dst_1));
}


/*-----------------------------------------------------------------------*/
/*  Start of the main test_harness code.                                 */
/*-----------------------------------------------------------------------*/

int main()
{
    /*-------------------------------------------------------------------*/
    /*  Declare a dma state structure with the attributes defined above. */
    /*-------------------------------------------------------------------*/

    DMA_resourceStruct  dmaResourceStruct;
    /*-------------------------------------------------------------------*/
    /*  We declare temporary variables here, which we assume have been   */
    /*  allocated through DMAN3, IDMA3.                                  */
    /*-------------------------------------------------------------------*/

    unsigned int            i,      j;
    unsigned int            num_tests;

    DMA_chanAttr            dmaAttr = DMA_CHAN_ATTR_EDMA;

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
    unsigned int            restoreValue;

    unsigned int            opt_1d_1d;
    unsigned int            fail_1d_1d;

    unsigned int            numBytes;
    unsigned int            linkAddr;

    CSL_EdmaccRegsOvly       edmaCc;
    int                      status;
    unsigned int             numParam;

    unsigned int             submitWord;
    /*-------------------------------------------------------------------*/
    /*  Anchor edmaCc to the start of the EDMA CC0, we only have one    */
    /*  CC so it is CC0.                                                 */
    /*-------------------------------------------------------------------*/

    edmaCc  =  (CSL_EdmaccRegsOvly) (CSL_EDMACC_0_REGS);
    printf ("edmaCc:0x%.8x \n", edmaCc);
    assert ((unsigned int)edmaCc == 0x400A0000);


    /*-------------------------------------------------------------------*/
    /*  The following loop runs for the number of tests requested by     */
    /*  the user, obtains a random event, random tcc, random PARAM       */
    /*  and performa a simple EDMA 1D to 1D transfer for purposes of     */
    /*  illustration.                                                    */
    /*-------------------------------------------------------------------*/

    num_tests = NUM_TESTS;

    dmaAttr = DMA_CHAN_ATTR_EDMA;
    /*--------------------------------------------------------------------*/
    /*  Seed the random number generator.                                 */
    /*--------------------------------------------------------------------*/

    srand (0xFADEBABE);
    numParam = 6;

    DMA_resourceAllocator_initResources();

    for (i = 0; i < num_tests; i++)
    {
        /*---------------------------------------------------------------*/
        /*  In this function we will zero all destinations, so as to     */
        /*  reset executions.                                            */
        /*---------------------------------------------------------------*/

         dst_buffers_setup();


        dmaResourceStruct.numChannels    = 1;
        dmaResourceStruct.numParam[0]    = numParam;
        dmaResourceStruct.dmaAttr[0]     = DMA_CHAN_ATTR_EDMA;
        dmaResourceStruct.queNo[0]       = 0;

        status = DMA_resourceAllocator_allocateResources(edmaCc , &dmaResourceStruct);



       /*---------------------------------------------------------------*/
       /*  Re-program global registers to accomplish the transfer       */
       /*  settings user has asked for.                                 */
       /*---------------------------------------------------------------*/
       DMA_funcs_hardwareRegSetup(edmaCc,&dmaResourceStruct);


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

        chan       =  0x0;
        itccEn     =  CSL_EDMACC_OPT_ITCCHEN_DISABLE;
        tccEn      =  CSL_EDMACC_OPT_TCCHEN_DISABLE;
        itcintEn   =  CSL_EDMACC_OPT_ITCINTEN_ENABLE;
        tcintEn    =  CSL_EDMACC_OPT_TCINTEN_ENABLE;
        tcc        =  dmaResourceStruct.tccVal[chan];
        tccMode    =  CSL_EDMACC_OPT_TCCMODE_NORMAL;
        fwid       =  CSL_EDMACC_OPT_FWID_8;
        stat       =  CSL_EDMACC_OPT_STATIC_NORMAL;
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

        numBytes  =    16;

        /*---------------------------------------------------------------*/
        /*  Disable interrupts during the entire period of IDMA          */
        /*  registers programmation and transfer for correct operation.  */
        /*  The IDMA is a shared resource and other threads should wait  */
        /*  for the completion. Note we can disable this disable of      */
        /*  interrupts later, as we will be in an ISR, and therefore     */
        /*  interrupts cannot happen anyway.                             */
        /*---------------------------------------------------------------*/

        restoreValue   = _disable_interrupts();

        /*---------------------------------------------------------------*/
        /*  Set up attributes of the 1D -> 1D transfer in intern mem.    */
        /*---------------------------------------------------------------*/

        linkAddr = (unsigned int)(dmaResourceStruct.baseParam[chan] + 8);

        printf("chan number %d \n",chan);
        printf("trigger param  %x \n",dmaResourceStruct.baseParam[chan]);
        printf("trigger param  %x \n",linkAddr);

       DMA_funcs_writeTransferParams(dmaResourceStruct.baseParam[chan],
                            opt_1d_1d,
                            ((uint8_t *) (src)   - CGEM_MEM_OFFSET),
                            ((uint8_t *) (dst_1) - CGEM_MEM_OFFSET),
                            numBytes,/*number of Bytes*/
                            0x2,/*number of lines */
                            numBytes,/* Source Line pitch */
                            numBytes,/* destination Line Pitch */
                            numBytes,/* Source CIDX */
                            -numBytes, /* Destination CIDX */
                            0x8,/*cCnt*/
                            linkAddr /* address of the next linked param set */
                            );


        printf("chan number %d \n",chan);
        /*----------------------------------------------------------------*/
        /* Now add an extra  parameter RAM which can do re-write.         */
        /*----------------------------------------------------------------*/

        DMA_funcs_writeTransferParams((volatile uint32_t *)linkAddr,
                                opt_1d_1d,
                                ((uint8_t *) (src)   - CGEM_MEM_OFFSET),
                                ((uint8_t *) (dst_1) - CGEM_MEM_OFFSET),
                                numBytes,/*number of Bytes*/
                                0x2,/*number of lines */
                                numBytes,/* Source Line pitch */
                                numBytes,/* destination Line Pitch */
                                numBytes,/* Source CIDX */
                                -numBytes, /* Destination CIDX */
                                0x8,/*cCnt*/
                                linkAddr /* address of the next linked param set */
                                );

        printf("chan number %d \n",chan);
        /*---------------------------------------------------------------*/
        /*  If channel is EDMA channel then set the associated event in  */
        /*  either ESR or ESRH.                                          */
        /*---------------------------------------------------------------*/

        for (j = 0; j < 24; j++)
        {
            submitWord = 0x1u << dmaResourceStruct.logicalChannelNo[chan];
            DMA_SUBMIT (edmaCc , submitWord);
            DMA_WAIT   (edmaCc , submitWord);
        }

        /*---------------------------------------------------------------*/
        /* Restore the previous state. This finishes submission phase    */
        /* of EDMA.                                                      */
        /*---------------------------------------------------------------*/

        _restore_interrupts(restoreValue);


        DMA_resourceAllocator_deallocateResources( edmaCc,&dmaResourceStruct );


        printf("i:%2d, evt:%2d, que:%2d, tcc:%2d, param:%2d \n",
                i,
                dmaResourceStruct.logicalChannelNo[0],
                dmaResourceStruct.queNo[0],
                dmaResourceStruct.tccVal[0],
                ((unsigned int ) dmaResourceStruct.baseParam[0] - (unsigned int ) &edmaCc->PARAMENTRY[0])
                    >> CSL_EDMACC_DCHMAP_PAENTRY_SHIFT
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

        assert (edmaCc->IPR   == 0);
        assert ((edmaCc->CCERR & 0x1000) == 0);
        assert ((edmaCc->CCERR & 0x3)    != 3);

        /*---------------------------------------------------------------*/
        /* Do further tests only if this is an EDMA channel.             */
        /*---------------------------------------------------------------*/


   }

   if (dmaAttr == DMA_CHAN_ATTR_EDMA)
   printf("------------------------EDMA_CHAN---------------------------------\n");
   if (!fail_1d_1d)     printf("Pass in 1d -> 1d             %d transfers \n", i);

   printf("------------------------------------------------------------\n");
}

/*-----------------------------------------------------------------------*/
/*  End of file main.c                                                   */
/*=======================================================================*/
/*  Texas Instruments incorporated 2002-2006.                            */
/*-----------------------------------------------------------------------*/

