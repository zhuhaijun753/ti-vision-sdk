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
 *  @file   qspi.c
 *
 *  @brief  This file contains the Flash driver using QSPI hal.
 *
 *  @path   $(ds)\test\hal\qspi_test\qspi.c
 *
 */

/*_______________________________ Include Files _____________________________*/
#include "stdint.h"
#include <stdlib.h>
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include "soc_defines.h"
#include "platform.h"
#include "qspi_flash.h"
#include "qspi_cmd_init.h"
#include "hw_qspi.h"
#include "hw_types.h"
#include "hw_l4per_cm_core.h"
#include "hw_ctrl_core.h"

#define QSPI_READ_DEVICEID_MAX_WORDS   (20U)

static uint32_t getNumAddrBytesFromBits(uint32_t numBits);
static uint32_t getNumDummyBytesFromBits(uint32_t numBits);
static uint32_t getMemSetupReadType(uint32_t cmdRegDataType);
static void mem1cpy(void *dstAddr, uint32_t *srcAddr, uint32_t length);

QSPI_FlashDevInfo_t gQspiFlashDevInfo;
uint32_t gQspiCmdInitDone = 0U;

/**
 * \brief This function configures memory mapped address for different
 *        chip select in control module.
 *
 * \param     MMPT_S    Memory map switch value
 * \param     chipSelect    External Chip Select value from enum
 *                          qspi_ChipSelect_e
 *
 * \return    None
 */
void QSPI_ConfMAddrSpace(uint8_t MMPT_S,qspi_ChipSelect_e chipSelect)
{
    /* set MAddrSpace in control module for CS0*/
    HW_WR_FIELD32(
        (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_CONTROL_IO_2,
        CTRL_CORE_CONTROL_IO_2_QSPI_MEMMAPPED_CS,
        chipSelect);
}

void QSPI_SelClockFrequency(qspi_ClockFreq_e in_ClockSettings)
{
    /* select 128/192MHz from L4 QSPI CLK CTRL register */

    /* Set divider value in QSPI Clock Control */
    HW_WR_FIELD32(
        (uint32_t) SOC_L4PER_CM_CORE_BASE + CM_L4PER2_QSPI_CLKCTRL,
        CM_L4PER2_QSPI_CLKCTRL_CLKSEL_DIV,
        CM_L4PER2_QSPI_CLKCTRL_CLKSEL_DIV_DIV1);
    if (in_ClockSettings & QSPI_CLKSWITCH_MASK)  /* set QSPI clock source as
                                                  * PER_QSPI_CLK from DPLL_PER
                                                  */
    {
        HW_WR_FIELD32(
            (uint32_t) SOC_L4PER_CM_CORE_BASE + CM_L4PER2_QSPI_CLKCTRL,
            CM_L4PER2_QSPI_CLKCTRL_CLKSEL_SOURCE,
            CM_L4PER2_QSPI_CLKCTRL_CLKSEL_SOURCE_SEL_PER_QSPI_CLK);
    }
    else /* set QSPI clock source as 128MHz derived from DPLL_PER*/
    {
        HW_WR_FIELD32(
            (uint32_t) SOC_L4PER_CM_CORE_BASE + CM_L4PER2_QSPI_CLKCTRL,
            CM_L4PER2_QSPI_CLKCTRL_CLKSEL_SOURCE,
            CM_L4PER2_QSPI_CLKCTRL_CLKSEL_SOURCE_SEL_FUNC_128M_CLK);
    }
}

int32_t QSPI_executeCmd(QSPI_FlashCmd_t flashCmd, uint32_t *data)
{
    int32_t  retVal          = STW_SOK;
    HAL_QSPI_Command_reg cmd = {0};
    uint32_t frameLength     = 0U;
    uint32_t localData, i;

    if ((flashCmd.numDataWords != 0) && (NULL == data))
    {
        retVal = STW_EBADARGS;
    }
    if (retVal == STW_SOK)
    {
        if (flashCmd.numAddrBits != 0)
        {
            frameLength++;
        }
        if (flashCmd.numAddrDummyBits != 0)
        {
            frameLength++;
        }
        if (flashCmd.numDataWords != 0)
        {
            frameLength = frameLength + flashCmd.numDataWords;
        }

        /* Write Command */
        cmd.regFields.frameLength = frameLength;
        cmd.regFields.wirq        =
            QSPI_SPI_CMD_REG_WIRQ_WORD_COUNT_IRQ_DISABLE;
        cmd.regFields.firq =
            QSPI_SPI_CMD_REG_FIRQ_FRAME_COUNT_IRQ_DISABLE;
        cmd.regFields.trCmd      = QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE;
        cmd.regFields.wordLength = flashCmd.numCmdBits - 1U;
        cmd.regFields.cs         = QSPI_SPI_CMD_REG_CSNUM_CS_0;

        QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, &flashCmd.cmd, (int32_t) 1);
        QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmd.reg);
        QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);

        /* Write Address Bytes */
        if (flashCmd.numAddrBits != 0)
        {
            QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, &flashCmd.addr, (int32_t) 1);
            cmd.reg = QSPIgetCommandReg(SOC_QSPI_ADDRSP0_BASE);
            cmd.regFields.wordLength = flashCmd.numAddrBits - 1U;
            cmd.regFields.trCmd      =
                QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE;
            QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmd.reg);
            QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
        }

        /* Write dummy Bytes */
        if (flashCmd.numAddrDummyBits != 0)
        {
            localData = 0U;
            QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, &localData, (int32_t) 1);
            cmd.reg = QSPIgetCommandReg(SOC_QSPI_ADDRSP0_BASE);
            cmd.regFields.wordLength = flashCmd.numAddrDummyBits - 1U;
            cmd.regFields.trCmd      =
                QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE;
            QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmd.reg);
            QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
        }
        /* Read or Write data */
        if (flashCmd.numDataWords != 0)
        {
            if (flashCmd.dataType == QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE)
            {
                for (i = 0; i < flashCmd.numDataWords; i++)
                {
                    QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, data, (int32_t) 1);
                    cmd.reg = QSPIgetCommandReg(SOC_QSPI_ADDRSP0_BASE);
                    cmd.regFields.trCmd      = flashCmd.dataType;
                    cmd.regFields.wordLength = flashCmd.numPerDataWordbits - 1U;
                    QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmd.reg);
                    QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
                    data++;
                }
            }
            else
            {
                for (i = 0; i < flashCmd.numDataWords; i++)
                {
                    cmd.reg = QSPIgetCommandReg(SOC_QSPI_ADDRSP0_BASE);
                    cmd.regFields.trCmd      = flashCmd.dataType;
                    cmd.regFields.wordLength = flashCmd.numPerDataWordbits - 1U;
                    QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmd.reg);
                    QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
                    QSPIreadData(SOC_QSPI_ADDRSP0_BASE, data, (int32_t) 1);
                    data++;
                }
            }
        }
    }
    return retVal;
}

