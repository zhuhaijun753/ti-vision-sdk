/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      edma3_lld_helper.c                                                       */
/*                                                                          */
/*  DESCRIPTION:                                                            */
/*  This file helper function to create  edma3 lld handle                  */
/*                                                                          */
/*==========================================================================*/
#include "edma3_lld_helper.h"

#include "edmacc_config.h"
#include "edma_baseaddr.h"


EDMA3_RM_Handle  EDMA3_LLD_HELPER_init(
                        unsigned int                  edma3Id,
                        EDMA3_RM_GblConfigParams    * rmConfigParams,
                        EDMA3_RM_InstanceInitConfig * rmInstanceInitConfig,
                        EDMA3_RM_Result             * errorCode)
{
  EDMA3_RM_Handle hEdmaResMgr = NULL;
#if (!HOST_EMULATION)
  EDMA3_RM_Param initParam;
  EDMA3_RM_Result edma3Result = EDMA3_RM_SOK;
  EDMA3_RM_MiscParam miscParam;
  EDMA3_RM_GblConfigParams globalConfig;
  EDMA3_RM_InstanceInitConfig instanceConfig;
  int i;
  unsigned int qdmaChannelToReserve;
  unsigned int tccToReserve;
  unsigned int paramSetToReserve;


  if ( rmConfigParams == NULL )
  {
    globalConfig.numDmaChannels          = NUM_EDMA_CHANNELS;
    globalConfig.numEvtQueue             = NUM_EEVTS;
    globalConfig.numPaRAMSets            = EDMA_NUM_PARAMS;
    globalConfig.numQdmaChannels         = NUM_QDMA_CHANNELS;
    globalConfig.numTccs                 = EDMA_NUM_TCCS;
    globalConfig.numRegions              = 1;
    globalConfig.globalRegs              = ((void *)(CSL_EDMACC_0_REGS));
    globalConfig.tcRegs[0]               = ((void *)(CSL_EDMA3_TC0_BASE_ADDR));
    globalConfig.tcRegs[1]               = ((void *)(CSL_EDMA3_TC1_BASE_ADDR));

    globalConfig.ccError                 = 23;
    for ( i = 0 ; i < globalConfig.numDmaChannels ; i++)
    {
      globalConfig.dmaChannelPaRAMMap[i] = EDMA3_RM_CH_NO_PARAM_MAP;
    }

    for ( i = 0 ; i < globalConfig.numDmaChannels ; i++)
    {
      globalConfig.dmaChannelTccMap[i] = EDMA3_RM_CH_NO_TCC_MAP;
    }
    globalConfig.dmaChannelHwEvtMap[0]   = (0x0u);
    globalConfig.dmaChannelHwEvtMap[1]   = (0x0u);

    globalConfig.dmaChPaRAMMapExists     = 1;
    globalConfig.evtQPri[0]              = 0;
    globalConfig.evtQPri[1]              = 1;
    globalConfig.evtQueueWaterMarkLvl[0] = 16;
    globalConfig.evtQueueWaterMarkLvl[1] = 16;

    globalConfig.memProtectionExists     = 0;
    globalConfig.numTcs                  = 2;
    globalConfig.tcDefaultBurstSize[0]   = 16;
    globalConfig.tcDefaultBurstSize[1]   = 16;
    globalConfig.tcError[0]              = 25;
    globalConfig.tcError[1]              = 25;
    globalConfig.xferCompleteInt         = 8;

    rmConfigParams = &globalConfig;
  }

/* Configure it as master, if required */

  edma3Result = EDMA3_RM_create (edma3Id, rmConfigParams ,
                  (void *)&miscParam);

  if ( edma3Result == EDMA3_DRV_SOK )
  {
    if ( rmInstanceInitConfig == NULL )
    {
      for ( i = 0 ; i < 16; i++ )
      {
        instanceConfig.ownPaRAMSets[i] = 0xFFFFFFFFU;
      }
      for ( i = 0 ; i < 2; i++ )
      {
        instanceConfig.ownDmaChannels[i] = 0xFFFFFFFFU;
      }
      for ( i = 0 ; i < 2; i++ )
      {
        instanceConfig.ownTccs[i] = 0xFFFFFFFFU;
      }
      for ( i = 0 ; i < 1; i++ )
      {
        instanceConfig.ownQdmaChannels[i] = 0x000000FFU;
      }

      for ( i = 0 ; i < 16; i++ )
      {
        instanceConfig.resvdPaRAMSets[i] = 0x0U;
      }

      for ( i = 0 ; i < 2; i++ )
      {
        instanceConfig.resvdDmaChannels[i] = 0x0U;
      }

      for ( i = 0 ; i < 2; i++ )
      {
        instanceConfig.resvdTccs[i] =0x0U;
      }

      for ( i = 0 ; i < 1 ; i++ )
      {
        instanceConfig.resvdQdmaChannels[i] = 0x0U;
      }

      qdmaChannelToReserve = rmConfigParams->numQdmaChannels - 1U;
      instanceConfig.resvdQdmaChannels[0] ^= ( 1U << qdmaChannelToReserve);
      tccToReserve     = rmConfigParams->numTccs - 1U;
      instanceConfig.resvdTccs[ tccToReserve / 32] ^= ( 1U << tccToReserve);
      paramSetToReserve = rmConfigParams->numPaRAMSets - 1U;
      instanceConfig.resvdPaRAMSets[ paramSetToReserve / 32] ^= ( 1U << paramSetToReserve);

      rmInstanceInitConfig = &instanceConfig;

    }

    initParam.isMaster = TRUE;
    /* Choose shadow region according to the DSP# */
    initParam.regionId = (EDMA3_RM_RegionId)0;
    /*Saving the regionId for using it in the sample_cs.c file */

    /* Driver instance specific config NULL */
    initParam.rmInstInitConfig = rmInstanceInitConfig;

    initParam.regionInitEnable = TRUE;
    initParam.gblerrCbParams.gblerrCb = (EDMA3_RM_GblErrCallback)NULL;
    initParam.gblerrCbParams.gblerrData = (void *)NULL;
    initParam.rmSemHandle = &edma3Result ; //:TODO:
    /* Open the Driver Instance */
    hEdmaResMgr = EDMA3_RM_open (edma3Id, (EDMA3_RM_Param *)&initParam,
                    &edma3Result);

  }


  *errorCode = edma3Result;
#endif

  return hEdmaResMgr;
}


/**
 * \brief   EDMA3 De-initialization
 *
 * This function removes the EDMA3 RM Instance and unregisters the
 * interrupt handlers. It also deletes the RM  Object.
 *
  * \return  EDMA3_RM_SOK if success, else error code
 */

EDMA3_RM_Result EDMA3_LLD_HELPER_deinit (unsigned int edma3Id, EDMA3_RM_Handle hEdmaResMgr)
{
  EDMA3_RM_Result edma3Result = EDMA3_RM_SOK;
#if (!HOST_EMULATION)
  /* Now, close the EDMA3 RM Instance */
  edma3Result = EDMA3_RM_close (hEdmaResMgr, NULL);

  if (EDMA3_RM_SOK == edma3Result)
  {
  /* Now, delete the EDMA3 RM Object */
  edma3Result = EDMA3_RM_delete (edma3Id, NULL);
  }
#endif
  return edma3Result;
}

/**
 * \brief   EDMA3 OS Semaphore Take
 *
 *      This function takes a semaphore token if available.
 *      If a semaphore is unavailable, it blocks currently
 *      running thread in wait (for specified duration) for
 *      a free semaphore.
 * \param   hSem [IN] is the handle of the specified semaphore
 * \param   mSecTimeout [IN] is wait time in milliseconds
 * \return  EDMA3_DRV_Result if successful else a suitable error code
 */
EDMA3_DRV_Result edma3OsSemTake(EDMA3_OS_Sem_Handle hSem, int32_t mSecTimeout)
{
    EDMA3_DRV_Result semTakeResult = EDMA3_DRV_SOK;


    return semTakeResult;
}


/**
 * \brief   EDMA3 OS Semaphore Give
 *
 *      This function gives or relinquishes an already
 *      acquired semaphore token
 * \param   hSem [IN] is the handle of the specified semaphore
 * \return  EDMA3_DRV_Result if successful else a suitable error code
 */
EDMA3_DRV_Result edma3OsSemGive(EDMA3_OS_Sem_Handle hSem)
{
    EDMA3_DRV_Result semGiveResult = EDMA3_DRV_SOK;



    return semGiveResult;
}

void edma3OsProtectEntry (uint32_t edma3InstanceId,
                      int32_t level,
                      uint32_t *intState)
{
  return;
}

void edma3OsProtectExit (uint32_t edma3InstanceId,
                    int32_t level,
                    uint32_t intState)
{
  return;
}


