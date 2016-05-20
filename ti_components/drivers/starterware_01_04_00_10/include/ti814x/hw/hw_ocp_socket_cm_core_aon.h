/******************************************************************************
*
* hw_ocp_socket_cm_core_aon.h - register-level header file for PRCM
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
#ifndef HW_OCP_SOCKET_CM_CORE_AON_H_
#define HW_OCP_SOCKET_CM_CORE_AON_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define REVISION_CM_CORE_AON                                                                                (0x0U)
#define CM_CM_CORE_AON_PROFILING_CLKCTRL                                                                    (0x40U)
#define CM_CORE_AON_DEBUG_OUT                                                                               (0xecU)
#define CM_CORE_AON_DEBUG_CFG0                                                                              (0xf0U)
#define CM_CORE_AON_DEBUG_CFG1                                                                              (0xf4U)
#define CM_CORE_AON_DEBUG_CFG2                                                                              (0xf8U)
#define CM_CORE_AON_DEBUG_CFG3                                                                              (0xfcU)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define REVISION_CM_CORE_AON_CUSTOM_SHIFT                                                                   (6U)
#define REVISION_CM_CORE_AON_CUSTOM_MASK                                                                    (0x000000c0U)
#define REVISION_CM_CORE_AON_CUSTOM_STANDARD                                                                 (0U)

#define REVISION_CM_CORE_AON_R_RTL_SHIFT                                                                    (11U)
#define REVISION_CM_CORE_AON_R_RTL_MASK                                                                     (0x0000f800U)

#define REVISION_CM_CORE_AON_FUNC_SHIFT                                                                     (16U)
#define REVISION_CM_CORE_AON_FUNC_MASK                                                                      (0x0fff0000U)

#define REVISION_CM_CORE_AON_RESERVED_SHIFT                                                                 (28U)
#define REVISION_CM_CORE_AON_RESERVED_MASK                                                                  (0x30000000U)

#define REVISION_CM_CORE_AON_SCHEME_SHIFT                                                                   (30U)
#define REVISION_CM_CORE_AON_SCHEME_MASK                                                                    (0xc0000000U)
#define REVISION_CM_CORE_AON_SCHEME_H08                                                                      (1U)
#define REVISION_CM_CORE_AON_SCHEME_LEGACY                                                                   (0U)

#define REVISION_CM_CORE_AON_Y_MINOR_SHIFT                                                                  (0U)
#define REVISION_CM_CORE_AON_Y_MINOR_MASK                                                                   (0x0000003fU)
#define REVISION_CM_CORE_AON_Y_MINOR_ES1                                                                     (0U)
#define REVISION_CM_CORE_AON_Y_MINOR_ES2                                                                     (1U)

#define REVISION_CM_CORE_AON_X_MAJOR_SHIFT                                                                  (8U)
#define REVISION_CM_CORE_AON_X_MAJOR_MASK                                                                   (0x00000700U)
#define REVISION_CM_CORE_AON_X_MAJOR_OMAP4430_ES1_X                                                          (0U)
#define REVISION_CM_CORE_AON_X_MAJOR_OMAP4430_ES2_X                                                          (1U)
#define REVISION_CM_CORE_AON_X_MAJOR_OMAP4460                                                                (2U)
#define REVISION_CM_CORE_AON_X_MAJOR_OMAP5430                                                                (3U)
#define REVISION_CM_CORE_AON_X_MAJOR_OMAP470                                                                 (4U)

#define CM_CM_CORE_AON_PROFILING_CLKCTRL_MODULEMODE_SHIFT                                                   (0U)
#define CM_CM_CORE_AON_PROFILING_CLKCTRL_MODULEMODE_MASK                                                    (0x00000003U)
#define CM_CM_CORE_AON_PROFILING_CLKCTRL_MODULEMODE_DISABLED                                                 (0U)
#define CM_CM_CORE_AON_PROFILING_CLKCTRL_MODULEMODE_AUTO                                                     (1U)
#define CM_CM_CORE_AON_PROFILING_CLKCTRL_MODULEMODE_RESERVED_2                                               (2U)
#define CM_CM_CORE_AON_PROFILING_CLKCTRL_MODULEMODE_RESERVED                                                 (3U)

#define CM_CM_CORE_AON_PROFILING_CLKCTRL_RESERVED_SHIFT                                                     (2U)
#define CM_CM_CORE_AON_PROFILING_CLKCTRL_RESERVED_MASK                                                      (0x0000fffcU)

#define CM_CM_CORE_AON_PROFILING_CLKCTRL_IDLEST_SHIFT                                                       (16U)
#define CM_CM_CORE_AON_PROFILING_CLKCTRL_IDLEST_MASK                                                        (0x00030000U)
#define CM_CM_CORE_AON_PROFILING_CLKCTRL_IDLEST_DISABLE                                                      (3U)
#define CM_CM_CORE_AON_PROFILING_CLKCTRL_IDLEST_IDLE                                                         (2U)
#define CM_CM_CORE_AON_PROFILING_CLKCTRL_IDLEST_FUNC                                                         (0U)
#define CM_CM_CORE_AON_PROFILING_CLKCTRL_IDLEST_TRANS                                                        (1U)

#define CM_CM_CORE_AON_PROFILING_CLKCTRL_RESERVED1_SHIFT                                                    (18U)
#define CM_CM_CORE_AON_PROFILING_CLKCTRL_RESERVED1_MASK                                                     (0xfffc0000U)

#define CM_CORE_AON_DEBUG_OUT_OUTPUT_SHIFT                                                                  (0U)
#define CM_CORE_AON_DEBUG_OUT_OUTPUT_MASK                                                                   (0xffffffffU)

#define CM_CORE_AON_DEBUG_CFG0_SEL0_SHIFT                                                                   (0U)
#define CM_CORE_AON_DEBUG_CFG0_SEL0_MASK                                                                    (0x000003ffU)

#define CM_CORE_AON_DEBUG_CFG0_RESERVED_SHIFT                                                               (10U)
#define CM_CORE_AON_DEBUG_CFG0_RESERVED_MASK                                                                (0xfffffc00U)

#define CM_CORE_AON_DEBUG_CFG1_SEL1_SHIFT                                                                   (0U)
#define CM_CORE_AON_DEBUG_CFG1_SEL1_MASK                                                                    (0x000003ffU)

#define CM_CORE_AON_DEBUG_CFG1_RESERVED_SHIFT                                                               (10U)
#define CM_CORE_AON_DEBUG_CFG1_RESERVED_MASK                                                                (0xfffffc00U)

#define CM_CORE_AON_DEBUG_CFG2_SEL2_SHIFT                                                                   (0U)
#define CM_CORE_AON_DEBUG_CFG2_SEL2_MASK                                                                    (0x000003ffU)

#define CM_CORE_AON_DEBUG_CFG2_RESERVED_SHIFT                                                               (10U)
#define CM_CORE_AON_DEBUG_CFG2_RESERVED_MASK                                                                (0xfffffc00U)

#define CM_CORE_AON_DEBUG_CFG3_SEL3_SHIFT                                                                   (0U)
#define CM_CORE_AON_DEBUG_CFG3_SEL3_MASK                                                                    (0x000003ffU)

#define CM_CORE_AON_DEBUG_CFG3_RESERVED_SHIFT                                                               (10U)
#define CM_CORE_AON_DEBUG_CFG3_RESERVED_MASK                                                                (0xfffffc00U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_OCP_SOCKET_CM_CORE_AON_H_ */