/*_____________________________________________________________________________
 * FUNCTION:     QSPI_Initialize
 *
 * DESCRIPTION:  Initializes the QSPI Device.
 *
 * PARAMETERS:   ipDeviceDesc
 *                   IO:  Device Descriptor
 *
 * RETURNS:      SUCCESS if the QSPI initialized successfully
 *
 *               FAIL:
 *
 * NOTES:
 *
 *____________________________________________________________________________*/
uint32_t QSPI_Initialize(qspi_DeviceType_e DeviceType)
{
    int32_t retVal;

    HAL_QSPI_DeviceControl_reg devCtrl;
    HAL_QSPI_MemMapSetup_reg   memSetup = {0};
    QSPI_FlashDevInfo_t        localFlashDevInfo;

    if (gQspiCmdInitDone == 0U)
    {
        /* Default initialize for device type passed */
        retVal = QSPI_GetDefaultFlashDevInfo(DeviceType, &localFlashDevInfo);
        if (retVal == STW_SOK)
        {
            QSPI_SetDefaultFlashDevInfo(DeviceType, &localFlashDevInfo);
        }
    }

    /*
     * Set Device Control register - clock polarity, phase, CS polarity and data
     * delay depending on silicon Revision
     */
    devCtrl.reg = QSPIgetDeviceControl(SOC_QSPI_ADDRSP0_BASE);

    if (3U == gQspiFlashDevInfo.qspiMode)
    {
        devCtrl.regFields.CKP0  = QSPI__SPI_DC_REG__CKP__DATA_ACTIVE;
        devCtrl.regFields.CSP0  = QSPI__SPI_DC_REG__CSP__ACTIVE_LOW;
        devCtrl.regFields.CKPH0 =
            QSPI__SPI_DC_REG__CKPH__CKP_1_SHIFT_OUT_FALLING_EDGE;
    }
    else
    {
        devCtrl.regFields.CKP0  = QSPI__SPI_DC_REG__CKP__DATA_INACTIVE;
        devCtrl.regFields.CSP0  = QSPI__SPI_DC_REG__CSP__ACTIVE_LOW;
        devCtrl.regFields.CKPH0 =
            QSPI__SPI_DC_REG__CKPH__CKP_0_SHIFT_OUT_FALLING_EDGE;
    }
    devCtrl.regFields.DD0 = gQspiFlashDevInfo.qspiDataDelay;
    QSPIsetDeviceControl(SOC_QSPI_ADDRSP0_BASE, devCtrl.reg);

    /* Set Clock Control register */
    QSPI_SelClockFrequency(gQspiFlashDevInfo.qspifrequency);
    QSPISetClockControl(SOC_QSPI_ADDRSP0_BASE, gQspiFlashDevInfo.qspifrequency);

    /* Set Memory Map Setup registers */
    memSetup.regFields.readCmd     = gQspiFlashDevInfo.readCmd.cmd;
    memSetup.regFields.numAddBytes = getNumAddrBytesFromBits(
        gQspiFlashDevInfo.readCmd.numAddrBits);
    memSetup.regFields.numDummyBytes = getNumDummyBytesFromBits(
        gQspiFlashDevInfo.readCmd.numAddrDummyBits);
    memSetup.regFields.readType = getMemSetupReadType(
        gQspiFlashDevInfo.readCmd.dataType);
    memSetup.regFields.writeCmd = gQspiFlashDevInfo.writeCmd.cmd;
    if (getNumDummyBytesFromBits(gQspiFlashDevInfo.readCmd.numAddrDummyBits) !=
        QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_NUM_D_BITS)
    {
        memSetup.regFields.numDummyBits = 0;
    }
    else
    {
        memSetup.regFields.numDummyBits =
            gQspiFlashDevInfo.readCmd.numAddrDummyBits;
    }
    QSPISetMemoryMapSetup(SOC_QSPI_ADDRSP0_BASE, memSetup.reg,
                          gQspiFlashDevInfo.qspiCs);

    if (NULL != gQspiFlashDevInfo.qspiFlashInitFxn)
    {
        gQspiFlashDevInfo.qspiFlashInitFxn(DeviceType);
    }

    return SUCCESS;
} /* QSPI_Initialize */

