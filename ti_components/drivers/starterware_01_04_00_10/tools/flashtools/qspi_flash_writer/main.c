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
#include "stdio.h"
#include "qspi.h"
#include "qspi_flash.h"
#include "wd_timer.h"
#include "soc.h"
#include "soc_defines.h"
#include "platform.h"

int32_t qspiwriter(void);
#define READ_CHUNK      (16U * 1024U)
#define QSPIFLASH_SIZE  (32U * 1024U * 1024U)
#define APP_SIZE_MAX                (uint32_t)(32U * 1024U * 1024U)
#define APP_READ_BUF_SIZE_MAX       (uint32_t)(0x1000000)

#ifndef FILE_SEEK_SET
#define FILE_SEEK_SET    0   /* set file offset to offset */
#endif
#ifndef FILE_SEEK_CUR
#define FILE_SEEK_CUR    1   /* set file offset to current plus offset */
#endif
#ifndef FILE_SEEK_END
#define FILE_SEEK_END    2   /* set file offset to EOF plus offset */
#endif

static uint32_t gAppReadBuff[(APP_SIZE_MAX  / 4U)];
static uint32_t gAppVerifydBuff[(APP_READ_BUF_SIZE_MAX / 4U)];

int main(void) {
    qspi_DeviceType_e DeviceType = DEVICE_TYPE_CUSTOM;
    volatile uint32_t dstAddr, srcOffsetAddr;
    volatile uint32_t srcAddr, dstOffsetAddr;
    volatile uint32_t length = 10U;
    uint32_t          device_Id, usrInputFlashType;

    printf("\nQSPI Flash writer application");

    PlatformUnlockMMR();

#ifdef TDA2XX_FAMILY_BUILD
    /*Disable the WDTIMER*/
    WDTIMERDisable(SOC_WD_TIMER2_BASE);
#endif
    while (1)
    {
        printf(
            "\nEnter Device type to use\
                  \n1 - Spansion 1 bit \n2 - Spansion 4 bit\
                  \n3 - Micron 1 bit   \n4 - Micron 4 bit\
                  \n5 - Winbond 1 bit  \n6 - Winbond 4 bit\
                  \n7 - ISSI 1 bit     \n8 - ISSI 4 bit\n$ > ");
        scanf("%u", &usrInputFlashType);
        if (usrInputFlashType == 1U)
        {
            DeviceType = DEVICE_TYPE_SPANSION_QSPI1;
        }
        else if (usrInputFlashType == 2U)
        {
            DeviceType = DEVICE_TYPE_SPANSION_QSPI4;
        }
        else if (usrInputFlashType == 3U)
        {
            DeviceType = DEVICE_TYPE_MICRON_QSPI1;
        }
        else if (usrInputFlashType == 4U)
        {
            DeviceType = DEVICE_TYPE_MICRON_QSPI4;
        }
        else if (usrInputFlashType == 5U)
        {
            DeviceType = DEVICE_TYPE_WINBOND_QSPI1;
        }
        else if (usrInputFlashType == 6U)
        {
            DeviceType = DEVICE_TYPE_WINBOND_QSPI4;
        }
        else if (usrInputFlashType == 7U)
        {
            DeviceType = DEVICE_TYPE_ISSI_QSPI1;
        }
        else if (usrInputFlashType == 8U)
        {
            DeviceType = DEVICE_TYPE_ISSI_QSPI4;
        }
        else
        {
            printf("\nInvalid Input Please try again\n");
        }

        if (DeviceType != DEVICE_TYPE_CUSTOM)
        {
            break;
        }
    }
    /* Configure PADs. */
    PlatformQSPISetPinMux();

    QSPI_Initialize(DeviceType);

    device_Id = QSPI_GetDeviceId();

    printf("\nMID - ");
    printf("%x", (device_Id & 0xFFU));
    printf("\nDID - ");
    printf("%x", (device_Id & 0xFF0000U) >> 16);

    qspiwriter();
    return 0;
}

