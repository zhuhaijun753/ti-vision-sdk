/**
 *  \file   main_tda3xx.c
 *
 *  \brief  System Config implementation example.
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
#include "timer.h"
#include "hw_ctrl_core.h"
#include "hw_l4per_cm_core.h"
#include <wd_timer.h>
#include "pmlib_sysconfig.h"
#include "pm_utils.h"
#include "hw_pmhal_data_names.h"
#include "hw_ctrl_core_sec.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define PMHAL_PRCM_MOD_MIN (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)
#define PMHAL_PRCM_MOD_MAX (PMHAL_PRCM_MOD_COUNT - 1U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

pmErrCode_t    finalSuccess = PM_SUCCESS;

pmlibSysConfigPowerStateParams_t gInputTable[] =
{
    {PMHAL_PRCM_MOD_CRC,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_SMARTREFLEX_CORE,    PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_EFUSE_CTRL_CUST,     PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_DSP1,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_DSP2,                PMLIB_SYS_CONFIG_AUTO_CG       },
    {PMHAL_PRCM_MOD_DSS,                 PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_DLL,                 PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_EMIF1,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
#ifndef BUILD_M4
    {PMHAL_PRCM_MOD_EVE1,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
#endif
    {PMHAL_PRCM_MOD_CPGMAC,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCASP1,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER5,              PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TIMER6,              PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TIMER7,              PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TIMER8,              PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
#ifndef BUILD_M4
    {PMHAL_PRCM_MOD_IPU1,                PMLIB_SYS_CONFIG_AUTO_CG       },
#endif
    {PMHAL_PRCM_MOD_IEEE1500_2_OCP,      PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP, PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DLL_AGING,           PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_L3_INSTR,            PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_L3_MAIN_2,           PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_OCP_WP_NOC,          PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_GPMC,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_L3_MAIN_1,           PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MMU_EDMA,            PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_OCMC_RAM1,           PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TESOC,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TPCC,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TPTC1,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_TPTC2,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_L4_CFG,              PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_SPINLOCK,            PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MAILBOX1,            PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MAILBOX2,            PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_I2C1,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_I2C2,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_L4_PER1,             PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_DCC6,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_DCC7,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER2,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER3,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER4,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DCC5,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_ELM,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_ESM,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCSPI1,              PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_MCSPI2,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCSPI3,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MCSPI4,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_UART1,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_UART2,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_UART3,               PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_GPIO2,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_GPIO3,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_GPIO4,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_MMC4,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DCAN2,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_L4_PER2,             PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_ADC,                 PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_PWMSS1,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_QSPI,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_L4_PER3,             PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_DCC1,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DCC2,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DCC3,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_DCC4,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_VIP1,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_ISS,                 PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_DEBUG_LOGIC,         PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_COUNTER_32K,         PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_CTRL_MODULE_WKUP,    PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_DCAN1,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_GPIO1,               PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_L4_WKUP,             PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_RTI1,                PMLIB_SYS_CONFIG_ALWAYS_ENABLED},
    {PMHAL_PRCM_MOD_RTI2,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_RTI3,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_RTI4,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_RTI5,                PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_TIMER1,              PMLIB_SYS_CONFIG_DISABLED      },
    {PMHAL_PRCM_MOD_CAMERARX,            PMLIB_SYS_CONFIG_DISABLED      }
};

const uint32_t numTableEntries = sizeof (gInputTable) /
                                 sizeof (pmlibSysConfigPowerStateParams_t);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    uint32_t                  i = 0U;
    pmhalPrcmModuleId_t       idx;
    pmErrCode_t               status = PM_SUCCESS;
    pmlibSysConfigErrReturn_t resultReturn[sizeof (gInputTable) /
                                           sizeof (
                                               pmlibSysConfigPowerStateParams_t)
    ];
    PlatformUART3SetPinMux();
    UARTStdioInit();
    UARTPuts("\nPM System Config Test App\n", -1);

    PlatformUnlockMMR();

    status = PMLIBSysConfigSetPowerState(gInputTable, (uint32_t) numTableEntries,
                                         PM_TIMEOUT_INFINITE,
                                         resultReturn);

    if (PM_SUCCESS == status)
    {
        UARTPuts("All Module Power Status Success... Printing Pass status\n",
                 -1);
    }

    for (i = 0U; i < numTableEntries; i++)
    {
        idx = gInputTable[i].modId;
        if (idx < PMHAL_PRCM_MOD_COUNT)
        {
            UARTPuts((char *) pmhalNodeList_names[idx], -1);
        }
        UARTPuts(": ", -1);
        if (PMLIB_SYS_CONFIG_ALWAYS_ENABLED == gInputTable[i].pwrState)
        {
            if (PM_SUCCESS == resultReturn[i].failCause)
            {
                UARTPuts("PMLIB_SYS_CONFIG_ALWAYS_ENABLED PASS\n", -1);
            }
            else if (PM_SYS_CONFIG_MODULE_CANNOT_BE_ENABLED ==
                     resultReturn[i].failCause)
            {
                UARTPuts(
                    "No Valid Module Mode, Cannot be enabled from software\n",
                    -1);
                UARTPuts("Optional Clocks if any have been enabled\n", -1);
            }
            else
            {
                UARTPuts(
                    "PMLIB_SYS_CONFIG_ALWAYS_ENABLED FAIL :Error Code Returned : ",
                    -1);
                UARTPutNum(resultReturn[i].failCause);
                UARTPuts("\n", -1);
                finalSuccess = PM_FAIL;
            }
        }

        if (PMLIB_SYS_CONFIG_DISABLED == gInputTable[i].pwrState)
        {
            if (PM_SUCCESS == resultReturn[i].failCause)
            {
                UARTPuts("PMLIB_SYS_CONFIG_DISABLED PASS\n", -1);
            }
            else if (PM_SYS_CONFIG_MODULE_CANNOT_BE_DISABLED ==
                     resultReturn[i].failCause)
            {
                UARTPuts(
                    "No Valid Module Mode, Cannot be disabled from software\n",
                    -1);
                UARTPuts("Optional Clocks if any have been disabled\n", -1);
            }
            else if (PM_SYS_CONFIG_MODULE_HAS_DEPENDENCIES ==
                     resultReturn[i].failCause)
            {
                UARTPuts("Module has dependencies\n", -1);
            }
            else
            {
                UARTPuts(
                    "PMLIB_SYS_CONFIG_DISABLED FAIL :Error Code Returned : ",
                    -1);
                UARTPutNum(resultReturn[i].failCause);
                UARTPuts("\n", -1);
                finalSuccess = PM_FAIL;
            }
        }

        if (PMLIB_SYS_CONFIG_AUTO_CG == gInputTable[i].pwrState)
        {
            if (PM_SUCCESS == resultReturn[i].failCause)
            {
                UARTPuts("PMLIB_SYS_CONFIG_AUTO_CG PASS\n", -1);
            }
            else if (PM_SYS_CONFIG_MODULE_CANNOT_BE_ENABLED ==
                     resultReturn[i].failCause)
            {
                UARTPuts(
                    "No Valid Module Mode, Cannot be enabled from software\n",
                    -1);
                UARTPuts("Optional Clocks if any have been enabled\n", -1);
            }
            else if (PM_SYS_CONFIG_MODULE_CANNOT_BE_AUTOCG ==
                     resultReturn[i].failCause)
            {
                UARTPuts(
                    "No Valid CLKCTLR Register. Cannot be auto clock gated\n",
                    -1);
            }
            else
            {
                UARTPuts(
                    "PMLIB_SYS_CONFIG_AUTO_CG FAIL :Error Code Returned : ", -1);
                UARTPutNum(resultReturn[i].failCause);
                UARTPuts("\n", -1);
                finalSuccess = PM_FAIL;
            }
        }
    }
    if (PM_SUCCESS == finalSuccess)
    {
        UARTPuts("\n--------------------------------------------------\n", -1);
        UARTPuts("Sysconfig Test case has passed\n", -1);
    }
    else
    {
        UARTPuts("\n----------------------------------------------------", -1);
        UARTPuts("Sysconfig Test case has failed\n", -1);
    }
    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */
