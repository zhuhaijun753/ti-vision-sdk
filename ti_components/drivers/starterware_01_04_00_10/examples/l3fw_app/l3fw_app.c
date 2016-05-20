/**
 *  \file     l3fw_app.c
 *
 *  \brief    This file contains L3FW test code for checking OCMC firewall.
 *
 *  \details  This application will produce violation by writing into write
 *            protected area.
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
#include "hw_ctrl_core.h"
#include "hw_l3fw.h"
#include "interrupt.h"
#include "platform.h"
#include "uartStdio.h"
#include "irq_xbar.h"
#include "l3fw.h"
#include "safetylib/fwlibl3.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#define APP_L3FW_REGION_ID               (1U)
#define APP_L3FW_REGION_PERMISSOIN       (0xFFFFFFFFU)
#define APP_L3FW_PORT_NUM                (0x0U)

#ifdef TDA3XX_FAMILY_BUILD
/* Example will run on M4 on TDA3xx*/
    #define APP_L3FW_ERROR_INT                  (44U)
    #define APP_XBAR_CPU                        (CPU_IPU1)
    #define APP_XBAR_INST_ERROR                 (XBAR_INST_IPU1_IRQ_44)
    #define APP_XBAR_INTR_SOURCE_ERROR          (CTRL_MODULE_CORE_IRQ_SEC_EVTS)
    #define APP_CONN_ID                         (SOC_CONNID_IPU_INIT)
    #define APP_L3FW_MODULE_INST                (L3FW_OCMC_RAM_INST)
    #define APP_L3FW_REGION_TARGET_ADDR         (SOC_OCMC_RAM1_BASE)
    #define APP_L3FW_REGION_START_ADDR          (SOC_OCMC_RAM1_BASE + 0x1000U)
    #define APP_L3FW_REGION_END_ADDR            (SOC_OCMC_RAM1_BASE + 0x2000U)

#elif defined (TDA2XX_FAMILY_BUILD)

#ifdef BUILD_M4
/* Example will run on M4 on TDA2ex */
    #define APP_L3FW_ERROR_INT                  (44U)
    #define APP_XBAR_CPU                        (CPU_IPU1)
    #define APP_XBAR_INST_ERROR                 (XBAR_INST_IPU1_IRQ_44)
    #define APP_XBAR_INTR_SOURCE_ERROR          (CTRL_MODULE_CORE_IRQ_SEC_EVTS)
    #define APP_CONN_ID                         (L3FW_IPU1_INST)
    #define APP_L3FW_MODULE_INST                (L3FW_OCMC_RAM_INST)
    #define APP_L3FW_REGION_TARGET_ADDR         (SOC_OCMC_RAM1_BASE)
    #define APP_L3FW_REGION_START_ADDR          (SOC_OCMC_RAM1_BASE + 0x1000U)
    #define APP_L3FW_REGION_END_ADDR            (SOC_OCMC_RAM1_BASE + 0x2000U)
#else
/* Example will run on A15 on TDA2xx*/
    #define APP_L3FW_ERROR_INT                  (44U)
    #define APP_XBAR_CPU                        (CPU_MPUSS)
    #define APP_XBAR_INST_ERROR                 (XBAR_INST_MPU_IRQ_44)
    #define APP_XBAR_INTR_SOURCE_ERROR          (CTRL_MODULE_CORE_IRQ_SEC_EVTS)
    #define APP_CONN_ID                         (SOC_CONNID_MPU)
    #define APP_L3FW_MODULE_INST                (L3FW_OCMC_RAM1_INST)
    #define APP_L3FW_REGION_TARGET_ADDR         (SOC_OCMC_RAM1_BASE)
    #define APP_L3FW_REGION_START_ADDR          (SOC_OCMC_RAM1_BASE + 0x1000U)
    #define APP_L3FW_REGION_END_ADDR            (SOC_OCMC_RAM1_BASE + 0x2000U)
#endif
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
volatile uint32_t       isrFlag = 0U;
l3fwRegionErrorStatus_t errorLog;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This function is used to configure and enable CPU interrupt.
 *
 * \param   None.
 *
 * \retval  status          Configuration status.
 */
static uint32_t L3FWAppXBarConfig(void);

