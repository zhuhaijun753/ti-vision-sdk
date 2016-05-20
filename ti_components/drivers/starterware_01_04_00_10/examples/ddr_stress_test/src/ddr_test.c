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
 * dma_test.c
 */

#include "stdint.h"
#include <stdlib.h>
#include <common/stw_types.h>
#include "uartStdio.h"
#include "edma.h"
#include "sample.h"
#include "interrupt.h"
#include "hw_types.h"
#include "soc.h"
#include "hw_counter_32k.h"

extern signed char       _srcBuffm[BUFFER_SIZE];
signed char             *srcBuffm;

extern volatile uint32_t transfer_complete;
extern uint32_t          base_address;
uint32_t ddr_start_addr;

/*
 * Get DDR Size
 *
 */

void getDDRSize(uint32_t *dsize)
{
    UARTPuts("\nEnter the size of DDR memory in hex(without 0x): ", -1);
    *dsize = UARTGetHexNum();
}

/*
 * Get User input
 *
 */
void getUserInput(uint32_t *test_num, uint32_t *start_addr, uint32_t *rand_cnt)
{
    UARTPuts("\nHow many times should the test be repeated(enter a number):",
             -1);
    *test_num = UARTGetNum();

    UARTPuts(
        "\nEnter the start address of the memory to be tested in hex(without 0x):",
        -1);
    *start_addr = UARTGetHexNum();

    UARTPuts(
        "\nHow many times random mem test is to be repeated(enter a number):",
        -1);
    *rand_cnt = UARTGetNum();
}

/*
 * Get User input
 *
 */
void getUserInput2(uint32_t *dsize, uint32_t *test_num, uint32_t *start_addr,
                   uint8_t *pattern)
{
    UARTPuts("\nHow many times should the test be repeated(enter a number):",
             -1);
    *test_num = UARTGetNum();

    UARTPuts(
        "\nEnter the start address of the memory to be tested in hex(without 0x):",
        -1);
    *start_addr = UARTGetHexNum();

    UARTPuts(
        "\nEnter the size of the DDR memory to be tested in hex(without 0x): ",
        -1);
    *dsize = UARTGetHexNum();

    UARTPuts("\nEnter the pattern used to be tested in hex(without 0x):", -1);
    *pattern = UARTGetHexNum();
}

static uint32_t getSrcBufPhyAddr(uint32_t srcAddr)
{
#if (defined (BUILD_M4))
    srcAddr = srcAddr + 0x40000000;
#endif
    return srcAddr;
}

/*
 * DDR Test
 * Full memory read/write
 */
