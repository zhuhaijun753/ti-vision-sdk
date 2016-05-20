/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      curve_fitting.h                                                     */
/*                                                                          */
/*  DESCRIPTION:                                                            */
/*  This file helps to calculate performance estimation formula for kernels */
/*                                                                          */
/*==========================================================================*/

#ifndef CURVE_FITTING_H_
#define CURVE_FITTING_H_

/* Memory utility includes */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

/* Profiling defines */
#define CF_PROFILE_MAX_TESTS     32
#define CF_PROFILE_MAX_ORDER      4
#define CF_PROFILE_FORMULA        0
#define CF_PROFILE_RANGE          1
#define CF_PROFILE_FORMULA_RANGE  2

void CF_profile_init (int order, char *kernel_name);
void CF_profile_setMode(int mode_order, int finalMode);
void CF_formula_add_test (int Ax0, int Ax1, int Ax2, int Ax3, int errorFlag, char *desc, int mode);
void CF_profile_cycle_report (int reportType, char *formulaInfo);

#endif

/* =========================================================================*/
/*  End of file:  VLIB_profile.h                                             */
/* =========================================================================*/

