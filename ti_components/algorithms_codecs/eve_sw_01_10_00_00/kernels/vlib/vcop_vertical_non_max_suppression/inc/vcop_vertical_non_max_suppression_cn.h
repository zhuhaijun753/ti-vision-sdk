/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME : vcop_vertical  _non_max_suppression: header file              */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2013 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*
@param  *corners    Pointer to the corner list

@param num_corners  Number of corners

@param *nms_x_score Pointer to score input

@param *nms_y_corners   Pointer to the corner list

@param *nms_score   Pointer to output score, packed with ID (score, ID - 32 bit)

*/

void vertical_nms(unsigned int* corners, unsigned int num_corners, unsigned short* nms_x_score, unsigned short* nms_id, unsigned short* nms_y_score, unsigned short* nms_y_corners, unsigned int* nms_corners, unsigned int* nms_score);

