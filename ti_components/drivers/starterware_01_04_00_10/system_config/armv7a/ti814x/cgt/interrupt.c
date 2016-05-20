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
 *  \file   interrupt.c
 *
 *  \brief  Interrupt related APIs.
 *
 *   This file contains the APIs for configuring AINTC
 */

#include "stdint.h"
#include "stddef.h"
#include "hw_intc.h"
#include "interrupt.h"
#include "hw_types.h"
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include "soc.h"
#include "soc_defines.h"
#include "cpu.h"

/******************************************************************************
**                INTERNAL MACRO DEFINITIONS
******************************************************************************/
#define REG_IDX_SHIFT                  ((uint32_t) 0x05)
#define REG_BIT_MASK                   (0x1FU)
#define NUM_INTERRUPTS                 (128U)

extern void CopyVectorTable(void);

/**************** *************************************************************
**                 STATIC VARIABLE DEFINITIONS
******************************************************************************/
IntrFuncPtr fnRAMVectors[NUM_INTERRUPTS];
void       *argArray[NUM_INTERRUPTS] = {0};

/******************************************************************************
**                STATIC FUNCTION DECLARATIONS
******************************************************************************/
static void IntDefaultHandler(void *dummy);

/******************************************************************************
**                     API FUNCTION DEFINITIONS
******************************************************************************/

/**
 *
 * The Default Interrupt Handler.
 *
 * This is the default interrupt handler for all interrupts.  It simply loops
 * forever so that the system state is preserved for observation by a
 * debugger.  Since interrupts should be disabled before unregistering the
 * corresponding handler, this should never be called.
 *
 *
 **/
static void IntDefaultHandler(void *dummy)
{
    /* Go into an infinite loop.*/
    volatile uint32_t loop = 1U;
    while (1U == loop)
    {
        ;
    }
}

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
void Intc_IntRegister(uint16_t intrNum, IntrFuncPtr fptr, void *fun_arg)
{
    /* Assign ISR */
    fnRAMVectors[intrNum] = fptr;
    argArray[intrNum]     = fun_arg;
}

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
void Intc_IntUnregister(uint16_t intrNum)
{
    uint32_t IntDefaultHandler_t = (uint32_t) (&IntDefaultHandler);
    /* Assign default ISR */
    fnRAMVectors[intrNum] = (IntrFuncPtr) IntDefaultHandler_t;
    argArray[intrNum]     = NULL;
}

/**
 * \brief   This API is used to initialize the interrupt controller. This API
 *          shall be called before using the interrupt controller.
 *
 * \param   None
 *
 * \return  None.
 *
 **/
void Intc_Init(void)
{
    /*Initialize vector table*/
    CopyVectorTable();

    /* Reset the ARM interrupt controller */
    HW_WR_REG32(SOC_AINTC_REGS + INTC_SYSCONFIG, INTC_SYSCONFIG_SOFTRESET);

    /* Wait for the reset to complete */
    while ((HW_RD_REG32(SOC_AINTC_REGS + INTC_SYSSTATUS)
            & INTC_SYSSTATUS_RESETDONE) != INTC_SYSSTATUS_RESETDONE)
    {
        ;
    }
    /* Enable any interrupt generation by setting priority threshold */
    HW_WR_REG32(SOC_AINTC_REGS + INTC_THRESHOLD,
                INTC_THRESHOLD_PRIORITYTHRESHOLD);
}

/**
 * \brief   This API assigns a priority to an interrupt and routes it to
 *          either IRQ or to FIQ. Priority 0 is the highest priority level
 *          Among the host interrupts, FIQ has more priority than IRQ.
 *
 * \param   intrNum  - Interrupt number
 * \param   priority - Interrupt priority level
 * \param   hostIntRoute - The host interrupt IRQ/FIQ to which the interrupt
 *                         is to be routed.
 *     'priority' can take any value from 0 to 127, 0 being the highest and
 *     127 being the lowest priority.
 *
 *     'hostIntRoute' can take one of the following values \n
 *             AINTC_HOSTINT_ROUTE_IRQ - To route the interrupt to IRQ \n
 *             AINTC_HOSTINT_ROUTE_FIQ - To route the interrupt to FIQ
 *
 * \return  None.
 *
 **/
void Intc_IntPrioritySet(uint16_t intrNum, uint16_t priority,
                         uint8_t hostIntRoute)
{
    HW_WR_REG32(SOC_AINTC_REGS + INTC_ILR(intrNum),
                (((uint32_t) priority << INTC_ILR_PRIORITY_SHIFT)
                 & INTC_ILR_PRIORITY)
                | hostIntRoute);
}

/**
 * \brief   This API enables the system interrupt in AINTC. However, for
 *          the interrupt generation, make sure that the interrupt is
 *          enabled at the peripheral level also.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void Intc_SystemEnable(uint16_t intrNum)
{
    /* Disable the system interrupt in the corresponding MIR_CLEAR register */
    HW_WR_REG32(SOC_AINTC_REGS + INTC_MIR_CLEAR(intrNum >> REG_IDX_SHIFT),
                ((uint32_t) 0x01 << (intrNum & REG_BIT_MASK)));
}

/**
 * \brief   This API disables the system interrupt in AINTC.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void Intc_SystemDisable(uint16_t intrNum)
{
    /* Enable the system interrupt in the corresponding MIR_SET register */
    HW_WR_REG32(SOC_AINTC_REGS + INTC_MIR_SET(intrNum >> REG_IDX_SHIFT),
                ((uint32_t) 0x01 << (intrNum & REG_BIT_MASK)));
}

/**
 * \brief   Sets the interface clock to be free running
 *
 * \param   None.
 *
 * \return  None.
 *
 **/
void IntIfClkFreeRunSet(void)
{
    uint32_t tmpVar;
    tmpVar  = HW_RD_REG32(SOC_AINTC_REGS + INTC_SYSCONFIG);
    tmpVar &= (~INTC_SYSCONFIG_AUTOIDLE);
    HW_WR_REG32(SOC_AINTC_REGS + INTC_SYSCONFIG, tmpVar);
}

/**
 * \brief   When this API is called,  automatic clock gating strategy is applied
 *          based on the interface bus activity.
 *
 * \param   None.
 *
 * \return  None.
 *
 **/
void IntIfClkAutoGateSet(void)
{
    uint32_t tmpVar;
    tmpVar  = HW_RD_REG32(SOC_AINTC_REGS + INTC_SYSCONFIG);
    tmpVar |= INTC_SYSCONFIG_AUTOIDLE;
    HW_WR_REG32(SOC_AINTC_REGS + INTC_SYSCONFIG, tmpVar);
}

/**
 * \brief   Reads the active IRQ number.
 *
 * \param   None
 *
 * \return  Active IRQ number.
 *
 **/
uint32_t IntActiveIrqNumGet(void)
{
    return (HW_RD_REG32(SOC_AINTC_REGS + INTC_SIR_IRQ) & INTC_SIR_IRQ_ACTIVEIRQ);
}

/**
 * \brief   Reads the active FIQ number.
 *
 * \param   None
 *
 * \return  Active FIQ number.
 *
 **/
uint32_t IntActiveFiqNumGet(void)
{
    return (HW_RD_REG32(SOC_AINTC_REGS + INTC_SIR_FIQ) & INTC_SIR_FIQ_ACTIVEFIQ);
}

/**
 * \brief   Reads the spurious IRQ Flag. Spurious IRQ flag is reflected in both
 *          SIR_IRQ and IRQ_PRIORITY registers of the interrupt controller.
 *
 * \param   None
 *
 * \return  Spurious IRQ Flag.
 *
 **/
uint32_t IntSpurIrqFlagGet(void)
{
    return ((HW_RD_REG32(SOC_AINTC_REGS + INTC_SIR_IRQ)
             & INTC_SIR_IRQ_SPURIOUSIRQ)
            >> INTC_SIR_IRQ_SPURIOUSIRQ_SHIFT);
}

/**
 * \brief   Reads the spurious FIQ Flag. Spurious FIQ flag is reflected in both
 *          SIR_FIQ and FIQ_PRIORITY registers of the interrupt controller.
 *
 * \param   None
 *
 * \return  Spurious IRQ Flag.
 *
 **/
uint32_t IntSpurFiqFlagGet(void)
{
    return ((HW_RD_REG32(SOC_AINTC_REGS + INTC_SIR_FIQ)
             & INTC_SIR_FIQ_SPURIOUSFIQ)
            >> INTC_SIR_FIQ_SPURIOUSFIQ_SHIFT);
}

/**
 * \brief   Enables protection mode for the interrupt controller register
 *          access.
 *          When the protection is enabled, the registers will be accessible
 *          only in privileged mode of the CPU.
 *
 * \param   None
 *
 * \return  None
 *
 **/
void IntProtectionEnable(void)
{
    HW_WR_REG32(SOC_AINTC_REGS + INTC_PROTECTION, INTC_PROTECTION_PROTECTION);
}

/**
 * \brief   Disables protection mode for the interrupt controller register
 *          access.
 *          When the protection is disabled, the registers will be accessible
 *          in both unprivileged and privileged mode of the CPU.
 *
 * \param   None
 *
 * \return  None
 *
 **/
void IntProtectionDisable(void)
{
    uint32_t tmpVar;
    tmpVar  = HW_RD_REG32(SOC_AINTC_REGS + INTC_PROTECTION);
    tmpVar &= (~INTC_PROTECTION_PROTECTION);
    HW_WR_REG32(SOC_AINTC_REGS + INTC_PROTECTION, tmpVar);
}

/**
 * \brief   Enables the free running of input synchronizer clock
 *
 * \param   None
 *
 * \return  None
 *
 **/
void IntSyncClkFreeRunSet(void)
{
    uint32_t tmpVar;
    tmpVar  = HW_RD_REG32(SOC_AINTC_REGS + INTC_IDLE);
    tmpVar &= (~INTC_IDLE_TURBO);
    HW_WR_REG32(SOC_AINTC_REGS + INTC_IDLE, tmpVar);
}

/**
 * \brief   When this API is called, Input synchronizer clock is auto-gated
 *          based on interrupt input activity
 *
 * \param   None
 *
 * \return  None
 *
 **/
void IntSyncClkAutoGateSet(void)
{
    uint32_t tmpVar;
    tmpVar  = HW_RD_REG32(SOC_AINTC_REGS + INTC_IDLE);
    tmpVar |= INTC_IDLE_TURBO;
    HW_WR_REG32(SOC_AINTC_REGS + INTC_IDLE, tmpVar);
}

/**
 * \brief   Enables the free running of functional clock
 *
 * \param   None
 *
 * \return  None
 *
 **/
void IntFuncClkFreeRunSet(void)
{
    uint32_t tmpVar;
    tmpVar  = HW_RD_REG32(SOC_AINTC_REGS + INTC_IDLE);
    tmpVar |= INTC_IDLE_FUNCIDLE;
    HW_WR_REG32(SOC_AINTC_REGS + INTC_IDLE, tmpVar);
}

/**
 * \brief   When this API is called, functional clock gating strategy
 *          is applied.
 *
 * \param   None
 *
 * \return  None
 *
 **/
void IntFuncClkAutoGateSet(void)
{
    uint32_t tmpVar;
    tmpVar  = HW_RD_REG32(SOC_AINTC_REGS + INTC_IDLE);
    tmpVar &= (~INTC_IDLE_FUNCIDLE);
    HW_WR_REG32(SOC_AINTC_REGS + INTC_IDLE, tmpVar);
}

/**
 * \brief   Returns the currently active IRQ priority level.
 *
 * \param   None
 *
 * \return  Current IRQ priority
 *
 **/
uint32_t IntCurrIrqPriorityGet(void)
{
    return (HW_RD_REG32(SOC_AINTC_REGS + INTC_IRQ_PRIORITY)
            & INTC_IRQ_PRIORITY_IRQPRIORITY);
}

/**
 * \brief   Returns the currently active FIQ priority level.
 *
 * \param   None
 *
 * \return  Current FIQ priority
 *
 **/
uint32_t IntCurrFiqPriorityGet(void)
{
    return (HW_RD_REG32(SOC_AINTC_REGS + INTC_FIQ_PRIORITY)
            & INTC_FIQ_PRIORITY_FIQPRIORITY);
}

/**
 * \brief   Returns the priority threshold.
 *
 * \param   None
 *
 * \return  Priority threshold value.
 *
 **/
uint32_t IntPriorityThresholdGet(void)
{
    return (HW_RD_REG32(SOC_AINTC_REGS + INTC_THRESHOLD)
            & INTC_THRESHOLD_PRIORITYTHRESHOLD);
}

/**
 * \brief   Sets the given priority threshold value.
 *
 * \param   threshold - Priority threshold value
 *
 *      'threshold' can take any value from 0x00 to 0x7F. To disable
 *      priority threshold, write 0xFF.
 *
 * \return  None.
 *
 **/
void IntPriorityThresholdSet(uint32_t threshold)
{
    HW_WR_REG32(SOC_AINTC_REGS + INTC_THRESHOLD,
                threshold & INTC_THRESHOLD_PRIORITYTHRESHOLD);
}

/**
 * \brief   Returns the raw interrupt status before masking.
 *
 * \param   intrNum - the system interrupt number.
 *
 * \return  TRUE - if the raw status is set \n
 *          FALSE - if the raw status is not set.
 *
 **/
uint32_t IntRawStatusGet(uint32_t intrNum)
{
    return (((uint32_t) 0 ==
             ((HW_RD_REG32(SOC_AINTC_REGS + INTC_ITR(intrNum >> REG_IDX_SHIFT))
               >> (intrNum &
                   REG_BIT_MASK)) & (uint32_t) 0x01)) ? FALSE : TRUE);
}

/**
 * \brief   Sets software interrupt for the given interrupt number.
 *
 * \param   intrNum - the system interrupt number, for which software interrupt
 *                    to be generated
 *
 * \return  None
 *
 **/
void IntSoftwareIntSet(uint32_t intrNum)
{
    /* Enable the software interrupt in the corresponding ISR_SET register */
    HW_WR_REG32(SOC_AINTC_REGS + INTC_ISR_SET(intrNum >> REG_IDX_SHIFT),
                ((uint32_t) 0x01 << (intrNum & REG_BIT_MASK)));
}

/**
 * \brief   Clears the software interrupt for the given interrupt number.
 *
 * \param   intrNum - the system interrupt number, for which software interrupt
 *                    to be cleared.
 *
 * \return  None
 *
 **/
void IntSoftwareIntClear(uint32_t intrNum)
{
    /* Disable the software interrupt in the corresponding ISR_CLEAR register */
    HW_WR_REG32(SOC_AINTC_REGS + INTC_ISR_CLEAR(intrNum >> REG_IDX_SHIFT),
                ((uint32_t) 0x01 << (intrNum & REG_BIT_MASK)));
}

/**
 * \brief   Returns the IRQ status after masking.
 *
 * \param   intrNum - the system interrupt number
 *
 * \return  TRUE - if interrupt is pending \n
 *          FALSE - in no interrupt is pending
 *
 **/
uint32_t IntPendingIrqMaskedStatusGet(uint32_t intrNum)
{
    return (((uint32_t) 0 ==
             (HW_RD_REG32(SOC_AINTC_REGS +
                          INTC_PENDING_IRQ(intrNum >> REG_IDX_SHIFT))
              >> (((intrNum &
                    REG_BIT_MASK)) & (uint32_t) 0x01))) ? FALSE : TRUE);
}

/**
 * \brief   Returns the FIQ status after masking.
 *
 * \param   intrNum - the system interrupt number
 *
 * \return  TRUE - if interrupt is pending \n
 *          FALSE - in no interrupt is pending
 *
 **/
uint32_t IntPendingFiqMaskedStatusGet(uint32_t intrNum)
{
    return (((uint32_t) 0 ==
             (HW_RD_REG32(SOC_AINTC_REGS +
                          INTC_PENDING_FIQ(intrNum >> REG_IDX_SHIFT))
              >> (((intrNum &
                    REG_BIT_MASK)) & (uint32_t) 0x01))) ? FALSE : TRUE);
}

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
void IntMasterIRQEnable(void)
{
    /* Enable IRQ in CPSR.*/
    CPUirqe();
}

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
void IntMasterIRQDisable(void)
{
    /* Disable IRQ in CPSR.*/
    CPUirqd();
}

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
void IntMasterFIQEnable(void)
{
    /* Enable FIQ in CPSR.*/
    CPUfiqe();
}

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
void IntMasterFIQDisable(void)
{
    /* Disable FIQ in CPSR.*/
    CPUfiqd();
}

/**
 * \brief   Returns the status of the interrupts FIQ and IRQ.
 *
 * \param    None
 *
 * \return   Status of interrupt as in CPSR.
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
uint32_t IntMasterStatusGet(void)
{
    return CPUIntStatus();
}

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
uint8_t Intc_IntDisable(void)
{
    uint8_t status;

    /* Reads the current status.*/
    status = (uint8_t) (IntMasterStatusGet() & 0xFFU);

    /* Disable the Interrupts.*/
    IntMasterIRQDisable();

    return status;
}

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
void Intc_IntEnable(uint8_t status)
{
    if ((status & 0x80U) == 0)
    {
        IntMasterIRQEnable();
    }
}

/********************************** End Of File ******************************/