int32_t qspiwriter(void)
{
    char      fileName[512];
    FILE     *fPtr;
    uint32_t  original_offset, original_fileSize;
    uint32_t  offset, fileSize, numBytesRead, totalBytesRead, input;
    uint32_t  eraseWhole;
    uint8_t  *tmp, *srcAddr;
    uint32_t *dstAddr;
    uint32_t *srctest, *dsttest;
    uint32_t  blkno;
    uint32_t  eraseSize;
    int32_t   option = 1;
    int32_t   retVal = 0;
    uint32_t  i;
    uint32_t readBlkOffset, readBlkSize, numBlks, lastBlkSize = 0U;
    uint32_t blkCnt, currentBlkSize, loopBreakFlag = 1U;

    printf("\nEnter 0 for Erase-Only (without flashing any image)"
           "\nNote : File size should be less than %d Bytes."
           "\nEnter the file path to flash: ", APP_SIZE_MAX);
    scanf("%511s", fileName);

    if ((fileName[0] == (char) '0') && (fileName[1] == 0x0))
    {
        /* Set option variable to '0' to erase without flashing */
        option = 0;
    }

    /* Read the offset from user */
    printf("Enter the Offset in bytes (HEX): ");
    scanf("%x", &offset);
    /* store offset for re-use later in verification */
    original_offset = offset;

    printf("Erase Options:\n---------------\n");
    printf("    0 -> Erase Only Required Region\n");
    printf("    1 -> Erase Whole Flash\n");
    printf("    2 -> Skip Erase \n");
    printf("Enter Erase Option: \n");
    scanf("%u", &eraseWhole);

    if (option != 0)
    {
        fPtr = fopen(fileName, "rb");
        if (fPtr == NULL)
        {
            printf("\tERROR: File ");
            printf("%s", fileName);
            printf(" open failed.\r\n");
            retVal = -1;
        }

        if (retVal == 0)
        {
            /* Read file size */
            fseek(fPtr, 0, FILE_SEEK_END);
            fileSize = (uint32_t) ftell(fPtr);
            if (fileSize == 0U)
            {
                printf("\tERROR: File read failed.. Closing program.\r\n");
                fclose(fPtr);
                retVal = -1;
            }
            /* store filesize for re-use later in verification */
            original_fileSize = fileSize;
        }

        if (retVal == 0)
        {
            fseek(fPtr, 0, FILE_SEEK_SET);

            printf("Load Options:\n-------------\n");
            printf("    0 -> fread using code (RTS Library)\n");
            printf("    1 -> load raw using CCS (Scripting console)\n");
            printf("Enter Load Option: \n");
            scanf("%u", &input);
            srcAddr = tmp = (uint8_t *) (gAppReadBuff);

            if (APP_SIZE_MAX >= fileSize)
            {
                if (0U == input)
                {
                    printf("Reading %u bytes from file...\r\n", fileSize);
                    totalBytesRead = 0U;
                    while (1)
                    {
                        numBytesRead =
                            fread((void *) tmp, (size_t) 1, READ_CHUNK,
                                  fPtr);
                        tmp += numBytesRead;
                        totalBytesRead += numBytesRead;
                        if (numBytesRead < READ_CHUNK)
                        {
                            break;
                        }
                        printf("Read %d bytes [%d%%] from file...\r\n",
                               totalBytesRead, ((totalBytesRead * 100U) / fileSize));
                    }
                    if (fileSize != totalBytesRead)
                    {
                        printf("\tWARNING: File Size mismatch.\r\n");
                    }
                    printf("Read %d bytes [%d%%] from file. Done!!\r\n",
                           totalBytesRead, ((totalBytesRead * 100U) / fileSize));
                }
                else
                {
                    printf("Use below command in CCS scripting console...\r\n");
                    printf("loadRaw(0x%.8x, 0, \"%s\", 32, false);\n", srcAddr,
                           fileName);
                    printf("Kindly use '/' (forward slash) in the file path\r\n");
                    printf(
                        "Enter any alpha-numeric key once loadraw is complete...\n");
                    scanf("%u", &input);
                }
            }
            else
            {
                printf("Given file can not be read into memory since it's size exceeds the allowed memory limit...\r\n");
                retVal = -1;
            }
            fclose(fPtr);

            blkno = offset / QSPIFLASH_BLOCKSIZE;
        }
    }

    if (retVal == 0)
    {
        QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);

        QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,QSPI_MMR);

        /* Erase the flash as required */
        if (eraseWhole == 1U)
        {
            printf("\n QSPI whole chip erase in progress\n");
            QSPI_WriteEnable();
            QSPI_FlashFullErase();
        }
        else if (eraseWhole == 0U)
        {
            if (option == 0)
            {
                printf("\nEnter number of bytes to erase (HEX): ");
                scanf("%x", &fileSize);
            }

            if ((fileSize > 0) && (fileSize < QSPIFLASH_SIZE))
            {
                printf("\n QSPI Erase started\n");
                blkno     = offset / QSPIFLASH_BLOCKSIZE;
                eraseSize = fileSize;
                while (eraseSize > 0U)
                {
                    QSPI_WriteEnable();
                    QSPI_FlashBlockErase(blkno);
                    blkno++;

                    if (eraseSize > QSPIFLASH_BLOCKSIZE)
                    {
                        eraseSize -= QSPIFLASH_BLOCKSIZE;
                    }
                    else
                    {
                        break;
                    }
                }
                printf("\n QSPI Erase completed\n");
            }
            else
            {
                printf(
                    "\n Number of bytes entered is invalid or greater than QSPIFLASH_SIZE(32MB) \n");
                retVal = -1;
            }
        }
        else
        {
            /* Nothing to be done here */
        }
    }

    if ((retVal == 0) && (option != 0))
    {
        printf("\n QSPI file write started \n");
        while (fileSize >= 256U) {
            /* Change to Memory mapped mode with given chip select */
            if (0)
            {
                QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);

                QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,QSPI_MMR);
                QSPI_WriteEnable();
                QSPI_WriteSectors(offset, (uint32_t) srcAddr, 64U);
            }
            else
            {
                QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
                QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,
                           QSPI_MMR);
                QSPI_WriteEnable();
                QSPI_WriteCfgMode(offset, (uint32_t) srcAddr, 64U);
            }
            fileSize -= 256U;
            offset   += 256U;
            srcAddr  += 256U;
        }
        if (fileSize > 0U)
        {
            /* Change to Memory mapped mode with given chip select */
            if (0)
            {
                QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
                QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,QSPI_MMR);
                QSPI_WriteEnable();
                QSPI_WriteSectors(offset, (uint32_t) srcAddr, fileSize);
            }
            else
            {
                QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
                QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,QSPI_MMR);
                QSPI_WriteEnable();
                QSPI_WriteCfgMode(offset, (uint32_t) srcAddr,
                                  (fileSize / 4U) + 1U);
            }
        }

        /* Change to Memory mapped mode with given chip select */
        QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);

        QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,QSPI_MMR);

        /* Skip the verification on tda3xx 12X12 package as DDR is only 64 MB
         * Current implimentation has hardcoding which goes beyond 64 MB.
         * TODO: Change implementation to read smaller chunk from file write to
         *       Flash and verify. May be one write block size */

         /* Code to do read-back & verify */
        dstAddr = (uint32_t *) (gAppVerifydBuff);

        /* Read block size for data verification- this is due to
         * limited memory on tda3xx 12X12 package */
        readBlkSize = APP_READ_BUF_SIZE_MAX;
        readBlkOffset = original_offset;
        numBlks = original_fileSize / readBlkSize;
        if(original_fileSize > (numBlks * readBlkSize))
        {
            lastBlkSize = original_fileSize - (numBlks * readBlkSize);
            numBlks++;
        }

        /* Change to Memory mapped mode with given chip select */
        QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);

        QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,QSPI_CS0);

        srctest = (uint32_t *) (gAppReadBuff);     /* same as hardcoded source
                                                   * address
                                                   *above */
        for(blkCnt = 0 ; blkCnt < numBlks ; blkCnt++)
        {
            if(1U != loopBreakFlag)
            {
                break;
            }
            dsttest = dstAddr;
            if(blkCnt < (numBlks - 1U))
            {
                currentBlkSize = readBlkSize;
            }
            else
            {
                currentBlkSize = lastBlkSize;
            }
            QSPI_ReadSectors((void *) dstAddr, readBlkOffset, currentBlkSize);
            readBlkOffset += currentBlkSize;
            for (i = 0; i < (currentBlkSize / 4U); i++)
            {
                uint32_t dataval = *dsttest;
                if (*srctest !=
                    (((dataval & 0xFFU) << 24) | ((dataval & 0xFF00U) << 8) |
                     ((dataval &
                       0xFF0000U) >> 8) | ((dataval & 0xFF000000U) >> 24)))
                {
                    printf(
                        "\n Data Read write error at flash location - 0x%x\n",
                        (((readBlkOffset - currentBlkSize) + (i * 4U))
                        - original_offset));
                    loopBreakFlag = 0U;
                    break;
                }
                srctest++; dsttest++;
            }
        }
    }

    if(retVal == 0)
    {
        printf(
        "\n ************QSPI flash completed sucessfully************** \n");
    }
    else
    {
        printf(
        "\n ************QSPI flash Failed************** \n");
    }

    {
        volatile uint8_t spin = 1U;
        while (spin)
        {
            /* Busy Loop*/
        }
    }

    return retVal;
}

