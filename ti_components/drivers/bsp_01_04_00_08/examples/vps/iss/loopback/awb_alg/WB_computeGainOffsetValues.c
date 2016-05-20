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

const float UNITYGAIN[3] = {1, 1, 1.01};          //Unity gain factors for NO AWB condition in low CCT ranges
const float UNITYOFFSET[3] = {0, 0, 0};           //Offset values for NO AWB condition in low CCT ranges
const float MINGAIN[3] = {0.5, 1, 0.5};           // Minimum values for rgb gainFactors
const float MAXGAIN[3] = {1.71, 1, 1.93};         // Maximum values for rgb gainFactors

const float TARGETCCT = 6500;                     // Datlight temperature

const bool  AWBFORLOWCCT = 1;                     //Enable AWB for low CCT temperatures (Default : Enable (1))
const float AWBFORLOWCCT_CCTTHRESHOLD     = 5000; /*CCT above which actual awb params are used, blended awb params are used for range [ AWBFORLOWCCT_CCTTHRESHOLD - AWBFORLOWCCT_TRANSITION_WIDTH, AWBFORLOWCCT_CCTTHRESHOLD] */
const float AWBFORLOWCCT_TRANSITION_WIDTH = 1500; /*Meaning no wb correctio performed below CCT (AWBFORLOWCCT_CCTTHRESHOLD - AWBFORLOWCCT_TRANSITION_WIDTH)*/
const int   SATURATION_THRESHOLD          = 250;  /*Gray pixel value above which it is considered to be saturated.  Value of 200 is set keeping in mind that the image data is not gamma corrcted*/

const bool  OFFSETENABLE = 0;                     //Enable offset (Default : Disable (0))
const float OFFSET_COMPUTATION_PARAMETER = 250;   /* Use of smaller value leads to slightly bluish tinge on the AWBed picyure*/

void WB_computeGainOffsetValues(WBParams *cP) {
    int   i;
    float temperatureDifference, blendingFactor;
    float temp1;

    cP->gainOffset.gainFactors[0] = (float)(cP->illum.RGB[1]) /
                                    (float)(cP->illum.RGB[0]);
    cP->gainOffset.gainFactors[1] = 1;
    cP->gainOffset.gainFactors[2] = (float)(cP->illum.RGB[1]) /
                                    (float)(cP->illum.RGB[2]);

    if(OFFSETENABLE == 1)
    {
        temp1 =
            (cP->illum.temperature - TARGETCCT) / OFFSET_COMPUTATION_PARAMETER;
        temp1 = (temp1 > 1) ? temp1 : 1;
        cP->gainOffset.offsets[0] = temp1 * (cP->gainOffset.gainFactors[0] -1);

        cP->gainOffset.offsets[1] = 0;

        temp1 =
            (TARGETCCT - cP->illum.temperature) / OFFSET_COMPUTATION_PARAMETER;
        temp1 = (temp1 > 1) ? temp1 : 1;
        cP->gainOffset.offsets[2] = temp1 * (cP->gainOffset.gainFactors[2] -1);
    }
    else
    {
        cP->gainOffset.offsets[0] = 0;
        cP->gainOffset.offsets[1] = 0;
        cP->gainOffset.offsets[2] = 0;
    }

    if(AWBFORLOWCCT == 0)
    {
        if(cP->illum.temperature < AWBFORLOWCCT_CCTTHRESHOLD)
        {
            temperatureDifference = AWBFORLOWCCT_CCTTHRESHOLD -
                                    cP->illum.temperature;
            if(temperatureDifference > AWBFORLOWCCT_TRANSITION_WIDTH)
            {
                for(i = 0; i < 3; i++) {
                    cP->gainOffset.gainFactors[i] = UNITYGAIN[i];
                    cP->gainOffset.offsets[i]     = UNITYOFFSET[i];
                }
            }
            else
            {
                blendingFactor =  temperatureDifference /
                                 AWBFORLOWCCT_TRANSITION_WIDTH;
                for(i = 0; i < 3; i++) {
                    cP->gainOffset.gainFactors[i] =
                        (1 -
                         blendingFactor) * cP->gainOffset.gainFactors[i] +
                        blendingFactor * UNITYGAIN[i];
                    cP->gainOffset.offsets[i] =
                        (1 -
                         blendingFactor) * cP->gainOffset.offsets[i] +
                        blendingFactor * UNITYOFFSET[i];
                }
            }
        }
    }
}

