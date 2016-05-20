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

/*******************************************************************************
 *                       INCLUDE FILES
 *******************************************************************************/
#include "stdint.h"
#include "stddef.h"
#include <c6x.h>
#include "soc.h"
#include "interrupt.h"
#include "hw_types.h"
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include "hw_dsp_icfg.h"

/*******************************************************************************
 *                       INTERNAL MACRO DEFINITIONS
 *******************************************************************************/

/* number of DSP interrupt handlers 0..127*/
#define INTH_INT_TABLE_SIZE     128U

/* Max interrupt number*/
#define INTH_INT_NUM_MAX     (INTH_INT_TABLE_SIZE - 1U)

/* static __inline uint32_t get_int_evtflag(uint32_t i); */
/* static __inline void set_int_evt(uint32_t i, uint32_t val); */
static __inline uint32_t get_int_mevtflag(uint32_t i);
static __inline void clr_int_evt(uint32_t i, uint32_t val);
static __inline uint32_t get_int_evtmask(uint32_t i);
static __inline void set_int_evtmask(uint32_t i, uint32_t val);

#if 0 /* Unused Functions */
/*
 * \brief Macro to get the status of the events
 * \Param i  = register index for the register index passed
 *       i = 0 Get status of register DSP_EVTFLAG0
 *       i = 1 Get status of register DSP_EVTFLAG1
 *       i = 2 Get status of register DSP_EVTFLAG2
 *       i = 3 Get status of register DSP_EVTFLAG3
 */
static __inline uint32_t get_int_evtflag(uint32_t i)
{
    uint32_t retval;

    retval = HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_EVTFLAG0 + \
                         ((i) << 2U));
    return retval;
}

/*
 * \brief Macro to set the event for the register index passed
 * \Param i  = register index
 *       i = 0 Set event in register DSP_EVTSET0
 *       i = 1 Set event in register DSP_EVTSET1
 *       i = 2 Set event in register DSP_EVTSET2
 *       i = 3 Set event in register DSP_EVTSET3
 *
 *       val = value to be written to register
 */

static __inline void set_int_evt(uint32_t i, uint32_t val)
{
    HW_WR_REG32((SOC_DSP_ICFG_BASE + DSP_EVTSET0 + \
                 ((i) << 2U)), (val));
}

#endif

static __inline uint32_t get_int_mevtflag(uint32_t i)
{
    uint32_t retval;

    retval = HW_RD_REG32(SOC_DSP_ICFG_BASE + \
                         DSP_MEVTFLAG0 +     \
                         ((i) << 2U));
    return retval;
}

/*
 * \brief Macro to clear the event for the register index passed
 * \Param i  = register index
 *       i = 0 clear event by writting to register DSP_EVTCLR0
 *       i = 1 clear event by writting to register DSP_EVTCLR1
 *       i = 2 clear event by writting to register DSP_EVTCLR2
 *       i = 3 clear event by writting to register DSP_EVTCLR3
 *
 *       val = value to be written to register
 */

static __inline void clr_int_evt(uint32_t i, uint32_t val)
{
    HW_WR_REG32((SOC_DSP_ICFG_BASE + DSP_EVTCLR0 + \
                 ((i) << 2U)), (val));
}

/*
 * \brief Get Masked event status for the register index passed
 * \Param i  = register index
 *       i = 0 Get event mask for register DSP_EVTMASK0
 *       i = 1 Get event mask for register DSP_EVTMASK1
 *       i = 2 Get event mask for register DSP_EVTMASK2
 *       i = 3 Get event mask for register DSP_EVTMASK3
 *
 */
static __inline uint32_t get_int_evtmask(uint32_t i)
{
    uint32_t retval;

    retval = HW_RD_REG32(SOC_DSP_ICFG_BASE + DSP_EVTMASK0 + \
                         ((i) << 2U));
    return retval;
}

/*
 * \brief Mask the events for the register index passed with mask val
 * \Param i  = register index
 *       i = 0 Set event mask for register DSP_EVTMASK0
 *       i = 1 Set event mask for register DSP_EVTMASK1
 *       i = 2 Set event mask for register DSP_EVTMASK2
 *       i = 3 Set event mask for register DSP_EVTMASK3
 *
 */
static __inline void set_int_evtmask(uint32_t i, uint32_t val)
{
    HW_WR_REG32((SOC_DSP_ICFG_BASE + DSP_EVTMASK0 + \
                 ((i) << 2U)), (val));
}

