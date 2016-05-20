/* ======================================================================
 *   Copyright (C) 2013 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

/*
 * main.c
 */
#include "stdint.h"
#include <common/stw_types.h>
#include "uartStdio.h"
#include "edma.h"
#include "sample.h"
#include "interrupt.h"
#include "hw_types.h"

extern signed char       _srcBuff1[MAX_BUFFER_SIZE];
extern signed char       _dstBuff1[MAX_BUFFER_SIZE];
extern signed char       _srcBuff2[MAX_BUFFER_SIZE];
extern signed char       _dstBuff2[MAX_BUFFER_SIZE];

extern signed char      *srcBuff1;
extern signed char      *dstBuff1;
extern signed char      *srcBuff2;
extern signed char      *dstBuff2;

extern volatile uint32_t transfer_complete;

extern uint32_t          base_address;
int32_t qdma_link_test(uint32_t ch_num, uint32_t tcc_num, uint32_t evtq_num,
                       uint32_t edma_paRAMId1, uint32_t edma_paRAMId2,
                       uint32_t aCnt, uint32_t bCnt,
                       uint32_t cCnt)
{
    int32_t           count;
    volatile uint32_t i, error = SUCCESS;
    EDMA3CCPaRAMEntry edmaParam;
    EDMA3CCPaRAMEntry edmaLinkParam;

    srcBuff1 = (signed char *) (_srcBuff1);
    dstBuff1 = (signed char *) (_dstBuff1);

    srcBuff2 = (signed char *) (_srcBuff2);
    dstBuff2 = (signed char *) (_dstBuff2);

    UARTPuts("\nQdma Link test", -1);

    /*
     * Initialize the source address with a pattern
     * Initialize source and destination buffers
     */

    for (count = 0U; count < (aCnt * bCnt * cCnt); count++)
    {
        srcBuff1[count] = (int) 0x22;
        srcBuff2[count] = (int) 0x33;

        dstBuff1[count] = 0;
        dstBuff2[count] = 0;
    }

    /* Set params for channel 1*/
    EDMA3RequestChannel(base_address, EDMA3_CHANNEL_TYPE_QDMA, ch_num, tcc_num,
                        evtq_num);
    EDMA3MapQdmaChToPaRAM(base_address, ch_num, &edma_paRAMId1);

    EDMA3EnableQdmaEvt(base_address, ch_num);

    EDMA3SetQdmaTrigWord(base_address, ch_num, EDMA3CC_PARAM_ENTRY_SRC_DST_CIDX);

    edmaParam.opt        = 0;
    edmaParam.srcAddr    = (uint32_t) srcBuff1;
    edmaParam.destAddr   = (uint32_t) dstBuff1;
    edmaParam.aCnt       = aCnt;
    edmaParam.bCnt       = bCnt;
    edmaParam.cCnt       = cCnt;
    edmaParam.srcBIdx    = aCnt;
    edmaParam.destBIdx   = aCnt;
    edmaParam.srcCIdx    = aCnt;
    edmaParam.destCIdx   = aCnt;
    edmaParam.bCntReload = bCnt;
    edmaParam.linkAddr   =
        (uint16_t) ((base_address + EDMA_TPCC_OPT(edma_paRAMId2)) & 0x0FFFF);
    edmaParam.opt |= (EDMA3_OPT_ITCINTEN_MASK |
                      ((tcc_num << EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));

    /* Set second set of parameters for link transfer*/
    edmaLinkParam.opt        = 0;
    edmaLinkParam.srcAddr    = (uint32_t) srcBuff2;
    edmaLinkParam.destAddr   = (uint32_t) dstBuff2;
    edmaLinkParam.aCnt       = aCnt;
    edmaLinkParam.bCnt       = bCnt;
    edmaLinkParam.cCnt       = cCnt;
    edmaLinkParam.srcBIdx    = aCnt;
    edmaLinkParam.destBIdx   = aCnt;
    edmaLinkParam.srcCIdx    = aCnt;
    edmaLinkParam.destCIdx   = aCnt;
    edmaLinkParam.bCntReload = bCnt;
    edmaLinkParam.linkAddr   = 0xFFFFU;
    edmaLinkParam.opt       |=
        (EDMA3_OPT_TCINTEN_MASK | EDMA3_OPT_ITCINTEN_MASK |
         ((tcc_num <<
           EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));
    if ((bCnt * cCnt) == 1)
    {
        edmaLinkParam.opt |= EDMA_TPCC_OPT_STATIC_MASK;
    }

    /*
     * Setting the parameter for edma_paRAMId2.
     * The PaRAM set with ID edma_paRAMId2 is used for linking with channel
     * ch_num
     */
    EDMA3SetPaRAM(base_address, edma_paRAMId2, &edmaLinkParam);

    /*
     * Enable transfer by writing to the PaRAM set of first PaRAM
     * First Transfer is enabled when PaRAM set is written.
     * Remaining ((bCnt * cCnt) - 1) times on primary PaRAM trigger by writing
     * to trigger word.
     */
    transfer_complete = 0;
    EDMA3QdmaSetPaRAMEntry(base_address, edma_paRAMId1, EDMA3CC_PARAM_ENTRY_OPT,
                           edmaParam.opt);
    EDMA3QdmaSetPaRAMEntry(base_address, edma_paRAMId1, EDMA3CC_PARAM_ENTRY_SRC,
                           edmaParam.srcAddr);
    EDMA3QdmaSetPaRAMEntry(base_address, edma_paRAMId1,
                           EDMA3CC_PARAM_ENTRY_ACNT_BCNT,
                           edmaParam.bCnt << 16 | edmaParam.aCnt);
    EDMA3QdmaSetPaRAMEntry(base_address, edma_paRAMId1, EDMA3CC_PARAM_ENTRY_DST,
                           edmaParam.destAddr);
    EDMA3QdmaSetPaRAMEntry(base_address, edma_paRAMId1,
                           EDMA3CC_PARAM_ENTRY_SRC_DST_BIDX,
                           edmaParam.destBIdx << 16 | edmaParam.srcBIdx);
    EDMA3QdmaSetPaRAMEntry(base_address, edma_paRAMId1,
                           EDMA3CC_PARAM_ENTRY_LINK_BCNTRLD,
                           edmaParam.bCntReload << 16 | edmaParam.linkAddr);
    EDMA3QdmaSetPaRAMEntry(base_address, edma_paRAMId1,
                           EDMA3CC_PARAM_ENTRY_CCNT,
                           edmaParam.cCnt);
    EDMA3QdmaSetPaRAMEntry(base_address, edma_paRAMId1,
                           EDMA3CC_PARAM_ENTRY_SRC_DST_CIDX,
                           edmaParam.destCIdx << 16 | edmaParam.srcCIdx);

    if (bCnt * cCnt != 1)
    {
        while ((EDMA3GetIntrStatus(base_address) & (0x1 << tcc_num)) !=
               (0x1 << tcc_num)) ;
        EDMA3ClrIntr(base_address, tcc_num);
    }

    /*
     * Transfer is done in a sync mode
     * Number of triggers required are ((bCnt * cCnt) -1)
     * to completes the transfer on primary channel
     */
    for (i = 1; i < (bCnt * cCnt); i++)
    {
        transfer_complete = 0;
        EDMA3QdmaSetPaRAMEntry(base_address, edma_paRAMId1,
                               EDMA3CC_PARAM_ENTRY_SRC_DST_CIDX,
                               (aCnt << 16 | aCnt));
        while ((EDMA3GetIntrStatus(base_address) & (0x1 << tcc_num)) !=
               (0x1 << tcc_num)) ;
        EDMA3ClrIntr(base_address, tcc_num);
    }
    /*
     * Transfer is completed on primary channel.
     * Second PaRAM is linked First Transfer is enabled.
     * On the last trigger the linked channel is copied,
     * Hence first transfer is triggered.
     * Number of triggers required for second PaRAM to complete are ((bCnt *
     * cCnt) -1)
     */
    for (i = 1; i < (bCnt * cCnt); i++)
    {
        if (i == ((bCnt * cCnt) - 1))
        {
            edmaParam.opt = EDMA3QdmaGetPaRAMEntry(base_address, edma_paRAMId1,
                                                   EDMA3CC_PARAM_ENTRY_OPT);
            edmaParam.opt |= EDMA_TPCC_OPT_STATIC_MASK;
            EDMA3QdmaSetPaRAMEntry(base_address, edma_paRAMId1,
                                   EDMA3CC_PARAM_ENTRY_OPT,
                                   edmaParam.opt);
        }
        transfer_complete = 0;
        EDMA3QdmaSetPaRAMEntry(base_address, edma_paRAMId1,
                               EDMA3CC_PARAM_ENTRY_SRC_DST_CIDX,
                               (aCnt << 16 | aCnt));
        while ((EDMA3GetIntrStatus(base_address) & (0x1 << tcc_num)) !=
               (0x1 << tcc_num)) ;
        EDMA3ClrIntr(base_address, tcc_num);
    }
    if (bCnt * cCnt == 1)
    {
        while ((EDMA3GetIntrStatus(base_address) & (0x1 << tcc_num)) !=
               (0x1 << tcc_num)) ;
        EDMA3ClrIntr(base_address, tcc_num);
    }

    for (i = 0; i < (aCnt * bCnt * cCnt); i++)
    {
        if (srcBuff1[i] != dstBuff1[i])
        {
            error = FAIL;
            UARTPuts("\nError matching value at src and dst address", -1);
            break;
        }
    }

    for (i = 0; i < (aCnt * bCnt * cCnt); i++)
    {
        if (srcBuff2[i] != dstBuff2[i])
        {
            error = FAIL;
            UARTPuts("\nError matching value at src and dst address", -1);
            break;
        }
    }
    EDMA3DisableQdmaEvt(base_address, ch_num);

    return error;
}

