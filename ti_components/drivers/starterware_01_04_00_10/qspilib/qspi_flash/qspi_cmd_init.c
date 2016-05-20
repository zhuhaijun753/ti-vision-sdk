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
/**
 *  @file   qspi_cmd_init.c
 *
 *  @brief  This file contains the Flash cmd initialization.
 *
 */

/*_______________________________ Include Files _____________________________*/
#include "stdint.h"
#include <stdlib.h>
#include <common/stw_types.h>
#include "soc_defines.h"
#include "platform.h"
#include "qspi_flash.h"
#include "qspi_cmd_init.h"
#include "hw_qspi.h"

static int32_t saveFlashCmd(const QSPI_FlashCmd_t *srcCmd,
                            QSPI_FlashCmd_t       *destCmd);
static void QSPI_SpansionFlashInit(qspi_DeviceType_e DeviceType);
static void QSPI_MicronFlashInit(qspi_DeviceType_e DeviceType);
static void QSPI_WinbondFlashInit(qspi_DeviceType_e DeviceType);
static void QSPI_IssiFlashInit(qspi_DeviceType_e DeviceType);

extern QSPI_FlashDevInfo_t gQspiFlashDevInfo;
extern uint32_t gQspiCmdInitDone;

int32_t QSPI_GetDefaultFlashDevInfo(qspi_DeviceType_e    flashType,
                                    QSPI_FlashDevInfo_t *flashDevInfo)
{
    int32_t  retVal = STW_SOK;
    uint32_t qspi_FlashInitFxnPtrTmp;
    if (NULL == flashDevInfo)
    {
        retVal = STW_EBADARGS;
    }
    if (retVal == STW_SOK)
    {
        flashDevInfo->flashType     = flashType;
        flashDevInfo->qspiCs        = 0U;
        flashDevInfo->qspiDataDelay = QSPI__SPI_DC_REG__DD__CS_TO_DATA_DELAY_0;

        /* Initialize default mode to 3 and clk frequency to 12MHz */
        flashDevInfo->qspiMode      = 3;
        flashDevInfo->qspifrequency = QSPI_SCLK_FREQ_12MHz;

        /* Initialize default data lines to 1 */
        flashDevInfo->numDatalines = 1U;

        flashDevInfo->qspiFlashInitFxn = NULL;
    }
    if ((retVal == STW_SOK) &&
        ((flashType == DEVICE_TYPE_SPANSION_QSPI4) ||
         (flashType == DEVICE_TYPE_SPANSION_QSPI1)))
    {
        /* Initialize QSPI Mode */
        flashDevInfo->qspiMode = PlatformGetQspiMode();

        /* Initialize QSPI clk frequency */
        if (flashType == DEVICE_TYPE_SPANSION_QSPI4)
        {
            if (3U == flashDevInfo->qspiMode)
            {
                #if defined (TDA3XX_FAMILY_BUILD)
                flashDevInfo->qspifrequency = QSPI_SCLK_FREQ_64MHz;
                #else
                flashDevInfo->qspifrequency = QSPI_SCLK_FREQ_48MHz;
                #endif
            }
            else if (0U == flashDevInfo->qspiMode)
            {
                #if defined (TDA3XX_FAMILY_BUILD)
                flashDevInfo->qspifrequency = QSPI_SCLK_FREQ_96MHz;
                #else
                flashDevInfo->qspifrequency = QSPI_SCLK_FREQ_64MHz;
                #endif
            }
            else
            {
                /* Use default speed */
            }
        }

        /* Initializing Id Cmd */
        /* memClr(flashDevInfo, sizeof(flashDevInfo)); */
        flashDevInfo->idCmd.numCmdBits       = 8;
        flashDevInfo->idCmd.cmd              = QSPI_CMD_MFGID;
        flashDevInfo->idCmd.numAddrBits      = 24;
        flashDevInfo->idCmd.addr             = 0;
        flashDevInfo->idCmd.numAddrDummyBits = 0;
        flashDevInfo->idCmd.dataType         =
            QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE;
        flashDevInfo->idCmd.numDataWords       = 2;
        flashDevInfo->idCmd.numPerDataWordbits = 8;

        /* Initializing write Cmd */
        flashDevInfo->writeCmd.numCmdBits       = 8;
        flashDevInfo->writeCmd.cmd              = QSPI_CMD_WRITE;
        flashDevInfo->writeCmd.numAddrBits      = 32;
        flashDevInfo->writeCmd.addr             = 0;
        flashDevInfo->writeCmd.numAddrDummyBits = 0;
        flashDevInfo->writeCmd.dataType         =
            QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE;
        flashDevInfo->writeCmd.numDataWords       = 0;
        flashDevInfo->writeCmd.numPerDataWordbits = 32;

        /* Initializing sector erase Cmd */
        flashDevInfo->subSectorEraseCmd.numCmdBits         = 8;
        flashDevInfo->subSectorEraseCmd.cmd                = QSPI_CMD_PAGEERASE;
        flashDevInfo->subSectorEraseCmd.numAddrBits        = 32;
        flashDevInfo->subSectorEraseCmd.addr               = 0;
        flashDevInfo->subSectorEraseCmd.numAddrDummyBits   = 0;
        flashDevInfo->subSectorEraseCmd.dataType           = 0;
        flashDevInfo->subSectorEraseCmd.numDataWords       = 0;
        flashDevInfo->subSectorEraseCmd.numPerDataWordbits = 0;

        /* Initializing sector erase Cmd */
        flashDevInfo->sectorEraseCmd.numCmdBits         = 8;
        flashDevInfo->sectorEraseCmd.cmd                = QSPI_CMD_BLKERASE;
        flashDevInfo->sectorEraseCmd.numAddrBits        = 32;
        flashDevInfo->sectorEraseCmd.addr               = 0;
        flashDevInfo->sectorEraseCmd.numAddrDummyBits   = 0;
        flashDevInfo->sectorEraseCmd.dataType           = 0;
        flashDevInfo->sectorEraseCmd.numDataWords       = 0;
        flashDevInfo->sectorEraseCmd.numPerDataWordbits = 0;

        /* Initializing full erase Cmd */
        flashDevInfo->fullEraseCmd.numCmdBits         = 8;
        flashDevInfo->fullEraseCmd.cmd                = QSPI_CMD_FULLERASE;
        flashDevInfo->fullEraseCmd.numAddrBits        = 0;
        flashDevInfo->fullEraseCmd.addr               = 0;
        flashDevInfo->fullEraseCmd.numAddrDummyBits   = 0;
        flashDevInfo->fullEraseCmd.dataType           = 0;
        flashDevInfo->fullEraseCmd.numDataWords       = 0;
        flashDevInfo->fullEraseCmd.numPerDataWordbits = 0;

        /* Initializing write enable Cmd */
        flashDevInfo->writeEnableCmd.numCmdBits         = 8;
        flashDevInfo->writeEnableCmd.cmd                = QSPI_CMD_WREN;
        flashDevInfo->writeEnableCmd.numAddrBits        = 0;
        flashDevInfo->writeEnableCmd.addr               = 0;
        flashDevInfo->writeEnableCmd.numAddrDummyBits   = 0;
        flashDevInfo->writeEnableCmd.dataType           = 0;
        flashDevInfo->writeEnableCmd.numDataWords       = 0;
        flashDevInfo->writeEnableCmd.numPerDataWordbits = 0;

        /* Initializing flash status Cmd */
        flashDevInfo->flashStatusCmd.numCmdBits       = 8;
        flashDevInfo->flashStatusCmd.cmd              = QSPI_CMD_RDSR;
        flashDevInfo->flashStatusCmd.numAddrBits      = 0;
        flashDevInfo->flashStatusCmd.addr             = 0;
        flashDevInfo->flashStatusCmd.numAddrDummyBits = 0;
        flashDevInfo->flashStatusCmd.dataType         =
            QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE;
        flashDevInfo->flashStatusCmd.numDataWords       = 1;
        flashDevInfo->flashStatusCmd.numPerDataWordbits = 8;
        if (flashType == DEVICE_TYPE_SPANSION_QSPI1)
        {
            /* Initializing read Cmd */
            flashDevInfo->readCmd.numCmdBits       = 8;
            flashDevInfo->readCmd.cmd              = QSPI_CMD_READ;
            flashDevInfo->readCmd.numAddrBits      = 32;
            flashDevInfo->readCmd.addr             = 0;
            flashDevInfo->readCmd.numAddrDummyBits = 0;
            flashDevInfo->readCmd.dataType         =
                QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE;
            flashDevInfo->readCmd.numDataWords       = 0;
            flashDevInfo->readCmd.numPerDataWordbits = 32;

            /* Initialize data lines */
            flashDevInfo->numDatalines = 1U;
        }
        else /* DEVICE_TYPE_SPANSION_QSPI4 */
        {
            /* Initializing read Cmd */
            flashDevInfo->readCmd.numCmdBits       = 8;
            flashDevInfo->readCmd.cmd              = QSPI_CMD_FAST_QREAD;
            flashDevInfo->readCmd.numAddrBits      = 32;
            flashDevInfo->readCmd.addr             = 0;
            flashDevInfo->readCmd.numAddrDummyBits = 8;
            flashDevInfo->readCmd.dataType         =
                QSPI_SPI_CMD_REG_CMD_SIX_PIN_READ_QUAD;
            flashDevInfo->readCmd.numDataWords       = 0;
            flashDevInfo->readCmd.numPerDataWordbits = 32;

            /* Initialize data lines */
            flashDevInfo->numDatalines = 4U;
        }
        qspi_FlashInitFxnPtrTmp        = (uint32_t) &QSPI_SpansionFlashInit;
        flashDevInfo->qspiFlashInitFxn =
            (QSPI_flashInitFunPtr) qspi_FlashInitFxnPtrTmp;
    }
    if ((retVal == STW_SOK) &&
        ((flashType == DEVICE_TYPE_MICRON_QSPI1) ||
         (flashType == DEVICE_TYPE_MICRON_QSPI4)))
    {
        /* Initializing Id Cmd */
        flashDevInfo->idCmd.numCmdBits       = 8;
        flashDevInfo->idCmd.cmd              = QSPI_CMD_MICRON_MFGID;
        flashDevInfo->idCmd.numAddrBits      = 0;
        flashDevInfo->idCmd.addr             = 0;
        flashDevInfo->idCmd.numAddrDummyBits = 0;
        flashDevInfo->idCmd.dataType         =
            QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE;
        flashDevInfo->idCmd.numDataWords       = 20;
        flashDevInfo->idCmd.numPerDataWordbits = 8;

        /* Initializing write Cmd */
        flashDevInfo->writeCmd.numCmdBits       = 8;
        flashDevInfo->writeCmd.cmd              = QSPI_CMD_MICRON_WRITE_24;
        flashDevInfo->writeCmd.numAddrBits      = 24;
        flashDevInfo->writeCmd.addr             = 0;
        flashDevInfo->writeCmd.numAddrDummyBits = 0;
        flashDevInfo->writeCmd.dataType         =
            QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE;
        flashDevInfo->writeCmd.numDataWords       = 0;
        flashDevInfo->writeCmd.numPerDataWordbits = 32;

        /* Initializing sub sector erase Cmd */
        flashDevInfo->subSectorEraseCmd.numCmdBits = 8;
        flashDevInfo->subSectorEraseCmd.cmd        =
            QSPI_CMD_PAGEERASE_24;
        flashDevInfo->subSectorEraseCmd.numAddrBits        = 24;
        flashDevInfo->subSectorEraseCmd.addr               = 0;
        flashDevInfo->subSectorEraseCmd.numAddrDummyBits   = 0;
        flashDevInfo->subSectorEraseCmd.dataType           = 0;
        flashDevInfo->subSectorEraseCmd.numDataWords       = 0;
        flashDevInfo->subSectorEraseCmd.numPerDataWordbits = 0;

        /* Initializing sector erase Cmd */
        flashDevInfo->sectorEraseCmd.numCmdBits = 8;
        flashDevInfo->sectorEraseCmd.cmd        =
            QSPI_CMD_MICRON_BLKERASE_24;
        flashDevInfo->sectorEraseCmd.numAddrBits        = 24;
        flashDevInfo->sectorEraseCmd.addr               = 0;
        flashDevInfo->sectorEraseCmd.numAddrDummyBits   = 0;
        flashDevInfo->sectorEraseCmd.dataType           = 0;
        flashDevInfo->sectorEraseCmd.numDataWords       = 0;
        flashDevInfo->sectorEraseCmd.numPerDataWordbits = 0;

        /* Initializing full erase Cmd */
        flashDevInfo->fullEraseCmd.numCmdBits = 8;
        flashDevInfo->fullEraseCmd.cmd        =
            QSPI_CMD_MICRON_FULLERASE;
        flashDevInfo->fullEraseCmd.numAddrBits        = 0;
        flashDevInfo->fullEraseCmd.addr               = 0;
        flashDevInfo->fullEraseCmd.numAddrDummyBits   = 0;
        flashDevInfo->fullEraseCmd.dataType           = 0;
        flashDevInfo->fullEraseCmd.numDataWords       = 0;
        flashDevInfo->fullEraseCmd.numPerDataWordbits = 0;

        /* Initializing write enable Cmd */
        flashDevInfo->writeEnableCmd.numCmdBits         = 8;
        flashDevInfo->writeEnableCmd.cmd                = QSPI_CMD_MICRON_WREN;
        flashDevInfo->writeEnableCmd.numAddrBits        = 0;
        flashDevInfo->writeEnableCmd.addr               = 0;
        flashDevInfo->writeEnableCmd.numAddrDummyBits   = 0;
        flashDevInfo->writeEnableCmd.dataType           = 0;
        flashDevInfo->writeEnableCmd.numDataWords       = 0;
        flashDevInfo->writeEnableCmd.numPerDataWordbits = 0;

        /* Initializing flash status Cmd */
        flashDevInfo->flashStatusCmd.numCmdBits       = 8;
        flashDevInfo->flashStatusCmd.cmd              = QSPI_CMD_MICRON_RDSR;
        flashDevInfo->flashStatusCmd.numAddrBits      = 0;
        flashDevInfo->flashStatusCmd.addr             = 0;
        flashDevInfo->flashStatusCmd.numAddrDummyBits = 0;
        flashDevInfo->flashStatusCmd.dataType         =
            QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE;
        flashDevInfo->flashStatusCmd.numDataWords       = 1;
        flashDevInfo->flashStatusCmd.numPerDataWordbits = 8;

        if (flashType == DEVICE_TYPE_MICRON_QSPI1)
        {
            /* Initializing read Cmd */
            flashDevInfo->readCmd.numCmdBits       = 8;
            flashDevInfo->readCmd.cmd              = QSPI_CMD_MICRON_READ_24;
            flashDevInfo->readCmd.numAddrBits      = 24;
            flashDevInfo->readCmd.addr             = 0;
            flashDevInfo->readCmd.numAddrDummyBits = 0;
            flashDevInfo->readCmd.dataType         =
                QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE;
            flashDevInfo->readCmd.numDataWords       = 0;
            flashDevInfo->readCmd.numPerDataWordbits = 32;
        }
        else /* DEVICE_TYPE_MICRON_QSPI1 */
        {
            /* Initializing read Cmd */
            flashDevInfo->readCmd.numCmdBits       = 8;
            flashDevInfo->readCmd.cmd              = QSPI_CMD_MICRON_QREAD_24;
            flashDevInfo->readCmd.numAddrBits      = 24;
            flashDevInfo->readCmd.addr             = 0;
            flashDevInfo->readCmd.numAddrDummyBits = 8;
            flashDevInfo->readCmd.dataType         =
                QSPI_SPI_CMD_REG_CMD_SIX_PIN_READ_QUAD;
            flashDevInfo->readCmd.numDataWords       = 0;
            flashDevInfo->readCmd.numPerDataWordbits = 32;
        }
        qspi_FlashInitFxnPtrTmp        = (uint32_t) &QSPI_MicronFlashInit;
        flashDevInfo->qspiFlashInitFxn =
            (QSPI_flashInitFunPtr) qspi_FlashInitFxnPtrTmp;
    }
    if ((retVal == STW_SOK) &&
        ((flashType == DEVICE_TYPE_WINBOND_QSPI1) ||
         (flashType == DEVICE_TYPE_WINBOND_QSPI4) ||
         (flashType == DEVICE_TYPE_ISSI_QSPI1) ||
         (flashType == DEVICE_TYPE_ISSI_QSPI4)))
    {
        /* Initializing Id Cmd */
        flashDevInfo->idCmd.numCmdBits       = 8;
        flashDevInfo->idCmd.cmd              = QSPI_CMD_MFGID;
        flashDevInfo->idCmd.numAddrBits      = 24;
        flashDevInfo->idCmd.addr             = 0;
        flashDevInfo->idCmd.numAddrDummyBits = 0;
        flashDevInfo->idCmd.dataType         =
            QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE;
        flashDevInfo->idCmd.numDataWords       = 2;
        flashDevInfo->idCmd.numPerDataWordbits = 8;

        /* Initializing write Cmd */
        flashDevInfo->writeCmd.numCmdBits       = 8;
        flashDevInfo->writeCmd.cmd              = QSPI_CMD_WRITE_24;
        flashDevInfo->writeCmd.numAddrBits      = 24;
        flashDevInfo->writeCmd.addr             = 0;
        flashDevInfo->writeCmd.numAddrDummyBits = 0;
        flashDevInfo->writeCmd.dataType         =
            QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE;
        flashDevInfo->writeCmd.numDataWords       = 0;
        flashDevInfo->writeCmd.numPerDataWordbits = 32;

        /* Initializing sub sector erase Cmd */
        flashDevInfo->subSectorEraseCmd.numCmdBits = 8;
        flashDevInfo->subSectorEraseCmd.cmd        =
            QSPI_CMD_PAGEERASE_24;
        flashDevInfo->subSectorEraseCmd.numAddrBits        = 24;
        flashDevInfo->subSectorEraseCmd.addr               = 0;
        flashDevInfo->subSectorEraseCmd.numAddrDummyBits   = 0;
        flashDevInfo->subSectorEraseCmd.dataType           = 0;
        flashDevInfo->subSectorEraseCmd.numDataWords       = 0;
        flashDevInfo->subSectorEraseCmd.numPerDataWordbits = 0;

        /* Initializing sector erase Cmd */
        flashDevInfo->sectorEraseCmd.numCmdBits = 8;
        flashDevInfo->sectorEraseCmd.cmd        =
            QSPI_CMD_BLKERASE_24;
        flashDevInfo->sectorEraseCmd.numAddrBits        = 24;
        flashDevInfo->sectorEraseCmd.addr               = 0;
        flashDevInfo->sectorEraseCmd.numAddrDummyBits   = 0;
        flashDevInfo->sectorEraseCmd.dataType           = 0;
        flashDevInfo->sectorEraseCmd.numDataWords       = 0;
        flashDevInfo->sectorEraseCmd.numPerDataWordbits = 0;

        /* Initializing full erase Cmd */
        flashDevInfo->fullEraseCmd.numCmdBits = 8;
        flashDevInfo->fullEraseCmd.cmd        =
            QSPI_CMD_FULLERASE;
        flashDevInfo->fullEraseCmd.numAddrBits        = 0;
        flashDevInfo->fullEraseCmd.addr               = 0;
        flashDevInfo->fullEraseCmd.numAddrDummyBits   = 0;
        flashDevInfo->fullEraseCmd.dataType           = 0;
        flashDevInfo->fullEraseCmd.numDataWords       = 0;
        flashDevInfo->fullEraseCmd.numPerDataWordbits = 0;

        /* Initializing write enable Cmd */
        flashDevInfo->writeEnableCmd.numCmdBits         = 8;
        flashDevInfo->writeEnableCmd.cmd                = QSPI_CMD_WREN;
        flashDevInfo->writeEnableCmd.numAddrBits        = 0;
        flashDevInfo->writeEnableCmd.addr               = 0;
        flashDevInfo->writeEnableCmd.numAddrDummyBits   = 0;
        flashDevInfo->writeEnableCmd.dataType           = 0;
        flashDevInfo->writeEnableCmd.numDataWords       = 0;
        flashDevInfo->writeEnableCmd.numPerDataWordbits = 0;

        /* Initializing flash status Cmd */
        flashDevInfo->flashStatusCmd.numCmdBits       = 8;
        flashDevInfo->flashStatusCmd.cmd              = QSPI_CMD_RDSR;
        flashDevInfo->flashStatusCmd.numAddrBits      = 0;
        flashDevInfo->flashStatusCmd.addr             = 0;
        flashDevInfo->flashStatusCmd.numAddrDummyBits = 0;
        flashDevInfo->flashStatusCmd.dataType         =
            QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE;
        flashDevInfo->flashStatusCmd.numDataWords       = 1;
        flashDevInfo->flashStatusCmd.numPerDataWordbits = 8;

        if ((flashType == DEVICE_TYPE_WINBOND_QSPI1) ||
            (flashType == DEVICE_TYPE_ISSI_QSPI1))
        {
            /* Initializing read Cmd */
            flashDevInfo->readCmd.numCmdBits       = 8;
            flashDevInfo->readCmd.cmd              = QSPI_CMD_READ_24;
            flashDevInfo->readCmd.numAddrBits      = 24;
            flashDevInfo->readCmd.addr             = 0;
            flashDevInfo->readCmd.numAddrDummyBits = 0;
            flashDevInfo->readCmd.dataType         =
                QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE;
            flashDevInfo->readCmd.numDataWords       = 0;
            flashDevInfo->readCmd.numPerDataWordbits = 32;
        }
        if ((flashType == DEVICE_TYPE_WINBOND_QSPI4) ||
            (flashType == DEVICE_TYPE_ISSI_QSPI4))
        {
            /* Initializing read Cmd */
            flashDevInfo->readCmd.numCmdBits       = 8;
            flashDevInfo->readCmd.cmd              = QSPI_CMD_FAST_QREAD_24;
            flashDevInfo->readCmd.numAddrBits      = 24;
            flashDevInfo->readCmd.addr             = 0;
            flashDevInfo->readCmd.numAddrDummyBits = 8;
            flashDevInfo->readCmd.dataType         =
                QSPI_SPI_CMD_REG_CMD_SIX_PIN_READ_QUAD;
            flashDevInfo->readCmd.numDataWords       = 0;
            flashDevInfo->readCmd.numPerDataWordbits = 32;
        }

        if ((flashType == DEVICE_TYPE_WINBOND_QSPI1) ||
            (flashType == DEVICE_TYPE_WINBOND_QSPI4))
        {
            qspi_FlashInitFxnPtrTmp        = (uint32_t) &QSPI_WinbondFlashInit;
            flashDevInfo->qspiFlashInitFxn =
                (QSPI_flashInitFunPtr) qspi_FlashInitFxnPtrTmp;
        }
        if ((flashType == DEVICE_TYPE_ISSI_QSPI1) ||
            (flashType == DEVICE_TYPE_ISSI_QSPI4))
        {
            qspi_FlashInitFxnPtrTmp        = (uint32_t) &QSPI_IssiFlashInit;
            flashDevInfo->qspiFlashInitFxn =
                (QSPI_flashInitFunPtr) qspi_FlashInitFxnPtrTmp;
        }
    }

    return retVal;
}

int32_t QSPI_SetDefaultFlashDevInfo(qspi_DeviceType_e          flashType,
                                    const QSPI_FlashDevInfo_t *flashDevInfo)
{
    int32_t retVal = STW_SOK;
    if (NULL == flashDevInfo)
    {
        retVal = STW_EBADARGS;
    }
    else
    {
        gQspiFlashDevInfo.flashType     = flashDevInfo->flashType;
        gQspiFlashDevInfo.qspiMode      = flashDevInfo->qspiMode;
        gQspiFlashDevInfo.qspiCs        = flashDevInfo->qspiCs;
        gQspiFlashDevInfo.qspiDataDelay = flashDevInfo->qspiDataDelay;
        gQspiFlashDevInfo.qspifrequency = flashDevInfo->qspifrequency;

        saveFlashCmd(&flashDevInfo->idCmd, &(gQspiFlashDevInfo.idCmd));
        saveFlashCmd(&flashDevInfo->readCmd, &gQspiFlashDevInfo.readCmd);
        saveFlashCmd(&flashDevInfo->writeCmd, &gQspiFlashDevInfo.writeCmd);
        saveFlashCmd(&flashDevInfo->subSectorEraseCmd,
                     &gQspiFlashDevInfo.subSectorEraseCmd);
        saveFlashCmd(&flashDevInfo->sectorEraseCmd,
                     &gQspiFlashDevInfo.sectorEraseCmd);
        saveFlashCmd(&flashDevInfo->fullEraseCmd,
                     &gQspiFlashDevInfo.fullEraseCmd);
        saveFlashCmd(&flashDevInfo->flashStatusCmd,
                     &gQspiFlashDevInfo.flashStatusCmd);
        saveFlashCmd(&flashDevInfo->writeEnableCmd,
                     &gQspiFlashDevInfo.writeEnableCmd);

        gQspiFlashDevInfo.qspiFlashInitFxn = flashDevInfo->qspiFlashInitFxn;

        gQspiCmdInitDone = 1U;
    }
    return retVal;
}

