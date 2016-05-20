/**
 *  \file     sbl_tda3xx_main.c
 *
 *  \brief    This file contains the SBL main function which calls the SOC Init
 *            and slave core boot up functions in sequence.
 *
 *  \copyright Copyright (C) 2015 Texas Instruments Incorporated -
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
#include "hw_types.h"
#include "hw_ctrl_core_sec.h"
#include "hw_emif.h"
#include "interrupt.h"
#include "ipu_wugen.h"
#include "soc.h"
#include "soc_defines.h"
#include "edma.h"
#include "emif.h"
#include "rti.h"
#include "irq_xbar.h"
#include "sbl_lib/sbl_lib.h"
#include "sbl_lib/sbl_lib_tda3xx.h"
#include "sbl_utils/sbl_utils_common.h"
#include "sbl_utils/sbl_utils_tda3xx.h"
#include "sbl_utils/sbl_utils_tda3xx_ddr_config.h"
#include "sbl_lib_config.h"
#include "sbl_tda3xx_priv.h"
#include "platform.h"
#include "uartStdio.h"
#include "pmhal_prcm.h"
#include "pm/pmhal/pmhal_cm.h"
#include "pm/pmhal/pmhal_mm.h"
#include "pm/pmhal/pmhal_rm.h"
#include "pm/pmhal/pmhal_pdm.h"
#include "stw_platformEcc.h"

#if defined (BOOTMODE_QSPI_SD)
#include <common/stw_config.h>
#include <common/stw_utils.h>
#include "i2clib/lld_hsi2c.h"
#include "boards/stw_board.h"
#include "devices/stw_device.h"
#include "stwutils_app.h"
#endif

#if !defined (BOOTMODE_NOR)
#include "qspi_flash.h"
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Define Address for SBL start time variable in NOR boot mode.
 * Should be in sync with sbl_m4_init_nor.asm
 */
#define  SBL_NOR_START_TIME_ADDRESS                    ((uint32_t) 0x003001C0U)

/* Macro to disable/enable RTI */
#define SBL_DISABLE_RTI                                ((uint32_t) TRUE)

/* Macro to lock/unlock Control Module MMR */
#define SBL_LOCK_MMR                                   ((uint32_t) FALSE)

/* Macro containing 32K Timer frequency */
#define SBL_32KTIMER_REFERENCE_VAL                     (32U * 1024U)

/* Macro containing Interrupt line Number to be used for TESOC */
#define SBL_IPU_TESOC_TEST_INTR_LINE_NUMBER            ((uint16_t) 67U)

/* Macro containing IPU1 Core1 start address in QSPI and QSPI_SD boot mode */
#define SBL_RBL_SLAVE_CORE_START_ADDRESS_QSPI      ((uint32_t) 0x00300101U)

/* Macro containing IPU1 Core1 start address in NOR boot mode */
#define SBL_RBL_SLAVE_CORE_START_ADDRESS_NOR       ((uint32_t) 0x08000201U)

/* Typedef for entry point function */
typedef void (*EntryFuncPtr_t)(void);

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This function contains the code for jumping to IPU1 Core1's entry
 *          point.
 *
 * \param   None.
 *
 * \retval  None.
 */
#ifdef __cplusplus
#pragma CODE_SECTION(".ipu1_1_init");
#else
#pragma CODE_SECTION(SblIPU1Core1Init, ".ipu1_1_init");
#endif
void SblIPU1Core1Init(void);

/**
 * \brief   This function copies the vector table to IPU RAM.
 *
 * \param   None.
 *
 * \retval  None.
 */
static void SblCopyVectorTable(void);

/**
 * \brief   This function configures the RGMII PADs in QSPI_SD boot mode.
 *
 * \param   None.
 *
 * \retval  None.
 *
 * \note    In order to use RGMII and MMC same PADs need to be configured. Thus
 *          RGMII is not configured while doing TI EVM PAD Configuration.
 */
static void SblConfigRGMIIPad(void);

/**
 * \brief   This function does the SBL configuration needed before running
 *          IPU TESOC Tests.
 *
 * \param   None.
 *
 * \retval  None.
 */
static void SblConfigPreIPUTESOC(void);

#if (SBL_LIB_CONFIG_ENABLE_IPU_TESOC_TESTS == 1)
/**
 * \brief   This function configures and initiates the IPU LBIST.
 *
 * \param   None.
 *
 * \retval  None.
 *
 * \note    IPU resets after LBIST and the control jumps to API
 *          SblCheckIPULBISTResult after wake-up.
 */
static void SblConfigAndInitiateIPULBIST(void);

/**
 * \brief   This function checks the IPU LBIST result. The boot is aborted in
 *          case of failure.
 *
 * \param   None.
 *
 * \retval  None.
 *
 * \note    This API also triggers IPU MBIST by calling API
 *          SblConfigAndInitiateIPUMBIST.
 */
static void SblCheckIPULBISTResult(void);

/**
 * \brief   This function configures and initiates the IPU MBIST.
 *
 * \param   None.
 *
 * \retval  None.
 *
 * \note    IPU resets after MBIST and the control jumps to API
 *          SblCheckIPUMBISTResult after wake-up.
 */
static void SblConfigAndInitiateIPUMBIST(void);

/**
 * \brief   This function checks the IPU MBIST result. The boot is aborted in
 *          case of failure.
 *
 * \param   None.
 *
 * \retval  None.
 *
 * \note    This API calls SblConfigPostIPUTESOC after checking MBIST result.
 */
static void SblCheckIPUMBISTResult(void);
#endif

/**
 * \brief   This function does the normal SBL configuration after running IPU
 *          TESOC Tests.
 *
 * \param   None.
 *
 * \retval  None.
 */
static void SblConfigPostIPUTESOC(void);

#if (SBL_LIB_CONFIG_ENABLE_OTHER_TESOC_TESTS == 1)
/**
 * \brief   This function configures and initiates the TESOC tests on other
 *          domains except IPU i.e. DSP1, DSP2, EVE and ISSDSSVIP.
 *
 * \param   None.
 *
 * \retval  None.
 *
 * \note    Reset is not generated on SOC master IPU after running TESOC on
 *          these domains.
 */
static void SblConfigAndInitiateOtherTesocTests(void);
#endif

/**
 * \brief   This function acts as a wrapper for SBL print function.
 *
 * \param   message       Message to be printed.
 *
 * \retval  None.
 *
 * \note    Below ifdef __cplusplus is added so that C++ build passes without
 *          typecasting. This is because the prototype is build as C type
 *          whereas this file is build as CPP file. Hence we get C++ build
 *          error. Also if typecasting is used, then we get MisraC error
 *          Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif
static void SBLPrintFunction(const char *message);
#ifdef __cplusplus
}
#endif

/**
 * \brief   This function prints the boot-cycles in ms.
 *
 * \param   cyclesString     Description of boot cycles.
 * \param   bootCycles       Boot time in Cycles.
 *
 * \retval  None.
 */
static void SblPrintBootCycles(const char *cyclesString, uint32_t bootCycles);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern const volatile uint32_t vector_table[NUM_ELEMENTS_VECTOR_TABLE];

/**
 *  \brief Global time stamp variables. These variable can't be put in stack as
 *         reset due to TESOC test will re-initialize them.
 */
static volatile uint32_t       timeValSblStart;
static volatile uint32_t       timeValSblInitStart;
#if (SBL_LIB_CONFIG_ENABLE_IPU_TESOC_TESTS == 1)
static volatile uint32_t       timeValIPULbistStart;
static volatile uint32_t       timeValIPULbistEnd;
static volatile uint32_t       timeValIPUMbistStart;
static volatile uint32_t       timeValIPUMbistEnd;
#endif
#if (SBL_LIB_CONFIG_ENABLE_OTHER_TESOC_TESTS == 1)
static volatile uint32_t       timeValOtherTesocTestStart;
static volatile uint32_t       timeValOtherTesocTestEnd;
#endif

/*
 * Variable for Meta Header structure
 */
#ifdef __cplusplus
#pragma DATA_SECTION(".img_hdr");
#else
#pragma DATA_SECTION(sblAppMetaHeader, ".img_hdr");
#endif
sbllibMetaHeader_t sblAppMetaHeader;

/*
 * Variable for RPRC Header structure
 */
#ifdef __cplusplus
#pragma DATA_SECTION(".img_hdr");
#else
#pragma DATA_SECTION(sblAppRPRCHeader, ".img_hdr");
#endif
sbllibRPRCImageHeader_t        sblAppRPRCHeader;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    sbllibInitParams_t sblInitPrms;

    /* Default initialization of SBL Lib Params */
    SBLLibInitParamsInit(&sblInitPrms);

    /* Assign SBL Params */
    sblInitPrms.printFxn = &SBLPrintFunction;
    SBLLibInit(&sblInitPrms);

    /* Do initial configuration needed before IPU TESOC tests */
    SblConfigPreIPUTESOC();

#if (SBL_LIB_CONFIG_ENABLE_IPU_TESOC_TESTS == 1)
    /*
     * Initiate IPU LBIST. MBIST will be initiated by APIs further called by
     * this API.
     */
    SblConfigAndInitiateIPULBIST();
#else
    /* Do SBL configuration that should be done post TESOC tests */
    SblConfigPostIPUTESOC();
#endif

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static void SBLPrintFunction(const char *message)
{
    UARTPuts(message, -1);
}

void SblIPU1Core1Init(void)
{
    /* Warm reset does not clear AUXBOOT registers. Hence they should be cleared
     * explicitly after Core1 boot-up
     */
    /* Unlock Control Module */
    asm (" MOV R0, #0x2540");
    asm (" MOVT R0, #0x4A00");
    asm (" MOV R1, #0xAC2B");
    asm (" MOVT R1, #0x2FF1");
    asm (" STR R1, [R0]");

    /* Set AUXBOOT0 to Zero */
    asm (" MOV R0, #0x3CA8");
    asm (" MOVT R0, #0x4A00");
    asm (" MOV R1, #0x0");
    asm (" STR R1, [R0]");

    /* Set AUXBOOT1 to Zero */
    asm (" MOV R0, #0x3CAC");
    asm (" MOVT R0, #0x4A00");
    asm (" MOV R1, #0x0");
    asm (" STR R1, [R0]");

    while (0U == HW_RD_REG32(SBLLIB_IPU1_CORE_1_ENTRY_POINT_ADDRESS))
    {
        /* To remove MISRA C error */
    }

    /* IPU1 Core1 is held in WFE status by RBL. Core 0 wakes up core 1 by
     * sending event. Core 1 jumps to address specified by register
     * CTRL_CORE_SEC_ROM_AUXBOOT1 i.e. 0x00300100. Core 1 stays in while loop
     * till the time Core 0 parses the image and sets the entry point address
     * at location 0x00300180. Core 1 then branches to entry point.
     */
    asm (" MOV R0, #0x0180");
    asm (" MOVT R0, #0x0030");
    asm (" LDR R0, [R0]");
    asm (" BX R0");
}

static void SblCopyVectorTable(void)
{
    uint32_t addr   = 0x8U, index = 0U;
    uint32_t length = NUM_ELEMENTS_VECTOR_TABLE;

    for (index = 2U; index < length; index++)
    {
        HW_WR_REG32(addr, vector_table[index]);
        addr = addr + 4U;
    }
}

static void SblConfigRGMIIPad(void)
{
#if defined (BOOTMODE_QSPI_SD)
    stwAppInitParams_t stwAppInitParamsVal;
    int32_t retVal = STW_SOK;

    stwAppInitParamsVal.isI2cInitReq  = (uint32_t) TRUE;
    stwAppInitParamsVal.isUartInitReq = (uint32_t) FALSE;
    retVal = StwUtils_appDefaultInit(stwAppInitParamsVal);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\nSystem Init Failed while configuring RGMII PAD \n");
    }

    /*IOExpander mux config : Mux F : EMAC0PHY */
    BOARDSelectDevice(DEVICE_ID_EMAC0PHY, DEVICE_EMAC0PHY_INST_ID_0);

    /* Set RGMII PAD configuration */
    PlatformRGMIISetPinMux();
#endif
}

