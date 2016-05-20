/*--------------------------------------------------------------------------*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_copy_data_per_cinit                                             */
/*                                                                          */
/*    void vcop_copy_data_c (                                               */
/*                            unsigned char *Y_in,                          */  
/*                            unsigned char *Y_out,                         */
/*                            int block_w,                                  */
/*                            int block_h                                   */
/*                          )                                               */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*            This routine accepts a pointer to a greyscale image declared  */
/*     as Y_in and copies its data to the ouput array declared as Y_out.    */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*--------------------------------------------------------------------------*/



#ifndef _vcop_copy_data_cinit
#define _vcop_copy_data_cinit  1

void vcop_copy_data_cinit
(               
    unsigned char *In,  
    unsigned char *Out, 
    int r_w,                    
    int r_h   
    );

#endif
