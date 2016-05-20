/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*-----------------------------------------------------------------*/
/* NAME : vcop_BayerCFA_interpolate                                */
/*                                                                 */
/*                                                                 */
/* DESCRIPTION:                                                    */
/* The "vcop_BayerCFA_interpolate" code accepts 8 or 16-bit data   */
/* in the form of 8 or 16-bit Bayer Pattern, and writes out        */
/* the result as separate R, G and B planes. The output is         */
/* interpolated data to match the input width and height.          */
/* Interpolation is carried out by averaging the left and right    */
/* pixels, or the top and bottom pixels as the case may be.        */
/* In some cases, all four of the top-bottom-left-right pixels are */
/* used to compute the center pixel value.                         */
/*                                                                 */
/*                                                                 */
/* The Bayer pattern is as follows:                                */
/* -------------------------------                                 */
/* B G B G B G B G                                                 */
/* G R G R G R G R                                                 */
/* B G B G B G B G                                                 */
/* G R G R G R G R                                                 */
/* B G B G B G B G                                                 */
/* G R G R G R G R                                                 */
/*                                                                 */
/* After demosiacing or deinterleaving step we get:                */
/* ------------------------------------------------                */
/* B  bx B  bx B  bx  B                                            */
/* by bz by bz by bz  by                                           */
/* B  bx B  bx B  bx  B                                            */
/* by bz by bz by bz  by                                           */
/*                                                                 */
/* R  rx R  rx R  rx R                                             */
/* ry rz ry rz ry rz ry                                            */
/* R  rx R  rx R  rx R                                             */
/* ry rz ry rz ry rz ry                                            */
/*                                                                 */
/* G gx G  gx G  gx G                                              */
/* G gy G  gy G  gy G                                              */
/* G gx G  gx G  gx G                                              */
/* G gy G  gy G  gy G                                              */
/*                                                                 */
/* At this stage, bx, by, bz, rx, ry, rz, gx, gy are zeros.        */
/*                                                                 */
/* After interpolating we get:                                     */
/* ---------------------------                                     */
/* Where bx = (Bleft + Bright)/2                                   */
/* Where by = (Btop  + Bbottom)/2                                  */
/* Where bz = (Bleft + Bright + Btop + Bbottom)/4                  */
/*                                                                 */
/* Where rx = (Rleft + Rright)/2                                   */
/* Where ry = (Rtop  + Rbottom)/2                                  */
/* Where rz = (Rleft + Rright + Rtop + Rbottom)/4                  */
/*                                                                 */
/* Where gx = (Gleft + Gright)/2                                   */
/* Where gy = (Gtop  + Gbottom)/2                                  */
/*                                                                 */
/* API:                                                            */
/*                                                                 */
/* void vcop_BayerCFA_Interpolate_char                             */
/* (                                                               */
/*     unsigned char*   CFA_char,                                  */
/*     unsigned int   blk_w,                                       */
/*     unsigned int   blk_h,                                       */
/*     unsigned char*   R_char,                                    */
/*     unsigned char*   G_char,                                    */
/*     unsigned char*   B_char                                     */
/* );                                                              */
/*                                                                 */
/*                                                                 */
/* void vcop_BayerCFA_Interpolate_short                            */
/* (                                                               */
/*     __vptr_uint16  CFA_short,                                   */
/*     unsigned int   blk_w,                                       */
/*     unsigned int   blk_h,                                       */
/*     __vptr_uint16  R_short,                                     */
/*     __vptr_uint16  G_short,                                     */
/*     __vptr_uint16  B_short                                      */
/* );                                                              */
/*                                                                 */
/*                                                                 */
/* PERFORMANCE                                                     */
/*                                                                 */
/* BayerCFA_interpolate_char:                                      */
/* BayerCFA_interpolate_short:                                     */
/*                                                                 */
/*=================================================================*/


#include <math.h>

#include "../inc/vcop_BayerCFA_Interpolate_c.h"

/* * * * * * * * * * * * * * * * * * * * */

void vcop_BayerCFA_interpolate_char
(
    unsigned char  *CFA_char,  
    unsigned int   in_w,
    unsigned int   blk_w,
    unsigned int   blk_h,
    unsigned char  *R_char,
    unsigned char  *G_char,
    unsigned char  *B_char
)
{
    int i, j;
    unsigned char Bleft, Bright, Rleft, Rright, Gleft, Gright;
    unsigned char Btop, Bbottom, Rtop, Rbottom;

    /*------------------------------------------------------------*/
    /* The Bayer pattern is as follows:                           */
    /* -------------------------------                            */
    /* B G B G B G B G                                            */
    /* G R G R G R G R                                            */
    /* B G B G B G B G                                            */
    /* G R G R G R G R                                            */
    /* B G B G B G B G                                            */
    /* G R G R G R G R                                            */
    /*                                                            */
    /* DEMOSAICing STEP                                           */
    /* First step is to copy the R, G and B pixels which exist to */
    /* the separate R, G and B planes keeping their locations     */
    /* the same as the input array. This means, there are holes   */
    /* in these planar arrays which will eventually be filled     */
    /* with the interpolated values.                              */
    /*                                                            */
    /* This step also does the interleave step for G plane by     */
    /* using the top and bottom pixels that are already read-in.  */
    /* This step takes and extra cycle as we need to make copies  */
    /* of some of the registers due to their odd/even numbering.  */
    /* Due to this, this loop takes 3 cycles to process 16 pixs.  */
    /*                                                            */
    /*------------------------------------------------------------*/
    
    for ( i = 0; i < blk_h/2; i++)
    {
        for ( j = 0; j < blk_w/2; j++)
        {
            B_char[(i * 2 * blk_w) + (j * 2)] = CFA_char[(i * 2 * in_w) + (j * 2)];
            R_char[(i * 2 * blk_w) + (j * 2)] = CFA_char[(((i * 2) + 1) * in_w) + (j * 2) + 1];

            G_char[(i * 2 * blk_w) + (j * 2)] = CFA_char[(i * 2 * in_w) + ((j * 2) + 1)];
            G_char[(((i * 2) + 1) * blk_w) + (j * 2)] = CFA_char[(((i * 2) + 1) * in_w) + (j * 2)];
 
        }
    }

    /*------------------------------------------------------------*/
    /* Interpolation Step 1 (Horizontal compute):                 */
    /* ------------------------------------------                 */
    /* Where bx = (Bleft + Bright)/2                              */
    /*                                                            */
    /* Where rx = (Rleft + Rright)/2                              */
    /*                                                            */
    /*------------------------------------------------------------*/

    for ( i = 0; i < blk_h/2; i++)
    {
        for ( j = 0; j < blk_w/2; j++)
        {
            Bleft  =  B_char[(i * 2 * blk_w) + (j * 2)];
            Bright =  B_char[(i * 2 * blk_w) + (j * 2) + 2];

            Rleft  =  R_char[(i * 2 * blk_w) + (j * 2)];
            Rright =  R_char[(i * 2 * blk_w) + (j * 2) + 2];

            B_char[(i * 2 * blk_w) + (j * 2) + 1] = (Bleft + Bright) >> 1;
            R_char[(i * 2 * blk_w) + (j * 2) + 1] = (Rleft + Rright) >> 1;
        }
    }

    /*------------------------------------------------------------*/
    /* Where gx = (Gleft + Gright)/2                              */
    /*------------------------------------------------------------*/
   
    for ( i = 0; i < blk_h; i++)
    {
        for ( j = 0; j < blk_w/2; j++)
        {
            Gleft  =  G_char[(i * 1 * blk_w) + (j * 2)];
            Gright =  G_char[(i * 1 * blk_w) + (j * 2) + 2];

            G_char[(i * 1 * blk_w) + (j * 2) + 1] = (Gleft + Gright) >> 1;
        }
    }


    /*------------------------------------------------------------*/
    /* Interpolation Step 2 (Vertical compute):                   */
    /* ------------------------------------------                 */
    /* Here by = (Btop  + Bbottom)/2                              */
    /* Also bz = (Bleft + Bright + Btop + Bbottom)/4              */
    /* This can be also computed in a 2nd pass as:                */
    /* bz = (Btop_new + Bbottom_new)/2                            */
    /*                                                            */
    /* Here ry = (Rtop  + Rbottom)/2                              */
    /* Also rz = (Rleft + Rright + Rtop + Rbottom)/4              */
    /* This can be also computed in a 2nd pass as:                */
    /* rz = (Rtop_new + Rbottom_new)/2                            */
    /*                                                            */
    /*------------------------------------------------------------*/
  
    for ( i = 0; i < blk_h/2; i++)
    {
        for ( j = 0; j < blk_w; j++)
        {
            Btop     =  B_char[(i * 2 * blk_w) + j];
            Bbottom  =  B_char[(((i * 2) + 2) * blk_w) + j];

            Rtop     =  R_char[(i * 2 * blk_w) + (j * 1)];
            Rbottom  =  R_char[(((i * 2) + 2) * blk_w) + (j * 1)];

            B_char[(((i * 2) + 1) * blk_w) + (j * 1)] = (Btop + Bbottom) >> 1;
            R_char[(((i * 2) + 1) * blk_w) + (j * 1)] = (Rtop + Rbottom) >> 1;
        }
        
    }

}


/* * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * */

void vcop_BayerCFA_interpolate_short
(
    unsigned short  *CFA_short,  
    unsigned int   in_w,
    unsigned int   blk_w,
    unsigned int   blk_h,
    unsigned short  *R_short,
    unsigned short  *G_short,
    unsigned short  *B_short
)
{
    int i, j;
    unsigned short Bleft, Bright, Rleft, Rright, Gleft, Gright;
    unsigned short Btop, Bbottom, Rtop, Rbottom;

    /*------------------------------------------------------------*/
    /* The Bayer pattern is as follows:                           */
    /* -------------------------------                            */
    /* B G B G B G B G                                            */
    /* G R G R G R G R                                            */
    /* B G B G B G B G                                            */
    /* G R G R G R G R                                            */
    /* B G B G B G B G                                            */
    /* G R G R G R G R                                            */
    /*                                                            */
    /* DEMOSAICing STEP                                           */
    /* First step is to copy the R, G and B pixels which exist to */
    /* the separate R, G and B planes keeping their locations     */
    /* the same as the input array. This means, there are holes   */
    /* in these planar arrays which will eventually be filled     */
    /* with the interpolated values.                              */
    /*                                                            */
    /* This step also does the interleave step for G plane by     */
    /* using the top and bottom pixels that are already read-in.  */
    /* This step takes and extra cycle as we need to make copies  */
    /* of some of the registers due to their odd/even numbering.  */
    /* Due to this, this loop takes 3 cycles to process 16 pixs.  */
    /*                                                            */
    /*------------------------------------------------------------*/
    
    for ( i = 0; i < blk_h/2; i++)
    {
        for ( j = 0; j < blk_w/2; j++)
        {
            B_short[(i * 2 * blk_w) + (j * 2)] = CFA_short[(i * 2 * in_w) + (j * 2)];
            R_short[(i * 2 * blk_w) + (j * 2)] = CFA_short[(((i * 2) + 1) * in_w) + (j * 2) + 1];

            G_short[(i * 2 * blk_w) + (j * 2)] = CFA_short[(i * 2 * in_w) + ((j * 2) + 1)];
            G_short[(((i * 2) + 1) * blk_w) + (j * 2)] = CFA_short[(((i * 2) + 1) * in_w) + (j * 2)];
 
        }
    }

    /*------------------------------------------------------------*/
    /* Interpolation Step 1 (Horizontal compute):                 */
    /* ------------------------------------------                 */
    /* Where bx = (Bleft + Bright)/2                              */
    /*                                                            */
    /* Where rx = (Rleft + Rright)/2                              */
    /*                                                            */
    /*------------------------------------------------------------*/

    for ( i = 0; i < blk_h/2; i++)
    {
        for ( j = 0; j < blk_w/2; j++)
        {
            Bleft  =  B_short[(i * 2 * blk_w) + (j * 2)];
            Bright =  B_short[(i * 2 * blk_w) + (j * 2) + 2];

            Rleft  =  R_short[(i * 2 * blk_w) + (j * 2)];
            Rright =  R_short[(i * 2 * blk_w) + (j * 2) + 2];

            B_short[(i * 2 * blk_w) + (j * 2) + 1] = (Bleft + Bright) >> 1;
            R_short[(i * 2 * blk_w) + (j * 2) + 1] = (Rleft + Rright) >> 1;
        }
    }

    /*------------------------------------------------------------*/
    /* Where gx = (Gleft + Gright)/2                              */
    /*------------------------------------------------------------*/
   
    for ( i = 0; i < blk_h; i++)
    {
        for ( j = 0; j < blk_w/2; j++)
        {
            Gleft  =  G_short[(i * 1 * blk_w) + (j * 2)];
            Gright =  G_short[(i * 1 * blk_w) + (j * 2) + 2];

            G_short[(i * 1 * blk_w) + (j * 2) + 1] = (Gleft + Gright) >> 1;
        }
    }


    /*------------------------------------------------------------*/
    /* Interpolation Step 2 (Vertical compute):                   */
    /* ------------------------------------------                 */
    /* Here by = (Btop  + Bbottom)/2                              */
    /* Also bz = (Bleft + Bright + Btop + Bbottom)/4              */
    /* This can be also computed in a 2nd pass as:                */
    /* bz = (Btop_new + Bbottom_new)/2                            */
    /*                                                            */
    /* Here ry = (Rtop  + Rbottom)/2                              */
    /* Also rz = (Rleft + Rright + Rtop + Rbottom)/4              */
    /* This can be also computed in a 2nd pass as:                */
    /* rz = (Rtop_new + Rbottom_new)/2                            */
    /*                                                            */
    /*------------------------------------------------------------*/
  
    for ( i = 0; i < blk_h/2; i++)
    {
        for ( j = 0; j < blk_w; j++)
        {
            Btop     =  B_short[(i * 2 * blk_w) + j];
            Bbottom  =  B_short[(((i * 2) + 2) * blk_w) + j];

            Rtop     =  R_short[(i * 2 * blk_w) + (j * 1)];
            Rbottom  =  R_short[(((i * 2) + 2) * blk_w) + (j * 1)];

            B_short[(((i * 2) + 1) * blk_w) + (j * 1)] = (Btop + Bbottom) >> 1;
            R_short[(((i * 2) + 1) * blk_w) + (j * 1)] = (Rtop + Rbottom) >> 1;
        }
        
    }

}


/* * * * * * * * * * * * * * * * * * * * */
