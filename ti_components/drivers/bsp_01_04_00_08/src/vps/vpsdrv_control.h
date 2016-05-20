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
 *  \file vpsdrv_control.h
 *
 *  \brief VPS control driver interface file.
 *
 */

#ifndef VPSDRV_CONTROL_H_
#define VPSDRV_CONTROL_H_

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

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief One-time VPS control driver init.
 *
 *  Gets called as part of Vps_init().
 *
 *  Initializes internal data structures.
 *
 *  \return 0 on success, else failure.
 */
Int32 VpsDrv_ctrlInit(void);

/**
 *  \brief One-time VPS control driver de-init.
 *
 *  Free's all resources allocated during VpsDrv_ctrlInit().
 *
 *  \return 0 on success, else failure.
 */
Int32 VpsDrv_ctrlDeInit(void);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef VPSDRV_CONTROL_H_ */
