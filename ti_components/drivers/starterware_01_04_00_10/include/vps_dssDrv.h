/* ======================================================================
 *   Copyright (C) 2013 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */
/**
 *  \defgroup BSP_DRV_VIP_STARTERWARE_API VIP Starterware Driver API
 *
 *  @{
 */

/**
 *  \file vpsdrv_displayApi.c
 *
 *  \brief File containing the VPS display driver APIs.
 *
 */
#ifndef VPS_DSSDRV_H_
#define VPS_DSSDRV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <dispcore/vpscore_dss.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*
 *  Macros for different driver instance numbers to be passed as instance ID
 *  at the time of driver create.
 *  Note: These are read only macros. Don't modify the value of these macros.
 */

/**
 *  \name DSS Display Instance ID's
 *
 *  @{
 */

/** \brief Video Pipeline 1 display driver instance number. */
#define VPSDRV_DISP_INST_DSS_VID1          (0U)

/** \brief Video Pipeline 2 display driver instance number. */
#define VPSDRV_DISP_INST_DSS_VID2          (1U)

/**
 *  \brief Video Pipeline 3 display driver instance number.
 *  This video instance is not applicable for TDA3xx platform
 */
#define VPSDRV_DISP_INST_DSS_VID3          (2U)

/** \brief Graphics Pipeline 1 display driver instance number. */
#define VPSDRV_DISP_INST_DSS_GFX1          (3U)

#define VPS_DISP_INST_MAX                  (4U)

/** \brief Forward declaration for instance object. */
typedef struct VpsDrv_DispInstObj_t VpsDrv_DispInstObj;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct VpsDrv_DispInitParams
 *  \brief Instance specific parameters used at init call.
 */
typedef struct
{
    UInt32             drvInstId;
    /**< Instance ID. */
    /* Dc_NodeNum              dctrlNodeNum; */
    /**< Node number for registering to display controller. */
    VpsCore_Inst       coreInstObj;
    /**< Core instance object used in core open. */
    const VpsCore_Ops *coreOps;
    /**< Core function pointers. */
} VpsDrv_DispInitParams;

/**
 *  \brief Platform specific data containing base address information of
 *  DSS module.
 */
typedef struct
{
    VpsDrv_DispInitParams DispDrvInitPrms[VPS_DISP_INST_MAX];
    /**< Capture driver init parameters. */
} VpsDrv_DssPlatformData;

/**
 *  \brief Per instance information.
 */
struct VpsDrv_DispInstObj_t
{
    UInt32             drvInstId;
    /**< Instance ID. */
    VpsCore_Inst       coreInstObj;
    /**< Core instance object used in core open. */
    const VpsCore_Ops *coreOps;
    /**< Core function pointers. */
    VpsCore_Handle     coreHandle;
    /**< Core handle. */
    UInt32             isPrevBufRep;
    /**< Flag to check if previous buffer is repeated. */
    UInt32             standard;
    /**< VENC Standard like NTSC, 1080p etc to which the display driver
     *   path is connected. For valid values see #FVID2_Standard. */
    UInt32             dispWidth;
    /**< Width of the display at the VENC in pixels to which the
     *   display driver path is connected. */
    UInt32             dispHeight;
    /**< Height of the display at the VENC in linesto which the
     *   display driver path is connected. */
    UInt32             vencId;
    /**< Venc ID to which this display instance is connected. */
};

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
} VpsDrv_DispDssParams;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  Vps_init
 *  \brief Initializes all HAL/CORE/DRIVER SW modules for VPS starterware
 *
 *  \param none
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 Vps_init(Ptr args);

/**
 *  Vps_deInit
 *  \brief Initializes all HAL/CORE/DRIVER SW modules for VPS starterware
 *
 *  \param none
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 Vps_deInit(Ptr args);

/**
 *  VpsDrv_dssOpen
 *  \brief Open a capture driver instance as per specified parameters
 *
 *  \param vipInstId         Dss Instance ID #dssInstId
 *  \param DssOpenParams Capture Driver parameters #VpsCore_OpenPrms
 *  \param dssOpenParams     VIP specific parameters #VpsCore_DssOpenParams
 *
 *  \return                  Capture handle #VpsDrv_CaptInstObj on success
 *                           NULL pointer on failure
 *
 */
VpsDrv_DispInstObj *VpsDrv_dssOpen(
    UInt32                 dssInstId,
    VpsCore_OpenPrms      *OpenParams,
    VpsCore_DssOpenParams *dssOpenParams);

/**
 *  VpsDrv_dssClose
 *  \brief Close the specified capture handle
 *
 *  \param pObj         Dss Handle to close
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_dssClose(VpsDrv_DispInstObj *pObj);

/**
 *  VpsDrv_dssStart
 *  \brief Start capture on the specified capture handle
 *
 *  \param pObj         Capture Handle #VpsDrv_DispInstObj
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_dssStart(VpsDrv_DispInstObj *pObj);

/**
 *  VpsDrv_dssStop
 *  \brief Stop capture on the specified capture handle
 *
 *  \param pObj         Capture Handle #VpsDrv_DispInstObj
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_dssStop(VpsDrv_DispInstObj *pObj);

/**
 *  VpsDrv_dssSetParams
 *  \brief Set capture params for specified handle
 *
 *  \param instObj           Capture Handle #VpsDrv_DispInstObj
 *  \param dssPrms        Path configuration #VpsCore_DispDssParams
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_dssSetParams(VpsDrv_DispInstObj         *instObj,
                          const VpsDrv_DispDssParams *dssPrms);

/**
 *  VpsDrv_dssGetParams
 *  \brief Get capture params for specified handle. If not configured, this will
 *  return a default configuration
 *
 *  \param pObj         Capture Handle #VpsDrv_DispInstObj
 *  \param dssParams    Pointer to #VpsCore_DispDssParams where configuration
 *                                           will be copied
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_dssGetParams(VpsDrv_DispInstObj    *pObj,
                          VpsCore_DispDssParams *dssParams);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* VPS_DSSDRV_H_ */

/* @} */
