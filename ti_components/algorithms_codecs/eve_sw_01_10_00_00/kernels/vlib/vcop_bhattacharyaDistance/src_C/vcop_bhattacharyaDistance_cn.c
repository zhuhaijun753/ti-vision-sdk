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


typedef unsigned char  Uint8;
typedef unsigned short Uint16;
typedef unsigned int   Uint32;

typedef char    Int8;
typedef short   Int16;
typedef int     Int32;

int vcop_bhattacharyaDistance_cn
(
	unsigned short X[],
	unsigned short Y[],
	  	  	   int N,
	  	    Uint32 UBD[]
)

{
	int i, count;
	unsigned int root, remHi, remLo, testDiv;// count;
	unsigned int Z, BD = 0;


	#pragma MUST_ITERATE(4, , )
	for(i=0;i<N;i++){

		Z = X[i] * Y[i];


		root = 0; 	// Clear root
		remHi = 0; 	// Clear high part of partial remainder
		remLo = Z;  // Get argument into low part of partial remainder

		#pragma UNROLL(32)
		#pragma MUST_ITERATE(32, 32, )
		for(count=31;count>=0;count--){

			remHi = (remHi<<2) | (remLo>>30); 	// get lower 2 bits of arg into the high part
//			remHi = (remHi*4) + (remLo>>30); 	// get lower 2 bits of arg into the high part

			remLo <<= 2; 						// get 2 bits of arg
//			remLo = remLo  * 4; 						// get 2 bits of arg

			root <<= 1; 						// Get ready for the next bit in the root
//			root = 2*root;

//			testDiv = (root << 1) + 1; 			// 2*root + 1
			testDiv = (2*root) + 1; 			// 2*root + 1
			if (remHi >= testDiv) {				// if x > (2*r + 1),
				remHi -= testDiv;				// 		x = x - (2*root+1)
				root++;							// 		insert a 1 bit into LSB of root
			}									// else
												//		x is unaletered
												//		insert a 0 bit into LSB of root
		}

		BD = BD + root;
	}

	BD = 1 - BD;

	root = 0; /* Clear root */
	remHi = 0; /* Clear high part of partial remainder */
	remLo = BD; /* Get argument into low part of partial remainder */
	#pragma UNROLL(32)
	#pragma MUST_ITERATE(32, 32, )
	for(count=31;count>=0;count--){
		remHi = (remHi<<2) | (remLo>>30);
		remLo <<= 2; /* get 2 bits of arg */
		root <<= 1; /* Get ready for the next bit in the root */
		testDiv = (root << 1) + 1; /* Test radical */
		if (remHi >= testDiv) {
			remHi -= testDiv;
			root++;
		}
	}

	UBD[0] = BD; //root;
	return 0;
}

