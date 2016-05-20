/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_orientation_binning_cn.h                                        */
/*                                                                          */
/*     DESCRIPTION                                `                         */
/*         This is the c-reference header for the                           */
/*         vcop_orientation_binning  kernel                                 */
/*                                                                          */
/*                                                                          */
/*     @version 0.1 (May 2014) : Base version.                              */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_ORIENTATION_BINNING_CN
#define _VCOP_ORIENTATION_BINNING_CN  1

void vcop_orientation_binning_cn
  (
  short         *  gradX,
  short         *  gradY,
  unsigned char *  outBin,
  short         *  wSinTab,
  short         *  wCosTab,
  unsigned short   numBins,
  unsigned short   width,
  unsigned short   height,
  unsigned short   pitch
  );

#endif /* _VCOP_ORIENTATION_BINNING_CN */
