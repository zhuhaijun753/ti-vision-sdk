/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       ti_draw_utils.h
 *
 *  @brief      This file defines the interface for line and box drawing
 *  @version 0.0 (Sep 2014) : Base version.
 */
#ifndef PYRAMID_LK_SOF_DRAW_UTILS
#define PYRAMID_LK_SOF_DRAW_UTILS

void
APP_drawBoxRGB
(
uint8_t * srcR, 
uint8_t * srcG,
uint8_t * srcB,
uint32_t  rgb24bit,
int16_t  cols,
int16_t  x1, 
int16_t  y1, 
int16_t  x2, 
int16_t  y2
);
void
APP_drawLineRGB(
uint8_t * srcR, 
uint8_t * srcG,
uint8_t * srcB,
uint32_t  rgb24bit,
int16_t  cols,
int16_t  x1, 
int16_t  y1, 
int16_t  x2, 
int16_t  y2
        );
void APP_convertYUV420ptoRGB888(
              uint8_t * y, 
              uint8_t * u, 
              uint8_t * v, 
						  uint8_t * r, 
						  uint8_t * g,
						  uint8_t * b,
						  uint16_t   cols,
						  uint16_t   rows);

void APP_convertYUV420sptoRGB888(
              uint8_t * y, 
              uint8_t * uv, 
						  uint8_t * r, 
						  uint8_t * g,
						  uint8_t * b,
						  uint16_t   cols,
						  uint16_t   rows);

void APP_convertRGB888toYUV420p(
						  uint8_t * r, 
						  uint8_t * g,
						  uint8_t * b,
              uint8_t * y, 
              uint8_t * u, 
              uint8_t * v, 
						  uint16_t   cols,
						  uint16_t   rows);

void APP_convertRGB888toYUV420sp(
						  uint8_t * r, 
						  uint8_t * g,
						  uint8_t * b,
              uint8_t * y, 
              uint8_t * uv, 
						  uint16_t   cols,
						  uint16_t   rows);

#endif
