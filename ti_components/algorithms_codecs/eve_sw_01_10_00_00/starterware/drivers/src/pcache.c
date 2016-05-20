/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#include "GlobalTypes.h"
#include "cram.h"

#pragma CHECK_MISRA ("none")
#include "baseaddress.h"
#include "eve_control_cred.h"
#pragma RESET_MISRA ("required")

#include "pcache.h"


void EVE_PROGCACHE_BlockInvalidate
(
    CRED_index_t  component,
    const UWORD32  *address,
    UWORD32  num_bytes
)
{
    UWORD32 value;

    /* Write the address and number of bytes to invaidate the cache */
    WR_REG_32(component, EVE_CONTROL__EVE_PC_IBAR, address);
    WR_REG_32(component, EVE_CONTROL__EVE_PC_IBC,  num_bytes);

    /* Read PC_IBC and ensure that it goes down to 0, to ensure completion*/
    value = RD_REG_32 (component, EVE_CONTROL__EVE_PC_IBC);

    while (value != 0x0)
    {
        value = RD_REG_32 (component, EVE_CONTROL__EVE_PC_IBC);
    }
}

void EVE_PROGCACHE_GlobalInvalidate (CRED_index_t  component)
{
    UWORD32 value;

    /* Write a 0x1 to cause global invalidation of cache */
    WR_REG_32(component, EVE_CONTROL__EVE_PC_INV, 0x1);

    /* Read back and make sure value went to 0x0, to confirm global inv. */
    value = RD_REG_32 (component, EVE_CONTROL__EVE_PC_INV);

    while (value != 0x0)
    {
        value = RD_REG_32 (component, EVE_CONTROL__EVE_PC_INV);
    }
}


void EVE_PROGCACHE_Prefetch (CRED_index_t component, const UWORD32 *addr, UWORD32 sizePrefetch)
{
    UWORD32 value;

    WR_REG_32(component, EVE_CONTROL__EVE_PC_PBAR, addr);
    WR_REG_32(component,  EVE_CONTROL__EVE_PC_PBC,  sizePrefetch);

    value = RD_REG_32 (component, EVE_CONTROL__EVE_PC_PBC);

    while (value != 0x0)
    {
        value = RD_REG_32 (component, EVE_CONTROL__EVE_PC_PBC);
    }
}



