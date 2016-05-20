/**
 *  \file   ipu_wugen.c
 *
 *  \brief  IPU WUGEN related APIs.
 *
 *   This file contains the APIs for configuring IPU_WUGEN
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
#include "hw_ipu_wugen_local_prcm.h"
#include "ipu_wugen.h"
#include "hw_ipu_m4_nvic.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define REG_IDX_SHIFT                  (0x05U)
/** \brief Register Index */

#define REG_BIT_MASK                   (0x1FU)
/** \brief Register Bit Mask */

#define NUM_BYTES_REG                  (0x4U)
/** \brief Address offset per register */

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

void IPU_WUGEN_Init(void)
{
    IPU_WUGEN_DisableAll();
}

void IPU_WUGEN_DisableAll(void)
{
    HW_WR_REG32(SOC_IPU1_WUGEN_BASE + IPU_WUGEN_MEVT0, 0U);
    HW_WR_REG32(SOC_IPU1_WUGEN_BASE + IPU_WUGEN_MEVT1, 0U);
}

/*
 * Interrupts should be dis/enabled before/after calling this function.
 */
void IPU_WUGEN_Interrupt_Lookup(void)
{
    uint32_t regval, rdVal;
    uint32_t index = 0U;

    for (index = 0U; index < 2U; index++)
    {
        /*
         * Fix for OMAPS00325441
         * Just copy:
         * IPU_M4_NVIC_EXTERNAL_INTERRUPT_SETEN_0_31 -> IPU_WUGEN_MEVT0
         * IPU_M4_NVIC_EXTERNAL_INTERRUPT_SETEN_0_31 + 4 -> IPU_WUGEN_MEVT1
         */
        /* Writing to WUGEN_MEVT0 & WUGEN_MEVT1*/
        regval = HW_RD_REG32((SOC_IPU1_C0_INTC_BASE +
                              IPU_M4_NVIC_EXTERNAL_INTERRUPT_SETEN_0_31) +
                             (NUM_BYTES_REG * index));
        regval |= HW_RD_REG32(SOC_IPU1_WUGEN_BASE +
                              (IPU_WUGEN_MEVT0 + (NUM_BYTES_REG * index)));

        HW_WR_REG32(SOC_IPU1_WUGEN_BASE +
                    (IPU_WUGEN_MEVT0 + (NUM_BYTES_REG * index)),
                    regval);

        rdVal = HW_RD_REG32(SOC_IPU1_WUGEN_BASE +
                            (IPU_WUGEN_MEVT0 + (NUM_BYTES_REG * index)));

        /*
         * Fix for OMAPS00325441: Fix race condition
         * In case of possible race-conditions between core0 and core1, one
         * write will be missed. So if write was not successful, write again.
         * This approach will work because only two cores are writing to same
         * register. It will not work for more than two cores.
         * Race condition within the following if-condition will not occur since
         * the other core will read the same register only after at least one
         * iteration of this for-loop and, therefore, later than the execution
         * of the following if-condition.
         */
        if (regval != (regval & rdVal))
        {
            regval |= HW_RD_REG32(SOC_IPU1_WUGEN_BASE +
                                  (IPU_WUGEN_MEVT0 + (NUM_BYTES_REG * index)));
            HW_WR_REG32(SOC_IPU1_WUGEN_BASE +
                        (IPU_WUGEN_MEVT0 + (NUM_BYTES_REG * index)),
                        regval);
        }
    }
}

void IPU_WUGEN_Enable(uint16_t intrNum)
{
    uint32_t addr, index, mask, shift;
    uint16_t modIntNum = intrNum - IPU_WUGEN_NUM_INTR_INTERNAL;

    if (modIntNum > (IPU_WUGEN_FIRST_EXTERNAL_INT_NUM -
                     IPU_WUGEN_NUM_INTR_INTERNAL))
    {
        index = (uint32_t) modIntNum >> REG_IDX_SHIFT;
        shift = (uint32_t) modIntNum & REG_BIT_MASK;
        mask  = ((uint32_t) 1U) << shift;
        addr  = SOC_IPU1_WUGEN_BASE + (IPU_WUGEN_MEVT0 + (NUM_BYTES_REG * index));

        /* Enable the wakeup event for interrupt number passed */
        HW_WR_FIELD32_RAW(addr,
                          mask,
                          shift,
                          (uint32_t) 1U);
    }
}

void IPU_WUGEN_Disable(uint16_t intrNum)
{
    uint32_t addr, index, mask, shift;
    uint16_t modIntNum = intrNum - IPU_WUGEN_NUM_INTR_INTERNAL;

    if (modIntNum > (IPU_WUGEN_FIRST_EXTERNAL_INT_NUM -
                     IPU_WUGEN_NUM_INTR_INTERNAL))
    {
        index = (uint32_t) modIntNum >> REG_IDX_SHIFT;
        shift = (uint32_t) modIntNum & REG_BIT_MASK;
        mask  = ((uint32_t) 1U) << shift;
        addr  = SOC_IPU1_WUGEN_BASE + (IPU_WUGEN_MEVT0 + (NUM_BYTES_REG * index));

        /* Enable the wakeup event for interrupt number passed */
        HW_WR_FIELD32_RAW(addr, mask, shift, (uint32_t) 0U);
    }
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */

