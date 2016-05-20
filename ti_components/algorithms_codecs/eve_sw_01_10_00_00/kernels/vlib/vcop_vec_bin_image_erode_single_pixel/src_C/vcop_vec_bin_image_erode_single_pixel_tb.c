/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      vcop_vec_bin_image_erode_single_pixel-tb                            */
/*                                                                          */
/*  Driver file for testing Erosion of isolated pixels                      */
/*                                                                          */
/*                                                                          */
/*  USAGE                                                                   */
/*      This code contains a driver program for testing the 'vcop_vec_bin_  */
/*  image_erode_single_pixel" function by injecting it with the same data   */
/*  set as in the natural C testbench functions.                            */
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

#include "vcop_vec_bin_image_erode_single_pixel_c.h"


#define WIDTH   (64*4)
#define PITCH   (64*4)
#define HEIGHT  (30)

unsigned int Erode_bin_single_pixel_IN[32*2*4]={                                                 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x007e001f, 0xc00ff000, 0x007e001f, 0xc00ff000, 
    0x007e001f, 0xc00ff000, 0x007e001f, 0xc00ff000, 
    0x207c001f, 0x8007f000, 0x207c001f, 0x8007f000, 
    0x207c001f, 0x8007f000, 0x207c001f, 0x8007f000, 
    0x003f003f, 0xe00fe000, 0x003f003f, 0xe00fe000, 
    0x003f003f, 0xe00fe000, 0x003f003f, 0xe00fe000, 
    0x000fe0ff, 0xfc3fe000, 0x000fe0ff, 0xfc3fe000, 
    0x000fe0ff, 0xfc3fe000, 0x000fe0ff, 0xfc3fe000, 
    0x0003f9fc, 0xff7fc004, 0x0003f9fc, 0xff7fc004, 
    0x0003f9fc, 0xff7fc004, 0x0003f9fc, 0xff7fc004, 
    0x0000fff0, 0x1fff0000, 0x0000fff0, 0x1fff0000, 
    0x0000fff0, 0x1fff0000, 0x0000fff0, 0x1fff0000, 
    0x00003fc0, 0x07f80000, 0x00003fc0, 0x07f80000, 
    0x00003fc0, 0x07f80000, 0x00003fc0, 0x07f80000, 
    0x02000f00, 0x01f00000, 0x02000f00, 0x01f00000, 
    0x02000f00, 0x01f00000, 0x02000f00, 0x01f00000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x20000000, 0x00000000, 0x20000000, 0x00000000, 
    0x20000000, 0x00000000, 0x20000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x0000007c, 0x00000010, 0x0000007c, 0x00000010, 
    0x0000007c, 0x00000010, 0x0000007c, 0x00000010, 
    0x00007fff, 0xff000000, 0x00007fff, 0xff000000, 
    0x00007fff, 0xff000000, 0x00007fff, 0xff000000, 
    0x003fffff, 0xfff00000, 0x003fffff, 0xfff00000, 
    0x003fffff, 0xfff00000, 0x003fffff, 0xfff00000, 
    0x07fff000, 0xfffe0000, 0x07fff000, 0xfffe0000, 
    0x07fff000, 0xfffe0000, 0x07fff000, 0xfffe0000, 
    0x0ff80000, 0x01ffc000, 0x0ff80000, 0x01ffc000, 
    0x0ff80000, 0x01ffc000, 0x0ff80000, 0x01ffc000, 
    0x0fe00c03, 0x00ffe000, 0x0fe00c03, 0x00ffe000, 
    0x0fe00c03, 0x00ffe000, 0x0fe00c03, 0x00ffe000, 
    0x0fe0070e, 0x007fe000, 0x0fe0070e, 0x007fe000, 
    0x0fe0070e, 0x007fe000, 0x0fe0070e, 0x007fe000, 
    0x0fe00000, 0x007fe000, 0x0fe00000, 0x007fe000, 
    0x0fe00000, 0x007fe000, 0x0fe00000, 0x007fe000, 
    0x0fe00000, 0x007fe002, 0x0fe00000, 0x007fe002, 
    0x0fe00000, 0x007fe002, 0x0fe00000, 0x007fe002, 
    0x0ff83803, 0x80ffe000, 0x0ff83803, 0x80ffe000, 
    0x0ff83803, 0x80ffe000, 0x0ff83803, 0x80ffe000, 
    0x0ffe0e0e, 0x01fff000, 0x0ffe0e0e, 0x01fff000, 
    0x0ffe0e0e, 0x01fff000, 0x0ffe0e0e, 0x01fff000, 
    0x07ff83fc, 0x0fff8000, 0x07ff83fc, 0x0fff8000, 
    0x07ff83fc, 0x0fff8000, 0x07ff83fc, 0x0fff8000, 
    0x01fff800, 0x7ff80000, 0x01fff800, 0x7ff80000, 
    0x01fff800, 0x7ff80000, 0x01fff800, 0x7ff80000, 
    0x003fffff, 0xff000000, 0x003fffff, 0xff000000, 
    0x003fffff, 0xff000000, 0x003fffff, 0xff000000, 
    0x00001fff, 0xf8000010, 0x00001fff, 0xf8000010, 
    0x00001fff, 0xf8000010, 0x00001fff, 0xf8000010, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000
};    

