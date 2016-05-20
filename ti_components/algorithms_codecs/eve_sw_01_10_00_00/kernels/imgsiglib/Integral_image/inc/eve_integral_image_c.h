/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#ifndef __VCOP_INTEGRAL_IMG_H__
#define __VCOP_INTEGRAL_IMG_H__  1

void eve_integral_image_cn
( 
 unsigned short width,
 unsigned short height,
 unsigned short img_width,
 unsigned int  *acc_h,
 unsigned int  *acc_v,
 unsigned char *inimgptr,
 unsigned short *Bimgptr0,
 unsigned short *Bimgptr1,
 unsigned int  *Cimgptr0, 
 unsigned int  *Cimgptr1, 
 unsigned int  *outimgptr
);

void reset_acc_mem( unsigned int *in, int size);

#endif
