/**
 *  \file     adc_app_semicpu.c
 *
 *  \brief    This file contains ADC test code.
 *
 *  \details  ADC operational mode is set to Single shot.
 *            Following steps are enabled.
 *            Step ID       Input from Channel
 *            2             1
 *            3             3
 *            4             4
 *            5             5
 *            6             6
 *            Program uses SYNTIMER32k for timing calculations.
 *
 *  \copyright Copyright (C) 2014 Texas Instruments Incorporated =
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
#include <stdint.h>
#include "common/stw_dataTypes.h"
#include "common/stw_types.h"
#include "soc.h"
#include "soc_defines.h"
#include "hw_types.h"
#include "edma.h"
#include "timer.h"
#include "hw_adc.h"
#include "interrupt.h"
#include "platform.h"
#include "uartStdio.h"
#include "hw_core_cm_core.h"
#include "hw_counter_32k.h"
#include "irq_xbar.h"
#include "pmhal_prcm.h"
#include "pmhal_mm.h"
#include "pm/pmhal/pmhal_cm.h"
#include "adc.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#define APP_ADC_MODULE          (SOC_TSC_ADC_BASE)
#define APP_ADC_DIV             (1U)
/* Reference voltage for ADC - should be given in mV*/
#define APP_ADC_REF_VOLTAGE     (1800U)
#define APP_ADC_RANGE_MAX       (1024U)

#define APP_ADC_INT_M4                                  (34U)
#define APP_ADC_INT_DSP                                 (32U)
#ifdef BUILD_M4
    #define APP_ADC_INT                     (APP_ADC_INT_M4)
    #define EDMA3_CC_REGION                 (EDMA3_CC_REGION_M4)
    #define XBAR_CPU                        (CPU_IPU1)
    #define XBAR_INST                       (XBAR_INST_IPU1_IRQ_34)
    #define XBAR_INTR_SOURCE                (TSC_ADC_IRQ_GENINT)
#elif defined (BUILD_DSP)
    #define APP_ADC_INT                     (APP_ADC_INT_DSP)
    #define XBAR_CPU                        (CPU_DSP1)
    #define XBAR_INST                       (XBAR_INST_DSP1_IRQ_32)
    #define XBAR_INTR_SOURCE                (TSC_ADC_IRQ_GENINT)
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
volatile uint32_t isrFlag = 1U;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This is Interrupt Service Routine for ADC interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void AppADCIntrISR(void *handle);

/**
 * \brief   This function waits for 62.50us.
 *
 * \param   none.
 *
 * \retval  none.
 *
 * \note    Wait for 4 us before starting a conversion,after powering on
 *          ADC module.
 */
static void AppADCWait(void);

/**
 * \brief   This function initializes ADC module.
 *
 * \param   none.
 *
 * \retval  status          Initialization status.
 */
static int32_t AppADCInit(void);

/**
 * \brief   This function will start ADC conversion.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void AppADCStart(void);

/**
 * \brief   This function will stop ADC conversion
 *
 * \param   none.
 *
 * \retval  none.
 */
