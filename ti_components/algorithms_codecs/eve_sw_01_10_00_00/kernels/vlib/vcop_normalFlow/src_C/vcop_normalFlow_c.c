/*==========================================================================*/ 
/*     TEXAS INSTRUMENTS, INC.                                              */ 
/*                                                                          */ 
/*     NAME                                                                 */ 
/*     vcop_normalFlow_c                                                    */ 
/*                                                                          */
/*   USAGE                                                                  */
/*   This routine is C-callable and can be called as:                       */
/*                                                                          */          
/*   void vcop_normalFlow_c                                                 */
/*   {                                                                      */
/*      short imDiff[],                                                     */
/*      short Emag[],                                                       */
/*      short Ex[],                                                         */
/*      short Ey[],                                                         */
/*      short LUT[],                                                        */
/*      short T,                                                            */
/*      char  numEls,                                                       */
/*      short normalFlowU[],                                                */
/*      short normalFlowV[],                                                */
/*  }                                                                       */
/*                                                                          */
/*     imdiff       :  image difference values (SQ15.0)                     */
/*     Emag         :  gradient magnitude values (SQ15.0)                   */
/*     Ex           :  x-direction gradient  (SQ15.0)                       */
/*     Ey           :  y-direction gradient  (SQ15.0)                       */
/*     LUT          :  Look-Up-Table containing values for integer          */
/*                                          division (SQ0.15)               */
/*     T            :  Threshold on gradient magnitude                      */
/*     numEls       :  Number of pixels to process                          */
/*     normalFlowU    :  Normal flow vector output in x-direction           */
/*     normalFlowV    :  Normal flow vector output in y-direction           */
/*                                                                          */
/*     Returns        :  None or void.                                      */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine ocmputes for every pixel in the image, motion   */
/*     vectors parallel to the gradient direction at each pixel.            */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2012 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/                              


#include <stdio.h>
#include <stdlib.h>

//#include "vcop_normalFlow_c.h"

void vcop_normalFlow_c(short imDiff[],          // SQ15.0
                          short Emag[],         // SQ15.0
                          short Ex[],           // SQ15.0
                          short Ey[],           // SQ15.0
                          short LUT[],          // QS0.15
                          short T,              // SQ15.0
                          char  numEls,         // SQ31.0
                          short normalFlowU[],  // SQ8.7
                          short normalFlowV[])  // SQ8.7
{
    char i;
    short m,m_inv,ex, ey, d, nu, nv;

    for(i=0;i<numEls;i++){

        // Q8.0
        m = Emag[i];

        // Q0.16
        m_inv = LUT[m];

        // QS15.0 * QS0.15 = QSS15.15 -> QS8.7
        ex = ((Ex[i] * m_inv) >> 8);
        ey = ((Ey[i] * m_inv) >> 8);

        // QS15.0 * QS0.15 = QSS15.15 -> QS8.7
        d = ((-imDiff[i] * m_inv) >> 8);

        // QS8.7 * QS8.7 = QSS16.14 -> QS8.7
        nu = ((ex * d) >> 7);
        nv = ((ey * d) >> 7);

      if(m < T)
      {
            nu = 0;
        nv = 0;
      }
        normalFlowU[i] = nu;
        normalFlowV[i] = nv;
    }
}

/* ======================================================================== */
/*  End of file:  vcop_normalFlow_c.c                                       */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2012 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
