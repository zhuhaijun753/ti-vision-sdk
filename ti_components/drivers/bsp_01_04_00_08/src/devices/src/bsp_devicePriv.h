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
 *  \file bsp_devicePriv.h
 *
 *  \brief BSP device private header file.
 *
 */

#ifndef BSP_DEVICE_PRIV_H_
#define BSP_DEVICE_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <xdc/runtime/Error.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/io/GIO.h>
#include <ti/sysbios/io/IOM.h>
#include <ti/sysbios/syncs/SyncSem.h>
#include <ti/sysbios/knl/Semaphore.h>

#include <common/bsp_types.h>
#include <osal/bsp_osal.h>
#include <common/trace.h>
#include <common/bsp_config.h>
#include <platforms/bsp_platform.h>
#include <boards/bsp_board.h>
#include <i2c/bsp_i2c.h>
#include <devices/bsp_device.h>

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

typedef struct
{
    UInt32            i2cDebugEnable;
    GIO_Handle        i2cHndl[BSP_DEVICE_I2C_INST_ID_MAX];
    GIO_Struct        i2cGioStruct[BSP_DEVICE_I2C_INST_ID_MAX];
    BspOsal_SemHandle i2cHndlLock[BSP_DEVICE_I2C_INST_ID_MAX];
    SyncSem_Struct    i2cSyncSemStruct[BSP_DEVICE_I2C_INST_ID_MAX];
    Semaphore_Struct  i2cSemStruct[BSP_DEVICE_I2C_INST_ID_MAX];
} Bsp_DeviceObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

Int32 Bsp_deviceI2cInit(void);
Int32 Bsp_deviceI2cDeInit(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSP_DEVICE_PRIV_H_ */
