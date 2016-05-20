/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      test_profile.h                                                      */
/*                                                                          */
/*  DESCRIPTION:                                                            */
/*  This file helps you to enable and disable profiling                     */
/*                                                                          */
/*==========================================================================*/


#ifndef __TEST_PROFILE_H_
#define __TEST_PROFILE_H_

/* disable if console prints are not required */
#define CONSOLE 

/* disable if profiling and validation report is not to be generated using  
the test frame work*/
//#define REPORT  

/* enable if VCOP_BUSY_CYCLES are to be profiled. Enable only if target is CentEVE */
//#define SCTM  

#ifndef REPORT
#undef SCTM
#endif

#if VCOP_HOST_EMULATION
#undef SCTM
#endif

#ifdef SCTM
#include "GlobalTypes.h"
#include "baseaddress.h"
#include "pcache.h"
#include "sctm.h"
#include <assert.h>
#include <stdint.h>
#endif

#endif

/*--------------------------------------------------------------------------*/
/* End of file: test_profile.h                                               */
/*==========================================================================*/
/* Texas Instruments Incorporated 2010-2012.                                */
/*--------------------------------------------------------------------------*/ 