int32_t edma_mem_test1(uint32_t ddr_address, uint32_t ch_num, uint32_t tcc_num,
                       uint32_t evtq_num,
                       uint32_t aCnt, uint32_t bCnt,
                       uint32_t cCnt)
{
    signed char      *dst_addr;
    static uint32_t   blk_size = 0x1FFFFFFF;
    static int32_t    buf_size = BUFFER_SIZE;
    uint32_t          i, retVal = SUCCESS, count;

    dst_addr = (signed char *) ddr_address;
    srcBuffm = (signed char *) (_srcBuffm);
    EDMA3CCPaRAMEntry edmaParam;

    UARTPuts("\n********************************************************\n", -1);
    UARTPuts("Running DDR test case 1-- Full memory read/write ", -1);

    UARTPuts("\nSize of DDR is ", -1);
    UARTPutHexNum(blk_size);

    /*
     * Initialize the source address with a pattern
     * initialize dst address with zero/another pattern (optional)
     */

    for (count = 0U; count < (aCnt * bCnt * cCnt); count++)
    {
        srcBuffm[count] = (int) 0x55;
    }

    count = 0;

    while (blk_size != 0)
    {
        EDMA3RequestChannel(base_address, EDMA3_CHANNEL_TYPE_DMA, ch_num,
                            tcc_num,
                            evtq_num);

        edmaParam.opt     = 0;
        edmaParam.srcAddr = (uint32_t) srcBuffm;
        /* To change virtual address to physical*/
        edmaParam.srcAddr  = getSrcBufPhyAddr(edmaParam.srcAddr);
        edmaParam.destAddr = (uint32_t) (dst_addr);
        edmaParam.aCnt     = aCnt;
        edmaParam.bCnt     = bCnt;
        edmaParam.cCnt     = cCnt;
        edmaParam.srcBIdx  = 0;
        edmaParam.destBIdx = 0;
        edmaParam.srcCIdx  = 0;
        edmaParam.destCIdx = 0;
        edmaParam.linkAddr = 0xFFFFU;
        edmaParam.opt     |= (EDMA3_OPT_TCINTEN_MASK |
                              ((tcc_num <<
                                EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));

        EDMA3SetPaRAM(base_address, ch_num, &edmaParam);

        /*
         * Transfer is done in A-sync mode
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
            if (srcBuffm[i] != dst_addr[i])
            {
                retVal = FAIL;
                UARTPuts("\nError matching value at src and dst address\n", -1);
                UARTPuts("Value at src address ", -1);
                UARTPutHexNum((uint32_t) &srcBuffm[i]);
                UARTPuts(" is:", -1);
                UARTPutHexNum(srcBuffm[i]);
                UARTPuts("\nValue at dst address ", -1);
                UARTPutHexNum((uint32_t) &dst_addr[i]);
                UARTPuts(" is:", -1);
                UARTPutHexNum(dst_addr[i]);
                break;
            }
        }

        if (retVal == FAIL)
        {
            UARTPuts(" \nEDMA TEST failed at address ", -1);
            UARTPutHexNum((uint32_t) &dst_addr[i]);
            break;
        }

        dst_addr += buf_size;
        blk_size -= buf_size;
        count++;

        if (count == 0x1FFF)
        {
            count = 0;
            UARTPuts("\ndst address ", -1);
            UARTPutHexNum((uint32_t) &dst_addr[0]);
        }

        if ((blk_size < BUFFER_SIZE) && (blk_size % BUFFER_SIZE) != 0)
        {
            aCnt     = blk_size;
            buf_size = blk_size;
        }
    }

    return retVal;
}

/*
 * DDR Test
 * Random memory read/write
 */

int32_t edma_mem_test2(uint32_t ch_num, uint32_t tcc_num, uint32_t evtq_num,
                       uint32_t aCnt, uint32_t bCnt,
                       uint32_t cCnt)
{
    uint32_t          i, retVal = SUCCESS, count, flag = 0;
    signed char      *dst_addr;
    uint32_t          ddr_max_size = 0x1fffffff, randCnt;
    static int32_t    buf_size     = BUFFER_SIZE;
    uint32_t          test_num, randVal, tempCnt = 0;
#ifndef TI814X_FAMILY_BUILD
    uint32_t          seedVal;
#endif
    uint32_t          num, numBlocks, tempVal;
    uint32_t          ddr_end_addr, rnd_ddr_addr;

    EDMA3CCPaRAMEntry edmaParam;

    UARTPuts(
        "\n****************************************************************",
        -1);
    UARTPuts("\nRunning DDR test case 2 -- Random memory read/write\n ", -1);

    getUserInput(&test_num, &ddr_start_addr, &randCnt);

    dst_addr = (signed char *) ddr_start_addr;
    srcBuffm = (signed char *) (_srcBuffm);

    ddr_end_addr = (ddr_start_addr & 0xf0000000) + ddr_max_size;

    numBlocks = (ddr_max_size + 1) / buf_size;

    /*
     * Initialize the source address with a pattern
     *
     */
    for (count = 0U; count < (aCnt * bCnt * cCnt); count++)
    {
        srcBuffm[count] = (int) 0xAA;
    }

    for (num = 0; num < test_num; num++)
    {
        dst_addr = (signed char *) ddr_start_addr;

        while (randCnt)
        {
            EDMA3RequestChannel(base_address, EDMA3_CHANNEL_TYPE_DMA, ch_num,
                                tcc_num,
                                evtq_num);
            edmaParam.opt     = 0;
            edmaParam.srcAddr = (uint32_t) srcBuffm;
            /* To change virtual address to physical*/
            edmaParam.srcAddr  = getSrcBufPhyAddr(edmaParam.srcAddr);
            edmaParam.destAddr = (uint32_t) dst_addr;
            edmaParam.aCnt     = aCnt;
            edmaParam.bCnt     = bCnt;
            edmaParam.cCnt     = cCnt;
            edmaParam.srcBIdx  = 0;
            edmaParam.destBIdx = 0;
            edmaParam.srcCIdx  = 0;
            edmaParam.destCIdx = 0;
            edmaParam.linkAddr = 0xFFFFU;
            edmaParam.opt     |= (EDMA3_OPT_TCINTEN_MASK |
                                  ((tcc_num <<
                                    EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));
            EDMA3SetPaRAM(base_address, ch_num, &edmaParam);

            /*
             * Transfer is done in a sync mode
             * Number of triggers required are bCnt * cCnt
             */
            for (i = 0; i < (bCnt * cCnt); i++)
            {
                transfer_complete = 0;
                EDMA3EnableTransfer(base_address, ch_num,
                                    EDMA3_TRIG_MODE_MANUAL);
                while (transfer_complete != 1) ;
            }
            for (i = 0; i < (aCnt * bCnt * cCnt); i++)
            {
                if (srcBuffm[i] != dst_addr[i])
                {
                    retVal = FAIL;
                    UARTPuts("\nError matching value at src and dst address\n",
                             -1);
                    UARTPuts("Value at src address ", -1);
                    UARTPutHexNum((uint32_t) &srcBuffm[i]);
                    UARTPuts(" is:", -1);
                    UARTPutHexNum(srcBuffm[i]);
                    UARTPuts("\nValue at dst address ", -1);
                    UARTPutHexNum((uint32_t) &dst_addr[i]);
                    UARTPuts(" is:", -1);
                    UARTPutHexNum(dst_addr[i]);
                    break;
                }
            }
            if (retVal == FAIL)
            {
                UARTPuts(" \n DDR TEST failed at address: ", -1);
                UARTPutHexNum(dst_addr[i]);
                break;
            }
            tempCnt = 0;
            do
            {
                tempCnt++;
                if (tempCnt > 10)
                    break;
                flag = 1;
#ifndef TI814X_FAMILY_BUILD
                seedVal = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
                srand(seedVal);
#endif
                randVal      = rand() % numBlocks;
                tempVal      = buf_size * randVal;
                rnd_ddr_addr = ddr_start_addr + tempVal;
                if (((uint32_t) (rnd_ddr_addr) < ddr_end_addr) &&
                    ((uint32_t) (rnd_ddr_addr) > ddr_start_addr))
                {
                    dst_addr = (signed char *) rnd_ddr_addr;
                    flag     = 0;
                }
            } while (flag);
            UARTPuts("\n Random DDR address ", -1);
            UARTPutHexNum((uint32_t) rnd_ddr_addr);
            UARTPuts(" size :", -1);
            UARTPutHexNum(buf_size);
            randCnt--;
        }
        UARTPuts("\nTest count number ", -1);
        UARTPutHexNum(num);
    }

    return retVal;
}

/*
 * DDR Test
 * Sequential memory read/write
 */

int32_t edma_mem_test3(uint32_t ch_num, uint32_t tcc_num, uint32_t evtq_num,
                       uint32_t aCnt, uint32_t bCnt,
                       uint32_t cCnt)
{
    uint32_t          i, retVal = SUCCESS, count;
    signed char      *dst_addr;
    static uint32_t   blk_size = 0, bsize = 0;
    static int32_t    buf_size = BUFFER_SIZE;
    static uint32_t   test_num;
    uint8_t           pattern;

    uint32_t          num;

    EDMA3CCPaRAMEntry edmaParam;

    UARTPuts(
        "\n****************************************************************",
        -1);
    UARTPuts("\nRunning DDR test case 3 -- Sequential memory read/write\n ", -1);

    getUserInput2(&bsize, &test_num, &ddr_start_addr, &pattern);
    dst_addr = (signed char *) ddr_start_addr;
    srcBuffm = (signed char *) (_srcBuffm);

    /*
     * Initialize the source address with a pattern
     *
     */
    for (count = 0U; count < (aCnt * bCnt * cCnt); count++)
    {
        srcBuffm[count] = (int) pattern;
    }

    for (num = 0; num < test_num; num++)
    {
        dst_addr = (signed char *) ddr_start_addr;
        blk_size = bsize;

        while (blk_size != 0)
        {
            EDMA3RequestChannel(base_address, EDMA3_CHANNEL_TYPE_DMA, ch_num,
                                tcc_num,
                                evtq_num);
            edmaParam.opt     = 0;
            edmaParam.srcAddr = (uint32_t) srcBuffm;

            /* To change virtual address to physical*/
            edmaParam.srcAddr  = getSrcBufPhyAddr(edmaParam.srcAddr);
            edmaParam.destAddr = (uint32_t) dst_addr;
            edmaParam.aCnt     = aCnt;
            edmaParam.bCnt     = bCnt;
            edmaParam.cCnt     = cCnt;
            edmaParam.srcBIdx  = 0;
            edmaParam.destBIdx = 0;
            edmaParam.srcCIdx  = 0;
            edmaParam.destCIdx = 0;
            edmaParam.linkAddr = 0xFFFFU;
            edmaParam.opt     |= (EDMA3_OPT_TCINTEN_MASK |
                                  ((tcc_num <<
                                    EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));
            EDMA3SetPaRAM(base_address, ch_num, &edmaParam);

            /*
             * Transfer is done in a sync mode
             * Number of triggers required are bCnt * cCnt
             */
            for (i = 0; i < (bCnt * cCnt); i++)
            {
                transfer_complete = 0;
                EDMA3EnableTransfer(base_address, ch_num,
                                    EDMA3_TRIG_MODE_MANUAL);
                while (transfer_complete != 1) ;
            }

            for (i = 0; i < (aCnt * bCnt * cCnt); i++)
            {
                if (srcBuffm[i] != dst_addr[i])
                {
                    retVal = FAIL;
                    UARTPuts("\nError matching value at src and dst address\n",
                             -1);
                    UARTPuts("Value at src address ", -1);
                    UARTPutHexNum((uint32_t) &srcBuffm[i]);
                    UARTPuts(" is:", -1);
                    UARTPutHexNum(srcBuffm[i]);
                    UARTPuts("\nValue at dst address ", -1);
                    UARTPutHexNum((uint32_t) &dst_addr[i]);
                    UARTPuts(" is:", -1);
                    UARTPutHexNum(dst_addr[i]);
                    break;
                }
            }

            if (retVal == FAIL)
            {
                UARTPuts(" \nEDMA TEST failed at address: ", -1);
                UARTPutHexNum(dst_addr[i]);
                break;
            }

            dst_addr += buf_size;
            blk_size -= buf_size;

            if ((blk_size < BUFFER_SIZE) && (blk_size % BUFFER_SIZE) != 0)
            {
                buf_size = blk_size;
            }
        }

        UARTPuts("\nTest count number ", -1);
        UARTPutHexNum(num);
    }

    return retVal;
}

/*
 * DDR Test
 * Sequential increment pattern test
 */

int32_t edma_mem_test4(uint32_t ch_num, uint32_t tcc_num, uint32_t evtq_num,
                       uint32_t aCnt, uint32_t bCnt,
                       uint32_t cCnt)
{
    uint32_t          i, retVal = SUCCESS, count;
    signed char      *dst_addr;
    static uint32_t   blk_size = 0, bsize = 0;
    static int32_t    buf_size = BUFFER_SIZE;
    static uint32_t   test_num;
    uint8_t           pattern;

    uint32_t          num;

    EDMA3CCPaRAMEntry edmaParam;

    UARTPuts(
        "\n****************************************************************",
        -1);
    UARTPuts("\nRunning DDR test case 4 -- Sequential increment pattern \n ",
             -1);

    getUserInput2(&bsize, &test_num, &ddr_start_addr, &pattern);
    dst_addr = (signed char *) ddr_start_addr;
    srcBuffm = (signed char *) (_srcBuffm);

    for (num = 0; num < test_num; num++)
    {
        dst_addr = (signed char *) ddr_start_addr;
        blk_size = bsize;

        while (blk_size != 0)
        {
            /*
             * Initialize the source address with a Sequential increment pattern
             *
             */
            for (count = 0U; count < (aCnt * bCnt * cCnt); count++)
            {
                srcBuffm[count] = (int) pattern;
                pattern++;
            }

            EDMA3RequestChannel(base_address, EDMA3_CHANNEL_TYPE_DMA, ch_num,
                                tcc_num,
                                evtq_num);
            edmaParam.opt     = 0;
            edmaParam.srcAddr = (uint32_t) srcBuffm;
            /* To change virtual address to physical*/
            edmaParam.srcAddr  = getSrcBufPhyAddr(edmaParam.srcAddr);
            edmaParam.destAddr = (uint32_t) dst_addr;
            edmaParam.aCnt     = aCnt;
            edmaParam.bCnt     = bCnt;
            edmaParam.cCnt     = cCnt;
            edmaParam.srcBIdx  = 0;
            edmaParam.destBIdx = 0;
            edmaParam.srcCIdx  = 0;
            edmaParam.destCIdx = 0;
            edmaParam.linkAddr = 0xFFFFU;
            edmaParam.opt     |= (EDMA3_OPT_TCINTEN_MASK |
                                  ((tcc_num <<
                                    EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));
            EDMA3SetPaRAM(base_address, ch_num, &edmaParam);

            /*
             * Transfer is done in a sync mode
             * Number of triggers required are bCnt * cCnt
             */
            for (i = 0; i < (bCnt * cCnt); i++)
            {
                transfer_complete = 0;
                EDMA3EnableTransfer(base_address, ch_num,
                                    EDMA3_TRIG_MODE_MANUAL);
                while (transfer_complete != 1) ;
            }

            for (i = 0; i < (aCnt * bCnt * cCnt); i++)
            {
                if (srcBuffm[i] != dst_addr[i])
                {
                    retVal = FAIL;
                    UARTPuts("\nError matching value at src and dst address\n",
                             -1);
                    UARTPuts("Value at src address ", -1);
                    UARTPutHexNum((uint32_t) &srcBuffm[i]);
                    UARTPuts(" is:", -1);
                    UARTPutHexNum(srcBuffm[i]);
                    UARTPuts("\nValue at dst address ", -1);
                    UARTPutHexNum((uint32_t) &dst_addr[i]);
                    UARTPuts(" is:", -1);
                    UARTPutHexNum(dst_addr[i]);
                    break;
                }
            }

            if (retVal == FAIL)
            {
                UARTPuts(" \nEDMA TEST failed at address: ", -1);
                UARTPutHexNum(dst_addr[i]);
                break;
            }

            dst_addr += buf_size;
            blk_size -= buf_size;

            if ((blk_size < BUFFER_SIZE) && (blk_size % BUFFER_SIZE) != 0)
            {
                buf_size = blk_size;
            }
        }

        UARTPuts("\nTest count number ", -1);
        UARTPutHexNum(num);
    }

    return retVal;
}

