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

# include "inc/white_balance.h"

static float MINGAIN[3] = {1, 1, 1};     // Minimum values for rgb gainFactors
static float MAXGAIN[3] = {2.71, 1, 2.93};   // Maximum values for rgb gainFactors

void WB_clipCorrectionParams(WBParams *cP) {
    int i;
    for(i = 0; i < 3; i++) {
        if(cP->gainOffset.gainFactors[i] < MINGAIN[i])
        {
            cP->gainOffset.gainFactors[i] = MINGAIN[i];
        }
        else
        {
            if(cP->gainOffset.gainFactors[i] > MAXGAIN[i])
            {
                cP->gainOffset.gainFactors[i] = MAXGAIN[i];
            }
        }
    }
}

