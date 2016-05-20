/******************************************************************************
*
* hw_cmi.h - register-level header file for PRCM
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
#ifndef HW_CMI_H_
#define HW_CMI_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define CMI_IDENTICATION                                                                                    (0x0U)
#define CMI_SYS_CONFIG                                                                                      (0x10U)
#define CMI_STATUS                                                                                          (0x14U)
#define CMI_CONFIGURATION                                                                                   (0x24U)
#define CMI_CLASS_FILTERING                                                                                 (0x28U)
#define CMI_TRIGGERING                                                                                      (0x2cU)
#define CMI_SAMPLING                                                                                        (0x30U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define CMI_IDENTICATION_MINOR_SHIFT                                                                        (0U)
#define CMI_IDENTICATION_MINOR_MASK                                                                         (0x0000003fU)

#define CMI_IDENTICATION_CUSTOM_SHIFT                                                                       (6U)
#define CMI_IDENTICATION_CUSTOM_MASK                                                                        (0x000000c0U)

#define CMI_IDENTICATION_MAJOR_SHIFT                                                                        (8U)
#define CMI_IDENTICATION_MAJOR_MASK                                                                         (0x00000700U)

#define CMI_IDENTICATION_RTL_SHIFT                                                                          (11U)
#define CMI_IDENTICATION_RTL_MASK                                                                           (0x0000f800U)

#define CMI_IDENTICATION_FUNC_SHIFT                                                                         (16U)
#define CMI_IDENTICATION_FUNC_MASK                                                                          (0x0fff0000U)

#define CMI_IDENTICATION_RESERVED_SHIFT                                                                     (28U)
#define CMI_IDENTICATION_RESERVED_MASK                                                                      (0x30000000U)

#define CMI_IDENTICATION_SCHEME_SHIFT                                                                       (30U)
#define CMI_IDENTICATION_SCHEME_MASK                                                                        (0xc0000000U)

#define CMI_SYS_CONFIG_SOFTRESET_SHIFT                                                                      (0U)
#define CMI_SYS_CONFIG_SOFTRESET_MASK                                                                       (0x00000001U)

#define CMI_SYS_CONFIG_RESERVED_1_SHIFT                                                                     (1U)
#define CMI_SYS_CONFIG_RESERVED_1_MASK                                                                      (0x00000002U)

#define CMI_SYS_CONFIG_IDLEMODE_SHIFT                                                                       (2U)
#define CMI_SYS_CONFIG_IDLEMODE_MASK                                                                        (0x0000000cU)

#define CMI_SYS_CONFIG_RESERVED_2_SHIFT                                                                     (4U)
#define CMI_SYS_CONFIG_RESERVED_2_MASK                                                                      (0x00000030U)

#define CMI_SYS_CONFIG_RESERVED_3_SHIFT                                                                     (6U)
#define CMI_SYS_CONFIG_RESERVED_3_MASK                                                                      (0xffffffc0U)

#define CMI_STATUS_RESERVED_1_SHIFT                                                                         (0U)
#define CMI_STATUS_RESERVED_1_MASK                                                                          (0x000000ffU)

#define CMI_STATUS_FIFOEMPTY_SHIFT                                                                          (8U)
#define CMI_STATUS_FIFOEMPTY_MASK                                                                           (0x00000100U)

#define CMI_STATUS_RESERVED_2_SHIFT                                                                         (9U)
#define CMI_STATUS_RESERVED_2_MASK                                                                          (0xfffffe00U)

#define CMI_CONFIGURATION_RESERVED_1_SHIFT                                                                  (0U)
#define CMI_CONFIGURATION_RESERVED_1_MASK                                                                   (0x0000007fU)

#define CMI_CONFIGURATION_EVT_CAPT_EN_SHIFT                                                                 (7U)
#define CMI_CONFIGURATION_EVT_CAPT_EN_MASK                                                                  (0x00000080U)

#define CMI_CONFIGURATION_RESERVED_2_SHIFT                                                                  (8U)
#define CMI_CONFIGURATION_RESERVED_2_MASK                                                                   (0x00007f00U)

#define CMI_CONFIGURATION_MOD_ACT_EN_SHIFT                                                                  (15U)
#define CMI_CONFIGURATION_MOD_ACT_EN_MASK                                                                   (0x00008000U)

#define CMI_CONFIGURATION_RESERVED_4_SHIFT                                                                  (16U)
#define CMI_CONFIGURATION_RESERVED_4_MASK                                                                   (0x007f0000U)

#define CMI_CONFIGURATION_RESERVED_5_SHIFT                                                                  (23U)
#define CMI_CONFIGURATION_RESERVED_5_MASK                                                                   (0x00800000U)

#define CMI_CONFIGURATION_RESERVED_6_SHIFT                                                                  (24U)
#define CMI_CONFIGURATION_RESERVED_6_MASK                                                                   (0x0f000000U)

#define CMI_CONFIGURATION_CLAIM_1_SHIFT                                                                     (28U)
#define CMI_CONFIGURATION_CLAIM_1_MASK                                                                      (0x10000000U)

#define CMI_CONFIGURATION_CLAIM_2_SHIFT                                                                     (29U)
#define CMI_CONFIGURATION_CLAIM_2_MASK                                                                      (0x20000000U)

#define CMI_CONFIGURATION_CLAIM_3_SHIFT                                                                     (30U)
#define CMI_CONFIGURATION_CLAIM_3_MASK                                                                      (0xc0000000U)

#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_00_SHIFT                                                           (0U)
#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_00_MASK                                                            (0x00000001U)

#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_01_SHIFT                                                           (1U)
#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_01_MASK                                                            (0x00000002U)

#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_02_SHIFT                                                           (2U)
#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_02_MASK                                                            (0x00000004U)

#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_03_SHIFT                                                           (3U)
#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_03_MASK                                                            (0x00000008U)

#define CMI_CLASS_FILTERING_RESERVED_SHIFT                                                                  (4U)
#define CMI_CLASS_FILTERING_RESERVED_MASK                                                                   (0x0000fff0U)

#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_10_SHIFT                                                           (16U)
#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_10_MASK                                                            (0x00010000U)

#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_11_SHIFT                                                           (17U)
#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_11_MASK                                                            (0x00020000U)

#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_12_SHIFT                                                           (18U)
#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_12_MASK                                                            (0x00040000U)

#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_13_SHIFT                                                           (19U)
#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_13_MASK                                                            (0x00080000U)

#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_14_SHIFT                                                           (20U)
#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_14_MASK                                                            (0x00100000U)

#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_15_SHIFT                                                           (21U)
#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_15_MASK                                                            (0x00200000U)

#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_16_SHIFT                                                           (22U)
#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_16_MASK                                                            (0x00400000U)

#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_17_SHIFT                                                           (23U)
#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_17_MASK                                                            (0x00800000U)

#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_18_SHIFT                                                           (24U)
#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_18_MASK                                                            (0x01000000U)

#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_19_SHIFT                                                           (25U)
#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_19_MASK                                                            (0x02000000U)

#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_1A_SHIFT                                                           (26U)
#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_1A_MASK                                                            (0x04000000U)

#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_1B_SHIFT                                                           (27U)
#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_1B_MASK                                                            (0x08000000U)

#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_1C_SHIFT                                                           (28U)
#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_1C_MASK                                                            (0x10000000U)

#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_1D_SHIFT                                                           (29U)
#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_1D_MASK                                                            (0x20000000U)

#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_1E_SHIFT                                                           (30U)
#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_1E_MASK                                                            (0x40000000U)

#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_1F_SHIFT                                                           (31U)
#define CMI_CLASS_FILTERING_SNAP_CAPT_EN_1F_MASK                                                            (0x80000000U)

#define CMI_TRIGGERING_TRIG_START_EN_SHIFT                                                                  (0U)
#define CMI_TRIGGERING_TRIG_START_EN_MASK                                                                   (0x00000001U)

#define CMI_TRIGGERING_TRIG_STOP_EN_SHIFT                                                                   (1U)
#define CMI_TRIGGERING_TRIG_STOP_EN_MASK                                                                    (0x00000002U)

#define CMI_TRIGGERING_RESERVED_SHIFT                                                                       (2U)
#define CMI_TRIGGERING_RESERVED_MASK                                                                        (0xfffffffcU)

#define CMI_SAMPLING_SAMP_WIND_SIZE_SHIFT                                                                   (0U)
#define CMI_SAMPLING_SAMP_WIND_SIZE_MASK                                                                    (0x000000ffU)

#define CMI_SAMPLING_RESERVED_0_SHIFT                                                                       (8U)
#define CMI_SAMPLING_RESERVED_0_MASK                                                                        (0x0000ff00U)

#define CMI_SAMPLING_FCLK_DIV_FACOR_SHIFT                                                                   (16U)
#define CMI_SAMPLING_FCLK_DIV_FACOR_MASK                                                                    (0x000f0000U)

#define CMI_SAMPLING_RESERVED_1_SHIFT                                                                       (20U)
#define CMI_SAMPLING_RESERVED_1_MASK                                                                        (0xfff00000U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_CMI_H_ */
