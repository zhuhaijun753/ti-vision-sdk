/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <vcop.h>
#pragma RESET_MISRA ("required")

#include "evealgframework.h"
#include "evelib_memcopy_dma_2d.h"


#define IMAGE_WIDTH         1280U
#define IMAGE_HEIGHT        736U

#define BUFFER_WIDTH        (IMAGE_WIDTH+4) /* can be heigher */
#define BUFFER_HEIGHT       (IMAGE_HEIGHT+4) /* can be heigher */


uint8_t     gTestInput[BUFFER_WIDTH*BUFFER_HEIGHT] = {0U};
uint8_t     gTestOutput[BUFFER_WIDTH*BUFFER_HEIGHT] = {0U};

static void  passThroughBufferInit(void);

int main(void)
{
    int t0=0, t1=0, tdiff=0, tmcpfX16=0, tmcpsX16=0, tpixX16 = 0;
    int numSlices = 1;
    char *status = NULL;
    int fail = 0;

    /* initialize input buffers */
    passThroughBufferInit();
    vcop_malloc(VCOP_WMEM, 0); /* to disable compiler warning */

    _tsc_start();
    t0 = _tsc_gettime();

    EVELIB_memcopyDMA2D(gTestInput,
                       gTestOutput,
                       IMAGE_WIDTH,
                       IMAGE_HEIGHT,
                       BUFFER_WIDTH,
                       BUFFER_WIDTH);
    t1 = _tsc_gettime();

    fail = 0;
    fail = memcmp(gTestInput, gTestOutput, BUFFER_WIDTH*BUFFER_HEIGHT);

    tdiff = (t1-t0)*2;
    tmcpfX16 = tdiff*16 / 1000000;
    tmcpsX16 = tmcpfX16*30;
    tpixX16  = tdiff * 16 / (IMAGE_WIDTH*IMAGE_HEIGHT);

    status = fail? "FAILED" : "PASSED";

#ifdef EN_ZEBU_TEST
        TEST_PRINTF("\n%s %s %s %s %s %s %s %s %s %s %s\n", \
                "Algorithm", "Status", "Width", "Height", "NumSlices", "VCOPCycPerFr", "MegaCycPerFr", \
                "MegaCycPerSec(30Fr)", "CycPerPix", "TimePerFr(MSec)", "Comments");
        TEST_PRINTF("\n%s %s %d %d %d %d %f %f %f %f    %s\n", "EVELIB Image Copy", status, IMAGE_WIDTH, IMAGE_HEIGHT,
            numSlices, tdiff, (tmcpfX16/16.0), (tmcpsX16/16.0), (tpixX16/16.0), (tmcpfX16*1000/16.0/500.0),"");
#else
        TEST_PRINTF("\n%-20s %10s %10s %10s %10s %15s %15s %20s %10s %16s    %s", \
                "Algorithm", "Status", "Width", "Height", "NumSlices", "VCOPCycPerFr", "MegaCycPerFr", \
                "MegaCycPerSec(30Fr)", "CycPerPix", "TimePerFr(MSec)", "Comments");
        TEST_PRINTF("\n%-20s %10s %10d %10d %10d %15d %15.2f %20.2f %10.2f %16.2f    %s\n", "EVELIB Image Copy", status, IMAGE_WIDTH, IMAGE_HEIGHT,
            numSlices, tdiff, (tmcpfX16/16.0), (tmcpsX16/16.0), (tpixX16/16.0), (tmcpfX16*1000/16.0/500.0),"");

        TEST_PRINTF("\n%-20s %25s %20s %20s %20s %20s %20s    %s", \
                "Algorithm", "Scratch(.far/.fardata)", "Const(.const)", "Program(.text)", "DDRTrfrIn", "DDRTrfrOut", "DDRTrfrTot", "Comments");
        TEST_PRINTF("\n%-20s %25d %20d %20d %20.1f %20.1f %20.1f    %s\n", "EVELIB Image Copy", 0, 1, 18, 0.0, 0.0, 1.0, "");
#endif

       fflush(stdout);
    return 0;
}

static void  passThroughBufferInit(void)
{
    int i = 0, j = 0;
    uint8_t *rowStart = 0;
    uint8_t *frameStart = gTestInput;

    for(j=0; j<IMAGE_HEIGHT; j++)
    {
        rowStart = &frameStart[BUFFER_WIDTH*j];
        for(i=0; i<IMAGE_WIDTH; i++)
        {
            rowStart[i]  = rand() & 0xFF;
        }
    }
}

