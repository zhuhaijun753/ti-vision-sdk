/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#define POSSIBLE_EDGE 127
#define ELEMSZ          sizeof(*pInMag)


/*******************************************************************************
  This routine finds edges that are above some high threshhold or
* are connected to a high pixel by a path of pixels greater than a low
* threshold.
*******************************************************************************/
void vcop_doublethresholding_cn
(
	short pInMag[],
    short edgeMap[],
    unsigned short width,
    unsigned short pitch,
    unsigned short height,
	unsigned char loThresh,
    unsigned char hiThresh,
	short edgeMap_out[]
)
{	int y; 
	int x;
	int pos;
	unsigned char addEdge,value,posEdge;
	unsigned char belowLow,aboveHigh;

	/////////////////////////////////////////////////////////////////////////////
	// Build edge list; pre-screen for magnitude values that are below the LOW 
	// THRESHOLD, which makes edge following easier in subsequent stage
	
	for (y=0; y < height; y++)
	{
		for (x=0; x < pitch; x++)
		{

			belowLow = (pInMag[x+y*pitch] >= loThresh) ;
            aboveHigh = (pInMag[x+y*pitch] >= hiThresh);
            value = edgeMap[x+y*pitch];
            posEdge = (value == POSSIBLE_EDGE);
			addEdge  = posEdge && aboveHigh;
  			value  = ( value + (addEdge *128) )*belowLow;  // adds 128 to 127, i.e. an EDGE == 255
            edgeMap_out[x+y*pitch]=value;
		}

	}

}

