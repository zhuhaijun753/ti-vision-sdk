/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef VCOP_CANNY_NON_MAXIMUM_SUPPRESSION_CN
#define VCOP_CANNY_NON_MAXIMUM_SUPPRESSION_CN

/* ==================================================
 *  @func     vcop_canny_bin_indexing
 *
 *  @desc     This function implements natural C of binning of edges into 4 cases:
 *                Case 1: Edges lying between -22.5 to +22.5 : output Index < 4
 *                Case 2: Edges lying between +22.5 to +67.5 : output Index == 4
 *                Case 3: Edges lying between +67.5 to +112.5 : output Index > 5
 *                Case 1: Edges lying between +112.5  to +157.5 : output Index == 5
 *                This kernel uses following three conditions
 *                Condition 1 :  abs(gy) > gx * tan(22.5)
 *                Condition 1 :  abs(gy) > gx * tan(67.5)
 *                Condition 3 :  Gx^Gy < 0
 *
 *                Following is the truth tables implemented in this kernel:
 *                               Condition1   Condition2  Condition3
 *                 Case 1    0                  0               0
 *                 Case 1    0                  0               1
 *                 Case 1    0                  1               0
 *                 Case 1    0                  1               1
 *                 Case 2    1                  0               0
 *                 Case 4    1                  0               1
 *                 Case 3    1                  1               0
 *                 Case 3    1                  1               1
 *
 *  @inputs   This kernel takes following Inputs
 *                  pGx :
 *                          Gradient in X direction
 *
 *                  pGy :
 *                          Gradient in Y direction
 *
 *                  computeWidth :
 *                          Compute width
 *                  computeHeight :
 *                          Compute height
 *                  pitch :
 *                          Pitch of the input
 *
 *  @scratch   This func needs  following scratch buffers
 *                  NONE
 *
 *  @outputs   This VCOP_CANNY_NON_MAXIMUM_SUPPRESSION_CN produce following outputs
 *                  pIndex :
 *                          This is the pointer which contains the index corresponding to the edge as
 *                           described in the description
 *
 *  @remarks
 *                NONE
 *
 *  @constraints Following constraints
 *                NONE
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_canny_bin_indexing_cn(
    int16_t   *pGx,
    int16_t   *pGy,
    uint8_t   *pIndex,
    uint16_t   computeWidth,
    uint16_t   computeHeight,
    uint16_t   pitch);

/* ==================================================
 *  @kernel     vcop_canny_nms_max_cases
 *
 *  @desc     This kernel finds the maximum of all the pixel for all 4 cases along the
 *                Direction of edge. 4 cases are described as :
 *                Case 1: Edges lying between -22.5 to +22.5 : output Index < 4
 *                Case 2: Edges lying between +22.5 to +67.5 : output Index == 4
 *                Case 3: Edges lying between +67.5 to +112.5 : output Index > 5
 *                Case 1: Edges lying between +112.5  to +157.5 : output Index == 5
 *
 *  @inputs   This kernel takes following Inputs
 *                  pMag :
 *                          Gradient Magnitude
 *                          Size of this buffer should be ALIGN_2SMID(computeWidth) * computeHeight  * sizeof(int16_t)
 *                  computeWidth :
 *                          Compute width
 *                  computeHeight :
 *                          Compute height
 *                  pitch :
 *                          Pitch of the input
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                  NONE
 *
 *  @outputs   This kernel produce following outputs
 *                  pCase1Max :
 *                          Maximum of the three pixel along the direction of case 1
 *                          Size of this buffer should be  ALIGN_2SMID(computeWidth) * computeHeight
 *                          Output pitch will be same as pitch
 *                  pCase2Max :
 *                          Maximum of the three pixel along the direction of case 2
 *                          Size of this buffer should be  ALIGN_2SMID(computeWidth) * computeHeight
 *                          Output pitch will be same as pitch
 *                  pCase3Max :
 *                          Maximum of the three pixel along the direction of case 3
 *                          Size of this buffer should be  ALIGN_2SMID(computeWidth) * computeHeight
 *                          Output pitch will be same as pitch
 *                  pCase4Max :
 *                          Maximum of the three pixel along the direction of case 4
 *                          Size of this buffer should be  ALIGN_2SMID(computeWidth) * computeHeight
 *                          Output pitch will be same as pitch
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                   NONE
 *
 *  @constraints Following constraints
 *                    NONE
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_canny_nms_max_cases_cn
(
    uint16_t   *pMag,
    uint16_t   *pCase1Max,
    uint16_t   *pCase2Max,
    uint16_t   *pCase3Max,
    uint16_t   *pCase4Max,
    uint16_t computeWidth,
    uint16_t computeHeight,
    uint16_t pitch
);

/* ==================================================
 *  @func     vcop_canny_nms_double_thresholding
 *
 *  @desc     This function uses the previous two functions  to do NMS and also
 *                apply double threshold to give an image whose output is
 *                0 for pixels which are below low threshold
 *                1 for pixels which are above low threshold and below High Threshold
 *                255 for pixels which are above High Threshold
 *
 *
 *  @inputs   This kernel takes following Inputs
 *                  pIndex :
 *                          This is the pointer which contains the index corresponding to the edge as
 *                           described in the description
 *                          Size of this buffer should be  ALIGN_2SMID(computeWidth) * computeHeight
 *                          Output pitch will be same as pitch
 *
 *                  pCase1Max :
 *                          Maximum of the three pixel along the direction of case 1
 *                          Size of this buffer should be  ALIGN_2SMID(computeWidth) * computeHeight
 *                          Output pitch will be same as pitch
 *                  pCase2Max :
 *                          Maximum of the three pixel along the direction of case 2
 *                          Size of this buffer should be  ALIGN_2SMID(computeWidth) * computeHeight
 *                          Output pitch will be same as pitch
 *                  pCase3Max :
 *                          Maximum of the three pixel along the direction of case 3
 *                          Size of this buffer should be  ALIGN_2SMID(computeWidth) * computeHeight
 *                          Output pitch will be same as pitch
 *                  pCase4Max :
 *                          Maximum of the three pixel along the direction of case 4
 *                          Size of this buffer should be  ALIGN_2SMID(computeWidth) * computeHeight
 *                          Output pitch will be same as pitch
 *                  computeWidth :
 *                          Compute width
 *                  computeHeight :
 *                          Compute height
 *                  pitch :
 *                          Pitch of the input
 *                  outputPitch :
 *                          Pitch of the input
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                  NONE
 *
 *  @outputs   This kernel produce following outputs
 *                  pOutVal :
 *                   Gives double thresholded output as
 *                0 for pixels which are below low threshold
 *                1 for pixels which are above low threshold and below High Threshold
 *                255 for pixels which are above High Threshold
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                   NONE
 *
 *  @constraints Following constraints
 *                    NONE
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_canny_nms_double_thresholding_cn
(
    uint8_t    *pIndex,
    uint16_t   *pCase1Max,
    uint16_t   *pCase2Max,
    uint16_t   *pCase3Max,
    uint16_t   *pCase4Max,
    uint8_t    *pOutVal,
    uint8_t     lowThreshold,
    uint8_t     highThreshold,
    uint16_t width,
    uint16_t height,
    uint16_t pitch,
    uint16_t outputPitch
);


#endif /* VCOP_CANNY_NON_MAXIMUM_SUPPRESSION_CN */

/* ======================================================================== */
/*  End of file:  vcop_canny_non_maximum_suppression_cn.h                    */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2012 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */



