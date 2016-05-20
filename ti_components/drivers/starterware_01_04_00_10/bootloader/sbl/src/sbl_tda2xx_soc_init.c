/**
 *  \file     sbl_tda2xx_soc_init.c
 *
 *  \brief    This file contains SoC init functions like configure
 *            dpll, clock domain wake-up & PRCM module enable.
 *
 *  \copyright Copyright (C) 2014 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

/* =============================================================================
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
 * ========================================================================== */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include "common/stw_dataTypes.h"
#include "sbl_tda2xx_prcmlib_dpll.h"
#include "pmhal_prcm.h"
#include "pm/pmhal/pmhal_mm.h"
#include "pm/pmhal/pmhal_pdm.h"
#include "pm/pmhal/pmhal_cm.h"
#include "pm/pmhal/pmhal_sd.h"
#include "pm/pm_types.h"
#include "soc.h"
#include "hw_ctrl_core.h"
#include "hw_ctrl_wkup.h"
#include "hw_ckgen_prm.h"
#include "hw_l3init_cm_core.h"
#include "hw_l4per_cm_core.h"
#include "hw_emif.h"
#include "soc_defines.h"
#include "sbl_tda2xx_platform.h"
#include "sbl_tda2xx_soc_init.h"
#include "uartConsole.h"
#include "platform.h"
#include "sbl_tda2xx_prcm_dpll.h"

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static const SBLPDStateConfig_t gPDStateTable[] = {
    {PMHAL_PRCM_PD_CAM,       PMHAL_PRCM_PD_STATE_ON_ACTIVE, "CAM"      },
    {PMHAL_PRCM_PD_CORE,      PMHAL_PRCM_PD_STATE_ON_ACTIVE, "CORE"     },
    {PMHAL_PRCM_PD_CUSTEFUSE, PMHAL_PRCM_PD_STATE_ON_ACTIVE, "CUSTEFUSE"},
    {PMHAL_PRCM_PD_DSP1,      PMHAL_PRCM_PD_STATE_ON_ACTIVE, "DSP1"     },
#ifndef TDA2EX_BUILD
    {PMHAL_PRCM_PD_DSP2,      PMHAL_PRCM_PD_STATE_ON_ACTIVE, "DSP2"     },
#endif
    {PMHAL_PRCM_PD_DSS,       PMHAL_PRCM_PD_STATE_ON_ACTIVE, "DSS"      },
#ifndef TDA2EX_BUILD
    {PMHAL_PRCM_PD_EVE1,      PMHAL_PRCM_PD_STATE_ON_ACTIVE, "EVE1"     },
    {PMHAL_PRCM_PD_EVE2,      PMHAL_PRCM_PD_STATE_ON_ACTIVE, "EVE2"     },
    {PMHAL_PRCM_PD_EVE3,      PMHAL_PRCM_PD_STATE_ON_ACTIVE, "EVE3"     },
    {PMHAL_PRCM_PD_EVE4,      PMHAL_PRCM_PD_STATE_ON_ACTIVE, "EVE4"     },
#endif
    {PMHAL_PRCM_PD_GPU,       PMHAL_PRCM_PD_STATE_ON_ACTIVE, "GPU"      },
    {PMHAL_PRCM_PD_IPU,       PMHAL_PRCM_PD_STATE_ON_ACTIVE, "IPU"      },
    {PMHAL_PRCM_PD_IVA,       PMHAL_PRCM_PD_STATE_ON_ACTIVE, "IVA"      },
    {PMHAL_PRCM_PD_L3INIT,    PMHAL_PRCM_PD_STATE_ON_ACTIVE, "L3INIT"   },
    {PMHAL_PRCM_PD_L4PER,     PMHAL_PRCM_PD_STATE_ON_ACTIVE, "L4PER"    },
    {PMHAL_PRCM_PD_MPU,       PMHAL_PRCM_PD_STATE_ON_ACTIVE, "MPU"      },
    {PMHAL_PRCM_PD_VPE,       PMHAL_PRCM_PD_STATE_ON_ACTIVE, "VPE"      },
};

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief      dss_dpll_set_clock_div function program the dss pll to
 *             derive clockouts on High divider clock outs
 *
 *
 * \param       None.
 *
 * \return      error status.If error has occurred it returns a non zero value.
 *              If no error has occurred then return status will be zero.
 *
 **/
static int32_t dss_dpll_set_clock_div(enum dss_dpll               dpll,
                                      const struct dpll_config_t *dpll_config);

#ifdef TDA2XX_BUILD
/**
 * \brief    This API tells if the silicon supports Multiple OPPs.
 *
 * \param    None.
 *
 * \return   1: Silicon supports multiple OPPs.
 *           0: Silicon does not support Multiple OPPs.
 *
 **/
static uint32_t is_multiopp_supported(void);
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Device Package read Shift */
#define SBL_TDA2XX_PACKAGE_BIT_SHIFT (16U)
/** \brief Device Package read Mask */
#define SBL_TDA2XX_PACKAGE_BIT_MASK  (0x30000U)
/** \brief Package Type 1: Corresponds to 17x17 package */
#define SBL_TDA2XX_PACKAGE_TYPE_0 (1U)
/** \brief Package Type 2: Corresponds to 23x23 package */
#define SBL_TDA2XX_PACKAGE_TYPE_1 (0U)

#define NUM_ENTRIES_POWER_DOMAIN_STATE_TABLE \
    (sizeof (gPDStateTable) / sizeof (gPDStateTable[0]))

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#ifdef TDA2XX_BUILD
/**
 * \brief    This API tells if the silicon supports Multiple OPPs.
 *
 * \param    None.
 *
 * \return   1: Silicon supports multiple OPPs.
 *           0: Silicon does not support Multiple OPPs.
 *
 **/
static uint32_t is_multiopp_supported(void)
{
    uint32_t retVal = FALSE;
    uint32_t siliconRev, ftRev;

    siliconRev = PlatformGetSiliconRev();

    if (0U != siliconRev)
    {
        retVal = (uint32_t) TRUE;
    }
    else
    {
        ftRev = PlatformGetFtRev();
        if (ftRev >= 11U)
        {
            retVal = (uint32_t) TRUE;
        }
    }
    return (retVal);
}

#endif

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

/**
 * \brief       This API returns what is the current OPP selected.
 *
 * \param       None.
 *
 * \return      returns current OPP
 *
 **/
uint32_t get_current_opp(void)
{
    uint32_t opp = DPLL_OPP_NOM;
#ifdef TDA2XX_BUILD
    uint32_t oppVal = FALSE;
#if (FORCE_OPP_MODE == 1)
    oppVal = TRUE;
#else
    /* Check if OPP_OD and OPP_HIGH are supported */
    oppVal = is_multiopp_supported();
#endif

    if (TRUE == oppVal)
    {
#if (OPP_MODE == OPP_HIGH)
        opp = DPLL_OPP_HIGH;
#elif (OPP_MODE == OPP_OD)
        opp = DPLL_OPP_OD;
#elif (OPP_MODE == OPP_LOW)
        opp = DPLL_OPP_LOW;
#endif
    }
#else

#if (OPP_MODE == OPP_HIGH)
    opp = DPLL_OPP_HIGH;
#elif (OPP_MODE == OPP_OD)
    opp = DPLL_OPP_OD;
#endif

#endif
    return (uint32_t) opp;
}

/**
 * \brief       configure_dpll function program the ADPLLM & ADPLLJM for
 *              vayu SoC
 *
 * \param           None.
 *
 * \return      error status.If error has occured it returns a non zero value.
 *                  If no error has occured then return status will be zero.
 *
 **/
