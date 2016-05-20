/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 *   \file  ndk2nsp.c
 *
 *   \brief
 *          Translation layer to go from NDK to NSP hardware driver.
 *
 */


/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

/* OS/Posix headers */
#include <ti/sysbios/utils/Load.h>
#include <ti/sysbios/hal/Cache.h>

/* NDK Dependencies */
#include <ti/ndk/inc/stkmain.h>

/* NSP GMACSW driver dependency headers */
#include "gmacsw.h"
#include "gmacsw_al.h"
#include "gmacsw_config.h"
#if defined(NSP_INSTRUMENTATION_ENABLED)
#include "private/timer_.h"
#endif
#include "private/debug_.h"

/* This module's header */
#include "ndk2nsp.h"


/*---------------------------------------------------------------------------*\
|                             Extern Declarations                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                            Local Macros/Defines                             |
\*---------------------------------------------------------------------------*/



#define BUFF_DESC_PER_PACKET        ((uint32_t)1U)

#define NDK_RX_PACKET_TASK_PRI      (OS_TASKPRIHIGH)
#define NDK_RX_PACKET_TASK_STACK    (2048)

#define NDK_TX_PACKET_TASK_PRI      (OS_TASKPRIHIGH)
#define NDK_TX_PACKET_TASK_STACK    (2048)


/*---------------------------------------------------------------------------*\
|                            Local Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Local Function Declarations                         |
\*---------------------------------------------------------------------------*/

static void     LOCAL_closeRxChannel(void *hCallbackArg);
static void     LOCAL_notifyRxPackets(void *hCallbackArg);
static void     LOCAL_rxPacketTask(void *arg0);
static void     LOCAL_allocRxPackets(NDK2NSP_Handle hNDK2NSP);
static uint32_t LOCAL_prepRxPacketQueue(NDK2NSP_Handle hNDK2NSP, CPDMA_PacketQueue *pPacketQueue);

static void     LOCAL_closeTxChannel(void *hCallbackArg);
static void     LOCAL_notifyTxPackets(void *hCallbackArg);
static void     LOCAL_txPacketTask(void *arg0);
static void     LOCAL_allocTxPackets(NDK2NSP_Handle hNDK2NSP);
static uint32_t LOCAL_prepTxPacketQueue(NDK2NSP_Handle hNDK2NSP, CPDMA_PacketQueue *pPacketQueue);

static void     LOCAL_pollingCallback(void *hCallbackArg);


/*---------------------------------------------------------------------------*\
|                         Local Variable Declarations                         |
\*---------------------------------------------------------------------------*/

#if !defined(NSP_DYNAMIC_ALLOCATION)
static NDK2NSP_Object NDK2NSP_object;
#endif


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/

NDK2NSP_Stats ndk2NspStats;


/*---------------------------------------------------------------------------*\
|                          Global Function Definitions                        |
\*---------------------------------------------------------------------------*/

/*!
 *  @b NDK2NSP_open
 *  @n
 *      Opens and configures GMACSW. Configures Interrupts, SGMII,
 *      and send and receive queues.
 *
 *  \param[in]  hNDK2NSP
 *      NDK2NSP_object structure pointer.
 *
 *  \retval
 *      Success -  0
 *  \retval
 *      Error   -  Any non-zero value
 */
