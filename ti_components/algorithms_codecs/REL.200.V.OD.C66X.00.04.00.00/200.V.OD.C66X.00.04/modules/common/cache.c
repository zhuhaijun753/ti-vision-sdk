/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/




#if (!HOST_EMULATION)
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cache.h>
#include <stdbool.h>
#pragma RESET_MISRA ("required")

static Void all(volatile unsigned int *cacheReg)
{
  /* disable interrupts */
  /* wait for any previous cache operation to complete */
  while (*L2WWC != 0)
  {
  }
  /* perform global write back of cache */
  *cacheReg = 1;
  /* wait until cache operation completes */
  while (*cacheReg)
  {
    ;
  }
}


/* Writeback Invalidate Cache */
static void Cache_WbInvAll()
{
  /* Write back invalidate cache */
  all(L1DWBINV);
  all(L2WBINV);
}


/* Invalidate Cache */
static void Cache_InvAll()
{
  /* Write back invalidate cache */
  all(L1DINV);
  all(L2INV);
}

/* Writeback Cache */
static void Cache_WbAll()
{
  /* Write back invalidate cache */
  all(L1DWb);
  all(L2Wb);
}

/*
 *  ======== emifRange ========
 *  If addr within range of 'base' and 'base + length - 1' then return TRUE,
 *  otherwise return FALSE.
 */
static inline bool emifRange(unsigned int addr, unsigned int base, unsigned int length)
{
  if (base != 0) {
      return (addr >= base) && (addr <= (base + length - 1));
  }
  else {
      return false;
  }
}

/*
 *  ======== getEmifCtrlAddr ========
 *  Return the EMIF configuratin control register for the address.
 */
static inline volatile unsigned int *getEmifCtrlAddr(unsigned int addr)
{
  if (emifRange(addr, Cache_EMIFA_BASE, Cache_EMIFA_LENGTH)) {
      return (unsigned int *)Cache_EMIFA_CFG;
  }
  else if (emifRange(addr, Cache_EMIFB_BASE, Cache_EMIFB_LENGTH)) {
      return (unsigned int *)Cache_EMIFB_CFG;
  }
  else if (emifRange(addr, Cache_EMIFC_BASE, Cache_EMIFC_LENGTH)) {
      return (unsigned int *)Cache_EMIFC_CFG;
  }
  else {
      return NULL;
  }
}


/*
 *  ======== block ========
 *  This is a static function used by the block cache APIs.
 */
static Void block(uint8_t* blockPtr, unsigned int byteCnt, bool wait, volatile unsigned int *barReg)
{
  volatile unsigned int *bar;
  volatile unsigned int *wc;
  volatile unsigned int *emifAddr;
  Int wordCnt;
  unsigned int alignAddr;

  /*
   *  Get the base address and word count register.
   *  wc is one word after bar on c64x+ cache.
   */
  bar = barReg;
  wc = bar + 1;

  /* word align the base address */
  alignAddr = ((unsigned int)blockPtr & ~3);

  /* convert from byte to word since cache operation takes words */
  wordCnt = (byteCnt + 3 + ((unsigned int)blockPtr - alignAddr)) >> 2;

  /* loop until word count is zero or less */
  while (wordCnt > 0) {

      /* critical section -- disable interrupts */
     // mask = Hwi_disable();

      /* get the emif config for the address */
      emifAddr = getEmifCtrlAddr(alignAddr);

      /* set the word address and number of words to invalidate */
      *bar = alignAddr;
      *wc = (wordCnt > MAXWC) ? MAXWC : wordCnt;

      /* end of critical section -- restore interrupts */
      //Hwi_restore(mask);

      /*
       * reduce word count by _BCACHE_MAXWC and
       * increase base address by BCACHE_MAXWC
       */
      wordCnt -= MAXWC;
      alignAddr += (MAXWC * sizeof(Int));
  }

  /* wait for cache operation to complete */
  if (wait) {

  /* wait for L2 word count to be zero */
  while (*wc != 0) {
      ;
  }

  /*
   *  make a dummy write and read to emif config register to
   *  insure that data made it out to external memory, otherwise
   *  its possible that the data is out of the Master's view but
   *  has not reached its final destination.
   */
 // mask = Hwi_disable();
  if (emifAddr != NULL) {
      *(emifAddr) = 0;
      *(emifAddr);
      emifAddr = NULL;
  }
 // Hwi_restore(mask);
  }
}


/*
 *  ======== Cache_inv ========
 *  Invalidate the range of memory within the specified starting address and
 *  byte count.  The range of addresses operated on gets quantized to whole
 *  cache lines in each cache.  All cache lines in range are invalidated in L1P
 *  cache.  All cache lines in range are invalidated in L1D cache.
 *  All cache lines in range are invaliated in L2 cache.
 */
Void Cache_inv(uint8_t* blockPtr, unsigned int byteCnt, bool wait)
{
  block(blockPtr, byteCnt, wait, L2IBAR);
}

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
Void Cache_wb(uint8_t* blockPtr, unsigned int byteCnt, bool wait)
{
  block(blockPtr, byteCnt, wait, L2WBAR);
}

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
Void Cache_wbInv(uint8_t* blockPtr, unsigned int byteCnt, bool wait)
{
  block(blockPtr, byteCnt, wait, L2WIBAR);
}

#endif

