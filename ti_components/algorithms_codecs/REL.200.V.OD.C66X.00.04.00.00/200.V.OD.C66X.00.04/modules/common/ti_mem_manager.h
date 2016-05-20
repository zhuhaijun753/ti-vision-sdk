/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*!
 *****************************************************************************
 * @file      ti_mem_manager.h
 * @brief     Implementation of the Memory Manager for internal memories in
              TI devices which needs to be handled by EVE software.
              User can create a object of memory with given base address and
              total size. Later user can get different memory chunks by
              requesting to memory manager
 * @version   0.0 - Sep 2008 : initial version
 *****************************************************************************
 */

#ifndef _TI_MEMMANAGER_H_
#define _TI_MEMMANAGER_H_

/* #define _FILLMEM_ */

#ifdef _FILLMEM_
#define MEMSET(a,b,c) memset(a,b,c)
#else
#define MEMSET(a,b,c)
#endif /* _FILLMEM_ */

/*!
  @struct sMemory_t
  @brief  This structure is memory object structure,
  @param  ptrBase : Base of the memory Object
  @param  ptrCurr : start point of the free memory in pool
          it is a private member of memory object
  @param  u32Totalsize : Total size of the memory object
          it is a private member of memory object
  @param  u32AvailableSize : Total free size of the memory
          it is a private member of memory object

*/
typedef struct _memory
{
  unsigned char *ptrBase;
  unsigned char *ptrCurr;
  unsigned int  u32Totalsize;
  unsigned int  u32AvailableSize;

} sMemory_t ;

typedef sMemory_t  TIMemObject;   /* !< Memory object */
typedef sMemory_t* TIMemHandle;   /* !< Handle of the memory object */

/*!
  @func   TI_CreateMemoryHandle
  @brief  This function makes a memory handle live
  @param  memhandle [IN]:  Memory Handle
  @param  baseAddr [IN]: Base address of the memory object
  @param  size [IN]:  Size of the total memory being assigned to this
                      memory handle
  @return none
*/
void TI_CreateMemoryHandle(
   TIMemHandle memhandle,
   unsigned char *baseAddr,
   unsigned int size) ;

/*!
  @func   TI_ResetMemoryHandle
  @brief  This function makes reset an existing memory object to its initial state, effectively removing all the previously allcoated memory chunks
  @param  memhandle [IN]:  Memory Handle
  @return none
*/
void TI_ResetMemoryHandle(TIMemHandle memhandle);

/*!
  @func   TI_GetMemoryChunk
  @brief  This function provides the requested memory to user
  @param  memhandle [IN]:  Memory Handle
  @param  size [IN]: Requested size of the memory
  @param  alignment[IN]:  alignment of required memory
  @return pointer to the memory
*/
unsigned char* TI_GetMemoryChunk(
    TIMemHandle memhandle,
    unsigned int size,
    unsigned int alignment) ;

#endif /* _TI_MEMMANAGER_H */