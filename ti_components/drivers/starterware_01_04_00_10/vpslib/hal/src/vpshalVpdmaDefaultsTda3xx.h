/* ======================================================================
 *   Copyright (C) 2013 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

/**
 * \file vpshalVpdmaDefaultsTda3xx.h
 *
 * \brief VPS VPDMA HAL default configuration file
 * This file contains default configuration for VPDMA.
 *
 */

#ifndef VPSSHALVPDMADEFAULTS_TDA3XX_H_
#define VPSSHALVPDMADEFAULTS_TDA3XX_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * Expert value for the anchor and interpolated pixel
 */
#define VPSHAL_VPDMA_DEFAULT_CHANNEL_INFO                                     \
    {                                                                         \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC0,                             \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC1,                             \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC2,                             \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC3,                             \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC4,                             \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC5,                             \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC6,                             \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC7,                             \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC8,                             \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC9,                             \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC10,                            \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC11,                            \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC12,                            \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC13,                            \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC14,                            \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC15,                            \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC0,                             \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC1,                             \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC2,                             \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC3,                             \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC4,                             \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC5,                             \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC6,                             \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC7,                             \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC8,                             \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC9,                             \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC10,                            \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC11,                            \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC12,                            \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC13,                            \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC14,                            \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC15,                            \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC0,                              \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC1,                              \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC2,                              \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC3,                              \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC4,                              \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC5,                              \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC6,                              \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC7,                              \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC8,                              \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC9,                              \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC10,                             \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC11,                             \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC12,                             \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC13,                             \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC14,                             \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC15,                             \
         VPDMA_S0_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC0,                              \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC1,                              \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC2,                              \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC3,                              \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC4,                              \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC5,                              \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC6,                              \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC7,                              \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC8,                              \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC9,                              \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC10,                             \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC11,                             \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC12,                             \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC13,                             \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC14,                             \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC15,                             \
         VPDMA_S0_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S0_PORTA_LUMA,                                  \
         VPDMA_S0_UP_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_S0_PORTA_CHROMA,                                \
         VPDMA_S0_UP_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_S0_PORTB_LUMA,                                  \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_S0_PORTB_CHROMA,                                \
         VPDMA_S0_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_S0_PORTA_RGB,                                   \
         VPDMA_S0_UP_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_S0_PORTB_RGB,                                   \
         VPDMA_S0_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC0,                             \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC1,                             \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC2,                             \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC3,                             \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC4,                             \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC5,                             \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC6,                             \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC7,                             \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC8,                             \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC9,                             \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC10,                            \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC11,                            \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC12,                            \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC13,                            \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC14,                            \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC15,                            \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC0,                             \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC1,                             \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC2,                             \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC3,                             \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC4,                             \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC5,                             \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC6,                             \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC7,                             \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC8,                             \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC9,                             \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC10,                            \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC11,                            \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC12,                            \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC13,                            \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC14,                            \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC15,                            \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC0,                              \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC1,                              \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC2,                              \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC3,                              \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC4,                              \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC5,                              \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC6,                              \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC7,                              \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC8,                              \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC9,                              \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC10,                             \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC11,                             \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC12,                             \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC13,                             \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC14,                             \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC15,                             \
         VPDMA_S1_ANC_A_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC0,                              \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC1,                              \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC2,                              \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC3,                              \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC4,                              \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC5,                              \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC6,                              \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC7,                              \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC8,                              \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC9,                              \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC10,                             \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC11,                             \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC12,                             \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC13,                             \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC14,                             \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC15,                             \
         VPDMA_S1_ANC_B_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_S1_PORTA_LUMA,                                  \
         VPDMA_S1_UP_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_S1_PORTA_CHROMA,                                \
         VPDMA_S1_UP_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_S1_PORTB_LUMA,                                  \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_S1_PORTB_CHROMA,                                \
         VPDMA_S1_LO_UV_CSTAT,                                                \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_S1_PORTA_RGB,                                   \
         VPDMA_S1_UP_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_S1_PORTB_RGB,                                   \
         VPDMA_S1_LO_Y_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
    }

