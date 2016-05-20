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
#ifndef DCTRL_CONFIGURE_H_
#define DCTRL_CONFIGURE_H_

#include <stdio.h>
#include <string.h>
#include <common/bsp_types.h>

#include <vps_dctrlDrv.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

extern VpsCore_Frame *App_DssqueBufs(void *drvData);
extern Int32 App_DssdeQueBufs(void *drvData, VpsCore_Frame *frmBufList);

VpsDrv_DctrlInstObj *App_dctrlcoreOpen(void);
Int32 App_dctrlcoreClose(VpsDrv_DctrlInstObj *pObj);
Int32 App_configureDctrl(VpsDrv_DctrlInstObj *pObj);
Int32 App_configureDctrlPipe(VpsDrv_DctrlInstObj *pObj);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /*VPS_CONFIGURE_H_*/
