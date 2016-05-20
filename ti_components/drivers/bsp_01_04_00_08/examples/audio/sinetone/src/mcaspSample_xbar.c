/******************************************************************************
 *                                                                            *
 * Copyright (c) 2014 Texas Instruments Incorporated - http://www.ti.com/     *
 *                                                                            *
 * All rights reserved. Property of Texas Instruments Incorporated.           *
 * Restricted rights to use, duplicate or disclose this code are              *
 * granted through contract.                                                  *
 *                                                                            *
 * The program may not be used without the written permission                 *
 * of Texas Instruments Incorporated or against the terms and conditions      *
 * stipulated in the agreement under which this program has been              *
 * supplied.                                                                  *
 *                                                                            *
 *****************************************************************************/

/** \file     mcaspSample_xbar.c
 *
 *  \brief    sample application for demostration of audio driver usage
 *
 *  This file contains the implementation of the sample appliation for the
 *  demonstration of audio playing through the audio interface layer.
 *
 *             (C) Copyright 2014, Texas Instruments, Inc
 */

/* ========================================================================== */
/*                            INCLUDE FILES                                   */
/* ========================================================================== */

#include <xdc/std.h>
#include <stdint.h>

#include <soc.h>
#include <soc_defines.h>
#include <chip_config.h>
#include <irq_xbar.h>
#include <irq_xbar_interrupt_ids.h>
#include <dma_xbar.h>
#include <dma_xbar_event_ids.h>

/* ========================================================================== */
/*                           FUNCTION PROTOTYPE                          */
/* ========================================================================== */

void Configure_XBAR(void);

/*
 * ======== Configure_XBAR ========
 * This function configures the INT and DMA XBARs for the TDA2XX_FAMILY_BUILD.
 */
