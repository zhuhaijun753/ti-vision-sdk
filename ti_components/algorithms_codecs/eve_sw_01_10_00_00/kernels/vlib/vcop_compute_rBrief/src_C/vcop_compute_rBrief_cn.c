/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME : rBrief : header file.                                         */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include "stdlib.h"
#include <stdio.h>
#include "math.h"

#include "vcop_compute_rBrief_c.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

// Function to compute the moments m01 and m10 which is needed to compute the orientation
static int compute_moments(unsigned char* pIn, char* moment_col_mask,
                    char* moment_row_mask,
                    short* m01,
                    short* m10)
{
  int i, j;
  int a;
  int b;

  a = 0;
  b = 0;
  for(i=0; i<MOMENTS_PATCH_SIZE; i++)
  {
    for(j=0; j<MOMENTS_PATCH_SIZE; j++)
    {
      a += pIn[632+i*PATCH_SIZE+j]*moment_col_mask[i*MOMENTS_PATCH_SIZE+j];
      b += pIn[632+i*PATCH_SIZE+j]*moment_row_mask[i*MOMENTS_PATCH_SIZE+j];
    }
  }
  if(a > 0x7FFF) a = 0x7FFF;
  if(a < -0x8000) a = -0x8000;

  if(b > 0x7FFF) b = 0x7FFF;
  if(b < -0x8000) b = -0x8000;

  *m10 = (short)a ;
  *m01 = (short)b ;

  return 0;
}

// Function to compute the 5x5 sum around each pixel in the patch, this patch sum is used to compute the descriptor
// *pIn is the pointer to the start of 48x53 patch, patch_sum is 48x48 patch output - the center pixel co-ordinate is (26,21)
static int compute_patch_sum(unsigned char*pIn, short* patch_sum)
{
  int k, l;

  for(k=0; k<PATCH_SIZE; k++)
  {
    for(l=0; l<PATCH_SIZE-4; l++)
    {
      patch_sum[k*PATCH_SIZE+l] = pIn[k*PATCH_SIZE+l] + pIn[k*PATCH_SIZE+l+1] + pIn[k*PATCH_SIZE+l+2] + pIn[k*PATCH_SIZE+l+3] + pIn[k*PATCH_SIZE+l+4];
      patch_sum[k*PATCH_SIZE+l] += pIn[(k+1)*PATCH_SIZE+l] + pIn[(k+1)*PATCH_SIZE+l+1] + pIn[(k+1)*PATCH_SIZE+l+2] + pIn[(k+1)*PATCH_SIZE+l+3] + pIn[(k+1)*PATCH_SIZE+l+4];
      patch_sum[k*PATCH_SIZE+l] += pIn[(k+2)*PATCH_SIZE+l] + pIn[(k+2)*PATCH_SIZE+l+1] + pIn[(k+2)*PATCH_SIZE+l+2] + pIn[(k+2)*PATCH_SIZE+l+3] + pIn[(k+2)*PATCH_SIZE+l+4];
      patch_sum[k*PATCH_SIZE+l] += pIn[(k+3)*PATCH_SIZE+l] + pIn[(k+3)*PATCH_SIZE+l+1] + pIn[(k+3)*PATCH_SIZE+l+2] + pIn[(k+3)*PATCH_SIZE+l+3] + pIn[(k+3)*PATCH_SIZE+l+4];
      patch_sum[k*PATCH_SIZE+l] += pIn[(k+4)*PATCH_SIZE+l] + pIn[(k+4)*PATCH_SIZE+l+1] + pIn[(k+4)*PATCH_SIZE+l+2] + pIn[(k+4)*PATCH_SIZE+l+3] + pIn[(k+4)*PATCH_SIZE+l+4];
    }
  }
  return 0;
}

// This function computes the angle atan(m01/m10)
// Since division is costly on EVE, a different logic using LUT is applied
// first, the abs(y)*thr is compared against abs(x) to determine the bin
// to determine the quadrant, the sign of x and y is checked and suitable offset is added
// The final offset is used to look-up the Cos and Sin values from the look up table
static int compute_wedge(short* m01, short* m10, unsigned short* thrx, short* cos_in_ptr, short* sin_in_ptr, short* cos_out_ptr, short* sin_out_ptr)
{
  int i;
  short x, y;
  int val = 0;
  int multxthr;
  int offset;

  y = m01[0]; // y
  x = m10[0]; // x

  for(i=0; i<8; i++)
  {
    multxthr = (abs(x)*thrx[i]) >> 8;
    if(abs(y) >= multxthr)
      val++;
  }

  // determine the offset
  if(y>0 && x>0)
    offset = val;
  else if(y<0 && x>0)
    offset = 24+val;
  else if(y>0 && x<0)
    offset = 8+val;
  else
    offset = 16+val;

  cos_out_ptr[0] = cos_in_ptr[offset];
  sin_out_ptr[0] = sin_in_ptr[offset];

  return 0;
}

// This function computes the Orb descriptor
static int compute_OrbDescriptor(char* in_src_dst_x, char* in_src_dst_y,  short* cos_out_ptr, short* sin_out_ptr, short* patch_sum, unsigned char* orb_descriptor)
{
  int i, j;
  char rot_src_x[256];
  char rot_src_y[256];
  char rot_dst_x[256];
  char rot_dst_y[256];
  short a, b;
  short rnd_bits;
  int t0, t1, val;

  a = cos_out_ptr[0];
  b = sin_out_ptr[0];

  rnd_bits = 14;

  // compute rotated x,y co-ordinates -> Stheta = Rtheta * S
  // Rtheta is a 2x2 matrix = [cos(theta) -Sin(theta); Sin(theta Cos(theta)]
  // S is 2xn matrix = [x1 y1; x2 y2; ... ; xn yn]
  for(i=0; i<256; i++)
  {
    val = (in_src_dst_x[i]*a - in_src_dst_y[i]*b);
    val += (1 << (rnd_bits - 1));
    rot_src_x[i] = val >> rnd_bits; // only 8 bit rotated co-ordinates

    val = (in_src_dst_x[i+256]*a - in_src_dst_y[i+256]*b);
    val += (1 << (rnd_bits - 1));
    rot_dst_x[i] = val >> rnd_bits; // only 8 bit rotated co-ordinates

    val = (in_src_dst_x[i]*b + in_src_dst_y[i]*a);
    val += (1 << (rnd_bits - 1));
    rot_src_y[i] = val >> rnd_bits; // only 8 bit rotated co-ordinates

    val = (in_src_dst_x[i+256]*b + in_src_dst_y[i+256]*a);
    val += (1 << (rnd_bits - 1));
    rot_dst_y[i] = val >> rnd_bits; // only 8 bit rotated co-ordinates

  }

  // prepare the 256 bit descriptor
  for(i=0, j=0; i<32; i++, j+=8)
  {
    // The center of the patch is located at (26,21)
    // So look up the corresponding value at an offset from the center
    // The offset is specified by the rotated X and Y co-ordinates
    // Perform the binary test using the looked up values

    t0 = patch_sum[(26+rot_src_y[j])*PATCH_SIZE+(21+rot_src_x[j])];
    t1 = patch_sum[(26+rot_dst_y[j])*PATCH_SIZE+(21+rot_dst_x[j])];
    val = (t0 < t1); // bit 0

    t0 = patch_sum[(26+rot_src_y[j+1])*PATCH_SIZE+(21+rot_src_x[j+1])];
    t1 = patch_sum[(26+rot_dst_y[j+1])*PATCH_SIZE+(21+rot_dst_x[j+1])];
    val |= (t0 < t1) << 1; // bit 1

    t0 = patch_sum[(26+rot_src_y[j+2])*PATCH_SIZE+(21+rot_src_x[j+2])];
    t1 = patch_sum[(26+rot_dst_y[j+2])*PATCH_SIZE+(21+rot_dst_x[j+2])];
    val |= (t0 < t1) << 2; // bit 2

    t0 = patch_sum[(26+rot_src_y[j+3])*PATCH_SIZE+(21+rot_src_x[j+3])];
    t1 = patch_sum[(26+rot_dst_y[j+3])*PATCH_SIZE+(21+rot_dst_x[j+3])];
    val |= (t0 < t1) << 3; // bit 3

    t0 = patch_sum[(26+rot_src_y[j+4])*PATCH_SIZE+(21+rot_src_x[j+4])];
    t1 = patch_sum[(26+rot_dst_y[j+4])*PATCH_SIZE+(21+rot_dst_x[j+4])];
    val |= (t0 < t1) << 4; // bit 4

    t0 = patch_sum[(26+rot_src_y[j+5])*PATCH_SIZE+(21+rot_src_x[j+5])];
    t1 = patch_sum[(26+rot_dst_y[j+5])*PATCH_SIZE+(21+rot_dst_x[j+5])];
    val |= (t0 < t1) << 5; // bit 5

    t0 = patch_sum[(26+rot_src_y[j+6])*PATCH_SIZE+(21+rot_src_x[j+6])];
    t1 = patch_sum[(26+rot_dst_y[j+6])*PATCH_SIZE+(21+rot_dst_x[j+6])];
    val |= (t0 < t1) << 6; // bit 6

    t0 = patch_sum[(26+rot_src_y[j+7])*PATCH_SIZE+(21+rot_src_x[j+7])];
    t1 = patch_sum[(26+rot_dst_y[j+7])*PATCH_SIZE+(21+rot_dst_x[j+7])];
    val |= (t0 < t1) << 7; // bit 7

    orb_descriptor[i] = val;
  }
  return 0;
}

void compute_Orb(unsigned char* pIn, char* moment_col_mask, char* moment_row_mask, char* in_src_dst_x, char* in_src_dst_y, short *cos_ptr, short* sin_ptr, unsigned short* arc_thrx, unsigned char* descriptor )
{
  short m01[1], m10[1];
  int status = 0;
  short patch_sum[PATCH_SIZE*PATCH_SIZE];
  short cos_out_ptr[1], sin_out_ptr[1];


  // compute moments m01 and m10 to compute orientation
  status = compute_moments(pIn, moment_col_mask, moment_row_mask, m01, m10);

  if(status)
    printf("Error while computing moments\n");

  // compute angle of orientation theta
  status = compute_wedge(m01, m10, arc_thrx, cos_ptr, sin_ptr, cos_out_ptr, sin_out_ptr);

  // compute the 5x5 sum around a pixel, to use to generate the ORB descriptor
  status = compute_patch_sum(pIn, patch_sum);

  if(status)
    printf("Error while computing moments\n");

#if 0
  printf("The patch sum computed is: \n");

  for(i=0; i<PATCH_SIZE; i++)
  {
    for(j=0; j<PATCH_SIZE; j++)
    {
      printf("%d \t", patch_sum[i*PATCH_SIZE+j]);
    }
    printf("\n");
  }
#endif

  // compute the ORB descriptor
  status = compute_OrbDescriptor(in_src_dst_x, in_src_dst_y, cos_out_ptr, sin_out_ptr, patch_sum, descriptor);

}

