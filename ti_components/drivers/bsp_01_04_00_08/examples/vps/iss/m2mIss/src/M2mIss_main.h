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
 *  \file displayDss_main.h
 *
 *  \brief DSS Display driver sample application private header file.
 *
 */

#ifndef ISS_WDR_MAIN_H_
#define ISS_WDR_MAIN_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xdc/std.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/utils/Load.h>

#include <common/bsp_types.h>
#include <common/trace.h>
#include <common/bsp_config.h>
#include <common/bsp_utils.h>
#include <osal/bsp_osal.h>
#include <fvid2/fvid2.h>
#include <platforms/bsp_platform.h>
#include <vps/vps.h>

#include <vps/vps_m2mIntf.h>
#include <vps/iss/vps_m2mIss.h>

#include <boards/bsp_board.h>
#include <utility/bsputils_prf.h>
#include <utility/bsputils_app.h>
#include <utility/bsputils_mem.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Test application stack size */
#define ISS_WDR_APP_TSK_STACK_MAIN         (10U * 1024U)

/* Test application task priority */
#define ISS_WDR_APP_TSK_PRI_MAIN           (10U)

#define APP_NAME                            "ISSM2MApp"

/* Worst case frames per handle */
#define ISS_WDR_APP_MAX_FRAMES_PER_HANDLE  (4U)

/* Padding required for allocating extra memory. */
#define ISS_WDR_APP_PADDING_LINES          (0U)

/* Default run count in seconds in case of EVM else this is in frame count. */
#define ISS_WDR_APP_RUN_COUNT              (60U)

/* Buffer width in pixels to allocate. */
#define ISS_WDR_APP_BUF_WIDTH              (1920U)
/* Buffer height in lines to allocate. */
#define ISS_WDR_APP_BUF_HEIGHT             (1080U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef ISS_WDR_MAIN_H_ */
