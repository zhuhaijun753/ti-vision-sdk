/******************************************************************************
*
* hw_csc.h - register-level header file for CSC
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
#ifndef HW_CSC_H_
#define HW_CSC_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define CSC_00                                                                                              (0x0U)
#define CSC_01                                                                                              (0x4U)
#define CSC_02                                                                                              (0x8U)
#define CSC_03                                                                                              (0xcU)
#define CSC_04                                                                                              (0x10U)
#define CSC_05                                                                                              (0x14U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define CSC_00_A0_SHIFT                                                                                     (0U)
#define CSC_00_A0_MASK                                                                                      (0x00001fffU)

#define CSC_00_B0_SHIFT                                                                                     (16U)
#define CSC_00_B0_MASK                                                                                      (0x1fff0000U)

#define CSC_01_C0_SHIFT                                                                                     (0U)
#define CSC_01_C0_MASK                                                                                      (0x00001fffU)

#define CSC_01_A1_SHIFT                                                                                     (16U)
#define CSC_01_A1_MASK                                                                                      (0x1fff0000U)

#define CSC_02_B1_SHIFT                                                                                     (0U)
#define CSC_02_B1_MASK                                                                                      (0x00001fffU)

#define CSC_02_C1_SHIFT                                                                                     (16U)
#define CSC_02_C1_MASK                                                                                      (0x1fff0000U)

#define CSC_03_A2_SHIFT                                                                                     (0U)
#define CSC_03_A2_MASK                                                                                      (0x00001fffU)

#define CSC_03_B2_SHIFT                                                                                     (16U)
#define CSC_03_B2_MASK                                                                                      (0x1fff0000U)

#define CSC_04_C2_SHIFT                                                                                     (0U)
#define CSC_04_C2_MASK                                                                                      (0x00001fffU)

#define CSC_04_D0_SHIFT                                                                                     (16U)
#define CSC_04_D0_MASK                                                                                      (0x0fff0000U)

#define CSC_05_D1_SHIFT                                                                                     (0U)
#define CSC_05_D1_MASK                                                                                      (0x00000fffU)

#define CSC_05_D2_SHIFT                                                                                     (16U)
#define CSC_05_D2_MASK                                                                                      (0x0fff0000U)

#define CSC_05_BYPASS_SHIFT                                                                                 (28U)
#define CSC_05_BYPASS_MASK                                                                                  (0x10000000U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_CSC_H_ */
