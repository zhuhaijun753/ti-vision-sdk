/*============================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.               */
/*                      All Rights Reserved                                   */
/*============================================================================*/

/* ===========================================================================*/
/*   @file : vcop_bilateralFilter.c                                           */

/*   @brief  : This file contains functions for bilateral filter              */

/*   @author Gajanan Ambi(gajanan.ambi@ti.com)                                */

/*   @version 0.0 (March 2012) : Base version.                                */
/*============================================================================*/

#include<stdio.h>
#include<stdlib.h>
#include <math.h>

/**
 *******************************************************************************
 * @fn       lut_range_preparation 
 * @brief    Function to prepare range look up table. 
 *
 * @inputs -  lut_range_q12  : LUT Buffer
 * @return - None
 * @param Comments: 
 *******************************************************************************
*/
void lut_range_preparation
(
unsigned short *lut_range_q12
)
{
  unsigned int i;
  float sigmaR = 0.02f * 255;
  
  for(i = 0; i <= 255; i++)
  {
    int qval = 12;
    int maxval = (1<<qval)-1;
    float temp = (i*i)/(2.0f*sigmaR*sigmaR);
    float val = exp(-temp) * (1<<qval) + (0.5);
    lut_range_q12[i] = val>=maxval? maxval : val;
  }
}

/**
 *******************************************************************************
 * @fn       lut_space_preparation 
 * @brief    Function to prepare space look up table. 
 *
 * @inputs -  lut_range_q12  : LUT Buffer
 * @return - None
 * @param Comments: 
 *******************************************************************************
*/
void lut_space_preparation
(
unsigned short *lut_space_q12
)
{
  unsigned int s,t;
  float sigmaS = 1.0f;
  
  for(s = 0; s < 5; s++)
  {
    for(t = 0; t < 5; t++)
    {
      int qval   = 12;
      int maxval = (1<<qval)-1;
      float temp = ((s-2)*(s-2) + (t-2)*(t-2))/(2.0f*sigmaS*sigmaS);
      float val  = (float) exp(-temp) * (1<<qval) + (0.5);
      lut_space_q12[s*5+t] = val>=maxval? maxval : val;
    }
  }
}

/*----------------------------------------------------------------------------*/
/*Function that emulates EVE VBINLOG instruction                              */
/*----------------------------------------------------------------------------*/
unsigned int binlog(unsigned int val)
{
  int exp, frac;
  unsigned int binlog;

  exp = (int) (log10((double) val)/log10(2));

  if(exp >= 28)
  {
    frac = (val >> (exp - 28)) - (1 << 28);
  }
  else
  {
    if(exp >= 17)
    {
      frac = (val << (28 - exp)) - (1 << 28);
    }
    else
    {
      frac = (val << 11);
    }
  }

  exp = (exp >= 17) ? (exp - 16) : 0;

  binlog = (exp << 28) | frac;

  return binlog;
}

/*----------------------------------------------------------------------------*/
/* Function to take the inverse log of the difference                         */
/* between VBINLOG(X) and VBINLOG(Y)                                          */
/*----------------------------------------------------------------------------*/
unsigned int quotient_invbinlog(int exp, unsigned int frac, unsigned int Qpoint)
{
  unsigned int frac_p1, val; 

  /*--------------------------------------------------------------------------*/
  /* Adjust the exponent such that it is aligned to                           */
  /* Qformat selected by the user                                             */
  /*--------------------------------------------------------------------------*/
  exp += Qpoint - 28;

  /*--------------------------------------------------------------------------*/
  /* Return the LMBD to bit position 28 before                                */
  /* performing the inverse binlog                                            */
  /*--------------------------------------------------------------------------*/
  frac_p1 = (1 << 28) + frac;

  /*--------------------------------------------------------------------------*/
  /* Perform inverse binlog                                                   */
  /*--------------------------------------------------------------------------*/
  if(exp < 0)
  {
    val = frac_p1 >> abs(exp);
  }
  else
  {
    val = frac_p1 << exp;
  }        
  
  return val;
}


