/******************************************************************************
*
* hw_gmacsw_ss.h - register-level header file for GMAC_SW
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
#ifndef HW_GMACSW_SS_H_
#define HW_GMACSW_SS_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define GMAC_SW_PTYPE                                                                                       (0x10U)
#define GMAC_SW_VLAN_LTYPE                                                                                  (0x28U)
#define GMAC_SW_STAT_PORT_EN                                                                                (0xcU)
#define GMAC_SW_CONTROL                                                                                     (0x4U)
#define GMAC_SW_SOFT_IDLE                                                                                   (0x14U)
#define GMAC_SW_ID_VER                                                                                      (0x0U)
#define GMAC_SW_TX_START_WDS                                                                                (0x20U)
#define GMAC_SW_SOFT_RESET                                                                                  (0x8U)
#define GMAC_SW_GAP_THRESH                                                                                  (0x1cU)
#define GMAC_SW_TS_LTYPE                                                                                    (0x2cU)
#define GMAC_SW_THRU_RATE                                                                                   (0x18U)
#define GMAC_SW_DLR_LTYPE                                                                                   (0x30U)
#define GMAC_SW_FLOW_CONTROL                                                                                (0x24U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define GMAC_SW_PTYPE_ESC_PRI_LD_VAL_SHIFT                                                                  (0U)
#define GMAC_SW_PTYPE_ESC_PRI_LD_VAL_MASK                                                                   (0x0000001fU)

#define GMAC_SW_PTYPE_P0_PTYPE_ESC_SHIFT                                                                    (8U)
#define GMAC_SW_PTYPE_P0_PTYPE_ESC_MASK                                                                     (0x00000100U)

#define GMAC_SW_PTYPE_P1_PTYPE_ESC_SHIFT                                                                    (9U)
#define GMAC_SW_PTYPE_P1_PTYPE_ESC_MASK                                                                     (0x00000200U)

#define GMAC_SW_PTYPE_P2_PTYPE_ESC_SHIFT                                                                    (10U)
#define GMAC_SW_PTYPE_P2_PTYPE_ESC_MASK                                                                     (0x00000400U)

#define GMAC_SW_PTYPE_P1_PRI1_SHAPE_EN_SHIFT                                                                (16U)
#define GMAC_SW_PTYPE_P1_PRI1_SHAPE_EN_MASK                                                                 (0x00010000U)

#define GMAC_SW_PTYPE_P1_PRI2_SHAPE_EN_SHIFT                                                                (17U)
#define GMAC_SW_PTYPE_P1_PRI2_SHAPE_EN_MASK                                                                 (0x00020000U)

#define GMAC_SW_PTYPE_P1_PRI3_SHAPE_EN_SHIFT                                                                (18U)
#define GMAC_SW_PTYPE_P1_PRI3_SHAPE_EN_MASK                                                                 (0x00040000U)

#define GMAC_SW_PTYPE_P2_PRI1_SHAPE_EN_SHIFT                                                                (19U)
#define GMAC_SW_PTYPE_P2_PRI1_SHAPE_EN_MASK                                                                 (0x00080000U)

#define GMAC_SW_PTYPE_P2_PRI2_SHAPE_EN_SHIFT                                                                (20U)
#define GMAC_SW_PTYPE_P2_PRI2_SHAPE_EN_MASK                                                                 (0x00100000U)

#define GMAC_SW_PTYPE_P2_PRI3_SHAPE_EN_SHIFT                                                                (21U)
#define GMAC_SW_PTYPE_P2_PRI3_SHAPE_EN_MASK                                                                 (0x00200000U)

#define GMAC_SW_PTYPE_RESERVED_SHIFT                                                                        (5U)
#define GMAC_SW_PTYPE_RESERVED_MASK                                                                         (0x000000e0U)

#define GMAC_SW_PTYPE_RESERVED_2_SHIFT                                                                      (11U)
#define GMAC_SW_PTYPE_RESERVED_2_MASK                                                                       (0x0000f800U)

#define GMAC_SW_PTYPE_RESERVED_3_SHIFT                                                                      (22U)
#define GMAC_SW_PTYPE_RESERVED_3_MASK                                                                       (0xffc00000U)

#define GMAC_SW_VLAN_LTYPE_VLAN_LTYPE1_SHIFT                                                                (0U)
#define GMAC_SW_VLAN_LTYPE_VLAN_LTYPE1_MASK                                                                 (0x0000ffffU)

#define GMAC_SW_VLAN_LTYPE_VLAN_LTYPE2_SHIFT                                                                (16U)
#define GMAC_SW_VLAN_LTYPE_VLAN_LTYPE2_MASK                                                                 (0xffff0000U)

#define GMAC_SW_STAT_PORT_EN_P0_STAT_EN_SHIFT                                                               (0U)
#define GMAC_SW_STAT_PORT_EN_P0_STAT_EN_MASK                                                                (0x00000001U)

#define GMAC_SW_STAT_PORT_EN_P1_STAT_EN_SHIFT                                                               (1U)
#define GMAC_SW_STAT_PORT_EN_P1_STAT_EN_MASK                                                                (0x00000002U)

#define GMAC_SW_STAT_PORT_EN_P2_STAT_EN_SHIFT                                                               (2U)
#define GMAC_SW_STAT_PORT_EN_P2_STAT_EN_MASK                                                                (0x00000004U)

#define GMAC_SW_STAT_PORT_EN_RESERVED_SHIFT                                                                 (3U)
#define GMAC_SW_STAT_PORT_EN_RESERVED_MASK                                                                  (0xfffffff8U)

#define GMAC_SW_CONTROL_FIFO_LOOPBACK_SHIFT                                                                 (0U)
#define GMAC_SW_CONTROL_FIFO_LOOPBACK_MASK                                                                  (0x00000001U)

#define GMAC_SW_CONTROL_VLAN_AWARE_SHIFT                                                                    (1U)
#define GMAC_SW_CONTROL_VLAN_AWARE_MASK                                                                     (0x00000002U)

#define GMAC_SW_CONTROL_RX_VLAN_ENCAP_SHIFT                                                                 (2U)
#define GMAC_SW_CONTROL_RX_VLAN_ENCAP_MASK                                                                  (0x00000004U)

#define GMAC_SW_CONTROL_DLR_EN_SHIFT                                                                        (3U)
#define GMAC_SW_CONTROL_DLR_EN_MASK                                                                         (0x00000008U)

#define GMAC_SW_CONTROL_RESERVED_SHIFT                                                                      (4U)
#define GMAC_SW_CONTROL_RESERVED_MASK                                                                       (0xfffffff0U)

#define GMAC_SW_SOFT_IDLE_SOFT_IDLE_SHIFT                                                                   (0U)
#define GMAC_SW_SOFT_IDLE_SOFT_IDLE_MASK                                                                    (0x00000001U)

#define GMAC_SW_SOFT_IDLE_RESERVED_SHIFT                                                                    (1U)
#define GMAC_SW_SOFT_IDLE_RESERVED_MASK                                                                     (0xfffffffeU)

#define GMAC_SW_ID_VER_CPSW_3G_MINOR_VER_SHIFT                                                              (0U)
#define GMAC_SW_ID_VER_CPSW_3G_MINOR_VER_MASK                                                               (0x000000ffU)

#define GMAC_SW_ID_VER_CPSW_3G_MAJ_VER_SHIFT                                                                (8U)
#define GMAC_SW_ID_VER_CPSW_3G_MAJ_VER_MASK                                                                 (0x00000700U)

#define GMAC_SW_ID_VER_CPSW_3G_RTL_VER_SHIFT                                                                (11U)
#define GMAC_SW_ID_VER_CPSW_3G_RTL_VER_MASK                                                                 (0x0000f800U)

#define GMAC_SW_ID_VER_CPSW_3G_IDENT_SHIFT                                                                  (16U)
#define GMAC_SW_ID_VER_CPSW_3G_IDENT_MASK                                                                   (0xffff0000U)

#define GMAC_SW_TX_START_WDS_TX_START_WDS_SHIFT                                                             (0U)
#define GMAC_SW_TX_START_WDS_TX_START_WDS_MASK                                                              (0x000007ffU)

#define GMAC_SW_TX_START_WDS_RESERVED_SHIFT                                                                 (11U)
#define GMAC_SW_TX_START_WDS_RESERVED_MASK                                                                  (0xfffff800U)

#define GMAC_SW_SOFT_RESET_SOFT_RESET_SHIFT                                                                 (0U)
#define GMAC_SW_SOFT_RESET_SOFT_RESET_MASK                                                                  (0x00000001U)

#define GMAC_SW_SOFT_RESET_RESERVED_SHIFT                                                                   (1U)
#define GMAC_SW_SOFT_RESET_RESERVED_MASK                                                                    (0xfffffffeU)

#define GMAC_SW_GAP_THRESH_GAP_THRESH_SHIFT                                                                 (0U)
#define GMAC_SW_GAP_THRESH_GAP_THRESH_MASK                                                                  (0x0000001fU)

#define GMAC_SW_GAP_THRESH_RESERVED_SHIFT                                                                   (5U)
#define GMAC_SW_GAP_THRESH_RESERVED_MASK                                                                    (0xffffffe0U)

#define GMAC_SW_TS_LTYPE_TS_LTYPE1_SHIFT                                                                    (0U)
#define GMAC_SW_TS_LTYPE_TS_LTYPE1_MASK                                                                     (0x0000ffffU)

#define GMAC_SW_TS_LTYPE_TS_LTYPE2_SHIFT                                                                    (16U)
#define GMAC_SW_TS_LTYPE_TS_LTYPE2_MASK                                                                     (0xffff0000U)

#define GMAC_SW_THRU_RATE_CPDMA_THRU_RATE_SHIFT                                                             (0U)
#define GMAC_SW_THRU_RATE_CPDMA_THRU_RATE_MASK                                                              (0x0000000fU)

#define GMAC_SW_THRU_RATE_SL_RX_THRU_RATE_SHIFT                                                             (12U)
#define GMAC_SW_THRU_RATE_SL_RX_THRU_RATE_MASK                                                              (0x0000f000U)

#define GMAC_SW_THRU_RATE_RESERVED_SHIFT                                                                    (4U)
#define GMAC_SW_THRU_RATE_RESERVED_MASK                                                                     (0x000000f0U)

#define GMAC_SW_DLR_LTYPE_DLR_LTYPE_SHIFT                                                                   (0U)
#define GMAC_SW_DLR_LTYPE_DLR_LTYPE_MASK                                                                    (0x0000ffffU)

#define GMAC_SW_FLOW_CONTROL_P0_FLOW_EN_SHIFT                                                               (0U)
#define GMAC_SW_FLOW_CONTROL_P0_FLOW_EN_MASK                                                                (0x00000001U)

#define GMAC_SW_FLOW_CONTROL_P1_FLOW_EN_SHIFT                                                               (1U)
#define GMAC_SW_FLOW_CONTROL_P1_FLOW_EN_MASK                                                                (0x00000002U)

#define GMAC_SW_FLOW_CONTROL_P2_FLOW_EN_SHIFT                                                               (2U)
#define GMAC_SW_FLOW_CONTROL_P2_FLOW_EN_MASK                                                                (0x00000004U)

#define GMAC_SW_FLOW_CONTROL_RESERVED_SHIFT                                                                 (3U)
#define GMAC_SW_FLOW_CONTROL_RESERVED_MASK                                                                  (0x0000fff8U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_GMACSW_SS_H_ */
