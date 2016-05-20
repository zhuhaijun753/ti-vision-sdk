/******************************************************************************
*
* hw_pmi.h - register-level header file for PRCM
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
#ifndef HW_PMI_H_
#define HW_PMI_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define PMI_IDENTICATION                                                                                    (0x0U)
#define PMI_SYS_CONFIG                                                                                      (0x10U)
#define PMI_STATUS                                                                                          (0x14U)
#define PMI_CONFIGURATION                                                                                   (0x24U)
#define PMI_CLASS_FILTERING                                                                                 (0x28U)
#define PMI_TRIGGERING                                                                                      (0x2cU)
#define PMI_SAMPLING                                                                                        (0x30U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define PMI_IDENTICATION_MINOR_SHIFT                                                                        (0U)
#define PMI_IDENTICATION_MINOR_MASK                                                                         (0x0000003fU)

#define PMI_IDENTICATION_CUSTOM_SHIFT                                                                       (6U)
#define PMI_IDENTICATION_CUSTOM_MASK                                                                        (0x000000c0U)

#define PMI_IDENTICATION_MAJOR_SHIFT                                                                        (8U)
#define PMI_IDENTICATION_MAJOR_MASK                                                                         (0x00000700U)

#define PMI_IDENTICATION_RTL_SHIFT                                                                          (11U)
#define PMI_IDENTICATION_RTL_MASK                                                                           (0x0000f800U)

#define PMI_IDENTICATION_FUNC_SHIFT                                                                         (16U)
#define PMI_IDENTICATION_FUNC_MASK                                                                          (0x0fff0000U)

#define PMI_IDENTICATION_RESERVED_SHIFT                                                                     (28U)
#define PMI_IDENTICATION_RESERVED_MASK                                                                      (0x30000000U)

#define PMI_IDENTICATION_SCHEME_SHIFT                                                                       (30U)
#define PMI_IDENTICATION_SCHEME_MASK                                                                        (0xc0000000U)

#define PMI_SYS_CONFIG_SOFTRESET_SHIFT                                                                      (0U)
#define PMI_SYS_CONFIG_SOFTRESET_MASK                                                                       (0x00000001U)

#define PMI_SYS_CONFIG_RESERVED_1_SHIFT                                                                     (1U)
#define PMI_SYS_CONFIG_RESERVED_1_MASK                                                                      (0x00000002U)

#define PMI_SYS_CONFIG_IDLEMODE_SHIFT                                                                       (2U)
#define PMI_SYS_CONFIG_IDLEMODE_MASK                                                                        (0x0000000cU)

#define PMI_SYS_CONFIG_RESERVED_2_SHIFT                                                                     (4U)
#define PMI_SYS_CONFIG_RESERVED_2_MASK                                                                      (0x00000030U)

#define PMI_SYS_CONFIG_RESERVED_3_SHIFT                                                                     (6U)
#define PMI_SYS_CONFIG_RESERVED_3_MASK                                                                      (0xffffffc0U)

#define PMI_STATUS_RESERVED_1_SHIFT                                                                         (0U)
#define PMI_STATUS_RESERVED_1_MASK                                                                          (0x000000ffU)

#define PMI_STATUS_FIFOEMPTY_SHIFT                                                                          (8U)
#define PMI_STATUS_FIFOEMPTY_MASK                                                                           (0x00000100U)

#define PMI_STATUS_RESERVED_2_SHIFT                                                                         (9U)
#define PMI_STATUS_RESERVED_2_MASK                                                                          (0xfffffe00U)

#define PMI_CONFIGURATION_RESERVED_1_SHIFT                                                                  (0U)
#define PMI_CONFIGURATION_RESERVED_1_MASK                                                                   (0x0000007fU)

#define PMI_CONFIGURATION_EVT_CAPT_EN_SHIFT                                                                 (7U)
#define PMI_CONFIGURATION_EVT_CAPT_EN_MASK                                                                  (0x00000080U)

#define PMI_CONFIGURATION_RESERVED_2_SHIFT                                                                  (8U)
#define PMI_CONFIGURATION_RESERVED_2_MASK                                                                   (0x00007f00U)

#define PMI_CONFIGURATION_RESERVED_3_SHIFT                                                                  (15U)
#define PMI_CONFIGURATION_RESERVED_3_MASK                                                                   (0x00008000U)

#define PMI_CONFIGURATION_RESERVED_4_SHIFT                                                                  (16U)
#define PMI_CONFIGURATION_RESERVED_4_MASK                                                                   (0x007f0000U)

#define PMI_CONFIGURATION_RESERVED_5_SHIFT                                                                  (23U)
#define PMI_CONFIGURATION_RESERVED_5_MASK                                                                   (0x00800000U)

#define PMI_CONFIGURATION_RESERVED_6_SHIFT                                                                  (24U)
#define PMI_CONFIGURATION_RESERVED_6_MASK                                                                   (0x0f000000U)

#define PMI_CONFIGURATION_CLAIM_1_SHIFT                                                                     (28U)
#define PMI_CONFIGURATION_CLAIM_1_MASK                                                                      (0x10000000U)

#define PMI_CONFIGURATION_CLAIM_2_SHIFT                                                                     (29U)
#define PMI_CONFIGURATION_CLAIM_2_MASK                                                                      (0x20000000U)

#define PMI_CONFIGURATION_CLAIM_3_SHIFT                                                                     (30U)
#define PMI_CONFIGURATION_CLAIM_3_MASK                                                                      (0xc0000000U)

#define PMI_CLASS_FILTERING_SNAP_CAPT_EN_00_SHIFT                                                           (0U)
#define PMI_CLASS_FILTERING_SNAP_CAPT_EN_00_MASK                                                            (0x00000001U)

#define PMI_CLASS_FILTERING_SNAP_CAPT_EN_01_SHIFT                                                           (1U)
#define PMI_CLASS_FILTERING_SNAP_CAPT_EN_01_MASK                                                            (0x00000002U)

#define PMI_CLASS_FILTERING_SNAP_CAPT_EN_02_SHIFT                                                           (2U)
#define PMI_CLASS_FILTERING_SNAP_CAPT_EN_02_MASK                                                            (0x00000004U)

#define PMI_CLASS_FILTERING_SNAP_CAPT_EN_03_SHIFT                                                           (3U)
#define PMI_CLASS_FILTERING_SNAP_CAPT_EN_03_MASK                                                            (0x00000008U)

#define PMI_CLASS_FILTERING_RESERVED_SHIFT                                                                  (4U)
#define PMI_CLASS_FILTERING_RESERVED_MASK                                                                   (0xfffffff0U)

#define PMI_TRIGGERING_TRIG_START_EN_SHIFT                                                                  (0U)
#define PMI_TRIGGERING_TRIG_START_EN_MASK                                                                   (0x00000001U)

#define PMI_TRIGGERING_TRIG_STOP_EN_SHIFT                                                                   (1U)
#define PMI_TRIGGERING_TRIG_STOP_EN_MASK                                                                    (0x00000002U)

#define PMI_TRIGGERING_RESERVED_SHIFT                                                                       (2U)
#define PMI_TRIGGERING_RESERVED_MASK                                                                        (0xfffffffcU)

#define PMI_SAMPLING_SAMP_WIND_SIZE_SHIFT                                                                   (0U)
#define PMI_SAMPLING_SAMP_WIND_SIZE_MASK                                                                    (0x000000ffU)

#define PMI_SAMPLING_RESERVED_0_SHIFT                                                                       (8U)
#define PMI_SAMPLING_RESERVED_0_MASK                                                                        (0x0000ff00U)

#define PMI_SAMPLING_FCLK_DIV_FACOR_SHIFT                                                                   (16U)
#define PMI_SAMPLING_FCLK_DIV_FACOR_MASK                                                                    (0x000f0000U)

#define PMI_SAMPLING_RESERVED_1_SHIFT                                                                       (20U)
#define PMI_SAMPLING_RESERVED_1_MASK                                                                        (0xfff00000U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_PMI_H_ */
