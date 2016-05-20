/******************************************************************************
*
* hw_gmacsw_port.h - register-level header file for GMAC_SW
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
#ifndef HW_GMACSW_PORT_H_
#define HW_GMACSW_PORT_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7                                                                         (0x24cU)
#define GMAC_SW_P2_TX_IN_CTL                                                                                (0x210U)
#define GMAC_SW_P2_BLK_CNT                                                                                  (0x20cU)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0                                                                         (0x130U)
#define GMAC_SW_P1_SA_LO                                                                                    (0x120U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP1                                                                         (0x234U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP7                                                                         (0x4cU)
#define GMAC_SW_P0_MAX_BLKS                                                                                 (0x8U)
#define GMAC_SW_P1_CONTROL                                                                                  (0x100U)
#define GMAC_SW_P2_TX_PRI_MAP                                                                               (0x218U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP2                                                                         (0x238U)
#define GMAC_SW_P2_SA_HI                                                                                    (0x224U)
#define GMAC_SW_P2_SA_LO                                                                                    (0x220U)
#define GMAC_SW_P0_CPDMA_TX_PRI_MAP                                                                         (0x1cU)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP4                                                                         (0x240U)
#define GMAC_SW_P0_BLK_CNT                                                                                  (0xcU)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP0                                                                         (0x30U)
#define GMAC_SW_P0_TX_IN_CTL                                                                                (0x10U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP5                                                                         (0x44U)
#define GMAC_SW_P2_SEND_PERCENT                                                                             (0x228U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP7                                                                         (0x14cU)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP1                                                                         (0x34U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP1                                                                         (0x134U)
#define GMAC_SW_P1_TX_IN_CTL                                                                                (0x110U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP4                                                                         (0x40U)
#define GMAC_SW_P2_TS_SEQ_MTYPE                                                                             (0x21cU)
#define GMAC_SW_P0_PORT_VLAN                                                                                (0x14U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP4                                                                         (0x140U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP5                                                                         (0x244U)
#define GMAC_SW_P2_CONTROL                                                                                  (0x200U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP5                                                                         (0x144U)
#define GMAC_SW_P0_CPDMA_RX_CH_MAP                                                                          (0x20U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP2                                                                         (0x138U)
#define GMAC_SW_P1_MAX_BLKS                                                                                 (0x108U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP3                                                                         (0x13cU)
#define GMAC_SW_P1_TX_PRI_MAP                                                                               (0x118U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP3                                                                         (0x23cU)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP6                                                                         (0x148U)
#define GMAC_SW_P1_SA_HI                                                                                    (0x124U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6                                                                         (0x248U)
#define GMAC_SW_P2_MAX_BLKS                                                                                 (0x208U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3                                                                         (0x3cU)
#define GMAC_SW_P0_TX_PRI_MAP                                                                               (0x18U)
#define GMAC_SW_P1_TS_SEQ_MTYPE                                                                             (0x11cU)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP6                                                                         (0x48U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP0                                                                         (0x230U)
#define GMAC_SW_P0_CONTROL                                                                                  (0x0U)
#define GMAC_SW_P1_SEND_PERCENT                                                                             (0x128U)
#define GMAC_SW_P1_BLK_CNT                                                                                  (0x10cU)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP2                                                                         (0x38U)
#define GMAC_SW_P2_PORT_VLAN                                                                                (0x214U)
#define GMAC_SW_P1_PORT_VLAN                                                                                (0x114U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI56_SHIFT                                                             (0U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI56_MASK                                                              (0x00000007U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI57_SHIFT                                                             (4U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI57_MASK                                                              (0x00000070U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI58_SHIFT                                                             (8U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI58_MASK                                                              (0x00000700U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI59_SHIFT                                                             (12U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI59_MASK                                                              (0x00007000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI60_SHIFT                                                             (16U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI60_MASK                                                              (0x00070000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI61_SHIFT                                                             (20U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI61_MASK                                                              (0x00700000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI62_SHIFT                                                             (24U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI62_MASK                                                              (0x07000000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI63_SHIFT                                                             (28U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_PRI63_MASK                                                              (0x70000000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_SHIFT                                                          (3U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_MASK                                                           (0x00000008U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_2_SHIFT                                                        (7U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_2_MASK                                                         (0x00000080U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_3_SHIFT                                                        (11U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_3_MASK                                                         (0x00000800U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_4_SHIFT                                                        (15U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_4_MASK                                                         (0x00008000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_5_SHIFT                                                        (19U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_5_MASK                                                         (0x00080000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_6_SHIFT                                                        (23U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_6_MASK                                                         (0x00800000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_7_SHIFT                                                        (27U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_7_MASK                                                         (0x08000000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_8_SHIFT                                                        (31U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP7_RESERVED_8_MASK                                                         (0x80000000U)

#define GMAC_SW_P2_TX_IN_CTL_TX_PRI_WDS_SHIFT                                                               (0U)
#define GMAC_SW_P2_TX_IN_CTL_TX_PRI_WDS_MASK                                                                (0x000003ffU)

#define GMAC_SW_P2_TX_IN_CTL_TX_BLKS_REM_SHIFT                                                              (12U)
#define GMAC_SW_P2_TX_IN_CTL_TX_BLKS_REM_MASK                                                               (0x0000f000U)

#define GMAC_SW_P2_TX_IN_CTL_TX_IN_SEL_SHIFT                                                                (16U)
#define GMAC_SW_P2_TX_IN_CTL_TX_IN_SEL_MASK                                                                 (0x00030000U)

#define GMAC_SW_P2_TX_IN_CTL_TX_RATE_EN_SHIFT                                                               (20U)
#define GMAC_SW_P2_TX_IN_CTL_TX_RATE_EN_MASK                                                                (0x00f00000U)

#define GMAC_SW_P2_TX_IN_CTL_HOST_BLKS_REM_SHIFT                                                            (24U)
#define GMAC_SW_P2_TX_IN_CTL_HOST_BLKS_REM_MASK                                                             (0x0f000000U)

#define GMAC_SW_P2_TX_IN_CTL_RESERVED_SHIFT                                                                 (10U)
#define GMAC_SW_P2_TX_IN_CTL_RESERVED_MASK                                                                  (0x00000c00U)

#define GMAC_SW_P2_TX_IN_CTL_RESERVED_2_SHIFT                                                               (18U)
#define GMAC_SW_P2_TX_IN_CTL_RESERVED_2_MASK                                                                (0x000c0000U)

#define GMAC_SW_P2_TX_IN_CTL_RESERVED_3_SHIFT                                                               (28U)
#define GMAC_SW_P2_TX_IN_CTL_RESERVED_3_MASK                                                                (0xf0000000U)

#define GMAC_SW_P2_BLK_CNT_P2_RX_BLK_CNT_SHIFT                                                              (0U)
#define GMAC_SW_P2_BLK_CNT_P2_RX_BLK_CNT_MASK                                                               (0x0000000fU)

#define GMAC_SW_P2_BLK_CNT_P2_TX_BLK_CNT_SHIFT                                                              (4U)
#define GMAC_SW_P2_BLK_CNT_P2_TX_BLK_CNT_MASK                                                               (0x000001f0U)

#define GMAC_SW_P2_BLK_CNT_RESERVED_SHIFT                                                                   (9U)
#define GMAC_SW_P2_BLK_CNT_RESERVED_MASK                                                                    (0xfffffe00U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI0_SHIFT                                                              (0U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI0_MASK                                                               (0x00000007U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI1_SHIFT                                                              (4U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI1_MASK                                                               (0x00000070U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI2_SHIFT                                                              (8U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI2_MASK                                                               (0x00000700U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI3_SHIFT                                                              (12U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI3_MASK                                                               (0x00007000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI4_SHIFT                                                              (16U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI4_MASK                                                               (0x00070000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI5_SHIFT                                                              (20U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI5_MASK                                                               (0x00700000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI6_SHIFT                                                              (24U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI6_MASK                                                               (0x07000000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI7_SHIFT                                                              (28U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_PRI7_MASK                                                               (0x70000000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_SHIFT                                                          (3U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_MASK                                                           (0x00000008U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_2_SHIFT                                                        (7U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_2_MASK                                                         (0x00000080U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_3_SHIFT                                                        (11U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_3_MASK                                                         (0x00000800U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_4_SHIFT                                                        (15U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_4_MASK                                                         (0x00008000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_5_SHIFT                                                        (19U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_5_MASK                                                         (0x00080000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_6_SHIFT                                                        (23U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_6_MASK                                                         (0x00800000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_7_SHIFT                                                        (27U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_7_MASK                                                         (0x08000000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_8_SHIFT                                                        (31U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP0_RESERVED_8_MASK                                                         (0x80000000U)

#define GMAC_SW_P1_SA_LO_MACSRCADDR_15_8_SHIFT                                                              (0U)
#define GMAC_SW_P1_SA_LO_MACSRCADDR_15_8_MASK                                                               (0x000000ffU)

#define GMAC_SW_P1_SA_LO_MACSRCADDR_7_0_SHIFT                                                               (8U)
#define GMAC_SW_P1_SA_LO_MACSRCADDR_7_0_MASK                                                                (0x0000ff00U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI8_SHIFT                                                              (0U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI8_MASK                                                               (0x00000007U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI9_SHIFT                                                              (4U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI9_MASK                                                               (0x00000070U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI10_SHIFT                                                             (8U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI10_MASK                                                              (0x00000700U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI11_SHIFT                                                             (12U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI11_MASK                                                              (0x00007000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI12_SHIFT                                                             (16U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI12_MASK                                                              (0x00070000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI13_SHIFT                                                             (20U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI13_MASK                                                              (0x00700000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI14_SHIFT                                                             (24U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI14_MASK                                                              (0x07000000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI15_SHIFT                                                             (28U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_PRI15_MASK                                                              (0x70000000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_RESERVED_SHIFT                                                          (3U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_RESERVED_MASK                                                           (0x00000008U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_RESERVED_2_SHIFT                                                        (7U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_RESERVED_2_MASK                                                         (0x00000080U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_RESERVED_3_SHIFT                                                        (11U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_RESERVED_3_MASK                                                         (0x00000800U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_RESERVED_4_SHIFT                                                        (15U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP1_RESERVED_4_MASK                                                         (0x00008000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI56_SHIFT                                                             (0U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI56_MASK                                                              (0x00000007U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI57_SHIFT                                                             (4U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI57_MASK                                                              (0x00000070U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI58_SHIFT                                                             (8U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI58_MASK                                                              (0x00000700U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI59_SHIFT                                                             (12U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI59_MASK                                                              (0x00007000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI60_SHIFT                                                             (16U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI60_MASK                                                              (0x00070000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI61_SHIFT                                                             (20U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI61_MASK                                                              (0x00700000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI62_SHIFT                                                             (24U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI62_MASK                                                              (0x07000000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI63_SHIFT                                                             (28U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_PRI63_MASK                                                              (0x70000000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_RESERVED_SHIFT                                                          (3U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_RESERVED_MASK                                                           (0x00000008U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_RESERVED_2_SHIFT                                                        (7U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_RESERVED_2_MASK                                                         (0x00000080U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_RESERVED_3_SHIFT                                                        (11U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_RESERVED_3_MASK                                                         (0x00000800U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_RESERVED_4_SHIFT                                                        (15U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP7_RESERVED_4_MASK                                                         (0x00008000U)

#define GMAC_SW_P0_MAX_BLKS_P0_RX_MAX_BLKS_SHIFT                                                            (0U)
#define GMAC_SW_P0_MAX_BLKS_P0_RX_MAX_BLKS_MASK                                                             (0x0000000fU)

#define GMAC_SW_P0_MAX_BLKS_P0_TX_MAX_BLKS_SHIFT                                                            (4U)
#define GMAC_SW_P0_MAX_BLKS_P0_TX_MAX_BLKS_MASK                                                             (0x000001f0U)

#define GMAC_SW_P0_MAX_BLKS_RESERVED_SHIFT                                                                  (9U)
#define GMAC_SW_P0_MAX_BLKS_RESERVED_MASK                                                                   (0x0000fe00U)

#define GMAC_SW_P1_CONTROL_P1_TS_RX_EN_SHIFT                                                                (0U)
#define GMAC_SW_P1_CONTROL_P1_TS_RX_EN_MASK                                                                 (0x00000001U)

#define GMAC_SW_P1_CONTROL_P1_TS_TX_EN_SHIFT                                                                (1U)
#define GMAC_SW_P1_CONTROL_P1_TS_TX_EN_MASK                                                                 (0x00000002U)

#define GMAC_SW_P1_CONTROL_P1_TS_LTYPE1_EN_SHIFT                                                            (2U)
#define GMAC_SW_P1_CONTROL_P1_TS_LTYPE1_EN_MASK                                                             (0x00000004U)

#define GMAC_SW_P1_CONTROL_P1_TS_LTYPE2_EN_SHIFT                                                            (3U)
#define GMAC_SW_P1_CONTROL_P1_TS_LTYPE2_EN_MASK                                                             (0x00000008U)

#define GMAC_SW_P1_CONTROL_P1_TS_ANNEX_D_EN_SHIFT                                                           (4U)
#define GMAC_SW_P1_CONTROL_P1_TS_ANNEX_D_EN_MASK                                                            (0x00000010U)

#define GMAC_SW_P1_CONTROL_P1_TS_TTL_NONZERO_SHIFT                                                          (8U)
#define GMAC_SW_P1_CONTROL_P1_TS_TTL_NONZERO_MASK                                                           (0x00000100U)

#define GMAC_SW_P1_CONTROL_P1_TS_129_SHIFT                                                                  (9U)
#define GMAC_SW_P1_CONTROL_P1_TS_129_MASK                                                                   (0x00000200U)

#define GMAC_SW_P1_CONTROL_P1_TS_130_SHIFT                                                                  (10U)
#define GMAC_SW_P1_CONTROL_P1_TS_130_MASK                                                                   (0x00000400U)

#define GMAC_SW_P1_CONTROL_P1_TS_131_SHIFT                                                                  (11U)
#define GMAC_SW_P1_CONTROL_P1_TS_131_MASK                                                                   (0x00000800U)

#define GMAC_SW_P1_CONTROL_P1_TS_132_SHIFT                                                                  (12U)
#define GMAC_SW_P1_CONTROL_P1_TS_132_MASK                                                                   (0x00001000U)

#define GMAC_SW_P1_CONTROL_P1_TS_319_SHIFT                                                                  (13U)
#define GMAC_SW_P1_CONTROL_P1_TS_319_MASK                                                                   (0x00002000U)

#define GMAC_SW_P1_CONTROL_P1_TS_320_SHIFT                                                                  (14U)
#define GMAC_SW_P1_CONTROL_P1_TS_320_MASK                                                                   (0x00004000U)

#define GMAC_SW_P1_CONTROL_P1_DSCP_PRI_EN_SHIFT                                                             (16U)
#define GMAC_SW_P1_CONTROL_P1_DSCP_PRI_EN_MASK                                                              (0x00010000U)

#define GMAC_SW_P1_CONTROL_P1_VLAN_LTYPE1_EN_SHIFT                                                          (20U)
#define GMAC_SW_P1_CONTROL_P1_VLAN_LTYPE1_EN_MASK                                                           (0x00100000U)

#define GMAC_SW_P1_CONTROL_P1_VLAN_LTYPE2_EN_SHIFT                                                          (21U)
#define GMAC_SW_P1_CONTROL_P1_VLAN_LTYPE2_EN_MASK                                                           (0x00200000U)

#define GMAC_SW_P1_CONTROL_P1_PASS_PRI_TAGGED_SHIFT                                                         (24U)
#define GMAC_SW_P1_CONTROL_P1_PASS_PRI_TAGGED_MASK                                                          (0x01000000U)

#define GMAC_SW_P1_CONTROL_RESERVED_SHIFT                                                                   (5U)
#define GMAC_SW_P1_CONTROL_RESERVED_MASK                                                                    (0x000000e0U)

#define GMAC_SW_P1_CONTROL_RESERVED_2_SHIFT                                                                 (15U)
#define GMAC_SW_P1_CONTROL_RESERVED_2_MASK                                                                  (0x00008000U)

#define GMAC_SW_P2_TX_PRI_MAP_PRI0_SHIFT                                                                    (0U)
#define GMAC_SW_P2_TX_PRI_MAP_PRI0_MASK                                                                     (0x00000003U)

#define GMAC_SW_P2_TX_PRI_MAP_PRI1_SHIFT                                                                    (4U)
#define GMAC_SW_P2_TX_PRI_MAP_PRI1_MASK                                                                     (0x00000030U)

#define GMAC_SW_P2_TX_PRI_MAP_PRI2_SHIFT                                                                    (8U)
#define GMAC_SW_P2_TX_PRI_MAP_PRI2_MASK                                                                     (0x00000300U)

#define GMAC_SW_P2_TX_PRI_MAP_PRI3_SHIFT                                                                    (12U)
#define GMAC_SW_P2_TX_PRI_MAP_PRI3_MASK                                                                     (0x00003000U)

#define GMAC_SW_P2_TX_PRI_MAP_PRI4_SHIFT                                                                    (16U)
#define GMAC_SW_P2_TX_PRI_MAP_PRI4_MASK                                                                     (0x00030000U)

#define GMAC_SW_P2_TX_PRI_MAP_PRI5_SHIFT                                                                    (20U)
#define GMAC_SW_P2_TX_PRI_MAP_PRI5_MASK                                                                     (0x00300000U)

#define GMAC_SW_P2_TX_PRI_MAP_PRI6_SHIFT                                                                    (24U)
#define GMAC_SW_P2_TX_PRI_MAP_PRI6_MASK                                                                     (0x03000000U)

#define GMAC_SW_P2_TX_PRI_MAP_PRI7_SHIFT                                                                    (28U)
#define GMAC_SW_P2_TX_PRI_MAP_PRI7_MASK                                                                     (0x30000000U)

#define GMAC_SW_P2_TX_PRI_MAP_RESERVED_SHIFT                                                                (2U)
#define GMAC_SW_P2_TX_PRI_MAP_RESERVED_MASK                                                                 (0x0000000cU)

#define GMAC_SW_P2_TX_PRI_MAP_RESERVED_2_SHIFT                                                              (6U)
#define GMAC_SW_P2_TX_PRI_MAP_RESERVED_2_MASK                                                               (0x000000c0U)

#define GMAC_SW_P2_TX_PRI_MAP_RESERVED_3_SHIFT                                                              (10U)
#define GMAC_SW_P2_TX_PRI_MAP_RESERVED_3_MASK                                                               (0x00000c00U)

#define GMAC_SW_P2_TX_PRI_MAP_RESERVED_4_SHIFT                                                              (14U)
#define GMAC_SW_P2_TX_PRI_MAP_RESERVED_4_MASK                                                               (0x0000c000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI16_SHIFT                                                             (0U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI16_MASK                                                              (0x00000007U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI17_SHIFT                                                             (4U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI17_MASK                                                              (0x00000070U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI18_SHIFT                                                             (8U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI18_MASK                                                              (0x00000700U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI19_SHIFT                                                             (12U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI19_MASK                                                              (0x00007000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI20_SHIFT                                                             (16U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI20_MASK                                                              (0x00070000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI21_SHIFT                                                             (20U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI21_MASK                                                              (0x00700000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI22_SHIFT                                                             (24U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI22_MASK                                                              (0x07000000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI23_SHIFT                                                             (28U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_PRI23_MASK                                                              (0x70000000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_RESERVED_SHIFT                                                          (3U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_RESERVED_MASK                                                           (0x00000008U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_RESERVED_2_SHIFT                                                        (7U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_RESERVED_2_MASK                                                         (0x00000080U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_RESERVED_3_SHIFT                                                        (11U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_RESERVED_3_MASK                                                         (0x00000800U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_RESERVED_4_SHIFT                                                        (15U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP2_RESERVED_4_MASK                                                         (0x00008000U)

#define GMAC_SW_P2_SA_HI_MACSRCADDR_47_40_SHIFT                                                             (0U)
#define GMAC_SW_P2_SA_HI_MACSRCADDR_47_40_MASK                                                              (0x000000ffU)

#define GMAC_SW_P2_SA_HI_MACSRCADDR_39_32_SHIFT                                                             (8U)
#define GMAC_SW_P2_SA_HI_MACSRCADDR_39_32_MASK                                                              (0x0000ff00U)

#define GMAC_SW_P2_SA_HI_MACSRCADDR_31_23_SHIFT                                                             (16U)
#define GMAC_SW_P2_SA_HI_MACSRCADDR_31_23_MASK                                                              (0x00ff0000U)

#define GMAC_SW_P2_SA_HI_MACSRCADDR_23_16_SHIFT                                                             (24U)
#define GMAC_SW_P2_SA_HI_MACSRCADDR_23_16_MASK                                                              (0xff000000U)

#define GMAC_SW_P2_SA_LO_MACSRCADDR_15_8_SHIFT                                                              (0U)
#define GMAC_SW_P2_SA_LO_MACSRCADDR_15_8_MASK                                                               (0x000000ffU)

#define GMAC_SW_P2_SA_LO_MACSRCADDR_7_0_SHIFT                                                               (8U)
#define GMAC_SW_P2_SA_LO_MACSRCADDR_7_0_MASK                                                                (0x0000ff00U)

#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI0_SHIFT                                                              (0U)
#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI0_MASK                                                               (0x00000007U)

#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI1_SHIFT                                                              (4U)
#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI1_MASK                                                               (0x00000070U)

#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI2_SHIFT                                                              (8U)
#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI2_MASK                                                               (0x00000700U)

#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI3_SHIFT                                                              (12U)
#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI3_MASK                                                               (0x00007000U)

#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI4_SHIFT                                                              (16U)
#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI4_MASK                                                               (0x00070000U)

#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI5_SHIFT                                                              (20U)
#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI5_MASK                                                               (0x00700000U)

#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI6_SHIFT                                                              (24U)
#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI6_MASK                                                               (0x07000000U)

#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI7_SHIFT                                                              (28U)
#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_PRI7_MASK                                                               (0x70000000U)

#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_RESERVED_SHIFT                                                          (3U)
#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_RESERVED_MASK                                                           (0x00000008U)

#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_RESERVED_2_SHIFT                                                        (7U)
#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_RESERVED_2_MASK                                                         (0x00000080U)

#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_RESERVED_3_SHIFT                                                        (11U)
#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_RESERVED_3_MASK                                                         (0x00000800U)

#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_RESERVED_4_SHIFT                                                        (15U)
#define GMAC_SW_P0_CPDMA_TX_PRI_MAP_RESERVED_4_MASK                                                         (0x00008000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI32_SHIFT                                                             (0U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI32_MASK                                                              (0x00000007U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI33_SHIFT                                                             (4U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI33_MASK                                                              (0x00000070U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI34_SHIFT                                                             (8U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI34_MASK                                                              (0x00000700U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI35_SHIFT                                                             (12U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI35_MASK                                                              (0x00007000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI36_SHIFT                                                             (16U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI36_MASK                                                              (0x00070000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI37_SHIFT                                                             (20U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI37_MASK                                                              (0x00700000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI38_SHIFT                                                             (24U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI38_MASK                                                              (0x07000000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI39_SHIFT                                                             (28U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_PRI39_MASK                                                              (0x70000000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_RESERVED_SHIFT                                                          (3U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_RESERVED_MASK                                                           (0x00000008U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_RESERVED_2_SHIFT                                                        (7U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_RESERVED_2_MASK                                                         (0x00000080U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_RESERVED_3_SHIFT                                                        (11U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_RESERVED_3_MASK                                                         (0x00000800U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_RESERVED_4_SHIFT                                                        (15U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP4_RESERVED_4_MASK                                                         (0x00008000U)

#define GMAC_SW_P0_BLK_CNT_P0_RX_BLK_CNT_SHIFT                                                              (0U)
#define GMAC_SW_P0_BLK_CNT_P0_RX_BLK_CNT_MASK                                                               (0x0000000fU)

#define GMAC_SW_P0_BLK_CNT_P0_TX_BLK_CNT_SHIFT                                                              (4U)
#define GMAC_SW_P0_BLK_CNT_P0_TX_BLK_CNT_MASK                                                               (0x000001f0U)

#define GMAC_SW_P0_BLK_CNT_RESERVED_SHIFT                                                                   (9U)
#define GMAC_SW_P0_BLK_CNT_RESERVED_MASK                                                                    (0x0000fe00U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI0_SHIFT                                                              (0U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI0_MASK                                                               (0x00000007U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI1_SHIFT                                                              (4U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI1_MASK                                                               (0x00000070U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI2_SHIFT                                                              (8U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI2_MASK                                                               (0x00000700U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI3_SHIFT                                                              (12U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI3_MASK                                                               (0x00007000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI4_SHIFT                                                              (16U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI4_MASK                                                               (0x00070000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI5_SHIFT                                                              (20U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI5_MASK                                                               (0x00700000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI6_SHIFT                                                              (24U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI6_MASK                                                               (0x07000000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI7_SHIFT                                                              (28U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_PRI7_MASK                                                               (0x70000000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_RESERVED_SHIFT                                                          (3U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_RESERVED_MASK                                                           (0x00000008U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_RESERVED_2_SHIFT                                                        (7U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_RESERVED_2_MASK                                                         (0x00000080U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_RESERVED_3_SHIFT                                                        (11U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_RESERVED_3_MASK                                                         (0x00000800U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_RESERVED_4_SHIFT                                                        (15U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP0_RESERVED_4_MASK                                                         (0x00008000U)

#define GMAC_SW_P0_TX_IN_CTL_TX_PRI_WDS_SHIFT                                                               (0U)
#define GMAC_SW_P0_TX_IN_CTL_TX_PRI_WDS_MASK                                                                (0x000003ffU)

#define GMAC_SW_P0_TX_IN_CTL_TX_BLKS_REM_SHIFT                                                              (12U)
#define GMAC_SW_P0_TX_IN_CTL_TX_BLKS_REM_MASK                                                               (0x0000f000U)

#define GMAC_SW_P0_TX_IN_CTL_TX_IN_SEL_SHIFT                                                                (16U)
#define GMAC_SW_P0_TX_IN_CTL_TX_IN_SEL_MASK                                                                 (0x00030000U)

#define GMAC_SW_P0_TX_IN_CTL_TX_RATE_EN_SHIFT                                                               (20U)
#define GMAC_SW_P0_TX_IN_CTL_TX_RATE_EN_MASK                                                                (0x00f00000U)

#define GMAC_SW_P0_TX_IN_CTL_RESERVED_SHIFT                                                                 (10U)
#define GMAC_SW_P0_TX_IN_CTL_RESERVED_MASK                                                                  (0x00000c00U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI40_SHIFT                                                             (0U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI40_MASK                                                              (0x00000007U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI41_SHIFT                                                             (4U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI41_MASK                                                              (0x00000070U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI42_SHIFT                                                             (8U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI42_MASK                                                              (0x00000700U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI43_SHIFT                                                             (12U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI43_MASK                                                              (0x00007000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI44_SHIFT                                                             (16U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI44_MASK                                                              (0x00070000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI45_SHIFT                                                             (20U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI45_MASK                                                              (0x00700000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI46_SHIFT                                                             (24U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI46_MASK                                                              (0x07000000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI47_SHIFT                                                             (28U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_PRI47_MASK                                                              (0x70000000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_RESERVED_SHIFT                                                          (3U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_RESERVED_MASK                                                           (0x00000008U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_RESERVED_2_SHIFT                                                        (7U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_RESERVED_2_MASK                                                         (0x00000080U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_RESERVED_3_SHIFT                                                        (11U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_RESERVED_3_MASK                                                         (0x00000800U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_RESERVED_4_SHIFT                                                        (15U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP5_RESERVED_4_MASK                                                         (0x00008000U)

#define GMAC_SW_P2_SEND_PERCENT_PRI1_SEND_PERCENT_SHIFT                                                     (0U)
#define GMAC_SW_P2_SEND_PERCENT_PRI1_SEND_PERCENT_MASK                                                      (0x0000007fU)

#define GMAC_SW_P2_SEND_PERCENT_PRI2_SEND_PERCENT_SHIFT                                                     (8U)
#define GMAC_SW_P2_SEND_PERCENT_PRI2_SEND_PERCENT_MASK                                                      (0x00007f00U)

#define GMAC_SW_P2_SEND_PERCENT_PRI3_SEND_PERCENT_SHIFT                                                     (16U)
#define GMAC_SW_P2_SEND_PERCENT_PRI3_SEND_PERCENT_MASK                                                      (0x007f0000U)

#define GMAC_SW_P2_SEND_PERCENT_RESERVED_SHIFT                                                              (7U)
#define GMAC_SW_P2_SEND_PERCENT_RESERVED_MASK                                                               (0x00000080U)

#define GMAC_SW_P2_SEND_PERCENT_RESERVED_2_SHIFT                                                            (15U)
#define GMAC_SW_P2_SEND_PERCENT_RESERVED_2_MASK                                                             (0x00008000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI56_SHIFT                                                             (0U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI56_MASK                                                              (0x00000007U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI57_SHIFT                                                             (4U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI57_MASK                                                              (0x00000070U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI58_SHIFT                                                             (8U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI58_MASK                                                              (0x00000700U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI59_SHIFT                                                             (12U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI59_MASK                                                              (0x00007000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI60_SHIFT                                                             (16U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI60_MASK                                                              (0x00070000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI61_SHIFT                                                             (20U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI61_MASK                                                              (0x00700000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI62_SHIFT                                                             (24U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI62_MASK                                                              (0x07000000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI63_SHIFT                                                             (28U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_PRI63_MASK                                                              (0x70000000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_RESERVED_SHIFT                                                          (3U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_RESERVED_MASK                                                           (0x00000008U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_RESERVED_2_SHIFT                                                        (7U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_RESERVED_2_MASK                                                         (0x00000080U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_RESERVED_3_SHIFT                                                        (11U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_RESERVED_3_MASK                                                         (0x00000800U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_RESERVED_4_SHIFT                                                        (15U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP7_RESERVED_4_MASK                                                         (0x00008000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI8_SHIFT                                                              (0U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI8_MASK                                                               (0x00000007U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI9_SHIFT                                                              (4U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI9_MASK                                                               (0x00000070U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI10_SHIFT                                                             (8U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI10_MASK                                                              (0x00000700U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI11_SHIFT                                                             (12U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI11_MASK                                                              (0x00007000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI12_SHIFT                                                             (16U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI12_MASK                                                              (0x00070000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI13_SHIFT                                                             (20U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI13_MASK                                                              (0x00700000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI14_SHIFT                                                             (24U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI14_MASK                                                              (0x07000000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI15_SHIFT                                                             (28U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_PRI15_MASK                                                              (0x70000000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_RESERVED_SHIFT                                                          (3U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_RESERVED_MASK                                                           (0x00000008U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_RESERVED_2_SHIFT                                                        (7U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_RESERVED_2_MASK                                                         (0x00000080U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_RESERVED_3_SHIFT                                                        (11U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_RESERVED_3_MASK                                                         (0x00000800U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_RESERVED_4_SHIFT                                                        (15U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP1_RESERVED_4_MASK                                                         (0x00008000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI8_SHIFT                                                              (0U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI8_MASK                                                               (0x00000007U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI9_SHIFT                                                              (4U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI9_MASK                                                               (0x00000070U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI10_SHIFT                                                             (8U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI10_MASK                                                              (0x00000700U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI11_SHIFT                                                             (12U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI11_MASK                                                              (0x00007000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI12_SHIFT                                                             (16U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI12_MASK                                                              (0x00070000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI13_SHIFT                                                             (20U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI13_MASK                                                              (0x00700000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI14_SHIFT                                                             (24U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI14_MASK                                                              (0x07000000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI15_SHIFT                                                             (28U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_PRI15_MASK                                                              (0x70000000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_RESERVED_SHIFT                                                          (3U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_RESERVED_MASK                                                           (0x00000008U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_RESERVED_2_SHIFT                                                        (7U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_RESERVED_2_MASK                                                         (0x00000080U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_RESERVED_3_SHIFT                                                        (11U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_RESERVED_3_MASK                                                         (0x00000800U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_RESERVED_4_SHIFT                                                        (15U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP1_RESERVED_4_MASK                                                         (0x00008000U)

#define GMAC_SW_P1_TX_IN_CTL_TX_PRI_WDS_SHIFT                                                               (0U)
#define GMAC_SW_P1_TX_IN_CTL_TX_PRI_WDS_MASK                                                                (0x000003ffU)

#define GMAC_SW_P1_TX_IN_CTL_TX_BLKS_REM_SHIFT                                                              (12U)
#define GMAC_SW_P1_TX_IN_CTL_TX_BLKS_REM_MASK                                                               (0x0000f000U)

#define GMAC_SW_P1_TX_IN_CTL_TX_IN_SEL_SHIFT                                                                (16U)
#define GMAC_SW_P1_TX_IN_CTL_TX_IN_SEL_MASK                                                                 (0x00030000U)

#define GMAC_SW_P1_TX_IN_CTL_TX_RATE_EN_SHIFT                                                               (20U)
#define GMAC_SW_P1_TX_IN_CTL_TX_RATE_EN_MASK                                                                (0x00f00000U)

#define GMAC_SW_P1_TX_IN_CTL_HOST_BLKS_REM_SHIFT                                                            (24U)
#define GMAC_SW_P1_TX_IN_CTL_HOST_BLKS_REM_MASK                                                             (0x0f000000U)

#define GMAC_SW_P1_TX_IN_CTL_RESERVED_SHIFT                                                                 (10U)
#define GMAC_SW_P1_TX_IN_CTL_RESERVED_MASK                                                                  (0x00000c00U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI32_SHIFT                                                             (0U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI32_MASK                                                              (0x00000007U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI33_SHIFT                                                             (4U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI33_MASK                                                              (0x00000070U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI34_SHIFT                                                             (8U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI34_MASK                                                              (0x00000700U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI35_SHIFT                                                             (12U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI35_MASK                                                              (0x00007000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI36_SHIFT                                                             (16U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI36_MASK                                                              (0x00070000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI37_SHIFT                                                             (20U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI37_MASK                                                              (0x00700000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI38_SHIFT                                                             (24U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI38_MASK                                                              (0x07000000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI39_SHIFT                                                             (28U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_PRI39_MASK                                                              (0x70000000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_RESERVED_SHIFT                                                          (3U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_RESERVED_MASK                                                           (0x00000008U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_RESERVED_2_SHIFT                                                        (7U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_RESERVED_2_MASK                                                         (0x00000080U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_RESERVED_3_SHIFT                                                        (11U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_RESERVED_3_MASK                                                         (0x00000800U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_RESERVED_4_SHIFT                                                        (15U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP4_RESERVED_4_MASK                                                         (0x00008000U)

#define GMAC_SW_P2_TS_SEQ_MTYPE_P2_TS_MSG_TYPE_EN_SHIFT                                                     (0U)
#define GMAC_SW_P2_TS_SEQ_MTYPE_P2_TS_MSG_TYPE_EN_MASK                                                      (0x0000ffffU)

#define GMAC_SW_P2_TS_SEQ_MTYPE_P2_TS_SEQ_ID_OFFSET_SHIFT                                                   (16U)
#define GMAC_SW_P2_TS_SEQ_MTYPE_P2_TS_SEQ_ID_OFFSET_MASK                                                    (0x003f0000U)

#define GMAC_SW_P0_PORT_VLAN_PORT_VID_SHIFT                                                                 (0U)
#define GMAC_SW_P0_PORT_VLAN_PORT_VID_MASK                                                                  (0x00000fffU)

#define GMAC_SW_P0_PORT_VLAN_PORT_CFI_SHIFT                                                                 (12U)
#define GMAC_SW_P0_PORT_VLAN_PORT_CFI_MASK                                                                  (0x00001000U)

#define GMAC_SW_P0_PORT_VLAN_PORT_PRI_SHIFT                                                                 (13U)
#define GMAC_SW_P0_PORT_VLAN_PORT_PRI_MASK                                                                  (0x0000e000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI32_SHIFT                                                             (0U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI32_MASK                                                              (0x00000007U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI33_SHIFT                                                             (4U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI33_MASK                                                              (0x00000070U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI34_SHIFT                                                             (8U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI34_MASK                                                              (0x00000700U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI35_SHIFT                                                             (12U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI35_MASK                                                              (0x00007000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI36_SHIFT                                                             (16U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI36_MASK                                                              (0x00070000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI37_SHIFT                                                             (20U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI37_MASK                                                              (0x00700000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI38_SHIFT                                                             (24U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI38_MASK                                                              (0x07000000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI39_SHIFT                                                             (28U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_PRI39_MASK                                                              (0x70000000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_RESERVED_SHIFT                                                          (3U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_RESERVED_MASK                                                           (0x00000008U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_RESERVED_2_SHIFT                                                        (7U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_RESERVED_2_MASK                                                         (0x00000080U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_RESERVED_3_SHIFT                                                        (11U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_RESERVED_3_MASK                                                         (0x00000800U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_RESERVED_4_SHIFT                                                        (15U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP4_RESERVED_4_MASK                                                         (0x00008000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI40_SHIFT                                                             (0U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI40_MASK                                                              (0x00000007U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI41_SHIFT                                                             (4U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI41_MASK                                                              (0x00000070U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI42_SHIFT                                                             (8U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI42_MASK                                                              (0x00000700U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI43_SHIFT                                                             (12U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI43_MASK                                                              (0x00007000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI44_SHIFT                                                             (16U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI44_MASK                                                              (0x00070000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI45_SHIFT                                                             (20U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI45_MASK                                                              (0x00700000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI46_SHIFT                                                             (24U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI46_MASK                                                              (0x07000000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI47_SHIFT                                                             (28U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_PRI47_MASK                                                              (0x70000000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_RESERVED_SHIFT                                                          (3U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_RESERVED_MASK                                                           (0x00000008U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_RESERVED_2_SHIFT                                                        (7U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_RESERVED_2_MASK                                                         (0x00000080U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_RESERVED_3_SHIFT                                                        (11U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_RESERVED_3_MASK                                                         (0x00000800U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_RESERVED_4_SHIFT                                                        (15U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP5_RESERVED_4_MASK                                                         (0x00008000U)

#define GMAC_SW_P2_CONTROL_P2_TS_RX_EN_SHIFT                                                                (0U)
#define GMAC_SW_P2_CONTROL_P2_TS_RX_EN_MASK                                                                 (0x00000001U)

#define GMAC_SW_P2_CONTROL_P2_TS_TX_EN_SHIFT                                                                (1U)
#define GMAC_SW_P2_CONTROL_P2_TS_TX_EN_MASK                                                                 (0x00000002U)

#define GMAC_SW_P2_CONTROL_P2_TS_LTYPE1_EN_SHIFT                                                            (2U)
#define GMAC_SW_P2_CONTROL_P2_TS_LTYPE1_EN_MASK                                                             (0x00000004U)

#define GMAC_SW_P2_CONTROL_P2_TS_LTYPE2_EN_SHIFT                                                            (3U)
#define GMAC_SW_P2_CONTROL_P2_TS_LTYPE2_EN_MASK                                                             (0x00000008U)

#define GMAC_SW_P2_CONTROL_P2_TS_ANNEX_D_EN_SHIFT                                                           (4U)
#define GMAC_SW_P2_CONTROL_P2_TS_ANNEX_D_EN_MASK                                                            (0x00000010U)

#define GMAC_SW_P2_CONTROL_P2_TS_TTL_NONZERO_SHIFT                                                          (8U)
#define GMAC_SW_P2_CONTROL_P2_TS_TTL_NONZERO_MASK                                                           (0x00000100U)

#define GMAC_SW_P2_CONTROL_P2_TS_129_SHIFT                                                                  (9U)
#define GMAC_SW_P2_CONTROL_P2_TS_129_MASK                                                                   (0x00000200U)

#define GMAC_SW_P2_CONTROL_P2_TS_130_SHIFT                                                                  (10U)
#define GMAC_SW_P2_CONTROL_P2_TS_130_MASK                                                                   (0x00000400U)

#define GMAC_SW_P2_CONTROL_P2_TS_131_SHIFT                                                                  (11U)
#define GMAC_SW_P2_CONTROL_P2_TS_131_MASK                                                                   (0x00000800U)

#define GMAC_SW_P2_CONTROL_P2_TS_132_SHIFT                                                                  (12U)
#define GMAC_SW_P2_CONTROL_P2_TS_132_MASK                                                                   (0x00001000U)

#define GMAC_SW_P2_CONTROL_P2_TS_319_SHIFT                                                                  (13U)
#define GMAC_SW_P2_CONTROL_P2_TS_319_MASK                                                                   (0x00002000U)

#define GMAC_SW_P2_CONTROL_P2_TS_320_SHIFT                                                                  (14U)
#define GMAC_SW_P2_CONTROL_P2_TS_320_MASK                                                                   (0x00004000U)

#define GMAC_SW_P2_CONTROL_P2_DSCP_PRI_EN_SHIFT                                                             (16U)
#define GMAC_SW_P2_CONTROL_P2_DSCP_PRI_EN_MASK                                                              (0x00010000U)

#define GMAC_SW_P2_CONTROL_P2_VLAN_LTYPE1_EN_SHIFT                                                          (20U)
#define GMAC_SW_P2_CONTROL_P2_VLAN_LTYPE1_EN_MASK                                                           (0x00100000U)

#define GMAC_SW_P2_CONTROL_P2_VLAN_LTYPE2_EN_SHIFT                                                          (21U)
#define GMAC_SW_P2_CONTROL_P2_VLAN_LTYPE2_EN_MASK                                                           (0x00200000U)

#define GMAC_SW_P2_CONTROL_P2_PASS_PRI_TAGGED_SHIFT                                                         (24U)
#define GMAC_SW_P2_CONTROL_P2_PASS_PRI_TAGGED_MASK                                                          (0x01000000U)

#define GMAC_SW_P2_CONTROL_RESERVED_SHIFT                                                                   (5U)
#define GMAC_SW_P2_CONTROL_RESERVED_MASK                                                                    (0x000000e0U)

#define GMAC_SW_P2_CONTROL_RESERVED_2_SHIFT                                                                 (15U)
#define GMAC_SW_P2_CONTROL_RESERVED_2_MASK                                                                  (0x00008000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI40_SHIFT                                                             (0U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI40_MASK                                                              (0x00000007U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI41_SHIFT                                                             (4U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI41_MASK                                                              (0x00000070U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI42_SHIFT                                                             (8U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI42_MASK                                                              (0x00000700U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI43_SHIFT                                                             (12U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI43_MASK                                                              (0x00007000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI44_SHIFT                                                             (16U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI44_MASK                                                              (0x00070000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI45_SHIFT                                                             (20U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI45_MASK                                                              (0x00700000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI46_SHIFT                                                             (24U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI46_MASK                                                              (0x07000000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI47_SHIFT                                                             (28U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_PRI47_MASK                                                              (0x70000000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_RESERVED_SHIFT                                                          (3U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_RESERVED_MASK                                                           (0x00000008U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_RESERVED_2_SHIFT                                                        (7U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_RESERVED_2_MASK                                                         (0x00000080U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_RESERVED_3_SHIFT                                                        (11U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_RESERVED_3_MASK                                                         (0x00000800U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_RESERVED_4_SHIFT                                                        (15U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP5_RESERVED_4_MASK                                                         (0x00008000U)

#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P1_PRI0_SHIFT                                                            (0U)
#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P1_PRI0_MASK                                                             (0x00000007U)

#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P1_PRI1_SHIFT                                                            (4U)
#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P1_PRI1_MASK                                                             (0x00000070U)

#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P1_PRI2_SHIFT                                                            (8U)
#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P1_PRI2_MASK                                                             (0x00000700U)

#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P1_PRI3_SHIFT                                                            (12U)
#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P1_PRI3_MASK                                                             (0x00007000U)

#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P2_PRI0_SHIFT                                                            (16U)
#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P2_PRI0_MASK                                                             (0x00070000U)

#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P2_PRI1_SHIFT                                                            (20U)
#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P2_PRI1_MASK                                                             (0x00700000U)

#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P2_PRI2_SHIFT                                                            (24U)
#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P2_PRI2_MASK                                                             (0x07000000U)

#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P2_PRI3_SHIFT                                                            (28U)
#define GMAC_SW_P0_CPDMA_RX_CH_MAP_P2_PRI3_MASK                                                             (0x70000000U)

#define GMAC_SW_P0_CPDMA_RX_CH_MAP_RESERVED_SHIFT                                                           (3U)
#define GMAC_SW_P0_CPDMA_RX_CH_MAP_RESERVED_MASK                                                            (0x00000008U)

#define GMAC_SW_P0_CPDMA_RX_CH_MAP_RESERVED_2_SHIFT                                                         (7U)
#define GMAC_SW_P0_CPDMA_RX_CH_MAP_RESERVED_2_MASK                                                          (0x00000080U)

#define GMAC_SW_P0_CPDMA_RX_CH_MAP_RESERVED_3_SHIFT                                                         (11U)
#define GMAC_SW_P0_CPDMA_RX_CH_MAP_RESERVED_3_MASK                                                          (0x00000800U)

#define GMAC_SW_P0_CPDMA_RX_CH_MAP_RESERVED_4_SHIFT                                                         (15U)
#define GMAC_SW_P0_CPDMA_RX_CH_MAP_RESERVED_4_MASK                                                          (0x00008000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI16_SHIFT                                                             (0U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI16_MASK                                                              (0x00000007U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI17_SHIFT                                                             (4U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI17_MASK                                                              (0x00000070U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI18_SHIFT                                                             (8U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI18_MASK                                                              (0x00000700U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI19_SHIFT                                                             (12U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI19_MASK                                                              (0x00007000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI20_SHIFT                                                             (16U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI20_MASK                                                              (0x00070000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI21_SHIFT                                                             (20U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI21_MASK                                                              (0x00700000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI22_SHIFT                                                             (24U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI22_MASK                                                              (0x07000000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI23_SHIFT                                                             (28U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_PRI23_MASK                                                              (0x70000000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_RESERVED_SHIFT                                                          (3U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_RESERVED_MASK                                                           (0x00000008U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_RESERVED_2_SHIFT                                                        (7U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_RESERVED_2_MASK                                                         (0x00000080U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_RESERVED_3_SHIFT                                                        (11U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_RESERVED_3_MASK                                                         (0x00000800U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_RESERVED_4_SHIFT                                                        (15U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP2_RESERVED_4_MASK                                                         (0x00008000U)

#define GMAC_SW_P1_MAX_BLKS_P1_RX_MAX_BLKS_SHIFT                                                            (0U)
#define GMAC_SW_P1_MAX_BLKS_P1_RX_MAX_BLKS_MASK                                                             (0x0000000fU)

#define GMAC_SW_P1_MAX_BLKS_P1_TX_MAX_BLKS_SHIFT                                                            (4U)
#define GMAC_SW_P1_MAX_BLKS_P1_TX_MAX_BLKS_MASK                                                             (0x000001f0U)

#define GMAC_SW_P1_MAX_BLKS_RESERVED_SHIFT                                                                  (9U)
#define GMAC_SW_P1_MAX_BLKS_RESERVED_MASK                                                                   (0x0000fe00U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI24_SHIFT                                                             (0U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI24_MASK                                                              (0x00000007U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI25_SHIFT                                                             (4U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI25_MASK                                                              (0x00000070U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI26_SHIFT                                                             (8U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI26_MASK                                                              (0x00000700U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI27_SHIFT                                                             (12U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI27_MASK                                                              (0x00007000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI28_SHIFT                                                             (16U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI28_MASK                                                              (0x00070000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI29_SHIFT                                                             (20U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI29_MASK                                                              (0x00700000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI30_SHIFT                                                             (24U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI30_MASK                                                              (0x07000000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI31_SHIFT                                                             (28U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_PRI31_MASK                                                              (0x70000000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_RESERVED_SHIFT                                                          (3U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_RESERVED_MASK                                                           (0x00000008U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_RESERVED_2_SHIFT                                                        (7U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_RESERVED_2_MASK                                                         (0x00000080U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_RESERVED_3_SHIFT                                                        (11U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_RESERVED_3_MASK                                                         (0x00000800U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_RESERVED_4_SHIFT                                                        (15U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP3_RESERVED_4_MASK                                                         (0x00008000U)

#define GMAC_SW_P1_TX_PRI_MAP_PRI0_SHIFT                                                                    (0U)
#define GMAC_SW_P1_TX_PRI_MAP_PRI0_MASK                                                                     (0x00000003U)

#define GMAC_SW_P1_TX_PRI_MAP_PRI1_SHIFT                                                                    (4U)
#define GMAC_SW_P1_TX_PRI_MAP_PRI1_MASK                                                                     (0x00000030U)

#define GMAC_SW_P1_TX_PRI_MAP_PRI2_SHIFT                                                                    (8U)
#define GMAC_SW_P1_TX_PRI_MAP_PRI2_MASK                                                                     (0x00000300U)

#define GMAC_SW_P1_TX_PRI_MAP_PRI3_SHIFT                                                                    (12U)
#define GMAC_SW_P1_TX_PRI_MAP_PRI3_MASK                                                                     (0x00003000U)

#define GMAC_SW_P1_TX_PRI_MAP_PRI4_SHIFT                                                                    (16U)
#define GMAC_SW_P1_TX_PRI_MAP_PRI4_MASK                                                                     (0x00030000U)

#define GMAC_SW_P1_TX_PRI_MAP_PRI5_SHIFT                                                                    (20U)
#define GMAC_SW_P1_TX_PRI_MAP_PRI5_MASK                                                                     (0x00300000U)

#define GMAC_SW_P1_TX_PRI_MAP_PRI6_SHIFT                                                                    (24U)
#define GMAC_SW_P1_TX_PRI_MAP_PRI6_MASK                                                                     (0x03000000U)

#define GMAC_SW_P1_TX_PRI_MAP_PRI7_SHIFT                                                                    (28U)
#define GMAC_SW_P1_TX_PRI_MAP_PRI7_MASK                                                                     (0x30000000U)

#define GMAC_SW_P1_TX_PRI_MAP_RESERVED_SHIFT                                                                (2U)
#define GMAC_SW_P1_TX_PRI_MAP_RESERVED_MASK                                                                 (0x0000000cU)

#define GMAC_SW_P1_TX_PRI_MAP_RESERVED_2_SHIFT                                                              (6U)
#define GMAC_SW_P1_TX_PRI_MAP_RESERVED_2_MASK                                                               (0x000000c0U)

#define GMAC_SW_P1_TX_PRI_MAP_RESERVED_3_SHIFT                                                              (10U)
#define GMAC_SW_P1_TX_PRI_MAP_RESERVED_3_MASK                                                               (0x00000c00U)

#define GMAC_SW_P1_TX_PRI_MAP_RESERVED_4_SHIFT                                                              (14U)
#define GMAC_SW_P1_TX_PRI_MAP_RESERVED_4_MASK                                                               (0x0000c000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI24_SHIFT                                                             (0U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI24_MASK                                                              (0x00000007U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI25_SHIFT                                                             (4U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI25_MASK                                                              (0x00000070U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI26_SHIFT                                                             (8U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI26_MASK                                                              (0x00000700U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI27_SHIFT                                                             (12U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI27_MASK                                                              (0x00007000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI28_SHIFT                                                             (16U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI28_MASK                                                              (0x00070000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI29_SHIFT                                                             (20U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI29_MASK                                                              (0x00700000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI30_SHIFT                                                             (24U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI30_MASK                                                              (0x07000000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI31_SHIFT                                                             (28U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_PRI31_MASK                                                              (0x70000000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_RESERVED_SHIFT                                                          (3U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_RESERVED_MASK                                                           (0x00000008U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_RESERVED_2_SHIFT                                                        (7U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_RESERVED_2_MASK                                                         (0x00000080U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_RESERVED_3_SHIFT                                                        (11U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_RESERVED_3_MASK                                                         (0x00000800U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_RESERVED_4_SHIFT                                                        (15U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP3_RESERVED_4_MASK                                                         (0x00008000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI48_SHIFT                                                             (0U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI48_MASK                                                              (0x00000007U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI49_SHIFT                                                             (4U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI49_MASK                                                              (0x00000070U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI50_SHIFT                                                             (8U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI50_MASK                                                              (0x00000700U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI51_SHIFT                                                             (12U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI51_MASK                                                              (0x00007000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI52_SHIFT                                                             (16U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI52_MASK                                                              (0x00070000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI53_SHIFT                                                             (20U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI53_MASK                                                              (0x00700000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI54_SHIFT                                                             (24U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI54_MASK                                                              (0x07000000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI55_SHIFT                                                             (28U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_PRI55_MASK                                                              (0x70000000U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_RESERVED_SHIFT                                                          (3U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_RESERVED_MASK                                                           (0x00000008U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_RESERVED_2_SHIFT                                                        (7U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_RESERVED_2_MASK                                                         (0x00000080U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_RESERVED_3_SHIFT                                                        (11U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_RESERVED_3_MASK                                                         (0x00000800U)

#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_RESERVED_4_SHIFT                                                        (15U)
#define GMAC_SW_P1_RX_DSCP_PRI_MAP6_RESERVED_4_MASK                                                         (0x00008000U)

#define GMAC_SW_P1_SA_HI_MACSRCADDR_47_40_SHIFT                                                             (0U)
#define GMAC_SW_P1_SA_HI_MACSRCADDR_47_40_MASK                                                              (0x000000ffU)

#define GMAC_SW_P1_SA_HI_MACSRCADDR_39_32_SHIFT                                                             (8U)
#define GMAC_SW_P1_SA_HI_MACSRCADDR_39_32_MASK                                                              (0x0000ff00U)

#define GMAC_SW_P1_SA_HI_MACSRCADDR_31_24_SHIFT                                                             (16U)
#define GMAC_SW_P1_SA_HI_MACSRCADDR_31_24_MASK                                                              (0x00ff0000U)

#define GMAC_SW_P1_SA_HI_MACSRCADDR_23_16_SHIFT                                                             (24U)
#define GMAC_SW_P1_SA_HI_MACSRCADDR_23_16_MASK                                                              (0xff000000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI48_SHIFT                                                             (0U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI48_MASK                                                              (0x00000007U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI49_SHIFT                                                             (4U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI49_MASK                                                              (0x00000070U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI50_SHIFT                                                             (8U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI50_MASK                                                              (0x00000700U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI51_SHIFT                                                             (12U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI51_MASK                                                              (0x00007000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI52_SHIFT                                                             (16U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI52_MASK                                                              (0x00070000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI53_SHIFT                                                             (20U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI53_MASK                                                              (0x00700000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI54_SHIFT                                                             (24U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI54_MASK                                                              (0x07000000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI55_SHIFT                                                             (28U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_PRI55_MASK                                                              (0x70000000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_SHIFT                                                          (3U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_MASK                                                           (0x00000008U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_2_SHIFT                                                        (7U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_2_MASK                                                         (0x00000080U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_3_SHIFT                                                        (11U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_3_MASK                                                         (0x00000800U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_4_SHIFT                                                        (15U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_4_MASK                                                         (0x00008000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_5_SHIFT                                                        (19U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_5_MASK                                                         (0x00080000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_6_SHIFT                                                        (23U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_6_MASK                                                         (0x00800000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_7_SHIFT                                                        (27U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_7_MASK                                                         (0x08000000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_8_SHIFT                                                        (31U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP6_RESERVED_8_MASK                                                         (0x80000000U)

#define GMAC_SW_P2_MAX_BLKS_P2_RX_MAX_BLKS_SHIFT                                                            (0U)
#define GMAC_SW_P2_MAX_BLKS_P2_RX_MAX_BLKS_MASK                                                             (0x0000000fU)

#define GMAC_SW_P2_MAX_BLKS_P2_TX_MAX_BLKS_SHIFT                                                            (4U)
#define GMAC_SW_P2_MAX_BLKS_P2_TX_MAX_BLKS_MASK                                                             (0x000001f0U)

#define GMAC_SW_P2_MAX_BLKS_RESERVED_SHIFT                                                                  (9U)
#define GMAC_SW_P2_MAX_BLKS_RESERVED_MASK                                                                   (0xfffffe00U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI24_SHIFT                                                             (0U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI24_MASK                                                              (0x00000007U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI25_SHIFT                                                             (4U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI25_MASK                                                              (0x00000070U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI26_SHIFT                                                             (8U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI26_MASK                                                              (0x00000700U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI27_SHIFT                                                             (12U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI27_MASK                                                              (0x00007000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI28_SHIFT                                                             (16U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI28_MASK                                                              (0x00070000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI29_SHIFT                                                             (20U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI29_MASK                                                              (0x00700000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI30_SHIFT                                                             (24U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI30_MASK                                                              (0x07000000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI31_SHIFT                                                             (28U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_PRI31_MASK                                                              (0x70000000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_SHIFT                                                          (3U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_MASK                                                           (0x00000008U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_2_SHIFT                                                        (7U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_2_MASK                                                         (0x00000080U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_3_SHIFT                                                        (11U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_3_MASK                                                         (0x00000800U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_4_SHIFT                                                        (15U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_4_MASK                                                         (0x00008000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_5_SHIFT                                                        (19U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_5_MASK                                                         (0x00080000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_6_SHIFT                                                        (23U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_6_MASK                                                         (0x00800000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_7_SHIFT                                                        (27U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_7_MASK                                                         (0x08000000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_8_SHIFT                                                        (31U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP3_RESERVED_8_MASK                                                         (0x80000000U)

#define GMAC_SW_P0_TX_PRI_MAP_PRI0_SHIFT                                                                    (0U)
#define GMAC_SW_P0_TX_PRI_MAP_PRI0_MASK                                                                     (0x00000003U)

#define GMAC_SW_P0_TX_PRI_MAP_PRI1_SHIFT                                                                    (4U)
#define GMAC_SW_P0_TX_PRI_MAP_PRI1_MASK                                                                     (0x00000030U)

#define GMAC_SW_P0_TX_PRI_MAP_PRI2_SHIFT                                                                    (8U)
#define GMAC_SW_P0_TX_PRI_MAP_PRI2_MASK                                                                     (0x00000300U)

#define GMAC_SW_P0_TX_PRI_MAP_PRI3_SHIFT                                                                    (12U)
#define GMAC_SW_P0_TX_PRI_MAP_PRI3_MASK                                                                     (0x00003000U)

#define GMAC_SW_P0_TX_PRI_MAP_PRI4_SHIFT                                                                    (16U)
#define GMAC_SW_P0_TX_PRI_MAP_PRI4_MASK                                                                     (0x00030000U)

#define GMAC_SW_P0_TX_PRI_MAP_PRI5_SHIFT                                                                    (20U)
#define GMAC_SW_P0_TX_PRI_MAP_PRI5_MASK                                                                     (0x00300000U)

#define GMAC_SW_P0_TX_PRI_MAP_PRI6_SHIFT                                                                    (24U)
#define GMAC_SW_P0_TX_PRI_MAP_PRI6_MASK                                                                     (0x03000000U)

#define GMAC_SW_P0_TX_PRI_MAP_PRI7_SHIFT                                                                    (28U)
#define GMAC_SW_P0_TX_PRI_MAP_PRI7_MASK                                                                     (0x30000000U)

#define GMAC_SW_P0_TX_PRI_MAP_RESERVED_SHIFT                                                                (2U)
#define GMAC_SW_P0_TX_PRI_MAP_RESERVED_MASK                                                                 (0x0000000cU)

#define GMAC_SW_P0_TX_PRI_MAP_RESERVED_2_SHIFT                                                              (6U)
#define GMAC_SW_P0_TX_PRI_MAP_RESERVED_2_MASK                                                               (0x000000c0U)

#define GMAC_SW_P0_TX_PRI_MAP_RESERVED_3_SHIFT                                                              (10U)
#define GMAC_SW_P0_TX_PRI_MAP_RESERVED_3_MASK                                                               (0x00000c00U)

#define GMAC_SW_P0_TX_PRI_MAP_RESERVED_4_SHIFT                                                              (14U)
#define GMAC_SW_P0_TX_PRI_MAP_RESERVED_4_MASK                                                               (0x0000c000U)

#define GMAC_SW_P1_TS_SEQ_MTYPE_P1_TS_MSG_TYPE_EN_SHIFT                                                     (0U)
#define GMAC_SW_P1_TS_SEQ_MTYPE_P1_TS_MSG_TYPE_EN_MASK                                                      (0x0000ffffU)

#define GMAC_SW_P1_TS_SEQ_MTYPE_P1_TS_SEQ_ID_OFFSET_SHIFT                                                   (16U)
#define GMAC_SW_P1_TS_SEQ_MTYPE_P1_TS_SEQ_ID_OFFSET_MASK                                                    (0x003f0000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI48_SHIFT                                                             (0U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI48_MASK                                                              (0x00000007U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI49_SHIFT                                                             (4U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI49_MASK                                                              (0x00000070U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI50_SHIFT                                                             (8U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI50_MASK                                                              (0x00000700U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI51_SHIFT                                                             (12U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI51_MASK                                                              (0x00007000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI52_SHIFT                                                             (16U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI52_MASK                                                              (0x00070000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI53_SHIFT                                                             (20U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI53_MASK                                                              (0x00700000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI54_SHIFT                                                             (24U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI54_MASK                                                              (0x07000000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI55_SHIFT                                                             (28U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_PRI55_MASK                                                              (0x70000000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_RESERVED_SHIFT                                                          (3U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_RESERVED_MASK                                                           (0x00000008U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_RESERVED_2_SHIFT                                                        (7U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_RESERVED_2_MASK                                                         (0x00000080U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_RESERVED_3_SHIFT                                                        (11U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_RESERVED_3_MASK                                                         (0x00000800U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_RESERVED_4_SHIFT                                                        (15U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP6_RESERVED_4_MASK                                                         (0x00008000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI0_SHIFT                                                              (0U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI0_MASK                                                               (0x00000007U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI1_SHIFT                                                              (4U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI1_MASK                                                               (0x00000070U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI2_SHIFT                                                              (8U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI2_MASK                                                               (0x00000700U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI3_SHIFT                                                              (12U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI3_MASK                                                               (0x00007000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI4_SHIFT                                                              (16U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI4_MASK                                                               (0x00070000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI5_SHIFT                                                              (20U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI5_MASK                                                               (0x00700000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI6_SHIFT                                                              (24U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI6_MASK                                                               (0x07000000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI7_SHIFT                                                              (28U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_PRI7_MASK                                                               (0x70000000U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_RESERVED_SHIFT                                                          (3U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_RESERVED_MASK                                                           (0x00000008U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_RESERVED_2_SHIFT                                                        (7U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_RESERVED_2_MASK                                                         (0x00000080U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_RESERVED_3_SHIFT                                                        (11U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_RESERVED_3_MASK                                                         (0x00000800U)

#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_RESERVED_4_SHIFT                                                        (15U)
#define GMAC_SW_P2_RX_DSCP_PRI_MAP0_RESERVED_4_MASK                                                         (0x00008000U)

#define GMAC_SW_P0_CONTROL_P0_DSCP_PRI_EN_SHIFT                                                             (16U)
#define GMAC_SW_P0_CONTROL_P0_DSCP_PRI_EN_MASK                                                              (0x00010000U)

#define GMAC_SW_P0_CONTROL_P0_VLAN_LTYPE1_EN_SHIFT                                                          (20U)
#define GMAC_SW_P0_CONTROL_P0_VLAN_LTYPE1_EN_MASK                                                           (0x00100000U)

#define GMAC_SW_P0_CONTROL_P0_VLAN_LTYPE2_EN_SHIFT                                                          (21U)
#define GMAC_SW_P0_CONTROL_P0_VLAN_LTYPE2_EN_MASK                                                           (0x00200000U)

#define GMAC_SW_P0_CONTROL_P0_PASS_PRI_TAGGED_SHIFT                                                         (24U)
#define GMAC_SW_P0_CONTROL_P0_PASS_PRI_TAGGED_MASK                                                          (0x01000000U)

#define GMAC_SW_P0_CONTROL_P0_DLR_CPDMA_CH_SHIFT                                                            (28U)
#define GMAC_SW_P0_CONTROL_P0_DLR_CPDMA_CH_MASK                                                             (0x70000000U)

#define GMAC_SW_P0_CONTROL_RESERVED_SHIFT                                                                   (0U)
#define GMAC_SW_P0_CONTROL_RESERVED_MASK                                                                    (0x0000ffffU)

#define GMAC_SW_P1_SEND_PERCENT_PRI1_SEND_PERCENT_SHIFT                                                     (0U)
#define GMAC_SW_P1_SEND_PERCENT_PRI1_SEND_PERCENT_MASK                                                      (0x0000007fU)

#define GMAC_SW_P1_SEND_PERCENT_PRI2_SEND_PERCENT_SHIFT                                                     (8U)
#define GMAC_SW_P1_SEND_PERCENT_PRI2_SEND_PERCENT_MASK                                                      (0x00007f00U)

#define GMAC_SW_P1_SEND_PERCENT_PRI3_SEND_PERCENT_SHIFT                                                     (16U)
#define GMAC_SW_P1_SEND_PERCENT_PRI3_SEND_PERCENT_MASK                                                      (0x007f0000U)

#define GMAC_SW_P1_SEND_PERCENT_RESERVED_SHIFT                                                              (7U)
#define GMAC_SW_P1_SEND_PERCENT_RESERVED_MASK                                                               (0x00000080U)

#define GMAC_SW_P1_SEND_PERCENT_RESERVED_2_SHIFT                                                            (15U)
#define GMAC_SW_P1_SEND_PERCENT_RESERVED_2_MASK                                                             (0x00008000U)

#define GMAC_SW_P1_BLK_CNT_P1_RX_BLK_CNT_SHIFT                                                              (0U)
#define GMAC_SW_P1_BLK_CNT_P1_RX_BLK_CNT_MASK                                                               (0x0000000fU)

#define GMAC_SW_P1_BLK_CNT_P1_TX_BLK_CNT_SHIFT                                                              (4U)
#define GMAC_SW_P1_BLK_CNT_P1_TX_BLK_CNT_MASK                                                               (0x000001f0U)

#define GMAC_SW_P1_BLK_CNT_RESERVED_SHIFT                                                                   (9U)
#define GMAC_SW_P1_BLK_CNT_RESERVED_MASK                                                                    (0x0000fe00U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI16_SHIFT                                                             (0U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI16_MASK                                                              (0x00000007U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI17_SHIFT                                                             (4U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI17_MASK                                                              (0x00000070U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI18_SHIFT                                                             (8U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI18_MASK                                                              (0x00000700U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI19_SHIFT                                                             (12U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI19_MASK                                                              (0x00007000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI20_SHIFT                                                             (16U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI20_MASK                                                              (0x00070000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI21_SHIFT                                                             (20U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI21_MASK                                                              (0x00700000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI22_SHIFT                                                             (24U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI22_MASK                                                              (0x07000000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI23_SHIFT                                                             (28U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_PRI23_MASK                                                              (0x70000000U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_RESERVED_SHIFT                                                          (3U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_RESERVED_MASK                                                           (0x00000008U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_RESERVED_2_SHIFT                                                        (7U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_RESERVED_2_MASK                                                         (0x00000080U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_RESERVED_3_SHIFT                                                        (11U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_RESERVED_3_MASK                                                         (0x00000800U)

#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_RESERVED_4_SHIFT                                                        (15U)
#define GMAC_SW_P0_RX_DSCP_PRI_MAP2_RESERVED_4_MASK                                                         (0x00008000U)

#define GMAC_SW_P2_PORT_VLAN_PORT_VID_SHIFT                                                                 (0U)
#define GMAC_SW_P2_PORT_VLAN_PORT_VID_MASK                                                                  (0x00000fffU)

#define GMAC_SW_P2_PORT_VLAN_PORT_CFI_SHIFT                                                                 (12U)
#define GMAC_SW_P2_PORT_VLAN_PORT_CFI_MASK                                                                  (0x00001000U)

#define GMAC_SW_P2_PORT_VLAN_PORT_PRI_SHIFT                                                                 (13U)
#define GMAC_SW_P2_PORT_VLAN_PORT_PRI_MASK                                                                  (0x0000e000U)

#define GMAC_SW_P1_PORT_VLAN_PORT_VID_SHIFT                                                                 (0U)
#define GMAC_SW_P1_PORT_VLAN_PORT_VID_MASK                                                                  (0x00000fffU)

#define GMAC_SW_P1_PORT_VLAN_PORT_CFI_SHIFT                                                                 (12U)
#define GMAC_SW_P1_PORT_VLAN_PORT_CFI_MASK                                                                  (0x00001000U)

#define GMAC_SW_P1_PORT_VLAN_PORT_PRI_SHIFT                                                                 (13U)
#define GMAC_SW_P1_PORT_VLAN_PORT_PRI_MASK                                                                  (0x0000e000U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_GMACSW_PORT_H_ */
