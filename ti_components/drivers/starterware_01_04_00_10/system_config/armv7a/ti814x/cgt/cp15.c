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
 *  \file   cp15.c
 *
 *  \brief  coprocessor related definitions
 *
 *  This file contains the API definitions for configuring coprocessor register
 */
#include <stdint.h>
#include "cp15.h"

asm ("INV_TLB:    .word 0x55555555");
asm ("CLIENTD:   .word 0x55555555");
asm ("FLD_MAX_WAY:   .word 0x3ff");
asm ("FLD_MAX_IDX:   .word 0x7ff");

asm ("MODE_SVC:   .set 0xD3");
asm ("I_F_BIT:   .set 0xC0");
asm ("SVC_STACK_SIZE:   .set 0x200");

/*****************************************************************************
**                   FUNCTION DEFINITIONS
******************************************************************************/
/**
 * \brief      This API disable the Instruction cache.
 *
 * \param      None.
 *
 * \return     None.
 *
 **/
void CP15ICacheDisable(void)
{
    asm ("    mrc     p15, #0, r0, c1, c0, #0\n\t"
         "    bic     r0,  r0, #0x00001000\n\t"
         "    mcr     p15, #0, r0, c1, c0, #0");
}

/**
 * \brief      This API disable the Data cache.
 *
 * \param      None.
 *
 * \return     None.
 *
 **/
void CP15DCacheDisable(void)
{
    asm ("    mrc     p15, #0, r0, c1, c0, #0\n\t"
         "    bic     r0,  r0, #0x00000004\n\t"
         "    mcr     p15, #0, r0, c1, c0, #0");
}

/**
 * \brief      This API Enables the Instruction cache.
 *
 * \param      None.
 *
 * \return     None.
 *
 **/
void CP15ICacheEnable(void)
{
    asm ("    mrc     p15, #0, r0, c1, c0, #0\n\t"
         "    orr     r0,  r0, #0x00001000 \n\t"
         "    mcr     p15, #0, r0, c1, c0, #0 \n\t");
}

/**
 * \brief      This API Enables the Data cache.
 *
 * \param      None.
 *
 * \retiurn     None.
 *
 * Note: MMU shall be enabled before enabling D-Cache
 **/
void CP15DCacheEnable(void)
{
    asm ("    mrc     p15, #0, r0, c1, c0, #0\n\t"
         "    orr     r0,  r0, #0x00000004\n\t"
         "    mcr     p15, #0, r0, c1, c0, #0");
}

/**
 * \brief      This API cleans and flushes the D-Cache. This is done  using the
 *             test clean command
 *
 * \param      None.
 *
 * \return     None.
 *
 **/

void CP15DCacheCleanFlush(void)
{
    asm ("    push    {r4-r11} \n\t"
         "    dmb \n\t"
         "    mrc    p15, #1, r0, c0, c0, #1 \n\t"  /* Load CLID register */
         "    ands    r3, r0, #0x7000000  \n\t"     /* Get LoC */
         "    mov    r3, r3, lsr #23 \n\t"
         "    beq    finished \n\t"                 /* if LoC is 0, then no need
                                                     *to clean */
         "    mov    r10, #0 \n"                    /* start cleaning at cache
                                                     *level 0 */
         "loop1: \n"
         "    add    r2, r10, r10, lsr #1 \n\t"     /* work out 3x current cache
                                                     *level */
         "    mov    r1, r0, lsr r2 \n\t"           /* get cache type */
         "    and    r1, r1, #7 \n\t"               /* mask of the bits for
                                                     *current cache only*/
         "    cmp    r1, #2  \n\t"                  /* cache at this level */
         "    blt    skip \n\t"                     /* skip if no cache, or just
                                                     *i-cache */
         "    mcr    p15, #2, r10, c0, c0, #0 \n\t" /* select current cache
                                                     *level */
         "    isb \n\t"                             /* isb to sych the new CSSR
                                                     *& CSIDR */
         "    mrc    p15, #1, r1, c0, c0, #0 \n\t"  /* read the new CSIDR */
         "    and    r2, r1, #7 \n\t"               /* extract the length of the
                                                     *cache lines */
         "    add    r2, r2, #4 \n\t"
         "    ldr    r4, FLD_MAX_WAY \n\t"
         "    ands   r4, r4, r1, lsr #3 \n\t" /* Max on the way size */
         "    clz    r5, r4 \n\t"             /* find bit position of way size
                                               *increment */
         "    ldr    r7, FLD_MAX_IDX \n\t"
         "    ands    r7, r7, r1, lsr #13 \n" /* Max number of the index size */
         "loop2: \n"
         "    mov     r9, r4 \n"
         "loop3: \n"
         "    orr     r11, r10, r9, lsl r5  \n\t"    /* factor way and cache
                                                      *number */
         "    orr    r11, r11, r7, lsl r2 \n\t"      /* factor index number */
         "    mcr    p15, #0, r11, c7, c14, #2 \n\t" /* clean & invalidate by
                                                      *set/way */
         "    subs    r9, r9, #1 \n\t"               /* decrement the way */
         "    bge     loop3 \n\t"
         "    subs    r7, r7, #1 \n\t"               /* decrement the index */
         "    bge     loop2 \n"
         "skip: \n"
         "    add     r10, r10, #2 \n\t" /*  increment cache number */
         "    cmp     r3, r10 \n\t"
         "    bgt     loop1 \n"
         "finished:  \n"
         "    isb    \n\t"
         "    pop    {r4-r11} \n\t");
}

