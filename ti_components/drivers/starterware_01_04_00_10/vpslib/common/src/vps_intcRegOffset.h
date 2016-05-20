/******************************************************************************
 *                                                                            *
 * Copyright (c) 2012 Texas Instruments Incorporated - http://www.ti.com/     *
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

/** ============================================================================
 *   \file  vps_intcRegOffset.h
 *
 *   This file contains the Register Desciptions for VPS
 *  ============================================================================
 */

#ifndef VPS_INTCREGOFFSET_H_
#define VPS_INTCREGOFFSET_H_

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/** \brief Start address of the first DSS interrupt set. */
#define VPS_INTC_SET_START_OFFSET       (0x20U)
/** \brief Size in bytes for each DSS interrupt set. */
#define VPS_INTC_SET_SIZE               (0x20U)

#define VPS_INTC_RAW_SET_REG0           (0x00U)
#define VPS_INTC_RAW_SET_REG1           (0x04U)
#define VPS_INTC_ENABLED_CLR_REG0       (0x08U)
#define VPS_INTC_ENABLED_CLR_REG1       (0x0CU)
#define VPS_INTC_ENABLE_SET_REG0        (0x10U)
#define VPS_INTC_ENABLE_SET_REG1        (0x14U)
#define VPS_INTC_ENABLE_CLR_REG0        (0x18U)
#define VPS_INTC_ENABLE_CLR_REG1        (0x1CU)
#define VPS_INTC_EOI_ADDR               (0xA0U)

#define VIP_FIQ_MASK                    (0x14U)
#define VIP_FIQ_CLEAR                   (0x18U)
#define VIP_FIQ_STATUS                  (0x1CU)

/** \brief Start address of the first VPDMA interrupt set. */
#define VPS_VPDMA_INT_SET_START_OFFSET  (0x40U)
/** \brief Size in bytes for each VPDMA interrupt set. */
#define VPS_VPDMA_INT_SET_SIZE          (0x50U)

/**
 *  \brief This offset should be 0xE0 but using 0xD0 because simulator still
 *  has not interoduced two register which are int_channel6_stat and
 *  int_channel6_mask registers
 */
#define VPDMA_INT_CHANNEL0_INT_STAT     (0x00U)
#define VPDMA_INT_CHANNEL0_INT_MASK     (0x04U)
#define VPDMA_INT_CHANNEL1_INT_STAT     (0x08U)
#define VPDMA_INT_CHANNEL1_INT_MASK     (0x0CU)
#define VPDMA_INT_CHANNEL2_INT_STAT     (0x10U)
#define VPDMA_INT_CHANNEL2_INT_MASK     (0x14U)
#define VPDMA_INT_CHANNEL3_INT_STAT     (0x18U)
#define VPDMA_INT_CHANNEL3_INT_MASK     (0x1CU)
#define VPDMA_INT_CHANNEL4_INT_STAT     (0x20U)
#define VPDMA_INT_CHANNEL4_INT_MASK     (0x24U)
#define VPDMA_INT_CHANNEL5_INT_STAT     (0x28U)
#define VPDMA_INT_CHANNEL5_INT_MASK     (0x2CU)
#define VPDMA_INT_CHANNEL6_INT_STAT     (0x30U)
#define VPDMA_INT_CHANNEL6_INT_MASK     (0x34U)
#define VPDMA_INT_CLIENT0_INT_STAT      (0x38U)
#define VPDMA_INT_CLIENT0_INT_MASK      (0x3CU)
#define VPDMA_INT_CLIENT1_INT_STAT      (0x40U)
#define VPDMA_INT_CLIENT1_INT_MASK      (0x44U)
#define VPDMA_INT_LIST0_INT_STAT        (0x48U)
#define VPDMA_INT_LIST0_INT_MASK        (0x4CU)

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* End of #ifndef VPS_INTCREGOFFSET_H_ */
