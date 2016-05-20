/******************************************************************************
*
* hw_ckgen_cm_core_aon.h - register-level header file for PRCM
*
* Copyright (c) 2008-2013 Texas Instruments Incorporated.  All rights reserved.
* Software License Agreement
*
* Texas Instruments (TI) is supplying this software for use solely and
* exclusively on TI devices. The software is owned by TI and/or its
* suppliers, and is protected under applicable patent and copyright laws.
*
* You may not combine this software with any open-source software if such
* combination would cause this software to become subject to any of the
* license terms applicable to such open source software.
*
* THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
* NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
* NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
* CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
* DAMAGES, FOR ANY REASON WHATSOEVER.
* 
******************************************************************************
*/
#ifndef HW_CKGEN_CM_CORE_AON_H_
#define HW_CKGEN_CM_CORE_AON_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define CM_CLKSEL_CORE                                                                                      (0x0U)
#define CM_CLKSEL_ABE                                                                                       (0x8U)
#define CM_DLL_CTRL                                                                                         (0x10U)
#define CM_CLKMODE_DPLL_CORE                                                                                (0x20U)
#define CM_IDLEST_DPLL_CORE                                                                                 (0x24U)
#define CM_AUTOIDLE_DPLL_CORE                                                                               (0x28U)
#define CM_CLKSEL_DPLL_CORE                                                                                 (0x2cU)
#define CM_DIV_M2_DPLL_CORE                                                                                 (0x30U)
#define CM_DIV_H12_DPLL_CORE                                                                                (0x3cU)
#define CM_DIV_H13_DPLL_CORE                                                                                (0x40U)
#define CM_DIV_H14_DPLL_CORE                                                                                (0x44U)
#define CM_SSC_DELTAMSTEP_DPLL_CORE                                                                         (0x48U)
#define CM_SSC_MODFREQDIV_DPLL_CORE                                                                         (0x4cU)
#define CM_DIV_H22_DPLL_CORE                                                                                (0x54U)
#define CM_DIV_H23_DPLL_CORE                                                                                (0x58U)
#define CM_DIV_H24_DPLL_CORE                                                                                (0x5cU)
#define CM_CLKMODE_DPLL_MPU                                                                                 (0x60U)
#define CM_IDLEST_DPLL_MPU                                                                                  (0x64U)
#define CM_AUTOIDLE_DPLL_MPU                                                                                (0x68U)
#define CM_CLKSEL_DPLL_MPU                                                                                  (0x6cU)
#define CM_DIV_M2_DPLL_MPU                                                                                  (0x70U)
#define CM_SSC_DELTAMSTEP_DPLL_MPU                                                                          (0x88U)
#define CM_SSC_MODFREQDIV_DPLL_MPU                                                                          (0x8cU)
#define CM_BYPCLK_DPLL_MPU                                                                                  (0x9cU)
#define CM_CLKMODE_DPLL_IVA                                                                                 (0xa0U)
#define CM_IDLEST_DPLL_IVA                                                                                  (0xa4U)
#define CM_AUTOIDLE_DPLL_IVA                                                                                (0xa8U)
#define CM_CLKSEL_DPLL_IVA                                                                                  (0xacU)
#define CM_DIV_M2_DPLL_IVA                                                                                  (0xb0U)
#define CM_SSC_DELTAMSTEP_DPLL_IVA                                                                          (0xc8U)
#define CM_SSC_MODFREQDIV_DPLL_IVA                                                                          (0xccU)
#define CM_BYPCLK_DPLL_IVA                                                                                  (0xdcU)
#define CM_CLKMODE_DPLL_ABE                                                                                 (0xe0U)
#define CM_IDLEST_DPLL_ABE                                                                                  (0xe4U)
#define CM_AUTOIDLE_DPLL_ABE                                                                                (0xe8U)
#define CM_CLKSEL_DPLL_ABE                                                                                  (0xecU)
#define CM_DIV_M2_DPLL_ABE                                                                                  (0xf0U)
#define CM_DIV_M3_DPLL_ABE                                                                                  (0xf4U)
#define CM_SSC_DELTAMSTEP_DPLL_ABE                                                                          (0x108U)
#define CM_SSC_MODFREQDIV_DPLL_ABE                                                                          (0x10cU)
#define CM_CLKMODE_DPLL_DDR                                                                                 (0x110U)
#define CM_IDLEST_DPLL_DDR                                                                                  (0x114U)
#define CM_AUTOIDLE_DPLL_DDR                                                                                (0x118U)
#define CM_CLKSEL_DPLL_DDR                                                                                  (0x11cU)
#define CM_DIV_M2_DPLL_DDR                                                                                  (0x120U)
#define CM_DIV_H11_DPLL_DDR                                                                                 (0x128U)
#define CM_SSC_DELTAMSTEP_DPLL_DDR                                                                          (0x12cU)
#define CM_SSC_MODFREQDIV_DPLL_DDR                                                                          (0x130U)
#define CM_CLKMODE_DPLL_DSP                                                                                 (0x134U)
#define CM_IDLEST_DPLL_DSP                                                                                  (0x138U)
#define CM_AUTOIDLE_DPLL_DSP                                                                                (0x13cU)
#define CM_CLKSEL_DPLL_DSP                                                                                  (0x140U)
#define CM_DIV_M2_DPLL_DSP                                                                                  (0x144U)
#define CM_DIV_M3_DPLL_DSP                                                                                  (0x148U)
#define CM_SSC_DELTAMSTEP_DPLL_DSP                                                                          (0x14cU)
#define CM_SSC_MODFREQDIV_DPLL_DSP                                                                          (0x150U)
#define CM_BYPCLK_DPLL_DSP                                                                                  (0x154U)
#define CM_SHADOW_FREQ_CONFIG1                                                                              (0x160U)
#define CM_SHADOW_FREQ_CONFIG2                                                                              (0x164U)
#define CM_DYN_DEP_PRESCAL                                                                                  (0x170U)
#define CM_RESTORE_ST                                                                                       (0x180U)
#define CM_CLKMODE_DPLL_EVE                                                                                 (0x184U)
#define CM_IDLEST_DPLL_EVE                                                                                  (0x188U)
#define CM_AUTOIDLE_DPLL_EVE                                                                                (0x18cU)
#define CM_CLKSEL_DPLL_EVE                                                                                  (0x190U)
#define CM_DIV_M2_DPLL_EVE                                                                                  (0x194U)
#define CM_DIV_M3_DPLL_EVE                                                                                  (0x198U)
#define CM_SSC_DELTAMSTEP_DPLL_EVE                                                                          (0x19cU)
#define CM_SSC_MODFREQDIV_DPLL_EVE                                                                          (0x1a0U)
#define CM_BYPCLK_DPLL_EVE                                                                                  (0x1a4U)
#define CM_CLKMODE_DPLL_GMAC                                                                                (0x1a8U)
#define CM_IDLEST_DPLL_GMAC                                                                                 (0x1acU)
#define CM_AUTOIDLE_DPLL_GMAC                                                                               (0x1b0U)
#define CM_CLKSEL_DPLL_GMAC                                                                                 (0x1b4U)
#define CM_DIV_M2_DPLL_GMAC                                                                                 (0x1b8U)
#define CM_DIV_M3_DPLL_GMAC                                                                                 (0x1bcU)
#define CM_DIV_H11_DPLL_GMAC                                                                                (0x1c0U)
#define CM_DIV_H12_DPLL_GMAC                                                                                (0x1c4U)
#define CM_DIV_H13_DPLL_GMAC                                                                                (0x1c8U)
#define CM_SSC_DELTAMSTEP_DPLL_GMAC                                                                         (0x1d0U)
#define CM_SSC_MODFREQDIV_DPLL_GMAC                                                                         (0x1d4U)
#define CM_CLKMODE_DPLL_GPU                                                                                 (0x1d8U)
#define CM_IDLEST_DPLL_GPU                                                                                  (0x1dcU)
#define CM_AUTOIDLE_DPLL_GPU                                                                                (0x1e0U)
#define CM_CLKSEL_DPLL_GPU                                                                                  (0x1e4U)
#define CM_DIV_M2_DPLL_GPU                                                                                  (0x1e8U)
#define CM_SSC_DELTAMSTEP_DPLL_GPU                                                                          (0x1f0U)
#define CM_SSC_MODFREQDIV_DPLL_GPU                                                                          (0x1f4U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define CM_CLKSEL_CORE_CLKSEL_L3_SHIFT                                                                      (4U)
#define CM_CLKSEL_CORE_CLKSEL_L3_MASK                                                                       (0x00000010U)
#define CM_CLKSEL_CORE_CLKSEL_L3_CORE_CLK_DIV_1                                                              (0U)
#define CM_CLKSEL_CORE_CLKSEL_L3_CORE_CLK_DIV_2                                                              (1U)

#define CM_CLKSEL_CORE_CLKSEL_L4_SHIFT                                                                      (8U)
#define CM_CLKSEL_CORE_CLKSEL_L4_MASK                                                                       (0x00000100U)
#define CM_CLKSEL_CORE_CLKSEL_L4_L3_CLK_DIV_1                                                                (0U)
#define CM_CLKSEL_CORE_CLKSEL_L4_L3_CLK_DIV_2                                                                (1U)

#define CM_CLKSEL_CORE_RESERVED_SHIFT                                                                       (0U)
#define CM_CLKSEL_CORE_RESERVED_MASK                                                                        (0x0000000fU)

#define CM_CLKSEL_CORE_RESERVED1_SHIFT                                                                      (5U)
#define CM_CLKSEL_CORE_RESERVED1_MASK                                                                       (0x000000e0U)

#define CM_CLKSEL_CORE_RESERVED2_SHIFT                                                                      (9U)
#define CM_CLKSEL_CORE_RESERVED2_MASK                                                                       (0xfffffe00U)

#define CM_CLKSEL_ABE_CLKSEL_OPP_SHIFT                                                                      (0U)
#define CM_CLKSEL_ABE_CLKSEL_OPP_MASK                                                                       (0x00000003U)
#define CM_CLKSEL_ABE_CLKSEL_OPP_DIV_1                                                                       (0U)
#define CM_CLKSEL_ABE_CLKSEL_OPP_DIV_2                                                                       (1U)
#define CM_CLKSEL_ABE_CLKSEL_OPP_DIV_4                                                                       (2U)
#define CM_CLKSEL_ABE_CLKSEL_OPP_RESERVED                                                                    (3U)

#define CM_CLKSEL_ABE_PAD_CLKS_GATE_SHIFT                                                                   (8U)
#define CM_CLKSEL_ABE_PAD_CLKS_GATE_MASK                                                                    (0x00000100U)
#define CM_CLKSEL_ABE_PAD_CLKS_GATE_GATED                                                                    (0U)
#define CM_CLKSEL_ABE_PAD_CLKS_GATE_ENABLED                                                                  (1U)

#define CM_CLKSEL_ABE_SLIMBUS1_CLK_GATE_SHIFT                                                               (10U)
#define CM_CLKSEL_ABE_SLIMBUS1_CLK_GATE_MASK                                                                (0x00000400U)
#define CM_CLKSEL_ABE_SLIMBUS1_CLK_GATE_GATED                                                                (0U)
#define CM_CLKSEL_ABE_SLIMBUS1_CLK_GATE_ENABLED                                                              (1U)

#define CM_CLKSEL_ABE_RESERVED1_SHIFT                                                                       (9U)
#define CM_CLKSEL_ABE_RESERVED1_MASK                                                                        (0x00000200U)

#define CM_CLKSEL_ABE_RESERVED2_SHIFT                                                                       (11U)
#define CM_CLKSEL_ABE_RESERVED2_MASK                                                                        (0xfffff800U)

#define CM_CLKSEL_ABE_RESERVED_SHIFT                                                                        (2U)
#define CM_CLKSEL_ABE_RESERVED_MASK                                                                         (0x000000fcU)

#define CM_DLL_CTRL_DLL_OVERRIDE_SHIFT                                                                      (0U)
#define CM_DLL_CTRL_DLL_OVERRIDE_MASK                                                                       (0x00000001U)
#define CM_DLL_CTRL_DLL_OVERRIDE_NO_OVR                                                                      (0U)
#define CM_DLL_CTRL_DLL_OVERRIDE_OVR                                                                         (1U)

#define CM_DLL_CTRL_RESERVED_SHIFT                                                                          (1U)
#define CM_DLL_CTRL_RESERVED_MASK                                                                           (0xfffffffeU)

#define CM_CLKMODE_DPLL_CORE_DPLL_EN_SHIFT                                                                  (0U)
#define CM_CLKMODE_DPLL_CORE_DPLL_EN_MASK                                                                   (0x00000007U)
#define CM_CLKMODE_DPLL_CORE_DPLL_EN_RESERVED                                                                (0U)
#define CM_CLKMODE_DPLL_CORE_DPLL_EN_RESERVED1                                                               (1U)
#define CM_CLKMODE_DPLL_CORE_DPLL_EN_RESERVED2                                                               (2U)
#define CM_CLKMODE_DPLL_CORE_DPLL_EN_RESERVED3                                                               (3U)
#define CM_CLKMODE_DPLL_CORE_DPLL_EN_RESERVED4                                                               (4U)
#define CM_CLKMODE_DPLL_CORE_DPLL_EN_DPLL_LP_BYP_MODE                                                        (5U)
#define CM_CLKMODE_DPLL_CORE_DPLL_EN_DPLL_FR_BYP_MODE                                                        (6U)
#define CM_CLKMODE_DPLL_CORE_DPLL_EN_DPLL_LOCK_MODE                                                          (7U)

#define CM_CLKMODE_DPLL_CORE_DPLL_DRIFTGUARD_EN_SHIFT                                                       (8U)
#define CM_CLKMODE_DPLL_CORE_DPLL_DRIFTGUARD_EN_MASK                                                        (0x00000100U)
#define CM_CLKMODE_DPLL_CORE_DPLL_DRIFTGUARD_EN_ENABLED                                                      (1U)
#define CM_CLKMODE_DPLL_CORE_DPLL_DRIFTGUARD_EN_DIASBLED                                                     (0U)

#define CM_CLKMODE_DPLL_CORE_DPLL_RAMP_LEVEL_SHIFT                                                          (3U)
#define CM_CLKMODE_DPLL_CORE_DPLL_RAMP_LEVEL_MASK                                                           (0x00000018U)
#define CM_CLKMODE_DPLL_CORE_DPLL_RAMP_LEVEL_RAMP_DISABLE                                                    (0U)
#define CM_CLKMODE_DPLL_CORE_DPLL_RAMP_LEVEL_RAMP_ALGO1                                                      (1U)
#define CM_CLKMODE_DPLL_CORE_DPLL_RAMP_LEVEL_RAMP_ALGO2                                                      (2U)
#define CM_CLKMODE_DPLL_CORE_DPLL_RAMP_LEVEL_RESERVED                                                        (3U)

#define CM_CLKMODE_DPLL_CORE_DPLL_RAMP_RATE_SHIFT                                                           (5U)
#define CM_CLKMODE_DPLL_CORE_DPLL_RAMP_RATE_MASK                                                            (0x000000e0U)
#define CM_CLKMODE_DPLL_CORE_DPLL_RAMP_RATE_REFCLKX2                                                         (0U)
#define CM_CLKMODE_DPLL_CORE_DPLL_RAMP_RATE_REFCLKX4                                                         (1U)
#define CM_CLKMODE_DPLL_CORE_DPLL_RAMP_RATE_REFCLKX8                                                         (2U)
#define CM_CLKMODE_DPLL_CORE_DPLL_RAMP_RATE_REFCLKX16                                                        (3U)
#define CM_CLKMODE_DPLL_CORE_DPLL_RAMP_RATE_REFCLKX32                                                        (4U)
#define CM_CLKMODE_DPLL_CORE_DPLL_RAMP_RATE_REFCLKX64                                                        (5U)
#define CM_CLKMODE_DPLL_CORE_DPLL_RAMP_RATE_REFCLKX128                                                       (6U)
#define CM_CLKMODE_DPLL_CORE_DPLL_RAMP_RATE_REFCLKX512                                                       (7U)

#define CM_CLKMODE_DPLL_CORE_DPLL_RELOCK_RAMP_EN_SHIFT                                                      (9U)
#define CM_CLKMODE_DPLL_CORE_DPLL_RELOCK_RAMP_EN_MASK                                                       (0x00000200U)

#define CM_CLKMODE_DPLL_CORE_DPLL_LPMODE_EN_SHIFT                                                           (10U)
#define CM_CLKMODE_DPLL_CORE_DPLL_LPMODE_EN_MASK                                                            (0x00000400U)
#define CM_CLKMODE_DPLL_CORE_DPLL_LPMODE_EN_DISABLED                                                         (0U)
#define CM_CLKMODE_DPLL_CORE_DPLL_LPMODE_EN_ENABLED                                                          (1U)

#define CM_CLKMODE_DPLL_CORE_DPLL_REGM4XEN_SHIFT                                                            (11U)
#define CM_CLKMODE_DPLL_CORE_DPLL_REGM4XEN_MASK                                                             (0x00000800U)
#define CM_CLKMODE_DPLL_CORE_DPLL_REGM4XEN_DISABLED                                                          (0U)

#define CM_CLKMODE_DPLL_CORE_DPLL_SSC_EN_SHIFT                                                              (12U)
#define CM_CLKMODE_DPLL_CORE_DPLL_SSC_EN_MASK                                                               (0x00001000U)
#define CM_CLKMODE_DPLL_CORE_DPLL_SSC_EN_DISABLED                                                            (0U)
#define CM_CLKMODE_DPLL_CORE_DPLL_SSC_EN_ENABLED                                                             (1U)

#define CM_CLKMODE_DPLL_CORE_DPLL_SSC_ACK_SHIFT                                                             (13U)
#define CM_CLKMODE_DPLL_CORE_DPLL_SSC_ACK_MASK                                                              (0x00002000U)
#define CM_CLKMODE_DPLL_CORE_DPLL_SSC_ACK_DISABLED                                                           (0U)
#define CM_CLKMODE_DPLL_CORE_DPLL_SSC_ACK_ENABLED                                                            (1U)

#define CM_CLKMODE_DPLL_CORE_DPLL_SSC_DOWNSPREAD_SHIFT                                                      (14U)
#define CM_CLKMODE_DPLL_CORE_DPLL_SSC_DOWNSPREAD_MASK                                                       (0x00004000U)
#define CM_CLKMODE_DPLL_CORE_DPLL_SSC_DOWNSPREAD_FULL_SPREAD                                                 (0U)
#define CM_CLKMODE_DPLL_CORE_DPLL_SSC_DOWNSPREAD_LOW_SPREAD                                                  (1U)

#define CM_CLKMODE_DPLL_CORE_DPLL_SSC_TYPE_SHIFT                                                            (15U)
#define CM_CLKMODE_DPLL_CORE_DPLL_SSC_TYPE_MASK                                                             (0x00008000U)
#define CM_CLKMODE_DPLL_CORE_DPLL_SSC_TYPE_TRIANGULAR                                                        (0U)
#define CM_CLKMODE_DPLL_CORE_DPLL_SSC_TYPE_SQUARE                                                            (1U)

#define CM_CLKMODE_DPLL_CORE_RESERVED_SHIFT                                                                 (16U)
#define CM_CLKMODE_DPLL_CORE_RESERVED_MASK                                                                  (0xffff0000U)

#define CM_IDLEST_DPLL_CORE_ST_DPLL_CLK_SHIFT                                                               (0U)
#define CM_IDLEST_DPLL_CORE_ST_DPLL_CLK_MASK                                                                (0x00000001U)
#define CM_IDLEST_DPLL_CORE_ST_DPLL_CLK_DPLL_UNLOCKED                                                        (0U)
#define CM_IDLEST_DPLL_CORE_ST_DPLL_CLK_DPLL_LOCKED                                                          (1U)

#define CM_IDLEST_DPLL_CORE_RESERVED_SHIFT                                                                  (5U)
#define CM_IDLEST_DPLL_CORE_RESERVED_MASK                                                                   (0xffffffe0U)

#define CM_IDLEST_DPLL_CORE_ST_DPLL_MODE_SHIFT                                                              (1U)
#define CM_IDLEST_DPLL_CORE_ST_DPLL_MODE_MASK                                                               (0x0000000eU)
#define CM_IDLEST_DPLL_CORE_ST_DPLL_MODE_TRANSIENT                                                           (0U)
#define CM_IDLEST_DPLL_CORE_ST_DPLL_MODE_LP_STOP                                                             (1U)
#define CM_IDLEST_DPLL_CORE_ST_DPLL_MODE_FR_STOP                                                             (2U)
#define CM_IDLEST_DPLL_CORE_ST_DPLL_MODE_RESERVED1                                                           (3U)
#define CM_IDLEST_DPLL_CORE_ST_DPLL_MODE_RESERVED2                                                           (4U)
#define CM_IDLEST_DPLL_CORE_ST_DPLL_MODE_LP_BYP                                                              (5U)
#define CM_IDLEST_DPLL_CORE_ST_DPLL_MODE_FR_BYP                                                              (6U)
#define CM_IDLEST_DPLL_CORE_ST_DPLL_MODE_RESERVED3                                                           (7U)

#define CM_IDLEST_DPLL_CORE_ST_DPLL_INIT_SHIFT                                                              (4U)
#define CM_IDLEST_DPLL_CORE_ST_DPLL_INIT_MASK                                                               (0x00000010U)
#define CM_IDLEST_DPLL_CORE_ST_DPLL_INIT_DPLL_NOTINIT                                                        (0U)
#define CM_IDLEST_DPLL_CORE_ST_DPLL_INIT_DPLL_INIT                                                           (1U)

#define CM_AUTOIDLE_DPLL_CORE_AUTO_DPLL_MODE_SHIFT                                                          (0U)
#define CM_AUTOIDLE_DPLL_CORE_AUTO_DPLL_MODE_MASK                                                           (0x00000007U)
#define CM_AUTOIDLE_DPLL_CORE_AUTO_DPLL_MODE_AUTO_CTL_DISABLE                                                (0U)
#define CM_AUTOIDLE_DPLL_CORE_AUTO_DPLL_MODE_AUTO_LP_STOP                                                    (1U)
#define CM_AUTOIDLE_DPLL_CORE_AUTO_DPLL_MODE_AUTO_FR_STOP                                                    (2U)
#define CM_AUTOIDLE_DPLL_CORE_AUTO_DPLL_MODE_RESERVED                                                        (3U)
#define CM_AUTOIDLE_DPLL_CORE_AUTO_DPLL_MODE_RESERVED1                                                       (4U)
#define CM_AUTOIDLE_DPLL_CORE_AUTO_DPLL_MODE_AUTO_LP_BYP                                                     (5U)
#define CM_AUTOIDLE_DPLL_CORE_AUTO_DPLL_MODE_AUTO_FR_BYP                                                     (6U)
#define CM_AUTOIDLE_DPLL_CORE_AUTO_DPLL_MODE_RESERVED2                                                       (7U)

