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
 * main_c66x.c
 */
#include <stdio.h>
#include "stdint.h"
#include <common/stw_types.h>
#include <common/stw_dataTypes.h>
#include "soc_defines.h"
#include "soc.h"
#include "uartStdio.h"
#include "interrupt.h"
#include "platform.h"
#include "stw_platformEcc.h"
#include "irq_xbar.h"
#include "hw_types.h"
#include "hw_emif.h"
#include "ocmc_ecc_l1.h"
#include "edma.h"
#include "dsp_icfg.h"

/* Test case options */
#define DSP_L1P_CACHE_TEST              ('1')
#define DSP_L1P_DMA_TEST                ('2')
#define DSP_L2_L1D_ACCESS_ERROR_TEST    ('3')
#define DSP_L2_L1P_ACCESS_ERROR_TEST    ('4')
#define DSP_L2_DMA_ACCESS_ERROR_TEST    ('5')
#define DSP_L2_VICTIM_ACCESS_ERROR_TEST ('6')
#define DSP_ECC_RUN_ALL                 ('7')

#define EXIT(opt)      (('x' == opt) || ('X' == opt))

#define DSP_IRQ_113                      (113U)
#define DSP_IRQ_116                      (116U)
#define DSP_IRQ_117                      (117U)
#define DSP_ECC_NUM_BYTES                (128U)

static void mainMenu(char *option);
static int32_t dspEccL1PCacheTest(void);
static int32_t dspEccL1PDmaTest(void);
static int32_t dspEccL2L1DAccessErrTest(void);
static int32_t dspEccL2L1PAccessErrTest(void);
static int32_t dspEccL2DmaAccessErrTest(void);
static int32_t dspEccL2VictimAccessErrTest(void);

/* Global variables are defined which are used to generate accesses to
 * different ways of the L2 cache line.
 */
#ifdef __cplusplus
#pragma DATA_SECTION(".my_l2_data_sec1")
#else
#pragma DATA_SECTION(dummyVar1, ".my_l2_data_sec1")
#endif
volatile uint32_t dummyVar1 = 0U;
#ifdef __cplusplus
#pragma DATA_SECTION(".my_l2_data_sec2")
#else
#pragma DATA_SECTION(dummyVar2, ".my_l2_data_sec2")
#endif
volatile uint32_t dummyVar2 = 0U;
#ifdef __cplusplus
#pragma DATA_SECTION(".my_l2_data_sec3")
#else
#pragma DATA_SECTION(dummyVar3, ".my_l2_data_sec3")
#endif
volatile uint32_t dummyVar3 = 0U;
#ifdef __cplusplus
#pragma DATA_SECTION(".my_l2_data_sec4")
#else
#pragma DATA_SECTION(dummyVar4, ".my_l2_data_sec4")
#endif
volatile uint32_t dummyVar4 = 0U;
#ifdef __cplusplus
#pragma DATA_SECTION(".my_l2_data_sec5")
#else
#pragma DATA_SECTION(dummyVar5, ".my_l2_data_sec5")
#endif
volatile uint32_t dummyVar5 = 0U;
volatile uint32_t gInterruptRecd = 0U;
volatile uint32_t gCurrEccTest = 0U;