static int32_t saveFlashCmd(const QSPI_FlashCmd_t *srcCmd,
                            QSPI_FlashCmd_t       *destCmd)
{
    int32_t retVal = STW_SOK;
    if ((srcCmd == NULL) || (destCmd == NULL))
    {
        retVal = STW_EBADARGS;
    }
    if (retVal == STW_SOK)
    {
        destCmd->numCmdBits         = srcCmd->numCmdBits;
        destCmd->cmd                = srcCmd->cmd;
        destCmd->numCmdDummyBits    = srcCmd->numCmdDummyBits;
        destCmd->numAddrBits        = srcCmd->numAddrBits;
        destCmd->addr               = srcCmd->addr;
        destCmd->numAddrDummyBits   = srcCmd->numAddrDummyBits;
        destCmd->dataType           = srcCmd->dataType;
        destCmd->numDataWords       = srcCmd->numDataWords;
        destCmd->numPerDataWordbits = srcCmd->numPerDataWordbits;
    }
    return retVal;
}

static void QSPI_SpansionFlashInit(qspi_DeviceType_e DeviceType)
{
    if (DeviceType == DEVICE_TYPE_SPANSION_QSPI4)
    {
        QSPI_QuadEnable();
    }
}

static void QSPI_MicronFlashInit(qspi_DeviceType_e DeviceType)
{
    uint32_t data;
    uint32_t nvcr;
    HAL_QSPI_Command_reg cmd = {0};

    if (DeviceType == DEVICE_TYPE_MICRON_QSPI4)
    {
        /* Read non volatile configuration register */
        data = QSPI_CMD_MICRON_RDNVCR;
        QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, &data, (int32_t) 1);

        cmd.regFields.frameLength = QSPI_CR_FLEN_2_WORDS;
        cmd.regFields.trCmd       = QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE;
        cmd.regFields.wordLength  = QSPI_CR_WLEN_8_BITS;
        QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmd.reg);
        QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);

        cmd.regFields.trCmd      = QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE;
        cmd.regFields.wordLength = QSPI_CR_WLEN_16_BITS;
        QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmd.reg);
        QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
        QSPIreadData(SOC_QSPI_ADDRSP0_BASE, &nvcr, (int32_t) 1);
        if ((nvcr & ((uint32_t) 0x1U << 2)) == 0)
        {
            /* Bit 2 of non volatile configuration register is quad enable
             * Set as its not set already */
            QSPI_WriteEnable();
            /* Set Configuration register 6th bit to 1 for Quad enable */
            nvcr |= ((uint32_t) 0x1U << 2);
            /* write non volatile configuration register */
            data = QSPI_CMD_MICRON_WRNVCR;
            QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, &data, (int32_t) 1);

            cmd.regFields.frameLength = QSPI_CR_FLEN_2_WORDS;
            cmd.regFields.trCmd       =
                QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE;
            cmd.regFields.wordLength = QSPI_CR_WLEN_8_BITS;
            QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmd.reg);
            QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);

            cmd.regFields.wordLength = QSPI_CR_WLEN_16_BITS;
            QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, &nvcr, (int32_t) 1);
            QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmd.reg);
            QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
            while ((QSPI_FlashStatus() & 0x01U) != 0U)
            {
                /* Do Nothing - Misra fix */
            }
        }
    }
}