static void SblConfigPreIPUTESOC(void)
{
    uint32_t siliconPackageType;
    int32_t  retVal = STW_SOK;
    pmhalPrcmDpllConfig_t *dpllParams;
    pmhalPrcmSysClkVal_t sysClkFreq = PMHAL_PRCM_SYSCLK_20_MHZ;
    uint32_t oppId;
#if (SBL_LIB_CONFIG_ENABLE_IPU_TESOC_TESTS == 0)
    uint32_t ipuCore1StartAddr;
#endif

    /* Take start time-stamp and change RTI reaction */
#if defined (BOOTMODE_NOR)
    timeValSblStart = HW_RD_REG32(SBL_NOR_START_TIME_ADDRESS);
#else
    timeValSblStart = SBLUtilsRead32KTimer();
#endif

    timeValSblInitStart = SBLUtilsRead32KTimer();

    if (TRUE == SBL_DISABLE_RTI)
    {
        /* Configure DWWD Window size */
        RTIDwwdSetWindowSize(SOC_RTI1_BASE, RTI_DWWD_WINDOWSIZE_50_PERCENT);

        /* Service DWWD */
        RTIDwwdService(SOC_RTI1_BASE);

        /* Change RTI's action to interrupt */
        RTIDwwdSetReaction(SOC_RTI1_BASE, RTI_DWWD_REACTION_GENERATE_NMI);
    }

    /*
     * Wakeup IPU1-Core 1 before re-configuring AMMU if TESOC tests are
     * disabled
     */
#if (SBL_LIB_CONFIG_ENABLE_IPU_TESOC_TESTS == 0)
    /* Set IPU1 entry point to zero */
    HW_WR_REG32(SBLLIB_IPU1_CORE_1_ENTRY_POINT_ADDRESS, 0x0U);
    #if defined (BOOTMODE_NOR)
    ipuCore1StartAddr = SBL_RBL_SLAVE_CORE_START_ADDRESS_NOR;
    #else
    ipuCore1StartAddr = SBL_RBL_SLAVE_CORE_START_ADDRESS_QSPI;
    #endif
    SBLUtilsWakeUpIPU1Core1(ipuCore1StartAddr);
#endif

    /* Configure the IPU1 AMMU */
    SBLUtilsConfigIPU1DefaultAMMU();

#if !defined (BOOTMODE_QSPI_SD)
    /* Enable the IPU1's Uni-cache */
    SBLUtilsEnableIPU1Unicache();
#endif

    siliconPackageType = PlatformGetSiliconPackageType();

    /* Copy the vector table */
    SblCopyVectorTable();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /* Unlock the MMR registers */
    PlatformUnlockMMR();

    /* Get the Sys clock1 Frequency */
    sysClkFreq = PMHALCMGetSysClockFreqEnum();

    /* Read the opp for which the SBL has been compiled */
    oppId = SBLGetOppId(siliconPackageType);

    /* Configure PRCM and Control Module registers before configuring DPLL. */
    retVal = SBLUtilsConfigureDspEveMux(oppId, siliconPackageType);

    /* Configure DPLL CORE */
    retVal += SBLLibGetDpllStructure(PMHAL_PRCM_DPLL_CORE,
                                     sysClkFreq,
                                     oppId,
                                     &dpllParams);

    /* L3 clock = CORE CLK /2, L4 clock = L3 clock /2 */
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_L3_ICLK, (uint32_t) 2U);
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_L4_ROOT_CLK, (uint32_t) 2U);

    retVal += PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_CORE,
                                   dpllParams,
                                   PM_TIMEOUT_INFINITE);

    /* Configure DPLL PER */
    retVal += SBLLibGetDpllStructure(PMHAL_PRCM_DPLL_PER,
                                     sysClkFreq,
                                     oppId,
                                     &dpllParams);

    retVal += PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_PER,
                                   dpllParams,
                                   PM_TIMEOUT_INFINITE);

    /* UART Initialization */
    SBLUtilsPrintfInit(SBL_LIB_CONFIG_UART_INST);

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1, "\n TDA3xx SBL Boot \n");

    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n SBL Config Before IPU LBIST and MBIST Failed \n");
        SBLLibAbortBoot();
    }

    /*
     * DSPs cause random issues as they are uninitialized,
     * power down DSPs
     */
    retVal = PMHALCMSetCdClockMode(
        (pmhalPrcmCdId_t) PMHAL_PRCM_CD_DSP1,
        PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
        PM_TIMEOUT_NOWAIT);
    retVal += PMHALPdmSetPDState(
        PMHAL_PRCM_PD_DSP1,
        PMHAL_PRCM_PD_STATE_OFF,
        PM_TIMEOUT_NOWAIT);

    retVal += PMHALCMSetCdClockMode(
        (pmhalPrcmCdId_t) PMHAL_PRCM_CD_DSP2,
        PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
        PM_TIMEOUT_NOWAIT);
    retVal += PMHALPdmSetPDState(
        PMHAL_PRCM_PD_DSP2,
        PMHAL_PRCM_PD_STATE_OFF,
        PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != retVal)
    {
        SBLLibPrintf(
            SBLLIB_TRACE_LEVEL_ERROR,
            "\n PRCM Failed to Power Down DSPs, Aborting Boot\n");
        SBLLibAbortBoot();
    }
}

#if (SBL_LIB_CONFIG_ENABLE_IPU_TESOC_TESTS == 1)
static void SblConfigAndInitiateIPULBIST(void)
{
    int32_t        retVal = STW_SOK;
    tesocTestCfg_t tesocTestConfig;
#if (SBL_LIB_CONFIG_ENABLE_IPU_TESOC_ROM_CRC == 1)
    crcSignature_t crcSigVal;
#endif

    /* Take IPU LBIST start time-stamp */
    timeValIPULbistStart = SBLUtilsRead32KTimer();

#if (SBL_LIB_CONFIG_ENABLE_IPU_TESOC_ROM_CRC == 1)
    /* Compute CRC for IPU TESOC ROM */
    retVal = SBLUtilsComputeIPUTesocROMCRC(&crcSigVal);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(
            SBLLIB_TRACE_LEVEL_ERROR,
            "\n TESOC ROM CRC Computation Failed, Aborting Boot\n");
        SBLLibAbortBoot();
    }
    else
    {
        if ((TESOC_ROM_IPU_CRC_SIGNATURE_REGL != crcSigVal.regL) ||
            (TESOC_ROM_IPU_CRC_SIGNATURE_REGH != crcSigVal.regH))
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_ERROR,
                "\n TESOC ROM CRC Match Failed, Aborting Boot\n");
            SBLLibAbortBoot();
        }
        else
        {
            /* CRC Computed is correct, do nothing */
        }
    }
#endif

    /* Configure and enable TESOC HS divider */
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_TESOC_EXT_CLK, (uint32_t) 1U);

    tesocTestConfig.testId = TESOC_TEST_ID_IPU_LBIST;
    retVal = TESOCGetDefaultSliceInfo(SOC_TESOC_BASE, &tesocTestConfig);
    if (PM_SUCCESS != retVal)
    {
        SBLLibPrintf(
            SBLLIB_TRACE_LEVEL_ERROR,
            "\n Failed to Get IPU LBIST Slice Info, Aborting Boot\n");
        SBLLibAbortBoot();
    }

    /*
     * Configure TESOC interrupt for IPU. TESOC interrupt acts as wake up
     * event for IPU to reboot.
     */
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                   CPU_IPU1,
                   (SBL_IPU_TESOC_TEST_INTR_LINE_NUMBER - 22U),
                   TESOC_IRQ_DONE);
    Intc_IntPrioritySet(SBL_IPU_TESOC_TEST_INTR_LINE_NUMBER,
                        (uint16_t) 1U,
                        (uint8_t) 0U);
    Intc_SystemEnable(SBL_IPU_TESOC_TEST_INTR_LINE_NUMBER);

    /* Register IPU Wake-up event instead of ISR */
    IPU_WUGEN_Enable(SBL_IPU_TESOC_TEST_INTR_LINE_NUMBER);

    /* Set entry point after reboot due to TESOC */
    HW_WR_REG32(SOC_SEC_EFUSE_REGISTERS_BASE +
                CTRL_CORE_SEC_ROM_CPU0_BRANCH,
                (uint32_t) &SblCheckIPULBISTResult);

    SBLLibRunTesocTest(TESOC_TEST_ID_IPU_LBIST, &tesocTestConfig);
    /*
     * IPU resets after IPU LBIST and hence no more execution happens after
     * this statement. After wakeup execution begins from API
     * SblCheckIPULBISTResult.
     */
}

