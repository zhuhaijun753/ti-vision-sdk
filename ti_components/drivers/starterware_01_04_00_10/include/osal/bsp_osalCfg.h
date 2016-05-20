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
 *  \file bsp_osalCfg.h
 *
 *  \brief BSP OS abstraction layer configuration header file.
 *
 */

#ifndef BSP_OSAL_CFG_H_
#define BSP_OSAL_CFG_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/** \brief Set this to TRUE to use <Module>_Construct API of BIOS */
#define BSP_OSAL_CFG_USE_STATIC          (TRUE)

#if defined (BUILD_ARP32) || defined (BUILD_DSP) || defined (BUILD_A15)

#define BSP_OSAL_CFG_MAX_SEM_OBJECTS     (1000U)
#define BSP_OSAL_CFG_MAX_TASK_OBJECTS    (100U)
#define BSP_OSAL_CFG_MAX_CLOCK_OBJECTS   (100U)
#define BSP_OSAL_CFG_MAX_HWI_OBJECTS     (100U)

#else

#define BSP_OSAL_CFG_MAX_SEM_OBJECTS     (1000U)
#define BSP_OSAL_CFG_MAX_TASK_OBJECTS    (100U)
#define BSP_OSAL_CFG_MAX_CLOCK_OBJECTS   (100U)
#define BSP_OSAL_CFG_MAX_HWI_OBJECTS     (100U)

#endif

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSP_OSAL_CFG_H_ */
