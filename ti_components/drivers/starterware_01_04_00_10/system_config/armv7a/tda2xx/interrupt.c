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
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include "hw_types.h"
#include "soc.h"
#include "hw_mpu_intc_dist.h"
#include "hw_mpu_intc_phys.h"
#include "cpu.h"
#include "mpu_wugen.h"

/******************************************************************************
**                INTERNAL MACRO DEFINITIONS
******************************************************************************/
#define REG_IDX_SHIFT                  (0x05U)
#define REG_BIT_MASK                   (0x1FU)

#define NUM_GICD_ENABLE_REGS    6U
#define NUM_BYTES_REG           4U
#define BINARY_POINT_REG_VAL    0x03
#define PRIORITY_MASK_REG_VAL   0xF0

/**************** *************************************************************
**                 STATIC VARIABLE DEFINITIONS
******************************************************************************/
IntrFuncPtr fnRAMVectors[NUM_INTERRUPTS];
void       *argArray[NUM_INTERRUPTS] = {0};

/******************************************************************************
**                STATIC FUNCTION DECLARATIONS
******************************************************************************/
static void IntDefaultHandler(void *dummy);

/**********************************************************************
 *                   INTERNAL FUNCTION PROTOTYPES
 **********************************************************************/

extern void CopyVectorTable(void);

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
    uint32_t intActiveReg = 0;
    uint32_t i, j;

    /*Initialize vector table*/
    CopyVectorTable();

    /*
     * Disable forwarding of interrupts in GIC Distributor and CPU interface
     * Controller.
     */
    HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE + MPU_GICD_DCR, 0);
    HW_WR_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE + MPU_GICC_ICR, 0);

    /*
     * Disable all interrupts at startup
     */
    for (i = 0U; i < NUM_GICD_ENABLE_REGS; i++)
    {
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_ICER0 + (NUM_BYTES_REG * i)), 0xFFFFFFFFU);
    }

    /*
     * Disable all wakeup events at startup
     */
    MPU_WUGEN_Init();

    /*
     * Enable forwarding of both secure and non secure interrupts in GIC
     * Distributor and CPU interface
     * Controller.
     */
/*    HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE + MPU_GICD_DCR,
 *          (MPU_GICD_DCR__ENABLENS | MPU_GICD_DCR_ENABLES_MASK));
 *  HW_WR_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE + MPU_GICC_ICR,
 *          (MPU_GICC_ICR_ENABLES_MASK | MPU_GICC_ICR__ENABLENS |
 *                  MPU_GICC_ICR__ACKCTL | MPU_GICC_ICR__SBPR));
 */
    HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                MPU_GICD_DCR, MPU_GICD_DCR_ENABLES_MASK);
    HW_WR_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE +
                MPU_GICC_ICR, MPU_GICC_ICR_ENABLES_MASK);

    /* Search for any previously active interrupts and acknowledge them */
    for (i = 0; i < NUM_GICD_ENABLE_REGS; i++)
    {
        intActiveReg =
            HW_RD_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                        (MPU_GICD_ISACTIVER0 + (NUM_BYTES_REG * i)));

        if (intActiveReg)
        {
            for (j = 0U; j < 32U; j++)
            {
                if (intActiveReg & 0x1U)
                {
                    HW_WR_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE +
                                MPU_GICC_EOIR, (i * 32U) + j);
                }
                intActiveReg = intActiveReg >> 1;
            }
        }
    }

    /*
     * Clear any currently pending enabled interrupts
     *
     * Note: SGIs are always enabled
     */
    for (i = 0U; i < 4U; i++)
    {
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_CPENDSGIR0 + (NUM_BYTES_REG * i)), 0x01010101);
    }

    for (i = 0; i < NUM_GICD_ENABLE_REGS; i++)
    {
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_ICPR0 + (NUM_BYTES_REG * i)), 0xFFFFFFFFU);
    }

    /*
     * Clear all interrupt active status registers
     */
    for (i = 0; i < NUM_GICD_ENABLE_REGS; i++) {
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_ICACTIVER0 + (NUM_BYTES_REG * i)), 0xFFFFFFFFU);
    }

    /*
     * Set MPU0 as the target processor for all interrupts.
     *
     */
    for (i = 0U; i < 48U; i++) {
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_IPTR0 + (NUM_BYTES_REG * i)), 0x01010101);
    }

    /*
     * Initialize Binary Point Register
     */
    HW_WR_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE + MPU_GICC_BPR,
                BINARY_POINT_REG_VAL);

    /*
     * Initialize Priority mast register
     */
    HW_WR_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE + MPU_GICC_PMR,
                PRIORITY_MASK_REG_VAL);

    /*configure interrupts to level-sensitive interrupt type and 1-N model */
    for (i = 0U; i < 12U; i++)
    {
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_ICFR0 + (NUM_BYTES_REG * i)), 0xFFFFFFFFU);
    }
}

/**
 * \brief   This API assigns a priority to an interrupt and
 *          Priority 0 is the highest priority level.
 *
 *
 * \param   intrNum  - Interrupt number
 * \param   priority - Interrupt priority level
 *
 *
 * \return  None.
 *
 **/
void Intc_IntPrioritySet(uint16_t intrNum, uint16_t priority,
                         uint8_t hostIntRoute)
{
    uint32_t index, mask;

    if (intrNum < NUM_INTERRUPTS_EXTERNAL)
    {
        index = ((uint32_t) intrNum >> 2) + 1U;
        mask  = (uint32_t) intrNum % 4U;

        /*Sets the priority of shared peripheral interrupt*/
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_IPR0 + (NUM_BYTES_REG * index)),
                    ((priority & (uint32_t) 0xFF) << (mask * 8U)));
    }
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
    uint32_t index, mask, shift;
    uint32_t addr, target_cpus;

    if (intrNum < NUM_INTERRUPTS_EXTERNAL)
    {
        index = ((uint32_t) intrNum >> REG_IDX_SHIFT) + 1U;
        mask  = ((uint32_t) 1) << ((uint32_t) intrNum & REG_BIT_MASK);

        /* Enable the system interrupt for interrupt number passed */
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_ISER0 + (NUM_BYTES_REG * index)), mask);

        index = (uint32_t) intrNum >> 2;
        shift = ((uint32_t) ((uint32_t) intrNum & 3U) << 3);
        mask  = 0xffU << shift;
        addr  = SOC_INTC_MPU_DISTRIBUTOR_BASE +
                (MPU_GICD_IPTR8 + (NUM_BYTES_REG * index));
        target_cpus = HW_RD_FIELD32_RAW(addr,
                                        mask,
                                        shift);
        switch (target_cpus)
        {
            case 1U:
                MPU_WUGEN_0_Enable(intrNum);
                break;
            case 2U:
                MPU_WUGEN_1_Enable(intrNum);
                break;
            case 3U:
                MPU_WUGEN_0_Enable(intrNum);
                MPU_WUGEN_1_Enable(intrNum);
                break;
            default:
                MPU_WUGEN_0_Enable(intrNum);
                break;
        }
    }
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
    uint32_t index, mask, shift;
    uint32_t addr, target_cpus;

    if (intrNum < NUM_INTERRUPTS_EXTERNAL)
    {
        index = ((uint32_t) intrNum >> REG_IDX_SHIFT) + 1U;
        mask  = ((uint32_t) 1) << ((uint32_t) intrNum & REG_BIT_MASK);

        /* Disable the system interrupt for interrupt number passed */
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_ICER0 + (NUM_BYTES_REG * index)), mask);

        index = (uint32_t) intrNum >> 2;
        shift = ((uint32_t) ((uint32_t) intrNum & 3U) << 3);
        mask  = 0xffU << shift;
        addr  = SOC_INTC_MPU_DISTRIBUTOR_BASE +
                (MPU_GICD_IPTR8 + (NUM_BYTES_REG * index));
        target_cpus = HW_RD_FIELD32_RAW(addr,
                                        mask,
                                        shift);
        switch (target_cpus)
        {
            case 1U:
                MPU_WUGEN_0_Disable(intrNum);
                break;
            case 2U:
                MPU_WUGEN_1_Disable(intrNum);
                break;
            case 3U:
                MPU_WUGEN_0_Disable(intrNum);
                MPU_WUGEN_1_Disable(intrNum);
                break;
            default:
                MPU_WUGEN_0_Disable(intrNum);
                break;
        }
    }
}

/**
 * \brief   This API configures the interrupt passed to secure.
 *          In secure mode interrupts can be routed to either IRQ or FIQ.
 *
 * \param   intrNum  - Interrupt number
 *
 *
 * \return  None.
 *
 **/
void IntEnableSecureMode(uint32_t intrNum)
{
    uint32_t index, mask;
    uint32_t tmpVar;

    if (intrNum < NUM_INTERRUPTS_EXTERNAL)
    {
        index = (intrNum >> REG_IDX_SHIFT) + 1U;

        mask = ~((uint32_t) 1U << (intrNum & (uint32_t) 0x1fU));

        /* Enable secure mode for interrupt number passed */
        tmpVar = HW_RD_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                             (MPU_GICD_ISR0 + (NUM_BYTES_REG * index)));
        tmpVar &= mask;
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_ISR0 + (NUM_BYTES_REG * index)), tmpVar);
    }
}

/**
 * \brief   This API configures the interrupt passed to non-secure.
 *          In non-secure mode interrupts can only be routed to IRQ
 *
 * \param   intrNum  - Interrupt number
 *
 *
 * \return  None.
 *
 **/
void IntDisableSecureMode(uint32_t intrNum)
{
    uint32_t index, mask;
    uint32_t tmpVar;

    if (intrNum < NUM_INTERRUPTS_EXTERNAL)
    {
        index = (intrNum >> REG_IDX_SHIFT) + 1U;

        mask = (uint32_t) 1 << (intrNum & (uint32_t) 0x1f);

        /* Disable secure mode for interrupt number passed */
        tmpVar = HW_RD_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                             (MPU_GICD_ISR0 + (NUM_BYTES_REG * index)));
        tmpVar |= mask;
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_ISR0 + (NUM_BYTES_REG * index)), tmpVar);
    }
}

/**
 * \brief   This API sets the status of the interrupt passed to pending.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void IntSetPendingState(uint32_t intrNum)
{
    uint32_t index, mask;

    if (intrNum < NUM_INTERRUPTS_EXTERNAL)
    {
        index = (intrNum >> REG_IDX_SHIFT) + 1U;
        mask  = ((uint32_t) 1) << (intrNum & REG_BIT_MASK);

        /* Set the interrupt status to pending for the interrupt number passed*/
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_ISPR0 + (NUM_BYTES_REG * index)), mask);
    }
}

/**
 * \brief   This API clears the pending status of interrupt passed.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void IntClearPendingState(uint32_t intrNum)
{
    uint32_t index, mask;

    if (intrNum < NUM_INTERRUPTS_EXTERNAL)
    {
        index = (intrNum >> REG_IDX_SHIFT) + 1U;
        mask  = ((uint32_t) 1) << (intrNum & REG_BIT_MASK);

        /* Clear the interrupt pending status for the interrupt number passed */
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_ICPR0 + (NUM_BYTES_REG * index)), mask);
    }
}

/**
 * \brief   This API gets the pending status of interrupt passed.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  non zero value if pending.
 *          0              if not pending
 *
 **/
uint32_t IntGetPendingState(uint32_t intrNum)
{
    uint32_t state = 0U;
    uint32_t index, mask;

    if (intrNum < NUM_INTERRUPTS_EXTERNAL)
    {
        index = (intrNum >> REG_IDX_SHIFT) + 1U;
        mask  = ((uint32_t) 1) << (intrNum & REG_BIT_MASK);

        /* Clear the interrupt pending status for the interrupt number passed */
        state = (HW_RD_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                            (MPU_GICD_ISPR0 + (NUM_BYTES_REG * index))) & mask);
    }

    return (state);
}

/**
 * \brief   This API gets the active status of interrupt passed.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  non zero value if active.
 *          0              if not active
 *
 **/
uint32_t IntGetActiveState(uint32_t intrNum)
{
    uint32_t state = 0U;
    uint32_t index, mask;

    if (intrNum < NUM_INTERRUPTS_EXTERNAL)
    {
        index = (intrNum >> REG_IDX_SHIFT) + 1U;
        mask  = ((uint32_t) 1) << (intrNum & REG_BIT_MASK);

        /* Clear the interrupt pending status for the interrupt number passed */
        state = (HW_RD_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                            (MPU_GICD_ISACTIVER0 +
                             (NUM_BYTES_REG * index))) & mask);
    }

    return (state);
}

/**
 * \brief   This API clears the Active status of interrupt passed.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void IntClearActiveState(uint32_t intrNum)
{
    uint32_t index, mask;

    if (intrNum < NUM_INTERRUPTS_EXTERNAL)
    {
        index = (intrNum >> REG_IDX_SHIFT) + 1U;
        mask  = ((uint32_t) 1) << (intrNum & REG_BIT_MASK);

        /* Clear the interrupt pending status for the interrupt number passed */
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_ICACTIVER0 + (NUM_BYTES_REG * index)), mask);
    }
}

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
 *
 * \return  None.
 *
 **/