static void AppADCStop(void);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t main(void)
{
    int32_t         configStatus;
    uint32_t        loopcnt, fifoData, fifoWordCnt, stepID, voltageLvl;
    adcStepConfig_t adcConfig;

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
        /* Enable Error interrupt for ADC */
        Intc_Init();
        Intc_IntEnable(APP_ADC_INT);
        /* Register ISR */
        Intc_IntRegister(APP_ADC_INT,
                         (IntrFuncPtr) AppADCIntrISR, 0);
        Intc_IntPrioritySet(APP_ADC_INT, 1, 0);
        Intc_SystemEnable(APP_ADC_INT);
    }
    else
    {
        UARTPuts("Error in configuring CrossBar.\n", -1);
    }

    /* Enable ADC module */
    configStatus = PMHALModuleModeSet(PMHAL_PRCM_MOD_ADC,
                                      PMHAL_PRCM_MODULE_MODE_ENABLED,
                                      PM_TIMEOUT_INFINITE);

    if (PM_SUCCESS != configStatus)
    {
        UARTPuts("Error in ADC module enable.\n", -1);
    }
    else
    {
        /* Initialize ADC module */
        configStatus = AppADCInit();
        if (STW_SOK != configStatus)
        {
            UARTPuts("Error in ADC divider configuration.\n", -1);
        }
        /* Initialize ADC configuration params */
        adcConfig.mode             = ADC_OPERATION_MODE_SINGLE_SHOT;
        adcConfig.channel          = ADC_CHANNEL_1;
        adcConfig.openDelay        = 0x1U;
        adcConfig.sampleDelay      = 0U;
        adcConfig.rangeCheckEnable = 0U;
        adcConfig.averaging        = ADC_AVERAGING_NONE;
        adcConfig.fifoNum          = ADC_FIFO_NUM_0;

        /* Enable interrupts */
        ADCEnableIntr(APP_ADC_MODULE, (ADC_INTR_SRC_END_OF_SEQUENCE |
                                       ADC_INTR_SRC_FIFO0_THRESHOLD |
                                       ADC_INTR_SRC_FIFO0_OVERRUN |
                                       ADC_INTR_SRC_FIFO0_UNDERFLOW |
                                       ADC_INTR_SRC_FIFO1_THRESHOLD |
                                       ADC_INTR_SRC_FIFO1_OVERRUN |
                                       ADC_INTR_SRC_FIFO1_UNDERFLOW |
                                       ADC_INTR_SRC_OUT_OF_RANGE));
        /* Configure ADC */
        /* step 2 configuration */
        configStatus = ADCSetStepParams(APP_ADC_MODULE, ADC_STEP_2, &adcConfig);
        if (STW_SOK != configStatus)
        {
            UARTPuts("Error in ADC step configuration.\n", -1);
        }
        /* step 3 configuration */
        adcConfig.channel = ADC_CHANNEL_3;
        configStatus      = ADCSetStepParams(APP_ADC_MODULE, ADC_STEP_3,
                                             &adcConfig);
        if (STW_SOK != configStatus)
        {
            UARTPuts("Error in ADC step configuration.\n", -1);
        }
        /* step 4 configuration */
        adcConfig.channel = ADC_CHANNEL_4;
        configStatus      = ADCSetStepParams(APP_ADC_MODULE, ADC_STEP_4,
                                             &adcConfig);
        if (STW_SOK != configStatus)
        {
            UARTPuts("Error in ADC step configuration.\n", -1);
        }
        /* step 5 configuration */
        adcConfig.channel = ADC_CHANNEL_5;
        configStatus      = ADCSetStepParams(APP_ADC_MODULE, ADC_STEP_5,
                                             &adcConfig);
        if (STW_SOK != configStatus)
        {
            UARTPuts("Error in ADC step configuration.\n", -1);
        }
        /* step 6 configuration */
        adcConfig.channel = ADC_CHANNEL_6;
        configStatus      = ADCSetStepParams(APP_ADC_MODULE, ADC_STEP_6,
                                             &adcConfig);
        if (STW_SOK != configStatus)
        {
            UARTPuts("Error in ADC step configuration.\n", -1);
        }
        ADCStepIdTagEnable(APP_ADC_MODULE, TRUE);
        configStatus =
            ADCSetCPUFIFOThresholdLevel(APP_ADC_MODULE, ADC_FIFO_NUM_0,
                                        40U);
        if (STW_SOK != configStatus)
        {
            UARTPuts("Error in ADC CPU threshold configuration.\n", -1);
        }
        /* step enable */
        ADCStepEnable(APP_ADC_MODULE, ADC_STEP_2, TRUE);
        ADCStepEnable(APP_ADC_MODULE, ADC_STEP_3, TRUE);
        ADCStepEnable(APP_ADC_MODULE, ADC_STEP_4, TRUE);
        ADCStepEnable(APP_ADC_MODULE, ADC_STEP_5, TRUE);
        ADCStepEnable(APP_ADC_MODULE, ADC_STEP_6, TRUE);
        AppADCStart();
        while (1U == isrFlag)
        {}
        /*Get FIFO data */
        fifoWordCnt = ADCGetFIFOWordCount(APP_ADC_MODULE, ADC_FIFO_NUM_0);
        UARTprintf("Number of samples in FIFO:%d.\n", fifoWordCnt);
        UARTprintf("FIFO Data:\n", -1);
        for (loopcnt = 0U; loopcnt < fifoWordCnt; loopcnt++)
        {
            fifoData = ADCGetFIFOData(APP_ADC_MODULE, ADC_FIFO_NUM_0);
            stepID   = ((fifoData & ADC_FIFODATA_ADCCHNLID_MASK) >>
                        ADC_FIFODATA_ADCCHNLID_SHIFT);
            fifoData = ((fifoData & ADC_FIFODATA_ADCDATA_MASK) >>
                        ADC_FIFODATA_ADCDATA_SHIFT);
            voltageLvl  = fifoData * (uint32_t) APP_ADC_REF_VOLTAGE;
            voltageLvl /= (uint32_t) APP_ADC_RANGE_MAX;
            UARTprintf("Step ID : %d.       Voltage Level:%dmV\n",
                       (stepID + 1U), voltageLvl);
        }
        AppADCStop();
        /* Power down ADC */
        ADCPowerUp(APP_ADC_MODULE, FALSE);
        /* Disable ADC module */
        configStatus = PMHALModuleModeSet(PMHAL_PRCM_MOD_ADC,
                                          PMHAL_PRCM_MODULE_MODE_DISABLED,
                                          PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != configStatus)
        {
            UARTPuts("Error in ADC module disable.\n", -1);
        }
        UARTPuts("\nApplication is completed.\n", -1);;
    }
    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static void AppADCIntrISR(void *handle)
{
    uint32_t status;

    UARTPuts("\nIn ISR...\n", -1);
    status = ADCGetIntrStatus(APP_ADC_MODULE);
    ADCClearIntrStatus(APP_ADC_MODULE, status);
    if (ADC_INTR_SRC_END_OF_SEQUENCE == (status & ADC_INTR_SRC_END_OF_SEQUENCE))
    {
        UARTPuts("End of sequence interrupt occurred.\n", -1);
    }
    if (ADC_INTR_SRC_FIFO0_THRESHOLD == (status & ADC_INTR_SRC_FIFO0_THRESHOLD))
    {
        UARTPuts("FIFO 0 threshold interrupt occurred.\n", -1);
    }
    if (ADC_INTR_SRC_FIFO0_OVERRUN == (status & ADC_INTR_SRC_FIFO0_OVERRUN))
    {
        UARTPuts("FIFO 0 overrun interrupt occurred.\n", -1);
    }
    if (ADC_INTR_SRC_FIFO0_UNDERFLOW == (status & ADC_INTR_SRC_FIFO0_UNDERFLOW))
    {
        UARTPuts("FIFO 0 underflow interrupt occurred.\n", -1);
    }
    if (ADC_INTR_SRC_FIFO1_THRESHOLD == (status & ADC_INTR_SRC_FIFO1_THRESHOLD))
    {
        UARTPuts("FIFO 1 threshold interrupt occurred.\n", -1);
    }
    if (ADC_INTR_SRC_FIFO1_OVERRUN == (status & ADC_INTR_SRC_FIFO1_OVERRUN))
    {
        UARTPuts("FIFO 1 overrun interrupt occurred.\n", -1);
    }
    if (ADC_INTR_SRC_FIFO1_UNDERFLOW == (status & ADC_INTR_SRC_FIFO1_UNDERFLOW))
    {
        UARTPuts("FIFO 1 underflow interrupt occurred.\n", -1);
    }
    if (ADC_INTR_SRC_OUT_OF_RANGE == (status & ADC_INTR_SRC_OUT_OF_RANGE))
    {
        UARTPuts("Out of range interrupt occurred.\n", -1);
    }
    isrFlag = 0U;
    ADCWriteEOI(APP_ADC_MODULE);
}

