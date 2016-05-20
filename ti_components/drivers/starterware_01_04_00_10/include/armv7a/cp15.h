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
/**
 *  \file  cp15.h
 *
 *  \brief This file contains the API prototypes for configuring CP15.
 */

#ifndef CP15_H_
#define CP15_H_

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
**                           FUNCTION PROTOTYPES
*****************************************************************************/
extern void CP15DCacheCleanBuff(uint32_t bufPtr, uint32_t size);
extern void CP15ICacheFlushBuff(uint32_t bufPtr, uint32_t size);
extern void CP15ICacheDisable(void);
extern void CP15DCacheDisable(void);
extern void CP15ICacheEnable(void);
extern void CP15DCacheEnable(void);
extern void CP15DCacheCleanFlush(void);
extern void CP15ICacheFlush(void);
extern void CP15Ttb0Set(uint32_t ttb);
extern void CP15TlbInvalidate(void);
extern void CP15MMUDisable(void);
extern void CP15MMUEnable(void);
extern void CP15VectorBaseAddrSet(uint32_t addr);
extern void CP15BranchPredictorInvalidate(void);
extern void CP15BranchPredictionEnable(void);
extern void CP15BranchPredictionDisable(void);
extern void CP15DomainAccessClientSet(void);
extern void CP15FPUEnable(void);
extern void CP15InvalidateICache(uint32_t bufPtr, uint32_t size);
extern void CP15InvalidateDCache(uint32_t bufPtr, uint32_t size);
#ifdef TDA2XX_FAMILY_BUILD
extern uint32_t CP15ReadCoreId(void);
extern void ARM_CCNT_Enable(void);
extern void ARM_CCNT_Reset(void);
extern uint32_t ARM_CCNT_Read(void);
#endif

#ifdef TI814X_FAMILY_BUILD
extern void setSvMode(void);
extern void setUserMode(void);
#endif

#ifdef __cplusplus
}
#endif
#endif /* CP15_H___ */
