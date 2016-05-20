/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#ifndef VCOP_REMAP_H
#define VCOP_REMAP_H

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */

#define ALIGN_HALFSIMD(a) (((a) + (VCOP_SIMD_WIDTH/2U)-1U) & ~((VCOP_SIMD_WIDTH/2U)-1U))
#define ALIGN_SIMD(a)     (((a) + VCOP_SIMD_WIDTH-1U) & ~(VCOP_SIMD_WIDTH-1U))
#define ALIGN_2SIMD(a)    (((a) + 2U*VCOP_SIMD_WIDTH-1U) & ~(2U*VCOP_SIMD_WIDTH-1U))
#define ALIGN_4SIMD(a)    (((a) + 4U*VCOP_SIMD_WIDTH-1U) & ~(4U*VCOP_SIMD_WIDTH-1U))
#define ALIGN_TLU(a)      (((a) + 32U-1U) & ~(32U-1U))

/* RESET_MISRA("19.7")  -> Reset rule 19.7     */

#endif
