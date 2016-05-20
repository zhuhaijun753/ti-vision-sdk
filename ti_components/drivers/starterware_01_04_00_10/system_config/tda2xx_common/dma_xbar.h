/* ======================================================================
 *   Copyright (C) 2013 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */
/**
 *  \file   dma_xbar.h
 *
 *  \brief  This module contains the DMA XBAR hardware abstraction layer
 *
 *   This file contains the DMA XBAR HAL API prototypes and macro definitions.
 */

#ifndef DMA_XBAR_H
#define DMA_XBAR_H

#include "dma_xbar_event_ids.h"
#include "chip_config.h"

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/**
 * \enum   dma_xbar_ret_type_t
 * \brief  Enumeration that specifies all possible return values from the DMA
 *         XBAR
 *
 */
typedef enum
{
    dma_xbar_success,
    invalid_dma_id,
    invalid_dma_xbar_inst_id,
    invalid_event_source_id
} dma_xbar_ret_type_t;

extern dma_xbar_ret_type_t DMAXBARValidateArgs(dma_id_t   dma,
                                               uint32_t   xbarInst,
                                               xbar_evt_t eventSource);

extern uint32_t DMAXBARGetOffset(dma_id_t dma, uint32_t xbarInst);

extern dma_xbar_ret_type_t DMAXBARConnect(uint32_t baseAddr, dma_id_t dma,
                                          uint32_t xbarInst,
                                          xbar_evt_t eventSource);

extern dma_xbar_ret_type_t DMAXBARDisconnect(uint32_t baseAddr,
                                             dma_id_t dma,
                                             uint32_t xbarInst);

extern dma_xbar_ret_type_t DMAXBARIsConnected(uint32_t   baseAddr,
                                              dma_id_t   dma,
                                              uint32_t   xbarInst,
                                              xbar_evt_t eventSource,
                                              uint8_t   *status);

extern dma_xbar_ret_type_t DMAXBARGetConnection(uint32_t    baseAddr,
                                                dma_id_t    dma,
                                                uint32_t    xbarInst,
                                                xbar_evt_t *eventSource);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif
