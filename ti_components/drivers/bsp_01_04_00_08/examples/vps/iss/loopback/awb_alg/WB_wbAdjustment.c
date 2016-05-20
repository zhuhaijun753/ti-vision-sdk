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

int WB_wbAdjustment(Image *imgPtr, lookUpTable *LUT) {
    int test;

    test = IDH_remapFromLUT(imgPtr, 'r', LUT);
    if(test != 1)
    {
        return test;
    }
    test = IDH_remapFromLUT(imgPtr, 'g', LUT+1);
    if(test != 1)
    {
        return test;
    }
    test = IDH_remapFromLUT(imgPtr, 'b', LUT+2);
    if(test != 1)
    {
        return test;
    }
    else
    {
        return 1;
    }
}