unsigned int Erode_bin_single_pixel_OUT[30*2*4]={                                                
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00fc003f, 0x801fe000, 0x00fc003f, 0x801fe000, 
    0x00fc003f, 0x801fe000, 0x00fc003f, 0x801fe000, 
    0x00f8003f, 0x000fe000, 0x00f8003f, 0x000fe000, 
    0x00f8003f, 0x000fe000, 0x00f8003f, 0x000fe000, 
    0x007e007f, 0xc01fc000, 0x007e007f, 0xc01fc000, 
    0x007e007f, 0xc01fc000, 0x007e007f, 0xc01fc000, 
    0x001fc1ff, 0xf87fc000, 0x001fc1ff, 0xf87fc000, 
    0x001fc1ff, 0xf87fc000, 0x001fc1ff, 0xf87fc000, 
    0x0007f3f9, 0xfeff8000, 0x0007f3f9, 0xfeff8000, 
    0x0007f3f9, 0xfeff8000, 0x0007f3f9, 0xfeff8000, 
    0x0001ffe0, 0x3ffe0000, 0x0001ffe0, 0x3ffe0000, 
    0x0001ffe0, 0x3ffe0000, 0x0001ffe0, 0x3ffe0000, 
    0x00007f80, 0x0ff00000, 0x00007f80, 0x0ff00000, 
    0x00007f80, 0x0ff00000, 0x00007f80, 0x0ff00000, 
    0x00001e00, 0x03e00000, 0x00001e00, 0x03e00000, 
    0x00001e00, 0x03e00000, 0x00001e00, 0x03e00000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x000000f8, 0x00000000, 0x000000f8, 0x00000000, 
    0x000000f8, 0x00000000, 0x000000f8, 0x00000000, 
    0x0000ffff, 0xfe000000, 0x0000ffff, 0xfe000000, 
    0x0000ffff, 0xfe000000, 0x0000ffff, 0xfe000000, 
    0x007fffff, 0xffe00000, 0x007fffff, 0xffe00000, 
    0x007fffff, 0xffe00000, 0x007fffff, 0xffe00000, 
    0x0fffe001, 0xfffc0000, 0x0fffe001, 0xfffc0000, 
    0x0fffe001, 0xfffc0000, 0x0fffe001, 0xfffc0000, 
    0x1ff00000, 0x03ff8000, 0x1ff00000, 0x03ff8000, 
    0x1ff00000, 0x03ff8000, 0x1ff00000, 0x03ff8000, 
    0x1fc01806, 0x01ffc000, 0x1fc01806, 0x01ffc000, 
    0x1fc01806, 0x01ffc000, 0x1fc01806, 0x01ffc000, 
    0x1fc00e1c, 0x00ffc000, 0x1fc00e1c, 0x00ffc000, 
    0x1fc00e1c, 0x00ffc000, 0x1fc00e1c, 0x00ffc000, 
    0x1fc00000, 0x00ffc000, 0x1fc00000, 0x00ffc000, 
    0x1fc00000, 0x00ffc000, 0x1fc00000, 0x00ffc000, 
    0x1fc00000, 0x00ffc000, 0x1fc00000, 0x00ffc000, 
    0x1fc00000, 0x00ffc000, 0x1fc00000, 0x00ffc000, 
    0x1ff07007, 0x01ffc000, 0x1ff07007, 0x01ffc000, 
    0x1ff07007, 0x01ffc000, 0x1ff07007, 0x01ffc000, 
    0x1ffc1c1c, 0x03ffe000, 0x1ffc1c1c, 0x03ffe000, 
    0x1ffc1c1c, 0x03ffe000, 0x1ffc1c1c, 0x03ffe000, 
    0x0fff07f8, 0x1fff0000, 0x0fff07f8, 0x1fff0000, 
    0x0fff07f8, 0x1fff0000, 0x0fff07f8, 0x1fff0000, 
    0x03fff000, 0xfff00000, 0x03fff000, 0xfff00000, 
    0x03fff000, 0xfff00000, 0x03fff000, 0xfff00000, 
    0x007fffff, 0xfe000000, 0x007fffff, 0xfe000000, 
    0x007fffff, 0xfe000000, 0x007fffff, 0xfe000000, 
    0x00003fff, 0xf0000000, 0x00003fff, 0xf0000000, 
    0x00003fff, 0xf0000000, 0x00003fff, 0xf0000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000
};
    
#pragma DATA_SECTION(Erode_bin_single_pixel_output, "Cdata");                                                                               
unsigned int Erode_bin_single_pixel_output[30*2*4];

int main()
{
    int fail;
    int i;

    /*---------------------------------------------------------------------*/
    /*  Function call to the Natural-C API to be tested                    */
    /*---------------------------------------------------------------------*/

    vcop_vec_bin_image_erode_single_pixel_cn (Erode_bin_single_pixel_IN, 
                     Erode_bin_single_pixel_output , WIDTH, PITCH, HEIGHT);

    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */


    /*---------------------------------------------------------------------*/

    fail = memcmp (Erode_bin_single_pixel_output, 
                         Erode_bin_single_pixel_OUT, (HEIGHT-2)*WIDTH/32*4);

    /*---------------------------------------------------------------------*/
    /*  If there is a mis-compare, print out a memory trace, else print    */
    /*  pass.                                                              */
    /*---------------------------------------------------------------------*/

    if (fail) 
    {
        for (i = 0; i < (HEIGHT-2)*WIDTH/32; i++)
        {
             printf ("i:%d, out:%u, EOut:%u, %c \n",
                      i, Erode_bin_single_pixel_output[i], 
                      Erode_bin_single_pixel_OUT[i], 
                      (Erode_bin_single_pixel_output[i]
                      !=Erode_bin_single_pixel_OUT[i]) ? '*':' '
                    );
        }
    }
    else      printf ("Pass \n");

}

/* ======================================================================== */
/*  End of file:  vcop_vec_bin_image_erode_single_pixel_tb.c                */
/*--------------------------------------------------------------------------*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

