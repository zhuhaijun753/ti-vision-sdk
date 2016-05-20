/******************************************************************************
*
* hw_wkupaon_cm.h - register-level header file for PRCM
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
#ifndef HW_WKUPAON_CM_H_
#define HW_WKUPAON_CM_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define CM_WKUPAON_CLKSTCTRL                                                                                (0x0U)
#define CM_WKUPAON_L4_WKUP_CLKCTRL                                                                          (0x20U)
#define CM_WKUPAON_WD_TIMER1_CLKCTRL                                                                        (0x28U)
#define CM_WKUPAON_WD_TIMER2_CLKCTRL                                                                        (0x30U)
#define CM_WKUPAON_GPIO1_CLKCTRL                                                                            (0x38U)
#define CM_WKUPAON_TIMER1_CLKCTRL                                                                           (0x40U)
#define CM_WKUPAON_TIMER12_CLKCTRL                                                                          (0x48U)
#define CM_WKUPAON_COUNTER_32K_CLKCTRL                                                                      (0x50U)
#define CM_WKUPAON_SAR_RAM_CLKCTRL                                                                          (0x60U)
#define CM_WKUPAON_KBD_CLKCTRL                                                                              (0x78U)
#define CM_WKUPAON_UART10_CLKCTRL                                                                           (0x80U)
#define CM_WKUPAON_DCAN1_CLKCTRL                                                                            (0x88U)
#define CM_WKUPAON_SCRM_CLKCTRL                                                                             (0x90U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define CM_WKUPAON_CLKSTCTRL_CLKTRCTRL_SHIFT                                                                (0U)
#define CM_WKUPAON_CLKSTCTRL_CLKTRCTRL_MASK                                                                 (0x00000003U)
#define CM_WKUPAON_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                                                              (0U)
#define CM_WKUPAON_CLKSTCTRL_CLKTRCTRL_RESERVED_1                                                            (1U)
#define CM_WKUPAON_CLKSTCTRL_CLKTRCTRL_SW_WKUP                                                               (2U)
#define CM_WKUPAON_CLKSTCTRL_CLKTRCTRL_HW_AUTO                                                               (3U)

#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_SYS_CLK_SHIFT                                                      (8U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_SYS_CLK_MASK                                                       (0x00000100U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_SYS_CLK_INACT                                                       (0U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_SYS_CLK_ACT                                                         (1U)

#define CM_WKUPAON_CLKSTCTRL_RESERVED_SHIFT                                                                 (2U)
#define CM_WKUPAON_CLKSTCTRL_RESERVED_MASK                                                                  (0x000000fcU)

#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_ABE_LP_CLK_SHIFT                                                   (9U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_ABE_LP_CLK_MASK                                                    (0x00000200U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_ABE_LP_CLK_INACT                                                    (0U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_ABE_LP_CLK_ACT                                                      (1U)

#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_WKUPAON_SYS_GFCLK_SHIFT                                            (11U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_WKUPAON_SYS_GFCLK_MASK                                             (0x00000800U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_WKUPAON_SYS_GFCLK_INACT                                             (0U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_WKUPAON_SYS_GFCLK_ACT                                               (1U)

#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_WKUPAON_GICLK_SHIFT                                                (12U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_WKUPAON_GICLK_MASK                                                 (0x00001000U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_WKUPAON_GICLK_INACT                                                 (0U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_WKUPAON_GICLK_ACT                                                   (1U)

#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_SYS_CLK_FUNC_SHIFT                                                 (14U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_SYS_CLK_FUNC_MASK                                                  (0x00004000U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_SYS_CLK_FUNC_INACT                                                  (0U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_SYS_CLK_FUNC_ACT                                                    (1U)

#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_SYS_CLK_ALL_SHIFT                                                  (15U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_SYS_CLK_ALL_MASK                                                   (0x00008000U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_SYS_CLK_ALL_INACT                                                   (0U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_SYS_CLK_ALL_ACT                                                     (1U)

#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_DCAN1_SYS_CLK_SHIFT                                                (16U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_DCAN1_SYS_CLK_MASK                                                 (0x00010000U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_DCAN1_SYS_CLK_INACT                                                 (0U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_DCAN1_SYS_CLK_ACT                                                   (1U)

#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_TIMER1_GFCLK_SHIFT                                                 (17U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_TIMER1_GFCLK_MASK                                                  (0x00020000U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_TIMER1_GFCLK_INACT                                                  (0U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_TIMER1_GFCLK_ACT                                                    (1U)

#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_UART10_GFCLK_SHIFT                                                 (18U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_UART10_GFCLK_MASK                                                  (0x00040000U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_UART10_GFCLK_INACT                                                  (0U)
#define CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_UART10_GFCLK_ACT                                                    (1U)

#define CM_WKUPAON_CLKSTCTRL_RESERVED2_SHIFT                                                                (19U)
#define CM_WKUPAON_CLKSTCTRL_RESERVED2_MASK                                                                 (0xfff80000U)

#define CM_WKUPAON_CLKSTCTRL_RESERVED1_SHIFT                                                                (10U)
#define CM_WKUPAON_CLKSTCTRL_RESERVED1_MASK                                                                 (0x00000400U)
#define CM_WKUPAON_CLKSTCTRL_RESERVED1_INACT                                                                 (0U)
#define CM_WKUPAON_CLKSTCTRL_RESERVED1_ACT                                                                   (1U)

#define CM_WKUPAON_L4_WKUP_CLKCTRL_RESERVED_SHIFT                                                           (2U)
#define CM_WKUPAON_L4_WKUP_CLKCTRL_RESERVED_MASK                                                            (0x0000fffcU)

#define CM_WKUPAON_L4_WKUP_CLKCTRL_RESERVED1_SHIFT                                                          (18U)
#define CM_WKUPAON_L4_WKUP_CLKCTRL_RESERVED1_MASK                                                           (0xfffc0000U)

#define CM_WKUPAON_L4_WKUP_CLKCTRL_MODULEMODE_SHIFT                                                         (0U)
#define CM_WKUPAON_L4_WKUP_CLKCTRL_MODULEMODE_MASK                                                          (0x00000003U)
#define CM_WKUPAON_L4_WKUP_CLKCTRL_MODULEMODE_AUTO                                                           (1U)

#define CM_WKUPAON_L4_WKUP_CLKCTRL_IDLEST_SHIFT                                                             (16U)
#define CM_WKUPAON_L4_WKUP_CLKCTRL_IDLEST_MASK                                                              (0x00030000U)
#define CM_WKUPAON_L4_WKUP_CLKCTRL_IDLEST_DISABLE                                                            (3U)
#define CM_WKUPAON_L4_WKUP_CLKCTRL_IDLEST_IDLE                                                               (2U)
#define CM_WKUPAON_L4_WKUP_CLKCTRL_IDLEST_FUNC                                                               (0U)
#define CM_WKUPAON_L4_WKUP_CLKCTRL_IDLEST_TRANS                                                              (1U)

#define CM_WKUPAON_WD_TIMER1_CLKCTRL_RESERVED_SHIFT                                                         (2U)
#define CM_WKUPAON_WD_TIMER1_CLKCTRL_RESERVED_MASK                                                          (0x0000fffcU)

#define CM_WKUPAON_WD_TIMER1_CLKCTRL_RESERVED1_SHIFT                                                        (18U)
#define CM_WKUPAON_WD_TIMER1_CLKCTRL_RESERVED1_MASK                                                         (0xfffc0000U)

#define CM_WKUPAON_WD_TIMER1_CLKCTRL_IDLEST_SHIFT                                                           (16U)
#define CM_WKUPAON_WD_TIMER1_CLKCTRL_IDLEST_MASK                                                            (0x00030000U)
#define CM_WKUPAON_WD_TIMER1_CLKCTRL_IDLEST_DISABLE                                                          (3U)
#define CM_WKUPAON_WD_TIMER1_CLKCTRL_IDLEST_IDLE                                                             (2U)
#define CM_WKUPAON_WD_TIMER1_CLKCTRL_IDLEST_FUNC                                                             (0U)
#define CM_WKUPAON_WD_TIMER1_CLKCTRL_IDLEST_TRANS                                                            (1U)

#define CM_WKUPAON_WD_TIMER1_CLKCTRL_MODULEMODE_SHIFT                                                       (0U)
#define CM_WKUPAON_WD_TIMER1_CLKCTRL_MODULEMODE_MASK                                                        (0x00000003U)
#define CM_WKUPAON_WD_TIMER1_CLKCTRL_MODULEMODE_AUTO                                                         (1U)

#define CM_WKUPAON_WD_TIMER2_CLKCTRL_RESERVED_SHIFT                                                         (2U)
#define CM_WKUPAON_WD_TIMER2_CLKCTRL_RESERVED_MASK                                                          (0x0000fffcU)

#define CM_WKUPAON_WD_TIMER2_CLKCTRL_RESERVED1_SHIFT                                                        (18U)
#define CM_WKUPAON_WD_TIMER2_CLKCTRL_RESERVED1_MASK                                                         (0xfffc0000U)

#define CM_WKUPAON_WD_TIMER2_CLKCTRL_IDLEST_SHIFT                                                           (16U)
#define CM_WKUPAON_WD_TIMER2_CLKCTRL_IDLEST_MASK                                                            (0x00030000U)
#define CM_WKUPAON_WD_TIMER2_CLKCTRL_IDLEST_DISABLE                                                          (3U)
#define CM_WKUPAON_WD_TIMER2_CLKCTRL_IDLEST_IDLE                                                             (2U)
#define CM_WKUPAON_WD_TIMER2_CLKCTRL_IDLEST_FUNC                                                             (0U)
#define CM_WKUPAON_WD_TIMER2_CLKCTRL_IDLEST_TRANS                                                            (1U)

#define CM_WKUPAON_WD_TIMER2_CLKCTRL_MODULEMODE_SHIFT                                                       (0U)
#define CM_WKUPAON_WD_TIMER2_CLKCTRL_MODULEMODE_MASK                                                        (0x00000003U)
#define CM_WKUPAON_WD_TIMER2_CLKCTRL_MODULEMODE_DISABLED                                                     (0U)
#define CM_WKUPAON_WD_TIMER2_CLKCTRL_MODULEMODE_RESERVED_1                                                   (1U)
#define CM_WKUPAON_WD_TIMER2_CLKCTRL_MODULEMODE_ENABLE                                                       (2U)
#define CM_WKUPAON_WD_TIMER2_CLKCTRL_MODULEMODE_RESERVED                                                     (3U)

#define CM_WKUPAON_GPIO1_CLKCTRL_RESERVED1_SHIFT                                                            (18U)
#define CM_WKUPAON_GPIO1_CLKCTRL_RESERVED1_MASK                                                             (0xfffc0000U)

#define CM_WKUPAON_GPIO1_CLKCTRL_IDLEST_SHIFT                                                               (16U)
#define CM_WKUPAON_GPIO1_CLKCTRL_IDLEST_MASK                                                                (0x00030000U)
#define CM_WKUPAON_GPIO1_CLKCTRL_IDLEST_DISABLE                                                              (3U)
#define CM_WKUPAON_GPIO1_CLKCTRL_IDLEST_IDLE                                                                 (2U)
#define CM_WKUPAON_GPIO1_CLKCTRL_IDLEST_FUNC                                                                 (0U)
#define CM_WKUPAON_GPIO1_CLKCTRL_IDLEST_TRANS                                                                (1U)

#define CM_WKUPAON_GPIO1_CLKCTRL_OPTFCLKEN_DBCLK_SHIFT                                                      (8U)
#define CM_WKUPAON_GPIO1_CLKCTRL_OPTFCLKEN_DBCLK_MASK                                                       (0x00000100U)
#define CM_WKUPAON_GPIO1_CLKCTRL_OPTFCLKEN_DBCLK_FCLK_EN                                                     (1U)
#define CM_WKUPAON_GPIO1_CLKCTRL_OPTFCLKEN_DBCLK_FCLK_DIS                                                    (0U)

#define CM_WKUPAON_GPIO1_CLKCTRL_RESERVED_SHIFT                                                             (2U)
#define CM_WKUPAON_GPIO1_CLKCTRL_RESERVED_MASK                                                              (0x000000fcU)

#define CM_WKUPAON_GPIO1_CLKCTRL_RESERVED2_SHIFT                                                            (9U)
#define CM_WKUPAON_GPIO1_CLKCTRL_RESERVED2_MASK                                                             (0x0000fe00U)

#define CM_WKUPAON_GPIO1_CLKCTRL_MODULEMODE_SHIFT                                                           (0U)
#define CM_WKUPAON_GPIO1_CLKCTRL_MODULEMODE_MASK                                                            (0x00000003U)
#define CM_WKUPAON_GPIO1_CLKCTRL_MODULEMODE_DISABLED                                                         (0U)
#define CM_WKUPAON_GPIO1_CLKCTRL_MODULEMODE_AUTO                                                             (1U)
#define CM_WKUPAON_GPIO1_CLKCTRL_MODULEMODE_RESERVED_2                                                       (2U)
#define CM_WKUPAON_GPIO1_CLKCTRL_MODULEMODE_RESERVED                                                         (3U)

#define CM_WKUPAON_TIMER1_CLKCTRL_RESERVED_SHIFT                                                            (2U)
#define CM_WKUPAON_TIMER1_CLKCTRL_RESERVED_MASK                                                             (0x0000fffcU)

#define CM_WKUPAON_TIMER1_CLKCTRL_RESERVED1_SHIFT                                                           (18U)
#define CM_WKUPAON_TIMER1_CLKCTRL_RESERVED1_MASK                                                            (0x00fc0000U)

#define CM_WKUPAON_TIMER1_CLKCTRL_IDLEST_SHIFT                                                              (16U)
#define CM_WKUPAON_TIMER1_CLKCTRL_IDLEST_MASK                                                               (0x00030000U)
#define CM_WKUPAON_TIMER1_CLKCTRL_IDLEST_DISABLE                                                             (3U)
#define CM_WKUPAON_TIMER1_CLKCTRL_IDLEST_IDLE                                                                (2U)
#define CM_WKUPAON_TIMER1_CLKCTRL_IDLEST_FUNC                                                                (0U)
#define CM_WKUPAON_TIMER1_CLKCTRL_IDLEST_TRANS                                                               (1U)

#define CM_WKUPAON_TIMER1_CLKCTRL_MODULEMODE_SHIFT                                                          (0U)
#define CM_WKUPAON_TIMER1_CLKCTRL_MODULEMODE_MASK                                                           (0x00000003U)
#define CM_WKUPAON_TIMER1_CLKCTRL_MODULEMODE_DISABLED                                                        (0U)
#define CM_WKUPAON_TIMER1_CLKCTRL_MODULEMODE_RESERVED_1                                                      (1U)
#define CM_WKUPAON_TIMER1_CLKCTRL_MODULEMODE_ENABLE                                                          (2U)
#define CM_WKUPAON_TIMER1_CLKCTRL_MODULEMODE_RESERVED                                                        (3U)

#define CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_SHIFT                                                              (24U)
#define CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_MASK                                                               (0x0f000000U)
#define CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_SEL_TIMER_SYS_CLK                                                   (0U)
#define CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_SEL_SYS_CLK1_32K_CLK                                                (1U)
#define CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_SEL_SYS_CLK2                                                        (2U)
#define CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_SEL_XREF_CLK0                                                       (3U)
#define CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_SEL_XREF_CLK1                                                       (4U)
#define CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_SEL_XREF_CLK2                                                       (5U)
#define CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_SEL_XREF_CLK3                                                       (6U)
#define CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_SEL_PER_ABE_X1_GFCLK                                                (7U)
#define CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_SEL_VIDEO1_CLK                                                      (8U)
#define CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_SEL_VIDEO2_CLK                                                      (9U)
#define CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_SEL_HDMI_CLK                                                        (10U)
#define CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_RESERVED                                                            (11U)
#define CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_RESERVED1                                                           (12U)
#define CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_RESERVED2                                                           (13U)
#define CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_RESERVED3                                                           (14U)
#define CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_RESERVED4                                                           (15U)

#define CM_WKUPAON_TIMER1_CLKCTRL_RESERVED2_SHIFT                                                           (28U)
#define CM_WKUPAON_TIMER1_CLKCTRL_RESERVED2_MASK                                                            (0xf0000000U)

#define CM_WKUPAON_TIMER12_CLKCTRL_RESERVED_SHIFT                                                           (2U)
#define CM_WKUPAON_TIMER12_CLKCTRL_RESERVED_MASK                                                            (0x0000fffcU)

#define CM_WKUPAON_TIMER12_CLKCTRL_RESERVED1_SHIFT                                                          (18U)
#define CM_WKUPAON_TIMER12_CLKCTRL_RESERVED1_MASK                                                           (0xfffc0000U)

#define CM_WKUPAON_TIMER12_CLKCTRL_IDLEST_SHIFT                                                             (16U)
#define CM_WKUPAON_TIMER12_CLKCTRL_IDLEST_MASK                                                              (0x00030000U)
#define CM_WKUPAON_TIMER12_CLKCTRL_IDLEST_DISABLE                                                            (3U)
#define CM_WKUPAON_TIMER12_CLKCTRL_IDLEST_IDLE                                                               (2U)
#define CM_WKUPAON_TIMER12_CLKCTRL_IDLEST_FUNC                                                               (0U)
#define CM_WKUPAON_TIMER12_CLKCTRL_IDLEST_TRANS                                                              (1U)

#define CM_WKUPAON_TIMER12_CLKCTRL_MODULEMODE_SHIFT                                                         (0U)
#define CM_WKUPAON_TIMER12_CLKCTRL_MODULEMODE_MASK                                                          (0x00000003U)
#define CM_WKUPAON_TIMER12_CLKCTRL_MODULEMODE_AUTO                                                           (1U)

#define CM_WKUPAON_COUNTER_32K_CLKCTRL_RESERVED_SHIFT                                                       (2U)
#define CM_WKUPAON_COUNTER_32K_CLKCTRL_RESERVED_MASK                                                        (0x0000fffcU)

#define CM_WKUPAON_COUNTER_32K_CLKCTRL_RESERVED1_SHIFT                                                      (18U)
#define CM_WKUPAON_COUNTER_32K_CLKCTRL_RESERVED1_MASK                                                       (0xfffc0000U)

#define CM_WKUPAON_COUNTER_32K_CLKCTRL_IDLEST_SHIFT                                                         (16U)
#define CM_WKUPAON_COUNTER_32K_CLKCTRL_IDLEST_MASK                                                          (0x00030000U)
#define CM_WKUPAON_COUNTER_32K_CLKCTRL_IDLEST_DISABLE                                                        (3U)
#define CM_WKUPAON_COUNTER_32K_CLKCTRL_IDLEST_IDLE                                                           (2U)
#define CM_WKUPAON_COUNTER_32K_CLKCTRL_IDLEST_FUNC                                                           (0U)
#define CM_WKUPAON_COUNTER_32K_CLKCTRL_IDLEST_TRANS                                                          (1U)

#define CM_WKUPAON_COUNTER_32K_CLKCTRL_MODULEMODE_SHIFT                                                     (0U)
#define CM_WKUPAON_COUNTER_32K_CLKCTRL_MODULEMODE_MASK                                                      (0x00000003U)
#define CM_WKUPAON_COUNTER_32K_CLKCTRL_MODULEMODE_AUTO                                                       (1U)

#define CM_WKUPAON_SAR_RAM_CLKCTRL_RESERVED_SHIFT                                                           (2U)
#define CM_WKUPAON_SAR_RAM_CLKCTRL_RESERVED_MASK                                                            (0x0000fffcU)

#define CM_WKUPAON_SAR_RAM_CLKCTRL_RESERVED1_SHIFT                                                          (18U)
#define CM_WKUPAON_SAR_RAM_CLKCTRL_RESERVED1_MASK                                                           (0xfffc0000U)

#define CM_WKUPAON_SAR_RAM_CLKCTRL_MODULEMODE_SHIFT                                                         (0U)
#define CM_WKUPAON_SAR_RAM_CLKCTRL_MODULEMODE_MASK                                                          (0x00000003U)
#define CM_WKUPAON_SAR_RAM_CLKCTRL_MODULEMODE_AUTO                                                           (1U)

#define CM_WKUPAON_SAR_RAM_CLKCTRL_IDLEST_SHIFT                                                             (16U)
#define CM_WKUPAON_SAR_RAM_CLKCTRL_IDLEST_MASK                                                              (0x00030000U)
#define CM_WKUPAON_SAR_RAM_CLKCTRL_IDLEST_DISABLE                                                            (3U)
#define CM_WKUPAON_SAR_RAM_CLKCTRL_IDLEST_IDLE                                                               (2U)
#define CM_WKUPAON_SAR_RAM_CLKCTRL_IDLEST_FUNC                                                               (0U)
#define CM_WKUPAON_SAR_RAM_CLKCTRL_IDLEST_TRANS                                                              (1U)

#define CM_WKUPAON_KBD_CLKCTRL_RESERVED_SHIFT                                                               (2U)
#define CM_WKUPAON_KBD_CLKCTRL_RESERVED_MASK                                                                (0x0000fffcU)

#define CM_WKUPAON_KBD_CLKCTRL_RESERVED1_SHIFT                                                              (18U)
#define CM_WKUPAON_KBD_CLKCTRL_RESERVED1_MASK                                                               (0xfffc0000U)

#define CM_WKUPAON_KBD_CLKCTRL_IDLEST_SHIFT                                                                 (16U)
#define CM_WKUPAON_KBD_CLKCTRL_IDLEST_MASK                                                                  (0x00030000U)
#define CM_WKUPAON_KBD_CLKCTRL_IDLEST_DISABLE                                                                (3U)
#define CM_WKUPAON_KBD_CLKCTRL_IDLEST_IDLE                                                                   (2U)
#define CM_WKUPAON_KBD_CLKCTRL_IDLEST_FUNC                                                                   (0U)
#define CM_WKUPAON_KBD_CLKCTRL_IDLEST_TRANS                                                                  (1U)

#define CM_WKUPAON_KBD_CLKCTRL_MODULEMODE_SHIFT                                                             (0U)
#define CM_WKUPAON_KBD_CLKCTRL_MODULEMODE_MASK                                                              (0x00000003U)
#define CM_WKUPAON_KBD_CLKCTRL_MODULEMODE_DISABLED                                                           (0U)
#define CM_WKUPAON_KBD_CLKCTRL_MODULEMODE_RESERVED_1                                                         (1U)
#define CM_WKUPAON_KBD_CLKCTRL_MODULEMODE_ENABLE                                                             (2U)
#define CM_WKUPAON_KBD_CLKCTRL_MODULEMODE_RESERVED                                                           (3U)

#define CM_WKUPAON_UART10_CLKCTRL_RESERVED_SHIFT                                                            (2U)
#define CM_WKUPAON_UART10_CLKCTRL_RESERVED_MASK                                                             (0x0000fffcU)

#define CM_WKUPAON_UART10_CLKCTRL_IDLEST_SHIFT                                                              (16U)
#define CM_WKUPAON_UART10_CLKCTRL_IDLEST_MASK                                                               (0x00030000U)
#define CM_WKUPAON_UART10_CLKCTRL_IDLEST_DISABLE                                                             (3U)
#define CM_WKUPAON_UART10_CLKCTRL_IDLEST_IDLE                                                                (2U)
#define CM_WKUPAON_UART10_CLKCTRL_IDLEST_FUNC                                                                (0U)
#define CM_WKUPAON_UART10_CLKCTRL_IDLEST_TRANS                                                               (1U)

#define CM_WKUPAON_UART10_CLKCTRL_MODULEMODE_SHIFT                                                          (0U)
#define CM_WKUPAON_UART10_CLKCTRL_MODULEMODE_MASK                                                           (0x00000003U)
#define CM_WKUPAON_UART10_CLKCTRL_MODULEMODE_DISABLED                                                        (0U)
#define CM_WKUPAON_UART10_CLKCTRL_MODULEMODE_RESERVED_1                                                      (1U)
#define CM_WKUPAON_UART10_CLKCTRL_MODULEMODE_ENABLE                                                          (2U)
#define CM_WKUPAON_UART10_CLKCTRL_MODULEMODE_RESERVED                                                        (3U)

#define CM_WKUPAON_UART10_CLKCTRL_RESERVED1_SHIFT                                                           (18U)
#define CM_WKUPAON_UART10_CLKCTRL_RESERVED1_MASK                                                            (0x00fc0000U)

#define CM_WKUPAON_UART10_CLKCTRL_CLKSEL_SHIFT                                                              (24U)
#define CM_WKUPAON_UART10_CLKCTRL_CLKSEL_MASK                                                               (0x01000000U)
#define CM_WKUPAON_UART10_CLKCTRL_CLKSEL_SEL_FUNC_48M_CLK                                                    (0U)
#define CM_WKUPAON_UART10_CLKCTRL_CLKSEL_SEL_FUNC_192M_CLK                                                   (1U)

#define CM_WKUPAON_UART10_CLKCTRL_RESERVED2_SHIFT                                                           (25U)
#define CM_WKUPAON_UART10_CLKCTRL_RESERVED2_MASK                                                            (0xfe000000U)

#define CM_WKUPAON_DCAN1_CLKCTRL_RESERVED_SHIFT                                                             (2U)
#define CM_WKUPAON_DCAN1_CLKCTRL_RESERVED_MASK                                                              (0x0000fffcU)

#define CM_WKUPAON_DCAN1_CLKCTRL_IDLEST_SHIFT                                                               (16U)
#define CM_WKUPAON_DCAN1_CLKCTRL_IDLEST_MASK                                                                (0x00030000U)
#define CM_WKUPAON_DCAN1_CLKCTRL_IDLEST_DISABLE                                                              (3U)
#define CM_WKUPAON_DCAN1_CLKCTRL_IDLEST_IDLE                                                                 (2U)
#define CM_WKUPAON_DCAN1_CLKCTRL_IDLEST_FUNC                                                                 (0U)
#define CM_WKUPAON_DCAN1_CLKCTRL_IDLEST_TRANS                                                                (1U)

#define CM_WKUPAON_DCAN1_CLKCTRL_MODULEMODE_SHIFT                                                           (0U)
#define CM_WKUPAON_DCAN1_CLKCTRL_MODULEMODE_MASK                                                            (0x00000003U)
#define CM_WKUPAON_DCAN1_CLKCTRL_MODULEMODE_DISABLED                                                         (0U)
#define CM_WKUPAON_DCAN1_CLKCTRL_MODULEMODE_RESERVED_1                                                       (1U)
#define CM_WKUPAON_DCAN1_CLKCTRL_MODULEMODE_ENABLE                                                           (2U)
#define CM_WKUPAON_DCAN1_CLKCTRL_MODULEMODE_RESERVED                                                         (3U)

#define CM_WKUPAON_DCAN1_CLKCTRL_CLKSEL_SHIFT                                                               (24U)
#define CM_WKUPAON_DCAN1_CLKCTRL_CLKSEL_MASK                                                                (0x01000000U)
#define CM_WKUPAON_DCAN1_CLKCTRL_CLKSEL_SEL_SYS_CLK1                                                         (0U)
#define CM_WKUPAON_DCAN1_CLKCTRL_CLKSEL_SEL_SYS_CLK2                                                         (1U)

#define CM_WKUPAON_DCAN1_CLKCTRL_RESERVED1_SHIFT                                                            (18U)
#define CM_WKUPAON_DCAN1_CLKCTRL_RESERVED1_MASK                                                             (0x00fc0000U)

#define CM_WKUPAON_DCAN1_CLKCTRL_RESERVED2_SHIFT                                                            (25U)
#define CM_WKUPAON_DCAN1_CLKCTRL_RESERVED2_MASK                                                             (0xfe000000U)

#define CM_WKUPAON_SCRM_CLKCTRL_OPTFCLKEN_SCRM_CORE_SHIFT                                                   (8U)
#define CM_WKUPAON_SCRM_CLKCTRL_OPTFCLKEN_SCRM_CORE_MASK                                                    (0x00000100U)
#define CM_WKUPAON_SCRM_CLKCTRL_OPTFCLKEN_SCRM_CORE_FCLK_EN                                                  (1U)
#define CM_WKUPAON_SCRM_CLKCTRL_OPTFCLKEN_SCRM_CORE_FCLK_DIS                                                 (0U)

#define CM_WKUPAON_SCRM_CLKCTRL_RESERVED_SHIFT                                                              (0U)
#define CM_WKUPAON_SCRM_CLKCTRL_RESERVED_MASK                                                               (0x000000ffU)

#define CM_WKUPAON_SCRM_CLKCTRL_RESERVED1_SHIFT                                                             (10U)
#define CM_WKUPAON_SCRM_CLKCTRL_RESERVED1_MASK                                                              (0xfffffc00U)

#define CM_WKUPAON_SCRM_CLKCTRL_OPTFCLKEN_SCRM_PER_SHIFT                                                    (9U)
#define CM_WKUPAON_SCRM_CLKCTRL_OPTFCLKEN_SCRM_PER_MASK                                                     (0x00000200U)
#define CM_WKUPAON_SCRM_CLKCTRL_OPTFCLKEN_SCRM_PER_FCLK_EN                                                   (1U)
#define CM_WKUPAON_SCRM_CLKCTRL_OPTFCLKEN_SCRM_PER_FCLK_DIS                                                  (0U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_WKUPAON_CM_H_ */
