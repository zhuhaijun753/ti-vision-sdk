/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/** @file_image_file_io.c
*
*  @brief  This file contains code for reading, writing Y, YUV, PGM files
*
*
*  @date   April 2015
*
*  Description
*
*/
#ifndef _IMAGE_FILE_IO_TEST_H_
#define _IMAGE_FILE_IO_TEST_H_

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

int32_t readFileYUV_ILE_IBE(const int8_t *infilename,
             uint8_t **image,
             uint16_t height,
             uint16_t width);

int32_t readFileY(const int8_t *infilename,
             uint8_t **image,
             uint16_t height,
             uint16_t width);

int32_t writeFile_PGM(const int8_t *outfilename,
              const uint8_t *image,
              uint16_t n_rows,
              uint16_t n_cols,
              const int8_t *comment,
              int32_t maxval);

int32_t writeFileYUV_ILE_IBE(const int8_t *outfilename,
              const uint8_t *image,
              uint16_t height,
              uint16_t width
              );

int32_t writeFileY(const int8_t *outfilename,
              const uint8_t *image,
              uint16_t height,
              uint16_t width
              );

int32_t writeFile_PPM(const int8_t *outfilename,
              const uint8_t *image_red,
              const uint8_t *image_grn,
              const uint8_t *image_blu,
              uint16_t n_rows,
              uint16_t n_cols,
              const int8_t *comment,
              int32_t maxval);

int32_t writeFile_YUV444(const int8_t *outfilename,
              const uint8_t *image_y,
              const uint8_t *image_u,
              const uint8_t *image_v,
              uint16_t n_rows,
              uint16_t n_cols,
              const int8_t *comment,
              int32_t maxval);

int32_t writeFile_YUV420SP(const int8_t *outfilename,
              const uint8_t *image_y,
              const uint8_t *image_uv,
              uint16_t n_rows,
              uint16_t n_cols,
              const int8_t *comment,
              int32_t maxval);

#endif