int main(void)
{
    volatile uint32_t testDone = 1;
    int32_t           retVal   = STW_SOK;
    char mainMenuOption;

    PlatformUartConsoleSetPinMux();
    UARTStdioInit();

    while (testDone)
    {
        mainMenu(&mainMenuOption);
        switch (mainMenuOption)
        {
            case DSP_L1P_CACHE_TEST:
                gCurrEccTest = DSP_L1P_CACHE_TEST;
                retVal = dspEccL1PCacheTest();
                if (STW_SOK == retVal)
                {
                    UARTPuts("\n  DSP_L1P_CACHE_TEST: Pass!!", -1);
                }
                else
                {
                    UARTPuts("\n  DSP_L1P_CACHE_TEST: Fail!!", -1);
                }
                break;
            case DSP_L1P_DMA_TEST:
                gCurrEccTest = DSP_L1P_DMA_TEST;
                retVal = dspEccL1PDmaTest();
                if (STW_SOK == retVal)
                {
                    UARTPuts("\n  DSP_L1P_DMA_TEST: Pass!!", -1);
                }
                else
                {
                    UARTPuts("\n  DSP_L1P_DMA_TEST: Fail!!", -1);
                }
                break;
            case DSP_L2_L1D_ACCESS_ERROR_TEST:
                gCurrEccTest = DSP_L2_L1D_ACCESS_ERROR_TEST;
                retVal = dspEccL2L1DAccessErrTest();
                if (STW_SOK == retVal)
                {
                    UARTPuts("\n  DSP_L2_L1D_ACCESS_ERROR_TEST: Pass!!", -1);
                }
                else
                {
                    UARTPuts("\n  DSP_L2_L1D_ACCESS_ERROR_TEST: Fail!!", -1);
                }
                break;
            case DSP_L2_L1P_ACCESS_ERROR_TEST:
                gCurrEccTest = DSP_L2_L1P_ACCESS_ERROR_TEST;
                retVal = dspEccL2L1PAccessErrTest();
                if (STW_SOK == retVal)
                {
                    UARTPuts("\n  DSP_L2_L1P_ACCESS_ERROR_TEST: Pass!!", -1);
                }
                else
                {
                    UARTPuts("\n  DSP_L2_L1P_ACCESS_ERROR_TEST: Fail!!", -1);
                }
                break;
            case DSP_L2_DMA_ACCESS_ERROR_TEST:
                gCurrEccTest = DSP_L2_DMA_ACCESS_ERROR_TEST;
                retVal = dspEccL2DmaAccessErrTest();
                if (STW_SOK == retVal)
                {
                    UARTPuts("\n  DSP_L2_DMA_ACCESS_ERROR_TEST: Pass!!", -1);
                }
                else
                {
                    UARTPuts("\n  DSP_L2_DMA_ACCESS_ERROR_TEST: Fail!!", -1);
                }
                break;
            case DSP_L2_VICTIM_ACCESS_ERROR_TEST:
                gCurrEccTest = DSP_L2_VICTIM_ACCESS_ERROR_TEST;
                retVal = dspEccL2VictimAccessErrTest();
                if (STW_SOK == retVal)
                {
                    UARTPuts("\n  DSP_L2_VICTIM_ACCESS_ERROR_TEST: Pass!!", -1);
                }
                else
                {
                    UARTPuts("\n  DSP_L2_VICTIM_ACCESS_ERROR_TEST: Fail!!", -1);
                }
                break;
            case DSP_ECC_RUN_ALL:
                gCurrEccTest = DSP_L1P_CACHE_TEST;
                retVal = dspEccL1PCacheTest();
                if (STW_SOK == retVal)
                {
                    UARTPuts("\n  DSP_L1P_CACHE_TEST: Pass!!", -1);
                }
                else
                {
                    UARTPuts("\n  DSP_L1P_CACHE_TEST: Fail!!", -1);
                }
                gCurrEccTest = DSP_L1P_DMA_TEST;
                retVal = dspEccL1PDmaTest();
                if (STW_SOK == retVal)
                {
                    UARTPuts("\n  DSP_L1P_DMA_TEST: Pass!!", -1);
                }
                else
                {
                    UARTPuts("\n  DSP_L1P_DMA_TEST: Fail!!", -1);
                }
                gCurrEccTest = DSP_L2_L1D_ACCESS_ERROR_TEST;
                retVal = dspEccL2L1DAccessErrTest();
                if (STW_SOK == retVal)
                {
                    UARTPuts("\n  DSP_L2_L1D_ACCESS_ERROR_TEST: Pass!!", -1);
                }
                else
                {
                    UARTPuts("\n  DSP_L2_L1D_ACCESS_ERROR_TEST: Fail!!", -1);
                }
                gCurrEccTest = DSP_L2_L1P_ACCESS_ERROR_TEST;
                retVal = dspEccL2L1PAccessErrTest();
                if (STW_SOK == retVal)
                {
                    UARTPuts("\n  DSP_L2_L1P_ACCESS_ERROR_TEST: Pass!!", -1);
                }
                else
                {
                    UARTPuts("\n  DSP_L2_L1P_ACCESS_ERROR_TEST: Fail!!", -1);
                }
                gCurrEccTest = DSP_L2_DMA_ACCESS_ERROR_TEST;
                retVal = dspEccL2DmaAccessErrTest();
                if (STW_SOK == retVal)
                {
                    UARTPuts("\n  DSP_L2_DMA_ACCESS_ERROR_TEST: Pass!!", -1);
                }
                else
                {
                    UARTPuts("\n  DSP_L2_DMA_ACCESS_ERROR_TEST: Fail!!", -1);
                }
                gCurrEccTest = DSP_L2_VICTIM_ACCESS_ERROR_TEST;
                retVal = dspEccL2VictimAccessErrTest();
                if (STW_SOK == retVal)
                {
                    UARTPuts("\n  DSP_L2_VICTIM_ACCESS_ERROR_TEST: Pass!!", -1);
                }
                else
                {
                    UARTPuts("\n  DSP_L2_VICTIM_ACCESS_ERROR_TEST: Fail!!", -1);
                }
                break;
            default :
                UARTPuts("\n  ECC test exiting...", -1);
                testDone = 0U;
                break;
        }
    }
    return retVal;
}

