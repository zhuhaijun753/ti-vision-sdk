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
 *  \ingroup BSP_DRV_VPS_API
 *  \defgroup BSP_DRV_VPS_DCTRL_API Display Controller API
 *
 *  @{
 */

/**
 *  \file vps_displayCtrl.h
 *
 *  \brief Display Controller Driver
 *  Generic Display Controller Driver Interface file.
 */

#ifndef VPS_DISPLAY_CTRL_H_
#define VPS_DISPLAY_CTRL_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <vps/vps_dataTypes.h>
#include <vps/vps_displayCtrlDataTypes.h>
#include <vps/vps.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*
 *  Macros for display controller instance numbers to be passed as instance ID
 *  at the time of driver create.
 *  Note: These are read only macros. Don't modify the value of these macros.
 */

/**
 *  \name DCTRL Instance ID's
 *
 *  @{
 */

/** \brief Display controller instance 0. */
#define VPS_DCTRL_INST_0                (0U)

/* @} */

/**
 *  \addtogroup BSP_DRV_IOCTL_VPS_DCTRL
 *  @{
 */

/** \brief Command to set the entire VPS display path configuration in
 *  one shot.
 *
 *  All the VPS modules handled by the Display Controller can be
 *  represented by a graph, where node represents a module like blender,
 *  mux etc. and edge is present between two nodes if they are connected. All
 *  VPS paths can be configured by this IOCTL in one shot. Use macro
 *  defined in this file for input path, muxes
 *  output and blender(overlay) as the node numbers.
 *
 *  This IOCTL takes either name of the pre-defined configuration or
 *  list of edges
 *  connecting nodes and configures display paths.
 *  It first validates these paths and then configures VPS for the display
 *  paths. It configures all the modules present in the path.
 *
 * \par This IOCTL cannot be used for clearing configuration on a path
 *      streaming path.
 *
 * \param   cmdArgs [IN] Pointer of type Vps_DctrlConfig
 *
 * \return  FVID2_SOK if successful, else suitable error code
 */
#define IOCTL_VPS_DCTRL_SET_CONFIG      (VPS_DCTRL_IOCTL_BASE + 0x01U)

/** \brief Command to clear the VPS display path configuration in
 *  one shot.
 *
 *  This IOCTL takes either name of the pre-defined configuration or
 *  list of edges
 *  connecting nodes and clears the configuration. It also stops vencs.
 *
 *  It does not validates the edge list. It simply disables the edge
 *  connecting nodes. For the vencs, it checks for the validity and then
 *  disables the venc if there are not errors.
 *
 *  Use macro defined in this file for input path, muxes
 *  output and blender(overlay) as the node numbers.
 *
 * \par This IOCTL cannot be used for clearing configuration on a path
 *      streaming path.
 *
 * \param   cmdArgs [IN] Pointer of type Vps_DctrlConfig
 *
 * \return  FVID2_SOK if successful, else suitable error code
 */
#define IOCTL_VPS_DCTRL_CLEAR_CONFIG    (VPS_DCTRL_IOCTL_BASE + 0x02U)

/** \brief Command to set output in the given Venc.
 *
 *  This IOCTL is used to set the output i.e. dataformat, polarities of all the
 *  signals of the given venc if venc is not on. For the tied vencs, venc has to
 *  be stopped first, then output can can be changed.This IOCTL should be called
 *  before SET_CONFIG_IOCTL.
 *
 * \param   cmdArgs [IN] Pointer of type Vps_DctrlOutputInfo
 *
 * \return  VPS_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPS_DCTRL_SET_VENC_OUTPUT (VPS_DCTRL_IOCTL_BASE + 0x03U)

/** \brief Command to get output in the given Venc.
 *
 * \param   cmdArgs [IN] Pointer of type Vps_DctrlOutputInfo
 *
 * \return  FVID2_SOK if successful, else suitable error code
 */
#define IOCTL_VPS_DCTRL_GET_VENC_OUTPUT (VPS_DCTRL_IOCTL_BASE + 0x04U)

/** \brief Command to set output in the given Venc.
 *
 *  This IOCTL is used to set the Overlay parameters like transparency color
 *  key,
 *  background color, alphablender, overlay optimization etc.
 *
 * \param   cmdArgs [IN] Pointer of type Vps_DssDispcOvlyPanelConfig
 *
 * \return  VPS_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPS_DCTRL_SET_OVLY_PARAMS (VPS_DCTRL_IOCTL_BASE + 0x05U)

/** \brief Command to set Pipeline related params.
 *
 *  This IOCTL is used to set the pipeline parameters related to display
 *  contoller like Zorder, global alpha and premultiply alpha.
 *
 * \param   cmdArgs [IN] Pointer of type Vps_DssDispcOvlyPipeConfig
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPS_DCTRL_SET_PIPELINE_PARAMS  (VPS_DCTRL_IOCTL_BASE + 0x06U)

/** \brief Command to set Venc(Overlay) pixel clock divisor params.
 *
 *  This IOCTL is used to set the divisor values for the Venc pixel clock.
 *   DISPC_LCDx_PCLK = (LCDx_CLK/ divisorLCD) / divisorPCD
 *
 * \param   cmdArgs [IN] Pointer of type Vps_DctrlVencDivisorInfo
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPS_DCTRL_SET_VENC_PCLK_DIVISORS  (VPS_DCTRL_IOCTL_BASE + 0x07U)

/** \brief Command to enable/disable the SDVENC.
 *
 *  This IOCTL is used to Enable/disable and Init/deinit the SD VENC.
 *  This IOCTL should be called before calling any SD VENC related IOCTL.
 *  In this IOCTL we put the Display Controller in Slave Mode and Disable
 *  the DPI output when SD Is Enabled. When its disabled we put DIPSC
 *  back to master mode and enable the DPI output.
 *  This IOCTL should be called after IOCTL_VPS_DCTRL_SET_CONFIG IOCTL
 *
 * \param   cmdArgs [IN] (UInt32*) value enable/disable the SD-VENC
 *                                1- enable
 *                                0 - disable
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPS_DCTRL_ENABLE_SDVENC  (VPS_DCTRL_IOCTL_BASE + 0x08U)

/** \brief Command to configure the SDVENC for particular video mode(NTSC/PAL).
 *
 *  This IOCTL is used to configure the SD-VENC for different video modes like
 *  NTSC, PAL variants.
 *
 *  \param   cmdArgs [IN]  pointer of type Vps_DctrlSDVencVideoStandard.
 *                         Standard to which the SDVENC should be configured for
 *                         For valid values see #Fvid2_Standard. Supported only
 *                         NTSC and PAL Format as of now.
 *  \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPS_DCTRL_SET_SDVENC_MODE  (VPS_DCTRL_IOCTL_BASE + 0x09U)

/** \brief IOCTl to get the count of number of sync losts of all the overlays
 *  and ocp error.
 *
 *  This IOCTL is used to get the count of number of sync losts occured for all
 *  the applicable overlays and number of ocp errors occured.
 *
 * \param   cmdArgs [IN]  pointer of type Vps_DctrlErrorSyncLostStats.
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPS_DCTRL_GET_ERROR_STATS   (VPS_DCTRL_IOCTL_BASE + 0x0AU)

/** \brief IOCTl to get the sdvenc default configuration.
 *
 *  This IOCTL is used initialize the object of Vps_DssDispcSdVencAdvConfig
 *  passed in cmdArgs with the default values.
 *
 * \param   cmdArgs [IN]  pointer of type Vps_DssDispcSdVencAdvConfig.
 *          Vps_DssDispcSdVencAdvConfig->videoStandard should be set
 *          to get proper default values
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPS_DCTRL_SDVENC_GET_DEF_ADV_CONFIG  (VPS_DCTRL_IOCTL_BASE + \
                                                    0x0BU)

/** \brief IOCTl to set the sdvenc configuration.
 *
 *  This IOCTL is used to set the sd venc configuration using the object of
 *  Vps_DssDispcSdVencAdvConfig passed in cmdArgs.
 *
 * \param   cmdArgs [IN]  pointer of type Vps_DssDispcSdVencAdvConfig.
 *
 * \return  FVID2_SOK if successful, else suitable error code
 *
 */
#define IOCTL_VPS_DCTRL_SDVENC_SET_ADV_CONFIG  (VPS_DCTRL_IOCTL_BASE + 0x0CU)
/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/* ========================================================================== */
/*                      Part-3 Advanced Configuration                         */
/* ========================================================================== */
/* ========================================================================== */

/**
 *  \addtogroup BSP_DRV_IOCTL_VPS_DCTRL
 *  @{
 */

/** \brief Advanced configurations
 *
 *  Marker used to denote the begining of IOCTLs that would be required
 *  for advanced control
 *
 *  \par CAUTION Ensure that basic IOCTL value does not execeed this value
 */
#define VPS_DCTRL_IOCTL_ADV_BASE    (VPS_DCTRL_IOCTL_BASE + 0x100U)

/** \brief Command to program advance Venc Signal parameters
 *
 *  This IOCTL is used to program the advance signal parameters for the VENCS,
 *  parameters include when the Hsync and Vsync should be driver(rising or
 *  falling
 *  edge of the pixel clock), Hsync,Vsync,pixelclock,pixel data signals are
 *  gated, aC bias pin transition , ac bias pin frequency etc.
 *  This is valid only for first three VENCS(DPI1/DPI2/DPI3),
 *  not valid for VPS_DCTRL_DSS_VENC_HDMI.
 *
 * \param   cmdArgs [IN]     Pointer of type Vps_DssDispcLcdAdvSignalConfig.
 *
 * \return  VPS_SOK if successful, else suitable error code
 */
#define IOCTL_VPS_DCTRL_DSS_SET_ADV_VENC_SIGNAL_PARAMS  ( \
        VPS_DCTRL_IOCTL_ADV_BASE +                        \
        0x1U)

