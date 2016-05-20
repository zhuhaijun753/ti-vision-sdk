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
 *  \ingroup BSP_DRV_VPS_COMMON_API
 *  \addtogroup BSP_DRV_VPS_COMMON_DATATYPES VPS - Common Data Types and macros
 *
 *  @{
 */

/**
 *  \file vps_isscommon.h
 *
 *  \brief ISS - Common API datatypes
 */

#ifndef VPS_ISSCOMMON_H_
#define VPS_ISSCOMMON_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <fvid2/fvid2_dataTypes.h>
#include <vps/iss/vps_cfgldc.h>
#include <vps/iss/vps_cfgvtnf.h>

/* ========================================================================== */
/*          Include HW specific config constants, structures                  */
/* ========================================================================== */

#ifdef VPS_ISS_BUILD
#include <vps/iss/vps_cfgipipe.h>
#include <vps/iss/vps_cfgisif.h>
#include <vps/iss/vps_cfgrsz.h>
#include <vps/iss/vps_cfgh3a.h>
#include <vps/iss/vps_cfgipipeif.h>
#include <vps/iss/vps_cfgcnf.h>
#endif /* VPS_ISS_BUILD */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define VPS_ISS_IOCTL_IPIPE_IOCTL_BASE      (uint32_t) (0x00000000U)
/**< IPIPE Ioctl base */
#define VPS_ISS_IOCTL_IPIPE_IOCTL_NUM       (uint32_t) (0x10U)
/**< Number of control commands */
#define VPS_ISS_IOCTL_IPIPE_IOCTL_END       (VPS_ISS_IOCTL_IPIPE_IOCTL_BASE + \
                                             VPS_ISS_IOCTL_IPIPE_IOCTL_NUM -  \
                                             1U)
/**< Value of last control command */

#define VPS_ISS_IOCTL_ISIF_IOCTL_BASE       (VPS_ISS_IOCTL_IPIPE_IOCTL_END)
/**< ISIF Ioctl base */
#define VPS_ISS_IOCTL_ISIF_IOCTL_NUM        (uint32_t) (0x10U)
/**< Number of control commands */
#define VPS_ISS_IOCTL_ISIF_IOCTL_END        (VPS_ISS_IOCTL_ISIF_IOCTL_BASE + \
                                             VPS_ISS_IOCTL_ISIF_IOCTL_NUM -  \
                                             1U)
/**< Value of last control command */

#define VPS_ISS_IOCTL_RSZ_IOCTL_BASE        (VPS_ISS_IOCTL_ISIF_IOCTL_END)
/**< RSZ Ioctl base */
#define VPS_ISS_IOCTL_RSZ_IOCTL_NUM         (uint32_t) (0x10U)
/**< Number of control commands */
#define VPS_ISS_IOCTL_RSZ_IOCTL_END         (VPS_ISS_IOCTL_RSZ_IOCTL_BASE + \
                                             VPS_ISS_IOCTL_RSZ_IOCTL_NUM -  \
                                             1U)
/**< Value of last control command */

#define VPS_ISS_IOCTL_H3A_IOCTL_BASE        (uint32_t) ( \
        VPS_ISS_IOCTL_RSZ_IOCTL_END)
/**< H3A Ioctl base */
#define VPS_ISS_IOCTL_H3A_IOCTL_NUM         (uint32_t) (0x10U)
/**< Number of control commands */
#define VPS_ISS_IOCTL_H3A_IOCTL_END         (VPS_ISS_IOCTL_H3A_IOCTL_BASE + \
                                             VPS_ISS_IOCTL_H3A_IOCTL_NUM -  \
                                             1U)
/**< Value of last control command */

#define VPS_ISS_IOCTL_IPIPEIF_IOCTL_BASE  (VPS_ISS_IOCTL_H3A_IOCTL_END)
/**< IPIPEIF Ioctl base */
#define VPS_ISS_IOCTL_IPIPEIF_IOCTL_NUM   (uint32_t) (0x10U)
/**< Number of control commands */
#define VPS_ISS_IOCTL_IPIPEIF_IOCTL_END   (VPS_ISS_IOCTL_IPIPEIF_IOCTL_BASE + \
                                           VPS_ISS_IOCTL_IPIPEIF_IOCTL_NUM -  \
                                           1U)
/**< Value of last control command */

