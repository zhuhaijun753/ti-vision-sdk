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
#ifndef VPS_CORE_VIPVIPCONTROL_H_
#define VPS_CORE_VIPVIPCONTROL_H_

#include <captcore/vpscore_vip.h>
#include <captcore/src/vpscore_vipPriv.h>
#include <common/vps_graph.h>
#include <common/vps_common.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

Int32 VpsCore_vipPostAbortList(VpsCore_VipPathObj *pathObj);
Int32 VpsCore_vipResetFIFO(VpsCore_VipPathObj *pathObj, UInt32 enable);
Int32 VpsCore_vipBlockReset(VpsCore_VipPathObj *pathObj);
void VpsCore_vipTopResetAllModules(VpsCore_VipPathObj *pathObj, UInt32 enable);
Int32 VpsCore_vipPortAndModulesReset(VpsCore_VipPathObj *pathObj);
VpsCore_Frame *VpsCore_vipGetCurrentCaptFrame(const VpsCore_VipPathObj *pathObj);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* VPS_CORE_VIPVIPCONTROL_H_ */
