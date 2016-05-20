/*
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

 /**
 * \file  qspi.c
 * \brief      This file contains the function prototypes for the device
 *             abstraction layer for QSPI. It also contains some
 *             related macro definitions and enum definitions.
 *
 *             The QSPI module support single, dual and quad read mode
 *             in interrupt and polling mode using QSPI data registers
 *             and also support memory mapped mode.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include "qspi.h"
#include "hw_qspi.h"
#include "hw_types.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void QSPIconfigIdleMode(uint32_t baseAdd, uint32_t idleMode)
{
    /* Set the idle mode value */
    HW_WR_FIELD32(baseAdd + QSPI_SYSCONFIG,
                  QSPI_SYSCONFIG_IDLE_MODE,
                  idleMode);
}

void QSPISetClockControl(uint32_t baseAdd, qspi_ClockFreq_e in_ClockSettings)
{
    uint32_t lv_clkDivider;
    /* select 128/192MHz from L4 QSPI CLK CTRL register */

    /* get qspi CC register divider value */
    lv_clkDivider = (uint32_t) in_ClockSettings & QSPI_CLKDIVIDER_MASK;

    /* wait for the QSPI to be idle */
    QSPIWaitIdle(baseAdd);

    /* turn off QSPI data clock */
    HW_WR_FIELD32(
        baseAdd + QSPI_SPI_CLOCK_CNTRL_REG,
        QSPI_SPI_CLOCK_CNTRL_REG_CLKEN,
        QSPI_SPI_CLOCK_CNTRL_REG_CLKEN_DCLOCK_OFF);

    /* clear QSPI clock divider*/
    HW_WR_FIELD32(
        baseAdd + QSPI_SPI_CLOCK_CNTRL_REG,
        QSPI_SPI_CLOCK_CNTRL_REG_DCLK_DIV,
        0U);

    /* update QSPI clock divider*/
    HW_WR_FIELD32(
        baseAdd + QSPI_SPI_CLOCK_CNTRL_REG,
        QSPI_SPI_CLOCK_CNTRL_REG_DCLK_DIV,
        lv_clkDivider);

    /* enable QSPI data clock */
    HW_WR_FIELD32(
        baseAdd + QSPI_SPI_CLOCK_CNTRL_REG,
        QSPI_SPI_CLOCK_CNTRL_REG_CLKEN,
        QSPI_SPI_CLOCK_CNTRL_REG_CLKEN_DCLOCK_ON);
}
void QSPIsetDeviceControl(uint32_t baseAdd, uint32_t value)
{
    /* wait for the QSPI to be idle */
    QSPIWaitIdle(baseAdd);
    HW_WR_REG32(baseAdd + QSPI_SPI_DC_REG, value);
}

uint32_t QSPIgetDeviceControl(uint32_t baseAdd)
{
    return (HW_RD_REG32(baseAdd + QSPI_SPI_DC_REG));
}

void QSPIsetCommandReg(uint32_t baseAdd, uint32_t cmd)
{
    /* wait for the QSPI to be idle */
    QSPIWaitIdle(baseAdd);
    HW_WR_REG32(baseAdd + QSPI_SPI_CMD_REG, cmd);
}

uint32_t QSPIgetCommandReg(uint32_t baseAdd)
{
    return (HW_RD_REG32(baseAdd + QSPI_SPI_CMD_REG));
}

uint32_t QSPIgetStatus(uint32_t baseAdd)
{
    return (HW_RD_REG32(baseAdd + QSPI_SPI_STATUS_REG));
}

uint32_t QSPIgetStatusWordCount(uint32_t baseAdd)
{
    return ((QSPIgetStatus(baseAdd) &
             QSPI_SPI_STATUS_REG_WDCNT_MASK) >> QSPI_SPI_STATUS_REG_WDCNT_SHIFT);
}

void QSPIWaitIdle(uint32_t baseAdd)
{
    /* wait while QSPI is busy */
    while ((QSPIgetStatus(baseAdd) & QSPI_SPI_STATUS_REG_BUSY_MASK) ==
           QSPI_SPI_STATUS_REG_BUSY_BUSY)
    {
        /*Do nothing */
    }
}

