/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME : vcop_horizontal_non_max_suppression: header file              */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2013 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*    
  @param *corners       pointer to input key point list (X,Y in packed format 16-bit each)
  
  @param num_corners    number of corners to be processed
  
  @param *scores        pointer to the score for each of the key points in the XY key point list
  
  @param *nms_x_corners Pointer to the suppressed XY list, packed with ID (X,Y,ID - 32 bit data)
  
  @param *nms_x_score   Pointer to the suppressed score
  
*/

void horizontal_nms(unsigned int* corners, unsigned int num_corners, unsigned short* scores, unsigned int* nms_x_corners, unsigned short* nms_x_score);