static uint32_t getMemSetupReadType(uint32_t cmdRegDataType)
{
    uint32_t localReadType;
    if (cmdRegDataType == QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE)
    {
        localReadType = QSPI_SPI_SETUP0_REG_READ_TYPE_NORMAL_READ;
    }
    else if (cmdRegDataType == QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_DUAL)
    {
        localReadType = QSPI_SPI_SETUP0_REG_READ_TYPE_DUAL_READ;
    }
    else if (cmdRegDataType == QSPI_SPI_CMD_REG_CMD_SIX_PIN_READ_QUAD)
    {
        localReadType = QSPI_SPI_SETUP0_REG_READ_TYPE_QUAD_READ;
    }
    else
    {
        localReadType = QSPI_SPI_SETUP0_REG_READ_TYPE_NORMAL_READ;
    }
    return localReadType;
}

static uint32_t getNumAddrBytesFromBits(uint32_t numBits)
{
    uint32_t numBytes;
    if (numBits <= 8U)
    {
        numBytes = (uint32_t) 0U;
    }
    else if (numBits <= 16U)
    {
        numBytes = 1U;
    }
    else if (numBits <= 24U)
    {
        numBytes = 2U;
    }
    else if (numBits <= 32U)
    {
        numBytes = 3U;
    }
    else
    {
        numBytes = (uint32_t) 0U;
    }
    return numBytes;
}

static uint32_t getNumDummyBytesFromBits(uint32_t numBits)
{
    uint32_t numBytes;
    if (numBits == 8U)
    {
        numBytes = QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_8_BITS;
    }
    else if (numBits == 16U)
    {
        numBytes = QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_16_BITS;
    }
    else if (numBits == 24U)
    {
        numBytes = QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_24_BITS;
    }
    else
    {
        numBytes = QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_NUM_D_BITS;
    }
    return numBytes;
}

uint32_t QSPI_GetDeviceId(void)
{
    uint32_t deviceId[2U];
    QSPI_GetDeviceIdExtended((uint32_t) 2, &deviceId[0U]);
    return ((uint32_t) ((deviceId[1U] << 16U) | deviceId[0U]));
}

int32_t QSPI_GetDeviceIdExtended(uint32_t numSpiWords, uint32_t *data)
{
    int32_t  retval;
    uint32_t deviceId[QSPI_READ_DEVICEID_MAX_WORDS] = {0};
    if (gQspiFlashDevInfo.idCmd.numDataWords > QSPI_READ_DEVICEID_MAX_WORDS)
    {
        gQspiFlashDevInfo.idCmd.numDataWords = QSPI_READ_DEVICEID_MAX_WORDS;
    }
    /* Always read full id command but return numWords */
    retval = QSPI_executeCmd(gQspiFlashDevInfo.idCmd, &deviceId[0]);
    if (numSpiWords > QSPI_READ_DEVICEID_MAX_WORDS)
    {
        numSpiWords = QSPI_READ_DEVICEID_MAX_WORDS;
    }
    /* Copy the number of data words passed as parameter */
    mem1cpy((void *) data, &deviceId[0], numSpiWords * 4U);
    return retval;
}

static void mem1cpy(void *dstAddr, uint32_t *srcAddr, uint32_t length)
{
    uint32_t  i;
    uint32_t *DAddr = (uint32_t *) (dstAddr);
    uint32_t *SAddr = (uint32_t *) (srcAddr);
    uint8_t  *DAddr_byte, *SAddr_byte;
    void     *DAddr_byteTmp, *SAddr_byteTmp;

    /*Do a word read*/
    for (i = 0U; i < (length / 4U); i++)
    {
        *DAddr = *SAddr;
        DAddr++;
        SAddr++;
    }

    /*Do a byte write*/
    if ((length % 4U) != 0U)
    {
        DAddr_byteTmp = (void *) DAddr;
        SAddr_byteTmp = (void *) SAddr;
        DAddr_byte    = (uint8_t *) DAddr_byteTmp;
        SAddr_byte    = (uint8_t *) SAddr_byteTmp;
        for (i = 0U; i < (length % 4U); ++i)
        {
            *DAddr_byte = *SAddr_byte;
            DAddr_byte++;
            SAddr_byte++;
        }
    }
}

/*_____________________________________________________________________________
 * FUNCTION:     QSPI_ReadSectors
 *
 * DESCRIPTION:  Reads one or several sectors from the QSPI Memory described
 *               in the Device Descriptor.
 *
 * PARAMETERS:   ipDeviceDesc
 *                   Device Descriptor
 *               ipReadDesc
 *                   Indicate where from and how many sectors to read
 *
 * RETURNS:      SUCCESS if the QSPI Device Sector(s) could be read
 *
 *____________________________________________________________________________*/
uint32_t QSPI_ReadSectors(void    *dstAddr,
                          uint32_t srcOffsetAddr,
                          uint32_t length)
{
    uint32_t address = SOC_QSPI_ADDRSP1_BASE + srcOffsetAddr;

    /* Read from QSPI */
    mem1cpy(dstAddr, (uint32_t *) address, length);

    return SUCCESS;
}

void QSPI_ReadSectors_edma(void    *dstAddr,
                           uint32_t srcOffsetAddr,
                           uint32_t length,
                           uint32_t edma_ch_num)
{
    EDMA3CCPaRAMEntry edmaParam;
    uint32_t          bCntValue = 1U;
    uint32_t          remBytes  = 0;
    uint32_t          aCntValue = length;
    uint32_t          addr      = (uint32_t) (dstAddr);
    uint32_t          max_acnt  = 0x7FFFU;
    if (length > max_acnt)
    {
        bCntValue = (length / max_acnt);
        remBytes  = (length % max_acnt);
        aCntValue = max_acnt;
    }

    /* Compute QSPI address and size */
    edmaParam.opt      = 0;
    edmaParam.srcAddr  = SOC_QSPI_ADDRSP1_BASE + srcOffsetAddr;
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
         ((edma_ch_num <<
           EDMA_TPCC_OPT_TCC_SHIFT) &
          EDMA_TPCC_OPT_TCC_MASK) | EDMA_TPCC_OPT_SYNCDIM_MASK);

    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, edma_ch_num, &edmaParam);
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE, edma_ch_num, EDMA3_TRIG_MODE_MANUAL);

    while ((EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE) &
            ((uint32_t) 1U << edma_ch_num)) == 0U)
    {
        /* Do Nothing - Misra fix */
    }
    EDMA3ClrIntr(SOC_EDMA_TPCC_BASE, edma_ch_num);
    if (remBytes != 0)
    {
        /* Compute QSPI address and size */
        edmaParam.opt     = 0;
        edmaParam.srcAddr =
            (SOC_QSPI_ADDRSP1_BASE +
             (bCntValue * max_acnt) + srcOffsetAddr);
        edmaParam.destAddr = (addr + (max_acnt * bCntValue));
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
             ((edma_ch_num << EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK));
        EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, edma_ch_num, &edmaParam);
        EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE, edma_ch_num,
                            EDMA3_TRIG_MODE_MANUAL);

        while ((EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE) &
                ((uint32_t) 1U << edma_ch_num)) == 0U)
        {
            /* Do Nothing - Misra fix */
        }
        EDMA3ClrIntr(SOC_EDMA_TPCC_BASE, edma_ch_num);
    }
}

