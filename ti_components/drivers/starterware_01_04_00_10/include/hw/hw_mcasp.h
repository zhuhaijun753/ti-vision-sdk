/******************************************************************************
*
* hw_mcasp.h - register-level header file for MCASP
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
#ifndef HW_MCASP_H_
#define HW_MCASP_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*
** McASP Register Offset for MCASP_XRSRCTL(x), MCASP_TXBUF(x), MCASP_RXBUF(x),  
   MCASP_DITCSRA(x), MCASP_DITCSRB(x), MCASP_DITUDRA(x), and MCASP_DITUDRB(x) register set. 
*/
#define MCASP_REG_OFFSET                                                                                    (0x4U)

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define MCASP_PID                                                                                           (0x0U)
#define MCASP_PWRIDLESYSCONFIG                                                                              (0x4U)
#define MCASP_PFUNC                                                                                         (0x10U)
#define MCASP_PDIR                                                                                          (0x14U)
#define MCASP_PDOUT                                                                                         (0x18U)
#define MCASP_PDIN                                                                                          (0x1cU)
#define MCASP_PDSET                                                                                         (0x1cU)
#define MCASP_PDCLR                                                                                         (0x20U)
#define MCASP_GBLCTL                                                                                        (0x44U)
#define MCASP_AMUTE                                                                                         (0x48U)
#define MCASP_LBCTL                                                                                         (0x4cU)
#define MCASP_TXDITCTL                                                                                      (0x50U)
#define MCASP_GBLCTLR                                                                                       (0x60U)
#define MCASP_RXMASK                                                                                        (0x64U)
#define MCASP_RXFMT                                                                                         (0x68U)
#define MCASP_RXFMCTL                                                                                       (0x6cU)
#define MCASP_ACLKRCTL                                                                                      (0x70U)
#define MCASP_AHCLKRCTL                                                                                     (0x74U)
#define MCASP_RXTDM                                                                                         (0x78U)
#define MCASP_EVTCTLR                                                                                       (0x7cU)
#define MCASP_RXSTAT                                                                                        (0x80U)
#define MCASP_RXTDMSLOT                                                                                     (0x84U)
#define MCASP_RXCLKCHK                                                                                      (0x88U)
#define MCASP_REVTCTL                                                                                       (0x8cU)
#define MCASP_GBLCTLX                                                                                       (0xa0U)
#define MCASP_TXMASK                                                                                        (0xa4U)
#define MCASP_TXFMT                                                                                         (0xa8U)
#define MCASP_TXFMCTL                                                                                       (0xacU)
#define MCASP_ACLKXCTL                                                                                      (0xb0U)
#define MCASP_AHCLKXCTL                                                                                     (0xb4U)
#define MCASP_TXTDM                                                                                         (0xb8U)
#define MCASP_EVTCTLX                                                                                       (0xbcU)
#define MCASP_TXSTAT                                                                                        (0xc0U)
#define MCASP_TXTDMSLOT                                                                                     (0xc4U)
#define MCASP_TXCLKCHK                                                                                      (0xc8U)
#define MCASP_XEVTCTL                                                                                       (0xccU)
#define MCASP_CLKADJEN                                                                                      (0xd0U)
#define MCASP_DITCSRA0                                                                                      (0x100U)
#define MCASP_DITCSRA1                                                                                      (0x104U)
#define MCASP_DITCSRA2                                                                                      (0x108U)
#define MCASP_DITCSRA3                                                                                      (0x10cU)
#define MCASP_DITCSRA4                                                                                      (0x110U)
#define MCASP_DITCSRA5                                                                                      (0x114U)
#define MCASP_DITCSRB0                                                                                      (0x118U)
#define MCASP_DITCSRB1                                                                                      (0x11cU)
#define MCASP_DITCSRB2                                                                                      (0x120U)
#define MCASP_DITCSRB3                                                                                      (0x124U)
#define MCASP_DITCSRB4                                                                                      (0x128U)
#define MCASP_DITCSRB5                                                                                      (0x12cU)
#define MCASP_DITUDRA0                                                                                      (0x130U)
#define MCASP_DITUDRA1                                                                                      (0x134U)
#define MCASP_DITUDRA2                                                                                      (0x138U)
#define MCASP_DITUDRA3                                                                                      (0x13cU)
#define MCASP_DITUDRA4                                                                                      (0x140U)
#define MCASP_DITUDRA5                                                                                      (0x144U)
#define MCASP_DITUDRB0                                                                                      (0x148U)
#define MCASP_DITUDRB1                                                                                      (0x14cU)
#define MCASP_DITUDRB2                                                                                      (0x150U)
#define MCASP_DITUDRB3                                                                                      (0x154U)
#define MCASP_DITUDRB4                                                                                      (0x158U)
#define MCASP_DITUDRB5                                                                                      (0x15cU)
#define MCASP_XRSRCTL0                                                                                      (0x180U)
#define MCASP_XRSRCTL1                                                                                      (0x184U)
#define MCASP_XRSRCTL2                                                                                      (0x188U)
#define MCASP_XRSRCTL3                                                                                      (0x18cU)
#define MCASP_XRSRCTL4                                                                                      (0x190U)
#define MCASP_XRSRCTL5                                                                                      (0x194U)
#define MCASP_XRSRCTL6                                                                                      (0x198U)
#define MCASP_XRSRCTL7                                                                                      (0x19cU)
#define MCASP_XRSRCTL8                                                                                      (0x1a0U)
#define MCASP_XRSRCTL9                                                                                      (0x1a4U)
#define MCASP_XRSRCTL10                                                                                     (0x1a8U)
#define MCASP_XRSRCTL11                                                                                     (0x1acU)
#define MCASP_XRSRCTL12                                                                                     (0x1b0U)
#define MCASP_XRSRCTL13                                                                                     (0x1b4U)
#define MCASP_XRSRCTL14                                                                                     (0x1b8U)
#define MCASP_XRSRCTL15                                                                                     (0x1bcU)
#define MCASP_TXBUF0                                                                                        (0x200U)
#define MCASP_TXBUF1                                                                                        (0x204U)
#define MCASP_TXBUF2                                                                                        (0x208U)
#define MCASP_TXBUF3                                                                                        (0x20cU)
#define MCASP_TXBUF4                                                                                        (0x210U)
#define MCASP_TXBUF5                                                                                        (0x214U)
#define MCASP_TXBUF6                                                                                        (0x218U)
#define MCASP_TXBUF7                                                                                        (0x21cU)
#define MCASP_TXBUF8                                                                                        (0x220U)
#define MCASP_TXBUF9                                                                                        (0x224U)
#define MCASP_TXBUF10                                                                                       (0x228U)
#define MCASP_TXBUF11                                                                                       (0x22cU)
#define MCASP_TXBUF12                                                                                       (0x230U)
#define MCASP_TXBUF13                                                                                       (0x234U)
#define MCASP_TXBUF14                                                                                       (0x238U)
#define MCASP_TXBUF15                                                                                       (0x23cU)
#define MCASP_RXBUF0                                                                                        (0x280U)
#define MCASP_RXBUF1                                                                                        (0x284U)
#define MCASP_RXBUF2                                                                                        (0x288U)
#define MCASP_RXBUF3                                                                                        (0x28cU)
#define MCASP_RXBUF4                                                                                        (0x290U)
#define MCASP_RXBUF5                                                                                        (0x294U)
#define MCASP_RXBUF6                                                                                        (0x298U)
#define MCASP_RXBUF7                                                                                        (0x29cU)
#define MCASP_RXBUF8                                                                                        (0x2a0U)
#define MCASP_RXBUF9                                                                                        (0x2a4U)
#define MCASP_RXBUF10                                                                                       (0x2a8U)
#define MCASP_RXBUF11                                                                                       (0x2acU)
#define MCASP_RXBUF12                                                                                       (0x2b0U)
#define MCASP_RXBUF13                                                                                       (0x2b4U)
#define MCASP_RXBUF14                                                                                       (0x2b8U)
#define MCASP_RXBUF15                                                                                       (0x2bcU)
#define MCASP_WFIFOCTL                                                                                      (0x1000U)
#define MCASP_RFIFOCTL                                                                                      (0x1008U)
#define MCASP_WFIFOSTS                                                                                      (0x1004U)
#define MCASP_RFIFOSTS                                                                                      (0x100cU)

/*
** Base address of MCASP_XRSRCTL(x)
*/
#define MCASP_SRCTL(x)                           ((uint32_t) MCASP_XRSRCTL0 + \
                                                  (MCASP_REG_OFFSET * (x)))
/*
** Base address of MCASP_TXBUF(x)
*/
#define MCASP_TXBUF(x)                           ((uint32_t) MCASP_TXBUF0 + \
                                                  (MCASP_REG_OFFSET * (x)))
/*
** Base address of MCASP_RXBUF(x)
*/
#define MCASP_RXBUF(x)                           ((uint32_t) MCASP_RXBUF0 + \
                                                  (MCASP_REG_OFFSET * (x)))
/*
** Base address of MCASP_DITCSRA(x)
*/
#define MCASP_DITCSRA(x)                         ((uint32_t) MCASP_DITCSRA0 + \
                                                  (MCASP_REG_OFFSET * (x)))
/*
** Base address of MCASP_DITCSRB(x)
*/
#define MCASP_DITCSRB(x)                         ((uint32_t) MCASP_DITCSRB0 + \
                                                  (MCASP_REG_OFFSET * (x)))
/*
** Base address of MCASP_DITUDRA(x)
*/
#define MCASP_DITUDRA(x)                         ((uint32_t) MCASP_DITUDRA0 + \
                                                  (MCASP_REG_OFFSET * (x)))
/*
** Base address of MCASP_DITUDRB(x)
*/
#define MCASP_DITUDRB(x)                         ((uint32_t) MCASP_DITUDRB0 + \
                                                  (MCASP_REG_OFFSET * (x)))
/*****************************************************************************/

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define MCASP_PID_REVISION_SHIFT                                                                            (0U)
#define MCASP_PID_REVISION_MASK                                                                             (0xffffffffU)

#define MCASP_PWRIDLESYSCONFIG_IDLE_MODE_SHIFT                                                              (0U)
#define MCASP_PWRIDLESYSCONFIG_IDLE_MODE_MASK                                                               (0x00000003U)

#define MCASP_PWRIDLESYSCONFIG_OTHER_SHIFT                                                                  (2U)
#define MCASP_PWRIDLESYSCONFIG_OTHER_MASK                                                                   (0x0000003cU)

#define MCASP_PWRIDLESYSCONFIG_RSV_SHIFT                                                                    (6U)
#define MCASP_PWRIDLESYSCONFIG_RSV_MASK                                                                     (0xffffffc0U)

#define MCASP_PFUNC_AFSR_SHIFT                                                                              (31U)
#define MCASP_PFUNC_AFSR_MASK                                                                               (0x80000000U)
#define MCASP_PFUNC_AFSR_MCASP                                                                               (0U)
#define MCASP_PFUNC_AFSR_GPIO                                                                                (1U)

#define MCASP_PFUNC_ACLKR_SHIFT                                                                             (29U)
#define MCASP_PFUNC_ACLKR_MASK                                                                              (0x20000000U)
#define MCASP_PFUNC_ACLKR_MCASP                                                                              (0U)
#define MCASP_PFUNC_ACLKR_GPIO                                                                               (1U)

#define MCASP_PFUNC_AFSX_SHIFT                                                                              (28U)
#define MCASP_PFUNC_AFSX_MASK                                                                               (0x10000000U)
#define MCASP_PFUNC_AFSX_MCASP                                                                               (0U)
#define MCASP_PFUNC_AFSX_GPIO                                                                                (1U)

#define MCASP_PFUNC_AHCLKX_SHIFT                                                                            (27U)
#define MCASP_PFUNC_AHCLKX_MASK                                                                             (0x08000000U)
#define MCASP_PFUNC_AHCLKX_MCASP                                                                             (0U)
#define MCASP_PFUNC_AHCLKX_GPIO                                                                              (1U)

#define MCASP_PFUNC_ACLKX_SHIFT                                                                             (26U)
#define MCASP_PFUNC_ACLKX_MASK                                                                              (0x04000000U)
#define MCASP_PFUNC_ACLKX_MCASP                                                                              (0U)
#define MCASP_PFUNC_ACLKX_GPIO                                                                               (1U)

#define MCASP_PFUNC_AMUTE_SHIFT                                                                             (25U)
#define MCASP_PFUNC_AMUTE_MASK                                                                              (0x02000000U)
#define MCASP_PFUNC_AMUTE_MCASP                                                                              (0U)
#define MCASP_PFUNC_AMUTE_GPIO                                                                               (1U)

#define MCASP_PFUNC_RESV1_SHIFT                                                                             (16U)
#define MCASP_PFUNC_RESV1_MASK                                                                              (0x01ff0000U)

#define MCASP_PFUNC_AXR15_SHIFT                                                                             (15U)
#define MCASP_PFUNC_AXR15_MASK                                                                              (0x00008000U)
#define MCASP_PFUNC_AXR15_MCASP                                                                              (0U)
#define MCASP_PFUNC_AXR15_GPIO                                                                               (1U)

#define MCASP_PFUNC_AXR14_SHIFT                                                                             (14U)
#define MCASP_PFUNC_AXR14_MASK                                                                              (0x00004000U)
#define MCASP_PFUNC_AXR14_MCASP                                                                              (0U)
#define MCASP_PFUNC_AXR14_GPIO                                                                               (1U)

#define MCASP_PFUNC_AXR13_SHIFT                                                                             (13U)
#define MCASP_PFUNC_AXR13_MASK                                                                              (0x00002000U)
#define MCASP_PFUNC_AXR13_MCASP                                                                              (0U)
#define MCASP_PFUNC_AXR13_GPIO                                                                               (1U)

#define MCASP_PFUNC_AXR12_SHIFT                                                                             (12U)
#define MCASP_PFUNC_AXR12_MASK                                                                              (0x00001000U)
#define MCASP_PFUNC_AXR12_MCASP                                                                              (0U)
#define MCASP_PFUNC_AXR12_GPIO                                                                               (1U)

#define MCASP_PFUNC_AXR11_SHIFT                                                                             (11U)
#define MCASP_PFUNC_AXR11_MASK                                                                              (0x00000800U)
#define MCASP_PFUNC_AXR11_MCASP                                                                              (0U)
#define MCASP_PFUNC_AXR11_GPIO                                                                               (1U)

#define MCASP_PFUNC_AXR10_SHIFT                                                                             (10U)
#define MCASP_PFUNC_AXR10_MASK                                                                              (0x00000400U)
#define MCASP_PFUNC_AXR10_MCASP                                                                              (0U)
#define MCASP_PFUNC_AXR10_GPIO                                                                               (1U)

#define MCASP_PFUNC_AXR9_SHIFT                                                                              (9U)
#define MCASP_PFUNC_AXR9_MASK                                                                               (0x00000200U)
#define MCASP_PFUNC_AXR9_MCASP                                                                               (0U)
#define MCASP_PFUNC_AXR9_GPIO                                                                                (1U)

#define MCASP_PFUNC_AXR8_SHIFT                                                                              (8U)
#define MCASP_PFUNC_AXR8_MASK                                                                               (0x00000100U)
#define MCASP_PFUNC_AXR8_MCASP                                                                               (0U)
#define MCASP_PFUNC_AXR8_GPIO                                                                                (1U)

#define MCASP_PFUNC_AXR7_SHIFT                                                                              (7U)
#define MCASP_PFUNC_AXR7_MASK                                                                               (0x00000080U)
#define MCASP_PFUNC_AXR7_MCASP                                                                               (0U)
#define MCASP_PFUNC_AXR7_GPIO                                                                                (1U)

#define MCASP_PFUNC_AXR6_SHIFT                                                                              (6U)
#define MCASP_PFUNC_AXR6_MASK                                                                               (0x00000040U)
#define MCASP_PFUNC_AXR6_MCASP                                                                               (0U)
#define MCASP_PFUNC_AXR6_GPIO                                                                                (1U)

#define MCASP_PFUNC_AXR5_SHIFT                                                                              (5U)
#define MCASP_PFUNC_AXR5_MASK                                                                               (0x00000020U)
#define MCASP_PFUNC_AXR5_MCASP                                                                               (0U)
#define MCASP_PFUNC_AXR5_GPIO                                                                                (1U)

#define MCASP_PFUNC_AXR4_SHIFT                                                                              (4U)
#define MCASP_PFUNC_AXR4_MASK                                                                               (0x00000010U)
#define MCASP_PFUNC_AXR4_MCASP                                                                               (0U)
#define MCASP_PFUNC_AXR4_GPIO                                                                                (1U)

#define MCASP_PFUNC_AXR3_SHIFT                                                                              (3U)
#define MCASP_PFUNC_AXR3_MASK                                                                               (0x00000008U)
#define MCASP_PFUNC_AXR3_MCASP                                                                               (0U)
#define MCASP_PFUNC_AXR3_GPIO                                                                                (1U)

#define MCASP_PFUNC_AXR2_SHIFT                                                                              (2U)
#define MCASP_PFUNC_AXR2_MASK                                                                               (0x00000004U)
#define MCASP_PFUNC_AXR2_MCASP                                                                               (0U)
#define MCASP_PFUNC_AXR2_GPIO                                                                                (1U)

#define MCASP_PFUNC_AXR1_SHIFT                                                                              (1U)
#define MCASP_PFUNC_AXR1_MASK                                                                               (0x00000002U)
#define MCASP_PFUNC_AXR1_MCASP                                                                               (0U)
#define MCASP_PFUNC_AXR1_GPIO                                                                                (1U)

#define MCASP_PFUNC_AXR0_SHIFT                                                                              (0U)
#define MCASP_PFUNC_AXR0_MASK                                                                               (0x00000001U)
#define MCASP_PFUNC_AXR0_MCASP                                                                               (0U)
#define MCASP_PFUNC_AXR0_GPIO                                                                                (1U)

#define MCASP_PFUNC_RESV2_SHIFT                                                                             (30U)
#define MCASP_PFUNC_RESV2_MASK                                                                              (0x40000000U)
#define MCASP_PFUNC_RESV2_MCASP                                                                              (0U)
#define MCASP_PFUNC_RESV2_GPIO                                                                               (1U)

#define MCASP_PDIR_AFSR_SHIFT                                                                               (31U)
#define MCASP_PDIR_AFSR_MASK                                                                                (0x80000000U)
#define MCASP_PDIR_AFSR_INPUT                                                                                (0U)
#define MCASP_PDIR_AFSR_OUTPUT                                                                               (1U)

#define MCASP_PDIR_ACLKR_SHIFT                                                                              (29U)
#define MCASP_PDIR_ACLKR_MASK                                                                               (0x20000000U)
#define MCASP_PDIR_ACLKR_INPUT                                                                               (0U)
#define MCASP_PDIR_ACLKR_OUTPUT                                                                              (1U)

#define MCASP_PDIR_AFSX_SHIFT                                                                               (28U)
#define MCASP_PDIR_AFSX_MASK                                                                                (0x10000000U)
#define MCASP_PDIR_AFSX_INPUT                                                                                (0U)
#define MCASP_PDIR_AFSX_OUTPUT                                                                               (1U)

#define MCASP_PDIR_AHCLKX_SHIFT                                                                             (27U)
#define MCASP_PDIR_AHCLKX_MASK                                                                              (0x08000000U)
#define MCASP_PDIR_AHCLKX_INPUT                                                                              (0U)
#define MCASP_PDIR_AHCLKX_OUTPUT                                                                             (1U)

#define MCASP_PDIR_ACLKX_SHIFT                                                                              (26U)
#define MCASP_PDIR_ACLKX_MASK                                                                               (0x04000000U)
#define MCASP_PDIR_ACLKX_INPUT                                                                               (0U)
#define MCASP_PDIR_ACLKX_OUTPUT                                                                              (1U)

#define MCASP_PDIR_AMUTE_SHIFT                                                                              (25U)
#define MCASP_PDIR_AMUTE_MASK                                                                               (0x02000000U)
#define MCASP_PDIR_AMUTE_INPUT                                                                               (0U)
#define MCASP_PDIR_AMUTE_OUTPUT                                                                              (1U)

#define MCASP_PDIR_RESV_SHIFT                                                                               (16U)
#define MCASP_PDIR_RESV_MASK                                                                                (0x01ff0000U)

#define MCASP_PDIR_AXR15_SHIFT                                                                              (15U)
#define MCASP_PDIR_AXR15_MASK                                                                               (0x00008000U)
#define MCASP_PDIR_AXR15_INPUT                                                                               (0U)
#define MCASP_PDIR_AXR15_OUTPUT                                                                              (1U)

#define MCASP_PDIR_AXR14_SHIFT                                                                              (14U)
#define MCASP_PDIR_AXR14_MASK                                                                               (0x00004000U)
#define MCASP_PDIR_AXR14_INPUT                                                                               (0U)
#define MCASP_PDIR_AXR14_OUTPUT                                                                              (1U)

#define MCASP_PDIR_AXR13_SHIFT                                                                              (13U)
#define MCASP_PDIR_AXR13_MASK                                                                               (0x00002000U)
#define MCASP_PDIR_AXR13_INPUT                                                                               (0U)
#define MCASP_PDIR_AXR13_OUTPUT                                                                              (1U)

#define MCASP_PDIR_AXR12_SHIFT                                                                              (12U)
#define MCASP_PDIR_AXR12_MASK                                                                               (0x00001000U)
#define MCASP_PDIR_AXR12_INPUT                                                                               (0U)
#define MCASP_PDIR_AXR12_OUTPUT                                                                              (1U)

#define MCASP_PDIR_AXR11_SHIFT                                                                              (11U)
#define MCASP_PDIR_AXR11_MASK                                                                               (0x00000800U)
#define MCASP_PDIR_AXR11_INPUT                                                                               (0U)
#define MCASP_PDIR_AXR11_OUTPUT                                                                              (1U)

#define MCASP_PDIR_AXR10_SHIFT                                                                              (10U)
#define MCASP_PDIR_AXR10_MASK                                                                               (0x00000400U)
#define MCASP_PDIR_AXR10_INPUT                                                                               (0U)
#define MCASP_PDIR_AXR10_OUTPUT                                                                              (1U)

#define MCASP_PDIR_AXR9_SHIFT                                                                               (9U)
#define MCASP_PDIR_AXR9_MASK                                                                                (0x00000200U)
#define MCASP_PDIR_AXR9_INPUT                                                                                (0U)
#define MCASP_PDIR_AXR9_OUTPUT                                                                               (1U)

#define MCASP_PDIR_AXR8_SHIFT                                                                               (8U)
#define MCASP_PDIR_AXR8_MASK                                                                                (0x00000100U)
#define MCASP_PDIR_AXR8_INPUT                                                                                (0U)
#define MCASP_PDIR_AXR8_OUTPUT                                                                               (1U)

#define MCASP_PDIR_AXR7_SHIFT                                                                               (7U)
#define MCASP_PDIR_AXR7_MASK                                                                                (0x00000080U)
#define MCASP_PDIR_AXR7_INPUT                                                                                (0U)
#define MCASP_PDIR_AXR7_OUTPUT                                                                               (1U)

#define MCASP_PDIR_AXR6_SHIFT                                                                               (6U)
#define MCASP_PDIR_AXR6_MASK                                                                                (0x00000040U)
#define MCASP_PDIR_AXR6_INPUT                                                                                (0U)
#define MCASP_PDIR_AXR6_OUTPUT                                                                               (1U)

#define MCASP_PDIR_AXR5_SHIFT                                                                               (5U)
#define MCASP_PDIR_AXR5_MASK                                                                                (0x00000020U)
#define MCASP_PDIR_AXR5_INPUT                                                                                (0U)
#define MCASP_PDIR_AXR5_OUTPUT                                                                               (1U)

#define MCASP_PDIR_AXR4_SHIFT                                                                               (4U)
#define MCASP_PDIR_AXR4_MASK                                                                                (0x00000010U)
#define MCASP_PDIR_AXR4_INPUT                                                                                (0U)
#define MCASP_PDIR_AXR4_OUTPUT                                                                               (1U)

#define MCASP_PDIR_AXR3_SHIFT                                                                               (3U)
#define MCASP_PDIR_AXR3_MASK                                                                                (0x00000008U)
#define MCASP_PDIR_AXR3_INPUT                                                                                (0U)
#define MCASP_PDIR_AXR3_OUTPUT                                                                               (1U)

#define MCASP_PDIR_AXR2_SHIFT                                                                               (2U)
#define MCASP_PDIR_AXR2_MASK                                                                                (0x00000004U)
#define MCASP_PDIR_AXR2_INPUT                                                                                (0U)
#define MCASP_PDIR_AXR2_OUTPUT                                                                               (1U)

#define MCASP_PDIR_AXR1_SHIFT                                                                               (1U)
#define MCASP_PDIR_AXR1_MASK                                                                                (0x00000002U)
#define MCASP_PDIR_AXR1_INPUT                                                                                (0U)
#define MCASP_PDIR_AXR1_OUTPUT                                                                               (1U)