#define CM_AUTOIDLE_DPLL_CORE_RESERVED_SHIFT                                                                (3U)
#define CM_AUTOIDLE_DPLL_CORE_RESERVED_MASK                                                                 (0xfffffff8U)

#define CM_CLKSEL_DPLL_CORE_DPLL_DIV_SHIFT                                                                  (0U)
#define CM_CLKSEL_DPLL_CORE_DPLL_DIV_MASK                                                                   (0x0000007fU)

#define CM_CLKSEL_DPLL_CORE_DPLL_BYP_CLKSEL_SHIFT                                                           (23U)
#define CM_CLKSEL_DPLL_CORE_DPLL_BYP_CLKSEL_MASK                                                            (0x00800000U)

#define CM_CLKSEL_DPLL_CORE_DPLL_CLKOUTHIF_CLKSEL_SHIFT                                                     (20U)
#define CM_CLKSEL_DPLL_CORE_DPLL_CLKOUTHIF_CLKSEL_MASK                                                      (0x00100000U)
#define CM_CLKSEL_DPLL_CORE_DPLL_CLKOUTHIF_CLKSEL_SEL_DCO                                                    (0U)
#define CM_CLKSEL_DPLL_CORE_DPLL_CLKOUTHIF_CLKSEL_SEL_CLKINPHIF                                              (1U)

#define CM_CLKSEL_DPLL_CORE_RESERVED_SHIFT                                                                  (7U)
#define CM_CLKSEL_DPLL_CORE_RESERVED_MASK                                                                   (0x00000080U)

#define CM_CLKSEL_DPLL_CORE_RESERVED1_SHIFT                                                                 (19U)
#define CM_CLKSEL_DPLL_CORE_RESERVED1_MASK                                                                  (0x00080000U)

#define CM_CLKSEL_DPLL_CORE_DPLL_MULT_SHIFT                                                                 (8U)
#define CM_CLKSEL_DPLL_CORE_DPLL_MULT_MASK                                                                  (0x0007ff00U)
#define CM_CLKSEL_DPLL_CORE_DPLL_MULT_RESERVED_0                                                             (0U)
#define CM_CLKSEL_DPLL_CORE_DPLL_MULT_RESERVED_1                                                             (1U)

#define CM_CLKSEL_DPLL_CORE_RESERVED3_SHIFT                                                                 (24U)
#define CM_CLKSEL_DPLL_CORE_RESERVED3_MASK                                                                  (0xff000000U)

#define CM_CLKSEL_DPLL_CORE_DCC_EN_SHIFT                                                                    (22U)
#define CM_CLKSEL_DPLL_CORE_DCC_EN_MASK                                                                     (0x00400000U)
#define CM_CLKSEL_DPLL_CORE_DCC_EN_DISABLED                                                                  (0U)

#define CM_CLKSEL_DPLL_CORE_RESERVED2_SHIFT                                                                 (21U)
#define CM_CLKSEL_DPLL_CORE_RESERVED2_MASK                                                                  (0x00200000U)

#define CM_DIV_M2_DPLL_CORE_DIVHS_SHIFT                                                                     (0U)
#define CM_DIV_M2_DPLL_CORE_DIVHS_MASK                                                                      (0x0000001fU)
#define CM_DIV_M2_DPLL_CORE_DIVHS_RESERVED                                                                   (0U)

#define CM_DIV_M2_DPLL_CORE_CLKST_SHIFT                                                                     (9U)
#define CM_DIV_M2_DPLL_CORE_CLKST_MASK                                                                      (0x00000200U)
#define CM_DIV_M2_DPLL_CORE_CLKST_CLK_ENABLED                                                                (1U)
#define CM_DIV_M2_DPLL_CORE_CLKST_CLK_GATED                                                                  (0U)

#define CM_DIV_M2_DPLL_CORE_RESERVED_SHIFT                                                                  (5U)
#define CM_DIV_M2_DPLL_CORE_RESERVED_MASK                                                                   (0x000001e0U)

#define CM_DIV_M2_DPLL_CORE_RESERVED1_SHIFT                                                                 (10U)
#define CM_DIV_M2_DPLL_CORE_RESERVED1_MASK                                                                  (0xfffffc00U)

#define CM_DIV_H12_DPLL_CORE_DIVHS_SHIFT                                                                    (0U)
#define CM_DIV_H12_DPLL_CORE_DIVHS_MASK                                                                     (0x0000003fU)
#define CM_DIV_H12_DPLL_CORE_DIVHS_RESERVED                                                                  (0U)

#define CM_DIV_H12_DPLL_CORE_CLKST_SHIFT                                                                    (9U)
#define CM_DIV_H12_DPLL_CORE_CLKST_MASK                                                                     (0x00000200U)
#define CM_DIV_H12_DPLL_CORE_CLKST_CLK_ENABLED                                                               (1U)
#define CM_DIV_H12_DPLL_CORE_CLKST_CLK_GATED                                                                 (0U)

#define CM_DIV_H12_DPLL_CORE_RESERVED_SHIFT                                                                 (6U)
#define CM_DIV_H12_DPLL_CORE_RESERVED_MASK                                                                  (0x000001c0U)

#define CM_DIV_H12_DPLL_CORE_RESERVED1_SHIFT                                                                (10U)
#define CM_DIV_H12_DPLL_CORE_RESERVED1_MASK                                                                 (0xfffffc00U)

#define CM_DIV_H13_DPLL_CORE_DIVHS_SHIFT                                                                    (0U)
#define CM_DIV_H13_DPLL_CORE_DIVHS_MASK                                                                     (0x0000003fU)
#define CM_DIV_H13_DPLL_CORE_DIVHS_RESERVED                                                                  (0U)

#define CM_DIV_H13_DPLL_CORE_CLKST_SHIFT                                                                    (9U)
#define CM_DIV_H13_DPLL_CORE_CLKST_MASK                                                                     (0x00000200U)
#define CM_DIV_H13_DPLL_CORE_CLKST_CLK_ENABLED                                                               (1U)
#define CM_DIV_H13_DPLL_CORE_CLKST_CLK_GATED                                                                 (0U)

#define CM_DIV_H13_DPLL_CORE_RESERVED_SHIFT                                                                 (6U)
#define CM_DIV_H13_DPLL_CORE_RESERVED_MASK                                                                  (0x000001c0U)

#define CM_DIV_H13_DPLL_CORE_RESERVED1_SHIFT                                                                (10U)
#define CM_DIV_H13_DPLL_CORE_RESERVED1_MASK                                                                 (0xfffffc00U)

#define CM_DIV_H14_DPLL_CORE_DIVHS_SHIFT                                                                    (0U)
#define CM_DIV_H14_DPLL_CORE_DIVHS_MASK                                                                     (0x0000003fU)
#define CM_DIV_H14_DPLL_CORE_DIVHS_RESERVED                                                                  (0U)

#define CM_DIV_H14_DPLL_CORE_CLKST_SHIFT                                                                    (9U)
#define CM_DIV_H14_DPLL_CORE_CLKST_MASK                                                                     (0x00000200U)
#define CM_DIV_H14_DPLL_CORE_CLKST_CLK_ENABLED                                                               (1U)
#define CM_DIV_H14_DPLL_CORE_CLKST_CLK_GATED                                                                 (0U)

#define CM_DIV_H14_DPLL_CORE_RESERVED_SHIFT                                                                 (6U)
#define CM_DIV_H14_DPLL_CORE_RESERVED_MASK                                                                  (0x000001c0U)

#define CM_DIV_H14_DPLL_CORE_RESERVED1_SHIFT                                                                (10U)
#define CM_DIV_H14_DPLL_CORE_RESERVED1_MASK                                                                 (0xfffffc00U)

#define CM_SSC_DELTAMSTEP_DPLL_CORE_DELTAMSTEP_SHIFT                                                        (0U)
#define CM_SSC_DELTAMSTEP_DPLL_CORE_DELTAMSTEP_MASK                                                         (0x000fffffU)

#define CM_SSC_DELTAMSTEP_DPLL_CORE_RESERVED_SHIFT                                                          (20U)
#define CM_SSC_DELTAMSTEP_DPLL_CORE_RESERVED_MASK                                                           (0xfff00000U)

#define CM_SSC_MODFREQDIV_DPLL_CORE_MODFREQDIV_MANTISSA_SHIFT                                               (0U)
#define CM_SSC_MODFREQDIV_DPLL_CORE_MODFREQDIV_MANTISSA_MASK                                                (0x0000007fU)

#define CM_SSC_MODFREQDIV_DPLL_CORE_MODFREQDIV_EXPONENT_SHIFT                                               (8U)
#define CM_SSC_MODFREQDIV_DPLL_CORE_MODFREQDIV_EXPONENT_MASK                                                (0x00000700U)

#define CM_SSC_MODFREQDIV_DPLL_CORE_RESERVED_SHIFT                                                          (7U)
#define CM_SSC_MODFREQDIV_DPLL_CORE_RESERVED_MASK                                                           (0x00000080U)

#define CM_SSC_MODFREQDIV_DPLL_CORE_RESERVED1_SHIFT                                                         (11U)
#define CM_SSC_MODFREQDIV_DPLL_CORE_RESERVED1_MASK                                                          (0xfffff800U)

#define CM_DIV_H22_DPLL_CORE_DIVHS_SHIFT                                                                    (0U)
#define CM_DIV_H22_DPLL_CORE_DIVHS_MASK                                                                     (0x0000003fU)
#define CM_DIV_H22_DPLL_CORE_DIVHS_RESERVED                                                                  (0U)

#define CM_DIV_H22_DPLL_CORE_CLKST_SHIFT                                                                    (9U)
#define CM_DIV_H22_DPLL_CORE_CLKST_MASK                                                                     (0x00000200U)
#define CM_DIV_H22_DPLL_CORE_CLKST_CLK_ENABLED                                                               (1U)
#define CM_DIV_H22_DPLL_CORE_CLKST_CLK_GATED                                                                 (0U)

#define CM_DIV_H22_DPLL_CORE_RESERVED_SHIFT                                                                 (6U)
#define CM_DIV_H22_DPLL_CORE_RESERVED_MASK                                                                  (0x000001c0U)

#define CM_DIV_H22_DPLL_CORE_RESERVED1_SHIFT                                                                (10U)
#define CM_DIV_H22_DPLL_CORE_RESERVED1_MASK                                                                 (0xfffffc00U)

#define CM_DIV_H23_DPLL_CORE_DIVHS_SHIFT                                                                    (0U)
#define CM_DIV_H23_DPLL_CORE_DIVHS_MASK                                                                     (0x0000003fU)
#define CM_DIV_H23_DPLL_CORE_DIVHS_RESERVED                                                                  (0U)

#define CM_DIV_H23_DPLL_CORE_CLKST_SHIFT                                                                    (9U)
#define CM_DIV_H23_DPLL_CORE_CLKST_MASK                                                                     (0x00000200U)
#define CM_DIV_H23_DPLL_CORE_CLKST_CLK_ENABLED                                                               (1U)
#define CM_DIV_H23_DPLL_CORE_CLKST_CLK_GATED                                                                 (0U)

#define CM_DIV_H23_DPLL_CORE_RESERVED_SHIFT                                                                 (6U)
#define CM_DIV_H23_DPLL_CORE_RESERVED_MASK                                                                  (0x000001c0U)

#define CM_DIV_H23_DPLL_CORE_RESERVED1_SHIFT                                                                (10U)
#define CM_DIV_H23_DPLL_CORE_RESERVED1_MASK                                                                 (0xfffffc00U)

#define CM_DIV_H24_DPLL_CORE_DIVHS_SHIFT                                                                    (0U)
#define CM_DIV_H24_DPLL_CORE_DIVHS_MASK                                                                     (0x0000003fU)
#define CM_DIV_H24_DPLL_CORE_DIVHS_RESERVED                                                                  (0U)

#define CM_DIV_H24_DPLL_CORE_CLKST_SHIFT                                                                    (9U)
#define CM_DIV_H24_DPLL_CORE_CLKST_MASK                                                                     (0x00000200U)
#define CM_DIV_H24_DPLL_CORE_CLKST_CLK_ENABLED                                                               (1U)
#define CM_DIV_H24_DPLL_CORE_CLKST_CLK_GATED                                                                 (0U)

#define CM_DIV_H24_DPLL_CORE_RESERVED_SHIFT                                                                 (6U)
#define CM_DIV_H24_DPLL_CORE_RESERVED_MASK                                                                  (0x000001c0U)

#define CM_DIV_H24_DPLL_CORE_RESERVED1_SHIFT                                                                (10U)
#define CM_DIV_H24_DPLL_CORE_RESERVED1_MASK                                                                 (0xfffffc00U)

#define CM_CLKMODE_DPLL_MPU_DPLL_EN_SHIFT                                                                   (0U)
#define CM_CLKMODE_DPLL_MPU_DPLL_EN_MASK                                                                    (0x00000007U)
#define CM_CLKMODE_DPLL_MPU_DPLL_EN_RESERVED                                                                 (0U)
#define CM_CLKMODE_DPLL_MPU_DPLL_EN_RESERVED1                                                                (1U)
#define CM_CLKMODE_DPLL_MPU_DPLL_EN_RESERVED2                                                                (2U)
#define CM_CLKMODE_DPLL_MPU_DPLL_EN_RESERVED3                                                                (3U)
#define CM_CLKMODE_DPLL_MPU_DPLL_EN_RESERVED4                                                                (4U)
#define CM_CLKMODE_DPLL_MPU_DPLL_EN_DPLL_LP_BYP_MODE                                                         (5U)
#define CM_CLKMODE_DPLL_MPU_DPLL_EN_DPLL_FR_BYP_MODE                                                         (6U)
#define CM_CLKMODE_DPLL_MPU_DPLL_EN_DPLL_LOCK_MODE                                                           (7U)

#define CM_CLKMODE_DPLL_MPU_DPLL_RAMP_LEVEL_SHIFT                                                           (3U)
#define CM_CLKMODE_DPLL_MPU_DPLL_RAMP_LEVEL_MASK                                                            (0x00000018U)
#define CM_CLKMODE_DPLL_MPU_DPLL_RAMP_LEVEL_RAMP_DISABLE                                                     (0U)
#define CM_CLKMODE_DPLL_MPU_DPLL_RAMP_LEVEL_RAMP_ALGO1                                                       (1U)
#define CM_CLKMODE_DPLL_MPU_DPLL_RAMP_LEVEL_RAMP_ALGO2                                                       (2U)
#define CM_CLKMODE_DPLL_MPU_DPLL_RAMP_LEVEL_RESERVED                                                         (3U)

#define CM_CLKMODE_DPLL_MPU_DPLL_RAMP_RATE_SHIFT                                                            (5U)
#define CM_CLKMODE_DPLL_MPU_DPLL_RAMP_RATE_MASK                                                             (0x000000e0U)
#define CM_CLKMODE_DPLL_MPU_DPLL_RAMP_RATE_REFCLKX2                                                          (0U)
#define CM_CLKMODE_DPLL_MPU_DPLL_RAMP_RATE_REFCLKX4                                                          (1U)
#define CM_CLKMODE_DPLL_MPU_DPLL_RAMP_RATE_REFCLKX8                                                          (2U)
#define CM_CLKMODE_DPLL_MPU_DPLL_RAMP_RATE_REFCLKX16                                                         (3U)
#define CM_CLKMODE_DPLL_MPU_DPLL_RAMP_RATE_REFCLKX32                                                         (4U)
#define CM_CLKMODE_DPLL_MPU_DPLL_RAMP_RATE_REFCLKX64                                                         (5U)
#define CM_CLKMODE_DPLL_MPU_DPLL_RAMP_RATE_REFCLKX128                                                        (6U)
#define CM_CLKMODE_DPLL_MPU_DPLL_RAMP_RATE_REFCLKX512                                                        (7U)

#define CM_CLKMODE_DPLL_MPU_DPLL_DRIFTGUARD_EN_SHIFT                                                        (8U)
#define CM_CLKMODE_DPLL_MPU_DPLL_DRIFTGUARD_EN_MASK                                                         (0x00000100U)
#define CM_CLKMODE_DPLL_MPU_DPLL_DRIFTGUARD_EN_ENABLED                                                       (1U)
#define CM_CLKMODE_DPLL_MPU_DPLL_DRIFTGUARD_EN_DIASBLED                                                      (0U)

#define CM_CLKMODE_DPLL_MPU_DPLL_RELOCK_RAMP_EN_SHIFT                                                       (9U)
#define CM_CLKMODE_DPLL_MPU_DPLL_RELOCK_RAMP_EN_MASK                                                        (0x00000200U)

#define CM_CLKMODE_DPLL_MPU_DPLL_LPMODE_EN_SHIFT                                                            (10U)
#define CM_CLKMODE_DPLL_MPU_DPLL_LPMODE_EN_MASK                                                             (0x00000400U)
#define CM_CLKMODE_DPLL_MPU_DPLL_LPMODE_EN_DISABLED                                                          (0U)
#define CM_CLKMODE_DPLL_MPU_DPLL_LPMODE_EN_ENABLED                                                           (1U)

#define CM_CLKMODE_DPLL_MPU_DPLL_REGM4XEN_SHIFT                                                             (11U)
#define CM_CLKMODE_DPLL_MPU_DPLL_REGM4XEN_MASK                                                              (0x00000800U)
#define CM_CLKMODE_DPLL_MPU_DPLL_REGM4XEN_DISABLED                                                           (0U)

#define CM_CLKMODE_DPLL_MPU_DPLL_SSC_EN_SHIFT                                                               (12U)
#define CM_CLKMODE_DPLL_MPU_DPLL_SSC_EN_MASK                                                                (0x00001000U)
#define CM_CLKMODE_DPLL_MPU_DPLL_SSC_EN_DISABLED                                                             (0U)
#define CM_CLKMODE_DPLL_MPU_DPLL_SSC_EN_ENABLED                                                              (1U)

#define CM_CLKMODE_DPLL_MPU_DPLL_SSC_ACK_SHIFT                                                              (13U)
#define CM_CLKMODE_DPLL_MPU_DPLL_SSC_ACK_MASK                                                               (0x00002000U)
#define CM_CLKMODE_DPLL_MPU_DPLL_SSC_ACK_DISABLED                                                            (0U)
#define CM_CLKMODE_DPLL_MPU_DPLL_SSC_ACK_ENABLED                                                             (1U)

#define CM_CLKMODE_DPLL_MPU_DPLL_SSC_DOWNSPREAD_SHIFT                                                       (14U)
#define CM_CLKMODE_DPLL_MPU_DPLL_SSC_DOWNSPREAD_MASK                                                        (0x00004000U)
#define CM_CLKMODE_DPLL_MPU_DPLL_SSC_DOWNSPREAD_FULL_SPREAD                                                  (0U)
#define CM_CLKMODE_DPLL_MPU_DPLL_SSC_DOWNSPREAD_LOW_SPREAD                                                   (1U)

#define CM_CLKMODE_DPLL_MPU_DPLL_SSC_TYPE_SHIFT                                                             (15U)
#define CM_CLKMODE_DPLL_MPU_DPLL_SSC_TYPE_MASK                                                              (0x00008000U)
#define CM_CLKMODE_DPLL_MPU_DPLL_SSC_TYPE_TRIANGULAR                                                         (0U)
#define CM_CLKMODE_DPLL_MPU_DPLL_SSC_TYPE_SQUARE                                                             (1U)

#define CM_CLKMODE_DPLL_MPU_RESERVED_SHIFT                                                                  (16U)
#define CM_CLKMODE_DPLL_MPU_RESERVED_MASK                                                                   (0xffff0000U)

#define CM_IDLEST_DPLL_MPU_ST_DPLL_CLK_SHIFT                                                                (0U)
#define CM_IDLEST_DPLL_MPU_ST_DPLL_CLK_MASK                                                                 (0x00000001U)
#define CM_IDLEST_DPLL_MPU_ST_DPLL_CLK_DPLL_UNLOCKED                                                         (0U)
#define CM_IDLEST_DPLL_MPU_ST_DPLL_CLK_DPLL_LOCKED                                                           (1U)

#define CM_IDLEST_DPLL_MPU_RESERVED_SHIFT                                                                   (5U)
#define CM_IDLEST_DPLL_MPU_RESERVED_MASK                                                                    (0xffffffe0U)

#define CM_IDLEST_DPLL_MPU_ST_DPLL_MODE_SHIFT                                                               (1U)
#define CM_IDLEST_DPLL_MPU_ST_DPLL_MODE_MASK                                                                (0x0000000eU)
#define CM_IDLEST_DPLL_MPU_ST_DPLL_MODE_TRANSIENT                                                            (0U)
#define CM_IDLEST_DPLL_MPU_ST_DPLL_MODE_LP_STOP                                                              (1U)
#define CM_IDLEST_DPLL_MPU_ST_DPLL_MODE_FR_STOP                                                              (2U)
#define CM_IDLEST_DPLL_MPU_ST_DPLL_MODE_RESERVED1                                                            (3U)
#define CM_IDLEST_DPLL_MPU_ST_DPLL_MODE_RESERVED2                                                            (4U)
#define CM_IDLEST_DPLL_MPU_ST_DPLL_MODE_LP_BYP                                                               (5U)
#define CM_IDLEST_DPLL_MPU_ST_DPLL_MODE_FR_BYP                                                               (6U)
#define CM_IDLEST_DPLL_MPU_ST_DPLL_MODE_RESERVED3                                                            (7U)

#define CM_IDLEST_DPLL_MPU_ST_DPLL_INIT_SHIFT                                                               (4U)
#define CM_IDLEST_DPLL_MPU_ST_DPLL_INIT_MASK                                                                (0x00000010U)
#define CM_IDLEST_DPLL_MPU_ST_DPLL_INIT_DPLL_NOTINIT                                                         (0U)
#define CM_IDLEST_DPLL_MPU_ST_DPLL_INIT_DPLL_INIT                                                            (1U)

