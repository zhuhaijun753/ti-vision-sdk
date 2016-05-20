/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*-----------------------------------------------------------------------*/
/*  NAME : ROI_copy_cpu.c                                                */
/*                                                                       */
/*  DESCRIPTION:                                                         */
/*                                                                       */
/*  void ROI_copy_cpu                                                    */
/*  (                                                                    */
/*      unsigned char *InputImg,   // Input image                        */
/*      unsigned char *ROI_blocks, // Output image                       */
/*      unsigned int  *ROI_offset, // ROI offsets in input               */
/*      unsigned int  num_roi,     // # of ROI blocks                    */
/*      unsigned int  num_iter,    // # of times all ROI are transferred */
/*      unsigned int  blkw,        // Block width                        */
/*      unsigned int  blkh,        // Block height                       */
/*      unsigned int  img_pitch    // Image pitch                        */
/*  )                                                                    */
/*                                                                       */
/*  This routine accepts a pointer to an array of linear image offsets   */
/*  to a series of ROI blocks, and copies the blocks contiguously to an  */
/*  output array per the illustration below.                             */
/*                                                                       */
/*  "Input image w 6 ROI in ext mem"            "6 ROI in ext mem"       */
/*                                              "transferred twice"      */
/*   ------------------------------                                      */
/*  | |E|                    |F|   |                 |A|                 */
/*  |     |A|                      |                 |B|                 */
/*  |                              |                 |C|                 */
/*  |               |D|            |      --->       |D|                 */
/*  |                              |                 |E|                 */
/*  | |C|                    |B|   |                 |F|                 */
/*  |                              |                 |A|                 */
/*   ------------------------------                  |B|                 */
/*                                                   |C|                 */
/*                                                   |D|                 */
/*                                                   |E|                 */
/*                                                   |F|                 */
/*                                                                       */
/* This routine will transfer "num_roi" ROI blocks "num_iter" times and  */ 
/* is used to verify EDMA with linking transfers.                        */
/*                                                                       */  
/*=======================================================================*/
/*  Texas Instruments Incorporated 2012.                                 */
/*-----------------------------------------------------------------------*/

void ROI_copy_cpu
(
    unsigned char *InputImg, 
    unsigned char *ROI_blocks, 
    unsigned int *ROI_offset, 
    unsigned int num_roi, 
    unsigned int num_iter, 
    unsigned int blkw, 
    unsigned int blkh, 
    unsigned int img_pitch
)
{
    int i, j, y, x;

    for(i = 0; i < num_iter; i++)
    {
        for(j = 0; j < num_roi; j++)
        {
            for(y = 0; y < blkh; y++)
            {  
                for(x = 0; x < blkw; x++)
                {
                    ROI_blocks[(i*num_roi*blkw*blkh) + (j*blkw*blkh) + (y*blkw) + x] = InputImg[ROI_offset[j] + (y*img_pitch) + x];
                } 
            }
        }
    }
}