#define MCASP_PDIR_AXR0_SHIFT                                                                               (0U)
#define MCASP_PDIR_AXR0_MASK                                                                                (0x00000001U)
#define MCASP_PDIR_AXR0_INPUT                                                                                (0U)
#define MCASP_PDIR_AXR0_OUTPUT                                                                               (1U)

#define MCASP_PDIR_RESV1_SHIFT                                                                              (30U)
#define MCASP_PDIR_RESV1_MASK                                                                               (0x40000000U)
#define MCASP_PDIR_RESV1_INPUT                                                                               (0U)
#define MCASP_PDIR_RESV1_OUTPUT                                                                              (1U)

#define MCASP_PDOUT_AFSR_SHIFT                                                                              (31U)
#define MCASP_PDOUT_AFSR_MASK                                                                               (0x80000000U)
#define MCASP_PDOUT_AFSR_DRV0                                                                                (0U)
#define MCASP_PDOUT_AFSR_DRV1                                                                                (1U)

#define MCASP_PDOUT_AHCLKR_SHIFT                                                                            (30U)
#define MCASP_PDOUT_AHCLKR_MASK                                                                             (0x40000000U)
#define MCASP_PDOUT_AHCLKR_DRV0                                                                              (0U)
#define MCASP_PDOUT_AHCLKR_DRV1                                                                              (1U)

#define MCASP_PDOUT_ACLKR_SHIFT                                                                             (29U)
#define MCASP_PDOUT_ACLKR_MASK                                                                              (0x20000000U)
#define MCASP_PDOUT_ACLKR_DRV0                                                                               (0U)
#define MCASP_PDOUT_ACLKR_DRV1                                                                               (1U)

#define MCASP_PDOUT_AFSX_SHIFT                                                                              (28U)
#define MCASP_PDOUT_AFSX_MASK                                                                               (0x10000000U)
#define MCASP_PDOUT_AFSX_DRV0                                                                                (0U)
#define MCASP_PDOUT_AFSX_DRV1                                                                                (1U)

#define MCASP_PDOUT_AHCLKX_SHIFT                                                                            (27U)
#define MCASP_PDOUT_AHCLKX_MASK                                                                             (0x08000000U)
#define MCASP_PDOUT_AHCLKX_DRV0                                                                              (0U)
#define MCASP_PDOUT_AHCLKX_DRV1                                                                              (1U)

#define MCASP_PDOUT_ACLKX_SHIFT                                                                             (26U)
#define MCASP_PDOUT_ACLKX_MASK                                                                              (0x04000000U)
#define MCASP_PDOUT_ACLKX_DRV0                                                                               (0U)
#define MCASP_PDOUT_ACLKX_DRV1                                                                               (1U)

#define MCASP_PDOUT_AMUTE_SHIFT                                                                             (25U)
#define MCASP_PDOUT_AMUTE_MASK                                                                              (0x02000000U)
#define MCASP_PDOUT_AMUTE_DRV0                                                                               (0U)
#define MCASP_PDOUT_AMUTE_DRV1                                                                               (1U)

#define MCASP_PDOUT_RESV_SHIFT                                                                              (16U)
#define MCASP_PDOUT_RESV_MASK                                                                               (0x01ff0000U)

#define MCASP_PDOUT_AXR15_SHIFT                                                                             (15U)
#define MCASP_PDOUT_AXR15_MASK                                                                              (0x00008000U)
#define MCASP_PDOUT_AXR15_DRV0                                                                               (0U)
#define MCASP_PDOUT_AXR15_DRV1                                                                               (1U)

#define MCASP_PDOUT_AXR14_SHIFT                                                                             (14U)
#define MCASP_PDOUT_AXR14_MASK                                                                              (0x00004000U)
#define MCASP_PDOUT_AXR14_DRV0                                                                               (0U)
#define MCASP_PDOUT_AXR14_DRV1                                                                               (1U)

#define MCASP_PDOUT_AXR13_SHIFT                                                                             (13U)
#define MCASP_PDOUT_AXR13_MASK                                                                              (0x00002000U)
#define MCASP_PDOUT_AXR13_DRV0                                                                               (0U)
#define MCASP_PDOUT_AXR13_DRV1                                                                               (1U)

#define MCASP_PDOUT_AXR12_SHIFT                                                                             (12U)
#define MCASP_PDOUT_AXR12_MASK                                                                              (0x00001000U)
#define MCASP_PDOUT_AXR12_DRV0                                                                               (0U)
#define MCASP_PDOUT_AXR12_DRV1                                                                               (1U)

#define MCASP_PDOUT_AXR11_SHIFT                                                                             (11U)
#define MCASP_PDOUT_AXR11_MASK                                                                              (0x00000800U)
#define MCASP_PDOUT_AXR11_DRV0                                                                               (0U)
#define MCASP_PDOUT_AXR11_DRV1                                                                               (1U)

#define MCASP_PDOUT_AXR10_SHIFT                                                                             (10U)
#define MCASP_PDOUT_AXR10_MASK                                                                              (0x00000400U)
#define MCASP_PDOUT_AXR10_DRV0                                                                               (0U)
#define MCASP_PDOUT_AXR10_DRV1                                                                               (1U)

#define MCASP_PDOUT_AXR9_SHIFT                                                                              (9U)
#define MCASP_PDOUT_AXR9_MASK                                                                               (0x00000200U)
#define MCASP_PDOUT_AXR9_DRV0                                                                                (0U)
#define MCASP_PDOUT_AXR9_DRV1                                                                                (1U)

#define MCASP_PDOUT_AXR8_SHIFT                                                                              (8U)
#define MCASP_PDOUT_AXR8_MASK                                                                               (0x00000100U)
#define MCASP_PDOUT_AXR8_DRV0                                                                                (0U)
#define MCASP_PDOUT_AXR8_DRV1                                                                                (1U)

#define MCASP_PDOUT_AXR7_SHIFT                                                                              (7U)
#define MCASP_PDOUT_AXR7_MASK                                                                               (0x00000080U)
#define MCASP_PDOUT_AXR7_DRV0                                                                                (0U)
#define MCASP_PDOUT_AXR7_DRV1                                                                                (1U)

#define MCASP_PDOUT_AXR6_SHIFT                                                                              (6U)
#define MCASP_PDOUT_AXR6_MASK                                                                               (0x00000040U)
#define MCASP_PDOUT_AXR6_DRV0                                                                                (0U)
#define MCASP_PDOUT_AXR6_DRV1                                                                                (1U)

#define MCASP_PDOUT_AXR5_SHIFT                                                                              (5U)
#define MCASP_PDOUT_AXR5_MASK                                                                               (0x00000020U)
#define MCASP_PDOUT_AXR5_DRV0                                                                                (0U)
#define MCASP_PDOUT_AXR5_DRV1                                                                                (1U)

#define MCASP_PDOUT_AXR4_SHIFT                                                                              (4U)
#define MCASP_PDOUT_AXR4_MASK                                                                               (0x00000010U)
#define MCASP_PDOUT_AXR4_DRV0                                                                                (0U)
#define MCASP_PDOUT_AXR4_DRV1                                                                                (1U)

#define MCASP_PDOUT_AXR3_SHIFT                                                                              (3U)
#define MCASP_PDOUT_AXR3_MASK                                                                               (0x00000008U)
#define MCASP_PDOUT_AXR3_DRV0                                                                                (0U)
#define MCASP_PDOUT_AXR3_DRV1                                                                                (1U)

#define MCASP_PDOUT_AXR2_SHIFT                                                                              (2U)
#define MCASP_PDOUT_AXR2_MASK                                                                               (0x00000004U)
#define MCASP_PDOUT_AXR2_DRV0                                                                                (0U)
#define MCASP_PDOUT_AXR2_DRV1                                                                                (1U)

#define MCASP_PDOUT_AXR1_SHIFT                                                                              (1U)
#define MCASP_PDOUT_AXR1_MASK                                                                               (0x00000002U)
#define MCASP_PDOUT_AXR1_DRV0                                                                                (0U)
#define MCASP_PDOUT_AXR1_DRV1                                                                                (1U)

#define MCASP_PDOUT_AXR0_SHIFT                                                                              (0U)
#define MCASP_PDOUT_AXR0_MASK                                                                               (0x00000001U)
#define MCASP_PDOUT_AXR0_DRV0                                                                                (0U)
#define MCASP_PDOUT_AXR0_DRV1                                                                                (1U)

#define MCASP_PDIN_AFSR_SHIFT                                                                               (31U)
#define MCASP_PDIN_AFSR_MASK                                                                                (0x80000000U)
#define MCASP_PDIN_AFSR_LOW                                                                                  (0U)
#define MCASP_PDIN_AFSR_HIGH                                                                                 (1U)

#define MCASP_PDIN_ACLKR_SHIFT                                                                              (29U)
#define MCASP_PDIN_ACLKR_MASK                                                                               (0x20000000U)
#define MCASP_PDIN_ACLKR_LOW                                                                                 (0U)
#define MCASP_PDIN_ACLKR_HIGH                                                                                (1U)

#define MCASP_PDIN_AFSX_SHIFT                                                                               (28U)
#define MCASP_PDIN_AFSX_MASK                                                                                (0x10000000U)
#define MCASP_PDIN_AFSX_LOW                                                                                  (0U)
#define MCASP_PDIN_AFSX_HIGH                                                                                 (1U)

#define MCASP_PDIN_AHCLKX_SHIFT                                                                             (27U)
#define MCASP_PDIN_AHCLKX_MASK                                                                              (0x08000000U)
#define MCASP_PDIN_AHCLKX_LOW                                                                                (0U)
#define MCASP_PDIN_AHCLKX_HIGH                                                                               (1U)

#define MCASP_PDIN_ACLKX_SHIFT                                                                              (26U)
#define MCASP_PDIN_ACLKX_MASK                                                                               (0x04000000U)
#define MCASP_PDIN_ACLKX_LOW                                                                                 (0U)
#define MCASP_PDIN_ACLKX_HIGH                                                                                (1U)

#define MCASP_PDIN_AMUTE_SHIFT                                                                              (25U)
#define MCASP_PDIN_AMUTE_MASK                                                                               (0x02000000U)
#define MCASP_PDIN_AMUTE_LOW                                                                                 (0U)
#define MCASP_PDIN_AMUTE_HIGH                                                                                (1U)

#define MCASP_PDIN_RESV_SHIFT                                                                               (16U)
#define MCASP_PDIN_RESV_MASK                                                                                (0x01ff0000U)

#define MCASP_PDIN_AXR15_SHIFT                                                                              (15U)
#define MCASP_PDIN_AXR15_MASK                                                                               (0x00008000U)
#define MCASP_PDIN_AXR15_LOW                                                                                 (0U)
#define MCASP_PDIN_AXR15_HIGH                                                                                (1U)

#define MCASP_PDIN_AXR14_SHIFT                                                                              (14U)
#define MCASP_PDIN_AXR14_MASK                                                                               (0x00004000U)
#define MCASP_PDIN_AXR14_LOW                                                                                 (0U)
#define MCASP_PDIN_AXR14_HIGH                                                                                (1U)

#define MCASP_PDIN_AXR13_SHIFT                                                                              (13U)
#define MCASP_PDIN_AXR13_MASK                                                                               (0x00002000U)
#define MCASP_PDIN_AXR13_LOW                                                                                 (0U)
#define MCASP_PDIN_AXR13_HIGH                                                                                (1U)

#define MCASP_PDIN_AXR12_SHIFT                                                                              (12U)
#define MCASP_PDIN_AXR12_MASK                                                                               (0x00001000U)
#define MCASP_PDIN_AXR12_LOW                                                                                 (0U)
#define MCASP_PDIN_AXR12_HIGH                                                                                (1U)

#define MCASP_PDIN_AXR11_SHIFT                                                                              (11U)
#define MCASP_PDIN_AXR11_MASK                                                                               (0x00000800U)
#define MCASP_PDIN_AXR11_LOW                                                                                 (0U)
#define MCASP_PDIN_AXR11_HIGH                                                                                (1U)

#define MCASP_PDIN_AXR10_SHIFT                                                                              (10U)
#define MCASP_PDIN_AXR10_MASK                                                                               (0x00000400U)
#define MCASP_PDIN_AXR10_LOW                                                                                 (0U)
#define MCASP_PDIN_AXR10_HIGH                                                                                (1U)

#define MCASP_PDIN_AXR9_SHIFT                                                                               (9U)
#define MCASP_PDIN_AXR9_MASK                                                                                (0x00000200U)
#define MCASP_PDIN_AXR9_LOW                                                                                  (0U)
#define MCASP_PDIN_AXR9_HIGH                                                                                 (1U)

#define MCASP_PDIN_AXR8_SHIFT                                                                               (8U)
#define MCASP_PDIN_AXR8_MASK                                                                                (0x00000100U)
#define MCASP_PDIN_AXR8_LOW                                                                                  (0U)
#define MCASP_PDIN_AXR8_HIGH                                                                                 (1U)

#define MCASP_PDIN_AXR7_SHIFT                                                                               (7U)
#define MCASP_PDIN_AXR7_MASK                                                                                (0x00000080U)
#define MCASP_PDIN_AXR7_LOW                                                                                  (0U)
#define MCASP_PDIN_AXR7_HIGH                                                                                 (1U)

#define MCASP_PDIN_AXR6_SHIFT                                                                               (6U)
#define MCASP_PDIN_AXR6_MASK                                                                                (0x00000040U)
#define MCASP_PDIN_AXR6_LOW                                                                                  (0U)
#define MCASP_PDIN_AXR6_HIGH                                                                                 (1U)

#define MCASP_PDIN_AXR5_SHIFT                                                                               (5U)
#define MCASP_PDIN_AXR5_MASK                                                                                (0x00000020U)
#define MCASP_PDIN_AXR5_LOW                                                                                  (0U)
#define MCASP_PDIN_AXR5_HIGH                                                                                 (1U)

#define MCASP_PDIN_AXR4_SHIFT                                                                               (4U)
#define MCASP_PDIN_AXR4_MASK                                                                                (0x00000010U)
#define MCASP_PDIN_AXR4_LOW                                                                                  (0U)
#define MCASP_PDIN_AXR4_HIGH                                                                                 (1U)

#define MCASP_PDIN_AXR3_SHIFT                                                                               (3U)
#define MCASP_PDIN_AXR3_MASK                                                                                (0x00000008U)
#define MCASP_PDIN_AXR3_LOW                                                                                  (0U)
#define MCASP_PDIN_AXR3_HIGH                                                                                 (1U)

#define MCASP_PDIN_AXR2_SHIFT                                                                               (2U)
#define MCASP_PDIN_AXR2_MASK                                                                                (0x00000004U)
#define MCASP_PDIN_AXR2_LOW                                                                                  (0U)
#define MCASP_PDIN_AXR2_HIGH                                                                                 (1U)

#define MCASP_PDIN_AXR1_SHIFT                                                                               (1U)
#define MCASP_PDIN_AXR1_MASK                                                                                (0x00000002U)
#define MCASP_PDIN_AXR1_LOW                                                                                  (0U)
#define MCASP_PDIN_AXR1_HIGH                                                                                 (1U)

#define MCASP_PDIN_AXR0_SHIFT                                                                               (0U)
#define MCASP_PDIN_AXR0_MASK                                                                                (0x00000001U)
#define MCASP_PDIN_AXR0_LOW                                                                                  (0U)
#define MCASP_PDIN_AXR0_HIGH                                                                                 (1U)

#define MCASP_PDIN_RESV1_SHIFT                                                                              (30U)
#define MCASP_PDIN_RESV1_MASK                                                                               (0x40000000U)
#define MCASP_PDIN_RESV1_LOW                                                                                 (0U)
#define MCASP_PDIN_RESV1_HIGH                                                                                (1U)

#define MCASP_PDSET_AFSR_SHIFT                                                                              (31U)
#define MCASP_PDSET_AFSR_MASK                                                                               (0x80000000U)
#define MCASP_PDSET_AFSR_NOEFFECT                                                                            (0U)
#define MCASP_PDSET_AFSR_SET                                                                                 (1U)

#define MCASP_PDSET_ACLKR_SHIFT                                                                             (29U)
#define MCASP_PDSET_ACLKR_MASK                                                                              (0x20000000U)
#define MCASP_PDSET_ACLKR_NOEFFECT                                                                           (0U)
#define MCASP_PDSET_ACLKR_SET                                                                                (1U)

#define MCASP_PDSET_AFSX_SHIFT                                                                              (28U)
#define MCASP_PDSET_AFSX_MASK                                                                               (0x10000000U)
#define MCASP_PDSET_AFSX_NOEFFECT                                                                            (0U)
#define MCASP_PDSET_AFSX_SET                                                                                 (1U)

#define MCASP_PDSET_AHCLKX_SHIFT                                                                            (27U)
#define MCASP_PDSET_AHCLKX_MASK                                                                             (0x08000000U)
#define MCASP_PDSET_AHCLKX_NOEFFECT                                                                          (0U)
#define MCASP_PDSET_AHCLKX_SET                                                                               (1U)

#define MCASP_PDSET_ACLKX_SHIFT                                                                             (26U)
#define MCASP_PDSET_ACLKX_MASK                                                                              (0x04000000U)
#define MCASP_PDSET_ACLKX_NOEFFECT                                                                           (0U)
#define MCASP_PDSET_ACLKX_SET                                                                                (1U)

#define MCASP_PDSET_AMUTE_SHIFT                                                                             (25U)
#define MCASP_PDSET_AMUTE_MASK                                                                              (0x02000000U)
#define MCASP_PDSET_AMUTE_NOEFFECT                                                                           (0U)
#define MCASP_PDSET_AMUTE_SET                                                                                (1U)

#define MCASP_PDSET_RESV_SHIFT                                                                              (16U)
#define MCASP_PDSET_RESV_MASK                                                                               (0x01ff0000U)

#define MCASP_PDSET_AXR15_SHIFT                                                                             (15U)
#define MCASP_PDSET_AXR15_MASK                                                                              (0x00008000U)
#define MCASP_PDSET_AXR15_NOEFFECT                                                                           (0U)
#define MCASP_PDSET_AXR15_SET                                                                                (1U)

#define MCASP_PDSET_AXR14_SHIFT                                                                             (14U)
#define MCASP_PDSET_AXR14_MASK                                                                              (0x00004000U)
#define MCASP_PDSET_AXR14_NOEFFECT                                                                           (0U)
#define MCASP_PDSET_AXR14_SET                                                                                (1U)

#define MCASP_PDSET_AXR13_SHIFT                                                                             (13U)
#define MCASP_PDSET_AXR13_MASK                                                                              (0x00002000U)
#define MCASP_PDSET_AXR13_NOEFFECT                                                                           (0U)
#define MCASP_PDSET_AXR13_SET                                                                                (1U)

#define MCASP_PDSET_AXR12_SHIFT                                                                             (12U)
#define MCASP_PDSET_AXR12_MASK                                                                              (0x00001000U)
#define MCASP_PDSET_AXR12_NOEFFECT                                                                           (0U)
#define MCASP_PDSET_AXR12_SET                                                                                (1U)

#define MCASP_PDSET_AXR11_SHIFT                                                                             (11U)
#define MCASP_PDSET_AXR11_MASK                                                                              (0x00000800U)
#define MCASP_PDSET_AXR11_NOEFFECT                                                                           (0U)
#define MCASP_PDSET_AXR11_SET                                                                                (1U)

#define MCASP_PDSET_AXR10_SHIFT                                                                             (10U)
#define MCASP_PDSET_AXR10_MASK                                                                              (0x00000400U)
#define MCASP_PDSET_AXR10_NOEFFECT                                                                           (0U)
#define MCASP_PDSET_AXR10_SET                                                                                (1U)

#define MCASP_PDSET_AXR9_SHIFT                                                                              (9U)
#define MCASP_PDSET_AXR9_MASK                                                                               (0x00000200U)
#define MCASP_PDSET_AXR9_NOEFFECT                                                                            (0U)
#define MCASP_PDSET_AXR9_SET                                                                                 (1U)

#define MCASP_PDSET_AXR8_SHIFT                                                                              (8U)
#define MCASP_PDSET_AXR8_MASK                                                                               (0x00000100U)
#define MCASP_PDSET_AXR8_NOEFFECT                                                                            (0U)
#define MCASP_PDSET_AXR8_SET                                                                                 (1U)

#define MCASP_PDSET_AXR7_SHIFT                                                                              (7U)
#define MCASP_PDSET_AXR7_MASK                                                                               (0x00000080U)
#define MCASP_PDSET_AXR7_NOEFFECT                                                                            (0U)
#define MCASP_PDSET_AXR7_SET                                                                                 (1U)

#define MCASP_PDSET_AXR6_SHIFT                                                                              (6U)
#define MCASP_PDSET_AXR6_MASK                                                                               (0x00000040U)
#define MCASP_PDSET_AXR6_NOEFFECT                                                                            (0U)
#define MCASP_PDSET_AXR6_SET                                                                                 (1U)

#define MCASP_PDSET_AXR5_SHIFT                                                                              (5U)
#define MCASP_PDSET_AXR5_MASK                                                                               (0x00000020U)
#define MCASP_PDSET_AXR5_NOEFFECT                                                                            (0U)
#define MCASP_PDSET_AXR5_SET                                                                                 (1U)

#define MCASP_PDSET_AXR4_SHIFT                                                                              (4U)
#define MCASP_PDSET_AXR4_MASK                                                                               (0x00000010U)
#define MCASP_PDSET_AXR4_NOEFFECT                                                                            (0U)
#define MCASP_PDSET_AXR4_SET                                                                                 (1U)

#define MCASP_PDSET_AXR3_SHIFT                                                                              (3U)
#define MCASP_PDSET_AXR3_MASK                                                                               (0x00000008U)
#define MCASP_PDSET_AXR3_NOEFFECT                                                                            (0U)
#define MCASP_PDSET_AXR3_SET                                                                                 (1U)

#define MCASP_PDSET_AXR2_SHIFT                                                                              (2U)
#define MCASP_PDSET_AXR2_MASK                                                                               (0x00000004U)
#define MCASP_PDSET_AXR2_NOEFFECT                                                                            (0U)
#define MCASP_PDSET_AXR2_SET                                                                                 (1U)

#define MCASP_PDSET_AXR1_SHIFT                                                                              (1U)
#define MCASP_PDSET_AXR1_MASK                                                                               (0x00000002U)
#define MCASP_PDSET_AXR1_NOEFFECT                                                                            (0U)
#define MCASP_PDSET_AXR1_SET                                                                                 (1U)

#define MCASP_PDSET_AXR0_SHIFT                                                                              (0U)
#define MCASP_PDSET_AXR0_MASK                                                                               (0x00000001U)
#define MCASP_PDSET_AXR0_NOEFFECT                                                                            (0U)
#define MCASP_PDSET_AXR0_SET                                                                                 (1U)

#define MCASP_PDSET_RESV1_SHIFT                                                                             (30U)
#define MCASP_PDSET_RESV1_MASK                                                                              (0x40000000U)
#define MCASP_PDSET_RESV1_NOEFFECT                                                                           (0U)
#define MCASP_PDSET_RESV1_SET                                                                                (1U)

#define MCASP_PDCLR_AFSR_SHIFT                                                                              (31U)
#define MCASP_PDCLR_AFSR_MASK                                                                               (0x80000000U)
#define MCASP_PDCLR_AFSR_NOEFFECT                                                                            (0U)
#define MCASP_PDCLR_AFSR_CLEAR                                                                               (1U)

#define MCASP_PDCLR_ACLKR_SHIFT                                                                             (29U)
#define MCASP_PDCLR_ACLKR_MASK                                                                              (0x20000000U)
#define MCASP_PDCLR_ACLKR_NOEFFECT                                                                           (0U)
#define MCASP_PDCLR_ACLKR_CLEAR                                                                              (1U)

#define MCASP_PDCLR_AFSX_SHIFT                                                                              (28U)
#define MCASP_PDCLR_AFSX_MASK                                                                               (0x10000000U)
#define MCASP_PDCLR_AFSX_NOEFFECT                                                                            (0U)
#define MCASP_PDCLR_AFSX_CLEAR                                                                               (1U)

#define MCASP_PDCLR_AHCLKX_SHIFT                                                                            (27U)
#define MCASP_PDCLR_AHCLKX_MASK                                                                             (0x08000000U)
#define MCASP_PDCLR_AHCLKX_NOEFFECT                                                                          (0U)
#define MCASP_PDCLR_AHCLKX_CLEAR                                                                             (1U)

#define MCASP_PDCLR_ACLKX_SHIFT                                                                             (26U)
#define MCASP_PDCLR_ACLKX_MASK                                                                              (0x04000000U)
#define MCASP_PDCLR_ACLKX_NOEFFECT                                                                           (0U)
#define MCASP_PDCLR_ACLKX_CLEAR                                                                              (1U)

#define MCASP_PDCLR_AMUTE_SHIFT                                                                             (25U)
#define MCASP_PDCLR_AMUTE_MASK                                                                              (0x02000000U)
#define MCASP_PDCLR_AMUTE_NOEFFECT                                                                           (0U)
#define MCASP_PDCLR_AMUTE_CLEAR                                                                              (1U)

#define MCASP_PDCLR_RESV_SHIFT                                                                              (16U)
#define MCASP_PDCLR_RESV_MASK                                                                               (0x01ff0000U)