#define VPS_ISS_IOCTL_NSF3_IOCTL_BASE       (VPS_ISS_IOCTL_IPIPEIF_IOCTL_END)
/**< NSF3 Ioctl base */
#define VPS_ISS_IOCTL_NSF3_IOCTL_NUM        (uint32_t) (0x10U)
/**< Number of control commands */
#define VPS_ISS_IOCTL_NSF3_IOCTL_END        (VPS_ISS_IOCTL_NSF3_IOCTL_BASE + \
                                             VPS_ISS_IOCTL_NSF3_IOCTL_NUM -  \
                                             1U)
/**< Value of last control command */

#define VPS_ISS_IOCTL_GLBCE_IOCTL_BASE      (VPS_ISS_IOCTL_NSF3_IOCTL_END)
/**< GLBCE Ioctl base */
#define VPS_ISS_IOCTL_GLBCE_IOCTL_NUM       (uint32_t) (0x10U)
/**< Number of control commands */
#define VPS_ISS_IOCTL_GLBCE_IOCTL_END       (VPS_ISS_IOCTL_GLBCE_IOCTL_BASE + \
                                             VPS_ISS_IOCTL_GLBCE_IOCTL_NUM -  \
                                             1U)
/**< Value of last control command */

#define VPS_ISS_IOCTL_CNF_IOCTL_BASE        (VPS_ISS_IOCTL_GLBCE_IOCTL_END)
/**< CNF Ioctl base */
#define VPS_ISS_IOCTL_CNF_IOCTL_NUM         (uint32_t) (0x5U)
/**< Number of control commands */
#define VPS_ISS_IOCTL_CNF_IOCTL_END         (VPS_ISS_IOCTL_CNF_IOCTL_BASE + \
                                             VPS_ISS_IOCTL_CNF_IOCTL_NUM -  \
                                             1U)
/**< Value of last control command */

#define VPS_ISS_IOCTL_CAL_IOCTL_BASE        (VPS_ISS_IOCTL_CNF_IOCTL_END)
/**< CAL Ioctl base */
#define VPS_ISS_IOCTL_CAL_IOCTL_NUM         (0x10U)
/**< Number of control commands */
#define VPS_ISS_IOCTL_CAL_IOCTL_END         (VPS_ISS_IOCTL_CAL_IOCTL_BASE + \
                                             VPS_ISS_IOCTL_CAL_IOCTL_NUM -  \
                                             1U)
/**< Value of last control command */

#define VPS_ISS_IOCTL_LVDS_IOCTL_BASE       (VPS_ISS_IOCTL_CAL_IOCTL_END)
/**< LVDS Ioctl base */
#define VPS_ISS_IOCTL_LVDS_IOCTL_NUM        (0x10U)
/**< Number of control commands */
#define VPS_ISS_IOCTL_LVDS_IOCTL_END        (VPS_ISS_IOCTL_LVDS_IOCTL_BASE + \
                                             VPS_ISS_IOCTL_LVDS_IOCTL_NUM -  \
                                             1U)
/**< Value of last control command */

#define VPS_ISS_IOCTL_CPI_IOCTL_BASE        (VPS_ISS_IOCTL_LVDS_IOCTL_END)
/**< CPI Ioctl base */
#define VPS_ISS_IOCTL_CPI_IOCTL_NUM         (0x10U)
/**< Number of control commands */
#define VPS_ISS_IOCTL_CPI_IOCTL_END         (VPS_ISS_IOCTL_CPI_IOCTL_BASE + \
                                             VPS_ISS_IOCTL_CPI_IOCTL_NUM -  \
                                             1U)
/**< Value of last control command */

#define VPS_ISS_IOCTL_ISP_IOCTL_BASE        (VPS_ISS_IOCTL_CPI_IOCTL_END)
/**< ISP Ioctl base */
#define VPS_ISS_IOCTL_ISP_IOCTL_NUM         (0x10U)
/**< Number of control commands */
#define VPS_ISS_IOCTL_ISP_IOCTL_END         (VPS_ISS_IOCTL_ISP_IOCTL_BASE + \
                                             VPS_ISS_IOCTL_ISP_IOCTL_NUM -  \
                                             1U)
/**< Value of last control command */

/* ========================================================================== */
/*                                 Function Types                             */
/* ========================================================================== */
/**
 *  \brief Defines expected function type that could be called by drivers on
 *          error conditions. Please refer driver specific header files on
 *          methods to attach callbacks on errors.
 *
 *  \param  event       Pointer to an array that holds event (s) that have
 *                          occurred. The numEvents determine the number of
 *                          elements that could accessed.
 *  \param  numEvents   Number of events (error conditions) that were detected.
 *  \param  arg         Argument provided while configuring the error parameters
 */
