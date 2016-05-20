/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|         Copyright (c) 2007-2012 Texas Instruments Incorporated           |**
**|                        ALL RIGHTS RESERVED                               |**
**|                                                                          |**
**| Permission to use, copy, modify, or distribute this software,            |**
**| whether in part or in whole, for any purpose is forbidden without        |**
**| a signed licensing agreement and NDA from Texas Instruments              |**
**| Incorporated (TI).                                                       |**
**|                                                                          |**
**| TI makes no representation or warranties with respect to the             |**
**| performance of this computer program, and specifically disclaims         |**
**| any responsibility for any damages, special or consequential,            |**
**| connected with the use of this program.                                  |**
**|                                                                          |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include "vcop.h"
#include "Canny_prototypes.h"

#include "test_profile.h"

#define WIDTH 64
#define HEIGHT 64


#pragma DATA_SECTION(gaussian_3x3, "Cdata");
char gaussian_3x3[9] = { 1, 2, 1,    // Gauss mask
                      2, 4, 2,
                      1, 2, 1  };

#pragma DATA_SECTION(pregs, "Cdata");
unsigned short pregs[64*8];

#pragma DATA_SECTION(pregs_offset, "Cdata");
unsigned short pregs_offset[8];

#pragma DATA_SECTION(pBufGradX, "Adata");
short  pBufGradX[WIDTH*HEIGHT];
#pragma DATA_SECTION(pBufGradY, "Adata");
short  pBufGradY[WIDTH*HEIGHT];
#pragma DATA_SECTION(pBufMag, "Bdata");
short  pBufMag[WIDTH*HEIGHT];
#pragma DATA_SECTION(Index, "Bdata");
unsigned char Index[WIDTH*HEIGHT];
#pragma DATA_SECTION(pBufOut, "Bdata");
unsigned char pBufOut[WIDTH*HEIGHT];

#pragma DATA_SECTION(Mag2_array, "Cdata");
int Mag2_array[WIDTH*HEIGHT];
#pragma DATA_SECTION(mag1_array, "Vdata");
int mag1_array[WIDTH*HEIGHT];
#pragma DATA_SECTION(mag3_array, "Udata");
int mag3_array[WIDTH*HEIGHT];

extern unsigned char canny_ref[];
extern unsigned char gTITexasLogo[];

extern int vcop_edgeRelaxation_cn(
                     unsigned char *edgeMap,
                     unsigned int * restrict strongEdgeListPtr,
                     int *numStrongEdges,
                     unsigned short width);

void main()
{

    unsigned int i, j;
    unsigned int error;
    unsigned short numparms1, numparms2, numparms3,numparms4;
#ifdef REPORT
    FILE* fpReport = fopen("../../../report.csv","a+");
#ifdef SCTM
    unsigned int sctm_t1, sctm_t2, exec_diff;
    unsigned int overflow;
#endif
#endif
    int numItems = 0;

#ifdef CONSOLE
    printf("\nvcop_canny_applet:\n");
#endif
    
    VCOP_SET_MEM_VIEW(FLAT_MEM_VIEW);

    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                  IBUFHA_SYST, IBUFLA_SYST);

    for(j = 0; j < HEIGHT-2; j++)
    {
        IMG_conv_3x3_i8_c8s(gTITexasLogo+j*WIDTH,
            pBufOut+WIDTH+1+j*WIDTH,
            WIDTH,
            gaussian_3x3,
            4);
    }

    numparms1 = vcop_vec_gradients_xy_and_magnitude_init (pBufOut + WIDTH*1 + 1,
            pBufGradX+ WIDTH*2 + 2,
            pBufGradY+ WIDTH*2 + 2,
            pBufMag+ WIDTH*2 + 2,
            WIDTH,
            64-4,
            pregs);

    numparms2 = numparms1;
    numparms2 +=           vcop_canny_non_maximum_suppression_1_k_init(pBufMag+ WIDTH*3 + 3,
        pBufGradX+ WIDTH*3 + 3,
        pBufGradY+ WIDTH*3 + 3,
        Mag2_array,
        Index,
        WIDTH-6,
        WIDTH,
        HEIGHT-6,
        pregs+numparms1);

    numparms3 = numparms2;
    numparms3 += vcop_canny_non_maximum_suppression_2_k_init(pBufMag+ WIDTH*3 + 3,
        Index,
        mag1_array,
        mag3_array,
        WIDTH-6,
        WIDTH,
        HEIGHT-6,
        pregs+numparms2);

    numparms4 = numparms3;
    numparms4 +=  vcop_canny_non_maximum_suppression_3_k_init(
        pBufGradX+ WIDTH*3 + 3,
        pBufGradY+ WIDTH*3 + 3,
        pBufOut + WIDTH*3 + 3,
        Mag2_array,
        mag1_array,
        mag3_array,
        WIDTH-6,
        WIDTH,
        HEIGHT-6,
        pregs+numparms3);

    vcop_doublethresholding_init(
                             pBufMag,
                             pBufOut,
                             WIDTH-6,
                             WIDTH,
                             HEIGHT-6,
                             2,
                             10,
                             pBufOut,
                             pregs+numparms4
                             );

    VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                       IBUFHA_VCOP, IBUFLA_VCOP);

