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
 *  \file bsp_common.c
 *
 *  \brief Interface file to the common utility function.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <xdc/std.h>
#include <common/bsp_types.h>
#include <common/trace.h>
#include <common/bsp_config.h>
#include <common/bsp_common.h>
#include <bsp_commonPriv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 Bsp_commonInit(const Bsp_CommonInitParams *initPrms)
{
    Int32 retVal = BSP_SOK;

    if (NULL == initPrms)
    {
        GT_0trace(BspUtilsTrace, GT_ERR, "NULL init params!!\n");
        retVal = BSP_EBADARGS;
    }
    else
    {
        retVal = BspUtils_init();
    }

    return (retVal);
}

Int32 Bsp_commonDeInit(Ptr args)
{
    Int32 retVal = BSP_SOK;

    retVal = BspUtils_deInit(NULL);

    return (retVal);
}

/**
 *  Bsp_getVersionString
 *  \brief Get the BSP package version in string form. This API can be
 *  called before calling #Bsp_commonInit().
 *
 *  \return             Returns pointer to BSP version string.
 */
const Char *Bsp_getVersionString(void)
{
    return (BSP_VERSION_STRING);
}

/**
 *  Bsp_getVersionNumber
 *  \brief Get the BSP package version in number form. This API can be
 *  called before calling #Bsp_commonInit().
 *
 *  \return             BSP version number.
 */
UInt32 Bsp_getVersionNumber(void)
{
    return (BSP_VERSION_NUMBER);
}

