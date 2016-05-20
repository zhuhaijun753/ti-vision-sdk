/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|         Copyright (c) 2007-2012 Texas Instruments Incorporated           |**
**|                        ALL RIGHTS RESERVED                               |**
**|                                                                          |**
**| Permission to use, copy, modify, or distribute this software,            |**
**| whether in part or in whole, for any purpose is forbidden without        |**
**| a signed licensing agreement and NDA from Texas Instruments              |**
**| Incorporated (TI).                                                       |**
**|                                                                          |**
**| TI makes no representation or warranties with respect to the             |**
**| performance of this computer program, and specifically disclaims         |**
**| any responsibility for any damages, special or consequential,            |**
**| connected with the use of this program.                                  |**
**|                                                                          |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/
#ifndef VCOP_HOUGH_FOR_LINES_CN_H_
#define VCOP_HOUGH_FOR_LINES_CN_H_


/* ==================================================
 *  @func     vcop_hough_for_lines_cn
 *
 *  @desc     Reference C implementation to  voted array of rho ( for fix theta)
 *                for all (listSize) the edge list points given as input
 *
 *  @inputs   This kernel takes following Inputs
 *                  pEdgeMapList :
 *                          Pointer to the edge list which is in packed format with x coordinate followed by y.
 *                          Both x and y are 16 bit quantity. Size of this buffer should be listSize * 2 * sizeof(uint16_t)
 *                  pCosSinThetaMulNormQ15 :
 *                          This is pointer to the buffer which contains precalculated values of cos(theta) * normFactor
 *                           followed by sin(theta) * normactor which are  signed quantity in Q15 format.  Where
 *                           normactor = (rhoMaxLength / (2 * diameter)
 *                           diameter = sqrt( imgWidth^2 + imgHeight ^2 ) which can be approximated to
 *                                             sqrt(2) * max (imgWidth, imgHeight)
 *                           Size of this array should be 2 * sizeof(uint16_t)
 *                  listSize :
 *                          Size of edge list in terms on number of edges
 *                  rhoMaxLength :
 *                          Maximum value which rho could take
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                  intermIndexArray :
 *                          This is pointer  to an intermediate scratch buffer which contains the rho values calculated
 *                          for each edge point in the list. Size of this buffer should be (listsize * uint16_t)
 *
 *  @outputs   This kernel produce following outputs
 *                  votedRhoArray:
 *                          Pointer to the buffer which will store voted rho ( per theta). Size of this buffer
 *                          should be (rhoMaxLength * 2 )
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_hough_for_lines_cn
(
  unsigned short        * pEdgeMapList,
  short                 * pCosSinThetaMulNormQ15,
  unsigned short        * intermIndexArray,
  unsigned short        * votedRhoArray,
  unsigned short          listSize,
  unsigned short          rhoMaxLength
);

/* ==================================================
 *  @func     vcop_merge_voted_rho_array_cn
 *
 *  @desc     Referrence C code to merge two voted rho array
 *
 *  @inputs   This kernel takes following Inputs
 *                  votedRhoArrayCurr:
 *                          Pointer to the buffer which contain  voted rho ( per theta) for current theta. Size of this buffer
 *                          should be (rhoMaxLength * (uint16_t) )
 *                  rhoMaxLength :
 *                          Maximum value which rho could take( should be same as the one used in previous kernel)
 *
 *  @outputs   This kernel produce following outputs
 *                  votedRhoArray :
 *                          Pointer to the buffer containing which will contains updated voted rho ( per theta). Size of this buffer
 *                          should be (rhoMaxLength * sizeof(uint16_t))
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_merge_voted_rho_array_cn
(
  unsigned short *  votedRhoArrayCurr,
  unsigned short *  votedRhoArray,
  unsigned short    rhoMaxLength
);

#endif /* VCOP_HOUGH_FOR_LINES_CN_H_ */


