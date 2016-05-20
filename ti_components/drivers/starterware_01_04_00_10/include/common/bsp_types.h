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
 *  \file bsp_types.h
 *
 *  \brief BSP header file containing commonly used data types and macros.
 *
 */

#ifndef BSP_TYPES_H_
#define BSP_TYPES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*
 * =========== Error codes returned by BSP functions ===========
 */
#define BSP_SOK                         ((Int32) 0)
#define BSP_EFAIL                       ((Int32) - 1)
#define BSP_EBADARGS                    ((Int32) - 2)
#define BSP_EINVALID_PARAMS             ((Int32) - 3)
#define BSP_EDEVICE_INUSE               ((Int32) - 4)
#define BSP_ETIMEOUT                    ((Int32) - 5)
#define BSP_EALLOC                      ((Int32) - 6)
#define BSP_EOUT_OF_RANGE               ((Int32) - 7)
#define BSP_EAGAIN                      ((Int32) - 8)
#define BSP_EUNSUPPORTED_CMD            ((Int32) - 9)
#define BSP_ENO_MORE_BUFFERS            ((Int32) - 10)
#define BSP_EUNSUPPORTED_OPS            ((Int32) - 11)
#define BSP_EDRIVER_INUSE               ((Int32) - 12)
#define BSP_WNON_RECOMMENDED_PARAMS     ((Int32) - 13)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSP_TYPES_H_ */
