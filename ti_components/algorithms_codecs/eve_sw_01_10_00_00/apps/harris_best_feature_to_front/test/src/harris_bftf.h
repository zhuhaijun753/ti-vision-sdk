/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#ifndef _HARRIS_BFTF_H_
#define HARRIS_BFTF_H_

#include "stdint.h"
#include <stdlib.h>


int HarrisScoreBestFeatureToFront(
    unsigned char *src[],
    unsigned int  *cornerListXY[],
    unsigned int   cornerListSize[],
    unsigned short srcImageWidth,
    unsigned short srcImageHeight,
    unsigned short srcBufferPitch,
    unsigned short sensitivityParam,
    unsigned int  *cornerListXYOut,
    unsigned char *cornerListLevelOut,
    unsigned char  numLevels,
    unsigned int   bestN
);

#endif /*HARRIS_BFTF_H_*/