static void mainMenu(char *option)
{
    while (1)
    {
        UARTPuts("\n\n**** DSP ECC TEST ****", -1);
        UARTPuts("\nMenu:", -1);
        UARTPuts("\n1. DSP L1P CACHE TEST", -1);
        UARTPuts("\n2. DSP L1P DMA TEST", -1);
        UARTPuts("\n3. DSP L2 L1D ACCESS ERROR TEST", -1);
        UARTPuts("\n4. DSP L2 L1P ACCESS ERROR TEST", -1);
        UARTPuts("\n5. DSP L2 DMA ACCESS ERROR TEST", -1);
        UARTPuts("\n6. DSP L2 VICTIM ACCESS ERROR TEST", -1);
        UARTPuts("\n7. Run All Back to Back", -1);
        UARTPuts("\nx. Exit", -1);
        UARTPuts("\nSelect ECC TEST : ", -1);
        /* Get option */
        UARTGets(option, 1);

        if((DSP_L1P_CACHE_TEST              == *option) ||
           (DSP_L1P_DMA_TEST                == *option) ||
           (DSP_L2_L1D_ACCESS_ERROR_TEST    == *option) ||
           (DSP_L2_L1P_ACCESS_ERROR_TEST    == *option) ||
           (DSP_L2_DMA_ACCESS_ERROR_TEST    == *option) ||
           (DSP_L2_VICTIM_ACCESS_ERROR_TEST == *option) ||
           (DSP_ECC_RUN_ALL == *option) ||
            EXIT(*option))
        {
            break;
        }
        else
        {
            UARTPuts("\nEnter Valid option\n", -1);
        }
    }
}
#ifdef __cplusplus
#pragma CODE_SECTION(".my_l1p_code_sec1")
#else
#pragma CODE_SECTION(dummyAdd, ".my_l1p_code_sec1")
#endif
int32_t dummyAdd ( int32_t a, int32_t b)
{
    return a + b;
}
#ifdef __cplusplus
#pragma CODE_SECTION(".my_l1p_code_sec2")
#else
#pragma CODE_SECTION(dummySub, ".my_l1p_code_sec2")
#endif
int32_t dummySub (int32_t a, int32_t b)
{
    return a - b;
}

/*
 * ISR for DSP L1P ECC Errors
 */
static void dspEccL1PDmaErrHandler(void *handle)
{
    int32_t retVal = STW_SOK;
    eccDspErrStatus_t errStatus = {0U};
    eccDspErrInfo_t   eccDspInfo = {0U};

    retVal = ECCDspIntrGetErrStatus(&errStatus);
    if ((STW_SOK == retVal) && (1U == errStatus.l1PDmaAccessErr))
    {
        ECCDspGetErrInfo(ECC_DSP_MEM_TYPE_L1P, &eccDspInfo);
        if (eccDspInfo.errRamOrCache == 1U)
        {
            UARTprintf("\nDSP L1P DMA Error @ address = 0x%x",
                     eccDspInfo.errAddress, -1);
            ECCDspIntrClrErrStatus(&errStatus);
            gInterruptRecd = 1U;
        }
        else
        {
            gInterruptRecd = 0U;
        }
    }
}

static void dspEccL2unregisterIntr(void)
{
    Intc_SystemDisable(DSP_IRQ_116);
    Intc_IntUnregister(DSP_IRQ_116);
    Intc_SystemDisable(DSP_IRQ_117);
    Intc_IntUnregister(DSP_IRQ_117);
}
/*
 * ISR for DSP L2 ECC Errors
 */
static void dspEccL2UnCorrErrHandler(void *handle)
{
    int32_t retVal = STW_SOK;
    eccDspErrStatus_t errStatus = {0U};
    eccDspErrInfo_t   eccDspInfo = {0U};

    retVal = ECCDspIntrGetErrStatus(&errStatus);
    if (STW_SOK == retVal)
    {
        switch(gCurrEccTest)
        {
            case DSP_L2_L1D_ACCESS_ERROR_TEST:
                if (1U == errStatus.l2L1DAccessErr)
                {
                    gInterruptRecd = 1U;
                }
                else
                {
                    UARTprintf("\nError Not generated");
                }
                break;
            case DSP_L2_L1P_ACCESS_ERROR_TEST:
                if (1U == errStatus.l2L1PAccessErr)
                {
                    gInterruptRecd = 1U;
                    /* Invalidate L1P */
                    DSPICFGCacheInvalidateAll(SOC_DSP_ICFG_BASE,
                                              DSPICFG_MEM_L1P);
                    /* Configure Cache size of L1P as disabled. */
                    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1P,
                       DSPICFG_CACHE_SIZE_L1_DISABLED);
                    /* Disable ECC for L2 */
                    ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                                 ECC_DISABLE,
                                 1000U);
                    dspEccL2unregisterIntr();
                }
                else
                {
                    UARTprintf("\nError Not generated");
                }
                break;
            case DSP_L2_DMA_ACCESS_ERROR_TEST:
                if (1U == errStatus.l2DmaAccessErr)
                {
                    gInterruptRecd = 1U;
                }
                else
                {
                    UARTprintf("\nError Not generated");
                }
                break;
            case DSP_L2_VICTIM_ACCESS_ERROR_TEST:
                if (1U == errStatus.l2VictimsErr)
                {
                    gInterruptRecd = 1U;
                }
                else
                {
                    UARTprintf("\nError Not generated");
                }
                break;
            default :
                UARTprintf("\nError Recieved for incorrect test!!");
                gInterruptRecd = 0U;
        }
        ECCDspGetErrInfo(ECC_DSP_MEM_TYPE_L2, &eccDspInfo);
        ECCDspIntrClrErrStatus(&errStatus);
        UARTprintf("\nDSP L2 Uncorrectable Error @ address = 0x%x",
                     eccDspInfo.errAddress);
        UARTprintf("\n             @ Ram(1)/Cache(0) = %d",
                     eccDspInfo.errRamOrCache, -1);
        UARTprintf("\n             @ Bit Position = %d",
                     eccDspInfo.errL2BitPosition, -1);
        UARTprintf(
            "\n             @ Single Bit(0)/Double Bit(1)/Parity(3) = %d",
            eccDspInfo.errL2Type, -1);
        UARTprintf("\n             @ L2 Cache error in Way %d",
            eccDspInfo.errL2way, -1);
        UARTprintf("\n             @ Correctable Parity Error Count = %d",
            eccDspInfo.errL2CorrectableCount, -1);
        UARTprintf("\n             @ Non-Correctable Parity Error count = %d",
            eccDspInfo.errL2NonCorrectableCount, -1);
    }
}
/*
 * ISR for DSP L2 ECC Errors
 */
static void dspEccL2CorrErrHandler(void *handle)
{
    int32_t retVal = STW_SOK;
    eccDspErrStatus_t errStatus = {0U};
    eccDspErrInfo_t   eccDspInfo = {0U};

    retVal = ECCDspIntrGetErrStatus(&errStatus);
    if (STW_SOK == retVal)
    {
        switch(gCurrEccTest)
        {
            case DSP_L2_L1D_ACCESS_ERROR_TEST:
                if (1U == errStatus.l2L1DAccessErr)
                {
                    gInterruptRecd = 1U;
                }
                else
                {
                    UARTprintf("\nError Not generated");
                }
                break;
            case DSP_L2_L1P_ACCESS_ERROR_TEST:
                if (1U == errStatus.l2L1PAccessErr)
                {
                    gInterruptRecd = 1U;
                    /* Invalidate L1P */
                    DSPICFGCacheInvalidateAll(SOC_DSP_ICFG_BASE,
                                              DSPICFG_MEM_L1P);
                    /* Configure Cache size of L1P as disabled. */
                    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1P,
                       DSPICFG_CACHE_SIZE_L1_DISABLED);
                    /* Disable ECC for L2 */
                    ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                                 ECC_DISABLE,
                                 1000U);
                    dspEccL2unregisterIntr();
                }
                else
                {
                    UARTprintf("\nError Not generated");
                }
                break;
            case DSP_L2_DMA_ACCESS_ERROR_TEST:
                if (1U == errStatus.l2DmaAccessErr)
                {
                    gInterruptRecd = 1U;
                }
                else
                {
                    UARTprintf("\nError Not generated");
                }
                break;
            case DSP_L2_VICTIM_ACCESS_ERROR_TEST:
                if (1U == errStatus.l2VictimsErr)
                {
                    gInterruptRecd = 1U;
                }
                else
                {
                    UARTprintf("\nError Not generated");
                }
                break;
            default :
                UARTprintf("\nError Recieved for incorrect test!!");
                gInterruptRecd = 0U;
        }
        ECCDspGetErrInfo(ECC_DSP_MEM_TYPE_L2, &eccDspInfo);
        ECCDspIntrClrErrStatus(&errStatus);
        UARTprintf("\nDSP L2 Correctable Error @ address = 0x%x",
                     eccDspInfo.errAddress);
        UARTprintf("\n             @ Ram(1)/Cache(0) = %d",
                     eccDspInfo.errRamOrCache, -1);
        UARTprintf("\n             @ Bit Position = %d",
                     eccDspInfo.errL2BitPosition, -1);
        UARTprintf(
            "\n             @ Single Bit(0)/Double Bit(1)/Parity(3) = %d",
            eccDspInfo.errL2Type, -1);
        UARTprintf("\n             @ L2 Cache error in Way %d",
            eccDspInfo.errL2way, -1);
        UARTprintf("\n             @ Correctable Parity Error Count = %d",
            eccDspInfo.errL2CorrectableCount, -1);
        UARTprintf("\n             @ Non-Correctable Parity Error count = %d",
            eccDspInfo.errL2NonCorrectableCount, -1);
    }
}

