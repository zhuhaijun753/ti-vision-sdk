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
/*     __vptr_uint8   CFA_char,                                    */
/*     unsigned int   blk_w,                                       */
/*     unsigned int   blk_h,                                       */
/*     __vptr_uint8   R_char,                                      */
/*     __vptr_uint8   G_char,                                      */
/*     __vptr_uint8   B_char                                       */
/* );                                                              */
/*                                                                 */
/*                                                                 */
/* void vcop__BayerCFA_Interpolate_short                           */
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
/* BayerCFA_interpolate_char: (2/16 * 1/3) + 13/16 = 0.85 cyc/pix  */
/* BayerCFA_interpolate_short: (2/16 * 1/3) + 13/16 = 0.85 cyc/pix */
/*                                                                 */
/*=================================================================*/


#define VCOP_2SIMD_WIDTH   (VCOP_SIMD_WIDTH * 2)

#define ELEMSZ_IN_CHAR     sizeof(*CFA_char)
#define VECTORSZ_IN_CHAR  (ELEMSZ_IN_CHAR * VCOP_SIMD_WIDTH)

#define ELEMSZ_IN_SHORT     sizeof(*CFA_short)
#define VECTORSZ_IN_SHORT  (ELEMSZ_IN_SHORT * VCOP_SIMD_WIDTH)

/* * * * * * * * * * * * * * * * * * * * */

