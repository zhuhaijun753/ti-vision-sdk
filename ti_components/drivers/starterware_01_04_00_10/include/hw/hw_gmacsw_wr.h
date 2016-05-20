/******************************************************************************
*
* hw_gmacsw_wr.h - register-level header file for GMAC_SW
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
#ifndef HW_GMACSW_WR_H_
#define HW_GMACSW_WR_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define GMAC_SW_C1_RX_THRESH_STAT                                                                           (0x50U)
#define GMAC_SW_C0_RX_STAT                                                                                  (0x44U)
#define GMAC_SW_C0_RX_THRESH_STAT                                                                           (0x40U)
#define GMAC_SW_C1_MISC_EN                                                                                  (0x2cU)
#define GMAC_SW_C2_RX_THRESH_EN                                                                             (0x30U)
#define GMAC_SW_C2_MISC_STAT                                                                                (0x6cU)
#define GMAC_SW_C0_RX_EN                                                                                    (0x14U)
#define GMAC_SW_C2_RX_IMAX                                                                                  (0x80U)
#define GMAC_SW_C1_TX_STAT                                                                                  (0x58U)
#define GMAC_SW_C1_RX_STAT                                                                                  (0x54U)
#define GMAC_SW_C0_RX_THRESH_EN                                                                             (0x10U)
#define GMAC_SW_C1_RX_EN                                                                                    (0x24U)
#define GMAC_SW_C1_TX_EN                                                                                    (0x28U)
#define GMAC_SW_C0_RX_IMAX                                                                                  (0x70U)
#define GMAC_SW_C2_RX_EN                                                                                    (0x34U)
#define GMAC_SW_C1_RX_IMAX                                                                                  (0x78U)
#define GMAC_SW_C0_MISC_EN                                                                                  (0x1cU)
#define GMAC_SW_CONTROL                                                                                     (0x8U)
#define GMAC_SW_SOFT_RESET                                                                                  (0x4U)
#define GMAC_SW_C0_TX_STAT                                                                                  (0x48U)
#define GMAC_SW_C2_RX_STAT                                                                                  (0x64U)
#define GMAC_SW_C2_MISC_EN                                                                                  (0x3cU)
#define GMAC_SW_IDVER                                                                                       (0x0U)
#define GMAC_SW_C2_TX_IMAX                                                                                  (0x84U)
#define GMAC_SW_C1_TX_IMAX                                                                                  (0x7cU)
#define GMAC_SW_RGMII_CTL                                                                                   (0x88U)
#define GMAC_SW_C1_RX_THRESH_EN                                                                             (0x20U)
#define GMAC_SW_C1_MISC_STAT                                                                                (0x5cU)
#define GMAC_SW_C0_TX_EN                                                                                    (0x18U)
#define GMAC_SW_C2_TX_EN                                                                                    (0x38U)
#define GMAC_SW_C0_MISC_STAT                                                                                (0x4cU)
#define GMAC_SW_C2_RX_THRESH_STAT                                                                           (0x60U)
#define GMAC_SW_C0_TX_IMAX                                                                                  (0x74U)
#define GMAC_SW_C2_TX_STAT                                                                                  (0x68U)
#define GMAC_SW_INT_CONTROL                                                                                 (0xcU)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define GMAC_SW_C1_RX_THRESH_STAT_C1_RX_THRESH_STAT_SHIFT                                                   (0U)
#define GMAC_SW_C1_RX_THRESH_STAT_C1_RX_THRESH_STAT_MASK                                                    (0x000000ffU)

#define GMAC_SW_C1_RX_THRESH_STAT_RESERVED1_SHIFT                                                           (8U)
#define GMAC_SW_C1_RX_THRESH_STAT_RESERVED1_MASK                                                            (0xffffff00U)

#define GMAC_SW_C0_RX_STAT_C0_RX_STAT_SHIFT                                                                 (0U)
#define GMAC_SW_C0_RX_STAT_C0_RX_STAT_MASK                                                                  (0x000000ffU)

#define GMAC_SW_C0_RX_STAT_RESERVED1_SHIFT                                                                  (8U)
#define GMAC_SW_C0_RX_STAT_RESERVED1_MASK                                                                   (0xffffff00U)

#define GMAC_SW_C0_RX_THRESH_STAT_C0_RX_THRESH_STAT_SHIFT                                                   (0U)
#define GMAC_SW_C0_RX_THRESH_STAT_C0_RX_THRESH_STAT_MASK                                                    (0x000000ffU)

#define GMAC_SW_C0_RX_THRESH_STAT_RESERVED1_SHIFT                                                           (8U)
#define GMAC_SW_C0_RX_THRESH_STAT_RESERVED1_MASK                                                            (0xffffff00U)

#define GMAC_SW_C1_MISC_EN_C1_MISC_EN_SHIFT                                                                 (0U)
#define GMAC_SW_C1_MISC_EN_C1_MISC_EN_MASK                                                                  (0x0000001fU)

#define GMAC_SW_C1_MISC_EN_RESERVED1_SHIFT                                                                  (5U)
#define GMAC_SW_C1_MISC_EN_RESERVED1_MASK                                                                   (0xffffffe0U)

#define GMAC_SW_C2_RX_THRESH_EN_C2_RX_THRESH_EN_SHIFT                                                       (0U)
#define GMAC_SW_C2_RX_THRESH_EN_C2_RX_THRESH_EN_MASK                                                        (0x000000ffU)

#define GMAC_SW_C2_RX_THRESH_EN_RESERVED1_SHIFT                                                             (8U)
#define GMAC_SW_C2_RX_THRESH_EN_RESERVED1_MASK                                                              (0xffffff00U)

#define GMAC_SW_C2_MISC_STAT_C2_MISC_STAT_SHIFT                                                             (0U)
#define GMAC_SW_C2_MISC_STAT_C2_MISC_STAT_MASK                                                              (0x0000001fU)

#define GMAC_SW_C2_MISC_STAT_RESERVED1_SHIFT                                                                (5U)
#define GMAC_SW_C2_MISC_STAT_RESERVED1_MASK                                                                 (0xffffffe0U)

#define GMAC_SW_C0_RX_EN_C0_RX_EN_SHIFT                                                                     (0U)
#define GMAC_SW_C0_RX_EN_C0_RX_EN_MASK                                                                      (0x000000ffU)

#define GMAC_SW_C0_RX_EN_RESERVED1_SHIFT                                                                    (8U)
#define GMAC_SW_C0_RX_EN_RESERVED1_MASK                                                                     (0xffffff00U)

#define GMAC_SW_C2_RX_IMAX_C2_RX_IMAX_SHIFT                                                                 (0U)
#define GMAC_SW_C2_RX_IMAX_C2_RX_IMAX_MASK                                                                  (0x0000003fU)

#define GMAC_SW_C2_RX_IMAX_RESERVED1_SHIFT                                                                  (6U)
#define GMAC_SW_C2_RX_IMAX_RESERVED1_MASK                                                                   (0xffffffc0U)

#define GMAC_SW_C1_TX_STAT_C1_TX_STAT_SHIFT                                                                 (0U)
#define GMAC_SW_C1_TX_STAT_C1_TX_STAT_MASK                                                                  (0x000000ffU)

#define GMAC_SW_C1_TX_STAT_RESERVED1_SHIFT                                                                  (8U)
#define GMAC_SW_C1_TX_STAT_RESERVED1_MASK                                                                   (0xffffff00U)

#define GMAC_SW_C1_RX_STAT_C1_RX_STAT_SHIFT                                                                 (0U)
#define GMAC_SW_C1_RX_STAT_C1_RX_STAT_MASK                                                                  (0x000000ffU)

#define GMAC_SW_C1_RX_STAT_RESERVED1_SHIFT                                                                  (8U)
#define GMAC_SW_C1_RX_STAT_RESERVED1_MASK                                                                   (0xffffff00U)

#define GMAC_SW_C0_RX_THRESH_EN_C0_RX_THRESH_EN_SHIFT                                                       (0U)
#define GMAC_SW_C0_RX_THRESH_EN_C0_RX_THRESH_EN_MASK                                                        (0x000000ffU)

#define GMAC_SW_C0_RX_THRESH_EN_RESERVED1_SHIFT                                                             (8U)
#define GMAC_SW_C0_RX_THRESH_EN_RESERVED1_MASK                                                              (0xffffff00U)

#define GMAC_SW_C1_RX_EN_C1_RX_EN_SHIFT                                                                     (0U)
#define GMAC_SW_C1_RX_EN_C1_RX_EN_MASK                                                                      (0x000000ffU)

#define GMAC_SW_C1_RX_EN_RESERVED1_SHIFT                                                                    (8U)
#define GMAC_SW_C1_RX_EN_RESERVED1_MASK                                                                     (0xffffff00U)

#define GMAC_SW_C1_TX_EN_C1_TX_EN_SHIFT                                                                     (0U)
#define GMAC_SW_C1_TX_EN_C1_TX_EN_MASK                                                                      (0x000000ffU)

#define GMAC_SW_C1_TX_EN_RESERVED1_SHIFT                                                                    (8U)
#define GMAC_SW_C1_TX_EN_RESERVED1_MASK                                                                     (0xffffff00U)

#define GMAC_SW_C0_RX_IMAX_C0_RX_IMAX_SHIFT                                                                 (0U)
#define GMAC_SW_C0_RX_IMAX_C0_RX_IMAX_MASK                                                                  (0x0000003fU)

#define GMAC_SW_C0_RX_IMAX_RESERVED1_SHIFT                                                                  (6U)
#define GMAC_SW_C0_RX_IMAX_RESERVED1_MASK                                                                   (0xffffffc0U)

#define GMAC_SW_C2_RX_EN_C2_RX_EN_SHIFT                                                                     (0U)
#define GMAC_SW_C2_RX_EN_C2_RX_EN_MASK                                                                      (0x000000ffU)

#define GMAC_SW_C2_RX_EN_RESERVED1_SHIFT                                                                    (8U)
#define GMAC_SW_C2_RX_EN_RESERVED1_MASK                                                                     (0xffffff00U)

#define GMAC_SW_C1_RX_IMAX_C1_RX_IMAX_SHIFT                                                                 (0U)
#define GMAC_SW_C1_RX_IMAX_C1_RX_IMAX_MASK                                                                  (0x0000003fU)

#define GMAC_SW_C1_RX_IMAX_RESERVED1_SHIFT                                                                  (6U)
#define GMAC_SW_C1_RX_IMAX_RESERVED1_MASK                                                                   (0xffffffc0U)

#define GMAC_SW_C0_MISC_EN_C0_MISC_EN_SHIFT                                                                 (0U)
#define GMAC_SW_C0_MISC_EN_C0_MISC_EN_MASK                                                                  (0x0000001fU)

#define GMAC_SW_C0_MISC_EN_RESERVED1_SHIFT                                                                  (5U)
#define GMAC_SW_C0_MISC_EN_RESERVED1_MASK                                                                   (0xffffffe0U)

#define GMAC_SW_CONTROL_MMR_IDLEMODE_SHIFT                                                                  (0U)
#define GMAC_SW_CONTROL_MMR_IDLEMODE_MASK                                                                   (0x00000003U)
#define GMAC_SW_CONTROL_MMR_IDLEMODE_EN_0X1                                                                  (1U)
#define GMAC_SW_CONTROL_MMR_IDLEMODE_EN_0X2                                                                  (2U)
#define GMAC_SW_CONTROL_MMR_IDLEMODE_EN_0X3                                                                  (3U)
#define GMAC_SW_CONTROL_MMR_IDLEMODE_EN_0X0                                                                  (0U)

#define GMAC_SW_CONTROL_MMR_STDBYMODE_SHIFT                                                                 (2U)
#define GMAC_SW_CONTROL_MMR_STDBYMODE_MASK                                                                  (0x0000000cU)
#define GMAC_SW_CONTROL_MMR_STDBYMODE_EN_0X0                                                                 (0U)
#define GMAC_SW_CONTROL_MMR_STDBYMODE_EN_0X2                                                                 (2U)
#define GMAC_SW_CONTROL_MMR_STDBYMODE_EN_0X3                                                                 (3U)
#define GMAC_SW_CONTROL_MMR_STDBYMODE_EN_0X1                                                                 (1U)

#define GMAC_SW_CONTROL_RESERVED1_SHIFT                                                                     (4U)
#define GMAC_SW_CONTROL_RESERVED1_MASK                                                                      (0xfffffff0U)

#define GMAC_SW_SOFT_RESET_SOFT_RESET_SHIFT                                                                 (0U)
#define GMAC_SW_SOFT_RESET_SOFT_RESET_MASK                                                                  (0x00000001U)

#define GMAC_SW_SOFT_RESET_RESERVED1_SHIFT                                                                  (1U)
#define GMAC_SW_SOFT_RESET_RESERVED1_MASK                                                                   (0xfffffffeU)

#define GMAC_SW_C0_TX_STAT_C0_TX_STAT_SHIFT                                                                 (0U)
#define GMAC_SW_C0_TX_STAT_C0_TX_STAT_MASK                                                                  (0x000000ffU)

#define GMAC_SW_C0_TX_STAT_RESERVED1_SHIFT                                                                  (8U)
#define GMAC_SW_C0_TX_STAT_RESERVED1_MASK                                                                   (0xffffff00U)

#define GMAC_SW_C2_RX_STAT_C2_RX_STAT_SHIFT                                                                 (0U)
#define GMAC_SW_C2_RX_STAT_C2_RX_STAT_MASK                                                                  (0x000000ffU)

#define GMAC_SW_C2_RX_STAT_RESERVED1_SHIFT                                                                  (8U)
#define GMAC_SW_C2_RX_STAT_RESERVED1_MASK                                                                   (0xffffff00U)

#define GMAC_SW_C2_MISC_EN_C2_MISC_EN_SHIFT                                                                 (0U)
#define GMAC_SW_C2_MISC_EN_C2_MISC_EN_MASK                                                                  (0x0000001fU)

#define GMAC_SW_C2_MISC_EN_RESERVED1_SHIFT                                                                  (5U)
#define GMAC_SW_C2_MISC_EN_RESERVED1_MASK                                                                   (0xffffffe0U)

#define GMAC_SW_IDVER_MINOR_SHIFT                                                                           (0U)
#define GMAC_SW_IDVER_MINOR_MASK                                                                            (0x0000003fU)

#define GMAC_SW_IDVER_CUSTOM_SHIFT                                                                          (6U)
#define GMAC_SW_IDVER_CUSTOM_MASK                                                                           (0x000000c0U)

#define GMAC_SW_IDVER_MAJOR_SHIFT                                                                           (8U)
#define GMAC_SW_IDVER_MAJOR_MASK                                                                            (0x00000700U)

#define GMAC_SW_IDVER_RTL_SHIFT                                                                             (11U)
#define GMAC_SW_IDVER_RTL_MASK                                                                              (0x0000f800U)

#define GMAC_SW_IDVER_FUNCTION_SHIFT                                                                        (16U)
#define GMAC_SW_IDVER_FUNCTION_MASK                                                                         (0x0fff0000U)

#define GMAC_SW_IDVER_RESERVED1_SHIFT                                                                       (28U)
#define GMAC_SW_IDVER_RESERVED1_MASK                                                                        (0x30000000U)

#define GMAC_SW_IDVER_SCHEME_SHIFT                                                                          (30U)
#define GMAC_SW_IDVER_SCHEME_MASK                                                                           (0xc0000000U)

#define GMAC_SW_C2_TX_IMAX_C2_TX_IMAX_SHIFT                                                                 (0U)
#define GMAC_SW_C2_TX_IMAX_C2_TX_IMAX_MASK                                                                  (0x0000003fU)

#define GMAC_SW_C2_TX_IMAX_RESERVED1_SHIFT                                                                  (6U)
#define GMAC_SW_C2_TX_IMAX_RESERVED1_MASK                                                                   (0xffffffc0U)

#define GMAC_SW_C1_TX_IMAX_C1_TX_IMAX_SHIFT                                                                 (0U)
#define GMAC_SW_C1_TX_IMAX_C1_TX_IMAX_MASK                                                                  (0x0000003fU)

#define GMAC_SW_C1_TX_IMAX_RESERVED1_SHIFT                                                                  (6U)
#define GMAC_SW_C1_TX_IMAX_RESERVED1_MASK                                                                   (0xffffffc0U)

#define GMAC_SW_RGMII_CTL_RGMII1_LINK_SHIFT                                                                 (0U)
#define GMAC_SW_RGMII_CTL_RGMII1_LINK_MASK                                                                  (0x00000001U)

#define GMAC_SW_RGMII_CTL_RGMII1_SPEED_SHIFT                                                                (1U)
#define GMAC_SW_RGMII_CTL_RGMII1_SPEED_MASK                                                                 (0x00000006U)

#define GMAC_SW_RGMII_CTL_RGMII1_FULLDUPLEX_SHIFT                                                           (3U)
#define GMAC_SW_RGMII_CTL_RGMII1_FULLDUPLEX_MASK                                                            (0x00000008U)

#define GMAC_SW_RGMII_CTL_RGMII2_LINK_SHIFT                                                                 (4U)
#define GMAC_SW_RGMII_CTL_RGMII2_LINK_MASK                                                                  (0x00000010U)

#define GMAC_SW_RGMII_CTL_RGMII2_SPEED_SHIFT                                                                (5U)
#define GMAC_SW_RGMII_CTL_RGMII2_SPEED_MASK                                                                 (0x00000060U)

#define GMAC_SW_RGMII_CTL_RGMII2_FULLDUPLEX_SHIFT                                                           (7U)
#define GMAC_SW_RGMII_CTL_RGMII2_FULLDUPLEX_MASK                                                            (0x00000080U)

#define GMAC_SW_RGMII_CTL_RESERVED1_SHIFT                                                                   (8U)
#define GMAC_SW_RGMII_CTL_RESERVED1_MASK                                                                    (0xffffff00U)

#define GMAC_SW_C1_RX_THRESH_EN_C1_RX_THRESH_EN_SHIFT                                                       (0U)
#define GMAC_SW_C1_RX_THRESH_EN_C1_RX_THRESH_EN_MASK                                                        (0x000000ffU)

#define GMAC_SW_C1_RX_THRESH_EN_RESERVED1_SHIFT                                                             (8U)
#define GMAC_SW_C1_RX_THRESH_EN_RESERVED1_MASK                                                              (0xffffff00U)

#define GMAC_SW_C1_MISC_STAT_C1_MISC_STAT_SHIFT                                                             (0U)
#define GMAC_SW_C1_MISC_STAT_C1_MISC_STAT_MASK                                                              (0x0000001fU)

#define GMAC_SW_C1_MISC_STAT_RESERVED1_SHIFT                                                                (5U)
#define GMAC_SW_C1_MISC_STAT_RESERVED1_MASK                                                                 (0xffffffe0U)

#define GMAC_SW_C0_TX_EN_C0_TX_EN_SHIFT                                                                     (0U)
#define GMAC_SW_C0_TX_EN_C0_TX_EN_MASK                                                                      (0x000000ffU)

#define GMAC_SW_C0_TX_EN_RESERVED1_SHIFT                                                                    (8U)
#define GMAC_SW_C0_TX_EN_RESERVED1_MASK                                                                     (0xffffff00U)

#define GMAC_SW_C2_TX_EN_C2_TX_EN_SHIFT                                                                     (0U)
#define GMAC_SW_C2_TX_EN_C2_TX_EN_MASK                                                                      (0x000000ffU)

#define GMAC_SW_C2_TX_EN_RESERVED1_SHIFT                                                                    (8U)
#define GMAC_SW_C2_TX_EN_RESERVED1_MASK                                                                     (0xffffff00U)

#define GMAC_SW_C0_MISC_STAT_C0_MISC_STAT_SHIFT                                                             (0U)
#define GMAC_SW_C0_MISC_STAT_C0_MISC_STAT_MASK                                                              (0x0000001fU)

#define GMAC_SW_C0_MISC_STAT_RESERVED1_SHIFT                                                                (5U)
#define GMAC_SW_C0_MISC_STAT_RESERVED1_MASK                                                                 (0xffffffe0U)

#define GMAC_SW_C2_RX_THRESH_STAT_C2_RX_THRESH_STAT_SHIFT                                                   (0U)
#define GMAC_SW_C2_RX_THRESH_STAT_C2_RX_THRESH_STAT_MASK                                                    (0x000000ffU)

#define GMAC_SW_C2_RX_THRESH_STAT_RESERVED1_SHIFT                                                           (8U)
#define GMAC_SW_C2_RX_THRESH_STAT_RESERVED1_MASK                                                            (0xffffff00U)

#define GMAC_SW_C0_TX_IMAX_C0_TX_IMAX_SHIFT                                                                 (0U)
#define GMAC_SW_C0_TX_IMAX_C0_TX_IMAX_MASK                                                                  (0x0000003fU)

#define GMAC_SW_C0_TX_IMAX_RESERVED1_SHIFT                                                                  (6U)
#define GMAC_SW_C0_TX_IMAX_RESERVED1_MASK                                                                   (0xffffffc0U)

#define GMAC_SW_C2_TX_STAT_C2_TX_STAT_SHIFT                                                                 (0U)
#define GMAC_SW_C2_TX_STAT_C2_TX_STAT_MASK                                                                  (0x000000ffU)

#define GMAC_SW_C2_TX_STAT_RESERVED1_SHIFT                                                                  (8U)
#define GMAC_SW_C2_TX_STAT_RESERVED1_MASK                                                                   (0xffffff00U)

#define GMAC_SW_INT_CONTROL_INT_PRESCALE_SHIFT                                                              (0U)
#define GMAC_SW_INT_CONTROL_INT_PRESCALE_MASK                                                               (0x00000fffU)

#define GMAC_SW_INT_CONTROL_RESERVED2_SHIFT                                                                 (12U)
#define GMAC_SW_INT_CONTROL_RESERVED2_MASK                                                                  (0x0000f000U)

#define GMAC_SW_INT_CONTROL_INT_PACE_EN_SHIFT                                                               (16U)
#define GMAC_SW_INT_CONTROL_INT_PACE_EN_MASK                                                                (0x003f0000U)

#define GMAC_SW_INT_CONTROL_RESERVED1_SHIFT                                                                 (22U)
#define GMAC_SW_INT_CONTROL_RESERVED1_MASK                                                                  (0x7fc00000U)

#define GMAC_SW_INT_CONTROL_INT_TEST_SHIFT                                                                  (31U)
#define GMAC_SW_INT_CONTROL_INT_TEST_MASK                                                                   (0x80000000U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_GMACSW_WR_H_ */
