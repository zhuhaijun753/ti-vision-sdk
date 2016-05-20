/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*-----------------------------------------------------------------*/
/* NAME : vcop_rgb_rgb16 : Test bench data                         */ 
/*                                                                 */
/* DESCRIPTION:                                                    */
/* The function "vcop_rgb_rgb16" accepts un-packed data in         */
/* the form of packed 16-bit "r", "g" and "b" with 5-bits each,    */
/* resulting in RGB555 or RGB565 data.                             */
/*                                                                 */
/* API:                                                            */
/*                                                                 */
/* void vcop_rgb_rgb555                                            */
/* (                                                               */
/*     __vptr_uint32  rgb,                                         */
/*     __vptr_int8    rgbmask,                                     */
/*     unsigned int   npixels,                                     */
/*     __vptr_uint16  rgb555                                       */
/*  );                                                             */
/*                                                                 */
/* void vcop_rgb_rgb565                                            */
/* (                                                               */
/*     __vptr_uint32  rgb,                                         */
/*     __vptr_int8    rgbmask,                                     */
/*     unsigned int   npixels,                                     */
/*     __vptr_uint16  rgb565                                       */
/*  );                                                             */
/*                                                                 */
/* The function "vcop_rgb_rgb16" accepts unpacked "r", "g"         */
/* and "b" data, for "npixels" pixels, and writes packed 16-bit    */
/* RGB555 or RGB565 data.                                          */
/*                                                                 */
/* PERFORMANCE                                                     */
/* 4/8 cyc/pix                                                     */
/*                                                                 */
/*=================================================================*/



#include <stdio.h>
#include <vcop.h>

#include "test_profile.h"


typedef unsigned short Uint16;
typedef unsigned char  Uint8;

#define NUM_PIXELS   16

#pragma DATA_SECTION (in_rgb1, "Adata");
unsigned char in_rgb1[NUM_PIXELS * 4] =
{ 
    0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0x01, 0x02, 0x03,
    0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0x01, 0x02, 0x03,
    0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0x01, 0x02, 0x03,
    0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0x01, 0x02, 0x03,
    0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0x01, 0x02, 0x03,
    0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0x01, 0x02, 0x03,
    0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0x01, 0x02, 0x03,
    0x01,
};

#pragma DATA_SECTION (rgb_shift, "Bdata");
char rgb_shift[24] =
{  
   -0, -24, -16,  -8,  -0, -24, -16,  -8,
   -8,  -0, -24, -16,  -8,  -0, -24, -16,
  -16,  -8,  -0, -24, -16,  -8,  -0, -24,
};

#pragma DATA_SECTION (out_rgb555, "Cdata");
#pragma DATA_ALIGN (out_rgb555, 32);
unsigned short out_rgb555[NUM_PIXELS] = {0};

#pragma DATA_SECTION (Ergb555, "EOutdata");
unsigned short Ergb555[NUM_PIXELS] =
{
    0x0c41, 0x0c41, 0x0c41, 0x0c41,
    0x0c41, 0x0c41, 0x0c41, 0x0c41,
    0x0c41, 0x0c41, 0x0c41, 0x0c41,
    0x0c41, 0x0c41, 0x0c41, 0x0c41,
};

#pragma DATA_SECTION (in_rgb2, "Adata");
unsigned char in_rgb2[NUM_PIXELS * 4] =
{
    0x1A, 0x3C, 0x0F, 0x1F, 0x2F, 0x07, 0x1F, 0x3C, 
    0x0F, 0x1A, 0x2F, 0x07, 0x1A, 0x3C, 0x0F, 0x1F,
    0x2F, 0x07, 0x1F, 0x3C, 0x0F, 0x1A, 0x2F, 0x07,
    0x1A, 0x3C, 0x0F, 0x1F, 0x2F, 0x07, 0x1F, 0x3C,
    0x0F, 0x1A, 0x2F, 0x07, 0x1A, 0x3C, 0x0F, 0x1F,
    0x2F, 0x07, 0x1F, 0x3C, 0x0F, 0x1A, 0x2F, 0x07,  
};

#pragma DATA_SECTION (out_rgb565, "Cdata");
#pragma DATA_ALIGN (out_rgb565, 32);
unsigned short out_rgb565[NUM_PIXELS] = {0};