void QSPIwriteData(uint32_t baseAdd, const uint32_t *data, int32_t length)
{
    HW_WR_REG32(baseAdd + QSPI_SPI_DATA_REG, *data);
    data++;
    length--;
    if (length > 0)
    {
        HW_WR_REG32(baseAdd + QSPI_SPI_DATA_REG_1, *data);
        data++;
        length--;
    }
    if (length > 0)
    {
        HW_WR_REG32(baseAdd + QSPI_SPI_DATA_REG_2, *data);
        data++;
        length--;
    }
    if (length > 0)
    {
        HW_WR_REG32(baseAdd + QSPI_SPI_DATA_REG_3, *data);
        data++;
    }
}

void QSPIreadData(uint32_t baseAdd, uint32_t *data, int32_t length)
{
    *data = HW_RD_REG32(baseAdd + QSPI_SPI_DATA_REG);
    data++;
    length--;
    if (length > 0)
    {
        *data = HW_RD_REG32(baseAdd + QSPI_SPI_DATA_REG_1);
        data++;
        length--;
    }
    if (length > 0)
    {
        *data = HW_RD_REG32(baseAdd + QSPI_SPI_DATA_REG_2);
        data++;
        length--;
    }
    if (length > 0)
    {
        *data = HW_RD_REG32(baseAdd + QSPI_SPI_DATA_REG_3);
        data++;
    }
}

void QSPISetMemoryMapSetup(uint32_t baseAdd, uint32_t value,
                           uint32_t chipSelect)
{
    HW_WR_REG32(baseAdd + QSPI_SPI_SETUP0_REG + (4U * chipSelect), value);
}

uint32_t QSPIgetMemoryMapSetup(uint32_t baseAdd, uint32_t chipSelect)
{
    return (HW_RD_REG32(baseAdd + QSPI_SPI_SETUP0_REG + (4U * chipSelect)));
}

void QSPISetMAddrSpace(uint32_t baseAdd, uint8_t MMPT_S)
{
    /* Set to MMPT_S value */
    HW_WR_FIELD32(baseAdd + QSPI_SPI_SWITCH_REG,
                  QSPI_SPI_SWITCH_REG_MMPT_S,
                  MMPT_S);
}
void QSPIintEnable(uint32_t baseAdd, uint32_t intFlag)
{
    uint32_t regVal;

    regVal = HW_RD_REG32(baseAdd + QSPI_INTR_ENABLE_SET_REG);

    regVal |= intFlag;

    HW_WR_REG32(baseAdd + QSPI_INTR_ENABLE_SET_REG, regVal);
}

void QSPIintDisable(uint32_t baseAdd, uint32_t intFlag)
{
    uint32_t regVal;

    regVal = HW_RD_REG32(baseAdd + QSPI_INTR_ENABLE_CLEAR_REG);

    regVal |= intFlag;

    HW_WR_REG32(baseAdd + QSPI_INTR_ENABLE_CLEAR_REG, regVal);
}

uint32_t QSPIgetEnabledIntStatus(uint32_t baseAdd)
{
    return (HW_RD_REG32(baseAdd + QSPI_INTR_ENABLE_SET_REG));
}

uint32_t QSPIintStatus(uint32_t baseAdd)
{
    return (HW_RD_REG32(baseAdd + QSPI_INTR_STATUS_ENABLED_CLEAR));
}

void QSPIintClear(uint32_t baseAdd, uint32_t intFlag)
{
    HW_WR_REG32(baseAdd + QSPI_INTR_STATUS_ENABLED_CLEAR, intFlag);
}

uint32_t QSPIintRawStatus(uint32_t baseAdd)
{
    return (HW_RD_REG32(baseAdd + QSPI_INTR_STATUS_RAW_SET));
}

void QSPIintRawStatusClear(uint32_t baseAdd, uint32_t intFlag)
{
    HW_WR_REG32(baseAdd + QSPI_INTR_STATUS_RAW_SET, intFlag);
}
/********************************* End of file ******************************/
