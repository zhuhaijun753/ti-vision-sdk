/*==========================================================================*/ 
/*     TEXAS INSTRUMENTS, INC.                                              */ 
/*                                                                          */ 
/*     NAME                                                                 */ 
/*     vcop_gradient5x5PyramidKernel_8_kernel_cn                            */ 
/*                                                                          */ 
/*                                                                          */ 
/*     USAGE                                                                */ 
/*     This routine is C-callable and can be called as:                     */ 
/*                                                                          */ 
/*     void vcop_gradientH5x5PyramidKernel_8                                */ 
/*     (                                                                    */ 
/*         unsigned char   pIn[],                                           */ 
/*         short           pB[],                                            */ 
/*         unsigned short  width,                                           */ 
/*         unsigned short  pitch,                                           */ 
/*         unsigned short  height,                                          */ 
/*         unsigned char   pOut[]                                           */
/*     )                                                                    */
/*                                                                          */
/*     vcop_gradientV5x5PyramidKernel_8                                     */ 
/*     (                                                                    */ 
/*         unsigned char  pIn[],                                            */ 
/*         short          pB[],                                             */ 
/*         unsigned short width,                                            */ 
/*         unsigned short pitch,                                            */ 
/*         unsigned short height,                                           */ 
/*         unsigned char  pOut[]                                            */ 
/*     )                                                                    */ 
/*                                                                          */ 
/*     pIn      :  8-bit input image                                        */
/*     pB       :  Intermediate buffer                                      */  
/*     width    :  Width of the input image                                 */ 
/*     pitch    :  Pitch of the input image                                 */ 
/*     height   :  Height of the input image                                */ 
/*     pOut     :  8-bit output image                                       */
/*                                                                          */ 
/*     Returns :  None or void.                                             */ 
/*                                                                          */ 
/*     DESCRIPTION                                                          */ 
/*             This routine accepts an 8-bit input image and outputs three  */ 
/*     levels of gradient pyramid in the pOut array.                        */ 
/*                                                                          */ 
/*     ASSUMPTIONS                                                          */ 
/*     The number of columns in the input image should be a multiple of 8.  */ 
/*                                                                          */ 
/*==========================================================================*/ 
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */ 
/*                      All Rights Reserved                                 */ 
/*==========================================================================*/ 


void vcop_gradientH5x5PyramidKernel_8
(
    unsigned char   pIn[],  
    short           pB[],     
    unsigned short  width, 
    unsigned short  pitch, 
    unsigned short  height,
    unsigned char   pOut[]
)
{
    unsigned int i,j;
    short R;
    short R0,R1,R2,R3,R4,R5;

    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            R0 = pIn[i*pitch+ j+0];
            R1 = pIn[i*pitch+ j+1];
            R3 = pIn[i*pitch+ j+3];
            R4 = pIn[i*pitch+ j+4];
            
            // [1 2 0 -2 -1] filter
            R= R0*1 + R1*2 - R3*2 - R4*1;
                                 
            pB[i*width + j] = R;                                  
                                  
        }
    }

    for(i = 0; i < (height - 3)/2; i++)
    {                
        for(j = 0; j < width/2; j++)
        {
            
            R0 = pB[2*i*width+0*width +2*j];
            R1 = pB[2*i*width+1*width +2*j];
            R2 = pB[2*i*width+2*width +2*j];
            R3 = pB[2*i*width+3*width +2*j];
            R4 = pB[2*i*width+4*width +2*j];
                        
            // [1 4 6 4 1] filter
            R =   R0*1 + R1*4 + R2*6 + R3*4 + R4*1;
            
            pOut[i*width/2+j] = ((R+64) >> 7) + 128;
            
        }
    }

}

void vcop_gradientV5x5PyramidKernel_8
(
    unsigned char  pIn[],      
    short          pB[],             
    unsigned short width,  
    unsigned short pitch,  
    unsigned short height,
    unsigned char  pOut[]
)  
{
    unsigned int i,j;
    short R;
    short R0,R1,R2,R3,R4,R5;

    for (i = 0; i < height ; i++)
    {
         for(j = 0; j < width; j++)
         {
             
             R0 = pIn[i*pitch+ j+0];
             R1 = pIn[i*pitch+ j+1];
             R2 = pIn[i*pitch+ j+2];
             R3 = pIn[i*pitch+ j+3];
             R4 = pIn[i*pitch+ j+4];
                             
             // [1 4 6 4 1]' filter
             R = R0*1 + R1*4 + R2*6 + R3*4 + R4*1;
             
             pB[i*(width) + j] = R;
                                   
         }
     }

    for (i = 0; i < (height - 3)/2; i++)
    {
        for(j = 0; j < width/2; j++)
        {
            
             R0 = pB[2*i*(width)+0*(width) + 2*j];
             R1 = pB[2*i*(width)+1*(width) + 2*j];
             R3 = pB[2*i*(width)+3*(width) + 2*j];
             R4 = pB[2*i*(width)+4*(width) + 2*j];
             
             // [1 2 0 -2 -1]' filter
             R =  R0*1 + R1*2 - R3*2 - R4*1;
             
             pOut[i*width/2+j] = ((R+64) >> 7) + 128;
            
        }        
    }
    
}

/* ======================================================================== */
/*  End of file: vcop_gradient5x5PyramidKernel_8_c.c                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

