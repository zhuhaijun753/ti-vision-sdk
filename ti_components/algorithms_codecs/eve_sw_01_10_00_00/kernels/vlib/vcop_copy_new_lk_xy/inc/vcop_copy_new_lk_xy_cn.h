/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_copy_new_lk_xy_cn.h                                     */
/*                                                                          */
/*     @version 1.0 (January 2014) : Base version.                          */
/*                                                                          */
/*==========================================================================*/

#include <stdint.h>

#ifndef _VCOP_COPY_NEW_LK_XY_CN
#define _VCOP_COPY_NEW_LK_XY_CN  1

void vcop_copy_new_lk_xy_cn
(
    short         *  pInput_A,
    short         *  pOutput_B,
    unsigned char *  currValidPoints,
    unsigned int  *  pBaseAddrList ,
    unsigned int  *  pValidAddrList,
    unsigned int  *  pOutAddrList     ,
    unsigned int  *  pValidOutAddrList,
    short         *  pLocalX,
    short         *  pLocalY,
    short         *  pLocalXY,
    unsigned short   numKeyPoints
);
#endif /* _VCOP_COPY_NEW_LK_XY_CN */
