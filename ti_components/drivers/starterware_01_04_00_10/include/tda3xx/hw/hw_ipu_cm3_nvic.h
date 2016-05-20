/*
* hw_ipu_cm3_nvic.h
*
* Register-level header file for IPU_CM3_NVIC
*
* Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
*
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#ifndef HW_IPU_CM3_NVIC_H_
#define HW_IPU_CM3_NVIC_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define IPU_CM3_NVIC_INTERRUPT_CONTROLLER_TYPE                      (0x4U)
#define IPU_CM3_NVIC_AUXILIARY_CONTROL                              (0x8U)
#define IPU_CM3_NVIC_SYSTICK_CONTROL_AND_STATUS                     (0x10U)
#define IPU_CM3_NVIC_SYSTICK_RELOAD_VALUE                           (0x14U)
#define IPU_CM3_NVIC_SYSTICK_CURRENT_VALUE                          (0x18U)
#define IPU_CM3_NVIC_SYSTICK_CALIBRATION_VALUE                      (0x1cU)
#define IPU_CM3_NVIC_EXTERNAL_INTERRUPT_SETEN_0_31                  (0x100U)
#define IPU_CM3_NVIC_EXTERNAL_INTERRUPT_SETEN_32_63                 (0x104U)
#define IPU_CM3_NVIC_EXTERNAL_INTERRUPT_SETEN_64_95                 (0x108U)
#define IPU_CM3_NVIC_EXTERNAL_INTERRUPT_CLREN_0_31                  (0x180U)
#define IPU_CM3_NVIC_EXTERNAL_INTERRUPT_CLREN_32_63                 (0x184U)
#define IPU_CM3_NVIC_EXTERNAL_INTERRUPT_CLREN_64_95                 (0x188U)
#define IPU_CM3_NVIC_EXTERNAL_INTERRUPT_SETPEND_0_31                (0x200U)
#define IPU_CM3_NVIC_EXTERNAL_INTERRUPT_SETPEND_32_63               (0x204U)
#define IPU_CM3_NVIC_EXTERNAL_INTERRUPT_SETPEND_64_95               (0x208U)
#define IPU_CM3_NVIC_EXTERNAL_INTERRUPT_CLRPEND_0_31                (0x280U)
#define IPU_CM3_NVIC_EXTERNAL_INTERRUPT_CLRPEND_32_63               (0x284U)
#define IPU_CM3_NVIC_EXTERNAL_INTERRUPT_CLRPEND_64_95               (0x288U)
#define IPU_CM3_NVIC_EXTERNAL_INTERRUPT_ACTIVE_0_31                 (0x300U)
#define IPU_CM3_NVIC_EXTERNAL_INTERRUPT_ACTIVE_32_63                (0x304U)
#define IPU_CM3_NVIC_EXTERNAL_INTERRUPT_ACTIVE_64_95                (0x308U)
#define IPU_CM3_NVIC_EXTERNAL_INT_PRIORITY_LEVEL(n)                 (0x400U + (n * 0x4U))
#define IPU_CM3_NVIC_EXTERNAL_INT_PRIORITY_LEVEL_NUM_ELEMS          (16U)
#define IPU_CM3_NVIC_CPU_ID_BASE_REGISTER                           (0xd00U)
#define IPU_CM3_NVIC_INTERRUPT_CONTROL_AND_STATE                    (0xd04U)
#define IPU_CM3_NVIC_VECTOR_TABLE_OFFSET                            (0xd08U)
#define IPU_CM3_NVIC_APPLICATION_INT_AND_RESET_CONTROL              (0xd0cU)
#define IPU_CM3_NVIC_SYSTEM_CONTROL                                 (0xd10U)
#define IPU_CM3_NVIC_CONFIGURATION_CONTROL                          (0xd14U)
#define IPU_CM3_NVIC_SYSTEM_EXCEPTION_PRIORITY_LEVEL(n)             (0xd18U + (n * 0x4U))
#define IPU_CM3_NVIC_SYSTEM_EXCEPTION_PRIORITY_LEVEL_NUM_ELEMS      (3U)
#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE               (0xd24U)
#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS                      (0xd28U)
#define IPU_CM3_NVIC_HARD_FAULT_STATUS                              (0xd2cU)
#define IPU_CM3_NVIC_DEBUG_FAULT_STATUS                             (0xd30U)
#define IPU_CM3_NVIC_MEMORY_MANAGE_ADDRESS                          (0xd34U)
#define IPU_CM3_NVIC_BUS_FAULT_MANAGE_ADDRESS                       (0xd38U)
#define IPU_CM3_NVIC_AUXILIARY_FAULT_STATUS                         (0xd3cU)
#define IPU_CM3_NVIC_MPU_TYPE                                       (0xd90U)
#define IPU_CM3_NVIC_MPU_CONTROL                                    (0xd94U)
#define IPU_CM3_NVIC_MPU_REGION_NUMBER                              (0xd98U)
#define IPU_CM3_NVIC_MPU_REGION_BASE_ADDRESS                        (0xd9cU)
#define IPU_CM3_NVIC_MPU_REGION_BASE_ATTRIBUTE_AND_SIZE             (0xda0U)
#define IPU_CM3_NVIC_MPU_ALIAS(n)                                   (0xda4U + (n * 0x4U))
#define IPU_CM3_NVIC_MPU_ALIAS_NUM_ELEMS                            (6U)
#define IPU_CM3_NVIC_DEBUG_HALTING_CONTROL_AND_STATUS               (0xdf0U)
#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_SELECTOR                   (0xdf4U)
#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_DATA                       (0xdf8U)
#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL            (0xdfcU)
#define IPU_CM3_NVIC_SOFTWARE_TRIGGER_INTERRUPT                     (0xf00U)
#define IPU_CM3_NVIC_PERIPHERAL_ID_4                                (0xfd0U)
#define IPU_CM3_NVIC_PERIPHERAL_ID_5                                (0xfd4U)
#define IPU_CM3_NVIC_PERIPHERAL_ID_6                                (0xfd8U)
#define IPU_CM3_NVIC_PERIPHERAL_ID_7                                (0xfdcU)
#define IPU_CM3_NVIC_PERIPHERAL_ID_0                                (0xfe0U)
#define IPU_CM3_NVIC_PERIPHERAL_ID_1                                (0xfe4U)
#define IPU_CM3_NVIC_PERIPHERAL_ID_2                                (0xfe8U)
#define IPU_CM3_NVIC_PERIPHERAL_ID_3                                (0xfecU)
#define IPU_CM3_NVIC_COMPONENT_ID_0                                 (0xff0U)
#define IPU_CM3_NVIC_COMPONENT_ID_1                                 (0xff4U)
#define IPU_CM3_NVIC_COMPONENT_ID_2                                 (0xff8U)
#define IPU_CM3_NVIC_COMPONENT_ID_3                                 (0xffcU)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define IPU_CM3_NVIC_INTERRUPT_CONTROLLER_TYPE_INTLINESNUM_SHIFT                        (0U)
#define IPU_CM3_NVIC_INTERRUPT_CONTROLLER_TYPE_INTLINESNUM_MASK                         (0x0000001fU)

#define IPU_CM3_NVIC_AUXILIARY_CONTROL_DISMCYCINT_SHIFT                                 (0U)
#define IPU_CM3_NVIC_AUXILIARY_CONTROL_DISMCYCINT_MASK                                  (0x00000001U)

#define IPU_CM3_NVIC_AUXILIARY_CONTROL_DISDEFWBUF_SHIFT                                 (1U)
#define IPU_CM3_NVIC_AUXILIARY_CONTROL_DISDEFWBUF_MASK                                  (0x00000002U)

#define IPU_CM3_NVIC_AUXILIARY_CONTROL_DISFOLD_SHIFT                                    (2U)
#define IPU_CM3_NVIC_AUXILIARY_CONTROL_DISFOLD_MASK                                     (0x00000004U)

#define IPU_CM3_NVIC_SYSTICK_CONTROL_AND_STATUS_ENABLE_SHIFT                            (0U)
#define IPU_CM3_NVIC_SYSTICK_CONTROL_AND_STATUS_ENABLE_MASK                             (0x00000001U)

#define IPU_CM3_NVIC_SYSTICK_CONTROL_AND_STATUS_TICKINT_SHIFT                           (1U)
#define IPU_CM3_NVIC_SYSTICK_CONTROL_AND_STATUS_TICKINT_MASK                            (0x00000002U)

#define IPU_CM3_NVIC_SYSTICK_CONTROL_AND_STATUS_CLKSOURCE_SHIFT                         (2U)
#define IPU_CM3_NVIC_SYSTICK_CONTROL_AND_STATUS_CLKSOURCE_MASK                          (0x00000004U)

#define IPU_CM3_NVIC_SYSTICK_CONTROL_AND_STATUS_COUNTFLAG_SHIFT                         (16U)
#define IPU_CM3_NVIC_SYSTICK_CONTROL_AND_STATUS_COUNTFLAG_MASK                          (0x00010000U)

#define IPU_CM3_NVIC_SYSTICK_RELOAD_VALUE_SHIFT                                         (0U)
#define IPU_CM3_NVIC_SYSTICK_RELOAD_VALUE_MASK                                          (0x00ffffffU)

#define IPU_CM3_NVIC_SYSTICK_CURRENT_VALUE_SHIFT                                        (0U)
#define IPU_CM3_NVIC_SYSTICK_CURRENT_VALUE_MASK                                         (0x00000001U)

#define IPU_CM3_NVIC_SYSTICK_CALIBRATION_VALUE_TENMS_SHIFT                              (0U)
#define IPU_CM3_NVIC_SYSTICK_CALIBRATION_VALUE_TENMS_MASK                               (0x00ffffffU)

#define IPU_CM3_NVIC_SYSTICK_CALIBRATION_VALUE_NOREF_SHIFT                              (31U)
#define IPU_CM3_NVIC_SYSTICK_CALIBRATION_VALUE_NOREF_MASK                               (0x80000000U)

#define IPU_CM3_NVIC_SYSTICK_CALIBRATION_VALUE_SKEW_SHIFT                               (30U)
#define IPU_CM3_NVIC_SYSTICK_CALIBRATION_VALUE_SKEW_MASK                                (0x40000000U)

#define _SHIFT(n)                                                                       (n * 1U)
#define _MASK(n)                                                                        (1U << (n * 1U))

#define _SHIFT(n)                                                                       (n * 1U)
#define _MASK(n)                                                                        (1U << (n * 1U))

#define IPU_CM3_NVIC_EXTERNAL_INTERRUPT_SETEN_64_95_SETENA64_SHIFT                      (0U)
#define IPU_CM3_NVIC_EXTERNAL_INTERRUPT_SETEN_64_95_SETENA64_MASK                       (0x00000001U)

#define _SHIFT(n)                                                                       (n * 1U)
#define _MASK(n)                                                                        (1U << (n * 1U))

#define _SHIFT(n)                                                                       (n * 1U)
#define _MASK(n)                                                                        (1U << (n * 1U))

#define IPU_CM3_NVIC_EXTERNAL_INTERRUPT_CLREN_64_95_CLRENA64_SHIFT                      (0U)
#define IPU_CM3_NVIC_EXTERNAL_INTERRUPT_CLREN_64_95_CLRENA64_MASK                       (0x00000001U)

#define _SHIFT(n)                                                                       (n * 1U)
#define _MASK(n)                                                                        (1U << (n * 1U))

#define _SHIFT(n)                                                                       (n * 1U)
#define _MASK(n)                                                                        (1U << (n * 1U))

#define IPU_CM3_NVIC_EXTERNAL_INTERRUPT_SETPEND_64_95_SETPEND64_SHIFT                   (0U)
#define IPU_CM3_NVIC_EXTERNAL_INTERRUPT_SETPEND_64_95_SETPEND64_MASK                    (0x00000001U)

#define _SHIFT(n)                                                                       (n * 1U)
#define _MASK(n)                                                                        (1U << (n * 1U))

#define _SHIFT(n)                                                                       (n * 1U)
#define _MASK(n)                                                                        (1U << (n * 1U))

#define IPU_CM3_NVIC_EXTERNAL_INTERRUPT_CLRPEND_64_95_CLRPEND64_SHIFT                   (0U)
#define IPU_CM3_NVIC_EXTERNAL_INTERRUPT_CLRPEND_64_95_CLRPEND64_MASK                    (0x00000001U)

#define _SHIFT(n)                                                                       (n * 1U)
#define _MASK(n)                                                                        (1U << (n * 1U))

#define _SHIFT(n)                                                                       (n * 1U)
#define _MASK(n)                                                                        (1U << (n * 1U))

#define IPU_CM3_NVIC_EXTERNAL_INTERRUPT_ACTIVE_64_95_ACTIVE64_SHIFT                     (0U)
#define IPU_CM3_NVIC_EXTERNAL_INTERRUPT_ACTIVE_64_95_ACTIVE64_MASK                      (0x00000001U)

#define _SHIFT(n)                                                                       (n * 8U)
#define _MASK(n)                                                                        (255U << (n * 8U))

#define IPU_CM3_NVIC_CPU_ID_BASE_REGISTER_REVISION_SHIFT                                (0U)
#define IPU_CM3_NVIC_CPU_ID_BASE_REGISTER_REVISION_MASK                                 (0x0000000fU)

#define IPU_CM3_NVIC_CPU_ID_BASE_REGISTER_PARTNO_SHIFT                                  (4U)
#define IPU_CM3_NVIC_CPU_ID_BASE_REGISTER_PARTNO_MASK                                   (0x0000fff0U)

#define IPU_CM3_NVIC_CPU_ID_BASE_REGISTER_CONSTANT_SHIFT                                (16U)
#define IPU_CM3_NVIC_CPU_ID_BASE_REGISTER_CONSTANT_MASK                                 (0x000f0000U)

#define IPU_CM3_NVIC_CPU_ID_BASE_REGISTER_VARIANT_SHIFT                                 (20U)
#define IPU_CM3_NVIC_CPU_ID_BASE_REGISTER_VARIANT_MASK                                  (0x00f00000U)

#define IPU_CM3_NVIC_CPU_ID_BASE_REGISTER_IMPLEMENTER_SHIFT                             (24U)
#define IPU_CM3_NVIC_CPU_ID_BASE_REGISTER_IMPLEMENTER_MASK                              (0xff000000U)

#define IPU_CM3_NVIC_INTERRUPT_CONTROL_AND_STATE_VECTACTIVE_SHIFT                       (0U)
#define IPU_CM3_NVIC_INTERRUPT_CONTROL_AND_STATE_VECTACTIVE_MASK                        (0x000003ffU)

#define IPU_CM3_NVIC_INTERRUPT_CONTROL_AND_STATE_RETTOBASE_SHIFT                        (10U)
#define IPU_CM3_NVIC_INTERRUPT_CONTROL_AND_STATE_RETTOBASE_MASK                         (0x00000400U)

#define IPU_CM3_NVIC_INTERRUPT_CONTROL_AND_STATE_VECTPENDING_SHIFT                      (11U)
#define IPU_CM3_NVIC_INTERRUPT_CONTROL_AND_STATE_VECTPENDING_MASK                       (0x003ff800U)

#define IPU_CM3_NVIC_INTERRUPT_CONTROL_AND_STATE_ISRPENDING_SHIFT                       (22U)
#define IPU_CM3_NVIC_INTERRUPT_CONTROL_AND_STATE_ISRPENDING_MASK                        (0x00400000U)

#define IPU_CM3_NVIC_INTERRUPT_CONTROL_AND_STATE_ISRPREEMPT_SHIFT                       (23U)
#define IPU_CM3_NVIC_INTERRUPT_CONTROL_AND_STATE_ISRPREEMPT_MASK                        (0x00800000U)

#define IPU_CM3_NVIC_INTERRUPT_CONTROL_AND_STATE_PENDSTCLR_SHIFT                        (25U)
#define IPU_CM3_NVIC_INTERRUPT_CONTROL_AND_STATE_PENDSTCLR_MASK                         (0x02000000U)

#define IPU_CM3_NVIC_INTERRUPT_CONTROL_AND_STATE_PENDSTSET_SHIFT                        (26U)
#define IPU_CM3_NVIC_INTERRUPT_CONTROL_AND_STATE_PENDSTSET_MASK                         (0x04000000U)

#define IPU_CM3_NVIC_INTERRUPT_CONTROL_AND_STATE_PENDSVCLR_SHIFT                        (27U)
#define IPU_CM3_NVIC_INTERRUPT_CONTROL_AND_STATE_PENDSVCLR_MASK                         (0x08000000U)

#define IPU_CM3_NVIC_INTERRUPT_CONTROL_AND_STATE_PENDSVSET_SHIFT                        (28U)
#define IPU_CM3_NVIC_INTERRUPT_CONTROL_AND_STATE_PENDSVSET_MASK                         (0x10000000U)

#define IPU_CM3_NVIC_INTERRUPT_CONTROL_AND_STATE_NMIPENDSET_SHIFT                       (31U)
#define IPU_CM3_NVIC_INTERRUPT_CONTROL_AND_STATE_NMIPENDSET_MASK                        (0x80000000U)

#define IPU_CM3_NVIC_VECTOR_TABLE_OFFSET_TBLOFF_SHIFT                                   (7U)
#define IPU_CM3_NVIC_VECTOR_TABLE_OFFSET_TBLOFF_MASK                                    (0xffffff80U)

#define IPU_CM3_NVIC_APPLICATION_INT_AND_RESET_CONTROL_VECTRESET_SHIFT                  (0U)
#define IPU_CM3_NVIC_APPLICATION_INT_AND_RESET_CONTROL_VECTRESET_MASK                   (0x00000001U)

#define IPU_CM3_NVIC_APPLICATION_INT_AND_RESET_CONTROL_VECTCLRACTIVE_SHIFT              (1U)
#define IPU_CM3_NVIC_APPLICATION_INT_AND_RESET_CONTROL_VECTCLRACTIVE_MASK               (0x00000002U)

#define IPU_CM3_NVIC_APPLICATION_INT_AND_RESET_CONTROL_SYSRESETREQ_SHIFT                (2U)
#define IPU_CM3_NVIC_APPLICATION_INT_AND_RESET_CONTROL_SYSRESETREQ_MASK                 (0x00000004U)

#define IPU_CM3_NVIC_APPLICATION_INT_AND_RESET_CONTROL_PRIGROUP_SHIFT                   (8U)
#define IPU_CM3_NVIC_APPLICATION_INT_AND_RESET_CONTROL_PRIGROUP_MASK                    (0x00000700U)

#define IPU_CM3_NVIC_APPLICATION_INT_AND_RESET_CONTROL_ENDIANESS_SHIFT                  (15U)
#define IPU_CM3_NVIC_APPLICATION_INT_AND_RESET_CONTROL_ENDIANESS_MASK                   (0x00008000U)

#define IPU_CM3_NVIC_APPLICATION_INT_AND_RESET_CONTROL_VECTKEY_SHIFT                    (16U)
#define IPU_CM3_NVIC_APPLICATION_INT_AND_RESET_CONTROL_VECTKEY_MASK                     (0xffff0000U)

#define IPU_CM3_NVIC_SYSTEM_CONTROL_SLEEPONEXIT_SHIFT                                   (1U)
#define IPU_CM3_NVIC_SYSTEM_CONTROL_SLEEPONEXIT_MASK                                    (0x00000002U)

#define IPU_CM3_NVIC_SYSTEM_CONTROL_SLEEPDEEP_SHIFT                                     (2U)
#define IPU_CM3_NVIC_SYSTEM_CONTROL_SLEEPDEEP_MASK                                      (0x00000004U)

#define IPU_CM3_NVIC_SYSTEM_CONTROL_SEVONPEND_SHIFT                                     (4U)
#define IPU_CM3_NVIC_SYSTEM_CONTROL_SEVONPEND_MASK                                      (0x00000010U)

#define IPU_CM3_NVIC_CONFIGURATION_CONTROL_NONBASETHRDENA_SHIFT                         (0U)
#define IPU_CM3_NVIC_CONFIGURATION_CONTROL_NONBASETHRDENA_MASK                          (0x00000001U)

#define IPU_CM3_NVIC_CONFIGURATION_CONTROL_USERSETMPEND_SHIFT                           (1U)
#define IPU_CM3_NVIC_CONFIGURATION_CONTROL_USERSETMPEND_MASK                            (0x00000002U)

#define IPU_CM3_NVIC_CONFIGURATION_CONTROL_UNALIGN_TRP_SHIFT                            (3U)
#define IPU_CM3_NVIC_CONFIGURATION_CONTROL_UNALIGN_TRP_MASK                             (0x00000008U)

#define IPU_CM3_NVIC_CONFIGURATION_CONTROL_DIV_0_TRP_SHIFT                              (4U)
#define IPU_CM3_NVIC_CONFIGURATION_CONTROL_DIV_0_TRP_MASK                               (0x00000010U)

#define IPU_CM3_NVIC_CONFIGURATION_CONTROL_BFHFNMIGN_SHIFT                              (8U)
#define IPU_CM3_NVIC_CONFIGURATION_CONTROL_BFHFNMIGN_MASK                               (0x00000100U)

#define IPU_CM3_NVIC_CONFIGURATION_CONTROL_STKALIGN_SHIFT                               (9U)
#define IPU_CM3_NVIC_CONFIGURATION_CONTROL_STKALIGN_MASK                                (0x00000200U)

#define _SHIFT(n)                                                                       (n * 8U)
#define _MASK(n)                                                                        (255U << (n * 8U))

#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_MEMFAULTACT_SHIFT                 (0U)
#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_MEMFAULTACT_MASK                  (0x00000001U)

#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_BUSFAULTACT_SHIFT                 (1U)
#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_BUSFAULTACT_MASK                  (0x00000002U)

#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_USGFAULTACT_SHIFT                 (3U)
#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_USGFAULTACT_MASK                  (0x00000008U)

#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_SVCFAULTACT_SHIFT                 (7U)
#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_SVCFAULTACT_MASK                  (0x00000080U)

#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_MONITORACT_SHIFT                  (8U)
#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_MONITORACT_MASK                   (0x00000100U)

#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_PENDSVACT_SHIFT                   (10U)
#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_PENDSVACT_MASK                    (0x00000400U)

#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_SYSICKACT_SHIFT                   (11U)
#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_SYSICKACT_MASK                    (0x00000800U)

#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_USGFAULTPENDED_SHIFT              (12U)
#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_USGFAULTPENDED_MASK               (0x00001000U)

#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_MEMFAULTPENDED_SHIFT              (13U)
#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_MEMFAULTPENDED_MASK               (0x00002000U)

#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_BUSFAULTPENDED_SHIFT              (14U)
#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_BUSFAULTPENDED_MASK               (0x00004000U)

#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_SVCALLPENDED_SHIFT                (15U)
#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_SVCALLPENDED_MASK                 (0x00008000U)

#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_MEMFAULTENA_SHIFT                 (16U)
#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_MEMFAULTENA_MASK                  (0x00010000U)

#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_BUSFAULTENA_SHIFT                 (17U)
#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_BUSFAULTENA_MASK                  (0x00020000U)

#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_USGFAULTENA_SHIFT                 (18U)
#define IPU_CM3_NVIC_SYSTEM_HANDLER_CONTROL_AND_STATE_USGFAULTENA_MASK                  (0x00040000U)

#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_IACCVIOL_SHIFT                           (0U)
#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_IACCVIOL_MASK                            (0x00000001U)

#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_DACCVIOL_SHIFT                           (1U)
#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_DACCVIOL_MASK                            (0x00000002U)

#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_MUNSTKERR_SHIFT                          (3U)
#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_MUNSTKERR_MASK                           (0x00000008U)

#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_MSTKERR_SHIFT                            (4U)
#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_MSTKERR_MASK                             (0x00000010U)

#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_MMARVALID_SHIFT                          (7U)
#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_MMARVALID_MASK                           (0x00000080U)

#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_IBUSERR_SHIFT                            (8U)
#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_IBUSERR_MASK                             (0x00000100U)

#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_PRECISERR_SHIFT                          (9U)
#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_PRECISERR_MASK                           (0x00000200U)

#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_IMPRECISERR_SHIFT                        (10U)
#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_IMPRECISERR_MASK                         (0x00000400U)

#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_UNSTKERR_SHIFT                           (11U)
#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_UNSTKERR_MASK                            (0x00000800U)

#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_STKERR_SHIFT                             (12U)
#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_STKERR_MASK                              (0x00001000U)

#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_BFARVALID_SHIFT                          (15U)
#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_BFARVALID_MASK                           (0x00008000U)

#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_UNDEDINSTR_SHIFT                         (16U)
#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_UNDEDINSTR_MASK                          (0x00010000U)

#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_INVSTATE_SHIFT                           (17U)
#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_INVSTATE_MASK                            (0x00020000U)

#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_INVPC_SHIFT                              (18U)
#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_INVPC_MASK                               (0x00040000U)

#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_NOCP_SHIFT                               (19U)
#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_NOCP_MASK                                (0x00080000U)

#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_UNALIGNED_SHIFT                          (24U)
#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_UNALIGNED_MASK                           (0x01000000U)

#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_DIVBYZERO_SHIFT                          (25U)
#define IPU_CM3_NVIC_CONFIGURABLE_FAULT_STATUS_DIVBYZERO_MASK                           (0x02000000U)

#define IPU_CM3_NVIC_HARD_FAULT_STATUS_VECTBL_SHIFT                                     (1U)
#define IPU_CM3_NVIC_HARD_FAULT_STATUS_VECTBL_MASK                                      (0x00000002U)

#define IPU_CM3_NVIC_HARD_FAULT_STATUS_FORCED_SHIFT                                     (30U)
#define IPU_CM3_NVIC_HARD_FAULT_STATUS_FORCED_MASK                                      (0x40000000U)

#define IPU_CM3_NVIC_HARD_FAULT_STATUS_DEBUGEVT_SHIFT                                   (31U)
#define IPU_CM3_NVIC_HARD_FAULT_STATUS_DEBUGEVT_MASK                                    (0x80000000U)

#define IPU_CM3_NVIC_DEBUG_FAULT_STATUS_HALTED_SHIFT                                    (0U)
#define IPU_CM3_NVIC_DEBUG_FAULT_STATUS_HALTED_MASK                                     (0x00000001U)

#define IPU_CM3_NVIC_DEBUG_FAULT_STATUS_BKPT_SHIFT                                      (1U)
#define IPU_CM3_NVIC_DEBUG_FAULT_STATUS_BKPT_MASK                                       (0x00000002U)

#define IPU_CM3_NVIC_DEBUG_FAULT_STATUS_DWTTRAP_SHIFT                                   (2U)
#define IPU_CM3_NVIC_DEBUG_FAULT_STATUS_DWTTRAP_MASK                                    (0x00000004U)

#define IPU_CM3_NVIC_DEBUG_FAULT_STATUS_VCATCH_SHIFT                                    (3U)
#define IPU_CM3_NVIC_DEBUG_FAULT_STATUS_VCATCH_MASK                                     (0x00000008U)

#define IPU_CM3_NVIC_DEBUG_FAULT_STATUS_EXTERNAL_SHIFT                                  (4U)
#define IPU_CM3_NVIC_DEBUG_FAULT_STATUS_EXTERNAL_MASK                                   (0x00000010U)

#define IPU_CM3_NVIC_MEMORY_MANAGE_ADDRESS_MMAR_SHIFT                                   (0U)
#define IPU_CM3_NVIC_MEMORY_MANAGE_ADDRESS_MMAR_MASK                                    (0xffffffffU)

#define IPU_CM3_NVIC_BUS_FAULT_MANAGE_ADDRESS_BFAR_SHIFT                                (0U)
#define IPU_CM3_NVIC_BUS_FAULT_MANAGE_ADDRESS_BFAR_MASK                                 (0xffffffffU)

#define IPU_CM3_NVIC_AUXILIARY_FAULT_STATUS_IMPDEF_SHIFT                                (0U)
#define IPU_CM3_NVIC_AUXILIARY_FAULT_STATUS_IMPDEF_MASK                                 (0xffffffffU)

#define IPU_CM3_NVIC_MPU_TYPE_SEPARATE_SHIFT                                            (0U)
#define IPU_CM3_NVIC_MPU_TYPE_SEPARATE_MASK                                             (0x00000001U)

#define IPU_CM3_NVIC_MPU_TYPE_DREGION_SHIFT                                             (8U)
#define IPU_CM3_NVIC_MPU_TYPE_DREGION_MASK                                              (0x0000ff00U)

#define IPU_CM3_NVIC_MPU_TYPE_IREGION_SHIFT                                             (16U)
#define IPU_CM3_NVIC_MPU_TYPE_IREGION_MASK                                              (0x00ff0000U)

#define IPU_CM3_NVIC_MPU_CONTROL_ENABLE_SHIFT                                           (0U)
#define IPU_CM3_NVIC_MPU_CONTROL_ENABLE_MASK                                            (0x00000001U)

#define IPU_CM3_NVIC_MPU_CONTROL_HFNMIENA_SHIFT                                         (1U)
#define IPU_CM3_NVIC_MPU_CONTROL_HFNMIENA_MASK                                          (0x00000002U)

#define IPU_CM3_NVIC_MPU_CONTROL_PRIVDEFENA_SHIFT                                       (2U)
#define IPU_CM3_NVIC_MPU_CONTROL_PRIVDEFENA_MASK                                        (0x00000004U)

#define IPU_CM3_NVIC_MPU_REGION_NUMBER_SHIFT                                            (0U)
#define IPU_CM3_NVIC_MPU_REGION_NUMBER_MASK                                             (0x000000ffU)

#define IPU_CM3_NVIC_MPU_REGION_BASE_ADDRESS_SHIFT                                      (0U)
#define IPU_CM3_NVIC_MPU_REGION_BASE_ADDRESS_MASK                                       (0x0000000fU)

#define IPU_CM3_NVIC_MPU_REGION_BASE_ADDRESS_VALID_SHIFT                                (4U)
#define IPU_CM3_NVIC_MPU_REGION_BASE_ADDRESS_VALID_MASK                                 (0x00000010U)

#define IPU_CM3_NVIC_MPU_REGION_BASE_ADDRESS_ADDR_SHIFT                                 (8U)
#define IPU_CM3_NVIC_MPU_REGION_BASE_ADDRESS_ADDR_MASK                                  (0xffffff00U)

#define IPU_CM3_NVIC_DEBUG_HALTING_CONTROL_AND_STATUS_C_DEBUGEN_SHIFT                   (0U)
#define IPU_CM3_NVIC_DEBUG_HALTING_CONTROL_AND_STATUS_C_DEBUGEN_MASK                    (0x00000001U)

#define IPU_CM3_NVIC_DEBUG_HALTING_CONTROL_AND_STATUS_C_HALT_SHIFT                      (1U)
#define IPU_CM3_NVIC_DEBUG_HALTING_CONTROL_AND_STATUS_C_HALT_MASK                       (0x00000002U)

#define IPU_CM3_NVIC_DEBUG_HALTING_CONTROL_AND_STATUS_C_STEP_SHIFT                      (2U)
#define IPU_CM3_NVIC_DEBUG_HALTING_CONTROL_AND_STATUS_C_STEP_MASK                       (0x00000004U)

#define IPU_CM3_NVIC_DEBUG_HALTING_CONTROL_AND_STATUS_C_MASKINTS_SHIFT                  (3U)
#define IPU_CM3_NVIC_DEBUG_HALTING_CONTROL_AND_STATUS_C_MASKINTS_MASK                   (0x00000008U)

#define IPU_CM3_NVIC_DEBUG_HALTING_CONTROL_AND_STATUS_C_SNAPSTALL_SHIFT                 (5U)
#define IPU_CM3_NVIC_DEBUG_HALTING_CONTROL_AND_STATUS_C_SNAPSTALL_MASK                  (0x00000020U)

#define IPU_CM3_NVIC_DEBUG_HALTING_CONTROL_AND_STATUS_S_REGRDY_SHIFT                    (16U)
#define IPU_CM3_NVIC_DEBUG_HALTING_CONTROL_AND_STATUS_S_REGRDY_MASK                     (0x00010000U)

#define IPU_CM3_NVIC_DEBUG_HALTING_CONTROL_AND_STATUS_S_HALT_SHIFT                      (17U)
#define IPU_CM3_NVIC_DEBUG_HALTING_CONTROL_AND_STATUS_S_HALT_MASK                       (0x00020000U)

#define IPU_CM3_NVIC_DEBUG_HALTING_CONTROL_AND_STATUS_S_SLEEP_SHIFT                     (18U)
#define IPU_CM3_NVIC_DEBUG_HALTING_CONTROL_AND_STATUS_S_SLEEP_MASK                      (0x00040000U)

#define IPU_CM3_NVIC_DEBUG_HALTING_CONTROL_AND_STATUS_S_LOCKUP_SHIFT                    (19U)
#define IPU_CM3_NVIC_DEBUG_HALTING_CONTROL_AND_STATUS_S_LOCKUP_MASK                     (0x00080000U)

#define IPU_CM3_NVIC_DEBUG_HALTING_CONTROL_AND_STATUS_S_RETIRE_ST_SHIFT                 (24U)
#define IPU_CM3_NVIC_DEBUG_HALTING_CONTROL_AND_STATUS_S_RETIRE_ST_MASK                  (0x01000000U)

#define IPU_CM3_NVIC_DEBUG_HALTING_CONTROL_AND_STATUS_S_RESET_ST_SHIFT                  (25U)
#define IPU_CM3_NVIC_DEBUG_HALTING_CONTROL_AND_STATUS_S_RESET_ST_MASK                   (0x02000000U)

#define IPU_CM3_NVIC_DEBUG_HALTING_CONTROL_AND_STATUS_KEY_SHIFT                         (26U)
#define IPU_CM3_NVIC_DEBUG_HALTING_CONTROL_AND_STATUS_KEY_MASK                          (0xfc000000U)

#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_SELECTOR_REGSEL_SHIFT                          (0U)
#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_SELECTOR_REGSEL_MASK                           (0x0000001fU)
#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_SELECTOR_REGSEL_R0                              (0U)
#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_SELECTOR_REGSEL_R1                              (1U)
#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_SELECTOR_REGSEL_R2                              (2U)
#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_SELECTOR_REGSEL_R3                              (3U)
#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_SELECTOR_REGSEL_R4                              (4U)
#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_SELECTOR_REGSEL_R5                              (5U)
#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_SELECTOR_REGSEL_R6                              (6U)
#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_SELECTOR_REGSEL_R7                              (7U)
#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_SELECTOR_REGSEL_R8                              (8U)
#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_SELECTOR_REGSEL_R9                              (9U)
#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_SELECTOR_REGSEL_R10                             (10U)
#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_SELECTOR_REGSEL_R11                             (11U)
#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_SELECTOR_REGSEL_R12                             (12U)
#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_SELECTOR_REGSEL_R13                             (13U)
#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_SELECTOR_REGSEL_R14                             (14U)
#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_SELECTOR_REGSEL_R15                             (15U)
#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_SELECTOR_REGSEL_XPSR_FLAGS                      (16U)
#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_SELECTOR_REGSEL_MSP                             (17U)
#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_SELECTOR_REGSEL_PSP                             (18U)
#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_SELECTOR_REGSEL_SPECIAL_REGISTERS               (19U)

#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_SELECTOR_REGWNR_SHIFT                          (16U)
#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_SELECTOR_REGWNR_MASK                           (0x00010000U)

#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_DATA_SHIFT                                     (0U)
#define IPU_CM3_NVIC_DEBUG_CORE_REGISTER_DATA_MASK                                      (0xffffffffU)

#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL_VC_CORERESET_SHIFT             (0U)
#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL_VC_CORERESET_MASK              (0x00000001U)

#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL_VC_MMERR_SHIFT                 (4U)
#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL_VC_MMERR_MASK                  (0x00000010U)

#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL_VC_NOCPERR_SHIFT               (5U)
#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL_VC_NOCPERR_MASK                (0x00000020U)

#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL_VC_CHKERR_SHIFT                (6U)
#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL_VC_CHKERR_MASK                 (0x00000040U)

#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL_VC_STATERR_SHIFT               (7U)
#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL_VC_STATERR_MASK                (0x00000080U)

#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL_VC_BUSERR_SHIFT                (8U)
#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL_VC_BUSERR_MASK                 (0x00000100U)

#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL_VC_INTERR_SHIFT                (9U)
#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL_VC_INTERR_MASK                 (0x00000200U)

#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL_VC_HARDERR_SHIFT               (10U)
#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL_VC_HARDERR_MASK                (0x00000400U)

#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL_MON_EN_SHIFT                   (16U)
#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL_MON_EN_MASK                    (0x00010000U)

#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL_MON_PEND_SHIFT                 (17U)
#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL_MON_PEND_MASK                  (0x00020000U)

#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL_MON_STEP_SHIFT                 (18U)
#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL_MON_STEP_MASK                  (0x00040000U)

#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL_MON_REQ_SHIFT                  (19U)
#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL_MON_REQ_MASK                   (0x00080000U)

#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL_TRC_ENA_SHIFT                  (24U)
#define IPU_CM3_NVIC_DEBUG_EXCEPTION_AND_MONITOR_CONTROL_TRC_ENA_MASK                   (0x01000000U)

#define IPU_CM3_NVIC_SOFTWARE_TRIGGER_INTERRUPT_INTID_SHIFT                             (0U)
#define IPU_CM3_NVIC_SOFTWARE_TRIGGER_INTERRUPT_INTID_MASK                              (0x000001ffU)

#define IPU_CM3_NVIC_PERIPHERAL_ID_4_PERIPHID4_SHIFT                                    (0U)
#define IPU_CM3_NVIC_PERIPHERAL_ID_4_PERIPHID4_MASK                                     (0x000000ffU)

#define IPU_CM3_NVIC_PERIPHERAL_ID_5_PERIPHID5_SHIFT                                    (0U)
#define IPU_CM3_NVIC_PERIPHERAL_ID_5_PERIPHID5_MASK                                     (0x000000ffU)

#define IPU_CM3_NVIC_PERIPHERAL_ID_6_PERIPHID6_SHIFT                                    (0U)
#define IPU_CM3_NVIC_PERIPHERAL_ID_6_PERIPHID6_MASK                                     (0x000000ffU)

#define IPU_CM3_NVIC_PERIPHERAL_ID_7_PERIPHID7_SHIFT                                    (0U)
#define IPU_CM3_NVIC_PERIPHERAL_ID_7_PERIPHID7_MASK                                     (0x000000ffU)

#define IPU_CM3_NVIC_PERIPHERAL_ID_0_PERIPHID0_SHIFT                                    (0U)
#define IPU_CM3_NVIC_PERIPHERAL_ID_0_PERIPHID0_MASK                                     (0x000000ffU)

#define IPU_CM3_NVIC_PERIPHERAL_ID_1_PERIPHID1_SHIFT                                    (0U)
#define IPU_CM3_NVIC_PERIPHERAL_ID_1_PERIPHID1_MASK                                     (0x000000ffU)

#define IPU_CM3_NVIC_PERIPHERAL_ID_2_PERIPHID2_SHIFT                                    (0U)
#define IPU_CM3_NVIC_PERIPHERAL_ID_2_PERIPHID2_MASK                                     (0x000000ffU)

#define IPU_CM3_NVIC_PERIPHERAL_ID_3_PERIPHID3_SHIFT                                    (0U)
#define IPU_CM3_NVIC_PERIPHERAL_ID_3_PERIPHID3_MASK                                     (0x000000ffU)

#define IPU_CM3_NVIC_COMPONENT_ID_0_PCELLID0_SHIFT                                      (0U)
#define IPU_CM3_NVIC_COMPONENT_ID_0_PCELLID0_MASK                                       (0x000000ffU)

#define IPU_CM3_NVIC_COMPONENT_ID_1_PCELLID1_SHIFT                                      (0U)
#define IPU_CM3_NVIC_COMPONENT_ID_1_PCELLID1_MASK                                       (0x000000ffU)

#define IPU_CM3_NVIC_COMPONENT_ID_2_PCELLID2_SHIFT                                      (0U)
#define IPU_CM3_NVIC_COMPONENT_ID_2_PCELLID2_MASK                                       (0x000000ffU)

#define IPU_CM3_NVIC_COMPONENT_ID_3_PCELLID3_SHIFT                                      (0U)
#define IPU_CM3_NVIC_COMPONENT_ID_3_PCELLID3_MASK                                       (0x000000ffU)

#ifdef __cplusplus
}
#endif
#endif  /* HW_IPU_CM3_NVIC_H_ */

