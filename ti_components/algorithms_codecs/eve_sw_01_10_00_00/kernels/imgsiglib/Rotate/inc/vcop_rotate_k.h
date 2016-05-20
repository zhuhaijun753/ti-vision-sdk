/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#ifndef __TI_ROTATE_K_H__
#define __TI_ROTATE_K_H__

void vcop_rotate_90
(
     __vptr_uint8  in,         //  Pointer to an input array of "in_type".              
     __vptr_uint8  inter,      //  Pointer to intermediate array of "inter_type".       
     __vptr_uint8  out,        //  Pointer to output array of "out_type".               
     int img_w,                //  Width of input image in pixels.                      
     int img_h,                //  Height of the input image in pixels.                 
     int out_w,                //  Width of the output image in pixels.                 
     int out_h,                //  Height of the input image in pixels.                 
     int blk_w,                //  The compute width over which rotate values are found.
     int blk_h,                //  The compute height for rotate function.              
     int in_type,              //  0 - BYTE,  1 - SHORT                                 
     int inter_type,           //  0 - BYTE,  1 - SHORT                                 
     int out_type,             //  0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT           
     int angle,                //  Angle of rotation, can be 90, 180 or 270.            
     int round_shift           //  Amount of rounding and shifting on output data.      
);

void vcop_rotate_180
(
     __vptr_uint8  in, 
     __vptr_uint8  inter,
     __vptr_uint8  out,
     int img_w,
     int img_h,
     int out_w,
     int out_h,
     int blk_w, 
     int blk_h,
     int in_type,
     int inter_type,
     int out_type,
     int angle,
     int round_shift
);


void vcop_rotate_270
(
     __vptr_uint8  in, 
     __vptr_uint8  inter,
     __vptr_uint8  out,
     int img_w,
     int img_h,
     int out_w,
     int out_h,
     int blk_w, 
     int blk_h,
     int in_type,
     int inter_type,
     int out_type,
     int angle,
     int round_shift
);

#endif
