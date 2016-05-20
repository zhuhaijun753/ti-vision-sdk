/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int32_t readFilePGM(const int8_t *infilename,
             uint8_t **image,
             uint16_t *n_rows,
             uint16_t *n_cols,
             uint16_t *bytesPerPixel,
             uint16_t *maxBitPerPixel,
             int32_t *n_maxValue);

int32_t writeFile_PGM(const int8_t *outfilename,
              const uint8_t *image,
              uint16_t n_rows,
              uint16_t n_cols,
              const int8_t *comment,
              int32_t maxval);

int32_t writeFile_PPM(const int8_t *outfilename,
              const uint8_t *image_red,
              const uint8_t *image_grn,
              const uint8_t *image_blu,
              uint16_t n_rows,
              uint16_t n_cols,
              const int8_t *comment,
              int32_t maxval);

