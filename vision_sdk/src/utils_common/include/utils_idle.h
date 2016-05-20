/*
 *******************************************************************************
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \ingroup UTILS_API
 * \defgroup UTILS_IDLE_API CPU IDLE API
 *
 * \brief  APIs to execute CPU Idle instruction and put CPU into IDLE
 *
 * @{
 *
 *******************************************************************************
*/

/**
 *******************************************************************************
 *
 * \file utils_idle.h
 *
 * \brief CPU Idle
 *
 * \version 0.0 First version
 *
 *******************************************************************************
*/

#ifndef UTILS_IDLE_H_
#define UTILS_IDLE_H_

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/utils_common/include/utils.h>

/*******************************************************************************
 *  Functions
 *******************************************************************************
*/
Void Utils_idleFxn(void);

Void Utils_idlePrepare(void);

#if defined (BUILD_ARP32)
Void Utils_idleEnableEveDMA(void);
Void Utils_idleDisableEveDMA(void);
#endif

#endif

/* @} */
