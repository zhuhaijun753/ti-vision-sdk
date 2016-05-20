/* ======================================================================
 *   Copyright (C) 2013 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */
/**
 *  \file  hw_intc.h
 *
 *  \brief This file contains the MACROS definitions used by interrupt
 **controller module.
 */

#ifndef HW_INTC_H_
#define HW_INTC_H_

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/*************************************************************************\
 * Registers Definition
 \*************************************************************************/
#define INTC_REVISION (0x0U)
#define INTC_SYSCONFIG (0x10U)
#define INTC_SYSSTATUS (0x14U)
#define INTC_SIR_IRQ (0x40U)
#define INTC_SIR_FIQ (0x44U)
#define INTC_CONTROL (0x48U)
#define INTC_PROTECTION (0x4cU)
#define INTC_IDLE  (0x50U)
#define INTC_IRQ_PRIORITY (0x60U)
#define INTC_FIQ_PRIORITY (0x64U)
#define INTC_THRESHOLD (0x68U)
#define INTC_SICR  (0x6cU)
#define INTC_SCR(n) ((uint32_t) 0x70 + ((n) * (uint32_t) 0x04))
#define INTC_ITR(n) ((uint32_t) 0x80 + ((n) * (uint32_t) 0x20))
#define INTC_MIR(n) ((uint32_t) 0x84 + ((n) * (uint32_t) 0x20))
#define INTC_MIR_CLEAR(n) ((uint32_t) 0x88 + ((n) * (uint32_t) 0x20))
#define INTC_MIR_SET(n) ((uint32_t) 0x8c + ((n) * (uint32_t) 0x20))
#define INTC_ISR_SET(n) ((uint32_t) 0x90 + ((n) * (uint32_t) 0x20))
#define INTC_ISR_CLEAR(n) ((uint32_t) 0x94 + ((n) * (uint32_t) 0x20))
#define INTC_PENDING_IRQ(n) ((uint32_t) 0x98 + ((n) * (uint32_t) 0x20))
#define INTC_PENDING_FIQ(n) ((uint32_t) 0x9c + ((n) * (uint32_t) 0x20))
#define INTC_ILR(n)  ((uint32_t) 0x100 + ((n) * (uint32_t) 0x04))

/**************************************************************************\
 * Field Definition Macros
 \**************************************************************************/

/* REVISION */
#define INTC_REVISION_REV    (0x000000FFU)
#define INTC_REVISION_REV_SHIFT  (0x00000000U)

/* SYSCONFIG */
#define INTC_SYSCONFIG_SOFTRESET    (0x00000002U)
#define INTC_SYSCONFIG_SOFTRESET_SHIFT  (0x00000001U)

#define INTC_SYSCONFIG_AUTOIDLE    (0x00000001U)
#define INTC_SYSCONFIG_AUTOIDLE_SHIFT  (0x00000000U)

/* SYSSTATUS */
#define INTC_SYSSTATUS_RESETDONE    (0x00000001U)
#define INTC_SYSSTATUS_RESETDONE_SHIFT  (0x00000000U)

/* SIR_IRQ */
#define INTC_SIR_IRQ_SPURIOUSIRQ    (0xFFFFFF80U)
#define INTC_SIR_IRQ_SPURIOUSIRQ_SHIFT  (0x00000007U)

#define INTC_SIR_IRQ_ACTIVEIRQ    (0x0000007FU)
#define INTC_SIR_IRQ_ACTIVEIRQ_SHIFT  (0x00000000U)

/* SIR_FIQ */
#define INTC_SIR_FIQ_SPURIOUSFIQ    (0xFFFFFF80U)
#define INTC_SIR_FIQ_SPURIOUSFIQ_SHIFT  (0x00000007U)

#define INTC_SIR_FIQ_ACTIVEFIQ    (0x0000007FU)
#define INTC_SIR_FIQ_ACTIVEFIQ_SHIFT  (0x00000000U)

/* CONTROL */
#define INTC_CONTROL_NEWFIQAGR    (0x00000002U)
#define INTC_CONTROL_NEWFIQAGR_SHIFT  (0x00000001U)

#define INTC_CONTROL_NEWIRQAGR    (0x00000001U)
#define INTC_CONTROL_NEWIRQAGR_SHIFT  (0x00000000U)

/* PROTECTION */
#define INTC_PROTECTION_PROTECTION    (0x00000001U)
#define INTC_PROTECTION_PROTECTION_SHIFT  (0x00000000U)

/* IDLE */
#define INTC_IDLE_TURBO    (0x00000002U)
#define INTC_IDLE_TURBO_SHIFT  (0x00000001U)

#define INTC_IDLE_FUNCIDLE    (0x00000001U)
#define INTC_IDLE_FUNCIDLE_SHIFT  (0x00000000U)

/* IRQ_PRIORITY */
#define INTC_IRQ_PRIORITY_SPURIOUSIRQFLAG    (0xFFFFFFC0U)
#define INTC_IRQ_PRIORITY_SPURIOUSIRQFLAG_SHIFT  (0x00000006U)

#define INTC_IRQ_PRIORITY_IRQPRIORITY    (0x0000003FU)
#define INTC_IRQ_PRIORITY_IRQPRIORITY_SHIFT  (0x00000000U)

/* FIQ_PRIORITY */
#define INTC_FIQ_PRIORITY_SPURIOUSFIQFLAG    (0xFFFFFFC0U)
#define INTC_FIQ_PRIORITY_SPURIOUSFIQFLAG_SHIFT  (0x00000006U)

#define INTC_FIQ_PRIORITY_FIQPRIORITY    (0x0000003FU)
#define INTC_FIQ_PRIORITY_FIQPRIORITY_SHIFT  (0x00000000U)

/* THRESHOLD */
#define INTC_THRESHOLD_PRIORITYTHRESHOLD    (0x000000FFU)
#define INTC_THRESHOLD_PRIORITYTHRESHOLD_SHIFT  (0x00000000U)

/* SICR */
#define INTC_SICR_GLOBALMASK    (0x00000040U)
#define INTC_SICR_GLOBALMASK_SHIFT  (0x00000006U)

#define INTC_SICR_SOFTRESETINH    (0x00000020U)
#define INTC_SICR_SOFTRESETINH_SHIFT  (0x00000005U)

#define INTC_SICR_PUBLICMASKFEEDBACK    (0x00000010U)
#define INTC_SICR_PUBLICMASKFEEDBACK_SHIFT  (0x00000004U)

#define INTC_SICR_PUBLICINHIBIT    (0x00000008U)
#define INTC_SICR_PUBLICINHIBIT_SHIFT  (0x00000003U)

#define INTC_SICR_AUTOINHIBIT    (0x00000004U)
#define INTC_SICR_AUTOINHIBIT_SHIFT  (0x00000002U)

#define INTC_SICR_SSMFIQENABLE    (0x00000002U)
#define INTC_SICR_SSMFIQENABLE_SHIFT  (0x00000001U)

#define INTC_SICR_SSMFIQSTATUS    (0x00000001U)
#define INTC_SICR_SSMFIQSTATUS_SHIFT  (0x00000000U)

/* SCR0 */
#define INTC_SCR0_SECUREENABLE    (0xFFFFFFFFU)
#define INTC_SCR0_SECUREENABLE_SHIFT  (0x00000000U)

/* SCR1 */
#define INTC_SCR1_SECUREENABLE    (0xFFFFFFFFU)
#define INTC_SCR1_SECUREENABLE_SHIFT  (0x00000000U)

/* SCR2 */
#define INTC_SCR2_SECUREENABLE    (0xFFFFFFFFU)
#define INTC_SCR2_SECUREENABLE_SHIFT  (0x00000000U)

/* ITR0 */
#define INTC_ITR0_ITR    (0xFFFFFFFFU)
#define INTC_ITR0_ITR_SHIFT  (0x00000000U)

/* MIR0 */
#define INTC_MIR0_MIR    (0xFFFFFFFFU)
#define INTC_MIR0_MIR_SHIFT  (0x00000000U)

/* MIR_CLEAR0 */
#define INTC_MIR_CLEAR0_MIRCLEAR    (0xFFFFFFFFU)
#define INTC_MIR_CLEAR0_MIRCLEAR_SHIFT  (0x00000000U)

/* MIR_SET0 */
#define INTC_MIR_SET0_MIRSET    (0xFFFFFFFFU)
#define INTC_MIR_SET0_MIRSET_SHIFT  (0x00000000U)

/* ISR_SET0 */
#define INTC_ISR_SET0_ISRSET    (0xFFFFFFFFU)
#define INTC_ISR_SET0_ISRSET_SHIFT  (0x00000000U)

/* ISR_CLEAR0 */
#define INTC_ISR_CLEAR0_ISRCLEAR    (0xFFFFFFFFU)
#define INTC_ISR_CLEAR0_ISRCLEAR_SHIFT  (0x00000000U)

/* PENDING_IRQ0 */
#define INTC_PENDING_IRQ0_PENDING_IRQ    (0xFFFFFFFFU)
#define INTC_PENDING_IRQ0_PENDING_IRQ_SHIFT  (0x00000000U)

/* PENDING_FIQ0 */
#define INTC_PENDING_FIQ0_PENDING_FIQ    (0xFFFFFFFFU)
#define INTC_PENDING_FIQ0_PENDING_FIQ_SHIFT  (0x00000000U)

/* ITR1 */
#define INTC_ITR1_ITR    (0xFFFFFFFFU)
#define INTC_ITR1_ITR_SHIFT  (0x00000000U)

/* MIR1 */
#define INTC_MIR1_MIR    (0xFFFFFFFFU)
#define INTC_MIR1_MIR_SHIFT  (0x00000000U)

/* MIR_CLEAR1 */
#define INTC_MIR_CLEAR1_MIRCLEAR    (0xFFFFFFFFU)
#define INTC_MIR_CLEAR1_MIRCLEAR_SHIFT  (0x00000000U)

/* MIR_SET1 */
#define INTC_MIR_SET1_MIRSET    (0xFFFFFFFFU)
#define INTC_MIR_SET1_MIRSET_SHIFT  (0x00000000U)

/* ISR_SET1 */
#define INTC_ISR_SET1_ISRSET    (0xFFFFFFFFU)
#define INTC_ISR_SET1_ISRSET_SHIFT  (0x00000000U)

/* ISR_CLEAR1 */
#define INTC_ISR_CLEAR1_ISRCLEAR    (0xFFFFFFFFU)
#define INTC_ISR_CLEAR1_ISRCLEAR_SHIFT  (0x00000000U)

/* PENDING_IRQ1 */
#define INTC_PENDING_IRQ1_PENDING_IRQ    (0xFFFFFFFFU)
#define INTC_PENDING_IRQ1_PENDING_IRQ_SHIFT  (0x00000000U)

/* PENDING_FIQ1 */
#define INTC_PENDING_FIQ1_PENDING_FIQ    (0xFFFFFFFFU)
#define INTC_PENDING_FIQ1_PENDING_FIQ_SHIFT  (0x00000000U)

/* ITR2 */
#define INTC_ITR2_ITR    (0xFFFFFFFFU)
#define INTC_ITR2_ITR_SHIFT  (0x00000000U)

/* MIR2 */
#define INTC_MIR2_MIR    (0xFFFFFFFFU)
#define INTC_MIR2_MIR_SHIFT  (0x00000000U)

/* MIR_CLEAR2 */
#define INTC_MIR_CLEAR2_MIRCLEAR    (0xFFFFFFFFU)
#define INTC_MIR_CLEAR2_MIRCLEAR_SHIFT  (0x00000000U)

/* MIR_SET2 */
#define INTC_MIR_SET2_MIRSET    (0xFFFFFFFFU)
#define INTC_MIR_SET2_MIRSET_SHIFT  (0x00000000U)

/* ISR_SET2 */
#define INTC_ISR_SET2_ISRSET    (0xFFFFFFFFU)
#define INTC_ISR_SET2_ISRSET_SHIFT  (0x00000000U)

/* ISR_CLEAR2 */
#define INTC_ISR_CLEAR2_ISRCLEAR    (0xFFFFFFFFU)
#define INTC_ISR_CLEAR2_ISRCLEAR_SHIFT  (0x00000000U)

/* PENDING_IRQ2 */
#define INTC_PENDING_IRQ2_PENDING_IRQ    (0xFFFFFFFFU)
#define INTC_PENDING_IRQ2_PENDING_IRQ_SHIFT  (0x00000000U)

/* PENDING_FIQ2 */
#define INTC_PENDING_FIQ2_PENDING_FIQ    (0xFFFFFFFFU)
#define INTC_PENDING_FIQ2_PENDING_FIQ_SHIFT  (0x00000000U)

/* ILR */
#define INTC_ILR_PRIORITY    (0x000001FCU)
#define INTC_ILR_PRIORITY_SHIFT  (0x00000002U)

#define INTC_ILR_FIQNIRQ    (0x00000001U)
#define INTC_ILR_FIQNIRQ_SHIFT  (0x00000000U)

void _c_int00(void);
void UndefInstHandler(void);
void SVCHandler(void);
void AbortHandler(void);
void IRQHandler(void);
void FIQHandler(void);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif
