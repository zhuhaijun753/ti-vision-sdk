/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_weight_address_bilinear_interpolation_cn.h              */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*     function for computing weights and base address of each block        */
/*     corresponding to different feature/key point. These weights and      */
/*     updated base address will be used during bilinear interpolation of   */
/*     frame for which the base address and weights change due to iterative */
/*     update of the X and Y coordinates such as in LK tracker              */
/*                                                                          */
/*     vcop_weight_address_bilinear_interpolation_cn                        */
/*         This is the c-reference for the vcop_weight_address_bilinear     */
/*         _interpolation_cn kernel. This routine accepts an X coordinate,  */
/*         Y coordinate lists of length 'numKeyPoints' along with base      */
/*         address of each block and computes weights and updated base      */
/*         address that will be used for bilinear interpolation of image    */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_weight_address_bilinear_interpolation_cn                   */
/*     (                                                                    */
/*       unsigned short    *pXYList,                                        */
/*       unsigned int      *pBaseAddrList,                                  */
/*       unsigned char     *pOutWts,                                        */
/*       unsigned int      *pOutBaseAddress,                                */
/*       unsigned short     numKeyPoints,                                   */
/*       unsigned short     qFormatMaxFactor,                               */
/*       unsigned short     qShift,                                         */
/*       unsigned short     blkStride,                                      */
/*       unsigned short     outputStride                                    */
/*     )                                                                    */
/*                                                                          */
/*     pXYList          : Pointer to (X,Y) Coordinate list of key points    */
/*     pBaseAddrList    : Pointer to base address list of key points        */
/*     pOutWts          : Pointer to output weights for each key point      */
/*                        Buffer Size = 4 * outputStride                    */
/*                        w0, w1, w2, w3 are four outputs for key point     */
/*     pOutBaseAddress  : Pointer to updated base address output for each   */
/*                        key point                                         */
/*     numKeyPoints     : Number of key points                              */
/*     qFormatMaxFactor : Maximum scale factor for given Q format           */
/*                        Q4 format => 4 bits for fraction,                 */
/*                        qFormatMaxFactor = (2)^4 - 1 = 15                 */
/*     qShift           : Number of fractional bits in X,Y coordinates      */
/*     blkStride        : Stride of the block input                         */
/*     outputStride     : Stride of the output buffer, should be greater    */
/*                        than or equal to 'numKeyPoints'                   */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     @author Venkat R Peddigari (a0393744@ti.com)                         */
/*                                                                          */
/*     @version 1.0 (November 2013) : Base version.                         */
/*                                                                          */
/*==========================================================================*/

#include <stdio.h>
#include <string.h>

#define PWID 7

void vcop_weight_address_bilinear_interpolation_cn
(
    unsigned short    *pXList,
    unsigned short    *pYList,
    unsigned int      *pBaseAddrList,
    unsigned int      *pOutAddrList,
    unsigned short     *pOutWts,
    unsigned int      *pOutBaseAddress,
    unsigned short    *pParamBlkOffsetVec,
    unsigned short     numKeyPoints,
    unsigned short     qFormatMaxFactor,
    unsigned short     truncateBits,
    unsigned short     qShift,
    unsigned short     blkStride,
    unsigned short     outputStride
)
{
    int i;
    unsigned short dx, dy, w0, w1, w2, w3;
    short x_int, y_int;

    for(i = 0; i < numKeyPoints; i++)
    {
        dx = pXList[i] & (qFormatMaxFactor);
        dy = pYList[i] & (qFormatMaxFactor);
        x_int = (pXList[i] >> qShift)-(PWID/2);
        y_int = (pYList[i] >> qShift)-(PWID/2);

        if(x_int < 0)
        {
            x_int = 0;
        }

        if(y_int < 0)
        {
            y_int = 0;
        }
 
        /*---------------------------------------------------------------
        If the flow vector points to the regoin outside the valid search 
        region then the flow vector will not be updated by the next 
        iterartion. The address generated by this kerenl will be only
        used by interpolatrion kernel and the output is iignored. 
        So it is ok to point the address to start of the buffer
        -----------------------------------------------------------------*/
        if((x_int+(3*(PWID/2))) >= blkStride)
        {
            x_int = 0;
        }

        if((y_int+(3*(PWID/2))) >= blkStride)
        {
            y_int = 0;
        }

        w0 = dx * dy;
        w1 = (qFormatMaxFactor - dx) * dy;
        w2 = dx * (qFormatMaxFactor - dy);
        w3 = (qFormatMaxFactor - dx) * (qFormatMaxFactor - dy);

        pOutWts[i]                    = w0 >> truncateBits;
        pOutWts[outputStride + i]     = w1 >> truncateBits;
        pOutWts[2 * outputStride + i] = w2 >> truncateBits;
        pOutWts[3 * outputStride + i] = w3 >> truncateBits;

        //Specifies offset in bytes, should be multiple of 4 bytes
        //need to divide by 4 bytes since the base address is unsigned int data type
        pOutBaseAddress[(pParamBlkOffsetVec[i]>>2)] = pBaseAddrList[i] + y_int * blkStride + x_int;
        pOutBaseAddress[(pParamBlkOffsetVec[i]>>2)+1] = pBaseAddrList[i] + y_int * blkStride + x_int + 1;
        pOutBaseAddress[(pParamBlkOffsetVec[i]>>2)+2] = pBaseAddrList[i] + (y_int + 1) * blkStride + x_int;
        pOutBaseAddress[(pParamBlkOffsetVec[i]>>2)+3] = pBaseAddrList[i] + (y_int + 1) * blkStride + x_int + 1;
        pOutBaseAddress[(pParamBlkOffsetVec[i]>>2)+4] =  pOutAddrList[i];
    }
}
