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

#if VCOP_HOST_EMULATION
    #include "vcop_vec_gradients_xy_and_magnitude_kernel.k"
    #include "vcop_canny_non_maximum_suppression_kernel.k"
    #include "vcop_doublethresholding_kernel.k"
#else
    #include "vcop_vec_gradients_xy_and_magnitude_kernel.h"
    #include "vcop_canny_non_maximum_suppression_kernel.h"
    #include "vcop_doublethresholding_kernel.h"
#endif

void vcop_vec_gradients_xy_and_magnitude_cn
(
    unsigned char  pIn[],
    short          pGradX[],
    short          pGradY[],
    short          pMag[],
    unsigned short width,
    unsigned short height
);

void IMG_conv_3x3_i8_c8s(const unsigned char    *restrict inptr,
                                  unsigned char *restrict outptr,
                                  int            x_dim,
                                  const char    *restrict mask,
                                  int            shift);


int VLIB_doublethresholding_cn(short *pInMag,
                     unsigned char   *edgeMap,
                     unsigned int    *strongEdgeListPtr,
                     int             *numStrongEdges,
                     unsigned short   width,
                     unsigned short   pitch,
                     unsigned short   height,
                     unsigned char    loThresh,
                     unsigned char    hiThresh,
                     unsigned int     pos_frm
                     );

void vcop_canny_non_maximum_suppression_cn
(
    short          pMag[],
    short          pGx[],
    short          pGy[],
    unsigned char  pEdge[],
    int            Mag2_array[],
    unsigned char  Index[],
    int            mag1_array[],
    int            mag3_array[],
    unsigned short width,
    unsigned short pitch,
    unsigned short height
);

void vcop_canny_non_maximum_suppression_1
(
    __vptr_int16   pMag,
    __vptr_int16   pGx,
    __vptr_int16   pGy,
    __vptr_int32   Mag2_array,
    __vptr_uint8   Index,
    unsigned short width,
    unsigned short pitch,
    unsigned short height
);

void vcop_canny_non_maximum_suppression_2
(
    __vptr_int16   pMag,
    __vptr_uint8   Index,
    __vptr_int32   mag1_array,
    __vptr_int32   mag3_array,
    unsigned short width,
    unsigned short pitch,
    unsigned short height
);

void vcop_canny_non_maximum_suppression_3
(
    __vptr_int16   pGx,
    __vptr_int16   pGy,
    __vptr_uint8   pEdge,
    __vptr_int32   Mag2_array,
    __vptr_int32   mag1_array,
    __vptr_int32   mag3_array,
    unsigned short width,
    unsigned short pitch,
    unsigned short height
);

int VLIB_edgeRelaxation_cn(
                     unsigned char *edgeMap,
                     unsigned int  *restrict strongEdgeListPtr,
                     int           *numStrongEdges,
                     unsigned short width);

void vcop_doublethresholding_1(short *pInMag,
                     unsigned char   *edgeMap,
                     unsigned short   width,
                     unsigned short   pitch,
                     unsigned short   height,
                     unsigned char    loThresh,
                     unsigned char    hiThresh,
                     unsigned int     pos_frm
                     );

int vcop_doublethresholding_2(
                     unsigned char *edgeMap,
                     unsigned int  *strongEdgeListPtr,
                     int           *numStrongEdges,
                     unsigned short width,
                     unsigned short pitch,
                     unsigned short height,
                     unsigned int   pos_frm
                     );
