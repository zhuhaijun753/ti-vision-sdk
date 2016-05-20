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
# include <math.h>
//# include <memory.h>
# include <stdlib.h>

# include "inc/Image_Data_Handling.h"
# include "inc/spatial_domain.h"

int IDH_remapFromLUT(Image *ptr, char channel, lookUpTable *LUT) {
    int  i, j, temp;
    int *dummyPtr;

    if((ptr->bpp != 8 && ptr->bpp != 24 &&
        ptr->bpp != 32) ||
       (ptr->bpp == 8 && channel != 'a') || (ptr->bpp == 24 && channel == 'a'))
    {
        return (-1);
    }

    if(ptr->bpp == 24 || ptr->bpp == 32)
    {
        switch(channel) {
            case 'b': dummyPtr = ptr->bdata; break;
            case 'g': dummyPtr = ptr->gdata; break;
            case 'r': dummyPtr = ptr->rdata; break;
            case 'a':   if(ptr->bpp != 32)
                {
                    return -1;
                }
                else
                {
                    dummyPtr = ptr->adata; break;
                }
            default: return 0;
        }
    }

    if(ptr->bpp == 8)
    {
        if(channel != 'a')
        {
            return 0;
        }
        else
        {
            dummyPtr = ptr->adata;
        }
    }

    for(i = 0; i <= ptr->rows - 1; i++) {
        for(j = 0; j <= ptr->cols - 1; j++) {
            temp = *(dummyPtr + (i * ptr->cols) + j);
            *(dummyPtr + (i * ptr->cols) + j) = LUT->table[temp];
        }
    }

    return(1);
}

