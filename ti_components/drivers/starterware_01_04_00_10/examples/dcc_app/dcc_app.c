/**
 *  \file     dcc_app.c
 *
 *  \brief    This file contains DCC test code for single shot mode.
 *            DPLLDSP_GMAC_H12 clock is used as clock to be tested against
 *            SYS_CLK1 which is reference clock.
 *
 *  \details  DCC operational mode is set to single shot mode.
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
#include "pmhal_prcm.h"
#include "pmhal_mm.h"
#include "soc_defines.h"
#include "hw_types.h"
#include "hw_dcc.h"
#include "interrupt.h"
#include "platform.h"
#include "uartStdio.h"
#include "hw_core_cm_core.h"
#include "hw_counter_32k.h"
#include "irq_xbar.h"
#include "dcc.h"
#include "pm/pmhal/pmhal_cm.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#define APP_DCC_MODULE_INST             (SOC_DCC4_BASE)
#define APP_DCC_MODE                    (DCC_OPERATION_MODE_SINGLE_SHOT2)
#define APP_DCC_CLK_SRC0                (DCC_CLK_SRC0_SYS_CLK1)
#define APP_DCC_CLK_SRC1                (DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_H12)
#define APP_DCC_CLK_SRC1_DRIFT          (5U)
#define APP_SYS_CLK1_FREQ_KHZ           ((uint32_t) 20000)
#define DCC_SRC0_COUNT_MAX              (0xFFFFFU)
#define DCC_SRC0_VALID_MAX              (0x0FFFFU)
#define DCC_SRC1_COUNT_MAX              (0xFFFFFU)
#define APP_DCC_DPLL_ID                 (PMHAL_PRCM_DPLL_DSP_GMAC)
#define APP_DCC_DPLL_POST_DIV           (PMHAL_PRCM_DPLL_POST_DIV_H12)
#define APP_DCC_DPLL_POST_DIV_MAX       (64U)

#define APP_DCC_ERROR_INT_M4                 (44U)
#define APP_DCC_DONE_INT_M4                  (45U)
#ifdef BUILD_M4
    #define APP_XBAR_CPU                        (CPU_IPU1)
    #define APP_XBAR_INST_ERROR                 (XBAR_INST_IPU1_IRQ_44)
    #define APP_XBAR_INST_DONE                  (XBAR_INST_IPU1_IRQ_45)
    #define APP_XBAR_INTR_SOURCE_ERROR          (DCC4_IRQ_ERROR)
    #define APP_XBAR_INTR_SOURCE_DONE           (DCC4_IRQ_DONE)
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
volatile uint32_t isrFlag = 0U, lastIntr = 2;
/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This function is used to configure and enable CPU interrupt.
 *
 * \param   intrType        Interrupt for which crossbar is to be configured.
 *                          Refer enum #dccIntrType_t.
 *
 * \retval  status          Configuration status.
 */
static uint32_t DCCAppXBarConfig(uint32_t intrType);

/**
 * \brief   This Interrupt Service Routine for DCC error interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void DCCAppErrorIntrISR(void *handle);

/**
 * \brief   This Interrupt Service Routine for DCC DONE interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void DCCAppDoneIntrISR(void *handle);

/**
 * \brief   This function returns reference clock frequency.
 *
 * \param   refClk          Clock whose frequency to be calculated.
 *
 * \retval  frequency       Frequency of the given clock in KHz.
 */
static uint32_t DCCAppGetTestClkfreqKHz(uint32_t refClk);

/**
 * \brief   This function changes the test clock frequency.
 *
 * \param   None
 *
 * \retval  status          Configuration status.
 */
static int32_t DCCAppTestClkFreqChange(void);

/**
 * \brief   This function returns seed value for COUNT1.
 *
 * \param   refClkFreq      Reference clock frequency in KHz.
 * \param   testClkFreq     Test clock frequency in KHz.
 * \param   refClkRatioNum  Reference clock ratio number.
 * \param   testClkRatioNum Test clock ratio number.
 * \param   drfitPer        Allowed drift in test clock in percentage.
 * \param   configParams    DCC configuration parameters.
 *                          Refer enum #dccConfigParams_t.
 *
 * \retval  None.
 */
static void DCCAppSetSeedVals(uint32_t           refClkFreq,
                              uint32_t           testClkFreq,
                              uint32_t           refClkRatioNum,
                              uint32_t           testClkRatioNum,
                              uint32_t           drfitPer,
                              dccConfigParams_t *configParams);

/**
 * \brief   This function returns least integral ratio for given clocks.
 *
 * \param   refClkFreq      Reference clock frequency in KHz.
 * \param   testClkFreq     Test clock frequency in KHz.
 * \param   refClkRatioNum  Reference clock ratio number.
 * \param   testClkRatioNum Test clock ratio number.
 *
 * \retval  None.
 */
static void DCCAppGetClkRatio(uint32_t  refClkFreq,
                              uint32_t  testClkFreq,
                              uint32_t *refClkRatioNum,
                              uint32_t *testClkRatioNum);

/**
 * \brief   This function is used for misc configuration needed by DCC App.
 *
 * \param   none.
 *
 * \retval  none.
 */
void DCCAppMiscConfig(uint32_t clksrc);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int main(void)
{
    int32_t           configStatus;
    uint32_t          xBarStatus, testClkFreq, refClkRatioNum,
                      testClkRatioNum, refClkFreq;
    dccConfigParams_t configParams;

    /* Configure UARTStdioInit */
    PlatformUartConsoleSetPinMux();
    UARTStdioInit();
    UARTPuts("\nStarting application...\n", -1);

    refClkFreq = APP_SYS_CLK1_FREQ_KHZ;
    /* Get the test clock frequency */
    testClkFreq = DCCAppGetTestClkfreqKHz(APP_DCC_CLK_SRC1);
    if (0U == testClkFreq)
    {
        UARTPuts("Error in calculating Frequency.\n", -1);
    }
    /* Get clock ratio */
    DCCAppGetClkRatio(refClkFreq,
                      testClkFreq,
                      &refClkRatioNum,
                      &testClkRatioNum);

    DCCAppMiscConfig(APP_DCC_CLK_SRC1);
    /* Initialize DCC configuration parameters */
    configParams.mode    = APP_DCC_MODE;
    configParams.clkSrc0 = APP_DCC_CLK_SRC0;
    configParams.clkSrc1 = APP_DCC_CLK_SRC1;
    /* Get the seed values for given clock selections and allowed drift */
    DCCAppSetSeedVals(refClkFreq,
                      testClkFreq,
                      refClkRatioNum,
                      testClkRatioNum,
                      APP_DCC_CLK_SRC1_DRIFT,
                      &configParams);

    /* Configure XBar and interrupt */
    xBarStatus  = DCCAppXBarConfig(DCC_INTERRUPTS_ERROR);
    xBarStatus |= DCCAppXBarConfig(DCC_INTERRUPTS_DONE);
    if (SUCCESS == xBarStatus)
    {
        /* Enable DCC module */
        configStatus = PMHALModuleModeSet(PMHAL_PRCM_MOD_DCC1,
                                          PMHAL_PRCM_MODULE_MODE_ENABLED,
                                          PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS == configStatus)
        {
            UARTPuts("Module enabled.\n", -1);
            /* Configure DCC module */
            configStatus = DCCSetConfig(APP_DCC_MODULE_INST, &configParams);
            if (STW_EFAIL == configStatus)
            {
                UARTPuts("ERROR in DCC configuration.\n", -1);
            }
            else
            {
                /* Enable DCC interrupts */
                DCCEnableIntr(APP_DCC_MODULE_INST, DCC_INTERRUPTS_ERROR);
                DCCEnableIntr(APP_DCC_MODULE_INST, DCC_INTERRUPTS_DONE);
                /* Enable DCC operation/module */
                DCCEnable(APP_DCC_MODULE_INST, TRUE);
                /* Wait here till interrupt is generated */
                while (0U == isrFlag) ;
                if (1U == lastIntr)
                {
                    isrFlag = 0U;
                    /* Change test clock frequency */
                    if (FAIL == DCCAppTestClkFreqChange())
                    {
                        /* Error in configuration */
                    }
                    /* Configure DCC module */
                    configStatus = DCCSetConfig(APP_DCC_MODULE_INST,
                                                &configParams);
                    if (STW_EFAIL == configStatus)
                    {
                        UARTPuts("ERROR in DCC configuration.\n", -1);
                    }
                    else
                    {
                        /* Enable DCC interrupts */
                        DCCEnableIntr(APP_DCC_MODULE_INST,
                                      DCC_INTERRUPTS_ERROR);
                        DCCEnableIntr(APP_DCC_MODULE_INST, DCC_INTERRUPTS_DONE);
                        /* Enable DCC operation/module */
                        DCCEnable(APP_DCC_MODULE_INST, TRUE);
                        /* Wait here till interrupt is generated */
                        while (0U == isrFlag) ;
                        isrFlag = 0U;
                        if (0U == lastIntr)
                        {
                            UARTPuts("Application successfully executed.\n",
                                     -1);
                        }
                        else
                        {
                            UARTPuts("Try to run application again.\n",
                                     -1);
                        }
                    }
                }
                else
                {
                    UARTPuts("Try to run application again.\n", -1);
                }
            }
        }
        else
        {
            UARTPuts("ERROR in enabling DCC module.\n", -1);
        }
    }
    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static uint32_t DCCAppXBarConfig(uint32_t intrType)
{
    uint32_t status = FAIL;

    /* Configure Cross bar instance and interrupt */
    PlatformUnlockMMR();
    switch (intrType)
    {
        case DCC_INTERRUPTS_ERROR:
            if (irq_xbar_success ==
                IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                               APP_XBAR_CPU, APP_XBAR_INST_ERROR,
                               APP_XBAR_INTR_SOURCE_ERROR))
            {
                /* Successfully configured CrossBar */
                status = SUCCESS;
            }
            else
            {
                UARTPuts("Error in configuring CrossBar.\n", -1);
            }
            if (SUCCESS == status)
            {
                /* Enable Error interrupt for DCC */
                Intc_Init();
                Intc_IntEnable(APP_DCC_ERROR_INT_M4);

                /* Register ISR */
                Intc_IntRegister(APP_DCC_ERROR_INT_M4,
                                 (IntrFuncPtr) DCCAppErrorIntrISR, 0);
                Intc_IntPrioritySet(APP_DCC_ERROR_INT_M4, 1, 0);
                Intc_SystemEnable(APP_DCC_ERROR_INT_M4);
            }
            break;
        case DCC_INTERRUPTS_DONE:
            if (irq_xbar_success ==
                IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                               APP_XBAR_CPU, APP_XBAR_INST_DONE,
                               APP_XBAR_INTR_SOURCE_DONE))
            {
                /* Successfully configured CrossBar */
                status = SUCCESS;
            }
            else
            {
                UARTPuts("Error in configuring CrossBar.\n", -1);
            }
            if (SUCCESS == status)
            {
                /* Enable Done and Error interrupt for DCC */
                Intc_Init();
                Intc_IntEnable(APP_DCC_DONE_INT_M4);

                /* Register ISR */
                Intc_IntRegister(APP_DCC_DONE_INT_M4,
                                 (IntrFuncPtr) DCCAppDoneIntrISR, 0);
                Intc_IntPrioritySet(APP_DCC_DONE_INT_M4, 1, 0);
                Intc_SystemEnable(APP_DCC_DONE_INT_M4);
            }
            break;
        default:
            status = FAIL;
            break;
    }
    return status;
}

static void DCCAppErrorIntrISR(void *handle)
{
    UARTPuts("In ISR...\n", -1);
    UARTPuts("ERROR interrupt generated.\n", -1);
    DCCClearIntrStatus(APP_DCC_MODULE_INST, DCC_INTERRUPTS_ERROR);
    isrFlag  = 1U;
    lastIntr = 0U;
}

static void DCCAppDoneIntrISR(void *handle)
{
    UARTPuts("In ISR...\n", -1);
    UARTPuts("DONE interrupt generated.\n", -1);
    DCCClearIntrStatus(APP_DCC_MODULE_INST, DCC_INTERRUPTS_DONE);
    isrFlag  = 1U;
    lastIntr = 1U;
}

static uint32_t DCCAppGetTestClkfreqKHz(uint32_t refClk)
{
    uint32_t multilpier = 1, divider = 1, postDivider;
    uint32_t clkFreqKHz = 0U;
    pmhalPrcmPllPostDivValue_t dpllPostDivider;

    multilpier = 250U;
    divider    = 4U;
    dpllPostDivider.postDivId   = APP_DCC_DPLL_POST_DIV;
    dpllPostDivider.configValue = 1000;
    if (PM_SUCCESS == PMHALCMDpllGetPostDiv(APP_DCC_DPLL_ID,
                                            &dpllPostDivider, 1))
    {
        postDivider = dpllPostDivider.configValue;
        clkFreqKHz  = (2 * multilpier * APP_SYS_CLK1_FREQ_KHZ / (postDivider)
                       / (divider + 1));
    }
    else
    {
        clkFreqKHz = 0U;
        UARTPuts("Error in calculating frequency.\n", -1);
    }
    return clkFreqKHz;
}

