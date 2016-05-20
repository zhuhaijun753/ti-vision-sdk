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
#include "stdint.h"
#include "stddef.h"
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include "hw_types.h"
#include "interrupt.h"
#ifndef TI814X_FAMILY_BUILD
#include "ipu_wugen.h"
#endif

#define M4_NUM_NVIC_INTERNAL   (16U)
#define M4_NUM_NVIC_EXTERNAL   (128U)
#define M4_IRQ_EN_SET_START    (0xE000E100U)
#define M4_IRQ_EN_SET_END      (M4_IRQ_EN_SET_START + \
                                (M4_NUM_NVIC_EXTERNAL >> 5) * 4U)
#define M4_IRQ_EN_CLR_START    (0xE000E180U)
#define M4_IRQ_EN_CLR_END      (M4_IRQ_EN_CLR_START + \
                                (M4_NUM_NVIC_EXTERNAL >> 5) * 4U)
#define M4_IRQ_ACTIVE_START    (0xE000E300U)
#define M4_IRQ_ACTIVE_END      (M4_IRQ_ACTIVE_START + \
                                (M4_NUM_NVIC_EXTERNAL >> 5) * 4U)

#define M4_INT_CTL_STATE    (0xE000ED04U)

void       *argArray[M4_NUM_NVIC_EXTERNAL] = {0};
IntrFuncPtr fxnArray[M4_NUM_NVIC_EXTERNAL] = {0};
uint32_t    ieCookie[M4_NUM_NVIC_EXTERNAL >> 5] = {0};

/******************************************************************************
**                FUNCTION DECLARATIONS
******************************************************************************/
#ifdef __cplusplus
#pragma CODE_SECTION(".intc_text");
#else
#pragma CODE_SECTION(HF, ".intc_text");
#endif  /* #ifdef __cplusplus */
void HF(void);
/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif
static void IntDefaultHandler(void *dummy);
#ifdef __cplusplus
}
#endif

static void masterIsr(void);
void clearIntr(uint32_t intNum);

/******************************************************************************
**
******************************************************************************/

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */

