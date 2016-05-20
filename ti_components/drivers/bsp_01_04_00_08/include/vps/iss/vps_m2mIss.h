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
 *  \ingroup BSP_DRV_VPS_M2M_INTF_API
 *  \defgroup BSP_DRV_VPS_M2M_ISS_API M2M ISS API
 *
 *  This modules define APIs for memory to memory operation using CAL-ISP
 *  in ISS.
 *  @{
 */

/**
 *  \file vps_m2mIss.h
 *
 *  \brief Interface specific to ISS memory to memory driver.
 */

#ifndef VPS_M2MISS_H_
#define VPS_M2MISS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <vps/iss/vps_cfgisp.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*
 *  ISP M2M driver.
 */

/*
 *  Macros used to identify different drivers, expected to be passed as the
 *  instance ID, during driver creation.
 *
 *  Note: These are read only macros. Don't modify the value of these macros.
 */
/** \brief ISS M2M Instance for the Path CAL -> ISP. */
#define VPS_M2M_ISS_INST_CAL_ISP        (0U)

/** \brief SIMCOP Instance for the Path DDR -> SIMCOP -> DDR. */
#define VPS_M2M_ISS_INST_SIMCOP         (1U)

/**
 *  \brief Maximum number of M2M ISS driver instance.
 *  \warning This is a read only macro. Don't modify the value of this macro.
 */
/** \brief Maximum number of M2M ISS driver instance.
 *  \warning  This is a read only macro. Don't modify the value of this macro.
 */
#define VPS_M2M_INTF_INST_MAX                   (5U)

/** \brief ISS M2M driver IOCTL base.
 *  VPS_M2M_IOCTL_BASE + 0x200U is already used by generic M2M interface. */
#define VPS_M2M_ISS_IOCTL_BASE          (VPS_M2M_IOCTL_BASE + 0x0300U)

/**
 *  \addtogroup BSP_DRV_IOCTL_VPS_M2M_ISS
 *  @{
 */

/**
 *  \brief Allocate ISS path.
 *
 *  This IOCTL is used to allocate the path in the isp module and
 *  in the CAL module. This IOCTL must be called first after creating
 *  the driver. None of the other IOCTL can be called before calling
 *  this IOCTL.
 *
 *  \param cmdArgs       [IN]  const Vps_M2mIssRescParams *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_VPS_ISS_M2M_ALLOC_RESOURCES   (VPS_M2M_ISS_IOCTL_BASE + 0x0000U)

/**
 *  \brief Set ISS parameters.
 *
 *  This IOCTL can be used to set the ISS hardware specific parameters.
 *  This IOCTL should be called after creating ISS M2M driver instance
 *  and before queueing or starting the M2M driver.
 *
 *  This IOCTL is used for setting up the input frame size, input
 *  frame format, enabling different input and output streams and for
 *  selecting the path for the GLBCE and NSF3 modules. It is also used
 *  for configuring HD/VD signal polarity.
 *
 *  This ioctl cannot be called from the ISR context.
 *
 *  \param cmdArgs       [IN]  const vpsissIspParams_t *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_VPS_ISS_M2M_SET_ISP_PARAMS    (VPS_M2M_ISS_IOCTL_BASE + 0x0001U)

/**
 *  \brief Get ISS parameters.
 *
 *  This IOCTL can be used to get the ISS hardware parameters.
 *  This IOCTL could be called at any time after creating ISS M2M
 *  driver instance. If it is not required to update all the
 *  parameters of ISP, this ioctl can be used to get the default parameters,
 *  update the required parameters and set them using
 *  #IOCTL_VPS_ISS_M2M_SET_ISP_PARAMS ioctl
 *
 *  This ioctl cannot be called from the ISR context.
 *
 *  \param cmdArgs       [IN]  vpsissIspParams_t *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_VPS_ISS_M2M_GET_ISP_PARAMS    (VPS_M2M_ISS_IOCTL_BASE + 0x0002U)

/**
 *  \brief Get Stream Information.
 *
 *  This IOCTL can be used to get particular stream information.
 *  Upper layer could using this information for allocating buffers for this
 *  stream.
 *
 *  This IOCTL will return stream information only if it is enabled, It
 *  will error if the stream is not enabled.
 *
 *  \param cmdArgs       [IN]  Vps_M2mStreamInfo *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_VPS_M2M_INTF_GET_STREAM_INFO  (VPS_M2M_ISS_IOCTL_BASE + 0x0003U)

/* @} */

/** \brief SIMCOP M2M driver IOCTL base.
 *  VPS_M2M_IOCTL_BASE + 0x200U is already used by generic M2M interface. */
#define VPS_M2M_SIMCOP_IOCTL_BASE          (VPS_M2M_IOCTL_BASE + 0x0400U)

/**
 *  \addtogroup BSP_DRV_IOCTL_VPS_M2M_ISS
 *  @{
 */
/**
 *  \brief Set SIMCOP parameters.
 *
 *  This IOCTL can be used to set the SIMCOP hardware specific parameters.
 *  This IOCTL should be called after creating SIMCOP M2M driver instance
 *  and before queueing or starting the M2M driver.
 *
 *  \param cmdArgs       [IN]  const vcoreSimcopCfgPrms_t *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_VPS_SIMCOP_M2M_SET_PARAMS   (VPS_M2M_SIMCOP_IOCTL_BASE + 0x0001U)

/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPS_M2MISS_H_ */

/*  @}  */
