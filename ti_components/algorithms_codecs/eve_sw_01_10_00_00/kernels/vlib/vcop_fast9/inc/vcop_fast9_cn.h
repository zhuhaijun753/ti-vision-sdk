/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *******************************************************************************
 *  @func          vcop_fast9_cn
 *  @brief         This is natural C implementation of FAST9 corner detection
 *  @param [in]    input   : Pointer to input 8-bit image
 *  @param [in]    output  : Pointer to output binary image
 *
 *  Output format of the buffer is crtical to know. It is as described
 *  OutputWidth of the buffer is ROUNDUP ((in_w-6)/8)
 *  OutputHeight of the buffer is in_h
 *  The way corners are stored are packed..... so pixel 0 being corner
 *  or not is represnted by bit 0 of byte 0 in output buffer. The first byte
 *  bit 0 in output buffer belongs to pixel at (3,3) in input buffer. and per row
 *  key point desiction of width-6 pixels are reported back
 *  since there are possibly width - 6 key points in a line and to fit them in
 *  packed form width-6 has to be multiple of 8. If not then last byte in each
 *  line contains the few extra bits having zero
 *  example if width = 400, then width - 6 = 394. and outwidth would
 *  ROUNDUP(394/8) = 50 and 6 upper bits in last byte would be 0. First byte indicates
 *  cornerness of pixel 3 (bit0),4,5,6,7,8,9,10 (bit7) and it continues...
 *
 *  @param [in]    threshold : Threshold for corner detection
 *  @param [in]    pitch  : Pitch of input buffer
 *  @param [in]    in_w : Width of input buffer for which corner detction has
 *                 to be performed
 *  @param [in]    in_h : Height of input buffer for which corner detction has
 *                 to be performed
 *  @return        None
 *******************************************************************************
 */
#include <stdint.h>

void vcop_fast9_cn
(
 uint8_t *input,
 uint8_t *output,
 uint8_t threshold,
 uint32_t pitch,
 uint32_t in_w,
 uint32_t in_h
) ;