#define VPSHAL_VPDMA_DEFAULT_PATH_INFO                          \
    {                                                           \
        {VPSHAL_VPDMA_PATH_VIP0_LO_UV, TRUE, 1920, 4096, 4096}, \
        {VPSHAL_VPDMA_PATH_VIP0_LO_Y, TRUE, 1920, 4096, 4096},  \
        {VPSHAL_VPDMA_PATH_VIP0_UP_UV, TRUE, 1920, 4096, 4096}, \
        {VPSHAL_VPDMA_PATH_VIP0_UP_Y, TRUE, 1920, 4096, 4096},  \
        {VPSHAL_VPDMA_PATH_VIP1_LO_UV, TRUE, 1920, 4096, 4096}, \
        {VPSHAL_VPDMA_PATH_VIP1_LO_Y, TRUE, 1920, 4096, 4096},  \
        {VPSHAL_VPDMA_PATH_VIP1_UP_UV, TRUE, 1920, 4096, 4096}, \
        {VPSHAL_VPDMA_PATH_VIP1_UP_Y, TRUE, 1920, 4096, 4096},  \
        {VPSHAL_VPDMA_PATH_VIP0_ANCA, FALSE, 0, 4096, 4096},    \
        {VPSHAL_VPDMA_PATH_VIP0_ANCB, FALSE, 0, 4096, 4096},    \
        {VPSHAL_VPDMA_PATH_VIP1_ANCA, FALSE, 0, 4096, 4096},    \
        {VPSHAL_VPDMA_PATH_VIP1_ANCB, FALSE, 0, 4096, 4096},    \
        {VPSHAL_VPDMA_PATH_SEC0, TRUE, 1920, 1920, 4096},       \
        {VPSHAL_VPDMA_PATH_SEC1, TRUE, 1920, 1920, 4096},       \
        {VPSHAL_VPDMA_PATH_PRI, TRUE, 1920, 1920, 4096},        \
        {VPSHAL_VPDMA_PATH_WB0, FALSE, 0, 4096, 4096},          \
        {VPSHAL_VPDMA_PATH_AUX, TRUE, 1920, 1920, 4096},        \
        {VPSHAL_VPDMA_PATH_WB1, FALSE, 0, 4096, 4096},          \
        {VPSHAL_VPDMA_PATH_BP0, FALSE, 0, 4096, 4096},          \
        {VPSHAL_VPDMA_PATH_BP1, FALSE, 0, 4096, 4096},          \
        {VPSHAL_VPDMA_PATH_WB2, FALSE, 0, 4096, 4096},          \
        {VPSHAL_VPDMA_PATH_GRPX0, FALSE, 0, 4096, 4096},        \
        {VPSHAL_VPDMA_PATH_GRPX0_STENC, FALSE, 0, 4096, 4096},  \
        {VPSHAL_VPDMA_PATH_GRPX1, FALSE, 0, 4096, 4096},        \
        {VPSHAL_VPDMA_PATH_GRPX1_STENC, FALSE, 0, 4096, 4096},  \
        {VPSHAL_VPDMA_PATH_GRPX2, FALSE, 0, 4096, 4096},        \
        {VPSHAL_VPDMA_PATH_GRPX2_STENC, FALSE, 0, 4096, 4096},  \
        {VPSHAL_VPDMA_PATH_VBI_HD, FALSE, 0, 4096, 4096},       \
        {VPSHAL_VPDMA_PATH_VBI_SD, FALSE, 0, 4096, 4096},       \
        {VPSHAL_VPDMA_PATH_NF, TRUE, 1920, 4096, 4096}          \
    }

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None*/

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPSSHALVPDMADEFAULTS_TDA3XX_H_ */
