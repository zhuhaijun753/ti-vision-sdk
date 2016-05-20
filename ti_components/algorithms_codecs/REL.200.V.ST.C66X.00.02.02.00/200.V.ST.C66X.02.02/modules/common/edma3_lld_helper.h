/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      edma3_lld_helper.h                                                      */
/*                                                                          */
/*  DESCRIPTION:                                                            */
/*  This file wrapper function to create  edma3 lld handle                   */
/*                                                                          */
/*==========================================================================*/

#ifndef EDMA3_LLD_HELPER_H_
#define EDMA3_LLD_HELPER_H_

#if (!HOST_EMULATION)
#include "edma3_rm.h"
#else
#include "stdint.h"
#include "edma3lld_support.h"
typedef int32_t             EDMA3_RM_GblConfigParams;
typedef int32_t             EDMA3_RM_InstanceInitConfig;

/** EDMA3_RM Result - return value of a function  */
typedef int32_t             EDMA3_RM_Result;

/** EDMA3_DRV Result - return value of a function  */
typedef int32_t             EDMA3_DRV_Result;

/**
 * OS specific Semaphore Handle.
 * Used to acquire/free the semaphore, used for sharing of resources
 * among multiple users.
 */
typedef void    *EDMA3_OS_Sem_Handle;

/** EDMA3 Resource Manager Result OK */
#define EDMA3_RM_SOK             (0)
/** EDMA3 Driver Result OK */
#define EDMA3_DRV_SOK            (0)

/** Define for NULL values*/
#ifndef NULL
  #define NULL 0u
#endif

#endif

EDMA3_RM_Handle  EDMA3_LLD_HELPER_init(
                        unsigned int                  edma3Id,
                        EDMA3_RM_GblConfigParams    * rmConfigParams,
                        EDMA3_RM_InstanceInitConfig * rmInstanceInitConfig,
                        EDMA3_RM_Result             * errorCode);

EDMA3_RM_Result EDMA3_LLD_HELPER_deinit (unsigned int edma3Id, EDMA3_RM_Handle hEdmaResMgr);


/**
 * \brief   EDMA3 OS Semaphore Give
 *
 *      This function gives or relinquishes an already
 *      acquired semaphore token
 * \param   hSem [IN] is the handle of the specified semaphore
 * \return  EDMA3_DRV_Result if successful else a suitable error code
 */
EDMA3_DRV_Result edma3OsSemTake(EDMA3_OS_Sem_Handle hSem, int32_t mSecTimeout);


/**
 * \brief   EDMA3 OS Semaphore Give
 *
 *      This function gives or relinquishes an already
 *      acquired semaphore token
 * \param   hSem [IN] is the handle of the specified semaphore
 * \return  EDMA3_DRV_Result if successful else a suitable error code
 */
EDMA3_DRV_Result edma3OsSemGive(EDMA3_OS_Sem_Handle hSem);


void edma3OsProtectEntry (uint32_t edma3InstanceId,
                      int32_t level,
                      uint32_t *intState);

void edma3OsProtectExit (uint32_t edma3InstanceId,
                    int32_t level,
                    uint32_t intState);

#endif /* EDMA3_LLD_HELPER_H_ */
