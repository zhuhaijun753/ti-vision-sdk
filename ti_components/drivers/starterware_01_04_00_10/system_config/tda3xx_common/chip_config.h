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
 *  \file   chip_config.h
 *
 *  \brief  Chip Configuration Hardware Abstraction Layer
 *
 *   This file contains the driver API prototypes and macro definitions.
 */

#ifndef CHIP_CONFIG_H
#define CHIP_CONFIG_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

extern uint32_t  CHIPCONFIGGetNumIPUs(void);

extern uint32_t  CHIPCONFIGGetNumDSPs(void);

extern uint32_t  CHIPCONFIGGetNumEVEs(void);

typedef enum
{
    CPU_IPU1,
    CPU_DSP1,
    CPU_DSP2,
    CPU_EVE1
} cpu_id_t;

typedef enum
{
    EDMA,
    EDMA_DSP1,
    EDMA_DSP2
} dma_id_t;

#ifdef __cplusplus
}
#endif

#endif
