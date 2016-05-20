/**
 *  \file main.c
 *
 *  \brief TDA2xx Junction Temperature Sensor Application
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

#define MPU_IRQ_126                      (126U)
/**< \brief MPU IRQ number for Temperature Sensor Interrupt */

#define TIMEOUT_VAL                      (10000U)
/**< \brief Timeout value to wait for event */

#define HOT_EVT_TEMP_THRESH              (10000)
/**< \brief HOT temperature event triggered at 20 degrees Celcius */

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
    "PMHAL_PRCM_VD_MPU",
    "PMHAL_PRCM_VD_CORE",
    "PMHAL_PRCM_VD_IVAHD",
    "PMHAL_PRCM_VD_DSPEVE",
    "PMHAL_PRCM_VD_GPU",
};

pmhalPrcmVdId_t          gVoltId          = PMHAL_PRCM_VD_MPU;
static volatile uint8_t  tempEvtOccurred = 0U;

static volatile uint32_t gXbarInst = 121;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    pmhalBgapRange_t currTempRange = {0, 0};
    int32_t          retVal        = PM_SUCCESS;
    int32_t          timeout       = TIMEOUT_VAL;
    int32_t          finalResult   = PM_SUCCESS;

    UART_PAD_CONFIG();
    UARTStdioInit();
    UARTPuts("\nPM Junction Temperature Measure Test App", -1);

    PMHALBgapSetMeasureDelay(PMHAL_BGAP_BAND_GAP_1_MS);
    for (gVoltId = PMHAL_PRCM_VD_MPU; gVoltId <= PMHAL_PRCM_VD_GPU; gVoltId++)
    {
        PMHALBgapClearState(gVoltId);
    }

    UARTPuts("\n----------------------------------------", -1);
    UARTPuts("\n Measure the Current Temperature of different Voltage Rails",
             -1);
    UARTPuts("\n----------------------------------------", -1);
    for (gVoltId = PMHAL_PRCM_VD_MPU; gVoltId <= PMHAL_PRCM_VD_GPU; gVoltId++)
    {
        UARTPuts("\nVoltage Domain: ", -1);
        UARTPuts(voltageDomain_t_names[gVoltId], -1);
        retVal = PMHALBgapGetCurrTemperature(gVoltId, &currTempRange);

        if (PM_SUCCESS == retVal)
        {
            UARTprintf(
                "\nCurrent Temperature Range in Degrees C = [%u.%u , %u.%u]",
                currTempRange.minTemp / 1000, (currTempRange.minTemp % 1000),
                currTempRange.maxTemp / 1000, (currTempRange.maxTemp % 1000));
        }
        else
        {
            UARTPuts("\nGet Current Temperature Failed!!", -1);
            finalResult |= PM_FAIL;
        }
    }

    UARTPuts("\n----------------------------------------", -1);
    UARTPuts("\n Check for Hot events of different Voltage Rails",
             -1);
    UARTPuts("\n----------------------------------------", -1);
    SensorIntcInit();
    for (gVoltId = PMHAL_PRCM_VD_MPU; gVoltId <= PMHAL_PRCM_VD_GPU; gVoltId++)
    {
        UARTPuts("\nVoltage Domain: ", -1);
        UARTPuts(voltageDomain_t_names[gVoltId], -1);
        tempEvtOccurred = 0U;
        timeout         = TIMEOUT_VAL;
        retVal          = PMHALBgapSetHotThreshold(gVoltId, HOT_EVT_TEMP_THRESH);
        while ((0U == tempEvtOccurred) && (timeout > 0U))
        {
            timeout--;
        }

        if ((0U == timeout) && (0U == tempEvtOccurred))
        {
            UARTPuts("\nHot event not received. Timed Out!!", -1);
            finalResult |= PM_FAIL;
        }
    }

    UARTPuts("\n----------------------------------------", -1);
    UARTPuts("\n Check for Cold events of different Voltage Rails",
             -1);
    UARTPuts("\n----------------------------------------", -1);
    for (gVoltId = PMHAL_PRCM_VD_MPU; gVoltId <= PMHAL_PRCM_VD_GPU; gVoltId++)
    {
        UARTPuts("\nVoltage Domain: ", -1);
        UARTPuts(voltageDomain_t_names[gVoltId], -1);
        tempEvtOccurred = 0U;
        timeout         = TIMEOUT_VAL;
        retVal          = PMHALBgapSetColdThreshold(gVoltId,
                                                    COLD_EVT_TEMP_THRESH);
        while ((0U == tempEvtOccurred) && (timeout > 0U))
        {
            timeout--;
        }

        if ((0U == timeout) && (0U == tempEvtOccurred))
        {
            UARTPuts("\nCold event not received. Timed Out!!", -1);
            finalResult |= PM_FAIL;
        }
    }

    UARTPuts("\n----------------------------------------", -1);
    if (PM_SUCCESS != finalResult)
    {
        UARTPuts("\nJunction Temperature App Failed!!", -1);
    }
    else
    {
        UARTPuts("\nJunction Temperature App Passed!!", -1);
    }
    UARTPuts("\n----------------------------------------", -1);
    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static void SensorIntcInit(void)
{
    irq_xbar_ret_type_t status = invalid_mpu_id;
    uint8_t connectionStatus   = 0;

    /*Unlock the Crossbar register */
    PlatformUnlockMMR();

    /* Connect the Xbar with interrupt source */
    status = IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_MPUSS,
                            gXbarInst, CTRL_MODULE_CORE_IRQ_THERMAL_ALERT);

    if (status == irq_xbar_success)
    {
        /* Check if xbar is indeed connected correctly */
        IRQXBARIsConnected(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_MPUSS,
                           gXbarInst, CTRL_MODULE_CORE_IRQ_THERMAL_ALERT,
                           &connectionStatus);
        if (connectionStatus == 1)
        {
            UARTPuts("\nXBar is sucessfully connected to inst:", -1);
            UARTPutNum(gXbarInst);
        }
        else
        {
            UARTPuts("\nWrong XBar Connection", -1);
        }
    }
    else
    {
        UARTPuts("\nXBar not able to connect", -1);
    }

    /* Initialize the interrupt control */
    Intc_Init();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /* Registering TimerIsr */
    Intc_IntRegister(MPU_IRQ_126, (IntrFuncPtr) TemperatureSensorIsr, NULL);

    /* Set the priority */
    Intc_IntPrioritySet(MPU_IRQ_126, 1, 0);

    /* Enable the system interrupt */
    Intc_SystemEnable(MPU_IRQ_126);
}

static void TemperatureSensorIsr(void *handle)
{
    int32_t retVal = PM_SUCCESS;

    UARTPuts("\nTemperature Event Occurred", -1);
    tempEvtOccurred = 1U;

    /* Follow this sequence to resolve silicon Errata ID: i813 which can
     * cause a spurious interrupt.
     */

    /* Disable the system interrupt */
    Intc_SystemDisable(MPU_IRQ_126);

    retVal  = PMHALBgapSetHotThreshold(gVoltId, MAX_HOT_EVT_TEMP_THRESH);
    retVal |= PMHALBgapSetColdThreshold(gVoltId, MIN_COLD_EVT_TEMP_THRESH);

    PMHALBgapDisableHotEvent(gVoltId);
    PMHALBgapDisableColdEvent(gVoltId);

    IntClearPendingState(MPU_IRQ_126);

    /* Enable the system interrupt */
    Intc_SystemEnable(MPU_IRQ_126);

    if (PM_SUCCESS != retVal)
    {
        UARTPuts("\nNot able to change thresholds", -1);
    }
}

