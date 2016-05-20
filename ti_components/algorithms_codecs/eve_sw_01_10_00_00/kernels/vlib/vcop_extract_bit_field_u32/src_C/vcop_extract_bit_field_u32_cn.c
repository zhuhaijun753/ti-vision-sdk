/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "vcop_extract_bit_field_u32_cn.h"

void vcop_extract_bit_field_u32_cn
(
    uint32_t *inArray,
    uint16_t  length,
    uint32_t  bit_mask,
    uint8_t   shift,
    uint8_t  *outList
)
{
    int32_t i, bit_field;

    for(i = 0; i < length; i++) {
        bit_field = (inArray[i] & bit_mask);
        outList[i] = bit_field >> shift;
    }
}

