/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_generateList                                                    */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_generateList                                               */
/*     (                                                                    */
/*      unsigned char  pIn[],                                               */
/*      __vptr_uint8   pEndRowPadVal,                                       */
/*      __vptr_uint16  pXval,                                               */
/*      __vptr_uint16  pYval,                                               */
/*      __vptr_uint16  pBlockX,                                             */
/*       __vptr_uint16  pBlockY,                                            */
/*        unsigned short numHorzBlock,                                      */
/*        unsigned short numVertBlock,                                      */
/*        __vptr_uint16  pListX,                                            */
/*        __vptr_uint16  pListY,                                            */
/*        __vptr_uint16  pNumElmtsX,                                        */
/*        __vptr_uint16  pNumElmtsY,                                        */
/*        unsigned short maxNumElmts,                                       */
/*        unsigned short width,                                             */
/*        unsigned short height,                                            */
/*        unsigned short inStride,                                          */
/*        unsigned char qShift                                              */
/*     )                                                                    */
/*                                                                          */
/*     pIn       :  8-bit input block made of 0 or non zero                 */
/*     pEndRowPadVal: Pointer to pattern that is used to complete each row  */
/*                    to multiple of 8 in order to avoid side effect        */
/*     pXval     :  Pointer to predefined X coordinate values  0,1,..width-1*/
/*     pYval     :  Pointer to predefined X coordinate values 0,1,..height-1*/
/*     pBlockX   :  Pointer to a single short that will keep track of the X */
/*                  coordinate of the current block being processed.        */
/*                  Used in conjuction with pXval to calculate the absolute */
/*                  X coordinate of the 'ON' pixels added to the list       */
/*     pBlockY   :  Pointer to a single short that will keep track of the Y */
/*                  coordinate of the current block being processed.        */
/*                  Used in conjuction with pXval to calculate the absolute */
/*                  Y coordinate of the 'ON' pixels added to the list       */
/*     numHorzBlock: number of horizontal blocks in the frame to be processed */
/*                   Used by the function to know when to roll back *pBlockX */
/*                   to 0.                                                  */
/*     numVertBlock: number of vertical blocks in the frame to be processed */
/*                   Used by the function to know when to roll back *pBlockY */
/*                   to 0.                                                  */
/*     pListX    :  Pointer to destination list for X coordinates           */
/*     pListY    :  Pointer to destination list for Y coordinates           */
/*     pNumElmtsX: pointer to location where the number of elements in listX */
/*                 will be stored                                           */
/*     pNumElmtsY: pointer to location where the number of elements in listY */
/*                 will be stored. Always we will have  pNumElmtsX=*pNumElmtsY */
/*                 so this parameter might appear unnecessary. However for   */
/*                 BAM kernel implementation it is useful to have symmetry   */
/*     maxNumElmts: Maximum numebr of elements that cna be added to the list */
/*                  The kernel uses early termination in order not to overflow */
/*                  the list. Note that amount of memory to be allocated    */
/*                  to store the list should be maxNumElmts + 8 because collate */
/*                  store has a granularity of 8 elements                   */
/*     width     :  width of the block                                      */
/*     height    :  height of the block                                     */
/*     inStride  :  pitch of the input block, must be multiple of 8         */
/*                 and >= width                                             */
/*     qShift   : qshift that needs to be applied to the coordinates        */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*       This routine accepts a 8-bit input block and generates two lists   */
/*       First list contains X coordinates of pixels that are non zero.     */
/*       Second list contains Y coordinates of pixels that are non zero.    */
/*                                                                          */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2013 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define ALIGN_SIMD(a)   (((a) + VCOP_SIMD_WIDTH-1) & ~(VCOP_SIMD_WIDTH-1))
#define ALIGN_2SIMD(a)  (((a) + 2*VCOP_SIMD_WIDTH-1) & ~(2*VCOP_SIMD_WIDTH-1))

#define ELEMSZ          sizeof(*pIn)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)

void vcop_generateList
(
        __vptr_uint8   pIn,
        __vptr_uint8   pEndRowPadVal,
        __vptr_uint16  pXval,
        __vptr_uint16  pYval,
        __vptr_uint16  pBlockX, /* pointer to X coordinate of the current block processed */
        __vptr_uint16  pBlockY, /* pointer to Y coordinate of the current block processed */
        unsigned short numHorzBlock,   /* number of horizontal blocks in the frame */
        unsigned short numVertBlock,   /* number of vertical blocks in the frame */
        __vptr_uint16  pListX,
        __vptr_uint16  pListY,
        __vptr_uint16  pNumElmtsX,
        __vptr_uint16  pNumElmtsY,
        unsigned short maxNumElmts,
        unsigned short width,
        unsigned short height,
        unsigned short inStride,
        unsigned char qShift
)
{
    /* First we append the 8 values pointed by pEndRowPadVal to the end of each row pointed by pIn in case width is not multiple of VCOP_SIMD_WIDTH
     * We use pEndRowPadVal that we AND with the last 8 elements of each row extended to a multiple fo 8 elements
     * */
    __vector vEndRowPadVal;
    __agen Addr0= 0;

    vEndRowPadVal= pEndRowPadVal[Addr0].npt();

    for (int i=0;i<height;i++){
        __vector vIn;
        __agen AddrIn= i*inStride*sizeof(*pIn);

        vIn= (pIn + sizeof(*pIn)*(ALIGN_SIMD(width)-VCOP_SIMD_WIDTH))[AddrIn].npt();

        vIn= vIn & vEndRowPadVal;

        (pIn + sizeof(*pIn)*(ALIGN_SIMD(width)-VCOP_SIMD_WIDTH))[AddrIn].npt()= vIn;

    }

    /* Read the current block coordinate and increment blockX. At the end of the row reset blockX to 0 and increment blockY */

    __vector vBlockX, vBlockY, vOneIn8Lanes, vFF, vOne, vWidth, vHeight;

    vFF= 0xff;
    vOne= 1;
    vWidth= width;
    vHeight= height;

    vBlockX= pBlockX[Addr0].onept();
    vBlockY= pBlockY[Addr0].onept();

    for (int i=0; i<1; i++) {

        __vector vUpdateBlockX, vUpdateBlockY, vFlag, vNumHorzBlock;

        vNumHorzBlock= numHorzBlock*width;

        vUpdateBlockX= vBlockX + vWidth;
        vUpdateBlockY= vBlockY + vHeight;

        vFlag= (vUpdateBlockX == vNumHorzBlock); /* vFlag=1 when end of row is reached */
        vOneIn8Lanes= transpose_bits(vFF);

        pBlockX[Addr0].onept()= vUpdateBlockX.saturate(0, 0, numHorzBlock*width, 0); /* saturate blockX to 0 when end of row is reached */
        pBlockY[Addr0].onept()= vUpdateBlockY.saturate(0, 0, numVertBlock*height, 0).predicate(vFlag); /* write to pBlockY only at the of the row */

    }

    /* Extract the coordinates corresponding to 'ON' pixels and collate them into 2 lists: X and Y
     *
     * performance: 4/8 cyc/pixel
     * */

    _COLLATE(pListX);
    _COLLATE(pListY);

    __vector vNumElmts;

    vNumElmts= pNumElmtsX[Addr0].onept();

    for (int i=0;i<height;i++){
        __vector vyVal;
        __agen AddrYval;

        AddrYval= i*sizeof(*pYval) ;

        vyVal= pYval[AddrYval].onept();

        for(int j=0; j<ALIGN_SIMD(width)/VCOP_SIMD_WIDTH; j++) {
            __agen AddrIn, AddrXval;
            __vector vIn, vxVal, vBitMask, vxValAbsolute, vyValAbsolute, vNumNewElmts, vMask, vFlag, vQshift, vMaxNumElmts;
            __vector vZero, vNeg1;

            vZero= 0;
            vNeg1= -1;

            vQshift= qShift;
            vMaxNumElmts= maxNumElmts;

            AddrIn= i*sizeof(*pIn)*inStride + j*sizeof(*pIn)*VCOP_SIMD_WIDTH;
            AddrXval= j*sizeof(*pXval)*VCOP_SIMD_WIDTH;

            vIn=pIn[AddrIn].npt();
            vxVal= pXval[AddrXval].npt();

            vBitMask= pack(vIn >= vOne);
            vxValAbsolute= vxVal + vBlockX;

            vyValAbsolute= vyVal + vBlockY;
            vNumNewElmts= count_bits(vBitMask);

            vMask= unpack(vBitMask, vOneIn8Lanes);
            vNumElmts+= vNumNewElmts;

            vFlag= (vNumElmts > vMaxNumElmts);
            vxValAbsolute= vxValAbsolute << vQshift;

            vFlag&= vNeg1; /* workaround for silicon bug present in centEve, but not on Vayu: vFlag is left unchanged as long as Vneg1’s value remains at 0xFFFFFFFFFF */
            vyValAbsolute= vyValAbsolute << vQshift;


            vNeg1= select(vFlag, vZero, vNeg1); /* workaround for silicon bug present in centEve, but on Vayu: as soon as vFlag becomes 1 then Vneg1’s value turns to 0 and in next iteration the operation in previous line always assigns 0 to vFlag. */
            vNumElmts= min(vNumElmts, vMaxNumElmts);

            pListX[collate(vMask)]= vxValAbsolute;
            pListY[collate(vMask)]= vyValAbsolute;
            pNumElmtsX[Addr0].onept()= vNumElmts;
            pNumElmtsY[Addr0].onept()= vNumElmts;

            if (vFlag[0]) goto end_loop; /* we don't want to add more elements if maxNumElmts reached */

        }
    }

    end_loop:;

}
#if 1
void vcop_updateGenerateList(
        __vptr_uint32 preg,
        unsigned int  pListX, /* pointer to X coordinate of the current block processed */
        unsigned int  pListY, /* pointer to Y coordinate of the current block processed */
        __vptr_uint16  pNumElmtsX,
        unsigned short listXOfst,
        unsigned short listYOfst)
{

    __agen Addr0;
    __vector vNumElmts;
    __vector vMaxNumElmts;
    __vector vConst0;
    __vector vListX, vListY;
    __vector vFlag;

  vConst0      = 0;
  Addr0        = 0;
  vListX       = pListX;
  vListY       = pListY;

    vNumElmts= pNumElmtsX[Addr0].onept();

    for (int i=0; i<1; i++)
    {

        vListX+= vNumElmts;
        vListY+= vNumElmts;

        vListX+= vNumElmts;
        vListY+= vNumElmts;

        (preg + listXOfst*sizeof(*preg))[Addr0].onept()= vListX;
        (preg + listYOfst*sizeof(*preg))[Addr0].onept()= vListY;
    }
}