/******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
/* L2 Interrupt Vector Table */
#ifdef __cplusplus
#pragma DATA_SECTION(".l2_int")
#else
#pragma DATA_SECTION(inth_IrqHandler, ".l2_int")
#endif  /* #ifdef __cplusplus */
IntrFuncPtr     inth_IrqHandler[INTH_INT_TABLE_SIZE];

void           *argArray[INTH_INT_TABLE_SIZE] = {0};
uint32_t        INTH_intRouting[16];

#ifdef __cplusplus
#pragma DATA_SECTION(".vects")
#else
#pragma DATA_SECTION(__ISR_Table, ".vects")
#endif  /* #ifdef __cplusplus */
uint32_t        __ISR_Table[16] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000
};

/* array of interrupt counter */
static uint32_t inth_IrqCount[INTH_INT_TABLE_SIZE];

/******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/
static void scanCombined(uint8_t *intNo, uint32_t flag, uint32_t combNo);
void INTH_IRQHandler(uint8_t L1intNumber);

interrupt void INTH_L1IRQ4Handler(void);
interrupt void INTH_L1IRQ5Handler(void);
interrupt void INTH_L1IRQ6Handler(void);
interrupt void INTH_L1IRQ7Handler(void);
interrupt void INTH_L1IRQ8Handler(void);
interrupt void INTH_L1IRQ9Handler(void);
interrupt void INTH_L1IRQ10Handler(void);
interrupt void INTH_L1IRQ11Handler(void);
interrupt void INTH_L1IRQ12Handler(void);
interrupt void INTH_L1IRQ13Handler(void);
interrupt void INTH_L1IRQ14Handler(void);
interrupt void INTH_L1IRQ15Handler(void);

/******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/

void Intc_IntRegister(uint16_t intrNum, IntrFuncPtr fptr, void *fun_arg)
{
    /* reset counter and install handler */
    inth_IrqCount[intrNum]   = 0;
    inth_IrqHandler[intrNum] = fptr;
    argArray[intrNum]        = fun_arg;
} /* EVE_HOST_INTH_InterruptSetup() */

/*==================== Function Separator =============================*/

void Intc_SystemEnable(uint16_t intrNum)
{
    uint32_t uTmp;
    uint32_t rgs;
    uint32_t tempVal;

    uTmp = (uint32_t) intrNum >> 5;

    rgs     = get_int_evtmask(uTmp);
    tempVal = ~((uint32_t) 1U << (intrNum & 0x1FU));
    rgs    &= tempVal;
    set_int_evtmask(uTmp, rgs);
}

/*==================== Function Separator =============================*/

void Intc_SystemDisable(uint16_t intrNum)
{
    uint32_t uTmp;
    uint32_t rgs;
    uint32_t tempVal;

    uTmp = (uint32_t) intrNum >> 5;

    rgs     = get_int_evtmask(uTmp);
    tempVal = ((uint32_t) 1U << (intrNum & 0x1FU));
    rgs    |= (uint32_t) tempVal;
    set_int_evtmask(uTmp, rgs);
}

/*==================== Function Separator =============================*/
void INTH_IRQHandler(uint8_t L1intNumber)

