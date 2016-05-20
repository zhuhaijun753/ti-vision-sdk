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
 *  \file vpshal_vipPort.h
 *
 *  \brief HAL header file for VIP Parser
 *  This file exposes the HAL APIs of the VIP Parsers and Ports.
 *
 */

#ifndef VPSHAL_VIPPORT_H_
#define VPSHAL_VIPPORT_H_

/* ========================================================================= */
/*                             Include Files                                 */
/* ========================================================================= */

#include <hal/vpshal.h>
#include <vps/vps_dataTypes.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/* ========================================================================= */
/*                           Macros & Typedefs                               */
/* ========================================================================= */

/**
 *  enum VpsHal_VipPortInstId
 *  \brief Enum for selecting different instances of VIP Port.
 */
typedef enum
{
    VPSHAL_VIP1_S0_PORTA = 0,
    /**< VIP 1 - Slice 0 PORTA. */
    VPSHAL_VIP1_S0_PORTB,
    /**< VIP 1 - Slice 0 PORTB. */
    VPSHAL_VIP1_S1_PORTA,
    /**< VIP 1 - Slice 1 PORTA. */
    VPSHAL_VIP1_S1_PORTB,
    /**< VIP 1 - Slice 1 PORTB. */
    VPSHAL_VIP2_S0_PORTA,
    /**< VIP 2 - Slice 0 PORTA. */
    VPSHAL_VIP2_S0_PORTB,
    /**< VIP 2 - Slice 0 PORTB. */
    VPSHAL_VIP2_S1_PORTA,
    /**< VIP 2 - Slice 1 PORTA. */
    VPSHAL_VIP2_S1_PORTB,
    /**< VIP 2 - Slice 1 PORTB. */
    VPSHAL_VIP3_S0_PORTA,
    /**< VIP 3 - Slice 0 PORTA. */
    VPSHAL_VIP3_S0_PORTB,
    /**< VIP 3 - Slice 0 PORTB. */
    VPSHAL_VIP3_S1_PORTA,
    /**< VIP 3 - Slice 1 PORTA. */
    VPSHAL_VIP3_S1_PORTB,
    /**< VIP 3 - Slice 1 PORTB. */
    VPSHAL_VIP_PORT_INST_ID_MAX
    /**< Max - used for error check. */
} VpsHal_VipPortInstId;

/**
 *  \brief VIP PORT maximum number of instances for any given platform - used
 *  for memory allocation.
 */
#define VPSHAL_VIP_PORT_MAX_INST   (VPSHAL_NUM_VIP_INST *   \
                                    VPSHAL_NUM_VIP_SLICES * \
                                    VPSHAL_NUM_VIP_PORTS)

/* ========================================================================= */
/*                         Structure Declarations                            */
/* ========================================================================= */

/**
 *  struct VpsHal_vipInstParams
 *  \brief Structure containg parameters to initialize vip instances
 */

typedef struct
{
    UInt32 halId;
    /**< Hal ID for current instance.
     *   For valid values see #VpsHal_VipPortInstId. */
    UInt32 baseAddr;
    /**< Base address of VIP PORT for current instance. */
} VpsHal_VipPortInstParams;

/**
 *  struct VpsHal_VipPortOpenParams
 *  \brief Structure to identify a VIP Port HAL instance.
 */
typedef struct
{
    UInt32 halId;
    /**< VIP Port Instance ID. For valid values see #VpsHal_VipPortInstId. */
} VpsHal_VipPortOpenParams;

/**
 *  struct VpsHal_VipStatus
 *  \brief Structure containing configuration status parameter.
 *  All parameter are read only
 */
typedef struct
{
    UInt32 isVideoDetect;
    /**< '1' = proper video sync is found, '0' = Proper video sync is not found
     * for Embedded Sync only
     */

    UInt32 curFid;
    /**< Current FID of the source frame. See #Vps_VipFid  */

    UInt32 prevFid;
    /**< Previous FID of the source frame. See #Vps_VipFid  */

    UInt16 height;
    /**< Height of source frame */

    UInt16 width;
    /**< Width of source frame */
} VpsHal_VipStatus;

/**
 *  struct VpsHal_VipErrStatus
 *  \brief Structure containing status of errors like overflow/protocol
 *  violations for the current VIP port
 */
typedef struct
{
    UInt32 isOutputOverflow;
    /**< 1: Indicates the output port had overflowed.
     *   0: Indicates no overflow */
    UInt32 isAsyncOverflow;
    /**< 1: Indicates the async port had overflowed.
     *   0: Indicates no overflow */
    UInt32 isActProtViolation;
    /**< 1: Indicates protocal violations in data channel.
     *   0: Indicates no violations */
    UInt32 isAncProtViolation;
    /**< 1: Indicates protocal violations in ancillary channel.
     *   0: Indicates no violations */
} VpsHal_VipPortErrStatus;

/* ========================================================================== */
/*                        Public Function Declarations                        */
/* ========================================================================== */
/**
 *  VpsHal_vipPortInit
 *  \brief VIP PORT HAL init function.
 *  This function should be called before calling any of VIP PORT HAL API's.
 *
 *  \param numInst            Number of instances to initialize.
 *  \param instPrms           Pointer to #VpsHal_VipPortInstParams.
 *  \param arg                Not used currently. Meant for future purpose.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 VpsHal_vipPortInit(UInt32                          numInst,
                         const VpsHal_VipPortInstParams *instPrms,
                         Ptr                             arg);

/**
 *  VpsHal_vipPortDeInit
 *  \brief VIP PORT HAL exit function.
 *  Resets internal variables.
 *
 *  \param arg      Not used currently. Meant for future purpose
 *
 *  \return         TODO: Error check. Always returns BSP_SOK for now.
 *
 */
Int32 VpsHal_vipPortDeInit(Ptr arg);

/**
 *  VpsHal_vipPortOpen
 *  \brief Returns the handle to the requested Vip Port instance.
 *  It is allowed to open only one handle for each vip Instance.
 *
 *  This function should be called prior to calling any of the VIP PORT HAL
 *  configuration APIs.
 *
 *  VpsHal_vipPortInit should be called prior to this
 *  Caller shall ensure simulataneous calls do not happen.
 *
 *  \param openPrms     Identify port using #VpsHal_VipPortOpenParams
 *
 *  \return              success     VIP PORT handle
 *                       failure     NULL
 */
VpsHal_Handle VpsHal_vipPortOpen(const VpsHal_VipPortOpenParams *openPrms);

/**
 *  VpsHal_vipClose
 *  \brief Closes specified instance of Vip Port HAL
 *  VpsHal_vipPortInit and VpsHal_vipPortOpen should be called prior to this.
 *
 *  \param handle       Valid handle returned by VpsHal_vipPortOpen()
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vipPortClose(VpsHal_Handle handle);

/**
 *  VpsHal_vipPortSetCfg
 *  \brief Sets the entire port configuration
 *
 *  \param  handle            Valid handle returned by VpsHal_vipPortOpen
 *                            function
 *  \param  portCfg           Pointer to #Vps_VipPortConfig structure.
 *                            This parameter should be non-NULL.
 *  \param  configOvlyPtr     Register Overlay address. Ignored if 0.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipPortSetCfg(VpsHal_Handle            handle,
                           const Vps_VipPortConfig *portCfg,
                           Ptr                      configOvlyPtr);

/**
 *  VpsHal_vipPortEnable
 *  \brief Enable/Disable specified port.
 *         Primarily use PORT_X register
 *
 *  \param  handle            Valid handle returned by VpsHal_vipPortOpen()
 *  \param  enable            1: Enable Port; 0: Disable Port
 *  \param  configOvlyPtr     Register Overlay address. Ignored if 0.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipPortEnable(VpsHal_Handle handle,
                           UInt32        enable,
                           Ptr           configOvlyPtr);

/**
 *  VpsHal_vipGetSrcStatus
 *  \brief Get the status of Video Source.
 *
 *  \param  handle         Valid handle returned by VpsHal_vipPortOpen()
 *  \param  configOvlyPtr  Register Overlay address. Ignored if 0.
 *  \param  vpdmaCh        VPDMA channel used
 *  \param  vipStatus      Pointer to #VpsHal_VipStatus structure.
 *                         This parameter should be non-NULL
 *
 *  \return                success     0
 *                         failure     error value.
 */
Int32 VpsHal_vipGetSrcStatus(VpsHal_Handle handle,
                             UInt32 vpdmaCh, VpsHal_VipStatus *vipStatus,
                             Ptr configOvlyPtr);

/**
 *  VpsHal_vipPortReset
 *  \brief SW reset for VIP Ports.
 *
 *  \param  handle         Valid handle returned by VpsHal_vipPortOpen()
 *  \param  enable         1 to RESET, 0 to UN-RESET
 *
 *  \return                success     0
 *                         failure     error value.
 */
Int32 VpsHal_vipPortReset(VpsHal_Handle handle, UInt32 enable);

/**
 *  VpsHal_vipPortResetFIFO
 *  \brief FIFO reset for VIP Ports.
 *
 *  \param  handle         Valid handle returned by VpsHal_vipPortOpen()
 *  \param  enable         1 to RESET, 0 to UN-RESET
 *
 *  \return                success     0
 *                         failure     error value.
 */
Int32 VpsHal_vipPortResetFIFO(VpsHal_Handle handle, UInt32 enable);

/**
 *  VpsHal_vipPortIsOverflow
 *  \brief Check whether the specified port/slice combo has overflowed or not.
 *         Interrupt will also be cleared.
 *
 *  \param handle           Valid handle returned by VpsHal_vipPortOpen function
 *  \param vipErrStatus     Pointer to #VpsHal_VipErrStatus which will contains
 *                          error status for the specified port
 *
 *  \return                 BSP_SOK: Success
 *                          BSP_EFAIL: Failure
 */
Int32 VpsHal_vipPortGetErrorStatus(VpsHal_Handle            handle,
                                   VpsHal_VipPortErrStatus *vipErrStatus);

/**
 *  VpsHal_vipPortGetOverflowStatus
 *  \brief Check whether the specified port/slice combo has overflowed or not.
 *
 *  \param handle           Valid handle returned by VpsHal_vipPortOpen function
 *  \param vipErrStatus     Pointer to #VpsHal_VipErrStatus which will contains
 *                          error status for the specified port
 *
 *  \return                 BSP_SOK: Success
 *                          BSP_EFAIL: Failure
 */

Int32 VpsHal_vipPortGetOverflowStatus(VpsHal_Handle handle,
                                      UInt32       *vipErrStatus);

/**
 *  VpsHal_vipPortGetPortParams
 *  \brief Gets the portid and slice id from a valid port handle
 *
 *  \param handle           Valid handle returned by VpsHal_vipPortOpen function
 *  \param port               Port ID
 *                                  #VpsHal_VipPortInst for values
 *
 *  \param slice               Slice ID
 *                                  #Vps_VipSliceInst for values
 *
 *  \return                 BSP_SOK: Success
 *                          BSP_EFAIL: Failure
 */

Int32 VpsHal_vipPortGetPortParams(VpsHal_Handle handle, UInt32 *port,
                                  UInt32 *slice);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* VPSHAL_VIPPORT_H_ */
