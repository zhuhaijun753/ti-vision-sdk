/******************************************************************************
*
* hw_mpu_prcm_prmc0.h - register-level header file for MPU
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
#ifndef HW_MPU_PRCM_PRMC0_H_
#define HW_MPU_PRCM_PRMC0_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define MPU_PM_CPU0_PWRSTCTRL                                                                               (0x0U)
#define MPU_PM_CPU0_PWRSTST                                                                                 (0x4U)
#define MPU_RM_CPU0_CPU0_RSTCTRL                                                                            (0x10U)
#define MPU_RM_CPU0_CPU0_RSTST                                                                              (0x14U)
#define MPU_RM_CPU0_CPU0_CONTEXT                                                                            (0x24U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define MPU_PM_CPU0_PWRSTCTRL_L1_BANK_ONSTATE_SHIFT                                                         (16U)
#define MPU_PM_CPU0_PWRSTCTRL_L1_BANK_ONSTATE_MASK                                                          (0x00030000U)
#define MPU_PM_CPU0_PWRSTCTRL_L1_BANK_ONSTATE_MEM_ON                                                         (3U)

#define MPU_PM_CPU0_PWRSTCTRL_POWERSTATE_SHIFT                                                              (0U)
#define MPU_PM_CPU0_PWRSTCTRL_POWERSTATE_MASK                                                               (0x00000003U)
#define MPU_PM_CPU0_PWRSTCTRL_POWERSTATE_OFF                                                                 (0U)
#define MPU_PM_CPU0_PWRSTCTRL_POWERSTATE_INACT                                                               (2U)
#define MPU_PM_CPU0_PWRSTCTRL_POWERSTATE_RET                                                                 (1U)
#define MPU_PM_CPU0_PWRSTCTRL_POWERSTATE_ON                                                                  (3U)

#define MPU_PM_CPU0_PWRSTCTRL_RESERVED3_SHIFT                                                               (18U)
#define MPU_PM_CPU0_PWRSTCTRL_RESERVED3_MASK                                                                (0xfffc0000U)

#define MPU_PM_CPU0_PWRSTCTRL_L1_BANK_RETSTATE_SHIFT                                                        (8U)
#define MPU_PM_CPU0_PWRSTCTRL_L1_BANK_RETSTATE_MASK                                                         (0x00000100U)
#define MPU_PM_CPU0_PWRSTCTRL_L1_BANK_RETSTATE_MEM_RET                                                       (1U)

#define MPU_PM_CPU0_PWRSTCTRL_RESERVED2_SHIFT                                                               (9U)
#define MPU_PM_CPU0_PWRSTCTRL_RESERVED2_MASK                                                                (0x0000fe00U)

#define MPU_PM_CPU0_PWRSTCTRL_RESERVED1_SHIFT                                                               (3U)
#define MPU_PM_CPU0_PWRSTCTRL_RESERVED1_MASK                                                                (0x000000f8U)

#define MPU_PM_CPU0_PWRSTCTRL_LOGICRETSTATE_SHIFT                                                           (2U)
#define MPU_PM_CPU0_PWRSTCTRL_LOGICRETSTATE_MASK                                                            (0x00000004U)
#define MPU_PM_CPU0_PWRSTCTRL_LOGICRETSTATE_LOGIC_RET                                                        (1U)

#define MPU_PM_CPU0_PWRSTST_POWERSTATEST_SHIFT                                                              (0U)
#define MPU_PM_CPU0_PWRSTST_POWERSTATEST_MASK                                                               (0x00000003U)
#define MPU_PM_CPU0_PWRSTST_POWERSTATEST_ON                                                                  (3U)
#define MPU_PM_CPU0_PWRSTST_POWERSTATEST_OFF                                                                 (0U)
#define MPU_PM_CPU0_PWRSTST_POWERSTATEST_RET                                                                 (1U)
#define MPU_PM_CPU0_PWRSTST_POWERSTATEST_INACTIVE                                                            (2U)

#define MPU_PM_CPU0_PWRSTST_INTRANSITION_SHIFT                                                              (20U)
#define MPU_PM_CPU0_PWRSTST_INTRANSITION_MASK                                                               (0x00100000U)
#define MPU_PM_CPU0_PWRSTST_INTRANSITION_NO                                                                  (0U)
#define MPU_PM_CPU0_PWRSTST_INTRANSITION_ONGOING                                                             (1U)

#define MPU_PM_CPU0_PWRSTST_LOGICSTATEST_SHIFT                                                              (2U)
#define MPU_PM_CPU0_PWRSTST_LOGICSTATEST_MASK                                                               (0x00000004U)
#define MPU_PM_CPU0_PWRSTST_LOGICSTATEST_ON                                                                  (1U)
#define MPU_PM_CPU0_PWRSTST_LOGICSTATEST_OFF                                                                 (0U)

#define MPU_PM_CPU0_PWRSTST_L1_BANK_STATEST_SHIFT                                                           (4U)
#define MPU_PM_CPU0_PWRSTST_L1_BANK_STATEST_MASK                                                            (0x00000030U)
#define MPU_PM_CPU0_PWRSTST_L1_BANK_STATEST_MEM_OFF                                                          (0U)
#define MPU_PM_CPU0_PWRSTST_L1_BANK_STATEST_MEM_RET                                                          (1U)
#define MPU_PM_CPU0_PWRSTST_L1_BANK_STATEST_RESERVED                                                         (2U)
#define MPU_PM_CPU0_PWRSTST_L1_BANK_STATEST_MEM_ON                                                           (3U)

#define MPU_PM_CPU0_PWRSTST_RESERVED_SHIFT                                                                  (3U)
#define MPU_PM_CPU0_PWRSTST_RESERVED_MASK                                                                   (0x00000008U)

#define MPU_PM_CPU0_PWRSTST_RESERVED1_SHIFT                                                                 (6U)
#define MPU_PM_CPU0_PWRSTST_RESERVED1_MASK                                                                  (0x000fffc0U)

#define MPU_PM_CPU0_PWRSTST_RESERVED2_SHIFT                                                                 (21U)
#define MPU_PM_CPU0_PWRSTST_RESERVED2_MASK                                                                  (0x00e00000U)

#define MPU_PM_CPU0_PWRSTST_LASTPOWERSTATEENTERED_SHIFT                                                     (24U)
#define MPU_PM_CPU0_PWRSTST_LASTPOWERSTATEENTERED_MASK                                                      (0x03000000U)
#define MPU_PM_CPU0_PWRSTST_LASTPOWERSTATEENTERED_ON                                                         (3U)
#define MPU_PM_CPU0_PWRSTST_LASTPOWERSTATEENTERED_OFF                                                        (0U)
#define MPU_PM_CPU0_PWRSTST_LASTPOWERSTATEENTERED_RET                                                        (1U)
#define MPU_PM_CPU0_PWRSTST_LASTPOWERSTATEENTERED_INACT                                                      (2U)

#define MPU_PM_CPU0_PWRSTST_RESERVED4_SHIFT                                                                 (26U)
#define MPU_PM_CPU0_PWRSTST_RESERVED4_MASK                                                                  (0xfc000000U)

#define MPU_RM_CPU0_CPU0_RSTCTRL_RST_SHIFT                                                                  (0U)
#define MPU_RM_CPU0_CPU0_RSTCTRL_RST_MASK                                                                   (0x00000001U)
#define MPU_RM_CPU0_CPU0_RSTCTRL_RST_ASSERT                                                                  (1U)
#define MPU_RM_CPU0_CPU0_RSTCTRL_RST_CLEAR                                                                   (0U)

#define MPU_RM_CPU0_CPU0_RSTCTRL_RESERVED_SHIFT                                                             (1U)
#define MPU_RM_CPU0_CPU0_RSTCTRL_RESERVED_MASK                                                              (0xfffffffeU)

#define MPU_RM_CPU0_CPU0_RSTST_RSTST_SHIFT                                                                  (0U)
#define MPU_RM_CPU0_CPU0_RSTST_RSTST_MASK                                                                   (0x00000001U)
#define MPU_RM_CPU0_CPU0_RSTST_RSTST_CLEAR                                                                   (0U)
#define MPU_RM_CPU0_CPU0_RSTST_RSTST_ASSERT                                                                  (1U)

#define MPU_RM_CPU0_CPU0_RSTST_RESERVED_SHIFT                                                               (2U)
#define MPU_RM_CPU0_CPU0_RSTST_RESERVED_MASK                                                                (0xfffffffcU)

#define MPU_RM_CPU0_CPU0_RSTST_DBGRST_REQ_RSTST_SHIFT                                                       (1U)
#define MPU_RM_CPU0_CPU0_RSTST_DBGRST_REQ_RSTST_MASK                                                        (0x00000002U)
#define MPU_RM_CPU0_CPU0_RSTST_DBGRST_REQ_RSTST_CLEAR                                                        (0U)
#define MPU_RM_CPU0_CPU0_RSTST_DBGRST_REQ_RSTST_ASSERT                                                       (1U)

#define MPU_RM_CPU0_CPU0_CONTEXT_RESERVED_SHIFT                                                             (1U)
#define MPU_RM_CPU0_CPU0_CONTEXT_RESERVED_MASK                                                              (0x000000feU)

#define MPU_RM_CPU0_CPU0_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                      (0U)
#define MPU_RM_CPU0_CPU0_CONTEXT_LOSTCONTEXT_DFF_MASK                                                       (0x00000001U)
#define MPU_RM_CPU0_CPU0_CONTEXT_LOSTCONTEXT_DFF_LOST                                                        (1U)
#define MPU_RM_CPU0_CPU0_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                  (0U)

#define MPU_RM_CPU0_CPU0_CONTEXT_LOSTMEM_CPU_L1_SHIFT                                                       (8U)
#define MPU_RM_CPU0_CPU0_CONTEXT_LOSTMEM_CPU_L1_MASK                                                        (0x00000100U)
#define MPU_RM_CPU0_CPU0_CONTEXT_LOSTMEM_CPU_L1_LOST                                                         (1U)
#define MPU_RM_CPU0_CPU0_CONTEXT_LOSTMEM_CPU_L1_MAINTAINED                                                   (0U)

#define MPU_RM_CPU0_CPU0_CONTEXT_RESERVED1_SHIFT                                                            (9U)
#define MPU_RM_CPU0_CPU0_CONTEXT_RESERVED1_MASK                                                             (0xfffffe00U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_MPU_PRCM_PRMC0_H_ */
