/**
 *  \file   arp32_wugen.c
 *
 *  \brief  EVE Wake up Generator related APIs.
 *
 *   This file contains the APIs for configuring ARP32 WUGEN
 *
 *  \copyright Copyright (C) 2014 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

/* =============================================================================
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
 * ===========================================================================*/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "stdint.h"
#include "hw_types.h"
#include "soc.h"
#include "hw_eve_control.h"
#include "arp32_wugen.h"
#include "inth.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define ARP32_WUGEN_INVALID_SHIFT      (0xFFFFFFFFU)
/** \brief  Macro to define Invalid register shift */

#define ARP32_INTR_REGISTER_ADDRESS_JUMP    (0x10U)
/** \brief ARP32 Interrupt Register Address Jump */

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
/*                          Function Declarations                             */
/* ========================================================================== */

void ARP32_WUGEN_IRQ_DisableAll(void)
{
    HW_WR_REG32(SOC_EVE_SYSTEM_BASE + EVE_ARP32_IRQWAKEEN, 0);
}

void ARP32_WUGEN_IRQ_Init(void)
{
    ARP32_WUGEN_IRQ_DisableAll();
}

void ARP32_WUGEN_IRQ_Interrupt_Lookup(void)
{
    uint32_t index  = 0U;
    uint32_t  regval = 0U, finalRegVal = 0U;

    /* First grab the EVT_INT00 to EVT_INT07 status */
    for (index = 0U; index < 4U; index++)
    {
        regval |= HW_RD_REG32(SOC_EVE_SYSTEM_BASE +
                              EVE_ARP32_INT4_IRQENABLE_SET +
                              (index * ARP32_INTR_REGISTER_ADDRESS_JUMP));
    }
    /* Get the lower 8 bits of the register */
    finalRegVal = regval & (((uint32_t)1U << (uint32_t)TPCC_INTG) - (uint32_t)1U);

    /* Then grab the EVE_EVT_INT0 to EVE_EVT_INT15 status */
    regval = 0U;
    for (index = 0U; index < 4U; index++)
    {
        regval |= HW_RD_REG32(SOC_EVE_SYSTEM_BASE +
                              EVE_ARP32_INT8_IRQENABLE_SET +
                              (index * ARP32_INTR_REGISTER_ADDRESS_JUMP));
    }
    /* Get the lower 16 bits of the register */
    regval = regval & (((uint32_t)1U << ((uint32_t)EVE_INT1_0 -
            (uint32_t)EVE_EVT_INT0)) - (uint32_t)1U);

    finalRegVal = ((uint32_t)regval <<
                  ((uint32_t)EVE_INT07 + (uint32_t)1U)) | (uint32_t)finalRegVal;

    HW_WR_REG32(SOC_EVE_SYSTEM_BASE + (EVE_ARP32_IRQWAKEEN), finalRegVal);
}

void ARP32_WUGEN_IRQ_Enable(uint16_t intrNum)
{
    uint32_t addr, mask, shift;
    addr = SOC_EVE_SYSTEM_BASE + (EVE_ARP32_IRQWAKEEN);

    if (intrNum <= (uint16_t) EVE_INT07)
    {
        shift = intrNum;
    }
    else if ((intrNum >= (uint16_t)EVE_EVT_INT0) &&
             (intrNum <= (uint16_t)EVE_EVT_INT15))
    {
        shift = ((uint32_t)intrNum - (uint32_t)EVE_EVT_INT0) +
                (uint32_t)EVE_INT07 + 1U;
    }
    else
    {
        shift = ARP32_WUGEN_INVALID_SHIFT;
    }

    if (ARP32_WUGEN_INVALID_SHIFT != shift)
    {
        mask = (uint32_t) 1 << shift;
        /* Enable the wakeup event for interrupt number passed */
        HW_WR_FIELD32_RAW(addr,
                          mask,
                          shift,
                          (uint32_t)1U);
    }
}

void ARP32_WUGEN_IRQ_Disable(uint16_t intrNum)
{
    uint32_t addr, mask, shift;
    addr = SOC_EVE_SYSTEM_BASE + (EVE_ARP32_IRQWAKEEN);

    if (intrNum <= (uint16_t) EVE_INT07)
    {
        shift = intrNum;
    }
    else if ((intrNum >= (uint16_t)EVE_EVT_INT0) &&
             (intrNum <= (uint16_t)EVE_EVT_INT15))
    {
        shift = ((uint32_t)intrNum - (uint32_t)EVE_EVT_INT0) +
                (uint32_t)EVE_INT07 + 1U;
    }
    else
    {
        shift = ARP32_WUGEN_INVALID_SHIFT;
    }

    if (ARP32_WUGEN_INVALID_SHIFT != shift)
    {
        mask = (uint32_t) 1 << shift;
        /* Enable the wakeup event for interrupt number passed */
        HW_WR_FIELD32_RAW(addr,
                          mask,
                          shift,
                          (uint32_t)0U);
    }
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */

