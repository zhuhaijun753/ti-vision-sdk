/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *******************************************************************************
 *  @func          vcop_census_16bits_cn
 *  @brief         This is natural C implementation of census transform
 *  @param [in]    input   : Pointer to input 16-bit image
 *  @param [in]    output  : Pointer to bitpacked output
 *
 *  Output format of the buffer is crtical to know. It is as described
 *  Output stride of the buffer in bytes is at least computeWidth*ROUNDUP( ((winWidth+winHorzStep-1)/winHorzStep)*((winHeight+winVertStep-1)/winVertStep)/8)
 *  OutputHeight of the buffer is computeHeight
 *  The way census transform output is organized is as follow:
 *  For any input pixel input(x,y)
 *  bit#0 is '1' if center pixel input(x,y) is greater or equal than pixel at position input(x-winWidth/2 , y-winHeight/2)), which is the upper-left pixel, else it is '0'
 *  bit#1 is '1' if center pixel input(x,y) is greater or equal than pixel at position input(x-winWidth/2 + winHorzStep, y-winHeight/2), else it is '0'
 *  bit#2 is '1' if center pixel input(x,y) is greater or equal than pixel at position input(x-winWidth/2 + 2*winHorzStep, y+winHeight/2), else it is '0'
 *  etc.
 *  
 *  Most significant bits that correspond to non-existent pixel positions are set to 0.
 *
 *  @param [in]    winWidth : width of the census transform support window.
 *  @param [in]    winHeight : height of the census transform support window.
 *  @param [in]    winHorzStep : horizontal step between each orientation in the support window. Typically 1 or 2.
 *  @param [in]    winVertStep : vertical step between each orientation in the support window. Typically 1 or 2.
 *  @param [in]    computeWidth : Number of horizontal pixels to be filtered, not including winWidth-1 border pixels
 *  @param [in]    computeWidth : Number of vertical pixels to be filtered, not including winWHeight-1 border pixels
 *  @param [in]    inStride : Horizontal stride of the input block in number of pixels. Should be greater or equal to computeWidth + winWidth - 1
 *  @param [in]    outStride : Horizontal stride of the output block in number of bytes. Should be greater or equal to computeWidth*ROUNDUP((winWidth*winHeight)/8)
 *  @return        None
 *******************************************************************************
 */

#ifndef _VCOP_CENSUS_16BITS_CN_H_
#define _VCOP_CENSUS_16BITS_CN_H_

#include <stdint.h>

/*#define _DROP_CENTER_PIXEL*/

#ifdef _DROP_CENTER_PIXEL
#define _CENSUS_WIN_SIZE(winWidth, winHeight) ((((winWidth) + (hStep) -1u)/(hStep)) * (((winHeight) + (vStep) -1u)/(vStep)) -  1u)
#define _IS_NOT_CENTER(l, k, winWidth, winHeight) ((k)!= (winHeight)/2u || (l) != (winWidth)/2u)
#else
#define _CENSUS_WIN_SIZE(winWidth, winHeight, hStep, vStep) ((((winWidth) + (hStep) -1u)/(hStep)) * (((winHeight) + (vStep) -1u)/(vStep)))
#define _IS_NOT_CENTER(l, k, winWidth, winHeight) (1)
#endif

#define CENSUS_COMPARE(a,b) ((a)<=(b))

void vcop_census_16bits_cn
(
        uint16_t *input,
        uint8_t *output,
        uint8_t winWidth, /* windWidth * winHeight msut be > 8 */
        uint8_t winHeight,
        uint8_t winHorzStep,
        uint8_t winVertStep,
        uint16_t computeWidth,
        uint16_t computeHeight,
        uint16_t inStride,
        uint16_t outStride /* in bytes */
);

#endif
