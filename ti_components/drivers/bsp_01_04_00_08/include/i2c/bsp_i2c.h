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
 *  \defgroup BSP_DRV_I2C_API I2C Driver API
 *
 *  @{
 */

/**
 *  \file bsp_i2c.h
 *
 *  \brief I2C Driver Interface.
 */

#ifndef BSP_I2C_H_
#define BSP_I2C_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <i2clib/lld_hsi2c.h>
#include <osal/bsp_osal.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \brief  I2C Ioctl commands
 *
 *  I2C Ioctl commands
 */
typedef enum {
    IOCTL_I2C_PROBE,
    /** < IOCTL for probing the i2c instance>*/
    IOCTL_I2C_GET_BUS_FREQUENCY,
    /** < IOCTL to get I2C Bus frequency>*/
    IOCTL_I2C_SET_BUS_FREQUENCY,
    /** < IOCTL to set I2C Bus frequency>*/
    IOCTL_I2C_RESET_CONTROLLER,
    /** < IOCTL reset I2C controller>*/
    IOCTL_I2C_RECOVER_BUS
    /** < IOCTL to force 9 clk pulses>*/
}I2c_IOCTL;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief I2C Device Initialization Object
 *
 *  This structure provides Initalization Routines.
 *  It needs to be passed while creating the specific I2C instance object.
 */
typedef struct
{
    lld_hsi2c_initParam_t *initParams;
    /**< lld_hsi2c_initParam_s contains the I2C initialisation parameters.*/
    BspOsal_SemHandle      hsi2c_sem;
    /**< hsi2c_sem semaphore handle that needs to be passed by application*/
    UInt32                 instId;
    /**< instId Instance Id of the instance, needs to be passed by application*/
} I2c_DevInitParams;

/**
 *  \brief Initialize I2C controller(s)
 *
 *  Initializes I2C controller(s) with the initPrms structure. User should pass
 *  configuration information for numInst controllers.
 *  This function should be called before calling any of driver APIs and
 *  should be called only once.
 *
 *  \param  numInst     [IN]    Number of I2C controllers need to be
 *                              initialized
 *  \param  devInitPrms    [IN]    Configuration for numInst controllers.
 *
 *  \return IOM_COMPLETED on success else appropriate error code on failure.
 */

Int32 I2c_GlobalInit(UInt32 numInst, const I2c_DevInitParams *devInitPrms);
/**
 *  \brief De-initializes I2C Instances
 *
 *  De-initializes the I2C controllers. If there are open handles,
 *  they are invalidated. It should be called only after calling Bsp_i2cInit
 *  and in the end when I2C driver is no more required by any user.
 *
 *  \param args         [IN] Not used currently. Meant for future purpose.
 *
 *  \return IOM_COMPLETED on success else appropriate error code on failure.
 */
Int32 I2c_GlobalDeInit(Ptr args);
#ifdef __cplusplus
}
#endif

#endif  /* #ifndef BSP_I2C_H_ */

/* @} */