/**
 * \brief   This Interrupt Service Routine for L3FW error interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void L3FWAppErrorIntrISR(void *handle);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int main(void)
{
    int32_t                  configStatus;
    uint32_t                 xBarStatus, numOfMaster;
    l3fwMasterList_t         masterList[16];
    l3fwRegionConfigParams_t configParams;

    /* Configure UARTStdioInit */
    PlatformUartConsoleSetPinMux();
    UARTStdioInit();
    UARTPuts("\nStarting application...\n", -1);

    /* Initialize L3FW configuration parameters */
    configParams.regionId         = APP_L3FW_REGION_ID;
    configParams.targetBaseAddr   = APP_L3FW_REGION_TARGET_ADDR;
    configParams.regionStartAddr  = APP_L3FW_REGION_START_ADDR;
    configParams.regionEndAddr    = APP_L3FW_REGION_END_ADDR;
    configParams.regionPermission = APP_L3FW_REGION_PERMISSOIN;

    numOfMaster              = 1U;
    masterList[0].connId     = APP_CONN_ID;
    masterList[0].permission = L3FW_MRM_RW_PERMISSION_READ_ONLY;
    /* Configure XBar and interrupt */
    xBarStatus = L3FWAppXBarConfig();
    if (SUCCESS == xBarStatus)
    {
        /* Configure L3FW module */
        configStatus = FWLIBL3ConfigRegion(APP_L3FW_MODULE_INST,
                                           &configParams,
                                           numOfMaster,
                                           masterList);
        if (STW_SOK == configStatus)
        {
            UARTPuts("L3 Firewall configuration done.\n", -1);
            configStatus = FWLIBL3RegionEnable(APP_L3FW_MODULE_INST,
                                               configParams.regionId,
                                               APP_L3FW_PORT_NUM);
            if (STW_SOK == configStatus)
            {
                UARTPuts("L3 Firewall region is enabled.\n", -1);
                UARTPuts("Waiting for violation to happen.\n", -1);
                while (0U == isrFlag)
                {
                    /* Generating violation here */
                    HW_WR_REG32(0x40301050, 0xAAAAAAAAU);
                }
                FWLIBL3RegionDisable(APP_L3FW_MODULE_INST,
                                     configParams.regionId,
                                     APP_L3FW_PORT_NUM);
            }
            else
            {
                UARTPuts("L3 Firewall region can not be enabled.\n", -1);
            }
        }
        else
        {
            UARTPuts("Error in L3 Firewall configuration done.\n", -1);
        }
        UARTPuts("Application execution completed.\n", -1);
    }
    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static uint32_t L3FWAppXBarConfig(void)
{
    uint32_t status = FAIL;

    /* Configure Cross bar instance and interrupt */
    PlatformUnlockMMR();

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
        /* Enable Error interrupt for L3FW */
        Intc_Init();
        Intc_IntEnable(APP_L3FW_ERROR_INT);

        /* Register ISR */
        Intc_IntRegister(APP_L3FW_ERROR_INT,
                         (IntrFuncPtr) L3FWAppErrorIntrISR, 0);
        Intc_IntPrioritySet(APP_L3FW_ERROR_INT, 1, 0);
        Intc_SystemEnable(APP_L3FW_ERROR_INT);
    }
    return status;
}

static void L3FWAppErrorIntrISR(void *handle)
{
    uint32_t regVal;

    UARTPuts("\nIn ISR...\n", -1);
    UARTPuts("OUT BAND ERROR interrupt generated.\n", -1);
    regVal = HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                         CTRL_CORE_SEC_ERR_STATUS_FUNC_1);
    if (CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L3RAM1_FW_ERROR_MASK ==
        (regVal & CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L3RAM1_FW_ERROR_MASK))
    {
        UARTPuts("Out Band error is generated by L3 Firewall.\n", -1);
        FWLIBL3GetErrorLog(APP_L3FW_MODULE_INST, APP_L3FW_PORT_NUM, &errorLog);
        UARTPuts("===================================================\n", -1);
        UARTPuts("Violation Details:\n", -1);
        UARTprintf("L3 Firewall Instance : 0x%x\n", APP_L3FW_MODULE_INST);
        UARTprintf("MReqType(0:data access/1:\
instruction fetch) : %d\n", errorLog.mReqType);
        UARTprintf("Supervisor mode(0:User/1:Privilege) : %d\n",
                   errorLog.mReqSupervisor);
        UARTprintf("Mode(0:Functional/Debug) : %d\n", errorLog.mReqDebug);
        UARTprintf("Access Type(0:Read/1:Write) : %d\n", errorLog.accessType);
        UARTprintf("Master connId : 0x%x\n", errorLog.connIdMSB4bit);
        UARTprintf("Error Start Region : %d\n", errorLog.errorStartRegion);
        UARTprintf("Error End Region : %d\n", errorLog.errorEndRegion);
        UARTprintf("Block burst violation : %d\n", errorLog.blockBurstViolation);
        UARTprintf("Error address offset : 0x%x\n", errorLog.addrOffset);
        UARTPuts("===================================================\n", -1);
        HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                    CTRL_CORE_SEC_ERR_STATUS_FUNC_1,
                    CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L3RAM1_FW_ERROR_MASK);
        FWLIBL3ClearErrorLog(APP_L3FW_MODULE_INST, APP_L3FW_PORT_NUM);
    }
    else
    {
        UARTPuts("Out Band error is not generated by L3 Firewall.\n", -1);
    }

    isrFlag = 1U;
}

