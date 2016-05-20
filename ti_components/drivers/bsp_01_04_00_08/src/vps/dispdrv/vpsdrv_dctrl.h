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
 *  \file vpsdrv_dctrl.h
 *
 *  \brief Display controller driver interface file.
 *
 */

#ifndef VPSDRV_DCTRL_H_
#define VPSDRV_DCTRL_H_

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
 *  struct VpsDrv_DctrlInitParams
 *  \brief Instance specific parameters used at init call.
 */
typedef struct
{
    const VpsCore_Ops *coreOps;
    /**< Core function pointers. */
    VpsCore_Inst       coreInstObj;
    /**< Core instance object used in core open. */
} VpsDrv_DctrlInitParams;

Int32 VpsDrv_dctrlInit(const VpsDrv_DctrlInitParams *initPrms);

Int32 VpsDrv_dctrlDeInit(void);

#ifdef __cplusplus
}
#endif

#endif
