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
 * \file platform_tda3xx.c
 *
 * \brief  Contains board specific configurations
 *
 */

#include "stdint.h"
#include "soc_defines.h"
#include "platform.h"
#include "soc.h"
#include "hw_types.h"
#include "hw_ctrl_core_pad_io.h"
#include "hw_ctrl_core.h"
#include "hw_ctrl_wkup.h"
#include "hw_core_cm_core.h"
#include "hw_l4per_cm_core.h"
#include "hw_core_prm.h"
#include "hw_ctrl_core_sec.h"
#include "hw_ckgen_cm_core.h"
#include "hw_l3init_cm_core.h"
#include "hw_l3init_prm.h"
#include "hw_wkupaon_cm.h"
#include "hw_ipu_cm_core_aon.h"

/***********************************************************************
**                            MACRO DEFINITIONS
***********************************************************************/

/* Todo : Define GPMC MUX Val */

/***********************************************************************
**                     EXTERNAL FUNCTION PROTOTYPES
***********************************************************************/

/**********************************************************************
 *                   INTERNAL FUNCTION PROTOTYPES
 **********************************************************************/

/******************************************************************************
**                      EXTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
#ifdef REGRESSION_MODE
sbl_regression_log_bfr_t sbl_regression_log_bfr  __attribute__ ((section(
                                                                     ".sbl_reg_log_bfr")));
#endif

/******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/

/***********************************************************************
**                     EXTERNAL FUNCTION PROTOTYPES
***********************************************************************/

/**********************************************************************
 *                   INTERNAL FUNCTION PROTOTYPES
 **********************************************************************/

/******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/

void PlatformMCSPI1PrcmEnable(void)
{
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MCSPI1_CLKCTRL, 0x02);
    while (HW_RD_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MCSPI1_CLKCTRL) !=
           0x02U)
    {
        ;
    }
}

void PlatformMCSPI2PrcmEnable(void)
{
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MCSPI2_CLKCTRL, 0x02);
    while (HW_RD_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MCSPI2_CLKCTRL) !=
           0x02U)
    {
        ;
    }
}

void PlatformGPMCPinCtrl(void)
{
    /* Todo : GPMC PinCtrl */
}

void PlatformGPMCConfig(void)
{
    /* Todo : GPMC config */
}

uint32_t PlatformGetQspiMode(void)
{
    return 0U;
}

void PlatformDCAN1PrcmEnable(void)
{
    /*CM_WKUPAON_DCAN1_CLKCTRL*/
    HW_WR_FIELD32(SOC_WKUPAON_CM_BASE + CM_WKUPAON_DCAN1_CLKCTRL,
                  CM_WKUPAON_DCAN1_CLKCTRL_MODULEMODE,
                  CM_WKUPAON_DCAN1_CLKCTRL_MODULEMODE_ENABLE);

    while ((HW_RD_FIELD32(SOC_WKUPAON_CM_BASE + CM_WKUPAON_DCAN1_CLKCTRL,
                          CM_WKUPAON_DCAN1_CLKCTRL_IDLEST)) ==
           CM_WKUPAON_DCAN1_CLKCTRL_IDLEST_DISABLE)
    {
        ;
    }
}

void PlatformDCAN2PrcmEnable(void)
{
    /*CM_WKUPAON_DCAN2_CLKCTRL*/
    HW_WR_FIELD32(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_DCAN2_CLKCTRL,
                  CM_L4PER2_DCAN2_CLKCTRL_MODULEMODE,
                  CM_L4PER2_DCAN2_CLKCTRL_MODULEMODE_ENABLE);

    while ((HW_RD_FIELD32(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_DCAN2_CLKCTRL,
                          CM_L4PER2_DCAN2_CLKCTRL_IDLEST)) ==
           CM_L4PER2_DCAN2_CLKCTRL_IDLEST_DISABLE)
    {
        ;
    }
}

void PlatformDcanMessageRamInit(uint32_t instance)
{
    uint32_t status = 0U;

    switch (instance)
    {
        case 0U:
            /* Clear the start bit so that pulse is generated
             * when run second time */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START,
                0U);

            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START_CAUSESTHEINITIALIZATIONPULSETOHAPPENANDNONEEDFORSWTOWRITE0);

            status =
                ((uint32_t) 0x1 <<
                 CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE_SHIFT) &
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE_MASK;

            while (status !=
                   ((status &
                     HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                                 CTRL_CORE_CONTROL_IO_2))))
            {
                ;
            }

            /* Write one to clear done bit */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE,
                1U);
            break;

        case 1U:
            /* Clear the start bit so that pulse is generated
             * when run second time */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START,
                0U);

            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START_CAUSESTHEINITIALIZATIONPULSETOHAPPENANDNONEEDFORSWTOWRITE0);
            status =
                ((uint32_t) 0x1 <<
                 CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE_SHIFT) &
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE_MASK;

            while (status !=
                   ((status &
                     HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                                 CTRL_CORE_CONTROL_IO_2))))
            {
                ;
            }

            /* Write one to clear done bit */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE,
                1U);
            break;

        default:
            break;
    }
}

uint32_t PlatformGetSiliconPackageType(void)
{
    uint32_t packageType, regVal;

    regVal = HW_RD_FIELD32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                           CTRL_CORE_BOOTSTRAP,
                           CTRL_CORE_BOOTSTRAP_SYSBOOT_7);

    if (0x1U == regVal)
    {
        packageType = PLATFORM_SILICON_PACKAGE_TYPE_12X12;
    }
    else
    {
        packageType = PLATFORM_SILICON_PACKAGE_TYPE_15X15;
    }
    return packageType;
}

void PlatformMCASP1PrcmEnable(void)
{
    HW_WR_REG32(SOC_IPU_CM_CORE_AON_BASE + CM_IPU_MCASP1_CLKCTRL, 0x02);
    while ((HW_RD_REG32(SOC_IPU_CM_CORE_AON_BASE + CM_IPU_MCASP1_CLKCTRL)) !=
           0x02U)
    {
        ;
    }
}

