/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_generateList_cn                                                 */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_generateList_cn                                            */
/*     (                                                                    */
/*         unsigned char  pIn[],                                            */
/*         unsigned short *pListX,                                          */
/*         unsigend short *pListY,                                          */
/*         unsigned short *pNumElmts,                                       */
/*         unsigned short maxNumElmts,                                      */
/*         unsigned short width,                                            */
/*         unsigned short height,                                           */
/*         unsigned short inStride                                           */
/*     )                                                                    */
/*                                                                          */
/*     pIn       :  8-bit input block made of 0 or non zero                 */
/*     pListX    :  Destination list for X coordinates                      */
/*     pListY    :  Destination list for Y coordinates                      */
/*     pNumElmts: pointer to location where the number pixels > 0 is stored */
/*     width     :  width of the frame                                      */
/*     height    :  height of the frame                                     */
/*     inStride  :  pitch of the input block                                 */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*       This routine accepts a 8-bit input block and generates two lists   */
/*       First list contains X coordinates of pixels that are non zero.     */
/*                                                                          */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2013 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include <stdio.h>
#include <stdlib.h>

/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/

#include "../inc/vcop_generateList_c.h"

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
)
{
    unsigned short i, j, nFeatures=0;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (pIn[i*inStride+j])
            {
                if (*pNumElmtsX >=  maxNumElmts) { /* if *pNumElmt exceeds maximum number of features allowable then exit as we don't want to overwrite other memory region */
                    goto Exit;
                }

                pListX[nFeatures] = (j + *pBlockX)<<qShift;
                pListY[nFeatures] = (i + *pBlockY)<<qShift;
                nFeatures++;
                *pNumElmtsX= *pNumElmtsX + 1;
            }
        }
    }

Exit:
    *pBlockX= *pBlockX + width;

    if (*pBlockX== width*numHorzBlock) {
        *pBlockX=0;
        *pBlockY= *pBlockY + height;
        if (*pBlockY== height*numVertBlock)
            *pBlockY= 0;
    }

    *pNumElmtsY= *pNumElmtsX;

return nFeatures;
}

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
)
{
    unsigned short i, j, nFeatures=0;

    offsetX= offsetX << qShift;
    offsetY= offsetY << qShift;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (pIn[i*inStride+j])
            {
                if (*pNumElmtsX >=  maxNumElmts) { /* if *pNumElmt exceeds maximum number of features allowable then exit as we don't want to overwrite other memory region */
                    goto Exit;
                }

                pListXY[2*nFeatures] = ((j + *pBlockX)<<qShift) + offsetX;
                pListXY[2*nFeatures+1] = ((i + *pBlockY)<<qShift) + offsetY;
                nFeatures++;
                *pNumElmtsX= *pNumElmtsX + 1;
            }
        }
    }

Exit:
    *pBlockX= *pBlockX + width;

    if (*pBlockX== width*numHorzBlock) {
        *pBlockX=0;
        *pBlockY= *pBlockY + height;
        if (*pBlockY== height*numVertBlock)
            *pBlockY= 0;
    }

    *pNumElmtsY= *pNumElmtsX;

return nFeatures;
}
/* ======================================================================== */
/*  End of file:  vcop_vec_gradients_xy_and_magnitude_c.c                   */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