/**
 * \brief      This API Invalidates Instruction cache.
 *
 * \param      None.
 *
 * \return     None.
 *
 **/
void CP15ICacheFlush(void)
{
    asm ("    mov     r0, #0\n\t"
         "    mcr     p15, #0, r0, c7, c5, #0\n\t");
}

/**
 * \brief      Flushes cache lines corresponding to the buffer pointer
 *             upto the specified length.
 *
 * \param      Buffer Pointer     1st parameter; Buffer start address
 * \param      Buffer Size    2nd parameter; Size of the buffer in bytes
 *
 * \return     None.
 *
 **/
__asm("    .sect \".text:CP15ICacheFlushBuff\"\n"
      "    .clink\n"
      "    .global CP15ICacheFlushBuff\n"
      "CP15ICacheFlushBuff:\n"
      "    bic      r2, r0, #0x3F\n"
      "    add      r0, r1, r0\n"
      "    mov      r1, r2\n"
      "    b        FlushBuffChk\n"
      "FlushBuffLoop:\n"
      "    mcr p15, #0, r1, c7, c6, #1\n"
      "    add      r1, r1, #64\n"
      "FlushBuffChk:\n"
      "    cmp      r1, r0\n"
      "    blt      FlushBuffLoop\n"
      "    bx       lr\n");

/**
 * \brief      Cleans the D-cache lines corresponding to the buffer pointer
 *             upto the specified length.
 *
 * \param      Buffer Pointer     1st parameter; Buffer start address
 * \param      Buffer Size    2nd parameter; Size of the buffer in bytes
 *
 * \return     None.
 *
 **/
__asm("    .sect \".text:CP15DCacheCleanBuff\"\n"
      "    .clink\n"
      "    .global CP15DCacheCleanBuff\n"
      "CP15DCacheCleanBuff:\n"
      "    bic      r2, r0, #0x3F\n"
      "    add      r0, r1, r0\n"
      "    mov      r1, r2\n"
      "    b        CleanBuffChk\n"
      "CleanBuffLoop:\n"
      "    mcr p15, #0, r1, c7, c10, #1\n"
      "    add      r1, r1, #64\n"
      "CleanBuffChk:\n"
      "    cmp      r1, r0\n"
      "    blt      CleanBuffLoop\n"
      "    bx       lr\n");

/**
 * \brief     This API Configures translation table base register 0 with
 *            with page table starting address.
 *
 * \param     ttb  - starting address of the pageTable.
 *
 * \return    None.
 *
 *  Note : Page Table starting address should be aligned to 16k.
 **/
__asm("    .sect \".text:CP15Ttb0Set\"\n"
      "    .clink\n"
      "    .global CP15Ttb0Set\n"
      "CP15Ttb0Set:\n"
      "     mcr p15, #0, r0, c2, c0, #0\n"
      "    bx       lr\n");
