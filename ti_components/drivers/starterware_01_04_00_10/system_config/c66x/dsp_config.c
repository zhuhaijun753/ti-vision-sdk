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

#include "stdint.h"
#include "dsp_config.h"
#include "hw_dsp_system.h"
#include "hw_types.h"

void DSPSysMmuConfig(uint32_t baseAddr, uint32_t mmuInstance, uint32_t enable,
                     uint32_t mmuAbort)
{
    uint32_t regVal;
    if (0U != mmuAbort)
    {
        if (0U == mmuInstance)
        {
            regVal  = HW_RD_REG32(baseAddr + DSP_MMU_CONFIG);
            regVal |= DSP_MMU_CONFIG_MMU0_ABORT_MASK;
            HW_WR_REG32(baseAddr + DSP_MMU_CONFIG, regVal);
        }
        else
        {
            regVal  = HW_RD_REG32(baseAddr + DSP_MMU_CONFIG);
            regVal |= DSP_MMU_CONFIG_MMU1_ABORT_MASK;
            HW_WR_REG32(baseAddr + DSP_MMU_CONFIG, regVal);
        }
    }
    else
    {
        if (0U == mmuInstance)
        {
            regVal  = HW_RD_REG32(baseAddr + DSP_MMU_CONFIG);
            regVal &= (~DSP_MMU_CONFIG_MMU0_ABORT_MASK);
            HW_WR_REG32(baseAddr + DSP_MMU_CONFIG, regVal);
        }
        else
        {
            regVal  = HW_RD_REG32(baseAddr + DSP_MMU_CONFIG);
            regVal &= (~DSP_MMU_CONFIG_MMU1_ABORT_MASK);
            HW_WR_REG32_RAW(baseAddr + DSP_MMU_CONFIG, regVal);
        }
    }

    if (0U != enable)
    {
        regVal  = HW_RD_REG32(baseAddr + DSP_MMU_CONFIG);
        regVal |=
            (DSP_MMU_CONFIG_MMU0_EN_MASK <<
             (mmuInstance * DSP_MMU_CONFIG_MMU1_EN_SHIFT));
        HW_WR_REG32(baseAddr + DSP_MMU_CONFIG, regVal);
    }
    else
    {
        regVal  = HW_RD_REG32(baseAddr + DSP_MMU_CONFIG);
        regVal &=
            (~(DSP_MMU_CONFIG_MMU0_EN_MASK <<
               (mmuInstance * DSP_MMU_CONFIG_MMU1_EN_SHIFT)));
        HW_WR_REG32(baseAddr + DSP_MMU_CONFIG, regVal);
    }
}