int32_t configure_dpll(void)
{
    pmhalPrcmDpllConfig_t *dpllMpuCfg  = 0U;
    pmhalPrcmDpllConfig_t *dpllIvaCfg  = 0U;
    pmhalPrcmDpllConfig_t *dpllAbeCfg  = 0U;
    pmhalPrcmDpllConfig_t *dpllDdrCfg  = 0U;
    pmhalPrcmDpllConfig_t *dpllGmacCfg = 0U;
    pmhalPrcmDpllConfig_t *dpllDspCfg  = 0U;
#ifdef TDA2XX_BUILD
    uint32_t packageType;
    pmhalPrcmDpllConfig_t *dpllEveCfg = 0U;
#endif
    pmhalPrcmDpllConfig_t *dpllGpuCfg  = 0U;
    pmhalPrcmDpllConfig_t *dpllPcieCfg = 0U;
    int32_t retVal   = 0;
    uint32_t sysFreq = 0;
    uint32_t opp;
    pmhalPrcmSysClkVal_t   sysClkFreq = PMHAL_PRCM_SYSCLK_20_MHZ;

    SBL_PRINTF(TRACE_LOW, __func__);

    sysFreq = PMHALCMGetSysClockFreq();

    if (sysFreq == 20000U)
    {
        sysClkFreq = PMHAL_PRCM_SYSCLK_20_MHZ;
    }
    else if (sysFreq == 19200U)
    {
        sysClkFreq = PMHAL_PRCM_SYSCLK_19_2_MHZ;
        /* PMHAL_PRCM_SYSCLK_19_2_MHZ is not tested in tda2xx*/
    }
    else
    {
        /* To remove MISRA C error */
    }

    PMHALCMSetCdClockMode(PMHAL_PRCM_CD_COREAON,
                          PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                          PM_TIMEOUT_INFINITE);

    /*Configure prcm_dpll_mpu*/
    /* MPU support OPP NOM and OPP OD; But frequency for both is same */
    opp = get_current_opp();

#if defined (TDA2XX_BUILD)
    packageType = HW_RD_FIELD32(
        (SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE +
         CTRL_WKUP_STD_FUSE_DIE_ID_2),
        SBL_TDA2XX_PACKAGE_BIT);

    if ((DPLL_OPP_LOW == opp) &&
        (SBL_TDA2XX_PACKAGE_TYPE_0 != packageType))
    {
        /* SBL_TDA2XX_PACKAGE_TYPE_0 is for 17x17 package,
         * MPU opp Low is supported only for 17x17 package */
        opp = DPLL_OPP_NOM;
    }
#endif

    getDpllStructure(PMHAL_PRCM_DPLL_MPU,
                     sysClkFreq,
                     opp,
                     &dpllMpuCfg);
    retVal = PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_MPU,
                                  dpllMpuCfg,
                                  PM_TIMEOUT_INFINITE);
    if (retVal != PM_SUCCESS)
    {
        SBL_PRINTF(TRACE_HIGH, "\n configure PMHAL_PRCM_DPLL_MPU - error \n");
    }
    if (retVal == PM_SUCCESS)
    {
        /* Note: prcm_dpll_core & prcm_dpll_per are programmed in the
         * SBL_UART_PRCM
         *function*/

        /*Configure prcm_dpll_dsp*/
        opp = get_current_opp();
        getDpllStructure(PMHAL_PRCM_DPLL_DSP, sysClkFreq, opp,
                         &dpllDspCfg);
        retVal = PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_DSP,
                                      dpllDspCfg,
                                      PM_TIMEOUT_INFINITE);
        if (retVal != PM_SUCCESS)
        {
            SBL_PRINTF(TRACE_HIGH, "\n config PMHAL_PRCM_DPLL_DSP - error  \n");
        }
    }
#if defined (TDA2XX_BUILD)
    if (retVal == PM_SUCCESS)
    {
        /*Configure prcm_dpll_eve*/
        getDpllStructure(PMHAL_PRCM_DPLL_EVE, sysClkFreq, opp,
                         &dpllEveCfg);
        retVal = PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_EVE,
                                      dpllEveCfg,
                                      PM_TIMEOUT_INFINITE);
        if (retVal != PM_SUCCESS)
        {
            SBL_PRINTF(TRACE_HIGH,
                       "\n config PMHAL_PRCM_DPLL_EVE - error  \n");
        }
    }