#define MCASP_PDCLR_AXR15_SHIFT                                                                             (15U)
#define MCASP_PDCLR_AXR15_MASK                                                                              (0x00008000U)
#define MCASP_PDCLR_AXR15_NOEFFECT                                                                           (0U)
#define MCASP_PDCLR_AXR15_CLEAR                                                                              (1U)

#define MCASP_PDCLR_AXR14_SHIFT                                                                             (14U)
#define MCASP_PDCLR_AXR14_MASK                                                                              (0x00004000U)
#define MCASP_PDCLR_AXR14_NOEFFECT                                                                           (0U)
#define MCASP_PDCLR_AXR14_CLEAR                                                                              (1U)

#define MCASP_PDCLR_AXR13_SHIFT                                                                             (13U)
#define MCASP_PDCLR_AXR13_MASK                                                                              (0x00002000U)
#define MCASP_PDCLR_AXR13_NOEFFECT                                                                           (0U)
#define MCASP_PDCLR_AXR13_CLEAR                                                                              (1U)

#define MCASP_PDCLR_AXR12_SHIFT                                                                             (12U)
#define MCASP_PDCLR_AXR12_MASK                                                                              (0x00001000U)
#define MCASP_PDCLR_AXR12_NOEFFECT                                                                           (0U)
#define MCASP_PDCLR_AXR12_CLEAR                                                                              (1U)

#define MCASP_PDCLR_AXR11_SHIFT                                                                             (11U)
#define MCASP_PDCLR_AXR11_MASK                                                                              (0x00000800U)
#define MCASP_PDCLR_AXR11_NOEFFECT                                                                           (0U)
#define MCASP_PDCLR_AXR11_CLEAR                                                                              (1U)

#define MCASP_PDCLR_AXR10_SHIFT                                                                             (10U)
#define MCASP_PDCLR_AXR10_MASK                                                                              (0x00000400U)
#define MCASP_PDCLR_AXR10_NOEFFECT                                                                           (0U)
#define MCASP_PDCLR_AXR10_CLEAR                                                                              (1U)

#define MCASP_PDCLR_AXR9_SHIFT                                                                              (9U)
#define MCASP_PDCLR_AXR9_MASK                                                                               (0x00000200U)
#define MCASP_PDCLR_AXR9_NOEFFECT                                                                            (0U)
#define MCASP_PDCLR_AXR9_CLEAR                                                                               (1U)

#define MCASP_PDCLR_AXR8_SHIFT                                                                              (8U)
#define MCASP_PDCLR_AXR8_MASK                                                                               (0x00000100U)
#define MCASP_PDCLR_AXR8_NOEFFECT                                                                            (0U)
#define MCASP_PDCLR_AXR8_CLEAR                                                                               (1U)

#define MCASP_PDCLR_AXR7_SHIFT                                                                              (7U)
#define MCASP_PDCLR_AXR7_MASK                                                                               (0x00000080U)
#define MCASP_PDCLR_AXR7_NOEFFECT                                                                            (0U)
#define MCASP_PDCLR_AXR7_CLEAR                                                                               (1U)

#define MCASP_PDCLR_AXR6_SHIFT                                                                              (6U)
#define MCASP_PDCLR_AXR6_MASK                                                                               (0x00000040U)
#define MCASP_PDCLR_AXR6_NOEFFECT                                                                            (0U)
#define MCASP_PDCLR_AXR6_CLEAR                                                                               (1U)

#define MCASP_PDCLR_AXR5_SHIFT                                                                              (5U)
#define MCASP_PDCLR_AXR5_MASK                                                                               (0x00000020U)
#define MCASP_PDCLR_AXR5_NOEFFECT                                                                            (0U)
#define MCASP_PDCLR_AXR5_CLEAR                                                                               (1U)

#define MCASP_PDCLR_AXR4_SHIFT                                                                              (4U)
#define MCASP_PDCLR_AXR4_MASK                                                                               (0x00000010U)
#define MCASP_PDCLR_AXR4_NOEFFECT                                                                            (0U)
#define MCASP_PDCLR_AXR4_CLEAR                                                                               (1U)

#define MCASP_PDCLR_AXR3_SHIFT                                                                              (3U)
#define MCASP_PDCLR_AXR3_MASK                                                                               (0x00000008U)
#define MCASP_PDCLR_AXR3_NOEFFECT                                                                            (0U)
#define MCASP_PDCLR_AXR3_CLEAR                                                                               (1U)

#define MCASP_PDCLR_AXR2_SHIFT                                                                              (2U)
#define MCASP_PDCLR_AXR2_MASK                                                                               (0x00000004U)
#define MCASP_PDCLR_AXR2_NOEFFECT                                                                            (0U)
#define MCASP_PDCLR_AXR2_CLEAR                                                                               (1U)

#define MCASP_PDCLR_AXR1_SHIFT                                                                              (1U)
#define MCASP_PDCLR_AXR1_MASK                                                                               (0x00000002U)
#define MCASP_PDCLR_AXR1_NOEFFECT                                                                            (0U)
#define MCASP_PDCLR_AXR1_CLEAR                                                                               (1U)

#define MCASP_PDCLR_AXR0_SHIFT                                                                              (0U)
#define MCASP_PDCLR_AXR0_MASK                                                                               (0x00000001U)
#define MCASP_PDCLR_AXR0_NOEFFECT                                                                            (0U)
#define MCASP_PDCLR_AXR0_CLEAR                                                                               (1U)

#define MCASP_PDCLR_RESV1_SHIFT                                                                             (30U)
#define MCASP_PDCLR_RESV1_MASK                                                                              (0x40000000U)
#define MCASP_PDCLR_RESV1_NOEFFECT                                                                           (0U)
#define MCASP_PDCLR_RESV1_CLEAR                                                                              (1U)

#define MCASP_GBLCTL_RESERVED_SHIFT                                                                         (13U)
#define MCASP_GBLCTL_RESERVED_MASK                                                                          (0xffffe000U)

#define MCASP_GBLCTL_XFRST_SHIFT                                                                            (12U)
#define MCASP_GBLCTL_XFRST_MASK                                                                             (0x00001000U)
#define MCASP_GBLCTL_XFRST_RESET                                                                             (0U)
#define MCASP_GBLCTL_XFRST_ACTIVE                                                                            (1U)

#define MCASP_GBLCTL_XSMRST_SHIFT                                                                           (11U)
#define MCASP_GBLCTL_XSMRST_MASK                                                                            (0x00000800U)
#define MCASP_GBLCTL_XSMRST_RESET                                                                            (0U)
#define MCASP_GBLCTL_XSMRST_ACTIVE                                                                           (1U)

#define MCASP_GBLCTL_XSRCLR_SHIFT                                                                           (10U)
#define MCASP_GBLCTL_XSRCLR_MASK                                                                            (0x00000400U)
#define MCASP_GBLCTL_XSRCLR_CLEAR                                                                            (0U)
#define MCASP_GBLCTL_XSRCLR_ACTIVE                                                                           (1U)

#define MCASP_GBLCTL_XHCLKRST_SHIFT                                                                         (9U)
#define MCASP_GBLCTL_XHCLKRST_MASK                                                                          (0x00000200U)
#define MCASP_GBLCTL_XHCLKRST_RESET                                                                          (0U)
#define MCASP_GBLCTL_XHCLKRST_ACTIVE                                                                         (1U)

#define MCASP_GBLCTL_XCLKRST_SHIFT                                                                          (8U)
#define MCASP_GBLCTL_XCLKRST_MASK                                                                           (0x00000100U)
#define MCASP_GBLCTL_XCLKRST_RESET                                                                           (0U)
#define MCASP_GBLCTL_XCLKRST_ACTIVE                                                                          (1U)

#define MCASP_GBLCTL_RESERVED1_SHIFT                                                                        (5U)
#define MCASP_GBLCTL_RESERVED1_MASK                                                                         (0x000000e0U)

#define MCASP_GBLCTL_RFRST_SHIFT                                                                            (4U)
#define MCASP_GBLCTL_RFRST_MASK                                                                             (0x00000010U)
#define MCASP_GBLCTL_RFRST_RESET                                                                             (0U)
#define MCASP_GBLCTL_RFRST_ACTIVE                                                                            (1U)

#define MCASP_GBLCTL_RSMRST_SHIFT                                                                           (3U)
#define MCASP_GBLCTL_RSMRST_MASK                                                                            (0x00000008U)
#define MCASP_GBLCTL_RSMRST_RESET                                                                            (0U)
#define MCASP_GBLCTL_RSMRST_ACTIVE                                                                           (1U)

#define MCASP_GBLCTL_RSRCLR_SHIFT                                                                           (2U)
#define MCASP_GBLCTL_RSRCLR_MASK                                                                            (0x00000004U)
#define MCASP_GBLCTL_RSRCLR_CLEAR                                                                            (0U)
#define MCASP_GBLCTL_RSRCLR_ACTIVE                                                                           (1U)

#define MCASP_GBLCTL_RHCLKRST_SHIFT                                                                         (1U)
#define MCASP_GBLCTL_RHCLKRST_MASK                                                                          (0x00000002U)
#define MCASP_GBLCTL_RHCLKRST_RESET                                                                          (0U)
#define MCASP_GBLCTL_RHCLKRST_ACTIVE                                                                         (1U)

#define MCASP_GBLCTL_RCLKRST_SHIFT                                                                          (0U)
#define MCASP_GBLCTL_RCLKRST_MASK                                                                           (0x00000001U)
#define MCASP_GBLCTL_RCLKRST_RESET                                                                           (0U)
#define MCASP_GBLCTL_RCLKRST_ACTIVE                                                                          (1U)

#define MCASP_AMUTE_RESERVED_SHIFT                                                                          (0U)
#define MCASP_AMUTE_RESERVED_MASK                                                                           (0xffffffffU)

#define MCASP_LBCTL_RESERVED3_SHIFT                                                                         (5U)
#define MCASP_LBCTL_RESERVED3_MASK                                                                          (0xffffffe0U)

#define MCASP_LBCTL_IOLBEN_SHIFT                                                                            (4U)
#define MCASP_LBCTL_IOLBEN_MASK                                                                             (0x00000010U)
#define MCASP_LBCTL_IOLBEN_DISABLE                                                                           (0U)
#define MCASP_LBCTL_IOLBEN_ENABLE                                                                            (1U)

#define MCASP_LBCTL_MODE_SHIFT                                                                              (2U)
#define MCASP_LBCTL_MODE_MASK                                                                               (0x0000000cU)
#define MCASP_LBCTL_MODE_RESERVED                                                                            (0U)
#define MCASP_LBCTL_MODE_XMTCLK                                                                              (1U)
#define MCASP_LBCTL_MODE_RESERVED1                                                                           (2U)
#define MCASP_LBCTL_MODE_RESERVED2                                                                           (3U)

#define MCASP_LBCTL_ORD_SHIFT                                                                               (1U)
#define MCASP_LBCTL_ORD_MASK                                                                                (0x00000002U)
#define MCASP_LBCTL_ORD_ODD                                                                                  (0U)
#define MCASP_LBCTL_ORD_EVEN                                                                                 (1U)

#define MCASP_LBCTL_DLBEN_SHIFT                                                                             (0U)
#define MCASP_LBCTL_DLBEN_MASK                                                                              (0x00000001U)
#define MCASP_LBCTL_DLBEN_DISABLE                                                                            (0U)
#define MCASP_LBCTL_DLBEN_ENABLE                                                                             (1U)

#define MCASP_TXDITCTL_RESERVED3_SHIFT                                                                      (4U)
#define MCASP_TXDITCTL_RESERVED3_MASK                                                                       (0xfffffff0U)

#define MCASP_TXDITCTL_VB_SHIFT                                                                             (3U)
#define MCASP_TXDITCTL_VB_MASK                                                                              (0x00000008U)
#define MCASP_TXDITCTL_VB_ZEROSTUFF                                                                          (0U)
#define MCASP_TXDITCTL_VB_ONESTUFF                                                                           (1U)

#define MCASP_TXDITCTL_VA_SHIFT                                                                             (2U)
#define MCASP_TXDITCTL_VA_MASK                                                                              (0x00000004U)
#define MCASP_TXDITCTL_VA_ZEROSTUFF                                                                          (0U)
#define MCASP_TXDITCTL_VA_ONESTUFF                                                                           (1U)

#define MCASP_TXDITCTL_RESERVED4_SHIFT                                                                      (1U)
#define MCASP_TXDITCTL_RESERVED4_MASK                                                                       (0x00000002U)

#define MCASP_TXDITCTL_DITEN_SHIFT                                                                          (0U)
#define MCASP_TXDITCTL_DITEN_MASK                                                                           (0x00000001U)
#define MCASP_TXDITCTL_DITEN_DISABLE                                                                         (0U)
#define MCASP_TXDITCTL_DITEN_ENABLE                                                                          (1U)

#define MCASP_GBLCTLR_RESERVED5_SHIFT                                                                       (13U)
#define MCASP_GBLCTLR_RESERVED5_MASK                                                                        (0xffffe000U)

#define MCASP_GBLCTLR_XFRST_SHIFT                                                                           (12U)
#define MCASP_GBLCTLR_XFRST_MASK                                                                            (0x00001000U)
#define MCASP_GBLCTLR_XFRST_RESET                                                                            (0U)
#define MCASP_GBLCTLR_XFRST_ACTIVE                                                                           (1U)

#define MCASP_GBLCTLR_XSMRST_SHIFT                                                                          (11U)
#define MCASP_GBLCTLR_XSMRST_MASK                                                                           (0x00000800U)
#define MCASP_GBLCTLR_XSMRST_RESET                                                                           (0U)
#define MCASP_GBLCTLR_XSMRST_ACTIVE                                                                          (1U)

#define MCASP_GBLCTLR_XSRCLR_SHIFT                                                                          (10U)
#define MCASP_GBLCTLR_XSRCLR_MASK                                                                           (0x00000400U)
#define MCASP_GBLCTLR_XSRCLR_CLEAR                                                                           (0U)
#define MCASP_GBLCTLR_XSRCLR_ACTIVE                                                                          (1U)

#define MCASP_GBLCTLR_XHCLKRST_SHIFT                                                                        (9U)
#define MCASP_GBLCTLR_XHCLKRST_MASK                                                                         (0x00000200U)
#define MCASP_GBLCTLR_XHCLKRST_RESET                                                                         (0U)
#define MCASP_GBLCTLR_XHCLKRST_ACTIVE                                                                        (1U)

#define MCASP_GBLCTLR_XCLKRST_SHIFT                                                                         (8U)
#define MCASP_GBLCTLR_XCLKRST_MASK                                                                          (0x00000100U)
#define MCASP_GBLCTLR_XCLKRST_RESET                                                                          (0U)
#define MCASP_GBLCTLR_XCLKRST_ACTIVE                                                                         (1U)

#define MCASP_GBLCTLR_RESERVED6_SHIFT                                                                       (5U)
#define MCASP_GBLCTLR_RESERVED6_MASK                                                                        (0x000000e0U)

#define MCASP_GBLCTLR_RFRST_SHIFT                                                                           (4U)
#define MCASP_GBLCTLR_RFRST_MASK                                                                            (0x00000010U)
#define MCASP_GBLCTLR_RFRST_RESET                                                                            (0U)
#define MCASP_GBLCTLR_RFRST_ACTIVE                                                                           (1U)

#define MCASP_GBLCTLR_RSMRST_SHIFT                                                                          (3U)
#define MCASP_GBLCTLR_RSMRST_MASK                                                                           (0x00000008U)
#define MCASP_GBLCTLR_RSMRST_RESET                                                                           (0U)
#define MCASP_GBLCTLR_RSMRST_ACTIVE                                                                          (1U)

#define MCASP_GBLCTLR_RSRCLR_SHIFT                                                                          (2U)
#define MCASP_GBLCTLR_RSRCLR_MASK                                                                           (0x00000004U)
#define MCASP_GBLCTLR_RSRCLR_CLEAR                                                                           (0U)
#define MCASP_GBLCTLR_RSRCLR_ACTIVE                                                                          (1U)

#define MCASP_GBLCTLR_RHCLKRST_SHIFT                                                                        (1U)
#define MCASP_GBLCTLR_RHCLKRST_MASK                                                                         (0x00000002U)
#define MCASP_GBLCTLR_RHCLKRST_RESET                                                                         (0U)
#define MCASP_GBLCTLR_RHCLKRST_ACTIVE                                                                        (1U)

#define MCASP_GBLCTLR_RCLKRST_SHIFT                                                                         (0U)
#define MCASP_GBLCTLR_RCLKRST_MASK                                                                          (0x00000001U)
#define MCASP_GBLCTLR_RCLKRST_RESET                                                                          (0U)
#define MCASP_GBLCTLR_RCLKRST_ACTIVE                                                                         (1U)

#define MCASP_RXMASK_RMASK31_SHIFT                                                                          (31U)
#define MCASP_RXMASK_RMASK31_MASK                                                                           (0x80000000U)
#define MCASP_RXMASK_RMASK31_USEMASK                                                                         (0U)
#define MCASP_RXMASK_RMASK31_NOMASK                                                                          (1U)

#define MCASP_RXMASK_RMASK30_SHIFT                                                                          (30U)
#define MCASP_RXMASK_RMASK30_MASK                                                                           (0x40000000U)
#define MCASP_RXMASK_RMASK30_USEMASK                                                                         (0U)
#define MCASP_RXMASK_RMASK30_NOMASK                                                                          (1U)

#define MCASP_RXMASK_RMASK29_SHIFT                                                                          (29U)
#define MCASP_RXMASK_RMASK29_MASK                                                                           (0x20000000U)
#define MCASP_RXMASK_RMASK29_USEMASK                                                                         (0U)
#define MCASP_RXMASK_RMASK29_NOMASK                                                                          (1U)

#define MCASP_RXMASK_RMASK28_SHIFT                                                                          (28U)
#define MCASP_RXMASK_RMASK28_MASK                                                                           (0x10000000U)
#define MCASP_RXMASK_RMASK28_USEMASK                                                                         (0U)
#define MCASP_RXMASK_RMASK28_NOMASK                                                                          (1U)

#define MCASP_RXMASK_RMASK27_SHIFT                                                                          (27U)
#define MCASP_RXMASK_RMASK27_MASK                                                                           (0x08000000U)
#define MCASP_RXMASK_RMASK27_USEMASK                                                                         (0U)
#define MCASP_RXMASK_RMASK27_NOMASK                                                                          (1U)

#define MCASP_RXMASK_RMASK26_SHIFT                                                                          (26U)
#define MCASP_RXMASK_RMASK26_MASK                                                                           (0x04000000U)
#define MCASP_RXMASK_RMASK26_USEMASK                                                                         (0U)
#define MCASP_RXMASK_RMASK26_NOMASK                                                                          (1U)

#define MCASP_RXMASK_RMASK25_SHIFT                                                                          (25U)
#define MCASP_RXMASK_RMASK25_MASK                                                                           (0x02000000U)
#define MCASP_RXMASK_RMASK25_USEMASK                                                                         (0U)
#define MCASP_RXMASK_RMASK25_NOMASK                                                                          (1U)

#define MCASP_RXMASK_RMASK24_SHIFT                                                                          (24U)
#define MCASP_RXMASK_RMASK24_MASK                                                                           (0x01000000U)
#define MCASP_RXMASK_RMASK24_USEMASK                                                                         (0U)
#define MCASP_RXMASK_RMASK24_NOMASK                                                                          (1U)

#define MCASP_RXMASK_RMASK23_SHIFT                                                                          (23U)
#define MCASP_RXMASK_RMASK23_MASK                                                                           (0x00800000U)
#define MCASP_RXMASK_RMASK23_USEMASK                                                                         (0U)
#define MCASP_RXMASK_RMASK23_NOMASK                                                                          (1U)

#define MCASP_RXMASK_RMASK22_SHIFT                                                                          (22U)
#define MCASP_RXMASK_RMASK22_MASK                                                                           (0x00400000U)
#define MCASP_RXMASK_RMASK22_USEMASK                                                                         (0U)
#define MCASP_RXMASK_RMASK22_NOMASK                                                                          (1U)

#define MCASP_RXMASK_RMASK21_SHIFT                                                                          (21U)
#define MCASP_RXMASK_RMASK21_MASK                                                                           (0x00200000U)
#define MCASP_RXMASK_RMASK21_USEMASK                                                                         (0U)
#define MCASP_RXMASK_RMASK21_NOMASK                                                                          (1U)

#define MCASP_RXMASK_RMASK20_SHIFT                                                                          (20U)
#define MCASP_RXMASK_RMASK20_MASK                                                                           (0x00100000U)
#define MCASP_RXMASK_RMASK20_USEMASK                                                                         (0U)
#define MCASP_RXMASK_RMASK20_NOMASK                                                                          (1U)

#define MCASP_RXMASK_RMASK19_SHIFT                                                                          (19U)
#define MCASP_RXMASK_RMASK19_MASK                                                                           (0x00080000U)
#define MCASP_RXMASK_RMASK19_USEMASK                                                                         (0U)
#define MCASP_RXMASK_RMASK19_NOMASK                                                                          (1U)

#define MCASP_RXMASK_RMASK18_SHIFT                                                                          (18U)
#define MCASP_RXMASK_RMASK18_MASK                                                                           (0x00040000U)
#define MCASP_RXMASK_RMASK18_USEMASK                                                                         (0U)
#define MCASP_RXMASK_RMASK18_NOMASK                                                                          (1U)

#define MCASP_RXMASK_RMASK17_SHIFT                                                                          (17U)
#define MCASP_RXMASK_RMASK17_MASK                                                                           (0x00020000U)
#define MCASP_RXMASK_RMASK17_USEMASK                                                                         (0U)
#define MCASP_RXMASK_RMASK17_NOMASK                                                                          (1U)

#define MCASP_RXMASK_RMASK16_SHIFT                                                                          (16U)
#define MCASP_RXMASK_RMASK16_MASK                                                                           (0x00010000U)
#define MCASP_RXMASK_RMASK16_USEMASK                                                                         (0U)
#define MCASP_RXMASK_RMASK16_NOMASK                                                                          (1U)

#define MCASP_RXMASK_RMASK15_SHIFT                                                                          (15U)
#define MCASP_RXMASK_RMASK15_MASK                                                                           (0x00008000U)
#define MCASP_RXMASK_RMASK15_USEMASK                                                                         (0U)
#define MCASP_RXMASK_RMASK15_NOMASK                                                                          (1U)

#define MCASP_RXMASK_RMASK14_SHIFT                                                                          (14U)
#define MCASP_RXMASK_RMASK14_MASK                                                                           (0x00004000U)
#define MCASP_RXMASK_RMASK14_USEMASK                                                                         (0U)
#define MCASP_RXMASK_RMASK14_NOMASK                                                                          (1U)

#define MCASP_RXMASK_RMASK13_SHIFT                                                                          (13U)
#define MCASP_RXMASK_RMASK13_MASK                                                                           (0x00002000U)
#define MCASP_RXMASK_RMASK13_USEMASK                                                                         (0U)
#define MCASP_RXMASK_RMASK13_NOMASK                                                                          (1U)

#define MCASP_RXMASK_RMASK12_SHIFT                                                                          (12U)
#define MCASP_RXMASK_RMASK12_MASK                                                                           (0x00001000U)
#define MCASP_RXMASK_RMASK12_USEMASK                                                                         (0U)
#define MCASP_RXMASK_RMASK12_NOMASK                                                                          (1U)

#define MCASP_RXMASK_RMASK11_SHIFT                                                                          (11U)
#define MCASP_RXMASK_RMASK11_MASK                                                                           (0x00000800U)
#define MCASP_RXMASK_RMASK11_USEMASK                                                                         (0U)
#define MCASP_RXMASK_RMASK11_NOMASK                                                                          (1U)

#define MCASP_RXMASK_RMASK10_SHIFT                                                                          (10U)
#define MCASP_RXMASK_RMASK10_MASK                                                                           (0x00000400U)
#define MCASP_RXMASK_RMASK10_USEMASK                                                                         (0U)
#define MCASP_RXMASK_RMASK10_NOMASK                                                                          (1U)

#define MCASP_RXMASK_RMASK9_SHIFT                                                                           (9U)
#define MCASP_RXMASK_RMASK9_MASK                                                                            (0x00000200U)
#define MCASP_RXMASK_RMASK9_USEMASK                                                                          (0U)
#define MCASP_RXMASK_RMASK9_NOMASK                                                                           (1U)

#define MCASP_RXMASK_RMASK8_SHIFT                                                                           (8U)
#define MCASP_RXMASK_RMASK8_MASK                                                                            (0x00000100U)
#define MCASP_RXMASK_RMASK8_USEMASK                                                                          (0U)
#define MCASP_RXMASK_RMASK8_NOMASK                                                                           (1U)

#define MCASP_RXMASK_RMASK7_SHIFT                                                                           (7U)
#define MCASP_RXMASK_RMASK7_MASK                                                                            (0x00000080U)
#define MCASP_RXMASK_RMASK7_USEMASK                                                                          (0U)
#define MCASP_RXMASK_RMASK7_NOMASK                                                                           (1U)

#define MCASP_RXMASK_RMASK6_SHIFT                                                                           (6U)
#define MCASP_RXMASK_RMASK6_MASK                                                                            (0x00000040U)
#define MCASP_RXMASK_RMASK6_USEMASK                                                                          (0U)
#define MCASP_RXMASK_RMASK6_NOMASK                                                                           (1U)

#define MCASP_RXMASK_RMASK5_SHIFT                                                                           (5U)
#define MCASP_RXMASK_RMASK5_MASK                                                                            (0x00000020U)
#define MCASP_RXMASK_RMASK5_USEMASK                                                                          (0U)
#define MCASP_RXMASK_RMASK5_NOMASK                                                                           (1U)

#define MCASP_RXMASK_RMASK4_SHIFT                                                                           (4U)
#define MCASP_RXMASK_RMASK4_MASK                                                                            (0x00000010U)
#define MCASP_RXMASK_RMASK4_USEMASK                                                                          (0U)
#define MCASP_RXMASK_RMASK4_NOMASK                                                                           (1U)

#define MCASP_RXMASK_RMASK3_SHIFT                                                                           (3U)
#define MCASP_RXMASK_RMASK3_MASK                                                                            (0x00000008U)
#define MCASP_RXMASK_RMASK3_USEMASK                                                                          (0U)
#define MCASP_RXMASK_RMASK3_NOMASK                                                                           (1U)

#define MCASP_RXMASK_RMASK2_SHIFT                                                                           (2U)
#define MCASP_RXMASK_RMASK2_MASK                                                                            (0x00000004U)
#define MCASP_RXMASK_RMASK2_USEMASK                                                                          (0U)
#define MCASP_RXMASK_RMASK2_NOMASK                                                                           (1U)

#define MCASP_RXMASK_RMASK1_SHIFT                                                                           (1U)
#define MCASP_RXMASK_RMASK1_MASK                                                                            (0x00000002U)
#define MCASP_RXMASK_RMASK1_USEMASK                                                                          (0U)
#define MCASP_RXMASK_RMASK1_NOMASK                                                                           (1U)

#define MCASP_RXMASK_RMASK0_SHIFT                                                                           (0U)
#define MCASP_RXMASK_RMASK0_MASK                                                                            (0x00000001U)
#define MCASP_RXMASK_RMASK0_USEMASK                                                                          (0U)
#define MCASP_RXMASK_RMASK0_NOMASK                                                                           (1U)

#define MCASP_RXFMT_RESERVED7_SHIFT                                                                         (18U)
#define MCASP_RXFMT_RESERVED7_MASK                                                                          (0xfffc0000U)

#define MCASP_RXFMT_RDATDLY_SHIFT                                                                           (16U)
#define MCASP_RXFMT_RDATDLY_MASK                                                                            (0x00030000U)
#define MCASP_RXFMT_RDATDLY_0BIT                                                                             (0U)
#define MCASP_RXFMT_RDATDLY_1BIT                                                                             (1U)
#define MCASP_RXFMT_RDATDLY_2BIT                                                                             (2U)

#define MCASP_RXFMT_RRVRS_SHIFT                                                                             (15U)
#define MCASP_RXFMT_RRVRS_MASK                                                                              (0x00008000U)
#define MCASP_RXFMT_RRVRS_LSBFIRST                                                                           (0U)
#define MCASP_RXFMT_RRVRS_MSBFIRST                                                                           (1U)

#define MCASP_RXFMT_RPAD_SHIFT                                                                              (13U)
#define MCASP_RXFMT_RPAD_MASK                                                                               (0x00006000U)
#define MCASP_RXFMT_RPAD_ZERO                                                                                (0U)
#define MCASP_RXFMT_RPAD_ONE                                                                                 (1U)
#define MCASP_RXFMT_RPAD_RPBIT                                                                               (2U)

#define MCASP_RXFMT_RPBIT_SHIFT                                                                             (8U)
#define MCASP_RXFMT_RPBIT_MASK                                                                              (0x00001f00U)

#define MCASP_RXFMT_RSSZ_SHIFT                                                                              (4U)
#define MCASP_RXFMT_RSSZ_MASK                                                                               (0x000000f0U)
#define MCASP_RXFMT_RSSZ_RSV                                                                                 (0U)
#define MCASP_RXFMT_RSSZ_RSV1                                                                                (1U)
#define MCASP_RXFMT_RSSZ_RSV2                                                                                (2U)
#define MCASP_RXFMT_RSSZ_8BITS                                                                               (3U)
#define MCASP_RXFMT_RSSZ_RSV3                                                                                (4U)
#define MCASP_RXFMT_RSSZ_12BITS                                                                              (5U)
#define MCASP_RXFMT_RSSZ_RSV4                                                                                (6U)
#define MCASP_RXFMT_RSSZ_16BITS                                                                              (7U)
#define MCASP_RXFMT_RSSZ_RSV5                                                                                (8U)
#define MCASP_RXFMT_RSSZ_20BITS                                                                              (9U)
#define MCASP_RXFMT_RSSZ_RSV6                                                                                (10U)
#define MCASP_RXFMT_RSSZ_24BITS                                                                              (11U)
#define MCASP_RXFMT_RSSZ_RSV7                                                                                (12U)
#define MCASP_RXFMT_RSSZ_28BITS                                                                              (13U)
#define MCASP_RXFMT_RSSZ_RSV8                                                                                (14U)
#define MCASP_RXFMT_RSSZ_32BITS                                                                              (15U)

#define MCASP_RXFMT_RBUSEL_SHIFT                                                                            (3U)
#define MCASP_RXFMT_RBUSEL_MASK                                                                             (0x00000008U)
#define MCASP_RXFMT_RBUSEL_VBUSP                                                                             (0U)
#define MCASP_RXFMT_RBUSEL_VBUS                                                                              (1U)

#define MCASP_RXFMT_RROT_SHIFT                                                                              (0U)
#define MCASP_RXFMT_RROT_MASK                                                                               (0x00000007U)
#define MCASP_RXFMT_RROT_NONE                                                                                (0U)
#define MCASP_RXFMT_RROT_4BITS                                                                               (1U)
#define MCASP_RXFMT_RROT_8BITS                                                                               (2U)
#define MCASP_RXFMT_RROT_12BITS                                                                              (3U)
#define MCASP_RXFMT_RROT_16BITS                                                                              (4U)
#define MCASP_RXFMT_RROT_20BITS                                                                              (5U)
#define MCASP_RXFMT_RROT_24BITS                                                                              (6U)
#define MCASP_RXFMT_RROT_28BITS                                                                              (7U)

#define MCASP_RXFMCTL_RESERVED8_SHIFT                                                                       (16U)
#define MCASP_RXFMCTL_RESERVED8_MASK                                                                        (0xffff0000U)

#define MCASP_RXFMCTL_RMOD_SHIFT                                                                            (7U)
#define MCASP_RXFMCTL_RMOD_MASK                                                                             (0x0000ff80U)

#define MCASP_RXFMCTL_RESERVED9_SHIFT                                                                       (5U)
#define MCASP_RXFMCTL_RESERVED9_MASK                                                                        (0x00000060U)

#define MCASP_RXFMCTL_FRWID_SHIFT                                                                           (4U)
#define MCASP_RXFMCTL_FRWID_MASK                                                                            (0x00000010U)
#define MCASP_RXFMCTL_FRWID_BIT                                                                              (0U)
#define MCASP_RXFMCTL_FRWID_WORD                                                                             (1U)

#define MCASP_RXFMCTL_RESERVED10_SHIFT                                                                      (2U)
#define MCASP_RXFMCTL_RESERVED10_MASK                                                                       (0x0000000cU)

#define MCASP_RXFMCTL_FSRM_SHIFT                                                                            (1U)
#define MCASP_RXFMCTL_FSRM_MASK                                                                             (0x00000002U)
#define MCASP_RXFMCTL_FSRM_EXTERNAL                                                                          (0U)
#define MCASP_RXFMCTL_FSRM_INTERNAL                                                                          (1U)

#define MCASP_RXFMCTL_FSRP_SHIFT                                                                            (0U)
#define MCASP_RXFMCTL_FSRP_MASK                                                                             (0x00000001U)
#define MCASP_RXFMCTL_FSRP_RISINGEDGE                                                                        (0U)
#define MCASP_RXFMCTL_FSRP_FALLINGEDGE                                                                       (1U)

#define MCASP_ACLKRCTL_RESERVED11_SHIFT                                                                     (21U)
#define MCASP_ACLKRCTL_RESERVED11_MASK                                                                      (0xffe00000U)

#define MCASP_ACLKRCTL_BUSY_SHIFT                                                                           (20U)
#define MCASP_ACLKRCTL_BUSY_MASK                                                                            (0x00100000U)
#define MCASP_ACLKRCTL_BUSY_NOTBUSY                                                                          (0U)
#define MCASP_ACLKRCTL_BUSY_BUSY                                                                             (1U)

#define MCASP_ACLKRCTL_DIVBUSY_SHIFT                                                                        (19U)
#define MCASP_ACLKRCTL_DIVBUSY_MASK                                                                         (0x00080000U)
#define MCASP_ACLKRCTL_DIVBUSY_NOTBUSY                                                                       (0U)
#define MCASP_ACLKRCTL_DIVBUSY_BUSY                                                                          (1U)

#define MCASP_ACLKRCTL_ADJBUSY_SHIFT                                                                        (18U)
#define MCASP_ACLKRCTL_ADJBUSY_MASK                                                                         (0x00040000U)
#define MCASP_ACLKRCTL_ADJBUSY_NOTBUSY                                                                       (0U)
#define MCASP_ACLKRCTL_ADJBUSY_BUSY                                                                          (1U)

#define MCASP_ACLKRCTL_CLKRADJ_SHIFT                                                                        (16U)
#define MCASP_ACLKRCTL_CLKRADJ_MASK                                                                         (0x00030000U)
#define MCASP_ACLKRCTL_CLKRADJ_PLUSZERO                                                                      (0U)
#define MCASP_ACLKRCTL_CLKRADJ_MINUSONE                                                                      (1U)
#define MCASP_ACLKRCTL_CLKRADJ_PLUSONE                                                                       (2U)
#define MCASP_ACLKRCTL_CLKRADJ_PLUSZER0                                                                      (3U)

#define MCASP_ACLKRCTL_RESERVED12_SHIFT                                                                     (8U)
#define MCASP_ACLKRCTL_RESERVED12_MASK                                                                      (0x0000ff00U)

#define MCASP_ACLKRCTL_CLKRP_SHIFT                                                                          (7U)
#define MCASP_ACLKRCTL_CLKRP_MASK                                                                           (0x00000080U)
#define MCASP_ACLKRCTL_CLKRP_FALLINGEDGE                                                                     (0U)
#define MCASP_ACLKRCTL_CLKRP_RISINGEDGE                                                                      (1U)

#define MCASP_ACLKRCTL_RESERVED13_SHIFT                                                                     (6U)
#define MCASP_ACLKRCTL_RESERVED13_MASK                                                                      (0x00000040U)

#define MCASP_ACLKRCTL_CLKRM_SHIFT                                                                          (5U)
#define MCASP_ACLKRCTL_CLKRM_MASK                                                                           (0x00000020U)
#define MCASP_ACLKRCTL_CLKRM_EXTERNAL                                                                        (0U)
#define MCASP_ACLKRCTL_CLKRM_INTERNAL                                                                        (1U)

#define MCASP_ACLKRCTL_CLKRDIV_SHIFT                                                                        (0U)
#define MCASP_ACLKRCTL_CLKRDIV_MASK                                                                         (0x0000001fU)

#define MCASP_AHCLKRCTL_RESERVED14_SHIFT                                                                    (21U)
#define MCASP_AHCLKRCTL_RESERVED14_MASK                                                                     (0xffe00000U)

#define MCASP_AHCLKRCTL_BUSY_SHIFT                                                                          (20U)
#define MCASP_AHCLKRCTL_BUSY_MASK                                                                           (0x00100000U)
#define MCASP_AHCLKRCTL_BUSY_NOTBUSY                                                                         (0U)
#define MCASP_AHCLKRCTL_BUSY_BUSY                                                                            (1U)

#define MCASP_AHCLKRCTL_DIVBUSY_SHIFT                                                                       (19U)
#define MCASP_AHCLKRCTL_DIVBUSY_MASK                                                                        (0x00080000U)
#define MCASP_AHCLKRCTL_DIVBUSY_NOTBUSY                                                                      (0U)
#define MCASP_AHCLKRCTL_DIVBUSY_BUSY                                                                         (1U)

#define MCASP_AHCLKRCTL_ADJBUSY_SHIFT                                                                       (18U)
#define MCASP_AHCLKRCTL_ADJBUSY_MASK                                                                        (0x00040000U)
#define MCASP_AHCLKRCTL_ADJBUSY_NOTBUSY                                                                      (0U)
#define MCASP_AHCLKRCTL_ADJBUSY_BUSY                                                                         (1U)

#define MCASP_AHCLKRCTL_HCLKRADJ_SHIFT                                                                      (16U)
#define MCASP_AHCLKRCTL_HCLKRADJ_MASK                                                                       (0x00030000U)
#define MCASP_AHCLKRCTL_HCLKRADJ_PLUSZERO                                                                    (0U)
#define MCASP_AHCLKRCTL_HCLKRADJ_MINUSONE                                                                    (1U)
#define MCASP_AHCLKRCTL_HCLKRADJ_PLUSONE                                                                     (2U)
#define MCASP_AHCLKRCTL_HCLKRADJ_PLUSZER0                                                                    (3U)

#define MCASP_AHCLKRCTL_HCLKRM_SHIFT                                                                        (15U)
#define MCASP_AHCLKRCTL_HCLKRM_MASK                                                                         (0x00008000U)
#define MCASP_AHCLKRCTL_HCLKRM_EXTERNAL                                                                      (0U)
#define MCASP_AHCLKRCTL_HCLKRM_INTERNAL                                                                      (1U)

#define MCASP_AHCLKRCTL_HCLKRP_SHIFT                                                                        (14U)
#define MCASP_AHCLKRCTL_HCLKRP_MASK                                                                         (0x00004000U)
#define MCASP_AHCLKRCTL_HCLKRP_NOTINVERTED                                                                   (0U)
#define MCASP_AHCLKRCTL_HCLKRP_INVERTED                                                                      (1U)

#define MCASP_AHCLKRCTL_RESERVED15_SHIFT                                                                    (12U)
#define MCASP_AHCLKRCTL_RESERVED15_MASK                                                                     (0x00003000U)

#define MCASP_AHCLKRCTL_HCLKRDIV_SHIFT                                                                      (0U)
#define MCASP_AHCLKRCTL_HCLKRDIV_MASK                                                                       (0x00000fffU)

#define MCASP_RXTDM_RTDMS31_SHIFT                                                                           (31U)
#define MCASP_RXTDM_RTDMS31_MASK                                                                            (0x80000000U)
#define MCASP_RXTDM_RTDMS31_INACTIVE                                                                         (0U)
#define MCASP_RXTDM_RTDMS31_ACTIVE                                                                           (1U)

#define MCASP_RXTDM_RTDMS30_SHIFT                                                                           (30U)
#define MCASP_RXTDM_RTDMS30_MASK                                                                            (0x40000000U)
#define MCASP_RXTDM_RTDMS30_INACTIVE                                                                         (0U)
#define MCASP_RXTDM_RTDMS30_ACTIVE                                                                           (1U)

#define MCASP_RXTDM_RTDMS29_SHIFT                                                                           (29U)
#define MCASP_RXTDM_RTDMS29_MASK                                                                            (0x20000000U)
#define MCASP_RXTDM_RTDMS29_INACTIVE                                                                         (0U)
#define MCASP_RXTDM_RTDMS29_ACTIVE                                                                           (1U)

#define MCASP_RXTDM_RTDMS28_SHIFT                                                                           (28U)
#define MCASP_RXTDM_RTDMS28_MASK                                                                            (0x10000000U)
#define MCASP_RXTDM_RTDMS28_INACTIVE                                                                         (0U)
#define MCASP_RXTDM_RTDMS28_ACTIVE                                                                           (1U)

#define MCASP_RXTDM_RTDMS27_SHIFT                                                                           (27U)
#define MCASP_RXTDM_RTDMS27_MASK                                                                            (0x08000000U)
#define MCASP_RXTDM_RTDMS27_INACTIVE                                                                         (0U)
#define MCASP_RXTDM_RTDMS27_ACTIVE                                                                           (1U)

#define MCASP_RXTDM_RTDMS26_SHIFT                                                                           (26U)
#define MCASP_RXTDM_RTDMS26_MASK                                                                            (0x04000000U)
#define MCASP_RXTDM_RTDMS26_INACTIVE                                                                         (0U)
#define MCASP_RXTDM_RTDMS26_ACTIVE                                                                           (1U)

#define MCASP_RXTDM_RTDMS25_SHIFT                                                                           (25U)
#define MCASP_RXTDM_RTDMS25_MASK                                                                            (0x02000000U)
#define MCASP_RXTDM_RTDMS25_INACTIVE                                                                         (0U)
#define MCASP_RXTDM_RTDMS25_ACTIVE                                                                           (1U)

#define MCASP_RXTDM_RTDMS24_SHIFT                                                                           (24U)
#define MCASP_RXTDM_RTDMS24_MASK                                                                            (0x01000000U)
#define MCASP_RXTDM_RTDMS24_INACTIVE                                                                         (0U)
#define MCASP_RXTDM_RTDMS24_ACTIVE                                                                           (1U)

#define MCASP_RXTDM_RTDMS23_SHIFT                                                                           (23U)
#define MCASP_RXTDM_RTDMS23_MASK                                                                            (0x00800000U)
#define MCASP_RXTDM_RTDMS23_INACTIVE                                                                         (0U)
#define MCASP_RXTDM_RTDMS23_ACTIVE                                                                           (1U)

#define MCASP_RXTDM_RTDMS22_SHIFT                                                                           (22U)
#define MCASP_RXTDM_RTDMS22_MASK                                                                            (0x00400000U)
#define MCASP_RXTDM_RTDMS22_INACTIVE                                                                         (0U)
#define MCASP_RXTDM_RTDMS22_ACTIVE                                                                           (1U)

#define MCASP_RXTDM_RTDMS21_SHIFT                                                                           (21U)
#define MCASP_RXTDM_RTDMS21_MASK                                                                            (0x00200000U)
#define MCASP_RXTDM_RTDMS21_INACTIVE                                                                         (0U)
#define MCASP_RXTDM_RTDMS21_ACTIVE                                                                           (1U)

#define MCASP_RXTDM_RTDMS20_SHIFT                                                                           (20U)
#define MCASP_RXTDM_RTDMS20_MASK                                                                            (0x00100000U)
#define MCASP_RXTDM_RTDMS20_INACTIVE                                                                         (0U)
#define MCASP_RXTDM_RTDMS20_ACTIVE                                                                           (1U)

#define MCASP_RXTDM_RTDMS19_SHIFT                                                                           (19U)
#define MCASP_RXTDM_RTDMS19_MASK                                                                            (0x00080000U)
#define MCASP_RXTDM_RTDMS19_INACTIVE                                                                         (0U)
#define MCASP_RXTDM_RTDMS19_ACTIVE                                                                           (1U)

#define MCASP_RXTDM_RTDMS18_SHIFT                                                                           (18U)
#define MCASP_RXTDM_RTDMS18_MASK                                                                            (0x00040000U)
#define MCASP_RXTDM_RTDMS18_INACTIVE                                                                         (0U)
#define MCASP_RXTDM_RTDMS18_ACTIVE                                                                           (1U)

#define MCASP_RXTDM_RTDMS17_SHIFT                                                                           (17U)
#define MCASP_RXTDM_RTDMS17_MASK                                                                            (0x00020000U)
#define MCASP_RXTDM_RTDMS17_INACTIVE                                                                         (0U)
#define MCASP_RXTDM_RTDMS17_ACTIVE                                                                           (1U)

#define MCASP_RXTDM_RTDMS16_SHIFT                                                                           (16U)
#define MCASP_RXTDM_RTDMS16_MASK                                                                            (0x00010000U)
#define MCASP_RXTDM_RTDMS16_INACTIVE                                                                         (0U)
#define MCASP_RXTDM_RTDMS16_ACTIVE                                                                           (1U)

#define MCASP_RXTDM_RTDMS15_SHIFT                                                                           (15U)
#define MCASP_RXTDM_RTDMS15_MASK                                                                            (0x00008000U)
#define MCASP_RXTDM_RTDMS15_INACTIVE                                                                         (0U)
#define MCASP_RXTDM_RTDMS15_ACTIVE                                                                           (1U)

#define MCASP_RXTDM_RTDMS14_SHIFT                                                                           (14U)
#define MCASP_RXTDM_RTDMS14_MASK                                                                            (0x00004000U)
#define MCASP_RXTDM_RTDMS14_INACTIVE                                                                         (0U)
#define MCASP_RXTDM_RTDMS14_ACTIVE                                                                           (1U)

#define MCASP_RXTDM_RTDMS13_SHIFT                                                                           (13U)
#define MCASP_RXTDM_RTDMS13_MASK                                                                            (0x00002000U)
#define MCASP_RXTDM_RTDMS13_INACTIVE                                                                         (0U)
#define MCASP_RXTDM_RTDMS13_ACTIVE                                                                           (1U)

#define MCASP_RXTDM_RTDMS12_SHIFT                                                                           (12U)
#define MCASP_RXTDM_RTDMS12_MASK                                                                            (0x00001000U)
#define MCASP_RXTDM_RTDMS12_INACTIVE                                                                         (0U)
#define MCASP_RXTDM_RTDMS12_ACTIVE                                                                           (1U)

#define MCASP_RXTDM_RTDMS11_SHIFT                                                                           (11U)
#define MCASP_RXTDM_RTDMS11_MASK                                                                            (0x00000800U)
#define MCASP_RXTDM_RTDMS11_INACTIVE                                                                         (0U)
#define MCASP_RXTDM_RTDMS11_ACTIVE                                                                           (1U)

#define MCASP_RXTDM_RTDMS10_SHIFT                                                                           (10U)
#define MCASP_RXTDM_RTDMS10_MASK                                                                            (0x00000400U)
#define MCASP_RXTDM_RTDMS10_INACTIVE                                                                         (0U)
#define MCASP_RXTDM_RTDMS10_ACTIVE                                                                           (1U)

#define MCASP_RXTDM_RTDMS9_SHIFT                                                                            (9U)
#define MCASP_RXTDM_RTDMS9_MASK                                                                             (0x00000200U)
#define MCASP_RXTDM_RTDMS9_INACTIVE                                                                          (0U)
#define MCASP_RXTDM_RTDMS9_ACTIVE                                                                            (1U)

#define MCASP_RXTDM_RTDMS8_SHIFT                                                                            (8U)
#define MCASP_RXTDM_RTDMS8_MASK                                                                             (0x00000100U)
#define MCASP_RXTDM_RTDMS8_INACTIVE                                                                          (0U)
#define MCASP_RXTDM_RTDMS8_ACTIVE                                                                            (1U)

#define MCASP_RXTDM_RTDMS7_SHIFT                                                                            (7U)
#define MCASP_RXTDM_RTDMS7_MASK                                                                             (0x00000080U)
#define MCASP_RXTDM_RTDMS7_INACTIVE                                                                          (0U)
#define MCASP_RXTDM_RTDMS7_ACTIVE                                                                            (1U)

#define MCASP_RXTDM_RTDMS6_SHIFT                                                                            (6U)
#define MCASP_RXTDM_RTDMS6_MASK                                                                             (0x00000040U)
#define MCASP_RXTDM_RTDMS6_INACTIVE                                                                          (0U)
#define MCASP_RXTDM_RTDMS6_ACTIVE                                                                            (1U)

#define MCASP_RXTDM_RTDMS5_SHIFT                                                                            (5U)
#define MCASP_RXTDM_RTDMS5_MASK                                                                             (0x00000020U)
#define MCASP_RXTDM_RTDMS5_INACTIVE                                                                          (0U)
#define MCASP_RXTDM_RTDMS5_ACTIVE                                                                            (1U)

#define MCASP_RXTDM_RTDMS4_SHIFT                                                                            (4U)
#define MCASP_RXTDM_RTDMS4_MASK                                                                             (0x00000010U)
#define MCASP_RXTDM_RTDMS4_INACTIVE                                                                          (0U)
#define MCASP_RXTDM_RTDMS4_ACTIVE                                                                            (1U)

#define MCASP_RXTDM_RTDMS3_SHIFT                                                                            (3U)
#define MCASP_RXTDM_RTDMS3_MASK                                                                             (0x00000008U)
#define MCASP_RXTDM_RTDMS3_INACTIVE                                                                          (0U)
#define MCASP_RXTDM_RTDMS3_ACTIVE                                                                            (1U)

#define MCASP_RXTDM_RTDMS2_SHIFT                                                                            (2U)
#define MCASP_RXTDM_RTDMS2_MASK                                                                             (0x00000004U)
#define MCASP_RXTDM_RTDMS2_INACTIVE                                                                          (0U)
#define MCASP_RXTDM_RTDMS2_ACTIVE                                                                            (1U)

