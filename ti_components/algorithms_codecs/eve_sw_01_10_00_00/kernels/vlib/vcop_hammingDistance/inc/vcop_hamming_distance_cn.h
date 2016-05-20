/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_hamming_distance_cn.h                                   */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*     function namely hamming distance                                     */
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

#ifndef _VCOP_HAMMING_DISTANCE_CN
#define _VCOP_HAMMING_DISTANCE_CN  1

void vcop_hamming_distance_cn
(
    uint8_t           *pString1,            // pointer to first byte array string pointer
    uint8_t           *pString2,            // pointer to second byte array string pointer
    uint32_t           xsize,               // size of each byte array element in bytes
    uint32_t           ysize,               // number of byte array elements with size "xsize" & pitch "xpitch" in first/second string pointer
    uint32_t           mode,                // mode = 0 : Many to one; mode = 1: One to one
    uint32_t           xpitch,              // pitch of each byte array element in bytes
    uint32_t          *pHammingDistance,    // pointer to hamming distance output array
    uint16_t           outStride,
    int16_t            startIdx
);

void vcop_findTwoBestMatches_cn
(
    uint32_t *pHammingDistance,
    uint32_t *pMinDist0,
    uint32_t *pMinDist1,
    uint8_t   stride,
    uint32_t  n
);

void vcop_pickConfidentMatches_cn
(
  uint16_t  *pMinDist0,
  uint16_t  *pMinDist1,
  uint16_t  *pMatchIndex,
  unsigned int   m,
  unsigned short minDistanceThres,
  unsigned short matchConfidence
);

#endif /* _VCOP_HAMMING_DISTANCE_CN */
