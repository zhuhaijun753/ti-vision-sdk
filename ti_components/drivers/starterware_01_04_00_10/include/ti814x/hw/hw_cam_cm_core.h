/******************************************************************************
*
* hw_cam_cm_core.h - register-level header file for PRCM
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
#ifndef HW_CAM_CM_CORE_H_
#define HW_CAM_CM_CORE_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define CM_CAM_CLKSTCTRL                                                                                    (0x0U)
#define CM_CAM_STATICDEP                                                                                    (0x4U)
#define CM_CAM_VIP1_CLKCTRL                                                                                 (0x20U)
#define CM_CAM_VIP2_CLKCTRL                                                                                 (0x28U)
#define CM_CAM_VIP3_CLKCTRL                                                                                 (0x30U)
#define CM_CAM_LVDSRX_CLKCTRL                                                                               (0x38U)
#define CM_CAM_CSI1_CLKCTRL                                                                                 (0x40U)
#define CM_CAM_CSI2_CLKCTRL                                                                                 (0x48U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define CM_CAM_CLKSTCTRL_CLKTRCTRL_SHIFT                                                                    (0U)
#define CM_CAM_CLKSTCTRL_CLKTRCTRL_MASK                                                                     (0x00000003U)
#define CM_CAM_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                                                                  (0U)
#define CM_CAM_CLKSTCTRL_CLKTRCTRL_SW_SLEEP                                                                  (1U)
#define CM_CAM_CLKSTCTRL_CLKTRCTRL_SW_WKUP                                                                   (2U)
#define CM_CAM_CLKSTCTRL_CLKTRCTRL_HW_AUTO                                                                   (3U)

#define CM_CAM_CLKSTCTRL_CLKACTIVITY_VIP1_GCLK_SHIFT                                                        (8U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_VIP1_GCLK_MASK                                                         (0x00000100U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_VIP1_GCLK_INACT                                                         (0U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_VIP1_GCLK_ACT                                                           (1U)

#define CM_CAM_CLKSTCTRL_CLKACTIVITY_VIP2_GCLK_SHIFT                                                        (9U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_VIP2_GCLK_MASK                                                         (0x00000200U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_VIP2_GCLK_INACT                                                         (0U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_VIP2_GCLK_ACT                                                           (1U)

#define CM_CAM_CLKSTCTRL_RESERVED_SHIFT                                                                     (2U)
#define CM_CAM_CLKSTCTRL_RESERVED_MASK                                                                      (0x000000fcU)

#define CM_CAM_CLKSTCTRL_CLKACTIVITY_VIP3_GCLK_SHIFT                                                        (10U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_VIP3_GCLK_MASK                                                         (0x00000400U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_VIP3_GCLK_INACT                                                         (0U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_VIP3_GCLK_ACT                                                           (1U)

#define CM_CAM_CLKSTCTRL_CLKACTIVITY_LVDSRX_L4_GICLK_SHIFT                                                  (11U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_LVDSRX_L4_GICLK_MASK                                                   (0x00000800U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_LVDSRX_L4_GICLK_INACT                                                   (0U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_LVDSRX_L4_GICLK_ACT                                                     (1U)

#define CM_CAM_CLKSTCTRL_CLKACTIVITY_LVDSRX_96M_GFCLK_SHIFT                                                 (12U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_LVDSRX_96M_GFCLK_MASK                                                  (0x00001000U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_LVDSRX_96M_GFCLK_INACT                                                  (0U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_LVDSRX_96M_GFCLK_ACT                                                    (1U)

#define CM_CAM_CLKSTCTRL_RESERVED1_SHIFT                                                                    (13U)
#define CM_CAM_CLKSTCTRL_RESERVED1_MASK                                                                     (0xffffe000U)

#define CM_CAM_STATICDEP_IVA_STATDEP_SHIFT                                                                  (2U)
#define CM_CAM_STATICDEP_IVA_STATDEP_MASK                                                                   (0x00000004U)
#define CM_CAM_STATICDEP_IVA_STATDEP_ENABLED                                                                 (1U)
#define CM_CAM_STATICDEP_IVA_STATDEP_DISABLED                                                                (0U)

#define CM_CAM_STATICDEP_EMIF_STATDEP_SHIFT                                                                 (4U)
#define CM_CAM_STATICDEP_EMIF_STATDEP_MASK                                                                  (0x00000010U)
#define CM_CAM_STATICDEP_EMIF_STATDEP_ENABLED                                                                (1U)
#define CM_CAM_STATICDEP_EMIF_STATDEP_DISABLED                                                               (0U)

#define CM_CAM_STATICDEP_L3MAIN1_STATDEP_SHIFT                                                              (5U)
#define CM_CAM_STATICDEP_L3MAIN1_STATDEP_MASK                                                               (0x00000020U)
#define CM_CAM_STATICDEP_L3MAIN1_STATDEP_ENABLED                                                             (1U)

#define CM_CAM_STATICDEP_L4CFG_STATDEP_SHIFT                                                                (12U)
#define CM_CAM_STATICDEP_L4CFG_STATDEP_MASK                                                                 (0x00001000U)
#define CM_CAM_STATICDEP_L4CFG_STATDEP_DISABLED                                                              (0U)

#define CM_CAM_STATICDEP_EVE1_STATDEP_SHIFT                                                                 (19U)
#define CM_CAM_STATICDEP_EVE1_STATDEP_MASK                                                                  (0x00080000U)
#define CM_CAM_STATICDEP_EVE1_STATDEP_ENABLED                                                                (1U)
#define CM_CAM_STATICDEP_EVE1_STATDEP_DISABLED                                                               (0U)

#define CM_CAM_STATICDEP_EVE2_STATDEP_SHIFT                                                                 (20U)
#define CM_CAM_STATICDEP_EVE2_STATDEP_MASK                                                                  (0x00100000U)
#define CM_CAM_STATICDEP_EVE2_STATDEP_ENABLED                                                                (1U)
#define CM_CAM_STATICDEP_EVE2_STATDEP_DISABLED                                                               (0U)

#define CM_CAM_STATICDEP_EVE3_STATDEP_SHIFT                                                                 (21U)
#define CM_CAM_STATICDEP_EVE3_STATDEP_MASK                                                                  (0x00200000U)
#define CM_CAM_STATICDEP_EVE3_STATDEP_ENABLED                                                                (1U)
#define CM_CAM_STATICDEP_EVE3_STATDEP_DISABLED                                                               (0U)

#define CM_CAM_STATICDEP_EVE4_STATDEP_SHIFT                                                                 (22U)
#define CM_CAM_STATICDEP_EVE4_STATDEP_MASK                                                                  (0x00400000U)
#define CM_CAM_STATICDEP_EVE4_STATDEP_ENABLED                                                                (1U)
#define CM_CAM_STATICDEP_EVE4_STATDEP_DISABLED                                                               (0U)

#define CM_CAM_STATICDEP_GMAC_STATDEP_SHIFT                                                                 (25U)
#define CM_CAM_STATICDEP_GMAC_STATDEP_MASK                                                                  (0x02000000U)
#define CM_CAM_STATICDEP_GMAC_STATDEP_ENABLED                                                                (1U)
#define CM_CAM_STATICDEP_GMAC_STATDEP_DISABLED                                                               (0U)

#define CM_CAM_STATICDEP_L4PER3_STATDEP_SHIFT                                                               (27U)
#define CM_CAM_STATICDEP_L4PER3_STATDEP_MASK                                                                (0x08000000U)
#define CM_CAM_STATICDEP_L4PER3_STATDEP_ENABLED                                                              (1U)
#define CM_CAM_STATICDEP_L4PER3_STATDEP_DISABLED                                                             (0U)

#define CM_CAM_STATICDEP_VPE_STATDEP_SHIFT                                                                  (28U)
#define CM_CAM_STATICDEP_VPE_STATDEP_MASK                                                                   (0x10000000U)
#define CM_CAM_STATICDEP_VPE_STATDEP_ENABLED                                                                 (1U)
#define CM_CAM_STATICDEP_VPE_STATDEP_DISABLED                                                                (0U)

#define CM_CAM_STATICDEP_RESERVED_SHIFT                                                                     (0U)
#define CM_CAM_STATICDEP_RESERVED_MASK                                                                      (0x00000003U)

#define CM_CAM_STATICDEP_RESERVED1_SHIFT                                                                    (3U)
#define CM_CAM_STATICDEP_RESERVED1_MASK                                                                     (0x00000008U)

#define CM_CAM_STATICDEP_RESERVED2_SHIFT                                                                    (6U)
#define CM_CAM_STATICDEP_RESERVED2_MASK                                                                     (0x00000fc0U)

#define CM_CAM_STATICDEP_RESERVED3_SHIFT                                                                    (13U)
#define CM_CAM_STATICDEP_RESERVED3_MASK                                                                     (0x0007e000U)

#define CM_CAM_STATICDEP_RESERVED4_SHIFT                                                                    (23U)
#define CM_CAM_STATICDEP_RESERVED4_MASK                                                                     (0x01800000U)

#define CM_CAM_STATICDEP_RESERVED5_SHIFT                                                                    (26U)
#define CM_CAM_STATICDEP_RESERVED5_MASK                                                                     (0x04000000U)

#define CM_CAM_STATICDEP_RESERVED6_SHIFT                                                                    (29U)
#define CM_CAM_STATICDEP_RESERVED6_MASK                                                                     (0xe0000000U)

#define CM_CAM_VIP1_CLKCTRL_IDLEST_SHIFT                                                                    (16U)
#define CM_CAM_VIP1_CLKCTRL_IDLEST_MASK                                                                     (0x00030000U)
#define CM_CAM_VIP1_CLKCTRL_IDLEST_DISABLE                                                                   (3U)
#define CM_CAM_VIP1_CLKCTRL_IDLEST_IDLE                                                                      (2U)
#define CM_CAM_VIP1_CLKCTRL_IDLEST_FUNC                                                                      (0U)
#define CM_CAM_VIP1_CLKCTRL_IDLEST_TRANS                                                                     (1U)

#define CM_CAM_VIP1_CLKCTRL_STBYST_SHIFT                                                                    (18U)
#define CM_CAM_VIP1_CLKCTRL_STBYST_MASK                                                                     (0x00040000U)
#define CM_CAM_VIP1_CLKCTRL_STBYST_FUNC                                                                      (0U)
#define CM_CAM_VIP1_CLKCTRL_STBYST_STANDBY                                                                   (1U)

#define CM_CAM_VIP1_CLKCTRL_RESERVED_SHIFT                                                                  (2U)
#define CM_CAM_VIP1_CLKCTRL_RESERVED_MASK                                                                   (0x0000fffcU)

#define CM_CAM_VIP1_CLKCTRL_CLKSEL_SHIFT                                                                    (24U)
#define CM_CAM_VIP1_CLKCTRL_CLKSEL_MASK                                                                     (0x01000000U)
#define CM_CAM_VIP1_CLKCTRL_CLKSEL_SEL_L3_ICLK                                                               (0U)
#define CM_CAM_VIP1_CLKCTRL_CLKSEL_SEL_CORE_ISS_MAIN_CLK                                                     (1U)

#define CM_CAM_VIP1_CLKCTRL_RESERVED1_SHIFT                                                                 (19U)
#define CM_CAM_VIP1_CLKCTRL_RESERVED1_MASK                                                                  (0x00f80000U)

#define CM_CAM_VIP1_CLKCTRL_RESERVED2_SHIFT                                                                 (25U)
#define CM_CAM_VIP1_CLKCTRL_RESERVED2_MASK                                                                  (0xfe000000U)

#define CM_CAM_VIP1_CLKCTRL_MODULEMODE_SHIFT                                                                (0U)
#define CM_CAM_VIP1_CLKCTRL_MODULEMODE_MASK                                                                 (0x00000003U)
#define CM_CAM_VIP1_CLKCTRL_MODULEMODE_DISABLED                                                              (0U)
#define CM_CAM_VIP1_CLKCTRL_MODULEMODE_AUTO                                                                  (1U)
#define CM_CAM_VIP1_CLKCTRL_MODULEMODE_RESERVED_2                                                            (2U)
#define CM_CAM_VIP1_CLKCTRL_MODULEMODE_RESERVED                                                              (3U)

#define CM_CAM_VIP2_CLKCTRL_IDLEST_SHIFT                                                                    (16U)
#define CM_CAM_VIP2_CLKCTRL_IDLEST_MASK                                                                     (0x00030000U)
#define CM_CAM_VIP2_CLKCTRL_IDLEST_DISABLE                                                                   (3U)
#define CM_CAM_VIP2_CLKCTRL_IDLEST_IDLE                                                                      (2U)
#define CM_CAM_VIP2_CLKCTRL_IDLEST_FUNC                                                                      (0U)
#define CM_CAM_VIP2_CLKCTRL_IDLEST_TRANS                                                                     (1U)

#define CM_CAM_VIP2_CLKCTRL_STBYST_SHIFT                                                                    (18U)
#define CM_CAM_VIP2_CLKCTRL_STBYST_MASK                                                                     (0x00040000U)
#define CM_CAM_VIP2_CLKCTRL_STBYST_FUNC                                                                      (0U)
#define CM_CAM_VIP2_CLKCTRL_STBYST_STANDBY                                                                   (1U)

#define CM_CAM_VIP2_CLKCTRL_RESERVED_SHIFT                                                                  (2U)
#define CM_CAM_VIP2_CLKCTRL_RESERVED_MASK                                                                   (0x0000fffcU)

#define CM_CAM_VIP2_CLKCTRL_RESERVED1_SHIFT                                                                 (19U)
#define CM_CAM_VIP2_CLKCTRL_RESERVED1_MASK                                                                  (0x00f80000U)

#define CM_CAM_VIP2_CLKCTRL_RESERVED2_SHIFT                                                                 (25U)
#define CM_CAM_VIP2_CLKCTRL_RESERVED2_MASK                                                                  (0xfe000000U)

#define CM_CAM_VIP2_CLKCTRL_CLKSEL_SHIFT                                                                    (24U)
#define CM_CAM_VIP2_CLKCTRL_CLKSEL_MASK                                                                     (0x01000000U)
#define CM_CAM_VIP2_CLKCTRL_CLKSEL_SEL_L3_ICLK                                                               (0U)
#define CM_CAM_VIP2_CLKCTRL_CLKSEL_SEL_CORE_ISS_MAIN_CLK                                                     (1U)

#define CM_CAM_VIP2_CLKCTRL_MODULEMODE_SHIFT                                                                (0U)
#define CM_CAM_VIP2_CLKCTRL_MODULEMODE_MASK                                                                 (0x00000003U)
#define CM_CAM_VIP2_CLKCTRL_MODULEMODE_DISABLED                                                              (0U)
#define CM_CAM_VIP2_CLKCTRL_MODULEMODE_AUTO                                                                  (1U)
#define CM_CAM_VIP2_CLKCTRL_MODULEMODE_RESERVED_2                                                            (2U)
#define CM_CAM_VIP2_CLKCTRL_MODULEMODE_RESERVED                                                              (3U)

#define CM_CAM_VIP3_CLKCTRL_IDLEST_SHIFT                                                                    (16U)
#define CM_CAM_VIP3_CLKCTRL_IDLEST_MASK                                                                     (0x00030000U)
#define CM_CAM_VIP3_CLKCTRL_IDLEST_DISABLE                                                                   (3U)
#define CM_CAM_VIP3_CLKCTRL_IDLEST_IDLE                                                                      (2U)
#define CM_CAM_VIP3_CLKCTRL_IDLEST_FUNC                                                                      (0U)
#define CM_CAM_VIP3_CLKCTRL_IDLEST_TRANS                                                                     (1U)

#define CM_CAM_VIP3_CLKCTRL_STBYST_SHIFT                                                                    (18U)
#define CM_CAM_VIP3_CLKCTRL_STBYST_MASK                                                                     (0x00040000U)
#define CM_CAM_VIP3_CLKCTRL_STBYST_FUNC                                                                      (0U)
#define CM_CAM_VIP3_CLKCTRL_STBYST_STANDBY                                                                   (1U)

#define CM_CAM_VIP3_CLKCTRL_RESERVED_SHIFT                                                                  (2U)
#define CM_CAM_VIP3_CLKCTRL_RESERVED_MASK                                                                   (0x0000fffcU)

#define CM_CAM_VIP3_CLKCTRL_RESERVED1_SHIFT                                                                 (19U)
#define CM_CAM_VIP3_CLKCTRL_RESERVED1_MASK                                                                  (0x00f80000U)

#define CM_CAM_VIP3_CLKCTRL_RESERVED2_SHIFT                                                                 (25U)
#define CM_CAM_VIP3_CLKCTRL_RESERVED2_MASK                                                                  (0xfe000000U)

#define CM_CAM_VIP3_CLKCTRL_CLKSEL_SHIFT                                                                    (24U)
#define CM_CAM_VIP3_CLKCTRL_CLKSEL_MASK                                                                     (0x01000000U)
#define CM_CAM_VIP3_CLKCTRL_CLKSEL_SEL_L3_ICLK                                                               (0U)
#define CM_CAM_VIP3_CLKCTRL_CLKSEL_SEL_CORE_ISS_MAIN_CLK                                                     (1U)

#define CM_CAM_VIP3_CLKCTRL_MODULEMODE_SHIFT                                                                (0U)
#define CM_CAM_VIP3_CLKCTRL_MODULEMODE_MASK                                                                 (0x00000003U)
#define CM_CAM_VIP3_CLKCTRL_MODULEMODE_DISABLED                                                              (0U)
#define CM_CAM_VIP3_CLKCTRL_MODULEMODE_AUTO                                                                  (1U)
#define CM_CAM_VIP3_CLKCTRL_MODULEMODE_RESERVED_2                                                            (2U)
#define CM_CAM_VIP3_CLKCTRL_MODULEMODE_RESERVED                                                              (3U)

#define CM_CAM_LVDSRX_CLKCTRL_IDLEST_SHIFT                                                                  (16U)
#define CM_CAM_LVDSRX_CLKCTRL_IDLEST_MASK                                                                   (0x00030000U)
#define CM_CAM_LVDSRX_CLKCTRL_IDLEST_DISABLE                                                                 (3U)
#define CM_CAM_LVDSRX_CLKCTRL_IDLEST_IDLE                                                                    (2U)
#define CM_CAM_LVDSRX_CLKCTRL_IDLEST_FUNC                                                                    (0U)
#define CM_CAM_LVDSRX_CLKCTRL_IDLEST_TRANS                                                                   (1U)

#define CM_CAM_LVDSRX_CLKCTRL_RESERVED_SHIFT                                                                (2U)
#define CM_CAM_LVDSRX_CLKCTRL_RESERVED_MASK                                                                 (0x0000fffcU)

#define CM_CAM_LVDSRX_CLKCTRL_MODULEMODE_SHIFT                                                              (0U)
#define CM_CAM_LVDSRX_CLKCTRL_MODULEMODE_MASK                                                               (0x00000003U)
#define CM_CAM_LVDSRX_CLKCTRL_MODULEMODE_DISABLED                                                            (0U)
#define CM_CAM_LVDSRX_CLKCTRL_MODULEMODE_RESERVED_1                                                          (1U)
#define CM_CAM_LVDSRX_CLKCTRL_MODULEMODE_ENABLE                                                              (2U)
#define CM_CAM_LVDSRX_CLKCTRL_MODULEMODE_RESERVED                                                            (3U)

#define CM_CAM_LVDSRX_CLKCTRL_RESERVED1_SHIFT                                                               (18U)
#define CM_CAM_LVDSRX_CLKCTRL_RESERVED1_MASK                                                                (0xfffc0000U)

#define CM_CAM_CSI1_CLKCTRL_IDLEST_SHIFT                                                                    (16U)
#define CM_CAM_CSI1_CLKCTRL_IDLEST_MASK                                                                     (0x00030000U)
#define CM_CAM_CSI1_CLKCTRL_IDLEST_DISABLE                                                                   (3U)
#define CM_CAM_CSI1_CLKCTRL_IDLEST_IDLE                                                                      (2U)
#define CM_CAM_CSI1_CLKCTRL_IDLEST_FUNC                                                                      (0U)
#define CM_CAM_CSI1_CLKCTRL_IDLEST_TRANS                                                                     (1U)

#define CM_CAM_CSI1_CLKCTRL_STBYST_SHIFT                                                                    (18U)
#define CM_CAM_CSI1_CLKCTRL_STBYST_MASK                                                                     (0x00040000U)
#define CM_CAM_CSI1_CLKCTRL_STBYST_FUNC                                                                      (0U)
#define CM_CAM_CSI1_CLKCTRL_STBYST_STANDBY                                                                   (1U)

#define CM_CAM_CSI1_CLKCTRL_RESERVED_SHIFT                                                                  (2U)
#define CM_CAM_CSI1_CLKCTRL_RESERVED_MASK                                                                   (0x0000fffcU)

#define CM_CAM_CSI1_CLKCTRL_MODULEMODE_SHIFT                                                                (0U)
#define CM_CAM_CSI1_CLKCTRL_MODULEMODE_MASK                                                                 (0x00000003U)
#define CM_CAM_CSI1_CLKCTRL_MODULEMODE_AUTO                                                                  (1U)

#define CM_CAM_CSI1_CLKCTRL_RESERVED1_SHIFT                                                                 (19U)
#define CM_CAM_CSI1_CLKCTRL_RESERVED1_MASK                                                                  (0xfff80000U)

#define CM_CAM_CSI2_CLKCTRL_IDLEST_SHIFT                                                                    (16U)
#define CM_CAM_CSI2_CLKCTRL_IDLEST_MASK                                                                     (0x00030000U)
#define CM_CAM_CSI2_CLKCTRL_IDLEST_DISABLE                                                                   (3U)
#define CM_CAM_CSI2_CLKCTRL_IDLEST_IDLE                                                                      (2U)
#define CM_CAM_CSI2_CLKCTRL_IDLEST_FUNC                                                                      (0U)
#define CM_CAM_CSI2_CLKCTRL_IDLEST_TRANS                                                                     (1U)

#define CM_CAM_CSI2_CLKCTRL_STBYST_SHIFT                                                                    (18U)
#define CM_CAM_CSI2_CLKCTRL_STBYST_MASK                                                                     (0x00040000U)
#define CM_CAM_CSI2_CLKCTRL_STBYST_FUNC                                                                      (0U)
#define CM_CAM_CSI2_CLKCTRL_STBYST_STANDBY                                                                   (1U)

#define CM_CAM_CSI2_CLKCTRL_RESERVED_SHIFT                                                                  (2U)
#define CM_CAM_CSI2_CLKCTRL_RESERVED_MASK                                                                   (0x0000fffcU)

#define CM_CAM_CSI2_CLKCTRL_MODULEMODE_SHIFT                                                                (0U)
#define CM_CAM_CSI2_CLKCTRL_MODULEMODE_MASK                                                                 (0x00000003U)
#define CM_CAM_CSI2_CLKCTRL_MODULEMODE_AUTO                                                                  (1U)

#define CM_CAM_CSI2_CLKCTRL_RESERVED1_SHIFT                                                                 (19U)
#define CM_CAM_CSI2_CLKCTRL_RESERVED1_MASK                                                                  (0xfff80000U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_CAM_CM_CORE_H_ */
