/**
 *  \file     sbl_utils_common.c
 *
 *  \brief    This file contains the SBL Utility layer common across platforms.
 *
 *  \copyright Copyright (C) 2015 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

/* ======================================================================
 *   Copyright (C) 2015 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include "hw_types.h"
#include "common/stw_types.h"
#include "soc_defines.h"
#include "platform.h"
#include "hw_counter_32k.h"
#include "crc.h"
#include "sbl_lib/sbl_lib.h"
#include "sbl_utils/sbl_utils_common.h"
#include "qspi_flash.h"
#include "hsmmcsd_API.h"
#include "i2clib/lld_hsi2c.h"
#include "boards/stw_board.h"
#include "devices/stw_device.h"
#include "stwutils_app.h"
#include "uartConsole.h"
#ifdef TDA3XX_FAMILY_BUILD
#include "sbl_utils/sbl_utils_tda3xx.h"
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This function copies data from NOR memory using EDMA.
 *
 * \param   dstAddr             Destination Address
 * \param   srcOffsetAddr       NOR Source Offset Address
 * \param   length              The length of data block to be copied.
 * \param   edmaChNum           EDMA channel number used for transfer.
 *
 * \return  None
 */
static void SblUtilsNorReadEdma(void    *dstAddr,
                                uint32_t srcOffsetAddr,
                                uint32_t length,
                                uint32_t edmaChNum);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Global variable for referencing the App Image File Pointer */
FIL gAppImageSDFilePtr;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

uint32_t SBLUtilsRead32KTimer(void)
{
    uint32_t timerVal = 0U;

    /* Read the counter value for 32 KHz SoC Synchronous Timer */
    timerVal = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);

    return timerVal;
}

int32_t SBLUtilsPrintfInit(UART_INST_t uartInstance)
{
    int32_t retVal = STW_SOK;

    /* Configure PRCM for UART instance */
    retVal = SBLUtilsUartPrcm(uartInstance);
    if (STW_SOK != retVal)
    {
        SBLLibAbortBoot();
    }

    /* Configure Pin Mux for UART instance */
    PlatformUARTSetPinMux(uartInstance);

    /* Initialize UART Peripheral */
    UARTConsoleInit(uartInstance);

    return retVal;
}

int32_t SBLUtilsNorRead(void    *dstAddr,
                        uint32_t srcOffsetAddr,
                        uint32_t length)
{
    /* Read from NOR memory */
    SblUtilsNorReadEdma(dstAddr, srcOffsetAddr, length, (uint32_t) 1U);

    return STW_SOK;
}

void SBLUtilsNorFileSeek(uint32_t *srcAddr, uint32_t numBytes)
{
    *(srcAddr) = numBytes;
}

int32_t SBLUtilsNorBootRprc(sbllibAppImageParseParams_t *imageParams)
{
    imageParams->appImageOffset = SBLUTILS_APP_IMAGE_OFFSET_NOR;

    SBLLibRegisterImageCopyCallback(&SBLUtilsNorRead,
                                    &SBLUtilsDDRReadEdma,
                                    &SBLUtilsNorFileSeek);

    return (SBLLibMultiCoreImageParse(imageParams));
}

int32_t SBLUtilsQspiReadSectors(void    *dstAddr,
                                uint32_t srcOffsetAddr,
                                uint32_t length)
{
    /* Read from QSPI */
    QSPI_ReadSectors_edma(dstAddr, srcOffsetAddr, length, (uint32_t) 1U);

    return STW_SOK;
}

