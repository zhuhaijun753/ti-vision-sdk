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
 *  \file bsp_common.h
 *
 *  \brief BSP header file containing commonly used functions.
 *
 */

#ifndef BSP_COMMON_H_
#define BSP_COMMON_H_

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

/**
 *  \brief BSP common library initialization parameters.
 */
typedef struct
{
    UInt32 reserved;
    /**< Reserved. Not used as of now. */
} Bsp_CommonInitParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Init the the BSP common library. This function should be called
 *  before calling any of the common utility APIs.
 *
 *  \param initPrms     [IN] Common library initialization parameters. This
 *                           parameter can't be NULL.
 *
 *  \return BSP_SOK on success, else appropriate error code on failure.
 */
Int32 Bsp_commonInit(const Bsp_CommonInitParams *initPrms);

/**
 *  \brief De-init the common library.
 *
 *  \param args         [IN] Not used currently. Set to NULL.
 *
 *  \return BSP_SOK on success, else appropriate error code on failure.
 */
Int32 Bsp_commonDeInit(Ptr args);

/**
 *  \brief Bsp_CommonInitParams structure init function.
 *
 *  \param initPrms     [IN] Pointer to #Bsp_CommonInitParams structure.
 *
 */
static inline void BspCommonInitParams_init(Bsp_CommonInitParams *initPrms);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void BspCommonInitParams_init(Bsp_CommonInitParams *initPrms)
{
    if (NULL != initPrms)
    {
        initPrms->reserved = 0;
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSP_COMMON_H_ */
