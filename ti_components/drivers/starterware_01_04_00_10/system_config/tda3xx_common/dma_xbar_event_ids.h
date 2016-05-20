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
 *  \file   dma_xbar_event_ids.h
 *
 *  \brief  Definitions used for DMA XBAR Event IDs
 *
 *   This file contains all of the DMA XBAR Event IDs needed to program an DMA
 *   XBAR instance.
 */

#ifndef DMA_XBAR_EVENT_IDS_H
#define DMA_XBAR_EVENT_IDS_H

#ifdef __cplusplus
extern "C"
{
#endif
/* Enumerated list of DMA event sources into the DMA_XBAR */
/**
 * \enum xbar_evt_t
 * \brief  Enumeration that contains all possible DMA event source IDs as inputs
 *         to each DMA crossbar instance on Vayu
 *
 */
typedef enum {
    DMA_XBAR_RSVD                  = 0,
    EXT_SYS_DREQ_0                 = 2,
    EXT_SYS_DREQ_1                 = 3,
    GPMC_DREQ                      = 4,
    DISPC_DREQ                     = 6,
    CT_TBR_DREQ                    = 7,
    ISS_DREQ_1                     = 9,
    ISS_DREQ_2                     = 10,
    ISS_DREQ_3                     = 12,
    ISS_DREQ_4                     = 13,
    MCSPI3_DREQ_TX0                = 15,
    MCSPI3_DREQ_RX0                = 16,
    MCSPI3_DREQ_TX1                = 23,
    MCSPI3_DREQ_RX1                = 24,
    I2C1_DREQ_TX                   = 27,
    I2C1_DREQ_RX                   = 28,
    I2C2_DREQ_TX                   = 29,
    I2C2_DREQ_RX                   = 30,
    MCSPI1_DREQ_TX0                = 35,
    MCSPI1_DREQ_RX0                = 36,
    MCSPI1_DREQ_TX1                = 37,
    MCSPI1_DREQ_RX1                = 38,
    MCSPI1_DREQ_TX2                = 39,
    MCSPI1_DREQ_RX2                = 40,
    MCSPI1_DREQ_TX3                = 41,
    MCSPI1_DREQ_RX3                = 42,
    MCSPI2_DREQ_TX0                = 43,
    MCSPI2_DREQ_RX0                = 44,
    MCSPI2_DREQ_TX1                = 45,
    MCSPI2_DREQ_RX1                = 46,
    UART1_DREQ_TX                  = 49,
    UART1_DREQ_RX                  = 50,
    UART2_DREQ_TX                  = 51,
    UART2_DREQ_RX                  = 52,
    UART3_DREQ_TX                  = 53,
    UART3_DREQ_RX                  = 54,
    MMC1_DREQ_TX                   = 61,
    MMC1_DREQ_RX                   = 62,
    MCSPI4_DREQ_TX0                = 70,
    MCSPI4_DREQ_RX0                = 71,
    McASP1_DREQ_RX                 = 128,
    McASP1_DREQ_TX                 = 129,
    DCAN1_DREQ_IF1                 = 158,
    DCAN1_DREQ_IF2                 = 159,
    DCAN1_DREQ_IF3                 = 160,
    DCAN2_DREQ_IF1                 = 161,
    DCAN2_DREQ_IF2                 = 162,
    DCAN2_DREQ_IF3                 = 163,
    EXT_SYS_DREQ_2                 = 167,
    EXT_SYS_DREQ_3                 = 168,
    MCSPI2_DREQ_TX2                = 169,
    MCSPI2_DREQ_RX2                = 170,
    MCSPI2_DREQ_TX3                = 171,
    MCSPI2_DREQ_RX3                = 172,
    MCSPI3_DREQ_TX2                = 173,
    MCSPI3_DREQ_RX2                = 174,
    MCSPI3_DREQ_TX3                = 175,
    MCSPI3_DREQ_RX3                = 176,
    MCSPI4_DREQ_TX1                = 177,
    MCSPI4_DREQ_RX1                = 178,
    MCSPI4_DREQ_TX2                = 179,
    MCSPI4_DREQ_RX2                = 180,
    MCSPI4_DREQ_TX3                = 181,
    MCSPI4_DREQ_RX3                = 182,
    GPIO1_DREQ_EVT                 = 187,
    GPIO2_DREQ_EVT                 = 188,
    GPIO3_DREQ_EVT                 = 189,
    GPIO4_DREQ_EVT                 = 190,
    PWMSS1_DREQ_ePWM0_EVT          = 195,
    PWMSS1_DREQ_eQEP0_EVT          = 198,
    PWMSS1_DREQ_eCAP0_EVT          = 201,
    CRC_DREQ_EVT0                  = 204,
    TSC_ADC_DREQ_FIFO0             = 205,
    TSC_ADC_DREQ_FIFO1             = 206,
    CRC_DREQ_EVT1                  = 207,
    CRC_DREQ_EVT2                  = 208,
    CRC_DREQ_EVT3                  = 209,
    RTI1_DREQ_EVT0                 = 210,
    RTI1_DREQ_EVT1                 = 211,
    RTI1_DREQ_EVT2                 = 212,
    RTI1_DREQ_EVT3                 = 213,
    RTI2_DREQ_EVT0                 = 214,
    RTI2_DREQ_EVT1                 = 215,
    RTI2_DREQ_EVT2                 = 216,
    RTI2_DREQ_EVT3                 = 217,
    RTI3_DREQ_EVT0                 = 218,
    RTI3_DREQ_EVT1                 = 219,
    RTI3_DREQ_EVT2                 = 220,
    RTI3_DREQ_EVT3                 = 221,
    RTI4_DREQ_EVT0                 = 222,
    RTI4_DREQ_EVT1                 = 223,
    RTI4_DREQ_EVT2                 = 224,
    RTI4_DREQ_EVT3                 = 225,
    RTI5_DREQ_EVT0                 = 226,
    RTI5_DREQ_EVT1                 = 227,
    RTI5_DREQ_EVT2                 = 228,
    RTI5_DREQ_EVT3                 = 229
} xbar_evt_t;

#define EDMA_EVT_XBAR_COUNT             0x40
#define DSP1_EDMA_EVT_XBAR_COUNT        0x40
#define DSP2_EDMA_EVT_XBAR_COUNT        0x40
#define DMA_XBAR_MAX_EVT_COUNT          0xE6

#ifdef __cplusplus
}
#endif
#endif
