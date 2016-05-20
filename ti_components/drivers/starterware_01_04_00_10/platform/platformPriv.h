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
/*
 *  \file   platformPriv.h
 *
 *  \brief  platform API declarations.
 *
 *   This file contains the API prototypes for platform specific functions
 */

#ifndef PLATFORM_PRIV_H_
#define PLATFORM_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
**                       MACRO DEFINITIONS
****************************************************************************/

#define E_PASS                     (0)
#define E_FAIL                     (-1)

#define GPMC_CONFIG1_N(n)          (0x60 + ((n) * 48))
#define GPMC_CONFIG2_N(n)          (0x64 + ((n) * 48))
#define GPMC_CONFIG3_N(n)          (0x68 + ((n) * 48))
#define GPMC_CONFIG4_N(n)          (0x6c + ((n) * 48))
#define GPMC_CONFIG5_N(n)          (0x70 + ((n) * 48))
#define GPMC_CONFIG6_N(n)          (0x74 + ((n) * 48))
#define GPMC_CONFIG7_N(n)          (0x78 + ((n) * 48))

#define gpmc_cfg1_addr             (SOC_GPMC_CONF_REGS_BASE + \
                                    (uint32_t) GPMC_CONFIG1_N(0))
#define gpmc_cfg2_addr             (SOC_GPMC_CONF_REGS_BASE + \
                                    (uint32_t) GPMC_CONFIG2_N(0))
#define gpmc_cfg3_addr             (SOC_GPMC_CONF_REGS_BASE + \
                                    (uint32_t) GPMC_CONFIG3_N(0))
#define gpmc_cfg4_addr             (SOC_GPMC_CONF_REGS_BASE + \
                                    (uint32_t) GPMC_CONFIG4_N(0))
#define gpmc_cfg5_addr             (SOC_GPMC_CONF_REGS_BASE + \
                                    (uint32_t) GPMC_CONFIG5_N(0))
#define gpmc_cfg6_addr             (SOC_GPMC_CONF_REGS_BASE + \
                                    (uint32_t) GPMC_CONFIG6_N(0))
#define gpmc_cfg7_addr             (SOC_GPMC_CONF_REGS_BASE + \
                                    (uint32_t) GPMC_CONFIG7_N(0))

#define GPMC_D0         (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_AD0)
#define GPMC_D1         (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_AD1)
#define GPMC_D2         (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_AD2)
#define GPMC_D3         (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_AD3)
#define GPMC_D4         (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_AD4)
#define GPMC_D5         (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_AD5)
#define GPMC_D6         (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_AD6)
#define GPMC_D7         (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_AD7)
#define GPMC_D8         (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_AD8)
#define GPMC_D9         (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_AD9)
#define GPMC_D10        (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_AD10)
#define GPMC_D11        (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_AD11)
#define GPMC_D12        (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_AD12)
#define GPMC_D13        (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_AD13)
#define GPMC_D14        (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_AD14)
#define GPMC_D15        (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_AD15)

#define GPMC_A0         (SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_GPMC_A0)
#define GPMC_A1         (SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_GPMC_A1)
#define GPMC_A2         (SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_GPMC_A2)
#define GPMC_A3         (SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_GPMC_A3)
#define GPMC_A4         (SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_GPMC_A4)
#define GPMC_A5         (SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_GPMC_A5)
#define GPMC_A6         (SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_GPMC_A6)
#define GPMC_A7         (SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_GPMC_A7)
#define GPMC_A8         (SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_GPMC_A8)
#define GPMC_A9         (SOC_CORE_PAD_IO_REGISTERS_BASE + CTRL_CORE_PAD_GPMC_A9)
#define GPMC_A10        (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_A10)
#define GPMC_A11        (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_A11)
#define GPMC_A12        (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_A12)
#define GPMC_A13        (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_A13)
#define GPMC_A14        (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_A14)
#define GPMC_A15        (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_A15)
#define GPMC_A16        (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_A16)
#define GPMC_A17        (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_A17)
#define GPMC_A18        (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_A18)
#define GPMC_A19        (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_A19)
#define GPMC_A20        (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_A20)
#define GPMC_A21        (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_A21)
#define GPMC_A22        (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_A22)
#define GPMC_A23        (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_A23)
#define GPMC_A24        (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_A24)
#define GPMC_A25        (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_A25)
#define GPMC_A26        (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_A26)
#define GPMC_A27        (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_A27)
#define GPMC_CS0_REG    (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_CS0)
#define GPMC_OEN        (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_OEN_REN)
#define GPMC_WEN        (SOC_CORE_PAD_IO_REGISTERS_BASE + \
                         CTRL_CORE_PAD_GPMC_WEN)

void wait(int32_t count);
void configure_pad(const pad_config_t *pad_array, uint32_t elements);
void cntrl_core_pad_configuration(uint32_t            baseAdd,
                                  const pad_config_t *pad_config);

#ifdef __cplusplus
}
#endif
#endif
