/******************************************************************************
*
* hw_mpu_intc_virthyp.h - register-level header file for MPU
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
#ifndef HW_MPU_INTC_VIRTHYP_H_
#define HW_MPU_INTC_VIRTHYP_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define MPU_GICH_HCR                                                                                        (0x0U)
#define MPU_GICH_VTR                                                                                        (0x4U)
#define MPU_GICH_VMCR                                                                                       (0x8U)
#define MPU_GICH_MISR                                                                                       (0x10U)
#define MPU_GICH_EISR0                                                                                      (0x20U)
#define MPU_GICH_ELSR0                                                                                      (0x30U)
#define MPU_GICH_APR0                                                                                       (0xf0U)
#define MPU_GICH_LR0                                                                                        (0x100U)
#define MPU_GICH_LR1                                                                                        (0x104U)
#define MPU_GICH_LR2                                                                                        (0x108U)
#define MPU_GICH_LR3                                                                                        (0x10cU)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define MPU_GICH_HCR_EOICOUNT_SHIFT                                                                         (27U)
#define MPU_GICH_HCR_EOICOUNT_MASK                                                                          (0xf8000000U)

#define MPU_GICH_HCR_VDNSIE_SHIFT                                                                           (7U)
#define MPU_GICH_HCR_VDNSIE_MASK                                                                            (0x00000080U)

#define MPU_GICH_HCR_VENSIE_SHIFT                                                                           (6U)
#define MPU_GICH_HCR_VENSIE_MASK                                                                            (0x00000040U)

#define MPU_GICH_HCR_VDSIE_SHIFT                                                                            (5U)
#define MPU_GICH_HCR_VDSIE_MASK                                                                             (0x00000020U)

#define MPU_GICH_HCR_VESIE_SHIFT                                                                            (4U)
#define MPU_GICH_HCR_VESIE_MASK                                                                             (0x00000010U)

#define MPU_GICH_HCR_NPIE_SHIFT                                                                             (3U)
#define MPU_GICH_HCR_NPIE_MASK                                                                              (0x00000008U)

#define MPU_GICH_HCR_SKIDIE_SHIFT                                                                           (2U)
#define MPU_GICH_HCR_SKIDIE_MASK                                                                            (0x00000004U)

#define MPU_GICH_HCR_UIE_SHIFT                                                                              (1U)
#define MPU_GICH_HCR_UIE_MASK                                                                               (0x00000002U)

#define MPU_GICH_HCR_EN_SHIFT                                                                               (0U)
#define MPU_GICH_HCR_EN_MASK                                                                                (0x00000001U)

#define MPU_GICH_HCR_RESERVED_SHIFT                                                                         (8U)
#define MPU_GICH_HCR_RESERVED_MASK                                                                          (0x07ffff00U)

#define MPU_GICH_VTR_LISTREGS_SHIFT                                                                         (0U)
#define MPU_GICH_VTR_LISTREGS_MASK                                                                          (0x0000003fU)

#define MPU_GICH_VTR_PREBITS_SHIFT                                                                          (26U)
#define MPU_GICH_VTR_PREBITS_MASK                                                                           (0x1c000000U)

#define MPU_GICH_VTR_PRIBITS_SHIFT                                                                          (29U)
#define MPU_GICH_VTR_PRIBITS_MASK                                                                           (0xe0000000U)

#define MPU_GICH_VTR_RESERVED_SHIFT                                                                         (6U)
#define MPU_GICH_VTR_RESERVED_MASK                                                                          (0x03ffffc0U)

#define MPU_GICH_VMCR_VMSEN_SHIFT                                                                           (0U)
#define MPU_GICH_VMCR_VMSEN_MASK                                                                            (0x00000001U)

#define MPU_GICH_VMCR_VMNSEN_SHIFT                                                                          (1U)
#define MPU_GICH_VMCR_VMNSEN_MASK                                                                           (0x00000002U)

#define MPU_GICH_VMCR_VMACKCTL_SHIFT                                                                        (2U)
#define MPU_GICH_VMCR_VMACKCTL_MASK                                                                         (0x00000004U)

#define MPU_GICH_VMCR_VMFIQEN_SHIFT                                                                         (3U)
#define MPU_GICH_VMCR_VMFIQEN_MASK                                                                          (0x00000008U)

#define MPU_GICH_VMCR_VMSBPR_SHIFT                                                                          (4U)
#define MPU_GICH_VMCR_VMSBPR_MASK                                                                           (0x00000010U)

#define MPU_GICH_VMCR_VEM_SHIFT                                                                             (9U)
#define MPU_GICH_VMCR_VEM_MASK                                                                              (0x00000200U)

#define MPU_GICH_VMCR_RESERVED_SHIFT                                                                        (5U)
#define MPU_GICH_VMCR_RESERVED_MASK                                                                         (0x000001e0U)

#define MPU_GICH_VMCR_RESERVED1_SHIFT                                                                       (24U)
#define MPU_GICH_VMCR_RESERVED1_MASK                                                                        (0x07000000U)

#define MPU_GICH_VMCR_VMNSBP_SHIFT                                                                          (18U)
#define MPU_GICH_VMCR_VMNSBP_MASK                                                                           (0x001c0000U)

#define MPU_GICH_VMCR_VMBP_SHIFT                                                                            (21U)
#define MPU_GICH_VMCR_VMBP_MASK                                                                             (0x00e00000U)

#define MPU_GICH_VMCR_VMPRIMASK_SHIFT                                                                       (27U)
#define MPU_GICH_VMCR_VMPRIMASK_MASK                                                                        (0xf8000000U)

#define MPU_GICH_VMCR_RESERVED2_SHIFT                                                                       (10U)
#define MPU_GICH_VMCR_RESERVED2_MASK                                                                        (0x0003fc00U)

#define MPU_GICH_MISR_RESERVED_SHIFT                                                                        (8U)
#define MPU_GICH_MISR_RESERVED_MASK                                                                         (0xffffff00U)

#define MPU_GICH_MISR_EI_SHIFT                                                                              (0U)
#define MPU_GICH_MISR_EI_MASK                                                                               (0x00000001U)

#define MPU_GICH_MISR_UI_SHIFT                                                                              (1U)
#define MPU_GICH_MISR_UI_MASK                                                                               (0x00000002U)

#define MPU_GICH_MISR_SKDI_SHIFT                                                                            (2U)
#define MPU_GICH_MISR_SKDI_MASK                                                                             (0x00000004U)

#define MPU_GICH_MISR_NPI_SHIFT                                                                             (3U)
#define MPU_GICH_MISR_NPI_MASK                                                                              (0x00000008U)

#define MPU_GICH_MISR_VESI_SHIFT                                                                            (4U)
#define MPU_GICH_MISR_VESI_MASK                                                                             (0x00000010U)

#define MPU_GICH_MISR_VDSI_SHIFT                                                                            (5U)
#define MPU_GICH_MISR_VDSI_MASK                                                                             (0x00000020U)

#define MPU_GICH_MISR_VENSI_SHIFT                                                                           (6U)
#define MPU_GICH_MISR_VENSI_MASK                                                                            (0x00000040U)

#define MPU_GICH_MISR_VDNSI_SHIFT                                                                           (7U)
#define MPU_GICH_MISR_VDNSI_MASK                                                                            (0x00000080U)

#define MPU_GICH_EISR0_LR0_SHIFT                                                                            (0U)
#define MPU_GICH_EISR0_LR0_MASK                                                                             (0x00000001U)

#define MPU_GICH_EISR0_LR1_SHIFT                                                                            (1U)
#define MPU_GICH_EISR0_LR1_MASK                                                                             (0x00000002U)

#define MPU_GICH_EISR0_LR2_SHIFT                                                                            (2U)
#define MPU_GICH_EISR0_LR2_MASK                                                                             (0x00000004U)

#define MPU_GICH_EISR0_LR3_SHIFT                                                                            (3U)
#define MPU_GICH_EISR0_LR3_MASK                                                                             (0x00000008U)

#define MPU_GICH_EISR0_RESERVED_SHIFT                                                                       (4U)
#define MPU_GICH_EISR0_RESERVED_MASK                                                                        (0xfffffff0U)

#define MPU_GICH_ELSR0_LR0_SHIFT                                                                            (0U)
#define MPU_GICH_ELSR0_LR0_MASK                                                                             (0x00000001U)

#define MPU_GICH_ELSR0_LR1_SHIFT                                                                            (1U)
#define MPU_GICH_ELSR0_LR1_MASK                                                                             (0x00000002U)

#define MPU_GICH_ELSR0_LR2_SHIFT                                                                            (2U)
#define MPU_GICH_ELSR0_LR2_MASK                                                                             (0x00000004U)

#define MPU_GICH_ELSR0_LR3_SHIFT                                                                            (3U)
#define MPU_GICH_ELSR0_LR3_MASK                                                                             (0x00000008U)

#define MPU_GICH_ELSR0_RESERVED_SHIFT                                                                       (4U)
#define MPU_GICH_ELSR0_RESERVED_MASK                                                                        (0xfffffff0U)

#define MPU_GICH_APR0_AP0_SHIFT                                                                             (0U)
#define MPU_GICH_APR0_AP0_MASK                                                                              (0x00000001U)

#define MPU_GICH_APR0_AP1_SHIFT                                                                             (1U)
#define MPU_GICH_APR0_AP1_MASK                                                                              (0x00000002U)

#define MPU_GICH_APR0_AP2_SHIFT                                                                             (2U)
#define MPU_GICH_APR0_AP2_MASK                                                                              (0x00000004U)

#define MPU_GICH_APR0_AP3_SHIFT                                                                             (3U)
#define MPU_GICH_APR0_AP3_MASK                                                                              (0x00000008U)

#define MPU_GICH_APR0_AP4_SHIFT                                                                             (4U)
#define MPU_GICH_APR0_AP4_MASK                                                                              (0x00000010U)

#define MPU_GICH_APR0_AP5_SHIFT                                                                             (5U)
#define MPU_GICH_APR0_AP5_MASK                                                                              (0x00000020U)

#define MPU_GICH_APR0_AP6_SHIFT                                                                             (6U)
#define MPU_GICH_APR0_AP6_MASK                                                                              (0x00000040U)

#define MPU_GICH_APR0_AP7_SHIFT                                                                             (7U)
#define MPU_GICH_APR0_AP7_MASK                                                                              (0x00000080U)

#define MPU_GICH_APR0_AP8_SHIFT                                                                             (8U)
#define MPU_GICH_APR0_AP8_MASK                                                                              (0x00000100U)

#define MPU_GICH_APR0_AP9_SHIFT                                                                             (9U)
#define MPU_GICH_APR0_AP9_MASK                                                                              (0x00000200U)

#define MPU_GICH_APR0_AP10_SHIFT                                                                            (10U)
#define MPU_GICH_APR0_AP10_MASK                                                                             (0x00000400U)

#define MPU_GICH_APR0_AP11_SHIFT                                                                            (11U)
#define MPU_GICH_APR0_AP11_MASK                                                                             (0x00000800U)

#define MPU_GICH_APR0_AP12_SHIFT                                                                            (12U)
#define MPU_GICH_APR0_AP12_MASK                                                                             (0x00001000U)

#define MPU_GICH_APR0_AP13_SHIFT                                                                            (13U)
#define MPU_GICH_APR0_AP13_MASK                                                                             (0x00002000U)

#define MPU_GICH_APR0_AP14_SHIFT                                                                            (14U)
#define MPU_GICH_APR0_AP14_MASK                                                                             (0x00004000U)

#define MPU_GICH_APR0_AP15_SHIFT                                                                            (15U)
#define MPU_GICH_APR0_AP15_MASK                                                                             (0x00008000U)

#define MPU_GICH_APR0_AP16_SHIFT                                                                            (16U)
#define MPU_GICH_APR0_AP16_MASK                                                                             (0x00010000U)

#define MPU_GICH_APR0_AP17_SHIFT                                                                            (17U)
#define MPU_GICH_APR0_AP17_MASK                                                                             (0x00020000U)

#define MPU_GICH_APR0_AP18_SHIFT                                                                            (18U)
#define MPU_GICH_APR0_AP18_MASK                                                                             (0x00040000U)

#define MPU_GICH_APR0_AP19_SHIFT                                                                            (19U)
#define MPU_GICH_APR0_AP19_MASK                                                                             (0x00080000U)

#define MPU_GICH_APR0_AP20_SHIFT                                                                            (20U)
#define MPU_GICH_APR0_AP20_MASK                                                                             (0x00100000U)

#define MPU_GICH_APR0_AP21_SHIFT                                                                            (21U)
#define MPU_GICH_APR0_AP21_MASK                                                                             (0x00200000U)

#define MPU_GICH_APR0_AP22_SHIFT                                                                            (22U)
#define MPU_GICH_APR0_AP22_MASK                                                                             (0x00400000U)

#define MPU_GICH_APR0_AP23_SHIFT                                                                            (23U)
#define MPU_GICH_APR0_AP23_MASK                                                                             (0x00800000U)

#define MPU_GICH_APR0_AP24_SHIFT                                                                            (24U)
#define MPU_GICH_APR0_AP24_MASK                                                                             (0x01000000U)

#define MPU_GICH_APR0_AP25_SHIFT                                                                            (25U)
#define MPU_GICH_APR0_AP25_MASK                                                                             (0x02000000U)

#define MPU_GICH_APR0_AP26_SHIFT                                                                            (26U)
#define MPU_GICH_APR0_AP26_MASK                                                                             (0x04000000U)

#define MPU_GICH_APR0_AP27_SHIFT                                                                            (27U)
#define MPU_GICH_APR0_AP27_MASK                                                                             (0x08000000U)

#define MPU_GICH_APR0_AP28_SHIFT                                                                            (28U)
#define MPU_GICH_APR0_AP28_MASK                                                                             (0x10000000U)

#define MPU_GICH_APR0_AP29_SHIFT                                                                            (29U)
#define MPU_GICH_APR0_AP29_MASK                                                                             (0x20000000U)

#define MPU_GICH_APR0_AP30_SHIFT                                                                            (30U)
#define MPU_GICH_APR0_AP30_MASK                                                                             (0x40000000U)

#define MPU_GICH_APR0_AP31_SHIFT                                                                            (31U)
#define MPU_GICH_APR0_AP31_MASK                                                                             (0x80000000U)

#define MPU_GICH_LR0_HW_SHIFT                                                                               (31U)
#define MPU_GICH_LR0_HW_MASK                                                                                (0x80000000U)

#define MPU_GICH_LR0_NS_SHIFT                                                                               (30U)
#define MPU_GICH_LR0_NS_MASK                                                                                (0x40000000U)

#define MPU_GICH_LR0_STATE_SHIFT                                                                            (28U)
#define MPU_GICH_LR0_STATE_MASK                                                                             (0x30000000U)

#define MPU_GICH_LR0_PRIORITY_SHIFT                                                                         (23U)
#define MPU_GICH_LR0_PRIORITY_MASK                                                                          (0x0f800000U)

#define MPU_GICH_LR0_PHYSICALID_SHIFT                                                                       (10U)
#define MPU_GICH_LR0_PHYSICALID_MASK                                                                        (0x000ffc00U)

#define MPU_GICH_LR0_VIRTUALNUMBER_SHIFT                                                                    (0U)
#define MPU_GICH_LR0_VIRTUALNUMBER_MASK                                                                     (0x000003ffU)

#define MPU_GICH_LR0_RESERVED_SHIFT                                                                         (20U)
#define MPU_GICH_LR0_RESERVED_MASK                                                                          (0x00700000U)

#define MPU_GICH_LR1_HW_SHIFT                                                                               (31U)
#define MPU_GICH_LR1_HW_MASK                                                                                (0x80000000U)

#define MPU_GICH_LR1_NS_SHIFT                                                                               (30U)
#define MPU_GICH_LR1_NS_MASK                                                                                (0x40000000U)

#define MPU_GICH_LR1_STATE_SHIFT                                                                            (28U)
#define MPU_GICH_LR1_STATE_MASK                                                                             (0x30000000U)

#define MPU_GICH_LR1_PRIORITY_SHIFT                                                                         (23U)
#define MPU_GICH_LR1_PRIORITY_MASK                                                                          (0x0f800000U)

#define MPU_GICH_LR1_PHYSICALID_SHIFT                                                                       (10U)
#define MPU_GICH_LR1_PHYSICALID_MASK                                                                        (0x000ffc00U)

#define MPU_GICH_LR1_VIRTUALNUMBER_SHIFT                                                                    (0U)
#define MPU_GICH_LR1_VIRTUALNUMBER_MASK                                                                     (0x000003ffU)

#define MPU_GICH_LR1_RESERVED_SHIFT                                                                         (20U)
#define MPU_GICH_LR1_RESERVED_MASK                                                                          (0x00700000U)

#define MPU_GICH_LR2_HW_SHIFT                                                                               (31U)
#define MPU_GICH_LR2_HW_MASK                                                                                (0x80000000U)

#define MPU_GICH_LR2_NS_SHIFT                                                                               (30U)
#define MPU_GICH_LR2_NS_MASK                                                                                (0x40000000U)

#define MPU_GICH_LR2_STATE_SHIFT                                                                            (28U)
#define MPU_GICH_LR2_STATE_MASK                                                                             (0x30000000U)

#define MPU_GICH_LR2_PRIORITY_SHIFT                                                                         (23U)
#define MPU_GICH_LR2_PRIORITY_MASK                                                                          (0x0f800000U)

#define MPU_GICH_LR2_PHYSICALID_SHIFT                                                                       (10U)
#define MPU_GICH_LR2_PHYSICALID_MASK                                                                        (0x000ffc00U)

#define MPU_GICH_LR2_VIRTUALNUMBER_SHIFT                                                                    (0U)
#define MPU_GICH_LR2_VIRTUALNUMBER_MASK                                                                     (0x000003ffU)

#define MPU_GICH_LR2_RESERVED_SHIFT                                                                         (20U)
#define MPU_GICH_LR2_RESERVED_MASK                                                                          (0x00700000U)

#define MPU_GICH_LR3_HW_SHIFT                                                                               (31U)
#define MPU_GICH_LR3_HW_MASK                                                                                (0x80000000U)

#define MPU_GICH_LR3_NS_SHIFT                                                                               (30U)
#define MPU_GICH_LR3_NS_MASK                                                                                (0x40000000U)

#define MPU_GICH_LR3_STATE_SHIFT                                                                            (28U)
#define MPU_GICH_LR3_STATE_MASK                                                                             (0x30000000U)

#define MPU_GICH_LR3_PRIORITY_SHIFT                                                                         (23U)
#define MPU_GICH_LR3_PRIORITY_MASK                                                                          (0x0f800000U)

#define MPU_GICH_LR3_PHYSICALID_SHIFT                                                                       (10U)
#define MPU_GICH_LR3_PHYSICALID_MASK                                                                        (0x000ffc00U)

#define MPU_GICH_LR3_VIRTUALNUMBER_SHIFT                                                                    (0U)
#define MPU_GICH_LR3_VIRTUALNUMBER_MASK                                                                     (0x000003ffU)

#define MPU_GICH_LR3_RESERVED_SHIFT                                                                         (20U)
#define MPU_GICH_LR3_RESERVED_MASK                                                                          (0x00700000U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_MPU_INTC_VIRTHYP_H_ */
