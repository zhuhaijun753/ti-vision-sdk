/******************************************************************************
*
* hw_mpu_csstm.h - register-level header file for MPU
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
#ifndef HW_MPU_CSSTM_H_
#define HW_MPU_CSSTM_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define MPU_STMDMASTARTR                                                                                    (0x0U)
#define MPU_STMDMASTOPR                                                                                     (0x4U)
#define MPU_STMDMASTATR                                                                                     (0x8U)
#define MPU_STMDMACTLR                                                                                      (0xcU)
#define MPU_STMDMAIDR                                                                                       (0xf8U)
#define MPU_STMHEER                                                                                         (0xfcU)
#define MPU_STMHETER                                                                                        (0x11cU)
#define MPU_STMHEMCR                                                                                        (0x160U)
#define MPU_STMHEMASTR                                                                                      (0x1f0U)
#define MPU_STMHEFEAT1R                                                                                     (0x1f4U)
#define MPU_STMHEIDR                                                                                        (0x1f8U)
#define MPU_STMSPER                                                                                         (0x1fcU)
#define MPU_STMSPTER                                                                                        (0x21cU)
#define MPU_STMSPSCR                                                                                        (0x25cU)
#define MPU_STMSPMSCR                                                                                       (0x260U)
#define MPU_STMSPOVERRIDER                                                                                  (0x264U)
#define MPU_STMSPMOVERRIDER                                                                                 (0x268U)
#define MPU_STMSPTRIGCSR                                                                                    (0x26cU)
#define MPU_STMTCSR                                                                                         (0x27cU)
#define MPU_STMTSSTIMR                                                                                      (0x280U)
#define MPU_STMTSFREQR                                                                                      (0x288U)
#define MPU_STMSYNCR                                                                                        (0x28cU)
#define MPU_STMAUXCR                                                                                        (0x290U)
#define MPU_STMFEAT1R                                                                                       (0x29cU)
#define MPU_STMFEAT2R                                                                                       (0x2a0U)
#define MPU_STMFEAT3R                                                                                       (0x2a4U)
#define MPU_STMITCTRL                                                                                       (0x2fcU)
#define MPU_STMCLAIMSET                                                                                     (0x39cU)
#define MPU_STMCLAIMCLR                                                                                     (0x3a0U)
#define MPU_STMLAR                                                                                          (0x3acU)
#define MPU_STMLSR                                                                                          (0x3b0U)
#define MPU_STMAUTHSTATUS                                                                                   (0x3b4U)
#define MPU_STMDEVID                                                                                        (0x3c4U)
#define MPU_STMDEVTYPE                                                                                      (0x3c8U)
#define MPU_STMPIDR4                                                                                        (0x3ccU)
#define MPU_STMPIDR0                                                                                        (0x3dcU)
#define MPU_STMPIDR1                                                                                        (0x3e0U)
#define MPU_STMPIDR2                                                                                        (0x3e4U)
#define MPU_STMPIDR3                                                                                        (0x3e8U)
#define MPU_STMCIDR0                                                                                        (0x3ecU)
#define MPU_STMCIDR1                                                                                        (0x3f0U)
#define MPU_STMCIDR2                                                                                        (0x3f4U)
#define MPU_STMCIDR3                                                                                        (0x3f8U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define MPU_STMDMASTARTR_START_SHIFT                                                                        (0U)
#define MPU_STMDMASTARTR_START_MASK                                                                         (0x00000001U)

#define MPU_STMDMASTARTR_RESERVED_SHIFT                                                                     (1U)
#define MPU_STMDMASTARTR_RESERVED_MASK                                                                      (0xfffffffeU)

#define MPU_STMDMASTOPR_STOP_SHIFT                                                                          (0U)
#define MPU_STMDMASTOPR_STOP_MASK                                                                           (0x00000001U)

#define MPU_STMDMASTOPR_RESERVED_SHIFT                                                                      (1U)
#define MPU_STMDMASTOPR_RESERVED_MASK                                                                       (0xfffffffeU)

#define MPU_STMDMASTATR_STATUS_SHIFT                                                                        (0U)
#define MPU_STMDMASTATR_STATUS_MASK                                                                         (0x00000001U)

#define MPU_STMDMASTATR_RESERVED_SHIFT                                                                      (1U)
#define MPU_STMDMASTATR_RESERVED_MASK                                                                       (0xfffffffeU)

#define MPU_STMDMACTLR_SENS_SHIFT                                                                           (0U)
#define MPU_STMDMACTLR_SENS_MASK                                                                            (0x0000000fU)

#define MPU_STMDMACTLR_RESERVED_SHIFT                                                                       (4U)
#define MPU_STMDMACTLR_RESERVED_MASK                                                                        (0xfffffff0U)

#define MPU_STMDMAIDR_CLASS_SHIFT                                                                           (0U)
#define MPU_STMDMAIDR_CLASS_MASK                                                                            (0x0000000fU)

#define MPU_STMDMAIDR_CLASSREV_SHIFT                                                                        (4U)
#define MPU_STMDMAIDR_CLASSREV_MASK                                                                         (0x000000f0U)

#define MPU_STMDMAIDR_VENDSPEC_SHIFT                                                                        (8U)
#define MPU_STMDMAIDR_VENDSPEC_MASK                                                                         (0x00000f00U)

#define MPU_STMDMAIDR_RESERVED_SHIFT                                                                        (12U)
#define MPU_STMDMAIDR_RESERVED_MASK                                                                         (0xfffff000U)

#define MPU_STMHEER_HEE_SHIFT                                                                               (0U)
#define MPU_STMHEER_HEE_MASK                                                                                (0xffffffffU)

#define MPU_STMHETER_HETE_SHIFT                                                                             (0U)
#define MPU_STMHETER_HETE_MASK                                                                              (0xffffffffU)

#define MPU_STMHEMCR_EN_SHIFT                                                                               (0U)
#define MPU_STMHEMCR_EN_MASK                                                                                (0x00000001U)

#define MPU_STMHEMCR_COMPEN_SHIFT                                                                           (1U)
#define MPU_STMHEMCR_COMPEN_MASK                                                                            (0x00000002U)

#define MPU_STMHEMCR_ERRDETECT_SHIFT                                                                        (2U)
#define MPU_STMHEMCR_ERRDETECT_MASK                                                                         (0x00000004U)

#define MPU_STMHEMCR_TRIGCTL_SHIFT                                                                          (4U)
#define MPU_STMHEMCR_TRIGCTL_MASK                                                                           (0x00000010U)

#define MPU_STMHEMCR_TRIGSTATUS_SHIFT                                                                       (5U)
#define MPU_STMHEMCR_TRIGSTATUS_MASK                                                                        (0x00000020U)

#define MPU_STMHEMCR_TRIGCLEAR_SHIFT                                                                        (6U)
#define MPU_STMHEMCR_TRIGCLEAR_MASK                                                                         (0x00000040U)

#define MPU_STMHEMCR_ATBTRIGEN_SHIFT                                                                        (7U)
#define MPU_STMHEMCR_ATBTRIGEN_MASK                                                                         (0x00000080U)

#define MPU_STMHEMCR_RESERVED_SHIFT                                                                         (3U)
#define MPU_STMHEMCR_RESERVED_MASK                                                                          (0x00000008U)

#define MPU_STMHEMCR_RESERVED1_SHIFT                                                                        (8U)
#define MPU_STMHEMCR_RESERVED1_MASK                                                                         (0xffffff00U)

#define MPU_STMHEMASTR_MASTER_SHIFT                                                                         (0U)
#define MPU_STMHEMASTR_MASTER_MASK                                                                          (0x0000ffffU)

#define MPU_STMHEMASTR_RESERVED_SHIFT                                                                       (16U)
#define MPU_STMHEMASTR_RESERVED_MASK                                                                        (0xffff0000U)

#define MPU_STMHEFEAT1R_HETER_SHIFT                                                                         (0U)
#define MPU_STMHEFEAT1R_HETER_MASK                                                                          (0x00000001U)

#define MPU_STMHEFEAT1R_HEERR_SHIFT                                                                         (2U)
#define MPU_STMHEFEAT1R_HEERR_MASK                                                                          (0x00000004U)

#define MPU_STMHEFEAT1R_HEMASTR_SHIFT                                                                       (3U)
#define MPU_STMHEFEAT1R_HEMASTR_MASK                                                                        (0x00000008U)

#define MPU_STMHEFEAT1R_HECOMP_SHIFT                                                                        (4U)
#define MPU_STMHEFEAT1R_HECOMP_MASK                                                                         (0x00000030U)

#define MPU_STMHEFEAT1R_NUMHE_SHIFT                                                                         (15U)
#define MPU_STMHEFEAT1R_NUMHE_MASK                                                                          (0x00ff8000U)

#define MPU_STMHEFEAT1R_RESERVED_SHIFT                                                                      (1U)
#define MPU_STMHEFEAT1R_RESERVED_MASK                                                                       (0x00000002U)

#define MPU_STMHEFEAT1R_RESERVED1_SHIFT                                                                     (6U)
#define MPU_STMHEFEAT1R_RESERVED1_MASK                                                                      (0x00007fc0U)

#define MPU_STMHEFEAT1R_RESERVED2_SHIFT                                                                     (24U)
#define MPU_STMHEFEAT1R_RESERVED2_MASK                                                                      (0xff000000U)

#define MPU_STMHEIDR_CLASS_SHIFT                                                                            (0U)
#define MPU_STMHEIDR_CLASS_MASK                                                                             (0x0000000fU)

#define MPU_STMHEIDR_CLASSREV_SHIFT                                                                         (4U)
#define MPU_STMHEIDR_CLASSREV_MASK                                                                          (0x000000f0U)

#define MPU_STMHEIDR_VENDSPEC_SHIFT                                                                         (8U)
#define MPU_STMHEIDR_VENDSPEC_MASK                                                                          (0x00000f00U)

#define MPU_STMHEIDR_RESERVED_SHIFT                                                                         (12U)
#define MPU_STMHEIDR_RESERVED_MASK                                                                          (0xfffff000U)

#define MPU_STMSPER_SPE_SHIFT                                                                               (0U)
#define MPU_STMSPER_SPE_MASK                                                                                (0xffffffffU)

#define MPU_STMSPTER_SPTE_SHIFT                                                                             (0U)
#define MPU_STMSPTER_SPTE_MASK                                                                              (0xffffffffU)

#define MPU_STMSPSCR_PORTSEL_SHIFT                                                                          (20U)
#define MPU_STMSPSCR_PORTSEL_MASK                                                                           (0xfff00000U)

#define MPU_STMSPSCR_PORTCTL_SHIFT                                                                          (0U)
#define MPU_STMSPSCR_PORTCTL_MASK                                                                           (0x00000003U)

#define MPU_STMSPSCR_RESERVED_SHIFT                                                                         (2U)
#define MPU_STMSPSCR_RESERVED_MASK                                                                          (0x000ffffcU)

#define MPU_STMSPMSCR_MASTSEL_SHIFT                                                                         (15U)
#define MPU_STMSPMSCR_MASTSEL_MASK                                                                          (0xffff8000U)

#define MPU_STMSPMSCR_MASTCTL_SHIFT                                                                         (0U)
#define MPU_STMSPMSCR_MASTCTL_MASK                                                                          (0x00000001U)

#define MPU_STMSPMSCR_RESERVED_SHIFT                                                                        (1U)
#define MPU_STMSPMSCR_RESERVED_MASK                                                                         (0x00007ffeU)

#define MPU_STMSPOVERRIDER_PORTSEL_SHIFT                                                                    (15U)
#define MPU_STMSPOVERRIDER_PORTSEL_MASK                                                                     (0xffff8000U)

#define MPU_STMSPOVERRIDER_OVERTS_SHIFT                                                                     (2U)
#define MPU_STMSPOVERRIDER_OVERTS_MASK                                                                      (0x00000004U)

#define MPU_STMSPOVERRIDER_OVERCTL_SHIFT                                                                    (0U)
#define MPU_STMSPOVERRIDER_OVERCTL_MASK                                                                     (0x00000003U)

#define MPU_STMSPOVERRIDER_RESERVED_SHIFT                                                                   (3U)
#define MPU_STMSPOVERRIDER_RESERVED_MASK                                                                    (0x00007ff8U)

#define MPU_STMSPMOVERRIDER_MASTSEL_SHIFT                                                                   (15U)
#define MPU_STMSPMOVERRIDER_MASTSEL_MASK                                                                    (0xffff8000U)

#define MPU_STMSPMOVERRIDER_MASTCTL_SHIFT                                                                   (0U)
#define MPU_STMSPMOVERRIDER_MASTCTL_MASK                                                                    (0x00000001U)

#define MPU_STMSPMOVERRIDER_RESERVED_SHIFT                                                                  (1U)
#define MPU_STMSPMOVERRIDER_RESERVED_MASK                                                                   (0x00007ffeU)

#define MPU_STMSPTRIGCSR_ATBTRIGEN_DIR_SHIFT                                                                (4U)
#define MPU_STMSPTRIGCSR_ATBTRIGEN_DIR_MASK                                                                 (0x00000010U)

#define MPU_STMSPTRIGCSR_ATBTRIGEN_TE_SHIFT                                                                 (3U)
#define MPU_STMSPTRIGCSR_ATBTRIGEN_TE_MASK                                                                  (0x00000008U)

#define MPU_STMSPTRIGCSR_TRIGCLEAR_SHIFT                                                                    (2U)
#define MPU_STMSPTRIGCSR_TRIGCLEAR_MASK                                                                     (0x00000004U)

#define MPU_STMSPTRIGCSR_TRIGSTATUS_SHIFT                                                                   (1U)
#define MPU_STMSPTRIGCSR_TRIGSTATUS_MASK                                                                    (0x00000002U)

#define MPU_STMSPTRIGCSR_TRIGCTL_SHIFT                                                                      (0U)
#define MPU_STMSPTRIGCSR_TRIGCTL_MASK                                                                       (0x00000001U)

#define MPU_STMSPTRIGCSR_RESERVED_SHIFT                                                                     (5U)
#define MPU_STMSPTRIGCSR_RESERVED_MASK                                                                      (0xffffffe0U)

#define MPU_STMTCSR_BUSY_SHIFT                                                                              (23U)
#define MPU_STMTCSR_BUSY_MASK                                                                               (0x00800000U)

#define MPU_STMTCSR_TRACEID_SHIFT                                                                           (16U)
#define MPU_STMTCSR_TRACEID_MASK                                                                            (0x007f0000U)

#define MPU_STMTCSR_COMPEN_SHIFT                                                                            (5U)
#define MPU_STMTCSR_COMPEN_MASK                                                                             (0x00000020U)

#define MPU_STMTCSR_SYNCEN_SHIFT                                                                            (2U)
#define MPU_STMTCSR_SYNCEN_MASK                                                                             (0x00000004U)

#define MPU_STMTCSR_TSEN_SHIFT                                                                              (1U)
#define MPU_STMTCSR_TSEN_MASK                                                                               (0x00000002U)

#define MPU_STMTCSR_EN_SHIFT                                                                                (0U)
#define MPU_STMTCSR_EN_MASK                                                                                 (0x00000001U)

#define MPU_STMTCSR_RESERVED_SHIFT                                                                          (3U)
#define MPU_STMTCSR_RESERVED_MASK                                                                           (0x00000018U)

#define MPU_STMTCSR_RESERVED1_SHIFT                                                                         (6U)
#define MPU_STMTCSR_RESERVED1_MASK                                                                          (0x0000ffc0U)

#define MPU_STMTCSR_RESERVED2_SHIFT                                                                         (24U)
#define MPU_STMTCSR_RESERVED2_MASK                                                                          (0xff000000U)

#define MPU_STMTSSTIMR_FORCETS_SHIFT                                                                        (0U)
#define MPU_STMTSSTIMR_FORCETS_MASK                                                                         (0x00000001U)

#define MPU_STMTSSTIMR_RESERVED_SHIFT                                                                       (1U)
#define MPU_STMTSSTIMR_RESERVED_MASK                                                                        (0xfffffffeU)

#define MPU_STMTSFREQR_FREQ_SHIFT                                                                           (0U)
#define MPU_STMTSFREQR_FREQ_MASK                                                                            (0xffffffffU)

#define MPU_STMSYNCR_MODE_SHIFT                                                                             (12U)
#define MPU_STMSYNCR_MODE_MASK                                                                              (0x00001000U)

#define MPU_STMSYNCR_COUNT_SHIFT                                                                            (0U)
#define MPU_STMSYNCR_COUNT_MASK                                                                             (0x00000fffU)

#define MPU_STMSYNCR_RESERVED_SHIFT                                                                         (13U)
#define MPU_STMSYNCR_RESERVED_MASK                                                                          (0xffffe000U)

#define MPU_STMAUXCR_FIFOAF_SHIFT                                                                           (0U)
#define MPU_STMAUXCR_FIFOAF_MASK                                                                            (0x00000001U)

#define MPU_STMAUXCR_ASYNCPE_SHIFT                                                                          (1U)
#define MPU_STMAUXCR_ASYNCPE_MASK                                                                           (0x00000002U)

#define MPU_STMAUXCR_PRIORINVDIS_SHIFT                                                                      (2U)
#define MPU_STMAUXCR_PRIORINVDIS_MASK                                                                       (0x00000004U)

#define MPU_STMAUXCR_CLKON_SHIFT                                                                            (3U)
#define MPU_STMAUXCR_CLKON_MASK                                                                             (0x00000008U)

#define MPU_STMAUXCR_AFREADYHIGH_SHIFT                                                                      (4U)
#define MPU_STMAUXCR_AFREADYHIGH_MASK                                                                       (0x00000010U)

#define MPU_STMAUXCR_RESERVED_SHIFT                                                                         (5U)
#define MPU_STMAUXCR_RESERVED_MASK                                                                          (0xffffffe0U)

#define MPU_STMFEAT1R_PROT_SHIFT                                                                            (0U)
#define MPU_STMFEAT1R_PROT_MASK                                                                             (0x0000000fU)

#define MPU_STMFEAT1R_TS_SHIFT                                                                              (4U)
#define MPU_STMFEAT1R_TS_MASK                                                                               (0x00000030U)

#define MPU_STMFEAT1R_TSFREQ_SHIFT                                                                          (6U)
#define MPU_STMFEAT1R_TSFREQ_MASK                                                                           (0x00000040U)

#define MPU_STMFEAT1R_FORCETS_SHIFT                                                                         (7U)
#define MPU_STMFEAT1R_FORCETS_MASK                                                                          (0x00000080U)

#define MPU_STMFEAT1R_SYNC_SHIFT                                                                            (8U)
#define MPU_STMFEAT1R_SYNC_MASK                                                                             (0x00000300U)

#define MPU_STMFEAT1R_TRACEBUS_SHIFT                                                                        (10U)
#define MPU_STMFEAT1R_TRACEBUS_MASK                                                                         (0x00003c00U)

#define MPU_STMFEAT1R_TRIGCTL_SHIFT                                                                         (14U)
#define MPU_STMFEAT1R_TRIGCTL_MASK                                                                          (0x0000c000U)

#define MPU_STMFEAT1R_TSPRESCALE_SHIFT                                                                      (16U)
#define MPU_STMFEAT1R_TSPRESCALE_MASK                                                                       (0x00030000U)

#define MPU_STMFEAT1R_HWTEN_SHIFT                                                                           (18U)
#define MPU_STMFEAT1R_HWTEN_MASK                                                                            (0x000c0000U)

#define MPU_STMFEAT1R_SYNCEN_SHIFT                                                                          (20U)
#define MPU_STMFEAT1R_SYNCEN_MASK                                                                           (0x00300000U)

#define MPU_STMFEAT1R_SWOEN_SHIFT                                                                           (22U)
#define MPU_STMFEAT1R_SWOEN_MASK                                                                            (0x00c00000U)

#define MPU_STMFEAT1R_RESERVED_SHIFT                                                                        (24U)
#define MPU_STMFEAT1R_RESERVED_MASK                                                                         (0xff000000U)

#define MPU_STMFEAT2R_SPTER_SHIFT                                                                           (0U)
#define MPU_STMFEAT2R_SPTER_MASK                                                                            (0x00000003U)

#define MPU_STMFEAT2R_SPER_SHIFT                                                                            (2U)
#define MPU_STMFEAT2R_SPER_MASK                                                                             (0x00000004U)

#define MPU_STMFEAT2R_SPCOMP_SHIFT                                                                          (4U)
#define MPU_STMFEAT2R_SPCOMP_MASK                                                                           (0x00000030U)

#define MPU_STMFEAT2R_SPOVERRIDE_SHIFT                                                                      (6U)
#define MPU_STMFEAT2R_SPOVERRIDE_MASK                                                                       (0x00000040U)

#define MPU_STMFEAT2R_PRIVMASK_SHIFT                                                                        (7U)
#define MPU_STMFEAT2R_PRIVMASK_MASK                                                                         (0x00000180U)

#define MPU_STMFEAT2R_SPTRTYPE_SHIFT                                                                        (9U)
#define MPU_STMFEAT2R_SPTRTYPE_MASK                                                                         (0x00000600U)

#define MPU_STMFEAT2R_DSIZE_SHIFT                                                                           (12U)
#define MPU_STMFEAT2R_DSIZE_MASK                                                                            (0x0000f000U)

#define MPU_STMFEAT2R_SPTYPE_SHIFT                                                                          (16U)
#define MPU_STMFEAT2R_SPTYPE_MASK                                                                           (0x00030000U)

#define MPU_STMFEAT2R_RESERVED_SHIFT                                                                        (3U)
#define MPU_STMFEAT2R_RESERVED_MASK                                                                         (0x00000008U)

#define MPU_STMFEAT2R_RESERVED1_SHIFT                                                                       (11U)
#define MPU_STMFEAT2R_RESERVED1_MASK                                                                        (0x00000800U)

#define MPU_STMFEAT2R_RESERVED2_SHIFT                                                                       (18U)
#define MPU_STMFEAT2R_RESERVED2_MASK                                                                        (0xfffc0000U)

#define MPU_STMFEAT3R_NUMMAST_SHIFT                                                                         (0U)
#define MPU_STMFEAT3R_NUMMAST_MASK                                                                          (0x0000007fU)

#define MPU_STMFEAT3R_RESERVED_SHIFT                                                                        (7U)
#define MPU_STMFEAT3R_RESERVED_MASK                                                                         (0xffffff80U)

#define MPU_STMITCTRL_INTEGRATION_MODE_SHIFT                                                                (0U)
#define MPU_STMITCTRL_INTEGRATION_MODE_MASK                                                                 (0x00000001U)

#define MPU_STMITCTRL_RESERVED_SHIFT                                                                        (1U)
#define MPU_STMITCTRL_RESERVED_MASK                                                                         (0xfffffffeU)

#define MPU_STMCLAIMSET_CLAIMSET_SHIFT                                                                      (0U)
#define MPU_STMCLAIMSET_CLAIMSET_MASK                                                                       (0x00000001U)

#define MPU_STMCLAIMSET_RESERVED_SHIFT                                                                      (4U)
#define MPU_STMCLAIMSET_RESERVED_MASK                                                                       (0xfffffff0U)

#define MPU_STMCLAIMCLR_CLAIMCLR_SHIFT                                                                      (0U)
#define MPU_STMCLAIMCLR_CLAIMCLR_MASK                                                                       (0x00000001U)

#define MPU_STMCLAIMCLR_RESERVED_SHIFT                                                                      (4U)
#define MPU_STMCLAIMCLR_RESERVED_MASK                                                                       (0xfffffff0U)

#define MPU_STMLAR_ACCESS_W_SHIFT                                                                           (0U)
#define MPU_STMLAR_ACCESS_W_MASK                                                                            (0xffffffffU)

#define MPU_STMLSR_PRESENT_SHIFT                                                                            (0U)
#define MPU_STMLSR_PRESENT_MASK                                                                             (0x00000001U)

#define MPU_STMLSR_LOCKED_SHIFT                                                                             (1U)
#define MPU_STMLSR_LOCKED_MASK                                                                              (0x00000002U)

#define MPU_STMLSR_TYPE_SHIFT                                                                               (2U)
#define MPU_STMLSR_TYPE_MASK                                                                                (0x00000004U)

#define MPU_STMLSR_RESERVED_SHIFT                                                                           (3U)
#define MPU_STMLSR_RESERVED_MASK                                                                            (0xfffffff8U)

#define MPU_STMAUTHSTATUS_NSID_SHIFT                                                                        (0U)
#define MPU_STMAUTHSTATUS_NSID_MASK                                                                         (0x00000003U)

#define MPU_STMAUTHSTATUS_NSNID_SHIFT                                                                       (2U)
#define MPU_STMAUTHSTATUS_NSNID_MASK                                                                        (0x0000000cU)

#define MPU_STMAUTHSTATUS_SID_SHIFT                                                                         (4U)
#define MPU_STMAUTHSTATUS_SID_MASK                                                                          (0x00000030U)

#define MPU_STMAUTHSTATUS_SNID_SHIFT                                                                        (6U)
#define MPU_STMAUTHSTATUS_SNID_MASK                                                                         (0x000000c0U)

#define MPU_STMAUTHSTATUS_RESERVED_SHIFT                                                                    (8U)
#define MPU_STMAUTHSTATUS_RESERVED_MASK                                                                     (0xffffff00U)

#define MPU_STMDEVID_NUMSP_SHIFT                                                                            (0U)
#define MPU_STMDEVID_NUMSP_MASK                                                                             (0x0001ffffU)

#define MPU_STMDEVID_RESERVED_SHIFT                                                                         (17U)
#define MPU_STMDEVID_RESERVED_MASK                                                                          (0xfffe0000U)

#define MPU_STMDEVTYPE_MAJOR_TYPE_SHIFT                                                                     (0U)
#define MPU_STMDEVTYPE_MAJOR_TYPE_MASK                                                                      (0x0000000fU)

#define MPU_STMDEVTYPE_SUB_TYPE_SHIFT                                                                       (4U)
#define MPU_STMDEVTYPE_SUB_TYPE_MASK                                                                        (0x000000f0U)

#define MPU_STMDEVTYPE_RESERVED_SHIFT                                                                       (8U)
#define MPU_STMDEVTYPE_RESERVED_MASK                                                                        (0xffffff00U)

#define MPU_STMPIDR4_JEP106_CONT_SHIFT                                                                      (0U)
#define MPU_STMPIDR4_JEP106_CONT_MASK                                                                       (0x0000000fU)

#define MPU_STMPIDR4_FOURKB_COUNT_SHIFT                                                                     (4U)
#define MPU_STMPIDR4_FOURKB_COUNT_MASK                                                                      (0x000000f0U)

#define MPU_STMPIDR4_RESERVED_SHIFT                                                                         (8U)
#define MPU_STMPIDR4_RESERVED_MASK                                                                          (0xffffff00U)

#define MPU_STMPIDR0_PART_NUMBER_BITS7TO0_SHIFT                                                             (0U)
#define MPU_STMPIDR0_PART_NUMBER_BITS7TO0_MASK                                                              (0x000000ffU)

#define MPU_STMPIDR0_RESERVED_SHIFT                                                                         (8U)
#define MPU_STMPIDR0_RESERVED_MASK                                                                          (0xffffff00U)

#define MPU_STMPIDR1_PART_NUMBER_BITS11TO8_SHIFT                                                            (0U)
#define MPU_STMPIDR1_PART_NUMBER_BITS11TO8_MASK                                                             (0x0000000fU)

#define MPU_STMPIDR1_JEP106_BITS3TO0_SHIFT                                                                  (4U)
#define MPU_STMPIDR1_JEP106_BITS3TO0_MASK                                                                   (0x000000f0U)

#define MPU_STMPIDR1_RESERVED_SHIFT                                                                         (8U)
#define MPU_STMPIDR1_RESERVED_MASK                                                                          (0xffffff00U)

#define MPU_STMPIDR2_JEP106_BITS6TO4_SHIFT                                                                  (0U)
#define MPU_STMPIDR2_JEP106_BITS6TO4_MASK                                                                   (0x00000007U)

#define MPU_STMPIDR2_JEDEC_SHIFT                                                                            (3U)
#define MPU_STMPIDR2_JEDEC_MASK                                                                             (0x00000008U)

#define MPU_STMPIDR2_REVISION_SHIFT                                                                         (4U)
#define MPU_STMPIDR2_REVISION_MASK                                                                          (0x000000f0U)

#define MPU_STMPIDR2_RESERVED_SHIFT                                                                         (8U)
#define MPU_STMPIDR2_RESERVED_MASK                                                                          (0xffffff00U)

#define MPU_STMPIDR3_CUSTOMER_MODIFIED_SHIFT                                                                (0U)
#define MPU_STMPIDR3_CUSTOMER_MODIFIED_MASK                                                                 (0x0000000fU)

#define MPU_STMPIDR3_REVAND_SHIFT                                                                           (4U)
#define MPU_STMPIDR3_REVAND_MASK                                                                            (0x000000f0U)

#define MPU_STMPIDR3_RESERVED_SHIFT                                                                         (8U)
#define MPU_STMPIDR3_RESERVED_MASK                                                                          (0xffffff00U)

#define MPU_STMCIDR0_PREAMBLE_SHIFT                                                                         (0U)
#define MPU_STMCIDR0_PREAMBLE_MASK                                                                          (0x000000ffU)

#define MPU_STMCIDR0_RESERVED_SHIFT                                                                         (8U)
#define MPU_STMCIDR0_RESERVED_MASK                                                                          (0xffffff00U)

#define MPU_STMCIDR1_PREAMBLE_SHIFT                                                                         (0U)
#define MPU_STMCIDR1_PREAMBLE_MASK                                                                          (0x0000000fU)

#define MPU_STMCIDR1_CLASS_SHIFT                                                                            (4U)
#define MPU_STMCIDR1_CLASS_MASK                                                                             (0x000000f0U)

#define MPU_STMCIDR1_RESERVED_SHIFT                                                                         (8U)
#define MPU_STMCIDR1_RESERVED_MASK                                                                          (0xffffff00U)

#define MPU_STMCIDR2_PREAMBLE_SHIFT                                                                         (0U)
#define MPU_STMCIDR2_PREAMBLE_MASK                                                                          (0x000000ffU)

#define MPU_STMCIDR2_RESERVED_SHIFT                                                                         (8U)
#define MPU_STMCIDR2_RESERVED_MASK                                                                          (0xffffff00U)

#define MPU_STMCIDR3_PREAMBLE_SHIFT                                                                         (0U)
#define MPU_STMCIDR3_PREAMBLE_MASK                                                                          (0x000000ffU)

#define MPU_STMCIDR3_RESERVED_SHIFT                                                                         (8U)
#define MPU_STMCIDR3_RESERVED_MASK                                                                          (0xffffff00U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_MPU_CSSTM_H_ */
