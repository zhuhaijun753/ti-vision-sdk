/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "evealgframework.h"
#include "evelib_fir_filter_2d_scatter_gather.h"
#include "..\imgsiglib\Filter\inc\vcop_filter_cn.h"

#define IMAGE_WIDTH  1280
#define IMAGE_HEIGHT 736
#define COMPARE_REFERENCE

uint8_t input[IMAGE_WIDTH*IMAGE_HEIGHT];
uint8_t output[IMAGE_WIDTH*IMAGE_HEIGHT];
uint8_t refOutput[IMAGE_WIDTH*IMAGE_HEIGHT];

uint8_t coeff[9] = {28, 28, 28,
                    28, 29, 28,
                    28, 28, 28};
uint8_t rndShift = 8;

int main()
{
    int i=0, j=0, fail = 0;
    int t0=0, t1=0, tdiff=0, tmcpfX16=0, tmcpsX16=0, tpixX16 = 0;
    int numSlices = 1;
    char *status = "UNKNOWN";

    srand(1);
    for(i=0; i<IMAGE_WIDTH*IMAGE_HEIGHT; i++)
    {
       input[i] = rand() % 256;
    }
    memset(output, 0, sizeof(output));
    memset(refOutput, 0, sizeof(refOutput));

    _tsc_start();
    t0 = _tsc_gettime();

    EVELIB_firFilter2D_scatterGather(input, IMAGE_WIDTH, IMAGE_HEIGHT, IMAGE_WIDTH, output, IMAGE_WIDTH, IMAGE_HEIGHT, IMAGE_WIDTH, (char*)coeff, 3, 3, 1, 1, rndShift);

    t1 = _tsc_gettime();

#ifdef COMPARE_REFERENCE
    filter_uchar_cn(input, (char*)coeff, refOutput, IMAGE_WIDTH, 3, 3, IMAGE_WIDTH, IMAGE_HEIGHT, IMAGE_WIDTH, 1, 1, 2, 8);


    fail = 0;
    for(j=0; j<IMAGE_HEIGHT; j++)
    {
        for(i=0; i<IMAGE_WIDTH; i++)
        {
           if(output[j*IMAGE_WIDTH+i] != refOutput[j*IMAGE_WIDTH+i])
           {
             fail = 1;
             /* printf("failed at %d %d\n", i, j); */
           }
        }
    }

    status = fail? "FAILED" : "PASSED";
#endif

    tdiff = (t1-t0)*2;
    tmcpfX16 = tdiff*16 / 1000000;
    tmcpsX16 = tmcpfX16*30;
    tpixX16  = tdiff * 16 / (IMAGE_WIDTH*IMAGE_HEIGHT);

#ifdef EN_ZEBU_TEST
    TEST_PRINTF("\n%s %s %s %s %s %s %s %s %s %s %s\n", \
            "Algorithm", "Status", "Width", "Height", "NumSlices", "VCOPCycPerFr", "MegaCycPerFr", \
            "MegaCycPerSec(30Fr)", "CycPerPix", "TimePerFr(MSec)", "Comments");
    TEST_PRINTF("\n%s %s %s\n", "EVELIB Filter2D(SG)", status, "");
#else
    TEST_PRINTF("\n%-20s %10s %10s %10s %10s %15s %15s %20s %10s %16s    %s", \
            "Algorithm", "Status", "Width", "Height", "NumSlices", "VCOPCycPerFr", "MegaCycPerFr", \
            "MegaCycPerSec(30Fr)", "CycPerPix", "TimePerFr(MSec)", "Comments");
    TEST_PRINTF("\n%-20s %10s %10d %10d %10d %15d %15.2f %20.2f %10.2f %16.2f    %s\n", "EVELIB Filter2D(SG)", status, IMAGE_WIDTH, IMAGE_HEIGHT,
        numSlices, tdiff, (tmcpfX16/16.0), (tmcpsX16/16.0), (tpixX16/16.0), (tmcpfX16*1000/16.0/500.0), "");

    TEST_PRINTF("\n%-20s %25s %20s %20s %20s %20s %20s    %s", \
            "Algorithm", "Scratch(.far/.fardata)", "Const(.const)", "Program(.text)", "DDRTrfrIn", "DDRTrfrOut", "DDRTrfrTot", "Comments");
    TEST_PRINTF("\n%-20s %25d %20d %20d %20.1f %20.1f %20.1f    %s\n","EVELIB Filter2D(SG)", 0, 1, 27, 1.0, 1.0, 2.0, "");
#endif

    return fail;
}

