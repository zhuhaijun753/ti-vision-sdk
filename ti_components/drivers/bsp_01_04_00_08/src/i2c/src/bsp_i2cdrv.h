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
 *  \file Bsp_i2cdrv.h
 *
 *  \brief I2C driver interface file.
 *
 */
#ifndef BSP_I2CDRV_H_
#define BSP_I2CDRV_H_

#include <xdc/std.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Queue.h>
#include <common/bsp_types.h>
#include <osal/bsp_osal.h>
#include <i2clib/lld_hsi2c.h>
#include <i2c/bsp_i2c.h>
#include <common/bsp_config.h>
#include <ti/sysbios/io/IOM.h>
#ifdef __cplusplus
extern "C"
{
#endif

/*! To disable/enable entry level parameter checking in the module APIs       */
#define I2c_paramCheckEnable        (TRUE)

#if defined (BUILD_M4) || defined (BUILD_M3)
#define I2C_IRQ_TIME_OUT    5000
#elif defined (BUILD_DSP)
#define I2C_IRQ_TIME_OUT    7000
#elif defined (BUILD_A15) || defined (BUILD_A8)
#define I2C_IRQ_TIME_OUT    10000
#else
/* default timeout if BUILD_xxx is not set */
#define I2C_IRQ_TIME_OUT    5000
#endif

/**
 *  \brief I2c IOM_Fxns table
 *
 *  Driver function table to be used by applications.
 */
extern const IOM_Fxns I2c_IOMFXNS;

#ifdef __cplusplus
}
#endif /* extern "C"                                                          */

#endif /* BSP_I2CDRV_H_                                 */
