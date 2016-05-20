/******************************************************************************
*
* hw_mpu_wdtimer.h - register-level header file for MPU
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
#ifndef HW_MPU_WDTIMER_H_
#define HW_MPU_WDTIMER_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define MPU_WDT_LOAD_REGISTER(n)                                                                           (0x0U + (n * 0))
#define MPU_WDT_COUNT_REGISTER(n)                                                                          (0x4U + (n * 0))
#define MPU_WDT_WARNING_REGISTER(n)                                                                        (0x8U + (n * 0))
#define MPU_WDT_CONTROL_REGISTER(n)                                                                        (0x10U + (n * 0))
#define MPU_WDT_RESET_STATUS_REGISTER(n)                                                                   (0x14U + (n * 0))
#define MPU_WDT_PRESCALER_REGISTER(n)                                                                      (0xcU + (n * 0))

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define MPU_WDT_LOAD_REGISTER_NEWCOUNT_SHIFT                                                              (0U)
#define MPU_WDT_LOAD_REGISTER_NEWCOUNT_MASK                                                               (0xffffffffU)

#define MPU_WDT_COUNT_REGISTER_CURRENTCOUNT_SHIFT                                                         (0U)
#define MPU_WDT_COUNT_REGISTER_CURRENTCOUNT_MASK                                                          (0xffffffffU)

#define MPU_WDT_WARNING_REGISTER_WARNING_WATERMARK_SHIFT                                                  (0U)
#define MPU_WDT_WARNING_REGISTER_WARNING_WATERMARK_MASK                                                   (0xffffffffU)

#define MPU_WDT_CONTROL_REGISTER_ENABLE_SHIFT                                                             (0U)
#define MPU_WDT_CONTROL_REGISTER_ENABLE_MASK                                                              (0x00000001U)

#define MPU_WDT_CONTROL_REGISTER_INTREN_SHIFT                                                             (1U)
#define MPU_WDT_CONTROL_REGISTER_INTREN_MASK                                                              (0x00000002U)

#define MPU_WDT_CONTROL_REGISTER_WARNEN_SHIFT                                                             (8U)
#define MPU_WDT_CONTROL_REGISTER_WARNEN_MASK                                                              (0x00000100U)

#define MPU_WDT_CONTROL_REGISTER_RESERVED2_SHIFT                                                          (9U)
#define MPU_WDT_CONTROL_REGISTER_RESERVED2_MASK                                                           (0xfffffe00U)

#define MPU_WDT_CONTROL_REGISTER_MPUSSRSTEN_SHIFT                                                         (3U)
#define MPU_WDT_CONTROL_REGISTER_MPUSSRSTEN_MASK                                                          (0x00000008U)

#define MPU_WDT_CONTROL_REGISTER_RESERVED_SHIFT                                                           (2U)
#define MPU_WDT_CONTROL_REGISTER_RESERVED_MASK                                                            (0x00000004U)

#define MPU_WDT_CONTROL_REGISTER_RESERVED3_SHIFT                                                          (4U)
#define MPU_WDT_CONTROL_REGISTER_RESERVED3_MASK                                                           (0x000000f0U)

#define MPU_WDT_RESET_STATUS_REGISTER_TO_SHIFT                                                            (0U)
#define MPU_WDT_RESET_STATUS_REGISTER_TO_MASK                                                             (0x00000001U)

#define MPU_WDT_RESET_STATUS_REGISTER_RESERVED_SHIFT                                                      (2U)
#define MPU_WDT_RESET_STATUS_REGISTER_RESERVED_MASK                                                       (0xfffffffcU)

#define MPU_WDT_RESET_STATUS_REGISTER_WARN_SHIFT                                                          (1U)
#define MPU_WDT_RESET_STATUS_REGISTER_WARN_MASK                                                           (0x00000002U)

#define MPU_WDT_PRESCALER_REGISTER_PRESCALER_SHIFT                                                        (0U)
#define MPU_WDT_PRESCALER_REGISTER_PRESCALER_MASK                                                         (0x000003ffU)

#define MPU_WDT_PRESCALER_REGISTER_RESERVED3_SHIFT                                                        (10U)
#define MPU_WDT_PRESCALER_REGISTER_RESERVED3_MASK                                                         (0xfffffc00U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_MPU_WDTIMER_H_ */
