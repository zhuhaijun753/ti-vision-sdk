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
/*
 * \file startup.c
 *
 * \brief  Configures the PLL registers to achieve the required Operating
 *         frequency. Power and sleep controller is activated for UART and
 *         Interuppt controller. Interrupt vector is copied to the shared Ram.
 *         After doing all the above, controller is given to the application.
 *
 */

#include "stdint.h"
#include <armv7a/tda2xx/hw_intc.h>
#include "cpu.h"
#include "cp15.h"
#include "interrupt.h"

/***********************************************************************
**                            MACRO DEFINITIONS
***********************************************************************/
#define E_PASS                         (0)
#define E_FAIL                         (-1)

/***********************************************************************
**                     EXTERNAL FUNCTION PROTOTYPES
***********************************************************************/

extern void _c_int00(void);
extern void UndefInstHandler(void);
extern void SVCHandler(void);
extern void AbortHandler(void);
extern void IRQHandler(void);
extern void FIQHandler(void);

/**********************************************************************
 *                   INTERNAL FUNCTION PROTOTYPES
 **********************************************************************/

void CopyVectorTable(void);

/******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
#if (defined (TDA2XX_BUILD))
const uint32_t        TDA2XX_VECTOR_BASE = 0x40410000U;
#elif (defined (TDA2EX_BUILD))
const uint32_t        TDA2XX_VECTOR_BASE = 0x40300100U;
#endif

void _c_int00(void)
{}

static uint32_t const vecTbl[14] =
{
    0xE59FF018U,
    0xE59FF018U,
    0xE59FF018U,
    0xE59FF018U,
    0xE59FF014U,
    0xE24FF008U,
    0xE59FF010U,
    0xE59FF010U,
    (uint32_t) (&_c_int00),
    (uint32_t) (&UndefInstHandler),
    (uint32_t) (&SVCHandler),
    (uint32_t) (&AbortHandler),
    (uint32_t) (&IRQHandler),
    (uint32_t) (&FIQHandler)
};

/******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/

void CopyVectorTable(void)
{
    uint32_t *dest = (uint32_t *) TDA2XX_VECTOR_BASE;
    uint32_t *src  = (uint32_t *) vecTbl;
    uint32_t  count;

    /*
     * Setting base address of the exception vector table has to be done
     * in priviledge mode.
     *
     * This is done from SBL
     *
     */
    CP15VectorBaseAddrSet(TDA2XX_VECTOR_BASE);

    for (count = 0; count < (sizeof (vecTbl) / sizeof (vecTbl[0])); count++)
    {
        dest[count] = src[count];
    }
}

/***************************** End Of File ***********************************/
