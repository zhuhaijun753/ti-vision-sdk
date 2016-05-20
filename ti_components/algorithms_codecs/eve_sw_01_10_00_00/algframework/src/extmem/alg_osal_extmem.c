/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#pragma CHECK_MISRA ("none")
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#if (!VCOP_HOST_EMULATION)
#include <_lock.h>
#endif
#include "vcop.h"
#pragma RESET_MISRA ("required")

#include "alg_osal.h"

/*----------------------------------------------------------------------------
* VCOP_MINIT - This function performs the initial setup of the heap.
*---------------------------------------------------------------------------*/
void ALGOSAL_extMemInit(void)
{
}


/*----------------------------------------------------------------------------
* IBAMALG_MALLOC - Allocate a packet of a given size from a given heap and return
*               an aligned memory pointer to it.
*---------------------------------------------------------------------------*/
void *ALGOSAL_extMemAlloc(int32_t size)
{
    PRINTF("Error, dynamic allocation in external memory not allowed per MISRA-C rule\n");
    return NULL;
    /*return malloc(size); */
}

/*----------------------------------------------------------------------------
* IBAMALG_FREE - Return a packet allocated by IBAMALG_malloc to the  free memory
*             pool.  The algorithm will automatically calculate which heap from
*             which to free the memory.
*---------------------------------------------------------------------------*/
void ALGOSAL_extMemFree(void *userptr)
{
    PRINTF("Error, dynamic allocation in external memory not allowed per MISRA-C rule\n");
    /*free(userptr);*/
    return;
}

#if (!VCOP_HOST_EMULATION)
/* Indicates heap size. see memory.c in rtssrc */
/* CHECK_MISRA("-20.2")  -> Disable rule 20.2 */
/* Usage of a reserved name for naming a language entity */
/* Deviation is allowed because the symbol __TI_SYSMEM_SIZE is not the name of any language entity*/
extern int32_t __TI_SYSMEM_SIZE;
/* RESET_MISRA("20.2")  -> Reset rule 20.2*/

/*----------------------------------------------------------------------------
* ALNBYTES is the amount by which the allocation should be aligned: 32 bytes
*---------------------------------------------------------------------------*/
#define ALNBYTES 0x20

/**
 * Total heap seems to required to be atleast greater by this much compared to what is requested.
 * 32 bytes is sufficient for LBUF/WBUF, but 256 bytes seem to be required for DMEM (malloc)
 */
#define EXTRA_BYTES_HEAP (256)

int32_t ALGOSAL_extMemMax(void)
{
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3 */
    /* Cast between a pointer and an integral type */
    /* Deviation is allowed because conversion is necessary in order to perform pointer arithmetic  */
    int32_t ptrval = (int32_t)(&__TI_SYSMEM_SIZE);
    /* RESET_MISRA("11.3")  -> Reset rule 11.3*/
    int32_t maxAvailable = (ptrval -(int32_t)ALNBYTES - (int32_t)EXTRA_BYTES_HEAP);
    /*----------------------------------------------------------------
    * return available memory size
    *---------------------------------------------------------------*/
    return maxAvailable;
}
#else
 int32_t ALGOSAL_extMemMax(void)
{
    
    return 0;
}
#endif