void Configure_XBAR(void)
{
#if defined (TDA2XX_FAMILY_BUILD)

    #if defined (BUILD_DSP)

    /* DSP INT XBAR mapping for all McASP instances                 */
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_DSP1,
                   (UInt32) XBAR_INST_DSP1_IRQ_58,
                   McASP1_IRQ_AREVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_DSP1,
                   (UInt32) XBAR_INST_DSP1_IRQ_59,
                   McASP1_IRQ_AXEVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_DSP1,
                   (UInt32) XBAR_INST_DSP1_IRQ_60,
                   McASP2_IRQ_AREVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_DSP1,
                   (UInt32) XBAR_INST_DSP1_IRQ_61,
                   McASP2_IRQ_AXEVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_DSP1,
                   (UInt32) XBAR_INST_DSP1_IRQ_91,
                   McASP3_IRQ_AREVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_DSP1,
                   (UInt32) XBAR_INST_DSP1_IRQ_92,
                   McASP3_IRQ_AXEVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_DSP1,
                   (UInt32) XBAR_INST_DSP1_IRQ_74,
                   McASP4_IRQ_AREVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_DSP1,
                   (UInt32) XBAR_INST_DSP1_IRQ_51,
                   McASP4_IRQ_AXEVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_DSP1,
                   (UInt32) XBAR_INST_DSP1_IRQ_79,
                   McASP5_IRQ_AREVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_DSP1,
                   (UInt32) XBAR_INST_DSP1_IRQ_81,
                   McASP5_IRQ_AXEVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_DSP1,
                   (UInt32) XBAR_INST_DSP1_IRQ_86,
                   McASP6_IRQ_AREVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_DSP1,
                   (UInt32) XBAR_INST_DSP1_IRQ_87,
                   McASP6_IRQ_AXEVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_DSP1,
                   (UInt32) XBAR_INST_DSP1_IRQ_88,
                   McASP7_IRQ_AREVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_DSP1,
                   (UInt32) XBAR_INST_DSP1_IRQ_43,
                   McASP7_IRQ_AXEVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_DSP1,
                   (UInt32) XBAR_INST_DSP1_IRQ_48,
                   McASP8_IRQ_AREVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_DSP1,
                   (UInt32) XBAR_INST_DSP1_IRQ_49,
                   McASP8_IRQ_AXEVT);

    #elif defined (BUILD_M4)
    /*  M4 INT XBAR mapping for all McASP instances                 */
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1,
                   (UInt32) XBAR_INST_IPU1_IRQ_27,
                   McASP1_IRQ_AREVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1,
                   (UInt32) XBAR_INST_IPU1_IRQ_28,
                   McASP1_IRQ_AXEVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1,
                   (UInt32) XBAR_INST_IPU1_IRQ_29,
                   McASP2_IRQ_AREVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1,
                   (UInt32) XBAR_INST_IPU1_IRQ_30,
                   McASP2_IRQ_AXEVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1,
                   (UInt32) XBAR_INST_IPU1_IRQ_31,
                   McASP3_IRQ_AREVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1,
                   (UInt32) XBAR_INST_IPU1_IRQ_32,
                   McASP3_IRQ_AXEVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1,
                   (UInt32) XBAR_INST_IPU1_IRQ_33,
                   McASP4_IRQ_AREVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1,
                   (UInt32) XBAR_INST_IPU1_IRQ_59,
                   McASP4_IRQ_AXEVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1,
                   (UInt32) XBAR_INST_IPU1_IRQ_60,
                   McASP5_IRQ_AREVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1,
                   (UInt32) XBAR_INST_IPU1_IRQ_61,
                   McASP5_IRQ_AXEVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1,
                   (UInt32) XBAR_INST_IPU1_IRQ_62,
                   McASP6_IRQ_AREVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1,
                   (UInt32) XBAR_INST_IPU1_IRQ_63,
                   McASP6_IRQ_AXEVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1,
                   (UInt32) XBAR_INST_IPU1_IRQ_69,
                   McASP7_IRQ_AREVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1,
                   (UInt32) XBAR_INST_IPU1_IRQ_70,
                   McASP7_IRQ_AXEVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1,
                   (UInt32) XBAR_INST_IPU1_IRQ_71,
                   McASP8_IRQ_AREVT);
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1,
                   (UInt32) XBAR_INST_IPU1_IRQ_72,
                   McASP8_IRQ_AXEVT);

    /* DMA XBAR mapping for all McASP instances.  Common among all 
     * cores, but default mapping only needs to be overridden for
     * the M4. */
    DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, EDMA,
                   (UInt32) XBAR_INST_DMA_EDMA_DREQ_0,
                   McASP1_DREQ_RX);
    DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, EDMA,
                   (UInt32) XBAR_INST_DMA_EDMA_DREQ_1,
                   McASP1_DREQ_TX);
    DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, EDMA,
                   (UInt32) XBAR_INST_DMA_EDMA_DREQ_2,
                   McASP2_DREQ_RX);
    DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, EDMA,
                   (UInt32) XBAR_INST_DMA_EDMA_DREQ_3,
                   McASP2_DREQ_TX);
    DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, EDMA,
                   (UInt32) XBAR_INST_DMA_EDMA_DREQ_4,
                   McASP3_DREQ_RX);
    DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, EDMA,
                   (UInt32) XBAR_INST_DMA_EDMA_DREQ_5,
                   McASP3_DREQ_TX);
    DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, EDMA,
                   (UInt32) XBAR_INST_DMA_EDMA_DREQ_6,
                   McASP4_DREQ_RX);
    DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, EDMA,
                   (UInt32) XBAR_INST_DMA_EDMA_DREQ_7,
                   McASP4_DREQ_TX);
    DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, EDMA,
                   (UInt32) XBAR_INST_DMA_EDMA_DREQ_8,
                   McASP5_DREQ_RX);
    DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, EDMA,
                   (UInt32) XBAR_INST_DMA_EDMA_DREQ_9,
                   McASP5_DREQ_TX);
    DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, EDMA,
                   (UInt32) XBAR_INST_DMA_EDMA_DREQ_10,
                   McASP6_DREQ_RX);
    DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, EDMA,
                   (UInt32) XBAR_INST_DMA_EDMA_DREQ_11,
                   McASP6_DREQ_TX);
    DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, EDMA,
                   (UInt32) XBAR_INST_DMA_EDMA_DREQ_12,
                   McASP7_DREQ_RX);
    DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, EDMA,
                   (UInt32) XBAR_INST_DMA_EDMA_DREQ_13,
                   McASP7_DREQ_TX);
    DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, EDMA,
                   (UInt32) XBAR_INST_DMA_EDMA_DREQ_14,
                   McASP8_DREQ_RX);
    DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, EDMA,
                   (UInt32) XBAR_INST_DMA_EDMA_DREQ_15,
                   McASP8_DREQ_TX);
    #endif /* defined BUILD_DSP/BUILD_M4 */

#endif

}
/*============================================================================*/
/*                          END OF FILE                                       */
/*============================================================================*/
