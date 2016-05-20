/**
 *  \file  inth.c
 *
 *  \brief Interrupt handling utilities
 *
 *  \copyright Copyright (C) 2014 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

/* =============================================================================
 *   Copyright (C) 2014 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ===========================================================================*/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "stdint.h"
#include "stddef.h"
#include "arp32_wugen.h"
#include "inth.h"
#include "hw_types.h"
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include "soc.h"
#include "intctl.h"
#include "hw_eve_control.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

extern int32_t  NMI_IRQ_ASM1(void);
extern int32_t  NMI_IRQ_ASM2(void);

/* number of T16 interrupt inputs 0..127 */
#define INTH_INT_TABLE_SIZE     128U

#ifdef VME_PLATFORM
/* number of T16 interrupt inputs 0..31 */
#define INTH_INT_TABLE_SIZE     32U
#endif

/* number max of interrupt handlers */
#define INTH_INT_NUM_MAX          (INTH_INT_TABLE_SIZE - 1U)

/* array of interrupt handlers */
/* #pragma DATA_SECTION(inth_IrqHandler, ".dmem_int_sec")*/
static INTH_Handler_t inth_IrqHandler[INTH_INT_TABLE_SIZE];

/* array of interrupt counter */
static uint32_t       inth_IrqCount[INTH_INT_TABLE_SIZE];

/* This is used but, referenced  from intvect.asm */
uint32_t IRQ_intTable[8];

uint32_t lock_en = 0;

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

void INTH_EnableLock(void);
interrupt void NMI_IRQ(void);
interrupt void SWI_IRQ(void);
interrupt void INTH_IRQ4(void);
interrupt void INTH_IRQ5(void);
interrupt void INTH_IRQ6(void);
interrupt void INTH_IRQ7(void);

interrupt void INTH_IRQ8(void);
interrupt void INTH_IRQ9(void);
interrupt void INTH_IRQ10(void);
interrupt void INTH_IRQ11(void);
interrupt void INTH_IRQ12(void);
interrupt void INTH_IRQ13(void);
interrupt void INTH_IRQ14(void);
interrupt void INTH_IRQ15(void);

void NMI_IRQInternalFunction(void);

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

int32_t EVE_INTH_InterruptSetup(const uint8_t              intVector,
                                const uint32_t             intHandler,
                                const INTH_InterruptKind_t intKind,
                                const INTH_Priority_t      intPriority)
{
    int32_t returnCode = STW_SOK;

    /* Call interrupt Controler Configuration */
    returnCode = EVE_INTCTL_LevelInit(SOC_EVE_SYSTEM_BASE,
                                      intVector,
                                      (INTCTL_InterruptKind_t) intKind,
                                      (INTCTL_Priority_t) intPriority);
    if (returnCode == STW_SOK)
    {
        /* reset counter and install handler */
        inth_IrqCount[intVector]   = 0;
        inth_IrqHandler[intVector] = (INTH_Handler_t) intHandler;
        ARP32_WUGEN_IRQ_Enable((uint16_t) intVector);
    }

    return returnCode;
} /* EVE_INTH_InterruptSetup() */

int32_t EVE_INTH_InterruptEnable(const uint8_t intVector)
{
    int32_t returnCode = STW_SOK;

    returnCode = EVE_INTCTL_OneITEnable(SOC_EVE_SYSTEM_BASE,
                                        intVector,
                                        INTCTL_ENABLE);

    return returnCode;
} /* EVE_INTH_InterruptEnable() */

int32_t EVE_INTH_InterruptDisable(const uint8_t intVector)
{
    int32_t returnCode = STW_SOK;

    returnCode = EVE_INTCTL_OneITEnable(SOC_EVE_SYSTEM_BASE,
                                        intVector,
                                        INTCTL_DISABLE);

    return returnCode;
} /* EVE_INTH_InterruptDisable() */

void INTH_EnableLock(void)
{
    lock_en = 1U;
}

interrupt void NMI_IRQ(void)
{
    asm ("       STRF    R7, R0             ");
    asm ("       MVC    LSA0, R0            ");
    asm ("       MVC     LEA0, R1           ");
    asm ("       MVC     LCNT0, R2          ");
    asm ("       MVC     LSA1, R3           ");
    asm ("       MVC     LEA1, R4           ");
    asm ("       MVC     LCNT1, R5          ");
    asm ("       MVC     LCNT0RLD, R6       ");
    asm ("       STRF    R6, R0             ");

    asm ("       CALL    NMI_IRQInternalFunction");

    /*   return; */
    asm ("    LDRF    R0, R6       ");
    asm ("    MVC     R0, LSA0     ");
    asm ("    MVC     R1, LEA0     ");
    asm ("    MVC     R2, LCNT0    ");
    asm ("    MVC     R3, LSA1     ");
    asm ("    MVC     R4, LEA1     ");
    asm ("    MVC     R5, LCNT1    ");
    asm ("    MVC     R6, LCNT0RLD ");
    asm ("    LDRF    R0, R7       ");
    asm ("     NOP                  ");
    asm ("     NOP                  ");
    asm ("     ADD 4, SP            ");
    asm ("     BNRP                 ");
    asm ("     NOP                  ");
    asm ("     NOP                  ");
}

interrupt void SWI_IRQ(void)
{
    return;
}

interrupt void INTH_IRQ4(void)
{
    if (lock_en == 1U)
    {
        HW_WR_REG32((SOC_EVE_SYSTEM_BASE + MMR_LOCK_4), 0xC7EAD20AU);
    }

    uint16_t lvInterrupt = 0;
    /* Get pending interrupt */
    EVE_INTCTL_Ack(SOC_EVE_SYSTEM_BASE, /* BaseAddress */
                   INTCTL_INT4,         /* Interrupt Priority */
                   &lvInterrupt);       /* Interrupt Id */

    /* Enable for Valid next IRQ*/
    EVE_INTCTL_NextValid(SOC_EVE_SYSTEM_BASE, /* BaseAddress */
                         INTCTL_INT4);        /* Interrupt Priority */

    /* increment interrupt counter */
    inth_IrqCount[lvInterrupt]++;

    /* if an interrupt handler has been registered */
    if (inth_IrqHandler[lvInterrupt] != NULL)
    {
        /* call regitered interrupt handler */
        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }

    if (lock_en == 1U)
    {
        HW_WR_REG32((SOC_EVE_SYSTEM_BASE + MMR_LOCK_4), 0x12345678U);
    }

    return;
}

interrupt void INTH_IRQ5(void)
{
    if (lock_en == 1U)
    {
        HW_WR_REG32((SOC_EVE_SYSTEM_BASE + MMR_LOCK_4), 0xC7EAD20AU);
    }

    uint16_t lvInterrupt = 0;
    /* Get pending interrupt */
    EVE_INTCTL_Ack(SOC_EVE_SYSTEM_BASE, /* BaseAddress */
                   INTCTL_INT5,         /* Interrupt Priority */
                   &lvInterrupt);       /* Interrupt Id */

    /* Enable for Valid next IRQ*/
    EVE_INTCTL_NextValid(SOC_EVE_SYSTEM_BASE, /* BaseAddress */
                         INTCTL_INT5);        /* Interrupt Priority */

    /* increment interrupt counter */
    inth_IrqCount[lvInterrupt]++;

    /* if an interrupt handler has been registered */
    if (inth_IrqHandler[lvInterrupt] != NULL)
    {
        /* call regitered interrupt handler */
        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }

    if (lock_en == 1U)
    {
        HW_WR_REG32((SOC_EVE_SYSTEM_BASE + MMR_LOCK_4), 0x12345678U);
    }

    return;
}

interrupt void INTH_IRQ6(void)
{
    if (lock_en == 1U)
    {
        HW_WR_REG32((SOC_EVE_SYSTEM_BASE + MMR_LOCK_4), 0xC7EAD20AU);
    }

    uint16_t lvInterrupt = 0;
    /* Get pending interrupt */
    EVE_INTCTL_Ack(SOC_EVE_SYSTEM_BASE, /* BaseAddress */
                   INTCTL_INT6,         /* Interrupt Priority */
                   &lvInterrupt);       /* Interrupt Id */

    /* Enable for Valid next IRQ*/
    EVE_INTCTL_NextValid(SOC_EVE_SYSTEM_BASE, /* BaseAddress */
                         INTCTL_INT6);        /* Interrupt Priority */

    /* increment interrupt counter */
    inth_IrqCount[lvInterrupt]++;

    /* if an interrupt handler has been registered */
    if (inth_IrqHandler[lvInterrupt] != NULL)
    {
        /* call regitered interrupt handler */
        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }

    if (lock_en == 1U)
    {
        HW_WR_REG32((SOC_EVE_SYSTEM_BASE + MMR_LOCK_4), 0x12345678U);
    }

    return;
}

interrupt void INTH_IRQ7(void)
{
    if (lock_en == 1U)
    {
        HW_WR_REG32((SOC_EVE_SYSTEM_BASE + MMR_LOCK_4), 0xC7EAD20AU);
    }

    uint16_t lvInterrupt = 0;
    /* Get pending interrupt */
    EVE_INTCTL_Ack(SOC_EVE_SYSTEM_BASE, /* BaseAddress */
                   INTCTL_INT7,         /* Interrupt Priority */
                   &lvInterrupt);       /* Interrupt Id */

    /* Enable for Valid next IRQ*/
    EVE_INTCTL_NextValid(SOC_EVE_SYSTEM_BASE, /* BaseAddress */
                         INTCTL_INT7);        /* Interrupt Priority */

    /* increment interrupt counter */
    inth_IrqCount[lvInterrupt]++;

    /* if an interrupt handler has been registered */
    if (inth_IrqHandler[lvInterrupt] != NULL)
    {
        /* call regitered interrupt handler */
        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }

    if (lock_en == 1U)
    {
        HW_WR_REG32((SOC_EVE_SYSTEM_BASE + MMR_LOCK_4), 0x12345678U);
    }

    return;
}

interrupt void INTH_IRQ8(void)
{
    if (lock_en == 1U)
    {
        HW_WR_REG32((SOC_EVE_SYSTEM_BASE + MMR_LOCK_4), 0xC7EAD20AU);
    }

    uint16_t lvInterrupt = 0;
    /* Get pending interrupt */
    EVE_INTCTL_Ack(SOC_EVE_SYSTEM_BASE, /* BaseAddress */
                   INTCTL_INT8,         /* Interrupt Priority */
                   &lvInterrupt);       /* Interrupt Id */

    /* Enable for Valid next IRQ*/
    EVE_INTCTL_NextValid(SOC_EVE_SYSTEM_BASE, /* BaseAddress */
                         INTCTL_INT8);        /* Interrupt Priority */

    /* increment interrupt counter */
    inth_IrqCount[lvInterrupt]++;

    /* if an interrupt handler has been registered */
    if (NULL != inth_IrqHandler[lvInterrupt])
    {
        /* call regitered interrupt handler */
        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }

    if (lock_en == 1U)
    {
        HW_WR_REG32((SOC_EVE_SYSTEM_BASE + MMR_LOCK_4), 0x12345678U);
    }

    return;
}

interrupt void INTH_IRQ9(void)
{
    if (lock_en == 1U)
    {
        HW_WR_REG32((SOC_EVE_SYSTEM_BASE + MMR_LOCK_4), 0xC7EAD20AU);
    }

    uint16_t lvInterrupt = 0;
    /* Get pending interrupt */
    EVE_INTCTL_Ack(SOC_EVE_SYSTEM_BASE, /* BaseAddress */
                   INTCTL_INT9,         /* Interrupt Priority */
                   &lvInterrupt);       /* Interrupt Id */

    /* Enable for Valid next IRQ*/
    EVE_INTCTL_NextValid(SOC_EVE_SYSTEM_BASE, /* BaseAddress */
                         INTCTL_INT9);        /* Interrupt Priority */

    /* increment interrupt counter */
    inth_IrqCount[lvInterrupt]++;

    /* if an interrupt handler has been registered */
    if (inth_IrqHandler[lvInterrupt] != NULL)
    {
        /* call regitered interrupt handler */
        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }

    if (lock_en == 1U)
    {
        HW_WR_REG32((SOC_EVE_SYSTEM_BASE + MMR_LOCK_4), 0x12345678U);
    }

    return;
}

