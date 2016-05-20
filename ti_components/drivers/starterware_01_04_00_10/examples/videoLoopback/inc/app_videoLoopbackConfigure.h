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
#ifndef VIDEOLOOPBACK_CONFIGURE_H_
#define VIDEOLOOPBACK_CONFIGURE_H_

#include <stdio.h>
#include <string.h>
#include <common/bsp_types.h>

#include <vps_vipDrv.h>
#include <vps_dssDrv.h>
#include <vps_dctrlDrv.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/*VIP Capture functions*/
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

/*DSS Display functions*/

extern VpsCore_Frame *App_DssqueBufs(void *drvData);
extern Int32 App_DssdeQueBufs(void *drvData, VpsCore_Frame *frmBufList);

VpsDrv_DispInstObj *App_dsscoreOpen(UInt32 dssInstId);

Int32 App_dsscoreClose(VpsDrv_DispInstObj *pObj);

Int32 App_dsscoreStart(VpsDrv_DispInstObj *pObj);

Int32 App_dsscoreStop(VpsDrv_DispInstObj *pObj);

Int32 App_dssconfigure(VpsDrv_DispInstObj *pObj);

/*Display Controller functions*/
VpsDrv_DctrlInstObj *App_dctrlcoreOpen(void);
Int32 App_dctrlcoreClose(VpsDrv_DctrlInstObj *pObj);
Int32 App_configureDctrl(VpsDrv_DctrlInstObj *pObj);
Int32 App_configureDctrlPipe(VpsDrv_DctrlInstObj *pObj);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /*VIDEOLOOPBACK_CONFIGURE_H_*/
