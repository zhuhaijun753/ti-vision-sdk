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
 *  \file  cpu.h
 *
 *  \brief This file contains the API prototypes for configuring CPU.
 */

#ifndef CPU_H_
#define CPU_H_

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
**                           FUNCTION PROTOTYPES
*****************************************************************************/
extern void CPUSwitchToUserMode(void);
extern void CPUSwitchToPrivilegedMode(void);

/****************************************************************************/
/*
** Functions used internally
*/
extern void CPUAbortHandler(void);
extern void CPUirqd(void);
extern void CPUirqe(void);
extern void CPUfiqd(void);
extern void CPUfiqe(void);
extern void CPUSendEvent(void);
extern void CPUDisableCPSRABit(void);
extern uint32_t CPUIntStatus(void);

#ifdef __cplusplus
}
#endif
#endif /* CPU_H___ */
