/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/****************************************************************************/
/*  bam_mempkt.h v1.0.2 - Common declarations for ARP32/VCOP memory         */
/*                        allocation                                        */
/****************************************************************************/

#ifndef _BAM_MEMPKT_H
#define _BAM_MEMPKT_H
#include <stddef.h>
#include "bam_common.h"

/* DEBUG_BAM_MALLOC only works when HOST emulation is turned off */
#if (VCOP_HOST_EMULATION==0)
/*#define DEBUG_BAM_MALLOC*/
#endif

#if (VCOP_HOST_EMULATION==1)
typedef enum memview
{
    VCOP_MEMFLAT = 0,
    VCOP_MEMALIASED
} VCOP_MEMVIEW;
#endif

/* Guard value that is added to the number of available memory packets to ensure that the pool of memory packets is big enough
 * has the maximum number of memory records in each memory heap. */
#define BAM_NUM_GUARD_PACKETS 0

/*----------------------------------------------------------------------------
 * "BAM_Packet" is the template for a memory data packet. "packet_size" is the
 * number of words allocated for the user, excluding the size "OVERHEAD"
 * required for management of the packet. When a packet is on the free list, the
 * field "next_free" is a pointer to the next member of the freelist; when the
 * packet is in use (allocated), this field is invalid, overwritten by user data
 * (the address of this field is the address returned by malloc). A negative
 * size indicates a free packet.
 *---------------------------------------------------------------------------*/
typedef ptrdiff_t memsz_t;
typedef struct fpack
{
    memsz_t packet_size; /* in words */
    struct fpack *next_free;
    struct fpack *apacket; /* alias packet */
    void *uaptr; /* unaligned ptr */
    void *ptr;   /* aligned ptr */
    int32_t heap; /* 0: free packet, other value correspond to the heap it belongs to */ 
} BAM_Packet;

/*----------------------------------------------------------------------------
 * LIMIT is used to initialize the initial "next_free" pointer
 *---------------------------------------------------------------------------*/
#define LIMIT   ((BAM_Packet *) (void*)0xFFFFFFFFU)

/*----------------------------------------------------------------------------
 * OVERHEAD is the space in the packet required to store the packet size. This
 * macro is used for two purposes: to compute the size of the allocation, and
 * to ensure that the packet is properly aligned.
 *---------------------------------------------------------------------------*/
#define OVERHEAD (offsetof(BAM_Packet, next_free))

/*----------------------------------------------------------------------------
 * Utility macro to round up the value to be a multiple of aln.
 *---------------------------------------------------------------------------*/
 
/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* This macro has to accept 2 arguments */
#define RNDUP(val,aln) ((uint32_t)((val) + ((uint32_t)(aln)-1U)) & ~((uint32_t)(aln)-1U))
/* RESET_MISRA("19.7")  -> Reset rule 19.7 */

/*----------------------------------------------------------------------------
 * Generic memory allocation / free prototypes
 *---------------------------------------------------------------------------*/
void bam_setview(VCOP_MEMVIEW view);
int32_t bam_minit(BAM_Packet *packet_pool, int32_t num_packets);
int32_t bam_mcheck(void);
BAM_Packet *bam_getMemPacket(VCOP_MEMHEAP heap, int32_t alignment, size_t size);
BAM_Packet *bam_get_packet(int32_t heap);
BAM_Packet *bam_mem_alloc(BAM_Packet **free_mem, size_t allocsize, int32_t heap);
void bam_releaseMemPacket(BAM_Packet *packet);
void bam_mem_free(BAM_Packet **free_mem, BAM_Packet *packet);
BAM_Packet *bam_get_packet(int32_t heap);
int32_t bam_put_packet(BAM_Packet *packet);

#endif /* _MEMPKT_H */