#pragma DATA_SECTION (Ergb565, "EOutdata");
unsigned short Ergb565[NUM_PIXELS] =
{
    0x7F9A, 0x3DFF, 0x7F9F, 0x3DFA, 
    0x7F9A, 0x3DFF, 0x7F9F, 0x3DFA,
    0x7F9A, 0x3DFF, 0x7F9F, 0x3DFA,
    0x7F9A, 0x3DFF, 0x7F9F, 0x3DFA,
};

#if VCOP_HOST_EMULATION
  #include "vcop_rgb_rgb16_kernel.k"           // kernel source
#else
  #include "../inc/vcop_rgb_rgb16_kernel.h"    // translated kernel
#endif

void print_output();
int  verify_output();

int main()
{
    int ok;
#ifdef REPORT
FILE* fpReport = fopen("../../../report.csv","a+");
#ifdef SCTM
unsigned int sctm_t1, sctm_t2, exec_diff;
unsigned int overflow;
EVE_SCTM_Enable(CTM);
EVE_SCTM_CounterConfig(CTM, SCTM_Counter_0, VCOP_BUSY, SCTM_DURATION);
EVE_SCTM_CounterTimerEnable(CTM, SCTM_Counter_0);
#endif   
#endif

#ifdef REPORT
#ifdef SCTM
sctm_t1 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
#endif
#endif        
    vcop_rgb_rgb555
    (
        (unsigned int *)in_rgb1,
        rgb_shift,
        NUM_PIXELS,
        out_rgb555
    );

    vcop_rgb_rgb565
    (
        (unsigned int *)in_rgb2,
        rgb_shift,
        NUM_PIXELS,
        out_rgb565
    );
#ifdef REPORT	
#ifdef SCTM
sctm_t2 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
		overflow= EVE_SCTM_OverflowCheck(CTM,SCTM_Counter_0);
		assert(overflow!=1);

exec_diff = sctm_t2 - sctm_t1;		
EVE_SCTM_CounterTimerDisable(CTM, SCTM_Counter_0);
#endif			
#endif	

#ifdef CONSOLE   
   print_output();
#endif
   
   ok = verify_output();

#ifdef CONSOLE   
   if (ok )   printf(ok ? "\n\nR, G, B planes pack to RGB 16-bit -- Kernel-C code: PASS\n" : "FAIL\n"); 
#endif
#ifdef REPORT
fprintf(fpReport,"vcop_rgb16bitPack,");
fprintf(fpReport,"%d,",NUM_PIXELS);
fprintf(fpReport,"%d,",1);
fprintf(fpReport,"%d,",NUM_PIXELS);
fprintf(fpReport,"%d,",1);
fprintf(fpReport,"1,");
#endif	       

#ifdef REPORT   
if(ok){
fprintf(fpReport,"PASS,");
}
else{
fprintf(fpReport,"FAIL,");
}
#ifdef SCTM
fprintf(fpReport,"%d\n",exec_diff);
#endif
if(fpReport){
fclose(fpReport);
}
#endif 
    return 0;
}

void print_output()
{
   int i;

   printf("\n\n RGB555 - DATA  \n");
   for (i = 0; i < NUM_PIXELS; ++i)
   {
      printf("0x%3.4x, ", out_rgb555[i]); 
   }
 
   printf("\n\n RGB565 - DATA  \n");
   for (i = 0; i < NUM_PIXELS; ++i)
   {
      printf("0x%2.2x, ", out_rgb565[i]); 
   }

   printf("\n\n");
}

int verify_output()
{
   int ok = 1;
   int i;

   for (i = 0; i < NUM_PIXELS; ++i)
   {
      if (out_rgb555[i] != Ergb555[i])
          ok = 0;
   }
 
   for (i = 0; i < NUM_PIXELS; ++i)
   {
      if (out_rgb565[i] != Ergb565[i])
          ok = 0;
   }

  return (ok);

}

/*=================================================================*/
/* End of file: vcop_rgb_rgb16.c                                   */
/*-----------------------------------------------------------------*/
/* Texas Instruments Incorporated 2009-2012.                       */
/*-----------------------------------------------------------------*/