#define MCASP_RXTDM_RTDMS1_SHIFT                                                                            (1U)
#define MCASP_RXTDM_RTDMS1_MASK                                                                             (0x00000002U)
#define MCASP_RXTDM_RTDMS1_INACTIVE                                                                          (0U)
#define MCASP_RXTDM_RTDMS1_ACTIVE                                                                            (1U)

#define MCASP_RXTDM_RTDMS0_SHIFT                                                                            (0U)
#define MCASP_RXTDM_RTDMS0_MASK                                                                             (0x00000001U)
#define MCASP_RXTDM_RTDMS0_INACTIVE                                                                          (0U)
#define MCASP_RXTDM_RTDMS0_ACTIVE                                                                            (1U)

#define MCASP_EVTCTLR_RESERVED16_SHIFT                                                                      (8U)
#define MCASP_EVTCTLR_RESERVED16_MASK                                                                       (0xffffff00U)

#define MCASP_EVTCTLR_RSTAFRM_SHIFT                                                                         (7U)
#define MCASP_EVTCTLR_RSTAFRM_MASK                                                                          (0x00000080U)
#define MCASP_EVTCTLR_RSTAFRM_DISABLE                                                                        (0U)
#define MCASP_EVTCTLR_RSTAFRM_ENABLE                                                                         (1U)

#define MCASP_EVTCTLR_RESERVED17_SHIFT                                                                      (6U)
#define MCASP_EVTCTLR_RESERVED17_MASK                                                                       (0x00000040U)

#define MCASP_EVTCTLR_RDATA_SHIFT                                                                           (5U)
#define MCASP_EVTCTLR_RDATA_MASK                                                                            (0x00000020U)
#define MCASP_EVTCTLR_RDATA_DISABLE                                                                          (0U)
#define MCASP_EVTCTLR_RDATA_ENABLE                                                                           (1U)

#define MCASP_EVTCTLR_RLAST_SHIFT                                                                           (4U)
#define MCASP_EVTCTLR_RLAST_MASK                                                                            (0x00000010U)
#define MCASP_EVTCTLR_RLAST_DISABLE                                                                          (0U)
#define MCASP_EVTCTLR_RLAST_ENABLE                                                                           (1U)

#define MCASP_EVTCTLR_RDMAERR_SHIFT                                                                         (3U)
#define MCASP_EVTCTLR_RDMAERR_MASK                                                                          (0x00000008U)
#define MCASP_EVTCTLR_RDMAERR_DISABLE                                                                        (0U)
#define MCASP_EVTCTLR_RDMAERR_ENABLE                                                                         (1U)

#define MCASP_EVTCTLR_RCKFAIL_SHIFT                                                                         (2U)
#define MCASP_EVTCTLR_RCKFAIL_MASK                                                                          (0x00000004U)
#define MCASP_EVTCTLR_RCKFAIL_DISABLE                                                                        (0U)
#define MCASP_EVTCTLR_RCKFAIL_ENABLE                                                                         (1U)

#define MCASP_EVTCTLR_RSYNCERR_SHIFT                                                                        (1U)
#define MCASP_EVTCTLR_RSYNCERR_MASK                                                                         (0x00000002U)
#define MCASP_EVTCTLR_RSYNCERR_DISABLE                                                                       (0U)
#define MCASP_EVTCTLR_RSYNCERR_ENABLE                                                                        (1U)

#define MCASP_EVTCTLR_ROVRN_SHIFT                                                                           (0U)
#define MCASP_EVTCTLR_ROVRN_MASK                                                                            (0x00000001U)
#define MCASP_EVTCTLR_ROVRN_DISABLE                                                                          (0U)
#define MCASP_EVTCTLR_ROVRN_ENABLE                                                                           (1U)

#define MCASP_RXSTAT_RESERVED18_SHIFT                                                                       (9U)
#define MCASP_RXSTAT_RESERVED18_MASK                                                                        (0xfffffe00U)

#define MCASP_RXSTAT_RERR_SHIFT                                                                             (8U)
#define MCASP_RXSTAT_RERR_MASK                                                                              (0x00000100U)
#define MCASP_RXSTAT_RERR_NOERROR                                                                            (0U)
#define MCASP_RXSTAT_RERR_ERROR                                                                              (1U)

#define MCASP_RXSTAT_RDMAERR_SHIFT                                                                          (7U)
#define MCASP_RXSTAT_RDMAERR_MASK                                                                           (0x00000080U)
#define MCASP_RXSTAT_RDMAERR_NOTOCCUR                                                                        (0U)
#define MCASP_RXSTAT_RDMAERR_OCCUR                                                                           (1U)

#define MCASP_RXSTAT_RSTAFRM_SHIFT                                                                          (6U)
#define MCASP_RXSTAT_RSTAFRM_MASK                                                                           (0x00000040U)
#define MCASP_RXSTAT_RSTAFRM_NOTOCCUR                                                                        (0U)
#define MCASP_RXSTAT_RSTAFRM_OCCUR                                                                           (1U)

#define MCASP_RXSTAT_RDATA_SHIFT                                                                            (5U)
#define MCASP_RXSTAT_RDATA_MASK                                                                             (0x00000020U)
#define MCASP_RXSTAT_RDATA_NOTOCCUR                                                                          (0U)
#define MCASP_RXSTAT_RDATA_OCCUR                                                                             (1U)

#define MCASP_RXSTAT_RLAST_SHIFT                                                                            (4U)
#define MCASP_RXSTAT_RLAST_MASK                                                                             (0x00000010U)
#define MCASP_RXSTAT_RLAST_NOTOCCUR                                                                          (0U)
#define MCASP_RXSTAT_RLAST_OCCUR                                                                             (1U)

#define MCASP_RXSTAT_RTDMSLOT_SHIFT                                                                         (3U)
#define MCASP_RXSTAT_RTDMSLOT_MASK                                                                          (0x00000008U)
#define MCASP_RXSTAT_RTDMSLOT_ODDSLOT                                                                        (0U)
#define MCASP_RXSTAT_RTDMSLOT_EVENSLOT                                                                       (1U)

#define MCASP_RXSTAT_RCKFAIL_SHIFT                                                                          (2U)
#define MCASP_RXSTAT_RCKFAIL_MASK                                                                           (0x00000004U)
#define MCASP_RXSTAT_RCKFAIL_NOTOCCUR                                                                        (0U)
#define MCASP_RXSTAT_RCKFAIL_OCCUR                                                                           (1U)

#define MCASP_RXSTAT_RSYNCERR_SHIFT                                                                         (1U)
#define MCASP_RXSTAT_RSYNCERR_MASK                                                                          (0x00000002U)
#define MCASP_RXSTAT_RSYNCERR_NOTOCCUR                                                                       (0U)
#define MCASP_RXSTAT_RSYNCERR_OCCUR                                                                          (1U)

#define MCASP_RXSTAT_ROVRN_SHIFT                                                                            (0U)
#define MCASP_RXSTAT_ROVRN_MASK                                                                             (0x00000001U)
#define MCASP_RXSTAT_ROVRN_NOTOCCUR                                                                          (0U)
#define MCASP_RXSTAT_ROVRN_OCCUR                                                                             (1U)

#define MCASP_RXTDMSLOT_RESERVED19_SHIFT                                                                    (10U)
#define MCASP_RXTDMSLOT_RESERVED19_MASK                                                                     (0xfffffc00U)

#define MCASP_RXTDMSLOT_RSLOTCNT_SHIFT                                                                      (0U)
#define MCASP_RXTDMSLOT_RSLOTCNT_MASK                                                                       (0x000003ffU)

#define MCASP_RXCLKCHK_RCNT_SHIFT                                                                           (24U)
#define MCASP_RXCLKCHK_RCNT_MASK                                                                            (0xff000000U)

#define MCASP_RXCLKCHK_RMAX_SHIFT                                                                           (16U)
#define MCASP_RXCLKCHK_RMAX_MASK                                                                            (0x00ff0000U)

#define MCASP_RXCLKCHK_RMIN_SHIFT                                                                           (8U)
#define MCASP_RXCLKCHK_RMIN_MASK                                                                            (0x0000ff00U)

#define MCASP_RXCLKCHK_RESERVED20_SHIFT                                                                     (4U)
#define MCASP_RXCLKCHK_RESERVED20_MASK                                                                      (0x000000f0U)

#define MCASP_RXCLKCHK_RPS_SHIFT                                                                            (0U)
#define MCASP_RXCLKCHK_RPS_MASK                                                                             (0x0000000fU)
#define MCASP_RXCLKCHK_RPS_DIVBY1                                                                            (0U)
#define MCASP_RXCLKCHK_RPS_DIVBY2                                                                            (1U)
#define MCASP_RXCLKCHK_RPS_DIVBY4                                                                            (2U)
#define MCASP_RXCLKCHK_RPS_DIVBY8                                                                            (3U)
#define MCASP_RXCLKCHK_RPS_DIVBY16                                                                           (4U)
#define MCASP_RXCLKCHK_RPS_DIVBY32                                                                           (5U)
#define MCASP_RXCLKCHK_RPS_DIVBY64                                                                           (6U)
#define MCASP_RXCLKCHK_RPS_DIVBY128                                                                          (7U)
#define MCASP_RXCLKCHK_RPS_DIVBY256                                                                          (8U)

#define MCASP_REVTCTL_RESERVED21_SHIFT                                                                      (1U)
#define MCASP_REVTCTL_RESERVED21_MASK                                                                       (0xfffffffeU)

#define MCASP_REVTCTL_RDATDMA_SHIFT                                                                         (0U)
#define MCASP_REVTCTL_RDATDMA_MASK                                                                          (0x00000001U)
#define MCASP_REVTCTL_RDATDMA_ENABLE                                                                         (0U)
#define MCASP_REVTCTL_RDATDMA_DISABLE                                                                        (1U)

#define MCASP_GBLCTLX_RESERVED22_SHIFT                                                                      (13U)
#define MCASP_GBLCTLX_RESERVED22_MASK                                                                       (0xffffe000U)

#define MCASP_GBLCTLX_XFRST_SHIFT                                                                           (12U)
#define MCASP_GBLCTLX_XFRST_MASK                                                                            (0x00001000U)
#define MCASP_GBLCTLX_XFRST_RESET                                                                            (0U)
#define MCASP_GBLCTLX_XFRST_ACTIVE                                                                           (1U)

#define MCASP_GBLCTLX_XSMRST_SHIFT                                                                          (11U)
#define MCASP_GBLCTLX_XSMRST_MASK                                                                           (0x00000800U)
#define MCASP_GBLCTLX_XSMRST_RESET                                                                           (0U)
#define MCASP_GBLCTLX_XSMRST_ACTIVE                                                                          (1U)

#define MCASP_GBLCTLX_XSRCLR_SHIFT                                                                          (10U)
#define MCASP_GBLCTLX_XSRCLR_MASK                                                                           (0x00000400U)
#define MCASP_GBLCTLX_XSRCLR_CLEAR                                                                           (0U)
#define MCASP_GBLCTLX_XSRCLR_ACTIVE                                                                          (1U)

#define MCASP_GBLCTLX_XHCLKRST_SHIFT                                                                        (9U)
#define MCASP_GBLCTLX_XHCLKRST_MASK                                                                         (0x00000200U)
#define MCASP_GBLCTLX_XHCLKRST_RESET                                                                         (0U)
#define MCASP_GBLCTLX_XHCLKRST_ACTIVE                                                                        (1U)

#define MCASP_GBLCTLX_XCLKRST_SHIFT                                                                         (8U)
#define MCASP_GBLCTLX_XCLKRST_MASK                                                                          (0x00000100U)
#define MCASP_GBLCTLX_XCLKRST_RESET                                                                          (0U)
#define MCASP_GBLCTLX_XCLKRST_ACTIVE                                                                         (1U)

#define MCASP_GBLCTLX_RESERVED23_SHIFT                                                                      (5U)
#define MCASP_GBLCTLX_RESERVED23_MASK                                                                       (0x000000e0U)

#define MCASP_GBLCTLX_RFRST_SHIFT                                                                           (4U)
#define MCASP_GBLCTLX_RFRST_MASK                                                                            (0x00000010U)
#define MCASP_GBLCTLX_RFRST_RESET                                                                            (0U)
#define MCASP_GBLCTLX_RFRST_ACTIVE                                                                           (1U)

#define MCASP_GBLCTLX_RSMRST_SHIFT                                                                          (3U)
#define MCASP_GBLCTLX_RSMRST_MASK                                                                           (0x00000008U)
#define MCASP_GBLCTLX_RSMRST_RESET                                                                           (0U)
#define MCASP_GBLCTLX_RSMRST_ACTIVE                                                                          (1U)

#define MCASP_GBLCTLX_RSRCLKR_SHIFT                                                                         (2U)
#define MCASP_GBLCTLX_RSRCLKR_MASK                                                                          (0x00000004U)
#define MCASP_GBLCTLX_RSRCLKR_CLEAR                                                                          (0U)
#define MCASP_GBLCTLX_RSRCLKR_ACTIVE                                                                         (1U)

#define MCASP_GBLCTLX_RHCLKRST_SHIFT                                                                        (1U)
#define MCASP_GBLCTLX_RHCLKRST_MASK                                                                         (0x00000002U)
#define MCASP_GBLCTLX_RHCLKRST_RESET                                                                         (0U)
#define MCASP_GBLCTLX_RHCLKRST_ACTIVE                                                                        (1U)

#define MCASP_GBLCTLX_RCLKRST_SHIFT                                                                         (0U)
#define MCASP_GBLCTLX_RCLKRST_MASK                                                                          (0x00000001U)
#define MCASP_GBLCTLX_RCLKRST_RESET                                                                          (0U)
#define MCASP_GBLCTLX_RCLKRST_ACTIVE                                                                         (1U)

#define MCASP_TXMASK_XMASK31_SHIFT                                                                          (31U)
#define MCASP_TXMASK_XMASK31_MASK                                                                           (0x80000000U)
#define MCASP_TXMASK_XMASK31_USEMASK                                                                         (0U)
#define MCASP_TXMASK_XMASK31_NOMASK                                                                          (1U)

#define MCASP_TXMASK_XMASK30_SHIFT                                                                          (30U)
#define MCASP_TXMASK_XMASK30_MASK                                                                           (0x40000000U)
#define MCASP_TXMASK_XMASK30_USEMASK                                                                         (0U)
#define MCASP_TXMASK_XMASK30_NOMASK                                                                          (1U)

#define MCASP_TXMASK_XMASK29_SHIFT                                                                          (29U)
#define MCASP_TXMASK_XMASK29_MASK                                                                           (0x20000000U)
#define MCASP_TXMASK_XMASK29_USEMASK                                                                         (0U)
#define MCASP_TXMASK_XMASK29_NOMASK                                                                          (1U)

#define MCASP_TXMASK_XMASK28_SHIFT                                                                          (28U)
#define MCASP_TXMASK_XMASK28_MASK                                                                           (0x10000000U)
#define MCASP_TXMASK_XMASK28_USEMASK                                                                         (0U)
#define MCASP_TXMASK_XMASK28_NOMASK                                                                          (1U)

#define MCASP_TXMASK_XMASK27_SHIFT                                                                          (27U)
#define MCASP_TXMASK_XMASK27_MASK                                                                           (0x08000000U)
#define MCASP_TXMASK_XMASK27_USEMASK                                                                         (0U)
#define MCASP_TXMASK_XMASK27_NOMASK                                                                          (1U)

#define MCASP_TXMASK_XMASK26_SHIFT                                                                          (26U)
#define MCASP_TXMASK_XMASK26_MASK                                                                           (0x04000000U)
#define MCASP_TXMASK_XMASK26_USEMASK                                                                         (0U)
#define MCASP_TXMASK_XMASK26_NOMASK                                                                          (1U)

#define MCASP_TXMASK_XMASK25_SHIFT                                                                          (25U)
#define MCASP_TXMASK_XMASK25_MASK                                                                           (0x02000000U)
#define MCASP_TXMASK_XMASK25_USEMASK                                                                         (0U)
#define MCASP_TXMASK_XMASK25_NOMASK                                                                          (1U)

#define MCASP_TXMASK_XMASK24_SHIFT                                                                          (24U)
#define MCASP_TXMASK_XMASK24_MASK                                                                           (0x01000000U)
#define MCASP_TXMASK_XMASK24_USEMASK                                                                         (0U)
#define MCASP_TXMASK_XMASK24_NOMASK                                                                          (1U)

#define MCASP_TXMASK_XMASK23_SHIFT                                                                          (23U)
#define MCASP_TXMASK_XMASK23_MASK                                                                           (0x00800000U)
#define MCASP_TXMASK_XMASK23_USEMASK                                                                         (0U)
#define MCASP_TXMASK_XMASK23_NOMASK                                                                          (1U)

#define MCASP_TXMASK_XMASK22_SHIFT                                                                          (22U)
#define MCASP_TXMASK_XMASK22_MASK                                                                           (0x00400000U)
#define MCASP_TXMASK_XMASK22_USEMASK                                                                         (0U)
#define MCASP_TXMASK_XMASK22_NOMASK                                                                          (1U)

#define MCASP_TXMASK_XMASK21_SHIFT                                                                          (21U)
#define MCASP_TXMASK_XMASK21_MASK                                                                           (0x00200000U)
#define MCASP_TXMASK_XMASK21_USEMASK                                                                         (0U)
#define MCASP_TXMASK_XMASK21_NOMASK                                                                          (1U)

#define MCASP_TXMASK_XMASK20_SHIFT                                                                          (20U)
#define MCASP_TXMASK_XMASK20_MASK                                                                           (0x00100000U)
#define MCASP_TXMASK_XMASK20_USEMASK                                                                         (0U)
#define MCASP_TXMASK_XMASK20_NOMASK                                                                          (1U)

#define MCASP_TXMASK_XMASK19_SHIFT                                                                          (19U)
#define MCASP_TXMASK_XMASK19_MASK                                                                           (0x00080000U)
#define MCASP_TXMASK_XMASK19_USEMASK                                                                         (0U)
#define MCASP_TXMASK_XMASK19_NOMASK                                                                          (1U)

#define MCASP_TXMASK_XMASK18_SHIFT                                                                          (18U)
#define MCASP_TXMASK_XMASK18_MASK                                                                           (0x00040000U)
#define MCASP_TXMASK_XMASK18_USEMASK                                                                         (0U)
#define MCASP_TXMASK_XMASK18_NOMASK                                                                          (1U)

#define MCASP_TXMASK_XMASK17_SHIFT                                                                          (17U)
#define MCASP_TXMASK_XMASK17_MASK                                                                           (0x00020000U)
#define MCASP_TXMASK_XMASK17_USEMASK                                                                         (0U)
#define MCASP_TXMASK_XMASK17_NOMASK                                                                          (1U)

#define MCASP_TXMASK_XMASK16_SHIFT                                                                          (16U)
#define MCASP_TXMASK_XMASK16_MASK                                                                           (0x00010000U)
#define MCASP_TXMASK_XMASK16_USEMASK                                                                         (0U)
#define MCASP_TXMASK_XMASK16_NOMASK                                                                          (1U)

#define MCASP_TXMASK_XMASK15_SHIFT                                                                          (15U)
#define MCASP_TXMASK_XMASK15_MASK                                                                           (0x00008000U)
#define MCASP_TXMASK_XMASK15_USEMASK                                                                         (0U)
#define MCASP_TXMASK_XMASK15_NOMASK                                                                          (1U)

#define MCASP_TXMASK_XMASK14_SHIFT                                                                          (14U)
#define MCASP_TXMASK_XMASK14_MASK                                                                           (0x00004000U)
#define MCASP_TXMASK_XMASK14_USEMASK                                                                         (0U)
#define MCASP_TXMASK_XMASK14_NOMASK                                                                          (1U)

#define MCASP_TXMASK_XMASK13_SHIFT                                                                          (13U)
#define MCASP_TXMASK_XMASK13_MASK                                                                           (0x00002000U)
#define MCASP_TXMASK_XMASK13_USEMASK                                                                         (0U)
#define MCASP_TXMASK_XMASK13_NOMASK                                                                          (1U)

#define MCASP_TXMASK_XMASK12_SHIFT                                                                          (12U)
#define MCASP_TXMASK_XMASK12_MASK                                                                           (0x00001000U)
#define MCASP_TXMASK_XMASK12_USEMASK                                                                         (0U)
#define MCASP_TXMASK_XMASK12_NOMASK                                                                          (1U)

#define MCASP_TXMASK_XMASK11_SHIFT                                                                          (11U)
#define MCASP_TXMASK_XMASK11_MASK                                                                           (0x00000800U)
#define MCASP_TXMASK_XMASK11_USEMASK                                                                         (0U)
#define MCASP_TXMASK_XMASK11_NOMASK                                                                          (1U)

#define MCASP_TXMASK_XMASK10_SHIFT                                                                          (10U)
#define MCASP_TXMASK_XMASK10_MASK                                                                           (0x00000400U)
#define MCASP_TXMASK_XMASK10_USEMASK                                                                         (0U)
#define MCASP_TXMASK_XMASK10_NOMASK                                                                          (1U)

#define MCASP_TXMASK_XMASK9_SHIFT                                                                           (9U)
#define MCASP_TXMASK_XMASK9_MASK                                                                            (0x00000200U)
#define MCASP_TXMASK_XMASK9_USEMASK                                                                          (0U)
#define MCASP_TXMASK_XMASK9_NOMASK                                                                           (1U)

#define MCASP_TXMASK_XMASK8_SHIFT                                                                           (8U)
#define MCASP_TXMASK_XMASK8_MASK                                                                            (0x00000100U)
#define MCASP_TXMASK_XMASK8_USEMASK                                                                          (0U)
#define MCASP_TXMASK_XMASK8_NOMASK                                                                           (1U)

#define MCASP_TXMASK_XMASK7_SHIFT                                                                           (7U)
#define MCASP_TXMASK_XMASK7_MASK                                                                            (0x00000080U)
#define MCASP_TXMASK_XMASK7_USEMASK                                                                          (0U)
#define MCASP_TXMASK_XMASK7_NOMASK                                                                           (1U)

#define MCASP_TXMASK_XMASK6_SHIFT                                                                           (6U)
#define MCASP_TXMASK_XMASK6_MASK                                                                            (0x00000040U)
#define MCASP_TXMASK_XMASK6_USEMASK                                                                          (0U)
#define MCASP_TXMASK_XMASK6_NOMASK                                                                           (1U)

#define MCASP_TXMASK_XMASK5_SHIFT                                                                           (5U)
#define MCASP_TXMASK_XMASK5_MASK                                                                            (0x00000020U)
#define MCASP_TXMASK_XMASK5_USEMASK                                                                          (0U)
#define MCASP_TXMASK_XMASK5_NOMASK                                                                           (1U)

#define MCASP_TXMASK_XMASK4_SHIFT                                                                           (4U)
#define MCASP_TXMASK_XMASK4_MASK                                                                            (0x00000010U)
#define MCASP_TXMASK_XMASK4_USEMASK                                                                          (0U)
#define MCASP_TXMASK_XMASK4_NOMASK                                                                           (1U)

#define MCASP_TXMASK_XMASK3_SHIFT                                                                           (3U)
#define MCASP_TXMASK_XMASK3_MASK                                                                            (0x00000008U)
#define MCASP_TXMASK_XMASK3_USEMASK                                                                          (0U)
#define MCASP_TXMASK_XMASK3_NOMASK                                                                           (1U)

#define MCASP_TXMASK_XMASK2_SHIFT                                                                           (2U)
#define MCASP_TXMASK_XMASK2_MASK                                                                            (0x00000004U)
#define MCASP_TXMASK_XMASK2_USEMASK                                                                          (0U)
#define MCASP_TXMASK_XMASK2_NOMASK                                                                           (1U)

#define MCASP_TXMASK_XMASK1_SHIFT                                                                           (1U)
#define MCASP_TXMASK_XMASK1_MASK                                                                            (0x00000002U)
#define MCASP_TXMASK_XMASK1_USEMASK                                                                          (0U)
#define MCASP_TXMASK_XMASK1_NOMASK                                                                           (1U)

#define MCASP_TXMASK_XMASK0_SHIFT                                                                           (0U)
#define MCASP_TXMASK_XMASK0_MASK                                                                            (0x00000001U)
#define MCASP_TXMASK_XMASK0_USEMASK                                                                          (0U)
#define MCASP_TXMASK_XMASK0_NOMASK                                                                           (1U)

#define MCASP_TXFMT_RESERVED24_SHIFT                                                                        (18U)
#define MCASP_TXFMT_RESERVED24_MASK                                                                         (0xfffc0000U)

#define MCASP_TXFMT_XDATDLY_SHIFT                                                                           (16U)
#define MCASP_TXFMT_XDATDLY_MASK                                                                            (0x00030000U)
#define MCASP_TXFMT_XDATDLY_0BIT                                                                             (0U)
#define MCASP_TXFMT_XDATDLY_1BIT                                                                             (1U)
#define MCASP_TXFMT_XDATDLY_2BIT                                                                             (2U)

#define MCASP_TXFMT_XRVRS_SHIFT                                                                             (15U)
#define MCASP_TXFMT_XRVRS_MASK                                                                              (0x00008000U)
#define MCASP_TXFMT_XRVRS_LSBFIRST                                                                           (0U)
#define MCASP_TXFMT_XRVRS_MSBFIRST                                                                           (1U)

#define MCASP_TXFMT_XPAD_SHIFT                                                                              (13U)
#define MCASP_TXFMT_XPAD_MASK                                                                               (0x00006000U)
#define MCASP_TXFMT_XPAD_ZERO                                                                                (0U)
#define MCASP_TXFMT_XPAD_ONE                                                                                 (1U)
#define MCASP_TXFMT_XPAD_XPBIT                                                                               (2U)

#define MCASP_TXFMT_XPBIT_SHIFT                                                                             (8U)
#define MCASP_TXFMT_XPBIT_MASK                                                                              (0x00001f00U)

#define MCASP_TXFMT_XSSZ_SHIFT                                                                              (4U)
#define MCASP_TXFMT_XSSZ_MASK                                                                               (0x000000f0U)
#define MCASP_TXFMT_XSSZ_RSV                                                                                 (0U)
#define MCASP_TXFMT_XSSZ_RSV1                                                                                (1U)
#define MCASP_TXFMT_XSSZ_RSV2                                                                                (2U)
#define MCASP_TXFMT_XSSZ_8BITS                                                                               (3U)
#define MCASP_TXFMT_XSSZ_RSV3                                                                                (4U)
#define MCASP_TXFMT_XSSZ_12BITS                                                                              (5U)
#define MCASP_TXFMT_XSSZ_RSV4                                                                                (6U)
#define MCASP_TXFMT_XSSZ_16BITS                                                                              (7U)
#define MCASP_TXFMT_XSSZ_RSV5                                                                                (8U)
#define MCASP_TXFMT_XSSZ_20BITS                                                                              (9U)
#define MCASP_TXFMT_XSSZ_RSV6                                                                                (10U)
#define MCASP_TXFMT_XSSZ_24BITS                                                                              (11U)
#define MCASP_TXFMT_XSSZ_RSV7                                                                                (12U)
#define MCASP_TXFMT_XSSZ_28BITS                                                                              (13U)
#define MCASP_TXFMT_XSSZ_RSV8                                                                                (14U)
#define MCASP_TXFMT_XSSZ_32BITS                                                                              (15U)

#define MCASP_TXFMT_XBUSEL_SHIFT                                                                            (3U)
#define MCASP_TXFMT_XBUSEL_MASK                                                                             (0x00000008U)
#define MCASP_TXFMT_XBUSEL_VBUSP                                                                             (0U)
#define MCASP_TXFMT_XBUSEL_VBUS                                                                              (1U)

#define MCASP_TXFMT_XROT_SHIFT                                                                              (0U)
#define MCASP_TXFMT_XROT_MASK                                                                               (0x00000007U)
#define MCASP_TXFMT_XROT_NONE                                                                                (0U)
#define MCASP_TXFMT_XROT_4BITS                                                                               (1U)
#define MCASP_TXFMT_XROT_8BITS                                                                               (2U)
#define MCASP_TXFMT_XROT_12BITS                                                                              (3U)
#define MCASP_TXFMT_XROT_16BITS                                                                              (4U)
#define MCASP_TXFMT_XROT_20BITS                                                                              (5U)
#define MCASP_TXFMT_XROT_24BITS                                                                              (6U)
#define MCASP_TXFMT_XROT_28BITS                                                                              (7U)

#define MCASP_TXFMCTL_RESERVED25_SHIFT                                                                      (16U)
#define MCASP_TXFMCTL_RESERVED25_MASK                                                                       (0xffff0000U)

#define MCASP_TXFMCTL_XMOD_SHIFT                                                                            (7U)
#define MCASP_TXFMCTL_XMOD_MASK                                                                             (0x0000ff80U)

#define MCASP_TXFMCTL_RESERVED26_SHIFT                                                                      (5U)
#define MCASP_TXFMCTL_RESERVED26_MASK                                                                       (0x00000060U)

#define MCASP_TXFMCTL_FXWID_SHIFT                                                                           (4U)
#define MCASP_TXFMCTL_FXWID_MASK                                                                            (0x00000010U)
#define MCASP_TXFMCTL_FXWID_BIT                                                                              (0U)
#define MCASP_TXFMCTL_FXWID_WORD                                                                             (1U)

#define MCASP_TXFMCTL_RESERVED27_SHIFT                                                                      (2U)
#define MCASP_TXFMCTL_RESERVED27_MASK                                                                       (0x0000000cU)

#define MCASP_TXFMCTL_FSXM_SHIFT                                                                            (1U)
#define MCASP_TXFMCTL_FSXM_MASK                                                                             (0x00000002U)
#define MCASP_TXFMCTL_FSXM_EXTERNAL                                                                          (0U)
#define MCASP_TXFMCTL_FSXM_INTERNAL                                                                          (1U)

#define MCASP_TXFMCTL_FSXP_SHIFT                                                                            (0U)
#define MCASP_TXFMCTL_FSXP_MASK                                                                             (0x00000001U)
#define MCASP_TXFMCTL_FSXP_RISINGEDGE                                                                        (0U)
#define MCASP_TXFMCTL_FSXP_FALLINGEDGE                                                                       (1U)

#define MCASP_ACLKXCTL_RESERVED28_SHIFT                                                                     (21U)
#define MCASP_ACLKXCTL_RESERVED28_MASK                                                                      (0xffe00000U)

#define MCASP_ACLKXCTL_BUSY_SHIFT                                                                           (20U)
#define MCASP_ACLKXCTL_BUSY_MASK                                                                            (0x00100000U)
#define MCASP_ACLKXCTL_BUSY_NOTBUSY                                                                          (0U)
#define MCASP_ACLKXCTL_BUSY_BUSY                                                                             (1U)

#define MCASP_ACLKXCTL_DIVBUSY_SHIFT                                                                        (19U)
#define MCASP_ACLKXCTL_DIVBUSY_MASK                                                                         (0x00080000U)
#define MCASP_ACLKXCTL_DIVBUSY_NOTBUSY                                                                       (0U)
#define MCASP_ACLKXCTL_DIVBUSY_BUSY                                                                          (1U)

#define MCASP_ACLKXCTL_ADJBUSY_SHIFT                                                                        (18U)
#define MCASP_ACLKXCTL_ADJBUSY_MASK                                                                         (0x00040000U)
#define MCASP_ACLKXCTL_ADJBUSY_NOTBUSY                                                                       (0U)
#define MCASP_ACLKXCTL_ADJBUSY_BUSY                                                                          (1U)

#define MCASP_ACLKXCTL_CLKXADJ_SHIFT                                                                        (16U)
#define MCASP_ACLKXCTL_CLKXADJ_MASK                                                                         (0x00030000U)
#define MCASP_ACLKXCTL_CLKXADJ_PLUSZERO                                                                      (0U)
#define MCASP_ACLKXCTL_CLKXADJ_MINUSONE                                                                      (1U)
#define MCASP_ACLKXCTL_CLKXADJ_PLUSONE                                                                       (2U)
#define MCASP_ACLKXCTL_CLKXADJ_PLUSZER0                                                                      (3U)

#define MCASP_ACLKXCTL_RESERVED29_SHIFT                                                                     (8U)
#define MCASP_ACLKXCTL_RESERVED29_MASK                                                                      (0x0000ff00U)

#define MCASP_ACLKXCTL_CLKXP_SHIFT                                                                          (7U)
#define MCASP_ACLKXCTL_CLKXP_MASK                                                                           (0x00000080U)
#define MCASP_ACLKXCTL_CLKXP_RISINGEDGE                                                                      (0U)
#define MCASP_ACLKXCTL_CLKXP_FALLINGEDGE                                                                     (1U)

#define MCASP_ACLKXCTL_ASYNC_SHIFT                                                                          (6U)
#define MCASP_ACLKXCTL_ASYNC_MASK                                                                           (0x00000040U)
#define MCASP_ACLKXCTL_ASYNC_SYNC                                                                            (0U)
#define MCASP_ACLKXCTL_ASYNC_ASYNC                                                                           (1U)

#define MCASP_ACLKXCTL_CLKXM_SHIFT                                                                          (5U)
#define MCASP_ACLKXCTL_CLKXM_MASK                                                                           (0x00000020U)
#define MCASP_ACLKXCTL_CLKXM_EXTERNAL                                                                        (0U)
#define MCASP_ACLKXCTL_CLKXM_INTERNAL                                                                        (1U)

#define MCASP_ACLKXCTL_CLKXDIV_SHIFT                                                                        (0U)
#define MCASP_ACLKXCTL_CLKXDIV_MASK                                                                         (0x0000001fU)

#define MCASP_AHCLKXCTL_RESERVED30_SHIFT                                                                    (21U)
#define MCASP_AHCLKXCTL_RESERVED30_MASK                                                                     (0xffe00000U)

#define MCASP_AHCLKXCTL_BUSY_SHIFT                                                                          (20U)
#define MCASP_AHCLKXCTL_BUSY_MASK                                                                           (0x00100000U)
#define MCASP_AHCLKXCTL_BUSY_NOTBUSY                                                                         (0U)
#define MCASP_AHCLKXCTL_BUSY_BUSY                                                                            (1U)

#define MCASP_AHCLKXCTL_DIVBUSY_SHIFT                                                                       (19U)
#define MCASP_AHCLKXCTL_DIVBUSY_MASK                                                                        (0x00080000U)
#define MCASP_AHCLKXCTL_DIVBUSY_NOTBUSY                                                                      (0U)
#define MCASP_AHCLKXCTL_DIVBUSY_BUSY                                                                         (1U)

#define MCASP_AHCLKXCTL_ADJBUSY_SHIFT                                                                       (18U)
#define MCASP_AHCLKXCTL_ADJBUSY_MASK                                                                        (0x00040000U)
#define MCASP_AHCLKXCTL_ADJBUSY_NOTBUSY                                                                      (0U)
#define MCASP_AHCLKXCTL_ADJBUSY_BUSY                                                                         (1U)

#define MCASP_AHCLKXCTL_HCLKXADJ_SHIFT                                                                      (16U)
#define MCASP_AHCLKXCTL_HCLKXADJ_MASK                                                                       (0x00030000U)
#define MCASP_AHCLKXCTL_HCLKXADJ_PLUSZERO                                                                    (0U)
#define MCASP_AHCLKXCTL_HCLKXADJ_MINUSONE                                                                    (1U)
#define MCASP_AHCLKXCTL_HCLKXADJ_PLUSONE                                                                     (2U)
#define MCASP_AHCLKXCTL_HCLKXADJ_PLUSZER0                                                                    (3U)

#define MCASP_AHCLKXCTL_HCLKXM_SHIFT                                                                        (15U)
#define MCASP_AHCLKXCTL_HCLKXM_MASK                                                                         (0x00008000U)
#define MCASP_AHCLKXCTL_HCLKXM_EXTERNAL                                                                      (0U)
#define MCASP_AHCLKXCTL_HCLKXM_INTERNAL                                                                      (1U)

#define MCASP_AHCLKXCTL_HCLKXP_SHIFT                                                                        (14U)
#define MCASP_AHCLKXCTL_HCLKXP_MASK                                                                         (0x00004000U)
#define MCASP_AHCLKXCTL_HCLKXP_NOTINVERTED                                                                   (0U)
#define MCASP_AHCLKXCTL_HCLKXP_INVERTED                                                                      (1U)

#define MCASP_AHCLKXCTL_RESERVED31_SHIFT                                                                    (12U)
#define MCASP_AHCLKXCTL_RESERVED31_MASK                                                                     (0x00003000U)

#define MCASP_AHCLKXCTL_HCLKXDIV_SHIFT                                                                      (0U)
#define MCASP_AHCLKXCTL_HCLKXDIV_MASK                                                                       (0x00000fffU)

#define MCASP_TXTDM_XTDMS31_SHIFT                                                                           (31U)
#define MCASP_TXTDM_XTDMS31_MASK                                                                            (0x80000000U)
#define MCASP_TXTDM_XTDMS31_INACTIVE                                                                         (0U)
#define MCASP_TXTDM_XTDMS31_ACTIVE                                                                           (1U)

#define MCASP_TXTDM_XTDMS30_SHIFT                                                                           (30U)
#define MCASP_TXTDM_XTDMS30_MASK                                                                            (0x40000000U)
#define MCASP_TXTDM_XTDMS30_INACTIVE                                                                         (0U)
#define MCASP_TXTDM_XTDMS30_ACTIVE                                                                           (1U)

#define MCASP_TXTDM_XTDMS29_SHIFT                                                                           (29U)
#define MCASP_TXTDM_XTDMS29_MASK                                                                            (0x20000000U)
#define MCASP_TXTDM_XTDMS29_INACTIVE                                                                         (0U)
#define MCASP_TXTDM_XTDMS29_ACTIVE                                                                           (1U)

#define MCASP_TXTDM_XTDMS28_SHIFT                                                                           (28U)
#define MCASP_TXTDM_XTDMS28_MASK                                                                            (0x10000000U)
#define MCASP_TXTDM_XTDMS28_INACTIVE                                                                         (0U)
#define MCASP_TXTDM_XTDMS28_ACTIVE                                                                           (1U)

#define MCASP_TXTDM_XTDMS27_SHIFT                                                                           (27U)
#define MCASP_TXTDM_XTDMS27_MASK                                                                            (0x08000000U)
#define MCASP_TXTDM_XTDMS27_INACTIVE                                                                         (0U)
#define MCASP_TXTDM_XTDMS27_ACTIVE                                                                           (1U)

#define MCASP_TXTDM_XTDMS26_SHIFT                                                                           (26U)
#define MCASP_TXTDM_XTDMS26_MASK                                                                            (0x04000000U)
#define MCASP_TXTDM_XTDMS26_INACTIVE                                                                         (0U)
#define MCASP_TXTDM_XTDMS26_ACTIVE                                                                           (1U)

#define MCASP_TXTDM_XTDMS25_SHIFT                                                                           (25U)
#define MCASP_TXTDM_XTDMS25_MASK                                                                            (0x02000000U)
#define MCASP_TXTDM_XTDMS25_INACTIVE                                                                         (0U)
#define MCASP_TXTDM_XTDMS25_ACTIVE                                                                           (1U)

#define MCASP_TXTDM_XTDMS24_SHIFT                                                                           (24U)
#define MCASP_TXTDM_XTDMS24_MASK                                                                            (0x01000000U)
#define MCASP_TXTDM_XTDMS24_INACTIVE                                                                         (0U)
#define MCASP_TXTDM_XTDMS24_ACTIVE                                                                           (1U)

#define MCASP_TXTDM_XTDMS23_SHIFT                                                                           (23U)
#define MCASP_TXTDM_XTDMS23_MASK                                                                            (0x00800000U)
#define MCASP_TXTDM_XTDMS23_INACTIVE                                                                         (0U)
#define MCASP_TXTDM_XTDMS23_ACTIVE                                                                           (1U)

#define MCASP_TXTDM_XTDMS22_SHIFT                                                                           (22U)
#define MCASP_TXTDM_XTDMS22_MASK                                                                            (0x00400000U)
#define MCASP_TXTDM_XTDMS22_INACTIVE                                                                         (0U)
#define MCASP_TXTDM_XTDMS22_ACTIVE                                                                           (1U)

#define MCASP_TXTDM_XTDMS21_SHIFT                                                                           (21U)
#define MCASP_TXTDM_XTDMS21_MASK                                                                            (0x00200000U)
#define MCASP_TXTDM_XTDMS21_INACTIVE                                                                         (0U)
#define MCASP_TXTDM_XTDMS21_ACTIVE                                                                           (1U)

#define MCASP_TXTDM_XTDMS20_SHIFT                                                                           (20U)
#define MCASP_TXTDM_XTDMS20_MASK                                                                            (0x00100000U)
#define MCASP_TXTDM_XTDMS20_INACTIVE                                                                         (0U)
#define MCASP_TXTDM_XTDMS20_ACTIVE                                                                           (1U)

#define MCASP_TXTDM_XTDMS19_SHIFT                                                                           (19U)
#define MCASP_TXTDM_XTDMS19_MASK                                                                            (0x00080000U)
#define MCASP_TXTDM_XTDMS19_INACTIVE                                                                         (0U)
#define MCASP_TXTDM_XTDMS19_ACTIVE                                                                           (1U)

#define MCASP_TXTDM_XTDMS18_SHIFT                                                                           (18U)
#define MCASP_TXTDM_XTDMS18_MASK                                                                            (0x00040000U)
#define MCASP_TXTDM_XTDMS18_INACTIVE                                                                         (0U)
#define MCASP_TXTDM_XTDMS18_ACTIVE                                                                           (1U)

#define MCASP_TXTDM_XTDMS17_SHIFT                                                                           (17U)
#define MCASP_TXTDM_XTDMS17_MASK                                                                            (0x00020000U)
#define MCASP_TXTDM_XTDMS17_INACTIVE                                                                         (0U)
#define MCASP_TXTDM_XTDMS17_ACTIVE                                                                           (1U)

#define MCASP_TXTDM_XTDMS16_SHIFT                                                                           (16U)
#define MCASP_TXTDM_XTDMS16_MASK                                                                            (0x00010000U)
#define MCASP_TXTDM_XTDMS16_INACTIVE                                                                         (0U)
#define MCASP_TXTDM_XTDMS16_ACTIVE                                                                           (1U)

#define MCASP_TXTDM_XTDMS15_SHIFT                                                                           (15U)
#define MCASP_TXTDM_XTDMS15_MASK                                                                            (0x00008000U)
#define MCASP_TXTDM_XTDMS15_INACTIVE                                                                         (0U)
#define MCASP_TXTDM_XTDMS15_ACTIVE                                                                           (1U)

#define MCASP_TXTDM_XTDMS14_SHIFT                                                                           (14U)
#define MCASP_TXTDM_XTDMS14_MASK                                                                            (0x00004000U)
#define MCASP_TXTDM_XTDMS14_INACTIVE                                                                         (0U)
#define MCASP_TXTDM_XTDMS14_ACTIVE                                                                           (1U)

#define MCASP_TXTDM_XTDMS13_SHIFT                                                                           (13U)
#define MCASP_TXTDM_XTDMS13_MASK                                                                            (0x00002000U)
#define MCASP_TXTDM_XTDMS13_INACTIVE                                                                         (0U)
#define MCASP_TXTDM_XTDMS13_ACTIVE                                                                           (1U)

#define MCASP_TXTDM_XTDMS12_SHIFT                                                                           (12U)
#define MCASP_TXTDM_XTDMS12_MASK                                                                            (0x00001000U)
#define MCASP_TXTDM_XTDMS12_INACTIVE                                                                         (0U)
#define MCASP_TXTDM_XTDMS12_ACTIVE                                                                           (1U)

#define MCASP_TXTDM_XTDMS11_SHIFT                                                                           (11U)
#define MCASP_TXTDM_XTDMS11_MASK                                                                            (0x00000800U)
#define MCASP_TXTDM_XTDMS11_INACTIVE                                                                         (0U)
#define MCASP_TXTDM_XTDMS11_ACTIVE                                                                           (1U)

#define MCASP_TXTDM_XTDMS10_SHIFT                                                                           (10U)
#define MCASP_TXTDM_XTDMS10_MASK                                                                            (0x00000400U)
#define MCASP_TXTDM_XTDMS10_INACTIVE                                                                         (0U)
#define MCASP_TXTDM_XTDMS10_ACTIVE                                                                           (1U)

#define MCASP_TXTDM_XTDMS9_SHIFT                                                                            (9U)
#define MCASP_TXTDM_XTDMS9_MASK                                                                             (0x00000200U)
#define MCASP_TXTDM_XTDMS9_INACTIVE                                                                          (0U)
#define MCASP_TXTDM_XTDMS9_ACTIVE                                                                            (1U)

#define MCASP_TXTDM_XTDMS8_SHIFT                                                                            (8U)
#define MCASP_TXTDM_XTDMS8_MASK                                                                             (0x00000100U)
#define MCASP_TXTDM_XTDMS8_INACTIVE                                                                          (0U)
#define MCASP_TXTDM_XTDMS8_ACTIVE                                                                            (1U)

#define MCASP_TXTDM_XTDMS7_SHIFT                                                                            (7U)
#define MCASP_TXTDM_XTDMS7_MASK                                                                             (0x00000080U)
#define MCASP_TXTDM_XTDMS7_INACTIVE                                                                          (0U)
#define MCASP_TXTDM_XTDMS7_ACTIVE                                                                            (1U)

#define MCASP_TXTDM_XTDMS6_SHIFT                                                                            (6U)
#define MCASP_TXTDM_XTDMS6_MASK                                                                             (0x00000040U)
#define MCASP_TXTDM_XTDMS6_INACTIVE                                                                          (0U)
#define MCASP_TXTDM_XTDMS6_ACTIVE                                                                            (1U)

#define MCASP_TXTDM_XTDMS5_SHIFT                                                                            (5U)
#define MCASP_TXTDM_XTDMS5_MASK                                                                             (0x00000020U)
#define MCASP_TXTDM_XTDMS5_INACTIVE                                                                          (0U)
#define MCASP_TXTDM_XTDMS5_ACTIVE                                                                            (1U)

#define MCASP_TXTDM_XTDMS4_SHIFT                                                                            (4U)
#define MCASP_TXTDM_XTDMS4_MASK                                                                             (0x00000010U)
#define MCASP_TXTDM_XTDMS4_INACTIVE                                                                          (0U)
#define MCASP_TXTDM_XTDMS4_ACTIVE                                                                            (1U)

#define MCASP_TXTDM_XTDMS3_SHIFT                                                                            (3U)
#define MCASP_TXTDM_XTDMS3_MASK                                                                             (0x00000008U)
#define MCASP_TXTDM_XTDMS3_INACTIVE                                                                          (0U)
#define MCASP_TXTDM_XTDMS3_ACTIVE                                                                            (1U)

#define MCASP_TXTDM_XTDMS2_SHIFT                                                                            (2U)
#define MCASP_TXTDM_XTDMS2_MASK                                                                             (0x00000004U)
#define MCASP_TXTDM_XTDMS2_INACTIVE                                                                          (0U)
#define MCASP_TXTDM_XTDMS2_ACTIVE                                                                            (1U)

#define MCASP_TXTDM_XTDMS1_SHIFT                                                                            (1U)
#define MCASP_TXTDM_XTDMS1_MASK                                                                             (0x00000002U)
#define MCASP_TXTDM_XTDMS1_INACTIVE                                                                          (0U)
#define MCASP_TXTDM_XTDMS1_ACTIVE                                                                            (1U)

#define MCASP_TXTDM_XTDMS0_SHIFT                                                                            (0U)
#define MCASP_TXTDM_XTDMS0_MASK                                                                             (0x00000001U)
#define MCASP_TXTDM_XTDMS0_INACTIVE                                                                          (0U)
#define MCASP_TXTDM_XTDMS0_ACTIVE                                                                            (1U)

#define MCASP_EVTCTLX_RESERVED32_SHIFT                                                                      (8U)
#define MCASP_EVTCTLX_RESERVED32_MASK                                                                       (0xffffff00U)

#define MCASP_EVTCTLX_XSTAFRM_SHIFT                                                                         (7U)
#define MCASP_EVTCTLX_XSTAFRM_MASK                                                                          (0x00000080U)
#define MCASP_EVTCTLX_XSTAFRM_DISABLE                                                                        (0U)
#define MCASP_EVTCTLX_XSTAFRM_ENABLE                                                                         (1U)

#define MCASP_EVTCTLX_RESERVED33_SHIFT                                                                      (6U)
#define MCASP_EVTCTLX_RESERVED33_MASK                                                                       (0x00000040U)

#define MCASP_EVTCTLX_XDATA_SHIFT                                                                           (5U)
#define MCASP_EVTCTLX_XDATA_MASK                                                                            (0x00000020U)
#define MCASP_EVTCTLX_XDATA_DISABLE                                                                          (0U)
#define MCASP_EVTCTLX_XDATA_ENABLE                                                                           (1U)

#define MCASP_EVTCTLX_XLAST_SHIFT                                                                           (4U)
#define MCASP_EVTCTLX_XLAST_MASK                                                                            (0x00000010U)
#define MCASP_EVTCTLX_XLAST_DISABLE                                                                          (0U)
#define MCASP_EVTCTLX_XLAST_ENABLE                                                                           (1U)

#define MCASP_EVTCTLX_XDMAERR_SHIFT                                                                         (3U)
#define MCASP_EVTCTLX_XDMAERR_MASK                                                                          (0x00000008U)
#define MCASP_EVTCTLX_XDMAERR_DISABLE                                                                        (0U)
#define MCASP_EVTCTLX_XDMAERR_ENABLE                                                                         (1U)

#define MCASP_EVTCTLX_XCKFAIL_SHIFT                                                                         (2U)
#define MCASP_EVTCTLX_XCKFAIL_MASK                                                                          (0x00000004U)
#define MCASP_EVTCTLX_XCKFAIL_DISABLE                                                                        (0U)
#define MCASP_EVTCTLX_XCKFAIL_ENABLE                                                                         (1U)