#endif
    if (retVal == PM_SUCCESS)
    {
        /*Configure prcm_dpll_iva*/
        getDpllStructure(PMHAL_PRCM_DPLL_IVA, sysClkFreq, opp,
                         &dpllIvaCfg);
        retVal = PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_IVA,
                                      dpllIvaCfg,
                                      PM_TIMEOUT_INFINITE);
        if (retVal != PM_SUCCESS)
        {
            SBL_PRINTF(TRACE_HIGH,
                       "\n config PMHAL_PRCM_DPLL_IVA - error  \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /*Configure prcm_dpll_gpu*/
        if (opp == DPLL_OPP_HIGH)
        {
#if defined (TDA2XX_BUILD)
            /* GPU doesnot support OPP HIGH; configuring for OPP NOM */
            opp = DPLL_OPP_NOM;
#endif
        }
        getDpllStructure(PMHAL_PRCM_DPLL_GPU,
                         sysClkFreq,
                         opp,
                         &dpllGpuCfg);

        retVal = PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_GPU,
                                      dpllGpuCfg,
                                      PM_TIMEOUT_INFINITE);
        if (retVal != PM_SUCCESS)
        {
            SBL_PRINTF(TRACE_HIGH,
                       "\n config PMHAL_PRCM_DPLL_GPU - error  \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /*Configure prcm_dpll_ddr*/
        getDpllStructure(PMHAL_PRCM_DPLL_DDR,
                         sysClkFreq,
                         DPLL_OPP_NOM,
                         &dpllDdrCfg);
        retVal = PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_DDR,
                                      dpllDdrCfg,
                                      PM_TIMEOUT_INFINITE);
        if (retVal != PM_SUCCESS)
        {
            SBL_PRINTF(TRACE_HIGH,
                       "\n config PMHAL_PRCM_DPLL_DDR - error  \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /*configure prcm_dpll_gmac*/
        getDpllStructure(PMHAL_PRCM_DPLL_GMAC,
                         sysClkFreq,
                         DPLL_OPP_NOM,
                         &dpllGmacCfg);
        retVal = PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_GMAC,
                                      dpllGmacCfg,
                                      PM_TIMEOUT_INFINITE);
        if (retVal != PM_SUCCESS)
        {
            SBL_PRINTF(
                TRACE_HIGH,
                "\n config PMHAL_PRCM_DPLL_GMAC - error  \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /*configure prcm_dpll_abe*/
        /* ADAS use-cases do not use ABE DPLL and this configuration is done to
         * simplify SW maintenance between ADAS and DRI variants
         * Select SYSCLK2 as source
         * Output = 451.584 MHz
         * Provides enough headroom so the McASP can evenly divide this down
         * to multiple different sampling rates as the module does not
         * contain a multiplier.
         */

        HW_WR_FIELD32(
            SOC_CKGEN_PRM_BASE + CM_CLKSEL_ABE_PLL_SYS,
            CM_CLKSEL_ABE_PLL_SYS_CLKSEL,
            CM_CLKSEL_ABE_PLL_SYS_CLKSEL_SEL_SYS_CLK2);

        getDpllStructure(PMHAL_PRCM_DPLL_ABE,
                         sysClkFreq,
                         DPLL_OPP_NOM,
                         &dpllAbeCfg);
        retVal = PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_ABE,
                                      dpllAbeCfg,
                                      PM_TIMEOUT_INFINITE);
        if (retVal != PM_SUCCESS)
        {
            SBL_PRINTF(
                TRACE_HIGH,
                "\n config PMHAL_PRCM_DPLL_ABE - error  \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /*Configure prcm_dpll_pcie_ref*/
        getDpllStructure(PMHAL_PRCM_DPLL_PCIE_REF,
                         sysClkFreq,
                         DPLL_OPP_NOM,
                         &dpllPcieCfg);
        retVal = PMHALCMDpllConfigure(
            PMHAL_PRCM_DPLL_PCIE_REF,
            dpllPcieCfg,
            PM_TIMEOUT_INFINITE);
        if (retVal != PM_SUCCESS)
        {
            SBL_PRINTF(
                TRACE_HIGH,
                "\n config dpll_pcie_cfg - error  \n");
        }
    }
    return retVal;
}

/**
 * \brief       dss_dpll_set_clock_div function program the dss pll to
 *              derive clockouts on High divider clock outs
 *
 *
 * \param       None.
 *
 * \return      error status.If error has occured it returns a non zero value.
 *              If no error has occured then return status will be zero.
 *
 **/
static int32_t dss_dpll_set_clock_div(enum dss_dpll               dpll,
                                      const struct dpll_config_t *dpll_config)
{
    uint32_t regn_start = 8U, regn_end = 1U, regm_start = 20U, regm_end = 9U;
    /* M4 divider */
    uint32_t regm_hsdiv_start = 25U, regm_hsdiv_end = 21U;

    uint32_t base_addr = 0;
    uint32_t regval    = 0;
    uint32_t maskVal, shiftVal;

    switch (dpll)
    {
        case dss_dpll_video1:
            base_addr = SOC_PLLCTRL1_BASE;
            break;

#ifdef TDA2XX_BUILD
        case dss_dpll_video2:
            base_addr = SOC_PLLCTRL2_BASE;
            break;
#endif

        default:
            SBL_PRINTF(TRACE_HIGH, "\n Wrong Video DPLL ");
            break;
    }

    SBL_PRINTF(TRACE_LOW, "\n DSS PLL programming - PLL Automode ");

    /* PLL_AUTOMODE = manual */
    HW_WR_REG32(base_addr + PLL_CONTROL, HW_RD_REG32(
                    base_addr + PLL_CONTROL) & 0xfffffffEU);

    SBL_PRINTF(TRACE_LOW, "\n DSS PLL Programming - Configuration1");
    /* CONFIGURATION1 */
    regval = HW_RD_REG32(base_addr + PLL_CONFIGURATION1);
    /* PLL_REGN */
    maskVal =
        (((((uint32_t) 1) << ((regn_start - regn_end) + 1U)) - 1U) << regn_end);
    shiftVal = regn_end;
    HW_WR_FIELD32_RAW((uint32_t) &regval, maskVal, shiftVal,
                      dpll_config->divider -
                      (uint32_t) 1);
    /* PLL_REGM */
    maskVal =
        (((((uint32_t) 1) << ((regm_start - regm_end) + 1U)) - 1U) << regm_end);
    shiftVal = regm_end;
    HW_WR_FIELD32_RAW((uint32_t) &regval, maskVal, shiftVal,
                      dpll_config->multiplier);
    /* M4_CLOCK_DIV */
    maskVal =
        (((((uint32_t) 1) <<
           ((regm_hsdiv_start - regm_hsdiv_end) + 1U)) - 1U) << regm_hsdiv_end);
    shiftVal = regm_hsdiv_end;
    HW_WR_FIELD32_RAW((uint32_t) &regval, maskVal, shiftVal,
                      (dpll_config->div_h11_clkcfg >
                       0 ? dpll_config->div_h11_clkcfg -
                       1 : 0));
    HW_WR_REG32(base_addr + PLL_CONFIGURATION1, regval);

    SBL_PRINTF(TRACE_LOW, "\n DSS PLL Programming - Configuration2");
    /* CONFIGURATION2 */
    regval = HW_RD_REG32(base_addr + PLL_CONFIGURATION2);

    /* PLL_REFEN */
    maskVal = ((uint32_t) 1 << 13);
    HW_WR_FIELD32_RAW((uint32_t) &regval, maskVal, (uint32_t) 13, (uint32_t) 1);
    /* DSIPHY_CLKINEN */
    maskVal = ((uint32_t) 1 << 14);
    HW_WR_FIELD32_RAW((uint32_t) &regval, maskVal, (uint32_t) 14, (uint32_t) 0);
    /* HSDIVBYPASS */
    maskVal = ((uint32_t) 1 << 20);
    HW_WR_FIELD32_RAW((uint32_t) &regval, maskVal, (uint32_t) 20, (uint32_t) 1);
    /* REF_SYSCLK = sysclk */
    maskVal = ((uint32_t) 3 << 21);
    HW_WR_FIELD32_RAW((uint32_t) &regval, maskVal, (uint32_t) 21, (uint32_t) 3);
    /* CLOCK_EN */
    maskVal = ((uint32_t) 1 << 16);
    HW_WR_FIELD32_RAW((uint32_t) &regval, maskVal, (uint32_t) 16, (uint32_t) 1);

    HW_WR_REG32(base_addr + PLL_CONFIGURATION2, regval);

    /* PLL_GO */
    HW_WR_REG32(base_addr + PLL_GO, HW_RD_REG32(base_addr + PLL_GO) | 0x1U);

    SBL_PRINTF(TRACE_LOW, "\n DSS PLL Programming - PLL GO");
    while ((HW_RD_REG32(base_addr + PLL_GO) & 0x1U) != 0)
    {
        /* Busy Loop */
    }

    SBL_PRINTF(TRACE_LOW, "\n DSS PLL Programming - PLL Status");

    while ((HW_RD_REG32(base_addr + PLL_STATUS) & 0x2U) != 0x00000002U)
    {
        /* Busy Loop */
    }

    SBL_PRINTF(TRACE_LOW, "\n DSS PLL Programming - PLL Configuration2");
    regval = HW_RD_REG32(base_addr + PLL_CONFIGURATION2);
    /* PLL_IDLE */
    maskVal = ((uint32_t) 1);
    HW_WR_FIELD32_RAW((uint32_t) &regval, maskVal, (uint32_t) 0, (uint32_t) 0);
    /* PLL_PLLLPMODE */
    maskVal = ((uint32_t) 1 << 5);
    HW_WR_FIELD32_RAW((uint32_t) &regval, maskVal, (uint32_t) 5, (uint32_t) 0);
    /* PLL_LOWCURRSTBY */
    maskVal = ((uint32_t) 1 << 6);
    HW_WR_FIELD32_RAW((uint32_t) &regval, maskVal, (uint32_t) 6, (uint32_t) 0);
    /* PLL_TIGHTPHASELOCK */
    maskVal = ((uint32_t) 1 << 7);
    HW_WR_FIELD32_RAW((uint32_t) &regval, maskVal, (uint32_t) 7, (uint32_t) 0);
    /* PLL_DRIFTGUARDEN */
    maskVal = ((uint32_t) 1 << 8);
    HW_WR_FIELD32_RAW((uint32_t) &regval, maskVal, (uint32_t) 8, (uint32_t) 0);
    /* PLL_LOCKSEL */
    maskVal = ((uint32_t) 3 << 9);
    HW_WR_FIELD32_RAW((uint32_t) &regval, maskVal, (uint32_t) 9, (uint32_t) 0);
    /* PLL_REFEN */
    maskVal = ((uint32_t) 1 << 13);
    HW_WR_FIELD32_RAW((uint32_t) &regval, maskVal, (uint32_t) 13, (uint32_t) 1);
    /* PHY_CLKINEN */
    maskVal = ((uint32_t) 1 << 14);
    HW_WR_FIELD32_RAW((uint32_t) &regval, maskVal, (uint32_t) 14, (uint32_t) 1);
    /* BYPASSEN */
    maskVal = ((uint32_t) 1 << 15);
    HW_WR_FIELD32_RAW((uint32_t) &regval, maskVal, (uint32_t) 15, (uint32_t) 0);
    /* CLOCK_EN */
    maskVal = ((uint32_t) 1 << 16);
    HW_WR_FIELD32_RAW((uint32_t) &regval, maskVal, (uint32_t) 16, (uint32_t) 1);
    /* CLOCK_PWDN */
    maskVal = ((uint32_t) 1 << 17);
    HW_WR_FIELD32_RAW((uint32_t) &regval, maskVal, (uint32_t) 17, (uint32_t) 0);
    /* PROTO_CLOCK_EN */
    maskVal = ((uint32_t) 1 << 18);
    HW_WR_FIELD32_RAW((uint32_t) &regval, maskVal, (uint32_t) 18, (uint32_t) 1);
    /* PROTO_CLOCK_PWDN */
    maskVal = ((uint32_t) 1 << 19);
    HW_WR_FIELD32_RAW((uint32_t) &regval, maskVal, (uint32_t) 19, (uint32_t) 0);
    /* HSDIVBYPASS */
    maskVal = ((uint32_t) 1 << 20);
    HW_WR_FIELD32_RAW((uint32_t) &regval, maskVal, (uint32_t) 20, (uint32_t) 0);
    HW_WR_REG32(base_addr + PLL_CONFIGURATION2, regval);

    SBL_PRINTF(TRACE_LOW, "\nDSS PLL Programming - completed");

    return 0;
}

/**
 * \brief             program_dss_video_pll function program the DSS
 *                    video1,video2 & hdmi PLL
 *                      DSS PLL Programming steps
 *
 *                        1) Enable PLL programming in CTRL_CORE_DSS_PLL_CONTROL
 *                        2) Enable DSS SCP Interface - DSI_CLK_CTRL.CIO_CLK_ICG
 *                        3) DSI Power enable - DSI_CLK_CTRL.PLL_PWR_CMD
 *                        4) Check for PLL reset status -
 *                           PLL_STATUS.PLLCTRL_RESET_DONE
 *                        5) set the M,N & H-DIV
 *
 *
 * \param           None.
 *
 * \return      error status.If error has occured it returns a non zero value.
 *                  If no error has occured then return status will be zero.
 *
 **/
int32_t program_dss_video_pll(void)
{
    int32_t  retVal;
    uint32_t regval;

    struct dpll_config_t *dpll_video1_cfg = (struct dpll_config_t *) 0;
#ifdef TDA2XX_BUILD
    struct dpll_config_t *dpll_video2_cfg = (struct dpll_config_t *) 0;
#endif
    SBL_PRINTF(TRACE_LOW, __func__);

    /*1) Enable DSS SCP Interface - DSI_CLK_CTRL.CIO_CLK_ICG*/
    regval  = HW_RD_REG32(DSI_CLK_CTRL);
    regval |= 0x00004001U;
    HW_WR_REG32(DSI_CLK_CTRL, regval);

    SBL_PRINTF(TRACE_LOW,
               "\n 1) Enable DSS SCP Interface - DSI_CLK_CTRL.CIO_CLK_ICG");

    /*2) Enable PLL programming in CTRL_CORE_DSS_PLL_CONTROL */
    regval = HW_RD_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_DSS_PLL_CONTROL);
    regval &= ~(0x00000005U);
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_DSS_PLL_CONTROL, regval);

    SBL_PRINTF(TRACE_LOW,
               "\n 2) Enable PLL programming in CTRL_CORE_DSS_PLL_CONTROL");

    /*3) DSI Power enable - DSI_CLK_CTRL.PLL_PWR_CMD */
    regval  = HW_RD_REG32(DSI_CLK_CTRL);
    regval |= 0x80000000U;
    HW_WR_REG32(DSI_CLK_CTRL, regval);

    SBL_PRINTF(TRACE_LOW, "\n 3) DSI Power enable - DSI_CLK_CTRL.PLL_PWR_CMD");

    /*4) Check for PLL reset status - PLL_STATUS.PLLCTRL_RESET_DONE*/
    while ((HW_RD_REG32(DSI_PLL_STATUS) & 0x1U) != 0x1U)
    {
        /* Busy Loop */
    }

    SBL_PRINTF(
        TRACE_LOW,
        "\n 4) Check for PLL reset status - PLL_STATUS.PLLCTRL_RESET_DONE");

    /*DSS video1 PLL Programming*/

    dpll_video1_cfg = &dpll_video1_cfg_opp100_20;

    retVal = dss_dpll_set_clock_div(dss_dpll_video1,
                                    dpll_video1_cfg);
    if (retVal != PM_SUCCESS)
    {
        SBL_PRINTF(TRACE_HIGH, "\n dss dpll video1 -lock error  \n");
    }
    if (retVal == PM_SUCCESS)
    {
        SBL_PRINTF(TRACE_LOW, "\n DSS video1 PLL Programming ");
#ifdef TDA2XX_BUILD

        /*1) Enable DSS SCP Interface - DSI_CLK_CTRL.CIO_CLK_ICG*/
        regval  = HW_RD_REG32(DSI2_CLK_CTRL);
        regval |= 0x00004001U;
        HW_WR_REG32(DSI2_CLK_CTRL, regval);

        SBL_PRINTF(TRACE_LOW,
                   "\n 1) Enable DSS SCP Interface - DSI_CLK_CTRL.CIO_CLK_ICG");

        /*2) Enable PLL programming in CTRL_CORE_DSS_PLL_CONTROL */
        regval = HW_RD_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
            CTRL_CORE_DSS_PLL_CONTROL);
        regval &= ~(0x00000002U);
        HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                    CTRL_CORE_DSS_PLL_CONTROL, regval);

        SBL_PRINTF(TRACE_LOW,
                   "\n 2) Enable PLL programming in CTRL_CORE_DSS_PLL_CONTROL");

        /*3) DSI Power enable - DSI_CLK_CTRL.PLL_PWR_CMD */
        regval  = HW_RD_REG32(DSI2_CLK_CTRL);
        regval |= 0x80000000U;
        HW_WR_REG32(DSI2_CLK_CTRL, regval);

        SBL_PRINTF(TRACE_LOW,
                   "\n 3) DSI Power enable - DSI_CLK_CTRL.PLL_PWR_CMD");

        /*4) Check for PLL reset status - PLL_STATUS.PLLCTRL_RESET_DONE*/
        while ((HW_RD_REG32(DSI2_PLL_STATUS) & 0x1U) != 0x1U)
        {
            /* Busy Loop */
        }

        SBL_PRINTF(
            TRACE_LOW,
            "\n 4) Check for PLL reset status - PLL_STATUS.PLLCTRL_RESET_DONE");

        /*DSS video2 PLL Programming*/

        dpll_video2_cfg = &dpll_video2_cfg_opp100_20;

        retVal = dss_dpll_set_clock_div(dss_dpll_video2,
                                        dpll_video2_cfg);
        if (retVal != PM_SUCCESS)
        {
            SBL_PRINTF(TRACE_HIGH, "\n dss dpll video2 -lock error  \n");
        }
        else
        {
            SBL_PRINTF(TRACE_LOW, "\n DSS video2 PLL Programming ");
        }
#endif
    }
    return retVal;
}

/**
 * \brief   This is the wrapper function for configuring Power domains.
 *
 *
 * \param           None.
 *
 * \return      error status.If error has occured it returns a non zero value.
 *                  If no error has occured then return status will be zero.
 *
 **/
int32_t ConfigPowerDomains(void)
{
    int32_t  retVal   = 0;
    uint32_t tblIndex = 0U;

    for (tblIndex = 0U;
         tblIndex < NUM_ENTRIES_POWER_DOMAIN_STATE_TABLE;
         tblIndex++)
    {
        retVal += PMHALPdmSetPDState(
            gPDStateTable[tblIndex].domainId,
            gPDStateTable[tblIndex].powerDomainState,
            PM_TIMEOUT_NOWAIT);
    }
    return retVal;
}

/**
 * \brief           configure_clock_domains function wake-up the clock domains &
 *                  check for functional clock are gated.
 *                   If not log error message & returns
 *
 *
 * \param           None.
 *
 * \return      error status.If error has occured it returns a non zero value.
 *                  If no error has occured then return status will be zero.
 *
 **/
int32_t configure_clock_domains(void)
{
    int32_t retVal = 0;

    /*TODO: verify the sequence to wake-up clock domain*/

    SBL_PRINTF(TRACE_LOW, __func__);

    /*Note: prcm_cd_l4per wake-up handled in SBL_UART_PRCM*/

    /*Force Wake-up clock domain l3init*/
    retVal += PMHALCMSetCdClockMode(PMHAL_PRCM_CD_L3INIT,
                                    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                    PM_TIMEOUT_INFINITE);

    /*Force Wake-up clock domain emif*/
    retVal += PMHALCMSetCdClockMode(PMHAL_PRCM_CD_EMIF,
                                    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                    PM_TIMEOUT_INFINITE);

    /*Force Wake-up clock domain l4cfg*/
    retVal += PMHALCMSetCdClockMode(PMHAL_PRCM_CD_L4CFG,
                                    PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP,
                                    PM_TIMEOUT_INFINITE);

    /*Force Wake-up clock domain dma*/
    retVal += PMHALCMSetCdClockMode(PMHAL_PRCM_CD_DMA,
                                    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                    PM_TIMEOUT_INFINITE);

    /*Force Wake-up clock domain l3main1*/
    retVal += PMHALCMSetCdClockMode(PMHAL_PRCM_CD_L3MAIN1,
                                    PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                                    PM_TIMEOUT_INFINITE);

    /*Force Wake-up clock domain cam*/
    retVal += PMHALCMSetCdClockMode(PMHAL_PRCM_CD_CAM,
                                    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                    PM_TIMEOUT_INFINITE);

    /*Force wake-up clock domain iva*/
    retVal += PMHALCMSetCdClockMode(PMHAL_PRCM_CD_IVA,
                                    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                    PM_TIMEOUT_INFINITE);

    /*Force Wake-up clock domain dss*/
    retVal += PMHALCMSetCdClockMode(PMHAL_PRCM_CD_DSS,
                                    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                    PM_TIMEOUT_INFINITE);
#ifdef TDA2EX_BUILD
    /*Force Wake-up clock domain l4per*/
    retVal += PMHALCMSetCdClockMode(PMHAL_PRCM_CD_L4PER,
                                    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                    PM_TIMEOUT_INFINITE);
#endif

    /*Force Wake-up clock domain l4per2*/
    retVal += PMHALCMSetCdClockMode(PMHAL_PRCM_CD_L4PER2,
                                    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                    PM_TIMEOUT_INFINITE);

    /*Force Wake-up clock domain l4per3*/
    retVal +=
        PMHALCMSetCdClockMode(PMHAL_PRCM_CD_L4PER3,
                              PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                              PM_TIMEOUT_INFINITE);

    /*Force Wake-up clock domain gmac*/
    retVal +=
        PMHALCMSetCdClockMode(PMHAL_PRCM_CD_GMAC,
                              PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                              PM_TIMEOUT_INFINITE);

    /*Force Wake-up clock domain mpu*/
    retVal += PMHALCMSetCdClockMode(PMHAL_PRCM_CD_MPU,
                                    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                    PM_TIMEOUT_INFINITE);

    /*Force Wake-up clock domain vpe*/
    retVal += PMHALCMSetCdClockMode(PMHAL_PRCM_CD_VPE,
                                    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                    PM_TIMEOUT_INFINITE);

    /*Force Wake-up clock domain wkupaon*/
    retVal += PMHALCMSetCdClockMode(PMHAL_PRCM_CD_WKUPAON,
                                    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                    PM_TIMEOUT_INFINITE);

    /*Force Wake-up clock domain pcie*/
    retVal += PMHALCMSetCdClockMode(PMHAL_PRCM_CD_PCIE,
                                    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                    PM_TIMEOUT_INFINITE);

    /*Force Wake-up clock domain ipu*/
    retVal += PMHALCMSetCdClockMode(PMHAL_PRCM_CD_IPU,
                                    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                    PM_TIMEOUT_INFINITE);

    /* Force Wake-up clock domain EMU, this is required to ensure DSP powers
     * down correctly when DSP Idle is executed
     */
    retVal += PMHALCMSetCdClockMode(PMHAL_PRCM_CD_EMU,
                                    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                    PM_TIMEOUT_NOWAIT);

    return retVal;
}

/**
 * \brief            enable_vip_dss function set the video subsystem module mode
 *                   to Auto.Check for error status & log the error message.
 *
 * \param           None.
 *
 * \return      error status.If error has occured it returns a non zero value.
 *                  If no error has occured then return status will be zero.
 *
 **/
int32_t enable_vip_dss(void)
{
    int32_t retVal = PM_SUCCESS;

    SBL_PRINTF(TRACE_LOW, __func__);

    /*Enable the module - vip1*/
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_VIP1,
                                PMHAL_PRCM_MODULE_MODE_AUTO,
                                PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n vip1 module enable - Error \n");
    }
#ifdef TDA2XX_BUILD
    if (retVal == PM_SUCCESS)
    {
        /*Enable the module - vip2*/
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_VIP2,
                                    PMHAL_PRCM_MODULE_MODE_AUTO,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n vip2 module enable - Error \n");
        }

        if (retVal == PM_SUCCESS)
        {
            /*Enable the module - vip3*/
            retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_VIP3,
                                        PMHAL_PRCM_MODULE_MODE_AUTO,
                                        PM_TIMEOUT_INFINITE);

            if (retVal != PM_SUCCESS)
            {
                SBL_PRINTF(TRACE_HIGH, "\n vip3 module enable - Error \n");
            }
        }
    }
#endif
    if (retVal == PM_SUCCESS)
    {
        /*MMR Enable*/
        PlatformUnlockControlIODSS();

        PMHALCMModuleEnableAllOptClock(PMHAL_PRCM_MOD_DSS);

        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_DSS,
                                    PMHAL_PRCM_MODULE_MODE_ENABLED,
                                    PM_TIMEOUT_INFINITE);

        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n dss module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /*Enable the module - vpe*/
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_VPE,
                                    PMHAL_PRCM_MODULE_MODE_AUTO,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n vpe module enable - Error \n");
        }
    }

    return retVal;
}

/**
 * \brief            enable_ocmc function set the OCMC mode to Auto.
 *                      check for error status & log the error message.
 *
 * \param           None.
 *
 * \return      error status.If error has occured it returns a non zero value.
 *                  If no error has occured then return status will be zero.
 *
 **/
int32_t enable_ocmc(void)
{
    int32_t retVal = PM_SUCCESS;

    SBL_PRINTF(TRACE_LOW, __func__);

    /*Enable the module - ocmc_ram1*/
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_OCMC_RAM1,
                                PMHAL_PRCM_MODULE_MODE_AUTO,
                                PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n ocmc_ram1 module enable - Error \n");
    }
#ifdef TDA2XX_BUILD
    if (retVal == PM_SUCCESS)
    {
        /*Enable the module - ocmc_ram2*/
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_OCMC_RAM2,
                                    PMHAL_PRCM_MODULE_MODE_AUTO,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n ocmc_ram2 module enable - Error \n");
        }
        if (retVal == PM_SUCCESS)
        {
            /*Enable the module - ocmc_ram3*/
            retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_OCMC_RAM3,
                                        PMHAL_PRCM_MODULE_MODE_AUTO,
                                        PM_TIMEOUT_INFINITE);
            if (PM_SUCCESS != retVal)
            {
                SBL_PRINTF(TRACE_HIGH, "\n ocmc_ram3 module enable - Error \n");
            }
        }
        if (retVal == PM_SUCCESS)
        {
            /*Enable the module - ocmc_rom*/
            retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_OCMC_ROM,
                                        PMHAL_PRCM_MODULE_MODE_AUTO,
                                        PM_TIMEOUT_INFINITE);
            if (PM_SUCCESS != retVal)
            {
                SBL_PRINTF(TRACE_HIGH, "\n ocmc_rom module enable - Error \n");
            }
        }
    }
#endif
    return retVal;
}

/**
 * \brief       enable_serial_per function set the serial peripheral module
 *              mode to Auto or module_enable.
 *              check for error status & log the error message.
 *
 * \param       None.
 *
 * \return      error status.If error has occured it returns a non zero value.
 *                  If no error has occured then return status will be zero.
 *
 **/
int32_t enable_serial_per(void)
{
    int32_t retVal = PM_SUCCESS;

    SBL_PRINTF(TRACE_LOW, __func__);

    /*Note: UART1 module enable handled in SBL_UART_PRCM*/

    /*Enable the module - mcspi1*/
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_MCSPI1,
                                PMHAL_PRCM_MODULE_MODE_ENABLED,
                                PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n mcspi1 module enable - Error \n");
    }
    if (retVal == PM_SUCCESS)
    {
        /*Enable the module - i2c2*/
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_I2C2,
                                    PMHAL_PRCM_MODULE_MODE_ENABLED,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n i2c2 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /*Enable the module - i2c3*/
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_I2C3,
                                    PMHAL_PRCM_MODULE_MODE_ENABLED,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n i2c3 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /*Enable the module - i2c4*/
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_I2C4,
                                    PMHAL_PRCM_MODULE_MODE_ENABLED,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n i2c4 module enable - Error \n");
        }
    }
#ifdef MCASP1_ENABLE
    if (retVal == PM_SUCCESS)
    {
        /*Enable the module - mcaps1*/
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_MCASP1,
                                    PMHAL_PRCM_MODULE_MODE_ENABLED,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF("\n mcasp1 module enable - Error \n");
        }
    }
#endif
    if (retVal == PM_SUCCESS)
    {
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_QSPI,
                                    PMHAL_PRCM_MODULE_MODE_ENABLED,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n qspi module enable - Error \n");
        }
    }

    return retVal;
}

/**
 * \brief       enable_core function set the MPU to Auto or module_enable.
 *              check for error status & log the error message.
 *
 * \param       None.
 *
 * \return      error status.If error has occured it returns a non zero value.
 *              If no error has occured then return status will be zero.
 *
 **/
int32_t enable_core(void)
{
    int32_t retVal = PM_SUCCESS;
    /* Enable the module - mpu */
    /* Enable all modules' optional clocks */
    PMHALCMModuleEnableAllOptClock(PMHAL_PRCM_MOD_MPU);

    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_MPU,
                                PMHAL_PRCM_MODULE_MODE_ENABLED,
                                PM_TIMEOUT_INFINITE);

    return retVal;
}

/**
 * \brief       enable_mem function set the memory subsystem to Auto or
 *              module_enable state.
 *              check for error status & log the error message.
 *
 * \param       None.
 *
 * \return      error status.If error has occured it returns a non zero value.
 *              If no error has occured then return status will be zero.
 *
 **/
int32_t enable_mem(void)
{
    int32_t retVal = PM_SUCCESS;

    SBL_PRINTF(TRACE_LOW, __func__);

    /*Enable DMA TPTC1*/
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_TPTC1,
                                PMHAL_PRCM_MODULE_MODE_AUTO,
                                PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n dma tptc1 enable - Error \n");
    }
    if (retVal == PM_SUCCESS)
    {
        /*Enable DMA TPTC2*/
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_TPTC2,
                                    PMHAL_PRCM_MODULE_MODE_AUTO,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n dma tptc2 enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /*Enable DMA TPCC*/
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_TPCC,
                                    PMHAL_PRCM_MODULE_MODE_AUTO,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n dma tpcc enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /*Enable the module - dmm*/
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_DMM,
                                    PMHAL_PRCM_MODULE_MODE_AUTO,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n dmm module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /*Enable the module - emif1*/
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_EMIF1,
                                    PMHAL_PRCM_MODULE_MODE_AUTO,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n emif1 module enable - Error \n");
        }
    }

#ifdef TDA2XX_BUILD
    if (retVal == PM_SUCCESS)
    {
#if (EMIF_MODE != SINGLE_EMIF_256MB)
        /*Enable the module - emif2 */
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_EMIF2,
                                    PMHAL_PRCM_MODULE_MODE_AUTO,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n emif2 module enable - Error \n");
        }
#else
        /* Set the power down time to 7 cycles */
        HW_WR_FIELD32(
            SOC_EMIF2_CONF_REGS_BASE +
            EMIF_POWER_MANAGEMENT_CONTROL,
            EMIF_POWER_MANAGEMENT_CONTROL_PD_TIM,
            0x7);
        /* Set the EMIF to power down mode */
        HW_WR_FIELD32(
            SOC_EMIF2_CONF_REGS_BASE +
            EMIF_POWER_MANAGEMENT_CONTROL,
            EMIF_POWER_MANAGEMENT_CONTROL_LP_MODE,
            0x4);
        /* Write the PD down time in the EMIF power managment
         *shadow register */
        HW_WR_REG32(SOC_EMIF2_CONF_REGS_BASE +
                    EMIF_POWER_MANAGEMENT_CONTROL_SHADOW,
                    0x7000);

        /*Disable the module - emif2 */
        retVal = PMHALModuleModeSet(
            PMHAL_PRCM_MOD_EMIF2,
            PMHAL_PRCM_MODULE_MODE_DISABLED,
            PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n emif2 module disable - Error \n");
        }
#endif
    }
#endif

    if (retVal == PM_SUCCESS)
    {
        /*Enable the module - emif_ocp_fw*/
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_EMIF_OCP_FW,
                                    PMHAL_PRCM_MODULE_MODE_AUTO,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n emip_ocp_fw module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /*Enable the module - gpmc*/
        retVal = PMHALModuleModeSet(
            PMHAL_PRCM_MOD_GPMC,
            PMHAL_PRCM_MODULE_MODE_AUTO,
            PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n gpmc module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /*Enable the module - mmu_edma*/
        retVal = PMHALModuleModeSet(
            PMHAL_PRCM_MOD_MMU_EDMA,
            PMHAL_PRCM_MODULE_MODE_AUTO,
            PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n mmu module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /*Enable the module - mmu_pciess*/
        retVal = PMHALModuleModeSet(
            PMHAL_PRCM_MOD_MMU_PCIESS,
            PMHAL_PRCM_MODULE_MODE_AUTO,
            PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n pciess module enable - Error \n");
        }
    }
    return retVal;
}

/**
 * \brief       enable_interconnect function set the L3 & L4 to auto or
 *              module_enable state.
 *              It check for error status & log the error message.
 *
 * \param       None.
 *
 * \return      error status.If error has occured it returns a non zero value.
 *                  If no error has occured then return status will be zero.
 *
 **/
int32_t enable_interconnect(void)
{
    int32_t retVal = PM_SUCCESS;

    SBL_PRINTF(TRACE_LOW, __func__);

    /*Enable the module - l3_main_2*/
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_L3_MAIN_2,
                                PMHAL_PRCM_MODULE_MODE_AUTO,
                                PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n prcm_l3_main_2 module enable - Error \n");
    }
    if (retVal == PM_SUCCESS)
    {
        /*Enable the module - l3_main_1*/
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_L3_MAIN_1,
                                    PMHAL_PRCM_MODULE_MODE_AUTO,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_l3_main_1 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /*Enable the module - l4_cfg*/
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_L4_CFG,
                                    PMHAL_PRCM_MODULE_MODE_AUTO,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_l4_cfg module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /*Enable the module - l4_per2*/
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_L4_PER2,
                                    PMHAL_PRCM_MODULE_MODE_AUTO,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_l4_per2 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /*Enable the module - l4_per3*/
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_L4_PER3,
                                    PMHAL_PRCM_MODULE_MODE_AUTO,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_l4_per3 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /*Enable the module - l4_per1*/
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_L4_PER1,
                                    PMHAL_PRCM_MODULE_MODE_AUTO,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_l4_per1 module enable - Error \n");
        }
    }
    return retVal;
}

/**
 * \brief       enable_iva function set the VPC & IVA to auto or
 *              module_enable state.
 *              It check for error status & log the error message.
 *
 * \param       None.
 *
 * \return      error status.If error has occured it returns a non zero value.
 *              If no error has occured then return status will be zero.
 *
 **/
int32_t enable_iva(void)
{
    int32_t retVal = PM_SUCCESS;

    SBL_PRINTF(TRACE_LOW, __func__);

    /*Enable the module - vcp1*/
    /* Enable all modules' optional clocks */
    PMHALCMModuleEnableAllOptClock(PMHAL_PRCM_MOD_VCP1);
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_VCP1,
                                PMHAL_PRCM_MODULE_MODE_ENABLED,
                                PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n prcm_vcp1 module enable - Error \n");
    }
    if (retVal == PM_SUCCESS)
    {
        /*Enable the module - vcp2*/
        /* Enable all modules' optional clocks */
        PMHALCMModuleEnableAllOptClock(PMHAL_PRCM_MOD_VCP2);
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_VCP2,
                                    PMHAL_PRCM_MODULE_MODE_ENABLED,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_vcp2 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /*Enable the module - iva*/
        /* Enable all modules' optional clocks */
        PMHALCMModuleEnableAllOptClock(PMHAL_PRCM_MOD_IVA);
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_IVA,
                                    PMHAL_PRCM_MODULE_MODE_ENABLED,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_iva module enable - Error \n");
        }
    }

    return retVal;
}

/**
 * \brief       enable_ipc function set the mailbox & spinlock modules to
 *              auto or module_enable state.
 *              It check for error status & log the error message.
 *
 * \param       None.
 *
 * \return      error status.If error has occured it returns a non zero value.
 *                  If no error has occured then return status will be zero.
 *
 */
