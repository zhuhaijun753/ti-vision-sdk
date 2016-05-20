/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       ti_draw_utils.c
 *
 *  @brief      This file defines the functions for line and box drawing
 *  @version 0.0 (Sep 2014) : Base version.
 */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <vcop.h>

#include "xdais_types.h"

#include "ti_draw_utils.h"

#ifndef MIN
#define MIN(x,y) (x < y ? x : y)
#endif
#ifndef MAX
#define MAX(x,y) (x > y ? x : y)
#endif

#ifndef clip8Bit
#define clip8Bit(x) MAX( MIN(x, 255), 0)
#endif

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
)
{
	uint16_t     left;
	uint16_t     right;
	uint16_t     top;
	uint16_t     bottom;
	uint16_t     y;
	uint32_t     offset;

	uint8_t r = (rgb24bit >> 16) & 0xff;
	uint8_t g = (rgb24bit >> 8 ) & 0xff;
	uint8_t b = (rgb24bit      ) & 0xff;

		left    = x1;
		right   = x2;
		top     = y1;
		bottom  = y2;

		// draw top boundary line
		offset = cols * top + left;
		memset(&srcR[offset], r, right - left + 1);
		memset(&srcG[offset], g, right - left + 1);
		memset(&srcB[offset], b, right - left + 1);

		// draw left & right boundary lines
		for (y = top+1; y <= bottom; y++)
		{
			// left
			srcR[offset] = r;
			srcG[offset] = g;
			srcB[offset] = b;
      
			srcR[offset + (right - left)] = r;
			srcG[offset + (right - left)] = g;
			srcB[offset + (right - left)] = b;

			// incrememt offset for next row
			offset += cols;
		}
		// draw bottom boundary lines
		offset = cols * bottom + left;
		memset(&srcR[offset], r, right - left + 1);
		memset(&srcG[offset], g, right - left + 1);
		memset(&srcB[offset], b, right - left + 1);
}

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
        ) 
{
	int32_t delta_x, delta_y, i, e, ebigstep, esmallstep;

	uint8_t r = (rgb24bit >> 16) & 0xff;
	uint8_t g = (rgb24bit >> 8 ) & 0xff;
	uint8_t b = (rgb24bit      ) & 0xff;


	if (x1 > x2) 
	{
		int16_t tmp;
		tmp = x2; x2 = x1; x1 = tmp;
		tmp = y2; y2 = y1; y1 = tmp;
	}

	delta_x = x2 - x1;
	delta_y = y2 - y1;

	// know that delta_x >= 0
	if ((delta_x >= delta_y) && (delta_y >= 0)) 
	{
		e 			= (delta_y << 1) - delta_x;
		ebigstep 	= (delta_y << 1) - (delta_x << 1);
		esmallstep 	= (delta_y << 1);

		for (i = 1; i <= delta_x; i++) 
		{
			srcR[y1 * cols + x1] = r;
			srcG[y1 * cols + x1] = g;
			srcB[y1 * cols + x1] = b;
			if (e > 0) 	{
				y1++; 
				e += ebigstep;
			} 
			else 
				e += esmallstep;
			x1++;
		}
	}
	else if (delta_x < delta_y) 
	{
		e 			= (delta_x << 1) - delta_y;
		ebigstep 	= (delta_x << 1) - (delta_y << 1);
		esmallstep 	= (delta_x << 1);

		for (i = 1; i <= delta_y; i++) {
			srcR[y1 * cols + x1] = r;
			srcG[y1 * cols + x1] = g;
			srcB[y1 * cols + x1] = b;
			if (e > 0) 	{
				x1++; 
				e += ebigstep;
			} 
			else 
				e += esmallstep;
			y1++;
		}
	}
	else if (delta_x >= (delta_y = abs(delta_y))) 
	{
		e 			= (delta_y << 1) - delta_x;
		ebigstep 	= (delta_y << 1) - (delta_x << 1);
		esmallstep	= (delta_y << 1);

		for (i = 1; i <= delta_x; i++) {
			srcR[y1 * cols + x1] = r;
			srcG[y1 * cols + x1] = g;
			srcB[y1 * cols + x1] = b;
			if (e > 0) 	{
				y1--; 
				e += ebigstep;
			} 
			else 
				e += esmallstep;
			x1++;
		}
	} 
	else 
	{
		e 			= (delta_x << 1) - delta_y;
		ebigstep 	= (delta_x << 1) - (delta_y << 1);
		esmallstep 	= (delta_x << 1);

		for (i = 1; i <= delta_y; i++) {
			srcR[y1 * cols + x1] = r;
			srcG[y1 * cols + x1] = g;
			srcB[y1 * cols + x1] = b;
			if (e > 0) 	{
				x1++; 
				e += ebigstep;
			}
			else 
				e += esmallstep;
			y1--;
		}
	}
}

