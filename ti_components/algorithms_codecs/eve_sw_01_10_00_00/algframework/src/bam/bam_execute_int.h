/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


/**
 *  @file       bam_construct.c
 *
 *  @brief      This file defines internal structures and functions for BAM Graph execution
 */

#ifndef BAM_EXECUTE_INT_H
#define BAM_EXECUTE_INT_H

#pragma CHECK_MISRA ("none")
#include <stdint.h>
#include <vcop.h>
#pragma RESET_MISRA ("required")

#include "bam_execute.h"
#include "bam_construct_int.h"

#if 0
#include "bam_kernel_database_int.h"

#define PROFILING

#define BAM_EN_MULTIPLE_DMANODE_SUPPORT
#endif

typedef struct {
    BAM_KernelFunc kernelCompute;
    BAM_KernelFunc kernelWaitSource;
    BAM_KernelFunc kernelWaitSink;
    void *context[2];
    uint8_t *pArgs[2];
    uint16_t argsAndPrivContextSize;
    void *kernelContextSource;
    void *kernelContextSink;
    uint8_t pingpongFlag; /** ping pong flag to determine which image buffer to switch to before calling kernelCompute, PING->IMGBUFA, PONG->IMGBUFB */
} BAM_ARP32KernelComputeContext;

BAM_Status BAM_ARP32_computeWrapper(void *context);

BAM_Status BAM_dummyKernelFunc(void *context);

BAM_Status BAM_controlGraphNode(const BAM_GraphDef *graphDef, uint8_t nodeIndex, void *ctlArg);

/* Execute every kernel's init instance functions, which will initialize the internal memory records */
int32_t BAM_initGraphInstance(const BAM_GraphHandle graphHandle);

#endif