int32_t enable_ipc(void)
{
    int32_t retVal = PM_SUCCESS;

    SBL_PRINTF(TRACE_LOW, __func__);

    /* Enable the module - mailbox1 */
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_MAILBOX1,
                                PMHAL_PRCM_MODULE_MODE_AUTO,
                                PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n prcm_mailbox1 module enable - Error \n");
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - mailbox10 */
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_MAILBOX10,
                                    PMHAL_PRCM_MODULE_MODE_AUTO,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_mailbox10 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - mailbox11 */
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_MAILBOX11,
                                    PMHAL_PRCM_MODULE_MODE_AUTO,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_mailbox11 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - mailbox12 */
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_MAILBOX12,
                                    PMHAL_PRCM_MODULE_MODE_AUTO,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_mailbox12 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - mailbox13 */
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_MAILBOX13,
                                    PMHAL_PRCM_MODULE_MODE_AUTO,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_mailbox13 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - mailbox2 */
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_MAILBOX2,
                                    PMHAL_PRCM_MODULE_MODE_AUTO,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_mailbox2 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - mailbox3 */
        retVal = PMHALModuleModeSet(
            PMHAL_PRCM_MOD_MAILBOX3,
            PMHAL_PRCM_MODULE_MODE_AUTO,
            PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_mailbox3 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - mailbox4 */
        retVal = PMHALModuleModeSet(
            PMHAL_PRCM_MOD_MAILBOX4,
            PMHAL_PRCM_MODULE_MODE_AUTO,
            PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_mailbox4 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - mailbox5 */
        retVal = PMHALModuleModeSet(
            PMHAL_PRCM_MOD_MAILBOX5,
            PMHAL_PRCM_MODULE_MODE_AUTO,
            PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_mailbox5 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - mailbox6 */
        retVal = PMHALModuleModeSet(
            PMHAL_PRCM_MOD_MAILBOX6,
            PMHAL_PRCM_MODULE_MODE_AUTO,
            PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_mailbox6 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - mailbox7 */
        retVal = PMHALModuleModeSet(
            PMHAL_PRCM_MOD_MAILBOX7,
            PMHAL_PRCM_MODULE_MODE_AUTO,
            PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_mailbox7 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - mailbox8
        **/
        retVal = PMHALModuleModeSet(
            PMHAL_PRCM_MOD_MAILBOX8,
            PMHAL_PRCM_MODULE_MODE_AUTO,
            PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_mailbox8 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - mailbox9 */
        retVal = PMHALModuleModeSet(
            PMHAL_PRCM_MOD_MAILBOX9,
            PMHAL_PRCM_MODULE_MODE_AUTO,
            PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_mailbox9 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - spinlock */
        retVal = PMHALModuleModeSet(
            PMHAL_PRCM_MOD_SPINLOCK,
            PMHAL_PRCM_MODULE_MODE_AUTO,
            PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_spinlock module enable - Error \n");
        }
    }

    return retVal;
}

/**
 * \brief       enable_timer function set the timer modules to  auto or
 *              module_enable state.
 *              It check for error status & log the error message.
 *
 * \param       None.
 *
 * \return      error status.If error has occured it returns a non zero value.
 *                  If no error has occured then return status will be zero.
 *
 **/
int32_t enable_timer(void)
{
    int32_t retVal = PM_SUCCESS;

    SBL_PRINTF(TRACE_LOW, __func__);

    /* Enable the module - timer5 */
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_TIMER5,
                                PMHAL_PRCM_MODULE_MODE_ENABLED,
                                PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n prcm_timer5 module enable - Error \n");
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - timer6 */
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_TIMER6,
                                    PMHAL_PRCM_MODULE_MODE_ENABLED,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_timer6 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - timer7 */
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_TIMER7,
                                    PMHAL_PRCM_MODULE_MODE_ENABLED,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_timer7 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - timer8 */
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_TIMER8,
                                    PMHAL_PRCM_MODULE_MODE_ENABLED,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_timer8 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - timer13 */
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_TIMER13,
                                    PMHAL_PRCM_MODULE_MODE_ENABLED,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_timer13 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - timer14 */
        retVal = PMHALModuleModeSet(
            PMHAL_PRCM_MOD_TIMER14,
            PMHAL_PRCM_MODULE_MODE_ENABLED,
            PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_timer14 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - timer15 */
        retVal = PMHALModuleModeSet(
            PMHAL_PRCM_MOD_TIMER15,
            PMHAL_PRCM_MODULE_MODE_ENABLED,
            PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_timer15 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - timer16 */
        retVal = PMHALModuleModeSet(
            PMHAL_PRCM_MOD_TIMER16,
            PMHAL_PRCM_MODULE_MODE_ENABLED,
            PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_timer16 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - timer10 */
        retVal = PMHALModuleModeSet(
            PMHAL_PRCM_MOD_TIMER10,
            PMHAL_PRCM_MODULE_MODE_ENABLED,
            PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_timer10 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - timer11 */
        retVal = PMHALModuleModeSet(
            PMHAL_PRCM_MOD_TIMER11,
            PMHAL_PRCM_MODULE_MODE_ENABLED,
            PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_timer11 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - timer2 */
        retVal = PMHALModuleModeSet(
            PMHAL_PRCM_MOD_TIMER2,
            PMHAL_PRCM_MODULE_MODE_ENABLED,
            PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_timer2 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - timer3 */
        retVal = PMHALModuleModeSet(
            PMHAL_PRCM_MOD_TIMER3,
            PMHAL_PRCM_MODULE_MODE_ENABLED,
            PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_timer3 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - timer4 */
        retVal = PMHALModuleModeSet(
            PMHAL_PRCM_MOD_TIMER4,
            PMHAL_PRCM_MODULE_MODE_ENABLED,
            PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_timer4 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - timer9 */
        retVal = PMHALModuleModeSet(
            PMHAL_PRCM_MOD_TIMER9,
            PMHAL_PRCM_MODULE_MODE_ENABLED,
            PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_timer9 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - timer1 */
        retVal = PMHALModuleModeSet(
            PMHAL_PRCM_MOD_TIMER1,
            PMHAL_PRCM_MODULE_MODE_ENABLED,
            PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_timer1 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - timer12 */
        retVal = PMHALModuleModeSet(
            PMHAL_PRCM_MOD_TIMER12,
            PMHAL_PRCM_MODULE_MODE_AUTO,
            PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_timer12 module enable - Error \n");
        }
    }
    if (retVal == PM_SUCCESS)
    {
        /* Enable the module - wd_timer2 */
        retVal = PMHALModuleModeSet(
            PMHAL_PRCM_MOD_WD_TIMER2,
            PMHAL_PRCM_MODULE_MODE_ENABLED,
            PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            SBL_PRINTF(TRACE_HIGH, "\n prcm_wd_timer2 module enable - Error \n");
        }
    }
    return retVal;
}

/**
 * \brief       enable_per function set the mmc & gpio modules to  auto or
 *              module_enable state.
 *              It check for error status & log the error message.
 *
 * \param       None.
 *
 * \return      error status.If error has occured it returns a non zero value.
 *                  If no error has occured then return status will be zero.
 *
 **/
int32_t enable_per(void)
{
    int32_t retVal = PM_SUCCESS;

    SBL_PRINTF(TRACE_LOW, __func__);

    /*Todo - replace with PMHAL_PRCM_CM function*/

    /*MMC1- CM_L3INIT_MMC1_CLKCTRL */

    /* Select the mux and divider .*/
    PMHALCMMuxParentSelect(PMHAL_PRCM_MUX_MMC1_FCLK_MUX, PMHAL_PRCM_DPLL_PER);
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_MMC1_FCLK, (uint32_t) 2);

    /* Enable the module - mmc1 */
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_MMC1,
                                PMHAL_PRCM_MODULE_MODE_ENABLED,
                                PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n prcm_mmc1 module enable - Error \n");
    }

    /* Enable the module - gpio1 */
    /* Enable all modules' optional clocks */
    PMHALCMModuleEnableAllOptClock(PMHAL_PRCM_MOD_GPIO1);
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_GPIO1,
                                PMHAL_PRCM_MODULE_MODE_AUTO,
                                PM_TIMEOUT_INFINITE);

    /* Enable the module - gpio2 */
    /* Enable all modules' optional clocks */
    PMHALCMModuleEnableAllOptClock(PMHAL_PRCM_MOD_GPIO2);
    PMHALModuleModeSet(PMHAL_PRCM_MOD_GPIO2,
                       PMHAL_PRCM_MODULE_MODE_AUTO,
                       PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n prcm_gpior2 module enable - Error \n");
    }

    /* Enable the module - gpio3 */
    /* Enable all modules' optional clocks */
    PMHALCMModuleEnableAllOptClock(PMHAL_PRCM_MOD_GPIO3);
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_GPIO3,
                                PMHAL_PRCM_MODULE_MODE_AUTO,
                                PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n prcm_gpio3 module enable - Error \n");
    }

    /* Enable the module - gpio4 */
    /* Enable all modules' optional clocks */
    PMHALCMModuleEnableAllOptClock(PMHAL_PRCM_MOD_GPIO4);
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_GPIO4,
                                PMHAL_PRCM_MODULE_MODE_AUTO,
                                PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n prcm_gpio4 module enable - Error \n");
    }

    /* Enable the module - gpio5 */
    /* Enable all modules' optional clocks */
    PMHALCMModuleEnableAllOptClock(PMHAL_PRCM_MOD_GPIO5);
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_GPIO5,
                                PMHAL_PRCM_MODULE_MODE_AUTO,
                                PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n prcm_gpio5 module enable - Error \n");
    }

    /* Enable the module - gpio6 */
    /* Enable all modules' optional clocks */
    PMHALCMModuleEnableAllOptClock(PMHAL_PRCM_MOD_GPIO6);
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_GPIO6,
                                PMHAL_PRCM_MODULE_MODE_AUTO,
                                PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n prcm_gpio6 module enable - Error \n");
    }

    /* Enable the module - gpio7 */
    /* Enable all modules' optional clocks */
    PMHALCMModuleEnableAllOptClock(PMHAL_PRCM_MOD_GPIO7);
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_GPIO7,
                                PMHAL_PRCM_MODULE_MODE_AUTO,
                                PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n prcm_gpio7 module enable - Error \n");
    }

    /* Enable the module - gpio8 */
    /* Enable all modules' optional clocks */
    PMHALCMModuleEnableAllOptClock(PMHAL_PRCM_MOD_GPIO8);
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_GPIO8,
                                PMHAL_PRCM_MODULE_MODE_AUTO,
                                PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n prcm_gpio8 module enable - Error \n");
    }

    return retVal;
}

/**
 * \brief         enable_per function set the mmc & gpio modules to  auto or
 *                module_enable state.
 *                It check for error status & log the error message.
 *
 * \param           None.
 *
 * \return      error status.If error has occured it returns a non zero value.
 *                  If no error has occured then return status will be zero.
 *
 **/
int32_t enable_cpgmac(void)
{
    int32_t retVal = PM_SUCCESS;

    SBL_PRINTF(TRACE_LOW, __func__);

    /* Enable the module - cpgmac */
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_CPGMAC,
                                PMHAL_PRCM_MODULE_MODE_ENABLED,
                                PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n prcm_cpgmac module enable - Error \n");
    }

    return retVal;
}

/**
 * \brief       enable_i2c1 function to enable i2c1 peripheral module
 *              To log the debug messages it get called at the start-up.
 *
 * \param           None.
 *
 * \return      error status.If error has occured it returns a non zero value.
 *                  If no error has occured then return status will be zero.
 *
 **/
int32_t enable_i2c1(void)
{
    int32_t retVal = PM_SUCCESS;

    SBL_PRINTF(TRACE_LOW, __func__);

    /* Enable the module - i2c1 */
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_I2C1,
                                PMHAL_PRCM_MODULE_MODE_ENABLED,
                                PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != retVal)
    {
        SBL_PRINTF(TRACE_HIGH, "\n prcm_i2c1 module enable - Error \n");
    }

    return retVal;
}

/**
 * \brief       SBL_UART_PRCM function program dpll_per, wake-up l4_per
 *              clock domain & enable uart1 peripheral module
 *              To log the debug messages it get called at the start-up.
 *
 * \param           None.
 *
 * \return      error status.If error has occured it returns a non zero value.
 *                  If no error has occured then return status will be zero.
 *
 **/
int32_t SBL_UART_PRCM(UART_INST_t num)
{
    pmhalPrcmDpllConfig_t *dpllCoreCfg;
    pmhalPrcmDpllConfig_t *dpllPerCfg;
    uint32_t sysFreq = 0;
    int32_t retVal   = PM_SUCCESS;
    pmhalPrcmSysClkVal_t   sysClkFreq = PMHAL_PRCM_SYSCLK_20_MHZ;

    /* get system clock frequency */
    sysFreq = PMHALCMGetSysClockFreq();

    if (sysFreq == 20000U)
    {
        sysClkFreq = PMHAL_PRCM_SYSCLK_20_MHZ;
    }
    else if (sysFreq == 19200U)
    {
        sysClkFreq = PMHAL_PRCM_SYSCLK_19_2_MHZ;
        /* PMHAL_PRCM_SYSCLK_19_2_MHZ is not tested in tda2xx*/
    }
    else
    {
        /* To remove MISRA C error */
    }

    /*Configure DPLL_CORE - L4_PER_L3_GICLK - UART1 Interface clock*/
    /*Configure prcm_dpll_core*/
    getDpllStructure(PMHAL_PRCM_DPLL_CORE,
                     sysClkFreq,
                     DPLL_OPP_NOM,
                     &dpllCoreCfg);

    /* This selects CORE_IPU_ISS_BOOST_CLK as IPU functional clock */
    PMHALCMMuxParentSelect(PMHAL_PRCM_MUX_IPU1_GFCLK_MUX, PMHAL_PRCM_DPLL_CORE);

    /* Config DPLL_CORE*/
    retVal = PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_CORE,
                                  dpllCoreCfg,
                                  PM_TIMEOUT_INFINITE);

    /*Configure DPLL_PER - UART1_GFCLK - UART1 Functional clock*/
    /*Configure prcm_dpll_per*/
    getDpllStructure(PMHAL_PRCM_DPLL_PER,
                     sysClkFreq,
                     DPLL_OPP_NOM,
                     &dpllPerCfg);

    /* Config DPLL_PER */
    retVal = PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_PER,
                                  dpllPerCfg,
                                  PM_TIMEOUT_INFINITE);
    if (retVal != PM_SUCCESS)
    {
        SBL_PRINTF(TRACE_HIGH, "\n DPLL_PER PMHALCMDpllConfigure - Error \n");
    }

    /*Force Wake-up clock domain l4per*/
    retVal = PMHALCMSetCdClockMode(PMHAL_PRCM_CD_L4PER2,
                                   PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                   PM_TIMEOUT_INFINITE);

    if (retVal != PM_SUCCESS)
    {
        SBL_PRINTF(TRACE_HIGH, "\n L4PER2 PMHALCMSetCdClockMode - Error \n");
    }

    /*Enable the module - uart*/
    switch (num)
    {
        case UART1_INST:
            retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_UART1,
                                        PMHAL_PRCM_MODULE_MODE_ENABLED,
                                        PM_TIMEOUT_INFINITE);
            break;
        case UART2_INST:
            break;
        case UART3_INST:
            retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_UART3,
                                        PMHAL_PRCM_MODULE_MODE_ENABLED,
                                        PM_TIMEOUT_INFINITE);
            break;
        case UART4_INST:
            retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_UART4,
                                        PMHAL_PRCM_MODULE_MODE_ENABLED,
                                        PM_TIMEOUT_INFINITE);
            break;
        default:
            retVal = -1;
            break;
    }

    return retVal;
}