NDK2NSP_Handle NDK2NSP_open(STKEVENT_Handle hEvent)
{
    uint32_t i;
    NDK2NSP_Handle  hNDK2NSP;
    GMACSW_Config   *pGMACSWConfig;

#if defined(NSP_DYNAMIC_ALLOCATION)
    hNDK2NSP = (NDK2NSP_Handle ) mmAlloc(sizeof(NDK2NSP_object));
    if (hNDK2NSP == NULL)
    {
        dprint("ERROR: Unable to allocate packet device object!\n");
        return NULL;
    }
#else
    hNDK2NSP = &NDK2NSP_object;
#endif

    /* Clear instrumentation statistics structure */
    memset(&ndk2NspStats, 0, sizeof(NDK2NSP_Stats));

    /* Initialize the allocated memory block. */
    memset(hNDK2NSP, 0, sizeof(NDK2NSP_object));

    /* Initialize the Rx Queues & Data */
    PBMQ_init(&hNDK2NSP->rxReadyPBMPacketQueue);
    PBMQ_init(&hNDK2NSP->rxFreePBMPacketQueue);

    /* Initialize the Tx Queues & Data */
    PBMQ_init(&hNDK2NSP->txReadyPBMPacketQueue);
    CPDMA_packetQueueInit(&hNDK2NSP->txFreeCPDMAPacketQueue);

    /* Keep stack event handle to use to signal the NDK stack */
    hNDK2NSP->hEvent = hEvent;

    /* MCast List is EMPTY */
    hNDK2NSP->MCastCnt = 0;

    /* Init internal bookkeeping fields */
    hNDK2NSP->OldMCastCnt = 0;

    /* Get application provided driver configuration */
    pGMACSWConfig = GMACSW_getConfig();

    /* If configuration structure is invalid, get the driver default */
    if (NULL == pGMACSWConfig)
    {
        pGMACSWConfig = GMACSW_CONFIG_getDefaultConfig();
    }

    /* Open the hardware driver using the obtained configuration */
    hNDK2NSP->hGMACSW = GMACSW_open(pGMACSWConfig);
    if (NULL == hNDK2NSP->hGMACSW)
    {
        dprint("GMACSW_open() Returned error \n");

#if defined(NSP_DYNAMIC_ALLOCATION)
        mmFree(hNDK2NSP);
#endif
        return NULL;
    }

    /* Copy the MAC address(es) into the translation layer structure */
    for (i = 0; i < pGMACSWConfig->activeMACPortCount; i++)
    {
        memcpy( (void *)&(hNDK2NSP->bMacAddr[i][0]), (void *)&(pGMACSWConfig->macInitCfg[i].macAddr[0]), (size_t)6U);
    }

    /* Get initial link/interface status from the driver */
    GMACSW_getLinkStatus(hNDK2NSP->hGMACSW, &hNDK2NSP->linkIsUp, &hNDK2NSP->currLinkedInterface);

    hNDK2NSP->PktMTU = pGMACSWConfig->PktMTU;

    hNDK2NSP->inDLBMode = pGMACSWConfig->dlbMode;

    /* Open Rx Channel */
    {
        CPDMA_OpenRxChannelIoctlCmd cmd;
        CPDMA_RxChannelConfig       config;

        cmd.pRxChannelConfig                    = &config;
        cmd.pRxChannelHandle                    = &hNDK2NSP->hRxChannel;

        config.packetCount                      = NDK2NSP_RX_PACKETS;
        config.buffersPerPacketCount            = BUFF_DESC_PER_PACKET;
        config.packetMem                        = (void *) hNDK2NSP->rxPacketMem;
        config.rxThreshCount                    = (NDK2NSP_RX_PACKETS * BUFF_DESC_PER_PACKET) / 4U; /* Set threshold at 25% of total */
        config.callbacks.pFxnCbCloseChannel     = &LOCAL_closeRxChannel;
        config.callbacks.pFxnCbUsedPacketNotify = &LOCAL_notifyRxPackets;
        config.callbacks.hCallbackArg           = (void *) hNDK2NSP;

        GMACSW_ioctl(hNDK2NSP->hGMACSW,
                     GMACSW_IOCTL_CPDMA_OPEN_RX_CHANNEL,
                     (void *)&cmd,
                     sizeof(CPDMA_OpenRxChannelIoctlCmd));
        assert(NULL != hNDK2NSP->hRxChannel);
    }

    /* Config Rx Channel for best effort traffic */
    {
        PORT_AddRxPriorityMappingIoctlCmd   cmd;
        PORT_RxPriorityConfig               config;

        cmd.pPriConfig              = &config;
        cmd.pRxPriorityMapHandle    = &hNDK2NSP->hRxPriorityMap;

        config.hCpdmaRxChannel  = hNDK2NSP->hRxChannel;
        config.switchPriority   = PORT_SWITCH_PRIORITY_NONE;
        config.rxSource         = PORT_RX_SOURCE_MAC_BOTH;
        config.rxPriorityType   = PORT_RX_PRIORITY_TYPE_ALL_UNTAGGED;
        config.rxPriorityOption.untagged.priority  = 0;

        GMACSW_ioctl(hNDK2NSP->hGMACSW,
                     GMACSW_IOCTL_PORT_ADD_RX_PRIORITY_MAPPING,
                     (void *)&cmd,
                     sizeof(PORT_AddRxPriorityMappingIoctlCmd));
        assert(NULL != hNDK2NSP->hRxPriorityMap);
    }

    /* Open Tx Channel */
    {
        CPDMA_OpenTxChannelIoctlCmd cmd;
        CPDMA_TxChannelConfig       config;

        cmd.pTxChannelConfig                    = &config;
        cmd.pTxChannelHandle                    = &hNDK2NSP->hTxChannel;

        config.packetCount                      = NDK2NSP_TX_PACKETS;
        config.buffersPerPacketCount            = BUFF_DESC_PER_PACKET;
        config.packetMem                        = (void *) hNDK2NSP->txPacketMem;
        config.callbacks.pFxnCbCloseChannel     = &LOCAL_closeTxChannel;
        config.callbacks.pFxnCbUsedPacketNotify = &LOCAL_notifyTxPackets;
        config.callbacks.hCallbackArg           = (void *) hNDK2NSP;

        GMACSW_ioctl(hNDK2NSP->hGMACSW,
                     GMACSW_IOCTL_CPDMA_OPEN_TX_CHANNEL,
                     (void *)&cmd,
                     sizeof(CPDMA_OpenTxChannelIoctlCmd));
        assert(NULL != hNDK2NSP->hTxChannel);
    }

    /* Register a local function for 100ms-period callback */
    {
        GMACSW_TickFxnIoctlCmd cmd;

        cmd.pTickFxnCallback    = &LOCAL_pollingCallback;
        cmd.hTickFxnCallbackArg = (void *) hNDK2NSP;
        cmd.hRegisteredTickFxn  = &hNDK2NSP->hRegisteredTickFxn;

        GMACSW_ioctl(hNDK2NSP->hGMACSW,
                     GMACSW_IOCTL_REGISTER_TICK_FXN,
                     (void *)&cmd,
                     sizeof(GMACSW_TickFxnIoctlCmd));
        assert(NULL != hNDK2NSP->hRegisteredTickFxn);
    }

    /* Allocate/fill the PBM/CPDMA packets for the Rx channel */
    LOCAL_allocRxPackets(hNDK2NSP);

    /* Allocate/fill the CPDMA packets for the Tx channel */
    LOCAL_allocTxPackets(hNDK2NSP);

    /* Create semaphore objects, init shutDown status */
    hNDK2NSP->shutDown      = 0U;
    hNDK2NSP->shutDownSem   = SemCreate(0);
    hNDK2NSP->rxPacketSem   = SemCreateBinary(0);
    hNDK2NSP->txPacketSem   = SemCreateBinary(0);

    /* Start the packet processing tasks now that the channels are open */
    hNDK2NSP->rxPacketTask  = TaskCreate(&LOCAL_rxPacketTask, "NDK2NSP_RxPacketTask",
                                         (int)NDK_RX_PACKET_TASK_PRI, (uint)NDK_RX_PACKET_TASK_STACK,
                                         (uint32_t) hNDK2NSP, (uint32_t)0, (uint32_t)0 );
    hNDK2NSP->txPacketTask  = TaskCreate(&LOCAL_txPacketTask, "NDK2NSP_TxPacketTask",
                                         (int)NDK_RX_PACKET_TASK_PRI, (uint)NDK_RX_PACKET_TASK_STACK,
                                         (uint32_t) hNDK2NSP, (uint32_t)0, (uint32_t)0 );

    /* Start the Rx Channel */
    GMACSW_ioctl(hNDK2NSP->hGMACSW,
                 GMACSW_IOCTL_CPDMA_START_RX_CHANNEL,
                 (void *)&hNDK2NSP->hRxChannel,
                 sizeof(CPDMA_ChannelHandle));

    /* Start the Tx Channel */
    GMACSW_ioctl(hNDK2NSP->hGMACSW,
                 GMACSW_IOCTL_CPDMA_START_TX_CHANNEL,
                 (void *)&hNDK2NSP->hTxChannel,
                 sizeof(CPDMA_ChannelHandle));

    return hNDK2NSP;
}

/*!
 *  @b NDK2NSP_close
 *  @n
 *      Closes GMACSW and disables interrupts.
 *
 *  \param[in]  hNDK2NSP
 *      NDK2NSP_object structure pointer.
 *
 *  \retval
 *      void
 */
void NDK2NSP_close( NDK2NSP_Handle hNDK2NSP )
{
    uint32_t retVal;

    /* Stop the Tx Channel */
    GMACSW_ioctl(hNDK2NSP->hGMACSW,
                 GMACSW_IOCTL_CPDMA_STOP_TX_CHANNEL,
                 (void *)&hNDK2NSP->hTxChannel,
                 sizeof(CPDMA_ChannelHandle));

    /* Stop the Rx Channel */
    GMACSW_ioctl(hNDK2NSP->hGMACSW,
                 GMACSW_IOCTL_CPDMA_STOP_RX_CHANNEL,
                 (void *)&hNDK2NSP->hRxChannel,
                 sizeof(CPDMA_ChannelHandle));

    /* Set the translation layer shutdown flag */
    hNDK2NSP->shutDown = 1U;

    /* Unregister the 100ms-period callback */
    GMACSW_ioctl(hNDK2NSP->hGMACSW,
                 GMACSW_IOCTL_UNREGISTER_TICK_FXN,
                 (void *)&hNDK2NSP->hRegisteredTickFxn,
                 sizeof(GMACSW_RegisteredTickFxnHandle));

    /* Close the Tx Channel */
    GMACSW_ioctl(hNDK2NSP->hGMACSW,
                 GMACSW_IOCTL_CPDMA_CLOSE_TX_CHANNEL,
                 (void *)&hNDK2NSP->hTxChannel,
                 sizeof(CPDMA_ChannelHandle));
    hNDK2NSP->hTxChannel = NULL;

    /* Remove the best effort Rx priority mapping */
    GMACSW_ioctl( hNDK2NSP->hGMACSW,
                  GMACSW_IOCTL_PORT_REMOVE_RX_PRIORITY_MAPPING,
                  (void *)&hNDK2NSP->hRxPriorityMap,
                  sizeof(PORT_RxPriorityMapHandle));
    hNDK2NSP->hRxPriorityMap = NULL;

    /* Close the Rx Channel */
    GMACSW_ioctl(hNDK2NSP->hGMACSW,
                 GMACSW_IOCTL_CPDMA_CLOSE_RX_CHANNEL,
                 (void *)&hNDK2NSP->hRxChannel,
                 sizeof(CPDMA_ChannelHandle));
    hNDK2NSP->hRxChannel = NULL;

    /* Now close the driver */
    retVal = GMACSW_close(hNDK2NSP->hGMACSW);
    if(retVal != 0)
    {
        dprint1("GMACSW Close Returned error %08x\n",retVal);
    }

    /* Flush out our pending receive queue */
    while (PBMQ_count(&hNDK2NSP->rxReadyPBMPacketQueue) != 0)
    {
        PBM_free( PBMQ_deq(&hNDK2NSP->rxReadyPBMPacketQueue) );
#if defined(NSP_INSTRUMENTATION_ENABLED)
        ndk2NspStats.rxReadyPBMPacketDequeue++;
#endif
    }

    /* Pend on shutDownSem (twice for two sub-tasks) */
    SemPend(hNDK2NSP->shutDownSem, SEM_FOREVER);
    SemPend(hNDK2NSP->shutDownSem, SEM_FOREVER);

    /* Delete the semaphore objects */
    SemDelete(hNDK2NSP->rxPacketSem);
    SemDelete(hNDK2NSP->txPacketSem);
    SemDelete(hNDK2NSP->shutDownSem);

    /*
     * We don't do task deletion since the NDK forces the
     * Task.deleteTerminatedTasks option be true, which means
     * the rxPacketTask and txPacketTask are auto-deleted.
     */

    /* Clear the allocated translation */
    memset(hNDK2NSP, 0, sizeof(NDK2NSP_object));

#if defined(NSP_DYNAMIC_ALLOCATION)
    mmFree(hNDK2NSP);
#endif
}

/*!
 *  @b NDK2NSP_setRx
 *  @n
 *      Sets the filter for GMACSW. Sets up the multicast addresses in
 *      the ALE.
 *
 *  \param[in]  hNDK2NSP
 *      NDK2NSP_object structure pointer.
 *
 *  \retval
 *      void
 */
void NDK2NSP_setRx( NDK2NSP_Handle hNDK2NSP )
{
    uint32_t i;
    uint32_t key = 0;

    key = GMACSW_AL_globalInterruptDisable();

    /* Configure the Receive filter */
    GMACSW_ioctl(hNDK2NSP->hGMACSW,
                 GMACSW_IOCTL_ALE_SET_RX_FILTER,
                 (void *)&hNDK2NSP->Filter,
                 sizeof(uint32_t));


    /* Clear the Old multicast list settings */
    {
        ALE_MulticastIoctlCmd cmd;

        cmd.addrCount   = hNDK2NSP->OldMCastCnt;
        cmd.pMCastList  = hNDK2NSP->bOldMCast;

        GMACSW_ioctl(hNDK2NSP->hGMACSW,
                    GMACSW_IOCTL_ALE_CLEAR_MULTICAST,
                    (void *)&cmd,
                    sizeof(ALE_MulticastIoctlCmd));
    }

    hNDK2NSP->OldMCastCnt = 0;

    /* Finally configure the Filter and new multicast settings in the GMACSW ALE. */
    {
        ALE_MulticastIoctlCmd cmd;

        cmd.addrCount   = hNDK2NSP->MCastCnt;
        cmd.pMCastList  = hNDK2NSP->bMCast;

        i = GMACSW_ioctl(hNDK2NSP->hGMACSW,
                    GMACSW_IOCTL_ALE_SET_MULTICAST,
                    (void *)&cmd,
                    sizeof(ALE_MulticastIoctlCmd));
        if (i != 0)
        {
            dprint1("GMACSW_setMulticast Returned error %0x08X\n",i);
            return;
        }
    }
    GMACSW_AL_globalInterruptEnable(key);

    /* Save count and entries for deletion next time around */
    hNDK2NSP->OldMCastCnt = hNDK2NSP->MCastCnt;
    for(i = 0; i < hNDK2NSP->MCastCnt; i++)
    {
        mmCopy(&hNDK2NSP->bOldMCast[(uint32_t)6U*i], &hNDK2NSP->bMCast[(uint32_t)6U*i], (uint)6U);
    }
}

