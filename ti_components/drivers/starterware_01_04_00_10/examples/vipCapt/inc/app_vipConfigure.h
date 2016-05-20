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
#ifndef VPS_CONFIGURE_H_
#define VPS_CONFIGURE_H_

#include <stdio.h>
#include <string.h>
#include <common/bsp_types.h>

#include <vps_vipDrv.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

extern VpsCore_Frame *App_queBufs(void *drvData, UInt32 streamId, UInt32 chId);
extern Int32 App_deQueBufs(void *drvData, VpsCore_Frame *frmBufList);
VpsDrv_CaptInstObj *App_coreOpen(UInt32 vipInstId,
                                 UInt32 sliceId,
                                 UInt32 portId);

Int32 App_coreClose(VpsDrv_CaptInstObj *pObj);

Int32 App_coreStart(VpsDrv_CaptInstObj *pObj);

Int32 App_coreStop(VpsDrv_CaptInstObj *pObj);

Int32 App_configureVIP(VpsDrv_CaptInstObj *pObj,
                       UInt32              sliceId,
                       UInt32              portId);

Int32 App_portReset(VpsDrv_CaptInstObj *pObj);

Int32 App_overflowIsr(VpsDrv_CaptInstObj *pObj);
Int32 App_checkOverflow(VpsDrv_CaptInstObj      *pObj,
                        Vps_OverflowCheckParams *overflow);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /*VPS_CONFIGURE_H_*/
