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
 *  \file vpshal_issvtnf.h
 *
 *  \brief HAL Header file for VTNF
 *  This file exposes the HAL APIs for ISS VTNF module
 *
 */

#ifndef VPSHAL_ISS_VTNF_H_
#define VPSHAL_ISS_VTNF_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief VTNF maximum number of instances for any given platform - used for
 *  memory allocation.
 */
#define ISSHAL_VTNF_MAX_INST             (1U)

/**
 *  enum isshalvtnfInstId
 *  \brief Enum to define the various VTNF instance.
 */
typedef enum isshalvtnfInstId
{
    ISSHAL_VTNF_INST_0 = 0,
    /**< Vtnf Instance Id 0. */
    ISSHAL_VTNF_INST_MAX_ID = 1,
    /**< Max - used for error check. */
    ISSHAL_VTNF_INST_FORCE_INT = 0x7FFFFFFF
                                 /**< This will ensure enum is not packed, will
                                  *always be contained in int */
} isshalvtnfInstId_t;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct isshalvtnfInstParams
 *  \brief Instance specific parameters used at the init.
 */
typedef struct isshalvtnfInstParams
{
    uint32_t instId;
    /**< Instand Id. For valid values see #isshalvtnfInstId. */
    uint32_t baseAddress;
    /**< Register base address */
} isshalvtnfInstParams_t;

/**
 *  struct isshalvtnfOpenParams
 *  \brief Structure to identify a VTNF HAL instance.
 */
typedef struct isshalvtnfOpenParams
{
    uint32_t instId;
    /**< Instance ID. For valid values see #isshalvtnfInstId. */
} isshalvtnfOpenParams_t;

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */

/**
 *  VpsHal_issvtnfInit
 *  \brief VTNF init function.
 *
 *  Initializes VTNF objects.
 *  This function should be called before calling any of VTNF HAL API's.
 *  All global variables are initialized.
 *
 *  \param numInst       Number of instances to initialize.
 *  \param instPrms      Pointer to #isshalvtnfInstParams_t.
 *  \param arg           Not used currently. Meant for future purpose.
 *
 *  \return              Returns 0 on success else returns error value.
 *
 */
int32_t VpsHal_issvtnfInit(UInt32                        numInst,
                           const isshalvtnfInstParams_t *instPrms,
                           Ptr                           arg);

/**
 *  VpsHal_issvtnfDeInit
 *  \brief VTNF HAL exit function.
 *  Resets internal variables.
 *
 *  \param arg      Not used currently. Meant for future purpose
 *
 *  \return         TODO: Error check. Always returns BSP_SOK for now.
 *
 */
int32_t VpsHal_issvtnfDeInit(Ptr arg);

/**
 *  VpsHal_issvtnfOpen
 *  \brief This function should be called prior to calling any of the VTNF HAL
 *  configuration APIs to get the instance handle.
 *
 *  \param openPrms       Open Parameters
 */
VpsHal_Handle VpsHal_issvtnfOpen(const isshalvtnfOpenParams_t *openPrms);

/**
 *  VpsHal_issvtnfClose
 *  \brief This functions closes the vtnf handle and after call to this
 *  function, vtnf handle is not valid.
 *
 *  \param handle         Requested VTNF instance
 */
int32_t VpsHal_issvtnfClose(VpsHal_Handle handle);

/**
 *  \brief Sets the entire VTNF configuration to the VTNF registers.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to vpsissvtnfConfig_t structure
 *                          containing the register configurations.
 *                          This parameter should be non-NULL.
 *  \param arg              Not used, should be NULL
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issvtnfSetConfig(VpsHal_Handle             handle,
                                const vpsissvtnfConfig_t *config,
                                Ptr                       arg);

/**
 *  VpsHal_issvtnfGetConfig
 *  \brief Gets the entire VTNF configuration from the registers.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to vpsissvtnfConfig_t structure to be
 *                          filled with register configurations.
 *                          This parameter should be non-NULL.
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issvtnfGetConfig(VpsHal_Handle       handle,
                                vpsissvtnfConfig_t *config);

/**
 *  VpsHal_issvtnfControl
 *  \brief VTNF specific control commands.
 *
 *  \param handle           Instance handle
 *  \param cmd              Control Command
 *  \param cmdArgs          Arguments for the control command, could be null
 *                          depends on the control command
 *  \param arg              not used. should be null
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issvtnfControl(VpsHal_Handle handle,
                              UInt32        cmd,
                              Ptr           cmdArgs,
                              Ptr           arg);

/**
 *  VpsHal_issvtnfSetAddress
 *  \brief VTNF Api for setting input and output address.
 *
 *  \param handle           Instance handle
 *  \param inAddr           Current Input Frame address, must be 16byte aligned
 *  \param prevInAddr       Previous Input Frame address, must be 16byte aligned
 *  \param outAddr          Current Output Frame address, must be 16byte aligned
 *  \param lineOffset       Line Offset/pitch for input and output buffers
 *                          must be even and 16byte aligned
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issvtnfSetAddress(VpsHal_Handle handle,
                                 Ptr           inAddr,
                                 Ptr           prevInAddr,
                                 Ptr           outAddr,
                                 uint32_t      lineOffset);

/**
 *  VpsHal_issvtnfSetAddress
 *  \brief VTNF Api for enabling the module. Used only when Trigger Source
 *         is set to 0, otherwise HwSeq takes care of starting the module.
 *         It will get reset when it finishes processing for a block.
 *
 *  \param handle           Instance handle
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issvtnfStart(VpsHal_Handle handle);

#ifdef __cplusplus
}
#endif

#endif  /* VPSHAL_ISS_VTNF_H_ */
