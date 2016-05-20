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
#include <stdlib.h>
#include "qspi.h"
#include "soc_defines.h"
#include "uartStdio.h"
#include "qspi_flash.h"
#include "edma.h"
#include "bl_rprc.h"
#include "platform.h"

#define BOOT_FROM_FLASH 0
#define _READ_MM_MODE_ 0
#define _WRITE_MM_MODE_ 0

#ifndef SOC_EDMA_TPCC_BASE /* Temporary HACK for Vayu M4 */
#if defined (BUILD_M4)
#define SOC_EDMA_TPCC_BASE      (0x63300000U)
#endif
#endif

void PlatformQSPISetPinMux();
int32_t clockFreqtest(void);

#if BOOT_FROM_FLASH
static void     (*appEntry)();
extern uint32_t (*fp_readData)(void *, void *, uint32_t);
extern void     (*fp_seek)(void *srcAddr, uint32_t location);
#endif

uint32_t        gEdma_ch_num   = 1;
uint32_t        edma_tcc_num  = 1;
uint32_t        edma_evtq_num = 0;
uint32_t        entryPoint_modena;

uint32_t        flash_size;
uint32_t        buf_size;

#define FLASH_BLOCK_SIZE (64 * 1024)
#define READ_LENGTH (16 * 1024)
#define FLASH_SIZE  (32 * 1024 * 1024)  /* 32MB */

#ifndef BUILD_A15
#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_dstBuff1, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
uint8_t         _dstBuff1[FLASH_BLOCK_SIZE];

#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_dstBuff2, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
uint8_t         _dstBuff2[256 * 1024];

#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_srcBuff1, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
uint8_t         _srcBuff1[FLASH_BLOCK_SIZE];

#else
uint8_t __attribute__((section(".my_sect_ddr"))) _dstBuff1[FLASH_BLOCK_SIZE];
uint8_t __attribute__((section(".my_sect_ddr"))) _dstBuff2[256 * 1024];
uint8_t __attribute__((section(".my_sect_ddr"))) _srcBuff1[FLASH_BLOCK_SIZE];
#endif

int main(void) {
    qspi_DeviceType_e DeviceType;
    volatile uint32_t dstAddr, srcOffsetAddr;
    volatile uint32_t srcAddr, dstOffsetAddr;
    volatile uint32_t length;
    uint32_t          device_Id;
    uint32_t          i, k;
    uint8_t          *patternOrg = (uint8_t *) (_srcBuff1);
    uint8_t          *patternAddr;
    uint8_t          *patternRead = (uint8_t *) (_dstBuff1);
    uint32_t         *srctest, *dsttest;
    uint32_t          offset_addr = 0x0;
    uint32_t          testCase, retVal = 0;
    uint32_t          transferLength = 0;

    PlatformUartConsoleSetPinMux();
    UARTStdioInit();
    UARTPuts("\nQSPI App", -1);
    while (1)
    {
        UARTPuts(
            "\nEnter Device type to use\
                  \n1 - Spansion 1 bit \n2 - Spansion 4 bit\
                  \n3 - Micron 1 bit   \n4 - Micron 4 bit\
                  \n5 - Winbond 1 bit  \n6 - Winbond 4 bit\
                  \n7 - ISSI 1 bit     \n8 - ISSI 4 bit\n$ > ",
            -1);
        testCase = UARTGetNum();
        if (testCase == 1)
        {
            DeviceType = DEVICE_TYPE_SPANSION_QSPI1;
            break;
        }
        else if (testCase == 2)
        {
            DeviceType = DEVICE_TYPE_SPANSION_QSPI4;
            break;
        }
        else if (testCase == 3)
        {
            DeviceType = DEVICE_TYPE_MICRON_QSPI1;
            break;
        }
        else if (testCase == 4)
        {
            DeviceType = DEVICE_TYPE_MICRON_QSPI4;
            break;
        }
        else if (testCase == 5)
        {
            DeviceType = DEVICE_TYPE_WINBOND_QSPI1;
            break;
        }
        else if (testCase == 6)
        {
            DeviceType = DEVICE_TYPE_WINBOND_QSPI4;
            break;
        }
        else if (testCase == 7)
        {
            DeviceType = DEVICE_TYPE_ISSI_QSPI1;
            break;
        }
        else if (testCase == 8)
        {
            DeviceType = DEVICE_TYPE_ISSI_QSPI4;
            break;
        }
        else
        {
            UARTPuts("\nInvalid Input Please try again\n", -1);
        }
    }

    /* Configure PADs. */
    PlatformQSPISetPinMux();

    QSPI_Initialize(DeviceType);
    /* Data read from the Flash in cfg port mode */
    QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
    QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,QSPI_MMR);
    device_Id = QSPI_GetDeviceId();

    UARTPuts("\nMID - ", -1);
    UARTPutHexNum(device_Id & 0xFF);
    UARTPuts("\nDID - ", -1);
    UARTPutHexNum((device_Id & 0xFF0000) >> 16);

    while (1)
    {
        UARTPuts(
            "\nEnter the testcase number\n1 for quick flash test\n2 for extended flash test\n3 for qspi edma test\n4 for clock frequency test\n$ > ",
            -1);
        testCase = UARTGetNum();
        if (testCase == 1)
        {
            /* Data read from the Flash in cfg port mode */
            QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
            QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,QSPI_MMR);
            /* Erase the first block */
            QSPI_WriteEnable();
            UARTPuts("\nErasing QSPI Flash Block", -1);
            QSPI_FlashBlockErase(0);

            UARTPuts("\nErase Complete", -1);

            UARTPuts("\nWriting test pattern to flash.. ", -1);
            length      = READ_LENGTH; /* in words */
            patternAddr = patternOrg;
            for (i = 0; i < (length * 4); i++)
            {
                *patternAddr++ = i + 8;
            }

            /* Write data from DDR location to flash at offset address  */
            srcAddr       = (uint32_t) patternOrg;
            dstOffsetAddr = offset_addr;
            while (length > 64) {
                /* Change to Memory mapped mode with given chip select */
                if (0)
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
                    /* 64 words -- 64*4= 256 bytes */
                }
                length        -= 64;
                dstOffsetAddr += 256;
                srcAddr       += 256;
            }
            if (length > 0)
            {
                /* Change to Memory mapped mode with given chip select */
                if (0)
                {
                    QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
                    QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,QSPI_CS0);
                    QSPI_WriteEnable();
                    QSPI_WriteSectors(dstOffsetAddr, srcAddr, length);
                }
                else
                {
                    QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
                    QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,QSPI_MMR);
                    QSPI_WriteEnable();
                    QSPI_WriteCfgMode(dstOffsetAddr, srcAddr, length);
                }
            }
            UARTPuts("\nWrite flash Completed", -1);

            UARTPuts("\nReading the flash data..\n", -1);

            /* Read From 0x10 words from offset address 0x100 Memory mapped
             *mode*/
            dstAddr       = (uint32_t) patternRead;
            srcOffsetAddr = offset_addr;
            length        = READ_LENGTH;

            /* Change to Memory mapped mode with given chip select */
            QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
            QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,QSPI_CS0);
            QSPI_ReadSectors((void *) dstAddr,
                             srcOffsetAddr,
                             length * 4);

            srctest = (uint32_t *) (_srcBuff1);
            dsttest = (uint32_t *) (_dstBuff1);
            for (i = 0; i < (length); i++)
            {
                uint32_t dataval = *dsttest;
                if (*srctest !=
                    (((dataval & 0xFF) << 24) | ((dataval & 0xFF00) << 8) |
                     ((dataval &
                       0xFF0000) >> 8) | ((dataval & 0xFF000000) >> 24)))
                {
                    UARTPuts("\n Data Read write error at flash location - ",
                             -1);
                    UARTPutHexNum((i * 4));
                    break;
                }
                srctest++; dsttest++;
            }
            if (i == length)
            {
                UARTPuts("\nData Read Write Test Passed.", -1);
            }
            /* switch to cfg port mode */
            QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
            QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,QSPI_MMR);
            /* Now erase first 4 KB sector using sub sector erase */
            QSPI_WriteEnable();
            QSPI_FlashSubSectorErase(0);
            /* Change to Memory mapped mode with given chip select */
            QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
            QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,QSPI_CS0);
            dstAddr       = (uint32_t) patternRead;
            srcOffsetAddr = 0x0U;
            QSPI_ReadSectors((void *) dstAddr,
                             srcOffsetAddr,
                             QSPIFLASH_SUBSECTORSIZE);
            /* Check if all bits in first 4 KB is set to 0xFF */
            dsttest = (uint32_t *) (_dstBuff1);
            for (i = 0; i < (QSPIFLASH_SUBSECTORSIZE / 4); i++)
            {
                if (*dsttest != 0xFFFFFFFF)
                {
                    UARTPuts("\nSub sector erase failed ", -1);
                    break;
                }
                dsttest++;
            }
            if (i == (QSPIFLASH_SUBSECTORSIZE / 4))
            {
                UARTPuts("\nSub sector erase on first 4 KB sector successful ",
                         -1);
            }

            UARTPuts("\nQuick Flash Test Complete.\n", -1);
        } /* end test case 1*/
        else if (testCase == 2)
        {
            /* Data read from the Flash in cfg port mode */
            QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
            QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,QSPI_MMR);

            /* Erase the entire flash */
            QSPI_WriteEnable();
            UARTPuts("\nErasing entire QSPI Flash..This takes 50-60 seconds",
                     -1);
            QSPI_FlashFullErase();

            UARTPuts("\nErase Completed", -1);

            /* If 128Mbit size of flash is 16MB and if 512Mbit size of flash is
             * 32MB
             **/
            length      = READ_LENGTH; /* in words */
            patternAddr = patternOrg;
            for (i = 0; i < (length * 4); i++)
            {
                *patternAddr++ = i + 8;
            }

            flash_size = FLASH_SIZE;
            buf_size   = FLASH_BLOCK_SIZE;
            k          = 0;
            while (flash_size != 0)
            {
                /* Write data from DDR location to flash at offset address  */
                srcAddr       = (uint32_t) patternOrg;
                dstOffsetAddr = offset_addr;
                length        = READ_LENGTH;
                while (length > 64) {
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
                        /* 64 words -- 64*4= 256 bytes */
                    }
                    length        -= 64;
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
                        QSPI_WriteSectors(dstOffsetAddr, srcAddr, length);
                    }
                    else
                    {
                        QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                                          QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
                        QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,QSPI_MMR);
                        QSPI_WriteEnable();
                        QSPI_WriteCfgMode(dstOffsetAddr, srcAddr, length);
                    }
                }

                /* Read From 0x10 words from offset address 0x100 Memory mapped
                 *mode*/
                dstAddr       = (uint32_t) patternRead;
                srcOffsetAddr = offset_addr;
                length        = READ_LENGTH;

                /* Change to Memory mapped mode with given chip select */
                QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                                          QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
                QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,QSPI_CS0);
                QSPI_ReadSectors((void *) dstAddr,
                                 srcOffsetAddr,
                                 length * 4);

                srctest = (uint32_t *) (_srcBuff1);
                dsttest = (uint32_t *) (_dstBuff1);
                for (i = 0; i < (length); i++)
                {
                    uint32_t dataval = *dsttest;
                    if (*srctest !=
                        (((dataval &
                           0xFF) <<
                          24) |
                         ((dataval &
                           0xFF00) <<
                          8) |
                         ((dataval &
                           0xFF0000) >> 8) | ((dataval & 0xFF000000) >> 24)))
                    {
                        UARTPuts("\nData Read write error at flash location - ",
                                 -1);
                        UARTPutHexNum((i * 4) + offset_addr);
                        retVal = 1;
                        break;
                    }
                    srctest++; dsttest++;
                }
                if (retVal == 1)
                {
                    UARTPuts("\nError testing block num: ", -1);
                    UARTPutNum(k);
                    break;
                }
                if ((k % 20U) == 0)
                {
                    /* Print Success Msg only once in 20 times not to clutter
                     * uart console, still letting user know test is in progress
                     **/
                    UARTPuts("\nTesting Completed till block no.", -1);
                    UARTPutNum(k);
                }
                k++;
                offset_addr += buf_size;
                flash_size  -= buf_size;
            }

            UARTPuts("\nEntire Flash Test Complete\n", -1);
            offset_addr = 0x0;
        }
        else if (testCase == 3)
        {
            QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                                          QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
            QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,QSPI_CS0);
            UARTPuts("\nQSPI read using EDMA", -1);
            srcOffsetAddr  = 0;
            srctest        = (uint32_t *) (SOC_QSPI_ADDRSP1_BASE);
            srctest       += srcOffsetAddr;
            dstAddr        = (uint32_t) (_dstBuff2);
            transferLength = ((64 * 1024 * 3) + 1234);
            EDMAsetRegion(1);
            EDMA3Init(SOC_EDMA_TPCC_BASE, 0);
            EDMA3RequestChannel(SOC_EDMA_TPCC_BASE, EDMA3_CHANNEL_TYPE_DMA,
                                gEdma_ch_num,
                                edma_tcc_num,
                                edma_evtq_num);
            QSPI_ReadSectors_edma((void *) dstAddr, srcOffsetAddr,
                                  transferLength,
                                  gEdma_ch_num);

            dsttest = (uint32_t *) (_dstBuff2);
            for (i = 0; i < (transferLength / 4); i++)
            {
                uint32_t dataval = *dsttest;
                if (*srctest != dataval)
                {
                    UARTPuts("\n Data Read write error at flash location - ",
                             -1);
                    UARTPutHexNum((i * 4));
                    break;
                }
                srctest++; dsttest++;
            }
            if (i == (transferLength / 4))
            {
                UARTPuts("\nData Read Write Test Passed.\n", -1);
            }
        }
        else if (testCase == 4)
        {
            UARTPuts("\nConfigure Flash to different Clock speeds and read", -1);
            clockFreqtest();
        }
        else
        {
            UARTPuts("\nQuick Flash Test Complete.", -1);
            break;
        }
    }

#if BOOT_FROM_FLASH
    dstAddr       = 0x80000000;
    srcOffsetAddr = 0x0;
    length        = 0x31D7;

    /* Change to Memory mapped mode with given chip select */
    QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
    QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,QSPI_CS0);
    QSPI_ReadSectors_edma((void *) dstAddr, srcOffsetAddr, length,
                          gEdma_ch_num);

    appEntry = (void (*)(void)) 0x800000D0;
    (*appEntry)();

    /* Read RPRC file from QSPI flash and run the image */
    QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                                          QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
    QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,QSPI_CS0);
    fp_readData   = QSPI_ReadSectors;
    fp_seek       = QSPI_seek;
    srcOffsetAddr = OFFSET_SI;
    MulticoreImageParse((void *) &srcOffsetAddr, OFFSET_SI);
    appEntry = (void (*)(void))entryPoint_modena;
    if (appEntry)
    {
        UARTPuts("Jumping to cortex-A8 Application...\r\n\n", -1);
        (*appEntry)();
    }
#endif
    return 0;
}
