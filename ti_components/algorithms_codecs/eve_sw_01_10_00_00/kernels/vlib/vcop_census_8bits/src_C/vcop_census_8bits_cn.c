/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include "stdint.h"
#include "vcop_census_8bits_cn.h"

void vcop_census_8bits_cn
(
        uint8_t *input,
        uint8_t *output,
        uint8_t winWidth, /* windWidth * winHeight msut be > 8 */
        uint8_t winHeight,
        uint8_t winHorzStep,
        uint8_t winVertStep,
        uint16_t computeWidth,
        uint16_t computeHeight,
        uint16_t inStride,
        uint16_t outStride /* in bytes */
)
{
    uint16_t i, j, k, l, j_in;
    uint8_t numBytesPerCensus=(_CENSUS_WIN_SIZE(winWidth, winHeight, winHorzStep, winVertStep) + 7) / 8;

    for(i=0; i<computeHeight; i++){
        j=0;
        j_in=0;
        while (j<computeWidth*numBytesPerCensus) {
            uint8_t census = 0;
            uint8_t count=0;
            uint8_t center_pixel = input[(i+winHeight/2)*inStride+j_in+winWidth/2];
            
            for(k=0; k<winHeight; k+= winVertStep){
                for(l=0; l<winWidth; l+= winHorzStep){
                    if (count== 8) { /* If count reaches 8 then we write out what has been packed into 8 bits so far*/
                        output[i*outStride+j]= census;
                        census= 0;
                        count= 0;
                        j++;
                    }   
                    if _IS_NOT_CENTER(l, k, winWidth, winHeight) {
                        census = census | ((CENSUS_COMPARE(input[(i+k)*inStride+j_in+l], center_pixel)?1:0)<<count);
                        count++;
                    }
                }
            }
            output[i*outStride+j] = census;
            j++;
            j_in++;
        }
    }
}
