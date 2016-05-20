/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_nxn_block_sum_cn.h                                              */
/*                                                                          */
/*     DESCRIPTION                                `                         */
/*         This is the c-reference header for the                           */
/*         nx bloc sum of 8 bit or 16 bit data                              */
/*                                                                          */
/*                                                                          */
/*     @version 0.1 (May 2014) : Base version.                              */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_NXN_BLOCK_SUM_CN
#define _VCOP_NXN_BLOCK_SUM_CN  1

void vcop_nxn_sum_u8_cn
(
  unsigned char  *   inPtr1,
  unsigned char  *   inPtr2,
  unsigned short *   outPtr1,
  unsigned short *   outPtr2,
  unsigned short     n,
  unsigned short     width,
  unsigned short     height,
  unsigned short     pitch1,
  unsigned short     pitch2
);
void vcop_nxn_sum_u16_cn
(
  unsigned short *   inPtr1,
  unsigned short *   inPtr2,
  unsigned short *   outPtr1,
  unsigned short *   outPtr2,
  unsigned short     n,
  unsigned short     width,
  unsigned short     height,
  unsigned short     pitch1,
  unsigned short     pitch2
);
void vcop_nxn_sum_interleaved_cn
(
  unsigned char *   inPtr,
  unsigned short *   outPtr1,
  unsigned short *   outPtr2,
  unsigned short     n,
  unsigned short     width,
  unsigned short     height,
  unsigned short     pitch,
  unsigned short     shiftValue
);

#endif /* _VCOP_NXN_BLOCK_SUM_CN */
