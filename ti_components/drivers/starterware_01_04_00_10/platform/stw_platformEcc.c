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
/*
 * \file stw_platformEcc.c
 *
 * \brief  This file contains ECC configurations of DSP Internal memory(L1P& L2)
 *
 */

#include <stdio.h>
#include "stdint.h"
#include "stw_platformEcc.h"
#include <common/stw_types.h>
#include <common/stw_dataTypes.h>
#include "hw_types.h"
#if defined (BUILD_DSP)
#include "soc.h"
#include "hw_dsp_icfg.h"
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

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#if defined (BUILD_DSP)
int32_t ECCDspL2CfgPrm_init(eccDspL2CfgPrm_t *eccDspL2Param)
{
    int32_t retVal = STW_SOK;
    if (NULL == eccDspL2Param)
    {
        retVal = STW_EFAIL;
    }
    else
    {
        /* By default the L2 is configured to be able to perform EDC on
         * all L1D Cache, RAM, L1P Cache, RAM and SDMA accesses.
         */
        eccDspL2Param->l1DCacheReadEccEn = ECC_ENABLE;
        eccDspL2Param->l1PCacheReadEccEn = ECC_ENABLE;
        eccDspL2Param->l1DRamReadEccEn   = ECC_ENABLE;
        eccDspL2Param->l1PRamReadEccEn   = ECC_ENABLE;
        eccDspL2Param->sdmaReadEccEn     = ECC_ENABLE;
    }
    return retVal;
}

int32_t ECCDspL2Configure(const eccDspL2CfgPrm_t *eccDspL2Param)
{
    int32_t retVal = STW_SOK;
    uint32_t regVal = (uint32_t) 0U;

    if (NULL == eccDspL2Param)
    {
        retVal = STW_EFAIL;
    }
    else
    {
        /* Configure the DSP_L2EDCEN register bits based on the input structure
         * Writing 0 makes the feature of EDC disabled for L2.
         */
        regVal =
            (((eccDspL2Param->l1DCacheReadEccEn & 0x1U) <<
              DSP_L2EDCEN_DL2CEN_SHIFT) |
             ((eccDspL2Param->l1PCacheReadEccEn & 0x1U) <<
              DSP_L2EDCEN_PL2CEN_SHIFT) |
             ((eccDspL2Param->l1DRamReadEccEn & 0x1U) <<
              DSP_L2EDCEN_DL2SEN_SHIFT) |
             ((eccDspL2Param->l1PRamReadEccEn & 0x1U) <<
              DSP_L2EDCEN_PL2SEN_SHIFT) |
             ((eccDspL2Param->sdmaReadEccEn & 0x1U) <<
              DSP_L2EDCEN_SDMAEN_SHIFT));
        HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_L2EDCEN, regVal);
    }
    return retVal;
}

int32_t ECCDspEnable(uint32_t memType, uint32_t eccEnable, uint32_t timeout)
{
    int32_t  retVal = STW_SOK;
    uint32_t status;
    uint32_t timeToWait = timeout;
    if (ECC_DSP_MEM_TYPE_L2 == memType)
    {
        switch (eccEnable)
        {
            /* Enable calculating parity for L2 RAM and Cache */
            case ECC_ENABLE:
                HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_L2EDCMD,
                            ((uint32_t) 1U) << DSP_L2EDCMD_EN_SHIFT);
                /* Wait for ECC to be enabled in the status register */
                do
                {
                    status = HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2EDSTAT,
                                           DSP_L2EDSTAT_EN);
                    timeToWait--;
                } while ((0U == status) && (timeToWait > 0));
                if ((0U == status) && (0U == timeToWait))
                {
                    retVal = STW_EFAIL;
                }
                break;
            /* Disable calculating parity for L2 RAM and Cache */
            case ECC_DISABLE:
                HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_L2EDCMD,
                            ((uint32_t) 1U) << DSP_L2EDCMD_DIS_SHIFT);
                /* Wait for ECC to be disabled in the status register */
                do
                {
                    status = HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2EDSTAT,
                                           DSP_L2EDSTAT_DIS);
                    timeToWait--;
                } while ((0U == status) && (timeToWait > 0));
                if ((0U == status) && (0U == timeToWait))
                {
                    retVal = STW_EFAIL;
                }
                break;
            default:
                retVal = STW_EFAIL;
                break;
        }
    }
    else if (ECC_DSP_MEM_TYPE_L1P == memType)
    {
        switch (eccEnable)
        {
            /* Enable calculating parity for L1 Program RAM and Cache */
            case ECC_ENABLE:
                HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_L1PEDCMD,
                            ((uint32_t) 1U) << DSP_L1PEDCMD_EN_SHIFT);
                /* Wait for ECC to be enabled in the status register */
                do
                {
                    status = HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1PEDSTAT,
                                           DSP_L1PEDSTAT_EN);
                    timeToWait--;
                } while ((0U == status) && (timeToWait > 0));
                if ((0U == status) && (0U == timeToWait))
                {
                    retVal = STW_EFAIL;
                }
                break;
            /* Disable calculating parity for L1 Program RAM and Cache */
            case ECC_DISABLE:
                HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_L1PEDCMD,
                            ((uint32_t) 1U) << DSP_L1PEDCMD_DIS_SHIFT);
                /* Wait for ECC to be disabled in the status register */
                do
                {
                    status = HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1PEDSTAT,
                                           DSP_L1PEDSTAT_DIS);
                    timeToWait--;
                } while ((0U == status) && (timeToWait > 0));
                if ((0U == status) && (0U == timeToWait))
                {
                    retVal = STW_EFAIL;
                }
                break;
            default:
                retVal = STW_EFAIL;
                break;
        }
    }
    else
    {
        retVal = STW_EFAIL;
    }
    return retVal;
}

int32_t ECCDspSuspend(uint32_t memType, uint32_t timeout)
{
    int32_t  retVal     = STW_SOK;
    uint32_t status     = 0U;
    uint32_t timeToWait = timeout;
    if (ECC_DSP_MEM_TYPE_L2 == memType)
    {
        /* Suspend ECC for test purpose to inject errors */
        HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_L2EDCMD,
                    ((uint32_t) 1U) << DSP_L2EDCMD_SUSP_SHIFT);
        /* Wait for ECC to be disabled in the status register */
        do
        {
            status = HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2EDSTAT,
                                   DSP_L2EDSTAT_SUSP);
            timeToWait--;
        } while ((0U == status) && (timeToWait > 0));
        if ((0U == status) && (0U == timeToWait))
        {
            retVal = STW_EFAIL;
        }
    }
    else if (ECC_DSP_MEM_TYPE_L1P == memType)
    {
        /* Suspend ECC for test purpose to inject errors */
        HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_L1PEDCMD,
                    ((uint32_t) 1U) << DSP_L1PEDCMD_SUSP_SHIFT);
        /* Wait for ECC to be suspended in the status register */
        do
        {
            status = HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1PEDSTAT,
                                   DSP_L1PEDSTAT_SUSP);
            timeToWait--;
        } while ((0U == status) && (timeToWait > 0));
        if ((0U == status) && (0U == timeToWait))
        {
            retVal = STW_EFAIL;
        }
    }
    else
    {
        retVal = STW_EFAIL;
    }
    return retVal;
}

int32_t ECCDspIntrGetErrStatus(eccDspErrStatus_t *errStatus)
{
    int32_t  retVal   = STW_SOK;
    uint32_t regValL2 = 0U, regValL1 = 0U;
    if (NULL == errStatus)
    {
        retVal = STW_EFAIL;
    }
    else
    {
        regValL2 = HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_L2EDSTAT);
        regValL1 = HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_L1PEDSTAT);
        /* Populate the structure fields based on the read register. 1
         * indicates that the error occurred and 0 indicates that the
         * error did not occur.
         */
        errStatus->l1PProgramFetchErr =
            HW_GET_FIELD(regValL1, DSP_L1PEDSTAT_PERR);
        errStatus->l1PDmaAccessErr =
            HW_GET_FIELD(regValL1, DSP_L1PEDSTAT_DMAERR);
        errStatus->l2L1DAccessErr =
            HW_GET_FIELD(regValL2, DSP_L2EDSTAT_DERR);
        errStatus->l2L1PAccessErr =
            HW_GET_FIELD(regValL2, DSP_L2EDSTAT_PERR);
        errStatus->l2DmaAccessErr =
            HW_GET_FIELD(regValL2, DSP_L2EDSTAT_DMAERR);
        errStatus->l2VictimsErr =
            HW_GET_FIELD(regValL2, DSP_L2EDSTAT_VERR);
    }
    return retVal;
}

