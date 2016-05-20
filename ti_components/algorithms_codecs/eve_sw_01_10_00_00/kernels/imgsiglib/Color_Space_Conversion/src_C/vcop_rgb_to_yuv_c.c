/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*-----------------------------------------------------------------*/
/* NAME : vcop_rgb_to_yuv                                          */
/*                                                                 */
/*                                                                 */
/* DESCRIPTION:                                                    */
/*                                                                 */
/* The function rgb_to_yuv, converts rgb to interleaved yuv.       */
/* by applying coefficients weighting red, blue and green,         */
/* to luma. Similarly we aplly a weighted product of red,          */
/* blue and green to U and V.                                      */
/*                                                                 */
/* A possible set of coefficients, to use is suggnsted at:         */
/* http://msdn.microsoft.com/en-us/library/ms893078.aspx           */
/*                                                                 */
/* Y = ( (  66 * R + 129 * G +  25 * B + 128) >> 8) +  16          */
/* U = ( ( -38 * R -  74 * G + 112 * B + 128) >> 8) + 128          */
/* V = ( ( 112 * R -  94 * G -  18 * B + 128) >> 8) + 128          */
/*                                                                 */
/* The values from this equation, will have to be clamped          */
/* between 0..255.                                                 */
/*                                                                 */
/* This benchmark is intended to highlight the value of predicated */
/* stores to memory.                                               */
/*                                                                 */
/* API:                                                            */
/* void rgb_to_yuv                                                 */
/* (                                                               */
/*     unsigned char    iPtrR[],                                   */
/*     unsigned char    iPtrG[],                                   */
/*     unsigned char    iPtrB[],                                   */
/*     unsigned short   width,                                     */
/*     short            coefs[],                                   */
/*     unsigned char    iPtrOut[]                                  */
/* )                                                               */
/*                                                                 */
/* The function "rgb_to_yuv" accepts red, green and blue pixels    */
/* in arrays "iPtrR", "iPtrG" and "iPtrB" into an interleaved      */
/* array of YUYV pixels stored in "iPtrOut" by applying a 3x3      */
/* array of coefficients to convert from RGB to YUV space.         */
/*                                                                 */
/*=================================================================*/


unsigned char CLIP (int x)
{
    unsigned char y;
    y = (x > 255) ? 255: ((x < 0)) ? 0: x;
    return (y);
}

void rgb_to_yuv 
(
    unsigned char    iPtrR[],
    unsigned char    iPtrG[],
    unsigned char    iPtrB[],
    unsigned short   width,
    short            coefs[],
    unsigned char    iPtrOut[]
)
{
     int j;

     short coef_ry0  = coefs[0];
     short coef_gy0  = coefs[1];
     short coef_by0  = coefs[2];

     short coef_ru0  = coefs[3];
     short coef_gu0  = coefs[4];
     short coef_bu0  = coefs[5];

     short coef_rv0  = coefs[6];
     short coef_gv0  = coefs[7];
     short coef_bv0  = coefs[8];

     unsigned char redByte1;
     unsigned char greenByte1;
     unsigned char blueByte1;

     unsigned char redByte2;
     unsigned char greenByte2;
     unsigned char blueByte2;

     int temp_y0;
     int temp_y1;
     int temp_u0;
     int temp_v0;
     int temp_ur0;
     int temp_ug0;
     int temp_vb0;
     int temp_vg0;

     for (j=0; j < (width/2); j++)
     {
        //Get First pixel Data            
        redByte1    =  iPtrR[2*j];  
        greenByte1  =  iPtrG[2*j];  
        blueByte1   =  iPtrB[2*j];
  
        //Get Second Pixel Data     
        redByte2    = iPtrR[2*j+1];  
        greenByte2  = iPtrG[2*j+1];  
        blueByte2   = iPtrB[2*j+1];
        
        temp_y0   = (coef_ry0*redByte1 + coef_gy0*greenByte1 + coef_by0*blueByte1 + 128) >> 8;
        temp_y1   = (coef_ry0*redByte2 + coef_gy0*greenByte2 + coef_by0*blueByte2 + 128) >> 8;

        temp_ur0   = coef_ru0*redByte1;
        temp_ug0   = coef_gu0*greenByte1;
        temp_u0    = ((temp_ur0 + temp_ug0 + coef_bu0*blueByte1 + 128) >> 8) + 128;
        
        temp_vb0  = coef_bv0*blueByte2;
        temp_vg0  = coef_gv0*greenByte2;
        temp_v0 = ((temp_vb0 + temp_vg0 + coef_rv0*redByte2 + 128) >> 8) + 128;

        temp_y0 = CLIP (temp_y0);
        temp_u0 = CLIP (temp_u0);
        temp_y1 = CLIP (temp_y1);
        temp_v0 = CLIP (temp_v0);

        iPtrOut[4*j]     = temp_u0;  
        iPtrOut[4*j + 2] = temp_v0;

        iPtrOut[4*j+1] = temp_y0;
        iPtrOut[4*j+3] = temp_y1;
     }
}

/*-----------------------------------------------------------------*/
/*  End of file: vcop_rgb_to_yuv_c.c                               */
/*=================================================================*/
/* Texas Instruments Incorporated 2009-2012.                       */
/*-----------------------------------------------------------------*/