#ifdef REPORT
#ifdef SCTM
    EVE_SCTM_Enable(CTM);
    EVE_SCTM_CounterConfig(CTM, SCTM_Counter_0, VCOP_BUSY, SCTM_DURATION);
    EVE_SCTM_CounterTimerEnable(CTM, SCTM_Counter_0);
    sctm_t1 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
#endif
#endif

    vcop_vec_gradients_xy_and_magnitude_vloops(pregs);
    vcop_canny_non_maximum_suppression_1_k_vloops(pregs+numparms1);
    vcop_canny_non_maximum_suppression_2_k_vloops(pregs+numparms2);
    vcop_canny_non_maximum_suppression_3_k_vloops(pregs+numparms3);
    vcop_doublethresholding_vloops(pregs+numparms4);

    _vcop_vloop_done();

#ifdef REPORT
#ifdef SCTM
    sctm_t2 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
    overflow= EVE_SCTM_OverflowCheck(CTM,SCTM_Counter_0);
    assert(overflow!=1);

    exec_diff = sctm_t2 - sctm_t1;
    EVE_SCTM_CounterTimerDisable(CTM, SCTM_Counter_0);
#endif
#endif

    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                       IBUFHA_SYST, IBUFLA_SYST);

    vcop_doublethresholding_2(
                     pBufOut,
                     (unsigned int *) pBufGradX,
                     &numItems,
                     WIDTH-6,
                     WIDTH,
                     HEIGHT-6,
                     0
                     );

    vcop_edgeRelaxation_cn(pBufOut,
                     (unsigned int *) pBufGradX,
                     &numItems,
                     WIDTH);

    /////////////////////////////////////////////////////////////////////////////
    // Clean-Up: Set all the remaining 'possible edges' to non-edges
    /////////////////////////////////////////////////////////////////////////////
    for (i=0; i < WIDTH*HEIGHT; i++)
        pBufOut[i] = (pBufOut[i] >> 7) * 255;
    //pgmwrite("Canny_frame.pgm", WIDTH,HEIGHT,pBufOut,"test",sizeof(char));

    error = memcmp(pBufOut, canny_ref, 64*64);

#ifdef REPORT
    printf("vcop_canny_applet");
    fprintf(fpReport,"vcop_canny_applet,");
    fprintf(fpReport,"%d,",WIDTH);
    fprintf(fpReport,"%d,",HEIGHT);
    fprintf(fpReport,"%d,",WIDTH);
    fprintf(fpReport,"%d,",HEIGHT);
    fprintf(fpReport,"1,");
#endif

    if(error) {
#ifdef CONSOLE
        printf("FAIL, error=%d\n",error);
#endif

#ifdef REPORT
        fprintf(fpReport,"FAIL,");
#endif
    }
    else {
#ifdef CONSOLE
        printf("PASS\n");
#endif

#ifdef REPORT
        fprintf(fpReport,"PASS,");
#endif
    }

#ifdef REPORT
#ifdef SCTM
    fprintf(fpReport,"%d\n",exec_diff);
#endif
#endif

#ifdef REPORT
    fclose(fpReport);
#endif

    return;
}
