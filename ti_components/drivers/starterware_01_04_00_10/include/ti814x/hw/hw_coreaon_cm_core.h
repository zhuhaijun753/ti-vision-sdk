/******************************************************************************
*
* hw_coreaon_cm_core.h - register-level header file for PRCM
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
#ifndef HW_COREAON_CM_CORE_H_
#define HW_COREAON_CM_CORE_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define CM_COREAON_CLKSTCTRL                                                                                (0x0U)
#define CM_COREAON_SMARTREFLEX_MPU_CLKCTRL                                                                  (0x28U)
#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL                                                                 (0x38U)
#define CM_COREAON_USB_PHY1_CORE_CLKCTRL                                                                    (0x40U)
#define CM_COREAON_IO_SRCOMP_CLKCTRL                                                                        (0x50U)
#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL                                                                  (0x58U)
#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL                                                               (0x68U)
#define CM_COREAON_SMARTREFLEX_IVAHD_CLKCTRL                                                                (0x78U)
#define CM_COREAON_USB_PHY2_CORE_CLKCTRL                                                                    (0x88U)
#define CM_COREAON_USB_PHY3_CORE_CLKCTRL                                                                    (0x98U)
#define CM_COREAON_DUMMY_MODULE1_CLKCTRL                                                                    (0xa0U)
#define CM_COREAON_DUMMY_MODULE2_CLKCTRL                                                                    (0xb0U)
#define CM_COREAON_DUMMY_MODULE3_CLKCTRL                                                                    (0xc0U)
#define CM_COREAON_DUMMY_MODULE4_CLKCTRL                                                                    (0xd0U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define CM_COREAON_CLKSTCTRL_CLKTRCTRL_SHIFT                                                                (0U)
#define CM_COREAON_CLKSTCTRL_CLKTRCTRL_MASK                                                                 (0x00000003U)
#define CM_COREAON_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                                                              (0U)
#define CM_COREAON_CLKSTCTRL_CLKTRCTRL_RESERVED                                                              (1U)
#define CM_COREAON_CLKSTCTRL_CLKTRCTRL_SW_WKUP                                                               (2U)
#define CM_COREAON_CLKSTCTRL_CLKTRCTRL_HW_AUTO                                                               (3U)

#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_COREAON_L4_GICLK_SHIFT                                             (8U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_COREAON_L4_GICLK_MASK                                              (0x00000100U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_COREAON_L4_GICLK_INACT                                              (0U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_COREAON_L4_GICLK_ACT                                                (1U)

#define CM_COREAON_CLKSTCTRL_RESERVED_SHIFT                                                                 (2U)
#define CM_COREAON_CLKSTCTRL_RESERVED_MASK                                                                  (0x000000fcU)

#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_MPU_SYS_GFCLK_SHIFT                                             (9U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_MPU_SYS_GFCLK_MASK                                              (0x00000200U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_MPU_SYS_GFCLK_INACT                                              (0U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_MPU_SYS_GFCLK_ACT                                                (1U)

#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_GPU_SYS_GFCLK_SHIFT                                             (10U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_GPU_SYS_GFCLK_MASK                                              (0x00000400U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_GPU_SYS_GFCLK_INACT                                              (0U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_GPU_SYS_GFCLK_ACT                                                (1U)

#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_CORE_SYS_GFCLK_SHIFT                                            (11U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_CORE_SYS_GFCLK_MASK                                             (0x00000800U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_CORE_SYS_GFCLK_INACT                                             (0U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_CORE_SYS_GFCLK_ACT                                               (1U)

#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_COREAON_32K_GFCLK_SHIFT                                            (12U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_COREAON_32K_GFCLK_MASK                                             (0x00001000U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_COREAON_32K_GFCLK_INACT                                             (0U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_COREAON_32K_GFCLK_ACT                                               (1U)

#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_DSPEVE_SYS_GFCLK_SHIFT                                          (13U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_DSPEVE_SYS_GFCLK_MASK                                           (0x00002000U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_DSPEVE_SYS_GFCLK_INACT                                           (0U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_DSPEVE_SYS_GFCLK_ACT                                             (1U)

#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_IVAHD_SYS_GFCLK_SHIFT                                           (15U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_IVAHD_SYS_GFCLK_MASK                                            (0x00008000U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_IVAHD_SYS_GFCLK_INACT                                            (0U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_IVAHD_SYS_GFCLK_ACT                                              (1U)

#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_ABE_GICLK_SHIFT                                                    (16U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_ABE_GICLK_MASK                                                     (0x00010000U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_ABE_GICLK_INACT                                                     (0U)
#define CM_COREAON_CLKSTCTRL_CLKACTIVITY_ABE_GICLK_ACT                                                       (1U)

#define CM_COREAON_CLKSTCTRL_RESERVED2_SHIFT                                                                (17U)
#define CM_COREAON_CLKSTCTRL_RESERVED2_MASK                                                                 (0xfffe0000U)

#define CM_COREAON_CLKSTCTRL_RESERVED1_SHIFT                                                                (14U)
#define CM_COREAON_CLKSTCTRL_RESERVED1_MASK                                                                 (0x00004000U)
#define CM_COREAON_CLKSTCTRL_RESERVED1_INACT                                                                 (0U)
#define CM_COREAON_CLKSTCTRL_RESERVED1_ACT                                                                   (1U)

#define CM_COREAON_SMARTREFLEX_MPU_CLKCTRL_IDLEST_SHIFT                                                     (16U)
#define CM_COREAON_SMARTREFLEX_MPU_CLKCTRL_IDLEST_MASK                                                      (0x00030000U)
#define CM_COREAON_SMARTREFLEX_MPU_CLKCTRL_IDLEST_DISABLE                                                    (3U)
#define CM_COREAON_SMARTREFLEX_MPU_CLKCTRL_IDLEST_IDLE                                                       (2U)
#define CM_COREAON_SMARTREFLEX_MPU_CLKCTRL_IDLEST_FUNC                                                       (0U)
#define CM_COREAON_SMARTREFLEX_MPU_CLKCTRL_IDLEST_TRANS                                                      (1U)

#define CM_COREAON_SMARTREFLEX_MPU_CLKCTRL_RESERVED_SHIFT                                                   (2U)
#define CM_COREAON_SMARTREFLEX_MPU_CLKCTRL_RESERVED_MASK                                                    (0x0000fffcU)

#define CM_COREAON_SMARTREFLEX_MPU_CLKCTRL_RESERVED1_SHIFT                                                  (18U)
#define CM_COREAON_SMARTREFLEX_MPU_CLKCTRL_RESERVED1_MASK                                                   (0xfffc0000U)

#define CM_COREAON_SMARTREFLEX_MPU_CLKCTRL_MODULEMODE_SHIFT                                                 (0U)
#define CM_COREAON_SMARTREFLEX_MPU_CLKCTRL_MODULEMODE_MASK                                                  (0x00000003U)
#define CM_COREAON_SMARTREFLEX_MPU_CLKCTRL_MODULEMODE_DISABLED                                               (0U)
#define CM_COREAON_SMARTREFLEX_MPU_CLKCTRL_MODULEMODE_RESERVED_1                                             (1U)
#define CM_COREAON_SMARTREFLEX_MPU_CLKCTRL_MODULEMODE_ENABLE                                                 (2U)
#define CM_COREAON_SMARTREFLEX_MPU_CLKCTRL_MODULEMODE_RESERVED                                               (3U)

#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_IDLEST_SHIFT                                                    (16U)
#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_IDLEST_MASK                                                     (0x00030000U)
#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_IDLEST_DISABLE                                                   (3U)
#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_IDLEST_IDLE                                                      (2U)
#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_IDLEST_FUNC                                                      (0U)
#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_IDLEST_TRANS                                                     (1U)

#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_RESERVED_SHIFT                                                  (2U)
#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_RESERVED_MASK                                                   (0x0000fffcU)

#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_RESERVED1_SHIFT                                                 (18U)
#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_RESERVED1_MASK                                                  (0xfffc0000U)

#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_MODULEMODE_SHIFT                                                (0U)
#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_MODULEMODE_MASK                                                 (0x00000003U)
#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_MODULEMODE_DISABLED                                              (0U)
#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_MODULEMODE_RESERVED_1                                            (1U)
#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_MODULEMODE_ENABLE                                                (2U)
#define CM_COREAON_SMARTREFLEX_CORE_CLKCTRL_MODULEMODE_RESERVED                                              (3U)

#define CM_COREAON_USB_PHY1_CORE_CLKCTRL_OPTFCLKEN_CLK32K_SHIFT                                             (8U)
#define CM_COREAON_USB_PHY1_CORE_CLKCTRL_OPTFCLKEN_CLK32K_MASK                                              (0x00000100U)
#define CM_COREAON_USB_PHY1_CORE_CLKCTRL_OPTFCLKEN_CLK32K_FCLK_EN                                            (1U)
#define CM_COREAON_USB_PHY1_CORE_CLKCTRL_OPTFCLKEN_CLK32K_FCLK_DIS                                           (0U)

#define CM_COREAON_USB_PHY1_CORE_CLKCTRL_RESERVED_SHIFT                                                     (0U)
#define CM_COREAON_USB_PHY1_CORE_CLKCTRL_RESERVED_MASK                                                      (0x000000ffU)

#define CM_COREAON_USB_PHY1_CORE_CLKCTRL_RESERVED1_SHIFT                                                    (9U)
#define CM_COREAON_USB_PHY1_CORE_CLKCTRL_RESERVED1_MASK                                                     (0xfffffe00U)

#define CM_COREAON_IO_SRCOMP_CLKCTRL_CLKEN_SRCOMP_FCLK_SHIFT                                                (8U)
#define CM_COREAON_IO_SRCOMP_CLKCTRL_CLKEN_SRCOMP_FCLK_MASK                                                 (0x00000100U)
#define CM_COREAON_IO_SRCOMP_CLKCTRL_CLKEN_SRCOMP_FCLK_FCLK_DIS                                              (0U)
#define CM_COREAON_IO_SRCOMP_CLKCTRL_CLKEN_SRCOMP_FCLK_FCLK_EN                                               (1U)

#define CM_COREAON_IO_SRCOMP_CLKCTRL_RESERVED_SHIFT                                                         (0U)
#define CM_COREAON_IO_SRCOMP_CLKCTRL_RESERVED_MASK                                                          (0x000000ffU)

#define CM_COREAON_IO_SRCOMP_CLKCTRL_RESERVED1_SHIFT                                                        (9U)
#define CM_COREAON_IO_SRCOMP_CLKCTRL_RESERVED1_MASK                                                         (0xfffffe00U)

#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_IDLEST_SHIFT                                                     (16U)
#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_IDLEST_MASK                                                      (0x00030000U)
#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_IDLEST_DISABLE                                                    (3U)
#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_IDLEST_IDLE                                                       (2U)
#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_IDLEST_FUNC                                                       (0U)
#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_IDLEST_TRANS                                                      (1U)

#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_RESERVED_SHIFT                                                   (2U)
#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_RESERVED_MASK                                                    (0x0000fffcU)

#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_RESERVED1_SHIFT                                                  (18U)
#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_RESERVED1_MASK                                                   (0xfffc0000U)

#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_MODULEMODE_SHIFT                                                 (0U)
#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_MODULEMODE_MASK                                                  (0x00000003U)
#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_MODULEMODE_DISABLED                                               (0U)
#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_MODULEMODE_RESERVED_1                                             (1U)
#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_MODULEMODE_ENABLE                                                 (2U)
#define CM_COREAON_SMARTREFLEX_GPU_CLKCTRL_MODULEMODE_RESERVED                                               (3U)

#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_IDLEST_SHIFT                                                  (16U)
#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_IDLEST_MASK                                                   (0x00030000U)
#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_IDLEST_DISABLE                                                 (3U)
#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_IDLEST_IDLE                                                    (2U)
#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_IDLEST_FUNC                                                    (0U)
#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_IDLEST_TRANS                                                   (1U)

#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_RESERVED_SHIFT                                                (2U)
#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_RESERVED_MASK                                                 (0x0000fffcU)

#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_RESERVED1_SHIFT                                               (18U)
#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_RESERVED1_MASK                                                (0xfffc0000U)

#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_MODULEMODE_SHIFT                                              (0U)
#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_MODULEMODE_MASK                                               (0x00000003U)
#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_MODULEMODE_DISABLED                                            (0U)
#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_MODULEMODE_RESERVED_1                                          (1U)
#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_MODULEMODE_ENABLE                                              (2U)
#define CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL_MODULEMODE_RESERVED                                            (3U)

#define CM_COREAON_SMARTREFLEX_IVAHD_CLKCTRL_IDLEST_SHIFT                                                   (16U)
#define CM_COREAON_SMARTREFLEX_IVAHD_CLKCTRL_IDLEST_MASK                                                    (0x00030000U)
#define CM_COREAON_SMARTREFLEX_IVAHD_CLKCTRL_IDLEST_DISABLE                                                  (3U)
#define CM_COREAON_SMARTREFLEX_IVAHD_CLKCTRL_IDLEST_IDLE                                                     (2U)
#define CM_COREAON_SMARTREFLEX_IVAHD_CLKCTRL_IDLEST_FUNC                                                     (0U)
#define CM_COREAON_SMARTREFLEX_IVAHD_CLKCTRL_IDLEST_TRANS                                                    (1U)

#define CM_COREAON_SMARTREFLEX_IVAHD_CLKCTRL_RESERVED_SHIFT                                                 (2U)
#define CM_COREAON_SMARTREFLEX_IVAHD_CLKCTRL_RESERVED_MASK                                                  (0x0000fffcU)

#define CM_COREAON_SMARTREFLEX_IVAHD_CLKCTRL_RESERVED1_SHIFT                                                (18U)
#define CM_COREAON_SMARTREFLEX_IVAHD_CLKCTRL_RESERVED1_MASK                                                 (0xfffc0000U)

#define CM_COREAON_SMARTREFLEX_IVAHD_CLKCTRL_MODULEMODE_SHIFT                                               (0U)
#define CM_COREAON_SMARTREFLEX_IVAHD_CLKCTRL_MODULEMODE_MASK                                                (0x00000003U)
#define CM_COREAON_SMARTREFLEX_IVAHD_CLKCTRL_MODULEMODE_DISABLED                                             (0U)
#define CM_COREAON_SMARTREFLEX_IVAHD_CLKCTRL_MODULEMODE_RESERVED_1                                           (1U)
#define CM_COREAON_SMARTREFLEX_IVAHD_CLKCTRL_MODULEMODE_ENABLE                                               (2U)
#define CM_COREAON_SMARTREFLEX_IVAHD_CLKCTRL_MODULEMODE_RESERVED                                             (3U)

#define CM_COREAON_USB_PHY2_CORE_CLKCTRL_OPTFCLKEN_CLK32K_SHIFT                                             (8U)
#define CM_COREAON_USB_PHY2_CORE_CLKCTRL_OPTFCLKEN_CLK32K_MASK                                              (0x00000100U)
#define CM_COREAON_USB_PHY2_CORE_CLKCTRL_OPTFCLKEN_CLK32K_FCLK_EN                                            (1U)
#define CM_COREAON_USB_PHY2_CORE_CLKCTRL_OPTFCLKEN_CLK32K_FCLK_DIS                                           (0U)

#define CM_COREAON_USB_PHY2_CORE_CLKCTRL_RESERVED_SHIFT                                                     (0U)
#define CM_COREAON_USB_PHY2_CORE_CLKCTRL_RESERVED_MASK                                                      (0x000000ffU)

#define CM_COREAON_USB_PHY2_CORE_CLKCTRL_RESERVED1_SHIFT                                                    (9U)
#define CM_COREAON_USB_PHY2_CORE_CLKCTRL_RESERVED1_MASK                                                     (0xfffffe00U)

#define CM_COREAON_USB_PHY3_CORE_CLKCTRL_OPTFCLKEN_CLK32K_SHIFT                                             (8U)
#define CM_COREAON_USB_PHY3_CORE_CLKCTRL_OPTFCLKEN_CLK32K_MASK                                              (0x00000100U)
#define CM_COREAON_USB_PHY3_CORE_CLKCTRL_OPTFCLKEN_CLK32K_FCLK_EN                                            (1U)
#define CM_COREAON_USB_PHY3_CORE_CLKCTRL_OPTFCLKEN_CLK32K_FCLK_DIS                                           (0U)

#define CM_COREAON_USB_PHY3_CORE_CLKCTRL_RESERVED_SHIFT                                                     (0U)
#define CM_COREAON_USB_PHY3_CORE_CLKCTRL_RESERVED_MASK                                                      (0x000000ffU)

#define CM_COREAON_USB_PHY3_CORE_CLKCTRL_RESERVED1_SHIFT                                                    (9U)
#define CM_COREAON_USB_PHY3_CORE_CLKCTRL_RESERVED1_MASK                                                     (0xfffffe00U)

#define CM_COREAON_DUMMY_MODULE1_CLKCTRL_OPTFCLKEN_CLKOUTMUX1_CLK_SHIFT                                     (8U)
#define CM_COREAON_DUMMY_MODULE1_CLKCTRL_OPTFCLKEN_CLKOUTMUX1_CLK_MASK                                      (0x00000100U)
#define CM_COREAON_DUMMY_MODULE1_CLKCTRL_OPTFCLKEN_CLKOUTMUX1_CLK_FCLK_EN                                    (1U)
#define CM_COREAON_DUMMY_MODULE1_CLKCTRL_OPTFCLKEN_CLKOUTMUX1_CLK_FCLK_DIS                                   (0U)

#define CM_COREAON_DUMMY_MODULE1_CLKCTRL_RESERVED_SHIFT                                                     (0U)
#define CM_COREAON_DUMMY_MODULE1_CLKCTRL_RESERVED_MASK                                                      (0x000000ffU)

#define CM_COREAON_DUMMY_MODULE1_CLKCTRL_RESERVED1_SHIFT                                                    (9U)
#define CM_COREAON_DUMMY_MODULE1_CLKCTRL_RESERVED1_MASK                                                     (0xfffffe00U)

#define CM_COREAON_DUMMY_MODULE2_CLKCTRL_OPTFCLKEN_CLKOUTMUX2_CLK_SHIFT                                     (8U)
#define CM_COREAON_DUMMY_MODULE2_CLKCTRL_OPTFCLKEN_CLKOUTMUX2_CLK_MASK                                      (0x00000100U)
#define CM_COREAON_DUMMY_MODULE2_CLKCTRL_OPTFCLKEN_CLKOUTMUX2_CLK_FCLK_EN                                    (1U)
#define CM_COREAON_DUMMY_MODULE2_CLKCTRL_OPTFCLKEN_CLKOUTMUX2_CLK_FCLK_DIS                                   (0U)

#define CM_COREAON_DUMMY_MODULE2_CLKCTRL_RESERVED_SHIFT                                                     (0U)
#define CM_COREAON_DUMMY_MODULE2_CLKCTRL_RESERVED_MASK                                                      (0x000000ffU)

#define CM_COREAON_DUMMY_MODULE2_CLKCTRL_RESERVED1_SHIFT                                                    (9U)
#define CM_COREAON_DUMMY_MODULE2_CLKCTRL_RESERVED1_MASK                                                     (0xfffffe00U)

#define CM_COREAON_DUMMY_MODULE3_CLKCTRL_OPTFCLKEN_L3INIT_60M_GFCLK_SHIFT                                   (8U)
#define CM_COREAON_DUMMY_MODULE3_CLKCTRL_OPTFCLKEN_L3INIT_60M_GFCLK_MASK                                    (0x00000100U)
#define CM_COREAON_DUMMY_MODULE3_CLKCTRL_OPTFCLKEN_L3INIT_60M_GFCLK_FCLK_EN                                  (1U)
#define CM_COREAON_DUMMY_MODULE3_CLKCTRL_OPTFCLKEN_L3INIT_60M_GFCLK_FCLK_DIS                                 (0U)

#define CM_COREAON_DUMMY_MODULE3_CLKCTRL_RESERVED_SHIFT                                                     (0U)
#define CM_COREAON_DUMMY_MODULE3_CLKCTRL_RESERVED_MASK                                                      (0x000000ffU)

#define CM_COREAON_DUMMY_MODULE3_CLKCTRL_RESERVED1_SHIFT                                                    (9U)
#define CM_COREAON_DUMMY_MODULE3_CLKCTRL_RESERVED1_MASK                                                     (0xfffffe00U)

#define CM_COREAON_DUMMY_MODULE4_CLKCTRL_OPTFCLKEN_ABE_GICLK_SHIFT                                          (8U)
#define CM_COREAON_DUMMY_MODULE4_CLKCTRL_OPTFCLKEN_ABE_GICLK_MASK                                           (0x00000100U)
#define CM_COREAON_DUMMY_MODULE4_CLKCTRL_OPTFCLKEN_ABE_GICLK_FCLK_EN                                         (1U)
#define CM_COREAON_DUMMY_MODULE4_CLKCTRL_OPTFCLKEN_ABE_GICLK_FCLK_DIS                                        (0U)

#define CM_COREAON_DUMMY_MODULE4_CLKCTRL_RESERVED_SHIFT                                                     (0U)
#define CM_COREAON_DUMMY_MODULE4_CLKCTRL_RESERVED_MASK                                                      (0x000000ffU)

#define CM_COREAON_DUMMY_MODULE4_CLKCTRL_RESERVED1_SHIFT                                                    (9U)
#define CM_COREAON_DUMMY_MODULE4_CLKCTRL_RESERVED1_MASK                                                     (0xfffffe00U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_COREAON_CM_CORE_H_ */
