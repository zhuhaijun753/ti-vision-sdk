/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#ifndef __VCOP_SAD_CN_H__
#define __VCOP_SAD_CN_H__    1

void vcop_SAD_cn
(
    signed char   *in, 
    signed char   *ref,
    signed short  *sad,
    signed short  *min_sad,
    int           blk_w,      
    int           blk_h,      
    int           in_w,      
    int           in_h,       
    int           ref_w,      
    int           ref_h,      
    int           offset_horz,
    int           offset_vert,
    int           steps_horz, 
    int           steps_vert,
    int           no_input_blks_horz,
    int           no_input_blks_vert
);

#endif
