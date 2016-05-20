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

int IDH_freeImage(Image *ptr)
{
#if 0
    if(ptr->bpp == 0)
    {
        return 1;
    }
    else if(ptr->bpp == 8)
    {
        ptr->bpp  = 0;
        ptr->rows = 0;
        ptr->cols = 0;
        ptr->res  = 0;

        free(ptr->adata);
        return 1;
    }
    else if(ptr->bpp == 24)
    {
        ptr->bpp  = 0;
        ptr->rows = 0;
        ptr->cols = 0;
        ptr->res  = 0;

        if(NULL != ptr->bdata)
            free(ptr->bdata);
        if(NULL != ptr->gdata)
            free(ptr->gdata);
        if(NULL != ptr->rdata)
            free(ptr->rdata);

        return 1;
    }
    else if(ptr->bpp == 32)
    {
        ptr->bpp  = 0;
        ptr->rows = 0;
        ptr->cols = 0;
        ptr->res  = 0;

        free(ptr->bdata);
        free(ptr->gdata);
        free(ptr->rdata);
        free(ptr->adata);

        return 1;
    }
    else
    {
        ptr->bpp = 0;
        return 1;
    }
#endif
    if (NULL != ptr->rdata)
    {
        BspUtils_memFree(ptr->rdata, sizeof(int)*(ptr->rows*ptr->cols));
        ptr->rdata = NULL;
    }
    if (NULL != ptr->gdata)
    {
        BspUtils_memFree(ptr->gdata, sizeof(int)*(ptr->rows*ptr->cols));
        ptr->gdata = NULL;
    }
    if (NULL != ptr->bdata)
    {
        BspUtils_memFree(ptr->bdata, sizeof(int)*(ptr->rows*ptr->cols));
        ptr->bdata = NULL;
    }
    if (NULL != ptr->adata)
    {
        BspUtils_memFree(ptr->adata, sizeof(int)*(ptr->rows*ptr->cols));
        ptr->adata = NULL;
    }

    return 1;
}

