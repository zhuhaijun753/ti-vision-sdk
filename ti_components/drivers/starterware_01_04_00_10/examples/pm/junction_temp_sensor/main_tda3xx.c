/**
 *  \file main.c
 *
 *  \brief TDA3xx Junction Temperature Sensor Application
 *
 *  \copyright Copyright (C) 2014 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

/* ======================================================================
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
 * ==================================================================== */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "stdio.h"
#include "string.h"
#include "stdint.h"
#include "soc_defines.h"
#include "platform.h"
#include "soc.h"
#include "uartStdio.h"
#include "uartConsole.h"
#include "hw_types.h"
#include "interrupt.h"
#include "irq_xbar.h"
#include "hw_ctrl_core.h"
#include "hw_l4per_cm_core.h"
#include <wd_timer.h>
#include "pm/pm_types.h"
#include "pm/pm_utils.h"
#include "pmhal_prcm.h"
#include "pmhal_bgap.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define IPU_IRQ_65                      (65U)
/**< \brief MPU IRQ number for Temperature Sensor Interrupt */

#define TIMEOUT_VAL                      (10000U)
/**< \brief Timeout value to wait for event */

#define HOT_EVT_TEMP_THRESH              (10000)
/**< \brief HOT temperature event triggered at 10 degrees Celcius */

#define MAX_HOT_EVT_TEMP_THRESH          (125000)
/**< \brief HOT temperature event triggered at 125 degrees Celcius */

#define COLD_EVT_TEMP_THRESH             (100000)
/**< \brief HOT temperature event triggered at 100 degrees Celcius */

#define MIN_COLD_EVT_TEMP_THRESH         (0)
/**< \brief HOT temperature event triggered at 0 degrees Celcius */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/** \brief  Configure the Temperature Sensor Interrupt.
 */
static void SensorIntcInit(void);

/** \brief  Sensor interrupt service routine. This will disable the Temperature
 *          sensor interrupt.
 */
static void TemperatureSensorIsr(void *handle);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

const char              *voltageDomain_t_names[] =
{
    "PMHAL_PRCM_VD_CORE",
    "PMHAL_PRCM_VD_DSPEVE",
};

pmhalPrcmVdId_t          gVoltId          = PMHAL_PRCM_VD_CORE;
static volatile uint8_t  tempEvtOccurred = 0U;

static volatile uint32_t gXbarInst = 43;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    pmhalBgapRange_t currTempRange = {0, 0};
    int32_t          retVal        = PM_SUCCESS;
    int32_t          timeout       = TIMEOUT_VAL;
    int32_t          finalResult   = PM_SUCCESS;

    printf("\nPM Junction Temperature Measure Test App");

    PMHALBgapSetMeasureDelay(PMHAL_BGAP_BAND_GAP_1_MS);
    PMHALBgapClearState(gVoltId);

    printf("\n----------------------------------------");
    printf("\n Measure the Current Temperature of different Voltage Rails");
    printf("\n----------------------------------------");

    if((PMHAL_PRCM_VD_COUNT > gVoltId) && (0 <= gVoltId))
    {
        printf("\nVoltage Domain: ");
        puts(voltageDomain_t_names[gVoltId]);
    }
    retVal = PMHALBgapGetCurrTemperature(gVoltId, &currTempRange);

    if (PM_SUCCESS == retVal)
    {
        printf(
            "\nCurrent Temperature Range in Degrees C = [%u.%u , %u.%u]",
            currTempRange.minTemp / 1000, (currTempRange.minTemp % 1000),
            currTempRange.maxTemp / 1000, (currTempRange.maxTemp % 1000));
    }
    else
    {
        printf("\nGet Current Temperature Failed!!");
        finalResult |= PM_FAIL;
    }

    printf("\n----------------------------------------");
    printf("\n Check for Hot events of different Voltage Rails");
    printf("\n----------------------------------------");
    SensorIntcInit();
    if((PMHAL_PRCM_VD_COUNT > gVoltId) && (0 <= gVoltId))
    {
        printf("\nVoltage Domain: ");
        puts(voltageDomain_t_names[gVoltId]);
    }
    tempEvtOccurred = 0U;
    timeout         = TIMEOUT_VAL;
    retVal          = PMHALBgapSetHotThreshold(gVoltId, HOT_EVT_TEMP_THRESH);
    while ((0U == tempEvtOccurred) && (timeout > 0U))
    {
        timeout--;
    }

    if ((0U == timeout) && (0U == tempEvtOccurred))
    {
        printf("\nHot event not received. Timed Out!!");
        finalResult |= PM_FAIL;
    }

    printf("\n----------------------------------------");
    printf("\n Check for Cold events of different Voltage Rails");
    printf("\n----------------------------------------");
    if((PMHAL_PRCM_VD_COUNT > gVoltId) && (0 <= gVoltId))
    {
        printf("\nVoltage Domain: ");
        puts(voltageDomain_t_names[gVoltId]);
    }
    tempEvtOccurred = 0U;
    timeout         = TIMEOUT_VAL;
    retVal          = PMHALBgapSetColdThreshold(gVoltId, COLD_EVT_TEMP_THRESH);
    while ((0U == tempEvtOccurred) && (timeout > 0U))
    {
        timeout--;
    }

    if ((0U == timeout) && (0U == tempEvtOccurred))
    {
        printf("\nCold event not received. Timed Out!!");
        finalResult |= PM_FAIL;
    }

    printf("\n----------------------------------------");
    if (PM_SUCCESS != finalResult)
    {
        printf("\nJunction Temperature App Failed!!");
    }
    else
    {
        printf("\nJunction Temperature App Passed!!");
    }
    printf("\n----------------------------------------");
    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static void SensorIntcInit(void)
{
    irq_xbar_ret_type_t status = invalid_mpu_id;

    /*Unlock the Crossbar register */
    PlatformUnlockMMR();

    /* Connect the Xbar with interrupt source */
    status = IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1,
                            gXbarInst, CTRL_MODULE_CORE_IRQ_THERMAL_ALERT);

    if (status != irq_xbar_success)
    {
        printf("\nXBar not able to connect");
    }

    /* Initialize the interrupt control */
    Intc_Init();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /* Registering TimerIsr */
    Intc_IntRegister(IPU_IRQ_65, (IntrFuncPtr) TemperatureSensorIsr, NULL);

    /* Set the priority */
    Intc_IntPrioritySet(IPU_IRQ_65, 1, 0);

    /* Enable the system interrupt */
    Intc_SystemEnable(IPU_IRQ_65);
}

static void TemperatureSensorIsr(void *handle)
{
    int32_t retVal = PM_SUCCESS;

    printf("\nTemperature Event Occurred");
    tempEvtOccurred = 1U;

    /* Follow this sequence to resolve silicon Errata ID: i813 which can
     * cause a spurious interrupt.
     */

    /* Disable the system interrupt */
    Intc_SystemDisable(IPU_IRQ_65);

    retVal  = PMHALBgapSetHotThreshold(gVoltId, MAX_HOT_EVT_TEMP_THRESH);
    retVal |= PMHALBgapSetColdThreshold(gVoltId, MIN_COLD_EVT_TEMP_THRESH);

    PMHALBgapDisableHotEvent(gVoltId);
    PMHALBgapDisableColdEvent(gVoltId);

    /* Enable the system interrupt */
    Intc_SystemEnable(IPU_IRQ_65);

    if (PM_SUCCESS != retVal)
    {
        printf("\nNot able to change thresholds");
    }
}
