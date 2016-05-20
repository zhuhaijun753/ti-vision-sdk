/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


/**
 *  @file       IBAMALG_create.c
 *
 *  @brief      Example file that shows algorithm creation
 */

#pragma CHECK_MISRA ("none")
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <vcop.h>
#pragma RESET_MISRA ("required")

#include "alg_osal.h"
#include "bam.h"
#include "ibamalg_create.h"

/* CHECK_MISRA("-15.1")  -> Disable rule 15.1 */
/* Goto statement is used */
/* Deviation is allowed because all the GOTOs point to a single exit point */

/**
 * Allocated the MemTabs
 * DMEM is handled specially as differnt algorithms can share it.
 */
int32_t IBAMALG_allocMemRecs( IBAMALG_MemRec memRec[], uint32_t numMemRecs, const ALGOSAL_MemAllocator *memAllocator)
{
    uint32_t i;
    int32_t status = IBAMALG_S_SUCCESS;
    
     /* CHECK_MISRA("-14.6")  -> Disable rule 14.6 */
     /* Iteration statement has more than one break or goto for loop termination */
     /* Deviation is allowed because all the GOTOs point to a single exit point */
    for (i = 0; i < numMemRecs; i++)
    {
        /* allocate the base memory - could be internal or external memory */
        if ((memRec[i].size!= 0) && (memRec[i].base == NULL))
        {
            void *mem = memAllocator->sysMalloc(memRec[i].space, memRec[i].size);
            memRec[i].base = mem;
            if (memRec[i].base == NULL)
            {
                PRINTF("IBAMALG Malloc error !\n");
                status = IBAMALG_E_FAIL;
                goto Exit;
            }
#ifdef SHOW_MEM
            PRINTF("[IBAMALG]\t%d\t0x%x\t0x%x\t%d\n", i, memRec[i].base, memRec[i].size, memRec[i].space);
#endif
        }

        /* if the space for base is internal memory, allocate an additional external memory to enable context save/restore. */
        if ((memRec[i].size!= 0) && (memRec[i].ext == NULL) && (memRec[i].space != BAM_MEMSPACE_EXTMEM) &&
            (memRec[i].attrs.memAttrs != BAM_MEMATTRS_SCRATCH))
        {
            void *mem = memAllocator->sysMalloc(BAM_MEMSPACE_EXTMEM, memRec[i].size);
            memRec[i].ext = mem;
            if (mem == NULL)
            {
                PRINTF("IBAMALG Malloc error !\n");
                status = IBAMALG_E_FAIL;
                goto Exit;
            }
#ifdef SHOW_MEM
 /*           PRINTF("memRec[%d].ext= 0x%x \tsize= %d \tspace= %d\n", i, memRec[i].ext, memRec[i].size, memRec[i].space); */
#endif
        }
    }
    /* RESET_MISRA("14.6")  -> Reset rule 14.6*/

Exit:
    return status;
}

/**
 * Allocate the MemRecs which request internal memory only
 * DMEM is handled specially as differnt algorithms can share it.
 */
int32_t IBAMALG_allocMemRecsInt(IBAMALG_MemRec memRec[], uint32_t numMemRecs)
{
    uint32_t i;
    int32_t status = IBAMALG_S_SUCCESS;

    for (i = 0; i < numMemRecs; i++)
    {
        /* allocate the base memory - could be internal memory */
        if ((memRec[i].size!= 0) && (memRec[i].base == NULL) && (memRec[i].space != BAM_MEMSPACE_EXTMEM))
        {
            void *mem = ALGOSAL_malloc(memRec[i].space, memRec[i].size);
            memRec[i].base = mem;
            if (memRec[i].base == NULL)
            {
                PRINTF("IBAMALG Malloc error !\n");
                status = IBAMALG_E_FAIL;
                break;
            }
        }
    }
    return status;
}

int32_t IBAMALG_freeMemRecsInt(IBAMALG_MemRec memRec[], uint32_t numMemRecs, uint32_t freeDMEM)
{
    uint32_t i;
    int32_t status = IBAMALG_S_SUCCESS;

    /* Free VCOP memories, so that another algorithm can use it. IT is not safe to do this for DMEM as system might also need it. */
    for (i=0; i<numMemRecs; i++)
    {
        uint32_t space = memRec[i].space;
        if(memRec[i].base)
        {
            if( (space == (uint32_t)BAM_MEMSPACE_IBUFLA) || (space == (uint32_t)BAM_MEMSPACE_IBUFLB) || (space == (uint32_t)BAM_MEMSPACE_IBUFHA) ||
                (space == (uint32_t)BAM_MEMSPACE_IBUFHB) || (space == (uint32_t)BAM_MEMSPACE_WBUF)
#ifdef ENABLE_CNTXT_SAVE_RESTORE
                || ((freeDMEM!=0) && (space == (uint32_t)BAM_MEMSPACE_DMEM))

#endif
              )
            {
                ALGOSAL_free(memRec[i].space, memRec[i].base);
            }
        }
    }
    return status;
}


/**
    *              Sample (meaning, a typical) delete function. Apps can call this to delete the handles.
    *              If this implementation of create doesnot serve the purpose, apps can choose to
    *             write their own delete function. Note: x is for example
    */
