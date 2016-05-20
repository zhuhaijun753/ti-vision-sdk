/**
 *  \file     esm.c
 *
 *  \brief    This file contains the implementation of the APIs present in the
 *            device abstraction layer file of ESM.
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
#include <stdint.h>
#include "common/stw_dataTypes.h"
#include "common/stw_types.h"
#include "hw_types.h"
#include "soc_defines.h"
#include "esm.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define ESM_ESMIEPSR(m)            ((uint32_t) ESM_ESMIEPSR1 + \
                                    (((m) / 32U) * 0x40U))
#define ESM_ESMIEPCR(m)            ((uint32_t) ESM_ESMIEPCR1 + \
                                    (((m) / 32U) * 0x40U))
#define ESM_ESMIEPSR_NUM_ELEMS     (4U)
#define ESM_ESMIEPCR_NUM_ELEMS     (4U)
#define ESM_ESMIESR(m)             ((uint32_t) ESM_ESMIESR1 + \
                                    (((m) / 32U) * 0x40U))
#define ESM_ESMIECR(m)             ((uint32_t) ESM_ESMIECR1 + \
                                    (((m) / 32U) * 0x40U))
#define ESM_ESMIESR_NUM_ELEMS      (4U)
#define ESM_ESMIECR_NUM_ELEMS      (4U)
#define ESM_ESMILSR(m)             ((uint32_t) ESM_ESMILSR1 + \
                                    (((m) / 32U) * 0x40U))
#define ESM_ESMILCR(m)             ((uint32_t) ESM_ESMILCR1 + \
                                    (((m) / 32U) * 0x40U))
#define ESM_ESMILSR_NUM_ELEMS      (4U)
#define ESM_ESMILCR_NUM_ELEMS      (4U)
#define ESM_ESMSR(m)               ((uint32_t) ESM_ESMSR1 + \
                                    (((m) / 32U) * 0x40U))
#define ESM_ESMSR_NUM_ELEMS        (4U)

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
void ESMSetMode(uint32_t baseAddr, uint32_t mode)
{
    HW_WR_FIELD32(baseAddr + ESM_ESMEKR, ESM_ESMEKR_EKEY, mode);
}

void ESMSetInfluenceOnErrPin(uint32_t baseAddr, uint32_t intrSrc,
                             uint32_t influence)
{
    uint32_t regVal;

    if ((uint32_t) TRUE == influence)
    {
        regVal  = HW_RD_REG32(baseAddr + ESM_ESMIEPSR(intrSrc));
        regVal &= ~((uint32_t) TRUE << (intrSrc % 32U));
        regVal |= ((uint32_t) 0x1U << (intrSrc % 32U));
        HW_WR_REG32(baseAddr + ESM_ESMIEPSR(intrSrc), regVal);
    }
    else
    {
        regVal  = HW_RD_REG32(baseAddr + ESM_ESMIEPCR(intrSrc));
        regVal &= ~((uint32_t) TRUE << (intrSrc % 32U));
        regVal |= ((uint32_t) TRUE << (intrSrc % 32U));
        HW_WR_REG32(baseAddr + ESM_ESMIEPCR(intrSrc), regVal);
    }
}

int32_t ESMSetErrPinLowTimePreload(uint32_t baseAddr, uint32_t lowTime)
{
    int32_t status = STW_EFAIL;

    if (ESM_ESMLTCPR_LTCPR_MAX >= lowTime)
    {
        HW_WR_FIELD32(baseAddr + ESM_ESMLTCPR, ESM_ESMLTCPR_LTCPR, lowTime);
        status = STW_SOK;
    }
    return status;
}

uint32_t ESMGetCurrErrPinLowTimeCnt(uint32_t baseAddr)
{
    return HW_RD_FIELD32(baseAddr + ESM_ESMLTCR, ESM_ESMLTCR_LTC);
}

uint32_t ESMGetErrPinStatus(uint32_t baseAddr)
{
    return HW_RD_FIELD32(baseAddr + ESM_ESMEPSR, ESM_ESMEPSR_EPSF);
}

void ESMResetErrPin(uint32_t baseAddr)
{
    HW_WR_FIELD32(baseAddr + ESM_ESMEKR, ESM_ESMEKR_EKEY,
                  ESM_ESMEKR_EKEY_ERROR_PIN_RESET);
}

void ESMEnableIntr(uint32_t baseAddr, uint32_t intrSrc)
{
    uint32_t regVal;

    regVal  = HW_RD_REG32(baseAddr + ESM_ESMIESR(intrSrc));
    regVal &= ~((uint32_t) TRUE << (intrSrc % 32U));
    regVal |= ((uint32_t) TRUE << (intrSrc % 32U));
    HW_WR_REG32(baseAddr + ESM_ESMIESR(intrSrc), regVal);
}

void ESMDisableIntr(uint32_t baseAddr, uint32_t intrSrc)
{
    uint32_t regVal;

    regVal  = HW_RD_REG32(baseAddr + ESM_ESMIECR(intrSrc));
    regVal &= ~((uint32_t) TRUE << (intrSrc % 32U));
    regVal |= ((uint32_t) TRUE << (intrSrc % 32U));
    HW_WR_REG32(baseAddr + ESM_ESMIECR(intrSrc), regVal);
}

void ESMSetIntrPriorityLvl(uint32_t baseAddr, uint32_t intrSrc,
                           uint32_t intrPriorityLvl)
{
    uint32_t regVal;

    if (ESM_INTR_PRIORITY_LEVEL_LOW == intrPriorityLvl)
    {
        regVal  = HW_RD_REG32(baseAddr + ESM_ESMILCR(intrSrc));
        regVal &= ~((uint32_t) TRUE << (intrSrc % 32U));
        regVal |= ((uint32_t) TRUE << (intrSrc % 32U));
        HW_WR_REG32(baseAddr + ESM_ESMILCR(intrSrc), regVal);
    }
    else
    {
        regVal  = HW_RD_REG32(baseAddr + ESM_ESMILSR(intrSrc));
        regVal &= ~((uint32_t) TRUE << (intrSrc % 32U));
        regVal |= ((uint32_t) TRUE << (intrSrc % 32U));
        HW_WR_REG32(baseAddr + ESM_ESMILSR(intrSrc), regVal);
    }
}

uint32_t ESMGetIntrStatus(uint32_t baseAddr, uint32_t intrSrc)
{
    uint32_t regVal;

    regVal  = HW_RD_REG32(baseAddr + ESM_ESMSR(intrSrc));
    regVal &= ((uint32_t) TRUE << (intrSrc % 32U));
    regVal  = (regVal >> (intrSrc % 32U));
    return regVal;
}

int32_t ESMGetGroupIntrStatus(uint32_t baseAddr, uint32_t grpNum,
                              esmGroupIntrStatus_t *intrstatus)
{
    int32_t  status  = STW_EFAIL;
    uint32_t loopCnt = 0;

    if (ESM_NUM_GROUP_MAX < grpNum)
    {
        status = STW_EFAIL;
    }
    else
    {
        switch (grpNum)
        {
            case 1U:
                for (loopCnt = 0; loopCnt < ESM_ESMSR_NUM_ELEMS; loopCnt++)
                {
                    intrstatus->grpIntrStatus[loopCnt] =
                        HW_RD_REG32(baseAddr + ESM_ESMSR(loopCnt * 32U));
                }
                status = STW_SOK;
                break;
            default:
                status = STW_EFAIL;
                break;
        }
    }
    return status;
}

void ESMClearIntrStatus(uint32_t baseAddr, uint32_t intrSrc)
{
    uint32_t regVal = 0U;

    regVal = ((uint32_t) TRUE << (intrSrc % 32U));
    HW_WR_REG32(baseAddr + ESM_ESMSR(intrSrc), regVal);
}

uint32_t ESMGetHighPriorityLvlIntrStatus(uint32_t baseAddr)
{
    return HW_RD_FIELD32(baseAddr + ESM_ESMIOFFHR, ESM_ESMIOFFHR_INTOFFH);
}

uint32_t ESMGetLowPriorityLvlIntrStatus(uint32_t baseAddr)
{
    return HW_RD_FIELD32(baseAddr + ESM_ESMIOFFLR, ESM_ESMIOFFLR_INTOFFL);
}

