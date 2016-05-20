/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      vcop_vec_update_ewr_variance_s16-tb                                 */
/*                                                                          */
/*  Driver file for testing                                                 */
/*                                                                          */
/*                                                                          */
/*  USAGE                                                                   */
/*      This code contains a driver program for testing the 'vcop_vec_      */
/*  update_ewr_variance_s16" function by injecting it with the same data    */
/*  set as in the assembly testbench functions.                             */
/*                                                                          */
/*  This testbench then compares the results with the expected output       */
/*  array by doing a standard "memcmp" function and printing a pass/fail    */
/*  message. If it failed it prints a byte by byte trace.                   */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include  <stdio.h>
#include  <stdlib.h>

//#include "vcop_vec_update_ewr_variance_s16_c.h"

#define NUM_PIXELS   (32)
#define UPDATE_RATE  (0x10)

unsigned char newLuma[32] = 
{
    0x000, 0x001, 0x002, 0x003, 0x004, 0x005, 0x006, 0x007, 
    0x008, 0x009, 0x00a, 0x00b, 0x00c, 0x00d, 0x00e, 0x00f, 
    0x010, 0x011, 0x012, 0x013, 0x014, 0x015, 0x016, 0x017, 
    0x018, 0x019, 0x01a, 0x01b, 0x01c, 0x01d, 0x01e, 0x01f
};

unsigned int mask32packed[1] = {0x03E0FFFF};

short runningMean[32] = 
{
    0x6400, 0x6400, 0x6400, 0x6400, 0x6400, 0x6400, 0x6400, 0x6400, 
    0x0800, 0x0800, 0x0800, 0x0800, 0x0800, 0x0800, 0x0800, 0x0800, 
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
    0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x0000, 0x0000
};       

short runningVar[32] = 
{
    80, 80, 80, 80, 80, 80, 80, 80,
    80, 80, 80, 80, 80, 80, 80, 80,
    80, 80, 80, 80, 80, 80, 80, 80,
    80, 80, 80, 80, 80, 80, 80, 80 
};              
short trueRunningVar[32] = 
{
    0x0063, 0x0063, 0x0063, 0x0062, 0x0062, 0x0062, 0x0050, 0x0050,
    0x0050, 0x0050, 0x0050, 0x0050, 0x004F, 0x004F, 0x004F, 0x004F,
    0x0050, 0x0050, 0x0050, 0x0050, 0x0050, 0x0050, 0x0050, 0x0050,
    0x0050, 0x0050, 0x0050, 0x0050, 0x0050, 0x0050, 0x0050, 0x0050
};

int main()
{
    int fail;
    int i;

    /*---------------------------------------------------------------------*/
    /*  Function call to the Natural-C API to be tested                    */
    /*---------------------------------------------------------------------*/

    vcop_vec_update_ewr_variance_s16_cn (runningVar,runningMean,
                              newLuma,mask32packed, UPDATE_RATE,NUM_PIXELS);

    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*---------------------------------------------------------------------*/

    fail = memcmp (runningVar, trueRunningVar, NUM_PIXELS);

    /*---------------------------------------------------------------------*/
    /*  If there is a mis-compare, print out a memory trace, else print    */
    /*  pass.                                                              */
    /*---------------------------------------------------------------------*/

    if (fail) 
    {
        for (i = 0; i < NUM_PIXELS; i++)
        {
             printf ("i:%d, out:%u, EOut:%u, %c \n",
                      i, runningVar[i], trueRunningVar[i], 
                      (runningVar[i]!=trueRunningVar[i]) ? '*':' '
                    );
        }
    }
    else      printf ("Pass \n");

}

/* ======================================================================== */
/*  End of file:  vcop_vec_update_ewr_variance_s16_tb.c                     */
/*--------------------------------------------------------------------------*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

