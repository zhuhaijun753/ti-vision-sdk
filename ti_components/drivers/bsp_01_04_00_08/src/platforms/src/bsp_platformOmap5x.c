/******************************************************************************
 *                                                                            *
 * Copyright (c) 2012 Texas Instruments Incorporated - http://www.ti.com/     *
 *                                                                            *
 * All rights reserved. Property of Texas Instruments Incorporated.           *
 * Restricted rights to use, duplicate or disclose this code are              *
 * granted through contract.                                                  *
 *                                                                            *
 * The program may not be used without the written permission                 *
 * of Texas Instruments Incorporated or against the terms and conditions      *
 * stipulated in the agreement under which this program has been              *
 * supplied.                                                                  *
 *                                                                            *
 *****************************************************************************/

/**
 *  \file bsp_platformOmap5x.c
 *
 *  \brief Implements the Omap5x platform specific functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <xdc/std.h>
#include <common/bsp_types.h>
#include <common/trace.h>
#include <platforms/bsp_platform.h>
#include <bsp_platformOmap5x.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define REG32(x)                        *((volatile UInt32 *) (x))
#define PD  (0x0)
#define DEFAULT (0xFF)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 Bsp_platformOmap5xSetPinMux(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 Bsp_platformOmap5xInit(const Bsp_PlatformInitParams *initParams)
{
    Int32 status = BSP_SOK;
    /* Unlock MMR_LOCK_2  */
    *((volatile UInt32 *) 0x4A002544U) = (UInt32) 0xF757FDC0;
    /* XBAR DISPC_IRQ at IPU1_23 */
    *((volatile UInt32 *) 0x4A0027E0U) = (UInt32) 20;
    /*
     *  To be implemented
     */
    return (status);
}

Int32 Bsp_platformOmap5xDeInit(void)
{
    Int32 status = BSP_SOK;

    return (status);
}

Bsp_PlatformCpuRev Bsp_platformOmap5xGetCpuRev(void)
{
    /* Todo - Read from Chip ID register */
    return (BSP_PLATFORM_CPU_REV_1_0);
}

Bsp_PlatformPackageType Bsp_platformOmap5xGetPackageType(void)
{
    return (BSP_PLATFORM_PACKAGE_TYPE_UNKNOWN);
}
