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

int WB_estimateWbParams(Image *imgPtr, float percPix, WBParams *cP) {
    int flag;

    flag = WB_estimateIlluminant(imgPtr, percPix, &cP->illum);

    if(flag == 0)
    {
        return 0;
    }

    WB_computeGainOffsetValues(cP);

    WB_clipCorrectionParams(cP);

    return 1;
}

