/******************************************************************************
*
* hw_restore_cm_core_aon.h - register-level header file for PRCM
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
#ifndef HW_RESTORE_CM_CORE_AON_H_
#define HW_RESTORE_CM_CORE_AON_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define CM_CLKSEL_CORE_RESTORE                                                                              (0x0U)
#define CM_DIV_M2_DPLL_CORE_RESTORE                                                                         (0x4U)
#define CM_DIV_H12_DPLL_CORE_RESTORE                                                                        (0x10U)
#define CM_DIV_H13_DPLL_CORE_RESTORE                                                                        (0x14U)
#define CM_DIV_H14_DPLL_CORE_RESTORE                                                                        (0x18U)
#define CM_DIV_H22_DPLL_CORE_RESTORE                                                                        (0x20U)
#define CM_DIV_H23_DPLL_CORE_RESTORE                                                                        (0x24U)
#define CM_DIV_H24_DPLL_CORE_RESTORE                                                                        (0x28U)
#define CM_CLKSEL_DPLL_CORE_RESTORE                                                                         (0x2cU)
#define CM_SSC_DELTAMSTEP_DPLL_CORE_RESTORE                                                                 (0x30U)
#define CM_SSC_MODFREQDIV_DPLL_CORE_RESTORE                                                                 (0x34U)
#define CM_CLKMODE_DPLL_CORE_RESTORE                                                                        (0x38U)
#define CM_SHADOW_FREQ_CONFIG2_RESTORE                                                                      (0x3cU)
#define CM_SHADOW_FREQ_CONFIG1_RESTORE                                                                      (0x40U)
#define CM_AUTOIDLE_DPLL_CORE_RESTORE                                                                       (0x44U)
#define CM_MPU_CLKSTCTRL_RESTORE                                                                            (0x48U)
#define CM_CM_CORE_AON_PROFILING_CLKCTRL_RESTORE                                                            (0x4cU)
#define CM_DYN_DEP_PRESCAL_RESTORE                                                                          (0x50U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define CM_CLKSEL_CORE_RESTORE_RESTORE_SHIFT                                                                (0U)
#define CM_CLKSEL_CORE_RESTORE_RESTORE_MASK                                                                 (0xffffffffU)

#define CM_DIV_M2_DPLL_CORE_RESTORE_RESTORE_SHIFT                                                           (0U)
#define CM_DIV_M2_DPLL_CORE_RESTORE_RESTORE_MASK                                                            (0xffffffffU)

#define CM_DIV_H12_DPLL_CORE_RESTORE_RESTORE_SHIFT                                                          (0U)
#define CM_DIV_H12_DPLL_CORE_RESTORE_RESTORE_MASK                                                           (0xffffffffU)

#define CM_DIV_H13_DPLL_CORE_RESTORE_RESTORE_SHIFT                                                          (0U)
#define CM_DIV_H13_DPLL_CORE_RESTORE_RESTORE_MASK                                                           (0xffffffffU)

#define CM_DIV_H14_DPLL_CORE_RESTORE_RESTORE_SHIFT                                                          (0U)
#define CM_DIV_H14_DPLL_CORE_RESTORE_RESTORE_MASK                                                           (0xffffffffU)

#define CM_DIV_H22_DPLL_CORE_RESTORE_RESTORE_SHIFT                                                          (0U)
#define CM_DIV_H22_DPLL_CORE_RESTORE_RESTORE_MASK                                                           (0xffffffffU)

#define CM_DIV_H23_DPLL_CORE_RESTORE_RESTORE_SHIFT                                                          (0U)
#define CM_DIV_H23_DPLL_CORE_RESTORE_RESTORE_MASK                                                           (0xffffffffU)

#define CM_DIV_H24_DPLL_CORE_RESTORE_RESTORE_SHIFT                                                          (0U)
#define CM_DIV_H24_DPLL_CORE_RESTORE_RESTORE_MASK                                                           (0xffffffffU)

#define CM_CLKSEL_DPLL_CORE_RESTORE_RESTORE_SHIFT                                                           (0U)
#define CM_CLKSEL_DPLL_CORE_RESTORE_RESTORE_MASK                                                            (0xffffffffU)

#define CM_SSC_DELTAMSTEP_DPLL_CORE_RESTORE_RESTORE_SHIFT                                                   (0U)
#define CM_SSC_DELTAMSTEP_DPLL_CORE_RESTORE_RESTORE_MASK                                                    (0xffffffffU)

#define CM_SSC_MODFREQDIV_DPLL_CORE_RESTORE_RESTORE_SHIFT                                                   (0U)
#define CM_SSC_MODFREQDIV_DPLL_CORE_RESTORE_RESTORE_MASK                                                    (0xffffffffU)

#define CM_CLKMODE_DPLL_CORE_RESTORE_RESTORE_SHIFT                                                          (0U)
#define CM_CLKMODE_DPLL_CORE_RESTORE_RESTORE_MASK                                                           (0xffffffffU)

#define CM_SHADOW_FREQ_CONFIG2_RESTORE_RESTORE_SHIFT                                                        (0U)
#define CM_SHADOW_FREQ_CONFIG2_RESTORE_RESTORE_MASK                                                         (0xffffffffU)

#define CM_SHADOW_FREQ_CONFIG1_RESTORE_RESTORE_SHIFT                                                        (0U)
#define CM_SHADOW_FREQ_CONFIG1_RESTORE_RESTORE_MASK                                                         (0xffffffffU)

#define CM_AUTOIDLE_DPLL_CORE_RESTORE_RESTORE_SHIFT                                                         (0U)
#define CM_AUTOIDLE_DPLL_CORE_RESTORE_RESTORE_MASK                                                          (0xffffffffU)

#define CM_MPU_CLKSTCTRL_RESTORE_RESTORE_SHIFT                                                              (0U)
#define CM_MPU_CLKSTCTRL_RESTORE_RESTORE_MASK                                                               (0xffffffffU)

#define CM_CM_CORE_AON_PROFILING_CLKCTRL_RESTORE_RESTORE_SHIFT                                              (0U)
#define CM_CM_CORE_AON_PROFILING_CLKCTRL_RESTORE_RESTORE_MASK                                               (0xffffffffU)

#define CM_DYN_DEP_PRESCAL_RESTORE_RESTORE_SHIFT                                                            (0U)
#define CM_DYN_DEP_PRESCAL_RESTORE_RESTORE_MASK                                                             (0xffffffffU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_RESTORE_CM_CORE_AON_H_ */
