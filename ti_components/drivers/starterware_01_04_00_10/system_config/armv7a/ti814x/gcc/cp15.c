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
         "    ldr    r4, =0x3ff \n\t"
         "    ands   r4, r4, r1, lsr #3 \n\t" /* Max on the way size */
         "    clz    r5, r4 \n\t"             /* find bit position of way size
                                               *increment */
         "    ldr    r7, =0x7fff \n\t"
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
 * \param      bufPtr     Buffer start address
 * \param      size       Size of the buffer in bytes
 *
 * \return     None.
 *
 **/
void CP15ICacheFlushBuff(uint32_t bufPtr, uint32_t size)
{
    uint32_t ptr;

    ptr = bufPtr & ~0x3f;

    while (ptr < bufPtr + size)
    {
        asm ("    mcr p15, #0, %[value], c7, c6, #1" ::[value] "r" (ptr));

        ptr += 64;
    }
}

/**
 * \brief      Cleans the D-cache lines corresponding to the buffer pointer
 *             upto the specified length.
 *
 * \param      bufPtr     Buffer start address
 * \param      size       Size of the buffer in bytes
 *
 * \return     None.
 *
 **/

void CP15DCacheCleanBuff(uint32_t bufPtr, uint32_t size)
{
    uint32_t ptr;

    ptr = bufPtr & ~0x3f;

    asm ("dmb");
    while (ptr < bufPtr + size)
    {
        asm ("    mcr p15, #0, %[value], c7, c10, #1" ::[value] "r" (ptr));

        ptr += 64;
    }
}

/**
 * \brief     This API Configures translation table base register 0 with
 *            with page table starting address.
 *
 * \param     ttb  is the starting address of the pageTable.
 *
 * \return    None.
 *
 *  Note : Page Table starting address should be aligned to 16k.
 **/
void CP15Ttb0Set(uint32_t ttb)
{
    /* sets translation table base resgister with page table
     * starting address.
     */
    asm ("   mcr p15, #0, %[value], c2, c0, 0" ::[value] "r" (ttb));
}

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
         "   ldr r1, =0x55555555\n\t"
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
void CP15VectorBaseAddrSet(uint32_t addr)
{
    asm ("   mcr p15, #0, %[value], c12, c0, 0" ::[value] "r" (addr));
}

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
    asm ("    ldr r0, =0x55555555 \n\t"
         "    mcr p15, #0, r0, c3, c0, #0");
}

void setSvMode(void)
{
    asm ("    MOV     r0, #0xD3  \n\t"
         "    MSR     cpsr_c, r0  \n\t"
         "    MOV     sp, r0 \n\t"
         "    SUB     r0, r0, #0x200 \n\t"
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

void CP15FPUEnable(void)
{
    asm ("movw r0, #0x0000 \n\t"
         "movt r0, #0x00F0 \n\t"
         "mcr p15, #0, r0, c1, c0, #2 \n\t"
         "isb \n\t"
         "movw r0, #0x0000  \n\t"
         "movt r0, #0x4000  \n\t"
         "fmxr fpexc, r0"
         );

/*set the FPEXC.EN bit to enable Advanced SIMD and VFP      */

/*gcc does not support UAL equivalent
 *                                                                      */
/*instruction, vmsr*/
}

/********************************* End Of File ********************************/
