/**
 *  \file     emif.c
 *
 *  \brief    This file contains the implementation of the APIs present in the
 *            device abstraction layer file of EMIF.
 *            This also contains some related macros.
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
#include <stdio.h>
#include <stdint.h>
#include "common/stw_types.h"
#include "common/stw_dataTypes.h"
#include "hw_types.h"
#include "emif.h"

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

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t EMIFConfigECCInitECCParams(uint32_t               baseAddr,
                                   const emifEccCfgPrm_t *pCfgPrm)
{
    uint32_t startAddr;
    uint32_t endAddr;
    uint32_t emifMsbStartAddr;
    const emifEccAddrRangeCfgPrm_t  *pAddrRangeCfgPrm;
    int32_t  retVal = STW_SOK;

    if ((pCfgPrm == NULL) || (pCfgPrm->addrRangeCfgPrm == NULL))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        pAddrRangeCfgPrm = pCfgPrm->addrRangeCfgPrm;
        emifMsbStartAddr = (pCfgPrm->emifStartAddr >> 16U);

        startAddr =
            (((pAddrRangeCfgPrm->startAddr &
               0xFFFF0000U) >> 16U) - emifMsbStartAddr);
        endAddr =
            (((pAddrRangeCfgPrm->endAddr &
               0xFFFF0000U) >> 16U) - emifMsbStartAddr);

        /*Config EMIF_ECC_ADDR_RANGE_NUM_2*/
        if (pAddrRangeCfgPrm->addrRangeNum == EMIF_ECC_ADDR_RANGE_NUM_2)
        {
            HW_WR_FIELD32(baseAddr + EMIF_ECC_ADDRESS_RANGE_2,
                          EMIF_ECC_ADDRESS_RANGE_2_REG_ECC_STRT_ADDR_2,
                          startAddr);

            HW_WR_FIELD32(baseAddr + EMIF_ECC_ADDRESS_RANGE_2,
                          EMIF_ECC_ADDRESS_RANGE_2_REG_ECC_END_ADDR_2,
                          endAddr);
            /*Enable/Disable ECC address range 2*/
            HW_WR_FIELD32(baseAddr + EMIF_ECC_CTRL_REG,
                          EMIF_ECC_CTRL_REG_REG_ECC_ADDR_RGN_2_EN,
                          pAddrRangeCfgPrm->enableAddrRange);
        }
        else
        {
            /*Config EMIF_ECC_ADDR_RANGE_NUM_1*/
            HW_WR_FIELD32(baseAddr + EMIF_ECC_ADDRESS_RANGE_1,
                          EMIF_ECC_ADDRESS_RANGE_1_REG_ECC_STRT_ADDR_1,
                          startAddr);

            HW_WR_FIELD32(baseAddr + EMIF_ECC_ADDRESS_RANGE_1,
                          EMIF_ECC_ADDRESS_RANGE_1_REG_ECC_END_ADDR_1,
                          endAddr);
            /*Enable/Disable ECC address range 1*/
            HW_WR_FIELD32(baseAddr + EMIF_ECC_CTRL_REG,
                          EMIF_ECC_CTRL_REG_REG_ECC_ADDR_RGN_1_EN,
                          pAddrRangeCfgPrm->enableAddrRange);
        }

        /*Configs EMIF ECC Addr Range is within /Outside defined Addr range*/
        HW_WR_FIELD32(baseAddr + EMIF_ECC_CTRL_REG,
                      EMIF_ECC_CTRL_REG_REG_ECC_ADDR_RGN_PROT,
                      pAddrRangeCfgPrm->addrRangeType);

        /*Configure the thresholds to generate 1-bit error interrupt*/
        HW_WR_FIELD32(baseAddr + EMIF_1B_ECC_ERR_THRSH,
                      EMIF_1B_ECC_ERR_THRSH_REG_1B_ECC_ERR_THRSH,
                      pCfgPrm->thresholdVal);
    }

    return retVal;
}

void EMIFConfigECCEnableEcc(uint32_t baseAddr)
{
    /*Enable EMIF ECC*/
    HW_WR_FIELD32(baseAddr + EMIF_ECC_CTRL_REG,
                  EMIF_ECC_CTRL_REG_REG_ECC_EN,
                  EMIF_ECC_ENABLE);
}

void EMIFConfigECCDisableEcc(uint32_t baseAddr)
{
    /*Disable EMIF ECC*/
    HW_WR_FIELD32(baseAddr + EMIF_ECC_CTRL_REG,
                  EMIF_ECC_CTRL_REG_REG_ECC_EN,
                  EMIF_ECC_DISABLE);
}

void EMIFEnableIntr(uint32_t baseAddr, uint32_t intrMask)
{
    HW_WR_REG32(baseAddr + EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET, intrMask);
}

void EMIFDisableIntr(uint32_t baseAddr, uint32_t intrMask)
{
    HW_WR_REG32(baseAddr + EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR, intrMask);
}

uint32_t EMIFGetIntrStatus(uint32_t baseAddr)
{
    return (HW_RD_REG32(baseAddr + EMIF_SYSTEM_OCP_INTERRUPT_STATUS));
}

void EMIFClearIntrStatus(uint32_t baseAddr, uint32_t intrMask)
{
    HW_WR_REG32(baseAddr + EMIF_SYSTEM_OCP_INTERRUPT_STATUS, intrMask);
}

uint32_t EMIFGetIntrRawStatus(uint32_t baseAddr)
{
    return (HW_RD_REG32(baseAddr + EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS));
}

int32_t EMIFConfigECCGetEccErrInfo(uint32_t          baseAddr,
                                   uint32_t          errType,
                                   emifEccErrInfo_t *pErrInfo)
{
    uint32_t fifoIndex = 0;
    int32_t  retVal    = STW_SOK;

    if (pErrInfo == NULL)
    {
        retVal = STW_EFAIL;
    }
    else
    {
        if ((errType & EMIF_ERR_ECC_ONEBIT) == EMIF_ERR_ECC_ONEBIT)
        {
            /* Reads ECC Err count and clears ECC Err count*/
            pErrInfo->errCnt = HW_RD_REG32(baseAddr + EMIF_1B_ECC_ERR_CNT);
            HW_WR_REG32((baseAddr + EMIF_1B_ECC_ERR_CNT),
                        pErrInfo->errCnt);

            /* Reads ECC Err Bit mask and clears ECC Err Bit mask*/
            pErrInfo->errBitLoc = HW_RD_REG32(baseAddr + EMIF_1B_ECC_ERR_DIST_1);
            HW_WR_REG32((baseAddr + EMIF_1B_ECC_ERR_DIST_1),
                        pErrInfo->errBitLoc);

            if (pErrInfo->errCnt > EMIF_ECC_FIFO_BUF_SIZE)
            {
                /* Address log FIFO Buffer is overflowed*/
                pErrInfo->numValidErrAddr = EMIF_ECC_FIFO_BUF_SIZE;
            }
            else
            {
                pErrInfo->numValidErrAddr = pErrInfo->errCnt;
            }

            while (fifoIndex < pErrInfo->numValidErrAddr)
            {
                /* Reads ECC Err Addr log and clears ECC Err Addr log reg and
                 * Address log Fifo Buffer */
                pErrInfo->errAddr[fifoIndex] =
                    HW_RD_REG32(baseAddr + EMIF_1B_ECC_ERR_ADDR_LOG);
                HW_WR_REG32((baseAddr + EMIF_1B_ECC_ERR_ADDR_LOG), 0x1);
                fifoIndex++;
            }
        }
        else if ((errType & EMIF_ERR_ECC_TWOBIT) == EMIF_ERR_ECC_TWOBIT)
        {
            /* Reads ECC Err Addr log and clears ECC Err Addr log reg and
             * Address log Fifo Buffer */
            pErrInfo->errAddr[fifoIndex] =
                HW_RD_REG32(baseAddr + EMIF_2B_ECC_ERR_ADDR_LOG);
            HW_WR_REG32((baseAddr + EMIF_2B_ECC_ERR_ADDR_LOG), 0x1);
        }
        else
        {
            /* Nothing */
        }
    }

    return retVal;
}

void EMIFConfigECCClrAllEccErrInfo(uint32_t baseAddr)
{
    uint32_t regVal;
    uint32_t errCnt;
    uint32_t numValidErrAddr;

    /* Clears 1Bit ECC Err Info*/
    errCnt = HW_RD_REG32(baseAddr + EMIF_1B_ECC_ERR_CNT);
    HW_WR_REG32((baseAddr + EMIF_1B_ECC_ERR_CNT), errCnt);

    regVal = HW_RD_REG32(baseAddr + EMIF_1B_ECC_ERR_DIST_1);
    HW_WR_REG32((baseAddr + EMIF_1B_ECC_ERR_DIST_1), regVal);

    if (errCnt > EMIF_ECC_FIFO_BUF_SIZE)
    {
        /* Adress log FIFO Buffer is overflowed*/
        numValidErrAddr = EMIF_ECC_FIFO_BUF_SIZE;
    }
    else
    {
        numValidErrAddr = errCnt;
    }

    while (numValidErrAddr)
    {
        regVal = HW_RD_REG32(baseAddr + EMIF_1B_ECC_ERR_ADDR_LOG);
        HW_WR_REG32((baseAddr + EMIF_1B_ECC_ERR_ADDR_LOG), 0x1);
        numValidErrAddr = numValidErrAddr - 1U;
    }

    /* Clears 2Bit ECC Err Info*/
    regVal = HW_RD_REG32(baseAddr + EMIF_2B_ECC_ERR_ADDR_LOG);
    HW_WR_REG32((baseAddr + EMIF_2B_ECC_ERR_ADDR_LOG), 0x1);
}
