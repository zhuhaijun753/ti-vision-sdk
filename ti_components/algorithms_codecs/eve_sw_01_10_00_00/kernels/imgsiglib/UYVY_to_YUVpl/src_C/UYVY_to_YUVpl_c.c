/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     UYVY_to_YUVpl                                                        */
/*                                                                          */
/*     USAGE                                                                */
/*     The C version of this routine is can be called as:                   */
/*                                                                          */
/*     void UYVY_to_YUVpl_c                                                 */
/*     (                                                                    */
/*         unsigned char *YUV_422image,                                     */
/*         int width,                                                       */
/*         int line_pitch,                                                  */
/*         int height,                                                      */
/*         unsigned char *y,                                                */
/*         unsigned char *cr,                                               */
/*         unsigned char *cb                                                */
/*     )                                                                    */ 
/*                                                                          */
/*     DESCRIPTION                                                          */
/*            (Source VLIB) This routine accepts a pointer to an            */
/*     interleaved YUV 422 data array and de-interleaves the color channels */
/*     into three separate memory locations.                                */
/*                                                                          */
/*     YUV_422image :  Pointer to an input array of interleaved chroma and  */
/*                     luma pixels. Each value is unsigned 8-bit.           */
/*                                                                          */ 
/*                     U0 Y0 V0 Y1 U1 Y2 V1 Y3                              */
/*                                                                          */
/*     The image data is loaded as 16-bit halfwords where each half word    */
/*     contains a Y component and either a Cr or Cb component.              */
/*     Planarization is done by using store-byte to ignore the upper byte   */
/*     of the half word and store only Cb and Cr, and store-byte with       */
/*     truncation by 8-bits to shift the luma from the upper byte to the    */
/*     lower byte before the store.                                         */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
                                                                            
                                                                            
                                                                            
                                                                            


void UYVY_to_YUVpl_c
(
    unsigned char *yc,      /* Interleaved luma/chroma  */
    int width,              /* width (number of luma pixels)    */
    int pitch,                    
    int height,                   
    unsigned char* y,       /* Luma plane (8-bit)      */
    unsigned char* cr,      /* Cr chroma plane (8-bit) */
    unsigned char* cb       /* Cb chroma plane (8-bit) */
)
{                                          
    int i,j;   
    
    for (i = 0; i < height; i++)
    {                  
        for (j = 0; j < (width/2); j++)
        {                         
            y[width*i + 2*j+0]  = yc[2*pitch*i + 4*j + 1];
            y[width*i + 2*j+1]  = yc[2*pitch*i + 4*j + 3];
            cr[(width/2)*i + j] = yc[2*pitch*i + 4*j + 2];
            cb[(width/2)*i + j] = yc[2*pitch*i + 4*j + 0];
        }
    }
}