static int32_t dspEccL1PCacheTest(void)
{
    int32_t retVal = STW_SOK;
    volatile int32_t dummyTotal = 0U;
    eccDspErrStatus_t errStatus = {0U};
    eccDspErrInfo_t   eccDspInfo = {0U};

    UARTprintf("\nDSP ECC L1P Cache Access Error Test");

    /* Configure Cache size of L1P as 4K. */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1P,
                       DSPICFG_CACHE_SIZE_L1_4K);
    /* Enable ECC for L1P */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L1P,
                 ECC_ENABLE,
                 1000U);
    /* Initializing the cache line with the code. This function is placed
     * such that the corrupting function call falls exactly in the same
     * L1P cache line.
     */
    dummyTotal = dummyAdd(3, 4);
    /* Suspend the ECC operation to corrupt the cache line */
    ECCDspSuspend(ECC_DSP_MEM_TYPE_L1P, 1000U);
    /* Corrupting the Cache line */
    dummyTotal = dummySub(3, 4);
    /* Re-enable the ECC operation */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L1P,
                 ECC_ENABLE,
                 1000U);
    /* Access the same corrupted cache line to cause a ECC L1P error */
    dummyTotal = dummySub(3, 4);

    ECCDspIntrGetErrStatus(&errStatus);

    if (errStatus.l1PProgramFetchErr == 1U)
    {
        ECCDspGetErrInfo(ECC_DSP_MEM_TYPE_L1P, &eccDspInfo);
        if (eccDspInfo.errRamOrCache == 0U)
        {
            retVal = STW_SOK;
            UARTprintf("\nDSP L1P Cache Error @ address = 0x%x",
                     eccDspInfo.errAddress, -1);
            ECCDspIntrClrErrStatus(&errStatus);
            DSPICFGCacheInvalidateAll(SOC_DSP_ICFG_BASE, DSPICFG_MEM_L1P);
        }
        else
        {
            retVal = STW_EFAIL;
        }
    }
    else
    {
        retVal = STW_EFAIL;
    }

    /* Disable ECC */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L1P,
                 ECC_DISABLE,
                 1000U);
    /* Reconfigure L1P cache to the default value of 32K */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1P,
                       DSPICFG_CACHE_SIZE_L1_32K);
    ECCDspIntrClrErrStatus(&errStatus);
    return retVal;
}
static int32_t dspEccL1PDmaTest(void)
{
    int32_t retVal = STW_SOK;
    uint32_t i = 0U;
    gInterruptRecd = 0U;
    UARTprintf("\nDSP ECC L1P DMA Access Error Test");
    /* Initialize the interrupt control */
    Intc_Init();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /* Registering TimerIsr */
    Intc_IntRegister((uint16_t) DSP_IRQ_113,
                     (IntrFuncPtr) dspEccL1PDmaErrHandler, NULL);

    /* Set the priority */
    Intc_IntPrioritySet((uint16_t) DSP_IRQ_113, (uint16_t) 1, (uint8_t) 0);

    /* Enable the system interrupt */
    Intc_SystemEnable((uint16_t) DSP_IRQ_113);

    /* Configure Cache size of L1P as 4K. */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1P,
                       DSPICFG_CACHE_SIZE_L1_DISABLED);
    /* Fill the initialization pattern to some location in L1P. This will be
     * copied to the targetted location after first enabling ECC.
     */
    for ( i = 0U; i < (DSP_ECC_NUM_BYTES/4U); i++)
    {
        HW_WR_REG32(SOC_DSP_L2_BASE + 0x8000U + (4U*i), 0xA1A1A1A1U);
    }
    /* Fill the corruption pattern in some location in L1P. This will be used
     * to test the L1P EDC for DMA access.
     */
    for ( i = 0U ; i < (DSP_ECC_NUM_BYTES/4U); i++)
    {
        if (16U == i)
        {
            /* Corrupt One Bit of the 17th word */
            HW_WR_REG32(SOC_DSP_L2_BASE + 0x8100U + (4U*i), 0xA5A1A1A1U);
        }
        else
        {
            HW_WR_REG32(SOC_DSP_L2_BASE + 0x8100U + (4U*i), 0xA1A1A1A1U);
        }
    }

    /* Enable ECC for L1P */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L1P,
                 ECC_ENABLE,
                 1000U);
    /* Initialize memory using IDMA */
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_SOURCE,
                SOC_DSP_L2_BASE + 0x8000U);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_DEST, SOC_DSP_L1P_BASE);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_COUNT, DSP_ECC_NUM_BYTES);
    while (HW_RD_REG32 (SOC_DSP_ICFG_BASE + DSP_IDMA1_STAT) & 0x1U != 0U) {;}

    /* Suspend the ECC operation to corrupt L1P SRAM */
    ECCDspSuspend(ECC_DSP_MEM_TYPE_L1P, 1000U);

    /* Corrupt memory using IDMA */
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_SOURCE,
                SOC_DSP_L2_BASE + 0x8100U);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_DEST, SOC_DSP_L1P_BASE);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_COUNT, DSP_ECC_NUM_BYTES);
    while (HW_RD_REG32 (SOC_DSP_ICFG_BASE + DSP_IDMA1_STAT) & 0x1U != 0U) {;}

    /* Re-enable the ECC operation */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L1P,
                 ECC_ENABLE,
                 1000U);
    /* Read the corrupted data to cause a ECC error interrupt */
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_SOURCE,
                SOC_DSP_L1P_BASE);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_DEST, SOC_DSP_L2_BASE + 0x8200U);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_COUNT, DSP_ECC_NUM_BYTES);
    while (HW_RD_REG32 (SOC_DSP_ICFG_BASE + DSP_IDMA1_STAT) & 0x1U != 0U) {;}

    /* Wait for interrupt to be recieved */
    while(gInterruptRecd != 1U) {;}

    /* Disable ECC */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L1P,
                 ECC_DISABLE,
                 1000U);
    /* Reconfigure L1P cache to the default value of 32K */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1P,
                       DSPICFG_CACHE_SIZE_L1_32K);
    return retVal;
}
static void dspEccL2registerIntr(void)
{
    /* Initialize the interrupt control */
    Intc_Init();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /* Registering TimerIsr */
    Intc_IntRegister((uint16_t) DSP_IRQ_116,
                     (IntrFuncPtr) dspEccL2CorrErrHandler, NULL);

    /* Set the priority */
    Intc_IntPrioritySet((uint16_t) DSP_IRQ_116, (uint16_t) 1, (uint8_t) 0);

    /* Enable the system interrupt */
    Intc_SystemEnable((uint16_t) DSP_IRQ_116);

    /* Registering TimerIsr */
    Intc_IntRegister((uint16_t) DSP_IRQ_117,
                     (IntrFuncPtr) dspEccL2UnCorrErrHandler, NULL);

    /* Set the priority */
    Intc_IntPrioritySet((uint16_t) DSP_IRQ_117, (uint16_t) 1, (uint8_t) 0);

    /* Enable the system interrupt */
    Intc_SystemEnable((uint16_t) DSP_IRQ_117);
}

static int32_t dspEccL2L1DAccessErrTest(void)
{
    int32_t retVal = STW_SOK;
    uint32_t i = 0U;
    gInterruptRecd = 0U;
    UARTprintf("\nDSP ECC L2 L1D Cache Access Error Test");
    dspEccL2registerIntr();

    /* Configure Cache size of L1D as disabled. */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1D,
                       DSPICFG_CACHE_SIZE_L1_DISABLED);
    /* Fill the initialization pattern to some location in L2. This will be
     * copied to the targetted location after first enabling ECC.
     */
    for ( i = 0U; i < (DSP_ECC_NUM_BYTES/4U); i++)
    {
        HW_WR_REG32(SOC_DSP_L2_BASE + 0x8000U + (4U*i), 0xA1A1A1A1U);
    }
    /* Fill the corruption pattern in some location in L2. This will be used
     * to test the L2 EDC for L1D access.
     */
    for ( i = 0U ; i < (DSP_ECC_NUM_BYTES/4U); i++)
    {
        if (16U == i)
        {
            /* Corrupt One Bit of the 17th word */
            HW_WR_REG32(SOC_DSP_L2_BASE + 0x8100U + (4U*i), 0xA5A5A1A1U);
        }
        else
        {
            HW_WR_REG32(SOC_DSP_L2_BASE + 0x8100U + (4U*i), 0xA1A1A1A1U);
        }
    }
    /* Enable ECC for L2 */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                 ECC_ENABLE,
                 1000U);
    /* Initialize memory using IDMA */
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_SOURCE,
                SOC_DSP_L2_BASE + 0x8000U);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_DEST, SOC_DSP_L2_BASE + 0x8200);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_COUNT, DSP_ECC_NUM_BYTES);
    while (HW_RD_REG32 (SOC_DSP_ICFG_BASE + DSP_IDMA1_STAT) & 0x1U != 0U) {;}

    /* Suspend the ECC operation to corrupt L1P SRAM */
    ECCDspSuspend(ECC_DSP_MEM_TYPE_L2, 1000U);

    /* Corrupt memory using IDMA */
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_SOURCE,
                SOC_DSP_L2_BASE + 0x8100U);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_DEST, SOC_DSP_L2_BASE  + 0x8200);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_COUNT, DSP_ECC_NUM_BYTES);
    while (HW_RD_REG32 (SOC_DSP_ICFG_BASE + DSP_IDMA1_STAT) & 0x1U != 0U) {;}

    /* Re-enable the ECC operation */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                 ECC_ENABLE,
                 1000U);
    /* Configure Cache size of L1D as 4K. */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1D,
                       DSPICFG_CACHE_SIZE_L1_32K);

    /* This read will cause the L1D Access error to be set. This is always
     * uncorrectable.
     */
    HW_RD_REG32(SOC_DSP_L2_BASE  + 0x8200 + (4U*16U));

    /* Wait for interrupt to be recieved */
    while(gInterruptRecd != 1U) {;}

    /* Disable ECC for L2 */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                 ECC_DISABLE,
                 1000U);
    dspEccL2unregisterIntr();
    return retVal;
}

#ifdef __cplusplus
#pragma CODE_SECTION(".my_l2_code_sec1")
#else
#pragma CODE_SECTION(dummyCodeL2First, ".my_l2_code_sec1")
#endif
uint32_t dummyCodeL2First(int32_t a, int32_t b)
{
    uint32_t returnVal;
    if (a > b)
    {
        returnVal = 1U;
    }
    else
    {
        returnVal = 0U;
    }
    return returnVal;
}

#ifdef __cplusplus
#pragma CODE_SECTION(".my_l2_code_sec2")
#else
#pragma CODE_SECTION(dummyCodeL2Second, ".my_l2_code_sec2")
#endif
uint32_t dummyCodeL2Second(int32_t a, int32_t b)
{
    uint32_t returnVal;
    if (a > b)
    {
        returnVal = 5U;
    }
    else
    {
        returnVal = 0U;
    }
    return returnVal;
}

static int32_t dspEccL2L1PAccessErrTest(void)
{
    int32_t retVal = STW_SOK;
    eccDspErrStatus_t errStatus = {0U};
    volatile uint32_t dummyVal = 0U;
    gInterruptRecd = 0U;

    UARTprintf("\nDSP ECC L2 L1P Cache Access Error Test");

    /* Configure Cache size of L1P as disabled. */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1P,
                       DSPICFG_CACHE_SIZE_L1_DISABLED);
    dspEccL2unregisterIntr();
    /* Enable ECC for L2 */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                 ECC_ENABLE,
                 1000U);
    /* Memory Scubbing */
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_SOURCE,
                (uint32_t)&dummyCodeL2First);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_DEST,
                (uint32_t)&dummyCodeL2First);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_COUNT,
                DSPICFG_L2_CACHE_LINE_SIZE);
    while (HW_RD_REG32 (SOC_DSP_ICFG_BASE + DSP_IDMA1_STAT) & 0x1U != 0U) {;}

    /* Memory Scubbing */
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_SOURCE,
                (uint32_t)&dummyCodeL2Second);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_DEST,
                (uint32_t)&dummyCodeL2Second);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_COUNT,
                DSPICFG_L2_CACHE_LINE_SIZE);
    while (HW_RD_REG32 (SOC_DSP_ICFG_BASE + DSP_IDMA1_STAT) & 0x1U != 0U) {;}

    /* Suspend the ECC operation to corrupt L1P SRAM */
    ECCDspSuspend(ECC_DSP_MEM_TYPE_L2, 1000U);

    /* Memory Corruption */
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_SOURCE,
                (uint32_t)&dummyCodeL2Second);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_DEST,
                (uint32_t)&dummyCodeL2First);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_COUNT,
                DSPICFG_L2_CACHE_LINE_SIZE);
    while (HW_RD_REG32 (SOC_DSP_ICFG_BASE + DSP_IDMA1_STAT) & 0x1U != 0U) {;}

    /* Clear interrupts generated during scrubbing */
    retVal = ECCDspIntrGetErrStatus(&errStatus);
    ECCDspIntrClrErrStatus(&errStatus);

    /* Register interrupt handler */
    dspEccL2registerIntr();

    /* Re-enable the ECC operation */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                 ECC_ENABLE,
                 1000U);
    /* Configure Cache size of L1P as 32K. */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1P,
                       DSPICFG_CACHE_SIZE_L1_32K);
    dummyVal = dummyCodeL2First(3U, 5U);
    /* Wait for interrupt to be recieved */
    while(gInterruptRecd != 1U) {;}

    /* Since 3 < 5 the value is always 0 */
    retVal += dummyVal;

    /* Disable ECC for L2 */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                 ECC_DISABLE,
                 1000U);
    /* Clear interrupts generated during scrubbing */
    retVal = ECCDspIntrGetErrStatus(&errStatus);
    ECCDspIntrClrErrStatus(&errStatus);
    return retVal;
}
static int32_t dspEccL2DmaAccessErrTest(void)
{
    int32_t retVal = STW_SOK;
    uint32_t i = 0U;

    UARTprintf("\nDSP ECC L2 DMA Access Error Test");

    gInterruptRecd = 0U;

    dspEccL2registerIntr();
    /* Fill the initialization pattern to some location in L2. This will be
     * copied to the targetted location after first enabling ECC.
     */
    for ( i = 0U; i < (DSP_ECC_NUM_BYTES/4U); i++)
    {
        HW_WR_REG32(SOC_DSP_L2_BASE + 0x8000U + (4U*i), 0xA1A1A1A1U);
    }
    /* Fill the corruption pattern in some location in L2. This will be used
     * to test the L2 EDC for DMA access.
     */
    for ( i = 0U ; i < (DSP_ECC_NUM_BYTES/4U); i++)
    {
        if (16U == i)
        {
            /* Corrupt One Bit of the 17th word */
            HW_WR_REG32(SOC_DSP_L2_BASE + 0x8100U + (4U*i), 0xA5A1A1A1U);
        }
        else
        {
            HW_WR_REG32(SOC_DSP_L2_BASE + 0x8100U + (4U*i), 0xA1A1A1A1U);
        }
    }
    /* Enable ECC for L2 */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                 ECC_ENABLE,
                 1000U);
    /* Initialize memory using IDMA */
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_SOURCE,
                SOC_DSP_L2_BASE + 0x8000U);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_DEST, SOC_DSP_L2_BASE + 0x8200);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_COUNT, DSP_ECC_NUM_BYTES);
    while (HW_RD_REG32 (SOC_DSP_ICFG_BASE + DSP_IDMA1_STAT) & 0x1U != 0U) {;}

    /* Suspend the ECC operation to corrupt L1P SRAM */
    ECCDspSuspend(ECC_DSP_MEM_TYPE_L2, 1000U);

    /* Corrupt memory using IDMA */
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_SOURCE,
                SOC_DSP_L2_BASE + 0x8100U);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_DEST, SOC_DSP_L2_BASE  + 0x8200);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_COUNT, DSP_ECC_NUM_BYTES);
    while (HW_RD_REG32 (SOC_DSP_ICFG_BASE + DSP_IDMA1_STAT) & 0x1U != 0U) {;}

    /* Re-enable the ECC operation */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                 ECC_ENABLE,
                 1000U);
    /*
     * This read will cause an error in the L2 DMA read error field. The error
     * should be a single bit error at the 26th bit and it correctable.
     */
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_SOURCE,
                SOC_DSP_L2_BASE  + 0x8200);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_DEST, SOC_DSP_L2_BASE  + 0x8300);
    HW_WR_REG32(SOC_DSP_ICFG_BASE + DSP_IDMA1_COUNT, DSP_ECC_NUM_BYTES);
    while (HW_RD_REG32 (SOC_DSP_ICFG_BASE + DSP_IDMA1_STAT) & 0x1U != 0U) {;}

    /* Wait for interrupt to be recieved */
    while(gInterruptRecd != 1U) {;}

    /* Disable ECC for L2 */
    ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                 ECC_DISABLE,
                 1000U);
    dspEccL2unregisterIntr();
    return retVal;
}

static int32_t dspEccL2VictimAccessErrTest(void)
{
    int32_t retVal = STW_SOK;
    uint32_t i = 0U, address = 0U;
    eccDspErrStatus_t errStatus = {0U};
    gInterruptRecd = 0U;

    /* Configure Cache size of L1P as 32K. */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1P,
                       DSPICFG_CACHE_SIZE_L1_DISABLED);

    /* Clear interrupts generated during scrubbing */
    retVal = ECCDspIntrGetErrStatus(&errStatus);
    ECCDspIntrClrErrStatus(&errStatus);

    UARTprintf("\nDSP ECC L2 Victim Access Error Test");

    dspEccL2registerIntr();
    /* Initialize memory worth the cache line size */
    address = (uint32_t)&dummyVar1;
    for (i = address;
         i < (address + DSPICFG_L2_CACHE_LINE_SIZE); i = i + 4U)
    {
        HW_WR_REG32(i , 0x0U);
    }
    address = (uint32_t)&dummyVar2;
    for (i = address;
         i < (address + DSPICFG_L2_CACHE_LINE_SIZE); i = i + 4U)
    {
        HW_WR_REG32(i , 0x0U);
    }
    address = (uint32_t)&dummyVar3;
    for (i = address;
         i < (address + DSPICFG_L2_CACHE_LINE_SIZE); i = i + 4U)
    {
        HW_WR_REG32(i , 0x0U);
    }
    address = (uint32_t)&dummyVar4;
    for (i = address;
         i < (address + DSPICFG_L2_CACHE_LINE_SIZE); i = i + 4U)
    {
        HW_WR_REG32(i , 0x0U);
    }
    address = (uint32_t)&dummyVar5;
    for (i = address;
         i < (address + DSPICFG_L2_CACHE_LINE_SIZE); i = i + 4U)
    {
        HW_WR_REG32(i , 0x0U);
    }
    HW_WR_REG32((uint32_t)&dummyVar1, 0x11111111);
    HW_WR_REG32((uint32_t)&dummyVar2, 0x11111111);
    HW_WR_REG32((uint32_t)&dummyVar3, 0x11111111);
    HW_WR_REG32((uint32_t)&dummyVar4, 0x11111111);
    HW_WR_REG32((uint32_t)&dummyVar5, 0x11011111);

    /* Configure Cache size of L1D as disabled. */
    retVal = DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1D,
                       DSPICFG_CACHE_SIZE_L1_DISABLED);
    /* Configure Cache size of L2 as 32K Cache. */
    retVal = DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L2,
                       DSPICFG_CACHE_SIZE_L2_32K);
    retVal = DSPICFGSetMAR(SOC_DSP_ICFG_BASE, (uint32_t)&dummyVar1,
                  DSPICFG_MAR_PC);
    retVal = DSPICFGSetMAR(SOC_DSP_ICFG_BASE, (uint32_t)&dummyVar2,
                  DSPICFG_MAR_PC);
    retVal = DSPICFGSetMAR(SOC_DSP_ICFG_BASE, (uint32_t)&dummyVar3,
                  DSPICFG_MAR_PC);
    retVal = DSPICFGSetMAR(SOC_DSP_ICFG_BASE, (uint32_t)&dummyVar4,
                  DSPICFG_MAR_PC);
    retVal = DSPICFGSetMAR(SOC_DSP_ICFG_BASE, (uint32_t)&dummyVar5,
                  DSPICFG_MAR_PC);
    /* Enable ECC for L2 */
    retVal = ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                 ECC_ENABLE,
                 1000U);

    HW_RD_REG32((uint32_t)&dummyVar1);
    HW_RD_REG32((uint32_t)&dummyVar2);
    HW_RD_REG32((uint32_t)&dummyVar3);
    HW_RD_REG32((uint32_t)&dummyVar4);

    /* Suspend the ECC operation to corrupt L1P SRAM */
    retVal = ECCDspSuspend(ECC_DSP_MEM_TYPE_L2, 1000U);

    HW_WR_REG32((uint32_t)&dummyVar5, 0x11011111);

    /* Re-enable the ECC operation */
    retVal = ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                 ECC_ENABLE,
                 1000U);
    /* This will generate an L2 Victim error at the 20th bit which is
     * correctable.
     */
    retVal = DSPICFGCacheWriteBackInvalidateAll(SOC_DSP_ICFG_BASE,
                                                DSPICFG_MEM_L2);

     /* Wait for interrupt to be recieved */
    while(gInterruptRecd != 1U) {;}

    /* Disable ECC for L2 */
    retVal = ECCDspEnable(ECC_DSP_MEM_TYPE_L2,
                 ECC_DISABLE,
                 1000U);
    retVal = DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1D,
                       DSPICFG_CACHE_SIZE_L1_32K);
    /* Configure Cache size of L2 as 32K Cache. */
    retVal = DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L2,
                       DSPICFG_CACHE_SIZE_L2_DISABLED);
    /* Configure Cache size of L1P as 32K. */
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1P,
                       DSPICFG_CACHE_SIZE_L1_32K);
    dspEccL2unregisterIntr();
    return retVal;
}
