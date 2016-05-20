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
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define POSSIBLE_EDGE 127 



int vcop_edgeRelaxation_cn(
                     unsigned char *edgeMap, 
    				 unsigned int * restrict strongEdgeListPtr,
                     int * numStrongEdges,
                     unsigned short width)
{	
	int checkLocation;

	unsigned char addTL;
	unsigned char addTC;
	unsigned char addTR;
	unsigned char addLC;
	unsigned char addRC;
	unsigned char addBL;
	unsigned char addBC;
	unsigned char addBR;

	short offsetTL;
	short offsetTC;
	short offsetTR;
	short offsetRC;
	short offsetBR;
	short offsetBC;
	short offsetBL;
	short offsetLC;

	unsigned char * restrict mapTL;
	unsigned char * restrict mapTC;
	unsigned char * restrict mapTR;
	unsigned char * restrict mapLC;
	unsigned char * restrict mapRC;
	unsigned char * restrict mapBL;
	unsigned char * restrict mapBC;
	unsigned char * restrict mapBR;
	unsigned char * restrict mapC;

    int numItems = * numStrongEdges;

	offsetTL = - 1 - width;
	offsetTC = - 0 - width;
	offsetTR = + 1 - width;
	offsetRC = + 1;
	offsetBR = + 1 + width;
	offsetBC = - 0 + width;
	offsetBL = - 1 + width;
	offsetLC = - 1;

	checkLocation = strongEdgeListPtr[numItems - 1];  

	while (--numItems)
	{
		mapC = edgeMap + checkLocation;

		mapTL = mapC + offsetTL;
		mapTC = mapC + offsetTC;
		mapTR = mapC + offsetTR;
		mapLC = mapC + offsetLC;
		mapRC = mapC + offsetRC;
		mapBR = mapC + offsetBR;
		mapBC = mapC + offsetBC;
		mapBL = mapC + offsetBL;

        addTL = (*mapTL == POSSIBLE_EDGE);
        addTC = (*mapTC == POSSIBLE_EDGE);
        addTR = (*mapTR == POSSIBLE_EDGE);
        addRC = (*mapRC == POSSIBLE_EDGE);
        addBR = (*mapBR == POSSIBLE_EDGE);
        addBC = (*mapBC == POSSIBLE_EDGE);
        addBL = (*mapBL == POSSIBLE_EDGE);
        addLC = (*mapLC == POSSIBLE_EDGE);

        *mapTL += addTL << 7;
        *mapTC += addTC << 7;
        *mapTR += addTR << 7;
        *mapRC += addRC << 7;
        *mapBR += addBR << 7;
        *mapBC += addBC << 7;
        *mapBL += addBL << 7;
        *mapLC += addLC << 7;
       
		strongEdgeListPtr[numItems] = checkLocation + offsetTL;
		numItems += addTL;
		strongEdgeListPtr[numItems] = checkLocation + offsetTC;
		numItems += addTC;
		strongEdgeListPtr[numItems] = checkLocation + offsetTR;
		numItems += addTR;
		strongEdgeListPtr[numItems] = checkLocation + offsetRC;
		numItems += addRC;
		strongEdgeListPtr[numItems] = checkLocation + offsetBR;
		numItems += addBR;
		strongEdgeListPtr[numItems] = checkLocation + offsetBC;
		numItems += addBC;
		strongEdgeListPtr[numItems] = checkLocation + offsetBL;
		numItems += addBL;
		strongEdgeListPtr[numItems] = checkLocation + offsetLC;
		numItems += addLC;
        
		checkLocation = strongEdgeListPtr[numItems - 1];
	}

  return 0;
}