static int32_t AppADCInit(void)
{
    adcRevisionId_t revId;
    int32_t         configStatus = STW_EFAIL;

    /* Get ADC information */
    ADCGetRevisionId(APP_ADC_MODULE, &revId);
    UARTPuts("ADC Revision ID:\n", -1);
    UARTprintf("Scheme            : 0x%x.\n", revId.scheme);
    UARTprintf("Functional number : 0x%x.\n", revId.func);
    UARTprintf("RTL revision      : 0x%x.\n", revId.rtlRev);
    UARTprintf("Major revision    : 0x%x.\n", revId.major);
    UARTprintf("Minor revision    : 0x%x.\n", revId.minor);
    UARTprintf("Custom revision   : 0x%x.\n", revId.custom);
    /* Clear All interrupt status */
    ADCClearIntrStatus(APP_ADC_MODULE, ADC_INTR_STATUS_ALL);
    /* Power up AFE */
    ADCPowerUp(APP_ADC_MODULE, TRUE);
    /* Wait for 4us at least */
    AppADCWait();
    /* Do the internal calibration */
    ADCInit(APP_ADC_MODULE, FALSE, 0U, 0U);
    /* Configure ADC divider*/
    configStatus = ADCSetClkDivider(APP_ADC_MODULE, APP_ADC_DIV);

    return configStatus;
}

