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
#ifndef DSS_CONFIGURE_H_
#define DSS_CONFIGURE_H_

#include <stdio.h>
#include <string.h>
#include <common/bsp_types.h>

#include <vps_dssDrv.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

extern VpsCore_Frame *App_DssqueBufs(void *drvData);

extern Int32 App_DssdeQueBufs(void *drvData, VpsCore_Frame *frmBufList);

VpsDrv_DispInstObj *App_dsscoreOpen(UInt32 dssInstId);

Int32 App_dsscoreClose(VpsDrv_DispInstObj *pObj);

Int32 App_dsscoreStart(VpsDrv_DispInstObj *pObj);

Int32 App_dsscoreStop(VpsDrv_DispInstObj *pObj);

Int32 App_dssconfigure(VpsDrv_DispInstObj *pObj);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /*VPS_CONFIGURE_H_*/
