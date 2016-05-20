/* =================================================================
 *   Copyright (C) 2013 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and
 *   conditionsstipulated in the agreement under which this program
 *   has been supplied.
 * =================================================================*/
/*
 * \file   hs_mmcsdlib.h
 *
 */

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/* Prototype declarations */
void HSMMCSDBusWidthConfig(mmcsdCtrlInfo *ctrl, uint32_t busWidth);
int HSMMCSDBusFreqConfig(mmcsdCtrlInfo *ctrl, uint32_t busFreq);
uint32_t HSMMCSDCmdSend(mmcsdCtrlInfo *ctrl, mmcsdCmd *c);
uint32_t HSMMCSDControllerInit(mmcsdCtrlInfo *ctrl);
uint32_t HSMMCSDCardPresent(mmcsdCtrlInfo *ctrl);
void HSMMCSDIntEnable(mmcsdCtrlInfo *ctrl);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

