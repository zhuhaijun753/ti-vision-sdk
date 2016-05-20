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
 *  \file stw_device_priv.h
 *
 *  \brief STW device private header file.
 */

#ifndef STW_DEVICE_I2C_PRIV_H_
#define STW_DEVICE_I2C_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "i2clib/lld_hsi2c.h"

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

typedef struct deviceI2cObj
{
    uint32_t       i2cDebugEnable;
    hsI2cObjHandle i2cHndl[HSI2C_INST_MAX];
} deviceI2cObj_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

LLD_hsi2cErrorCode_t DEVICEI2cInit(const deviceInitParams_t *pPrm);
LLD_hsi2cErrorCode_t DEVICEI2cDeInit(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef STW_DEVICE_I2C_PRIV_H_ */
