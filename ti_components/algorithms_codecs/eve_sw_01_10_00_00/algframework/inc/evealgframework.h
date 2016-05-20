/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       evealgframework.h
 *
 *  @brief      This header defines types & constants shared by all implementations
 *              of the "generic" algorithm interface.
 */

#ifndef EVEALGFRAMEWORK_H
#define EVEALGFRAMEWORK_H

#pragma CHECK_MISRA ("none")
#include "evestarterware.h"
#pragma RESET_MISRA ("required")
#include "bam.h"
#include "ibamalg_create.h"

/* included in order to use the default provided ext mem allocatoer in libeveextmem.eve.lib*/
/* The test can choose to define and use different malloc functions as shown in alg_osal_memory.c */
#include "alg_osal_extmem.h"

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/*Function-like macro definition */
/* Deviation allowed since it is a single statement best implemented through a macro function */
#define ALIGN_SIMD(a)   (((a) + VCOP_SIMD_WIDTH-1U) & ~(VCOP_SIMD_WIDTH-1U)) /**< macro to help align any value to the next multiple of VCOP_SIMD_WIDTH */
#define ALIGN_2SIMD(a)   (((a) + 2U*VCOP_SIMD_WIDTH-1U) & ~(2U*VCOP_SIMD_WIDTH-1U)) /**< macro to help align any value to the next multiple of 2*VCOP_SIMD_WIDTH */
/* RESET_MISRA("19.7")  -> Reset rule 19.7*/

#endif