/*_____________________________________________________________________________
 * FUNCTION:     QSPI_WriteSectors (not implemented)
 *
 * DESCRIPTION:  Writes one or several sectors to the QSPI Memory described
 *               in the Device Descriptor.
 *
 * PARAMETERS:   ipDeviceDesc
 *                   Device Descriptor
 *               ipWriteDesc
 *                   Indicate where to and how many sectors to write
 *
 * RETURNS:      FAIL
 *
 *____________________________________________________________________________*/
/* flash status should be checked before sending next command
 * Bit 0 of Flash status should be 0 indicating flash is not busy
 * Ex: while ((QSPI_FlashStatus() & 0x01)) ; */
uint32_t QSPI_WriteSectorsNonBlocking(uint32_t dstOffsetAddr, uint32_t srcAddr,
                                      uint32_t length)
{
    uint32_t Address;
    /* Compute QSPI address and size */
    Address = SOC_QSPI_ADDRSP1_BASE + dstOffsetAddr;
    /* Read from QSPI */
    mem1cpy((void *) Address, (uint32_t *) srcAddr, length);

    QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);

    QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,QSPI_MMR);

    return SUCCESS;
} /* QSPI_WriteSectors */

uint32_t QSPI_WriteSectors(uint32_t dstOffsetAddr, uint32_t srcAddr,
                           uint32_t length)
{
    uint32_t retVal;
    retVal = QSPI_WriteSectorsNonBlocking(dstOffsetAddr, srcAddr, length);
    /* Wait while Flash is busy */
    while ((QSPI_FlashStatus() & 0x01U) != 0U)
    {
        /* Do Nothing - Misra fix */
    }
    return retVal;
}

void QSPI_ReadCfgMode(uint32_t dstAddr, uint32_t srcOffsetAddr,
                      uint32_t length)
{
    gQspiFlashDevInfo.readCmd.numDataWords = length;
    gQspiFlashDevInfo.readCmd.addr         = srcOffsetAddr;
    QSPI_executeCmd(gQspiFlashDevInfo.readCmd, (uint32_t *) dstAddr);
    gQspiFlashDevInfo.readCmd.numDataWords = 0;
    gQspiFlashDevInfo.readCmd.addr         = 0;
    return;
}

/* flash status should be checked before sending next command
 * Bit 0 of Flash status should be 0 indicating flash is not busy
 * Ex: while ((QSPI_FlashStatus() & 0x01)) ; */
void QSPI_WriteCfgModeNonBlocking(uint32_t dstOffsetAddr, uint32_t srcAddr,
                                  uint32_t length)
{
    gQspiFlashDevInfo.writeCmd.numDataWords = length;
    gQspiFlashDevInfo.writeCmd.addr         = dstOffsetAddr;
    QSPI_executeCmd(gQspiFlashDevInfo.writeCmd, (uint32_t *) srcAddr);
    gQspiFlashDevInfo.writeCmd.numDataWords = 0;
    gQspiFlashDevInfo.writeCmd.addr         = 0;
}

void QSPI_WriteCfgMode(uint32_t dstOffsetAddr, uint32_t srcAddr,
                       uint32_t length)
{
    QSPI_WriteCfgModeNonBlocking(dstOffsetAddr, srcAddr, length);
    /* Wait while Flash is busy */
    while ((QSPI_FlashStatus() & 0x01U) != 0U)
    {
        /* Do Nothing - Misra fix */
    }
}

uint32_t QSPI_FlashStatus(void)
{
    uint32_t data;
    QSPI_executeCmd(gQspiFlashDevInfo.flashStatusCmd, &data);
    return (data & 0xFFU);
}