static void AppADCStart(void)
{
    adcSequencerStatus_t status;

    /* Check if FSM is idle */
    ADCGetSequencerStatus(APP_ADC_MODULE, &status);
    while ((ADC_ADCSTAT_FSM_BUSY_IDLE != status.fsmBusy) &&
           ADC_ADCSTAT_STEP_ID_IDLE != status.stepId)
    {
        ADCGetSequencerStatus(APP_ADC_MODULE, &status);
    }
    /* Start ADC conversion */
    ADCStart(APP_ADC_MODULE, TRUE);
}

static void AppADCStop(void)
{
    adcSequencerStatus_t status;

    /* Disable all/enabled steps */
    ADCStepEnable(APP_ADC_MODULE, ADC_STEP_2, FALSE);
    ADCStepEnable(APP_ADC_MODULE, ADC_STEP_3, FALSE);
    ADCStepEnable(APP_ADC_MODULE, ADC_STEP_4, FALSE);
    ADCStepEnable(APP_ADC_MODULE, ADC_STEP_5, FALSE);
    ADCStepEnable(APP_ADC_MODULE, ADC_STEP_6, FALSE);
    /* Wait for FSM to go IDLE */
    ADCGetSequencerStatus(APP_ADC_MODULE, &status);
    while ((ADC_ADCSTAT_FSM_BUSY_IDLE != status.fsmBusy) &&
           ADC_ADCSTAT_STEP_ID_IDLE != status.stepId)
    {
        ADCGetSequencerStatus(APP_ADC_MODULE, &status);
    }
    /* Stop ADC */
    ADCStart(APP_ADC_MODULE, FALSE);
    /* Wait for FSM to go IDLE */
    ADCGetSequencerStatus(APP_ADC_MODULE, &status);
    while ((ADC_ADCSTAT_FSM_BUSY_IDLE != status.fsmBusy) &&
           ADC_ADCSTAT_STEP_ID_IDLE != status.stepId)
    {
        ADCGetSequencerStatus(APP_ADC_MODULE, &status);
    }
}

static void AppADCWait(void)
{
    uint32_t time;

    /* One tick of 32kHz is 31.25us */
    time  = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
    time += 2;
    while (time > (HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR)))
    {}
}