#define MCASP_EVTCTLX_XSYNCERR_SHIFT                                                                        (1U)
#define MCASP_EVTCTLX_XSYNCERR_MASK                                                                         (0x00000002U)
#define MCASP_EVTCTLX_XSYNCERR_DISABLE                                                                       (0U)
#define MCASP_EVTCTLX_XSYNCERR_ENABLE                                                                        (1U)

#define MCASP_EVTCTLX_XUNDRN_SHIFT                                                                          (0U)
#define MCASP_EVTCTLX_XUNDRN_MASK                                                                           (0x00000001U)
#define MCASP_EVTCTLX_XUNDRN_DISABLE                                                                         (0U)
#define MCASP_EVTCTLX_XUNDRN_ENABLE                                                                          (1U)

#define MCASP_TXSTAT_RESERVED34_SHIFT                                                                       (9U)
#define MCASP_TXSTAT_RESERVED34_MASK                                                                        (0xfffffe00U)

#define MCASP_TXSTAT_XERR_SHIFT                                                                             (8U)
#define MCASP_TXSTAT_XERR_MASK                                                                              (0x00000100U)
#define MCASP_TXSTAT_XERR_NOERROR                                                                            (0U)
#define MCASP_TXSTAT_XERR_ERROR                                                                              (1U)

#define MCASP_TXSTAT_XDMAERR_SHIFT                                                                          (7U)
#define MCASP_TXSTAT_XDMAERR_MASK                                                                           (0x00000080U)
#define MCASP_TXSTAT_XDMAERR_NOTOCCUR                                                                        (0U)
#define MCASP_TXSTAT_XDMAERR_OCCUR                                                                           (1U)

#define MCASP_TXSTAT_XSTAFRM_SHIFT                                                                          (6U)
#define MCASP_TXSTAT_XSTAFRM_MASK                                                                           (0x00000040U)
#define MCASP_TXSTAT_XSTAFRM_NOTOCCUR                                                                        (0U)
#define MCASP_TXSTAT_XSTAFRM_OCCUR                                                                           (1U)

#define MCASP_TXSTAT_XDATA_SHIFT                                                                            (5U)
#define MCASP_TXSTAT_XDATA_MASK                                                                             (0x00000020U)
#define MCASP_TXSTAT_XDATA_NOTOCCUR                                                                          (0U)
#define MCASP_TXSTAT_XDATA_OCCUR                                                                             (1U)

#define MCASP_TXSTAT_XLAST_SHIFT                                                                            (4U)
#define MCASP_TXSTAT_XLAST_MASK                                                                             (0x00000010U)
#define MCASP_TXSTAT_XLAST_NOTOCCUR                                                                          (0U)
#define MCASP_TXSTAT_XLAST_OCCUR                                                                             (1U)

#define MCASP_TXSTAT_XTDMSLOT_SHIFT                                                                         (3U)
#define MCASP_TXSTAT_XTDMSLOT_MASK                                                                          (0x00000008U)
#define MCASP_TXSTAT_XTDMSLOT_ODDSLOT                                                                        (0U)
#define MCASP_TXSTAT_XTDMSLOT_EVENSLOT                                                                       (1U)

#define MCASP_TXSTAT_XCKFAIL_SHIFT                                                                          (2U)
#define MCASP_TXSTAT_XCKFAIL_MASK                                                                           (0x00000004U)
#define MCASP_TXSTAT_XCKFAIL_NOTOCCUR                                                                        (0U)
#define MCASP_TXSTAT_XCKFAIL_OCCUR                                                                           (1U)

#define MCASP_TXSTAT_XSYNCERR_SHIFT                                                                         (1U)
#define MCASP_TXSTAT_XSYNCERR_MASK                                                                          (0x00000002U)
#define MCASP_TXSTAT_XSYNCERR_NOTOCCUR                                                                       (0U)
#define MCASP_TXSTAT_XSYNCERR_OCCUR                                                                          (1U)

#define MCASP_TXSTAT_XUNDRN_SHIFT                                                                           (0U)
#define MCASP_TXSTAT_XUNDRN_MASK                                                                            (0x00000001U)
#define MCASP_TXSTAT_XUNDRN_NOTOCCUR                                                                         (0U)
#define MCASP_TXSTAT_XUNDRN_OCCUR                                                                            (1U)

#define MCASP_TXTDMSLOT_RESERVED35_SHIFT                                                                    (10U)
#define MCASP_TXTDMSLOT_RESERVED35_MASK                                                                     (0xfffffc00U)

#define MCASP_TXTDMSLOT_XSLOTCNT_SHIFT                                                                      (0U)
#define MCASP_TXTDMSLOT_XSLOTCNT_MASK                                                                       (0x000003ffU)

#define MCASP_TXCLKCHK_XCNT_SHIFT                                                                           (24U)
#define MCASP_TXCLKCHK_XCNT_MASK                                                                            (0xff000000U)

#define MCASP_TXCLKCHK_XMAX_SHIFT                                                                           (16U)
#define MCASP_TXCLKCHK_XMAX_MASK                                                                            (0x00ff0000U)

#define MCASP_TXCLKCHK_XMIN_SHIFT                                                                           (8U)
#define MCASP_TXCLKCHK_XMIN_MASK                                                                            (0x0000ff00U)

#define MCASP_TXCLKCHK_RESV_SHIFT                                                                           (7U)
#define MCASP_TXCLKCHK_RESV_MASK                                                                            (0x00000080U)

#define MCASP_TXCLKCHK_RESERVED36_SHIFT                                                                     (4U)
#define MCASP_TXCLKCHK_RESERVED36_MASK                                                                      (0x00000070U)

#define MCASP_TXCLKCHK_XPS_SHIFT                                                                            (0U)
#define MCASP_TXCLKCHK_XPS_MASK                                                                             (0x0000000fU)
#define MCASP_TXCLKCHK_XPS_DIVBY1                                                                            (0U)
#define MCASP_TXCLKCHK_XPS_DIVBY2                                                                            (1U)
#define MCASP_TXCLKCHK_XPS_DIVBY4                                                                            (2U)
#define MCASP_TXCLKCHK_XPS_DIVBY8                                                                            (3U)
#define MCASP_TXCLKCHK_XPS_DIVBY16                                                                           (4U)
#define MCASP_TXCLKCHK_XPS_DIVBY32                                                                           (5U)
#define MCASP_TXCLKCHK_XPS_DIVBY64                                                                           (6U)
#define MCASP_TXCLKCHK_XPS_DIVBY128                                                                          (7U)
#define MCASP_TXCLKCHK_XPS_DIVBY256                                                                          (8U)

#define MCASP_XEVTCTL_RESERVED37_SHIFT                                                                      (1U)
#define MCASP_XEVTCTL_RESERVED37_MASK                                                                       (0xfffffffeU)

#define MCASP_XEVTCTL_XDATDMA_SHIFT                                                                         (0U)
#define MCASP_XEVTCTL_XDATDMA_MASK                                                                          (0x00000001U)
#define MCASP_XEVTCTL_XDATDMA_ENABLE                                                                         (0U)
#define MCASP_XEVTCTL_XDATDMA_DISABLE                                                                        (1U)

#define MCASP_CLKADJEN_RESERVED38_SHIFT                                                                     (1U)
#define MCASP_CLKADJEN_RESERVED38_MASK                                                                      (0xfffffffeU)

#define MCASP_CLKADJEN_ENABLE_SHIFT                                                                         (0U)
#define MCASP_CLKADJEN_ENABLE_MASK                                                                          (0x00000001U)
#define MCASP_CLKADJEN_ENABLE_DISABLE                                                                        (0U)
#define MCASP_CLKADJEN_ENABLE_ENABLE                                                                         (1U)

#define MCASP_DITCSRA0_DITCSRA0_SHIFT                                                                       (0U)
#define MCASP_DITCSRA0_DITCSRA0_MASK                                                                        (0xffffffffU)

#define MCASP_DITCSRA1_DITCSRA1_SHIFT                                                                       (0U)
#define MCASP_DITCSRA1_DITCSRA1_MASK                                                                        (0xffffffffU)

#define MCASP_DITCSRA2_DITCSRA2_SHIFT                                                                       (0U)
#define MCASP_DITCSRA2_DITCSRA2_MASK                                                                        (0xffffffffU)

#define MCASP_DITCSRA3_DITCSRA3_SHIFT                                                                       (0U)
#define MCASP_DITCSRA3_DITCSRA3_MASK                                                                        (0xffffffffU)

#define MCASP_DITCSRA4_DITCSRA4_SHIFT                                                                       (0U)
#define MCASP_DITCSRA4_DITCSRA4_MASK                                                                        (0xffffffffU)

#define MCASP_DITCSRA5_DITCSRA5_SHIFT                                                                       (0U)
#define MCASP_DITCSRA5_DITCSRA5_MASK                                                                        (0xffffffffU)

#define MCASP_DITCSRB0_DITCSRB0_SHIFT                                                                       (0U)
#define MCASP_DITCSRB0_DITCSRB0_MASK                                                                        (0xffffffffU)

#define MCASP_DITCSRB1_DITCSRB1_SHIFT                                                                       (0U)
#define MCASP_DITCSRB1_DITCSRB1_MASK                                                                        (0xffffffffU)

#define MCASP_DITCSRB2_DITCSRB2_SHIFT                                                                       (0U)
#define MCASP_DITCSRB2_DITCSRB2_MASK                                                                        (0xffffffffU)

#define MCASP_DITCSRB3_DITCSRB3_SHIFT                                                                       (0U)
#define MCASP_DITCSRB3_DITCSRB3_MASK                                                                        (0xffffffffU)

#define MCASP_DITCSRB4_DITCSRB4_SHIFT                                                                       (0U)
#define MCASP_DITCSRB4_DITCSRB4_MASK                                                                        (0xffffffffU)

#define MCASP_DITCSRB5_DITCSRB5_SHIFT                                                                       (0U)
#define MCASP_DITCSRB5_DITCSRB5_MASK                                                                        (0xffffffffU)

#define MCASP_DITUDRA0_DITUDRA0_SHIFT                                                                       (0U)
#define MCASP_DITUDRA0_DITUDRA0_MASK                                                                        (0xffffffffU)

#define MCASP_DITUDRA1_DITUDRA1_SHIFT                                                                       (0U)
#define MCASP_DITUDRA1_DITUDRA1_MASK                                                                        (0xffffffffU)

#define MCASP_DITUDRA2_DITUDRA2_SHIFT                                                                       (0U)
#define MCASP_DITUDRA2_DITUDRA2_MASK                                                                        (0xffffffffU)

#define MCASP_DITUDRA3_DITUDRA3_SHIFT                                                                       (0U)
#define MCASP_DITUDRA3_DITUDRA3_MASK                                                                        (0xffffffffU)

#define MCASP_DITUDRA4_DITUDRA4_SHIFT                                                                       (0U)
#define MCASP_DITUDRA4_DITUDRA4_MASK                                                                        (0xffffffffU)

#define MCASP_DITUDRA5_DITUDRA5_SHIFT                                                                       (0U)
#define MCASP_DITUDRA5_DITUDRA5_MASK                                                                        (0xffffffffU)

#define MCASP_DITUDRB0_DITUDRB0_SHIFT                                                                       (0U)
#define MCASP_DITUDRB0_DITUDRB0_MASK                                                                        (0xffffffffU)

#define MCASP_DITUDRB1_DITUDRB1_SHIFT                                                                       (0U)
#define MCASP_DITUDRB1_DITUDRB1_MASK                                                                        (0xffffffffU)

#define MCASP_DITUDRB2_DITUDRB2_SHIFT                                                                       (0U)
#define MCASP_DITUDRB2_DITUDRB2_MASK                                                                        (0xffffffffU)

#define MCASP_DITUDRB3_DITUDRB3_SHIFT                                                                       (0U)
#define MCASP_DITUDRB3_DITUDRB3_MASK                                                                        (0xffffffffU)

#define MCASP_DITUDRB4_DITUDRB4_SHIFT                                                                       (0U)
#define MCASP_DITUDRB4_DITUDRB4_MASK                                                                        (0xffffffffU)

#define MCASP_DITUDRB5_DITUDRB5_SHIFT                                                                       (0U)
#define MCASP_DITUDRB5_DITUDRB5_MASK                                                                        (0xffffffffU)

#define MCASP_XRSRCTL0_RESERVED39_SHIFT                                                                     (6U)
#define MCASP_XRSRCTL0_RESERVED39_MASK                                                                      (0xffffffc0U)

#define MCASP_XRSRCTL0_RRDY_SHIFT                                                                           (5U)
#define MCASP_XRSRCTL0_RRDY_MASK                                                                            (0x00000020U)
#define MCASP_XRSRCTL0_RRDY_EMPTY                                                                            (0U)
#define MCASP_XRSRCTL0_RRDY_DATA                                                                             (1U)

#define MCASP_XRSRCTL0_XRDY_SHIFT                                                                           (4U)
#define MCASP_XRSRCTL0_XRDY_MASK                                                                            (0x00000010U)
#define MCASP_XRSRCTL0_XRDY_DATA                                                                             (0U)
#define MCASP_XRSRCTL0_XRDY_EMPTY                                                                            (1U)

#define MCASP_XRSRCTL0_DISMOD_SHIFT                                                                         (2U)
#define MCASP_XRSRCTL0_DISMOD_MASK                                                                          (0x0000000cU)
#define MCASP_XRSRCTL0_DISMOD_TRI                                                                            (0U)
#define MCASP_XRSRCTL0_DISMOD_RSV                                                                            (1U)
#define MCASP_XRSRCTL0_DISMOD_DRV0                                                                           (2U)
#define MCASP_XRSRCTL0_DISMOD_DRV1                                                                           (3U)

#define MCASP_XRSRCTL0_SRMOD_SHIFT                                                                          (0U)
#define MCASP_XRSRCTL0_SRMOD_MASK                                                                           (0x00000003U)
#define MCASP_XRSRCTL0_SRMOD_INACTIVE                                                                        (0U)
#define MCASP_XRSRCTL0_SRMOD_XMT                                                                             (1U)
#define MCASP_XRSRCTL0_SRMOD_RCV                                                                             (2U)

#define MCASP_XRSRCTL1_RESERVED40_SHIFT                                                                     (6U)
#define MCASP_XRSRCTL1_RESERVED40_MASK                                                                      (0xffffffc0U)

#define MCASP_XRSRCTL1_RRDY_SHIFT                                                                           (5U)
#define MCASP_XRSRCTL1_RRDY_MASK                                                                            (0x00000020U)
#define MCASP_XRSRCTL1_RRDY_EMPTY                                                                            (0U)
#define MCASP_XRSRCTL1_RRDY_DATA                                                                             (1U)

#define MCASP_XRSRCTL1_XRDY_SHIFT                                                                           (4U)
#define MCASP_XRSRCTL1_XRDY_MASK                                                                            (0x00000010U)
#define MCASP_XRSRCTL1_XRDY_DATA                                                                             (0U)
#define MCASP_XRSRCTL1_XRDY_EMPTY                                                                            (1U)

#define MCASP_XRSRCTL1_DISMOD_SHIFT                                                                         (2U)
#define MCASP_XRSRCTL1_DISMOD_MASK                                                                          (0x0000000cU)
#define MCASP_XRSRCTL1_DISMOD_TRI                                                                            (0U)
#define MCASP_XRSRCTL1_DISMOD_RSV                                                                            (1U)
#define MCASP_XRSRCTL1_DISMOD_DRV0                                                                           (2U)
#define MCASP_XRSRCTL1_DISMOD_DRV1                                                                           (3U)

#define MCASP_XRSRCTL1_SRMOD_SHIFT                                                                          (0U)
#define MCASP_XRSRCTL1_SRMOD_MASK                                                                           (0x00000003U)
#define MCASP_XRSRCTL1_SRMOD_INACTIVE                                                                        (0U)
#define MCASP_XRSRCTL1_SRMOD_XMT                                                                             (1U)
#define MCASP_XRSRCTL1_SRMOD_RCV                                                                             (2U)

#define MCASP_XRSRCTL2_RESERVED41_SHIFT                                                                     (6U)
#define MCASP_XRSRCTL2_RESERVED41_MASK                                                                      (0xffffffc0U)

#define MCASP_XRSRCTL2_RRDY_SHIFT                                                                           (5U)
#define MCASP_XRSRCTL2_RRDY_MASK                                                                            (0x00000020U)
#define MCASP_XRSRCTL2_RRDY_EMPTY                                                                            (0U)
#define MCASP_XRSRCTL2_RRDY_DATA                                                                             (1U)

#define MCASP_XRSRCTL2_XRDY_SHIFT                                                                           (4U)
#define MCASP_XRSRCTL2_XRDY_MASK                                                                            (0x00000010U)
#define MCASP_XRSRCTL2_XRDY_DATA                                                                             (0U)
#define MCASP_XRSRCTL2_XRDY_EMPTY                                                                            (1U)

#define MCASP_XRSRCTL2_DISMOD_SHIFT                                                                         (2U)
#define MCASP_XRSRCTL2_DISMOD_MASK                                                                          (0x0000000cU)
#define MCASP_XRSRCTL2_DISMOD_TRI                                                                            (0U)
#define MCASP_XRSRCTL2_DISMOD_RSV                                                                            (1U)
#define MCASP_XRSRCTL2_DISMOD_DRV0                                                                           (2U)
#define MCASP_XRSRCTL2_DISMOD_DRV1                                                                           (3U)

#define MCASP_XRSRCTL2_SRMOD_SHIFT                                                                          (0U)
#define MCASP_XRSRCTL2_SRMOD_MASK                                                                           (0x00000003U)
#define MCASP_XRSRCTL2_SRMOD_INACTIVE                                                                        (0U)
#define MCASP_XRSRCTL2_SRMOD_XMT                                                                             (1U)
#define MCASP_XRSRCTL2_SRMOD_RCV                                                                             (2U)

#define MCASP_XRSRCTL3_RESERVED42_SHIFT                                                                     (6U)
#define MCASP_XRSRCTL3_RESERVED42_MASK                                                                      (0xffffffc0U)

#define MCASP_XRSRCTL3_RRDY_SHIFT                                                                           (5U)
#define MCASP_XRSRCTL3_RRDY_MASK                                                                            (0x00000020U)
#define MCASP_XRSRCTL3_RRDY_EMPTY                                                                            (0U)
#define MCASP_XRSRCTL3_RRDY_DATA                                                                             (1U)

#define MCASP_XRSRCTL3_XRDY_SHIFT                                                                           (4U)
#define MCASP_XRSRCTL3_XRDY_MASK                                                                            (0x00000010U)
#define MCASP_XRSRCTL3_XRDY_DATA                                                                             (0U)
#define MCASP_XRSRCTL3_XRDY_EMPTY                                                                            (1U)

#define MCASP_XRSRCTL3_DISMOD_SHIFT                                                                         (2U)
#define MCASP_XRSRCTL3_DISMOD_MASK                                                                          (0x0000000cU)
#define MCASP_XRSRCTL3_DISMOD_TRI                                                                            (0U)
#define MCASP_XRSRCTL3_DISMOD_RSV                                                                            (1U)
#define MCASP_XRSRCTL3_DISMOD_DRV0                                                                           (2U)
#define MCASP_XRSRCTL3_DISMOD_DRV1                                                                           (3U)

#define MCASP_XRSRCTL3_SRMOD_SHIFT                                                                          (0U)
#define MCASP_XRSRCTL3_SRMOD_MASK                                                                           (0x00000003U)
#define MCASP_XRSRCTL3_SRMOD_INACTIVE                                                                        (0U)
#define MCASP_XRSRCTL3_SRMOD_XMT                                                                             (1U)
#define MCASP_XRSRCTL3_SRMOD_RCV                                                                             (2U)

#define MCASP_XRSRCTL4_RESERVED43_SHIFT                                                                     (6U)
#define MCASP_XRSRCTL4_RESERVED43_MASK                                                                      (0xffffffc0U)

#define MCASP_XRSRCTL4_RRDY_SHIFT                                                                           (5U)
#define MCASP_XRSRCTL4_RRDY_MASK                                                                            (0x00000020U)
#define MCASP_XRSRCTL4_RRDY_EMPTY                                                                            (0U)
#define MCASP_XRSRCTL4_RRDY_DATA                                                                             (1U)

#define MCASP_XRSRCTL4_XRDY_SHIFT                                                                           (4U)
#define MCASP_XRSRCTL4_XRDY_MASK                                                                            (0x00000010U)
#define MCASP_XRSRCTL4_XRDY_DATA                                                                             (0U)
#define MCASP_XRSRCTL4_XRDY_EMPTY                                                                            (1U)

#define MCASP_XRSRCTL4_DISMOD_SHIFT                                                                         (2U)
#define MCASP_XRSRCTL4_DISMOD_MASK                                                                          (0x0000000cU)
#define MCASP_XRSRCTL4_DISMOD_TRI                                                                            (0U)
#define MCASP_XRSRCTL4_DISMOD_RSV                                                                            (1U)
#define MCASP_XRSRCTL4_DISMOD_DRV0                                                                           (2U)
#define MCASP_XRSRCTL4_DISMOD_DRV1                                                                           (3U)

#define MCASP_XRSRCTL4_SRMOD_SHIFT                                                                          (0U)
#define MCASP_XRSRCTL4_SRMOD_MASK                                                                           (0x00000003U)
#define MCASP_XRSRCTL4_SRMOD_INACTIVE                                                                        (0U)
#define MCASP_XRSRCTL4_SRMOD_XMT                                                                             (1U)
#define MCASP_XRSRCTL4_SRMOD_RCV                                                                             (2U)

#define MCASP_XRSRCTL5_RESERVED44_SHIFT                                                                     (6U)
#define MCASP_XRSRCTL5_RESERVED44_MASK                                                                      (0xffffffc0U)

#define MCASP_XRSRCTL5_RRDY_SHIFT                                                                           (5U)
#define MCASP_XRSRCTL5_RRDY_MASK                                                                            (0x00000020U)
#define MCASP_XRSRCTL5_RRDY_EMPTY                                                                            (0U)
#define MCASP_XRSRCTL5_RRDY_DATA                                                                             (1U)

#define MCASP_XRSRCTL5_XRDY_SHIFT                                                                           (4U)
#define MCASP_XRSRCTL5_XRDY_MASK                                                                            (0x00000010U)
#define MCASP_XRSRCTL5_XRDY_DATA                                                                             (0U)
#define MCASP_XRSRCTL5_XRDY_EMPTY                                                                            (1U)

#define MCASP_XRSRCTL5_DISMOD_SHIFT                                                                         (2U)
#define MCASP_XRSRCTL5_DISMOD_MASK                                                                          (0x0000000cU)
#define MCASP_XRSRCTL5_DISMOD_TRI                                                                            (0U)
#define MCASP_XRSRCTL5_DISMOD_RSV                                                                            (1U)
#define MCASP_XRSRCTL5_DISMOD_DRV0                                                                           (2U)
#define MCASP_XRSRCTL5_DISMOD_DRV1                                                                           (3U)

#define MCASP_XRSRCTL5_SRMOD_SHIFT                                                                          (0U)
#define MCASP_XRSRCTL5_SRMOD_MASK                                                                           (0x00000003U)
#define MCASP_XRSRCTL5_SRMOD_INACTIVE                                                                        (0U)
#define MCASP_XRSRCTL5_SRMOD_XMT                                                                             (1U)
#define MCASP_XRSRCTL5_SRMOD_RCV                                                                             (2U)

#define MCASP_XRSRCTL6_RESERVED45_SHIFT                                                                     (6U)
#define MCASP_XRSRCTL6_RESERVED45_MASK                                                                      (0xffffffc0U)

#define MCASP_XRSRCTL6_RRDY_SHIFT                                                                           (5U)
#define MCASP_XRSRCTL6_RRDY_MASK                                                                            (0x00000020U)
#define MCASP_XRSRCTL6_RRDY_EMPTY                                                                            (0U)
#define MCASP_XRSRCTL6_RRDY_DATA                                                                             (1U)

#define MCASP_XRSRCTL6_XRDY_SHIFT                                                                           (4U)
#define MCASP_XRSRCTL6_XRDY_MASK                                                                            (0x00000010U)
#define MCASP_XRSRCTL6_XRDY_DATA                                                                             (0U)
#define MCASP_XRSRCTL6_XRDY_EMPTY                                                                            (1U)

#define MCASP_XRSRCTL6_DISMOD_SHIFT                                                                         (2U)
#define MCASP_XRSRCTL6_DISMOD_MASK                                                                          (0x0000000cU)
#define MCASP_XRSRCTL6_DISMOD_TRI                                                                            (0U)
#define MCASP_XRSRCTL6_DISMOD_RSV                                                                            (1U)
#define MCASP_XRSRCTL6_DISMOD_DRV0                                                                           (2U)
#define MCASP_XRSRCTL6_DISMOD_DRV1                                                                           (3U)

