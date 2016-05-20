/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/**
*  @file       pcache.h
*
*  @brief      The program cache library component offers basic interface apis
*              to the cache
*
*  This header provides basic apis to invalidate or prefetch program cache
*
*/
#ifndef PCACHE_H
#define PCACHE_H

#include "GlobalTypes.h"

#ifdef __cplusplus
extern  "C"
{
#endif

/* ------------------------------------------------------------------------*//**
 * @brief          EVE_PROGCACHE_BlockInvalidate
 *
 * @brief       Invalidate the block of data in program cache
 *
 * @brief   CRED_index_t - cred module Identifier
 * @brief   UWORD32 * - address
 * @brief   UWORD32   - size
 *
 * @return      Void
 *
 * @details     Invalidates the block as specified by address and size
 *              in program cache
 *
 * @remarks      -
 *
 *//*------------------------------------------------------------------------ */
void EVE_PROGCACHE_BlockInvalidate (CRED_index_t component, const UWORD32 *address, UWORD32 num_bytes);
/* ------------------------------------------------------------------------*//**
 * @brief          EVE_PROGCACHE_GlobalInvalidate
 *
 * @brief       Invalidate the program cache globally
 *
 * @brief   CRED_index_t - cred module Identifier
 *
 * @return      Void
 *
 * @details     Invalidates the program cache globally
 *
 * @remarks      -
 *
 *//*------------------------------------------------------------------------ */
void EVE_PROGCACHE_GlobalInvalidate(CRED_index_t component);
/* ------------------------------------------------------------------------*//**
 * @brief          EVE_PROGCACHE_Prefetch
 *
 * @brief       Prefetch the block of data into program cache
 *
 * @brief   CRED_index_t - cred module Identifier
 * @brief   UWORD32 * - address
 * @brief   UWORD32   - size
 *
 * @return      Void
 *
 * @details     Prefetch the block as specified by address and size in
 *              to program cache
 *
 * @remarks      -
 *
 *//*------------------------------------------------------------------------ */
void EVE_PROGCACHE_Prefetch (CRED_index_t component, const UWORD32 *addr, UWORD32 sizePrefetch);

#ifdef __cplusplus
}
#endif
#endif	/* PCACHE_H */
/* EOF */




