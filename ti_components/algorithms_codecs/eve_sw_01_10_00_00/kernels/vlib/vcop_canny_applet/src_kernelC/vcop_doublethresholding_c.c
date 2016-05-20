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
 
// ======================================================================== 
//																			
//  AUTHORS         					  	            
//		Darnell J. Moore	(DJM)			       		            
//									    
//  CONTACT                						    
//		djmoore@ti.com, +1 214 480 7422
//    DSP Solutions R&D Center, Dallas, TX
//		Video & Image Processing Laboratory
//    Embedded Vision Branch
//									    
//  FILE NAME								    
//		EVref_cannyFrontEnd.c							    
//									    
//  REVISION HISTORY                                                        
//		Jan 2008 * DJM wrote original version 
//		Jun 2008 * DJM optimized
//									    
//  DESCRIPTION                                                             
//		Hysteresis Thresholding used for Canny Edge detector
//
//  NOTES
//    This function performs Hysteresis Thresholding
// ------------------------------------------------------------------------ 
//         Copyright (c) 2008 Texas Instruments, Incorporated.           
//                           All Rights Reserved.                           
// ======================================================================== 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
//#include "VLIB_hysteresisThresholding.h"

#define POSSIBLE_EDGE 127 

/*******************************************************************************
  This routine finds edges that are above some high threshhold or
* are connected to a high pixel by a path of pixels greater than a low
* threshold.
*******************************************************************************/
void vcop_doublethresholding_1(short *pInMag, 
                     unsigned char *edgeMap, 
                     unsigned short width, 
                     unsigned short pitch, 
                     unsigned short height,
				     unsigned char loThresh,
                     unsigned char hiThresh,
					 unsigned int pos_frm
                     )
{	int y; 
	int x;
	unsigned char addEdge,value,posEdge;
	unsigned char belowLow,aboveHigh;

	for (y=0; y < height; y++) 
	{
		for (x=0; x < width; x++) 
		{
			belowLow = (pInMag[x+y*pitch] >= loThresh) ;
            aboveHigh = (pInMag[x+y*pitch] >= hiThresh);
            value = edgeMap[x+y*pitch];
            posEdge = (value == POSSIBLE_EDGE);
			addEdge  = posEdge && aboveHigh;
  			value  = ( value + (addEdge *128) )*belowLow;  // adds 128 to 127, i.e. an EDGE == 255
            edgeMap[x+y*pitch]=value;

		}
	}
	

}

int vcop_doublethresholding_2(
                     unsigned char *edgeMap, 
    				 unsigned int * strongEdgeListPtr,
                     int * numStrongEdges,
                     unsigned short width, 
                     unsigned short pitch, 
                     unsigned short height,
                     unsigned int pos_frm
                     )
{	int y; 
	int x;
	int numItems;
	unsigned char value;

	numItems = *numStrongEdges;

	for (y=0; y < height; y++) 
	{
		for (x=0; x < width; x++) 
		{

            value = edgeMap[x+y*pitch];
			if (value == 255)
            strongEdgeListPtr[numItems++] = pos_frm + x+y*pitch; 

		}
	}	

  *numStrongEdges =  numItems;   

  return 0;

}

