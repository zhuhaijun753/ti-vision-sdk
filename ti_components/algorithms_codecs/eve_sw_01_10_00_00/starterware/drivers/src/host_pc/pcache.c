/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#include "GlobalTypes.h"
#include "baseaddress.h"
#include "pcache.h"


void EVE_PROGCACHE_BlockInvalidate
(
    CRED_index_t  component,
    UWORD32  *address,
    UWORD32  num_bytes
)
{
	return;
}

void EVE_PROGCACHE_GlobalInvalidate (CRED_index_t  component)
{
    return;
}


void EVE_PROGCACHE_Prefetch (CRED_index_t component, UWORD32 *addr, UWORD32 sizePrefetch)
{
    return;
}



