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

#ifdef __cplusplus
extern "C"
{
#endif

extern uint32_t  CHIPCONFIGGetNumMPUs(void);

extern uint32_t  CHIPCONFIGGetNumIPUs(void);

extern uint32_t  CHIPCONFIGGetNumDSPs(void);

extern uint32_t  CHIPCONFIGGetNumEVEs(void);

extern uint32_t  CHIPCONFIGGetNumPRUSSs(void);

typedef enum
{
    CPU_MPUSS,
    CPU_IPU1,
    CPU_DSP1,
#if !(defined (TDA2EX_BUILD))
    CPU_DSP2,
    CPU_EVE1,
    CPU_EVE2,
    CPU_EVE3,
    CPU_EVE4,
#endif
    CPU_PRUSS1
} cpu_id_t;

typedef enum
{
    EDMA,
#if !(defined (TDA2EX_BUILD))
    EDMA_DSP1,
    EDMA_DSP2
#else
    EDMA_DSP1
#endif
} dma_id_t;

#ifdef __cplusplus
}
#endif

#endif
