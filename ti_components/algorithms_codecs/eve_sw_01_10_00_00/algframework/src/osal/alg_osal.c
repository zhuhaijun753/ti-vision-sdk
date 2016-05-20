/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#pragma CHECK_MISRA ("none")
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#if (!VCOP_HOST_EMULATION)
#include <_lock.h>
#endif
#include "vcop.h"

#include "alg_osal.h"
#include "alg_osal_extmem.h"

#pragma RESET_MISRA ("required")

#pragma CHECK_MISRA ("none")
#include "evestarterware.h"
#if PRINTF_TYPE == PRINTF_TYPE_UART
#include "zebu_uart/inc/uartlib.h"
#endif
#pragma RESET_MISRA ("required")


/* 
  Internal memory function declarations
*/
extern void    ALGOSAL_intMinit   (IBAMALG_MemHeap heap);
extern void   *ALGOSAL_intMalloc  (IBAMALG_MemHeap heap, size_t size);
extern void    ALGOSAL_intFree    (IBAMALG_MemHeap heap, void *userptr);
extern int32_t ALGOSAL_intMemMax  (IBAMALG_MemHeap heap);


void  ALGOSAL_minit(IBAMALG_MemHeap heap)
{
    if(heap <= IBAMALG_MEMHEAP_DMEM)
    {
        ALGOSAL_intMinit(heap);
    }
    else if(heap == IBAMALG_MEMHEAP_EXTMEM)
    {
        /* minit() of external memory is not supported - except at startup */
        /* ALGOSAL_extMemInit(); */
        PRINTF("Error: minit() of external memory is not supported.\n");
    }
    else
    {
        PRINTF("Error: minit(), heap argument value invalid.\n");
    }

    return;
}


void *ALGOSAL_malloc(IBAMALG_MemHeap heap, size_t size)
{
    void *ptr = 0;

    if(heap <= IBAMALG_MEMHEAP_DMEM)
    {
        ptr =  ALGOSAL_intMalloc(heap, size);
    }
    else if(heap == IBAMALG_MEMHEAP_EXTMEM)
    {
        ptr =   ALGOSAL_extMemAlloc(size);
    }
    else
    {
        PRINTF("Error: ALGOSAL_malloc(), heap argument value invalid.\n");
    }

    return ptr;
}

/*
 * size is added to align the header with BIOS MEM_free. Currently not used.
 */
void ALGOSAL_free(IBAMALG_MemHeap heap, void *userptr)
{
    /*------------------------------------------------------------------------*/
    /* If pointer is NULL, just return                                        */
    /*-----------------------------------------------------------------------*/
    if (userptr != 0)
    {
        if(heap <= IBAMALG_MEMHEAP_DMEM)
        {
            ALGOSAL_intFree(heap, userptr);
        }
        else if(heap == IBAMALG_MEMHEAP_EXTMEM)
        {
            ALGOSAL_extMemFree(userptr);
        }
        else
        {
            PRINTF("Error: ALGOSAL_free(), heap argument value invalid.\n");
        }
    }
}



int32_t ALGOSAL_memMax(IBAMALG_MemHeap heap)
{
    int32_t maxAvailable = 0;

    if(heap <= IBAMALG_MEMHEAP_DMEM)
    {
        maxAvailable = ALGOSAL_intMemMax(heap);
    }
    else if(heap == IBAMALG_MEMHEAP_EXTMEM)
    {
        maxAvailable = ALGOSAL_extMemMax();
    }
    else
    {
        PRINTF("Error: ALGOSAL_memMax(), heap argument value invalid.\n");
    }

    /*----------------------------------------------------------------
    * return available memory size
    *---------------------------------------------------------------*/
    return maxAvailable;
}


/*
 A sample allocator defined
*/
const ALGOSAL_MemAllocator gALGOSAL_memAllocator = {&ALGOSAL_malloc, &ALGOSAL_free, &ALGOSAL_minit, &ALGOSAL_memMax};

char gALGOSAL_memPrintfArr[ALGOSAL_PRINTF_MEM_SIZE] = {0};

/* CHECK_MISRA("-16.1")  -> Disable rule 16.1  */
/* Function with variable number of arguments */
/* Deviation allowed since these functions are wrapper around printf() function, which accept variable number of arguments  */

/* CHECK_MISRA("-20.9")  -> Disable rule 20.9  */
/* Use of input/output library stdio.h in production code */
/* Deviation allowed since these functions are only enabled if PRINTF_TYPE == PRINTF_TYPE_STANDARD, which should be unset in production code  */

/* CHECK_MISRA("-20.1 - 20.5 - 20.6 - 20.7 - 20.8")  -> Disable rules  */
/* Unsafe macro stdout is used */
/* Deviation allowed since stdout is only used if PRINTF_TYPE == PRINTF_TYPE_STANDARD, which should be unset in production code  */

void ALGOSAL_printf(const char * text, ...)
{
#if PRINTF_TYPE == PRINTF_TYPE_STANDARD
    va_list argptr;
    va_start(argptr, text);
    vfprintf(stdout, text, argptr);
    va_end(argptr);
#elif PRINTF_TYPE == PRINTF_TYPE_UART
    va_list argptr;
    va_start(argptr, text);
    vuart1_write_formated(text, argptr);
    va_end(argptr);
#else
    va_list argptr;
    va_start(argptr, text);
    memset(gALGOSAL_memPrintfArr, 0, sizeof(gALGOSAL_memPrintfArr));
    vsprintf(gALGOSAL_memPrintfArr, text, argptr);
    va_end(argptr);
#endif
}

/* to be removed and replaced with ALGOSAL_printf */
void PRINTF(const char * text, ...)
{
#if PRINTF_TYPE == PRINTF_TYPE_STANDARD
    va_list argptr;
    va_start(argptr, text);
    vfprintf(stdout, text, argptr);
    va_end(argptr);
    fflush(stdout);
#elif PRINTF_TYPE == PRINTF_TYPE_UART
    va_list argptr;
    va_start(argptr, text);
    vuart1_write_formated(text, argptr);
    va_end(argptr);
#else
    va_list argptr;
    va_start(argptr, text);
    memset(gALGOSAL_memPrintfArr, 0, sizeof(gALGOSAL_memPrintfArr));
    vsprintf(gALGOSAL_memPrintfArr, text, argptr);
    va_end(argptr);
#endif
}

/* Used only for printfs in standalone test files */
void TEST_PRINTF(const char * text, ...)
{
#ifndef EN_ZEBU_TEST
    va_list argptr;
    va_start(argptr, text);
    vfprintf(stdout, text, argptr);
    va_end(argptr);
    fflush(stdout);    
#else
    va_list argptr;
    va_start(argptr, text);
    vuart1_write_formated(text, argptr);
    va_end(argptr);
#endif
}
/* RESET_MISRA("16.1")  -> Reset rule 16.1*/
/* RESET_MISRA("20.9")  -> Reset rule 20.9*/
/* RESET_MISRA("-20.1 - 20.5 - 20.6 - 20.7 - 20.8")  -> Reset rules */

