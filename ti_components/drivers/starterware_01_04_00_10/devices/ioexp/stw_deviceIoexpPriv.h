/* ======================================================================
 *   Copyright (C) 2014 Texas Instruments Incorporated
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

/**
 *  \file stw_device_ioexp_priv.h
 *
 *  \brief IO Expander internal interface file.
 */

#ifndef STW_DEVICE_IOEXP_PRIV_H_
#define STW_DEVICE_IOEXP_PRIV_H_

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

int32_t DEVICEIoexpInit(void);
int32_t DEVICEIoexpDeInit(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef STW_DEVICE_IOEXP_PRIV_H_ */
