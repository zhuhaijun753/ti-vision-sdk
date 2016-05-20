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
 *  \file bsp_commonPriv.h
 *
 *  \brief BSP common library private header file.
 *
 */

#ifndef BSP_COMMON_PRIV_H_
#define BSP_COMMON_PRIV_H_

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
 *  BspUtils_init
 *  \brief Initializes the Util objects and create pool semaphore.
 *
 *  \returns                Returns 0 on success else returns error value.
 */
Int32 BspUtils_init(void);

/**
 *  BspUtils_deInit
 *  \brief De-Initializes the Util objects by removing pool semaphore.
 *
 *  \param arg              Not used currently. Meant for future purpose.
 *
 *  \return                 Returns 0 on success else returns error value.
 */
Int32 BspUtils_deInit(Ptr arg);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSP_COMMON_PRIV_H_ */