int32_t ti_tda2xx_evm_configure_pad(void)
{
    int32_t retVal;
    /*MMC1 PAD Configuration*/
    retVal = PlatformMMCSDSetPinMux(MMC1_INST);

#ifdef NOR
    PlatformGPMCSetPinMuxAddrLines();
#elif defined (QSPI)
    PlatformQSPISetPinMux();
#endif

    PlatformRGMIISetPinMux();

    return retVal;
}

int32_t ti_tda2xx_mc_configure_pad(void)
{
    int32_t retval;
    /*MMC1 PAD Configuration*/
    retval = PlatformMMCSDSetPinMux(MMC1_INST);

    /*I2C1 MUX MODE 0*/
    /*I2C2 MUX MODE 0*/
    PlatformI2C3SetPinMux();
    I2C4_Pin_Mux();
    PlatformI2C5SetPinMux();

#ifdef NOR
    PlatformGPMCSetPinMuxAddrLines();
#elif defined (QSPI)
    PlatformQSPISetPinMux();
#endif

    PlatformRGMIISetPinMux();

    /*MC board specific pad configuration*/
    PlatformTDA2xxMCSetPinMux();

    return retval;
}

int32_t SBLConfigStaticDependency(void)
{
    int32_t         pmError;
    pmhalPrcmCdId_t clockDomain = 0U;

    for (clockDomain = (PMHAL_PRCM_CD_LOWER_BOUND + 1U);
         clockDomain < PMHAL_PRCM_CD_COUNT;
         clockDomain++)
    {
        /* Do not care much about the return value here because not
         * not all clock domains are masters */
        PMHALStaticDepDisableAllSlaveDep(clockDomain);
    }

    pmError  = PMHALStaticDepEnable(PMHAL_PRCM_CD_MPU, PMHAL_PRCM_CD_EMIF);
    pmError += PMHALStaticDepEnable(PMHAL_PRCM_CD_MPU, PMHAL_PRCM_CD_L3MAIN1);
    pmError += PMHALStaticDepEnable(PMHAL_PRCM_CD_IPU1, PMHAL_PRCM_CD_L3MAIN1);
#ifdef TDA2XX_BUILD
    pmError += PMHALStaticDepEnable(PMHAL_PRCM_CD_IPU2, PMHAL_PRCM_CD_L3MAIN1);
#endif
    pmError += PMHALStaticDepEnable(PMHAL_PRCM_CD_DSP1, PMHAL_PRCM_CD_L3MAIN1);
#ifdef TDA2XX_BUILD
    pmError += PMHALStaticDepEnable(PMHAL_PRCM_CD_DSP2, PMHAL_PRCM_CD_L3MAIN1);
#endif
    return pmError;
}

