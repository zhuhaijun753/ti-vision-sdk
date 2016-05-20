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
#include "evelib_edma_frame_padding.h"


#define IMAGE_WIDTH         1280U
#define IMAGE_HEIGHT        768U
#define FRAME_PAD_LEFT      2U
#define FRAME_PAD_RIGHT     2U
#define FRAME_PAD_TOP       2U
#define FRAME_PAD_BOTTOM    2U
#define PAD_ELEM_SIZE_VERT  2U
#define PAD_ELEM_SIZE_HORZ  2U

#define BUFFER_WIDTH        (IMAGE_WIDTH+(FRAME_PAD_LEFT+FRAME_PAD_RIGHT)*PAD_ELEM_SIZE_HORZ) /* can be heigher */
#define BUFFER_HEIGHT       (IMAGE_HEIGHT+(FRAME_PAD_TOP+FRAME_PAD_BOTTOM)*PAD_ELEM_SIZE_VERT) /* can be heigher */

uint8_t     gTestInput[BUFFER_WIDTH*BUFFER_HEIGHT] = {0U};

void  paddingBufferInit(void);

int main(void)
{
    int t0=0, t1=0, tdiff=0, tmcpfX16=0, tmcpsX16=0, tpixX16 = 0;
    int tdiffTop =0, tdiffBottom =0, tdiffLeft =0, tdiffRight =0;
    char *status = NULL;
    int fail = 0;
#ifdef EN_ZEBU_TEST
        TEST_PRINTF("\n%s %s %s %s %s %s %s %s %s %s %s\n", \
                "Algorithm", "Status", "Pad Width", "Pad Height", "NumSlices", "VCOPCycPerFr", "MegaCycPerFr", \
                "MegaCycPerSec(30Fr)", "CycPerPix", "TimePerFr(MSec)", "Comments");
#else
        TEST_PRINTF("\n%-20s %10s %10s %10s %10s %15s %15s %20s %10s %16s    %s", \
                "Algorithm", "Status", "Width", "Height", "NumSlices", "VCOPCycPerFr", "MegaCycPerFr", \
                "MegaCycPerSec(30Fr)", "CycPerPix", "TimePerFr(MSec)", "Comments");
#endif
    /* initialize input buffers */
    paddingBufferInit();
    vcop_malloc(VCOP_WMEM, 0); /* to disable compiler warning */

    _tsc_start();
    t0 = _tsc_gettime();
    /* pad top boarder of the frame with a height of 2. Padding element size is 2 (eg. bayer data) hence 2*2 lines will be padded*/
    EVELIB_padVertEDMA(&gTestInput[BUFFER_WIDTH * (FRAME_PAD_TOP*PAD_ELEM_SIZE_VERT)+(FRAME_PAD_LEFT*PAD_ELEM_SIZE_HORZ)],
                       &gTestInput[(FRAME_PAD_LEFT*PAD_ELEM_SIZE_HORZ)],
                       IMAGE_WIDTH,
                       FRAME_PAD_TOP,
                       BUFFER_WIDTH,
                       BUFFER_WIDTH,
                       PAD_ELEM_SIZE_VERT);
    t1 = _tsc_gettime();
    tdiffTop = (t1-t0)*2;

    t0 = _tsc_gettime();
    /* pad bottom boarder of the frame with a height of 2. Padding element size is 2 (eg. bayer data) hence 2*2 lines will be padded*/
    EVELIB_padVertEDMA(&gTestInput[BUFFER_WIDTH * (FRAME_PAD_TOP*PAD_ELEM_SIZE_VERT+IMAGE_HEIGHT-PAD_ELEM_SIZE_VERT)+(FRAME_PAD_LEFT*PAD_ELEM_SIZE_HORZ)],
                       &gTestInput[BUFFER_WIDTH * (FRAME_PAD_TOP*PAD_ELEM_SIZE_VERT+IMAGE_HEIGHT)+(FRAME_PAD_LEFT*PAD_ELEM_SIZE_HORZ)],
                       IMAGE_WIDTH,
                       FRAME_PAD_BOTTOM,
                       BUFFER_WIDTH,
                       BUFFER_WIDTH,
                       PAD_ELEM_SIZE_VERT);
    t1 = _tsc_gettime();
    tdiffBottom = (t1-t0)*2;

    t0 = _tsc_gettime();
    /* pad left boarder of the frame with a height of 2. Padding element size is 2 (eg. bayer data) hence 2*2 bytes will be padded*/
    EVELIB_padHorzEDMA(&gTestInput[(FRAME_PAD_LEFT*PAD_ELEM_SIZE_HORZ)],
                       &gTestInput[0],
                       FRAME_PAD_LEFT,
                       IMAGE_HEIGHT+((FRAME_PAD_TOP+FRAME_PAD_BOTTOM)*PAD_ELEM_SIZE_VERT),
                       BUFFER_WIDTH,
                       BUFFER_WIDTH,
                       PAD_ELEM_SIZE_HORZ);
    t1 = _tsc_gettime();
    tdiffLeft = (t1-t0)*2;

    t0 = _tsc_gettime();
    /* pad right boarder of the frame with a height of 2. Padding element size is 2 (eg. bayer data) hence 2*2 bytes will be padded*/
    EVELIB_padHorzEDMA(&gTestInput[(FRAME_PAD_LEFT*PAD_ELEM_SIZE_HORZ+IMAGE_WIDTH-PAD_ELEM_SIZE_HORZ)],
                       &gTestInput[(FRAME_PAD_LEFT*PAD_ELEM_SIZE_HORZ+IMAGE_WIDTH)],
                       FRAME_PAD_RIGHT,
                       IMAGE_HEIGHT+((FRAME_PAD_TOP+FRAME_PAD_BOTTOM)*PAD_ELEM_SIZE_VERT),
                       BUFFER_WIDTH,
                       BUFFER_WIDTH,
                       PAD_ELEM_SIZE_HORZ);
    t1 = _tsc_gettime();
    tdiffRight = (t1-t0)*2;

    status = fail? "FAILED" : "PASSED";

#ifdef EN_ZEBU_TEST
    TEST_PRINTF("\n%20s %10s %s\n", "EVELIB Padding", status, "");
#else
    tdiff = tdiffTop;
    tmcpfX16 = tdiff*16 / 1000000;
    tmcpsX16 = tmcpfX16*30;
    tpixX16  = tdiff * 16 / (IMAGE_WIDTH*FRAME_PAD_TOP*PAD_ELEM_SIZE_VERT);

    TEST_PRINTF("\n%-20s %10s %10d %10d %10d %15d %15.2f %20.2f %10.2f %16.2f    %s\n", "EVELIB Padding", status, IMAGE_WIDTH, FRAME_PAD_TOP*PAD_ELEM_SIZE_VERT,
         1, tdiff, (tmcpfX16/16.0), (tmcpsX16/16.0), (tpixX16/16.0), (tmcpfX16*1000/16.0/500.0),"TOP");

    tdiff = tdiffBottom;
    tmcpfX16 = tdiff*16 / 1000000;
    tmcpsX16 = tmcpfX16*30;
    tpixX16  = tdiff * 16 / (IMAGE_WIDTH*FRAME_PAD_BOTTOM*PAD_ELEM_SIZE_VERT);

    TEST_PRINTF("\n%-20s %10s %10d %10d %10d %15d %15.2f %20.2f %10.2f %16.2f    %s\n", "EVELIB Padding", status, IMAGE_WIDTH, FRAME_PAD_BOTTOM*PAD_ELEM_SIZE_VERT,
         1, tdiff, (tmcpfX16/16.0), (tmcpsX16/16.0), (tpixX16/16.0), (tmcpfX16*1000/16.0/500.0),"BOTTOM");

    tdiff = tdiffLeft;
    tmcpfX16 = tdiff*16 / 1000000;
    tmcpsX16 = tmcpfX16*30;
    tpixX16  = tdiff * 16 / (FRAME_PAD_LEFT*PAD_ELEM_SIZE_HORZ*IMAGE_HEIGHT);

    TEST_PRINTF("\n%-20s %10s %10d %10d %10d %15d %15.2f %20.2f %10.2f %16.2f    %s\n", "EVELIB Padding", status, FRAME_PAD_LEFT*PAD_ELEM_SIZE_HORZ, IMAGE_HEIGHT,
         1, tdiff, (tmcpfX16/16.0), (tmcpsX16/16.0), (tpixX16/16.0), (tmcpfX16*1000/16.0/500.0),"LEFT");

    tdiff = tdiffRight;
    tmcpfX16 = tdiff*16 / 1000000;
    tmcpsX16 = tmcpfX16*30;
    tpixX16  = tdiff * 16 / (FRAME_PAD_RIGHT*PAD_ELEM_SIZE_HORZ*IMAGE_HEIGHT);

    TEST_PRINTF("\n%-20s %10s %10d %10d %10d %15d %15.2f %20.2f %10.2f %16.2f    %s\n", "EVELIB Padding", status, FRAME_PAD_RIGHT*PAD_ELEM_SIZE_HORZ, IMAGE_HEIGHT,
        1, tdiff, (tmcpfX16/16.0), (tmcpsX16/16.0), (tpixX16/16.0), (tmcpfX16*1000/16.0/500.0), "RIGHT");

    TEST_PRINTF("\n%-20s %25s %20s %20s %20s %20s %20s    %s", \
            "Algorithm", "Scratch(.far/.fardata)", "Const(.const)", "Program(.text)", "DDRTrfrIn", "DDRTrfrOut", "DDRTrfrTot", "Comments");
    TEST_PRINTF("\n%-20s %25d %20d %20d %20.1f %20.1f %20.1f    %s\n","EVELIB Padding", 0, 1, 19, 0.0, 0.0, 1.0, "");
#endif

    return 0;
}

void  paddingBufferInit(void)
{
    int i = 0, j = 0;
    uint8_t *rowStart = 0;
    uint8_t *frameStart = 0;
    frameStart = &gTestInput[BUFFER_WIDTH*(PAD_ELEM_SIZE_VERT*FRAME_PAD_BOTTOM)+((PAD_ELEM_SIZE_HORZ*FRAME_PAD_LEFT))];

    for(j=0; j<IMAGE_HEIGHT; j++)
    {
        rowStart = &frameStart[BUFFER_WIDTH*j];
        for(i=0; i<IMAGE_WIDTH; i++)
        {
            rowStart[i]  = rand() & 0xFF;
        }
    }
}