static void SblCheckIPULBISTResult(void)
{
    int32_t        retVal = STW_SOK;
    tesocTestCfg_t tesocTestConfig;

    /* Configure the IPU1 AMMU */
    SBLUtilsConfigIPU1DefaultAMMU();

#if !defined (BOOTMODE_QSPI_SD)
    /* Enable the IPU1's Uni-cache */
    SBLUtilsEnableIPU1Unicache();
#endif

    /* Copy the vector table */
    SblCopyVectorTable();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /* Clear TESOC interrupt and check IPU LBIST Result */
    tesocTestConfig.testId = TESOC_TEST_ID_IPU_LBIST;
    TESOCGetDefaultSliceInfo(SOC_TESOC_BASE, &tesocTestConfig);
    TESOCIntrClear(SOC_TESOC_BASE, TESOC_INTR_FLAG_TEST_COMPLETION);
    retVal = SBLLibCheckTesocTestResult(&tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n IPU LBIST Failed, Aborting Boot\n");
        SBLLibAbortBoot();
    }
    timeValIPULbistEnd = SBLUtilsRead32KTimer();

    /* Run IPU MBIST */
    SblConfigAndInitiateIPUMBIST();
}

static void SblConfigAndInitiateIPUMBIST(void)
{
    int32_t        retVal = STW_SOK;
    tesocTestCfg_t tesocTestConfig;

    /* Take IPU MBIST start time-stamp */
    timeValIPUMbistStart = SBLUtilsRead32KTimer();

    /* Configure and enable TESOC HS divider */
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_TESOC_EXT_CLK, (uint32_t) 1U);

    /* Assign test configuration for IPU MBIST */
    tesocTestConfig.testId = TESOC_TEST_ID_IPU_MBIST;
    TESOCGetDefaultSliceInfo(SOC_TESOC_BASE, &tesocTestConfig);

    /*
     * Configure TESOC interrupt for IPU. TESOC interrupt acts as wake up
     * event for IPU to reboot.
     */
    Intc_IntPrioritySet(SBL_IPU_TESOC_TEST_INTR_LINE_NUMBER,
                        (uint16_t) 1U,
                        (uint8_t) 0U);
    Intc_SystemEnable(SBL_IPU_TESOC_TEST_INTR_LINE_NUMBER);

    /* Register IPU Wake-up event instead of ISR */
    IPU_WUGEN_Enable(SBL_IPU_TESOC_TEST_INTR_LINE_NUMBER);

    /* Set entry point after reboot due to TESOC */
    HW_WR_REG32(SOC_SEC_EFUSE_REGISTERS_BASE +
                CTRL_CORE_SEC_ROM_CPU0_BRANCH,
                (uint32_t) &SblCheckIPUMBISTResult);

    /*
     * IPU MBIST data needs to be copied to TESOC RAM.
     * Set QSPI in Memory Mapped Mode before triggering EDMA.
     */
#if !defined (BOOTMODE_NOR)
    QSPI_Initialize(DEVICE_TYPE_QSPI4);
    QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      (uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);

    QSPI_ConfMAddrSpace((uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,
                        QSPI_CS0);
#endif

    /* Enable EDMA module */
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_TPCC,
                                PMHAL_PRCM_MODULE_MODE_AUTO,
                                PM_TIMEOUT_INFINITE);
    retVal += PMHALModuleModeSet(PMHAL_PRCM_MOD_TPTC1,
                                 PMHAL_PRCM_MODULE_MODE_AUTO,
                                 PM_TIMEOUT_INFINITE);
    retVal += PMHALModuleModeSet(PMHAL_PRCM_MOD_TPTC2,
                                 PMHAL_PRCM_MODULE_MODE_AUTO,
                                 PM_TIMEOUT_INFINITE);

    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n EDMA PRCM Failed, Aborting Boot\n");
        SBLLibAbortBoot();
    }

    /* Initialize the EDMA */
    EDMAsetRegion(0U);
    EDMA3Init(SOC_EDMA_TPCC_BASE, 0U);

    SBLUtilsTriggerEDMAPolledMode(SBL_IPU_MBIST_DATA_ADDRESS,
                                  SOC_TESOC_BASE + TESOC_RAM(0),
                                  TESOC_RAM_SIZE,
                                  (uint32_t) 1U,
                                  (uint32_t) 1U,
                                  (uint32_t) 0U,
                                  (uint32_t) 1U);

    /* De-initialize EDMA */
    EDMA3Deinit(SOC_EDMA_TPCC_BASE, 0);

    SBLLibRunTesocTest(TESOC_TEST_ID_IPU_MBIST, &tesocTestConfig);
    /*
     * IPU resets after IPU MBIST and hence no more execution happens after
     * this statement. After wakeup execution begins from API
     * SblConfigPostIPUTESOC.
     */
}

static void SblCheckIPUMBISTResult(void)
{
    int32_t        retVal = STW_SOK;
    tesocTestCfg_t tesocTestConfig;
    uint32_t       ipuCore1StartAddr;

    /* Enable IPU Core 1 After Completing IPU LBIST and MBIST */
    /*
     * Wakeup event has woken up only Core 0. Core 1 is still held in reset.
     */
    PMHALResetRelease(PMHAL_PRCM_RG_IPU1_CPU1_RST, PM_TIMEOUT_NOWAIT);

    /* Set IPU1 entry point to zero */
    HW_WR_REG32(SBLLIB_IPU1_CORE_1_ENTRY_POINT_ADDRESS, 0x0U);

    /* Wakeup IPU1-Core 1 before re-configuring AMMU */
    #if defined (BOOTMODE_NOR)
    ipuCore1StartAddr = SBL_RBL_SLAVE_CORE_START_ADDRESS_NOR;
    #else
    ipuCore1StartAddr = SBL_RBL_SLAVE_CORE_START_ADDRESS_QSPI;
    #endif
    SBLUtilsWakeUpIPU1Core1(ipuCore1StartAddr);

    /* Configure the IPU1 AMMU */
    SBLUtilsConfigIPU1DefaultAMMU();

#if !defined (BOOTMODE_QSPI_SD)
    /* Enable the IPU1's Uni-cache */
    SBLUtilsEnableIPU1Unicache();
#endif

    /* Copy the vector table */
    SblCopyVectorTable();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /* Assign test configuration for IPU MBIST */
    tesocTestConfig.testId = TESOC_TEST_ID_IPU_MBIST;
    TESOCGetDefaultSliceInfo(SOC_TESOC_BASE, &tesocTestConfig);
    /* Clear TESOC interrupt and check IPU MBIST Result */
    TESOCIntrClear(SOC_TESOC_BASE, TESOC_INTR_FLAG_TEST_COMPLETION);
    retVal = SBLLibCheckTesocTestResult(&tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n IPU MBIST Failed, Aborting Boot\n");
        SBLLibAbortBoot();
    }
    timeValIPUMbistEnd = SBLUtilsRead32KTimer();

    /* Do post IPU TESOC SBL configuration */
    SblConfigPostIPUTESOC();
}

#endif

static void SblConfigPostIPUTESOC(void)
{
    int32_t                     retVal = STW_SOK;
    uint32_t                    siliconPackageType;
    uint32_t                    sblBuildMode;
    uint32_t                    oppId;
    uint32_t                    edmaChNum   = 1U;
    uint32_t                    edmaTccNum  = 1U;
    uint32_t                    edmaEvtqNum = 0U;
    uint32_t                    timeValSblEnd;
    uint32_t                    timeValAppImgLoadStart, timeValAppImgLoadEnd;
    uint32_t                    timeValSblInitEnd;
    uint32_t                    timeValSocInitStart, timeValSocInitEnd;
    uint32_t                    timeValDdrConfigStart, timeValDdrConfigEnd;
    uint32_t                    timeValSlaveCoreBootupStart,
                                timeValSlaveCoreBootupEnd;
    volatile uint32_t           spin           = 1U;
    sbllibEntryPoints_t         sblEntryPoints = {0U};
    sbllibAppImageParseParams_t appImgParams;
    EntryFuncPtr_t              ipu1Core0EntryFuncPtr;
    pmhalPrcmSysClkVal_t        sysClkFreq = PMHALCMGetSysClockFreqEnum();
#if (SBL_LIB_CONFIG_ENABLE_EMIF_ECC == 1)
    uint32_t                    timeValEccInitStart, timeValEccInitEnd;
#endif

#ifdef SBL_DEV_BUILD
    sblBuildMode = SBLLIB_SBL_BUILD_MODE_DEV;
#else
    sblBuildMode = SBLLIB_SBL_BUILD_MODE_PROD;
#endif

    siliconPackageType = PlatformGetSiliconPackageType();

    /* Read the opp for which the SBL has been compiled */
    oppId = SBLGetOppId(siliconPackageType);

    if (PLATFORM_SILICON_PACKAGE_TYPE_12X12 == siliconPackageType)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                     "\n Identified 12X12 Silicon \n");
    }
    else /* PLATFORM_SILICON_PACKAGE_TYPE_15X15 == siliconPackageType */
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                     "\n Identified 15X15 Silicon \n");
    }

    /* Configure Voltage Rails : Done after DPLL_PER to make sure
     * the I2C1 gets the 96 MHz clock.
     */
    retVal += SBLUtilsConfigAllVoltageRails(oppId);

    /* Enable the Power Domains */
    retVal += SBLUtilsConfigPowerDomains();

    /* Print error in case initial configuration not done correctly */
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(
            SBLLIB_TRACE_LEVEL_ERROR,
            "\n SBL Initial Config After IPU LBIST and MBIST Failed \n");
        SBLLibAbortBoot();
    }

    timeValSblInitEnd = SBLUtilsRead32KTimer();

    timeValSocInitStart = SBLUtilsRead32KTimer();

    /* Configure DPLL DDR and DPLL GMAC */
    SBLUtilsConfigDpll(oppId);

#if (SBL_LIB_CONFIG_ENABLE_OTHER_TESOC_TESTS == 1)
    SblConfigAndInitiateOtherTesocTests();
#endif

    /* Enable the Clock Domains */
    SBLUtilsConfigClockDomains();

    /* Enable the Modules */
    SBLUtilsConfigModules();

    /* Configure PADs for TI TDA3xx EVM */
    SBLConfigTIEVMPad();

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                 "\n TI EVM PAD Configuration Completed \n");

    timeValSocInitEnd = SBLUtilsRead32KTimer();

    timeValDdrConfigStart = SBLUtilsRead32KTimer();

    if (PLATFORM_SILICON_PACKAGE_TYPE_12X12 == siliconPackageType)
    {
        /*Configure LPDDR2 */
        #if (SBLLIB_DDR_TYPE_LPDDR2 == SBL_LIB_CONFIG_DDR_TYPE_12X12)
        SBLUtilsLPDDR2Config(
            (uint32_t) SBL_LIB_CONFIG_DDR_SPEED_12X12);
        #else
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Invalid DDR Type \n");
        SBLLibAbortBoot();
        #endif
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                     "\n DDR Configuration Completed \n");
    }
    else /* PLATFORM_SILICON_PACKAGE_TYPE_15X15 == siliconPackageType */
    {
        /* Configure DDR */
        #if (SBLLIB_DDR_TYPE_DDR2 == SBL_LIB_CONFIG_DDR_TYPE)
        SBLUtilsDDR2Config(SBL_LIB_CONFIG_DDR_SPEED);
        #elif (SBLLIB_DDR_TYPE_DDR3 == SBL_LIB_CONFIG_DDR_TYPE)
        SBLUtilsDDR3Config(SBL_LIB_CONFIG_DDR_SPEED);
        #else
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Invalid DDR Type \n");
        SBLLibAbortBoot();
        #endif
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                     "\n DDR Configuration Completed \n");
    }

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_IMP_INFO,
                 "\n TDA3xx SOC Init Completed \n");

    timeValDdrConfigEnd = SBLUtilsRead32KTimer();

#if (SBL_LIB_CONFIG_ENABLE_EMIF_ECC == 1)
    timeValEccInitStart = SBLUtilsRead32KTimer();

    /* Disable EMIF ECC */
    EMIFConfigECCDisableEcc(SOC_EMIF1_CONF_REGS_BASE);

    retVal = SBLUtilsEmifECCConfigure();

    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n EMIF ECC configuration failed \n");
    }

    timeValEccInitEnd = SBLUtilsRead32KTimer();
#endif

    timeValAppImgLoadStart = SBLUtilsRead32KTimer();

    /* Initialize the EDMA */
    EDMAsetRegion(0);
    EDMA3Init(SOC_EDMA_TPCC_BASE, 0);

    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE,
                        EDMA3_CHANNEL_TYPE_DMA,
                        edmaChNum,
                        edmaTccNum,
                        edmaEvtqNum);

    /* Reset the slave cores */
    SBLLibResetAllSlaveCores();

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1, "\n App Image Download Begins \n");

    SBLLibAppImageParamsInit(&appImgParams);
#if (SBL_LIB_CONFIG_ENABLE_CRC == 1)
    SBLLibRegisterCRCCallback(&SBLUtilsComputeCRC);
    appImgParams.enableCrc = (uint32_t) TRUE;
#endif

    appImgParams.appImgMetaHeader   = &sblAppMetaHeader;
    appImgParams.appImgRPRCHeader   = &sblAppRPRCHeader;
    appImgParams.entryPoints        = &sblEntryPoints;
    appImgParams.ddrAppImageAddress = SBLUtilsGetDDRAppCopyAddress();

    /*Load the App Image */
    retVal = SBLLoadAppImage(&appImgParams);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_IMP_INFO,
                     "\n Valid App Image is not Available \n");
    }
    else
    {
        #if (SBL_OPT_LEVEL < SBLLIB_OPT_LEVEL_HIGH)
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_IMP_INFO,
                     "\n App Image Download Completed \n");
        #else
        if ((0U != sblEntryPoints.entryPoint[SBLLIB_CORE_ID_IPU1_CPU0]) &&
            (0U == sblEntryPoints.entryPoint[SBLLIB_CORE_ID_IPU1_CPU1]) &&
            (0U == sblEntryPoints.entryPoint[SBLLIB_CORE_ID_DSP1]) &&
            (0U == sblEntryPoints.entryPoint[SBLLIB_CORE_ID_DSP2]) &&
            (0U == sblEntryPoints.entryPoint[SBLLIB_CORE_ID_EVE1]))
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_IMP_INFO,
                "\n Valid App Image only on IPU1 CPU0, load Completed\n");
        }
        else if ((0U != sblEntryPoints.entryPoint[SBLLIB_CORE_ID_IPU1_CPU0]) &&
                 (0U != sblEntryPoints.entryPoint[SBLLIB_CORE_ID_IPU1_CPU1]) &&
                 (0U == sblEntryPoints.entryPoint[SBLLIB_CORE_ID_DSP1]) &&
                 (0U == sblEntryPoints.entryPoint[SBLLIB_CORE_ID_DSP2]) &&
                 (0U == sblEntryPoints.entryPoint[SBLLIB_CORE_ID_EVE1]))
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_IMP_INFO,
                "\n Valid App Image only on IPU1 CPU0 and IPU CPU1, load Completed\n");
        }
        else if ((0U != sblEntryPoints.entryPoint[SBLLIB_CORE_ID_IPU1_CPU0]) &&
                 (0U != sblEntryPoints.entryPoint[SBLLIB_CORE_ID_IPU1_CPU1]) &&
                 (0U != sblEntryPoints.entryPoint[SBLLIB_CORE_ID_DSP1]) &&
                 (0U == sblEntryPoints.entryPoint[SBLLIB_CORE_ID_DSP2]) &&
                 (0U == sblEntryPoints.entryPoint[SBLLIB_CORE_ID_EVE1]))
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_IMP_INFO,
                "\n Valid App Image only on IPU1 CPU0, IPU CPU1 and DSP1, load Completed\n");
        }
        else if ((0U != sblEntryPoints.entryPoint[SBLLIB_CORE_ID_IPU1_CPU0]) &&
                 (0U != sblEntryPoints.entryPoint[SBLLIB_CORE_ID_IPU1_CPU1]) &&
                 (0U != sblEntryPoints.entryPoint[SBLLIB_CORE_ID_DSP1]) &&
                 (0U != sblEntryPoints.entryPoint[SBLLIB_CORE_ID_DSP2]) &&
                 (0U == sblEntryPoints.entryPoint[SBLLIB_CORE_ID_EVE1]))
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_IMP_INFO,
                "\n Valid App Image only on IPU1 CPU0, IPU CPU1, DSP1 and DSP2, load Completed\n");
        }
        else
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_IMP_INFO,
                "\n Valid App Image on IPU1 CPU0, IPU CPU1, DSP1, DSP2 and EVE; load Completed\n");
        }
        #endif
    }

    timeValAppImgLoadEnd = SBLUtilsRead32KTimer();

    timeValSlaveCoreBootupStart = SBLUtilsRead32KTimer();

    SblConfigRGMIIPad();

    SBLLibDSP1BringUp(sblEntryPoints.entryPoint[SBLLIB_CORE_ID_DSP1],
                      sblBuildMode);

    SBLLibDSP2BringUp(sblEntryPoints.entryPoint[SBLLIB_CORE_ID_DSP2],
                      sblBuildMode);

    SBLLibEVE1BringUp(sblEntryPoints.entryPoint[SBLLIB_CORE_ID_EVE1],
                      sblBuildMode);

    timeValSlaveCoreBootupEnd = SBLUtilsRead32KTimer();

    EDMA3Deinit(SOC_EDMA_TPCC_BASE, 0);

    if (TRUE == SBL_LOCK_MMR)
    {
        /* Lock the MMR registers */
        PlatformLockMMR();
    }

    timeValSblEnd = SBLUtilsRead32KTimer();

    SBLLibPrintf(
        SBLLIB_TRACE_LEVEL_INFO,
        "\n*****************************************************************\n");
    SBLLibPrintf(
        SBLLIB_TRACE_LEVEL_INFO,
        "\n 32K Timer is used to measure cycles, divide by 32K to get time in seconds \n");
    SblPrintBootCycles("Reset to SBL Init Cycles", timeValSblStart);
#if (SBL_LIB_CONFIG_ENABLE_IPU_TESOC_TESTS == 1)
    SblPrintBootCycles("SBL IPU LBIST Cycles",
                       (timeValIPULbistEnd - timeValIPULbistStart));
    SblPrintBootCycles("SBL IPU MBIST Cycles",
                       (timeValIPUMbistEnd - timeValIPUMbistStart));
    SblPrintBootCycles("SBL Initial Config Cycles including IPU LBIST & MBIST",
                       (timeValSblInitEnd - timeValSblInitStart));
#endif
#if (SBL_LIB_CONFIG_ENABLE_IPU_TESOC_TESTS == 0)
    SblPrintBootCycles("SBL Initial Config Cycles",
                       (timeValSblInitEnd - timeValSblInitStart));
#endif
#if (SBL_LIB_CONFIG_ENABLE_OTHER_TESOC_TESTS == 1)
    SblPrintBootCycles("SOC Init Cycles Including TESOC Tests other than IPU",
                       (timeValSocInitEnd - timeValSocInitStart));
    SblPrintBootCycles("TESOC Tests other than IPU Cycles",
                       (timeValOtherTesocTestEnd - timeValOtherTesocTestStart));
#endif
#if (SBL_LIB_CONFIG_ENABLE_OTHER_TESOC_TESTS == 0)
    SblPrintBootCycles("SOC Init Cycles",
                       (timeValSocInitEnd - timeValSocInitStart));
#endif
    SblPrintBootCycles("DDR Config Clock Cycles",
                       (timeValDdrConfigEnd - timeValDdrConfigStart));
#if (SBL_LIB_CONFIG_ENABLE_EMIF_ECC == 1)
    SblPrintBootCycles("ECC Initialization Cycles",
                       (timeValEccInitEnd - timeValEccInitStart));
#endif
    SblPrintBootCycles("App Image Load Cycles",
                       (timeValAppImgLoadEnd - timeValAppImgLoadStart));
    SblPrintBootCycles("Slave Core Bootup Cycles",
                       (timeValSlaveCoreBootupEnd - timeValSlaveCoreBootupStart));
    SblPrintBootCycles("SBL Boot-up Cycles", (timeValSblEnd - timeValSblStart));
    SBLLibPrintf(
        SBLLIB_TRACE_LEVEL_INFO,
        "\n*****************************************************************\n");

#if (SBL_LIB_CONFIG_DISABLE_UNICACHE == 1)
    /* Evict the IPU1 Uni-cache */
    SBLUtilsEvictIPU1Unicache();

    /* Disable the IPU1 Uni-cache */
    SBLUtilsDisableIPU1Unicache();

    /* Invalidate the IPU1 Uni-cache */
    SBLUtilsInvalidateIPU1Unicache();
#endif
#if (SBL_LIB_CONFIG_DISABLE_AMMU == 1)
    /* AMMU can be disabled only when the optimization level is lower than
     * optimization level high. Otherwise IPU1 Core1 should wait until IPU1
     * Core0 comes up and configures AMMU. Impact of disabling AMMU should be
     * analysed carefully before enabling this option
     */
    SBLUtilsDisableIPU1AMMU();
#endif

    /* In case the SBL optimization level is high, IPU Core1 App has been booted
     * earlier itself before loading Image on any other cores. In other cases
     * the IPU Core1 App boots takes place here
     */
#if (SBL_OPT_LEVEL < SBLLIB_OPT_LEVEL_HIGH)
    /* Set the entry point for IPU1 Core 1 */
    if (0U != sblEntryPoints.entryPoint[SBLLIB_CORE_ID_IPU1_CPU1])
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_IMP_INFO,
                     "\n Jumping to IPU1 CPU1 App \n");
        HW_WR_REG32(SBLLIB_IPU1_CORE_1_ENTRY_POINT_ADDRESS,
                    sblEntryPoints.entryPoint[SBLLIB_CORE_ID_IPU1_CPU1]);
    }
    else
    {
        /* Set while(1) loop */
        HW_WR_REG32((SBLLIB_IPU1_CORE1_BOOT_ADDRESS_NO_IMAGE - 1U), 0xE7FEE7FEU);

        SBLLibPrintf(SBLLIB_TRACE_LEVEL_IMP_INFO,
                     "\n No IPU1 CPU1 App Found, Switching to while Loop \n");
        HW_WR_REG32(SBLLIB_IPU1_CORE_1_ENTRY_POINT_ADDRESS,
                    SBLLIB_IPU1_CORE1_BOOT_ADDRESS_NO_IMAGE);
    }
#endif

    /* Jump to IPU1 Core 0's entry point */
    if (0U != sblEntryPoints.entryPoint[SBLLIB_CORE_ID_IPU1_CPU0])
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_IMP_INFO,
                     "\n Jumping to IPU1 CPU0 App \n");
        UARTWaitUntilTransmitComplete();
        ipu1Core0EntryFuncPtr =
            (EntryFuncPtr_t) (sblEntryPoints.entryPoint[
                                  SBLLIB_CORE_ID_IPU1_CPU0]);
        ipu1Core0EntryFuncPtr();
    }

    while (0U != spin)
    {
        /* To remove MISRA C error */
    }
}

static void SblPrintBootCycles(const char *cyclesString, uint32_t bootCycles)
{
    uint32_t cyclesInMsInt        = 0U, cyclesInMsFrac = 0U;
    char     bootCyclesStr[8]     = {0}, cyclesInMsIntStr[8] = {0},
             cyclesInMsFracStr[8] = {0};

    cyclesInMsInt = (bootCycles * 1000U) / SBL_32KTIMER_REFERENCE_VAL;

    cyclesInMsFrac =
        (((bootCycles *
           1000U) %
          SBL_32KTIMER_REFERENCE_VAL) * 100U) / SBL_32KTIMER_REFERENCE_VAL;

    snprintf(bootCyclesStr, (size_t) 8, "%d", bootCycles);
    snprintf(cyclesInMsIntStr, (size_t) 8, "%d", cyclesInMsInt);
    snprintf(cyclesInMsFracStr, (size_t) 8, "%02d", cyclesInMsFrac);

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO, "\n ");
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO, cyclesString);
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO, " - ");
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO, bootCyclesStr);
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO, "  (");
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO, cyclesInMsIntStr);
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO, ".");
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO, cyclesInMsFracStr);
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO, " ms) \n");
}

#if (SBL_LIB_CONFIG_ENABLE_OTHER_TESOC_TESTS == 1)
static void SblConfigAndInitiateOtherTesocTests(void)
{
    int32_t        retVal = STW_SOK;
    uint32_t       blockIndex;
    tesocTestCfg_t tesocTestConfig;

    /* Test Start Time-stamp */
    timeValOtherTesocTestStart = SBLUtilsRead32KTimer();

    tesocTestConfig.testId = TESOC_TEST_ID_ISSDSSVIP;
    /* Configure and enable TESOC HS divider */
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_TESOC_EXT_CLK, (uint32_t) 1U);

    retVal  = TESOCGetDefaultSliceInfo(SOC_TESOC_BASE, &tesocTestConfig);
    retVal += SBLLibRunTesocTest(TESOC_TEST_ID_ISSDSSVIP, &tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n ISSDSSVIP TESOC Test Failed to Start/Finish \n");
        SBLLibAbortBoot();
    }

    retVal = SBLLibCheckTesocTestResult(&tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n ISSDSSVIP TESOC Test Result: FAIL \n");
        SBLLibAbortBoot();
    }

    tesocTestConfig.testId = TESOC_TEST_ID_EVE;
    /* Configure and enable TESOC HS divider */
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_TESOC_EXT_CLK, (uint32_t) 1U);

    retVal = TESOCGetDefaultSliceInfo(SOC_TESOC_BASE, &tesocTestConfig);
    for (blockIndex = 0; blockIndex < TESOC_NUM_SLICE_BLOCKS; blockIndex++)
    {
        tesocTestConfig.sliceTestBlock[blockIndex] = 0x0U;
    }
    tesocTestConfig.sliceTestBlock[0U] = 0x800U;
    retVal += SBLLibRunTesocTest(TESOC_TEST_ID_EVE, &tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(
            SBLLIB_TRACE_LEVEL_ERROR,
            "\n EVE LBIST after ISSDSSVIP Failed to Start/Finish \n");
        SBLLibAbortBoot();
    }

    retVal = SBLLibCheckTesocTestResult(&tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n EVE LBIST after ISSDSSVIP Result: FAIL \n");
        SBLLibAbortBoot();
    }

    tesocTestConfig.testId = TESOC_TEST_ID_ISS;
    /* Configure and enable TESOC HS divider */
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_TESOC_EXT_CLK, (uint32_t) 1U);

    retVal  = TESOCGetDefaultSliceInfo(SOC_TESOC_BASE, &tesocTestConfig);
    retVal += SBLLibRunTesocTest(TESOC_TEST_ID_ISS, &tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n ISS TESOC Test Failed to Start/Finish \n");
        SBLLibAbortBoot();
    }

    retVal = SBLLibCheckTesocTestResult(&tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n ISS TESOC Test Result: FAIL \n");
        SBLLibAbortBoot();
    }

    tesocTestConfig.testId = TESOC_TEST_ID_EVE;
    /* Configure and enable TESOC HS divider */
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_TESOC_EXT_CLK, (uint32_t) 1U);

    retVal = TESOCGetDefaultSliceInfo(SOC_TESOC_BASE, &tesocTestConfig);
    for (blockIndex = 0; blockIndex < TESOC_NUM_SLICE_BLOCKS; blockIndex++)
    {
        tesocTestConfig.sliceTestBlock[blockIndex] = 0x0U;
    }
    tesocTestConfig.sliceTestBlock[0U] = 0x800U;
    retVal += SBLLibRunTesocTest(TESOC_TEST_ID_EVE, &tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n EVE LBIST after ISS Failed to Start/Finish \n");
        SBLLibAbortBoot();
    }

    retVal = SBLLibCheckTesocTestResult(&tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n EVE LBIST after ISS Result: FAIL \n");
        SBLLibAbortBoot();
    }

    tesocTestConfig.testId = TESOC_TEST_ID_DSS;
    /* Configure and enable TESOC HS divider */
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_TESOC_EXT_CLK, (uint32_t) 1U);

    retVal  = TESOCGetDefaultSliceInfo(SOC_TESOC_BASE, &tesocTestConfig);
    retVal += SBLLibRunTesocTest(TESOC_TEST_ID_DSS, &tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n DSS TESOC Test Failed to Start/Finish  \n");
        SBLLibAbortBoot();
    }

    retVal = SBLLibCheckTesocTestResult(&tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n DSS TESOC Test Result: FAIL \n");
        SBLLibAbortBoot();
    }

    tesocTestConfig.testId = TESOC_TEST_ID_EVE;
    /* Configure and enable TESOC HS divider */
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_TESOC_EXT_CLK, (uint32_t) 1U);

    retVal = TESOCGetDefaultSliceInfo(SOC_TESOC_BASE, &tesocTestConfig);
    for (blockIndex = 0; blockIndex < TESOC_NUM_SLICE_BLOCKS; blockIndex++)
    {
        tesocTestConfig.sliceTestBlock[blockIndex] = 0x0U;
    }
    tesocTestConfig.sliceTestBlock[0U] = 0x800U;
    retVal += SBLLibRunTesocTest(TESOC_TEST_ID_EVE, &tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n EVE LBIST after DSS Failed to Start/Finish  \n");
        SBLLibAbortBoot();
    }

    retVal = SBLLibCheckTesocTestResult(&tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n EVE LBIST after DSS Result: FAIL \n");
        SBLLibAbortBoot();
    }

    tesocTestConfig.testId = TESOC_TEST_ID_VIP;
    /* Configure and enable TESOC HS divider */
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_TESOC_EXT_CLK, (uint32_t) 1U);

    retVal  = TESOCGetDefaultSliceInfo(SOC_TESOC_BASE, &tesocTestConfig);
    retVal += SBLLibRunTesocTest(TESOC_TEST_ID_VIP, &tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n VIP TESOC Test Failed to Start/Finish  \n");
        SBLLibAbortBoot();
    }

    retVal = SBLLibCheckTesocTestResult(&tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n VIP TESOC Test Result: FAIL \n");
        SBLLibAbortBoot();
    }

    tesocTestConfig.testId = TESOC_TEST_ID_EVE;
    /* Configure and enable TESOC HS divider */
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_TESOC_EXT_CLK, (uint32_t) 1U);

    retVal = TESOCGetDefaultSliceInfo(SOC_TESOC_BASE, &tesocTestConfig);
    for (blockIndex = 0; blockIndex < TESOC_NUM_SLICE_BLOCKS; blockIndex++)
    {
        tesocTestConfig.sliceTestBlock[blockIndex] = 0x0U;
    }
    tesocTestConfig.sliceTestBlock[0U] = 0x800U;
    retVal += SBLLibRunTesocTest(TESOC_TEST_ID_EVE, &tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n EVE LBIST Test after VIP Failed to Start/Finish  \n");
        SBLLibAbortBoot();
    }

    retVal = SBLLibCheckTesocTestResult(&tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n EVE LBIST after VIP Result: FAIL \n");
        SBLLibAbortBoot();
    }

    tesocTestConfig.testId = TESOC_TEST_ID_DSP1;
    /* Configure and enable TESOC HS divider */
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_TESOC_EXT_CLK, (uint32_t) 2U);

    retVal  = TESOCGetDefaultSliceInfo(SOC_TESOC_BASE, &tesocTestConfig);
    retVal += SBLLibRunTesocTest(TESOC_TEST_ID_DSP1, &tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n DSP1 TESOC Test Failed to Start/Finish  \n");
        SBLLibAbortBoot();
    }

    retVal = SBLLibCheckTesocTestResult(&tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n DSP1 TESOC Test Result: FAIL \n");
        SBLLibAbortBoot();
    }

    tesocTestConfig.testId = TESOC_TEST_ID_DSP2;
    /* Configure and enable TESOC HS divider */
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_TESOC_EXT_CLK, (uint32_t) 2U);

    retVal  = TESOCGetDefaultSliceInfo(SOC_TESOC_BASE, &tesocTestConfig);
    retVal += SBLLibRunTesocTest(TESOC_TEST_ID_DSP2, &tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n DSP2 TESOC Test Failed to Start/Finish  \n");
        SBLLibAbortBoot();
    }

    retVal = SBLLibCheckTesocTestResult(&tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n DSP2 TESOC Test Result: FAIL \n");
        SBLLibAbortBoot();
    }

    tesocTestConfig.testId = TESOC_TEST_ID_EVE;
    /* Configure and enable TESOC HS divider */
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_TESOC_EXT_CLK, (uint32_t) 1U);

    retVal  = TESOCGetDefaultSliceInfo(SOC_TESOC_BASE, &tesocTestConfig);
    retVal += SBLLibRunTesocTest(TESOC_TEST_ID_EVE, &tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n EVE TESOC Test Failed to Start/Finish  \n");
        SBLLibAbortBoot();
    }

    retVal = SBLLibCheckTesocTestResult(&tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n EVE TESOC Test Result: FAIL \n");
        SBLLibAbortBoot();
    }

    /* Test Complete Time-stamp */
    timeValOtherTesocTestEnd = SBLUtilsRead32KTimer();
}

#endif
