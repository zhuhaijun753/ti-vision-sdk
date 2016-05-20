/******************************************************************************
 *                                                                            *
 * Copyright (c) 2012 Texas Instruments Incorporated - http://www.ti.com/     *
 *                                                                            *
 * All rights reserved. Property of Texas Instruments Incorporated.           *
 * Restricted rights to use, duplicate or disclose this code are              *
 * granted through contract.                                                  *
 *                                                                            *
 * The program may not be used without the written permission                 *
 * of Texas Instruments Incorporated or against the terms and conditions      *
 * stipulated in the agreement under which this program has been              *
 * supplied.                                                                  *
 *                                                                            *
 *****************************************************************************/

/**
 *  \file bsp_utils.c
 *
 *  \brief Utility functions implementation file.
 *  This file defines the helper functions like create, add and remove nodes
 *
 */

/* Minimal os-independent Utils layer */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdio.h>

#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include <common/bsp_types.h>
#include <osal/bsp_osal.h>
#include <common/trace.h>
#include <common/stw_config.h>
#include <common/bsp_utils.h>

#include <string.h>
#include <stdlib.h>

/**
 *  BspUtils_memset
 *  \brief Sets the memory with the given value. Access memory as byte.
 *  Returns the memory pointer.
 *
 *  \param mem              Destination memory pointer
 *  \param ch               Byte value to fill with
 *  \param byteCount        Number of bytes to fill
 *
 *  \return                 The destination memory pointer
 */
void *BspUtils_memset(Ptr mem, UInt8 ch, UInt32 byteCount)
{
    /* NULL pointer check */
    GT_assert(StwUtilsTrace, (NULL != mem));

    return memset(mem, (Int32) ch, byteCount);
}

/**
 *  BspUtils_memsetw
 *  \brief Sets the memory with the given value. Access memory as word.
 *  Hence memory pointer should be aligned to 4 byte boundary
 *  Returns the memory pointer.
 *
 *  \param mem              Destination memory pointer
 *  \param word             Word value to fill with
 *  \param wordCount        Number of words to fill
 *
 *  \return                 The destination memory pointer
 */
void *BspUtils_memsetw(Ptr mem, UInt32 word, UInt32 wordCount)
{
    UInt32  count;
    UInt32 *memPtr = NULL;

    /* NULL pointer check */
    GT_assert(StwUtilsTrace, (NULL != mem));

    memPtr = (UInt32 *) mem;
    for (count = 0; count < wordCount; count++)
    {
        memPtr[count] = word;
    }

    return (mem);
}

/**
 *  BspUtils_memcpy
 *  \brief Copies source memory into destination memory. Access memory as byte.
 *  Returns the destination memory pointer.
 *
 *  \param dest             Destination memory pointer
 *  \param src              Source memory pointer
 *  \param byteCount        Number of bytes to copy
 *
 *  \return                 The destination memory pointer
 */
void *BspUtils_memcpy(Ptr dest, const void *src, UInt32 byteCount)
{
    /* NULL pointer check */
    GT_assert(StwUtilsTrace, (NULL != dest));
    GT_assert(StwUtilsTrace, (NULL != src));

    return memcpy(dest, src, byteCount);
}

/**
 *  BspUtils_memcmp
 *  \brief Compare memory block 1 with memory block 2. Access memory as byte.
 *  Returns 0 if two memories are  identical.
 *
 *  \param mem1             memory block 1
 *  \param mem2              memory block 2
 *  \param byteCount        Number of bytes to compare
 *
 *  \return                 0 if two memory are identical other return 1
 */
Int32 BspUtils_memcmp(const void *mem1, const void *mem2, UInt32 byteCount)
{
    /* NULL pointer check */
    GT_assert(StwUtilsTrace, (NULL != mem1));
    GT_assert(StwUtilsTrace, (NULL != mem2));

    return memcmp(mem1, mem2, byteCount);
}