static void QSPI_WinbondFlashInit(qspi_DeviceType_e DeviceType)
{
    uint32_t data;
    uint32_t sr;
    HAL_QSPI_Command_reg cmd = {0};

    if (DeviceType == DEVICE_TYPE_WINBOND_QSPI4)
    {
        /* Read Ststus register 2 */
        data = QSPI_CMD_WINBOND_RDSR2;
        QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, &data, (int32_t) 1);

        cmd.regFields.frameLength = QSPI_CR_FLEN_2_WORDS;
        cmd.regFields.trCmd       = QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE;
        cmd.regFields.wordLength  = QSPI_CR_WLEN_8_BITS;
        QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmd.reg);
        QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);

        cmd.regFields.trCmd      = QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE;
        cmd.regFields.wordLength = QSPI_CR_WLEN_8_BITS;
        QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmd.reg);
        QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
        QSPIreadData(SOC_QSPI_ADDRSP0_BASE, &sr, (int32_t) 1);

        if ((sr & ((uint32_t) 0x1U << 2)) == 0)
        {
            /* Bit 2 of status register 2 is quad enable
             * Set as its not set already */
            QSPI_WriteEnable();
            /* Set Configuration register 6th bit to 1 for Quad enable */
            sr |= ((uint32_t) 0x1U << 2);
            /* write SR register */
            data = QSPI_CMD_WINBOND_WRSR2;
            QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, &data, (int32_t) 1);

            cmd.regFields.frameLength = QSPI_CR_FLEN_2_WORDS;
            cmd.regFields.trCmd       =
                QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE;
            cmd.regFields.wordLength = QSPI_CR_WLEN_8_BITS;
            QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmd.reg);
            QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);

            QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, &sr, (int32_t) 1);
            QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmd.reg);
            QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
            while ((QSPI_FlashStatus() & 0x01U) != 0U)
            {
                /* Do Nothing - Misra fix */
            }
        }
    }
}

static void QSPI_IssiFlashInit(qspi_DeviceType_e DeviceType)
{
    uint32_t data;
    uint32_t sr;
    HAL_QSPI_Command_reg cmd = {0};

    if (DeviceType == DEVICE_TYPE_ISSI_QSPI4)
    {
        /* Read Ststus register 1 */
        data = QSPI_CMD_RDSR;
        QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, &data, (int32_t) 1);

        cmd.regFields.frameLength = QSPI_CR_FLEN_2_WORDS;
        cmd.regFields.trCmd       = QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE;
        cmd.regFields.wordLength  = QSPI_CR_WLEN_8_BITS;
        QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmd.reg);
        QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);

        cmd.regFields.trCmd      = QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE;
        cmd.regFields.wordLength = QSPI_CR_WLEN_8_BITS;
        QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmd.reg);
        QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
        QSPIreadData(SOC_QSPI_ADDRSP0_BASE, &sr, (int32_t) 1);

        if ((sr & ((uint32_t) 0x1U << 6)) == 0)
        {
            /* Bit 6 of status register is quad enable
             * Set as its not set already */
            QSPI_WriteEnable();
            /* Set Configuration register 6th bit to 1 for Quad enable */
            sr |= ((uint32_t) 0x1U << 6);
            /* write SR register */
            data = QSPI_CMD_WRREG;
            QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, &data, (int32_t) 1);

            cmd.regFields.frameLength = QSPI_CR_FLEN_2_WORDS;
            cmd.regFields.trCmd       =
                QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE;
            cmd.regFields.wordLength = QSPI_CR_WLEN_8_BITS;
            QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmd.reg);
            QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);

            QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, &sr, (int32_t) 1);
            QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmd.reg);
            QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);

            while ((QSPI_FlashStatus() & 0x01U) != 0U)
            {
                /* Do Nothing - Misra fix */
            }
        }
    }
}

