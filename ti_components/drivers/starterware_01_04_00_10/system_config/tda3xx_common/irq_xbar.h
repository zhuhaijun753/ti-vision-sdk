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
 *  \file   irq_xbar.h
 *
 *  \brief  This module contains the IRQ XBAR hardware abstraction layer
 *
 *   This file contains the IRQ XBAR HAL API prototypes and macro definitions.
 */

#ifndef IRQ_XBAR_HAL_H
#define IRQ_XBAR_HAL_H

#include "irq_xbar_interrupt_ids.h"
#include "chip_config.h"

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/**
 * \enum   irq_xbar_ret_type_t
 * \brief  Enumeration that specifies all possible return values from the IRQ
 *         XBAR
 *
 */
typedef enum
{
    irq_xbar_success,
    invalid_mpu_id,
    invalid_ipu_id,
    invalid_dsp_id,
    invalid_eve_id,
    invalid_pru_id,
    invalid_irq_xbar_inst_id,
    invalid_intr_source_id
} irq_xbar_ret_type_t;

extern irq_xbar_ret_type_t IRQXBARValidateArgs(cpu_id_t   cpu,
                                               uint32_t   xbarInst,
                                               xbar_irq_t intrSource);

extern uint32_t IRQXBARGetOffset(cpu_id_t cpu, uint32_t xbarInst);

extern irq_xbar_ret_type_t IRQXBARConnect(uint32_t baseAddr, cpu_id_t cpu,
                                          uint32_t xbarInst,
                                          xbar_irq_t intrSource);

extern irq_xbar_ret_type_t IRQXBARDisconnect(uint32_t baseAddr,
                                             cpu_id_t cpu,
                                             uint32_t xbarInst);

extern irq_xbar_ret_type_t IRQXBARIsConnected(uint32_t   baseAddr,
                                              cpu_id_t   cpu,
                                              uint32_t   xbarInst,
                                              xbar_irq_t intrSource,
                                              uint8_t   *status);

extern irq_xbar_ret_type_t IRQXBARGetConnection(uint32_t    baseAddr,
                                                cpu_id_t    cpu,
                                                uint32_t    xbarInst,
                                                xbar_irq_t *intrSource);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif
