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
 *  \file vpsdrv_displayPriv.h
 *
 *  \brief Display driver private header file.
 *
 */

#ifndef VPSDRV_DCTRL_PRIV_H_
#define VPSDRV_DCTRL_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <common/bsp_types.h>
#include <common/trace.h>
#include <common/bsp_config.h>
#include <common/bsp_utils.h>
#include <fvid2/fvid2.h>
#include <fvid2_drvMgr.h>
#include <vps/vps_display.h>
#include <common/vpscore.h>
#include <dispcore/vpscore_dss.h>
#include <dispdrv/vpsdrv_display.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Forward declaration for instance object. */
typedef struct VpsDrv_DctrlInstObj_t VpsDrv_DctrlInstObj;

/**
 *  struct VpsDrv_DispStates
 *  \brief Different states of the driver.
 */
typedef struct
{
    UInt32 isInit;
    /**< Flag to indicate intialization is done or not for an instance. */
    UInt32 isOpened;
    /**< Flag to indicate whether a instance is opened or not. */
    UInt32 isStarted;
    /**< Flag to indicate whether the display has started or not. */
} VpsDrv_DctrlStates;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    Fvid2_DrvOps         fvidDrvOps;
    /**< FVID2 driver ops. */
    UInt32               isRegistered;
    /**< FVID2 registeration complete flag. */
    VpsDrv_DctrlInstObj *instObj;
    /**< Display instance objects pointer. */
} VpsDrv_DctrlCommonObj;

/**
 *  \brief Per instance information.
 */
struct VpsDrv_DctrlInstObj_t
{
    UInt32               drvInstId;
    /**< Instance ID. */
    VpsCore_Inst         coreInstObj;
    /**< Core instance object used in core open. */
    const VpsCore_Ops   *coreOps;
    /**< Core function pointers. */

    VpsCore_Property     coreProperty;
    /**< Core properties. */

    Vps_DispCreateParams createPrms;
    /**< Create parameters. */

    Vps_DispStatus       stat;
    /**< Instance statistics object. */

    VpsDrv_DctrlStates   state;
    /**< Instance state. */

    VpsCore_Handle       coreHandle;
    /**< Core handle. */

    BspOsal_SemHandle    lockSem;
    /**< Semaphore to protect the open/close calls and other memory
     *   allocation per instance. */
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/*
 * Global variables
 */

/*
 * Core functions
 */
Int32 vpsDrvDctrlOpenCore(VpsDrv_DctrlInstObj *instObj);
Int32 vpsDrvDctrlCloseCore(VpsDrv_DctrlInstObj *instObj);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef VPSDRV_DCTRL_PRIV_H_ */

