/******************************************************************************
*
* hw_mpu_prcm_cmc0.h - register-level header file for MPU
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
#ifndef HW_MPU_PRCM_CMC0_H_
#define HW_MPU_PRCM_CMC0_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define MPU_CM_CPU0_CLKSTCTRL                                                                               (0x0U)
#define MPU_CM_CPU0_CPU0_CLKCTRL                                                                            (0x20U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define MPU_CM_CPU0_CLKSTCTRL_CLKTRCTRL_SHIFT                                                               (0U)
#define MPU_CM_CPU0_CLKSTCTRL_CLKTRCTRL_MASK                                                                (0x00000003U)
#define MPU_CM_CPU0_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                                                             (0U)
#define MPU_CM_CPU0_CLKSTCTRL_CLKTRCTRL_RESERVED                                                             (1U)
#define MPU_CM_CPU0_CLKSTCTRL_CLKTRCTRL_SW_WKUP                                                              (2U)
#define MPU_CM_CPU0_CLKSTCTRL_CLKTRCTRL_HW_AUTO                                                              (3U)

#define MPU_CM_CPU0_CLKSTCTRL_RESERVED_SHIFT                                                                (2U)
#define MPU_CM_CPU0_CLKSTCTRL_RESERVED_MASK                                                                 (0xfffffffcU)

#define MPU_CM_CPU0_CPU0_CLKCTRL_STBYST_SHIFT                                                               (0U)
#define MPU_CM_CPU0_CPU0_CLKCTRL_STBYST_MASK                                                                (0x00000001U)
#define MPU_CM_CPU0_CPU0_CLKCTRL_STBYST_FUNC                                                                 (0U)
#define MPU_CM_CPU0_CPU0_CLKCTRL_STBYST_STANDBY                                                              (1U)

#define MPU_CM_CPU0_CPU0_CLKCTRL_RESERVED_SHIFT                                                             (1U)
#define MPU_CM_CPU0_CPU0_CLKCTRL_RESERVED_MASK                                                              (0xfffffffeU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_MPU_PRCM_CMC0_H_ */