#define CM_AUTOIDLE_DPLL_MPU_AUTO_DPLL_MODE_SHIFT                                                           (0U)
#define CM_AUTOIDLE_DPLL_MPU_AUTO_DPLL_MODE_MASK                                                            (0x00000007U)
#define CM_AUTOIDLE_DPLL_MPU_AUTO_DPLL_MODE_AUTO_CTL_DISABLE                                                 (0U)
#define CM_AUTOIDLE_DPLL_MPU_AUTO_DPLL_MODE_AUTO_LP_STOP                                                     (1U)
#define CM_AUTOIDLE_DPLL_MPU_AUTO_DPLL_MODE_AUTO_FR_STOP                                                     (2U)
#define CM_AUTOIDLE_DPLL_MPU_AUTO_DPLL_MODE_RESERVED3                                                        (3U)
#define CM_AUTOIDLE_DPLL_MPU_AUTO_DPLL_MODE_RESERVED4                                                        (4U)
#define CM_AUTOIDLE_DPLL_MPU_AUTO_DPLL_MODE_AUTO_LP_BYP                                                      (5U)
#define CM_AUTOIDLE_DPLL_MPU_AUTO_DPLL_MODE_AUTO_FR_BYP                                                      (6U)
#define CM_AUTOIDLE_DPLL_MPU_AUTO_DPLL_MODE_RESERVED7                                                        (7U)

#define CM_AUTOIDLE_DPLL_MPU_RESERVED_SHIFT                                                                 (3U)
#define CM_AUTOIDLE_DPLL_MPU_RESERVED_MASK                                                                  (0xfffffff8U)

#define CM_CLKSEL_DPLL_MPU_DPLL_DIV_SHIFT                                                                   (0U)
#define CM_CLKSEL_DPLL_MPU_DPLL_DIV_MASK                                                                    (0x0000007fU)

#define CM_CLKSEL_DPLL_MPU_DPLL_BYP_CLKSEL_SHIFT                                                            (23U)
#define CM_CLKSEL_DPLL_MPU_DPLL_BYP_CLKSEL_MASK                                                             (0x00800000U)

#define CM_CLKSEL_DPLL_MPU_RESERVED_SHIFT                                                                   (7U)
#define CM_CLKSEL_DPLL_MPU_RESERVED_MASK                                                                    (0x00000080U)

#define CM_CLKSEL_DPLL_MPU_RESERVED1_SHIFT                                                                  (19U)
#define CM_CLKSEL_DPLL_MPU_RESERVED1_MASK                                                                   (0x00380000U)

#define CM_CLKSEL_DPLL_MPU_RESERVED2_SHIFT                                                                  (24U)
#define CM_CLKSEL_DPLL_MPU_RESERVED2_MASK                                                                   (0xff000000U)

#define CM_CLKSEL_DPLL_MPU_DPLL_MULT_SHIFT                                                                  (8U)
#define CM_CLKSEL_DPLL_MPU_DPLL_MULT_MASK                                                                   (0x0007ff00U)
#define CM_CLKSEL_DPLL_MPU_DPLL_MULT_RESERVED_0                                                              (0U)
#define CM_CLKSEL_DPLL_MPU_DPLL_MULT_RESERVED_1                                                              (1U)

#define CM_CLKSEL_DPLL_MPU_DCC_EN_SHIFT                                                                     (22U)
#define CM_CLKSEL_DPLL_MPU_DCC_EN_MASK                                                                      (0x00400000U)
#define CM_CLKSEL_DPLL_MPU_DCC_EN_DISABLED                                                                   (0U)
#define CM_CLKSEL_DPLL_MPU_DCC_EN_ENABLED                                                                    (1U)

#define CM_DIV_M2_DPLL_MPU_DIVHS_SHIFT                                                                      (0U)
#define CM_DIV_M2_DPLL_MPU_DIVHS_MASK                                                                       (0x0000001fU)
#define CM_DIV_M2_DPLL_MPU_DIVHS_RESERVED                                                                    (0U)

#define CM_DIV_M2_DPLL_MPU_CLKST_SHIFT                                                                      (9U)
#define CM_DIV_M2_DPLL_MPU_CLKST_MASK                                                                       (0x00000200U)
#define CM_DIV_M2_DPLL_MPU_CLKST_CLK_ENABLED                                                                 (1U)
#define CM_DIV_M2_DPLL_MPU_CLKST_CLK_GATED                                                                   (0U)

#define CM_DIV_M2_DPLL_MPU_RESERVED_SHIFT                                                                   (5U)
#define CM_DIV_M2_DPLL_MPU_RESERVED_MASK                                                                    (0x000001e0U)

#define CM_DIV_M2_DPLL_MPU_RESERVED1_SHIFT                                                                  (10U)
#define CM_DIV_M2_DPLL_MPU_RESERVED1_MASK                                                                   (0xfffffc00U)

#define CM_SSC_DELTAMSTEP_DPLL_MPU_RESERVED_SHIFT                                                           (20U)
#define CM_SSC_DELTAMSTEP_DPLL_MPU_RESERVED_MASK                                                            (0xfff00000U)

#define CM_SSC_DELTAMSTEP_DPLL_MPU_DELTAMSTEP_SHIFT                                                         (0U)
#define CM_SSC_DELTAMSTEP_DPLL_MPU_DELTAMSTEP_MASK                                                          (0x000fffffU)

#define CM_SSC_MODFREQDIV_DPLL_MPU_MODFREQDIV_MANTISSA_SHIFT                                                (0U)
#define CM_SSC_MODFREQDIV_DPLL_MPU_MODFREQDIV_MANTISSA_MASK                                                 (0x0000007fU)

#define CM_SSC_MODFREQDIV_DPLL_MPU_MODFREQDIV_EXPONENT_SHIFT                                                (8U)
#define CM_SSC_MODFREQDIV_DPLL_MPU_MODFREQDIV_EXPONENT_MASK                                                 (0x00000700U)

#define CM_SSC_MODFREQDIV_DPLL_MPU_RESERVED_SHIFT                                                           (7U)
#define CM_SSC_MODFREQDIV_DPLL_MPU_RESERVED_MASK                                                            (0x00000080U)

#define CM_SSC_MODFREQDIV_DPLL_MPU_RESERVED1_SHIFT                                                          (11U)
#define CM_SSC_MODFREQDIV_DPLL_MPU_RESERVED1_MASK                                                           (0xfffff800U)

#define CM_BYPCLK_DPLL_MPU_CLKSEL_SHIFT                                                                     (0U)
#define CM_BYPCLK_DPLL_MPU_CLKSEL_MASK                                                                      (0x00000003U)
#define CM_BYPCLK_DPLL_MPU_CLKSEL_CORE_X2_CLK_DIV_1                                                          (0U)
#define CM_BYPCLK_DPLL_MPU_CLKSEL_CORE_X2_CLK_DIV_2                                                          (1U)
#define CM_BYPCLK_DPLL_MPU_CLKSEL_CORE_X2_CLK_DIV_4                                                          (2U)
#define CM_BYPCLK_DPLL_MPU_CLKSEL_CORE_X2_CLK_DIV_8                                                          (3U)

#define CM_BYPCLK_DPLL_MPU_RESERVED_SHIFT                                                                   (2U)
#define CM_BYPCLK_DPLL_MPU_RESERVED_MASK                                                                    (0xfffffffcU)

#define CM_CLKMODE_DPLL_IVA_DPLL_EN_SHIFT                                                                   (0U)
#define CM_CLKMODE_DPLL_IVA_DPLL_EN_MASK                                                                    (0x00000007U)
#define CM_CLKMODE_DPLL_IVA_DPLL_EN_RESERVED                                                                 (0U)
#define CM_CLKMODE_DPLL_IVA_DPLL_EN_RESERVED1                                                                (1U)
#define CM_CLKMODE_DPLL_IVA_DPLL_EN_RESERVED2                                                                (2U)
#define CM_CLKMODE_DPLL_IVA_DPLL_EN_RESERVED3                                                                (3U)
#define CM_CLKMODE_DPLL_IVA_DPLL_EN_RESERVED4                                                                (4U)
#define CM_CLKMODE_DPLL_IVA_DPLL_EN_DPLL_LP_BYP_MODE                                                         (5U)
#define CM_CLKMODE_DPLL_IVA_DPLL_EN_DPLL_FR_BYP_MODE                                                         (6U)
#define CM_CLKMODE_DPLL_IVA_DPLL_EN_DPLL_LOCK_MODE                                                           (7U)

#define CM_CLKMODE_DPLL_IVA_DPLL_RAMP_LEVEL_SHIFT                                                           (3U)
#define CM_CLKMODE_DPLL_IVA_DPLL_RAMP_LEVEL_MASK                                                            (0x00000018U)
#define CM_CLKMODE_DPLL_IVA_DPLL_RAMP_LEVEL_RAMP_DISABLE                                                     (0U)
#define CM_CLKMODE_DPLL_IVA_DPLL_RAMP_LEVEL_RAMP_ALGO1                                                       (1U)
#define CM_CLKMODE_DPLL_IVA_DPLL_RAMP_LEVEL_RAMP_ALGO2                                                       (2U)
#define CM_CLKMODE_DPLL_IVA_DPLL_RAMP_LEVEL_RESERVED                                                         (3U)

#define CM_CLKMODE_DPLL_IVA_DPLL_RAMP_RATE_SHIFT                                                            (5U)
#define CM_CLKMODE_DPLL_IVA_DPLL_RAMP_RATE_MASK                                                             (0x000000e0U)
#define CM_CLKMODE_DPLL_IVA_DPLL_RAMP_RATE_REFCLKX2                                                          (0U)
#define CM_CLKMODE_DPLL_IVA_DPLL_RAMP_RATE_REFCLKX4                                                          (1U)
#define CM_CLKMODE_DPLL_IVA_DPLL_RAMP_RATE_REFCLKX8                                                          (2U)
#define CM_CLKMODE_DPLL_IVA_DPLL_RAMP_RATE_REFCLKX16                                                         (3U)
#define CM_CLKMODE_DPLL_IVA_DPLL_RAMP_RATE_REFCLKX32                                                         (4U)
#define CM_CLKMODE_DPLL_IVA_DPLL_RAMP_RATE_REFCLKX64                                                         (5U)
#define CM_CLKMODE_DPLL_IVA_DPLL_RAMP_RATE_REFCLKX128                                                        (6U)
#define CM_CLKMODE_DPLL_IVA_DPLL_RAMP_RATE_REFCLKX512                                                        (7U)

#define CM_CLKMODE_DPLL_IVA_DPLL_DRIFTGUARD_EN_SHIFT                                                        (8U)
#define CM_CLKMODE_DPLL_IVA_DPLL_DRIFTGUARD_EN_MASK                                                         (0x00000100U)
#define CM_CLKMODE_DPLL_IVA_DPLL_DRIFTGUARD_EN_ENABLED                                                       (1U)
#define CM_CLKMODE_DPLL_IVA_DPLL_DRIFTGUARD_EN_DIASBLED                                                      (0U)

#define CM_CLKMODE_DPLL_IVA_DPLL_RELOCK_RAMP_EN_SHIFT                                                       (9U)
#define CM_CLKMODE_DPLL_IVA_DPLL_RELOCK_RAMP_EN_MASK                                                        (0x00000200U)

#define CM_CLKMODE_DPLL_IVA_DPLL_LPMODE_EN_SHIFT                                                            (10U)
#define CM_CLKMODE_DPLL_IVA_DPLL_LPMODE_EN_MASK                                                             (0x00000400U)
#define CM_CLKMODE_DPLL_IVA_DPLL_LPMODE_EN_DISABLED                                                          (0U)
#define CM_CLKMODE_DPLL_IVA_DPLL_LPMODE_EN_ENABLED                                                           (1U)

#define CM_CLKMODE_DPLL_IVA_DPLL_REGM4XEN_SHIFT                                                             (11U)
#define CM_CLKMODE_DPLL_IVA_DPLL_REGM4XEN_MASK                                                              (0x00000800U)
#define CM_CLKMODE_DPLL_IVA_DPLL_REGM4XEN_DISABLED                                                           (0U)

#define CM_CLKMODE_DPLL_IVA_DPLL_SSC_EN_SHIFT                                                               (12U)
#define CM_CLKMODE_DPLL_IVA_DPLL_SSC_EN_MASK                                                                (0x00001000U)
#define CM_CLKMODE_DPLL_IVA_DPLL_SSC_EN_DISABLED                                                             (0U)
#define CM_CLKMODE_DPLL_IVA_DPLL_SSC_EN_ENABLED                                                              (1U)

#define CM_CLKMODE_DPLL_IVA_DPLL_SSC_ACK_SHIFT                                                              (13U)
#define CM_CLKMODE_DPLL_IVA_DPLL_SSC_ACK_MASK                                                               (0x00002000U)
#define CM_CLKMODE_DPLL_IVA_DPLL_SSC_ACK_DISABLED                                                            (0U)
#define CM_CLKMODE_DPLL_IVA_DPLL_SSC_ACK_ENABLED                                                             (1U)

#define CM_CLKMODE_DPLL_IVA_DPLL_SSC_DOWNSPREAD_SHIFT                                                       (14U)
#define CM_CLKMODE_DPLL_IVA_DPLL_SSC_DOWNSPREAD_MASK                                                        (0x00004000U)
#define CM_CLKMODE_DPLL_IVA_DPLL_SSC_DOWNSPREAD_FULL_SPREAD                                                  (0U)
#define CM_CLKMODE_DPLL_IVA_DPLL_SSC_DOWNSPREAD_LOW_SPREAD                                                   (1U)

#define CM_CLKMODE_DPLL_IVA_DPLL_SSC_TYPE_SHIFT                                                             (15U)
#define CM_CLKMODE_DPLL_IVA_DPLL_SSC_TYPE_MASK                                                              (0x00008000U)
#define CM_CLKMODE_DPLL_IVA_DPLL_SSC_TYPE_TRIANGULAR                                                         (0U)
#define CM_CLKMODE_DPLL_IVA_DPLL_SSC_TYPE_SQUARE                                                             (1U)

#define CM_CLKMODE_DPLL_IVA_RESERVED_SHIFT                                                                  (16U)
#define CM_CLKMODE_DPLL_IVA_RESERVED_MASK                                                                   (0xffff0000U)

#define CM_IDLEST_DPLL_IVA_ST_DPLL_CLK_SHIFT                                                                (0U)
#define CM_IDLEST_DPLL_IVA_ST_DPLL_CLK_MASK                                                                 (0x00000001U)
#define CM_IDLEST_DPLL_IVA_ST_DPLL_CLK_DPLL_UNLOCKED                                                         (0U)
#define CM_IDLEST_DPLL_IVA_ST_DPLL_CLK_DPLL_LOCKED                                                           (1U)

#define CM_IDLEST_DPLL_IVA_RESERVED_SHIFT                                                                   (5U)
#define CM_IDLEST_DPLL_IVA_RESERVED_MASK                                                                    (0xffffffe0U)

#define CM_IDLEST_DPLL_IVA_ST_DPLL_MODE_SHIFT                                                               (1U)
#define CM_IDLEST_DPLL_IVA_ST_DPLL_MODE_MASK                                                                (0x0000000eU)
#define CM_IDLEST_DPLL_IVA_ST_DPLL_MODE_TRANSIENT                                                            (0U)
#define CM_IDLEST_DPLL_IVA_ST_DPLL_MODE_LP_STOP                                                              (1U)
#define CM_IDLEST_DPLL_IVA_ST_DPLL_MODE_FR_STOP                                                              (2U)
#define CM_IDLEST_DPLL_IVA_ST_DPLL_MODE_RESERVED1                                                            (3U)
#define CM_IDLEST_DPLL_IVA_ST_DPLL_MODE_RESERVED2                                                            (4U)
#define CM_IDLEST_DPLL_IVA_ST_DPLL_MODE_LP_BYP                                                               (5U)
#define CM_IDLEST_DPLL_IVA_ST_DPLL_MODE_FR_BYP                                                               (6U)
#define CM_IDLEST_DPLL_IVA_ST_DPLL_MODE_RESERVED3                                                            (7U)

#define CM_IDLEST_DPLL_IVA_ST_DPLL_INIT_SHIFT                                                               (4U)
#define CM_IDLEST_DPLL_IVA_ST_DPLL_INIT_MASK                                                                (0x00000010U)
#define CM_IDLEST_DPLL_IVA_ST_DPLL_INIT_DPLL_NOTINIT                                                         (0U)
#define CM_IDLEST_DPLL_IVA_ST_DPLL_INIT_DPLL_INIT                                                            (1U)

#define CM_AUTOIDLE_DPLL_IVA_AUTO_DPLL_MODE_SHIFT                                                           (0U)
#define CM_AUTOIDLE_DPLL_IVA_AUTO_DPLL_MODE_MASK                                                            (0x00000007U)
#define CM_AUTOIDLE_DPLL_IVA_AUTO_DPLL_MODE_AUTO_CTL_DISABLE                                                 (0U)
#define CM_AUTOIDLE_DPLL_IVA_AUTO_DPLL_MODE_AUTO_LP_STOP                                                     (1U)
#define CM_AUTOIDLE_DPLL_IVA_AUTO_DPLL_MODE_AUTO_FR_STOP                                                     (2U)
#define CM_AUTOIDLE_DPLL_IVA_AUTO_DPLL_MODE_RESERVED3                                                        (3U)
#define CM_AUTOIDLE_DPLL_IVA_AUTO_DPLL_MODE_RESERVED4                                                        (4U)
#define CM_AUTOIDLE_DPLL_IVA_AUTO_DPLL_MODE_AUTO_LP_BYP                                                      (5U)
#define CM_AUTOIDLE_DPLL_IVA_AUTO_DPLL_MODE_AUTO_FR_BYP                                                      (6U)
#define CM_AUTOIDLE_DPLL_IVA_AUTO_DPLL_MODE_RESERVED7                                                        (7U)

#define CM_AUTOIDLE_DPLL_IVA_RESERVED_SHIFT                                                                 (3U)
#define CM_AUTOIDLE_DPLL_IVA_RESERVED_MASK                                                                  (0xfffffff8U)

#define CM_CLKSEL_DPLL_IVA_DPLL_DIV_SHIFT                                                                   (0U)
#define CM_CLKSEL_DPLL_IVA_DPLL_DIV_MASK                                                                    (0x0000007fU)

#define CM_CLKSEL_DPLL_IVA_RESERVED_SHIFT                                                                   (7U)
#define CM_CLKSEL_DPLL_IVA_RESERVED_MASK                                                                    (0x00000080U)

#define CM_CLKSEL_DPLL_IVA_RESERVED1_SHIFT                                                                  (19U)
#define CM_CLKSEL_DPLL_IVA_RESERVED1_MASK                                                                   (0x00380000U)

#define CM_CLKSEL_DPLL_IVA_RESERVED2_SHIFT                                                                  (24U)
#define CM_CLKSEL_DPLL_IVA_RESERVED2_MASK                                                                   (0xff000000U)

#define CM_CLKSEL_DPLL_IVA_DPLL_BYP_CLKSEL_SHIFT                                                            (23U)
#define CM_CLKSEL_DPLL_IVA_DPLL_BYP_CLKSEL_MASK                                                             (0x00800000U)

#define CM_CLKSEL_DPLL_IVA_DPLL_MULT_SHIFT                                                                  (8U)
#define CM_CLKSEL_DPLL_IVA_DPLL_MULT_MASK                                                                   (0x0007ff00U)
#define CM_CLKSEL_DPLL_IVA_DPLL_MULT_RESERVED_0                                                              (0U)
#define CM_CLKSEL_DPLL_IVA_DPLL_MULT_RESERVED_1                                                              (1U)

#define CM_CLKSEL_DPLL_IVA_DCC_EN_SHIFT                                                                     (22U)
#define CM_CLKSEL_DPLL_IVA_DCC_EN_MASK                                                                      (0x00400000U)
#define CM_CLKSEL_DPLL_IVA_DCC_EN_DISABLED                                                                   (0U)

#define CM_DIV_M2_DPLL_IVA_DIVHS_SHIFT                                                                      (0U)
#define CM_DIV_M2_DPLL_IVA_DIVHS_MASK                                                                       (0x0000001fU)
#define CM_DIV_M2_DPLL_IVA_DIVHS_RESERVED                                                                    (0U)

#define CM_DIV_M2_DPLL_IVA_CLKST_SHIFT                                                                      (9U)
#define CM_DIV_M2_DPLL_IVA_CLKST_MASK                                                                       (0x00000200U)
#define CM_DIV_M2_DPLL_IVA_CLKST_CLK_ENABLED                                                                 (1U)
#define CM_DIV_M2_DPLL_IVA_CLKST_CLK_GATED                                                                   (0U)

#define CM_DIV_M2_DPLL_IVA_RESERVED_SHIFT                                                                   (5U)
#define CM_DIV_M2_DPLL_IVA_RESERVED_MASK                                                                    (0x000001e0U)

#define CM_DIV_M2_DPLL_IVA_RESERVED1_SHIFT                                                                  (10U)
#define CM_DIV_M2_DPLL_IVA_RESERVED1_MASK                                                                   (0xfffffc00U)

#define CM_SSC_DELTAMSTEP_DPLL_IVA_RESERVED_SHIFT                                                           (20U)
#define CM_SSC_DELTAMSTEP_DPLL_IVA_RESERVED_MASK                                                            (0xfff00000U)

#define CM_SSC_DELTAMSTEP_DPLL_IVA_DELTAMSTEP_SHIFT                                                         (0U)
#define CM_SSC_DELTAMSTEP_DPLL_IVA_DELTAMSTEP_MASK                                                          (0x000fffffU)

#define CM_SSC_MODFREQDIV_DPLL_IVA_MODFREQDIV_MANTISSA_SHIFT                                                (0U)
#define CM_SSC_MODFREQDIV_DPLL_IVA_MODFREQDIV_MANTISSA_MASK                                                 (0x0000007fU)

#define CM_SSC_MODFREQDIV_DPLL_IVA_MODFREQDIV_EXPONENT_SHIFT                                                (8U)
#define CM_SSC_MODFREQDIV_DPLL_IVA_MODFREQDIV_EXPONENT_MASK                                                 (0x00000700U)

#define CM_SSC_MODFREQDIV_DPLL_IVA_RESERVED_SHIFT                                                           (7U)
#define CM_SSC_MODFREQDIV_DPLL_IVA_RESERVED_MASK                                                            (0x00000080U)

#define CM_SSC_MODFREQDIV_DPLL_IVA_RESERVED1_SHIFT                                                          (11U)
#define CM_SSC_MODFREQDIV_DPLL_IVA_RESERVED1_MASK                                                           (0xfffff800U)

#define CM_BYPCLK_DPLL_IVA_CLKSEL_SHIFT                                                                     (0U)
#define CM_BYPCLK_DPLL_IVA_CLKSEL_MASK                                                                      (0x00000003U)
#define CM_BYPCLK_DPLL_IVA_CLKSEL_CORE_X2_CLK_DIV_1                                                          (0U)
#define CM_BYPCLK_DPLL_IVA_CLKSEL_CORE_X2_CLK_DIV_2                                                          (1U)
#define CM_BYPCLK_DPLL_IVA_CLKSEL_CORE_X2_CLK_DIV_4                                                          (2U)
#define CM_BYPCLK_DPLL_IVA_CLKSEL_CORE_X2_CLK_DIV_8                                                          (3U)

#define CM_BYPCLK_DPLL_IVA_RESERVED_SHIFT                                                                   (2U)
#define CM_BYPCLK_DPLL_IVA_RESERVED_MASK                                                                    (0xfffffffcU)

#define CM_CLKMODE_DPLL_ABE_DPLL_EN_SHIFT                                                                   (0U)
#define CM_CLKMODE_DPLL_ABE_DPLL_EN_MASK                                                                    (0x00000007U)
#define CM_CLKMODE_DPLL_ABE_DPLL_EN_RESERVED                                                                 (0U)
#define CM_CLKMODE_DPLL_ABE_DPLL_EN_RESERVED1                                                                (1U)
#define CM_CLKMODE_DPLL_ABE_DPLL_EN_RESERVED2                                                                (2U)
#define CM_CLKMODE_DPLL_ABE_DPLL_EN_RESERVED3                                                                (3U)
#define CM_CLKMODE_DPLL_ABE_DPLL_EN_RESERVED4                                                                (4U)
#define CM_CLKMODE_DPLL_ABE_DPLL_EN_DPLL_LP_BYP_MODE                                                         (5U)
#define CM_CLKMODE_DPLL_ABE_DPLL_EN_DPLL_FR_BYP_MODE                                                         (6U)
#define CM_CLKMODE_DPLL_ABE_DPLL_EN_DPLL_LOCK_MODE                                                           (7U)

#define CM_CLKMODE_DPLL_ABE_DPLL_RAMP_LEVEL_SHIFT                                                           (3U)
#define CM_CLKMODE_DPLL_ABE_DPLL_RAMP_LEVEL_MASK                                                            (0x00000018U)
#define CM_CLKMODE_DPLL_ABE_DPLL_RAMP_LEVEL_RAMP_DISABLE                                                     (0U)
#define CM_CLKMODE_DPLL_ABE_DPLL_RAMP_LEVEL_RAMP_ALGO1                                                       (1U)
#define CM_CLKMODE_DPLL_ABE_DPLL_RAMP_LEVEL_RAMP_ALGO2                                                       (2U)
#define CM_CLKMODE_DPLL_ABE_DPLL_RAMP_LEVEL_RESERVED                                                         (3U)

#define CM_CLKMODE_DPLL_ABE_DPLL_RAMP_RATE_SHIFT                                                            (5U)
#define CM_CLKMODE_DPLL_ABE_DPLL_RAMP_RATE_MASK                                                             (0x000000e0U)
#define CM_CLKMODE_DPLL_ABE_DPLL_RAMP_RATE_REFCLKX2                                                          (0U)
#define CM_CLKMODE_DPLL_ABE_DPLL_RAMP_RATE_REFCLKX4                                                          (1U)
#define CM_CLKMODE_DPLL_ABE_DPLL_RAMP_RATE_REFCLKX8                                                          (2U)
#define CM_CLKMODE_DPLL_ABE_DPLL_RAMP_RATE_REFCLKX16                                                         (3U)
#define CM_CLKMODE_DPLL_ABE_DPLL_RAMP_RATE_REFCLKX32                                                         (4U)
#define CM_CLKMODE_DPLL_ABE_DPLL_RAMP_RATE_REFCLKX64                                                         (5U)
#define CM_CLKMODE_DPLL_ABE_DPLL_RAMP_RATE_REFCLKX128                                                        (6U)
#define CM_CLKMODE_DPLL_ABE_DPLL_RAMP_RATE_REFCLKX512                                                        (7U)

#define CM_CLKMODE_DPLL_ABE_DPLL_DRIFTGUARD_EN_SHIFT                                                        (8U)
#define CM_CLKMODE_DPLL_ABE_DPLL_DRIFTGUARD_EN_MASK                                                         (0x00000100U)
#define CM_CLKMODE_DPLL_ABE_DPLL_DRIFTGUARD_EN_ENABLED                                                       (1U)
#define CM_CLKMODE_DPLL_ABE_DPLL_DRIFTGUARD_EN_DIASBLED                                                      (0U)

#define CM_CLKMODE_DPLL_ABE_DPLL_RELOCK_RAMP_EN_SHIFT                                                       (9U)
#define CM_CLKMODE_DPLL_ABE_DPLL_RELOCK_RAMP_EN_MASK                                                        (0x00000200U)

#define CM_CLKMODE_DPLL_ABE_DPLL_LPMODE_EN_SHIFT                                                            (10U)
#define CM_CLKMODE_DPLL_ABE_DPLL_LPMODE_EN_MASK                                                             (0x00000400U)
#define CM_CLKMODE_DPLL_ABE_DPLL_LPMODE_EN_DISABLED                                                          (0U)
#define CM_CLKMODE_DPLL_ABE_DPLL_LPMODE_EN_ENABLED                                                           (1U)

#define CM_CLKMODE_DPLL_ABE_DPLL_REGM4XEN_SHIFT                                                             (11U)
#define CM_CLKMODE_DPLL_ABE_DPLL_REGM4XEN_MASK                                                              (0x00000800U)
#define CM_CLKMODE_DPLL_ABE_DPLL_REGM4XEN_DISABLED                                                           (0U)
#define CM_CLKMODE_DPLL_ABE_DPLL_REGM4XEN_ENABLE                                                             (1U)

#define CM_CLKMODE_DPLL_ABE_DPLL_SSC_EN_SHIFT                                                               (12U)
#define CM_CLKMODE_DPLL_ABE_DPLL_SSC_EN_MASK                                                                (0x00001000U)
#define CM_CLKMODE_DPLL_ABE_DPLL_SSC_EN_DISABLED                                                             (0U)
#define CM_CLKMODE_DPLL_ABE_DPLL_SSC_EN_ENABLED                                                              (1U)

#define CM_CLKMODE_DPLL_ABE_DPLL_SSC_ACK_SHIFT                                                              (13U)
#define CM_CLKMODE_DPLL_ABE_DPLL_SSC_ACK_MASK                                                               (0x00002000U)
#define CM_CLKMODE_DPLL_ABE_DPLL_SSC_ACK_DISABLED                                                            (0U)
#define CM_CLKMODE_DPLL_ABE_DPLL_SSC_ACK_ENABLED                                                             (1U)

#define CM_CLKMODE_DPLL_ABE_DPLL_SSC_DOWNSPREAD_SHIFT                                                       (14U)
#define CM_CLKMODE_DPLL_ABE_DPLL_SSC_DOWNSPREAD_MASK                                                        (0x00004000U)
#define CM_CLKMODE_DPLL_ABE_DPLL_SSC_DOWNSPREAD_FULL_SPREAD                                                  (0U)
#define CM_CLKMODE_DPLL_ABE_DPLL_SSC_DOWNSPREAD_LOW_SPREAD                                                   (1U)

#define CM_CLKMODE_DPLL_ABE_DPLL_SSC_TYPE_SHIFT                                                             (15U)
#define CM_CLKMODE_DPLL_ABE_DPLL_SSC_TYPE_MASK                                                              (0x00008000U)
#define CM_CLKMODE_DPLL_ABE_DPLL_SSC_TYPE_TRIANGULAR                                                         (0U)
#define CM_CLKMODE_DPLL_ABE_DPLL_SSC_TYPE_SQUARE                                                             (1U)

#define CM_CLKMODE_DPLL_ABE_RESERVED_SHIFT                                                                  (16U)
#define CM_CLKMODE_DPLL_ABE_RESERVED_MASK                                                                   (0xffff0000U)

#define CM_IDLEST_DPLL_ABE_ST_DPLL_CLK_SHIFT                                                                (0U)
#define CM_IDLEST_DPLL_ABE_ST_DPLL_CLK_MASK                                                                 (0x00000001U)
#define CM_IDLEST_DPLL_ABE_ST_DPLL_CLK_DPLL_UNLOCKED                                                         (0U)
#define CM_IDLEST_DPLL_ABE_ST_DPLL_CLK_DPLL_LOCKED                                                           (1U)

#define CM_IDLEST_DPLL_ABE_RESERVED_SHIFT                                                                   (5U)
#define CM_IDLEST_DPLL_ABE_RESERVED_MASK                                                                    (0xffffffe0U)

#define CM_IDLEST_DPLL_ABE_ST_DPLL_MODE_SHIFT                                                               (1U)
#define CM_IDLEST_DPLL_ABE_ST_DPLL_MODE_MASK                                                                (0x0000000eU)
#define CM_IDLEST_DPLL_ABE_ST_DPLL_MODE_TRANSIENT                                                            (0U)
#define CM_IDLEST_DPLL_ABE_ST_DPLL_MODE_LP_STOP                                                              (1U)
#define CM_IDLEST_DPLL_ABE_ST_DPLL_MODE_FR_STOP                                                              (2U)
#define CM_IDLEST_DPLL_ABE_ST_DPLL_MODE_RESERVED1                                                            (3U)
#define CM_IDLEST_DPLL_ABE_ST_DPLL_MODE_RESERVED2                                                            (4U)
#define CM_IDLEST_DPLL_ABE_ST_DPLL_MODE_LP_BYP                                                               (5U)
#define CM_IDLEST_DPLL_ABE_ST_DPLL_MODE_FR_BYP                                                               (6U)
#define CM_IDLEST_DPLL_ABE_ST_DPLL_MODE_RESERVED3                                                            (7U)

#define CM_IDLEST_DPLL_ABE_ST_DPLL_INIT_SHIFT                                                               (4U)
#define CM_IDLEST_DPLL_ABE_ST_DPLL_INIT_MASK                                                                (0x00000010U)
#define CM_IDLEST_DPLL_ABE_ST_DPLL_INIT_DPLL_NOTINIT                                                         (0U)
#define CM_IDLEST_DPLL_ABE_ST_DPLL_INIT_DPLL_INIT                                                            (1U)

#define CM_AUTOIDLE_DPLL_ABE_AUTO_DPLL_MODE_SHIFT                                                           (0U)
#define CM_AUTOIDLE_DPLL_ABE_AUTO_DPLL_MODE_MASK                                                            (0x00000007U)
#define CM_AUTOIDLE_DPLL_ABE_AUTO_DPLL_MODE_AUTO_CTL_DISABLE                                                 (0U)
#define CM_AUTOIDLE_DPLL_ABE_AUTO_DPLL_MODE_AUTO_LP_STOP                                                     (1U)
#define CM_AUTOIDLE_DPLL_ABE_AUTO_DPLL_MODE_AUTO_FR_STOP                                                     (2U)
#define CM_AUTOIDLE_DPLL_ABE_AUTO_DPLL_MODE_RESERVED3                                                        (3U)
#define CM_AUTOIDLE_DPLL_ABE_AUTO_DPLL_MODE_RESERVED4                                                        (4U)
#define CM_AUTOIDLE_DPLL_ABE_AUTO_DPLL_MODE_AUTO_LP_BYP                                                      (5U)
#define CM_AUTOIDLE_DPLL_ABE_AUTO_DPLL_MODE_AUTO_FR_BYP                                                      (6U)
#define CM_AUTOIDLE_DPLL_ABE_AUTO_DPLL_MODE_RESERVED7                                                        (7U)

#define CM_AUTOIDLE_DPLL_ABE_RESERVED_SHIFT                                                                 (3U)
#define CM_AUTOIDLE_DPLL_ABE_RESERVED_MASK                                                                  (0xfffffff8U)

#define CM_CLKSEL_DPLL_ABE_DPLL_DIV_SHIFT                                                                   (0U)
#define CM_CLKSEL_DPLL_ABE_DPLL_DIV_MASK                                                                    (0x0000007fU)

#define CM_CLKSEL_DPLL_ABE_RESERVED_SHIFT                                                                   (7U)
#define CM_CLKSEL_DPLL_ABE_RESERVED_MASK                                                                    (0x00000080U)

#define CM_CLKSEL_DPLL_ABE_RESERVED1_SHIFT                                                                  (19U)
#define CM_CLKSEL_DPLL_ABE_RESERVED1_MASK                                                                   (0x00380000U)

#define CM_CLKSEL_DPLL_ABE_RESERVED2_SHIFT                                                                  (24U)
#define CM_CLKSEL_DPLL_ABE_RESERVED2_MASK                                                                   (0xff000000U)

#define CM_CLKSEL_DPLL_ABE_DPLL_BYP_CLKSEL_SHIFT                                                            (23U)
#define CM_CLKSEL_DPLL_ABE_DPLL_BYP_CLKSEL_MASK                                                             (0x00800000U)

#define CM_CLKSEL_DPLL_ABE_DPLL_MULT_SHIFT                                                                  (8U)
#define CM_CLKSEL_DPLL_ABE_DPLL_MULT_MASK                                                                   (0x0007ff00U)
#define CM_CLKSEL_DPLL_ABE_DPLL_MULT_RESERVED_0                                                              (0U)
#define CM_CLKSEL_DPLL_ABE_DPLL_MULT_RESERVED_1                                                              (1U)

#define CM_CLKSEL_DPLL_ABE_DCC_EN_SHIFT                                                                     (22U)
#define CM_CLKSEL_DPLL_ABE_DCC_EN_MASK                                                                      (0x00400000U)
#define CM_CLKSEL_DPLL_ABE_DCC_EN_DISABLED                                                                   (0U)

#define CM_DIV_M2_DPLL_ABE_DIVHS_SHIFT                                                                      (0U)
#define CM_DIV_M2_DPLL_ABE_DIVHS_MASK                                                                       (0x0000001fU)
#define CM_DIV_M2_DPLL_ABE_DIVHS_RESERVED                                                                    (0U)

#define CM_DIV_M2_DPLL_ABE_CLKST_SHIFT                                                                      (9U)
#define CM_DIV_M2_DPLL_ABE_CLKST_MASK                                                                       (0x00000200U)
#define CM_DIV_M2_DPLL_ABE_CLKST_CLK_ENABLED                                                                 (1U)
#define CM_DIV_M2_DPLL_ABE_CLKST_CLK_GATED                                                                   (0U)

#define CM_DIV_M2_DPLL_ABE_CLKX2ST_SHIFT                                                                    (11U)
#define CM_DIV_M2_DPLL_ABE_CLKX2ST_MASK                                                                     (0x00000800U)
#define CM_DIV_M2_DPLL_ABE_CLKX2ST_CLK_ENABLED                                                               (1U)
#define CM_DIV_M2_DPLL_ABE_CLKX2ST_CLK_GATED                                                                 (0U)

#define CM_DIV_M2_DPLL_ABE_RESERVED_SHIFT                                                                   (5U)
#define CM_DIV_M2_DPLL_ABE_RESERVED_MASK                                                                    (0x000001e0U)

#define CM_DIV_M2_DPLL_ABE_RESERVED1_SHIFT                                                                  (12U)
#define CM_DIV_M2_DPLL_ABE_RESERVED1_MASK                                                                   (0xfffff000U)

#define CM_DIV_M2_DPLL_ABE_RESERVED2_SHIFT                                                                  (10U)
#define CM_DIV_M2_DPLL_ABE_RESERVED2_MASK                                                                   (0x00000400U)

#define CM_DIV_M3_DPLL_ABE_DIVHS_SHIFT                                                                      (0U)
#define CM_DIV_M3_DPLL_ABE_DIVHS_MASK                                                                       (0x0000001fU)
#define CM_DIV_M3_DPLL_ABE_DIVHS_RESERVED                                                                    (0U)

#define CM_DIV_M3_DPLL_ABE_CLKST_SHIFT                                                                      (9U)
#define CM_DIV_M3_DPLL_ABE_CLKST_MASK                                                                       (0x00000200U)
#define CM_DIV_M3_DPLL_ABE_CLKST_CLK_ENABLED                                                                 (1U)
#define CM_DIV_M3_DPLL_ABE_CLKST_CLK_GATED                                                                   (0U)

#define CM_DIV_M3_DPLL_ABE_RESERVED_SHIFT                                                                   (5U)
#define CM_DIV_M3_DPLL_ABE_RESERVED_MASK                                                                    (0x000001e0U)

#define CM_DIV_M3_DPLL_ABE_RESERVED1_SHIFT                                                                  (10U)
#define CM_DIV_M3_DPLL_ABE_RESERVED1_MASK                                                                   (0xfffffc00U)

#define CM_SSC_DELTAMSTEP_DPLL_ABE_RESERVED_SHIFT                                                           (20U)
#define CM_SSC_DELTAMSTEP_DPLL_ABE_RESERVED_MASK                                                            (0xfff00000U)

#define CM_SSC_DELTAMSTEP_DPLL_ABE_DELTAMSTEP_SHIFT                                                         (0U)
#define CM_SSC_DELTAMSTEP_DPLL_ABE_DELTAMSTEP_MASK                                                          (0x000fffffU)

#define CM_SSC_MODFREQDIV_DPLL_ABE_MODFREQDIV_MANTISSA_SHIFT                                                (0U)
#define CM_SSC_MODFREQDIV_DPLL_ABE_MODFREQDIV_MANTISSA_MASK                                                 (0x0000007fU)

#define CM_SSC_MODFREQDIV_DPLL_ABE_MODFREQDIV_EXPONENT_SHIFT                                                (8U)
#define CM_SSC_MODFREQDIV_DPLL_ABE_MODFREQDIV_EXPONENT_MASK                                                 (0x00000700U)

#define CM_SSC_MODFREQDIV_DPLL_ABE_RESERVED_SHIFT                                                           (7U)
#define CM_SSC_MODFREQDIV_DPLL_ABE_RESERVED_MASK                                                            (0x00000080U)

#define CM_SSC_MODFREQDIV_DPLL_ABE_RESERVED1_SHIFT                                                          (11U)
#define CM_SSC_MODFREQDIV_DPLL_ABE_RESERVED1_MASK                                                           (0xfffff800U)

#define CM_CLKMODE_DPLL_DDR_DPLL_EN_SHIFT                                                                   (0U)
#define CM_CLKMODE_DPLL_DDR_DPLL_EN_MASK                                                                    (0x00000007U)
#define CM_CLKMODE_DPLL_DDR_DPLL_EN_RESERVED                                                                 (0U)
#define CM_CLKMODE_DPLL_DDR_DPLL_EN_RESERVED1                                                                (1U)
#define CM_CLKMODE_DPLL_DDR_DPLL_EN_RESERVED2                                                                (2U)
#define CM_CLKMODE_DPLL_DDR_DPLL_EN_RESERVED3                                                                (3U)
#define CM_CLKMODE_DPLL_DDR_DPLL_EN_RESERVED4                                                                (4U)
#define CM_CLKMODE_DPLL_DDR_DPLL_EN_DPLL_LP_BYP_MODE                                                         (5U)
#define CM_CLKMODE_DPLL_DDR_DPLL_EN_DPLL_FR_BYP_MODE                                                         (6U)
#define CM_CLKMODE_DPLL_DDR_DPLL_EN_DPLL_LOCK_MODE                                                           (7U)

#define CM_CLKMODE_DPLL_DDR_DPLL_RAMP_LEVEL_SHIFT                                                           (3U)
#define CM_CLKMODE_DPLL_DDR_DPLL_RAMP_LEVEL_MASK                                                            (0x00000018U)
#define CM_CLKMODE_DPLL_DDR_DPLL_RAMP_LEVEL_RAMP_DISABLE                                                     (0U)
#define CM_CLKMODE_DPLL_DDR_DPLL_RAMP_LEVEL_RAMP_ALGO1                                                       (1U)
#define CM_CLKMODE_DPLL_DDR_DPLL_RAMP_LEVEL_RAMP_ALGO2                                                       (2U)
#define CM_CLKMODE_DPLL_DDR_DPLL_RAMP_LEVEL_RESERVED                                                         (3U)

#define CM_CLKMODE_DPLL_DDR_DPLL_RAMP_RATE_SHIFT                                                            (5U)
#define CM_CLKMODE_DPLL_DDR_DPLL_RAMP_RATE_MASK                                                             (0x000000e0U)
#define CM_CLKMODE_DPLL_DDR_DPLL_RAMP_RATE_REFCLKX2                                                          (0U)
#define CM_CLKMODE_DPLL_DDR_DPLL_RAMP_RATE_REFCLKX4                                                          (1U)
#define CM_CLKMODE_DPLL_DDR_DPLL_RAMP_RATE_REFCLKX8                                                          (2U)
#define CM_CLKMODE_DPLL_DDR_DPLL_RAMP_RATE_REFCLKX16                                                         (3U)
#define CM_CLKMODE_DPLL_DDR_DPLL_RAMP_RATE_REFCLKX32                                                         (4U)
#define CM_CLKMODE_DPLL_DDR_DPLL_RAMP_RATE_REFCLKX64                                                         (5U)
#define CM_CLKMODE_DPLL_DDR_DPLL_RAMP_RATE_REFCLKX128                                                        (6U)
#define CM_CLKMODE_DPLL_DDR_DPLL_RAMP_RATE_REFCLKX512                                                        (7U)

#define CM_CLKMODE_DPLL_DDR_DPLL_DRIFTGUARD_EN_SHIFT                                                        (8U)
#define CM_CLKMODE_DPLL_DDR_DPLL_DRIFTGUARD_EN_MASK                                                         (0x00000100U)
#define CM_CLKMODE_DPLL_DDR_DPLL_DRIFTGUARD_EN_ENABLED                                                       (1U)
#define CM_CLKMODE_DPLL_DDR_DPLL_DRIFTGUARD_EN_DIASBLED                                                      (0U)

#define CM_CLKMODE_DPLL_DDR_DPLL_RELOCK_RAMP_EN_SHIFT                                                       (9U)
#define CM_CLKMODE_DPLL_DDR_DPLL_RELOCK_RAMP_EN_MASK                                                        (0x00000200U)

#define CM_CLKMODE_DPLL_DDR_DPLL_LPMODE_EN_SHIFT                                                            (10U)
#define CM_CLKMODE_DPLL_DDR_DPLL_LPMODE_EN_MASK                                                             (0x00000400U)
#define CM_CLKMODE_DPLL_DDR_DPLL_LPMODE_EN_DISABLED                                                          (0U)
#define CM_CLKMODE_DPLL_DDR_DPLL_LPMODE_EN_ENABLED                                                           (1U)

#define CM_CLKMODE_DPLL_DDR_DPLL_REGM4XEN_SHIFT                                                             (11U)
#define CM_CLKMODE_DPLL_DDR_DPLL_REGM4XEN_MASK                                                              (0x00000800U)
#define CM_CLKMODE_DPLL_DDR_DPLL_REGM4XEN_DISABLED                                                           (0U)

#define CM_CLKMODE_DPLL_DDR_DPLL_SSC_EN_SHIFT                                                               (12U)
#define CM_CLKMODE_DPLL_DDR_DPLL_SSC_EN_MASK                                                                (0x00001000U)
#define CM_CLKMODE_DPLL_DDR_DPLL_SSC_EN_DISABLED                                                             (0U)
#define CM_CLKMODE_DPLL_DDR_DPLL_SSC_EN_ENABLED                                                              (1U)

#define CM_CLKMODE_DPLL_DDR_DPLL_SSC_ACK_SHIFT                                                              (13U)
#define CM_CLKMODE_DPLL_DDR_DPLL_SSC_ACK_MASK                                                               (0x00002000U)
#define CM_CLKMODE_DPLL_DDR_DPLL_SSC_ACK_DISABLED                                                            (0U)
#define CM_CLKMODE_DPLL_DDR_DPLL_SSC_ACK_ENABLED                                                             (1U)

#define CM_CLKMODE_DPLL_DDR_DPLL_SSC_DOWNSPREAD_SHIFT                                                       (14U)
#define CM_CLKMODE_DPLL_DDR_DPLL_SSC_DOWNSPREAD_MASK                                                        (0x00004000U)
#define CM_CLKMODE_DPLL_DDR_DPLL_SSC_DOWNSPREAD_FULL_SPREAD                                                  (0U)
#define CM_CLKMODE_DPLL_DDR_DPLL_SSC_DOWNSPREAD_LOW_SPREAD                                                   (1U)

#define CM_CLKMODE_DPLL_DDR_DPLL_SSC_TYPE_SHIFT                                                             (15U)
#define CM_CLKMODE_DPLL_DDR_DPLL_SSC_TYPE_MASK                                                              (0x00008000U)
#define CM_CLKMODE_DPLL_DDR_DPLL_SSC_TYPE_TRIANGULAR                                                         (0U)
#define CM_CLKMODE_DPLL_DDR_DPLL_SSC_TYPE_SQUARE                                                             (1U)

#define CM_CLKMODE_DPLL_DDR_RESERVED_SHIFT                                                                  (16U)
#define CM_CLKMODE_DPLL_DDR_RESERVED_MASK                                                                   (0xffff0000U)

#define CM_IDLEST_DPLL_DDR_ST_DPLL_CLK_SHIFT                                                                (0U)
#define CM_IDLEST_DPLL_DDR_ST_DPLL_CLK_MASK                                                                 (0x00000001U)
#define CM_IDLEST_DPLL_DDR_ST_DPLL_CLK_DPLL_UNLOCKED                                                         (0U)
#define CM_IDLEST_DPLL_DDR_ST_DPLL_CLK_DPLL_LOCKED                                                           (1U)

#define CM_IDLEST_DPLL_DDR_RESERVED_SHIFT                                                                   (5U)
#define CM_IDLEST_DPLL_DDR_RESERVED_MASK                                                                    (0xffffffe0U)

#define CM_IDLEST_DPLL_DDR_ST_DPLL_MODE_SHIFT                                                               (1U)
#define CM_IDLEST_DPLL_DDR_ST_DPLL_MODE_MASK                                                                (0x0000000eU)
#define CM_IDLEST_DPLL_DDR_ST_DPLL_MODE_TRANSIENT                                                            (0U)
#define CM_IDLEST_DPLL_DDR_ST_DPLL_MODE_LP_STOP                                                              (1U)
#define CM_IDLEST_DPLL_DDR_ST_DPLL_MODE_FR_STOP                                                              (2U)
#define CM_IDLEST_DPLL_DDR_ST_DPLL_MODE_RESERVED1                                                            (3U)
#define CM_IDLEST_DPLL_DDR_ST_DPLL_MODE_RESERVED2                                                            (4U)
#define CM_IDLEST_DPLL_DDR_ST_DPLL_MODE_LP_BYP                                                               (5U)
#define CM_IDLEST_DPLL_DDR_ST_DPLL_MODE_FR_BYP                                                               (6U)
#define CM_IDLEST_DPLL_DDR_ST_DPLL_MODE_RESERVED3                                                            (7U)

#define CM_IDLEST_DPLL_DDR_ST_DPLL_INIT_SHIFT                                                               (4U)
#define CM_IDLEST_DPLL_DDR_ST_DPLL_INIT_MASK                                                                (0x00000010U)
#define CM_IDLEST_DPLL_DDR_ST_DPLL_INIT_DPLL_NOTINIT                                                         (0U)
#define CM_IDLEST_DPLL_DDR_ST_DPLL_INIT_DPLL_INIT                                                            (1U)

#define CM_AUTOIDLE_DPLL_DDR_AUTO_DPLL_MODE_SHIFT                                                           (0U)
#define CM_AUTOIDLE_DPLL_DDR_AUTO_DPLL_MODE_MASK                                                            (0x00000007U)
#define CM_AUTOIDLE_DPLL_DDR_AUTO_DPLL_MODE_AUTO_CTL_DISABLE                                                 (0U)
#define CM_AUTOIDLE_DPLL_DDR_AUTO_DPLL_MODE_AUTO_LP_STOP                                                     (1U)
#define CM_AUTOIDLE_DPLL_DDR_AUTO_DPLL_MODE_AUTO_FR_STOP                                                     (2U)
#define CM_AUTOIDLE_DPLL_DDR_AUTO_DPLL_MODE_RESERVED3                                                        (3U)
#define CM_AUTOIDLE_DPLL_DDR_AUTO_DPLL_MODE_RESERVED4                                                        (4U)
#define CM_AUTOIDLE_DPLL_DDR_AUTO_DPLL_MODE_AUTO_LP_BYP                                                      (5U)
#define CM_AUTOIDLE_DPLL_DDR_AUTO_DPLL_MODE_AUTO_FR_BYP                                                      (6U)
#define CM_AUTOIDLE_DPLL_DDR_AUTO_DPLL_MODE_RESERVED7                                                        (7U)

#define CM_AUTOIDLE_DPLL_DDR_RESERVED_SHIFT                                                                 (3U)
#define CM_AUTOIDLE_DPLL_DDR_RESERVED_MASK                                                                  (0xfffffff8U)

#define CM_CLKSEL_DPLL_DDR_DPLL_DIV_SHIFT                                                                   (0U)
#define CM_CLKSEL_DPLL_DDR_DPLL_DIV_MASK                                                                    (0x0000007fU)

#define CM_CLKSEL_DPLL_DDR_RESERVED_SHIFT                                                                   (7U)
#define CM_CLKSEL_DPLL_DDR_RESERVED_MASK                                                                    (0x00000080U)

#define CM_CLKSEL_DPLL_DDR_RESERVED1_SHIFT                                                                  (19U)
#define CM_CLKSEL_DPLL_DDR_RESERVED1_MASK                                                                   (0x00380000U)

#define CM_CLKSEL_DPLL_DDR_RESERVED2_SHIFT                                                                  (24U)
#define CM_CLKSEL_DPLL_DDR_RESERVED2_MASK                                                                   (0xff000000U)

#define CM_CLKSEL_DPLL_DDR_DPLL_MULT_SHIFT                                                                  (8U)
#define CM_CLKSEL_DPLL_DDR_DPLL_MULT_MASK                                                                   (0x0007ff00U)
#define CM_CLKSEL_DPLL_DDR_DPLL_MULT_RESERVED_0                                                              (0U)
#define CM_CLKSEL_DPLL_DDR_DPLL_MULT_RESERVED_1                                                              (1U)

#define CM_CLKSEL_DPLL_DDR_DCC_EN_SHIFT                                                                     (22U)
#define CM_CLKSEL_DPLL_DDR_DCC_EN_MASK                                                                      (0x00400000U)
#define CM_CLKSEL_DPLL_DDR_DCC_EN_DISABLED                                                                   (0U)
#define CM_CLKSEL_DPLL_DDR_DCC_EN_ENABLED                                                                    (1U)

#define CM_CLKSEL_DPLL_DDR_DPLL_BYP_CLKSEL_SHIFT                                                            (23U)
#define CM_CLKSEL_DPLL_DDR_DPLL_BYP_CLKSEL_MASK                                                             (0x00800000U)

#define CM_DIV_M2_DPLL_DDR_DIVHS_SHIFT                                                                      (0U)
#define CM_DIV_M2_DPLL_DDR_DIVHS_MASK                                                                       (0x0000001fU)
#define CM_DIV_M2_DPLL_DDR_DIVHS_RESERVED                                                                    (0U)

#define CM_DIV_M2_DPLL_DDR_CLKST_SHIFT                                                                      (9U)
#define CM_DIV_M2_DPLL_DDR_CLKST_MASK                                                                       (0x00000200U)
#define CM_DIV_M2_DPLL_DDR_CLKST_CLK_ENABLED                                                                 (1U)
#define CM_DIV_M2_DPLL_DDR_CLKST_CLK_GATED                                                                   (0U)

#define CM_DIV_M2_DPLL_DDR_RESERVED_SHIFT                                                                   (5U)
#define CM_DIV_M2_DPLL_DDR_RESERVED_MASK                                                                    (0x000001e0U)

#define CM_DIV_M2_DPLL_DDR_RESERVED1_SHIFT                                                                  (10U)
#define CM_DIV_M2_DPLL_DDR_RESERVED1_MASK                                                                   (0xfffffc00U)

#define CM_DIV_H11_DPLL_DDR_DIVHS_SHIFT                                                                     (0U)
#define CM_DIV_H11_DPLL_DDR_DIVHS_MASK                                                                      (0x0000003fU)
#define CM_DIV_H11_DPLL_DDR_DIVHS_RESERVED                                                                   (0U)

#define CM_DIV_H11_DPLL_DDR_CLKST_SHIFT                                                                     (9U)
#define CM_DIV_H11_DPLL_DDR_CLKST_MASK                                                                      (0x00000200U)
#define CM_DIV_H11_DPLL_DDR_CLKST_CLK_ENABLED                                                                (1U)
#define CM_DIV_H11_DPLL_DDR_CLKST_CLK_GATED                                                                  (0U)

#define CM_DIV_H11_DPLL_DDR_RESERVED_SHIFT                                                                  (6U)
#define CM_DIV_H11_DPLL_DDR_RESERVED_MASK                                                                   (0x000001c0U)

#define CM_DIV_H11_DPLL_DDR_RESERVED1_SHIFT                                                                 (10U)
#define CM_DIV_H11_DPLL_DDR_RESERVED1_MASK                                                                  (0xfffffc00U)

#define CM_SSC_DELTAMSTEP_DPLL_DDR_DELTAMSTEP_SHIFT                                                         (0U)
#define CM_SSC_DELTAMSTEP_DPLL_DDR_DELTAMSTEP_MASK                                                          (0x000fffffU)

#define CM_SSC_DELTAMSTEP_DPLL_DDR_RESERVED_SHIFT                                                           (20U)
#define CM_SSC_DELTAMSTEP_DPLL_DDR_RESERVED_MASK                                                            (0xfff00000U)

#define CM_SSC_MODFREQDIV_DPLL_DDR_MODFREQDIV_MANTISSA_SHIFT                                                (0U)
#define CM_SSC_MODFREQDIV_DPLL_DDR_MODFREQDIV_MANTISSA_MASK                                                 (0x0000007fU)

#define CM_SSC_MODFREQDIV_DPLL_DDR_MODFREQDIV_EXPONENT_SHIFT                                                (8U)
#define CM_SSC_MODFREQDIV_DPLL_DDR_MODFREQDIV_EXPONENT_MASK                                                 (0x00000700U)

#define CM_SSC_MODFREQDIV_DPLL_DDR_RESERVED_SHIFT                                                           (7U)
#define CM_SSC_MODFREQDIV_DPLL_DDR_RESERVED_MASK                                                            (0x00000080U)

#define CM_SSC_MODFREQDIV_DPLL_DDR_RESERVED1_SHIFT                                                          (11U)
#define CM_SSC_MODFREQDIV_DPLL_DDR_RESERVED1_MASK                                                           (0xfffff800U)

#define CM_CLKMODE_DPLL_DSP_DPLL_EN_SHIFT                                                                   (0U)
#define CM_CLKMODE_DPLL_DSP_DPLL_EN_MASK                                                                    (0x00000007U)
#define CM_CLKMODE_DPLL_DSP_DPLL_EN_RESERVED                                                                 (0U)
#define CM_CLKMODE_DPLL_DSP_DPLL_EN_RESERVED1                                                                (1U)
#define CM_CLKMODE_DPLL_DSP_DPLL_EN_RESERVED2                                                                (2U)
#define CM_CLKMODE_DPLL_DSP_DPLL_EN_RESERVED3                                                                (3U)
#define CM_CLKMODE_DPLL_DSP_DPLL_EN_RESERVED4                                                                (4U)
#define CM_CLKMODE_DPLL_DSP_DPLL_EN_DPLL_LP_BYP_MODE                                                         (5U)
#define CM_CLKMODE_DPLL_DSP_DPLL_EN_DPLL_FR_BYP_MODE                                                         (6U)
#define CM_CLKMODE_DPLL_DSP_DPLL_EN_DPLL_LOCK_MODE                                                           (7U)

#define CM_CLKMODE_DPLL_DSP_DPLL_RAMP_LEVEL_SHIFT                                                           (3U)
#define CM_CLKMODE_DPLL_DSP_DPLL_RAMP_LEVEL_MASK                                                            (0x00000018U)
#define CM_CLKMODE_DPLL_DSP_DPLL_RAMP_LEVEL_RAMP_DISABLE                                                     (0U)
#define CM_CLKMODE_DPLL_DSP_DPLL_RAMP_LEVEL_RAMP_ALGO1                                                       (1U)
#define CM_CLKMODE_DPLL_DSP_DPLL_RAMP_LEVEL_RAMP_ALGO2                                                       (2U)
#define CM_CLKMODE_DPLL_DSP_DPLL_RAMP_LEVEL_RESERVED                                                         (3U)

#define CM_CLKMODE_DPLL_DSP_DPLL_RAMP_RATE_SHIFT                                                            (5U)
#define CM_CLKMODE_DPLL_DSP_DPLL_RAMP_RATE_MASK                                                             (0x000000e0U)
#define CM_CLKMODE_DPLL_DSP_DPLL_RAMP_RATE_REFCLKX2                                                          (0U)
#define CM_CLKMODE_DPLL_DSP_DPLL_RAMP_RATE_REFCLKX4                                                          (1U)
#define CM_CLKMODE_DPLL_DSP_DPLL_RAMP_RATE_REFCLKX8                                                          (2U)
#define CM_CLKMODE_DPLL_DSP_DPLL_RAMP_RATE_REFCLKX16                                                         (3U)
#define CM_CLKMODE_DPLL_DSP_DPLL_RAMP_RATE_REFCLKX32                                                         (4U)
#define CM_CLKMODE_DPLL_DSP_DPLL_RAMP_RATE_REFCLKX64                                                         (5U)
#define CM_CLKMODE_DPLL_DSP_DPLL_RAMP_RATE_REFCLKX128                                                        (6U)
#define CM_CLKMODE_DPLL_DSP_DPLL_RAMP_RATE_REFCLKX512                                                        (7U)

#define CM_CLKMODE_DPLL_DSP_DPLL_DRIFTGUARD_EN_SHIFT                                                        (8U)
#define CM_CLKMODE_DPLL_DSP_DPLL_DRIFTGUARD_EN_MASK                                                         (0x00000100U)
#define CM_CLKMODE_DPLL_DSP_DPLL_DRIFTGUARD_EN_ENABLED                                                       (1U)
#define CM_CLKMODE_DPLL_DSP_DPLL_DRIFTGUARD_EN_DIASBLED                                                      (0U)

#define CM_CLKMODE_DPLL_DSP_DPLL_RELOCK_RAMP_EN_SHIFT                                                       (9U)
#define CM_CLKMODE_DPLL_DSP_DPLL_RELOCK_RAMP_EN_MASK                                                        (0x00000200U)

#define CM_CLKMODE_DPLL_DSP_DPLL_LPMODE_EN_SHIFT                                                            (10U)
#define CM_CLKMODE_DPLL_DSP_DPLL_LPMODE_EN_MASK                                                             (0x00000400U)
#define CM_CLKMODE_DPLL_DSP_DPLL_LPMODE_EN_DISABLED                                                          (0U)
#define CM_CLKMODE_DPLL_DSP_DPLL_LPMODE_EN_ENABLED                                                           (1U)

#define CM_CLKMODE_DPLL_DSP_DPLL_REGM4XEN_SHIFT                                                             (11U)
#define CM_CLKMODE_DPLL_DSP_DPLL_REGM4XEN_MASK                                                              (0x00000800U)
#define CM_CLKMODE_DPLL_DSP_DPLL_REGM4XEN_DISABLED                                                           (0U)

#define CM_CLKMODE_DPLL_DSP_DPLL_SSC_EN_SHIFT                                                               (12U)
#define CM_CLKMODE_DPLL_DSP_DPLL_SSC_EN_MASK                                                                (0x00001000U)
#define CM_CLKMODE_DPLL_DSP_DPLL_SSC_EN_DISABLED                                                             (0U)
#define CM_CLKMODE_DPLL_DSP_DPLL_SSC_EN_ENABLED                                                              (1U)

#define CM_CLKMODE_DPLL_DSP_DPLL_SSC_ACK_SHIFT                                                              (13U)
#define CM_CLKMODE_DPLL_DSP_DPLL_SSC_ACK_MASK                                                               (0x00002000U)
#define CM_CLKMODE_DPLL_DSP_DPLL_SSC_ACK_DISABLED                                                            (0U)
#define CM_CLKMODE_DPLL_DSP_DPLL_SSC_ACK_ENABLED                                                             (1U)

#define CM_CLKMODE_DPLL_DSP_DPLL_SSC_DOWNSPREAD_SHIFT                                                       (14U)
#define CM_CLKMODE_DPLL_DSP_DPLL_SSC_DOWNSPREAD_MASK                                                        (0x00004000U)
#define CM_CLKMODE_DPLL_DSP_DPLL_SSC_DOWNSPREAD_FULL_SPREAD                                                  (0U)
#define CM_CLKMODE_DPLL_DSP_DPLL_SSC_DOWNSPREAD_LOW_SPREAD                                                   (1U)

#define CM_CLKMODE_DPLL_DSP_DPLL_SSC_TYPE_SHIFT                                                             (15U)
#define CM_CLKMODE_DPLL_DSP_DPLL_SSC_TYPE_MASK                                                              (0x00008000U)
#define CM_CLKMODE_DPLL_DSP_DPLL_SSC_TYPE_TRIANGULAR                                                         (0U)
#define CM_CLKMODE_DPLL_DSP_DPLL_SSC_TYPE_SQUARE                                                             (1U)

#define CM_CLKMODE_DPLL_DSP_RESERVED_SHIFT                                                                  (16U)
#define CM_CLKMODE_DPLL_DSP_RESERVED_MASK                                                                   (0xffff0000U)

#define CM_IDLEST_DPLL_DSP_ST_DPLL_CLK_SHIFT                                                                (0U)
#define CM_IDLEST_DPLL_DSP_ST_DPLL_CLK_MASK                                                                 (0x00000001U)
#define CM_IDLEST_DPLL_DSP_ST_DPLL_CLK_DPLL_UNLOCKED                                                         (0U)
#define CM_IDLEST_DPLL_DSP_ST_DPLL_CLK_DPLL_LOCKED                                                           (1U)

#define CM_IDLEST_DPLL_DSP_RESERVED_SHIFT                                                                   (5U)
#define CM_IDLEST_DPLL_DSP_RESERVED_MASK                                                                    (0xffffffe0U)

#define CM_IDLEST_DPLL_DSP_ST_DPLL_MODE_SHIFT                                                               (1U)
#define CM_IDLEST_DPLL_DSP_ST_DPLL_MODE_MASK                                                                (0x0000000eU)
#define CM_IDLEST_DPLL_DSP_ST_DPLL_MODE_TRANSIENT                                                            (0U)
#define CM_IDLEST_DPLL_DSP_ST_DPLL_MODE_LP_STOP                                                              (1U)
#define CM_IDLEST_DPLL_DSP_ST_DPLL_MODE_FR_STOP                                                              (2U)
#define CM_IDLEST_DPLL_DSP_ST_DPLL_MODE_RESERVED1                                                            (3U)
#define CM_IDLEST_DPLL_DSP_ST_DPLL_MODE_RESERVED2                                                            (4U)
#define CM_IDLEST_DPLL_DSP_ST_DPLL_MODE_LP_BYP                                                               (5U)
#define CM_IDLEST_DPLL_DSP_ST_DPLL_MODE_FR_BYP                                                               (6U)
#define CM_IDLEST_DPLL_DSP_ST_DPLL_MODE_RESERVED3                                                            (7U)

#define CM_IDLEST_DPLL_DSP_ST_DPLL_INIT_SHIFT                                                               (4U)
#define CM_IDLEST_DPLL_DSP_ST_DPLL_INIT_MASK                                                                (0x00000010U)
#define CM_IDLEST_DPLL_DSP_ST_DPLL_INIT_DPLL_NOTINIT                                                         (0U)
#define CM_IDLEST_DPLL_DSP_ST_DPLL_INIT_DPLL_INIT                                                            (1U)

