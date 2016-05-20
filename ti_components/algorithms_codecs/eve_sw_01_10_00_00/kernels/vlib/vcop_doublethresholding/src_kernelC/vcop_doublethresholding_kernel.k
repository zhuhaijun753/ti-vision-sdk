/*==========================================================================*/
/*                                                                          */
/*            TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION        */
/*                                                                          */
/*  Property of Texas Instruments                                           */
/*  For Unrestricted Internal Use Only                                      */
/*  Unauthorized reproduction and/or distribution is strictly prohibited.   */
/*  This product is protected under copyright law and trade secret law      */
/*  as an unpublished work.                                                 */
/*  Created 2012, (C) Copyright 2012 Texas Instruments.                     */
/*  All rights reserved.                                                    */
/*                                                                          */
/*******************************************************************************
  This routine finds edges that are above some high threshhold or
* are connected to a high pixel by a path of pixels greater than a low
* threshold.
*******************************************************************************/

#define ELEMSZ          sizeof(*pInMag)
#define VECTORSZ		(VCOP_SIMD_WIDTH*ELEMSZ)

void vcop_doublethresholding
(
	__vptr_int16 pInMag,
    __vptr_int16 edgeMap,
           short width,
           short pitch,
           short height,
			char loThresh,
            char hiThresh,
	 __vptr_int16 edgeMap_out
)
{
	__vector addEdge, mag, value, posEdge, belowLow, aboveHigh;
	__vector R0, R1, R2, R3;


	R0 = 128;
	R1 = loThresh;
	R2 = hiThresh;
	R3 = 127;

	/////////////////////////////////////////////////////////////////////////////
	// Build edge list; pre-screen for magnitude values that are below the LOW
	// THRESHOLD, which makes edge following easier in subsequent stage

	for( int I1 = 0; I1 < height; I1++)
    {
    	for( int I2 = 0; I2 < (pitch/VCOP_SIMD_WIDTH); I2++)
    	{
    		__agen Addr = I1*pitch*ELEMSZ + I2*VECTORSZ;


    		mag = pInMag[Addr];
    		value = edgeMap[Addr];
    		
    		posEdge = value == R3;
    		aboveHigh = mag >= R2;
    		
    		belowLow = mag >= R1;
    		addEdge = posEdge & aboveHigh;
    		
    		addEdge *= R0;
    		
    		value += addEdge;
    		
    		edgeMap_out[Addr] = value.predicate(belowLow);
    		
    	}
    }


}
