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
 *  \ingroup STWUTILS_API
 *  \defgroup STWUTILS_APP_API Application helper APIs
 *  @{
 */

/**
 *  \file stwutils_app.h
 *
 *  \brief Header file to use application level helper functions.
 */

#ifndef STWUTILS_APP_H_
#define STWUTILS_APP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

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
 *  \brief Starterware Application initialization parameters.
 */
typedef struct stwAppInitParams
{
    uint32_t isI2cInitReq;
    /**< I2c Initialisation is required or not */
    uint32_t isUartInitReq;
    /**< uart Initialisation is required or not */
} stwAppInitParams_t;

/**
 *  \brief Starterware Application initialization parameters.
 */
typedef struct stwAppDeInitParams
{
    uint32_t isI2cDeInitReq;
    /**< I2c Initialisation is required or not */
} stwAppDeInitParams_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief STW application utils init function.
 *
 *  Init function which initializes global objects.
 *
 *  This function should be called only once after doing all other module
 *  initialization device init and platform init.
 *
 *  \return STW_SOK on success else appropiate error code on failure.
 */
int32_t StwUtils_appInit(void);

/**
 *  \brief STW application utils deinit function.
 *
 *  De-init function
 *
 *  \return STW_SOK on success else appropriate error code on failure.
 */
int32_t StwUtils_appDeInit(void);

/**
 *  \brief STW application utils function to call all the default init
 *  functions.
 *
 *  Note that this function calls the StwUtils_appInit() as well
 *  and hence the application should not call StwUtils_appInit() separately.
 *
 *  \return STW_SOK on success else appropriate error code on failure.
 */
int32_t StwUtils_appDefaultInit(stwAppInitParams_t stwAppInitPrms);

/**
 *  \brief STW application utils function to call all the default de-init
 *  functions.
 *
 *  Note that this function calls the StwUtils_appDeInit() as well
 *  and hence the application should not call StwUtils_appDeInit() separately.
 *
 *  \return STW_SOK on success else appropriate error code on failure.
 */
int32_t StwUtils_appDefaultDeInit(stwAppDeInitParams_t stwAppDeInitPrms);

/**
 *  \brief STW application utils function to print platform and Board Info
 *
 */
void StwUtils_appPrintInfo(void);

/**
 *  \brief STW application utils function for UART Console Intialisation
 *
 */
int32_t StwUtils_appUartModuleInit(uint32_t uartInitReq);

#ifdef __cplusplus
}
#endif

#endif  /* #define STWUTILS_APP_H_ */

/* @} */
