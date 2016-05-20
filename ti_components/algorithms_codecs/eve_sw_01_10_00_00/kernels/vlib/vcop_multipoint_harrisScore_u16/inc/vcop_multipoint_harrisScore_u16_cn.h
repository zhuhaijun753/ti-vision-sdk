/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     @file : vcop_multipoint_harrisScore_u16_cn                           */
/*                                                                          */
/*     @brief : This is the C-reference for the vcop_multipoint_harrisScore */
/*         _u16 kernel. This routine accepts a buffer containing sequence   */
/*         of 'numPoints' 8-bit image blocks of dimension (winWidth+2) by   */
/*         (winHeight+2). The function computes 16-bit Harris score for     */
/*         each of the numPoints points based on the winWidth x winHeight   */
/*         X and Y-gradients and packs this with the image pyramid level    */
/*         and a unique index starting with user specified start_idx.       */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_multipoint_harrisScore_u16_cn                              */
/*     (                                                                    */
/*         uint8_t  *pImgBlocks,                                            */
/*         uint16_t *pHarrisScore,                                          */
/*         uint16_t  numPoints,                                             */
/*         uint8_t   winWidth,                                              */
/*         uint8_t   winHeight,                                             */
/*         uint16_t  inputStride,                                           */
/*         uint16_t  interBlockOffset,                                      */
/*         uint16_t  sensitivityParam,                                      */
/*         uint8_t   level,                                                 */
/*         uint16_t  start_id                                               */
/*     )                                                                    */
/*                                                                          */
/*     pImgBlocks       : Image blocks. 'numPoints' image blocks of size    */
/*                        (winWidth+2) x (winHeight+2) are expected.        */
/*     pHarrisScore     : Output Harris Score. The 16-bit MSB contains the  */
/*                        computed score. Next 5-bits contain the image     */
/*                        pyramid level and last 11-bits contain an id.     */
/*     numPoints        : Number of points for which score is computed      */
/*     winWidth         : Width of window used for score computation        */
/*     winHeight        : Height of window used for score computation       */
/*     interBlockOffset : Offset between two adjacent image blocks in bytes */
/*     sensitivityParam : Harris score tunable sensitivity parameter        */
/*     level            : Image pyramid level information to be packed with */
/*                        in bits 12-15 of Harris score                     */
/*     start_id         : Start value of index to be packed with the scores */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     @version 1.0 (Nov 2013) : Base version.                              */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_MULTIPOINT_HARRISSCORE_U16_CN
#define _VCOP_MULTIPOINT_HARRISSCORE_U16_CN

void vcop_multipoint_harrisScore_u16_cn
(
    uint8_t    *pImgBlocks,
    uint16_t   *pHarrisScore,
    uint16_t    numPoints,
    uint8_t     winWidth,
    uint8_t     winHeight,
    uint16_t    inputStride,
    uint16_t    interBlockOffset,
    uint16_t    sensitivityParam,
    uint16_t    start_id
);

#endif /* _VCOP_MULTIPOINT_HARRISSCORE_U16_CN */
