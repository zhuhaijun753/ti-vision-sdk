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

#ifndef DEBUG_H_
#define DEBUG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "nor.h"
extern Nor_InitPrms_t gNor_InitPrms;

uint32_t DEBUG_printString(const char *s);
void DEBUG_ConvertHexToString(uint32_t hexValue, char *stringValue,
                              int32_t maxLimitCount);

#ifdef __cplusplus
}
#endif

#endif
