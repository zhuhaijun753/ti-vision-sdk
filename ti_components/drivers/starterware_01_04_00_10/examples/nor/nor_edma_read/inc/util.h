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

#ifndef UTIL_H_
#define UTIL_H_

#include <stdio.h>
#include "gpmc.h"

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

void GPMC_Init();

void UTIL_waitLoop(uint32_t loopcnt);

uint32_t DEVICE_Delay(uint32_t delay);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif
