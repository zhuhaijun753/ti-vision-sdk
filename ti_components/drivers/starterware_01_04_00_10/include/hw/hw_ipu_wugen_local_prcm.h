/******************************************************************************
*
* hw_ipu_wugen_local_prcm.h - register-level header file for IPU
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
#ifndef HW_IPU_WUGEN_LOCAL_PRCM_H_
#define HW_IPU_WUGEN_LOCAL_PRCM_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define IPU_STANDBY_CORE_SYSCONFIG                                                                          (0x4U)
#define IPU_IDLE_CORE_SYSCONFIG                                                                             (0x8U)
#define IPU_WUGEN_MEVT0                                                                                     (uint32_t)(0xcU)
#define IPU_WUGEN_MEVT1                                                                                     (0x10U)
#define IPU_CORTEXM4_CTRL_REG                                                                               (0x0U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define IPU_STANDBY_CORE_SYSCONFIG_STANDBYMODE_SHIFT                                                        (0U)
#define IPU_STANDBY_CORE_SYSCONFIG_STANDBYMODE_MASK                                                         (0x00000003U)

#define IPU_STANDBY_CORE_SYSCONFIG_RESERVED_SHIFT                                                           (2U)
#define IPU_STANDBY_CORE_SYSCONFIG_RESERVED_MASK                                                            (0xfffffffcU)

#define IPU_IDLE_CORE_SYSCONFIG_IDLEMODE_SHIFT                                                              (0U)
#define IPU_IDLE_CORE_SYSCONFIG_IDLEMODE_MASK                                                               (0x00000003U)

#define IPU_IDLE_CORE_SYSCONFIG_RESERVED_SHIFT                                                              (2U)
#define IPU_IDLE_CORE_SYSCONFIG_RESERVED_MASK                                                               (0xfffffffcU)

#define IPU_WUGEN_MEVT0_MIRQ0_SHIFT                                                                         (0U)
#define IPU_WUGEN_MEVT0_MIRQ0_MASK                                                                          (0x00000001U)

#define IPU_WUGEN_MEVT0_MIRQ1_SHIFT                                                                         (1U)
#define IPU_WUGEN_MEVT0_MIRQ1_MASK                                                                          (0x00000002U)

#define IPU_WUGEN_MEVT0_MIRQ2_SHIFT                                                                         (2U)
#define IPU_WUGEN_MEVT0_MIRQ2_MASK                                                                          (0x00000004U)

#define IPU_WUGEN_MEVT0_MIRQ3_SHIFT                                                                         (3U)
#define IPU_WUGEN_MEVT0_MIRQ3_MASK                                                                          (0x00000008U)

#define IPU_WUGEN_MEVT0_MIRQ4_SHIFT                                                                         (4U)
#define IPU_WUGEN_MEVT0_MIRQ4_MASK                                                                          (0x00000010U)

#define IPU_WUGEN_MEVT0_MIRQ5_SHIFT                                                                         (5U)
#define IPU_WUGEN_MEVT0_MIRQ5_MASK                                                                          (0x00000020U)

#define IPU_WUGEN_MEVT0_MIRQ6_SHIFT                                                                         (6U)
#define IPU_WUGEN_MEVT0_MIRQ6_MASK                                                                          (0x00000040U)

#define IPU_WUGEN_MEVT0_MIRQ7_SHIFT                                                                         (7U)
#define IPU_WUGEN_MEVT0_MIRQ7_MASK                                                                          (0x00000080U)

#define IPU_WUGEN_MEVT0_MIRQ8_SHIFT                                                                         (8U)
#define IPU_WUGEN_MEVT0_MIRQ8_MASK                                                                          (0x00000100U)

#define IPU_WUGEN_MEVT0_MIRQ9_SHIFT                                                                         (9U)
#define IPU_WUGEN_MEVT0_MIRQ9_MASK                                                                          (0x00000200U)

#define IPU_WUGEN_MEVT0_MIRQ10_SHIFT                                                                        (10U)
#define IPU_WUGEN_MEVT0_MIRQ10_MASK                                                                         (0x00000400U)

#define IPU_WUGEN_MEVT0_MIRQ11_SHIFT                                                                        (11U)
#define IPU_WUGEN_MEVT0_MIRQ11_MASK                                                                         (0x00000800U)

#define IPU_WUGEN_MEVT0_MIRQ12_SHIFT                                                                        (12U)
#define IPU_WUGEN_MEVT0_MIRQ12_MASK                                                                         (0x00001000U)

#define IPU_WUGEN_MEVT0_MIRQ13_SHIFT                                                                        (13U)
#define IPU_WUGEN_MEVT0_MIRQ13_MASK                                                                         (0x00002000U)

#define IPU_WUGEN_MEVT0_MIRQ14_SHIFT                                                                        (14U)
#define IPU_WUGEN_MEVT0_MIRQ14_MASK                                                                         (0x00004000U)

#define IPU_WUGEN_MEVT0_MIRQ15_SHIFT                                                                        (15U)
#define IPU_WUGEN_MEVT0_MIRQ15_MASK                                                                         (0x00008000U)

#define IPU_WUGEN_MEVT0_MIRQ16_SHIFT                                                                        (16U)
#define IPU_WUGEN_MEVT0_MIRQ16_MASK                                                                         (0x00010000U)

#define IPU_WUGEN_MEVT0_MIRQ17_SHIFT                                                                        (17U)
#define IPU_WUGEN_MEVT0_MIRQ17_MASK                                                                         (0x00020000U)

#define IPU_WUGEN_MEVT0_MIRQ18_SHIFT                                                                        (18U)
#define IPU_WUGEN_MEVT0_MIRQ18_MASK                                                                         (0x00040000U)

#define IPU_WUGEN_MEVT0_MIRQ19_SHIFT                                                                        (19U)
#define IPU_WUGEN_MEVT0_MIRQ19_MASK                                                                         (0x00080000U)

#define IPU_WUGEN_MEVT0_MIRQ20_SHIFT                                                                        (20U)
#define IPU_WUGEN_MEVT0_MIRQ20_MASK                                                                         (0x00100000U)

#define IPU_WUGEN_MEVT0_MIRQ21_SHIFT                                                                        (21U)
#define IPU_WUGEN_MEVT0_MIRQ21_MASK                                                                         (0x00200000U)

#define IPU_WUGEN_MEVT0_MIRQ22_SHIFT                                                                        (22U)
#define IPU_WUGEN_MEVT0_MIRQ22_MASK                                                                         (0x00400000U)

#define IPU_WUGEN_MEVT0_MIRQ23_SHIFT                                                                        (23U)
#define IPU_WUGEN_MEVT0_MIRQ23_MASK                                                                         (0x00800000U)

#define IPU_WUGEN_MEVT0_MIRQ24_SHIFT                                                                        (24U)
#define IPU_WUGEN_MEVT0_MIRQ24_MASK                                                                         (0x01000000U)

#define IPU_WUGEN_MEVT0_MIRQ25_SHIFT                                                                        (25U)
#define IPU_WUGEN_MEVT0_MIRQ25_MASK                                                                         (0x02000000U)

#define IPU_WUGEN_MEVT0_MIRQ26_SHIFT                                                                        (26U)
#define IPU_WUGEN_MEVT0_MIRQ26_MASK                                                                         (0x04000000U)

#define IPU_WUGEN_MEVT0_MIRQ27_SHIFT                                                                        (27U)
#define IPU_WUGEN_MEVT0_MIRQ27_MASK                                                                         (0x08000000U)

#define IPU_WUGEN_MEVT0_MIRQ28_SHIFT                                                                        (28U)
#define IPU_WUGEN_MEVT0_MIRQ28_MASK                                                                         (0x10000000U)

#define IPU_WUGEN_MEVT0_MIRQ29_SHIFT                                                                        (29U)
#define IPU_WUGEN_MEVT0_MIRQ29_MASK                                                                         (0x20000000U)

#define IPU_WUGEN_MEVT0_MIRQ30_SHIFT                                                                        (30U)
#define IPU_WUGEN_MEVT0_MIRQ30_MASK                                                                         (0x40000000U)

#define IPU_WUGEN_MEVT0_MIRQ31_SHIFT                                                                        (31U)
#define IPU_WUGEN_MEVT0_MIRQ31_MASK                                                                         (0x80000000U)

#define IPU_WUGEN_MEVT1_MIRQ32_SHIFT                                                                        (0U)
#define IPU_WUGEN_MEVT1_MIRQ32_MASK                                                                         (0x00000001U)

#define IPU_WUGEN_MEVT1_MIRQ33_SHIFT                                                                        (1U)
#define IPU_WUGEN_MEVT1_MIRQ33_MASK                                                                         (0x00000002U)

#define IPU_WUGEN_MEVT1_MIRQ34_SHIFT                                                                        (2U)
#define IPU_WUGEN_MEVT1_MIRQ34_MASK                                                                         (0x00000004U)

#define IPU_WUGEN_MEVT1_MIRQ35_SHIFT                                                                        (3U)
#define IPU_WUGEN_MEVT1_MIRQ35_MASK                                                                         (0x00000008U)

#define IPU_WUGEN_MEVT1_MIRQ36_SHIFT                                                                        (4U)
#define IPU_WUGEN_MEVT1_MIRQ36_MASK                                                                         (0x00000010U)

#define IPU_WUGEN_MEVT1_MIRQ37_SHIFT                                                                        (5U)
#define IPU_WUGEN_MEVT1_MIRQ37_MASK                                                                         (0x00000020U)

#define IPU_WUGEN_MEVT1_MIRQ38_SHIFT                                                                        (6U)
#define IPU_WUGEN_MEVT1_MIRQ38_MASK                                                                         (0x00000040U)

#define IPU_WUGEN_MEVT1_MIRQ39_SHIFT                                                                        (7U)
#define IPU_WUGEN_MEVT1_MIRQ39_MASK                                                                         (0x00000080U)

#define IPU_WUGEN_MEVT1_MIRQ40_SHIFT                                                                        (8U)
#define IPU_WUGEN_MEVT1_MIRQ40_MASK                                                                         (0x00000100U)

#define IPU_WUGEN_MEVT1_MIRQ41_SHIFT                                                                        (9U)
#define IPU_WUGEN_MEVT1_MIRQ41_MASK                                                                         (0x00000200U)

#define IPU_WUGEN_MEVT1_MIRQ42_SHIFT                                                                        (10U)
#define IPU_WUGEN_MEVT1_MIRQ42_MASK                                                                         (0x00000400U)

#define IPU_WUGEN_MEVT1_MIRQ43_SHIFT                                                                        (11U)
#define IPU_WUGEN_MEVT1_MIRQ43_MASK                                                                         (0x00000800U)

#define IPU_WUGEN_MEVT1_MIRQ44_SHIFT                                                                        (12U)
#define IPU_WUGEN_MEVT1_MIRQ44_MASK                                                                         (0x00001000U)

#define IPU_WUGEN_MEVT1_MIRQ45_SHIFT                                                                        (13U)
#define IPU_WUGEN_MEVT1_MIRQ45_MASK                                                                         (0x00002000U)

#define IPU_WUGEN_MEVT1_MIRQ46_SHIFT                                                                        (14U)
#define IPU_WUGEN_MEVT1_MIRQ46_MASK                                                                         (0x00004000U)

#define IPU_WUGEN_MEVT1_MIRQ47_SHIFT                                                                        (15U)
#define IPU_WUGEN_MEVT1_MIRQ47_MASK                                                                         (0x00008000U)

#define IPU_WUGEN_MEVT1_MIRQ48_SHIFT                                                                        (16U)
#define IPU_WUGEN_MEVT1_MIRQ48_MASK                                                                         (0x00010000U)

#define IPU_WUGEN_MEVT1_MIRQ49_SHIFT                                                                        (17U)
#define IPU_WUGEN_MEVT1_MIRQ49_MASK                                                                         (0x00020000U)

#define IPU_WUGEN_MEVT1_MIRQ50_SHIFT                                                                        (18U)
#define IPU_WUGEN_MEVT1_MIRQ50_MASK                                                                         (0x00040000U)

#define IPU_WUGEN_MEVT1_MIRQ51_SHIFT                                                                        (19U)
#define IPU_WUGEN_MEVT1_MIRQ51_MASK                                                                         (0x00080000U)

#define IPU_WUGEN_MEVT1_MIRQ52_SHIFT                                                                        (20U)
#define IPU_WUGEN_MEVT1_MIRQ52_MASK                                                                         (0x00100000U)

#define IPU_WUGEN_MEVT1_MIRQ53_SHIFT                                                                        (21U)
#define IPU_WUGEN_MEVT1_MIRQ53_MASK                                                                         (0x00200000U)

#define IPU_WUGEN_MEVT1_MIRQ54_SHIFT                                                                        (22U)
#define IPU_WUGEN_MEVT1_MIRQ54_MASK                                                                         (0x00400000U)

#define IPU_WUGEN_MEVT1_MIRQ55_SHIFT                                                                        (23U)
#define IPU_WUGEN_MEVT1_MIRQ55_MASK                                                                         (0x00800000U)

#define IPU_WUGEN_MEVT1_MIRQ56_SHIFT                                                                        (24U)
#define IPU_WUGEN_MEVT1_MIRQ56_MASK                                                                         (0x01000000U)

#define IPU_WUGEN_MEVT1_MIRQ57_SHIFT                                                                        (25U)
#define IPU_WUGEN_MEVT1_MIRQ57_MASK                                                                         (0x02000000U)

#define IPU_WUGEN_MEVT1_MIRQ58_SHIFT                                                                        (26U)
#define IPU_WUGEN_MEVT1_MIRQ58_MASK                                                                         (0x04000000U)

#define IPU_WUGEN_MEVT1_MIRQ59_SHIFT                                                                        (27U)
#define IPU_WUGEN_MEVT1_MIRQ59_MASK                                                                         (0x08000000U)

#define IPU_WUGEN_MEVT1_MIRQ60_SHIFT                                                                        (28U)
#define IPU_WUGEN_MEVT1_MIRQ60_MASK                                                                         (0x10000000U)

#define IPU_WUGEN_MEVT1_MIRQ61_SHIFT                                                                        (29U)
#define IPU_WUGEN_MEVT1_MIRQ61_MASK                                                                         (0x20000000U)

#define IPU_WUGEN_MEVT1_MIRQ62_SHIFT                                                                        (30U)
#define IPU_WUGEN_MEVT1_MIRQ62_MASK                                                                         (0x40000000U)

#define IPU_WUGEN_MEVT1_MIRQ63_SHIFT                                                                        (31U)
#define IPU_WUGEN_MEVT1_MIRQ63_MASK                                                                         (0x80000000U)

#define IPU_CORTEXM4_CTRL_REG_INT_CORTEX_1_SHIFT                                                            (0U)
#define IPU_CORTEXM4_CTRL_REG_INT_CORTEX_1_MASK                                                             (0x00000001U)

#define IPU_CORTEXM4_CTRL_REG_INT_CORTEX_2_SHIFT                                                            (16U)
#define IPU_CORTEXM4_CTRL_REG_INT_CORTEX_2_MASK                                                             (0x00010000U)

#define IPU_CORTEXM4_CTRL_REG_RESERVED_SHIFT                                                                (1U)
#define IPU_CORTEXM4_CTRL_REG_RESERVED_MASK                                                                 (0x0000fffeU)

#define IPU_CORTEXM4_CTRL_REG_RESERVED1_SHIFT                                                               (17U)
#define IPU_CORTEXM4_CTRL_REG_RESERVED1_MASK                                                                (0xfffe0000U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_IPU_WUGEN_LOCAL_PRCM_H_ */