static void DCCAppSetSeedVals(uint32_t           refClkFreq,
                              uint32_t           testClkFreq,
                              uint32_t           refClkRatioNum,
                              uint32_t           testClkRatioNum,
                              uint32_t           drfitPer,
                              dccConfigParams_t *configParams)
{
    uint32_t maxFreqKHz, maxCntLimit;
    uint32_t maxRefCnt, minRefCnt;
    uint64_t mulVar;

    /* Find maximum frequency between test and reference clock */
    if (refClkFreq > testClkFreq)
    {
        maxFreqKHz  = refClkFreq;
        maxCntLimit = DCC_SRC0_COUNT_MAX;
    }
    else
    {
        maxFreqKHz  = testClkFreq;
        maxCntLimit = DCC_SRC1_COUNT_MAX;
    }
    /* Calculate seed values for 0% drift */
    if (maxFreqKHz == refClkFreq)
    {
        configParams->seedSrc0 = maxCntLimit / refClkRatioNum;
        configParams->seedSrc0 = configParams->seedSrc0 * refClkRatioNum;
        mulVar = ((uint64_t) (configParams->seedSrc0) *
                  (uint32_t) (testClkRatioNum));
        configParams->seedSrc1   = (uint32_t) (mulVar / refClkRatioNum);
        configParams->seedValid0 = refClkRatioNum;
    }
    else
    {
        configParams->seedSrc1 = maxCntLimit / testClkRatioNum;
        configParams->seedSrc1 = configParams->seedSrc1 * testClkRatioNum;
        mulVar = ((uint64_t) (configParams->seedSrc1) *
                  (uint32_t) (refClkRatioNum));
        configParams->seedSrc0   = (uint32_t) (mulVar / testClkRatioNum);
        configParams->seedValid0 = 1U;
    }
    /* Applying allowed drift */
    if (((DCC_SRC0_COUNT_MAX + DCC_SRC0_VALID_MAX) <
         (configParams->seedSrc0 * (100U + drfitPer) / 100U)))
    {
        /* Seed values with drift exceeds maximum range */
        UARTPuts("Seed values with drift exceeds allowed range.\n", -1);
        UARTPuts("Application will run with 0% allowed drift.\n", -1);
    }
    else if (100U < drfitPer)
    {
        /* Error percentage is greater than 100 */
        UARTPuts("Wrong drift percentage. Not applying drift.\n", -1);
        UARTPuts("Application will run with 0% allowed drift.\n", -1);
    }
    else
    {
        maxRefCnt = (configParams->seedSrc0 * (100U + drfitPer) / 100U);
        minRefCnt = (configParams->seedSrc0 * (100U - drfitPer) / 100U);
        if (DCC_SRC0_VALID_MAX < (maxRefCnt - minRefCnt))
        {
            UARTPuts("Seed value for valid count exceeds allowed range.\n", -1);
            UARTPuts("Application will run with 0% allowed drift.\n", -1);
        }
        else
        {
            if (maxRefCnt == minRefCnt)
            {
                configParams->seedValid0 = 1U;
            }
            else
            {
                configParams->seedSrc0   = minRefCnt;
                configParams->seedValid0 = (maxRefCnt - minRefCnt);
            }
        }
    }
    UARTPuts("Seed values calculation done.\n", -1);
}

static int32_t DCCAppTestClkFreqChange(void)
{
    pmhalPrcmPllPostDivValue_t dpllPostDivider;
    uint32_t status = FAIL;

    dpllPostDivider.postDivId   = APP_DCC_DPLL_POST_DIV;
    dpllPostDivider.configValue = 1000U;
    if (PM_SUCCESS == PMHALCMDpllGetPostDiv(APP_DCC_DPLL_ID,
                                            &dpllPostDivider, 1))
    {
        dpllPostDivider.configValue++;
        dpllPostDivider.configValue %= APP_DCC_DPLL_POST_DIV_MAX;
        if (PM_SUCCESS == PMHALCMDpllSetPostDiv(APP_DCC_DPLL_ID,
                                                &dpllPostDivider, 1))
        {
            status = SUCCESS;
            UARTPuts("Frequency configuration successful.\n", -1);
        }
        else
        {
            status = FAIL;
            UARTPuts("Error in configuring frequency.\n", -1);
        }
    }
    else
    {
        status = FAIL;
        UARTPuts("Error in configuring frequency.\n", -1);
    }
    return status;
}

static void DCCAppGetClkRatio(uint32_t  refClkFreq,
                              uint32_t  testClkFreq,
                              uint32_t *refClkRatioNum,
                              uint32_t *testClkRatioNum)
{
    uint32_t loopCnt, hcf = 1U;

    for (loopCnt = 1;
         (loopCnt <= refClkFreq) || (loopCnt <= testClkFreq);
         loopCnt++)
    {
        if ((refClkFreq % loopCnt == 0) && (testClkFreq % loopCnt == 0))
        {
            hcf = loopCnt;
        }
    }
    *refClkRatioNum  = (refClkFreq / hcf);
    *testClkRatioNum = (testClkFreq / hcf);
}

void DCCAppMiscConfig(uint32_t clksrc)
{
    int32_t configStatus;

    if (DCC_CLK_SRC1_DCC4_DPLLDSP_GMAC_H12 == clksrc)
    {
        /* Enable CPGMAC for DPLLCORE_M2 */
        configStatus = PMHALModuleModeSet(PMHAL_PRCM_MOD_CPGMAC,
                                          PMHAL_PRCM_MODULE_MODE_ENABLED,
                                          PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != configStatus)
        {
            UARTPuts("Error in Misc Config.\n", -1);
        }
        else
        {
            UARTPuts("Misc Config done.\n", -1);
        }
    }
}

