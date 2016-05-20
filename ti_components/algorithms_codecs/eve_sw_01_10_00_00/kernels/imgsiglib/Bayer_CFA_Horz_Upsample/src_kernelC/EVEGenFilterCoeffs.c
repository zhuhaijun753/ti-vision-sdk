/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      GenResamplingCoeffs.c                                               */
/*                                                                          */
/*  Helper function for generation resampling filter coefficients for use   */
/*  use with the polyphase filter provided with VICP library.               */
/*                                                                          */
/*  USAGE                                                                   */
/*      This code has a function for generating filter coefficients for     */
/*  polyphase filter for resampling. The Up and Down sampling values are    */
/*  given by U and D respectively.                                          */
/*                                                                          */
/*  The function returns the up and down-sample values, number of taps and  */
/*  coefficents for the polyphase filter.                                   */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include <stdio.h>
#include <math.h>

short GenResamplingCoeffs
(
    int   U,                 // Up sampling value
    int   D,                 // Down sampling value
    int   taps,              // original number of taps 
    short *coeffs,
    unsigned char *sampling_pattern,
    int   *pattern_size
) 
{
    int   i, j, k;
    int   resample_max_ud;
    float sample;
    short ntaps;
    float pi;
    float sum;
    int   val, limit, prev_index;
    float filt_coef[256] = {0.0};
  //  short coeffs[256] = {0};

    /*-------------------------------------------------------------------*/
    /* Filter built for taps * max(U,D). Choose something reasonable!    */
    /*-------------------------------------------------------------------*/

    pi = (float) atan(1.0) * taps;
    resample_max_ud = (U >= D) ? U : D;
    
    /* first generate (4*max_ud)-tap filter coefficients */
    
    for (i = 0; i < taps * resample_max_ud; i++) 
    {
        /*---------------------------------------------------------------*/
        /* Get the sample or step values here, window for coefficients   */
        /*---------------------------------------------------------------*/

        if (i <= (taps/2) * resample_max_ud) 
            sample = (float) (i / ((taps/2.0) * resample_max_ud));
        else
            sample = (float) ((taps * resample_max_ud - i)/((taps/2.0) * resample_max_ud));
        
        /*---------------------------------------------------------------*/
        /* Computing the filter coefficients, center coef has max value. */
        /*---------------------------------------------------------------*/

        if (i == (taps/2) * resample_max_ud) 
            filt_coef[i] = 1.0;
        else
            filt_coef[i] = sample * (float) sin((pi * (i - (taps/2) * resample_max_ud))/resample_max_ud)
                / ((pi * (i - (taps/2) * resample_max_ud)) / resample_max_ud);
        
    }

    /*-------------------------------------------------------------------*/
    /* taps/polyfilter => total_taps (in this case "i")/U.               */
    /*-------------------------------------------------------------------*/
   
    ntaps = i/resample_max_ud;
    
    /* next normalize each phase */
    for (i = 0; i < resample_max_ud; i++) 
    {
        sum = 0.0;
        for (j = i; j < taps * resample_max_ud; j += U)
            sum += filt_coef[j];  
        
        for (j = i; j < taps * resample_max_ud; j += U) 
            coeffs[j] = (short) ((filt_coef[j] / sum) * 4096);
        
    }    
  
  /*-------------------------------------------------------------------*/
  /* For U/D generate the flag information giving sampling pattern.    */
  /*-------------------------------------------------------------------*/

    limit = (U > D) ? U : D;

    k = 0;
    prev_index = 1;
    for (i = 0; i < limit + 1; i++)
    {
        for ( j = 0; j < U/D + 1; j++)
        {
            val = (int) floor(j + (i * U/D) + 0.5);
            if (val == prev_index)
            {
                sampling_pattern[k-1] = 0;
                sampling_pattern[k++] = 1;
            }
            else sampling_pattern[k++] = 1;

            prev_index = val;
        }
    }

    /*-------------------------------------------------------------------*/
    /* We write the pattern size out so we know the size to replicate    */
    /* for writing the flags needed for doing collated stores. Due to    */
    /* the fact that we have only 4 levels of nested looping in VCOP, we */
    /* have to write the output address pattern as a repetitive pattern  */
    /* of *pattern_size and repeat it over to account for the size of    */
    /* filter.                                                           */
    /*-------------------------------------------------------------------*/

    *pattern_size = (U > D) ? ((limit  - 1) * (U/D + 1)) : (limit * (U/D + 1));

#if 0
    if (U > D)
    {
        printf("\nSampling pattern is: \n\n");
        for (i = 0; i < ((limit  - 1) * (U/D + 1)); i++)
        {
            printf("%d, ", sampling_pattern[i]);
        }

        printf("\n");
    }
    else
    {
        printf("\nSampling pattern is: \n\n");
        for (i = 0; i < (limit * (U/D + 1)); i++)
        {
            printf("%d, ", sampling_pattern[i]);
        }

        printf("\n");
    }
#endif

   return ntaps;
} 




