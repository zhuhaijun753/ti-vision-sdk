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
 *  \file  hw_intc.h
 *
 *  \brief This file contains the MACROS definitions used by interrupt
 **controller module.
 */

#ifndef HW_INTC_H_
#define HW_INTC_H_

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/************/

#define INTC_MPU_DIST_BASE       (0x48211000)
#define INTC_MPU_CPU_IF_BASE     (0x48212000)

#define INTC_MPU_CPU_IF_IAR_OFFSET (0x000C)
#define INTC_MPU_CPU_IF_EOI_OFFSET (0x0010)

#define IAR_INT_ID_MASK (0x000000FF)
#define PPI_SGI_MASK    (0x20)

#define ADDR_IAR        (INTC_MPU_CPU_IF_BASE + INTC_MPU_CPU_IF_IAR_OFFSET)
#define ADDR_EOI        (INTC_MPU_CPU_IF_BASE + INTC_MPU_CPU_IF_EOI_OFFSET)

#define MASK_SVC_NUM    (0xFF000000)
#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif
