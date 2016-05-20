/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_weight_computation_cn.h                                 */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*     function for computing weights corresponding to different feature/key*/
/*     point. These weights will be used during bilinear interpolation      */
/*                                                                          */
/*     vcop_weight_computation_cn                                           */
/*         This is the c-reference for the vcop_weight_computation_cn       */
/*         kernel. This routine accepts an X coordinate and Y coordinate    */
/*         lists of length 'numKeyPoints' and computes weights used for     */
/*         bilinear interpolation of image or gradient pixels               */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_weight_computation_cn                                      */
/*     (                                                                    */
/*        unsigned short    *pXYList,                                       */
/*        unsigned char     *pOutWts,                                       */
/*        unsigned short     numKeyPoints,                                  */
/*        unsigned short     qFormatMaxFactor                               */
/*        unsigned short     outputStride                                   */
/*     )                                                                    */
/*                                                                          */
/*     pXYList          : Pointer to (X,Y) Coordinate list of key points    */
/*     pOutWts          : Pointer to output weights for each key point      */
/*                        Buffer Size = 4 * outputStride                    */
/*                        w0, w1, w2, w3 are four outputs for key point     */
/*     numKeyPoints     : Number of key points                              */
/*     qFormatMaxFactor : Maximum scale factor for given Q format           */
/*                        Q4 format => 4 bits for fraction,                 */
/*                        qFormatMaxFactor = (2)^4 - 1 = 15                 */
/*     outputStride     : Stride in the output buffer, should be greater    */
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

void vcop_weight_computation_cn
(
    unsigned short    *pXYList,
    unsigned short    *pOutWts,
    unsigned short     numKeyPoints,
    unsigned short     qFormatMaxFactor,
    unsigned short     truncateBits,
    unsigned short     outputStride
)
{
    int i;
    unsigned short dx, dy, w0, w1, w2, w3;

    for(i = 0; i < numKeyPoints; i++)
    {
        dx = pXYList[2*i] % (qFormatMaxFactor + 1);
        dy = pXYList[2*i+1] % (qFormatMaxFactor + 1);

        w0 = (int)dx * dy;
        w1 = (int)(qFormatMaxFactor - dx) * dy;
        w2 = (int)dx * (qFormatMaxFactor - dy);
        w3 = (int)(qFormatMaxFactor - dx) * (qFormatMaxFactor - dy);

        pOutWts[i]                    = (w0 >> truncateBits);
        pOutWts[outputStride + i]     = (w1 >> truncateBits);
        pOutWts[2 * outputStride + i] = (w2 >> truncateBits);
        pOutWts[3 * outputStride + i] = (w3 >> truncateBits);
    }
}
