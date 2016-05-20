/**
 *  \file     crc.c
 *
 *  \brief    This file contains the implementation of the APIs present in the
 *            device abstraction layer file of CRC.
 *            This also contains some related macros.
 *
 *  \copyright Copyright (C) 2014 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

/* ======================================================================
 *   Copyright (C) 2014 Texas Instruments Incorporated
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
#include "common/stw_types.h"
#include "hw_types.h"
#include "hw_crc.h"
#include "crc.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define CRC_PATTERN_COUNT_MAX          (0x000FFFFFU)
#define CRC_SECTOR_COUNT_MAX           (0x0000FFFFU)

#define CRC_BCTOPLD_MAX                (0x00FFFFFFU)
#define CRC_WDTOPLD_MAX                (0x00FFFFFFU)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t CRCInitialize(uint32_t baseAddr,
                      uint32_t channel,
                      uint32_t crcWatchdogPreload,
                      uint32_t crcBlockPreload)
{
    int32_t crcConfigStatus = STW_EFAIL;

    if ((CRC_WDTOPLD_MAX > crcWatchdogPreload) &&
        (CRC_BCTOPLD_MAX > crcBlockPreload))
    {
        switch (channel)
        {
            case CRC_CHANNEL_1:
                /* Configure watchdog preload value */
                HW_WR_FIELD32(baseAddr + CRC_WDTOPLD1,
                              CRC_WDTOPLD1,
                              crcWatchdogPreload);
                /* Configure clock preload value */
                HW_WR_FIELD32(baseAddr + CRC_BCTOPLD1,
                              CRC_BCTOPLD1,
                              crcBlockPreload);
                break;
            case CRC_CHANNEL_2:
                /* Configure watchdog preload value */
                HW_WR_FIELD32(baseAddr + CRC_WDTOPLD2,
                              CRC_WDTOPLD2,
                              crcWatchdogPreload);
                /* Configure clock preload value */
                HW_WR_FIELD32(baseAddr + CRC_BCTOPLD2,
                              CRC_BCTOPLD2,
                              crcBlockPreload);
                break;
            case CRC_CHANNEL_3:
                /* Configure watchdog preload value */
                HW_WR_FIELD32(baseAddr + CRC_WDTOPLD3,
                              CRC_WDTOPLD3,
                              crcWatchdogPreload);
                /* Configure clock preload value */
                HW_WR_FIELD32(baseAddr + CRC_BCTOPLD3,
                              CRC_BCTOPLD3,
                              crcBlockPreload);
                break;
            case CRC_CHANNEL_4:
                /* Configure watchdog preload value */
                HW_WR_FIELD32(baseAddr + CRC_WDTOPLD4,
                              CRC_WDTOPLD4,
                              crcWatchdogPreload);
                /* Configure clock preload value */
                HW_WR_FIELD32(baseAddr + CRC_BCTOPLD4,
                              CRC_BCTOPLD4,
                              crcBlockPreload);
                break;
            default:
                break;
        }
        crcConfigStatus = STW_SOK;
    }
    else
    {
        crcConfigStatus = STW_EFAIL;
    }
    return crcConfigStatus;
}

int32_t CRCConfigure(uint32_t baseAddr,
                     uint32_t channel,
                     uint32_t crcPatternCount,
                     uint32_t crcSectorCount,
                     uint32_t crcMode)
{
    int32_t crcInitStatus = STW_EFAIL;

    if ((CRC_PATTERN_COUNT_MAX > crcPatternCount) &&
        (CRC_SECTOR_COUNT_MAX > crcSectorCount))
    {
        switch (channel)
        {
            case CRC_CHANNEL_1:
                /* Configure CRC pattern count */
                HW_WR_FIELD32(baseAddr + CRC_PCOUNT_REG1,
                              CRC_PCOUNT_REG1_PAT_COUNT1,
                              crcPatternCount);
                /* Configure CRC sector count */
                HW_WR_FIELD32(baseAddr + CRC_SCOUNT_REG1,
                              CRC_SCOUNT_REG1_SEC_COUNT1,
                              crcSectorCount);
                /* Configure CRC operation mode */
                HW_WR_FIELD32(baseAddr + CRC_CTRL2,
                              CRC_CTRL2_CH1_MODE,
                              crcMode);
                break;
            case CRC_CHANNEL_2:
                /* Configure CRC pattern count */
                HW_WR_FIELD32(baseAddr + CRC_PCOUNT_REG2,
                              CRC_PCOUNT_REG2_PAT_COUNT2,
                              crcPatternCount);
                /* Configure CRC sector count */
                HW_WR_FIELD32(baseAddr + CRC_SCOUNT_REG2,
                              CRC_SCOUNT_REG2_SEC_COUNT2,
                              crcSectorCount);
                /* Configure CRC operation mode */
                HW_WR_FIELD32(baseAddr + CRC_CTRL2,
                              CRC_CTRL2_CH2_MODE,
                              crcMode);
                break;
            case CRC_CHANNEL_3:
                /* Configure CRC pattern count */
                HW_WR_FIELD32(baseAddr + CRC_PCOUNT_REG3,
                              CRC_PCOUNT_REG3_PAT_COUNT3,
                              crcPatternCount);
                /* Configure CRC sector count */
                HW_WR_FIELD32(baseAddr + CRC_SCOUNT_REG3,
                              CRC_SCOUNT_REG3_SEC_COUNT3,
                              crcSectorCount);
                /* Configure CRC operation mode */
                HW_WR_FIELD32(baseAddr + CRC_CTRL2,
                              CRC_CTRL2_CH3_MODE,
                              crcMode);
                break;
            case CRC_CHANNEL_4:
                /* Configure CRC pattern count */
                HW_WR_FIELD32(baseAddr + CRC_PCOUNT_REG4,
                              CRC_PCOUNT_REG4_PAT_COUNT4,
                              crcPatternCount);
                /* Configure CRC sector count */
                HW_WR_FIELD32(baseAddr + CRC_SCOUNT_REG4,
                              CRC_SCOUNT_REG4_SEC_COUNT4,
                              crcSectorCount);
                /* Configure CRC operation mode */
                HW_WR_FIELD32(baseAddr + CRC_CTRL2,
                              CRC_CTRL2_CH4_MODE,
                              crcMode);
                break;
            default:
                break;
        }
        crcInitStatus = STW_SOK;
    }
    else
    {
        crcInitStatus = STW_EFAIL;
    }
    return crcInitStatus;
}

void CRCChannelReset(uint32_t baseAddr, uint32_t channel)
{
    switch (channel)
    {
        case CRC_CHANNEL_1:
            HW_WR_FIELD32(baseAddr + CRC_CTRL0,
                          CRC_CTRL0_CH1_PSA_SWRE,
                          CRC_CTRL0_CH1_PSA_SWRE_ON);
            HW_WR_FIELD32(baseAddr + CRC_CTRL0,
                          CRC_CTRL0_CH1_PSA_SWRE,
                          CRC_CTRL0_CH1_PSA_SWRE_OFF);
            break;
        case CRC_CHANNEL_2:
            HW_WR_FIELD32(baseAddr + CRC_CTRL0,
                          CRC_CTRL0_CH2_PSA_SWRE,
                          CRC_CTRL0_CH2_PSA_SWRE_ON);
            HW_WR_FIELD32(baseAddr + CRC_CTRL0,
                          CRC_CTRL0_CH2_PSA_SWRE,
                          CRC_CTRL0_CH2_PSA_SWRE_OFF);
            break;
        case CRC_CHANNEL_3:
            HW_WR_FIELD32(baseAddr + CRC_CTRL0,
                          CRC_CTRL0_CH3_PSA_SWRE,
                          CRC_CTRL0_CH3_PSA_SWRE_ON);
            HW_WR_FIELD32(baseAddr + CRC_CTRL0,
                          CRC_CTRL0_CH3_PSA_SWRE,
                          CRC_CTRL0_CH3_PSA_SWRE_OFF);
            break;
        case CRC_CHANNEL_4:
            HW_WR_FIELD32(baseAddr + CRC_CTRL0,
                          CRC_CTRL0_CH4_PSA_SWRE,
                          CRC_CTRL0_CH4_PSA_SWRE_ON);
            HW_WR_FIELD32(baseAddr + CRC_CTRL0,
                          CRC_CTRL0_CH4_PSA_SWRE,
                          CRC_CTRL0_CH4_PSA_SWRE_OFF);
            break;
        default:
            break;
    }
}

void CRCGetPSASigRegAddr(uint32_t               baseAddr,
                         uint32_t               channel,
                         crcSignatureRegAddr_t *crcRegAddr)
{
    switch (channel)
    {
        case CRC_CHANNEL_1:
            crcRegAddr->regH = (baseAddr + CRC_PSA_SIGREGH1);
            crcRegAddr->regL = (baseAddr + CRC_PSA_SIGREGL1);
            break;
        case CRC_CHANNEL_2:
            crcRegAddr->regH = (baseAddr + CRC_PSA_SIGREGH2);
            crcRegAddr->regL = (baseAddr + CRC_PSA_SIGREGL2);
            break;
        case CRC_CHANNEL_3:
            crcRegAddr->regH = (baseAddr + CRC_PSA_SIGREGH3);
            crcRegAddr->regL = (baseAddr + CRC_PSA_SIGREGL3);
            break;
        case CRC_CHANNEL_4:
            crcRegAddr->regH = (baseAddr + CRC_PSA_SIGREGH4);
            crcRegAddr->regL = (baseAddr + CRC_PSA_SIGREGL4);
            break;
        default:
            crcRegAddr->regH = 0U;
            crcRegAddr->regL = 0U;
            break;
    }
}

void CRCGetPSASig(uint32_t        baseAddr,
                  uint32_t        channel,
                  crcSignature_t *crcPSASign)
{
    switch (channel)
    {
        case CRC_CHANNEL_1:
            crcPSASign->regH = HW_RD_REG32(baseAddr + CRC_PSA_SIGREGH1);
            crcPSASign->regL = HW_RD_REG32(baseAddr + CRC_PSA_SIGREGL1);
            break;
        case CRC_CHANNEL_2:
            crcPSASign->regH = HW_RD_REG32(baseAddr + CRC_PSA_SIGREGH2);
            crcPSASign->regL = HW_RD_REG32(baseAddr + CRC_PSA_SIGREGL2);
            break;
        case CRC_CHANNEL_3:
            crcPSASign->regH = HW_RD_REG32(baseAddr + CRC_PSA_SIGREGH3);
            crcPSASign->regL = HW_RD_REG32(baseAddr + CRC_PSA_SIGREGL3);
            break;
        case CRC_CHANNEL_4:
            crcPSASign->regH = HW_RD_REG32(baseAddr + CRC_PSA_SIGREGH4);
            crcPSASign->regL = HW_RD_REG32(baseAddr + CRC_PSA_SIGREGL4);
            break;
        default:
            crcPSASign->regH = 0U;
            crcPSASign->regL = 0U;
            break;
    }
}