int32_t IBAMALG_create(const IBAMALG_Fxns *fxns, IBAMALG_Handle *handle, const IBAMALG_Params *params,
                      const  ALGOSAL_MemAllocator *memAllocator)
{

    uint32_t i;
    int32_t status = IBAMALG_S_SUCCESS;
    IBAMALG_MemRec (*memRec)[];
    uint32_t numMemRecs = 0;
    size_t memRecSize = 0;

    int32_t maxMemAvailable[IBAMALG_MEMHEAP_NUM];

    if(fxns->algNumAlloc)
    {
        numMemRecs = fxns->algNumAlloc(params);
    }
    else
    {
        PRINTF("IBAMALG_create(): algNumAlloc() is not implemeted. Memory cannot be freed.\n");
        status = IBAMALG_E_FAIL;
        goto Exit;
    }

    /* Will remove later, used now in case of multiple graph */
    for(i=0; i<IBAMALG_MEMHEAP_NUM; i++)
    {
        maxMemAvailable[i] = memAllocator->sysMemMaxSize(i);
    }

    /* Allocate space for memRec array */
    memRecSize = sizeof(IBAMALG_MemRec)*numMemRecs;
    memRec = (IBAMALG_MemRec (*)[])memAllocator->sysMalloc(BAM_MEMSPACE_EXTMEM, memRecSize);

    for (i = 0; i < numMemRecs; i++)
    {
        (*memRec)[i].size = 0;
        (*memRec)[i].base = 0;
        (*memRec)[i].ext = 0;
        (*memRec)[i].space = VCOP_MEMSPACE_NONE;
    }

    /* allocate the handle */
    if(fxns->algAlloc)
    {
        status = fxns->algAlloc((const IBAMALG_Params *) params, maxMemAvailable, IBAMALG_MEMHEAP_NUM, (*memRec), numMemRecs);
    }
    if (status != IBAMALG_S_SUCCESS)
    {
        goto Exit;
    }


    status = IBAMALG_allocMemRecs(*memRec, (numMemRecs), memAllocator);
    if (status != IBAMALG_S_SUCCESS)
    {
        goto Exit;
    }

    /* initialize */
    status = fxns->algInit(handle, (const IBAMALG_Params *)params, *memRec, numMemRecs);

    /* Free whatever was allocated in BAM_MEMSPACE_DMEM if context save/restore enabled */
    for (i=0; i<numMemRecs; i++)
    {
        if((*memRec)[i].base)
        {
#ifdef ENABLE_CNTXT_SAVE_RESTORE
            if ((*memRec)[i].space == BAM_MEMSPACE_DMEM)
            {
                memAllocator->sysFree((*memRec)[i].space, (*memRec)[i].base);
            }
#endif
        }
    }

    /* Free local memRec */
    memAllocator->sysFree(BAM_MEMSPACE_EXTMEM, (*memRec));

Exit:
    return status;
}


int32_t IBAMALG_delete(const IBAMALG_Handle handle, const ALGOSAL_MemAllocator *memAllocator)
{
    int32_t status = IBAMALG_S_SUCCESS;
    uint32_t i;
    IBAMALG_MemRec (*memRec)[];
    uint32_t numMemRecs = 0;
    size_t memRecSize = 0;

    if(handle->numMemRecs== 0)
    {
        PRINTF("IBAMALG_delete(): handle->numMemRecs is not available. Memory cannot be freed.\n");
        status = IBAMALG_E_FAIL;
        goto Exit;
    }

    /* Allocate space for memRec array */
    memRecSize = sizeof(BAM_MemRec)*(handle->numMemRecs);
    memRec = (IBAMALG_MemRec(*)[])memAllocator->sysMalloc(BAM_MEMSPACE_EXTMEM, memRecSize);
    numMemRecs = handle->numMemRecs;
    for (i = 0; i < (numMemRecs); i++)
    {
        (*memRec)[i].size = 0;
        (*memRec)[i].base = 0;
        (*memRec)[i].ext = 0;
        (*memRec)[i].space = VCOP_MEMSPACE_NONE;
    }

    if(handle->fxns->algFree)
    {
        handle->fxns->algFree(handle, (*memRec), numMemRecs);
    }
    else
    {
        PRINTF("IBAMALG_delete(): AlgFree() is not implemeted. Memory cannot be freed.\n");
        status = IBAMALG_E_FAIL;
        goto Exit;
    }

    for (i=0; i<numMemRecs; i++)
    {
        uint32_t space = (*memRec)[i].space;
        if((*memRec)[i].base)
        {
            /* VCOP memories are already freed. Nothing to be done for them */
            if((space == (uint32_t)BAM_MEMSPACE_EXTMEM)
#ifndef ENABLE_CNTXT_SAVE_RESTORE
                || (space == BAM_MEMSPACE_DMEM)
#endif
              )
            {
                memAllocator->sysFree((*memRec)[i].space, (*memRec)[i].base);
            }
        }

        if(((*memRec)[i].ext!= NULL) && ((*memRec)[i].attrs.memAttrs != BAM_MEMATTRS_CONST))
        {
            memAllocator->sysFree(BAM_MEMSPACE_EXTMEM, (*memRec)[i].ext);
        }
    }

    /* Free local memRec */
    memAllocator->sysFree(BAM_MEMSPACE_EXTMEM, (*memRec));

#if 0
    DMANODE_qdmaGlobalDeint();
#endif

Exit:
    return status;
}


/**
*    Context Save
*/
int32_t IBAMALG_contextSaveMemRec(BAM_MemRec *memRec)
{
    int32_t status = IBAMALG_S_SUCCESS;

    status = BAM_contextSaveMemRec(memRec);

    return status;
}


/**
*    Context Restore
*/
int32_t IBAMALG_contextRestoreMemRec(BAM_MemRec *memRec)
{
    int32_t status = IBAMALG_S_SUCCESS;
    
    status = BAM_contextRestoreMemRec(memRec);

    return status;
}

/* RESET_MISRA("15.1")  -> Reset rule 15.1*/


