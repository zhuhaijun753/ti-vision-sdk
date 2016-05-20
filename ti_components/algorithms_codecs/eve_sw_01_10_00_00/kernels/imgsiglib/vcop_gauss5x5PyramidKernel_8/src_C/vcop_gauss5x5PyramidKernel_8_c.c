/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_gauss5x5PyramidKernel_8_kernel_cn                               */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_gauss5x5PyramidKernel_8_horiz                              */
/*     (                                                                    */
/*         unsigned char  pIn[],                                            */
/*         unsigned char  pB[],                                             */
/*         unsigned short width,                                            */
/*         unsigned short pitch,                                            */
/*         unsigned short height                                            */
/*     )                                                                    */
/*                                                                          */
/*     void vcop_gauss5x5PyramidKernel_8_vert                               */
/*     (                                                                    */
/*         unsigned char  pB[],                                             */
/*         unsigned short width,                                            */
/*         unsigned short pitch,                                            */
/*         unsigned short height,                                           */
/*         unsigned char  pOut[]                                            */
/*     )                                                                    */
/*                                                                          */
/*     pIn      :  8-bit input image                                        */
/*     pB       :  Intermediate buffer                                      */
/*     inCols   :  Number of coluns in the image                            */
/*     inRows   :  Number of rows in the image                              */
/*     pOut     :  8-bit output image                                       */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts an 8-bit input image and outputs three  */
/*     levels of Gaussian pyramid in the pOut array.                        */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*     The number of columns in the input image should be a multiple of 8.  */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#define ELEMSZ          sizeof(*pB)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)

void vcop_gauss5x5PyramidKernel_8_horiz_c
(
    unsigned char   pIn[],
    unsigned char   pOut[],
    unsigned short  width,
    unsigned short  height,
    unsigned short  inPitch,
    unsigned short  outPitch
)
{
	int i,j;
	unsigned char R1, R2, R3, R4, R5;
	unsigned short R;

    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
	        R1 = pIn[i*inPitch + j];
	        R2 = pIn[i*inPitch + j + 1];
	        R3 = pIn[i*inPitch + j + 2];
	        R4 = pIn[i*inPitch + j + 3];
	        R5 = pIn[i*inPitch + j + 4];

		    R =  R1 + R2*4 + R3*6 + R4*4 + R5;

		    pOut[i*outPitch + j] = R >> 4;
        }
    }
}

/* This function includes downsampling of the output in both horizontal and vertical direction */
void vcop_gauss5x5PyramidKernel_8_vert_c
(
    unsigned char   pIn[],
    unsigned char   pOut[],
    unsigned short  width,
    unsigned short  height,
    unsigned short  inPitch,
    unsigned short  outPitch
)
{

	int i,j;
	unsigned char R1, R2, R3, R4, R5;
	unsigned short R;

    for(i = 0; i < height/2; i++)
    {
        for(j = 0; j < width/2; j++)
        {

	        R1 = pIn[2*i*inPitch+2*j];
	        R2 = pIn[2*i*inPitch+2*j+inPitch];
	        R3 = pIn[2*i*inPitch+2*j+2*inPitch];
	        R4 = pIn[2*i*inPitch+2*j+3*inPitch];
	        R5 = pIn[2*i*inPitch+2*j+4*inPitch];

		    R =  R1 + R2*4 + R3*6 + R4*4 + R5;

	        pOut[i*outPitch + j] = R >> 4;

        }
    }
}

/* ======================================================================== */
/*  End of file: vcop_gauss5x5PyramidKernel_8_c.c                           */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