void QSPI_WriteEnable(void)
{
    QSPI_executeCmd(gQspiFlashDevInfo.writeEnableCmd, NULL);
}

/* flash status should be checked before sending next command
 * Bit 0 of Flash status should be 0 indicating flash is not busy
 * Ex: while ((QSPI_FlashStatus() & 0x01)) ; */
void QSPI_QuadEnableNonBlocking(void)
{
    uint32_t data;
    uint32_t sr1, cr;
    QSPI_WriteEnable();
    HAL_QSPI_Command_reg cmd = {0};
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
    QSPIreadData(SOC_QSPI_ADDRSP0_BASE, &sr1, (int32_t) 1);
    /* Read Command Register */
    data = QSPI_CMD_RDCR;
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
    QSPIreadData(SOC_QSPI_ADDRSP0_BASE, &cr, (int32_t) 1);

    /* Set Configuration register 2nd bit to 1 for Quad enable */
    cr |= 0x2U;
    /* write CR register */
    data = ((uint32_t) QSPI_CMD_WRREG << 16U) | (sr1 << 8U) | cr;
    QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, &data, (int32_t) 1);

    cmd.regFields.frameLength = QSPI_CR_FLEN_1_WORD;
    cmd.regFields.trCmd       = QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE;
    cmd.regFields.wordLength  = QSPI_CR_WLEN_24_BITS;
    QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmd.reg);

    QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
}

void QSPI_QuadEnable(void)
{
    QSPI_QuadEnableNonBlocking();
    /* Wait while Flash is busy */
    while ((QSPI_FlashStatus() & 0x01U) != 0U)
    {
        /* Do Nothing - Misra fix */
    }
}

/* flash status should be checked before sending next command
 * Bit 0 of Flash status should be 0 indicating flash is not busy
 * Ex: while ((QSPI_FlashStatus() & 0x01)) ; */
void QSPI_FlashSubSectorEraseNonBlocking(uint32_t offsetAddr)
{
    gQspiFlashDevInfo.subSectorEraseCmd.numDataWords = 0;
    gQspiFlashDevInfo.subSectorEraseCmd.addr         = offsetAddr;
    QSPI_executeCmd(gQspiFlashDevInfo.subSectorEraseCmd, NULL);
    gQspiFlashDevInfo.subSectorEraseCmd.addr = 0;
}

void QSPI_FlashSubSectorErase(uint32_t offsetAddr)
{
    QSPI_FlashSubSectorEraseNonBlocking(offsetAddr);
    /* Wait while Flash is busy */
    while ((QSPI_FlashStatus() & 0x01U) != 0U)
    {
        /* Do Nothing - Misra fix */
    }
}

/* flash status should be checked before sending next command
 * Bit 0 of Flash status should be 0 indicating flash is not busy
 * Ex: while ((QSPI_FlashStatus() & 0x01)) ; */
void QSPI_FlashBlockEraseNonBlocking(uint32_t blkNo)
{
    gQspiFlashDevInfo.sectorEraseCmd.numDataWords = 0;
    gQspiFlashDevInfo.sectorEraseCmd.addr         = blkNo * QSPIFLASH_BLOCKSIZE;
    QSPI_executeCmd(gQspiFlashDevInfo.sectorEraseCmd, NULL);
    gQspiFlashDevInfo.sectorEraseCmd.addr = 0;
}

void QSPI_FlashBlockErase(uint32_t blkNo)
{
    QSPI_FlashBlockEraseNonBlocking(blkNo);
    /* Wait while Flash is busy */
    while ((QSPI_FlashStatus() & 0x01U) != 0U)
    {
        /* Do Nothing - Misra fix */
    }
}

/* flash status should be checked before sending next command
 * Bit 0 of Flash status should be 0 indicating flash is not busy
 * Ex: while ((QSPI_FlashStatus() & 0x01)) ; */
void QSPI_FlashFullEraseNonBlocking(void)
{
    QSPI_executeCmd(gQspiFlashDevInfo.fullEraseCmd, NULL);
}

void QSPI_FlashFullErase(void)
{
    QSPI_FlashFullEraseNonBlocking();
    /* Wait while Flash is busy */
    while ((QSPI_FlashStatus() & 0x01U) != 0U)
    {
        /* Do Nothing - Misra fix */
    }
}

void QSPI_seek(uint32_t *srcAddr, uint32_t location)
{
    *srcAddr = location;
}

