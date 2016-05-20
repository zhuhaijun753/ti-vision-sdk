/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#ifndef EVE_OSAL_H
#define EVE_OSAL_H

#pragma CHECK_MISRA ("none")
#include <stdlib.h>
#include <vcop.h>
#include <stdint.h>
#pragma RESET_MISRA ("required")

#include "alg_osal_extmem.h"

#define ALGOSAL_PRINTF_MEM_SIZE 1024U
#define PRINTF_TYPE_STANDARD 0U
#define PRINTF_TYPE_UART     1U
#define PRINTF_TYPE_SPRINTF  2U

/*
 Set the actual printf to use.
 Setting to PRINTF_TYPE_SPRINTF will allow a common .lib to be used for virtio and fpga.
*/
#define PRINTF_TYPE          (PRINTF_TYPE_STANDARD) /* In production code this should be set to PRINTF_TYPE_SPRINTF */

typedef int32_t IBAMALG_MemHeap;

#if (VCOP_HOST_EMULATION)
typedef enum memheap
{
    VCOP_NONE   = -1,
    VCOP_IBUFLA = 0,
    VCOP_IBUFHA,
    VCOP_IBUFLB,
    VCOP_IBUFHB,
    VCOP_WMEM
} VCOP_MEMHEAP;
#endif
typedef enum IBAMALG_mem_heap_enum_id
{
    IBAMALG_NONE    = (VCOP_NONE),
    IBAMALG_IBUFLA  = (VCOP_IBUFLA),
    IBAMALG_IBUFHA  = (VCOP_IBUFHA),
    IBAMALG_IBUFLB  = (VCOP_IBUFLB),
    IBAMALG_IBUFHB  = (VCOP_IBUFHB),
    IBAMALG_WMEM    = (VCOP_WMEM),

    IBAMALG_ANY_VCOPBUF            =( VCOP_WMEM+1),
    IBAMALG_MEMHEAP_DMEM           = (VCOP_WMEM+2),
    IBAMALG_MEMHEAP_EXTMEM         = (VCOP_WMEM+3),
    
    IBAMALG_MEMHEAP_INTMEM_NUM     = (IBAMALG_MEMHEAP_DMEM+1),    
    IBAMALG_MEMHEAP_NUM            = (IBAMALG_MEMHEAP_EXTMEM+1)

}IBAMALG_MemHeapId;


/*
 Functions used for external and internal memory allocation
*/
void    ALGOSAL_minit(IBAMALG_MemHeap heap);
void   *ALGOSAL_malloc(IBAMALG_MemHeap heap, size_t size);
void    ALGOSAL_free(IBAMALG_MemHeap heap, void *userptr);
int32_t ALGOSAL_memMax(IBAMALG_MemHeap heap);


typedef void    *(*ALGOSAL_mallocType) (IBAMALG_MemHeap heap, size_t size);
typedef void     (*ALGOSAL_freeType)   (IBAMALG_MemHeap heap, void *userptr);
typedef void     (*ALGOSAL_minitType)  (IBAMALG_MemHeap heap);
typedef int32_t  (*ALGOSAL_maxType)    (IBAMALG_MemHeap heap);


/**
*  @brief      Structure containing pointers to various memory management functions.
*
*/
typedef struct ALGOSAL_MemAllocatorStruct
{
    ALGOSAL_mallocType sysMalloc;       /**< Pointer to OSAL memory allocation function */
    ALGOSAL_freeType sysFree;           /**< Pointer to OSAL memory free function */
    ALGOSAL_minitType sysMinit;         /**< Pointer to OSAL memory init function */
    ALGOSAL_maxType sysMemMaxSize;      /**< Pointer to OSAL memory maximum size returnig function */
} ALGOSAL_MemAllocator;

/*
 A sample allocator defined
*/
extern const ALGOSAL_MemAllocator gALGOSAL_memAllocator;

/* CHECK_MISRA("-16.1")  -> Disable rule 16.1  */
/* Function with variable number of arguments */
/* Deviation allowed since these functions are wrapper around printf() function, which accept variable number of arguments  */
void ALGOSAL_printf(const char * text, ...);
void PRINTF(const char * text, ...);

/* Used only for printfs in standalone test files */
void TEST_PRINTF(const char * text, ...);
/* RESET_MISRA("16.1")  -> Reset rule 16.1*/

extern char gALGOSAL_memPrintfArr[ALGOSAL_PRINTF_MEM_SIZE];

#endif

