/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


#ifndef IBAMALG_CREATE_H
#define IBAMALG_CREATE_H

#if 0
#include <vcop.h>
#include <stdio.h>
#endif

#include "ibamalg.h"
#if 0
#include "ibamalg_memory.h"
#endif

#define ENABLE_CNTXT_SAVE_RESTORE


/**
 *  @brief      Allocates an array of memRecs. It can allocate both internal memory and external memory if needed.
 *
 *  @param      memRec          Array of IBAMALG_MemRec containing information about the memories need to be allocated.
 *  @param[in]  numMemRecs      Number of IBAMALG_MemRec in the array.
 *  @param[out] memAllocator    OSAL memory utility descriptor.
 *
 *  @retval     int32_t
 *
 *  @remarks    This function allocates requested memory using memory allocator function defined in the memAllocator and popuates the .base of the memRec.
 *              A memory of same size will be allocated in the external memory except for BAM_MEMATTRS_SCRATCH in the .ext field of the memRec.
 *              This external memory copy can be used for context switching purposes. If the requested memory space is already BAM_MEMSPACE_EXTMEM its external memory
 *              copy will not be allocated.
 *  @remarks    A memRec with zero .size field will be skipped from any allocation . MemRecs with nonzero .base or .ext fields will be exempted from allocation 
 *              of that particular memory space. This is for avoiding re-allocation of already allocated memRecs in the list.
 *              
 */
int32_t IBAMALG_allocMemRecs( IBAMALG_MemRec memRec[], uint32_t numMemRecs, const ALGOSAL_MemAllocator *memAllocator);

/**
 *  @brief      Allocates an array of memRecs. It can allocates only internal memory requirement.
 *
 *  @param      memRec          Array of IBAMALG_MemRec containing information about the memories need to be allocated.
 *  @param[in]  numMemRecs      Number of IBAMALG_MemRec in the array.
 *
 *  @retval     int32_t
 *
 *  @remarks    This function allocates requested internal memory popuates the .base of the memRec.
 *              If the requested memory space is BAM_MEMSPACE_EXTMEM which is not an internal memory space and hence will be not be allocated
 *
 *  @remarks    A memRec with zero .size field will be skipped from any allocation . MemRecs with nonzero .base field will be exempted from allocation.
 *              This is for avoiding re-allocation of already allocated memRecs in the list.
 *              
 */
int32_t IBAMALG_allocMemRecsInt(IBAMALG_MemRec memRec[], uint32_t numMemRecs);

/**
 *  @brief      Frees an array of memRecs. It can frees only internal memory requirements.
 *
 *  @param      memRec          Array of IBAMALG_MemRec containing information about the memories need to be freed.
 *  @param[in]  numMemRecs      Number of IBAMALG_MemRec in the array.
 *  @param[in]  freeDMEM        Indicates whether DMEM should be freed or not. This is becasue DMEM is sometimes allocated inside the algorithm,
 *                              in which case the algorithm itself will free it.
 *
 *  @retval     int32_t
 *
 *  @remarks    This function frees internal memory popuated at the address from .base field of the memRec.
 *              If the requested memory space is BAM_MEMSPACE_EXTMEM which is not an internal memory space and hence will be not be freed.
 *
 *  @remarks    MemRecs with NULL .base field will be exempted from freeing.
 *              
 */
int32_t IBAMALG_freeMemRecsInt(IBAMALG_MemRec memRec[], uint32_t numMemRecs, uint32_t freeDMEM);

/**
 *  @brief      A Sample or a typical create function for an algorithm. This functions basically gets all the memory requirements of the
 *              algorithm and allocates them as requested. Internally it calls 
 *              1. algNumAlloc()
 *              2. algAlloc() and
 *              3. algAllocMem() of the algorithm and allocates memory requirements as per the algorithm requests.
 *
 *  @param[in]  fxns            Pointer to algorithm IBAMALG_Fxns structure.
 *  @param[out] handle          Pointer to the algorithm main handle.
 *  @param[in]  params          Pointer to the create time parameter structure of the algorithm.
 *  @param[in]  memAllocator    Pointer to OSAL memory utility descriptor.
 *
 *  @retval     int32_t
 *
 *  @remarks    All the internal memory requirements of the algorithm are freed internally prior to the exit of this function so that those
 *              internal memory spaces can be reused by a different algorithm. Algorithm must make sure that all the persistant data residing in the
 *              internal memories are saved using context save/restore mechanism.
 *
 *  @remarks    Algorithms can always use their own create() functions if this function does not meet their requirements.
 */
int32_t IBAMALG_create(const IBAMALG_Fxns *fxns, IBAMALG_Handle *handle, const IBAMALG_Params *params,
                       const ALGOSAL_MemAllocator *memAllocator);

/**
 *  @brief      A Sample or a typical delete function for an algorithm. This functions basically gets all the memory requirements of the
 *              algorithm and frees them. Internally it calls algFree() of the algorithm and frees the memories reported by it.
 *
 *  @param[in]  handle          Pointer to the algorithm main handle.
 *  @param[in]  memAllocator    Pointer to OSAL memory utility descriptor.
 *
 *  @retval     int32_t
 *
 *  @remarks    None of the internal memory requirements of the algorithm are freed since it assumes all internal memories are freed at the algCreate() itself.
 *
 *  @remarks    Algorithms can always use their own delete() functions if this function does not meet their requirements.
 */
int32_t IBAMALG_delete(const IBAMALG_Handle handle, const ALGOSAL_MemAllocator *memAllocator);

/**
 *  @brief      API for saving a memRec for the purpose of context save. This function basically copies the contents pointed
                by the .base field of the memRec to the memory pointed by .ext field. It refers to .size field for the amount of data to be copied.
                memRecs with attributes BAM_MEMATTRS_CONST & BAM_MEMATTRS_SCRATCH will not be saved.
 *
 *  @param[in]  memRec          Pointer to the memRec to be saved.
 *
 *  @retval     int32_t
 *
 *  @remarks    This function internally uses QDMA for data transfer. Please refer to the QDMA interface for any possible QDMA resource conflict.
 */
int32_t IBAMALG_contextSaveMemRec(BAM_MemRec *memRec);

/**
 *  @brief      API for restoring a memRec for the purpose of context restore. This function basically copies the contents pointed
                by the .ext field of the memRec to the memory pointed by .base field. It refers to .size field for the amount of data to be copied.
                All memRecs except those with attribute BAM_MEMATTRS_SCRATCH will not be restored.
 *
 *  @param[in]  memRec          Pointer to the memRec to be saved.
 *
 *  @retval     int32_t
 *
 *  @remarks    This function internally uses QDMA for data transfer. Please refer to the QDMA interface for any possible QDMA resource conflict.
 */
int32_t IBAMALG_contextRestoreMemRec(BAM_MemRec *memRec);

#endif

