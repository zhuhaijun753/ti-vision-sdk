/************************************************************************************//**
* TI ISP Library Reference Code
* This library is a software module developed for simulation of vision and ISP
* algorithms ported on TI's embedded platforms
* Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
* ALL RIGHTS RESERVED
* @author       Hrushikesh Garud (A0393878)
* @version      1.0
*
****************************************************************************************/

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "inc/Image_Data_Handling.h"

# include <utility/bsputils_mem.h>

int IDH_createImage(Image *ptr, int rows, int columns, int bpp, int overwrite)
{
    int test;
    if(overwrite == 0 && (ptr->bpp == 8 || ptr->bpp == 24 || ptr->bpp == 32))
    {
        return (0);
    }
    else
    {
        test = IDH_freeImage(ptr);
        if(test == 0)
        {
            return -1;
        }
        ptr->bpp  = bpp;
        ptr->rows = rows;
        ptr->cols = columns;
        ptr->res  = 11808;

#if 0
        if(bpp == 32)
        {
            ptr->bdata = (int *)calloc(sizeof(int), (rows*columns));
            ptr->gdata = (int *)calloc(sizeof(int), (rows*columns));
            ptr->rdata = (int *)calloc(sizeof(int), (rows*columns));
            ptr->adata = (int *)calloc(sizeof(int), (rows*columns));
        }
        else if(bpp == 24)
        {
            ptr->bdata = (int *)calloc(sizeof(int), (rows*columns));
            ptr->gdata = (int *)calloc(sizeof(int), (rows*columns));
            ptr->rdata = (int *)calloc(sizeof(int), (rows*columns));
        }
        else if(bpp == 8)
        {
            ptr->adata = (int *)calloc(sizeof(int), (rows*columns));
        }
#endif
        ptr->rdata = (int *)BspUtils_memAlloc(sizeof(int)*(rows*columns), 16);
        ptr->gdata = (int *)BspUtils_memAlloc(sizeof(int)*(rows*columns), 16);
        ptr->bdata = (int *)BspUtils_memAlloc(sizeof(int)*(rows*columns), 16);
        ptr->adata = (int *)BspUtils_memAlloc(sizeof(int)*(rows*columns), 16);
    }
    return 1;
}

