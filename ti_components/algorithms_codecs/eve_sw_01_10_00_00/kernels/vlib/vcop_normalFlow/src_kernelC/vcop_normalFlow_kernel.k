/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_vec_normalFlow_kernel                                           */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_vec_normalFlow_kernel                                      */
/*     (                                                                    */
/*         __vptr_int16   imDiff,                                           */
/*         __vptr_int16   Emag,                                             */
/*         __vptr_int16   E,                                                */
/*         __vptr_int16   LUT,                                              */
/*                  int   T,                                                */
/*                short   numEls,                                           */
/*         __vptr_int16   normalFlowU,                                      */
/*         __vptr_int16   normalFlowV,                                      */
/*      )                                                                   */
/*                                                                          */
/*     imdiff       :  image difference values (SQ15.0)                     */
/*     Emag         :  gradient magnitude values (SQ15.0)                   */
/*     E            :  x-direction gradient  (SQ15.0) and                   */
/*                     y-direction gradient  (SQ15.0)  interleaved          */
/*     LUT          :  Look-Up-Table containing values for integer division */
/*                     (SQ0.15)                                             */
/*     T            :  Threshold on gradient magnitude                      */
/*     numEls       :  Number of pixels to process                          */
/*     normalFlowU  :  Normal flow vector output in x-direction             */
/*     normalFlowV  :  Normal flow vector output in y-direction             */
/*                                                                          */
/*     Returns      :  None or void.                                        */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine ocmputes for every pixel in the image, motion   */
/*     vectors parallel to the gradient direction at each pixel.            */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*     (1) The LUT array should hold values such that LUT[n] = X, where X   */
/*         is 1/n represented in SQ0.15 format.                             */
/*     (2) The threshold, T, on gradient magnitude ensures that only those  */
/*         pixels with gradient madnitude greater than T will be processed. */
/*         Normal flow values for pixels that do not pass the threshold is 0*/
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2012 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


#define ELEMSZ          sizeof(*Emag)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)
#define NUM_TBLS    (8)
#define NUM_PTS_TLU (1)
#define IND_ELEMSZ (NUM_TBLS * sizeof(*Emag))
#define OUT_ELEMSZ (NUM_TBLS  * NUM_PTS_TLU * sizeof(*TLU_m_inv))

void vcop_normalFlow
(
    __vptr_int16   imDiff,
    __vptr_int16   Emag,
    __vptr_int16   LUT,
    __vptr_int16   E,
    __vptr_int16   TLU_m_inv,
             int   T,
           short   numEls,
    __vptr_int16   normalFlowU,
    __vptr_int16   normalFlowV       
)
{
    __vector m, m_inv, ex, ey, d, Vdst;
    __vector R0, R1, R2, R3;
    __vector Ex_1, Ey_1, d_1, Ex_2, Ey_2;
    __vector im, im_1, exd, eyd;
    __vector Vpred;
    __vector Vindex, Vtabledata;

//  Look-up table kernel to compute the inverse of Emag

    _LOOKUP(NUM_TBLS, NUM_PTS_TLU);
    for (int I1 = 0; I1 < numEls/NUM_TBLS; I1++)
    {
        __agen index_addr = I1 * IND_ELEMSZ;
        __agen table_addr = 0;
        __agen out_addr   = I1 * OUT_ELEMSZ;

        Vindex     = Emag[index_addr];
        Vtabledata = LUT[table_addr].lookup(Vindex);
        TLU_m_inv[out_addr].table_npt() = Vtabledata;
    }

    R0 = -8;
    R2 = T;
    R3 = 0;

// Compute kernel to do the normal flow computations

    for (int I1 = 0; I1 < numEls/VCOP_SIMD_WIDTH; I1++)
    {
        __agen Addr, Addr1;

        Addr = I1*VECTORSZ;
        Addr1 = 2*I1*VECTORSZ;

        m = Emag[Addr];
        im = imDiff[Addr];
        m_inv = TLU_m_inv[Addr];
        
        (Ex_1,Ey_1) = E[Addr1].deinterleave();

        Ex_2 = (Ex_1 * m_inv).truncate(8);
        Ey_2 = (Ey_1 * m_inv).truncate(8);

        im_1 = R3 - im;
        d = (im_1 * m_inv).truncate(8);

        exd = (Ex_2 * d);
        eyd = (Ey_2 * d);
        
        Vpred = (m > R2);  // Check if the Emag value is greater than threshold T

        normalFlowU[Addr] = exd.truncate(7).predicate(Vpred);
        normalFlowV[Addr] = eyd.truncate(7).predicate(Vpred);
    }
}

/* ======================================================================== */
/*  End of file:  vcop_normalFlow_kernel.k                                  */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2012 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
