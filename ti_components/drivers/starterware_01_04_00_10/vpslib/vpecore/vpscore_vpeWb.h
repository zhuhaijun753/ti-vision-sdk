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
 *  \file vpscore_vpeWb.h
 *
 *  \brief VPS Core header file for VPE write back path.
 *  This core is used by both writeback capture as well as in M2M drivers.
 *  In capture mode, only one handle could be opened per instance, while in
 *  M2M mode each instance could be opened multiple times.
 *
 */

#ifndef VPSCORE_VPEWB_H_
#define VPSCORE_VPEWB_H_

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

/** \brief Instance ID for VPE Write-back path. */
#define VCORE_VWB_INST_WB0              (0U)
/**
 *  \brief Maximum number of instance. Change this macro accordingly when
 *  number of instance is changed.
 */
#define VCORE_VWB_NUM_INST              (1U)

/** \brief Maximum number of handles supported per VWB path instance. */
#define VCORE_VWB_MAX_HANDLES           (16U)

/**
 *  \brief Maximum number of channels supported for all handles.
 *  When the core is configured in capture mode, this is always 1.
 *  This is only used in mem-mem driver mode where software context makes sense.
 */
#define VCORE_VWB_MAX_CHANNELS          (40U)

/** \brief Luma index to the buffer address array in FVID frame structure. */
#define VCORE_VWB_Y_IDX                 (0U)
/** \brief Chroma index to the buffer address array in FVID frame structure. */
#define VCORE_VWB_CBCR_IDX              (1U)

/** \brief VWB VPDMA channel index for luma output port. */
#define VCORE_VWB_LUMA_IDX              (0U)
/** \brief VWB VPDMA channel index for chroma output port. */
#define VCORE_VWB_CHROMA_IDX            (1U)
/** \brief VWB VPDMA channel index for RGB output port. */
#define VCORE_VWB_RGB_IDX               (2U)

/** \brief Maximum number of VPDMA channels requried by VWB. */
#define VCORE_VWB_MAX_VPDMA_CH          (3U)

/** \brief VWB index for CSC HAL. */
#define VCORE_VWB_CSC_IDX               (0U)
/** \brief VWB index for VPE Top for configuring mux. */
#define VCORE_VWB_VPETOP_IDX            (1U)
/** \brief VWB index for VPDMA HAL. */
#define VCORE_VWB_VPDMA_IDX             (2U)
/** \brief Maximum number of HAL required by VWB. */
#define VCORE_VWB_MAX_HAL               (3U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct Vcore_VwbInitParams
 *  \brief Instance specific parameters used at init call.
 */
typedef struct
{
    UInt32              instId;
    /**< VWB Path Instance. */
    UInt32              maxHandle;
    /**< Maximum number of handles/channels to be supported per instance. */
    VpsHal_VpdmaChannel vpdmaCh[VCORE_VWB_MAX_VPDMA_CH];
    /**< VPE writeback VPDMA channel number required by core. */
    VpsHal_Handle       halHandle[VCORE_VWB_MAX_HAL];
    /**< Array to pass the HAL handles required by core. */
} Vcore_VwbInitParams;

/**
 *  struct Vcore_VwbRtParams
 *  \brief VWB runtime configuration parameters.
 */
typedef struct
{
    Vps_FrameParams *outFrmPrms;
    /**< Frame params for VPE writeback output frame.
     *   Pass NULL if no change is required or this output is not used
     *   by an instance. */
} Vcore_VwbRtParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  Vcore_vwbInit
 *  \brief VWB core init function.
 *  Initializes VWB core objects, allocates memory etc.
 *  This function should be called before calling any of VWB core API's.
 *
 *  \param numInst      [IN] Number of instance objects to be initialized.
 *  \param initPrms     [IN] Pointer to the init parameter containing
 *                      instance specific information. If the number of
 *                      instance is greater than 1, then this pointer
 *                      should point to an array of init parameter
 *                      structure of size numInstance.
 *
 *  \return             Returns 0 on success else returns error value.
 */
Int32 Vcore_vwbInit(UInt32                     numInst,
                    const Vcore_VwbInitParams *initPrms);

/**
 *  Vcore_vwbDeInit
 *  \brief VWB core exit function.
 *  Deallocates memory allocated by init function.
 *
 *  \return             Returns 0 on success else returns error value.
 */
Int32 Vcore_vwbDeInit(void);

/**
 *  Vcore_vwbGetCoreOps
 *  \brief Returns the pointer to core function pointer table.
 *
 *  \return             Returns the pointer to core function pointer table.
 */
const Vcore_M2mOps *Vcore_vwbGetCoreOps(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPSCORE_VPEWB_H_ */
