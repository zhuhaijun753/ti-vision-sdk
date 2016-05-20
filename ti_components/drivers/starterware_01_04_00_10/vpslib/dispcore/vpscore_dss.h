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
 *  \file vpscore_dss.h
 *
 *  \brief VPS display DSS core interface.
 *  This file defines the interface for the DSS display core.
 *
 */

#ifndef VPSCORE_DSS_H_
#define VPSCORE_DSS_H_

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
#define VCORE_DSS_COMMON_IOCTL_BASE     (0x00000000U)
/** \brief IOCTL base address for the custom IOCTLs of each cores. */
#define VCORE_DSS_CUSTOM_IOCTL_BASE     (0x00000100U)

/**
 *  \brief Set DSS CSC Coefficients IOCTL.
 *
 *  This IOCTL can be used to set the CSC coefficients.
 *  Note: Default BT601 coefficients are set.
 *
 *  \param cmdArgs       [IN] const Vps_DssCscCoeff *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure
 */
#define VCORE_DSS_SET_CSC_COEFF  (VCORE_DSS_COMMON_IOCTL_BASE + 0x01U)
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    UInt32        dispcIrqNumber;
    /**< DISPC IRQ number at CPU level INTC. */
    VpsHal_Handle vidHandle[VPSHAL_DSS_DISPC_PIPE_MAX_INST];
    VpsHal_Handle ovlHandle[VPSHAL_DSS_DISPC_OVLY_MAX_INST];
} VpsCore_DssInitParams;

typedef struct
{
    UInt32 standard;
    /**< VENC Standard like NTSC, 1080p etc to which the display driver
     *   path is connected. For valid values see #FVID2_Standard. */
    UInt32 dispWidth;
    /**< Width of the display at the VENC in pixels to which the
     *   display driver path is connected. */
    UInt32 dispHeight;
    /**< Height of the display at the VENC in linesto which the
     *   display driver path is connected. */
    UInt32 vencId;
    /**< Venc ID to which this display instance is connected. */
} VpsCore_DssOpenRetParams;

/**
 *  \brief DSS parameters used in set/get DSS params.
 */
typedef struct
{
    Fvid2_Format           inFmt;
    /**< Input FVID frame format. */
    UInt32                 tarWidth;
    /**< Horizontal Size of picture at output of video pipeline
     *   Not used in case of Graphics instance. */
    UInt32                 tarHeight;
    /**< Verticle Size of picture at output of video pipeline
     *   Not used in case of Graphics instance. */
    UInt32                 posX;
    /**< X position of the frame in the output Video Window . */
    UInt32                 posY;
    /**< Y position of the frame in the output Video Window . */
    UInt32                 memType;
    /**< Memory type. For valid values see #Vps_VpdmaMemoryType.
     *   Note: Tiler Memory is not supported as of now, user should set this
     *   to VPS_VPDMA_MT_NONTILEDMEM. */
    Vps_DssDispcVidConfig *vidCfg;
    /**< Video Configuration structure, applicable only for Video pipeline
     *   instances, if NULL default configuration will be used */
    Vps_DssDispcGfxConfig *gfxCfg;
    /**< Graphics Configuration structure, applicable only for Graphics pipeline
     *   instances, if NULL default configuration will be used */
} VpsCore_DispDssParams;

typedef struct
{
    UInt32 src;
    /**< #Vps_DssDispcPipes */
} VpsCore_DssOpenParams;

typedef struct
{
    UInt32 vidBufferUnderflow;
    /**<VID pipeline Buffer underflow count. */
}VpsCore_DssVidErrorStatus;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  VpsCore_dssInit
 *  \brief Initialize DSS Instance.
 *
 *  \param initParams       Valid handle returned by #TODO function.
 *
 *  \return                 success: Valid #VpsCore_Inst
 *                          failure: NULL
 */
VpsCore_Inst VpsCore_dssInit(const VpsCore_DssInitParams *initParams);

/**
 *  VpsCore_dssDeInit
 *  \brief Free DSS instance.
 *
 *  \param pDssHandle     Valid #VpsCore_Inst.
 *
 *  \return               success: Valid #VpsCore_Inst
 *                        failure: NULL
 */
Int32 VpsCore_dssDeInit(VpsCore_Inst pDssHandle);

/**
 *  VpsCore_dssGetCoreOps
 *  \brief Returns the pointer to core function pointer table.
 *
 *  \return             Returns the pointer to core function pointer table.
 */
const VpsCore_Ops *VpsCore_dssGetCoreOps(void);

#ifdef __cplusplus
}
#endif

#endif /*VPSCORE_DSS_H_*/