{
    uint8_t  intNumber[32];

    uint32_t FlagLatch = 0;
    uint32_t pass;

    intNumber[0] = 0;

    switch (L1intNumber)
    {
        case 4U:
            FlagLatch = get_int_mevtflag((uint32_t) 0);
            clr_int_evt((uint32_t) 0, FlagLatch);
            scanCombined(intNumber, FlagLatch, (uint32_t) 0U);
            break;
        case 5U:
            FlagLatch = get_int_mevtflag((uint32_t) 1);
            clr_int_evt((uint32_t) 1, FlagLatch);
            scanCombined(intNumber, FlagLatch, (uint32_t) 1U);
            break;
        case 6U:
            FlagLatch = get_int_mevtflag((uint32_t) 2);
            clr_int_evt((uint32_t) 2, FlagLatch);
            scanCombined(intNumber, FlagLatch, (uint32_t) 2U);
            break;
        case 7U:
            FlagLatch = get_int_mevtflag((uint32_t) 3);
            clr_int_evt((uint32_t) 3, FlagLatch);
            scanCombined(intNumber, FlagLatch, (uint32_t) 3U);
            break;
        default:
            intNumber[0] = INTH_intRouting[L1intNumber];
            intNumber[1] = 0;
            pass         = ((uint32_t) intNumber[0] >> 5U);
            clr_int_evt((uint32_t) pass,
                        ((uint32_t) 1U <<
                         ((uint32_t) intNumber[0] - (uint32_t) (pass << 5U))));
            break;
    }

    while (FlagLatch)
    {
        /* Process all active interrupts */
        pass = 0;
        while (intNumber[pass]) {
            /* increment interrupt counter */
            inth_IrqCount[intNumber[pass]]++;

            if (inth_IrqHandler[intNumber[pass]])
            {
                /* call regitered interrupt handler */
                inth_IrqHandler[intNumber[pass]](argArray[intNumber[pass]]);
            }
            pass++;
        }

        switch (L1intNumber)
        {
            case 4U:
                FlagLatch = get_int_mevtflag((uint32_t) 0);
                clr_int_evt((uint32_t) 0, FlagLatch);
                scanCombined(intNumber, FlagLatch, (uint32_t) 0);
                break;
            case 5U:
                FlagLatch = get_int_mevtflag((uint32_t) 1);
                clr_int_evt((uint32_t) 1, FlagLatch);
                scanCombined(intNumber, FlagLatch, (uint32_t) 1);
                break;
            case 6U:
                FlagLatch = get_int_mevtflag((uint32_t) 2);
                clr_int_evt((uint32_t) 2, FlagLatch);
                scanCombined(intNumber, FlagLatch, (uint32_t) 2);
                break;
            case 7U:
                FlagLatch = get_int_mevtflag((uint32_t) 3);
                clr_int_evt((uint32_t) 3, FlagLatch);
                scanCombined(intNumber, FlagLatch, (uint32_t) 3);
                break;
            default:
                intNumber[0] = INTH_intRouting[L1intNumber];
                intNumber[1] = 0;
                pass         = ((uint32_t) intNumber[0] >> 5U);
                clr_int_evt(pass,
                            ((uint32_t) 1U <<
                             ((uint32_t) intNumber[0] -
                              (uint32_t) (pass << 5U))));
                break;
        }
    }
}  /* INTH_IRQHandler() */

/*==================== Function Separator =============================*/
void Intc_IntUnregister(uint16_t intrNum)
{
    uint32_t L1int;

    /* Find and clean interrupt entry in INTH_intRouting table */
    for (L1int = 8U; L1int < 16U; L1int++)
    {
        if (INTH_intRouting[L1int] == intrNum)
        {
            /*reset interrupt routing entry*/
            INTH_intRouting[L1int] = 0;

            /*reset counter and deinstall handler*/
            inth_IrqCount[intrNum]   = 0;
            inth_IrqHandler[intrNum] = NULL;
        }
    }
}

/**
 * \brief  Restore the processor IER status if status is not equal to 0.
 *         else enables all the bits in IER.
 *         This does not affect the set of interrupts enabled/disabled
 *         in the INTC.
 *
 * \param    The status returned by the Intc_IntDisable function.
 *
 * \return   None
 *
 **/
void Intc_IntEnable(uint32_t status)
{
    uint32_t mask;
    mask = 0x000000f2U;

    if (0U == status)
    {
        IER |= mask;
    }
    else
    {
        IER |= status;
    }
}

/**
 * \brief  Read and save the status and Disables the bits in IER .
 *         Prevents the processor to respond to interrupts.
 *
 * \param    None
 *
 * \return   Current status of IER
 *
 **/
uint32_t Intc_IntDisable(void)
{
    uint32_t status = IER;

    IER = 0;

    return status;
}

/**
 * \brief   This API assigns a priority to an interrupt and routes it to
 *          either IRQ or to FIQ. Priority 0 is the highest priority level
 *          Among the host interrupts, FIQ has more priority than IRQ.
 **/
void Intc_IntPrioritySet(uint16_t intrNum, uint16_t priority,
                         uint8_t hostIntRoute)
{
    /* Dummy function in DSP */
}

/* ============================================================================
 * LOCAL FUNCTIONS
 * =============================================================================
 */

/*==================== Function Separator =============================*/
static void scanCombined(uint8_t *intNo, uint32_t flag, uint32_t combNo)
{
    volatile uint32_t i, count;

    count = 0U;
    if (0U == combNo)
    {
        i = 4U;
    }
    else
    {
        i = 0U;
    }

    for (; i < 32U; i++)
    {
        if ((uint32_t) 0 != (flag & ((uint32_t) 1 << i)))
        {
            intNo[count] = i + (combNo << 5);
            count++;
        }
    }

    intNo[count] = 0;
} /* scanCombined() */

/*==================== Function Separator =============================*/

void Intc_Init(void)
{
    uint32_t count;
    uint32_t mask;

    /* Now, enable the 4,5,6, and 7 bits of IER
     *     These involve the default priority mode which uses the interrupt
     *       combiner */

    /* Clear all entries in L2 interrupt handler */
    for (count = 0U; count < INTH_INT_TABLE_SIZE; count++)
    {
        inth_IrqHandler[count] = NULL;
    }

    /* Clear Routing Table */
    for (count = 0U; count < 16U; count++)
    {
        INTH_intRouting[count] = 0;
    }

    /* Route combined inputs */
    INTH_intRouting[4] = INTH_INT_ID_EVT0;
    INTH_intRouting[5] = INTH_INT_ID_EVT1;
    INTH_intRouting[6] = INTH_INT_ID_EVT2;
    INTH_intRouting[7] = INTH_INT_ID_EVT3;

    /* Configure IC */
    /* Remove all inputs from combiner */
    for (count = 0U; count < 4U; count++)
    {
        clr_int_evt(count, 0xFFFFFFFFU);
        set_int_evtmask(count, 0xFFFFFFFFU);
    }

    /*Mask dropped interrupts*/
    HW_WR_REG32((SOC_DSP_ICFG_BASE + DSP_INTDMASK), 0xFFF0U);

    /*
     * Program the interrupt selector here,
     * the first 4 interrupt output of the interrupt selector is
     * routed from the interrupt combiner
     * Each of these interrupt line cater to 32 event input lines
     *
     * Below is the mapping -
     * 0 bit -> 0-31 event lines
     * 1 bit -> 32-63 event lines
     * 2 bit -> 64-95 event lines
     * 3 bit -> 96-127 event lines
     *
     */
    HW_WR_REG32((SOC_DSP_ICFG_BASE + DSP_INTMUX1), 0x03020100U);

    /* Route unused EVT 119 to other interrupt inputs */
    HW_WR_REG32((SOC_DSP_ICFG_BASE + DSP_INTMUX2), 0x77777777U);
    HW_WR_REG32((SOC_DSP_ICFG_BASE + DSP_INTMUX3), 0x77777777U);

    ICR = 0xffffU;

    /* Clear Dropped interrupts */
    HW_WR_REG32((SOC_DSP_ICFG_BASE + DSP_INTXCLR), 0x1U);

    __ISR_Table[4]  = (uint32_t) &INTH_L1IRQ4Handler;
    __ISR_Table[5]  = (uint32_t) &INTH_L1IRQ5Handler;
    __ISR_Table[6]  = (uint32_t) &INTH_L1IRQ6Handler;
    __ISR_Table[7]  = (uint32_t) &INTH_L1IRQ7Handler;
    __ISR_Table[8]  = (uint32_t) &INTH_L1IRQ8Handler;
    __ISR_Table[9]  = (uint32_t) &INTH_L1IRQ9Handler;
    __ISR_Table[10] = (uint32_t) &INTH_L1IRQ10Handler;
    __ISR_Table[11] = (uint32_t) &INTH_L1IRQ11Handler;
    __ISR_Table[12] = (uint32_t) &INTH_L1IRQ12Handler;
    __ISR_Table[13] = (uint32_t) &INTH_L1IRQ13Handler;
    __ISR_Table[14] = (uint32_t) &INTH_L1IRQ14Handler;
    __ISR_Table[15] = (uint32_t) &INTH_L1IRQ15Handler;

    mask = 0x000000f2U;
    IER |= mask;

    /* Enable the Global Interrupt Enable bit in CSR register of GEM*/
    CSR |= 0x00000001U;
} /* INTH_InitIntTable() */

interrupt void INTH_L1IRQ4Handler(void)
{
    INTH_IRQHandler(4U);
}

interrupt void INTH_L1IRQ5Handler(void)
{
    INTH_IRQHandler(5U);
}

interrupt void INTH_L1IRQ6Handler(void)
{
    INTH_IRQHandler(6U);
}

interrupt void INTH_L1IRQ7Handler(void)
{
    INTH_IRQHandler(7U);
}

interrupt void INTH_L1IRQ8Handler(void)
{
    INTH_IRQHandler(8U);
}

interrupt void INTH_L1IRQ9Handler(void)
{
    INTH_IRQHandler(9U);
}

interrupt void INTH_L1IRQ10Handler(void)
{
    INTH_IRQHandler(10U);
}

interrupt void INTH_L1IRQ11Handler(void)
{
    INTH_IRQHandler(11U);
}

interrupt void INTH_L1IRQ12Handler(void)
{
    INTH_IRQHandler(12U);
}

interrupt void INTH_L1IRQ13Handler(void)
{
    INTH_IRQHandler(13U);
}

interrupt void INTH_L1IRQ14Handler(void)
{
    INTH_IRQHandler(14U);
}

interrupt void INTH_L1IRQ15Handler(void)
{
    INTH_IRQHandler(15U);
}

