/**
 *  \file     pcie_app.c
 *
 *  \brief    Source file containing the PCIe IP related configuration
 *            functions. These functions will be called by example
 *            applications.
 *
 *  \copyright Copyright (C) 2013 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "stdint.h"
#include <string.h>
#include <common/stw_types.h>
#include "hw_types.h"
#include "soc_defines.h"
#include "platform.h"
#include "uartStdio.h"
#include "soc.h"
#include "pcie.h"

/* Application header files */
#include "pcie_app.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void PCIEAppUartInit(void)
{
    PlatformUART1SetPinMux();

    UARTStdioInit();
}

void PCIEAppPrcmConfig(void)
{
    PlatformPCIESS1ClockEnable();

    PlatformPCIESS1PllConfig();

    PlatformPCIESS1CtrlConfig();

    PlatformPCIESS1Reset();

    PCIESS1PhyConfig();
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */