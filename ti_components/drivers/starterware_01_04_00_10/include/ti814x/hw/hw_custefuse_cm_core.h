/******************************************************************************
*
* hw_custefuse_cm_core.h - register-level header file for PRCM
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
#ifndef HW_CUSTEFUSE_CM_CORE_H_
#define HW_CUSTEFUSE_CM_CORE_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define CM_CUSTEFUSE_CLKSTCTRL                                                                              (0x0U)
#define CM_CUSTEFUSE_EFUSE_CTRL_CUST_CLKCTRL                                                                (0x20U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define CM_CUSTEFUSE_CLKSTCTRL_CLKTRCTRL_SHIFT                                                              (0U)
#define CM_CUSTEFUSE_CLKSTCTRL_CLKTRCTRL_MASK                                                               (0x00000003U)
#define CM_CUSTEFUSE_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                                                            (0U)
#define CM_CUSTEFUSE_CLKSTCTRL_CLKTRCTRL_RESERVED                                                            (1U)
#define CM_CUSTEFUSE_CLKSTCTRL_CLKTRCTRL_SW_WKUP                                                             (2U)
#define CM_CUSTEFUSE_CLKSTCTRL_CLKTRCTRL_HW_AUTO                                                             (3U)

#define CM_CUSTEFUSE_CLKSTCTRL_CLKACTIVITY_CUSTEFUSE_L4_GICLK_SHIFT                                         (8U)
#define CM_CUSTEFUSE_CLKSTCTRL_CLKACTIVITY_CUSTEFUSE_L4_GICLK_MASK                                          (0x00000100U)
#define CM_CUSTEFUSE_CLKSTCTRL_CLKACTIVITY_CUSTEFUSE_L4_GICLK_INACT                                          (0U)
#define CM_CUSTEFUSE_CLKSTCTRL_CLKACTIVITY_CUSTEFUSE_L4_GICLK_ACT                                            (1U)

#define CM_CUSTEFUSE_CLKSTCTRL_RESERVED_SHIFT                                                               (2U)
#define CM_CUSTEFUSE_CLKSTCTRL_RESERVED_MASK                                                                (0x000000fcU)

#define CM_CUSTEFUSE_CLKSTCTRL_CLKACTIVITY_CUSTEFUSE_SYS_GFCLK_SHIFT                                        (9U)
#define CM_CUSTEFUSE_CLKSTCTRL_CLKACTIVITY_CUSTEFUSE_SYS_GFCLK_MASK                                         (0x00000200U)
#define CM_CUSTEFUSE_CLKSTCTRL_CLKACTIVITY_CUSTEFUSE_SYS_GFCLK_INACT                                         (0U)
#define CM_CUSTEFUSE_CLKSTCTRL_CLKACTIVITY_CUSTEFUSE_SYS_GFCLK_ACT                                           (1U)

#define CM_CUSTEFUSE_CLKSTCTRL_RESERVED1_SHIFT                                                              (10U)
#define CM_CUSTEFUSE_CLKSTCTRL_RESERVED1_MASK                                                               (0xfffffc00U)

#define CM_CUSTEFUSE_EFUSE_CTRL_CUST_CLKCTRL_IDLEST_SHIFT                                                   (16U)
#define CM_CUSTEFUSE_EFUSE_CTRL_CUST_CLKCTRL_IDLEST_MASK                                                    (0x00030000U)
#define CM_CUSTEFUSE_EFUSE_CTRL_CUST_CLKCTRL_IDLEST_DISABLE                                                  (3U)
#define CM_CUSTEFUSE_EFUSE_CTRL_CUST_CLKCTRL_IDLEST_IDLE                                                     (2U)
#define CM_CUSTEFUSE_EFUSE_CTRL_CUST_CLKCTRL_IDLEST_FUNC                                                     (0U)
#define CM_CUSTEFUSE_EFUSE_CTRL_CUST_CLKCTRL_IDLEST_TRANS                                                    (1U)

#define CM_CUSTEFUSE_EFUSE_CTRL_CUST_CLKCTRL_RESERVED_SHIFT                                                 (2U)
#define CM_CUSTEFUSE_EFUSE_CTRL_CUST_CLKCTRL_RESERVED_MASK                                                  (0x0000fffcU)

#define CM_CUSTEFUSE_EFUSE_CTRL_CUST_CLKCTRL_RESERVED1_SHIFT                                                (18U)
#define CM_CUSTEFUSE_EFUSE_CTRL_CUST_CLKCTRL_RESERVED1_MASK                                                 (0xfffc0000U)

#define CM_CUSTEFUSE_EFUSE_CTRL_CUST_CLKCTRL_MODULEMODE_SHIFT                                               (0U)
#define CM_CUSTEFUSE_EFUSE_CTRL_CUST_CLKCTRL_MODULEMODE_MASK                                                (0x00000003U)
#define CM_CUSTEFUSE_EFUSE_CTRL_CUST_CLKCTRL_MODULEMODE_DISABLED                                             (0U)
#define CM_CUSTEFUSE_EFUSE_CTRL_CUST_CLKCTRL_MODULEMODE_RESERVED_1                                           (1U)
#define CM_CUSTEFUSE_EFUSE_CTRL_CUST_CLKCTRL_MODULEMODE_ENABLE                                               (2U)
#define CM_CUSTEFUSE_EFUSE_CTRL_CUST_CLKCTRL_MODULEMODE_RESERVED                                             (3U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_CUSTEFUSE_CM_CORE_H_ */
