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
 *
 *  @{
 */

/**
 *  \file vps_cfgMem.h
 *
 *  \brief VPS - Configuration for size of static object array
 */

#ifndef VPS_CFG_MEM_H_
#define VPS_CFG_MEM_H_

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

/**
 *  \brief DSS number of instances for Vid + Gfx (Forward) pipe objects to
 *  allocate.
 *  If user uses only fewer than these pipes, this can be reduced!!
 */
#ifdef TDA2XX_FAMILY_BUILD
/* Tda2xx has 3 video + 1 Grpx pipelines */
#define VPS_CFG_MEM_DSS_MAX_FWD_PIPE_OBJS   (4U)
#elif defined (TDA3XX_FAMILY_BUILD)
/* Tda3xx has 2 video + 1 Grpx pipelines */
#define VPS_CFG_MEM_DSS_MAX_FWD_PIPE_OBJS   (3U)
#endif

/**
 *  \brief DSS number of instances of WB pipe objects to allocate
 *  Tda2xx and Tda3xx supports 1 WB pipeline
 */
#define VPS_CFG_MEM_DSS_MAX_WB_PIPE_OBJS    (1U)

/**
 *  \brief Number of VIP instances objects to allocate.
 *
 *  Note: This macro is used for storing platform data at init time. Hence
 *  this should be changed only when a particular VIP instance is removed
 *  from the build using make macros like VPS_VIP1_BUILD etc...
 */
#define VPS_CFG_MEM_VIP_MAX_INST_OBJS       (VPS_VIP_MAX)

/**
 *  \brief Number of VIP port objects to allocate.
 *  If user uses only fewer than these ports, this can be reduced!!
 *  Note: Each VIP instance has 4 ports. That's why it is (x * 2 * 2) below.
 */
#define VPS_CFG_MEM_VIP_MAX_PORT_OBJS                \
            (VPS_VIP_MAX * VPS_VIP_SLICE_MAX * VPS_VIP_PORT_MAX)

/*
 * Note: Below macros cannot be changed. These macros are used for storing
 * platform data. Hence depends on a platform build and not as a configurable
 * parameters!!
 */
/**
 *  \brief DSS number of instances for Vid + Gfx (forward) pipes for a platform
 */
#ifdef TDA2XX_FAMILY_BUILD
/* Tda2xx has 3 video + 1 Grpx pipelines */
#define VPS_CFG_MEM_DSS_NUM_FWD_PIPE        (4U)
#elif defined (TDA3XX_FAMILY_BUILD)
/* Tda3xx has 2 video + 1 Grpx pipelines */
#define VPS_CFG_MEM_DSS_NUM_FWD_PIPE        (3U)
#endif

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

#endif  /* #ifndef VPS_CFG_MEM_H_ */

/* @} */
