/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      eve_mat_mul_tb.c                                                    */
/*                                                                          */
/*  Driver file for mat_mul mat_mul over a window.                          */
/*                                                                          */
/*  USAGE                                                                   */
/*      This code is a driver file for testing the 'vcop_mat_mul'           */
/*  function by injecting it with the same data set as in the               */
/*  Kernel-C testbench functions.                                           */
/*                                                                          */
/*  This testbench then compares the results with the expected output       */
/*  array "EOut" by doing a standard "memcmp" and printing a pass/fail      */
/*  message. If it failed it prints a byte by byte trace.                   */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


#include <stdio.h>
#include <vcop.h>

#include "test_profile.h"

typedef unsigned char  Uint8;
typedef unsigned short Uint16;
typedef unsigned int   Uint32;

typedef char    Int8;
typedef short   Int16;
typedef int     Int32;


/*-----------------------------------------------------------------------*/
/* Complete image size for correct block placement                       */
/*-----------------------------------------------------------------------*/

#define   IN1_W             (8)
#define   IN1_H             (5)

/*-----------------------------------------------------------------------*/
/* Array sizes for matrices being multiplied                             */
/*-----------------------------------------------------------------------*/

#define   IN2_W            (8)      
#define   IN2_H            (IN1_W)

#define   RND_SAT          (0)

#define   N0                (IN1_W * IN1_H )
#define   N1                (IN2_W * IN2_H)
#define   Nout              (IN2_W * IN1_H)

#define   INPUT_TYPE        0   // 0 - uchar, 1 - char, 2 - ushort, 3 - short 
#define   COEF_TYPE         0   // 0 - uchar, 1 - char, 2 - ushort, 3 - short
#define   OUTPUT_TYPE       1   // 0 - char, 1 - short, 2 - word

#if 1
#pragma DATA_SECTION(in1, "Adata");
Uint8 in1[N0] =
{
    0x001, 0x02, 0x03, 0x04, 0x05,  0x06,  0x07,  0x08,
    0x010, 0x02, 0x03, 0x04, 0x05,  0x06,  0x07,  0x08,
    0x020, 0x02, 0x03, 0x04, 0x05,  0x06,  0x07,  0x08,
    0x030, 0x02, 0x03, 0x04, 0x05,  0x06,  0x07,  0x08,
    0x040, 0x02, 0x03, 0x04, 0x05,  0x06,  0x07,  0x08,

};

#pragma DATA_SECTION(in2, "Bdata");
Uint8 in2[N1] =
{
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
};
#else
#pragma DATA_SECTION(in1, "Adata");
Uint8 in1[N0] =
{
    0x01, 0x01, 0x01, 0x01, 0x01,  0x01,  0x01,  0x01,
    0x01, 0x01, 0x01, 0x01, 0x01,  0x01,  0x01,  0x01,
    0x01, 0x01, 0x01, 0x01, 0x01,  0x01,  0x01,  0x01,
    0x01, 0x01, 0x01, 0x01, 0x01,  0x01,  0x01,  0x01,
    0x01, 0x01, 0x01, 0x01, 0x01,  0x01,  0x01,  0x01,

};

#pragma DATA_SECTION(in2, "Bdata");
Uint8 in2[N1] =
{
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
};
#endif

#pragma DATA_SECTION(ref, "Cdata");
Int16 ref[Nout] =
{
    36,    72,   108,   144,   180,   216,   252,   288,
    51,   102,   153,   204,   255,   306,   357,   408,
    67,   134,   201,   268,   335,   402,   469,   536,
    83,   166,   249,   332,   415,   498,   581,   664,
    99,   198,   297,   396,   495,   594,   693,   792,
    
};

/*-----------------------------------------------------------------------*/
/* This is our intermediate buffer before downsampling horizontally.     */
/*-----------------------------------------------------------------------*/

#pragma DATA_SECTION(out, "Bdata");
Int16 out[Nout] = {0};
  
#pragma DATA_SECTION(profile_array, "Cdata");
unsigned int profile_array[2];

#if VCOP_HOST_EMULATION
  #include "vcop_mat_mul_kernel.k"    // kernel source
#else
  #include "../inc/vcop_mat_mul_kernel.h"    // translated kernel
#endif

int verify_output();

int main()
{
    int ok;
    int i;

    /*-------------------------------------------------------------------*/
    /* Actual mat_muling operation happens here as part of the test bench */
    /* and the results are written out so as to be compared with EVE     */
    /* results.                                                          */
    /*-------------------------------------------------------------------*/
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

    if (( INPUT_TYPE == 0) && (COEF_TYPE == 0) && (OUTPUT_TYPE == 1) )
    {
        
        for (i = 0; i < 2; i++)
        {
            vcop_mat_mul_uchar_uchar_short
            ( 
               in1, 
               in2, 
               out,
               IN1_W,         
               IN1_H,       
               IN2_W,        
               RND_SAT
            ); 
            
            /*-------------------------------------------------------------------*/
            /* Print out the results here.                                       */
            /*-------------------------------------------------------------------*/
            
        }
    }
#ifdef REPORT	
#ifdef SCTM
sctm_t2 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
		overflow= EVE_SCTM_OverflowCheck(CTM,SCTM_Counter_0);
		assert(overflow!=1);

exec_diff = sctm_t2 - sctm_t1;		
EVE_SCTM_CounterTimerDisable(CTM, SCTM_Counter_0);
#endif			
#endif

#ifdef REPORT
fprintf(fpReport,"vcop_matrix_mul,");
fprintf(fpReport,"%d,",IN1_W);
fprintf(fpReport,"%d,",IN1_H);
fprintf(fpReport,"%d,",IN1_W);
fprintf(fpReport,"%d,",IN1_H);
fprintf(fpReport,"2,");
#endif	        
    ok = verify_output();

#ifdef CONSOLE	
    if (ok) printf("\n\nMatrix Multiplication Kernel-C - code : PASS\n");
    else printf("\n\nMatrix Multiplication Kernel-C - code : FAIL\n");
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


int verify_output()
{
    int i, j, ok;

   ok = 1;
   for ( j = 0; j < IN1_H; j++)
   {
      for ( i = 0; i < IN2_W; i++)
      {
          if ( out[j * IN2_W + i] != ref[j * IN2_W + i] )
          {
              ok = 0;
          }
      } 
   }
   
   return ok;

}




