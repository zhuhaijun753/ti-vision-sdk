/******************************************************************************
*
* hw_mmu.h - register-level header file for MMU
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
#ifndef HW_MMU_H_
#define HW_MMU_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define MMU_REVISION                                                                                        (0x0U)
#define MMU_SYSCONFIG                                                                                       (0x10U)
#define MMU_SYSSTATUS                                                                                       (0x14U)
#define MMU_IRQSTATUS                                                                                       (0x18U)
#define MMU_IRQENABLE                                                                                       (0x1cU)
#define MMU_WALKING_ST                                                                                      (0x40U)
#define MMU_CNTL                                                                                            (0x44U)
#define MMU_FAULT_AD                                                                                        (0x48U)
#define MMU_TTB                                                                                             (0x4cU)
#define MMU_LOCK                                                                                            (0x50U)
#define MMU_LD_TLB                                                                                          (0x54U)
#define MMU_CAM                                                                                             (0x58U)
#define MMU_RAM                                                                                             (0x5cU)
#define MMU_GFLUSH                                                                                          (0x60U)
#define MMU_FLUSH_ENTRY                                                                                     (0x64U)
#define MMU_READ_CAM                                                                                        (0x68U)
#define MMU_READ_RAM                                                                                        (0x6cU)
#define MMU_EMU_FAULT_AD                                                                                    (0x70U)
#define MMU_FAULT_PC                                                                                        (0x80U)
#define MMU_FAULT_STATUS                                                                                    (0x84U)
#define MMU_GP_REG                                                                                          (0x88U)
#define MMU_DSPSS_GPR                                                                                       (0x88U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define MMU_REVISION_REVISION_SHIFT                                                                         (0U)
#define MMU_REVISION_REVISION_MASK                                                                          (0xffffffffU)

#define MMU_SYSCONFIG_AUTOIDLE_SHIFT                                                                        (0U)
#define MMU_SYSCONFIG_AUTOIDLE_MASK                                                                         (0x00000001U)
#define MMU_SYSCONFIG_AUTOIDLE_CLKFREE                                                                       (0U)
#define MMU_SYSCONFIG_AUTOIDLE_AUTOCLKGATE                                                                   (1U)

#define MMU_SYSCONFIG_SOFTRESET_SHIFT                                                                       (1U)
#define MMU_SYSCONFIG_SOFTRESET_MASK                                                                        (0x00000002U)
#define MMU_SYSCONFIG_SOFTRESET_READ0                                                                        (0U)
#define MMU_SYSCONFIG_SOFTRESET_READ1                                                                        (1U)
#define MMU_SYSCONFIG_SOFTRESET_WRITE0                                                                       (0U)
#define MMU_SYSCONFIG_SOFTRESET_WRITE1                                                                       (1U)

#define MMU_SYSCONFIG_RESERVED_SHIFT                                                                        (2U)
#define MMU_SYSCONFIG_RESERVED_MASK                                                                         (0x00000004U)

#define MMU_SYSCONFIG_IDLEMODE_SHIFT                                                                        (3U)
#define MMU_SYSCONFIG_IDLEMODE_MASK                                                                         (0x00000018U)
#define MMU_SYSCONFIG_IDLEMODE_SFIDLE                                                                        (0U)
#define MMU_SYSCONFIG_IDLEMODE_SNIDLE                                                                        (1U)
#define MMU_SYSCONFIG_IDLEMODE_SSIDLE                                                                        (2U)
#define MMU_SYSCONFIG_IDLEMODE_RES                                                                           (3U)

#define MMU_SYSCONFIG_RESERVED2_SHIFT                                                                       (5U)
#define MMU_SYSCONFIG_RESERVED2_MASK                                                                        (0x000000e0U)

#define MMU_SYSCONFIG_CLOCKACTIVITY_SHIFT                                                                   (8U)
#define MMU_SYSCONFIG_CLOCKACTIVITY_MASK                                                                    (0x00000300U)

#define MMU_SYSCONFIG_RESERVED3_SHIFT                                                                       (10U)
#define MMU_SYSCONFIG_RESERVED3_MASK                                                                        (0xfffffc00U)

#define MMU_SYSSTATUS_RESETDONE_SHIFT                                                                       (0U)
#define MMU_SYSSTATUS_RESETDONE_MASK                                                                        (0x00000001U)
#define MMU_SYSSTATUS_RESETDONE_RSTONGOING                                                                   (0U)
#define MMU_SYSSTATUS_RESETDONE_RSTCOMP                                                                      (1U)

#define MMU_SYSSTATUS_RESERVED_SHIFT                                                                        (1U)
#define MMU_SYSSTATUS_RESERVED_MASK                                                                         (0x000000feU)

#define MMU_SYSSTATUS_RESERVED2_SHIFT                                                                       (8U)
#define MMU_SYSSTATUS_RESERVED2_MASK                                                                        (0xffffff00U)

#define MMU_IRQSTATUS_TLBMISS_SHIFT                                                                         (0U)
#define MMU_IRQSTATUS_TLBMISS_MASK                                                                          (0x00000001U)
#define MMU_IRQSTATUS_TLBMISS_READ0                                                                          (0U)
#define MMU_IRQSTATUS_TLBMISS_READ1                                                                          (1U)
#define MMU_IRQSTATUS_TLBMISS_WRITE0                                                                         (0U)
#define MMU_IRQSTATUS_TLBMISS_WRITE1                                                                         (1U)

#define MMU_IRQSTATUS_TRANSLATIONFAULT_SHIFT                                                                (1U)
#define MMU_IRQSTATUS_TRANSLATIONFAULT_MASK                                                                 (0x00000002U)
#define MMU_IRQSTATUS_TRANSLATIONFAULT_READ0                                                                 (0U)
#define MMU_IRQSTATUS_TRANSLATIONFAULT_READ1                                                                 (1U)
#define MMU_IRQSTATUS_TRANSLATIONFAULT_WRITE0                                                                (0U)
#define MMU_IRQSTATUS_TRANSLATIONFAULT_WRITE1                                                                (1U)

#define MMU_IRQSTATUS_EMUMISS_SHIFT                                                                         (2U)
#define MMU_IRQSTATUS_EMUMISS_MASK                                                                          (0x00000004U)
#define MMU_IRQSTATUS_EMUMISS_READ0                                                                          (0U)
#define MMU_IRQSTATUS_EMUMISS_READ1                                                                          (1U)
#define MMU_IRQSTATUS_EMUMISS_WRITE0                                                                         (0U)
#define MMU_IRQSTATUS_EMUMISS_WRITE1                                                                         (1U)

#define MMU_IRQSTATUS_TABLEWALKFAULT_SHIFT                                                                  (3U)
#define MMU_IRQSTATUS_TABLEWALKFAULT_MASK                                                                   (0x00000008U)
#define MMU_IRQSTATUS_TABLEWALKFAULT_READ0                                                                   (0U)
#define MMU_IRQSTATUS_TABLEWALKFAULT_READ1                                                                   (1U)
#define MMU_IRQSTATUS_TABLEWALKFAULT_WRITE0                                                                  (0U)
#define MMU_IRQSTATUS_TABLEWALKFAULT_WRITE1                                                                  (1U)

#define MMU_IRQSTATUS_MULTIHITFAULT_SHIFT                                                                   (4U)
#define MMU_IRQSTATUS_MULTIHITFAULT_MASK                                                                    (0x00000010U)
#define MMU_IRQSTATUS_MULTIHITFAULT_READ0                                                                    (0U)
#define MMU_IRQSTATUS_MULTIHITFAULT_READ1                                                                    (1U)
#define MMU_IRQSTATUS_MULTIHITFAULT_WRITE0                                                                   (0U)
#define MMU_IRQSTATUS_MULTIHITFAULT_WRITE1                                                                   (1U)

#define MMU_IRQSTATUS_RESERVED_SHIFT                                                                        (5U)
#define MMU_IRQSTATUS_RESERVED_MASK                                                                         (0xffffffe0U)

#define MMU_IRQENABLE_TLBMISS_SHIFT                                                                         (0U)
#define MMU_IRQENABLE_TLBMISS_MASK                                                                          (0x00000001U)
#define MMU_IRQENABLE_TLBMISS_TRMISSINTM                                                                     (0U)
#define MMU_IRQENABLE_TLBMISS_TRMISSGINT                                                                     (1U)

#define MMU_IRQENABLE_TRANSLATIONFAULT_SHIFT                                                                (1U)
#define MMU_IRQENABLE_TRANSLATIONFAULT_MASK                                                                 (0x00000002U)
#define MMU_IRQENABLE_TRANSLATIONFAULT_TRANFLTMASK                                                           (0U)
#define MMU_IRQENABLE_TRANSLATIONFAULT_TRANFLTGINT                                                           (1U)

#define MMU_IRQENABLE_EMUMISS_SHIFT                                                                         (2U)
#define MMU_IRQENABLE_EMUMISS_MASK                                                                          (0x00000004U)
#define MMU_IRQENABLE_EMUMISS_EMUMFLTMASK                                                                    (0U)
#define MMU_IRQENABLE_EMUMISS_EMUMFLTGINT                                                                    (1U)

#define MMU_IRQENABLE_TABLEWALKFAULT_SHIFT                                                                  (3U)
#define MMU_IRQENABLE_TABLEWALKFAULT_MASK                                                                   (0x00000008U)
#define MMU_IRQENABLE_TABLEWALKFAULT_TWLFLTMASK                                                              (0U)
#define MMU_IRQENABLE_TABLEWALKFAULT_TWLFLTGINT                                                              (1U)

#define MMU_IRQENABLE_MULTIHITFAULT_SHIFT                                                                   (4U)
#define MMU_IRQENABLE_MULTIHITFAULT_MASK                                                                    (0x00000010U)
#define MMU_IRQENABLE_MULTIHITFAULT_MHFLTMASK                                                                (0U)
#define MMU_IRQENABLE_MULTIHITFAULT_MHFLTGINT                                                                (1U)

#define MMU_IRQENABLE_RESERVED_SHIFT                                                                        (5U)
#define MMU_IRQENABLE_RESERVED_MASK                                                                         (0xffffffe0U)

#define MMU_WALKING_ST_TWLRUNNING_SHIFT                                                                     (0U)
#define MMU_WALKING_ST_TWLRUNNING_MASK                                                                      (0x00000001U)
#define MMU_WALKING_ST_TWLRUNNING_READ0                                                                      (0U)
#define MMU_WALKING_ST_TWLRUNNING_READ1                                                                      (1U)

#define MMU_WALKING_ST_RESERVED_SHIFT                                                                       (1U)
#define MMU_WALKING_ST_RESERVED_MASK                                                                        (0xfffffffeU)

#define MMU_CNTL_RESERVED_SHIFT                                                                             (0U)
#define MMU_CNTL_RESERVED_MASK                                                                              (0x00000001U)

#define MMU_CNTL_MMUENABLE_SHIFT                                                                            (1U)
#define MMU_CNTL_MMUENABLE_MASK                                                                             (0x00000002U)
#define MMU_CNTL_MMUENABLE_MMUDIS                                                                            (0U)
#define MMU_CNTL_MMUENABLE_MMUEN                                                                             (1U)

#define MMU_CNTL_TWLENABLE_SHIFT                                                                            (2U)
#define MMU_CNTL_TWLENABLE_MASK                                                                             (0x00000004U)
#define MMU_CNTL_TWLENABLE_TWLEN                                                                             (1U)
#define MMU_CNTL_TWLENABLE_TWLDIS                                                                            (0U)

#define MMU_CNTL_EMUTLBUPDATE_SHIFT                                                                         (3U)
#define MMU_CNTL_EMUTLBUPDATE_MASK                                                                          (0x00000008U)
#define MMU_CNTL_EMUTLBUPDATE_EMUDIS                                                                         (0U)
#define MMU_CNTL_EMUTLBUPDATE_EMUEN                                                                          (1U)

#define MMU_CNTL_RESERVED2_SHIFT                                                                            (4U)
#define MMU_CNTL_RESERVED2_MASK                                                                             (0xfffffff0U)

#define MMU_FAULT_AD_FAULTADDRESS_SHIFT                                                                     (0U)
#define MMU_FAULT_AD_FAULTADDRESS_MASK                                                                      (0xffffffffU)

#define MMU_TTB_RESERVED_SHIFT                                                                              (0U)
#define MMU_TTB_RESERVED_MASK                                                                               (0x0000007fU)

#define MMU_TTB_TTBADDRESS_SHIFT                                                                            (7U)
#define MMU_TTB_TTBADDRESS_MASK                                                                             (0xffffff80U)

#define MMU_LOCK_RESERVED_SHIFT                                                                             (0U)
#define MMU_LOCK_RESERVED_MASK                                                                              (0x0000000fU)

#define MMU_LOCK_CURRENTVICTIM_SHIFT                                                                        (4U)
#define MMU_LOCK_CURRENTVICTIM_MASK                                                                         (0x000001f0U)

#define MMU_LOCK_RESERVED2_SHIFT                                                                            (9U)
#define MMU_LOCK_RESERVED2_MASK                                                                             (0x00000200U)

#define MMU_LOCK_BASEVALUE_SHIFT                                                                            (10U)
#define MMU_LOCK_BASEVALUE_MASK                                                                             (0x00007c00U)

#define MMU_LOCK_RESERVED3_SHIFT                                                                            (15U)
#define MMU_LOCK_RESERVED3_MASK                                                                             (0xffff8000U)

#define MMU_LD_TLB_LDTLBITEM_SHIFT                                                                          (0U)
#define MMU_LD_TLB_LDTLBITEM_MASK                                                                           (0x00000001U)
#define MMU_LD_TLB_LDTLBITEM_READ0                                                                           (0U)
#define MMU_LD_TLB_LDTLBITEM_READ1                                                                           (1U)
#define MMU_LD_TLB_LDTLBITEM_WRITE0                                                                          (0U)
#define MMU_LD_TLB_LDTLBITEM_WRITE1                                                                          (1U)

#define MMU_LD_TLB_RESERVED_SHIFT                                                                           (1U)
#define MMU_LD_TLB_RESERVED_MASK                                                                            (0xfffffffeU)

#define MMU_CAM_PAGESIZE_SHIFT                                                                              (0U)
#define MMU_CAM_PAGESIZE_MASK                                                                               (0x00000003U)
#define MMU_CAM_PAGESIZE_SECTION                                                                             (0U)
#define MMU_CAM_PAGESIZE_LARGE                                                                               (1U)
#define MMU_CAM_PAGESIZE_SMALL                                                                               (2U)
#define MMU_CAM_PAGESIZE_SUPER                                                                               (3U)

#define MMU_CAM_V_SHIFT                                                                                     (2U)
#define MMU_CAM_V_MASK                                                                                      (0x00000004U)
#define MMU_CAM_V_INVALID                                                                                    (0U)
#define MMU_CAM_V_VALID                                                                                      (1U)

#define MMU_CAM_P_SHIFT                                                                                     (3U)
#define MMU_CAM_P_MASK                                                                                      (0x00000008U)
#define MMU_CAM_P_CANFLUSH                                                                                   (0U)
#define MMU_CAM_P_NOFLUSH                                                                                    (1U)

#define MMU_CAM_RESERVED_SHIFT                                                                              (4U)
#define MMU_CAM_RESERVED_MASK                                                                               (0x00000ff0U)

#define MMU_CAM_VATAG_SHIFT                                                                                 (12U)
#define MMU_CAM_VATAG_MASK                                                                                  (0xfffff000U)

#define MMU_RAM_RESERVED_SHIFT                                                                              (0U)
#define MMU_RAM_RESERVED_MASK                                                                               (0x0000003fU)

#define MMU_RAM_PHYSICALADDRESS_SHIFT                                                                       (12U)
#define MMU_RAM_PHYSICALADDRESS_MASK                                                                        (0xfffff000U)

#define MMU_RAM_MIXED_SHIFT                                                                                 (6U)
#define MMU_RAM_MIXED_MASK                                                                                  (0x00000040U)

#define MMU_RAM_ELEMENTSIZE_SHIFT                                                                           (7U)
#define MMU_RAM_ELEMENTSIZE_MASK                                                                            (0x00000180U)

#define MMU_RAM_ENDIANNESS_SHIFT                                                                            (9U)
#define MMU_RAM_ENDIANNESS_MASK                                                                             (0x00000200U)

#define MMU_RAM_RESERVED1_SHIFT                                                                             (10U)
#define MMU_RAM_RESERVED1_MASK                                                                              (0x00000c00U)

#define MMU_GFLUSH_GLOBALFLUSH_SHIFT                                                                        (0U)
#define MMU_GFLUSH_GLOBALFLUSH_MASK                                                                         (0x00000001U)
#define MMU_GFLUSH_GLOBALFLUSH_READ0                                                                         (0U)
#define MMU_GFLUSH_GLOBALFLUSH_READ1                                                                         (1U)
#define MMU_GFLUSH_GLOBALFLUSH_WRITE0                                                                        (0U)
#define MMU_GFLUSH_GLOBALFLUSH_WRITE1                                                                        (1U)

#define MMU_GFLUSH_RESERVED_SHIFT                                                                           (1U)
#define MMU_GFLUSH_RESERVED_MASK                                                                            (0xfffffffeU)

#define MMU_FLUSH_ENTRY_FLUSHENTRY_SHIFT                                                                    (0U)
#define MMU_FLUSH_ENTRY_FLUSHENTRY_MASK                                                                     (0x00000001U)
#define MMU_FLUSH_ENTRY_FLUSHENTRY_READ0                                                                     (0U)
#define MMU_FLUSH_ENTRY_FLUSHENTRY_READ1                                                                     (1U)
#define MMU_FLUSH_ENTRY_FLUSHENTRY_WRITE0                                                                    (0U)
#define MMU_FLUSH_ENTRY_FLUSHENTRY_WRITE1                                                                    (1U)

#define MMU_FLUSH_ENTRY_RESERVED_SHIFT                                                                      (1U)
#define MMU_FLUSH_ENTRY_RESERVED_MASK                                                                       (0xfffffffeU)

#define MMU_READ_CAM_PAGESIZE_SHIFT                                                                         (0U)
#define MMU_READ_CAM_PAGESIZE_MASK                                                                          (0x00000003U)
#define MMU_READ_CAM_PAGESIZE_SECTION                                                                        (0U)
#define MMU_READ_CAM_PAGESIZE_LARGE                                                                          (1U)
#define MMU_READ_CAM_PAGESIZE_SMALL                                                                          (2U)
#define MMU_READ_CAM_PAGESIZE_SUPER                                                                          (3U)

#define MMU_READ_CAM_V_SHIFT                                                                                (2U)
#define MMU_READ_CAM_V_MASK                                                                                 (0x00000004U)
#define MMU_READ_CAM_V_INVALID                                                                               (0U)
#define MMU_READ_CAM_V_VALID                                                                                 (1U)

#define MMU_READ_CAM_P_SHIFT                                                                                (3U)
#define MMU_READ_CAM_P_MASK                                                                                 (0x00000008U)
#define MMU_READ_CAM_P_CANFLUSH                                                                              (0U)
#define MMU_READ_CAM_P_NOFLUSH                                                                               (1U)

#define MMU_READ_CAM_RESERVED_SHIFT                                                                         (4U)
#define MMU_READ_CAM_RESERVED_MASK                                                                          (0x00000ff0U)

#define MMU_READ_CAM_VATAG_SHIFT                                                                            (12U)
#define MMU_READ_CAM_VATAG_MASK                                                                             (0xfffff000U)

#define MMU_READ_RAM_RESERVED_SHIFT                                                                         (0U)
#define MMU_READ_RAM_RESERVED_MASK                                                                          (0x0000003fU)

#define MMU_READ_RAM_PHYSICALADDRESS_SHIFT                                                                  (12U)
#define MMU_READ_RAM_PHYSICALADDRESS_MASK                                                                   (0xfffff000U)

#define MMU_READ_RAM_MIXED_SHIFT                                                                            (6U)
#define MMU_READ_RAM_MIXED_MASK                                                                             (0x00000040U)

#define MMU_READ_RAM_ELEMENTSIZE_SHIFT                                                                      (7U)
#define MMU_READ_RAM_ELEMENTSIZE_MASK                                                                       (0x00000180U)

#define MMU_READ_RAM_ENDIANESS_SHIFT                                                                        (9U)
#define MMU_READ_RAM_ENDIANESS_MASK                                                                         (0x00000200U)

#define MMU_READ_RAM_RESERVED1_SHIFT                                                                        (10U)
#define MMU_READ_RAM_RESERVED1_MASK                                                                         (0x00000c00U)

#define MMU_EMU_FAULT_AD_EMUFAULTADDRESS_SHIFT                                                              (0U)
#define MMU_EMU_FAULT_AD_EMUFAULTADDRESS_MASK                                                               (0xffffffffU)

#define MMU_FAULT_PC_PC_SHIFT                                                                               (0U)
#define MMU_FAULT_PC_PC_MASK                                                                                (0xffffffffU)

#define MMU_FAULT_STATUS_FAULTINDICATION_SHIFT                                                              (0U)
#define MMU_FAULT_STATUS_FAULTINDICATION_MASK                                                               (0x00000001U)

#define MMU_FAULT_STATUS_MMU_FAULT_TYPE_SHIFT                                                               (1U)
#define MMU_FAULT_STATUS_MMU_FAULT_TYPE_MASK                                                                (0x00000006U)

#define MMU_FAULT_STATUS_RD_WR_SHIFT                                                                        (3U)
#define MMU_FAULT_STATUS_RD_WR_MASK                                                                         (0x00000008U)

#define MMU_FAULT_STATUS_MMU_FAULT_TRANS_ID_SHIFT                                                           (4U)
#define MMU_FAULT_STATUS_MMU_FAULT_TRANS_ID_MASK                                                            (0x000000f0U)

#define MMU_FAULT_STATUS_RESERVED_SHIFT                                                                     (8U)
#define MMU_FAULT_STATUS_RESERVED_MASK                                                                      (0x7fffff00U)

#define MMU_GP_REG_BUS_ERR_BACK_EN_SHIFT                                                                    (0U)
#define MMU_GP_REG_BUS_ERR_BACK_EN_MASK                                                                     (0x00000001U)
#define MMU_GP_REG_BUS_ERR_BACK_EN_DEFAULT                                                                   (0U)
#define MMU_GP_REG_BUS_ERR_BACK_EN_ALL                                                                       (1U)

#define MMU_GP_REG_RESERVED_SHIFT                                                                           (1U)
#define MMU_GP_REG_RESERVED_MASK                                                                            (0xfffffffeU)

#define MMU_DSPSS_GPR_HWDEBUG_MUX_SHIFT                                                                     (0U)
#define MMU_DSPSS_GPR_HWDEBUG_MUX_MASK                                                                      (0x0000000fU)

#define MMU_DSPSS_GPR_RESERVED_SHIFT                                                                        (4U)
#define MMU_DSPSS_GPR_RESERVED_MASK                                                                         (0x00007ff0U)

#define MMU_DSPSS_GPR_FORCE_IDLE_REQ_SHIFT                                                                  (15U)
#define MMU_DSPSS_GPR_FORCE_IDLE_REQ_MASK                                                                   (0x00008000U)

#define MMU_DSPSS_GPR_RESERVED1_SHIFT                                                                       (16U)
#define MMU_DSPSS_GPR_RESERVED1_MASK                                                                        (0xffff0000U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_MMU_H_ */