interrupt void INTH_IRQ10(void)
{
    if (lock_en == 1U)
    {
        HW_WR_REG32((SOC_EVE_SYSTEM_BASE + MMR_LOCK_4), 0xC7EAD20AU);
    }

    uint16_t lvInterrupt = 0;
    /* Get pending interrupt */
    EVE_INTCTL_Ack(SOC_EVE_SYSTEM_BASE, /* BaseAddress */
                   INTCTL_INT10,        /* Interrupt Priority */
                   &lvInterrupt);       /* Interrupt Id */

    /* Enable for Valid next IRQ*/
    EVE_INTCTL_NextValid(SOC_EVE_SYSTEM_BASE, /* BaseAddress */
                         INTCTL_INT10);       /* Interrupt Priority */

    /* increment interrupt counter */
    inth_IrqCount[lvInterrupt]++;

    /* if an interrupt handler has been registered */
    if (inth_IrqHandler[lvInterrupt] != NULL)
    {
        /* call regitered interrupt handler */
        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }

    if (lock_en == 1U)
    {
        HW_WR_REG32((SOC_EVE_SYSTEM_BASE + MMR_LOCK_4), 0x12345678U);
    }

    return;
}

interrupt void INTH_IRQ11(void)
{
    if (lock_en == 1U)
    {
        HW_WR_REG32((SOC_EVE_SYSTEM_BASE + MMR_LOCK_4), 0xC7EAD20AU);
    }

    uint16_t lvInterrupt = 0;
    /* Get pending interrupt */
    EVE_INTCTL_Ack(SOC_EVE_SYSTEM_BASE, /* BaseAddress */
                   INTCTL_INT11,        /* Interrupt Priority */
                   &lvInterrupt);       /* Interrupt Id */

    /* Enable for Valid next IRQ*/
    EVE_INTCTL_NextValid(SOC_EVE_SYSTEM_BASE, /* BaseAddress */
                         INTCTL_INT11);       /* Interrupt Priority */

    /* increment interrupt counter */
    inth_IrqCount[lvInterrupt]++;

    /* if an interrupt handler has been registered */
    if (inth_IrqHandler[lvInterrupt] != NULL)
    {
        /* call regitered interrupt handler */
        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }

    if (lock_en == 1U)
    {
        HW_WR_REG32((SOC_EVE_SYSTEM_BASE + MMR_LOCK_4), 0x12345678U);
    }

    return;
}

interrupt void INTH_IRQ12(void)
{
    if (lock_en == 1U)
    {
        HW_WR_REG32((SOC_EVE_SYSTEM_BASE + MMR_LOCK_4), 0xC7EAD20AU);
    }

    uint16_t lvInterrupt = 0;
    /* Get pending interrupt */
    EVE_INTCTL_Ack(SOC_EVE_SYSTEM_BASE, /* BaseAddress */
                   INTCTL_INT12,        /* Interrupt Priority */
                   &lvInterrupt);       /* Interrupt Id */

    /* Enable for Valid next IRQ*/
    EVE_INTCTL_NextValid(SOC_EVE_SYSTEM_BASE, /* BaseAddress */
                         INTCTL_INT12);       /* Interrupt Priority */

    /* increment interrupt counter */
    inth_IrqCount[lvInterrupt]++;

    /* if an interrupt handler has been registered */
    if (inth_IrqHandler[lvInterrupt] != NULL)
    {
        /* call regitered interrupt handler */
        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }

    if (lock_en == 1U)
    {
        HW_WR_REG32((SOC_EVE_SYSTEM_BASE + MMR_LOCK_4), 0x12345678U);
    }

    return;
}

interrupt void INTH_IRQ13(void)
{
    if (lock_en == 1U)
    {
        HW_WR_REG32((SOC_EVE_SYSTEM_BASE + MMR_LOCK_4), 0xC7EAD20AU);
    }

    uint16_t lvInterrupt = 0;
    /* Get pending interrupt */
    EVE_INTCTL_Ack(SOC_EVE_SYSTEM_BASE, /* BaseAddress */
                   INTCTL_INT13,        /* Interrupt Priority */
                   &lvInterrupt);       /* Interrupt Id */

    /* Enable for Valid next IRQ*/
    EVE_INTCTL_NextValid(SOC_EVE_SYSTEM_BASE, /* BaseAddress */
                         INTCTL_INT13);       /* Interrupt Priority */

    /* increment interrupt counter */
    inth_IrqCount[lvInterrupt]++;

    /* if an interrupt handler has been registered */
    if (inth_IrqHandler[lvInterrupt] != NULL)
    {
        /* call regitered interrupt handler */
        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }

    if (lock_en == 1U)
    {
        HW_WR_REG32((SOC_EVE_SYSTEM_BASE + MMR_LOCK_4), 0x12345678U);
    }

    return;
}

