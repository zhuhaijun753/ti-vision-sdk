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
 * clockFreq_test.c
 */
#include "stdint.h"
#include "qspi.h"
#include "uartStdio.h"
#include "qspi_flash.h"
#include "hw_qspi.h"
#include "soc.h"

#define FLASH_BLOCK_SIZE (64 * 1024)
extern uint8_t _dstBuff1[];
extern uint8_t _srcBuff1[];
void writeFlash(uint32_t srcAddr, uint32_t dstOffsetAddr, uint32_t length);

#define _READ_MM_MODE_ 0
#define _WRITE_MM_MODE_ 0
void changeClockFreq(uint32_t index)
{
    HAL_QSPI_MemMapSetup_reg memSetup = {0};
    if (index == 0)
    {
        /* Memory mapped read: 48MHz, Fast read 0B */
        UARTPuts("\nClock freq : 48MHz Fast Read", -1);
        QSPI_SelClockFrequency(QSPI_SCLK_FREQ_48MHz);
        QSPISetClockControl(SOC_QSPI_ADDRSP0_BASE, QSPI_SCLK_FREQ_48MHz);
        memSetup.regFields.readCmd     = QSPI_CMD_FAST_READ;
        memSetup.regFields.numAddBytes =
            QSPI_SPI_SETUP0_REG_NUM_A_BYTES_FOUR_BYTES;
        memSetup.regFields.numDummyBytes =
            QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_8_BITS;
        memSetup.regFields.readType =
            QSPI_SPI_SETUP0_REG_READ_TYPE_NORMAL_READ_TYPE;
        memSetup.regFields.writeCmd     = QSPI_CMD_WRITE;
        memSetup.regFields.numDummyBits = 0;
        QSPISetMemoryMapSetup(SOC_QSPI_ADDRSP0_BASE, memSetup.reg, 0);
        return;
    }
    else if (index == 1)
    {
        /* Memory mapped read: 96MHz, Fast read 0B */
        UARTPuts("\nClock freq : 64MHz Fast Read", -1);
        QSPI_SelClockFrequency(QSPI_SCLK_FREQ_64MHz);
        QSPISetClockControl(SOC_QSPI_ADDRSP0_BASE, QSPI_SCLK_FREQ_64MHz);
        memSetup.reg = 0;
        memSetup.regFields.readCmd     = QSPI_CMD_FAST_READ;
        memSetup.regFields.numAddBytes =
            QSPI_SPI_SETUP0_REG_NUM_A_BYTES_FOUR_BYTES;
        memSetup.regFields.numDummyBytes =
            QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_8_BITS;
        memSetup.regFields.readType =
            QSPI_SPI_SETUP0_REG_READ_TYPE_NORMAL_READ;
        memSetup.regFields.writeCmd     = QSPI_CMD_WRITE;
        memSetup.regFields.numDummyBits = 0;
        QSPISetMemoryMapSetup(SOC_QSPI_ADDRSP0_BASE, memSetup.reg, 0);
        return;
    }
    else if (index == 2)
    {
        /* Memory mapped read: 96MHz, Dual read 3B */
        QSPI_SelClockFrequency(QSPI_SCLK_FREQ_64MHz);
        QSPISetClockControl(SOC_QSPI_ADDRSP0_BASE, QSPI_SCLK_FREQ_64MHz);
        UARTPuts("\nClock freq : 64MHz Dual Read", -1);
        memSetup.reg = 0;
        memSetup.regFields.readCmd     = QSPI_CMD_FAST_DREAD;
        memSetup.regFields.numAddBytes =
            QSPI_SPI_SETUP0_REG_NUM_A_BYTES_FOUR_BYTES;
        memSetup.regFields.numDummyBytes =
            QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_8_BITS;
        memSetup.regFields.readType =
            QSPI_SPI_SETUP0_REG_READ_TYPE_DUAL_READ;
        memSetup.regFields.writeCmd     = QSPI_CMD_WRITE;
        memSetup.regFields.numDummyBits = 0;
        QSPISetMemoryMapSetup(SOC_QSPI_ADDRSP0_BASE, memSetup.reg, 0);
        return;
    }
    else if (index == 3)
    {
        /* Memory mapped read: 96MHz, Quad read 6B */
        QSPI_SelClockFrequency(QSPI_SCLK_FREQ_64MHz);
        QSPISetClockControl(SOC_QSPI_ADDRSP0_BASE, QSPI_SCLK_FREQ_64MHz);
        UARTPuts("\nClock freq : 64MHz Quad Read", -1);
        memSetup.reg = 0;
        memSetup.regFields.readCmd     = QSPI_CMD_FAST_QREAD;
        memSetup.regFields.numAddBytes =
            QSPI_SPI_SETUP0_REG_NUM_A_BYTES_FOUR_BYTES;
        memSetup.regFields.numDummyBytes =
            QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_8_BITS;
        memSetup.regFields.readType =
            QSPI_SPI_SETUP0_REG_READ_TYPE_QUAD_READ;
        memSetup.regFields.writeCmd     = QSPI_CMD_WRITE;
        memSetup.regFields.numDummyBits = 0;
        QSPISetMemoryMapSetup(SOC_QSPI_ADDRSP0_BASE, memSetup.reg, 0);
        QSPI_QuadEnable();
        return;
    }
}

int32_t clockFreqtest(void) {
    volatile uint32_t dstAddr, srcOffsetAddr;
    volatile uint32_t length;
    uint32_t          i;
    uint8_t          *PatternAddr = (uint8_t *) (_srcBuff1);
    uint8_t          *PatternOrg;
    uint8_t          *PatternRead = (uint8_t *) (_dstBuff1);
    uint32_t         *srctest, *dsttest;
    uint32_t          offset_addr = 0x0;
    uint32_t          index, max_index = 4;
    PatternOrg = PatternAddr;
    for (index = 0; index < max_index; index++)
    {
        /* Change the Clock settings */
        changeClockFreq(index);

        /* Data read from the Flash in cfg port mode */
        QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
                      
        QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,QSPI_MMR);
        /* Erase the first block */
        QSPI_WriteEnable();
        QSPI_FlashBlockErase(0);
        UARTPuts("\nErase First block Completed", -1);
        PatternAddr = PatternOrg;
        length      = 2048;
        for (i = 0; i < length; i++)
        {
            *PatternAddr++ = i + index;
        }

        writeFlash((uint32_t) PatternOrg, offset_addr, length);

        /* Change to Memory mapped mode with given chip select */
        dstAddr       = (uint32_t) PatternRead;
        srcOffsetAddr = offset_addr;
#if _READ_MM_MODE_
        QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
                      
        QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,QSPI_CS0);
        QSPI_ReadSectors((void *) dstAddr, (void *) &srcOffsetAddr, length);
#else
        QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
                      
        QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,QSPI_MMR);
        QSPI_ReadCfgMode(dstAddr, srcOffsetAddr, length / 4);
#endif
        QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
                      
        QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,QSPI_CS0);
        srctest = (uint32_t *) (_srcBuff1);
        dsttest = (uint32_t *) (_dstBuff1);
        for (i = 0; i < (length / 4); i++)
        {
            uint32_t dataval = *dsttest;
#if _READ_MM_MODE_
            /* For Memory mapped mode read value will be in Big Endian Mode
             * So Convert to Little Endian Mode */
            dataval = ((dataval & 0xFF) << 24) |
                      ((dataval & 0xFF00) << 8) |
                      ((dataval & 0xFF0000) >> 8) |
                      ((dataval & 0xFF000000) >> 24));
#endif
            if (*srctest != dataval)
            {
                UARTPuts("\nData Read write error at location - ", -1);
                UARTPutHexNum(i * 4);
                break;
            }
            srctest++; dsttest++;
        }
        if (i == (length / 4))
        {
            UARTPuts("\nData Read write passed", -1);
        }
    }
    UARTPuts("\n", -1);
    return 0;
}

void writeFlash(uint32_t srcAddr, uint32_t dstOffsetAddr, uint32_t length)
{
    while (length >= 256) {
        /* Change to Memory mapped mode with given chip select */
        if (_WRITE_MM_MODE_)
        {
            QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
                      
            QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,QSPI_CS0);
            QSPI_WriteEnable();
            QSPI_WriteSectors(dstOffsetAddr, srcAddr, 64);
        }
        else
        {
            QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
                      
            QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,QSPI_MMR);
            QSPI_WriteEnable();
            QSPI_WriteCfgMode(dstOffsetAddr, srcAddr, 64);
        }
        length        -= 256;
        dstOffsetAddr += 256;
        srcAddr       += 256;
    }
    if (length > 0)
    {
        /* Change to Memory mapped mode with given chip select */
        if (_WRITE_MM_MODE_)
        {
            QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
                      
            QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,QSPI_CS0);
            QSPI_WriteEnable();
            QSPI_WriteSectors(dstOffsetAddr, srcAddr, ((length / 4) + 1));
        }
        else
        {
            QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
                      
            QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,QSPI_MMR);
            QSPI_WriteEnable();
            QSPI_WriteCfgMode(dstOffsetAddr, srcAddr, ((length / 4) + 1));
        }
    }
    UARTPuts("\nWrite to flash completed", -1);
}

