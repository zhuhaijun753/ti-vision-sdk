/******************************************************************************
 *                                                                            *
 * Copyright (c) 2014 Texas Instruments Incorporated - http://www.ti.com/     *
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
 *  \file bsp_config.h
 *
 *  \brief BSP header file containing globally used configuration.
 *
 */

#ifndef BSP_CONFIG_H_
#define BSP_CONFIG_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief BSP package version string.
 *  Version is of the form mm_nn_xx_yy where,
 *      mm - Product version. This increments for any new BSP versions or
 *           platform.
 *      nn - Major number - Increments if any backward compatibility is broken
 *           or major change within a product version.
 *      xx - Minor number - Increments for any minor change or any additions
 *           done without breaking backward compatibility.
 *      yy - Build number - Increments for every release.
 */
#define BSP_VERSION_STRING              "BSP_01_04_00_08"

/** \brief BSP package version number. */
#define BSP_VERSION_NUMBER              ((UInt32) 0x01040008U)

/* ========================================================================== */
/* The define below could be used to enable logging for each modules          */
/* Set the value to                                                           */
/* (GT_DEBUG | GT_TraceState_Enable) - Enables all log messages               */
/* (GT_INFO | GT_TraceState_Enable) - Enables log messages except debug level */
/* (GT_ERR | GT_TraceState_Enable) - Enables only error log messages          */
/* 0 - Disables all log messages                                              */
/* ========================================================================== */

/** \brief Log enable for BSP Utils. */
#define BspUtilsTrace                   (GT_DEFAULT_MASK)

/** \brief Log enable for platform module. */
#define BspPlatTrace                    (GT_INFO | GT_TraceState_Enable)

/** \brief Log enable for board module. */
#define BspBoardTrace                   (GT_INFO | GT_TraceState_Enable)

/** \brief Log enable for I2C driver. */
#define BspI2cTrace                     (GT_DEFAULT_MASK)

/** \brief Log enable for external decoder/encoder drivers. */
#define BspDeviceTrace                  (GT_INFO | GT_TraceState_Enable)

/** \brief Log enable for VPS driver common modules. */
#define VpsDrvTrace                     (GT_INFO | GT_TraceState_Enable)

/** \brief Log enable for capture driver. */
#define VpsDrvCaptTrace                 (GT_DEFAULT_MASK)

/** \brief Log enable for display driver. */
#define VpsDrvDispTrace                 (GT_DEFAULT_MASK)

/** \brief Log enable for display controller driver. */
#define VpsDrvDctrlTrace                 (GT_DEFAULT_MASK)

/** \brief Log enable for memory to memory driver. */
#define VpsMDrvTrace                    (GT_DEFAULT_MASK)

/** \brief Log enable for M2M list manager. */
#define VpsMlmTrace                     (GT_DEFAULT_MASK)
/** \brief Log enable for M2M VPE driver. */
#define VpsMdrvVpeTrace                 (GT_DEFAULT_MASK)

/** \brief Log enable for M2M ISS driver. */
#define VpsMdrvIssTrace                 (GT_DEFAULT_MASK)

/** \brief Log enable for control driver. */
#define VpsDrvCtrlTrace                 (GT_DEFAULT_MASK)

/** \brief Log enable for example application. */
#define BspAppTrace                     (GT_INFO | GT_TraceState_Enable)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Get the version string for the BSP package.
 *
 *  This is the version number for all the drivers on BSP. This
 *  function can be called prior to #Bsp_commonInit() to get the version number.
 *
 *  \return pointer to BSP version string.
 */
const Char *Bsp_getVersionString(void);

/**
 *  \brief Same as #Bsp_getVersionString() except it returns the version in
 *  UInt32 form.
 *
 *  Example, v1.0.1.17 will be 0x01000117
 *
 *  \return BSP version number.
 */
UInt32 Bsp_getVersionNumber(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSP_CONFIG_H_ */
