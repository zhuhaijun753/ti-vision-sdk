/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#ifndef __ALGOSAL_EXTMEM_H__
#define __ALGOSAL_EXTMEM_H__


#pragma CHECK_MISRA ("none")
#include <stdint.h>

#if (!VCOP_HOST_EMULATION)
#include "arp32.h"
#include "vcopmem.h"
#endif


#pragma RESET_MISRA ("required")

#include "alg_osal.h"

/*
 Functions used for external memory allocation
*/
void    ALGOSAL_extMemInit(void);
void   *ALGOSAL_extMemAlloc(int32_t size);
void    ALGOSAL_extMemFree(void *userptr);
int32_t ALGOSAL_extMemMax(void);



#endif /* __ALGOSAL_EXTMEM_H__ */
