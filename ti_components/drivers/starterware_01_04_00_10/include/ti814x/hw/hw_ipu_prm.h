/******************************************************************************
*
* hw_ipu_prm.h - register-level header file for PRCM
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
#ifndef HW_IPU_PRM_H_
#define HW_IPU_PRM_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define PM_IPU_PWRSTCTRL                                                                                    (0x0U)
#define PM_IPU_PWRSTST                                                                                      (0x4U)
#define RM_IPU1_RSTCTRL                                                                                     (0x10U)
#define RM_IPU1_RSTST                                                                                       (0x14U)
#define RM_IPU1_IPU1_CONTEXT                                                                                (0x24U)
#define PM_IPU_MCASP1_WKDEP                                                                                 (0x50U)
#define RM_IPU_MCASP1_CONTEXT                                                                               (0x54U)
#define PM_IPU_TIMER5_WKDEP                                                                                 (0x58U)
#define RM_IPU_TIMER5_CONTEXT                                                                               (0x5cU)
#define PM_IPU_TIMER6_WKDEP                                                                                 (0x60U)
#define RM_IPU_TIMER6_CONTEXT                                                                               (0x64U)
#define PM_IPU_TIMER7_WKDEP                                                                                 (0x68U)
#define RM_IPU_TIMER7_CONTEXT                                                                               (0x6cU)
#define PM_IPU_TIMER8_WKDEP                                                                                 (0x70U)
#define RM_IPU_TIMER8_CONTEXT                                                                               (0x74U)
#define PM_IPU_I2C5_WKDEP                                                                                   (0x78U)
#define RM_IPU_I2C5_CONTEXT                                                                                 (0x7cU)
#define PM_IPU_UART6_WKDEP                                                                                  (0x80U)
#define RM_IPU_UART6_CONTEXT                                                                                (0x84U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define PM_IPU_PWRSTCTRL_AESSMEM_RETSTATE_SHIFT                                                             (8U)
#define PM_IPU_PWRSTCTRL_AESSMEM_RETSTATE_MASK                                                              (0x00000100U)
#define PM_IPU_PWRSTCTRL_AESSMEM_RETSTATE_MEM_RET                                                            (1U)
#define PM_IPU_PWRSTCTRL_AESSMEM_RETSTATE_MEM_OFF                                                            (0U)

#define PM_IPU_PWRSTCTRL_AESSMEM_ONSTATE_SHIFT                                                              (16U)
#define PM_IPU_PWRSTCTRL_AESSMEM_ONSTATE_MASK                                                               (0x00030000U)
#define PM_IPU_PWRSTCTRL_AESSMEM_ONSTATE_MEM_ON                                                              (3U)

#define PM_IPU_PWRSTCTRL_LOGICRETSTATE_SHIFT                                                                (2U)
#define PM_IPU_PWRSTCTRL_LOGICRETSTATE_MASK                                                                 (0x00000004U)
#define PM_IPU_PWRSTCTRL_LOGICRETSTATE_LOGIC_OFF                                                             (0U)

#define PM_IPU_PWRSTCTRL_POWERSTATE_SHIFT                                                                   (0U)
#define PM_IPU_PWRSTCTRL_POWERSTATE_MASK                                                                    (0x00000003U)
#define PM_IPU_PWRSTCTRL_POWERSTATE_OFF                                                                      (0U)
#define PM_IPU_PWRSTCTRL_POWERSTATE_INACT                                                                    (2U)
#define PM_IPU_PWRSTCTRL_POWERSTATE_RET                                                                      (1U)
#define PM_IPU_PWRSTCTRL_POWERSTATE_ON                                                                       (3U)

#define PM_IPU_PWRSTCTRL_PERIPHMEM_RETSTATE_SHIFT                                                           (10U)
#define PM_IPU_PWRSTCTRL_PERIPHMEM_RETSTATE_MASK                                                            (0x00000400U)
#define PM_IPU_PWRSTCTRL_PERIPHMEM_RETSTATE_MEM_OFF                                                          (0U)
#define PM_IPU_PWRSTCTRL_PERIPHMEM_RETSTATE_MEM_RET                                                          (1U)

#define PM_IPU_PWRSTCTRL_PERIPHMEM_ONSTATE_SHIFT                                                            (20U)
#define PM_IPU_PWRSTCTRL_PERIPHMEM_ONSTATE_MASK                                                             (0x00300000U)
#define PM_IPU_PWRSTCTRL_PERIPHMEM_ONSTATE_MEM_ON                                                            (3U)

#define PM_IPU_PWRSTCTRL_RESERVED1_SHIFT                                                                    (11U)
#define PM_IPU_PWRSTCTRL_RESERVED1_MASK                                                                     (0x0000f800U)

#define PM_IPU_PWRSTCTRL_RESERVED2_SHIFT                                                                    (22U)
#define PM_IPU_PWRSTCTRL_RESERVED2_MASK                                                                     (0xffc00000U)

#define PM_IPU_PWRSTCTRL_RESERVED3_SHIFT                                                                    (9U)
#define PM_IPU_PWRSTCTRL_RESERVED3_MASK                                                                     (0x00000200U)

#define PM_IPU_PWRSTCTRL_RESERVED4_SHIFT                                                                    (18U)
#define PM_IPU_PWRSTCTRL_RESERVED4_MASK                                                                     (0x000c0000U)

#define PM_IPU_PWRSTCTRL_LOWPOWERSTATECHANGE_SHIFT                                                          (4U)
#define PM_IPU_PWRSTCTRL_LOWPOWERSTATECHANGE_MASK                                                           (0x00000010U)
#define PM_IPU_PWRSTCTRL_LOWPOWERSTATECHANGE_EN                                                              (1U)
#define PM_IPU_PWRSTCTRL_LOWPOWERSTATECHANGE_DIS                                                             (0U)

#define PM_IPU_PWRSTCTRL_RESERVED_SHIFT                                                                     (3U)
#define PM_IPU_PWRSTCTRL_RESERVED_MASK                                                                      (0x00000008U)

#define PM_IPU_PWRSTCTRL_RESERVED5_SHIFT                                                                    (5U)
#define PM_IPU_PWRSTCTRL_RESERVED5_MASK                                                                     (0x000000e0U)

#define PM_IPU_PWRSTST_POWERSTATEST_SHIFT                                                                   (0U)
#define PM_IPU_PWRSTST_POWERSTATEST_MASK                                                                    (0x00000003U)
#define PM_IPU_PWRSTST_POWERSTATEST_ON                                                                       (3U)
#define PM_IPU_PWRSTST_POWERSTATEST_OFF                                                                      (0U)
#define PM_IPU_PWRSTST_POWERSTATEST_RET                                                                      (1U)
#define PM_IPU_PWRSTST_POWERSTATEST_INACTIVE                                                                 (2U)

#define PM_IPU_PWRSTST_INTRANSITION_SHIFT                                                                   (20U)
#define PM_IPU_PWRSTST_INTRANSITION_MASK                                                                    (0x00100000U)
#define PM_IPU_PWRSTST_INTRANSITION_NO                                                                       (0U)
#define PM_IPU_PWRSTST_INTRANSITION_ONGOING                                                                  (1U)

#define PM_IPU_PWRSTST_LOGICSTATEST_SHIFT                                                                   (2U)
#define PM_IPU_PWRSTST_LOGICSTATEST_MASK                                                                    (0x00000004U)
#define PM_IPU_PWRSTST_LOGICSTATEST_ON                                                                       (1U)
#define PM_IPU_PWRSTST_LOGICSTATEST_OFF                                                                      (0U)

#define PM_IPU_PWRSTST_AESSMEM_STATEST_SHIFT                                                                (4U)
#define PM_IPU_PWRSTST_AESSMEM_STATEST_MASK                                                                 (0x00000030U)
#define PM_IPU_PWRSTST_AESSMEM_STATEST_MEM_ON                                                                (3U)
#define PM_IPU_PWRSTST_AESSMEM_STATEST_MEM_RET                                                               (1U)
#define PM_IPU_PWRSTST_AESSMEM_STATEST_MEM_OFF                                                               (0U)
#define PM_IPU_PWRSTST_AESSMEM_STATEST_RESERVED                                                              (2U)

#define PM_IPU_PWRSTST_RESERVED_SHIFT                                                                       (3U)
#define PM_IPU_PWRSTST_RESERVED_MASK                                                                        (0x00000008U)

#define PM_IPU_PWRSTST_PERIPHMEM_STATEST_SHIFT                                                              (8U)
#define PM_IPU_PWRSTST_PERIPHMEM_STATEST_MASK                                                               (0x00000300U)
#define PM_IPU_PWRSTST_PERIPHMEM_STATEST_MEM_ON                                                              (3U)
#define PM_IPU_PWRSTST_PERIPHMEM_STATEST_RESERVED1                                                           (1U)
#define PM_IPU_PWRSTST_PERIPHMEM_STATEST_MEM_OFF                                                             (0U)
#define PM_IPU_PWRSTST_PERIPHMEM_STATEST_RESERVED                                                            (2U)

#define PM_IPU_PWRSTST_RESERVED1_SHIFT                                                                      (10U)
#define PM_IPU_PWRSTST_RESERVED1_MASK                                                                       (0x000ffc00U)

#define PM_IPU_PWRSTST_RESERVED3_SHIFT                                                                      (6U)
#define PM_IPU_PWRSTST_RESERVED3_MASK                                                                       (0x000000c0U)

#define PM_IPU_PWRSTST_RESERVED2_SHIFT                                                                      (21U)
#define PM_IPU_PWRSTST_RESERVED2_MASK                                                                       (0x00e00000U)

#define PM_IPU_PWRSTST_RESERVED4_SHIFT                                                                      (26U)
#define PM_IPU_PWRSTST_RESERVED4_MASK                                                                       (0xfc000000U)

#define PM_IPU_PWRSTST_LASTPOWERSTATEENTERED_SHIFT                                                          (24U)
#define PM_IPU_PWRSTST_LASTPOWERSTATEENTERED_MASK                                                           (0x03000000U)
#define PM_IPU_PWRSTST_LASTPOWERSTATEENTERED_ON                                                              (3U)
#define PM_IPU_PWRSTST_LASTPOWERSTATEENTERED_OFF                                                             (0U)
#define PM_IPU_PWRSTST_LASTPOWERSTATEENTERED_RET                                                             (1U)
#define PM_IPU_PWRSTST_LASTPOWERSTATEENTERED_INACTIVE                                                        (2U)

#define RM_IPU1_RSTCTRL_RST_CPU0_SHIFT                                                                      (0U)
#define RM_IPU1_RSTCTRL_RST_CPU0_MASK                                                                       (0x00000001U)
#define RM_IPU1_RSTCTRL_RST_CPU0_ASSERT                                                                      (1U)
#define RM_IPU1_RSTCTRL_RST_CPU0_CLEAR                                                                       (0U)

#define RM_IPU1_RSTCTRL_RST_CPU1_SHIFT                                                                      (1U)
#define RM_IPU1_RSTCTRL_RST_CPU1_MASK                                                                       (0x00000002U)
#define RM_IPU1_RSTCTRL_RST_CPU1_ASSERT                                                                      (1U)
#define RM_IPU1_RSTCTRL_RST_CPU1_CLEAR                                                                       (0U)

#define RM_IPU1_RSTCTRL_RST_IPU_SHIFT                                                                       (2U)
#define RM_IPU1_RSTCTRL_RST_IPU_MASK                                                                        (0x00000004U)
#define RM_IPU1_RSTCTRL_RST_IPU_ASSERT                                                                       (1U)
#define RM_IPU1_RSTCTRL_RST_IPU_CLEAR                                                                        (0U)

#define RM_IPU1_RSTCTRL_RESERVED_SHIFT                                                                      (3U)
#define RM_IPU1_RSTCTRL_RESERVED_MASK                                                                       (0xfffffff8U)

#define RM_IPU1_RSTST_RST_EMULATION_CPU0_SHIFT                                                              (3U)
#define RM_IPU1_RSTST_RST_EMULATION_CPU0_MASK                                                               (0x00000008U)
#define RM_IPU1_RSTST_RST_EMULATION_CPU0_RESET_YES                                                           (1U)
#define RM_IPU1_RSTST_RST_EMULATION_CPU0_RESET_NO                                                            (0U)

#define RM_IPU1_RSTST_RST_EMULATION_CPU1_SHIFT                                                              (4U)
#define RM_IPU1_RSTST_RST_EMULATION_CPU1_MASK                                                               (0x00000010U)
#define RM_IPU1_RSTST_RST_EMULATION_CPU1_RESET_YES                                                           (1U)
#define RM_IPU1_RSTST_RST_EMULATION_CPU1_RESET_NO                                                            (0U)

#define RM_IPU1_RSTST_RST_CPU0_SHIFT                                                                        (0U)
#define RM_IPU1_RSTST_RST_CPU0_MASK                                                                         (0x00000001U)
#define RM_IPU1_RSTST_RST_CPU0_RESET_YES                                                                     (1U)
#define RM_IPU1_RSTST_RST_CPU0_RESET_NO                                                                      (0U)

#define RM_IPU1_RSTST_RST_CPU1_SHIFT                                                                        (1U)
#define RM_IPU1_RSTST_RST_CPU1_MASK                                                                         (0x00000002U)
#define RM_IPU1_RSTST_RST_CPU1_RESET_YES                                                                     (1U)
#define RM_IPU1_RSTST_RST_CPU1_RESET_NO                                                                      (0U)

#define RM_IPU1_RSTST_RST_IPU_SHIFT                                                                         (2U)
#define RM_IPU1_RSTST_RST_IPU_MASK                                                                          (0x00000004U)
#define RM_IPU1_RSTST_RST_IPU_RESET_YES                                                                      (1U)
#define RM_IPU1_RSTST_RST_IPU_RESET_NO                                                                       (0U)

#define RM_IPU1_RSTST_RST_ICECRUSHER_CPU0_SHIFT                                                             (5U)
#define RM_IPU1_RSTST_RST_ICECRUSHER_CPU0_MASK                                                              (0x00000020U)
#define RM_IPU1_RSTST_RST_ICECRUSHER_CPU0_RESET_YES                                                          (1U)
#define RM_IPU1_RSTST_RST_ICECRUSHER_CPU0_RESET_NO                                                           (0U)

#define RM_IPU1_RSTST_RST_ICECRUSHER_CPU1_SHIFT                                                             (6U)
#define RM_IPU1_RSTST_RST_ICECRUSHER_CPU1_MASK                                                              (0x00000040U)
#define RM_IPU1_RSTST_RST_ICECRUSHER_CPU1_RESET_YES                                                          (1U)
#define RM_IPU1_RSTST_RST_ICECRUSHER_CPU1_RESET_NO                                                           (0U)

#define RM_IPU1_RSTST_RESERVED_SHIFT                                                                        (7U)
#define RM_IPU1_RSTST_RESERVED_MASK                                                                         (0xffffff80U)

#define RM_IPU1_IPU1_CONTEXT_RESERVED1_SHIFT                                                                (10U)
#define RM_IPU1_IPU1_CONTEXT_RESERVED1_MASK                                                                 (0xfffffc00U)

#define RM_IPU1_IPU1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                          (0U)
#define RM_IPU1_IPU1_CONTEXT_LOSTCONTEXT_DFF_MASK                                                           (0x00000001U)
#define RM_IPU1_IPU1_CONTEXT_LOSTCONTEXT_DFF_LOST                                                            (1U)
#define RM_IPU1_IPU1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                      (0U)

#define RM_IPU1_IPU1_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                          (1U)
#define RM_IPU1_IPU1_CONTEXT_LOSTCONTEXT_RFF_MASK                                                           (0x00000002U)
#define RM_IPU1_IPU1_CONTEXT_LOSTCONTEXT_RFF_LOST                                                            (1U)
#define RM_IPU1_IPU1_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                      (0U)

#define RM_IPU1_IPU1_CONTEXT_RESERVED_SHIFT                                                                 (2U)
#define RM_IPU1_IPU1_CONTEXT_RESERVED_MASK                                                                  (0x000000fcU)

#define RM_IPU1_IPU1_CONTEXT_LOSTMEM_IPU_UNICACHE_SHIFT                                                     (8U)
#define RM_IPU1_IPU1_CONTEXT_LOSTMEM_IPU_UNICACHE_MASK                                                      (0x00000100U)
#define RM_IPU1_IPU1_CONTEXT_LOSTMEM_IPU_UNICACHE_LOST                                                       (1U)
#define RM_IPU1_IPU1_CONTEXT_LOSTMEM_IPU_UNICACHE_MAINTAINED                                                 (0U)

#define RM_IPU1_IPU1_CONTEXT_LOSTMEM_IPU_L2RAM_SHIFT                                                        (9U)
#define RM_IPU1_IPU1_CONTEXT_LOSTMEM_IPU_L2RAM_MASK                                                         (0x00000200U)
#define RM_IPU1_IPU1_CONTEXT_LOSTMEM_IPU_L2RAM_LOST                                                          (1U)
#define RM_IPU1_IPU1_CONTEXT_LOSTMEM_IPU_L2RAM_MAINTAINED                                                    (0U)

#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_MPU_SHIFT                                                    (0U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_MPU_MASK                                                     (0x00000001U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_MPU_ENABLED                                                   (1U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_MPU_DISABLED                                                  (0U)

#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_DSP1_SHIFT                                                   (2U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_DSP1_MASK                                                    (0x00000004U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_DSP1_ENABLED                                                  (1U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_DSP1_DISABLED                                                 (0U)

#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_IPU2_SHIFT                                                   (1U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_IPU2_MASK                                                    (0x00000002U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_IPU2_ENABLED                                                  (1U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_IPU2_DISABLED                                                 (0U)

#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_IPU1_SHIFT                                                   (4U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_IPU1_MASK                                                    (0x00000010U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_IPU1_ENABLED                                                  (1U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_IPU1_DISABLED                                                 (0U)

#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_DSP2_SHIFT                                                   (5U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_DSP2_MASK                                                    (0x00000020U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_DSP2_ENABLED                                                  (1U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_DSP2_DISABLED                                                 (0U)

#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_EVE1_SHIFT                                                   (6U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_EVE1_MASK                                                    (0x00000040U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_EVE1_ENABLED                                                  (1U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_EVE1_DISABLED                                                 (0U)

#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_EVE2_SHIFT                                                   (7U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_EVE2_MASK                                                    (0x00000080U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_EVE2_ENABLED                                                  (1U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_EVE2_DISABLED                                                 (0U)

#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_EVE3_SHIFT                                                   (8U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_EVE3_MASK                                                    (0x00000100U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_EVE3_ENABLED                                                  (1U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_EVE3_DISABLED                                                 (0U)

#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_EVE4_SHIFT                                                   (9U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_EVE4_MASK                                                    (0x00000200U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_EVE4_ENABLED                                                  (1U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_IRQ_EVE4_DISABLED                                                 (0U)

#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_DMA_SDMA_SHIFT                                                   (13U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_DMA_SDMA_MASK                                                    (0x00002000U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_DMA_SDMA_ENABLED                                                  (1U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_DMA_SDMA_DISABLED                                                 (0U)

#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_DMA_DSP1_SHIFT                                                   (12U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_DMA_DSP1_MASK                                                    (0x00001000U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_DMA_DSP1_ENABLED                                                  (1U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_DMA_DSP1_DISABLED                                                 (0U)

#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_DMA_DSP2_SHIFT                                                   (15U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_DMA_DSP2_MASK                                                    (0x00008000U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_DMA_DSP2_ENABLED                                                  (1U)
#define PM_IPU_MCASP1_WKDEP_WKUPDEP_MCASP1_DMA_DSP2_DISABLED                                                 (0U)

#define PM_IPU_MCASP1_WKDEP_RESERVED_SHIFT                                                                  (3U)
#define PM_IPU_MCASP1_WKDEP_RESERVED_MASK                                                                   (0x00000008U)

#define PM_IPU_MCASP1_WKDEP_RESERVED1_SHIFT                                                                 (10U)
#define PM_IPU_MCASP1_WKDEP_RESERVED1_MASK                                                                  (0x00000c00U)

#define PM_IPU_MCASP1_WKDEP_RESERVED2_SHIFT                                                                 (14U)
#define PM_IPU_MCASP1_WKDEP_RESERVED2_MASK                                                                  (0x00004000U)

#define PM_IPU_MCASP1_WKDEP_RESERVED3_SHIFT                                                                 (16U)
#define PM_IPU_MCASP1_WKDEP_RESERVED3_MASK                                                                  (0xffff0000U)

#define RM_IPU_MCASP1_CONTEXT_RESERVED_SHIFT                                                                (1U)
#define RM_IPU_MCASP1_CONTEXT_RESERVED_MASK                                                                 (0xfffffffeU)

#define RM_IPU_MCASP1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                         (0U)
#define RM_IPU_MCASP1_CONTEXT_LOSTCONTEXT_DFF_MASK                                                          (0x00000001U)
#define RM_IPU_MCASP1_CONTEXT_LOSTCONTEXT_DFF_LOST                                                           (1U)
#define RM_IPU_MCASP1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                     (0U)

#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_MPU_SHIFT                                                        (0U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_MPU_MASK                                                         (0x00000001U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_MPU_ENABLED                                                       (1U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_MPU_DISABLED                                                      (0U)

#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_IPU2_SHIFT                                                       (1U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_IPU2_MASK                                                        (0x00000002U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_IPU2_ENABLED                                                      (1U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_IPU2_DISABLED                                                     (0U)

#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_DSP1_SHIFT                                                       (2U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_DSP1_MASK                                                        (0x00000004U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_DSP1_ENABLED                                                      (1U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_DSP1_DISABLED                                                     (0U)

#define PM_IPU_TIMER5_WKDEP_RESERVED1_SHIFT                                                                 (3U)
#define PM_IPU_TIMER5_WKDEP_RESERVED1_MASK                                                                  (0x00000008U)

#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_IPU1_SHIFT                                                       (4U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_IPU1_MASK                                                        (0x00000010U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_IPU1_ENABLED                                                      (1U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_IPU1_DISABLED                                                     (0U)

#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_DSP2_SHIFT                                                       (5U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_DSP2_MASK                                                        (0x00000020U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_DSP2_ENABLED                                                      (1U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_DSP2_DISABLED                                                     (0U)

#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_EVE1_SHIFT                                                       (6U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_EVE1_MASK                                                        (0x00000040U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_EVE1_ENABLED                                                      (1U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_EVE1_DISABLED                                                     (0U)

#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_EVE2_SHIFT                                                       (7U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_EVE2_MASK                                                        (0x00000080U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_EVE2_ENABLED                                                      (1U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_EVE2_DISABLED                                                     (0U)

#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_EVE3_SHIFT                                                       (8U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_EVE3_MASK                                                        (0x00000100U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_EVE3_ENABLED                                                      (1U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_EVE3_DISABLED                                                     (0U)

#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_EVE4_SHIFT                                                       (9U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_EVE4_MASK                                                        (0x00000200U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_EVE4_ENABLED                                                      (1U)
#define PM_IPU_TIMER5_WKDEP_WKUPDEP_TIMER5_EVE4_DISABLED                                                     (0U)

#define PM_IPU_TIMER5_WKDEP_RESERVED_SHIFT                                                                  (10U)
#define PM_IPU_TIMER5_WKDEP_RESERVED_MASK                                                                   (0xfffffc00U)

#define RM_IPU_TIMER5_CONTEXT_RESERVED_SHIFT                                                                (1U)
#define RM_IPU_TIMER5_CONTEXT_RESERVED_MASK                                                                 (0xfffffffeU)

#define RM_IPU_TIMER5_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                         (0U)
#define RM_IPU_TIMER5_CONTEXT_LOSTCONTEXT_DFF_MASK                                                          (0x00000001U)
#define RM_IPU_TIMER5_CONTEXT_LOSTCONTEXT_DFF_LOST                                                           (1U)
#define RM_IPU_TIMER5_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                     (0U)

#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_MPU_SHIFT                                                        (0U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_MPU_MASK                                                         (0x00000001U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_MPU_ENABLED                                                       (1U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_MPU_DISABLED                                                      (0U)

#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_IPU2_SHIFT                                                       (1U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_IPU2_MASK                                                        (0x00000002U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_IPU2_ENABLED                                                      (1U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_IPU2_DISABLED                                                     (0U)

#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_DSP1_SHIFT                                                       (2U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_DSP1_MASK                                                        (0x00000004U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_DSP1_ENABLED                                                      (1U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_DSP1_DISABLED                                                     (0U)

#define PM_IPU_TIMER6_WKDEP_RESERVED1_SHIFT                                                                 (3U)
#define PM_IPU_TIMER6_WKDEP_RESERVED1_MASK                                                                  (0x00000008U)

#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_IPU1_SHIFT                                                       (4U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_IPU1_MASK                                                        (0x00000010U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_IPU1_ENABLED                                                      (1U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_IPU1_DISABLED                                                     (0U)

#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_DSP2_SHIFT                                                       (5U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_DSP2_MASK                                                        (0x00000020U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_DSP2_ENABLED                                                      (1U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_DSP2_DISABLED                                                     (0U)

#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_EVE1_SHIFT                                                       (6U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_EVE1_MASK                                                        (0x00000040U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_EVE1_ENABLED                                                      (1U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_EVE1_DISABLED                                                     (0U)

#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_EVE2_SHIFT                                                       (7U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_EVE2_MASK                                                        (0x00000080U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_EVE2_ENABLED                                                      (1U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_EVE2_DISABLED                                                     (0U)

#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_EVE3_SHIFT                                                       (8U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_EVE3_MASK                                                        (0x00000100U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_EVE3_ENABLED                                                      (1U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_EVE3_DISABLED                                                     (0U)

#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_EVE4_SHIFT                                                       (9U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_EVE4_MASK                                                        (0x00000200U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_EVE4_ENABLED                                                      (1U)
#define PM_IPU_TIMER6_WKDEP_WKUPDEP_TIMER6_EVE4_DISABLED                                                     (0U)

#define PM_IPU_TIMER6_WKDEP_RESERVED_SHIFT                                                                  (10U)
#define PM_IPU_TIMER6_WKDEP_RESERVED_MASK                                                                   (0xfffffc00U)

#define RM_IPU_TIMER6_CONTEXT_RESERVED_SHIFT                                                                (1U)
#define RM_IPU_TIMER6_CONTEXT_RESERVED_MASK                                                                 (0xfffffffeU)

#define RM_IPU_TIMER6_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                         (0U)
#define RM_IPU_TIMER6_CONTEXT_LOSTCONTEXT_DFF_MASK                                                          (0x00000001U)
#define RM_IPU_TIMER6_CONTEXT_LOSTCONTEXT_DFF_LOST                                                           (1U)
#define RM_IPU_TIMER6_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                     (0U)

#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_MPU_SHIFT                                                        (0U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_MPU_MASK                                                         (0x00000001U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_MPU_ENABLED                                                       (1U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_MPU_DISABLED                                                      (0U)

#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_IPU2_SHIFT                                                       (1U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_IPU2_MASK                                                        (0x00000002U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_IPU2_ENABLED                                                      (1U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_IPU2_DISABLED                                                     (0U)

#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_DSP1_SHIFT                                                       (2U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_DSP1_MASK                                                        (0x00000004U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_DSP1_ENABLED                                                      (1U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_DSP1_DISABLED                                                     (0U)

#define PM_IPU_TIMER7_WKDEP_RESERVED1_SHIFT                                                                 (3U)
#define PM_IPU_TIMER7_WKDEP_RESERVED1_MASK                                                                  (0x00000008U)

#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_IPU1_SHIFT                                                       (4U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_IPU1_MASK                                                        (0x00000010U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_IPU1_ENABLED                                                      (1U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_IPU1_DISABLED                                                     (0U)

#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_DSP2_SHIFT                                                       (5U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_DSP2_MASK                                                        (0x00000020U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_DSP2_ENABLED                                                      (1U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_DSP2_DISABLED                                                     (0U)

#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_EVE1_SHIFT                                                       (6U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_EVE1_MASK                                                        (0x00000040U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_EVE1_ENABLED                                                      (1U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_EVE1_DISABLED                                                     (0U)

#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_EVE2_SHIFT                                                       (7U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_EVE2_MASK                                                        (0x00000080U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_EVE2_ENABLED                                                      (1U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_EVE2_DISABLED                                                     (0U)

#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_EVE3_SHIFT                                                       (8U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_EVE3_MASK                                                        (0x00000100U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_EVE3_ENABLED                                                      (1U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_EVE3_DISABLED                                                     (0U)

#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_EVE4_SHIFT                                                       (9U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_EVE4_MASK                                                        (0x00000200U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_EVE4_ENABLED                                                      (1U)
#define PM_IPU_TIMER7_WKDEP_WKUPDEP_TIMER7_EVE4_DISABLED                                                     (0U)

#define PM_IPU_TIMER7_WKDEP_RESERVED_SHIFT                                                                  (10U)
#define PM_IPU_TIMER7_WKDEP_RESERVED_MASK                                                                   (0xfffffc00U)

#define RM_IPU_TIMER7_CONTEXT_RESERVED_SHIFT                                                                (1U)
#define RM_IPU_TIMER7_CONTEXT_RESERVED_MASK                                                                 (0xfffffffeU)

#define RM_IPU_TIMER7_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                         (0U)
#define RM_IPU_TIMER7_CONTEXT_LOSTCONTEXT_DFF_MASK                                                          (0x00000001U)
#define RM_IPU_TIMER7_CONTEXT_LOSTCONTEXT_DFF_LOST                                                           (1U)
#define RM_IPU_TIMER7_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                     (0U)

#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_MPU_SHIFT                                                        (0U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_MPU_MASK                                                         (0x00000001U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_MPU_ENABLED                                                       (1U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_MPU_DISABLED                                                      (0U)

#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_IPU2_SHIFT                                                       (1U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_IPU2_MASK                                                        (0x00000002U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_IPU2_ENABLED                                                      (1U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_IPU2_DISABLED                                                     (0U)

#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_DSP1_SHIFT                                                       (2U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_DSP1_MASK                                                        (0x00000004U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_DSP1_ENABLED                                                      (1U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_DSP1_DISABLED                                                     (0U)

#define PM_IPU_TIMER8_WKDEP_RESERVED1_SHIFT                                                                 (3U)
#define PM_IPU_TIMER8_WKDEP_RESERVED1_MASK                                                                  (0x00000008U)

#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_IPU1_SHIFT                                                       (4U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_IPU1_MASK                                                        (0x00000010U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_IPU1_ENABLED                                                      (1U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_IPU1_DISABLED                                                     (0U)

#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_DSP2_SHIFT                                                       (5U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_DSP2_MASK                                                        (0x00000020U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_DSP2_ENABLED                                                      (1U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_DSP2_DISABLED                                                     (0U)

#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_EVE1_SHIFT                                                       (6U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_EVE1_MASK                                                        (0x00000040U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_EVE1_ENABLED                                                      (1U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_EVE1_DISABLED                                                     (0U)

#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_EVE2_SHIFT                                                       (7U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_EVE2_MASK                                                        (0x00000080U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_EVE2_ENABLED                                                      (1U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_EVE2_DISABLED                                                     (0U)

#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_EVE3_SHIFT                                                       (8U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_EVE3_MASK                                                        (0x00000100U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_EVE3_ENABLED                                                      (1U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_EVE3_DISABLED                                                     (0U)

#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_EVE4_SHIFT                                                       (9U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_EVE4_MASK                                                        (0x00000200U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_EVE4_ENABLED                                                      (1U)
#define PM_IPU_TIMER8_WKDEP_WKUPDEP_TIMER8_EVE4_DISABLED                                                     (0U)

#define PM_IPU_TIMER8_WKDEP_RESERVED_SHIFT                                                                  (10U)
#define PM_IPU_TIMER8_WKDEP_RESERVED_MASK                                                                   (0xfffffc00U)

#define RM_IPU_TIMER8_CONTEXT_RESERVED_SHIFT                                                                (1U)
#define RM_IPU_TIMER8_CONTEXT_RESERVED_MASK                                                                 (0xfffffffeU)

#define RM_IPU_TIMER8_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                         (0U)
#define RM_IPU_TIMER8_CONTEXT_LOSTCONTEXT_DFF_MASK                                                          (0x00000001U)
#define RM_IPU_TIMER8_CONTEXT_LOSTCONTEXT_DFF_LOST                                                           (1U)
#define RM_IPU_TIMER8_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                     (0U)

#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_MPU_SHIFT                                                        (0U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_MPU_MASK                                                         (0x00000001U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_MPU_ENABLED                                                       (1U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_MPU_DISABLED                                                      (0U)

#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_DSP1_SHIFT                                                       (2U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_DSP1_MASK                                                        (0x00000004U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_DSP1_ENABLED                                                      (1U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_DSP1_DISABLED                                                     (0U)

#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_IPU2_SHIFT                                                       (1U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_IPU2_MASK                                                        (0x00000002U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_IPU2_ENABLED                                                      (1U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_IPU2_DISABLED                                                     (0U)

#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_IPU1_SHIFT                                                       (4U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_IPU1_MASK                                                        (0x00000010U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_IPU1_ENABLED                                                      (1U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_IPU1_DISABLED                                                     (0U)

#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_DSP2_SHIFT                                                       (5U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_DSP2_MASK                                                        (0x00000020U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_DSP2_ENABLED                                                      (1U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_DSP2_DISABLED                                                     (0U)

#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_EVE1_SHIFT                                                       (6U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_EVE1_MASK                                                        (0x00000040U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_EVE1_ENABLED                                                      (1U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_EVE1_DISABLED                                                     (0U)

#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_EVE2_SHIFT                                                       (7U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_EVE2_MASK                                                        (0x00000080U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_EVE2_ENABLED                                                      (1U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_EVE2_DISABLED                                                     (0U)

#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_EVE3_SHIFT                                                       (8U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_EVE3_MASK                                                        (0x00000100U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_EVE3_ENABLED                                                      (1U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_EVE3_DISABLED                                                     (0U)

#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_EVE4_SHIFT                                                       (9U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_EVE4_MASK                                                        (0x00000200U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_EVE4_ENABLED                                                      (1U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_IRQ_EVE4_DISABLED                                                     (0U)

#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_DMA_SDMA_SHIFT                                                       (13U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_DMA_SDMA_MASK                                                        (0x00002000U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_DMA_SDMA_ENABLED                                                      (1U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_DMA_SDMA_DISABLED                                                     (0U)

#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_DMA_DSP1_SHIFT                                                       (12U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_DMA_DSP1_MASK                                                        (0x00001000U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_DMA_DSP1_ENABLED                                                      (1U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_DMA_DSP1_DISABLED                                                     (0U)

#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_DMA_DSP2_SHIFT                                                       (15U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_DMA_DSP2_MASK                                                        (0x00008000U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_DMA_DSP2_ENABLED                                                      (1U)
#define PM_IPU_I2C5_WKDEP_WKUPDEP_I2C5_DMA_DSP2_DISABLED                                                     (0U)

#define PM_IPU_I2C5_WKDEP_RESERVED_SHIFT                                                                    (3U)
#define PM_IPU_I2C5_WKDEP_RESERVED_MASK                                                                     (0x00000008U)

#define PM_IPU_I2C5_WKDEP_RESERVED1_SHIFT                                                                   (10U)
#define PM_IPU_I2C5_WKDEP_RESERVED1_MASK                                                                    (0x00000c00U)

#define PM_IPU_I2C5_WKDEP_RESERVED2_SHIFT                                                                   (14U)
#define PM_IPU_I2C5_WKDEP_RESERVED2_MASK                                                                    (0x00004000U)

#define PM_IPU_I2C5_WKDEP_RESERVED3_SHIFT                                                                   (16U)
#define PM_IPU_I2C5_WKDEP_RESERVED3_MASK                                                                    (0xffff0000U)

#define RM_IPU_I2C5_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                           (0U)
#define RM_IPU_I2C5_CONTEXT_LOSTCONTEXT_DFF_MASK                                                            (0x00000001U)
#define RM_IPU_I2C5_CONTEXT_LOSTCONTEXT_DFF_LOST                                                             (1U)
#define RM_IPU_I2C5_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                       (0U)

#define RM_IPU_I2C5_CONTEXT_RESERVED_SHIFT                                                                  (1U)
#define RM_IPU_I2C5_CONTEXT_RESERVED_MASK                                                                   (0xfffffffeU)

#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_MPU_SHIFT                                                          (0U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_MPU_MASK                                                           (0x00000001U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_MPU_ENABLED                                                         (1U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_MPU_DISABLED                                                        (0U)

#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_DSP1_SHIFT                                                         (2U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_DSP1_MASK                                                          (0x00000004U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_DSP1_ENABLED                                                        (1U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_DSP1_DISABLED                                                       (0U)

#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_IPU2_SHIFT                                                         (1U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_IPU2_MASK                                                          (0x00000002U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_IPU2_ENABLED                                                        (1U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_IPU2_DISABLED                                                       (0U)

#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_SDMA_SHIFT                                                         (3U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_SDMA_MASK                                                          (0x00000008U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_SDMA_ENABLED                                                        (1U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_SDMA_DISABLED                                                       (0U)

#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_IPU1_SHIFT                                                         (4U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_IPU1_MASK                                                          (0x00000010U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_IPU1_ENABLED                                                        (1U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_IPU1_DISABLED                                                       (0U)

#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_DSP2_SHIFT                                                         (5U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_DSP2_MASK                                                          (0x00000020U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_DSP2_ENABLED                                                        (1U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_DSP2_DISABLED                                                       (0U)

#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_EVE1_SHIFT                                                         (6U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_EVE1_MASK                                                          (0x00000040U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_EVE1_ENABLED                                                        (1U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_EVE1_DISABLED                                                       (0U)

#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_EVE2_SHIFT                                                         (7U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_EVE2_MASK                                                          (0x00000080U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_EVE2_ENABLED                                                        (1U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_EVE2_DISABLED                                                       (0U)

#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_EVE3_SHIFT                                                         (8U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_EVE3_MASK                                                          (0x00000100U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_EVE3_ENABLED                                                        (1U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_EVE3_DISABLED                                                       (0U)

#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_EVE4_SHIFT                                                         (9U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_EVE4_MASK                                                          (0x00000200U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_EVE4_ENABLED                                                        (1U)
#define PM_IPU_UART6_WKDEP_WKUPDEP_UART6_EVE4_DISABLED                                                       (0U)

#define PM_IPU_UART6_WKDEP_RESERVED_SHIFT                                                                   (10U)
#define PM_IPU_UART6_WKDEP_RESERVED_MASK                                                                    (0xfffffc00U)

#define RM_IPU_UART6_CONTEXT_RESERVED1_SHIFT                                                                (0U)
#define RM_IPU_UART6_CONTEXT_RESERVED1_MASK                                                                 (0x00000001U)

#define RM_IPU_UART6_CONTEXT_RESERVED_SHIFT                                                                 (2U)
#define RM_IPU_UART6_CONTEXT_RESERVED_MASK                                                                  (0x000000fcU)

#define RM_IPU_UART6_CONTEXT_RESERVED2_SHIFT                                                                (9U)
#define RM_IPU_UART6_CONTEXT_RESERVED2_MASK                                                                 (0xfffffe00U)

#define RM_IPU_UART6_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                          (1U)
#define RM_IPU_UART6_CONTEXT_LOSTCONTEXT_RFF_MASK                                                           (0x00000002U)
#define RM_IPU_UART6_CONTEXT_LOSTCONTEXT_RFF_LOST                                                            (1U)
#define RM_IPU_UART6_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                      (0U)

#define RM_IPU_UART6_CONTEXT_LOSTMEM_RETAINED_BANK_SHIFT                                                    (8U)
#define RM_IPU_UART6_CONTEXT_LOSTMEM_RETAINED_BANK_MASK                                                     (0x00000100U)
#define RM_IPU_UART6_CONTEXT_LOSTMEM_RETAINED_BANK_LOST                                                      (1U)
#define RM_IPU_UART6_CONTEXT_LOSTMEM_RETAINED_BANK_MAINTAINED                                                (0U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_IPU_PRM_H_ */
