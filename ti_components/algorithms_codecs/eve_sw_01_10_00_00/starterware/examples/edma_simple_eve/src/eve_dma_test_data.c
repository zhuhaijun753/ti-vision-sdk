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
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x0A1B2C3D, 0x4E5F6B7C, 0x5AA5ECCE, 0xFABEFACE,
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x0A1B2C3D, 0x4E5F6B7C, 0x5AA5ECCE, 0xFABEFACE,
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x00000000, 0x00000001, 0x00000002, 0x00000003,
    0xAAAAAAAA, 0xBBBBBBBB, 0xCCCCCCCC, 0xDDDDDDDD 
};

/*-----------------------------------------------------------------------*/
/*  Now we define a destination region, in simple example we will try    */
/*  out all basic transfers for each of them we have an array. Some      */
/*  arrays are larger than source to allow for 2D stride.                */
/*-----------------------------------------------------------------------*/

#pragma DATA_ALIGN   (dst_1,  32);
#pragma DATA_ALIGN   (dst_2,  32);
#pragma DATA_ALIGN   (dst_3,  32);
#pragma DATA_ALIGN   (dst_4,  32);
#pragma DATA_ALIGN   (dst_5,  32);
#pragma DATA_ALIGN   (dst_6,  32);
#pragma DATA_ALIGN   (dst_7,  32);
#pragma DATA_ALIGN   (dst_8,  32);


#pragma DATA_SECTION (dst_1, "DST1_REGION");
#pragma DATA_SECTION (dst_2, "DST2_REGION");
#pragma DATA_SECTION (dst_3, "DST3_REGION");
#pragma DATA_SECTION (dst_4, "DST4_REGION");
#pragma DATA_SECTION (dst_5, "DST5_REGION");
#pragma DATA_SECTION (dst_6, "DST6_REGION");
#pragma DATA_SECTION (dst_7, "DST7_REGION");
#pragma DATA_SECTION (dst_8, "DST8_REGION");

unsigned int dst_1[64];
unsigned int dst_2[80];
unsigned int dst_3[64];
unsigned int dst_4[64];
unsigned int dst_5[64];
unsigned int dst_6[96];
unsigned int dst_7[160];
unsigned int dst_8[64];

#pragma DATA_ALIGN   (e_dst_1,  32);
#pragma DATA_ALIGN   (e_dst_2,  32);
#pragma DATA_ALIGN   (e_dst_3,  32);
#pragma DATA_ALIGN   (e_dst_4,  32);
#pragma DATA_ALIGN   (e_dst_5,  32);
#pragma DATA_ALIGN   (e_dst_6,  32);
#pragma DATA_ALIGN   (e_dst_7,  32);
#pragma DATA_ALIGN   (e_dst_8,  32);

#pragma DATA_SECTION (e_dst_1, "DST_REGION");
#pragma DATA_SECTION (e_dst_2, "DST_REGION");
#pragma DATA_SECTION (e_dst_3, "DST_REGION");
#pragma DATA_SECTION (e_dst_4, "DST_REGION");
#pragma DATA_SECTION (e_dst_5, "DST_REGION");
#pragma DATA_SECTION (e_dst_6, "DST_REGION");
#pragma DATA_SECTION (e_dst_7, "DST_REGION");
#pragma DATA_SECTION (e_dst_8, "DST_REGION");

/*-----------------------------------------------------------------------*/
/* Have seperate destination arrays for the expected results.            */
/*-----------------------------------------------------------------------*/

unsigned int e_dst_1[64] =
{
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x0A1B2C3D, 0x4E5F6B7C, 0x5AA5ECCE, 0xFABEFACE,
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x0A1B2C3D, 0x4E5F6B7C, 0x5AA5ECCE, 0xFABEFACE,
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x00000000, 0x00000001, 0x00000002, 0x00000003,
    0xAAAAAAAA, 0xBBBBBBBB, 0xCCCCCCCC, 0xDDDDDDDD 
};

unsigned int e_dst_2[80] =
{
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x0A1B2C3D, 0x4E5F6B7C, 0x5AA5ECCE, 0xFABEFACE,
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x0A1B2C3D, 0x4E5F6B7C, 0x5AA5ECCE, 0xFABEFACE,
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x00000000, 0x00000001, 0x00000002, 0x00000003,
    0xAAAAAAAA, 0xBBBBBBBB, 0xCCCCCCCC, 0xDDDDDDDD,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
};

unsigned int e_dst_3[64] =
{
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x0A1B2C3D, 0x4E5F6B7C, 0x5AA5ECCE, 0xFABEFACE,
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x0A1B2C3D, 0x4E5F6B7C, 0x5AA5ECCE, 0xFABEFACE,
    0x0A1B2C3D, 0x4E5F6B7C, 0x5AA5ECCE, 0xFABEFACE,
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12
};

