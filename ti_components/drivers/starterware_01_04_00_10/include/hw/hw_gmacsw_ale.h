/******************************************************************************
*
* hw_gmacsw_ale.h - register-level header file for GMAC_SW
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
#ifndef HW_GMACSW_ALE_H_
#define HW_GMACSW_ALE_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define GMAC_SW_TBLW2                                                                                       (0x34U)
#define GMAC_SW_PORTCTL4                                                                                    (0x50U)
#define GMAC_SW_TBLCTL                                                                                      (0x20U)
#define GMAC_SW_UNKNOWN_VLAN                                                                                (0x18U)
#define GMAC_SW_PORTCTL1                                                                                    (0x44U)
#define GMAC_SW_TBLW1                                                                                       (0x38U)
#define GMAC_SW_IDVER                                                                                       (0x0U)
#define GMAC_SW_PORTCTL2                                                                                    (0x48U)
#define GMAC_SW_PRESCALE                                                                                    (0x10U)
#define GMAC_SW_PORTCTL0                                                                                    (0x40U)
#define GMAC_SW_CONTROL                                                                                     (0x8U)
#define GMAC_SW_TBLW0                                                                                       (0x3cU)
#define GMAC_SW_PORTCTL5                                                                                    (0x54U)
#define GMAC_SW_PORTCTL3                                                                                    (0x4cU)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define GMAC_SW_TBLW2_ENTRY71_64_SHIFT                                                                      (0U)
#define GMAC_SW_TBLW2_ENTRY71_64_MASK                                                                       (0x000000ffU)

#define GMAC_SW_PORTCTL4_PORT_STATE_SHIFT                                                                   (0U)
#define GMAC_SW_PORTCTL4_PORT_STATE_MASK                                                                    (0x00000003U)

#define GMAC_SW_PORTCTL4_DROP_UNTAGGED_SHIFT                                                                (2U)
#define GMAC_SW_PORTCTL4_DROP_UNTAGGED_MASK                                                                 (0x00000004U)

#define GMAC_SW_PORTCTL4_VID_INGRESS_CHECK_SHIFT                                                            (3U)
#define GMAC_SW_PORTCTL4_VID_INGRESS_CHECK_MASK                                                             (0x00000008U)

#define GMAC_SW_PORTCTL4_NO_LEARN_SHIFT                                                                     (4U)
#define GMAC_SW_PORTCTL4_NO_LEARN_MASK                                                                      (0x00000010U)

#define GMAC_SW_PORTCTL4_NO_SA_UPDATE_SHIFT                                                                 (5U)
#define GMAC_SW_PORTCTL4_NO_SA_UPDATE_MASK                                                                  (0x00000020U)

#define GMAC_SW_PORTCTL4_MCAST_LIMIT_SHIFT                                                                  (16U)
#define GMAC_SW_PORTCTL4_MCAST_LIMIT_MASK                                                                   (0x00ff0000U)

#define GMAC_SW_PORTCTL4_BCAST_LIMIT_SHIFT                                                                  (24U)
#define GMAC_SW_PORTCTL4_BCAST_LIMIT_MASK                                                                   (0xff000000U)

#define GMAC_SW_TBLCTL_ENTRY_POINTER_SHIFT                                                                  (0U)
#define GMAC_SW_TBLCTL_ENTRY_POINTER_MASK                                                                   (0x000003ffU)

#define GMAC_SW_TBLCTL_WRITE_RDZ_SHIFT                                                                      (31U)
#define GMAC_SW_TBLCTL_WRITE_RDZ_MASK                                                                       (0x80000000U)

#define GMAC_SW_UNKNOWN_VLAN_UNKNOWN_VLAN_MEMBER_LIST_SHIFT                                                 (0U)
#define GMAC_SW_UNKNOWN_VLAN_UNKNOWN_VLAN_MEMBER_LIST_MASK                                                  (0x0000003fU)

#define GMAC_SW_UNKNOWN_VLAN_UNKNOWN_MCAST_FLOOD_MASK_SHIFT                                                 (8U)
#define GMAC_SW_UNKNOWN_VLAN_UNKNOWN_MCAST_FLOOD_MASK_MASK                                                  (0x00003f00U)

#define GMAC_SW_UNKNOWN_VLAN_UNKNOWN_REG_MCAST_FLOOD_MASK_SHIFT                                             (16U)
#define GMAC_SW_UNKNOWN_VLAN_UNKNOWN_REG_MCAST_FLOOD_MASK_MASK                                              (0x003f0000U)

#define GMAC_SW_UNKNOWN_VLAN_UNKNOWN_FORCE_UNTAGGED_EGRESS_SHIFT                                            (24U)
#define GMAC_SW_UNKNOWN_VLAN_UNKNOWN_FORCE_UNTAGGED_EGRESS_MASK                                             (0x3f000000U)

#define GMAC_SW_PORTCTL1_PORT_STATE_SHIFT                                                                   (0U)
#define GMAC_SW_PORTCTL1_PORT_STATE_MASK                                                                    (0x00000003U)

#define GMAC_SW_PORTCTL1_DROP_UNTAGGED_SHIFT                                                                (2U)
#define GMAC_SW_PORTCTL1_DROP_UNTAGGED_MASK                                                                 (0x00000004U)

#define GMAC_SW_PORTCTL1_VID_INGRESS_CHECK_SHIFT                                                            (3U)
#define GMAC_SW_PORTCTL1_VID_INGRESS_CHECK_MASK                                                             (0x00000008U)

#define GMAC_SW_PORTCTL1_NO_LEARN_SHIFT                                                                     (4U)
#define GMAC_SW_PORTCTL1_NO_LEARN_MASK                                                                      (0x00000010U)

#define GMAC_SW_PORTCTL1_NO_SA_UPDATE_SHIFT                                                                 (5U)
#define GMAC_SW_PORTCTL1_NO_SA_UPDATE_MASK                                                                  (0x00000020U)

#define GMAC_SW_PORTCTL1_MCAST_LIMIT_SHIFT                                                                  (16U)
#define GMAC_SW_PORTCTL1_MCAST_LIMIT_MASK                                                                   (0x00ff0000U)

#define GMAC_SW_PORTCTL1_BCAST_LIMIT_SHIFT                                                                  (24U)
#define GMAC_SW_PORTCTL1_BCAST_LIMIT_MASK                                                                   (0xff000000U)

#define GMAC_SW_TBLW1_ENTRY63_32_SHIFT                                                                      (0U)
#define GMAC_SW_TBLW1_ENTRY63_32_MASK                                                                       (0xffffffffU)

#define GMAC_SW_IDVER_MINOR_VER_SHIFT                                                                       (0U)
#define GMAC_SW_IDVER_MINOR_VER_MASK                                                                        (0x000000ffU)

#define GMAC_SW_IDVER_MAJ_VER_SHIFT                                                                         (8U)
#define GMAC_SW_IDVER_MAJ_VER_MASK                                                                          (0x0000ff00U)

#define GMAC_SW_IDVER_IDENT_SHIFT                                                                           (16U)
#define GMAC_SW_IDVER_IDENT_MASK                                                                            (0xffff0000U)

#define GMAC_SW_PORTCTL2_PORT_STATE_SHIFT                                                                   (0U)
#define GMAC_SW_PORTCTL2_PORT_STATE_MASK                                                                    (0x00000003U)

#define GMAC_SW_PORTCTL2_DROP_UNTAGGED_SHIFT                                                                (2U)
#define GMAC_SW_PORTCTL2_DROP_UNTAGGED_MASK                                                                 (0x00000004U)

#define GMAC_SW_PORTCTL2_VID_INGRESS_CHECK_SHIFT                                                            (3U)
#define GMAC_SW_PORTCTL2_VID_INGRESS_CHECK_MASK                                                             (0x00000008U)

#define GMAC_SW_PORTCTL2_NO_LEARN_SHIFT                                                                     (4U)
#define GMAC_SW_PORTCTL2_NO_LEARN_MASK                                                                      (0x00000010U)

#define GMAC_SW_PORTCTL2_NO_SA_UPDATE_SHIFT                                                                 (5U)
#define GMAC_SW_PORTCTL2_NO_SA_UPDATE_MASK                                                                  (0x00000020U)

#define GMAC_SW_PORTCTL2_MCAST_LIMIT_SHIFT                                                                  (16U)
#define GMAC_SW_PORTCTL2_MCAST_LIMIT_MASK                                                                   (0x00ff0000U)

#define GMAC_SW_PORTCTL2_BCAST_LIMIT_SHIFT                                                                  (24U)
#define GMAC_SW_PORTCTL2_BCAST_LIMIT_MASK                                                                   (0xff000000U)

#define GMAC_SW_PRESCALE_PRESCALE_SHIFT                                                                     (0U)
#define GMAC_SW_PRESCALE_PRESCALE_MASK                                                                      (0x000fffffU)

#define GMAC_SW_PORTCTL0_PORT_STATE_SHIFT                                                                   (0U)
#define GMAC_SW_PORTCTL0_PORT_STATE_MASK                                                                    (0x00000003U)

#define GMAC_SW_PORTCTL0_DROP_UNTAGGED_SHIFT                                                                (2U)
#define GMAC_SW_PORTCTL0_DROP_UNTAGGED_MASK                                                                 (0x00000004U)

#define GMAC_SW_PORTCTL0_VID_INGRESS_CHECK_SHIFT                                                            (3U)
#define GMAC_SW_PORTCTL0_VID_INGRESS_CHECK_MASK                                                             (0x00000008U)

#define GMAC_SW_PORTCTL0_NO_LEARN_SHIFT                                                                     (4U)
#define GMAC_SW_PORTCTL0_NO_LEARN_MASK                                                                      (0x00000010U)

#define GMAC_SW_PORTCTL0_NO_SA_UPDATE_SHIFT                                                                 (5U)
#define GMAC_SW_PORTCTL0_NO_SA_UPDATE_MASK                                                                  (0x00000020U)

#define GMAC_SW_PORTCTL0_MCAST_LIMIT_SHIFT                                                                  (16U)
#define GMAC_SW_PORTCTL0_MCAST_LIMIT_MASK                                                                   (0x00ff0000U)

#define GMAC_SW_PORTCTL0_BCAST_LIMIT_SHIFT                                                                  (24U)
#define GMAC_SW_PORTCTL0_BCAST_LIMIT_MASK                                                                   (0xff000000U)

#define GMAC_SW_CONTROL_ENABLE_RATE_LIMIT_SHIFT                                                             (0U)
#define GMAC_SW_CONTROL_ENABLE_RATE_LIMIT_MASK                                                              (0x00000001U)

#define GMAC_SW_CONTROL_ENABLE_AUTH_MODE_SHIFT                                                              (1U)
#define GMAC_SW_CONTROL_ENABLE_AUTH_MODE_MASK                                                               (0x00000002U)

#define GMAC_SW_CONTROL_VLAN_AWARE_SHIFT                                                                    (2U)
#define GMAC_SW_CONTROL_VLAN_AWARE_MASK                                                                     (0x00000004U)

#define GMAC_SW_CONTROL_RATE_LIMIT_TX_SHIFT                                                                 (3U)
#define GMAC_SW_CONTROL_RATE_LIMIT_TX_MASK                                                                  (0x00000008U)

#define GMAC_SW_CONTROL_BYPASS_SHIFT                                                                        (4U)
#define GMAC_SW_CONTROL_BYPASS_MASK                                                                         (0x00000010U)

#define GMAC_SW_CONTROL_ENABLE_OUI_DENY_SHIFT                                                               (5U)
#define GMAC_SW_CONTROL_ENABLE_OUI_DENY_MASK                                                                (0x00000020U)

#define GMAC_SW_CONTROL_EN_VID0_MODE_SHIFT                                                                  (6U)
#define GMAC_SW_CONTROL_EN_VID0_MODE_MASK                                                                   (0x00000040U)

#define GMAC_SW_CONTROL_LEARN_NO_VID_SHIFT                                                                  (7U)
#define GMAC_SW_CONTROL_LEARN_NO_VID_MASK                                                                   (0x00000080U)

#define GMAC_SW_CONTROL_EN_P0_UNI_FLOOD_SHIFT                                                               (8U)
#define GMAC_SW_CONTROL_EN_P0_UNI_FLOOD_MASK                                                                (0x00000100U)

#define GMAC_SW_CONTROL_AGE_OUT_NOW_SHIFT                                                                   (29U)
#define GMAC_SW_CONTROL_AGE_OUT_NOW_MASK                                                                    (0x20000000U)

#define GMAC_SW_CONTROL_CLEAR_TABLE_SHIFT                                                                   (30U)
#define GMAC_SW_CONTROL_CLEAR_TABLE_MASK                                                                    (0x40000000U)

#define GMAC_SW_CONTROL_ENABLE_ALE_SHIFT                                                                    (31U)
#define GMAC_SW_CONTROL_ENABLE_ALE_MASK                                                                     (0x80000000U)

#define GMAC_SW_TBLW0_ENTRY31_0_SHIFT                                                                       (0U)
#define GMAC_SW_TBLW0_ENTRY31_0_MASK                                                                        (0xffffffffU)

#define GMAC_SW_PORTCTL5_PORT_STATE_SHIFT                                                                   (0U)
#define GMAC_SW_PORTCTL5_PORT_STATE_MASK                                                                    (0x00000003U)

#define GMAC_SW_PORTCTL5_DROP_UNTAGGED_SHIFT                                                                (2U)
#define GMAC_SW_PORTCTL5_DROP_UNTAGGED_MASK                                                                 (0x00000004U)

#define GMAC_SW_PORTCTL5_VID_INGRESS_CHECK_SHIFT                                                            (3U)
#define GMAC_SW_PORTCTL5_VID_INGRESS_CHECK_MASK                                                             (0x00000008U)

#define GMAC_SW_PORTCTL5_NO_LEARN_SHIFT                                                                     (4U)
#define GMAC_SW_PORTCTL5_NO_LEARN_MASK                                                                      (0x00000010U)

#define GMAC_SW_PORTCTL5_NO_SA_UPDATE_SHIFT                                                                 (5U)
#define GMAC_SW_PORTCTL5_NO_SA_UPDATE_MASK                                                                  (0x00000020U)

#define GMAC_SW_PORTCTL5_MCAST_LIMIT_SHIFT                                                                  (16U)
#define GMAC_SW_PORTCTL5_MCAST_LIMIT_MASK                                                                   (0x00ff0000U)

#define GMAC_SW_PORTCTL5_BCAST_LIMIT_SHIFT                                                                  (24U)
#define GMAC_SW_PORTCTL5_BCAST_LIMIT_MASK                                                                   (0xff000000U)

#define GMAC_SW_PORTCTL3_PORT_STATE_SHIFT                                                                   (0U)
#define GMAC_SW_PORTCTL3_PORT_STATE_MASK                                                                    (0x00000003U)

#define GMAC_SW_PORTCTL3_DROP_UNTAGGED_SHIFT                                                                (2U)
#define GMAC_SW_PORTCTL3_DROP_UNTAGGED_MASK                                                                 (0x00000004U)

#define GMAC_SW_PORTCTL3_VID_INGRESS_CHECK_SHIFT                                                            (3U)
#define GMAC_SW_PORTCTL3_VID_INGRESS_CHECK_MASK                                                             (0x00000008U)

#define GMAC_SW_PORTCTL3_NO_LEARN_SHIFT                                                                     (4U)
#define GMAC_SW_PORTCTL3_NO_LEARN_MASK                                                                      (0x00000010U)

#define GMAC_SW_PORTCTL3_NO_SA_UPDATE_SHIFT                                                                 (5U)
#define GMAC_SW_PORTCTL3_NO_SA_UPDATE_MASK                                                                  (0x00000020U)

#define GMAC_SW_PORTCTL3_MCAST_LIMIT_SHIFT                                                                  (16U)
#define GMAC_SW_PORTCTL3_MCAST_LIMIT_MASK                                                                   (0x00ff0000U)

#define GMAC_SW_PORTCTL3_BCAST_LIMIT_SHIFT                                                                  (24U)
#define GMAC_SW_PORTCTL3_BCAST_LIMIT_MASK                                                                   (0xff000000U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_GMACSW_ALE_H_ */
