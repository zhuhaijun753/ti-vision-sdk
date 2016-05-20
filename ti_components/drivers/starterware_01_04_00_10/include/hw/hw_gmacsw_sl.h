/******************************************************************************
*
* hw_gmacsw_sl.h - register-level header file for GMAC_SW
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
#ifndef HW_GMACSW_SL_H_
#define HW_GMACSW_SL_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define GMAC_SW_RX_PAUSE                                                                                    (0x18U)
#define GMAC_SW_RX_MAXLEN                                                                                   (0x10U)
#define GMAC_SW_TX_GAP                                                                                      (0x28U)
#define GMAC_SW_TX_PAUSE                                                                                    (0x1cU)
#define GMAC_SW_IDVER                                                                                       (0x0U)
#define GMAC_SW_RX_PRI_MAP                                                                                  (0x24U)
#define GMAC_SW_EMCONTROL                                                                                   (0x20U)
#define GMAC_SW_MACSTATUS                                                                                   (0x8U)
#define GMAC_SW_SOFT_RESET                                                                                  (0xcU)
#define GMAC_SW_BOFFTEST                                                                                    (0x14U)
#define GMAC_SW_MACCONTROL                                                                                  (0x4U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define GMAC_SW_RX_PAUSE_RX_PAUSETIMER_SHIFT                                                                (0U)
#define GMAC_SW_RX_PAUSE_RX_PAUSETIMER_MASK                                                                 (0x0000ffffU)

#define GMAC_SW_RX_PAUSE_RESERVED1_SHIFT                                                                    (16U)
#define GMAC_SW_RX_PAUSE_RESERVED1_MASK                                                                     (0xffff0000U)

#define GMAC_SW_RX_MAXLEN_RX_MAXLEN_SHIFT                                                                   (0U)
#define GMAC_SW_RX_MAXLEN_RX_MAXLEN_MASK                                                                    (0x00003fffU)

#define GMAC_SW_RX_MAXLEN_RESERVED1_SHIFT                                                                   (14U)
#define GMAC_SW_RX_MAXLEN_RESERVED1_MASK                                                                    (0xffffc000U)

#define GMAC_SW_TX_GAP_TX_GAP_SHIFT                                                                         (0U)
#define GMAC_SW_TX_GAP_TX_GAP_MASK                                                                          (0x000001ffU)

#define GMAC_SW_TX_GAP_RESERVED1_SHIFT                                                                      (9U)
#define GMAC_SW_TX_GAP_RESERVED1_MASK                                                                       (0xfffffe00U)

#define GMAC_SW_TX_PAUSE_TX_PAUSETIMER_SHIFT                                                                (0U)
#define GMAC_SW_TX_PAUSE_TX_PAUSETIMER_MASK                                                                 (0x0000ffffU)

#define GMAC_SW_TX_PAUSE_RESERVED1_SHIFT                                                                    (16U)
#define GMAC_SW_TX_PAUSE_RESERVED1_MASK                                                                     (0xffff0000U)

#define GMAC_SW_IDVER_Y_SHIFT                                                                               (0U)
#define GMAC_SW_IDVER_Y_MASK                                                                                (0x000000ffU)

#define GMAC_SW_IDVER_X_SHIFT                                                                               (8U)
#define GMAC_SW_IDVER_X_MASK                                                                                (0x00000700U)

#define GMAC_SW_IDVER_Z_SHIFT                                                                               (11U)
#define GMAC_SW_IDVER_Z_MASK                                                                                (0x0000f800U)

#define GMAC_SW_IDVER_IDENT_SHIFT                                                                           (16U)
#define GMAC_SW_IDVER_IDENT_MASK                                                                            (0xffff0000U)

#define GMAC_SW_RX_PRI_MAP_PRI0_SHIFT                                                                       (0U)
#define GMAC_SW_RX_PRI_MAP_PRI0_MASK                                                                        (0x00000007U)

#define GMAC_SW_RX_PRI_MAP_RESERVED8_SHIFT                                                                  (3U)
#define GMAC_SW_RX_PRI_MAP_RESERVED8_MASK                                                                   (0x00000008U)

#define GMAC_SW_RX_PRI_MAP_PRI1_SHIFT                                                                       (4U)
#define GMAC_SW_RX_PRI_MAP_PRI1_MASK                                                                        (0x00000070U)

#define GMAC_SW_RX_PRI_MAP_RESERVED7_SHIFT                                                                  (7U)
#define GMAC_SW_RX_PRI_MAP_RESERVED7_MASK                                                                   (0x00000080U)

#define GMAC_SW_RX_PRI_MAP_PRI2_SHIFT                                                                       (8U)
#define GMAC_SW_RX_PRI_MAP_PRI2_MASK                                                                        (0x00000700U)

#define GMAC_SW_RX_PRI_MAP_RESERVED6_SHIFT                                                                  (11U)
#define GMAC_SW_RX_PRI_MAP_RESERVED6_MASK                                                                   (0x00000800U)

#define GMAC_SW_RX_PRI_MAP_PRI3_SHIFT                                                                       (12U)
#define GMAC_SW_RX_PRI_MAP_PRI3_MASK                                                                        (0x00007000U)

#define GMAC_SW_RX_PRI_MAP_RESERVED5_SHIFT                                                                  (15U)
#define GMAC_SW_RX_PRI_MAP_RESERVED5_MASK                                                                   (0x00008000U)

#define GMAC_SW_RX_PRI_MAP_PRI4_SHIFT                                                                       (16U)
#define GMAC_SW_RX_PRI_MAP_PRI4_MASK                                                                        (0x00070000U)

#define GMAC_SW_RX_PRI_MAP_RESERVED4_SHIFT                                                                  (19U)
#define GMAC_SW_RX_PRI_MAP_RESERVED4_MASK                                                                   (0x00080000U)

#define GMAC_SW_RX_PRI_MAP_PRI5_SHIFT                                                                       (20U)
#define GMAC_SW_RX_PRI_MAP_PRI5_MASK                                                                        (0x00700000U)

#define GMAC_SW_RX_PRI_MAP_RESERVED3_SHIFT                                                                  (23U)
#define GMAC_SW_RX_PRI_MAP_RESERVED3_MASK                                                                   (0x00800000U)

#define GMAC_SW_RX_PRI_MAP_PRI6_SHIFT                                                                       (24U)
#define GMAC_SW_RX_PRI_MAP_PRI6_MASK                                                                        (0x07000000U)

#define GMAC_SW_RX_PRI_MAP_RESERVED2_SHIFT                                                                  (27U)
#define GMAC_SW_RX_PRI_MAP_RESERVED2_MASK                                                                   (0x08000000U)

#define GMAC_SW_RX_PRI_MAP_PRI7_SHIFT                                                                       (28U)
#define GMAC_SW_RX_PRI_MAP_PRI7_MASK                                                                        (0x70000000U)

#define GMAC_SW_RX_PRI_MAP_RESERVED1_SHIFT                                                                  (31U)
#define GMAC_SW_RX_PRI_MAP_RESERVED1_MASK                                                                   (0x80000000U)

#define GMAC_SW_EMCONTROL_FREE_SHIFT                                                                        (0U)
#define GMAC_SW_EMCONTROL_FREE_MASK                                                                         (0x00000001U)

#define GMAC_SW_EMCONTROL_SOFT_SHIFT                                                                        (1U)
#define GMAC_SW_EMCONTROL_SOFT_MASK                                                                         (0x00000002U)

#define GMAC_SW_EMCONTROL_RESERVED1_SHIFT                                                                   (2U)
#define GMAC_SW_EMCONTROL_RESERVED1_MASK                                                                    (0xfffffffcU)

#define GMAC_SW_MACSTATUS_TX_FLOW_ACT_SHIFT                                                                 (0U)
#define GMAC_SW_MACSTATUS_TX_FLOW_ACT_MASK                                                                  (0x00000001U)

#define GMAC_SW_MACSTATUS_RX_FLOW_ACT_SHIFT                                                                 (1U)
#define GMAC_SW_MACSTATUS_RX_FLOW_ACT_MASK                                                                  (0x00000002U)

#define GMAC_SW_MACSTATUS_RESERVED2_SHIFT                                                                   (2U)
#define GMAC_SW_MACSTATUS_RESERVED2_MASK                                                                    (0x00000004U)

#define GMAC_SW_MACSTATUS_EXT_FULLDUPLEX_SHIFT                                                              (3U)
#define GMAC_SW_MACSTATUS_EXT_FULLDUPLEX_MASK                                                               (0x00000008U)

#define GMAC_SW_MACSTATUS_EXT_GIG_SHIFT                                                                     (4U)
#define GMAC_SW_MACSTATUS_EXT_GIG_MASK                                                                      (0x00000010U)

#define GMAC_SW_MACSTATUS_RESERVED1_SHIFT                                                                   (5U)
#define GMAC_SW_MACSTATUS_RESERVED1_MASK                                                                    (0x7fffffe0U)

#define GMAC_SW_MACSTATUS_IDLE_SHIFT                                                                        (31U)
#define GMAC_SW_MACSTATUS_IDLE_MASK                                                                         (0x80000000U)

#define GMAC_SW_SOFT_RESET_SOFT_RESET_SHIFT                                                                 (0U)
#define GMAC_SW_SOFT_RESET_SOFT_RESET_MASK                                                                  (0x00000001U)

#define GMAC_SW_SOFT_RESET_RESERVED1_SHIFT                                                                  (1U)
#define GMAC_SW_SOFT_RESET_RESERVED1_MASK                                                                   (0xfffffffeU)

#define GMAC_SW_BOFFTEST_TX_BACKOFF_SHIFT                                                                   (0U)
#define GMAC_SW_BOFFTEST_TX_BACKOFF_MASK                                                                    (0x000003ffU)

#define GMAC_SW_BOFFTEST_RESERVED2_SHIFT                                                                    (10U)
#define GMAC_SW_BOFFTEST_RESERVED2_MASK                                                                     (0x00000c00U)

#define GMAC_SW_BOFFTEST_COLL_COUNT_SHIFT                                                                   (12U)
#define GMAC_SW_BOFFTEST_COLL_COUNT_MASK                                                                    (0x0000f000U)

#define GMAC_SW_BOFFTEST_RNDNUM_SHIFT                                                                       (16U)
#define GMAC_SW_BOFFTEST_RNDNUM_MASK                                                                        (0x03ff0000U)

#define GMAC_SW_BOFFTEST_PACEVAL_SHIFT                                                                      (26U)
#define GMAC_SW_BOFFTEST_PACEVAL_MASK                                                                       (0x7c000000U)

#define GMAC_SW_BOFFTEST_RESERVED1_SHIFT                                                                    (31U)
#define GMAC_SW_BOFFTEST_RESERVED1_MASK                                                                     (0x80000000U)

#define GMAC_SW_MACCONTROL_FULLDUPLEX_SHIFT                                                                 (0U)
#define GMAC_SW_MACCONTROL_FULLDUPLEX_MASK                                                                  (0x00000001U)

#define GMAC_SW_MACCONTROL_LOOPBACK_SHIFT                                                                   (1U)
#define GMAC_SW_MACCONTROL_LOOPBACK_MASK                                                                    (0x00000002U)

#define GMAC_SW_MACCONTROL_MTEST_SHIFT                                                                      (2U)
#define GMAC_SW_MACCONTROL_MTEST_MASK                                                                       (0x00000004U)

#define GMAC_SW_MACCONTROL_RX_FLOW_EN_SHIFT                                                                 (3U)
#define GMAC_SW_MACCONTROL_RX_FLOW_EN_MASK                                                                  (0x00000008U)

#define GMAC_SW_MACCONTROL_TX_FLOW_EN_SHIFT                                                                 (4U)
#define GMAC_SW_MACCONTROL_TX_FLOW_EN_MASK                                                                  (0x00000010U)

#define GMAC_SW_MACCONTROL_GMII_EN_SHIFT                                                                    (5U)
#define GMAC_SW_MACCONTROL_GMII_EN_MASK                                                                     (0x00000020U)

#define GMAC_SW_MACCONTROL_TX_PACE_SHIFT                                                                    (6U)
#define GMAC_SW_MACCONTROL_TX_PACE_MASK                                                                     (0x00000040U)

#define GMAC_SW_MACCONTROL_GIG_SHIFT                                                                        (7U)
#define GMAC_SW_MACCONTROL_GIG_MASK                                                                         (0x00000080U)

#define GMAC_SW_MACCONTROL_RESERVED4_SHIFT                                                                  (8U)
#define GMAC_SW_MACCONTROL_RESERVED4_MASK                                                                   (0x00000300U)

#define GMAC_SW_MACCONTROL_TX_SHORT_GAP_EN_SHIFT                                                            (10U)
#define GMAC_SW_MACCONTROL_TX_SHORT_GAP_EN_MASK                                                             (0x00000400U)

#define GMAC_SW_MACCONTROL_CMD_IDLE_SHIFT                                                                   (11U)
#define GMAC_SW_MACCONTROL_CMD_IDLE_MASK                                                                    (0x00000800U)

#define GMAC_SW_MACCONTROL_RESERVED3_SHIFT                                                                  (12U)
#define GMAC_SW_MACCONTROL_RESERVED3_MASK                                                                   (0x00007000U)

#define GMAC_SW_MACCONTROL_IFCTL_A_SHIFT                                                                    (15U)
#define GMAC_SW_MACCONTROL_IFCTL_A_MASK                                                                     (0x00008000U)

#define GMAC_SW_MACCONTROL_IFCTL_B_SHIFT                                                                    (16U)
#define GMAC_SW_MACCONTROL_IFCTL_B_MASK                                                                     (0x00010000U)

#define GMAC_SW_MACCONTROL_GIG_FORCE_SHIFT                                                                  (17U)
#define GMAC_SW_MACCONTROL_GIG_FORCE_MASK                                                                   (0x00020000U)

#define GMAC_SW_MACCONTROL_EXT_EN_SHIFT                                                                     (18U)
#define GMAC_SW_MACCONTROL_EXT_EN_MASK                                                                      (0x00040000U)

#define GMAC_SW_MACCONTROL_RESERVED2_SHIFT                                                                  (19U)
#define GMAC_SW_MACCONTROL_RESERVED2_MASK                                                                   (0x00180000U)

#define GMAC_SW_MACCONTROL_TX_SHORT_GAP_LIM_EN_SHIFT                                                        (21U)
#define GMAC_SW_MACCONTROL_TX_SHORT_GAP_LIM_EN_MASK                                                         (0x00200000U)

#define GMAC_SW_MACCONTROL_RX_CEF_EN_SHIFT                                                                  (22U)
#define GMAC_SW_MACCONTROL_RX_CEF_EN_MASK                                                                   (0x00400000U)

#define GMAC_SW_MACCONTROL_RX_CSF_EN_SHIFT                                                                  (23U)
#define GMAC_SW_MACCONTROL_RX_CSF_EN_MASK                                                                   (0x00800000U)

#define GMAC_SW_MACCONTROL_RX_CMF_EN_SHIFT                                                                  (24U)
#define GMAC_SW_MACCONTROL_RX_CMF_EN_MASK                                                                   (0x01000000U)

#define GMAC_SW_MACCONTROL_RESERVED1_SHIFT                                                                  (25U)
#define GMAC_SW_MACCONTROL_RESERVED1_MASK                                                                   (0xfe000000U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_GMACSW_SL_H_ */