void IntSetTargetProcessor(uint32_t intrNum, uint32_t processorSelect)
{
    uint32_t index, mask;
    uint32_t tmpVar;

    if (intrNum < NUM_INTERRUPTS_EXTERNAL)
    {
        index = (intrNum >> 2) + 1U;
        mask  = intrNum % 4U;

        tmpVar = HW_RD_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                             (MPU_GICD_IPTR0 + (NUM_BYTES_REG * index)));
        tmpVar |= ((processorSelect & (uint32_t) 0x03) << (mask * 8U));
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_IPTR0 + (NUM_BYTES_REG * index)), tmpVar);
    }
}

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
 *
 *          must implement a mechanism to determine which processor handles an
 *          interrupt that is programmed to target more than one processor.
 *
 *          1-N Model :All processors receive the interrupt independently. When
 *          a processor acknowledges the interrupt, the interrupt pending state
 *          is cleared only for that processor. The interrupt remains pending
 *          for the other processors must
 *          implement a mechanism to determine which processor handles an
 *          interrupt that
 *          is programmed to target more than one processor.
 *
 *          Possible values are:
 *             0x0 - interrupt set to 1-N interrupt handling Model
 *             0x1 - interrupt set to N-N interrupt handling Model
 *
 * \return  None.
 *
 **/
void IntConfigTypenModel(uint32_t intrNum, uint32_t intType,
                         uint32_t intHandleModel)
{
    uint32_t index, mask;
    uint32_t tmpVar;

    if (intrNum < NUM_INTERRUPTS_EXTERNAL)
    {
        index = intrNum / 16U;
        mask  = intrNum % 16U;

        tmpVar = HW_RD_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                             (MPU_GICD_ICFR0 + (NUM_BYTES_REG * index)));
        tmpVar &= ~(MPU_GICD_ICFR0_INT_CONFIG_FIELD_0_MASK << (mask * 2U));
        tmpVar |= ((((intType & 0x01U) << 1) |
                    (intHandleModel & 0x01U)) << (mask * 2U));
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_ICFR0 + (NUM_BYTES_REG * index)), tmpVar);
    }
}

/***************************
 * CPU interface API's
 ***************************/

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
void IntEnableSecureFIQ(uint32_t intRoute)
{
    uint32_t tmpVar;
    if (AINTC_HOSTINT_ROUTE_FIQ == intRoute)
    {
        tmpVar  = HW_RD_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE + MPU_GICC_ICR);
        tmpVar |= MPU_GICC_ICR_FIQEN_MASK;
        HW_WR_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE + MPU_GICC_ICR, tmpVar);
    }
    else
    {
        tmpVar  = HW_RD_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE + MPU_GICC_ICR);
        tmpVar &= (~MPU_GICC_ICR_FIQEN_MASK);
        HW_WR_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE + MPU_GICC_ICR, tmpVar);
    }
}

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
void IntSetProirityMask(uint32_t priorityMask)
{
    HW_WR_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE +
                MPU_GICC_PMR, (priorityMask & MPU_GICC_PMR_PRIORITY_MASK));
}

/**
 * \brief   returns the priority mask level for the CPU interface.
 *
 * \return  prirityMask.
 *
 **/
uint32_t IntGetProirityMask(void)
{
    return (HW_RD_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE +
                        MPU_GICC_PMR) & MPU_GICC_PMR_PRIORITY_MASK);
}

/**
 * \brief   This API returns the priority value of the highest priority
 *
 *          interrupt that is active on the CPU interface
 *
 * \return  priority value of the highest priority interrupt
 *          that is active on the CPU interface
 *
 **/
uint32_t IntGetActivePriority(void)
{
    return (HW_RD_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE + MPU_GICC_RPR));
}

/**
 * \brief  returns the interrupt ID of the highest priority pending interrupt
 *
 * \return interrupt ID of the highest priority pending interrupt
 *
 */
uint32_t IntGetPendingIntNum(void)
{
    return (HW_RD_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE +
                        MPU_GICC_HPIR) & MPU_GICC_HPIR_PENDINTID_MASK);
}

/**
 * \brief  On a multiprocessor implementation, if the PENDINTID field returns
 *         the ID of an SGI, this field contains the CPUID value for that
 *         interrupt. This identifies the processor that generated the
 *         interrupt.
 *
 * \return CPUID of the highest priority pending interrupt
 *
 */
uint32_t IntGetPendingCPUID(void)
{
    uint32_t tmpVar;
    tmpVar = HW_RD_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE + MPU_GICC_HPIR);
    tmpVar = (tmpVar & MPU_GICC_HPIR_CPUID_MASK) >> MPU_GICC_HPIR_CPUID_SHIFT;
    return (tmpVar);
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
void Intc_AbortHandler(void)
{
    if (0U != fnRAMVectors[INTERNAL_INTERRUPT_ABORT_ID])
    {
        fnRAMVectors[INTERNAL_INTERRUPT_ABORT_ID]
            (argArray[INTERNAL_INTERRUPT_ABORT_ID]);
    }
    else
    {
        /* Go into an infinite loop.*/
        volatile uint32_t loop = 1U;
        while (1U == loop)
        {
            ;
        }
    }
}

/********************************** End Of File ******************************/