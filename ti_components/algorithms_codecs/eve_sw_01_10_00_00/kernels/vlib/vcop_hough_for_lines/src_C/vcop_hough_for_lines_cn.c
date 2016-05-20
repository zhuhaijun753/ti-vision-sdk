/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#include <stdio.h>
#include <stdlib.h>

#define round(x,n) ( (x + ( 1 << (n-1))) / (1 << n))


void vcop_hough_for_lines_cn
(
  unsigned short        * pEdgeMapList,
  short                 * pCosSinThetaMulNormQ15,
  unsigned short        * intermIndexArray,
  unsigned short        * votedRhoArray,
  unsigned short          listSize,
  unsigned short          rhoMaxLength
)
{
  int rhoCount;
  int           listCount;
  unsigned int  rhoQ15, rho;
  short       cosMulNormQ15;
  short       sinMulNormQ15;
  unsigned int normFactMulDiamQ15;
  /* Find the diameter of image by considering it to be a square image */

  /* Normalisation factor = rhoMaxLength/(diameter * 2 ) */
  /* Division by 2 * diameter because rho value can range from -diamter to +diameter,hence to rho range to be
  positive we add 2*diameter to rho , which is causing this division by 2*diameter */

  /* normFactMulDiam = Normalisation factor  * diameter */
  /* normFactMulDiam = (rhoMaxLength/(diameter * 2 ))  * diameter */
  /* normFactMulDiam = (rhoMaxLength / 2) */
  normFactMulDiamQ15 = ( rhoMaxLength << 15 ) / 2;

  cosMulNormQ15 = pCosSinThetaMulNormQ15[0];
  sinMulNormQ15 = pCosSinThetaMulNormQ15[1];

  /* Loop 1 : Find the rho values for corresponding to the current theta for list size edge elements*/
  for ( listCount = 0 ; listCount < listSize; listCount++ )
  {
    /* rho = x.cos(theta) + y.sin(theta) */
    /* normalized rho = ( rho + diameter)*normFactor */
    /* normalized rho  = rho * normFactor + diameter * normFactor */

    rhoQ15 = pEdgeMapList[listCount * 2] * cosMulNormQ15 +
                  pEdgeMapList[(listCount * 2) + 1] * sinMulNormQ15;


    /* Add diameter to rho to make  rho lie between 0 to 2*diameter as rho can lie between -diamter to + diameter
    and then use normalization factor to fit it into the range (rhoMaxLength) specified by user */
    /* rhoQ15 = (rhoQ8 + diameterQ8) * normFactorQ8; */

    rhoQ15 += (normFactMulDiamQ15);
    /* round rhoQ15 around 15 bits */

    rho = round(rhoQ15, 15);

    intermIndexArray[listCount] = rho;
  }

  /*Loop 2 : Initialize output vote array to 0 */
  for ( rhoCount = 0; rhoCount< rhoMaxLength; rhoCount++)
  {
    votedRhoArray[rhoCount] = 0;
  }

  /*Loop 3 : Update votedRhoArray based on the index calculated in Loop 1 */
  for ( listCount = 0 ; listCount < listSize; listCount++ )
  {
    votedRhoArray[intermIndexArray[listCount]]++;
  }



}


void vcop_merge_voted_rho_array_cn
(
  unsigned short *  votedRhoArrayCurr,
  unsigned short *  votedRhoArray,
  unsigned short    rhoMaxLength
)
{

  int rhoCount;

  /*Loop 4 : Merge Previous histogram into current one*/
  for ( rhoCount = 0; rhoCount < rhoMaxLength; rhoCount++)
  {
    votedRhoArray[rhoCount] += votedRhoArrayCurr[rhoCount];
  }
}



