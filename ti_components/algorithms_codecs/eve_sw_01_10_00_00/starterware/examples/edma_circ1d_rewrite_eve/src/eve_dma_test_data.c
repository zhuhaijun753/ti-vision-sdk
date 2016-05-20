/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*-----------------------------------------------------------------------*/
/*  This is a known array of input values that will serve as the source  */
/*  or input of all DMA transfers. This array is an array of 256 bytes   */
/*  and is aligned on a word boundary. This array can technically be     */
/*  allocated to any valid data memory.                                  */
/*-----------------------------------------------------------------------*/

#pragma DATA_ALIGN   (src,  32);
#pragma DATA_SECTION (src, "SRC_REGION");

unsigned int src[64] =
{
    0x01010101,0x01010101,0x01010101,0x01010101,
    0x02020202,0x02020202,0x02020202,0x02020202,
    0x03030303,0x03030303,0x03030303,0x03030303,
    0x04040404,0x04040404,0x04040404,0x04040404,
    0x05050505,0x05050505,0x05050505,0x05050505,
    0x06060606,0x06060606,0x06060606,0x06060606,
    0x07070707,0x07070707,0x07070707,0x07070707,
    0x08080808,0x08080808,0x08080808,0x08080808,
    0x01010101,0x01010101,0x01010101,0x01010101,
    0x02020202,0x02020202,0x02020202,0x02020202,
    0x03030303,0x03030303,0x03030303,0x03030303,
    0x04040404,0x04040404,0x04040404,0x04040404,
    0x05050505,0x05050505,0x05050505,0x05050505,
    0x06060606,0x06060606,0x06060606,0x06060606,
    0x07070707,0x07070707,0x07070707,0x07070707,
    0x08080808,0x08080808,0x08080808,0x08080808,
};

/*-----------------------------------------------------------------------*/
/*  Now we define a destination region, in simple example we will try    */
/*  out all basic transfers for each of them we have an array. Some      */
/*  arrays are larger than source to allow for 2D stride.                */
/*-----------------------------------------------------------------------*/

#pragma DATA_ALIGN   (dst_1,  32);
#pragma DATA_SECTION (dst_1, "DST1_REGION");

unsigned int dst_1[8];

#pragma DATA_ALIGN   (e_dst_1,  32);
#pragma DATA_SECTION (e_dst_1, "DST_REGION");

/*-----------------------------------------------------------------------*/
/* Have seperate destination arrays for the expected results.            */
/*-----------------------------------------------------------------------*/

unsigned int e_dst_1[8] =
{
    0x07070707,0x07070707,0x07070707,0x07070707,
    0x08080808,0x08080808,0x08080808,0x08080808
};

