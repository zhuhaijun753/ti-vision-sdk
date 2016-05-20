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
 *  \file vpscore_dssWb.h
 *
 *  \brief VPS Writeback DSS core interface.
 *  This file defines the interface for the DSS Writeback core.
 *
 */

#ifndef VPSCORE_DSSWB_H_
#define VPSCORE_DSSWB_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <common/bsp_types.h>
#include <common/vps_common.h>
#include <common/vps_evtMgr.h>
#include <common/vpscore.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief IOCTL base address for the common IOCTLs listed below. */
#define VCORE_DSS_WB_COMMON_IOCTL_BASE     (0x00000000U)
/** \brief IOCTL base address for the custom IOCTLs of each cores. */
#define VCORE_DSS_WB_CUSTOM_IOCTL_BASE     (0x00000100U)

/**
 *  \brief Set DSSWB CSC Coefficients IOCTL.
 *
 *  This IOCTL can be used to set the CSC coefficients.
 *  Note: Default BT601 coefficients are set.
 *
 *  \param cmdArgs       [IN] const Vps_DssCscCoeff *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure
 */
#define VCORE_DSS_WB_SET_CSC_COEFF  (VCORE_DSS_WB_COMMON_IOCTL_BASE + 0x01U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    UInt32        dispcIrqNumber;
    /**< DISPC IRQ number at CPU level INTC. */
    VpsHal_Handle wbHandle[VPSHAL_DSS_DISPC_PIPE_MAX_INST];
} VpsCore_DssWbInitParams;

/**
 *  \brief DSS parameters used in set/get DSS params.
 */
typedef struct
{
    Fvid2_Format         outFmt;
    /**< output FVID frame format. */
    UInt32               sourceWidth;
    /**< Horizontal size at source (overlay or vid/Gfx pipeline)
     *   For tda2xx it should be same as inWidth as crop is not supported */
    UInt32               sourceHeight;
    /**< Vertical size at source (overlay or vid/Gfx pipeline)
     *   For tda2xx it should be same as inHeight as crop is not supported */
    UInt32               inWidth;
    /**< Horizontal Size of picture at input of writeback pipeline. */
    UInt32               inHeight;
    /**< Vertical Size of picture at input of writeback pipeline. */
    UInt32               inPosX;
    /**< PositionX of picture at input of writeback pipeline(Overlay Window). */
    UInt32               inPosY;
    /**< PositionY of picture at input of writeback pipeline(Overlay Window). */
    UInt32               indataFormat;
    /**< Input data Format. For valid values see #Fvid2_DataFormat. */
    UInt32               memType;
    /**< Memory type. For valid values see #Vps_VpdmaMemoryType.
     *   Note: Tiler Memory is not supported as of now, user should set this
     *   to VPS_VPDMA_MT_NONTILEDMEM. */
    Vps_DssDispcWbConfig wbCfg;
    /**< Video Configuration structure, applicable only for Writeback pipeline
     *   instances. */
    UInt32               wbMode;
    /**< M2M Writeback or capture Writeback mode. For valid
     *   values check #Vps_DssDispcWbMode. */
    UInt32               inNode;
    /**< Input pipe/overlay that is connected to writeback Pipeline
     *    For valid values see #Vps_DssDispcWbInNode. */
} VpsCore_DispDssWbParams;

typedef struct
{
    UInt32 src;
    /**< #Vps_DssDispcPipes */
} VpsCore_DssWbOpenParams;

typedef struct
{
    UInt32 inWidth;
    /**< Horizontal Size of picture at input of writeback pipeline .
     *    Should be same as overlay/forward pipe Width in case
     *    of TDA2XX. */
    UInt32 inHeight;
    /**< Verticle Size of picture at input of writeback pipeline
     *    Should be same as overlay/forward pipe Height in case
     *    of TDA2XX. */
    UInt32 outWidth;
    /**< Horizontal Size of picture at output of writeback pipeline
     *     whcih is going to memory */
    UInt32 outHeight;
    /**< Vertical Size of picture at output of writeback pipeline
     *     whcih is going to memory */
    UInt32 inPosX;
    /**< PositionX of picture at input of writeback pipeline(Overlay Window)
     *    Applicable only for TDA3xx platform. */
    UInt32 inPosY;
    /**< PositionY of picture at input of writeback pipeline(Overlay Window)
     *    Applicable only for TDA3xx platform. */
} VpsCore_DssWbRtParams;

typedef struct
{
    UInt32 wbBufferOverflow;
    /**<Wb pipeline Buffer overflow count. */
    UInt32 wbIncompleteError;
    /**<WB pipeline Incomplete Error count. */
}VpsCore_DssWbErrorStatus;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  VpsCore_dssWbInit
 *  \brief Initialize DSS WB Instance.
 *
 *  \param initParams       Valid init params
 *
 *  \return                 success: Valid #VpsCore_Inst
 *                          failure: NULL
 */
VpsCore_Inst VpsCore_dssWbInit(const VpsCore_DssWbInitParams *initParams);

/**
 *  VpsCore_dssWbDeInit
 *  \brief Free DSS WB instance.
 *
 *  \param pDssHandle     Valid #VpsCore_Inst.
 *
 *  \return               success: Valid #VpsCore_Inst
 *                        failure: NULL
 */
Int32 VpsCore_dssWbDeInit(VpsCore_Inst pDssWbHandle);

/**
 *  VpsCore_dssWbGetCoreOps
 *  \brief Returns the pointer to core function pointer table.
 *
 *  \return             Returns the pointer to core function pointer table.
 */
const VpsCore_Ops *VpsCore_dssWbGetCoreOps(void);

#ifdef __cplusplus
}
#endif

#endif /*VPSCORE_DSS_H_*/