void vcop_copyListToOutBuff
  (
  __vptr_uint16  pListX,
  __vptr_uint16  pListY,
  __vptr_uint16  pListXY,
  __vptr_uint16  pNumElmts,
  __vptr_uint16  pNumElmtsOut,
 unsigned short NumElmts,
  unsigned short offsetX,
  unsigned short offsetY
  )
{
  __agen Addr0;
  __agen Addr1;
  __agen Addr2;
  __vector vListX, vListY;
  __vector voffsetX, voffsetY,vListYout;
  voffsetX = offsetX;
  voffsetY = offsetY;
  __vector vIn;

  Addr2 = 0;
  vIn = pNumElmts[Addr2].onept();
  for (int j=0; j<1; j++)
  {
    for (int i=0; i<NumElmts/VCOP_SIMD_WIDTH; i++)
    {
      Addr0 = i*VCOP_SIMD_WIDTH*sizeof(*pListX);
      Addr1 = i*VCOP_SIMD_WIDTH*sizeof(*pListX)*2;

      vListX = pListX[Addr0];
      vListY = pListY[Addr0];
      vListX    = vListX + voffsetX;
      vListYout = vListY + voffsetY;

      pListXY[Addr1].interleave() = (vListX,vListYout);
    }
    pNumElmtsOut[Addr2].onept()= vIn;
  }
}

void vcop_copyNumElementsToOutBuff_init
  (
  __vptr_uint16  src,
  __vptr_uint16  dst
  )
{
  __agen Addr0;
  __vector vIn;

  Addr0 = 0;
  vIn = src[Addr0].onept();

  for (int i=0; i<1; i++)
  {
    dst[Addr0].onept()= vIn;
  }
}



#endif
/* ======================================================================== */
/*  End of file:  vcop_vec_gradients_xy_and_magnitude_kernel.k              */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


