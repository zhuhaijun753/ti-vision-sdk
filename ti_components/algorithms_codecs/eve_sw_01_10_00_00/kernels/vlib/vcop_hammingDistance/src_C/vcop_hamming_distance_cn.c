/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_hamming_distance_cn.c                                   */
/*                                                                          */
/*     @brief : This file contains C reference implementation for hamming   */
/*              distance                                                    */
/*                                                                          */
/*     The following basic hamming distance function is provided:           */
/*     vcop_hamming_distance_cn                                             */
/*           Computes the hamming distance between two input byte array     */
/*           string pointers. Each byte array pointer is represented        */
/*           as depicted below                                              */
/*     Supports the following two modes                                     */
/*       1. mode = 0 :Many-to-One                                           */
/*          pHammingDistance[i] = HammingDistance(bytearr1[i], bytearr2[0]);*/
/*       2. mode = 1 :One-to-One                                            */
/*          pHammingDistance[i] = HammingDistance(bytearr1[i], bytearr2[i]);*/
/*       where i = 0,1,2, ...ySize-1                                        */
/*                                                                          */
/*                 xpitch                             xpitch                */
/*       <----------------------->          <----------------------->       */
/*            xsize                              xsize                      */
/*       <---------->                       <---------->                    */
/*       |-----------------------|          |-----------------------|       */
/*       |bytearr1[0]            |          |bytearr2[0]            |       */
/*       |-----------------------|          |-----------------------|       */
/*       |bytearr1[1]            |          |bytearr2[1]            |       */
/*       |-----------------------|          |-----------------------|       */
/*       |                       |          |                       |       */
/*       |                       |          |                       |       */
/*       |-----------------------|          |-----------------------|       */
/*       |bytearr1[ysize-1]      |          |bytearr2[ysize-1]      |       */
/*       |-----------------------|          |-----------------------|       */
/*           The output is written into pHammingDistance output array.      */
/*                                                                          */
/*     @author Venkat R Peddigari (a0393744@ti.com)                         */
/*                                                                          */
/*     @version 1.0 (July 2013) : Base version.                             */
/*                                                                          */
/*==========================================================================*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define PIX_SORT(a,b) { if ((a)>(b)) PIX_SWAP((a),(b)); }
#define PIX_SWAP(a,b) { uint32_t temp=(a);(a)=(b);(b)=temp; }

void vcop_hamming_distance_cn
(
  uint8_t  *pString1,            // pointer to first byte array string pointer
  uint8_t  *pString2,            // pointer to second byte array string pointer
  uint32_t  xsize,               // size of each byte array element in bytes
  uint32_t  ysize,               // number of byte array elements with size "xsize" & pitch "xpitch" in first/second string pointer
  uint32_t  mode,                // mode = 0 : Many to one; mode = 1: One to one
  uint32_t  xpitch,              // pitch of each byte array element in bytes
  uint32_t *pHammingDistance,    // pointer to hamming distance output array
  uint16_t  outStride,
  int16_t   startIdx
)
{
  uint32_t i = 0, j = 0, val = 0;
  uint16_t dist = 0;

  for(j = 0; j < ysize; j++)
  {
      val = 0;
      dist = 0;
      for(i = 0; i < xsize; i++)
      {
          val = pString1[j*xpitch+i] ^ pString2[j*xpitch*mode+i];

          while (val > 0)
          {
            if (val % 2 != 0)
            {
              ++dist;
            }
            val = val / 2;
          }
      }

      pHammingDistance[j*outStride] = (dist << 16) + startIdx + j;
  }
}

void vcop_findTwoBestMatches_cn
(
    uint32_t *pHammingDistance,
    uint32_t *pMinDist0,
    uint32_t *pMinDist1,
    uint8_t   stride,
    uint32_t  n
)
{
  uint32_t i, j, currDist;

  for(i = 0; i < 16; i++) {
    pMinDist0[i] = 0xFFFFFFFF;
    pMinDist1[i] = 0xFFFFFFFF;
    for(j = 0; j < n; j++) {
      currDist = pHammingDistance[j*stride + i];
      PIX_SORT(pMinDist0[i], currDist);
      PIX_SORT(pMinDist1[i], currDist);
    }
  }
}

void vcop_pickConfidentMatches_cn
(
  uint16_t  *pMinDist0,
  uint16_t  *pMinDist1,
  uint16_t  *pMatchIndex,
  unsigned int   m,
  unsigned short minDistanceThres,
  unsigned short matchConfidence
)
{
  uint32_t i;

  for(i = 0; i < m; i++) {
    pMatchIndex[i] = 0xFFFF;
    if((pMinDist0[2*i + 1] <= minDistanceThres) && (pMinDist0[2*i + 1] <=
       (((1<<15) - matchConfidence)*pMinDist1[2*i + 1])>>15)) {
      pMatchIndex[i] = pMinDist0[2*i];
    }
  }
}

