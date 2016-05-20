/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#ifndef _EVE_DMA_TEST_DATA_H
#define _EVE_DMA_TEST_DATA_H  1

extern unsigned int src[64]; 
extern unsigned int dst_1[64];
extern unsigned int dst_2[80];
extern unsigned int dst_3[64];
extern unsigned int dst_4[64];
extern unsigned int dst_5[64];
extern unsigned int dst_6[96];
extern unsigned int dst_7[160];
extern unsigned int dst_8[64];

/*-----------------------------------------------------------------------*/
/* Have seperate destination arrays for the expected results.            */
/*-----------------------------------------------------------------------*/

extern unsigned int e_dst_1[64]; 
extern unsigned int e_dst_2[80]; 
extern unsigned int e_dst_3[64]; 
extern unsigned int e_dst_4[64]; 
extern unsigned int e_dst_5[64]; 
extern unsigned int e_dst_6[96]; 
extern unsigned int e_dst_7[160];
extern unsigned int e_dst_8[64]; 


/*-----------------------------------------------------------------------*/
/*  Maintain an array of sources, dests, num_bytes for 6 1d -> 1d lnkd.  */
/*  transfers.                                                           */
/*-----------------------------------------------------------------------*/

extern unsigned int *src_1d_1d[6];  
extern unsigned int *dst_1d_1d[6];  
extern int  num_bytes_1d_1d[6];     

extern unsigned int *src_1d_2d[6]; 
extern unsigned int *dst_1d_2d[6]; 
extern int num_bytes_1d_2d[6]; 
extern int num_lines_1d_2d[6]; 
extern int pitch_1d_2d[6]; 
#endif

