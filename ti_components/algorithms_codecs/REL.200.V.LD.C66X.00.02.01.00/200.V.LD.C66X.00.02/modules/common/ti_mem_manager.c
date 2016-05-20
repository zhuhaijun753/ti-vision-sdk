/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*!
 *****************************************************************************
 * @file      ti_mem_manager.c
 * @brief     Implementation of the Memory Manager for internal memories in TI
              devices which needs to be handled by DSP software
  * @version   0.0 - Sep 2008 : initial version
*****************************************************************************
 */

#include <ti_mem_manager.h>

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <assert.h>
#pragma RESET_MISRA ("required")

#define _GUARD_SIZE_      0x00
#define _PAYLOAD_VAL_     0xBB
#define _GUARD_VAL_       0xAA

/*!
  @func   TI_CreateMemoryHandle
  @brief  This function makes a memory handle live
  @param  memhandle [IN]:  Memory Handle
  @param  baseAddr [IN]: Base address of the memory object
  @param  size [IN]:  Size of the total memory being assigned to this
                      memory handle
  @return none
*/
void TI_CreateMemoryHandle(TIMemHandle memhandle,
  unsigned char *baseAddr, unsigned int size)
{
  memhandle->ptrBase          = baseAddr;
  memhandle->u32Totalsize     = size;
  memhandle->u32AvailableSize = size;
  memhandle->ptrCurr          = baseAddr;
  return  ;
}

/*!
  @func   TI_ResetMemoryHandle
  @brief  This function makes reset an existing memory object to its initial state, effectively removing all the previously allcoated memory chunks
  @param  memhandle [IN]:  Memory Handle
  @return none
*/
void TI_ResetMemoryHandle(TIMemHandle memhandle)
{
  memhandle->u32AvailableSize = memhandle->u32Totalsize;
  memhandle->ptrCurr          = memhandle->ptrBase;
  return  ;
}

/*!
  @func   TI_GetMemoryChunk
  @brief  This function provides the requested memory to user
  @param  memhandle [IN]:  Memory Handle
  @param  size [IN]: Requested size of the memory
  @param  alignment[IN]:  alignment of required memory
  @return pointer to the memory
*/
unsigned char* TI_GetMemoryChunk(TIMemHandle memhandle,
  unsigned int size, unsigned int alignment)
{
  unsigned char *mem ;
  unsigned int alignmentBytes  =
    ((((unsigned int)memhandle->ptrCurr + _GUARD_SIZE_) + alignment - 1) & (~(alignment - 1))) -
      ((unsigned int)memhandle->ptrCurr + _GUARD_SIZE_);

  assert(alignment > 0) ;
  if( memhandle->u32AvailableSize < (alignmentBytes + size))
  {
    /* ----------------------------------------------------*/
    /* This scenario arrives if remaining space in SL2     */
    /* is not sufficient for the requested chunk of memory */
    /* Control never hits below  instruction at run-time   */
    /* This while(1) is kept here to catch the SL2 memory  */
    /* insufficiency during development phase              */
    /* ----------------------------------------------------*/

    while(1){
        ;
    }
  }
  else
  {
    memhandle->u32AvailableSize -= (alignmentBytes   + (size + 2*_GUARD_SIZE_));
    mem                 = (memhandle->ptrCurr + (alignmentBytes + _GUARD_SIZE_));
    memhandle->ptrCurr += (alignmentBytes     + (size + 2*_GUARD_SIZE_)       ) ;

    MEMSET(mem, _PAYLOAD_VAL_, size);
    MEMSET(mem - _GUARD_SIZE_ , _GUARD_VAL_  , _GUARD_SIZE_) ;
    MEMSET(mem + size         , _GUARD_VAL_  , _GUARD_SIZE_) ;
  }
  return mem ;
}
