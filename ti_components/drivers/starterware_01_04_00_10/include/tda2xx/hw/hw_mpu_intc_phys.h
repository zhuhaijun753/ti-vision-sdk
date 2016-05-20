/******************************************************************************
*
* hw_mpu_intc_phys.h - register-level header file for MPU
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
#ifndef HW_MPU_INTC_PHYS_H_
#define HW_MPU_INTC_PHYS_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define MPU_GICC_ICR                                                                                        (0x0U)
#define MPU_GICC_PMR                                                                                        (0x4U)
#define MPU_GICC_BPR                                                                                        (0x8U)
#define MPU_GICC_IAR                                                                                        (0xcU)
#define MPU_GICC_EOIR                                                                                       (0x10U)
#define MPU_GICC_RPR                                                                                        (0x14U)
#define MPU_GICC_HPIR                                                                                       (0x18U)
#define MPU_GICC_ABPR                                                                                       (0x1cU)
#define MPU_GICC_AIAR                                                                                       (0x20U)
#define MPU_GICC_AEOIR                                                                                      (0x24U)
#define MPU_GICC_AHPPIR                                                                                     (0x28U)
#define MPU_GICC_APR0                                                                                       (0xd0U)
#define MPU_GICC_NSAPR0                                                                                     (0xe0U)
#define MPU_GICC_IIDR                                                                                       (0xfcU)
#define MPU_GICC_DIR                                                                                        (0x1000U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define MPU_GICC_ICR_RESERVED_SHIFT                                                                         (11U)
#define MPU_GICC_ICR_RESERVED_MASK                                                                          (0xfffff800U)

#define MPU_GICC_ICR_ENABLES_SHIFT                                                                          (0U)
#define MPU_GICC_ICR_ENABLES_MASK                                                                           (0x00000001U)

#define MPU_GICC_ICR_ENABLENS_SHIFT                                                                         (1U)
#define MPU_GICC_ICR_ENABLENS_MASK                                                                          (0x00000002U)

#define MPU_GICC_ICR_ACKCTL_SHIFT                                                                           (2U)
#define MPU_GICC_ICR_ACKCTL_MASK                                                                            (0x00000004U)

#define MPU_GICC_ICR_FIQEN_SHIFT                                                                            (3U)
#define MPU_GICC_ICR_FIQEN_MASK                                                                             (0x00000008U)

#define MPU_GICC_ICR_SBPR_SHIFT                                                                             (4U)
#define MPU_GICC_ICR_SBPR_MASK                                                                              (0x00000010U)

#define MPU_GICC_ICR_FIQBYPDISABLE_SHIFT                                                                    (5U)
#define MPU_GICC_ICR_FIQBYPDISABLE_MASK                                                                     (0x00000020U)

#define MPU_GICC_ICR_IRQBYPDISABLE_SHIFT                                                                    (6U)
#define MPU_GICC_ICR_IRQBYPDISABLE_MASK                                                                     (0x00000040U)

#define MPU_GICC_ICR_FIQBYPDISNS_SHIFT                                                                      (7U)
#define MPU_GICC_ICR_FIQBYPDISNS_MASK                                                                       (0x00000080U)

#define MPU_GICC_ICR_IRQBYPDISNS_SHIFT                                                                      (8U)
#define MPU_GICC_ICR_IRQBYPDISNS_MASK                                                                       (0x00000100U)

#define MPU_GICC_ICR_EOIMODE_SHIFT                                                                          (9U)
#define MPU_GICC_ICR_EOIMODE_MASK                                                                           (0x00000200U)

#define MPU_GICC_ICR_EOIMODENS_SHIFT                                                                        (10U)
#define MPU_GICC_ICR_EOIMODENS_MASK                                                                         (0x00000400U)

#define MPU_GICC_PMR_PRIORITY_SHIFT                                                                         (3U)
#define MPU_GICC_PMR_PRIORITY_MASK                                                                          (uint32_t)(0x000000f8U)

#define MPU_GICC_PMR_RESERVED_SHIFT                                                                         (8U)
#define MPU_GICC_PMR_RESERVED_MASK                                                                          (0xffffff00U)

#define MPU_GICC_PMR_RESERVED1_SHIFT                                                                        (0U)
#define MPU_GICC_PMR_RESERVED1_MASK                                                                         (0x00000007U)

#define MPU_GICC_BPR_BINARYPOINT_SHIFT                                                                      (0U)
#define MPU_GICC_BPR_BINARYPOINT_MASK                                                                       (0x00000007U)

#define MPU_GICC_BPR_RESERVED_SHIFT                                                                         (3U)
#define MPU_GICC_BPR_RESERVED_MASK                                                                          (0xfffffff8U)

#define MPU_GICC_IAR_ACKINTID_SHIFT                                                                         (0U)
#define MPU_GICC_IAR_ACKINTID_MASK                                                                          (0x000003ffU)

#define MPU_GICC_IAR_RESERVED_SHIFT                                                                         (13U)
#define MPU_GICC_IAR_RESERVED_MASK                                                                          (0xffffe000U)

#define MPU_GICC_IAR_CPUID_SHIFT                                                                            (10U)
#define MPU_GICC_IAR_CPUID_MASK                                                                             (0x00001c00U)

#define MPU_GICC_EOIR_EOIINTID_SHIFT                                                                        (0U)
#define MPU_GICC_EOIR_EOIINTID_MASK                                                                         (0x000003ffU)

#define MPU_GICC_EOIR_CPUID_SHIFT                                                                           (10U)
#define MPU_GICC_EOIR_CPUID_MASK                                                                            (0x00001c00U)

#define MPU_GICC_EOIR_RESERVED_SHIFT                                                                        (13U)
#define MPU_GICC_EOIR_RESERVED_MASK                                                                         (0xffffe000U)

#define MPU_GICC_RPR_RESERVED_SHIFT                                                                         (8U)
#define MPU_GICC_RPR_RESERVED_MASK                                                                          (0xffffff00U)

#define MPU_GICC_RPR_PRIORITY_SHIFT                                                                         (0U)
#define MPU_GICC_RPR_PRIORITY_MASK                                                                          (0x000000ffU)

#define MPU_GICC_HPIR_RESERVED_SHIFT                                                                        (13U)
#define MPU_GICC_HPIR_RESERVED_MASK                                                                         (0xffffe000U)

#define MPU_GICC_HPIR_CPUID_SHIFT                                                                           (10U)
#define MPU_GICC_HPIR_CPUID_MASK                                                                            (uint32_t)(0x00001c00U)

#define MPU_GICC_HPIR_PENDINTID_SHIFT                                                                       (0U)
#define MPU_GICC_HPIR_PENDINTID_MASK                                                                        (uint32_t)(0x000003ffU)

#define MPU_GICC_ABPR_RESERVED_SHIFT                                                                        (3U)
#define MPU_GICC_ABPR_RESERVED_MASK                                                                         (0xfffffff8U)

#define MPU_GICC_ABPR_BINARYPOINT_SHIFT                                                                     (0U)
#define MPU_GICC_ABPR_BINARYPOINT_MASK                                                                      (0x00000007U)

#define MPU_GICC_AIAR_ACKINTID_SHIFT                                                                        (0U)
#define MPU_GICC_AIAR_ACKINTID_MASK                                                                         (0x000003ffU)

#define MPU_GICC_AIAR_RESERVED_SHIFT                                                                        (13U)
#define MPU_GICC_AIAR_RESERVED_MASK                                                                         (0xffffe000U)

#define MPU_GICC_AIAR_CPUID_SHIFT                                                                           (10U)
#define MPU_GICC_AIAR_CPUID_MASK                                                                            (0x00001c00U)

#define MPU_GICC_AEOIR_EOIINTID_SHIFT                                                                       (0U)
#define MPU_GICC_AEOIR_EOIINTID_MASK                                                                        (0x000003ffU)

#define MPU_GICC_AEOIR_CPUID_SHIFT                                                                          (10U)
#define MPU_GICC_AEOIR_CPUID_MASK                                                                           (0x00001c00U)

#define MPU_GICC_AEOIR_RESERVED_SHIFT                                                                       (13U)
#define MPU_GICC_AEOIR_RESERVED_MASK                                                                        (0xffffe000U)

#define MPU_GICC_AHPPIR_RESERVED_SHIFT                                                                      (13U)
#define MPU_GICC_AHPPIR_RESERVED_MASK                                                                       (0xffffe000U)

#define MPU_GICC_AHPPIR_CPUID_SHIFT                                                                         (10U)
#define MPU_GICC_AHPPIR_CPUID_MASK                                                                          (0x00001c00U)

#define MPU_GICC_AHPPIR_PENDINTID_SHIFT                                                                     (0U)
#define MPU_GICC_AHPPIR_PENDINTID_MASK                                                                      (0x000003ffU)

#define MPU_GICC_APR0_AP0_SHIFT                                                                             (0U)
#define MPU_GICC_APR0_AP0_MASK                                                                              (0x00000001U)

#define MPU_GICC_APR0_AP1_SHIFT                                                                             (1U)
#define MPU_GICC_APR0_AP1_MASK                                                                              (0x00000002U)

#define MPU_GICC_APR0_AP2_SHIFT                                                                             (2U)
#define MPU_GICC_APR0_AP2_MASK                                                                              (0x00000004U)

#define MPU_GICC_APR0_AP3_SHIFT                                                                             (3U)
#define MPU_GICC_APR0_AP3_MASK                                                                              (0x00000008U)

#define MPU_GICC_APR0_AP4_SHIFT                                                                             (4U)
#define MPU_GICC_APR0_AP4_MASK                                                                              (0x00000010U)

#define MPU_GICC_APR0_AP5_SHIFT                                                                             (5U)
#define MPU_GICC_APR0_AP5_MASK                                                                              (0x00000020U)

#define MPU_GICC_APR0_AP6_SHIFT                                                                             (6U)
#define MPU_GICC_APR0_AP6_MASK                                                                              (0x00000040U)

#define MPU_GICC_APR0_AP7_SHIFT                                                                             (7U)
#define MPU_GICC_APR0_AP7_MASK                                                                              (0x00000080U)

#define MPU_GICC_APR0_AP8_SHIFT                                                                             (8U)
#define MPU_GICC_APR0_AP8_MASK                                                                              (0x00000100U)

#define MPU_GICC_APR0_AP9_SHIFT                                                                             (9U)
#define MPU_GICC_APR0_AP9_MASK                                                                              (0x00000200U)

#define MPU_GICC_APR0_AP10_SHIFT                                                                            (10U)
#define MPU_GICC_APR0_AP10_MASK                                                                             (0x00000400U)

#define MPU_GICC_APR0_AP11_SHIFT                                                                            (11U)
#define MPU_GICC_APR0_AP11_MASK                                                                             (0x00000800U)

#define MPU_GICC_APR0_AP12_SHIFT                                                                            (12U)
#define MPU_GICC_APR0_AP12_MASK                                                                             (0x00001000U)

#define MPU_GICC_APR0_AP13_SHIFT                                                                            (13U)
#define MPU_GICC_APR0_AP13_MASK                                                                             (0x00002000U)

#define MPU_GICC_APR0_AP14_SHIFT                                                                            (14U)
#define MPU_GICC_APR0_AP14_MASK                                                                             (0x00004000U)

#define MPU_GICC_APR0_AP15_SHIFT                                                                            (15U)
#define MPU_GICC_APR0_AP15_MASK                                                                             (0x00008000U)

#define MPU_GICC_APR0_AP16_SHIFT                                                                            (16U)
#define MPU_GICC_APR0_AP16_MASK                                                                             (0x00010000U)

#define MPU_GICC_APR0_AP17_SHIFT                                                                            (17U)
#define MPU_GICC_APR0_AP17_MASK                                                                             (0x00020000U)

#define MPU_GICC_APR0_AP18_SHIFT                                                                            (18U)
#define MPU_GICC_APR0_AP18_MASK                                                                             (0x00040000U)

#define MPU_GICC_APR0_AP19_SHIFT                                                                            (19U)
#define MPU_GICC_APR0_AP19_MASK                                                                             (0x00080000U)

#define MPU_GICC_APR0_AP20_SHIFT                                                                            (20U)
#define MPU_GICC_APR0_AP20_MASK                                                                             (0x00100000U)

#define MPU_GICC_APR0_AP21_SHIFT                                                                            (21U)
#define MPU_GICC_APR0_AP21_MASK                                                                             (0x00200000U)

#define MPU_GICC_APR0_AP22_SHIFT                                                                            (22U)
#define MPU_GICC_APR0_AP22_MASK                                                                             (0x00400000U)

#define MPU_GICC_APR0_AP23_SHIFT                                                                            (23U)
#define MPU_GICC_APR0_AP23_MASK                                                                             (0x00800000U)

#define MPU_GICC_APR0_AP24_SHIFT                                                                            (24U)
#define MPU_GICC_APR0_AP24_MASK                                                                             (0x01000000U)

#define MPU_GICC_APR0_AP25_SHIFT                                                                            (25U)
#define MPU_GICC_APR0_AP25_MASK                                                                             (0x02000000U)

#define MPU_GICC_APR0_AP26_SHIFT                                                                            (26U)
#define MPU_GICC_APR0_AP26_MASK                                                                             (0x04000000U)

#define MPU_GICC_APR0_AP27_SHIFT                                                                            (27U)
#define MPU_GICC_APR0_AP27_MASK                                                                             (0x08000000U)

#define MPU_GICC_APR0_AP28_SHIFT                                                                            (28U)
#define MPU_GICC_APR0_AP28_MASK                                                                             (0x10000000U)

#define MPU_GICC_APR0_AP29_SHIFT                                                                            (29U)
#define MPU_GICC_APR0_AP29_MASK                                                                             (0x20000000U)

#define MPU_GICC_APR0_AP30_SHIFT                                                                            (30U)
#define MPU_GICC_APR0_AP30_MASK                                                                             (0x40000000U)

#define MPU_GICC_APR0_AP31_SHIFT                                                                            (31U)
#define MPU_GICC_APR0_AP31_MASK                                                                             (0x80000000U)

#define MPU_GICC_NSAPR0_AP0_SHIFT                                                                           (0U)
#define MPU_GICC_NSAPR0_AP0_MASK                                                                            (0x00000001U)

#define MPU_GICC_NSAPR0_AP1_SHIFT                                                                           (1U)
#define MPU_GICC_NSAPR0_AP1_MASK                                                                            (0x00000002U)

#define MPU_GICC_NSAPR0_AP2_SHIFT                                                                           (2U)
#define MPU_GICC_NSAPR0_AP2_MASK                                                                            (0x00000004U)

#define MPU_GICC_NSAPR0_AP3_SHIFT                                                                           (3U)
#define MPU_GICC_NSAPR0_AP3_MASK                                                                            (0x00000008U)

#define MPU_GICC_NSAPR0_AP4_SHIFT                                                                           (4U)
#define MPU_GICC_NSAPR0_AP4_MASK                                                                            (0x00000010U)

#define MPU_GICC_NSAPR0_AP5_SHIFT                                                                           (5U)
#define MPU_GICC_NSAPR0_AP5_MASK                                                                            (0x00000020U)

#define MPU_GICC_NSAPR0_AP6_SHIFT                                                                           (6U)
#define MPU_GICC_NSAPR0_AP6_MASK                                                                            (0x00000040U)

#define MPU_GICC_NSAPR0_AP7_SHIFT                                                                           (7U)
#define MPU_GICC_NSAPR0_AP7_MASK                                                                            (0x00000080U)

#define MPU_GICC_NSAPR0_AP8_SHIFT                                                                           (8U)
#define MPU_GICC_NSAPR0_AP8_MASK                                                                            (0x00000100U)

#define MPU_GICC_NSAPR0_AP9_SHIFT                                                                           (9U)
#define MPU_GICC_NSAPR0_AP9_MASK                                                                            (0x00000200U)

#define MPU_GICC_NSAPR0_AP10_SHIFT                                                                          (10U)
#define MPU_GICC_NSAPR0_AP10_MASK                                                                           (0x00000400U)

#define MPU_GICC_NSAPR0_AP11_SHIFT                                                                          (11U)
#define MPU_GICC_NSAPR0_AP11_MASK                                                                           (0x00000800U)

#define MPU_GICC_NSAPR0_AP12_SHIFT                                                                          (12U)
#define MPU_GICC_NSAPR0_AP12_MASK                                                                           (0x00001000U)

#define MPU_GICC_NSAPR0_AP13_SHIFT                                                                          (13U)
#define MPU_GICC_NSAPR0_AP13_MASK                                                                           (0x00002000U)

#define MPU_GICC_NSAPR0_AP14_SHIFT                                                                          (14U)
#define MPU_GICC_NSAPR0_AP14_MASK                                                                           (0x00004000U)

#define MPU_GICC_NSAPR0_AP15_SHIFT                                                                          (15U)
#define MPU_GICC_NSAPR0_AP15_MASK                                                                           (0x00008000U)

#define MPU_GICC_NSAPR0_AP16_SHIFT                                                                          (16U)
#define MPU_GICC_NSAPR0_AP16_MASK                                                                           (0x00010000U)

#define MPU_GICC_NSAPR0_AP17_SHIFT                                                                          (17U)
#define MPU_GICC_NSAPR0_AP17_MASK                                                                           (0x00020000U)

#define MPU_GICC_NSAPR0_AP18_SHIFT                                                                          (18U)
#define MPU_GICC_NSAPR0_AP18_MASK                                                                           (0x00040000U)

#define MPU_GICC_NSAPR0_AP19_SHIFT                                                                          (19U)
#define MPU_GICC_NSAPR0_AP19_MASK                                                                           (0x00080000U)

#define MPU_GICC_NSAPR0_AP20_SHIFT                                                                          (20U)
#define MPU_GICC_NSAPR0_AP20_MASK                                                                           (0x00100000U)

#define MPU_GICC_NSAPR0_AP21_SHIFT                                                                          (21U)
#define MPU_GICC_NSAPR0_AP21_MASK                                                                           (0x00200000U)

#define MPU_GICC_NSAPR0_AP22_SHIFT                                                                          (22U)
#define MPU_GICC_NSAPR0_AP22_MASK                                                                           (0x00400000U)

#define MPU_GICC_NSAPR0_AP23_SHIFT                                                                          (23U)
#define MPU_GICC_NSAPR0_AP23_MASK                                                                           (0x00800000U)

#define MPU_GICC_NSAPR0_AP24_SHIFT                                                                          (24U)
#define MPU_GICC_NSAPR0_AP24_MASK                                                                           (0x01000000U)

#define MPU_GICC_NSAPR0_AP25_SHIFT                                                                          (25U)
#define MPU_GICC_NSAPR0_AP25_MASK                                                                           (0x02000000U)

#define MPU_GICC_NSAPR0_AP26_SHIFT                                                                          (26U)
#define MPU_GICC_NSAPR0_AP26_MASK                                                                           (0x04000000U)

#define MPU_GICC_NSAPR0_AP27_SHIFT                                                                          (27U)
#define MPU_GICC_NSAPR0_AP27_MASK                                                                           (0x08000000U)

#define MPU_GICC_NSAPR0_AP28_SHIFT                                                                          (28U)
#define MPU_GICC_NSAPR0_AP28_MASK                                                                           (0x10000000U)

#define MPU_GICC_NSAPR0_AP29_SHIFT                                                                          (29U)
#define MPU_GICC_NSAPR0_AP29_MASK                                                                           (0x20000000U)

#define MPU_GICC_NSAPR0_AP30_SHIFT                                                                          (30U)
#define MPU_GICC_NSAPR0_AP30_MASK                                                                           (0x40000000U)

#define MPU_GICC_NSAPR0_AP31_SHIFT                                                                          (31U)
#define MPU_GICC_NSAPR0_AP31_MASK                                                                           (0x80000000U)

#define MPU_GICC_IIDR_PRODUCTID_SHIFT                                                                       (20U)
#define MPU_GICC_IIDR_PRODUCTID_MASK                                                                        (0xfff00000U)

#define MPU_GICC_IIDR_ARCHITECTUREVERSION_SHIFT                                                             (16U)
#define MPU_GICC_IIDR_ARCHITECTUREVERSION_MASK                                                              (0x000f0000U)

#define MPU_GICC_IIDR_REVISION_SHIFT                                                                        (12U)
#define MPU_GICC_IIDR_REVISION_MASK                                                                         (0x0000f000U)

#define MPU_GICC_IIDR_IMPLEMENTER_SHIFT                                                                     (0U)
#define MPU_GICC_IIDR_IMPLEMENTER_MASK                                                                      (0x00000fffU)

#define MPU_GICC_DIR_INTERRUPTID_SHIFT                                                                      (0U)
#define MPU_GICC_DIR_INTERRUPTID_MASK                                                                       (0x000003ffU)

#define MPU_GICC_DIR_CPUID_SHIFT                                                                            (10U)
#define MPU_GICC_DIR_CPUID_MASK                                                                             (0x00001c00U)

#define MPU_GICC_DIR_RESERVED_SHIFT                                                                         (13U)
#define MPU_GICC_DIR_RESERVED_MASK                                                                          (0xffffe000U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_MPU_INTC_PHYS_H_ */
