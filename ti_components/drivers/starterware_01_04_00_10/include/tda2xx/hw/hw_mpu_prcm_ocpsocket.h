/******************************************************************************
*
* hw_mpu_prcm_ocpsocket.h - register-level header file for MPU
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
#ifndef HW_MPU_PRCM_OCPSOCKET_H_
#define HW_MPU_PRCM_OCPSOCKET_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define MPU_REVISION                                                                                       (0x0U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define MPU_REVISION_X_MAJOR_SHIFT                                                                        (8U)
#define MPU_REVISION_X_MAJOR_MASK                                                                         (0x00000700U)
#define MPU_REVISION_X_MAJOR_READ0X0                                                                      (0U)

#define MPU_REVISION_Y_MINOR_SHIFT                                                                        (0U)
#define MPU_REVISION_Y_MINOR_MASK                                                                         (0x0000003fU)
#define MPU_REVISION_Y_MINOR_READ0X0                                                                      (0U)
#define MPU_REVISION_Y_MINOR_READ0X1                                                                      (1U)

#define MPU_REVISION_CUSTOM_SHIFT                                                                         (6U)
#define MPU_REVISION_CUSTOM_MASK                                                                          (0x000000c0U)

#define MPU_REVISION_R_RTL_SHIFT                                                                          (11U)
#define MPU_REVISION_R_RTL_MASK                                                                           (0x0000f800U)

#define MPU_REVISION_FUNC_SHIFT                                                                           (16U)
#define MPU_REVISION_FUNC_MASK                                                                            (0x0fff0000U)

#define MPU_REVISION_RESERVED_SHIFT                                                                       (28U)
#define MPU_REVISION_RESERVED_MASK                                                                        (0x30000000U)

#define MPU_REVISION_SCHEME_SHIFT                                                                         (30U)
#define MPU_REVISION_SCHEME_MASK                                                                          (0xc0000000U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_MPU_PRCM_OCPSOCKET_H_ */
