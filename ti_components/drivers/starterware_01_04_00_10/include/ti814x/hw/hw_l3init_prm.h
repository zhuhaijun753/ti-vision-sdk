/******************************************************************************
*
* hw_l3init_prm.h - register-level header file for PRCM
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
#ifndef HW_L3INIT_PRM_H_
#define HW_L3INIT_PRM_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define PM_L3INIT_PWRSTCTRL                                                                                 (0x0U)
#define PM_L3INIT_PWRSTST                                                                                   (0x4U)
#define RM_PCIESS_RSTCTRL                                                                                   (0x10U)
#define RM_PCIESS_RSTST                                                                                     (0x14U)
#define PM_L3INIT_MMC1_WKDEP                                                                                (0x28U)
#define RM_L3INIT_MMC1_CONTEXT                                                                              (0x2cU)
#define PM_L3INIT_MMC2_WKDEP                                                                                (0x30U)
#define RM_L3INIT_MMC2_CONTEXT                                                                              (0x34U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP                                                                         (0x40U)
#define RM_L3INIT_USB_OTG_SS2_CONTEXT                                                                       (0x44U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP                                                                         (0x48U)
#define RM_L3INIT_USB_OTG_SS3_CONTEXT                                                                       (0x4cU)
#define PM_L3INIT_USB_OTG_SS4_WKDEP                                                                         (0x50U)
#define RM_L3INIT_USB_OTG_SS4_CONTEXT                                                                       (0x54U)
#define RM_L3INIT_MLB_SS_CONTEXT                                                                            (0x5cU)
#define RM_L3INIT_IEEE1500_2_OCP_CONTEXT                                                                    (0x7cU)
#define PM_L3INIT_SATA_WKDEP                                                                                (0x88U)
#define RM_L3INIT_SATA_CONTEXT                                                                              (0x8cU)
#define PM_PCIE_PCIESS1_WKDEP                                                                               (0xb0U)
#define RM_PCIE_PCIESS1_CONTEXT                                                                             (0xb4U)
#define PM_PCIE_PCIESS2_WKDEP                                                                               (0xb8U)
#define RM_PCIE_PCIESS2_CONTEXT                                                                             (0xbcU)
#define RM_GMAC_GMAC_CONTEXT                                                                                (0xd4U)
#define RM_L3INIT_OCP2SCP1_CONTEXT                                                                          (0xe4U)
#define RM_L3INIT_OCP2SCP3_CONTEXT                                                                          (0xecU)
#define PM_L3INIT_USB_OTG_SS1_WKDEP                                                                         (0xf0U)
#define RM_L3INIT_USB_OTG_SS1_CONTEXT                                                                       (0xf4U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define PM_L3INIT_PWRSTCTRL_L3INIT_BANK1_RETSTATE_SHIFT                                                     (8U)
#define PM_L3INIT_PWRSTCTRL_L3INIT_BANK1_RETSTATE_MASK                                                      (0x00000100U)
#define PM_L3INIT_PWRSTCTRL_L3INIT_BANK1_RETSTATE_MEM_OFF                                                    (0U)

#define PM_L3INIT_PWRSTCTRL_L3INIT_BANK1_ONSTATE_SHIFT                                                      (14U)
#define PM_L3INIT_PWRSTCTRL_L3INIT_BANK1_ONSTATE_MASK                                                       (0x0000c000U)
#define PM_L3INIT_PWRSTCTRL_L3INIT_BANK1_ONSTATE_MEM_ON                                                      (3U)

#define PM_L3INIT_PWRSTCTRL_POWERSTATE_SHIFT                                                                (0U)
#define PM_L3INIT_PWRSTCTRL_POWERSTATE_MASK                                                                 (0x00000003U)
#define PM_L3INIT_PWRSTCTRL_POWERSTATE_OFF                                                                   (0U)
#define PM_L3INIT_PWRSTCTRL_POWERSTATE_INACT                                                                 (2U)
#define PM_L3INIT_PWRSTCTRL_POWERSTATE_RET                                                                   (1U)
#define PM_L3INIT_PWRSTCTRL_POWERSTATE_ON                                                                    (3U)

#define PM_L3INIT_PWRSTCTRL_LOGICRETSTATE_SHIFT                                                             (2U)
#define PM_L3INIT_PWRSTCTRL_LOGICRETSTATE_MASK                                                              (0x00000004U)
#define PM_L3INIT_PWRSTCTRL_LOGICRETSTATE_LOGIC_RET                                                          (1U)
#define PM_L3INIT_PWRSTCTRL_LOGICRETSTATE_LOGIC_OFF                                                          (0U)

#define PM_L3INIT_PWRSTCTRL_LOWPOWERSTATECHANGE_SHIFT                                                       (4U)
#define PM_L3INIT_PWRSTCTRL_LOWPOWERSTATECHANGE_MASK                                                        (0x00000010U)
#define PM_L3INIT_PWRSTCTRL_LOWPOWERSTATECHANGE_EN                                                           (1U)
#define PM_L3INIT_PWRSTCTRL_LOWPOWERSTATECHANGE_DIS                                                          (0U)

#define PM_L3INIT_PWRSTCTRL_RESERVED_SHIFT                                                                  (3U)
#define PM_L3INIT_PWRSTCTRL_RESERVED_MASK                                                                   (0x00000008U)

#define PM_L3INIT_PWRSTCTRL_RESERVED3_SHIFT                                                                 (5U)
#define PM_L3INIT_PWRSTCTRL_RESERVED3_MASK                                                                  (0x000000e0U)

#define PM_L3INIT_PWRSTCTRL_L3INIT_BANK2_RETSTATE_SHIFT                                                     (9U)
#define PM_L3INIT_PWRSTCTRL_L3INIT_BANK2_RETSTATE_MASK                                                      (0x00000200U)
#define PM_L3INIT_PWRSTCTRL_L3INIT_BANK2_RETSTATE_MEM_RET                                                    (1U)

#define PM_L3INIT_PWRSTCTRL_L3INIT_BANK2_ONSTATE_SHIFT                                                      (16U)
#define PM_L3INIT_PWRSTCTRL_L3INIT_BANK2_ONSTATE_MASK                                                       (0x00030000U)
#define PM_L3INIT_PWRSTCTRL_L3INIT_BANK2_ONSTATE_MEM_ON                                                      (3U)

#define PM_L3INIT_PWRSTCTRL_GMAC_BANK_RETSTATE_SHIFT                                                        (10U)
#define PM_L3INIT_PWRSTCTRL_GMAC_BANK_RETSTATE_MASK                                                         (0x00000400U)
#define PM_L3INIT_PWRSTCTRL_GMAC_BANK_RETSTATE_MEM_RET                                                       (1U)

#define PM_L3INIT_PWRSTCTRL_GMAC_BANK_ONSTATE_SHIFT                                                         (18U)
#define PM_L3INIT_PWRSTCTRL_GMAC_BANK_ONSTATE_MASK                                                          (0x000c0000U)
#define PM_L3INIT_PWRSTCTRL_GMAC_BANK_ONSTATE_MEM_ON                                                         (3U)

#define PM_L3INIT_PWRSTCTRL_RESERVED1_SHIFT                                                                 (11U)
#define PM_L3INIT_PWRSTCTRL_RESERVED1_MASK                                                                  (0x00003800U)

#define PM_L3INIT_PWRSTCTRL_RESERVED2_SHIFT                                                                 (20U)
#define PM_L3INIT_PWRSTCTRL_RESERVED2_MASK                                                                  (0xfff00000U)

#define PM_L3INIT_PWRSTST_POWERSTATEST_SHIFT                                                                (0U)
#define PM_L3INIT_PWRSTST_POWERSTATEST_MASK                                                                 (0x00000003U)
#define PM_L3INIT_PWRSTST_POWERSTATEST_ON                                                                    (3U)
#define PM_L3INIT_PWRSTST_POWERSTATEST_OFF                                                                   (0U)
#define PM_L3INIT_PWRSTST_POWERSTATEST_RET                                                                   (1U)
#define PM_L3INIT_PWRSTST_POWERSTATEST_INACTIVE                                                              (2U)

#define PM_L3INIT_PWRSTST_INTRANSITION_SHIFT                                                                (20U)
#define PM_L3INIT_PWRSTST_INTRANSITION_MASK                                                                 (0x00100000U)
#define PM_L3INIT_PWRSTST_INTRANSITION_NO                                                                    (0U)
#define PM_L3INIT_PWRSTST_INTRANSITION_ONGOING                                                               (1U)

#define PM_L3INIT_PWRSTST_LOGICSTATEST_SHIFT                                                                (2U)
#define PM_L3INIT_PWRSTST_LOGICSTATEST_MASK                                                                 (0x00000004U)
#define PM_L3INIT_PWRSTST_LOGICSTATEST_ON                                                                    (1U)
#define PM_L3INIT_PWRSTST_LOGICSTATEST_OFF                                                                   (0U)

#define PM_L3INIT_PWRSTST_L3INIT_BANK1_STATEST_SHIFT                                                        (4U)
#define PM_L3INIT_PWRSTST_L3INIT_BANK1_STATEST_MASK                                                         (0x00000030U)
#define PM_L3INIT_PWRSTST_L3INIT_BANK1_STATEST_MEM_ON                                                        (3U)
#define PM_L3INIT_PWRSTST_L3INIT_BANK1_STATEST_RESERVED1                                                     (1U)
#define PM_L3INIT_PWRSTST_L3INIT_BANK1_STATEST_MEM_OFF                                                       (0U)
#define PM_L3INIT_PWRSTST_L3INIT_BANK1_STATEST_RESERVED                                                      (2U)

#define PM_L3INIT_PWRSTST_RESERVED_SHIFT                                                                    (3U)
#define PM_L3INIT_PWRSTST_RESERVED_MASK                                                                     (0x00000008U)

#define PM_L3INIT_PWRSTST_RESERVED2_SHIFT                                                                   (21U)
#define PM_L3INIT_PWRSTST_RESERVED2_MASK                                                                    (0x00e00000U)

#define PM_L3INIT_PWRSTST_RESERVED3_SHIFT                                                                   (26U)
#define PM_L3INIT_PWRSTST_RESERVED3_MASK                                                                    (0xfc000000U)

#define PM_L3INIT_PWRSTST_LASTPOWERSTATEENTERED_SHIFT                                                       (24U)
#define PM_L3INIT_PWRSTST_LASTPOWERSTATEENTERED_MASK                                                        (0x03000000U)
#define PM_L3INIT_PWRSTST_LASTPOWERSTATEENTERED_ON                                                           (3U)
#define PM_L3INIT_PWRSTST_LASTPOWERSTATEENTERED_OFF                                                          (0U)
#define PM_L3INIT_PWRSTST_LASTPOWERSTATEENTERED_RET                                                          (1U)
#define PM_L3INIT_PWRSTST_LASTPOWERSTATEENTERED_INACTIVE                                                     (2U)

#define PM_L3INIT_PWRSTST_L3INIT_BANK2_STATEST_SHIFT                                                        (6U)
#define PM_L3INIT_PWRSTST_L3INIT_BANK2_STATEST_MASK                                                         (0x000000c0U)
#define PM_L3INIT_PWRSTST_L3INIT_BANK2_STATEST_MEM_ON                                                        (3U)
#define PM_L3INIT_PWRSTST_L3INIT_BANK2_STATEST_MEM_RET                                                       (1U)
#define PM_L3INIT_PWRSTST_L3INIT_BANK2_STATEST_MEM_OFF                                                       (0U)
#define PM_L3INIT_PWRSTST_L3INIT_BANK2_STATEST_RESERVED                                                      (2U)

#define PM_L3INIT_PWRSTST_L3INIT_GMAC_STATEST_SHIFT                                                         (8U)
#define PM_L3INIT_PWRSTST_L3INIT_GMAC_STATEST_MASK                                                          (0x00000300U)
#define PM_L3INIT_PWRSTST_L3INIT_GMAC_STATEST_MEM_ON                                                         (3U)
#define PM_L3INIT_PWRSTST_L3INIT_GMAC_STATEST_RESERVED1                                                      (1U)
#define PM_L3INIT_PWRSTST_L3INIT_GMAC_STATEST_MEM_OFF                                                        (0U)
#define PM_L3INIT_PWRSTST_L3INIT_GMAC_STATEST_RESERVED                                                       (2U)

#define PM_L3INIT_PWRSTST_RESERVED1_SHIFT                                                                   (10U)
#define PM_L3INIT_PWRSTST_RESERVED1_MASK                                                                    (0x000ffc00U)

#define RM_PCIESS_RSTCTRL_RST_LOCAL_PCIE1_SHIFT                                                             (0U)
#define RM_PCIESS_RSTCTRL_RST_LOCAL_PCIE1_MASK                                                              (0x00000001U)
#define RM_PCIESS_RSTCTRL_RST_LOCAL_PCIE1_ASSERT                                                             (0U)
#define RM_PCIESS_RSTCTRL_RST_LOCAL_PCIE1_CLEAR                                                              (1U)

#define RM_PCIESS_RSTCTRL_RST_LOCAL_PCIE2_SHIFT                                                             (1U)
#define RM_PCIESS_RSTCTRL_RST_LOCAL_PCIE2_MASK                                                              (0x00000002U)
#define RM_PCIESS_RSTCTRL_RST_LOCAL_PCIE2_ASSERT                                                             (0U)
#define RM_PCIESS_RSTCTRL_RST_LOCAL_PCIE2_CLEAR                                                              (1U)

#define RM_PCIESS_RSTCTRL_RESERVED_SHIFT                                                                    (2U)
#define RM_PCIESS_RSTCTRL_RESERVED_MASK                                                                     (0xfffffffcU)

#define RM_PCIESS_RSTST_RST_LOCAL_PCIE1_SHIFT                                                               (0U)
#define RM_PCIESS_RSTST_RST_LOCAL_PCIE1_MASK                                                                (0x00000001U)
#define RM_PCIESS_RSTST_RST_LOCAL_PCIE1_RESET_YES                                                            (1U)
#define RM_PCIESS_RSTST_RST_LOCAL_PCIE1_RESET_NO                                                             (0U)

#define RM_PCIESS_RSTST_RST_LOCAL_PCIE2_SHIFT                                                               (1U)
#define RM_PCIESS_RSTST_RST_LOCAL_PCIE2_MASK                                                                (0x00000002U)
#define RM_PCIESS_RSTST_RST_LOCAL_PCIE2_RESET_YES                                                            (1U)
#define RM_PCIESS_RSTST_RST_LOCAL_PCIE2_RESET_NO                                                             (0U)

#define RM_PCIESS_RSTST_RESERVED_SHIFT                                                                      (2U)
#define RM_PCIESS_RSTST_RESERVED_MASK                                                                       (0xfffffffcU)

#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_MPU_SHIFT                                                         (0U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_MPU_MASK                                                          (0x00000001U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_MPU_ENABLED                                                        (1U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_MPU_DISABLED                                                       (0U)

#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_IPU2_SHIFT                                                        (1U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_IPU2_MASK                                                         (0x00000002U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_IPU2_ENABLED                                                       (1U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_IPU2_DISABLED                                                      (0U)

#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_DSP1_SHIFT                                                        (2U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_DSP1_MASK                                                         (0x00000004U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_DSP1_ENABLED                                                       (1U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_DSP1_DISABLED                                                      (0U)

#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_SDMA_SHIFT                                                        (3U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_SDMA_MASK                                                         (0x00000008U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_SDMA_ENABLED                                                       (1U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_SDMA_DISABLED                                                      (0U)

#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_IPU1_SHIFT                                                        (4U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_IPU1_MASK                                                         (0x00000010U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_IPU1_ENABLED                                                       (1U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_IPU1_DISABLED                                                      (0U)

#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_DSP2_SHIFT                                                        (5U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_DSP2_MASK                                                         (0x00000020U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_DSP2_ENABLED                                                       (1U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_DSP2_DISABLED                                                      (0U)

#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_EVE1_SHIFT                                                        (6U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_EVE1_MASK                                                         (0x00000040U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_EVE1_ENABLED                                                       (1U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_EVE1_DISABLED                                                      (0U)

#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_EVE2_SHIFT                                                        (7U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_EVE2_MASK                                                         (0x00000080U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_EVE2_ENABLED                                                       (1U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_EVE2_DISABLED                                                      (0U)

#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_EVE3_SHIFT                                                        (8U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_EVE3_MASK                                                         (0x00000100U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_EVE3_ENABLED                                                       (1U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_EVE3_DISABLED                                                      (0U)

#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_EVE4_SHIFT                                                        (9U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_EVE4_MASK                                                         (0x00000200U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_EVE4_ENABLED                                                       (1U)
#define PM_L3INIT_MMC1_WKDEP_WKUPDEP_MMC1_EVE4_DISABLED                                                      (0U)

#define PM_L3INIT_MMC1_WKDEP_RESERVED_SHIFT                                                                 (10U)
#define PM_L3INIT_MMC1_WKDEP_RESERVED_MASK                                                                  (0xfffffc00U)

#define RM_L3INIT_MMC1_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                        (1U)
#define RM_L3INIT_MMC1_CONTEXT_LOSTCONTEXT_RFF_MASK                                                         (0x00000002U)
#define RM_L3INIT_MMC1_CONTEXT_LOSTCONTEXT_RFF_LOST                                                          (1U)
#define RM_L3INIT_MMC1_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                    (0U)

#define RM_L3INIT_MMC1_CONTEXT_RESERVED_SHIFT                                                               (2U)
#define RM_L3INIT_MMC1_CONTEXT_RESERVED_MASK                                                                (0x000000fcU)

#define RM_L3INIT_MMC1_CONTEXT_RESERVED1_SHIFT                                                              (9U)
#define RM_L3INIT_MMC1_CONTEXT_RESERVED1_MASK                                                               (0xfffffe00U)

#define RM_L3INIT_MMC1_CONTEXT_RESERVED2_SHIFT                                                              (0U)
#define RM_L3INIT_MMC1_CONTEXT_RESERVED2_MASK                                                               (0x00000001U)

#define RM_L3INIT_MMC1_CONTEXT_LOSTMEM_L3INIT_BANK1_SHIFT                                                   (8U)
#define RM_L3INIT_MMC1_CONTEXT_LOSTMEM_L3INIT_BANK1_MASK                                                    (0x00000100U)
#define RM_L3INIT_MMC1_CONTEXT_LOSTMEM_L3INIT_BANK1_LOST                                                     (1U)
#define RM_L3INIT_MMC1_CONTEXT_LOSTMEM_L3INIT_BANK1_MAINTAINED                                               (0U)

#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_MPU_SHIFT                                                         (0U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_MPU_MASK                                                          (0x00000001U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_MPU_ENABLED                                                        (1U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_MPU_DISABLED                                                       (0U)

#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_IPU2_SHIFT                                                        (1U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_IPU2_MASK                                                         (0x00000002U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_IPU2_ENABLED                                                       (1U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_IPU2_DISABLED                                                      (0U)

#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_DSP1_SHIFT                                                        (2U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_DSP1_MASK                                                         (0x00000004U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_DSP1_ENABLED                                                       (1U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_DSP1_DISABLED                                                      (0U)

#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_SDMA_SHIFT                                                        (3U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_SDMA_MASK                                                         (0x00000008U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_SDMA_ENABLED                                                       (1U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_SDMA_DISABLED                                                      (0U)

#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_IPU1_SHIFT                                                        (4U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_IPU1_MASK                                                         (0x00000010U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_IPU1_ENABLED                                                       (1U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_IPU1_DISABLED                                                      (0U)

#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_DSP2_SHIFT                                                        (5U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_DSP2_MASK                                                         (0x00000020U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_DSP2_ENABLED                                                       (1U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_DSP2_DISABLED                                                      (0U)

#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_EVE1_SHIFT                                                        (6U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_EVE1_MASK                                                         (0x00000040U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_EVE1_ENABLED                                                       (1U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_EVE1_DISABLED                                                      (0U)

#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_EVE2_SHIFT                                                        (7U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_EVE2_MASK                                                         (0x00000080U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_EVE2_ENABLED                                                       (1U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_EVE2_DISABLED                                                      (0U)

#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_EVE3_SHIFT                                                        (8U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_EVE3_MASK                                                         (0x00000100U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_EVE3_ENABLED                                                       (1U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_EVE3_DISABLED                                                      (0U)

#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_EVE4_SHIFT                                                        (9U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_EVE4_MASK                                                         (0x00000200U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_EVE4_ENABLED                                                       (1U)
#define PM_L3INIT_MMC2_WKDEP_WKUPDEP_MMC2_EVE4_DISABLED                                                      (0U)

#define PM_L3INIT_MMC2_WKDEP_RESERVED_SHIFT                                                                 (10U)
#define PM_L3INIT_MMC2_WKDEP_RESERVED_MASK                                                                  (0xfffffc00U)

#define RM_L3INIT_MMC2_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                        (1U)
#define RM_L3INIT_MMC2_CONTEXT_LOSTCONTEXT_RFF_MASK                                                         (0x00000002U)
#define RM_L3INIT_MMC2_CONTEXT_LOSTCONTEXT_RFF_LOST                                                          (1U)
#define RM_L3INIT_MMC2_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                    (0U)

#define RM_L3INIT_MMC2_CONTEXT_RESERVED_SHIFT                                                               (2U)
#define RM_L3INIT_MMC2_CONTEXT_RESERVED_MASK                                                                (0x000000fcU)

#define RM_L3INIT_MMC2_CONTEXT_RESERVED1_SHIFT                                                              (9U)
#define RM_L3INIT_MMC2_CONTEXT_RESERVED1_MASK                                                               (0xfffffe00U)

#define RM_L3INIT_MMC2_CONTEXT_RESERVED2_SHIFT                                                              (0U)
#define RM_L3INIT_MMC2_CONTEXT_RESERVED2_MASK                                                               (0x00000001U)

#define RM_L3INIT_MMC2_CONTEXT_LOSTMEM_L3INIT_BANK1_SHIFT                                                   (8U)
#define RM_L3INIT_MMC2_CONTEXT_LOSTMEM_L3INIT_BANK1_MASK                                                    (0x00000100U)
#define RM_L3INIT_MMC2_CONTEXT_LOSTMEM_L3INIT_BANK1_LOST                                                     (1U)
#define RM_L3INIT_MMC2_CONTEXT_LOSTMEM_L3INIT_BANK1_MAINTAINED                                               (0U)

#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_MPU_SHIFT                                           (0U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_MPU_MASK                                            (0x00000001U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_MPU_ENABLED                                          (1U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_MPU_DISABLED                                         (0U)

#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_IPU2_SHIFT                                          (1U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_IPU2_MASK                                           (0x00000002U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_IPU2_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_IPU2_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_DSP1_SHIFT                                          (2U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_DSP1_MASK                                           (0x00000004U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_DSP1_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_DSP1_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS2_WKDEP_RESERVED1_SHIFT                                                         (3U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_RESERVED1_MASK                                                          (0x00000008U)

#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_IPU1_SHIFT                                          (4U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_IPU1_MASK                                           (0x00000010U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_IPU1_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_IPU1_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_DSP2_SHIFT                                          (5U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_DSP2_MASK                                           (0x00000020U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_DSP2_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_DSP2_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_EVE1_SHIFT                                          (6U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_EVE1_MASK                                           (0x00000040U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_EVE1_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_EVE1_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_EVE2_SHIFT                                          (7U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_EVE2_MASK                                           (0x00000080U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_EVE2_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_EVE2_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_EVE3_SHIFT                                          (8U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_EVE3_MASK                                           (0x00000100U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_EVE3_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_EVE3_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_EVE4_SHIFT                                          (9U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_EVE4_MASK                                           (0x00000200U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_EVE4_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_WKUPDEP_USB_OTG_SS2_EVE4_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS2_WKDEP_RESERVED_SHIFT                                                          (10U)
#define PM_L3INIT_USB_OTG_SS2_WKDEP_RESERVED_MASK                                                           (0xfffffc00U)

#define RM_L3INIT_USB_OTG_SS2_CONTEXT_RESERVED1_SHIFT                                                       (9U)
#define RM_L3INIT_USB_OTG_SS2_CONTEXT_RESERVED1_MASK                                                        (0xfffffe00U)

#define RM_L3INIT_USB_OTG_SS2_CONTEXT_RESERVED2_SHIFT                                                       (0U)
#define RM_L3INIT_USB_OTG_SS2_CONTEXT_RESERVED2_MASK                                                        (0x00000001U)

#define RM_L3INIT_USB_OTG_SS2_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                 (1U)
#define RM_L3INIT_USB_OTG_SS2_CONTEXT_LOSTCONTEXT_RFF_MASK                                                  (0x00000002U)
#define RM_L3INIT_USB_OTG_SS2_CONTEXT_LOSTCONTEXT_RFF_LOST                                                   (1U)
#define RM_L3INIT_USB_OTG_SS2_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                             (0U)

#define RM_L3INIT_USB_OTG_SS2_CONTEXT_RESERVED_SHIFT                                                        (2U)
#define RM_L3INIT_USB_OTG_SS2_CONTEXT_RESERVED_MASK                                                         (0x000000fcU)

#define RM_L3INIT_USB_OTG_SS2_CONTEXT_LOSTMEM_L3INIT_BANK1_SHIFT                                            (8U)
#define RM_L3INIT_USB_OTG_SS2_CONTEXT_LOSTMEM_L3INIT_BANK1_MASK                                             (0x00000100U)
#define RM_L3INIT_USB_OTG_SS2_CONTEXT_LOSTMEM_L3INIT_BANK1_LOST                                              (1U)
#define RM_L3INIT_USB_OTG_SS2_CONTEXT_LOSTMEM_L3INIT_BANK1_MAINTAINED                                        (0U)

#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_MPU_SHIFT                                           (0U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_MPU_MASK                                            (0x00000001U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_MPU_ENABLED                                          (1U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_MPU_DISABLED                                         (0U)

#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_IPU2_SHIFT                                          (1U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_IPU2_MASK                                           (0x00000002U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_IPU2_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_IPU2_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_DSP1_SHIFT                                          (2U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_DSP1_MASK                                           (0x00000004U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_DSP1_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_DSP1_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS3_WKDEP_RESERVED1_SHIFT                                                         (3U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_RESERVED1_MASK                                                          (0x00000008U)

#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_IPU1_SHIFT                                          (4U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_IPU1_MASK                                           (0x00000010U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_IPU1_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_IPU1_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_DSP2_SHIFT                                          (5U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_DSP2_MASK                                           (0x00000020U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_DSP2_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_DSP2_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_EVE1_SHIFT                                          (6U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_EVE1_MASK                                           (0x00000040U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_EVE1_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_EVE1_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_EVE2_SHIFT                                          (7U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_EVE2_MASK                                           (0x00000080U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_EVE2_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_EVE2_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_EVE3_SHIFT                                          (8U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_EVE3_MASK                                           (0x00000100U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_EVE3_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_EVE3_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_EVE4_SHIFT                                          (9U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_EVE4_MASK                                           (0x00000200U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_EVE4_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_WKUPDEP_USB_OTG_SS3_EVE4_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS3_WKDEP_RESERVED_SHIFT                                                          (10U)
#define PM_L3INIT_USB_OTG_SS3_WKDEP_RESERVED_MASK                                                           (0xfffffc00U)

#define RM_L3INIT_USB_OTG_SS3_CONTEXT_RESERVED1_SHIFT                                                       (9U)
#define RM_L3INIT_USB_OTG_SS3_CONTEXT_RESERVED1_MASK                                                        (0xfffffe00U)

#define RM_L3INIT_USB_OTG_SS3_CONTEXT_RESERVED2_SHIFT                                                       (0U)
#define RM_L3INIT_USB_OTG_SS3_CONTEXT_RESERVED2_MASK                                                        (0x00000001U)

#define RM_L3INIT_USB_OTG_SS3_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                 (1U)
#define RM_L3INIT_USB_OTG_SS3_CONTEXT_LOSTCONTEXT_RFF_MASK                                                  (0x00000002U)
#define RM_L3INIT_USB_OTG_SS3_CONTEXT_LOSTCONTEXT_RFF_LOST                                                   (1U)
#define RM_L3INIT_USB_OTG_SS3_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                             (0U)

#define RM_L3INIT_USB_OTG_SS3_CONTEXT_RESERVED_SHIFT                                                        (2U)
#define RM_L3INIT_USB_OTG_SS3_CONTEXT_RESERVED_MASK                                                         (0x000000fcU)

#define RM_L3INIT_USB_OTG_SS3_CONTEXT_LOSTMEM_L3INIT_BANK1_SHIFT                                            (8U)
#define RM_L3INIT_USB_OTG_SS3_CONTEXT_LOSTMEM_L3INIT_BANK1_MASK                                             (0x00000100U)
#define RM_L3INIT_USB_OTG_SS3_CONTEXT_LOSTMEM_L3INIT_BANK1_LOST                                              (1U)
#define RM_L3INIT_USB_OTG_SS3_CONTEXT_LOSTMEM_L3INIT_BANK1_MAINTAINED                                        (0U)

#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_MPU_SHIFT                                           (0U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_MPU_MASK                                            (0x00000001U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_MPU_ENABLED                                          (1U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_MPU_DISABLED                                         (0U)

#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_IPU2_SHIFT                                          (1U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_IPU2_MASK                                           (0x00000002U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_IPU2_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_IPU2_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_DSP1_SHIFT                                          (2U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_DSP1_MASK                                           (0x00000004U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_DSP1_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_DSP1_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS4_WKDEP_RESERVED1_SHIFT                                                         (3U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_RESERVED1_MASK                                                          (0x00000008U)

#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_IPU1_SHIFT                                          (4U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_IPU1_MASK                                           (0x00000010U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_IPU1_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_IPU1_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_DSP2_SHIFT                                          (5U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_DSP2_MASK                                           (0x00000020U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_DSP2_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_DSP2_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_EVE1_SHIFT                                          (6U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_EVE1_MASK                                           (0x00000040U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_EVE1_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_EVE1_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_EVE2_SHIFT                                          (7U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_EVE2_MASK                                           (0x00000080U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_EVE2_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_EVE2_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_EVE3_SHIFT                                          (8U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_EVE3_MASK                                           (0x00000100U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_EVE3_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_EVE3_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_EVE4_SHIFT                                          (9U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_EVE4_MASK                                           (0x00000200U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_EVE4_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_WKUPDEP_USB_OTG_SS4_EVE4_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS4_WKDEP_RESERVED_SHIFT                                                          (10U)
#define PM_L3INIT_USB_OTG_SS4_WKDEP_RESERVED_MASK                                                           (0xfffffc00U)

#define RM_L3INIT_USB_OTG_SS4_CONTEXT_RESERVED1_SHIFT                                                       (9U)
#define RM_L3INIT_USB_OTG_SS4_CONTEXT_RESERVED1_MASK                                                        (0xfffffe00U)

#define RM_L3INIT_USB_OTG_SS4_CONTEXT_RESERVED2_SHIFT                                                       (0U)
#define RM_L3INIT_USB_OTG_SS4_CONTEXT_RESERVED2_MASK                                                        (0x00000001U)

#define RM_L3INIT_USB_OTG_SS4_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                 (1U)
#define RM_L3INIT_USB_OTG_SS4_CONTEXT_LOSTCONTEXT_RFF_MASK                                                  (0x00000002U)
#define RM_L3INIT_USB_OTG_SS4_CONTEXT_LOSTCONTEXT_RFF_LOST                                                   (1U)
#define RM_L3INIT_USB_OTG_SS4_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                             (0U)

#define RM_L3INIT_USB_OTG_SS4_CONTEXT_RESERVED_SHIFT                                                        (2U)
#define RM_L3INIT_USB_OTG_SS4_CONTEXT_RESERVED_MASK                                                         (0x000000fcU)

#define RM_L3INIT_USB_OTG_SS4_CONTEXT_LOSTMEM_L3INIT_BANK1_SHIFT                                            (8U)
#define RM_L3INIT_USB_OTG_SS4_CONTEXT_LOSTMEM_L3INIT_BANK1_MASK                                             (0x00000100U)
#define RM_L3INIT_USB_OTG_SS4_CONTEXT_LOSTMEM_L3INIT_BANK1_LOST                                              (1U)
#define RM_L3INIT_USB_OTG_SS4_CONTEXT_LOSTMEM_L3INIT_BANK1_MAINTAINED                                        (0U)

#define RM_L3INIT_MLB_SS_CONTEXT_LOSTMEM_MLB_BANK_SHIFT                                                     (8U)
#define RM_L3INIT_MLB_SS_CONTEXT_LOSTMEM_MLB_BANK_MASK                                                      (0x00000100U)
#define RM_L3INIT_MLB_SS_CONTEXT_LOSTMEM_MLB_BANK_LOST                                                       (1U)
#define RM_L3INIT_MLB_SS_CONTEXT_LOSTMEM_MLB_BANK_MAINTAINED                                                 (0U)

#define RM_L3INIT_MLB_SS_CONTEXT_RESERVED1_SHIFT                                                            (9U)
#define RM_L3INIT_MLB_SS_CONTEXT_RESERVED1_MASK                                                             (0xfffffe00U)

#define RM_L3INIT_MLB_SS_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                      (0U)
#define RM_L3INIT_MLB_SS_CONTEXT_LOSTCONTEXT_DFF_MASK                                                       (0x00000001U)
#define RM_L3INIT_MLB_SS_CONTEXT_LOSTCONTEXT_DFF_LOST                                                        (1U)
#define RM_L3INIT_MLB_SS_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                  (0U)

#define RM_L3INIT_MLB_SS_CONTEXT_RESERVED_SHIFT                                                             (1U)
#define RM_L3INIT_MLB_SS_CONTEXT_RESERVED_MASK                                                              (0x000000feU)

#define RM_L3INIT_IEEE1500_2_OCP_CONTEXT_RESERVED_SHIFT                                                     (1U)
#define RM_L3INIT_IEEE1500_2_OCP_CONTEXT_RESERVED_MASK                                                      (0xfffffffeU)

#define RM_L3INIT_IEEE1500_2_OCP_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                              (0U)
#define RM_L3INIT_IEEE1500_2_OCP_CONTEXT_LOSTCONTEXT_DFF_MASK                                               (0x00000001U)
#define RM_L3INIT_IEEE1500_2_OCP_CONTEXT_LOSTCONTEXT_DFF_LOST                                                (1U)
#define RM_L3INIT_IEEE1500_2_OCP_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                          (0U)

#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_MPU_SHIFT                                                         (0U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_MPU_MASK                                                          (0x00000001U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_MPU_DISABLED                                                       (0U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_MPU_ENABLED                                                        (1U)

#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_IPU2_SHIFT                                                        (1U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_IPU2_MASK                                                         (0x00000002U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_IPU2_ENABLED                                                       (1U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_IPU2_DISABLED                                                      (0U)

#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_DSP1_SHIFT                                                        (2U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_DSP1_MASK                                                         (0x00000004U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_DSP1_ENABLED                                                       (1U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_DSP1_DISABLED                                                      (0U)

#define PM_L3INIT_SATA_WKDEP_RESERVED1_SHIFT                                                                (3U)
#define PM_L3INIT_SATA_WKDEP_RESERVED1_MASK                                                                 (0x00000008U)

#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_IPU1_SHIFT                                                        (4U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_IPU1_MASK                                                         (0x00000010U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_IPU1_ENABLED                                                       (1U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_IPU1_DISABLED                                                      (0U)

#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_DSP2_SHIFT                                                        (5U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_DSP2_MASK                                                         (0x00000020U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_DSP2_ENABLED                                                       (1U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_DSP2_DISABLED                                                      (0U)

#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_EVE1_SHIFT                                                        (6U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_EVE1_MASK                                                         (0x00000040U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_EVE1_ENABLED                                                       (1U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_EVE1_DISABLED                                                      (0U)

#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_EVE2_SHIFT                                                        (7U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_EVE2_MASK                                                         (0x00000080U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_EVE2_ENABLED                                                       (1U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_EVE2_DISABLED                                                      (0U)

#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_EVE3_SHIFT                                                        (8U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_EVE3_MASK                                                         (0x00000100U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_EVE3_ENABLED                                                       (1U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_EVE3_DISABLED                                                      (0U)

#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_EVE4_SHIFT                                                        (9U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_EVE4_MASK                                                         (0x00000200U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_EVE4_ENABLED                                                       (1U)
#define PM_L3INIT_SATA_WKDEP_WKUPDEP_SATA_EVE4_DISABLED                                                      (0U)

#define PM_L3INIT_SATA_WKDEP_RESERVED_SHIFT                                                                 (10U)
#define PM_L3INIT_SATA_WKDEP_RESERVED_MASK                                                                  (0xfffffc00U)

#define RM_L3INIT_SATA_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                        (0U)
#define RM_L3INIT_SATA_CONTEXT_LOSTCONTEXT_DFF_MASK                                                         (0x00000001U)
#define RM_L3INIT_SATA_CONTEXT_LOSTCONTEXT_DFF_LOST                                                          (1U)
#define RM_L3INIT_SATA_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                    (0U)

#define RM_L3INIT_SATA_CONTEXT_RESERVED_SHIFT                                                               (1U)
#define RM_L3INIT_SATA_CONTEXT_RESERVED_MASK                                                                (0x000000feU)

#define RM_L3INIT_SATA_CONTEXT_LOSTMEM_L3INIT_BANK1_SHIFT                                                   (8U)
#define RM_L3INIT_SATA_CONTEXT_LOSTMEM_L3INIT_BANK1_MASK                                                    (0x00000100U)
#define RM_L3INIT_SATA_CONTEXT_LOSTMEM_L3INIT_BANK1_LOST                                                     (1U)
#define RM_L3INIT_SATA_CONTEXT_LOSTMEM_L3INIT_BANK1_MAINTAINED                                               (0U)

#define RM_L3INIT_SATA_CONTEXT_RESERVED1_SHIFT                                                              (9U)
#define RM_L3INIT_SATA_CONTEXT_RESERVED1_MASK                                                               (0xfffffe00U)

#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_MPU_SHIFT                                                     (0U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_MPU_MASK                                                      (0x00000001U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_MPU_ENABLED                                                    (1U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_MPU_DISABLED                                                   (0U)

#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_IPU2_SHIFT                                                    (1U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_IPU2_MASK                                                     (0x00000002U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_IPU2_ENABLED                                                   (1U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_IPU2_DISABLED                                                  (0U)

#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_DSP1_SHIFT                                                    (2U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_DSP1_MASK                                                     (0x00000004U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_DSP1_ENABLED                                                   (1U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_DSP1_DISABLED                                                  (0U)

#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_IPU1_SHIFT                                                    (4U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_IPU1_MASK                                                     (0x00000010U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_IPU1_ENABLED                                                   (1U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_IPU1_DISABLED                                                  (0U)

#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_DSP2_SHIFT                                                    (5U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_DSP2_MASK                                                     (0x00000020U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_DSP2_ENABLED                                                   (1U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_DSP2_DISABLED                                                  (0U)

#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_EVE1_SHIFT                                                    (6U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_EVE1_MASK                                                     (0x00000040U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_EVE1_ENABLED                                                   (1U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_EVE1_DISABLED                                                  (0U)

#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_EVE2_SHIFT                                                    (7U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_EVE2_MASK                                                     (0x00000080U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_EVE2_ENABLED                                                   (1U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_EVE2_DISABLED                                                  (0U)

#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_EVE3_SHIFT                                                    (8U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_EVE3_MASK                                                     (0x00000100U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_EVE3_ENABLED                                                   (1U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_EVE3_DISABLED                                                  (0U)

#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_EVE4_SHIFT                                                    (9U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_EVE4_MASK                                                     (0x00000200U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_EVE4_ENABLED                                                   (1U)
#define PM_PCIE_PCIESS1_WKDEP_WKUPDEP_PCIESS1_EVE4_DISABLED                                                  (0U)

#define PM_PCIE_PCIESS1_WKDEP_RESERVED_SHIFT                                                                (10U)
#define PM_PCIE_PCIESS1_WKDEP_RESERVED_MASK                                                                 (0xfffffc00U)

#define PM_PCIE_PCIESS1_WKDEP_RESERVED1_SHIFT                                                               (3U)
#define PM_PCIE_PCIESS1_WKDEP_RESERVED1_MASK                                                                (0x00000008U)

#define RM_PCIE_PCIESS1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                       (0U)
#define RM_PCIE_PCIESS1_CONTEXT_LOSTCONTEXT_DFF_MASK                                                        (0x00000001U)
#define RM_PCIE_PCIESS1_CONTEXT_LOSTCONTEXT_DFF_LOST                                                         (1U)
#define RM_PCIE_PCIESS1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                   (0U)

#define RM_PCIE_PCIESS1_CONTEXT_RESERVED_SHIFT                                                              (1U)
#define RM_PCIE_PCIESS1_CONTEXT_RESERVED_MASK                                                               (0x000000feU)

#define RM_PCIE_PCIESS1_CONTEXT_LOSTMEM_L3INIT_BANK1_SHIFT                                                  (8U)
#define RM_PCIE_PCIESS1_CONTEXT_LOSTMEM_L3INIT_BANK1_MASK                                                   (0x00000100U)
#define RM_PCIE_PCIESS1_CONTEXT_LOSTMEM_L3INIT_BANK1_LOST                                                    (1U)
#define RM_PCIE_PCIESS1_CONTEXT_LOSTMEM_L3INIT_BANK1_MAINTAINED                                              (0U)

#define RM_PCIE_PCIESS1_CONTEXT_RESERVED1_SHIFT                                                             (9U)
#define RM_PCIE_PCIESS1_CONTEXT_RESERVED1_MASK                                                              (0xfffffe00U)

#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_MPU_SHIFT                                                     (0U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_MPU_MASK                                                      (0x00000001U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_MPU_ENABLED                                                    (1U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_MPU_DISABLED                                                   (0U)

#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_IPU2_SHIFT                                                    (1U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_IPU2_MASK                                                     (0x00000002U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_IPU2_ENABLED                                                   (1U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_IPU2_DISABLED                                                  (0U)

#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_DSP1_SHIFT                                                    (2U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_DSP1_MASK                                                     (0x00000004U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_DSP1_ENABLED                                                   (1U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_DSP1_DISABLED                                                  (0U)

#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_IPU1_SHIFT                                                    (4U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_IPU1_MASK                                                     (0x00000010U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_IPU1_ENABLED                                                   (1U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_IPU1_DISABLED                                                  (0U)

#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_DSP2_SHIFT                                                    (5U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_DSP2_MASK                                                     (0x00000020U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_DSP2_ENABLED                                                   (1U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_DSP2_DISABLED                                                  (0U)

#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_EVE1_SHIFT                                                    (6U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_EVE1_MASK                                                     (0x00000040U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_EVE1_ENABLED                                                   (1U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_EVE1_DISABLED                                                  (0U)

#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_EVE2_SHIFT                                                    (7U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_EVE2_MASK                                                     (0x00000080U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_EVE2_ENABLED                                                   (1U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_EVE2_DISABLED                                                  (0U)

#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_EVE3_SHIFT                                                    (8U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_EVE3_MASK                                                     (0x00000100U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_EVE3_ENABLED                                                   (1U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_EVE3_DISABLED                                                  (0U)

#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_EVE4_SHIFT                                                    (9U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_EVE4_MASK                                                     (0x00000200U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_EVE4_ENABLED                                                   (1U)
#define PM_PCIE_PCIESS2_WKDEP_WKUPDEP_PCIESS2_EVE4_DISABLED                                                  (0U)

#define PM_PCIE_PCIESS2_WKDEP_RESERVED_SHIFT                                                                (10U)
#define PM_PCIE_PCIESS2_WKDEP_RESERVED_MASK                                                                 (0xfffffc00U)

#define PM_PCIE_PCIESS2_WKDEP_RESERVED1_SHIFT                                                               (3U)
#define PM_PCIE_PCIESS2_WKDEP_RESERVED1_MASK                                                                (0x00000008U)

#define RM_PCIE_PCIESS2_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                       (0U)
#define RM_PCIE_PCIESS2_CONTEXT_LOSTCONTEXT_DFF_MASK                                                        (0x00000001U)
#define RM_PCIE_PCIESS2_CONTEXT_LOSTCONTEXT_DFF_LOST                                                         (1U)
#define RM_PCIE_PCIESS2_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                   (0U)

#define RM_PCIE_PCIESS2_CONTEXT_RESERVED_SHIFT                                                              (1U)
#define RM_PCIE_PCIESS2_CONTEXT_RESERVED_MASK                                                               (0x000000feU)

#define RM_PCIE_PCIESS2_CONTEXT_LOSTMEM_L3INIT_BANK1_SHIFT                                                  (8U)
#define RM_PCIE_PCIESS2_CONTEXT_LOSTMEM_L3INIT_BANK1_MASK                                                   (0x00000100U)
#define RM_PCIE_PCIESS2_CONTEXT_LOSTMEM_L3INIT_BANK1_LOST                                                    (1U)
#define RM_PCIE_PCIESS2_CONTEXT_LOSTMEM_L3INIT_BANK1_MAINTAINED                                              (0U)

#define RM_PCIE_PCIESS2_CONTEXT_RESERVED1_SHIFT                                                             (9U)
#define RM_PCIE_PCIESS2_CONTEXT_RESERVED1_MASK                                                              (0xfffffe00U)

#define RM_GMAC_GMAC_CONTEXT_RESERVED1_SHIFT                                                                (9U)
#define RM_GMAC_GMAC_CONTEXT_RESERVED1_MASK                                                                 (0xfffffe00U)

#define RM_GMAC_GMAC_CONTEXT_LOSTMEM_GMAC_BANK_SHIFT                                                        (8U)
#define RM_GMAC_GMAC_CONTEXT_LOSTMEM_GMAC_BANK_MASK                                                         (0x00000100U)
#define RM_GMAC_GMAC_CONTEXT_LOSTMEM_GMAC_BANK_LOST                                                          (1U)
#define RM_GMAC_GMAC_CONTEXT_LOSTMEM_GMAC_BANK_MAINTAINED                                                    (0U)

#define RM_GMAC_GMAC_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                          (0U)
#define RM_GMAC_GMAC_CONTEXT_LOSTCONTEXT_DFF_MASK                                                           (0x00000001U)
#define RM_GMAC_GMAC_CONTEXT_LOSTCONTEXT_DFF_LOST                                                            (1U)
#define RM_GMAC_GMAC_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                      (0U)

#define RM_GMAC_GMAC_CONTEXT_RESERVED_SHIFT                                                                 (1U)
#define RM_GMAC_GMAC_CONTEXT_RESERVED_MASK                                                                  (0x000000feU)

#define RM_L3INIT_OCP2SCP1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                    (0U)
#define RM_L3INIT_OCP2SCP1_CONTEXT_LOSTCONTEXT_DFF_MASK                                                     (0x00000001U)
#define RM_L3INIT_OCP2SCP1_CONTEXT_LOSTCONTEXT_DFF_LOST                                                      (1U)
#define RM_L3INIT_OCP2SCP1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                (0U)

#define RM_L3INIT_OCP2SCP1_CONTEXT_RESERVED_SHIFT                                                           (1U)
#define RM_L3INIT_OCP2SCP1_CONTEXT_RESERVED_MASK                                                            (0xfffffffeU)

#define RM_L3INIT_OCP2SCP3_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                    (0U)
#define RM_L3INIT_OCP2SCP3_CONTEXT_LOSTCONTEXT_DFF_MASK                                                     (0x00000001U)
#define RM_L3INIT_OCP2SCP3_CONTEXT_LOSTCONTEXT_DFF_LOST                                                      (1U)
#define RM_L3INIT_OCP2SCP3_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                (0U)

#define RM_L3INIT_OCP2SCP3_CONTEXT_RESERVED_SHIFT                                                           (1U)
#define RM_L3INIT_OCP2SCP3_CONTEXT_RESERVED_MASK                                                            (0xfffffffeU)

#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_MPU_SHIFT                                           (0U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_MPU_MASK                                            (0x00000001U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_MPU_ENABLED                                          (1U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_MPU_DISABLED                                         (0U)

#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_IPU2_SHIFT                                          (1U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_IPU2_MASK                                           (0x00000002U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_IPU2_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_IPU2_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_DSP1_SHIFT                                          (2U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_DSP1_MASK                                           (0x00000004U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_DSP1_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_DSP1_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS1_WKDEP_RESERVED1_SHIFT                                                         (3U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_RESERVED1_MASK                                                          (0x00000008U)

#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_IPU1_SHIFT                                          (4U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_IPU1_MASK                                           (0x00000010U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_IPU1_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_IPU1_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_DSP2_SHIFT                                          (5U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_DSP2_MASK                                           (0x00000020U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_DSP2_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_DSP2_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_EVE1_SHIFT                                          (6U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_EVE1_MASK                                           (0x00000040U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_EVE1_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_EVE1_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_EVE2_SHIFT                                          (7U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_EVE2_MASK                                           (0x00000080U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_EVE2_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_EVE2_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_EVE3_SHIFT                                          (8U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_EVE3_MASK                                           (0x00000100U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_EVE3_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_EVE3_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_EVE4_SHIFT                                          (9U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_EVE4_MASK                                           (0x00000200U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_EVE4_ENABLED                                         (1U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_WKUPDEP_USB_OTG_SS1_EVE4_DISABLED                                        (0U)

#define PM_L3INIT_USB_OTG_SS1_WKDEP_RESERVED_SHIFT                                                          (10U)
#define PM_L3INIT_USB_OTG_SS1_WKDEP_RESERVED_MASK                                                           (0xfffffc00U)

#define RM_L3INIT_USB_OTG_SS1_CONTEXT_RESERVED1_SHIFT                                                       (9U)
#define RM_L3INIT_USB_OTG_SS1_CONTEXT_RESERVED1_MASK                                                        (0xfffffe00U)

#define RM_L3INIT_USB_OTG_SS1_CONTEXT_RESERVED2_SHIFT                                                       (0U)
#define RM_L3INIT_USB_OTG_SS1_CONTEXT_RESERVED2_MASK                                                        (0x00000001U)

#define RM_L3INIT_USB_OTG_SS1_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                 (1U)
#define RM_L3INIT_USB_OTG_SS1_CONTEXT_LOSTCONTEXT_RFF_MASK                                                  (0x00000002U)
#define RM_L3INIT_USB_OTG_SS1_CONTEXT_LOSTCONTEXT_RFF_LOST                                                   (1U)
#define RM_L3INIT_USB_OTG_SS1_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                             (0U)

#define RM_L3INIT_USB_OTG_SS1_CONTEXT_RESERVED_SHIFT                                                        (2U)
#define RM_L3INIT_USB_OTG_SS1_CONTEXT_RESERVED_MASK                                                         (0x000000fcU)

#define RM_L3INIT_USB_OTG_SS1_CONTEXT_LOSTMEM_L3INIT_BANK1_SHIFT                                            (8U)
#define RM_L3INIT_USB_OTG_SS1_CONTEXT_LOSTMEM_L3INIT_BANK1_MASK                                             (0x00000100U)
#define RM_L3INIT_USB_OTG_SS1_CONTEXT_LOSTMEM_L3INIT_BANK1_LOST                                              (1U)
#define RM_L3INIT_USB_OTG_SS1_CONTEXT_LOSTMEM_L3INIT_BANK1_MAINTAINED                                        (0U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_L3INIT_PRM_H_ */
