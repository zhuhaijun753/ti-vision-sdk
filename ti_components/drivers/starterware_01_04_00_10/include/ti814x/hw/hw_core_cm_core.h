/******************************************************************************
*
* hw_core_cm_core.h - register-level header file for PRCM
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
#ifndef HW_CORE_CM_CORE_H_
#define HW_CORE_CM_CORE_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define CM_L3MAIN1_CLKSTCTRL                                                                                (0x0U)
#define CM_L3MAIN1_DYNAMICDEP                                                                               (0x8U)
#define CM_L3MAIN1_L3_MAIN_1_CLKCTRL                                                                        (0x20U)
#define CM_L3MAIN1_GPMC_CLKCTRL                                                                             (0x28U)
#define CM_L3MAIN1_MMU_EDMA_CLKCTRL                                                                         (0x30U)
#define CM_L3MAIN1_MMU_PCIESS_CLKCTRL                                                                       (0x48U)
#define CM_L3MAIN1_OCMC_RAM1_CLKCTRL                                                                        (0x50U)
#define CM_L3MAIN1_OCMC_RAM2_CLKCTRL                                                                        (0x58U)
#define CM_L3MAIN1_OCMC_RAM3_CLKCTRL                                                                        (0x60U)
#define CM_L3MAIN1_OCMC_ROM_CLKCTRL                                                                         (0x68U)
#define CM_L3MAIN1_TPCC_CLKCTRL                                                                             (0x70U)
#define CM_L3MAIN1_TPTC1_CLKCTRL                                                                            (0x78U)
#define CM_L3MAIN1_TPTC2_CLKCTRL                                                                            (0x80U)
#define CM_L3MAIN1_VCP1_CLKCTRL                                                                             (0x88U)
#define CM_L3MAIN1_VCP2_CLKCTRL                                                                             (0x90U)
#define CM_IPU2_CLKSTCTRL                                                                                   (0x200U)
#define CM_IPU2_STATICDEP                                                                                   (0x204U)
#define CM_IPU2_DYNAMICDEP                                                                                  (0x208U)
#define CM_IPU2_IPU2_CLKCTRL                                                                                (0x220U)
#define CM_DMA_CLKSTCTRL                                                                                    (0x300U)
#define CM_DMA_STATICDEP                                                                                    (0x304U)
#define CM_DMA_DYNAMICDEP                                                                                   (0x308U)
#define CM_DMA_DMA_SYSTEM_CLKCTRL                                                                           (0x320U)
#define CM_EMIF_CLKSTCTRL                                                                                   (0x400U)
#define CM_EMIF_DMM_CLKCTRL                                                                                 (0x420U)
#define CM_EMIF_EMIF_OCP_FW_CLKCTRL                                                                         (0x428U)
#define CM_EMIF_EMIF1_CLKCTRL                                                                               (0x430U)
#define CM_EMIF_EMIF2_CLKCTRL                                                                               (0x438U)
#define CM_EMIF_EMIF_DLL_CLKCTRL                                                                            (0x440U)
#define CM_ATL_ATL_CLKCTRL                                                                                  (0x500U)
#define CM_ATL_CLKSTCTRL                                                                                    (0x520U)
#define CM_L4CFG_CLKSTCTRL                                                                                  (0x600U)
#define CM_L4CFG_DYNAMICDEP                                                                                 (0x608U)
#define CM_L4CFG_L4_CFG_CLKCTRL                                                                             (0x620U)
#define CM_L4CFG_SPINLOCK_CLKCTRL                                                                           (0x628U)
#define CM_L4CFG_MAILBOX1_CLKCTRL                                                                           (0x630U)
#define CM_L4CFG_SAR_ROM_CLKCTRL                                                                            (0x638U)
#define CM_L4CFG_OCP2SCP2_CLKCTRL                                                                           (0x640U)
#define CM_L4CFG_MAILBOX2_CLKCTRL                                                                           (0x648U)
#define CM_L4CFG_MAILBOX3_CLKCTRL                                                                           (0x650U)
#define CM_L4CFG_MAILBOX4_CLKCTRL                                                                           (0x658U)
#define CM_L4CFG_MAILBOX5_CLKCTRL                                                                           (0x660U)
#define CM_L4CFG_MAILBOX6_CLKCTRL                                                                           (0x668U)
#define CM_L4CFG_MAILBOX7_CLKCTRL                                                                           (0x670U)
#define CM_L4CFG_MAILBOX8_CLKCTRL                                                                           (0x678U)
#define CM_L4CFG_MAILBOX9_CLKCTRL                                                                           (0x680U)
#define CM_L4CFG_MAILBOX10_CLKCTRL                                                                          (0x688U)
#define CM_L4CFG_MAILBOX11_CLKCTRL                                                                          (0x690U)
#define CM_L4CFG_MAILBOX12_CLKCTRL                                                                          (0x698U)
#define CM_L4CFG_MAILBOX13_CLKCTRL                                                                          (0x6a0U)
#define CM_L3INSTR_CLKSTCTRL                                                                                (0x700U)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL                                                                        (0x720U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL                                                                         (0x728U)
#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL                                                                       (0x740U)
#define CM_L3INSTR_DLL_AGING_CLKCTRL                                                                        (0x748U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL                                                              (0x750U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define CM_L3MAIN1_CLKSTCTRL_CLKTRCTRL_SHIFT                                                                (0U)
#define CM_L3MAIN1_CLKSTCTRL_CLKTRCTRL_MASK                                                                 (0x00000003U)
#define CM_L3MAIN1_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                                                              (0U)
#define CM_L3MAIN1_CLKSTCTRL_CLKTRCTRL_RESERVED_1                                                            (1U)
#define CM_L3MAIN1_CLKSTCTRL_CLKTRCTRL_RESERVED_2                                                            (2U)
#define CM_L3MAIN1_CLKSTCTRL_CLKTRCTRL_HW_AUTO                                                               (3U)

#define CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L3_GICLK_SHIFT                                             (8U)
#define CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L3_GICLK_MASK                                              (0x00000100U)
#define CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L3_GICLK_INACT                                              (0U)
#define CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L3_GICLK_ACT                                                (1U)

#define CM_L3MAIN1_CLKSTCTRL_RESERVED_SHIFT                                                                 (2U)
#define CM_L3MAIN1_CLKSTCTRL_RESERVED_MASK                                                                  (0x000000fcU)

#define CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L4_GICLK_SHIFT                                             (9U)
#define CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L4_GICLK_MASK                                              (0x00000200U)
#define CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L4_GICLK_INACT                                              (0U)
#define CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L4_GICLK_ACT                                                (1U)

#define CM_L3MAIN1_CLKSTCTRL_RESERVED1_SHIFT                                                                (10U)
#define CM_L3MAIN1_CLKSTCTRL_RESERVED1_MASK                                                                 (0xfffffc00U)

#define CM_L3MAIN1_DYNAMICDEP_EMIF_DYNDEP_SHIFT                                                             (4U)
#define CM_L3MAIN1_DYNAMICDEP_EMIF_DYNDEP_MASK                                                              (0x00000010U)
#define CM_L3MAIN1_DYNAMICDEP_EMIF_DYNDEP_ENABLED                                                            (1U)

#define CM_L3MAIN1_DYNAMICDEP_WINDOWSIZE_SHIFT                                                              (24U)
#define CM_L3MAIN1_DYNAMICDEP_WINDOWSIZE_MASK                                                               (0x0f000000U)

#define CM_L3MAIN1_DYNAMICDEP_L4CFG_DYNDEP_SHIFT                                                            (12U)
#define CM_L3MAIN1_DYNAMICDEP_L4CFG_DYNDEP_MASK                                                             (0x00001000U)
#define CM_L3MAIN1_DYNAMICDEP_L4CFG_DYNDEP_ENABLED                                                           (1U)

#define CM_L3MAIN1_DYNAMICDEP_WKUPAON_DYNDEP_SHIFT                                                          (15U)
#define CM_L3MAIN1_DYNAMICDEP_WKUPAON_DYNDEP_MASK                                                           (0x00008000U)
#define CM_L3MAIN1_DYNAMICDEP_WKUPAON_DYNDEP_ENABLED                                                         (1U)

#define CM_L3MAIN1_DYNAMICDEP_IPU2_DYNDEP_SHIFT                                                             (0U)
#define CM_L3MAIN1_DYNAMICDEP_IPU2_DYNDEP_MASK                                                              (0x00000001U)
#define CM_L3MAIN1_DYNAMICDEP_IPU2_DYNDEP_ENABLED                                                            (1U)

#define CM_L3MAIN1_DYNAMICDEP_DSP1_DYNDEP_SHIFT                                                             (1U)
#define CM_L3MAIN1_DYNAMICDEP_DSP1_DYNDEP_MASK                                                              (0x00000002U)
#define CM_L3MAIN1_DYNAMICDEP_DSP1_DYNDEP_ENABLED                                                            (1U)

#define CM_L3MAIN1_DYNAMICDEP_DSP2_DYNDEP_SHIFT                                                             (20U)
#define CM_L3MAIN1_DYNAMICDEP_DSP2_DYNDEP_MASK                                                              (0x00100000U)
#define CM_L3MAIN1_DYNAMICDEP_DSP2_DYNDEP_ENABLED                                                            (1U)

#define CM_L3MAIN1_DYNAMICDEP_DSS_DYNDEP_SHIFT                                                              (8U)
#define CM_L3MAIN1_DYNAMICDEP_DSS_DYNDEP_MASK                                                               (0x00000100U)
#define CM_L3MAIN1_DYNAMICDEP_DSS_DYNDEP_ENABLED                                                             (1U)

#define CM_L3MAIN1_DYNAMICDEP_EVE1_DYNDEP_SHIFT                                                             (28U)
#define CM_L3MAIN1_DYNAMICDEP_EVE1_DYNDEP_MASK                                                              (0x10000000U)
#define CM_L3MAIN1_DYNAMICDEP_EVE1_DYNDEP_ENABLED                                                            (1U)

#define CM_L3MAIN1_DYNAMICDEP_EVE2_DYNDEP_SHIFT                                                             (29U)
#define CM_L3MAIN1_DYNAMICDEP_EVE2_DYNDEP_MASK                                                              (0x20000000U)
#define CM_L3MAIN1_DYNAMICDEP_EVE2_DYNDEP_ENABLED                                                            (1U)

#define CM_L3MAIN1_DYNAMICDEP_EVE3_DYNDEP_SHIFT                                                             (30U)
#define CM_L3MAIN1_DYNAMICDEP_EVE3_DYNDEP_MASK                                                              (0x40000000U)
#define CM_L3MAIN1_DYNAMICDEP_EVE3_DYNDEP_ENABLED                                                            (1U)

#define CM_L3MAIN1_DYNAMICDEP_EVE4_DYNDEP_SHIFT                                                             (31U)
#define CM_L3MAIN1_DYNAMICDEP_EVE4_DYNDEP_MASK                                                              (0x80000000U)
#define CM_L3MAIN1_DYNAMICDEP_EVE4_DYNDEP_ENABLED                                                            (1U)

#define CM_L3MAIN1_DYNAMICDEP_GPU_DYNDEP_SHIFT                                                              (10U)
#define CM_L3MAIN1_DYNAMICDEP_GPU_DYNDEP_MASK                                                               (0x00000400U)
#define CM_L3MAIN1_DYNAMICDEP_GPU_DYNDEP_ENABLED                                                             (1U)

#define CM_L3MAIN1_DYNAMICDEP_IPU1_DYNDEP_SHIFT                                                             (18U)
#define CM_L3MAIN1_DYNAMICDEP_IPU1_DYNDEP_MASK                                                              (0x00040000U)
#define CM_L3MAIN1_DYNAMICDEP_IPU1_DYNDEP_ENABLED                                                            (1U)

#define CM_L3MAIN1_DYNAMICDEP_IPU_DYNDEP_SHIFT                                                              (3U)
#define CM_L3MAIN1_DYNAMICDEP_IPU_DYNDEP_MASK                                                               (0x00000008U)
#define CM_L3MAIN1_DYNAMICDEP_IPU_DYNDEP_ENABLED                                                             (1U)

#define CM_L3MAIN1_DYNAMICDEP_IVA_DYNDEP_SHIFT                                                              (2U)
#define CM_L3MAIN1_DYNAMICDEP_IVA_DYNDEP_MASK                                                               (0x00000004U)
#define CM_L3MAIN1_DYNAMICDEP_IVA_DYNDEP_ENABLED                                                             (1U)

#define CM_L3MAIN1_DYNAMICDEP_L4PER_DYNDEP_SHIFT                                                            (13U)
#define CM_L3MAIN1_DYNAMICDEP_L4PER_DYNDEP_MASK                                                             (0x00002000U)
#define CM_L3MAIN1_DYNAMICDEP_L4PER_DYNDEP_ENABLED                                                           (1U)

#define CM_L3MAIN1_DYNAMICDEP_L4PER2_DYNDEP_SHIFT                                                           (22U)
#define CM_L3MAIN1_DYNAMICDEP_L4PER2_DYNDEP_MASK                                                            (0x00400000U)
#define CM_L3MAIN1_DYNAMICDEP_L4PER2_DYNDEP_ENABLED                                                          (1U)

#define CM_L3MAIN1_DYNAMICDEP_L4PER3_DYNDEP_SHIFT                                                           (23U)
#define CM_L3MAIN1_DYNAMICDEP_L4PER3_DYNDEP_MASK                                                            (0x00800000U)
#define CM_L3MAIN1_DYNAMICDEP_L4PER3_DYNDEP_ENABLED                                                          (1U)

#define CM_L3MAIN1_DYNAMICDEP_L4SEC_DYNDEP_SHIFT                                                            (14U)
#define CM_L3MAIN1_DYNAMICDEP_L4SEC_DYNDEP_MASK                                                             (0x00004000U)
#define CM_L3MAIN1_DYNAMICDEP_L4SEC_DYNDEP_ENABLED                                                           (1U)

#define CM_L3MAIN1_DYNAMICDEP_PCIE_DYNDEP_SHIFT                                                             (21U)
#define CM_L3MAIN1_DYNAMICDEP_PCIE_DYNDEP_MASK                                                              (0x00200000U)
#define CM_L3MAIN1_DYNAMICDEP_PCIE_DYNDEP_ENABLED                                                            (1U)

#define CM_L3MAIN1_DYNAMICDEP_RESERVED_SHIFT                                                                (5U)
#define CM_L3MAIN1_DYNAMICDEP_RESERVED_MASK                                                                 (0x000000e0U)

#define CM_L3MAIN1_DYNAMICDEP_RESERVED1_SHIFT                                                               (9U)
#define CM_L3MAIN1_DYNAMICDEP_RESERVED1_MASK                                                                (0x00000200U)

#define CM_L3MAIN1_DYNAMICDEP_RESERVED2_SHIFT                                                               (11U)
#define CM_L3MAIN1_DYNAMICDEP_RESERVED2_MASK                                                                (0x00000800U)

#define CM_L3MAIN1_DYNAMICDEP_RESERVED3_SHIFT                                                               (16U)
#define CM_L3MAIN1_DYNAMICDEP_RESERVED3_MASK                                                                (0x00030000U)

#define CM_L3MAIN1_DYNAMICDEP_RESERVED4_SHIFT                                                               (19U)
#define CM_L3MAIN1_DYNAMICDEP_RESERVED4_MASK                                                                (0x00080000U)

#define CM_L3MAIN1_L3_MAIN_1_CLKCTRL_MODULEMODE_SHIFT                                                       (0U)
#define CM_L3MAIN1_L3_MAIN_1_CLKCTRL_MODULEMODE_MASK                                                        (0x00000003U)
#define CM_L3MAIN1_L3_MAIN_1_CLKCTRL_MODULEMODE_AUTO                                                         (1U)

#define CM_L3MAIN1_L3_MAIN_1_CLKCTRL_RESERVED_SHIFT                                                         (2U)
#define CM_L3MAIN1_L3_MAIN_1_CLKCTRL_RESERVED_MASK                                                          (0x0000fffcU)

#define CM_L3MAIN1_L3_MAIN_1_CLKCTRL_RESERVED1_SHIFT                                                        (18U)
#define CM_L3MAIN1_L3_MAIN_1_CLKCTRL_RESERVED1_MASK                                                         (0xfffc0000U)

#define CM_L3MAIN1_L3_MAIN_1_CLKCTRL_IDLEST_SHIFT                                                           (16U)
#define CM_L3MAIN1_L3_MAIN_1_CLKCTRL_IDLEST_MASK                                                            (0x00030000U)
#define CM_L3MAIN1_L3_MAIN_1_CLKCTRL_IDLEST_DISABLE                                                          (3U)
#define CM_L3MAIN1_L3_MAIN_1_CLKCTRL_IDLEST_IDLE                                                             (2U)
#define CM_L3MAIN1_L3_MAIN_1_CLKCTRL_IDLEST_FUNC                                                             (0U)
#define CM_L3MAIN1_L3_MAIN_1_CLKCTRL_IDLEST_TRANS                                                            (1U)

#define CM_L3MAIN1_GPMC_CLKCTRL_RESERVED_SHIFT                                                              (2U)
#define CM_L3MAIN1_GPMC_CLKCTRL_RESERVED_MASK                                                               (0x0000fffcU)

#define CM_L3MAIN1_GPMC_CLKCTRL_RESERVED1_SHIFT                                                             (18U)
#define CM_L3MAIN1_GPMC_CLKCTRL_RESERVED1_MASK                                                              (0xfffc0000U)

#define CM_L3MAIN1_GPMC_CLKCTRL_IDLEST_SHIFT                                                                (16U)
#define CM_L3MAIN1_GPMC_CLKCTRL_IDLEST_MASK                                                                 (0x00030000U)
#define CM_L3MAIN1_GPMC_CLKCTRL_IDLEST_DISABLE                                                               (3U)
#define CM_L3MAIN1_GPMC_CLKCTRL_IDLEST_IDLE                                                                  (2U)
#define CM_L3MAIN1_GPMC_CLKCTRL_IDLEST_FUNC                                                                  (0U)
#define CM_L3MAIN1_GPMC_CLKCTRL_IDLEST_TRANS                                                                 (1U)

#define CM_L3MAIN1_GPMC_CLKCTRL_MODULEMODE_SHIFT                                                            (0U)
#define CM_L3MAIN1_GPMC_CLKCTRL_MODULEMODE_MASK                                                             (0x00000003U)
#define CM_L3MAIN1_GPMC_CLKCTRL_MODULEMODE_DISABLED                                                          (0U)
#define CM_L3MAIN1_GPMC_CLKCTRL_MODULEMODE_AUTO                                                              (1U)
#define CM_L3MAIN1_GPMC_CLKCTRL_MODULEMODE_RESERVED_2                                                        (2U)
#define CM_L3MAIN1_GPMC_CLKCTRL_MODULEMODE_RESERVED                                                          (3U)

#define CM_L3MAIN1_MMU_EDMA_CLKCTRL_RESERVED_SHIFT                                                          (2U)
#define CM_L3MAIN1_MMU_EDMA_CLKCTRL_RESERVED_MASK                                                           (0x0000fffcU)

#define CM_L3MAIN1_MMU_EDMA_CLKCTRL_RESERVED1_SHIFT                                                         (18U)
#define CM_L3MAIN1_MMU_EDMA_CLKCTRL_RESERVED1_MASK                                                          (0xfffc0000U)

#define CM_L3MAIN1_MMU_EDMA_CLKCTRL_MODULEMODE_SHIFT                                                        (0U)
#define CM_L3MAIN1_MMU_EDMA_CLKCTRL_MODULEMODE_MASK                                                         (0x00000003U)
#define CM_L3MAIN1_MMU_EDMA_CLKCTRL_MODULEMODE_AUTO                                                          (1U)

#define CM_L3MAIN1_MMU_EDMA_CLKCTRL_IDLEST_SHIFT                                                            (16U)
#define CM_L3MAIN1_MMU_EDMA_CLKCTRL_IDLEST_MASK                                                             (0x00030000U)
#define CM_L3MAIN1_MMU_EDMA_CLKCTRL_IDLEST_DISABLE                                                           (3U)
#define CM_L3MAIN1_MMU_EDMA_CLKCTRL_IDLEST_IDLE                                                              (2U)
#define CM_L3MAIN1_MMU_EDMA_CLKCTRL_IDLEST_FUNC                                                              (0U)
#define CM_L3MAIN1_MMU_EDMA_CLKCTRL_IDLEST_TRANS                                                             (1U)

#define CM_L3MAIN1_MMU_PCIESS_CLKCTRL_RESERVED_SHIFT                                                        (2U)
#define CM_L3MAIN1_MMU_PCIESS_CLKCTRL_RESERVED_MASK                                                         (0x0000fffcU)

#define CM_L3MAIN1_MMU_PCIESS_CLKCTRL_RESERVED1_SHIFT                                                       (18U)
#define CM_L3MAIN1_MMU_PCIESS_CLKCTRL_RESERVED1_MASK                                                        (0xfffc0000U)

#define CM_L3MAIN1_MMU_PCIESS_CLKCTRL_MODULEMODE_SHIFT                                                      (0U)
#define CM_L3MAIN1_MMU_PCIESS_CLKCTRL_MODULEMODE_MASK                                                       (0x00000003U)
#define CM_L3MAIN1_MMU_PCIESS_CLKCTRL_MODULEMODE_AUTO                                                        (1U)

#define CM_L3MAIN1_MMU_PCIESS_CLKCTRL_IDLEST_SHIFT                                                          (16U)
#define CM_L3MAIN1_MMU_PCIESS_CLKCTRL_IDLEST_MASK                                                           (0x00030000U)
#define CM_L3MAIN1_MMU_PCIESS_CLKCTRL_IDLEST_DISABLE                                                         (3U)
#define CM_L3MAIN1_MMU_PCIESS_CLKCTRL_IDLEST_IDLE                                                            (2U)
#define CM_L3MAIN1_MMU_PCIESS_CLKCTRL_IDLEST_FUNC                                                            (0U)
#define CM_L3MAIN1_MMU_PCIESS_CLKCTRL_IDLEST_TRANS                                                           (1U)

#define CM_L3MAIN1_OCMC_RAM1_CLKCTRL_RESERVED_SHIFT                                                         (2U)
#define CM_L3MAIN1_OCMC_RAM1_CLKCTRL_RESERVED_MASK                                                          (0x0000fffcU)

#define CM_L3MAIN1_OCMC_RAM1_CLKCTRL_RESERVED1_SHIFT                                                        (18U)
#define CM_L3MAIN1_OCMC_RAM1_CLKCTRL_RESERVED1_MASK                                                         (0xfffc0000U)

#define CM_L3MAIN1_OCMC_RAM1_CLKCTRL_MODULEMODE_SHIFT                                                       (0U)
#define CM_L3MAIN1_OCMC_RAM1_CLKCTRL_MODULEMODE_MASK                                                        (0x00000003U)
#define CM_L3MAIN1_OCMC_RAM1_CLKCTRL_MODULEMODE_AUTO                                                         (1U)

#define CM_L3MAIN1_OCMC_RAM1_CLKCTRL_IDLEST_SHIFT                                                           (16U)
#define CM_L3MAIN1_OCMC_RAM1_CLKCTRL_IDLEST_MASK                                                            (0x00030000U)
#define CM_L3MAIN1_OCMC_RAM1_CLKCTRL_IDLEST_DISABLE                                                          (3U)
#define CM_L3MAIN1_OCMC_RAM1_CLKCTRL_IDLEST_IDLE                                                             (2U)
#define CM_L3MAIN1_OCMC_RAM1_CLKCTRL_IDLEST_FUNC                                                             (0U)
#define CM_L3MAIN1_OCMC_RAM1_CLKCTRL_IDLEST_TRANS                                                            (1U)

#define CM_L3MAIN1_OCMC_RAM2_CLKCTRL_RESERVED_SHIFT                                                         (2U)
#define CM_L3MAIN1_OCMC_RAM2_CLKCTRL_RESERVED_MASK                                                          (0x0000fffcU)

#define CM_L3MAIN1_OCMC_RAM2_CLKCTRL_RESERVED1_SHIFT                                                        (18U)
#define CM_L3MAIN1_OCMC_RAM2_CLKCTRL_RESERVED1_MASK                                                         (0xfffc0000U)

#define CM_L3MAIN1_OCMC_RAM2_CLKCTRL_MODULEMODE_SHIFT                                                       (0U)
#define CM_L3MAIN1_OCMC_RAM2_CLKCTRL_MODULEMODE_MASK                                                        (0x00000003U)
#define CM_L3MAIN1_OCMC_RAM2_CLKCTRL_MODULEMODE_AUTO                                                         (1U)

#define CM_L3MAIN1_OCMC_RAM2_CLKCTRL_IDLEST_SHIFT                                                           (16U)
#define CM_L3MAIN1_OCMC_RAM2_CLKCTRL_IDLEST_MASK                                                            (0x00030000U)
#define CM_L3MAIN1_OCMC_RAM2_CLKCTRL_IDLEST_DISABLE                                                          (3U)
#define CM_L3MAIN1_OCMC_RAM2_CLKCTRL_IDLEST_IDLE                                                             (2U)
#define CM_L3MAIN1_OCMC_RAM2_CLKCTRL_IDLEST_FUNC                                                             (0U)
#define CM_L3MAIN1_OCMC_RAM2_CLKCTRL_IDLEST_TRANS                                                            (1U)

#define CM_L3MAIN1_OCMC_RAM3_CLKCTRL_RESERVED_SHIFT                                                         (2U)
#define CM_L3MAIN1_OCMC_RAM3_CLKCTRL_RESERVED_MASK                                                          (0x0000fffcU)

#define CM_L3MAIN1_OCMC_RAM3_CLKCTRL_RESERVED1_SHIFT                                                        (18U)
#define CM_L3MAIN1_OCMC_RAM3_CLKCTRL_RESERVED1_MASK                                                         (0xfffc0000U)

#define CM_L3MAIN1_OCMC_RAM3_CLKCTRL_MODULEMODE_SHIFT                                                       (0U)
#define CM_L3MAIN1_OCMC_RAM3_CLKCTRL_MODULEMODE_MASK                                                        (0x00000003U)
#define CM_L3MAIN1_OCMC_RAM3_CLKCTRL_MODULEMODE_AUTO                                                         (1U)

#define CM_L3MAIN1_OCMC_RAM3_CLKCTRL_IDLEST_SHIFT                                                           (16U)
#define CM_L3MAIN1_OCMC_RAM3_CLKCTRL_IDLEST_MASK                                                            (0x00030000U)
#define CM_L3MAIN1_OCMC_RAM3_CLKCTRL_IDLEST_DISABLE                                                          (3U)
#define CM_L3MAIN1_OCMC_RAM3_CLKCTRL_IDLEST_IDLE                                                             (2U)
#define CM_L3MAIN1_OCMC_RAM3_CLKCTRL_IDLEST_FUNC                                                             (0U)
#define CM_L3MAIN1_OCMC_RAM3_CLKCTRL_IDLEST_TRANS                                                            (1U)

#define CM_L3MAIN1_OCMC_ROM_CLKCTRL_RESERVED_SHIFT                                                          (2U)
#define CM_L3MAIN1_OCMC_ROM_CLKCTRL_RESERVED_MASK                                                           (0x0000fffcU)

#define CM_L3MAIN1_OCMC_ROM_CLKCTRL_RESERVED1_SHIFT                                                         (18U)
#define CM_L3MAIN1_OCMC_ROM_CLKCTRL_RESERVED1_MASK                                                          (0xfffc0000U)

#define CM_L3MAIN1_OCMC_ROM_CLKCTRL_MODULEMODE_SHIFT                                                        (0U)
#define CM_L3MAIN1_OCMC_ROM_CLKCTRL_MODULEMODE_MASK                                                         (0x00000003U)
#define CM_L3MAIN1_OCMC_ROM_CLKCTRL_MODULEMODE_AUTO                                                          (1U)

#define CM_L3MAIN1_OCMC_ROM_CLKCTRL_IDLEST_SHIFT                                                            (16U)
#define CM_L3MAIN1_OCMC_ROM_CLKCTRL_IDLEST_MASK                                                             (0x00030000U)
#define CM_L3MAIN1_OCMC_ROM_CLKCTRL_IDLEST_DISABLE                                                           (3U)
#define CM_L3MAIN1_OCMC_ROM_CLKCTRL_IDLEST_IDLE                                                              (2U)
#define CM_L3MAIN1_OCMC_ROM_CLKCTRL_IDLEST_FUNC                                                              (0U)
#define CM_L3MAIN1_OCMC_ROM_CLKCTRL_IDLEST_TRANS                                                             (1U)

#define CM_L3MAIN1_TPCC_CLKCTRL_RESERVED_SHIFT                                                              (2U)
#define CM_L3MAIN1_TPCC_CLKCTRL_RESERVED_MASK                                                               (0x0000fffcU)

#define CM_L3MAIN1_TPCC_CLKCTRL_MODULEMODE_SHIFT                                                            (0U)
#define CM_L3MAIN1_TPCC_CLKCTRL_MODULEMODE_MASK                                                             (0x00000003U)
#define CM_L3MAIN1_TPCC_CLKCTRL_MODULEMODE_AUTO                                                              (1U)

#define CM_L3MAIN1_TPCC_CLKCTRL_IDLEST_SHIFT                                                                (16U)
#define CM_L3MAIN1_TPCC_CLKCTRL_IDLEST_MASK                                                                 (0x00030000U)
#define CM_L3MAIN1_TPCC_CLKCTRL_IDLEST_DISABLE                                                               (3U)
#define CM_L3MAIN1_TPCC_CLKCTRL_IDLEST_IDLE                                                                  (2U)
#define CM_L3MAIN1_TPCC_CLKCTRL_IDLEST_FUNC                                                                  (0U)
#define CM_L3MAIN1_TPCC_CLKCTRL_IDLEST_TRANS                                                                 (1U)

#define CM_L3MAIN1_TPCC_CLKCTRL_RESERVED1_SHIFT                                                             (18U)
#define CM_L3MAIN1_TPCC_CLKCTRL_RESERVED1_MASK                                                              (0xfffc0000U)

#define CM_L3MAIN1_TPTC1_CLKCTRL_RESERVED_SHIFT                                                             (2U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_RESERVED_MASK                                                              (0x0000fffcU)

#define CM_L3MAIN1_TPTC1_CLKCTRL_RESERVED1_SHIFT                                                            (19U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_RESERVED1_MASK                                                             (0xfff80000U)

#define CM_L3MAIN1_TPTC1_CLKCTRL_STBYST_SHIFT                                                               (18U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_STBYST_MASK                                                                (0x00040000U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_STBYST_FUNC                                                                 (0U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_STBYST_STANDBY                                                              (1U)

#define CM_L3MAIN1_TPTC1_CLKCTRL_IDLEST_SHIFT                                                               (16U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_IDLEST_MASK                                                                (0x00030000U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_IDLEST_DISABLE                                                              (3U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_IDLEST_IDLE                                                                 (2U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_IDLEST_FUNC                                                                 (0U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_IDLEST_TRANS                                                                (1U)

#define CM_L3MAIN1_TPTC1_CLKCTRL_MODULEMODE_SHIFT                                                           (0U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_MODULEMODE_MASK                                                            (0x00000003U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_MODULEMODE_DISABLED                                                         (0U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_MODULEMODE_AUTO                                                             (1U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_MODULEMODE_RESERVED_2                                                       (2U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_MODULEMODE_RESERVED                                                         (3U)

#define CM_L3MAIN1_TPTC2_CLKCTRL_RESERVED_SHIFT                                                             (2U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_RESERVED_MASK                                                              (0x0000fffcU)

#define CM_L3MAIN1_TPTC2_CLKCTRL_RESERVED1_SHIFT                                                            (19U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_RESERVED1_MASK                                                             (0xfff80000U)

#define CM_L3MAIN1_TPTC2_CLKCTRL_STBYST_SHIFT                                                               (18U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_STBYST_MASK                                                                (0x00040000U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_STBYST_FUNC                                                                 (0U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_STBYST_STANDBY                                                              (1U)

#define CM_L3MAIN1_TPTC2_CLKCTRL_IDLEST_SHIFT                                                               (16U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_IDLEST_MASK                                                                (0x00030000U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_IDLEST_DISABLE                                                              (3U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_IDLEST_IDLE                                                                 (2U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_IDLEST_FUNC                                                                 (0U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_IDLEST_TRANS                                                                (1U)

#define CM_L3MAIN1_TPTC2_CLKCTRL_MODULEMODE_SHIFT                                                           (0U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_MODULEMODE_MASK                                                            (0x00000003U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_MODULEMODE_DISABLED                                                         (0U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_MODULEMODE_AUTO                                                             (1U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_MODULEMODE_RESERVED_2                                                       (2U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_MODULEMODE_RESERVED                                                         (3U)

#define CM_L3MAIN1_VCP1_CLKCTRL_RESERVED_SHIFT                                                              (2U)
#define CM_L3MAIN1_VCP1_CLKCTRL_RESERVED_MASK                                                               (0x0000fffcU)

#define CM_L3MAIN1_VCP1_CLKCTRL_MODULEMODE_SHIFT                                                            (0U)
#define CM_L3MAIN1_VCP1_CLKCTRL_MODULEMODE_MASK                                                             (0x00000003U)
#define CM_L3MAIN1_VCP1_CLKCTRL_MODULEMODE_AUTO                                                              (1U)

#define CM_L3MAIN1_VCP1_CLKCTRL_IDLEST_SHIFT                                                                (16U)
#define CM_L3MAIN1_VCP1_CLKCTRL_IDLEST_MASK                                                                 (0x00030000U)
#define CM_L3MAIN1_VCP1_CLKCTRL_IDLEST_DISABLE                                                               (3U)
#define CM_L3MAIN1_VCP1_CLKCTRL_IDLEST_IDLE                                                                  (2U)
#define CM_L3MAIN1_VCP1_CLKCTRL_IDLEST_FUNC                                                                  (0U)
#define CM_L3MAIN1_VCP1_CLKCTRL_IDLEST_TRANS                                                                 (1U)

#define CM_L3MAIN1_VCP1_CLKCTRL_RESERVED1_SHIFT                                                             (18U)
#define CM_L3MAIN1_VCP1_CLKCTRL_RESERVED1_MASK                                                              (0xfffc0000U)

#define CM_L3MAIN1_VCP2_CLKCTRL_RESERVED_SHIFT                                                              (2U)
#define CM_L3MAIN1_VCP2_CLKCTRL_RESERVED_MASK                                                               (0x0000fffcU)

#define CM_L3MAIN1_VCP2_CLKCTRL_MODULEMODE_SHIFT                                                            (0U)
#define CM_L3MAIN1_VCP2_CLKCTRL_MODULEMODE_MASK                                                             (0x00000003U)
#define CM_L3MAIN1_VCP2_CLKCTRL_MODULEMODE_AUTO                                                              (1U)

#define CM_L3MAIN1_VCP2_CLKCTRL_IDLEST_SHIFT                                                                (16U)
#define CM_L3MAIN1_VCP2_CLKCTRL_IDLEST_MASK                                                                 (0x00030000U)
#define CM_L3MAIN1_VCP2_CLKCTRL_IDLEST_DISABLE                                                               (3U)
#define CM_L3MAIN1_VCP2_CLKCTRL_IDLEST_IDLE                                                                  (2U)
#define CM_L3MAIN1_VCP2_CLKCTRL_IDLEST_FUNC                                                                  (0U)
#define CM_L3MAIN1_VCP2_CLKCTRL_IDLEST_TRANS                                                                 (1U)

#define CM_L3MAIN1_VCP2_CLKCTRL_RESERVED1_SHIFT                                                             (18U)
#define CM_L3MAIN1_VCP2_CLKCTRL_RESERVED1_MASK                                                              (0xfffc0000U)

#define CM_IPU2_CLKSTCTRL_CLKTRCTRL_SHIFT                                                                   (0U)
#define CM_IPU2_CLKSTCTRL_CLKTRCTRL_MASK                                                                    (0x00000003U)
#define CM_IPU2_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                                                                 (0U)
#define CM_IPU2_CLKSTCTRL_CLKTRCTRL_SW_SLEEP                                                                 (1U)
#define CM_IPU2_CLKSTCTRL_CLKTRCTRL_SW_WKUP                                                                  (2U)
#define CM_IPU2_CLKSTCTRL_CLKTRCTRL_HW_AUTO                                                                  (3U)

#define CM_IPU2_CLKSTCTRL_CLKACTIVITY_IPU2_GFCLK_SHIFT                                                      (8U)
#define CM_IPU2_CLKSTCTRL_CLKACTIVITY_IPU2_GFCLK_MASK                                                       (0x00000100U)
#define CM_IPU2_CLKSTCTRL_CLKACTIVITY_IPU2_GFCLK_INACT                                                       (0U)
#define CM_IPU2_CLKSTCTRL_CLKACTIVITY_IPU2_GFCLK_ACT                                                         (1U)

#define CM_IPU2_CLKSTCTRL_RESERVED_SHIFT                                                                    (2U)
#define CM_IPU2_CLKSTCTRL_RESERVED_MASK                                                                     (0x000000fcU)

#define CM_IPU2_CLKSTCTRL_RESERVED1_SHIFT                                                                   (9U)
#define CM_IPU2_CLKSTCTRL_RESERVED1_MASK                                                                    (0xfffffe00U)

#define CM_IPU2_STATICDEP_DSP1_STATDEP_SHIFT                                                                (1U)
#define CM_IPU2_STATICDEP_DSP1_STATDEP_MASK                                                                 (0x00000002U)
#define CM_IPU2_STATICDEP_DSP1_STATDEP_ENABLED                                                               (1U)
#define CM_IPU2_STATICDEP_DSP1_STATDEP_DISABLED                                                              (0U)

#define CM_IPU2_STATICDEP_IVA_STATDEP_SHIFT                                                                 (2U)
#define CM_IPU2_STATICDEP_IVA_STATDEP_MASK                                                                  (0x00000004U)
#define CM_IPU2_STATICDEP_IVA_STATDEP_ENABLED                                                                (1U)
#define CM_IPU2_STATICDEP_IVA_STATDEP_DISABLED                                                               (0U)

#define CM_IPU2_STATICDEP_EMIF_STATDEP_SHIFT                                                                (4U)
#define CM_IPU2_STATICDEP_EMIF_STATDEP_MASK                                                                 (0x00000010U)
#define CM_IPU2_STATICDEP_EMIF_STATDEP_ENABLED                                                               (1U)
#define CM_IPU2_STATICDEP_EMIF_STATDEP_DISABLED                                                              (0U)

#define CM_IPU2_STATICDEP_L3MAIN1_STATDEP_SHIFT                                                             (5U)
#define CM_IPU2_STATICDEP_L3MAIN1_STATDEP_MASK                                                              (0x00000020U)
#define CM_IPU2_STATICDEP_L3MAIN1_STATDEP_ENABLED                                                            (1U)
#define CM_IPU2_STATICDEP_L3MAIN1_STATDEP_DISABLED                                                           (0U)

#define CM_IPU2_STATICDEP_L3INIT_STATDEP_SHIFT                                                              (7U)
#define CM_IPU2_STATICDEP_L3INIT_STATDEP_MASK                                                               (0x00000080U)
#define CM_IPU2_STATICDEP_L3INIT_STATDEP_ENABLED                                                             (1U)
#define CM_IPU2_STATICDEP_L3INIT_STATDEP_DISABLED                                                            (0U)

#define CM_IPU2_STATICDEP_DSS_STATDEP_SHIFT                                                                 (8U)
#define CM_IPU2_STATICDEP_DSS_STATDEP_MASK                                                                  (0x00000100U)
#define CM_IPU2_STATICDEP_DSS_STATDEP_ENABLED                                                                (1U)
#define CM_IPU2_STATICDEP_DSS_STATDEP_DISABLED                                                               (0U)

#define CM_IPU2_STATICDEP_CAM_STATDEP_SHIFT                                                                 (9U)
#define CM_IPU2_STATICDEP_CAM_STATDEP_MASK                                                                  (0x00000200U)
#define CM_IPU2_STATICDEP_CAM_STATDEP_DISABLED                                                               (0U)

#define CM_IPU2_STATICDEP_GPU_STATDEP_SHIFT                                                                 (10U)
#define CM_IPU2_STATICDEP_GPU_STATDEP_MASK                                                                  (0x00000400U)
#define CM_IPU2_STATICDEP_GPU_STATDEP_ENABLED                                                                (1U)
#define CM_IPU2_STATICDEP_GPU_STATDEP_DISABLED                                                               (0U)

#define CM_IPU2_STATICDEP_L4CFG_STATDEP_SHIFT                                                               (12U)
#define CM_IPU2_STATICDEP_L4CFG_STATDEP_MASK                                                                (0x00001000U)
#define CM_IPU2_STATICDEP_L4CFG_STATDEP_ENABLED                                                              (1U)
#define CM_IPU2_STATICDEP_L4CFG_STATDEP_DISABLED                                                             (0U)

#define CM_IPU2_STATICDEP_L4PER_STATDEP_SHIFT                                                               (13U)
#define CM_IPU2_STATICDEP_L4PER_STATDEP_MASK                                                                (0x00002000U)
#define CM_IPU2_STATICDEP_L4PER_STATDEP_ENABLED                                                              (1U)
#define CM_IPU2_STATICDEP_L4PER_STATDEP_DISABLED                                                             (0U)

#define CM_IPU2_STATICDEP_L4SEC_STATDEP_SHIFT                                                               (14U)
#define CM_IPU2_STATICDEP_L4SEC_STATDEP_MASK                                                                (0x00004000U)
#define CM_IPU2_STATICDEP_L4SEC_STATDEP_ENABLED                                                              (1U)
#define CM_IPU2_STATICDEP_L4SEC_STATDEP_DISABLED                                                             (0U)

#define CM_IPU2_STATICDEP_COREAON_STATDEP_SHIFT                                                             (16U)
#define CM_IPU2_STATICDEP_COREAON_STATDEP_MASK                                                              (0x00010000U)
#define CM_IPU2_STATICDEP_COREAON_STATDEP_DISABLED                                                           (0U)

#define CM_IPU2_STATICDEP_CUSTEFUSE_STATDEP_SHIFT                                                           (17U)
#define CM_IPU2_STATICDEP_CUSTEFUSE_STATDEP_MASK                                                            (0x00020000U)
#define CM_IPU2_STATICDEP_CUSTEFUSE_STATDEP_DISABLED                                                         (0U)

#define CM_IPU2_STATICDEP_SDMA_STATDEP_SHIFT                                                                (11U)
#define CM_IPU2_STATICDEP_SDMA_STATDEP_MASK                                                                 (0x00000800U)
#define CM_IPU2_STATICDEP_SDMA_STATDEP_DISABLED                                                              (0U)

#define CM_IPU2_STATICDEP_WKUPAON_STATDEP_SHIFT                                                             (15U)
#define CM_IPU2_STATICDEP_WKUPAON_STATDEP_MASK                                                              (0x00008000U)
#define CM_IPU2_STATICDEP_WKUPAON_STATDEP_ENABLED                                                            (1U)
#define CM_IPU2_STATICDEP_WKUPAON_STATDEP_DISABLED                                                           (0U)

#define CM_IPU2_STATICDEP_ATL_STATDEP_SHIFT                                                                 (30U)
#define CM_IPU2_STATICDEP_ATL_STATDEP_MASK                                                                  (0x40000000U)
#define CM_IPU2_STATICDEP_ATL_STATDEP_ENABLED                                                                (1U)
#define CM_IPU2_STATICDEP_ATL_STATDEP_DISABLED                                                               (0U)

#define CM_IPU2_STATICDEP_DSP2_STATDEP_SHIFT                                                                (18U)
#define CM_IPU2_STATICDEP_DSP2_STATDEP_MASK                                                                 (0x00040000U)
#define CM_IPU2_STATICDEP_DSP2_STATDEP_ENABLED                                                               (1U)
#define CM_IPU2_STATICDEP_DSP2_STATDEP_DISABLED                                                              (0U)

#define CM_IPU2_STATICDEP_EVE1_STATDEP_SHIFT                                                                (19U)
#define CM_IPU2_STATICDEP_EVE1_STATDEP_MASK                                                                 (0x00080000U)
#define CM_IPU2_STATICDEP_EVE1_STATDEP_ENABLED                                                               (1U)
#define CM_IPU2_STATICDEP_EVE1_STATDEP_DISABLED                                                              (0U)

#define CM_IPU2_STATICDEP_EVE3_STATDEP_SHIFT                                                                (21U)
#define CM_IPU2_STATICDEP_EVE3_STATDEP_MASK                                                                 (0x00200000U)
#define CM_IPU2_STATICDEP_EVE3_STATDEP_ENABLED                                                               (1U)
#define CM_IPU2_STATICDEP_EVE3_STATDEP_DISABLED                                                              (0U)

#define CM_IPU2_STATICDEP_EVE2_STATDEP_SHIFT                                                                (20U)
#define CM_IPU2_STATICDEP_EVE2_STATDEP_MASK                                                                 (0x00100000U)
#define CM_IPU2_STATICDEP_EVE2_STATDEP_ENABLED                                                               (1U)
#define CM_IPU2_STATICDEP_EVE2_STATDEP_DISABLED                                                              (0U)

#define CM_IPU2_STATICDEP_EVE4_STATDEP_SHIFT                                                                (22U)
#define CM_IPU2_STATICDEP_EVE4_STATDEP_MASK                                                                 (0x00400000U)
#define CM_IPU2_STATICDEP_EVE4_STATDEP_ENABLED                                                               (1U)
#define CM_IPU2_STATICDEP_EVE4_STATDEP_DISABLED                                                              (0U)

#define CM_IPU2_STATICDEP_IPU1_STATDEP_SHIFT                                                                (23U)
#define CM_IPU2_STATICDEP_IPU1_STATDEP_MASK                                                                 (0x00800000U)
#define CM_IPU2_STATICDEP_IPU1_STATDEP_ENABLED                                                               (1U)
#define CM_IPU2_STATICDEP_IPU1_STATDEP_DISABLED                                                              (0U)

#define CM_IPU2_STATICDEP_IPU_STATDEP_SHIFT                                                                 (24U)
#define CM_IPU2_STATICDEP_IPU_STATDEP_MASK                                                                  (0x01000000U)
#define CM_IPU2_STATICDEP_IPU_STATDEP_ENABLED                                                                (1U)
#define CM_IPU2_STATICDEP_IPU_STATDEP_DISABLED                                                               (0U)

#define CM_IPU2_STATICDEP_GMAC_STATDEP_SHIFT                                                                (25U)
#define CM_IPU2_STATICDEP_GMAC_STATDEP_MASK                                                                 (0x02000000U)
#define CM_IPU2_STATICDEP_GMAC_STATDEP_ENABLED                                                               (1U)
#define CM_IPU2_STATICDEP_GMAC_STATDEP_DISABLED                                                              (0U)

#define CM_IPU2_STATICDEP_L4PER3_STATDEP_SHIFT                                                              (27U)
#define CM_IPU2_STATICDEP_L4PER3_STATDEP_MASK                                                               (0x08000000U)
#define CM_IPU2_STATICDEP_L4PER3_STATDEP_ENABLED                                                             (1U)
#define CM_IPU2_STATICDEP_L4PER3_STATDEP_DISABLED                                                            (0U)

#define CM_IPU2_STATICDEP_L4PER2_STATDEP_SHIFT                                                              (26U)
#define CM_IPU2_STATICDEP_L4PER2_STATDEP_MASK                                                               (0x04000000U)
#define CM_IPU2_STATICDEP_L4PER2_STATDEP_ENABLED                                                             (1U)
#define CM_IPU2_STATICDEP_L4PER2_STATDEP_DISABLED                                                            (0U)

#define CM_IPU2_STATICDEP_PCIE_STATDEP_SHIFT                                                                (29U)
#define CM_IPU2_STATICDEP_PCIE_STATDEP_MASK                                                                 (0x20000000U)
#define CM_IPU2_STATICDEP_PCIE_STATDEP_ENABLED                                                               (1U)
#define CM_IPU2_STATICDEP_PCIE_STATDEP_DISABLED                                                              (0U)

#define CM_IPU2_STATICDEP_VPE_STATDEP_SHIFT                                                                 (28U)
#define CM_IPU2_STATICDEP_VPE_STATDEP_MASK                                                                  (0x10000000U)
#define CM_IPU2_STATICDEP_VPE_STATDEP_ENABLED                                                                (1U)
#define CM_IPU2_STATICDEP_VPE_STATDEP_DISABLED                                                               (0U)

#define CM_IPU2_STATICDEP_RESERVED_SHIFT                                                                    (0U)
#define CM_IPU2_STATICDEP_RESERVED_MASK                                                                     (0x00000001U)

#define CM_IPU2_STATICDEP_RESERVED1_SHIFT                                                                   (3U)
#define CM_IPU2_STATICDEP_RESERVED1_MASK                                                                    (0x00000008U)

#define CM_IPU2_STATICDEP_RESERVED2_SHIFT                                                                   (6U)
#define CM_IPU2_STATICDEP_RESERVED2_MASK                                                                    (0x00000040U)

#define CM_IPU2_STATICDEP_RESERVED3_SHIFT                                                                   (31U)
#define CM_IPU2_STATICDEP_RESERVED3_MASK                                                                    (0x80000000U)

#define CM_IPU2_DYNAMICDEP_L3MAIN1_DYNDEP_SHIFT                                                             (5U)
#define CM_IPU2_DYNAMICDEP_L3MAIN1_DYNDEP_MASK                                                              (0x00000020U)
#define CM_IPU2_DYNAMICDEP_L3MAIN1_DYNDEP_ENABLED                                                            (1U)

#define CM_IPU2_DYNAMICDEP_CAM_DYNDEP_SHIFT                                                                 (9U)
#define CM_IPU2_DYNAMICDEP_CAM_DYNDEP_MASK                                                                  (0x00000200U)
#define CM_IPU2_DYNAMICDEP_CAM_DYNDEP_DISABLED                                                               (0U)

#define CM_IPU2_DYNAMICDEP_RESERVED2_SHIFT                                                                  (10U)
#define CM_IPU2_DYNAMICDEP_RESERVED2_MASK                                                                   (0x00fffc00U)

#define CM_IPU2_DYNAMICDEP_RESERVED3_SHIFT                                                                  (28U)
#define CM_IPU2_DYNAMICDEP_RESERVED3_MASK                                                                   (0xf0000000U)

#define CM_IPU2_DYNAMICDEP_WINDOWSIZE_SHIFT                                                                 (24U)
#define CM_IPU2_DYNAMICDEP_WINDOWSIZE_MASK                                                                  (0x0f000000U)

#define CM_IPU2_DYNAMICDEP_RESERVED_SHIFT                                                                   (0U)
#define CM_IPU2_DYNAMICDEP_RESERVED_MASK                                                                    (0x0000001fU)

#define CM_IPU2_DYNAMICDEP_RESERVED1_SHIFT                                                                  (6U)
#define CM_IPU2_DYNAMICDEP_RESERVED1_MASK                                                                   (0x000001c0U)

#define CM_IPU2_IPU2_CLKCTRL_RESERVED_SHIFT                                                                 (2U)
#define CM_IPU2_IPU2_CLKCTRL_RESERVED_MASK                                                                  (0x0000fffcU)

#define CM_IPU2_IPU2_CLKCTRL_RESERVED1_SHIFT                                                                (19U)
#define CM_IPU2_IPU2_CLKCTRL_RESERVED1_MASK                                                                 (0xfff80000U)

#define CM_IPU2_IPU2_CLKCTRL_STBYST_SHIFT                                                                   (18U)
#define CM_IPU2_IPU2_CLKCTRL_STBYST_MASK                                                                    (0x00040000U)
#define CM_IPU2_IPU2_CLKCTRL_STBYST_FUNC                                                                     (0U)
#define CM_IPU2_IPU2_CLKCTRL_STBYST_STANDBY                                                                  (1U)

#define CM_IPU2_IPU2_CLKCTRL_IDLEST_SHIFT                                                                   (16U)
#define CM_IPU2_IPU2_CLKCTRL_IDLEST_MASK                                                                    (0x00030000U)
#define CM_IPU2_IPU2_CLKCTRL_IDLEST_DISABLE                                                                  (3U)
#define CM_IPU2_IPU2_CLKCTRL_IDLEST_IDLE                                                                     (2U)
#define CM_IPU2_IPU2_CLKCTRL_IDLEST_FUNC                                                                     (0U)
#define CM_IPU2_IPU2_CLKCTRL_IDLEST_TRANS                                                                    (1U)

#define CM_IPU2_IPU2_CLKCTRL_MODULEMODE_SHIFT                                                               (0U)
#define CM_IPU2_IPU2_CLKCTRL_MODULEMODE_MASK                                                                (0x00000003U)
#define CM_IPU2_IPU2_CLKCTRL_MODULEMODE_DISABLED                                                             (0U)
#define CM_IPU2_IPU2_CLKCTRL_MODULEMODE_AUTO                                                                 (1U)
#define CM_IPU2_IPU2_CLKCTRL_MODULEMODE_RESERVED_2                                                           (2U)
#define CM_IPU2_IPU2_CLKCTRL_MODULEMODE_RESERVED                                                             (3U)

#define CM_DMA_CLKSTCTRL_CLKTRCTRL_SHIFT                                                                    (0U)
#define CM_DMA_CLKSTCTRL_CLKTRCTRL_MASK                                                                     (0x00000003U)
#define CM_DMA_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                                                                  (0U)
#define CM_DMA_CLKSTCTRL_CLKTRCTRL_RESERVED_1                                                                (1U)
#define CM_DMA_CLKSTCTRL_CLKTRCTRL_SW_WKUP                                                                   (2U)
#define CM_DMA_CLKSTCTRL_CLKTRCTRL_HW_AUTO                                                                   (3U)

#define CM_DMA_CLKSTCTRL_CLKACTIVITY_DMA_L3_GICLK_SHIFT                                                     (8U)
#define CM_DMA_CLKSTCTRL_CLKACTIVITY_DMA_L3_GICLK_MASK                                                      (0x00000100U)
#define CM_DMA_CLKSTCTRL_CLKACTIVITY_DMA_L3_GICLK_INACT                                                      (0U)
#define CM_DMA_CLKSTCTRL_CLKACTIVITY_DMA_L3_GICLK_ACT                                                        (1U)

#define CM_DMA_CLKSTCTRL_RESERVED_SHIFT                                                                     (2U)
#define CM_DMA_CLKSTCTRL_RESERVED_MASK                                                                      (0x000000fcU)

#define CM_DMA_CLKSTCTRL_RESERVED1_SHIFT                                                                    (9U)
#define CM_DMA_CLKSTCTRL_RESERVED1_MASK                                                                     (0xfffffe00U)

#define CM_DMA_STATICDEP_IPU2_STATDEP_SHIFT                                                                 (0U)
#define CM_DMA_STATICDEP_IPU2_STATDEP_MASK                                                                  (0x00000001U)
#define CM_DMA_STATICDEP_IPU2_STATDEP_ENABLED                                                                (1U)
#define CM_DMA_STATICDEP_IPU2_STATDEP_DISABLED                                                               (0U)

#define CM_DMA_STATICDEP_IVA_STATDEP_SHIFT                                                                  (2U)
#define CM_DMA_STATICDEP_IVA_STATDEP_MASK                                                                   (0x00000004U)
#define CM_DMA_STATICDEP_IVA_STATDEP_ENABLED                                                                 (1U)
#define CM_DMA_STATICDEP_IVA_STATDEP_DISABLED                                                                (0U)

#define CM_DMA_STATICDEP_IPU_STATDEP_SHIFT                                                                  (24U)
#define CM_DMA_STATICDEP_IPU_STATDEP_MASK                                                                   (0x01000000U)
#define CM_DMA_STATICDEP_IPU_STATDEP_ENABLED                                                                 (1U)
#define CM_DMA_STATICDEP_IPU_STATDEP_DISABLED                                                                (0U)

#define CM_DMA_STATICDEP_EMIF_STATDEP_SHIFT                                                                 (4U)
#define CM_DMA_STATICDEP_EMIF_STATDEP_MASK                                                                  (0x00000010U)
#define CM_DMA_STATICDEP_EMIF_STATDEP_ENABLED                                                                (1U)
#define CM_DMA_STATICDEP_EMIF_STATDEP_DISABLED                                                               (0U)

#define CM_DMA_STATICDEP_L3MAIN1_STATDEP_SHIFT                                                              (5U)
#define CM_DMA_STATICDEP_L3MAIN1_STATDEP_MASK                                                               (0x00000020U)
#define CM_DMA_STATICDEP_L3MAIN1_STATDEP_ENABLED                                                             (1U)

#define CM_DMA_STATICDEP_L3INIT_STATDEP_SHIFT                                                               (7U)
#define CM_DMA_STATICDEP_L3INIT_STATDEP_MASK                                                                (0x00000080U)
#define CM_DMA_STATICDEP_L3INIT_STATDEP_ENABLED                                                              (1U)
#define CM_DMA_STATICDEP_L3INIT_STATDEP_DISABLED                                                             (0U)

#define CM_DMA_STATICDEP_DSS_STATDEP_SHIFT                                                                  (8U)
#define CM_DMA_STATICDEP_DSS_STATDEP_MASK                                                                   (0x00000100U)
#define CM_DMA_STATICDEP_DSS_STATDEP_ENABLED                                                                 (1U)
#define CM_DMA_STATICDEP_DSS_STATDEP_DISABLED                                                                (0U)

#define CM_DMA_STATICDEP_CAM_STATDEP_SHIFT                                                                  (9U)
#define CM_DMA_STATICDEP_CAM_STATDEP_MASK                                                                   (0x00000200U)
#define CM_DMA_STATICDEP_CAM_STATDEP_DISABLED                                                                (0U)

#define CM_DMA_STATICDEP_L4PER_STATDEP_SHIFT                                                                (13U)
#define CM_DMA_STATICDEP_L4PER_STATDEP_MASK                                                                 (0x00002000U)
#define CM_DMA_STATICDEP_L4PER_STATDEP_ENABLED                                                               (1U)
#define CM_DMA_STATICDEP_L4PER_STATDEP_DISABLED                                                              (0U)

#define CM_DMA_STATICDEP_L4SEC_STATDEP_SHIFT                                                                (14U)
#define CM_DMA_STATICDEP_L4SEC_STATDEP_MASK                                                                 (0x00004000U)
#define CM_DMA_STATICDEP_L4SEC_STATDEP_ENABLED                                                               (1U)
#define CM_DMA_STATICDEP_L4SEC_STATDEP_DISABLED                                                              (0U)

#define CM_DMA_STATICDEP_L4CFG_STATDEP_SHIFT                                                                (12U)
#define CM_DMA_STATICDEP_L4CFG_STATDEP_MASK                                                                 (0x00001000U)
#define CM_DMA_STATICDEP_L4CFG_STATDEP_ENABLED                                                               (1U)
#define CM_DMA_STATICDEP_L4CFG_STATDEP_DISABLED                                                              (0U)

#define CM_DMA_STATICDEP_WKUPAON_STATDEP_SHIFT                                                              (15U)
#define CM_DMA_STATICDEP_WKUPAON_STATDEP_MASK                                                               (0x00008000U)
#define CM_DMA_STATICDEP_WKUPAON_STATDEP_ENABLED                                                             (1U)
#define CM_DMA_STATICDEP_WKUPAON_STATDEP_DISABLED                                                            (0U)

#define CM_DMA_STATICDEP_IPU1_STATDEP_SHIFT                                                                 (23U)
#define CM_DMA_STATICDEP_IPU1_STATDEP_MASK                                                                  (0x00800000U)
#define CM_DMA_STATICDEP_IPU1_STATDEP_ENABLED                                                                (1U)
#define CM_DMA_STATICDEP_IPU1_STATDEP_DISABLED                                                               (0U)

#define CM_DMA_STATICDEP_L4PER2_STATDEP_SHIFT                                                               (26U)
#define CM_DMA_STATICDEP_L4PER2_STATDEP_MASK                                                                (0x04000000U)
#define CM_DMA_STATICDEP_L4PER2_STATDEP_ENABLED                                                              (1U)
#define CM_DMA_STATICDEP_L4PER2_STATDEP_DISABLED                                                             (0U)

#define CM_DMA_STATICDEP_L4PER3_STATDEP_SHIFT                                                               (27U)
#define CM_DMA_STATICDEP_L4PER3_STATDEP_MASK                                                                (0x08000000U)
#define CM_DMA_STATICDEP_L4PER3_STATDEP_ENABLED                                                              (1U)
#define CM_DMA_STATICDEP_L4PER3_STATDEP_DISABLED                                                             (0U)

#define CM_DMA_STATICDEP_PCIE_STATDEP_SHIFT                                                                 (29U)
#define CM_DMA_STATICDEP_PCIE_STATDEP_MASK                                                                  (0x20000000U)
#define CM_DMA_STATICDEP_PCIE_STATDEP_ENABLED                                                                (1U)
#define CM_DMA_STATICDEP_PCIE_STATDEP_DISABLED                                                               (0U)

#define CM_DMA_STATICDEP_RESERVED_SHIFT                                                                     (1U)
#define CM_DMA_STATICDEP_RESERVED_MASK                                                                      (0x00000002U)

#define CM_DMA_STATICDEP_RESERVED1_SHIFT                                                                    (3U)
#define CM_DMA_STATICDEP_RESERVED1_MASK                                                                     (0x00000008U)

#define CM_DMA_STATICDEP_RESERVED2_SHIFT                                                                    (6U)
#define CM_DMA_STATICDEP_RESERVED2_MASK                                                                     (0x00000040U)

#define CM_DMA_STATICDEP_RESERVED3_SHIFT                                                                    (10U)
#define CM_DMA_STATICDEP_RESERVED3_MASK                                                                     (0x00000c00U)

#define CM_DMA_STATICDEP_RESERVED4_SHIFT                                                                    (16U)
#define CM_DMA_STATICDEP_RESERVED4_MASK                                                                     (0x007f0000U)

#define CM_DMA_STATICDEP_RESERVED5_SHIFT                                                                    (25U)
#define CM_DMA_STATICDEP_RESERVED5_MASK                                                                     (0x02000000U)

#define CM_DMA_STATICDEP_RESERVED6_SHIFT                                                                    (28U)
#define CM_DMA_STATICDEP_RESERVED6_MASK                                                                     (0x10000000U)

#define CM_DMA_STATICDEP_RESERVED7_SHIFT                                                                    (30U)
#define CM_DMA_STATICDEP_RESERVED7_MASK                                                                     (0xc0000000U)

#define CM_DMA_DYNAMICDEP_L3MAIN1_DYNDEP_SHIFT                                                              (5U)
#define CM_DMA_DYNAMICDEP_L3MAIN1_DYNDEP_MASK                                                               (0x00000020U)
#define CM_DMA_DYNAMICDEP_L3MAIN1_DYNDEP_DISABLED                                                            (0U)

#define CM_DMA_DYNAMICDEP_RESERVED_SHIFT                                                                    (0U)
#define CM_DMA_DYNAMICDEP_RESERVED_MASK                                                                     (0x0000001fU)

#define CM_DMA_DYNAMICDEP_RESERVED1_SHIFT                                                                   (6U)
#define CM_DMA_DYNAMICDEP_RESERVED1_MASK                                                                    (0xffffffc0U)

#define CM_DMA_DMA_SYSTEM_CLKCTRL_RESERVED_SHIFT                                                            (2U)
#define CM_DMA_DMA_SYSTEM_CLKCTRL_RESERVED_MASK                                                             (0x0000fffcU)

#define CM_DMA_DMA_SYSTEM_CLKCTRL_RESERVED1_SHIFT                                                           (19U)
#define CM_DMA_DMA_SYSTEM_CLKCTRL_RESERVED1_MASK                                                            (0xfff80000U)

#define CM_DMA_DMA_SYSTEM_CLKCTRL_MODULEMODE_SHIFT                                                          (0U)
#define CM_DMA_DMA_SYSTEM_CLKCTRL_MODULEMODE_MASK                                                           (0x00000003U)
#define CM_DMA_DMA_SYSTEM_CLKCTRL_MODULEMODE_AUTO                                                            (1U)

#define CM_DMA_DMA_SYSTEM_CLKCTRL_STBYST_SHIFT                                                              (18U)
#define CM_DMA_DMA_SYSTEM_CLKCTRL_STBYST_MASK                                                               (0x00040000U)
#define CM_DMA_DMA_SYSTEM_CLKCTRL_STBYST_FUNC                                                                (0U)
#define CM_DMA_DMA_SYSTEM_CLKCTRL_STBYST_STANDBY                                                             (1U)

#define CM_DMA_DMA_SYSTEM_CLKCTRL_IDLEST_SHIFT                                                              (16U)
#define CM_DMA_DMA_SYSTEM_CLKCTRL_IDLEST_MASK                                                               (0x00030000U)
#define CM_DMA_DMA_SYSTEM_CLKCTRL_IDLEST_DISABLE                                                             (3U)
#define CM_DMA_DMA_SYSTEM_CLKCTRL_IDLEST_IDLE                                                                (2U)
#define CM_DMA_DMA_SYSTEM_CLKCTRL_IDLEST_FUNC                                                                (0U)
#define CM_DMA_DMA_SYSTEM_CLKCTRL_IDLEST_TRANS                                                               (1U)

#define CM_EMIF_CLKSTCTRL_CLKTRCTRL_SHIFT                                                                   (0U)
#define CM_EMIF_CLKSTCTRL_CLKTRCTRL_MASK                                                                    (0x00000003U)
#define CM_EMIF_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                                                                 (0U)
#define CM_EMIF_CLKSTCTRL_CLKTRCTRL_RESERVED_1                                                               (1U)
#define CM_EMIF_CLKSTCTRL_CLKTRCTRL_HW_AUTO                                                                  (3U)
#define CM_EMIF_CLKSTCTRL_CLKTRCTRL_SW_WKUP                                                                  (2U)

#define CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_L3_GICLK_SHIFT                                                   (8U)
#define CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_L3_GICLK_MASK                                                    (0x00000100U)
#define CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_L3_GICLK_INACT                                                    (0U)
#define CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_L3_GICLK_ACT                                                      (1U)

#define CM_EMIF_CLKSTCTRL_RESERVED_SHIFT                                                                    (2U)
#define CM_EMIF_CLKSTCTRL_RESERVED_MASK                                                                     (0x000000fcU)

#define CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_DLL_GCLK_SHIFT                                                   (9U)
#define CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_DLL_GCLK_MASK                                                    (0x00000200U)
#define CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_DLL_GCLK_INACT                                                    (0U)
#define CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_DLL_GCLK_ACT                                                      (1U)

#define CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_PHY_GCLK_SHIFT                                                   (10U)
#define CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_PHY_GCLK_MASK                                                    (0x00000400U)
#define CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_PHY_GCLK_INACT                                                    (0U)
#define CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_PHY_GCLK_ACT                                                      (1U)

#define CM_EMIF_CLKSTCTRL_RESERVED1_SHIFT                                                                   (11U)
#define CM_EMIF_CLKSTCTRL_RESERVED1_MASK                                                                    (0xfffff800U)

#define CM_EMIF_DMM_CLKCTRL_RESERVED_SHIFT                                                                  (2U)
#define CM_EMIF_DMM_CLKCTRL_RESERVED_MASK                                                                   (0x0000fffcU)

#define CM_EMIF_DMM_CLKCTRL_RESERVED1_SHIFT                                                                 (18U)
#define CM_EMIF_DMM_CLKCTRL_RESERVED1_MASK                                                                  (0xfffc0000U)

#define CM_EMIF_DMM_CLKCTRL_MODULEMODE_SHIFT                                                                (0U)
#define CM_EMIF_DMM_CLKCTRL_MODULEMODE_MASK                                                                 (0x00000003U)
#define CM_EMIF_DMM_CLKCTRL_MODULEMODE_AUTO                                                                  (1U)

#define CM_EMIF_DMM_CLKCTRL_IDLEST_SHIFT                                                                    (16U)
#define CM_EMIF_DMM_CLKCTRL_IDLEST_MASK                                                                     (0x00030000U)
#define CM_EMIF_DMM_CLKCTRL_IDLEST_DISABLE                                                                   (3U)
#define CM_EMIF_DMM_CLKCTRL_IDLEST_IDLE                                                                      (2U)
#define CM_EMIF_DMM_CLKCTRL_IDLEST_FUNC                                                                      (0U)
#define CM_EMIF_DMM_CLKCTRL_IDLEST_TRANS                                                                     (1U)

#define CM_EMIF_EMIF_OCP_FW_CLKCTRL_RESERVED_SHIFT                                                          (2U)
#define CM_EMIF_EMIF_OCP_FW_CLKCTRL_RESERVED_MASK                                                           (0x0000fffcU)

#define CM_EMIF_EMIF_OCP_FW_CLKCTRL_RESERVED1_SHIFT                                                         (18U)
#define CM_EMIF_EMIF_OCP_FW_CLKCTRL_RESERVED1_MASK                                                          (0xfffc0000U)

#define CM_EMIF_EMIF_OCP_FW_CLKCTRL_MODULEMODE_SHIFT                                                        (0U)
#define CM_EMIF_EMIF_OCP_FW_CLKCTRL_MODULEMODE_MASK                                                         (0x00000003U)
#define CM_EMIF_EMIF_OCP_FW_CLKCTRL_MODULEMODE_AUTO                                                          (1U)

#define CM_EMIF_EMIF_OCP_FW_CLKCTRL_IDLEST_SHIFT                                                            (16U)
#define CM_EMIF_EMIF_OCP_FW_CLKCTRL_IDLEST_MASK                                                             (0x00030000U)
#define CM_EMIF_EMIF_OCP_FW_CLKCTRL_IDLEST_DISABLE                                                           (3U)
#define CM_EMIF_EMIF_OCP_FW_CLKCTRL_IDLEST_IDLE                                                              (2U)
#define CM_EMIF_EMIF_OCP_FW_CLKCTRL_IDLEST_FUNC                                                              (0U)
#define CM_EMIF_EMIF_OCP_FW_CLKCTRL_IDLEST_TRANS                                                             (1U)

#define CM_EMIF_EMIF1_CLKCTRL_RESERVED_SHIFT                                                                (2U)
#define CM_EMIF_EMIF1_CLKCTRL_RESERVED_MASK                                                                 (0x0000fffcU)

#define CM_EMIF_EMIF1_CLKCTRL_RESERVED1_SHIFT                                                               (18U)
#define CM_EMIF_EMIF1_CLKCTRL_RESERVED1_MASK                                                                (0x00fc0000U)

#define CM_EMIF_EMIF1_CLKCTRL_IDLEST_SHIFT                                                                  (16U)
#define CM_EMIF_EMIF1_CLKCTRL_IDLEST_MASK                                                                   (0x00030000U)
#define CM_EMIF_EMIF1_CLKCTRL_IDLEST_DISABLE                                                                 (3U)
#define CM_EMIF_EMIF1_CLKCTRL_IDLEST_IDLE                                                                    (2U)
#define CM_EMIF_EMIF1_CLKCTRL_IDLEST_FUNC                                                                    (0U)
#define CM_EMIF_EMIF1_CLKCTRL_IDLEST_TRANS                                                                   (1U)

#define CM_EMIF_EMIF1_CLKCTRL_MODULEMODE_SHIFT                                                              (0U)
#define CM_EMIF_EMIF1_CLKCTRL_MODULEMODE_MASK                                                               (0x00000003U)
#define CM_EMIF_EMIF1_CLKCTRL_MODULEMODE_DISABLED                                                            (0U)
#define CM_EMIF_EMIF1_CLKCTRL_MODULEMODE_AUTO                                                                (1U)
#define CM_EMIF_EMIF1_CLKCTRL_MODULEMODE_RESERVED_2                                                          (2U)
#define CM_EMIF_EMIF1_CLKCTRL_MODULEMODE_RESERVED                                                            (3U)

#define CM_EMIF_EMIF1_CLKCTRL_CLKSEL_LL_SHIFT                                                               (24U)
#define CM_EMIF_EMIF1_CLKCTRL_CLKSEL_LL_MASK                                                                (0x01000000U)
#define CM_EMIF_EMIF1_CLKCTRL_CLKSEL_LL_SEL_C2C                                                              (0U)
#define CM_EMIF_EMIF1_CLKCTRL_CLKSEL_LL_SEL_LLI                                                              (1U)

#define CM_EMIF_EMIF1_CLKCTRL_RESERVED2_SHIFT                                                               (25U)
#define CM_EMIF_EMIF1_CLKCTRL_RESERVED2_MASK                                                                (0xfe000000U)

#define CM_EMIF_EMIF2_CLKCTRL_RESERVED_SHIFT                                                                (2U)
#define CM_EMIF_EMIF2_CLKCTRL_RESERVED_MASK                                                                 (0x0000fffcU)

#define CM_EMIF_EMIF2_CLKCTRL_RESERVED1_SHIFT                                                               (18U)
#define CM_EMIF_EMIF2_CLKCTRL_RESERVED1_MASK                                                                (0xfffc0000U)

#define CM_EMIF_EMIF2_CLKCTRL_IDLEST_SHIFT                                                                  (16U)
#define CM_EMIF_EMIF2_CLKCTRL_IDLEST_MASK                                                                   (0x00030000U)
#define CM_EMIF_EMIF2_CLKCTRL_IDLEST_DISABLE                                                                 (3U)
#define CM_EMIF_EMIF2_CLKCTRL_IDLEST_IDLE                                                                    (2U)
#define CM_EMIF_EMIF2_CLKCTRL_IDLEST_FUNC                                                                    (0U)
#define CM_EMIF_EMIF2_CLKCTRL_IDLEST_TRANS                                                                   (1U)

#define CM_EMIF_EMIF2_CLKCTRL_MODULEMODE_SHIFT                                                              (0U)
#define CM_EMIF_EMIF2_CLKCTRL_MODULEMODE_MASK                                                               (0x00000003U)
#define CM_EMIF_EMIF2_CLKCTRL_MODULEMODE_DISABLED                                                            (0U)
#define CM_EMIF_EMIF2_CLKCTRL_MODULEMODE_AUTO                                                                (1U)
#define CM_EMIF_EMIF2_CLKCTRL_MODULEMODE_RESERVED_2                                                          (2U)
#define CM_EMIF_EMIF2_CLKCTRL_MODULEMODE_RESERVED                                                            (3U)

#define CM_EMIF_EMIF_DLL_CLKCTRL_OPTFCLKEN_DLL_CLK_SHIFT                                                    (8U)
#define CM_EMIF_EMIF_DLL_CLKCTRL_OPTFCLKEN_DLL_CLK_MASK                                                     (0x00000100U)
#define CM_EMIF_EMIF_DLL_CLKCTRL_OPTFCLKEN_DLL_CLK_FCLK_EN                                                   (1U)
#define CM_EMIF_EMIF_DLL_CLKCTRL_OPTFCLKEN_DLL_CLK_FCLK_DIS                                                  (0U)

#define CM_EMIF_EMIF_DLL_CLKCTRL_RESERVED_SHIFT                                                             (0U)
#define CM_EMIF_EMIF_DLL_CLKCTRL_RESERVED_MASK                                                              (0x000000ffU)

#define CM_EMIF_EMIF_DLL_CLKCTRL_RESERVED1_SHIFT                                                            (9U)
#define CM_EMIF_EMIF_DLL_CLKCTRL_RESERVED1_MASK                                                             (0xfffffe00U)

#define CM_ATL_ATL_CLKCTRL_RESERVED_SHIFT                                                                   (2U)
#define CM_ATL_ATL_CLKCTRL_RESERVED_MASK                                                                    (0x0000fffcU)

#define CM_ATL_ATL_CLKCTRL_IDLEST_SHIFT                                                                     (16U)
#define CM_ATL_ATL_CLKCTRL_IDLEST_MASK                                                                      (0x00030000U)
#define CM_ATL_ATL_CLKCTRL_IDLEST_DISABLE                                                                    (3U)
#define CM_ATL_ATL_CLKCTRL_IDLEST_IDLE                                                                       (2U)
#define CM_ATL_ATL_CLKCTRL_IDLEST_FUNC                                                                       (0U)
#define CM_ATL_ATL_CLKCTRL_IDLEST_TRANS                                                                      (1U)

#define CM_ATL_ATL_CLKCTRL_RESERVED1_SHIFT                                                                  (18U)
#define CM_ATL_ATL_CLKCTRL_RESERVED1_MASK                                                                   (0x00fc0000U)

#define CM_ATL_ATL_CLKCTRL_CLKSEL_SOURCE1_SHIFT                                                             (24U)
#define CM_ATL_ATL_CLKCTRL_CLKSEL_SOURCE1_MASK                                                              (0x03000000U)
#define CM_ATL_ATL_CLKCTRL_CLKSEL_SOURCE1_SEL_VIDEO1_CLK                                                     (1U)
#define CM_ATL_ATL_CLKCTRL_CLKSEL_SOURCE1_SEL_VIDEO2_CLK                                                     (2U)
#define CM_ATL_ATL_CLKCTRL_CLKSEL_SOURCE1_SEL_HDMI_CLK                                                       (3U)
#define CM_ATL_ATL_CLKCTRL_CLKSEL_SOURCE1_SEL_FUNC_32K_CLK                                                   (0U)

#define CM_ATL_ATL_CLKCTRL_CLKSEL_SOURCE2_SHIFT                                                             (26U)
#define CM_ATL_ATL_CLKCTRL_CLKSEL_SOURCE2_MASK                                                              (0x0c000000U)
#define CM_ATL_ATL_CLKCTRL_CLKSEL_SOURCE2_SEL_L3_ICLK                                                        (0U)
#define CM_ATL_ATL_CLKCTRL_CLKSEL_SOURCE2_SEL_PER_ABE_X1_CLK                                                 (1U)
#define CM_ATL_ATL_CLKCTRL_CLKSEL_SOURCE2_SEL_DPLL_CLK                                                       (2U)
#define CM_ATL_ATL_CLKCTRL_CLKSEL_SOURCE2_RESERVED                                                           (3U)

#define CM_ATL_ATL_CLKCTRL_RESERVED2_SHIFT                                                                  (28U)
#define CM_ATL_ATL_CLKCTRL_RESERVED2_MASK                                                                   (0xf0000000U)

#define CM_ATL_ATL_CLKCTRL_MODULEMODE_SHIFT                                                                 (0U)
#define CM_ATL_ATL_CLKCTRL_MODULEMODE_MASK                                                                  (0x00000003U)
#define CM_ATL_ATL_CLKCTRL_MODULEMODE_DISABLED                                                               (0U)
#define CM_ATL_ATL_CLKCTRL_MODULEMODE_RESERVED_1                                                             (1U)
#define CM_ATL_ATL_CLKCTRL_MODULEMODE_ENABLE                                                                 (2U)
#define CM_ATL_ATL_CLKCTRL_MODULEMODE_RESERVED                                                               (3U)

#define CM_ATL_CLKSTCTRL_CLKTRCTRL_SHIFT                                                                    (0U)
#define CM_ATL_CLKSTCTRL_CLKTRCTRL_MASK                                                                     (0x00000003U)
#define CM_ATL_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                                                                  (0U)
#define CM_ATL_CLKSTCTRL_CLKTRCTRL_RESERVED_1                                                                (1U)
#define CM_ATL_CLKSTCTRL_CLKTRCTRL_SW_WKUP                                                                   (2U)
#define CM_ATL_CLKSTCTRL_CLKTRCTRL_HW_AUTO                                                                   (3U)

#define CM_ATL_CLKSTCTRL_CLKACTIVITY_ATL_L3_GICLK_SHIFT                                                     (8U)
#define CM_ATL_CLKSTCTRL_CLKACTIVITY_ATL_L3_GICLK_MASK                                                      (0x00000100U)
#define CM_ATL_CLKSTCTRL_CLKACTIVITY_ATL_L3_GICLK_INACT                                                      (0U)
#define CM_ATL_CLKSTCTRL_CLKACTIVITY_ATL_L3_GICLK_ACT                                                        (1U)

#define CM_ATL_CLKSTCTRL_CLKACTIVITY_ATL_GFCLK_SHIFT                                                        (9U)
#define CM_ATL_CLKSTCTRL_CLKACTIVITY_ATL_GFCLK_MASK                                                         (0x00000200U)
#define CM_ATL_CLKSTCTRL_CLKACTIVITY_ATL_GFCLK_INACT                                                         (0U)
#define CM_ATL_CLKSTCTRL_CLKACTIVITY_ATL_GFCLK_ACT                                                           (1U)

#define CM_ATL_CLKSTCTRL_RESERVED_SHIFT                                                                     (2U)
#define CM_ATL_CLKSTCTRL_RESERVED_MASK                                                                      (0x000000fcU)

#define CM_ATL_CLKSTCTRL_RESERVED1_SHIFT                                                                    (10U)
#define CM_ATL_CLKSTCTRL_RESERVED1_MASK                                                                     (0xfffffc00U)

#define CM_L4CFG_CLKSTCTRL_CLKTRCTRL_SHIFT                                                                  (0U)
#define CM_L4CFG_CLKSTCTRL_CLKTRCTRL_MASK                                                                   (0x00000003U)
#define CM_L4CFG_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                                                                (0U)
#define CM_L4CFG_CLKSTCTRL_CLKTRCTRL_RESERVED_1                                                              (1U)
#define CM_L4CFG_CLKSTCTRL_CLKTRCTRL_RESERVED_2                                                              (2U)
#define CM_L4CFG_CLKSTCTRL_CLKTRCTRL_HW_AUTO                                                                 (3U)

#define CM_L4CFG_CLKSTCTRL_CLKACTIVITY_L4CFG_L4_GICLK_SHIFT                                                 (8U)
#define CM_L4CFG_CLKSTCTRL_CLKACTIVITY_L4CFG_L4_GICLK_MASK                                                  (0x00000100U)
#define CM_L4CFG_CLKSTCTRL_CLKACTIVITY_L4CFG_L4_GICLK_INACT                                                  (0U)
#define CM_L4CFG_CLKSTCTRL_CLKACTIVITY_L4CFG_L4_GICLK_ACT                                                    (1U)

#define CM_L4CFG_CLKSTCTRL_RESERVED_SHIFT                                                                   (2U)
#define CM_L4CFG_CLKSTCTRL_RESERVED_MASK                                                                    (0x000000fcU)

#define CM_L4CFG_CLKSTCTRL_CLKACTIVITY_L4CFG_L3_GICLK_SHIFT                                                 (9U)
#define CM_L4CFG_CLKSTCTRL_CLKACTIVITY_L4CFG_L3_GICLK_MASK                                                  (0x00000200U)
#define CM_L4CFG_CLKSTCTRL_CLKACTIVITY_L4CFG_L3_GICLK_INACT                                                  (0U)
#define CM_L4CFG_CLKSTCTRL_CLKACTIVITY_L4CFG_L3_GICLK_ACT                                                    (1U)

#define CM_L4CFG_CLKSTCTRL_RESERVED1_SHIFT                                                                  (10U)
#define CM_L4CFG_CLKSTCTRL_RESERVED1_MASK                                                                   (0xfffffc00U)

#define CM_L4CFG_DYNAMICDEP_EMIF_DYNDEP_SHIFT                                                               (4U)
#define CM_L4CFG_DYNAMICDEP_EMIF_DYNDEP_MASK                                                                (0x00000010U)
#define CM_L4CFG_DYNAMICDEP_EMIF_DYNDEP_ENABLED                                                              (1U)

#define CM_L4CFG_DYNAMICDEP_L3INIT_DYNDEP_SHIFT                                                             (7U)
#define CM_L4CFG_DYNAMICDEP_L3INIT_DYNDEP_MASK                                                              (0x00000080U)
#define CM_L4CFG_DYNAMICDEP_L3INIT_DYNDEP_ENABLED                                                            (1U)

#define CM_L4CFG_DYNAMICDEP_COREAON_DYNDEP_SHIFT                                                            (16U)
#define CM_L4CFG_DYNAMICDEP_COREAON_DYNDEP_MASK                                                             (0x00010000U)
#define CM_L4CFG_DYNAMICDEP_COREAON_DYNDEP_ENABLED                                                           (1U)

#define CM_L4CFG_DYNAMICDEP_CUSTEFUSE_DYNDEP_SHIFT                                                          (17U)
#define CM_L4CFG_DYNAMICDEP_CUSTEFUSE_DYNDEP_MASK                                                           (0x00020000U)
#define CM_L4CFG_DYNAMICDEP_CUSTEFUSE_DYNDEP_ENABLED                                                         (1U)

#define CM_L4CFG_DYNAMICDEP_SDMA_DYNDEP_SHIFT                                                               (11U)
#define CM_L4CFG_DYNAMICDEP_SDMA_DYNDEP_MASK                                                                (0x00000800U)
#define CM_L4CFG_DYNAMICDEP_SDMA_DYNDEP_ENABLED                                                              (1U)

#define CM_L4CFG_DYNAMICDEP_L3MAIN1_DYNDEP_SHIFT                                                            (5U)
#define CM_L4CFG_DYNAMICDEP_L3MAIN1_DYNDEP_MASK                                                             (0x00000020U)
#define CM_L4CFG_DYNAMICDEP_L3MAIN1_DYNDEP_ENABLED                                                           (1U)

#define CM_L4CFG_DYNAMICDEP_WINDOWSIZE_SHIFT                                                                (24U)
#define CM_L4CFG_DYNAMICDEP_WINDOWSIZE_MASK                                                                 (0x0f000000U)

#define CM_L4CFG_DYNAMICDEP_MPU_DYNDEP_SHIFT                                                                (19U)
#define CM_L4CFG_DYNAMICDEP_MPU_DYNDEP_MASK                                                                 (0x00080000U)
#define CM_L4CFG_DYNAMICDEP_MPU_DYNDEP_ENABLED                                                               (1U)

#define CM_L4CFG_DYNAMICDEP_RESERVED_SHIFT                                                                  (0U)
#define CM_L4CFG_DYNAMICDEP_RESERVED_MASK                                                                   (0x0000000fU)

#define CM_L4CFG_DYNAMICDEP_RESERVED1_SHIFT                                                                 (6U)
#define CM_L4CFG_DYNAMICDEP_RESERVED1_MASK                                                                  (0x00000040U)

#define CM_L4CFG_DYNAMICDEP_RESERVED2_SHIFT                                                                 (8U)
#define CM_L4CFG_DYNAMICDEP_RESERVED2_MASK                                                                  (0x00000700U)

#define CM_L4CFG_DYNAMICDEP_RESERVED3_SHIFT                                                                 (12U)
#define CM_L4CFG_DYNAMICDEP_RESERVED3_MASK                                                                  (0x0000f000U)

#define CM_L4CFG_DYNAMICDEP_RESERVED4_SHIFT                                                                 (18U)
#define CM_L4CFG_DYNAMICDEP_RESERVED4_MASK                                                                  (0x00040000U)

#define CM_L4CFG_DYNAMICDEP_RESERVED5_SHIFT                                                                 (20U)
#define CM_L4CFG_DYNAMICDEP_RESERVED5_MASK                                                                  (0x00f00000U)

#define CM_L4CFG_DYNAMICDEP_RESERVED6_SHIFT                                                                 (28U)
#define CM_L4CFG_DYNAMICDEP_RESERVED6_MASK                                                                  (0xf0000000U)

#define CM_L4CFG_L4_CFG_CLKCTRL_MODULEMODE_SHIFT                                                            (0U)
#define CM_L4CFG_L4_CFG_CLKCTRL_MODULEMODE_MASK                                                             (0x00000003U)
#define CM_L4CFG_L4_CFG_CLKCTRL_MODULEMODE_AUTO                                                              (1U)

#define CM_L4CFG_L4_CFG_CLKCTRL_RESERVED_SHIFT                                                              (2U)
#define CM_L4CFG_L4_CFG_CLKCTRL_RESERVED_MASK                                                               (0x0000fffcU)

#define CM_L4CFG_L4_CFG_CLKCTRL_RESERVED1_SHIFT                                                             (18U)
#define CM_L4CFG_L4_CFG_CLKCTRL_RESERVED1_MASK                                                              (0xfffc0000U)

#define CM_L4CFG_L4_CFG_CLKCTRL_IDLEST_SHIFT                                                                (16U)
#define CM_L4CFG_L4_CFG_CLKCTRL_IDLEST_MASK                                                                 (0x00030000U)
#define CM_L4CFG_L4_CFG_CLKCTRL_IDLEST_DISABLE                                                               (3U)
#define CM_L4CFG_L4_CFG_CLKCTRL_IDLEST_IDLE                                                                  (2U)
#define CM_L4CFG_L4_CFG_CLKCTRL_IDLEST_FUNC                                                                  (0U)
#define CM_L4CFG_L4_CFG_CLKCTRL_IDLEST_TRANS                                                                 (1U)

#define CM_L4CFG_SPINLOCK_CLKCTRL_RESERVED_SHIFT                                                            (2U)
#define CM_L4CFG_SPINLOCK_CLKCTRL_RESERVED_MASK                                                             (0x0000fffcU)

#define CM_L4CFG_SPINLOCK_CLKCTRL_RESERVED1_SHIFT                                                           (18U)
#define CM_L4CFG_SPINLOCK_CLKCTRL_RESERVED1_MASK                                                            (0xfffc0000U)

#define CM_L4CFG_SPINLOCK_CLKCTRL_MODULEMODE_SHIFT                                                          (0U)
#define CM_L4CFG_SPINLOCK_CLKCTRL_MODULEMODE_MASK                                                           (0x00000003U)
#define CM_L4CFG_SPINLOCK_CLKCTRL_MODULEMODE_AUTO                                                            (1U)

#define CM_L4CFG_SPINLOCK_CLKCTRL_IDLEST_SHIFT                                                              (16U)
#define CM_L4CFG_SPINLOCK_CLKCTRL_IDLEST_MASK                                                               (0x00030000U)
#define CM_L4CFG_SPINLOCK_CLKCTRL_IDLEST_DISABLE                                                             (3U)
#define CM_L4CFG_SPINLOCK_CLKCTRL_IDLEST_IDLE                                                                (2U)
#define CM_L4CFG_SPINLOCK_CLKCTRL_IDLEST_FUNC                                                                (0U)
#define CM_L4CFG_SPINLOCK_CLKCTRL_IDLEST_TRANS                                                               (1U)

#define CM_L4CFG_MAILBOX1_CLKCTRL_RESERVED_SHIFT                                                            (2U)
#define CM_L4CFG_MAILBOX1_CLKCTRL_RESERVED_MASK                                                             (0x0000fffcU)

#define CM_L4CFG_MAILBOX1_CLKCTRL_RESERVED1_SHIFT                                                           (18U)
#define CM_L4CFG_MAILBOX1_CLKCTRL_RESERVED1_MASK                                                            (0xfffc0000U)

#define CM_L4CFG_MAILBOX1_CLKCTRL_MODULEMODE_SHIFT                                                          (0U)
#define CM_L4CFG_MAILBOX1_CLKCTRL_MODULEMODE_MASK                                                           (0x00000003U)
#define CM_L4CFG_MAILBOX1_CLKCTRL_MODULEMODE_AUTO                                                            (1U)

#define CM_L4CFG_MAILBOX1_CLKCTRL_IDLEST_SHIFT                                                              (16U)
#define CM_L4CFG_MAILBOX1_CLKCTRL_IDLEST_MASK                                                               (0x00030000U)
#define CM_L4CFG_MAILBOX1_CLKCTRL_IDLEST_DISABLE                                                             (3U)
#define CM_L4CFG_MAILBOX1_CLKCTRL_IDLEST_IDLE                                                                (2U)
#define CM_L4CFG_MAILBOX1_CLKCTRL_IDLEST_FUNC                                                                (0U)
#define CM_L4CFG_MAILBOX1_CLKCTRL_IDLEST_TRANS                                                               (1U)

#define CM_L4CFG_SAR_ROM_CLKCTRL_RESERVED_SHIFT                                                             (2U)
#define CM_L4CFG_SAR_ROM_CLKCTRL_RESERVED_MASK                                                              (0x0000fffcU)

#define CM_L4CFG_SAR_ROM_CLKCTRL_RESERVED1_SHIFT                                                            (18U)
#define CM_L4CFG_SAR_ROM_CLKCTRL_RESERVED1_MASK                                                             (0xfffc0000U)

#define CM_L4CFG_SAR_ROM_CLKCTRL_MODULEMODE_SHIFT                                                           (0U)
#define CM_L4CFG_SAR_ROM_CLKCTRL_MODULEMODE_MASK                                                            (0x00000003U)
#define CM_L4CFG_SAR_ROM_CLKCTRL_MODULEMODE_AUTO                                                             (1U)

#define CM_L4CFG_SAR_ROM_CLKCTRL_IDLEST_SHIFT                                                               (16U)
#define CM_L4CFG_SAR_ROM_CLKCTRL_IDLEST_MASK                                                                (0x00030000U)
#define CM_L4CFG_SAR_ROM_CLKCTRL_IDLEST_DISABLE                                                              (3U)
#define CM_L4CFG_SAR_ROM_CLKCTRL_IDLEST_IDLE                                                                 (2U)
#define CM_L4CFG_SAR_ROM_CLKCTRL_IDLEST_FUNC                                                                 (0U)
#define CM_L4CFG_SAR_ROM_CLKCTRL_IDLEST_TRANS                                                                (1U)

#define CM_L4CFG_OCP2SCP2_CLKCTRL_IDLEST_SHIFT                                                              (16U)
#define CM_L4CFG_OCP2SCP2_CLKCTRL_IDLEST_MASK                                                               (0x00030000U)
#define CM_L4CFG_OCP2SCP2_CLKCTRL_IDLEST_DISABLE                                                             (3U)
#define CM_L4CFG_OCP2SCP2_CLKCTRL_IDLEST_IDLE                                                                (2U)
#define CM_L4CFG_OCP2SCP2_CLKCTRL_IDLEST_FUNC                                                                (0U)
#define CM_L4CFG_OCP2SCP2_CLKCTRL_IDLEST_TRANS                                                               (1U)

#define CM_L4CFG_OCP2SCP2_CLKCTRL_MODULEMODE_SHIFT                                                          (0U)
#define CM_L4CFG_OCP2SCP2_CLKCTRL_MODULEMODE_MASK                                                           (0x00000003U)
#define CM_L4CFG_OCP2SCP2_CLKCTRL_MODULEMODE_AUTO                                                            (1U)

#define CM_L4CFG_OCP2SCP2_CLKCTRL_RESERVED_SHIFT                                                            (2U)
#define CM_L4CFG_OCP2SCP2_CLKCTRL_RESERVED_MASK                                                             (0x0000fffcU)

#define CM_L4CFG_OCP2SCP2_CLKCTRL_RESERVED2_SHIFT                                                           (18U)
#define CM_L4CFG_OCP2SCP2_CLKCTRL_RESERVED2_MASK                                                            (0xfffc0000U)

#define CM_L4CFG_MAILBOX2_CLKCTRL_RESERVED_SHIFT                                                            (2U)
#define CM_L4CFG_MAILBOX2_CLKCTRL_RESERVED_MASK                                                             (0x0000fffcU)

#define CM_L4CFG_MAILBOX2_CLKCTRL_RESERVED1_SHIFT                                                           (18U)
#define CM_L4CFG_MAILBOX2_CLKCTRL_RESERVED1_MASK                                                            (0xfffc0000U)

#define CM_L4CFG_MAILBOX2_CLKCTRL_MODULEMODE_SHIFT                                                          (0U)
#define CM_L4CFG_MAILBOX2_CLKCTRL_MODULEMODE_MASK                                                           (0x00000003U)
#define CM_L4CFG_MAILBOX2_CLKCTRL_MODULEMODE_AUTO                                                            (1U)

#define CM_L4CFG_MAILBOX2_CLKCTRL_IDLEST_SHIFT                                                              (16U)
#define CM_L4CFG_MAILBOX2_CLKCTRL_IDLEST_MASK                                                               (0x00030000U)
#define CM_L4CFG_MAILBOX2_CLKCTRL_IDLEST_DISABLE                                                             (3U)
#define CM_L4CFG_MAILBOX2_CLKCTRL_IDLEST_IDLE                                                                (2U)
#define CM_L4CFG_MAILBOX2_CLKCTRL_IDLEST_FUNC                                                                (0U)
#define CM_L4CFG_MAILBOX2_CLKCTRL_IDLEST_TRANS                                                               (1U)

#define CM_L4CFG_MAILBOX3_CLKCTRL_RESERVED_SHIFT                                                            (2U)
#define CM_L4CFG_MAILBOX3_CLKCTRL_RESERVED_MASK                                                             (0x0000fffcU)

#define CM_L4CFG_MAILBOX3_CLKCTRL_RESERVED1_SHIFT                                                           (18U)
#define CM_L4CFG_MAILBOX3_CLKCTRL_RESERVED1_MASK                                                            (0xfffc0000U)

#define CM_L4CFG_MAILBOX3_CLKCTRL_MODULEMODE_SHIFT                                                          (0U)
#define CM_L4CFG_MAILBOX3_CLKCTRL_MODULEMODE_MASK                                                           (0x00000003U)
#define CM_L4CFG_MAILBOX3_CLKCTRL_MODULEMODE_AUTO                                                            (1U)

#define CM_L4CFG_MAILBOX3_CLKCTRL_IDLEST_SHIFT                                                              (16U)
#define CM_L4CFG_MAILBOX3_CLKCTRL_IDLEST_MASK                                                               (0x00030000U)
#define CM_L4CFG_MAILBOX3_CLKCTRL_IDLEST_DISABLE                                                             (3U)
#define CM_L4CFG_MAILBOX3_CLKCTRL_IDLEST_IDLE                                                                (2U)
#define CM_L4CFG_MAILBOX3_CLKCTRL_IDLEST_FUNC                                                                (0U)
#define CM_L4CFG_MAILBOX3_CLKCTRL_IDLEST_TRANS                                                               (1U)

#define CM_L4CFG_MAILBOX4_CLKCTRL_RESERVED_SHIFT                                                            (2U)
#define CM_L4CFG_MAILBOX4_CLKCTRL_RESERVED_MASK                                                             (0x0000fffcU)

#define CM_L4CFG_MAILBOX4_CLKCTRL_RESERVED1_SHIFT                                                           (18U)
#define CM_L4CFG_MAILBOX4_CLKCTRL_RESERVED1_MASK                                                            (0xfffc0000U)

#define CM_L4CFG_MAILBOX4_CLKCTRL_MODULEMODE_SHIFT                                                          (0U)
#define CM_L4CFG_MAILBOX4_CLKCTRL_MODULEMODE_MASK                                                           (0x00000003U)
#define CM_L4CFG_MAILBOX4_CLKCTRL_MODULEMODE_AUTO                                                            (1U)

#define CM_L4CFG_MAILBOX4_CLKCTRL_IDLEST_SHIFT                                                              (16U)
#define CM_L4CFG_MAILBOX4_CLKCTRL_IDLEST_MASK                                                               (0x00030000U)
#define CM_L4CFG_MAILBOX4_CLKCTRL_IDLEST_DISABLE                                                             (3U)
#define CM_L4CFG_MAILBOX4_CLKCTRL_IDLEST_IDLE                                                                (2U)
#define CM_L4CFG_MAILBOX4_CLKCTRL_IDLEST_FUNC                                                                (0U)
#define CM_L4CFG_MAILBOX4_CLKCTRL_IDLEST_TRANS                                                               (1U)

#define CM_L4CFG_MAILBOX5_CLKCTRL_RESERVED_SHIFT                                                            (2U)
#define CM_L4CFG_MAILBOX5_CLKCTRL_RESERVED_MASK                                                             (0x0000fffcU)

#define CM_L4CFG_MAILBOX5_CLKCTRL_RESERVED1_SHIFT                                                           (18U)
#define CM_L4CFG_MAILBOX5_CLKCTRL_RESERVED1_MASK                                                            (0xfffc0000U)

#define CM_L4CFG_MAILBOX5_CLKCTRL_MODULEMODE_SHIFT                                                          (0U)
#define CM_L4CFG_MAILBOX5_CLKCTRL_MODULEMODE_MASK                                                           (0x00000003U)
#define CM_L4CFG_MAILBOX5_CLKCTRL_MODULEMODE_AUTO                                                            (1U)

#define CM_L4CFG_MAILBOX5_CLKCTRL_IDLEST_SHIFT                                                              (16U)
#define CM_L4CFG_MAILBOX5_CLKCTRL_IDLEST_MASK                                                               (0x00030000U)
#define CM_L4CFG_MAILBOX5_CLKCTRL_IDLEST_DISABLE                                                             (3U)
#define CM_L4CFG_MAILBOX5_CLKCTRL_IDLEST_IDLE                                                                (2U)
#define CM_L4CFG_MAILBOX5_CLKCTRL_IDLEST_FUNC                                                                (0U)
#define CM_L4CFG_MAILBOX5_CLKCTRL_IDLEST_TRANS                                                               (1U)

#define CM_L4CFG_MAILBOX6_CLKCTRL_RESERVED_SHIFT                                                            (2U)
#define CM_L4CFG_MAILBOX6_CLKCTRL_RESERVED_MASK                                                             (0x0000fffcU)

#define CM_L4CFG_MAILBOX6_CLKCTRL_RESERVED1_SHIFT                                                           (18U)
#define CM_L4CFG_MAILBOX6_CLKCTRL_RESERVED1_MASK                                                            (0xfffc0000U)

#define CM_L4CFG_MAILBOX6_CLKCTRL_MODULEMODE_SHIFT                                                          (0U)
#define CM_L4CFG_MAILBOX6_CLKCTRL_MODULEMODE_MASK                                                           (0x00000003U)
#define CM_L4CFG_MAILBOX6_CLKCTRL_MODULEMODE_AUTO                                                            (1U)

#define CM_L4CFG_MAILBOX6_CLKCTRL_IDLEST_SHIFT                                                              (16U)
#define CM_L4CFG_MAILBOX6_CLKCTRL_IDLEST_MASK                                                               (0x00030000U)
#define CM_L4CFG_MAILBOX6_CLKCTRL_IDLEST_DISABLE                                                             (3U)
#define CM_L4CFG_MAILBOX6_CLKCTRL_IDLEST_IDLE                                                                (2U)
#define CM_L4CFG_MAILBOX6_CLKCTRL_IDLEST_FUNC                                                                (0U)
#define CM_L4CFG_MAILBOX6_CLKCTRL_IDLEST_TRANS                                                               (1U)

#define CM_L4CFG_MAILBOX7_CLKCTRL_RESERVED_SHIFT                                                            (2U)
#define CM_L4CFG_MAILBOX7_CLKCTRL_RESERVED_MASK                                                             (0x0000fffcU)

#define CM_L4CFG_MAILBOX7_CLKCTRL_RESERVED1_SHIFT                                                           (18U)
#define CM_L4CFG_MAILBOX7_CLKCTRL_RESERVED1_MASK                                                            (0xfffc0000U)

#define CM_L4CFG_MAILBOX7_CLKCTRL_MODULEMODE_SHIFT                                                          (0U)
#define CM_L4CFG_MAILBOX7_CLKCTRL_MODULEMODE_MASK                                                           (0x00000003U)
#define CM_L4CFG_MAILBOX7_CLKCTRL_MODULEMODE_AUTO                                                            (1U)

#define CM_L4CFG_MAILBOX7_CLKCTRL_IDLEST_SHIFT                                                              (16U)
#define CM_L4CFG_MAILBOX7_CLKCTRL_IDLEST_MASK                                                               (0x00030000U)
#define CM_L4CFG_MAILBOX7_CLKCTRL_IDLEST_DISABLE                                                             (3U)
#define CM_L4CFG_MAILBOX7_CLKCTRL_IDLEST_IDLE                                                                (2U)
#define CM_L4CFG_MAILBOX7_CLKCTRL_IDLEST_FUNC                                                                (0U)
#define CM_L4CFG_MAILBOX7_CLKCTRL_IDLEST_TRANS                                                               (1U)

#define CM_L4CFG_MAILBOX8_CLKCTRL_RESERVED_SHIFT                                                            (2U)
#define CM_L4CFG_MAILBOX8_CLKCTRL_RESERVED_MASK                                                             (0x0000fffcU)

#define CM_L4CFG_MAILBOX8_CLKCTRL_RESERVED1_SHIFT                                                           (18U)
#define CM_L4CFG_MAILBOX8_CLKCTRL_RESERVED1_MASK                                                            (0xfffc0000U)

#define CM_L4CFG_MAILBOX8_CLKCTRL_MODULEMODE_SHIFT                                                          (0U)
#define CM_L4CFG_MAILBOX8_CLKCTRL_MODULEMODE_MASK                                                           (0x00000003U)
#define CM_L4CFG_MAILBOX8_CLKCTRL_MODULEMODE_AUTO                                                            (1U)

#define CM_L4CFG_MAILBOX8_CLKCTRL_IDLEST_SHIFT                                                              (16U)
#define CM_L4CFG_MAILBOX8_CLKCTRL_IDLEST_MASK                                                               (0x00030000U)
#define CM_L4CFG_MAILBOX8_CLKCTRL_IDLEST_DISABLE                                                             (3U)
#define CM_L4CFG_MAILBOX8_CLKCTRL_IDLEST_IDLE                                                                (2U)
#define CM_L4CFG_MAILBOX8_CLKCTRL_IDLEST_FUNC                                                                (0U)
#define CM_L4CFG_MAILBOX8_CLKCTRL_IDLEST_TRANS                                                               (1U)

#define CM_L4CFG_MAILBOX9_CLKCTRL_RESERVED_SHIFT                                                            (2U)
#define CM_L4CFG_MAILBOX9_CLKCTRL_RESERVED_MASK                                                             (0x0000fffcU)

#define CM_L4CFG_MAILBOX9_CLKCTRL_RESERVED1_SHIFT                                                           (18U)
#define CM_L4CFG_MAILBOX9_CLKCTRL_RESERVED1_MASK                                                            (0xfffc0000U)

#define CM_L4CFG_MAILBOX9_CLKCTRL_MODULEMODE_SHIFT                                                          (0U)
#define CM_L4CFG_MAILBOX9_CLKCTRL_MODULEMODE_MASK                                                           (0x00000003U)
#define CM_L4CFG_MAILBOX9_CLKCTRL_MODULEMODE_AUTO                                                            (1U)

#define CM_L4CFG_MAILBOX9_CLKCTRL_IDLEST_SHIFT                                                              (16U)
#define CM_L4CFG_MAILBOX9_CLKCTRL_IDLEST_MASK                                                               (0x00030000U)
#define CM_L4CFG_MAILBOX9_CLKCTRL_IDLEST_DISABLE                                                             (3U)
#define CM_L4CFG_MAILBOX9_CLKCTRL_IDLEST_IDLE                                                                (2U)
#define CM_L4CFG_MAILBOX9_CLKCTRL_IDLEST_FUNC                                                                (0U)
#define CM_L4CFG_MAILBOX9_CLKCTRL_IDLEST_TRANS                                                               (1U)

#define CM_L4CFG_MAILBOX10_CLKCTRL_RESERVED_SHIFT                                                           (2U)
#define CM_L4CFG_MAILBOX10_CLKCTRL_RESERVED_MASK                                                            (0x0000fffcU)

#define CM_L4CFG_MAILBOX10_CLKCTRL_RESERVED1_SHIFT                                                          (18U)
#define CM_L4CFG_MAILBOX10_CLKCTRL_RESERVED1_MASK                                                           (0xfffc0000U)

#define CM_L4CFG_MAILBOX10_CLKCTRL_MODULEMODE_SHIFT                                                         (0U)
#define CM_L4CFG_MAILBOX10_CLKCTRL_MODULEMODE_MASK                                                          (0x00000003U)
#define CM_L4CFG_MAILBOX10_CLKCTRL_MODULEMODE_AUTO                                                           (1U)

#define CM_L4CFG_MAILBOX10_CLKCTRL_IDLEST_SHIFT                                                             (16U)
#define CM_L4CFG_MAILBOX10_CLKCTRL_IDLEST_MASK                                                              (0x00030000U)
#define CM_L4CFG_MAILBOX10_CLKCTRL_IDLEST_DISABLE                                                            (3U)
#define CM_L4CFG_MAILBOX10_CLKCTRL_IDLEST_IDLE                                                               (2U)
#define CM_L4CFG_MAILBOX10_CLKCTRL_IDLEST_FUNC                                                               (0U)
#define CM_L4CFG_MAILBOX10_CLKCTRL_IDLEST_TRANS                                                              (1U)

#define CM_L4CFG_MAILBOX11_CLKCTRL_RESERVED_SHIFT                                                           (2U)
#define CM_L4CFG_MAILBOX11_CLKCTRL_RESERVED_MASK                                                            (0x0000fffcU)

#define CM_L4CFG_MAILBOX11_CLKCTRL_RESERVED1_SHIFT                                                          (18U)
#define CM_L4CFG_MAILBOX11_CLKCTRL_RESERVED1_MASK                                                           (0xfffc0000U)

#define CM_L4CFG_MAILBOX11_CLKCTRL_MODULEMODE_SHIFT                                                         (0U)
#define CM_L4CFG_MAILBOX11_CLKCTRL_MODULEMODE_MASK                                                          (0x00000003U)
#define CM_L4CFG_MAILBOX11_CLKCTRL_MODULEMODE_AUTO                                                           (1U)

#define CM_L4CFG_MAILBOX11_CLKCTRL_IDLEST_SHIFT                                                             (16U)
#define CM_L4CFG_MAILBOX11_CLKCTRL_IDLEST_MASK                                                              (0x00030000U)
#define CM_L4CFG_MAILBOX11_CLKCTRL_IDLEST_DISABLE                                                            (3U)
#define CM_L4CFG_MAILBOX11_CLKCTRL_IDLEST_IDLE                                                               (2U)
#define CM_L4CFG_MAILBOX11_CLKCTRL_IDLEST_FUNC                                                               (0U)
#define CM_L4CFG_MAILBOX11_CLKCTRL_IDLEST_TRANS                                                              (1U)

#define CM_L4CFG_MAILBOX12_CLKCTRL_RESERVED_SHIFT                                                           (2U)
#define CM_L4CFG_MAILBOX12_CLKCTRL_RESERVED_MASK                                                            (0x0000fffcU)

#define CM_L4CFG_MAILBOX12_CLKCTRL_RESERVED1_SHIFT                                                          (18U)
#define CM_L4CFG_MAILBOX12_CLKCTRL_RESERVED1_MASK                                                           (0xfffc0000U)

#define CM_L4CFG_MAILBOX12_CLKCTRL_MODULEMODE_SHIFT                                                         (0U)
#define CM_L4CFG_MAILBOX12_CLKCTRL_MODULEMODE_MASK                                                          (0x00000003U)
#define CM_L4CFG_MAILBOX12_CLKCTRL_MODULEMODE_AUTO                                                           (1U)

#define CM_L4CFG_MAILBOX12_CLKCTRL_IDLEST_SHIFT                                                             (16U)
#define CM_L4CFG_MAILBOX12_CLKCTRL_IDLEST_MASK                                                              (0x00030000U)
#define CM_L4CFG_MAILBOX12_CLKCTRL_IDLEST_DISABLE                                                            (3U)
#define CM_L4CFG_MAILBOX12_CLKCTRL_IDLEST_IDLE                                                               (2U)
#define CM_L4CFG_MAILBOX12_CLKCTRL_IDLEST_FUNC                                                               (0U)
#define CM_L4CFG_MAILBOX12_CLKCTRL_IDLEST_TRANS                                                              (1U)

#define CM_L4CFG_MAILBOX13_CLKCTRL_RESERVED_SHIFT                                                           (2U)
#define CM_L4CFG_MAILBOX13_CLKCTRL_RESERVED_MASK                                                            (0x0000fffcU)

#define CM_L4CFG_MAILBOX13_CLKCTRL_RESERVED1_SHIFT                                                          (18U)
#define CM_L4CFG_MAILBOX13_CLKCTRL_RESERVED1_MASK                                                           (0xfffc0000U)

#define CM_L4CFG_MAILBOX13_CLKCTRL_MODULEMODE_SHIFT                                                         (0U)
#define CM_L4CFG_MAILBOX13_CLKCTRL_MODULEMODE_MASK                                                          (0x00000003U)
#define CM_L4CFG_MAILBOX13_CLKCTRL_MODULEMODE_AUTO                                                           (1U)

#define CM_L4CFG_MAILBOX13_CLKCTRL_IDLEST_SHIFT                                                             (16U)
#define CM_L4CFG_MAILBOX13_CLKCTRL_IDLEST_MASK                                                              (0x00030000U)
#define CM_L4CFG_MAILBOX13_CLKCTRL_IDLEST_DISABLE                                                            (3U)
#define CM_L4CFG_MAILBOX13_CLKCTRL_IDLEST_IDLE                                                               (2U)
#define CM_L4CFG_MAILBOX13_CLKCTRL_IDLEST_FUNC                                                               (0U)
#define CM_L4CFG_MAILBOX13_CLKCTRL_IDLEST_TRANS                                                              (1U)

#define CM_L3INSTR_CLKSTCTRL_CLKTRCTRL_SHIFT                                                                (0U)
#define CM_L3INSTR_CLKSTCTRL_CLKTRCTRL_MASK                                                                 (0x00000003U)
#define CM_L3INSTR_CLKSTCTRL_CLKTRCTRL_HW_AUTO                                                               (3U)

#define CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_L3_GICLK_SHIFT                                             (8U)
#define CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_L3_GICLK_MASK                                              (0x00000100U)
#define CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_L3_GICLK_INACT                                              (0U)
#define CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_L3_GICLK_ACT                                                (1U)

#define CM_L3INSTR_CLKSTCTRL_RESERVED_SHIFT                                                                 (2U)
#define CM_L3INSTR_CLKSTCTRL_RESERVED_MASK                                                                  (0x000000fcU)

#define CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_DLL_AGING_GCLK_SHIFT                                       (9U)
#define CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_DLL_AGING_GCLK_MASK                                        (0x00000200U)
#define CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_DLL_AGING_GCLK_INACT                                        (0U)
#define CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_DLL_AGING_GCLK_ACT                                          (1U)

#define CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_TS_GCLK_SHIFT                                              (10U)
#define CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_TS_GCLK_MASK                                               (0x00000400U)
#define CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_TS_GCLK_INACT                                               (0U)
#define CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_TS_GCLK_ACT                                                 (1U)

#define CM_L3INSTR_CLKSTCTRL_RESERVED1_SHIFT                                                                (11U)
#define CM_L3INSTR_CLKSTCTRL_RESERVED1_MASK                                                                 (0xfffff800U)

#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_RESERVED_SHIFT                                                         (2U)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_RESERVED_MASK                                                          (0x0000fffcU)

#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_RESERVED1_SHIFT                                                        (18U)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_RESERVED1_MASK                                                         (0xfffc0000U)

#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_IDLEST_SHIFT                                                           (16U)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_IDLEST_MASK                                                            (0x00030000U)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_IDLEST_DISABLE                                                          (3U)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_IDLEST_IDLE                                                             (2U)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_IDLEST_FUNC                                                             (0U)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_IDLEST_TRANS                                                            (1U)

#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_MODULEMODE_SHIFT                                                       (0U)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_MODULEMODE_MASK                                                        (0x00000003U)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_MODULEMODE_DISABLED                                                     (0U)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_MODULEMODE_AUTO                                                         (1U)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_MODULEMODE_RESERVED_2                                                   (2U)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_MODULEMODE_RESERVED                                                     (3U)

#define CM_L3INSTR_L3_INSTR_CLKCTRL_RESERVED_SHIFT                                                          (2U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL_RESERVED_MASK                                                           (0x0000fffcU)

#define CM_L3INSTR_L3_INSTR_CLKCTRL_RESERVED1_SHIFT                                                         (18U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL_RESERVED1_MASK                                                          (0xfffc0000U)

#define CM_L3INSTR_L3_INSTR_CLKCTRL_IDLEST_SHIFT                                                            (16U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL_IDLEST_MASK                                                             (0x00030000U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL_IDLEST_DISABLE                                                           (3U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL_IDLEST_IDLE                                                              (2U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL_IDLEST_FUNC                                                              (0U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL_IDLEST_TRANS                                                             (1U)

#define CM_L3INSTR_L3_INSTR_CLKCTRL_MODULEMODE_SHIFT                                                        (0U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL_MODULEMODE_MASK                                                         (0x00000003U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL_MODULEMODE_DISABLED                                                      (0U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL_MODULEMODE_AUTO                                                          (1U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL_MODULEMODE_RESERVED_2                                                    (2U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL_MODULEMODE_RESERVED                                                      (3U)

#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_RESERVED_SHIFT                                                        (2U)
#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_RESERVED_MASK                                                         (0x0000fffcU)

#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_RESERVED1_SHIFT                                                       (18U)
#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_RESERVED1_MASK                                                        (0xfffc0000U)

#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_IDLEST_SHIFT                                                          (16U)
#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_IDLEST_MASK                                                           (0x00030000U)
#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_IDLEST_DISABLE                                                         (3U)
#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_IDLEST_IDLE                                                            (2U)
#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_IDLEST_FUNC                                                            (0U)
#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_IDLEST_TRANS                                                           (1U)

#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_MODULEMODE_SHIFT                                                      (0U)
#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_MODULEMODE_MASK                                                       (0x00000003U)
#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_MODULEMODE_DISABLED                                                    (0U)
#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_MODULEMODE_AUTO                                                        (1U)
#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_MODULEMODE_RESERVED_2                                                  (2U)
#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_MODULEMODE_RESERVED                                                    (3U)

#define CM_L3INSTR_DLL_AGING_CLKCTRL_RESERVED_SHIFT                                                         (2U)
#define CM_L3INSTR_DLL_AGING_CLKCTRL_RESERVED_MASK                                                          (0x0000fffcU)

#define CM_L3INSTR_DLL_AGING_CLKCTRL_RESERVED1_SHIFT                                                        (18U)
#define CM_L3INSTR_DLL_AGING_CLKCTRL_RESERVED1_MASK                                                         (0xfffc0000U)

#define CM_L3INSTR_DLL_AGING_CLKCTRL_MODULEMODE_SHIFT                                                       (0U)
#define CM_L3INSTR_DLL_AGING_CLKCTRL_MODULEMODE_MASK                                                        (0x00000003U)
#define CM_L3INSTR_DLL_AGING_CLKCTRL_MODULEMODE_AUTO                                                         (1U)

#define CM_L3INSTR_DLL_AGING_CLKCTRL_IDLEST_SHIFT                                                           (16U)
#define CM_L3INSTR_DLL_AGING_CLKCTRL_IDLEST_MASK                                                            (0x00030000U)
#define CM_L3INSTR_DLL_AGING_CLKCTRL_IDLEST_DISABLE                                                          (3U)
#define CM_L3INSTR_DLL_AGING_CLKCTRL_IDLEST_IDLE                                                             (2U)
#define CM_L3INSTR_DLL_AGING_CLKCTRL_IDLEST_FUNC                                                             (0U)
#define CM_L3INSTR_DLL_AGING_CLKCTRL_IDLEST_TRANS                                                            (1U)

#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_RESERVED_SHIFT                                               (2U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_RESERVED_MASK                                                (0x0000fffcU)

#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_RESERVED1_SHIFT                                              (18U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_RESERVED1_MASK                                               (0x00fc0000U)

#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_MODULEMODE_SHIFT                                             (0U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_MODULEMODE_MASK                                              (0x00000003U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_MODULEMODE_AUTO                                               (1U)

#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_IDLEST_SHIFT                                                 (16U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_IDLEST_MASK                                                  (0x00030000U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_IDLEST_DISABLE                                                (3U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_IDLEST_IDLE                                                   (2U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_IDLEST_FUNC                                                   (0U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_IDLEST_TRANS                                                  (1U)

#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_CLKSEL_SHIFT                                                 (24U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_CLKSEL_MASK                                                  (0x03000000U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_CLKSEL_DIV8                                                   (0U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_CLKSEL_DIV16                                                  (1U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_CLKSEL_DIV32                                                  (2U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_CLKSEL_RESERVED                                               (3U)

#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_RESERVED2_SHIFT                                              (26U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_RESERVED2_MASK                                               (0xfc000000U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_CORE_CM_CORE_H_ */
