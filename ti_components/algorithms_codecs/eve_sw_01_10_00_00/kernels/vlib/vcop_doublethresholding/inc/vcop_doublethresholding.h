/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#ifndef _vcop_doublethresholding_CN 
#define _vcop_doublethresholding_CN  1

void vcop_doublethresholding_cn
(
	short pInMag[],
	short edgeMap[],
    int numStrongEdges,
    unsigned short width,
    unsigned short pitch,
	unsigned short height,
	unsigned char loThresh,
	unsigned char hiThresh,
	unsigned int pos_frm,
	short edgeMap_out[]
);

#endif
