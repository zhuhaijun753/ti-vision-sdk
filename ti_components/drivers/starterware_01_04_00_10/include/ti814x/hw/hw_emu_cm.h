/******************************************************************************
*
* hw_emu_cm.h - register-level header file for PRCM
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
#ifndef HW_EMU_CM_H_
#define HW_EMU_CM_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define CM_EMU_CLKSTCTRL                                                                                    (0x0U)
#define CM_EMU_DEBUGSS_CLKCTRL                                                                              (0x4U)
#define CM_EMU_DYNAMICDEP                                                                                   (0x8U)
#define CM_EMU_MPU_EMU_DBG_CLKCTRL                                                                          (0xcU)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define CM_EMU_CLKSTCTRL_CLKTRCTRL_SHIFT                                                                    (0U)
#define CM_EMU_CLKSTCTRL_CLKTRCTRL_MASK                                                                     (0x00000003U)
#define CM_EMU_CLKSTCTRL_CLKTRCTRL_RESERVED                                                                  (0U)
#define CM_EMU_CLKSTCTRL_CLKTRCTRL_RESERVED_1                                                                (1U)
#define CM_EMU_CLKSTCTRL_CLKTRCTRL_SW_WKUP                                                                   (2U)
#define CM_EMU_CLKSTCTRL_CLKTRCTRL_HW_AUTO                                                                   (3U)

#define CM_EMU_CLKSTCTRL_CLKACTIVITY_EMU_SYS_CLK_SHIFT                                                      (8U)
#define CM_EMU_CLKSTCTRL_CLKACTIVITY_EMU_SYS_CLK_MASK                                                       (0x00000100U)
#define CM_EMU_CLKSTCTRL_CLKACTIVITY_EMU_SYS_CLK_INACT                                                       (0U)
#define CM_EMU_CLKSTCTRL_CLKACTIVITY_EMU_SYS_CLK_ACT                                                         (1U)

#define CM_EMU_CLKSTCTRL_RESERVED_SHIFT                                                                     (2U)
#define CM_EMU_CLKSTCTRL_RESERVED_MASK                                                                      (0x000000fcU)

#define CM_EMU_CLKSTCTRL_RESERVED1_SHIFT                                                                    (9U)
#define CM_EMU_CLKSTCTRL_RESERVED1_MASK                                                                     (0xfffffe00U)

#define CM_EMU_DEBUGSS_CLKCTRL_IDLEST_SHIFT                                                                 (16U)
#define CM_EMU_DEBUGSS_CLKCTRL_IDLEST_MASK                                                                  (0x00030000U)
#define CM_EMU_DEBUGSS_CLKCTRL_IDLEST_DISABLE                                                                (3U)
#define CM_EMU_DEBUGSS_CLKCTRL_IDLEST_IDLE                                                                   (2U)
#define CM_EMU_DEBUGSS_CLKCTRL_IDLEST_FUNC                                                                   (0U)
#define CM_EMU_DEBUGSS_CLKCTRL_IDLEST_TRANS                                                                  (1U)

#define CM_EMU_DEBUGSS_CLKCTRL_STBYST_SHIFT                                                                 (18U)
#define CM_EMU_DEBUGSS_CLKCTRL_STBYST_MASK                                                                  (0x00040000U)
#define CM_EMU_DEBUGSS_CLKCTRL_STBYST_FUNC                                                                   (0U)
#define CM_EMU_DEBUGSS_CLKCTRL_STBYST_STANDBY                                                                (1U)

#define CM_EMU_DEBUGSS_CLKCTRL_RESERVED1_SHIFT                                                              (19U)
#define CM_EMU_DEBUGSS_CLKCTRL_RESERVED1_MASK                                                               (0xfff80000U)

#define CM_EMU_DEBUGSS_CLKCTRL_MODULEMODE_SHIFT                                                             (0U)
#define CM_EMU_DEBUGSS_CLKCTRL_MODULEMODE_MASK                                                              (0x00000003U)
#define CM_EMU_DEBUGSS_CLKCTRL_MODULEMODE_AUTO                                                               (1U)

#define CM_EMU_DEBUGSS_CLKCTRL_RESERVED_SHIFT                                                               (2U)
#define CM_EMU_DEBUGSS_CLKCTRL_RESERVED_MASK                                                                (0x0000fffcU)

#define CM_EMU_DYNAMICDEP_RESERVED1_SHIFT                                                                   (28U)
#define CM_EMU_DYNAMICDEP_RESERVED1_MASK                                                                    (0xf0000000U)

#define CM_EMU_DYNAMICDEP_L3MAIN1_DYNDEP_SHIFT                                                              (5U)
#define CM_EMU_DYNAMICDEP_L3MAIN1_DYNDEP_MASK                                                               (0x00000020U)
#define CM_EMU_DYNAMICDEP_L3MAIN1_DYNDEP_ENABLED                                                             (1U)

#define CM_EMU_DYNAMICDEP_WINDOWSIZE_SHIFT                                                                  (24U)
#define CM_EMU_DYNAMICDEP_WINDOWSIZE_MASK                                                                   (0x0f000000U)

#define CM_EMU_DYNAMICDEP_RESERVED_SHIFT                                                                    (0U)
#define CM_EMU_DYNAMICDEP_RESERVED_MASK                                                                     (0x0000001fU)

#define CM_EMU_DYNAMICDEP_RESERVED2_SHIFT                                                                   (6U)
#define CM_EMU_DYNAMICDEP_RESERVED2_MASK                                                                    (0x00ffffc0U)

#define CM_EMU_MPU_EMU_DBG_CLKCTRL_IDLEST_SHIFT                                                             (16U)
#define CM_EMU_MPU_EMU_DBG_CLKCTRL_IDLEST_MASK                                                              (0x00030000U)
#define CM_EMU_MPU_EMU_DBG_CLKCTRL_IDLEST_DISABLE                                                            (3U)
#define CM_EMU_MPU_EMU_DBG_CLKCTRL_IDLEST_IDLE                                                               (2U)
#define CM_EMU_MPU_EMU_DBG_CLKCTRL_IDLEST_FUNC                                                               (0U)
#define CM_EMU_MPU_EMU_DBG_CLKCTRL_IDLEST_TRANS                                                              (1U)

#define CM_EMU_MPU_EMU_DBG_CLKCTRL_RESERVED1_SHIFT                                                          (18U)
#define CM_EMU_MPU_EMU_DBG_CLKCTRL_RESERVED1_MASK                                                           (0xfffc0000U)

#define CM_EMU_MPU_EMU_DBG_CLKCTRL_MODULEMODE_SHIFT                                                         (0U)
#define CM_EMU_MPU_EMU_DBG_CLKCTRL_MODULEMODE_MASK                                                          (0x00000003U)
#define CM_EMU_MPU_EMU_DBG_CLKCTRL_MODULEMODE_AUTO                                                           (1U)

#define CM_EMU_MPU_EMU_DBG_CLKCTRL_RESERVED_SHIFT                                                           (2U)
#define CM_EMU_MPU_EMU_DBG_CLKCTRL_RESERVED_MASK                                                            (0x0000fffcU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_EMU_CM_H_ */
