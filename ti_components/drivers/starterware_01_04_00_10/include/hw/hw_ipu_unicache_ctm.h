/******************************************************************************
*
* hw_ipu_unicache_ctm.h - register-level header file for IPU
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
#ifndef HW_IPU_UNICACHE_CTM_H_
#define HW_IPU_UNICACHE_CTM_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define IPU_CTCNTL                                                                                          (0x0U)
#define IPU_TINTVLR(n)                                                                                      (0x40U + (n * 4))
#define IPU_CTDBGNUM                                                                                        (0x7cU)
#define IPU_CTGNBL                                                                                          (0xf0U)
#define IPU_CTGRST                                                                                          (0xf8U)
#define IPU_CTCR_WT(n)                                                                                      (0x100U + (n * 4))
#define IPU_CTCR_WOT(n)                                                                                     (0x108U + (n * 4))
#define IPU_CTCNTR(n)                                                                                       (0x180U + (n * 4))

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define IPU_CTCNTL_ENBL_SHIFT                                                                               (0U)
#define IPU_CTCNTL_ENBL_MASK                                                                                (0x00000001U)
#define IPU_CTCNTL_ENBL_DISABLE                                                                              (0U)
#define IPU_CTCNTL_ENBL_ENABLE                                                                               (1U)

#define IPU_CTCNTL_IDLEMODE_SHIFT                                                                           (1U)
#define IPU_CTCNTL_IDLEMODE_MASK                                                                            (0x00000006U)
#define IPU_CTCNTL_IDLEMODE_FORCE_IDLE                                                                       (0U)
#define IPU_CTCNTL_IDLEMODE_NO_IDLE                                                                          (1U)
#define IPU_CTCNTL_IDLEMODE_SMART_IDLE                                                                       (2U)
#define IPU_CTCNTL_IDLEMODE_SMART_IDLE_WAKEUP                                                                (3U)

#define IPU_CTCNTL_REVID_SHIFT                                                                              (3U)
#define IPU_CTCNTL_REVID_MASK                                                                               (0x00000078U)

#define IPU_CTCNTL_NUMCNTR_SHIFT                                                                            (7U)
#define IPU_CTCNTL_NUMCNTR_MASK                                                                             (0x00001f80U)

#define IPU_CTCNTL_NUMTIMR_SHIFT                                                                            (13U)
#define IPU_CTCNTL_NUMTIMR_MASK                                                                             (0x0003e000U)

#define IPU_CTCNTL_NUMINPT_SHIFT                                                                            (18U)
#define IPU_CTCNTL_NUMINPT_MASK                                                                             (0x03fc0000U)

#define IPU_CTCNTL_NUMSTM_SHIFT                                                                             (26U)
#define IPU_CTCNTL_NUMSTM_MASK                                                                              (0xfc000000U)

#define IPU_TINTVLR_INTERVAL_SHIFT                                                                          (0U)
#define IPU_TINTVLR_INTERVAL_MASK                                                                           (0xffffffffU)

#define IPU_CTDBGNUM_NUMEVT_SHIFT                                                                           (0U)
#define IPU_CTDBGNUM_NUMEVT_MASK                                                                            (0x00000007U)

#define IPU_CTDBGNUM_RESERVED_SHIFT                                                                         (3U)
#define IPU_CTDBGNUM_RESERVED_MASK                                                                          (0xfffffff8U)

#define IPU_CTGNBL_ENABLE_SHIFT                                                                             (0U)
#define IPU_CTGNBL_ENABLE_MASK                                                                              (0x000000ffU)

#define IPU_CTGNBL_RESERVED_SHIFT                                                                           (8U)
#define IPU_CTGNBL_RESERVED_MASK                                                                            (0xffffff00U)

#define IPU_CTGRST_RESET_SHIFT                                                                              (0U)
#define IPU_CTGRST_RESET_MASK                                                                               (0x000000ffU)

#define IPU_CTGRST_RESERVED_SHIFT                                                                           (8U)
#define IPU_CTGRST_RESERVED_MASK                                                                            (0xffffff00U)

#define IPU_CTCR_WT_ENBL_SHIFT                                                                              (0U)
#define IPU_CTCR_WT_ENBL_MASK                                                                               (0x00000001U)

#define IPU_CTCR_WT_RESET_SHIFT                                                                             (1U)
#define IPU_CTCR_WT_RESET_MASK                                                                              (0x00000002U)

#define IPU_CTCR_WT_CHAIN_SHIFT                                                                             (2U)
#define IPU_CTCR_WT_CHAIN_MASK                                                                              (0x00000004U)

#define IPU_CTCR_WT_DURMODE_SHIFT                                                                           (3U)
#define IPU_CTCR_WT_DURMODE_MASK                                                                            (0x00000008U)

#define IPU_CTCR_WT_FREE_SHIFT                                                                              (4U)
#define IPU_CTCR_WT_FREE_MASK                                                                               (0x00000010U)

#define IPU_CTCR_WT_IDLE_SHIFT                                                                              (5U)
#define IPU_CTCR_WT_IDLE_MASK                                                                               (0x00000020U)

#define IPU_CTCR_WT_OVRFLW_SHIFT                                                                            (6U)
#define IPU_CTCR_WT_OVRFLW_MASK                                                                             (0x00000040U)

#define IPU_CTCR_WT_INT_SHIFT                                                                               (8U)
#define IPU_CTCR_WT_INT_MASK                                                                                (0x00000100U)

#define IPU_CTCR_WT_DBG_SHIFT                                                                               (9U)
#define IPU_CTCR_WT_DBG_MASK                                                                                (0x00000200U)

#define IPU_CTCR_WT_RESTART_SHIFT                                                                           (10U)
#define IPU_CTCR_WT_RESTART_MASK                                                                            (0x00000400U)

#define IPU_CTCR_WT_INPSEL_SHIFT                                                                            (16U)
#define IPU_CTCR_WT_INPSEL_MASK                                                                             (0x001f0000U)

#define IPU_CTCR_WT_RESERVED1_SHIFT                                                                         (11U)
#define IPU_CTCR_WT_RESERVED1_MASK                                                                          (0x0000f800U)

#define IPU_CTCR_WT_RESERVED2_SHIFT                                                                         (21U)
#define IPU_CTCR_WT_RESERVED2_MASK                                                                          (0xffe00000U)

#define IPU_CTCR_WT_CHNCDW_SHIFT                                                                            (7U)
#define IPU_CTCR_WT_CHNCDW_MASK                                                                             (0x00000080U)

#define IPU_CTCR_WOT_ENBL_SHIFT                                                                             (0U)
#define IPU_CTCR_WOT_ENBL_MASK                                                                              (0x00000001U)

#define IPU_CTCR_WOT_RESET_SHIFT                                                                            (1U)
#define IPU_CTCR_WOT_RESET_MASK                                                                             (0x00000002U)

#define IPU_CTCR_WOT_CHAIN_SHIFT                                                                            (2U)
#define IPU_CTCR_WOT_CHAIN_MASK                                                                             (0x00000004U)

#define IPU_CTCR_WOT_DURMODE_SHIFT                                                                          (3U)
#define IPU_CTCR_WOT_DURMODE_MASK                                                                           (0x00000008U)

#define IPU_CTCR_WOT_FREE_SHIFT                                                                             (4U)
#define IPU_CTCR_WOT_FREE_MASK                                                                              (0x00000010U)

#define IPU_CTCR_WOT_IDLE_SHIFT                                                                             (5U)
#define IPU_CTCR_WOT_IDLE_MASK                                                                              (0x00000020U)

#define IPU_CTCR_WOT_OVRFLW_SHIFT                                                                           (6U)
#define IPU_CTCR_WOT_OVRFLW_MASK                                                                            (0x00000040U)

#define IPU_CTCR_WOT_INPSEL_SHIFT                                                                           (16U)
#define IPU_CTCR_WOT_INPSEL_MASK                                                                            (0x001f0000U)

#define IPU_CTCR_WOT_RESERVED1_SHIFT                                                                        (8U)
#define IPU_CTCR_WOT_RESERVED1_MASK                                                                         (0x0000ff00U)

#define IPU_CTCR_WOT_RESERVED2_SHIFT                                                                        (21U)
#define IPU_CTCR_WOT_RESERVED2_MASK                                                                         (0xffe00000U)

#define IPU_CTCR_WOT_CHNSDW_SHIFT                                                                           (7U)
#define IPU_CTCR_WOT_CHNSDW_MASK                                                                            (0x00000080U)

#define IPU_CTCNTR_COUNT_SHIFT                                                                              (0U)
#define IPU_CTCNTR_COUNT_MASK                                                                               (0xffffffffU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_IPU_UNICACHE_CTM_H_ */
