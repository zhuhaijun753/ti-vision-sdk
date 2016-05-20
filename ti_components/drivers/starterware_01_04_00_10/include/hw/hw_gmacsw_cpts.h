/******************************************************************************
*
* hw_gmacsw_cpts.h - register-level header file for GMAC_SW
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
#ifndef HW_GMACSW_CPTS_H_
#define HW_GMACSW_CPTS_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define GMAC_SW_CPTS_EVENT_LOW                                                                              (0x34U)
#define GMAC_SW_CPTS_TS_PUSH                                                                                (0xcU)
#define GMAC_SW_CPTS_IDVER                                                                                  (0x0U)
#define GMAC_SW_CPTS_TS_LOAD_VAL                                                                            (0x10U)
#define GMAC_SW_CPTS_INTSTAT_RAW                                                                            (0x20U)
#define GMAC_SW_CPTS_EVENT_HIGH                                                                             (0x38U)
#define GMAC_SW_CPTS_TS_LOAD_EN                                                                             (0x14U)
#define GMAC_SW_CPTS_INT_ENABLE                                                                             (0x28U)
#define GMAC_SW_CPTS_CONTROL                                                                                (0x4U)
#define GMAC_SW_CPTS_EVENT_POP                                                                              (0x30U)
#define GMAC_SW_CPTS_INTSTAT_MASKED                                                                         (0x24U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define GMAC_SW_CPTS_EVENT_LOW_TIME_STAMP_SHIFT                                                             (0U)
#define GMAC_SW_CPTS_EVENT_LOW_TIME_STAMP_MASK                                                              (0xffffffffU)

#define GMAC_SW_CPTS_TS_PUSH_TS_PUSH_SHIFT                                                                  (0U)
#define GMAC_SW_CPTS_TS_PUSH_TS_PUSH_MASK                                                                   (0x00000001U)

#define GMAC_SW_CPTS_TS_PUSH_RESERVED1_SHIFT                                                                (1U)
#define GMAC_SW_CPTS_TS_PUSH_RESERVED1_MASK                                                                 (0xfffffffeU)

#define GMAC_SW_CPTS_IDVER_MINOR_VER_SHIFT                                                                  (0U)
#define GMAC_SW_CPTS_IDVER_MINOR_VER_MASK                                                                   (0x000000ffU)

#define GMAC_SW_CPTS_IDVER_MAJOR_VER_SHIFT                                                                  (8U)
#define GMAC_SW_CPTS_IDVER_MAJOR_VER_MASK                                                                   (0x00000700U)

#define GMAC_SW_CPTS_IDVER_RTL_VER_SHIFT                                                                    (11U)
#define GMAC_SW_CPTS_IDVER_RTL_VER_MASK                                                                     (0x0000f800U)

#define GMAC_SW_CPTS_IDVER_TX_IDENT_SHIFT                                                                   (16U)
#define GMAC_SW_CPTS_IDVER_TX_IDENT_MASK                                                                    (0xffff0000U)

#define GMAC_SW_CPTS_TS_LOAD_VAL_TS_LOAD_VAL_SHIFT                                                          (0U)
#define GMAC_SW_CPTS_TS_LOAD_VAL_TS_LOAD_VAL_MASK                                                           (0xffffffffU)

#define GMAC_SW_CPTS_INTSTAT_RAW_TS_PEND_RAW_SHIFT                                                          (0U)
#define GMAC_SW_CPTS_INTSTAT_RAW_TS_PEND_RAW_MASK                                                           (0x00000001U)

#define GMAC_SW_CPTS_INTSTAT_RAW_RESERVED1_SHIFT                                                            (1U)
#define GMAC_SW_CPTS_INTSTAT_RAW_RESERVED1_MASK                                                             (0xfffffffeU)

#define GMAC_SW_CPTS_EVENT_HIGH_SEQUENCE_ID_SHIFT                                                           (0U)
#define GMAC_SW_CPTS_EVENT_HIGH_SEQUENCE_ID_MASK                                                            (0x0000ffffU)

#define GMAC_SW_CPTS_EVENT_HIGH_MESSAGE_TYPE_SHIFT                                                          (16U)
#define GMAC_SW_CPTS_EVENT_HIGH_MESSAGE_TYPE_MASK                                                           (0x000f0000U)

#define GMAC_SW_CPTS_EVENT_HIGH_EVENT_TYPE_SHIFT                                                            (20U)
#define GMAC_SW_CPTS_EVENT_HIGH_EVENT_TYPE_MASK                                                             (0x00f00000U)

#define GMAC_SW_CPTS_EVENT_HIGH_PORT_NUMBER_SHIFT                                                           (24U)
#define GMAC_SW_CPTS_EVENT_HIGH_PORT_NUMBER_MASK                                                            (0x1f000000U)

#define GMAC_SW_CPTS_EVENT_HIGH_RESERVED1_SHIFT                                                             (29U)
#define GMAC_SW_CPTS_EVENT_HIGH_RESERVED1_MASK                                                              (0xe0000000U)

#define GMAC_SW_CPTS_TS_LOAD_EN_TS_LOAD_EN_SHIFT                                                            (0U)
#define GMAC_SW_CPTS_TS_LOAD_EN_TS_LOAD_EN_MASK                                                             (0x00000001U)

#define GMAC_SW_CPTS_TS_LOAD_EN_RESERVED1_SHIFT                                                             (1U)
#define GMAC_SW_CPTS_TS_LOAD_EN_RESERVED1_MASK                                                              (0xfffffffeU)

#define GMAC_SW_CPTS_INT_ENABLE_TS_PEND_EN_SHIFT                                                            (0U)
#define GMAC_SW_CPTS_INT_ENABLE_TS_PEND_EN_MASK                                                             (0x00000001U)

#define GMAC_SW_CPTS_INT_ENABLE_RESERVED1_SHIFT                                                             (1U)
#define GMAC_SW_CPTS_INT_ENABLE_RESERVED1_MASK                                                              (0xfffffffeU)

#define GMAC_SW_CPTS_CONTROL_CPTS_EN_SHIFT                                                                  (0U)
#define GMAC_SW_CPTS_CONTROL_CPTS_EN_MASK                                                                   (0x00000001U)

#define GMAC_SW_CPTS_CONTROL_INT_TEST_SHIFT                                                                 (1U)
#define GMAC_SW_CPTS_CONTROL_INT_TEST_MASK                                                                  (0x00000002U)

#define GMAC_SW_CPTS_CONTROL_RESERVED2_SHIFT                                                                (2U)
#define GMAC_SW_CPTS_CONTROL_RESERVED2_MASK                                                                 (0x000000fcU)

#define GMAC_SW_CPTS_CONTROL_HW1_TS_PUSH_EN_SHIFT                                                           (8U)
#define GMAC_SW_CPTS_CONTROL_HW1_TS_PUSH_EN_MASK                                                            (0x00000100U)

#define GMAC_SW_CPTS_CONTROL_HW2_TS_PUSH_EN_SHIFT                                                           (9U)
#define GMAC_SW_CPTS_CONTROL_HW2_TS_PUSH_EN_MASK                                                            (0x00000200U)

#define GMAC_SW_CPTS_CONTROL_HW3_TS_PUSH_EN_SHIFT                                                           (10U)
#define GMAC_SW_CPTS_CONTROL_HW3_TS_PUSH_EN_MASK                                                            (0x00000400U)

#define GMAC_SW_CPTS_CONTROL_HW4_TS_PUSH_EN_SHIFT                                                           (11U)
#define GMAC_SW_CPTS_CONTROL_HW4_TS_PUSH_EN_MASK                                                            (0x00000800U)

#define GMAC_SW_CPTS_CONTROL_RESERVED1_SHIFT                                                                (12U)
#define GMAC_SW_CPTS_CONTROL_RESERVED1_MASK                                                                 (0xfffff000U)

#define GMAC_SW_CPTS_EVENT_POP_EVENT_POP_SHIFT                                                              (0U)
#define GMAC_SW_CPTS_EVENT_POP_EVENT_POP_MASK                                                               (0x00000001U)

#define GMAC_SW_CPTS_EVENT_POP_RESERVED1_SHIFT                                                              (1U)
#define GMAC_SW_CPTS_EVENT_POP_RESERVED1_MASK                                                               (0xfffffffeU)

#define GMAC_SW_CPTS_INTSTAT_MASKED_TS_PEND_SHIFT                                                           (0U)
#define GMAC_SW_CPTS_INTSTAT_MASKED_TS_PEND_MASK                                                            (0x00000001U)

#define GMAC_SW_CPTS_INTSTAT_MASKED_RESERVED1_SHIFT                                                         (1U)
#define GMAC_SW_CPTS_INTSTAT_MASKED_RESERVED1_MASK                                                          (0xfffffffeU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_GMACSW_CPTS_H_ */