#define CM_AUTOIDLE_DPLL_DSP_AUTO_DPLL_MODE_SHIFT                                                           (0U)
#define CM_AUTOIDLE_DPLL_DSP_AUTO_DPLL_MODE_MASK                                                            (0x00000007U)
#define CM_AUTOIDLE_DPLL_DSP_AUTO_DPLL_MODE_AUTO_CTL_DISABLE                                                 (0U)
#define CM_AUTOIDLE_DPLL_DSP_AUTO_DPLL_MODE_AUTO_LP_STOP                                                     (1U)
#define CM_AUTOIDLE_DPLL_DSP_AUTO_DPLL_MODE_AUTO_FR_STOP                                                     (2U)
#define CM_AUTOIDLE_DPLL_DSP_AUTO_DPLL_MODE_RESERVED3                                                        (3U)
#define CM_AUTOIDLE_DPLL_DSP_AUTO_DPLL_MODE_RESERVED4                                                        (4U)
#define CM_AUTOIDLE_DPLL_DSP_AUTO_DPLL_MODE_AUTO_LP_BYP                                                      (5U)
#define CM_AUTOIDLE_DPLL_DSP_AUTO_DPLL_MODE_AUTO_FR_BYP                                                      (6U)
#define CM_AUTOIDLE_DPLL_DSP_AUTO_DPLL_MODE_RESERVED7                                                        (7U)

#define CM_AUTOIDLE_DPLL_DSP_RESERVED_SHIFT                                                                 (3U)
#define CM_AUTOIDLE_DPLL_DSP_RESERVED_MASK                                                                  (0xfffffff8U)

#define CM_CLKSEL_DPLL_DSP_DPLL_DIV_SHIFT                                                                   (0U)
#define CM_CLKSEL_DPLL_DSP_DPLL_DIV_MASK                                                                    (0x0000007fU)

#define CM_CLKSEL_DPLL_DSP_RESERVED_SHIFT                                                                   (7U)
#define CM_CLKSEL_DPLL_DSP_RESERVED_MASK                                                                    (0x00000080U)

#define CM_CLKSEL_DPLL_DSP_RESERVED1_SHIFT                                                                  (19U)
#define CM_CLKSEL_DPLL_DSP_RESERVED1_MASK                                                                   (0x00380000U)

#define CM_CLKSEL_DPLL_DSP_RESERVED2_SHIFT                                                                  (24U)
#define CM_CLKSEL_DPLL_DSP_RESERVED2_MASK                                                                   (0xff000000U)

#define CM_CLKSEL_DPLL_DSP_DPLL_BYP_CLKSEL_SHIFT                                                            (23U)
#define CM_CLKSEL_DPLL_DSP_DPLL_BYP_CLKSEL_MASK                                                             (0x00800000U)

#define CM_CLKSEL_DPLL_DSP_DPLL_MULT_SHIFT                                                                  (8U)
#define CM_CLKSEL_DPLL_DSP_DPLL_MULT_MASK                                                                   (0x0007ff00U)
#define CM_CLKSEL_DPLL_DSP_DPLL_MULT_RESERVED_0                                                              (0U)
#define CM_CLKSEL_DPLL_DSP_DPLL_MULT_RESERVED_1                                                              (1U)

#define CM_CLKSEL_DPLL_DSP_DCC_EN_SHIFT                                                                     (22U)
#define CM_CLKSEL_DPLL_DSP_DCC_EN_MASK                                                                      (0x00400000U)
#define CM_CLKSEL_DPLL_DSP_DCC_EN_DISABLED                                                                   (0U)

#define CM_DIV_M2_DPLL_DSP_DIVHS_SHIFT                                                                      (0U)
#define CM_DIV_M2_DPLL_DSP_DIVHS_MASK                                                                       (0x0000001fU)
#define CM_DIV_M2_DPLL_DSP_DIVHS_RESERVED                                                                    (0U)

#define CM_DIV_M2_DPLL_DSP_CLKST_SHIFT                                                                      (9U)
#define CM_DIV_M2_DPLL_DSP_CLKST_MASK                                                                       (0x00000200U)
#define CM_DIV_M2_DPLL_DSP_CLKST_CLK_ENABLED                                                                 (1U)
#define CM_DIV_M2_DPLL_DSP_CLKST_CLK_GATED                                                                   (0U)

#define CM_DIV_M2_DPLL_DSP_RESERVED_SHIFT                                                                   (5U)
#define CM_DIV_M2_DPLL_DSP_RESERVED_MASK                                                                    (0x000001e0U)

#define CM_DIV_M2_DPLL_DSP_RESERVED1_SHIFT                                                                  (10U)
#define CM_DIV_M2_DPLL_DSP_RESERVED1_MASK                                                                   (0xfffffc00U)

#define CM_DIV_M3_DPLL_DSP_DIVHS_SHIFT                                                                      (0U)
#define CM_DIV_M3_DPLL_DSP_DIVHS_MASK                                                                       (0x0000001fU)
#define CM_DIV_M3_DPLL_DSP_DIVHS_RESERVED                                                                    (0U)

#define CM_DIV_M3_DPLL_DSP_CLKST_SHIFT                                                                      (9U)
#define CM_DIV_M3_DPLL_DSP_CLKST_MASK                                                                       (0x00000200U)
#define CM_DIV_M3_DPLL_DSP_CLKST_CLK_ENABLED                                                                 (1U)
#define CM_DIV_M3_DPLL_DSP_CLKST_CLK_GATED                                                                   (0U)

#define CM_DIV_M3_DPLL_DSP_RESERVED_SHIFT                                                                   (5U)
#define CM_DIV_M3_DPLL_DSP_RESERVED_MASK                                                                    (0x000001e0U)

#define CM_DIV_M3_DPLL_DSP_RESERVED1_SHIFT                                                                  (10U)
#define CM_DIV_M3_DPLL_DSP_RESERVED1_MASK                                                                   (0xfffffc00U)

#define CM_SSC_DELTAMSTEP_DPLL_DSP_RESERVED_SHIFT                                                           (20U)
#define CM_SSC_DELTAMSTEP_DPLL_DSP_RESERVED_MASK                                                            (0xfff00000U)

#define CM_SSC_DELTAMSTEP_DPLL_DSP_DELTAMSTEP_SHIFT                                                         (0U)
#define CM_SSC_DELTAMSTEP_DPLL_DSP_DELTAMSTEP_MASK                                                          (0x000fffffU)

#define CM_SSC_MODFREQDIV_DPLL_DSP_MODFREQDIV_MANTISSA_SHIFT                                                (0U)
#define CM_SSC_MODFREQDIV_DPLL_DSP_MODFREQDIV_MANTISSA_MASK                                                 (0x0000007fU)

#define CM_SSC_MODFREQDIV_DPLL_DSP_MODFREQDIV_EXPONENT_SHIFT                                                (8U)
#define CM_SSC_MODFREQDIV_DPLL_DSP_MODFREQDIV_EXPONENT_MASK                                                 (0x00000700U)

#define CM_SSC_MODFREQDIV_DPLL_DSP_RESERVED_SHIFT                                                           (7U)
#define CM_SSC_MODFREQDIV_DPLL_DSP_RESERVED_MASK                                                            (0x00000080U)

#define CM_SSC_MODFREQDIV_DPLL_DSP_RESERVED1_SHIFT                                                          (11U)
#define CM_SSC_MODFREQDIV_DPLL_DSP_RESERVED1_MASK                                                           (0xfffff800U)

#define CM_BYPCLK_DPLL_DSP_CLKSEL_SHIFT                                                                     (0U)
#define CM_BYPCLK_DPLL_DSP_CLKSEL_MASK                                                                      (0x00000003U)
#define CM_BYPCLK_DPLL_DSP_CLKSEL_CORE_X2_CLK_DIV_1                                                          (0U)
#define CM_BYPCLK_DPLL_DSP_CLKSEL_CORE_X2_CLK_DIV_2                                                          (1U)
#define CM_BYPCLK_DPLL_DSP_CLKSEL_CORE_X2_CLK_DIV_4                                                          (2U)
#define CM_BYPCLK_DPLL_DSP_CLKSEL_CORE_X2_CLK_DIV_8                                                          (3U)

#define CM_BYPCLK_DPLL_DSP_RESERVED_SHIFT                                                                   (2U)
#define CM_BYPCLK_DPLL_DSP_RESERVED_MASK                                                                    (0xfffffffcU)

#define CM_SHADOW_FREQ_CONFIG1_DPLL_DDR_M2_DIV_SHIFT                                                        (11U)
#define CM_SHADOW_FREQ_CONFIG1_DPLL_DDR_M2_DIV_MASK                                                         (0x0000f800U)
#define CM_SHADOW_FREQ_CONFIG1_DPLL_DDR_M2_DIV_RESERVED                                                      (0U)

#define CM_SHADOW_FREQ_CONFIG1_FREQ_UPDATE_SHIFT                                                            (0U)
#define CM_SHADOW_FREQ_CONFIG1_FREQ_UPDATE_MASK                                                             (0x00000001U)

#define CM_SHADOW_FREQ_CONFIG1_DLL_OVERRIDE_SHIFT                                                           (2U)
#define CM_SHADOW_FREQ_CONFIG1_DLL_OVERRIDE_MASK                                                            (0x00000004U)
#define CM_SHADOW_FREQ_CONFIG1_DLL_OVERRIDE_NO_OVR                                                           (0U)
#define CM_SHADOW_FREQ_CONFIG1_DLL_OVERRIDE_OVR                                                              (1U)

#define CM_SHADOW_FREQ_CONFIG1_DLL_RESET_SHIFT                                                              (3U)
#define CM_SHADOW_FREQ_CONFIG1_DLL_RESET_MASK                                                               (0x00000008U)
#define CM_SHADOW_FREQ_CONFIG1_DLL_RESET_NO_RESET                                                            (0U)
#define CM_SHADOW_FREQ_CONFIG1_DLL_RESET_RESET                                                               (1U)

#define CM_SHADOW_FREQ_CONFIG1_RESERVED2_SHIFT                                                              (1U)
#define CM_SHADOW_FREQ_CONFIG1_RESERVED2_MASK                                                               (0x00000002U)

#define CM_SHADOW_FREQ_CONFIG1_DPLL_DDR_DPLL_EN_SHIFT                                                       (16U)
#define CM_SHADOW_FREQ_CONFIG1_DPLL_DDR_DPLL_EN_MASK                                                        (0x00070000U)
#define CM_SHADOW_FREQ_CONFIG1_DPLL_DDR_DPLL_EN_RESERVED                                                     (0U)
#define CM_SHADOW_FREQ_CONFIG1_DPLL_DDR_DPLL_EN_RESERVED1                                                    (1U)
#define CM_SHADOW_FREQ_CONFIG1_DPLL_DDR_DPLL_EN_RESERVED2                                                    (2U)
#define CM_SHADOW_FREQ_CONFIG1_DPLL_DDR_DPLL_EN_RESERVED3                                                    (3U)
#define CM_SHADOW_FREQ_CONFIG1_DPLL_DDR_DPLL_EN_RESERVED4                                                    (4U)
#define CM_SHADOW_FREQ_CONFIG1_DPLL_DDR_DPLL_EN_DPLL_LP_BYP_MODE                                             (5U)
#define CM_SHADOW_FREQ_CONFIG1_DPLL_DDR_DPLL_EN_DPLL_FR_BYP_MODE                                             (6U)
#define CM_SHADOW_FREQ_CONFIG1_DPLL_DDR_DPLL_EN_DPLL_LOCK_MODE                                               (7U)

#define CM_SHADOW_FREQ_CONFIG1_RESERVED1_SHIFT                                                              (19U)
#define CM_SHADOW_FREQ_CONFIG1_RESERVED1_MASK                                                               (0xfff80000U)

#define CM_SHADOW_FREQ_CONFIG1_RESERVED_SHIFT                                                               (4U)
#define CM_SHADOW_FREQ_CONFIG1_RESERVED_MASK                                                                (0x000007f0U)

#define CM_SHADOW_FREQ_CONFIG2_DPLL_CORE_H12_DIV_SHIFT                                                      (2U)
#define CM_SHADOW_FREQ_CONFIG2_DPLL_CORE_H12_DIV_MASK                                                       (0x000000fcU)
#define CM_SHADOW_FREQ_CONFIG2_DPLL_CORE_H12_DIV_RESERVED                                                    (0U)

#define CM_SHADOW_FREQ_CONFIG2_GPMC_FREQ_UPDATE_SHIFT                                                       (0U)
#define CM_SHADOW_FREQ_CONFIG2_GPMC_FREQ_UPDATE_MASK                                                        (0x00000001U)
#define CM_SHADOW_FREQ_CONFIG2_GPMC_FREQ_UPDATE_DISABLED                                                     (0U)
#define CM_SHADOW_FREQ_CONFIG2_GPMC_FREQ_UPDATE_ENABLED                                                      (1U)

#define CM_SHADOW_FREQ_CONFIG2_CLKSEL_L3_SHIFT                                                              (1U)
#define CM_SHADOW_FREQ_CONFIG2_CLKSEL_L3_MASK                                                               (0x00000002U)
#define CM_SHADOW_FREQ_CONFIG2_CLKSEL_L3_CORE_CLK_DIV_1                                                      (0U)
#define CM_SHADOW_FREQ_CONFIG2_CLKSEL_L3_CORE_CLK_DIV_2                                                      (1U)

#define CM_SHADOW_FREQ_CONFIG2_RESERVED_SHIFT                                                               (8U)
#define CM_SHADOW_FREQ_CONFIG2_RESERVED_MASK                                                                (0xffffff00U)

#define CM_DYN_DEP_PRESCAL_PRESCAL_SHIFT                                                                    (0U)
#define CM_DYN_DEP_PRESCAL_PRESCAL_MASK                                                                     (0x0000003fU)

#define CM_DYN_DEP_PRESCAL_RESERVED_SHIFT                                                                   (6U)
#define CM_DYN_DEP_PRESCAL_RESERVED_MASK                                                                    (0xffffffc0U)

#define CM_RESTORE_ST_PHASE1_COMPLETED_SHIFT                                                                (0U)
#define CM_RESTORE_ST_PHASE1_COMPLETED_MASK                                                                 (0x00000001U)

#define CM_RESTORE_ST_PHASE2A_COMPLETED_SHIFT                                                               (1U)
#define CM_RESTORE_ST_PHASE2A_COMPLETED_MASK                                                                (0x00000002U)

#define CM_RESTORE_ST_PHASE2B_COMPLETED_SHIFT                                                               (2U)
#define CM_RESTORE_ST_PHASE2B_COMPLETED_MASK                                                                (0x00000004U)

#define CM_RESTORE_ST_RESERVED_SHIFT                                                                        (3U)
#define CM_RESTORE_ST_RESERVED_MASK                                                                         (0xfffffff8U)

#define CM_CLKMODE_DPLL_EVE_DPLL_EN_SHIFT                                                                   (0U)
#define CM_CLKMODE_DPLL_EVE_DPLL_EN_MASK                                                                    (0x00000007U)
#define CM_CLKMODE_DPLL_EVE_DPLL_EN_RESERVED                                                                 (0U)
#define CM_CLKMODE_DPLL_EVE_DPLL_EN_RESERVED1                                                                (1U)
#define CM_CLKMODE_DPLL_EVE_DPLL_EN_RESERVED2                                                                (2U)
#define CM_CLKMODE_DPLL_EVE_DPLL_EN_RESERVED3                                                                (3U)
#define CM_CLKMODE_DPLL_EVE_DPLL_EN_RESERVED4                                                                (4U)
#define CM_CLKMODE_DPLL_EVE_DPLL_EN_DPLL_LP_BYP_MODE                                                         (5U)
#define CM_CLKMODE_DPLL_EVE_DPLL_EN_DPLL_FR_BYP_MODE                                                         (6U)
#define CM_CLKMODE_DPLL_EVE_DPLL_EN_DPLL_LOCK_MODE                                                           (7U)

#define CM_CLKMODE_DPLL_EVE_DPLL_RAMP_LEVEL_SHIFT                                                           (3U)
#define CM_CLKMODE_DPLL_EVE_DPLL_RAMP_LEVEL_MASK                                                            (0x00000018U)
#define CM_CLKMODE_DPLL_EVE_DPLL_RAMP_LEVEL_RAMP_DISABLE                                                     (0U)
#define CM_CLKMODE_DPLL_EVE_DPLL_RAMP_LEVEL_RAMP_ALGO1                                                       (1U)
#define CM_CLKMODE_DPLL_EVE_DPLL_RAMP_LEVEL_RAMP_ALGO2                                                       (2U)
#define CM_CLKMODE_DPLL_EVE_DPLL_RAMP_LEVEL_RESERVED                                                         (3U)

#define CM_CLKMODE_DPLL_EVE_DPLL_RAMP_RATE_SHIFT                                                            (5U)
#define CM_CLKMODE_DPLL_EVE_DPLL_RAMP_RATE_MASK                                                             (0x000000e0U)
#define CM_CLKMODE_DPLL_EVE_DPLL_RAMP_RATE_REFCLKX2                                                          (0U)
#define CM_CLKMODE_DPLL_EVE_DPLL_RAMP_RATE_REFCLKX4                                                          (1U)
#define CM_CLKMODE_DPLL_EVE_DPLL_RAMP_RATE_REFCLKX8                                                          (2U)
#define CM_CLKMODE_DPLL_EVE_DPLL_RAMP_RATE_REFCLKX16                                                         (3U)
#define CM_CLKMODE_DPLL_EVE_DPLL_RAMP_RATE_REFCLKX32                                                         (4U)
#define CM_CLKMODE_DPLL_EVE_DPLL_RAMP_RATE_REFCLKX64                                                         (5U)
#define CM_CLKMODE_DPLL_EVE_DPLL_RAMP_RATE_REFCLKX128                                                        (6U)
#define CM_CLKMODE_DPLL_EVE_DPLL_RAMP_RATE_REFCLKX512                                                        (7U)

#define CM_CLKMODE_DPLL_EVE_DPLL_DRIFTGUARD_EN_SHIFT                                                        (8U)
#define CM_CLKMODE_DPLL_EVE_DPLL_DRIFTGUARD_EN_MASK                                                         (0x00000100U)
#define CM_CLKMODE_DPLL_EVE_DPLL_DRIFTGUARD_EN_ENABLED                                                       (1U)
#define CM_CLKMODE_DPLL_EVE_DPLL_DRIFTGUARD_EN_DIASBLED                                                      (0U)

#define CM_CLKMODE_DPLL_EVE_DPLL_RELOCK_RAMP_EN_SHIFT                                                       (9U)
#define CM_CLKMODE_DPLL_EVE_DPLL_RELOCK_RAMP_EN_MASK                                                        (0x00000200U)

#define CM_CLKMODE_DPLL_EVE_DPLL_LPMODE_EN_SHIFT                                                            (10U)
#define CM_CLKMODE_DPLL_EVE_DPLL_LPMODE_EN_MASK                                                             (0x00000400U)
#define CM_CLKMODE_DPLL_EVE_DPLL_LPMODE_EN_DISABLED                                                          (0U)
#define CM_CLKMODE_DPLL_EVE_DPLL_LPMODE_EN_ENABLED                                                           (1U)

#define CM_CLKMODE_DPLL_EVE_DPLL_REGM4XEN_SHIFT                                                             (11U)
#define CM_CLKMODE_DPLL_EVE_DPLL_REGM4XEN_MASK                                                              (0x00000800U)
#define CM_CLKMODE_DPLL_EVE_DPLL_REGM4XEN_DISABLED                                                           (0U)

#define CM_CLKMODE_DPLL_EVE_DPLL_SSC_EN_SHIFT                                                               (12U)
#define CM_CLKMODE_DPLL_EVE_DPLL_SSC_EN_MASK                                                                (0x00001000U)
#define CM_CLKMODE_DPLL_EVE_DPLL_SSC_EN_DISABLED                                                             (0U)
#define CM_CLKMODE_DPLL_EVE_DPLL_SSC_EN_ENABLED                                                              (1U)

#define CM_CLKMODE_DPLL_EVE_DPLL_SSC_ACK_SHIFT                                                              (13U)
#define CM_CLKMODE_DPLL_EVE_DPLL_SSC_ACK_MASK                                                               (0x00002000U)
#define CM_CLKMODE_DPLL_EVE_DPLL_SSC_ACK_DISABLED                                                            (0U)
#define CM_CLKMODE_DPLL_EVE_DPLL_SSC_ACK_ENABLED                                                             (1U)

#define CM_CLKMODE_DPLL_EVE_DPLL_SSC_DOWNSPREAD_SHIFT                                                       (14U)
#define CM_CLKMODE_DPLL_EVE_DPLL_SSC_DOWNSPREAD_MASK                                                        (0x00004000U)
#define CM_CLKMODE_DPLL_EVE_DPLL_SSC_DOWNSPREAD_FULL_SPREAD                                                  (0U)
#define CM_CLKMODE_DPLL_EVE_DPLL_SSC_DOWNSPREAD_LOW_SPREAD                                                   (1U)

#define CM_CLKMODE_DPLL_EVE_DPLL_SSC_TYPE_SHIFT                                                             (15U)
#define CM_CLKMODE_DPLL_EVE_DPLL_SSC_TYPE_MASK                                                              (0x00008000U)
#define CM_CLKMODE_DPLL_EVE_DPLL_SSC_TYPE_TRIANGULAR                                                         (0U)
#define CM_CLKMODE_DPLL_EVE_DPLL_SSC_TYPE_SQUARE                                                             (1U)

#define CM_CLKMODE_DPLL_EVE_RESERVED_SHIFT                                                                  (16U)
#define CM_CLKMODE_DPLL_EVE_RESERVED_MASK                                                                   (0xffff0000U)

#define CM_IDLEST_DPLL_EVE_ST_DPLL_CLK_SHIFT                                                                (0U)
#define CM_IDLEST_DPLL_EVE_ST_DPLL_CLK_MASK                                                                 (0x00000001U)
#define CM_IDLEST_DPLL_EVE_ST_DPLL_CLK_DPLL_UNLOCKED                                                         (0U)
#define CM_IDLEST_DPLL_EVE_ST_DPLL_CLK_DPLL_LOCKED                                                           (1U)

#define CM_IDLEST_DPLL_EVE_RESERVED_SHIFT                                                                   (5U)
#define CM_IDLEST_DPLL_EVE_RESERVED_MASK                                                                    (0xffffffe0U)

#define CM_IDLEST_DPLL_EVE_ST_DPLL_MODE_SHIFT                                                               (1U)
#define CM_IDLEST_DPLL_EVE_ST_DPLL_MODE_MASK                                                                (0x0000000eU)
#define CM_IDLEST_DPLL_EVE_ST_DPLL_MODE_TRANSIENT                                                            (0U)
#define CM_IDLEST_DPLL_EVE_ST_DPLL_MODE_LP_STOP                                                              (1U)
#define CM_IDLEST_DPLL_EVE_ST_DPLL_MODE_FR_STOP                                                              (2U)
#define CM_IDLEST_DPLL_EVE_ST_DPLL_MODE_RESERVED1                                                            (3U)
#define CM_IDLEST_DPLL_EVE_ST_DPLL_MODE_RESERVED2                                                            (4U)
#define CM_IDLEST_DPLL_EVE_ST_DPLL_MODE_LP_BYP                                                               (5U)
#define CM_IDLEST_DPLL_EVE_ST_DPLL_MODE_FR_BYP                                                               (6U)
#define CM_IDLEST_DPLL_EVE_ST_DPLL_MODE_RESERVED3                                                            (7U)

#define CM_IDLEST_DPLL_EVE_ST_DPLL_INIT_SHIFT                                                               (4U)
#define CM_IDLEST_DPLL_EVE_ST_DPLL_INIT_MASK                                                                (0x00000010U)
#define CM_IDLEST_DPLL_EVE_ST_DPLL_INIT_DPLL_NOTINIT                                                         (0U)
#define CM_IDLEST_DPLL_EVE_ST_DPLL_INIT_DPLL_INIT                                                            (1U)

#define CM_AUTOIDLE_DPLL_EVE_AUTO_DPLL_MODE_SHIFT                                                           (0U)
#define CM_AUTOIDLE_DPLL_EVE_AUTO_DPLL_MODE_MASK                                                            (0x00000007U)
#define CM_AUTOIDLE_DPLL_EVE_AUTO_DPLL_MODE_AUTO_CTL_DISABLE                                                 (0U)
#define CM_AUTOIDLE_DPLL_EVE_AUTO_DPLL_MODE_AUTO_LP_STOP                                                     (1U)
#define CM_AUTOIDLE_DPLL_EVE_AUTO_DPLL_MODE_AUTO_FR_STOP                                                     (2U)
#define CM_AUTOIDLE_DPLL_EVE_AUTO_DPLL_MODE_RESERVED3                                                        (3U)
#define CM_AUTOIDLE_DPLL_EVE_AUTO_DPLL_MODE_RESERVED4                                                        (4U)
#define CM_AUTOIDLE_DPLL_EVE_AUTO_DPLL_MODE_AUTO_LP_BYP                                                      (5U)
#define CM_AUTOIDLE_DPLL_EVE_AUTO_DPLL_MODE_AUTO_FR_BYP                                                      (6U)
#define CM_AUTOIDLE_DPLL_EVE_AUTO_DPLL_MODE_RESERVED7                                                        (7U)

#define CM_AUTOIDLE_DPLL_EVE_RESERVED_SHIFT                                                                 (3U)
#define CM_AUTOIDLE_DPLL_EVE_RESERVED_MASK                                                                  (0xfffffff8U)

#define CM_CLKSEL_DPLL_EVE_DPLL_DIV_SHIFT                                                                   (0U)
#define CM_CLKSEL_DPLL_EVE_DPLL_DIV_MASK                                                                    (0x0000007fU)

#define CM_CLKSEL_DPLL_EVE_RESERVED_SHIFT                                                                   (7U)
#define CM_CLKSEL_DPLL_EVE_RESERVED_MASK                                                                    (0x00000080U)

#define CM_CLKSEL_DPLL_EVE_RESERVED1_SHIFT                                                                  (19U)
#define CM_CLKSEL_DPLL_EVE_RESERVED1_MASK                                                                   (0x00380000U)

#define CM_CLKSEL_DPLL_EVE_RESERVED2_SHIFT                                                                  (24U)
#define CM_CLKSEL_DPLL_EVE_RESERVED2_MASK                                                                   (0xff000000U)

#define CM_CLKSEL_DPLL_EVE_DPLL_BYP_CLKSEL_SHIFT                                                            (23U)
#define CM_CLKSEL_DPLL_EVE_DPLL_BYP_CLKSEL_MASK                                                             (0x00800000U)

#define CM_CLKSEL_DPLL_EVE_DPLL_MULT_SHIFT                                                                  (8U)
#define CM_CLKSEL_DPLL_EVE_DPLL_MULT_MASK                                                                   (0x0007ff00U)
#define CM_CLKSEL_DPLL_EVE_DPLL_MULT_RESERVED_0                                                              (0U)
#define CM_CLKSEL_DPLL_EVE_DPLL_MULT_RESERVED_1                                                              (1U)

#define CM_CLKSEL_DPLL_EVE_DCC_EN_SHIFT                                                                     (22U)
#define CM_CLKSEL_DPLL_EVE_DCC_EN_MASK                                                                      (0x00400000U)
#define CM_CLKSEL_DPLL_EVE_DCC_EN_DISABLED                                                                   (0U)

#define CM_DIV_M2_DPLL_EVE_DIVHS_SHIFT                                                                      (0U)
#define CM_DIV_M2_DPLL_EVE_DIVHS_MASK                                                                       (0x0000001fU)
#define CM_DIV_M2_DPLL_EVE_DIVHS_RESERVED                                                                    (0U)

#define CM_DIV_M2_DPLL_EVE_CLKST_SHIFT                                                                      (9U)
#define CM_DIV_M2_DPLL_EVE_CLKST_MASK                                                                       (0x00000200U)
#define CM_DIV_M2_DPLL_EVE_CLKST_CLK_ENABLED                                                                 (1U)
#define CM_DIV_M2_DPLL_EVE_CLKST_CLK_GATED                                                                   (0U)

#define CM_DIV_M2_DPLL_EVE_RESERVED_SHIFT                                                                   (5U)
#define CM_DIV_M2_DPLL_EVE_RESERVED_MASK                                                                    (0x000001e0U)

#define CM_DIV_M2_DPLL_EVE_RESERVED1_SHIFT                                                                  (10U)
#define CM_DIV_M2_DPLL_EVE_RESERVED1_MASK                                                                   (0xfffffc00U)

#define CM_DIV_M3_DPLL_EVE_DIVHS_SHIFT                                                                      (0U)
#define CM_DIV_M3_DPLL_EVE_DIVHS_MASK                                                                       (0x0000001fU)
#define CM_DIV_M3_DPLL_EVE_DIVHS_RESERVED                                                                    (0U)

#define CM_DIV_M3_DPLL_EVE_CLKST_SHIFT                                                                      (9U)
#define CM_DIV_M3_DPLL_EVE_CLKST_MASK                                                                       (0x00000200U)
#define CM_DIV_M3_DPLL_EVE_CLKST_CLK_ENABLED                                                                 (1U)
#define CM_DIV_M3_DPLL_EVE_CLKST_CLK_GATED                                                                   (0U)

#define CM_DIV_M3_DPLL_EVE_RESERVED_SHIFT                                                                   (5U)
#define CM_DIV_M3_DPLL_EVE_RESERVED_MASK                                                                    (0x000001e0U)

#define CM_DIV_M3_DPLL_EVE_RESERVED1_SHIFT                                                                  (10U)
#define CM_DIV_M3_DPLL_EVE_RESERVED1_MASK                                                                   (0xfffffc00U)

#define CM_SSC_DELTAMSTEP_DPLL_EVE_RESERVED_SHIFT                                                           (20U)
#define CM_SSC_DELTAMSTEP_DPLL_EVE_RESERVED_MASK                                                            (0xfff00000U)

#define CM_SSC_DELTAMSTEP_DPLL_EVE_DELTAMSTEP_SHIFT                                                         (0U)
#define CM_SSC_DELTAMSTEP_DPLL_EVE_DELTAMSTEP_MASK                                                          (0x000fffffU)

#define CM_SSC_MODFREQDIV_DPLL_EVE_MODFREQDIV_MANTISSA_SHIFT                                                (0U)
#define CM_SSC_MODFREQDIV_DPLL_EVE_MODFREQDIV_MANTISSA_MASK                                                 (0x0000007fU)

#define CM_SSC_MODFREQDIV_DPLL_EVE_MODFREQDIV_EXPONENT_SHIFT                                                (8U)
#define CM_SSC_MODFREQDIV_DPLL_EVE_MODFREQDIV_EXPONENT_MASK                                                 (0x00000700U)

#define CM_SSC_MODFREQDIV_DPLL_EVE_RESERVED_SHIFT                                                           (7U)
#define CM_SSC_MODFREQDIV_DPLL_EVE_RESERVED_MASK                                                            (0x00000080U)

#define CM_SSC_MODFREQDIV_DPLL_EVE_RESERVED1_SHIFT                                                          (11U)
#define CM_SSC_MODFREQDIV_DPLL_EVE_RESERVED1_MASK                                                           (0xfffff800U)

#define CM_BYPCLK_DPLL_EVE_CLKSEL_SHIFT                                                                     (0U)
#define CM_BYPCLK_DPLL_EVE_CLKSEL_MASK                                                                      (0x00000003U)
#define CM_BYPCLK_DPLL_EVE_CLKSEL_CORE_X2_CLK_DIV_1                                                          (0U)
#define CM_BYPCLK_DPLL_EVE_CLKSEL_CORE_X2_CLK_DIV_2                                                          (1U)
#define CM_BYPCLK_DPLL_EVE_CLKSEL_CORE_X2_CLK_DIV_4                                                          (2U)
#define CM_BYPCLK_DPLL_EVE_CLKSEL_CORE_X2_CLK_DIV_8                                                          (3U)

#define CM_BYPCLK_DPLL_EVE_RESERVED_SHIFT                                                                   (2U)
#define CM_BYPCLK_DPLL_EVE_RESERVED_MASK                                                                    (0xfffffffcU)

#define CM_CLKMODE_DPLL_GMAC_DPLL_EN_SHIFT                                                                  (0U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_EN_MASK                                                                   (0x00000007U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_EN_RESERVED                                                                (0U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_EN_RESERVED1                                                               (1U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_EN_RESERVED2                                                               (2U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_EN_RESERVED3                                                               (3U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_EN_RESERVED4                                                               (4U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_EN_DPLL_LP_BYP_MODE                                                        (5U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_EN_DPLL_FR_BYP_MODE                                                        (6U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_EN_DPLL_LOCK_MODE                                                          (7U)

#define CM_CLKMODE_DPLL_GMAC_DPLL_RAMP_LEVEL_SHIFT                                                          (3U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_RAMP_LEVEL_MASK                                                           (0x00000018U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_RAMP_LEVEL_RAMP_DISABLE                                                    (0U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_RAMP_LEVEL_RAMP_ALGO1                                                      (1U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_RAMP_LEVEL_RAMP_ALGO2                                                      (2U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_RAMP_LEVEL_RESERVED                                                        (3U)

#define CM_CLKMODE_DPLL_GMAC_DPLL_RAMP_RATE_SHIFT                                                           (5U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_RAMP_RATE_MASK                                                            (0x000000e0U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_RAMP_RATE_REFCLKX2                                                         (0U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_RAMP_RATE_REFCLKX4                                                         (1U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_RAMP_RATE_REFCLKX8                                                         (2U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_RAMP_RATE_REFCLKX16                                                        (3U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_RAMP_RATE_REFCLKX32                                                        (4U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_RAMP_RATE_REFCLKX64                                                        (5U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_RAMP_RATE_REFCLKX128                                                       (6U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_RAMP_RATE_REFCLKX512                                                       (7U)

#define CM_CLKMODE_DPLL_GMAC_DPLL_DRIFTGUARD_EN_SHIFT                                                       (8U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_DRIFTGUARD_EN_MASK                                                        (0x00000100U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_DRIFTGUARD_EN_ENABLED                                                      (1U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_DRIFTGUARD_EN_DIASBLED                                                     (0U)

#define CM_CLKMODE_DPLL_GMAC_DPLL_RELOCK_RAMP_EN_SHIFT                                                      (9U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_RELOCK_RAMP_EN_MASK                                                       (0x00000200U)

#define CM_CLKMODE_DPLL_GMAC_DPLL_LPMODE_EN_SHIFT                                                           (10U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_LPMODE_EN_MASK                                                            (0x00000400U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_LPMODE_EN_DISABLED                                                         (0U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_LPMODE_EN_ENABLED                                                          (1U)

#define CM_CLKMODE_DPLL_GMAC_DPLL_REGM4XEN_SHIFT                                                            (11U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_REGM4XEN_MASK                                                             (0x00000800U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_REGM4XEN_DISABLED                                                          (0U)

#define CM_CLKMODE_DPLL_GMAC_DPLL_SSC_EN_SHIFT                                                              (12U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_SSC_EN_MASK                                                               (0x00001000U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_SSC_EN_DISABLED                                                            (0U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_SSC_EN_ENABLED                                                             (1U)

#define CM_CLKMODE_DPLL_GMAC_DPLL_SSC_ACK_SHIFT                                                             (13U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_SSC_ACK_MASK                                                              (0x00002000U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_SSC_ACK_DISABLED                                                           (0U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_SSC_ACK_ENABLED                                                            (1U)

#define CM_CLKMODE_DPLL_GMAC_DPLL_SSC_DOWNSPREAD_SHIFT                                                      (14U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_SSC_DOWNSPREAD_MASK                                                       (0x00004000U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_SSC_DOWNSPREAD_FULL_SPREAD                                                 (0U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_SSC_DOWNSPREAD_LOW_SPREAD                                                  (1U)

#define CM_CLKMODE_DPLL_GMAC_DPLL_SSC_TYPE_SHIFT                                                            (15U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_SSC_TYPE_MASK                                                             (0x00008000U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_SSC_TYPE_TRIANGULAR                                                        (0U)
#define CM_CLKMODE_DPLL_GMAC_DPLL_SSC_TYPE_SQUARE                                                            (1U)

#define CM_CLKMODE_DPLL_GMAC_RESERVED_SHIFT                                                                 (16U)
#define CM_CLKMODE_DPLL_GMAC_RESERVED_MASK                                                                  (0xffff0000U)

#define CM_IDLEST_DPLL_GMAC_ST_DPLL_CLK_SHIFT                                                               (0U)
#define CM_IDLEST_DPLL_GMAC_ST_DPLL_CLK_MASK                                                                (0x00000001U)
#define CM_IDLEST_DPLL_GMAC_ST_DPLL_CLK_DPLL_UNLOCKED                                                        (0U)
#define CM_IDLEST_DPLL_GMAC_ST_DPLL_CLK_DPLL_LOCKED                                                          (1U)

#define CM_IDLEST_DPLL_GMAC_RESERVED_SHIFT                                                                  (5U)
#define CM_IDLEST_DPLL_GMAC_RESERVED_MASK                                                                   (0xffffffe0U)

#define CM_IDLEST_DPLL_GMAC_ST_DPLL_MODE_SHIFT                                                              (1U)
#define CM_IDLEST_DPLL_GMAC_ST_DPLL_MODE_MASK                                                               (0x0000000eU)
#define CM_IDLEST_DPLL_GMAC_ST_DPLL_MODE_TRANSIENT                                                           (0U)
#define CM_IDLEST_DPLL_GMAC_ST_DPLL_MODE_LP_STOP                                                             (1U)
#define CM_IDLEST_DPLL_GMAC_ST_DPLL_MODE_FR_STOP                                                             (2U)
#define CM_IDLEST_DPLL_GMAC_ST_DPLL_MODE_RESERVED1                                                           (3U)
#define CM_IDLEST_DPLL_GMAC_ST_DPLL_MODE_RESERVED2                                                           (4U)
#define CM_IDLEST_DPLL_GMAC_ST_DPLL_MODE_LP_BYP                                                              (5U)
#define CM_IDLEST_DPLL_GMAC_ST_DPLL_MODE_FR_BYP                                                              (6U)
#define CM_IDLEST_DPLL_GMAC_ST_DPLL_MODE_RESERVED3                                                           (7U)

#define CM_IDLEST_DPLL_GMAC_ST_DPLL_INIT_SHIFT                                                              (4U)
#define CM_IDLEST_DPLL_GMAC_ST_DPLL_INIT_MASK                                                               (0x00000010U)
#define CM_IDLEST_DPLL_GMAC_ST_DPLL_INIT_DPLL_NOTINIT                                                        (0U)
#define CM_IDLEST_DPLL_GMAC_ST_DPLL_INIT_DPLL_INIT                                                           (1U)

#define CM_AUTOIDLE_DPLL_GMAC_AUTO_DPLL_MODE_SHIFT                                                          (0U)
#define CM_AUTOIDLE_DPLL_GMAC_AUTO_DPLL_MODE_MASK                                                           (0x00000007U)
#define CM_AUTOIDLE_DPLL_GMAC_AUTO_DPLL_MODE_AUTO_CTL_DISABLE                                                (0U)
#define CM_AUTOIDLE_DPLL_GMAC_AUTO_DPLL_MODE_AUTO_LP_STOP                                                    (1U)
#define CM_AUTOIDLE_DPLL_GMAC_AUTO_DPLL_MODE_AUTO_FR_STOP                                                    (2U)
#define CM_AUTOIDLE_DPLL_GMAC_AUTO_DPLL_MODE_RESERVED3                                                       (3U)
#define CM_AUTOIDLE_DPLL_GMAC_AUTO_DPLL_MODE_RESERVED4                                                       (4U)
#define CM_AUTOIDLE_DPLL_GMAC_AUTO_DPLL_MODE_AUTO_LP_BYP                                                     (5U)
#define CM_AUTOIDLE_DPLL_GMAC_AUTO_DPLL_MODE_AUTO_FR_BYP                                                     (6U)
#define CM_AUTOIDLE_DPLL_GMAC_AUTO_DPLL_MODE_RESERVED7                                                       (7U)

#define CM_AUTOIDLE_DPLL_GMAC_RESERVED_SHIFT                                                                (3U)
#define CM_AUTOIDLE_DPLL_GMAC_RESERVED_MASK                                                                 (0xfffffff8U)

#define CM_CLKSEL_DPLL_GMAC_DPLL_DIV_SHIFT                                                                  (0U)
#define CM_CLKSEL_DPLL_GMAC_DPLL_DIV_MASK                                                                   (0x0000007fU)

#define CM_CLKSEL_DPLL_GMAC_RESERVED_SHIFT                                                                  (7U)
#define CM_CLKSEL_DPLL_GMAC_RESERVED_MASK                                                                   (0x00000080U)

#define CM_CLKSEL_DPLL_GMAC_RESERVED2_SHIFT                                                                 (24U)
#define CM_CLKSEL_DPLL_GMAC_RESERVED2_MASK                                                                  (0xff000000U)

#define CM_CLKSEL_DPLL_GMAC_DPLL_MULT_SHIFT                                                                 (8U)
#define CM_CLKSEL_DPLL_GMAC_DPLL_MULT_MASK                                                                  (0x0007ff00U)
#define CM_CLKSEL_DPLL_GMAC_DPLL_MULT_RESERVED_0                                                             (0U)
#define CM_CLKSEL_DPLL_GMAC_DPLL_MULT_RESERVED_1                                                             (1U)

#define CM_CLKSEL_DPLL_GMAC_DCC_EN_SHIFT                                                                    (22U)
#define CM_CLKSEL_DPLL_GMAC_DCC_EN_MASK                                                                     (0x00400000U)
#define CM_CLKSEL_DPLL_GMAC_DCC_EN_DISABLED                                                                  (0U)
#define CM_CLKSEL_DPLL_GMAC_DCC_EN_ENABLED                                                                   (1U)

#define CM_CLKSEL_DPLL_GMAC_DPLL_BYP_CLKSEL_SHIFT                                                           (23U)
#define CM_CLKSEL_DPLL_GMAC_DPLL_BYP_CLKSEL_MASK                                                            (0x00800000U)

#define CM_CLKSEL_DPLL_GMAC_RESERVED1_SHIFT                                                                 (19U)
#define CM_CLKSEL_DPLL_GMAC_RESERVED1_MASK                                                                  (0x00080000U)

#define CM_CLKSEL_DPLL_GMAC_DPLL_CLKOUTHIF_CLKSEL_SHIFT                                                     (20U)
#define CM_CLKSEL_DPLL_GMAC_DPLL_CLKOUTHIF_CLKSEL_MASK                                                      (0x00100000U)
#define CM_CLKSEL_DPLL_GMAC_DPLL_CLKOUTHIF_CLKSEL_SEL_DCO                                                    (0U)
#define CM_CLKSEL_DPLL_GMAC_DPLL_CLKOUTHIF_CLKSEL_SEL_CLKINPHIF                                              (1U)

#define CM_CLKSEL_DPLL_GMAC_RESERVED3_SHIFT                                                                 (21U)
#define CM_CLKSEL_DPLL_GMAC_RESERVED3_MASK                                                                  (0x00200000U)

#define CM_DIV_M2_DPLL_GMAC_DIVHS_SHIFT                                                                     (0U)
#define CM_DIV_M2_DPLL_GMAC_DIVHS_MASK                                                                      (0x0000001fU)
#define CM_DIV_M2_DPLL_GMAC_DIVHS_RESERVED                                                                   (0U)

#define CM_DIV_M2_DPLL_GMAC_CLKST_SHIFT                                                                     (9U)
#define CM_DIV_M2_DPLL_GMAC_CLKST_MASK                                                                      (0x00000200U)
#define CM_DIV_M2_DPLL_GMAC_CLKST_CLK_ENABLED                                                                (1U)
#define CM_DIV_M2_DPLL_GMAC_CLKST_CLK_GATED                                                                  (0U)

#define CM_DIV_M2_DPLL_GMAC_RESERVED_SHIFT                                                                  (5U)
#define CM_DIV_M2_DPLL_GMAC_RESERVED_MASK                                                                   (0x000001e0U)

#define CM_DIV_M2_DPLL_GMAC_RESERVED1_SHIFT                                                                 (10U)
#define CM_DIV_M2_DPLL_GMAC_RESERVED1_MASK                                                                  (0xfffffc00U)

#define CM_DIV_M3_DPLL_GMAC_DIVHS_SHIFT                                                                     (0U)
#define CM_DIV_M3_DPLL_GMAC_DIVHS_MASK                                                                      (0x0000001fU)
#define CM_DIV_M3_DPLL_GMAC_DIVHS_RESERVED                                                                   (0U)

#define CM_DIV_M3_DPLL_GMAC_CLKST_SHIFT                                                                     (9U)
#define CM_DIV_M3_DPLL_GMAC_CLKST_MASK                                                                      (0x00000200U)
#define CM_DIV_M3_DPLL_GMAC_CLKST_CLK_ENABLED                                                                (1U)
#define CM_DIV_M3_DPLL_GMAC_CLKST_CLK_GATED                                                                  (0U)

#define CM_DIV_M3_DPLL_GMAC_RESERVED_SHIFT                                                                  (5U)
#define CM_DIV_M3_DPLL_GMAC_RESERVED_MASK                                                                   (0x000001e0U)

#define CM_DIV_M3_DPLL_GMAC_RESERVED1_SHIFT                                                                 (10U)
#define CM_DIV_M3_DPLL_GMAC_RESERVED1_MASK                                                                  (0xfffffc00U)

#define CM_DIV_H11_DPLL_GMAC_DIVHS_SHIFT                                                                    (0U)
#define CM_DIV_H11_DPLL_GMAC_DIVHS_MASK                                                                     (0x0000003fU)
#define CM_DIV_H11_DPLL_GMAC_DIVHS_RESERVED                                                                  (0U)

#define CM_DIV_H11_DPLL_GMAC_CLKST_SHIFT                                                                    (9U)
#define CM_DIV_H11_DPLL_GMAC_CLKST_MASK                                                                     (0x00000200U)
#define CM_DIV_H11_DPLL_GMAC_CLKST_CLK_ENABLED                                                               (1U)
#define CM_DIV_H11_DPLL_GMAC_CLKST_CLK_GATED                                                                 (0U)

#define CM_DIV_H11_DPLL_GMAC_RESERVED_SHIFT                                                                 (6U)
#define CM_DIV_H11_DPLL_GMAC_RESERVED_MASK                                                                  (0x000001c0U)

#define CM_DIV_H11_DPLL_GMAC_RESERVED1_SHIFT                                                                (10U)
#define CM_DIV_H11_DPLL_GMAC_RESERVED1_MASK                                                                 (0xfffffc00U)

#define CM_DIV_H12_DPLL_GMAC_DIVHS_SHIFT                                                                    (0U)
#define CM_DIV_H12_DPLL_GMAC_DIVHS_MASK                                                                     (0x0000003fU)
#define CM_DIV_H12_DPLL_GMAC_DIVHS_RESERVED                                                                  (0U)

#define CM_DIV_H12_DPLL_GMAC_CLKST_SHIFT                                                                    (9U)
#define CM_DIV_H12_DPLL_GMAC_CLKST_MASK                                                                     (0x00000200U)
#define CM_DIV_H12_DPLL_GMAC_CLKST_CLK_ENABLED                                                               (1U)
#define CM_DIV_H12_DPLL_GMAC_CLKST_CLK_GATED                                                                 (0U)

#define CM_DIV_H12_DPLL_GMAC_RESERVED_SHIFT                                                                 (6U)
#define CM_DIV_H12_DPLL_GMAC_RESERVED_MASK                                                                  (0x000001c0U)

#define CM_DIV_H12_DPLL_GMAC_RESERVED1_SHIFT                                                                (10U)
#define CM_DIV_H12_DPLL_GMAC_RESERVED1_MASK                                                                 (0xfffffc00U)

#define CM_DIV_H13_DPLL_GMAC_DIVHS_SHIFT                                                                    (0U)
#define CM_DIV_H13_DPLL_GMAC_DIVHS_MASK                                                                     (0x0000003fU)
#define CM_DIV_H13_DPLL_GMAC_DIVHS_RESERVED                                                                  (0U)

#define CM_DIV_H13_DPLL_GMAC_CLKST_SHIFT                                                                    (9U)
#define CM_DIV_H13_DPLL_GMAC_CLKST_MASK                                                                     (0x00000200U)
#define CM_DIV_H13_DPLL_GMAC_CLKST_CLK_ENABLED                                                               (1U)
#define CM_DIV_H13_DPLL_GMAC_CLKST_CLK_GATED                                                                 (0U)

#define CM_DIV_H13_DPLL_GMAC_RESERVED_SHIFT                                                                 (6U)
#define CM_DIV_H13_DPLL_GMAC_RESERVED_MASK                                                                  (0x000001c0U)

#define CM_DIV_H13_DPLL_GMAC_RESERVED1_SHIFT                                                                (10U)
#define CM_DIV_H13_DPLL_GMAC_RESERVED1_MASK                                                                 (0xfffffc00U)

#define CM_SSC_DELTAMSTEP_DPLL_GMAC_DELTAMSTEP_SHIFT                                                        (0U)
#define CM_SSC_DELTAMSTEP_DPLL_GMAC_DELTAMSTEP_MASK                                                         (0x000fffffU)

#define CM_SSC_DELTAMSTEP_DPLL_GMAC_RESERVED_SHIFT                                                          (20U)
#define CM_SSC_DELTAMSTEP_DPLL_GMAC_RESERVED_MASK                                                           (0xfff00000U)

#define CM_SSC_MODFREQDIV_DPLL_GMAC_MODFREQDIV_MANTISSA_SHIFT                                               (0U)
#define CM_SSC_MODFREQDIV_DPLL_GMAC_MODFREQDIV_MANTISSA_MASK                                                (0x0000007fU)

#define CM_SSC_MODFREQDIV_DPLL_GMAC_MODFREQDIV_EXPONENT_SHIFT                                               (8U)
#define CM_SSC_MODFREQDIV_DPLL_GMAC_MODFREQDIV_EXPONENT_MASK                                                (0x00000700U)

#define CM_SSC_MODFREQDIV_DPLL_GMAC_RESERVED_SHIFT                                                          (7U)
#define CM_SSC_MODFREQDIV_DPLL_GMAC_RESERVED_MASK                                                           (0x00000080U)

#define CM_SSC_MODFREQDIV_DPLL_GMAC_RESERVED1_SHIFT                                                         (11U)
#define CM_SSC_MODFREQDIV_DPLL_GMAC_RESERVED1_MASK                                                          (0xfffff800U)

#define CM_CLKMODE_DPLL_GPU_DPLL_EN_SHIFT                                                                   (0U)
#define CM_CLKMODE_DPLL_GPU_DPLL_EN_MASK                                                                    (0x00000007U)
#define CM_CLKMODE_DPLL_GPU_DPLL_EN_RESERVED                                                                 (0U)
#define CM_CLKMODE_DPLL_GPU_DPLL_EN_RESERVED1                                                                (1U)
#define CM_CLKMODE_DPLL_GPU_DPLL_EN_RESERVED2                                                                (2U)
#define CM_CLKMODE_DPLL_GPU_DPLL_EN_RESERVED3                                                                (3U)
#define CM_CLKMODE_DPLL_GPU_DPLL_EN_RESERVED4                                                                (4U)
#define CM_CLKMODE_DPLL_GPU_DPLL_EN_DPLL_LP_BYP_MODE                                                         (5U)
#define CM_CLKMODE_DPLL_GPU_DPLL_EN_DPLL_FR_BYP_MODE                                                         (6U)
#define CM_CLKMODE_DPLL_GPU_DPLL_EN_DPLL_LOCK_MODE                                                           (7U)

#define CM_CLKMODE_DPLL_GPU_DPLL_DRIFTGUARD_EN_SHIFT                                                        (8U)
#define CM_CLKMODE_DPLL_GPU_DPLL_DRIFTGUARD_EN_MASK                                                         (0x00000100U)
#define CM_CLKMODE_DPLL_GPU_DPLL_DRIFTGUARD_EN_ENABLED                                                       (1U)
#define CM_CLKMODE_DPLL_GPU_DPLL_DRIFTGUARD_EN_DIASBLED                                                      (0U)

#define CM_CLKMODE_DPLL_GPU_DPLL_RAMP_LEVEL_SHIFT                                                           (3U)
#define CM_CLKMODE_DPLL_GPU_DPLL_RAMP_LEVEL_MASK                                                            (0x00000018U)
#define CM_CLKMODE_DPLL_GPU_DPLL_RAMP_LEVEL_RAMP_DISABLE                                                     (0U)
#define CM_CLKMODE_DPLL_GPU_DPLL_RAMP_LEVEL_RAMP_ALGO1                                                       (1U)
#define CM_CLKMODE_DPLL_GPU_DPLL_RAMP_LEVEL_RAMP_ALGO2                                                       (2U)
#define CM_CLKMODE_DPLL_GPU_DPLL_RAMP_LEVEL_RESERVED                                                         (3U)

#define CM_CLKMODE_DPLL_GPU_DPLL_RAMP_RATE_SHIFT                                                            (5U)
#define CM_CLKMODE_DPLL_GPU_DPLL_RAMP_RATE_MASK                                                             (0x000000e0U)
#define CM_CLKMODE_DPLL_GPU_DPLL_RAMP_RATE_REFCLKX2                                                          (0U)
#define CM_CLKMODE_DPLL_GPU_DPLL_RAMP_RATE_REFCLKX4                                                          (1U)
#define CM_CLKMODE_DPLL_GPU_DPLL_RAMP_RATE_REFCLKX8                                                          (2U)
#define CM_CLKMODE_DPLL_GPU_DPLL_RAMP_RATE_REFCLKX16                                                         (3U)
#define CM_CLKMODE_DPLL_GPU_DPLL_RAMP_RATE_REFCLKX32                                                         (4U)
#define CM_CLKMODE_DPLL_GPU_DPLL_RAMP_RATE_REFCLKX64                                                         (5U)
#define CM_CLKMODE_DPLL_GPU_DPLL_RAMP_RATE_REFCLKX128                                                        (6U)
#define CM_CLKMODE_DPLL_GPU_DPLL_RAMP_RATE_REFCLKX512                                                        (7U)

#define CM_CLKMODE_DPLL_GPU_DPLL_RELOCK_RAMP_EN_SHIFT                                                       (9U)
#define CM_CLKMODE_DPLL_GPU_DPLL_RELOCK_RAMP_EN_MASK                                                        (0x00000200U)

#define CM_CLKMODE_DPLL_GPU_DPLL_LPMODE_EN_SHIFT                                                            (10U)
#define CM_CLKMODE_DPLL_GPU_DPLL_LPMODE_EN_MASK                                                             (0x00000400U)
#define CM_CLKMODE_DPLL_GPU_DPLL_LPMODE_EN_DISABLED                                                          (0U)
#define CM_CLKMODE_DPLL_GPU_DPLL_LPMODE_EN_ENABLED                                                           (1U)

#define CM_CLKMODE_DPLL_GPU_DPLL_REGM4XEN_SHIFT                                                             (11U)
#define CM_CLKMODE_DPLL_GPU_DPLL_REGM4XEN_MASK                                                              (0x00000800U)
#define CM_CLKMODE_DPLL_GPU_DPLL_REGM4XEN_DISABLED                                                           (0U)

#define CM_CLKMODE_DPLL_GPU_DPLL_SSC_EN_SHIFT                                                               (12U)
#define CM_CLKMODE_DPLL_GPU_DPLL_SSC_EN_MASK                                                                (0x00001000U)
#define CM_CLKMODE_DPLL_GPU_DPLL_SSC_EN_DISABLED                                                             (0U)
#define CM_CLKMODE_DPLL_GPU_DPLL_SSC_EN_ENABLED                                                              (1U)

#define CM_CLKMODE_DPLL_GPU_DPLL_SSC_ACK_SHIFT                                                              (13U)
#define CM_CLKMODE_DPLL_GPU_DPLL_SSC_ACK_MASK                                                               (0x00002000U)
#define CM_CLKMODE_DPLL_GPU_DPLL_SSC_ACK_DISABLED                                                            (0U)
#define CM_CLKMODE_DPLL_GPU_DPLL_SSC_ACK_ENABLED                                                             (1U)

#define CM_CLKMODE_DPLL_GPU_DPLL_SSC_DOWNSPREAD_SHIFT                                                       (14U)
#define CM_CLKMODE_DPLL_GPU_DPLL_SSC_DOWNSPREAD_MASK                                                        (0x00004000U)
#define CM_CLKMODE_DPLL_GPU_DPLL_SSC_DOWNSPREAD_FULL_SPREAD                                                  (0U)
#define CM_CLKMODE_DPLL_GPU_DPLL_SSC_DOWNSPREAD_LOW_SPREAD                                                   (1U)

#define CM_CLKMODE_DPLL_GPU_DPLL_SSC_TYPE_SHIFT                                                             (15U)
#define CM_CLKMODE_DPLL_GPU_DPLL_SSC_TYPE_MASK                                                              (0x00008000U)
#define CM_CLKMODE_DPLL_GPU_DPLL_SSC_TYPE_TRIANGULAR                                                         (0U)
#define CM_CLKMODE_DPLL_GPU_DPLL_SSC_TYPE_SQUARE                                                             (1U)

#define CM_CLKMODE_DPLL_GPU_RESERVED_SHIFT                                                                  (16U)
#define CM_CLKMODE_DPLL_GPU_RESERVED_MASK                                                                   (0xffff0000U)

#define CM_IDLEST_DPLL_GPU_ST_DPLL_CLK_SHIFT                                                                (0U)
#define CM_IDLEST_DPLL_GPU_ST_DPLL_CLK_MASK                                                                 (0x00000001U)
#define CM_IDLEST_DPLL_GPU_ST_DPLL_CLK_DPLL_UNLOCKED                                                         (0U)
#define CM_IDLEST_DPLL_GPU_ST_DPLL_CLK_DPLL_LOCKED                                                           (1U)

#define CM_IDLEST_DPLL_GPU_RESERVED_SHIFT                                                                   (5U)
#define CM_IDLEST_DPLL_GPU_RESERVED_MASK                                                                    (0xffffffe0U)

#define CM_IDLEST_DPLL_GPU_ST_DPLL_MODE_SHIFT                                                               (1U)
#define CM_IDLEST_DPLL_GPU_ST_DPLL_MODE_MASK                                                                (0x0000000eU)
#define CM_IDLEST_DPLL_GPU_ST_DPLL_MODE_TRANSIENT                                                            (0U)
#define CM_IDLEST_DPLL_GPU_ST_DPLL_MODE_LP_STOP                                                              (1U)
#define CM_IDLEST_DPLL_GPU_ST_DPLL_MODE_FR_STOP                                                              (2U)
#define CM_IDLEST_DPLL_GPU_ST_DPLL_MODE_RESERVED1                                                            (3U)
#define CM_IDLEST_DPLL_GPU_ST_DPLL_MODE_RESERVED2                                                            (4U)
#define CM_IDLEST_DPLL_GPU_ST_DPLL_MODE_LP_BYP                                                               (5U)
#define CM_IDLEST_DPLL_GPU_ST_DPLL_MODE_FR_BYP                                                               (6U)
#define CM_IDLEST_DPLL_GPU_ST_DPLL_MODE_RESERVED3                                                            (7U)

#define CM_IDLEST_DPLL_GPU_ST_DPLL_INIT_SHIFT                                                               (4U)
#define CM_IDLEST_DPLL_GPU_ST_DPLL_INIT_MASK                                                                (0x00000010U)
#define CM_IDLEST_DPLL_GPU_ST_DPLL_INIT_DPLL_NOTINIT                                                         (0U)
#define CM_IDLEST_DPLL_GPU_ST_DPLL_INIT_DPLL_INIT                                                            (1U)

#define CM_AUTOIDLE_DPLL_GPU_AUTO_DPLL_MODE_SHIFT                                                           (0U)
#define CM_AUTOIDLE_DPLL_GPU_AUTO_DPLL_MODE_MASK                                                            (0x00000007U)
#define CM_AUTOIDLE_DPLL_GPU_AUTO_DPLL_MODE_AUTO_CTL_DISABLE                                                 (0U)
#define CM_AUTOIDLE_DPLL_GPU_AUTO_DPLL_MODE_AUTO_LP_STOP                                                     (1U)
#define CM_AUTOIDLE_DPLL_GPU_AUTO_DPLL_MODE_AUTO_FR_STOP                                                     (2U)
#define CM_AUTOIDLE_DPLL_GPU_AUTO_DPLL_MODE_RESERVED                                                         (3U)
#define CM_AUTOIDLE_DPLL_GPU_AUTO_DPLL_MODE_RESERVED1                                                        (4U)
#define CM_AUTOIDLE_DPLL_GPU_AUTO_DPLL_MODE_AUTO_LP_BYP                                                      (5U)
#define CM_AUTOIDLE_DPLL_GPU_AUTO_DPLL_MODE_AUTO_FR_BYP                                                      (6U)
#define CM_AUTOIDLE_DPLL_GPU_AUTO_DPLL_MODE_RESERVED2                                                        (7U)

#define CM_AUTOIDLE_DPLL_GPU_RESERVED_SHIFT                                                                 (3U)
#define CM_AUTOIDLE_DPLL_GPU_RESERVED_MASK                                                                  (0xfffffff8U)

#define CM_CLKSEL_DPLL_GPU_DPLL_DIV_SHIFT                                                                   (0U)
#define CM_CLKSEL_DPLL_GPU_DPLL_DIV_MASK                                                                    (0x0000007fU)

#define CM_CLKSEL_DPLL_GPU_DPLL_BYP_CLKSEL_SHIFT                                                            (23U)
#define CM_CLKSEL_DPLL_GPU_DPLL_BYP_CLKSEL_MASK                                                             (0x00800000U)

#define CM_CLKSEL_DPLL_GPU_DPLL_CLKOUTHIF_CLKSEL_SHIFT                                                      (20U)
#define CM_CLKSEL_DPLL_GPU_DPLL_CLKOUTHIF_CLKSEL_MASK                                                       (0x00100000U)
#define CM_CLKSEL_DPLL_GPU_DPLL_CLKOUTHIF_CLKSEL_SEL_DCO                                                     (0U)
#define CM_CLKSEL_DPLL_GPU_DPLL_CLKOUTHIF_CLKSEL_SEL_CLKINPHIF                                               (1U)

#define CM_CLKSEL_DPLL_GPU_RESERVED_SHIFT                                                                   (7U)
#define CM_CLKSEL_DPLL_GPU_RESERVED_MASK                                                                    (0x00000080U)

#define CM_CLKSEL_DPLL_GPU_RESERVED1_SHIFT                                                                  (19U)
#define CM_CLKSEL_DPLL_GPU_RESERVED1_MASK                                                                   (0x00080000U)

#define CM_CLKSEL_DPLL_GPU_DPLL_MULT_SHIFT                                                                  (8U)
#define CM_CLKSEL_DPLL_GPU_DPLL_MULT_MASK                                                                   (0x0007ff00U)
#define CM_CLKSEL_DPLL_GPU_DPLL_MULT_RESERVED_0                                                              (0U)
#define CM_CLKSEL_DPLL_GPU_DPLL_MULT_RESERVED_1                                                              (1U)

#define CM_CLKSEL_DPLL_GPU_RESERVED3_SHIFT                                                                  (24U)
#define CM_CLKSEL_DPLL_GPU_RESERVED3_MASK                                                                   (0xff000000U)

#define CM_CLKSEL_DPLL_GPU_DCC_EN_SHIFT                                                                     (22U)
#define CM_CLKSEL_DPLL_GPU_DCC_EN_MASK                                                                      (0x00400000U)
#define CM_CLKSEL_DPLL_GPU_DCC_EN_DISABLED                                                                   (0U)

#define CM_CLKSEL_DPLL_GPU_RESERVED2_SHIFT                                                                  (21U)
#define CM_CLKSEL_DPLL_GPU_RESERVED2_MASK                                                                   (0x00200000U)

#define CM_DIV_M2_DPLL_GPU_DIVHS_SHIFT                                                                      (0U)
#define CM_DIV_M2_DPLL_GPU_DIVHS_MASK                                                                       (0x0000001fU)
#define CM_DIV_M2_DPLL_GPU_DIVHS_RESERVED                                                                    (0U)

#define CM_DIV_M2_DPLL_GPU_CLKST_SHIFT                                                                      (9U)
#define CM_DIV_M2_DPLL_GPU_CLKST_MASK                                                                       (0x00000200U)
#define CM_DIV_M2_DPLL_GPU_CLKST_CLK_ENABLED                                                                 (1U)
#define CM_DIV_M2_DPLL_GPU_CLKST_CLK_GATED                                                                   (0U)

#define CM_DIV_M2_DPLL_GPU_RESERVED_SHIFT                                                                   (5U)
#define CM_DIV_M2_DPLL_GPU_RESERVED_MASK                                                                    (0x000001e0U)

#define CM_DIV_M2_DPLL_GPU_RESERVED1_SHIFT                                                                  (10U)
#define CM_DIV_M2_DPLL_GPU_RESERVED1_MASK                                                                   (0xfffffc00U)

#define CM_SSC_DELTAMSTEP_DPLL_GPU_DELTAMSTEP_SHIFT                                                         (0U)
#define CM_SSC_DELTAMSTEP_DPLL_GPU_DELTAMSTEP_MASK                                                          (0x000fffffU)

#define CM_SSC_DELTAMSTEP_DPLL_GPU_RESERVED_SHIFT                                                           (20U)
#define CM_SSC_DELTAMSTEP_DPLL_GPU_RESERVED_MASK                                                            (0xfff00000U)

#define CM_SSC_MODFREQDIV_DPLL_GPU_MODFREQDIV_MANTISSA_SHIFT                                                (0U)
#define CM_SSC_MODFREQDIV_DPLL_GPU_MODFREQDIV_MANTISSA_MASK                                                 (0x0000007fU)

#define CM_SSC_MODFREQDIV_DPLL_GPU_MODFREQDIV_EXPONENT_SHIFT                                                (8U)
#define CM_SSC_MODFREQDIV_DPLL_GPU_MODFREQDIV_EXPONENT_MASK                                                 (0x00000700U)

#define CM_SSC_MODFREQDIV_DPLL_GPU_RESERVED_SHIFT                                                           (7U)
#define CM_SSC_MODFREQDIV_DPLL_GPU_RESERVED_MASK                                                            (0x00000080U)

#define CM_SSC_MODFREQDIV_DPLL_GPU_RESERVED1_SHIFT                                                          (11U)
#define CM_SSC_MODFREQDIV_DPLL_GPU_RESERVED1_MASK                                                           (0xfffff800U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_CKGEN_CM_CORE_AON_H_ */
