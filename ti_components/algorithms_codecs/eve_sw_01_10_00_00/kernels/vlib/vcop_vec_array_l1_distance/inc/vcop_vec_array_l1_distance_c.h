/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_vec_array_l1_distance_cn                                        */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_vec_array_l1_distance_cn                                   */
/*     (                                                                    */
/*         short           a[],                                             */
/*         short           b[],                                             */
/*         unsigned int    c[1],                                            */
/*         int             array_len                                        */
/*     )                                                                    */ 
/*                                                                          */
/*                                                                          */
/*     A         :  Pointer to an input array of shorts.                    */
/*     B         :  Pointer to second input array of shorts.                */
/*     C         :  Pointer to output unsigned int value                    */
/*     array_len :  length of the arrays A and B                            */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts pointers to two input arrays of         */
/*     length array_len and returns a single integer value representing     */
/*	   the L1 distance between the two arrays.                              */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*     While The C code does not have any assumptions on the length of      */
/*     the arrays, the assembly code assumes that array_len the length      */
/*     of the arrays is a multiple of 8.                                    */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef _vcop_vec_array_l1_distance_CN
#define _vcop_vec_array_l1_distance_CN  1

void vcop_vec_array_l1_distance_cn
(
    short           a[],
    short           b[],
    unsigned int    c[1],
    int             array_len
);

#endif

/* ======================================================================== */
/*  End of file:  vcop_vec_array_l1_distance_c.h                            */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */



