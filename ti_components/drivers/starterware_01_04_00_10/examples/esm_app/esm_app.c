/**
 *  \file     esm_app.c
 *
 *  \brief    This file contains ESM test code.
 *
 *  \details  ESM operational mode is set to normal mode for group 1.
 *            EVE reset interrupt is enabled from group 1 and
 *            it's priority is set as high level interrupt.
 *
 *  \copyright Copyright (C) 2015 Texas Instruments Incorporated =
 *             http://www.ti.com/
 */

/* ======================================================================
 *   Copyright (C) 2015 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include "common/stw_dataTypes.h"
#include "common/stw_types.h"
#include "soc.h"
#include "soc_defines.h"
#include "hw_types.h"
#include "edma.h"
#include "timer.h"
#include "hw_esm.h"
#include "interrupt.h"
#include "platform.h"
#include "uartStdio.h"
#include "hw_core_cm_core.h"
#include "hw_counter_32k.h"
#include "irq_xbar.h"
#include "pmhal_prcm.h"
#include "pmhal_mm.h"
#include "pm/pmhal/pmhal_cm.h"
#include "esm.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#define APP_ESM_MODULE          (SOC_ESM_BASE)
#define APP_ESM_MODE            (ESM_OPERATION_MODE_NORMAL)
#define APP_ESM_INTR            (ESM_GROUP1_INTR_SRC_EVE_CPU_RST)

#define APP_ESM_INT_M4                                  (34U)
#define APP_ESM_INT_DSP                                 (32U)
#ifdef BUILD_M4
    #define APP_ESM_INT                     (APP_ESM_INT_M4)
    #define XBAR_CPU                        (CPU_IPU1)
    #define XBAR_INST                       (XBAR_INST_IPU1_IRQ_34)
    #define XBAR_INTR_SOURCE                (ESM_IRQ_HIGH)
#elif defined (BUILD_DSP)
    #define APP_ESM_INT                     (APP_ESM_INT_DSP)
    #define XBAR_CPU                        (CPU_DSP1)
    #define XBAR_INST                       (XBAR_INST_DSP1_IRQ_32)
    #define XBAR_INTR_SOURCE                (ESM_IRQ_HIGH)
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
volatile uint32_t isrFlag = 1U;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This Interrupt Service Routine for ESM interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void AppESMIntrISR(void *handle);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int main(void)
{
    int32_t configStatus;

    /* Configure UARTStdioInit */
    PlatformUartConsoleSetPinMux();
    UARTStdioInit();
    UARTPuts("\nStarting application...\n", -1);
    /* XBar configuration */
    if (irq_xbar_success ==
        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                       XBAR_CPU, XBAR_INST,
                       XBAR_INTR_SOURCE))
    {
        /* Enable Error interrupt for ESM */
        Intc_Init();
        Intc_IntEnable(APP_ESM_INT);

        /* Register ISR */
        Intc_IntRegister(APP_ESM_INT,
                         (IntrFuncPtr) AppESMIntrISR, 0);
        Intc_IntPrioritySet(APP_ESM_INT, 1, 0);
        Intc_SystemEnable(APP_ESM_INT);
        UARTPuts("XBar configuration successfully done.\n", -1);
    }
    else
    {
        UARTPuts("Error in configuring CrossBar.\n", -1);
    }
    /* Enable ESM module */
    configStatus = PMHALModuleModeSet(PMHAL_PRCM_MOD_ESM,
                                      PMHAL_PRCM_MODULE_MODE_ENABLED,
                                      PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != configStatus)
    {
        UARTPuts("Error in ESM module enable.\n", -1);
    }
    else
    {
        ESMSetMode(APP_ESM_MODULE, APP_ESM_MODE);
        ESMEnableIntr(APP_ESM_MODULE, APP_ESM_INTR);
        ESMSetIntrPriorityLvl(APP_ESM_MODULE, APP_ESM_INTR,
                              ESM_INTR_PRIORITY_LEVEL_HIGH);
        /* Generate/trigger error condition here */
        UARTPuts("Do EVE CPU Reset.\nWait for interrupt till reset is given.\n",
                 -1);
        while (1U == isrFlag)
        {
            /* Wait here till interrupt happens */
        }
    }
    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static void AppESMIntrISR(void *handle)
{
    uint32_t status;

    status = ESMGetIntrStatus(APP_ESM_MODULE,
                              APP_ESM_INTR);
    if (1U == status)
    {
        UARTPuts("EVE reset interrupt occurred.\n", -1);
    }
    else
    {
        UARTPuts("EVE reset did not interrupt occur.\n", -1);
    }
    status = ESMGetHighPriorityLvlIntrStatus(APP_ESM_MODULE);
    UARTprintf("Highest level pending interrupt is %d.\n", status);
    ESMClearIntrStatus(APP_ESM_MODULE, APP_ESM_INTR);
    ESMDisableIntr(APP_ESM_MODULE, APP_ESM_INTR);
    isrFlag = 0U;
    UARTPuts("Application is completed.\n", status);
}

