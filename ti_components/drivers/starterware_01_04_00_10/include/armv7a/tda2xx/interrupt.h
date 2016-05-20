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
 *  \file  interrupt.h
 *
 *  \brief This file contains the API prototypes for configuring INTC for
 *         ARM Cortex-A8
 */

#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "stdint.h"
#include "hw_intc.h"
#include "hw_types.h"

#ifdef __cplusplus
extern "C" {
#endif
/****************************************************************************
**                       MACRO DEFINITIONS
****************************************************************************/
/*
** Macros which can be passed to IntPrioritySet API as hostIntRoute.
*/

/* To route an interrupt to IRQ */
#define AINTC_HOSTINT_ROUTE_IRQ                (0U)

/* To route an interrupt to FIQ */
#define AINTC_HOSTINT_ROUTE_FIQ                (1U)

/* External interrupt from the system */
#define NUM_INTERRUPTS_EXTERNAL     (160U)
/* Internal interrupts in ARMV7A core
 * Currently only supporting ABORT
 */
#define NUM_INTERRUPTS_INTERNAL     (1U)

#define INTERNAL_INTERRUPT_ABORT_ID (NUM_INTERRUPTS_EXTERNAL)

#define NUM_INTERRUPTS    (NUM_INTERRUPTS_EXTERNAL + NUM_INTERRUPTS_INTERNAL)

/*****************************************************************************
**                     TYPEDEF DEFINITIONS
*****************************************************************************/
typedef void (*IntrFuncPtr)(void *handle);

/*
** Interrupt number list
** Not yet defined
*/

/*****************************************************************************
**                     API FUNCTION PROTOTYPES
*****************************************************************************/

/**
 * \brief    Registers an interrupt Handler in the interrupt vector table for
 *           system interrupts.
 *
 * \param    intrNum - Interrupt Number
 * \param    fnHandler - Function pointer to the ISR
 * \param    fun_arg - Argument to the ISR
 *
 * Note: When the interrupt occurs for the sytem interrupt number indicated,
 * the control goes to the ISR given as the parameter.
 *
 * \return      None.
 **/
void Intc_IntRegister(uint16_t intrNum, IntrFuncPtr fptr, void *fun_arg);

/**
 * \brief   Unregisters an interrupt
 *
 * \param   intrNum - Interrupt Number
 *
 * Note: Once an interrupt is unregistered it will enter infinite loop once
 * an interrupt occurs
 *
 * \return      None.
 **/
void Intc_IntUnregister(uint16_t intrNum);

/**
 * \brief   This API is used to initialize the interrupt controller. This API
 *          shall be called before using the interrupt controller.
 *
 * \param   None
 *
 * \return  None.
 *
 **/
void Intc_Init(void);

/**
 * \brief   This API assigns a priority to an interrupt and routes it to
 *          either IRQ or to FIQ. Priority 0 is the highest priority level
 *          Among the host interrupts, FIQ has more priority than IRQ.
 *
 * \param   intrNum  - Interrupt number
 * \param   priority - Interrupt priority level
 * \param   dummy
 *
 * \return  None.
 *
 **/
void Intc_IntPrioritySet(uint16_t intrNum, uint16_t priority,
                         uint8_t hostIntRoute);

/**
 * \brief   This API enables the system interrupt in INTC. However, for
 *          the interrupt generation, make sure that the interrupt is
 *          enabled at the peripheral level also.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void Intc_SystemEnable(uint16_t intrNum);

/**
 * \brief   This API disables the system interrupt in INTC.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void Intc_SystemDisable(uint16_t intrNum);

void IntEnableSecureMode(uint32_t intrNum);
void IntDisableSecureMode(uint32_t intrNum);
void IntSetPendingState(uint32_t intrNum);
void IntClearPendingState(uint32_t intrNum);
uint32_t IntGetPendingState(uint32_t intrNum);
uint32_t IntGetActiveState(uint32_t intrNum);
void IntClearActiveState(uint32_t intrNum);

/**
 * \brief   This API configures the target processor for the interrupt passed
 *
 * \param   intrNum  - Interrupt number
 *
 * \param   processorSelect - Possible values are:
 *                            0x1 - Pending interrupt is sent to processors 0
 *                            0x2 - Pending interrupt is sent to processors 1
 *                            0x3 - Pending interrupt is sent to processors 0
 *                                  and 1
 * \return  None.
 *
 **/
void IntSetTargetProcessor(uint32_t intrNum, uint32_t processorSelect);

/**
 * \brief   This API configures the type of interrupt and Mode of interupt
 *          handling
 *
 * \param   intrNum  - Interrupt number
 *
 * \param   intType  - Possible values are:
 *                     0x0 - interrupt set to level sensitive type
 *                     0x1 - interrupt set to edge triggered type
 *
 * \param   intHandleModel  -
 *          1-N Model : Only one processor handles this interrupt. The system
 *          must implement a mechanism to determine which processor handles an
 *          interrupt that is programmed to target more than one processor.
 *
 *          1-N Model :All processors receive the interrupt independently. When
 *          a processor acknowledges the interrupt, the interrupt pending state
 *          is cleared only for that processor. The interrupt remains pending
 *          for the other processors
 *
 *          Possible values are:
 *             0x0 - interrupt set to 1-N interrupt handling Model
 *             0x1 - interrupt set to N-N interrupt handling Model
 *
 * \return  None.
 *
 **/
void IntConfigTypenModel(uint32_t intrNum, uint32_t intType,
                         uint32_t intHandleModel);

/**
 * \brief   This API configures whether the interrupt in secure mode to be
 *          routed to IRQ or FIQ
 *
 * \param   intRoute  - Possible values
 *                      AINTC_HOSTINT_ROUTE_IRQ - Interrupt routed to IRQ
 *                      AINTC_HOSTINT_ROUTE_FIQ - Interrupt routed to FIQ
 *
 * \return  None.
 *
 **/
void IntEnableSecureFIQ(uint32_t intRoute);

/**
 * \brief        The priority mask level for the CPU interface. If the
 *               priority of an interrupt is higher than the
 *               value indicated by this field, the interface signals the
 *               interrupt to the processor.
 *               If the GIC supports fewer than 256 priority levels then some
 *               bits are RAZ/WI, as follows:
 *               128 supported levels Bit [0] = 0.
 *               64 supported levels Bit [1:0] = 0b00.
 *               32 supported levels Bit [2:0] = 0b000.
 *               16 supported levels Bit [3:0] = 0b0000. - (RW)
 *
 * \param        prirityMask
 *
 * \return  None.
 *
 **/
void IntSetProirityMask(uint32_t priorityMask);

/**
 * \brief   returns the priority mask level for the CPU interface.
 *
 * \return  prirityMask.
 *
 **/
uint32_t IntGetProirityMask(void);

/**
 * \brief   This API returns the priority value of the highest priority
 *          interrupt that is active on the CPU interface
 *
 * \return  priority value of the highest priority interrupt
 *          that is active on the CPU interface
 *
 **/
uint32_t IntGetActivePriority(void);

/**
 * \brief  returns the interrupt ID of the highest priority pending interrupt
 *
 * \return interrupt ID of the highest priority pending interrupt
 *
 */
uint32_t IntGetPendingIntNum(void);

/**
 * \brief  On a multiprocessor implementation, if the PENDINTID field returns
 *         the ID of an SGI, this field contains the CPUID value for that
 *         interrupt. This identifies the processor that generated the
 *         interrupt.
 *
 * \return CPUID of the highest priority pending interrupt
 *
 */
uint32_t IntGetPendingCPUID(void);

/**
 * \brief  Enables the processor IRQ only in CPSR. Makes the processor to
 *         respond to IRQs.  This does not affect the set of interrupts
 *         enabled/disabled in the AINTC.
 *
 * \param    None
 *
 * \return   None
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
void IntMasterIRQEnable(void);

/**
 * \brief  Disables the processor IRQ only in CPSR.Prevents the processor to
 *         respond to IRQs.  This does not affect the set of interrupts
 *         enabled/disabled in the AINTC.
 *
 * \param    None
 *
 * \return   None
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
void IntMasterIRQDisable(void);

/**
 * \brief  Enables the processor FIQ only in CPSR. Makes the processor to
 *         respond to FIQs.  This does not affect the set of interrupts
 *         enabled/disabled in the AINTC.
 *
 * \param    None
 *
 * \return   None
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
void IntMasterFIQEnable(void);

/**
 * \brief  Disables the processor FIQ only in CPSR.Prevents the processor to
 *         respond to FIQs.  This does not affect the set of interrupts
 *         enabled/disabled in the AINTC.
 *
 * \param    None
 *
 * \return   None
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
void IntMasterFIQDisable(void);

/**
 * \brief   Returns the status of the interrupts FIQ and IRQ.
 *
 * \param    None
 *
 * \return   Status of interrupt as in CPSR.
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
uint32_t IntMasterStatusGet(void);

/**
 * \brief  Read and save the stasus and Disables the processor IRQ .
 *         Prevents the processor to respond to IRQs.
 *
 * \param    None
 *
 * \return   Current status of IRQ
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
uint8_t Intc_IntDisable(void);

/**
 * \brief  Restore the processor IRQ only status. This does not affect
 *          the set of interrupts enabled/disabled in the AINTC.
 *
 * \param    The status returned by the IntDisable fundtion.
 *
 * \return   None
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
void Intc_IntEnable(uint8_t status);

/**
 * \brief     This API is called when the CPU is aborted When the abort
 *            interrupt occurs , the control goes to the ISR which is registered
 *            using Intc_IntRegister else will result in infinite loop.
 *
 * \param     None.
 *
 * \return    None.
 *
 **/
void Intc_AbortHandler(void);

#ifdef __cplusplus
}
#endif
#endif

