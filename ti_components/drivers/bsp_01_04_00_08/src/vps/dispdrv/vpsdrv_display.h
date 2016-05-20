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
 *  \file vpsdrv_display.h
 *
 *  \brief Display driver interface file.
 *
 */

#ifndef VPSDRV_DISPLAY_H_
#define VPSDRV_DISPLAY_H_

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

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct VpsDrv_DispInitParams
 *  \brief Instance specific parameters used at init call.
 */
typedef struct
{
    UInt32             drvInstId;
    /**< Instance ID. */
    VpsCore_Inst       coreInstObj;
    /**< Core instance object used in core open. */
    const VpsCore_Ops *coreOps;
    /**< Core function pointers. */
} VpsDrv_DispInitParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief One-time display sub-system init.
 *
 *  Gets called as part of Vps_init().
 *
 *  Initializes internal data structures and common system level resources
 *  related to display.
 *
 *  \param numInst      Number of instance objects to be initialized.
 *  \param initPrms     Pointer to the init parameter containing
 *                      instance specific information. If the number of
 *                      instance is greater than 1, then this pointer
 *                      should point to an array of init parameter
 *                      structure of size numInst.
 *
 *  \return 0 on success, else failure.
 */
Int32 VpsDrv_dispInit(UInt32 numInst, const VpsDrv_DispInitParams *initPrms);

/**
 *  \brief One-time display sub-system de-init.
 *
 *  Free's all resources allocated during VpsDrv_dispInit().
 *
 *  \return 0 on success, else failure.
 */
Int32 VpsDrv_dispDeInit(void);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef VPSDRV_DISPLAY_H_ */
