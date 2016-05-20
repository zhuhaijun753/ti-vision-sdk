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
 *  \file bsp_cfgMem.h
 *
 *  \brief BSP header file containing configuration details,
 *         for the size of static object array.
 *
 */

#ifndef BSP_CFG_MEM_H_
#define BSP_CFG_MEM_H_

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

/** \brief Number of queue length per capture channel in capture driver */
#define BSP_CFG_CAPT_QUEUE_LEN_PER_CH       (16U)

/** \brief Number of queue length per display instance in display driver */
#define BSP_CFG_DISP_QUEUE_LEN_PER_INST     (16U)

/** \brief Number of queue length per M2M channel in M2M driver */
#define BSP_CFG_M2M_INTF_QUEUE_LEN_PER_CH   (10U)

/** \brief Number of queue length per VPE channel in VPE driver */
#define BSP_CFG_M2M_VPE_QUEUE_LEN_PER_CH    (10U)

/** \brief Number of driver object to allocate in FVID2 library. */
#define FVID2_CFG_FDM_NUM_DRV_OBJS          (40U)

/** \brief Number of channel object to allocate in FVID2 library. */
#define FVID2_CFG_FDM_NUM_CH_OBJS           (80U)

/**
 *  \brief Number of capture objects to allocate
 *
 *  Note: This macro is used for storing platform data at init time. Hence
 *  this should be changed only when a particular capture instance is removed
 *  from the build using make macros like VPS_VIP1_BUILD, VPS_ISS_BUILD etc...
 */
#define VPS_CFG_CAPT_NUM_INST_OBJS          (CSL_VPS_VIP_PORT_PER_CNT +    \
                                             CSL_VPS_DSS_WB_PIPE_PER_CNT + \
                                             CSL_VPS_ISS_CAPT_PIPE_PER_CNT)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef BSP_CFG_MEM_H_ */
