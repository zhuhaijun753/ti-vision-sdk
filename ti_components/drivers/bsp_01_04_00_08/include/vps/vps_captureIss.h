/******************************************************************************
 *                                                                            *
 * Copyright (c) 2014 Texas Instruments Incorporated - http://www.ti.com/     *
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
 *  \ingroup BSP_DRV_VPS_CAPTURE_API
 *  \defgroup BSP_DRV_VPS_CAPTURE_ISS_API VPS ISS Capture Driver API
 *
 *  The basic interface to capture video streams is defined /vps/vps_capture.h
 *      This interface lists additional APIs / config control for ISS based
 *      capture. The interface to control h/w specifics are listed as part of
 *      starterware interface. Staterware interface are available via the ISS
 *      capture driver.
 *
 *  \warning Following section describes the applicable parameters of generic
 *              capture.
 *          \li \b Vps_CaptCreateParams.videoIfMode valid values are
 *                              FVID2_VIFM_SCH_CSI2
 *                              FVID2_VIFM_SCH_LVDS
 *                              FVID2_VIFM_SCH_CPI
 *
 *          \li \b Vps_CaptCreateParams.videoIfWidth valid values are
 *                  When FVID2_VIFM_SCH_CSI2 - FVID2_VIFW_1LANES,
 *                          FVID2_VIFW_2LANES, FVID2_VIFW_3LANES,
 *                          FVID2_VIFW_4LANES
 *                  When FVID2_VIFM_SCH_LVDS - FVID2_VIFW_4LANES
 *                  When FVID2_VIFM_SCH_CPI - FVID2_VIFW_8BIT to
                                                FVID2_VIFW_16BIT
 *
 *  \warning Following feature of generic capture interface is not supported.
 *              Use of these features would be treated as a wrong argument.
 *
 *  \li Capture IOCTL \b IOCTL_VPS_CAPT_SET_FRAME_SKIP is not supported by ISS
 *          based capture.
 *  \li Buffer modes \b VPS_CAPT_BCM_CIRCULAR_FRM_REPEAT &
 *          \b VPS_CAPT_BCM_CIRCULAR_FRM_REPEAT is not supported.
 *  \li \b Vps_CaptFrameSkip is not supported. i.e. frames cannot be skipped.
 *  \li \b periodicCbEnable of #Vps_CaptCreateParams is not supported.
 *  \li \b muxModeStartChId of #Vps_CaptCreateParams is not applicable.
 *  \li \b descErrCount of #Vps_CaptChStatus is not supported.
 *
 *
 *  \note To control each sub block of ISS capture, Please refer the interface
 *          specific header defined in starterware <vps/iss/vps_cfg*.h>
 *  @{
 */

/**
 *  \file vps_captureIss.h
 *
 *  \brief Video Capture Driver API specific to ISS.
 */

#ifndef VPS_CAPTURE_ISS_H_
#define VPS_CAPTURE_ISS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <vps/vps_dataTypes.h>
#include <vps/iss/vps_isscommon.h>
#include <vps/iss/vps_cfgcal.h>

#include <vps/vps_capture.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 *  \ingroup BSP_DRV_IOCTL_VPS_CAPTURE
 *  \defgroup BSP_DRV_IOCTL_VPS_CAPTURE_ISS ISS Based Capture IOCTL's
 *  @{
 */
/**
 *  \brief Set CAL / ISP parameters.
 *
 *  This IOCTL should be used to configure the CAL to receive streams.
 *
 *  \attention Once the capture is started this IOCTL can't be invoked and
 *              if invoked, an error would be returned.
 *
 *  Once the capture is stopped, application could call this IOCTL to
 *  reconfigure.
 *
 *  \param cmd              [IN]  IOCTL_VPS_CAPT_SET_ISS_PARAMS
 *  \param cmdArgs          [IN]  const vpsissCalCfg_t *
 *  \param cmdArgsStatus    [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_VPS_CAPT_SET_ISS_PARAMS   (VPS_CAPT_ISS_IOCTL_BASE + 0x0001U)

/**
 *  \brief Identify ISP / NON-CAL Streams
 *
 *  When CAL/ISP is operated in on-the-fly mode, where in captured streams is
 *      routed to ISP for processing. The ISP could generate multiple streams
 *      from a single stream.
 *
 *  Applications are expected to identify ISP streams & its associated drivers
 *      stream ID.
 *      Use this control command to do the same.
 *
 *  \attention Once the capture is started this IOCTL can't be invoked and
 *              if invoked, an error would be returned.
 *
 *  Once the capture is stopped, application could use this IOCTL to
 *  reconfigure.
 *
 *  \param cmd              [IN]  IOCTL_VPS_CAPT_SET_ISS_STREAM_MAP
 *  \param cmdArgs          [IN]  const vpsissCalOtfStreamMapCfg_t *
 *  \param cmdArgsStatus    [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_VPS_CAPT_SET_ISS_STREAM_MAP   (VPS_CAPT_ISS_IOCTL_BASE + 0x0002U)

/**
 *  \brief Enable error notifications
 *
 *  When receiving from CSI2 interface or parallel interface, CAL provides
 *      mechanisms to detect / correct errors. Please refer
 *      vpsissCalErrorSource_t for supported errors.
 *  The errors are detected on instance basis i.e. these cannot be configured
 *      per handle.
 *
 *  \attention The callback provided by the applications, via this IOCTL, will
 *              called in interrupt context.
 *
 *  \attention The control command should be the last control command.
 *
 *  \param cmd              [IN]  IOCTL_VPS_CAPT_SET_ISS_ERR_PRMS
 *  \param cmdArgs          [IN]  const vpsissCalErrorCfg_t *
 *  \param cmdArgsStatus    [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_VPS_CAPT_SET_ISS_ERR_PRMS   (VPS_CAPT_ISS_IOCTL_BASE + 0x0003U)

/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Additional Open parameters required. Used to allocate sub-modules
 *          of CAL. The address of a instance of this structure should be
 *          specified.
 *  \code Vps_CaptCreateParams->pAdditionalArgs =
 *          (Vps_CaptIssOpenParams_t *)&cfg; \endcode
 */
typedef struct Vps_CaptIssOpenParams
{
    UInt32                subModules[VPS_ISS_CAL_MAX_STREAMS];
    /**< Identify the modules required for each stream.
        e.g. modulesReq[0] =
            IRM_CAL_SUB_PPI_ID | IRM_CAL_SUB_WR_DMA_ID resources are defined
            in vpsissCaptureSubModuleId_t
        Only 2 modules required, 1 to decode CSI2 and write received data */
    uint32_t              isCmplxIoCfgValid;
    /**< Specify if the complex IO configurations should be applied or the
            default config should be applied.
        TRUE - Complex IO configuration provided below is valid and will be
                applied.
        FALSE - Default complex IO configuration would be applied. */
    vpsissCalCmplxIoCfg_t cmplxIoCfg[VPS_ISS_CAL_MAX_CMPLXIO_INST];
    /**< Specify the CSI2 lanes configurations */
    void                 *otfOpenPrms;
    /**< Open Parameters for ISP */
    UInt32                csi2PhyClock;
    /**< Specify the CSI2 PHY Clock in MHz. e.g. if 400 MHz is the clock
            \code csi2PhyClock = 400; \endcode
        \warning In cases where CSI2 interface is not used. Set this to 400. */
    void                 *arg;
    /**< Not Used as of now */
} Vps_CaptIssOpenParams_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPS_CAPTURE_ISS_H_ */

/* @} */