/**
 *******************************************************************************
 * @fn       vcop_vec_array_div_unsword_c 
 * @brief    function to perform division by using binlog. 
 *
 * @inputs -  numerator : 
 *             - denominator  : 
 *             - Qpoint   : 
 * @return  - quotient
 * @param Comments:
 *******************************************************************************
*/
int vcop_vec_array_div_unsword_c
(
  unsigned int  numerator,
  unsigned int  denominator,
  unsigned int    Qpoint   
)
{
  unsigned int binlogX, binlogY, frac, logexp;

  int exp;
  unsigned int quotient;
  
  /*--------------------------------------------------------------------------*/
  /* Call emulated EVE binlog instruction                                     */
  /*--------------------------------------------------------------------------*/
  binlogX = binlog(numerator);
  binlogY = binlog(denominator);

  /*--------------------------------------------------------------------------*/
  /* Perform division by subtracting binlogs                                  */
  /*--------------------------------------------------------------------------*/
  if(binlogY > binlogX)
  {
    /*------------------------------------------------------------------------*/
    /* In this case binlogX - binlogY is signed 33-bit. We                    */
    /* must switch the operands for subtraction, and obtain the               */
    /* two's complement of the subtraction to get the same                    */
    /* results that EVE's VSUB instruction will give for the                  */
    /* exponent (bits 32-28) and fractional (bits 27-0) portion               */
    /* of the subtraction operation.                                          */
    /*------------------------------------------------------------------------*/
    logexp = binlogY - binlogX;

    /* two's complement */
    logexp = 0xFFFFFFFF - logexp + 1;    

    /* Add sign bit and sign-extend */
    exp    = 0xFFFFFFF0 | (logexp >> 28); 
  }
  else
  {
    logexp = binlogX - binlogY;
    exp    = logexp >> 28;
  }
  
  /*--------------------------------------------------------------------------*/
  /* Extract fractional portion of binlog                                     */
  /*--------------------------------------------------------------------------*/
  frac = logexp & 0x0FFFFFFF;

  /*--------------------------------------------------------------------------*/
  /* Call quotient_invbinlog, which emulates the EVE                          */
  /* assembly code steps needed to get the inverse binlog of                  */
  /* the quotient. This also aligns the output to the user                    */
  /* defined Qformat.                                                         */
  /*--------------------------------------------------------------------------*/
  quotient = quotient_invbinlog(exp, frac, Qpoint);        
  quotient = (quotient + (1<<(Qpoint-1)))>>Qpoint;

  return(quotient);
}


/**
 *******************************************************************************
 * @fn       vcop_img_bilateralFilter 
 * @brief    Function for bilateral filter in c code. (Fixed pt implementation)
 *
 * @inputs -  in_buff              : input image buffer 
 *             - LUT_RANGE_Q12  : Look up table range
 *             - LUT_SPACE_Q12  : Look up table for space
 *             - ref_out              : Reference output 
 *             - blk_width           : Input block width
 *             - blk_height          : Input block height
 *             - blk_stride           : Input block stride
 *             - horz_pad_size     : Horizontal padding size
 *             - vert_pad_size     : Vertical padding size
 *             - qFormat_tbl       :
 *             - qFormat_div       :
 *             - pixel_fmt           : 4 for RGBA and 1 for planar format
 * @return  - None
 *******************************************************************************
*/
void vcop_img_bilateralFilter
(
  unsigned char  *in_buff,
  unsigned short *LUT_RANGE_Q12,
  unsigned short *LUT_SPACE_Q12,
  unsigned char  *ref_out,
  unsigned int    blk_width,
  unsigned int    blk_height,
  unsigned int    blk_stride,
  unsigned int    horz_pad_size,
  unsigned int    vert_pad_size,
  unsigned int    qFormat_tbl,
  unsigned int    qFormat_div,
  unsigned int    pixel_fmt ,
  unsigned int   *ref_Wp,
  unsigned int   *ref_BFp,
  unsigned char  *ref_diff_buff,
  unsigned short *ref_Gpq,
  unsigned int    window_width, 
  unsigned int    window_height
)
{
  int s,t,i,j;
  int I_p;
  int I_q;
  int diff;
  int offset;
  int W_p; 
  int BF_p;

  unsigned char  *ptr_diff_out = ref_diff_buff;
  unsigned short *ptr_Gpq_out  = ref_Gpq;
  unsigned int   *ptr_ref_Wp   = ref_Wp;
  unsigned int   *ptr_ref_BFp  = ref_BFp;
  /*--------------------------------------------------------------------------*/
  /* Compute loop to find the difference                                      */
  /*--------------------------------------------------------------------------*/  
  for(s = 0; s < window_height; s++)
  {
    for(t = 0; t < window_width; t++)
    {
      for(i = 0; i< blk_height; i++)
      {
        for(j = 0; j< blk_width; j++)
        {
          /*------------------------------------------------------------------*/
          /* I_p :  Center pixel                                              */
          /*------------------------------------------------------------------*/  
          I_p = in_buff[((i+vert_pad_size) * blk_stride) + horz_pad_size + j];

          
          /*------------------------------------------------------------------*/
          /* I_q :  neighbour pixel                                           */
          /*------------------------------------------------------------------*/  
          offset = (i * blk_stride) + (s * blk_stride) + j + (t*pixel_fmt);
          I_q = in_buff[offset];
          
          diff = abs(I_p - I_q);
          
          *ref_diff_buff++ = abs(diff);
        
        }
      }
    }
  }

  /*--------------------------------------------------------------------------*/
  /* Lookup Loop to find out LUT values for each diff                         */
  /*--------------------------------------------------------------------------*/  
  for(s = 0; s < (window_height*window_width); s++)
  {
    for(i = 0; i< blk_height; i++)
    {
      for(j = 0; j< blk_width; j++)
      {
        int diff = *ptr_diff_out++;
        diff = LUT_RANGE_Q12[diff]; 
        *ref_Gpq++ = diff;
      }
    }
  }

  /*--------------------------------------------------------------------------*/
  /* Compute Loop                                                             */
  /*--------------------------------------------------------------------------*/  

  for(i = 0; i< blk_height; i++)
  {
    for(j = 0; j< blk_width; j++)
    {

      W_p  = 0;
      BF_p = 0;
      
      for(s = 0; s < window_height; s++)
      {
        for(t = 0; t < window_width; t++)
        {
          short lut_s = LUT_SPACE_Q12[s*window_width+t];
          
          short lut_r = ptr_Gpq_out[(s *window_width*blk_height*blk_width) + (t *blk_height*blk_width)+ (i*blk_width) + j];
          
          int G_pq = (lut_s * lut_r)>>8; 
          
          offset = (i * blk_stride) + (s * blk_stride) + j + (t*pixel_fmt);
          I_q = in_buff[offset];
          
          W_p  += G_pq;
          BF_p += I_q * G_pq;
        }
      }
      *ref_Wp++ = W_p;
      *ref_BFp++ = BF_p;
      
    }
  }

  /*--------------------------------------------------------------------------*/
  /* Division Loop : Using binlog                                             */
  /*--------------------------------------------------------------------------*/  
  for(i = 0; i< blk_height; i++)
  {
    for(j = 0; j< blk_width; j++)
    {
    
    W_p  = ptr_ref_Wp[(i*blk_width)+j];
    BF_p = ptr_ref_BFp[(i*blk_width)+j];
    
      unsigned char binlog_div = 
                 vcop_vec_array_div_unsword_c(
                                              BF_p<<(qFormat_div -qFormat_tbl),
                                              W_p<<(qFormat_div -qFormat_tbl),
                                              qFormat_tbl
                                              );
      
      /*----------------------------------------------------------------------*/
      /* Store the final reference output result for validation               */
      /*----------------------------------------------------------------------*/
      ref_out[(i*blk_width)+j] = binlog_div;
    }
  }

}