/*!
 *  @b NDK2NSP_sendTxPackets
 *  @n
 *      Routine to send out queued Tx packets to the hardware driver
 *
 *  \param[in]  hNDK2NSP
 *      NDK2NSP_object structure pointer.
 *
 *  \retval
 *      void
 */
void NDK2NSP_sendTxPackets( NDK2NSP_Handle hNDK2NSP )
{
    /* If link is not up, simply return */
    if (1U == hNDK2NSP->linkIsUp)
    {
        CPDMA_Packet *pPrevCPDMAPacket = NULL;
        PBM_Handle hPBMPacket;
        CPDMA_PacketQueue tempQueue;

        CPDMA_packetQueueInit(&tempQueue);

        /* If there is nothing queued to transmit, simply return */
        hPBMPacket = PBMQ_deq(&hNDK2NSP->txReadyPBMPacketQueue);
        while (NULL != hPBMPacket)
        {
            CPDMA_Packet *pCurrCPDMAPacket;

#if defined(NSP_INSTRUMENTATION_ENABLED)
            ndk2NspStats.txReadyPBMPacketDequeue++;
#endif

            /* Allocate a packet from the Tx CPDMA packet pool */
            pCurrCPDMAPacket = CPDMA_packetDequeue(&hNDK2NSP->txFreeCPDMAPacketQueue);
            if (NULL != pCurrCPDMAPacket)
            {
                /* Populate the packet and the buffer descriptor(s) it contains */
                uint8_t             *buffer = PBM_getDataBuffer(hPBMPacket) + PBM_getDataOffset(hPBMPacket);
                uint32_t            length = PBM_getValidLen(hPBMPacket);
                CPDMA_BuffDesc      *pFirstBuffDesc = CPDMA_packetGetFirstDesc(pCurrCPDMAPacket);
                CPDMA_BuffDesc      *pLastBuffDesc = CPDMA_packetGetLastDesc(pCurrCPDMAPacket);

#if defined(NSP_INSTRUMENTATION_ENABLED)
                ndk2NspStats.txFreeCPDMAPacketDequeue++;
#endif

#if defined(DATA_BUFFERS_IN_CACHED_MEMORY)
                /* Clean the cache for the packet data so CPDMA gets correct data */
                Cache_wbInv( (Ptr)(PBM_getDataBuffer(hPBMPacket)),
                             (SizeT)(length + PBM_getDataOffset(hPBMPacket)),
                             (Bits16)Cache_Type_ALLD,
                             (Bool)1U);
#endif

                /*
                 * Save off the PBM packet handle so it can be freed when the CPDMA
                 * packet is freed via the callback after it is transmitted
                 */
                pCurrCPDMAPacket->hPrivate = (void *)hPBMPacket;

                CPDMA_setHardwareAsOwner(pFirstBuffDesc);
                CPDMA_setStartOfPacket  (pFirstBuffDesc);
                CPDMA_setDataBuffer     (pFirstBuffDesc, buffer);
                CPDMA_setBufferLength   (pFirstBuffDesc, (uint16_t)length);
                CPDMA_setBufferOffset   (pFirstBuffDesc, 0);
                CPDMA_setPacketLength   (pFirstBuffDesc, (uint16_t)length);
                CPDMA_setEndOfPacket    (pLastBuffDesc);
                CPDMA_clearEndOfQueue   (pLastBuffDesc);

                if (1U == hNDK2NSP->inDLBMode)
                {
                    /*
                     * In digital loopback mode, we only want to send to SL/MAC port 1, so we only get one Rx in return.
                     * To accomplish that, we make the buffer descriptor be directed.
                     */
                    CPDMA_setTxToPort(pFirstBuffDesc, (uint32_t)1U);
                }

                /* Link the packets' buffer descriptor queues as we go through them */
                if (pPrevCPDMAPacket)
                {
                    pPrevCPDMAPacket->buffDescQueue.pTail->pNextBufferDescriptor = pFirstBuffDesc;
                }
                pPrevCPDMAPacket = pCurrCPDMAPacket;

                CPDMA_packetEnqueue(&tempQueue, pCurrCPDMAPacket);
            }
            else
            {
                /* Free the packet as we couldn't allocate an associated CPDMA packet */
                PBM_free(hPBMPacket);
#if defined(NSP_INSTRUMENTATION_ENABLED)
                ndk2NspStats.txDroppedPacketCount++;
#endif
            }
            hPBMPacket = PBMQ_deq(&hNDK2NSP->txReadyPBMPacketQueue);
        }

        /* Give the accumulated packets to the hardware */
        {
            CPDMA_SubmitPacketQueueIoctlCmd cmd;

            cmd.hChannel                    = hNDK2NSP->hTxChannel;
            cmd.pToChannelQueue             = &tempQueue;

            GMACSW_ioctl(hNDK2NSP->hGMACSW,
                        GMACSW_IOCTL_CPDMA_SUBMIT_PACKETS,
                        (void *)&cmd,
                        sizeof(CPDMA_SubmitPacketQueueIoctlCmd));
        }
    }
}

/*!
 *  @b NDK2NSP_ioctl
 *  @n
 *  Low level driver Ioctl interface. This interface can be used for
 *  ALE configuration,control,statistics
 *
 *  \param[in]  hNDK2NSP
 *      NDK2NSP_object structure pointer.
 *  \param[in]  cmd
 *      Ioctl command.
 *  \param[in]  pBuf
 *      Ioctl buffer with commands and params to set/get
 *      configuration from hardware.
 *  \param[in]  size
 *      Size of Ioctl buffer.
 *
 *  \retval
 *      void
 */
uint32_t NDK2NSP_ioctl(NDK2NSP_Handle hNDK2NSP, uint32_t cmd, void* param, uint32_t size)
{
    /* NDK2NSP doesn't have any of its own IOCTL commands, so pass it to the driver */
    return GMACSW_ioctl(hNDK2NSP->hGMACSW, cmd, param, size);
}


/*---------------------------------------------------------------------------*\
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/

static void LOCAL_pollingCallback(void *hCallbackArg)
{
    static uint32_t loadCount = 0;
    NDK2NSP_Handle hNDK2NSP = (NDK2NSP_Handle) hCallbackArg;
    Load_Stat stat;

    uint32_t prevLinkState = hNDK2NSP->linkIsUp;
    uint32_t prevLinkInterface = hNDK2NSP->currLinkedInterface;

    ndk2NspStats.gCpuLoad[loadCount] = Load_getCPULoad();

    if (Load_getGlobalHwiLoad(&stat))
    {
        ndk2NspStats.gHwiLoad[loadCount] = Load_calculateLoad(&stat);
    }
    if (Load_getTaskLoad(hNDK2NSP->rxPacketTask, &stat))
    {
        ndk2NspStats.rxStats.taskLoad[loadCount] = Load_calculateLoad(&stat);
    }
    if (Load_getTaskLoad(hNDK2NSP->txPacketTask, &stat))
    {
        ndk2NspStats.txStats.taskLoad[loadCount] = Load_calculateLoad(&stat);
    }

    loadCount = (loadCount + 1U) & (HISTORY_CNT - 1U);

    /* Get current link status as reported by the hardware driver */
    GMACSW_getLinkStatus(hNDK2NSP->hGMACSW, &hNDK2NSP->linkIsUp, &hNDK2NSP->currLinkedInterface);

    /* If the interface changed, discard any queue packets (since the MAC would now be wrong) */
    if (prevLinkInterface != hNDK2NSP->currLinkedInterface)
    {
        /* ToDo: Discard all queued packets */
    }

    /* If link status changed from down->up, then send any queued packets */
    if ((prevLinkState == 0) && (hNDK2NSP->linkIsUp != 0U))
    {
        NDK2NSP_sendTxPackets( hNDK2NSP );
    }

}