void vcop_BayerCFA_interpolate_char
(
    __vptr_uint8   CFA_char,  
    unsigned int   in_w,
    unsigned int   blk_w,
    unsigned int   blk_h,
    __vptr_uint8   R_char,
    __vptr_uint8   G_char,
    __vptr_uint8   B_char
)
{
    __vector Vzero_a, Vzero_b;
    
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
    /* Due to this, this loop takes 3 cycles to process 16/3 pixs.*/
    /*                                                            */
    /* Performance: 2/16 * (1/3) cyc/pix                          */
    /*------------------------------------------------------------*/
    
    Vzero_a =  0;
    Vzero_b =  0;

    for (int I3 = 0; I3 < blk_h/2; I3++)
    {
        __vector VB0, VB0_copy, VR0_copy, VR0, VG0, VG1;

        for (int I4 = 0; I4 < (blk_w/VCOP_2SIMD_WIDTH); I4++)
        { 
            __agen Addr_in, Addr;
            
            Addr_in  = I4 * 2 * VECTORSZ_IN_CHAR + I3 * 2 *  in_w * ELEMSZ_IN_CHAR;
            Addr     = I4 * 2 * VECTORSZ_IN_CHAR + I3 * 2 * blk_w * ELEMSZ_IN_CHAR;
            
            (VB0, VG0) = CFA_char[Addr_in].deinterleave();  // ibufla  
            (VG1, VR0) = (CFA_char + (in_w * ELEMSZ_IN_CHAR))[Addr_in].deinterleave(); // ibufla
            
            /*----------------------------------------------------*/
            /* Make copies to work atruncate the odd/even register*/
            /* usage issue. Even numbered registers cannot be the */
            /* first register in a register pair during store.    */
            /*----------------------------------------------------*/

            VB0_copy = VB0;
            VR0_copy = VR0;

            B_char[Addr].interleave()  = (VB0_copy, Vzero_a); // ibufha
            G_char[Addr].skip()  = VG0;       // wbuf   
            
            R_char[Addr].interleave() = (VR0_copy, Vzero_b);  // ibufha 
            (G_char + (blk_w * ELEMSZ_IN_CHAR))[Addr].skip() = VG1; // wbuf
        }
    }

    /*------------------------------------------------------------*/
    /* Interpolation Step 1 (Horizontal compute):                 */
    /* ------------------------------------------                 */
    /* Where bx = (Bleft + Bright)/2                              */
    /*                                                            */
    /* Where rx = (Rleft + Rright)/2                              */
    /*                                                            */
    /* Performance: (3/16) * 2 * (1/2) cyc/pix                    */
    /*------------------------------------------------------------*/

    for (int I3 = 0; I3 < blk_h/2; I3++)
    {
       __vector VB0, VR0, VB1, VR1, Vbx, Vrx;

        for (int I4 = 0; I4 < blk_w/VCOP_2SIMD_WIDTH; I4++)
        { 
            __agen Addr;

            Addr  = I4 * 2 *  VCOP_SIMD_WIDTH * ELEMSZ_IN_CHAR + I3 * 2 * blk_w * ELEMSZ_IN_CHAR;

            VB0 = B_char[Addr].ds2();
            VB1 = (B_char + (2 * ELEMSZ_IN_CHAR))[Addr].ds2();

            VR0 = R_char[Addr].ds2();
            VR1 = (R_char + (2 * ELEMSZ_IN_CHAR))[Addr].ds2();

            Vbx = VB0 + VB1;
            Vrx = VR0 + VR1;

            (B_char + ELEMSZ_IN_CHAR)[Addr].skip() = Vbx.truncate(1);
            (R_char + ELEMSZ_IN_CHAR)[Addr].skip() = Vrx.truncate(1);
        }
    }

    /*------------------------------------------------------------*/
    /* Where gx = (Gleft + Gright)/2                              */
    /* performance: 3/8 cyc/pix                                   */
    /*------------------------------------------------------------*/

    for (int I3 = 0; I3 < blk_h; I3++)
    {
        __vector VG0, VG1, Vgx;

        for (int I4 = 0; I4 < blk_w/VCOP_2SIMD_WIDTH; I4++)
        { 
            __agen Addr;

            Addr  = I4 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_IN_CHAR + I3 * blk_w * ELEMSZ_IN_CHAR;

            VG0 = G_char[Addr].ds2();
            VG1 = (G_char + (2 * ELEMSZ_IN_CHAR))[Addr].ds2();

            Vgx = VG0 + VG1;

            (G_char + ELEMSZ_IN_CHAR)[Addr].skip() = Vgx.truncate(1);
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
    /* Performance: 4/16 * (1/2) * 2 = cycles + H/2 + (R, B)      */
    /*------------------------------------------------------------*/

    for (int I3 = 0; I3 < blk_w/VCOP_2SIMD_WIDTH; I3++)
    {
        __vector VB0_lp3, VB1_lp3, VR0_lp3, VR1_lp3, Vb0, Vb1, Vr0, Vr1;
        __vector VR2, VR3, VB2, VB3;

        __agen Addr_toprow;

        Addr_toprow = I3 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_IN_CHAR;

        (VB0_lp3, VB1_lp3) = B_char[Addr_toprow].deinterleave();
        (VR0_lp3, VR1_lp3) = R_char[Addr_toprow].deinterleave();

        for (int I4 = 0; I4 < blk_h/2; I4++)
        { 
            __agen Addr;

            Addr  = I3 * 2 *  VCOP_SIMD_WIDTH * ELEMSZ_IN_CHAR + I4 * 2 * blk_w * ELEMSZ_IN_CHAR;

            (VB2, VB3) = (B_char + (2 * blk_w * ELEMSZ_IN_CHAR))[Addr].deinterleave();
            (VR2, VR3) = (R_char + (2 * blk_w * ELEMSZ_IN_CHAR))[Addr].deinterleave();
            
            Vb0 = (VB0_lp3 + VB2);
            Vb1 = (VB1_lp3 + VB3);

            Vr0 = (VR0_lp3 + VR2);
            Vr1 = (VR1_lp3 + VR3);
            
            VB0_lp3 = VB2;          // Save bottom pixels as 'new' top pixel
            VB1_lp3 = VB3;          // Save bottom pixels as 'new' top pixel
                                    
            VR0_lp3 = VR2;          // Save bottom pixels as 'new' top pixel
            VR1_lp3 = VR3;          // Save bottom pixels as 'new' top pixel
            
            (B_char + ( blk_w * ELEMSZ_IN_CHAR))[Addr].interleave() = (Vb0, Vb1).truncate(1);
            (R_char + ( blk_w * ELEMSZ_IN_CHAR))[Addr].interleave() = (Vr0, Vr1).truncate(1);
            
        }
    }
}

void vcop_BayerCFA_interpolate_short
(
    __vptr_uint16  CFA_short,
    unsigned int   in_w,
    unsigned int   blk_w,
    unsigned int   blk_h,
    __vptr_uint16  R_short,
    __vptr_uint16  G_short,
    __vptr_uint16  B_short
)
{

    __vector Vzero_a, Vzero_b;

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
    /* Performance: 2/16 * (1/3) cyc/pix                          */
    /*------------------------------------------------------------*/
    
    Vzero_a =  0;
    Vzero_b =  0;

    for (int I3 = 0; I3 < blk_h/2; I3++)
    {
        __vector VB0, VB0_copy, VR0, VR0_copy, VR1, VG0, VG1;

        for (int I4 = 0; I4 < (blk_w/VCOP_2SIMD_WIDTH); I4++)
        { 
            __agen Addr_in, Addr;
            
            Addr_in  = I4 * 2 * VECTORSZ_IN_SHORT + I3 * 2 *  in_w * ELEMSZ_IN_SHORT;
            Addr     = I4 * 2 * VECTORSZ_IN_SHORT + I3 * 2 * blk_w * ELEMSZ_IN_SHORT;
            
            (VB0, VG0) = CFA_short[Addr_in].deinterleave();  // ibufla
            (VG1, VR0) = (CFA_short + (in_w * ELEMSZ_IN_SHORT))[Addr_in].deinterleave(); // ibufla
            
            /*----------------------------------------------------*/
            /* Make copies to work atruncate the odd/even register*/
            /* usage issue. Even numbered registers cannot be the */
            /* first register in a register pair during store.    */
            /*----------------------------------------------------*/
            
            VB0_copy = VB0;
            VR0_copy = VR0;

            B_short[Addr].interleave()  = (VB0_copy, Vzero_a); // ibufha
            G_short[Addr].skip()  = VG0; // wbuf
            
            R_short[Addr].interleave() = (VR0_copy, Vzero_b);  // ibufha
            (G_short + (blk_w * ELEMSZ_IN_SHORT))[Addr].skip() = VG1; // wbuf

        }
    }

    /*------------------------------------------------------------*/
    /* Interpolation Step 1 (Horizontal compute):                 */
    /* ------------------------------------------                 */
    /* Where bx = (Bleft + Bright)/2                              */
    /*                                                            */
    /* Where rx = (Rleft + Rright)/2                              */
    /*                                                            */
    /* Performance: (3/16) * 2 * (1/2) cyc/pix                    */
    /*------------------------------------------------------------*/

    for (int I3 = 0; I3 < blk_h/2; I3++)
    {
        __vector VB0, VB1, VR0, VR1, Vrx, Vbx;

        for (int I4 = 0; I4 < blk_w/VCOP_2SIMD_WIDTH; I4++)
        { 
            __agen Addr;

            Addr  = I4 * 2 *  VCOP_SIMD_WIDTH * ELEMSZ_IN_SHORT + I3 * 2 * blk_w * ELEMSZ_IN_SHORT;

            VB0 = B_short[Addr].ds2();
            VB1 = (B_short + (2 * ELEMSZ_IN_SHORT))[Addr].ds2();

            VR0 = R_short[Addr].ds2();
            VR1 = (R_short + (2 * ELEMSZ_IN_SHORT))[Addr].ds2();

            Vbx = VB0 + VB1;
            Vrx = VR0 + VR1;

            (B_short + ELEMSZ_IN_SHORT)[Addr].skip() = Vbx.truncate(1);
            (R_short + ELEMSZ_IN_SHORT)[Addr].skip() = Vrx.truncate(1);
        }
    }

    /*------------------------------------------------------------*/
    /* Where gx = (Gleft + Gright)/2                              */
    /* performance: 3/8 cyc/pix                                   */
    /*------------------------------------------------------------*/

    for (int I3 = 0; I3 < blk_h; I3++)
    {
        __vector VG0, VG1, Vgx;

        for (int I4 = 0; I4 < blk_w/VCOP_2SIMD_WIDTH; I4++)
        { 
            __agen Addr;

            Addr  = I4 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_IN_SHORT + I3 * blk_w * ELEMSZ_IN_SHORT;

            VG0 = G_short[Addr].ds2();
            VG1 = (G_short + (2 * ELEMSZ_IN_SHORT))[Addr].ds2();

            Vgx = VG0 + VG1;

            (G_short + ELEMSZ_IN_SHORT)[Addr].skip() = Vgx.truncate(1);
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
    /* Performance: 4/16 * (1/2) * 2 = cycles + H/2 + (R, B)      */
    /*------------------------------------------------------------*/

    for (int I3 = 0; I3 < blk_w/VCOP_2SIMD_WIDTH; I3++)
    {

        __vector VB0_lp3, VB1_lp3, VR0_lp3, VR1_lp3, Vb0, Vb1, Vr0, Vr1;
        __vector VR2, VR3, VB2, VB3;

        __agen Addr_toprow;

        Addr_toprow = I3 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_IN_SHORT;

        (VB0_lp3, VB1_lp3) = B_short[Addr_toprow].deinterleave();
        (VR0_lp3, VR1_lp3) = R_short[Addr_toprow].deinterleave();

        for (int I4 = 0; I4 < blk_h/2; I4++)
        { 
            __agen Addr;

            Addr  = I3 * 2 *  VCOP_SIMD_WIDTH * ELEMSZ_IN_SHORT + I4 * 2 * blk_w * ELEMSZ_IN_SHORT;

            (VB2, VB3) = (B_short + (2 * blk_w * ELEMSZ_IN_SHORT))[Addr].deinterleave();
            (VR2, VR3) = (R_short + (2 * blk_w * ELEMSZ_IN_SHORT))[Addr].deinterleave();
            
            Vb0 = (VB0_lp3 + VB2);
            Vb1 = (VB1_lp3 + VB3);

            Vr0 = (VR0_lp3 + VR2);
            Vr1 = (VR1_lp3 + VR3);
            
            VB0_lp3 = VB2;          // Save bottom pixels as 'new' top pixel
            VB1_lp3 = VB3;          // Save bottom pixels as 'new' top pixel
                                    
            VR0_lp3 = VR2;          // Save bottom pixels as 'new' top pixel
            VR1_lp3 = VR3;          // Save bottom pixels as 'new' top pixel
            
            (B_short + ( blk_w * ELEMSZ_IN_SHORT))[Addr].interleave() = (Vb0, Vb1).truncate(1);
            (R_short + ( blk_w * ELEMSZ_IN_SHORT))[Addr].interleave() = (Vr0, Vr1).truncate(1);
            
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * */
