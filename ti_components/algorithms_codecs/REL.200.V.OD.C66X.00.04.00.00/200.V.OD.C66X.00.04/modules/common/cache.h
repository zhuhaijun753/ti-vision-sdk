/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef CACHE_H_
#define CACHE_H_

#include <xdais_types.h>

#if (!HOST_EMULATION)

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#pragma RESET_MISRA ("required")

#define Cache_EMIFA_CFG 0x1e00000
#define Cache_EMIFA_BASE 0x2000000
#define Cache_EMIFA_LENGTH 0x8000000

#define Cache_EMIFB_CFG 0x20000000
#define Cache_EMIFB_BASE 0x80000000
#define Cache_EMIFB_LENGTH 0x10000000

#define Cache_EMIFC_CFG 0x1e00000
#define Cache_EMIFC_BASE 0x42000000
#define Cache_EMIFC_LENGTH 0x8000000

#define L2CFG    (volatile unsigned int *)0x01840000
#define L1PCFG   (volatile unsigned int *)0x01840020
#define L1PCC    (volatile unsigned int *)0x01840024
#define L1DCFG   (volatile unsigned int *)0x01840040
#define L1DCC    (volatile unsigned int *)0x01840044
#define L2WBAR   (volatile unsigned int *)0x01844000
#define L2WWC    (volatile unsigned int *)0x01844004
#define L2WIBAR  (volatile unsigned int *)0x01844010
#define L2IBAR   (volatile unsigned int *)0x01844018
#define L2WBINV  (volatile unsigned int *)0x01845004
#define L1DWBINV (volatile unsigned int *)0x01845044
#define L1DINV   (volatile unsigned int *)0x01845048
#define L2INV    (volatile unsigned int *)0x01845008
#define L1DWb    (volatile unsigned int *)0x01845040
#define L2Wb     (volatile unsigned int *)0x01845000

#define L1DWWC   (volatile unsigned int *)0x0184404C

#define MAXWC    0xFF00      /* Max word count per cache operations */

/*
 *  ======== Cache_inv ========
 *  Invalidate the range of memory within the specified starting address and
 *  byte count.  The range of addresses operated on gets quantized to whole
 *  cache lines in each cache.  All cache lines in range are invalidated in L1P
 *  cache.  All cache lines in range are invalidated in L1D cache.
 *  All cache lines in range are invaliated in L2 cache.
 */
Void Cache_inv(uint8_t* blockPtr, unsigned int byteCnt, bool wait);

/*
 *  ======== Cache_wb ========
 *  Writes back the range of memory within the specified starting address
 *  and byte count.  The range of addresses operated on gets quantized to
 *  whole cache lines in each cache.  There is no effect on L1P cache.
 *  All cache lines within the range are left valid in L1D cache and the data
 *  within the range in L1D cache will be written back to L2 or external.
 *  All cache lines within the range are left valid in L2 cache and the data
 *  within the range in L2 cache will be written back to external.
 */
Void Cache_wb(uint8_t* blockPtr, unsigned int byteCnt, bool wait);

/*
 *  ======== Cache_wbInv ========
 *  Writes back and invalidates the range of memory within the specified
 *  starting address and byte count.  The range of addresses operated on gets
 *  quantized to whole cache lines in each cache.  All cache lines within range
 *  are invalidated in L1P cache.  All cache lines within the range are
 *  written back to L2 or external and then invalidated in L1D cache
 *  All cache lines within the range are written back to external and then
 *  invalidated in L2 cache.
 */
Void Cache_wbInv(uint8_t* blockPtr, unsigned int byteCnt, bool wait);


#endif
#endif /* CACHE_H_ */
