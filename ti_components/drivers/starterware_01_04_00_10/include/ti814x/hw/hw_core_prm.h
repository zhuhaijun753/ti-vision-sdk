/******************************************************************************
*
* hw_core_prm.h - register-level header file for PRCM
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
#ifndef HW_CORE_PRM_H_
#define HW_CORE_PRM_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define PM_CORE_PWRSTCTRL                                                                                   (0x0U)
#define PM_CORE_PWRSTST                                                                                     (0x4U)
#define RM_L3MAIN1_L3_MAIN_1_CONTEXT                                                                        (0x24U)
#define RM_L3MAIN1_GPMC_CONTEXT                                                                             (0x2cU)
#define RM_L3MAIN1_MMU_EDMA_CONTEXT                                                                         (0x34U)
#define RM_L3MAIN1_MMU_PCIESS_CONTEXT                                                                       (0x4cU)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP                                                                          (0x50U)
#define RM_L3MAIN1_OCMC_RAM1_CONTEXT                                                                        (0x54U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP                                                                          (0x58U)
#define RM_L3MAIN1_OCMC_RAM2_CONTEXT                                                                        (0x5cU)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP                                                                          (0x60U)
#define RM_L3MAIN1_OCMC_RAM3_CONTEXT                                                                        (0x64U)
#define RM_L3MAIN1_OCMC_ROM_CONTEXT                                                                         (0x6cU)
#define PM_L3MAIN1_TPCC_WKDEP                                                                               (0x70U)
#define RM_L3MAIN1_TPCC_CONTEXT                                                                             (0x74U)
#define PM_L3MAIN1_TPTC1_WKDEP                                                                              (0x78U)
#define RM_L3MAIN1_TPTC1_CONTEXT                                                                            (0x7cU)
#define PM_L3MAIN1_TPTC2_WKDEP                                                                              (0x80U)
#define RM_L3MAIN1_TPTC2_CONTEXT                                                                            (0x84U)
#define RM_L3MAIN1_VCP1_CONTEXT                                                                             (0x8cU)
#define RM_L3MAIN1_VCP2_CONTEXT                                                                             (0x94U)
#define RM_IPU2_RSTCTRL                                                                                     (0x210U)
#define RM_IPU2_RSTST                                                                                       (0x214U)
#define RM_IPU2_IPU2_CONTEXT                                                                                (0x224U)
#define RM_DMA_DMA_SYSTEM_CONTEXT                                                                           (0x324U)
#define RM_EMIF_DMM_CONTEXT                                                                                 (0x424U)
#define RM_EMIF_EMIF_OCP_FW_CONTEXT                                                                         (0x42cU)
#define RM_EMIF_EMIF1_CONTEXT                                                                               (0x434U)
#define RM_EMIF_EMIF2_CONTEXT                                                                               (0x43cU)
#define RM_EMIF_EMIF_DLL_CONTEXT                                                                            (0x444U)
#define RM_ATL_ATL_CONTEXT                                                                                  (0x524U)
#define RM_L4CFG_L4_CFG_CONTEXT                                                                             (0x624U)
#define RM_L4CFG_SPINLOCK_CONTEXT                                                                           (0x62cU)
#define RM_L4CFG_MAILBOX1_CONTEXT                                                                           (0x634U)
#define RM_L4CFG_SAR_ROM_CONTEXT                                                                            (0x63cU)
#define RM_L4CFG_OCP2SCP2_CONTEXT                                                                           (0x644U)
#define RM_L4CFG_MAILBOX2_CONTEXT                                                                           (0x64cU)
#define RM_L4CFG_MAILBOX3_CONTEXT                                                                           (0x654U)
#define RM_L4CFG_MAILBOX4_CONTEXT                                                                           (0x65cU)
#define RM_L4CFG_MAILBOX5_CONTEXT                                                                           (0x664U)
#define RM_L4CFG_MAILBOX6_CONTEXT                                                                           (0x66cU)
#define RM_L4CFG_MAILBOX7_CONTEXT                                                                           (0x674U)
#define RM_L4CFG_MAILBOX8_CONTEXT                                                                           (0x67cU)
#define RM_L4CFG_MAILBOX9_CONTEXT                                                                           (0x684U)
#define RM_L4CFG_MAILBOX10_CONTEXT                                                                          (0x68cU)
#define RM_L4CFG_MAILBOX11_CONTEXT                                                                          (0x694U)
#define RM_L4CFG_MAILBOX12_CONTEXT                                                                          (0x69cU)
#define RM_L4CFG_MAILBOX13_CONTEXT                                                                          (0x6a4U)
#define RM_L4CFG_SPARE_SMARTREFLEX_RTC_CONTEXT                                                              (0x6acU)
#define RM_L4CFG_SPARE_SMARTREFLEX_SDRAM_CONTEXT                                                            (0x6b4U)
#define RM_L4CFG_SPARE_SMARTREFLEX_WKUP_CONTEXT                                                             (0x6bcU)
#define RM_L4CFG_IO_DELAY_BLOCK_CONTEXT                                                                     (0x6c4U)
#define RM_L3INSTR_L3_MAIN_2_CONTEXT                                                                        (0x724U)
#define RM_L3INSTR_L3_INSTR_CONTEXT                                                                         (0x72cU)
#define RM_L3INSTR_OCP_WP_NOC_CONTEXT                                                                       (0x744U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define PM_CORE_PWRSTCTRL_CORE_OTHER_BANK_RETSTATE_SHIFT                                                    (8U)
#define PM_CORE_PWRSTCTRL_CORE_OTHER_BANK_RETSTATE_MASK                                                     (0x00000100U)
#define PM_CORE_PWRSTCTRL_CORE_OTHER_BANK_RETSTATE_MEM_RET                                                   (1U)

#define PM_CORE_PWRSTCTRL_CORE_OTHER_BANK_ONSTATE_SHIFT                                                     (16U)
#define PM_CORE_PWRSTCTRL_CORE_OTHER_BANK_ONSTATE_MASK                                                      (0x00030000U)
#define PM_CORE_PWRSTCTRL_CORE_OTHER_BANK_ONSTATE_MEM_ON                                                     (3U)

#define PM_CORE_PWRSTCTRL_LOGICRETSTATE_SHIFT                                                               (2U)
#define PM_CORE_PWRSTCTRL_LOGICRETSTATE_MASK                                                                (0x00000004U)
#define PM_CORE_PWRSTCTRL_LOGICRETSTATE_LOGIC_RET                                                            (1U)
#define PM_CORE_PWRSTCTRL_LOGICRETSTATE_LOGIC_OFF                                                            (0U)

#define PM_CORE_PWRSTCTRL_POWERSTATE_SHIFT                                                                  (0U)
#define PM_CORE_PWRSTCTRL_POWERSTATE_MASK                                                                   (0x00000003U)
#define PM_CORE_PWRSTCTRL_POWERSTATE_RESERVED                                                                (0U)
#define PM_CORE_PWRSTCTRL_POWERSTATE_INACT                                                                   (2U)
#define PM_CORE_PWRSTCTRL_POWERSTATE_RET                                                                     (1U)
#define PM_CORE_PWRSTCTRL_POWERSTATE_ON                                                                      (3U)

#define PM_CORE_PWRSTCTRL_CORE_OCMRAM_RETSTATE_SHIFT                                                        (9U)
#define PM_CORE_PWRSTCTRL_CORE_OCMRAM_RETSTATE_MASK                                                         (0x00000200U)
#define PM_CORE_PWRSTCTRL_CORE_OCMRAM_RETSTATE_MEM_RET                                                       (1U)

#define PM_CORE_PWRSTCTRL_CORE_OCMRAM_ONSTATE_SHIFT                                                         (18U)
#define PM_CORE_PWRSTCTRL_CORE_OCMRAM_ONSTATE_MASK                                                          (0x000c0000U)
#define PM_CORE_PWRSTCTRL_CORE_OCMRAM_ONSTATE_MEM_ON                                                         (3U)

#define PM_CORE_PWRSTCTRL_IPU_L2RAM_RETSTATE_SHIFT                                                          (10U)
#define PM_CORE_PWRSTCTRL_IPU_L2RAM_RETSTATE_MASK                                                           (0x00000400U)
#define PM_CORE_PWRSTCTRL_IPU_L2RAM_RETSTATE_MEM_RET                                                         (1U)
#define PM_CORE_PWRSTCTRL_IPU_L2RAM_RETSTATE_MEM_OFF                                                         (0U)

#define PM_CORE_PWRSTCTRL_IPU_L2RAM_ONSTATE_SHIFT                                                           (20U)
#define PM_CORE_PWRSTCTRL_IPU_L2RAM_ONSTATE_MASK                                                            (0x00300000U)
#define PM_CORE_PWRSTCTRL_IPU_L2RAM_ONSTATE_MEM_ON                                                           (3U)

#define PM_CORE_PWRSTCTRL_IPU_UNICACHE_RETSTATE_SHIFT                                                       (11U)
#define PM_CORE_PWRSTCTRL_IPU_UNICACHE_RETSTATE_MASK                                                        (0x00000800U)
#define PM_CORE_PWRSTCTRL_IPU_UNICACHE_RETSTATE_MEM_OFF                                                      (0U)
#define PM_CORE_PWRSTCTRL_IPU_UNICACHE_RETSTATE_MEM_RET                                                      (1U)

#define PM_CORE_PWRSTCTRL_IPU_UNICACHE_ONSTATE_SHIFT                                                        (22U)
#define PM_CORE_PWRSTCTRL_IPU_UNICACHE_ONSTATE_MASK                                                         (0x00c00000U)
#define PM_CORE_PWRSTCTRL_IPU_UNICACHE_ONSTATE_MEM_ON                                                        (3U)

#define PM_CORE_PWRSTCTRL_RESERVED1_SHIFT                                                                   (13U)
#define PM_CORE_PWRSTCTRL_RESERVED1_MASK                                                                    (0x0000e000U)

#define PM_CORE_PWRSTCTRL_RESERVED2_SHIFT                                                                   (26U)
#define PM_CORE_PWRSTCTRL_RESERVED2_MASK                                                                    (0xfc000000U)

#define PM_CORE_PWRSTCTRL_OCP_NRET_BANK_RETSTATE_SHIFT                                                      (12U)
#define PM_CORE_PWRSTCTRL_OCP_NRET_BANK_RETSTATE_MASK                                                       (0x00001000U)
#define PM_CORE_PWRSTCTRL_OCP_NRET_BANK_RETSTATE_MEM_OFF                                                     (0U)

#define PM_CORE_PWRSTCTRL_OCP_NRET_BANK_ONSTATE_SHIFT                                                       (24U)
#define PM_CORE_PWRSTCTRL_OCP_NRET_BANK_ONSTATE_MASK                                                        (0x03000000U)
#define PM_CORE_PWRSTCTRL_OCP_NRET_BANK_ONSTATE_MEM_ON                                                       (3U)

#define PM_CORE_PWRSTCTRL_LOWPOWERSTATECHANGE_SHIFT                                                         (4U)
#define PM_CORE_PWRSTCTRL_LOWPOWERSTATECHANGE_MASK                                                          (0x00000010U)
#define PM_CORE_PWRSTCTRL_LOWPOWERSTATECHANGE_EN                                                             (1U)
#define PM_CORE_PWRSTCTRL_LOWPOWERSTATECHANGE_DIS                                                            (0U)

#define PM_CORE_PWRSTCTRL_RESERVED_SHIFT                                                                    (5U)
#define PM_CORE_PWRSTCTRL_RESERVED_MASK                                                                     (0x000000e0U)

#define PM_CORE_PWRSTCTRL_RESERVED3_SHIFT                                                                   (3U)
#define PM_CORE_PWRSTCTRL_RESERVED3_MASK                                                                    (0x00000008U)

#define PM_CORE_PWRSTST_POWERSTATEST_SHIFT                                                                  (0U)
#define PM_CORE_PWRSTST_POWERSTATEST_MASK                                                                   (0x00000003U)
#define PM_CORE_PWRSTST_POWERSTATEST_ON                                                                      (3U)
#define PM_CORE_PWRSTST_POWERSTATEST_RESERVED                                                                (0U)
#define PM_CORE_PWRSTST_POWERSTATEST_RET                                                                     (1U)
#define PM_CORE_PWRSTST_POWERSTATEST_INACTIVE                                                                (2U)

#define PM_CORE_PWRSTST_INTRANSITION_SHIFT                                                                  (20U)
#define PM_CORE_PWRSTST_INTRANSITION_MASK                                                                   (0x00100000U)
#define PM_CORE_PWRSTST_INTRANSITION_NO                                                                      (0U)
#define PM_CORE_PWRSTST_INTRANSITION_ONGOING                                                                 (1U)

#define PM_CORE_PWRSTST_LOGICSTATEST_SHIFT                                                                  (2U)
#define PM_CORE_PWRSTST_LOGICSTATEST_MASK                                                                   (0x00000004U)
#define PM_CORE_PWRSTST_LOGICSTATEST_ON                                                                      (1U)
#define PM_CORE_PWRSTST_LOGICSTATEST_OFF                                                                     (0U)

#define PM_CORE_PWRSTST_CORE_OTHER_BANK_STATEST_SHIFT                                                       (4U)
#define PM_CORE_PWRSTST_CORE_OTHER_BANK_STATEST_MASK                                                        (0x00000030U)
#define PM_CORE_PWRSTST_CORE_OTHER_BANK_STATEST_MEM_ON                                                       (3U)
#define PM_CORE_PWRSTST_CORE_OTHER_BANK_STATEST_MEM_RET                                                      (1U)
#define PM_CORE_PWRSTST_CORE_OTHER_BANK_STATEST_MEM_OFF                                                      (0U)
#define PM_CORE_PWRSTST_CORE_OTHER_BANK_STATEST_RESERVED                                                     (2U)

#define PM_CORE_PWRSTST_RESERVED_SHIFT                                                                      (3U)
#define PM_CORE_PWRSTST_RESERVED_MASK                                                                       (0x00000008U)

#define PM_CORE_PWRSTST_CORE_OCMRAM_STATEST_SHIFT                                                           (6U)
#define PM_CORE_PWRSTST_CORE_OCMRAM_STATEST_MASK                                                            (0x000000c0U)
#define PM_CORE_PWRSTST_CORE_OCMRAM_STATEST_MEM_ON                                                           (3U)
#define PM_CORE_PWRSTST_CORE_OCMRAM_STATEST_MEM_RET                                                          (1U)
#define PM_CORE_PWRSTST_CORE_OCMRAM_STATEST_MEM_OFF                                                          (0U)
#define PM_CORE_PWRSTST_CORE_OCMRAM_STATEST_RESERVED                                                         (2U)

#define PM_CORE_PWRSTST_IPU_L2RAM_STATEST_SHIFT                                                             (8U)
#define PM_CORE_PWRSTST_IPU_L2RAM_STATEST_MASK                                                              (0x00000300U)
#define PM_CORE_PWRSTST_IPU_L2RAM_STATEST_MEM_ON                                                             (3U)
#define PM_CORE_PWRSTST_IPU_L2RAM_STATEST_MEM_RET                                                            (1U)
#define PM_CORE_PWRSTST_IPU_L2RAM_STATEST_MEM_OFF                                                            (0U)
#define PM_CORE_PWRSTST_IPU_L2RAM_STATEST_RESERVED                                                           (2U)

#define PM_CORE_PWRSTST_IPU_UNICACHE_STATEST_SHIFT                                                          (10U)
#define PM_CORE_PWRSTST_IPU_UNICACHE_STATEST_MASK                                                           (0x00000c00U)
#define PM_CORE_PWRSTST_IPU_UNICACHE_STATEST_MEM_ON                                                          (3U)
#define PM_CORE_PWRSTST_IPU_UNICACHE_STATEST_MEM_RET                                                         (1U)
#define PM_CORE_PWRSTST_IPU_UNICACHE_STATEST_MEM_OFF                                                         (0U)
#define PM_CORE_PWRSTST_IPU_UNICACHE_STATEST_RESERVED                                                        (2U)

#define PM_CORE_PWRSTST_RESERVED1_SHIFT                                                                     (14U)
#define PM_CORE_PWRSTST_RESERVED1_MASK                                                                      (0x000fc000U)

#define PM_CORE_PWRSTST_OCP_NRET_BANK_STATEST_SHIFT                                                         (12U)
#define PM_CORE_PWRSTST_OCP_NRET_BANK_STATEST_MASK                                                          (0x00003000U)
#define PM_CORE_PWRSTST_OCP_NRET_BANK_STATEST_MEM_ON                                                         (3U)
#define PM_CORE_PWRSTST_OCP_NRET_BANK_STATEST_RESERVED1                                                      (1U)
#define PM_CORE_PWRSTST_OCP_NRET_BANK_STATEST_MEM_OFF                                                        (0U)
#define PM_CORE_PWRSTST_OCP_NRET_BANK_STATEST_RESERVED                                                       (2U)

#define PM_CORE_PWRSTST_RESERVED2_SHIFT                                                                     (21U)
#define PM_CORE_PWRSTST_RESERVED2_MASK                                                                      (0x00e00000U)

#define PM_CORE_PWRSTST_RESERVED3_SHIFT                                                                     (26U)
#define PM_CORE_PWRSTST_RESERVED3_MASK                                                                      (0xfc000000U)

#define PM_CORE_PWRSTST_LASTPOWERSTATEENTERED_SHIFT                                                         (24U)
#define PM_CORE_PWRSTST_LASTPOWERSTATEENTERED_MASK                                                          (0x03000000U)
#define PM_CORE_PWRSTST_LASTPOWERSTATEENTERED_ON                                                             (3U)
#define PM_CORE_PWRSTST_LASTPOWERSTATEENTERED_OFF                                                            (0U)
#define PM_CORE_PWRSTST_LASTPOWERSTATEENTERED_RET                                                            (1U)
#define PM_CORE_PWRSTST_LASTPOWERSTATEENTERED_INACTIVE                                                       (2U)

#define RM_L3MAIN1_L3_MAIN_1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                  (0U)
#define RM_L3MAIN1_L3_MAIN_1_CONTEXT_LOSTCONTEXT_DFF_MASK                                                   (0x00000001U)
#define RM_L3MAIN1_L3_MAIN_1_CONTEXT_LOSTCONTEXT_DFF_LOST                                                    (1U)
#define RM_L3MAIN1_L3_MAIN_1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                              (0U)

#define RM_L3MAIN1_L3_MAIN_1_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                  (1U)
#define RM_L3MAIN1_L3_MAIN_1_CONTEXT_LOSTCONTEXT_RFF_MASK                                                   (0x00000002U)
#define RM_L3MAIN1_L3_MAIN_1_CONTEXT_LOSTCONTEXT_RFF_LOST                                                    (1U)
#define RM_L3MAIN1_L3_MAIN_1_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                              (0U)

#define RM_L3MAIN1_L3_MAIN_1_CONTEXT_RESERVED_SHIFT                                                         (2U)
#define RM_L3MAIN1_L3_MAIN_1_CONTEXT_RESERVED_MASK                                                          (0xfffffffcU)

#define RM_L3MAIN1_GPMC_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                       (1U)
#define RM_L3MAIN1_GPMC_CONTEXT_LOSTCONTEXT_RFF_MASK                                                        (0x00000002U)
#define RM_L3MAIN1_GPMC_CONTEXT_LOSTCONTEXT_RFF_LOST                                                         (1U)
#define RM_L3MAIN1_GPMC_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                   (0U)

#define RM_L3MAIN1_GPMC_CONTEXT_RESERVED_SHIFT                                                              (0U)
#define RM_L3MAIN1_GPMC_CONTEXT_RESERVED_MASK                                                               (0x00000001U)

#define RM_L3MAIN1_GPMC_CONTEXT_RESERVED1_SHIFT                                                             (2U)
#define RM_L3MAIN1_GPMC_CONTEXT_RESERVED1_MASK                                                              (0xfffffffcU)

#define RM_L3MAIN1_MMU_EDMA_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                   (1U)
#define RM_L3MAIN1_MMU_EDMA_CONTEXT_LOSTCONTEXT_RFF_MASK                                                    (0x00000002U)
#define RM_L3MAIN1_MMU_EDMA_CONTEXT_LOSTCONTEXT_RFF_LOST                                                     (1U)
#define RM_L3MAIN1_MMU_EDMA_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                               (0U)

#define RM_L3MAIN1_MMU_EDMA_CONTEXT_RESERVED_SHIFT                                                          (2U)
#define RM_L3MAIN1_MMU_EDMA_CONTEXT_RESERVED_MASK                                                           (0xfffffffcU)

#define RM_L3MAIN1_MMU_EDMA_CONTEXT_RESERVED1_SHIFT                                                         (0U)
#define RM_L3MAIN1_MMU_EDMA_CONTEXT_RESERVED1_MASK                                                          (0x00000001U)

#define RM_L3MAIN1_MMU_PCIESS_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                 (1U)
#define RM_L3MAIN1_MMU_PCIESS_CONTEXT_LOSTCONTEXT_RFF_MASK                                                  (0x00000002U)
#define RM_L3MAIN1_MMU_PCIESS_CONTEXT_LOSTCONTEXT_RFF_LOST                                                   (1U)
#define RM_L3MAIN1_MMU_PCIESS_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                             (0U)

#define RM_L3MAIN1_MMU_PCIESS_CONTEXT_RESERVED_SHIFT                                                        (2U)
#define RM_L3MAIN1_MMU_PCIESS_CONTEXT_RESERVED_MASK                                                         (0xfffffffcU)

#define RM_L3MAIN1_MMU_PCIESS_CONTEXT_RESERVED1_SHIFT                                                       (0U)
#define RM_L3MAIN1_MMU_PCIESS_CONTEXT_RESERVED1_MASK                                                        (0x00000001U)

#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_MPU_SHIFT                                              (0U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_MPU_MASK                                               (0x00000001U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_MPU_ENABLED                                             (1U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_MPU_DISABLED                                            (0U)

#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_DSP1_SHIFT                                             (2U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_DSP1_MASK                                              (0x00000004U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_DSP1_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_DSP1_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_IPU2_SHIFT                                             (1U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_IPU2_MASK                                              (0x00000002U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_IPU2_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_IPU2_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_IPU1_SHIFT                                             (4U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_IPU1_MASK                                              (0x00000010U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_IPU1_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_IPU1_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_DSP2_SHIFT                                             (5U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_DSP2_MASK                                              (0x00000020U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_DSP2_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_DSP2_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_EVE1_SHIFT                                             (6U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_EVE1_MASK                                              (0x00000040U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_EVE1_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_EVE1_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_EVE2_SHIFT                                             (7U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_EVE2_MASK                                              (0x00000080U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_EVE2_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_EVE2_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_EVE3_SHIFT                                             (8U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_EVE3_MASK                                              (0x00000100U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_EVE3_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_EVE3_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_EVE4_SHIFT                                             (9U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_EVE4_MASK                                              (0x00000200U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_EVE4_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_EVE4_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM1_WKDEP_RESERVED_SHIFT                                                           (10U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_RESERVED_MASK                                                            (0xfffffc00U)

#define PM_L3MAIN1_OCMC_RAM1_WKDEP_RESERVED1_SHIFT                                                          (3U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_RESERVED1_MASK                                                           (0x00000008U)

#define RM_L3MAIN1_OCMC_RAM1_CONTEXT_RESERVED_SHIFT                                                         (1U)
#define RM_L3MAIN1_OCMC_RAM1_CONTEXT_RESERVED_MASK                                                          (0x000000feU)

#define RM_L3MAIN1_OCMC_RAM1_CONTEXT_RESERVED1_SHIFT                                                        (9U)
#define RM_L3MAIN1_OCMC_RAM1_CONTEXT_RESERVED1_MASK                                                         (0xfffffe00U)

#define RM_L3MAIN1_OCMC_RAM1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                  (0U)
#define RM_L3MAIN1_OCMC_RAM1_CONTEXT_LOSTCONTEXT_DFF_MASK                                                   (0x00000001U)
#define RM_L3MAIN1_OCMC_RAM1_CONTEXT_LOSTCONTEXT_DFF_LOST                                                    (1U)
#define RM_L3MAIN1_OCMC_RAM1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                              (0U)

#define RM_L3MAIN1_OCMC_RAM1_CONTEXT_LOSTMEM_CORE_OCMRAM_SHIFT                                              (8U)
#define RM_L3MAIN1_OCMC_RAM1_CONTEXT_LOSTMEM_CORE_OCMRAM_MASK                                               (0x00000100U)
#define RM_L3MAIN1_OCMC_RAM1_CONTEXT_LOSTMEM_CORE_OCMRAM_LOST                                                (1U)
#define RM_L3MAIN1_OCMC_RAM1_CONTEXT_LOSTMEM_CORE_OCMRAM_MAINTAINED                                          (0U)

#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_MPU_SHIFT                                              (0U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_MPU_MASK                                               (0x00000001U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_MPU_ENABLED                                             (1U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_MPU_DISABLED                                            (0U)

#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_IPU2_SHIFT                                             (1U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_IPU2_MASK                                              (0x00000002U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_IPU2_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_IPU2_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_DSP1_SHIFT                                             (2U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_DSP1_MASK                                              (0x00000004U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_DSP1_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_DSP1_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM2_WKDEP_RESERVED1_SHIFT                                                          (3U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_RESERVED1_MASK                                                           (0x00000008U)

#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_IPU1_SHIFT                                             (4U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_IPU1_MASK                                              (0x00000010U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_IPU1_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_IPU1_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_DSP2_SHIFT                                             (5U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_DSP2_MASK                                              (0x00000020U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_DSP2_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_DSP2_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_EVE1_SHIFT                                             (6U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_EVE1_MASK                                              (0x00000040U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_EVE1_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_EVE1_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_EVE2_SHIFT                                             (7U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_EVE2_MASK                                              (0x00000080U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_EVE2_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_EVE2_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_EVE3_SHIFT                                             (8U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_EVE3_MASK                                              (0x00000100U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_EVE3_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_EVE3_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_EVE4_SHIFT                                             (9U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_EVE4_MASK                                              (0x00000200U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_EVE4_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_WKUPDEP_OCMC_RAM2_EVE4_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM2_WKDEP_RESERVED_SHIFT                                                           (10U)
#define PM_L3MAIN1_OCMC_RAM2_WKDEP_RESERVED_MASK                                                            (0xfffffc00U)

#define RM_L3MAIN1_OCMC_RAM2_CONTEXT_RESERVED_SHIFT                                                         (1U)
#define RM_L3MAIN1_OCMC_RAM2_CONTEXT_RESERVED_MASK                                                          (0x000000feU)

#define RM_L3MAIN1_OCMC_RAM2_CONTEXT_RESERVED1_SHIFT                                                        (9U)
#define RM_L3MAIN1_OCMC_RAM2_CONTEXT_RESERVED1_MASK                                                         (0xfffffe00U)

#define RM_L3MAIN1_OCMC_RAM2_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                  (0U)
#define RM_L3MAIN1_OCMC_RAM2_CONTEXT_LOSTCONTEXT_DFF_MASK                                                   (0x00000001U)
#define RM_L3MAIN1_OCMC_RAM2_CONTEXT_LOSTCONTEXT_DFF_LOST                                                    (1U)
#define RM_L3MAIN1_OCMC_RAM2_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                              (0U)

#define RM_L3MAIN1_OCMC_RAM2_CONTEXT_LOSTMEM_CORE_OCMRAM_SHIFT                                              (8U)
#define RM_L3MAIN1_OCMC_RAM2_CONTEXT_LOSTMEM_CORE_OCMRAM_MASK                                               (0x00000100U)
#define RM_L3MAIN1_OCMC_RAM2_CONTEXT_LOSTMEM_CORE_OCMRAM_LOST                                                (1U)
#define RM_L3MAIN1_OCMC_RAM2_CONTEXT_LOSTMEM_CORE_OCMRAM_MAINTAINED                                          (0U)

#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_MPU_SHIFT                                              (0U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_MPU_MASK                                               (0x00000001U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_MPU_ENABLED                                             (1U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_MPU_DISABLED                                            (0U)

#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_IPU2_SHIFT                                             (1U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_IPU2_MASK                                              (0x00000002U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_IPU2_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_IPU2_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_DSP1_SHIFT                                             (2U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_DSP1_MASK                                              (0x00000004U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_DSP1_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_DSP1_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM3_WKDEP_RESERVED1_SHIFT                                                          (3U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_RESERVED1_MASK                                                           (0x00000008U)

#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_IPU1_SHIFT                                             (4U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_IPU1_MASK                                              (0x00000010U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_IPU1_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_IPU1_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_DSP2_SHIFT                                             (5U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_DSP2_MASK                                              (0x00000020U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_DSP2_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_DSP2_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_EVE1_SHIFT                                             (6U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_EVE1_MASK                                              (0x00000040U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_EVE1_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_EVE1_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_EVE2_SHIFT                                             (7U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_EVE2_MASK                                              (0x00000080U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_EVE2_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_EVE2_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_EVE3_SHIFT                                             (8U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_EVE3_MASK                                              (0x00000100U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_EVE3_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_EVE3_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_EVE4_SHIFT                                             (9U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_EVE4_MASK                                              (0x00000200U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_EVE4_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_WKUPDEP_OCMC_RAM3_EVE4_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM3_WKDEP_RESERVED_SHIFT                                                           (10U)
#define PM_L3MAIN1_OCMC_RAM3_WKDEP_RESERVED_MASK                                                            (0xfffffc00U)

#define RM_L3MAIN1_OCMC_RAM3_CONTEXT_RESERVED_SHIFT                                                         (1U)
#define RM_L3MAIN1_OCMC_RAM3_CONTEXT_RESERVED_MASK                                                          (0x000000feU)

#define RM_L3MAIN1_OCMC_RAM3_CONTEXT_RESERVED1_SHIFT                                                        (9U)
#define RM_L3MAIN1_OCMC_RAM3_CONTEXT_RESERVED1_MASK                                                         (0xfffffe00U)

#define RM_L3MAIN1_OCMC_RAM3_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                  (0U)
#define RM_L3MAIN1_OCMC_RAM3_CONTEXT_LOSTCONTEXT_DFF_MASK                                                   (0x00000001U)
#define RM_L3MAIN1_OCMC_RAM3_CONTEXT_LOSTCONTEXT_DFF_LOST                                                    (1U)
#define RM_L3MAIN1_OCMC_RAM3_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                              (0U)

#define RM_L3MAIN1_OCMC_RAM3_CONTEXT_LOSTMEM_CORE_OCMRAM_SHIFT                                              (8U)
#define RM_L3MAIN1_OCMC_RAM3_CONTEXT_LOSTMEM_CORE_OCMRAM_MASK                                               (0x00000100U)
#define RM_L3MAIN1_OCMC_RAM3_CONTEXT_LOSTMEM_CORE_OCMRAM_LOST                                                (1U)
#define RM_L3MAIN1_OCMC_RAM3_CONTEXT_LOSTMEM_CORE_OCMRAM_MAINTAINED                                          (0U)

#define RM_L3MAIN1_OCMC_ROM_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                   (0U)
#define RM_L3MAIN1_OCMC_ROM_CONTEXT_LOSTCONTEXT_DFF_MASK                                                    (0x00000001U)
#define RM_L3MAIN1_OCMC_ROM_CONTEXT_LOSTCONTEXT_DFF_LOST                                                     (1U)
#define RM_L3MAIN1_OCMC_ROM_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                               (0U)

#define RM_L3MAIN1_OCMC_ROM_CONTEXT_RESERVED_SHIFT                                                          (1U)
#define RM_L3MAIN1_OCMC_ROM_CONTEXT_RESERVED_MASK                                                           (0x000000feU)

#define RM_L3MAIN1_OCMC_ROM_CONTEXT_LOSTMEM_CORE_OCMROM_SHIFT                                               (8U)
#define RM_L3MAIN1_OCMC_ROM_CONTEXT_LOSTMEM_CORE_OCMROM_MASK                                                (0x00000100U)
#define RM_L3MAIN1_OCMC_ROM_CONTEXT_LOSTMEM_CORE_OCMROM_LOST                                                 (1U)
#define RM_L3MAIN1_OCMC_ROM_CONTEXT_LOSTMEM_CORE_OCMROM_MAINTAINED                                           (0U)

#define RM_L3MAIN1_OCMC_ROM_CONTEXT_RESERVED1_SHIFT                                                         (9U)
#define RM_L3MAIN1_OCMC_ROM_CONTEXT_RESERVED1_MASK                                                          (0xfffffe00U)

#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_MPU_SHIFT                                                        (0U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_MPU_MASK                                                         (0x00000001U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_MPU_ENABLED                                                       (1U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_MPU_DISABLED                                                      (0U)

#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_DSP1_SHIFT                                                       (2U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_DSP1_MASK                                                        (0x00000004U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_DSP1_ENABLED                                                      (1U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_DSP1_DISABLED                                                     (0U)

#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_IPU2_SHIFT                                                       (1U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_IPU2_MASK                                                        (0x00000002U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_IPU2_ENABLED                                                      (1U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_IPU2_DISABLED                                                     (0U)

#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_IPU1_SHIFT                                                       (4U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_IPU1_MASK                                                        (0x00000010U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_IPU1_ENABLED                                                      (1U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_IPU1_DISABLED                                                     (0U)

#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_DSP2_SHIFT                                                       (5U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_DSP2_MASK                                                        (0x00000020U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_DSP2_ENABLED                                                      (1U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_DSP2_DISABLED                                                     (0U)

#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_EVE1_SHIFT                                                       (6U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_EVE1_MASK                                                        (0x00000040U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_EVE1_ENABLED                                                      (1U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_EVE1_DISABLED                                                     (0U)

#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_EVE2_SHIFT                                                       (7U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_EVE2_MASK                                                        (0x00000080U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_EVE2_ENABLED                                                      (1U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_EVE2_DISABLED                                                     (0U)

#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_EVE3_SHIFT                                                       (8U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_EVE3_MASK                                                        (0x00000100U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_EVE3_ENABLED                                                      (1U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_EVE3_DISABLED                                                     (0U)

#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_EVE4_SHIFT                                                       (9U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_EVE4_MASK                                                        (0x00000200U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_EVE4_ENABLED                                                      (1U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_EVE4_DISABLED                                                     (0U)

#define PM_L3MAIN1_TPCC_WKDEP_RESERVED_SHIFT                                                                (10U)
#define PM_L3MAIN1_TPCC_WKDEP_RESERVED_MASK                                                                 (0xfffffc00U)

#define PM_L3MAIN1_TPCC_WKDEP_RESERVED1_SHIFT                                                               (3U)
#define PM_L3MAIN1_TPCC_WKDEP_RESERVED1_MASK                                                                (0x00000008U)

#define RM_L3MAIN1_TPCC_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                       (1U)
#define RM_L3MAIN1_TPCC_CONTEXT_LOSTCONTEXT_RFF_MASK                                                        (0x00000002U)
#define RM_L3MAIN1_TPCC_CONTEXT_LOSTCONTEXT_RFF_LOST                                                         (1U)
#define RM_L3MAIN1_TPCC_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                   (0U)

#define RM_L3MAIN1_TPCC_CONTEXT_RESERVED_SHIFT                                                              (0U)
#define RM_L3MAIN1_TPCC_CONTEXT_RESERVED_MASK                                                               (0x00000001U)

#define RM_L3MAIN1_TPCC_CONTEXT_RESERVED1_SHIFT                                                             (2U)
#define RM_L3MAIN1_TPCC_CONTEXT_RESERVED1_MASK                                                              (0x000000fcU)

#define RM_L3MAIN1_TPCC_CONTEXT_LOSTMEM_TPCC_BANK_SHIFT                                                     (8U)
#define RM_L3MAIN1_TPCC_CONTEXT_LOSTMEM_TPCC_BANK_MASK                                                      (0x00000100U)
#define RM_L3MAIN1_TPCC_CONTEXT_LOSTMEM_TPCC_BANK_LOST                                                       (1U)
#define RM_L3MAIN1_TPCC_CONTEXT_LOSTMEM_TPCC_BANK_MAINTAINED                                                 (0U)

#define RM_L3MAIN1_TPCC_CONTEXT_RESERVED2_SHIFT                                                             (9U)
#define RM_L3MAIN1_TPCC_CONTEXT_RESERVED2_MASK                                                              (0xfffffe00U)

#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_MPU_SHIFT                                                      (0U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_MPU_MASK                                                       (0x00000001U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_MPU_ENABLED                                                     (1U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_MPU_DISABLED                                                    (0U)

#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_DSP1_SHIFT                                                     (2U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_DSP1_MASK                                                      (0x00000004U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_DSP1_ENABLED                                                    (1U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_DSP1_DISABLED                                                   (0U)

#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_IPU2_SHIFT                                                     (1U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_IPU2_MASK                                                      (0x00000002U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_IPU2_ENABLED                                                    (1U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_IPU2_DISABLED                                                   (0U)

#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_IPU1_SHIFT                                                     (4U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_IPU1_MASK                                                      (0x00000010U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_IPU1_ENABLED                                                    (1U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_IPU1_DISABLED                                                   (0U)

#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_DSP2_SHIFT                                                     (5U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_DSP2_MASK                                                      (0x00000020U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_DSP2_ENABLED                                                    (1U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_DSP2_DISABLED                                                   (0U)

#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_EVE1_SHIFT                                                     (6U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_EVE1_MASK                                                      (0x00000040U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_EVE1_ENABLED                                                    (1U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_EVE1_DISABLED                                                   (0U)

#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_EVE2_SHIFT                                                     (7U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_EVE2_MASK                                                      (0x00000080U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_EVE2_ENABLED                                                    (1U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_EVE2_DISABLED                                                   (0U)

#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_EVE3_SHIFT                                                     (8U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_EVE3_MASK                                                      (0x00000100U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_EVE3_ENABLED                                                    (1U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_EVE3_DISABLED                                                   (0U)

#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_EVE4_SHIFT                                                     (9U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_EVE4_MASK                                                      (0x00000200U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_EVE4_ENABLED                                                    (1U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_EVE4_DISABLED                                                   (0U)

#define PM_L3MAIN1_TPTC1_WKDEP_RESERVED_SHIFT                                                               (10U)
#define PM_L3MAIN1_TPTC1_WKDEP_RESERVED_MASK                                                                (0xfffffc00U)

#define PM_L3MAIN1_TPTC1_WKDEP_RESERVED1_SHIFT                                                              (3U)
#define PM_L3MAIN1_TPTC1_WKDEP_RESERVED1_MASK                                                               (0x00000008U)

#define RM_L3MAIN1_TPTC1_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                      (1U)
#define RM_L3MAIN1_TPTC1_CONTEXT_LOSTCONTEXT_RFF_MASK                                                       (0x00000002U)
#define RM_L3MAIN1_TPTC1_CONTEXT_LOSTCONTEXT_RFF_LOST                                                        (1U)
#define RM_L3MAIN1_TPTC1_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                  (0U)

#define RM_L3MAIN1_TPTC1_CONTEXT_RESERVED_SHIFT                                                             (0U)
#define RM_L3MAIN1_TPTC1_CONTEXT_RESERVED_MASK                                                              (0x00000001U)

#define RM_L3MAIN1_TPTC1_CONTEXT_LOSTMEM_TPTC_BANK_SHIFT                                                    (8U)
#define RM_L3MAIN1_TPTC1_CONTEXT_LOSTMEM_TPTC_BANK_MASK                                                     (0x00000100U)
#define RM_L3MAIN1_TPTC1_CONTEXT_LOSTMEM_TPTC_BANK_LOST                                                      (1U)
#define RM_L3MAIN1_TPTC1_CONTEXT_LOSTMEM_TPTC_BANK_MAINTAINED                                                (0U)

#define RM_L3MAIN1_TPTC1_CONTEXT_RESERVED1_SHIFT                                                            (2U)
#define RM_L3MAIN1_TPTC1_CONTEXT_RESERVED1_MASK                                                             (0x000000fcU)

#define RM_L3MAIN1_TPTC1_CONTEXT_RESERVED2_SHIFT                                                            (9U)
#define RM_L3MAIN1_TPTC1_CONTEXT_RESERVED2_MASK                                                             (0xfffffe00U)

#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_MPU_SHIFT                                                      (0U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_MPU_MASK                                                       (0x00000001U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_MPU_ENABLED                                                     (1U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_MPU_DISABLED                                                    (0U)

#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_DSP1_SHIFT                                                     (2U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_DSP1_MASK                                                      (0x00000004U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_DSP1_ENABLED                                                    (1U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_DSP1_DISABLED                                                   (0U)

#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_IPU2_SHIFT                                                     (1U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_IPU2_MASK                                                      (0x00000002U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_IPU2_ENABLED                                                    (1U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_IPU2_DISABLED                                                   (0U)

#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_IPU1_SHIFT                                                     (4U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_IPU1_MASK                                                      (0x00000010U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_IPU1_ENABLED                                                    (1U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_IPU1_DISABLED                                                   (0U)

#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_DSP2_SHIFT                                                     (5U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_DSP2_MASK                                                      (0x00000020U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_DSP2_ENABLED                                                    (1U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_DSP2_DISABLED                                                   (0U)

#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_EVE1_SHIFT                                                     (6U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_EVE1_MASK                                                      (0x00000040U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_EVE1_ENABLED                                                    (1U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_EVE1_DISABLED                                                   (0U)

#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_EVE2_SHIFT                                                     (7U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_EVE2_MASK                                                      (0x00000080U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_EVE2_ENABLED                                                    (1U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_EVE2_DISABLED                                                   (0U)

#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_EVE3_SHIFT                                                     (8U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_EVE3_MASK                                                      (0x00000100U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_EVE3_ENABLED                                                    (1U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_EVE3_DISABLED                                                   (0U)

#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_EVE4_SHIFT                                                     (9U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_EVE4_MASK                                                      (0x00000200U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_EVE4_ENABLED                                                    (1U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_EVE4_DISABLED                                                   (0U)

#define PM_L3MAIN1_TPTC2_WKDEP_RESERVED_SHIFT                                                               (10U)
#define PM_L3MAIN1_TPTC2_WKDEP_RESERVED_MASK                                                                (0xfffffc00U)

#define PM_L3MAIN1_TPTC2_WKDEP_RESERVED1_SHIFT                                                              (3U)
#define PM_L3MAIN1_TPTC2_WKDEP_RESERVED1_MASK                                                               (0x00000008U)

#define RM_L3MAIN1_TPTC2_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                      (1U)
#define RM_L3MAIN1_TPTC2_CONTEXT_LOSTCONTEXT_RFF_MASK                                                       (0x00000002U)
#define RM_L3MAIN1_TPTC2_CONTEXT_LOSTCONTEXT_RFF_LOST                                                        (1U)
#define RM_L3MAIN1_TPTC2_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                  (0U)

#define RM_L3MAIN1_TPTC2_CONTEXT_RESERVED_SHIFT                                                             (0U)
#define RM_L3MAIN1_TPTC2_CONTEXT_RESERVED_MASK                                                              (0x00000001U)

#define RM_L3MAIN1_TPTC2_CONTEXT_RESERVED1_SHIFT                                                            (2U)
#define RM_L3MAIN1_TPTC2_CONTEXT_RESERVED1_MASK                                                             (0x000000fcU)

#define RM_L3MAIN1_TPTC2_CONTEXT_LOSTMEM_TPTC_BANK_SHIFT                                                    (8U)
#define RM_L3MAIN1_TPTC2_CONTEXT_LOSTMEM_TPTC_BANK_MASK                                                     (0x00000100U)
#define RM_L3MAIN1_TPTC2_CONTEXT_LOSTMEM_TPTC_BANK_LOST                                                      (1U)
#define RM_L3MAIN1_TPTC2_CONTEXT_LOSTMEM_TPTC_BANK_MAINTAINED                                                (0U)

#define RM_L3MAIN1_TPTC2_CONTEXT_RESERVED2_SHIFT                                                            (9U)
#define RM_L3MAIN1_TPTC2_CONTEXT_RESERVED2_MASK                                                             (0xfffffe00U)

#define RM_L3MAIN1_VCP1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                       (0U)
#define RM_L3MAIN1_VCP1_CONTEXT_LOSTCONTEXT_DFF_MASK                                                        (0x00000001U)
#define RM_L3MAIN1_VCP1_CONTEXT_LOSTCONTEXT_DFF_LOST                                                         (1U)
#define RM_L3MAIN1_VCP1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                   (0U)

#define RM_L3MAIN1_VCP1_CONTEXT_LOSTMEM_VCP_BANK_SHIFT                                                      (8U)
#define RM_L3MAIN1_VCP1_CONTEXT_LOSTMEM_VCP_BANK_MASK                                                       (0x00000100U)
#define RM_L3MAIN1_VCP1_CONTEXT_LOSTMEM_VCP_BANK_LOST                                                        (1U)
#define RM_L3MAIN1_VCP1_CONTEXT_LOSTMEM_VCP_BANK_MAINTAINED                                                  (0U)

#define RM_L3MAIN1_VCP1_CONTEXT_RESERVED1_SHIFT                                                             (9U)
#define RM_L3MAIN1_VCP1_CONTEXT_RESERVED1_MASK                                                              (0xfffffe00U)

#define RM_L3MAIN1_VCP1_CONTEXT_RESERVED_SHIFT                                                              (1U)
#define RM_L3MAIN1_VCP1_CONTEXT_RESERVED_MASK                                                               (0x000000feU)

#define RM_L3MAIN1_VCP2_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                       (0U)
#define RM_L3MAIN1_VCP2_CONTEXT_LOSTCONTEXT_DFF_MASK                                                        (0x00000001U)
#define RM_L3MAIN1_VCP2_CONTEXT_LOSTCONTEXT_DFF_LOST                                                         (1U)
#define RM_L3MAIN1_VCP2_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                   (0U)

#define RM_L3MAIN1_VCP2_CONTEXT_LOSTMEM_VCP_BANK_SHIFT                                                      (8U)
#define RM_L3MAIN1_VCP2_CONTEXT_LOSTMEM_VCP_BANK_MASK                                                       (0x00000100U)
#define RM_L3MAIN1_VCP2_CONTEXT_LOSTMEM_VCP_BANK_LOST                                                        (1U)
#define RM_L3MAIN1_VCP2_CONTEXT_LOSTMEM_VCP_BANK_MAINTAINED                                                  (0U)

#define RM_L3MAIN1_VCP2_CONTEXT_RESERVED1_SHIFT                                                             (9U)
#define RM_L3MAIN1_VCP2_CONTEXT_RESERVED1_MASK                                                              (0xfffffe00U)

#define RM_L3MAIN1_VCP2_CONTEXT_RESERVED_SHIFT                                                              (1U)
#define RM_L3MAIN1_VCP2_CONTEXT_RESERVED_MASK                                                               (0x000000feU)

#define RM_IPU2_RSTCTRL_RST_CPU0_SHIFT                                                                      (0U)
#define RM_IPU2_RSTCTRL_RST_CPU0_MASK                                                                       (0x00000001U)
#define RM_IPU2_RSTCTRL_RST_CPU0_ASSERT                                                                      (1U)
#define RM_IPU2_RSTCTRL_RST_CPU0_CLEAR                                                                       (0U)

#define RM_IPU2_RSTCTRL_RST_CPU1_SHIFT                                                                      (1U)
#define RM_IPU2_RSTCTRL_RST_CPU1_MASK                                                                       (0x00000002U)
#define RM_IPU2_RSTCTRL_RST_CPU1_ASSERT                                                                      (1U)
#define RM_IPU2_RSTCTRL_RST_CPU1_CLEAR                                                                       (0U)

#define RM_IPU2_RSTCTRL_RST_IPU_SHIFT                                                                       (2U)
#define RM_IPU2_RSTCTRL_RST_IPU_MASK                                                                        (0x00000004U)
#define RM_IPU2_RSTCTRL_RST_IPU_ASSERT                                                                       (1U)
#define RM_IPU2_RSTCTRL_RST_IPU_CLEAR                                                                        (0U)

#define RM_IPU2_RSTCTRL_RESERVED_SHIFT                                                                      (3U)
#define RM_IPU2_RSTCTRL_RESERVED_MASK                                                                       (0xfffffff8U)

#define RM_IPU2_RSTST_RST_EMULATION_CPU0_SHIFT                                                              (3U)
#define RM_IPU2_RSTST_RST_EMULATION_CPU0_MASK                                                               (0x00000008U)
#define RM_IPU2_RSTST_RST_EMULATION_CPU0_RESET_YES                                                           (1U)
#define RM_IPU2_RSTST_RST_EMULATION_CPU0_RESET_NO                                                            (0U)

#define RM_IPU2_RSTST_RST_EMULATION_CPU1_SHIFT                                                              (4U)
#define RM_IPU2_RSTST_RST_EMULATION_CPU1_MASK                                                               (0x00000010U)
#define RM_IPU2_RSTST_RST_EMULATION_CPU1_RESET_YES                                                           (1U)
#define RM_IPU2_RSTST_RST_EMULATION_CPU1_RESET_NO                                                            (0U)

#define RM_IPU2_RSTST_RST_CPU0_SHIFT                                                                        (0U)
#define RM_IPU2_RSTST_RST_CPU0_MASK                                                                         (0x00000001U)
#define RM_IPU2_RSTST_RST_CPU0_RESET_YES                                                                     (1U)
#define RM_IPU2_RSTST_RST_CPU0_RESET_NO                                                                      (0U)

#define RM_IPU2_RSTST_RST_CPU1_SHIFT                                                                        (1U)
#define RM_IPU2_RSTST_RST_CPU1_MASK                                                                         (0x00000002U)
#define RM_IPU2_RSTST_RST_CPU1_RESET_YES                                                                     (1U)
#define RM_IPU2_RSTST_RST_CPU1_RESET_NO                                                                      (0U)

#define RM_IPU2_RSTST_RST_IPU_SHIFT                                                                         (2U)
#define RM_IPU2_RSTST_RST_IPU_MASK                                                                          (0x00000004U)
#define RM_IPU2_RSTST_RST_IPU_RESET_YES                                                                      (1U)
#define RM_IPU2_RSTST_RST_IPU_RESET_NO                                                                       (0U)

#define RM_IPU2_RSTST_RST_ICECRUSHER_CPU0_SHIFT                                                             (5U)
#define RM_IPU2_RSTST_RST_ICECRUSHER_CPU0_MASK                                                              (0x00000020U)
#define RM_IPU2_RSTST_RST_ICECRUSHER_CPU0_RESET_YES                                                          (1U)
#define RM_IPU2_RSTST_RST_ICECRUSHER_CPU0_RESET_NO                                                           (0U)

#define RM_IPU2_RSTST_RST_ICECRUSHER_CPU1_SHIFT                                                             (6U)
#define RM_IPU2_RSTST_RST_ICECRUSHER_CPU1_MASK                                                              (0x00000040U)
#define RM_IPU2_RSTST_RST_ICECRUSHER_CPU1_RESET_YES                                                          (1U)
#define RM_IPU2_RSTST_RST_ICECRUSHER_CPU1_RESET_NO                                                           (0U)

#define RM_IPU2_RSTST_RESERVED_SHIFT                                                                        (7U)
#define RM_IPU2_RSTST_RESERVED_MASK                                                                         (0xffffff80U)

#define RM_IPU2_IPU2_CONTEXT_RESERVED1_SHIFT                                                                (10U)
#define RM_IPU2_IPU2_CONTEXT_RESERVED1_MASK                                                                 (0xfffffc00U)

#define RM_IPU2_IPU2_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                          (0U)
#define RM_IPU2_IPU2_CONTEXT_LOSTCONTEXT_DFF_MASK                                                           (0x00000001U)
#define RM_IPU2_IPU2_CONTEXT_LOSTCONTEXT_DFF_LOST                                                            (1U)
#define RM_IPU2_IPU2_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                      (0U)

#define RM_IPU2_IPU2_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                          (1U)
#define RM_IPU2_IPU2_CONTEXT_LOSTCONTEXT_RFF_MASK                                                           (0x00000002U)
#define RM_IPU2_IPU2_CONTEXT_LOSTCONTEXT_RFF_LOST                                                            (1U)
#define RM_IPU2_IPU2_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                      (0U)

#define RM_IPU2_IPU2_CONTEXT_RESERVED_SHIFT                                                                 (2U)
#define RM_IPU2_IPU2_CONTEXT_RESERVED_MASK                                                                  (0x000000fcU)

#define RM_IPU2_IPU2_CONTEXT_LOSTMEM_IPU_UNICACHE_SHIFT                                                     (8U)
#define RM_IPU2_IPU2_CONTEXT_LOSTMEM_IPU_UNICACHE_MASK                                                      (0x00000100U)
#define RM_IPU2_IPU2_CONTEXT_LOSTMEM_IPU_UNICACHE_LOST                                                       (1U)
#define RM_IPU2_IPU2_CONTEXT_LOSTMEM_IPU_UNICACHE_MAINTAINED                                                 (0U)

#define RM_IPU2_IPU2_CONTEXT_LOSTMEM_IPU_L2RAM_SHIFT                                                        (9U)
#define RM_IPU2_IPU2_CONTEXT_LOSTMEM_IPU_L2RAM_MASK                                                         (0x00000200U)
#define RM_IPU2_IPU2_CONTEXT_LOSTMEM_IPU_L2RAM_LOST                                                          (1U)
#define RM_IPU2_IPU2_CONTEXT_LOSTMEM_IPU_L2RAM_MAINTAINED                                                    (0U)

#define RM_DMA_DMA_SYSTEM_CONTEXT_RESERVED1_SHIFT                                                           (9U)
#define RM_DMA_DMA_SYSTEM_CONTEXT_RESERVED1_MASK                                                            (0xfffffe00U)

#define RM_DMA_DMA_SYSTEM_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                     (1U)
#define RM_DMA_DMA_SYSTEM_CONTEXT_LOSTCONTEXT_RFF_MASK                                                      (0x00000002U)
#define RM_DMA_DMA_SYSTEM_CONTEXT_LOSTCONTEXT_RFF_LOST                                                       (1U)
#define RM_DMA_DMA_SYSTEM_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                 (0U)

#define RM_DMA_DMA_SYSTEM_CONTEXT_RESERVED_SHIFT                                                            (0U)
#define RM_DMA_DMA_SYSTEM_CONTEXT_RESERVED_MASK                                                             (0x00000001U)

#define RM_DMA_DMA_SYSTEM_CONTEXT_RESERVED2_SHIFT                                                           (2U)
#define RM_DMA_DMA_SYSTEM_CONTEXT_RESERVED2_MASK                                                            (0x000000fcU)

#define RM_DMA_DMA_SYSTEM_CONTEXT_LOSTMEM_CORE_OTHER_BANK_SHIFT                                             (8U)
#define RM_DMA_DMA_SYSTEM_CONTEXT_LOSTMEM_CORE_OTHER_BANK_MASK                                              (0x00000100U)
#define RM_DMA_DMA_SYSTEM_CONTEXT_LOSTMEM_CORE_OTHER_BANK_LOST                                               (1U)
#define RM_DMA_DMA_SYSTEM_CONTEXT_LOSTMEM_CORE_OTHER_BANK_MAINTAINED                                         (0U)

#define RM_EMIF_DMM_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                           (0U)
#define RM_EMIF_DMM_CONTEXT_LOSTCONTEXT_DFF_MASK                                                            (0x00000001U)
#define RM_EMIF_DMM_CONTEXT_LOSTCONTEXT_DFF_LOST                                                             (1U)
#define RM_EMIF_DMM_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                       (0U)

#define RM_EMIF_DMM_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                           (1U)
#define RM_EMIF_DMM_CONTEXT_LOSTCONTEXT_RFF_MASK                                                            (0x00000002U)
#define RM_EMIF_DMM_CONTEXT_LOSTCONTEXT_RFF_LOST                                                             (1U)
#define RM_EMIF_DMM_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                       (0U)

#define RM_EMIF_DMM_CONTEXT_RESERVED_SHIFT                                                                  (2U)
#define RM_EMIF_DMM_CONTEXT_RESERVED_MASK                                                                   (0xfffffffcU)

#define RM_EMIF_EMIF_OCP_FW_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                   (0U)
#define RM_EMIF_EMIF_OCP_FW_CONTEXT_LOSTCONTEXT_DFF_MASK                                                    (0x00000001U)
#define RM_EMIF_EMIF_OCP_FW_CONTEXT_LOSTCONTEXT_DFF_LOST                                                     (1U)
#define RM_EMIF_EMIF_OCP_FW_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                               (0U)

#define RM_EMIF_EMIF_OCP_FW_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                   (1U)
#define RM_EMIF_EMIF_OCP_FW_CONTEXT_LOSTCONTEXT_RFF_MASK                                                    (0x00000002U)
#define RM_EMIF_EMIF_OCP_FW_CONTEXT_LOSTCONTEXT_RFF_LOST                                                     (1U)
#define RM_EMIF_EMIF_OCP_FW_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                               (0U)

#define RM_EMIF_EMIF_OCP_FW_CONTEXT_RESERVED_SHIFT                                                          (2U)
#define RM_EMIF_EMIF_OCP_FW_CONTEXT_RESERVED_MASK                                                           (0xfffffffcU)

#define RM_EMIF_EMIF1_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                         (1U)
#define RM_EMIF_EMIF1_CONTEXT_LOSTCONTEXT_RFF_MASK                                                          (0x00000002U)
#define RM_EMIF_EMIF1_CONTEXT_LOSTCONTEXT_RFF_LOST                                                           (1U)
#define RM_EMIF_EMIF1_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                     (0U)

#define RM_EMIF_EMIF1_CONTEXT_RESERVED1_SHIFT                                                               (2U)
#define RM_EMIF_EMIF1_CONTEXT_RESERVED1_MASK                                                                (0xfffffffcU)

#define RM_EMIF_EMIF1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                         (0U)
#define RM_EMIF_EMIF1_CONTEXT_LOSTCONTEXT_DFF_MASK                                                          (0x00000001U)
#define RM_EMIF_EMIF1_CONTEXT_LOSTCONTEXT_DFF_LOST                                                           (1U)
#define RM_EMIF_EMIF1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                     (0U)

#define RM_EMIF_EMIF2_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                         (1U)
#define RM_EMIF_EMIF2_CONTEXT_LOSTCONTEXT_RFF_MASK                                                          (0x00000002U)
#define RM_EMIF_EMIF2_CONTEXT_LOSTCONTEXT_RFF_LOST                                                           (1U)
#define RM_EMIF_EMIF2_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                     (0U)

#define RM_EMIF_EMIF2_CONTEXT_RESERVED1_SHIFT                                                               (2U)
#define RM_EMIF_EMIF2_CONTEXT_RESERVED1_MASK                                                                (0xfffffffcU)

#define RM_EMIF_EMIF2_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                         (0U)
#define RM_EMIF_EMIF2_CONTEXT_LOSTCONTEXT_DFF_MASK                                                          (0x00000001U)
#define RM_EMIF_EMIF2_CONTEXT_LOSTCONTEXT_DFF_LOST                                                           (1U)
#define RM_EMIF_EMIF2_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                     (0U)

#define RM_EMIF_EMIF_DLL_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                      (0U)
#define RM_EMIF_EMIF_DLL_CONTEXT_LOSTCONTEXT_DFF_MASK                                                       (0x00000001U)
#define RM_EMIF_EMIF_DLL_CONTEXT_LOSTCONTEXT_DFF_LOST                                                        (1U)
#define RM_EMIF_EMIF_DLL_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                  (0U)

#define RM_EMIF_EMIF_DLL_CONTEXT_RESERVED_SHIFT                                                             (1U)
#define RM_EMIF_EMIF_DLL_CONTEXT_RESERVED_MASK                                                              (0xfffffffeU)

#define RM_ATL_ATL_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                            (0U)
#define RM_ATL_ATL_CONTEXT_LOSTCONTEXT_DFF_MASK                                                             (0x00000001U)
#define RM_ATL_ATL_CONTEXT_LOSTCONTEXT_DFF_LOST                                                              (1U)
#define RM_ATL_ATL_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                        (0U)

#define RM_ATL_ATL_CONTEXT_LOSTMEM_ATL_BANK_SHIFT                                                           (8U)
#define RM_ATL_ATL_CONTEXT_LOSTMEM_ATL_BANK_MASK                                                            (0x00000100U)
#define RM_ATL_ATL_CONTEXT_LOSTMEM_ATL_BANK_LOST                                                             (1U)
#define RM_ATL_ATL_CONTEXT_LOSTMEM_ATL_BANK_MAINTAINED                                                       (0U)

#define RM_ATL_ATL_CONTEXT_RESERVED1_SHIFT                                                                  (9U)
#define RM_ATL_ATL_CONTEXT_RESERVED1_MASK                                                                   (0xfffffe00U)

#define RM_ATL_ATL_CONTEXT_RESERVED_SHIFT                                                                   (1U)
#define RM_ATL_ATL_CONTEXT_RESERVED_MASK                                                                    (0x000000feU)

#define RM_L4CFG_L4_CFG_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                       (0U)
#define RM_L4CFG_L4_CFG_CONTEXT_LOSTCONTEXT_DFF_MASK                                                        (0x00000001U)
#define RM_L4CFG_L4_CFG_CONTEXT_LOSTCONTEXT_DFF_LOST                                                         (1U)
#define RM_L4CFG_L4_CFG_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                   (0U)

#define RM_L4CFG_L4_CFG_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                       (1U)
#define RM_L4CFG_L4_CFG_CONTEXT_LOSTCONTEXT_RFF_MASK                                                        (0x00000002U)
#define RM_L4CFG_L4_CFG_CONTEXT_LOSTCONTEXT_RFF_LOST                                                         (1U)
#define RM_L4CFG_L4_CFG_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                   (0U)

#define RM_L4CFG_L4_CFG_CONTEXT_RESERVED_SHIFT                                                              (2U)
#define RM_L4CFG_L4_CFG_CONTEXT_RESERVED_MASK                                                               (0xfffffffcU)

#define RM_L4CFG_SPINLOCK_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                     (1U)
#define RM_L4CFG_SPINLOCK_CONTEXT_LOSTCONTEXT_RFF_MASK                                                      (0x00000002U)
#define RM_L4CFG_SPINLOCK_CONTEXT_LOSTCONTEXT_RFF_LOST                                                       (1U)
#define RM_L4CFG_SPINLOCK_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                 (0U)

#define RM_L4CFG_SPINLOCK_CONTEXT_RESERVED_SHIFT                                                            (0U)
#define RM_L4CFG_SPINLOCK_CONTEXT_RESERVED_MASK                                                             (0x00000001U)

#define RM_L4CFG_SPINLOCK_CONTEXT_RESERVED1_SHIFT                                                           (2U)
#define RM_L4CFG_SPINLOCK_CONTEXT_RESERVED1_MASK                                                            (0xfffffffcU)

#define RM_L4CFG_MAILBOX1_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                     (1U)
#define RM_L4CFG_MAILBOX1_CONTEXT_LOSTCONTEXT_RFF_MASK                                                      (0x00000002U)
#define RM_L4CFG_MAILBOX1_CONTEXT_LOSTCONTEXT_RFF_LOST                                                       (1U)
#define RM_L4CFG_MAILBOX1_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                 (0U)

#define RM_L4CFG_MAILBOX1_CONTEXT_RESERVED_SHIFT                                                            (0U)
#define RM_L4CFG_MAILBOX1_CONTEXT_RESERVED_MASK                                                             (0x00000001U)

#define RM_L4CFG_MAILBOX1_CONTEXT_RESERVED1_SHIFT                                                           (2U)
#define RM_L4CFG_MAILBOX1_CONTEXT_RESERVED1_MASK                                                            (0xfffffffcU)

#define RM_L4CFG_SAR_ROM_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                      (0U)
#define RM_L4CFG_SAR_ROM_CONTEXT_LOSTCONTEXT_DFF_MASK                                                       (0x00000001U)
#define RM_L4CFG_SAR_ROM_CONTEXT_LOSTCONTEXT_DFF_LOST                                                        (1U)
#define RM_L4CFG_SAR_ROM_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                  (0U)

#define RM_L4CFG_SAR_ROM_CONTEXT_RESERVED_SHIFT                                                             (1U)
#define RM_L4CFG_SAR_ROM_CONTEXT_RESERVED_MASK                                                              (0xfffffffeU)

#define RM_L4CFG_OCP2SCP2_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                     (0U)
#define RM_L4CFG_OCP2SCP2_CONTEXT_LOSTCONTEXT_DFF_MASK                                                      (0x00000001U)
#define RM_L4CFG_OCP2SCP2_CONTEXT_LOSTCONTEXT_DFF_LOST                                                       (1U)
#define RM_L4CFG_OCP2SCP2_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                 (0U)

#define RM_L4CFG_OCP2SCP2_CONTEXT_RESERVED_SHIFT                                                            (1U)
#define RM_L4CFG_OCP2SCP2_CONTEXT_RESERVED_MASK                                                             (0xfffffffeU)

#define RM_L4CFG_MAILBOX2_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                     (1U)
#define RM_L4CFG_MAILBOX2_CONTEXT_LOSTCONTEXT_RFF_MASK                                                      (0x00000002U)
#define RM_L4CFG_MAILBOX2_CONTEXT_LOSTCONTEXT_RFF_LOST                                                       (1U)
#define RM_L4CFG_MAILBOX2_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                 (0U)

#define RM_L4CFG_MAILBOX2_CONTEXT_RESERVED_SHIFT                                                            (0U)
#define RM_L4CFG_MAILBOX2_CONTEXT_RESERVED_MASK                                                             (0x00000001U)

#define RM_L4CFG_MAILBOX2_CONTEXT_RESERVED1_SHIFT                                                           (2U)
#define RM_L4CFG_MAILBOX2_CONTEXT_RESERVED1_MASK                                                            (0xfffffffcU)

#define RM_L4CFG_MAILBOX3_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                     (1U)
#define RM_L4CFG_MAILBOX3_CONTEXT_LOSTCONTEXT_RFF_MASK                                                      (0x00000002U)
#define RM_L4CFG_MAILBOX3_CONTEXT_LOSTCONTEXT_RFF_LOST                                                       (1U)
#define RM_L4CFG_MAILBOX3_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                 (0U)

#define RM_L4CFG_MAILBOX3_CONTEXT_RESERVED_SHIFT                                                            (0U)
#define RM_L4CFG_MAILBOX3_CONTEXT_RESERVED_MASK                                                             (0x00000001U)

#define RM_L4CFG_MAILBOX3_CONTEXT_RESERVED1_SHIFT                                                           (2U)
#define RM_L4CFG_MAILBOX3_CONTEXT_RESERVED1_MASK                                                            (0xfffffffcU)

#define RM_L4CFG_MAILBOX4_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                     (1U)
#define RM_L4CFG_MAILBOX4_CONTEXT_LOSTCONTEXT_RFF_MASK                                                      (0x00000002U)
#define RM_L4CFG_MAILBOX4_CONTEXT_LOSTCONTEXT_RFF_LOST                                                       (1U)
#define RM_L4CFG_MAILBOX4_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                 (0U)

#define RM_L4CFG_MAILBOX4_CONTEXT_RESERVED_SHIFT                                                            (0U)
#define RM_L4CFG_MAILBOX4_CONTEXT_RESERVED_MASK                                                             (0x00000001U)

#define RM_L4CFG_MAILBOX4_CONTEXT_RESERVED1_SHIFT                                                           (2U)
#define RM_L4CFG_MAILBOX4_CONTEXT_RESERVED1_MASK                                                            (0xfffffffcU)

#define RM_L4CFG_MAILBOX5_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                     (1U)
#define RM_L4CFG_MAILBOX5_CONTEXT_LOSTCONTEXT_RFF_MASK                                                      (0x00000002U)
#define RM_L4CFG_MAILBOX5_CONTEXT_LOSTCONTEXT_RFF_LOST                                                       (1U)
#define RM_L4CFG_MAILBOX5_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                 (0U)

#define RM_L4CFG_MAILBOX5_CONTEXT_RESERVED_SHIFT                                                            (0U)
#define RM_L4CFG_MAILBOX5_CONTEXT_RESERVED_MASK                                                             (0x00000001U)

#define RM_L4CFG_MAILBOX5_CONTEXT_RESERVED1_SHIFT                                                           (2U)
#define RM_L4CFG_MAILBOX5_CONTEXT_RESERVED1_MASK                                                            (0xfffffffcU)

#define RM_L4CFG_MAILBOX6_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                     (1U)
#define RM_L4CFG_MAILBOX6_CONTEXT_LOSTCONTEXT_RFF_MASK                                                      (0x00000002U)
#define RM_L4CFG_MAILBOX6_CONTEXT_LOSTCONTEXT_RFF_LOST                                                       (1U)
#define RM_L4CFG_MAILBOX6_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                 (0U)

#define RM_L4CFG_MAILBOX6_CONTEXT_RESERVED_SHIFT                                                            (0U)
#define RM_L4CFG_MAILBOX6_CONTEXT_RESERVED_MASK                                                             (0x00000001U)

#define RM_L4CFG_MAILBOX6_CONTEXT_RESERVED1_SHIFT                                                           (2U)
#define RM_L4CFG_MAILBOX6_CONTEXT_RESERVED1_MASK                                                            (0xfffffffcU)

#define RM_L4CFG_MAILBOX7_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                     (1U)
#define RM_L4CFG_MAILBOX7_CONTEXT_LOSTCONTEXT_RFF_MASK                                                      (0x00000002U)
#define RM_L4CFG_MAILBOX7_CONTEXT_LOSTCONTEXT_RFF_LOST                                                       (1U)
#define RM_L4CFG_MAILBOX7_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                 (0U)

#define RM_L4CFG_MAILBOX7_CONTEXT_RESERVED_SHIFT                                                            (0U)
#define RM_L4CFG_MAILBOX7_CONTEXT_RESERVED_MASK                                                             (0x00000001U)

#define RM_L4CFG_MAILBOX7_CONTEXT_RESERVED1_SHIFT                                                           (2U)
#define RM_L4CFG_MAILBOX7_CONTEXT_RESERVED1_MASK                                                            (0xfffffffcU)

#define RM_L4CFG_MAILBOX8_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                     (1U)
#define RM_L4CFG_MAILBOX8_CONTEXT_LOSTCONTEXT_RFF_MASK                                                      (0x00000002U)
#define RM_L4CFG_MAILBOX8_CONTEXT_LOSTCONTEXT_RFF_LOST                                                       (1U)
#define RM_L4CFG_MAILBOX8_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                 (0U)

#define RM_L4CFG_MAILBOX8_CONTEXT_RESERVED_SHIFT                                                            (0U)
#define RM_L4CFG_MAILBOX8_CONTEXT_RESERVED_MASK                                                             (0x00000001U)

#define RM_L4CFG_MAILBOX8_CONTEXT_RESERVED1_SHIFT                                                           (2U)
#define RM_L4CFG_MAILBOX8_CONTEXT_RESERVED1_MASK                                                            (0xfffffffcU)

#define RM_L4CFG_MAILBOX9_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                     (1U)
#define RM_L4CFG_MAILBOX9_CONTEXT_LOSTCONTEXT_RFF_MASK                                                      (0x00000002U)
#define RM_L4CFG_MAILBOX9_CONTEXT_LOSTCONTEXT_RFF_LOST                                                       (1U)
#define RM_L4CFG_MAILBOX9_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                 (0U)

#define RM_L4CFG_MAILBOX9_CONTEXT_RESERVED_SHIFT                                                            (0U)
#define RM_L4CFG_MAILBOX9_CONTEXT_RESERVED_MASK                                                             (0x00000001U)

#define RM_L4CFG_MAILBOX9_CONTEXT_RESERVED1_SHIFT                                                           (2U)
#define RM_L4CFG_MAILBOX9_CONTEXT_RESERVED1_MASK                                                            (0xfffffffcU)

#define RM_L4CFG_MAILBOX10_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                    (1U)
#define RM_L4CFG_MAILBOX10_CONTEXT_LOSTCONTEXT_RFF_MASK                                                     (0x00000002U)
#define RM_L4CFG_MAILBOX10_CONTEXT_LOSTCONTEXT_RFF_LOST                                                      (1U)
#define RM_L4CFG_MAILBOX10_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                (0U)

#define RM_L4CFG_MAILBOX10_CONTEXT_RESERVED_SHIFT                                                           (0U)
#define RM_L4CFG_MAILBOX10_CONTEXT_RESERVED_MASK                                                            (0x00000001U)

#define RM_L4CFG_MAILBOX10_CONTEXT_RESERVED1_SHIFT                                                          (2U)
#define RM_L4CFG_MAILBOX10_CONTEXT_RESERVED1_MASK                                                           (0xfffffffcU)

#define RM_L4CFG_MAILBOX11_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                    (1U)
#define RM_L4CFG_MAILBOX11_CONTEXT_LOSTCONTEXT_RFF_MASK                                                     (0x00000002U)
#define RM_L4CFG_MAILBOX11_CONTEXT_LOSTCONTEXT_RFF_LOST                                                      (1U)
#define RM_L4CFG_MAILBOX11_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                (0U)

#define RM_L4CFG_MAILBOX11_CONTEXT_RESERVED_SHIFT                                                           (0U)
#define RM_L4CFG_MAILBOX11_CONTEXT_RESERVED_MASK                                                            (0x00000001U)

#define RM_L4CFG_MAILBOX11_CONTEXT_RESERVED1_SHIFT                                                          (2U)
#define RM_L4CFG_MAILBOX11_CONTEXT_RESERVED1_MASK                                                           (0xfffffffcU)

#define RM_L4CFG_MAILBOX12_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                    (1U)
#define RM_L4CFG_MAILBOX12_CONTEXT_LOSTCONTEXT_RFF_MASK                                                     (0x00000002U)
#define RM_L4CFG_MAILBOX12_CONTEXT_LOSTCONTEXT_RFF_LOST                                                      (1U)
#define RM_L4CFG_MAILBOX12_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                (0U)

#define RM_L4CFG_MAILBOX12_CONTEXT_RESERVED_SHIFT                                                           (0U)
#define RM_L4CFG_MAILBOX12_CONTEXT_RESERVED_MASK                                                            (0x00000001U)

#define RM_L4CFG_MAILBOX12_CONTEXT_RESERVED1_SHIFT                                                          (2U)
#define RM_L4CFG_MAILBOX12_CONTEXT_RESERVED1_MASK                                                           (0xfffffffcU)

#define RM_L4CFG_MAILBOX13_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                    (1U)
#define RM_L4CFG_MAILBOX13_CONTEXT_LOSTCONTEXT_RFF_MASK                                                     (0x00000002U)
#define RM_L4CFG_MAILBOX13_CONTEXT_LOSTCONTEXT_RFF_LOST                                                      (1U)
#define RM_L4CFG_MAILBOX13_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                (0U)

#define RM_L4CFG_MAILBOX13_CONTEXT_RESERVED_SHIFT                                                           (0U)
#define RM_L4CFG_MAILBOX13_CONTEXT_RESERVED_MASK                                                            (0x00000001U)

#define RM_L4CFG_MAILBOX13_CONTEXT_RESERVED1_SHIFT                                                          (2U)
#define RM_L4CFG_MAILBOX13_CONTEXT_RESERVED1_MASK                                                           (0xfffffffcU)

#define RM_L4CFG_SPARE_SMARTREFLEX_RTC_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                        (0U)
#define RM_L4CFG_SPARE_SMARTREFLEX_RTC_CONTEXT_LOSTCONTEXT_DFF_MASK                                         (0x00000001U)
#define RM_L4CFG_SPARE_SMARTREFLEX_RTC_CONTEXT_LOSTCONTEXT_DFF_LOST                                          (1U)
#define RM_L4CFG_SPARE_SMARTREFLEX_RTC_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                    (0U)

#define RM_L4CFG_SPARE_SMARTREFLEX_RTC_CONTEXT_RESERVED_SHIFT                                               (1U)
#define RM_L4CFG_SPARE_SMARTREFLEX_RTC_CONTEXT_RESERVED_MASK                                                (0xfffffffeU)

#define RM_L4CFG_SPARE_SMARTREFLEX_SDRAM_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                      (0U)
#define RM_L4CFG_SPARE_SMARTREFLEX_SDRAM_CONTEXT_LOSTCONTEXT_DFF_MASK                                       (0x00000001U)
#define RM_L4CFG_SPARE_SMARTREFLEX_SDRAM_CONTEXT_LOSTCONTEXT_DFF_LOST                                        (1U)
#define RM_L4CFG_SPARE_SMARTREFLEX_SDRAM_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                  (0U)

#define RM_L4CFG_SPARE_SMARTREFLEX_SDRAM_CONTEXT_RESERVED_SHIFT                                             (1U)
#define RM_L4CFG_SPARE_SMARTREFLEX_SDRAM_CONTEXT_RESERVED_MASK                                              (0xfffffffeU)

#define RM_L4CFG_SPARE_SMARTREFLEX_WKUP_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                       (0U)
#define RM_L4CFG_SPARE_SMARTREFLEX_WKUP_CONTEXT_LOSTCONTEXT_DFF_MASK                                        (0x00000001U)
#define RM_L4CFG_SPARE_SMARTREFLEX_WKUP_CONTEXT_LOSTCONTEXT_DFF_LOST                                         (1U)
#define RM_L4CFG_SPARE_SMARTREFLEX_WKUP_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                   (0U)

#define RM_L4CFG_SPARE_SMARTREFLEX_WKUP_CONTEXT_RESERVED_SHIFT                                              (1U)
#define RM_L4CFG_SPARE_SMARTREFLEX_WKUP_CONTEXT_RESERVED_MASK                                               (0xfffffffeU)

#define RM_L4CFG_IO_DELAY_BLOCK_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                               (0U)
#define RM_L4CFG_IO_DELAY_BLOCK_CONTEXT_LOSTCONTEXT_DFF_MASK                                                (0x00000001U)
#define RM_L4CFG_IO_DELAY_BLOCK_CONTEXT_LOSTCONTEXT_DFF_LOST                                                 (1U)
#define RM_L4CFG_IO_DELAY_BLOCK_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                           (0U)

#define RM_L4CFG_IO_DELAY_BLOCK_CONTEXT_RESERVED_SHIFT                                                      (1U)
#define RM_L4CFG_IO_DELAY_BLOCK_CONTEXT_RESERVED_MASK                                                       (0xfffffffeU)

#define RM_L3INSTR_L3_MAIN_2_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                  (0U)
#define RM_L3INSTR_L3_MAIN_2_CONTEXT_LOSTCONTEXT_DFF_MASK                                                   (0x00000001U)
#define RM_L3INSTR_L3_MAIN_2_CONTEXT_LOSTCONTEXT_DFF_LOST                                                    (1U)
#define RM_L3INSTR_L3_MAIN_2_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                              (0U)

#define RM_L3INSTR_L3_MAIN_2_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                  (1U)
#define RM_L3INSTR_L3_MAIN_2_CONTEXT_LOSTCONTEXT_RFF_MASK                                                   (0x00000002U)
#define RM_L3INSTR_L3_MAIN_2_CONTEXT_LOSTCONTEXT_RFF_LOST                                                    (1U)
#define RM_L3INSTR_L3_MAIN_2_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                              (0U)

#define RM_L3INSTR_L3_MAIN_2_CONTEXT_RESERVED_SHIFT                                                         (2U)
#define RM_L3INSTR_L3_MAIN_2_CONTEXT_RESERVED_MASK                                                          (0xfffffffcU)

#define RM_L3INSTR_L3_INSTR_CONTEXT_RESERVED_SHIFT                                                          (1U)
#define RM_L3INSTR_L3_INSTR_CONTEXT_RESERVED_MASK                                                           (0xfffffffeU)

#define RM_L3INSTR_L3_INSTR_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                   (0U)
#define RM_L3INSTR_L3_INSTR_CONTEXT_LOSTCONTEXT_DFF_MASK                                                    (0x00000001U)
#define RM_L3INSTR_L3_INSTR_CONTEXT_LOSTCONTEXT_DFF_LOST                                                     (1U)
#define RM_L3INSTR_L3_INSTR_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                               (0U)

#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                 (1U)
#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_LOSTCONTEXT_RFF_MASK                                                  (0x00000002U)
#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_LOSTCONTEXT_RFF_LOST                                                   (1U)
#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                             (0U)

#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                 (0U)
#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_LOSTCONTEXT_DFF_MASK                                                  (0x00000001U)
#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_LOSTCONTEXT_DFF_LOST                                                   (1U)
#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                             (0U)

#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_LOSTMEM_CORE_NRET_BANK_SHIFT                                          (8U)
#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_LOSTMEM_CORE_NRET_BANK_MASK                                           (0x00000100U)
#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_LOSTMEM_CORE_NRET_BANK_LOST                                            (1U)
#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_LOSTMEM_CORE_NRET_BANK_MAINTAINED                                      (0U)

#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_RESERVED_SHIFT                                                        (2U)
#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_RESERVED_MASK                                                         (0x000000fcU)

#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_RESERVED1_SHIFT                                                       (9U)
#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_RESERVED1_MASK                                                        (0xfffffe00U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_CORE_PRM_H_ */