void APP_convertYUV420ptoRGB888(
              uint8_t * y, 
              uint8_t * u, 
              uint8_t * v, 
						  uint8_t * r, 
						  uint8_t * g,
						  uint8_t * b,
						  uint16_t   cols,
						  uint16_t   rows)
{
	int32_t C, D, E;
	uint32_t i;
	uint32_t j;
	for(i = 0; i < rows; i++)
		for(j = 0; j < cols; j++)
		{
			C = y[cols*i + j];
			D = u[(cols>>1)*(i>>1) + (j>>1)];
			E = v[(cols>>1)*(i>>1) + (j>>1)];

		  C = C - 16;
		  D = D - 128;
		  E = E - 128;

		  r[cols*i + j] = (uint8_t) clip8Bit(( 298 * C           + 409 * E + 128) >> 8);
		  g[cols*i + j] = (uint8_t) clip8Bit(( 298 * C - 100 * D - 208 * E + 128) >> 8);
		  b[cols*i + j] = (uint8_t) clip8Bit(( 298 * C + 516 * D           + 128) >> 8);

		}	
}

void APP_convertYUV420sptoRGB888(
              uint8_t * y, 
              uint8_t * uv, 
						  uint8_t * r, 
						  uint8_t * g,
						  uint8_t * b,
						  uint16_t   cols,
						  uint16_t   rows)
{
	int32_t C, D, E;
	uint32_t i;
	uint32_t j;
	uint8_t * u = uv;
	uint8_t * v = u + 1;
	for(i = 0; i < rows; i++)
		for(j = 0; j < cols; j++)
		{
			C = y[cols*i + j];
			D = u[cols*(i>>1) + ((j>>1)<<1)];
			E = v[cols*(i>>1) + ((j>>1)<<1)];

		  C = C - 16;
		  D = D - 128;
		  E = E - 128;

		  r[cols*i + j] = (uint8_t) clip8Bit(( 298 * C           + 409 * E + 128) >> 8);
		  g[cols*i + j] = (uint8_t) clip8Bit(( 298 * C - 100 * D - 208 * E + 128) >> 8);
		  b[cols*i + j] = (uint8_t) clip8Bit(( 298 * C + 516 * D           + 128) >> 8);

		}	
}

void APP_convertRGB888toYUV420p(
						  uint8_t * r, 
						  uint8_t * g,
						  uint8_t * b,
              uint8_t * y, 
              uint8_t * u, 
              uint8_t * v, 
						  uint16_t   cols,
						  uint16_t   rows)
{
	int32_t R, G, B;
	uint32_t i;
	uint32_t j;
	for(i = 0; i < rows; i++)
		for(j = 0; j < cols; j++)
		{
      R = r[cols*i + j];
      G = g[cols*i + j];
      B = b[cols*i + j];

      y[cols*i + j]                = ( (  66 * (R) + 129 * (G) +  25 * (B) + 128) >> 8) +  16;

      if(((i&1) == 0) && ((j&1) == 0))
      {
		    u[(cols>>1)*(i>>1) + (j>>1)] = ( ( -38 * (R) -  74 * (G) + 112 * (B) + 128) >> 8) + 128;
		    v[(cols>>1)*(i>>1) + (j>>1)] = ( ( 112 * (R) -  94 * (G) -  18 * (B) + 128) >> 8) + 128;
      }

		}	
}

void APP_convertRGB888toYUV420sp(
						  uint8_t * r, 
						  uint8_t * g,
						  uint8_t * b,
              uint8_t * y, 
              uint8_t * uv, 
						  uint16_t   cols,
						  uint16_t   rows)
{
	int32_t R, G, B;
	uint32_t i;
	uint32_t j;
	uint8_t * u = uv;
	uint8_t * v = u + 1;
	for(i = 0; i < rows; i++)
		for(j = 0; j < cols; j++)
		{
      R = r[cols*i + j];
      G = g[cols*i + j];
      B = b[cols*i + j];

      y[cols*i + j]                = ( (  66 * (R) + 129 * (G) +  25 * (B) + 128) >> 8) +  16;

      if(((i&1) == 0) && ((j&1) == 0))
      {
		    u[cols*(i>>1) + ((j>>1)<<1)] = ( ( -38 * (R) -  74 * (G) + 112 * (B) + 128) >> 8) + 128;
		    v[cols*(i>>1) + ((j>>1)<<1)] = ( ( 112 * (R) -  94 * (G) -  18 * (B) + 128) >> 8) + 128;
      }

		}	
}


