/******************************************************************************
*
* hw_ipu_rw_table.h - register-level header file for IPU
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
#ifndef HW_IPU_RW_TABLE_H_
#define HW_IPU_RW_TABLE_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define IPU_CORTEXM4_RW_PID1                                                                                (0x0U)
#define IPU_CORTEXM4_RW_PID2                                                                                (0x4U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define IPU_CORTEXM4_RW_PID1_BASEADD1_SHIFT                                                                 (0U)
#define IPU_CORTEXM4_RW_PID1_BASEADD1_MASK                                                                  (0xffffffffU)

#define IPU_CORTEXM4_RW_PID2_BASEADD2_SHIFT                                                                 (0U)
#define IPU_CORTEXM4_RW_PID2_BASEADD2_MASK                                                                  (0xffffffffU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_IPU_RW_TABLE_H_ */
