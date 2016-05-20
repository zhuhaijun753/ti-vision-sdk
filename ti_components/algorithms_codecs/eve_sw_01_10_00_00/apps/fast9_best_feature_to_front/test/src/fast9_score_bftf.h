/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#ifndef _FAST9_SCORE_BFTF_H_
#define _FAST9_SCORE_BFTF_H_

#ifdef __cplusplus
extern "C" {
#endif

int FAST9ScoreCompute(
    unsigned char *src,
    unsigned short srcImageWidth,
    unsigned short srcImageHeight,
    unsigned short srcBufferPitch,
    unsigned int   * cornerListXY,
    unsigned int   cornerListSize,
    unsigned char  fast9Th,
    unsigned char  sad_method,
    unsigned short *outScore);
    
#ifdef __cplusplus
}
#endif

#endif
