/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      UYVY_to_YUVpl-tb                                                    */
/*                                                                          */
/*  Driver file for testing UYVY de-interleaving                            */
/*                                                                          */
/*  USAGE                                                                   */
/*      This code contains a driver program for testing the                 */
/*  'UYVY_to_YUVpl_c" function by injecting it with the same data set as    */
/*  in the assembly testbench functions.                                    */
/*                                                                          */
/*  This testbench then compares the results with the expected output       */
/*  arrays "EOutY, EOutU, ROutV" by doing a standard "memcmp" and printing  */
/*  a pass/fail message. If it failed it prints a byte by byte trace.       */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */


#include <stdlib.h>
#include <stdio.h>     

#include "../inc/UYVY_to_YUVpl_c.h"

#define IMG_WIDTH  64 
#define IMG_HEIGHT 32
#define IMG_LINE_PITCH 64

/* Input UYVY image */
extern unsigned char CurrentFrame[64*32*2];

#pragma DATA_SECTION(CurrentLumaPtr,"Cdata") 
unsigned char CurrentLumaPtr[IMG_WIDTH*IMG_HEIGHT] = {0};

#pragma DATA_SECTION(CurrentCrPtr,"Cdata") 
unsigned char CurrentCrPtr[IMG_WIDTH*IMG_HEIGHT/2] = {0};

#pragma DATA_SECTION(CurrentCbPtr,"Cdata") 
unsigned char CurrentCbPtr[IMG_WIDTH*IMG_HEIGHT/2] = {0};

/* Expected output data */
extern unsigned char ECurrentLumaPtr[IMG_WIDTH*IMG_HEIGHT];
extern unsigned char ECurrentCrPtr[IMG_WIDTH*IMG_HEIGHT/2];
extern unsigned char ECurrentCbPtr[IMG_WIDTH*IMG_HEIGHT/2];


void main ()
{
    int fail_y, fail_Cr, fail_Cb, i;
    
    UYVY_to_YUVpl_c(CurrentFrame, IMG_WIDTH, IMG_LINE_PITCH, IMG_HEIGHT, CurrentLumaPtr, CurrentCrPtr, CurrentCbPtr);
    
    fail_y  = memcmp (CurrentLumaPtr, ECurrentLumaPtr, IMG_WIDTH*IMG_HEIGHT);
    fail_Cr = memcmp (CurrentCrPtr, ECurrentCrPtr, IMG_WIDTH*IMG_HEIGHT/2);
    fail_Cb = memcmp (CurrentCbPtr, ECurrentCbPtr, IMG_WIDTH*IMG_HEIGHT/2);



    if (fail_y) 
    {
        for (i = 0; i < IMG_WIDTH*IMG_WIDTH; i++)
        {
           printf ("i:%d, Y:%d, EOut:%d, %c \n", 
                    i, CurrentLumaPtr[i], ECurrentLumaPtr[i], (CurrentLumaPtr[i] == ECurrentLumaPtr[i]) ? ' ' : '*'
                  );
        }
    }
    else      printf ("Y Pass \n");

    if (fail_Cr) 
    {
        for (i = 0; i < IMG_WIDTH*IMG_WIDTH/2; i++)
        {
           printf ("i:%d, V:%d, EOut:%d, %c \n", 
                    i, CurrentCrPtr[i], ECurrentCrPtr[i], (CurrentCrPtr[i] == ECurrentCrPtr[i]) ? ' ' : '*'
                  );
        }
    }
    else      printf ("V Pass \n");

    if (fail_Cb) 
    {
        for (i = 0; i < IMG_WIDTH*IMG_WIDTH/2; i++)
        {
           printf ("i:%d, U:%d, EOut:%d, %c \n", 
                    i, CurrentCbPtr[i], ECurrentCbPtr[i], (CurrentCbPtr[i] == ECurrentCbPtr[i]) ? ' ' : '*'
                  );
        }
    }
    else      printf ("U Pass \n");

}

