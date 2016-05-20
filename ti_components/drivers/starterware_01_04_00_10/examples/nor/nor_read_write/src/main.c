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

#include "stdio.h"
#include "string.h"
#include "stdint.h"
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include <common/stw_utils.h>
#include "soc_defines.h"
#include "platform.h"
#include "device.h"
#include "nor.h"
#include "soc.h"
#include "uartStdio.h"
#include "gpmc.h"
#include "i2clib/lld_hsi2c.h"
#include "boards/stw_board.h"
#include "devices/stw_device.h"
#include "stwutils_app.h"
#include "debug.h"

#define BUF_SIZE (32 * 1024)
#define GPMC_CS0 0
#define FLASH_BLOCK_SIZE (128 * 1024)

#if !defined (BUILD_A15) && !defined (BUILD_GCC)
#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_srcBuffm, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
uint8_t       _srcBuffm[FLASH_BLOCK_SIZE];
#else
uint8_t __attribute__((section(".my_sect_ddr"))) _srcBuffm[FLASH_BLOCK_SIZE];
#endif

signed char  *srcBuffm;
unsigned int  NORStart = NOR_BASE;

static void NorTest(void);
static int32_t local_DEBUGprintString(const char *s);

/************************************************************
 * Local Function Deefinitions                              *
 ************************************************************/
static int32_t local_DEBUGprintString(const char *s)
{
#ifndef BUILD_A15
    printf(s);
#else
    UARTPuts(s, -1);
#endif
    return SUCCESS;
}

GPMC_Config_t GPMC_ConfigNorDefault = {
    /* SysConfig - ROM Code defaults */
    0x0,           /*0x0008,*/
    /* IRQEnable - ROM Code defaults */
    0x0000,
    /* TimeOutControl - ROM Code defaults */
    0xf01f0000,
    /* Config - ROM Code defaults */
    0x000a0000,
    {
        0x00001010,
        0x001e1e01,
        0x00090907,
        0xf071d0b,
        0x001c1f1f,
        0x8f070080,
        0x00000f48,
    },
};

int main(void)
{
    uint32_t           baseAddr = SOC_GPMC_CONF_REGS_BASE;
    stwAppInitParams_t stwAppInitParams;
    int32_t retVal;
    Nor_InitPrms_t     Nor_InitPrms;

    /* System init */
    stwAppInitParams.isI2cInitReq  = TRUE;
    stwAppInitParams.isUartInitReq = TRUE;
    retVal = StwUtils_appDefaultInit(stwAppInitParams);
    if (retVal != STW_SOK)
    {
        UARTPuts("\nSystem Init Failed ", -1);
    }

    PlatformGPMCSetPinMux();

    BOARDSelectDevice(DEVICE_ID_NORFLASH, DEVICE_NORFLASH_INST_ID_0);

    GPMC_Init(&GPMC_ConfigNorDefault, GPMC_CS0);

    /* FOLLOWING IS NOR CHIP-SELECT CONFIGURATION */

    /* Select the chip-select base address, chip addr needs to be given */
    GPMCBaseAddrSet(baseAddr, GPMC_CHIP_SELECT_0, 0x00000008);

    /* Select the chip-select mask address */
    GPMCMaskAddrSet(baseAddr, GPMC_CHIP_SELECT_0, GPMC_CS_SIZE_64MB);

    UARTPuts("\nNOR Flash Test App", -1);

    /* Initialize function pointer Default */
    NOR_InitParmsDefault(&Nor_InitPrms);

    Nor_InitPrms.norFlashInitPrintFxnPtr =
        (NOR_FlashInitPrintFxnPtr) (&local_DEBUGprintString);
    /* Initialize function pointer Default */
    NOR_Init(&Nor_InitPrms);

    /* Function to Test NOR Flash */
    NorTest();

    return 0;
}

static void NorTest(void)
{
    NOR_InfoHandle    hNorInfo;
    uint32_t          baseAddress = 0;
    uint32_t          blockSize, blockAddr;
    uint32_t          count, i, k;
    uint32_t          flash_size;
    volatile uint32_t dstOffsetAddr;
    uint32_t          offset_addr, buf_size;
    signed char      *dst_addr;
    volatile uint32_t norTest = 0;
    uint32_t          retVal  = SUCCESS;

    srcBuffm = (signed char *) (_srcBuffm);

    while (1) {
        UARTPuts(
            "\nEnter the testcase number\n1: Read Manufacturer ID and Device ID of NOR\n2: Erase, Write/Read and Verify 1 block of NOR flash\n3: Erase, Write/Read and Verify entire NOR flash\nAny other number to quit\n",
            -1);
        norTest = UARTGetNum();
        UARTPuts("\n", -1);
        if (norTest == 1)
        {
            UARTPuts(
                "Running Test Case 1: Read Manufacturer ID and Device ID of NOR\n",
                -1);
            /* Initialize NOR Flash */
            hNorInfo = NOR_open(NORStart, 2 /* 16 Bit */);
            if (hNorInfo == NULL)
            {
                UARTPuts("\tERROR: NOR Initialization failed.\r\n", -1);
                retVal = FAIL;
                break;
            }
            else
            {
                UARTPuts("\nTest Passed.\n", -1);
            }
        }
        else if (norTest == 2)
        {
            UARTPuts(
                "\nRunning Test Case 2:Erase, Write/Read and Verify 1 block of NOR flash\n",
                -1);
            hNorInfo = NOR_open(NORStart, 2 /* 16 Bit */);
            if (hNorInfo == NULL)
            {
                UARTPuts("\tERROR: NOR Initialization failed.\r\n", -1);
                retVal = FAIL;
                break;
            }
            /* Get NOR block size */
            NOR_getBlockInfo(hNorInfo, NORStart, &blockSize,
                             &blockAddr);

            /* Set base address to start putting data at */
            baseAddress = hNorInfo->flashBase;

            /*Erase the entire NOR Flash*/
            if (NOR_erase(hNorInfo, baseAddress, FLASH_BLOCK_SIZE) != SUCCESS)
            {
                UARTPuts("\tERROR: Erasing NOR failed.\r\n", -1);
                retVal = FAIL;
                break;
            }

            /*
             * Initialize the source address with a pattern
             * initialize dst address with zero/another pattern (optional)
             */

            for (count = 0U; count < (FLASH_BLOCK_SIZE); count++)
            {
                srcBuffm[count] = (int) 0x55;
            }
            offset_addr = baseAddress;

            dstOffsetAddr = offset_addr;
            dst_addr      = (signed char *) dstOffsetAddr;

            /* Write the data pattern to the flash */
            if (NOR_writeBytes(hNorInfo, dstOffsetAddr, FLASH_BLOCK_SIZE,
                               (uint32_t) srcBuffm) != SUCCESS)
            {
                UARTPuts("\tERROR: Writing NOR failed.\n", -1);
                retVal = FAIL;
                break;
            }

            for (i = 0; i < (FLASH_BLOCK_SIZE); i++)
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
                UARTPuts("\nError testing block : ", -1);
                UARTPuts("\nTest Failed.\n", -1);
                break;
            }
            else
            {
                UARTPuts("\nTest Passed.\n", -1);
            }
        }
        else if (norTest == 3)
        {
            UARTPuts(
                "\nRunning Test Case 3: Erase, Write/Read and Verify entire NOR flash",
                -1);
            hNorInfo = NOR_open(NORStart, 2 /* 16 Bit */);
            if (hNorInfo == NULL)
            {
                UARTPuts("\tERROR: NOR Initialization failed.\r\n", -1);
                retVal = FAIL;
                break;
            }
            /* Get NOR block size */
            NOR_getBlockInfo(hNorInfo, NORStart, &blockSize,
                             &blockAddr);

            UARTPuts("NOR Init Done\n", -1);

            /* Set base address to start putting data at */
            baseAddress = hNorInfo->flashBase;

            /*Erase the entire NOR Flash*/
            if (NOR_erase(hNorInfo, baseAddress,
                          hNorInfo->flashSize) != SUCCESS)
            {
                UARTPuts("\tERROR: Erasing NOR failed.\r\n", -1);
                retVal = FAIL;
                break;
            }

            /*
             * Initialize the source address with a pattern
             * initialize dst address with zero/another pattern (optional)
             */

            for (count = 0U; count < (FLASH_BLOCK_SIZE); count++)
            {
                srcBuffm[count] = (int) 0x55;
            }

            /* Write the data pattern to the flash */
            flash_size  = hNorInfo->flashSize;
            offset_addr = baseAddress;
            buf_size    = FLASH_BLOCK_SIZE;
            k           = 0;
            while (flash_size != 0)
            {
                dstOffsetAddr = offset_addr;
                dst_addr      = (signed char *) dstOffsetAddr;

                /* Write the data pattern to the flash */
                if (NOR_writeBytes(hNorInfo, dstOffsetAddr, FLASH_BLOCK_SIZE,
                                   (uint32_t) srcBuffm) != SUCCESS)
                {
                    UARTPuts("\tERROR: Writing NOR failed.\n", -1);
                    retVal = FAIL;
                    break;
                }

                for (i = 0; i < (FLASH_BLOCK_SIZE); i++)
                {
                    if (srcBuffm[i] != dst_addr[i])
                    {
                        retVal = FAIL;
                        UARTPuts(
                            "\nError matching value at src and dst address\n",
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
                    UARTPuts("\nError testing block num: ", -1);
                    UARTPutNum(k);
                    break;
                }
                offset_addr += buf_size;
                flash_size  -= buf_size;

                UARTPuts("Testing block no. ", -1);
                UARTPutNum(k++);
                UARTPuts(" Completed\n", -1);
            }
            if (retVal == FAIL)
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    if (retVal == FAIL)
    {
        UARTPuts("\nTest Failed Exitting.\n", -1);
    }
    else
    {
        UARTPuts("\nExiting the nor test\n", -1);
    }
}

