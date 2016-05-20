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
 *  \file bspdrv_sii9022aPriv.h
 *
 *  \brief SII9022a encoder internal header file.
 */

#ifndef BSP_SII9022A_PRIV_H_
#define BSP_SII9022A_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <xdc/std.h>
#include <common/bsp_types.h>
#include <common/bsp_config.h>
#include <common/trace.h>
#include <osal/bsp_osal.h>
#include <common/bsp_utils.h>
#include <fvid2_drvMgr.h>
#include <platforms/bsp_platform.h>
#include <devices/bsp_videoEncoder.h>
#include <devices/bsp_sii9022a.h>
#include <sii9022a/bspdrv_sii9022a.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Driver object state - NOT IN USE. */
#define BSP_SII9022A_OBJ_STATE_UNUSED       (UInt32) (0U)
/** \brief Driver object state - IN USE and IDLE. */
#define BSP_SII9022A_OBJ_STATE_IDLE         (UInt32) (1U)
/** \brief Device state - Not initialized. */
#define BSP_SII9022A_NOT_INITED             (UInt32) (0U)
/** \brief Device state - initialized successfully. */
#define BSP_SII9022A_INITED                 (UInt32) (1U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief SII9022A driver handle object.
 */
typedef struct
{
    UInt32                 state;
    /**< Handle state - used or free. */
    UInt32                 handleId;
    /**< Handle ID, 0..BSP_DEVICE_MAX_HANDLES-1. */
    BspOsal_SemHandle      lock;
    /**< Driver lock. */
    Bsp_VidEncCreateParams createPrms;
    /**< Create time arguments. */
    Bsp_Sii9022aParams     prms;
    /**< SII9022A params */
    Bsp_Sii9022aHdmiChipId hdmiChipId;
    /**< HDMI Chip id. */
    UInt32                 hpd;
    /**< HDMI Hot plug detect. */
    UInt8                  syncCfgReg;
    /**< Sync Configuration Register. */
    UInt8                  syncPolarityReg;
    /**< Sync polarity Register. */
    UInt32                 isRgbOutput;
    /**< Is output RGB. */
    UInt32                 inBusCfg;
    /**< Input bus config. */
} Bsp_Sii9022aHandleObj;

/**
 *  \brief SII9022A Global driver object.
 */
typedef struct
{
    UInt32                deviceState;
    /**< Driver state. */
    BspOsal_SemHandle     lock;
    /**< Global driver lock. */
    Bsp_Sii9022aHandleObj handlePool[BSP_DEVICE_MAX_HANDLES];
    /**< Handle objects. */
} Bsp_Sii9022aCommonObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef BSPDRV_SII9022A_PRIV_H_ */