typedef void (*vpsissErrorCallBack)(const UInt32 *event,
                                    UInt32        numEvents,
                                    Ptr           arg);

/**
 *  struct vpsissCaptInstId
 *  \brief Different instances of capture. As name suggests, each instance is
 *          associated with a particular method of capture. Multiple instances
 *          can co-exist, provided co-existence is supported in the h/w.
 */
typedef enum vpsissCaptInstId
{
    VPS_ISS_CAPT_CAL_A_ID = 0U,
    /**< Capture CSI2 streams via CAL. Requires to be first enum.
     *      This is requires to start with 0x0. Used an index internally in
     *      core */
    VPS_ISS_CAPT_CAL_A_CPI = 1U,
    /**< Capture From CPI - Via VPORT of IPIPEIF. Essentially via Parallel OR
     *      LVDS input which are interfaced to CPI port. */
    VPS_ISS_CAPT_CAL_A_OTF0_ID = 2U,
    /**< Capture CSI2 streams via CAL. Requires to be first enum. */
    VPS_ISS_CAPT_INST_MAX_ID = 3U,
    /**< Enum end marker */
    VPS_ISS_CAPT_INST_FORCE_INT = 0x7FFFFFFF
                        /**< This will ensure enum is not packed,
                         *      will always be contained in int */
} vpsissCaptInstId_t;   /**< vpsissCaptInstId_t */

/**
 *  \brief ISS output Stream ID
 */
typedef enum vpsissStreamId
{
    VPS_ISS_STREAM_CAL_RD_INPUT_0 = 0x0,
    /**< CAL Read Input */
    VPS_ISS_STREAM_ID_RSZ_A = 0x1,
    /**< Id for output from RSZ_A */
    VPS_ISS_STREAM_ID_INPUT_N1 = 0x2,
    /**< Id for the Previous input */
    VPS_ISS_STREAM_ID_RSZ_B = 0x3,
    /** Id for output from RSZ_B */
    VPS_ISS_STREAM_ID_BSC = 0x4,
    /** Id for output BSC data */
    VPS_ISS_STREAM_ID_BOXCAR = 0x5,
    /** Id for output Boxcar data */
    VPS_ISS_STREAM_ID_HIST = 0x6,
    /** Id for output Histogram data */
    VPS_ISS_STREAM_ID_AF = 0x7,
    /** Id for output AutoFocus Data */
    VPS_ISS_STREAM_ID_AEWB = 0x8,
    /** Id for output AutoWhiteBalance Data */
    VPS_ISS_STREAM_ID_MAX = 0x9
                    /**< Should be the last enum */
} vpsissStreamId_t; /**< vpsissStreamId_t */

/**
 *  enum vpsissCaptureSubModuleId
 *  \brief Different sub-modules with in the CAL block.
 */
typedef enum vpsissCaptureSubModuleId
{
    VPS_ISS_CAPT_CAL_SUB_MIN_ID = 0x000,
    /**< Begin marker */
    VPS_ISS_CAPT_CAL_SUB_PPI_ID = 0x001,
    /**< PPI Interface, one per instance  */
    VPS_ISS_CAPT_CAL_SUB_PIX_EXTRACT_ID = 0x002,
    /**< Pixel extract */
    VPS_ISS_CAPT_CAL_SUB_DPCM_DEC_ID = 0x004,
    /**< DPCM Decode */
    VPS_ISS_CAPT_CAL_SUB_DPCM_ENC_ID = 0x008,
    /**< DPCM Encode */
    VPS_ISS_CAPT_CAL_SUB_PIX_PACK_ID = 0x010,
    /**< Pixel packing */
    VPS_ISS_CAPT_CAL_SUB_BYS_OUT_ID = 0x020,
    /**< BYS Out */
    VPS_ISS_CAPT_CAL_SUB_BYS_IN_ID = 0x040,
    /**< BYS IN */
    VPS_ISS_CAPT_CAL_SUB_VPORT_ID = 0x080,
    /**< BYS IN */
    VPS_ISS_CAPT_CAL_SUB_DMA_RD_ID = 0x100,
    /**< DMA Read */
    VPS_ISS_CAPT_CAL_SUB_DMA_WR_ID = 0x200,
    /**< DMA Write */
    VPS_ISS_CAPT_CAL_SUB_CSI2_ID = 0x400,
    /**< cport ID */
    VPS_ISS_CAPT_CAL_SUB_CPORT_ID = 0x800,
    /**< cport ID */
    VPS_ISS_CAPT_LVDS_ID = 0x1000,
    /**< LVDS Port ID */
    VPS_ISS_CAPT_CPI_ID = 0x2000,
    /**< CPI / Parallel interface */
    VPS_ISS_CAPT_MOD_MAX_ID = 0x2001,
    /**< Enum end marker */
    VPS_ISS_CAPT_MOD_FORCE_INT = 0x7FFFFFFF
                                /**< This will ensure enum is not packed,
                                 *      will always be contained in int */
} vpsissCaptureSubModuleId_t;   /**< vpsissCaptureSubModuleId_t */

/**  \brief Enum for selecting the ISP modules, Selecting a module enables
 *         the clock for that module at the open time. All the modules
 *         required for the m2m instance must be enabled.
 */
typedef enum vpsissIspModuleId
{
    VPS_ISS_ISP_MODULE_IPIPEIF = 0x0,
    /**< IPIPEIF Module */
    VPS_ISS_ISP_MODULE_NSF3 = 0x1,
    /**< NSF3 Module */
    VPS_ISS_ISP_MODULE_GLBCE = 0x2,
    /**< GLBCE Module */
    VPS_ISS_ISP_MODULE_ISIF = 0x3,
    /**< ISIF Module */
    VPS_ISS_ISP_MODULE_IPIPE = 0x4,
    /**< IPIPE Module */
    VPS_ISS_ISP_MODULE_RSZ = 0x5,
    /**< Resizer Module */
    VPS_ISS_ISP_MODULE_H3A = 0x6,
    /**< H3A module */
    VPS_ISS_ISP_MODULE_CNF = 0x7,
    /**< H3A module */
    VPS_ISS_ISP_MAX_MODULE = 0x8,
    /**< Last Enum, user for error checking and array size */
    VPS_ISS_ISP_MODULE_FORCE_INT = 0x7FFFFFFF
                        /**< This will ensure enum is not packed,
                         *      will always be contained in int */
} vpsissIspModuleId_t;  /**< vpsissIspModuleId_t */

/**  \brief Enum for selecting GLBCE Path, It could be either present
 *         in ISP or in CAL path
 */
typedef enum vpsissGlbcePath
{
    VPS_ISS_GLBCE_PATH_DISABLED = 0x0,
    /**< GLBCE is Disabled and is not enabled in any path */
    VPS_ISS_GLBCE_PATH_CAL = 0x1,
    /**< GLBCE is enabled on CAL Bys path */
    VPS_ISS_GLBCE_PATH_ISP = 0x2,
    /**< GLBCE is enabled on ISP IPIPEIF->IPIPE path */
    VPS_ISS_GLBCE_PATH_MAX = 0x3,
    /**< Last enum, used for error checking */
    VPS_ISS_GLBCE_PATH_FORCE_INT = 0x7FFFFFFF
                        /**< This will ensure enum is not packed,
                         *      will always be contained in int */
} vpsissGlbcePath_t;    /**< vpsissGlbcePath_t */

/**  \brief Enum for selecting NSF3 Path, It could be either present
 *         in ISP or in CAL path
 */
typedef enum vpsissNsf3Path
{
    VPS_ISS_NSF3_PATH_DISABLED = 0x0,
    /**< NSF3 is Disabled and is not enabled in any path */
    VPS_ISS_NSF3_PATH_CAL = 0x1,
    /**< NSF3 is enabled on CAL Bys path */
    VPS_ISS_NSF3_PATH_ISP = 0x2,
    /**< NSF3 is enabled on ISP IPIPEIF->IPIPE path */
    VPS_ISS_NSF3_PATH_MAX = 0x3,
    /**< Last enum, used for error checking */
    VPS_ISS_NSF3_PATH_FORCE_INT = 0x7FFFFFFF
                    /**< This will ensure enum is not packed,
                     *      will always be contained in int */
} vpsissNsf3Path_t; /**< vpsissNsf3Path_t */

/**
 *  \brief SIMCOP output Stream ID
 */
typedef enum vpsissSimcopStreamId
{
    VPS_SIMCOP_STREAM_ID_CUR_FRAME = 0x0,
    /**< Identifier for current frame */
    VPS_SIMCOP_STREAM_ID_PREV_FRAME = 0x1,
    /**< Identifier for previous frame */
    VPS_SIMCOP_STREAM_ID_OUT_FRAME = 0x2,
    /**< Identifier for output frame */
    VPS_SIMCOP_STREAM_ID_MESH_TABLE = 0x3,
    /**< Identifier for LDC mesh table frame */
    VPS_SIMCOP_STREAM_ID_MAX = VPS_SIMCOP_STREAM_ID_MESH_TABLE,
    /**< Last enum. Used for error checks or specifying stream count */
    VPS_SIMCOP_STREAM_ID_FORCE_INT = 0x7FFFFFFF
                            /**< This will ensure enum is not packed,
                             *      will always be contained in int */
} vpsissSimcopStreamId_t;   /**< vpsissSimcopStreamId_t */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Resources allocated instances. 0xFFFFFFFF in case not allocated.
 *          Otherwise valid instance number
 */
typedef struct vpsissCaptureBlocks
{
    UInt32 ppi;
    /**< PPI interface instance,  0xFFFFFFFF in case not allocated. Otherwise
     *      valid instance number */
    UInt32 pixExtract;
    /**< Pixel Extract instance */
    UInt32 dpmDecode;
    /**< DPM Decode instance */
    UInt32 dpmEncode;
    /**< DPM Encode instance */
    UInt32 pixPack;
    /**< Pixel Pack instance */
    UInt32 bysOut;
    /**< BYS Out instance */
    UInt32 bysIn;
    /**< BYS IN instance */
    UInt32 vPort;
    /**< VPORT IN instance */
    UInt32 rdDma;
    /**< RD Dma instance */
    UInt32 wrDma;
    /**< WR Dma instance */
    UInt32 csi2Ctx;
    /**< CSI2 processing context */
    UInt32 cport;
    /**< CPort ID */
    UInt32 lvds;
    /**< LVDS port */
    UInt32 cpi;
    /**< Parallel / CPI port */
} vpsissCaptureBlocks_t;

/**
 *  \brief Open Parameters
 */
typedef struct vpsissIspOpenParams
{
    uint32_t isModuleReq[VPS_ISS_ISP_MAX_MODULE];
    /**< Flag to indicate whether the given module is required or not
     *   vpsIssIspModuleId_t is used as an index into this array.
     *   Module Hal will be opened only if the module is enabled here.
     *   If the module is not openend, its functional clock will not
     *   be enabled, which saves the power.
     *   If the modules is set to not required here, it can not be
     *   enabled later on any time, setConfig for the module will
     *   return error. */
    Ptr      arg;
    /**< Not Used as of now */
} vpsissIspOpenParams_t;

/**
 *  \brief Open Return Parameters, contain return status and module
 *         caused failure
 */
typedef struct vpsissIspOpenRetParams
{
    int32_t             status;
    /**< Status of the open, return value of the open */
    vpsissIspModuleId_t module;
    /**< the first module, which failed to open */
    Ptr                 arg;
    /**< Not used as of now */
} vpsissIspOpenRetParams_t;

/**
 *  \brief Open Parameters, currently not used
 */
typedef struct vpsissSimcopOpenParams
{
    uint32_t mode;
    /**< Mode in which SIMCOP needs to be configured
     #vpsissSimcopM2MMode_t */
    Ptr      arg;
    /**< Not Used as of now */
} vpsissSimcopOpenParams_t;

/**
 *  \brief Open Parameters, currently not used
 */
typedef struct vpsissSimcopCfgPrms
{
    vpsissldcConfig_t  ldcCfg;
    /**< Configuration for LDC - Ignored if mode = VPSCORE_ISS_VTNF_ONLY */
    vpsissvtnfConfig_t vtnfCfg;
    /**< Configuration for VTNF - Ignored if mode = VPSCORE_ISS_LDC_ONLY */
    uint32_t           inpFrmPitch;
    /**< Input frames line stride */
    uint32_t           prevFrmPitch;
    /**< Previous / reference frames line stride */
    uint32_t           outFrmPitch;
    /**< Output frames line stride */
    uint32_t           inFrameWidth;
    /**< Input frames width */
    uint32_t           inFrameHeight;
    /**< Input frames height */
    Fvid2_CropConfig   cropCfg;
    /**< Selection section of input frame to be processed */
    uint32_t           blkWidth;
    /**< Sub Block Width */
    uint32_t           blkHeight;
    /**< Sub Block Height */
    Ptr                arg;
    /**< Not Used as of now */
}vpsissSimcopCfgPrms_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPS_ISSCOMMON_H_ */

/* @} */

