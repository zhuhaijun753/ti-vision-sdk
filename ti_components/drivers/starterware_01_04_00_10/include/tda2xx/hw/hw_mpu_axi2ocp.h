/******************************************************************************
*
* hw_mpu_axi2ocp.h - register-level header file for MPU
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
#ifndef HW_MPU_AXI2OCP_H_
#define HW_MPU_AXI2OCP_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define MPU_MA_PRIORITY                                                                                     (0x0U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define MPU_MA_PRIORITY_PRIORITY_SHIFT                                                                      (0U)
#define MPU_MA_PRIORITY_PRIORITY_MASK                                                                       (0x00000007U)

#define MPU_MA_PRIORITY_RESERVED_SHIFT                                                                      (3U)
#define MPU_MA_PRIORITY_RESERVED_MASK                                                                       (0x000000f8U)

#define MPU_MA_PRIORITY_HIMEM_INTERLEAVE_UN_SHIFT                                                           (8U)
#define MPU_MA_PRIORITY_HIMEM_INTERLEAVE_UN_MASK                                                            (0x00000100U)

#define MPU_MA_PRIORITY_RESERVED1_SHIFT                                                                     (9U)
#define MPU_MA_PRIORITY_RESERVED1_MASK                                                                      (0xfffffe00U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_MPU_AXI2OCP_H_ */
