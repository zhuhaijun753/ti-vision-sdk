/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "vcop_bin_image_to_list_cn.h"

void vcop_bin_image_to_list_cn
(
    uint8_t  *img,
    uint32_t *upperLeftXY,
    uint32_t *outXY_list,
    uint32_t *list_size,
    uint16_t  width,
    uint16_t  height,
    uint16_t  stride,
    uint16_t  outputQformat,
    uint8_t   xyOrder
)
{
    int i, j, k;
    char pix;
    int n = 0;
    int x, y;

    for(i = 0; i < height; i++) {
        for(j = 0; j < (width+7)/8; j++) {

            for(k = 0; k < 8; k++) {
                pix = ((img[i*stride/8 + j])>>k)&0x1;

                if(pix != 0) {
                    x = (8*j + k);
                    y = i;
                    if ( xyOrder )
                    {
                      outXY_list[n] = ((( x << outputQformat)<<16) + ( y << outputQformat )) + *upperLeftXY;
                    }
                    else
                    {
                      outXY_list[n] = ((( y << outputQformat)<<16) + ( x << outputQformat )) + *upperLeftXY;
                    }
                    n++;
                }
            }
        }
    }

    list_size[0] = n;
    *upperLeftXY += 2*width;
}