unsigned int e_dst_4[64] =
{
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x0A1B2C3D, 0x4E5F6B7C, 0x5AA5ECCE, 0xFABEFACE,
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x0A1B2C3D, 0x4E5F6B7C, 0x5AA5ECCE, 0xFABEFACE,
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x00000000, 0x00000001, 0x00000002, 0x00000003,
    0xAAAAAAAA, 0xBBBBBBBB, 0xCCCCCCCC, 0xDDDDDDDD 
};

unsigned int e_dst_5[64] =
{
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x0A1B2C3D, 0x4E5F6B7C, 0x5AA5ECCE, 0xFABEFACE,
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x0A1B2C3D, 0x4E5F6B7C, 0x5AA5ECCE, 0xFABEFACE,
    0x0A1B2C3D, 0x4E5F6B7C, 0x5AA5ECCE, 0xFABEFACE,
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12
};

unsigned int e_dst_6[96] =
{
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x0A1B2C3D, 0x4E5F6B7C, 0x5AA5ECCE, 0xFABEFACE,
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x0A1B2C3D, 0x4E5F6B7C, 0x5AA5ECCE, 0xFABEFACE,
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x00000000, 0x00000001, 0x00000002, 0x00000003,
    0xAAAAAAAA, 0xBBBBBBBB, 0xCCCCCCCC, 0xDDDDDDDD,
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x00000000, 0x00000001, 0x00000002, 0x00000003,
    0xAAAAAAAA, 0xBBBBBBBB, 0xCCCCCCCC, 0xDDDDDDDD,
};

unsigned int e_dst_7[160] =
{

// 0 ---> 6 rows
   
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x00000000, 0x5E69BA23, 0x4884A01F, 0x9265ACDA, 
    0xFFFF0123, 0x00000000, 0xBEADDABE, 0x234A76B2, 
    0x9675ABCD, 0xABCDEF12, 0x00000000, 0xEEEECDEA, 
    0x01234567, 0x00000000, 0xFEEDFADE, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
 
// 1 ----> 5 rows

    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,

//  2 ----> 7 rows

    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x00000000, 0x00000000, 0x5E69BA23, 0x4884A01F, 
    0x9265ACDA, 0xFFFF0123, 0x00000000, 0x00000000,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0x00000000, 0x00000000, 0xEEEECDEA, 0x01234567,
    0x00000000, 0xFEEDFADE, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    
//  3 -----> 7 rows

    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x00000000, 0x00000000, 0x00000000, 0x5E69BA23, 
    0x4884A01F, 0x9265ACDA, 0xFFFF0123, 0x00000000,
    0x00000000, 0x00000000, 0xBEADDABE, 0x234A76B2, 
    0x9675ABCD, 0xABCDEF12, 0x00000000, 0x00000000,
    0x00000000, 0xEEEECDEA, 0x01234567, 0x00000000, 
    0xFEEDFADE, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    
//4 ----> 9 rows

    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    
//5 ------> 5 rows
    
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x00000000, 0x00000000, 0x00000000, 0x00000000
};

unsigned int e_dst_8[64] =
{
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x0A1B2C3D, 0x4E5F6B7C, 0x5AA5ECCE, 0xFABEFACE,
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x0A1B2C3D, 0x4E5F6B7C, 0x5AA5ECCE, 0xFABEFACE,
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x00000000, 0x00000001, 0x00000002, 0x00000003,
    0xAAAAAAAA, 0xBBBBBBBB, 0xCCCCCCCC, 0xDDDDDDDD 
};


/*-----------------------------------------------------------------------*/
/*  Maintain an array of sources, dests, num_bytes for 6 1d -> 1d lnkd.  */
/*  transfers.                                                           */
/*-----------------------------------------------------------------------*/

unsigned int *src_1d_1d[6] = 
{ 
    src  + 0,   src   + 16, src   + 32, src   + 48,
    src  + 0,   src   + 48
};


unsigned int *dst_1d_1d[6] = 
{ 
    dst_6 +  0, dst_6 + 16, dst_6 + 32, dst_6 + 48,
    dst_6 + 64, dst_6 + 80
};

int  num_bytes_1d_1d[6]    = 
{ 
     64,        64,         64,         64,
     64,        64
};

/*-----------------------------------------------------------------------*/
/*  Maintain array of sources, dests, num_bytes per line, num_lines,     */
/*  destination pitches for 6 1D -> 2D transfers.                        */
/*-----------------------------------------------------------------------*/

unsigned int *src_1d_2d[6] =
{
    src  + 0,       src   + 0, src   + 0,     src   + 0,
    src  + 0,       src   + 0
};

unsigned int *dst_1d_2d[6] =
{
    dst_7 +  0,     dst_7 + 24, dst_7 + 44,   dst_7 + 72,
    dst_7 +  104,   dst_7 + 140
};

int num_bytes_1d_2d[6] =
{
    16,            16,       16,         16,
    16,            16
};

int num_lines_1d_2d[6] =
{
    4,             4,         4,          4,
    4,             4
};

int pitch_1d_2d[6] =
{
   20,             16,       24,          28,
   32,             16
};

