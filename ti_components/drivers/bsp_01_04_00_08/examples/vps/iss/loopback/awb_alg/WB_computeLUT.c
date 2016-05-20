/************************************************************************************//**
* TI ISP Library Reference Code
* This library is a software module developed for simulation of vision and ISP
* algorithms ported on TI's embedded platforms
* Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
* ALL RIGHTS RESERVED
* @author       Hrushikesh Garud (A0393878)
* @version      1.0
*
****************************************************************************************/

# include <stdio.h>
# include <math.h>
//# include <memory.h>
# include <stdlib.h>

# include "inc/Image_Data_Handling.h"
# include "inc/white_balance.h"

void WB_computeLUT(WB_GainOffset *gainOffset, lookUpTable *LUT)
{
    int   i, j;
    float temp[3];
    for(i = 0; i <= 255; i++) {
        for(j = 0; j < 3; j++) {
            temp[j] = (float)i * gainOffset->gainFactors[j] +
                      gainOffset->offsets[j];
            temp[j] = (temp[j] < 0) ? 0 : temp[j];
            temp[j] = (temp[j] > 255) ? 255 : temp[j];
            (LUT + j)->table[i] = (int)temp[j];
        }
    }
}