int32_t SBLUtilsQspiBootRprc(sbllibAppImageParseParams_t *imageParams)
{
    uint32_t deviceId, mfgId, devId;
    char     devIdStr[10] = {0}, mfgIdStr[10] = {0};

    QSPI_Initialize(DEVICE_TYPE_QSPI4);

    /* Print the Device ID & Manufacturer ID */
    deviceId = QSPI_GetDeviceId();
    mfgId    = deviceId & 0xFFU;
    devId    = (deviceId & 0xFF0000U) >> 16U;

    SBLLibConvertHexToString(mfgId, mfgIdStr);
    SBLLibConvertHexToString(devId, devIdStr);

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1, "\n Manufacturer ID - ");
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1, mfgIdStr);
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1, "\n Device ID - ");
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1, devIdStr);

    QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      (uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
    QSPI_ConfMAddrSpace((uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,
                        QSPI_CS0);

    SBLLibRegisterImageCopyCallback(&SBLUtilsQspiReadSectors,
                                    &SBLUtilsDDRReadEdma,
                                    &QSPI_seek);
    imageParams->appImageOffset = SBLUTILS_APP_IMAGE_OFFSET_QSPI;

    return (SBLLibMultiCoreImageParse(imageParams));
}

int32_t SBLUtilsSDFileRead(void    *dstbuff,
                           uint32_t srcFileAddr,
                           uint32_t numBytes)
{
    uint8_t *buffPtr   = (uint8_t *) dstbuff;
    uint32_t bytesRead = 0U;
    int32_t  retVal    = STW_SOK;
    FRESULT  fresult   = FR_OK;

    fresult = f_read(&gAppImageSDFilePtr,
                     (void *) buffPtr,
                     numBytes,
                     (UINT *) &bytesRead);
    if ((FR_OK != fresult) || (bytesRead != numBytes))
    {
        retVal = STW_EFAIL;
    }

    return retVal;
}

void SBLUtilsSDFileSeek(uint32_t *filePtr, uint32_t numBytes)
{
    f_lseek(&gAppImageSDFilePtr, numBytes);
}

int32_t SBLUtilsQspiSDBootRprc(sbllibAppImageParseParams_t *imageParams)
{
    int32_t            retVal   = STW_EFAIL;
    char              *filename = "AppImage";
    FRESULT            fresult;
    MMC_INST_t         num = MMC4_INST;

    stwAppInitParams_t stwAppInitParamsVal;

    stwAppInitParamsVal.isI2cInitReq  = TRUE;
    stwAppInitParamsVal.isUartInitReq = FALSE;
    retVal = StwUtils_appDefaultInit(stwAppInitParamsVal);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\nSystem Init Failed while configuring MMC \n");
    }

    /*IOExpander mux config : Mux F : MMC4*/
    BOARDSelectDevice(DEVICE_ID_MMC, DEVICE_MMC_INST_ID_4);

    if (0 != HSMMCSDInit(num))
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR, "\n No valid SD card \n");
        retVal = STW_EFAIL;
    }
    else
    {
        fresult = f_open(&gAppImageSDFilePtr, filename, (BYTE) FA_READ);
        if (FR_OK != fresult)
        {
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         "\n QSPI_SD Boot - File open fails \n");
            retVal = STW_EFAIL;
        }
        else
        {
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                         "\n SD Boot - file open completed successfully \n");

            SBLLibRegisterImageCopyCallback(&SBLUtilsSDFileRead,
                                            &SBLUtilsDDRReadEdma,
                                            &SBLUtilsSDFileSeek);
            imageParams->appImageOffset = 0U;
            retVal = SBLLibMultiCoreImageParse(imageParams);

            f_close(&gAppImageSDFilePtr);
        }
    }
    return retVal;
}

void SBLUtilsTriggerEDMAPolledMode(uint32_t srcAddr,
                                   uint32_t destAddr,
                                   uint32_t dataSize,
                                   uint32_t edmaChannelNum,
                                   uint32_t edmaTccNum,
                                   uint32_t edmaEvtqNum,
                                   uint32_t paramSetNum)
{
    EDMA3CCPaRAMEntry edmaParams;
    uint32_t          edmaACnt, edmaBCnt, edmaCCnt;
    uint32_t          tempdataSize = dataSize;
    uint32_t          remDataSize;
    uint32_t          index;

    /*
     * EDMA transfer is of type AB synchronized for better throughput.
     * Set ACnt as 64 bytes and calculate BCnt & CCnt.
     */
    edmaACnt = 0x3FFFU;
    edmaCCnt = 1U;
    while (0xFFFFU < (tempdataSize / edmaACnt))
    {
        edmaCCnt     = edmaCCnt * 2U;
        tempdataSize = tempdataSize / 2U;
    }
    edmaBCnt     = tempdataSize / edmaACnt;
    tempdataSize = edmaACnt * edmaBCnt * edmaCCnt;
    remDataSize  = dataSize - tempdataSize;

    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE,
                        EDMA3_CHANNEL_TYPE_DMA,
                        edmaChannelNum,
                        edmaTccNum,
                        edmaEvtqNum);

    edmaParams.opt      = 0U;
    edmaParams.srcAddr  = srcAddr;
    edmaParams.destAddr = destAddr;
    edmaParams.aCnt     = edmaACnt;
    edmaParams.bCnt     = edmaBCnt;
    edmaParams.cCnt     = edmaCCnt;
    edmaParams.srcBIdx  = edmaACnt;
    edmaParams.destBIdx = edmaACnt;
    edmaParams.srcCIdx  = edmaACnt * edmaBCnt;
    edmaParams.destCIdx = edmaACnt * edmaBCnt;
    edmaParams.linkAddr = 0xFFFFU;
    /* Program the TCC */
    edmaParams.opt |=
        ((edmaTccNum << EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK);
    /* Enable Intermediate & Final transfer completion interrupt */
    edmaParams.opt |= (EDMA3_OPT_ITCINTEN_MASK);
    edmaParams.opt |= (EDMA3_OPT_TCINTEN_MASK);
    /* AB Sync Transfer Mode */
    edmaParams.opt |= EDMA_TPCC_OPT_SYNCDIM_MASK;

    /* Map Param Set to Channel */
    EDMA3ChannelToParamMap(SOC_EDMA_TPCC_BASE, edmaChannelNum, paramSetNum);

    /* Set Params in EDMA registers */
    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, paramSetNum, &edmaParams);

    /*
     * Transfer is done in AB sync mode
     * Number of triggers required are edmaCCnt
     */
    for (index = 0U; index < edmaCCnt; index++)
    {
        /* Enable transfer manually */
        EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE, edmaChannelNum,
                            EDMA3_TRIG_MODE_MANUAL);

        /* Wait for transfer to complete */
        while (((uint32_t) 0x1U << edmaTccNum) !=
               (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE) &
                ((uint32_t) 0x1U << edmaTccNum)))
        {
            /* Busy Loop */
        }

        /* Clear EDMA completion interrupt */
        EDMA3ClrIntr(SOC_EDMA_TPCC_BASE, edmaTccNum);
    }

    if (0U != remDataSize)
    {
        edmaParams.opt      = 0U;
        edmaParams.srcAddr  = srcAddr + ((edmaACnt * edmaBCnt) * edmaCCnt);
        edmaParams.destAddr = destAddr + ((edmaACnt * edmaBCnt) * edmaCCnt);
        edmaParams.aCnt     = remDataSize;
        edmaParams.bCnt     = 1U;
        edmaParams.cCnt     = 1U;
        edmaParams.srcBIdx  = remDataSize;
        edmaParams.destBIdx = remDataSize;
        edmaParams.srcCIdx  = 0U;
        edmaParams.destCIdx = 0U;
        edmaParams.linkAddr = 0xFFFFU;
        edmaParams.opt     |=
            (EDMA3_OPT_TCINTEN_MASK |
             ((edmaTccNum << EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK));

        EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, paramSetNum, &edmaParams);

        EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE, edmaChannelNum,
                            EDMA3_TRIG_MODE_MANUAL);

        while (((uint32_t) 0x1U << edmaTccNum) !=
               (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE) &
                ((uint32_t) 0x1U << edmaTccNum)))
        {
            /* Busy Loop */
        }
        EDMA3ClrIntr(SOC_EDMA_TPCC_BASE, edmaTccNum);
    }
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static void SblUtilsNorReadEdma(void    *dstAddr,
                                uint32_t srcOffsetAddr,
                                uint32_t length,
                                uint32_t edmaChNum)
{
    EDMA3CCPaRAMEntry edmaParam;
    uint32_t          bCntValue = 1U;
    uint32_t          remBytes  = 0;
    uint32_t          aCntValue = length;
    uint32_t          addr      = (uint32_t) (dstAddr);
    uint32_t          maxACnt   = 0x7FFFU;
    if (length > maxACnt)
    {
        bCntValue = (length / maxACnt);
        remBytes  = (length % maxACnt);
        aCntValue = maxACnt;
    }

    /* Compute NOR address and size */
    edmaParam.opt      = 0;
    edmaParam.srcAddr  = SBLUTILS_NOR_BASE + srcOffsetAddr;
    edmaParam.destAddr = addr;
    edmaParam.aCnt     = aCntValue;
    edmaParam.bCnt     = bCntValue;
    edmaParam.cCnt     = 1;
    edmaParam.srcBIdx  = aCntValue;
    edmaParam.destBIdx = aCntValue;
    edmaParam.srcCIdx  = 0;
    edmaParam.destCIdx = 0;
    edmaParam.linkAddr = 0xFFFF;
    edmaParam.opt     |=
        (EDMA_TPCC_OPT_TCINTEN_MASK |
         ((edmaChNum << EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK) |
         EDMA_TPCC_OPT_SYNCDIM_MASK);

    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, edmaChNum, &edmaParam);
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE, edmaChNum, EDMA3_TRIG_MODE_MANUAL);

    while (0U ==
           (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE) &
            ((uint32_t) 1U << edmaChNum)))
    {
        /* Busy Loop */
    }
    EDMA3ClrIntr(SOC_EDMA_TPCC_BASE, edmaChNum);
    if (0U != remBytes)
    {
        /* Compute NOR address and size */
        edmaParam.opt     = 0;
        edmaParam.srcAddr =
            (SBLUTILS_NOR_BASE + ((bCntValue * maxACnt) + srcOffsetAddr));
        edmaParam.destAddr = (addr + (maxACnt * bCntValue));
        edmaParam.aCnt     = remBytes;
        edmaParam.bCnt     = 1;
        edmaParam.cCnt     = 1;
        edmaParam.srcBIdx  = remBytes;
        edmaParam.destBIdx = remBytes;
        edmaParam.srcCIdx  = 0;
        edmaParam.destCIdx = 0;
        edmaParam.linkAddr = 0xFFFF;
        edmaParam.opt     |=
            (EDMA_TPCC_OPT_TCINTEN_MASK |
             ((edmaChNum << EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK));

        EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, edmaChNum, &edmaParam);
        EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE, edmaChNum,
                            EDMA3_TRIG_MODE_MANUAL);

        while (0U ==
               (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE) &
                ((uint32_t) 1U << edmaChNum)))
        {
            /* Busy Loop */
        }
        EDMA3ClrIntr(SOC_EDMA_TPCC_BASE, edmaChNum);
    }
}