#define MCASP_XRSRCTL6_SRMOD_SHIFT                                                                          (0U)
#define MCASP_XRSRCTL6_SRMOD_MASK                                                                           (0x00000003U)
#define MCASP_XRSRCTL6_SRMOD_INACTIVE                                                                        (0U)
#define MCASP_XRSRCTL6_SRMOD_XMT                                                                             (1U)
#define MCASP_XRSRCTL6_SRMOD_RCV                                                                             (2U)

#define MCASP_XRSRCTL7_RESERVED46_SHIFT                                                                     (6U)
#define MCASP_XRSRCTL7_RESERVED46_MASK                                                                      (0xffffffc0U)

#define MCASP_XRSRCTL7_RRDY_SHIFT                                                                           (5U)
#define MCASP_XRSRCTL7_RRDY_MASK                                                                            (0x00000020U)
#define MCASP_XRSRCTL7_RRDY_EMPTY                                                                            (0U)
#define MCASP_XRSRCTL7_RRDY_DATA                                                                             (1U)

#define MCASP_XRSRCTL7_XRDY_SHIFT                                                                           (4U)
#define MCASP_XRSRCTL7_XRDY_MASK                                                                            (0x00000010U)
#define MCASP_XRSRCTL7_XRDY_DATA                                                                             (0U)
#define MCASP_XRSRCTL7_XRDY_EMPTY                                                                            (1U)

#define MCASP_XRSRCTL7_DISMOD_SHIFT                                                                         (2U)
#define MCASP_XRSRCTL7_DISMOD_MASK                                                                          (0x0000000cU)
#define MCASP_XRSRCTL7_DISMOD_TRI                                                                            (0U)
#define MCASP_XRSRCTL7_DISMOD_RSV                                                                            (1U)
#define MCASP_XRSRCTL7_DISMOD_DRV0                                                                           (2U)
#define MCASP_XRSRCTL7_DISMOD_DRV1                                                                           (3U)

#define MCASP_XRSRCTL7_SRMOD_SHIFT                                                                          (0U)
#define MCASP_XRSRCTL7_SRMOD_MASK                                                                           (0x00000003U)
#define MCASP_XRSRCTL7_SRMOD_INACTIVE                                                                        (0U)
#define MCASP_XRSRCTL7_SRMOD_XMT                                                                             (1U)
#define MCASP_XRSRCTL7_SRMOD_RCV                                                                             (2U)

#define MCASP_XRSRCTL8_RESERVED47_SHIFT                                                                     (6U)
#define MCASP_XRSRCTL8_RESERVED47_MASK                                                                      (0xffffffc0U)

#define MCASP_XRSRCTL8_RRDY_SHIFT                                                                           (5U)
#define MCASP_XRSRCTL8_RRDY_MASK                                                                            (0x00000020U)
#define MCASP_XRSRCTL8_RRDY_EMPTY                                                                            (0U)
#define MCASP_XRSRCTL8_RRDY_DATA                                                                             (1U)

#define MCASP_XRSRCTL8_XRDY_SHIFT                                                                           (4U)
#define MCASP_XRSRCTL8_XRDY_MASK                                                                            (0x00000010U)
#define MCASP_XRSRCTL8_XRDY_DATA                                                                             (0U)
#define MCASP_XRSRCTL8_XRDY_EMPTY                                                                            (1U)

#define MCASP_XRSRCTL8_DISMOD_SHIFT                                                                         (2U)
#define MCASP_XRSRCTL8_DISMOD_MASK                                                                          (0x0000000cU)
#define MCASP_XRSRCTL8_DISMOD_TRI                                                                            (0U)
#define MCASP_XRSRCTL8_DISMOD_RSV                                                                            (1U)
#define MCASP_XRSRCTL8_DISMOD_DRV0                                                                           (2U)
#define MCASP_XRSRCTL8_DISMOD_DRV1                                                                           (3U)

#define MCASP_XRSRCTL8_SRMOD_SHIFT                                                                          (0U)
#define MCASP_XRSRCTL8_SRMOD_MASK                                                                           (0x00000003U)
#define MCASP_XRSRCTL8_SRMOD_INACTIVE                                                                        (0U)
#define MCASP_XRSRCTL8_SRMOD_XMT                                                                             (1U)
#define MCASP_XRSRCTL8_SRMOD_RCV                                                                             (2U)

#define MCASP_XRSRCTL9_RESERVED48_SHIFT                                                                     (6U)
#define MCASP_XRSRCTL9_RESERVED48_MASK                                                                      (0xffffffc0U)

#define MCASP_XRSRCTL9_RRDY_SHIFT                                                                           (5U)
#define MCASP_XRSRCTL9_RRDY_MASK                                                                            (0x00000020U)
#define MCASP_XRSRCTL9_RRDY_EMPTY                                                                            (0U)
#define MCASP_XRSRCTL9_RRDY_DATA                                                                             (1U)

#define MCASP_XRSRCTL9_XRDY_SHIFT                                                                           (4U)
#define MCASP_XRSRCTL9_XRDY_MASK                                                                            (0x00000010U)
#define MCASP_XRSRCTL9_XRDY_DATA                                                                             (0U)
#define MCASP_XRSRCTL9_XRDY_EMPTY                                                                            (1U)

#define MCASP_XRSRCTL9_DISMOD_SHIFT                                                                         (2U)
#define MCASP_XRSRCTL9_DISMOD_MASK                                                                          (0x0000000cU)
#define MCASP_XRSRCTL9_DISMOD_TRI                                                                            (0U)
#define MCASP_XRSRCTL9_DISMOD_RSV                                                                            (1U)
#define MCASP_XRSRCTL9_DISMOD_DRV0                                                                           (2U)
#define MCASP_XRSRCTL9_DISMOD_DRV1                                                                           (3U)

#define MCASP_XRSRCTL9_SRMOD_SHIFT                                                                          (0U)
#define MCASP_XRSRCTL9_SRMOD_MASK                                                                           (0x00000003U)
#define MCASP_XRSRCTL9_SRMOD_INACTIVE                                                                        (0U)
#define MCASP_XRSRCTL9_SRMOD_XMT                                                                             (1U)
#define MCASP_XRSRCTL9_SRMOD_RCV                                                                             (2U)

#define MCASP_XRSRCTL10_RESERVED49_SHIFT                                                                    (6U)
#define MCASP_XRSRCTL10_RESERVED49_MASK                                                                     (0xffffffc0U)

#define MCASP_XRSRCTL10_RRDY_SHIFT                                                                          (5U)
#define MCASP_XRSRCTL10_RRDY_MASK                                                                           (0x00000020U)
#define MCASP_XRSRCTL10_RRDY_EMPTY                                                                           (0U)
#define MCASP_XRSRCTL10_RRDY_DATA                                                                            (1U)

#define MCASP_XRSRCTL10_XRDY_SHIFT                                                                          (4U)
#define MCASP_XRSRCTL10_XRDY_MASK                                                                           (0x00000010U)
#define MCASP_XRSRCTL10_XRDY_DATA                                                                            (0U)
#define MCASP_XRSRCTL10_XRDY_EMPTY                                                                           (1U)

#define MCASP_XRSRCTL10_DISMOD_SHIFT                                                                        (2U)
#define MCASP_XRSRCTL10_DISMOD_MASK                                                                         (0x0000000cU)
#define MCASP_XRSRCTL10_DISMOD_TRI                                                                           (0U)
#define MCASP_XRSRCTL10_DISMOD_RSV                                                                           (1U)
#define MCASP_XRSRCTL10_DISMOD_DRV0                                                                          (2U)
#define MCASP_XRSRCTL10_DISMOD_DRV1                                                                          (3U)

#define MCASP_XRSRCTL10_SRMOD_SHIFT                                                                         (0U)
#define MCASP_XRSRCTL10_SRMOD_MASK                                                                          (0x00000003U)
#define MCASP_XRSRCTL10_SRMOD_INACTIVE                                                                       (0U)
#define MCASP_XRSRCTL10_SRMOD_XMT                                                                            (1U)
#define MCASP_XRSRCTL10_SRMOD_RCV                                                                            (2U)

#define MCASP_XRSRCTL11_RESERVED50_SHIFT                                                                    (6U)
#define MCASP_XRSRCTL11_RESERVED50_MASK                                                                     (0xffffffc0U)

#define MCASP_XRSRCTL11_RRDY_SHIFT                                                                          (5U)
#define MCASP_XRSRCTL11_RRDY_MASK                                                                           (0x00000020U)
#define MCASP_XRSRCTL11_RRDY_EMPTY                                                                           (0U)
#define MCASP_XRSRCTL11_RRDY_DATA                                                                            (1U)

#define MCASP_XRSRCTL11_XRDY_SHIFT                                                                          (4U)
#define MCASP_XRSRCTL11_XRDY_MASK                                                                           (0x00000010U)
#define MCASP_XRSRCTL11_XRDY_DATA                                                                            (0U)
#define MCASP_XRSRCTL11_XRDY_EMPTY                                                                           (1U)

#define MCASP_XRSRCTL11_DISMOD_SHIFT                                                                        (2U)
#define MCASP_XRSRCTL11_DISMOD_MASK                                                                         (0x0000000cU)
#define MCASP_XRSRCTL11_DISMOD_TRI                                                                           (0U)
#define MCASP_XRSRCTL11_DISMOD_RSV                                                                           (1U)
#define MCASP_XRSRCTL11_DISMOD_DRV0                                                                          (2U)
#define MCASP_XRSRCTL11_DISMOD_DRV1                                                                          (3U)

#define MCASP_XRSRCTL11_SRMOD_SHIFT                                                                         (0U)
#define MCASP_XRSRCTL11_SRMOD_MASK                                                                          (0x00000003U)
#define MCASP_XRSRCTL11_SRMOD_INACTIVE                                                                       (0U)
#define MCASP_XRSRCTL11_SRMOD_XMT                                                                            (1U)
#define MCASP_XRSRCTL11_SRMOD_RCV                                                                            (2U)

#define MCASP_XRSRCTL12_RESERVED51_SHIFT                                                                    (6U)
#define MCASP_XRSRCTL12_RESERVED51_MASK                                                                     (0xffffffc0U)

#define MCASP_XRSRCTL12_RRDY_SHIFT                                                                          (5U)
#define MCASP_XRSRCTL12_RRDY_MASK                                                                           (0x00000020U)
#define MCASP_XRSRCTL12_RRDY_EMPTY                                                                           (0U)
#define MCASP_XRSRCTL12_RRDY_DATA                                                                            (1U)

#define MCASP_XRSRCTL12_XRDY_SHIFT                                                                          (4U)
#define MCASP_XRSRCTL12_XRDY_MASK                                                                           (0x00000010U)
#define MCASP_XRSRCTL12_XRDY_DATA                                                                            (0U)
#define MCASP_XRSRCTL12_XRDY_EMPTY                                                                           (1U)

#define MCASP_XRSRCTL12_DISMOD_SHIFT                                                                        (2U)
#define MCASP_XRSRCTL12_DISMOD_MASK                                                                         (0x0000000cU)
#define MCASP_XRSRCTL12_DISMOD_TRI                                                                           (0U)
#define MCASP_XRSRCTL12_DISMOD_RSV                                                                           (1U)
#define MCASP_XRSRCTL12_DISMOD_DRV0                                                                          (2U)
#define MCASP_XRSRCTL12_DISMOD_DRV1                                                                          (3U)

#define MCASP_XRSRCTL12_SRMOD_SHIFT                                                                         (0U)
#define MCASP_XRSRCTL12_SRMOD_MASK                                                                          (0x00000003U)
#define MCASP_XRSRCTL12_SRMOD_INACTIVE                                                                       (0U)
#define MCASP_XRSRCTL12_SRMOD_XMT                                                                            (1U)
#define MCASP_XRSRCTL12_SRMOD_RCV                                                                            (2U)

#define MCASP_XRSRCTL13_RESERVED52_SHIFT                                                                    (6U)
#define MCASP_XRSRCTL13_RESERVED52_MASK                                                                     (0xffffffc0U)

#define MCASP_XRSRCTL13_RRDY_SHIFT                                                                          (5U)
#define MCASP_XRSRCTL13_RRDY_MASK                                                                           (0x00000020U)
#define MCASP_XRSRCTL13_RRDY_EMPTY                                                                           (0U)
#define MCASP_XRSRCTL13_RRDY_DATA                                                                            (1U)

#define MCASP_XRSRCTL13_XRDY_SHIFT                                                                          (4U)
#define MCASP_XRSRCTL13_XRDY_MASK                                                                           (0x00000010U)
#define MCASP_XRSRCTL13_XRDY_DATA                                                                            (0U)
#define MCASP_XRSRCTL13_XRDY_EMPTY                                                                           (1U)

#define MCASP_XRSRCTL13_DISMOD_SHIFT                                                                        (2U)
#define MCASP_XRSRCTL13_DISMOD_MASK                                                                         (0x0000000cU)
#define MCASP_XRSRCTL13_DISMOD_TRI                                                                           (0U)
#define MCASP_XRSRCTL13_DISMOD_RSV                                                                           (1U)
#define MCASP_XRSRCTL13_DISMOD_DRV0                                                                          (2U)
#define MCASP_XRSRCTL13_DISMOD_DRV1                                                                          (3U)

#define MCASP_XRSRCTL13_SRMOD_SHIFT                                                                         (0U)
#define MCASP_XRSRCTL13_SRMOD_MASK                                                                          (0x00000003U)
#define MCASP_XRSRCTL13_SRMOD_INACTIVE                                                                       (0U)
#define MCASP_XRSRCTL13_SRMOD_XMT                                                                            (1U)
#define MCASP_XRSRCTL13_SRMOD_RCV                                                                            (2U)

#define MCASP_XRSRCTL14_RESERVED53_SHIFT                                                                    (6U)
#define MCASP_XRSRCTL14_RESERVED53_MASK                                                                     (0xffffffc0U)

#define MCASP_XRSRCTL14_RRDY_SHIFT                                                                          (5U)
#define MCASP_XRSRCTL14_RRDY_MASK                                                                           (0x00000020U)
#define MCASP_XRSRCTL14_RRDY_EMPTY                                                                           (0U)
#define MCASP_XRSRCTL14_RRDY_DATA                                                                            (1U)

#define MCASP_XRSRCTL14_XRDY_SHIFT                                                                          (4U)
#define MCASP_XRSRCTL14_XRDY_MASK                                                                           (0x00000010U)
#define MCASP_XRSRCTL14_XRDY_DATA                                                                            (0U)
#define MCASP_XRSRCTL14_XRDY_EMPTY                                                                           (1U)

#define MCASP_XRSRCTL14_DISMOD_SHIFT                                                                        (2U)
#define MCASP_XRSRCTL14_DISMOD_MASK                                                                         (0x0000000cU)
#define MCASP_XRSRCTL14_DISMOD_TRI                                                                           (0U)
#define MCASP_XRSRCTL14_DISMOD_RSV                                                                           (1U)
#define MCASP_XRSRCTL14_DISMOD_DRV0                                                                          (2U)
#define MCASP_XRSRCTL14_DISMOD_DRV1                                                                          (3U)

#define MCASP_XRSRCTL14_SRMOD_SHIFT                                                                         (0U)
#define MCASP_XRSRCTL14_SRMOD_MASK                                                                          (0x00000003U)
#define MCASP_XRSRCTL14_SRMOD_INACTIVE                                                                       (0U)
#define MCASP_XRSRCTL14_SRMOD_XMT                                                                            (1U)
#define MCASP_XRSRCTL14_SRMOD_RCV                                                                            (2U)

#define MCASP_XRSRCTL15_RESERVED54_SHIFT                                                                    (6U)
#define MCASP_XRSRCTL15_RESERVED54_MASK                                                                     (0xffffffc0U)

#define MCASP_XRSRCTL15_RRDY_SHIFT                                                                          (5U)
#define MCASP_XRSRCTL15_RRDY_MASK                                                                           (0x00000020U)
#define MCASP_XRSRCTL15_RRDY_EMPTY                                                                           (0U)
#define MCASP_XRSRCTL15_RRDY_DATA                                                                            (1U)

#define MCASP_XRSRCTL15_XRDY_SHIFT                                                                          (4U)
#define MCASP_XRSRCTL15_XRDY_MASK                                                                           (0x00000010U)
#define MCASP_XRSRCTL15_XRDY_DATA                                                                            (0U)
#define MCASP_XRSRCTL15_XRDY_EMPTY                                                                           (1U)

#define MCASP_XRSRCTL15_DISMOD_SHIFT                                                                        (2U)
#define MCASP_XRSRCTL15_DISMOD_MASK                                                                         (0x0000000cU)
#define MCASP_XRSRCTL15_DISMOD_TRI                                                                           (0U)
#define MCASP_XRSRCTL15_DISMOD_RSV                                                                           (1U)
#define MCASP_XRSRCTL15_DISMOD_DRV0                                                                          (2U)
#define MCASP_XRSRCTL15_DISMOD_DRV1                                                                          (3U)

#define MCASP_XRSRCTL15_SRMOD_SHIFT                                                                         (0U)
#define MCASP_XRSRCTL15_SRMOD_MASK                                                                          (0x00000003U)
#define MCASP_XRSRCTL15_SRMOD_INACTIVE                                                                       (0U)
#define MCASP_XRSRCTL15_SRMOD_XMT                                                                            (1U)
#define MCASP_XRSRCTL15_SRMOD_RCV                                                                            (2U)

#define MCASP_TXBUF0_XBUF0_SHIFT                                                                            (0U)
#define MCASP_TXBUF0_XBUF0_MASK                                                                             (0xffffffffU)

#define MCASP_TXBUF1_XBUF1_SHIFT                                                                            (0U)
#define MCASP_TXBUF1_XBUF1_MASK                                                                             (0xffffffffU)

#define MCASP_TXBUF2_XBUF2_SHIFT                                                                            (0U)
#define MCASP_TXBUF2_XBUF2_MASK                                                                             (0xffffffffU)

#define MCASP_TXBUF3_XBUF3_SHIFT                                                                            (0U)
#define MCASP_TXBUF3_XBUF3_MASK                                                                             (0xffffffffU)

#define MCASP_TXBUF4_XBUF4_SHIFT                                                                            (0U)
#define MCASP_TXBUF4_XBUF4_MASK                                                                             (0xffffffffU)

#define MCASP_TXBUF5_XBUF5_SHIFT                                                                            (0U)
#define MCASP_TXBUF5_XBUF5_MASK                                                                             (0xffffffffU)

#define MCASP_TXBUF6_XBUF6_SHIFT                                                                            (0U)
#define MCASP_TXBUF6_XBUF6_MASK                                                                             (0xffffffffU)

#define MCASP_TXBUF7_XBUF7_SHIFT                                                                            (0U)
#define MCASP_TXBUF7_XBUF7_MASK                                                                             (0xffffffffU)

#define MCASP_TXBUF8_XBUF8_SHIFT                                                                            (0U)
#define MCASP_TXBUF8_XBUF8_MASK                                                                             (0xffffffffU)

#define MCASP_TXBUF9_XBUF9_SHIFT                                                                            (0U)
#define MCASP_TXBUF9_XBUF9_MASK                                                                             (0xffffffffU)

#define MCASP_TXBUF10_XBUF10_SHIFT                                                                          (0U)
#define MCASP_TXBUF10_XBUF10_MASK                                                                           (0xffffffffU)

#define MCASP_TXBUF11_XBUF11_SHIFT                                                                          (0U)
#define MCASP_TXBUF11_XBUF11_MASK                                                                           (0xffffffffU)

#define MCASP_TXBUF12_XBUF12_SHIFT                                                                          (0U)
#define MCASP_TXBUF12_XBUF12_MASK                                                                           (0xffffffffU)

#define MCASP_TXBUF13_XBUF13_SHIFT                                                                          (0U)
#define MCASP_TXBUF13_XBUF13_MASK                                                                           (0xffffffffU)

#define MCASP_TXBUF14_XBUF14_SHIFT                                                                          (0U)
#define MCASP_TXBUF14_XBUF14_MASK                                                                           (0xffffffffU)

#define MCASP_TXBUF15_XBUF15_SHIFT                                                                          (0U)
#define MCASP_TXBUF15_XBUF15_MASK                                                                           (0xffffffffU)

#define MCASP_RXBUF0_RBUF0_SHIFT                                                                            (0U)
#define MCASP_RXBUF0_RBUF0_MASK                                                                             (0xffffffffU)

#define MCASP_RXBUF1_RBUF1_SHIFT                                                                            (0U)
#define MCASP_RXBUF1_RBUF1_MASK                                                                             (0xffffffffU)

#define MCASP_RXBUF2_RBUF2_SHIFT                                                                            (0U)
#define MCASP_RXBUF2_RBUF2_MASK                                                                             (0xffffffffU)

#define MCASP_RXBUF3_RBUF3_SHIFT                                                                            (0U)
#define MCASP_RXBUF3_RBUF3_MASK                                                                             (0xffffffffU)

#define MCASP_RXBUF4_RBUF4_SHIFT                                                                            (0U)
#define MCASP_RXBUF4_RBUF4_MASK                                                                             (0xffffffffU)

#define MCASP_RXBUF5_RBUF5_SHIFT                                                                            (0U)
#define MCASP_RXBUF5_RBUF5_MASK                                                                             (0xffffffffU)

#define MCASP_RXBUF6_RBUF6_SHIFT                                                                            (0U)
#define MCASP_RXBUF6_RBUF6_MASK                                                                             (0xffffffffU)

#define MCASP_RXBUF7_RBUF7_SHIFT                                                                            (0U)
#define MCASP_RXBUF7_RBUF7_MASK                                                                             (0xffffffffU)

#define MCASP_RXBUF8_RBUF8_SHIFT                                                                            (0U)
#define MCASP_RXBUF8_RBUF8_MASK                                                                             (0xffffffffU)

#define MCASP_RXBUF9_RBUF9_SHIFT                                                                            (0U)
#define MCASP_RXBUF9_RBUF9_MASK                                                                             (0xffffffffU)

#define MCASP_RXBUF10_RBUF10_SHIFT                                                                          (0U)
#define MCASP_RXBUF10_RBUF10_MASK                                                                           (0xffffffffU)

#define MCASP_RXBUF11_RBUF11_SHIFT                                                                          (0U)
#define MCASP_RXBUF11_RBUF11_MASK                                                                           (0xffffffffU)

#define MCASP_RXBUF12_RBUF12_SHIFT                                                                          (0U)
#define MCASP_RXBUF12_RBUF12_MASK                                                                           (0xffffffffU)

#define MCASP_RXBUF13_RBUF13_SHIFT                                                                          (0U)
#define MCASP_RXBUF13_RBUF13_MASK                                                                           (0xffffffffU)

#define MCASP_RXBUF14_RBUF14_SHIFT                                                                          (0U)
#define MCASP_RXBUF14_RBUF14_MASK                                                                           (0xffffffffU)

#define MCASP_RXBUF15_RBUF15_SHIFT                                                                          (0U)
#define MCASP_RXBUF15_RBUF15_MASK                                                                           (0xffffffffU)

#define MCASP_WFIFOCTL_WNUMDMA_SHIFT                                                                        (0U)
#define MCASP_WFIFOCTL_WNUMDMA_MASK                                                                         (0x000000ffU)

#define MCASP_WFIFOCTL_WNUMEVT_SHIFT                                                                        (8U)
#define MCASP_WFIFOCTL_WNUMEVT_MASK                                                                         (0x0000ff00U)

#define MCASP_WFIFOCTL_WENA_SHIFT                                                                           (16U)
#define MCASP_WFIFOCTL_WENA_MASK                                                                            (0x00010000U)

#define MCASP_WFIFOCTL_RESERVED_SHIFT                                                                       (17U)
#define MCASP_WFIFOCTL_RESERVED_MASK                                                                        (0xfffe0000U)

#define MCASP_RFIFOCTL_RNUMDMA_SHIFT                                                                        (0U)
#define MCASP_RFIFOCTL_RNUMDMA_MASK                                                                         (0x000000ffU)

#define MCASP_RFIFOCTL_RNUMEVT_SHIFT                                                                        (8U)
#define MCASP_RFIFOCTL_RNUMEVT_MASK                                                                         (0x0000ff00U)

#define MCASP_RFIFOCTL_RENA_SHIFT                                                                           (16U)
#define MCASP_RFIFOCTL_RENA_MASK                                                                            (0x00010000U)

#define MCASP_RFIFOCTL_RESERVED_SHIFT                                                                       (17U)
#define MCASP_RFIFOCTL_RESERVED_MASK                                                                        (0xfffe0000U)

#define MCASP_WFIFOSTS_WLVL_SHIFT                                                                           (0U)
#define MCASP_WFIFOSTS_WLVL_MASK                                                                            (0x000000ffU)

#define MCASP_WFIFOSTS_RESERVED_SHIFT                                                                       (8U)
#define MCASP_WFIFOSTS_RESERVED_MASK                                                                        (0xffffff00U)

#define MCASP_RFIFOSTS_RLVL_SHIFT                                                                           (0U)
#define MCASP_RFIFOSTS_RLVL_MASK                                                                            (0x000000ffU)

#define MCASP_RFIFOSTS_RESERVED_SHIFT                                                                       (8U)
#define MCASP_RFIFOSTS_RESERVED_MASK                                                                        (0xffffff00U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_MCASP_H_ */
