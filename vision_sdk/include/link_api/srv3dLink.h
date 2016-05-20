/*
 *******************************************************************************
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \ingroup SAMPLE_LINUX_MODULE_API
 * \defgroup SRV3D_LINK_API Srv3D Link API for InfoADAS
 *
 * \brief  This module has the interface for using Srv3D Link
 *
 *         Srv3D Link is used to feed video frames to SGX for
 *         creating the surround view (360 degree view) of the Car.
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file srv3DLink.h
 *
 * \brief Srv3D Link API
 *
 * \version 0.0 (Aug 2015) : [SS] First version
 *
 *******************************************************************************
 */

#ifndef SRV3D_LINK_H_
#define SRV3D_LINK_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
#define SRV3D_LINK_CMD_ACQUIRE_EGL_INFO                       (0x8000U)

/* @{ */

/**
 *******************************************************************************
 * \brief Enum for the input Q IDs
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/

typedef enum
{
    SRV3D_LINK_IPQID_MULTIVIEW = 0x0,
    /**< QueueId for multiview images */

    SRV3D_LINK_IPQID_PALUT = 1,
    /**< QueueId for PA statistics */

    SRV3D_LINK_IPQID_GALUT = 2,
    /**< QueueId for GA LUTs */

    SRV3D_LINK_IPQID_BLENDLUT = 3,
    /**< QueueId for SGX Blend LUT */

    SRV3D_LINK_NUM_IPQ = 4,
    /**< Maximum number of input queues */

    SRV3D_LINK_IPQID_FORCE32BITS = 0x7FFFFFFF
    /**< To make sure enum is 32 bits */

} srv3dLink_InputQueId;

/* @} */

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Structure containing the Srv3D link create time parameters
 *
 *          This structure is used to create and configure a Srv3D link
 *          instance.
 *
 *******************************************************************************
*/
typedef struct
{
    System_LinkOutQueParams  outQueParams;
    /**< Srv3D link output queue information */
    System_LinkInQueParams   inQueParams[SRV3D_LINK_NUM_IPQ];
    /**< Srv3D link input queue information */
    UInt32                   numInQue;
    /**< Number of inputs queue's */

} srv3dLink_CreateParams;

/*******************************************************************************
 *  Functions Prototypes
 *******************************************************************************
 */
static inline Void srv3dLink_CreateParams_Init(
                                srv3dLink_CreateParams *prm);

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Srv3D link register and init function
 *
 *          For each srv3D instance
 *          - Creates link task
 *          - Registers as a link with the system API
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 srv3dLink_init();

/**
 *******************************************************************************
 *
 *   \brief Srv3D link de-register and de-init function
 *
 *          For each srv3D instance
 *          - Deletes link task
 *          - De-registers as a link with the system API
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 srv3dLink_deInit();

/**
 *******************************************************************************
 *
 *   \brief Function to initialize the Srv3D Link Create Params
 *
 *          Sets default values for Srv3D link create time parameters
 *          User/App can override these default values later.
 *
 *   \param prm [IN] Srv3D Link create parameters
 *
 *   \return void
 *
 *******************************************************************************
*/
static inline Void srv3dLink_CreateParams_Init(
                                srv3dLink_CreateParams *prm)
{
    memset(prm, 0, sizeof(srv3dLink_CreateParams));
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