/**
 * \brief     This API invalidates the TLB
 *
 * \param     None
 *
 * \return    None.
 *
 **/
void CP15TlbInvalidate(void)
{
    /* Invalidates all TLBs.Domain access is selected as
     * client by configuring domain access register,
     * in that case access controlled by permission value
     * set by page table entry
     */
    asm ("   mov r1, #0\n\t"
         "   mcr p15, #0, r1, c8, c7, #0\n\t"
         "   ldr r1, INV_TLB \n\t"
         "   mcr p15, #0, r1, c3, c0, #0\n\t");
}

/**
 * \brief     This API disables the MMU.
 *
 * \param     None.
 *
 * \return    None.
 *
 **/
void CP15MMUDisable(void)
{
    asm ("    mov r0, #0\n\t"
         "    mcr p15, #0, r0, c8, c7, #0\n\t"
         "    mrc p15, #0, r0, c1, c0, #0\n\t"
         "    mov r1, #0x1\n\t"
         "    bic r0, r0, r1\n\t"
         "    mcr p15, #0, r0, c1, c0, #0\n\t");
}

/**
 * \brief     This API enables the MMU.
 *
 * \param     None.
 *
 * \return    None.
 *
 **/
void CP15MMUEnable(void)
{
    asm ("    mrc p15, #0, r0, c1, c0, #0\n\t"
         "    orr r0, r0, #0x00000001\n\t"
         "    mcr p15, #0, r0, c1, c0, #0\n\t");
}

/**
 * \brief     Set the exception table base address
 *
 * \param     addr    The base address of the exception vector table
 *
 * \return    None.
 *
 **/
__asm("    .sect \".text:CP15VectorBaseAddrSet\"\n"
      "    .clink\n"
      "    .global CP15VectorBaseAddrSet\n"
      "CP15VectorBaseAddrSet:\n"
      "     mcr p15, #0, r0, c12, c0, #0 \n"
      "    bx       lr\n");

/**
 * \brief     This API Invalidates the branch predictor
 *
 * \param     None.
 *
 * \return    None.
 *
 **/
void CP15BranchPredictorInvalidate(void)
{
    asm ("    mcr p15, #0, r0, c7, c5, #6");
}

/**
 * \brief     This API Enables the branch prediction logic
 *
 * \param     None.
 *
 *
 *
 **/
void CP15BranchPredictionEnable(void)
{
    asm ("    mrc p15, #0, r0, c1, c0, #0\n\t"
         "    orr r0, r0, #0x00000800\n\t"
         "    mcr p15, #0, r0, c1, c0, #0\n\t");
}

/**
 * \brief     This API Enables the branch prediction logic
 *
 * \param     None.
 *
 * \return    None.
 *
 **/
void CP15BranchPredictionDisable(void)
{
    asm ("    mrc p15, #0, r0, c1, c0, #0\n\t"
         "    bic r0, r0, #0x00000800\n\t"
         "    mcr p15, #0, r0, c1, c0, #0\n\t");
}

/**
 * \brief     Sets the domain access to client
 *
 * \param     None
 *
 * \return    None.
 *
 **/
void CP15DomainAccessClientSet(void)
{
    asm ("    ldr r0, CLIENTD \n\t"
         "    mcr p15, #0, r0, c3, c0, #0");
}

void setSvMode(void)
{
    asm ("    MOV     r0, #0xD3  \n\t"
         "    MSR     cpsr_c, r0  \n\t"
         "    MOV     sp, r0 \n\t"
         "    SUB     r0, r0, #SVC_STACK_SIZE \n\t"
         "    MRS     r0, cpsr \n\t"
         "    BIC     r0, r0, #0x1F \n\t"
         "    ORR     r0, r0, #0x13 \n\t"
         "    MSR     cpsr_c, r0");
}

void setUserMode(void)
{
    asm ("    MRS     r0, cpsr \n\t"
         "    BIC     r0, r0, #0x1F \n\t"
         "    ORR     r0, r0, #0x10 \n\t"
         "    MSR     cpsr_c, r0");
}

/********************************* End Of File ********************************/
