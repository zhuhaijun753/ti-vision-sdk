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

extern signed char      *srcBuff1;
extern signed char      *dstBuff1;

extern volatile uint32_t transfer_complete;

extern uint32_t          base_address;
int32_t qdma_test(uint32_t ch_num, uint32_t tcc_num, uint32_t evtq_num,
                  uint32_t paramId,
                  uint32_t aCnt, uint32_t bCnt,
                  uint32_t cCnt)
{
    volatile uint32_t i, error = SUCCESS, count;
    EDMA3CCPaRAMEntry edmaParam;

    srcBuff1 = (signed char *) (_srcBuff1);
    dstBuff1 = (signed char *) (_dstBuff1);

    UARTPuts("\nQdma test", -1);

    /*
     * Initialize the source address with a pattern
     * initialize dst address with zero/another pattern (optional)
     */
    for (count = 0U; count < (aCnt * bCnt * cCnt); count++)
    {
        srcBuff1[count] = (int) 0xDD;

        dstBuff1[count] = 0;
    }

    EDMA3RequestChannel(base_address, EDMA3_CHANNEL_TYPE_QDMA, ch_num, tcc_num,
                        evtq_num);
    EDMA3MapQdmaChToPaRAM(base_address, ch_num, &paramId);

    EDMA3EnableQdmaEvt(base_address, ch_num);

    /* Set trig word for ccnt*/
    EDMA3SetQdmaTrigWord(base_address, ch_num, EDMA3CC_PARAM_ENTRY_LINK_BCNTRLD);

    edmaParam.opt        = 0;
    edmaParam.srcAddr    = (uint32_t) srcBuff1;
    edmaParam.destAddr   = (uint32_t) dstBuff1;
    edmaParam.aCnt       = aCnt;
    edmaParam.bCnt       = bCnt;
    edmaParam.cCnt       = cCnt;
    edmaParam.srcBIdx    = aCnt;
    edmaParam.destBIdx   = aCnt;
    edmaParam.bCntReload = bCnt;
    edmaParam.srcCIdx    = aCnt;
    edmaParam.destCIdx   = aCnt;
    edmaParam.linkAddr   = 0xFFFFU;
    edmaParam.opt       |=
        (EDMA3_OPT_TCINTEN_MASK | EDMA3_OPT_ITCINTEN_MASK |
         ((tcc_num << EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));
    /* For Isolated qdma transfer and
     * last transfers in linked qdma transfer static field should be set */
    if ((bCnt * cCnt) == 1)
    {
        edmaParam.opt |= EDMA_TPCC_OPT_STATIC_MASK;
    }
    /*
     * Transfer is done in a sync mode
     * Number of triggers required are bCnt * cCnt
     */
    /* For the first transfer just write all Param set.
     * For subsequent transfer write only the cCnt value */
    transfer_complete = 0;
    EDMA3QdmaSetPaRAM(base_address, paramId, &edmaParam);
    while (transfer_complete != 1) ;

    for (i = 1; i < (bCnt * cCnt); i++)
    {
        if (i == ((bCnt * cCnt) - 1))
        {
            edmaParam.opt = EDMA3QdmaGetPaRAMEntry(base_address, paramId,
                                                   EDMA3CC_PARAM_ENTRY_OPT);
            edmaParam.opt |= EDMA_TPCC_OPT_STATIC_MASK;
            EDMA3QdmaSetPaRAMEntry(base_address, paramId,
                                   EDMA3CC_PARAM_ENTRY_OPT,
                                   edmaParam.opt);
        }
        transfer_complete = 0;
        EDMA3QdmaSetPaRAMEntry(base_address, paramId,
                               EDMA3CC_PARAM_ENTRY_LINK_BCNTRLD,
                               (bCnt << 16 | 0xFFFFU));
        while (transfer_complete != 1) ;
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

    EDMA3DisableQdmaEvt(base_address, ch_num);

    return error;
}

