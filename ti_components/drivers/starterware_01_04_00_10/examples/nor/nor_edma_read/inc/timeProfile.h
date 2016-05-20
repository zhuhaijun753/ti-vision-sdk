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
#ifndef TIMEPROFILE_H_
#define TIMEPROFILE_H_

#include "stdint.h"
#include <stdio.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

extern uint32_t ARM_CCNT_Enable();
extern uint32_t ARM_CCNT_Read();

#define enableticks ARM_CCNT_Enable()
#define getticks ARM_CCNT_Read()
#define ticks(u, v)  (v - u)

static inline uint32_t printticks(uint32_t val, char *name)
{
    uint32_t coreFreq;
    coreFreq = 600000000;

    float    valS  = ((float) val) / coreFreq;
    float    valMs = ((float) val) / (coreFreq / 1000);

    UARTPuts("\n Core frequency = ", -1);
    UARTPutNum(coreFreq / 1000000);
    UARTPuts(" MHz", -1);

    UARTPuts(name, -1);
    UARTPuts("\nticks    =  ", -1);
    UARTPutNum(val);

    UARTPuts("\ntime in ms =  ", -1);
    UARTPutNum(valMs);

    UARTPuts("\ntime in sec =  ", -1);
    UARTPutNum(valS);

    /*printf("\n Core frequency = %d MHz", coreFreq / 1000000);
     * printf("\n %s in ticks    = %d ticks", name, val);
     * printf("\n %s in ms       = %f ms", name, valMs);
     * printf("\n %s in s        = %f s", name, valS);
     * printf("\n");*/

    return valMs;
}

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif
