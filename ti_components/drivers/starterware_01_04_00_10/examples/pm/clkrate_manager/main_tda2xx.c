/**
 *  \file main_tda2xx.c
 *
 *  \brief Clock Rate Manager Library Example Application
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
#include "pmhal_prcm.h"
#include "common/stw_types.h"
#include "pmhal_cm.h"
#include "pmhal_mm.h"
#include "pmhal_vm.h"
#include "pmhal_pmic.h"
#include "hw_ctrl_core.h"
#include "hw_l4per_cm_core.h"
#include "pm/pmlib/pmlib_clkrate.h"
#ifndef TDA2EX_BUILD
#include "pmhal_tps659039.h"
#else
#include "pmhal_tps65917.h"
#endif
#include "pmlib_boardconfig.h"
#include "hw_pmhal_data_names.h"
#include "pmhal_pmicComm.h"
#include "hsi2c.h"
#include "pm_utils.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define VSIZE_TYPE(vec, type) (sizeof (vec) / sizeof (type))
/**
 * \brief Macro to find the number of elements of the array.
 */

/** I2C System Clock - PER_96M_CLK:  96 MHz */
#define PM_TEST_UTILS_I2C_SYSTEM_CLOCK       (96000000U)

/** I2C Internal Clock -  9.6 MHz , Fast Mode of Communication is
 *  is used here. A pre-scaler of 23 would be calculated here. Refer
 *  TRM for details on the different I2C modes.
 */
#define PM_TEST_UTILS_I2C_INTERNAL_CLOCK     (9600000U)

/** I2C Output Clock -  400 KHz, This complies with the Fast Mode
 *  of the I2C operation of 100 Kbps.
 */
#define PM_TEST_UTILS_I2C_OUTPUT_CLOCK       (400000U)

/**
 * When checking for I2C IRQSTATUS setting this count is used to
 * repeatedly check the status. This number is empirically derived.
 */
#define PM_TEST_UTILS_I2C_TIMEOUT_COUNT      (4000U)

/** Write Flag used when checking for the transfer status. */
#define PM_TEST_UTILS_I2C_WRITE              (1U)

/** Read Flag used when checking for the transfer status. */
#define PM_TEST_UTILS_I2C_READ               (2U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief Structure contains variables used by the example for automated
 *        debugging and testing
 */
typedef struct
{
    pmhalPrcmModuleId_t modId;
    /**< module Id */
    pmhalPrcmClockId_t  clkId;
    /**< clock Id */
    uint32_t            clkRate;
    /**< clock rate for setting */
}moduleClockList_t;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This function performs the I2C initialization to talk to PMIC.
 *
 * \param   None.
 *
 * \retval  None.
 */
static int32_t PmTestUtilsI2cInit(void);

/**
 * \brief   This function reads a byte from the PMIC via I2C
 *
 * \param   i2cNum   Instance Id of the I2C. 1 - for I2C1, 2 - for I2C2
 * \param   i2cDevAddr  I2C Slave address for the PMIC
 * \param   regAddr     Pointer to the register address which is to be read.
 * \param   regValue    Pointer to the location where the read value will be
 *                      placed.
 * \param   numRegs     Number of registers to be read.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t PmTestUtilsI2cReadByte(uint32_t i2cNum, uint32_t i2cDevAddr,
                                      const uint8_t *regAddr,
                                      uint8_t *regValue,
                                      uint32_t numRegs);

/**
 * \brief   This function writes a byte of data to the register of PMIC via I2C
 *
 * \param   i2cNum   Instance Id of the I2C. 1 - for I2C1, 2 - for I2C2
 * \param   i2cDevAddr  I2C Slave address for the PMIC
 * \param   regAddr     Pointer to the register address which is to be written.
 * \param   regValue    Pointer to the location where the write value will be
 *                      placed.
 * \param   numRegs     Number of registers to be written.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t PmTestUtilsI2cWriteByte(uint32_t i2cNum, uint32_t i2cDevAddr,
                                       const uint8_t *regAddr,
                                       const uint8_t *regValue,
                                       uint32_t numRegs);
/**
 * \brief   Poll for Bus Busy and return when bus is not busy or timed out.
 *
 * \param   i2cNum      The I2C number used on the board to connect to the
 *                      desired PMIC.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t PmTestUtilsI2cWaitForBB(uint32_t i2cNum);

/**
 * \brief  Poll for the given flags and return when any of the flags is set or
 *         timed out.
 *
 * \param   i2cNum      The I2C number used on the board to connect to the
 *                      desired PMIC.
 * \param   flags       Flag to be waited for.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t PmTestUtilsI2cWaitForFlags(uint32_t i2cNum, uint32_t flags);

/**
 * \brief  Write the given number of bytes to the given slave address.
 *
 * \param   i2cNum      The I2C number used on the board to connect to the
 *                      desired PMIC.
 * \param   slaveAddr   Address to which the data should be written.
 * \param   data        Data to be written.
 * \param   count       Number of Bytes to be written.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t PmTestUtilsI2cWrite(uint32_t i2cNum,
                                   uint8_t slaveAddr, const uint8_t data[],
                                   uint8_t count);

/**
 * \brief  Read one byte from the given slave address.
 *
 * \param   i2cNum      The I2C number used on the board to connect to the
 *                      desired PMIC.
 * \param   slaveAddr   Address to which the data should be written.
 * \param   value       Data to be read is returned.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t PmTestUtilsI2cRead(uint32_t i2cNum,
                                  uint8_t  slaveAddr,
                                  uint8_t *value);

/**
 * \brief Check the status of the transfer and handle the error conditions.
 *
 * \param   i2cNum  The I2C number used on the board to connect to the
 *                  desired PMIC.
 * \param   xfr     Transfer Type. Can be any one of PM_TEST_UTILS_I2C_WRITE or
 *                  PM_TEST_UTILS_I2C_READ.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t PmTestUtilsI2cCheckXfrStatus(uint32_t i2cNum, uint32_t xfr);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 * \brief Holds the root clock frequencies specific for a given platform
 */
static uint32_t         *gRootClkFreqList;

/**
 * \brief Holds the voltage domains information whose rails are shared
 */
static pmlibBoardVdRailShare_t           *gVdRailShareList;

/**
 * \brief Structure to define the clocks that one wants to set. The frequency is
 *        given in Hz. Generic clock is used when ever the user does not want to
 *        set any specific clock.
 *        One can look at the generic clocks list to know which module's clock
 *        is defined as generic. To program a specific clock refer
 *        #pmhalPrcmClockId_t
 */
static moduleClockList_t cpuClockTestList[] =
{
    {
        PMHAL_PRCM_MOD_GPU,
        PMHAL_PRCM_CLK_GPU_HYD_GCLK,
        500000000U
    },
    {
        PMHAL_PRCM_MOD_GPU,
        PMHAL_PRCM_CLK_GENERIC,
        532000000U
    },
    {
        PMHAL_PRCM_MOD_DSP1,
        PMHAL_PRCM_CLK_GENERIC,
        600000000U
    },
#ifndef TDA2EX_BUILD
    {
        PMHAL_PRCM_MOD_EVE1,
        PMHAL_PRCM_CLK_GENERIC,
        650000000U
    },
    {
        PMHAL_PRCM_MOD_MPU,
        PMHAL_PRCM_CLK_GENERIC,
        1500000000U
    },
#endif
    {
        PMHAL_PRCM_MOD_MPU,
        PMHAL_PRCM_CLK_GENERIC,
        1176000000U
    }
};

/**
 * \brief Structure to define the clocks that one wants to set. The frequency is
 *        given in Hz. Generic clock is used when ever the user does not want to
 *        set any specific clock.
 *        One can look at the generic clocks list to know which module's clock
 *        is defined as generic. To program a specific clock refer
 *        #pmhalPrcmClockId_t
 */
static moduleClockList_t cpuBypClockTestList[] =
{
    {
        PMHAL_PRCM_MOD_DSP1,
        PMHAL_PRCM_CLK_GENERIC,
        700000000U
    },
#ifndef TDA2EX_BUILD
    {
        PMHAL_PRCM_MOD_EVE1,
        PMHAL_PRCM_CLK_GENERIC,
        650000000U
    },
#endif
};

/**
 * \brief Structure to define the clocks that one wants to set. The frequency is
 *        given in Hz. Generic clock is used when ever the user does not want to
 *        set any specific clock.
 *        One can look at the generic clocks list to know which module's clock
 *        is defined as generic. To program a specific clock refer
 *        #pmhalPrcmClockId_t
 */
#ifndef TDA2EX_BUILD
static moduleClockList_t moduleClockTestList[] =
{
    {PMHAL_PRCM_MOD_DSS,    PMHAL_PRCM_CLK_DSS_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_CPGMAC, PMHAL_PRCM_CLK_GMAC_RFT_CLK,
     451584000},
    {PMHAL_PRCM_MOD_I2C5,   PMHAL_PRCM_CLK_IPU_96M_GFCLK,
     96000000},
    {PMHAL_PRCM_MOD_MCASP1, PMHAL_PRCM_CLK_MCASP1_AHCLKR,
     56448000},
    {PMHAL_PRCM_MOD_TIMER5, PMHAL_PRCM_CLK_TIMER5_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_DCAN1,  PMHAL_PRCM_CLK_DCAN1_SYS_CLK,
     22579200},
    {PMHAL_PRCM_MOD_GPIO1,  PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK,
     32786},
};
#endif
#ifdef TDA2EX_BUILD
static moduleClockList_t moduleClockTestList[] =
{
    {PMHAL_PRCM_MOD_DSS,         PMHAL_PRCM_CLK_DSS_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_CPGMAC,      PMHAL_PRCM_CLK_GMAC_RFT_CLK,
     451584000},
    {PMHAL_PRCM_MOD_TIMER10,     PMHAL_PRCM_CLK_TIMER10_GFCLK,
     451584000},
    {PMHAL_PRCM_MOD_MCSPI4,      PMHAL_PRCM_CLK_PER_48M_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_UART2,       PMHAL_PRCM_CLK_UART2_GFCLK,
     48000000},
    {PMHAL_PRCM_MOD_MMC4,        PMHAL_PRCM_CLK_MMC4_GFCLK,
     192000000},
    {PMHAL_PRCM_MOD_COUNTER_32K, PMHAL_PRCM_CLK_FUNC_32K_CLK,
     32786},
    {PMHAL_PRCM_MOD_I2C6,        PMHAL_PRCM_CLK_PER_96M_GFCLK,
     96000000},
};
#endif

/*
 * Table containing pointers to the functions to program I2C to talk to PMIC IC.
 */
static const pmhalPmicCommI2cOperations_t gPmicI2cfunc = {
    &PmTestUtilsI2cInit,
    &PmTestUtilsI2cReadByte,
    &PmTestUtilsI2cWriteByte
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static void ClkRateLibCpuTest(void)
{
    pmErrCode_t status;

    uint32_t    idx;
    UARTPuts("\nClkrate Manager Cpu Set and Get Frequency test: \n", -1);
    uint32_t    size = VSIZE_TYPE(cpuClockTestList, moduleClockList_t);
    for (idx = 0U; idx < size; idx++)
    {
        uint32_t clkGetRate;
        status = PMLIBClkRateGet(cpuClockTestList[idx].modId,
                                 cpuClockTestList[idx].clkId,
                                 &clkGetRate);

        if (status == PM_SUCCESS)
        {
            UARTprintf(
                "\nthe Clock Rate passed for ModID %s ClkId %s is %u Hz",
                pmhalNodeList_names[cpuClockTestList[idx].modId],
                pmhalClockList_names[cpuClockTestList[idx].clkId],
                clkGetRate);
        }
        else
        {
            UARTprintf(
                "\nGetClockRate failed for ModID %s ClkId %s ",
                pmhalNodeList_names[cpuClockTestList[idx].modId],
                pmhalClockList_names[cpuClockTestList[idx].clkId]);
        }
        status = PMLIBClkRateSet(cpuClockTestList[idx].modId,
                                 cpuClockTestList[idx].clkId,
                                 cpuClockTestList[idx].clkRate);
        if (status == PM_SUCCESS)
        {
            UARTprintf("\nClockSET for ModID %s ClkId %s Passed",
                       pmhalNodeList_names[cpuClockTestList[idx].modId],
                       pmhalClockList_names[cpuClockTestList[idx].clkId]);
        }
        else if (status == PM_CLOCKRATE_SAME_FREQ_CHANGE_REQ)
        {
            UARTprintf("\nClockSET for ModID %s ClkId %s Passed",
                       pmhalNodeList_names[cpuClockTestList[idx].modId],
                       pmhalClockList_names[cpuClockTestList[idx].clkId]);
        }
        else
        {
            UARTprintf("\nClockSET for ModID %s ClkId %s Failed: %d",
                       pmhalNodeList_names[cpuClockTestList[idx].modId],
                       pmhalClockList_names[cpuClockTestList[idx].clkId],
                       status);
        }
        status = PMLIBClkRateGet(cpuClockTestList[idx].modId,
                                 cpuClockTestList[idx].clkId,
                                 &clkGetRate);
        if (status == PM_SUCCESS)
        {
            UARTprintf(
                "\nAfter Clock Rate Set, the Clock Rate for ModID %s ClkId %s is %u Hz  \n ",
                pmhalNodeList_names[cpuClockTestList[idx].modId],
                pmhalClockList_names[cpuClockTestList[idx].clkId],
                clkGetRate);
        }
        else
        {
            UARTprintf(
                "\nAfter Clock Rate Set, Get ClockRate failed for ModID %s ClkId %s \n",
                pmhalNodeList_names[cpuClockTestList[idx].modId],
                pmhalClockList_names[cpuClockTestList[idx].clkId]);
        }
    }
    UARTPuts("\nClkrate Manager Cpu Set and Get Frequency test Completed!!\n",
             -1);
}

static void ClkRateLibCpuBypassFreqTest(void)
{
    pmErrCode_t       status;

    uint32_t          idx;
    pmhalPrcmNodeId_t dpllId = PMHAL_PRCM_DPLL_DSP;
    UARTPuts("\nClkrate Manager Bypass Freq Test: \n", -1);
    uint32_t          size = VSIZE_TYPE(cpuBypClockTestList, moduleClockList_t);
    PMHALCMDpllSetBypassClkSelect(dpllId,
                                  PMHAL_PRCM_DPLL_BYP_CLKINPULOW);
    PMHALCMDpllUnLock(dpllId);
    for (idx = 0U; idx < size; idx++)
    {
        uint32_t clkGetRate;
        status = PMLIBClkRateGet(cpuBypClockTestList[idx].modId,
                                 cpuBypClockTestList[idx].clkId,
                                 &clkGetRate);

        if (status == PM_SUCCESS)
        {
            UARTprintf(
                "\nthe Clock Rate passed for ModID %s ClkId %s is %u Hz \n ",
                pmhalNodeList_names[cpuBypClockTestList[idx].modId],
                pmhalClockList_names[cpuBypClockTestList[idx].clkId],
                clkGetRate);
        }
        else
        {
            UARTprintf(
                "\nGetClockRate failed for ModID %s ClkId %s \n",
                pmhalNodeList_names[cpuBypClockTestList[idx].modId],
                pmhalClockList_names[cpuBypClockTestList[idx].clkId]);
        }
    }
    UARTPuts("\nClkrate Manager Bypass Freq Test Completed!!\n", -1);
}

static void ClkRateLibModuleSetTest(void)
{
    pmErrCode_t status;

    uint32_t    idx;
    UARTPuts("\nClkrate Manager Module Set Frequency test: \n", -1);
    uint32_t    size = VSIZE_TYPE(moduleClockTestList, moduleClockList_t);
    for (idx = 0U; idx < size; idx++)
    {
        uint32_t clkGetRate;
        status = PMLIBClkRateGet(moduleClockTestList[idx].modId,
                                 moduleClockTestList[idx].clkId,
                                 &clkGetRate);

        if (status == PM_SUCCESS)
        {
            UARTprintf(
                "\nthe Clock Rate passed for ModID %s ClkId %s with clkrate %u Hz ",
                pmhalNodeList_names[moduleClockTestList[idx].modId],
                pmhalClockList_names[moduleClockTestList[idx].clkId],
                clkGetRate);
        }
        else
        {
            UARTprintf(
                "\nGetClockRate failed for ModID %s ClkId %s with errorcode %u",
                pmhalNodeList_names[moduleClockTestList[idx].modId],
                pmhalClockList_names[moduleClockTestList[idx].clkId],
                status);
        }
        status = PMLIBClkRateSet(moduleClockTestList[idx].modId,
                                 moduleClockTestList[idx].clkId,
                                 moduleClockTestList[idx].clkRate);
        if (status == PM_SUCCESS)
        {
            UARTprintf(
                "\nClockSET for ModID %s ClkId %s Passed for clkRate %u Hz",
                pmhalNodeList_names[moduleClockTestList[idx].modId],
                pmhalClockList_names[moduleClockTestList[idx].clkId],
                moduleClockTestList[idx].clkRate);
        }
        else if (status == PM_CLOCKRATE_SAME_FREQ_CHANGE_REQ)
        {
            UARTprintf(
                "\nClockSET for ModID %s ClkId %s Passed for clkRate %u Hz",
                pmhalNodeList_names[moduleClockTestList[idx].modId],
                pmhalClockList_names[moduleClockTestList[idx].clkId],
                moduleClockTestList[idx].clkRate);
        }
        else
        {
            UARTprintf(
                "\nClockSET for ModID %s ClkId %s Failed for clkRate %u Hz with errorcode %d",
                pmhalNodeList_names[moduleClockTestList[idx].modId],
                pmhalClockList_names[moduleClockTestList[idx].clkId],
                moduleClockTestList[idx].clkRate,
                status);
        }
        status = PMLIBClkRateGet(moduleClockTestList[idx].modId,
                                 moduleClockTestList[idx].clkId,
                                 &clkGetRate);
        if (status == PM_SUCCESS)
        {
            if (clkGetRate == moduleClockTestList[idx].clkRate)
            {
                UARTprintf(
                    "\nAfter Clock Rate Set,Clock Rate for ModID %s ClkId %s is %u Hz \n",
                    pmhalNodeList_names[moduleClockTestList[idx].modId],
                    pmhalClockList_names[moduleClockTestList[idx].clkId],
                    clkGetRate);
            }
            else
            {
                UARTprintf(
                    "\nAfter Clock Rate Set, Clock Rate failed for ModID %s ClkId %s for %u Hz and current rate is %u Hz  \n",
                    pmhalNodeList_names[moduleClockTestList[idx].modId],
                    pmhalClockList_names[moduleClockTestList[idx].clkId],
                    moduleClockTestList[idx].clkRate,
                    clkGetRate);
            }
        }
        else
        {
            UARTprintf(
                "\nAfter Clock Rate Set, Get ClockRate failed for ModID %s ClkId %s with errorcode %u\n",
                pmhalNodeList_names[moduleClockTestList[idx].modId],
                pmhalClockList_names[moduleClockTestList[idx].clkId],
                status);
        }
    }
    UARTPuts("\nClkrate Manager module Set Frequency test Completed!!\n\n", -1);
}

int32_t INIT(void)
{
    int32_t         retVal = (int32_t) PM_SUCCESS;
    pmhalPrcmVdId_t vdId;
    pmhalVmOppId_t  oppId;
    const pmhalPmicOperations_t *pmicOps;

    /* Get the build time set OPP value using which set the OPP */
    oppId = (pmhalVmOppId_t) PMHAL_VM_OPP_NOM;

    /* Enable I2C1 for PMIC Communication */
    /*Force Wake-up clock domain l4per*/
    retVal = PMHALCMSetCdClockMode(PMHAL_PRCM_CD_L4PER,
                                   PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                   PM_TIMEOUT_INFINITE);

    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_I2C1,
                                PMHAL_PRCM_MODULE_MODE_ENABLED,
                                PM_TIMEOUT_INFINITE);
    /* Register the I2C functions with the PMIC Communication to ensure the
     * PMIC can be communicated with I2C driver specific to SBL
     */
    PMHALPmicCommI2CRegister(&gPmicI2cfunc);
    /*
     * Get the pmic ops and register with the pmic interface.
     */
#ifndef TDA2EX_BUILD
    pmicOps = PMHALTps659039GetPMICOps();
#else
    pmicOps = PMHALTps65917GetPMICOps();
#endif
    retVal = (pmErrCode_t) PMHALPmicRegister(pmicOps);

    retVal = PMHALVMSetOpp(PMHAL_PRCM_VD_MPU, oppId, PM_TIMEOUT_INFINITE);
    /* VD_CORE can only support OPP_NOM */
    retVal =
        (pmErrCode_t) ((int32_t) retVal |
                       (int32_t) PMHALVMSetOpp(PMHAL_PRCM_VD_CORE,
                                               PMHAL_VM_OPP_NOM,
                                               PM_TIMEOUT_INFINITE));
    /*
     * Set the voltage for PMHAL_PRCM_VD_IVAHD, PMHAL_PRCM_VD_DSPEVE
     * and PMHAL_PRCM_VD_GPU.
     */
    for (vdId = PMHAL_PRCM_VD_IVAHD; vdId < PMHAL_PRCM_VD_RTC;
         vdId = (pmhalPrcmVdId_t) ((int32_t) vdId + 1))
    {
        retVal = (pmErrCode_t) ((int32_t) retVal | (int32_t) PMHALVMSetOpp(vdId,
                                                                           oppId,
                                                                           PM_TIMEOUT_INFINITE));
    }
    gRootClkFreqList = PMLIBBoardConfigGetRootClks();
    gVdRailShareList = PMLIBBoardConfigGetVdRailShareInfo();
    retVal           = PMLIBClkRateInit(gRootClkFreqList, gVdRailShareList);
    return (int32_t) retVal;
}

int main(void)
{
    UART_PAD_CONFIG();
    UARTStdioInit();
    UARTPuts("\nPM ClockRate Test App", -1);
    INIT();
    /* Functions to Test clkrate manager */
    ClkRateLibCpuTest();
    ClkRateLibCpuBypassFreqTest();
    ClkRateLibModuleSetTest();
    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static int32_t PmTestUtilsI2cInit(void)
{
    int32_t  status = STW_SOK;
    uint32_t timeout;
    uint32_t baseAddr = SOC_I2C1_BASE;

    /* Force Wake-up clock domain L4PER1 */
    PMHALCMSetCdClockMode(PMHAL_PRCM_CD_L4PER,
                          PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                          PM_TIMEOUT_NOWAIT);

    /* Enable I2C1 for PMIC Communication */
    PMHALModuleModeSet(PMHAL_PRCM_MOD_I2C1,
                       PMHAL_PRCM_MODULE_MODE_ENABLED,
                       PM_TIMEOUT_INFINITE);

    /*
     * Do a soft reset so we can clear any incorrect state and
     * configure to suit the PMIC communication.
     */
    I2CSoftReset(baseAddr);

    /*
     * Ensure that the reset is completed. The RDONE bit is set
     * only when the I2C is enabled, so enable I2C before
     * checking for the reset completion.
     */
    I2CMasterEnable(baseAddr);

    timeout = 50U;  /* Approximately 50ms */
    while ((I2CSystemStatusGet(baseAddr) !=
            I2C_SYSS_RDONE_RSTCOMP)
           && (timeout > 0))
    {
        PMUtilsMinDelayMS((uint32_t) 1U);
        timeout--;
    }

    if (timeout == 0)
    {
        status = STW_EFAIL;
    }

    if (status == STW_SOK)
    {
        /* Disable I2C so we can configure for the PMIC communication. */
        I2CMasterEnable(baseAddr);

        /* Configure the I2C BUS clock frequency (I2C_SCL). */
        I2CMasterInitExpClk(baseAddr,
                            PM_TEST_UTILS_I2C_SYSTEM_CLOCK,
                            PM_TEST_UTILS_I2C_INTERNAL_CLOCK,
                            PM_TEST_UTILS_I2C_OUTPUT_CLOCK);

        /*
         * The PMIC communication is always as a master so we don't have
         * to configure the I2C own address. However, it doesn't hurt.
         */
        I2COwnAddressSet(baseAddr, 0,
                         I2C_OWN_ADDR_0);

        /*
         * Make sure the I2C is not in Forced Idle Mode by setting it to No
         * Idle mode.
         */
        I2CSyscInit(baseAddr,
                    (uint32_t) (I2C_AUTOIDLE_DISABLE |
                                I2C_CUT_OFF_BOTH_CLK |
                                I2C_ENAWAKEUP_DISABLE |
                                I2C_NO_IDLE_MODE));

        /*
         * Configure the I2C:
         *    Select Fast/Standard Mode
         *    Select normal mode (vs. start byte mode)
         *    Select 7-bit slave address mode
         *
         * Note that this API writes the 32-bit value passed to the I2C_CON
         * register; the config bits not mentioned below is set to zero.
         */
        I2CConfig(baseAddr, I2C_CFG_N0RMAL_MODE |
                  I2C_CFG_7BIT_SLAVE_ADDR |
                  I2C_OPMODE_FAST_STAND_MODE);

        /* PMIC Comm uses polling mode; disable all the interrupts. */
        I2CMasterIntDisableEx(baseAddr, I2C_INT_ALL);

        /*
         * Bypass the Tx/Rx FIFO. For PRCM access we always read one byte
         * at a time so FIFO is bypassed.
         */
        I2CFIFOThresholdConfig(baseAddr,
                               0, I2C_TX_MODE);
        I2CFIFOThresholdConfig(baseAddr,
                               0, I2C_RX_MODE);
        I2CFIFOClear(baseAddr, I2C_TX_MODE);
        I2CFIFOClear(baseAddr, I2C_RX_MODE);

        /* Enable I2C module. */
        I2CMasterEnable(baseAddr);

        /*
         * This is required to ensure that the I2C communication continues
         * even if A15 (the master core) is debug halted on a breakpoint.
         */
        I2CMasterEnableFreeRun(baseAddr);
    }

    /* Clear status register  */
    I2CMasterIntClearEx(baseAddr, I2C_INT_ALL);

    return status;
}

static int32_t PmTestUtilsI2cReadByte(uint32_t i2cNum, uint32_t i2cDevAddr,
                                      const uint8_t *regAddr,
                                      uint8_t *regValue,
                                      uint32_t numRegs)
{
    int32_t status = STW_SOK;
    status = PmTestUtilsI2cWrite(i2cNum, i2cDevAddr, regAddr, 1U);

    /* Then read the value sent by the slave.  */
    if (status == STW_SOK)
    {
        status = PmTestUtilsI2cRead(i2cNum, i2cDevAddr, regValue);
    }
    else
    {
        *regValue = 0U;
    }
    return status;
}

static int32_t PmTestUtilsI2cWriteByte(uint32_t i2cNum, uint32_t i2cDevAddr,
                                       const uint8_t *regAddr,
                                       const uint8_t *regValue,
                                       uint32_t numRegs)
{
    uint8_t  data[2];
    uint8_t  count       = (uint8_t) 2U;
    int32_t  status      = STW_SOK;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    data[0] = *regAddr;
    data[1] = *regValue;
    status  = PmTestUtilsI2cWrite(i2cNum, i2cDevAddr, data, count);

    if (status == STW_SOK)
    {
        /*
         * Generate a stop condition and ensure the
         * bus is free before returning.
         */
        I2CMasterStop(baseAddress);

        status = PmTestUtilsI2cWaitForFlags(i2cNum,
                                            I2C_INT_BUS_FREE |
                                            I2C_INT_ADRR_READY_ACESS);

        I2CFlushFifo(baseAddress);

        /* Clear the data count and all the flags. */
        I2CMasterIntClearEx(baseAddress, I2C_INT_ALL);
        I2CSetDataCount(baseAddress, (uint32_t) 0U);
    }
    return status;
}

static int32_t PmTestUtilsI2cRead(uint32_t i2cNum,
                                  uint8_t  slaveAddr,
                                  uint8_t *value)
{
    int32_t  status      = STW_SOK;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    /* Set the slave address */
    I2CMasterSlaveAddrSet(baseAddress,
                          (uint32_t) slaveAddr);

    /* Configure to read 1 data word from the PMIC register.  */
    I2CSetDataCount(baseAddress, (uint32_t) 1U);

    /*
     * Configure i2c as master-receive and enable.
     * Make sure stop condition is generated after the transaction.
     */
    I2CMasterControl(baseAddress,
                     (uint32_t) (I2C_CFG_MST_RX | I2C_CFG_START | I2C_CFG_STOP));

    /* Read the data if the data is ready. */
    status = PmTestUtilsI2cCheckXfrStatus(i2cNum,
                                          (uint32_t) PM_TEST_UTILS_I2C_READ);
    if (status == STW_SOK)
    {
        *value = I2CMasterDataGet(baseAddress);
    }
    else
    {
        *value = 0U;
    }

    /* Wait for I2C access ready before returning. */
    if (status == STW_SOK)
    {
        uint32_t flags = I2C_INT_ADRR_READY_ACESS |
                         I2C_INT_BUS_FREE;
        status = PmTestUtilsI2cWaitForFlags(i2cNum, flags);
    }

    /* Clear the status of the I2C  */
    I2CFlushFifo(baseAddress);
    I2CMasterIntClearEx(baseAddress, I2C_INT_ALL);
    I2CSetDataCount(baseAddress, (uint32_t) 0U);

    return status;
}

static int32_t PmTestUtilsI2cWrite(uint32_t i2cNum,
                                   uint8_t slaveAddr, const uint8_t data[],
                                   uint8_t count)
{
    int32_t  status = STW_SOK;
    uint32_t rawSt;
    uint8_t  i;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    /*
     * Poll the BUS BUSY bit to ensure the bus is not busy before initiating
     * the transaction on the bus.
     */
    status = PmTestUtilsI2cWaitForBB(i2cNum);

    if (status == STW_SOK)
    {
        /* Set the slave address */
        I2CMasterSlaveAddrSet(baseAddress,
                              (uint32_t) slaveAddr);

        /* Configure to send 'count' data words */
        I2CSetDataCount(baseAddress, (uint32_t) count);

        /*
         * Configure i2c as master-transmitter, enable and set start condition.
         * Stop condition is NOT generated as this could be a part of write
         * followed by read (combined format).
         */
        I2CMasterControl(baseAddress,
                         I2C_CFG_MST_TX | I2C_CFG_START);

        /* Transmit 'count' bytes.  */
        for (i = 0; ((i < count) && (status == STW_SOK)); i++)
        {
            /*
             * Check the status to see if the data can be transferred and
             * send data.
             */
            status = PmTestUtilsI2cCheckXfrStatus(
                i2cNum,
                (uint32_t)
                PM_TEST_UTILS_I2C_WRITE);
            if (status == PM_SUCCESS)
            {
                I2CMasterDataPut(baseAddress, data[i]);
            }

            /* Clear XRDY flags */
            rawSt = I2CMasterIntRawStatus(baseAddress);
            I2CMasterIntClearEx(baseAddress,
                                rawSt & I2C_INT_TRANSMIT_READY);
        }

        /*
         * Once we complete writing the 'count' bytes, wait for the
         * ARDY flag to be set. This flag indicates that the I2C
         * is access ready for next transmission. ARDY can also be
         * set if we received NACK so ensure it is not the case.
         */
        if (status == STW_SOK)
        {
            status = PmTestUtilsI2cWaitForFlags(i2cNum,
                                                I2C_INT_ADRR_READY_ACESS);
            if (status == STW_SOK)
            {
                rawSt = I2CMasterIntRawStatus(baseAddress);
                if ((rawSt & I2C_INT_NO_ACK) != 0)
                {
                    status = STW_EFAIL;
                    /* Clear the NACK flag. */
                    I2CMasterIntClearEx(baseAddress,
                                        rawSt & I2C_INT_NO_ACK);
                }

                /* Clear the ARDY flag. */
                I2CMasterIntClearEx(baseAddress,
                                    rawSt & I2C_INT_ADRR_READY_ACESS);
            }
        }
    }

    return status;
}

static int32_t PmTestUtilsI2cCheckXfrStatus(uint32_t i2cNum, uint32_t xfr)
{
    int32_t  status = STW_SOK;
    uint32_t rawSt;
    uint32_t flags = I2C_INT_ADRR_READY_ACESS | I2C_INT_NO_ACK |
                     I2C_INT_ARBITRATION_LOST;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    if (xfr == PM_TEST_UTILS_I2C_WRITE)
    {
        flags |= I2C_INT_TRANSMIT_READY;
    }
    else if (xfr == PM_TEST_UTILS_I2C_READ)
    {
        flags |= I2C_INT_RECV_READY;
    }
    else
    {
        status = STW_EFAIL;
    }

    /*
     * Wait for any of the following conditions to occur and
     * handle them in the loop before transmitting data.
     * NACK, AL, XRDY/RRDY, ARDY
     */
    if (status == STW_SOK)
    {
        status = PmTestUtilsI2cWaitForFlags(i2cNum, flags);
    }

    if (status == STW_SOK)
    {
        rawSt = I2CMasterIntRawStatus(baseAddress);

        /*
         * When I2C is configured as master-transmitter and didn't
         * receive ACK from slave, NACK condition is generated. The
         * following could cause this situation:
         * 1. No receiver is present on the bus with the transmitted
         *    address; board issue
         * 2. Receiver is not ready to communicate with the master
         *    (probably a board/pmic device issue).
         * 3. Receiver gets data or commands it doesn't understand
         *    (incorrect PMIC)
         * 4. Receiver can't receive any more data bytes.
         *
         * NACK can be handled by a master by either generating a
         * STOP condition or a repeated START condition to start
         * a new transfer. In PMIC COMM we generate a STOP
         * condition to abort the transfer and clear the NACK
         * flag.
         *
         * I2C HW clears STT and STP bits in I2C_CON registers.
         */
        if ((rawSt & I2C_INT_NO_ACK) != 0)
        {
            I2CMasterStop(baseAddress);
            I2CMasterIntClearEx(baseAddress,
                                rawSt & I2C_INT_NO_ACK);
            status = STW_EFAIL;
        }
        /*
         * Arbitration loss occurs when multiple masters initiate
         * transfer at the same time. Only one master wins and others
         * loose the arbitration. The arbitration loss flag is set
         * if this local host lost the arbitration. After an
         * arbitration loss, the local host can continue to generate
         * clock till the end of the byte transfer on the bus and
         * must restart the transmission. Recovering from arbitration
         * loss slightly complicates the code and this can be added
         * if there is a need. At present we clear the flag  and
         * return error.
         *
         * When arbitration loss occurs, the I2C HW clears the
         * STT, STP and MST bits. The local host switches to the
         * slave mode.
         */
        else if ((rawSt & I2C_INT_ARBITRATION_LOST) != 0)
        {
            I2CMasterIntClearEx(baseAddress,
                                rawSt & I2C_INT_ARBITRATION_LOST);
            status = STW_EFAIL;
        }
        /*
         * ARDY flag is set to indicate that the local host is access
         * ready. We are in the middle of a data transfer and hence
         * it is bad if we get ARDY flag set. For example, if we
         * get NACKed, the ARDY flag is set in the middle of data
         * transfer.
         */
        else if ((rawSt & I2C_INT_ADRR_READY_ACESS) != 0)
        {
            I2CMasterIntClearEx(baseAddress,
                                rawSt & I2C_INT_ADRR_READY_ACESS);
            status = STW_EFAIL;
        }
        /*
         * XRDY flag is set when the TX FIFO is empty or the TX FIFO
         * threshold is not reached. This means the local host can
         * transmit now.
         *
         * RRDY flag is set when the RX FIFO is empty or the RX FIFO
         * threshold is not reached. This means the local host can
         * receive now.
         */
        else if (((xfr == PM_TEST_UTILS_I2C_WRITE) &&
                  ((rawSt & I2C_INT_TRANSMIT_READY) != 0)) ||
                 ((xfr == PM_TEST_UTILS_I2C_READ) &&
                  ((rawSt & I2C_INT_RECV_READY) != 0)))
        {
            /*
             * Return success so that the caller can send/receive the data
             * Note that the caller needs to clear the XRDY/RRDY flag as
             * needed.
             */
            status = STW_SOK;
        }
        else
        {
            /*
             * We should not get here...
             */
            status = STW_EFAIL;
        }
    }

    return status;
}

static int32_t PmTestUtilsI2cWaitForFlags(uint32_t i2cNum, uint32_t flags)
{
    int32_t  status = STW_SOK;
    uint32_t timeout;
    uint32_t rawSt;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    timeout = PM_TEST_UTILS_I2C_TIMEOUT_COUNT;

    rawSt = I2CMasterIntRawStatus(baseAddress);

    while (((rawSt & flags) == 0) && (timeout > 0U))
    {
        rawSt = I2CMasterIntRawStatus(baseAddress);
        timeout--;
    }

    if (timeout == 0U)
    {
        status = STW_EFAIL;
    }

    return status;
}

static int32_t PmTestUtilsI2cWaitForBB(uint32_t i2cNum)
{
    int32_t  status = STW_SOK;
    uint32_t timeout;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    /*
     * Clear all current interrupts first.
     */
    I2CMasterIntClearEx(baseAddress, I2C_INT_ALL);

    /*
     * Poll the BUS BUSY bit to ensure the bus is not busy before initiating
     * the transaction on the bus.
     */
    for (timeout = PM_TEST_UTILS_I2C_TIMEOUT_COUNT; timeout > 0U; --timeout)
    {
        if (I2CMasterBusBusy(baseAddress) == 0)
        {
            break;
        }
        I2CMasterIntClearEx(baseAddress, I2C_INT_BUS_BUSY);
    }

    if (timeout == 0U)
    {
        status = STW_EFAIL;
    }

    /*
     * Clear all current interrupts.
     */
    I2CMasterIntClearEx(baseAddress, I2C_INT_ALL);

    return status;
}

