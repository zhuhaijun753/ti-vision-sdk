/******************************************************************************
*
* hw_rtc_cm_core_aon.h - register-level header file for PRCM
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
#ifndef HW_RTC_CM_CORE_AON_H_
#define HW_RTC_CM_CORE_AON_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define CM_RTC_CLKSTCTRL                                                                                    (0x0U)
#define CM_RTC_RTCSS_CLKCTRL                                                                                (0x4U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define CM_RTC_CLKSTCTRL_CLKTRCTRL_SHIFT                                                                    (0U)
#define CM_RTC_CLKSTCTRL_CLKTRCTRL_MASK                                                                     (0x00000003U)
#define CM_RTC_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                                                                  (0U)
#define CM_RTC_CLKSTCTRL_CLKTRCTRL_RESERVED_1                                                                (1U)
#define CM_RTC_CLKSTCTRL_CLKTRCTRL_SW_WKUP                                                                   (2U)
#define CM_RTC_CLKSTCTRL_CLKTRCTRL_HW_AUTO                                                                   (3U)

#define CM_RTC_CLKSTCTRL_RESERVED_SHIFT                                                                     (2U)
#define CM_RTC_CLKSTCTRL_RESERVED_MASK                                                                      (0x000000fcU)

#define CM_RTC_CLKSTCTRL_CLKACTIVITY_RTC_L4_GICLK_SHIFT                                                     (8U)
#define CM_RTC_CLKSTCTRL_CLKACTIVITY_RTC_L4_GICLK_MASK                                                      (0x00000100U)
#define CM_RTC_CLKSTCTRL_CLKACTIVITY_RTC_L4_GICLK_INACT                                                      (0U)
#define CM_RTC_CLKSTCTRL_CLKACTIVITY_RTC_L4_GICLK_ACT                                                        (1U)

#define CM_RTC_CLKSTCTRL_CLKACTIVITY_RTC_AUX_CLK_SHIFT                                                      (10U)
#define CM_RTC_CLKSTCTRL_CLKACTIVITY_RTC_AUX_CLK_MASK                                                       (0x00000400U)
#define CM_RTC_CLKSTCTRL_CLKACTIVITY_RTC_AUX_CLK_INACT                                                       (0U)
#define CM_RTC_CLKSTCTRL_CLKACTIVITY_RTC_AUX_CLK_ACT                                                         (1U)

#define CM_RTC_CLKSTCTRL_RESERVED1_SHIFT                                                                    (11U)
#define CM_RTC_CLKSTCTRL_RESERVED1_MASK                                                                     (0xfffff800U)

#define CM_RTC_CLKSTCTRL_RESERVED2_SHIFT                                                                    (9U)
#define CM_RTC_CLKSTCTRL_RESERVED2_MASK                                                                     (0x00000200U)

#define CM_RTC_RTCSS_CLKCTRL_RESERVED_SHIFT                                                                 (2U)
#define CM_RTC_RTCSS_CLKCTRL_RESERVED_MASK                                                                  (0x0000fffcU)

#define CM_RTC_RTCSS_CLKCTRL_RESERVED1_SHIFT                                                                (18U)
#define CM_RTC_RTCSS_CLKCTRL_RESERVED1_MASK                                                                 (0xfffc0000U)

#define CM_RTC_RTCSS_CLKCTRL_IDLEST_SHIFT                                                                   (16U)
#define CM_RTC_RTCSS_CLKCTRL_IDLEST_MASK                                                                    (0x00030000U)
#define CM_RTC_RTCSS_CLKCTRL_IDLEST_DISABLE                                                                  (3U)
#define CM_RTC_RTCSS_CLKCTRL_IDLEST_IDLE                                                                     (2U)
#define CM_RTC_RTCSS_CLKCTRL_IDLEST_FUNC                                                                     (0U)
#define CM_RTC_RTCSS_CLKCTRL_IDLEST_TRANS                                                                    (1U)

#define CM_RTC_RTCSS_CLKCTRL_MODULEMODE_SHIFT                                                               (0U)
#define CM_RTC_RTCSS_CLKCTRL_MODULEMODE_MASK                                                                (0x00000003U)
#define CM_RTC_RTCSS_CLKCTRL_MODULEMODE_DISABLED                                                             (0U)
#define CM_RTC_RTCSS_CLKCTRL_MODULEMODE_RESERVED_1                                                           (1U)
#define CM_RTC_RTCSS_CLKCTRL_MODULEMODE_ENABLED                                                              (2U)
#define CM_RTC_RTCSS_CLKCTRL_MODULEMODE_RESERVED                                                             (3U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_RTC_CM_CORE_AON_H_ */
