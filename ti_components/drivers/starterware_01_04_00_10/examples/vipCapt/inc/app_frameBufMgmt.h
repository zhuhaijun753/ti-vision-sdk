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
#include <common/bsp_types.h>
#include <osal/bsp_osal.h>
#include <common/trace.h>

#include <common/vpscore.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/*
 * Setting as per closest VPDMA max-width/max-height setting.
 * VPDMA supports max-width/max-height setting based on pixels.
 * In raw mode, pixel size is assumed to be two bytes.
 * Therefore, buffer size must be twice the setting.
 * This should be in sync with maxOutWidth/maxOutHeight setting done in
 * App_configureVIP()
 */
#define BUF_STRIDE     (1280 * 2) /* Should be multiple of 16 */
#define BUF_HEIGHT     (720)

#define MAX_NUM_PORTS           2                         // Example: PORTA and
                                                          // PORTB capture
#define MAX_NUM_BUFS_PER_PORT   2                         // Example: ping-pong
                                                          // case
#define MAX_BUF_SIZE            (BUF_STRIDE * BUF_HEIGHT) // Size of one buffer

/* These are used in callback function to identify which port has called the
 * callback function.
 * These are given as input to VPSLIB in VpsDrv_captOpen() as
 * #VpsCore_OpenPrms.drvData
 */
#define BUF_ARRAY_IDX_PORTA     0
#define BUF_ARRAY_IDX_PORTB     1

Void App_FrameBufInit();

Void App_FrameBufDeInit();

VpsCore_Frame *App_GetFrameBuf(UInt32 streamId);

Void App_ReleaseFrameBuf(VpsCore_Frame *frm);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

