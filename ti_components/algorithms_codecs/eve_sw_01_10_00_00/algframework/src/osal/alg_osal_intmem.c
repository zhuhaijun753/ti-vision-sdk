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

#include "alg_osal_extmem.h"
#include "alg_osal.h"


/**
 * DMEM space reserve for algorithms.
 */
#define ALG_DMEM_SIZE (0x4000UL)
#if (!VCOP_HOST_EMULATION)
near uint8_t gALGOSAL_algDMEM[ALG_DMEM_SIZE];
near uint32_t gALGOSAL_algDMEMIndex = 0;
#else
uint8_t gALGOSAL_algDMEM[ALG_DMEM_SIZE];
uint32_t gALGOSAL_algDMEMIndex = 0;
#endif

/* 
  Internal memory function declaraionts 
*/
void    ALGOSAL_intMinit   (IBAMALG_MemHeap heap);
void   *ALGOSAL_intMalloc  (IBAMALG_MemHeap heap, size_t size);
void    ALGOSAL_intFree    (IBAMALG_MemHeap heap, void *userptr);
int32_t ALGOSAL_intMemMax  (IBAMALG_MemHeap heap);

void  ALGOSAL_intMinit(IBAMALG_MemHeap heap)
{

    if(heap < IBAMALG_MEMHEAP_DMEM)
    {
        vcop_minit();
    }
    else if(heap == IBAMALG_MEMHEAP_DMEM)
    {
        gALGOSAL_algDMEMIndex = 0;
    }     
    else if(heap == IBAMALG_MEMHEAP_EXTMEM)
    {
        /* ALGOSAL_extMemInit(); */ /* this is now handled my extmem module */
        PRINTF("Error: ALGOSAL_intMinit() of external memory is not supported.\n");
    }
    else
    {
        PRINTF("Error: ALGOSAL_intMinit(), heap argument value invalid.\n");
        /* It is not allowed to init external memory except at start */
        /* return minit(); */
    }

    return;

}


void *ALGOSAL_intMalloc(IBAMALG_MemHeap heap, size_t size)
{
    void *ptr = 0;
    
    if(heap < IBAMALG_MEMHEAP_DMEM)
    {
        ptr =  vcop_malloc((VCOP_MEMHEAP)heap, size);
    }
    else if(heap == IBAMALG_MEMHEAP_DMEM)
    {
        ptr = &gALGOSAL_algDMEM[gALGOSAL_algDMEMIndex];
        gALGOSAL_algDMEMIndex += size;
        /* If not enough memory, rewind gALGOSAL_algDMEMIndex */
        if (gALGOSAL_algDMEMIndex > ALG_DMEM_SIZE) {
            gALGOSAL_algDMEMIndex-= size;
            ptr= NULL;
        }
    }
    else if(heap == IBAMALG_MEMHEAP_EXTMEM)
    {
        /* ptr =   ALGOSAL_extMemAlloc(size); */ /* this is now handled my extmem module */
        PRINTF("Error: ALGOSAL_intMalloc(), allocation in external memory not supported.\n");
    }     
    else
    {
        PRINTF("Error: ALGOSAL_intMalloc(), heap argument value invalid.\n");
    }
    
    return ptr;
}

/*
 * size is added to align the header with BIOS MEM_free. Currently not used.
 */
void ALGOSAL_intFree(IBAMALG_MemHeap heap, void *userptr)
{
    /*------------------------------------------------------------------------*/
    /* If pointer is NULL, just return                                        */ 
    /*-----------------------------------------------------------------------*/
    if (userptr != 0)
    {
        if(heap < IBAMALG_MEMHEAP_DMEM)
        {
            vcop_free(userptr);
        }
        else if(heap == IBAMALG_MEMHEAP_DMEM)
        {
            gALGOSAL_algDMEMIndex = 0; 
        }
        else if(heap == IBAMALG_MEMHEAP_EXTMEM)
        {
            /* ALGOSAL_extMemFree(userptr); */ /* this is now handled my extmem module */
            PRINTF("Error: ALGOSAL_intMalloc(), allocation in external memory not supported.\n");
        }
        else
        {
            PRINTF("Error: ALGOSAL_intMalloc(), heap argument value invalid.\n");
        }
    }
}

/*----------------------------------------------------------------------------
* ALNBYTES is the amount by which the allocation should be aligned: 32 bytes
*---------------------------------------------------------------------------*/
#define ALNBYTES 0x20

/**
 * Total heap seems to required to be atleast greater by this much compared to what is requested.
 * 32 bytes is sufficient for LBUF/WBUF, but 256 bytes seem to be required for DMEM (malloc)
 */
#define EXTRA_BYTES_HEAP (0)

#if (!VCOP_HOST_EMULATION)
extern int32_t IMEML_SIZE[1];
extern int32_t IMEMH_SIZE[1];
extern int32_t WMEM_SIZE[1];
#endif
int32_t ALGOSAL_intMemMax(IBAMALG_MemHeap heap)
{
    int32_t maxAvailable = 0;
#if (!VCOP_HOST_EMULATION)
    int32_t ptrval = 0;
    
    switch(heap)
    {
        case IBAMALG_IBUFLA:
        {
            ptrval = (int32_t)IMEML_SIZE;
            maxAvailable = ptrval? ((ptrval -(int32_t)ALNBYTES)- (int32_t)ALNBYTES) : 0;
            break;
        }
        case IBAMALG_IBUFHA:
            ptrval = (int32_t)IMEMH_SIZE;
            maxAvailable = ptrval? ((ptrval -(int32_t)ALNBYTES)- (int32_t)ALNBYTES) : 0;
            break;
        case IBAMALG_IBUFLB:
            ptrval = (int32_t)IMEML_SIZE;
            maxAvailable = ptrval? ((ptrval -(int32_t)ALNBYTES)- (int32_t)ALNBYTES) : 0;
            break;
        case IBAMALG_IBUFHB:
            ptrval = (int32_t)IMEMH_SIZE;
            maxAvailable = ptrval? ((ptrval -(int32_t)ALNBYTES)- (int32_t)ALNBYTES) : 0;
            break;
        case IBAMALG_WMEM:
            ptrval = (int32_t)WMEM_SIZE;
            maxAvailable = ptrval? ((ptrval -(int32_t)ALNBYTES) - (int32_t)ALNBYTES) : 0;
            break;
        case IBAMALG_MEMHEAP_DMEM:
            ptrval = (int32_t)ALG_DMEM_SIZE; /*(int32_t)((size_t)&__TI_SYSMEM_SIZE);*/
            maxAvailable = ptrval? ((ptrval -(int32_t)ALNBYTES) - (int32_t)EXTRA_BYTES_HEAP) : 0;
            break;
        default:
            /* maxAvailable = ALGOSAL_extMemMax(); */ /* this is now handled my extmem module */
            break;
    }
#endif    
    /*----------------------------------------------------------------
    * return available memory size
    *---------------------------------------------------------------*/
    return maxAvailable;
}