interrupt void INTH_IRQ14(void)
{
    if (lock_en == 1U)
    {
        HW_WR_REG32((SOC_EVE_SYSTEM_BASE + MMR_LOCK_4), 0xC7EAD20AU);
    }

    uint16_t lvInterrupt = 0;
    /* Get pending interrupt */
    EVE_INTCTL_Ack(SOC_EVE_SYSTEM_BASE, /* BaseAddress */
                   INTCTL_INT14,        /* Interrupt Priority */
                   &lvInterrupt);       /* Interrupt Id */

    /* Enable for Valid next IRQ*/
    EVE_INTCTL_NextValid(SOC_EVE_SYSTEM_BASE, /* BaseAddress */
                         INTCTL_INT14);       /* Interrupt Priority */

    /* increment interrupt counter */
    inth_IrqCount[lvInterrupt]++;

    /* if an interrupt handler has been registered */
    if (inth_IrqHandler[lvInterrupt] != NULL)
    {
        /* call regitered interrupt handler */
        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }

    if (lock_en == 1U)
    {
        HW_WR_REG32((SOC_EVE_SYSTEM_BASE + MMR_LOCK_4), 0x12345678U);
    }

    return;
}

interrupt void INTH_IRQ15(void)
{
    if (lock_en == 1U)
    {
        HW_WR_REG32((SOC_EVE_SYSTEM_BASE + MMR_LOCK_4), 0xC7EAD20AU);
    }

    uint16_t lvInterrupt = 0;
    /* Get pending interrupt */
    EVE_INTCTL_Ack(SOC_EVE_SYSTEM_BASE, /* BaseAddress */
                   INTCTL_INT15,        /* Interrupt Priority */
                   &lvInterrupt);       /* Interrupt Id */

    /* Enable for Valid next IRQ*/
    EVE_INTCTL_NextValid(SOC_EVE_SYSTEM_BASE, /* BaseAddress */
                         INTCTL_INT15);       /* Interrupt Priority */

    /* increment interrupt counter */
    inth_IrqCount[lvInterrupt]++;

    /* if an interrupt handler has been registered */
    if (inth_IrqHandler[lvInterrupt] != NULL)
    {
        /* call regitered interrupt handler */
        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }

    if (lock_en == 1U)
    {
        HW_WR_REG32((SOC_EVE_SYSTEM_BASE + MMR_LOCK_4), 0x12345678U);
    }

    return;
}

void NMI_IRQInternalFunction(void)
{
    if (lock_en == 1U)
    {
        HW_WR_REG32((SOC_EVE_SYSTEM_BASE + MMR_LOCK_4), 0xC7EAD20AU);
    }

    uint16_t lvInterrupt = 0;
    /* Get pending interrupt */
    EVE_INTCTL_Ack(SOC_EVE_SYSTEM_BASE, /* BaseAddress */
                   INTCTL_NMI,          /* Interrupt Priority */
                   &lvInterrupt);       /* Interrupt Id */

    /* Enable for Valid next IRQ*/
    EVE_INTCTL_NextValid(SOC_EVE_SYSTEM_BASE, /* BaseAddress */
                         INTCTL_NMI);         /* Interrupt Priority */

    /* increment interrupt counter */
    inth_IrqCount[lvInterrupt]++;

    /* if an interrupt handler has been registered */
    if (inth_IrqHandler[lvInterrupt] != NULL)
    {
        /* call regitered interrupt handler */
        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }

    if (lock_en == 1U)
    {
        HW_WR_REG32((SOC_EVE_SYSTEM_BASE + MMR_LOCK_4), 0x12345678U);
    }
}

