/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_generateList                                                    */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_generateList                                               */
/*     (                                                                    */
/*      unsigned char  pIn[],                                               */
/*      __vptr_uint8   pEndRowPadVal,                                       */
/*      __vptr_uint16  pXval,                                               */
/*      __vptr_uint16  pYval,                                               */
/*      __vptr_uint16  pBlockX,                                             */
/*       __vptr_uint16  pBlockY,                                            */
/*        unsigned short numHorzBlock,                                      */
/*        unsigned short numVertBlock,                                      */
/*        __vptr_uint16  pListX,                                            */
/*        __vptr_uint16  pListY,                                            */
/*        __vptr_uint16  pNumElmtsX,                                        */
/*        __vptr_uint16  pNumElmtsY,                                        */
/*        unsigned short maxNumElmts,                                       */
/*        unsigned short width,                                             */
/*        unsigned short height,                                            */
/*        unsigned short inStride,                                          */
/*        unsigned char qShift                                              */
/*     )                                                                    */
/*                                                                          */
/*     pIn       :  8-bit input block made of 0 or non zero                 */
/*     pEndRowPadVal: Pointer to pattern that is used to complete each row  */
/*                    to multiple of 8 in order to avoid side effect        */
/*     pXval     :  Pointer to predefined X coordinate values  0,1,..width-1*/
/*     pYval     :  Pointer to predefined X coordinate values 0,1,..height-1*/
/*     pBlockX   :  Pointer to a single short that will keep track of the X */
/*                  coordinate of the current block being processed.        */
/*                  Used in conjuction with pXval to calculate the absolute */
/*                  X coordinate of the 'ON' pixels added to the list       */
/*     pBlockY   :  Pointer to a single short that will keep track of the Y */
/*                  coordinate of the current block being processed.        */
/*                  Used in conjuction with pXval to calculate the absolute */
/*                  Y coordinate of the 'ON' pixels added to the list       */
/*     numHorzBlock: number of horizontal blocks in the frame to be processed */
/*                   Used by the function to know when to roll back *pBlockX */
/*                   to 0.                                                  */
/*     numVertBlock: number of vertical blocks in the frame to be processed */
/*                   Used by the function to know when to roll back *pBlockY */
/*                   to 0.                                                  */
/*     pListX    :  Pointer to destination list for X coordinates           */
/*     pListY    :  Pointer to destination list for Y coordinates           */
/*     pNumElmtsX: pointer to location where the number of elements in listX */
/*                 will be stored                                           */
/*     pNumElmtsY: pointer to location where the number of elements in listY */
/*                 will be stored. Always we will have  pNumElmtsX=*pNumElmtsY */
/*                 so this parameter might appear unnecessary. However for   */
/*                 BAM kernel implementation it is useful to have symmetry   */
/*     maxNumElmts: Maximum numebr of elements that cna be added to the list */
/*                  The kernel uses early termination in order not to overflow */
/*                  the list. Note that amount of memory to be allocated    */
/*                  to store the list should be maxNumElmts + 8 because collate */
/*                  store has a granularity of 8 elements                   */
/*     width     :  width of the frame                                      */
/*     height    :  height of the frame                                     */
/*     inStride  :  pitch of the input block, must be multiple of 8         */
/*                 and >= width                                             */
/*     qShift   : qshift that needs to be applied to the coordinates        */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*       This routine accepts a 8-bit input block and generates two lists   */
/*       First list contains X coordinates of pixels that are non zero.     */
/*       Second list contains Y coordinates of pixels that are non zero.    */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2013 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef _VCOP_GENERATE_LIST_CN_H
#define _VCOP_GENERATE_LIST_CN_H

unsigned short vcop_generateList_cn
(
        unsigned char  pIn[],
        unsigned short *pBlockX, /* pointer to X coordinate of the current block processed */
        unsigned short *pBlockY, /* pointer to Y coordinate of the current block processed */
        unsigned short numHorzBlock,   /* number of horizontal blocks in the frame */
        unsigned short numVertBlock,   /* number of vertical blocks in the frame */
        unsigned short *pListX,
        unsigned short *pListY,
        unsigned short *pNumElmtsX,
        unsigned short *pNumElmtsY,
        unsigned short maxNumElmts,
        unsigned short width,
        unsigned short height,
        unsigned short inStride,
        unsigned short qShift
);

unsigned short vcop_generateList_intlv_cn
(
        unsigned char  pIn[],
        unsigned short *pBlockX, /* pointer to X coordinate of the current block processed */
        unsigned short *pBlockY, /* pointer to Y coordinate of the current block processed */
        unsigned short numHorzBlock,   /* number of horizontal blocks in the frame */
        unsigned short numVertBlock,   /* number of vertical blocks in the frame */
        unsigned short *pListXY,
        unsigned short *pNumElmtsX,
        unsigned short *pNumElmtsY,
        unsigned short maxNumElmts,
        unsigned short width,
        unsigned short height,
        unsigned short inStride,
        unsigned short qShift,
        unsigned short offsetX,
        unsigned short offsetY
);

#endif

/* ======================================================================== */
/*  End of file:  vcop_generateList_c.h                                     */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */



