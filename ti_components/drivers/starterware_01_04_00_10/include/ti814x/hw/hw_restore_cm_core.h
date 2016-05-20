/******************************************************************************
*
* hw_restore_cm_core.h - register-level header file for PRCM
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
#ifndef HW_RESTORE_CM_CORE_H_
#define HW_RESTORE_CM_CORE_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define CM_L3MAIN1_CLKSTCTRL_RESTORE                                                                        (0x0U)
#define CM_L4CFG_CLKSTCTRL_RESTORE                                                                          (0x8U)
#define CM_L4PER_CLKSTCTRL_RESTORE                                                                          (0x10U)
#define CM_L3INIT_CLKSTCTRL_RESTORE                                                                         (0x14U)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_RESTORE                                                                (0x18U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL_RESTORE                                                                 (0x1cU)
#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_RESTORE                                                               (0x20U)
#define CM_CM_CORE_PROFILING_CLKCTRL_RESTORE                                                                (0x24U)
#define CM_L3MAIN1_DYNAMICDEP_RESTORE                                                                       (0x30U)
#define CM_L4CFG_DYNAMICDEP_RESTORE                                                                         (0x40U)
#define CM_L4PER_DYNAMICDEP_RESTORE                                                                         (0x44U)
#define CM_DMA_STATICDEP_RESTORE                                                                            (0x54U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define CM_L3MAIN1_CLKSTCTRL_RESTORE_RESTORE_SHIFT                                                          (0U)
#define CM_L3MAIN1_CLKSTCTRL_RESTORE_RESTORE_MASK                                                           (0xffffffffU)

#define CM_L4CFG_CLKSTCTRL_RESTORE_RESTORE_SHIFT                                                            (0U)
#define CM_L4CFG_CLKSTCTRL_RESTORE_RESTORE_MASK                                                             (0xffffffffU)

#define CM_L4PER_CLKSTCTRL_RESTORE_RESTORE_SHIFT                                                            (0U)
#define CM_L4PER_CLKSTCTRL_RESTORE_RESTORE_MASK                                                             (0xffffffffU)

#define CM_L3INIT_CLKSTCTRL_RESTORE_RESTORE_SHIFT                                                           (0U)
#define CM_L3INIT_CLKSTCTRL_RESTORE_RESTORE_MASK                                                            (0xffffffffU)

#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_RESTORE_RESTORE_SHIFT                                                  (0U)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_RESTORE_RESTORE_MASK                                                   (0xffffffffU)

#define CM_L3INSTR_L3_INSTR_CLKCTRL_RESTORE_RESTORE_SHIFT                                                   (0U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL_RESTORE_RESTORE_MASK                                                    (0xffffffffU)

#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_RESTORE_RESTORE_SHIFT                                                 (0U)
#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_RESTORE_RESTORE_MASK                                                  (0xffffffffU)

#define CM_CM_CORE_PROFILING_CLKCTRL_RESTORE_RESTORE_SHIFT                                                  (0U)
#define CM_CM_CORE_PROFILING_CLKCTRL_RESTORE_RESTORE_MASK                                                   (0xffffffffU)

#define CM_L3MAIN1_DYNAMICDEP_RESTORE_RESTORE_SHIFT                                                         (0U)
#define CM_L3MAIN1_DYNAMICDEP_RESTORE_RESTORE_MASK                                                          (0xffffffffU)

#define CM_L4CFG_DYNAMICDEP_RESTORE_RESTORE_SHIFT                                                           (0U)
#define CM_L4CFG_DYNAMICDEP_RESTORE_RESTORE_MASK                                                            (0xffffffffU)

#define CM_L4PER_DYNAMICDEP_RESTORE_RESTORE_SHIFT                                                           (0U)
#define CM_L4PER_DYNAMICDEP_RESTORE_RESTORE_MASK                                                            (0xffffffffU)

#define CM_DMA_STATICDEP_RESTORE_RESTORE_SHIFT                                                              (0U)
#define CM_DMA_STATICDEP_RESTORE_RESTORE_MASK                                                               (0xffffffffU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_RESTORE_CM_CORE_H_ */
