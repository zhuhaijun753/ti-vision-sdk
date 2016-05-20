/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME : vcop_fast9_score : header file                                */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*
  @param *pIn               Pointer to input image 8x8 block around the key point
  
  @param num_corners    Number of corners to compute score
  
  @param *lut_index       Pointer to look up table of index pointing to the 16 pixels in the circular ring
                        
  @param Thr                Fast9threshold
  
  @param *sad_scores    SAD based output fast9 score

  @param *thesh_scores Threshold based output fast9 score
*/

/* Function interface to compute SAD based fast9 score*/
void fast9_sad_score(unsigned char* pIn, short num_corners, unsigned char* lut_index, int Thr, unsigned short* sad_scores);

/* Function interface to compute threshold based fast9 score */
void fast9_thresh_score(unsigned char* pIn, short num_corners, unsigned char* lut_index, int Thr, unsigned short* thresh_scores);
