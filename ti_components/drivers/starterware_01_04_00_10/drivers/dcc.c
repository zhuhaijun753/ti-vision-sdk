/**
 *  \file     dcc.c
 *
 *  \brief    This file contains the implementation of the APIs present in the
 *            device abstraction layer file of DCC.
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
#include "common/stw_types.h"
#include "common/stw_dataTypes.h"
#include "hw_types.h"
#include "hw_dcc.h"
#include "soc_defines.h"
#include "dcc.h"

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

int32_t DCCSetConfig(uint32_t baseAddr, const dccConfigParams_t *configParams)
{
    int32_t status = STW_EFAIL;
    if ((DCC_SRC0_COUNT_MAX >= configParams->seedSrc0) &&
        (DCC_SRC0_VALID_MAX >= configParams->seedValid0) &&
        (DCC_SRC1_COUNT_MAX >= configParams->seedSrc1))
    {
        /* Configure DCC mode of operation */
        HW_WR_FIELD32(baseAddr + DCC_DCCGCTRL, DCC_DCCGCTRL_SINGLESHOT,
                      configParams->mode);
        /* Select clock source for COUNT0 */
        HW_WR_FIELD32(baseAddr + DCC_DCCCLKSRC0, DCC_DCCCLKSRC0_CLKSRC0,
                      configParams->clkSrc0);

        /* Select clock source for COUNT1*/
        HW_WR_FIELD32(baseAddr + DCC_DCCCLKSRC1, DCC_DCCCLKSRC1_CLKSRC,
                      (configParams->clkSrc1 % 16));
        /* Enable clock source selection for COUNT1 */
        HW_WR_FIELD32(baseAddr + DCC_DCCCLKSRC1, DCC_DCCCLKSRC1_KEY,
                      DCC_DCCCLKSRC1_KEY_ENABLE);
        /* Configure COUNT0 preload/seed value */
        HW_WR_FIELD32(baseAddr + DCC_DCCCNTSEED0, DCC_DCCCNT0_COUNT0,
                      configParams->seedSrc0);
        /* Configure VALID0 preload/seed value */
        HW_WR_FIELD32(baseAddr + DCC_DCCVALIDSEED0, DCC_DCCVALID0_VALID0,
                      configParams->seedValid0);
        /* Configure COUNT1 preload/seed value */
        HW_WR_FIELD32(baseAddr + DCC_DCCCNTSEED1, DCC_DCCCNT1_COUNT1,
                      configParams->seedSrc1);
        status = STW_SOK;
    }
    else
    {
        status = STW_EFAIL;
    }
    return status;
}

void DCCEnable(uint32_t baseAddr, uint32_t enable)
{
    if ((uint32_t) TRUE == enable)
    {
        /* Enable DCC */
        HW_WR_FIELD32(baseAddr + DCC_DCCGCTRL, DCC_DCCGCTRL_DCCENA,
                      DCC_DCCGCTRL_DCCENA_ENABLE);
    }
    else
    {
        /* Disable DCC */
        HW_WR_FIELD32(baseAddr + DCC_DCCGCTRL, DCC_DCCGCTRL_DCCENA,
                      DCC_DCCGCTRL_DCCENA_DISABLE);
    }
}

int32_t DCCEnableIntr(uint32_t baseAddr, uint32_t intrType)
{
    int32_t status = STW_EFAIL;
    switch (intrType)
    {
        case DCC_INTERRUPTS_ERROR:
            /* Enable ERROR interrupt */
            HW_WR_FIELD32(baseAddr + DCC_DCCGCTRL, DCC_DCCGCTRL_ERRENA,
                          DCC_DCCGCTRL_ERRENA_ENABLE);
            status = STW_SOK;
            break;
        case DCC_INTERRUPTS_DONE:
            /* Enable DONE interrupt(only for single shot mode) */
            HW_WR_FIELD32(baseAddr + DCC_DCCGCTRL, DCC_DCCGCTRL_DONEENA,
                          DCC_DCCGCTRL_DONEENA_ENABLE);
            status = STW_SOK;
            break;
        default:
            status = STW_EBADARGS;
            break;
    }
    return status;
}

int32_t DCCDisableIntr(uint32_t baseAddr, uint32_t intrType)
{
    int32_t status = STW_EFAIL;
    switch (intrType)
    {
        case DCC_INTERRUPTS_ERROR:
            /* Disable ERROR interrupt */
            HW_WR_FIELD32(baseAddr + DCC_DCCGCTRL, DCC_DCCGCTRL_ERRENA,
                          DCC_DCCGCTRL_ERRENA_DISABLE);
            status = STW_SOK;
            break;
        case DCC_INTERRUPTS_DONE:
            /* Disable DONE interrupt(only for single shot mode) */
            HW_WR_FIELD32(baseAddr + DCC_DCCGCTRL, DCC_DCCGCTRL_DONEENA,
                          DCC_DCCGCTRL_DONEENA_DISABLE);
            status = STW_SOK;
            break;
        default:
            status = STW_EBADARGS;
            break;
    }
    return status;
}

uint32_t DCCGetIntrStatus(uint32_t baseAddr)
{
    /* Read and return DCC status register */
    return (HW_RD_REG32(baseAddr + DCC_DCCSTAT));
}

void DCCClearIntrStatus(uint32_t baseAddr, uint32_t intrMask)
{
    /* Clear status of given interrupt */
    HW_WR_REG32(baseAddr + DCC_DCCSTAT, ((uint32_t) 0x1U << intrMask));
}

void DCCGetConfig(uint32_t baseAddr, dccConfigParams_t *configParams)
{
    /* Get the configured mode of operation for DCC module */
    configParams->mode = HW_RD_FIELD32(baseAddr + DCC_DCCGCTRL,
                                       DCC_DCCGCTRL_SINGLESHOT);
    /* Get the clock source for COUNT0 */
    configParams->clkSrc0 = HW_RD_FIELD32(baseAddr + DCC_DCCCLKSRC0,
                                          DCC_DCCCLKSRC0_CLKSRC0);
    /* Get the clock source for COUNT1 */
    configParams->clkSrc1 = HW_RD_FIELD32(baseAddr + DCC_DCCCLKSRC1,
                                          DCC_DCCCLKSRC1_CLKSRC);
    /* Get the current value of COUNT0 */
    configParams->seedSrc0 = HW_RD_FIELD32(baseAddr + DCC_DCCCNTSEED0,
                                           DCC_DCCCNT0_COUNT0);
    /* Get the current value of VALID0 */
    configParams->seedValid0 = HW_RD_FIELD32(baseAddr + DCC_DCCVALIDSEED0,
                                             DCC_DCCVALID0_VALID0);
    /* Get the current value of COUNT1 */
    configParams->seedSrc1 = HW_RD_FIELD32(baseAddr + DCC_DCCCNTSEED1,
                                           DCC_DCCCNT1_COUNT1);
}

void DCCGetRevisionId(uint32_t baseAddr, dccRevisionId_t *revId)
{
    /* Get the scheme */
    revId->scheme = HW_RD_FIELD32(baseAddr + DCC_DCCREV, DCC_DCCREV_SCHEME);
    /* Get the Functional release number*/
    revId->func = HW_RD_FIELD32(baseAddr + DCC_DCCREV, DCC_DCCREV_FUNC);
    /* Get the Design Release Number */
    revId->rtlReleaseNum = HW_RD_FIELD32(baseAddr + DCC_DCCREV, DCC_DCCREV_RTL);
    /* Get the Major Revision Number */
    revId->major = HW_RD_FIELD32(baseAddr + DCC_DCCREV, DCC_DCCREV_MAJOR);
    /* Get a special version of the module */
    revId->custom = HW_RD_FIELD32(baseAddr + DCC_DCCREV, DCC_DCCREV_CUSTOM);
    /* Get the Minor revision number */
    revId->minor = HW_RD_FIELD32(baseAddr + DCC_DCCREV, DCC_DCCREV_MINOR);
}

