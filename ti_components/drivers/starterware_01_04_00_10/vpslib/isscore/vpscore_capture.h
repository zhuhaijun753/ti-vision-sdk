/**
 *  \file vpscore_capture.h
 *
 *  \brief  Provides interfaces to control / configure ISS based capture.
 *              Methods to configure capture via CAL OR LVDS.
 *
 *          With each instance of capture opened, one or more stream can be
 *          captured.
 */

/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 */
/*
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef VPSCORE_ISS_CAPTURE_H_
#define VPSCORE_ISS_CAPTURE_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <common/vpscore.h>
#include <vps/iss/vps_isscommon.h>
#include <vps/iss/vps_cfgcal.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Maximum number of opens supported per instance of core */
#define VCORE_ISS_CAPT_MAX_OPEN             (0x1U)

/** \brief IOCTL base address for the common IOCTLs listed below. TODO TBD
 *      Should derive from a common base */
#define VCORE_ISS_CAPT_BASE_IOCTL           (VPS_ISS_IOCTL_CAL_IOCTL_BASE)

/** \brief Configure CAL based on the config supplied by a pointer to instance
 *          of type vpsissCalCfg_t as argument.
 *          vpsissCalCfg_t defined in starterware_\include\vps\iss\vps_cfgcal.h
 */
#define VCORE_ISS_CAPT_CAL_SET_PARAMS       (VCORE_ISS_CAPT_BASE_IOCTL + 1U)

/** \brief CAL streams config, used to identify streams that are not written
 *          by CAL. Written by an entity outside CAL. (ISP)
 *          This is mandatory for OTF mode, not required for others. */
#define VCORE_ISS_CAPT_CAL_SET_STREAMS_MAP  (VCORE_ISS_CAPT_BASE_IOCTL + 2U)

/** \brief Enable/Disable error in CAL
 *    vpsissCalErrorCfg_t defined in starterware_\include\vps\iss\vps_cfgcal.h
 */
#define VCORE_ISS_CAPT_CAL_SET_ERR_PRMS     (VCORE_ISS_CAPT_BASE_IOCTL + 3U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct vcoreissCaptInterface
 *  \brief Different physical interface supported.
 */
typedef enum vcoreissCaptInterface
{
    VPSCORE_ISS_CAPT_IF_CSI2    = 0x0,
    /**< CSI2 Interface */
    VPSCORE_ISS_CAPT_IF_LVDS    = 0x1,
    /**< LVDS Interface */
    VPSCORE_ISS_CAPT_IF_CPI     = 0x2,
    /**< CPI / Parallel interface */
    VPSCORE_ISS_CAPT_IF_MAX     = 0x3,
    /**< End Marker */
    VPSCORE_ISS_CAPT_IF_FORCE_INT = 0x7FFFFFFF
                                    /**< This will ensure enum is not packed,
                                     *      will always be contained in int */
} vcoreissCaptInterface_t;

/**
 *  struct vcoreissCaptInitParams
 *  \brief Different modes of capture supported. LVDS & CAL based capture cannot
 *          not co-exist.
 */
typedef struct vcoreissCaptInitParams
{
    vpsissCaptInstId_t         instId;
    /**< Capture core instance ID, CAL OR LVDS */
    const VpsLib_PlatformData *halPlatformData;
    /**< HAL information */
    issemInstId_t              irqNum;
    /**< Interrupt number associated with this instance.
     *      The design / implementation, assumes single IRQ is used, if multi
     *      ple IRQ are used, we would require to guard ISR with interrupt
     *      enable / disable. */
    uint32_t                   subModules;
    /**< ISS Sub-modules required to be enabled for this instance */
    Ptr                        arg;
    /**< Not used for now, reserved */
} vcoreissCaptInitParams_t;

/**
 *  \brief Open Parameters.
 */
typedef struct vcoreissCaptOpenParams
{
    vcoreissCaptInterface_t captIf;
    /**< Type of interface
     *   Some interfaces are possible only in few instances,
     *   like CSI2 is possible only on CALA/B instances,
     #vcoreissCaptInterface_t  */
    uint32_t                numStreams;
    /**< Define number of streams that is required. */
    UInt32                  subModules[VPS_ISS_CAL_MAX_STREAMS];
    /**< Identify the modules required for each stream.
     *  e.g. modulesReq[0] =
     *      IRM_CAL_SUB_PPI_ID | IRM_CAL_SUB_WR_DMA_ID resources are defined
     *      in vpsissCaptureSubModuleId_t
     *  Only 2 modules required, 1 to decode CSI2 and write received data */
    uint32_t                isCmplxIoCfgValid;
    /**< Specify if the complex IO configurations should be applied or the
     *      default config should be applied.
     *  TRUE - Complex IO configuration provided below is valid and will be
     *          applied.
     *  FALSE - Default complex IO configuration would be applied. */
    vpsissCalCmplxIoCfg_t   cmplxIoCfg[VPS_ISS_CAL_MAX_CMPLXIO_INST];
    /**< Specify the CSI2 lanes configurations */
    uint32_t                csi2PhyClock;
    /**< Specify the CSI2 PHY clock in MHz. e.g. if 400 MHz is the clock
     *      \code csi2PhyClock = 400; */
    Ptr                     otfOpenPrms;
    /**< Open Parameters for ISP */
    Ptr                     arg;
    /**< Not Used as of now */
} vcoreissCaptOpenParams_t;

/**
 *  \brief Details returned by open operation
 */
typedef struct vcoreissCaptOpenRetParams
{
    int32_t  streamAllocError;
    /**< In case there no free streams available, status would be set to
     *      FVID2_EALLOC this variable will hold FVID2_EALLOC */
    uint32_t numStreamsAlloc;
    /**< Returns the number of streams allocated */
    UInt32   cportIdAlloc[VPS_ISS_CAL_MAX_STREAMS];
    /**< Instances of the sub modules allocated */
    UInt32   isStreamOpt[VPS_ISS_CAL_MAX_STREAMS];
    /**< Indicates streams that do not result in a write to memory.
     *      i.e. consumed internally by the CAL and for which memory need not
     *              be allocated. */
    Ptr      arg;
    /**< Not used as of now */
} vcoreissCaptOpenRetParams_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Function to initialize capture via ISS. Performs h/w initializations
 *          if required.
 *
 *  \param numInst          number of instances to be initialized
 *  \param initParams       Init parameters, containing HAL
 *                          initialization parameters.
 *  \param arg              not used as of now
 *
 *  \return                 FVID2_SOK: on successful completion, otherwise
 *                          appropriate error code.
 */
int32_t VpsCore_issCaptInit(
    uint32_t                  numInst,
    const vcoreissCaptInitParams_t *initParams,
    Ptr                       arg);

/**
 *  \brief DeInitializes Capture instances.
 *
 *  \param arg            Not used as of now.
 *
 *  \return                 FVID2_SOK: on successful completion, otherwise
 *                          appropriate error code.
 */
int32_t VpsCore_issCaptDeInit(Ptr arg);

/**
 *  \brief Returns the pointer to core function pointer table.
 *
 *  \return  Returns the pointer to core function pointer table. NULL on errors.
 */
const VpsCore_Ops *VpsCore_issCaptGetCoreOps(void);

/**
 *  \brief Returns the pointer to the core instance object
 *
 *  \return  A Valid pointer on success else a NULL pointer.
 */
VpsCore_Inst VpsCore_issCaptGetCoreInstObj(vpsissCaptInstId_t inst);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef VPSCORE_ISS_CAPTURE_H_ */
