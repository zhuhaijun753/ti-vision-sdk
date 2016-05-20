/*==========================================================================*/
/*      Copyright (C) 2009-2015 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
  ***************************************************************************
  *  @file       math_ext.h
  *  @author     a0393891
  *  @brief      This file defines macros which can be used in place of
  *              math operators or intrinsics specific to C6x DSP.
  *
  *              It also includes some standard C header files such as
  *              math.h (for math functions), float.h (for floating point limits)
  *              limits.h (for integer arithmetic limits)
  *
  *              Restrict keyword is supported only by C6x compiler. Hence it is
  *              defined as a macro. This should help build in host emulation mode
  *              without any errors.
  *
  *              Standard MIN, MAX, ABS, CLIP macro definitions.
  *
  *  @version 0.1 (Jan 2015) : Base version.
  ***************************************************************************
 */

#ifndef TI_OD_MATH_EXT_H
#define TI_OD_MATH_EXT_H

#include <math.h>
#include <float.h>
#include <limits.h>

#ifndef  _TMS320C6X
#include "C6xSimulator.h"

#define DIVSP(a, b) ((a)/(b))
#define DIVDP(a, b) ((a)/(b))
#define EXPDP(a) exp(a)
#define LOGDP(a) log(a)
#define SQRTSP(a) sqrt(a)

#define RESTRICT

#else
#include "mathlib.h"

#define DIVSP(a, b) divsp_i((a),(b))
#define DIVDP(a, b) divsp_i((a),(b))
#define EXPDP(a) expdp_i(a)
#define LOGDP(a) logdp_i(a)
#define SQRTSP(a) sqrtsp_i(a)

#define RESTRICT restrict

#endif

#define ABS(a)     ((a)>=0)?(a):-(a)
#define MIN(a,b)   ((a) < (b) ? (a) : (b))
#define MAX(a,b)   ((a) > (b) ? (a) : (b))
#define CLIP(a, b) ((b) < (a) ? (a) : (b))

#endif //TI_OD_MATH_EXT_H
