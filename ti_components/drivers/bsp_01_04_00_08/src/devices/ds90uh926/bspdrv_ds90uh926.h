/******************************************************************************
 *                                                                            *
 * Copyright (c) 2016 Texas Instruments Incorporated - http://www.ti.com/     *
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
 *  \file bspdrv_ds90uh926.h
 *
 *  \brief DS90UH926 24-bit FPD-III de-serializer interface file.
 */

#ifndef BSPDRV_DS90UH926_H_
#define BSPDRV_DS90UH926_H_

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

Int32 Bsp_ds90uh926Init(void);
Int32 Bsp_ds90uh926DeInit(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSPDRV_DS90UH926_H_ */