int32_t ECCDspIntrClrErrStatus(const eccDspErrStatus_t *errClr)
{
    int32_t retVal = STW_SOK;
    if (NULL == errClr)
    {
        retVal = STW_EFAIL;
    }
    else
    {
        /* Writing 1 clears the bit, writing 0 has no effect */
        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1PEDCMD, DSP_L1PEDCMD_PCLR,
                      errClr->l1PProgramFetchErr);
        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1PEDCMD, DSP_L1PEDCMD_DMACLR,
                      errClr->l1PDmaAccessErr);
        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2EDCMD, DSP_L2EDCMD_DCLR,
                      errClr->l2L1DAccessErr);
        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2EDCMD, DSP_L2EDCMD_PCLR,
                      errClr->l2L1PAccessErr);
        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2EDCMD, DSP_L2EDCMD_DMACLR,
                      errClr->l2DmaAccessErr);
        HW_WR_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2EDCMD, DSP_L2EDCMD_VCLR,
                      errClr->l2VictimsErr);
    }
    return retVal;
}

int32_t ECCDspGetErrInfo(uint32_t memType, eccDspErrInfo_t *eccDspInfo)
{
    int32_t retVal = STW_SOK;
    if (NULL == eccDspInfo)
    {
        retVal = STW_EFAIL;
    }
    else
    {
        if (ECC_DSP_MEM_TYPE_L2 == memType)
        {
            /* Read all the parameters which give further details about the
             * L2 ECC errors.
             * This includes the address, bit position, SEC/DED information,
             * L2 Cache Way number etc.
             */
            eccDspInfo->errAddress =
                HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2EDADDR,
                              DSP_L2EDADDR_ADDR) << DSP_L2EDADDR_ADDR_SHIFT;
            eccDspInfo->errRamOrCache =
                HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2EDADDR,
                              DSP_L2EDADDR_RAM);
            eccDspInfo->errL2BitPosition =
                HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2EDSTAT,
                              DSP_L2EDSTAT_BITPOS);
            eccDspInfo->errL2Type =
                HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2EDSTAT,
                              DSP_L2EDSTAT_NERR);
            eccDspInfo->errL2way =
                HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L2EDADDR,
                              DSP_L2EDADDR_L2WAY);
            eccDspInfo->errL2CorrectableCount =
                HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_L2EDCPEC);
            /* This address is generated as the macro is not defined in the
             * HW header file.
             */
            eccDspInfo->errL2NonCorrectableCount =
                HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_L2EDCPEC + 0x4U);
        }
        else if (ECC_DSP_MEM_TYPE_L1P == memType)
        {
            eccDspInfo->errAddress =
                HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1PEDADDR,
                              DSP_L1PEDADDR_ADDR) << DSP_L1PEDADDR_ADDR_SHIFT;
            eccDspInfo->errRamOrCache =
                HW_RD_FIELD32(SOC_DSP_ICFG_BASE + DSP_L1PEDADDR,
                              DSP_L1PEDADDR_RAM);
            /* The following fields do not exist for L1P ECC so populating
             * them with 0 always.
             */
            eccDspInfo->errL2BitPosition         = 0U;
            eccDspInfo->errL2Type                = 0U;
            eccDspInfo->errL2way                 = 0U;
            eccDspInfo->errL2CorrectableCount    = 0U;
            eccDspInfo->errL2NonCorrectableCount = 0U;
        }
        else
        {
            retVal = STW_EFAIL;
        }
    }
    return retVal;
}

#endif
