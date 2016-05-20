/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*--------------------------------------------------------------------------*/
/* NAME: vcop_copy_new_lk_xy_cn.c                                           */
/*                                                                          */
/* DESCRIPTION:                                                             */
/*                                                                          */
/* The file provides kernel for copying the xy points from internal scratch */
/* to output buffer                                                         */
/*                                                                          */
/*     @version 1.0 (January 2014) : Base version.                          */
/*                                                                          */
/*==========================================================================*/

void vcop_copy_new_lk_xy_cn
(
    short         *  pInput_A,
    short         *  pOutput_B,
    unsigned char *  currValidPoints,
    unsigned int  *  pBaseAddrList ,
    unsigned int  *  pValidAddrList,
    unsigned int  *  pOutAddrList     ,
    unsigned int  *  pValidOutAddrList,
    short         *  pLocalX,
    short         *  pLocalY,
    short         *  pLocalXY,
    unsigned short   numKeyPoints
)
{
    unsigned short i;

    for(i = 0; i < numKeyPoints; i++)
    {
        pOutput_B[2*i] = pInput_A[2*i];
        pOutput_B[2*i+1] = pInput_A[2*i+1];
        pValidAddrList[i] = pBaseAddrList[i];
        pValidOutAddrList[i] = pOutAddrList[i];
        currValidPoints[i] = 1;
        //pLocalX[i] = pLocalXY[2*i];
        //pLocalY[i] = pLocalXY[2*i+1];
    }
}
