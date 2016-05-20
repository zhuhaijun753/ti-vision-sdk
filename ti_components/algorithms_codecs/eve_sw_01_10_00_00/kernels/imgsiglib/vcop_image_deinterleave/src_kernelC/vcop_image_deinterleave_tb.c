/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


/*-----------------------------------------------------------------*/
/* NAME : vcop_image_interleave.c                                */
/*                                                                 */
/*                                                                 */
/* DESCRIPTION:                                                    */
/*=================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <vcop.h>
#if VCOP_HOST_EMULATION
  #include "vcop_image_deinterleave_kernel.k"    // kernel source
#else
  #include "vcop_image_deinterleave_kernel.h" 
#endif

/*---------------------------------------------------------------------------*/
/*Input block dimensions*/
/*IMPORTANT!! BLK_WIDTH should be a multiple of 8*/
/*---------------------------------------------------------------------------*/
#define BLK_WIDTH    16
#define BLK_HEIGHT   8

/*---------------------------------------------------------------------------*/
/*input image buffer*/
/*---------------------------------------------------------------------------*/
#pragma DATA_SECTION (input_blk, "Adata");
unsigned char input_blk[BLK_WIDTH * BLK_HEIGHT] =
{
  0xA1,0x21,0xA2,0x22,0xA3,0x23,0xA4,0x24,0xA5,0x25,0xA6,0x26,0xA7,0x27,0xA8,0x28,
  0xB1,0x31,0xB2,0x32,0xB3,0x33,0xB4,0x34,0xB5,0x35,0xB6,0x36,0xB7,0x37,0xB8,0x38,
  0xC1,0x41,0xC2,0x42,0xC3,0x43,0xC4,0x44,0xC5,0x45,0xC6,0x46,0xC7,0x47,0xC8,0x48,
  0xD1,0x51,0xD2,0x52,0xD3,0x53,0xD4,0x54,0xD5,0x55,0xD6,0x56,0xD7,0x57,0xD8,0x58,
  0xE1,0x61,0xE2,0x62,0xE3,0x63,0xE4,0x64,0xE5,0x65,0xE6,0x66,0xE7,0x67,0xE8,0x68,
  0xF1,0x71,0xF2,0x72,0xF3,0x73,0xF4,0x74,0xF5,0x75,0xF6,0x76,0xF7,0x77,0xF8,0x78,
  0x11,0x81,0x12,0x82,0x13,0x83,0x14,0x84,0x15,0x85,0x16,0x86,0x17,0x87,0x18,0x88,
  0x01,0x91,0x02,0x92,0x03,0x93,0x04,0x94,0x05,0x95,0x06,0x96,0x07,0x97,0x08,0x98
};

/*---------------------------------------------------------------------------*/
/*Reference output image buffer*/
/*---------------------------------------------------------------------------*/
#pragma DATA_SECTION (ref_output_blk_Y, "Adata");
unsigned char ref_output_blk_Y[BLK_WIDTH * BLK_HEIGHT] =
{
  0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,
  0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,
  0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,
  0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,
  0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,
  0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,
  0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,
  0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98
};

#pragma DATA_SECTION (ref_output_blk_UV, "Adata");
unsigned char ref_output_blk_UV[BLK_WIDTH * BLK_HEIGHT] =
{
  0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,
  0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,
  0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,
  0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,
  0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,
  0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,
  0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,
  0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08
};

/*---------------------------------------------------------------------------*/
/*output image buffer*/
/*---------------------------------------------------------------------------*/
#pragma DATA_SECTION(output_blk_Y, "Cdata");
#pragma DATA_ALIGN(output_blk_Y, 32);
unsigned char output_blk_Y[BLK_WIDTH * BLK_HEIGHT] =
{
  0
};

#pragma DATA_SECTION(output_blk_UV, "Cdata");
#pragma DATA_ALIGN(output_blk_UV, 32);
unsigned char output_blk_UV[BLK_WIDTH * BLK_HEIGHT] =
{
  0
};

void print_output
(
  unsigned char *buffer,
  unsigned int   blk_height,
  unsigned int   blk_width
);

unsigned int verify_output
(
unsigned char *output,
unsigned char *output_ref,
unsigned int   blk_height,
unsigned int   blk_width
);

int main()
{
    unsigned int status = 0;
    
    vcop_image_deinterleave_u8(input_blk,
                            BLK_WIDTH,
                            BLK_HEIGHT,
                            output_blk_Y,
                            output_blk_UV
                            );

   status = verify_output(output_blk_Y,ref_output_blk_Y,BLK_HEIGHT,(BLK_WIDTH/2));
   if(status)
   {
     printf("PASS: First block is bit match \n");
   }
   else
   {
     printf("FAIL: First block is not bit match \n");
     /*---------------------------------------------------------------------*/
     /*  If there is a mismatch, print out a memory trace*/
     /*---------------------------------------------------------------------*/
     print_output(output_blk_Y,BLK_HEIGHT,(BLK_WIDTH/2));
   }

  status = verify_output(output_blk_UV,ref_output_blk_UV,BLK_HEIGHT,(BLK_WIDTH/2));
  if(status)
  {
    printf("PASS: Second block is bit match \n");
  }
  else
  {
    printf("FAIL: Second block is not bit match \n");
    /*---------------------------------------------------------------------*/
    /*  If there is a mismatch, print out a memory trace*/
    /*---------------------------------------------------------------------*/
    print_output(output_blk_UV,BLK_HEIGHT,(BLK_WIDTH/2));
  }
   
  printf("Done!!!\n");
  return 0;
}

unsigned int verify_output
(
unsigned char *output,
unsigned char *output_ref,
unsigned int   blk_height,
unsigned int   blk_width
)
{
  unsigned int i, j;
  unsigned int status = 1;

  for(i = 0; i<blk_height; ++i)
  {
    for( j = 0; j<blk_width; j++)
    {
      if((output[(i * blk_width) + j]) != (output_ref[(i * blk_width) + j]))
      {
        status = 0;
      }
    }
  }

return(status);
}

void print_output
(
unsigned char *buffer,
unsigned int blk_height,
unsigned int blk_width
)
{
  unsigned int i,j;

  for(i = 0; i<blk_height; ++i)
  {
    for(j = 0; j<blk_width; j++)
    {
      printf("%4x, ",buffer[(i * blk_width) + j]);
    }
    printf("\n");
  }
}

