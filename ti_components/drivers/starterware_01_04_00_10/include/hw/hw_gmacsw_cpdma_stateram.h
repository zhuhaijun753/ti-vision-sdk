/******************************************************************************
*
* hw_gmacsw_cpdma_stateram.h - register-level header file for GMAC_SW
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
#ifndef HW_GMACSW_CPDMA_STATERAM_H_
#define HW_GMACSW_CPDMA_STATERAM_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define GMAC_SW_TX0_CP                                                                                      (0x40U)
#define GMAC_SW_RX1_HDP                                                                                     (0x24U)
#define GMAC_SW_RX3_CP                                                                                      (0x6cU)
#define GMAC_SW_RX4_HDP                                                                                     (0x30U)
#define GMAC_SW_RX7_HDP                                                                                     (0x3cU)
#define GMAC_SW_RX2_CP                                                                                      (0x68U)
#define GMAC_SW_TX7_HDP                                                                                     (0x1cU)
#define GMAC_SW_RX2_HDP                                                                                     (0x28U)
#define GMAC_SW_RX5_HDP                                                                                     (0x34U)
#define GMAC_SW_RX3_HDP                                                                                     (0x2cU)
#define GMAC_SW_RX6_HDP                                                                                     (0x38U)
#define GMAC_SW_TX4_HDP                                                                                     (0x10U)
#define GMAC_SW_TX2_CP                                                                                      (0x48U)
#define GMAC_SW_TX5_CP                                                                                      (0x54U)
#define GMAC_SW_TX7_CP                                                                                      (0x5cU)
#define GMAC_SW_TX0_HDP                                                                                     (0x0U)
#define GMAC_SW_TX4_CP                                                                                      (0x50U)
#define GMAC_SW_RX0_CP                                                                                      (0x60U)
#define GMAC_SW_TX3_CP                                                                                      (0x4cU)
#define GMAC_SW_TX5_HDP                                                                                     (0x14U)
#define GMAC_SW_RX4_CP                                                                                      (0x70U)
#define GMAC_SW_RX5_CP                                                                                      (0x74U)
#define GMAC_SW_TX6_CP                                                                                      (0x58U)
#define GMAC_SW_RX1_CP                                                                                      (0x64U)
#define GMAC_SW_RX0_HDP                                                                                     (0x20U)
#define GMAC_SW_TX2_HDP                                                                                     (0x8U)
#define GMAC_SW_TX3_HDP                                                                                     (0xcU)
#define GMAC_SW_RX7_CP                                                                                      (0x7cU)
#define GMAC_SW_TX6_HDP                                                                                     (0x18U)
#define GMAC_SW_TX1_HDP                                                                                     (0x4U)
#define GMAC_SW_TX1_CP                                                                                      (0x44U)
#define GMAC_SW_RX6_CP                                                                                      (0x78U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define GMAC_SW_TX0_CP_TX_CP_SHIFT                                                                          (0U)
#define GMAC_SW_TX0_CP_TX_CP_MASK                                                                           (0xffffffffU)

#define GMAC_SW_RX1_HDP_RX_HDP_SHIFT                                                                        (0U)
#define GMAC_SW_RX1_HDP_RX_HDP_MASK                                                                         (0xffffffffU)

#define GMAC_SW_RX3_CP_RX_CP_SHIFT                                                                          (0U)
#define GMAC_SW_RX3_CP_RX_CP_MASK                                                                           (0xffffffffU)

#define GMAC_SW_RX4_HDP_RX_HDP_SHIFT                                                                        (0U)
#define GMAC_SW_RX4_HDP_RX_HDP_MASK                                                                         (0xffffffffU)

#define GMAC_SW_RX7_HDP_RX_HDP_SHIFT                                                                        (0U)
#define GMAC_SW_RX7_HDP_RX_HDP_MASK                                                                         (0xffffffffU)

#define GMAC_SW_RX2_CP_RX_CP_SHIFT                                                                          (0U)
#define GMAC_SW_RX2_CP_RX_CP_MASK                                                                           (0xffffffffU)

#define GMAC_SW_TX7_HDP_TX_HDP_SHIFT                                                                        (0U)
#define GMAC_SW_TX7_HDP_TX_HDP_MASK                                                                         (0xffffffffU)

#define GMAC_SW_RX2_HDP_RX_HDP_SHIFT                                                                        (0U)
#define GMAC_SW_RX2_HDP_RX_HDP_MASK                                                                         (0xffffffffU)

#define GMAC_SW_RX5_HDP_RX_HDP_SHIFT                                                                        (0U)
#define GMAC_SW_RX5_HDP_RX_HDP_MASK                                                                         (0xffffffffU)

#define GMAC_SW_RX3_HDP_RX_HDP_SHIFT                                                                        (0U)
#define GMAC_SW_RX3_HDP_RX_HDP_MASK                                                                         (0xffffffffU)

#define GMAC_SW_RX6_HDP_RX_HDP_SHIFT                                                                        (0U)
#define GMAC_SW_RX6_HDP_RX_HDP_MASK                                                                         (0xffffffffU)

#define GMAC_SW_TX4_HDP_TX_HDP_SHIFT                                                                        (0U)
#define GMAC_SW_TX4_HDP_TX_HDP_MASK                                                                         (0xffffffffU)

#define GMAC_SW_TX2_CP_TX_CP_SHIFT                                                                          (0U)
#define GMAC_SW_TX2_CP_TX_CP_MASK                                                                           (0xffffffffU)

#define GMAC_SW_TX5_CP_TX_CP_SHIFT                                                                          (0U)
#define GMAC_SW_TX5_CP_TX_CP_MASK                                                                           (0xffffffffU)

#define GMAC_SW_TX7_CP_TX_CP_SHIFT                                                                          (0U)
#define GMAC_SW_TX7_CP_TX_CP_MASK                                                                           (0xffffffffU)

#define GMAC_SW_TX0_HDP_TX_HDP_SHIFT                                                                        (0U)
#define GMAC_SW_TX0_HDP_TX_HDP_MASK                                                                         (0xffffffffU)

#define GMAC_SW_TX4_CP_TX_CP_SHIFT                                                                          (0U)
#define GMAC_SW_TX4_CP_TX_CP_MASK                                                                           (0xffffffffU)

#define GMAC_SW_RX0_CP_RX_CP_SHIFT                                                                          (0U)
#define GMAC_SW_RX0_CP_RX_CP_MASK                                                                           (0xffffffffU)

#define GMAC_SW_TX3_CP_TX_CP_SHIFT                                                                          (0U)
#define GMAC_SW_TX3_CP_TX_CP_MASK                                                                           (0xffffffffU)

#define GMAC_SW_TX5_HDP_TX_HDP_SHIFT                                                                        (0U)
#define GMAC_SW_TX5_HDP_TX_HDP_MASK                                                                         (0xffffffffU)

#define GMAC_SW_RX4_CP_RX_CP_SHIFT                                                                          (0U)
#define GMAC_SW_RX4_CP_RX_CP_MASK                                                                           (0xffffffffU)

#define GMAC_SW_RX5_CP_RX_CP_SHIFT                                                                          (0U)
#define GMAC_SW_RX5_CP_RX_CP_MASK                                                                           (0xffffffffU)

#define GMAC_SW_TX6_CP_TX_CP_SHIFT                                                                          (0U)
#define GMAC_SW_TX6_CP_TX_CP_MASK                                                                           (0xffffffffU)

#define GMAC_SW_RX1_CP_RX_CP_SHIFT                                                                          (0U)
#define GMAC_SW_RX1_CP_RX_CP_MASK                                                                           (0xffffffffU)

#define GMAC_SW_RX0_HDP_RX_HDP_SHIFT                                                                        (0U)
#define GMAC_SW_RX0_HDP_RX_HDP_MASK                                                                         (0xffffffffU)

#define GMAC_SW_TX2_HDP_TX_HDP_SHIFT                                                                        (0U)
#define GMAC_SW_TX2_HDP_TX_HDP_MASK                                                                         (0xffffffffU)

#define GMAC_SW_TX3_HDP_TX_HDP_SHIFT                                                                        (0U)
#define GMAC_SW_TX3_HDP_TX_HDP_MASK                                                                         (0xffffffffU)

#define GMAC_SW_RX7_CP_RX_CP_SHIFT                                                                          (0U)
#define GMAC_SW_RX7_CP_RX_CP_MASK                                                                           (0xffffffffU)

#define GMAC_SW_TX6_HDP_TX_HDP_SHIFT                                                                        (0U)
#define GMAC_SW_TX6_HDP_TX_HDP_MASK                                                                         (0xffffffffU)

#define GMAC_SW_TX1_HDP_TX_HDP_SHIFT                                                                        (0U)
#define GMAC_SW_TX1_HDP_TX_HDP_MASK                                                                         (0xffffffffU)

#define GMAC_SW_TX1_CP_TX_CP_SHIFT                                                                          (0U)
#define GMAC_SW_TX1_CP_TX_CP_MASK                                                                           (0xffffffffU)

#define GMAC_SW_RX6_CP_RX_CP_SHIFT                                                                          (0U)
#define GMAC_SW_RX6_CP_RX_CP_MASK                                                                           (0xffffffffU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_GMACSW_CPDMA_STATERAM_H_ */