static void LOCAL_closeRxChannel(void *hCallbackArg)
{
    CPDMA_PacketQueue tempQueue;
    CPDMA_Packet *pCurrCPDMAPacket;
    uint32_t i;
    NDK2NSP_Handle hNDK2NSP = (NDK2NSP_Handle ) hCallbackArg;

    /* Post to rx packet task so that it will terminate (shutDown flag is already set) */
    if (hNDK2NSP->rxPacketTask != NULL)
    {
        SemPost(hNDK2NSP->rxPacketSem);
    }

    /*
     * Clear out the fromHardware queue, which should contain all packets
     * being returned from the hardware.
     */
    {
        CPDMA_RetrievePacketQueueIoctlCmd cmd;

        CPDMA_packetQueueInit(&tempQueue);

        cmd.hChannel                    = hNDK2NSP->hRxChannel;
        cmd.pFromChannelQueue           = &tempQueue;

        GMACSW_ioctl(hNDK2NSP->hGMACSW,
                     GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                     (void *)&cmd,
                     sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
    }

    /*
     * Take all PBM packets from the fromHardware queue and put them on the
     * rxFreePBMPacketQueue.
     */
    pCurrCPDMAPacket = CPDMA_packetDequeue(&tempQueue);
    while (NULL != pCurrCPDMAPacket)
    {
        /* Get the PBM packets that need to be freed */
        PBM_Handle hPBMPacket = (PBM_Handle) pCurrCPDMAPacket->hPrivate;

        if (hPBMPacket)
        {
            PBMQ_enq(&hNDK2NSP->rxFreePBMPacketQueue, hPBMPacket);
        }
        pCurrCPDMAPacket = CPDMA_packetDequeue(&tempQueue);
    }

    /* Free all PBM packets (this should be all of them) */
    for (i = 0U; i< ((uint32_t)NDK2NSP_RX_PACKETS*(uint32_t)2U); i++)
    {
        PBM_Handle hPBMPacket = PBMQ_deq(&hNDK2NSP->rxFreePBMPacketQueue);
        if (hPBMPacket)
        {
            PBM_free(hPBMPacket);
        }
    }
}

static void LOCAL_closeTxChannel(void *hCallbackArg)
{
    NDK2NSP_Handle hNDK2NSP = (NDK2NSP_Handle ) hCallbackArg;
    CPDMA_PacketQueue tempQueue;
    CPDMA_Packet *pCurrCPDMAPacket;

    /* Post to rx packet task so that it will terminate (shutDown flag is already set) */
    SemPost(hNDK2NSP->txPacketSem);

    /*
     * Clear out the fromHardware queue, which should contain all packets
     * being returned from the hardware.
     */
    {
        CPDMA_RetrievePacketQueueIoctlCmd cmd;

        CPDMA_packetQueueInit(&tempQueue);

        cmd.hChannel                    = hNDK2NSP->hTxChannel;
        cmd.pFromChannelQueue           = &tempQueue;

        GMACSW_ioctl(hNDK2NSP->hGMACSW,
                     GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                     (void *)&cmd,
                     sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
    }

    /*
     * Take all PBM packets from the fromHardware queue and free any
     * PBM attached packets.
     */
    pCurrCPDMAPacket = CPDMA_packetDequeue(&tempQueue);
    while (NULL != pCurrCPDMAPacket)
    {
        /* Get the PBM packets that need to be freed */
        PBM_Handle hPBMPacket = (PBM_Handle) pCurrCPDMAPacket->hPrivate;

        if (hPBMPacket)
        {
            PBM_free(hPBMPacket);
        }
        pCurrCPDMAPacket = CPDMA_packetDequeue(&tempQueue);
    }
}

static void LOCAL_notifyRxPackets(void *hCallbackArg)
{
    /* Post semaphore to rx handling task */
    NDK2NSP_Handle hNDK2NSP = (NDK2NSP_Handle ) hCallbackArg;

    SemPost(hNDK2NSP->rxPacketSem);
}

static void LOCAL_notifyTxPackets(void *hCallbackArg)
{
    /* Post semaphore to tx handling task */
    NDK2NSP_Handle hNDK2NSP = (NDK2NSP_Handle ) hCallbackArg;

    SemPost(hNDK2NSP->txPacketSem);
}

static void LOCAL_rxPacketTask(void *arg0)
{
    NDK2NSP_Handle hNDK2NSP = (NDK2NSP_Handle) arg0;
    CPDMA_PacketQueue tempQueue;
#if defined(NSP_INSTRUMENTATION_ENABLED)
    uint32_t time1 = 0;
    uint32_t packetCount;
#endif

    while (!hNDK2NSP->shutDown)
    {
        /* Wait for the Rx ISR to notify us that packets are available with data */
        SemPend(hNDK2NSP->rxPacketSem, SEM_FOREVER);

        if (hNDK2NSP->shutDown)
        {
            /* This translation layer is shutting down, don't give anything else to the stack */
            break;
        }

#if defined(NSP_INSTRUMENTATION_ENABLED)
        time1 = TIMER_READ();
        ndk2NspStats.rxStats.rawNotificationCount++;
        packetCount = 0;
#endif

        /* Retrieve the used (filled) packets from the channel */
        {
            CPDMA_RetrievePacketQueueIoctlCmd cmd;

            CPDMA_packetQueueInit(&tempQueue);

            cmd.hChannel                    = hNDK2NSP->hRxChannel;
            cmd.pFromChannelQueue           = &tempQueue;

            /* This function will initialize the tempQueue variable */
            GMACSW_ioctl(hNDK2NSP->hGMACSW,
                        GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                        (void *)&cmd,
                        sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
        }

        if (tempQueue.count != 0U)
        {
            /*
             * Get all used Rx CPDMA packets from the hardware, then send the buffers
             * of those packets on to the NDK stack to be parsed/processed.
             */
#if defined(NSP_INSTRUMENTATION_ENABLED)
            packetCount =
#endif
            LOCAL_prepRxPacketQueue(hNDK2NSP, &tempQueue);
        }
#if defined(NSP_INSTRUMENTATION_ENABLED)
        else
        {
            ndk2NspStats.rxStats.zeroNotificationCount++;
        }

        /*
         * We don't want to time the semaphore post used to notify the NDK stack as that may cause a
         * task transition. We don't want to time the semaphore pend, since that would time us doing
         * nothing but waiting.
         */
        if (packetCount != 0)
        {
            uint32_t notificationCount;
            uint32_t timeDiff = TIMER_READ_AND_DIFF(time1);
            uint32_t timePerPacket = timeDiff/packetCount;

            notificationCount = ndk2NspStats.rxStats.dataNotificationCount & (HISTORY_CNT - 1U);
            ndk2NspStats.rxStats.dataNotificationCount++;

            ndk2NspStats.rxStats.totalPacketCnt += packetCount;
            ndk2NspStats.rxStats.totalCycleCnt += timeDiff;

            ndk2NspStats.rxStats.cycleCountPerNotification[notificationCount] = timeDiff;
            if (timeDiff > ndk2NspStats.rxStats.cycleCountPerNotificationMax)
            {
                ndk2NspStats.rxStats.cycleCountPerNotificationMax = timeDiff;
            }

            ndk2NspStats.rxStats.packetsPerNotification[notificationCount] = packetCount;
            if (packetCount > ndk2NspStats.rxStats.packetsPerNotificationMax)
            {
                ndk2NspStats.rxStats.packetsPerNotificationMax = packetCount;
            }

            ndk2NspStats.rxStats.cycleCountPerPacket[notificationCount] = timePerPacket;
            if (timePerPacket >ndk2NspStats.rxStats.cycleCountPerPacketMax)
            {
                ndk2NspStats.rxStats.cycleCountPerPacketMax = timePerPacket;
            }
        }
#endif
        /* Notify NDK stack that packets are available (this is basically a SemPost) */
        if (PBMQ_count(&hNDK2NSP->rxReadyPBMPacketQueue) != 0U)
        {
            ((STKEVENT *)(hNDK2NSP->hEvent))->EventCodes[STKEVENT_ETHERNET] = 1;
            if( ((STKEVENT *)(hNDK2NSP->hEvent))->hSemEvent != NULL)
            {
                SemPost( ((STKEVENT *)(hNDK2NSP->hEvent))->hSemEvent );
            }
#if defined(NSP_INSTRUMENTATION_ENABLED)
            ndk2NspStats.ndkStackNotifyCount++;
#endif
        }
    }

    /* We are shutting down, notify that we are done */
    SemPost(hNDK2NSP->shutDownSem);
}

static void LOCAL_txPacketTask(void *arg0)
{
    NDK2NSP_Handle hNDK2NSP = (NDK2NSP_Handle) arg0;
    CPDMA_PacketQueue tempQueue;

#if defined(NSP_INSTRUMENTATION_ENABLED)
    uint32_t time1 = 0;
    uint32_t packetCount = 0;
#endif

    while (!hNDK2NSP->shutDown)
    {
        /*
         * Wait for the Tx ISR to notify us that empty packets are available
         * that were used to send data
         */
        SemPend(hNDK2NSP->txPacketSem, SEM_FOREVER);
#if defined(NSP_INSTRUMENTATION_ENABLED)
        time1 = TIMER_READ();
        ndk2NspStats.txStats.rawNotificationCount++;
        packetCount = 0;
#endif

        /* Retrieve the used (sent/empty) packets from the channel */
        {
            CPDMA_RetrievePacketQueueIoctlCmd cmd;

            CPDMA_packetQueueInit(&tempQueue);

            cmd.hChannel                    = hNDK2NSP->hTxChannel;
            cmd.pFromChannelQueue           = &tempQueue;

            /* This function will initialize the tempQueue variable */
            GMACSW_ioctl(hNDK2NSP->hGMACSW,
                        GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                        (void *)&cmd,
                        sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
        }

        if (tempQueue.count != 0U)
        {
            /*
             * Get all used Tx CPDMA packets from the hardware, then return those
             * buffers to the txFreePacketQueue so they can be used later to send with.
             */
#if defined(NSP_INSTRUMENTATION_ENABLED)
            packetCount =
#endif
            LOCAL_prepTxPacketQueue(hNDK2NSP, &tempQueue);
        }
#if defined(NSP_INSTRUMENTATION_ENABLED)
        else
        {
            ndk2NspStats.txStats.zeroNotificationCount++;
        }

        if (packetCount != 0)
        {
            uint32_t notificationCount;
            uint32_t timeDiff = TIMER_READ_AND_DIFF(time1);
            uint32_t timePerPacket = timeDiff/packetCount;

            notificationCount = ndk2NspStats.txStats.dataNotificationCount & (HISTORY_CNT - 1U);
            ndk2NspStats.txStats.dataNotificationCount++;

            ndk2NspStats.txStats.totalPacketCnt += packetCount;
            ndk2NspStats.txStats.totalCycleCnt += timeDiff;

            ndk2NspStats.txStats.cycleCountPerNotification[notificationCount] = timeDiff;
            if (timeDiff > ndk2NspStats.txStats.cycleCountPerNotificationMax)
            {
                ndk2NspStats.txStats.cycleCountPerNotificationMax = timeDiff;
            }

            ndk2NspStats.txStats.packetsPerNotification[notificationCount] = packetCount;
            if (packetCount > ndk2NspStats.txStats.packetsPerNotificationMax)
            {
                ndk2NspStats.txStats.packetsPerNotificationMax = packetCount;
            }

            ndk2NspStats.txStats.cycleCountPerPacket[notificationCount] = timePerPacket;
            if (timePerPacket >ndk2NspStats.txStats.cycleCountPerPacketMax)
            {
                ndk2NspStats.txStats.cycleCountPerPacketMax = timePerPacket;
            }
        }
#endif
    }

    /* We are shutting down, notify that we are done */
    SemPost(hNDK2NSP->shutDownSem);
}

static void LOCAL_allocRxPackets(NDK2NSP_Handle hNDK2NSP)
{
    CPDMA_PacketQueue tempQueue;
    uint32_t i;

    /*
     * Pre-allocate twice as many NDK stack packets as we plan to give to/get from the hardware.
     * The idea here is that even if we fill up all the buffer descriptors in the inUse
     * queue, we will have another complete set to swap in right away.
     */
    for (i = 0U; i < ((uint32_t)NDK2NSP_RX_PACKETS*(uint32_t)2U); i++)
    {
        PBM_Handle hPBMPacket = PBM_alloc((uint)(hNDK2NSP->PktMTU + (uint32_t)4U + PKT_PREPAD));
        if (hPBMPacket)
        {
            /* Enqueue to the free queue */
            PBMQ_enq(&hNDK2NSP->rxFreePBMPacketQueue, hPBMPacket);
#if defined(NSP_INSTRUMENTATION_ENABLED)
            ndk2NspStats.rxFreePBMPacketEnqueue++;
#endif
        }
    }

    /*
     * Get the contents of the fromHardware queue, which should contain all packets
     * initially allocated by the channel open function.
     */
    {
        CPDMA_RetrievePacketQueueIoctlCmd cmd;

        CPDMA_packetQueueInit(&tempQueue);

        cmd.hChannel                    = hNDK2NSP->hRxChannel;
        cmd.pFromChannelQueue           = &tempQueue;

        GMACSW_ioctl(hNDK2NSP->hGMACSW,
                     GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                     (void *)&cmd,
                     sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
    }

    /*
     * Go through packets in the queue, prep them to give to the
     * CPDMA Rx channel, then submit them to the channel
     */
    LOCAL_prepRxPacketQueue(hNDK2NSP, &tempQueue);
}

static void LOCAL_allocTxPackets(NDK2NSP_Handle hNDK2NSP)
{
    CPDMA_PacketQueue tempQueue;

    /*
     * Clear out the fromHardware queue, which should contain all packets
     * initially allocated by the channel open function.
     */
    {
        CPDMA_RetrievePacketQueueIoctlCmd cmd;

        CPDMA_packetQueueInit(&tempQueue);

        cmd.hChannel                    = hNDK2NSP->hTxChannel;
        cmd.pFromChannelQueue           = &tempQueue;

        GMACSW_ioctl(hNDK2NSP->hGMACSW,
                     GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                     (void *)&cmd,
                     sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
    }

    /*
     * Go through the CPDMA packets in the queue, and move them to the
     * txFreeCPDMAPacketQueue so they are ready to be used when the stack
     * wants to send a packet
     */
    LOCAL_prepTxPacketQueue(hNDK2NSP, &tempQueue);
}

static uint32_t LOCAL_prepRxPacketQueue(NDK2NSP_Handle hNDK2NSP, CPDMA_PacketQueue *pPacketQueue)
{
    CPDMA_Packet *pCurrCPDMAPacket;
    CPDMA_Packet *pNextCPDMAPacket;

    uint32_t packetCount = 0;

    pCurrCPDMAPacket = pPacketQueue->pHead;
    while (pCurrCPDMAPacket)
    {
        /* Get the full PBM packet that needs to be returned to the NDK stack */
        PBM_Handle hPBMPacket = (PBM_Handle) pCurrCPDMAPacket->hPrivate;

        if (hPBMPacket)
        {
            uint32_t validLen = CPDMA_packetGetLength(pCurrCPDMAPacket) - 4U;

            /* Fill in PBM packet length field */
            PBM_setValidLen(hPBMPacket, validLen);

#if defined(DATA_BUFFERS_IN_CACHED_MEMORY)
#if defined(CORTEX_AX)
            /*
             * Invalidate the data buffer so the CPU is forced to read new data from HW.
             * We only need to so this on the Cortex v7A devices because of possible
             * speculative reads done by the CPU core while the buffers are owned by the
             * CPDMA hardware.
             */
            {
                uint8_t *buffer             = PBM_getDataBuffer(hPBMPacket);
                uint32_t length             = validLen + PKT_PREPAD;
                Cache_inv((Ptr)buffer,
                      (SizeT)length,
                      (Bits16)Cache_Type_ALLD,
                      (Bool)1U);
            }
#endif
#endif

            /* Enqueue the received packet so that it can be consumed by the NDK stack*/
            PBMQ_enq(&hNDK2NSP->rxReadyPBMPacketQueue, hPBMPacket);

#if defined(NSP_INSTRUMENTATION_ENABLED)
            ndk2NspStats.rxReadyPBMPacketEnqueue++;
#endif
            packetCount++;
        }

        /* Dequeue an empty PBM packet to be associated with a CPDMA packet for the hardware */
        hPBMPacket = PBMQ_deq(&hNDK2NSP->rxFreePBMPacketQueue);
        if (hPBMPacket)
        {
#if defined(NSP_INSTRUMENTATION_ENABLED)
            ndk2NspStats.rxFreePBMPacketDequeue++;
#endif
            /* Link the new PBM packet to the CPDMA packet */
            CPDMA_BuffDesc *pBuffDesc           = CPDMA_packetGetFirstDesc(pCurrCPDMAPacket);
            uint8_t *buffer                     = PBM_getDataBuffer(hPBMPacket);
            uint32_t length                     = PBM_getBufferLen(hPBMPacket);

            /* The PBM packet has a data offset */
            PBM_setDataOffset( hPBMPacket, PKT_PREPAD );

            /* Save off the PBM packet handle so it can be handled by this layer later */
            pCurrCPDMAPacket->hPrivate          = (void *)hPBMPacket;

            /* The CPDMA buffer should skip past the NDK prepad */
            pBuffDesc->pDataBuffer              = buffer+PKT_PREPAD;
            pBuffDesc->bufferOffsetAndLength    = length-PKT_PREPAD;
            /* Mark the packet as owned by the hardware */
            pBuffDesc->flagsAndPacketLength     = CPDMA_BUF_DESC_OWNER_FLAG;

#if defined(DATA_BUFFERS_IN_CACHED_MEMORY)
            /*
             * Pre-invalidate the data buffer so that no spurious evictions will possibly
             * corrupt the packet buffer while the hardware CPDMA has ownership. We invalidate
             * the entire buffer since we don't know how big the arriving packets will be.
             */
            Cache_inv((Ptr)buffer,
                      (SizeT)length,
                      (Bits16)Cache_Type_ALLD,
                      (Bool)1U);
#endif

            /* Link the packets' buffer descriptor queues as we go through them */
            pNextCPDMAPacket = pCurrCPDMAPacket->pNextPacket;
            if (pNextCPDMAPacket)
            {
                pBuffDesc->pNextBufferDescriptor = pNextCPDMAPacket->buffDescQueue.pHead;
            }
            else
            {
                pBuffDesc->pNextBufferDescriptor = NULL;
            }
            pCurrCPDMAPacket = pNextCPDMAPacket;
        }
        else
        {
            pCurrCPDMAPacket = NULL;
        }
    }

    /*
     * Return the same CPDMA packets back to the CPDMA channel (but now
     * associated with a new PBM Packet and buffer)
     */
    {
        CPDMA_SubmitPacketQueueIoctlCmd cmd;

        cmd.hChannel                    = hNDK2NSP->hRxChannel;
        cmd.pToChannelQueue             = pPacketQueue;

        GMACSW_ioctl(hNDK2NSP->hGMACSW,
                    GMACSW_IOCTL_CPDMA_SUBMIT_PACKETS,
                    (void *)&cmd,
                    sizeof(CPDMA_SubmitPacketQueueIoctlCmd));
    }

    return packetCount;
}

static uint32_t LOCAL_prepTxPacketQueue(NDK2NSP_Handle hNDK2NSP, CPDMA_PacketQueue *pPacketQueue)
{
    CPDMA_Packet *pCurrCPDMAPacket;

    uint32_t packetCount = 0;

    pCurrCPDMAPacket = pPacketQueue->pHead;
    while (pCurrCPDMAPacket)
    {
        PBM_Handle hPBMPacket = (PBM_Handle) pCurrCPDMAPacket->hPrivate;

        /* Free the packet - it was allocated by the stack/sender */
        if (hPBMPacket)
        {
            PBM_free(hPBMPacket);
            packetCount++;
        }

        /* Unlink the packets' buffer descriptor queues as we go through them */
        pCurrCPDMAPacket->buffDescQueue.pTail->pNextBufferDescriptor = NULL;

        pCurrCPDMAPacket = pCurrCPDMAPacket->pNextPacket;
    }

    /* Attach the queue of packets being returned from the hardware to the free packet queue */
    {
        uint32_t key = GMACSW_AL_globalInterruptDisable();

        /* Moved the queue of packets into the txFreeCPDMAPacketQueue */
        CPDMA_appendPacketQueue(&hNDK2NSP->txFreeCPDMAPacketQueue, pPacketQueue);

        /* Clear the input queue */
        CPDMA_packetQueueInit(pPacketQueue);

        GMACSW_AL_globalInterruptEnable(key);
    }

#if defined(NSP_INSTRUMENTATION_ENABLED)
    ndk2NspStats.txFreeCPDMAPacketEnqueue += pPacketQueue->count;
#endif

    return packetCount;
}


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