/** \brief Command to program advance Venc Display parameters
 *
 *  This IOCTL is used to program the advance Display parameters for the VENCS
 *  like stall mode, number of tft datalines, scanformat, which fid to display
 *  first etc.
 *  This is valid only for first three VENCS(DPI1/DPI2/DPI3),
 *  not valid for VPS_DCTRL_DSS_VENC_HDMI.
 *
 *
 * \param   cmdArgs [IN]     Pointer of type Vps_DssDispcLcdAdvDisplayConfig.
 *
 * \return  VPS_SOK if successful, else suitable error code
 */
#define IOCTL_VPS_DCTRL_DSS_SET_ADV_VENC_DISP_PARAMS  (VPS_DCTRL_IOCTL_ADV_BASE \
                                                       + 0x2U)

/** \brief Command to program advance Venc TDM(Time division multiplexing)
 *  parameters
 *
 *  This IOCTL is used to program all the parameters related to TDM display.
 *  This is valid only for first three VENCS(DPI1/DPI2/DPI3),
 *  not valid for VPS_DCTRL_DSS_VENC_HDMI.
 *
 * \param   cmdArgs [IN]     Pointer of type Vps_DssDispcAdvLcdTdmConfig.
 *
 * \return  VPS_SOK if successful, else suitable error code
 */
#define IOCTL_VPS_DCTRL_DSS_SET_ADV_VENC_TDM_PARAMS  (VPS_DCTRL_IOCTL_ADV_BASE \
                                                      + 0x3U)

/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

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

#endif /* #ifndef VPS_DISPLAY_CTRL_H_ */

/* @} */