extern "C"
{
#endif
extern const volatile uint32_t vector_table[NUM_ELEMENTS_VECTOR_TABLE];
extern int32_t _c_int00(void);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

void HF(void)
{
    volatile int32_t a;
    a = 0;
}

#ifdef __cplusplus
#pragma DATA_SECTION(".intvecs");
#else
#pragma DATA_SECTION(vector_table, ".intvecs");
#endif  /* #ifdef __cplusplus */

const volatile uint32_t vector_table[NUM_ELEMENTS_VECTOR_TABLE] =
{
    0,                    /* Stack_base + STACK_SIZE*4 */
    (uint32_t) &_c_int00, /* ResetHandler               */
    (uint32_t) &HF,
    (uint32_t) &HF,       /* Hard Fault Handler */
    (uint32_t) &HF,       /* Populate if using MemManage(MPU)  */
    (uint32_t) &HF,       /* Populate if using Bus fault       */
    (uint32_t) &HF,       /* Populate if using Usage Fault     */
    (uint32_t) &HF,
    (uint32_t) &HF,
    (uint32_t) &HF,
    (uint32_t) &HF, /*   Reserved slots                          */
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF
};

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
 *
 * Master ISR handler.
 *
 * Reads the active interrupt number from  Interrupt control state register .
 * Call the registered ISR function with arguments
 *
 *
 **/

static void masterIsr(void)
{
    IntrFuncPtr        fxnPtr;
    uint32_t           regVal;
    volatile uint32_t  intNum;
    volatile uint32_t *intCtlStateAddr = (uint32_t *) M4_INT_CTL_STATE;
    regVal = *(volatile uint32_t *) intCtlStateAddr;
    /* 9 LSBits of Interrupt control state register contain
     * the actual interrupt number*/
    intNum = regVal & 0x1FFU;
    if (fxnArray[intNum] != NULL)
    {
        fxnPtr = fxnArray[intNum];
        fxnPtr(argArray[intNum]);
    }
}

void clearIntr(uint32_t intNum) {}

void Intc_Init(void)
{
    volatile int32_t a;
    a = 0;
    if (0 != a)
    {
        volatile int32_t b = vector_table[0];
    }
#ifndef TI814X_FAMILY_BUILD
    IPU_WUGEN_Init();
#endif

    /* TODO - Check for Cortex-M3 Interrupt controller( Reset & Init) */
}

/**
 * \brief    Registers an interrupt Handler in the interrupt vector table for
 *           system interrupts.
 *           Registers the same interrupt in IPU WUGEN
 *
 **/
void Intc_IntRegister(uint16_t intrNum, IntrFuncPtr fptr, void *fun_arg)
{
    uint32_t tempIntr = (uint32_t) intrNum * 4U;
    *(volatile uint32_t *) (tempIntr) = (uint32_t) &masterIsr;
    fxnArray[intrNum] = fptr;
    argArray[intrNum] = fun_arg;
#ifndef TI814X_FAMILY_BUILD
    if (intrNum > IPU_WUGEN_NUM_INTR_INTERNAL)
    {
        IPU_WUGEN_Enable(intrNum);
    }
#endif
}

/**
 * \brief   Unregisters an interrupt
 *
 **/
void Intc_IntUnregister(uint16_t intrNum)
{
    fxnArray[intrNum] = &IntDefaultHandler;
    argArray[intrNum] = NULL;
#ifndef TI814X_FAMILY_BUILD
    if (intrNum > IPU_WUGEN_NUM_INTR_INTERNAL)
    {
        IPU_WUGEN_Disable(intrNum);
    }
#endif
}

/**
 * \brief   This API assigns a priority to an interrupt and routes it to
 *          either IRQ or to FIQ. Priority 0 is the highest priority level
 *          Among the host interrupts, FIQ has more priority than IRQ.
 **/
void Intc_IntPrioritySet(uint16_t intrNum, uint16_t priority,
                         uint8_t hostIntRoute)
{
    /* Dummy function in Cortex - M3 */
}

/**
 * \brief   This API enables the system interrupt in INTC. However, for
 *          the interrupt generation, make sure that the interrupt is
 *          enabled at the peripheral level also.
 **/
void Intc_SystemEnable(uint16_t intrNum)
{
    volatile uint32_t *irqEnSetAddr = (uint32_t *) M4_IRQ_EN_SET_START;

    intrNum -= M4_NUM_NVIC_INTERNAL;

    while ((intrNum >= 32U) && (irqEnSetAddr < (uint32_t *) M4_IRQ_ACTIVE_END))
    {
        intrNum -= 32U;
        irqEnSetAddr++;
    }
    *(volatile uint32_t *) (irqEnSetAddr) = ((uint32_t) 1 << intrNum);
}

/**
 * \brief   This API disables the system interrupt in INTC.
 **/
void Intc_SystemDisable(uint16_t intrNum)
{
    volatile uint32_t *irqEnClrAddr = (uint32_t *) M4_IRQ_EN_CLR_START;

    intrNum -= M4_NUM_NVIC_INTERNAL;

    while ((intrNum > 32U) && (irqEnClrAddr < (uint32_t *) M4_IRQ_EN_CLR_END))
    {
        intrNum -= 32U;
        irqEnClrAddr++;
    }

    *(volatile uint32_t *) (irqEnClrAddr) = ((uint32_t) 1 << intrNum);
}

/**
 * \brief  Read and save the stasus and Disables the processor IRQ .
 *         Prevents the processor to respond to IRQs.
 **/
uint8_t Intc_IntDisable(void)
{
    asm (" CPSID I");
    return 0U;
}

/**
 * \brief  Restore the processor IRQ only status. This does not affect
 *          the set of interrupts enabled/disabled in the AINTC.
 **/
void Intc_IntEnable(uint8_t status)
{
    asm (" CPSIE I");
}

