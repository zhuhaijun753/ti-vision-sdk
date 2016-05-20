/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      eve_profile.h                                                      */
/*                                                                          */
/*  DESCRIPTION:                                                            */
/*  This file helps perform TSC and SCTM based profiling                    */
/*                                                                          */
/*==========================================================================*/

#ifndef EVE_PROFILE_H
#define EVE_PROFILE_H

#pragma CHECK_MISRA ("none")
#include <stdint.h>
#include "curve_fitting.h"

void profiler_init(void);

void profiler_start(void);

void profiler_end(void);

void print_profile_num(void);

void report_profile_num(char* comp_name, char* statusStr, int img_width, int img_height, char* comments);

void report_memory_usage(char* comp_name, char* comments);

void profiler_deinit(void);

uint32_t profiler_getSP(void);

void profiler_initStack(uint32_t SP);

uint32_t profiler_getStackDepth(void);

void profiler_printStatus(int32_t status);

void profiler_testCaseInfo(int8_t * name, int8_t *desc, uint8_t performanceTestcase);

void profiler_end_print(uint32_t id);

void profiler_performanceParam(uint32_t param);

void report_printAppletInfo(int8_t * name);

#endif /* EVE_PROFILE_H */