void CRCSetPSASeedSig(uint32_t              baseAddr,
                      uint32_t              channel,
                      const crcSignature_t *crcPSASeedSign)
{
    switch (channel)
    {
        case CRC_CHANNEL_1:
            /* Configure CRC operation mode */
            HW_WR_FIELD32(baseAddr + CRC_CTRL2,
                          CRC_CTRL2_CH1_MODE,
                          CRC_CTRL2_CH1_MODE_DATA);
            HW_WR_REG32(baseAddr + CRC_PSA_SIGREGH1, crcPSASeedSign->regH);
            HW_WR_REG32(baseAddr + CRC_PSA_SIGREGL1, crcPSASeedSign->regL);
            break;
        case CRC_CHANNEL_2:
            /* Configure CRC operation mode */
            HW_WR_FIELD32(baseAddr + CRC_CTRL2,
                          CRC_CTRL2_CH2_MODE,
                          CRC_CTRL2_CH2_MODE_DATA);
            HW_WR_REG32(baseAddr + CRC_PSA_SIGREGH2, crcPSASeedSign->regH);
            HW_WR_REG32(baseAddr + CRC_PSA_SIGREGL2, crcPSASeedSign->regL);
            break;
        case CRC_CHANNEL_3:
            /* Configure CRC operation mode */
            HW_WR_FIELD32(baseAddr + CRC_CTRL2,
                          CRC_CTRL2_CH3_MODE,
                          CRC_CTRL2_CH3_MODE_DATA);
            HW_WR_REG32(baseAddr + CRC_PSA_SIGREGH3, crcPSASeedSign->regH);
            HW_WR_REG32(baseAddr + CRC_PSA_SIGREGL3, crcPSASeedSign->regL);
            break;
        case CRC_CHANNEL_4:
            /* Configure CRC operation mode */
            HW_WR_FIELD32(baseAddr + CRC_CTRL2,
                          CRC_CTRL2_CH4_MODE,
                          CRC_CTRL2_CH4_MODE_DATA);
            HW_WR_REG32(baseAddr + CRC_PSA_SIGREGH4, crcPSASeedSign->regH);
            HW_WR_REG32(baseAddr + CRC_PSA_SIGREGL4, crcPSASeedSign->regL);
            break;
        default:
            /* To remove MISRA C Error */
            break;
    }
}

void CRCGetPSASectorSig(uint32_t        baseAddr,
                        uint32_t        channel,
                        crcSignature_t *crcSectorSign)
{
    switch (channel)
    {
        case CRC_CHANNEL_1:
            crcSectorSign->regH = HW_RD_REG32(baseAddr + CRC_PSA_SECSIGREGH1);
            crcSectorSign->regL = HW_RD_REG32(baseAddr + CRC_PSA_SECSIGREGL1);
            break;
        case CRC_CHANNEL_2:
            crcSectorSign->regH = HW_RD_REG32(baseAddr + CRC_PSA_SECSIGREGH2);
            crcSectorSign->regL = HW_RD_REG32(baseAddr + CRC_PSA_SECSIGREGL2);
            break;
        case CRC_CHANNEL_3:
            crcSectorSign->regH = HW_RD_REG32(baseAddr + CRC_PSA_SECSIGREGH3);
            crcSectorSign->regL = HW_RD_REG32(baseAddr + CRC_PSA_SECSIGREGL3);
            break;
        case CRC_CHANNEL_4:
            crcSectorSign->regH = HW_RD_REG32(baseAddr + CRC_PSA_SECSIGREGH4);
            crcSectorSign->regL = HW_RD_REG32(baseAddr + CRC_PSA_SECSIGREGL4);
            break;
        default:
            crcSectorSign->regH = 0U;
            crcSectorSign->regL = 0U;
            break;
    }
}

uint32_t CRCGetHighestPriorityIntrStatus(uint32_t baseAddr)
{
    return HW_RD_FIELD32(baseAddr + CRC_INT_OFFSET_REG, CRC_INT_OFFSET_REG);
}

uint32_t CRCGetIntrStatus(uint32_t baseAddr, uint32_t channel)
{
    uint32_t intVal = 0x0U;

    intVal = HW_RD_REG32(baseAddr + CRC_STATUS);
    switch (channel)
    {
        case CRC_CHANNEL_1:
            intVal = intVal & (CRC_CHANNEL_IRQSTATUS_RAW_MAIN_ALL <<
                               CRC_STATUS_CH1_CCIT_SHIFT);
            break;
        case CRC_CHANNEL_2:
            intVal = intVal & (CRC_CHANNEL_IRQSTATUS_RAW_MAIN_ALL <<
                               CRC_STATUS_CH2_CCIT_SHIFT);
            break;
        case CRC_CHANNEL_3:
            intVal = intVal & (CRC_CHANNEL_IRQSTATUS_RAW_MAIN_ALL <<
                               CRC_STATUS_CH3_CCIT_SHIFT);
            break;
        case CRC_CHANNEL_4:
            intVal = intVal & (CRC_CHANNEL_IRQSTATUS_RAW_MAIN_ALL <<
                               CRC_STATUS_CH4_CCIT_SHIFT);
            break;
        default:
            break;
    }
    return intVal;
}

void CRCEnableIntr(uint32_t baseAddr,
                   uint32_t channel,
                   uint32_t intrMask)
{
    uint32_t intVal = 0U;

    intVal = HW_RD_REG32(baseAddr + CRC_INTS);
    switch (channel)
    {
        case CRC_CHANNEL_1:
            intVal = intVal & (intrMask << CRC_INTS_CH1_CCITENS_SHIFT);
            break;
        case CRC_CHANNEL_2:
            intVal = intVal & (intrMask << CRC_INTS_CH2_CCITENS_SHIFT);
            break;
        case CRC_CHANNEL_3:
            intVal = intVal & (intrMask << CRC_INTS_CH3_CCITENS_SHIFT);
            break;
        case CRC_CHANNEL_4:
            intVal = intVal & (intrMask << CRC_INTS_CH4_CCITENS_SHIFT);
            break;
        default:
            break;
    }
    HW_WR_REG32(baseAddr + CRC_INTS, intVal);
}

void CRCDisableIntr(uint32_t baseAddr,
                    uint32_t channel,
                    uint32_t intrMask)
{
    uint32_t intVal = 0U;

    intVal = HW_RD_REG32(baseAddr + CRC_INTR);
    switch (channel)
    {
        case CRC_CHANNEL_1:
            intVal = intVal & (intrMask << CRC_INTR_CH1_CCITENR_SHIFT);
            break;
        case CRC_CHANNEL_2:
            intVal = intVal & (intrMask << CRC_INTR_CH2_CCITENR_SHIFT);
            break;
        case CRC_CHANNEL_3:
            intVal = intVal & (intrMask << CRC_INTR_CH3_CCITENR_SHIFT);
            break;
        case CRC_CHANNEL_4:
            intVal = intVal & (intrMask << CRC_INTR_CH4_CCITENR_SHIFT);
            break;
        default:
            break;
    }
    HW_WR_REG32(baseAddr + CRC_INTR, intVal);
}

void CRCClearIntr(uint32_t baseAddr,
                  uint32_t channel,
                  uint32_t intrMask
                  )
{
    uint32_t intVal = 0U;

    intVal = HW_RD_REG32(baseAddr + CRC_STATUS);
    switch (channel)
    {
        case CRC_CHANNEL_1:
            intVal = intVal & (intrMask << CRC_STATUS_CH1_CCIT_SHIFT);
            break;
        case CRC_CHANNEL_2:
            intVal = intVal & (intrMask << CRC_STATUS_CH2_CCIT_SHIFT);
            break;
        case CRC_CHANNEL_3:
            intVal = intVal & (intrMask << CRC_STATUS_CH3_CCIT_SHIFT);
            break;
        case CRC_CHANNEL_4:
            intVal = intVal & (intrMask << CRC_STATUS_CH4_CCIT_SHIFT);
            break;
        default:
            break;
    }
    HW_WR_REG32(baseAddr + CRC_STATUS, intVal);
}

