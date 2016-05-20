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
int32_t dma_chain_test(uint32_t ch_num, uint32_t tcc_num, uint32_t evtq_num,
                       uint32_t ch_num2, uint32_t tcc_num2, uint32_t evtq_num2,
                       uint32_t aCnt,
                       uint32_t bCnt,
                       uint32_t cCnt)
{
    int32_t           count;

    volatile uint32_t i, error = SUCCESS;
    EDMA3CCPaRAMEntry edmaParam;

    uint32_t          chain_param =
        (EDMA3_OPT_TCCHEN_MASK |
         EDMA3_OPT_ITCCHEN_MASK |
         EDMA3_OPT_TCINTEN_MASK |
         EDMA3_OPT_ITCINTEN_MASK);

    srcBuff1 = (signed char *) (_srcBuff1);
    dstBuff1 = (signed char *) (_dstBuff1);

    srcBuff2 = (signed char *) (_srcBuff2);
    dstBuff2 = (signed char *) (_dstBuff2);

    UARTPuts("\nDma Chain test", -1);

    /*
     * Initialize the source address with a pattern
     * Initialize source and destination buffers
     */

    for (count = 0U; count < (aCnt * bCnt * cCnt); count++)
    {
        srcBuff1[count] = (int) 0xAA;
        srcBuff2[count] = (int) 0xBB;

        dstBuff1[count] = 0;
        dstBuff2[count] = 0;
    }

    /*Set params for channel 1*/
    EDMA3RequestChannel(base_address, EDMA3_CHANNEL_TYPE_DMA, ch_num, tcc_num,
                        evtq_num);

    edmaParam.opt = 0;

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
    edmaParam.linkAddr   = 0xFFFFU;
    edmaParam.opt       |=
        (EDMA3_OPT_TCINTEN_MASK |
         ((tcc_num << EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));

    /*setting paRAM for channel ch_num with paRAM ID = ch_num */
    EDMA3SetPaRAM(base_address, ch_num, &edmaParam);

    /*Set params for channel 2*/
    EDMA3RequestChannel(base_address, EDMA3_CHANNEL_TYPE_DMA, ch_num2, tcc_num2,
                        evtq_num2);

    edmaParam.opt        = 0;
    edmaParam.srcAddr    = (uint32_t) srcBuff2;
    edmaParam.destAddr   = (uint32_t) dstBuff2;
    edmaParam.aCnt       = aCnt;
    edmaParam.bCnt       = bCnt;
    edmaParam.cCnt       = cCnt;
    edmaParam.srcBIdx    = aCnt;
    edmaParam.destBIdx   = aCnt;
    edmaParam.srcCIdx    = aCnt;
    edmaParam.destCIdx   = aCnt;
    edmaParam.bCntReload = bCnt;
    edmaParam.linkAddr   = 0xFFFFU;
    edmaParam.opt       |=
        (EDMA3_OPT_TCINTEN_MASK |
         ((tcc_num2 << EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));

    /*Enable transfer completion for channel 2*/

    edmaParam.opt |= EDMA_TPCC_OPT_TCINTEN_MASK | EDMA_TPCC_OPT_ITCINTEN_MASK;

    /*setting paRAM for channel ch_num2 with paRAM ID = ch_num2 */
    EDMA3SetPaRAM(base_address, ch_num2, &edmaParam);

    /*Set params for chain transfer. Chain two channels*/
    EDMA3ChainChannel(base_address, ch_num, ch_num2, chain_param);

    /**
     * Transfer is done in a sync mode
     * Number of triggers required are bCnt * cCnt
     */
    for (i = 0; i < (bCnt * cCnt); i++)
    {
        transfer_complete = 0;
        EDMA3EnableTransfer(base_address, ch_num, EDMA3_TRIG_MODE_MANUAL);
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

    for (i = 0; i < (aCnt * bCnt * cCnt); i++)
    {
        if (srcBuff2[i] != dstBuff2[i])
        {
            error = FAIL;
            UARTPuts("\nError matching value at src and dst address", -1);
            break;
        }
    }

    return error;
}

