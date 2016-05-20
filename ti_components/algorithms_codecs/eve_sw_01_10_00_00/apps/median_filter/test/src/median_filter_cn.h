/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/* ===========================================================================*/
/*   @file   : median_filter_cn.h                                             */
/*                                                                            */
/*   @brief  : This file contains all functions calls for reference median    */
/*             filter                                                         */
/*                                                                            */
/*   @version  0.1 (Sept 2013) : Base version.                                */
/*                                                                            */
/*============================================================================*/

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <vcop.h>
#pragma RESET_MISRA ("required")

#include "xdais_types.h"
#include "imedian_filter_ti.h"

#ifndef _MEDIAN_FILTER_CN_H
#define _MEDIAN_FILTER_CN_H

void medianFilter_cn
(
    MEDIAN_FILTER_TI_CreateParams *createParams,
    uint16_t  imagePitch,
    uint8_t  *pInput,
    uint8_t  *pMedian,
    int16_t  *histo
);

#endif

