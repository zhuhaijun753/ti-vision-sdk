/******************************************************************************
*
* hw_l3init_cm_core.h - register-level header file for PRCM
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
#ifndef HW_L3INIT_CM_CORE_H_
#define HW_L3INIT_CM_CORE_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define CM_L3INIT_CLKSTCTRL                                                                                 (0x0U)
#define CM_L3INIT_STATICDEP                                                                                 (0x4U)
#define CM_L3INIT_DYNAMICDEP                                                                                (0x8U)
#define CM_L3INIT_MMC1_CLKCTRL                                                                              (0x28U)
#define CM_L3INIT_MMC2_CLKCTRL                                                                              (0x30U)
#define CM_L3INIT_USB_OTG_SS2_CLKCTRL                                                                       (0x40U)
#define CM_L3INIT_USB_OTG_SS3_CLKCTRL                                                                       (0x48U)
#define CM_L3INIT_USB_OTG_SS4_CLKCTRL                                                                       (0x50U)
#define CM_L3INIT_MLB_SS_CLKCTRL                                                                            (0x58U)
#define CM_L3INIT_IEEE1500_2_OCP_CLKCTRL                                                                    (0x78U)
#define CM_L3INIT_SATA_CLKCTRL                                                                              (0x88U)
#define CM_PCIE_CLKSTCTRL                                                                                   (0xa0U)
#define CM_PCIE_STATICDEP                                                                                   (0xa4U)
#define CM_PCIE_PCIESS1_CLKCTRL                                                                             (0xb0U)
#define CM_PCIE_PCIESS2_CLKCTRL                                                                             (0xb8U)
#define CM_GMAC_CLKSTCTRL                                                                                   (0xc0U)
#define CM_GMAC_STATICDEP                                                                                   (0xc4U)
#define CM_GMAC_DYNAMICDEP                                                                                  (0xc8U)
#define CM_GMAC_GMAC_CLKCTRL                                                                                (0xd0U)
#define CM_L3INIT_OCP2SCP1_CLKCTRL                                                                          (0xe0U)
#define CM_L3INIT_OCP2SCP3_CLKCTRL                                                                          (0xe8U)
#define CM_L3INIT_USB_OTG_SS1_CLKCTRL                                                                       (0xf0U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define CM_L3INIT_CLKSTCTRL_CLKTRCTRL_SHIFT                                                                 (0U)
#define CM_L3INIT_CLKSTCTRL_CLKTRCTRL_MASK                                                                  (0x00000003U)
#define CM_L3INIT_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                                                               (0U)
#define CM_L3INIT_CLKSTCTRL_CLKTRCTRL_SW_SLEEP                                                               (1U)
#define CM_L3INIT_CLKSTCTRL_CLKTRCTRL_SW_WKUP                                                                (2U)
#define CM_L3INIT_CLKSTCTRL_CLKTRCTRL_HW_AUTO                                                                (3U)

#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_L3_GICLK_SHIFT                                               (8U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_L3_GICLK_MASK                                                (0x00000100U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_L3_GICLK_INACT                                                (0U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_L3_GICLK_ACT                                                  (1U)

#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_L4_GICLK_SHIFT                                               (9U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_L4_GICLK_MASK                                                (0x00000200U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_L4_GICLK_INACT                                                (0U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_L4_GICLK_ACT                                                  (1U)

#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_48M_GFCLK_SHIFT                                              (11U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_48M_GFCLK_MASK                                               (0x00000800U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_48M_GFCLK_INACT                                               (0U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_48M_GFCLK_ACT                                                 (1U)

#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_HSI_GFCLK_SHIFT                                                     (14U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_HSI_GFCLK_MASK                                                      (0x00004000U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_HSI_GFCLK_INACT                                                      (0U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_HSI_GFCLK_ACT                                                        (1U)

#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_MMC1_GFCLK_SHIFT                                                    (15U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_MMC1_GFCLK_MASK                                                     (0x00008000U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_MMC1_GFCLK_INACT                                                     (0U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_MMC1_GFCLK_ACT                                                       (1U)

#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_MMC2_GFCLK_SHIFT                                                    (16U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_MMC2_GFCLK_MASK                                                     (0x00010000U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_MMC2_GFCLK_INACT                                                     (0U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_MMC2_GFCLK_ACT                                                       (1U)

#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_USB_DPLL_CLK_SHIFT                                                  (12U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_USB_DPLL_CLK_MASK                                                   (0x00001000U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_USB_DPLL_CLK_INACT                                                   (0U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_USB_DPLL_CLK_ACT                                                     (1U)

#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_USB_DPLL_HS_CLK_SHIFT                                               (13U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_USB_DPLL_HS_CLK_MASK                                                (0x00002000U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_USB_DPLL_HS_CLK_INACT                                                (0U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_USB_DPLL_HS_CLK_ACT                                                  (1U)

#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_USB_OTG_SS_REF_CLK_SHIFT                                            (20U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_USB_OTG_SS_REF_CLK_MASK                                             (0x00100000U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_USB_OTG_SS_REF_CLK_INACT                                             (0U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_USB_OTG_SS_REF_CLK_ACT                                               (1U)

#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_USB_LFPS_TX_GFCLK_SHIFT                                      (10U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_USB_LFPS_TX_GFCLK_MASK                                       (0x00000400U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_USB_LFPS_TX_GFCLK_INACT                                       (0U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_USB_LFPS_TX_GFCLK_ACT                                         (1U)

#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_MLB_SHB_L3_GICLK_SHIFT                                              (17U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_MLB_SHB_L3_GICLK_MASK                                               (0x00020000U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_MLB_SHB_L3_GICLK_INACT                                               (0U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_MLB_SHB_L3_GICLK_ACT                                                 (1U)

#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_MLB_SPB_L4_GICLK_SHIFT                                              (18U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_MLB_SPB_L4_GICLK_MASK                                               (0x00040000U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_MLB_SPB_L4_GICLK_INACT                                               (0U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_MLB_SPB_L4_GICLK_ACT                                                 (1U)

#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_MLB_SYS_L3_GFCLK_SHIFT                                              (19U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_MLB_SYS_L3_GFCLK_MASK                                               (0x00080000U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_MLB_SYS_L3_GFCLK_INACT                                               (0U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_MLB_SYS_L3_GFCLK_ACT                                                 (1U)

#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_480M_GFCLK_SHIFT                                             (21U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_480M_GFCLK_MASK                                              (0x00200000U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_480M_GFCLK_INACT                                              (0U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_480M_GFCLK_ACT                                                (1U)

#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_960M_GFCLK_SHIFT                                             (22U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_960M_GFCLK_MASK                                              (0x00400000U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_960M_GFCLK_INACT                                              (0U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_960M_GFCLK_ACT                                                (1U)

#define CM_L3INIT_CLKSTCTRL_RESERVED_SHIFT                                                                  (2U)
#define CM_L3INIT_CLKSTCTRL_RESERVED_MASK                                                                   (0x000000fcU)

#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_32K_GFCLK_SHIFT                                              (23U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_32K_GFCLK_MASK                                               (0x00800000U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_32K_GFCLK_INACT                                               (0U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_32K_GFCLK_ACT                                                 (1U)

#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_SATA_REF_GFCLK_SHIFT                                                (24U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_SATA_REF_GFCLK_MASK                                                 (0x01000000U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_SATA_REF_GFCLK_INACT                                                 (0U)
#define CM_L3INIT_CLKSTCTRL_CLKACTIVITY_SATA_REF_GFCLK_ACT                                                   (1U)

#define CM_L3INIT_CLKSTCTRL_RESERVED1_SHIFT                                                                 (25U)
#define CM_L3INIT_CLKSTCTRL_RESERVED1_MASK                                                                  (0xfe000000U)

#define CM_L3INIT_STATICDEP_IVA_STATDEP_SHIFT                                                               (2U)
#define CM_L3INIT_STATICDEP_IVA_STATDEP_MASK                                                                (0x00000004U)
#define CM_L3INIT_STATICDEP_IVA_STATDEP_ENABLED                                                              (1U)
#define CM_L3INIT_STATICDEP_IVA_STATDEP_DISABLED                                                             (0U)

#define CM_L3INIT_STATICDEP_EMIF_STATDEP_SHIFT                                                              (4U)
#define CM_L3INIT_STATICDEP_EMIF_STATDEP_MASK                                                               (0x00000010U)
#define CM_L3INIT_STATICDEP_EMIF_STATDEP_ENABLED                                                             (1U)
#define CM_L3INIT_STATICDEP_EMIF_STATDEP_DISABLED                                                            (0U)

#define CM_L3INIT_STATICDEP_L3MAIN1_STATDEP_SHIFT                                                           (5U)
#define CM_L3INIT_STATICDEP_L3MAIN1_STATDEP_MASK                                                            (0x00000020U)
#define CM_L3INIT_STATICDEP_L3MAIN1_STATDEP_ENABLED                                                          (1U)

#define CM_L3INIT_STATICDEP_L4CFG_STATDEP_SHIFT                                                             (12U)
#define CM_L3INIT_STATICDEP_L4CFG_STATDEP_MASK                                                              (0x00001000U)
#define CM_L3INIT_STATICDEP_L4CFG_STATDEP_ENABLED                                                            (1U)
#define CM_L3INIT_STATICDEP_L4CFG_STATDEP_DISABLED                                                           (0U)

#define CM_L3INIT_STATICDEP_L4PER_STATDEP_SHIFT                                                             (13U)
#define CM_L3INIT_STATICDEP_L4PER_STATDEP_MASK                                                              (0x00002000U)
#define CM_L3INIT_STATICDEP_L4PER_STATDEP_ENABLED                                                            (1U)
#define CM_L3INIT_STATICDEP_L4PER_STATDEP_DISABLED                                                           (0U)

#define CM_L3INIT_STATICDEP_L4SEC_STATDEP_SHIFT                                                             (14U)
#define CM_L3INIT_STATICDEP_L4SEC_STATDEP_MASK                                                              (0x00004000U)
#define CM_L3INIT_STATICDEP_L4SEC_STATDEP_ENABLED                                                            (1U)
#define CM_L3INIT_STATICDEP_L4SEC_STATDEP_DISABLED                                                           (0U)

#define CM_L3INIT_STATICDEP_WKUPAON_STATDEP_SHIFT                                                           (15U)
#define CM_L3INIT_STATICDEP_WKUPAON_STATDEP_MASK                                                            (0x00008000U)
#define CM_L3INIT_STATICDEP_WKUPAON_STATDEP_ENABLED                                                          (1U)
#define CM_L3INIT_STATICDEP_WKUPAON_STATDEP_DISABLED                                                         (0U)

#define CM_L3INIT_STATICDEP_L4PER3_STATDEP_SHIFT                                                            (27U)
#define CM_L3INIT_STATICDEP_L4PER3_STATDEP_MASK                                                             (0x08000000U)
#define CM_L3INIT_STATICDEP_L4PER3_STATDEP_ENABLED                                                           (1U)
#define CM_L3INIT_STATICDEP_L4PER3_STATDEP_DISABLED                                                          (0U)

#define CM_L3INIT_STATICDEP_RESERVED_SHIFT                                                                  (0U)
#define CM_L3INIT_STATICDEP_RESERVED_MASK                                                                   (0x00000003U)

#define CM_L3INIT_STATICDEP_RESERVED1_SHIFT                                                                 (3U)
#define CM_L3INIT_STATICDEP_RESERVED1_MASK                                                                  (0x00000008U)

#define CM_L3INIT_STATICDEP_RESERVED2_SHIFT                                                                 (6U)
#define CM_L3INIT_STATICDEP_RESERVED2_MASK                                                                  (0x00000fc0U)

#define CM_L3INIT_STATICDEP_RESERVED3_SHIFT                                                                 (16U)
#define CM_L3INIT_STATICDEP_RESERVED3_MASK                                                                  (0x07ff0000U)

#define CM_L3INIT_STATICDEP_RESERVED4_SHIFT                                                                 (28U)
#define CM_L3INIT_STATICDEP_RESERVED4_MASK                                                                  (0xf0000000U)

#define CM_L3INIT_DYNAMICDEP_L3MAIN1_DYNDEP_SHIFT                                                           (5U)
#define CM_L3INIT_DYNAMICDEP_L3MAIN1_DYNDEP_MASK                                                            (0x00000020U)
#define CM_L3INIT_DYNAMICDEP_L3MAIN1_DYNDEP_DISABLED                                                         (0U)

#define CM_L3INIT_DYNAMICDEP_RESERVED_SHIFT                                                                 (0U)
#define CM_L3INIT_DYNAMICDEP_RESERVED_MASK                                                                  (0x0000001fU)

#define CM_L3INIT_DYNAMICDEP_RESERVED1_SHIFT                                                                (6U)
#define CM_L3INIT_DYNAMICDEP_RESERVED1_MASK                                                                 (0xffffffc0U)

#define CM_L3INIT_MMC1_CLKCTRL_RESERVED1_SHIFT                                                              (19U)
#define CM_L3INIT_MMC1_CLKCTRL_RESERVED1_MASK                                                               (0x00f80000U)

#define CM_L3INIT_MMC1_CLKCTRL_CLKSEL_SOURCE_SHIFT                                                          (24U)
#define CM_L3INIT_MMC1_CLKCTRL_CLKSEL_SOURCE_MASK                                                           (0x01000000U)
#define CM_L3INIT_MMC1_CLKCTRL_CLKSEL_SOURCE_SEL_128M                                                        (0U)
#define CM_L3INIT_MMC1_CLKCTRL_CLKSEL_SOURCE_SEL_192M                                                        (1U)

#define CM_L3INIT_MMC1_CLKCTRL_IDLEST_SHIFT                                                                 (16U)
#define CM_L3INIT_MMC1_CLKCTRL_IDLEST_MASK                                                                  (0x00030000U)
#define CM_L3INIT_MMC1_CLKCTRL_IDLEST_DISABLE                                                                (3U)
#define CM_L3INIT_MMC1_CLKCTRL_IDLEST_IDLE                                                                   (2U)
#define CM_L3INIT_MMC1_CLKCTRL_IDLEST_FUNC                                                                   (0U)
#define CM_L3INIT_MMC1_CLKCTRL_IDLEST_TRANS                                                                  (1U)

#define CM_L3INIT_MMC1_CLKCTRL_STBYST_SHIFT                                                                 (18U)
#define CM_L3INIT_MMC1_CLKCTRL_STBYST_MASK                                                                  (0x00040000U)
#define CM_L3INIT_MMC1_CLKCTRL_STBYST_FUNC                                                                   (0U)
#define CM_L3INIT_MMC1_CLKCTRL_STBYST_STANDBY                                                                (1U)

#define CM_L3INIT_MMC1_CLKCTRL_MODULEMODE_SHIFT                                                             (0U)
#define CM_L3INIT_MMC1_CLKCTRL_MODULEMODE_MASK                                                              (0x00000003U)
#define CM_L3INIT_MMC1_CLKCTRL_MODULEMODE_DISABLED                                                           (0U)
#define CM_L3INIT_MMC1_CLKCTRL_MODULEMODE_RESERVED_1                                                         (1U)
#define CM_L3INIT_MMC1_CLKCTRL_MODULEMODE_ENABLED                                                            (2U)
#define CM_L3INIT_MMC1_CLKCTRL_MODULEMODE_RESERVED                                                           (3U)

#define CM_L3INIT_MMC1_CLKCTRL_CLKSEL_DIV_SHIFT                                                             (25U)
#define CM_L3INIT_MMC1_CLKCTRL_CLKSEL_DIV_MASK                                                              (0x06000000U)
#define CM_L3INIT_MMC1_CLKCTRL_CLKSEL_DIV_DIV1                                                               (0U)
#define CM_L3INIT_MMC1_CLKCTRL_CLKSEL_DIV_DIV2                                                               (1U)
#define CM_L3INIT_MMC1_CLKCTRL_CLKSEL_DIV_DIV4                                                               (2U)
#define CM_L3INIT_MMC1_CLKCTRL_CLKSEL_DIV_RESERVED                                                           (3U)

#define CM_L3INIT_MMC1_CLKCTRL_RESERVED2_SHIFT                                                              (27U)
#define CM_L3INIT_MMC1_CLKCTRL_RESERVED2_MASK                                                               (0xf8000000U)

#define CM_L3INIT_MMC1_CLKCTRL_OPTFCLKEN_CLK32K_SHIFT                                                       (8U)
#define CM_L3INIT_MMC1_CLKCTRL_OPTFCLKEN_CLK32K_MASK                                                        (0x00000100U)
#define CM_L3INIT_MMC1_CLKCTRL_OPTFCLKEN_CLK32K_FCLK_EN                                                      (1U)
#define CM_L3INIT_MMC1_CLKCTRL_OPTFCLKEN_CLK32K_FCLK_DIS                                                     (0U)

#define CM_L3INIT_MMC1_CLKCTRL_RESERVED_SHIFT                                                               (2U)
#define CM_L3INIT_MMC1_CLKCTRL_RESERVED_MASK                                                                (0x000000fcU)

#define CM_L3INIT_MMC1_CLKCTRL_RESERVED3_SHIFT                                                              (9U)
#define CM_L3INIT_MMC1_CLKCTRL_RESERVED3_MASK                                                               (0x0000fe00U)

#define CM_L3INIT_MMC2_CLKCTRL_RESERVED1_SHIFT                                                              (19U)
#define CM_L3INIT_MMC2_CLKCTRL_RESERVED1_MASK                                                               (0x00f80000U)

#define CM_L3INIT_MMC2_CLKCTRL_CLKSEL_SOURCE_SHIFT                                                          (24U)
#define CM_L3INIT_MMC2_CLKCTRL_CLKSEL_SOURCE_MASK                                                           (0x01000000U)
#define CM_L3INIT_MMC2_CLKCTRL_CLKSEL_SOURCE_SEL_128M                                                        (0U)
#define CM_L3INIT_MMC2_CLKCTRL_CLKSEL_SOURCE_SEL_192M                                                        (1U)

#define CM_L3INIT_MMC2_CLKCTRL_IDLEST_SHIFT                                                                 (16U)
#define CM_L3INIT_MMC2_CLKCTRL_IDLEST_MASK                                                                  (0x00030000U)
#define CM_L3INIT_MMC2_CLKCTRL_IDLEST_DISABLE                                                                (3U)
#define CM_L3INIT_MMC2_CLKCTRL_IDLEST_IDLE                                                                   (2U)
#define CM_L3INIT_MMC2_CLKCTRL_IDLEST_FUNC                                                                   (0U)
#define CM_L3INIT_MMC2_CLKCTRL_IDLEST_TRANS                                                                  (1U)

#define CM_L3INIT_MMC2_CLKCTRL_STBYST_SHIFT                                                                 (18U)
#define CM_L3INIT_MMC2_CLKCTRL_STBYST_MASK                                                                  (0x00040000U)
#define CM_L3INIT_MMC2_CLKCTRL_STBYST_FUNC                                                                   (0U)
#define CM_L3INIT_MMC2_CLKCTRL_STBYST_STANDBY                                                                (1U)

#define CM_L3INIT_MMC2_CLKCTRL_MODULEMODE_SHIFT                                                             (0U)
#define CM_L3INIT_MMC2_CLKCTRL_MODULEMODE_MASK                                                              (0x00000003U)
#define CM_L3INIT_MMC2_CLKCTRL_MODULEMODE_DISABLED                                                           (0U)
#define CM_L3INIT_MMC2_CLKCTRL_MODULEMODE_RESERVED_1                                                         (1U)
#define CM_L3INIT_MMC2_CLKCTRL_MODULEMODE_ENABLED                                                            (2U)
#define CM_L3INIT_MMC2_CLKCTRL_MODULEMODE_RESERVED                                                           (3U)

#define CM_L3INIT_MMC2_CLKCTRL_CLKSEL_DIV_SHIFT                                                             (25U)
#define CM_L3INIT_MMC2_CLKCTRL_CLKSEL_DIV_MASK                                                              (0x06000000U)
#define CM_L3INIT_MMC2_CLKCTRL_CLKSEL_DIV_DIV1                                                               (0U)
#define CM_L3INIT_MMC2_CLKCTRL_CLKSEL_DIV_DIV2                                                               (1U)
#define CM_L3INIT_MMC2_CLKCTRL_CLKSEL_DIV_DIV4                                                               (2U)
#define CM_L3INIT_MMC2_CLKCTRL_CLKSEL_DIV_RESERVED                                                           (3U)

#define CM_L3INIT_MMC2_CLKCTRL_RESERVED2_SHIFT                                                              (27U)
#define CM_L3INIT_MMC2_CLKCTRL_RESERVED2_MASK                                                               (0xf8000000U)

#define CM_L3INIT_MMC2_CLKCTRL_OPTFCLKEN_CLK32K_SHIFT                                                       (8U)
#define CM_L3INIT_MMC2_CLKCTRL_OPTFCLKEN_CLK32K_MASK                                                        (0x00000100U)
#define CM_L3INIT_MMC2_CLKCTRL_OPTFCLKEN_CLK32K_FCLK_EN                                                      (1U)
#define CM_L3INIT_MMC2_CLKCTRL_OPTFCLKEN_CLK32K_FCLK_DIS                                                     (0U)

#define CM_L3INIT_MMC2_CLKCTRL_RESERVED_SHIFT                                                               (2U)
#define CM_L3INIT_MMC2_CLKCTRL_RESERVED_MASK                                                                (0x000000fcU)

#define CM_L3INIT_MMC2_CLKCTRL_RESERVED3_SHIFT                                                              (9U)
#define CM_L3INIT_MMC2_CLKCTRL_RESERVED3_MASK                                                               (0x0000fe00U)

#define CM_L3INIT_USB_OTG_SS2_CLKCTRL_IDLEST_SHIFT                                                          (16U)
#define CM_L3INIT_USB_OTG_SS2_CLKCTRL_IDLEST_MASK                                                           (0x00030000U)
#define CM_L3INIT_USB_OTG_SS2_CLKCTRL_IDLEST_DISABLE                                                         (3U)
#define CM_L3INIT_USB_OTG_SS2_CLKCTRL_IDLEST_IDLE                                                            (2U)
#define CM_L3INIT_USB_OTG_SS2_CLKCTRL_IDLEST_FUNC                                                            (0U)
#define CM_L3INIT_USB_OTG_SS2_CLKCTRL_IDLEST_TRANS                                                           (1U)

#define CM_L3INIT_USB_OTG_SS2_CLKCTRL_STBYST_SHIFT                                                          (18U)
#define CM_L3INIT_USB_OTG_SS2_CLKCTRL_STBYST_MASK                                                           (0x00040000U)
#define CM_L3INIT_USB_OTG_SS2_CLKCTRL_STBYST_FUNC                                                            (0U)
#define CM_L3INIT_USB_OTG_SS2_CLKCTRL_STBYST_STANDBY                                                         (1U)

#define CM_L3INIT_USB_OTG_SS2_CLKCTRL_MODULEMODE_SHIFT                                                      (0U)
#define CM_L3INIT_USB_OTG_SS2_CLKCTRL_MODULEMODE_MASK                                                       (0x00000003U)
#define CM_L3INIT_USB_OTG_SS2_CLKCTRL_MODULEMODE_DISABLED                                                    (0U)
#define CM_L3INIT_USB_OTG_SS2_CLKCTRL_MODULEMODE_AUTO                                                        (1U)
#define CM_L3INIT_USB_OTG_SS2_CLKCTRL_MODULEMODE_RESERVED_2                                                  (2U)
#define CM_L3INIT_USB_OTG_SS2_CLKCTRL_MODULEMODE_RESERVED                                                    (3U)

#define CM_L3INIT_USB_OTG_SS2_CLKCTRL_RESERVED_SHIFT                                                        (2U)
#define CM_L3INIT_USB_OTG_SS2_CLKCTRL_RESERVED_MASK                                                         (0x000000fcU)

#define CM_L3INIT_USB_OTG_SS2_CLKCTRL_OPTFCLKEN_REFCLK960M_SHIFT                                            (8U)
#define CM_L3INIT_USB_OTG_SS2_CLKCTRL_OPTFCLKEN_REFCLK960M_MASK                                             (0x00000100U)
#define CM_L3INIT_USB_OTG_SS2_CLKCTRL_OPTFCLKEN_REFCLK960M_FCLK_EN                                           (1U)
#define CM_L3INIT_USB_OTG_SS2_CLKCTRL_OPTFCLKEN_REFCLK960M_FCLK_DIS                                          (0U)

#define CM_L3INIT_USB_OTG_SS2_CLKCTRL_RESERVED2_SHIFT                                                       (19U)
#define CM_L3INIT_USB_OTG_SS2_CLKCTRL_RESERVED2_MASK                                                        (0xfff80000U)

#define CM_L3INIT_USB_OTG_SS2_CLKCTRL_RESERVED1_SHIFT                                                       (9U)
#define CM_L3INIT_USB_OTG_SS2_CLKCTRL_RESERVED1_MASK                                                        (0x0000fe00U)

#define CM_L3INIT_USB_OTG_SS3_CLKCTRL_IDLEST_SHIFT                                                          (16U)
#define CM_L3INIT_USB_OTG_SS3_CLKCTRL_IDLEST_MASK                                                           (0x00030000U)
#define CM_L3INIT_USB_OTG_SS3_CLKCTRL_IDLEST_DISABLE                                                         (3U)
#define CM_L3INIT_USB_OTG_SS3_CLKCTRL_IDLEST_IDLE                                                            (2U)
#define CM_L3INIT_USB_OTG_SS3_CLKCTRL_IDLEST_FUNC                                                            (0U)
#define CM_L3INIT_USB_OTG_SS3_CLKCTRL_IDLEST_TRANS                                                           (1U)

#define CM_L3INIT_USB_OTG_SS3_CLKCTRL_STBYST_SHIFT                                                          (18U)
#define CM_L3INIT_USB_OTG_SS3_CLKCTRL_STBYST_MASK                                                           (0x00040000U)
#define CM_L3INIT_USB_OTG_SS3_CLKCTRL_STBYST_FUNC                                                            (0U)
#define CM_L3INIT_USB_OTG_SS3_CLKCTRL_STBYST_STANDBY                                                         (1U)

#define CM_L3INIT_USB_OTG_SS3_CLKCTRL_MODULEMODE_SHIFT                                                      (0U)
#define CM_L3INIT_USB_OTG_SS3_CLKCTRL_MODULEMODE_MASK                                                       (0x00000003U)
#define CM_L3INIT_USB_OTG_SS3_CLKCTRL_MODULEMODE_DISABLED                                                    (0U)
#define CM_L3INIT_USB_OTG_SS3_CLKCTRL_MODULEMODE_AUTO                                                        (1U)
#define CM_L3INIT_USB_OTG_SS3_CLKCTRL_MODULEMODE_RESERVED_2                                                  (2U)
#define CM_L3INIT_USB_OTG_SS3_CLKCTRL_MODULEMODE_RESERVED                                                    (3U)

#define CM_L3INIT_USB_OTG_SS3_CLKCTRL_RESERVED2_SHIFT                                                       (19U)
#define CM_L3INIT_USB_OTG_SS3_CLKCTRL_RESERVED2_MASK                                                        (0xfff80000U)

#define CM_L3INIT_USB_OTG_SS3_CLKCTRL_RESERVED_SHIFT                                                        (2U)
#define CM_L3INIT_USB_OTG_SS3_CLKCTRL_RESERVED_MASK                                                         (0x0000fffcU)

#define CM_L3INIT_USB_OTG_SS4_CLKCTRL_IDLEST_SHIFT                                                          (16U)
#define CM_L3INIT_USB_OTG_SS4_CLKCTRL_IDLEST_MASK                                                           (0x00030000U)
#define CM_L3INIT_USB_OTG_SS4_CLKCTRL_IDLEST_DISABLE                                                         (3U)
#define CM_L3INIT_USB_OTG_SS4_CLKCTRL_IDLEST_IDLE                                                            (2U)
#define CM_L3INIT_USB_OTG_SS4_CLKCTRL_IDLEST_FUNC                                                            (0U)
#define CM_L3INIT_USB_OTG_SS4_CLKCTRL_IDLEST_TRANS                                                           (1U)

#define CM_L3INIT_USB_OTG_SS4_CLKCTRL_STBYST_SHIFT                                                          (18U)
#define CM_L3INIT_USB_OTG_SS4_CLKCTRL_STBYST_MASK                                                           (0x00040000U)
#define CM_L3INIT_USB_OTG_SS4_CLKCTRL_STBYST_FUNC                                                            (0U)
#define CM_L3INIT_USB_OTG_SS4_CLKCTRL_STBYST_STANDBY                                                         (1U)

#define CM_L3INIT_USB_OTG_SS4_CLKCTRL_MODULEMODE_SHIFT                                                      (0U)
#define CM_L3INIT_USB_OTG_SS4_CLKCTRL_MODULEMODE_MASK                                                       (0x00000003U)
#define CM_L3INIT_USB_OTG_SS4_CLKCTRL_MODULEMODE_DISABLED                                                    (0U)
#define CM_L3INIT_USB_OTG_SS4_CLKCTRL_MODULEMODE_AUTO                                                        (1U)
#define CM_L3INIT_USB_OTG_SS4_CLKCTRL_MODULEMODE_RESERVED_2                                                  (2U)
#define CM_L3INIT_USB_OTG_SS4_CLKCTRL_MODULEMODE_RESERVED                                                    (3U)

#define CM_L3INIT_USB_OTG_SS4_CLKCTRL_RESERVED2_SHIFT                                                       (19U)
#define CM_L3INIT_USB_OTG_SS4_CLKCTRL_RESERVED2_MASK                                                        (0xfff80000U)

#define CM_L3INIT_USB_OTG_SS4_CLKCTRL_RESERVED_SHIFT                                                        (2U)
#define CM_L3INIT_USB_OTG_SS4_CLKCTRL_RESERVED_MASK                                                         (0x0000fffcU)

#define CM_L3INIT_MLB_SS_CLKCTRL_RESERVED_SHIFT                                                             (2U)
#define CM_L3INIT_MLB_SS_CLKCTRL_RESERVED_MASK                                                              (0x0000fffcU)

#define CM_L3INIT_MLB_SS_CLKCTRL_IDLEST_SHIFT                                                               (16U)
#define CM_L3INIT_MLB_SS_CLKCTRL_IDLEST_MASK                                                                (0x00030000U)
#define CM_L3INIT_MLB_SS_CLKCTRL_IDLEST_DISABLE                                                              (3U)
#define CM_L3INIT_MLB_SS_CLKCTRL_IDLEST_IDLE                                                                 (2U)
#define CM_L3INIT_MLB_SS_CLKCTRL_IDLEST_FUNC                                                                 (0U)
#define CM_L3INIT_MLB_SS_CLKCTRL_IDLEST_TRANS                                                                (1U)

#define CM_L3INIT_MLB_SS_CLKCTRL_STBYST_SHIFT                                                               (18U)
#define CM_L3INIT_MLB_SS_CLKCTRL_STBYST_MASK                                                                (0x00040000U)
#define CM_L3INIT_MLB_SS_CLKCTRL_STBYST_FUNC                                                                 (0U)
#define CM_L3INIT_MLB_SS_CLKCTRL_STBYST_STANDBY                                                              (1U)

#define CM_L3INIT_MLB_SS_CLKCTRL_MODULEMODE_SHIFT                                                           (0U)
#define CM_L3INIT_MLB_SS_CLKCTRL_MODULEMODE_MASK                                                            (0x00000003U)
#define CM_L3INIT_MLB_SS_CLKCTRL_MODULEMODE_DISABLED                                                         (0U)
#define CM_L3INIT_MLB_SS_CLKCTRL_MODULEMODE_RESERVED_1                                                       (1U)
#define CM_L3INIT_MLB_SS_CLKCTRL_MODULEMODE_ENABLED                                                          (2U)
#define CM_L3INIT_MLB_SS_CLKCTRL_MODULEMODE_RESERVED                                                         (3U)

#define CM_L3INIT_MLB_SS_CLKCTRL_RESERVED1_SHIFT                                                            (19U)
#define CM_L3INIT_MLB_SS_CLKCTRL_RESERVED1_MASK                                                             (0xfff80000U)

#define CM_L3INIT_IEEE1500_2_OCP_CLKCTRL_RESERVED1_SHIFT                                                    (19U)
#define CM_L3INIT_IEEE1500_2_OCP_CLKCTRL_RESERVED1_MASK                                                     (0xfff80000U)

#define CM_L3INIT_IEEE1500_2_OCP_CLKCTRL_RESERVED_SHIFT                                                     (2U)
#define CM_L3INIT_IEEE1500_2_OCP_CLKCTRL_RESERVED_MASK                                                      (0x0000fffcU)

#define CM_L3INIT_IEEE1500_2_OCP_CLKCTRL_IDLEST_SHIFT                                                       (16U)
#define CM_L3INIT_IEEE1500_2_OCP_CLKCTRL_IDLEST_MASK                                                        (0x00030000U)
#define CM_L3INIT_IEEE1500_2_OCP_CLKCTRL_IDLEST_DISABLE                                                      (3U)
#define CM_L3INIT_IEEE1500_2_OCP_CLKCTRL_IDLEST_IDLE                                                         (2U)
#define CM_L3INIT_IEEE1500_2_OCP_CLKCTRL_IDLEST_FUNC                                                         (0U)
#define CM_L3INIT_IEEE1500_2_OCP_CLKCTRL_IDLEST_TRANS                                                        (1U)

#define CM_L3INIT_IEEE1500_2_OCP_CLKCTRL_STBYST_SHIFT                                                       (18U)
#define CM_L3INIT_IEEE1500_2_OCP_CLKCTRL_STBYST_MASK                                                        (0x00040000U)
#define CM_L3INIT_IEEE1500_2_OCP_CLKCTRL_STBYST_FUNC                                                         (0U)
#define CM_L3INIT_IEEE1500_2_OCP_CLKCTRL_STBYST_STANDBY                                                      (1U)

#define CM_L3INIT_IEEE1500_2_OCP_CLKCTRL_MODULEMODE_SHIFT                                                   (0U)
#define CM_L3INIT_IEEE1500_2_OCP_CLKCTRL_MODULEMODE_MASK                                                    (0x00000003U)
#define CM_L3INIT_IEEE1500_2_OCP_CLKCTRL_MODULEMODE_AUTO                                                     (1U)

#define CM_L3INIT_SATA_CLKCTRL_RESERVED_SHIFT                                                               (2U)
#define CM_L3INIT_SATA_CLKCTRL_RESERVED_MASK                                                                (0x000000fcU)

#define CM_L3INIT_SATA_CLKCTRL_RESERVED2_SHIFT                                                              (19U)
#define CM_L3INIT_SATA_CLKCTRL_RESERVED2_MASK                                                               (0xfff80000U)

#define CM_L3INIT_SATA_CLKCTRL_IDLEST_SHIFT                                                                 (16U)
#define CM_L3INIT_SATA_CLKCTRL_IDLEST_MASK                                                                  (0x00030000U)
#define CM_L3INIT_SATA_CLKCTRL_IDLEST_DISABLE                                                                (3U)
#define CM_L3INIT_SATA_CLKCTRL_IDLEST_IDLE                                                                   (2U)
#define CM_L3INIT_SATA_CLKCTRL_IDLEST_FUNC                                                                   (0U)
#define CM_L3INIT_SATA_CLKCTRL_IDLEST_TRANS                                                                  (1U)

#define CM_L3INIT_SATA_CLKCTRL_STBYST_SHIFT                                                                 (18U)
#define CM_L3INIT_SATA_CLKCTRL_STBYST_MASK                                                                  (0x00040000U)
#define CM_L3INIT_SATA_CLKCTRL_STBYST_FUNC                                                                   (0U)
#define CM_L3INIT_SATA_CLKCTRL_STBYST_STANDBY                                                                (1U)

#define CM_L3INIT_SATA_CLKCTRL_OPTFCLKEN_REF_CLK_SHIFT                                                      (8U)
#define CM_L3INIT_SATA_CLKCTRL_OPTFCLKEN_REF_CLK_MASK                                                       (0x00000100U)
#define CM_L3INIT_SATA_CLKCTRL_OPTFCLKEN_REF_CLK_FCLK_EN                                                     (1U)
#define CM_L3INIT_SATA_CLKCTRL_OPTFCLKEN_REF_CLK_FCLK_DIS                                                    (0U)

#define CM_L3INIT_SATA_CLKCTRL_RESERVED1_SHIFT                                                              (9U)
#define CM_L3INIT_SATA_CLKCTRL_RESERVED1_MASK                                                               (0x0000fe00U)

#define CM_L3INIT_SATA_CLKCTRL_MODULEMODE_SHIFT                                                             (0U)
#define CM_L3INIT_SATA_CLKCTRL_MODULEMODE_MASK                                                              (0x00000003U)
#define CM_L3INIT_SATA_CLKCTRL_MODULEMODE_DISABLED                                                           (0U)
#define CM_L3INIT_SATA_CLKCTRL_MODULEMODE_RESERVED_1                                                         (1U)
#define CM_L3INIT_SATA_CLKCTRL_MODULEMODE_ENABLED                                                            (2U)
#define CM_L3INIT_SATA_CLKCTRL_MODULEMODE_RESERVED                                                           (3U)

#define CM_PCIE_CLKSTCTRL_CLKTRCTRL_SHIFT                                                                   (0U)
#define CM_PCIE_CLKSTCTRL_CLKTRCTRL_MASK                                                                    (0x00000003U)
#define CM_PCIE_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                                                                 (0U)
#define CM_PCIE_CLKSTCTRL_CLKTRCTRL_SW_SLEEP                                                                 (1U)
#define CM_PCIE_CLKSTCTRL_CLKTRCTRL_SW_WKUP                                                                  (2U)
#define CM_PCIE_CLKSTCTRL_CLKTRCTRL_HW_AUTO                                                                  (3U)

#define CM_PCIE_CLKSTCTRL_CLKACTIVITY_PCIE_L3_GICLK_SHIFT                                                   (8U)
#define CM_PCIE_CLKSTCTRL_CLKACTIVITY_PCIE_L3_GICLK_MASK                                                    (0x00000100U)
#define CM_PCIE_CLKSTCTRL_CLKACTIVITY_PCIE_L3_GICLK_INACT                                                    (0U)
#define CM_PCIE_CLKSTCTRL_CLKACTIVITY_PCIE_L3_GICLK_ACT                                                      (1U)

#define CM_PCIE_CLKSTCTRL_RESERVED_SHIFT                                                                    (2U)
#define CM_PCIE_CLKSTCTRL_RESERVED_MASK                                                                     (0x000000fcU)

#define CM_PCIE_CLKSTCTRL_CLKACTIVITY_PCIE_PHY_GCLK_SHIFT                                                   (9U)
#define CM_PCIE_CLKSTCTRL_CLKACTIVITY_PCIE_PHY_GCLK_MASK                                                    (0x00000200U)
#define CM_PCIE_CLKSTCTRL_CLKACTIVITY_PCIE_PHY_GCLK_INACT                                                    (0U)
#define CM_PCIE_CLKSTCTRL_CLKACTIVITY_PCIE_PHY_GCLK_ACT                                                      (1U)

#define CM_PCIE_CLKSTCTRL_CLKACTIVITY_PCIE_PHY_DIV_GCLK_SHIFT                                               (10U)
#define CM_PCIE_CLKSTCTRL_CLKACTIVITY_PCIE_PHY_DIV_GCLK_MASK                                                (0x00000400U)
#define CM_PCIE_CLKSTCTRL_CLKACTIVITY_PCIE_PHY_DIV_GCLK_INACT                                                (0U)
#define CM_PCIE_CLKSTCTRL_CLKACTIVITY_PCIE_PHY_DIV_GCLK_ACT                                                  (1U)

#define CM_PCIE_CLKSTCTRL_CLKACTIVITY_PCIE_REF_GFCLK_SHIFT                                                  (11U)
#define CM_PCIE_CLKSTCTRL_CLKACTIVITY_PCIE_REF_GFCLK_MASK                                                   (0x00000800U)
#define CM_PCIE_CLKSTCTRL_CLKACTIVITY_PCIE_REF_GFCLK_INACT                                                   (0U)
#define CM_PCIE_CLKSTCTRL_CLKACTIVITY_PCIE_REF_GFCLK_ACT                                                     (1U)

#define CM_PCIE_CLKSTCTRL_CLKACTIVITY_PCIE_SYS_GFCLK_SHIFT                                                  (12U)
#define CM_PCIE_CLKSTCTRL_CLKACTIVITY_PCIE_SYS_GFCLK_MASK                                                   (0x00001000U)
#define CM_PCIE_CLKSTCTRL_CLKACTIVITY_PCIE_SYS_GFCLK_INACT                                                   (0U)
#define CM_PCIE_CLKSTCTRL_CLKACTIVITY_PCIE_SYS_GFCLK_ACT                                                     (1U)

#define CM_PCIE_CLKSTCTRL_CLKACTIVITY_PCIE_32K_GFCLK_SHIFT                                                  (13U)
#define CM_PCIE_CLKSTCTRL_CLKACTIVITY_PCIE_32K_GFCLK_MASK                                                   (0x00002000U)
#define CM_PCIE_CLKSTCTRL_CLKACTIVITY_PCIE_32K_GFCLK_INACT                                                   (0U)
#define CM_PCIE_CLKSTCTRL_CLKACTIVITY_PCIE_32K_GFCLK_ACT                                                     (1U)

#define CM_PCIE_CLKSTCTRL_RESERVED1_SHIFT                                                                   (14U)
#define CM_PCIE_CLKSTCTRL_RESERVED1_MASK                                                                    (0xffffc000U)

#define CM_PCIE_STATICDEP_DSP1_STATDEP_SHIFT                                                                (1U)
#define CM_PCIE_STATICDEP_DSP1_STATDEP_MASK                                                                 (0x00000002U)
#define CM_PCIE_STATICDEP_DSP1_STATDEP_ENABLED                                                               (1U)
#define CM_PCIE_STATICDEP_DSP1_STATDEP_DISABLED                                                              (0U)

#define CM_PCIE_STATICDEP_IVA_STATDEP_SHIFT                                                                 (2U)
#define CM_PCIE_STATICDEP_IVA_STATDEP_MASK                                                                  (0x00000004U)
#define CM_PCIE_STATICDEP_IVA_STATDEP_ENABLED                                                                (1U)
#define CM_PCIE_STATICDEP_IVA_STATDEP_DISABLED                                                               (0U)

#define CM_PCIE_STATICDEP_RESERVED_SHIFT                                                                    (3U)
#define CM_PCIE_STATICDEP_RESERVED_MASK                                                                     (0x00000008U)

#define CM_PCIE_STATICDEP_EMIF_STATDEP_SHIFT                                                                (4U)
#define CM_PCIE_STATICDEP_EMIF_STATDEP_MASK                                                                 (0x00000010U)
#define CM_PCIE_STATICDEP_EMIF_STATDEP_ENABLED                                                               (1U)
#define CM_PCIE_STATICDEP_EMIF_STATDEP_DISABLED                                                              (0U)

#define CM_PCIE_STATICDEP_L3INIT_STATDEP_SHIFT                                                              (7U)
#define CM_PCIE_STATICDEP_L3INIT_STATDEP_MASK                                                               (0x00000080U)
#define CM_PCIE_STATICDEP_L3INIT_STATDEP_ENABLED                                                             (1U)
#define CM_PCIE_STATICDEP_L3INIT_STATDEP_DISABLED                                                            (0U)

#define CM_PCIE_STATICDEP_DSS_STATDEP_SHIFT                                                                 (8U)
#define CM_PCIE_STATICDEP_DSS_STATDEP_MASK                                                                  (0x00000100U)
#define CM_PCIE_STATICDEP_DSS_STATDEP_ENABLED                                                                (1U)
#define CM_PCIE_STATICDEP_DSS_STATDEP_DISABLED                                                               (0U)

#define CM_PCIE_STATICDEP_CAM_STATDEP_SHIFT                                                                 (9U)
#define CM_PCIE_STATICDEP_CAM_STATDEP_MASK                                                                  (0x00000200U)
#define CM_PCIE_STATICDEP_CAM_STATDEP_ENABLED                                                                (1U)
#define CM_PCIE_STATICDEP_CAM_STATDEP_DISABLED                                                               (0U)

#define CM_PCIE_STATICDEP_GPU_STATDEP_SHIFT                                                                 (10U)
#define CM_PCIE_STATICDEP_GPU_STATDEP_MASK                                                                  (0x00000400U)
#define CM_PCIE_STATICDEP_GPU_STATDEP_ENABLED                                                                (1U)
#define CM_PCIE_STATICDEP_GPU_STATDEP_DISABLED                                                               (0U)

#define CM_PCIE_STATICDEP_SDMA_STATDEP_SHIFT                                                                (11U)
#define CM_PCIE_STATICDEP_SDMA_STATDEP_MASK                                                                 (0x00000800U)
#define CM_PCIE_STATICDEP_SDMA_STATDEP_DISABLED                                                              (0U)

#define CM_PCIE_STATICDEP_L4CFG_STATDEP_SHIFT                                                               (12U)
#define CM_PCIE_STATICDEP_L4CFG_STATDEP_MASK                                                                (0x00001000U)
#define CM_PCIE_STATICDEP_L4CFG_STATDEP_ENABLED                                                              (1U)
#define CM_PCIE_STATICDEP_L4CFG_STATDEP_DISABLED                                                             (0U)

#define CM_PCIE_STATICDEP_L4PER_STATDEP_SHIFT                                                               (13U)
#define CM_PCIE_STATICDEP_L4PER_STATDEP_MASK                                                                (0x00002000U)
#define CM_PCIE_STATICDEP_L4PER_STATDEP_ENABLED                                                              (1U)
#define CM_PCIE_STATICDEP_L4PER_STATDEP_DISABLED                                                             (0U)

#define CM_PCIE_STATICDEP_L4SEC_STATDEP_SHIFT                                                               (14U)
#define CM_PCIE_STATICDEP_L4SEC_STATDEP_MASK                                                                (0x00004000U)
#define CM_PCIE_STATICDEP_L4SEC_STATDEP_ENABLED                                                              (1U)
#define CM_PCIE_STATICDEP_L4SEC_STATDEP_DISABLED                                                             (0U)

#define CM_PCIE_STATICDEP_COREAON_STATDEP_SHIFT                                                             (16U)
#define CM_PCIE_STATICDEP_COREAON_STATDEP_MASK                                                              (0x00010000U)
#define CM_PCIE_STATICDEP_COREAON_STATDEP_DISABLED                                                           (0U)

#define CM_PCIE_STATICDEP_CUSTEFUSE_STATDEP_SHIFT                                                           (17U)
#define CM_PCIE_STATICDEP_CUSTEFUSE_STATDEP_MASK                                                            (0x00020000U)
#define CM_PCIE_STATICDEP_CUSTEFUSE_STATDEP_DISABLED                                                         (0U)

#define CM_PCIE_STATICDEP_DSP2_STATDEP_SHIFT                                                                (18U)
#define CM_PCIE_STATICDEP_DSP2_STATDEP_MASK                                                                 (0x00040000U)
#define CM_PCIE_STATICDEP_DSP2_STATDEP_ENABLED                                                               (1U)
#define CM_PCIE_STATICDEP_DSP2_STATDEP_DISABLED                                                              (0U)

#define CM_PCIE_STATICDEP_EVE1_STATDEP_SHIFT                                                                (19U)
#define CM_PCIE_STATICDEP_EVE1_STATDEP_MASK                                                                 (0x00080000U)
#define CM_PCIE_STATICDEP_EVE1_STATDEP_ENABLED                                                               (1U)
#define CM_PCIE_STATICDEP_EVE1_STATDEP_DISABLED                                                              (0U)

#define CM_PCIE_STATICDEP_EVE2_STATDEP_SHIFT                                                                (20U)
#define CM_PCIE_STATICDEP_EVE2_STATDEP_MASK                                                                 (0x00100000U)
#define CM_PCIE_STATICDEP_EVE2_STATDEP_ENABLED                                                               (1U)
#define CM_PCIE_STATICDEP_EVE2_STATDEP_DISABLED                                                              (0U)

#define CM_PCIE_STATICDEP_EVE3_STATDEP_SHIFT                                                                (21U)
#define CM_PCIE_STATICDEP_EVE3_STATDEP_MASK                                                                 (0x00200000U)
#define CM_PCIE_STATICDEP_EVE3_STATDEP_ENABLED                                                               (1U)
#define CM_PCIE_STATICDEP_EVE3_STATDEP_DISABLED                                                              (0U)

#define CM_PCIE_STATICDEP_EVE4_STATDEP_SHIFT                                                                (22U)
#define CM_PCIE_STATICDEP_EVE4_STATDEP_MASK                                                                 (0x00400000U)
#define CM_PCIE_STATICDEP_EVE4_STATDEP_ENABLED                                                               (1U)
#define CM_PCIE_STATICDEP_EVE4_STATDEP_DISABLED                                                              (0U)

#define CM_PCIE_STATICDEP_IPU1_STATDEP_SHIFT                                                                (23U)
#define CM_PCIE_STATICDEP_IPU1_STATDEP_MASK                                                                 (0x00800000U)
#define CM_PCIE_STATICDEP_IPU1_STATDEP_ENABLED                                                               (1U)
#define CM_PCIE_STATICDEP_IPU1_STATDEP_DISABLED                                                              (0U)

#define CM_PCIE_STATICDEP_IPU_STATDEP_SHIFT                                                                 (24U)
#define CM_PCIE_STATICDEP_IPU_STATDEP_MASK                                                                  (0x01000000U)
#define CM_PCIE_STATICDEP_IPU_STATDEP_ENABLED                                                                (1U)
#define CM_PCIE_STATICDEP_IPU_STATDEP_DISABLED                                                               (0U)

#define CM_PCIE_STATICDEP_GMAC_STATDEP_SHIFT                                                                (25U)
#define CM_PCIE_STATICDEP_GMAC_STATDEP_MASK                                                                 (0x02000000U)
#define CM_PCIE_STATICDEP_GMAC_STATDEP_ENABLED                                                               (1U)
#define CM_PCIE_STATICDEP_GMAC_STATDEP_DISABLED                                                              (0U)

#define CM_PCIE_STATICDEP_L4PER2_STATDEP_SHIFT                                                              (26U)
#define CM_PCIE_STATICDEP_L4PER2_STATDEP_MASK                                                               (0x04000000U)
#define CM_PCIE_STATICDEP_L4PER2_STATDEP_ENABLED                                                             (1U)
#define CM_PCIE_STATICDEP_L4PER2_STATDEP_DISABLED                                                            (0U)

#define CM_PCIE_STATICDEP_L4PER3_STATDEP_SHIFT                                                              (27U)
#define CM_PCIE_STATICDEP_L4PER3_STATDEP_MASK                                                               (0x08000000U)
#define CM_PCIE_STATICDEP_L4PER3_STATDEP_ENABLED                                                             (1U)
#define CM_PCIE_STATICDEP_L4PER3_STATDEP_DISABLED                                                            (0U)

#define CM_PCIE_STATICDEP_VPE_STATDEP_SHIFT                                                                 (28U)
#define CM_PCIE_STATICDEP_VPE_STATDEP_MASK                                                                  (0x10000000U)
#define CM_PCIE_STATICDEP_VPE_STATDEP_ENABLED                                                                (1U)
#define CM_PCIE_STATICDEP_VPE_STATDEP_DISABLED                                                               (0U)

#define CM_PCIE_STATICDEP_ATL_STATDEP_SHIFT                                                                 (30U)
#define CM_PCIE_STATICDEP_ATL_STATDEP_MASK                                                                  (0x40000000U)
#define CM_PCIE_STATICDEP_ATL_STATDEP_ENABLED                                                                (1U)
#define CM_PCIE_STATICDEP_ATL_STATDEP_DISABLED                                                               (0U)

#define CM_PCIE_STATICDEP_RESERVED1_SHIFT                                                                   (0U)
#define CM_PCIE_STATICDEP_RESERVED1_MASK                                                                    (0x00000001U)

#define CM_PCIE_STATICDEP_RESERVED2_SHIFT                                                                   (5U)
#define CM_PCIE_STATICDEP_RESERVED2_MASK                                                                    (0x00000060U)

#define CM_PCIE_STATICDEP_RESERVED3_SHIFT                                                                   (15U)
#define CM_PCIE_STATICDEP_RESERVED3_MASK                                                                    (0x00008000U)

#define CM_PCIE_STATICDEP_RESERVED4_SHIFT                                                                   (29U)
#define CM_PCIE_STATICDEP_RESERVED4_MASK                                                                    (0x20000000U)

#define CM_PCIE_STATICDEP_RESERVED5_SHIFT                                                                   (31U)
#define CM_PCIE_STATICDEP_RESERVED5_MASK                                                                    (0x80000000U)

#define CM_PCIE_PCIESS1_CLKCTRL_IDLEST_SHIFT                                                                (16U)
#define CM_PCIE_PCIESS1_CLKCTRL_IDLEST_MASK                                                                 (0x00030000U)
#define CM_PCIE_PCIESS1_CLKCTRL_IDLEST_DISABLE                                                               (3U)
#define CM_PCIE_PCIESS1_CLKCTRL_IDLEST_IDLE                                                                  (2U)
#define CM_PCIE_PCIESS1_CLKCTRL_IDLEST_FUNC                                                                  (0U)
#define CM_PCIE_PCIESS1_CLKCTRL_IDLEST_TRANS                                                                 (1U)

#define CM_PCIE_PCIESS1_CLKCTRL_STBYST_SHIFT                                                                (18U)
#define CM_PCIE_PCIESS1_CLKCTRL_STBYST_MASK                                                                 (0x00040000U)
#define CM_PCIE_PCIESS1_CLKCTRL_STBYST_FUNC                                                                  (0U)
#define CM_PCIE_PCIESS1_CLKCTRL_STBYST_STANDBY                                                               (1U)

#define CM_PCIE_PCIESS1_CLKCTRL_RESERVED1_SHIFT                                                             (19U)
#define CM_PCIE_PCIESS1_CLKCTRL_RESERVED1_MASK                                                              (0xfff80000U)

#define CM_PCIE_PCIESS1_CLKCTRL_OPTFCLKEN_32KHZ_SHIFT                                                       (8U)
#define CM_PCIE_PCIESS1_CLKCTRL_OPTFCLKEN_32KHZ_MASK                                                        (0x00000100U)
#define CM_PCIE_PCIESS1_CLKCTRL_OPTFCLKEN_32KHZ_FCLK_EN                                                      (1U)
#define CM_PCIE_PCIESS1_CLKCTRL_OPTFCLKEN_32KHZ_FCLK_DIS                                                     (0U)

#define CM_PCIE_PCIESS1_CLKCTRL_RESERVED_SHIFT                                                              (2U)
#define CM_PCIE_PCIESS1_CLKCTRL_RESERVED_MASK                                                               (0x000000fcU)

#define CM_PCIE_PCIESS1_CLKCTRL_OPTFCLKEN_PCIEPHY_CLK_SHIFT                                                 (9U)
#define CM_PCIE_PCIESS1_CLKCTRL_OPTFCLKEN_PCIEPHY_CLK_MASK                                                  (0x00000200U)
#define CM_PCIE_PCIESS1_CLKCTRL_OPTFCLKEN_PCIEPHY_CLK_FCLK_EN                                                (1U)
#define CM_PCIE_PCIESS1_CLKCTRL_OPTFCLKEN_PCIEPHY_CLK_FCLK_DIS                                               (0U)

#define CM_PCIE_PCIESS1_CLKCTRL_OPTFCLKEN_PCIEPHY_CLK_DIV_SHIFT                                             (10U)
#define CM_PCIE_PCIESS1_CLKCTRL_OPTFCLKEN_PCIEPHY_CLK_DIV_MASK                                              (0x00000400U)
#define CM_PCIE_PCIESS1_CLKCTRL_OPTFCLKEN_PCIEPHY_CLK_DIV_FCLK_EN                                            (1U)
#define CM_PCIE_PCIESS1_CLKCTRL_OPTFCLKEN_PCIEPHY_CLK_DIV_FCLK_DIS                                           (0U)

#define CM_PCIE_PCIESS1_CLKCTRL_RESERVED2_SHIFT                                                             (11U)
#define CM_PCIE_PCIESS1_CLKCTRL_RESERVED2_MASK                                                              (0x0000f800U)

#define CM_PCIE_PCIESS1_CLKCTRL_MODULEMODE_SHIFT                                                            (0U)
#define CM_PCIE_PCIESS1_CLKCTRL_MODULEMODE_MASK                                                             (0x00000003U)
#define CM_PCIE_PCIESS1_CLKCTRL_MODULEMODE_DISABLED                                                          (0U)
#define CM_PCIE_PCIESS1_CLKCTRL_MODULEMODE_RESERVED_1                                                        (1U)
#define CM_PCIE_PCIESS1_CLKCTRL_MODULEMODE_ENABLED                                                           (2U)
#define CM_PCIE_PCIESS1_CLKCTRL_MODULEMODE_RESERVED                                                          (3U)

#define CM_PCIE_PCIESS2_CLKCTRL_IDLEST_SHIFT                                                                (16U)
#define CM_PCIE_PCIESS2_CLKCTRL_IDLEST_MASK                                                                 (0x00030000U)
#define CM_PCIE_PCIESS2_CLKCTRL_IDLEST_DISABLE                                                               (3U)
#define CM_PCIE_PCIESS2_CLKCTRL_IDLEST_IDLE                                                                  (2U)
#define CM_PCIE_PCIESS2_CLKCTRL_IDLEST_FUNC                                                                  (0U)
#define CM_PCIE_PCIESS2_CLKCTRL_IDLEST_TRANS                                                                 (1U)

#define CM_PCIE_PCIESS2_CLKCTRL_STBYST_SHIFT                                                                (18U)
#define CM_PCIE_PCIESS2_CLKCTRL_STBYST_MASK                                                                 (0x00040000U)
#define CM_PCIE_PCIESS2_CLKCTRL_STBYST_FUNC                                                                  (0U)
#define CM_PCIE_PCIESS2_CLKCTRL_STBYST_STANDBY                                                               (1U)

#define CM_PCIE_PCIESS2_CLKCTRL_RESERVED1_SHIFT                                                             (19U)
#define CM_PCIE_PCIESS2_CLKCTRL_RESERVED1_MASK                                                              (0xfff80000U)

#define CM_PCIE_PCIESS2_CLKCTRL_OPTFCLKEN_32KHZ_SHIFT                                                       (8U)
#define CM_PCIE_PCIESS2_CLKCTRL_OPTFCLKEN_32KHZ_MASK                                                        (0x00000100U)
#define CM_PCIE_PCIESS2_CLKCTRL_OPTFCLKEN_32KHZ_FCLK_EN                                                      (1U)
#define CM_PCIE_PCIESS2_CLKCTRL_OPTFCLKEN_32KHZ_FCLK_DIS                                                     (0U)

#define CM_PCIE_PCIESS2_CLKCTRL_OPTFCLKEN_PCIEPHY_CLK_SHIFT                                                 (9U)
#define CM_PCIE_PCIESS2_CLKCTRL_OPTFCLKEN_PCIEPHY_CLK_MASK                                                  (0x00000200U)
#define CM_PCIE_PCIESS2_CLKCTRL_OPTFCLKEN_PCIEPHY_CLK_FCLK_EN                                                (1U)
#define CM_PCIE_PCIESS2_CLKCTRL_OPTFCLKEN_PCIEPHY_CLK_FCLK_DIS                                               (0U)

#define CM_PCIE_PCIESS2_CLKCTRL_OPTFCLKEN_PCIEPHY_CLK_DIV_SHIFT                                             (10U)
#define CM_PCIE_PCIESS2_CLKCTRL_OPTFCLKEN_PCIEPHY_CLK_DIV_MASK                                              (0x00000400U)
#define CM_PCIE_PCIESS2_CLKCTRL_OPTFCLKEN_PCIEPHY_CLK_DIV_FCLK_EN                                            (1U)
#define CM_PCIE_PCIESS2_CLKCTRL_OPTFCLKEN_PCIEPHY_CLK_DIV_FCLK_DIS                                           (0U)

#define CM_PCIE_PCIESS2_CLKCTRL_RESERVED_SHIFT                                                              (2U)
#define CM_PCIE_PCIESS2_CLKCTRL_RESERVED_MASK                                                               (0x000000fcU)

#define CM_PCIE_PCIESS2_CLKCTRL_RESERVED2_SHIFT                                                             (11U)
#define CM_PCIE_PCIESS2_CLKCTRL_RESERVED2_MASK                                                              (0x0000f800U)

#define CM_PCIE_PCIESS2_CLKCTRL_MODULEMODE_SHIFT                                                            (0U)
#define CM_PCIE_PCIESS2_CLKCTRL_MODULEMODE_MASK                                                             (0x00000003U)
#define CM_PCIE_PCIESS2_CLKCTRL_MODULEMODE_DISABLED                                                          (0U)
#define CM_PCIE_PCIESS2_CLKCTRL_MODULEMODE_RESERVED_1                                                        (1U)
#define CM_PCIE_PCIESS2_CLKCTRL_MODULEMODE_ENABLED                                                           (2U)
#define CM_PCIE_PCIESS2_CLKCTRL_MODULEMODE_RESERVED                                                          (3U)

#define CM_GMAC_CLKSTCTRL_CLKTRCTRL_SHIFT                                                                   (0U)
#define CM_GMAC_CLKSTCTRL_CLKTRCTRL_MASK                                                                    (0x00000003U)
#define CM_GMAC_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                                                                 (0U)
#define CM_GMAC_CLKSTCTRL_CLKTRCTRL_SW_SLEEP                                                                 (1U)
#define CM_GMAC_CLKSTCTRL_CLKTRCTRL_SW_WKUP                                                                  (2U)
#define CM_GMAC_CLKSTCTRL_CLKTRCTRL_HW_AUTO                                                                  (3U)

#define CM_GMAC_CLKSTCTRL_CLKACTIVITY_GMII_250MHZ_CLK_SHIFT                                                 (8U)
#define CM_GMAC_CLKSTCTRL_CLKACTIVITY_GMII_250MHZ_CLK_MASK                                                  (0x00000100U)
#define CM_GMAC_CLKSTCTRL_CLKACTIVITY_GMII_250MHZ_CLK_INACT                                                  (0U)
#define CM_GMAC_CLKSTCTRL_CLKACTIVITY_GMII_250MHZ_CLK_ACT                                                    (1U)

#define CM_GMAC_CLKSTCTRL_CLKACTIVITY_RGMII_5MHZ_CLK_SHIFT                                                  (9U)
#define CM_GMAC_CLKSTCTRL_CLKACTIVITY_RGMII_5MHZ_CLK_MASK                                                   (0x00000200U)
#define CM_GMAC_CLKSTCTRL_CLKACTIVITY_RGMII_5MHZ_CLK_INACT                                                   (0U)
#define CM_GMAC_CLKSTCTRL_CLKACTIVITY_RGMII_5MHZ_CLK_ACT                                                     (1U)

#define CM_GMAC_CLKSTCTRL_CLKACTIVITY_GMAC_RFT_CLK_SHIFT                                                    (11U)
#define CM_GMAC_CLKSTCTRL_CLKACTIVITY_GMAC_RFT_CLK_MASK                                                     (0x00000800U)
#define CM_GMAC_CLKSTCTRL_CLKACTIVITY_GMAC_RFT_CLK_INACT                                                     (0U)
#define CM_GMAC_CLKSTCTRL_CLKACTIVITY_GMAC_RFT_CLK_ACT                                                       (1U)

#define CM_GMAC_CLKSTCTRL_CLKACTIVITY_GMAC_MAIN_CLK_SHIFT                                                   (12U)
#define CM_GMAC_CLKSTCTRL_CLKACTIVITY_GMAC_MAIN_CLK_MASK                                                    (0x00001000U)
#define CM_GMAC_CLKSTCTRL_CLKACTIVITY_GMAC_MAIN_CLK_INACT                                                    (0U)
#define CM_GMAC_CLKSTCTRL_CLKACTIVITY_GMAC_MAIN_CLK_ACT                                                      (1U)

#define CM_GMAC_CLKSTCTRL_CLKACTIVITY_RMII_50MHZ_CLK_SHIFT                                                  (10U)
#define CM_GMAC_CLKSTCTRL_CLKACTIVITY_RMII_50MHZ_CLK_MASK                                                   (0x00000400U)
#define CM_GMAC_CLKSTCTRL_CLKACTIVITY_RMII_50MHZ_CLK_INACT                                                   (0U)
#define CM_GMAC_CLKSTCTRL_CLKACTIVITY_RMII_50MHZ_CLK_ACT                                                     (1U)

#define CM_GMAC_CLKSTCTRL_RESERVED_SHIFT                                                                    (2U)
#define CM_GMAC_CLKSTCTRL_RESERVED_MASK                                                                     (0x000000fcU)

#define CM_GMAC_CLKSTCTRL_RESERVED1_SHIFT                                                                   (13U)
#define CM_GMAC_CLKSTCTRL_RESERVED1_MASK                                                                    (0xffffe000U)

#define CM_GMAC_STATICDEP_EMIF_STATDEP_SHIFT                                                                (4U)
#define CM_GMAC_STATICDEP_EMIF_STATDEP_MASK                                                                 (0x00000010U)
#define CM_GMAC_STATICDEP_EMIF_STATDEP_ENABLED                                                               (1U)
#define CM_GMAC_STATICDEP_EMIF_STATDEP_DISABLED                                                              (0U)

#define CM_GMAC_STATICDEP_L3MAIN1_STATDEP_SHIFT                                                             (5U)
#define CM_GMAC_STATICDEP_L3MAIN1_STATDEP_MASK                                                              (0x00000020U)
#define CM_GMAC_STATICDEP_L3MAIN1_STATDEP_ENABLED                                                            (1U)

#define CM_GMAC_STATICDEP_L4PER2_STATDEP_SHIFT                                                              (26U)
#define CM_GMAC_STATICDEP_L4PER2_STATDEP_MASK                                                               (0x04000000U)
#define CM_GMAC_STATICDEP_L4PER2_STATDEP_ENABLED                                                             (1U)
#define CM_GMAC_STATICDEP_L4PER2_STATDEP_DISABLED                                                            (0U)

#define CM_GMAC_STATICDEP_RESERVED_SHIFT                                                                    (0U)
#define CM_GMAC_STATICDEP_RESERVED_MASK                                                                     (0x0000000fU)

#define CM_GMAC_STATICDEP_RESERVED3_SHIFT                                                                   (27U)
#define CM_GMAC_STATICDEP_RESERVED3_MASK                                                                    (0xf8000000U)

#define CM_GMAC_STATICDEP_RESERVED1_SHIFT                                                                   (6U)
#define CM_GMAC_STATICDEP_RESERVED1_MASK                                                                    (0x03ffffc0U)

#define CM_GMAC_DYNAMICDEP_L3MAIN1_DYNDEP_SHIFT                                                             (5U)
#define CM_GMAC_DYNAMICDEP_L3MAIN1_DYNDEP_MASK                                                              (0x00000020U)
#define CM_GMAC_DYNAMICDEP_L3MAIN1_DYNDEP_DISABLED                                                           (0U)

#define CM_GMAC_DYNAMICDEP_RESERVED_SHIFT                                                                   (0U)
#define CM_GMAC_DYNAMICDEP_RESERVED_MASK                                                                    (0x0000001fU)

#define CM_GMAC_DYNAMICDEP_RESERVED1_SHIFT                                                                  (6U)
#define CM_GMAC_DYNAMICDEP_RESERVED1_MASK                                                                   (0xffffffc0U)

#define CM_GMAC_GMAC_CLKCTRL_RESERVED_SHIFT                                                                 (2U)
#define CM_GMAC_GMAC_CLKCTRL_RESERVED_MASK                                                                  (0x0000fffcU)

#define CM_GMAC_GMAC_CLKCTRL_RESERVED1_SHIFT                                                                (19U)
#define CM_GMAC_GMAC_CLKCTRL_RESERVED1_MASK                                                                 (0x00f80000U)

#define CM_GMAC_GMAC_CLKCTRL_CLKSEL_REF_SHIFT                                                               (24U)
#define CM_GMAC_GMAC_CLKCTRL_CLKSEL_REF_MASK                                                                (0x01000000U)
#define CM_GMAC_GMAC_CLKCTRL_CLKSEL_REF_SEL_GMAC_RMII_HS_CLK                                                 (0U)
#define CM_GMAC_GMAC_CLKCTRL_CLKSEL_REF_SEL_GMAC_RMII_CLK                                                    (1U)

#define CM_GMAC_GMAC_CLKCTRL_IDLEST_SHIFT                                                                   (16U)
#define CM_GMAC_GMAC_CLKCTRL_IDLEST_MASK                                                                    (0x00030000U)
#define CM_GMAC_GMAC_CLKCTRL_IDLEST_DISABLE                                                                  (3U)
#define CM_GMAC_GMAC_CLKCTRL_IDLEST_IDLE                                                                     (2U)
#define CM_GMAC_GMAC_CLKCTRL_IDLEST_FUNC                                                                     (0U)
#define CM_GMAC_GMAC_CLKCTRL_IDLEST_TRANS                                                                    (1U)

#define CM_GMAC_GMAC_CLKCTRL_STBYST_SHIFT                                                                   (18U)
#define CM_GMAC_GMAC_CLKCTRL_STBYST_MASK                                                                    (0x00040000U)
#define CM_GMAC_GMAC_CLKCTRL_STBYST_FUNC                                                                     (0U)
#define CM_GMAC_GMAC_CLKCTRL_STBYST_STANDBY                                                                  (1U)

#define CM_GMAC_GMAC_CLKCTRL_MODULEMODE_SHIFT                                                               (0U)
#define CM_GMAC_GMAC_CLKCTRL_MODULEMODE_MASK                                                                (0x00000003U)
#define CM_GMAC_GMAC_CLKCTRL_MODULEMODE_DISABLED                                                             (0U)
#define CM_GMAC_GMAC_CLKCTRL_MODULEMODE_RESERVED_1                                                           (1U)
#define CM_GMAC_GMAC_CLKCTRL_MODULEMODE_ENABLED                                                              (2U)
#define CM_GMAC_GMAC_CLKCTRL_MODULEMODE_RESERVED                                                             (3U)

#define CM_GMAC_GMAC_CLKCTRL_CLKSEL_RFT_SHIFT                                                               (25U)
#define CM_GMAC_GMAC_CLKCTRL_CLKSEL_RFT_MASK                                                                (0x0e000000U)
#define CM_GMAC_GMAC_CLKCTRL_CLKSEL_RFT_SEL_VIDEO1_CLK                                                       (0U)
#define CM_GMAC_GMAC_CLKCTRL_CLKSEL_RFT_SEL_VIDEO2_CLK                                                       (1U)
#define CM_GMAC_GMAC_CLKCTRL_CLKSEL_RFT_SEL_PER_ABE_X1_GFCLK                                                 (2U)
#define CM_GMAC_GMAC_CLKCTRL_CLKSEL_RFT_SEL_HDMI_CLK                                                         (3U)
#define CM_GMAC_GMAC_CLKCTRL_CLKSEL_RFT_SEL_L3_ICLK                                                          (4U)
#define CM_GMAC_GMAC_CLKCTRL_CLKSEL_RFT_RESERVED                                                             (5U)
#define CM_GMAC_GMAC_CLKCTRL_CLKSEL_RFT_RESERVED1                                                            (6U)
#define CM_GMAC_GMAC_CLKCTRL_CLKSEL_RFT_RESERVED2                                                            (7U)

#define CM_GMAC_GMAC_CLKCTRL_RESERVED2_SHIFT                                                                (28U)
#define CM_GMAC_GMAC_CLKCTRL_RESERVED2_MASK                                                                 (0xf0000000U)

#define CM_L3INIT_OCP2SCP1_CLKCTRL_IDLEST_SHIFT                                                             (16U)
#define CM_L3INIT_OCP2SCP1_CLKCTRL_IDLEST_MASK                                                              (0x00030000U)
#define CM_L3INIT_OCP2SCP1_CLKCTRL_IDLEST_DISABLE                                                            (3U)
#define CM_L3INIT_OCP2SCP1_CLKCTRL_IDLEST_IDLE                                                               (2U)
#define CM_L3INIT_OCP2SCP1_CLKCTRL_IDLEST_FUNC                                                               (0U)
#define CM_L3INIT_OCP2SCP1_CLKCTRL_IDLEST_TRANS                                                              (1U)

#define CM_L3INIT_OCP2SCP1_CLKCTRL_RESERVED_SHIFT                                                           (2U)
#define CM_L3INIT_OCP2SCP1_CLKCTRL_RESERVED_MASK                                                            (0x0000fffcU)

#define CM_L3INIT_OCP2SCP1_CLKCTRL_RESERVED2_SHIFT                                                          (18U)
#define CM_L3INIT_OCP2SCP1_CLKCTRL_RESERVED2_MASK                                                           (0xfffc0000U)

#define CM_L3INIT_OCP2SCP1_CLKCTRL_MODULEMODE_SHIFT                                                         (0U)
#define CM_L3INIT_OCP2SCP1_CLKCTRL_MODULEMODE_MASK                                                          (0x00000003U)
#define CM_L3INIT_OCP2SCP1_CLKCTRL_MODULEMODE_DISABLED                                                       (0U)
#define CM_L3INIT_OCP2SCP1_CLKCTRL_MODULEMODE_AUTO                                                           (1U)
#define CM_L3INIT_OCP2SCP1_CLKCTRL_MODULEMODE_RESERVED_2                                                     (2U)
#define CM_L3INIT_OCP2SCP1_CLKCTRL_MODULEMODE_RESERVED                                                       (3U)

#define CM_L3INIT_OCP2SCP3_CLKCTRL_IDLEST_SHIFT                                                             (16U)
#define CM_L3INIT_OCP2SCP3_CLKCTRL_IDLEST_MASK                                                              (0x00030000U)
#define CM_L3INIT_OCP2SCP3_CLKCTRL_IDLEST_DISABLE                                                            (3U)
#define CM_L3INIT_OCP2SCP3_CLKCTRL_IDLEST_IDLE                                                               (2U)
#define CM_L3INIT_OCP2SCP3_CLKCTRL_IDLEST_FUNC                                                               (0U)
#define CM_L3INIT_OCP2SCP3_CLKCTRL_IDLEST_TRANS                                                              (1U)

#define CM_L3INIT_OCP2SCP3_CLKCTRL_RESERVED_SHIFT                                                           (2U)
#define CM_L3INIT_OCP2SCP3_CLKCTRL_RESERVED_MASK                                                            (0x0000fffcU)

#define CM_L3INIT_OCP2SCP3_CLKCTRL_RESERVED2_SHIFT                                                          (18U)
#define CM_L3INIT_OCP2SCP3_CLKCTRL_RESERVED2_MASK                                                           (0xfffc0000U)

#define CM_L3INIT_OCP2SCP3_CLKCTRL_MODULEMODE_SHIFT                                                         (0U)
#define CM_L3INIT_OCP2SCP3_CLKCTRL_MODULEMODE_MASK                                                          (0x00000003U)
#define CM_L3INIT_OCP2SCP3_CLKCTRL_MODULEMODE_DISABLED                                                       (0U)
#define CM_L3INIT_OCP2SCP3_CLKCTRL_MODULEMODE_AUTO                                                           (1U)
#define CM_L3INIT_OCP2SCP3_CLKCTRL_MODULEMODE_RESERVED_2                                                     (2U)
#define CM_L3INIT_OCP2SCP3_CLKCTRL_MODULEMODE_RESERVED                                                       (3U)

#define CM_L3INIT_USB_OTG_SS1_CLKCTRL_IDLEST_SHIFT                                                          (16U)
#define CM_L3INIT_USB_OTG_SS1_CLKCTRL_IDLEST_MASK                                                           (0x00030000U)
#define CM_L3INIT_USB_OTG_SS1_CLKCTRL_IDLEST_DISABLE                                                         (3U)
#define CM_L3INIT_USB_OTG_SS1_CLKCTRL_IDLEST_IDLE                                                            (2U)
#define CM_L3INIT_USB_OTG_SS1_CLKCTRL_IDLEST_FUNC                                                            (0U)
#define CM_L3INIT_USB_OTG_SS1_CLKCTRL_IDLEST_TRANS                                                           (1U)

#define CM_L3INIT_USB_OTG_SS1_CLKCTRL_STBYST_SHIFT                                                          (18U)
#define CM_L3INIT_USB_OTG_SS1_CLKCTRL_STBYST_MASK                                                           (0x00040000U)
#define CM_L3INIT_USB_OTG_SS1_CLKCTRL_STBYST_FUNC                                                            (0U)
#define CM_L3INIT_USB_OTG_SS1_CLKCTRL_STBYST_STANDBY                                                         (1U)

#define CM_L3INIT_USB_OTG_SS1_CLKCTRL_MODULEMODE_SHIFT                                                      (0U)
#define CM_L3INIT_USB_OTG_SS1_CLKCTRL_MODULEMODE_MASK                                                       (0x00000003U)
#define CM_L3INIT_USB_OTG_SS1_CLKCTRL_MODULEMODE_DISABLED                                                    (0U)
#define CM_L3INIT_USB_OTG_SS1_CLKCTRL_MODULEMODE_AUTO                                                        (1U)
#define CM_L3INIT_USB_OTG_SS1_CLKCTRL_MODULEMODE_RESERVED_2                                                  (2U)
#define CM_L3INIT_USB_OTG_SS1_CLKCTRL_MODULEMODE_RESERVED                                                    (3U)

#define CM_L3INIT_USB_OTG_SS1_CLKCTRL_RESERVED_SHIFT                                                        (2U)
#define CM_L3INIT_USB_OTG_SS1_CLKCTRL_RESERVED_MASK                                                         (0x000000fcU)

#define CM_L3INIT_USB_OTG_SS1_CLKCTRL_OPTFCLKEN_REFCLK960M_SHIFT                                            (8U)
#define CM_L3INIT_USB_OTG_SS1_CLKCTRL_OPTFCLKEN_REFCLK960M_MASK                                             (0x00000100U)
#define CM_L3INIT_USB_OTG_SS1_CLKCTRL_OPTFCLKEN_REFCLK960M_FCLK_EN                                           (1U)
#define CM_L3INIT_USB_OTG_SS1_CLKCTRL_OPTFCLKEN_REFCLK960M_FCLK_DIS                                          (0U)

#define CM_L3INIT_USB_OTG_SS1_CLKCTRL_RESERVED2_SHIFT                                                       (19U)
#define CM_L3INIT_USB_OTG_SS1_CLKCTRL_RESERVED2_MASK                                                        (0xfff80000U)

#define CM_L3INIT_USB_OTG_SS1_CLKCTRL_RESERVED1_SHIFT                                                       (9U)
#define CM_L3INIT_USB_OTG_SS1_CLKCTRL_RESERVED1_MASK                                                        (0x0000fe00U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_L3INIT_CM_CORE_H_ */
